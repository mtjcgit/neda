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

#include <QtGui>
#include <QDebug>
#include <QFileInfo>
#include <QTcpSocket>
#include <iostream>
#include <zim/file.h>
#include <zim/fileiterator.h>

#include "db-kiwix.h"

QString dbKiwix::name() const
{ return QLatin1String("db-kiwix"); }

QString dbKiwix::group() const
{ return QLatin1String("database"); }

QString dbKiwix::toolTip() const
{ return QLatin1String("This is kiwix implementation plug in."); }

QString dbKiwix::whatsThis() const
{ return QLatin1String("This is kiwix implementation plug in."); }

QString dbKiwix::type() const
{ return QLatin1String("kiwix"); }

QString dbKiwix::icon() const
{ return QLatin1String("kiwix.png"); }

QString dbKiwix::version() const
{ return QLatin1String("1.0.0"); }

QString dbKiwix::description() const
{ return QLatin1String("kiwix plugin..."); }

QString dbKiwix::searchWord(const QString &db, const QString &wrd)
{
  QString dbName, mean;
std::string std_title(wrd.toUtf8().constData());

  zim::File file(db.toStdString());
  zim::File::const_iterator it = file.findByTitle('A', std_title);
   if (it == file.end())
     qWarning() << "article not found";
//   if (it->isRedirect())
//   qDebug() << "see: " << it->getRedirectArticle().getTitle();
// else
   
  mean=QString::fromUtf8(it->getData().data(), it->getData().size());
//   QRegExp rxMetaViewport("<meta\\s[^>]*name\\s*=(\"viewport\"|'viewport')[^>]*>", Qt::CaseInsensitive);
//     data.replace(rxMetaViewport,QString("<meta name=\"viewport\" content=\"width=%1px, initial-scale=%2\">").arg(width).arg(scale));
 
  return mean;
}

bool dbKiwix::hasConfig() const
{
  return false;
}

bool dbKiwix::isEditable() const
{
  return false;
}

QString dbKiwix::config()
{
  QString cfg;
  
#ifdef PLUGINDIR
  cfg = QString(PLUGINDIR) + "/" + name() + ".ini";
#endif

  return cfg;
}

void dbKiwix::saveSetting()
{
  QSettings settings(config(), QSettings::IniFormat);
  
//   settings.setValue("generals/HostServer", hostComboBox->currentText());
}

QWidget *dbKiwix::createConfWidget(QWidget* parent)
{
  QWidget *cnfWidget = new QWidget(parent);
  return cnfWidget;
}


QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(dbkiwix, dbKiwix);
QT_END_NAMESPACE
