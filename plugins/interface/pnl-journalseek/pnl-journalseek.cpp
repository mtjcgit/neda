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
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QSettings>
#include <QDesktopServices>

#include "pnl-journalseek.h"
#include "doimanager.h"

QString pnlJournalSeek::name() const
{ return QLatin1String("journal seek"); }

QString pnlJournalSeek::group() const
{ return QLatin1String("interface"); }

QString pnlJournalSeek::toolTip() const
{ return QLatin1String("journal seek plug in."); }

QString pnlJournalSeek::whatsThis() const
{ return QLatin1String("journal seek plug in."); }

QString pnlJournalSeek::type() const
{ return QLatin1String("panel"); }

QString pnlJournalSeek::icon() const
{ return QLatin1String("objects/journalseek.png"); }

QString pnlJournalSeek::version() const
{ return QLatin1String("1.0.0"); }

QString pnlJournalSeek::description() const
{ return QLatin1String("Find information about journal article "); }

Qt::DockWidgetArea pnlJournalSeek::widgetArea() const
{
  return Qt::BottomDockWidgetArea;
}

bool pnlJournalSeek::hasConfig() const
{
  return true;
}

QWidget *pnlJournalSeek::createMainWidget(QWidget* parent)
{
  srcpnl = new QWidget(parent);
  
  oneGrid = new QGridLayout(srcpnl);
  //oneGrid->setContentsMargins(0, 0, 0, 0);
  oneGrid->setHorizontalSpacing(0);
  oneGrid->setVerticalSpacing(0);
  oneGrid->setMargin(6);
  
//   jrnllbl = new QLabel(srcpnl);
//   jrnlcb = new QComboBox(srcpnl);
//   doilbl = new QLabel(srcpnl);
  doile = new QLineEdit(srcpnl);
//   yerlbl = new QLabel(srcpnl);
//   vollbl = new QLabel(srcpnl);
//   isslbl = new QLabel(srcpnl);
//   paglbl = new QLabel(srcpnl);
//   yerle = new QSpinBox(srcpnl);
//   volle = new QSpinBox(srcpnl);
//   issle = new QSpinBox(srcpnl);
//   pagle = new QSpinBox(srcpnl);
  textEdit = new QTextEdit(srcpnl);
  srcbtn = new QPushButton(srcpnl);
  clrbtn = new QPushButton(srcpnl);
  svsbtn = new QPushButton(srcpnl);
  scibtn = new QPushButton(srcpnl);
  //QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //oneGrid->addItem(verticalSpacer, 7, 0, 1, 1);
  

//   oneGrid->addWidget(jrnllbl, 0, 0, 1, 1);
//   oneGrid->addWidget(jrnlcb, 0, 1, 1, 1);
//   oneGrid->addWidget(doilbl, 0, 0, 1, 1);
  oneGrid->addWidget(doile, 0, 0, 1, 4);
  oneGrid->addWidget(textEdit, 1, 0, 1, 4);
//   oneGrid->addWidget(yerlbl, 2, 0, 1, 1);
//   oneGrid->addWidget(vollbl, 3, 0, 1, 1);
//   oneGrid->addWidget(isslbl, 4, 0, 1, 1);
//   oneGrid->addWidget(paglbl, 5, 0, 1, 1);
  
//   oneGrid->addWidget(yerle, 2, 1, 1, 1);
//   oneGrid->addWidget(volle, 3, 1, 1, 1);
//   oneGrid->addWidget(issle, 4, 1, 1, 1);
//   oneGrid->addWidget(pagle, 5, 1, 1, 1);
  oneGrid->addWidget(clrbtn, 2, 0, 1, 1);
  oneGrid->addWidget(srcbtn, 2, 1, 1, 1);
  oneGrid->addWidget(svsbtn, 2, 2, 1, 1);
  oneGrid->addWidget(scibtn, 2, 3, 1, 1);

  connect(doile, SIGNAL(returnPressed()), this, SLOT(getInfo()));
  connect(srcbtn, SIGNAL(clicked()), this, SLOT(getInfo()));
  connect(clrbtn, SIGNAL(clicked()), textEdit, SLOT(clear()));
  connect(svsbtn, SIGNAL(clicked()), this, SLOT(saveAs()));
  connect(scibtn, SIGNAL(clicked()), this, SLOT(download()));
  
 
  retranslateUi();

#ifdef PLUGINDIR
  /*FIXME go to configure dialog*/
  QString path = QString(PLUGINDIR) + "/plugins";
#endif

  return srcpnl;
}

QWidget *pnlJournalSeek::createConfWidget(QWidget* parent)
{
  cnfWidget = new QWidget(parent);
  return cnfWidget;
}

void pnlJournalSeek::retranslateUi()
{
//   jrnllbl->setText(tr("Journal"));
//   doilbl->setText(tr("DOI"));
//   yerlbl->setText(tr("Year"));
//   vollbl->setText(tr("Volume"));
//   isslbl->setText(tr("Issue"));
//   paglbl->setText(tr("Page"));
  srcbtn->setText(tr("Search..."));
  clrbtn->setText(tr("Clear"));
  svsbtn->setText(tr("Save As"));
  scibtn->setText(tr("Download"));
}

void pnlJournalSeek::loadSettings()
{
}

void pnlJournalSeek::onBtnClicked(int btn)
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
  //emit wordRequeste(allButtons.at(btn)->accessibleName().trimmed());
}

void pnlJournalSeek::getInfo()
{
   diomng = new doiManager(this);
   diomng->fetch(doile->text().trimmed());
  
   connect(diomng, SIGNAL(textChanged(const QString&)), textEdit, SLOT(append(const QString&)));
}

void pnlJournalSeek::save()
{
    if ( filename.isEmpty() ) {
        saveAs();
        return;
    }

    QString text = textEdit->toPlainText();
    QFile data( filename );
    if (!data.open(QIODevice::WriteOnly)) {
       qDebug() << "Could not write";
        return;
    }

//     QTextStream t( &f );
    QTextStream out(&data);
    out << text;
    data.close();
    
//     textEdit->setModified( FALSE );
}

void pnlJournalSeek::saveAs()
{
//     QString fn = QFileDialog::getSaveFileName( QString::null, QString::null,this );
    QString fn = QFileDialog::getSaveFileName(0, tr("Save Bibliography File"), "", tr("Bibtex files (*.bib)"));
    if ( !fn.isEmpty() ) {
        filename = fn;
        save();
    } else {
      qDebug() << "Saving aborted";
    }
}

void pnlJournalSeek::download()
{
    QDesktopServices::openUrl(QUrl("http://sci-hub.se/"+doile->text().trimmed()));
}

void pnlJournalSeek::urlActivated(const QString &url)
{
  /*else
    phononWdgt->hide();*/
    qDebug() << "i'm pnlJournalSeek panel:" << url;
}

void pnlJournalSeek::saveSettings(void)
{
}

void pnlJournalSeek::loadAll()
{
 /* QStringList nameFilters;
  nameFilters.append(QLatin1String("*.info"));
  QDir infDir(subdir1);
      QFileInfoList infos = subDir.entryInfoList(nameFilters);
      QListIterator<QFileInfo> it(infos);
      while (it.hasNext()) {
	const QFileInfo fi = it.next();
	//QString filename = fi.absoluteFilePath();
	loadDB(fi.absoluteFilePath());
      }
      */
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(pnljournalseek, pnlJournalSeek);
QT_END_NAMESPACE
