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

#include "settingsdb.h"
#include "globalvar.h"
#include "helpdialog.h"
#include "dbmngwidget.h"
#include "dbcnfwidget.h"

databasePage::databasePage(QWidget *parent) : QWidget(parent)
{
  label = new QLabel(this);
  label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

  tabWidget = new QTabWidget(this);
  //tabWidget->setUsesScrollButtons(false);
  //dbMngWidget *dbmng = new dbMngWidget(this);
  dbmng = new dbMngWidget(this);
  dbcnf = new dbCnfWidget(this);
  tabWidget->addTab(dbmng, QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-database.png"), tr("&Management"));
  tabWidget->addTab(dbcnf, QIcon(globalVar::defaultIcons("22", "apps") + "/preferences-database.png"), tr("&Configure"));
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin( 0 );
  mainLayout->addWidget(label);
  mainLayout->addWidget(tabWidget);
//  mainLayout->addSpacing(12);
//  mainLayout->addStretch(1);
  setLayout(mainLayout);

  loadSettings();
  retranslateUi();
}

databasePage::~databasePage()
{
}

QString databasePage::pageName()
{
  return tr("Database");
}

QString databasePage::pageIcon()
{
  return (globalVar::defaultIcons("64", "places") + "/database.png");
}

void databasePage::retranslateUi()
{
  label->setText(tr("<b>Data Bases Settings</b>"));
}

void databasePage::loadSettings()
{
}

void databasePage::saveSettings()
{
  switch (tabWidget->currentIndex()) {
    case 0:
      dbmng->saveSettings();
    break;
    case 1:
      dbcnf->saveSettings();
    break;
  }
}

void databasePage::quickHelp()
{
  //helpDialog *hlp = new helpDialog(this, "gdict.html");
  //hlp->show();
}
