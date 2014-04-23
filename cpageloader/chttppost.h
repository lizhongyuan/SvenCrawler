#ifndef CHTTPPOST_H
#define CHTTPPOST_H

#include <QObject>
#include <QtCore/QUrl>
#include <QtCore/QByteArray>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class CHttpPost : public QObject {
  Q_OBJECT
  QNetworkAccessManager m_manager;
public:
  explicit CHttpPost(QObject *parent = 0);

  // post数据到指定url
  bool doPost(const QUrl & url, const QByteArray & post_data);

private:
  QByteArray m_content;
  QEventLoop m_eventloop;
  bool is_post_success;

public slots:
  void postFinished(QNetworkReply * reply);

signals:

};

#endif // CHTTPPOST_H
