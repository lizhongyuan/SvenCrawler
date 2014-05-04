﻿/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef octopus_crawler_TYPES_H
#define octopus_crawler_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




struct TemplateType {
  enum type {
    CSS_SELECTOR_TYPE = 0,
    PLAIN_HTML_TYPE = 1,
    RELAY_TYPE = 2,
    TEMPLATE_TYPE_MAX = 3,
    NONE_TYPE = 10000
  };
};

extern const std::map<int, const char*> _TemplateType_VALUES_TO_NAMES;

struct HeaderFieldsType {
  enum type {
    DEFAULT_TYPE = 0,
    UPDATE_PART_TYPE = 1,
    UPDATE_ALL_TYPE = 2,
    HEADER_FIELDS_TYPE_MAX = 3,
    NONE_TYPE = 10000
  };
};

extern const std::map<int, const char*> _HeaderFieldsType_VALUES_TO_NAMES;

struct DownloaderType {
  enum type {
    NORMAL_TYPE = 0,
    WEBKIT_TYPE = 1,
    DOWNLOADER_TYPE_MAX = 2,
    NONE_TYPE = 10000
  };
};

extern const std::map<int, const char*> _DownloaderType_VALUES_TO_NAMES;

struct ResultType {
  enum type {
    LINK_TYPE = 0,
    REPORT_TYPE = 1,
    DATA_TYPE = 2,
    RESULT_TYPE_MAX = 3,
    NONE_TYPE = 10000
  };
};

extern const std::map<int, const char*> _ResultType_VALUES_TO_NAMES;

struct TaskErrorType {
  enum type {
    OK_TYPE = 0,
    DOWNLOAD_FAILED_TYPE = 1,
    EXTRACT_FAILED_TYPE = 2,
    BANNED_TYPE = 3,
    TASK_ERROR_TYPE_MAX = 4,
    NONE_TYPE = 10000
  };
};

extern const std::map<int, const char*> _TaskErrorType_VALUES_TO_NAMES;

struct UrlType {
  enum type {
    LINK_URL_TYPE = 0,
    POST_URL_TYPE = 1,
    IMG_URL_TYPE = 2,
    PHONE_IMG_URL_TYPE = 3,
    NEXT_PAGE_URL_TYPE = 4,
    URL_TYPE_MAX = 5,
    NONE_TYPE = 10000
  };
};

extern const std::map<int, const char*> _UrlType_VALUES_TO_NAMES;

struct UpdateTaskTypes {
  enum type {
    KCRAWLERBOT = 0,
    KSEOBOT = 1,
    KTEMPALTE = 2,
    KDIAL = 3
  };
};

extern const std::map<int, const char*> _UpdateTaskTypes_VALUES_TO_NAMES;

struct BotTasktypes {
  enum type {
    KCRAWLERTASK = 0,
    KSEOTASK = 1,
    KCRAWLERTEMPLATEUPDATE = 2,
    KBOTUPDATE = 3,
    KDIALTASK = 4
  };
};

extern const std::map<int, const char*> _BotTasktypes_VALUES_TO_NAMES;

typedef struct _DownloadReqItem__isset {
  _DownloadReqItem__isset() : url(false), ip(false), referer(false), ua(false), header_fields_type(false), downloader_type(false), post_fields(false), time_out(false), header_list(false) {}
  bool url;
  bool ip;
  bool referer;
  bool ua;
  bool header_fields_type;
  bool downloader_type;
  bool post_fields;
  bool time_out;
  bool header_list;
} _DownloadReqItem__isset;

class DownloadReqItem {
 public:

  static const char* ascii_fingerprint; // = "66121B4576FE7A9DA35B400A9B046C57";
  static const uint8_t binary_fingerprint[16]; // = {0x66,0x12,0x1B,0x45,0x76,0xFE,0x7A,0x9D,0xA3,0x5B,0x40,0x0A,0x9B,0x04,0x6C,0x57};

  DownloadReqItem() : url(), ip(), referer(), ua(), header_fields_type((HeaderFieldsType::type)0), downloader_type((DownloaderType::type)0), post_fields(), time_out(0) {
  }

  virtual ~DownloadReqItem() throw() {}

  std::string url;
  std::string ip;
  std::string referer;
  std::string ua;
  HeaderFieldsType::type header_fields_type;
  DownloaderType::type downloader_type;
  std::string post_fields;
  int32_t time_out;
  std::vector<std::string>  header_list;

  _DownloadReqItem__isset __isset;

  void __set_url(const std::string& val) {
    url = val;
  }

  void __set_ip(const std::string& val) {
    ip = val;
  }

  void __set_referer(const std::string& val) {
    referer = val;
  }

  void __set_ua(const std::string& val) {
    ua = val;
  }

  void __set_header_fields_type(const HeaderFieldsType::type val) {
    header_fields_type = val;
  }

