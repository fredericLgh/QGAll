#pragma once
#include "windows.h"
#include "ImgInterface.h"

struct StructImageInfo 
{
	SYSTEMTIME FrameTm;					//�ɼ�ʱ���
	UINT CoilID;						//���ֱ��
	UINT ViewID;						//�����ӳ�
	long FrameID;						//ͼ��֡��
	UINT CCDPos;						//��ǰ������ӳ��е�λ�ã�Ĭ��Ϊ0����ע�⣺CCDPos < CamPerView

	
	cv::Mat SrcImage;					//ԭͼ
	cv::Mat NormalizedImage;			//��׼��ͼ

};

struct StructInspectResult		//����һ��ͼ��Ӽ�⿪ʼ�������������е�������Ϣ
{
	StructImageInfo Img;		//ͼ�񸱱�
	StructImageResult Result;	//ͼ����ӿڷ��صļ����
};