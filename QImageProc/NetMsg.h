#pragma once
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