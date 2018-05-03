#pragma once
#pragma execution_character_set("utf-8")

#include "MsgType.h"

struct MsgHead {
	unsigned int m_uiBeginFlag;     //开始校验位 0xAFAFAFCF
	MsgType m_eMsgType;             //消息类型
	int m_iMsgLen;                  //消息长度
};

struct Msg {
	MsgHead m_MsgHead;
	char m_aMsgData[0];
};