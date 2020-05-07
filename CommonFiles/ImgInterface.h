#pragma once

#include "CommFile.h"
#include "opencvWindows.h"
#include <vector>

struct StructImageRequire				//图像检测要求（输入）
{
	long Type;							//检测类型（0全检；1只检是否有效；）“开始和暂停的区别”
	long Reserved0;						//保留

	UINT CCDPos;						//当前相机在视场中的位置（默认为0），注意：CCDPos < CamPerView
	UINT CamPerView;					//单视场相机数量（默认为1）

	long Reserved1;						//保留
	long Reserved2;						//保留
};

struct StructImageDefect
{
	//缺陷信息
	long ClassID;						//缺陷名称所对应的ID
//    WCHAR ClassName[16];				//缺陷名称（注意：建议最多4个汉字）
	char ClassName[32];

	//缺陷在原图上的位置
	long RoiX0;							//缺陷X0位置
	long RoiY0;							//缺陷Y0位置
	long RoiX1;							//缺陷X1位置
	long RoiY1;							//缺陷Y1位置
};
struct StructImageResult				//图像检测结果（输出）
{
	long FullTime;						//处理时间ms（该值可以不填写）
	long IsValid;						//测量有效信号（能够锁定检测范围，即：能够得到下面4个边的位置，或者说能够确定有带钢）
	long LeftEdgePix;					//左边缘像素值（因为要确定缺陷在带材中距离边部的位置，所以必须要知道边部在哪里）
	long RightEdgePix;					//右边缘像素值（因为要确定缺陷在带材中距离边部的位置，所以必须要知道边部在哪里）
	long TopEdgePix;					//上边缘像素值（通常为0）
	long BottomEdgePix;					//下边缘像素值（通常为0）

	std::vector<StructImageDefect> vecDefects;		//每张图的缺陷


	//业务扩展内容
	long AverageGray;					//平均灰度值
	float BackgroundNoise;				//背景噪声强度（均差）

	long Reserved1;						//保留
	long Reserved2;						//保留
	long Reserved3;						//保留
	long Reserved4;						//保留
	long Reserved5;						//保留
	long Reserved6;						//保留
	long Reserved7;						//保留
	long Reserved8;						//保留
};

//************************ CoreEngine对外接口定义 *************************

//图像处理函数定义
typedef void(*pCoreProcess)(const cv::Mat&, cv::Mat&, StructImageRequire, StructImageResult&);

//启动平台
typedef void (*pCorePlatform)(void);

//重新加载配置参数
typedef void (*pReloadConfig)(void);

//焦距辅助调节
typedef void (*pFocusAdjust)(BYTE*, int, int, int&, int&);

//标定(这里的char不用变为宽字节）
//typedef bool (*pGoCalibration)(BYTE*, int, int, float&, float&, const WCHAR*);
typedef bool (*pGoCalibration)(BYTE*, int, int, float&, float&, const char*);
