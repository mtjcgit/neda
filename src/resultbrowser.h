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

#ifndef RESULTBROWSER_H
#define RESULTBROWSER_H

#include <QTextBrowser>

class QAction;
class QMenu;
class QTextDocument;
/*!
 \class resultBrowser
 \brief This class provides browser for results
*/

class resultBrowser : public QTextBrowser
{
  Q_OBJECT
  
public:
  //! Constructor of result browser.
  resultBrowser(QWidget *parent = 0);
  
public:
  //! load settings for result browser.
  void loadSettings();
  
private:
  //! create all actions for result browser.
  void createActions();
  //! create menus for result browser.
  void createMenus();
  //! translations of user interface for result browser.
  void retranslateUi();
  //! return font weight for result browser.
  QString fontWeight(int w);
  
protected:
  void contextMenuEvent (QContextMenuEvent *event );
  
signals:
  void requestedWord(const QString &word);
  
private slots:
  void requestWord();
//   void deSelect();
  
private:
  QTextDocument *doc;
  QAction *copyAction;
  QAction *selectAllAction;
//   QAction *deslctAllAction;
  QAction *findAction;
  QAction *bkmrkAction;
  QMenu *menu;
  QFont hdFont;
  QFont rsFont;
};

#endif
