#ifndef TDATABASESTRUCTURE_H
#define TDATABASESTRUCTURE_H

/*
class QMap<QString, QStringList>;
class QMap<QString, QString>;
class QMap<QString, QMap<QString, QString>;
*/

#include <QMap>

class QString;
class QStringList;

class TDatabaseStructure {
public:
    
    TDatabaseStructure();
    static QStringList tableStringList;
    static QMap<QString, QStringList> fieldNameMap;
    static QMap<QString, QStringList> fieldRelationNameMap;
    static QMap<QString, QStringList> fieldPrimaryKeyMap;
    static QMap<QString, QMap<QString, QString> > fieldCaptionMap;
    static QMap<QString, QMap<QString, QString> > fieldRelationCaptionMap;
    static QMap<QString, QMap<QString, bool> > fieldVisibleMap;
    static QMap<QString, QMap<QString, QString> > fieldEditorMap;
    static QMap<QString, QMap<QString, QStringList> > fieldRelationMap;
    static QMap<QString, QMap<int, QStringList> > contextMenuMap;
    
};

#endif // TDATABASESTRUCTURE_H
