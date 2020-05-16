#ifndef TTHREADEXPORT_H
#define TTHREADEXPORT_H

#include <QThread>
#include <QSqlRelationalTableModel>
#include <QString>
#include "../../TDatabase/TDatabase.h"

class TThreadExport : public QThread
{
	Q_OBJECT
public:
	TThreadExport(QSqlRelationalTableModel *model, QString &fileName, int format);
	void run();
	
	QSqlRelationalTableModel *model;
	QString fileName;
	int format;
signals:
	void emitStatus(int value);
public slots:
};

#endif // TTHREADEXPORT_H
