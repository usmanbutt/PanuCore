#include "ScriptPCH.h"
#include <cstring>

#define SET_CURRENCY 0  //0 for gold, 1 for honor, 2 for tokens
#define TOKEN_ID 0 // token id

#if SET_CURRENCY == 0
#define BOUNTY_1 "I would like to place a 20g bounty."
#define BOUNTY_2 "I would like to place a 40g bounty."
#define BOUNTY_3 "I would like to place a 100g bounty."
#define BOUNTY_4 "I would like to place a 200g bounty."
#endif
#if SET_CURRENCY == 1
#define BOUNTY_1 "I would like to place a 20 honor bounty."
#define BOUNTY_2 "I would like to place a 40 honor bounty."
#define BOUNTY_3 "I would like to place a 100 honor bounty."
#define BOUNTY_4 "I would like to place a 200 honor bounty."
#endif
#if SET_CURRENCY == 2
#define BOUNTY_1 "I would like to place a 1 token bounty."
#define BOUNTY_2 "I would like to place a 3 token bounty."
#define BOUNTY_3 "I would like to place a 5 token bounty."
#define BOUNTY_4 "I would like to place a 10 token bounty."
#endif

#define PLACE_BOUNTY "I would like to place a bounty."
#define BECOME_HUNTER "I would like to become a hunter."
#define LIST_BOUNTY "List the current bounties."
#define NVM "Nevermind"
#define WIPE_BOUNTY "Wipe bounties"

#if SET_CURRENCY != 2
//these are just visual prices, if you want to to change the real one, edit the sql further below
enum BountyPrice
{
        BOUNTY_PRICE_1 = 20,
        BOUNTY_PRICE_2 = 40,
        BOUNTY_PRICE_3 = 100,
        BOUNTY_PRICE_4 = 200,
};
#else
enum BountyPrice
{
        BOUNTY_PRICE_1 = 1,
        BOUNTY_PRICE_2 = 3,
        BOUNTY_PRICE_3 = 5,
        BOUNTY_PRICE_4 = 10,
};
#endif


bool passChecks(Player * pPlayer, const char * name)
{ 

Player * pBounty = sObjectAccessor->FindPlayerByName(name);
WorldSession * m_session = pPlayer->GetSession();
if(!pBounty)
{
m_session->SendNotification("The player is offline or doesn't exist!");
return false;
}
QueryResult result = CharacterDatabase.PQuery("SELECT * FROM bounties WHERE guid ='%u'", pBounty->GetGUID());
if(result)
{
m_session->SendNotification("This player already has a bounty on them!");
return false;
}
if(pPlayer->GetGUID() == pBounty->GetGUID())
{
m_session->SendNotification("You cannot set a bounty on yourself!");
return false;
}
return true;
}

void alertServer(const char * name, int msg)
{
std::string message;
if(msg == 1)
{
message = "A bounty has been placed on ";
message += name;
message += ". Kill them immediately to collect the reward!";
}
else if(msg == 2)
{
message = "The bounty on ";
message += name;
message += " has been collected!";
}
else if(msg == 3)
{
message = name;
message += " is now a Bounty Hunter!";
}
else if(msg == 4)
{
message = "A Bounty Hunter has been killed by, ";
message += name;
   message += ", the reward for his head has been increased!";
}
sWorld->SendServerMessage(SERVER_MSG_STRING, message.c_str(), 0);
}

bool hasCurrency(Player * pPlayer, uint32 required, int currency)
{
   WorldSession *m_session = pPlayer->GetSession();
        switch(currency)
        {
                case 0: //gold
   {
                        uint32 currentmoney = pPlayer->GetMoney();
                        uint32 requiredmoney = (required * 10000);
                        if(currentmoney < requiredmoney)
                        {
                                m_session->SendNotification("You don't have enough gold!");
                                return false;
                        }
                        pPlayer->SetMoney(currentmoney - requiredmoney);
                        break;
}
                case 1: //honor
{
                        uint32 currenthonor = pPlayer->GetHonorPoints();
                        if(currenthonor < required)
                        {
                                m_session->SendNotification("You don't have enough honor!");
                                return false;
                        }
                        pPlayer->SetHonorPoints(currenthonor - required);
                        break;
}
                case 2: //tokens
{
                        if(!pPlayer->HasItemCount(TOKEN_ID, required))
                        {
                                m_session->SendNotification("You don't have enough tokens!");
                                return false;
                        }
                        pPlayer->DestroyItemCount(TOKEN_ID, required, true, false);
                        break;
}
 
        }
        return true;
}

