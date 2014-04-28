#ifndef CSINGLECRAW_H
#define CSINGLECRAW_H

#ifndef LINUX
//#include<windows.h>
#endif

#include <time.h>
//#include <unistd.h>

#include<vector>

#include <QThread>
#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include <QMutex>

#include "KeyWordItem.h"
#include "cpageloader/cpageloader.h"
//#include "SEOTaskStream/bot_client.h"
#include "gen-cpp/octopus_crawler_types.h"

using namespace std;

class CSingleCraw : public QObject
{
  Q_OBJECT
public:
  explicit CSingleCraw(QObject *parent = 0);

  QList<KeyWordItem> getTaskWordList(QStringList&  key_word_lines,
                                     bool&         is_read_done);

  QList<KeyWordItem> getTaskWordList(vector<SimulatorTask> reqTaskVector,
                                     vector<SimulatorTask>& respTaskVector,
                                     bool& is_read_done);

  QList<KeyWordItem> getTaskWordList(vector<BotMessage> reqTaskVector,
                                     vector<BotMessage>& respTaskVector,
                                     bool& is_read_done);

  /*
  QList<KeyWordItem> getTaskList(vector<SimulatorTask>  taskVector,
                                 bool&                  is_read_done);
  */

  CPageLoader* pageLoaderFactory();
  void getAndClickInputPos(CPageLoader*& pageloader,
                           QWebElement& input);
  void getAndClickButton(QWebElement&   dom,
                         CPageLoader*&  pageloader);
  void keyWordProcess(QList<KeyWordItem>& word_list,
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

  void
  processSpanElem(QString& keyWordRank,
                  QWebElement& span_elem,
                  QWebElement& a_elem,
                  int& scroll_height,
                  int& window_height,
                  int& scroll_bar_maximun,
                  QString target_url,
                  CPageLoader*& pageloader,
                  bool& is_click,
                  bool& is_mousedown_ganji,
                  bool& is_prepare_ganji);

  void
  waitFunction(QElapsedTimer& elapsed_timer,
               QList<KeyWordItem>& word_lsit,
               int& spider_num);

  QString getCurTime();

  void Start(vector<SimulatorTask> reqTaskVector, int spider_num);
  void Start(vector<BotMessage> reqTaskVector, int spider_num);
  //void Start(vector<SimulatorTask>& taskVector, int spider_num);

  QEventLoop eventloop_;
  QTimer timer_;
  QTimer http_get_task_timer_;

  QString id_;
  QString rank_;

  //vector<SimulatorTask> SEOTaskVector_;
  //vector<SimulatorTask> respVector_;

  void Sleep(int msec);

public slots:
  void QuitEventLoop();

  void HttpGetSeoTask();
  void ThriftGetSeoTask(vector<SimulatorTask> SEOTaskVector);

private:
  QString seo_task_list_;
  QMutex mutex_;

public:
  //void BaiduSEOTest(int spider_num); // baidu.com 刷百度SEO
  vector<SimulatorTask> BaiduSEOTest(vector<SimulatorTask> reqTaskVector,
                                     int spider_num); // baidu.com 刷百度SEO
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


