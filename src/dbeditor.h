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

#ifndef DBEDITOR_H
#define DBEDITOR_H

#include <QDialog>

class QAction;
class QToolBar;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QLabel;
class QTextEdit;
class QHBoxLayout;
class lineEdit;

/*!
 \class dbEditor
 \brief This class provides tab widget for properties dialog.
*/

class dbEditor : public QDialog
{
Q_OBJECT

public:
  //! Constructor of database editor dialog.
  dbEditor(QWidget *parent = 0);
  //! Destructor of database editor dialog.
  ~dbEditor();
  
private:
  void createActions();
  void createToolbars();
  //! translations of user interface for database editor dialog.
  void retranslateUi();
  
private slots:
  //! function of load all databases that can be edited.
  void loadAllDbss();
  void currentChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void save();
  void checkEntry();
  void remove();
  //! slot for open selected database for edition.
  void editDb(bool open);
  
private:
  QToolBar *mainToolBar;
  QAction *saveAction;
  QAction *refreshAction;
  QAction *closeAction;
  QAction *editAction;
  QAction *deleteAction;
  QListWidget *listWidget;
  QWidget *rightWidget;
  QLabel *nameLabel;
  QTextEdit *valueEdit;
  QHBoxLayout *margin;
  lineEdit *entryEdit;
};

#endif
