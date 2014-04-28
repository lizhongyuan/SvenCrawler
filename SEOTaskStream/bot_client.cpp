
/**
 * @Copyright(c)  2014 Ganji Inc.
 * @file          ganji/crawler/octopus_crawler/octopus_client/libs/base/src/net/bot_client.cpp
 * @namespace     net
 * @version       1.0
 * @author        zhangdanian
 * @date          2011-04-04
 *
 *
 * �Ķ��������� ��ʹ��tools/cpplint/cpplint.py ���������Ƿ����ϱ����淶!
 * ��ѭ�ı����淶���ο�: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 *
 */
#include"bot_client.h"

namespace net
{
  int
  BotMessageHandler::Init(const string &peer_ip,
                          int peer_port,
                          int socket_timeout,
                          int check_interval)
  {
        proxy_ip_ = peer_ip;
        proxy_port_ = peer_port;
        connection_timeout_ = socket_timeout;
        check_interval_ = check_interval;
        return proxy_conn_.Init(peer_ip, peer_port, socket_timeout, check_interval);
    }

  bool
  BotMessageHandler::GetBotTask(const BotTasktypes::type bot_task_type,
                                std::vector<BotMessage> &requests,
                                const NodeState& node_state)
  {
    bool success = true;

    proxy_conn_.Client()->GetBotTask( requests,
                                      bot_task_type,
                                      node_state);
        return success;
    }

  bool
  BotMessageHandler::UploadBotTask(const std::vector<BotMessage> &responses,
                                   const NodeState& node_state)
  {
    bool success = true;
    success = proxy_conn_.Client()->UploadBotTask(responses,
                                                  node_state);
        return success;
    }

    /// @brief �رղ����
    bool BotMessageHandler::Reset() {
        return proxy_conn_.Reset();
    }

    void BotMessageHandler::IncrTimes() {
        proxy_conn_.IncrTimes();
    }
    void BotMessageHandler::Lock() {
        proxy_conn_.Lock();
    }

    void BotMessageHandler::Unlock() {
        proxy_conn_.Unlock();
    }

    /// @brief �Ƿ���Ҫreset
    bool BotMessageHandler::NeedReset() {
        return proxy_conn_.Reset();
    }
}
