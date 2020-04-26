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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QMultiMap>

/*!
 \class pluginManager
 \brief This class provides management for plugins
*/

class pluginManager
{
public:
  //! load all plug ins.
  static void loadAll();
  //! load specified plug ins.
  static void loadPlugin( const QString &fileName );
  //! reload all plug ins.
  static void reLoadAll();
  //! create new database information file.
  static bool createNew(const QString &dbFile, const QString &type);

public:
  //! Return the list of all founded plug ins.
  static QStringList foundPlugins();
  //! Return the list of available plug ins.
  static QStringList availablePlugins();
  //! Return the list of selected plug ins.
  static QStringList selectedPlugins();
  //! Return the list of specified plug ins by type.
  static QStringList plgsbyTyple(const QString &type);
  //! Return the list of specified plug ins by group.
  static QStringList plgbyGroup(const QString &group);
  //! Return the check state of specified plug ins.
  static int checkState(const QString &plgName);
  //! Return the name of specified plug in by type.
  static QString plgbyTyple(const QString &type);
  //! Return the file of specified plug in.
  static QString file(const QString &plgName);
  //! Return the version of specified plug in.
  static QString version(const QString &plgName);
  //! Return the group of specified plug in.
  static QString group(const QString &plgName);
  //! Return the description of specified plug in.
  static QString description(const QString &plgName);
  //! Return the type of specified plug in.
  static QString type(const QString &plgName);
  //! Return the icon of specified plug in.
  static QString icon(const QString &plgName);
  //! Return the configuration state of specified plug in.
  static bool hasConfig(const QString &plgName);
  //! Return the state of edition.
  static bool isEditable(const QString &plgName);
  //
  //! Call open function of specified plug in type.
  static bool open(const QString &type, const QString &name);
  /**
   * Call store function for store key and value to database.
   * This function Never replace old data with new.
   */
  static bool store(const QString &key, const QString &value);
  /**
   * Call replace function for substitution value for this key to database.
   * This function Always replace old data with new.
   */
  static bool replace(const QString &key, const QString &value);
  //! Check current key
  static QString check(const QString &key);
  //! Delete current key
  static void remove(const QString &key);
  //! Close opened database
  static void close();
  
private:
  static QStringList allPluginsList, selectedList, availableList;
  static QMultiMap<QString, QString> fileMap, grpsMap, versMap, descMap, typeMap, iconMap;
  static QMultiMap<QString, bool> confMap, editmap;
  static QObject *plgn;
};

#endif
