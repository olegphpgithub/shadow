#include "TTableView.h"
#include "TTableModel.h"
#include "TTableMapper.h"

#include "database/TDatabase.h"
#include "database/TDatabaseStructure.h"

#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include <QtXmlPatterns>

#include <typeinfo>

#include <QDebug>

/*
class oleg : public QAbstractMessageHandler
{
    virtual void handleMessage(QtMsgType type, const QString & description, const QUrl & identifier, const QSourceLocation & sourceLocation )
    {
        qDebug() << description << "<<<";
    }
};
*/

//----------------------------------------------------------------------------------------------------

TTableView::TTableView(QWidget *parent, const QString tableName, const QString filterName, const int filterValue)
    : QTableView(parent)
{
    
    setWordWrap(false);
    
    setSortingEnabled(true);
    horizontalHeader()->setSortIndicatorShown(true);
    connect(horizontalHeader(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)), this, SLOT(sortChanged(int,Qt::SortOrder)));
    
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    
    
    
    TTableModel *tableModel = new TTableModel(this, QSqlDatabase::database("rshb"));
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setTable(tableName);
    setModel(tableModel);
    
    
    
    createContextMenu();
    
    
    foreach(QString currentKeyfieldRelationString, TDatabaseStructure::fieldRelationMap.value(tableName).keys()) {
        QStringList currentfieldRelationStringList =
                TDatabaseStructure::fieldRelationMap.value(tableName).value(currentKeyfieldRelationString);
        tableModel->relationColumnStringList.append(currentKeyfieldRelationString);
        tableModel->setRelation(tableModel->fieldIndex(currentKeyfieldRelationString),
                QSqlRelation(currentfieldRelationStringList[0],
                currentfieldRelationStringList[1],
                currentfieldRelationStringList[2]));
    }
    
    setItemDelegate(new QSqlRelationalDelegate(this));
    
    foreach(QString currentKeyfieldCaptionString, TDatabaseStructure::fieldCaptionMap.value(tableName).keys()) {
        QString currentfieldCaptionString = TDatabaseStructure::fieldCaptionMap.value(tableName).value(currentKeyfieldCaptionString);
        tableModel->setHeaderData(tableModel->fieldIndex(currentKeyfieldCaptionString), Qt::Horizontal, currentfieldCaptionString);
    }
    
    foreach(QString currentKeyfieldVisibleString, TDatabaseStructure::fieldVisibleMap.value(tableName).keys()) {
        bool currentfieldVisibleBool = TDatabaseStructure::fieldVisibleMap.value(tableName).value(currentKeyfieldVisibleString);
        if(!currentfieldVisibleBool) {
            hideColumn(tableModel->fieldIndex(currentKeyfieldVisibleString));
        }
    }
    
    tableMapper = new TTableMapper(this);
    tableMapper->setModel(tableModel);
    
    loadSettings(Width);
    
    loadSettings(Sort);
    tableModel->setSort(sortColumn, sortOrder);
    
    tableModel->setFilter(filterName, filterValue);
    
    tableModel->select();
    
    loadSettings(Scroll);
    
    horizontalHeader()->setSortIndicator(sortColumn, sortOrder);
    
    setFocus();
    
}

//----------------------------------------------------------------------------------------------------

TTableView::~TTableView()
{
    
}

//----------------------------------------------------------------------------------------------------

void TTableView::createContextMenu()
{
    contextMenu = new QMenu(this);
    
    foreach(int currentKeyActionInt, TDatabaseStructure::contextMenuMap.value(tableName()).keys()) {
        QAction *action = new QAction(this);
        action->setObjectName(TDatabaseStructure::contextMenuMap[tableName()][currentKeyActionInt][2]);
        action->setText(TDatabaseStructure::contextMenuMap[tableName()][currentKeyActionInt][1]);
        connect(action, SIGNAL(triggered()), this, SLOT(createTableView()));
        contextMenu->addAction(action);
    }
    
    QAction *actionProperty = new QAction(QObject::tr("&Property"), this);
    connect(actionProperty, SIGNAL(triggered()), this, SLOT(showProperty()));
    if(contextMenu->actions().count() != 0) {
        contextMenu->addSeparator();
    }
    contextMenu->addAction(actionProperty);
    
}

