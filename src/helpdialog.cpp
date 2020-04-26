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

#include "helpdialog.h"
#include "globalvar.h"
#include "searchbar.h"
#include "langmanager.h"

//helpDialog::helpDialog(QWidget *parent) : QDialog(parent)
helpDialog::helpDialog(QWidget *parent, const QString &page) : QDialog(parent)
{
  setWindowIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-contents.png"));
  resize(450, 400);
  setAttribute(Qt::WA_DeleteOnClose);
  setAttribute(Qt::WA_GroupLeader);

  mainToolBar = new QToolBar(this);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(mainToolBar);
  buttonLayout->setSpacing(1);
  buttonLayout->setMargin(0);

  textBrowser = new QTextBrowser(this);
  QStringList paths;
  // FIXME paths
  paths << globalVar::helps() << globalVar::defaultIcons("22", "actions") << globalVar::dataPath() << "." << "/usr/local/share/doc";
  textBrowser->setSearchPaths(paths);
  textBrowser->setSource(globalVar::helps() + "/" + langManager::current() + "/html/" + page);
  
  findBar = new searchBar(this);
  findBar->setTextWidget(textBrowser);
  findBar->hide();
  
  createActions();
  createToolbars();
  
  connect(textBrowser, SIGNAL(sourceChanged(const QUrl &)), this, SLOT(updateWindowTitle()));
  connect(textBrowser, SIGNAL(copyAvailable(bool)), copyAction, SLOT(setEnabled(bool)));

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(textBrowser);
  mainLayout->addWidget(findBar);
  setLayout(mainLayout);
  retranslateUi();
}

helpDialog::~helpDialog()
{
}

void helpDialog::updateWindowTitle()
{
  setWindowTitle(tr("%1 - %2").arg(globalVar::appName()).arg(textBrowser->documentTitle()));
}

void helpDialog::createActions()
{
  homeAction = new QAction(this);
  connect(homeAction, SIGNAL(triggered()), textBrowser, SLOT(home()));
  backwardAction = new QAction(this);
  connect(backwardAction, SIGNAL(triggered()), textBrowser, SLOT(backward()));
  forwardAction = new QAction(this);
  connect(forwardAction, SIGNAL(triggered()), textBrowser, SLOT(forward()));
  refreshAction = new QAction(this);
  connect(refreshAction, SIGNAL(triggered()), textBrowser, SLOT(reload()));
  copyAction = new QAction(this);
  copyAction->setEnabled(false);
  connect(copyAction, SIGNAL(triggered()), textBrowser, SLOT(copy()));
  printAction = new QAction(this);
  connect(printAction, SIGNAL(triggered()), this, SLOT(showPrintDialog()));
  printPrwAction = new QAction(this);
  connect(printPrwAction, SIGNAL(triggered()), this, SLOT(showPrintPreview()));
  findAction = new QAction(this);
  findAction->setCheckable(true);
  connect(findAction, SIGNAL(toggled(bool)), findBar, SLOT(showSearchBar(bool)));
  zoomInAction = new QAction(this);
  connect(zoomInAction, SIGNAL(triggered()), textBrowser, SLOT(zoomIn()));
  zoomOutAction = new QAction(this);
  connect(zoomOutAction, SIGNAL(triggered()), textBrowser, SLOT(zoomOut()));
  zoomOrgAction = new QAction(this);
  // FIXME connection for zoomOrgAction
  closeAction = new QAction(this);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
}

void helpDialog::createToolbars()
{
  mainToolBar->addAction(homeAction);
  mainToolBar->addAction(backwardAction);
  mainToolBar->addAction(forwardAction);
  mainToolBar->addAction(refreshAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(copyAction);
  mainToolBar->addAction(printAction);
  mainToolBar->addAction(printPrwAction);
  mainToolBar->addAction(findAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(zoomInAction);
  mainToolBar->addAction(zoomOutAction);
  //mainToolBar->addAction(zoomOrgAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(closeAction);
}

void helpDialog::retranslateUi()
{
  setWindowTitle(tr("Help - %1").arg(globalVar::appName()));

  homeAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-home.png"));
  homeAction->setToolTip(tr("Home"));
  homeAction->setWhatsThis(tr("go home."));
  backwardAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-previous.png"));
  forwardAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-next.png"));
  refreshAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-refresh.png"));
  copyAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-copy.png"));
  printAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-print.png"));
  printPrwAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-print-preview.png"));
  findAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-find.png"));
  findAction->setToolTip(tr("Find in Text..."));
  findAction->setShortcut(QKeySequence::Find);
  zoomInAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/zoom-in.png"));
  zoomOutAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/zoom-out.png"));
  zoomOrgAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/zoom-original.png"));
  closeAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-close.png"));
  //closeAction->setShortcut(tr("Esc"));
}

void helpDialog::showFindWidget(bool b)
{
  // FIXME this function never used !!
  findBar->showSearchBar(b);
}

void helpDialog::showPrintDialog()
{
#ifndef QT_NO_PRINTER
   QPrinter printer(QPrinter::HighResolution);
  QPrintDialog *dlg = new QPrintDialog(&printer, this);
  if (textBrowser->textCursor().hasSelection())
    dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    //dlg->setWindowTitle(tr("Print Document"));
  dlg->addEnabledOption(QAbstractPrintDialog::PrintPageRange);
  dlg->addEnabledOption(QAbstractPrintDialog::PrintCollateCopies);
  if (dlg->exec() == QDialog::Accepted) {
    textBrowser->print(&printer);
  }
  delete dlg;
#endif
}

void helpDialog::showPrintPreview()
{
#ifndef QT_NO_PRINTER
  QPrinter printer(QPrinter::HighResolution);
  QPrintPreviewDialog preview(&printer, this);
  connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
  preview.exec();
#endif
}

void helpDialog::printPreview(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
  textBrowser->print(printer);
#else
  Q_UNUSED(printer);
#endif
}
