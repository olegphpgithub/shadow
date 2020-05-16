alter table netobjectspasswordslogs
    ADD CONSTRAINT `netobjectspasswordslogs_ibfk_1` FOREIGN KEY (`netObjectPasswordId`)
    REFERENCES netobjectspasswords (netObjectPasswordId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
alter table netobjectspasswordslogs
    ADD CONSTRAINT `netobjectspasswordslogs_ibfk_2` FOREIGN KEY (`userId`)
    REFERENCES users (userId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
alter table netobjectspasswordslogs
    ADD CONSTRAINT `netobjectspasswordslogs_ibfk_3` FOREIGN KEY (`netObjectId`)
    REFERENCES netobjects (netObjectId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
    
alter table netobjectspasswords
    ADD CONSTRAINT `netobjectspasswords_ibfk_1` FOREIGN KEY (`userId`)
    REFERENCES users (userId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
alter table netobjectspasswords
    ADD CONSTRAINT `netobjectspasswords_ibfk_2` FOREIGN KEY (`netObjectId`)
    REFERENCES netobjects (netObjectId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
    
alter table netobjectscomponents
    ADD CONSTRAINT `netobjectscomponents_ibfk_1` FOREIGN KEY (`netObjectId`)
    REFERENCES netobjects (netObjectId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
alter table netobjectscomponents
    ADD CONSTRAINT `netobjectscomponents_ibfk_2` FOREIGN KEY (`netObjectComponentTypeId`)
    REFERENCES netobjectscomponentstypes (netObjectComponentTypeId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    

alter table netobjects
    ADD CONSTRAINT `netobjects_ibfk_1` FOREIGN KEY (`netObjectParentId`)
    REFERENCES netobjects (netObjectId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    

alter table netobjects
    ADD CONSTRAINT `netobjects_ibfk_2` FOREIGN KEY (`officeId`)
    REFERENCES offices (officeId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    

alter table netobjects
    ADD CONSTRAINT `netobjects_ibfk_3` FOREIGN KEY (`userId`)
    REFERENCES users (userId)
    ON DELETE RESTRICT
    ON UPDATE RESTRICT
    
    
DROP TRIGGER IF EXISTS `t_bu_netobjectscomponents`;
DELIMITER $$
CREATE TRIGGER `t_bu_netobjectscomponents` BEFORE UPDATE ON `netobjectscomponents`
FOR EACH ROW
BEGIN
    
    DECLARE original_query VARCHAR(2048);
    
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID());
    
    INSERT INTO debug VALUES(original_query);
    
    
END $$
DELIMITER ;








CREATE TABLE `netobjects` (
`netObjectId` int(11) NOT NULL
AUTO_INCREMENT,
`netobjectTypeId` int(11) NOT
NULL DEFAULT '0',
`netObjectParentId` int(11)
NOT NULL DEFAULT '0',
`officeId` int(11) NOT NULL
DEFAULT '0', `userId`
int(11) NOT NULL DEFAULT '0',
`netObjectAddress` tinytext,
`netObjectName` tinytext,
`netObjectModel` tinytext,
`netObjectInventoryNumber`
tinytext,
`netObjectSerialNumber`
tinytext, `netObjectComment`
longtext, PRIMARY KEY
(`netObjectId`) )
ENGINE=InnoDB
AUTO_INCREMENT=700 DEFAULT
CHARSET=utf8




CREATE TABLE
`netobjectspasswords` (
`netObjectPasswordId` int(11)
NOT NULL AUTO_INCREMENT,
`userId` int(11) NOT NULL
DEFAULT '0', `netObjectId`
int(11) NOT NULL DEFAULT '0',
`netObjectLogin` tinytext,
`netObjectPassword` tinytext,
`netObjectDateTime` timestamp
NOT NULL DEFAULT
CURRENT_TIMESTAMP ON UPDATE
CURRENT_TIMESTAMP,
`netObjectPasswordComment`
tinytext, PRIMARY KEY
(`netObjectPasswordId`), KEY
`netobjectspasswords_ibfk_1`
(`userId`), KEY
`netobjectspasswords_ibfk_2`
(`netObjectId`), CONSTRAINT
`netobjectspasswords_ibfk_1`
FOREIGN KEY (`userId`)
REFERENCES `users`
(`userId`), CONSTRAINT
`netobjectspasswords_ibfk_2`
FOREIGN KEY (`netObjectId`)
REFERENCES `netobjects`
(`netObjectId`) )
ENGINE=InnoDB
AUTO_INCREMENT=734 DEFAULT
CHARSET=utf8
    
