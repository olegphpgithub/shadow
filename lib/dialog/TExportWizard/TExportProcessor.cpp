#include "TExportProcessor.h"

#include <QtXml>
#include <QtXmlPatterns>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QtWidgets>

#if XSLTPROCESSOR == LIBXSLT

#include <libxslt/xslt.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#include <stdio.h>
#include <errno.h>

#define XSLTPLAIN ":/xsl/res/xslt1.0/exporttext.xsl"
#define XSLTHTML ":/xsl/res/xslt1.0/exporthtml.xsl"

void TExportProcessor::defaultLibxmlInternalErrorHandler(void* /* ctx */, const char **msg, va_list ap)
{
    QString tmpStr;
    detErrStr += tmpStr.vsprintf(*msg, ap);
}

void TExportProcessor::defaultLibxmlErrorHandler(void *ctx, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    defaultLibxmlInternalErrorHandler(ctx, &msg, args);
    va_end(args);
}


#elif XSLTPROCESSOR == QXMLQUERY
    
    #define XSLTPLAIN ":/xsl/res/xslt2.0/exporttext.xsl"
    #define XSLTHTML ":/xsl/res/xslt2.0/exporthtml.xsl"
    
#endif

QString TExportProcessor::detErrStr;

TExportProcessor::TExportProcessor(QString document, QString fileName, int format = TExportProcessor::textFormat)
{
    sourceDocument = document;
    exportFileName = fileName;
    exportFormat = format;
}

void TExportProcessor::run()
{
    
    // +++++ Transform XML +++++
    
    statCode = 0;
    
    try {
        
        // +++++ Getting stylesheets +++++
        
        QFile *xsltFile;
        
        if(exportFormat == TExportProcessor::textFormat) {
            xsltFile = new QFile(XSLTPLAIN);
        } else {
            xsltFile = new QFile(XSLTHTML);
        }
        
        QString xsltString;
        if (xsltFile->open(QFile::ReadOnly)) {
            QTextStream xsltTextStream(xsltFile);
            xsltString = xsltTextStream.readAll();
        } else {
            infErrStr = tr("Error while opening stylesheet file: \"%1\"").arg(xsltFile->fileName());
            throw(xsltFile->errorString());
        }
        
        // ----- Getting stylesheets -----
        
        #if XSLTPROCESSOR == LIBXSLT
            
            const char *params[1] = {NULL};
            xsltStylesheetPtr stylesheet = NULL;
            xmlDocPtr styleDoc, srcDoc, resultXmlDocPtr;
            
            xmlSetGenericErrorFunc(NULL, TExportProcessor::defaultLibxmlErrorHandler);
            xsltSetGenericErrorFunc(NULL, TExportProcessor::defaultLibxmlErrorHandler);
            
            xmlSubstituteEntitiesDefault(1);
            
            detErrStr = "";
            srcDoc = xmlParseDoc((const xmlChar*)sourceDocument.toUtf8().data());
            if(srcDoc == NULL) {
                infErrStr = tr("Error while parsing source XML document");
                throw(detErrStr);
            }
            
            
            detErrStr = "";
            styleDoc = xmlParseDoc((const xmlChar*)xsltString.toUtf8().data());
            if(styleDoc == NULL) {
                xmlFreeDoc(srcDoc);
                infErrStr = tr("Error while parsing stylesheet: \"%1\"").arg(xsltFile->fileName());
                throw(detErrStr);
            }
            
            detErrStr = "";
            stylesheet = xsltParseStylesheetDoc(styleDoc);
            if( (stylesheet == NULL) || (!detErrStr.isEmpty())) {
                xmlFreeDoc(srcDoc);
                xmlFreeDoc(styleDoc);
                infErrStr = tr("Error while compiling stylesheet: \"%1\"").arg(xsltFile->fileName());
                throw(detErrStr);
            }
            
            detErrStr = "";
            resultXmlDocPtr = xsltApplyStylesheet(stylesheet, srcDoc, params);
            if( (resultXmlDocPtr == NULL) || (!detErrStr.isEmpty())) {
                xsltFreeStylesheet(stylesheet); // Function also clear styleDoc [xmlFreeDoc(stylesheet->doc)]
                xmlFreeDoc(srcDoc);
                xmlFreeDoc(styleDoc);
                infErrStr = tr("Error while transforming source XML document");
                throw(detErrStr);
            }
            
            detErrStr = "";
            int bytes = xsltSaveResultToFilename(exportFileName.toStdString().c_str(), resultXmlDocPtr, stylesheet, 0);
            
            xsltFreeStylesheet(stylesheet); // Function also clear styleDoc [xmlFreeDoc(stylesheet->doc)]
            xmlFreeDoc(srcDoc);
            xmlFreeDoc(resultXmlDocPtr);
            xmlCleanupParser();
            xsltCleanupGlobals();
            
            if(bytes < 0) {
                infErrStr = tr("Error while saving to file: \"%1\"").arg(exportFileName);
                throw(detErrStr);
            }
            
        #elif XSLTPROCESSOR == QXMLQUERY
            
            QString out;
            QXmlQuery query(QXmlQuery::XSLT20);
            query.setFocus(sourceDocument);
            query.setQuery(xsltString);
            query.evaluateTo(&out);
            
            QFile exportFile(exportFileName);
            if(!exportFile.open(QIODevice::WriteOnly)) {
                infErrStr = tr("Error while opening file \"%1\" in write mode").arg(exportFileName);
                throw(tr("Cannot write to file"));
            }
            
            QTextStream outStream(&exportFile);
            outStream << out;
            exportFile.close();
            
        #endif
        
    } catch(QString exception) {
        statCode = -1;
        detErrStr = exception;
    }
    
    // ----- Transform XML -----
    
}

void TExportProcessor::terminate()
{
    QThread::terminate();
}

QString TExportProcessor::informativeErrorString()
{
    return infErrStr;
}

QString TExportProcessor::detailedErrorString()
{
    return detErrStr;
}