//----------------------------------------------------------------------------------------------------

void TTableView::sortChanged(int logicalIndex, Qt::SortOrder order)
{
    sortColumn = logicalIndex;
    sortOrder = order;
}

//----------------------------------------------------------------------------------------------------

void TTableView::loadSettings(Settings settings)
{
    int sortOrderInt;
    
    switch(settings) {
        case Width:
            for(int i = 0; i < model()->columnCount(); i++) {
                int width = TDatabase::settings.value(tableName() + "/" + QString::number(i)).toInt();
                width = (width < 1) ? 100 : width;
                setColumnWidth(i, width);
            }
        break;
        case Sort:
            sortColumn = TDatabase::settings.value(tableName() + "/" + "sortColumn").toInt();
            sortOrderInt = TDatabase::settings.value(tableName() + "/" + "sortOrder").toInt();
            sortOrder = (sortOrderInt == 1)? Qt::DescendingOrder : Qt::AscendingOrder;
        break;
        case Scroll:
            verticalScroll = TDatabase::settings.value(tableName() + "/" + "verticalScrollBar/sliderPosition").toInt();
            horizontalScroll = TDatabase::settings.value(tableName() + "/" + "horizontalScrollBar/sliderPosition").toInt();
            
            verticalScrollBar()->setMinimum(0);
            verticalScrollBar()->setMaximum(model()->rowCount() - 1);
            if(model()->rowCount() > verticalScroll) {
                verticalScrollBar()->setSliderPosition(verticalScroll);
            } else {
                verticalScrollBar()->setSliderPosition(model()->rowCount() - 1);
            }
            
            horizontalScrollBar()->setMinimum(0);
            horizontalScrollBar()->setMaximum(model()->columnCount() - 1);
            if(model()->columnCount() > horizontalScroll) {
                horizontalScrollBar()->setSliderPosition(horizontalScroll);
            } else {
                horizontalScrollBar()->setSliderPosition(model()->columnCount() - 1);
            }
        break;
    }
}

//----------------------------------------------------------------------------------------------------

void TTableView::saveSettings()
{
    if(QAbstractItemView::model()) {
        QSqlRelationalTableModel *model = dynamic_cast<QSqlRelationalTableModel *>(QAbstractItemView::model());
        for(int i = 0; i < model->columnCount(); i++) {
            TDatabase::settings.setValue(model->tableName() + "/" + QString::number(i), columnWidth(i));
        }
    }
    
    TDatabase::settings.setValue(tableName() + "/" + "sortColumn", sortColumn);
    TDatabase::settings.setValue(tableName() + "/" + "sortOrder", sortOrder);
    
    TDatabase::settings.setValue(tableName() + "/" + "verticalScrollBar/sliderPosition", verticalScrollBar()->sliderPosition());
    TDatabase::settings.setValue(tableName() + "/" + "horizontalScrollBar/sliderPosition", horizontalScrollBar()->sliderPosition());
}

//----------------------------------------------------------------------------------------------------

void TTableView::createTableView()
{
    TTableModel *tableModel = dynamic_cast<TTableModel *>(QTableView::model());
    QAction *action = dynamic_cast<QAction *>(sender());
    QString primaryKeyString;
    primaryKeyString = tableModel->primaryKey().fieldName(0);
    int id = model()->index(currentIndex().row(), tableModel->fieldIndex(primaryKeyString)).data().toInt();
    emit createTableViewRequested(action->objectName(), primaryKeyString, id);
}

//----------------------------------------------------------------------------------------------------

