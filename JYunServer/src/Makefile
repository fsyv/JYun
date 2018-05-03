# This is Makefile
###############################################################################
#                 JJJJJJJ   YY    YY                                          #
#                   JJJ      YY  YY                                           #
#                   JJJ       YYYY     u      u    n  nnnn                    #
#                   JJJ        YY      u     uu    n n   nn                   #
#             JJJ  JJJ         YY      uu   u u    nn     n                   #
#               JJJJJ          YY       uuuu  u    n      n                   #
###############################################################################
# @brief : JYun编译脚本
# @author : fsyv
# @email : fsyv@gmail.com
# @date : 2018/3/17
##

TARGET=JYunServer

# C
CC=gcc
CSUFFIX=c
CFLAGS=-g -Wall -std=c11

# C++
CXX=g++
CXXSUFFIX=cpp
CXXFLAGS=-g -Wall -std=c++11

# 预编译文件
PCH_H=stdafx.h
PCH=$(PCH_H).gch

LIBEVENT=../lib/libevnt
LOG4CPP=../lib/log4cpp
MARIADB=../lib/mariadb-connector

LIBS=-L$(LIBEVENT)/.libs -levent \
     -L$(MARIADB)/libmariadb -lmariadb \
     -lpthread

INC=-I$(LIBEVENT)/include \
    -I$(MARIADB)/include

SRC=$(wildcard *.$(CXXSUFFIX))
OBJS=$(patsubst %.$(CXXSUFFIX), %.o, $(notdir $(SRC)))

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INC) $(LIBS)

%.o:%.$(CXXSUFFIX)
	$(CXX) $(CXXFLAGS) -c $< $(INC) $(LIBS)

#$(PCH):$(PCH_H)
#	$(CXX) -x c++-header -c $(PCH_H) $(CXXFLAGS) $(INC) -o $(PCH)

clean:
	rm -rf $(OBJS) $(PCH)

all:
	@echo $(SRC)
	@echo $(OBJS)