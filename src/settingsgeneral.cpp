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

#include "settingsgeneral.h"
#include "globalvar.h"
#include "helpdialog.h"
#include "appearancewidget.h"
#include "behaviorwidget.h"
#include "fontswidget.h"
#include "colorswidget.h"
#include "iconswidget.h"
#include "notificationswidget.h"

generalPage::generalPage(QWidget *parent) : QWidget(parent)
{
  label = new QLabel(this);
  //label->setFrameStyle(QFrame::Box | QFrame::Raised);
  label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

  tabWidget = new QTabWidget(this);
  appearance = new appearanceWidget(this);
  behavior = new behaviorWidget(this);
  colors = new colorsWidget(this);
  fonts = new fontsWidget(this);
  icons  = new iconsWidget(this);
  notifications = new notificationsWidget(this);
  
  tabWidget->addTab(appearance, QIcon(appearance->pageIcon()), appearance->pageName());
  tabWidget->addTab(behavior, QIcon(behavior->pageIcon()), behavior->pageName());
  tabWidget->addTab(colors, QIcon(colors->pageIcon()), colors->pageName());
  tabWidget->addTab(fonts, QIcon(fonts->pageIcon()), fonts->pageName());
  tabWidget->addTab(icons, QIcon(icons->pageIcon()), icons->pageName());
  tabWidget->addTab(notifications, QIcon(notifications->pageIcon()), notifications->pageName());

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin( 0 );
  mainLayout->addWidget(label);
  mainLayout->addWidget(tabWidget);
  setLayout(mainLayout);

  loadSettings();
  retranslateUi();
}

generalPage::~generalPage()
{
}

QString generalPage::pageName()
{
  return tr("General");
}

QString generalPage::pageIcon()
{
  return (globalVar::defaultIcons("64", "apps") + "/" + globalVar::appName() + ".png");
}

void generalPage::retranslateUi()
{
  label->setText(tr("<b>General Settings</b>"));
}

void generalPage::loadSettings()
{
}

void generalPage::saveSettings()
{
  switch (tabWidget->currentIndex()) {
    case 0:
      appearance->saveSettings();
    break;
    case 1:
      behavior->saveSettings();
    break;
    case 2:
      colors->saveSettings();
    break;
    case 3:
      fonts->saveSettings();
    break;
    case 4:
      icons->saveSettings();
    break;
    case 5:
      notifications->saveSettings();
    break;
  }
}

void generalPage::quickHelp()
{
  //helpDialog *hlp = new helpDialog(this, "introduction.html");
  //hlp->show();
}
