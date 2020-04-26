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

#include "trayicon.h"
#include "globalvar.h"
#include "searchmanager.h"

trayIcon::trayIcon(QWidget *parent) : QSystemTrayIcon(parent)
{
  connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
  
  retranslateUi();
  loadSettings();
}

trayIcon::~trayIcon()
{}

void trayIcon::setupToolTip()
{
  QString tooltip;
  
  //tooltip = "<center>";
  tooltip += globalVar::appName();
  tooltip +=  " - dictionary";
  //tooltip += "</center>";
  
  //tooltip += searchManager::searchedWord();
  
  setToolTip(tooltip);
}

void trayIcon::retranslateUi()
{
  setupToolTip();
  setIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/" + globalVar::appName() + ".png"));
}

QPixmap trayIcon::takeScreenshot() const
{
  const QRect rect = geometry();
  const QPoint g = rect.topLeft();
  int desktopWidth  = qApp->desktop()->width();
  int desktopHeight = qApp->desktop()->height();
  int tw = rect.width();
  int th = rect.height();
  int w = desktopWidth / 4;
  int h = desktopHeight / 9;
  int x = g.x() + tw/2 - w/2; // Center the rectange in the systray icon
  int y = g.y() + th/2 - h/2;
  if (x < 0)
    x = 0; // Move the rectangle to stay in the desktop limits
  if (y < 0)
    y = 0;
  if (x + w > desktopWidth)
    x = desktopWidth - w;
  if (y + h > desktopHeight)
    y = desktopHeight - h;
  
  // Grab the desktop and draw a circle around the icon:
  QPixmap shot = QPixmap::grabWindow(QApplication::desktop()->winId(), x, y, w, h);
  QPainter painter(&shot);
  painter.setRenderHint( QPainter::Antialiasing );
  const int MARGINS = 6;
  const int WIDTH   = 3;
  int ax = g.x() - x - MARGINS -1;
  int ay = g.y() - y - MARGINS -1;
  painter.setPen( QPen(Qt::red, WIDTH) );
  painter.drawArc(ax, ay, tw + 2*MARGINS, th + 2*MARGINS, 0, 16*360);
  painter.end();
  // Paint the border
  const int BORDER = 1;
  QPixmap finalShot(w + 2*BORDER, h + 2*BORDER);
  finalShot.fill( QApplication::palette().color( QPalette::Foreground ));
  painter.begin(&finalShot);
  painter.drawPixmap(BORDER, BORDER, shot);
  painter.end();
  return shot; // not finalShot?? -fo
}

void trayIcon::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason) {
    case QSystemTrayIcon::Unknown:
    break;
    case QSystemTrayIcon::Context:
    break;
    case QSystemTrayIcon::DoubleClick:
    break;
    case QSystemTrayIcon::Trigger:
      //this->setVisible(!this->isVisible());
      emit trayClicked();
    break;
    case QSystemTrayIcon::MiddleClick:
    break;
    default:
      ;
  }
}

void trayIcon::loadSettings()
{
  /*QSettings settings(globalVar::config(), QSettings::IniFormat);
  enabledNotify = settings.value("generals/EnableNotification").toBool();*/
  //QSettings settings(globalVar::config(), QSettings::IniFormat);
  //notifyCheckBox->setChecked( settings.value("generals/EnableNotification").toBool() );
}

void trayIcon::saveSettings()
{
  //QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  //settings.setValue("generals/EnableNotification", notifyCheckBox->isChecked());
}

void trayIcon::searchMessage(QString msg)
{
  if (QSystemTrayIcon::supportsMessages())
    showMessage("Search for: ", msg, QSystemTrayIcon::MessageIcon(1), 5000);
}

void trayIcon::simpleMessage(QString msg)
{
  showMessage("", msg, QSystemTrayIcon::MessageIcon(0), 3000);
}

void trayIcon::informationMessage(QString msg)
{
  showMessage("Note: ", msg, QSystemTrayIcon::MessageIcon(1), 3000);
}

void trayIcon::warningMessage(QString msg)
{
  showMessage("Warning: ", msg, QSystemTrayIcon::MessageIcon(2), 3000);
}

void trayIcon::criticalMessage(QString msg)
{
  showMessage("Critical: ", msg, QSystemTrayIcon::MessageIcon(3), 3000);
}
