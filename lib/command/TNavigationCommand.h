#ifndef TNAVIGATIONCOMMAND_H
#define TNAVIGATIONCOMMAND_H

#include <QtSql>
#include <QtGui>
#include <QUndoCommand>

class TNavigationCommand : public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    
    TNavigationCommand(QUndoCommand *parent = 0);
    TNavigationCommand(const QString &, QUndoCommand *parent = 0);
    ~TNavigationCommand();
    
    void undo();
    void redo();
    
    void setTableNamePrevious(const QString tableNamePrevious);
    void setFilterNamePrevious(const QString filterNamePrevious);
    void setFilterValuePrevious(int filterValuePrevious);
    
    void setTableNameNext(const QString tableNameNext);
    void setFilterNameNext(const QString filterNameNext);
    void setFilterValueNext(int filterValueNext);

signals:
    
    void createTableViewRequested(const QString tableIdentifier = "",
        const QString filterName = "", const int filterValue = 0);
    
private:
    
    QString tableNamePrevious;
    QString filterNamePrevious;
    int filterValuePrevious;
    QString tableNameNext;
    QString filterNameNext;
    int filterValueNext;
    
};

#endif // TNAVIGATIONCOMMAND_H
