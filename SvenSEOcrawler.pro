#-------------------------------------------------
#
# Project created by QtCreator 2014-04-22T16:56:53
#
#-------------------------------------------------

QT       += core
QT       += webkit
QT       += gui
QT       += network
QT       += xml
QT       += sql
QT       += testlib


TARGET = SvenSEOcrawler
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cpageloader/cpageloader.cpp \
    cpageloader/cmynetworkaccessmanage.cpp \
    cpageloader/cmynetworkcookiejar.cpp \
    cpageloader/cmywebpage.cpp \
    conf/cconf.cpp \
    conf/csqlhelper.cpp \
    cpageloader/chttpget.cpp \
    cpageloader/chttppost.cpp \
    SEOTaskStream/bot_client.cpp \
    gen-cpp/octopus_crawler_constants.cpp \
    gen-cpp/octopus_crawler_types.cpp \
    gen-cpp/OctopusProxyService.cpp \
    SEOTaskStream/seodownloader.cpp \
    thrift/protocol/TBinaryProtocol.tcc \
    manager/csinglecraw.cpp

OTHER_FILES += \
    conf/user_agent.txt \
    conf/settings.ini

HEADERS += \
    cpageloader/cpageloader.h \
    cpageloader/cmynetworkaccessmanage.h \
    cpageloader/cmynetworkcookiejar.h \
    cpageloader/cmywebpage.h \
    conf/cconf.h \
    conf/csqlhelper.h \
    cpageloader/chttpget.h \
    cpageloader/chttppost.h \
    SEOTaskStream/bot_client.h \
    SEOTaskStream/long_short_conn.h \
    thrift/config.h \
    thrift/cxxfunctional.h \
    thrift/TApplicationException.h \
    thrift/TDispatchProcessor.h \
    thrift/Thrift.h \
    thrift/thrift-config.h \
    thrift/TLogging.h \
    thrift/TProcessor.h \
    thrift/TReflectionLocal.h \
    thrift/transport/PlatformSocket.h \
    thrift/transport/TBufferTransports.h \
    thrift/transport/TFDTransport.h \
    thrift/transport/TFileTransport.h \
    thrift/transport/THttpClient.h \
    thrift/transport/THttpServer.h \
    thrift/transport/THttpTransport.h \
    thrift/transport/TPipe.h \
    thrift/transport/TPipeServer.h \
    thrift/transport/TServerSocket.h \
    thrift/transport/TServerTransport.h \
    thrift/transport/TShortReadTransport.h \
    thrift/transport/TSimpleFileTransport.h \
    thrift/transport/TSocket.h \
    thrift/transport/TSocketPool.h \
    thrift/transport/TSSLServerSocket.h \
    thrift/transport/TSSLSocket.h \
    thrift/transport/TTransport.h \
    thrift/transport/TTransportException.h \
    thrift/transport/TTransportUtils.h \
    thrift/transport/TVirtualTransport.h \
    thrift/transport/TZlibTransport.h \
    thrift/concurrency/BoostThreadFactory.h \
    thrift/concurrency/Exception.h \
    thrift/concurrency/FunctionRunner.h \
    thrift/concurrency/Monitor.h \
    thrift/concurrency/Mutex.h \
    thrift/concurrency/PlatformThreadFactory.h \
    thrift/concurrency/PosixThreadFactory.h \
    thrift/concurrency/StdThreadFactory.h \
    thrift/concurrency/Thread.h \
    thrift/concurrency/ThreadManager.h \
    thrift/concurrency/TimerManager.h \
    thrift/concurrency/Util.h \
    thrift/protocol/TBase64Utils.h \
    thrift/protocol/TBinaryProtocol.h \
    thrift/protocol/TCompactProtocol.h \
    thrift/protocol/TDebugProtocol.h \
    thrift/protocol/TDenseProtocol.h \
    thrift/protocol/TJSONProtocol.h \
    thrift/protocol/TMultiplexedProtocol.h \
    thrift/protocol/TProtocol.h \
    thrift/protocol/TProtocolDecorator.h \
    thrift/protocol/TProtocolException.h \
    thrift/protocol/TProtocolTap.h \
    thrift/protocol/TVirtualProtocol.h \
    thrift/server/TNonblockingServer.h \
    thrift/server/TServer.h \
    thrift/server/TSimpleServer.h \
    thrift/server/TThreadedServer.h \
    thrift/server/TThreadPoolServer.h \
    thrift/windows/config.h \
    thrift/windows/force_inc.h \
    thrift/windows/GetTimeOfDay.h \
    thrift/windows/Operators.h \
    thrift/windows/SocketPair.h \
    thrift/windows/StdAfx.h \
    thrift/windows/TargetVersion.h \
    thrift/windows/TWinsockSingleton.h \
    thrift/windows/WinFcntl.h \
    gen-cpp/octopus_crawler_constants.h \
    gen-cpp/octopus_crawler_types.h \
    gen-cpp/OctopusProxyService.h \
    SEOTaskStream/seodownloader.h \
    manager/csinglecraw.h \
    manager/KeyWordItem.h

LIBS += -L$$PWD/../../../software/boost_1_49_0/bin/vc10/lib/ -llibboost_thread-vc100-mt-gd-1_49

INCLUDEPATH += $$PWD/../../../software/boost_1_49_0
DEPENDPATH += $$PWD/../../../software/boost_1_49_0

#win32:!win32-g++ PRE_TARGETDEPS += $$PWD/../../../software/boost_1_49_0/bin/vc10/lib/libboost_thread-vc100-mt-gd-1_49.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../software/boost_1_49_0/bin/vc10/lib/liblibboost_thread-vc100-mt-gd-1_49.a

LIBS += -L$$PWD/libs/ -llibevent

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

#win32:!win32-g++ PRE_TARGETDEPS += $$PWD/libs/libevent.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/liblibevent.a

LIBS += -L$$PWD/libs/ -llibthrift

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

#win32:!win32-g++ PRE_TARGETDEPS += $$PWD/libs/libthrift.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/liblibthrift.a

LIBS += -L$$PWD/libs/ -llibthriftnb

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

#win32:!win32-g++ PRE_TARGETDEPS += $$PWD/libs/libthriftnb.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/liblibthriftnb.a

LIBS += -L$$PWD/libs/ -lnet

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

#win32:!win32-g++ PRE_TARGETDEPS += $$PWD/libs/net.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libnet.a


INCLUDEPATH += $$PWD/libevent-2.0.21-stable/WIN32-Code/
INCLUDEPATH += $$PWD/libevent-2.0.21-stable/
INCLUDEPATH += $$PWD/libevent-2.0.21-stable/include/
