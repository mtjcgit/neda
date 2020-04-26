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

#ifndef BASEPANEL_H
#define BASEPANEL_H

#include <QtGui/QDockWidget>

/*!
 \class basePanel
 \brief This class provides Base dock for all panels that can be docked on the window borders.
*/

class basePanel : public QDockWidget
{
Q_OBJECT

public:
  //! Constructor of base panel.
  basePanel(QWidget *parent = 0);
  //! Destructor of base panel.
  virtual ~basePanel();
  /*
protected slots:
  void saveSettings();
*/
/*signals:
  void dockLocationChanged(Qt::DockWidgetArea area);*/
};

#endif
