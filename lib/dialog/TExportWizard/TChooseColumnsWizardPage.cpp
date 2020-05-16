#include "TChooseColumnsWizardPage.h"
#include "ui_TChooseColumnsWizardPage.h"

#include "lib/database/TDatabase.h"
#include "lib/database/TDatabaseStructure.h"

#include "lib/dialog/TExportWizard/TExportWizard.h"
#include "lib/TTableModel.h"
#include "lib/TMapModel.h"

#include <QMessageBox>
#include <QtDebug>
#include <QStringListModel>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlRecord>
#include <QStringList>

#include <typeinfo>

TChooseColumnsWizardPage::TChooseColumnsWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::TChooseColumnsWizardPage)
{
    ui->setupUi(this);
    qRegisterMetaType<QItemSelectionModel*>("QItemSelectionModel*");
    registerField("columnsListViewSelection", this, "selectionModel");
    
    registerField("columnsSelected", this, "columnsStringList");
}

TChooseColumnsWizardPage::~TChooseColumnsWizardPage()
{
    delete ui;
}


QStringList TChooseColumnsWizardPage::columnsStringList(void)
{
    return _columnsStringList;
}


void TChooseColumnsWizardPage::initializePage()
{
    
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
    
    TMapModel *columnsMapModel = new TMapModel(this);
    columnsMapModel->setMap(&TDatabaseStructure::fieldRelationCaptionMap[tableModel->tableName()]);
    columnsMapModel->setList(&TDatabaseStructure::fieldRelationNameMap[tableModel->tableName()]);
    
    ui->columnsListView->setModel(columnsMapModel);
    ui->columnsListView->setModelColumn(1);
    
}

bool TChooseColumnsWizardPage::validatePage()
{
    
    QItemSelectionModel *currentSelectionModel = ui->columnsListView->selectionModel();
    
    if ( !currentSelectionModel->hasSelection() ) {
        QMessageBox::critical(this, QObject::tr("Error"), QObject::tr("No any column selected."), QMessageBox::Cancel);
        return false;
    }
    
    QModelIndexList selectedIndexList = currentSelectionModel->selectedIndexes();
    
    _columnsStringList.clear();
    foreach(QModelIndex selectedIndex, selectedIndexList) {
        QString columName = ui->columnsListView->model()->index(selectedIndex.row(), 0).data().toString();
        _columnsStringList.append(columName);
    }
    
    return true;
}

/*
QItemSelectionModel* TChooseColumnsWizardPage::selectionModel(void)
{
    return ui->columnsListView->selectionModel();
}
*/
