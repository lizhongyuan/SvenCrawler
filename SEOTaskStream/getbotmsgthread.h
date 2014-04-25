﻿#ifndef GETBOTMSGTHREAD_H
#define GETBOTMSGTHREAD_H

#include <QSettings>
#include <QThread>
#include <QMutex>
#include <QtDebug>
#include <vector>
#include <queue>
#include"gen-cpp/octopus_crawler_types.h"
#include"gen-cpp/OctopusProxyService.h"
#include"gen-cpp/octopus_crawler_constants.h"
#include"bot_client.h"
#include<QWaitCondition>
#include"QSettings"

#include"boost/thread.hpp"

namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {
using namespace net;
using namespace std;


class GetBotMsgThread : public QThread
{
    Q_OBJECT
public:
    //net::BotMessageHandler  octopus_server_conn_;  ///< 与bot server的连接
    //QSettings*  confSettingPtr;
    //explicit getBotMsgThread(QObject *parent = 0);
    GetBotMsgThread(net::BotMessageHandler* octopusServerConnPtr,
                    QSettings*              confSettingPtr,
                    vector<BotMessage>      reqTaskVector,
                    queue<BotMessage>&      download_queue,
                    QWaitCondition&         download_cond):
        octopusServerConnPtr_(octopusServerConnPtr), confSettingPtr_(confSettingPtr),
        reqTaskVector_(reqTaskVector), download_queue_(download_queue), download_cond_(download_cond)
    {
    }

    int
    ResetConnect();

    void run();

    void getBotMsgTask();

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
