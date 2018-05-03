#ifndef JYUNCODE_MARIADB_H
#define JYUNCODE_MARIADB_H
/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : Maria数据库
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/04/08
**/

typedef struct st_mysql MYSQL;

class MariaPrivate{
private:
    std::string host;
    int port;
    std::string username;
    std::string userpass;
    std::string database;
    std::string charset;

    friend class MariaDB;
};

class MariaDB {
public:
    enum class ConnectState{
        NotConnect = 0,     //未连接
        Connecting,         //正在连接
        Connected,          //已连接
        Closing,            //正在关闭
        Closed              //已关闭
    };

    explicit MariaDB(
            std::string host, int port, std::string username,
            std::string userpass, std::string database, std::string charset
    );
    virtual ~MariaDB();

    bool connect();
    bool disconnect();
private:
    MYSQL *m_pMysql;
    MariaPrivate m_MariaPrivate;
    ConnectState m_eConnectState;
};


#endif //JYUNCODE_MARIADB_H
