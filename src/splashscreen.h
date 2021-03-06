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

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

class QPixmap;

/*!
 \class splashScreen
 \brief This class provides a splash screen that can be shown during application startup.
*/

class splashScreen : public QSplashScreen
{
Q_OBJECT

public:
  //! Constructor of splash screen.
  splashScreen(const QPixmap& pixmap, Qt::WindowFlags f = 0);
  //! Destructor.
  virtual ~splashScreen();

public slots:
  //! show message text onto the splash screen with color color and aligns the text according to the flags in alignment.
  void message( const QString &str, int flags = Qt::AlignRight, const QColor &color = Qt::white );
};

#endif
