#pragma once

#include <QObject>
#include <QApplication>
#include <mutex>

#define pApp (static_cast<QImageProcApp *>(qApp))


class QImageProcApp : public QApplication
{
	Q_OBJECT

public:
	QImageProcApp(int &argc, char **argv);
	~QImageProcApp();

private:
	void InitApp();
	void ExitApp();

public:
	//�����ڴ����
	int m_ImageWidth;
	int m_ImageHeight;
	QString m_ServerIP;
	QString m_ClientIP;

	long m_SkipFrame;

	QString m_DllName;
	QString m_DependentLibPath;//���ѧϰ������·��
	int m_HostThreadCount;//�߳���
	//QSquallRecorder m_TestLog;//��¼������һ�������ش���
	std::mutex m_MutexLog;//m_TestLog������Ϣ����
	
private:
	bool m_IsParameterOk;

public:
	QSharedMem



};

