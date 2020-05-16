

CREATE TABLE netobjectstypes (
    netobjectTypeId INTEGER PRIMARY KEY auto_increment,
    netobjectTypeName TINYTEXT NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;



INSERT INTO netobjectstypes VALUES(1, 'Рабочая станция');
INSERT INTO netobjectstypes VALUES(2, 'Принтер');
INSERT INTO netobjectstypes VALUES(3, 'Сервер');
INSERT INTO netobjectstypes VALUES(4, 'Виртуальный сервер');
INSERT INTO netobjectstypes VALUES(5, 'Маршрутизатор');
INSERT INTO netobjectstypes VALUES(6, 'Прочее оборудование');



CREATE TABLE netobjects (
    netObjectId INTEGER primary key auto_increment,
    netobjectTypeId INTEGER NOT NULL DEFAULT 0 REFERENCES netobjectstypes(netobjectTypeId) ON UPDATE CASCADE ON DELETE RESTRICT,
    netObjectParentId INTEGER NOT NULL DEFAULT 0 REFERENCES netobjects(netObjectId) ON UPDATE CASCADE ON DELETE RESTRICT,
    officeId INTEGER NOT NULL DEFAULT 0 REFERENCES offices(officeId) ON UPDATE CASCADE ON DELETE RESTRICT,
    userId INTEGER NOT NULL DEFAULT 0 REFERENCES users(userId) ON UPDATE CASCADE ON DELETE RESTRICT,
    netObjectAddress TINYTEXT,
    netObjectName TINYTEXT,
    netObjectModel TINYTEXT,
    netObjectInventoryNumber TINYTEXT,
    netObjectSerialNumber TINYTEXT,
    netObjectComment TEXT
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE OR REPLACE VIEW netobjectsboxview AS
    SELECT netObjectId, officeId, userId, CASE WHEN CONCAT(netObjectAddress, ' (', netObjectName, ')') = ' ()' THEN '' ELSE CONCAT(netObjectAddress, ' (', netObjectName, ')') END AS netobjectComplexName
        FROM netobjects ORDER BY netObjectComplexName;
        
CREATE OR REPLACE VIEW serversboxview (serverId, officeId, userId, serverComplexName) AS
    SELECT netObjectId, officeId, userId, CASE WHEN CONCAT(netObjectAddress, ' (', netObjectName, ')') = ' ()' THEN '' ELSE CONCAT(netObjectAddress, ' (', netObjectName, ')') END AS serverComplexName
        FROM netobjects ORDER BY serverComplexName;
        
CREATE OR REPLACE VIEW virtualserversboxview (virtualServerId, officeId, userId, virtualServerComplexName) AS
    SELECT netObjectId, officeId, userId, CASE WHEN CONCAT(netObjectAddress, ' (', netObjectName, ')') = ' ()' THEN '' ELSE CONCAT(netObjectAddress, ' (', netObjectName, ')') END AS virtualServerComplexName
        FROM netobjects ORDER BY virtualServerComplexName;

CREATE VIEW workstationsboxview (workstationId, officeId, userId, workstationComplexName) AS
    SELECT netObjectId, officeId, userId, CASE WHEN CONCAT(netObjectAddress, ' (', netObjectName, ')') = ' ()' THEN '' ELSE CONCAT(netObjectAddress, ' (', netObjectName, ')') END AS workstationComplexName
        FROM netobjects ORDER BY workstationComplexName;
        
CREATE VIEW routersboxview (routerId, officeId, userId, routerComplexName) AS
    SELECT netObjectId, officeId, userId, CASE WHEN CONCAT(netObjectAddress, ' (', netObjectName, ')') = ' ()' THEN '' ELSE CONCAT(netObjectAddress, ' (', netObjectName, ')') END AS routerComplexName
        FROM netobjects ORDER BY routerComplexName;


CREATE TABLE `netobjectspasswords` (
  `netObjectPasswordId` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `userId` INTEGER NOT NULL DEFAULT 0 REFERENCES users(userId) ON UPDATE CASCADE ON DELETE RESTRICT,
  `netObjectId` INTEGER NOT NULL DEFAULT 0 REFERENCES netobjects(netObjectId) ON UPDATE CASCADE ON DELETE RESTRICT,
  `netObjectLogin` tinytext,
  `netObjectPassword` tinytext,
  `netObjectDateTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `netobjectspasswordslogs` (
  `netObjectPasswordLogId` INTEGER PRIMARY KEY AUTO_INCREMENT,
  `netObjectPasswordId` INTEGER NOT NULL DEFAULT 0 REFERENCES netobjectspasswords(netObjectPasswordId) ON UPDATE CASCADE ON DELETE RESTRICT,
  `userId` INTEGER NOT NULL DEFAULT 0 REFERENCES users(userId) ON UPDATE CASCADE ON DELETE RESTRICT,
  `netObjectId` INTEGER NOT NULL DEFAULT 0 REFERENCES netobjects(netObjectId) ON UPDATE CASCADE ON DELETE RESTRICT,
  `netObjectLoginLog` tinytext,
  `netObjectPasswordLog` tinytext,
  `netObjectDateTimeLog` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;



CREATE OR REPLACE VIEW workstationsview (
        workstationId,
        officeId,
        userId,
        workstationAddress,
        workstationName,
        workstationModel,
        workstationInventoryNumber,
        workstationSerialNumber,
        workstationComment
    ) AS
    SELECT
        netObjectId,
        officeId,
        userId,
        netObjectAddress,
        netObjectName,
        netObjectModel,
        netObjectInventoryNumber,
        netObjectSerialNumber,
        netObjectComment
    FROM netobjects WHERE netObjectTypeId = 1 OR netObjectId = 0;




CREATE OR REPLACE VIEW printersview (
        printerId,
        officeId,
        workstationId,
        printerAddress,
        printerName,
        printerModel,
        printerInventoryNumber,
        printerSerialNumber,
        printerComment
    ) AS
    SELECT
        netObjectId,
        officeId,
        netObjectParentId,
        netObjectAddress,
        netObjectName,
        netObjectModel,
        netObjectInventoryNumber,
        netObjectSerialNumber,
        netObjectComment
    FROM netobjects WHERE netObjectTypeId = 2 OR netObjectId = 0;

CREATE OR REPLACE VIEW serversview (
        serverId,
        officeId,
        serverAddress,
        serverName,
        serverModel,
        serverInventoryNumber,
        serverSerialNumber,
        serverComment
    ) AS
    SELECT
        netObjectId,
        officeId,
        netObjectAddress,
        netObjectName,
        netObjectModel,
        netObjectInventoryNumber,
        netObjectSerialNumber,
        netObjectComment
    FROM netobjects WHERE netObjectTypeId = 3 OR netObjectId = 0;
    
    
CREATE OR REPLACE VIEW virtualserversview (
        virtualServerId,
        officeId,
        serverId,
        virtualserverAddress,
        virtualserverName,
        virtualserverModel,
        virtualserverInventoryNumber,
        virtualserverSerialNumber,
        virtualserverComment
    ) AS
    SELECT
        netObjectId,
        officeId,
        netObjectParentId,
        netObjectAddress,
        netObjectName,
        netObjectModel,
        netObjectInventoryNumber,
        netObjectSerialNumber,
        netObjectComment
    FROM netobjects WHERE netObjectTypeId = 4 OR netObjectId = 0;


CREATE OR REPLACE VIEW routersview (
        routerId,
        officeId,
        routerAddress,
        routerName,
        routerModel,
        routerInventoryNumber,
        routerSerialNumber,
        routerComment
    ) AS
    SELECT
        netObjectId,
        officeId,
        netObjectAddress,
        netObjectName,
        netObjectModel,
        netObjectInventoryNumber,
        netObjectSerialNumber,
        netObjectComment
    FROM netobjects WHERE netObjectTypeId = 5 OR netObjectId = 0;



INSERT INTO netobjects VALUES(0, '', 0, 0, 0, '', '', '', '', '', '');
UPDATE netobjects SET netObjectId = 0;



INSERT INTO netobjects
    SELECT computerId,
        1,
        0,
        officeId,
        userId,
        computerNetWorkAddress,
        computerNetWorkName,
        computerModel,
        computerInventoryNumber,
        computerSerialNumber,
        computerComment
    FROM computers WHERE computerId > 0;


INSERT INTO netobjects
    SELECT NULL,
        2,
        computerId,
        officeId,
        0,
        printerNetWorkAddress,
        printerNetWorkName,
        printerModel,
        printerInventoryNumber,
        printerSerialNumber,
        printerComment
    FROM printers WHERE printerId > 0;


UPDATE netobjects SET netObjectTypeId = 3 WHERE netobjects.netObjectName LIKE 'S%';



INSERT INTO netobjectspasswords VALUES(0, 0, 0, '', '', '0000-00-00 00:00:00');
UPDATE netobjectspasswords SET netObjectPasswordId = 0, netObjectDateTime = '0000-00-00 00:00:00';

INSERT INTO netobjectspasswords
    SELECT computerPasswordId,
        userId,
        computerId,
        computerPasswordLogin,
        computerPasswordPassword,
        computerPasswordDateTime
    FROM computerspasswords WHERE computerPasswordId > 0;


CREATE OR REPLACE VIEW workstationspasswordsview (
        netObjectPasswordId,
        userId,
        workstationId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    ) AS
    SELECT
        netObjectPasswordId,
        userId,
        netObjectId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    FROM netobjectspasswords;

CREATE OR REPLACE VIEW serverspasswordsview (
        netObjectPasswordId,
        userId,
        serverId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    ) AS
    SELECT
        netObjectPasswordId,
        userId,
        netObjectId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    FROM netobjectspasswords;
    
CREATE OR REPLACE VIEW virtualserverspasswordsview (
        netObjectPasswordId,
        userId,
        virtualServerId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    ) AS
    SELECT
        netObjectPasswordId,
        userId,
        netObjectId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    FROM netobjectspasswords;


CREATE OR REPLACE VIEW routerspasswordsview (
        netObjectPasswordId,
        userId,
        routerId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    ) AS
    SELECT
        netObjectPasswordId,
        userId,
        netObjectId,
        netObjectLogin,
        netObjectPassword,
        netObjectDateTime,
        netObjectPasswordComment
    FROM netobjectspasswords;
    

INSERT INTO netobjectspasswordslogs VALUES(0, 0, 0, 0, '', '', '0000-00-00 00:00:00');
UPDATE netobjectspasswordslogs SET netObjectPasswordLogId = 0, netObjectDateTimeLog = '0000-00-00 00:00:00';

INSERT INTO netobjectspasswordslogs
    SELECT computerPasswordLogId,
        computerPasswordId,
        userId,
        computerId,
        computerPasswordLogLogin,
        computerPasswordLogpassword,
        computerPasswordLogDateTime
    FROM computerspasswordslogs WHERE computerPasswordLogId > 0;



DROP TRIGGER IF EXISTS `t_bi_netobjects`;
DELIMITER $$
CREATE TRIGGER `t_bi_netobjects` BEFORE INSERT ON `netobjects`
FOR EACH ROW
BEGIN
    
    DECLARE original_query VARCHAR(2048);
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID() AND info LIKE 'INSERT INTO workstationsview%');
    IF (original_query IS NOT NULL) THEN
        SET NEW.netObjectTypeId = 1;
    END IF;
    
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID() AND info LIKE 'INSERT INTO printersview%');
    IF (original_query IS NOT NULL) THEN
        SET NEW.netObjectTypeId = 2;
    END IF;
    
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID() AND info LIKE 'INSERT INTO serversview%');
    IF (original_query IS NOT NULL) THEN
        SET NEW.netObjectTypeId = 3;
    END IF;
    
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID() AND info LIKE 'INSERT INTO virtualserversview%');
    IF (original_query IS NOT NULL) THEN
        SET NEW.netObjectTypeId = 4;
    END IF;
    
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID() AND info LIKE 'INSERT INTO routersview%');
    IF (original_query IS NOT NULL) THEN
        SET NEW.netObjectTypeId = 5;
    END IF;
    
END $$
DELIMITER ;




CREATE TABLE netobjectscomponentstypes (
    netObjectComponentTypeId INTEGER primary key auto_increment,
    netObjectComponentTypeName tinytext,
    netObjectComponentTypeNamePlural tinytext,
    netObjectComponentTypeCategory tinytext
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


INSERT INTO netobjectscomponentstypes VALUES(0, '', '', '');
UPDATE netobjectscomponentstypes SET netObjectComponentTypeId = 0;


INSERT INTO netobjectscomponentstypes
    SELECT computerComponentTypeId,
        computerComponentTypeName,
        computerComponentTypeNamePlural,
        computerComponentTypeCategory
    FROM computerscomponentstypes WHERE computerComponentTypeId > 0;



CREATE TABLE netobjectscomponents(
    netObjectComponentId INTEGER primary key auto_increment,
    netObjectId INTEGER NOT NULL REFERENCES netobjects(netObjectId) ON UPDATE CASCADE ON DELETE RESTRICT,
    netObjectComponentTypeId INTEGER NOT NULL REFERENCES netobjectscomponentstypes(netObjectComponentTypeId) ON UPDATE CASCADE ON DELETE RESTRICT,
    netObjectComponentVendor tinytext,
    netObjectComponentModel tinytext,
    netObjectComponentSerialNumber tinytext,
    netObjectComponentComment text
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


INSERT INTO netobjectscomponents VALUES(0, 0, 0, '', '', '', '');
UPDATE netobjectscomponents SET netObjectComponentId = 0;


INSERT INTO netobjectscomponents
    SELECT computerComponentId,
        computerId,
        computerComponentTypeId,
        computerComponentVendor,
        computerComponentModel,
        computerComponentSerialNumber,
        computerComponentComment
    FROM computerscomponents WHERE computerComponentId > 0;
    
CREATE OR REPLACE VIEW workstationscomponentsview (
        netObjectComponentId,
        workstationId,
        netObjectComponentTypeId,
        netObjectComponentVendor,
        netObjectComponentModel,
        netObjectComponentSerialNumber,
        netObjectComponentComment
    ) AS
    SELECT
        netObjectComponentId,
        netObjectId,
        netObjectComponentTypeId,
        netObjectComponentVendor,
        netObjectComponentModel,
        netObjectComponentSerialNumber,
        netObjectComponentComment
    FROM netobjectscomponents;


DELIMITER $$
CREATE TRIGGER t_ai_netobjectspasswords AFTER INSERT ON netobjectspasswords FOR EACH ROW
    BEGIN
        INSERT INTO netobjectspasswordslogs VALUES (
            NULL,
            NEW.netObjectPasswordId,
            NEW.userId,
            NEW.netObjectId,
            NEW.netObjectLogin,
            NEW.netObjectPassword,
            NEW.netObjectDateTime
        );
END $$

CREATE TRIGGER t_au_netobjectspasswords AFTER UPDATE ON netobjectspasswords FOR EACH ROW
    BEGIN
        INSERT INTO netobjectspasswordslogs VALUES (
            NULL,
            NEW.netObjectPasswordId,
            NEW.userId,
            NEW.netObjectId,
            NEW.netObjectLogin,
            NEW.netObjectPassword,
            NEW.netObjectDateTime
        );
END $$

DELIMITER ;

