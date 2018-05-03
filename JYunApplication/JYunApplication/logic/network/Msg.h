#pragma once
#pragma execution_character_set("utf-8")

#include "MsgType.h"

struct MsgHead {
	unsigned int m_uiBeginFlag;     //��ʼУ��λ 0xAFAFAFCF
	MsgType m_eMsgType;             //��Ϣ����
	int m_iMsgLen;                  //��Ϣ����
};

struct Msg {
	MsgHead m_MsgHead;
	char m_aMsgData[0];
};