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

#ifndef DBMNGWIDGET_H
#define DBMNGWIDGET_H

#include <QWidget>

class QPushButton;
class QListWidgetItem;
class dbSelector;
class dbProperties;
class dbcreateWizard;

class dbMngWidget : public QWidget
{
Q_OBJECT

public:
  dbMngWidget(QWidget *parent = 0);

public:
  void saveSettings();

protected:
  void retranslateUi();
  void loadSettings();

private slots:
  void dbRefresh();
  void showProperties();
  void itemAction(QListWidgetItem *item);
  void createNewdb();

private:
  QPushButton *dbInfo;
  QPushButton *dbReload;
  QPushButton *createBtn;
  dbSelector *dbSel;
  dbProperties *dbprp;
  dbcreateWizard *newdbWzrd;
	
/*	QPushButton *removedbDir;
	QPushButton *updbDir;
	QPushButton *downDir;
	QPushButton *clrdbDir;*/
};

#endif
