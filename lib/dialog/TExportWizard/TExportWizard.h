#ifndef TEXPORTWIZARD_H
#define TEXPORTWIZARD_H

#include <QWizard>

namespace Ui {
class TExportWizard;
}

class TChooseFormatWizardPage;
class TChooseColumnsWizardPage;
class TChooseFileWizardPage;
class TExportProcessor;
class QAbstractItemModel;
class QProgressDialog;

class TExportWizard : public QWizard
{
    Q_OBJECT

public:
    explicit TExportWizard(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~TExportWizard();
    bool validateCurrentPage();
    int exec();
    int nextId() const;
    
    void setTableModel(QAbstractItemModel *tableModel);
    QAbstractItemModel *tableModel();
    
    enum { formatWizardPage, columnsWizardPage, fileWizardPage };
    
    TChooseFormatWizardPage *chooseFormatWizardPage;
    TChooseColumnsWizardPage *chooseColumnsWizardPage;
    TChooseFileWizardPage *chooseFileWizardPage;
    TExportProcessor *exportProcessor;
    
private:
    Ui::TExportWizard *ui;
    QAbstractItemModel *_tableModel;
    QProgressDialog *progressDialog;
    
    void exportFile();
    
public slots:
    void done();
    void done(int r);
};

#endif // TEXPORTWIZARD_H
