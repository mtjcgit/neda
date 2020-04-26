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

#ifndef SETTINGSDB_H
#define SETTINGSDB_H

#include <QWidget>

class QLabel;
class QTabWidget;
class dbMngWidget;
class dbCnfWidget;

/*!
 \class databasePage
 \brief This class provides database page for settings dialog.
*/

class databasePage : public QWidget
{
Q_OBJECT

public:
  //! Constructor of database page.
  databasePage(QWidget *parent = 0);
  //! Destructor of database page.
  ~databasePage();

public:
  //! Return name of page.
  virtual QString pageName();
  //! Return icon of page.
  virtual QString pageIcon();

public:
  //! translations of user interface for general page.
  void retranslateUi();

protected:
  //! function for loading settings.
  void loadSettings();

public slots:
  void quickHelp();
  void saveSettings();

private:
  QLabel *label;
  QTabWidget *tabWidget;
  dbMngWidget *dbmng;
  dbCnfWidget *dbcnf;
};

#endif
