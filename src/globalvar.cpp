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

#include "globalvar.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <QFile>
#include <QDir>
#include <QDebug>

bool globalVar::gui_bool;
QString globalVar::app_path;
QString globalVar::ini_path;
QString globalVar::req_word;

QString globalVar::appName() {
  return "neda";
}

QString globalVar::appVersion() {
  return "1.0.0";
}

QString globalVar::shortDescription()
{
  return "dictionary";
}

QString globalVar::copyrightStatement()
{
  return "(C) 2009-2011 Mohammad Taqi Jafari";
}

QString globalVar::author()
{
  return "Mohammad Taqi Jafari \"mchemtux@users.sf.net\"";
}

QString globalVar::thanks()
{
  QString tnk;
  tnk = "Oxygen Project \"www.oxygen-icons.org\"";
  tnk += "<br />";
  tnk += "Open Clip Art \"www.openclipart.org\"";
  return tnk;
}

QString globalVar::homepage()
{
  return "";
}

QString globalVar::licenseFile()
{
  QString lf;
  if (QFile::exists( "/usr/share/common-licenses/GPL-3" ) ) {
    lf = "/usr/share/common-licenses/GPL-3";
  } else {
    lf = dataPath() + "/COPYING";
  }
  return lf;
}

QString globalVar::appHomePath() {
#ifndef Q_OS_WIN
  return QDir::homePath() + "/.config/" + appName();
#else
  return QDir::homePath() + "/." + appName();
#endif
}

void globalVar::setGuiEnabled(bool g) {
  gui_bool = g;
}

void globalVar::setAppPath(QString path) {
  app_path = path;
  QDir home;
  if (!home.exists( appHomePath() ) ) {
    home.mkdir ( globalVar::appHomePath() );
  }
  
  if (QFile::exists( dataPath() + "/" + appName() + "rc" )) {
    QFile::copy ( dataPath() + "/" + appName() + "rc", appHomePath() + "/" + appName() + ".ini" );
  }
}

QString globalVar::appPath() {
  return app_path;
}

QString globalVar::libPath() {
  return appPath() + "/lib/" + appName();
}

QString globalVar::dataPath() {
  return appPath() + "/share/" + appName();
}

QString globalVar::defaultLanguage()
{
  return "en";
}

QString globalVar::defaultThemeName() {
  return QLatin1String("oxygen");
}

QString globalVar::defaultIconSize()
{
  return "22";
}

QString globalVar::defaultIcons(QString size, QString cat)
{
  if (size.isEmpty())
    size = defaultIconSize();
  return dataPath() + "/icons/oxygen/" + size + "x" + size + "/" + cat;
}

QString globalVar::tips() {
  return dataPath() + "/tips";
}

QString globalVar::helps() {
  return dataPath() + "/helps";
}

QString globalVar::config() {
  if (QFile::exists( appPath() + "/" + appName() + ".ini" )) {
    ini_path = appPath() + "/" + appName() + ".ini";
  } else {
    ini_path = appHomePath() + "/" + appName() + ".ini";
  }
  return ini_path;
}

QString globalVar::words() {
  QString wl;
  if (QFile::exists( dataPath() + "/dict/words" ) ) {
    wl = dataPath() + "/dict/words";
  } else if (QFile::exists("/usr/share/dict/words" ) ){
    wl = "/usr/share/dict/words";
  }
  return wl;
}

QString globalVar::translations() {
  return dataPath() + "/translations";
}

QString globalVar::history()
{
  return appHomePath() + "/history";
}

QStringList globalVar::plugins() {
  QStringList plgndir;
  plgndir << globalVar::libPath() + "/plugins" << dataPath() + "/plugins" << appHomePath()  + "/plugins" << "./plugins";
  return plgndir;
}

QString globalVar::reqWord()
{
  return req_word;
}

bool globalVar::isGuiEnabled() {
  return gui_bool;
}

void globalVar::parseArgs(int argc, char *argv[]) {
  /*some arguments should be processed before others. Handle them now:*/
  /*for (int i=1; i < argc; i++) {
  }*/
  
  /*Handle the rest of the arguments. They may override attributes already set:*/
  for (int i=1; i < argc; ++i){
    QString arg = argv[i];
    if (arg == QLatin1String("-h") || arg == QLatin1String("--help")) {
      gui_bool = false;
      qDebug() << "Usage: " << appName() << "[options] [WORD]";
      //FIXME exit
    } else if (arg == QLatin1String("-w") || arg == QLatin1String("--word")) {
      ++i;
      if (i == argc) {
	qWarning("The option -w or --word requires a parameter.");
	return;
      }
      req_word = argv[i];
      continue;
    }      
  }
}
