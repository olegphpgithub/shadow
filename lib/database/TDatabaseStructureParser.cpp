
#include "TDatabaseStructureParser.h"

#include "lib/database/TDatabase.h"
#include "lib/database/TDatabaseStructure.h"

#include <QBuffer>
#include <QtXmlPatterns>
#include <QDebug>

class oleg : public QAbstractMessageHandler
{
    virtual void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation )
    {
        (void)type;
        (void)identifier;
        (void)sourceLocation;
        qDebug() << description << "< Your message";
    }
};

TDatabaseStructureParser::TDatabaseStructureParser()
{
    
}

void TDatabaseStructureParser::run()
{
    
    int i;
    emit progress(0, QObject::tr("Preparing to parse..."));
    
    QXmlQuery xmlQuery(QXmlQuery::XQuery10);
    
    QBuffer domDocumentBuffer;
    domDocumentBuffer.setData(TDatabase::structString.toUtf8());
    domDocumentBuffer.open(QIODevice::ReadOnly);
    
    xmlQuery.bindVariable("domDocument", &domDocumentBuffer);
    
    xmlQuery.setMessageHandler(new oleg());
    
    emit progress(0, QObject::tr("Getting information about tables..."));
    
    QString queryString (
        "declare variable $domDocument external; "
        "let $node:=doc($domDocument)/database/tableView return "
        "let $a:=$node/@name/string() return "
        "for $result in ($a) "
        "return $result "
    );
    
    xmlQuery.setQuery(queryString);
    
    QStringList tableStringList;
    if(xmlQuery.isValid()) {
        xmlQuery.evaluateTo(&tableStringList);
        for(i=0; i<tableStringList.count(); i++) {
            TDatabaseStructure::tableStringList.append(tableStringList.at(i));
        }
    }
    
    emit progress(10, QObject::tr("Getting information about tables..."));
    
    foreach(QString currentTableString, TDatabaseStructure::tableStringList) {
        
        QString queryString (
            "declare variable $domDocument external; "
            "let $p1:=\"%1\" return "
            "let $node:=doc($domDocument)/database/tableView[@name=$p1]/table return "
            "let $a:=$node/field/@name/string() return "
            "for $result in ($a) "
            "return $result "
        );
        
        queryString = queryString.arg(currentTableString);
        
        xmlQuery.setQuery(queryString);
        
        
        
        QStringList fieldStringList;
        if(xmlQuery.isValid()) {
            xmlQuery.evaluateTo(&fieldStringList);
            foreach(QString currentFieldString, fieldStringList) {
                TDatabaseStructure::fieldNameMap[currentTableString].append(currentFieldString);
            }
        }
        domDocumentBuffer.seek(0);
        
        
    }
    
    emit progress(20, QObject::tr("Getting information about fields..."));
    
    
    //====================================================
    
    
    foreach(QString currentTableString, TDatabaseStructure::tableStringList) {
        foreach(QString currentfieldNameString, TDatabaseStructure::fieldNameMap.value(currentTableString)) {
            
            QString queryString (
                "declare variable $domDocument external; "
                "let $p1:=\"%1\" return "
                "let $p2:=\"%2\" return "
                "let $node:=doc($domDocument)/database/tableView[@name=$p1]/table/field[@name=$p2] return "
                "let $a:=if(exists($node/displayName)) then $node/displayName/string() else $node/@name/string() return "
                "let $b:=if(exists($node/visible)) then $node/visible/string() else \"true\" return "
                "let $c:=if(exists($node/editor)) then $node/editor/string() else \"lineEdit\" return "
                "let $d:=if(exists($node/primaryKey)) then \"true\" else \"false\" return "
                "for $result in ($a, $b, $c, $d) "
                "return $result "
            );
            
            queryString = queryString.arg(currentTableString).arg(currentfieldNameString);
            
            xmlQuery.setQuery(queryString);
            QStringList fieldCaptionStringList;
            if(xmlQuery.isValid()) {
                xmlQuery.evaluateTo(&fieldCaptionStringList);
                if(fieldCaptionStringList.count() == 4) {
                    TDatabaseStructure::fieldCaptionMap[currentTableString][currentfieldNameString] = fieldCaptionStringList[0];
                    TDatabaseStructure::fieldVisibleMap[currentTableString][currentfieldNameString] = (fieldCaptionStringList[1] == "true") ? true : false;
                    TDatabaseStructure::fieldEditorMap[currentTableString][currentfieldNameString] = fieldCaptionStringList[2];
                    if((fieldCaptionStringList[3] == "true")) {
                        TDatabaseStructure::fieldPrimaryKeyMap[currentTableString].append(currentfieldNameString);
                    }
                }
            }
            
            domDocumentBuffer.seek(0);
            
        }
    }
    
    
    //====================================================
    
    
    emit progress(40, QObject::tr("Getting information about relations..."));
    
    foreach(QString currentTableString, TDatabaseStructure::tableStringList) {
        foreach(QString currentfieldNameString, TDatabaseStructure::fieldNameMap.value(currentTableString)) {
            
            QString queryString (
                "declare variable $domDocument external; "
                "let $p1:=\"%1\" return "
                "let $p2:=\"%2\" return "
                "let $node:=doc($domDocument)/database/tableView[@name=$p1]/table/field[@name=$p2]/relation return "
                "let $a:=$node/relationTable/string() return "
                "let $b:=$node/relationField/string() return "
                "let $c:=$node/displayField/string() return "
                "for $result in ($a, $b, $c) "
                "return $result "
            );
            
            queryString = queryString.arg(currentTableString).arg(currentfieldNameString);
            
            xmlQuery.setQuery(queryString);
            
            QStringList fieldRelationStringList;
            if(xmlQuery.isValid()) {
                xmlQuery.evaluateTo(&fieldRelationStringList);
                if(fieldRelationStringList.count() == 3) {
                    QStringList list;
                    list << fieldRelationStringList[0] << fieldRelationStringList[1] << fieldRelationStringList[2];
                    TDatabaseStructure::fieldRelationMap[currentTableString][currentfieldNameString] = list;
                }
            }
            domDocumentBuffer.seek(0);
        }
    }
    
    foreach(QString currentTableString, TDatabaseStructure::tableStringList) {
        
        foreach(QString currentFieldNameString, TDatabaseStructure::fieldNameMap.value(currentTableString)) {
            
            if(TDatabaseStructure::fieldRelationMap[currentTableString].contains(currentFieldNameString)) {
                QString RelationFieldName = TDatabaseStructure::fieldRelationMap[currentTableString][currentFieldNameString][2];
                TDatabaseStructure::fieldRelationNameMap[currentTableString].append(RelationFieldName);
                TDatabaseStructure::fieldRelationCaptionMap[currentTableString][RelationFieldName] = TDatabaseStructure::fieldCaptionMap[currentTableString][currentFieldNameString];
            } else {
                TDatabaseStructure::fieldRelationNameMap[currentTableString].append(currentFieldNameString);
                TDatabaseStructure::fieldRelationCaptionMap[currentTableString][currentFieldNameString] = TDatabaseStructure::fieldCaptionMap[currentTableString][currentFieldNameString];
            }
            
        }
    }
    
    emit progress(60, QObject::tr("Getting information about context menu..."));
    
    foreach(QString currentTableString, TDatabaseStructure::tableStringList) {
        
        QString queryString (
            "declare variable $domDocument external; "
            "let $p1:=\"%1\" return "
            "let $node:=doc($domDocument)/database/tableView[@name=$p1]/contextMenu/action return "
            "let $a:=$node/@name/string() return "
            "for $result in ($a) "
            "return $result "
        );
        
        queryString = queryString.arg(currentTableString);
        
        xmlQuery.setQuery(queryString);
        
        QStringList actionStringList;
        if(xmlQuery.isValid()) {
            xmlQuery.evaluateTo(&actionStringList);
            i=0;
            foreach(QString currentActionString, actionStringList) {
                TDatabaseStructure::contextMenuMap[currentTableString][i].append(currentActionString);
                i++;
            }
        }
        domDocumentBuffer.seek(0);
    }
    
    emit progress(80, QObject::tr("Getting information about context menu..."));
    
    foreach(QString currentTableString, TDatabaseStructure::tableStringList) {
        foreach(int currentKeyActionInt, TDatabaseStructure::contextMenuMap.value(currentTableString).keys()) {
            
            QString currentActionString = TDatabaseStructure::contextMenuMap[currentTableString][currentKeyActionInt][0];
            
            QString queryString (
                "declare variable $domDocument external; "
                "let $p1:=\"%1\" return "
                "let $p2:=\"%2\" return "
                "let $node:=doc($domDocument)/database/tableView[@name=$p1]/contextMenu/action[@name=$p2] return "
                "let $a:=$node/displayName/string() return "
                "let $b:=$node/displayTable/string() return "
                "for $result in ($a, $b) "
                "return $result "
            );
            
            queryString = queryString.arg(currentTableString).arg(currentActionString);
            
            xmlQuery.setQuery(queryString);
            
            QStringList contextMenuStringList;
            if(xmlQuery.isValid()) {
                xmlQuery.evaluateTo(&contextMenuStringList);
                if(contextMenuStringList.count() == 2) {
                    TDatabaseStructure::contextMenuMap[currentTableString][currentKeyActionInt].append(contextMenuStringList[0]);
                    TDatabaseStructure::contextMenuMap[currentTableString][currentKeyActionInt].append(contextMenuStringList[1]);
                }
            }
            domDocumentBuffer.seek(0);
        }
    }
    
    emit progress(100, QObject::tr("Completed"));
    
}
