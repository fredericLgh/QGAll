#include "QClient1to2.h"
#include "QImageProcApp.h"
#include "NetMsg.h"
#include "QImageProcWidget.h"

QClient1to2::QClient1to2(QObject* parent)
	:QTcpSocket(parent)
{
	m_HeadRecvSize = m_FixedHeadSize;
	m_MessageType = 0;
	m_FullBodySize = 0;
	m_pBodyBuf = nullptr;
	m_BodyMaxSize = 0;
	m_BodyRecvSize = 0;
	m_ReadHeadSign = true;

	//************* 心跳信号初始化 *************
	m_HeartCounter = 0;
	m_hGetResponse.reset();

	//************* 心跳线程 *************
	m_QuitThread = false;
	m_HeartBeatThread = std::thread(&QClient1to2::HeartBeatThread, this);



}
QClient1to2::~QClient1to2()
{
}

void QClient1to2::CloseSocket()
{
}

void QClient1to2::SendData(const char * pData, int Size)
{
}

bool QClient1to2::IsConnected()
{
	return false;
}

void QClient1to2::TryConnect()
{
	if (IsConnected())
	{
		return;
	}
	else
	{
		m_HeadRecvSize = m_FixedHeadSize;
		m_MessageType = 0;
		m_FullBodySize = 0;
		m_BodyRecvSize = 0;
		m_ReadHeadSign = true;

	}

	if (ConnectServer(pApp->m_ClientIP,pApp->m_ServerIP,NETPORT_1TO2))
	{
		SendTrace(QString::fromLocal8Bit("---------- 尝试连接 %1 ----------").arg(pApp->m_ServerIP));
	}else
	{
		SendTrace(QString::fromLocal8Bit("---------- IP（%1）失败 ----------").arg(pApp->m_ClientIP));
	}

}

bool QClient1to2::SendMsg(long MsgType, LPVOID pBuf, long nSize)
{
	return false;
}

bool QClient1to2::SendWarning(long Type, QString Info)
{
	return false;
}

bool QClient1to2::SendHeartBeat(void)
{
	return false;
}

bool QClient1to2::SendFrame(std::shared_ptr<StructInspectResult> pResult)
{
	return false;
}

bool QClient1to2::ConnectServer(const QString & LocalIP, const QString & ServerIP, const UINT ServerPort)
{
	return false;
}

void QClient1to2::HeartBeatThread(void)
{
	std::chrono::milliseconds dura(100);
	while (1)
	{
		for (int i = 0; i < 150;i++)
		{
			std::this_thread::sleep_for(dura);
			if(m_QuitThread) break;
		}
		if(m_QuitThread) break;
		HeartTimerProc();
	}
}

void QClient1to2::HeartTimerProc(void)
{
	if (state() == QAbstractSocket::ConnectedState)
	{
		emit SendHeartbeat(UM_HEARTBEAT_SEND);

		auto ret = m_hGetResponse.wait(4000); //4秒内无反馈，则强行终止连接。

		switch (ret)
		{
		case squall::sync_event::LGH_WAIT_OBJECT_0:
			break;
		case squall::sync_event::LGH_WAIT_TIMEOUT:
			emit SendHeartbeat(UM_HEARTBEAT_TIMEOUT);
			break;
		case squall::sync_event::LGH_WAIT_FAILED:
			break;
		}

	}
}

void QClient1to2::OnReceive()
{
}

void QClient1to2::DealWithHeartACK(unsigned long AckID)
{
}

void QClient1to2::DealWithNewCoilID(unsigned long CoilID)
{
}

void QClient1to2::DealWithEndCoilID(unsigned long CoilID)
{
}

void QClient1to2::DealWithSystemStatus(unsigned long status)
{
}

void QClient1to2::DealWithCurrentCoil(unsigned long CoilID, bool CoilInView)
{
}

void QClient1to2::DealWithNodeConfig()
{
}

void QClient1to2::DealWithSendParam()
{
}

void QClient1to2::DealWithApplyParam()
{
}

void QClient1to2::ReceiveXMLThread(void)
{
}



void QClient1to2::InformUI(UINT UserMsg)
{
}
