#ifndef MSGTYPE_H_
#define MSGTYPE_H_

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 网络通信消息类型 	
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/21
**/

//消息类型
enum MsgType {
	Ack_Confirm = 0,	    //身份验证
	Ack_OK,                 //确定成功
	Ack_Error,              //确定错误

	Get_SystemConfig,       //获取系统配置
	Get_CheckUsername,      //检测用户名是否存在
    Get_UserInfo,           //获取用户信息
	Get_UserHead,			//获取用户头像
    Get_HeadMd5,            //获取头像的Md5
    Get_FileMd5,            //获取文件Md5
	Get_DownloadFile,		//下载文件
    Get_FileLists,          //文件列表

    Put_Login,              //登录
    Put_Registered,         //注册
    Put_Modifypass,         //修改密码
    Put_UploadHead,         //上传头像
	Put_UploadFile			//上传
};

//连接校验
struct ConfirmMsg{
    int m_iConfirm;
};

//成功应答
struct OkMsg{
    int m_iOk;
};

//错误应答
struct ErrorMsg{
    int m_iErrno;   //错误编号
};

struct LoginMsg {
	char m_aUsername[32];		//用户名
	char m_aPassword[128];		//密码
	enum LoginType {
		NotLogin = 0,			//没有登录
		Logout,					//注销
		UsernameNotExist,		//用户名不存在
		WrongPassword,			//密码错误
		LoginSuccess			//登录成功
	}m_eLogin;					//登录状态
};

struct RegisteredMsg {
	char m_aUsername[32];		//用户名
	char m_aPassword[128];		//密码
	enum RegisteredType {
		CheckUsername,			//检查用户名
		Registered				//注册
	}m_eMsgType;	
	enum RegisteredResult {
		UsernameExisted,		//用户名存在
		UsernameNotExisted,		//用户名不存在

		RegisteredSucced,		//注册成功
		RegisteredFailed		//注册失败
	}m_eResult;
};

struct GetUserHead {
	char m_aUsername[32];
	char m_aHeadUrl[512];
};

#endif //MSGTYPE_H_