/**
 * @Copyright 2012 Ganji Inc.
 * @file    conf/csqlhelper.h
 * @namespace no namespace
 * @version 1.0
 * @author  hongxiaodong
 * @date    2012-06-28
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#ifndef _GANJI_CRAWLER_WEBKIT_SPIDER_SPIDER_CONF_CSQLHELPER_H_
#define _GANJI_CRAWLER_WEBKIT_SPIDER_SPIDER_CONF_CSQLHELPER_H_

#include <QString>
//#include <QSqlDatabase>

#include <QtSql/QSqlDatabase>

/// @class mysql 数据库连接助手
class CSqlHelper {
 public:
  /// @brief 初始化mysql 连接。
  CSqlHelper();

  /// @brief 获取mysql database 连接对象。是一个可以自动重连的长连接。
  QSqlDatabase GetSqlDatabase();

 private:
  QString mysql_host_;
  QString mysql_port_;
  QString mysql_username_;
  QString mysql_password_;
  QString mysql_databasename_;
};

#endif  ///< _GANJI_CRAWLER_WEBKIT_SPIDER_SPIDER_CONF_CSQLHELPER_H_
