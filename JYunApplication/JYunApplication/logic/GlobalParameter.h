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
* @brief : 全局变量，用于保存：用户，网络，配置文件信息
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/4/6
**/

class User;
class JYunTcp;
class JYunConfig;

class GlobalParameter
{
public:
	static GlobalParameter *getInstance();
	static void destroyInstance();

	bool init();

	User *getUser() const;
	JYunTcp *getTcpNetwork() const;
	JYunConfig *getConfig() const;
private:
	GlobalParameter();
	~GlobalParameter();

	JYunConfig *m_pConfig;
	JYunTcp *m_pTcpNetwork;
	User *m_pUser;

	static GlobalParameter *m_pInstancer;
	static QMutex mutex;
};