void flagPlayer(const char * name)
{
Player * pBounty = sObjectAccessor->FindPlayerByName(name);
pBounty->SetPvP(true);
pBounty->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
}

class BountyHunter : public CreatureScript
{
public:
BountyHunter() : CreatureScript("BountyHunter"){}
bool OnGossipHello(Player * Player, Creature * Creature)
{
Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, BECOME_HUNTER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, LIST_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
if ( Player->isGameMaster() )
{
Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, WIPE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
}
            Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, NVM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
Player->PlayerTalkClass->SendGossipMenu(907, Creature->GetGUID());
return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
pPlayer->PlayerTalkClass->ClearMenus();
switch(uiAction)
{
case GOSSIP_ACTION_INFO_DEF+1:
{
pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5, "", 0, true);
pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6, "", 0, true);
pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7, "", 0, true);
pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8, "", 0, true);
pPlayer->PlayerTalkClass->SendGossipMenu(365, pCreature->GetGUID());
break;
}
case GOSSIP_ACTION_INFO_DEF+2:
{
QueryResult Bounties = CharacterDatabase.PQuery("SELECT * FROM bounties");
if(!Bounties)
{
pPlayer->PlayerTalkClass->SendCloseGossip();
return false;
}

if( Bounties->GetRowCount() > 1)
{
pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bounties: ", GOSSIP_SENDER_MAIN, 1);
do
{
Field * fields = Bounties->Fetch();
std::string option;
QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
Field * names = name->Fetch();
option = names[0].GetString();
option +=" ";
option += fields[1].GetString();
option += "g";
pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
}while(Bounties->NextRow());
}
else
{
pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bounties: ", GOSSIP_SENDER_MAIN, 1);
Field * fields = Bounties->Fetch();
std::string option;
QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
Field * names = name->Fetch();
option = names[0].GetString();
option +=" ";
option += fields[1].GetString();
option += "g";
pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
}
pPlayer->PlayerTalkClass->SendGossipMenu(878, pCreature->GetGUID());
break;
}
case GOSSIP_ACTION_INFO_DEF+3:
{
pPlayer->PlayerTalkClass->SendCloseGossip();
break;
}
case GOSSIP_ACTION_INFO_DEF+4:
{
CharacterDatabase.PExecute("TRUNCATE TABLE bounties");
CharacterDatabase.PExecute("TRNUCATE TABLE bounty_hunter");
pPlayer->PlayerTalkClass->SendCloseGossip();
break;
}
case GOSSIP_ACTION_INFO_DEF+9:
   {
pPlayer->PlayerTalkClass->SendCloseGossip();
break;
}
case GOSSIP_ACTION_INFO_DEF+11:
{
QueryResult IsHunter = CharacterDatabase.PQuery("SELECT is_hunter FROM bounty_hunters WHERE guid='%u'", pPlayer->GetGUID());
if (!IsHunter)
return false;
if(IsHunter)
{
do
{
Field * fields = IsHunter->Fetch();
if (fields[0].GetUInt32() == 0)
{
alertServer(pPlayer->GetName(), 3);
flagPlayer(pPlayer->GetName());
}
else
{
pPlayer->GetSession()->SendNotification("You are already a bounty hunter!");
return false;
}
}while(IsHunter->NextRow());
}
break;
}
}
return true;
}

bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char * code)
{
pPlayer->PlayerTalkClass->ClearMenus();
if ( uiSender == GOSSIP_SENDER_MAIN )
{
if(islower(code[0]))
toupper(code[0]);

if(passChecks(pPlayer, code))
{
Player * pBounty = sObjectAccessor->FindPlayerByName(code);
switch (uiAction)
{
                        case GOSSIP_ACTION_INFO_DEF+5:
                        {
                                if(hasCurrency(pPlayer, BOUNTY_PRICE_1, SET_CURRENCY))
                                {
                                        #if SET_CURRENCY != 2
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','20', '1')", pBounty->GetGUID());
                                        #else
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','1', '1')", pBounty->GetGUID());
                                        #endif
CharacterDatabase.PExecute("INSERT INTO bounty_hunters VALUES('%u', '1', '0')", pPlayer->GetGUID());
                                        alertServer(code, 1);
                                        flagPlayer(code);
                                        pPlayer->PlayerTalkClass->SendCloseGossip();
                                }
                                break;
                        }
                                                       
                        case GOSSIP_ACTION_INFO_DEF+6:
                        {
                                if(hasCurrency(pPlayer, BOUNTY_PRICE_2, SET_CURRENCY))
                                {
                                        #if SET_CURRENCY != 2
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '40', '2')", pBounty->GetGUID());
                                        #else
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '3', '2')", pBounty->GetGUID());
                                        #endif
CharacterDatabase.PExecute("INSERT INTO bounty_hunters VALUES('%u', '1', '0')", pPlayer->GetGUID());
                                        alertServer(code, 1);
                                        flagPlayer(code);
                                        pPlayer->PlayerTalkClass->SendCloseGossip();
                                }
                                break;
                        }
                        case GOSSIP_ACTION_INFO_DEF+7:
                        {
                                if(hasCurrency(pPlayer, BOUNTY_PRICE_3, SET_CURRENCY))
                                {
                                        #if SET_CURRENCY != 2
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '100', '3')", pBounty->GetGUID());
                                        #else
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '5', '3')", pBounty->GetGUID());
                                        #endif
CharacterDatabase.PExecute("INSERT INTO bounty_hunters VALUES('%u', '1', '0')", pPlayer->GetGUID());
                                        alertServer(code, 1);
                                        flagPlayer(code);
                                        pPlayer->PlayerTalkClass->SendCloseGossip();
                                }
                                break;
                        }
                        case GOSSIP_ACTION_INFO_DEF+8:
                        {
                                if(hasCurrency(pPlayer, BOUNTY_PRICE_4, SET_CURRENCY))
                                {
                                        #if SET_CURRENCY != 2
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '200', '4')", pBounty->GetGUID());
                                        #else
                                        CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '10', '3')", pBounty->GetGUID());
                                        #endif
CharacterDatabase.PExecute("INSERT INTO bounty_hunters VALUES('%u', '1', '0')", pPlayer->GetGUID());
                                        alertServer(code, 1);
                                        flagPlayer(code);
                                        pPlayer->PlayerTalkClass->SendCloseGossip();
                                }
                                break;
}
}
}
else
{
pPlayer->PlayerTalkClass->SendCloseGossip();
}
}
return true;
}
};


class BountyKills : public PlayerScript
{
public:
BountyKills() : PlayerScript("BountyKills"){}

void OnPVPKill(Player * Killer, Player * Bounty)
{
if(Killer->GetGUID() == Bounty->GetGUID())
return;

QueryResult result = CharacterDatabase.PQuery("SELECT * FROM bounties WHERE guid='%u'", Bounty->GetGUID());
if(!result)
return;

QueryResult hunter = CharacterDatabase.PQuery("SELECT * FROM bounty_hunters WHERE guid='%u'", Killer->GetGUID());
if(!hunter)
return;

Field * fields = result->Fetch();
Field * kfield = hunter->Fetch();
switch(fields[2].GetUInt64())
{
case 1:
if(kfield[1].GetUInt64() == 1) // If Killer is the hunter
                #if SET_CURRENCY != 2
                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_1 * 10000));
                #else
                Killer->AddItem(TOKEN_ID, 1);
                #endif
break;
case 2:
if(kfield[1].GetUInt64() == 1) // If Killer is the hunter
                #if SET_CURRENCY != 2
                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_2 * 10000));
                #else
                Killer->AddItem(TOKEN_ID, 3);
                #endif
break;
case 3:
if(kfield[1].GetUInt64() == 1) // If Killer is the hunter
                #if SET_CURRENCY != 2
                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_3 * 10000));
                #else
                Killer->AddItem(TOKEN_ID, 5);
                #endif
break;
case 4:
if(kfield[1].GetUInt64() == 1) // If Killer is the hunter
                #if SET_CURRENCY != 2
                Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_4 * 10000));
                #else
                Killer->AddItem(TOKEN_ID, 10);
                #endif
break;
}
CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid='%u'", Bounty->GetGUID());
CharacterDatabase.PExecute("DELETE FROM bounty_hunters WHERE guid='%u'", Bounty->GetGUID());
CharacterDatabase.PExecute("DELETE FROM bounty_hunters WHERE guid='%u'", Killer->GetGUID());
alertServer(Bounty->GetName(), 2);
}


void OnLogin(Player * Player)
{
QueryResult hunter = CharacterDatabase.PQuery("SELECT * FROM bounty_hunters WHERE guid='%u'", Player->GetGUID());
if(!hunter)
return;

Field * fields = hunter->Fetch();
if(fields[1].GetUInt64() == 1)
{
Player->GetSession()->SendNotification("You're still a bounty hunter! Beaware!");
Player->SetPvP(true);
Player->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
}
else
{
}
}
};

void AddSC_BountyHunter()
{
new BountyHunter();
new BountyKills();
}