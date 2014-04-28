#include <QCoreApplication>
#include <QtCore>
#include <QApplication>

#include <QNetworkProxy>

#include <signal.h>
#include "manager/csinglecraw.h"
#include "SEOTaskStream/seodownloader.h"

using namespace ganji::crawler::octopus_crawler::downloader;

void SetCharset() {
  // 设置全局字符编码为UTF-8
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);
}

void SigTerm(int x) {
  exit(0);
}

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  SetCharset();
  /*
  signal(SIGTERM, SigTerm);
  signal(SIGINT,  SigTerm);
#ifdef LINUX
  signal(SIGKILL, SigTerm);
  signal(SIGPIPE, SigTerm);
  signal(SIGHUP,  SigTerm);
#endif

  int spider_num = 0;

  if (a.arguments().size() >= 2)
  {
    //spider_num = a.arguments().at(1).toInt();
    spider_num = 1;
  }
   // if argc >= 5, set the proxy's attribute value
  if (a.arguments().size() >= 5)
  {
    // 设置全局代理，整个应用程序生存范围。
    QString hostname = a.arguments().at(3);
    int     port     = a.arguments().at(4).toInt();
    qDebug() << "use Proxy. hostname:" << hostname << "port:" << port;
    QNetworkProxy proxy;

    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(hostname);
    proxy.setPort(port);
    QNetworkProxy::setApplicationProxy(proxy);
    // proxy.setType(QNetworkProxy::HttpCachingProxy);
    // proxy.setCapabilities(QNetworkProxy::CachingCapability);
  }

  qDebug() << "Spider Num:" << spider_num;

  */

  QSettings* seoSetting = new QSettings("D:\\crawler_bot_conf.ini",  QSettings::IniFormat);

  SEOdownloader seoDownloader;

  seoDownloader.Init(seoSetting);
  seoDownloader.Run();

  /*
  // crawler begin
  CSingleCraw singlecraw;
  if (spider_num <= 0 || spider_num >= 100)
  {
    qDebug() << "Error spider_num:" << spider_num;
    exit(1);
  }
  else
  {
    singlecraw.Start(spider_num);
  }
  */

  return a.exec();
}

/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
*/
