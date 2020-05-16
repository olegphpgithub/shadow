#ifndef KREADONLYDELEGATE_H
#define KREADONLYDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
class QSize;
class QLineEdit;
class QString;

class TReadOnlyDelegate : public QItemDelegate
{
	Q_OBJECT
private:

public:
	TReadOnlyDelegate(QObject *parent = 0);
	
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // KREADONLYDELEGATE_H
