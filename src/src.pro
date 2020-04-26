#####################################################################
# Application
#####################################################################

TEMPLATE        = app
TARGET          = ../neda
MOC_DIR         = ../build
OBJECTS_DIR     = ../build
DEPENDPATH     += .
INCLUDEPATH    += .
QT             += network phonon

unix {
  # Prefix: base instalation directory
  isEmpty( PREFIX ){
    PREFIX=/usr/local
  }
  message(prefix: $$PREFIX)
  DEFINES += PREFIX=\\\"$${PREFIX}\\\"
}

win32-g++ {
  include(../windows/mingw.pri)
  RC_FILE   = ../windows/neda.rc
  DESTDIR   = ../bin/bin
}

exists(src/config.h){
  message(found: src/config.h)
  DEFINES += HAVE_CONFIG_H
}

# Input
HEADERS        += singleapplication.h        \
		  globalvar.h                \
		  lineedit.h                 \
		  mainwindow.h               \
		  splashscreen.h             \
		  trayicon.h                 \
		  langmanager.h              \
		  dbmanager.h                \
		  pluginmanager.h            \
		  searchmanager.h            \
		  searchbar.h                \
		  filechooser.h              \
		  switchlanguagedialog.h     \
		  tipdialog.h                \
		  aboutdialog.h              \
		  helpdialog.h               \
		  settingsdialog.h           \
		  settingspages.h            \
		  settingsgeneral.h          \
		  settingsdirs.h             \
		  settingsdb.h               \
		  settingsplugin.h           \
		  appearancewidget.h         \
		  behaviorwidget.h           \
		  colorswidget.h             \
		  fontswidget.h              \
		  iconswidget.h              \
		  notificationswidget.h      \
		  dbmngwidget.h              \
		  dbcnfwidget.h              \
		  dbselector.h               \
		  dbproperties.h             \
		  pluginselector.h           \
		  pluginproperties.h         \
		  pluginsettings.h           \
		  basepanel.h                \
		  resultbrowser.h            \
		  historyprovider.h          \
		  colorbutton.h              \
		  dbcreatewizard.h           \
		  dbeditor.h                      \
		  bookmarkmanager.h

SOURCES        += main.cpp                   \
		  singleapplication.cpp      \
		  globalvar.cpp              \
		  lineedit.cpp               \
		  mainwindow.cpp             \
		  splashscreen.cpp           \
		  trayicon.cpp               \
		  langmanager.cpp            \
		  dbmanager.cpp              \
		  pluginmanager.cpp          \
		  searchmanager.cpp          \
		  searchbar.cpp              \
		  filechooser.cpp            \
		  switchlanguagedialog.cpp   \
		  tipdialog.cpp              \
		  aboutdialog.cpp            \
		  helpdialog.cpp             \
		  settingsdialog.cpp         \
		  settingsgeneral.cpp        \
		  settingsdirs.cpp           \
		  settingsdb.cpp             \
		  settingsplugin.cpp         \
		  appearancewidget.cpp       \
		  behaviorwidget.cpp         \
		  colorswidget.cpp           \
		  fontswidget.cpp            \
		  iconswidget.cpp            \
		  notificationswidget.cpp    \
		  dbmngwidget.cpp            \
		  dbcnfwidget.cpp            \
		  dbselector.cpp             \
		  dbproperties.cpp           \
		  pluginselector.cpp         \
		  pluginproperties.cpp       \
		  pluginsettings.cpp         \
		  basepanel.cpp              \
		  resultbrowser.cpp          \
		  historyprovider.cpp        \
		  colorbutton.cpp            \
		  dbcreatewizard.cpp         \
		  dbeditor.cpp                      \
		  bookmarkmanager.cpp

TRANSLATIONS   += ../share/neda/translations/neda_en.ts \
		  ../share/neda/translations/neda_fa.ts 

### installations ####

target.path       += $${PREFIX}/bin
INSTALLS          += target

dev.path     = $${PREFIX}/include/neda
dev.files    = globalvar.h dbmanager.h pluginmanager.h plugins.h
INSTALLS     += dev
