#include "csinglecraw.h"
#include "cpageloader/chttpget.h"
#include "cpageloader/cpageloader.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTest>
#include "./conf/csqlhelper.h"

#include"stdlib.h"

CSingleCraw::CSingleCraw(QObject *parent) : QObject(parent) {
  connect(&(this->timer_), SIGNAL(timeout()), this, SLOT(QuitEventLoop()));
  connect(&(this->http_get_task_timer_), SIGNAL(timeout()), this, SLOT(HttpGetSeoTask()));
  this->HttpGetSeoTask();
  this->http_get_task_timer_.start(60000);
}

void CSingleCraw::Start(int spider_num)
{
  this->BaiduSEOTest(spider_num);
}

/*
void
CSingleCraw::Start(vector<SimulatorTask>& taskVector, int spider_num)
{
  this->BaiduSEOTest(taskVector, spider_num);
}
*/

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
 *
 */
void CSingleCraw::Sleep(int msec)
{
  // 暂停msec毫秒
  this->timer_.setSingleShot(true);
  this->timer_.start(msec);
  this->eventloop_.exec();
}


/*
QList<KeyWordItem>
CSingleCraw::getTaskWordList(SimulatorTask& curTask,
                             bool&          is_read_done)
*/


QList<KeyWordItem>
CSingleCraw::getTaskWordList(QStringList&  key_word_lines,
                             bool&         is_read_done)
{
    double day_week_rate[10] = {0, 0.16, 0.155, 0.152, 0.151, 0.15, 0.135, 0.133};
    int day_of_week = QDateTime::currentDateTime().date().dayOfWeek();
    qDebug() << "Today is:" << day_of_week << "Rate:" << day_week_rate[day_of_week];

    QList<KeyWordItem> word_list;
    for (int i = 0; i < key_word_lines.count(); i++)
    {
      if (key_word_lines[i] == "###done###")
      {
        is_read_done = true;
        break;
      }
      QStringList tmp = key_word_lines[i].split("\t");
      KeyWordItem kwi;
      if (tmp.count() >= 4)
      {
        kwi.id         = tmp[0];
        kwi.key_word   = tmp[1];
        kwi.target_url = tmp[2];
        kwi.baidu_index= tmp[3];
        kwi.ever_top   = tmp[4];
        kwi.cur_rank   = tmp.at(5).toInt();
        // qDebug() << kwi.key_word << kwi.baidu_index;
        int baidu_index_chu_10 = kwi.baidu_index.toInt() * day_week_rate[day_of_week];
        for (int ki = 0; ki < baidu_index_chu_10; ki++)
        {
          word_list.append(kwi);
        }
      }
    }
    return word_list;
}

/*
QList<KeyWordItem>
getTaskList(vector<SimulatorTask>  taskVector,
            bool&                  is_read_done)
{
  double day_week_rate[10] = {0, 0.16, 0.155, 0.152, 0.151, 0.15, 0.135, 0.133};

  int day_of_week = QDateTime::currentDateTime().date().dayOfWeek();
  qDebug() << "Today is:" << day_of_week << "Rate:" << day_week_rate[day_of_week];

  QList<KeyWordItem> word_list;

  //for (int i = 0; i < key_word_lines.count(); i++)
  for(vector<SimulatorTask> iter = taskVector.begin(), iter!= taskVector.end(); iter++)
  {
    if (key_word_lines[i] == "###done###")
    {
      is_read_done = true;
      break;
    }
    QStringList tmp = key_word_lines[i].split("\t");
    KeyWordItem kwi;
    if (tmp.count() >= 4)
    {
      kwi.id         = tmp[0];
      kwi.key_word   = tmp[1];
      kwi.target_url = tmp[2];
      kwi.baidu_index= tmp[3];
      kwi.ever_top   = tmp[4];
      kwi.cur_rank   = tmp.at(5).toInt();
      // qDebug() << kwi.key_word << kwi.baidu_index;
      int baidu_index_chu_10 = kwi.baidu_index.toInt() * day_week_rate[day_of_week];
      for (int ki = 0; ki < baidu_index_chu_10; ki++)
      {
        word_list.append(kwi);
      }
    }
  }
  return word_list;
}
*/

