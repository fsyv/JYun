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
* @brief : ��Ϣ����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/4/6
**/

typedef unsigned long long int memsize;

struct Msg;

class JYunStringBuffer
{
public:
	JYunStringBuffer(const memsize &size = 1024);
	~JYunStringBuffer();

	// \0 ��β�Ĵ�
	void append(const char *szbuf);
	// ��\0 ��β�Ĵ�
	void append(const char *buf, const size_t &len);
	//��֤ÿ�ζ���ͷ������β
	void alignmentBuffer();
	//�����ڴ�
	void adjustMemory();

	Msg *getMsg();
private:
	char *m_pBuffer;

	//�ܳ���
	memsize m_allSize;
	//��ǰ����
	memsize m_size;
	//���Գ���
	memsize m_initSize;
};

