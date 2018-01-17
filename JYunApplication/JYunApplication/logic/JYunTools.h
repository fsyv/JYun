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
* @brief : �����࣬�ṩ����ʹ�÷���
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

class JYunTools
{
public:
	JYunTools();
	virtual ~JYunTools();

	//json����ת��ΪMap
	static QMap<QString, QString> jsonToMap(const QByteArray &bytearray);
	//Mapת��Ϊjson����
	static QByteArray mapToJson(const QMap<QString, QString> &map);
};

