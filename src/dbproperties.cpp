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

#include "dbproperties.h"
#include "globalvar.h"
#include "dbmanager.h"

dbProperties::dbProperties(QWidget *parent, QString dbName) : QDialog(parent)
{
  //setWindowIcon(QIcon(globalVar::defaultIcons("22", "") + "/" + globalVar::appName() + ".png"));
  setModal(false);
  
  headerLayout = new QGridLayout;
  headerLayout->setColumnStretch(0, 0);
  headerLayout->setColumnStretch(1, 1);
  headerLayout->setMargin(6);
  
  textLabel = new QLabel(this);
  textLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  imageLabel = new QLabel(this);
  //imageLabel->setFixedSize(64, 64);
  imageLabel->setFixedHeight(64);
  commentLabel = new QLabel(this);
  commentLabel->setOpenExternalLinks(true);
  commentLabel->setWordWrap(true);
  commentLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  headerLayout->addWidget(imageLabel, 0, 0, 2, 1);
  headerLayout->addWidget(textLabel, 0, 1);
  //headerLayout->addWidget(commentLabel, 1, 1);
  
  tabWidget = new QTabWidget;
  tabWidget->setUsesScrollButtons(false);
  tabWidget->addTab(new generalTab(dbName, this), tr("&General"));
  
  buttonBox = new QDialogButtonBox(Qt::Horizontal);
  closeButton = new QPushButton(this);
  closeButton->setDefault(true);
  buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin(0);
  mainLayout->addLayout(headerLayout);
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);
  
  retranslateUi(dbName);
}

dbProperties::~dbProperties()
{
}

void dbProperties::retranslateUi(QString dbName)
{
  setWindowTitle(tr("Properties for - %1").arg(dbName));
  imageLabel->setPixmap(dbManager::icon(dbName));
  textLabel->setText(tr("<html><font size=\"5\">%1</font><br /><b>Version %2</b><br />%3</html>").arg(dbName, dbManager::version(dbName), dbManager::description(dbName)));
  
  closeButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-close.png"));
  closeButton->setText(tr("&Close"));
}

generalTab::generalTab(QString dbName, QWidget *parent) : QWidget(parent)
{
  QFileInfo fi(dbManager::file(dbName));
  // FIXME word number, creator, license, date of creation, editor(plugin) permision
  QGridLayout *grid = new QGridLayout(this);
  grid->setColumnStretch(0, 0);
  grid->setColumnStretch(1, 0);
  grid->setColumnStretch(2, 1);
  
  QLabel *l1 = new QLabel(tr("Type:"));
  QLabel *la = new QLabel;
  la->setText(dbManager::type(dbName));
  QLabel *l2 = new QLabel(tr("Location:"));
  QLabel *lb = new QLabel;
  // FIXME location dir
  //lb->setText(dbManager::file(dbName));
  lb->setText(fi.absolutePath());
  QLabel *l3 = new QLabel(tr("Size:"));
  QLabel *lc = new QLabel;
  lc->setText(tr("%1 bytes").arg(fi.size()));
  QLabel *l4 = new QLabel(tr("Number of Entries:"));
  QLabel *ld = new QLabel;
  grid->addWidget(l1, 0, 0, Qt::AlignLeft);
  grid->addWidget(la, 0, 1, Qt::AlignLeft);
  grid->addWidget(l2, 1, 0, Qt::AlignLeft);
  grid->addWidget(lb, 1, 1, Qt::AlignLeft);
  grid->addWidget(l3, 2, 0, Qt::AlignLeft);
  grid->addWidget(lc, 2, 1, Qt::AlignLeft);
  grid->addWidget(l4, 3, 0, Qt::AlignLeft);
  grid->addWidget(ld, 3, 1, Qt::AlignLeft);
}
