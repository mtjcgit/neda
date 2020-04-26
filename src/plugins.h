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

/*!
   \file plugins.h

   Header file for provider implementation classes (plugins)
*/

#ifndef PLUGINS_H
#define PLUGINS_H

#include <QtPlugin>
#include <QObject>
#include <QString>
#include <QWidget>
//#include <QIcon>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

/*!
 \class baseInfo
 \brief This class provides base information for all plugins
*/

class baseInfo
{
public:
  virtual QString name() const = 0;
  virtual QString group() const = 0;
  virtual QString toolTip() const = 0;
  virtual QString whatsThis() const = 0;
  virtual QString type() const = 0;
  virtual QString icon() const = 0;
  virtual QString version() const = 0;
  virtual QString description() const = 0;
  virtual bool hasConfig() const = 0;
};

/*!
 \class CommonPlugin
 \brief This class provides management for common plugins
*/

class CommonPlugin : public baseInfo
{
public:
  virtual ~CommonPlugin() {}

  virtual QString results(const QString &file) = 0;
  virtual bool isEnabled() const = 0;
  virtual QWidget *createConfWidget(QWidget *parent) = 0;
};

/*!
 \class DatabasePlugin
 \brief This class provides management for database plugins
*/

class DatabasePlugin : public baseInfo
{
public:
  virtual ~DatabasePlugin() {}

  virtual QString searchWord(const QString &db, const QString &wrd) = 0;
  virtual bool isEditable() const = 0;
  virtual void createNewDb(const QString &dbFile) = 0;
  virtual void open(const QString &dbFile) = 0;
  virtual bool store(const QString &key, const QString &value) = 0;
  virtual bool replace(const QString &key, const QString &value) = 0;
  virtual QString check(const QString &key) = 0;
  virtual void remove(const QString &key) = 0;
  virtual void close() = 0;
  virtual QWidget *createConfWidget(QWidget *parent) = 0;
  
public slots:
  virtual void saveSetting() = 0;
};

/*!
 \class InterfacePlugin
 \brief This class provides management for interface plugins
*/

class InterfacePlugin : public baseInfo
{
public:
  virtual ~InterfacePlugin() {}
  
  virtual Qt::DockWidgetArea widgetArea() const = 0;
  virtual QWidget *createConfWidget(QWidget *parent) = 0;
  virtual QWidget *createMainWidget(QWidget *parent) = 0;
  
public Q_SLOTS:
  virtual void urlActivated(const QString &url) = 0;
  
Q_SIGNALS:
  void wordRequeste(const QString &word);
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(CommonPlugin, "com.trolltech.Neda.CommonPlugin/1.0")
Q_DECLARE_INTERFACE(DatabasePlugin, "com.trolltech.Neda.DatabasePlugin/1.0")
Q_DECLARE_INTERFACE(InterfacePlugin, "com.trolltech.Neda.InterfacePlugin/1.0")
QT_END_NAMESPACE

#endif //
