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

#ifndef PNL_PERIODICTABLE_H
#define PNL_PERIODICTABLE_H

#include <QObject>

#include "plugins.h"

class QGridLayout;
class QToolButton;
class QSignalMapper;

class pnlPeriodicTable : public QObject, public InterfacePlugin
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
  
public slots:
  void urlActivated(const QString &url);
  
signals:
  void wordRequeste(const QString &word);
  
  
private slots:
  void onBtnClicked(int btn);
  void saveSettings(void);

private:
  QWidget *table;
  QWidget *cnfWidget;
  QGridLayout *mainGrid;
  QToolButton *btnH;
  QToolButton *btnHe;
  QToolButton *btnLi;
  QToolButton *btnBe;
  QToolButton *btnB;
  QToolButton *btnC;
  QToolButton *btnN;
  QToolButton *btnO;
  QToolButton *btnF;
  QToolButton *btnNe;
  QToolButton *btnNa;
  QToolButton *btnMg;
  QToolButton *btnAl;
  QToolButton *btnSi;
  QToolButton *btnP;
  QToolButton *btnS;
  QToolButton *btnCl;
  QToolButton *btnAr;
  QToolButton *btnK;
  QToolButton *btnCa;
  QToolButton *btnSc;
  QToolButton *btnTi;
  QToolButton *btnV;
  QToolButton *btnCr;
  QToolButton *btnMn;
  QToolButton *btnFe;
  QToolButton *btnCo;
  QToolButton *btnNi;
  QToolButton *btnCu;
  QToolButton *btnZn;
  QToolButton *btnGa;
  QToolButton *btnGe;
  QToolButton *btnAs;
  QToolButton *btnSe;
  QToolButton *btnBr;
  QToolButton *btnKr;
  QToolButton *btnRb;
  QToolButton *btnSr;
  QToolButton *btnY;
  QToolButton *btnZr;
  QToolButton *btnNb;
  QToolButton *btnMo;
  QToolButton *btnTc;
  QToolButton *btnRu;
  QToolButton *btnRh;
  QToolButton *btnPd;
  QToolButton *btnAg;
  QToolButton *btnCd;
  QToolButton *btnIn;
  QToolButton *btnSn;
  QToolButton *btnSb;
  QToolButton *btnTe;
  QToolButton *btnI;
  QToolButton *btnXe;
  QToolButton *btnCs;
  QToolButton *btnBa;
  QToolButton *btnLa;
  QToolButton *btnCe;
  QToolButton *btnPr;
  QToolButton *btnNd;
  QToolButton *btnPm;
  QToolButton *btnSm;
  QToolButton *btnEu;
  QToolButton *btnGd;
  QToolButton *btnTb;
  QToolButton *btnDy;
  QToolButton *btnHo;
  QToolButton *btnEr;
  QToolButton *btnTm;
  QToolButton *btnYb;
  QToolButton *btnLu;
  QToolButton *btnHf;
  QToolButton *btnTa;
  QToolButton *btnW;
  QToolButton *btnRe;
  QToolButton *btnOs;
  QToolButton *btnIr;
  QToolButton *btnPt;
  QToolButton *btnAu;
  QToolButton *btnHg;
  QToolButton *btnTl;
  QToolButton *btnPb;
  QToolButton *btnBi;
  QToolButton *btnPo;
  QToolButton *btnAt;
  QToolButton *btnRn;
  QToolButton *btnFr;
  QToolButton *btnRa;
  QToolButton *btnAc;
  QToolButton *btnTh;
  QToolButton *btnPa;
  QToolButton *btnU;
  QToolButton *btnNp;
  QToolButton *btnPu;
  QToolButton *btnAm;
  QToolButton *btnCm;
  QToolButton *btnBk;
  QToolButton *btnCf;
  QToolButton *btnEs;
  QToolButton *btnFm;
  QToolButton *btnMd;
  QToolButton *btnNo;
  QToolButton *btnLr;
  QToolButton *btnRf;
  QToolButton *btnDb;
  QToolButton *btnSg;
  QToolButton *btnBh;
  QToolButton *btnHs;
  QToolButton *btnMt;
  QToolButton *btnDs;
  QToolButton *btnRg;
  QToolButton *btnCn;
  QToolButton *btnUut;
  QToolButton *btnUuq;
  QToolButton *btnUup;
  QToolButton *btnUuh;
  QToolButton *btnUus;
  QToolButton *btnUuo;
  QSignalMapper *signalMapper;
  QList<QToolButton *> allButtons;
};

#endif
