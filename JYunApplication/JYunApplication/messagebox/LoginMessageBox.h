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
* @brief : ��¼��ʾ��
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/5
**/
#include "basic\BasicMessageBox.h"

class LoginMessageBox : public BasicMessageBox
{
	Q_OBJECT
public:
	explicit LoginMessageBox();
	~LoginMessageBox();

	//��¼ȷ�ϵȴ�ʱ��
	static bool waitForConfirm(int msec);
	//���ؽ��
	bool isLogin();

protected:
	//�����϶��¼�
	///////////////////////////////////////////////////
	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	///////////////////////////////////////////////////

	void initWidget();
	void conn();
	void startTimer(int msec);
	void stopTimer();

	void timerEvent(QTimerEvent *e)override;
private:
	QFrame *m_pMainFrame;
	QLabel *m_pPicture;
	QPushButton *m_pCancel;
	bool m_bRet;
	int m_iTimerID;
};

