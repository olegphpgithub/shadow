#ifndef TCHOOSEFILEWIZARDPAGE_H
#define TCHOOSEFILEWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class TChooseFileWizardPage;
}

class TChooseFileWizardPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit TChooseFileWizardPage(QWidget *parent = 0);
    ~TChooseFileWizardPage();
    void initializePage();
    
public slots:
    void chooseFileName();
    
private:
    Ui::TChooseFileWizardPage *ui;
    QString filter;
};

#endif // TCHOOSEFILEWIZARDPAGE_H
