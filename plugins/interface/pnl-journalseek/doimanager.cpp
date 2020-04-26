#include <QUrl>
#include <QNetworkRequest>
#include <QDebug>
#include <QByteArray>
#include <QNetworkReply>

#include "doimanager.h"

doiManager::doiManager(QObject *parent) : QObject(parent)
{
  m_manager = new QNetworkAccessManager(this);
  connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

doiManager::~doiManager()
{
}

void doiManager::fetch(QString doi)
{
  //QString m_url = "http://dx.doi.org/" + doi;
  QString m_url = "http://data.crossref.org/" + doi;
  QNetworkRequest req;
  req.setUrl(QUrl(m_url));
  //req.setRawHeader("Content-Type", "application/x-bibtex");
  //req.setRawHeader(QString("Accept").toLatin1(), QString("text/bibliography; style=bibtex").toLatin1());
  req.setRawHeader(QString("Accept").toAscii(), QString("application/x-bibtex;q=0.5").toAscii());
  m_manager->get(req);
}

void doiManager::replyFinished(QNetworkReply *pReply)
{
   emit textChanged(QString::fromUtf8(pReply->readAll().data()));
   //emit finished(true);
}
