#include "stdafx.h"
#include "User.h"

User *User::m_pInstanceUser = nullptr;
QMutex User::mutex;

User::User()
{
}


User::~User()
{
}

User * User::getInstance()
{
	if (!m_pInstanceUser)
	{
		mutex.lock();
		if(!m_pInstanceUser)
			m_pInstanceUser = new User;
		mutex.unlock();
	}

	return m_pInstanceUser;
}

void User::destroyInstance()
{
	if (m_pInstanceUser)
	{
		mutex.lock();
		if (m_pInstanceUser)
			delete m_pInstanceUser;
		m_pInstanceUser = nullptr;
		mutex.unlock();
	}
}

void User::setUsername(const QString & username)
{
	m_stUsername = username;
}

QString & User::getUsername()
{
	return m_stUsername;
}
