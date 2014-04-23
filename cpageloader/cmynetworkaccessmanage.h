#ifndef CMYNETWORKACCESSMANAGER_H
#define CMYNETWORKACCESSMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore>
#include <QString>

class CMyNetworkAccessManager : public QNetworkAccessManager {
public:
  CMyNetworkAccessManager();

  void SetRefuseUrl(QString url);

protected:
  /*
  QNetworkAccessManager
  HeadOperation     1	retrieve headers operation (created with head())
  GetOperation      2	retrieve headers and download contents (created with get())
  PutOperation	    3	upload contents operation (created with put())
  PostOperation	    4	send the contents of an HTML form for processing via HTTP POST (created with post())
  DeleteOperation	5	delete contents operation (created with deleteResource())
  CustomOperation	6	custom operation (created with sendCustomRequest())
  */
  virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

public:
  QString refuse_url_;

};

#endif // CMYNETWORKACCESSMANAGER_H
