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

#ifndef PNL_JOURNALSEEK_H
#define PNL_JOURNALSEEK_H

#include <QObject>
 #include <QTextStream>

#include "plugins.h"

class QGridLayout;
class QToolButton;
class QLabel;
// class QComboBox;
class QLineEdit;
class QPushButton;
// class QSpinBox;
class QTextEdit;
class doiManager;

class pnlJournalSeek : public QObject, public InterfacePlugin
{
Q_OBJECT
Q_INTERFACES(InterfacePlugin)

public:
  QString name() const;
  QString group() const;
  QString toolTip() const;
  QString whatsThis() const;
  QString type() const;
  QString icon() const;
  QString version() const;
  QString description() const;
  Qt::DockWidgetArea widgetArea() const;
  bool hasConfig() const;
  QWidget *createConfWidget(QWidget* parent);
  QWidget *createMainWidget(QWidget* parent);
  
protected:
  void retranslateUi();
  void loadSettings();
  
private:
  //! load all databases.
  static void loadAll();
  
public slots:
  void urlActivated(const QString &url);
  void saveSettings(void);
  
signals:
  void wordRequeste(const QString &word);
  
  
private slots:
  void onBtnClicked(int btn);
  void getInfo();
  void save();
  void saveAs();
  void download();

private:
  QWidget *srcpnl;
  QWidget *cnfWidget;
  QGridLayout *oneGrid;
//   QLabel *jrnllbl;
//   QLabel *doilbl;
//   QLabel *yerlbl;
//   QLabel *vollbl;
//   QLabel *isslbl;
//   QLabel *paglbl;
//   QComboBox *jrnlcb;
  QLineEdit *doile;
  //QLineEdit *yerle;
  //QLineEdit *volle;
  //QLineEdit *issle;
  //QLineEdit *pagle;
  QPushButton *srcbtn;
  QPushButton *clrbtn;
  QPushButton *svsbtn;
  QPushButton *scibtn;
  QString path ,filename;
//   QSpinBox *yerle;
//   QSpinBox *volle;
//   QSpinBox *issle;
//   QSpinBox *pagle;
  QTextEdit *textEdit;
  doiManager *diomng;
};

#endif
