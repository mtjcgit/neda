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

#include <QtGui>
#include <QDebug>

#include "pnl-periodictable.h"

QString pnlPeriodicTable::name() const
{ return QLatin1String("periodic table"); }

QString pnlPeriodicTable::group() const
{ return QLatin1String("interface"); }

QString pnlPeriodicTable::toolTip() const
{ return QLatin1String("periodic table plug in."); }

QString pnlPeriodicTable::whatsThis() const
{ return QLatin1String("periodic table plug in."); }

QString pnlPeriodicTable::type() const
{ return QLatin1String("panel"); }

QString pnlPeriodicTable::icon() const
{ return QLatin1String("objects/periodic-table.png"); }

QString pnlPeriodicTable::version() const
{ return QLatin1String("1.0.0"); }

QString pnlPeriodicTable::description() const
{ return QLatin1String("Periodic table of the elements"); }

Qt::DockWidgetArea pnlPeriodicTable::widgetArea() const
{
  return Qt::BottomDockWidgetArea;
}

bool pnlPeriodicTable::hasConfig() const
{
  return true;
}

QWidget *pnlPeriodicTable::createMainWidget(QWidget* parent)
{
  table = new QWidget(parent);
  
  mainGrid = new QGridLayout(table);
  //mainGrid->setContentsMargins(0, 0, 0, 0);
  mainGrid->setHorizontalSpacing(0);
  mainGrid->setVerticalSpacing(0);
  mainGrid->setMargin(6);
  
  btnH = new QToolButton(table);
  btnH->setAccessibleName("hydrogen");
  btnHe = new QToolButton(table);
  btnHe->setAccessibleName("helium");
  btnLi = new QToolButton(table);
  btnLi->setAccessibleName("lithium");
  btnBe = new QToolButton(table);
  btnBe->setAccessibleName("beryllium");
  btnB = new QToolButton(table);
  btnB->setAccessibleName("boron");
  btnC = new QToolButton(table);
  btnC->setAccessibleName("carbon");
  btnN = new QToolButton(table);
  btnN->setAccessibleName("nitrogen");
  btnO = new QToolButton(table);
  btnO->setAccessibleName("oxygen");
  btnF = new QToolButton(table);
  btnF->setAccessibleName("fluorine");
  btnNe = new QToolButton(table);
  btnNe->setAccessibleName("neon");
  btnNa = new QToolButton(table);
  btnNa->setAccessibleName("sodium");
  btnMg = new QToolButton(table);
  btnMg->setAccessibleName("magnesium");
  btnAl = new QToolButton(table);
  btnAl->setAccessibleName("aluminum");
  btnSi = new QToolButton(table);
  btnSi->setAccessibleName("silicon");
  btnP = new QToolButton(table);
  btnP->setAccessibleName("phosphorus");
  btnS = new QToolButton(table);
  btnS->setAccessibleName("sulphur");
  btnCl = new QToolButton(table);
  btnCl->setAccessibleName("chlorine");
  btnAr = new QToolButton(table);
  btnAr->setAccessibleName("argon");
  btnK = new QToolButton(table);
  btnK->setAccessibleName("potassium");
  btnCa = new QToolButton(table);
  btnCa->setAccessibleName("calcium");
  btnSc = new QToolButton(table);
  btnSc->setAccessibleName("scandium");
  btnTi = new QToolButton(table);
  btnTi->setAccessibleName("titanium");
  btnV = new QToolButton(table);
  btnV->setAccessibleName("vanadium");
  btnCr = new QToolButton(table);
  btnCr->setAccessibleName("chromium");
  btnMn = new QToolButton(table);
  btnMn->setAccessibleName("manganese");
  btnFe = new QToolButton(table);
  btnFe->setAccessibleName("iron");
  btnCo = new QToolButton(table);
  btnCo->setAccessibleName("cobalt");
  btnNi = new QToolButton(table);
  btnNi->setAccessibleName("nickel");
  btnCu = new QToolButton(table);
  btnCu->setAccessibleName("copper");
  btnZn = new QToolButton(table);
  btnZn->setAccessibleName("zinc");
  btnGa = new QToolButton(table);
  btnGa->setAccessibleName("gallium");
  btnGe = new QToolButton(table);
  btnGe->setAccessibleName("germanium");
  btnAs = new QToolButton(table);
  btnAs->setAccessibleName("arsenic");
  btnSe = new QToolButton(table);
  btnSe->setAccessibleName("selenium");
  btnBr = new QToolButton(table);
  btnBr->setAccessibleName("bromine");
  btnKr = new QToolButton(table);
  btnKr->setAccessibleName("krypton");
  btnRb = new QToolButton(table);
  btnRb->setAccessibleName("rubidium");
  btnSr = new QToolButton(table);
  btnSr->setAccessibleName("strontium");
  btnY = new QToolButton(table);
  btnY->setAccessibleName("yttrium");
  btnZr = new QToolButton(table);
  btnZr->setAccessibleName("zirconium");
  btnNb = new QToolButton(table);
  btnNb->setAccessibleName("niobium");
  btnMo = new QToolButton(table);
  btnMo->setAccessibleName("molybdenum");
  btnTc = new QToolButton(table);
  btnTc->setAccessibleName("technetium");
  btnRu = new QToolButton(table);
  btnRu->setAccessibleName("ruthenium");
  btnRh = new QToolButton(table);
  btnRh->setAccessibleName("rhodium");
  btnPd = new QToolButton(table);
  btnPd->setAccessibleName("palladium");
  btnAg = new QToolButton(table);
  btnAg->setAccessibleName("silver");
  btnCd = new QToolButton(table);
  btnCd->setAccessibleName("cadmium");
  btnIn = new QToolButton(table);
  btnIn->setAccessibleName("indium");
  btnSn = new QToolButton(table);
  btnSn->setAccessibleName("tin");
  btnSb = new QToolButton(table);
  btnSb->setAccessibleName("antimony");
  btnTe = new QToolButton(table);
  btnTe->setAccessibleName("tellurium");
  btnI = new QToolButton(table);
  btnI->setAccessibleName("iodine");
  btnXe = new QToolButton(table);
  btnXe->setAccessibleName("xenon");
  btnCs = new QToolButton(table);
  btnCs->setAccessibleName("caesium");
  btnBa = new QToolButton(table);
  btnBa->setAccessibleName("barium");
  btnLa = new QToolButton(table);
  btnLa->setAccessibleName("lanthanum");
  btnCe = new QToolButton(table);
  btnCe->setAccessibleName("cerium");
  btnPr = new QToolButton(table);
  btnPr->setAccessibleName("praseodymium");
  btnNd = new QToolButton(table);
  btnNd->setAccessibleName("neodymium");
  btnPm = new QToolButton(table);
  btnPm->setAccessibleName("promethium");
  btnSm = new QToolButton(table);
  btnSm->setAccessibleName("samarium");
  btnEu = new QToolButton(table);
  btnEu->setAccessibleName("europium");
  btnGd = new QToolButton(table);
  btnGd->setAccessibleName("gadolinium");
  btnTb = new QToolButton(table);
  btnTb->setAccessibleName("terbium");
  btnDy = new QToolButton(table);
  btnDy->setAccessibleName("dysprosium");
  btnHo = new QToolButton(table);
  btnHo->setAccessibleName("holmium");
  btnEr = new QToolButton(table);
  btnEr->setAccessibleName("erbium");
  btnTm = new QToolButton(table);
  btnTm->setAccessibleName("thulium");
  btnYb = new QToolButton(table);
  btnYb->setAccessibleName("ytterbium");
  btnLu = new QToolButton(table);
  btnLu->setAccessibleName("lutetium");
  btnHf = new QToolButton(table);
  btnHf->setAccessibleName("hafnium");
  btnTa = new QToolButton(table);
  btnTa->setAccessibleName("tantalum");
  btnW = new QToolButton(table);
  btnW->setAccessibleName("tungsten");
  btnRe = new QToolButton(table);
  btnRe->setAccessibleName("rhenium");
  btnOs = new QToolButton(table);
  btnOs->setAccessibleName("osmium");
  btnIr = new QToolButton(table);
  btnIr->setAccessibleName("iridium");
  btnPt = new QToolButton(table);
  btnPt->setAccessibleName("platinum");
  btnAu = new QToolButton(table);
  btnAu->setAccessibleName("gold");
  btnHg = new QToolButton(table);
  btnHg->setAccessibleName("mercury");
  btnTl = new QToolButton(table);
  btnTl->setAccessibleName("thallium");
  btnPb = new QToolButton(table);
  btnPb->setAccessibleName("lead");
  btnBi = new QToolButton(table);
  btnBi->setAccessibleName("bismuth");
  btnPo = new QToolButton(table);
  btnPo->setAccessibleName("polonium");
  btnAt = new QToolButton(table);
  btnAt->setAccessibleName("astatine");
  btnRn = new QToolButton(table);
  btnRn->setAccessibleName("radon");
  btnFr = new QToolButton(table);
  btnFr->setAccessibleName("francium");
  btnRa = new QToolButton(table);
  btnRa->setAccessibleName("radium");
  btnAc = new QToolButton(table);
  btnAc->setAccessibleName("actinium");
  btnTh = new QToolButton(table);
  btnTh->setAccessibleName("thorium");
  btnPa = new QToolButton(table);
  btnPa->setAccessibleName("protactinium");
  btnU = new QToolButton(table);
  btnU->setAccessibleName("uranium");
  btnNp = new QToolButton(table);
  btnNp->setAccessibleName("neptunium");
  btnPu = new QToolButton(table);
  btnPu->setAccessibleName("plutonium");
  btnAm = new QToolButton(table);
  btnAm->setAccessibleName("americium");
  btnCm = new QToolButton(table);
  btnCm->setAccessibleName("curium");
  btnBk = new QToolButton(table);
  btnBk->setAccessibleName("berkelium");
  btnCf = new QToolButton(table);
  btnCf->setAccessibleName("californium");
  btnEs = new QToolButton(table);
  btnEs->setAccessibleName("einsteinium");
  btnFm = new QToolButton(table);
  btnFm->setAccessibleName("fermium");
  btnMd = new QToolButton(table);
  btnMd->setAccessibleName("mendelevium");
  btnNo = new QToolButton(table);
  btnNo->setAccessibleName("nobelium");
  btnLr = new QToolButton(table);
  btnLr->setAccessibleName("lawrencium");
  btnRf = new QToolButton(table);
  btnRf->setAccessibleName("rutherfordium");
  btnDb = new QToolButton(table);
  btnDb->setAccessibleName("dubnium");
  btnSg = new QToolButton(table);
  btnSg->setAccessibleName("seaborgium");
  btnBh = new QToolButton(table);
  btnBh->setAccessibleName("bohrium");
  btnHs = new QToolButton(table);
  btnHs->setAccessibleName("hassium");
  btnMt = new QToolButton(table);
  btnMt->setAccessibleName("meitnerium");
  btnDs = new QToolButton(table);
  btnDs->setAccessibleName("darmstadtium");
  btnRg = new QToolButton(table);
  btnRg->setAccessibleName("roentgenium");
  btnCn = new QToolButton(table);
  btnCn->setAccessibleName("copernicium");
  btnUut = new QToolButton(table);
  btnUut->setAccessibleName("ununtrium");
  btnUuq = new QToolButton(table);
  btnUuq->setAccessibleName("ununquadium");
  btnUup = new QToolButton(table);
  btnUup->setAccessibleName("ununpentium");
  btnUuh = new QToolButton(table);
  btnUuh->setAccessibleName("ununhexium");
  btnUus = new QToolButton(table);
  btnUus->setAccessibleName("ununseptium");
  btnUuo = new QToolButton(table);
  btnUuo->setAccessibleName("ununoctium");
  
  //QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //mainGrid->addItem(verticalSpacer, 7, 0, 1, 1);
  
  mainGrid->addWidget(btnH, 0, 0, 1, 1);
  mainGrid->addWidget(btnHe, 0, 17, 1, 1);
  mainGrid->addWidget(btnLi, 1, 0, 1, 1);
  mainGrid->addWidget(btnBe, 1, 1, 1, 1);
  mainGrid->addWidget(btnB, 1, 12, 1, 1);
  mainGrid->addWidget(btnC, 1, 13, 1, 1);
  mainGrid->addWidget(btnN, 1, 14, 1, 1);
  mainGrid->addWidget(btnO, 1, 15, 1, 1);
  mainGrid->addWidget(btnF, 1, 16, 1, 1);
  mainGrid->addWidget(btnNe, 1, 17, 1, 1);
  mainGrid->addWidget(btnNa, 2, 0, 1, 1);
  mainGrid->addWidget(btnMg, 2, 1, 1, 1);
  mainGrid->addWidget(btnAl, 2, 12, 1, 1);
  mainGrid->addWidget(btnSi, 2, 13, 1, 1);
  mainGrid->addWidget(btnP, 2, 14, 1, 1);
  mainGrid->addWidget(btnS, 2, 15, 1, 1);
  mainGrid->addWidget(btnCl, 2, 16, 1, 1);
  mainGrid->addWidget(btnAr, 2, 17, 1, 1);
  mainGrid->addWidget(btnK, 3, 0, 1, 1);
  mainGrid->addWidget(btnCa, 3, 1, 1, 1);
  mainGrid->addWidget(btnSc, 3, 2, 1, 1);
  mainGrid->addWidget(btnTi, 3, 3, 1, 1);
  mainGrid->addWidget(btnV, 3, 4, 1, 1);
  mainGrid->addWidget(btnCr, 3, 5, 1, 1);
  mainGrid->addWidget(btnMn, 3, 6, 1, 1);
  mainGrid->addWidget(btnFe, 3, 7, 1, 1);
  mainGrid->addWidget(btnCo, 3, 8, 1, 1);
  mainGrid->addWidget(btnNi, 3, 9, 1, 1);
  mainGrid->addWidget(btnCu, 3, 10, 1, 1);
  mainGrid->addWidget(btnZn, 3, 11, 1, 1);
  mainGrid->addWidget(btnGa, 3, 12, 1, 1);
  mainGrid->addWidget(btnGe, 3, 13, 1, 1);
  mainGrid->addWidget(btnAs, 3, 14, 1, 1);
  mainGrid->addWidget(btnSe, 3, 15, 1, 1);
  mainGrid->addWidget(btnBr, 3, 16, 1, 1);
  mainGrid->addWidget(btnKr, 3, 17, 1, 1);
  mainGrid->addWidget(btnRb, 4, 0, 1, 1);
  mainGrid->addWidget(btnSr, 4, 1, 1, 1);
  mainGrid->addWidget(btnY, 4, 2, 1, 1);
  mainGrid->addWidget(btnZr, 4, 3, 1, 1);
  mainGrid->addWidget(btnNb, 4, 4, 1, 1);
  mainGrid->addWidget(btnMo, 4, 5, 1, 1);
  mainGrid->addWidget(btnTc, 4, 6, 1, 1);
  mainGrid->addWidget(btnRu, 4, 7, 1, 1);
  mainGrid->addWidget(btnRh, 4, 8, 1, 1);
  mainGrid->addWidget(btnPd, 4, 9, 1, 1);
  mainGrid->addWidget(btnAg, 4, 10, 1, 1);
  mainGrid->addWidget(btnCd, 4, 11, 1, 1);
  mainGrid->addWidget(btnIn, 4, 12, 1, 1);
  mainGrid->addWidget(btnSn, 4, 13, 1, 1);
  mainGrid->addWidget(btnSb, 4, 14, 1, 1);
  mainGrid->addWidget(btnTe, 4, 15, 1, 1);
  mainGrid->addWidget(btnI, 4, 16, 1, 1);
  mainGrid->addWidget(btnXe, 4, 17, 1, 1);
  mainGrid->addWidget(btnCs, 5, 0, 1, 1);
  mainGrid->addWidget(btnBa, 5, 1, 1, 1);
  mainGrid->addWidget(btnLa, 5, 2, 1, 1);
  mainGrid->addWidget(btnCe, 8, 3, 1, 1);
  mainGrid->addWidget(btnPr, 8, 4, 1, 1);
  mainGrid->addWidget(btnNd, 8, 5, 1, 1);
  mainGrid->addWidget(btnPm, 8, 6, 1, 1);
  mainGrid->addWidget(btnSm, 8, 7, 1, 1);
  mainGrid->addWidget(btnEu, 8, 8, 1, 1);
  mainGrid->addWidget(btnGd, 8, 9, 1, 1);
  mainGrid->addWidget(btnTb, 8, 10, 1, 1);
  mainGrid->addWidget(btnDy, 8, 11, 1, 1);
  mainGrid->addWidget(btnHo, 8, 12, 1, 1);
  mainGrid->addWidget(btnEr, 8, 13, 1, 1);
  mainGrid->addWidget(btnTm, 8, 14, 1, 1);
  mainGrid->addWidget(btnYb, 8, 15, 1, 1);
  mainGrid->addWidget(btnLu, 8, 16, 1, 1);
  mainGrid->addWidget(btnHf, 5, 3, 1, 1);
  mainGrid->addWidget(btnTa, 5, 4, 1, 1);
  mainGrid->addWidget(btnW, 5, 5, 1, 1);
  mainGrid->addWidget(btnRe, 5, 6, 1, 1);
  mainGrid->addWidget(btnOs, 5, 7, 1, 1);
  mainGrid->addWidget(btnIr, 5, 8, 1, 1);
  mainGrid->addWidget(btnPt, 5, 9, 1, 1);
  mainGrid->addWidget(btnAu, 5, 10, 1, 1);
  mainGrid->addWidget(btnHg, 5, 11, 1, 1);
  mainGrid->addWidget(btnTl, 5, 12, 1, 1);
  mainGrid->addWidget(btnPb, 5, 13, 1, 1);
  mainGrid->addWidget(btnBi, 5, 14, 1, 1);
  mainGrid->addWidget(btnPo, 5, 15, 1, 1);
  mainGrid->addWidget(btnAt, 5, 16, 1, 1);
  mainGrid->addWidget(btnRn, 5, 17, 1, 1);
  mainGrid->addWidget(btnFr, 6, 0, 1, 1);
  mainGrid->addWidget(btnRa, 6, 1, 1, 1);
  mainGrid->addWidget(btnAc, 6, 2, 1, 1);
  mainGrid->addWidget(btnTh, 9, 3, 1, 1);
  mainGrid->addWidget(btnPa, 9, 4, 1, 1);
  mainGrid->addWidget(btnU, 9, 5, 1, 1);
  mainGrid->addWidget(btnNp, 9, 6, 1, 1);
  mainGrid->addWidget(btnPu, 9, 7, 1, 1);
  mainGrid->addWidget(btnAm, 9, 8, 1, 1);
  mainGrid->addWidget(btnCm, 9, 9, 1, 1);
  mainGrid->addWidget(btnBk, 9, 10, 1, 1);
  mainGrid->addWidget(btnCf, 9, 11, 1, 1);
  mainGrid->addWidget(btnEs, 9, 12, 1, 1);
  mainGrid->addWidget(btnFm, 9, 13, 1, 1);
  mainGrid->addWidget(btnMd, 9, 14, 1, 1);
  mainGrid->addWidget(btnNo, 9, 15, 1, 1);
  mainGrid->addWidget(btnLr, 9, 16, 1, 1);
  mainGrid->addWidget(btnRf, 6, 3, 1, 1);
  mainGrid->addWidget(btnDb, 6, 4, 1, 1);
  mainGrid->addWidget(btnSg, 6, 5, 1, 1);
  mainGrid->addWidget(btnBh, 6, 6, 1, 1);
  mainGrid->addWidget(btnHs, 6, 7, 1, 1);
  mainGrid->addWidget(btnMt, 6, 8, 1, 1);
  mainGrid->addWidget(btnDs, 6, 9, 1, 1);
  mainGrid->addWidget(btnRg, 6, 10, 1, 1);
  mainGrid->addWidget(btnCn, 6, 11, 1, 1);
  mainGrid->addWidget(btnUut, 6, 12, 1, 1);
  mainGrid->addWidget(btnUuq, 6, 13, 1, 1);
  mainGrid->addWidget(btnUup, 6, 14, 1, 1);
  mainGrid->addWidget(btnUuh, 6, 15, 1, 1);
  mainGrid->addWidget(btnUus, 6, 16, 1, 1);
  mainGrid->addWidget(btnUuo, 6, 17, 1, 1);
  table->setLayout(mainGrid);
  
  retranslateUi();
  
  signalMapper = new QSignalMapper(this);
  allButtons = table->findChildren<QToolButton *>();
  for (int i=0;i<allButtons.count();i++) {
    connect(allButtons.at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(allButtons.at(i), i);
    //allButtons.at(i)->setText(allButtons.at(i)->objectName());
    allButtons.at(i)->setObjectName(allButtons.at(i)->text());
    allButtons.at(i)->setToolTip(allButtons.at(i)->accessibleName());
    allButtons.at(i)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  }
  connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onBtnClicked(int)));
  
