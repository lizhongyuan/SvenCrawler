//#include "seodownloader.h"
#include "seocontroller.h"

#include<stdlib.h>
#include<iostream>
#include<list>
#include<vector>
#include<QtDebug>
#include<iostream>

using namespace std;

namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {

using namespace net;


int
SEOController::Init(QSettings* confSettingPtr)
{
  this->confSettingPtr_ = confSettingPtr;
  if(!confSettingPtr)
  {
      return -1;
  }

  /*
   * get the configure's value
   */
  QString dcHost = this->confSettingPtr_->value("downloader/OCTOPUS_SERVER_HOST").toString();
  int dcPort = this->confSettingPtr_->value("downloader/OCTOPUS_SERVER_PORT").toInt();
  int socketTimeout = this->confSettingPtr_->value("downloader/SOCKET_TIMEOUT").toInt();
  int persistCount = this->confSettingPtr_->value("downloader/PERSIST_COUNT").toInt();

  {
    this->ioMutex_.lock();
    qDebug()<<dcHost;
    qDebug()<<dcPort;
    qDebug()<<socketTimeout;
    qDebug()<<persistCount;
    this->ioMutex_.unlock();
  }

  this->octopusServerConnPtr_ = new net::BotMessageHandler();

  this->octopusServerConnPtr_->Init(dcHost.toStdString(),
                                    dcPort,
                                    socketTimeout,
                                    persistCount);

  return 0;
}

void
SEOController::Work()
{
    this->getBotMsgThread_ = new GetBotMsgThread(this->octopusServerConnPtr_,
                                                 this->confSettingPtr_,
                                                 this->reqTaskVector_,
                                                 this->download_queue_,
                                                 this->download_cond_);

    this->getBotMsgThread_->start();

    this->seoWorkThread_ = new SEOWorkThread(this->octopusServerConnPtr_,
                                             this->confSettingPtr_,
                                            this->download_queue_,
                                            this->upload_queue_,
                                            this->download_cond_,
                                            this->download_cond_);

    this->seoWorkThread_->run();
}

}}}};
