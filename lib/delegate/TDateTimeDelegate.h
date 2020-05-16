#ifndef KDATETIMEDELEGATE_H
#define KDATETIMEDELEGATE_H

#include <QItemDelegate>
class QModelIndex;
class QObject;
class QSize;
class QDateTimeEdit;

class TDateTimeDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	TDateTimeDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // KDATETIMEDELEGATE_H
