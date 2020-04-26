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

#include <QDir>
#include <QTranslator>
#include <QApplication>
#include <QLocale>
#include <QDebug>
#include <QLibraryInfo>
#include <QSettings>
#include "langmanager.h"
#include "globalvar.h"

QStringList langManager::localsList;
QMultiMap<QString, QString> langManager::fileMap, 
			    langManager::langMap,
			    langManager::counMap,
			    langManager::authMap,
			    langManager::contMap;
QTranslator langManager::appTranslator;
QTranslator langManager::qtTranslator;

void langManager::loadLang( const QString &fileName )
{
  QString locale = fileName;
  locale.remove(0, locale.indexOf('_') + 1);
  locale.truncate(locale.lastIndexOf('.'));
        
  QTranslator translator;
  translator.load(fileName, globalVar::translations());
  
  if( !locale.isEmpty() ) {
    localsList.append(locale);
    fileMap.insert(locale, fileName);
    langMap.insert(locale, translator.translate("langmanager", "Language"));
    counMap.insert(locale, translator.translate("langmanager", "Country"));
    authMap.insert(locale, translator.translate("langmanager", "Author"));
    contMap.insert(locale, translator.translate("langmanager", "Contact"));
  } else {
    return;
  }
}

void langManager::loadAll()
{
  /* FIXME search for home and standard Qt translation dir from lib.*/
  
  QDir dir(globalVar::translations());
  QStringList langNames = dir.entryList(QStringList(globalVar::appName() + "_*.qm"));
  
  foreach (const QString langName, langNames) {
    loadLang(langName);
  }
}

QStringList langManager::foundLangs()
{
  return localsList;
}

QString langManager::file(const QString &trnsName)
{
  return fileMap.find(trnsName).value();
}

QString langManager::lang(const QString &trnsName)
{
  return langMap.find(trnsName).value();
}

QString langManager::coun(const QString &trnsName)
{
  return counMap.find(trnsName).value();
}

QString langManager::auth(const QString &trnsName)
{
  return authMap.find(trnsName).value();
}

QString langManager::cont(const QString &trnsName)
{
  return contMap.find(trnsName).value();
}

int langManager::index(const QString &trnsName)
{
  return localsList.indexOf(trnsName);
}

QString langManager::current()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  QString lang;
  if (settings.value("generals/Language").toBool()) {
    lang = settings.value("generals/Language").toString();
  } else {
    lang = globalVar::defaultLanguage();
  }
  return lang;
}

void langManager::changeLang(QString &locale)
{
  // FIXME :check existence of selected local
  if (locale.isEmpty()) {
    locale = QLocale::system().name();
  }
  
  appTranslator.load(file(locale), globalVar::translations());

  QString transPath;
  QStringList transPaths;
  transPaths << QLibraryInfo::location(QLibraryInfo::TranslationsPath) << globalVar::translations();
  
  foreach (const QString tsPath, transPaths) {
    if (QFile::exists(tsPath + "/qt_" + locale + ".qm")) {
      transPath = tsPath;
    }
  }
  qtTranslator.load("qt_" + locale + ".qm", transPath);
  
  qApp->installTranslator(&appTranslator);
  qApp->installTranslator(&qtTranslator);
}
