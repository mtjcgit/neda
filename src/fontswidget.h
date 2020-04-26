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

#ifndef FONTSWIDGET_H
#define FONTSWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;
class QTextEdit;
/*!
 \class fontsWidget
 \brief This class provides fonts page for settings dialog.
*/

class fontsWidget : public QWidget
{
Q_OBJECT

public:
  //! Constructor of fonts page.
  fontsWidget(QWidget *parent = 0);
  //! Destructor of fonts page.
  ~fontsWidget();

public:
  //! Return name of fonts page.
  virtual QString pageName();
  //! Return icon of fonts page.
  virtual QString pageIcon();

public:
  //! function for save settings of fonts page.
  void saveSettings();

protected:
  //! translations of user interface for fonts page.
  void retranslateUi();
  //! function for load settings of fonts page.
  void loadSettings();
  
private slots:
  void hdtxtFont();
  void rstxtFont();
  
private:
  QLabel *hdtxtLabel;
  QLabel *rstxtLabel;
  QTextEdit *sampleText;
  QPushButton *hdtxtBtn;
  QPushButton *rstxtBtn;
  QFont hdFont;
  QFont rsFont;
};

#endif
