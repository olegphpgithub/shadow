#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include "ui_TMainWindow.h"
#include "lib/TTableView.h"

class QSystemTrayIcon;
class QUndoStack;
class QProgressDialog;

class TMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    
    TMainWindow(QWidget *parent=0, Qt::WindowFlags flags=0);
    ~TMainWindow();
    void closeEvent(QCloseEvent *event);
    
    
private:
    
    Ui::MainWindow ui;
    TTableView *view;
    QUndoStack *commandStack;
    
    QProgressDialog *progressDialog;
    
public slots:

    void createNavigationCommand(const QString tableIdentifier,
        const QString filterName = "", const int filterValue = 0);
    void createTableView();
    void createTableView(const QString tableName,
        const QString filterName = "", const int filterValue = 0);
    void progress(int persent, const QString status);
    void exportTable();
    void run();

signals:
    
    void createTableViewRequested(const QString tableName,
        const QString filterName = "", const int filterValue = 0);
    
private:
    
    void createToolBarActions();
    
    void loadSettings();
    void saveSettings();
    void createSettings();
    
};

#endif // TMAINWINDOW_H
