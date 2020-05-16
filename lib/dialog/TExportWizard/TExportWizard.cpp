#include "TExportWizard.h"
#include "ui_TExportWizard.h"

#include "lib/dialog/TExportWizard/TChooseFormatWizardPage.h"
#include "lib/dialog/TExportWizard/TChooseColumnsWizardPage.h"
#include "lib/dialog/TExportWizard/TChooseFileWizardPage.h"
#include "lib/dialog/TExportWizard/TExportProcessor.h"

#include "lib/database/TDatabase.h"
#include "lib/database/TDatabaseStructure.h"

#include "lib/TTableModel.h"

#include <QtDebug>
#include <QSqlRelationalTableModel>
#include <QtXml>
#include <QtXmlPatterns>
#include <QtWidgets>

#include <typeinfo>


TExportWizard::TExportWizard(QWidget *parent, Qt::WindowFlags flags) :
    QWizard(parent, flags),
    ui(new Ui::TExportWizard)
{
    ui->setupUi(this);
    
    _tableModel = NULL;
    
    chooseFormatWizardPage = new TChooseFormatWizardPage(this);
    chooseColumnsWizardPage = new TChooseColumnsWizardPage(this);
    chooseFileWizardPage  = new TChooseFileWizardPage(this);
    
    setPage(formatWizardPage, chooseFormatWizardPage);
    setPage(columnsWizardPage, chooseColumnsWizardPage);
    setPage(fileWizardPage, chooseFileWizardPage);
}

TExportWizard::~TExportWizard()
{
    //qDebug() << "~TExportWizard()";
    delete ui;
}

void TExportWizard::setTableModel(QAbstractItemModel *tableModel)
{
    _tableModel = tableModel;
}

QAbstractItemModel *TExportWizard::tableModel()
{
    return _tableModel;
}

bool TExportWizard::validateCurrentPage()
{
    return currentPage()->validatePage();
}

int TExportWizard::exec()
{
    if (_tableModel == NULL) {
        throw QString(tr("No table selected"));
    }
    return QWizard::exec();
}

int TExportWizard::nextId() const
{
    return currentPage()->nextId();
}

void TExportWizard::exportFile()
{
    
    // +++++ Create XML +++++
    
    QDomDocument xmlDocument;
    
    xmlDocument.appendChild(xmlDocument.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\""));
    QDomElement root = xmlDocument.createElement("doc");
    xmlDocument.appendChild(root);
    
    QDomElement head = xmlDocument.createElement("head");
    root.appendChild(head);
    
    QDomElement body = xmlDocument.createElement("body");
    root.appendChild(body);
    
    TTableModel *exportTableModel;
    
    try {
        exportTableModel = dynamic_cast<TTableModel *>(tableModel());
    } catch (const std::bad_cast&) {
        return;
    }
    
    QDomElement nameDomElement = xmlDocument.createElement("name");
    head.appendChild(nameDomElement);
    nameDomElement.appendChild(xmlDocument.createTextNode(exportTableModel->tableName()));
    
    QStringList fieldsStringList = field("columnsSelected").toStringList();
    
    for (int i = 0; i < fieldsStringList.size(); i++) {
        QDomElement field = xmlDocument.createElement("field");
        head.appendChild(field);
        QString caption = exportTableModel->headerData(exportTableModel->fieldIndex(fieldsStringList.at(i)), Qt::Horizontal).toString();
        field.appendChild(xmlDocument.createTextNode(caption));
        field.setAttribute("name", fieldsStringList.at(i));
    }
    
    for (int i = 0; i < exportTableModel->rowCount(); i++) {
        QDomElement rowDomElement = xmlDocument.createElement("row");
        body.appendChild(rowDomElement);
        for(int j = 0; j < fieldsStringList.count(); j++ ) {
            
            QString columnName = fieldsStringList.at(j);
            QModelIndex modelIndex = exportTableModel->index(i, exportTableModel->fieldIndex(columnName));
            QString dataString = exportTableModel->data(modelIndex).toString();
            
            QDomElement fieldDomElement = xmlDocument.createElement("field");
            rowDomElement.appendChild(fieldDomElement);
            
            fieldDomElement.appendChild(xmlDocument.createTextNode(dataString));
            fieldDomElement.setAttribute("name", fieldsStringList.at(j));
            
        }
    }
    
    // ----- Create XML -----
    
    // +++++ Transform XML +++++
    
    int format;
    if(field("textFormatRadioButton").toBool()) {
        format = TExportProcessor::textFormat;
    } else {
        format = TExportProcessor::htmlFormat;
    }
    
    exportProcessor = new TExportProcessor(xmlDocument.toString(0), field("fileName").toString(), format);
    progressDialog = new QProgressDialog(QString("Export from database"), QString("Cancel"), 0, 0, this, Qt::Dialog);
    QObject::connect(exportProcessor, SIGNAL(finished()), this, SLOT(done()));
    QObject::connect(progressDialog, SIGNAL(canceled()), exportProcessor, SLOT(terminate()));
    
    progressDialog->show();
    exportProcessor->start();
    
    // ----- Transform XML -----
    
}



void TExportWizard::done()
{
    progressDialog->hide();
    delete progressDialog;
    
    if(exportProcessor->statusCode() < 0) {
        QMessageBox messageBox(QMessageBox::Critical,
                               QString(tr("Critical error")),
                               tr("Cannot export from database."),
                               QMessageBox::Cancel,
                               this,
                               Qt::Dialog);
        messageBox.setInformativeText(exportProcessor->informativeErrorString());
        messageBox.setDetailedText(exportProcessor->detailedErrorString());
        messageBox.exec();
    }
    
    QWizard::done(1);
}

void TExportWizard::done(int result)
{
    if(result == 0) {
        QWizard::done(result);
    } else {
        exportFile();
    }
}

