#include <QtGui>
#include "TDateDelegate.h"


TDateDelegate::TDateDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

QWidget *TDateDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QDateEdit *editor = new QDateEdit(parent);
	editor->setDisplayFormat("dd MMM yyyy");
	return editor;
}

void TDateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QDate today = QDate::fromString(index.model()->data(index, Qt::DisplayRole).toString(), "dd MMM yyyy");
	QDateEdit *dateWidget = static_cast<QDateEdit *>(editor);
	dateWidget->setDate(today);
}

void TDateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QDateEdit *dateWidget = static_cast<QDateEdit *>(editor);
	QDate today = dateWidget->date();
	model->setData(index, today.toString("yyyy-MM-dd"));
}

void TDateDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
