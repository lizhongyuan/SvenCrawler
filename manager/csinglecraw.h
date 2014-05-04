#ifndef CSINGLECRAW_H
#define CSINGLECRAW_H

#ifndef LINUX
//#include<windows.h>
#endif

#include <time.h>

#include<vector>

#include <QThread>
#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include <QMutex>

#include "KeyWordItem.h"
#include "cpageloader/cpageloader.h"
#include "gen-cpp/octopus_crawler_types.h"
#include "cookiestruct.h"

using namespace std;

class CSingleCraw : public QObject
{
  Q_OBJECT
public:
  explicit CSingleCraw(QObject *parent = 0);

  QList<KeyWordItem> getTaskWordList(vector<BotMessage> reqTaskVector,
                                     vector<BotMessage>& respTaskVector);

  CPageLoader* pageLoaderFactory();
  void getAndClickInputPos(CPageLoader*& pageloader,
                           QWebElement& input);
  void getAndClickButton(QWebElement&   dom,
                         CPageLoader*&  pageloader);
  bool keyWordProcess(QList<KeyWordItem>& word_list,
                      CPageLoader*& pageloader,
                      int spider_num);
  void simulateInputKeyWord(QString key_word,
                            CPageLoader*& pageloader,
                            QWebElement& input);
  void getContentFromPages(bool& is_mousedown_ganji,
                           CPageLoader*& pageloader,
                           QString target_url,
                           int& max_page_load,
                           int& scroll_height);
  bool
  getSpanElem(QWebElement& span_elem, QWebElement& curColl);

  void
  gotoNextPage(int page_idx,
               CPageLoader*& pageloader,
               QWebElement& dom,
               int& window_height,
               int& scroll_height,
               int& scroll_bar_maximun);

  //void
  bool
  processSpanElem(QString& keyWordRank,
                  QWebElement& span_elem,
                  QWebElement& a_elem,
                  int& scroll_height,
                  int& window_height,
                  int& scroll_bar_maximun,
                  QString target_url,
                  CPageLoader*& pageloader);

  void
  waitFunction(QElapsedTimer& elapsed_timer,
               QList<KeyWordItem>& word_lsit,
               int& spider_num);


  void
  addCookies();

  QString
  getLocalIP();

  QString getCurTime();

  void Start(vector<BotMessage> reqTaskVector, int spider_num);

  QEventLoop eventloop_;
  QTimer timer_;
  QTimer http_get_task_timer_;

  QString id_;
  QString rank_;

  void Sleep(int msec);

public slots:
  void QuitEventLoop();

  //void HttpGetSeoTask();
  void ThriftGetSeoTask(vector<SimulatorTask> SEOTaskVector);

private:
  QString seo_task_list_;
  QMutex mutex_;
  cookieStruct cookieStruct_;

public:
  vector<BotMessage> BaiduSEOTest(vector<BotMessage> reqTaskVector,
                                     int spider_num); // baidu.com 刷百度SEO
};

class SeoRankRepotThread : public QThread {
 public:
  void run();
  QString id_;
  QString rank_;
};

#endif // CSINGLECRAW_H