  void __set_downloader_type(const DownloaderType::type val) {
    downloader_type = val;
  }

  void __set_post_fields(const std::string& val) {
    post_fields = val;
  }

  void __set_time_out(const int32_t val) {
    time_out = val;
  }

  void __set_header_list(const std::vector<std::string> & val) {
    header_list = val;
  }

  bool operator == (const DownloadReqItem & rhs) const
  {
    if (!(url == rhs.url))
      return false;
    if (!(ip == rhs.ip))
      return false;
    if (!(referer == rhs.referer))
      return false;
    if (!(ua == rhs.ua))
      return false;
    if (!(header_fields_type == rhs.header_fields_type))
      return false;
    if (!(downloader_type == rhs.downloader_type))
      return false;
    if (!(post_fields == rhs.post_fields))
      return false;
    if (!(time_out == rhs.time_out))
      return false;
    if (!(header_list == rhs.header_list))
      return false;
    return true;
  }
  bool operator != (const DownloadReqItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DownloadReqItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DownloadReqItem &a, DownloadReqItem &b);

typedef struct _DownloadPropItem__isset {
  _DownloadPropItem__isset() : is_friendly(false), interval(false), retry_times(false), task_id(false), depth(false), store_extract_depth(false), url_type(false), template_type(false), seed_url(false), url_template(false) {}
  bool is_friendly;
  bool interval;
  bool retry_times;
  bool task_id;
  bool depth;
  bool store_extract_depth;
  bool url_type;
  bool template_type;
  bool seed_url;
  bool url_template;
} _DownloadPropItem__isset;

class DownloadPropItem {
 public:

  static const char* ascii_fingerprint; // = "6AD589019BA4210C43B7F2ACD5B79431";
  static const uint8_t binary_fingerprint[16]; // = {0x6A,0xD5,0x89,0x01,0x9B,0xA4,0x21,0x0C,0x43,0xB7,0xF2,0xAC,0xD5,0xB7,0x94,0x31};

  DownloadPropItem() : is_friendly(0), interval(0), retry_times(0), task_id(0), depth(0), store_extract_depth(0), url_type((UrlType::type)0), template_type((TemplateType::type)0), seed_url(), url_template() {
  }

  virtual ~DownloadPropItem() throw() {}

  bool is_friendly;
  int32_t interval;
  int32_t retry_times;
  int32_t task_id;
  int32_t depth;
  int32_t store_extract_depth;
  UrlType::type url_type;
  TemplateType::type template_type;
  std::string seed_url;
  std::string url_template;

  _DownloadPropItem__isset __isset;

  void __set_is_friendly(const bool val) {
    is_friendly = val;
  }

  void __set_interval(const int32_t val) {
    interval = val;
  }

  void __set_retry_times(const int32_t val) {
    retry_times = val;
  }

  void __set_task_id(const int32_t val) {
    task_id = val;
  }

  void __set_depth(const int32_t val) {
    depth = val;
  }

  void __set_store_extract_depth(const int32_t val) {
    store_extract_depth = val;
  }

  void __set_url_type(const UrlType::type val) {
    url_type = val;
  }

  void __set_template_type(const TemplateType::type val) {
    template_type = val;
  }

  void __set_seed_url(const std::string& val) {
    seed_url = val;
  }

  void __set_url_template(const std::string& val) {
    url_template = val;
  }

  bool operator == (const DownloadPropItem & rhs) const
  {
    if (!(is_friendly == rhs.is_friendly))
      return false;
    if (!(interval == rhs.interval))
      return false;
    if (!(retry_times == rhs.retry_times))
      return false;
    if (!(task_id == rhs.task_id))
      return false;
    if (!(depth == rhs.depth))
      return false;
    if (!(store_extract_depth == rhs.store_extract_depth))
      return false;
    if (!(url_type == rhs.url_type))
      return false;
    if (!(template_type == rhs.template_type))
      return false;
    if (!(seed_url == rhs.seed_url))
      return false;
    if (!(url_template == rhs.url_template))
      return false;
    return true;
  }
  bool operator != (const DownloadPropItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DownloadPropItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DownloadPropItem &a, DownloadPropItem &b);

typedef struct _DownloadResultItem__isset {
  _DownloadResultItem__isset() : is_ok(false), http_code(false), err_info(false), result_type(false), extract_map(false) {}
  bool is_ok;
  bool http_code;
  bool err_info;
  bool result_type;
  bool extract_map;
} _DownloadResultItem__isset;

class DownloadResultItem {
 public:

  static const char* ascii_fingerprint; // = "C217E1C050106CFEC86D19C280538EDC";
  static const uint8_t binary_fingerprint[16]; // = {0xC2,0x17,0xE1,0xC0,0x50,0x10,0x6C,0xFE,0xC8,0x6D,0x19,0xC2,0x80,0x53,0x8E,0xDC};

