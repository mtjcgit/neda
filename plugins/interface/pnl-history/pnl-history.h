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

#ifndef PNL_HISTORY_H
#define PNL_HISTORY_H

#include <QObject>

#include "plugins.h"

class QFile;
class QFileSystemWatcher;
class QToolBar;
//class QLineEdit;
//class QAction;
class QListWidget;
class QListWidgetItem;
class QSpinBox;

class pnlHistory : public QObject, public InterfacePlugin
{
Q_OBJECT
Q_INTERFACES(InterfacePlugin)

public:
  QString name() const;
  QString group() const;
  QString toolTip() const;
  QString whatsThis() const;
  QString type() const;
  QString icon() const;
  QString version() const;
  QString description() const;
  //QStringList dependencies() const;
  Qt::DockWidgetArea widgetArea() const;
  bool hasConfig() const;
  QWidget *createConfWidget(QWidget* parent);
  QWidget *createMainWidget(QWidget* parent);

protected:
  void loadSettings();
  void retranslateUi();
  
signals:
  void wordRequeste(const QString &word);
  
public slots:
  void urlActivated(const QString &url);
  void saveSettings(void);

private slots:
  void loadHistory();
  void itemAction(QListWidgetItem *item);
  
private:
  QString pluginHomepath();
  QString config();
  
private:
  QWidget *hidtWdgt;
  QWidget *confWdgt;
  QFile *histFile;
  QFileSystemWatcher *fileWatcher;
  QToolBar *mainToolBar;
  //QLineEdit *searchLineEdit;
  //QAction *sortAction;
  //QAction *clearAction;
  QListWidget *listWidget;
  QSpinBox *histNumber;
};

#endif
