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
#include <QFile>

#include "mainwindow.h"
#include "globalvar.h"
#include "langmanager.h"
#include "pluginmanager.h"
#include "plugins.h"
#include "resultbrowser.h"
#include "trayicon.h"
#include "lineedit.h"
#include "searchbar.h"
#include "switchlanguagedialog.h"
#include "tipdialog.h"
#include "aboutdialog.h"
#include "helpdialog.h"
#include "settingsdialog.h"
#include "searchmanager.h"
#include "basepanel.h"
#include "dbcreatewizard.h"
#include "dbeditor.h"
#include "historyprovider.h"

QStringList mainWindow::filters;

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
  centralWidget = new QWidget;
  setCentralWidget(centralWidget);
  
  wrdEdit = new lineEdit();
  connect(wrdEdit, SIGNAL(returnPressed()), this, SLOT(sendPlugin()));
//FIXME   connect(wrdEdit, SIGNAL(textChanged(QString)), this, SLOT(checkState(QString)));
  
  fltrCombo = new QComboBox(this);
  connect(fltrCombo, SIGNAL(activated(QString)), this, SLOT(filterChanged(QString)));
  
  //FIXME add to settings dialog for arbitrary filter setting
  filters << "All" << "CODEN" << "DOI" << "ISBN" << "ISO" << "ISSN" << "LCCN";
  fltrCombo->addItems(filters);
  lkpButton = new QPushButton(this);
  connect(lkpButton, SIGNAL(clicked()), this, SLOT(sendPlugin()));
  textBrowser = new resultBrowser(this);
  connect(textBrowser, SIGNAL(requestedWord(QString)), this, SLOT(wordRequested(QString)));
  clipboard = QApplication::clipboard();
  connect(clipboard, SIGNAL(dataChanged()), this, SLOT(showTrayMessage()));
  originalPalette = QApplication::palette();
  /*Search Bar*/
  findBar = new searchBar(this);
  findBar->setTextWidget(textBrowser);
  findBar->hide();
  
  QVBoxLayout *mainLayout = new QVBoxLayout();
  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addWidget(fltrCombo);
  hLayout->addWidget(wrdEdit);
  hLayout->addWidget(lkpButton);
  mainLayout->addLayout(hLayout);
  mainLayout->addWidget(textBrowser);
  mainLayout->addWidget(findBar);
  centralWidget->setLayout(mainLayout);
  
  history = new historyProvider();
  
  createActions();
  createMenus();
  createToolbars();
  createPanels();
  createTrayIcon();
  
  connect(tray, SIGNAL(trayClicked()), this, SLOT(slotTogglePopupWindow()));
  connect(tray, SIGNAL(messageClicked()), this, SLOT(trayMessageClicked()));
  connect(trayAction, SIGNAL(triggered(bool)), tray, SLOT(setVisible(bool)));

  setWindowTitle(globalVar::appName());
  setWindowIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/" + globalVar::appName() + ".png"));
  resize(500, 500);
  
  wrdEdit->setFocus();
  
  loadSettings();
  retranslateUi();
  
  if (!globalVar::reqWord().isEmpty())
    wordRequested(globalVar::reqWord());
  
  Phonon::Path phononPath;

  mediaObject = new Phonon::MediaObject(this);
  audioOutput = new Phonon::AudioOutput(Phonon::NoCategory, this);
  phononPath = Phonon::createPath(mediaObject, audioOutput);
  audioOutput ->setVolume( 70 );
}

mainWindow::~mainWindow()
{
  //saveSettings();
}

void mainWindow::statusbarMessage(QString message)
{
  // FIXME set time in settings dialog
  statusBar()->showMessage(message, 2000);
}

