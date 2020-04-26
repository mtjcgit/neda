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

#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>

/*!
 \class singleApplication
 \brief This class provides support for applications that can be started only once per user.
*/

class singleApplication : public QApplication
{
Q_OBJECT

public:
  //! Constructor that sets new local server.
  singleApplication( int &argc, char **argv, bool GUIenabled = true);
  //! Destructor
  ~singleApplication();
  
public:
  //! Return the state of run.
  bool isRunning();
  
public slots:
  //! Return the state of send message.
  bool sendMessage(const QString &message);
  
protected slots:
  //! receive message.
  void receiveMessage();
  
signals:
  void messageAvailable(const QString &message);

protected:
  QString socketName;
  
private:
  bool _isRunning;
  QSharedMemory sharedMemory;
  QLocalServer *localServer;
  static const int timeout = 1000;
};

#endif
