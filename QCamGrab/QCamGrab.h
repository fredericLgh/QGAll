#pragma once

#include <QtWidgets/QWidget>
#include "ui_QCamGrab.h"
#include "DalsaGige.h"
#include "QCameraApp.h"
//住界面展示部分

class QCamGrab : public QWidget
{
	Q_OBJECT

public:
	QCamGrab(QWidget *parent = Q_NULLPTR);
	QDalsaGige m_Device;
						//原始图像解码器
						//图像显示界面
	QString m_SavePath;
	bool m_SaveSign;
	long m_PIcID;//本地保存的图像ID计数器 0-9999
						//微妙计数器  用于计算共享内存压缩时间
	static void XferCallback(SapAcqDeviceCallbackInfo *pInfo);
	
//相机断线重连
	static void myCallbackConncet(SapManCallbackInfo *pInfo);
	void ReStartCamera();

//信号槽的处理
signals:


protected:
	//鼠标一系列操作

private:
	void InitWnd();
	void ExitWnd();

	void App2Wnd();
	void Wnd2App();

public:

	void OnDestroy();
	void LoadParam();

	void OnClickedBtPath();
	void OnClickedBtSave();
	
	//消息提示接口
	//virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void OnClickedBtShow();
	void setupCamera();
	void OnClickedBtExposure();
	void OnClickedBtGain();




private:
	Ui::QCamGrabClass ui;
};
