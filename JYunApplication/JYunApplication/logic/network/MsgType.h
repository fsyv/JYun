#pragma once
#pragma execution_character_set("utf-8")

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : ����ͨ����Ϣ����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/21
**/

//��Ϣ����
enum MsgType {
	Ack_Confirm = 0,	    //�����֤
	Ack_OK,                 //ȷ���ɹ�
	Ack_Error,              //ȷ������

	Get_SystemConfig,       //��ȡϵͳ����
	Get_CheckUsername,      //����û����Ƿ����
	Get_UserInfo,           //��ȡ�û���Ϣ
	Get_UserHead,			//��ȡ�û�ͷ��
	Get_HeadMd5,            //��ȡͷ���Md5
	Get_FileMd5,            //��ȡ�ļ�Md5
	Get_DownloadFile,		//�����ļ�
	Get_FileLists,          //�ļ��б�

	Put_Login,              //��¼
	Put_Registered,         //ע��
	Put_Modifypass,         //�޸�����
	Put_UploadHead,         //�ϴ�ͷ��
	Put_UploadFile			//�ϴ�
};

//����У��
struct ConfirmMsg {
	int m_iConfirm;
};

//�ɹ�Ӧ��
struct OkMsg {
	int m_iOk;
};

//����Ӧ��
struct ErrorMsg {
	int m_iErrno;   //������
};

struct LoginMsg {
	char m_aUsername[32];		//�û���
	char m_aPassword[128];		//����
	enum LoginType {
		NotLogin = 0,			//û�е�¼
		Logout,					//ע��
		UsernameNotExist,		//�û���������
		WrongPassword,			//�������
		LoginSuccess			//��¼�ɹ�
	}m_eLogin;					//��¼״̬
};

struct RegisteredMsg {
	char m_aUsername[32];		//�û���
	char m_aPassword[128];		//����
	enum RegisteredType {
		CheckUsername,			//����û���
		Registered				//ע��
	}m_eMsgType;	
	enum RegisteredResult {
		UsernameExisted,		//�û�������
		UsernameNotExisted,		//�û���������

		RegisteredSucced,		//ע��ɹ�
		RegisteredFailed		//ע��ʧ��
	}m_eResult;
};

struct GetUserHead {
	char m_aUsername[32];
	char m_aHeadUrl[512];
};

struct GetUserHeadMd5 {
	char m_aUsername[32];
	char m_aMd5[128];
};