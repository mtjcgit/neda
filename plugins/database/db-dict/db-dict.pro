TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
#LIBS           += -ldict                  # link with libdict.a
HEADERS         = db-dict.h
SOURCES         = db-dict.cpp
TARGET          = $$qtLibraryTarget(dbdict)
#DESTDIR         = $${PREFIX}/lib/neda/plugins/db-dict
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0
QT             += network

win32-g++ {
  include(../../../windows/mingw.pri)
  #RC_FILE   = ../windows/neda.rc
  DESTDIR       = ../../../lib/neda/plugins/db-dict
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/db-dict\\\"
}

unix {
  DEFINES      += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/db-dict\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/db-dict
sources.path    = $${PREFIX}/lib/neda/plugins/db-dict
sources.files   = ReadMe dict.org-231x64.png db-dict.ini
INSTALLS       += target sources
