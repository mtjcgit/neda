TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
HEADERS         = pnl-history.h
SOURCES         = pnl-history.cpp
TARGET          = $$qtLibraryTarget(pnlhistory)
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0


win32 {
  include(../../../windows/mingw.pri)
  DESTDIR       = ../../../lib/neda/plugins/pnl-history
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/pnl-history\\\"
}

unix {
DEFINES        += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/pnl-history\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/pnl-history
sources.path    = $${PREFIX}/lib/neda/plugins/pnl-history
sources.files   = ReadMe actions historyrc
INSTALLS       += target sources