void mainWindow::createActions()
{
  printAction = new QAction(this);
  connect(printAction, SIGNAL(triggered()), this, SLOT(showPrintDialog()));
  printPrwAction = new QAction(this);
  connect(printPrwAction, SIGNAL(triggered()), this, SLOT(showPrintPreview()));
  newDbAction = new QAction(this);
  connect(newDbAction, SIGNAL(triggered()), this, SLOT(showNewDbWizard()));
  dbEditorAction = new QAction(this);
  connect(dbEditorAction, SIGNAL(triggered()), this, SLOT(showDbEditor()));
  quitAction = new QAction(this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  zoomInAction = new QAction(this);
  connect(zoomInAction, SIGNAL(triggered()), textBrowser, SLOT(zoomIn()));
  zoomOutAction = new QAction(this);
  connect(zoomOutAction, SIGNAL(triggered()), textBrowser, SLOT(zoomOut()));
  fullScreenAction = new QAction(this);
  connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(showFullScreen()));
  showNormalAction = new QAction(this);
  connect(showNormalAction, SIGNAL(triggered()), this, SLOT(showNormal()));
  settingsAction = new QAction(this);
  connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
  tipAction = new QAction(this);
  connect(tipAction, SIGNAL(triggered()), this, SLOT(showTipDialog()));
  helpAction = new QAction(this);
  connect(helpAction, SIGNAL(triggered()), this, SLOT(showHelpDialog()));
  languageAction = new QAction(this);
  connect(languageAction, SIGNAL(triggered()), this, SLOT(showLanguageDialog()));
  whatsThisAction = new QAction(this);
  connect(whatsThisAction, SIGNAL(triggered()), this, SLOT(onWhatsThis()));
  aboutAction = new QAction(this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
  aboutQtAction = new QAction(this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
  trayAction = new QAction(this);
  trayAction->setCheckable(true);
  stayontopAction = new QAction(this);
  stayontopAction->setCheckable(true);
  connect(stayontopAction, SIGNAL(toggled(bool)), this, SLOT(stayontop(bool)));
  clrhistAction = new QAction(this);
  connect(clrhistAction, SIGNAL(triggered()), this, SLOT(clearHistory()));
  srchAction = new QAction(this);
  srchAction->setCheckable(true);
  connect(srchAction, SIGNAL(toggled(bool)), findBar, SLOT(showSearchBar(bool)));
  showNotify = new QAction(this);
  showNotify->setCheckable(true);
  connect(showNotify, SIGNAL(toggled(bool)), this, SLOT(showNotification(bool)));
  restoreAction = new QAction(this);
  connect(restoreAction, SIGNAL(triggered()), this, SLOT(slotTogglePopupWindow()));
  playAction = new QAction(this);
  connect(playAction, SIGNAL(triggered()), this, SLOT(playback()));
}

void mainWindow::createMenus()
{
  fileMenu = new QMenu(this);
  fileMenu->addAction(printPrwAction);
  fileMenu->addAction(printAction);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);
  editMenu = new QMenu(this);
  editMenu->addAction(clrhistAction);
  editMenu->addAction(srchAction);
  panelMenu = new QMenu(this);
  viewMenu = new QMenu(this);
  viewMenu->addAction(trayAction);
  viewMenu->addMenu(panelMenu);
  viewMenu->addSeparator();
  viewMenu->addAction(zoomInAction);
  viewMenu->addAction(zoomOutAction);
  viewMenu->addAction(fullScreenAction);
  viewMenu->addAction(showNormalAction);
  toolsMenu = new QMenu(this);
  toolsMenu->addAction(newDbAction);
  toolsMenu->addAction(dbEditorAction);
  toolsMenu->addAction(playAction);
  settingMenu = new QMenu(this);
  settingMenu->addAction(settingsAction);
  helpMenu = new QMenu(this);
  helpMenu->addAction(helpAction);
  helpMenu->addAction(whatsThisAction);
  helpMenu->addSeparator();
  helpMenu->addAction(tipAction);
  helpMenu->addSeparator();
  helpMenu->addAction(languageAction);
  helpMenu->addSeparator();
  helpMenu->addAction(aboutAction);
  helpMenu->addSeparator();
  helpMenu->addAction(aboutQtAction);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(editMenu);
  menuBar()->addMenu(viewMenu);
  menuBar()->addMenu(toolsMenu);
  menuBar()->addMenu(settingMenu);
  menuBar()->addSeparator();
  menuBar()->addMenu(helpMenu);
}

void mainWindow::createToolbars()
{
  mainToolBar = new QToolBar(this);
  mainToolBar->addAction(settingsAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(aboutAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(printAction);
  mainToolBar->addAction(playAction);
  mainToolBar->addSeparator();
  //mainToolBar->addAction(stayontopAction);
  //mainToolBar->addSeparator();
  mainToolBar->addAction(quitAction);

  addToolBar(mainToolBar);
  viewMenu->addAction(mainToolBar->toggleViewAction());
}

void mainWindow::createPanels()
{
  // FIXME enable ability for updating new settings
  foreach (QString plugin, pluginManager::plgsbyTyple("panel")) {
    if (pluginManager::selectedPlugins().contains(plugin)) {
      basePanel *pnl = new basePanel(this);
//       connect(pnl, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(saveSettings()));
      QString fileName = pluginManager::file(plugin);
      QPluginLoader loader(fileName);
      QObject *plugin = loader.instance();
      InterfacePlugin *iInterface = qobject_cast<InterfacePlugin *>(plugin);
      if (iInterface) {
	pnl->setAllowedAreas(iInterface->widgetArea());
	pnl->setWidget(iInterface->createMainWidget(this));
	pnl->setWindowTitle(iInterface->name());
	pnl->setObjectName(iInterface->name());
	pnl->toggleViewAction()->setText(iInterface->name());
	pnl->toggleViewAction()->setIcon(QIcon(globalVar::defaultIcons("22", "") + "/" + iInterface->icon()));
	panelMenu->addAction(pnl->toggleViewAction());
	addDockWidget(iInterface->widgetArea(), pnl);
	connect(plugin, SIGNAL(wordRequeste(QString)), this, SLOT(wordRequested(QString)));
	connect(textBrowser, SIGNAL(highlighted(QString)), plugin, SLOT(urlActivated(QString)));
      }
      
      

    }
  }
//FIXME add lock & unlock panel toggled action in panels menu
//FIXME correct number of each area dock
  QList<QDockWidget*> docks = findChildren<QDockWidget*>();
  QList<QDockWidget*> bottomdocks, rightdocks;
  for(int i = 0; i < docks.size(); i++) {
     if (docks[i]->allowedAreas() == Qt::BottomDockWidgetArea)
       bottomdocks.append(docks[i]);
     if (docks[i]->allowedAreas() == Qt::RightDockWidgetArea)
       rightdocks.append(docks[i]);    
  }
  for(int j = 0; j < bottomdocks.size(); j++) {
    tabifyDockWidget(bottomdocks[0],bottomdocks[1]);
  }
  for(int k = 0; k < rightdocks.size(); k++) {
    tabifyDockWidget(rightdocks[0],rightdocks[1]);
  }

}

void mainWindow::createTrayIcon()
{
  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(showNotify);
  trayIconMenu->addAction(settingsAction);
  trayIconMenu->addAction(fullScreenAction);
  trayIconMenu->addAction(restoreAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);

  tray = new trayIcon(this);
  tray->setContextMenu(trayIconMenu);
}

void mainWindow::showTrayMessage()
{
  if (enabledNotify)
    tray->searchMessage(clipboard->text(QClipboard::Selection).trimmed().toLower());
  
}

void mainWindow::trayMessageClicked()
{
  this->setVisible(true);
  wrdEdit->setText(clipboard->text(QClipboard::Selection).trimmed().toLower());
  sendPlugin();
}

void mainWindow::closeEvent(QCloseEvent *event)
{
  if (tray->isVisible()) {
    
    const QPixmap shot = tray->takeScreenshot();
    QTemporaryFile tmp;
    QString tmpFileName;
    if ( tmp.open() ) {
      tmpFileName = tmp.fileName();
      shot.save( &tmp, "PNG" );
      tmp.close();
    }
    
    const QString imgTag = !tmpFileName.isEmpty() ? QString::fromLatin1( "<img src=\"%1\"/>" ).arg( tmpFileName ) : QString();
    //shot.save("/media/science/projects/qt4/neda/rtrt.png", "PNG");
    
    QMessageBox::information(this, tr( "Docking in System Tray" ), tr( "<qt><p>Closing the main window will keep <b>%1</b> running in the system tray. Use 'Quit' from the 'File' menu to quit the application.</p><p><center>%2</center></p></qt>").arg(globalVar::appName(), imgTag));
    
    /*FIXME add quit button*/
    hide();
    event->ignore();
  }
}

void mainWindow::setVisible(bool visible)
{
  QWidget::setVisible(visible);
}

void mainWindow::slotTogglePopupWindow()
{
  setVisible(!isVisible());
}

void mainWindow::onWhatsThis()
{
  QWhatsThis::enterWhatsThisMode();
}

void mainWindow::retranslateUi()
{
  statusbarMessage(tr("Ready..."));
  
  fileMenu->setTitle(tr("&File"));
  editMenu->setTitle(tr("&Edit"));
  panelMenu->setTitle(tr("&Panels"));
  viewMenu->setTitle(tr("&View"));
  toolsMenu->setTitle(tr("&Tools"));
  settingMenu->setTitle(tr("&Settings"));
  helpMenu->setTitle(tr("&Help"));
  
  
  printPrwAction->setText(tr("Print Preview"));
  printPrwAction->setStatusTip(tr("Show Print Preview Dialog"));
  printPrwAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-print-preview.png"));

  printAction->setText(tr("&Print..."));
  printAction->setShortcut(QKeySequence::Print);
  printAction->setStatusTip(tr("Show Print Dialog"));
  printAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-print.png"));

  quitAction->setText(tr("&Quit"));
  quitAction->setShortcut(tr("Ctrl+Q"));
  quitAction->setStatusTip(tr("Quit %1").arg(globalVar::appName()));
  quitAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/application-exit.png"));

  zoomInAction->setText(tr("&Zoom in"));
  zoomInAction->setStatusTip(tr("Magnify results font"));
  zoomInAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/zoom-in.png"));
  zoomInAction->setShortcut(QKeySequence::ZoomIn);
  zoomOutAction->setText(tr("&Zoom out"));
  zoomOutAction->setStatusTip(tr("Reduce results font"));
  zoomOutAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/zoom-out.png"));
  zoomOutAction->setShortcut(QKeySequence::ZoomOut);
  fullScreenAction->setText(tr("F&ull Screen Mode"));
  fullScreenAction->setStatusTip(tr("Switch to full screen mode"));
  fullScreenAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-fullscreen.png"));
  fullScreenAction->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_F);
  showNormalAction->setText(tr("Exit F&ull Screen Mode"));
  showNormalAction->setStatusTip(tr("Switch to normal screen mode"));
  showNormalAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-restore.png"));
//   showNormalAction->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_F);
  
  newDbAction->setText(tr("&Create New Database"));
  newDbAction->setStatusTip(tr("Show Wizard for create new Database"));
  newDbAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/database-new.png"));
  
  dbEditorAction->setText(tr("Database &Editor"));
  dbEditorAction->setStatusTip(tr("Show database editor dialog"));
  dbEditorAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/database-edit.png"));
  
  playAction->setText(tr("&Play Word Sound"));
  playAction->setStatusTip(tr("Playing Word Sound"));
  playAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/media-playback-start.png"));
  
  settingsAction->setText(tr("&Settings"));
  settingsAction->setShortcut(tr("Ctrl+S"));
  settingsAction->setStatusTip(tr("Configure %1").arg(globalVar::appName()));
  settingsAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/configure.png"));

  whatsThisAction->setText(tr("&What's This?"));
  whatsThisAction->setShortcut(QKeySequence::WhatsThis);
  whatsThisAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-contextual.png"));

  helpAction->setText(tr("Help %1").arg(globalVar::appName()));
  helpAction->setShortcut(QKeySequence::HelpContents);
  helpAction->setStatusTip(tr("Help %1").arg(globalVar::appName()));
  helpAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-contents.png"));

  tipAction->setText(tr("&Tip of the Day"));
  tipAction->setShortcut(tr("Ctrl+T"));
  tipAction->setStatusTip(tr("tip of the day"));
  tipAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/tip.png"));

  languageAction->setText(tr("Switch Application &Language..."));
  languageAction->setShortcut(tr("Ctrl+L"));
  languageAction->setStatusTip(tr("change %1 language").arg(globalVar::appName()));
  languageAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/change-language.png"));

  aboutAction->setText(tr("A&bout"));
//   aboutAction->setShortcut(tr("Ctrl+B"));
  aboutAction->setStatusTip(tr("About %1").arg(globalVar::appName()));
  aboutAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about.png"));

  aboutQtAction->setText(tr("About &Qt"));
  //aboutQtAction->setShortcut(tr("Ctrl+Q"));
  aboutQtAction->setStatusTip(tr("About Qt"));
  aboutQtAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about-qt.png"));

  trayAction->setText(tr("Show system &tray icon"));
  //trayAction->setShortcut(tr("Ctrl+T"));
  trayAction->setStatusTip(tr("Show %1 icon in system tray").arg(globalVar::appName()));

  stayontopAction->setText(tr("Stays on top"));
  stayontopAction->setStatusTip(tr("Window stays on top"));
  //stayontopAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about.png"));

  mainToolBar->toggleViewAction()->setText(tr("Main &toolbar"));
  mainToolBar->toggleViewAction()->setStatusTip(tr("Show main tool bar"));
  
  clrhistAction->setText(tr("Clear &History"));
  clrhistAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-clear-history.png"));
  clrhistAction->setStatusTip(tr("Clear History List"));
  srchAction->setText(tr("Show &search bar"));
  srchAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-find.png"));
  //srchAction->setShortcut(tr("Ctrl+F"));
  srchAction->setShortcut(QKeySequence::Find);
  srchAction->setStatusTip(tr("Find in Text..."));

  lkpButton->setText(tr("Look Up"));
  lkpButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-find.png"));
  lkpButton->setToolTip(tr("look up entered word"));
  lkpButton->setWhatsThis(tr("look for word entered in selected databases."));
  
  showNotify->setText(tr("Show &Notification message"));
  restoreAction->setText(tr("&Restore Main Window"));
  restoreAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-restore.png"));
}

void mainWindow::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  if (settings.value("generals/ShowTrayIcon").toBool()) {
    tray->show();
    trayAction->setChecked(true);
  } else {
    tray->hide();
    trayAction->setChecked(false);
  }
  
  if (settings.value("generals/Language").toBool())
    switchLanguage(settings.value("generals/Language").toString());
  
  stayontopAction->setChecked(settings.value("generals/StayOnTop").toBool());
  findBar->setVisible(settings.value("generals/ShowFindBar").toBool());
  useStylePalette = settings.value("generals/UseStyleStandardPalette").toBool();
  enabledNotify = settings.value("generals/EnableNotification").toBool();
  srchAction->setChecked(settings.value("generals/ShowFindBar").toBool());
  showNotify->setChecked(settings.value("generals/EnableNotification").toBool());
  
  if (settings.value("generals/CurrentStyle").toBool())
    changeStyle(settings.value("generals/CurrentStyle").toString());
  
  if (settings.value("generals/AutoCompletion").toBool())
    changeCompletionModel();
  
  if (settings.value("generals/RunTipOnStart").toBool())
    showTipDialog();
  
  restoreGeometry(settings.value("generals/geometry").toByteArray());
  restoreState(settings.value("generals/windowState").toByteArray());
  
  textBrowser->loadSettings();
}

void mainWindow::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("generals/ShowTrayIcon", trayAction->isChecked());
  settings.setValue("generals/ShowFindBar", findBar->isVisible());
  settings.setValue("generals/StayOnTop", stayontopAction->isChecked());
  
  settings.setValue("generals/geometry", saveGeometry());
  settings.setValue("generals/windowState", saveState());
}

