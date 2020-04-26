#ifndef DOIMANAGER_H
#define DOIMANAGER_H

#include <QNetworkAccessManager>

class doiManager : public QObject
{
Q_OBJECT

public:
  doiManager(QObject * parent = 0);
  ~doiManager();
  void fetch(QString doi);

private slots:
  void replyFinished(QNetworkReply*);

signals:
  QString textChanged(const QString&);
  //void finished(bool);
private:
  QNetworkAccessManager *m_manager;
};

#endif
