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
#include <QFileSystemWatcher>
#include <QFile>
#include <QDebug>
#include <QDir>

#include "pnl-history.h"

QString pnlHistory::name() const
{ return QLatin1String("history"); }

QString pnlHistory::group() const
{ return QLatin1String("interface"); }

QString pnlHistory::toolTip() const
{ return QLatin1String("history plug in."); }

QString pnlHistory::whatsThis() const
{ return QLatin1String("history plug in."); }

QString pnlHistory::type() const
{ return QLatin1String("panel"); }

QString pnlHistory::icon() const
{ return QLatin1String("actions/view-history.png"); }

QString pnlHistory::version() const
{ return QLatin1String("1.0.0"); }

QString pnlHistory::description() const
{ return QLatin1String("history..."); }

/*QStringList pnlHistory::dependencies() const
{
  QStringList mydpnds;
  mydpnds << "a" << "bb" << "ccc" << "dddd";
  return mydpnds;
}*/

Qt::DockWidgetArea pnlHistory::widgetArea() const
{
  return Qt::RightDockWidgetArea;
}

bool pnlHistory::hasConfig() const
{
  return true;
}

QWidget *pnlHistory::createMainWidget(QWidget* parent)
{
  hidtWdgt = new QWidget(parent);
  
  //createActions();
  //createToolbars();
  //mainToolBar = new QToolBar(hidtWdgt);
  
  /*QLabel *titleLabel = new QLabel(hidtWdgt);
  titleLabel->setText(tr("&Look for:"));*/
  
  /*searchLineEdit= new QLineEdit(hidtWdgt);
  titleLabel->setBuddy(searchLineEdit);*/
  
  listWidget = new QListWidget(hidtWdgt);
  listWidget->setMaximumWidth(128);
  //listWidget->addItem("hello");
  //listWidget->addItem("see");
  connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemAction(QListWidgetItem *)));
  
  QVBoxLayout *mainLayout = new QVBoxLayout();
  //mainLayout->addWidget(mainToolBar);
  //mainLayout->addWidget(titleLabel);
  //mainLayout->addWidget(searchLineEdit);
  mainLayout->addWidget(listWidget);
  hidtWdgt->setLayout(mainLayout);

  histFile = new QFile(pluginHomepath() + "/history");
  QFileInfo fi(pluginHomepath() + "/history");
  fileWatcher = new QFileSystemWatcher(this);
  if (fi.exists())
  	fileWatcher->addPath(pluginHomepath() + "/history");
  connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(loadHistory()));

  loadSettings();
  loadHistory();
  return hidtWdgt;
}

void pnlHistory::loadHistory()
{
  if (!histFile->open(QIODevice::ReadOnly | QIODevice::Text))
    qWarning("Failed to open history file.");
  listWidget->clear();
  while (!histFile->atEnd()) {
    QString line = histFile->readLine();
    QStringList word = line.split("\n");
    listWidget->addItem(word[0]);
    //listWidget->addItem(line.trimmed());
  }
  histFile->close();
}

QWidget *pnlHistory::createConfWidget(QWidget* parent)
{
  confWdgt = new QWidget(parent);
  
  QLabel *titleLabel = new QLabel( confWdgt );
  titleLabel->setText( tr( "Number of words to show:" ) );
  titleLabel->setWhatsThis(tr("This is the number of words that will be added to history."));
  
  histNumber = new QSpinBox(confWdgt);
  histNumber->setMinimum(0);

  QSettings settings(config(), QSettings::IniFormat);
  histNumber->setValue(settings.value("History/historyNumber").toInt());
	
  QVBoxLayout *mainLayout = new QVBoxLayout(confWdgt);
  mainLayout->addWidget(titleLabel);
  mainLayout->addWidget(histNumber);
  mainLayout->addStretch(0);
  confWdgt->setLayout(mainLayout);
  return confWdgt;
}

void pnlHistory::retranslateUi()
{
}

void pnlHistory::loadSettings()
{
  //QSettings settings(config(), QSettings::IniFormat);
  //settings.setValue("History/historyNumber", histNumber->value());
}

void pnlHistory::urlActivated(const QString &url)
{
  /*if (!url.isEmpty()) {
   
  }*/
  /*else
    phononWdgt->hide();*/
    //qDebug() << "i'm information panel:" << url;
}

/*void pnlHistory::createActions()
{
  //sortAction = new QAction(hidtWdgt);
  clearAction = new QAction(hidtWdgt);
}
void pnlHistory::createToolbars()
{
  //mainToolBar->addAction(sortAction);
  mainToolBar->addAction(clearAction);
}
void pnlHistory::retranslateUi()
{
#ifdef PLUGINDIR
  clearAction->setIcon(QIcon(QString(PLUGINDIR) + "/actions/edit-clear-history.png"));
#endif
  clearAction->setToolTip(tr("Clean History"));
  clearAction->setWhatsThis(tr("clean history."));
}*/

void pnlHistory::itemAction(QListWidgetItem *item)
{
  emit wordRequeste(item->text());
}

QString pnlHistory::pluginHomepath()
{
  QString hpath;
#ifndef Q_OS_WIN
  hpath = QDir::homePath() + "/.config/neda";
#else
  hpath = QDir::homePath() + "/.neda";
#endif
  return hpath;
}

QString pnlHistory::config()
{
  QString confile;
  
  if (QFile::exists(pluginHomepath() + "/plugins/" + name() + ".ini"))
    confile = pluginHomepath() + "/plugins/" + name() + ".ini";
#ifdef PLUGINDIR
  else if (QFile::exists(QString(PLUGINDIR) + "/"  + name() + "rc"))
    QFile::copy ( QString(PLUGINDIR) + "/" + name() + "rc", pluginHomepath() + "/plugins/" + name() + ".ini" );
    //confile = QString(PLUGINDIR);
#endif
    
  return confile;
}

void pnlHistory::saveSettings(void)
{
  QString confile = pluginHomepath() + "/plugins/" + name() + ".ini";
  QSettings settings(confile, QSettings::IniFormat);
  settings.setValue("History/historyNumber", histNumber->value());
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(pnlhistory, pnlHistory);
QT_END_NAMESPACE
