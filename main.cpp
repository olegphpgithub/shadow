#include <QtSql>
#include <QtXml>
#include <QtGui>

#include <QtWidgets/QMessageBox>

#include "lib/database/TDatabase.h"
#include "lib/database/TDatabaseStructure.h"
#include "lib/database/TDatabaseStructureParser.h"
#include "TMainWindow.h"
#include "lib/dialog/TConnectionDialog/TConnectionDialog.h"

QString TDatabase::hostName;
int TDatabase::port;
QString TDatabase::databaseName;
QString TDatabase::userName;
QString TDatabase::password;
QString TDatabase::connectionName;
QSettings TDatabase::settings("ttyrshb", "dddd");
QDomDocument TDatabase::domDocument;
QString TDatabase::structString;

QStringList TDatabaseStructure::tableStringList;
QMap<QString, QStringList> TDatabaseStructure::fieldNameMap;
QMap<QString, QStringList> TDatabaseStructure::fieldRelationNameMap;
QMap<QString, QStringList> TDatabaseStructure::fieldPrimaryKeyMap;
QMap<QString, QMap<QString, QString> > TDatabaseStructure::fieldCaptionMap;
QMap<QString, QMap<QString, QString> > TDatabaseStructure::fieldRelationCaptionMap;
QMap<QString, QMap<QString, bool> > TDatabaseStructure::fieldVisibleMap;
QMap<QString, QMap<QString, QString> > TDatabaseStructure::fieldEditorMap;
QMap<QString, QMap<QString, QStringList> > TDatabaseStructure::fieldRelationMap;
QMap<QString, QMap<int, QStringList> > TDatabaseStructure::contextMenuMap;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QTranslator translator;
    translator.load(QLocale::system().name());
    app.installTranslator(&translator);
    
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/images/favicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
    app.setWindowIcon(icon);
    
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
    QCoreApplication::setOrganizationName("rshb");
    QCoreApplication::setApplicationName("shadow");
    
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    
    TDatabase::hostName = "10.196.40.65";
    TDatabase::port = 3306;
    TDatabase::databaseName = "shadow";
    TDatabase::userName = "";
    TDatabase::password = "";
    TDatabase::connectionName = "rshb";
    
    QSqlDatabase::addDatabase("QMYSQL", TDatabase::connectionName);
    
    TConnectionDialog *connectionDialog;
    connectionDialog = new TConnectionDialog();
    while(true) {
        if(connectionDialog->exec() == QDialog::Accepted) {
            if(TDatabase::open()) {
                break;
            } else {
                QMessageBox messageBox(QMessageBox::Critical, QString(QObject::tr("Critical error")), QObject::tr("Cannot connect to database."), QMessageBox::Cancel | QMessageBox::Retry);
                messageBox.setInformativeText(TDatabase::database().lastError().driverText());
                messageBox.setDetailedText(TDatabase::database().lastError().databaseText());
                if(messageBox.exec() == QMessageBox::Retry) {
                    continue;
                } else {
                    return 0;
                }
            }
        } else {
            return 0;
        }
        QSqlDatabase::removeDatabase(TDatabase::connectionName);
    }
    delete connectionDialog;
    
    TDatabase::readStructure();
    
    TMainWindow *w = new TMainWindow();
    
    TDatabaseStructureParser *p = new TDatabaseStructureParser();
    
    QObject::connect(p, SIGNAL(progress(int, QString)), w, SLOT(progress(int, QString)));
    QObject::connect(p, SIGNAL(finished()), w, SLOT(run()));
    
    p->start();
    
    return app.exec();
}
