#include "TDateTimeDelegate.h"

#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QDateTimeEdit>
#include <QtGui>

TDateTimeDelegate::TDateTimeDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

QWidget *TDateTimeDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QDateTimeEdit *editor = new QDateTimeEdit(parent);
	editor->setDisplayFormat("dd MMM yyyy HH:mm:ss");
	return editor;
}

void TDateTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QDateTimeEdit *dateWidget = static_cast<QDateTimeEdit *>(editor);
	qDebug() << index.data().toString();
	dateWidget->setDateTime(QDateTime::fromString(index.data().toString(), "dd MMM yyyy HH:mm:ss"));
}

void TDateTimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QDateTimeEdit *dateWidget = static_cast<QDateTimeEdit *>(editor);
	QDateTime today = dateWidget->dateTime();
	model->setData(index, today.toString("yyyy-MM-dd HH:mm:ss"));
}

void TDateTimeDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
