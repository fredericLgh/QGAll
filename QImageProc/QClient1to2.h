#pragma once
#include <QTcpSocket>
#include <thread>
#include <memory>
#include "sync_event.h"
#include "CommFile.h"
#include "ProcHeader.h"
#include <QObject>




class StructInspectResult;



class QClient1to2 :
	public QTcpSocket
{
	Q_OBJECT
public:
	QClient1to2(QObject* parent);
	~QClient1to2();
	void CloseSocket();
	void SendData(const char*pData,int Size);
	bool IsConnected();

	void TryConnect();
	bool SendMsg(long MsgType,LPVOID pBuf=NULL,long nSize=0);
	bool SendWarning(long Type, QString Info);
	bool SendHeartBeat(void);
	bool SendFrame(std::shared_ptr<StructInspectResult> pResult);

signals:
	void SengClientState(bool isok);
	void SendTrace(QString str);
	void SendStatus(int state);
	void SendCCDPos(long ViewID, long CCDPos);
	void SendNewCoilID(QString str);
	void SendHeartbeat(UINT message,long lParam = 0);

private:
	bool ConnectServer(const QString&LocalIP, const QString &ServerIP, const UINT ServerPort);

	void HeartBeatThread(void);//�̺߳���
	void HeartTimerProc(void);

	//********************�����ź�**********************

	unsigned int m_HeartCounter;   //��������
	squall::sync_event m_hGetResponse;    //�¼���4���ڵõ��Է��ķ�����
	bool m_QuitThread;
	std::thread m_HeartBeatThread;

private:
	void OnReceive();
	void DealWithHeartACK(unsigned long AckID);
	void DealWithNewCoilID(unsigned long CoilID);
	void DealWithEndCoilID(unsigned long CoilID);
	void DealWithSystemStatus(unsigned long status);
	void DealWithCurrentCoil(unsigned long CoilID,bool CoilInView);
	void DealWithNodeConfig();

	void DealWithSendParam();
	void DealWithApplyParam();

	void ReceiveXMLThread(void);
#ifdef __linux__
	bool ReceiveOneXML(int socketfd);
#endif

	void InformUI(UINT UserMsg);

private:
	//**************���ݽ����ñ���**************
	static const long m_FixedHeadSize = 8;     //��Ϣͷ����
	BYTE m_HeadBuf[m_FixedHeadSize];     //��Ϣͷ����
	long m_HeadRecvSize;    //��Ϣͷ������յĳ���

	long m_MessageType;     //��Ϣ����
	long m_FullBodySize;    //��Ϣ�峤��

	LPBYTE m_pBodyBuf;      //��Ϣ�建��
	long m_BodyMaxSize;
	long m_BodyRecvSize;    //��Ϣ�廹��Ҫ���յĳ���

	bool m_ReadHeadSign;    //��Ϣ��ȡ�����ж�
};

