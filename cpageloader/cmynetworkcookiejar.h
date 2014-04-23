#ifndef CMYNETWORKCOOKIEJAR_H
#define CMYNETWORKCOOKIEJAR_H

#include <QNetworkCookieJar>

class CMyNetworkCookieJar : public QNetworkCookieJar
{
  Q_OBJECT
public:
  explicit CMyNetworkCookieJar(QObject *parent = 0);
  void Copy(const CMyNetworkCookieJar * other);

signals:

public slots:

};

#endif // CMYNETWORKCOOKIEJAR_H
