#include "QClient1to2.h"
#include <QHostAddress>
#include "QImageProcApp.h"
#include "NetMsg.h"
#include <QMessageBox>
#include "ProcHeader.h"

#include "QImageProcWidget.h"
#include "OperateINI.h"

QClient1to2::QClient1to2(QObject* parent)
    : QTcpSocket(parent)
{
    m_HeadRecvSize = m_FixedHeadSize;	//��Ϣͷ����Ҫ���յĳ���
    m_MessageType = 0;				//��Ϣ����
    m_FullBodySize = 0;				//��Ϣ�峤��
    m_pBodyBuf = nullptr;			//��Ϣ�建��
    m_BodyMaxSize = 0;              // new �ڴ��С
    m_BodyRecvSize = 0;				//��Ϣ�廹��Ҫ���յĳ���
    m_ReadHeadSign = true;			//��Ϣ��ȡ�����ж�


    //************* �����źų�ʼ�� *************
    m_HeartCounter = 0;
    m_hGetResponse.reset();


    //************* �����߳� *************
    m_QuitThread = false;
    m_HeartBeatThread = std::thread(&QClient1to2::HeartBeatThread, this);


    // �źŲۺ���
    connect(this, &QClient1to2::readyRead, this, &QClient1to2::OnReceive);

   /* connect(this, &QClient1to2::connected, [=]()
        {
            emit SendTrace(QString::fromLocal8Bit("---- Tcp (%1->%2)���ӳɹ� ----")
                .arg(pApp->m_ClientIP).arg(pApp->m_ServerIP));
            emit SendClientState(true);
        });
    connect(this, &QClient1to2::disconnected, [=]()
        {

            emit SendTrace(QString::fromLocal8Bit("---- Tcp (%1->%2)�Ͽ����� ----")
                .arg(pApp->m_ClientIP).arg(pApp->m_ServerIP));
            emit SendClinetState(false);
        });*/
}

QClient1to2::~QClient1to2()
{
    if (QTcpSocket::state() == QAbstractSocket::ConnectedState)
    {
        CloseSocket();
    }

    if (m_HeartBeatThread.joinable())
    {
        m_QuitThread = true;
        m_hGetResponse.set();	//�����waitforsingleobject�У���Ҳ��Ѹ�ٷ��ء�
        m_HeartBeatThread.join();
    }

    if (!m_pBodyBuf)
    {
        delete[]m_pBodyBuf;
        m_pBodyBuf = nullptr;
        m_BodyMaxSize = 0;
    }

    pApp->g_mem.GetPtrGlobalInfo()->SystemStatus = 3;
}

void QClient1to2::CloseSocket()
{
    if (IsConnected())
    {
        QTcpSocket::close();
    }

    emit SendTrace(QString::fromLocal8Bit("---------- Tcp ���ӶϿ� ----------"));
    pApp->g_mem.GetPtrGlobalInfo()->SystemStatus = 3;
    emit SendStatus(3);
}

bool QClient1to2::IsConnected()
{
    return (state() == ConnectedState || state() == QAbstractSocket::ConnectingState);
}

void QClient1to2::SendData(const char* pData, int Size)
{
    if (QAbstractSocket::ConnectedState == QTcpSocket::state())
    {
        QTcpSocket::write(pData, Size);
    }
}

void QClient1to2::TryConnect()
{
    if (IsConnected())
    {
        return;
    }
    else
    {
        m_HeadRecvSize = m_FixedHeadSize;	//��Ϣͷ����Ҫ���յĳ���
        m_MessageType = 0;				//��Ϣ����
        m_FullBodySize = 0;				//��Ϣ�峤��
        m_BodyRecvSize = 0;				//��Ϣ�廹��Ҫ���յĳ���
        m_ReadHeadSign = true;			//��Ϣ��ȡ�����ж�
    }

    if (ConnectServer(pApp->m_ClientIP, pApp->m_ServerIP, NETPORT_1TO2))
    {
        SendTrace(QString::fromLocal8Bit("---------- �������� %1 ----------").arg(pApp->m_ServerIP));
    }
    else
    {
        SendTrace(QString::fromLocal8Bit("---------- IP��%1��ʧ�� ----------").arg(pApp->m_ClientIP));
    }
}

bool QClient1to2::ConnectServer(const QString& LocalIP, const QString& ServerIP, const uint ServerPort)
{
    if (state() == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket::setLocalAddress(QHostAddress(LocalIP));

        QTcpSocket::connectToHost(ServerIP, ServerPort);

        return true;
    }
    else
    {
        return false;
    }
}


