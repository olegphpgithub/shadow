#include <QtWidgets>
#include "TDoubleDelegate.h"

//----------------------------------------------------------------------------------------------------
TDoubleDelegate::TDoubleDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}
//----------------------------------------------------------------------------------------------------
QWidget *TDoubleDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}
//----------------------------------------------------------------------------------------------------
void TDoubleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QLineEdit *moneyWidget = static_cast<QLineEdit *>(editor);
	lastText = index.model()->data(index, Qt::DisplayRole).toString();
	lastText.replace(".", QLocale::system().decimalPoint());
	moneyWidget->setText(lastText);
}
//----------------------------------------------------------------------------------------------------
void TDoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QLineEdit *widget = static_cast<QLineEdit *>(editor);
	
	QString number = (widget->text() != "") ? widget->text().replace(QLocale::system().decimalPoint(), ".").trimmed() : "0";
	
	QDoubleValidator doubleFormat(widget);
	
	int pos = 0;
	
	if(doubleFormat.validate(number, pos) == QValidator::Acceptable) {
		if(number != lastText)
			model->setData(index, QVariant(number).toDouble());
	} else {
		QMessageBox::warning(0, tr("User error"), tr("Invalid floating point format."), QMessageBox::Ok);
	}
}
//----------------------------------------------------------------------------------------------------
void TDoubleDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
//----------------------------------------------------------------------------------------------------
