ALTER TABLE computers ADD COLUMN computerModel TINYTEXT;
ALTER TABLE computers ADD COLUMN computerComment TINYTEXT;
ALTER TABLE computers ADD COLUMN computerInventoryNumber TINYTEXT AFTER computerModel;
ALTER TABLE computers ADD COLUMN computerInventoryNumber TINYTEXT AFTER computerModel;


ALTER TABLE printers ADD COLUMN printerModel TINYTEXT;
ALTER TABLE printers ADD COLUMN printerComment TINYTEXT;


ALTER TABLE printers modify printerComment TINYTEXT;


CREATE VIEW usersview AS
    SELECT userId, officeId, CASE WHEN CONCAT(userSurnameNamePatronymic, ' (', userPosition, ')') = ' ()' THEN '' ELSE CONCAT(userSurnameNamePatronymic, ' (', userPosition, ')') END AS userSurnameNamePatronymicPosition
        FROM users ORDER BY userSurnameNamePatronymicPosition;

CREATE TABLE computerscomponents(
    computerComponentId INTEGER primary key auto_increment,
    computerId INTEGER NOT NULL REFERENCES computers(computerId) ON UPDATE CASCADE ON DELETE RESTRICT,
    computerComponentTypeId INTEGER NOT NULL REFERENCES computerscomponentstypes(computerComponentTypeId) ON UPDATE CASCADE ON DELETE RESTRICT,
    computerComponentVendor tinytext,
    computerComponentModel tinytext,
    computerComponentSerialNumber tinytext,
    computerComponentComment text
) engine=innodb;


CREATE VIEW computersview AS
    SELECT computerId, officeId, userId, CASE WHEN CONCAT(computerNetWorkAddress, ' (', computerNetWorkName, ')') = ' ()' THEN '' ELSE CONCAT(computerNetWorkAddress, ' (', computerNetWorkName, ')') END AS computerNetWorkAddressName
        FROM computers ORDER BY computerNetWorkAddressName;
        
CREATE TABLE computerscomponentstypes (
    computerComponentTypeId INTEGER primary key auto_increment,
    computerComponentTypeName tinytext,
    computerComponentTypeNamePlural tinytext
) engine=innodb;

INSERT INTO computerscomponentstypes VALUES(0, "", "");
INSERT INTO computerscomponentstypes VALUES(1, "������������ �������", "������������ �������");
INSERT INTO computerscomponentstypes VALUES(2, "����������", "����������");
INSERT INTO computerscomponentstypes VALUES(3, "�������", "��������");
INSERT INTO computerscomponentstypes VALUES(4, "��������� �����", "��������� �����");
INSERT INTO computerscomponentstypes VALUES(5, "���������", "����������");
INSERT INTO computerscomponentstypes VALUES(6, "��������� ������", "��������� ������");
INSERT INTO computerscomponentstypes VALUES(7, "������-����������", "������-����������");
INSERT INTO computerscomponentstypes VALUES(8, "�������� ����������", "�������� ����������");
INSERT INTO computerscomponentstypes VALUES(9, "���������� ��������", "���������� ��������");
INSERT INTO computerscomponentstypes VALUES(10, "����������", "����������");
INSERT INTO computerscomponentstypes VALUES(11, "�����������", "������������");
INSERT INTO computerscomponentstypes VALUES(12, "������� �������", "������� ��������");

ALTER TABLE computerscomponentstypes ADD COLUMN computerComponentTypeCategory tinytext;


CREATE TABLE tellers(
    tellerId INTEGER primary key auto_increment,
    officeId INTEGER NOT NULL REFERENCES offices(officeId) ON UPDATE CASCADE ON DELETE RESTRICT,
    tellerSerialNumber tinytext,
    tellerComment text
) engine=innodb;



CREATE TABLE netequipments (
    netEquipmentId INTEGER primary key auto_increment,
    officeId INTEGER NOT NULL REFERENCES offices(officeId) ON UPDATE CASCADE ON DELETE RESTRICT,
    netEquipmentNetWorkAddress tinytext,
    netEquipmentNetWorkName tinytext,
    netEquipmentModel tinytext,
    netEquipmentComment text
) engine=innodb;

INSERT INTO netequipments VALUES(0, 0, "", "", "", "");



CREATE TABLE `netequipmentspasswords` (
    `netEquipmentPasswordId` int(11) PRIMARY KEY auto_increment,
    `netEquipmentId` int(11) NOT NULL default '0' REFERENCES `netequipments` (`netEquipmentId`) ON DELETE RESTRICT ON UPDATE CASCADE,
    `netEquipmentPasswordLogin` tinytext,
    `netEquipmentPasswordPassword` tinytext,
    `netEquipmentPasswordDateTime` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8
    
INSERT INTO netequipmentspasswords VALUES(0, 0, "", "", "");
    

CREATE VIEW netequipmentsview AS
    SELECT netEquipmentId, officeId,
        CASE WHEN CONCAT(netEquipmentNetWorkAddress, ' (', netEquipmentNetWorkName, ')') = ' ()' THEN '' ELSE CONCAT(netEquipmentNetWorkAddress, ' (', netEquipmentNetWorkName, ')') END AS netEquipmentNetWorkAddressName
        FROM netequipments ORDER BY netEquipmentNetWorkAddressName;


        



