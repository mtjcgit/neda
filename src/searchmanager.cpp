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

#include <QPluginLoader>
#include <QDebug>
#include "searchmanager.h"
#include "dbmanager.h"
#include "pluginmanager.h"
#include "plugins.h"
//#include "globalvar.h"

QString searchManager::findwrd(const QString &wrd)
{
  // NOTE object creation can move to pluginManager
  
  QString findetext, text;
  
  foreach (const QString sdb, dbManager::selectedDBs()) {
    //apply group of pluginManager::group(const QString &plgName)
    if (!pluginManager::plgsbyTyple(dbManager::type(sdb)).isEmpty()) {
      foreach (QString connection, pluginManager::plgsbyTyple(dbManager::type(sdb))) {
	if (pluginManager::selectedPlugins().contains(connection)) {
	  QString fileName = pluginManager::file(connection);
	  QPluginLoader loader(fileName);
	  QObject *plugin = loader.instance();
	  DatabasePlugin *iFilter = qobject_cast<DatabasePlugin *>(plugin);
	  if (iFilter) {
	    findetext = iFilter->searchWord(dbManager::file(sdb), wrd).replace("\n", "<br>", Qt::CaseSensitive);
	    if (!findetext.isEmpty()) {
	      findetext.prepend(QString("<h1>%1</h1>").arg(sdb));
	      text.append("<body>" + findetext + "</body>");
	      findetext.append("<br>");
	    }
	  }
	}
      }
    }
  }

  return text;
}
