#include "stdafx.h"
#include "GlobalParameter.h"

#include "User.h"
#include "JYunConfig.h"
#include "network\JYunTcp.h"

GlobalParameter *GlobalParameter::m_pInstancer = nullptr;
QMutex GlobalParameter::mutex;

GlobalParameter::GlobalParameter():
	m_pConfig(nullptr),
	m_pTcpNetwork(nullptr),
	m_pUser(nullptr)
{
}


GlobalParameter::~GlobalParameter()
{
	if (m_pConfig)
		delete m_pConfig;
	m_pConfig = nullptr;

	if (m_pTcpNetwork)
		delete m_pTcpNetwork;
	m_pTcpNetwork = nullptr;

	if (m_pUser)
		delete m_pUser;
	m_pUser = nullptr;
}

GlobalParameter * GlobalParameter::getInstance()
{
	if (!m_pInstancer)
	{
		mutex.lock();
		if (!m_pInstancer)
			m_pInstancer = new GlobalParameter;
		mutex.unlock();
	}

	return m_pInstancer;
}

void GlobalParameter::destroyInstance()
{
	if (m_pInstancer)
	{
		mutex.lock();
		if (m_pInstancer)
			delete m_pInstancer;
		m_pInstancer = nullptr;
		mutex.unlock();
	}
}

bool GlobalParameter::init()
{
	m_pUser = new User;
	m_pConfig = new JYunConfig;
	if (!m_pConfig->load())
		return false;

	m_pTcpNetwork = new JYunTcp;

	return true;
}

User * GlobalParameter::getUser() const
{
	return m_pUser;
}

JYunTcp * GlobalParameter::getTcpNetwork() const
{
	return m_pTcpNetwork;
}

JYunConfig * GlobalParameter::getConfig() const
{
	return m_pConfig;
}