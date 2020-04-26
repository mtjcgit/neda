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

#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>

class QToolButton;
class QLabel;
class QAction;
class QMenu;
class QTextBrowser;
class lineEdit;

/*!
 \class searchBar
 \brief This class provides search bar for main window
 search bar, provides options for finding specified word or phrase in search results
*/

class searchBar : public QWidget
{
Q_OBJECT
  
public:
  //! Constructor of search bar.
  searchBar(QWidget *parent = 0);
  //! Destructor of search bar.
  ~searchBar();

public:
  //! set browser widget for search bar.
  void setTextWidget(QTextBrowser *textBrowser);
  //! function for show search bar.
  void showSearchBar();
  //! translations of user interface of search bar.
  void retranslateUi();
  
private:
  //! create all actions for search bar.
  void createActions();
  //! create menus for search bar.
  void createMenus();
  
public slots:
  //! slot for state of search bar visibility.
  void showSearchBar(bool show);
  
private slots:
  void findFirst(QString ttf, bool forward = false, bool backward = false);
  void patternChanged(const QString & pattern);
  void onReturnPressed();
  void findNext();
  void findPrevious();
  
signals:
  bool hideSearchBar();
  
  
private:
  QLabel *fndLabel;
  QToolButton *optionsTool;
  QMenu *toolMenu;
  
public:
  QAction *caseAction;
  QAction *wholeWordsAction;
  QToolButton *toolClose;
  QToolButton *toolNext;
  QToolButton *toolPrevious;
  QTextBrowser *browser;
  lineEdit *patternEdit;
  //QTimer *hidingTimer;
};

#endif
