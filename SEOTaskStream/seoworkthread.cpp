#include "seoworkthread.h"

namespace ganji { namespace crawler { namespace octopus_crawler { namespace downloader {

SEOWorkThread::~SEOWorkThread()
{
  if(this->csingleCraw != NULL)
  {
      delete this->csingleCraw;
      this->csingleCraw = NULL;
  }
  if(this->octopusServerConnPtr_ != NULL)
  {
      delete this->octopusServerConnPtr_;
      this->csingleCraw = NULL;
  }
  if(this->confSettingPtr_ != NULL)
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
        cout<<"==================="<<endl;
        vector<BotMessage>  reqTaskVector = this->outOffQueue();
        if(reqTaskVector.size() != 0)
        {
          vector<BotMessage>  respTaskVector = this->SEOprocess(reqTaskVector);
          if(respTaskVector.size() != 0)
          {
            this->sendTask(respTaskVector);
          }
        }
    }
}

vector<BotMessage>
SEOWorkThread::outOffQueue()
{
    this->workMutex_.lock();
    while(this->download_queue_.empty())
    {
        this->ioMutex_.lock();
        //cout<<"The download_queue is empty."<<endl;
        //cout<<"The upload_queue_ size is "<<this->upload_queue_.size()<<endl;
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
    //int upload_ok;
    bool upload_ok;

    NodeState curNodeState;
    curNodeState.node_id = "lizhongyuan";
    curNodeState.cpu_state = "";
    curNodeState.mem_state = "";

    this->workMutex_.lock();
    do
    {
      if (this->octopusServerConnPtr_->NeedReset())
      {
        bool is_ok = this->octopusServerConnPtr_->Reset();
        if (!is_ok)
        {
          ret = -1;
          break;
        }
      }

      // retry until success
      for (int i = 0; i < this->confSettingPtr_->value("downloader/RETRY_TIMES").toInt() ; i++)
      {
        try
        {
          upload_ok = this->octopusServerConnPtr_->UploadBotTask(respTaskVector);
                                                                 //curNodeState);
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

}}}};
