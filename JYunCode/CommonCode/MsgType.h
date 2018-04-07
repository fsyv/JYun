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
typedef enum _MsgType {
	Ack_Confirm = 0,	    //身份验证
	Ack_OK,                 //确定成功
	Ack_Error,              //确定错误

	Get_SystemConfig,       //获取系统配置
	Get_CheckUsername,      //检测用户名是否存在
    Get_UserInfo,           //获取用户信息
    Get_HeadMd5,            //获取头像的Md5
    Get_FileMd5,            //获取文件Md5
	Get_DownloadFile,		//下载文件
    Get_FileLists,          //文件列表

    Put_Login,              //登录
    Put_Registered,         //注册
    Put_Modifypass,         //修改密码
    Put_UploadHead,         //上传头像
	Put_UploadFile			//上传
}MsgType;

//连接校验
typedef struct _ConfirmMsg{
    int m_iConfirm;
}ConfirmMsg_t;

//成功应答
typedef struct _OkMsg{
    int m_iOk;
}OkMsg;

//错误应答
typedef struct _ErrorMsg{
    int m_iErrno;   //错误编号
}ErrorMsg;


#endif