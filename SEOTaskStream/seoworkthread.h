#ifndef SEOWORKTHREAD_H
#define SEOWORKTHREAD_H

#include <QThread>

class SEOWorkThread : public QThread
{
    Q_OBJECT
public:
    explicit SEOWorkThread(QObject *parent = 0);

signals:

public slots:

};

#endif // SEOWORKTHREAD_H
