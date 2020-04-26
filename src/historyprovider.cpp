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

#include <QTextStream>
#include <QDebug>
#include <QStringList>

#include "historyprovider.h"
#include "globalvar.h"

historyProvider::historyProvider()
{
  histFile = new QFile(globalVar::history());
  loadHist();
  //if(!histFile->open(QIODevice::Text | QIODevice::ReadWrite))
}

historyProvider::~historyProvider()
{
}

void historyProvider::loadHist()
{
  if( !histFile->open( QIODevice::ReadOnly ) )
    qWarning("loadHist::Failed to open history file.");
  
  while (!histFile->atEnd()) {
    QString line = histFile->readLine();
    QStringList word = line.split("\n");
    histList.append(word[0]);
  }
histFile->close();
}

void historyProvider::insert( const QString& item )
{
  //QFile his(globalVar::history());
  if (!histList.contains(item)) {
    if( !histFile->open( QIODevice::WriteOnly | QIODevice::Append ) )
      qWarning("Failed to open history file.");
  
  //QTextStream ts( &histFile );
    QTextStream ts( histFile );
  // FIXME push instead append, insert each word one time
    if (!item.isEmpty()) {
      ts << item << endl;
      //histList.prepend(item);
      histList.append(item);
    }
    histFile->close();
  }
}

void historyProvider::remove( const QString& item )
{
}

void historyProvider::clear()
{
  histFile->open(QFile::WriteOnly|QFile::Truncate);
}
