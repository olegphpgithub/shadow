#include "TConnectionDialog.h"
#include "../../database/TDatabase.h"
#include <QSettings>

TConnectionDialog::TConnectionDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    ui.setupUi(this);
    
    QString host = TDatabase::settings.value("host").value<QString>();
    if(host.isNull()) {
        host = QString("127.0.0.1");
    }
    int port = TDatabase::settings.value("port").value<int>();
    if(port == 0) {
        port = 3306;
    }
    QString database = TDatabase::settings.value("database").value<QString>();
    QString user = TDatabase::settings.value("user").value<QString>();
    QString password = TDatabase::settings.value("password").value<QString>();
    
    ui.hostNameLineEdit->setText(host);
    ui.portSpinBox->setValue(port);
    ui.databaseNameLineEdit->setText(database);
    ui.userNameLineEdit->setText(user);
    ui.passwordLineEdit->setText(password);
    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void TConnectionDialog::accept()
{
    save();
    TDatabase::hostName = ui.hostNameLineEdit->text();
    TDatabase::port = ui.portSpinBox->value();
    TDatabase::databaseName = ui.databaseNameLineEdit->text();
    TDatabase::userName = ui.userNameLineEdit->text();
    TDatabase::password = ui.passwordLineEdit->text();
    QDialog::accept();
}

void TConnectionDialog::reject()
{
    save();
    QDialog::reject();
}

void TConnectionDialog::save()
{
    TDatabase::settings.setValue("host", ui.hostNameLineEdit->text());
    TDatabase::settings.setValue("port", ui.portSpinBox->value());
    TDatabase::settings.setValue("database", ui.databaseNameLineEdit->text());
    TDatabase::settings.setValue("user", ui.userNameLineEdit->text());
    TDatabase::settings.setValue("password", ui.passwordLineEdit->text());
}
