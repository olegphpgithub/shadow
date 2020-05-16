UPDATE netobjectstypes SET netobjectTypeName = 'Банкомат' where netobjectTypeId = 6;



CREATE OR REPLACE VIEW atmsview (
        atmId,
        officeId,
        atmAddress,
        atmName,
        atmModel,
        atmInventoryNumber,
        atmSerialNumber,
        atmComment
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
    FROM netobjects WHERE netObjectTypeId = 6 OR netObjectId = 0;



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
    
    SET original_query = (SELECT info FROM INFORMATION_SCHEMA.PROCESSLIST WHERE id = CONNECTION_ID() AND info LIKE 'INSERT INTO atmsview%');
    IF (original_query IS NOT NULL) THEN
        SET NEW.netObjectTypeId = 6;
    END IF;
    
END $$
DELIMITER ;

