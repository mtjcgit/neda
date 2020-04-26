/***************************************************************************
 *   Copyright (C) 2011 by Mohammad Taqi Jafari <mchemtux@users.sf.net>    *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include <QApplication>
#include <QSplashScreen>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMessageBox>

#include "globalvar.h"
#include "singleapplication.h"
#include "mainwindow.h"
#include "splashscreen.h"
#include "langmanager.h"
#include "pluginmanager.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setApplicationName(globalVar::appName());
  
#ifdef Q_WS_X11
  bool useGUI = getenv("DISPLAY") != 0;
#else
  //bool useGUI = true;
  bool useGUI = globalVar::isGuiEnabled();
#endif

  singleApplication app(argc, argv, useGUI);
  globalVar::parseArgs(argc, argv);
  if (app.isRunning()) {
    app.sendMessage(globalVar::reqWord());
    return 0;
  }
  
#ifdef PREFIX
  QString path = QString(PREFIX);
  if (!path.isEmpty())
    globalVar::setAppPath(path);
#else
  globalVar::setAppPath(app.applicationDirPath());
#endif
  
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  splashScreen *splash = 0;
  if (useGUI) {
    QPixmap pixmap(globalVar::dataPath() + "/splash.png");
    splash = new splashScreen( pixmap, Qt::WindowStaysOnTopHint );
    if (settings.value("generals/RunSplashOnStart").toBool()) {
      if (splash) splash->show();
    }
  } else {
    //startConsol();
  }
  
  if (splash) splash->message( "Load Languages..." );
  app.processEvents();
  langManager::loadAll();
  app.processEvents();
  if (splash) splash->message( "Load Plugins..." );
  app.processEvents();
  pluginManager::loadAll();
  app.processEvents();
  if (splash) splash->message( "Load Databases..." );
  app.processEvents();
  dbManager::loadAll();
  app.processEvents();
  if (splash) splash->message( "Starting GUI..." );
  app.processEvents();
  if (useGUI) {
    mainWindow *window = new mainWindow();
    QObject::connect(&app, SIGNAL(messageAvailable(const QString&)), window, SLOT(wordRequested(const QString&)));
    window->show();
    if (splash) splash->finish(window);
  }
  
  return app.exec();
  
}
