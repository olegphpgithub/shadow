#include <QtWidgets>
#include "TMoneyDelegate.h"

//----------------------------------------------------------------------------------------------------
TMoneyDelegate::TMoneyDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}
//----------------------------------------------------------------------------------------------------
QWidget *TMoneyDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}
//----------------------------------------------------------------------------------------------------
void TMoneyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *moneyWidget = static_cast<QLineEdit *>(editor);
    lastText = index.model()->data(index, Qt::DisplayRole).toString();
    lastText.replace(".", QLocale::system().decimalPoint());
    moneyWidget->setText(lastText);
}
//----------------------------------------------------------------------------------------------------
void TMoneyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *moneyWidget = static_cast<QLineEdit *>(editor);
    
    QString number = (moneyWidget->text() != "") ? moneyWidget->text().replace(QLocale::system().decimalPoint(), ".").trimmed() : "0";
    
    QDoubleValidator moneyFormat(0, 999999999.99, 2, moneyWidget);
    
    int pos = 0;
    
    if(moneyFormat.validate(number, pos) == QValidator::Acceptable) {
        if(number != lastText)
            model->setData(index, QVariant(number).toDouble());
    } else {
        QMessageBox::warning(0, tr("User error"), tr("Invalid money format."), QMessageBox::Ok);
        model->setData(index, lastText);
    }
}
//----------------------------------------------------------------------------------------------------
void TMoneyDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
//----------------------------------------------------------------------------------------------------
