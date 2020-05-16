#ifndef TEXPORTPROCESSOR_H
#define TEXPORTPROCESSOR_H

#include <QThread>

class QString;
class QFile;

class TExportProcessor : public QThread {
    Q_OBJECT
public:
    TExportProcessor(QString document, QString fileName, int format);
    void run();
    
    enum exportFormat { textFormat, htmlFormat };
    
    int statusCode() { return statCode; }
    QString informativeErrorString();
    QString detailedErrorString();
    
private:
    QString sourceDocument;
    QString exportFileName;
    int exportFormat;
    
    int statCode;
    QString infErrStr;
    static QString detErrStr;
    
    #if XSLTPROCESSOR == LIBXSLT
    
    static void defaultLibxmlInternalErrorHandler(void* /* ctx */, const char **msg, va_list ap);
    static void defaultLibxmlErrorHandler(void *ctx, const char *msg, ...);
    
    #endif
    
public slots:
    void terminate();
};

#endif // TEXPORTPROCESSOR_H
