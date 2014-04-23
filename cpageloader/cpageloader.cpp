#ifndef CPAGELOADER_CPP
#define CPAGELOADER_CPP

#include "cpageloader.h"

#ifndef LINUX
#include<windows.h>
#endif

#include <time.h>
//#include <unistd.h>

// #include <QtCore>
#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QEventLoop>
#include <QObject>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtNetwork/QNetworkRequest>

// public:
CPageLoader::CPageLoader(QObject *parent, QWidget* parent_widget) : QObject(parent) {
  this->m_is_download_success = true;
  this->m_webview = new QWebView(parent_widget); // 构造webview
  this->m_url = ""; // 要载入的url
  this->m_wait_time = 20000; // 默认下载等待20秒。
  this->m_time_used = 0; // 载入页面的时间
  this->m_timer = new QTimer(); // 超时定时器
  this->m_check_eventloop_timer = new QTimer(); // 检查eventloop的超时定时器
  this->m_last_op_time = time(unsigned(NULL));
  this->m_is_show_window = false; // 是否显示浏览器窗口，默认不显示
  this->m_lastCleanCacheTime = time(unsigned(NULL)); // 缓存清理时间
  this->m_cleanInterval = 3600; // 缓存清理时间间隔
  this->m_check_eventloop_count = 0;
  this->m_is_open_new_window = false;
  // 绑定事件，完成页面加载，和超时。
  connect(m_webview, SIGNAL(loadFinished(bool)), this, SLOT(Finished(bool)));
  connect(m_timer, SIGNAL(timeout()), this, SLOT(TimeOut()));
  connect(m_check_eventloop_timer, SIGNAL(timeout()), this, SLOT(CheckEventloop()));

  // 给webview设置WebPage
  this->m_mywebpage.settings()->setAttribute(QWebSettings::AutoLoadImages, false);
  this->m_mywebpage.settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
  this->m_webview->setPage(&(this->m_mywebpage));
  this->m_webview->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
  connect(m_webview->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(LinkClick(QUrl)));
  // 给webview设置NetworkAccessManager
  this->m_webview->page()->setNetworkAccessManager((QNetworkAccessManager*)(&(this->m_mynetworkAccessManager)));
  // set cookie_jar
  this->m_cookie_jar = new CMyNetworkCookieJar();
  this->m_webview->page()->networkAccessManager()->setCookieJar(this->m_cookie_jar);
  // 设置窗口大小
  this->m_webview->setGeometry(0, 0, 1024, 768);
  connect(&(this->m_sleep_timer), SIGNAL(timeout()), this, SLOT(QuitSleepEventLoop()));
}

void CPageLoader::Get(const QUrl url, QMap<QString, QString> http_header, int retry_times)
{
  // qDebug() << "-------------> Retry Times:" << retry_times;
  // 下载重试3次，每次间隔5秒
  for (int rt = 0; rt < retry_times; rt++)
  {
    this->m_last_op_time = time(unsigned(NULL));
    if (url.toString() == "about:blank" ||
        url.toString() == "http://about:blank" ||
        url.toString() == "http://")
    {
      return;
    }
    int cnt = 0;
    while (this->m_eventloop.isRunning() == true)
    {
      this->m_webview->page()->triggerAction(QWebPage::Stop);
      this->m_webview->page()->triggerAction(QWebPage::StopScheduledPageRefresh);
      this->m_eventloop.quit();
      if (cnt++ > 10000) break;
    }
    cnt = 0;
    while (this->m_check_eventloop_timer->isActive() == true) {
      this->m_check_eventloop_timer->stop();
      if (cnt++ > 10000) break;
    }
    this->m_check_eventloop_timer->start(this->m_wait_time); // 循环检查eventloop
    this->m_check_eventloop_count = 0;

    this->m_is_download_success = true;
    this->m_url = url;
    // this->CheckCache();
    // 定时器和计时器
    this->m_timer->setSingleShot(true);
    this->m_timer->start(this->m_wait_time);
    this->m_elapsed_timer.restart();

    // 创建Request，用于加载页面，并附加http header
    QNetworkRequest request;
    request.setPriority(QNetworkRequest::HighPriority);
    request.setUrl(this->m_url);
    QMap<QString, QString>::iterator it;
    for (it = http_header.begin(); it != http_header.end(); it++) {
      request.setRawHeader(it.key().toAscii(), it.value().toAscii());
      // request.setRawHeader("referer", "http://bj.58.com/");
    }
    // 加载页面
    qDebug() << "CPageLoader::Get() Loading Url: " << request.url().toString();
    this->m_webview->load(request);
    qDebug() << "CPageLoader::Get() Sync Loading Page Url: " << request.url().toString();
    // 是否显示浏览器窗口
    if (true == this->m_is_show_window) {
      this->m_webview->show();
    } else {
      this->m_webview->hide();
    }
    qDebug() << "CPageLoader::Get() eventloop exec.";
    this->m_eventloop.exec();
    qDebug() << "CPageLoader::Get() eventloop quit.";
    if (this->m_check_eventloop_timer->isActive() == true) {
      this->m_check_eventloop_timer->stop();
    }
    // 下载失败，sleep 5秒，然后重试。
    if (this->m_is_download_success == false) {
#ifdef LINUX
      sleep(5);
#else
      Sleep(5);
#endif
      continue;
    } else {
      break;
    }
  }
}

