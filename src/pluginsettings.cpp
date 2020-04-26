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

#include "pluginsettings.h"
#include "pluginmanager.h"
#include "globalvar.h"
#include "plugins.h"

pluginSettings::pluginSettings(QWidget *parent, QString plgName) : QDialog(parent)
{
  setModal(true);
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin(0);
  
  createButtons();
  buttonBox = new QDialogButtonBox(Qt::Horizontal);
  buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
  buttonBox->addButton(applyButton, QDialogButtonBox::ApplyRole);
  buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);
  
  QString fileName = pluginManager::file(plgName);
  QPluginLoader loader(fileName);
  QObject *plugin = loader.instance();
      
  //FIXME find a way to avoid build each object every time 
  CommonPlugin *iCommon = qobject_cast<CommonPlugin *>(plugin);
  if (iCommon) {
    mainLayout->addWidget(iCommon->createConfWidget(this));
    //connect(applyButton, SIGNAL(clicked()), iCommon, SLOT(saveSetting()));
  }
  DatabasePlugin *iDatabase = qobject_cast<DatabasePlugin *>(plugin);
  if (iDatabase) {
    mainLayout->addWidget(iDatabase->createConfWidget(this));
    //connect(applyButton, SIGNAL(clicked()), plugin, SLOT(saveSetting()));
  }
  InterfacePlugin *iInterface = qobject_cast<InterfacePlugin *>(plugin);
  if (iInterface) {
    mainLayout->addWidget(iInterface->createConfWidget(this));
    //connect(applyButton, SIGNAL(clicked()), iInterface, SLOT(saveSetting()));
  }
  
  connect(applyButton, SIGNAL(clicked()), plugin, SLOT(saveSettings()));
  connect(okButton, SIGNAL(clicked()), plugin, SLOT(saveSettings()));
  connect(okButton, SIGNAL(clicked()), plugin, SLOT(close()));
  QFrame *frame = new QFrame;
  frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  
  mainLayout->addWidget(frame);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);
  
  retranslateUi();
}

pluginSettings::~pluginSettings()
{
}
/*
void pluginSettings::retranslateUi(QString plgName)
{
}*/

void pluginSettings::createButtons()
{
  closeButton = new QPushButton(this);
  closeButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-cancel.png"));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
  okButton = new QPushButton(this);
  okButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-ok.png"));
  applyButton = new QPushButton(this);
  applyButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-ok-apply.png"));
}

void pluginSettings::retranslateUi()
{
  closeButton->setText(tr("&Cancel"));
  okButton->setText(tr("&Ok"));
  applyButton->setText(tr("&Apply"));
}
