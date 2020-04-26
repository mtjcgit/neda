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

#include "settingsdirs.h"
#include "globalvar.h"
#include "filechooser.h"
#include "helpdialog.h"

directoryPage::directoryPage(QWidget *parent) : QWidget(parent)
{
  label = new QLabel(this);
  label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

  dirGroup = new QGroupBox(this);

  dbDir = new fileChooser(this);
  dbDir->setEnabled(false);
  dbDir->setDialogType(fileChooser::GetDirectory);
  //connect(dbDir, SIGNAL(lineditChanged(bool)), this, SIGNAL(boolHappened(bool)));
  connect(dbDir, SIGNAL(textChanged(const QString&)), this, SLOT(dirEdited(const QString &)) );
  connect(dbDir, SIGNAL(textEdited(const QString&)), this, SLOT(dirEdited(const QString &)) );

  newdbDir = new QPushButton(this);
  removedbDir = new QPushButton(this);
  dbdirList = new QListWidget(this);
  updbDir = new QPushButton(this);
  downDir = new QPushButton(this);
  clrdbDir = new QPushButton(this);

  connect(newdbDir, SIGNAL(clicked()), this, SLOT(newdbdirFunc()));
  connect(removedbDir, SIGNAL(clicked()), this, SLOT(dblistRemove()));
  //connect(removedbDir, SIGNAL(clicked()), this, SIGNAL(changHappened()));
  connect(updbDir, SIGNAL(clicked()), this, SLOT(dblistUp()));
  //connect(updbDir, SIGNAL(clicked()), this, SIGNAL(changHappened()));
  connect(downDir, SIGNAL(clicked()), this, SLOT(dblistDown()));
  //connect(downDir, SIGNAL(clicked()), this, SIGNAL(changHappened()));
  //connect(downDir, SIGNAL(clicked(bool)), this, SIGNAL(boolHappened(bool)));
  connect(clrdbDir, SIGNAL(clicked()), this, SLOT(dblistClr()));
  //connect(clrdbDir, SIGNAL(clicked()), this, SIGNAL(changHappened()));
  connect(dbdirList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemAction(QListWidgetItem *)));
  connect(dbdirList, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(itemAction(QListWidgetItem *)));
  //connect(dbdirList, SIGNAL(itemSelectionChanged()), this, SIGNAL(changHappened()));

  QVBoxLayout *controlLayout = new QVBoxLayout;
  controlLayout->addWidget(removedbDir);
  controlLayout->addWidget(updbDir);
  controlLayout->addWidget(downDir);
  controlLayout->addWidget(clrdbDir);
  controlLayout->addStretch(0);

  QGridLayout *controlsLayout = new QGridLayout;
  controlsLayout->addWidget(dbDir, 0, 0);
  controlsLayout->addWidget(newdbDir, 0, 1);
  controlsLayout->addWidget(dbdirList, 1, 0);
  controlsLayout->addLayout(controlLayout, 1, 1);
  
  dirGroup->setLayout(controlsLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin( 0 );
  mainLayout->addWidget(label);
  mainLayout->addWidget(dirGroup);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
  deactiveControls();
}

directoryPage::~directoryPage()
{
}

QString directoryPage::pageName()
{
  return tr("Directory");
}

QString directoryPage::pageIcon()
{
  return (globalVar::defaultIcons("64", "places") + "/folder.png");
}

void directoryPage::retranslateUi()
{
  label->setText(tr("<b>Directories Settings</b>"));
  dirGroup->setTitle(tr("&Database Directories"));
  dbDir->setCaption(tr("Select database directory"));
  newdbDir->setText(tr("&New"));
  newdbDir->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/folder-new.png"));
  removedbDir->setText(tr("&Remove"));
  removedbDir->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/list-remove.png"));
  updbDir->setText(tr("&Up"));
  updbDir->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-up.png"));
  downDir->setText(tr("&Down"));
  downDir->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-down.png"));
  clrdbDir->setText(tr("&Clear All"));
  clrdbDir->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-clear-list.png"));
}

void directoryPage::loadSettings()
{
  dbdirList->clear();
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  QStringList dbdirs = settings.value("directories/dbDires").toString().split(", ", QString::SkipEmptyParts);
  dbdirList->addItems(dbdirs);

  //dbDir->setText(settings.value("directories/dbDires").toString());
  //splashCheckBox->setChecked( settings.value("generals/RunSplashOnStart").toBool() );
  //tipCheckBox->setChecked( settings.value("generals/RunTipOnStart").toBool() );
}

void directoryPage::saveSettings()
{
  QStringList paths;
  for ( int rowIndex = 0 ; rowIndex < dbdirList->count() ; rowIndex++ ) {
    if ( !dbdirList->item(rowIndex)->text().isEmpty() && QFile::exists(dbdirList->item(rowIndex)->text())) {
      paths << dbdirList->item(rowIndex)->text();
    }
  }
  QString str = paths.join(", ");
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("directories/dbDires", str);
}

void directoryPage::quickHelp()
{
  //helpDialog *hlp = new helpDialog(this, "gdictui.html");
  //hlp->show();
}

void directoryPage::deactiveControls()
{
  removedbDir->setEnabled(false);
  updbDir->setEnabled(false);
  downDir->setEnabled(false);
}

void directoryPage::newdbdirFunc()
{
  dbdirList->insertItem( 0 , QString() );
  dbdirList->setCurrentRow( 0 );
  itemAction(dbdirList->currentItem());
  dbDir->setText(QString());
  dbDir->setFocus();
}

void directoryPage::dblistRemove()
{
  dbDir->setText(QString());
  delete dbdirList->currentItem();
  removedbDir->setEnabled( false );
  updbDir->setEnabled( false );
  downDir->setEnabled( false );
  dbDir->setEnabled( false );
}

void directoryPage::dblistUp()
{
  int cur = dbdirList->currentRow();
  if ( cur>0 ) {
    QString txt = dbdirList->item(cur - 1)->text();
    delete dbdirList->takeItem( cur - 1 );
    dbdirList->insertItem( cur , txt );
    dbdirList->setEnabled( cur-1>0 );
    dbdirList->setEnabled( true );
  }
}

void directoryPage::dblistDown()
{
  int cur = dbdirList->currentRow();
  if ( cur < dbdirList->count()-1 ) {
    QString txt = dbdirList->item(cur+1)->text();
    delete dbdirList->takeItem( cur+1 );
    dbdirList->insertItem( cur , txt );
    
    updbDir->setEnabled( true );
    downDir->setEnabled( cur+1<dbdirList->count()-1 );
  }
}

void directoryPage::dblistClr()
{
  if (dbdirList->count() != 0) {
    dbdirList->clear();
    deactiveControls();
  }
}

void directoryPage::itemAction(QListWidgetItem *item)
{
  dbDir->setEnabled( item!=0 );
  removedbDir->setEnabled( item!=0 );
  
  int cur = dbdirList->currentRow();
  downDir->setEnabled( item!=0 && cur<dbdirList->count()-1 );
  updbDir->setEnabled( item!=0 && cur>0 );
  dbDir->setText( item!=0 ? item->text() : QString() );
}

void directoryPage::dirEdited(const QString &txt )
{
  if ( dbdirList->currentItem()->text() != txt ) {
    dbdirList->blockSignals(true);
    dbdirList->currentItem()->setText(txt);
    dbdirList->blockSignals(false);
  }
}
