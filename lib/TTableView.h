#ifndef TTABLEVIEW_H
#define TTABLEVIEW_H

#include <QtWidgets/QTableView>
#include <QDebug>

#include "database/TDatabase.h"

class QMenu;
class TTableMapper;

class TTableView : public QTableView
{
    Q_OBJECT
public:
    
    TTableView(QWidget *parent = 0,
        const QString tableName ="",
        const QString filterName = "",
        const int filterValue = 0);
    ~TTableView();
    
    QString tableName();
    
    QString filterName();
    int filterValue();
    
    enum Settings {
        Width,
        Sort,
        Scroll
    };
    
    void loadSettings(Settings settings);
    void saveSettings();
    
public slots:
    
    virtual void commit();
    virtual void rollback();
    
    void createTableView();

    void sortChanged(int logicalIndex, Qt::SortOrder order);

    virtual void addNewRecord();
    virtual void removeSelectedRecords();
    virtual void showProperty();
    
signals:
    
    void createTableViewRequested(const QString tableName = "",
        const QString tableFilterId = "",
        const int tableFilterIdValue = 0);
    
protected:
    
    QMenu *contextMenu;
    TTableMapper *tableMapper;

    void contextMenuEvent(QContextMenuEvent *event);
    void createContextMenu();

    int sortColumn;
    Qt::SortOrder sortOrder;

    int verticalScroll;
    int horizontalScroll;
    
};

#endif // TTABLEVIEW_H
