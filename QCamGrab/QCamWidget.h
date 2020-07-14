#pragma once

#include <QtWidgets/QWidget>
#include "ui_QCamWidget.h"
#include "DalsaGige.h"
#include "QCameraApp.h"
#include "Profile.h"
#include "QFiledata.h"
#include "QElapsedTimer"
#include "QImageEncoder.h"
#include "QTimer"
#include "ImageDlg.h"


//住界面展示部分
//QT_BEGIN_NAMESPACE
//namespace Ui { class QCameraWidget; }
//QT_END_NAMESPACE

class QCamWidget : public QWidget
{
	Q_OBJECT

public:
	QCamWidget(QWidget *parent = Q_NULLPTR);
	QDalsaGige m_Camera;
						//原始图像解码器
						//图像显示界面
	QString m_SavePath;
	bool m_SaveSign;
	long m_PIcID;//本地保存的图像ID计数器 0-9999
						//微妙计数器  用于计算共享内存压缩时间
	static void XferCallback(SapXferCallbackInfo *pInfo);
	
//相机断线重连
	void CallBackFunction(const void *pData, int width, int height);
	void myCallBackConnet(SapManCallbackInfo *Info);

//信号槽的处理
signals:
	void sigChangeCamState(bool state);
	void sigChangeElapsdTime(quint64 time);
	void sigchangeWaring(QString warning);


public slots:

	void slotChangeCamState(bool state);
	void slotChangeElapsdTime(quint64 time);
	void slotChangeWaring(QString warning);

protected:
	//鼠标一系列操作

private:
	void InitWnd();
	void ExitWnd();
	void TimeOut();

public:

	void OnDestroy();
	void LoadParam();

	void OnClickedBtPath();
	void OnClickedBtSave();
	
	//消息提示接口
	//virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void OnClickedBtShow();
	void SetupCamera();
	void OnClickedBtExposure();
	void OnClickedBtGain();
	// 计时器
	QElapsedTimer* m_pElapsdTimer;
	QImageEncoder* m_pImageEncoder;

	void SetLabel(QLabel*pLabel,bool state);
	QTimer *m_pTimer;
	long         m_PicID;  //本地保存的图像ID计数器 0 - 9999
	QImageDlg *m_pImageBox;


private:
	Ui::QCamWidgetClass ui;
	//Ui::QCamGrabClass ui;
};