#ifdef PLUGINDIR
  /*FIXME go to configure dialog*/
  QString path = QString(PLUGINDIR) + "/qss/default.qss";
#endif
  QFile styleSheet(path);
  if (styleSheet.open(QFile::ReadOnly)) {
    QString styleSheetContents = QLatin1String(styleSheet.readAll());
    table->setStyleSheet(styleSheetContents);
  }
  return table;
}

QWidget *pnlPeriodicTable::createConfWidget(QWidget* parent)
{
  cnfWidget = new QWidget(parent);
  return cnfWidget;
}

void pnlPeriodicTable::retranslateUi()
{
  btnH->setText(tr("H"));
  btnHe->setText(tr("He"));
  btnLi->setText(tr("Li"));
  btnBe->setText(tr("Be"));
  btnB->setText(tr("B"));
  btnC->setText(tr("C"));
  btnN->setText(tr("N"));
  btnO->setText(tr("O"));
  btnF->setText(tr("F"));
  btnNe->setText(tr("Ne"));
  btnNa->setText(tr("Na"));
  btnMg->setText(tr("Mg"));
  btnAl->setText(tr("Al"));
  btnSi->setText(tr("Si"));
  btnP->setText(tr("P"));
  btnS->setText(tr("S"));
  btnCl->setText(tr("Cl"));
  btnAr->setText(tr("Ar"));
  btnK->setText(tr("K"));
  btnCa->setText(tr("Ca"));
  btnSc->setText(tr("Sc"));
  btnTi->setText(tr("Ti"));
  btnV->setText(tr("V"));
  btnCr->setText(tr("Cr"));
  btnMn->setText(tr("Mn"));
  btnFe->setText(tr("Fe"));
  btnCo->setText(tr("Co"));
  btnNi->setText(tr("Ni"));
  btnCu->setText(tr("Cu"));
  btnZn->setText(tr("Zn"));
  btnGa->setText(tr("Ga"));
  btnGe->setText(tr("Ge"));
  btnAs->setText(tr("As"));
  btnSe->setText(tr("Se"));
  btnBr->setText(tr("Br"));
  btnKr->setText(tr("Kr"));
  btnRb->setText(tr("Rb"));
  btnSr->setText(tr("Sr"));
  btnY->setText(tr("Y"));
  btnZr->setText(tr("Zr"));
  btnNb->setText(tr("Nb"));
  btnMo->setText(tr("Mo"));
  btnTc->setText(tr("Tc"));
  btnRu->setText(tr("Ru"));
  btnRh->setText(tr("Rh"));
  btnPd->setText(tr("Pd"));
  btnAg->setText(tr("Ag"));
  btnCd->setText(tr("Cd"));
  btnIn->setText(tr("In"));
  btnSn->setText(tr("Sn"));
  btnSb->setText(tr("Sb"));
  btnTe->setText(tr("Te"));
  btnI->setText(tr("I"));
  btnXe->setText(tr("Xe"));
  btnCs->setText(tr("Cs"));
  btnBa->setText(tr("Ba"));
  btnLa->setText(tr("La"));
  btnCe->setText(tr("Ce"));
  btnPr->setText(tr("Pr"));
  btnNd->setText(tr("Nd"));
  btnPm->setText(tr("Pm"));
  btnSm->setText(tr("Sm"));
  btnEu->setText(tr("Eu"));
  btnGd->setText(tr("Gd"));
  btnTb->setText(tr("Tb"));
  btnDy->setText(tr("Dy"));
  btnHo->setText(tr("Ho"));
  btnEr->setText(tr("Er"));
  btnTm->setText(tr("Tm"));
  btnYb->setText(tr("Yb"));
  btnLu->setText(tr("Lu"));
  btnHf->setText(tr("Hf"));
  btnTa->setText(tr("Ta"));
  btnW->setText(tr("W"));
  btnRe->setText(tr("Re"));
  btnOs->setText(tr("Os"));
  btnIr->setText(tr("Ir"));
  btnPt->setText(tr("Pt"));
  btnAu->setText(tr("Au"));
  btnHg->setText(tr("Hg"));
  btnTl->setText(tr("Tl"));
  btnPb->setText(tr("Pb"));
  btnBi->setText(tr("Bi"));
  btnPo->setText(tr("Po"));
  btnAt->setText(tr("At"));
  btnRn->setText(tr("Rn"));
  btnFr->setText(tr("Fr"));
  btnRa->setText(tr("Ra"));
  btnAc->setText(tr("Ac"));
  btnTh->setText(tr("Th"));
  btnPa->setText(tr("Pa"));
  btnU->setText(tr("U"));
  btnNp->setText(tr("Np"));
  btnPu->setText(tr("Pu"));
  btnAm->setText(tr("Am"));
  btnCm->setText(tr("Cm"));
  btnBk->setText(tr("Bk"));
  btnCf->setText(tr("Cf"));
  btnEs->setText(tr("Es"));
  btnFm->setText(tr("Fm"));
  btnMd->setText(tr("Md"));
  btnNo->setText(tr("No"));
  btnLr->setText(tr("Lr"));
  btnRf->setText(tr("Rf"));
  btnDb->setText(tr("Db"));
  btnSg->setText(tr("Sg"));
  btnBh->setText(tr("Bh"));
  btnHs->setText(tr("Hs"));
  btnMt->setText(tr("Mt"));
  btnDs->setText(tr("Ds"));
  btnRg->setText(tr("Rg"));
  btnCn->setText(tr("Cn"));
  btnUut->setText(tr("Uut"));
  btnUuq->setText(tr("Uuq"));
  btnUup->setText(tr("Uup"));
  btnUuh->setText(tr("Uuh"));
  btnUus->setText(tr("Uus"));
  btnUuo->setText(tr("Uuo"));
}

