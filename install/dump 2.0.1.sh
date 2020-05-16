#!/bin/bash

/usr/bin/mysqldump -h 127.0.0.1 -u root -ptty698w3c shadow --tables \
_struct \
offices \
users usersview \
netobjectstypes \
netobjects netobjectsboxview netobjectspasswords netobjectspasswordslogs \
netobjectscomponentstypes netobjectscomponents \
workstationsview workstationsboxview workstationspasswordsview workstationscomponentssview \
printersview \
serversview serversboxview serverspasswordsview \
virtualserversview virtualserversboxview virtualserverspasswordsview \
routersview routersboxview routerspasswordsview \
atmsview > /u01/shared/backup/shadow/shadow-`date +%Y-%m-%d_%H-%M-%S`.sql
