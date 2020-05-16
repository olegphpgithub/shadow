#include "TConnectionDialog.h"
#include "../../database/TDatabase.h"

TConnectionDialog::TConnectionDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    ui.setupUi(this);
    ui.hostNameLineEdit->setText(TDatabase::hostName);
    ui.portSpinBox->setValue(TDatabase::port);
    ui.databaseNameLineEdit->setText(TDatabase::databaseName);
    ui.userNameLineEdit->setText(TDatabase::userName);
    ui.passwordLineEdit->setText(TDatabase::password);
    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void TConnectionDialog::accept()
{
    TDatabase::hostName = ui.hostNameLineEdit->text();
    TDatabase::port = ui.portSpinBox->value();
    TDatabase::databaseName = ui.databaseNameLineEdit->text();
    TDatabase::userName = ui.userNameLineEdit->text();
    TDatabase::password = ui.passwordLineEdit->text();
    QDialog::accept();
}

void TConnectionDialog::reject()
{
    QDialog::reject();
}
