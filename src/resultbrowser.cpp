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

#include <QtGui/QContextMenuEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMenu>
#include <QDebug>
#include <QSettings>

#include "resultbrowser.h"
#include "globalvar.h"

resultBrowser::resultBrowser(QWidget *parent) : QTextBrowser(parent)
{
  setOpenExternalLinks ( false );
  setOpenLinks ( false );
  
  //"h1, h2 {background: none; font-weight: normal; margin: 0; padding-top: .5em; padding-bottom: .17em; border-bottom: 1px solid #aaa;}"
  
  
  doc = document();
  //QString sheet = "h1 { color: %1; font-size: 188%; text-decoration: underline; background: #fdeeee;} h2 { color: #585858; align: justify;}";
  //doc->setDefaultStyleSheet(sheet).arg(settings.value("generals/bgcolor").value<QColor>().name());
  //doc->setDefaultFont(QFont("Times", 25, QFont::Bold));
  //textBrowser->setDefaultStyleSheet(globalVar::dataPath() + "/default.css");
  
  createActions();
  createMenus();
  retranslateUi();
  loadSettings();
}

void resultBrowser::createActions()
{
  copyAction = new QAction(this);
  copyAction->setEnabled(false);
  connect(this, SIGNAL(copyAvailable(bool)), copyAction, SLOT(setEnabled(bool)));
  connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
  selectAllAction = new QAction(this);
  connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));
//   deslctAllAction = new QAction(this);
//   deslctAllAction->setEnabled(false);
//   connect(this, SIGNAL(copyAvailable(bool)), deslctAllAction, SLOT(setEnabled(bool)));
//   connect(deslctAllAction, SIGNAL(triggered()), this, SLOT(deSelect()));
  findAction = new QAction(this);
  findAction->setEnabled(false);
  connect(this, SIGNAL(copyAvailable(bool)), findAction, SLOT(setEnabled(bool)));
  connect(findAction, SIGNAL(triggered()), this, SLOT(requestWord()));
  bkmrkAction  = new QAction(this);
  bkmrkAction->setEnabled(false);
  connect(this, SIGNAL(copyAvailable(bool)), bkmrkAction, SLOT(setEnabled(bool)));
//   connect(bkmrkAction, SIGNAL(triggered()), this, SLOT(bkmrkWord()));/*add slot to bookmark manager*/
}

void resultBrowser::createMenus()
{
  menu = createStandardContextMenu();
  menu->clear ();
  menu->addAction(copyAction);
  menu->addAction(selectAllAction);
//   menu->addAction(deslctAllAction);
  menu->addSeparator();
  menu->addAction(findAction);
  menu->addAction(bkmrkAction);
}

void resultBrowser::retranslateUi()
{
  copyAction->setText(tr("&Copy"));
  copyAction->setStatusTip(tr("Copy selected text to clipboard"));
  copyAction->setShortcut(tr("Ctrl+C"));
  copyAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-copy.png"));
  
  selectAllAction->setText(tr("Select &All"));
  selectAllAction->setStatusTip(tr("Select all text"));
  selectAllAction->setShortcut(tr("Ctrl+A"));
  selectAllAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-select-all.png"));
  
//   deslctAllAction->setText(tr("Deselect"));
//   deslctAllAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-select-none.png"));
  
  findAction->setText(tr("&Find"));
  //findAction->setShortcut(QKeySequence::Find);
  //findAction->setStatusTip(tr("Quit %1").arg(globalVar::appName()));
  findAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-find.png"));
  
  bkmrkAction->setText(tr("&Bookmark"));
  bkmrkAction->setStatusTip(tr("Open bookmark dialog"));
  bkmrkAction->setShortcut(tr("Ctrl+B"));
  bkmrkAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/bookmark-new.png"));
}

void resultBrowser::contextMenuEvent(QContextMenuEvent *event) {
  menu->exec(event->globalPos());
}

void resultBrowser::requestWord()
{
  if (textCursor().hasSelection())
    emit requestedWord(textCursor().selectedText());
}

/*void resultBrowser::deSelect()
{
	textCursor().clearSelection();//FIXME:doesn't work
// 	this->setTextCursor(textCursor());
}*/

QString resultBrowser::fontWeight(int w)
{
  QString fw;
  switch (w){
    case 25:
      fw = "light";
    break;
    case 50:
      fw = "normal";
    break;
    case 63:
      fw = "demibold";
    break;
    case 75:
      fw = "bold";
    break;
    case 87:
      fw = "black";
    break;
  }
  
  return fw;
}

void resultBrowser::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  QString hdtxtc, hdbgc, rstxtc, rsbgc;
  hdtxtc = settings.value("generals/hdtxtColor").value<QColor>().name();
  hdbgc = settings.value("generals/hdbgColor").value<QColor>().name();
  rstxtc = settings.value("generals/rstxtColor").value<QColor>().name();
  rsbgc = settings.value("generals/rsbgColor").value<QColor>().name();
  hdFont.fromString(settings.value("generals/hdtxtFont").toString());
  rsFont.fromString(settings.value("generals/rstxtFont").toString());
  
  if (hdtxtc == "#000000")
    hdtxtc = "#000000";
  if (hdbgc == "#000000")
    hdbgc = "#ffffff";
  if (rstxtc == "#000000")
    rstxtc = "#000000";
  if (rsbgc == "#000000")
    rsbgc = "#ffffff";
  
  QString ws = QString::number(hdFont.pointSize(), 10) + "pt";
  doc->setDefaultStyleSheet(QString("h1 { color: %1; font-family: %2; font-weight: %3; font-size: %4; text-decoration: underline; background: %5;} body { color: %6; font-family: %7; align: justify; background:%8;}").arg(hdtxtc, hdFont.family(), fontWeight(hdFont.weight()), ws, hdbgc, rstxtc, rsFont.family(), rsbgc));
}
