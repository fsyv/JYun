#include "stdafx.h"
#include "BasicNetwork.h"


BasicNetwork::BasicNetwork(QObject *parent):
	QTcpSocket(parent)
{
}


BasicNetwork::~BasicNetwork()
{
}
