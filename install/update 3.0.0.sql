
CREATE TABLE `_struct` (
`_struct` blob ) ENGINE=InnoDB
DEFAULT CHARSET=utf8





CREATE TABLE `networkobjecttypes` (
    netWorkObjectTypeId int(11) PRIMARY KEY AUTO_INCREMENT,
    netWorkObjectTypeName tinytext
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8


CREATE TABLE `networkobjects` (
    `netWorkObjectId` int(11) NOT NULL AUTO_INCREMENT,
    `netWorkObjectParentId` int(11) DEFAULT NULL,
    `netWorkObjectTypeId` int(11) NOT NULL DEFAULT 0,
    `netWorkObjectName` tinytext,
    `netWorkObjectAddress` tinytext,
    `netWorkObjectOS` tinytext,
    `netWorkObjectComment` tinytext,
    PRIMARY KEY (`netWorkObjectId`),
    FOREIGN KEY (netWorkObjectParentId) REFERENCES networkobjects(netWorkObjectId) ON UPDATE CASCADE ON DELETE RESTRICT,
    FOREIGN KEY (netWorkObjectTypeId) REFERENCES networkobjecttypes(netWorkObjectTypeId) ON UPDATE CASCADE ON DELETE RESTRICT
)
ENGINE=InnoDB
DEFAULT CHARSET=utf8
;

INSERT INTO networkobjects VALUES
(
    NULL,
    NULL,
    0,
    NULL,
    NULL,
    NULL,
    NULL
)
;

UPDATE networkobjects SET netWorkObjectId = 0;

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








