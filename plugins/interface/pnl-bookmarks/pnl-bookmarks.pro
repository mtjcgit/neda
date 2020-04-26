TEMPLATE        = lib
CONFIG         += plugin
INCLUDEPATH    += ../../../src
HEADERS         = pnl-bookmarks.h xbelreader.h treeproxymodel.h
SOURCES         = pnl-bookmarks.cpp xbelreader.cpp treeproxymodel.cpp
TARGET          = $$qtLibraryTarget(pnlbookmarks)
DEPENDPATH     += .
INCLUDEPATH    += .
QT             += xml
VERSION         = 1.0.0


win32 {
  include(../../../windows/mingw.pri)
  DESTDIR       = ../../../lib/neda/plugins/pnl-bookmarks
  DEFINES      += PLUGINDIR=\\\"lib/neda/plugins/pnl-bookmarks\\\"
}

unix {
DEFINES        += PLUGINDIR=\\\"$${PREFIX}/lib/neda/plugins/pnl-bookmarks\\\"
}

### installations ####
target.path     = $${PREFIX}/lib/neda/plugins/pnl-bookmarks
sources.path    = $${PREFIX}/lib/neda/plugins/pnl-bookmarks
sources.files   = ReadMe actions
INSTALLS       += target sources