void TTableView::addNewRecord()
{
    TTableModel *tableModel = dynamic_cast<TTableModel *>(QAbstractItemView::model());
    
    QSqlRecord record;
    
    if(filterName() != "") {
        for(int i = 0; i<tableModel->columnCount(); i++) {
            if(tableModel->relation(i).isValid()) {
                tableModel->relationColumnStringList.contains(filterName());
                if(i == tableModel->filtId) {
                    QSqlField field;
                    field.setName(tableModel->relation(i).displayColumn());
                    field.setType(QVariant::Int);
                    field.setValue(QVariant(filterValue()));
                    record.append(field);
                }
            }
        }
    }
    
    tableModel->insertRecord(-1, record);
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

//----------------------------------------------------------------------------------------------------

void TTableView::removeSelectedRecords()
{
    QModelIndexList modelList = selectionModel()->selectedRows();
    for(int i=0; i<modelList.count(); i++) {
        hideRow(modelList[i].row());
        model()->removeRow(modelList[i].row());
    }
}

//----------------------------------------------------------------------------------------------------

void TTableView::contextMenuEvent(QContextMenuEvent *event)
{
    setCurrentIndex(indexAt(event->pos()));
    if(currentIndex().row() > -1) {
        this->contextMenu->exec(event->globalPos());
    }
}

//----------------------------------------------------------------------------------------------------

QString TTableView::tableName()
{
    if(model() != NULL) {
        
        QSqlTableModel *sqlTableModel;
        try {
            sqlTableModel = dynamic_cast<QSqlTableModel *>(this->model());
        } catch (const std::bad_cast&) {
            return QString();
        }
        
        return sqlTableModel->tableName();
        
    }
    
    return QString();
    
}

//----------------------------------------------------------------------------------------------------

QString TTableView::filterName()
{
    if(this->model() != NULL) {
        
        TTableModel *tableModel;
        try {
            tableModel = dynamic_cast<TTableModel *>(this->model());
        } catch (const std::bad_cast&) {
            return QString();
        }
        
        return tableModel->filterName();
        
    }
    
    return QString();
    
}

//----------------------------------------------------------------------------------------------------

int TTableView::filterValue()
{
    if(this->model() != NULL) {
        
        TTableModel *tableModel;
        try {
            tableModel = dynamic_cast<TTableModel *>(this->model());
        } catch (const std::bad_cast&) {
            return 0;
        }
        
        return tableModel->filterValue();
        
    }
    
    return 0;
    
}

//----------------------------------------------------------------------------------------------------

void TTableView::commit()
{
    QSqlRelationalTableModel *model = dynamic_cast<QSqlRelationalTableModel *>(QTableView::model());
    int sliderPositionX = horizontalScrollBar()->sliderPosition();
    int sliderPositionY = verticalScrollBar()->sliderPosition();
    QModelIndex modelIndex = currentIndex();
    if(!model->submitAll()) {
        QMessageBox messageBox(QMessageBox::Warning, QString(QObject::tr("Warning")), QObject::tr("Cannot commit all changes."), QMessageBox::Cancel, this);
        messageBox.setInformativeText(model->lastError().driverText());
        messageBox.setDetailedText(model->lastError().databaseText());
        messageBox.exec();
    }
    horizontalScrollBar()->setSliderPosition(sliderPositionX);
    verticalScrollBar()->setSliderPosition(sliderPositionY);
    setCurrentIndex(modelIndex);
}

//----------------------------------------------------------------------------------------------------

void TTableView::rollback()
{
    QSqlRelationalTableModel *model = dynamic_cast<QSqlRelationalTableModel *>(QTableView::model());
    int sliderPositionX = horizontalScrollBar()->sliderPosition();
    int sliderPositionY = verticalScrollBar()->sliderPosition();
    QModelIndex modelIndex = currentIndex();
    model->revertAll();
    model->select();
    horizontalScrollBar()->setSliderPosition(sliderPositionX);
    verticalScrollBar()->setSliderPosition(sliderPositionY);
    setCurrentIndex(modelIndex);
}

//----------------------------------------------------------------------------------------------------

void TTableView::showProperty()
{
    tableMapper->setCurrentIndex(currentIndex().row());
    tableMapper->exec();
}

//----------------------------------------------------------------------------------------------------
