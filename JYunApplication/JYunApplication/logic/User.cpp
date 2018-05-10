#include "stdafx.h"
#include "User.h"

User::User()
{
}


User::~User()
{
}

void User::setUsername(const QString & username)
{
	m_stUsername = username;
}

QString & User::getUsername()
{
	return m_stUsername;
}

void User::setDownloadPath(const QString & path)
{
	m_strDownloadPath = path;
}

QString & User::getDownloadPath()
{
	return m_strDownloadPath;
}
