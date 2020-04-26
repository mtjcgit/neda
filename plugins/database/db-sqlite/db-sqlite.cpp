/***************************************************************************
 *   Copyright (C) 2014 by Mohammad Taqi Jafari <mchemtux@users.sf.net>    *
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

#include <QtGui>
#include <QDebug>
#include <QtSql/QtSql>

#include "db-sqlite.h"

QString dbSqlite::name() const
{ return QLatin1String("db-sqlite"); }

QString dbSqlite::group() const
{ return QLatin1String("database"); }

QString dbSqlite::toolTip() const
{ return QLatin1String("This is sqlite implementation plug in."); }

QString dbSqlite::whatsThis() const
{ return QLatin1String("This is sqlite implementation plug in."); }

QString dbSqlite::type() const
{ return QLatin1String("sqlite"); }

QString dbSqlite::icon() const
{ return QLatin1String("db-sqlite.png"); }

QString dbSqlite::version() const
{ return QLatin1String("1.0.0"); }

QString dbSqlite::description() const
{ return QLatin1String("Sqlite collection manager"); }

QString dbSqlite::searchWord(const QString &db, const QString &wrd)
{
  QString mean;
 
  QSqlDatabase dbf = QSqlDatabase::addDatabase("QSQLITE");
  dbf.setDatabaseName(db);
	
  if( !dbf.open() ){
    qDebug() << dbf.lastError();
    qDebug() << "Failed connect to db file.";
  }
  else{
    qDebug() << dbf.lastError();
    qDebug() << "connected to db.";
  }
  
  QSqlQuery query(dbf);
  qDebug() << dbf.lastError();
  QString aaaa = "SELECT * FROM JOURNALS WHERE DOI='" + wrd + "'";
  query.prepare(aaaa);
  query.exec();	
  qDebug() << dbf.lastError();
   while( query.next() ){
    mean.append("@article{" + query.value(0).toString() + ",\nauthor = \"" + query.value(1).toString() +"\",\ntitle = \"" + query.value(2).toString() +"\",\njournal = \"" + query.value(3).toString() +"\",\nvolume = \"" + query.value(4).toString() +"\",\nnumber = \"" + query.value(5).toString() +"\",\nyear = \"" + query.value(6).toString() +"\",\npages = \"" + query.value(7).toString() +"-" + query.value(8).toString()+"\"\n}");
//      mean.append(query.value(1).toString() + ", " + query.value(2).toString() + ", " + query.value(3).toString() + ", " + query.value(4).toString());
   }
  qDebug() <<mean;
  dbf.close();
  
  return mean;
}

bool dbSqlite::hasConfig() const
{
  return false;
}

bool dbSqlite::isEditable() const
{
  return false;
}

QString dbSqlite::config()
{
  QString cfg;
  
#ifdef PLUGINDIR
  cfg = QString(PLUGINDIR) + "/" + name() + ".ini";
#endif

  return cfg;
}

void dbSqlite::saveSetting()
{
  /*QSettings settings(config(), QSettings::IniFormat);
  
  settings.setValue("generals/HostServer", hostComboBox->currentText());*/
}

QWidget *dbSqlite::createConfWidget(QWidget* parent)
{
  /*QWidget *cnfWidget = new QWidget(parent);
  return cnfWidget;*/
}

void dbSqlite::createNewDb(const QString &dbFile)
{
}

void dbSqlite::open(const QString &dbFile)
{
}

bool dbSqlite::store(const QString &key, const QString &value)
{
}

bool dbSqlite::replace(const QString &key, const QString &value)
{
}

QString dbSqlite::check(const QString &key)
{
}

void dbSqlite::remove(const QString &key)
{
}

void dbSqlite::close()
{
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(dbsqlite, dbSqlite);
QT_END_NAMESPACE
