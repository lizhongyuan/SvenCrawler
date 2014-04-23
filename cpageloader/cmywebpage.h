#ifndef CMYWEBPAGE_H
#define CMYWEBPAGE_H

#include <QtWebKit/QWebPage>
#include <QtCore>

class CMyWebPage : public QWebPage {
public:
  CMyWebPage();
  QString GetUserAgent();
  void SetUserAgent(QString user_agent);

protected:
  QString userAgentForUrl(const QUrl & url) const;
  void javaScriptAlert(QWebFrame *originatingFrame, const QString &msg);
  bool javaScriptConfirm(QWebFrame *originatingFrame, const QString &msg);
  bool javaScriptPrompt(QWebFrame *originatingFrame, const QString &msg, const QString &defaultValue, QString *result);

private:
  // dynamic user agent list;
  static QList<QString> * m_user_agent_list;
  QString m_user_agent;
};

#endif // CMYWEBPAGE_H
