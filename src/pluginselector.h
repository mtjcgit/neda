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

#ifndef PLUGINSELECTOR_H
#define PLUGINSELECTOR_H

#include <QWidget>
#include <QIcon>

class QListWidget;
class QListWidgetItem;
class QPushButton;
class pluginProperties;
class pluginSettings;

/*!
 \class pluginSelector
 \brief This class provides plugin selector.
*/

class pluginSelector : public QWidget
{
Q_OBJECT

public:
  //! Constructor of plugin selector.
  pluginSelector(QWidget *parent = 0, const QString &group = "Unknown");
  //! Destructor of plugin selector.
  ~pluginSelector();

public:
  //! function for save settings of plugin selector.
  void saveSettings();

protected:
  //! translations of user interface for plugin selector.
  void retranslateUi();
  //! function of load settings for plugin selector.
  void loadSettings();
  //! function of load all plugins for plugin selector.
  void loadAllPlugins();
  //! function of load a group plugins for plugin selector.
  void loadGrpPlugins(const QString &group);

private slots:
  void itemAction(QListWidgetItem *item);
  //! function of show properties dialog for plugin selector.
  void showProperties();
  //! function of show settings dialog for plugin selector.
  void showSettings();

private:
  QString mygroup;
  QListWidget *listWidget;
  QIcon interfaceIcon;
  QIcon featureIcon;
  QPushButton *plgInfo;
  QPushButton *plgSett;
  pluginProperties *plgnprop;
  pluginSettings *plgnsett;
};

#endif
