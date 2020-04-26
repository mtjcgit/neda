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
#include <QSettings>
#include <QDebug>

#include "dbmanager.h"
#include "globalvar.h"

QString dbManager::newNmae, dbManager::newVer, dbManager::newDsc, dbManager::newType, 
	dbManager::newIcon, dbManager::newAuthor, dbManager::newEmail, dbManager::newInfo, dbManager::newDb, dbManager::newPath, dbManager::newDir;
QStringList dbManager::allDbList, dbManager::selectedList, dbManager::availableList;
QMultiMap<QString, QString> dbManager::fileMap,
			    dbManager::versMap,
			    dbManager::descMap,
			    dbManager::typeMap, 
			    dbManager::iconMap;

dbManager::dbManager()
{
}

void dbManager::loadDB( const QString &fileName )
{
  QSettings settings(fileName, QSettings::IniFormat);
  QString str0 = settings.value("NedaDatabase/Name").toString();
  if( !str0.isEmpty() ) {
    QFileInfo fi(fileName);
    QString dbfile = settings.value( "NedaDatabase/DBFile" ).toString();
    QString path = settings.value( "NedaDatabase/Path" ).toString();
    
    if (path.isEmpty()) {
      path = fi.absolutePath();
    }
    
    if (QFile::exists(path + "/" + dbfile)) {
      allDbList.append(str0);
      fileMap.insert(str0, path + "/" + dbfile);
      versMap.insert(str0, settings.value( "NedaDatabase/Version" ).toString());
      descMap.insert(str0, settings.value( "NedaDatabase/Description" ).toString());
      typeMap.insert(str0, settings.value( "NedaDatabase/Type" ).toString());

      if ( settings.value( "NedaDatabase/Icon" ).toString().startsWith( '/' ) )
	iconMap.insert(str0, settings.value( "NedaDatabase/Icon" ).toString());
      else
	iconMap.insert(str0, fi.absolutePath() + "/" + settings.value( "NedaDatabase/Icon" ).toString());
    } else {
      //qWarning("dbManager::loadDB can't find db file from identifier %s", qPrintable(fileName));
      return;
    }
    
  } else {
    return;
  }
}

void dbManager::loadAll()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  QStringList dbdirs = settings.value("directories/dbDires").toString().split(", ", QString::SkipEmptyParts);

  QStringList nameFilters;
  nameFilters.append(QLatin1String("*.desktop"));
  
  foreach (const QString dbdir, dbdirs) {
    QStringList subdirs =  QDir(dbdir).entryList( QDir::Dirs|QDir::NoDotAndDotDot );
    // FIXME remove empty!
    foreach (const QString subdir, subdirs) {
      QString subdir1 = dbdir + "/" + subdir;
      QDir subDir(subdir1);
      QFileInfoList infos = subDir.entryInfoList(nameFilters);
      QListIterator<QFileInfo> it(infos);
      while (it.hasNext()) {
	const QFileInfo fi = it.next();
	//QString filename = fi.absoluteFilePath();
	loadDB(fi.absoluteFilePath());
      }
    }
  }
}

void dbManager::reLoadAll()
{
  allDbList.clear();
  //availableList.clear();
  loadAll();
}

QStringList dbManager::foundDBs()
{
  return allDbList;
}

QStringList dbManager::availableDBs()
{
  availableList = allDbList;
  foreach (QString str, selectedList) {
    availableList.removeOne(str);
  }
  return availableList;
}

QStringList dbManager::selectedDBs()
{
  // FIXME disable selected but removed or unavailable db's.
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  selectedList = settings.value("databases/Selected").toString().split(", ", QString::SkipEmptyParts);
  return selectedList;
}

/*QStringList dbManager::dbbyTyple(const QString &type)
{
  const QList<QString> typeNames = typeMap.keys(type);
  return typeNames;
}*/

QString dbManager::file(const QString &plgName)
{
  return fileMap.find(plgName).value();
}

QString dbManager::version(const QString &plgName)
{
  return versMap.find(plgName).value();
}

QString dbManager::description(const QString &plgName)
{
  return descMap.find(plgName).value();
}

QString dbManager::type(const QString &plgName)
{
  return typeMap.find(plgName).value();
}

QString dbManager::icon(const QString &plgName)
{
  return iconMap.find(plgName).value();
}

bool dbManager::createNew()
{
  // FIXME check for existence
  QString filehelper = newPath + "/" + newInfo + "/" + newInfo + ".desktop";
  QSettings settings(filehelper, QSettings::IniFormat);
  settings.beginGroup("NedaDatabase");
  settings.setValue("Name", newNmae);
  settings.setValue("Version", newVer);
  settings.setValue("Description", newDsc);
  settings.setValue("Author", newAuthor);
  settings.setValue("E-mail", newEmail);
  settings.setValue("Icon", newIcon);
  settings.setValue("Type", newType);
  settings.setValue("Path", newDir);
  settings.setValue("DBFile", newDb);
  settings.endGroup();
  
  return 1;
}

void dbManager::setName(const QString &plgName)
{
  newNmae = plgName;
}

void dbManager::setVersion(const QString &plgName)
{
  newVer = plgName;
}

void dbManager::setDescription(const QString &plgName)
{
  newDsc = plgName;
}

void dbManager::setAuthor(const QString &plgName)
{
  newAuthor = plgName;
}

void dbManager::setEmail(const QString &plgName)
{
  newEmail = plgName;
}

void dbManager::setIcon(const QString &plgName)
{
  newIcon = plgName;
}

void dbManager::setType(const QString &plgName)
{
  newType = plgName;
}

void dbManager::setInfoName(const QString &plgName)
{
  newInfo = plgName;
}

void dbManager::setDbName(const QString &plgName)
{
  newDb = plgName;
}

void dbManager::setInfoPath(const QString &plgName)
{
  newPath = plgName;
}

void dbManager::setOutDir(const QString &plgName)
{
  newDir = plgName;
}
