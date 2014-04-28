#include "seoworkthread.h"

namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {

SEOWorkThread::~SEOWorkThread()
{
  if(this->csingleCraw != NULL)
  {
      delete this->csingleCraw;
      this->csingleCraw = NULL;
  }
}

void
SEOWorkThread::run()
{
    while(true)
    {
        vector<BotMessage>  reqTaskVector = this->outOffQueue();
        vector<BotMessage>  respTaskVector = this->SEOprocess(reqTaskVector);
        this->sendTask(respTaskVector);
    }
}

//void
vector<BotMessage>
SEOWorkThread::outOffQueue()
{
    this->workMutex_.lock();
    while(this->download_queue_.empty())
    {
        this->ioMutex_.lock();
        cout<<"The download_queue is empty."<<endl;
        cout<<"The upload_queue_ size is "<<this->upload_queue_.size()<<endl;
        this->ioMutex_.unlock();
        this->download_cond_.wait(&this->workMutex_);
    }

    vector<BotMessage> reqTaskVector;
    while(!this->download_queue_.empty())
    {
        BotMessage curBotMsg = this->download_queue_.front();
        reqTaskVector.push_back(curBotMsg);
        this->download_queue_.pop();
    }
    this->workMutex_.unlock();

    return reqTaskVector;
}

vector<BotMessage>
SEOWorkThread::SEOprocess(vector<BotMessage> reqTaskVector)
{
    this->workMutex_.lock();
    vector<BotMessage> respTaskVector = this->csingleCraw->BaiduSEOTest(reqTaskVector,1);
    this->workMutex_.unlock();
    return respTaskVector;
}

void
SEOWorkThread::sendTask(vector<BotMessage> respTaskVector)
{
    int ret = -2;
    int upload_ok;

    NodeState curNodeState;
    curNodeState.node_id = "lizhongyuan";
    curNodeState.cpu_state = "";
    curNodeState.mem_state = "";

    this->workMutex_.lock();
    do
    {
      //  There is a reclock before
      if (this->octopusServerConnPtr_->NeedReset())
      {
        bool is_ok = this->octopusServerConnPtr_->Reset();
        if (!is_ok) {
          ret = -1;
          break;
        }
      }

      // retry until success
      for (int i = 0; i < this->confSettingPtr_->value("downloader/RETRY_TIMES").toInt() ; i++)
      {
        try
        {
          upload_ok = this->octopusServerConnPtr_->UploadBotTask(respTaskVector,
                                                                 curNodeState);
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
            qDebug()<<"get uploadTask failed, and Reset failed.";
            this->ioMutex_.unlock();

            break;
          }
          else
          {
            this->ioMutex_.lock();
            qDebug()<<"get uploadTask failed.";
            this->ioMutex_.unlock();
          }
        }
      }
    } while (0);
    this->workMutex_.unlock();

    if(upload_ok)
    {
        this->ioMutex_.lock();
        qDebug()<<"upload ok";
        this->ioMutex_.unlock();
    }
    else
    {
        this->ioMutex_.lock();
        qDebug()<<"upload failed";
        this->ioMutex_.unlock();
    }
}

/*
int
SEOWorkThread::GetWork()
{
    int ret = -2;

    NodeState curNodeState;
    curNodeState.node_id = "lizhongyuan";
    curNodeState.cpu_state = "";
    curNodeState.mem_state = "";

    do
    {
      //boost::mutex::scoped_lock lock(this->download_lock_);
      this->getMutex_.lock();
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
          //std::cout<<"Test, reqBotMsgVector:"<<reqBotMsgVector[0].bot_task_types<<endl;
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
      this->getMutex_.unlock();
    } while (0);

    {
      this->ioMutex_.lock();
      qDebug()<<this->reqTaskVector_.size();
      this->ioMutex_.unlock();
    }

    if (this->reqTaskVector_.empty())
    {
      return 0;
    }
    return ret;
}
*/

/*
int
SEOWorkThread::GetWork()
{
    int ret = -2;

    NodeState curNodeState;
    curNodeState.node_id = "lizhongyuan";
    curNodeState.cpu_state = "";
    curNodeState.mem_state = "";

    do
    {
      //boost::mutex::scoped_lock lock(this->download_lock_);
      this->getMutex_.lock();
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
          //std::cout<<"Test, reqBotMsgVector:"<<reqBotMsgVector[0].bot_task_types<<endl;
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
      this->getMutex_.unlock();
    } while (0);

    {
      this->ioMutex_.lock();
      qDebug()<<this->reqTaskVector_.size();
      this->ioMutex_.unlock();
    }

    if (this->reqTaskVector_.empty())
    {
      return 0;
    }
}
*/

/*
void
SEOWorkThread::moveToQueue()
{
    this->getMutex_.lock();

    while(100 == this->download_queue_.size())
    {
        this->ioMutex_.lock();
        qDebug()<<"The download queue is full enough, wait for popping";
        this->ioMutex_.unlock();
        this->download_cond_.wait(&this->getMutex_);
    }

    this->getMutex_.unlock();

    for(vector<BotMessage>::iterator iter = this->reqTaskVector_.begin();
        iter != this->reqTaskVector_.end();
        iter ++)
    {
        this->getMutex_.lock();
        this->download_queue_.push(*iter);
        boost::this_thread::sleep(boost::posix_time::milliseconds(9));
        this->getMutex_.unlock();
        this->download_cond_.wakeAll();
    }

    this->reqTaskVector_.clear();

    this->ioMutex_.lock();
    std::cout<<"The download queue size is "<<this->download_queue_.size()<<endl;
    this->ioMutex_.unlock();
}
*/

}}}};
