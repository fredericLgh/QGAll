#pragma once
#include "FredSharedMemory.h"

#include <string>

/****************************************************

		共享内存图像 FIFO 缓冲区大小定义

	IMAGE_MAX_BUF_SIZE 定义了单个图片的最大像素；
	IMAGE_ARRAY_SIZE 定义了FIFO的长度；（3足够）

	我们推荐的像素配置为：
		4096*3000、6144*4000、8192*3000；
		2048*1500、1600*1200、1408*1056；

****************************************************/

#define  IMAGE_MAX_BUF_SIZE		8192 * 3000
#define  IMAGE_ARRAY_SIZE		3
//#define  BYTE unsigned char

struct StructRawImage
{
	unsigned int FrameTm;		//采集时间戳
	int CoilID;			//带钢编号
	int ViewID;			//带钢视场
	long FrameID;			//图像帧号
	int CCDPos;			//CCD位置

	char RawImageBuf[IMAGE_MAX_BUF_SIZE];  //图像数据

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
	int CoilID;				//带钢编号
	int ViewID;				//带钢视场
	long FrameID;				//图像帧号
	int CCDPos;				//CCD位置

	int SystemStatus;			//系统状态（1启动/2暂停/3停止）
	bool CoilInView;			//有钢信号（在钢坯模式下避免无钢时保存图片）

	int CamPerView;			//单面CCD数量
	bool ContinuousCoilMode;	//连续钢卷模式
	bool ControlByNet;			//冷轧的换卷、热轧的带钢开始结束，是否由网络信号来控制
	bool Normalization;			//0代表前端传输原图；1代表前端传输标准化图；
	int SaveImageMode;			//0不存图；1只存缺陷大图；2保存全部大图；3只存缺陷小图

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

