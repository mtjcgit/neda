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

#include <QLocalSocket>
#include <QDebug>
#include "singleapplication.h"
#include "globalvar.h"

singleApplication::singleApplication(int &argc, char **argv, bool GUIenabled) : QApplication(argc, argv, GUIenabled)
{
  socketName = globalVar::appName();
  
  sharedMemory.setKey(socketName);
  
  if (sharedMemory.attach())
    _isRunning = true;
  else {
    _isRunning = false;
    if (!sharedMemory.create(1)) {
      qWarning("Unable to create single instance.");
      return;
    }
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(receiveMessage()));
    localServer->listen(socketName);
  }
}

singleApplication::~singleApplication()
{}

void singleApplication::receiveMessage()
{
  QLocalSocket *localSocket = localServer->nextPendingConnection();
  if (!localSocket->waitForReadyRead(timeout)) {
    qDebug() << localSocket->errorString().toLatin1();
    return;
  }
  QByteArray byteArray = localSocket->readAll();
  QString message = QString::fromUtf8(byteArray.constData());
  emit messageAvailable(message);
  localSocket->disconnectFromServer();
}

bool singleApplication::isRunning()
{
  return _isRunning;
}

bool singleApplication::sendMessage(const QString &message)
{
  if (!_isRunning)
    return false;
  QLocalSocket localSocket(this);
  localSocket.connectToServer(socketName, QIODevice::WriteOnly);
  if (!localSocket.waitForConnected(timeout)) {
    qDebug() << localSocket.errorString().toLatin1();
    return false;
  }
  localSocket.write(message.toUtf8());
  if (!localSocket.waitForBytesWritten(timeout)) {
    qDebug() << localSocket.errorString().toLatin1();
    return false;
  }
  localSocket.disconnectFromServer();
  return true;
}


