#include "stdafx.h"
#include "JYunClient.h"

#include "JYunStringBuffer.h"
#include "tc_md5.h"

using namespace std;
using namespace chrono;
using namespace tars;

JYunClient::JYunClient(bufferevent *bev):
        m_pStringBuffer(nullptr),
        m_pMysql(nullptr)
{
    m_pBufferevent = bev;
    m_eState = ConnectionState::Confirm;
    m_SessionContactAction = minutes(1);

    m_pStringBuffer = new JYunStringBuffer();

    m_strUsername = "FSYV";
    initDB();
}

JYunClient::~JYunClient()
{
}

void JYunClient::init()
{
    sendConfirmMsg();
}

void JYunClient::initDB()
{
    string username = "root";
    string userpass = "root";
    string host = "127.0.0.1";
    string database = "JYUN";
    int port = 3306;
    string charset = "utf8";

    try{
        m_pMysql = new TC_Mysql(host, username, userpass, database, charset, port);
        m_pMysql->connect();
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
    }
}

void JYunClient::close()
{
    //客户端主动关闭了close请求
    m_eState = ConnectionState::Closing;
    m_eState = ConnectionState::Closed;
}

void JYunClient::readMsgBuffer()
{
    //同步
    char buf[512];
    int ret = 0;
    while ((ret = bufferevent_read(m_pBufferevent, buf, 512)) > 0)
    {
        buf[ret] = 0;
        m_pStringBuffer->append(buf, ret);
    }

    cout << "buffer size = "<<m_pStringBuffer->size() << endl;

    Msg *msg;
    while ((msg = m_pStringBuffer->getMsg()) != nullptr)
        readMsg(msg);

    //todo

    //printf("%s\n", m_stringstream.str().c_str());
    //异步
//    char buf[512];
//    int ret = 0;
//    while ((ret = bufferevent_read(m_pBufferevent, buf, 512)) > 0)
//    {
//        buf[ret] = 0;
//        m_pStringBuffer->append(buf, ret);
//    }
}

void JYunClient::checkState()
{
    //比较是否超时，如果超时设置state为false
}

JYunClient::ConnectionState JYunClient::state()
{
    checkState();
    return m_eState;
}

void JYunClient::refreshContactTime()
{
    m_LastContactTimeStamps = system_clock::now();
}

void JYunClient::run()
{
    m_StringBufferMutex.lock();

    cout << "buffer size = "<<m_pStringBuffer->size() << endl;


    Msg *msg;
    while ((msg = m_pStringBuffer->getMsg()) != nullptr)
        readMsg(msg);

    m_StringBufferMutex.unlock();
}

void JYunClient::registered(string username, string userpass)
{
    //插入TABLE_USER_PASS表
    //新建虚拟家目录表

    transform(username.begin(), username.end(), username.begin(), ::toupper);

    try{
        TC_Mysql::RECORD_DATA data;
        data["username"] = pair<TC_Mysql::FT, string>(TC_Mysql::DB_STR, username);
        data["userpass"] = pair<TC_Mysql::FT, string>(TC_Mysql::DB_STR, userpass);
        m_pMysql->insertRecord("TABLE_USER_PASS", data);
        data.clear();

        string tbname = "TABLE_" + username + "_HOME";

        stringstream sql;
        sql << "CREATE TABLE " << tbname << "("
            << "directory_md5 VARCHAR(32) PRIMARY KEY NOT NULL,"
            << "file_list TEXT"
            <<");";

        m_pMysql->execute(sql.str());

        string root_dir = username + ":/";
        string root_dir_md5 = TC_MD5::md5str(root_dir);
        data["directory_md5"] = pair<TC_Mysql::FT, string>(TC_Mysql::DB_STR, root_dir_md5);
        data["file_list"] = pair<TC_Mysql::FT, string>(TC_Mysql::DB_STR, "[]");

        sendRegisteredMsg(username, RegisteredMsg::Registered, RegisteredMsg::RegisteredSucced);
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
    }
}

void JYunClient::checkUsername(string username)
{
    transform(username.begin(), username.end(), username.begin(), ::toupper);

    try{
        stringstream sql;
        sql << "SELECT username FROM TABLE_USER_PASS WHERE username = '" << username << "';";

        TC_Mysql::MysqlData data = m_pMysql->queryRecord(sql.str());

        if(data.size() > 0)
            sendRegisteredMsg(username, RegisteredMsg::CheckUsername, RegisteredMsg::UsernameExisted);
        else
            sendRegisteredMsg(username, RegisteredMsg::CheckUsername, RegisteredMsg::UsernameNotExisted);
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
    }
}

int JYunClient::sendConfirmMsg()
{
    ConfirmMsg cMsg;
    cMsg.m_iConfirm = rand();

    char *p = new char[sizeof(Msg) + sizeof(ConfirmMsg) + 1];
    memset(p, 0, sizeof(Msg) + sizeof(ConfirmMsg) + 1);

    Msg *msg = (Msg *)p;
    msg->m_MsgHead.m_iMsgLen = sizeof(ConfirmMsg);
    msg->m_MsgHead.m_eMsgType = Ack_Confirm;
    memcpy(msg->m_aMsgData, &cMsg, sizeof(ConfirmMsg));

    int ret = 0;//sendMsg(msg);

    delete  []p;
    return ret;
}