void mainWindow::showLanguageDialog()
{
  sld = new switchLanguageDialog(this);
  connect(sld, SIGNAL(langChangHappened(const QString &)), this, SLOT(switchLanguage(const QString &)));
  sld->show();
}

void mainWindow::switchLanguage(QString locale)
{
  langManager::changeLang(locale);
  retranslateUi();
  findBar->retranslateUi();
}

void mainWindow::showSettingsDialog()
{
  std = new settingsDialog(this);
  connect(std, SIGNAL(settingModified()), this, SLOT(loadSettings()));
  std->show();
}

void mainWindow::showTipDialog()
{
  tip = new tipDialog(this);
  tip->show();
}

void mainWindow::showAboutDialog()
{
  abt = new aboutDialog(this);
  abt->show();
}

void mainWindow::showHelpDialog()
{
  // FIXME automatically load index file
  hlp = new helpDialog(this, "index.html");
  hlp->show();
}

void mainWindow::showPrintDialog()
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

void mainWindow::showPrintPreview()
{
#ifndef QT_NO_PRINTER
  QPrinter printer(QPrinter::HighResolution);
  QPrintPreviewDialog preview(&printer, this);
  connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
  preview.exec();
#endif
}

void mainWindow::showNewDbWizard()
{
  newdbWzrd = new dbcreateWizard(this);
  newdbWzrd->show();
}

