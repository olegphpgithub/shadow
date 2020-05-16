#ifndef TDATABASE_H
#define TDATABASE_H

class QString;
class QSettings;
class QSqlDatabase;
class QDomDocument;
class QSqlRelationalTableModel;

class TDatabase {
public:

    TDatabase();
    static bool open();
    static void readStructure();
    static QSqlDatabase database();
    static QString hostName;
    static int port;
    static QString databaseName;
    static QString userName;
    static QString password;
    static QString connectionName;
    static QSettings settings;
    static QDomDocument domDocument;
    static QString structString;
    
    static QString xmlData(QSqlRelationalTableModel *model);

};
#endif // TDATABASE_H
