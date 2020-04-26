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

#include "pnl-bookmarks.h"
#include "xbelreader.h"

QString pnlBookmarks::name() const
{ return QLatin1String("bookmarks"); }

QString pnlBookmarks::group() const
{ return QLatin1String("interface"); }

QString pnlBookmarks::toolTip() const
{ return QLatin1String("bookmarks plug in."); }

QString pnlBookmarks::whatsThis() const
{ return QLatin1String("bookmarks plug in."); }

QString pnlBookmarks::type() const
{ return QLatin1String("panel"); }

QString pnlBookmarks::icon() const
{ return QLatin1String("actions/bookmarks.png"); }

QString pnlBookmarks::version() const
{ return QLatin1String("1.0.0"); }

QString pnlBookmarks::description() const
{ return QLatin1String("bookmarks..."); }

/*QStringList pnlBookmarks::dependencies() const
{
  QStringList mydpnds;
  mydpnds << "a" << "bb" << "ccc" << "dddd";
  return mydpnds;
}*/

Qt::DockWidgetArea pnlBookmarks::widgetArea() const
{
  return Qt::RightDockWidgetArea;
}

bool pnlBookmarks::hasConfig() const
{
  return true;
}

QWidget *pnlBookmarks::createMainWidget(QWidget* parent)
{
  hidtWdgt = new QWidget(parent);
  
  //createActions();
  //createToolbars();
  //mainToolBar = new QToolBar(hidtWdgt);
  
  /*QLabel *titleLabel = new QLabel(hidtWdgt);
  titleLabel->setText(tr("&Look for:"));*/
  
  /*searchLineEdit= new QLineEdit(hidtWdgt);
  titleLabel->setBuddy(searchLineEdit);*/
  filterEdit = new QLineEdit(hidtWdgt);
  filterEdit->setPlaceholderText("Search...");
  bkmrkWidget = new QTreeWidget(hidtWdgt);
  bkmrkWidget->setHeaderHidden(true);
  bkmrkWidget->setIconSize(QSize(12, 12));
  bkmrkWidget->setMaximumWidth(128);
  //listWidget->addItem("hello");
  //listWidget->addItem("see");
  connect(bkmrkWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(itemAction(QTreeWidgetItem *)));
  
  QVBoxLayout *mainLayout = new QVBoxLayout();
  //mainLayout->addWidget(mainToolBar);
  mainLayout->addWidget(filterEdit);
  //mainLayout->addWidget(searchLineEdit);
  mainLayout->addWidget(bkmrkWidget);
  hidtWdgt->setLayout(mainLayout);

  bkmrkFile = new QFile(pluginHomepath() + "/bookmarks.xbel");
//   QFileInfo fi(pluginHomepath() + "/bookmarks");
  //fileWatcher = new QFileSystemWatcher(this);
  /*if (fi.exists())
  	fileWatcher->addPath(pluginHomepath() + "/bookmarks");
  connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(loadHistory()));*/

  loadSettings();
  loadBookmarks();
  return hidtWdgt;
}

void pnlBookmarks::loadBookmarks()
{
  if (!bkmrkFile->open(QIODevice::ReadOnly | QIODevice::Text))
    qWarning("Failed to open bookmarks file.");
  
  XbelReader reader(bkmrkWidget);
     if (!reader.read(bkmrkFile)) {
       qWarning("Failed to read bookmarks file.");
//          qWarning(tr("QXmlStream Bookmarks"), tr("Parse error in file %1:\n\n%2").arg(bkmrkFile->fileName()).arg(reader.errorString()));
     }
/*  
  listWidget->clear();
  while (!histFile->atEnd()) {
    QString line = histFile->readLine();
    QStringList word = line.split("\n");
    listWidget->addItem(word[0]);
    //listWidget->addItem(line.trimmed());
  }
  histFile->close();*/
}

QWidget *pnlBookmarks::createConfWidget(QWidget* parent)
{
  confWdgt = new QWidget(parent);
  
  /*QLabel *titleLabel = new QLabel( confWdgt );
  titleLabel->setText( tr( "Number of words to show:" ) );
  titleLabel->setWhatsThis(tr("This is the number of words that will be added to history."));
  
  histNumber = new QSpinBox(confWdgt);
  histNumber->setMinimum(0);

  QSettings settings(config(), QSettings::IniFormat);
  histNumber->setValue(settings.value("History/historyNumber").toInt());*/
	
  QVBoxLayout *mainLayout = new QVBoxLayout(confWdgt);
//   mainLayout->addWidget(titleLabel);
//   mainLayout->addWidget(histNumber);
  mainLayout->addStretch(0);
  confWdgt->setLayout(mainLayout);
  return confWdgt;
}

void pnlBookmarks::retranslateUi()
{
}

void pnlBookmarks::loadSettings()
{
  //QSettings settings(config(), QSettings::IniFormat);
  //settings.setValue("History/historyNumber", histNumber->value());
}

void pnlBookmarks::urlActivated(const QString &url)
{
  /*if (!url.isEmpty()) {
   
  }*/
  /*else
    phononWdgt->hide();*/
    //qDebug() << "i'm information panel:" << url;
}

/*void pnlBookmarks::createActions()
{
  //sortAction = new QAction(hidtWdgt);
  clearAction = new QAction(hidtWdgt);
}
void pnlBookmarks::createToolbars()
{
  //mainToolBar->addAction(sortAction);
  mainToolBar->addAction(clearAction);
}
void pnlBookmarks::retranslateUi()
{
#ifdef PLUGINDIR
  clearAction->setIcon(QIcon(QString(PLUGINDIR) + "/actions/edit-clear-history.png"));
#endif
  clearAction->setToolTip(tr("Clean History"));
  clearAction->setWhatsThis(tr("clean history."));
}*/

void pnlBookmarks::itemAction(QTreeWidgetItem *item)
{
  emit wordRequeste(item->text(0));
}

QString pnlBookmarks::pluginHomepath()
{
  QString hpath;
#ifndef Q_OS_WIN
  hpath = QDir::homePath() + "/.config/neda";
#else
  hpath = QDir::homePath() + "/.neda";
#endif
  return hpath;
}

QString pnlBookmarks::config()
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

void pnlBookmarks::saveSettings(void)
{
  /*QString confile = pluginHomepath() + "/plugins/" + name() + ".ini";
  QSettings settings(confile, QSettings::IniFormat);
  settings.setValue("History/historyNumber", histNumber->value());*/
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(pnlbookmarks, pnlBookmarks);
QT_END_NAMESPACE
