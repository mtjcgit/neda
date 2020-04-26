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
#include <QFileInfo>
#include <QTcpSocket>

#include "db-dict.h"

QString dbDict::name() const
{ return QLatin1String("db-dict"); }

QString dbDict::group() const
{ return QLatin1String("database"); }

QString dbDict::toolTip() const
{ return QLatin1String("This is dict implementation plug in."); }

QString dbDict::whatsThis() const
{ return QLatin1String("This is dict implementation plug in."); }

QString dbDict::type() const
{ return QLatin1String("dict"); }

QString dbDict::icon() const
{ return QLatin1String("dict.org-231x64.png"); }

QString dbDict::version() const
{ return QLatin1String("1.0.0"); }

QString dbDict::description() const
{ return QLatin1String("dict plugin..."); }

QString dbDict::wnToHtml(QByteArray &text)
{
  QList<QByteArray> splitText = text.split('\n');
    QString def;
    def += "<dl>\n";
    QRegExp linkRx("\\{(.*)\\}");
    linkRx.setMinimal(true);

    bool isFirst=true;
    while (!splitText.empty()) {
        //150 n definitions retrieved - definitions follow
        //151 word database name - text follows
        //250 ok (optional timing information here)
        //552 No match
        QString currentLine = splitText.takeFirst();
        if (currentLine.startsWith(QLatin1String("151"))) {
            isFirst = true;
            continue;
        }

        if (currentLine.startsWith('.')) {
            def += "</dd>";
            continue;
        }

        if (!(currentLine.startsWith(QLatin1String("150"))
           || currentLine.startsWith(QLatin1String("151"))
           || currentLine.startsWith(QLatin1String("250"))
           || currentLine.startsWith(QLatin1String("552")))) {
            currentLine.replace(linkRx,"<u>\\1</u>");

            if (isFirst) {
                def += "<dt><b>" + currentLine + "</b></dt>\n<dd>";
                isFirst = false;
                continue;
            } else {
                if (currentLine.contains(QRegExp("([1-9]{1,2}:)"))) {
                    def += "\n<br>\n";
                }
                currentLine.replace(QRegExp("^([\\s\\S]*[1-9]{1,2}:)"), "<b>\\1</b>");
                def += currentLine;
                continue;
            }
        }

    }

    def += "</dl>";
    return def;
}

QString dbDict::searchWord(const QString &db, const QString &wrd)
{
  QString dbName, mean;
  QFileInfo fi(db);
  dbName = fi.baseName();
  
  if (dbName.contains("freedict", Qt::CaseSensitive)) {
    dbName.replace(QString("freedict"), QString("fd"));
  } else if (dbName.contains("gazetteer", Qt::CaseSensitive)) {
    dbName.replace(QString("gazetteer"), QString("gaz"));
  }
  
  //serverName = "dict.org";
  //char *server = "localhost";
  serverName="localhost";
  dictName=dbName;
  
  /*if (tcpSocket) {
    tcpSocket->abort(); //stop if lookup is in progress and new word is requested
    tcpSocket->deleteLater();
    tcpSocket = 0;
  }*/
  tcpSocket = new QTcpSocket(this);
  //tcpSocket->abort();
  //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(getDefinition()));
  tcpSocket->connectToHost(serverName, 2628);
  if (!tcpSocket->waitForConnected(1000)) {
    qDebug() << tcpSocket->errorString().toLatin1();
  }
  
  tcpSocket->readAll();
  QByteArray ret;

    tcpSocket->write(QByteArray("DEFINE "));
    tcpSocket->write(dictName.toAscii());
    tcpSocket->write(QByteArray(" \""));
    tcpSocket->write(wrd.toUtf8());
    tcpSocket->write(QByteArray("\"\n"));
    tcpSocket->flush();

    while (!ret.contains("250") && !ret.contains("552")) {
        tcpSocket->waitForReadyRead();
        ret += tcpSocket->readAll();
    }
    tcpSocket->disconnectFromHost();
    
   mean = wnToHtml(ret);
    //mean = ret;

  return mean;
}

bool dbDict::hasConfig() const
{
  return true;
}

bool dbDict::isEditable() const
{
  return false;
}

QString dbDict::config()
{
  QString cfg;
  
#ifdef PLUGINDIR
  cfg = QString(PLUGINDIR) + "/" + name() + ".ini";
#endif

  return cfg;
}

QStringList dbDict::hosts()
{
  QStringList hs;
  hs << "localhost" << "dict.org";
  return hs;
}

void dbDict::saveSetting()
{
  QSettings settings(config(), QSettings::IniFormat);
  
  settings.setValue("generals/HostServer", hostComboBox->currentText());
}

QWidget *dbDict::createConfWidget(QWidget* parent)
{
  QWidget *cnfWidget = new QWidget(parent);
  
  /*
  titleLabel->setText( tr( "dbDict\n" ) );
	
  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->addWidget(titleLabel);
  cnfWidget->setLayout(mainLayout);*/
  QLabel *titleLabel = new QLabel(cnfWidget);
  titleLabel->setText( tr("Host of server: ") );
  hostComboBox = new QComboBox(cnfWidget);
  hostComboBox->setEditable(true);
  hostComboBox->addItems(hosts());
  hostComboBox->setWhatsThis( tr("Here you can choose host of dict server.") );
  //hostComboBox->setCurrentIndex(); //FIXME read from settings of plug in

  QSettings settings(config(), QSettings::IniFormat);
  hostComboBox->setCurrentIndex( hosts().indexOf(settings.value("generals/HostServer").toString()));

  QPushButton *aa = new QPushButton(cnfWidget);
  connect(aa, SIGNAL(clicked()), this, SLOT(saveSetting()));

  QGridLayout *mainLayout = new QGridLayout(cnfWidget);
  mainLayout->addWidget(titleLabel, 0, 0);
  mainLayout->addWidget(hostComboBox, 0, 1);
  mainLayout->addWidget(aa, 1, 0);
  
  return cnfWidget;
}

void dbDict::getDicts()
{
  /*
  QMap<QString, QString> theHash;
    tcpSocket->readAll();
    QByteArray ret;

    tcpSocket->write(QByteArray("SHOW DB\n"));;
    tcpSocket->flush();

    tcpSocket->waitForReadyRead();
    while (!ret.contains("250")) {
        tcpSocket->waitForReadyRead();
        ret += tcpSocket->readAll();
    }

    QList<QByteArray> retLines = ret.split('\n');
    QString tmp1, tmp2;

    while (!retLines.empty()) {
        QString curr(retLines.takeFirst());

        if (curr.startsWith(QLatin1String("554"))) {
            //TODO: What happens if no DB available?
            //TODO: Eventually there will be functionality to change the server...
            break;
        }

        // ignore status code and empty lines
        if (curr.startsWith(QLatin1String("250")) || curr.startsWith(QLatin1String("110"))
           || curr.isEmpty()) {
            continue;
        }

        if (!curr.startsWith('-') && !curr.startsWith('.')) {
            curr = curr.trimmed();
            tmp1 = curr.section(' ', 0, 0);
            tmp2 = curr.section(' ', 1);
  //          theHash.insert(tmp1, tmp2);
            //kDebug() << tmp1 + "  " + tmp2;
            setData("list-dictionaries", tmp1, tmp2);
        }
    }

    tcpSocket->disconnectFromHost();
//    setData("list-dictionaries", "dictionaries", QByteArray(theHash);
  */
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(dbdict, dbDict);
QT_END_NAMESPACE
