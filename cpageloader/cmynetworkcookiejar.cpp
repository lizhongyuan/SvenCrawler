#include "cmynetworkcookiejar.h"

CMyNetworkCookieJar::CMyNetworkCookieJar(QObject *parent) :
    QNetworkCookieJar(parent)
{
}

void CMyNetworkCookieJar::Copy(const CMyNetworkCookieJar * other) {
  if (other) {
    this->setAllCookies(other->allCookies());
  }
}
