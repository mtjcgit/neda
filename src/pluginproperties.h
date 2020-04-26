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

#ifndef PLUGINPROPERTIES_H
#define PLUGINPROPERTIES_H

#include <QDialog>

class QLabel;
class QGridLayout;
class QTabWidget;
class QPushButton;
class QDialogButtonBox;

/*!
 \class genTab
 \brief This class provides tab widget for plugin properties dialog.
*/

class genTab : public QWidget
{
Q_OBJECT
  
public:
  //! Constructor of tab widget for plugin properties dialog.
  genTab(QString plgName, QWidget *parent = 0);
};

/*!
 \class pluginProperties
 \brief This class provides plugin properties dialog.
*/

class pluginProperties : public QDialog
{
Q_OBJECT

public:
  //! Constructor of plugin properties dialog.
  pluginProperties(QWidget *parent = 0, QString plgName = "Unknown");
  //! Destructor of plugin properties dialog.
  ~pluginProperties();

private:
  //! translations of user interface for plugin properties dialog.
  void retranslateUi(QString plgName);

private:
  QLabel *textLabel;
  QLabel *imageLabel;
  QLabel *commentLabel;
  QGridLayout *headerLayout;
  QDialogButtonBox *buttonBox;
  QPushButton *closeButton;
  QTabWidget *tabWidget;
};

#endif
