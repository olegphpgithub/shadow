#include "TMainWindow.h"

#include <QtSql>
#include <QtGui>
#include <QtXml>
#include <QtXmlPatterns>
#include <QtWidgets>
#include <QPrinter>

#include "lib/database/TDatabase.h"
#include "lib/database/TDatabaseStructure.h"
#include "lib/command/TNavigationCommand.h"
#include "lib/dialog/TExportWizard/TExportWizard.h"


//----------------------------------------------------------------------------------------------------

TMainWindow::TMainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    view = NULL;
    progressDialog = new QProgressDialog(QString(""), QString("Cancel"), 0, 100, this, Qt::Dialog);
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::run()
{
    progressDialog->hide();
    
    ui.setupUi(this);
    createToolBarActions();
    loadSettings();
    
    commandStack = new QUndoStack(this);
    commandStack->setUndoLimit(10);
    connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(exportTable()));
    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui.actionPrevious, SIGNAL(triggered()), commandStack, SLOT(undo()));
    connect(ui.actionNext, SIGNAL(triggered()), commandStack, SLOT(redo()));
    connect(commandStack, SIGNAL(canUndoChanged(bool)), ui.actionPrevious, SLOT(setEnabled(bool)));
    connect(commandStack, SIGNAL(canRedoChanged(bool)), ui.actionNext, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(createTableViewRequested(QString)), this, SLOT(createNavigationCommand(QString)));
    createTableView(TDatabaseStructure::tableStringList[0]);
    
    setVisible(true);
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::progress(int persent, const QString status)
{
    progressDialog->setLabelText(status);
    progressDialog->setValue(persent);
    progressDialog->resize(400, progressDialog->height());
    progressDialog->show();
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::createToolBarActions()
{
    QXmlQuery query(QXmlQuery::XPath20);
    query.setFocus(TDatabase::domDocument.toString(1));
    query.setQuery("/database/toolBar/action");
    
    QXmlResultItems result;
    query.evaluateTo(&result);
    QXmlItem item(result.next());
    
    int i = 1;
    while(!item.isNull()) {
        
        QXmlQuery actionQuery;
        actionQuery.setFocus(TDatabase::domDocument.toString(1));
        actionQuery.setQuery(QString("/database/toolBar/action[%1]").arg(QString::number(i)));
        
        QString actionString;
        actionQuery.evaluateTo(&actionString);
        
        QBuffer actionBuffer;
        actionBuffer.setData(actionString.toUtf8());
        actionBuffer.open(QIODevice::ReadOnly);
        
        QXmlQuery actoinParametersQuery;
        //actoinParametersQuery.setFocus(actionString);
        actoinParametersQuery.bindVariable("domDocument", &actionBuffer);
        actoinParametersQuery.setQuery(
            "declare variable $domDocument external; "
            "let $a:=doc($domDocument)/action/@name/string() return "
            "let $b:=doc($domDocument)/action/displayName/string() return "
            "let $c:=doc($domDocument)/action/displayTable/string() return "
            "for $result in ($a, $b, $c) "
            "return $result "
        );
        
        QStringList actoinParametersStringList;
        if(actoinParametersQuery.isValid()) {
            actoinParametersQuery.evaluateTo(&actoinParametersStringList);
            QAction *action = new QAction(this);
            action->setObjectName(actoinParametersStringList.at(0).trimmed());
            action->setText(actoinParametersStringList.at(1).trimmed());
            connect(action, SIGNAL(triggered()), this, SLOT(createTableView()));
            ui.toolBar->addAction(action);
        }
        
        actionBuffer.close();
        item = result.next();
        i++;
    }
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::closeEvent(QCloseEvent *)
{
    view->saveSettings();
    saveSettings();
    TDatabase::settings.sync();
    QSqlDatabase::database(TDatabase::connectionName, false).close();
    QSqlDatabase::removeDatabase(TDatabase::connectionName);
}

//----------------------------------------------------------------------------------------------------

TMainWindow::~TMainWindow()
{
    
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::createNavigationCommand(const QString tableName,
    const QString filterName, const int filterValue)
{
    TNavigationCommand *navigationCommand = new TNavigationCommand(NULL);
    
    navigationCommand->setTableNamePrevious(view->tableName());
    navigationCommand->setFilterNamePrevious(view->filterName());
    navigationCommand->setFilterValuePrevious(view->filterValue());
    
    navigationCommand->setTableNameNext(tableName);
    navigationCommand->setFilterNameNext(filterName);
    navigationCommand->setFilterValueNext(filterValue);
    
    connect(navigationCommand, SIGNAL(createTableViewRequested(QString, QString, int)), this, SLOT(createTableView(QString, QString, int)));
    commandStack->push(navigationCommand);
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::createTableView()
{
    emit createTableViewRequested(sender()->objectName());
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::createTableView(const QString tableName,
        const QString tableFilterName, const int tableFilterValue)
{
    if(view != NULL) {
        view->saveSettings();
        view->deleteLater();
    }
    
    setWindowTitle(QCoreApplication::applicationName());
    
    view = new TTableView(this, tableName, tableFilterName, tableFilterValue);
    
    setWindowTitle(windowTitle() + " - " + tableName);
    
    connect(ui.actionCommit, SIGNAL(triggered()), view, SLOT(commit()));
    connect(ui.actionRollback, SIGNAL(triggered()), view, SLOT(rollback()));
    connect(ui.actionAdd, SIGNAL(triggered()), view, SLOT(addNewRecord()));
    connect(ui.actionRemove, SIGNAL(triggered()), view, SLOT(removeSelectedRecords()));
    connect(view, SIGNAL(createTableViewRequested(QString, QString, int)), this, SLOT(createNavigationCommand(QString, QString, int)));
    
    setCentralWidget(view);
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::exportTable()
{
    TExportWizard exportWizard(this, Qt::Dialog);
    exportWizard.setTableModel(this->view->model());
    exportWizard.exec();
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::loadSettings()
{
    QVariant flag = TDatabase::settings.value("MainWindow/flag");
    if(!flag.isValid()) {
        createSettings();
    }
    int x = TDatabase::settings.value("MainWindow/x").toInt();
    int y = TDatabase::settings.value("MainWindow/y").toInt();
    int width = TDatabase::settings.value("MainWindow/width").toInt();
    int height = TDatabase::settings.value("MainWindow/height").toInt();
    move(x, y);
    resize(width, height);
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::saveSettings()
{
    TDatabase::settings.setValue("MainWindow/x", x());
    TDatabase::settings.setValue("MainWindow/y", y());
    TDatabase::settings.setValue("MainWindow/width", width());
    TDatabase::settings.setValue("MainWindow/height", height());
    TDatabase::settings.sync();
}

//----------------------------------------------------------------------------------------------------

void TMainWindow::createSettings()
{
    TDatabase::settings.setValue("MainWindow/x", 0);
    TDatabase::settings.setValue("MainWindow/y", 0);
    TDatabase::settings.setValue("MainWindow/width", 640);
    TDatabase::settings.setValue("MainWindow/height", 480);
    TDatabase::settings.setValue("MainWindow/flag", 1);
}

//----------------------------------------------------------------------------------------------------
