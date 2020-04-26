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

#ifndef BEHAVIORWIDGET_H
#define BEHAVIORWIDGET_H

#include <QWidget>

class QGroupBox;
class QCheckBox;
class QLabel;
class QComboBox;
class fileChooser;

/*!
 \class behaviorWidget
 \brief This class provides behavior widget for settings dialog.
*/

class behaviorWidget : public QWidget
{
Q_OBJECT

public:
  //! Constructor of behavior page.
  behaviorWidget(QWidget *parent = 0);
  //! Destructor of behavior page.
  ~behaviorWidget();

public:
  //! Return name of behavior page.
  virtual QString pageName();
  //! Return icon of behavior page.
  virtual QString pageIcon();

public:
  //! function for save settings of behavior page.
  void saveSettings();

protected:
  //! translations of user interface for behavior page.
  void retranslateUi();
  //! function for load settings of behavior page.
  void loadSettings();

private:
  QGroupBox *mainGroup;
  QGroupBox *cmpltGroup;
  QCheckBox *splashCheckBox;
  QCheckBox *tipCheckBox;
  QCheckBox *trayCheckBox;
  QCheckBox *finbarCheckBox;
  QLabel *modeLabel;
  QLabel *caseLabel;
  QLabel *fileLabel;
  QComboBox *modeCombo;
  QComboBox *caseCombo;
  fileChooser *wordsfile;
};

#endif
