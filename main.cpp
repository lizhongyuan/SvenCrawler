#include <QCoreApplication>
#include <QtCore>
#include <QApplication>

#include <QNetworkProxy>

#include <signal.h>
#include "manager/csinglecraw.h"
#include "SEOTaskStream/seocontroller.h"

//#include<QTextStream>

using namespace ganji::crawler::octopus_crawler::downloader;

void SetCharset() {
  // 设置全局字符编码为UTF-8
  QTextCodec *codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(codec);
  QTextCodec::setCodecForCStrings(codec);
  QTextCodec::setCodecForTr(codec);

  //QTextStream::setCodec("UTF-8");
}

void SigTerm(int x) {
  exit(0);
}

QString
getLocalPath()
{
    QString runPath = QCoreApplication::applicationDirPath();
    return runPath;
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SetCharset();

  signal(SIGTERM, SigTerm);
  signal(SIGINT,  SigTerm);
#ifdef LINUX
  signal(SIGKILL, SigTerm);
  signal(SIGPIPE, SigTerm);
  signal(SIGHUP,  SigTerm);
#endif

  QSettings* seoSetting = new QSettings("./conf/crawler_bot_conf.ini",  QSettings::IniFormat);

  SEOController seoController;

  QString runPath = getLocalPath();
  qDebug()<<runPath;

  seoController.Init(seoSetting);
  seoController.Work();

  return a.exec();
}
