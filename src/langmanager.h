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

#ifndef LANGMANAGER_H
#define LANGMANAGER_H

#include <QMultiMap>

/*!
 \class langManager
 \brief This class provides management for languages support
*/

class langManager
{

public:
  //! load all translation files.
  static void loadAll();
  //! load specified translation file.
  static void loadLang(const QString &fileName );
  //! change language.
  static void changeLang(QString &locale);
  
public:
  //! Return the list of all available languages.
  static QStringList foundLangs();
  //! Return the file of specified languages.
  static QString file(const QString &trnsName);
  //! Return the languages letters of specified languages.
  static QString lang(const QString &trnsName);
  //! Return the country of specified languages.
  static QString coun(const QString &trnsName);
  //! Return the author of specified languages.
  static QString auth(const QString &trnsName);
  //! Return the contact address of specified languages.
  static QString cont(const QString &trnsName);
  //! Return the index number of specified languages.
  static int index(const QString &trnsName);
  //! Return the current selected languages.
  static QString current();
  
private:
  static QStringList localsList;
  static QMultiMap<QString, QString> fileMap, langMap, counMap, authMap, contMap;
  
protected:
  static QTranslator appTranslator;
  static QTranslator qtTranslator;
};

#endif
