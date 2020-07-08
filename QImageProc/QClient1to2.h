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

	void HeartBeatThread(void);//线程函数
	void HeartTimerProc(void);

	//********************心跳信号**********************

	unsigned int m_HeartCounter;   //心跳计数
	squall::sync_event m_hGetResponse;    //事件（4秒内得到对方的反馈）
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
	//**************数据接收用变量**************
	static const long m_FixedHeadSize = 8;     //消息头长度
	BYTE m_HeadBuf[m_FixedHeadSize];     //消息头缓存
	long m_HeadRecvSize;    //消息头还需接收的长度

	long m_MessageType;     //消息类型
	long m_FullBodySize;    //消息体长度

	LPBYTE m_pBodyBuf;      //消息体缓存
	long m_BodyMaxSize;
	long m_BodyRecvSize;    //消息体还需要接收的长度

	bool m_ReadHeadSign;    //消息读取部分判断
};

