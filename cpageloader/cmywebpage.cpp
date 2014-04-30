#include "cmywebpage.h"
//#include "../conf/cconf.h"
#include"conf/cconf.h"
//#include"E:/workspaces/qt_workspace/SEOcrawler/conf/cconf.h"
#include<QtDebug>

QList<QString> * CMyWebPage::m_user_agent_list = NULL;

CMyWebPage::CMyWebPage() {
  QWebPage();
  if (this->m_user_agent_list == NULL) {
    this->m_user_agent_list = new QList<QString>();
    // 初始化随机种子，为了随机变换UserAgent
    QTime time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    // 读取user-agent文件。
    QFile file(CConf::GetConfPath("user_agent.txt"));
    if (file.open(QIODevice::ReadOnly) == true) {
      while (!file.atEnd()) {
        QByteArray tmp = file.readLine().trimmed();
        if (tmp[0] == '#') {
          continue;
        }
        if (tmp.length() != 0) {
          this->m_user_agent_list->append(tmp);
        }
      }
      file.close();
    }
    else
    {
      qDebug() << "Error:CMyWebPage::CMyWebPage(): Cannot open 'user_agent.txt'";
    }
  }
  if (this->m_user_agent_list->size() > 0) {
    int rand_index = qrand() % this->m_user_agent_list->size();
    this->m_user_agent = (*this->m_user_agent_list)[rand_index];
  }
}

// 重写，使之能够随机变换UserAgent
QString CMyWebPage::userAgentForUrl(const QUrl &url) const {
  if (this->m_user_agent != "") {
    // qDebug() << this->user_agent;
    return m_user_agent;
  }
  return "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)";
}

// 避免webkit弹出窗口，阻断当前运行过程。
void CMyWebPage::javaScriptAlert(QWebFrame *originatingFrame, const QString &msg) {
  return;
}

bool CMyWebPage::javaScriptConfirm(QWebFrame *originatingFrame, const QString &msg) {
  return false;
}

bool CMyWebPage::javaScriptPrompt(QWebFrame *originatingFrame, const QString &msg, const QString &defaultValue, QString *result) {
  return false;
}

QString CMyWebPage::GetUserAgent() {
  return this->m_user_agent;
}

void CMyWebPage::SetUserAgent(QString user_agent) {
  this->m_user_agent = user_agent;
}