/*
 *
 */
//void
//CSingleCraw::resetPageloader(CPageLoader*& pageLoaderPtr)
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
CSingleCraw::simulateInputKeyWord(QString key_word,
                                  CPageLoader*& pageloader,
                                  QWebElement& input)
{
  for (int fi = 0; fi < key_word.length(); )
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
    for (int word_i = fi; word_i < key_word.length() && word_i < fi + word_len; word_i++)
    {
      seg_word += key_word[word_i];
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
CSingleCraw::getSpanElem(QWebElement& span_elem, QWebElement& curColl)
{
  bool isExist = false;
  if (span_elem.isNull())
  {
    span_elem = curColl.findFirst("div.f13 span.g"); //百度快照前面的
    isExist = true;
  }
  if (span_elem.isNull())
  {
    span_elem = curColl.findFirst("font[size='-1']");
    isExist = true;
  }
  if (span_elem.isNull())
  {
    isExist = false;
  }
  return isExist;
}

void
CSingleCraw::processSpanElem(QString& keyWordRank,
                             QWebElement& span_elem,
                             QWebElement& a_elem,
                             int& scroll_height,
                             int& window_height,
                             int& scroll_bar_maximun,
                             QString target_url,
                             CPageLoader*& pageloader,
                             bool& is_click,
                             bool& is_mousedown_ganji,
                             bool& is_prepare_ganji)
{
  QString span_str = span_elem.toPlainText().trimmed();
  target_url = target_url.replace("http://", "");
  int x = a_elem.geometry().left() + (rand() % a_elem.geometry().width());
  int y = a_elem.geometry().top()  + (rand() % a_elem.geometry().height()) - scroll_height;

  if (span_str.indexOf(target_url) >= 0 && is_mousedown_ganji == false && (!InBlackList(span_str))) {
    is_click = true;
    is_prepare_ganji = true;
  }

  if (is_click == true)
  {
    /*
    qDebug() << "Link Pos:" << x << y
             << "Window Height:" << window_height
             << "Scroll Bar Maximum" << scroll_bar_maximun;
    */
    while (y > window_height - (rand() % 100 + 30))
    {
      int rand_scroll = 100 + rand() % 2;

      if (scroll_height + rand_scroll < scroll_bar_maximun) // in the mid
      {
        y -= rand_scroll;               //向下移动rand_scroll
        scroll_height += rand_scroll;   // same as above
        pageloader->GetWebView()->page()->mainFrame()->scroll(0, rand_scroll);
      }
      else                                                  // to the end
      {
        int next_scroll = scroll_bar_maximun - scroll_height;
        y -= next_scroll;
        scroll_height += next_scroll;
        pageloader->GetWebView()->page()->mainFrame()->scroll(0, scroll_height);
      }
      this->Sleep(rand() % 200 + 400);
    }
    this->Sleep(rand() % 500 + 500);


    QString refuse_url = "";
    QStringList url_tmp_list = span_str.replace("...", " ").trimmed().split(" ");
    if (url_tmp_list.count() >= 1)
    {
      refuse_url = QUrl("http://" + url_tmp_list[0]).host();
    }

    qDebug() << "span_str:" << span_str << " : " << url_tmp_list;
    pageloader->m_mynetworkAccessManager.SetRefuseUrl(refuse_url);
    qDebug() << "Link Pos scrolled:" << x << y;
    QTest::mouseEvent(QTest::MouseClick, pageloader->GetWebView(), Qt::LeftButton, Qt::NoModifier, QPoint(x, y), -1);
    this->rank_ = keyWordRank;
    this->Sleep(rand() % 1000 + 2000);

    if (is_prepare_ganji == true)
    {
      SeoRankRepotThread seo_rank_report_thread;
      seo_rank_report_thread.id_   = this->id_;
      //seo_rank_report_thread.rank_ = a_coll[ai].attribute("id");
      seo_rank_report_thread.rank_ = this->rank_;
      seo_rank_report_thread.run();

      this->Sleep(rand() % 500 + 1000);
      is_mousedown_ganji = true;
    }
  }
}

void
CSingleCraw::gotoNextPage(int page_idx,
                          CPageLoader*& pageloader,
                          QWebElement& dom,
                          int& window_height,
                          int& scroll_height,
                          int& scroll_bar_maximun)
{
    qDebug() << "Target url not found in current page index:" << page_idx;
    QWebElementCollection page_coll = dom.findAll("*#page a");        // make sure 3: p[id=page] a
    //QWebElementCollection page_coll = dom.findAll("p[id=page] a");        // make sure 3: p[id=page] a
    for (int pidx = 0; pidx < page_coll.count(); pidx++)
    {
      QWebElement a_elem = page_coll[pidx];
      if (a_elem.toPlainText().trimmed() == QString::number(page_idx + 1))
      {
        qDebug() << "Prepare to load page index:" << page_idx + 1;
        int x = a_elem.geometry().left() + (rand() % a_elem.geometry().width());
        int y = a_elem.geometry().top()  + (rand() % a_elem.geometry().height()) - scroll_height;
        qDebug() << "Target Page Btn Pos:" << x << y
                 << "Window Height:" << window_height
                 << "Scroll Bar Maximum" << scroll_bar_maximun;
        while (y > window_height - (rand() % 10 + 40))
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
                                 QString target_url,
                                 int& max_page_load,
                                 int& scroll_height)
{
  for (int page_idx = 1; page_idx <= max_page_load && is_mousedown_ganji == false; page_idx++)
  {
    QWebElement dom = pageloader->GetWebElement();
    scroll_height = 0;
    qDebug() << " --> Now At Page:" << page_idx;
    int window_height = pageloader->GetWebView()->page()->mainFrame()->geometry().height();
    int scroll_bar_maximun = pageloader->GetWebView()->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);

    // get all the blocks
    QWebElementCollection a_coll = dom.findAll("div.result");       // make sure1
    for (int ai = 0; ai < a_coll.count(); ai++)
    {
      QString keyWordRank = a_coll[ai].attribute("id");
      QWebElement a_elem = a_coll[ai].findFirst("a");
      QWebElement span_elem = a_coll[ai].findFirst("font[size='-1'] span.g");       //make sure2

      if(!this->getSpanElem(span_elem, a_elem))
        continue;

      /*
       * 目前的条件, span_elem的content ,depends on fiv.f13 span.g
       */
      bool is_click = false;
      bool is_prepare_ganji = false;

      this->processSpanElem(keyWordRank,
                            span_elem,
                            a_elem,
                            scroll_height,
                            window_height,
                            scroll_bar_maximun,
                            target_url,
                            pageloader,
                            is_click,
                            is_mousedown_ganji,
                            is_prepare_ganji);


      // 4/5的可能
      if (is_mousedown_ganji == true)
      {
        if (rand() % 100 < 80)
        {
          break;
        }
      }
    }

    /*
     * ---------------------------------------------------
     * this page doesn't have ganji's reference, goto the next
     * ---------------------------------------------------
     */
    if (is_mousedown_ganji == false && page_idx + 1 <= max_page_load)
    {
      gotoNextPage(page_idx,
                   pageloader,
                   dom,
                   window_height,
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

void
CSingleCraw::keyWordProcess(QList<KeyWordItem>& word_list,
                            CPageLoader*& pageloader,
                            int spider_num)
{
  srand(unsigned(time(NULL)));
  uint pre_time = time(NULL);
  while (time(NULL) - pre_time < 400)
  {
    int wi = rand() % word_list.count();
    //QString id       = word_list[wi].id;
    this->id_       = word_list[wi].id;
    QString key_word = word_list[wi].key_word;
    QString target_url = word_list[wi].target_url;

    if (key_word == "" || target_url == "") {
      qDebug() << "Warning: key_word or target_url is NULL.";
      this->Sleep(1000);
      continue;
    }
    qDebug() << "Current Key Word:" << key_word << "Target Url:" << target_url;

    QElapsedTimer elapsed_timer;
    elapsed_timer.restart();

    pageloader->Get(QUrl("http://www.baidu.com/"));

    // 百度首页 输入第一个关键词
    QWebElement dom = pageloader->GetWebElement();
    if (dom.toPlainText().indexOf("使用百度前必读") == -1) {
      qDebug() << "Can not open www.baidu.com";
      this->Sleep(3000);
      continue;
    }
    QWebElement input = dom.findFirst("input#kw1");
    if (input.geometry().width() < 200 || input.geometry().height() < 10) {
      qDebug() << "Fatal Error: Strange kw input.";
      this->Sleep(60000);
      continue;
    }

    this->getAndClickInputPos(pageloader,
                              input);

    this->Sleep(rand() % 500 + 2000);

    this->simulateInputKeyWord(key_word,
                               pageloader,
                               input);

    this->Sleep(rand() % 500 + 300);

    this->getAndClickButton(dom,
                            pageloader);

    qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "输入关键词：" << key_word << " Now At:" << pageloader->GetWebView()->url().toEncoded();

    this->Sleep(rand() % 3000 + 5000);

    dom = pageloader->GetWebElement();
    if (dom.toPlainText().indexOf("此内容系百度根据您的指令自动搜索的结果") == -1) {
      qDebug() << "Incomplete page. skip.";
      this->Sleep(3000);
      continue;
    }

    bool is_mousedown_ganji = false;
    int scroll_height = 0;
    int max_page_load = 2;

    this->getContentFromPages(is_mousedown_ganji,
                              pageloader,
                              target_url,
                              max_page_load,
                              scroll_height);

    if (is_mousedown_ganji == false) {
      qDebug() << "Warning: Could not find target_url.";
    }

    //void waitFunction(QElapsedTimer& elapsed_timer)
    this->waitFunction(elapsed_timer,
                          word_list,
                          spider_num);
  }
}

/*
 * changed by lizhongyuan,
 * the function
 */
void CSingleCraw::BaiduSEOTest(int spider_num)
{
  //CPageLoader *pageloader = NULL;
  while (true)
  {
    this->mutex_.lock();
    QString key_word_data = this->seo_task_list_;
    this->mutex_.unlock();

    if (key_word_data.trimmed() == "###done###")
    {
      qDebug() << "No task right now. sleep 70s";
      this->Sleep(70000);
      continue;
    }

    QStringList key_word_lines = key_word_data.split("\n");
    bool is_read_done = false;

    /*
     * build the word_list
     */
    QList<KeyWordItem> word_list = this->getTaskWordList(key_word_lines,
                                                         is_read_done);
    qDebug() << "word_list count():" << word_list.count();
    if (is_read_done == false) {
      qDebug() << "Could not finish reading key word list.";
      this->Sleep(3000);
      continue;
    }
    if (word_list.count() == 0) {
      qDebug() << "Empty key word list.";
      this->Sleep(3000);
      continue;
    }

    // get a pageloader
    // this->resetPageloader(pageloader);
    CPageLoader* pageloader = CSingleCraw::pageLoaderFactory();
    if(pageloader == NULL)
    {
      continue;
    }

    this->keyWordProcess(word_list,
                         pageloader,
                         spider_num);

    delete pageloader;
    pageloader = NULL;
    // need delete the pageloader
  }
}



void SeoRankRepotThread::run()
{
    CHttpGet http_get;
    //QString url = QString("http://hhgjgame006.3322.org:19999/seo_task_set_rank.php?id=") + this->id_ + QString("&rank=") + this->rank_;
    QString url = QString("http://www.baidu.com");
    qDebug() << "SeoRankReport:" << url;
    qDebug()<<"The id is "<<this->id_;
    qDebug()<<"The rand is "<<this->rank_;
    system("pause");
    http_get.doDownload(QUrl(url));
}
