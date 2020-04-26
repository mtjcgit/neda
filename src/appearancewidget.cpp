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

#include "appearancewidget.h"
#include "globalvar.h"

appearanceWidget::appearanceWidget(QWidget *parent) : QWidget(parent)
{
  appearGroup = new QGroupBox(this);
  useStylePaletteCheckBox = new QCheckBox(this);
  useStylePaletteCheckBox->setChecked(true);
  styleComboBox = new QComboBox(this);
  styleComboBox->addItems(QStyleFactory::keys());

  QVBoxLayout *groupLayout = new QVBoxLayout;
  groupLayout->addWidget(useStylePaletteCheckBox);
  groupLayout->addWidget(styleComboBox);
  groupLayout->addStretch(0);
  appearGroup->setLayout(groupLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(appearGroup);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
}

appearanceWidget::~appearanceWidget()
{}

QString appearanceWidget::pageName()
{
  return tr("&Appearance");
}

QString appearanceWidget::pageIcon()
{
  return globalVar::defaultIcons("22", "apps") + "/preferences-desktop-theme.png";
}

void appearanceWidget::retranslateUi()
{
  appearGroup->setTitle( tr("&Style") );
  useStylePaletteCheckBox->setText( tr("&Use style's standard palette") );
  useStylePaletteCheckBox->setWhatsThis( tr( "If you enable this option, styles use standard palettes") );
  styleComboBox->setWhatsThis( tr("Here you can choose from a list of predefined widget styles") );
}

void appearanceWidget::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  useStylePaletteCheckBox->setChecked( settings.value("generals/UseStyleStandardPalette").toBool() );
  if (settings.value("generals/CurrentStyle").toBool()) {
    //FIXME if there isn't style from setting!
    styleComboBox->setCurrentIndex( QStyleFactory::keys().indexOf(settings.value("generals/CurrentStyle").toString()) );
  }
}

void appearanceWidget::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  settings.setValue("generals/UseStyleStandardPalette", useStylePaletteCheckBox->isChecked());
  settings.setValue("generals/CurrentStyle", styleComboBox->currentText());
  //settings.setValue("generals/CurrentStyleIndex", styleComboBox->currentIndex());
}
