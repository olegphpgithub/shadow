#include "TTableMapper.h"
#include "TTableModel.h"

#include "database/TDatabase.h"
#include "database/TDatabaseStructure.h"
#include "delegate/TDateDelegate.h"

#include <QtWidgets>
#include <QtSql>
#include <QtXml>
#include <QtXmlPatterns>

//----------------------------------------------------------------------------------------------------

TTableMapper::TTableMapper(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    tableMapperUi.setupUi(this);
    connect(tableMapperUi.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(tableMapperUi.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    
    mapper = new QDataWidgetMapper(this);
    
    connect(tableMapperUi.previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(tableMapperUi.nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
    connect(tableMapperUi.addButton, SIGNAL(clicked()), this, SLOT(addNewRecord()));
    connect(tableMapperUi.removeButton, SIGNAL(clicked()), this, SLOT(removeCurrentRecord()));
}

//----------------------------------------------------------------------------------------------------

TTableMapper::~TTableMapper()
{
    
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::setModel(TTableModel *model)
{
    int i;
    
    QGridLayout *gridLayout = new QGridLayout();
    tableMapperUi.scrollAreaWidgetContents->setLayout(gridLayout);
    
    for(i=0; i<model->columnCount(); i++) {
        
        QLabel *label = new QLabel();
        label->setText(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        gridLayout->addWidget(label, i, 0, Qt::AlignRight);
        
    }
    
    mapper->setModel(model);
    
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    
    for(i=0; i<model->relationColumnStringList.count(); i++) {
        QString relationColumnString = model->relationColumnStringList.at(i);
        QComboBox *comboBox = new QComboBox();
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        QSqlTableModel *relationSqlTableModel = model->relationModel(model->columnStringList.indexOf(relationColumnString));
        comboBox->setModel(relationSqlTableModel);
        QSqlRelation sqlRelation = model->relation(model->columnStringList.indexOf(relationColumnString));
        comboBox->setModelColumn(relationSqlTableModel->fieldIndex(sqlRelation.displayColumn()));
        mapper->addMapping(comboBox, model->columnStringList.indexOf(relationColumnString));
        gridLayout->addWidget(comboBox, model->columnStringList.indexOf(relationColumnString), 1);
    }
    
    for(i=0; i<model->columnCount(); i++) {
        if(TDatabaseStructure::fieldEditorMap[model->tableName()].contains(model->columnStringList[i])) {
            QString editorString = TDatabaseStructure::fieldEditorMap[model->tableName()][model->columnStringList[i]];
            if(editorString == "spinBox") {
                
                QSpinBox *spinBox = new QSpinBox();
                spinBox->setMinimum(0);
                spinBox->setMaximum(2147483647);
                mapper->addMapping(spinBox, i);
                gridLayout->addWidget(spinBox, i, 1);
                
            } else if(editorString == "dateEdit") {
                
                QDateEdit *dateEdit = new QDateEdit();
                mapper->addMapping(dateEdit, i);
                gridLayout->addWidget(dateEdit, i, 1);
                
            } else if(editorString == "dateTimeEdit") {
                
                QDateTimeEdit *dateTimeEdit = new QDateTimeEdit();
                dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
                mapper->addMapping(dateTimeEdit, i);
                gridLayout->addWidget(dateTimeEdit, i, 1);
                
            } else if(editorString == "plainTextEdit") {
                
                QPlainTextEdit *textEdit = new QPlainTextEdit();
                mapper->addMapping(textEdit, i);
                gridLayout->addWidget(textEdit, i, 1);
                
            } else if(!model->relationColumnStringList.contains(model->columnStringList[i])) {
                
                QLineEdit *lineEdit = new QLineEdit();
                lineEdit->setAlignment(Qt::AlignLeft);
                mapper->addMapping(lineEdit, i);
                gridLayout->addWidget(lineEdit, i, 1);
                lineEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
                
            }
        } else {
        }
    }
    
    
    QSpacerItem *spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    gridLayout->addItem(spacerItem, model->columnCount(), 0);
    
    mapper->toFirst();
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::accept()
{
    QSqlTableModel *model;
    model = dynamic_cast<QSqlTableModel *>(mapper->model());
    mapper->submit();
    model->submitAll();
    QDialog::accept();
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::reject()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(mapper->model());
    mapper->revert();
    model->revertAll();
    QDialog::reject();
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::setCurrentIndex(int index)
{
    mapper->setCurrentIndex(index);
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::updateButtons(int row)
{
    tableMapperUi.previousButton->setEnabled(row > 0);
    tableMapperUi.nextButton->setEnabled(row < mapper->model()->rowCount() - 1);
    tableMapperUi.removeButton->setEnabled(mapper->model()->rowCount() > 0);
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::addNewRecord()
{
    TTableModel *model = dynamic_cast<TTableModel *>(mapper->model());
    QSqlRecord record;
    model->insertRecord(-1, record);
    mapper->toLast();
}

//----------------------------------------------------------------------------------------------------

void TTableMapper::removeCurrentRecord()
{
    mapper->model()->removeRow(mapper->currentIndex());
}

//----------------------------------------------------------------------------------------------------