void QClient1to2::HeartBeatThread(void)
{
    std::chrono::milliseconds dura(100);

    while (1)
    {
        for (int i = 0; i < 150; i++)
        {
            std::this_thread::sleep_for(dura);
            if (m_QuitThread) break;
        }
        if (m_QuitThread) break;

        HeartTimerProc();
    }
}

void QClient1to2::HeartTimerProc(void)
{
    if (state() == QAbstractSocket::ConnectedState)
    {
        emit SendHeartbeat(UM_HEARTBEAT_SEND);

        auto ret = m_hGetResponse.wait(4000); //4�����޷�������ǿ����ֹ���ӡ�

        switch (ret)
        {
        case squall::sync_event::WAIT_OBJECT_0:
            break;
        case squall::sync_event::WAIT_TIMEOUT:
            emit SendHeartbeat(UM_HEARTBEAT_TIMEOUT);
            break;
        case squall::sync_event::WAIT_FAILED:
            break;
        }

    }
}


void QClient1to2::OnReceive()
{
    /***************************************************************************************

    ��Ϣ�ṹ��

    |   ��Ϣ����   |   ��Ϣ�峤��   |                ��Ϣ������                  |
        4 Bytes		 4 Bytes					0 - n Bytes

    ***************************************************************************************/


    while (1)
    {
        if (QTcpSocket::bytesAvailable() == 0) break;
        if (m_ReadHeadSign)
        {
            auto ReceivedBytes = QTcpSocket::read((char*)&m_HeadBuf[m_FixedHeadSize - m_HeadRecvSize], m_HeadRecvSize);

            if (ReceivedBytes == -1)
            {
                // ���쳣
                emit SendTrace(QString::fromLocal8Bit("OnReceive �����쳣"));
                return;
            }

            if (ReceivedBytes == m_HeadRecvSize)
            {
                //********************** ��ȡͷ����Ϣ **************************

                memcpy(&m_MessageType, &m_HeadBuf[0], 4);
                memcpy(&m_FullBodySize, &m_HeadBuf[4], 4);

                //******************* ����ͷ����Ϣ�����ж� *********************

                if (m_FullBodySize == 0)	//����Ϣ�壨����Ϣ��
                {
                    switch (m_MessageType)
                    {
                    case 0:
                    {
                        break;
                    }
                    case NETMSG_SEND_PARAM:
                    {
                        DealWithSendParam();
                        break;
                    }
                    case NETMSG_APPLY_PARAM:
                    {
                        DealWithApplyParam();
                        break;
                    }
                    default:
                    {
                        // TRACE(L"\n Message Warning !! ��Ϣ [%d] ����Ӧ������", m_MessageType);
                    }
                    }

                    m_ReadHeadSign = true;
                }
                else
                {
                    if (m_FullBodySize <= 0 || m_FullBodySize > 50000000)
                    {
                        QMessageBox::critical(nullptr, QString::fromLocal8Bit("����"),
                            QString::fromLocal8Bit("Msg=%1, Size=%2").arg(m_MessageType).arg(m_FullBodySize));
                    }

                    //m_pBodyBuf = new BYTE[m_FullBodySize];
                    if (m_FullBodySize > m_BodyMaxSize)
                    {
                        if (!m_pBodyBuf)
                        {
                            delete[]m_pBodyBuf;
                            m_pBodyBuf = nullptr;
                        }

                        m_BodyMaxSize = m_FullBodySize;
                        m_pBodyBuf = new BYTE[m_BodyMaxSize];
                    }

                    m_BodyRecvSize = m_FullBodySize;

                    m_ReadHeadSign = false;
                }

                //********************** ͷ�������� **************************

                memset(m_HeadBuf, 0, m_FixedHeadSize);
                m_HeadRecvSize = m_FixedHeadSize;

            }
            else
            {
                m_HeadRecvSize = m_HeadRecvSize - ReceivedBytes;
            }
        }
        else
        {
            auto ReceivedBytes = QTcpSocket::read((char*)m_pBodyBuf + m_FullBodySize - m_BodyRecvSize, m_BodyRecvSize);

            if (ReceivedBytes == -1)
            {
                // ���쳣
                emit SendTrace(QString::fromLocal8Bit("OnReceive �����쳣"));
                return;
            }

            if (ReceivedBytes == m_BodyRecvSize)
            {
                //********************** ������Ϣ���� *************************

                switch (m_MessageType)
                {
                case NETMSG_HEART_ACK:
                {
                    unsigned long Counter = 0;
                    memcpy(&Counter, m_pBodyBuf, 4);
                    DealWithHeartACK(Counter);

                    break;
                }
                case NETMSG_NEW_COILID:
                {
                    unsigned long NewID;
                    memcpy(&NewID, m_pBodyBuf, 4);
                    DealWithNewCoilID(NewID);

                    break;
                }
                case NETMSG_END_COILID:
                {
                    unsigned long EndID;
                    memcpy(&EndID, m_pBodyBuf, 4);
                    DealWithEndCoilID(EndID);

                    break;
                }
                case NETMSG_SET_STATUS:
                {
                    unsigned long Status;
                    memcpy(&Status, m_pBodyBuf, 4);
                    DealWithSystemStatus(Status);

                    break;
                }
                case NETMSG_SET_CURRENTCOIL:
                {
                    unsigned long CoilID = 0;
                    BOOL CoilInView = 0;
                    memcpy(&CoilID, m_pBodyBuf, 4);
                    memcpy(&CoilInView, m_pBodyBuf + 4, 4);
                    DealWithCurrentCoil(CoilID, CoilInView);

                    break;
                }
                case NETMSG_NODE_CONFIG:	//���ӳɹ���ĳ�ʼ����Ϣ
                {
                    UINT Offset = 0;

                    UINT ViewID;
                    memcpy(&ViewID, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    UINT CCDPos;
                    memcpy(&CCDPos, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    UINT CamPerView;
                    memcpy(&CamPerView, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    BOOL ContinuousCoilMode;
                    memcpy(&ContinuousCoilMode, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    BOOL ControlByNet;
                    memcpy(&ControlByNet, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    BOOL Normalization;
                    memcpy(&Normalization, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    UINT FileMode;
                    memcpy(&FileMode, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    UINT PictureMode;
                    memcpy(&PictureMode, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    UINT SnapShotMode;
                    memcpy(&SnapShotMode, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;

                    UINT SnapShotScale;
                    memcpy(&SnapShotScale, (LPBYTE)m_pBodyBuf + Offset, 4);
                    Offset += 4;


                    //ENSURE_EXPRESSION(Offset == m_FullBodySize);


                    Struct1GlobalInfo* pGlobal = pApp->g_mem.GetPtrGlobalInfo();
                    pGlobal->ViewID = ViewID;
                    pGlobal->CCDPos = CCDPos;
                    pGlobal->CamPerView = CamPerView;
                    pGlobal->ContinuousCoilMode = ContinuousCoilMode;
                    pGlobal->ControlByNet = ControlByNet;
                    pGlobal->Normalization = Normalization;
                    pGlobal->FileMode = FileMode;
                    pGlobal->PictureMode = PictureMode;
                    pGlobal->SnapShotMode = SnapShotMode;
                    pGlobal->SnapShotScale = SnapShotScale;

                    //DealWithNodeConfig();
                    break;
                }
                default:
                {
                    //TRACE(L"\n Message Warning !! ��Ϣ [%d] ����Ӧ������", m_MessageType);
                }
                }

                //********************** ��Ϣ�������� ************************

                m_FullBodySize = 0;
                m_BodyRecvSize = 0;

                m_ReadHeadSign = true;
            }
            else
            {
                m_BodyRecvSize = m_BodyRecvSize - ReceivedBytes;
            }
        }
    }
}


bool QClient1to2::SendMsg(long MsgType, LPVOID pBuf, long nSize)
{
    //ENSURE_EXPRESSION(state() == QAbstractSocket::ConnectedState);
    /***************************************************************************************

    ��Ϣ�ṹ��

    |   ��Ϣ����   |   ��Ϣ�峤��   |                ��Ϣ������                  |
        4 Bytes		 4 Bytes					0 - n Bytes

  ***************************************************************************************/

    long n = 8 + nSize;
    BYTE* pMem = new BYTE[n];

    memcpy(pMem, &MsgType, 4);
    memcpy(pMem + 4, &nSize, 4);
    memcpy(pMem + 8, pBuf, nSize);

    int sendSize = QTcpSocket::write((const char*)pMem, n);
    delete[]pMem;

    return sendSize == n;
}

bool QClient1to2::SendWarning(long Type, QString Info)
{
    if (state() != QAbstractSocket::ConnectedState)
    {
        emit SendTrace(QString::fromLocal8Bit("���;��� %1 ����(������״̬)!").arg(Type));
        return  false;
    }

    BYTE Buf[124] = { 0 };	// 4 + 60 * WCHAR = 124
    memcpy(&Buf[0], &Type, 4);

    memcpy(&Buf[4], Info.data(), Info.length() > 119 ? 119 : Info.length());

    BOOL bSent = SendMsg(NETMSG_SAMPLE_WARNING, Buf, 124);
    if (bSent)
    {
        emit SendTrace(QString::fromLocal8Bit("********** ���;��� %1 **********").arg(m_HeartCounter));
    }
    else
    {
        emit SendTrace(QString::fromLocal8Bit("******** ���;��� %1 ʧ��********").arg(m_HeartCounter));
    }

    return bSent;
}

bool QClient1to2::SendHeartBeat(void)
{
    if (state() != QAbstractSocket::ConnectedState)
    {
        emit SendTrace(QString::fromLocal8Bit("������������(������״̬)!"));
        return  false;
    }

    m_HeartCounter++;
    if (m_HeartCounter == 10000) m_HeartCounter = 1;

    BOOL bSent = SendMsg(NETMSG_HEART_BEAT, &m_HeartCounter, 4);
    if (bSent)
    {
        emit SendTrace(QString::fromLocal8Bit("********** �������� %1 **********").arg(m_HeartCounter));
    }
    else
    {
        emit SendTrace(QString::fromLocal8Bit("******** �������� %1 ʧ��********").arg(m_HeartCounter));
    }

    return bSent;
}

bool QClient1to2::SendFrame(std::shared_ptr<StructInspectResult> pResult)
{
    if (state() != QAbstractSocket::ConnectedState)
    {
        emit SendTrace(QString::fromLocal8Bit("����֡����(������״̬)!"));
        return  false;
    }

    /***************************************************************************************

        ֡��Ϣ���������

        FrameTm				//ʱ�����16�ֽڣ�
        CoilID				//�־�ID
        ViewID				//�ӳ�ID
        FrameID				//֡ID
        CCDPos				//���λ�ã�����

        IsValid				//�Ƿ��и�
        LeftEdgePix;		//���Ե����ֵ
        RightEdgePix;		//�ұ�Ե����ֵ
        TopEdgePix;			//�ϱ�Ե����ֵ
        BottomEdgePix;		//�±�Ե����ֵ

        AverageGray			//ƽ���Ҷ�
        BackgroundNoise		//��������
        DefectCount			//ȱ������

        +

        for
        {
        ClassID			//ȱ�����ID
        ClassName[16]	//ȱ���������

        RoiX0			//ȱ��λ��x0
        RoiY0			//ȱ��λ��y0
        RoiX1			//ȱ��λ��x1
        RoiY1			//ȱ��λ��y1
        }


        total bytes = 64 + n * 52

    ***************************************************************************************/

    StructImageInfo& ImgInfo = pResult->Img;
    StructImageResult& ImgResult = pResult->Result;


    long DefectCount = (long)ImgResult.vecDefects.size();
    long MemSize = 64 + DefectCount * 52;

    BYTE* pMem = new BYTE[MemSize];
    LPBYTE p = pMem;

    memcpy(p, &ImgInfo.FrameTm, 16);
    p += 16;

    memcpy(p, &ImgInfo.CoilID, 4);
    p += 4;

    memcpy(p, &ImgInfo.ViewID, 4);
    p += 4;

    memcpy(p, &ImgInfo.FrameID, 4);
    p += 4;

    memcpy(p, &ImgInfo.CCDPos, 4);
    p += 4;

    memcpy(p, &ImgResult.IsValid, 4);
    p += 4;

    memcpy(p, &ImgResult.LeftEdgePix, 4);
    p += 4;

    memcpy(p, &ImgResult.RightEdgePix, 4);
    p += 4;

    memcpy(p, &ImgResult.TopEdgePix, 4);
    p += 4;

    memcpy(p, &ImgResult.BottomEdgePix, 4);
    p += 4;

    memcpy(p, &ImgResult.AverageGray, 4);
    p += 4;

    memcpy(p, &ImgResult.BackgroundNoise, 4);
    p += 4;

    memcpy(p, &DefectCount, 4);
    p += 4;

    long i;
    for (i = 0; i < DefectCount; i++)
    {
        memcpy(p, &ImgResult.vecDefects[i].ClassID, 4);
        p += 4;

        memcpy(p, ImgResult.vecDefects[i].ClassName, 32);
        p += 32;

        memcpy(p, &ImgResult.vecDefects[i].RoiX0, 4);
        p += 4;

        memcpy(p, &ImgResult.vecDefects[i].RoiY0, 4);
        p += 4;

        memcpy(p, &ImgResult.vecDefects[i].RoiX1, 4);
        p += 4;

        memcpy(p, &ImgResult.vecDefects[i].RoiY1, 4);
        p += 4;

    }

    //ENSURE_EXPRESSION(pMem + MemSize == p);

    bool retValue = SendMsg(NETMSG_FRAME_RESULT, pMem, MemSize);
    delete[]pMem;

    if (!retValue)
    {
        emit SendTrace(QString::fromLocal8Bit("����֡ ����!"));
    }
    else
    {
        //emit SendTrace(QString::fromLocal8Bit("����֡ ok!"));
    }

    return retValue;
}


void QClient1to2::DealWithHeartACK(unsigned long AckID)
{
    if (AckID == m_HeartCounter)
    {
        m_hGetResponse.set();
        emit SendTrace(QString::fromLocal8Bit("---------- �յ����� %1 ----------").arg(AckID));
    }
}

void QClient1to2::DealWithNewCoilID(unsigned long CoilID)
{
    pApp->g_mem.GetPtrGlobalInfo()->CoilID = CoilID;
    pApp->g_mem.GetPtrGlobalInfo()->FrameID = 0;
    pApp->g_mem.GetPtrGlobalInfo()->CoilInView = true;

    emit SendNewCoilID(QString::fromLocal8Bit("010%1").arg(CoilID));
}

void QClient1to2::DealWithEndCoilID(unsigned long CoilID)
{
    pApp->g_mem.GetPtrGlobalInfo()->CoilInView = false;
}

void QClient1to2::DealWithSystemStatus(unsigned long Status)
{
    pApp->g_mem.GetPtrGlobalInfo()->SystemStatus = Status;

    emit SendStatus(Status);
}


void QClient1to2::DealWithCurrentCoil(unsigned long CoilID, bool CoilInView)
{
    pApp->g_mem.GetPtrGlobalInfo()->CoilInView = CoilInView;

    if (pApp->g_mem.GetPtrGlobalInfo()->CoilID != CoilID)		//��ID��������ID
    {
        pApp->g_mem.GetPtrGlobalInfo()->CoilID = CoilID;
        pApp->g_mem.GetPtrGlobalInfo()->FrameID = 0;

        emit SendNewCoilID(QString::fromLocal8Bit("010%1").arg(CoilID));
    }
}

void QClient1to2::DealWithNodeConfig()
{
	Struct1GlobalInfo* pGlobal = pApp->g_mem.GetPtrGlobalInfo();

	//emit SendCCDPos(pGlobal->ViewID, pGlobal->CCDPos);
}


void QClient1to2::DealWithSendParam()
{
    //std::thread(&QClient1to2::ReceiveXMLThread, this).detach();
}

void QClient1to2::DealWithApplyParam()
{
    //    pReloadConfig pFunAddr /*= (pReloadConfig)GetProcAddress(pApp->m_hDLL, "ReloadConfig")*/;
    //    ENSURE_EXPRESSION(pFunAddr != nullptr);

    //    try
    //    {
    //        (pFunAddr)();
    //    }
    //    catch (std::exception &err)
    //    {
    //        pApp->WriteTestLog(QString::fromLocal8Bit("Engine �ڲ�����%1").arg(err.what()));
    //        std::terminate();
    //    }
    //    catch (...)
    //    {
    //         pApp->WriteTestLog(QString::fromLocal8Bit("Engine �ڲ������ڲ�����δ֪����"));
    //        std::terminate();
    //    }

    InformUI(UM_APPLY_XML_OK); //֪ͨUI
    SendMsg(NETMSG_APPLYPARAM_OK); //֪ͨ������
}

/*************************************************************
| �ļ�����  | �ļ���   | �ļ���С | �ļ����� | �ļ���  |  �ļ���С | �ļ����� |...
| 4 bytes  | 60 bytes | 4 bytes  |         |40 bytes |  4 bytes |         |...

**************************************************************/
void QClient1to2::ReceiveXMLThread(void)
{
    //    WORD	wVersionRequested;
    //    WSADATA wsaData;
    //    wVersionRequested = MAKEWORD(2, 2);
    //    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    //    {
    //        InformUI(UM_RECEIVE_XML_FAIL);
    //        return;
    //    }


    //    int ret;
    //    SOCKET Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //    // ��(����Ϊ����ȷ��·�Ĺ���)
    //    SOCKADDR_IN local;
    //    local.sin_family = AF_INET;
    //    local.sin_port = htons(0);
    //    InetPton(AF_INET, theApp.m_ClientIP.GetString(), &local.sin_addr);
    //    ret = bind(Sock, (struct sockaddr *)&local, sizeof(SOCKADDR_IN));


    //    //����ʱ��
    //    int nNetTimeout = 2000;		//2��
    //    setsockopt(Sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&nNetTimeout, sizeof(int));


    //    //���ý��ջ�������С
    //    int nRecvBuf = 1 * 1024 * 1024;
    //    setsockopt(Sock, SOL_SOCKET, SO_RCVBUF, (char*)&nRecvBuf, sizeof(int));


    //    SOCKADDR_IN addrdata;
    //    addrdata.sin_family = AF_INET;
    //    addrdata.sin_port = htons(NETPORT_XML);
    //    InetPton(AF_INET, theApp.m_ServerIP.GetString(), &addrdata.sin_addr);


    //    //������߶Ͽ�����connect�ں�ʱ��15�����ң����ɿء�
    //    if (connect(Sock, (SOCKADDR*)&addrdata, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    //    {
    //        InformUI(UM_RECEIVE_XML_FAIL);

    //        closesocket(Sock);
    //        WSACleanup();
    //        return;
    //    }

    //    //����
    //    UINT nFileCount = 0;
    //    ret = recv(Sock, (char*)&nFileCount, 4, NULL);
    //    if (ret != 4)
    //    {
    //        InformUI(UM_RECEIVE_XML_FAIL);

    //        closesocket(Sock);
    //        WSACleanup();
    //        return;
    //    }

    //    for (UINT i = 0; i < nFileCount; i++)
    //    {
    //        BOOL bRet = ReceiveOneXML(Sock);
    //        if (!bRet)
    //        {
    //            InformUI(UM_RECEIVE_XML_FAIL);

    //            closesocket(Sock);
    //            WSACleanup();
    //            return;
    //        }
    //    }


    //    closesocket(Sock);
    //    WSACleanup();

    InformUI(UM_RECEIVE_XML_OK);
}


#ifdef __linux__
bool QClient1to2::ReceiveOneXML(int socketfd)
{
    // socketfd = 0;
//    const UINT nHeaderSize = 64;
//    BYTE HeaderBuffer[nHeaderSize];

//    UINT len = 0;
//    while (len < nHeaderSize)
//    {
//        int n = recv(Sock, (char*)HeaderBuffer + len, int(nHeaderSize - len), NULL);
//        if (n == SOCKET_ERROR)
//        {
//            return FALSE;
//        }
//        len += n;
//    }


//    //��ȡ�ļ���
//    WCHAR FN[30] = { 0 };
//    wcscpy_s(FN, (LPCWSTR)HeaderBuffer);
//    CString PathName = CProfile::GetAppPath() + FN;


//    //��ȡ�ļ���С�����ٿռ�
//    UINT nFileSize = *(UINT *)&HeaderBuffer[60];
//    std::vector<BYTE> vecBuf;
//    vecBuf.resize(nFileSize, 0);



//    CFile file;
//    if (file.Open(PathName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
//    {
//        len = 0;
//        while (len < nFileSize)
//        {
//            int n = recv(Sock, (char*)vecBuf.data() + len, int(nFileSize - len), NULL);
//            if (n == SOCKET_ERROR)
//            {
//                file.Close();
//                return FALSE;
//            }
//            len += n;
//        }

//        try
//        {
//            file.Write(vecBuf.data(), nFileSize);
//        }
//        catch (CException *e)
//        {
//            e->ReportError();
//            file.Close();
//            return FALSE;
//        }

//        file.Close();
//        return TRUE;
//    }
//    else
//    {
//        file.Abort();
//        return FALSE;
//    }

    return true;
}

#endif

void QClient1to2::InformUI(UINT UserMsg)
{
    emit SendMsg(UserMsg);
}

