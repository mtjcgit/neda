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

#include <QDebug>
#include <QSettings>

#include "basepanel.h"
#include "globalvar.h"

basePanel::basePanel(QWidget *parent) : QDockWidget(parent)
{
// connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), parent, SLOT(saveSettings()));
// connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea area)), this, SLOT(saveSettings(Qt::DockWidgetArea area)));
// connect(this, SIGNAL(dockLocationChanged()), this, SLOT(saveSettings()));
}

basePanel::~basePanel()
{}
/*
void basePanel::saveSettings()
{
  qDebug() << ">>>> saveSettings from dock";
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("generals/geometry", saveGeometry());
//   settings.setValue("generals/windowState", QApplication::saveState());
}*/
