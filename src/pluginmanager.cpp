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
#include <QPluginLoader>
#include <QList>

#include "plugins.h"
#include "pluginmanager.h"
#include "globalvar.h"

QStringList pluginManager::allPluginsList,
	    pluginManager::selectedList,
	    pluginManager::availableList;
QMultiMap<QString, QString> pluginManager::fileMap,
			    pluginManager::grpsMap,
			    pluginManager::versMap,
			    pluginManager::descMap,
			    pluginManager::typeMap, 
			    pluginManager::iconMap;
QMultiMap<QString, bool> pluginManager::confMap, 
			 pluginManager::editmap;

QObject *pluginManager::plgn;

void pluginManager::loadPlugin( const QString &fileName )
{
  QPluginLoader loader(fileName);
  QObject *plugin = loader.instance();
  if (plugin) {
    //allPluginsList.append(fileName);
    //qDebug() << allPluginsList;
    /**CommonPlugin*/
    CommonPlugin *iCommon = qobject_cast<CommonPlugin *>(plugin);
    if (iCommon) {
      fileMap.insert(iCommon->name(), fileName);
      allPluginsList.append(iCommon->name());
      typeMap.insert(iCommon->name(), iCommon->type());
      iconMap.insert(iCommon->name(), QFileInfo(fileName).absolutePath() + "/" + iCommon->icon());
      grpsMap.insert(iCommon->name(), iCommon->group());
      versMap.insert(iCommon->name(), iCommon->version());
      descMap.insert(iCommon->name(), iCommon->description());
      confMap.insert(iCommon->name(), iCommon->hasConfig());
      //typeMap.insert(iCommon->name(), iCommon->group());
     // iconMap.insert(iCommon->name(), iCommon->toolTip());
    }
    /**DatabasePlugin*/
    DatabasePlugin *iDatabase = qobject_cast<DatabasePlugin *>(plugin);
    if (iDatabase) {
      fileMap.insert(iDatabase->name(), fileName);
      allPluginsList.append(iDatabase->name());
      typeMap.insert(iDatabase->name(), iDatabase->type());
      iconMap.insert(iDatabase->name(), QFileInfo(fileName).absolutePath() + "/" + iDatabase->icon());
      grpsMap.insert(iDatabase->name(), iDatabase->group());
      versMap.insert(iDatabase->name(), iDatabase->version());
      descMap.insert(iDatabase->name(), iDatabase->description());
      confMap.insert(iDatabase->name(), iDatabase->hasConfig());
      editmap.insert(iDatabase->name(), iDatabase->isEditable());
      //typeMap.insert(iDatabase->name(), iDatabase->group());
     // iconMap.insert(iDatabase->name(), iDatabase->toolTip());
    }
    /**InterfacePlugin*/
    InterfacePlugin *iInterface = qobject_cast<InterfacePlugin *>(plugin);
    if (iInterface) {
      fileMap.insert(iInterface->name(), fileName);
      allPluginsList.append(iInterface->name());
      typeMap.insert(iInterface->name(), iInterface->type());
      iconMap.insert(iInterface->name(), QFileInfo(fileName).absolutePath() + "/" + iInterface->icon());
      grpsMap.insert(iInterface->name(), iInterface->group());
      versMap.insert(iInterface->name(), iInterface->version());
      descMap.insert(iInterface->name(), iInterface->description());
      confMap.insert(iInterface->name(), iInterface->hasConfig());
      //typeMap.insert(iInterface->name(), iInterface->group());
     // iconMap.insert(iInterface->name(), iInterface->toolTip());
    }
  }


}

void pluginManager::loadAll()
{
  QStringList plgdirs = globalVar::plugins();
  QStringList nameFilters;
  
#if defined(Q_OS_LINUX)
  nameFilters.append(QLatin1String("*.so"));
#elif defined(Q_OS_WIN32) || defined(Q_OS_WINCE)
  nameFilters.append(QLatin1String("*.dll"));
//#elif defined(Q_OS_MAC)
//  nameFilters.append(QLatin1String("*.dylib"));
#endif

  //nameFilters.append(QLatin1String("*.desktop"));
  foreach (const QString plgdir, plgdirs) {
    QStringList subdirs =  QDir(plgdir).entryList( QDir::Dirs|QDir::NoDotAndDotDot );
    // FIXME remove empty!
    foreach (const QString subdir, subdirs) {
      QString subdir1 = plgdir + "/" + subdir;
      QDir subDir(subdir1);
      QFileInfoList infos = subDir.entryInfoList(nameFilters);
      QListIterator<QFileInfo> it(infos);
      while (it.hasNext()) {
	const QFileInfo fi = it.next();
	loadPlugin(fi.absoluteFilePath());
      }
    }
  }
/*
foreach (QString fileName, subDir.entryList(QDir::Files)) {
	qDebug() << infos;
}
*/
}

