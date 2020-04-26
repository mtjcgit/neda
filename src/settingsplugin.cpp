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

#include "settingsplugin.h"
#include "pluginselector.h"
#include "globalvar.h"
#include "helpdialog.h"

pluginPage::pluginPage(QWidget *parent) : QWidget(parent)
{
  label = new QLabel(this);
  label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

  tabWidget = new QTabWidget(this);

  tabWidget->addTab(new pluginSelector(this, "common"), QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-database.png"), tr("&Common"));
  tabWidget->addTab(new pluginSelector(this, "database"), QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-database.png"), tr("&Database"));
  tabWidget->addTab(new pluginSelector(this, "interface"), QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-database.png"), tr("&Interface"));

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin( 0 );
  mainLayout->addWidget(label);
  mainLayout->addWidget(tabWidget);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
}

pluginPage::~pluginPage()
{
}

QString pluginPage::pageName()
{
  return tr("Plugins");
}

QString pluginPage::pageIcon()
{
  return (globalVar::defaultIcons("64", "places") + "/preferences-plugin.png");
}

void pluginPage::retranslateUi()
{
  label->setText(tr("<b>Plugin Settings</b>"));
}

void pluginPage::quickHelp()
{
  //helpDialog *hlp = new helpDialog(this, "gdict.html");
  //hlp->show();
}

void pluginPage::loadSettings()
{
}

void pluginPage::saveSettings()
{
  QList<pluginSelector*> allCombos = qFindChildren<pluginSelector*>(this);

  foreach (pluginSelector* box, allCombos) {
    box->saveSettings();
  }
}
