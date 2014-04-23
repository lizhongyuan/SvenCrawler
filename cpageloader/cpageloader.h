#ifndef CPAGELOADER_H
#define CPAGELOADER_H

#include "cpageloader.h"
//#include "cmynetworkaccessmanager.h"
#include "cpageloader/cmynetworkaccessmanage.h"
#include "cpageloader/cmynetworkcookiejar.h"
#include "cmywebpage.h"

// #include <QtCore>
#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QEventLoop>
#include <QObject>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>

class CPageLoader : public QObject
{
  Q_OBJECT
public:
  explicit CPageLoader(QObject *parent = 0, QWidget* parent_widget = 0);
  ~CPageLoader();
  void Get(const QUrl url, QMap<QString, QString> http_header = QMap<QString, QString>(), int retry_times = 3); // 用Get方式载入页面。
  void EvaluateJavaScript(QString js); // 执行JavaScript代码
  void SetWaitTime(int wait_time = 20000); // 设置下载等待时间，毫秒。
  void Show(bool is_show);  // 是否显示浏览器窗口
  void SetIsLoadImage(bool is_load); // 是否加载图片
  void SetIsOpenNewWindow(bool is_open); // 点击链接的时候，是否打开新窗口。
  QWebView * GetWebView();
  QWebElement GetWebElement();
  bool IsDownLoadSuccess();
  QString GetUserAgent();
  void SetUserAgent(QString user_agent);
  void Sleep(int msec);

private:
  void AbsoluteUrl(const QWebElement &parentElement, const QUrl & currentUrl);  // 将相对URL转换为绝对URL

private slots:
  void Finished(bool b);   // 页面载入完成。
  void CheckEventloop();   // 检查eventloop状态
  void TimeOut();  // 页面载入超时。
  void LinkClick(const QUrl & url);  // 点击超链接
  void QuitSleepEventLoop();

private:
  QWebView *m_webview; // webkit浏览器的窗体
  int m_time_used;  // 载入页面的时间
  QUrl m_url; // 要载入的url
  QEventLoop m_eventloop; // 事件循环，必须等待载入完成或者载入超时才退出
  int m_wait_time; // 载入超时的时间
  CMyWebPage m_mywebpage; // 重载webpage，用来变换UserAgent
  QTimer *m_timer; // 超时定时器
  QTimer *m_check_eventloop_timer; // 检查eventloop的定时器
  int m_last_op_time; // 上次加载页面的时间
  QElapsedTimer m_elapsed_timer; // 页面载入时间计时器
  int m_lastCleanCacheTime; // 上次清除缓存的时间
  int m_cleanInterval; // 清理缓存的时间间隔
  bool m_is_show_window; // 是否显示浏览器窗口
  bool m_is_download_success;
  int m_check_eventloop_count;
  bool m_is_open_new_window; // 点击链接的时候，是否打开新窗口。
  CMyNetworkCookieJar *m_cookie_jar;

  QTimer m_sleep_timer;
  QEventLoop m_sleep_eventloop;

public:
  CMyNetworkAccessManager m_mynetworkAccessManager; // webview使用的NetworkAccessManager，控制proxy和cache的加载。

  //signals:
  //public slots:
};

class CPageLoaderSingleton {
public:
  static CPageLoader * GetSinglePageLoader(QObject *parent = 0, QWidget* parent_widget = 0);

private:
  static CPageLoader * m_pageloader;
  static int m_used_count;
};

#endif // CPAGELOADER_H
