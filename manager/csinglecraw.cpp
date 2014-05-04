#include "csinglecraw.h"
#include "cpageloader/chttpget.h"
#include "cpageloader/cpageloader.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTest>
#include <QtNetWork>

#include <gen-cpp/octopus_crawler_types.h>

#include "./conf/csqlhelper.h"
#include "cookiestruct.h"

#include"stdlib.h"

using namespace std;

CSingleCraw::CSingleCraw(QObject *parent) : QObject(parent) {
  connect(&(this->timer_), SIGNAL(timeout()), this, SLOT(QuitEventLoop()));
  connect(&(this->http_get_task_timer_), SIGNAL(timeout()), this, SLOT(HttpGetSeoTask()));
  connect(&(this->timer_), SIGNAL(timeout()), this, SLOT(QuitEventLoop()), Qt::QueuedConnection);

  connect(&(this->http_get_task_timer_), SIGNAL(timeout()), this, SLOT(HttpGetSeoTask()), Qt::QueuedConnection);
  this->HttpGetSeoTask();
  this->http_get_task_timer_.start(60000);
}

void CSingleCraw::Start(vector<BotMessage> reqTaskVector, int spider_num)
{
  this->BaiduSEOTest(reqTaskVector, spider_num);
}

void CSingleCraw::QuitEventLoop()
{
  this->eventloop_.quit();
}

/*
 * get the SEO task
 */
void
CSingleCraw::HttpGetSeoTask()
{
  qDebug() << "HttpGetSeoTask";
  QByteArray word_list =
      "2489	招聘前台	ganji.com	100	0	8\n"
      "2490	招聘客服	ganji.com	100	1	3\n"
      "###done###";
  this->mutex_.lock();
  if (word_list.indexOf("###done###") >= 0)
  {
    this->seo_task_list_ = word_list;
  }
  this->mutex_.unlock();
}


/*
 * get the SEO task
 */
void
CSingleCraw::ThriftGetSeoTask(vector<SimulatorTask> SEOTaskVector)
{
}

/*
 *
 */
void CSingleCraw::Sleep(int msec)
{
  // 暂停msec毫秒
  this->timer_.setSingleShot(true);
  this->timer_.start(msec);
  this->eventloop_.exec();
}



QList<KeyWordItem>
CSingleCraw::getTaskWordList(vector<BotMessage> reqTaskVector,
                             vector<BotMessage>& respTaskVector
                             )
                             //bool& is_read_done
{
    QList<KeyWordItem> keyWordItemList;


    for (vector<BotMessage>::iterator iter = reqTaskVector.begin();
         iter != reqTaskVector.end(); iter++)
    {
      KeyWordItem kwi;
      BotMessage curRespTask;

      this->addCookies();

      kwi.task_id = QString::number(iter->simulator_task.req_item.task_id);
      kwi.click_count = iter->simulator_task.req_item.click_count;
      kwi.city = QString::fromStdString(iter->simulator_task.req_item.city);
      kwi.key_words = QString::fromStdString(iter->simulator_task.req_item.key_words);
      kwi.url_regex = QString::fromStdString(iter->simulator_task.req_item.url_regex);

      curRespTask.simulator_task.resp_item.task_id = iter->simulator_task.req_item.task_id;
      curRespTask.simulator_task.resp_item.target_url = iter->simulator_task.req_item.url_regex;
      curRespTask.simulator_task.resp_item.cookie = this->cookieStruct_.uploadCookieStr.toStdString();
      curRespTask.simulator_task.resp_item.ip = this->getLocalIP().toStdString();
      curRespTask.simulator_task.resp_item.time_stamp = this->getCurTime().toStdString();
      curRespTask.bot_task_types = BotTasktypes::type::KSEOTASK;

      QString localHostName = QHostInfo::localHostName();
      QHostInfo info = QHostInfo::fromName(localHostName);
      //curRespTask.simulator_task.resp_item.ip = info.addresses()[0].toString().toStdString();

      std::cout<<"The IP is: "<<curRespTask.simulator_task.resp_item.ip<<std::endl;
      curRespTask.simulator_task.resp_item.node_id = 796;

      respTaskVector.push_back(curRespTask);

      for (int i = 0; i < kwi.click_count; i++)
      {
        keyWordItemList.append(kwi);
      }
    }
    return keyWordItemList;
}

