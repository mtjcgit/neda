TEMPLATE=lib
MOC_DIR         = ../build/lib
OBJECTS_DIR     = ../build/lib

CONFIG += qt dll neda-buildlib
NEDA_LIBNAME = $$qtLibraryTarget(neda)
mac:CONFIG += absolute_library_soname
#win32|mac:!wince*:!win32-msvc:!macx-xcode:CONFIG += debug_and_release build_all
#include(.pri)
TARGET = $$NEDA_LIBNAME
#DESTDIR = $$PWD

win32-g++ {
  #RC_FILE   = ../windows/neda.rc
  include(../windows/mingw.pri)
  DLLDESTDIR = ..\\lib
  QMAKE_DISTCLEAN += ..\\lib\\$${NEDA_LIBNAME}.dll
  #RC_FILE   = ../windows/neda.rc
}

HEADERS        += ../src/globalvar.h     \
		  ../src/dbmanager.h     \
		  ../src/pluginmanager.h
SOURCES        += ../src/globalvar.cpp   \
		  ../src/dbmanager.cpp   \
		  ../src/pluginmanager.cpp

#target.path = $$DESTDIR
target.path  = $${PREFIX}/lib
INSTALLS += target
