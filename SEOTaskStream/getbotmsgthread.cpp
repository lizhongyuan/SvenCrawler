﻿#include "getbotmsgthread.h"


namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {

void
GetBotMsgThread::run()
{
    while(true)
    {
        this->getTask();
        this->moveToQueue();
    }
}

int
GetBotMsgThread::getTask()
{
    int ret = -2;

    NodeState curNodeState;
    curNodeState.node_id = "lizhongyuan";
    curNodeState.cpu_state = "";
    curNodeState.mem_state = "";

    this->getMutex_.lock();
    do
    {
      //this->getMutex_.lock();
      if (this->octopusServerConnPtr_->NeedReset())
      {
        bool is_ok = this->octopusServerConnPtr_->Reset();
        if (!is_ok) {
          ret = -1;
          break;
        }
      }

      for (int i = 0; i < this->confSettingPtr_->value("downloader/RETRY_TIMES").toInt() ; i++)
      {
        try
        {
          this->octopusServerConnPtr_->GetBotTask(BotTasktypes::type::KSEOTASK,
                                                  this->reqTaskVector_,
                                                  curNodeState);
          this->octopusServerConnPtr_->IncrTimes();
          ret = 0;
          break;
        }
        catch(...)
        {
          ret = -1;
          bool is_ok = this->octopusServerConnPtr_->Reset();
          if (!is_ok)
          {
            this->ioMutex_.lock();
            qDebug()<<"get downloadTask failed, and Reset failed.";
            this->ioMutex_.unlock();
            // qt log
            break;
          }
          else
          {
            this->ioMutex_.lock();
            qDebug()<<"get downloadTask failed.";
            this->ioMutex_.unlock();
          }
        }
      }
      //this->getMutex_.unlock();
    } while (0);

    this->getMutex_.unlock();

    {
      /*
      this->ioMutex_.lock();
      qDebug()<<this->reqTaskVector_.size();
      this->ioMutex_.unlock();
      */
    }

    if (this->reqTaskVector_.empty())
    {
      return 0;
    }

    return ret;
}

void
GetBotMsgThread::moveToQueue()
{
    this->getMutex_.lock();

    while(1000 == this->download_queue_.size())
    {
        this->ioMutex_.lock();
        //qDebug()<<"The download queue is full enough, wait for popping";
        this->ioMutex_.unlock();
        this->download_cond_.wait(&this->getMutex_);
    }

    this->getMutex_.unlock();

    for(vector<BotMessage>::iterator iter = this->reqTaskVector_.begin();
        iter != this->reqTaskVector_.end();
        iter ++)
    {
        this->getMutex_.lock();

        if(this->download_queue_.size() == 1000)
        {
            this->getMutex_.unlock();
            break;
        }

        this->download_queue_.push(*iter);

        boost::this_thread::sleep(boost::posix_time::milliseconds(9));

        this->getMutex_.unlock();
        //this->download_cond_.wakeAll();
    }

    this->download_cond_.wakeAll();   // tell the SEOworkThread
    this->reqTaskVector_.clear();

    /*
    this->ioMutex_.lock();
    std::cout<<"The download queue size is "<<this->download_queue_.size()<<endl;
    this->ioMutex_.unlock();
    */
}


}}}};
