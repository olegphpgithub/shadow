#include "TChooseFormatWizardPage.h"
#include "ui_TChooseFormatWizardPage.h"

#include <QtDebug>
#include <QtWidgets>

TChooseFormatWizardPage::TChooseFormatWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::TChooseFormatWizardPage)
{
    ui->setupUi(this);
    registerField("textFormatRadioButton", this->ui->textFormatRadioButton);
    registerField("htmlFormatRadioButton", this->ui->htmlFormatRadioButton);
}

TChooseFormatWizardPage::~TChooseFormatWizardPage()
{
    delete ui;
}

void TChooseFormatWizardPage::initializePage()
{
    
}

bool TChooseFormatWizardPage::validatePage()
{
    bool text, html;
    text = field("textFormatRadioButton").toBool();
    html = field("htmlFormatRadioButton").toBool();
    if(text || html) {
        return true;
    }
    QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No any export format selected."), QMessageBox::Cancel);
    return false;
}
