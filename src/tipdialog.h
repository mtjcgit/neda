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

#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>

class QLabel;
class QTextBrowser;
class QCheckBox;
class QPushButton;

/*!
 \class tipDialog
 \brief This class provides tip of the day dialog
*/

class tipDialog : public QDialog
{
Q_OBJECT

public:
  //! Constructor of tip of the day dialog.
  tipDialog(QWidget *parent = 0);
  //! Destructor of tip of the day dialog.
  ~tipDialog();
  //! state of tip of the day dialog on start up.
  static void setShowOnStart( bool show );

public:
  QString tip() const;

private:
  //! translations of user interface for tip of the day dialog.
  void retranslateUi();
  //! function for loading tips file.
  void loadTips(const QString &tipFile);
  void addTips( const QString &tipFile );
  void tipDatabase( const QString &tipFile );	/*FIXME is really need it?*/

private slots:
  void nextTip();
  void prevTip();
  void showOnStart(bool);

private:
  QStringList tips;
  int currentTip;

private:
  QLabel *titleLabel;
  QTextBrowser *tipText;
  QCheckBox *tipOnStart;
  QPushButton *prvBtn;
  QPushButton *nxtBtn;
  QPushButton *okBtn;
};

#endif
