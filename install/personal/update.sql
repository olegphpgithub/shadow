CREATE TABLE `users`
(
    `userId` int(11) NOT NULL AUTO_INCREMENT,
    `userSurnameNamePatronymic` tinytext,
    `userBirthday` date DEFAULT NULL,
    PRIMARY KEY (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

INSERT INTO `users` VALUES(0, "", NULL);
UPDATE `users` set `userId` = 0;
ALTER TABLE `users` AUTO_INCREMENT = 1;

CREATE TABLE `networkobjects`
(
    `netWorkObjectId` int(11) NOT NULL AUTO_INCREMENT,
    `userId` int(11) DEFAULT NULL,
    `netWorkObjectName` tinytext,
    `netWorkObjectAddress` tinytext,
    `netWorkObjectComment` text,
    PRIMARY KEY (`netWorkObjectId`),
    KEY `networkobjects_ibfk_1` (`userId`),
    CONSTRAINT `networkobjects_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

INSERT INTO `networkobjects` VALUES(0, 0, "", "", "");
UPDATE `networkobjects` set `netWorkObjectId` = 0;
ALTER TABLE `networkobjects` AUTO_INCREMENT = 1;

CREATE TABLE `networkobjectpasswords`
(
    `netWorkObjectPasswordId` int(11) NOT NULL AUTO_INCREMENT,
    `netWorkObjectId` int(11) NOT NULL DEFAULT '0',
    `userId` int(11) DEFAULT NULL,
    `netWorkObjectPasswordLogin` tinytext,
    `netWorkObjectPasswordPassword` tinytext,
    `netWorkObjectPasswordDateTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    `netWorkObjectPasswordComment` tinytext,
    PRIMARY KEY (`netWorkObjectPasswordId`),
    KEY `netWorkObjectId` (`netWorkObjectId`),
    KEY `networkobjectpasswords_ibfk_1` (`userId`),
    CONSTRAINT `networkobjectpasswords_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `users` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
;

INSERT INTO `networkobjectpasswords` VALUES(0, 0, 0, "", "", NULL, "");
UPDATE `networkobjectpasswords` set `netWorkObjectId` = 0;
ALTER TABLE `networkobjectpasswords` AUTO_INCREMENT = 1;