QString
CSingleCraw::getLocalIP()
{
  for(int i = 0; i < QNetworkInterface().allAddresses().size(); i++)
  {
    QString curIP = QNetworkInterface().allAddresses().at(i).toString();

    QString pattern("((?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d))))");
    QRegExp rx(pattern);

    bool match = rx.exactMatch(curIP);
    if(match && curIP.compare("127.0.0.1"))
    {
        return curIP;
    }
  }

  return NULL;
}

void
CSingleCraw::addCookies()
{
  CHttpGet http;
  QString get_cookie = http.doDownload(QUrl("http://hhgjgame006.3322.org:19999/cookie.php?act=get"));
  QStringList cookie_list = get_cookie.split("\t");
  qDebug() << "Http Get Cookie:" << cookie_list;
  QString cookie_id = "";
  QString cookie_val = "";
  if (cookie_list.count() >= 3)
  {
    cookie_id = cookie_list[0];
    cookie_val = cookie_list[1].trimmed();
    this->cookieStruct_.userAgent = cookie_list[2];
    if (cookie_val.indexOf("BAIDUID=") >= 0)
    {
      this->cookieStruct_.networkCookieList = QNetworkCookie::parseCookies(cookie_val.toAscii());
    }
    else
    {
      QNetworkCookie network_cookie;
      network_cookie.setName("BAIDUID");
      network_cookie.setValue(cookie_val.toAscii());
      network_cookie.setExpirationDate(QDateTime::currentDateTime().addYears(29));
      network_cookie.setDomain(".baidu.com");
      network_cookie.setPath("/");
      this->cookieStruct_.networkCookieList.append(network_cookie);
    }

    for(QList<QNetworkCookie>::iterator citer = this->cookieStruct_.networkCookieList.begin();
        citer != this->cookieStruct_.networkCookieList.end();
        citer++)
    {
      QByteArray curCont = citer->toRawForm();
      this->cookieStruct_.uploadCookieStr.prepend(curCont);
    }

    /*
    qDebug() << "Network Cookie List:" << network_cookie_list;
    pageloader->SetUserAgent(useragent);
    qDebug() << "User Agent:" << pageloader->GetUserAgent();
    pageloader->GetWebView()->page()->networkAccessManager()->cookieJar()->setCookiesFromUrl(network_cookie_list, QUrl("http://www.baidu.com"));
    qDebug() << "All Cookie:" << pageloader->GetWebView()->page()->networkAccessManager()->cookieJar()->cookiesForUrl(QUrl("http://www.baidu.com"));
    */
  }
}


QString
CSingleCraw::getCurTime()
{
    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("yyyy-MM-dd hh:mm:ss");

    return currentDate;
}

/*
 *
 */
CPageLoader*
CSingleCraw::pageLoaderFactory()
{
  CPageLoader* pageLoaderPtr = new CPageLoader();
  if (pageLoaderPtr == NULL)
  {
    qDebug()<<"Failed in new CPageLoader object";
    return NULL;
  }

  pageLoaderPtr->SetIsLoadImage(true);
  pageLoaderPtr->Show(true);
  pageLoaderPtr->SetIsOpenNewWindow(false);

  return pageLoaderPtr;
}

/*
 *
 */
bool InBlackList(QString url)
{
  QStringList black_list;
  black_list << "58.com";
  black_list << "baixing.com";
  black_list << "51job.com";

  for (int i = 0; i < black_list.count(); i++) {
    if (url.contains(black_list[i], Qt::CaseInsensitive)) {
      return true;
    }
  }

  return false;
}


void
CSingleCraw::simulateInputKeyWord(QString key_words,
                                  CPageLoader*& pageloader,
                                  QWebElement& input)
{
  for (int fi = 0; fi < key_words.length(); )
  {
    QString rand_str = "";
    int     rand_int = 1 + rand() % 3;
    for (int ri = 0; ri < rand_int; ++ri)
    {
      char rand_char = 'a' + (rand() % 26);
      rand_str += rand_char;
      input.evaluateJavaScript("this.value += \"" + QString(rand_char) + "\"");
      this->Sleep(rand() % 300 + 200);
    }
    for (int ri = 0; ri < rand_int; ++ri)
    {
      QTest::keyClick(pageloader->GetWebView(), Qt::Key_Backspace);
      this->Sleep(rand() % 300 + 200);
    }

    int word_len = rand() % 1 + 1;
    QString seg_word = "";
    for (int word_i = fi; word_i < key_words.length() && word_i < fi + word_len; word_i++)
    {
      seg_word += key_words[word_i];
    }
    fi += word_len;
    input.evaluateJavaScript("this.value += \"" + seg_word + "\"");
    QTest::keyClick(pageloader->GetWebView(), Qt::Key_Space);
    QTest::keyClick(pageloader->GetWebView(), Qt::Key_Backspace);

    this->Sleep(rand() % 500 + 1000);
  }
  input.evaluateJavaScript("this.blur();");
}



