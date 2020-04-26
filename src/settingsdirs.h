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

#ifndef SETTINGSDIRS_H
#define SETTINGSDIRS_H

#include <QWidget>

class QLabel;
class QGroupBox;
class QPushButton;
class QListWidget;
class QListWidgetItem;
class fileChooser;

/*!
 \class directoryPage
 \brief This class provides directory page for settings dialog.
*/

class directoryPage : public QWidget
{
Q_OBJECT

public:
  //! Constructor of directory page.
  directoryPage(QWidget *parent = 0);
  //! Destructor of directory page.
  ~directoryPage();

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

protected slots:
  void deactiveControls();
  void newdbdirFunc();
  void dblistRemove();
  void dblistUp();
  void dblistDown();
  void dblistClr();
  void itemAction(QListWidgetItem *item);
  void dirEdited(const QString &);

signals:
  void widgetModified();

private:
  QLabel *label;
  QGroupBox *dirGroup;
  QPushButton *newdbDir;
  QPushButton *removedbDir;
  QPushButton *updbDir;
  QPushButton *downDir;
  QPushButton *clrdbDir;
  QListWidget *dbdirList;
  fileChooser *dbDir;
};

#endif
