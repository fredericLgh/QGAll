#pragma once
#include "FredSharedMemory.h"

#include <string>

/****************************************************

		�����ڴ�ͼ�� FIFO ��������С����

	IMAGE_MAX_BUF_SIZE �����˵���ͼƬ��������أ�
	IMAGE_ARRAY_SIZE ������FIFO�ĳ��ȣ���3�㹻��

	�����Ƽ�����������Ϊ��
		4096*3000��6144*4000��8192*3000��
		2048*1500��1600*1200��1408*1056��

****************************************************/

#define  IMAGE_MAX_BUF_SIZE		8192 * 3000
#define  IMAGE_ARRAY_SIZE		3
//#define  BYTE unsigned char

struct StructRawImage
{
	unsigned int FrameTm;		//�ɼ�ʱ���
	int CoilID;			//���ֱ��
	int ViewID;			//�����ӳ�
	long FrameID;			//ͼ��֡��
	int CCDPos;			//CCDλ��

	char RawImageBuf[IMAGE_MAX_BUF_SIZE];  //ͼ������

	StructRawImage(void)
	{
		CoilID = 0;
		ViewID = 0;
		FrameID = 0;
		CCDPos = 0;

		memset(&FrameTm, 0, sizeof(int));
		memset(RawImageBuf, 0, IMAGE_MAX_BUF_SIZE);
	}

	~StructRawImage(void)
	{
	}
};

struct Struct1GlobalInfo
{
	int CoilID;				//���ֱ��
	int ViewID;				//�����ӳ�
	long FrameID;				//ͼ��֡��
	int CCDPos;				//CCDλ��

	int SystemStatus;			//ϵͳ״̬��1����/2��ͣ/3ֹͣ��
	bool CoilInView;			//�и��źţ��ڸ���ģʽ�±����޸�ʱ����ͼƬ��

	int CamPerView;			//����CCD����
	bool ContinuousCoilMode;	//�����־�ģʽ
	bool ControlByNet;			//�����Ļ��������Ĵ��ֿ�ʼ�������Ƿ��������ź�������
	bool Normalization;			//0����ǰ�˴���ԭͼ��1����ǰ�˴����׼��ͼ��
	int SaveImageMode;			//0����ͼ��1ֻ��ȱ�ݴ�ͼ��2����ȫ����ͼ��3ֻ��ȱ��Сͼ

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
};