void mainWindow::showDbEditor()
{
  dbEdit = new dbEditor(this);
  dbEdit->show();
}

void mainWindow::printPreview(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
  textBrowser->print(printer);
#else
  Q_UNUSED(printer);
#endif
}

QAbstractItemModel *mainWindow::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    QStandardItemModel *m = new QStandardItemModel(words.count(), 2, completer);

    for (int i = 0; i < words.count(); ++i) {
        QModelIndex countryIdx = m->index(i, 0);
        QModelIndex symbolIdx = m->index(i, 1);
        QString country = words[i].mid(0, words[i].length() - 2).trimmed();
        QString symbol = words[i].right(2);
        m->setData(countryIdx, country);
        m->setData(symbolIdx, symbol);
    }

    return m;
}

void mainWindow::changeCompletionModel()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);

  completer = new QCompleter(this);
  QString wr = settings.value("generals/CompletionWord").toString();
  
  if (!QFile::exists(wr)) {
    if (QFile::exists(globalVar::words())) {
      wr = globalVar::words();
    } else {
      qWarning("mainWindow::can't find completion words file %s", qPrintable(wr));
    }
  }
    
  completer->setModel(modelFromFile(wr));
  completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

  QCompleter::CompletionMode mode;

  int index = settings.value("generals/CompletionMode").toInt();
  if (index == 0)
    mode = QCompleter::InlineCompletion;
  else if (index == 1)
    mode = QCompleter::PopupCompletion;
  else
    mode = QCompleter::UnfilteredPopupCompletion;

  int cs = settings.value("generals/CompletionCase").toInt();
  completer->setCaseSensitivity(cs ? Qt::CaseSensitive : Qt::CaseInsensitive);
  completer->setCompletionMode(mode);

  wrdEdit->setCompleter(completer);
}