void CPageLoader::EvaluateJavaScript(QString js) {
  if (js.trimmed() == "") {
    return;
  }
  // 定时器和计时器
  this->m_timer->setSingleShot(true);
  this->m_timer->start(this->m_wait_time);
  this->m_elapsed_timer.restart();
  int cnt = 0;
  while (this->m_check_eventloop_timer->isActive() == true) {
    this->m_check_eventloop_timer->stop();
    if (cnt++ > 10000) break;
  }

  this->m_check_eventloop_timer->start(this->m_wait_time); // 循环检查eventloop
  this->m_check_eventloop_count = 0;

  QVariant result = this->m_webview->page()->mainFrame()->evaluateJavaScript(js);
  // qDebug() << result.toString();
  this->m_eventloop.exec();
  if (this->m_check_eventloop_timer->isActive() == true) {
    this->m_check_eventloop_timer->stop();
  }
}

void CPageLoader::SetWaitTime(int wait_time) {
  this->m_wait_time = wait_time;
}

void CPageLoader::Show(bool is_show) {
  this->m_is_show_window = is_show;
}

void CPageLoader::SetIsLoadImage(bool is_load) {
  this->m_webview->page()->settings()->setAttribute(QWebSettings::AutoLoadImages, is_load);
}

void CPageLoader::SetIsOpenNewWindow(bool is_open) {
  this->m_is_open_new_window = is_open;
}

QWebView * CPageLoader::GetWebView() {
  return this->m_webview;
}

QWebElement CPageLoader::GetWebElement() {
  return this->m_webview->page()->mainFrame()->documentElement();
}

bool CPageLoader::IsDownLoadSuccess() {
  return this->m_is_download_success;
}

QString CPageLoader::GetUserAgent() {
  CMyWebPage * mywebpage = (CMyWebPage *)this->m_webview->page();
  if (mywebpage != NULL) {
    return mywebpage->GetUserAgent();
  }
  return "";
}

void CPageLoader::SetUserAgent(QString user_agent) {
  CMyWebPage * mywebpage = (CMyWebPage *)this->m_webview->page();
  if (mywebpage != NULL) {
    return mywebpage->SetUserAgent(user_agent);
  }
}

void CPageLoader::Sleep(int msec) {
  // 暂停msec毫秒
  this->m_sleep_timer.setSingleShot(true);
  this->m_sleep_timer.start(msec);
  this->m_sleep_eventloop.exec();
}

void CPageLoader::AbsoluteUrl(const QWebElement &parentElement, const QUrl & currentUrl) {
  QWebElement element = parentElement.firstChild();
  while (!element.isNull()) {
    // 将相对URL转换为绝对URL
    if (element.tagName() == "a" || element.tagName() == "A") {
      if (element.attribute("href").toLower().startsWith("http://") == false &&
          element.attribute("href").toLower().startsWith("javascript") == false) {
        QUrl relativeUrl(element.attribute("href"));
        if (relativeUrl.toString() != "") {
          QUrl absoluteUrl = currentUrl.resolved(relativeUrl);
          element.setAttribute("href", absoluteUrl.toString());
        }
      }
    }
    this->AbsoluteUrl(element, currentUrl);
    element = element.nextSibling();
  }
}

CPageLoader::~CPageLoader()
{
  for (int i = 0; i < 10; i++) {
    this->m_webview->page()->triggerAction(QWebPage::Stop);
    this->m_webview->page()->triggerAction(QWebPage::StopScheduledPageRefresh);
  }
  if (this->m_webview != NULL) {
    delete this->m_webview;
    qDebug() << "CPageLoader::~CPageLoader() delete this->m_webview.";
  }
  if (this->m_timer != NULL) {
    delete this->m_timer;
    qDebug() << "CPageLoader::~CPageLoader() delete this->m_timer.";
  }
  if (this->m_check_eventloop_timer != NULL) {
    delete this->m_check_eventloop_timer;
    qDebug() << "CPageLoader::~CPageLoader() delete this->m_check_eventloop_timer.";
  }
}

