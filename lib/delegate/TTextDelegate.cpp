#include <QtGui>
#include "TTextDelegate.h"

//----------------------------------------------------------------------------------------------------
TTextDelegate::TTextDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}
//----------------------------------------------------------------------------------------------------
QWidget *TTextDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QLineEdit *editor = new QLineEdit(parent);
	return editor;
}
//----------------------------------------------------------------------------------------------------
void TTextDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QLineEdit *editWidget = static_cast<QLineEdit *>(editor);
	lastText = index.model()->data(index, Qt::DisplayRole).toString();
	editWidget->setText(lastText);
}
//----------------------------------------------------------------------------------------------------
void TTextDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QLineEdit *editWidget = static_cast<QLineEdit *>(editor);
	QString str = editWidget->text().trimmed();
	model->setData(index, str);
}
//----------------------------------------------------------------------------------------------------
void TTextDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
//----------------------------------------------------------------------------------------------------
