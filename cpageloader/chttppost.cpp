//#include "bot_client.h"
#include "SEOTaskStream/bot_client.h"

//#include "page_loader/chttppost.h"
#include "cpageloader/chttppost.h"

CHttpPost::CHttpPost(QObject *parent) : QObject(parent) {
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
          SLOT(postFinished(QNetworkReply*)));
}

bool CHttpPost::doPost(const QUrl & url, const QByteArray & post_data) {
  QNetworkRequest req;
  this->m_content = post_data;
  req.setUrl(url);
  req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  req.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
  this->m_manager.post(req, post_data);
  this->m_eventloop.exec();
  return this->is_post_success;
}

void CHttpPost::postFinished(QNetworkReply * reply) {
  QUrl url = reply->url();
  if (reply->error() != QNetworkReply::NoError) {
    //        fprintf(stderr, "CHttpPost::Error:PostData of %s failed: %s\n",
    //                url.toEncoded().constData(),
    //                qPrintable(reply->errorString()));
    this->is_post_success = false;
  } else {
    // QIODevice * data = (QIODevice *)reply;
    // this->m_content = data->readAll();
    this->is_post_success = true;
  }
  reply->deleteLater();
  this->m_eventloop.quit();
}

