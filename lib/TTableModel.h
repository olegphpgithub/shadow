#ifndef TTABLEMODEL_H
#define TTABLEMODEL_H

#include <QSqlRelationalTableModel>
#include <QDebug>
#include <QStringList>

class TTableModel : public QSqlRelationalTableModel {
    Q_OBJECT
public:
    
    TTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    ~TTableModel();
    
    virtual bool insertRecord(int row, QSqlRecord &record) { return QSqlTableModel::insertRecord(row, record); }
    
    void setTable(const QString &name);
    
    bool select();
    
    //void setFilterIdentifier(int filterIdentifier);
    //void setFilterIdentifierValue(int filterIdentifierValue);
    
    void setFilter(QString filterName, int filterValue);
    QString filterName();
    int filterValue();
    
    int filtId;
    QString filtName;
    int filtValue;
    
    QStringList columnStringList;
    QStringList relationColumnStringList;
    
private:
};

#endif // TTABLEMODEL_H
