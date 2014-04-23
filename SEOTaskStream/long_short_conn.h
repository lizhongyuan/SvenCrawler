/**
 * @Copyright 2014 GanJi Inc.
 * @file    ganji/crawler/octopus_crawler/GJOctClient/libs/base/src/net/long_short_conn.h
 * @namespace ganji::crawler::octopus_crawler
 * @version 1.0
 * @author  lisizhong (transport by zhangdanian)
 * @date    2014-04-02
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#ifndef _GANJI_CRAWLER_OCTOPUS_CRAWLER_LONG_SHORT_CONN_H_
#define _GANJI_CRAWLER_OCTOPUS_CRAWLER_LONG_SHORT_CONN_H_

#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/PosixThreadFactory.h>

#ifndef _WIN32
#include <pthread.h>
#include "ganji/util/log/thread_fast_log.h"
#include "ganji/util/thread/thread.h"
#include "ganji/util/thread/sleep.h"
#include "ganji/util/thread/mutex.h"
#include "ganji/util/thread/rwlock.h"
#else
//#include "utils/Threading.h"
//#include "common/Stdafx.h"
#endif

#include <map>
#include <string>
#include <utility>

#include<QMutex>

//#include"bot_client.h"



namespace net {

using std::string;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

#ifndef _WIN32
using namespace ganji::util::log::ThreadFastLog;
namespace FastLog = ganji::util::log::ThreadFastLog;
namespace thread = ganji::util::thread;
using thread::Thread;
namespace Sleep = ::ganji::util::thread::Sleep;
using ganji::util::thread::RWLock;
using ganji::util::thread::Mutex;
#endif

/**
 * @class LongShortConn
 * @brief 长短连接handler基类
 */
template <typename T>
class LongShortConn
{
public:
  explicit LongShortConn(): p_sock_(NULL), p_trans_(NULL),
    p_port_(NULL),p_client_(NULL), sock_lock_(QMutex::Recursive){
  }

  ~LongShortConn() {
  }

  int Init(const string &peer_ip,
           int peer_port,
           int socket_timeout,
           int persist_times)
  {
    peer_ip_ = peer_ip;
    peer_port_ = peer_port;
    socket_timeout_ = socket_timeout;
    persist_times_ = persist_times;
    cur_times_ = 0;

    return 0;
  }

  T*
  Client()
  {
    return p_client_;
  }

  void
  Lock()
  {
      //sock_lock_.Lock();
  }

  void Unlock()
  {
      //sock_lock_.Unlock();
  }

  /// @brief 是否需要reset
  bool
  NeedReset()
  {
    if (!p_client_)
      return true;
    if (cur_times_ > persist_times_)
      return true;
    return false;
  }

  /// @brief 关闭并重连
  bool Reset()
  {
    Clear();
    bool ret = Reconnect();
    if (!ret)
    {
#ifdef _WIN32
      //utils::RecLock lock(sock_lock_);
      //LOG_FATAL(boost::format("[long_short_conn.h, LongShortConn::Reset] reconnect failed, server address: %s:%d") %peer_ip_ %peer_port_);
#else
      //WriteLog(kLogFatal, "Reconnect() to[%s:%d] failed", peer_ip_.c_str(), peer_port_);
      // qt log
#endif
    }
    /// 清空请求次数
    cur_times_ = 0;

    return ret;
  }

  /*
   *
   */
  void IncrTimes() {
      cur_times_++;
  }

  int32_t
  worker_func()
  {
    int ret = 0;
    //utils::RecLock lock(sock_lock_);
    //sock_lock_.Lock();
    do
    {
      /// 若连接不可用或已达请求数上限，则重连
      if (NeedReset())
      {
        bool is_ok = Reset();
        if (!is_ok)
        {
          ret = -1;
          break;
        }
      }

      /// 上面的代码保证现在的长连接看起来是valid的，但不能保证实际是否可用
      /// 重试2次，第一次调用失败则重连，保证实际可用
      for (int i = 0; i < 2; i++)
      {
        try
        {
          /// my function
          IncrTimes();
          ret = 0;
          break;
        }
        catch(...)
        {
          ret = -1;
#ifdef _WIN32
          //LOG_FATAL(boost::format("[long_short_conn.h, LongShortConn::worker_func] exception, server address: %s:%d") %peer_ip_ %peer_port_);
#else
          //WriteLog(kLogFatal, "my_func() failed");
#endif
          bool is_ok = Reset();
          if (!is_ok) {
            break;
          }
        }
      }
    } while (0);
    //sock_lock_.Unlock();

    return ret;
  }

private:
  /*
   *  @brief 关闭连接
   */
  void Clear()
  {
    if (p_client_ != NULL)
    {
      delete p_client_;
      p_client_ = NULL;
    }
    /// 删除client的时候，智能指针被自动销毁，不需要delete
    p_port_ = NULL;
    p_trans_ = NULL;
    p_sock_ = NULL;
  }

  /// @brief 重连
  bool Reconnect()
  {
    try
    {
      p_sock_ = new TSocket(peer_ip_, peer_port_);
      p_sock_->setConnTimeout(socket_timeout_);
      p_sock_->setRecvTimeout(socket_timeout_);
      p_sock_->setSendTimeout(socket_timeout_);
      p_sock_->open();
      shared_ptr<TSocket> sock_ptr(p_sock_);

      p_trans_ = new TFramedTransport(sock_ptr);
      shared_ptr<TFramedTransport> trans_ptr(p_trans_);

      p_port_ = new TBinaryProtocol(trans_ptr);
      shared_ptr<TBinaryProtocol> prot_ptr(p_port_);

      p_client_ = new T(prot_ptr);
    }
    catch(...)
    {
      if (p_sock_)
        delete p_sock_;
      if (p_client_)
        delete p_client_;
      return false;
    }
    return true;
  }

public:
  /// 被外部直接使用，所以设定为public
  string peer_ip_;
  int peer_port_;
  int socket_timeout_;    ///< 网络超时
  int persist_times_;     /// 长连接维持的请求次数
  int cur_times_;         /// 当前请求计数

  TSocket* p_sock_;
  TFramedTransport* p_trans_;
  TBinaryProtocol* p_port_;
  T* p_client_;
  //utils::RecMutex sock_lock_;
  QMutex sock_lock_;
};

};  ///< end of namespace ganji::crawler::octopus_crawler

#endif  ///< _GANJI_CRAWLER_OCTOPUS_CRAWLER_LONG_SHORT_CONN_H_
