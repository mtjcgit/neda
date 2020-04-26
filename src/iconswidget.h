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

#ifndef ICONSWIDGET_H
#define ICONSWIDGET_H

#include <QWidget>

/*!
 \class iconsWidget
 \brief This class provides icons page for settings dialog.
*/

class iconsWidget : public QWidget
{
Q_OBJECT

public:
  //! Constructor of icons page.
  iconsWidget(QWidget *parent = 0);
  //! Destructor of icons page.
  ~iconsWidget();

public:
  //! Return name of icons page.
  virtual QString pageName();
  //! Return icon of icons page.
  virtual QString pageIcon();
  
public:
  //! function for save settings of icons page.
  void saveSettings();

protected:
  //! translations of user interface for icons page.
  void retranslateUi();
  //! function for load settings of icons page.
  void loadSettings();
};

#endif