int JYunClient::recvConfirmMsg(ConfirmMsg *msg)
{
    fprintf(stderr, "ConfirmMsg: %d\n", msg->m_iConfirm);

    if (m_eState == ConnectionState::Confirm)
        m_SessionContactAction = minutes(15);
    else
    {
        //异常
    }

    initDB();

    return 0;
}

int JYunClient::sendLoginMsg(std::string username, LoginMsg::LoginType loginType)
{
    LoginMsg cMsg;
    strncpy(cMsg.m_aUsername, username.c_str(), sizeof(cMsg.m_aUsername) - 1);
    cMsg.m_eLogin = loginType;

    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(LoginMsg) + 1];
    memset(msg, 0, sizeof(Msg) + sizeof(LoginMsg) + 1);

    msg->m_MsgHead.m_iMsgLen = sizeof(LoginMsg);
    msg->m_MsgHead.m_eMsgType = Put_Login;
    memcpy(msg->m_aMsgData, &cMsg, sizeof(LoginMsg));

    return sendMsg(msg);
}

int JYunClient::recvLoginMsg(LoginMsg *msg)
{
    fprintf(stderr, "username: %s\n", msg->m_aUsername);
    fprintf(stderr, "userpass: %s\n", msg->m_aPassword);

    string username = msg->m_aUsername;
    transform(username.begin(), username.end(), username.begin(), ::toupper);
    string userpass = msg->m_aPassword;
    m_strUsername = username;

    try{
        stringstream sql;
        sql << "SELECT userpass FROM TABLE_USER_PASS WHERE username = '" << username << "';";

        vector<map<string, string> > data = m_pMysql->queryRecord(sql.str()).data();

        if(data.size() > 0)
        {
            if(data[0]["userpass"] == userpass)
                return sendLoginMsg(msg->m_aUsername, LoginMsg::LoginType::LoginSuccess);
            else
                return sendLoginMsg(msg->m_aUsername, LoginMsg::LoginType::WrongPassword);
        }
        else
            return sendLoginMsg(msg->m_aUsername, LoginMsg::LoginType::UsernameNotExist);
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
        return sendLoginMsg(msg->m_aUsername, LoginMsg::LoginType::NotLogin);
    }
}

int JYunClient::sendRegisteredMsg(string username, RegisteredMsg::RegisteredType type,
                                  RegisteredMsg::RegisteredResult rusult)
{
    RegisteredMsg rMsg;
    strncpy(rMsg.m_aUsername, username.c_str(), sizeof(rMsg.m_aUsername) - 1);
    rMsg.m_eMsgType = type;
    rMsg.m_eResult = rusult;

    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(RegisteredMsg) + 1];
    memset(msg, 0, sizeof(Msg) + sizeof(RegisteredMsg) + 1);

    msg->m_MsgHead.m_iMsgLen = sizeof(RegisteredMsg);
    msg->m_MsgHead.m_eMsgType = Put_Registered;
    memcpy(msg->m_aMsgData, &rMsg, sizeof(RegisteredMsg));

    return sendMsg(msg);
}

int JYunClient::recvRegisteredMsg(RegisteredMsg *rmsg)
{
    if(!rmsg)
        return 0;

    fprintf(stderr, "username: %s\n", rmsg->m_aUsername);

    switch (rmsg->m_eMsgType){
        case RegisteredMsg::CheckUsername:
            checkUsername(rmsg->m_aUsername);
            break;
        case RegisteredMsg::Registered:
            registered(rmsg->m_aUsername, rmsg->m_aPassword);
            break;
    }
    return 0;
}

int JYunClient::sendGetUserHeadMd5Msg(string username, string headMd5)
{
    GetUserHeadMd5 gMsg;
    strncpy(gMsg.m_aUsername, username.c_str(), sizeof(gMsg.m_aUsername) - 1);
    strncpy(gMsg.m_aMd5, headMd5.c_str(), sizeof(gMsg.m_aMd5) - 1);

    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(GetUserHeadMd5) + 1];
    memset(msg, 0, sizeof(Msg) + sizeof(GetUserHeadMd5) + 1);

    msg->m_MsgHead.m_iMsgLen = sizeof(GetUserHeadMd5);
    msg->m_MsgHead.m_eMsgType = Get_HeadMd5;
    memcpy(msg->m_aMsgData, &gMsg, sizeof(GetUserHeadMd5));

    return sendMsg(msg);
}

