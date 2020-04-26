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

#ifndef DBPROPERTIES_H
#define DBPROPERTIES_H

#include <QDialog>

class QLabel;
class QGridLayout;
class QTabWidget;
class QPushButton;
class QDialogButtonBox;

/*!
 \class generalTab
 \brief This class provides tab widget for properties dialog.
*/

class generalTab : public QWidget
{
Q_OBJECT
  
public:
  //! Constructor of tab widget.
  generalTab(QString dbName, QWidget *parent = 0);
};

/*!
 \class dbProperties
 \brief This class provides database properties dialog.
*/

class dbProperties : public QDialog
{
Q_OBJECT

public:
  //! Constructor of database properties dialog.
  dbProperties(QWidget *parent = 0, QString dbName = "Unknown");
  //! Destructor of database properties dialog.
  ~dbProperties();

private:
  //! translations of user interface for database properties dialog.
  void retranslateUi(QString dbName);

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
