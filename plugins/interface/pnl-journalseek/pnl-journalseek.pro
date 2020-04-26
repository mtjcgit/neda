TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
HEADERS         = pnl-journalseek.h doimanager.h
SOURCES         = pnl-journalseek.cpp doimanager.cpp
TARGET          = $$qtLibraryTarget(pnljournalseek)
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0
QT += network

win32-g++ {
  include(../../../windows/mingw.pri)
  #RC_FILE   = ../windows/neda.rc
  DESTDIR   = ../../../lib/neda/plugins/pnl-journalseek
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/pnl-journalseek\\\"
}

unix {
DEFINES += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/pnl-journalseek\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/pnl-journalseek
sources.path    = $${PREFIX}/lib/neda/plugins/pnl-journalseek
sources.files   = ReadMe objects plugins
INSTALLS       += target sources
