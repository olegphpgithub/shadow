#ifndef TCHOOSECOLUMNSWIZARDPAGE_H
#define TCHOOSECOLUMNSWIZARDPAGE_H

#include <QWizardPage>
#include <QItemSelectionModel>
#include <QMap>
#include <QStringList>
#include <QString>

namespace Ui {
class TChooseColumnsWizardPage;
}



class TChooseColumnsWizardPage : public QWizardPage
{
    Q_OBJECT
    //Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel)
    Q_PROPERTY(QStringList columnsStringList READ columnsStringList)
    
public:
    explicit TChooseColumnsWizardPage(QWidget *parent = 0);
    ~TChooseColumnsWizardPage();
    void initializePage();
    bool validatePage();
    
    //QItemSelectionModel *selectionModel(void);
    
    QStringList columnsStringList(void);
    QStringList _columnsStringList;

private:
    Ui::TChooseColumnsWizardPage *ui;
    //QMap<QString, QString> *columnsMap = NULL;
};

//Q_DECLARE_METATYPE(QItemSelectionModel*)
//Q_DECLARE_METATYPE(QString*)

#endif // TCHOOSECOLUMNSWIZARDPAGE_H
