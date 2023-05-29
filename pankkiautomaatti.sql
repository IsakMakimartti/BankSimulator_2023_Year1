-- MySQL dump 10.13  Distrib 8.0.32, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: pankkiautomaatti
-- ------------------------------------------------------
-- Server version	8.0.31

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `idAsiakas` int NOT NULL AUTO_INCREMENT,
  `Etunimi` varchar(45) DEFAULT NULL,
  `Sukunimi` varchar(45) DEFAULT NULL,
  `Osoite` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idAsiakas`),
  UNIQUE KEY `idAsiakas_UNIQUE` (`idAsiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'Tom','Brady','Londonstreet 12D'),(2,'Sam','Brady','Londonstreet 12D'),(3,'George','Orwell','Wales Drive 12');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `asiakas_tili`
--

DROP TABLE IF EXISTS `asiakas_tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas_tili` (
  `idAsiakas` int NOT NULL,
  `idTili` int NOT NULL,
  `Omistaja` tinyint NOT NULL,
  `PaivaNostoraja` int DEFAULT NULL,
  PRIMARY KEY (`idAsiakas`,`idTili`),
  KEY `Tili1_idx` (`idTili`),
  KEY `Asiakas_idx` (`idAsiakas`),
  CONSTRAINT `Asiakas` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`),
  CONSTRAINT `Tili1` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas_tili`
--

LOCK TABLES `asiakas_tili` WRITE;
/*!40000 ALTER TABLE `asiakas_tili` DISABLE KEYS */;
INSERT INTO `asiakas_tili` VALUES (1,1,0,100),(2,1,1,NULL),(3,7,1,NULL);
/*!40000 ALTER TABLE `asiakas_tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `idKortti` varchar(255) NOT NULL,
  `pinkoodi` varchar(255) NOT NULL,
  `idAsiakas` int NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`idKortti`,`idTili`),
  UNIQUE KEY `idKortti_UNIQUE` (`idKortti`),
  KEY `Asiakas1_idx` (`idAsiakas`),
  KEY `Tili2_idx` (`idTili`),
  CONSTRAINT `Asiakas1` FOREIGN KEY (`idAsiakas`) REFERENCES `asiakas` (`idAsiakas`),
  CONSTRAINT `Tili2` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES ('05009b4410','$2a$10$7s5VPQcXcNaI0oOq8rb4F.nhWY2U70qxzV3sgNZB5GRFaw1mjN5lm',1,1),('05009b4422','$2a$10$K6xX.xlX3Uj.1rs2rc7zjO0DVLmB8VnwjPaIhcpc4hL0gSOd7SH/q',2,1),('06000626f5','$2a$10$YKKsljGW7FbgaifjXKx9mO5fCG39/LMNh2eNqev3fVoD.BdSvsCsC',3,7);
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nostohistoria`
--

DROP TABLE IF EXISTS `nostohistoria`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `nostohistoria` (
  `idNostoHistoria` int NOT NULL AUTO_INCREMENT,
  `DATETIME` datetime NOT NULL,
  `MAARA` float NOT NULL,
  `Debit` tinyint NOT NULL,
  `idTili` int NOT NULL,
  PRIMARY KEY (`idNostoHistoria`),
  KEY `Tili3_idx` (`idTili`),
  CONSTRAINT `Tili3` FOREIGN KEY (`idTili`) REFERENCES `tili` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nostohistoria`
--

LOCK TABLES `nostohistoria` WRITE;
/*!40000 ALTER TABLE `nostohistoria` DISABLE KEYS */;
INSERT INTO `nostohistoria` VALUES (1,'2021-10-22 13:54:19',-400,1,1);
/*!40000 ALTER TABLE `nostohistoria` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `idTili` int NOT NULL AUTO_INCREMENT,
  `DebitTilinumero` varchar(45) NOT NULL,
  `CreditTilinumero` varchar(45) DEFAULT NULL,
  `DebitSaldo` float NOT NULL,
  `CreditSaldo` float DEFAULT NULL,
  `Luottoraja` float DEFAULT NULL,
  PRIMARY KEY (`idTili`),
  UNIQUE KEY `idTili_UNIQUE` (`idTili`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (1,'FI0580001470824575',NULL,200,NULL,NULL),(7,'FI0580001470824580','FI0580001470829000',879.9,21.23,2000),(8,'FI0580001470824580','FI0580001470829000',879.8,21,2000);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-04-12 12:41:19
