/************************************
     �ļ�����: QSingleMutex.h
	 ��    ��: Novice
	 ��������: 2019-11-12
	 ĩ���޸�: 2019-11-12
	 ��    ��: Ver1.0
     ˵    ��: ȱ�㣬������MFC ֱ���ڳ�ʼ��ʱ�򣬸ɵ�����

**************************************/

#ifndef QSINGLEMUTEX_H_
#define QSINGLEMUTEX_H_

#include <QSharedMemory>

class QSingleMutex : public QSharedMemory
{
	Q_OBJECT

public:
	QSingleMutex(const QString& Name,QObject *parent = nullptr);
	~QSingleMutex();

	bool IsSignal();
private:
	QString  m_Key;
};

#endif