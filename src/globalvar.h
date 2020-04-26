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

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <QString>

/*!
 \class globalVar
 \brief This class provides global Variations
*/

class globalVar
{
public:
  //! Return the name of app.
  static QString appName();
  //! Return the version of app.
  static QString appVersion();
  //! Return the description of app.
  static QString shortDescription();
  //! Return the copyright statement of app.
  static QString copyrightStatement();
  //! Return the author(s) name(s).
  static QString author();
  //! Return the thanks.
  static QString thanks();
  //! Return the home page of app.
  static QString homepage();
  //! Return the license of app.
  static QString licenseFile();
  //! Set the GUI startup condition.
  static void setGuiEnabled(bool g);
  //! Set the app path.
  static void setAppPath(QString path);
  //! Parse arguments.
  static void parseArgs(int argc, char *argv[]);
  //! Return the GUI startup condition.
  static bool isGuiEnabled();
  //! Return the application path.
  static QString appPath();
  //! Return the library path.
  static QString libPath();
  //! Return the data path.
  static QString dataPath();
  
  //! Return the user's home.
  static QString appHomePath();
  
  //! Return the requested word.
  static QString reqWord();
  
  //! Return the default language.
  static QString defaultLanguage();
  //! Return the default theme.
  static QString defaultThemeName();
  //! Return the default icon size.
  static QString defaultIconSize();
  //! Return the default icons.
  static QString defaultIcons(QString size, QString cat);
  //! Return the tips of the day.
  static QString tips();
  //! Return the helps.
  static QString helps();
  //! Return the configuration file.
  static QString config();
  //! Return the words list for completion future.
  static QString words();
  //! Return the translations.
  static QString translations();
  //! Return the history.
  static QString history();
  //! Return the plugins.
  static QStringList plugins();
  
private:
  static bool gui_bool;
  static QString app_path;
  static QString ini_path;
  static QString req_word;
};

#endif
