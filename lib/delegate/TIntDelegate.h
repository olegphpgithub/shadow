#ifndef KINTDELEGATE
#define KINTDELEGATE

#include <QItemDelegate>
class QModelIndex;
class QSize;
class QLineEdit;
class QString;

class TIntDelegate : public QItemDelegate
{
	Q_OBJECT
private:

public:
	TIntDelegate(QObject *parent = 0);
	
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
	mutable QString lastValue;
};

#endif // INTEGERDELEGATE
