#include "TNavigationCommand.h"

TNavigationCommand::TNavigationCommand(QUndoCommand *parent)
    : QUndoCommand(parent)
{
    
}

//----------------------------------------------------------------------------------------------------

TNavigationCommand::TNavigationCommand(const QString &text, QUndoCommand *parent)
    : QUndoCommand(text, parent)
{
    
}

//----------------------------------------------------------------------------------------------------

TNavigationCommand::~TNavigationCommand()
{
    
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::setTableNamePrevious(const QString tableNamePrevious)
{
    this->tableNamePrevious = tableNamePrevious;
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::setFilterNamePrevious(const QString filterNamePrevious)
{
    this->filterNamePrevious = filterNamePrevious;
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::setFilterValuePrevious(int filterValuePrevious)
{
    this->filterValuePrevious = filterValuePrevious;
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::setTableNameNext(const QString tableNameNext)
{
    this->tableNameNext = tableNameNext;
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::setFilterNameNext(const QString filterNameNext)
{
    this->filterNameNext = filterNameNext;
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::setFilterValueNext(int filterValueNext)
{
    this->filterValueNext = filterValueNext;
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::undo()
{
    emit createTableViewRequested(tableNamePrevious, filterNamePrevious, filterValuePrevious);
}

//----------------------------------------------------------------------------------------------------

void TNavigationCommand::redo()
{
    emit createTableViewRequested(tableNameNext, filterNameNext, filterValueNext);
}

//----------------------------------------------------------------------------------------------------
