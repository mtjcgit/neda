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

#include "iconswidget.h"
#include "globalvar.h"

iconsWidget::iconsWidget(QWidget *parent) : QWidget(parent)
{
}

iconsWidget::~iconsWidget()
{}

QString iconsWidget::pageName()
{
  return tr("&Icons");
}

QString iconsWidget::pageIcon()
{
  return globalVar::defaultIcons("22", "apps") + "/preferences-desktop-icons.png";
}

void iconsWidget::retranslateUi()
{
}

void iconsWidget::loadSettings()
{
}

void iconsWidget::saveSettings()
{
}
