#####################################################################
# Main project file
#####################################################################

TEMPLATE      = subdirs
CONFIG       += ordered

#process the projects
NEDA_BUILD_PARTS = app plugins lib doc

for(PROJECT, $$list($$lower($$unique(NEDA_BUILD_PARTS)))) {
  isEqual(PROJECT, app) {
    SUBDIRS  += src
  } else:isEqual(PROJECT, plugins) {
    SUBDIRS  += plugins
  } else:isEqual(PROJECT, lib) {
    SUBDIRS  += libdev
  } else:isEqual(PROJECT, doc) {
    #include(doc/doc.pri)
  }
}

### installations ####

data.path     = $${PREFIX}/share/neda
data.files    = share/neda/*
INSTALLS     += data

desktop.path  = $${PREFIX}/share/applications
desktop.files = share/applications/neda.desktop
INSTALLS     += desktop

icons.path  = $${PREFIX}/share/icons
icons.files = share/hicolor
INSTALLS     += icons

pixmaps.path  = $${PREFIX}/share/pixmaps
pixmaps.files = share/pixmaps/neda.png
INSTALLS     += pixmaps