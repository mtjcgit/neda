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
#include <QDebug>

#include "fontswidget.h"
#include "globalvar.h"

fontsWidget::fontsWidget(QWidget *parent) : QWidget(parent)
{
  hdtxtLabel = new QLabel(this);
  hdtxtBtn = new QPushButton(this);
  connect(hdtxtBtn, SIGNAL(clicked()), this, SLOT(hdtxtFont()));
  rstxtLabel = new QLabel(this);
  rstxtBtn = new QPushButton(this);
  connect(rstxtBtn, SIGNAL(clicked()), this, SLOT(rstxtFont()));
  sampleText = new QTextEdit(this);
  sampleText->setMaximumHeight(100);
  sampleText->setAlignment(Qt::AlignCenter);
  
  QGridLayout *fontsLayout = new QGridLayout(this);
  fontsLayout->addWidget(hdtxtLabel, 0, 0);
  fontsLayout->addWidget(hdtxtBtn, 0, 1);
  fontsLayout->addWidget(rstxtLabel, 1, 0);
  fontsLayout->addWidget(rstxtBtn, 1, 1);
  fontsLayout->addWidget(sampleText, 2, 0, 1, 2);
  fontsLayout->setRowStretch(3, 1);
  setLayout(fontsLayout);
  
  retranslateUi();
  loadSettings();
}

fontsWidget::~fontsWidget()
{}

QString fontsWidget::pageName()
{
  return tr("&Fonts");
}

QString fontsWidget::pageIcon()
{
  return globalVar::defaultIcons("22", "apps") + "/preferences-desktop-font.png";
}

void fontsWidget::retranslateUi()
{
  hdtxtLabel->setText(tr("Header Text"));
  rstxtLabel->setText(tr("Results Text"));
  // FIXME add header style and show current setting
  sampleText->setText(tr("The Quick Brown Fox Jumps Over The Lazy Dog"));
  
  hdtxtBtn->setText(tr("Select"));
  hdtxtBtn->setIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-desktop-font.png"));
  hdtxtBtn->setToolTip("font selecte");
  hdtxtBtn->setFont(hdFont);
  //hdtxtBtn->setWhatsThis(tr(""));
  
  rstxtBtn->setText(tr("Select"));
  rstxtBtn->setIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-desktop-font.png"));
  rstxtBtn->setToolTip("font selecte");
  rstxtBtn->setFont(rsFont);
  //rstxtBtn->setWhatsThis(tr(""));
}

void fontsWidget::hdtxtFont()
{
  bool ok;
  // FIXME set default QApplication::font () for firest time
  hdFont = QFontDialog::getFont(&ok, hdFont, this);
  
  if (ok) {
   sampleText->selectAll();
   sampleText->setCurrentFont(hdFont);
 //} else {
 }
}

void fontsWidget::rstxtFont()
{
  bool ok;
  // FIXME set default QApplication::font () for firest time
  rsFont = QFontDialog::getFont(&ok, rsFont, this);
  
  if (ok) {
    sampleText->selectAll();
    sampleText->setCurrentFont(rsFont);
  //} else {
  }
}

void fontsWidget::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  hdFont.fromString(settings.value("generals/hdtxtFont").toString());
  rsFont.fromString(settings.value("generals/rstxtFont").toString());
}

void fontsWidget::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("generals/hdtxtFont", hdFont.toString());
  settings.setValue("generals/rstxtFont", rsFont.toString());
}
