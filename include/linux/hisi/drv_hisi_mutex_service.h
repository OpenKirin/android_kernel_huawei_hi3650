

#ifndef __DRV_HISI_MUTEX_SERVICE_H__
#define __DRV_HISI_MUTEX_SERVICE_H__

typedef int (*pPREEMPTFUNC )(int param);

#define START_OK 0
#define START_TIMEOUT 1
#define START_ERROR 2
#define STATUS_INVALID 3

#define STOP_OK 0
#define STOP_ERROR -1

#define NOTIFY_PREEMPT_STRING "NOTIFY_PREEMPT"
#define ABEND "ABEND"

#define STATUS_ALIVE 0
#define T2  3 //����T2ʱ��Ϊ3��

/*ҵ������*/
#define MUTEX_SERVICE_WIFI_NAME "WIFI_DISPLAY"
#define MUTEX_SERVICE_MIRROR_NAME "MIRROR"
#define MUTEX_SERVICE_HMP_NAME "HMP"
#define MUTEX_SERVICE_HDMI_NAME "HDMI"

#define MUTEX_SERVICE_GROUP_ID 0 /*�л����ϵ��ҵ������ID*/

/*ҵ��ID*/
enum hisi_mutex_service_id {
    MUTEX_SERVICE_WIFIDIS_ID = 0,
    MUTEX_SERVICE_MIRROR_ID = 1,
    MUTEX_SERVICE_HMP_ID = 2,
    MUTEX_SERVICE_HDMI_ID = 3,
};

/*ҵ�����ȼ�*/
enum hisi_mutex_service_priority {
    MUTEX_SERVICE_PRIORITY_0 = 0,
    MUTEX_SERVICE_PRIORITY_1 = 1,
    MUTEX_SERVICE_PRIORITY_2 = 2,
    MUTEX_SERVICE_PRIORITY_3 = 3,
    MUTEX_SERVICE_PRIORITY_4 = 4,
    MUTEX_SERVICE_PRIORITY_5 = 5,
    MUTEX_SERVICE_PRIORITY_6 = 6,
    MUTEX_SERVICE_PRIORITY_7 = 7,
    MUTEX_SERVICE_PRIORITY_8 = 8,
    MUTEX_SERVICE_PRIORITY_9 = 9,
};

/*****************************************************************************
 Description : �ں�̬ҵ������ʱ����ע������ע��ĺ���
  History
  1.Date: 2013/11/22
    Author : l00249396
    Modification : Created function
*****************************************************************************/
extern int hisi_mutex_mng_service_start(int  hisi_id, int (*pPREEMPTFUNC)(int param));
/*****************************************************************************
 Description : �ں�̬ҵ��ֹͣʱ����ע������ע��ĺ���
  History
  1.Date: 2013/11/22
    Author : l00249396
    Modification : Created function
*****************************************************************************/
extern int hisi_mutex_mng_service_stop(int  hisi_id);
/*****************************************************************************
 Description : �ⲿ�ӿڣ��ں�̬ҵ�������󣬵��ô˺�����������
  History
  1.Date: 2013/12/10
    Author : b00260479
    Modification : Created function
*****************************************************************************/
extern int hisi_mutex_mng_notify_alive(int  hisi_id);
#endif