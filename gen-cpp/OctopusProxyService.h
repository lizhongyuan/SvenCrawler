﻿/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef OctopusProxyService_H
#define OctopusProxyService_H

#include <thrift/TDispatchProcessor.h>
#include "octopus_crawler_types.h"



class OctopusProxyServiceIf {
 public:
  virtual ~OctopusProxyServiceIf() {}
  virtual void GetBotTask(std::vector<BotMessage> & _return, const BotTasktypes::type bot_task_type, const NodeState& node_state) = 0;
  virtual bool UploadBotTask(const std::vector<BotMessage> & responses, const NodeState& node_state) = 0;
};

class OctopusProxyServiceIfFactory {
 public:
  typedef OctopusProxyServiceIf Handler;

  virtual ~OctopusProxyServiceIfFactory() {}

  virtual OctopusProxyServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(OctopusProxyServiceIf* /* handler */) = 0;
};

class OctopusProxyServiceIfSingletonFactory : virtual public OctopusProxyServiceIfFactory {
 public:
  OctopusProxyServiceIfSingletonFactory(const boost::shared_ptr<OctopusProxyServiceIf>& iface) : iface_(iface) {}
  virtual ~OctopusProxyServiceIfSingletonFactory() {}

  virtual OctopusProxyServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(OctopusProxyServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<OctopusProxyServiceIf> iface_;
};

class OctopusProxyServiceNull : virtual public OctopusProxyServiceIf {
 public:
  virtual ~OctopusProxyServiceNull() {}
  void GetBotTask(std::vector<BotMessage> & /* _return */, const BotTasktypes::type /* bot_task_type */, const NodeState& /* node_state */) {
    return;
  }
  bool UploadBotTask(const std::vector<BotMessage> & /* responses */, const NodeState& /* node_state */) {
    bool _return = false;
    return _return;
  }
};

typedef struct _OctopusProxyService_GetBotTask_args__isset {
  _OctopusProxyService_GetBotTask_args__isset() : bot_task_type(false), node_state(false) {}
  bool bot_task_type;
  bool node_state;
} _OctopusProxyService_GetBotTask_args__isset;

class OctopusProxyService_GetBotTask_args {
 public:

  OctopusProxyService_GetBotTask_args() : bot_task_type((BotTasktypes::type)0) {
  }

  virtual ~OctopusProxyService_GetBotTask_args() throw() {}

  BotTasktypes::type bot_task_type;
  NodeState node_state;

  _OctopusProxyService_GetBotTask_args__isset __isset;

  void __set_bot_task_type(const BotTasktypes::type val) {
    bot_task_type = val;
  }

  void __set_node_state(const NodeState& val) {
    node_state = val;
  }

