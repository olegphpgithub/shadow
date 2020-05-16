#ifndef TTABLEMAPPER_H
#define TTABLEMAPPER_H

#include "../ui_TTableMapper.h"
#include "TTableModel.h"

#include <QDialog>

class QDataWidgetMapper;

class TTableMapper : public QDialog
{
    Q_OBJECT
public:
    
    TTableMapper(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~TTableMapper();
    void setModel(TTableModel *model);
    virtual void setCurrentIndex(int index);
    
public slots:
    
    void accept();
    void reject();
    void updateButtons(int row);
    
    virtual void addNewRecord();
    virtual void removeCurrentRecord();
    
signals:
    
protected:
    
    Ui::TTableMapper tableMapperUi;
    
    QDataWidgetMapper *mapper;
    
};

#endif // TTABLEMAPPER_H
