#include "lib/TMapModel.h"
#include <QtDebug>

TMapModel::TMapModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    _map = NULL;
}

TMapModel::~TMapModel()
{
    
}

int TMapModel::rowCount(const QModelIndex& /* parent */) const
{
    if (_map)
        return _map->count();
    return 0;
}

int TMapModel::columnCount(const QModelIndex& /* parent */) const
{
    return 2;
}

QVariant TMapModel::data(const QModelIndex &index, int role) const
{
    if (!_map)
        return QVariant();
    
    if (!_list) {
        
        if (index.row() < 0 ||
            index.row() >= _map->count() ||
            role != Qt::DisplayRole) {
            
            return QVariant();
            
        }
        
        if (index.column() == 0)
            return _map->keys().at(index.row());
        if (index.column() == 1)
            return _map->values().at(index.row());
        
        return QVariant();
        
    } else {
        
        if (index.row() < 0 ||
            index.row() >= _map->count() ||
            index.row() >= _list->count() ||
            role != Qt::DisplayRole) {
            
            return QVariant();
            
        }
        
        if (index.column() == 0)
            return _list->at(index.row());
        
        if (index.column() == 1) {
            return _map->value( _list->at(index.row()) );
        }
        
        return QVariant();
        
    }
}

void TMapModel::setMap(QMap<QString, QString> *map)
{
    _map = map;
}

void TMapModel::setList(QStringList* list)
{
    _list = list;
}