void
CSingleCraw::getAndClickInputPos(CPageLoader*& pageloader,
                                 QWebElement& input)
{
  int input_width  = input.geometry().width()  < 5 ? 5 : input.geometry().width();
  int input_height = input.geometry().height() < 2 ? 2 : input.geometry().height();
  int input_click_x = input.geometry().left() + 5 + (rand() % (input_width  - 5));
  int input_click_y = input.geometry().top()  + 2 + (rand() % (input_height - 2));
  qDebug() << "Input Click Pos:" << input_click_x << input_click_y << " Input:" << input.geometry().width() << input.geometry().height();
  QTest::mouseEvent(QTest::MouseClick, pageloader->GetWebView(), Qt::LeftButton, Qt::NoModifier, QPoint(input_click_x, input_click_y), -1);
}


void
CSingleCraw::getAndClickButton(QWebElement&   dom,
                       CPageLoader*&  pageloader)
{
  QWebElement btn = dom.findFirst("input#su1");
  int btn_x = btn.geometry().left() + (rand() % btn.geometry().width());
  int btn_y = btn.geometry().top()  + (rand() % btn.geometry().height());
  QTest::mouseEvent(QTest::MouseClick, pageloader->GetWebView(), Qt::LeftButton, Qt::NoModifier, QPoint(btn_x, btn_y), 100);
}


bool
CSingleCraw::getSpanElem(QWebElement& spanElem,
                         QWebElement& curColl)
{
  bool isExist = false;
  spanElem = curColl.findFirst("font[size='-1'] span.g");
  if (spanElem.isNull())
  {
    spanElem = curColl.findFirst("span.g"); //百度快照前面的
    if(spanElem.isNull())
        qDebug()<<"Fuck fuck fuck";
    isExist = true;
  }
  if (spanElem.isNull())
  {
    spanElem = curColl.findFirst("div.f13 span.g"); //百度快照前面的
    isExist = true;
  }
  if (spanElem.isNull())
  {
    spanElem = curColl.findFirst("font[size='-1']");
    isExist = true;
  }
  if (spanElem.isNull())
  {
    isExist = false;
  }
  return isExist;
}



//void
bool
CSingleCraw::processSpanElem(QString& keyWordRank,
                             QWebElement& spanElem,
                             QWebElement& clickLinkElement,
                             int& scroll_height,
                             int& windowHeight,
                             int& scroll_bar_maximun,
                             QString url_regex,
                             CPageLoader*& pageloader)
{
  QString spanStr = spanElem.toPlainText().trimmed();
  url_regex = url_regex.replace("http://", "");
  if (spanStr.indexOf(url_regex) < 0 || InBlackList(spanStr))
  {
      return false;
  }

  // get the scroller's position
  int clickXPos = clickLinkElement.geometry().left() + (rand() % clickLinkElement.geometry().width());
  int clickYPos = clickLinkElement.geometry().top()  + (rand() % clickLinkElement.geometry().height()) - scroll_height;


  while (clickYPos > windowHeight - (rand() % 100 + 30))
  {
    int rand_scroll = 100 + rand() % 2;

    if (scroll_height + rand_scroll < scroll_bar_maximun) // in the mid
    {
      clickYPos -= rand_scroll;               //向下移动rand_scroll
      scroll_height += rand_scroll;   // same as above
      pageloader->GetWebView()->page()->mainFrame()->scroll(0, rand_scroll);
    }
    else                                                  // to the end
    {
      int next_scroll = scroll_bar_maximun - scroll_height;
      clickYPos -= next_scroll;
      scroll_height += next_scroll;
      pageloader->GetWebView()->page()->mainFrame()->scroll(0, scroll_height);
    }
    this->Sleep(rand() % 200 + 400);
  }
  this->Sleep(rand() % 500 + 500);

  // get the refuse url
  QString refuse_url = "";
  QStringList url_tmp_list = spanStr.replace("...", " ").trimmed().split(" ");
  if (url_tmp_list.count() >= 1)
  {
    refuse_url = QUrl("http://" + url_tmp_list[0]).host();
  }

  qDebug() << "spanStr:" << spanStr << " : " << url_tmp_list;
  pageloader->m_mynetworkAccessManager.SetRefuseUrl(refuse_url);
  qDebug() << "Link Pos scrolled:" << clickXPos << clickYPos;

  // click the clickLinkPos, but don't show the page
  QTest::mouseEvent(QTest::MouseClick, pageloader->GetWebView(), Qt::LeftButton, Qt::NoModifier, QPoint(clickXPos, clickYPos), -1);
  this->rank_ = keyWordRank;
  this->Sleep(rand() % 1000 + 2000);

  SeoRankRepotThread seo_rank_report_thread;
  seo_rank_report_thread.id_   = this->id_;
  seo_rank_report_thread.rank_ = this->rank_;
  seo_rank_report_thread.run();

  this->Sleep(rand() % 500 + 1000);

  return true;
}

