#include "seodownloader.h"



#include<stdlib.h>
#include<iostream>
#include<list>
#include<vector>
#include<QtDebug>
#include<iostream>

using namespace std;

namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {

using namespace net;

/*
void*
SEOdownloader::GetTaskThread(void *arg)
{
  try
  {
    SEOdownloader *p_seodownloader = reinterpret_cast<SEOdownloader *>(arg);
    assert(p_seodownloader);

    int time_slice = 100;
    time_slice = p_seodownloader->confSettingPtr->value("downloader/TIME_SLICE").toInt();
    time_slice /= 100;//time_slice in milliseconds

    while (true)
    {
      //boost::this_thread::sleep(boost::posix_time::milliseconds(time_slice));
      boost::this_thread::sleep(boost::posix_time::seconds(time_slice));

      //  let's make a test, qDebug() sth .
      p_seodownloader->GetTaskFunc();
      //qDebug()<<i++;
    }

    return NULL;
  }
  catch (boost::thread_interrupted&)
  {
    qDebug()<<"interrupted";
    return NULL;
  }
}

void*
SEOdownloader::SEOTaskThread(void *arg)
{
    SEOdownloader *p_seodownloader = reinterpret_cast<SEOdownloader *>(arg);
    assert(p_seodownloader);

    int time_slice = 100;
    time_slice = p_seodownloader->confSettingPtr->value("downloader/TIME_SLICE").toInt();
    time_slice /= 1000;//time_slice in milliseconds
    while (true)
    {
      boost::this_thread::sleep(boost::posix_time::seconds(time_slice));
      p_seodownloader->SEOTaskFunc();
    }
    return NULL;
}


void*
SEOdownloader::UploadTaskThread(void *arg)
{
    SEOdownloader *p_seodownloader = reinterpret_cast<SEOdownloader *>(arg);
    assert(p_seodownloader);

    int time_slice = 100;
    time_slice = p_seodownloader->confSettingPtr->value("downloader/TIME_SLICE").toInt();
    time_slice /= 1000;//time_slice in milliseconds
    while (true)
    {
      boost::this_thread::sleep(boost::posix_time::seconds(time_slice));
      p_seodownloader->UploadTaskFunc();
    }
    return NULL;
}
*/

int
SEOdownloader::Init(QSettings* confSettingPtr)
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
    //boost::mutex::scoped_lock io_mutex(this->io_lock_);
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
SEOdownloader::Run()
{
    /*
    this->getBotTaskThread_ = boost::thread(boost::bind(GetTaskThread, this));
    this->popThread_ = boost::thread(boost::bind(SEOTaskThread, this));
    this->uploadThread_ = boost::thread(boost::bind(UploadTaskThread, this));
    */

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
    //this->seoWorkThread_->start();
    this->seoWorkThread_->run();
}


/*
 *  upload the task
 */
/*
int
SEOdownloader::SEOTaskFunc()
{
  boost::mutex::scoped_lock SEOLock(this->SEOtask_lock_);

  // wait when the download_queue_ is empty.
  while(this->download_queue_.empty())
  {
      {
          boost::mutex::scoped_lock io_lock(this->io_lock_);
          qDebug()<<"The download_queue is empty";
      }
      download_cond_.wait(SEOLock);
  }

  SEOLock.unlock(); //try unlock

  vector<SimulatorTask> SEOtaskVector;

  //CSingleCraw* singlecraw = new CSingleCraw;
  while(!this->download_queue_.empty())
  {
      SEOLock.lock();
      SimulatorTask curGetTask = this->download_queue_.front();
      SEOtaskVector.push_back(curGetTask);
      this->download_queue_.pop();
      SEOLock.unlock();
      this->download_cond_.notify_all();  //notify the download_queue
  }

   * SEO's core process
  //vector<SimulatorTask> respTaskVector = this->testSEOprocess(SEOtaskVector);
  this->singlecraw = new CSingleCraw();
  vector<SimulatorTask> respTaskVector = this->singlecraw->BaiduSEOTest(SEOtaskVector, 1);

  for(vector<SimulatorTask>::iterator iter = respTaskVector.begin(); iter != respTaskVector.end(); iter++)
  {
      SEOLock.lock();
      this->upload_queue_.push(*iter);
      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
      SEOLock.unlock();
      upload_cond_.notify_all();  //notify the upload_queue
  }

  return 0;
} //end

vector<SimulatorTask>
SEOdownloader::testSEOprocess2(vector<SimulatorTask>& reqTaskVector)
{

  vector<SimulatorTask> respTaskVector;
  return respTaskVector;
}

vector<SimulatorTask>
SEOdownloader::testSEOprocess(vector<SimulatorTask>& reqTask)
{
  vector<SimulatorTask> respTaskVector;
  for(vector<SimulatorTask>::iterator iter = reqTask.begin(); iter != reqTask.end(); iter++)
  {
      SimulatorTask curRespTask;
      curRespTask.resp_item.task_id = 2;
      curRespTask.resp_item.cookie = "";
      curRespTask.resp_item.ip = "192.168.9.13";
      curRespTask.resp_item.node_id = 1;
      curRespTask.resp_item.target_url = "www.ganji.com";
      curRespTask.resp_item.time_stamp = "2014-04-18 14:55:09";

      respTaskVector.push_back(curRespTask);
  }
  return respTaskVector;
}

int
SEOdownloader::UploadTaskFunc()
{
  int ret = -1;
  bool upload_ok;

  boost::mutex::scoped_lock uploadLock(this->upload_lock_);
  while(this->upload_queue_.empty())
  {
      {
          boost::mutex::scoped_lock io_mutex(this->io_lock_);
          //cout<<"the upload_queue_ is empty"<<endl;
          qDebug()<<"the upload_queue_ is empty";
      }
      this->upload_cond_.wait(uploadLock);
  }

  //vector<SimulatorTask> uploadVector;
  vector<BotMessage> uploadVector;

  while(!this->upload_queue_.empty())
  {
      SimulatorTask curSimuTask = this->upload_queue_.front();
      BotMessage curBotMsg;
      curBotMsg.simulator_task = curSimuTask;
      curBotMsg.bot_task_types = BotTasktypes::type::KSEOTASK;
      uploadVector.push_back(curBotMsg);
      this->upload_queue_.pop();
  }

  /*
  SimulatorTask popTask = this->upload_queue_.front();
  BotMessage  curBotMessage;
  curBotMessage.simulator_task = popTask;
  curBotMessage.bot_task_types = BotTasktypes::type::KSEOTASK;
  vector<BotMessage> uploadQueue;
  uploadQueue.push_back(curBotMessage);
  */

  /*
  NodeState curNodeState;
  curNodeState.node_id = "lizhongyuan";
  curNodeState.cpu_state = "";
  curNodeState.mem_state = "";
  */

  /*
   * connect, and upload the Simulate Task Queue
   */

/*
  do
  {
    //  There is a reclock before
    if (octopus_server_conn_.NeedReset())
    {
      bool is_ok = octopus_server_conn_.Reset();
      if (!is_ok) {
        ret = -1;
        break;
      }
    }

    // retry until success
    for (int i = 0; i < this->confSettingPtr->value("downloader/RETRY_TIMES").toInt() ; i++)
    {
      try
      {
        upload_ok = octopus_server_conn_.UploadBotTask(uploadVector,
                                                            curNodeState);
        ret = 0;
        break;
      }
      catch(...)
      {
        ret = -1;
        bool is_ok = octopus_server_conn_.Reset();
        if (!is_ok)
        {
          {
            boost::mutex::scoped_lock io_mutex(this->io_lock_);
            qDebug()<<"get uploadTask failed, and Reset failed.";
          }
          // qt log
          break;
        }
        else
        {
          {
            boost::mutex::scoped_lock io_mutex(this->io_lock_);
            qDebug()<<"get uploadTask failed.";
          }
        }
      }
    }
  } while (0);

  if(upload_ok)
  {
      boost::mutex::scoped_lock io_mutex(this->io_lock_);
      qDebug()<<"upload ok";
  }
  else
  {
      boost::mutex::scoped_lock io_mutex(this->io_lock_);
      qDebug()<<"upload failed";
  }

  while(!this->upload_queue_.empty())
  {
      this->upload_queue_.pop();
  }

  return 0;
}

int
SEOdownloader::GetTaskFunc()
{
  int ret = -2;
  vector<BotMessage> reqBotMsgVector;

  NodeState curNodeState;
  //curNodeState.node_id = "192.168.38.167";
  curNodeState.node_id = "lizhongyuan";
  curNodeState.cpu_state = "";
  curNodeState.mem_state = "";

  do
  {
    //  There is a reclock before
    boost::mutex::scoped_lock lock(this->download_lock_);
    if (octopus_server_conn_.NeedReset())
    {
      bool is_ok = octopus_server_conn_.Reset();
      if (!is_ok) {
        ret = -1;
        break;
      }
    }

    // retry until success
    // indeed, it only succeed once
    for (int i = 0; i < this->confSettingPtr->value("downloader/RETRY_TIMES").toInt() ; i++)
    {
      try
      {
        octopus_server_conn_.GetBotTask(BotTasktypes::type::KSEOTASK,
                                        reqBotMsgVector,
                                        curNodeState);
        //std::cout<<"Test, reqBotMsgVector:"<<reqBotMsgVector[0].bot_task_types<<endl;
        octopus_server_conn_.IncrTimes();
        ret = 0;
        break;
      }
      catch(...)
      {
        ret = -1;
        bool is_ok = octopus_server_conn_.Reset();
        if (!is_ok)
        {
          boost::mutex::scoped_lock io_mutex(this->io_lock_);
          qDebug()<<"get downloadTask failed, and Reset failed.";
          // qt log
          break;
        }
        else
        {
          boost::mutex::scoped_lock io_mutex(this->io_lock_);
          qDebug()<<"get downloadTask failed.";
        }
      }
    }
  } while (0);

  {
    boost::mutex::scoped_lock io_mutex(this->io_lock_);
    qDebug()<<reqBotMsgVector.size();
  }

  if (reqBotMsgVector.empty())
  {
    return 0;
  }

  for (vector<BotMessage>::iterator it_task = reqBotMsgVector.begin();
      it_task != reqBotMsgVector.end(); ++it_task)
  {
    std::cout<<"bot_task_types:"<<it_task->bot_task_types<<endl;
    //qDebug()<<it_task->bot_task_types;
    if (it_task->bot_task_types != BotTasktypes::KSEOTASK)
    {
      //continue;
    }

    boost::mutex::scoped_lock lock(download_lock_);
    download_queue_.push(it_task->simulator_task);
    lock.unlock();
    download_cond_.notify_all();
  }
  return 0;
} // end
*/

}}}};
