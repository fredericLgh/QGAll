/*********************************************************************

	NetMsg.h	������Ϣ���˿ڶ���

*********************************************************************/

#pragma once

#define NETMSG_HEART_BEAT				10001L
#define NETMSG_HEART_ACK				10002L

//******************* ����Ա to ������ ******************************
#define NETMSG_SET_PLAYSTATUS			12001L			//����ϵͳ״̬
#define NETMSG_SET_COMINGCOIL			12002L			//�趨Ĭ�ϵĴ�����Ϣ
#define NETMSG_SET_BAN					12003L			//�趨���
#define NETMSG_CHANGE_NEXT				12004L			//�������
#define NETMSG_QUERY_DEFECTS			12005L			//����ȱ����Ϣ


//******************* ������ to ����Ա ******************************
#define NETMSG_SYSTEM_WARNING			12011L			//�澯��ϵͳ��Ϣ����
#define NETMSG_RETURN_PLAYSTATUS		12012L			//����ϵͳ״̬
#define NETMSG_SERVER_COILINFO			12013L			//������Ϣ���и��ڼ䶨ʱ���ͣ�
#define NETMSG_INIT_OPERATOR			12014L			//OnLine�������Ӻ󣬵�һʱ��ͬ��ϵͳ����
#define NETMSG_COIL_COMING				12015L			//���ֵ���
#define NETMSG_COIL_LEAVING				12016L			//�����뿪
#define NETMSG_RETURN_BAN				12017L			//���ذ����Ϣ
#define NETMSG_VERSION					12018L			//����汾��Ϣ
#define NETMSG_SYSTEM_REALTIME_STATUS	12019L			//ϵͳʵʱ״̬��Ϣ


//******************* �ɼ��� to ������ ******************************
#define NETMSG_SAMPLE_WARNING			12022L			//�ɼ��˸澯��Ϣ
#define NETMSG_FRAME_RESULT				12023L			//֡�����
#define NETMSG_APPLYPARAM_OK			12024L			//���¼��ز����ɹ�


//******************* ������ to �ɼ��� ******************************
#define NETMSG_NEW_COILID				12031L			//���ֿ�ʼ�ź�
#define NETMSG_END_COILID				12032L			//���ֽ����ź�
#define NETMSG_SET_STATUS				12033L			//ϵͳ״̬֪ͨ
#define NETMSG_NODE_CONFIG				12034L			//CCD�ڵ��ʼ��
#define NETMSG_SET_CURRENTCOIL			12035L			//�趨��ǰ��ID�ȣ��ڼ�����;����ʱ��ϵͳ�������У�
#define NETMSG_SEND_PARAM				12036L			//�·�����
#define NETMSG_APPLY_PARAM				12037L			//Ӧ�ò���



//********************** UDP��Ϣ(�㲥) *****************************
#define NETMSG_TIME_SYNC				13101L			//ʱ��ͬ���źţ�Server����OptControl�գ�
#define NETMSG_LED_ON					13105L			//�򿪹�Դ
#define NETMSG_LED_OFF					13106L			//�رչ�Դ
#define NETMSG_LED_SET					13107L			//��Դǿ������


//********************** UDP��Ϣ(����) *****************************
#define NETMSG_REQ_LED_AUTO				13204L			//�Զ�������Դ ope to server
#define NETMSG_REQ_LED_ON				13205L			//�����LED  ope to server
#define NETMSG_REQ_LED_OFF				13206L			//����ر�LED  ope to server
#define NETMSG_REQ_LED_SET				13207L			//��������LED  ope to server





//----------------------------------------------------------------------- ����˿� --------------------------------------------------------------------------------


#define NETPORT_1TO2					6001			//����������
#define NETPORT_3TO2					6003			//����������
#define NETPORT_2TO3					6004			//����������

#define NETPORT_FILE_SERVER				6080			//File���շ�����
#define NETPORT_PICTURE_SERVER			6081			//Picture���շ�����
#define NETPORT_SNAPSHOT_SERVER			6082			//SnapShot���շ�����

#define NETPORT_FILE_DISPATCHER			6085			//File�ɷ�����
#define NETPORT_PICTURE_DISPATCHER		6086			//Picture�ɷ�����
#define NETPORT_SNAPSHOT_DISPATCHER		6088			//SnapShot�ɷ�����

#define	NETPORT_SYNCBOARD				6084			//ͬ��ģ��
#define NETPORT_XML						6087			//XML�ɷ�����



#define NET_UDP_CLOCK_SYNC_SERVER		6041			//������ʱ��ͬ��UDP
#define NET_UDP_CLOCK_SYNC_CLIENT		6040

#define NET_UDP_WAVE_FRONT				6030			//����궨
#define NET_UDP_WAVE_END				6031

#define NET_UDP_LED_CLIENT				6020			//��Դ����
#define NET_UDP_LED_SERVER				6021
#define NET_UDP_LED_OPERATOR			6022

