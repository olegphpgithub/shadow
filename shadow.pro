HEADERS         =  TMainWindow.h \
                    lib/command/TNavigationCommand.h \
                    lib/database/TDatabase.h \
                    lib/database/TDatabaseStructure.h \
                    lib/database/TDatabaseStructureParser.h \
    lib/dialog/TExportWizard/TChooseFormatWizardPage.h \
    lib/dialog/TExportWizard/TExportWizard.h \
    lib/dialog/TExportWizard/TChooseColumnsWizardPage.h \
    lib/dialog/TExportWizard/TChooseFileWizardPage.h \
    lib/TMapModel.h \
    lib/dialog/TExportWizard/TExportProcessor.h

SOURCES         =  main.cpp \
                    TMainWindow.cpp \
                    lib/command/TNavigationCommand.cpp \
                    lib/database/TDatabase.cpp \
                    lib/database/TDatabaseStructure.cpp \
                    lib/database/TDatabaseStructureParser.cpp \
    lib/dialog/TExportWizard/TChooseFormatWizardPage.cpp \
    lib/dialog/TExportWizard/TExportWizard.cpp \
    lib/dialog/TExportWizard/TChooseColumnsWizardPage.cpp \
    lib/dialog/TExportWizard/TChooseFileWizardPage.cpp \
    lib/TMapModel.cpp \
    lib/dialog/TExportWizard/TExportProcessor.cpp

QT              += sql xml xmlpatterns
QT              += widgets
QT              += printsupport
CONFIG          += release
# CONFIG          += console
TRANSLATIONS    =  ru_RU.ts
FORMS           =  TMainWindow.ui \
    lib/dialog/TExportWizard/TChooseFormatWizardPage.ui \
    lib/dialog/TExportWizard/TExportWizard.ui \
    lib/dialog/TExportWizard/TChooseColumnsWizardPage.ui \
    lib/dialog/TExportWizard/TChooseFileWizardPage.ui
RESOURCES       =  resources.qrc
RC_FILE         =  shadow.rc



#+++ VIEW +++#
HEADERS         += lib/TTableView.h
SOURCES         += lib/TTableView.cpp
#--- VIEW ---#

#+++ MAPPER +++#
HEADERS         += lib/TTableMapper.h
SOURCES         += lib/TTableMapper.cpp
FORMS           += lib/TTableMapper.ui
#--- MAPPER ---#

#+++ MODEL +++#
HEADERS         += lib/TTableModel.h
SOURCES         += lib/TTableModel.cpp
#--- MODEL ---#


#+++ DELEGATES +++#
HEADERS         +=  lib/delegate/TIntDelegate.h \
                    lib/delegate/TMoneyDelegate.h \
                    lib/delegate/TDateDelegate.h \
                    lib/delegate/TDateTimeDelegate.h \
                    lib/delegate/TReadOnlyDelegate.h \
                    lib/delegate/TDoubleDelegate.h
                    
SOURCES         +=  lib/delegate/TIntDelegate.cpp \
                    lib/delegate/TMoneyDelegate.cpp \
                    lib/delegate/TDateDelegate.cpp \
                    lib/delegate/TDateTimeDelegate.cpp \
                    lib/delegate/TReadOnlyDelegate.cpp \
                    lib/delegate/TDoubleDelegate.cpp
#--- DELEGATES ---#


#+++ DIALOGS +++#
HEADERS         += lib/dialog/TConnectionDialog/TConnectionDialog.h
SOURCES         += lib/dialog/TConnectionDialog/TConnectionDialog.cpp
FORMS           += lib/dialog/TConnectionDialog/TConnectionDialog.ui
#--- DIALOGS ---#



DEFINES += "QXMLQUERY=1" # Do not modify this macro
DEFINES += "LIBXSLT=2" # Do not modify this macro


# Modify this option if you want to use QXMLQUERY or LIBXSLT
XSLTPROCESSOR=QXMLQUERY
#XSLTPROCESSOR=LIBXSLT

equals(XSLTPROCESSOR, QXMLQUERY) {
    
    DEFINES += "XSLTPROCESSOR=1"
    
}

equals(XSLTPROCESSOR, LIBXSLT) {
    
    DEFINES += "XSLTPROCESSOR=2"
    
    # zlib-1.2.8
    win32:INCLUDEPATH += C:\opt\zlib\include
    win32:LIBS += -L"C:\opt\zlib\lib" -lzlib
    
    # libiconv-1.9.2
    win32:INCLUDEPATH += C:\usr\include
    win32:LIBS += -L"C:\usr\lib" -liconv
    
    # libxml2-2.7.2
    win32:INCLUDEPATH += ext\libxml2\win32\include
    win32:LIBS += -L"ext\libxml2\win32\lib" -llibxml2
    unix:INCLUDEPATH += ext/libxml2/unix/include
    unix:LIBS += -Lext/libxml2/unix/lib -llibxml2
    
    # libxslt-1.1.26
    win32:INCLUDEPATH += ext\libxslt\win32\include
    win32:LIBS += -L"ext\libxslt\win32\lib" -llibxslt
    unix:INCLUDEPATH += ext/libxslt/unix/include
    unix:LIBS += -Lext/libxslt/unix/lib -llibxslt
    
}

