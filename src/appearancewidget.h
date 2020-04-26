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

#ifndef APPEARANCEWIDGET_H
#define APPEARANCEWIDGET_H

#include <QWidget>

class QGroupBox;
class QComboBox;
class QCheckBox;

/*!
 \class appearanceWidget
 \brief This class provides appearance widget for settings dialog.
*/

class appearanceWidget : public QWidget
{
Q_OBJECT

public:
  //! Constructor of appearance widget.
  appearanceWidget(QWidget *parent = 0);
  //! Destructor of appearance widget.
  ~appearanceWidget();

public:
  //! Return name of appearance widget.
  virtual QString pageName();
  //! Return icon of appearance widget.
  virtual QString pageIcon();
  
public:
  //! function for save settings.
  void saveSettings();

protected:
  void retranslateUi();
  //! function for load settings.
  void loadSettings();

private:
  QGroupBox *appearGroup;
  QCheckBox *useStylePaletteCheckBox;
  QComboBox *styleComboBox;
};

#endif
