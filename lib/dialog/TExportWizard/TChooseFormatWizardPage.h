#ifndef TCHOOSEFORMATWIZARDPAGE_H
#define TCHOOSEFORMATWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class TChooseFormatWizardPage;
}

class TChooseFormatWizardPage : public QWizardPage
{
    Q_OBJECT
    
public:
    explicit TChooseFormatWizardPage(QWidget *parent = 0);
    ~TChooseFormatWizardPage();
    void initializePage();
    bool validatePage();
    
private:
    Ui::TChooseFormatWizardPage *ui;
};

#endif // TCHOOSEFORMATWIZARDPAGE_H
