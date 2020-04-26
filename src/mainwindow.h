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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <Phonon/Path>
#include <Phonon/AbstractMediaStream>

class QPushButton;
class QComboBox;
class QClipboard;
class QAction;
class QMenu;
class QToolBar;
class QAbstractItemModel;
class QCompleter;
class resultBrowser;
class trayIcon;
class lineEdit;
class searchBar;
class switchLanguageDialog;
class tipDialog;
class aboutDialog;
class helpDialog;
class settingsDialog;
class dbcreateWizard;
class dbEditor;
class historyProvider;

namespace Phonon
{
  class MediaObject;
  class AudioOutput;
  class Path;
}

/*!
 \class mainWindow
 \brief This class provides main window.
*/

class mainWindow : public QMainWindow
{
Q_OBJECT

public:
  //! Constructor of main window.
  mainWindow(QWidget *parent = 0);
  //! Destructor of main window.
  ~mainWindow();
 
private:
  //! show messages on status bar.
  void statusbarMessage(QString message);
  //! set state of visibility.
  void setVisible(bool visible);
  //! create all actions for main window.
  void createActions();
  //! create menus for main window.
  void createMenus();
  //! create tool bars for main window.
  void createToolbars();
  //! create panels for main window.
  void createPanels();
  //! create tray icon for main window.
  void createTrayIcon();
  //! translations of user interface
  void retranslateUi();
  //! state of using style palette
  bool useStylePalette;
  //! state of notification.
  bool enabledNotify;
  
protected:
  void closeEvent(QCloseEvent *event);
  //! save settings function
//   void saveSettings();
  
public slots:
  //! try to find word requested
  void wordRequested(const QString &message);
  
private slots:
  void onWhatsThis();
  void slotTogglePopupWindow();
  void showTrayMessage();
  void trayMessageClicked();
  void showLanguageDialog();
  void showSettingsDialog();
  void showTipDialog();
  void showAboutDialog();
  void showHelpDialog();
  void showPrintDialog();
  void showPrintPreview();
  void showNewDbWizard();
  void showDbEditor();
  void printPreview(QPrinter *printer);
  void changeCompletionModel();
  void changeStyle(const QString &styleName);
  void changePalette();
  void sendPlugin();
  void checkState(const QString &t);
  void stayontop(bool state);
  void clearHistory();
  void showNotification(bool state);
  void playback();
  void filterChanged(const QString &filter);
  
protected slots:
  void saveSettings();
  void loadSettings();
  void switchLanguage(QString locale);
  
private:
  static QStringList filters;
  
private:
  QWidget *centralWidget;
  QPushButton *lkpButton;
  QComboBox *fltrCombo;
  QClipboard *clipboard;
  QAction *printAction;
  QAction *printPrwAction;
  QAction *quitAction;
  QAction *newDbAction;
  QAction *dbEditorAction;
  QAction *settingsAction;
  QAction *whatsThisAction;
  QAction *helpAction;
  QAction *tipAction;
  QAction *languageAction;
  QAction *aboutAction;
  QAction *aboutQtAction;
  QAction *trayAction;
  QAction *stayontopAction;
  QAction *clrhistAction;
  QAction *srchAction;
  QAction *showNotify;
  QAction *restoreAction;
  QAction *playAction;
  QAction *zoomInAction;
  QAction *zoomOutAction;
  QAction *fullScreenAction;
  QAction *showNormalAction;
  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *panelMenu;
  QMenu *viewMenu;
  QMenu *settingMenu;
  QMenu *toolsMenu;
  QMenu *helpMenu;
  QMenu *trayIconMenu;
  QToolBar *mainToolBar;
  QAbstractItemModel *modelFromFile(const QString& fileName);
  QCompleter *completer;
  QPalette originalPalette;
  resultBrowser *textBrowser;
  trayIcon *tray;
  lineEdit *wrdEdit;
  switchLanguageDialog *sld;
  searchBar *findBar;
  tipDialog *tip;
  aboutDialog *abt;
  helpDialog *hlp;
  settingsDialog *std;
  dbcreateWizard *newdbWzrd;
  dbEditor *dbEdit;
  historyProvider *history;
  Phonon::MediaObject *mediaObject;
  Phonon::AudioOutput *audioOutput;
  //Phonon::Path phononPath;
};

#endif
