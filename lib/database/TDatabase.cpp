#include "TDatabase.h"

#include <QFile>
#include <QDebug>
#include <QString>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDomDocument>
#include <QSqlRelationalTableModel>


TDatabase::TDatabase()
{
    
}

bool TDatabase::open()
{
    QSqlDatabase db = QSqlDatabase::database(connectionName, false);
    db.setHostName(hostName);
    db.setPort(port);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);
    return db.open();
}

void TDatabase::readStructure()
{
    bool release = true;
    if(release) {
        QString queryString;
        queryString = "SELECT _struct from _struct";
        QSqlQuery sqlQuery(database());
        if (!sqlQuery.exec(queryString)) {
            qDebug() << "error";
            qDebug() << database().lastError().driverText();
        }
        qDebug() << "success";
        
        
        if(sqlQuery.next()) {
            if (!domDocument.setContent(sqlQuery.value(0).toString())) {
                return;
            }
        }
        
        structString = domDocument.toString(1);
        
    } else {
        QFile file("struct.xml");
        if (!file.open(QIODevice::ReadOnly))
            return;
        if (!domDocument.setContent(&file)) {
            file.close();
            return;
        }
        file.close();
        structString = domDocument.toString(1);
    }
}

QSqlDatabase TDatabase::database()
{
    return QSqlDatabase::database(connectionName);
}

//----------------------------------------------------------------------------------------------------

QString TDatabase::xmlData(QSqlRelationalTableModel *model)
{
    QDomDocument doc("table");
    
    QDomElement root = doc.createElement("table");
    doc.appendChild(root);
    
    QDomElement header = doc.createElement("header");
    root.appendChild(header);
    
    for(int j = 0; j < model->columnCount(); j++) {
        QDomElement field = doc.createElement("name");
        header.appendChild(field);
        QDomText text = doc.createTextNode(model->QSqlTableModel::headerData(j, Qt::Horizontal).toString());
        field.appendChild(text);
    }
    
    QDomElement rowset = doc.createElement("rowset");
    root.appendChild(rowset);
    
    for(int i = 0; i < model->rowCount(); i++) {
        
        QDomElement row = doc.createElement("row");
        rowset.appendChild(row);
        
        for(int j = 0; j < model->columnCount(); j++) {
            QDomElement field = doc.createElement("field");
            row.appendChild(field);
            
            QDomText text = doc.createTextNode(model->data(model->index(i, j), Qt::DisplayRole).toString());
            field.appendChild(text);
            
        }
        
    }
    
    return doc.toString();
}

