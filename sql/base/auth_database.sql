-- MySQL dump 10.13  Distrib 5.5.19, for Win64 (x86)
--
-- Host: localhost    Database: auth
-- ------------------------------------------------------
-- Server version	5.5.19

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

# Dumping structure for table auth.account
DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(32) NOT NULL DEFAULT '',
  `sha_pass_hash` varchar(40) NOT NULL DEFAULT '',
  `sessionkey` longtext,
  `v` longtext,
  `s` longtext,
  `email` text,
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_ip` varchar(30) NOT NULL DEFAULT '127.0.0.1',
  `failed_logins` int(11) unsigned NOT NULL DEFAULT '0',
  `locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `online` tinyint(4) NOT NULL DEFAULT '0',
  `expansion` tinyint(3) unsigned NOT NULL DEFAULT '2',
  `mutetime` bigint(40) NOT NULL DEFAULT '0',
  `locale` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `os` varchar(4) NOT NULL DEFAULT '',
  `recruiter` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`username`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Account System';
/*!40101 SET character_set_client = @saved_cs_client */;

# Dumping data for table auth.account: 0 rows
DELETE FROM `account`;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
/*!40000 ALTER TABLE `account` ENABLE KEYS */;

--
-- Table structure for table `account_access`
--

DROP TABLE IF EXISTS `account_access`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account_access` (
  `id` int(11) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_access`
--

LOCK TABLES `account_access` WRITE;
/*!40000 ALTER TABLE `account_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_access` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_banned`
--

# Dumping structure for table auth.account_access
DROP TABLE IF EXISTS `account_access`;
CREATE TABLE IF NOT EXISTS `account_access` (
  `id` int(11) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

# Dumping data for table auth.account_access: 0 rows
DELETE FROM `account_access`;
/*!40000 ALTER TABLE `account_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_access` ENABLE KEYS */;


# Dumping structure for table auth.account_banned
DROP TABLE IF EXISTS `account_banned`;
<<<<<<< HEAD
CREATE TABLE IF NOT EXISTS `account_banned` (
=======
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account_banned` (
>>>>>>> upstream/master
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `bandate` bigint(40) NOT NULL DEFAULT '0',
  `unbandate` bigint(40) NOT NULL DEFAULT '0',
  `bannedby` varchar(50) NOT NULL,
  `banreason` varchar(255) NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`bandate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Ban List';

# Dumping data for table auth.account_banned: 0 rows
DELETE FROM `account_banned`;
/*!40000 ALTER TABLE `account_banned` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_banned` ENABLE KEYS */;


# Dumping structure for table auth.account_premium
DROP TABLE IF EXISTS `account_premium`;
CREATE TABLE IF NOT EXISTS `account_premium` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `setdate` bigint(40) NOT NULL DEFAULT '0',
  `unsetdate` bigint(40) NOT NULL DEFAULT '0',
  `premium_type` tinyint(4) unsigned NOT NULL DEFAULT '1',
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`setdate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Premium Accounts';

# Dumping data for table auth.account_premium: 0 rows
DELETE FROM `account_premium`;
/*!40000 ALTER TABLE `account_premium` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_premium` ENABLE KEYS */;


# Dumping structure for table auth.ip_banned
DROP TABLE IF EXISTS `ip_banned`;
<<<<<<< HEAD
CREATE TABLE IF NOT EXISTS `ip_banned` (
=======
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ip_banned` (
>>>>>>> upstream/master
  `ip` varchar(32) NOT NULL DEFAULT '127.0.0.1',
  `bandate` bigint(40) NOT NULL,
  `unbandate` bigint(40) NOT NULL,
  `bannedby` varchar(50) NOT NULL DEFAULT '[Console]',
  `banreason` varchar(255) NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Banned IPs';

# Dumping data for table auth.ip_banned: 0 rows
DELETE FROM `ip_banned`;
/*!40000 ALTER TABLE `ip_banned` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip_banned` ENABLE KEYS */;


# Dumping structure for table auth.logs
DROP TABLE IF EXISTS `logs`;
CREATE TABLE IF NOT EXISTS `logs` (
  `time` int(14) NOT NULL,
  `realm` int(4) NOT NULL,
  `type` int(4) NOT NULL,
  `string` text
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Dumping data for table auth.logs: 0 rows
DELETE FROM `logs`;
/*!40000 ALTER TABLE `logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `logs` ENABLE KEYS */;


# Dumping structure for table auth.realmcharacters
DROP TABLE IF EXISTS `realmcharacters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `realmcharacters` (
  `realmid` int(11) unsigned NOT NULL DEFAULT '0',
  `acctid` bigint(20) unsigned NOT NULL,
  `numchars` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmid`,`acctid`),
  KEY `acctid` (`acctid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm Character Tracker';

# Dumping data for table auth.realmcharacters: 0 rows
DELETE FROM `realmcharacters`;
/*!40000 ALTER TABLE `realmcharacters` DISABLE KEYS */;
/*!40000 ALTER TABLE `realmcharacters` ENABLE KEYS */;


# Dumping structure for table auth.realmlist
DROP TABLE IF EXISTS `realmlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `realmlist` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT '',
  `address` varchar(32) NOT NULL DEFAULT '127.0.0.1',
  `port` int(11) NOT NULL DEFAULT '8085',
  `icon` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `color` tinyint(3) unsigned NOT NULL DEFAULT '2',
  `timezone` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `allowedSecurityLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `population` float unsigned NOT NULL DEFAULT '0',
  `gamebuild` int(11) unsigned NOT NULL DEFAULT '12340',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_name` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm System';

# Dumping data for table auth.realmlist: 1 rows
DELETE FROM `realmlist`;
/*!40000 ALTER TABLE `realmlist` DISABLE KEYS */;
INSERT INTO `realmlist` VALUES (1,'Trinity','127.0.0.1',8085,1,0,1,0,0,12340);
/*!40000 ALTER TABLE `realmlist` ENABLE KEYS */;


# Dumping structure for table auth.uptime
DROP TABLE IF EXISTS `uptime`;
CREATE TABLE IF NOT EXISTS `uptime` (
  `realmid` int(11) unsigned NOT NULL,
  `starttime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `startstring` varchar(64) NOT NULL DEFAULT '',
  `uptime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `maxplayers` smallint(5) unsigned NOT NULL DEFAULT '0',
  `revision` varchar(255) NOT NULL DEFAULT 'Trinitycore',
  PRIMARY KEY (`realmid`,`starttime`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Uptime system';

# Dumping data for table auth.uptime: 0 rows
DELETE FROM `uptime`;
/*!40000 ALTER TABLE `uptime` DISABLE KEYS */;
/*!40000 ALTER TABLE `uptime` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2012-02-19 13:18:35
