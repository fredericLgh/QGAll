#pragma once

#include <QtWidgets/QWidget>
#include "ui_QImageProcWidget.h"
#include "myShareMem.h"
#include "SquallThreadPool.h"
#include "ProcHeader.h"

#define UM_FRAME_THREAD_BEGIN		3100
#define UM_FRAME_THREAD_END			3101
#define UM_EVENT_PROCESS_DONE		3102
#define UM_TRANSMIT_THREAD_BEGIN	3103
#define UM_TRANSMIT_THREAD_END		3104

#define UM_WARNING_DATA_BREAK		3105	//数据中断
#define UM_WARNING_DATA_REGAIN		3106	//数据恢复
#define UM_HEARTBEAT_SEND			3107
#define UM_HEARTBEAT_TIMEOUT		3108

#define UM_RECEIVE_XML_OK			3109
#define UM_RECEIVE_XML_FAIL			3110
#define UM_APPLY_XML_OK				3111
#define UM_APPLY_XML_FAIL			3112


#define RED			QColor(255,16,16)
#define GREEN		QColor(0,255,64)
#define GREEN_TXT	QColor(0,160,32)
#define YELLOW		QColor(255,255,0)

class QLabel;
class QTimer;

class QClient1to2;


class QImageProcWidget : public QWidget
{
	Q_OBJECT

public:
	QImageProcWidget(QWidget *parent = Q_NULLPTR);

signals:
public:

private:
	void InitWnd();
	void ExitWnd();

private:
	Ui::QImageProcWidgetClass ui;

	QClient1to2 *m_pQuerySock;
	QTimer *m_pTimer;
	

	void SetLabelColor(QLabel *pLabel, const QColor &color);
private slots:

	void SetStatus(long status);
	void TimeOut();

private:

	std::list<QString> m_TraceList;			//存放Trace信息的链表（用于监控）
	std::list<long> m_ThreadListProc;		//图像处理线程链表（用于监控）
	std::list<long> m_ThreadListTransmit;	//传输线程链表（用于监控）

	bool m_Exit;
	std::thread m_LookForImageThread;		//图像采集线程

	squall::CSquallThreadPool m_ProcessPool;		//图像处理线程池
	squall::CSquallThreadPool m_TransmitPool;		//结果传输线程池





};
