/**
 * @Copyright 2014 GanJi Inc.
 * @file    ganji/crawler/octopus_crawler/GJOctClient/libs/base/src/net/bot_client.h
 * @namespace ganji::crawler::octopus_crawler::net
 * @version 1.0
 * @author  lisizhong (transport by zhangdanian)
 * @date    2014-04-02
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#ifndef _GANJI_CRAWLER_OCTOPUS_CRAWLER_BOT_CLIENT_H_
#define _GANJI_CRAWLER_OCTOPUS_CRAWLER_BOT_CLINET_H_


#include "long_short_conn.h"
#include "gen-cpp/octopus_crawler_types.h"
#include "gen-cpp/OctopusProxyService.h"
#include "gen-cpp/StaticLinkCenterService.h"
#include "gen-cpp/ExtractorService.h"

#ifndef _WIN32
#include "ganji/ganji_global.h"
#include "ganji/util/thread/thread.h"
#include "ganji/util/thread/mutex.h"
#include "ganji/util/thread/condition.h"
#else
#include "utils/Threading.h"
#endif

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <deque>



namespace net {
using std::string;
using std::vector;
using std::queue;
using std::deque;
using boost::shared_ptr;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;


#ifndef _WIN32
using namespace ganji::util::log::ThreadFastLog;
namespace FastLog = ganji::util::log::ThreadFastLog;
namespace thread = ganji::util::thread;
using thread::Thread;
namespace Sleep = ::ganji::util::thread::Sleep;
using ganji::util::thread::RWLock;
using ganji::util::thread::Mutex;
#else
#endif

class BotMessageHeader {
public:
    int    node_id_;
    string token_;          // token
};

/**
 * @class BotMessage
 * @brief inherit this class to implement particular message delivery
 */
class CrawlerBotMessage: public BotMessage {
public:
    bool encode();
    bool decode();
protected:
    BotMessageHeader  message_header_; // 数据包的头信息
};

class BotMessageHandler {
public:
    int  Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval);
    bool GetBotTask(const BotTasktypes::type bot_task_type, std::vector<BotMessage> &requests);
    bool UploadBotTask(const std::vector<BotMessage> &responses);
    OctopusProxyServiceClient * Client() {return proxy_conn_.Client();}
    bool Reset();
    void IncrTimes();
    void Lock();
    void Unlock();
    bool NeedReset();
protected:
    string node_id_;
    string proxy_ip_;
    int proxy_port_;
    int connection_timeout_;    ///< 连接超时
    int check_interval_;    ///< 连接检测的时间间隔，单位:秒
    LongShortConn<OctopusProxyServiceClient> proxy_conn_;
};

class CenterMessageHandler {
public:
    int  Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval);
    void get_link_task(std::vector<DownloadTask> & _return, const std::string& node_id);
    void get_link_task_list(ListDownloadTask& _return, const std::string& node_id);
    bool upload_link_task(const std::vector<DownloadTask> & upload_task_list, const std::string& node_id);
    StaticLinkCenterServiceClient * Client() {return proxy_conn_.Client();}
    bool Reset();
    void IncrTimes();
    void Lock();
    void Unlock();
    bool NeedReset();
protected:
    string node_id_;
    string proxy_ip_;
    int proxy_port_;
    int connection_timeout_;    ///< 连接超时
    int check_interval_;    ///< 连接检测的时间间隔，单位:秒
    utils::RecMutex conn_lock_;
    LongShortConn<StaticLinkCenterServiceClient> proxy_conn_;
};


class ExtractorMessageHandler {
public:
    int  Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval);
    bool upload_extract_task(const ExtractItem& extract_task);
    ExtractorServiceClient * Client() {return proxy_conn_.Client();}
    bool Reset();
    void IncrTimes();
    void Lock();
    void Unlock();
    bool NeedReset();
protected:
    string node_id_;
    string proxy_ip_;
    int proxy_port_;
    int connection_timeout_;    ///< 连接超时
    int check_interval_;    ///< 连接检测的时间间隔，单位:秒
    utils::RecMutex conn_lock_;
    LongShortConn<ExtractorServiceClient> proxy_conn_;
};
} ///< ganji::crawler::octopus_crawler::net
#endif  ///< _GANJI_CRAWLER_OCTOPUS_CRAWLER_BOT_CLIENT_H_

