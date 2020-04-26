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

#include "notificationswidget.h"
#include "globalvar.h"

notificationsWidget::notificationsWidget(QWidget *parent) : QWidget(parent)
{
  notifyGroup = new QGroupBox(this);
  notifyCheckBox = new QCheckBox(this);
  //notifyCheckBox->setChecked(true);
  
  QVBoxLayout *groupLayout = new QVBoxLayout;
  groupLayout->addWidget(notifyCheckBox);
  //groupLayout->addWidget(styleComboBox);
  groupLayout->addStretch(0);
  notifyGroup->setLayout(groupLayout);
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(notifyGroup);
  setLayout(mainLayout);
  
  retranslateUi();
  loadSettings();
}

notificationsWidget::~notificationsWidget()
{}

QString notificationsWidget::pageName()
{
  return tr("&Notifications");
}

QString notificationsWidget::pageIcon()
{
  return globalVar::defaultIcons("22", "apps") + "/preferences-desktop-notification.png";
}

void notificationsWidget::retranslateUi()
{
  notifyCheckBox->setText( tr("&Use tray message notification") );
  //notifyCheckBox->setWhatsThis( tr( "If you enable this option, ") );
}

void notificationsWidget::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  notifyCheckBox->setChecked( settings.value("generals/EnableNotification").toBool() );
}

void notificationsWidget::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  settings.setValue("generals/EnableNotification", notifyCheckBox->isChecked());
}
