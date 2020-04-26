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

#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

#include <QDialog>

class QDialogButtonBox;

/*!
 \class pluginSettings
 \brief This class provides plugin settings dialog.
*/

class pluginSettings : public QDialog
{
Q_OBJECT

public:
  //! Constructor of plugin settings dialog.
  pluginSettings(QWidget *parent = 0, QString plgName = "Unknown");
  //! Destructor of plugin settings dialog.
  ~pluginSettings();

private:
  //! function of create buttons for plugin settings dialog.
  void createButtons();
  //! translations of user interface for plugin settings dialog.
  void retranslateUi();

private:
  QDialogButtonBox *buttonBox;
  QPushButton *closeButton;
  QPushButton *okButton;
  QPushButton *applyButton;

  /*QLabel *textLabel;
  QLabel *imageLabel;
  QLabel *commentLabel;
  QGridLayout *headerLayout;
  QDialogButtonBox *buttonBox;
  QPushButton *closeButton;
  QTabWidget *tabWidget;*/
};

#endif
