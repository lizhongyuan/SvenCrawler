/**
 * @Copyright(c)  2014 Ganji Inc.
 * @file          ganji/crawler/octopus_crawler/octopus_client/libs/base/src/net/bot_client.cpp
 * @namespace     net
 * @version       1.0
 * @author        zhangdanian
 * @date          2011-04-04
 *
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 *
 */
#include "bot_client.h"

namespace net {
    bool CrawlerBotMessage::encode(){
        return true;
    }

    bool CrawlerBotMessage::decode(){
        return true;
    }

    ///
    int BotMessageHandler::Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval){
        node_id_ = "lizhongyuan";
        proxy_ip_ = peer_ip;
        proxy_port_ = peer_port;
        connection_timeout_ = socket_timeout;
        check_interval_ = check_interval;
        return proxy_conn_.Init(peer_ip, peer_port, socket_timeout, check_interval);
    }

    bool BotMessageHandler::GetBotTask(const BotTasktypes::type bot_task_type, std::vector<BotMessage> &requests){
        bool success = true;
        NodeState node_status;
        node_status.cpu_state = "";
        node_status.mem_state = "";
        node_status.node_id   = node_id_;
        proxy_conn_.Client()->GetBotTask(requests, bot_task_type, node_status);
        return success;
    }

    bool BotMessageHandler::UploadBotTask(const std::vector<BotMessage> &responses){
        bool success = true;
        NodeState node_status;
        node_status.cpu_state = "";
        node_status.mem_state = "";
        node_status.node_id   = node_id_;
        success = proxy_conn_.Client()->UploadBotTask(responses, node_status);
        return success;
    }
    /// @brief 关闭并重连
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

    /// @brief 是否需要reset
    bool BotMessageHandler::NeedReset() {
        return proxy_conn_.NeedReset();
    }


    /// LinkCenter Interface
    int CenterMessageHandler::Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval){
        node_id_ = "192.168.38.132";
        proxy_ip_ = peer_ip;
        proxy_port_ = peer_port;
        connection_timeout_ = socket_timeout;
        check_interval_ = check_interval;
        return proxy_conn_.Init(peer_ip, peer_port, socket_timeout, check_interval);
    }

    void CenterMessageHandler::get_link_task(std::vector<DownloadTask> & _return, const std::string& node_id){
        utils::RecLock lock(conn_lock_);
        proxy_conn_.Client()->get_link_task(_return, node_id_);
    }

    void CenterMessageHandler::get_link_task_list(ListDownloadTask& _return, const std::string& node_id){
        utils::RecLock lock(conn_lock_);
        proxy_conn_.Client()->get_link_task_list(_return, node_id_);
    }

    bool CenterMessageHandler::upload_link_task(const std::vector<DownloadTask> & upload_task_list, const std::string& node_id){
        utils::RecLock lock(conn_lock_);
        bool success = true;
        success = proxy_conn_.Client()->upload_link_task(upload_task_list, node_id_);
        return success;
    }
    /// @brief 关闭并重连
    bool CenterMessageHandler::Reset() {
        return proxy_conn_.Reset();
    }

    void CenterMessageHandler::IncrTimes() {
        proxy_conn_.IncrTimes();
    }
    void CenterMessageHandler::Lock() {
        proxy_conn_.Lock();
    }

    void CenterMessageHandler::Unlock() {
        proxy_conn_.Unlock();
    }

    /// @brief 是否需要reset
    bool CenterMessageHandler::NeedReset() {
        return proxy_conn_.NeedReset();
    }

    ///extrator interface

    int ExtractorMessageHandler::Init(const string &peer_ip, int peer_port, int socket_timeout, int check_interval){
        node_id_ = "192.168.38.132";
        proxy_ip_ = peer_ip;
        proxy_port_ = peer_port;
        connection_timeout_ = socket_timeout;
        check_interval_ = check_interval;
        return proxy_conn_.Init(peer_ip, peer_port, socket_timeout, check_interval);
    }

    bool ExtractorMessageHandler::upload_extract_task(const ExtractItem& extract_task){
        utils::RecLock lock(conn_lock_);
        bool success = true;
        proxy_conn_.Client()->upload_extract_task(extract_task);
        return success;
    }
    /// @brief 关闭并重连
    bool ExtractorMessageHandler::Reset() {
        return proxy_conn_.Reset();
    }

    void ExtractorMessageHandler::IncrTimes() {
        proxy_conn_.IncrTimes();
    }
    void ExtractorMessageHandler::Lock() {
        proxy_conn_.Lock();
    }

    void ExtractorMessageHandler::Unlock() {
        proxy_conn_.Unlock();
    }

    /// @brief 是否需要reset
    bool ExtractorMessageHandler::NeedReset() {
        return proxy_conn_.NeedReset();
    }
}