// private slots:
void CPageLoader::Finished(bool b) {
  QString cur_url = this->m_webview->url().toString();
  qDebug() << "CPageLoader::Finished() Current Url:" << cur_url;
  if (cur_url == "about:blank" || cur_url == "http://about:blank") {
    return;
  }
  if (this->m_timer->isActive() == true) {
    this->m_timer->stop();
  }
  this->m_time_used = this->m_elapsed_timer.elapsed();
//  if (this->m_time_used == 0 && this->m_eventloop.isRunning() == false) {
//    int times = 0;
//    while (this->m_eventloop.isRunning() == false) {
//      times++;
//      if (times > 3) break;
//      if (this->m_eventloop.isRunning() == true) {
//        this->m_eventloop.quit();
//        break;
//      }
//      sleep(1);
//    }
//  }
  int cnt = 0;
  while (this->m_eventloop.isRunning() == true) {
    this->m_eventloop.quit();
    if (cnt++ > 10000) break;
  }
  qDebug() << "CPageLoader::finished() Success:" << b << "UseTime:" << m_time_used << "ms";
}

void CPageLoader::CheckEventloop() {
  int now_time = time(unsigned(NULL));
  if (now_time - this->m_last_op_time >= (this->m_wait_time / 1000)) {
    if (this->m_eventloop.isRunning() == true) {
      qDebug() << "CPageLoader::CheckEventloop() eventloop exec for a long time, force quit.";
      int cnt = 0;
      while (this->m_eventloop.isRunning() == true) {
        this->m_eventloop.quit();
        if (cnt++ > 10000) break;
      }
    } else {
      qDebug() << "CPageLoader::CheckEventloop() eventloop is ok.";
      int cnt = 0;
      while (this->m_eventloop.isRunning() == true) {
        this->m_eventloop.quit();
        if (cnt++ > 10000) break;
      }
    }
  }
  if (this->m_check_eventloop_count++ > 10) {
    qDebug() << "Fatal Error: Can not finish Get() or EvaluateJavaScript() Function.";
    fflush(stdout);
    exit(100);
  }
}

// 载入超时, 停止载入页面
void CPageLoader::TimeOut() {
  this->m_is_download_success = false;
  qDebug() << "CPageLoader::timeOut() LoadingPageTimeOut!";
  for (int i = 0; i < 3; i++) {
    this->m_webview->page()->triggerAction(QWebPage::Stop);
    this->m_webview->page()->triggerAction(QWebPage::StopScheduledPageRefresh);
  }
  qDebug() << "CPageLoader::timeOut() StopPageLoading!";
  if (this->m_eventloop.isRunning() == true) {
    this->Finished(false);
  }
  // finished(false);  // 不用调用finished，triggerAction会触发connect
}

void CPageLoader::LinkClick(const QUrl & url) {
  QMap<QString, QString> http_header;
  http_header["Referer"] = this->m_webview->url().toEncoded();
  if (url.toEncoded().indexOf("http://www.baidu.com/s?wd=") >= 0) {
    this->Sleep(1000);
    this->Get(url, http_header);
  }
  if (url.toEncoded().indexOf("http://www.baidu.com/link?url=") >= 0) {
    CPageLoader * newpageloader = new CPageLoader;
    CMyNetworkCookieJar * cookie_jar = new CMyNetworkCookieJar();
    cookie_jar->Copy(this->m_cookie_jar);
    newpageloader->GetWebView()->page()->networkAccessManager()->setCookieJar(cookie_jar);
    qDebug() << "Copy Cookie:" << newpageloader->GetWebView()->page()->networkAccessManager()->cookieJar()->cookiesForUrl(QUrl("http://www.baidu.com"));
    newpageloader->m_mynetworkAccessManager.SetRefuseUrl(
            this->m_mynetworkAccessManager.refuse_url_
          );
    newpageloader->SetWaitTime(5000);
    newpageloader->Show(true);
    newpageloader->SetIsLoadImage(true);
    newpageloader->SetUserAgent(this->GetUserAgent());
    newpageloader->Get(url, http_header, 1);
    delete newpageloader;
  }
}

void CPageLoader::QuitSleepEventLoop() {
  this->m_sleep_eventloop.quit();
}

// CPageLoaderSingleton
CPageLoader * CPageLoaderSingleton::m_pageloader = NULL;
int CPageLoaderSingleton::m_used_count = 0;
CPageLoader * CPageLoaderSingleton::GetSinglePageLoader(QObject *parent, QWidget* parent_widget) {
  if (CPageLoaderSingleton::m_pageloader == NULL) {
    CPageLoaderSingleton::m_pageloader = new CPageLoader(parent, parent_widget);
  }
  if (CPageLoaderSingleton::m_used_count++ > 10) {
    CPageLoaderSingleton::m_used_count = 0;
    delete CPageLoaderSingleton::m_pageloader;
    CPageLoaderSingleton::m_pageloader = new CPageLoader(parent, parent_widget);
  }
  return CPageLoaderSingleton::m_pageloader;
}

#endif //CPAGELOADER_CPP
