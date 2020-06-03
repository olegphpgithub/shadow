
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


CREATE TABLE `offices` (
    `officeId` int(11) NOT NULL AUTO_INCREMENT,
    `officeIdentifier` int(11) DEFAULT NULL,
    `officeName` tinytext,
    `officeAddress` tinytext,
    PRIMARY KEY(`officeId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;


CREATE TABLE `users` (
    `userId` int(11) NOT NULL AUTO_INCREMENT,
    `officeId` int(11) NOT NULL DEFAULT '0',
    `userSurnameNamePatronymic` tinytext,
    `userBirthday` date DEFAULT NULL,
    `userPosition` tinytext,
    `userTelephoneMobile` tinytext,
    `userEMail` tinytext,
    PRIMARY KEY(`userId`),
    CONSTRAINT `users_ibfk_1` FOREIGN KEY (`officeId`) REFERENCES `offices` (`officeId`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

insert into users values(0, '', NULL, '', '', '');

update `users` set `userId` = 0;


alter table networkobjectpasswords modify column userId int(11) NOT NULL;
alter table `users` add `officeId` int(11) after `userId` NOT NULL DEFAULT '0';
alter table `networkobjects` add `userId` int(11) after `netWorkObjectTypeId` NOT NULL DEFAULT '0';

alter table networkobjectpasswords
    ADD CONSTRAINT `networkobjectpasswords_ibfk_2` FOREIGN KEY (`userId`)
    REFERENCES `users`(`userId`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
;

alter table users
    ADD CONSTRAINT `users_ibfk_1` FOREIGN KEY (`officeId`)
    REFERENCES `offices`(`officeId`)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
;


alter table networkobjects
    ADD CONSTRAINT `networkobjects_ibfk_1` FOREIGN KEY (`userId`)
    REFERENCES `users`(`userId`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
;

insert into offices values(NULL, 0, '', '');
update offices set officeId = 0;

CREATE  VIEW
`usersview` AS select
`users`.`userId` AS
`userId`,`users`.`officeId` AS
`officeId`,(case when
(concat(`users`.`userSurnameNamePatronymic`,_utf8'
(',`users`.`userPosition`,_utf8')')
= _utf8' ()') then _utf8''
else
concat(`users`.`userSurnameNamePatronymic`,_utf8'
(',`users`.`userPosition`,_utf8')')
end) AS
`userSurnameNamePatronymicPosition`
from `users` order by (case
when
(concat(`users`.`userSurnameNamePatronymic`,_utf8'
(',`users`.`userPosition`,_utf8')')
= _utf8' ()') then _utf8''
else
concat(`users`.`userSurnameNamePatronymic`,_utf8'
(',`users`.`userPosition`,_utf8')')
end)