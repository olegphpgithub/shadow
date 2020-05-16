#ifndef KMONEYDELEGATE
#define KMONEYDELEGATE

#include <QItemDelegate>
class QModelIndex;
class QSize;
class QLineEdit;
class QString;

class TMoneyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    TMoneyDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    mutable QString lastText;
};

#endif // KMONEYDELEGATE
