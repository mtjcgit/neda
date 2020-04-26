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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMultiMap>
#include <QStringList>

/*!
 \class dbManager
 \brief This class provides management for databases
*/

class dbManager
{
public:
  //! Constructor of database manager.
  dbManager();
  
public:
  //! load all databases.
  static void loadAll();
  //! load specified databases.
  static void loadDB( const QString &fileName );
  //! reload all databases.
  static void reLoadAll();
  //! create new database information file.
  static bool createNew();
  
public:
  //! Return the list of all founded databases.
  static QStringList foundDBs();
  //! Return the list of available databases.
  static QStringList availableDBs();
  //! Return the list of selected databases.
  static QStringList selectedDBs();
  /*//! Return the list of specified databases by type in available databases.
  static QStringList dbbyTyple(const QString &type);*/
  //! Return the file of specified database.
  static QString file(const QString &plgName);
  //! Return the version of specified database.
  static QString version(const QString &plgName);
  //! Return the description of specified database.
  static QString description(const QString &plgName);
  //! Return the type of specified database.
  static QString type(const QString &plgName);
  //! Return the icon of specified database.
  static QString icon(const QString &plgName);
  //
  static void setName(const QString &plgName);
  static void setVersion(const QString &plgName);
  static void setDescription(const QString &plgName);
  static void setAuthor(const QString &plgName);
  static void setEmail(const QString &plgName);
  static void setIcon(const QString &plgName);
  static void setType(const QString &plgName);
  static void setInfoName(const QString &plgName);
  static void setDbName(const QString &plgName);
  static void setInfoPath(const QString &plgName);
  static void setOutDir(const QString &plgName);

private:
  static QStringList allDbList, selectedList, availableList;
  static QMultiMap<QString, QString> fileMap, versMap, descMap, typeMap, iconMap;
  static QString newNmae, newVer, newDsc, newType, newIcon, newAuthor, newEmail, newInfo, newDb, newPath, newDir;
};

#endif
