#ifndef CHTTPGET_H
#define CHTTPGET_H

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QEventLoop>

class CHttpGet : public QObject
{
  Q_OBJECT
  QNetworkAccessManager m_manager;

public:

  explicit CHttpGet(QObject *parent = 0);
  ~CHttpGet();

  // 下载指定url
  QByteArray doDownload(const QUrl & url);
  QByteArray doDownload(const QUrl &url, int msecs);
  QByteArray doDownload(const QUrl & url, const QMap<QByteArray, QByteArray> & http_header);

  //signals:

public slots:
  void downloadFinished(QNetworkReply *reply);
  void downloadTimeOut();

private:
  QByteArray m_content;
  QEventLoop m_eventloop;
  QTimer * m_timer;
};

#endif // CHTTPGET_H