void
CSingleCraw::gotoNextPage(int pageIdx,
                          CPageLoader*& pageloader,
                          QWebElement& dom,
                          int& windowHeight,
                          int& scroll_height,
                          int& scroll_bar_maximun)
{
  qDebug() << "Target url not found in current page index:" << pageIdx;
  QWebElementCollection page_coll = dom.findAll("*#page a");        // make sure 3: p[id=page] a
  for (int pidx = 0; pidx < page_coll.count(); pidx++)
  {
    QWebElement clickLinkElement = page_coll[pidx];
    if (clickLinkElement.toPlainText().trimmed() == QString::number(pageIdx + 1))
    {
      qDebug() << "Prepare to load page index:" << pageIdx + 1;
      int x = clickLinkElement.geometry().left() + (rand() % clickLinkElement.geometry().width());
      int y = clickLinkElement.geometry().top()  + (rand() % clickLinkElement.geometry().height()) - scroll_height;
      qDebug() << "Target Page Btn Pos:" << x << y
               << "Window Height:" << windowHeight
               << "Scroll Bar Maximum" << scroll_bar_maximun;
      while (y > windowHeight - (rand() % 10 + 40))
      {
        int rand_scroll = 100 + rand() % 2;
        if (scroll_height + rand_scroll < scroll_bar_maximun)
        {
          y -= rand_scroll;
          scroll_height += rand_scroll;
          pageloader->GetWebView()->page()->mainFrame()->scroll(0, rand_scroll);
        }
        else
        {
          int next_scroll = scroll_bar_maximun - scroll_height;
          y -= next_scroll;
          scroll_height += next_scroll;
          pageloader->GetWebView()->page()->mainFrame()->scroll(0, scroll_height);
        }
        this->Sleep(rand() % 200 + 800);
      }
      // --- scroll to bottom
      int next_scroll = scroll_bar_maximun - scroll_height;
      y -= next_scroll;
      scroll_height += next_scroll;
      pageloader->GetWebView()->page()->mainFrame()->scroll(0, scroll_height);

      // ---
      this->Sleep(rand() % 500 + 1000);
      qDebug() << "Target Page Btn Pos Scrolled:" << x << y;
      QTest::mouseEvent(QTest::MouseClick, pageloader->GetWebView(), Qt::LeftButton, Qt::NoModifier, QPoint(x, y), -1);
      this->Sleep(rand() % 500 + 2000);
      break;
    }
  }
}


/*
 *
 */
