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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QLabel;
class QGridLayout;
class QTabWidget;
class QPushButton;
class QDialogButtonBox;

/*!
 \class aboutDialog
 \brief This class provides about dialog
*/

class aboutDialog : public QDialog
{
Q_OBJECT

public:
  //! Constructor of about dialog.
  aboutDialog(QWidget *parent = 0);
  //! Destructor of about dialog.
  ~aboutDialog();

private:
  //! translations of user interface for about dialog.
  void retranslateUi();

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
