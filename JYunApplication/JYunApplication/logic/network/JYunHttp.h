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
* @brief : http服务
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

class JYunHttp : public QObject
{
	Q_OBJECT
public:
	explicit JYunHttp();
	virtual ~JYunHttp();

	QMap<QString, QString> login(const QString &username, const QString &userpass);
	//获取头像
	void getHead();

private:
	QNetworkAccessManager *m_pManager;
	QUrl m_url;
};

