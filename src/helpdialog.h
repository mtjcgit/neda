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

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

class QAction;
class QToolBar;
class QTextBrowser;
class QFrame;
class searchBar;

/*!
 \class helpDialog
 \brief This class provides help dialog
*/

class helpDialog : public QDialog
{
Q_OBJECT

public:
  //! Constructor of help dialog.
  //helpDialog(QWidget *parent = 0);
  helpDialog(QWidget *parent = 0, const QString &page = "index.html");
  //! Destructor of help dialog.
  ~helpDialog();

private slots:
  //! function for update window title with page change.
  void updateWindowTitle();
  void showFindWidget(bool b);
  void showPrintDialog();
  void showPrintPreview();
  void printPreview(QPrinter *printer);

private:
  void createActions();
  void createToolbars();
  void retranslateUi();

private:
  QTextBrowser *textBrowser;
  QAction *homeAction;
  QAction *backwardAction;
  QAction *forwardAction;
  QAction *refreshAction;
  QAction *copyAction;
  QAction *printAction;
  QAction *printPrwAction;
  QAction *findAction;
  QAction *zoomInAction;
  QAction *zoomOutAction;
  QAction *zoomOrgAction;
  QAction *closeAction;
  QToolBar *mainToolBar;
  searchBar *findBar;
};

#endif
