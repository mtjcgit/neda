TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
HEADERS         = db-sqlite.h
SOURCES         = db-sqlite.cpp
QT             += sql
TARGET          = $$qtLibraryTarget(dbsqlite)
#DESTDIR         = $${PREFIX}/lib/neda/plugins/db-gdbm
DEPENDPATH     += .
INCLUDEPATH    += .
VERSION         = 1.0.0

win32-g++ {
  include(../../../windows/mingw.pri)
  #RC_FILE   = ../windows/neda.rc
  DESTDIR       = ../../../lib/neda/plugins/db-sqlite
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/db-sqlite\\\"
}

unix {
  DEFINES      += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/db-sqlite\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/db-sqlite
sources.path    = $${PREFIX}/lib/neda/plugins/db-sqlite
sources.files   = ReadMe db-sqlite.png
INSTALLS       += target sources
