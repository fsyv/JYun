#ifndef JYUNCLIENT_H_
#define JYUNCLIENT_H_
/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 客户端对象
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/3/18
**/

#include "ThreadObject.h"

#include "Msg.h"

#include "tc_mysql.h"

struct bufferevent;
class JYunStringBuffer;


class JYunClient : public ThreadObject{
    using string = std::string;

public:
    explicit JYunClient(bufferevent *bev);
    ~JYunClient();

    enum class ConnectionState{
        Confirm = 0,    //等待确认
        Connected,      //已连接
        Closing,        //正在关闭
        Closed,         //已经关闭
        Timeout         //超时
    };

    void init();
    void initDB();
    void close();
    void checkState();
    ConnectionState state();
    //刷新通信时间
    void refreshContactTime();
    void readMsgBuffer();

    //先使用多继承，以后修改为函数
    void run();

protected:
    void registered(string username, string userpass);
    void checkUsername(string username);

protected:
    int sendConfirmMsg();
    int recvConfirmMsg(ConfirmMsg *msg);

    int sendLoginMsg(string username, LoginMsg::LoginType loginType);
    int recvLoginMsg(LoginMsg *msg);

	int sendRegisteredMsg(string username, RegisteredMsg::RegisteredType type, RegisteredMsg::RegisteredResult rusult);
	int recvRegisteredMsg(RegisteredMsg *rmsg);

	int sendGetUserHeadMd5Msg(string username, string headMd5);
	int recvGetUserHeadMd5Msg(GetUserHeadMd5 *gmsg);

    int sendModifypassMsg(string username, ModifypassMsg::ModifyResult result);
    int recvModifypassMsg(ModifypassMsg *mmsg);

	int sendGetFileListsMsg(const string &path);
	int recvGetFileListsMsg(GetFileListsMsg *gmsg);

    int sendMsg(Msg *msg);
    int readMsg(Msg *msg);

private:
    // 客户端信息
    bufferevent *m_pBufferevent;
    unsigned int m_uiIP;
    unsigned short m_ui16Port;
    //客户端连接的状态，服务端会定期清理m_bState为false的客户端
    ConnectionState m_eState;
    //消息缓存
    JYunStringBuffer *m_pStringBuffer;
    std::mutex m_StringBufferMutex;

    // 上次通信时间
    // 用于做session
    std::chrono::system_clock::time_point m_LastContactTimeStamps;
    // session有效时间(ms)
    // 未通过验证的连接有效期为1分钟
    // 通过验证的连接有效期为15分钟
    std::chrono::minutes m_SessionContactAction;

    string m_strUsername;
    tars::TC_Mysql *m_pMysql;
};


#endif //JYUNCLIENT_H_
