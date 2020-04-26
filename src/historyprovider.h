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

#ifndef HISTORYPROVIDER_H
#define HISTORYPROVIDER_H

#include <QString>
#include <QFile>
#include <QList>
/*!
 \class historyProvider
 \brief This class provides history management.
*/

class historyProvider
{
public:
  //! Constructor of history manager.
  historyProvider();
  //! Destructor of main window.
  ~historyProvider();
  
public:
  //! function for load the history to a list.
  void loadHist();
  //! function for insert @p item into the history.
  void insert( const QString& item );
  //! function for remove @p item from the history.
  void remove( const QString& item );
  //! function for clear the history.
  void clear();
  
private:
  QFile *histFile;
  QList<QString> histList;
};

#endif
