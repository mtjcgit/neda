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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QDialogButtonBox;
class generalPage;
class directoryPage;
class databasePage;
class pluginPage;

/*!
 \class settingsDialog
 \brief This class provides settings dialog.
*/

class settingsDialog : public QDialog
{
Q_OBJECT

public:
  //! Constructor of settings dialog.
  settingsDialog(QWidget *parent = 0);
  //! Destructor of settings dialog.
  ~settingsDialog();

//public:
//	void updateActions();

public slots:
  //! slot for change page of settings.
  void changePage(QListWidgetItem *current, QListWidgetItem *previous);
  //! slot for update actions.
  void updateActions();
  //! slot for show help.
  void showHelp();
  //! slot for apply settings.
  void applySettings();
  //! slot for submit settings.
  void submitSettings();

protected slots:
  void quickHelp();

private:
  void createButtons();
  void retranslateUi();
  void addPageWidget(QWidget *page, const QString &itemName, const QString &pixmapName=QString());

signals:
  void settingModified();

private:
  QListWidget *contentsWidget;
  QStackedWidget *pagesWidget;
  QDialogButtonBox *buttonBox;
  QPushButton *closeButton;
  QPushButton *okButton;
  QPushButton *applyButton;
  QPushButton *helpButton;
  QPushButton *resetButton;
  generalPage *genPage;
  directoryPage *dirPage;
  databasePage *dbPage;
  pluginPage *plgnPage;
};

#endif
