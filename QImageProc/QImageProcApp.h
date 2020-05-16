#pragma once

#include <QObject>
#include <QApplication>
#include <mutex>
#include "myShareMem.h"
#include "interface.h"
#include "QSquallRecorder.h"
class QSingleMutex;

class CDetectFlawClass;

#define pApp (static_cast<QImageProcApp *>(qApp))


class QImageProcApp : public QApplication
{
	Q_OBJECT

public:
	QImageProcApp(int &argc, char **argv);
	~QImageProcApp();

	bool IsParameterOk() const;
	void ExceptionClose();

private:
	void InitApp();
	void ExitApp();

public:

	void WriteTestLog(QString Text);	//写入调试日志
	//共享内存操作
	int m_ImageWidth;
	int m_ImageHeight;
	QString m_ServerIP;
	QString m_ClientIP;

	long m_SkipFrame;

	QString m_DllName;
	QString m_DependentLibPath;//深度学习依赖库路径
	int m_HostThreadCount;//线程量
	QSquallRecorder m_TestLog;//记录程序奔溃一长和严重错误
	std::mutex m_MutexLog;//m_TestLog调试信息互斥
	
private:
	bool m_IsParameterOk;
	QSingleMutex* m_pSingleMutex;

public:
	myShareMem g_mem;


	int m_GpuNum;
	std::vector<std::pair<CDetectFlawClass *, unsigned long long >> m_vecDectFlawClass;



};

