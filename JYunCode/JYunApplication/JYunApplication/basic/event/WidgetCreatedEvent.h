#pragma once
#pragma execution_character_set("utf-8")

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 窗口创建完成事件
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/18
**/

#include <QEvent>

static const QEvent::Type WidgetCreated = (QEvent::Type)QEvent::registerEventType(QEvent::User + 123);

class WidgetCreatedEvent : public QEvent
{
public:
	WidgetCreatedEvent(QEvent::Type type);
	~WidgetCreatedEvent();
};

