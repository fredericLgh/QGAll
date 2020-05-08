#pragma once
#include "windows.h"
#include "ImgInterface.h"

struct StructImageInfo 
{
	SYSTEMTIME FrameTm;					//采集时间戳
	UINT CoilID;						//带钢编号
	UINT ViewID;						//带钢视场
	long FrameID;						//图像帧号
	UINT CCDPos;						//当前相机在视场中的位置（默认为0），注意：CCDPos < CamPerView

	
	cv::Mat SrcImage;					//原图
	cv::Mat NormalizedImage;			//标准化图

};

struct StructInspectResult		//包含一幅图像从检测开始到检测结束过程中的所有信息
{
	StructImageInfo Img;		//图像副本
	StructImageResult Result;	//图像处理接口返回的检测结果
};