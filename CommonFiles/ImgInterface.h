#pragma once

#include "CommFile.h"
#include "opencvWindows.h"
#include <vector>

struct StructImageRequire				//ͼ����Ҫ�����룩
{
	long Type;							//������ͣ�0ȫ�죻1ֻ���Ƿ���Ч��������ʼ����ͣ������
	long Reserved0;						//����

	UINT CCDPos;						//��ǰ������ӳ��е�λ�ã�Ĭ��Ϊ0����ע�⣺CCDPos < CamPerView
	UINT CamPerView;					//���ӳ����������Ĭ��Ϊ1��

	long Reserved1;						//����
	long Reserved2;						//����
};

struct StructImageDefect
{
	//ȱ����Ϣ
	long ClassID;						//ȱ����������Ӧ��ID
//    WCHAR ClassName[16];				//ȱ�����ƣ�ע�⣺�������4�����֣�
	char ClassName[32];

	//ȱ����ԭͼ�ϵ�λ��
	long RoiX0;							//ȱ��X0λ��
	long RoiY0;							//ȱ��Y0λ��
	long RoiX1;							//ȱ��X1λ��
	long RoiY1;							//ȱ��Y1λ��
};
struct StructImageResult				//ͼ�������������
{
	long FullTime;						//����ʱ��ms����ֵ���Բ���д��
	long IsValid;						//������Ч�źţ��ܹ�������ⷶΧ�������ܹ��õ�����4���ߵ�λ�ã�����˵�ܹ�ȷ���д��֣�
	long LeftEdgePix;					//���Ե����ֵ����ΪҪȷ��ȱ���ڴ����о���߲���λ�ã����Ա���Ҫ֪���߲������
	long RightEdgePix;					//�ұ�Ե����ֵ����ΪҪȷ��ȱ���ڴ����о���߲���λ�ã����Ա���Ҫ֪���߲������
	long TopEdgePix;					//�ϱ�Ե����ֵ��ͨ��Ϊ0��
	long BottomEdgePix;					//�±�Ե����ֵ��ͨ��Ϊ0��

	std::vector<StructImageDefect> vecDefects;		//ÿ��ͼ��ȱ��


	//ҵ����չ����
	long AverageGray;					//ƽ���Ҷ�ֵ
	float BackgroundNoise;				//��������ǿ�ȣ����

	long Reserved1;						//����
	long Reserved2;						//����
	long Reserved3;						//����
	long Reserved4;						//����
	long Reserved5;						//����
	long Reserved6;						//����
	long Reserved7;						//����
	long Reserved8;						//����
};

//************************ CoreEngine����ӿڶ��� *************************

//ͼ����������
typedef void(*pCoreProcess)(const cv::Mat&, cv::Mat&, StructImageRequire, StructImageResult&);

//����ƽ̨
typedef void (*pCorePlatform)(void);

//���¼������ò���
typedef void (*pReloadConfig)(void);

//���ศ������
typedef void (*pFocusAdjust)(BYTE*, int, int, int&, int&);

//�궨(�����char���ñ�Ϊ���ֽڣ�
//typedef bool (*pGoCalibration)(BYTE*, int, int, float&, float&, const WCHAR*);
typedef bool (*pGoCalibration)(BYTE*, int, int, float&, float&, const char*);
