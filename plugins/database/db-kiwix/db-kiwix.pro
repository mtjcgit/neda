TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
LIBS           += -lzim                  # link with libdict.a
HEADERS         = db-kiwix.h
SOURCES         = db-kiwix.cpp
TARGET          = $$qtLibraryTarget(dbkiwix)
#DESTDIR         = $${PREFIX}/lib/neda/plugins/db-kiwix
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0
QT             += network

win32-g++ {
  include(../../../windows/mingw.pri)
  #RC_FILE   = ../windows/neda.rc
  DESTDIR       = ../../../lib/neda/plugins/db-kiwix
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/db-kiwix\\\"
}

unix {
  DEFINES      += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/db-kiwix\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/db-kiwix
sources.path    = $${PREFIX}/lib/neda/plugins/db-kiwix
sources.files   = ReadMe kiwix.png
INSTALLS       += target sources