void
CSingleCraw::getContentFromPages(bool& is_mousedown_ganji,
                                 CPageLoader*& pageloader,
                                 QString url_regex,
                                 int& max_page_load,
                                 int& scroll_height)
{
  for (int pageIdx = 1; pageIdx <= max_page_load && is_mousedown_ganji == false; pageIdx++)
  {
    QWebElement dom = pageloader->GetWebElement();
    scroll_height = 0;
    qDebug() << " --> Now At Page:" << pageIdx;
    int windowHeight = pageloader->GetWebView()->page()->mainFrame()->geometry().height();
    int scroll_bar_maximun = pageloader->GetWebView()->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);

    // get all the blocks
    QWebElementCollection resultBlockCollection = dom.findAll("div.result");       // make sure1
    qDebug()<<"div.result: "<<resultBlockCollection.count();

    // traverse all the blocks
    for (int resultBlockIdex = 0;
         resultBlockIdex < resultBlockCollection.count();
         resultBlockIdex++)
    {
      std::cout<<"resultBlockIdex:"<<resultBlockIdex<<endl;

      QString keyWordRank = resultBlockCollection[resultBlockIdex].attribute("id");
      qDebug()<<"key word rank : "<< keyWordRank;

      // get the click url link position
      QWebElement clickLinkElement = resultBlockCollection[resultBlockIdex].findFirst("a");
      QWebElement spanElem;

      bool getRet = this->getSpanElem(spanElem, resultBlockCollection[resultBlockIdex]);
      if(!getRet)
      {
        qDebug()<<"can't parse the result blocks in page";
        continue;
      }

      is_mousedown_ganji = this->processSpanElem(keyWordRank,
                                                      spanElem,
                                                      clickLinkElement,
                                                      scroll_height,
                                                      windowHeight,
                                                      scroll_bar_maximun,
                                                      url_regex,
                                                      pageloader);

      // 4/5的可能
      if (is_mousedown_ganji == true)
      {
        if (rand() % 100 < 80)
        {
          cout<<"4/5, dont turn to next page"<<endl;
          break;
        }
      }
      cout<<"1/5, dont turn to next page"<<endl;
    }

    /*
     * ---------------------------------------------------
     * this page doesn't have ganji's reference, goto the next
     * ---------------------------------------------------
     */
    if (is_mousedown_ganji == false && pageIdx + 1 <= max_page_load)
    {
      gotoNextPage(pageIdx,
                   pageloader,
                   dom,
                   windowHeight,
                   scroll_height,
                   scroll_bar_maximun);
    }
  }
}


void
CSingleCraw::waitFunction(QElapsedTimer& elapsed_timer,
                          QList<KeyWordItem>& word_list,
                          int& spider_num)
{
  int now_hour = QDateTime::currentDateTime().time().hour();

  int visit_times_per_hour[24] = {100.697, 45.686, 25.848, 17.1, 13.626, 16.914, 35.948,
                                  79.833, 219.513, 336.597, 369.129, 350.273, 291.23, 308.35,
                                  332.05, 345.447, 345.31, 298.754, 230.526, 225.123, 252.20,
                                  267.329, 232.947, 155.963};

  double visit_per_day = ((double)word_list.count()) / ((double)spider_num);
  if (visit_per_day >= 5000.0)
  {
    qDebug() << "Too Many Task >= 5000. Set visit_per_day=5000.";
    visit_per_day = 5000.0;
  }
  int elapsed_time = elapsed_timer.elapsed();
  qDebug() << "Elapsed Time:" << elapsed_time;
  elapsed_time += 3000;

  qDebug() << "Visit Per Day:" << visit_per_day;
  int sleep_time = 60000 / (visit_per_day / 4896.402 / 60.0 * visit_times_per_hour[now_hour]);
  // sleep_time -= (rand() % 3000 + 17000);  // 减去一次点击大概消耗的20秒
  sleep_time -= elapsed_time; // 减去刚才消耗的时间。
  if (sleep_time < 1000) sleep_time = rand() % 1000 + 1000;
  if (sleep_time > 1800000) sleep_time = 1800000;
  qDebug() << "Sleep Time:" << sleep_time << " ms.";
  this->Sleep(sleep_time);
}