void pnlPeriodicTable::loadSettings()
{
}

void pnlPeriodicTable::onBtnClicked(int btn)
{
  /*QString strKeyId;
  strKeyId = allButtons.at(btn)->accessibleName().trimmed();
  Qt::KeyboardModifiers Modifier = Qt::NoModifier;
  int keyId = strKeyId.toInt();
  QString ch = allButtons.at(btn)->text().trimmed();
  int involvedKeys = 1;
  //QString ch = allButtons.at(btn)->text().trimmed();
  QKeyEvent keyEvent(QEvent::KeyPress, keyId, Modifier, strKeyId, false, involvedKeys);
  QApplication::sendEvent(QApplication::focusWidget(), &keyEvent);*/

  //qDebug() << keyId << btn << strKeyId;
  //emit wordRequeste(allButtons.at(btn)->text().trimmed());
  emit wordRequeste(allButtons.at(btn)->accessibleName().trimmed());
}

void pnlPeriodicTable::urlActivated(const QString &url)
{
  /*else
    phononWdgt->hide();*/
    qDebug() << "i'm pnlPeriodicTable panel:" << url;
}

void pnlPeriodicTable::saveSettings(void)
{
}
 
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(pnlperiodictable, pnlPeriodicTable);
QT_END_NAMESPACE
