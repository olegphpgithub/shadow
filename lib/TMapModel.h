#ifndef TMAPMODEL_H
#define TMAPMODEL_H

#include <QAbstractTableModel>
#include <QSqlTableModel>
#include <QMap>


class TMapModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    
    explicit TMapModel(QObject *parent = 0);
    ~TMapModel();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    
    void setMap(QMap<QString, QString>* map);
    void setList(QStringList* list);
    
signals:
    
public slots:
    
private:
    QMap<QString, QString>* _map;
    QStringList *_list;
};

#endif // TMAPMODEL_H
