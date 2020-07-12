/*********************************************************************

	NetMsg.h	网络消息及端口定义

*********************************************************************/

#pragma once

#define NETMSG_HEART_BEAT				10001L
#define NETMSG_HEART_ACK				10002L

//******************* 操作员 to 服务器 ******************************
#define NETMSG_SET_PLAYSTATUS			12001L			//设置系统状态
#define NETMSG_SET_COMINGCOIL			12002L			//设定默认的带钢信息
#define NETMSG_SET_BAN					12003L			//设定班次
#define NETMSG_CHANGE_NEXT				12004L			//点击换卷
#define NETMSG_QUERY_DEFECTS			12005L			//请求缺陷信息


//******************* 服务器 to 操作员 ******************************
#define NETMSG_SYSTEM_WARNING			12011L			//告警栏系统信息发布
#define NETMSG_RETURN_PLAYSTATUS		12012L			//返回系统状态
#define NETMSG_SERVER_COILINFO			12013L			//带钢信息（有钢期间定时发送）
#define NETMSG_INIT_OPERATOR			12014L			//OnLine建立连接后，第一时间同步系统参数
#define NETMSG_COIL_COMING				12015L			//带钢到达
#define NETMSG_COIL_LEAVING				12016L			//带钢离开
#define NETMSG_RETURN_BAN				12017L			//返回班次信息
#define NETMSG_VERSION					12018L			//软件版本信息
#define NETMSG_SYSTEM_REALTIME_STATUS	12019L			//系统实时状态信息


//******************* 采集端 to 服务器 ******************************
#define NETMSG_SAMPLE_WARNING			12022L			//采集端告警信息
#define NETMSG_FRAME_RESULT				12023L			//帧检测结果
#define NETMSG_APPLYPARAM_OK			12024L			//重新加载参数成功


//******************* 服务器 to 采集端 ******************************
#define NETMSG_NEW_COILID				12031L			//带钢开始信号
#define NETMSG_END_COILID				12032L			//带钢结束信号
#define NETMSG_SET_STATUS				12033L			//系统状态通知
#define NETMSG_NODE_CONFIG				12034L			//CCD节点初始化
#define NETMSG_SET_CURRENTCOIL			12035L			//设定当前钢ID等（在检测端中途连接时且系统正在运行）
#define NETMSG_SEND_PARAM				12036L			//下发参数
#define NETMSG_APPLY_PARAM				12037L			//应用参数



//********************** UDP消息(广播) *****************************
#define NETMSG_TIME_SYNC				13101L			//时间同步信号（Server发，OptControl收）
#define NETMSG_LED_ON					13105L			//打开光源
#define NETMSG_LED_OFF					13106L			//关闭光源
#define NETMSG_LED_SET					13107L			//光源强度设置


//********************** UDP消息(单播) *****************************
#define NETMSG_REQ_LED_AUTO				13204L			//自动调整光源 ope to server
#define NETMSG_REQ_LED_ON				13205L			//请求打开LED  ope to server
#define NETMSG_REQ_LED_OFF				13206L			//请求关闭LED  ope to server
#define NETMSG_REQ_LED_SET				13207L			//请求设置LED  ope to server





//----------------------------------------------------------------------- 网络端口 --------------------------------------------------------------------------------


#define NETPORT_1TO2					6001			//服务器监听
#define NETPORT_3TO2					6003			//服务器监听
#define NETPORT_2TO3					6004			//服务器监听

#define NETPORT_FILE_SERVER				6080			//File接收服务器
#define NETPORT_PICTURE_SERVER			6081			//Picture接收服务器
#define NETPORT_SNAPSHOT_SERVER			6082			//SnapShot接收服务器

#define NETPORT_FILE_DISPATCHER			6085			//File派发服务
#define NETPORT_PICTURE_DISPATCHER		6086			//Picture派发服务
#define NETPORT_SNAPSHOT_DISPATCHER		6088			//SnapShot派发服务

#define	NETPORT_SYNCBOARD				6084			//同步模块
#define NETPORT_XML						6087			//XML派发服务



#define NET_UDP_CLOCK_SYNC_SERVER		6041			//局域网时间同步UDP
#define NET_UDP_CLOCK_SYNC_CLIENT		6040

#define NET_UDP_WAVE_FRONT				6030			//相机标定
#define NET_UDP_WAVE_END				6031

#define NET_UDP_LED_CLIENT				6020			//光源控制
#define NET_UDP_LED_SERVER				6021
#define NET_UDP_LED_OPERATOR			6022

