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

#include "dbeditor.h"
#include "globalvar.h"
#include "dbmanager.h"
#include "pluginmanager.h"
#include "plugins.h"
#include "lineedit.h"

dbEditor::dbEditor(QWidget *parent) : QDialog(parent)
{
  mainToolBar = new QToolBar(this);
  
  listWidget = new QListWidget(this);
  listWidget->setIconSize(QSize(22, 22));
  listWidget->setMaximumWidth(128);
  listWidget->setSpacing(2);
  listWidget->setAlternatingRowColors(true);
  listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  connect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(currentChanged(QListWidgetItem*, QListWidgetItem*)));
  
  rightWidget = new QWidget;
  nameLabel = new QLabel(rightWidget);
  nameLabel->setAlignment(Qt::AlignHCenter);
  entryEdit = new lineEdit(this);
  entryEdit->setEnabled(false);
  connect(entryEdit, SIGNAL(editingFinished()), this, SLOT(checkEntry()));
  valueEdit = new QTextEdit(this);
  connect(entryEdit, SIGNAL(returnPressed()), valueEdit, SLOT(setFocus()));
  
  QHBoxLayout *margin = new QHBoxLayout();
  margin->addWidget(entryEdit);
  margin->setSpacing(0);
  
  QVBoxLayout *layout = new QVBoxLayout(rightWidget);
  layout->addWidget(nameLabel);
  layout->addLayout(margin);
  layout->addWidget(valueEdit);
  layout->setMargin(0);
  rightWidget->setLayout(layout);
  
  QSplitter *splitter = new QSplitter(this);
  splitter->addWidget(listWidget);
  splitter->addWidget(rightWidget);
    
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(mainToolBar);
  mainLayout->setMargin(0);
  mainLayout->addWidget(splitter);
  setLayout(mainLayout);
  
  createActions();
  createToolbars();
  
  retranslateUi();
  loadAllDbss();
}

dbEditor::~dbEditor()
{
  pluginManager::close();
}

void dbEditor::createActions()
{
  refreshAction = new QAction(this);
  connect(refreshAction, SIGNAL(triggered()), this, SLOT(loadAllDbss()));
  saveAction = new QAction(this);
  saveAction->setEnabled(false);
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
  closeAction = new QAction(this);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
  editAction = new QAction(this);
  editAction->setCheckable(true);
  connect(editAction, SIGNAL(toggled(bool)), this, SLOT(editDb(bool)));
  deleteAction = new QAction(this);
  deleteAction->setEnabled(false);
  connect(deleteAction, SIGNAL(triggered()), this, SLOT(remove()));
  //connect(closeAction, SIGNAL(triggered()), this, SLOT(editDb()));
}

void dbEditor::createToolbars()
{
  mainToolBar->addAction(refreshAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(editAction);
  mainToolBar->addAction(saveAction);
  mainToolBar->addAction(deleteAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(closeAction);
}

void dbEditor::retranslateUi()
{
  setWindowTitle(tr("Database Editor"));
  
  refreshAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-refresh.png"));
  refreshAction->setWhatsThis(tr("This action refresh databases list."));
  refreshAction->setToolTip("refresh databases list");
  editAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/database-edit.png"));
  editAction->setToolTip("open selected database for edition");
  saveAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-save.png"));
  saveAction->setToolTip("save key and value into databases list");
  closeAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-close.png"));
  closeAction->setToolTip("close database editor dialog");
  deleteAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-delete.png"));
  deleteAction->setToolTip("delete key from selected database");
}

void dbEditor::loadAllDbss()
{
  dbManager::reLoadAll();
  listWidget->clear();
  //if ((pluginManager::group(plugin) == "database") && pluginManager::isEditable(plugin))
  foreach (QString db, dbManager::foundDBs()) {
    if (!pluginManager::plgbyTyple(dbManager::type(db)).isEmpty() && pluginManager::isEditable(pluginManager::plgbyTyple(dbManager::type(db)))) {
	QListWidgetItem *dbItem = new QListWidgetItem(listWidget);
	dbItem->setText(db);
	//
	if (QFile::exists( dbManager::icon(db) ))
	  dbItem->setIcon(QIcon(dbManager::icon(db)));
	else
	  dbItem->setIcon(QIcon(globalVar::defaultIcons("22", "places") + "/database.png"));
      }
  }
}

void dbEditor::currentChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
  if (current) {
    nameLabel->setText(current->text());
  }
  int ret;
  if (previous) {
    if (saveAction->isEnabled()) {
      QMessageBox msgBox;
      msgBox.setText(tr("The database <b>%1</b> has been modified.").arg(previous->text()));
      msgBox.setInformativeText("Do you want to save your changes or discard them?");
      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Save);
      ret = msgBox.exec();
    }
  }
  switch (ret) {
    case QMessageBox::Save:
      save();
      editAction->setChecked(false);
    break;
    case QMessageBox::Discard:
      pluginManager::close();
      editAction->setChecked(false);
      saveAction->setEnabled(false);
    break;
    case QMessageBox::Cancel:
      disconnect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(currentChanged(QListWidgetItem*, QListWidgetItem*)));
      listWidget->setCurrentItem(previous);
      connect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(currentChanged(QListWidgetItem*, QListWidgetItem*)));
    break;
    default:
      editAction->setChecked(false);
      deleteAction->setEnabled(false);
    break;
  }
}

void dbEditor::checkEntry()
{
  valueEdit->setText(pluginManager::check(entryEdit->text()));
  saveAction->setEnabled(true);
  deleteAction->setEnabled(true);
}

void dbEditor::save()
{
  if (!pluginManager::check(entryEdit->text()).isEmpty()) {
    int n = QMessageBox::information(this, tr("Warning"), tr("Are you sure you want to replace <b>%1</b> ?").arg(entryEdit->text()), tr("&Yes"), tr("&No"));
    if(n == 0) {
      saveAction->setEnabled(!pluginManager::replace(entryEdit->text(), valueEdit->toPlainText()));
    }
  } else {
    saveAction->setEnabled(!pluginManager::store(entryEdit->text(), valueEdit->toPlainText()));
  }
}

void dbEditor::remove()
{
  int n = QMessageBox::warning(this, tr("Remove"), tr("Are you sure you want to remove <b>%1</b>?").arg(entryEdit->text()), tr("&Yes"), tr("&No"));
  if(n == 0) {
    pluginManager::remove(entryEdit->text());
    deleteAction->setEnabled(false);
  }
}

void dbEditor::editDb(bool open)
{
  if (pluginManager::open(dbManager::type(listWidget->currentItem()->text()), dbManager::file(listWidget->currentItem()->text())))
    entryEdit->setEnabled(open);
}
