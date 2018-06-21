#include "stdafx.h"
#include "FileProcess.h"

FileProcess::FileProcess()
{
	m_pSocket = new QTcpSocket;

	QObject::connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
	QObject::connect(m_pSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
	QObject::connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}


FileProcess::~FileProcess()
{
}

void FileProcess::connect()
{
	m_pSocket->connectToHost("127.0.0.1", m_usPort);
}

void FileProcess::disconnect()
{
	m_pSocket->disconnect();
}

void FileProcess::request()
{
}

void FileProcess::setPort(quint16 port)
{
	m_usPort = port;
}

void FileProcess::readMessage()
{
}

void FileProcess::displayState(QAbstractSocket::SocketState)
{
}

void FileProcess::displayError(QAbstractSocket::SocketError)
{
}