void mainWindow::changePalette()
{
  if (useStylePalette)
    QApplication::setPalette(QApplication::style()->standardPalette());
  else
    QApplication::setPalette(originalPalette);
}

void mainWindow::changeStyle(const QString &styleName)
{
  QApplication::setStyle(QStyleFactory::create(styleName));
  changePalette();
}

void mainWindow::filterChanged(const QString &filter)
{
  /*if( word == "the" ) {
  } else if( word == "at" ) {
  }*/
  switch (filters.indexOf(filter)) {
    case 0:
      qDebug() << filters.indexOf(filter) << "::::" << filter;
    break;
    case 1:
      qDebug() << filters.indexOf(filter) << "::::" << filter;
    break;
    case 2:
      qDebug() << filters.indexOf(filter) << "::::" << filter;
     }
}
 
void mainWindow::sendPlugin()
{
  textBrowser->clear();
  textBrowser->setText(searchManager::findwrd(wrdEdit->text().trimmed().toLower()));
  // FIXME add to history if the word founded
  history->insert(wrdEdit->text().trimmed().toLower());
}

// FIXME move this fure to lineEdit class
void mainWindow::checkState(const QString &t)
{
  QPalette *palette = new QPalette();
  
  QRegExp doiRegExp("^10\\.[\\d\\.]+/\\S+$", Qt::CaseInsensitive);
  QRegExp isbnRegExp("(\\d-?){9,11}-[\\dX]", Qt::CaseInsensitive);
  QValidator *validator = new QRegExpValidator(doiRegExp, this);
  wrdEdit->setValidator(validator);
  QString text = wrdEdit->text().trimmed().toLower();
  int pos;
//    State state = QRegExpValidator::validate(, 0)[0];
//    bool isValid = wrdEdit->validator()->validate(text, pos) == QValidator::Acceptable;
   qDebug() << wrdEdit->palette();
 /* if ( state == Acceptable ) {
    
  */
 switch (wrdEdit->validator()->validate(text, pos)) {
    case 0:
      palette->setColor(QPalette::Base,Qt::red);
      wrdEdit->setPalette(*palette);
    break;
    case 1:
      palette->setColor(QPalette::Base,Qt::yellow);
      wrdEdit->setPalette(*palette);
    break;
    case 2:
      palette->setColor(QPalette::Base,Qt::green);
      wrdEdit->setPalette(*palette);      
    default:
      palette->setColor(QPalette::Base,Qt::white);
      wrdEdit->setPalette(*palette);
    break;
     }
 
 /*if ( validator->validate( wrdEdit->text().trimmed().toLower(), 0 ) == Acceptable ) {
   palette->setColor(QPalette::Base,Qt::green);
      wrdEdit->setPalette(*palette);
      statusbarMessage(tr("Acceptable..."));
 }*/
}

void mainWindow::clearHistory()
{
  history->clear();
}

void mainWindow::wordRequested(const QString &message)
{
  if (!message.isEmpty()) {
    wrdEdit->setText(message);
    sendPlugin();
  }
}

void mainWindow::stayontop(bool state)
{
  Qt::WindowFlags flags = this->windowFlags();
  if (state) {
    this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    this->show();
  } else {
    this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
    this->show();
  }
}

void mainWindow::showNotification(bool state)
{
  enabledNotify = state;
}

// FIXME add as plugin for multi-direction support
void mainWindow::playback()
{
  QString wrd = wrdEdit->text().trimmed().toLower();

  QString file = "/usr/local/share/dicdb/file/WyabdcRealPeopleTTS/" + wrd[0] + "/" + wrd + ".wav";
  //QString file = "/usr/local/share/dicdb/file/WyabdcRealPeopleTTS/" + wrd[0] + "/" + wrd + ".wav";
  mediaObject->setCurrentSource(Phonon::MediaSource(file));
  mediaObject->play();
}
