/**
 * @Copyright 2012 Ganji Inc.
 * @file    conf/csqlhelper.cpp
 * @namespace no namespace
 * @version 1.0
 * @author  hongxiaodong
 * @date    2012-06-28
 *
 * 改动程序后， 请使用tools/cpplint/cpplint.py 检查代码是否符合编码规范!
 * 遵循的编码规范请参考: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * Change Log:
 */

#include <QDebug>
#include <QSettings>
#include "./csqlhelper.h"
#include "./cconf.h"

CSqlHelper::CSqlHelper() {
  // 从配置项类获取数据库连接配置。
  QSettings settings(CConf::GetConfPath("settings.ini"), QSettings::IniFormat);

  this->mysql_host_ = settings.value("/Db/db_host_name").toString();
  qDebug() << "DB host:" << this->mysql_host_;
  this->mysql_port_ = settings.value("/Db/db_port").toString();
  qDebug() << "DB port:" << this->mysql_port_;
  this->mysql_username_ = settings.value("/Db/db_user_name").toString();
  qDebug() << "DB user:" << this->mysql_username_;
  this->mysql_password_ = settings.value("/Db/db_password").toString();
  qDebug() << "DB pwd: " << this->mysql_password_;
  this->mysql_databasename_ = settings.value("/Db/db_database_name").toString();
  qDebug() << "DB db_name:" << this->mysql_databasename_;

  // 测试数据库连接
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "crawler02");
  db.setHostName(this->mysql_host_);
  db.setPort(this->mysql_port_.toInt());
  db.setUserName(this->mysql_username_);
  db.setPassword(this->mysql_password_);
  db.setDatabaseName(this->mysql_databasename_);
  bool db_succ = db.open();
  if (db_succ == false) {
    qDebug() << "Error CSqlHelper::GetSqlDatabase() Can not connect to mysql server.";
    exit(-1);
  } else {
    qDebug() << "CSqlHelper::GetSqlDatabase() Connect to mysql server success.";
  }
}

QSqlDatabase CSqlHelper::GetSqlDatabase() {
  if (QSqlDatabase::contains("crawler02")) {
    QSqlDatabase db = QSqlDatabase::database("crawler02");
    if (db.isOpenError() == false) {
      return db;
    }
  }
  // 数据库连接
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "crawler02");
  db.setHostName(this->mysql_host_);
  db.setPort(this->mysql_port_.toInt());
  db.setUserName(this->mysql_username_);
  db.setPassword(this->mysql_password_);
  db.setDatabaseName(this->mysql_databasename_);
  bool db_succ = db.open();
  if (db_succ == false) {
    qDebug() << "Error CSqlHelper::GetSqlDatabase() Can not connect to mysql server.";
    // exit(-1);
  } else {
    qDebug() << "CSqlHelper::GetSqlDatabase() Connect to mysql server success.";
  }
  return db;
}
