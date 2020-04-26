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

#ifndef COLORSWIDGET_H
#define COLORSWIDGET_H

#include <QWidget>

#include "colorbutton.h"

class QLabel;
class colorButton;

/*!
 \class colorsWidget
 \brief This class provides colors widget for settings dialog.
*/

class colorsWidget : public QWidget
{
Q_OBJECT

public:
  //! Constructor of colors page.
  colorsWidget(QWidget *parent = 0);
  //! Destructor of colors page.
  ~colorsWidget();

public:
  //! Return name of colors page.
  virtual QString pageName();
  //! Return icon of colors page.
  virtual QString pageIcon();

public:
  //! function for save settings of colors page.
  void saveSettings();

protected:
  //! translations of user interface for colors page.
  void retranslateUi();
  //! function for load settings of colors page.
  void loadSettings();

private:
  QLabel *hdtxtLabel;
  QLabel *hdbgLabel;
  QLabel *rstxtLabel;
  QLabel *rsbgLabel;
  colorButton *hdtxtBtn;
  colorButton *hdbgBtn;
  colorButton *rstxtBtn;
  colorButton *rsbgBtn;
};

#endif
