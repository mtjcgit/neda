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

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QImage>
#include <QPixmap>

/*!
 \class trayIcon
 \brief This class provides tray icon for main window
*/

class trayIcon : public QSystemTrayIcon
{
  Q_OBJECT
  
public:
  //! Constructor of tray icon.
  trayIcon(QWidget *parent = 0);
  //! Destructor of tray icon.
  ~trayIcon();
  
public:
  //! save settings function.
  void saveSettings();
  //! show a message an suggest for search a word.
  void searchMessage(QString msg);
  //! show a plain message.
  void simpleMessage(QString msg);
  //! show a information message.
  void informationMessage(QString msg);
  //! show a warning message.
  void warningMessage(QString msg);
  //! show a critical message.
  void criticalMessage(QString msg);
  
private:
  //! translations of user interface of tray icon.
  void retranslateUi();
  //! setting tool tip of tray icon.
  void setupToolTip();
  
signals:
  void trayClicked();
  
private slots:
  void trayActivated(QSystemTrayIcon::ActivationReason reason);
  
protected:
  void loadSettings();
  
public:
  QPixmap takeScreenshot() const;
};

#endif