  bool operator == (const OctopusProxyService_GetBotTask_args & rhs) const
  {
    if (!(bot_task_type == rhs.bot_task_type))
      return false;
    if (!(node_state == rhs.node_state))
      return false;
    return true;
  }
  bool operator != (const OctopusProxyService_GetBotTask_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OctopusProxyService_GetBotTask_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class OctopusProxyService_GetBotTask_pargs {
 public:


  virtual ~OctopusProxyService_GetBotTask_pargs() throw() {}

  const BotTasktypes::type* bot_task_type;
  const NodeState* node_state;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OctopusProxyService_GetBotTask_result__isset {
  _OctopusProxyService_GetBotTask_result__isset() : success(false) {}
  bool success;
} _OctopusProxyService_GetBotTask_result__isset;

class OctopusProxyService_GetBotTask_result {
 public:

  OctopusProxyService_GetBotTask_result() {
  }

  virtual ~OctopusProxyService_GetBotTask_result() throw() {}

  std::vector<BotMessage>  success;

  _OctopusProxyService_GetBotTask_result__isset __isset;

  void __set_success(const std::vector<BotMessage> & val) {
    success = val;
  }

  bool operator == (const OctopusProxyService_GetBotTask_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const OctopusProxyService_GetBotTask_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OctopusProxyService_GetBotTask_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OctopusProxyService_GetBotTask_presult__isset {
  _OctopusProxyService_GetBotTask_presult__isset() : success(false) {}
  bool success;
} _OctopusProxyService_GetBotTask_presult__isset;

class OctopusProxyService_GetBotTask_presult {
 public:


  virtual ~OctopusProxyService_GetBotTask_presult() throw() {}

  std::vector<BotMessage> * success;

  _OctopusProxyService_GetBotTask_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _OctopusProxyService_UploadBotTask_args__isset {
  _OctopusProxyService_UploadBotTask_args__isset() : responses(false), node_state(false) {}
  bool responses;
  bool node_state;
} _OctopusProxyService_UploadBotTask_args__isset;

class OctopusProxyService_UploadBotTask_args {
 public:

  OctopusProxyService_UploadBotTask_args() {
  }

  virtual ~OctopusProxyService_UploadBotTask_args() throw() {}

  std::vector<BotMessage>  responses;
  NodeState node_state;

  _OctopusProxyService_UploadBotTask_args__isset __isset;

  void __set_responses(const std::vector<BotMessage> & val) {
    responses = val;
  }

  void __set_node_state(const NodeState& val) {
    node_state = val;
  }

  bool operator == (const OctopusProxyService_UploadBotTask_args & rhs) const
  {
    if (!(responses == rhs.responses))
      return false;
    if (!(node_state == rhs.node_state))
      return false;
    return true;
  }
  bool operator != (const OctopusProxyService_UploadBotTask_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OctopusProxyService_UploadBotTask_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class OctopusProxyService_UploadBotTask_pargs {
 public:


  virtual ~OctopusProxyService_UploadBotTask_pargs() throw() {}

  const std::vector<BotMessage> * responses;
  const NodeState* node_state;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OctopusProxyService_UploadBotTask_result__isset {
  _OctopusProxyService_UploadBotTask_result__isset() : success(false) {}
  bool success;
} _OctopusProxyService_UploadBotTask_result__isset;

class OctopusProxyService_UploadBotTask_result {
 public:

  OctopusProxyService_UploadBotTask_result() : success(0) {
  }

  virtual ~OctopusProxyService_UploadBotTask_result() throw() {}

  bool success;

  _OctopusProxyService_UploadBotTask_result__isset __isset;

  void __set_success(const bool val) {
    success = val;
  }

  bool operator == (const OctopusProxyService_UploadBotTask_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const OctopusProxyService_UploadBotTask_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OctopusProxyService_UploadBotTask_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OctopusProxyService_UploadBotTask_presult__isset {
  _OctopusProxyService_UploadBotTask_presult__isset() : success(false) {}
  bool success;
} _OctopusProxyService_UploadBotTask_presult__isset;

class OctopusProxyService_UploadBotTask_presult {
 public:


  virtual ~OctopusProxyService_UploadBotTask_presult() throw() {}

  bool* success;

  _OctopusProxyService_UploadBotTask_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class OctopusProxyServiceClient : virtual public OctopusProxyServiceIf {
 public:
  OctopusProxyServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  OctopusProxyServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void GetBotTask(std::vector<BotMessage> & _return, const BotTasktypes::type bot_task_type, const NodeState& node_state);
  void send_GetBotTask(const BotTasktypes::type bot_task_type, const NodeState& node_state);
  void recv_GetBotTask(std::vector<BotMessage> & _return);
  bool UploadBotTask(const std::vector<BotMessage> & responses, const NodeState& node_state);
  void send_UploadBotTask(const std::vector<BotMessage> & responses, const NodeState& node_state);
  bool recv_UploadBotTask();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class OctopusProxyServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<OctopusProxyServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (OctopusProxyServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_GetBotTask(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_UploadBotTask(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  OctopusProxyServiceProcessor(boost::shared_ptr<OctopusProxyServiceIf> iface) :
    iface_(iface) {
    processMap_["GetBotTask"] = &OctopusProxyServiceProcessor::process_GetBotTask;
    processMap_["UploadBotTask"] = &OctopusProxyServiceProcessor::process_UploadBotTask;
  }

  virtual ~OctopusProxyServiceProcessor() {}
};

class OctopusProxyServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  OctopusProxyServiceProcessorFactory(const ::boost::shared_ptr< OctopusProxyServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< OctopusProxyServiceIfFactory > handlerFactory_;
};

class OctopusProxyServiceMultiface : virtual public OctopusProxyServiceIf {
 public:
  OctopusProxyServiceMultiface(std::vector<boost::shared_ptr<OctopusProxyServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~OctopusProxyServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<OctopusProxyServiceIf> > ifaces_;
  OctopusProxyServiceMultiface() {}
  void add(boost::shared_ptr<OctopusProxyServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void GetBotTask(std::vector<BotMessage> & _return, const BotTasktypes::type bot_task_type, const NodeState& node_state) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->GetBotTask(_return, bot_task_type, node_state);
    }
    ifaces_[i]->GetBotTask(_return, bot_task_type, node_state);
    return;
  }

  bool UploadBotTask(const std::vector<BotMessage> & responses, const NodeState& node_state) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->UploadBotTask(responses, node_state);
    }
    return ifaces_[i]->UploadBotTask(responses, node_state);
  }

};



#endif