int JYunClient::recvGetUserHeadMd5Msg(GetUserHeadMd5 *gmsg)
{
    string username = gmsg->m_aUsername;
    transform(username.begin(), username.end(), username.begin(), ::toupper);

    fprintf(stderr, "recvGetUserHeadMd5Msg username: %s\n", gmsg->m_aUsername);

    try{
        stringstream sql;
        sql << "SELECT head_md5 FROM TABLE_USER_HEAD WHERE username = '" << username << "';";

        vector<map<string, string> > data = m_pMysql->queryRecord(sql.str()).data();
        string head_md5 = data[0]["head_md5"];

        return sendGetUserHeadMd5Msg(gmsg->m_aUsername, head_md5);
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
        return sendGetUserHeadMd5Msg(gmsg->m_aUsername, "29b94408c3c1fd7aa4013d99911dd5a9");
    }
}

int JYunClient::sendModifypassMsg(string username, ModifypassMsg::ModifyResult result)
{
    ModifypassMsg mMsg;
    strncpy(mMsg.m_aUsername, username.c_str(), sizeof(mMsg.m_aUsername) - 1);
    mMsg.m_eResult = result;

    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ModifypassMsg) + 1];
    memset(msg, 0, sizeof(Msg) + sizeof(ModifypassMsg) + 1);

    msg->m_MsgHead.m_iMsgLen = sizeof(ModifypassMsg);
    msg->m_MsgHead.m_eMsgType = Put_Registered;
    memcpy(msg->m_aMsgData, &mMsg, sizeof(ModifypassMsg));

    return sendMsg(msg);
}

int JYunClient::recvModifypassMsg(ModifypassMsg *mmsg)
{
    fprintf(stderr, "username: %s\n", mmsg->m_aUsername);
    fprintf(stderr, "userpass: %s\n", mmsg->m_aPassword);
    fprintf(stderr, "md5: %s\n", mmsg->m_aMd5);

    string username = mmsg->m_aUsername;
    transform(username.begin(), username.end(), username.begin(), ::toupper);
    string userpass = mmsg->m_aPassword;
    string md5 = mmsg->m_aMd5;

    try{
        stringstream sql;
        sql << "UPDATE TABLE_USER_PASS SET userpass = '" << userpass << "' WHERE username = '" << username << "';";
        m_pMysql->execute(sql.str());

        sql = stringstream("");
        sql << "UPDATE TABLE_USER_HEAD SET head_md5 = '" << md5 << "' WHERE username = '" << username << "';";

        cout << sql.str() << endl;

        m_pMysql->execute(sql.str());

        return sendModifypassMsg(mmsg->m_aUsername, ModifypassMsg::Succed);
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
        return sendModifypassMsg(mmsg->m_aUsername, ModifypassMsg::Failed);
    }
}

int JYunClient::sendGetFileListsMsg(const string &path)
{
    cout << "path = " << path;

    GetFileListsMsg *gMsg = (GetFileListsMsg *)new char[path.length() + 1];
    strncpy(gMsg->m_aData, path.c_str(), path.length());

    Msg *msg = (Msg *)new char[sizeof(Msg) + path.length() + 1];
    memset(msg, 0, sizeof(Msg) + path.length() + 1);

    msg->m_MsgHead.m_iMsgLen = path.length();
    msg->m_MsgHead.m_eMsgType = Get_FileLists;
    memcpy(msg->m_aMsgData, &gMsg, path.length());

    delete gMsg;

    return sendMsg(msg);
}

int JYunClient::recvGetFileListsMsg(GetFileListsMsg *gmsg)
{
    string dir_md5 = gmsg->m_aData;
    cout << "dir_md5 = " <<dir_md5 << endl;
    string tbname = "TABLE_" + m_strUsername + "_HOME";

    try{
        stringstream sql;
        sql << "SELECT file_list FROM "<< tbname <<" WHERE directory_md5 = '" << dir_md5 << "';";

        TC_Mysql::MysqlData data = m_pMysql->queryRecord(sql.str());

        if(data.size() > 0)
            return sendGetFileListsMsg(data[0]["file_list"]);
        else
            return sendGetFileListsMsg("[]");
    }
    catch (const TC_Mysql_Exception &e){
        printf("Mysql error: %s", e.what());
        return sendGetFileListsMsg("[]");
    }
}

int JYunClient::sendMsg(Msg *msg)
{
    msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFCF;

    return send(bufferevent_getfd(m_pBufferevent), (void *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen, 0);

    //return bufferevent_write(m_pBufferevent, (void *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);
}

int JYunClient::readMsg(Msg *msg) {

    int ret = 0;
    switch (msg->m_MsgHead.m_eMsgType){
        case Ack_Confirm:
            ret = recvConfirmMsg((ConfirmMsg *)msg->m_aMsgData);
            break;
        case Put_Login:
            ret = recvLoginMsg((LoginMsg *)msg->m_aMsgData);
            break;
        case Put_Registered:
            ret = recvRegisteredMsg((RegisteredMsg *)msg->m_aMsgData);
            break;
        case Get_HeadMd5:
            ret = recvGetUserHeadMd5Msg((GetUserHeadMd5 *)msg->m_aMsgData);
            break;
        case Put_Modifypass:
            ret = recvModifypassMsg((ModifypassMsg *)msg->m_aMsgData);
            break;
        case Get_FileLists:
            ret = recvGetFileListsMsg((GetFileListsMsg *)msg->m_aMsgData);
            break;
    }

    return ret;
}



