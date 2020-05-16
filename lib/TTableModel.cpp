#include "TTableModel.h"

#include "database/TDatabase.h"
#include "database/TDatabaseStructure.h"

#include <QStringList>

#include <QtSql>

//----------------------------------------------------------------------------------------------------

TTableModel::TTableModel(QObject *parent, QSqlDatabase db)
    : QSqlRelationalTableModel(parent, db)
{

}

//----------------------------------------------------------------------------------------------------

TTableModel::~TTableModel()
{
    
}

//----------------------------------------------------------------------------------------------------

void TTableModel::setTable(const QString &name)
{
    QSqlRelationalTableModel::setTable(name);
    
    for(int i=0; i<columnCount(); i++) {
        columnStringList.append(headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
    }
    
    for(int i=0; i<columnCount(); i++) {
        columnStringList.append(headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
    }
    
    if (primaryKey().isEmpty()) {
        QSqlIndex primaryIndex("primaryKey", "primaryKey");
        
        foreach(QString currentKeyfieldPrimaryKeyString, TDatabaseStructure::fieldPrimaryKeyMap.value(tableName())) {
            if(fieldIndex(currentKeyfieldPrimaryKeyString) > -1) {
                QSqlField primaryField(currentKeyfieldPrimaryKeyString, QVariant::Int);
                primaryIndex.append(primaryField);
            }
            
        }
        
        if(!primaryIndex.isEmpty()) {
            setPrimaryKey(primaryIndex);
        }
        
    }

}

//----------------------------------------------------------------------------------------------------

bool TTableModel::select()
{
    return QSqlRelationalTableModel::select();
}

//----------------------------------------------------------------------------------------------------

void TTableModel::setFilter(QString filterName, int filterValue)
{
    this->filtId = fieldIndex(filterName);
    this->filtName = filterName;
    this->filtValue = filterValue;
    QString filterString;
    
    if(filterName != "") {
        filterString = "%1.%2=%3";
        filterString = filterString.arg(tableName()).arg(filterName).arg(filterValue);
        QSqlTableModel::setFilter(filterString);
        
        if(TDatabaseStructure::fieldRelationMap.contains(this->tableName())) {
            
            QStringList currentfieldRelationStringList =
                TDatabaseStructure::fieldRelationMap
                    .value(this->tableName())
                    .value(filterName, QStringList());
            
            if(!currentfieldRelationStringList.isEmpty()) {
                
                QString relationFieldName = currentfieldRelationStringList[1];
                
                QSqlTableModel *sqlTableModel = relationModel(fieldIndex(filterName));
                filterString = "%1=0 OR %1=%2";
                filterString = filterString.arg(relationFieldName).arg(filterValue);
                sqlTableModel->setFilter(filterString);
                
            }
        }
        
    } else {
        QString primaryKeyString;
        primaryKeyString = primaryKey().fieldName(0);
        if (!(primaryKeyString.isNull() || primaryKeyString.isEmpty())) {
            filterString = "%1.%2>0";
            filterString = filterString.arg(tableName()).arg(primaryKeyString);
            QSqlTableModel::setFilter(filterString);
        }
    }
    
}

//----------------------------------------------------------------------------------------------------

QString TTableModel::filterName()
{
    return this->filtName;
}

int TTableModel::filterValue()
{
    return this->filtValue;
}

//----------------------------------------------------------------------------------------------------
