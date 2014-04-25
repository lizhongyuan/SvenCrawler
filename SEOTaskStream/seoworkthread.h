#ifndef SEOWORKTHREAD_H
#define SEOWORKTHREAD_H

#include <QThread>

#include <QSettings>
#include <QMutex>
#include <QtDebug>
#include <QWaitCondition>
#include <vector>
#include <queue>
#include"gen-cpp/octopus_crawler_types.h"
#include"gen-cpp/OctopusProxyService.h"
#include"gen-cpp/octopus_crawler_constants.h"
#include"bot_client.h"
#include "manager/csinglecraw.h"
#include<QWaitCondition>
#include"QSettings"

#include"boost/thread.hpp"

namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {
using namespace net;
using namespace std;

class SEOWorkThread : public QThread
{
    Q_OBJECT
public:
    //explicit SEOWorkThread(QObject *parent = 0);
    SEOWorkThread(net::BotMessageHandler* octopusServerConnPtr,
                  QSettings*              confSettingPtr,
                  queue<BotMessage>&      download_queue,
                  queue<BotMessage>&      upload_queue,
                  QWaitCondition&         download_cond,
                  QWaitCondition&         upload_cond):
    {
    }

    void run();

    void SEOprocess();

    void init();

signals:

public slots:

private:
    net::BotMessageHandler* octopusServerConnPtr_;
    QSettings*              confSettingPtr_;
    queue<BotMessage>&      download_queue_;
    queue<BotMessage>&      upload_queue_;
    QWaitCondition&         download_cond_;
    QWaitCondition&         upload_cond_;

    QMutex  workMutex_;
    QMutex  ioMutex_;

    CSingleCraw*  csingleCraw;
};

}}}};

#endif // SEOWORKTHREAD_H
