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
* @brief : 配置文件实体类
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/4/6
**/

class JYunConfig
{
public:
	JYunConfig();
	~JYunConfig();

	bool load();
	bool reload();

	QString getConfigPath(QString config);
	QJsonValue getValue(QString config, QString key);

private:
	QString m_strSystemConfig;

	//name : path
	QMap<QString, QString> m_configs;
};

