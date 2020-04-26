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

#ifndef DB_TELLICO_H
#define DB_TELLICO_H

#include <QObject>
#include "plugins.h"

class dbTellico : public QObject, public DatabasePlugin
{
Q_OBJECT
Q_INTERFACES(DatabasePlugin)

public:
  QString name() const;
  QString group() const;
  QString toolTip() const;
  QString whatsThis() const;
  QString type() const;
  QString icon() const;
  QString version() const;
  QString description() const;
  //QString count() const;
  QString searchWord(const QString &db, const QString &wrd);
  bool hasConfig() const;
  bool isEditable() const;
  void createNewDb(const QString &dbFile);
  void open(const QString &dbFile);
  bool store(const QString &key, const QString &value);
  bool replace(const QString &key, const QString &value);
  QString check(const QString &key);
  void remove(const QString &key);
  void close();
  QWidget *createConfWidget(QWidget* parent);

public slots:
  void saveSetting();

private:
  QString config();
};

#endif
