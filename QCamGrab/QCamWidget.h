#pragma once

#include <QtWidgets/QWidget>
#include "ui_QCamWidget.h"
#include "DalsaGige.h"
#include "QCameraApp.h"
#include "Profile.h"
#include "QFiledata.h"
#include "QElapsedTimer"
#include "QImageEncoder.h"


//ס����չʾ����
//QT_BEGIN_NAMESPACE
//namespace Ui { class QCameraWidget; }
//QT_END_NAMESPACE

class QCamWidget : public QWidget
{
	Q_OBJECT

public:
	QCamWidget(QWidget *parent = Q_NULLPTR);
	QDalsaGige m_Camera;
						//ԭʼͼ�������
						//ͼ����ʾ����
	QString m_SavePath;
	bool m_SaveSign;
	long m_PIcID;//���ر����ͼ��ID������ 0-9999
						//΢�������  ���ڼ��㹲���ڴ�ѹ��ʱ��
	static void XferCallback(SapAcqDeviceCallbackInfo *pInfo);
	
//�����������
	void CallBackFunction(const void *pData, int width, int height);

//�źŲ۵Ĵ���
signals:
	void sigChangeCamState(bool state);
	void sigChangeElapsdTime(quint64 time);
	void sigchangeWaring(QString warning);


public slots:

	void slotChangeCamState(bool state);
	void slotChangeElapsdTime(quint64 time);
	void slotChangeWaring(QString warning);

protected:
	//���һϵ�в���

private:
	void InitWnd();
	void ExitWnd();

public:

	void OnDestroy();
	void LoadParam();

	void OnClickedBtPath();
	void OnClickedBtSave();
	
	//��Ϣ��ʾ�ӿ�
	//virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void OnClickedBtShow();
	void setupCamera();
	void OnClickedBtExposure();
	void OnClickedBtGain();
	// ��ʱ��
	QElapsedTimer* m_pElapsdTimer;
	QImageEncoder* m_pImageEncoder;




private:
	Ui::QCamWidgetClass ui;
	//Ui::QCamGrabClass ui;
};
