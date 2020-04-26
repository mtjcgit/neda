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

#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include <QAction>
#include <QMenu>

class QToolButton;
class QAction;
class QMenu;
/*!
 \class lineEdit
 \brief This class provides An enhanced QLineEdit widget for inputting text.
*/

class lineEdit : public QLineEdit
{
Q_OBJECT

public:
  //! Constructor of line edit.
  lineEdit(QWidget *parent = 0);

protected:
  void resizeEvent(QResizeEvent *);
  void contextMenuEvent (QContextMenuEvent *event );

private:
  //! create all actions for line edit.
  void createActions();
  //! translations of user interface for line edit.
  void retranslateUi();
  
private slots:
  void updateCloseButton(const QString &text);

private:
  QToolButton *clearButton;
  QAction *caseAction;
  QMenu *menu;
};

#endif
