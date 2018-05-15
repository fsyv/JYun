#include "stdafx.h"
#include "JYunStringBuffer.h"

JYunStringBuffer::JYunStringBuffer(const memsize &size) :
	m_pBuffer(nullptr),
	m_allSize(1024uLL),
	m_size(0uLL)
{
	while (m_allSize < size && m_allSize < 1024 * 1024 * 1024)
		m_allSize <<= 1;

	m_initSize = m_allSize;

	m_pBuffer = new char[m_allSize + 1];
	memset(m_pBuffer, 0, m_allSize + 1);
}


JYunStringBuffer::~JYunStringBuffer()
{
}

void JYunStringBuffer::append(const char * szbuf)
{
	append(szbuf, strlen(szbuf));
}

void JYunStringBuffer::append(const char * buf, const int & len)
{
	if (len + m_size < m_allSize)
	{
		memcpy(m_pBuffer + m_size, buf, len);
		m_size += len;
	}
	else
	{
		while (m_allSize < len + m_size)
			m_allSize <<= 1;

		char *p = new char[m_allSize + 1];
		memset(p, 0, m_allSize + 1);

		memcpy(p, m_pBuffer, m_size);

		delete m_pBuffer;
		m_pBuffer = p;
	}
}

void JYunStringBuffer::alignmentBuffer()
{
	char *p = m_pBuffer;

	while ((p = (char *)memchr(p, 0xCF, m_size)) != nullptr)
	{
		int index = p - m_pBuffer;

		if (m_size - index >= sizeof(unsigned int))
		{
			unsigned int *beginFlag = (unsigned int *)p;
			if (*beginFlag == 0xAFAFAFCF)
			{
				for (int i = 0; i < m_size - index; ++i)
					m_pBuffer[i] = p[i + index];

				m_size -= index;

				break;
			}
			else
				continue;
		}
		else
			break;
	}

	if (!p)
		m_size = 0;

	adjustMemory();
}

void JYunStringBuffer::adjustMemory()
{
	if (m_allSize / 2 > m_size && m_allSize > m_initSize)
	{
		while (m_allSize > m_size && m_allSize > m_initSize)
			m_allSize >>= 1;

		char *p = new char[m_allSize + 1];
		memset(p, 0, m_allSize + 1);

		memcpy(p, m_pBuffer, m_size);

		delete m_pBuffer;
		m_pBuffer = p;
	}
}

memsize JYunStringBuffer::size() const
{
	return m_size;
}

Msg * JYunStringBuffer::getMsg()
{
	if (m_size > sizeof(Msg))
	{
		unsigned int *beginFlag = (unsigned int *)m_pBuffer;

		Msg *msg = nullptr;

		//Í·²¿
		if (*beginFlag == 0xAFAFAFCF)
		{
			MsgHead *msgHead = (MsgHead *)m_pBuffer;

			int msgLen = sizeof(Msg) + msgHead->m_iMsgLen;

			msg = (Msg *)new char[msgLen + 1];
			memset(msg, 0, msgLen + 1);

			memcpy(msg, m_pBuffer, msgLen);

			memset(m_pBuffer, 0, msgLen);
		}

		alignmentBuffer();
		return msg;
	}

	return nullptr;
}
