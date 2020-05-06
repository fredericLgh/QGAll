//#ifndef QSHAREDMEM_H
//#define QSHAREDMEM_H



#include "FredSharedMemory.h"
//#include "NoviceSharedMemory.h"
#include <windows.h>
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

struct StructRawImage
{
    SYSTEMTIME FrameTm;		//采集时间戳
    UINT CoilID;			//带钢编号
    UINT ViewID;			//带钢视场
    long FrameID;			//图像帧号
	UINT CCDPos;            //CCD位置	

    BYTE RawImageBuf[IMAGE_MAX_BUF_SIZE];  //图像数据

    StructRawImage(void)
    {
        CoilID = 0;
        ViewID = 0;
        FrameID = 0;
        CCDPos = 0;

        memset( &FrameTm, 0, sizeof(SYSTEMTIME) );
        memset( RawImageBuf, 0, IMAGE_MAX_BUF_SIZE );
    }

    ~StructRawImage(void)
    {
    }
};

struct Struct1GlobalInfo
{
    UINT CoilID;				//带钢编号
    UINT ViewID;				//带钢视场
    long FrameID;				//图像帧号
    UINT CCDPos;				//CCD位置

    UINT SystemStatus;			//系统状态（1启动/2暂停/3停止）
    BOOL CoilInView;			//有钢信号（在钢坯模式下避免无钢时保存图片）

    UINT CamPerView;			//单面CCD数量
    BOOL ContinuousCoilMode;	//连续钢卷模式
    BOOL ControlByNet;			//冷轧的换卷、热轧的带钢开始结束，是否由网络信号来控制
    BOOL Normalization;			//0代表前端传输原图；1代表前端传输标准化图；
    UINT FileMode;				//0不传输；1传输；2全存；3只存含缺陷
    UINT PictureMode;			//0不传输；1传输；2保存；
    UINT SnapShotMode;			//0不传输；1传输；2保存整合图；
    UINT SnapShotScale;			//快照缩放尺寸

};

struct Struct1DataSpace
{
    StructRawImage ImageArray[ IMAGE_ARRAY_SIZE ];
    long WriteIndex;

    Struct1GlobalInfo GlobalInfo;
};

class QSharedMem : public CFredSharedMemory
{
public:
    QSharedMem(QObject *parent = 0);
    ~QSharedMem();

    bool Open(QString ClientIP);
    void Close(void);
    Struct1DataSpace* GetPtrDataSpace(void);
    Struct1GlobalInfo* GetPtrGlobalInfo(void);
    void WriteRawData(BYTE* pBuf, long Size);
    void ReadRawData(StructRawImage* &pRaw, long &ReadIndex);

    static void NoviceGetLocalTime(SYSTEMTIME &time);
};

//#endif // QSHAREDMEM_H
