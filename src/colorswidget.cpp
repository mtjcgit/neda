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

#include "colorswidget.h"
#include "globalvar.h"

colorsWidget::colorsWidget(QWidget *parent) : QWidget(parent)
{
  hdtxtLabel = new QLabel(this);
  hdtxtBtn = new colorButton(this);
  hdbgLabel = new QLabel(this);
  hdbgBtn = new colorButton(this);
  rstxtLabel = new QLabel(this);
  rstxtBtn = new colorButton(this);
  rsbgLabel = new QLabel(this);
  rsbgBtn = new colorButton(this);
  
  QGridLayout *colorsLayout = new QGridLayout(this);
  colorsLayout->addWidget(hdtxtLabel, 0, 0);
  colorsLayout->addWidget(hdtxtBtn, 0, 1);
  colorsLayout->addWidget(hdbgLabel, 1, 0);
  colorsLayout->addWidget(hdbgBtn, 1, 1);
  colorsLayout->addWidget(rstxtLabel, 2, 0);
  colorsLayout->addWidget(rstxtBtn, 2, 1);
  colorsLayout->addWidget(rsbgLabel, 3, 0);
  colorsLayout->addWidget(rsbgBtn, 3, 1);
  colorsLayout->setRowStretch(4, 1);
  setLayout(colorsLayout);
  
  retranslateUi();
  loadSettings();
}

colorsWidget::~colorsWidget()
{}

QString colorsWidget::pageName()
{
  return tr("&Colors");
}

QString colorsWidget::pageIcon()
{
  return globalVar::defaultIcons("22", "apps") + "/preferences-desktop-color.png";
}

void colorsWidget::retranslateUi()
{
  hdtxtLabel->setText(tr("Header Text"));
  hdbgLabel->setText(tr("Header Background"));
  rstxtLabel->setText(tr("Results Text"));
  rsbgLabel->setText(tr("Results Background"));
}

void colorsWidget::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  QColor hdtxtc, hdbgc, rstxtc, rsbgc;
  hdtxtc = settings.value("generals/hdtxtColor").value<QColor>();
  hdbgc = settings.value("generals/hdbgColor").value<QColor>();
  rstxtc = settings.value("generals/rstxtColor").value<QColor>();
  rsbgc = settings.value("generals/rsbgColor").value<QColor>();

  if (!hdtxtc.isValid())
    hdtxtc = QColor(Qt::black);
  if (!hdbgc.isValid())
    hdbgc = QColor(Qt::white);
  if (!rstxtc.isValid())
    rstxtc = QColor(Qt::black);
  if (!rsbgc.isValid())
    rsbgc = QColor(Qt::white);
  
  hdtxtBtn->setColor(hdtxtc);
  hdbgBtn->setColor(hdbgc);
  rstxtBtn->setColor(rstxtc);
  rsbgBtn->setColor(rsbgc);
}

void colorsWidget::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("generals/hdtxtColor", hdtxtBtn->color());
  settings.setValue("generals/hdbgColor", hdbgBtn->color());
  settings.setValue("generals/rstxtColor", rstxtBtn->color());
  settings.setValue("generals/rsbgColor", rsbgBtn->color());
}
