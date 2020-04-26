TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
HEADERS         = db-tellico.h
SOURCES         = db-tellico.cpp
QT             += xml
TARGET          = $$qtLibraryTarget(dbtellico)
#DESTDIR         = $${PREFIX}/lib/neda/plugins/db-gdbm
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0

win32-g++ {
  include(../../../windows/mingw.pri)
  #RC_FILE   = ../windows/neda.rc
  DESTDIR       = ../../../lib/neda/plugins/db-tellico
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/db-tellico\\\"
}

unix {
  DEFINES      += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/db-tellico\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/db-tellico
sources.path    = $${PREFIX}/lib/neda/plugins/db-tellico
sources.files   = ReadMe db-tellico.png
INSTALLS       += target sources
