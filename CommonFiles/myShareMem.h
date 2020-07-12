#ifndef QMYSHAREMEM_H_
#define QMYSHAREMEM_H_
#include "FredSharedMemory.h"


/****************************************************

		�����ڴ�ͼ�� FIFO ��������С����

	IMAGE_MAX_BUF_SIZE �����˵���ͼƬ��������أ�
	IMAGE_ARRAY_SIZE ������FIFO�ĳ��ȣ���3�㹻��

	�����Ƽ�����������Ϊ��
		4096*3000��6144*4000��8192*3000��
		2048*1500��1600*1200��1408*1056��

****************************************************/
#include <windows.h>

#define  IMAGE_MAX_BUF_SIZE		8192 * 3000
#define  IMAGE_ARRAY_SIZE		3

struct StructRawImage
{
	SYSTEMTIME FrameTm;		//�ɼ�ʱ���
	UINT CoilID;			//���ֱ��
	UINT ViewID;			//�����ӳ�
	long FrameID;			//ͼ��֡��
	UINT CCDPos;			//CCDλ��

	BYTE RawImageBuf[IMAGE_MAX_BUF_SIZE];  //ͼ������

	StructRawImage(void)
	{
		CoilID = 0;
		ViewID = 0;
		FrameID = 0;
		CCDPos = 0;

		memset(&FrameTm, 0, sizeof(SYSTEMTIME));
		memset(RawImageBuf, 0, IMAGE_MAX_BUF_SIZE);
	}

	~StructRawImage(void)
	{
	}
};

struct Struct1GlobalInfo
{
	UINT CoilID;				//���ֱ��
	UINT ViewID;				//�����ӳ�
	long FrameID;				//ͼ��֡��
	UINT CCDPos;				//CCDλ��

	UINT SystemStatus;			//ϵͳ״̬��1����/2��ͣ/3ֹͣ��
	BOOL CoilInView;			//�и��źţ��ڸ���ģʽ�±����޸�ʱ����ͼƬ��

	UINT CamPerView;			//����CCD����
	BOOL ContinuousCoilMode;	//�����־�ģʽ
	BOOL ControlByNet;			//�����Ļ��������Ĵ��ֿ�ʼ�������Ƿ��������ź�������
	BOOL Normalization;			//0����ǰ�˴���ԭͼ��1����ǰ�˴����׼��ͼ��
	UINT SaveImageMode;			//0����ͼ��1ֻ��ȱ�ݴ�ͼ��2����ȫ����ͼ��3ֻ��ȱ��Сͼ
	UINT FileMode;              //0�����䣻1���䣻2ȫ�棻3ֻ�溬ȱ��
	UINT PictureMode;			//0�����䣻1���䣻2���棻
	UINT SnapShotMode;			//0�����䣻1���䣻2��������ͼ��
	UINT SnapShotScale;			//�������ųߴ�

};

struct Struct1DataSpace
{
	StructRawImage ImageArray[IMAGE_ARRAY_SIZE];
	long WriteIndex;

	Struct1GlobalInfo GlobalInfo;
};



class myShareMem :
	public CFredSharedMemory
{
public:
	myShareMem(QObject *parent = 0);
	~myShareMem();

	bool Open(QString ClientIP);
	void Close(void);
	Struct1DataSpace* GetPtrDataSpace(void);
	Struct1GlobalInfo* GetPtrGlobalInfo(void);
	void WriteRawData(BYTE* pBuf, long Size);
	void ReadRawData(StructRawImage* &pRaw, long &ReadIndex);

	static void NoviceGetLocalTime(SYSTEMTIME &time);
};

#endif