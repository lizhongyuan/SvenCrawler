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

#include "bot_client.h"


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
    this->confSettingPtr = NULL;
  }

  ~SEOdownloader()
  {
      if(this->confSettingPtr != NULL)
      {
          delete this->confSettingPtr;
          this->confSettingPtr = NULL;
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

  static void* GetTaskThread(void *arg);
  int GetTaskFunc();
  static void* UploadTaskThread(void* arg);
  int UploadTaskFunc();
  static void* SEOTaskThread(void *arg);
  int SEOTaskFunc();


  vector<SimulatorTask> testSEOprocess(vector<SimulatorTask>& reqTask);

private:
  net::BotMessageHandler  octopus_server_conn_;  ///< 与bot server的连接
  QSettings*  confSettingPtr;

  boost::condition_variable download_cond_;
  boost::condition_variable upload_cond_;

  queue<SimulatorTask> upload_queue_;
  queue<SimulatorTask> download_queue_;

  boost::thread getBotTaskThread_;
  boost::thread popThread_;
  boost::thread uploadThread_;

  boost::mutex io_lock_;
  mutable boost::mutex download_lock_;
  mutable boost::mutex SEOtask_lock_;
  mutable boost::mutex upload_lock_;

  //CSingleCraw* singlecraw;
};


}}}};

#endif // SEODOWNLOADER_H
