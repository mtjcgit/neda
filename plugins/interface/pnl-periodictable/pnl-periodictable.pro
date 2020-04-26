TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
HEADERS         = pnl-periodictable.h
SOURCES         = pnl-periodictable.cpp
TARGET          = $$qtLibraryTarget(pnlperiodictable)
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0

win32-g++ {
  include(../../../windows/mingw.pri)
  #RC_FILE   = ../windows/neda.rc
  DESTDIR   = ../../../lib/neda/plugins/pnl-periodictable
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/pnl-periodictable\\\"
}

unix {
DEFINES += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/pnl-periodictable\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/pnl-periodictable
sources.path    = $${PREFIX}/lib/neda/plugins/pnl-periodictable
sources.files   = ReadMe objects qss
INSTALLS       += target sources
