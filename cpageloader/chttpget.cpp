#include <QDebug>
#include "chttpget.h"

/*
 * 1. if the reply finished, emit a signal of QNetworkReply
 * 2. if the Timer timeout, emit a signal by timeout(), call the downloadTimeOut();
 */
CHttpGet::CHttpGet(QObject *parent) : QObject(parent)
{
  this->m_timer = new QTimer();
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
  connect(m_timer, SIGNAL(timeout()), this, SLOT(downloadTimeOut()));
}

CHttpGet::~CHttpGet() {
  delete this->m_timer;
}

/*
 *
 */
QByteArray CHttpGet::doDownload(const QUrl &url)
{
  QNetworkRequest request(url);
  this->m_timer->setSingleShot(true);

  // set the wait time for http get
  this->m_timer->start(20000);

  // 1. perform the http GET method
  this->m_manager.get(request);

  // 2. blocking, wait for the reply, unblocked by downloadFinished,
  //    and the downloadFinished will end the Eventloop
  this->m_eventloop.exec();
  return this->m_content;
}

/*
 *
 */
QByteArray CHttpGet::doDownload(const QUrl &url, int msecs)
{
  QNetworkRequest request(url);
  this->m_timer->setSingleShot(true);

  // set the wait time for http get
  this->m_timer->start(20000);

  // 1. perform the http GET method
  this->m_manager.get(request);

  // 2. blocking, wait for the reply, unblocked by downloadFinished,
  //    and the downloadFinished will end the Eventloop
  this->m_eventloop.exec();
  return this->m_content;
}

/*
 *
 */
QByteArray CHttpGet::doDownload(const QUrl &url, const QMap<QByteArray, QByteArray> & http_header)
{
  QNetworkRequest request(url);
  for (QMap<QByteArray, QByteArray>::const_iterator it = http_header.begin(); it != http_header.end(); it++)
  {
    request.setRawHeader(it.key(), it.value());
  }
  this->m_timer->setSingleShot(true);
  this->m_timer->start(20000);
  this->m_manager.get(request);
  this->m_eventloop.exec();
  return this->m_content;
}

/*
 * when the NetworkAccessManager send a signal, the following function is called
 */
void CHttpGet::downloadFinished(QNetworkReply *reply)
{
  QUrl url = reply->url();
  if (reply->error() == QNetworkReply::NoError)
  {
    QIODevice * data = (QIODevice *)reply;
    this->m_content = data->readAll();
  }
  else
  {
    // fprintf(stderr, "CDownloadManager::Error:Download of %s failed: %s\n",
    //         url.toEncoded().constData(),
    //         qPrintable(reply->errorString()));
  }
  reply->deleteLater();     // delete the pending events
  this->m_timer->stop();
  this->m_eventloop.quit();
}

void CHttpGet::downloadTimeOut()
{
  qDebug() << "CHttpGet::downloadTimeOut() 20secs. time out.";
  this->m_timer->stop();
  this->m_eventloop.quit();
}
