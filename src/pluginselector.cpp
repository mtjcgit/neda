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

#include <QtGui>

#include "pluginselector.h"
#include "pluginmanager.h"
#include "globalvar.h"
#include "pluginproperties.h"
#include "pluginsettings.h"

pluginSelector::pluginSelector(QWidget *parent, const QString &group) : QWidget(parent)
{
  mygroup = group;
  
  listWidget = new QListWidget(this);
  listWidget->setIconSize(QSize(22, 22));
  listWidget->setAlternatingRowColors(true);
  connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemAction(QListWidgetItem *)));
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->addWidget(listWidget);

  plgInfo = new QPushButton(this);
  plgInfo->setEnabled(false);
  connect(plgInfo, SIGNAL(clicked()), this, SLOT(showProperties()));
  
  plgSett = new QPushButton(this);
  plgSett->setEnabled(false);
  connect(plgSett, SIGNAL(clicked()), this, SLOT(showSettings()));
  
  QVBoxLayout *controlLayout = new QVBoxLayout;
  controlLayout->addWidget(plgInfo);
  controlLayout->addWidget(plgSett);
  controlLayout->addStretch(0);
  
  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addLayout(layout);
  mainLayout->addLayout(controlLayout);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
  loadGrpPlugins(group);
}

pluginSelector::~pluginSelector()
{
}

void pluginSelector::retranslateUi()
{
  plgInfo->setText(tr("&Properties"));
  plgInfo->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about.png"));
  plgSett->setText(tr("&Settings"));
  plgSett->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/configure.png"));
}

void pluginSelector::loadSettings()
{
}

void pluginSelector::saveSettings()
{
  QStringList plgs;
  for ( int rowIndex = 0 ; rowIndex < listWidget->count() ; rowIndex++ ) {
    if (listWidget->item(rowIndex)->checkState() == Qt::Checked) {
    plgs << listWidget->item(rowIndex)->text();
    }
  }
  QString str = plgs.join(", ");
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue(QString("plugins/Selected-%1").arg(mygroup), str);
}

void pluginSelector::loadAllPlugins()
{
  pluginManager::selectedPlugins();
  
  foreach (QString plugin, pluginManager::foundPlugins()) {
    QListWidgetItem *pluginItem = new QListWidgetItem(listWidget);
    pluginItem->setText(plugin);
    
    // NOTE this can use icon provided from each plug in.
    /*if (QFile::exists(pluginManager::icon(plugin))) {
      pluginItem->setIcon(QIcon(pluginManager::icon(plugin)));
      
    } else {*/
      pluginItem->setIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-plugin.png"));
    //}
    pluginItem->setCheckState(Qt::CheckState(pluginManager::checkState(plugin)));
  }
}

void pluginSelector::loadGrpPlugins(const QString &group)
{
  
  pluginManager::selectedPlugins();
  
  foreach (QString plugin, pluginManager::foundPlugins()) {
    if (pluginManager::plgbyGroup(group).contains(plugin)) {
      QListWidgetItem *pluginItem = new QListWidgetItem(listWidget);
      pluginItem->setText(plugin);
      pluginItem->setIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-plugin.png"));
      pluginItem->setCheckState(Qt::CheckState(pluginManager::checkState(plugin)));
    }
  }
  
}

void pluginSelector::itemAction(QListWidgetItem *item)
{
  plgInfo->setEnabled( item!=0 );
  plgSett->setEnabled(pluginManager::hasConfig(item->text()));
}

void pluginSelector::showProperties()
{
  plgnprop = new pluginProperties(this, listWidget->currentItem()->text());
  plgnprop->show();
}

void pluginSelector::showSettings()
{
  plgnsett = new pluginSettings(this, listWidget->currentItem()->text());
  plgnsett->show();
}
