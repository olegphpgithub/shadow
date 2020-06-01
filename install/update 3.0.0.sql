
CREATE TABLE `_struct` (
`_struct` blob ) ENGINE=InnoDB
DEFAULT CHARSET=utf8


DROP TABLE IF EXISTS `networkobjecttypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `networkobjecttypes` (
  `netWorkObjectTypeId` int(11) NOT NULL AUTO_INCREMENT,
  `netWorkObjectTypeName` tinytext,
  PRIMARY KEY (`netWorkObjectTypeId`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


DROP TABLE IF EXISTS `networkobjects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `networkobjects` (
  `netWorkObjectId` int(11) NOT NULL AUTO_INCREMENT,
  `netWorkObjectParentId` int(11) NOT NULL DEFAULT '0',
  `netWorkObjectTypeId` int(11) NOT NULL DEFAULT '0',
  `netWorkObjectName` tinytext,
  `netWorkObjectAddress` tinytext,
  `netWorkObjectTeamViewer` tinytext,
  `netWorkObjectOS` tinytext,
  `netWorkObjectComment` text,
  PRIMARY KEY (`netWorkObjectId`),
  KEY `netWorkObjectParentId` (`netWorkObjectParentId`),
  KEY `netWorkObjectTypeId` (`netWorkObjectTypeId`),
  CONSTRAINT `networkobjects_ibfk_2` FOREIGN KEY (`netWorkObjectTypeId`) REFERENCES `networkobjecttypes` (`netWorkObjectTypeId`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


INSERT INTO networkobjects VALUES
(
    NULL,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL
)
;


UPDATE networkobjects SET netWorkObjectId = 0;


ALTER TABLE networkobjects MODIFY COLUMN `netWorkObjectParentId` int(11) NOT NULL DEFAULT 0;

INSERT INTO networkobjects VALUES
(
    NULL,
    NULL,
    0,
    "Compass Win 10 real PC",
    "compass.allowed.org:33892",
    "Windows",
    ""
)
;


CREATE TABLE networkobjectpasswords
(
    netWorkObjectPasswordId int(11) NOT NULL AUTO_INCREMENT,
    netWorkObjectId int(11) NOT NULL DEFAULT 0,
    netWorkObjectPasswordLogin tinytext,
    netWorkObjectPasswordPassword tinytext,
    netWorkObjectPasswordDateTime timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    netWorkObjectPasswordComment tinytext,
    PRIMARY KEY (`netWorkObjectPasswordId`),
    FOREIGN KEY (netWorkObjectId) REFERENCES networkobjects(netWorkObjectId) ON UPDATE CASCADE ON DELETE RESTRICT
)
;








