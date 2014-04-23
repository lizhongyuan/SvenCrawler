/**
 * @Copyright 2012 Ganji Inc.
 * @file    conf/cconf.cpp
 * @namespace no namespace
 * @version 1.0
 * @author  hongxiaodong
 * @date    2012-06-28
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#include "cconf.h"
#include <QtCore>

QMap<QString, QString> *CConf::conf_map_ = NULL;
CConf GLOBAL_CCONF;

CConf::CConf(QObject *parent) : QObject(parent)
{
  // 初始化配置项。
  if (CConf::conf_map_ == NULL) {
    CConf::conf_map_ = new QMap<QString, QString>();
    (*CConf::conf_map_)["settings.ini"]   = "./conf/settings.ini";
    (*CConf::conf_map_)["refuse_url.txt"]  = "./conf/refuse_url.txt";
    (*CConf::conf_map_)["user_agent.txt"] = "./conf/user_agent.txt";
    (*CConf::conf_map_)["known_header.xml"]   = "./conf/known_header.xml";
  }
}

QString CConf::GetConfPath(QString conf_name) {
  // 获取配置项，如果没有该配置项，则打印警告。
  QString conf_path = (*CConf::conf_map_)[conf_name];
  if (conf_path == "") {
    qDebug() << "Error CConf::GetConfPath Unknown conf_name: " << conf_name;
    exit(-1);
  }
  return conf_path;
}