  DownloadResultItem() : is_ok((TaskErrorType::type)0), http_code(0), err_info(), result_type((ResultType::type)0) {
  }

  virtual ~DownloadResultItem() throw() {}

  TaskErrorType::type is_ok;
  int32_t http_code;
  std::string err_info;
  ResultType::type result_type;
  std::map<std::string, std::vector<std::string> >  extract_map;

  _DownloadResultItem__isset __isset;

  void __set_is_ok(const TaskErrorType::type val) {
    is_ok = val;
  }

  void __set_http_code(const int32_t val) {
    http_code = val;
  }

  void __set_err_info(const std::string& val) {
    err_info = val;
  }

  void __set_result_type(const ResultType::type val) {
    result_type = val;
  }

  void __set_extract_map(const std::map<std::string, std::vector<std::string> > & val) {
    extract_map = val;
  }

  bool operator == (const DownloadResultItem & rhs) const
  {
    if (!(is_ok == rhs.is_ok))
      return false;
    if (!(http_code == rhs.http_code))
      return false;
    if (!(err_info == rhs.err_info))
      return false;
    if (!(result_type == rhs.result_type))
      return false;
    if (!(extract_map == rhs.extract_map))
      return false;
    return true;
  }
  bool operator != (const DownloadResultItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DownloadResultItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DownloadResultItem &a, DownloadResultItem &b);

typedef struct _DownloadTask__isset {
  _DownloadTask__isset() : req_item(false), prop_item(false), result_item(false) {}
  bool req_item;
  bool prop_item;
  bool result_item;
} _DownloadTask__isset;

class DownloadTask {
 public:

  static const char* ascii_fingerprint; // = "518A291C1954A5A1A154D5C54CF3974E";
  static const uint8_t binary_fingerprint[16]; // = {0x51,0x8A,0x29,0x1C,0x19,0x54,0xA5,0xA1,0xA1,0x54,0xD5,0xC5,0x4C,0xF3,0x97,0x4E};

  DownloadTask() {
  }

  virtual ~DownloadTask() throw() {}

  DownloadReqItem req_item;
  DownloadPropItem prop_item;
  DownloadResultItem result_item;

  _DownloadTask__isset __isset;

  void __set_req_item(const DownloadReqItem& val) {
    req_item = val;
  }

  void __set_prop_item(const DownloadPropItem& val) {
    prop_item = val;
  }

  void __set_result_item(const DownloadResultItem& val) {
    result_item = val;
  }

  bool operator == (const DownloadTask & rhs) const
  {
    if (!(req_item == rhs.req_item))
      return false;
    if (!(prop_item == rhs.prop_item))
      return false;
    if (!(result_item == rhs.result_item))
      return false;
    return true;
  }
  bool operator != (const DownloadTask &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DownloadTask & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DownloadTask &a, DownloadTask &b);

typedef struct _ListDownloadTask__isset {
  _ListDownloadTask__isset() : list_down_task(false) {}
  bool list_down_task;
} _ListDownloadTask__isset;

class ListDownloadTask {
 public:

  static const char* ascii_fingerprint; // = "4D2F16D6A536B351AB93CF80029B5BFA";
  static const uint8_t binary_fingerprint[16]; // = {0x4D,0x2F,0x16,0xD6,0xA5,0x36,0xB3,0x51,0xAB,0x93,0xCF,0x80,0x02,0x9B,0x5B,0xFA};

  ListDownloadTask() {
  }

  virtual ~ListDownloadTask() throw() {}

  std::vector<DownloadTask>  list_down_task;

  _ListDownloadTask__isset __isset;

  void __set_list_down_task(const std::vector<DownloadTask> & val) {
    list_down_task = val;
  }

