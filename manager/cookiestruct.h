#ifndef COOKIESTRUCT_H
#define COOKIESTRUCT_H

#include<QString>
#include<QtNetwork>
#include<QList>

using namespace std;

struct cookieStruct
{
  QString userAgent;
  QList<QNetworkCookie> networkCookieList;
  //std::string uploadCookieStr;
  QString uploadCookieStr;
};

#endif // COOKIESTRUCT_H
