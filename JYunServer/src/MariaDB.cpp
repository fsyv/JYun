#include "stdafx.h"
#include "MariaDB.h"

#include <mysql.h>

MariaDB::MariaDB(std::string host, int port, std::string username, std::string userpass, std::string database,
                 std::string charset) :
        m_pMysql(nullptr),
        m_eConnectState(ConnectState::NotConnect)
{
    m_MariaPrivate.host     = host;
    m_MariaPrivate.port     = port;
    m_MariaPrivate.username = username;
    m_MariaPrivate.userpass = userpass;
    m_MariaPrivate.database = database;
    m_MariaPrivate.charset  = charset;
}

MariaDB::~MariaDB() {

}

bool MariaDB::connect()
{
    m_pMysql = new MYSQL;

    mysql_init(m_pMysql);

//    int ret = mysql_real_connect(
//            m_pMysql,
//            m_MariaPrivate.host.c_str(),
//            m_MariaPrivate.username.c_str(),
//            m_MariaPrivate.userpass.c_str(),
//            m_MariaPrivate.database.c_str(),
//            m_MariaPrivate.port,
//            NULL,
//            0);

    return true;
}

bool MariaDB::disconnect() {
    return false;
}
