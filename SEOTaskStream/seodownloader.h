#ifndef SEODOWNLOADER_H
#define SEODOWNLOADER_H

#include<QSettings>
#include<QMutex>
#include<QtDebug>

#include"gen-cpp/OctopusProxyService.h"
#include"gen-cpp/octopus_crawler_constants.h"
#include"gen-cpp/octopus_crawler_types.h"

#include <queue>
#include <iostream>
#include <vector>
#include <list>
#include <QMutex>

//#include "bot_client.h"
#include "manager/csinglecraw.h"

#include "getbotmsgthread.h"
#include "seoworkthread.h"
#include "uploadbotmsgthread.h"


namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {

using namespace net;


class BotMessageHandler;

class SEOdownloader;

/*
struct ThreadArg
{
  ThreadArg()
  {
    p_seodownloader = NULL;
    idx = 0;
  }
  ThreadArg(SEOdownloader *my_seodownloader, int my_idx)
  {
    p_seodownloader = my_seodownloader;
    idx = my_idx;
  }

  SEOdownloader *p_seodownloader;
  int idx;
};
*/


/**
 * @class SEOdownloader
 * @brief 管理一个downloader与dc间的连接和下载需求
 */
class SEOdownloader
{
public:
  SEOdownloader()
  {
    this->confSettingPtr_ = NULL;
    this->octopusServerConnPtr_ = NULL;
  }

  ~SEOdownloader()
  {
      if(this->confSettingPtr_ != NULL)
      {
          delete this->confSettingPtr_;
          this->confSettingPtr_ = NULL;
      }
  }

  int Init(QSettings* confSettingPtr);
  void Run();

public:

  /*
  static void* GetTaskThread(void *arg);
  int GetTaskFunc();
  static void* UploadTaskThread(void* arg);
  int UploadTaskFunc();
  static void* SEOTaskThread(void *arg);
  int SEOTaskFunc();
  */

  /*
  vector<SimulatorTask> testSEOprocess(vector<SimulatorTask>& reqTask);
  vector<SimulatorTask> testSEOprocess2(vector<SimulatorTask>& reqTask);
  */

private:
  //net::BotMessageHandler  octopus_server_conn_;  ///< 与bot server的连接
  net::BotMessageHandler*  octopusServerConnPtr_;
  QSettings*  confSettingPtr_;

  vector<BotMessage> reqTaskVector_;
  vector<BotMessage> respTaskVector_;

  queue<BotMessage>   download_queue_;
  queue<BotMessage>   upload_queue;

  GetBotMsgThread*    getBotMsgThread_;
  SEOWorkThread*      seoWorkThread_;
  UploadBotMsgThread* uploadBotMsgThread_;

  QWaitCondition  download_cond_;
  QWaitCondition  upload_cond_;

  QMutex  ioMutex_;


  CSingleCraw* singlecraw_;
};


}}}};

#endif // SEODOWNLOADER_H
