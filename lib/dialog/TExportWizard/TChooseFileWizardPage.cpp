#include "TChooseFileWizardPage.h"
#include "ui_TChooseFileWizardPage.h"

#include "lib/dialog/TExportWizard/TExportWizard.h"
#include "lib/TTableModel.h"

#include <QDir>
#include <QFileDialog>

#include <typeinfo>

TChooseFileWizardPage::TChooseFileWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::TChooseFileWizardPage)
{
    ui->setupUi(this);
    connect(ui->chooseFilePushButton, SIGNAL(pressed()), this, SLOT(chooseFileName()));
    registerField("fileName", ui->chooseFileLineEdit);
}

TChooseFileWizardPage::~TChooseFileWizardPage()
{
    delete ui;
}

void TChooseFileWizardPage::initializePage()
{
    
    QString exportDir, extention;
    
    TExportWizard *exportWizard;
    
    try {
        exportWizard = dynamic_cast<TExportWizard*>(this->wizard());
    } catch (const std::bad_cast&) {
        return;
    }
    
    TTableModel *tableModel;
    
    try {
        tableModel = dynamic_cast<TTableModel *>(exportWizard->tableModel());
    } catch (const std::bad_cast&) {
        return;
    }
    
    exportDir = QDir::homePath();
    
    if(field("textFormatRadioButton").toBool()) {
        extention = "txt";
        filter = tr("Text (*.txt)");
    }
    
    if(field("htmlFormatRadioButton").toBool()) {
        extention = "html";
        filter = tr("Hypertext (*.html)");
    }
    
    ui->chooseFileLineEdit->setText(exportDir + "/" + tableModel->tableName() + "." + extention);
    
}


void TChooseFileWizardPage::chooseFileName()
{
    
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
        ui->chooseFileLineEdit->text(),
        filter);
    if(!(fileName.isNull() || fileName.isEmpty())) {
        ui->chooseFileLineEdit->setText(fileName);
    }
    ui->chooseFileLineEdit->setFocus();
    
}
