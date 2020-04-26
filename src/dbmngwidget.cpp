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

#include "dbmngwidget.h"
#include "globalvar.h"
#include "dbselector.h"
#include "dbmanager.h"
#include "dbproperties.h"
#include "dbcreatewizard.h"

dbMngWidget::dbMngWidget(QWidget *parent) : QWidget(parent)
{
  dbSel = new dbSelector( this );
  dbSel->setMoveOnDoubleClick(true);
  dbSel->setKeyboardEnabled(true);
  dbSel->avlbListWidget()->setSelectionMode(QAbstractItemView::ExtendedSelection);
  //dbSel->avlbListWidget()->setIconSize(QSize(24, 24));
  //dbSel->avlbListWidget()->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/database.png"));
  dbSel->setSortingEnabled(true);

  connect(dbSel->slctdListWidget(), SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemAction(QListWidgetItem *)));

  dbInfo = new QPushButton(this);
  dbInfo->setEnabled(false);
  connect(dbInfo, SIGNAL(clicked()), this, SLOT(showProperties()));
  dbReload = new QPushButton(this);
  connect(dbReload, SIGNAL(clicked()), this, SLOT(dbRefresh()));
  createBtn = new QPushButton(this);
  connect(createBtn, SIGNAL(clicked()), this, SLOT(createNewdb()));
/*	removedbDir = new QPushButton(this);
	dbdirList = new QListWidget(this);
	updbDir = new QPushButton(this);
	downDir = new QPushButton(this);
	clrdbDir = new QPushButton(this);*/

  QVBoxLayout *controlLayout = new QVBoxLayout;
  controlLayout->addWidget(createBtn);
  controlLayout->addWidget(dbInfo);
  controlLayout->addWidget(dbReload);
  controlLayout->addStretch(0);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(dbSel);
  mainLayout->addLayout(controlLayout);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
}

void dbMngWidget::retranslateUi()
{
  dbSel->setAvailableLabel( tr("A&vailable databases:") );
  dbSel->setSelectedLabel( tr("S&elected databases:") );

  createBtn->setText(tr("&New"));
  createBtn->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/folder-new.png"));

  dbInfo->setText(tr("&Properties"));
  dbInfo->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about.png"));

  dbReload->setText(tr("&Reload"));
  dbReload->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-refresh.png"));
}

void dbMngWidget::loadSettings()
{
  dbSel->slctdListWidget()->clear();
  //dbSel->slctdListWidget()->addItems(dbs);
  //dbManager::setSelected(dbs);
  dbRefresh();
}

void dbMngWidget::dbRefresh()
{
  dbManager::reLoadAll();
  dbSel->slctdListWidget()->clear();
  dbSel->avlbListWidget()->clear();
  dbSel->slctdListWidget()->addItems(dbManager::selectedDBs());
  dbSel->avlbListWidget()->addItems(dbManager::availableDBs());
}

void dbMngWidget::saveSettings()
{
  QStringList dbs;
  for ( int rowIndex = 0 ; rowIndex < dbSel->slctdListWidget()->count() ; rowIndex++ ) {
    dbs << dbSel->slctdListWidget()->item(rowIndex)->text();
  }
  QString str = dbs.join(", ");
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("databases/Selected", str);
}

void dbMngWidget::itemAction(QListWidgetItem *item)
{
  dbInfo->setEnabled( item!=0 );
}

void dbMngWidget::showProperties()
{
  dbprp = new dbProperties(this, dbSel->slctdListWidget()->currentItem()->text());
  dbprp->show();
}

void dbMngWidget::createNewdb()
{
  newdbWzrd = new dbcreateWizard(this);
  newdbWzrd->show();
  /*if (dbManager::createNew())
    qDebug() << "created";*/
}
