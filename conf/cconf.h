/**
 * @Copyright 2012 Ganji Inc.
 * @file    conf/cconf.h
 * @namespace no namespace
 * @version 1.0
 * @author  hongxiaodong
 * @date    2012-06-28
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#ifndef _GANJI_CRAWLER_WEBKIT_SPIDER_SPIDER_CONF_CCONF_H_
#define _GANJI_CRAWLER_WEBKIT_SPIDER_SPIDER_CONF_CCONF_H_

#include <QObject>
#include <QString>
#include <QMap>

/// @class CConf
/// @brief 配置类，用来管理程序的配置项
class CConf : public QObject
{
 Q_OBJECT
public:
  /// @brief 初始化配置类。
  explicit CConf(QObject *parent = 0);

  /// @brief 根据配置项名称，获取配置值。
  /// @param[in] conf_name, 配置项名称。
  static QString GetConfPath(QString conf_name);

 private:
  static QMap<QString, QString> *conf_map_;
};

#endif  ///< _GANJI_CRAWLER_WEBKIT_SPIDER_SPIDER_CONF_CCONF_H_
