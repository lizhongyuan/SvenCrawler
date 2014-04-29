#ifndef SEOWORKTHREAD_H
#define SEOWORKTHREAD_H

#include <QThread>

#include <QSettings>
#include <QMutex>
#include <QtDebug>
#include <QWaitCondition>
#include <vector>
#include <queue>
#include"gen-cpp/octopus_crawler_constants.h"
#include "manager/csinglecraw.h"
#include<QWaitCondition>
#include"QSettings"
#include"boost/thread.hpp"

#include"bot_client.h"


namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {
using namespace net;
using namespace std;


class SEOWorkThread : public QThread
{
    Q_OBJECT
public:
    SEOWorkThread(net::BotMessageHandler* octopusServerConnPtr,
                  QSettings*              confSettingPtr,
                  queue<BotMessage>&      download_queue,
                  queue<BotMessage>&      upload_queue,
                  QWaitCondition&         download_cond,
                  QWaitCondition&         upload_cond):
        octopusServerConnPtr_(octopusServerConnPtr), confSettingPtr_(confSettingPtr),
        download_queue_(download_queue), upload_queue_(upload_queue),
        download_cond_(download_cond), upload_cond_(upload_cond)
    {
        this->csingleCraw = new CSingleCraw();
    }

    ~SEOWorkThread();

    void run();

    vector<BotMessage>  outOffQueue();
    vector<BotMessage>  SEOprocess(vector<BotMessage> reqTaskVector);

    void sendTask(vector<BotMessage> respTaskVector);

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