void pluginManager::reLoadAll()
{
  allPluginsList.clear();
  loadAll();
}

bool pluginManager::createNew(const QString &dbFile, const QString &type)
{
  foreach (QString connection, plgsbyTyple(type)) {
    QString fileName = file(connection);
    QPluginLoader loader(fileName);
    QObject *plugin = loader.instance();
    if (plugin) {
      DatabasePlugin *nDatabase = qobject_cast<DatabasePlugin *>(plugin);
      if (nDatabase)
	nDatabase->createNewDb(dbFile);
      else
	return false;
    }
  }
  return true;
}

QStringList pluginManager::foundPlugins()
{
  return allPluginsList;
}

QStringList pluginManager::availablePlugins()
{
  return availableList;
}

QStringList pluginManager::selectedPlugins()
{
  selectedList.clear();
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.beginGroup("plugins");
  QStringList keys = settings.allKeys();
  foreach (QString key, keys) {
    selectedList << settings.value(QString("%1").arg(key)).toString().split(", ", QString::SkipEmptyParts);
  }
  //selectedList = settings.value(QString("plugins/%1").arg()).toString().split(", ", QString::SkipEmptyParts);
  return selectedList;
}

QStringList pluginManager::plgsbyTyple(const QString &type)
{
  const QList<QString> typeNames = typeMap.keys(type);
  return typeNames;
}

QStringList pluginManager::plgbyGroup(const QString &group)
{
  const QList<QString> groupNames = grpsMap.keys(group);
  return groupNames;
}

int pluginManager::checkState(const QString &plgName)
{
  // NOTE improve for partly selection!
  if (selectedList.contains(plgName))
    return 2;
  else
    return 0;
}

QString pluginManager::plgbyTyple(const QString &type)
{
  return typeMap.key(type);
}

QString pluginManager::file(const QString &plgName)
{
  return fileMap.find(plgName).value();
}

QString pluginManager::group(const QString &plgName)
{
  return grpsMap.find(plgName).value();
}

QString pluginManager::version(const QString &plgName)
{
  return versMap.find(plgName).value();
}

QString pluginManager::description(const QString &plgName)
{
  return descMap.find(plgName).value();
}

QString pluginManager::type(const QString &plgName)
{
  return typeMap.find(plgName).value();
}

QString pluginManager::icon(const QString &plgName)
{
  return iconMap.find(plgName).value();
}

bool pluginManager::hasConfig(const QString &plgName)
{
  return confMap.find(plgName).value();
}

bool pluginManager::isEditable(const QString &plgName)
{
  return editmap.find(plgName).value();
}

bool pluginManager::open(const QString &type, const QString &name)
{
  QPluginLoader loader(file(plgbyTyple(type)));
  if (!loader.isLoaded())
    plgn = loader.instance();
  
  if (plgn) {
    DatabasePlugin *eDatabase = qobject_cast<DatabasePlugin *>(plgn);
    if (eDatabase)
      eDatabase->open(name);
    else
      return false;
  }
  
  return loader.isLoaded();
}

bool pluginManager::store(const QString &key, const QString &value)
{
  if (plgn) {
    DatabasePlugin *eDatabase = qobject_cast<DatabasePlugin *>(plgn);
    if (eDatabase)
      return eDatabase->store(key, value);
    else
      return false;
  }
}

bool pluginManager::replace(const QString &key, const QString &value)
{
  if (plgn) {
    DatabasePlugin *eDatabase = qobject_cast<DatabasePlugin *>(plgn);
    if (eDatabase)
      return eDatabase->replace(key, value);
    else
      return false;
  }
}

QString pluginManager::check(const QString &key)
{
  if (plgn) {
    DatabasePlugin *eDatabase = qobject_cast<DatabasePlugin *>(plgn);
    if (eDatabase)
      return eDatabase->check(key);
  }
}

void pluginManager::remove(const QString &key)
{
  if (plgn) {
    DatabasePlugin *eDatabase = qobject_cast<DatabasePlugin *>(plgn);
    if (eDatabase)
      eDatabase->remove(key);
  }
}

void pluginManager::close()
{
  if (plgn) {
    DatabasePlugin *eDatabase = qobject_cast<DatabasePlugin *>(plgn);
    if (eDatabase)
      eDatabase->close();
  }
}
