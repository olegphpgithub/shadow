#ifndef KTEXTDELEGATE_H
#define KTEXTDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QLineEdit>
#include <QString>

class TTextDelegate : public QItemDelegate
{
    Q_OBJECT
private:

public:
	TTextDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
	mutable QString lastText;
};

#endif // KTEXTDELEGATE_H
