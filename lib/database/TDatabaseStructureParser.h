#ifndef TDATABASESTRUCTUREPARSER_H
#define TDATABASESTRUCTUREPARSER_H

#include <QThread>

class TDatabaseStructureParser : public QThread {
    Q_OBJECT
public:
    
    TDatabaseStructureParser();
    void run();
    
signals:
    void progress(int persent, const QString status);
    
};
#endif // TDATABASESTRUCTUREPARSER_H
