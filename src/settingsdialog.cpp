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

#include "settingsdialog.h"
#include "settingspages.h"
#include "globalvar.h"

settingsDialog::settingsDialog(QWidget *parent) : QDialog(parent)
{
  /*list*/
  contentsWidget = new QListWidget;
  contentsWidget->setViewMode(QListView::IconMode);
  contentsWidget->setIconSize(QSize(96, 84));
  contentsWidget->setMovement(QListView::Static);
  contentsWidget->setMaximumWidth(128);
  contentsWidget->setSpacing(2);
  connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(changePage(QListWidgetItem *, QListWidgetItem *)));

  /*pages*/
  pagesWidget = new QStackedWidget;
  genPage = new generalPage(this);
  addPageWidget(genPage, genPage->pageName(), genPage->pageIcon());
  dirPage = new directoryPage(this);
  addPageWidget(dirPage, dirPage->pageName(), dirPage->pageIcon());
  dbPage = new databasePage(this);
  addPageWidget(dbPage, dbPage->pageName(), dbPage->pageIcon());
  plgnPage = new pluginPage(this);
  addPageWidget(plgnPage, plgnPage->pageName(), plgnPage->pageIcon());
  //pagesWidget->addWidget(genPage);

  /*seperate*/
  QFrame *frame = new QFrame;
  frame->setFrameStyle(QFrame::HLine | QFrame::Sunken);

  /*buttons*/
  createButtons();
  buttonBox = new QDialogButtonBox(Qt::Horizontal);
  buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
  buttonBox->addButton(applyButton, QDialogButtonBox::ApplyRole);
  buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);
  buttonBox->addButton(helpButton, QDialogButtonBox::HelpRole);
  buttonBox->addButton(resetButton, QDialogButtonBox::ResetRole);

  QSplitter *splitter = new QSplitter(this);
  splitter->addWidget(contentsWidget);
  splitter->addWidget(pagesWidget);
  //splitter->setStretchFactor(splitter->indexOf(contentsWidget), 0);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(splitter);
  mainLayout->addWidget(frame);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);

  contentsWidget->setCurrentRow(0);

  retranslateUi();
  updateActions();
  
/*  for (int i = 0; i < pagesWidget->count(); ++i) {
    connect(helpButton, SIGNAL(clicked()), pagesWidget->widget(i), SLOT(quickHelp()));
  }*/
}

settingsDialog::~settingsDialog()
{
}

void settingsDialog::createButtons()
{
  closeButton = new QPushButton(this);
  closeButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-cancel.png"));
  okButton = new QPushButton(this);
  okButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-ok.png"));
  applyButton = new QPushButton(this);
  applyButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-ok-apply.png"));
  helpButton = new QPushButton(this);
  helpButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-contextual.png"));
  resetButton = new QPushButton(this);
  resetButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-undo.png"));

  //applyButton->setEnabled(false);
  closeButton->setDefault(true);
}

void settingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
  if (applyButton->isEnabled()) {
  }
  if (!current)
    current = previous;

  pagesWidget->setCurrentIndex(contentsWidget->row(current));
  //updateActions();
}

void settingsDialog::addPageWidget(QWidget *page,
                                        const QString &itemName,
                                        const QString &pixmapName)
{
  pagesWidget->addWidget(page);
  QListWidgetItem *pageBtn = new QListWidgetItem(contentsWidget);
  pageBtn->setText(itemName);
  pageBtn->setIcon(QIcon(pixmapName));
  pageBtn->setTextAlignment(Qt::AlignHCenter);
  pageBtn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void settingsDialog::updateActions()
{
  connect(helpButton, SIGNAL(clicked()), this, SLOT(showHelp()));
  /*defaults...*/
  connect(okButton, SIGNAL(clicked()), this, SLOT(submitSettings()));
  connect(applyButton, SIGNAL(clicked()), this, SLOT(applySettings()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void settingsDialog::retranslateUi()
{
  setWindowTitle(tr("Configure - %1").arg(globalVar::appName()));
  setWindowIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/" + globalVar::appName() + ".png"));
  //setToolTip(globalVar::appName() + " Configuration.");

  closeButton->setText(tr("&Cancel"));
  okButton->setText(tr("&Ok"));
  applyButton->setText(tr("&Apply"));
  helpButton->setText(tr("&Help"));
  resetButton->setText(tr("&Defaults"));
}

void settingsDialog::quickHelp()
{
  //helpDialog *hlp = new helpDialog(this, "introduction.html");
  //hlp->show();
}

void settingsDialog::showHelp()
{
  switch (pagesWidget->currentIndex()) {
    case 0:
      genPage->quickHelp();
    break;
    case 1:
      dirPage->quickHelp();
    break;
    case 2:
      dbPage->quickHelp();
    break;
    case 3:
      plgnPage->quickHelp();
    break;
    default:
      this->quickHelp();
  }
}

void settingsDialog::applySettings()
{
  switch (pagesWidget->currentIndex()) {
    case 0:
      genPage->saveSettings();
    break;
    case 1:
      dirPage->saveSettings();
    break;
    case 2:
      dbPage->saveSettings();
    break;
    case 3:
      plgnPage->saveSettings();
    break;
//     default:
//       this->quickHelp();
  }
  emit settingModified();
}

void settingsDialog::submitSettings()
{
  applySettings();
  //emit settingModified();
  this->close();
}