  bool operator == (const ListDownloadTask & rhs) const
  {
    if (!(list_down_task == rhs.list_down_task))
      return false;
    return true;
  }
  bool operator != (const ListDownloadTask &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ListDownloadTask & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(ListDownloadTask &a, ListDownloadTask &b);

typedef struct _ExtractItem__isset {
  _ExtractItem__isset() : task(false), body(false) {}
  bool task;
  bool body;
} _ExtractItem__isset;

class ExtractItem {
 public:

  static const char* ascii_fingerprint; // = "BB887B606A671A3339D7E22993AF3EA5";
  static const uint8_t binary_fingerprint[16]; // = {0xBB,0x88,0x7B,0x60,0x6A,0x67,0x1A,0x33,0x39,0xD7,0xE2,0x29,0x93,0xAF,0x3E,0xA5};

  ExtractItem() : body() {
  }

  virtual ~ExtractItem() throw() {}

  DownloadTask task;
  std::string body;

  _ExtractItem__isset __isset;

  void __set_task(const DownloadTask& val) {
    task = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  bool operator == (const ExtractItem & rhs) const
  {
    if (!(task == rhs.task))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const ExtractItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ExtractItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(ExtractItem &a, ExtractItem &b);

typedef struct _ExtractItems__isset {
  _ExtractItems__isset() : extract_task_list(false) {}
  bool extract_task_list;
} _ExtractItems__isset;

class ExtractItems {
 public:

  static const char* ascii_fingerprint; // = "92B6DF721AAFD189D4D0E6350420465D";
  static const uint8_t binary_fingerprint[16]; // = {0x92,0xB6,0xDF,0x72,0x1A,0xAF,0xD1,0x89,0xD4,0xD0,0xE6,0x35,0x04,0x20,0x46,0x5D};

  ExtractItems() {
  }

  virtual ~ExtractItems() throw() {}

  std::vector<ExtractItem>  extract_task_list;

  _ExtractItems__isset __isset;

  void __set_extract_task_list(const std::vector<ExtractItem> & val) {
    extract_task_list = val;
  }

  bool operator == (const ExtractItems & rhs) const
  {
    if (!(extract_task_list == rhs.extract_task_list))
      return false;
    return true;
  }
  bool operator != (const ExtractItems &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ExtractItems & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(ExtractItems &a, ExtractItems &b);

typedef struct _MatchedResultItem__isset {
  _MatchedResultItem__isset() : self_result(false), sub_result_list(false), is_ok(false), err_info(false) {}
  bool self_result;
  bool sub_result_list;
  bool is_ok;
  bool err_info;
} _MatchedResultItem__isset;

class MatchedResultItem {
 public:

  static const char* ascii_fingerprint; // = "7609B1D31BB860963FAAAD9401CD61DA";
  static const uint8_t binary_fingerprint[16]; // = {0x76,0x09,0xB1,0xD3,0x1B,0xB8,0x60,0x96,0x3F,0xAA,0xAD,0x94,0x01,0xCD,0x61,0xDA};

  MatchedResultItem() : is_ok(0), err_info() {
  }

  virtual ~MatchedResultItem() throw() {}

  std::map<std::string, std::vector<std::string> >  self_result;
  std::vector<std::map<std::string, std::vector<std::string> > >  sub_result_list;
  bool is_ok;
  std::string err_info;

  _MatchedResultItem__isset __isset;

  void __set_self_result(const std::map<std::string, std::vector<std::string> > & val) {
    self_result = val;
  }

  void __set_sub_result_list(const std::vector<std::map<std::string, std::vector<std::string> > > & val) {
    sub_result_list = val;
  }

  void __set_is_ok(const bool val) {
    is_ok = val;
  }

  void __set_err_info(const std::string& val) {
    err_info = val;
  }

  bool operator == (const MatchedResultItem & rhs) const
  {
    if (!(self_result == rhs.self_result))
      return false;
    if (!(sub_result_list == rhs.sub_result_list))
      return false;
    if (!(is_ok == rhs.is_ok))
      return false;
    if (!(err_info == rhs.err_info))
      return false;
    return true;
  }
  bool operator != (const MatchedResultItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MatchedResultItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(MatchedResultItem &a, MatchedResultItem &b);

typedef struct _DownloadedBodyItem__isset {
  _DownloadedBodyItem__isset() : task(false), is_ok(false), body(false) {}
  bool task;
  bool is_ok;
  bool body;
} _DownloadedBodyItem__isset;

class DownloadedBodyItem {
 public:

  static const char* ascii_fingerprint; // = "9580C4A6AB1BE3F9451F3A7393FB5DAD";
  static const uint8_t binary_fingerprint[16]; // = {0x95,0x80,0xC4,0xA6,0xAB,0x1B,0xE3,0xF9,0x45,0x1F,0x3A,0x73,0x93,0xFB,0x5D,0xAD};

  DownloadedBodyItem() : is_ok(0), body() {
  }

  virtual ~DownloadedBodyItem() throw() {}

  DownloadTask task;
  bool is_ok;
  std::string body;

  _DownloadedBodyItem__isset __isset;

  void __set_task(const DownloadTask& val) {
    task = val;
  }

  void __set_is_ok(const bool val) {
    is_ok = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  bool operator == (const DownloadedBodyItem & rhs) const
  {
    if (!(task == rhs.task))
      return false;
    if (!(is_ok == rhs.is_ok))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const DownloadedBodyItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DownloadedBodyItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DownloadedBodyItem &a, DownloadedBodyItem &b);

typedef struct _DialInfoItem__isset {
  _DialInfoItem__isset() : user(false), pwd(false) {}
  bool user;
  bool pwd;
} _DialInfoItem__isset;

class DialInfoItem {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

  DialInfoItem() : user(), pwd() {
  }

  virtual ~DialInfoItem() throw() {}

  std::string user;
  std::string pwd;

  _DialInfoItem__isset __isset;

  void __set_user(const std::string& val) {
    user = val;
  }

  void __set_pwd(const std::string& val) {
    pwd = val;
  }

  bool operator == (const DialInfoItem & rhs) const
  {
    if (!(user == rhs.user))
      return false;
    if (!(pwd == rhs.pwd))
      return false;
    return true;
  }
  bool operator != (const DialInfoItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DialInfoItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DialInfoItem &a, DialInfoItem &b);

typedef struct _DialRespItem__isset {
  _DialRespItem__isset() : ip(false), port(false) {}
  bool ip;
  bool port;
} _DialRespItem__isset;

class DialRespItem {
 public:

  static const char* ascii_fingerprint; // = "EEBC915CE44901401D881E6091423036";
  static const uint8_t binary_fingerprint[16]; // = {0xEE,0xBC,0x91,0x5C,0xE4,0x49,0x01,0x40,0x1D,0x88,0x1E,0x60,0x91,0x42,0x30,0x36};

  DialRespItem() : ip(), port(0) {
  }

  virtual ~DialRespItem() throw() {}

  std::string ip;
  int32_t port;

  _DialRespItem__isset __isset;

  void __set_ip(const std::string& val) {
    ip = val;
  }

  void __set_port(const int32_t val) {
    port = val;
  }

  bool operator == (const DialRespItem & rhs) const
  {
    if (!(ip == rhs.ip))
      return false;
    if (!(port == rhs.port))
      return false;
    return true;
  }
  bool operator != (const DialRespItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DialRespItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DialRespItem &a, DialRespItem &b);

typedef struct _UpdateReqItem__isset {
  _UpdateReqItem__isset() : task_id(false), url(false), target_ip(false), node_id(false), timestamp(false), version(false), update_type(false), target_name(false), template_type(false), dial_info(false) {}
  bool task_id;
  bool url;
  bool target_ip;
  bool node_id;
  bool timestamp;
  bool version;
  bool update_type;
  bool target_name;
  bool template_type;
  bool dial_info;
} _UpdateReqItem__isset;

class UpdateReqItem {
 public:

  static const char* ascii_fingerprint; // = "F4F95FBAFCD0D6402E66FF49B8F546CD";
  static const uint8_t binary_fingerprint[16]; // = {0xF4,0xF9,0x5F,0xBA,0xFC,0xD0,0xD6,0x40,0x2E,0x66,0xFF,0x49,0xB8,0xF5,0x46,0xCD};

  UpdateReqItem() : task_id(0), url(), target_ip(), node_id(), timestamp(0), version(), update_type((UpdateTaskTypes::type)0), target_name(), template_type((TemplateType::type)0) {
  }

  virtual ~UpdateReqItem() throw() {}

  int32_t task_id;
  std::string url;
  std::string target_ip;
  std::string node_id;
  int32_t timestamp;
  std::string version;
  UpdateTaskTypes::type update_type;
  std::string target_name;
  TemplateType::type template_type;
  std::vector<std::string>  dial_info;

  _UpdateReqItem__isset __isset;

  void __set_task_id(const int32_t val) {
    task_id = val;
  }

  void __set_url(const std::string& val) {
    url = val;
  }

  void __set_target_ip(const std::string& val) {
    target_ip = val;
  }

  void __set_node_id(const std::string& val) {
    node_id = val;
  }

  void __set_timestamp(const int32_t val) {
    timestamp = val;
  }

  void __set_version(const std::string& val) {
    version = val;
  }

  void __set_update_type(const UpdateTaskTypes::type val) {
    update_type = val;
  }

  void __set_target_name(const std::string& val) {
    target_name = val;
  }

  void __set_template_type(const TemplateType::type val) {
    template_type = val;
  }

  void __set_dial_info(const std::vector<std::string> & val) {
    dial_info = val;
  }

  bool operator == (const UpdateReqItem & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(url == rhs.url))
      return false;
    if (!(target_ip == rhs.target_ip))
      return false;
    if (!(node_id == rhs.node_id))
      return false;
    if (!(timestamp == rhs.timestamp))
      return false;
    if (!(version == rhs.version))
      return false;
    if (!(update_type == rhs.update_type))
      return false;
    if (!(target_name == rhs.target_name))
      return false;
    if (!(template_type == rhs.template_type))
      return false;
    if (!(dial_info == rhs.dial_info))
      return false;
    return true;
  }
  bool operator != (const UpdateReqItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const UpdateReqItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(UpdateReqItem &a, UpdateReqItem &b);

typedef struct _UpdateRespItem__isset {
  _UpdateRespItem__isset() : task_id(false), node_id(false), server_version(false), client_version(false), version_name(false), timestamp(false), body(false), dial_resp(false) {}
  bool task_id;
  bool node_id;
  bool server_version;
  bool client_version;
  bool version_name;
  bool timestamp;
  bool body;
  bool dial_resp;
} _UpdateRespItem__isset;

class UpdateRespItem {
 public:

  static const char* ascii_fingerprint; // = "44C8C8DCDECB6662B8DB5787B65D5E80";
  static const uint8_t binary_fingerprint[16]; // = {0x44,0xC8,0xC8,0xDC,0xDE,0xCB,0x66,0x62,0xB8,0xDB,0x57,0x87,0xB6,0x5D,0x5E,0x80};

  UpdateRespItem() : task_id(0), node_id(), server_version(), client_version(), version_name(), timestamp(), body() {
  }

  virtual ~UpdateRespItem() throw() {}

  int32_t task_id;
  std::string node_id;
  std::string server_version;
  std::string client_version;
  std::string version_name;
  std::string timestamp;
  std::string body;
  std::vector<DialRespItem>  dial_resp;

  _UpdateRespItem__isset __isset;

  void __set_task_id(const int32_t val) {
    task_id = val;
  }

  void __set_node_id(const std::string& val) {
    node_id = val;
  }

  void __set_server_version(const std::string& val) {
    server_version = val;
  }

  void __set_client_version(const std::string& val) {
    client_version = val;
  }

  void __set_version_name(const std::string& val) {
    version_name = val;
  }

  void __set_timestamp(const std::string& val) {
    timestamp = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  void __set_dial_resp(const std::vector<DialRespItem> & val) {
    dial_resp = val;
  }

  bool operator == (const UpdateRespItem & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(node_id == rhs.node_id))
      return false;
    if (!(server_version == rhs.server_version))
      return false;
    if (!(client_version == rhs.client_version))
      return false;
    if (!(version_name == rhs.version_name))
      return false;
    if (!(timestamp == rhs.timestamp))
      return false;
    if (!(body == rhs.body))
      return false;
    if (!(dial_resp == rhs.dial_resp))
      return false;
    return true;
  }
  bool operator != (const UpdateRespItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const UpdateRespItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(UpdateRespItem &a, UpdateRespItem &b);

typedef struct _UpdateTask__isset {
  _UpdateTask__isset() : req_item(false), resp_item(false) {}
  bool req_item;
  bool resp_item;
} _UpdateTask__isset;

class UpdateTask {
 public:

  static const char* ascii_fingerprint; // = "5302C3A69502391998AF50922BD603B6";
  static const uint8_t binary_fingerprint[16]; // = {0x53,0x02,0xC3,0xA6,0x95,0x02,0x39,0x19,0x98,0xAF,0x50,0x92,0x2B,0xD6,0x03,0xB6};

  UpdateTask() {
  }

  virtual ~UpdateTask() throw() {}

  UpdateReqItem req_item;
  UpdateRespItem resp_item;

  _UpdateTask__isset __isset;

  void __set_req_item(const UpdateReqItem& val) {
    req_item = val;
  }

  void __set_resp_item(const UpdateRespItem& val) {
    resp_item = val;
  }

  bool operator == (const UpdateTask & rhs) const
  {
    if (!(req_item == rhs.req_item))
      return false;
    if (!(resp_item == rhs.resp_item))
      return false;
    return true;
  }
  bool operator != (const UpdateTask &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const UpdateTask & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(UpdateTask &a, UpdateTask &b);

typedef struct _DedupExistItem__isset {
  _DedupExistItem__isset() : is_exists(false), item_info(false) {}
  bool is_exists;
  bool item_info;
} _DedupExistItem__isset;

class DedupExistItem {
 public:

  static const char* ascii_fingerprint; // = "1767FFB0CB3D9275BC64B198AB3B8A8B";
  static const uint8_t binary_fingerprint[16]; // = {0x17,0x67,0xFF,0xB0,0xCB,0x3D,0x92,0x75,0xBC,0x64,0xB1,0x98,0xAB,0x3B,0x8A,0x8B};

  DedupExistItem() : is_exists(0), item_info() {
  }

  virtual ~DedupExistItem() throw() {}

  bool is_exists;
  std::string item_info;

  _DedupExistItem__isset __isset;

  void __set_is_exists(const bool val) {
    is_exists = val;
  }

  void __set_item_info(const std::string& val) {
    item_info = val;
  }

  bool operator == (const DedupExistItem & rhs) const
  {
    if (!(is_exists == rhs.is_exists))
      return false;
    if (!(item_info == rhs.item_info))
      return false;
    return true;
  }
  bool operator != (const DedupExistItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DedupExistItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(DedupExistItem &a, DedupExistItem &b);

typedef struct _SimulatorReqItem__isset {
  _SimulatorReqItem__isset() : task_id(false), key_words(false), url_regex(false), click_count(false), city(false) {}
  bool task_id;
  bool key_words;
  bool url_regex;
  bool click_count;
  bool city;
} _SimulatorReqItem__isset;

class SimulatorReqItem {
 public:

  static const char* ascii_fingerprint; // = "3DEA490DCFDBF7F9065EFB84569A610F";
  static const uint8_t binary_fingerprint[16]; // = {0x3D,0xEA,0x49,0x0D,0xCF,0xDB,0xF7,0xF9,0x06,0x5E,0xFB,0x84,0x56,0x9A,0x61,0x0F};

  SimulatorReqItem() : task_id(0), key_words(), url_regex(), click_count(0), city() {
  }

  virtual ~SimulatorReqItem() throw() {}

  int32_t task_id;
  std::string key_words;
  std::string url_regex;
  int32_t click_count;
  std::string city;

  _SimulatorReqItem__isset __isset;

  void __set_task_id(const int32_t val) {
    task_id = val;
  }

  void __set_key_words(const std::string& val) {
    key_words = val;
  }

  void __set_url_regex(const std::string& val) {
    url_regex = val;
  }

  void __set_click_count(const int32_t val) {
    click_count = val;
  }

  void __set_city(const std::string& val) {
    city = val;
  }

  bool operator == (const SimulatorReqItem & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(key_words == rhs.key_words))
      return false;
    if (!(url_regex == rhs.url_regex))
      return false;
    if (!(click_count == rhs.click_count))
      return false;
    if (!(city == rhs.city))
      return false;
    return true;
  }
  bool operator != (const SimulatorReqItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SimulatorReqItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(SimulatorReqItem &a, SimulatorReqItem &b);

typedef struct _SimulatorRespItem__isset {
  _SimulatorRespItem__isset() : task_id(false), target_url(false), ip(false), cookie(false), node_id(false), time_stamp(false) {}
  bool task_id;
  bool target_url;
  bool ip;
  bool cookie;
  bool node_id;
  bool time_stamp;
} _SimulatorRespItem__isset;

class SimulatorRespItem {
 public:

  static const char* ascii_fingerprint; // = "511023597CEDC78D170D0E3534ED6749";
  static const uint8_t binary_fingerprint[16]; // = {0x51,0x10,0x23,0x59,0x7C,0xED,0xC7,0x8D,0x17,0x0D,0x0E,0x35,0x34,0xED,0x67,0x49};

  SimulatorRespItem() : task_id(0), target_url(), ip(), cookie(), node_id(0), time_stamp() {
  }

  virtual ~SimulatorRespItem() throw() {}

  int32_t task_id;
  std::string target_url;
  std::string ip;
  std::string cookie;
  int32_t node_id;
  std::string time_stamp;

  _SimulatorRespItem__isset __isset;

  void __set_task_id(const int32_t val) {
    task_id = val;
  }

  void __set_target_url(const std::string& val) {
    target_url = val;
  }

  void __set_ip(const std::string& val) {
    ip = val;
  }

  void __set_cookie(const std::string& val) {
    cookie = val;
  }

  void __set_node_id(const int32_t val) {
    node_id = val;
  }

  void __set_time_stamp(const std::string& val) {
    time_stamp = val;
  }

  bool operator == (const SimulatorRespItem & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(target_url == rhs.target_url))
      return false;
    if (!(ip == rhs.ip))
      return false;
    if (!(cookie == rhs.cookie))
      return false;
    if (!(node_id == rhs.node_id))
      return false;
    if (!(time_stamp == rhs.time_stamp))
      return false;
    return true;
  }
  bool operator != (const SimulatorRespItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SimulatorRespItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(SimulatorRespItem &a, SimulatorRespItem &b);

typedef struct _SimulatorTask__isset {
  _SimulatorTask__isset() : req_item(false), resp_item(false) {}
  bool req_item;
  bool resp_item;
} _SimulatorTask__isset;

class SimulatorTask {
 public:

  static const char* ascii_fingerprint; // = "6DDAC11E7F4D257B9656E37EA715A996";
  static const uint8_t binary_fingerprint[16]; // = {0x6D,0xDA,0xC1,0x1E,0x7F,0x4D,0x25,0x7B,0x96,0x56,0xE3,0x7E,0xA7,0x15,0xA9,0x96};

  SimulatorTask() {
  }

  virtual ~SimulatorTask() throw() {}

  SimulatorReqItem req_item;
  SimulatorRespItem resp_item;

  _SimulatorTask__isset __isset;

  void __set_req_item(const SimulatorReqItem& val) {
    req_item = val;
  }

  void __set_resp_item(const SimulatorRespItem& val) {
    resp_item = val;
  }

  bool operator == (const SimulatorTask & rhs) const
  {
    if (!(req_item == rhs.req_item))
      return false;
    if (!(resp_item == rhs.resp_item))
      return false;
    return true;
  }
  bool operator != (const SimulatorTask &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SimulatorTask & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(SimulatorTask &a, SimulatorTask &b);

typedef struct _PcNode__isset {
  _PcNode__isset() : node_id(false), name(false), time_stamp(false), secret(false), state(false) {}
  bool node_id;
  bool name;
  bool time_stamp;
  bool secret;
  bool state;
} _PcNode__isset;

class PcNode {
 public:

  static const char* ascii_fingerprint; // = "5959CE085787E3D819EB3EB041545A2C";
  static const uint8_t binary_fingerprint[16]; // = {0x59,0x59,0xCE,0x08,0x57,0x87,0xE3,0xD8,0x19,0xEB,0x3E,0xB0,0x41,0x54,0x5A,0x2C};

  PcNode() : node_id(), name(), time_stamp(), secret(), state(0) {
  }

  virtual ~PcNode() throw() {}

  std::string node_id;
  std::string name;
  std::string time_stamp;
  std::string secret;
  int32_t state;

  _PcNode__isset __isset;

  void __set_node_id(const std::string& val) {
    node_id = val;
  }

  void __set_name(const std::string& val) {
    name = val;
  }

  void __set_time_stamp(const std::string& val) {
    time_stamp = val;
  }

  void __set_secret(const std::string& val) {
    secret = val;
  }

  void __set_state(const int32_t val) {
    state = val;
  }

  bool operator == (const PcNode & rhs) const
  {
    if (!(node_id == rhs.node_id))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(time_stamp == rhs.time_stamp))
      return false;
    if (!(secret == rhs.secret))
      return false;
    if (!(state == rhs.state))
      return false;
    return true;
  }
  bool operator != (const PcNode &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PcNode & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(PcNode &a, PcNode &b);

typedef struct _BotMessage__isset {
  _BotMessage__isset() : down_load_task(false), simulator_task(false), update_task(false), bot_task_types(false), token(false) {}
  bool down_load_task;
  bool simulator_task;
  bool update_task;
  bool bot_task_types;
  bool token;
} _BotMessage__isset;

class BotMessage {
 public:

  static const char* ascii_fingerprint; // = "C7A4EEC2526E0BDEE5C75B1D2196BEFC";
  static const uint8_t binary_fingerprint[16]; // = {0xC7,0xA4,0xEE,0xC2,0x52,0x6E,0x0B,0xDE,0xE5,0xC7,0x5B,0x1D,0x21,0x96,0xBE,0xFC};

  BotMessage() : bot_task_types((BotTasktypes::type)0), token() {
  }

  virtual ~BotMessage() throw() {}

  DownloadTask down_load_task;
  SimulatorTask simulator_task;
  UpdateTask update_task;
  BotTasktypes::type bot_task_types;
  std::string token;

  _BotMessage__isset __isset;

  void __set_down_load_task(const DownloadTask& val) {
    down_load_task = val;
  }

  void __set_simulator_task(const SimulatorTask& val) {
    simulator_task = val;
  }

  void __set_update_task(const UpdateTask& val) {
    update_task = val;
  }

  void __set_bot_task_types(const BotTasktypes::type val) {
    bot_task_types = val;
  }

  void __set_token(const std::string& val) {
    token = val;
  }

  bool operator == (const BotMessage & rhs) const
  {
    if (!(down_load_task == rhs.down_load_task))
      return false;
    if (!(simulator_task == rhs.simulator_task))
      return false;
    if (!(update_task == rhs.update_task))
      return false;
    if (!(bot_task_types == rhs.bot_task_types))
      return false;
    if (!(token == rhs.token))
      return false;
    return true;
  }
  bool operator != (const BotMessage &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BotMessage & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(BotMessage &a, BotMessage &b);

typedef struct _NodeState__isset {
  _NodeState__isset() : node_id(false), cpu_state(false), mem_state(false) {}
  bool node_id;
  bool cpu_state;
  bool mem_state;
} _NodeState__isset;

class NodeState {
 public:

  static const char* ascii_fingerprint; // = "AB879940BD15B6B25691265F7384B271";
  static const uint8_t binary_fingerprint[16]; // = {0xAB,0x87,0x99,0x40,0xBD,0x15,0xB6,0xB2,0x56,0x91,0x26,0x5F,0x73,0x84,0xB2,0x71};

  NodeState() : node_id(), cpu_state(), mem_state() {
  }

  virtual ~NodeState() throw() {}

  std::string node_id;
  std::string cpu_state;
  std::string mem_state;

  _NodeState__isset __isset;

  void __set_node_id(const std::string& val) {
    node_id = val;
  }

  void __set_cpu_state(const std::string& val) {
    cpu_state = val;
  }

  void __set_mem_state(const std::string& val) {
    mem_state = val;
  }

  bool operator == (const NodeState & rhs) const
  {
    if (!(node_id == rhs.node_id))
      return false;
    if (!(cpu_state == rhs.cpu_state))
      return false;
    if (!(mem_state == rhs.mem_state))
      return false;
    return true;
  }
  bool operator != (const NodeState &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const NodeState & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(NodeState &a, NodeState &b);



#endif
