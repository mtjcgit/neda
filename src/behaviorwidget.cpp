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

#include "behaviorwidget.h"
#include "globalvar.h"
#include "filechooser.h"

behaviorWidget::behaviorWidget(QWidget *parent) : QWidget(parent)
{
  mainGroup = new QGroupBox(this);
  splashCheckBox = new QCheckBox(this);
  tipCheckBox = new QCheckBox(this);
  trayCheckBox = new QCheckBox(this);
  finbarCheckBox = new QCheckBox(this);
  
  QVBoxLayout *maingrpLayout = new QVBoxLayout;
  maingrpLayout->addWidget(splashCheckBox);
  maingrpLayout->addWidget(tipCheckBox);
  maingrpLayout->addWidget(trayCheckBox);
  maingrpLayout->addWidget(finbarCheckBox);
  maingrpLayout->addStretch(0);
  mainGroup->setLayout(maingrpLayout);
  
  cmpltGroup = new QGroupBox(this);
  cmpltGroup->setCheckable(true);
  
  modeLabel = new QLabel;
  modeCombo = new QComboBox;
  modeCombo->setCurrentIndex(1);
  caseLabel = new QLabel;
  caseCombo = new QComboBox;
  caseCombo->setCurrentIndex(0);
  fileLabel = new QLabel;
  wordsfile = new fileChooser(this);

  QGridLayout *cmpltLayout = new QGridLayout;
  cmpltLayout->addWidget(modeLabel, 0, 0);
  cmpltLayout->addWidget(modeCombo, 0, 1);
  cmpltLayout->addWidget(caseLabel, 1, 0);
  cmpltLayout->addWidget(caseCombo, 1, 1);
  cmpltLayout->addWidget(fileLabel, 2, 0);
  cmpltLayout->addWidget(wordsfile, 2, 1);

  cmpltGroup->setLayout(cmpltLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(mainGroup);
  mainLayout->addWidget(cmpltGroup);
  mainLayout->addStretch(0);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
}

behaviorWidget::~behaviorWidget()
{}

QString behaviorWidget::pageName()
{
  return tr("&Behavior");
}

QString behaviorWidget::pageIcon()
{
  return globalVar::defaultIcons("22", "apps") + "/preferences-system-windows-actions.png";
}

void behaviorWidget::retranslateUi()
{
  mainGroup->setTitle(tr("&Main Controls"));
  splashCheckBox->setText(tr("Show &splash-screen on startup"));
  //splashCheckBox->setAccessibleName("splashCB");
  tipCheckBox->setText(tr("Show &tips on startup"));
  //tipCheckBox->setAccessibleName("tipCB");
  trayCheckBox->setText(tr("Show &tray icon"));
  //trayCheckBox->setAccessibleName("tryCB");
  finbarCheckBox->setText(tr("Show &search bar"));
  
  cmpltGroup->setTitle(tr("&Auto Completion"));

  modeLabel->setText(tr("Completion Mode"));
  modeCombo->addItem(tr("Inline"));
  modeCombo->addItem(tr("Filtered Popup"));
  modeCombo->addItem(tr("Unfiltered Popup"));

  caseLabel->setText(tr("Case Sensitivity"));
  caseCombo->addItem(tr("Case Insensitive"));
  caseCombo->addItem(tr("Case Sensitive"));

  fileLabel->setText(tr("Words List"));
}

void behaviorWidget::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  splashCheckBox->setChecked( settings.value("generals/RunSplashOnStart").toBool() );
  tipCheckBox->setChecked( settings.value("generals/RunTipOnStart").toBool() );
  trayCheckBox->setChecked( settings.value("generals/ShowTrayIcon").toBool() );
  finbarCheckBox->setChecked( settings.value("generals/ShowFindBar").toBool() );

  cmpltGroup->setChecked( settings.value("generals/AutoCompletion").toBool() );
  modeCombo->setCurrentIndex( settings.value("generals/CompletionMode").toInt() );
  caseCombo->setCurrentIndex( settings.value("generals/CompletionCase").toInt() );
  
  if (!settings.value("generals/CompletionWord").toBool())
    wordsfile->setText(globalVar::words());
  else
    wordsfile->setText(settings.value("generals/CompletionWord").toString());
}

void behaviorWidget::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  settings.setValue("generals/RunSplashOnStart", splashCheckBox->isChecked());
  settings.setValue("generals/RunTipOnStart", tipCheckBox->isChecked());
  settings.setValue("generals/ShowTrayIcon", trayCheckBox->isChecked());
  settings.setValue("generals/ShowFindBar", finbarCheckBox->isChecked());

  settings.setValue("generals/AutoCompletion", cmpltGroup->isChecked());
  settings.setValue("generals/CompletionMode", modeCombo->currentIndex());
  settings.setValue("generals/CompletionCase", caseCombo->currentIndex());
  settings.setValue("generals/CompletionWord", wordsfile->text());
}
