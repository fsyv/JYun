#include "stdafx.h"
#include "GlobalParameter.h"

#include "FileProcessManager.h"

using namespace std;

GlobalParameter *GlobalParameter::m_pInstancer = nullptr;
mutex GlobalParameter::m_mutex;

GlobalParameter::GlobalParameter():
	m_pProcessManager(nullptr)
{
}


GlobalParameter::~GlobalParameter()
{
	if (m_pProcessManager)
		delete m_pProcessManager;
	m_pProcessManager = nullptr;
}

GlobalParameter * GlobalParameter::getInstance()
{
	if (!m_pInstancer)
	{
		m_mutex.lock();
		if (!m_pInstancer)
			m_pInstancer = new GlobalParameter;
		m_mutex.unlock();
	}

	return m_pInstancer;
}

void GlobalParameter::destroyInstance()
{
	if (m_pInstancer)
	{
		m_mutex.lock();
		if (m_pInstancer)
			delete m_pInstancer;
		m_pInstancer = nullptr;
		m_mutex.unlock();
	}
}

bool GlobalParameter::initFileProcessManager()
{
	m_pProcessManager = new FileProcessManager;

	return true;
}

bool GlobalParameter::init()
{
	initFileProcessManager();

	return true;
}

FileProcessManager *GlobalParameter::getProcessManager() const
{
	return m_pProcessManager;
}

