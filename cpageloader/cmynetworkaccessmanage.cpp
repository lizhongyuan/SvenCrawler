#include "cpageloader/cmynetworkaccessmanage.h"

CMyNetworkAccessManager::CMyNetworkAccessManager()
{
  refuse_url_ = "";
}

void CMyNetworkAccessManager::SetRefuseUrl(QString url)
{
  refuse_url_ = url;
  qDebug() << "Set Refuse Url:" << url;
}

QNetworkReply *	CMyNetworkAccessManager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData)
{
  QString req_url = req.url().toEncoded();
  if (req_url.indexOf("http://sclick.baidu.com/w.gif?q=") >= 0 &&
      req_url.indexOf("&url=") >= 0)
  {
    qDebug() << " --> Find msg:" << req.url().toString();
  }
  if (
       (refuse_url_ != "" && req.url().toString().contains(refuse_url_, Qt::CaseInsensitive))
       || req.url().host().endsWith("ganji.com")
       || req.url().host().endsWith("mayi.com")
       || req.url().host().endsWith("58.com")
       || req.url().host().endsWith("baixing.com")
     )
  {
    QNetworkRequest invalidReq;
    invalidReq.setUrl(QUrl("about:blank"));
    qDebug() << "CMyNetworkAccessManager::createRequest() Found refuse url: " << req_url;
    return QNetworkAccessManager::createRequest(op, invalidReq, outgoingData);
  }
  return QNetworkAccessManager::createRequest(op,req,outgoingData);
}



//class MyNetworkAccessManager : public QNetworkAccessManager
//{
//public:
//MyNetworkAccessManager():
//QNetworkAccessManager()
//{
//}
//protected:
//virtual QNetworkReply *	createRequest ( Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0 )
//{
//qDebug()<<req.url().toString();
//QString hh = req.url().toString();
//if(hh.indexOf(tr("goog"))>0 || hh.indexOf(tr("baid"))>0)
//{
////QUrl s = QUrl("http://bj.58.com");
////req.setUrl(s);
//QNetworkRequest req1=req;
//req1.setUrl(QUrl(tr("http://bj.ganji.com")));
//return QNetworkAccessManager::createRequest(op,req1,outgoingData);
//}
//QNetworkReply * rt= QNetworkAccessManager::createRequest(op,req,outgoingData);
//QList<QByteArray> httpHeaders = rt->rawHeaderList();
//for(int i = 0;i<httpHeaders.size();++i)
//{
//const QByteArray & headname = httpHeaders.at(i);
//qDebug()<<QString::fromLatin1(headname)<<QString::fromLatin1(rt->rawHeader(headname));
//}
//return rt;
//}
//};
//QNetworkAccessManager * netMgr = new MyNetworkAccessManager();
////netMgr->setProxy(proxy);
//ui->webView->page()->setNetworkAccessManager(netMgr);
