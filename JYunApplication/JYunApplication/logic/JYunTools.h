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
	//�����ļ�MD5
	static QByteArray fileMD5(QString filePath);
	//�����ַ���MD5
	static QByteArray stringMD5(QString string);
	//�ֽ��뱣��Ϊ����ͼƬ
	static void byteToLocalImage(const QString &filePath, const QByteArray &byte);
	//�ڴ��ַ�������
	static void *memstr(const void *src, quint64 src_len, const void *des);
};

