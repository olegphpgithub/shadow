#include "TThreadExport.h"
#include <stdlib.h>

TThreadExport::TThreadExport(QSqlRelationalTableModel *model, QString &fileName, int format)
{
	this->model = model;
	this->fileName = fileName;
	this->format = format;
}

void TThreadExport::run()
{
	int i;
	
	for(i=0; i<5; i++) {
		sleep(1);
		emit emitStatus(20*i);
	}
	emit emitStatus(100);
}
