#include <QtWidgets>
#include "TReadOnlyDelegate.h"

//----------------------------------------------------------------------------------------------------
TReadOnlyDelegate::TReadOnlyDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}
//----------------------------------------------------------------------------------------------------
QWidget *TReadOnlyDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QLineEdit *editor = new QLineEdit(parent);
	editor->setReadOnly(true);
	return editor;
}
//----------------------------------------------------------------------------------------------------
void TReadOnlyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QLineEdit *widget = static_cast<QLineEdit *>(editor);
	widget->setText(index.data(Qt::DisplayRole).toString());
}
//----------------------------------------------------------------------------------------------------
void TReadOnlyDelegate::setModelData(QWidget * /* editor */, QAbstractItemModel * /* model */, const QModelIndex & /* index */) const
{
}
//----------------------------------------------------------------------------------------------------
void TReadOnlyDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
//----------------------------------------------------------------------------------------------------
