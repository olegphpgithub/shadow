#include <QtWidgets>
#include "TIntDelegate.h"

//----------------------------------------------------------------------------------------------------
TIntDelegate::TIntDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}
//----------------------------------------------------------------------------------------------------
QWidget *TIntDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QLineEdit *editor = new QLineEdit(parent);
	return editor;
}
//----------------------------------------------------------------------------------------------------
void TIntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QLineEdit *moneyWidget = static_cast<QLineEdit *>(editor);
	lastValue = index.model()->data(index, Qt::DisplayRole).toString();
	moneyWidget->setText(lastValue);
}
//----------------------------------------------------------------------------------------------------
void TIntDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QLineEdit *widget = static_cast<QLineEdit *>(editor);
	
	QString number = (widget->text() != "") ? widget->text().trimmed() : "0";
	
	QIntValidator IntFormat(widget);
	IntFormat.setBottom(0);
	int pos = 0;
	
	if(IntFormat.validate(number, pos) == QValidator::Acceptable) {
		if(number != lastValue)
			model->setData(index, QVariant(number).toInt());
	} else {
		QMessageBox::warning(0, tr("User error"), tr("Invalid integer format."), QMessageBox::Ok);
		model->setData(index, lastValue);
	}
}
//----------------------------------------------------------------------------------------------------
void TIntDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
//----------------------------------------------------------------------------------------------------
