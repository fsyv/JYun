#ifndef STDAFX_H_H
#define STDAFX_H_H
/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 预编译头
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/3/17
**/

//C++ library
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>
#include <ctime>
#include <vector>
#include <chrono>
#include <sstream>
#include <functional>
#include <iostream>
#include <list>

//linux
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//libevent library
#include <event2/event.h>
#include <event2/bufferevent.h>

//maria
#include <mysql.h>
#endif 