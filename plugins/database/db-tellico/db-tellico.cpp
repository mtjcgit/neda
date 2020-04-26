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
#include <QtXml/QDomDocument>
#include <QDebug>

#include "db-tellico.h"

QString dbTellico::name() const
{ return QLatin1String("db-tellico"); }

QString dbTellico::group() const
{ return QLatin1String("database"); }

QString dbTellico::toolTip() const
{ return QLatin1String("This is tellico implementation plug in."); }

QString dbTellico::whatsThis() const
{ return QLatin1String("This is tellico implementation plug in."); }

QString dbTellico::type() const
{ return QLatin1String("tellico"); }

QString dbTellico::icon() const
{ return QLatin1String("db-tellico.png"); }

QString dbTellico::version() const
{ return QLatin1String("1.0.0"); }

QString dbTellico::description() const
{ return QLatin1String("Tellico collection manager"); }

QString dbTellico::searchWord(const QString &db, const QString &wrd)
{
  QString mean, title;
  QDomDocument doc(db);
  QFile file(db);
  if (doc.isNull()) {
    qDebug() << "Can not define database file" << endl;
  }
  if (!file.open(QIODevice::ReadOnly))
    qDebug() << "Can not open database file: " << file.fileName() << endl;
  if (!doc.setContent(&file)) {
    file.close();
    qDebug() << "Database file closed: " << file.fileName() << endl;
  }


  
  QDomNodeList entryelems = doc.elementsByTagName(QLatin1String("entry"));
  for(int j = 0; j < entryelems.count(); ++j) {
    QDomElement e = entryelems.item(j).toElement();
    if(e.isNull()) {
      continue;
    }
    title = e.namedItem(QLatin1String("title")).toElement().text();
    if (title == wrd) {
      mean = title;
      mean += QString("\n%1\n%2\n%3\n%4").arg(e.namedItem(QLatin1String("authors")).toElement().text(),e.namedItem(QLatin1String("isbn")).toElement().text(),e.namedItem(QLatin1String("publisher")).toElement().text(),e.namedItem(QLatin1String("cr_years")).toElement().text());
      //mean += "<img src=\"/usr/local/share/dicdb/tellico/images/";
      //mean += e.namedItem(QLatin1String("cover")).toElement().text();
      //mean += "\" alt=\"\" height=\"150\" width=\"95\" align=\"Right\">";
      mean += QString("<img src=\"/usr/local/share/dicdb/tellico/images/%1\" alt=\"\" height=\"150\" width=\"95\" align=\"Right\">").arg(e.namedItem(QLatin1String("cover")).toElement().text());
      break;
    }
    
    //QString n = e.namedItem(QLatin1String("id")).toElement().text();
  }
  
  
  return mean;
}

bool dbTellico::hasConfig() const
{
  return false;
}

bool dbTellico::isEditable() const
{
  return false;
}

QString dbTellico::config()
{
  QString cfg;
  
#ifdef PLUGINDIR
  cfg = QString(PLUGINDIR) + "/" + name() + ".ini";
#endif

  return cfg;
}

void dbTellico::saveSetting()
{
  /*QSettings settings(config(), QSettings::IniFormat);
  
  settings.setValue("generals/HostServer", hostComboBox->currentText());*/
}

QWidget *dbTellico::createConfWidget(QWidget* parent)
{
  /*QWidget *cnfWidget = new QWidget(parent);
  return cnfWidget;*/
}

void dbTellico::createNewDb(const QString &dbFile)
{
}

void dbTellico::open(const QString &dbFile)
{
}

bool dbTellico::store(const QString &key, const QString &value)
{
}

bool dbTellico::replace(const QString &key, const QString &value)
{
}

QString dbTellico::check(const QString &key)
{
}

void dbTellico::remove(const QString &key)
{
}

void dbTellico::close()
{
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(dbtellico, dbTellico);
QT_END_NAMESPACE
