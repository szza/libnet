# Install script for directory: /mnt/hgfs/self_study/MyPro/libnet/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/mnt/hgfs/self_study/MyPro/libnet/build/lib/libsrc.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/mnt/hgfs/self_study/MyPro/libnet/src/Acceptor.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Buffer.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Callbacks.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Channel.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Connector.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/CountDownLatch.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/EPoller.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/EventLoop.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/EventLoopThread.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/InetAddress.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Logger.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/noncopyable.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/TcpClient.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/TcpConnection.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/TcpServer.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/TcpServerSingle.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/ThreadPool.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Timer.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/TimerQueue.h"
    "/mnt/hgfs/self_study/MyPro/libnet/src/Timestamp.h"
    )
endif()