bool
CSingleCraw::keyWordProcess(QList<KeyWordItem>& word_list,
                            CPageLoader*& pageloader,
                            int spider_num)
{
  bool keyWordProcessDone = false;

  srand(unsigned(time(NULL)));
  uint pre_time = time(NULL);
  int wi = rand() % word_list.count();

  std::cout<<"keyWordList's size is"<<word_list.size()<<std::endl;

  this->id_ = word_list[wi].task_id;
  QString key_words = word_list[wi].key_words;
  QString url_regex = word_list[wi].url_regex;
  //while (time(NULL) - pre_time < 400 && )

  while(wi-- >= 0)
  {
    std::cout<<"cur wi is : "<<wi<<std::endl;

    if (key_words == "" || url_regex == "") {
      qDebug() << "Warning: key_words or url_regex is NULL.";
      this->Sleep(1000);
      continue;
    }

    qDebug() << "Current Key Word:" << key_words << "Target Url:" << url_regex;

    QElapsedTimer elapsed_timer;
    elapsed_timer.restart();

    qDebug() << "Network Cookie List:" << this->cookieStruct_.networkCookieList;
    pageloader->SetUserAgent(this->cookieStruct_.userAgent);
    qDebug() << "User Agent:" << pageloader->GetUserAgent();
    pageloader->GetWebView()->page()->networkAccessManager()->cookieJar()->setCookiesFromUrl(this->cookieStruct_.networkCookieList, QUrl("http://www.baidu.com"));
    qDebug() << "All Cookie:" << pageloader->GetWebView()->page()->networkAccessManager()->cookieJar()->cookiesForUrl(QUrl("http://www.baidu.com"));
    qDebug() << "All Cookie2:" << this->cookieStruct_.uploadCookieStr;

    pageloader->Get(QUrl("http://www.baidu.com/"));

    // 百度首页 输入第一个关键词
    QWebElement dom = pageloader->GetWebElement();

    qDebug()<<dom.toPlainText().toUtf8();

    if (dom.toPlainText().toUtf8().indexOf("使用百度前必读") == -1) {
      qDebug() << "Can not open www.baidu.com";
      this->Sleep(3000);
      continue;
    }

    QWebElement input = dom.findFirst("input#kw1");
    if (input.geometry().width() < 200 || input.geometry().height() < 10)
    {
      QWebElement input = dom.findFirst("input#kw");
    }
    if (input.geometry().width() < 200 || input.geometry().height() < 10)
    {
      qDebug() <<input.geometry().width();
      qDebug() <<input.geometry().height();
      qDebug() << "Fatal Error: Strange kw input.";
      this->Sleep(60000);
      continue;
    }

    this->getAndClickInputPos(pageloader,
                              input);

    this->Sleep(rand() % 500 + 2000);

    this->simulateInputKeyWord(key_words,
                               pageloader,
                               input);

    this->Sleep(rand() % 500 + 300);

    this->getAndClickButton(dom,
                            pageloader);

    qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "输入关键词：" << key_words << " Now At:" << pageloader->GetWebView()->url().toEncoded();

    this->Sleep(rand() % 3000 + 5000);

    dom = pageloader->GetWebElement();
    /*
    if (dom.toPlainText().indexOf("此内容系百度根据您的指令自动搜索的结果") == -1)
    {
      qDebug() << "Incomplete page. skip.";
      this->Sleep(3000);
      continue;
    }
    */

    bool is_mousedown_ganji = false;
    int scroll_height = 0;
    int max_page_load = 2;

    this->getContentFromPages(is_mousedown_ganji,
                              pageloader,
                              url_regex,
                              max_page_load,
                              scroll_height);

    if (is_mousedown_ganji == false) {
      qDebug() << "Warning: Could not find url_regex.";
      break;
    }

    keyWordProcessDone = true;

    //void waitFunction(QElapsedTimer& elapsed_timer)
    this->waitFunction(elapsed_timer,
                          word_list,
                          spider_num);
  }

  cout<<"=========================="<<endl;

  return keyWordProcessDone;
}


vector<BotMessage>
CSingleCraw::BaiduSEOTest(vector<BotMessage> reqTaskVector,
                          int spider_num) // baidu.com 刷百度SE
{
    vector<BotMessage> respTaskVector;

    if (reqTaskVector.empty())
    {
      qDebug() << "No task right now. sleep 70s";
      this->Sleep(70000);
      return respTaskVector;
    }

    //bool is_read_done = false;

    /*
     * build the keyWordItemList
     */
    QList<KeyWordItem> keyWordItemList = this->getTaskWordList(reqTaskVector,
                                                               respTaskVector
                                                               );
                                                               //is_read_done

    qDebug() << "keyWordItemList count():" << keyWordItemList.count();

    CPageLoader* pageloader = CSingleCraw::pageLoaderFactory();
    if(pageloader == NULL)
    {
        respTaskVector.clear();
        return respTaskVector;
    }

    // need ret
    if(!this->keyWordProcess(keyWordItemList,
                         pageloader,
                         spider_num))
    {
        respTaskVector.clear();
    }

    delete pageloader;
    pageloader = NULL;

    return respTaskVector;
}

void SeoRankRepotThread::run()
{
    CHttpGet http_get;
    //QString url = QString("http://hhgjgame006.3322.org:19999/seo_task_set_rank.php?id=") + this->id_ + QString("&rank=") + this->rank_;
    QString url = QString("http://www.baidu.com");
    qDebug() << "SeoRankReport:" << url;
    qDebug()<<"The id is "<<this->id_;
    qDebug()<<"The rand is "<<this->rank_;
    //system("pause");
    http_get.doDownload(QUrl(url));
}
