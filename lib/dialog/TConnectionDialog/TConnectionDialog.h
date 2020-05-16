#ifndef TCONNECTIONDIALOG_H
#define TCONNECTIONDIALOG_H

#include "../../../ui_TConnectionDialog.h"

class TConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    TConnectionDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
private:
    Ui::ConnectionDialog ui;
public slots:
    void accept();
    void reject();
};

#endif // TCONNECTIONDIALOG_H
