#ifndef GETBOTMSGTHREAD_H
#define GETBOTMSGTHREAD_H

#include <QSettings>
#include <QThread>
#include <QMutex>
#include <QtDebug>
#include <vector>
#include <queue>
//#include"gen-cpp/octopus_crawler_types.h"
//#include"gen-cpp/OctopusProxyService.h"
#include"gen-cpp/octopus_crawler_constants.h"
#include<QWaitCondition>
#include"QSettings"
#include"boost/thread.hpp"

//#include"bot_client.h"
#include "gen-cpp/net.h"


namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {
using namespace std;

class GetBotMsgThread : public QThread
{
    Q_OBJECT
public:
    GetBotMsgThread(net::BotMessageHandler* octopusServerConnPtr,
                    QSettings*              confSettingPtr,
                    vector<BotMessage>      reqTaskVector,
                    queue<BotMessage>&      download_queue,
                    QWaitCondition&         download_cond):
        octopusServerConnPtr_(octopusServerConnPtr), confSettingPtr_(confSettingPtr),
        reqTaskVector_(reqTaskVector), download_queue_(download_queue), download_cond_(download_cond)
    {
    }

    ~GetBotMsgThread();

    int
    getTask();

    void run();

    void moveToQueue();

signals:

public slots:

public:
    net::BotMessageHandler* octopusServerConnPtr_;
    QSettings*  confSettingPtr_;
    vector<BotMessage>  reqTaskVector_;
    queue<BotMessage>&  download_queue_;
    QWaitCondition&     download_cond_;

    QMutex  getMutex_;
    QMutex  ioMutex_;
};


}}}};
#endif // GETBOTMSGTHREAD_H
