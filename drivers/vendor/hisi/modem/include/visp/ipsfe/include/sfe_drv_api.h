/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_drv_api.h
*
*  Project Code: V1.1.0
*   Module Name: DRIVER
*  Date Created: 2010-9-16
*        Author: h00121208
*   Description: ����ģ��APIͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-9-16    h00121208                 Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_DRV_API_H_
#define _SFE_DRV_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif
/*ERRORCODE<������Driverģ�������>*/
typedef enum enumSfeDrvErrCode
{
    SFE_DRV_OK = SFE_OK,                                    /* �����ɹ� */
    SFE_DRV_ERR_BEGIN = SFE_DRV_BEGIN_RET_CODE,             /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_DRV_ZCOPY_INIT_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL,    /* 1  �㿽��������ʼ��ʱ,��ȡVCPU����Ԥ����ʧ�� */
    SFE_DRV_INIT_MALLOC_ZFD_FAIL,                           /* 2  �㿽��������ʼ��ʱ,�������㿽���豸�������Ĺ����ڴ�ʧ�� */
    SFE_DRV_ZCOPY_INIT_OPEN_DEV_FAIL,                       /* 3  �㿽��������ʼ��ʱ,���ַ��豸ʧ�� */
    SFE_DRV_ZCOPY_INIT_OPEN_BUFDEV_FAIL,                    /* 4  �㿽��������ʼ��ʱ,��ר�����ڻ�ȡ���Ľ��շ��Ͷ��е��ļ�����ַ��豸ʧ�� */
    SFE_DRV_ZCOPY_INIT_MMAP_FAIL,                           /* 5  �㿽��������ʼ��ʱ,MMAP Zcopy���Ľ��շ��Ͷ����ڴ��û�̬��ַʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ZCOPY_KNLSTART_ADDR_FAIL,        /* 6  �㿽��������ʼ��ʱ,��ȡZcopy���Ľ��շ��Ͷ����ڴ��ں�̬��ʼ��ַʧ�� */
    SFE_DRV_INIT_ADD_ZFD_FAIL,                              /* 7  �㿽��������ʼ��ʱ,���㿽���豸�������Ĺ����ڴ���ӵ��������ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_RCV_MEM_USER_ADDR_FAIL,             /* 8  �㿽��������ʼ��ʱ,�����ű��Ľ�����Ϣ�����û�̬��ַ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_GET_RCV_BUF_KNL_ADDR_FAIL,                 /* 9  �㿽��������ʼ��ʱ,��ȡ���Ľ�����Ϣ�����ڴ���ں�̬��ַʧ�� */
    SFE_DRV_INIT_ADD_RCV_BUF_USER_ADDR_FAIL,                /* 10 �㿽��������ʼ��ʱ,����ű��Ľ�����Ϣ�����û�̬��ַ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_SND_MEM_KNL_ADDR_FAIL,              /* 11 �㿽��������ʼ��ʱ,�����ű��ķ�����Ϣ�����ں�̬��ַ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_GET_SND_BUF_KNL_ADDR_FAIL,                 /* 12 �㿽��������ʼ��ʱ,��ȡ���ķ�����Ϣ�����ڴ���ں�̬��ַʧ�� */
    SFE_DRV_INIT_ADD_SND_BUF_KNL_ADDR_FAIL,                 /* 13 �㿽��������ʼ��ʱ,����ű��ķ�����Ϣ�����ں�̬��ַ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_SND_MEM_USER_ADDR_FAIL,             /* 14 �㿽��������ʼ��ʱ,�����ű��ķ�����Ϣ�����û�̬��ַ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_ADD_SND_BUF_USER_ADDR_FAIL,                /* 15 �㿽��������ʼ��ʱ,����ű��ķ�����Ϣ�����û�̬��ַ�Ĺ����ڴ���빲�����ֿ�ʧ�� */

    SFE_DRV_INIT_MALLOC_VCPU_SM_MEM_FAIL,                   /* 16 �㿽��������ʼ��ʱ,�����������ź����Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_CREATE_VCPU_SM_FAIL,                       /* 17 �㿽��������ʼ��ʱ,���������ź���ʧ�� */
    SFE_DRV_INIT_ADD_NAMEDB_VCPU_SM_FAIL,                   /* 18 �㿽��������ʼ��ʱ,�������ź����Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_PKT_RCV_INFO_FAIL,                  /* 19 �㿽��������ʼ��ʱ,�����ű��Ľ�����Ϣ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_RCV_PKT_MAX_NUM_PRECFG_FAIL,/* 20 �㿽��������ʼ��ʱ,��ȡ��������һ�δ��ں˽��յ�����ĸ�����Ԥ����ʧ�� */
    SFE_DRV_INIT_ADD_PKT_RCV_INFO_FAIL,                     /* 21 �㿽��������ʼ��ʱ,����ű��Ľ�����Ϣ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_INIT_MALLOC_PKT_SND_INFO_FAIL,                  /* 22 �㿽��������ʼ��ʱ,�����ű��ķ�����Ϣ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_SND_PKT_MAX_NUM_PRECFG_FAIL,/* 23 �㿽��������ʼ��ʱ,��ȡ��������һ�δ��ں˷��͵�����ĸ�����Ԥ����ʧ�� */
    SFE_DRV_ZCOPY_INIT_GET_ONCE_SND_TIMEOUT_PRECFG_FAIL,    /* 24 �㿽��������ʼ��ʱ,��ȡ��������һ�δ��ں˷��͵ĳ�ʱʱ��Ԥ����ʧ�� */
    SFE_DRV_INIT_ADD_PKT_SND_INFO_FAIL,                     /* 25 �㿽��������ʼ��ʱ,����ű��ķ�����Ϣ�Ĺ����ڴ���빲�����ֿ�ʧ�� */
    SFE_DRV_MALLOC_VCPU_DRVTIMER_MEM_FAIL,                  /* 26 �㿽����ʱ����ʼ��ʱ,�����Ŷ�ʱ���Ĺ����ڴ�ʧ�� */
    SFE_DRV_CREATE_VCPU_DRV_TIMER_FAIL,                     /* 27 �㿽����ʱ����ʼ��ʱ,����200MS��ʱ��ʧ�� */
    SFE_DRV_ADD_NAMEDB_VCPU_DRV_FAIL,                       /* 28 �㿽����ʱ����ʼ��ʱ,����Ŷ�ʱ���Ĺ����ڴ���빲�����ֿ�ʧ�� */

    SFE_DRV_TASK_INIT_CREATETASK_FAIL,                      /* 29 �㿽��������ʼ��ʱ,���������߳�ʧ�� */
    SFE_DRV_TASK_INIT_BINDTASK_FAIL,                        /* 30 �㿽��������ʼ��ʱ,�������̵߳�ָ��VCPUʧ�� */

    SFE_DRV_ERR_RCVPKT,                                     /* 31 �������ձ���ʧ�� */
    SFE_DRV_ERR_INTF_CREATESOCKET_INIT,                     /* 32 ������ʼ��ʱ,����Socketʧ�� */

    SFE_DRV_ERR_INTF_OPERIF_INIT,                           /* 33 ������ʼ��ʱ,����������ӽӿ�ʧ�� */
    SFE_DRV_ERR_INTF_GETIFHWADDR_INIT,                      /* 34 ������ʼ��ʱ,��Liunx��ȡӲ��physical��ַʧ�� */

    SFE_DRV_INIT_GET_SFE_DRV_INTF_MNG_MAX_NUM_PRECFG_FAIL,  /* 35 �����ӿڹ����ʼ��ʱ,��ȡ�����ӿڹ���֧�ֹ�������ӿ���Ԥ����ֵʧ�� */
    SFE_DRV_MALLOC_INTF_MNG_POOL_FAIL,                      /* 36 �����ӿڹ����ʼ��ʱ,���������ӿڹ��������ʧ�� */
    SFE_DRV_INIT_MALLOC_DRV_INFO_FAIL,                      /* 37 �����ӿڹ����ʼ��ʱ,��������������Ϣ�Ĺ����ڴ�ʧ�� */
    SFE_DRV_INIT_ADD_DRV_INFO_FAIL,                         /* 38 �����ӿڹ����ʼ��ʱ,����������Ϣ�Ĺ����ڴ���ӵ��������ֿ�ʧ�� */
    SFE_DRV_MALLOC_INTF_MNGINTF_FAIL,                       /* 39 �����ӿڹ����ʼ��ʱ,��Linux��ȡ�ӿ���Ϣ,����Linux�ӿڶ�Ӧ��VISP������ӿ�ʧ�� */

    SFE_DRV_ADD_INTF_ALREADY_EXIST,                         /* 40 ��ӽӿ�,�ӿ��Ѵ��� */
    SFE_DRV_ADD_INTF_NUM_EXCEED_MAX,                        /* 41 ��ӽӿ�,�ӿ��Ѵﵽ����� */
    SFE_DRV_ADD_ALL_PORT_ID_IS_USED,                        /* 42 ��ӽӿ�,��ͻ�����������˿ڸ���,���ж˿ڶ���ʹ���� */
    SFE_DRV_ADD_POOL_ALLOC_UNIT_FAIL,                       /* 43 ��ӽӿ�,�����µ�POOL�ڵ�ʧ�� */
    SFE_DRV_ADD_GET_POOL_NODE_FAIL,                         /* 44 ��ӽӿ�,��ȡ�����POOL���нڵ��ַʧ�� */

    SFE_DRV_DEL_INTF_NOT_EXIST,                             /* 45 ɾ���ӿ�,��ɾ���Ľڵ㲻���� */

    SFE_DRV_INIT_GET_DEV_INFO_FAIL,                         /* 46 ��ʼ����ӽӿ�,��ȡLinux�ӿ���Ϣʧ�� */
    SFE_DRV_INIT_GET_DEV_NUM_INVALID,                       /* 47 ��ʼ����ӽӿ�,�ӿڸ��������˵�ǰ֧�ֵ���������С����С��� */

    SFE_DRV_RCVPKT_INPUT_MBUF_POINTER_NULL,                 /* 48 �㿽�������������Ľ���,�������MBUFָ��ΪNULL */
    SFE_DRV_RCVPKT_VCPUID_INVALID,                          /* 49 �㿽�������������Ľ���,VCPU ID�Ƿ� */
    SFE_DRV_RCVPKT_IOCTL_FAIL,                              /* 50 �㿽�������������Ľ���,��ȡʵ�ʽ��ձ��ĸ���ʧ�� */
    SFE_DRV_RCVPKT_GET_IFID_FAIL,                           /* 51 �㿽�������������Ľ���,�����豸ID��ȡ������ӿ�IDʧ�� */

    SFE_DRV_GETIFID_MODULE_NOT_INIT,                        /* 52 �����豸ID��ȡ������ӿ�ID,�������ָ��ΪNULL,������ģ��û�г�ʼ�� */
    SFE_DRV_GETIFID_INPUT_POINTER_NULL,                     /* 53 �����豸ID��ȡ������ӿ�ID,�����������ӿ�IDָ��Ϊ�� */
    SFE_DRV_GETIFID_DEVID_NOT_EXSIT,                        /* 54 �����豸ID��ȡ������ӿ�ID,�ڵ㲻���� */

    SFE_DRV_GETDEVID_INPUT_IFID_POINTER_NULL,               /* 55 ����������ӿ�ID��ȡ�豸ID,�����������ӿ�IDΪ�� */
    SFE_DRV_GETDEVID_INPUT_DEVID_POINTER_NULL,              /* 56 ����������ӿ�ID��ȡ�豸ID,������豸IDָ��Ϊ�� */
    SFE_DRV_GETDEVID_IFID_NOT_EXSIT,                        /* 57 ����������ӿ�ID��ȡ�豸ID,�ڵ㲻���� */

    SFE_DRV_SNDPKT_INPUT_MBUF_POINTER_NULL,                 /* 58 �㿽�������������ķ���,����MBUFָ��ΪNULL */
    SFE_DRV_SNDPKT_VCPUID_INVALID,                          /* 59 �㿽�������������ķ���,VCPU ID�Ƿ� */
    SFE_DRV_SNDPKT_GET_DEVID_FAIL,                          /* 60 �㿽�������������ķ���,��ȡ�����ӿ��豸IDʧ�� */
    SFE_DRV_SND_TO_KNL_FAIL,                                /* 61 ������ͨ��ioctl���͵��ں�̬ʱʧ�� */

    SFE_DRV_SET_PKTRCVQUE_MODULE_NOT_INIT,                  /* 62 �����㿽���������Ľ��ն�����Ϣʱ,�������ָ��ΪNULL,������ģ��û�г�ʼ�� */
    SFE_DRV_SET_PKTRCVQUE_VCPUID_INVALID,                   /* 63 �����㿽���������Ľ��ն�����Ϣʱ,VCPU ID�Ƿ� */
    SFE_DRV_SET_PKTRCVQUE_LEN_INVALID,                      /* 64 �����㿽���������Ľ��ն�����Ϣʱ,����Ľ��ն��г��ȷǷ� */
    SFE_DRV_SET_PKTRCVQUE_WARMINGPARA_INVALID,              /* 65 �����㿽���������Ľ��ն�����Ϣʱ,����ĸ澯�����޲����Ƿ� */
    SFE_DRV_SET_PKTRCVQUE_IOCTL_FAIL,                       /* 66 �����㿽���������Ľ��ն�����Ϣʱ,����ioctl����ʧ�� */

    SFE_DRV_SET_DEVMTU_MODULE_NOT_INIT,                     /* 67 �����޸Ľӿ�MTUʱ,�������ָ��ΪNULL,������ģ��û�г�ʼ�� */
    SFE_DRV_SET_DEVMTU_DEVID_NOT_EXSIT,                     /* 68 �����޸Ľӿ�MTUʱ,�ӿڲ����� */
    SFE_DRV_INPUT_MTU_INVALID,                              /* 69 �����޸Ľӿ�MTUʱ,�����mtuֵ���Ϸ�,���ںϷ���Χ */

    SFE_DRV_INIT_MALLOC_DRVDEVMSG_FAIL,                     /* 70 ��ʼ����ӽӿ�,����DRVMSGINFO�ڴ�ʧ�� */
    SFE_DRV_RCVPKT_MBUF_VERSION_NOT_CONSISTENT,             /* 71 �㿽�������������Ľ���,�ں�̬���û�̬ʹ�õ�MBUFͷ�ļ��汾��һ�� */
    SFE_DRV_SETONCERCVSNDPKTNUM_MODULE_NOT_INIT,            /* 72 ����ָ������һ�δ��������պͷ��ͱ��ĸ���,ϵͳδ�������ܵ��� */
    SFE_DRV_SETONCERCVSNDPKTNUM_VCPUID_INVALID,             /* 73 ����ָ������һ�δ��������պͷ��ͱ��ĸ���,����˺ŷǷ� */
    SFE_DRV_SETONCERCVSNDPKTNUM_INPUTNUM_INVALID,           /* 74 ����ָ������һ�δ��������պͷ��ͱ��ĸ���,��������ò����Ƿ� */
}SFE_DRV_ERR_CODE_E;

/*MACRO<�������Ľ��ն�����Сֵ>*/
#define SFE_DRV_PKTRCVQUE_MIN_LEN   100
/*MACRO<�������Ľ��ն������ֵ>*/
#define SFE_DRV_PKTRCVQUE_MAX_LEN   20000

/*MACRO<�����ӿ�mtu��Сֵ>*/
#define SFE_DRV_IF_MTU_MIN_LEN   46
/*MACRO<�����ӿ�mtu���ֵ>*/
#define SFE_DRV_IF_MTU_MAX_LEN   1800

/*******************************************************************************
*    Func Name: SFE_ZEROCOPY_Init
* Date Created: 2010-09-20
*       Author: Gexianjun/00121208
*      Purpose: �㿽����ʼ������
*  Description: �㿽����ʼ������
*        Input: VOID
*       Output: 
*       Return: �ɹ����� SFE_DRV_OK
*               ʧ�ܷ��� ������
*      Caution: 1.�ú����ɲ�Ʒ����ʵ��Ӧ�õ���.��ǰSCG��ƷӦ���±�����øú���.
*               2.�㿽����ʼ����������������ģ���ʼ��֮ǰ����,
*                 �����������ȵ��õĺ���.
*               3.��ʼ��ʱ��������Դ�ͷ�����.����ʼ��ʧ��ʱ��������Դ���մ���.
*                 ԭ��:1)��ʼ�����̲�����ʧ��;
*                      2)�漰����˹�������,����ͷŻᵼ�������˷����쳣.
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-20   Gexianjun/00121208      Create
*
*******************************************************************************/
UINT32 SFE_ZEROCOPY_Init(VOID);

/*******************************************************************************
*    Func Name: SFE_DRV_Init
* Date Created: 2010-09-20
*       Author: Gexianjun/00121208
*      Purpose: ������ʼ������
*  Description: ������ʼ������
*        Input: VOID
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.�ú����ɲ�Ʒ����ʵ��Ӧ�õ���.��ǰSCG��ƷӦ���±�����øú���.
*               2.�ú���������VISP�������ʼ��SFE_Init֮�����.
*               3.��ʼ��ʱ��������Դ�ͷ�����.����ʼ��ʧ��ʱ��������Դ���մ���.
*                 ԭ��:1)��ʼ�����̲�����ʧ��;
*                      2)�漰����˹�������,����ͷŻᵼ�������˷����쳣.
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-20   Gexianjun/00121208      Create
*
*******************************************************************************/
UINT32 SFE_DRV_Init(VOID);

/*******************************************************************************
*    Func Name: SFE_DRV_SetPktRcvQueueInfo
* Date Created: 2010-10-5
*       Author: w60786
*      Purpose: ���õ�ǰ�˵��㿽���������Ľ�����Ϣ
*  Description: ���õ�ǰ�˵��㿽���������Ľ�����Ϣ(���ձ��Ķ��д�С,�澯����,�澯����)
*        Input: UINT32 u32VcpuId: ��Ҫ�޸ĵĽ��ն������ڵĺ�<����ֵ>
*               UINT32 u32RcvQueLen: �㿽���������Ľ��ն��д�С<SFE_DRV_PKTRCVQUE_MIN_LEN,SFE_DRV_PKTRCVQUE_MAX_LEN>
*               UINT32 u32WarningUpLimit: �澯����<SFE_DRV_PKTRCVQUE_MIN_LEN,SFE_DRV_PKTRCVQUE_MAX_LEN>
*                      ��ǰ�˽��ձ��Ķ����еı��ĸ������ڵ��ڸ澯����ʱ�ϱ��澯.
*               UINT32 u32WarningLowLimit: �澯����,<1,SFE_DRV_PKTRCVQUE_MAX_LEN>
*                      ��ǰ�˽��ձ��Ķ����еı��ĸ���С�ڵ��ڸ澯����ʱ�ϱ��澯����.
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.�ýӿ�ֻ�����õ�ǰ�˵ı��Ľ��ն�����Ϣ,����û���Ҫ����ÿ�����ϵ�
*                 ��Щ����,���û�������ÿ�����Ϸֱ���øýӿڽ�������.
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-10-5    w60786           Creat the first version.
*
*******************************************************************************/
UINT32 SFE_DRV_SetPktRcvQueueInfo(UINT32 u32VcpuId, UINT32 u32RcvQueLen, UINT32 u32WarningUpLimit, UINT32 u32WarningLowLimit);

/*******************************************************************************
*    Func Name: SFE_DRV_SetOnceRcvSndPktNum
* Date Created: 2011-1-13
*       Author: w60786
*      Purpose: ���õ�ǰ�˵�һ�δ��㿽���������պͷ��ͱ��ĸ���
*  Description: ���õ�ǰ�˵�һ�δ��㿽���������պͷ��ͱ��ĸ���(һ�δӽ��ձ��Ķ��н��ձ��ĸ���,һ�δӷ��ͱ��Ķ��з��ͱ��ĸ���)
*        Input: UINT32 u32VcpuId: ��Ҫ�޸ĵ��㿽�������շ����ĸ����������ڵĺ�<����ֵ>
*               UINT32 u32OnceRcvPktNum: һ�δ��㿽���������ձ��ĸ���<SFE_DRV_ONCE_RCV_PKT_MIN_NUM,SFE_DRV_ONCE_RCV_PKT_MAX_NUM>
*               UINT32 u32OnceSndPktNum: һ�δ��㿽���������ͱ��ĸ���<SFE_DRV_ONCE_SND_PKT_MIN_NUM,SFE_DRV_ONCE_SND_PKT_MAX_NUM>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.�ýӿ�ֻ����ϵͳ��ʼ����ɺ����,��ÿ�����ñ�������Ĳ�������Ч�������óɹ�.
*               2.�ýӿ�ֻ���õ�ǰ�˵�һ�δ��������պͷ��͵ı��ĸ���,����û���Ҫ����ÿ�����ϵ�
*                 ��Щ����,���û�������ÿ�����Ϸֱ���øýӿڽ�������.
*        Since: DOPRA VISP V2R3C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-1-13    w60786           Creat the first version.
*
*******************************************************************************/
UINT32 SFE_DRV_SetOnceRcvSndPktNum(UINT32 u32VcpuId, UINT32 u32OnceRcvPktNum, UINT32 u32OnceSndPktNum);

/*******************************************************************************
*    Func Name: SFE_DRV_SetDevMtu
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: ����ָ���豸�ӿڵ�MTUֵ
*  Description: ����ָ���豸�ӿڵ�MTUֵ
*        Input: UINT32 u32DevId:�豸ID(Linuxϵͳ�нӿڵĽӿ�����)
*               UINT32 u32Mtu:�µ�MTUֵ<46,1800>
*       Output: 
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
UINT32 SFE_DRV_SetDevMtu(UINT32 u32DevId, UINT32 u32Mtu);

/*******************************************************************************
*    Func Name: SFE_GetIfIdByDevId
* Date Created: 2010-06-07
*       Author: wuxiaowei 00161372 hexianjun 00121208
*      Purpose: �����豸ID��ȡ������ӿ�ID
*  Description: �����豸ID��ȡ������ӿ�ID
*        Input: UINT32 u32DevId: ��Ч���豸ID
*       Output: SFE_MBUF_IFID_S *pstIfId: ���豸ID��Ӧ��������ӿ�ID,�ڴ��ɲ�Ʒ�ṩ.
*       Return: �ɹ�:0
*               ʧ��:����
*      Caution: 1.��SCG��ƷӦ�ó�����,���ڲ�Ʒ��ȡָ��Linux�ӿڶ�Ӧ��VISP������ӿ���Ϣ.
*        Since: DOPRA VISP V2R3C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-07   wuxiaowei 00161372      Create
*               hexianjun 00121208
*
*******************************************************************************/
UINT32 SFE_GetIfIdByDevId(UINT32 u32DevId, SFE_MBUF_IFID_S *pstIfId);

/*******************************************************************************
*    Func Name: SFE_ShowAllDrvIntf
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: ��ʾ���������ӿڹ�����Ϣ
*  Description: ��ʾ���������ӿڹ�����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_ShowAllDrvIntf
*               SFE_ShowOneDrvIntf
*               SFE_ShowDrvInfoByVcpu
*               SFE_ShowAllDrvInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowAllDrvIntf(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowOneDrvIntf
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: ��ʾָ�������ӿڹ�����Ϣ
*  Description: ��ʾָ�������ӿڹ�����Ϣ
*        Input: UINT8 *pucDevName: �豸����
*       Output: 
*       Return: VOID
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_ShowAllDrvIntf
*               SFE_ShowOneDrvIntf
*               SFE_ShowDrvInfoByVcpu
*               SFE_ShowAllDrvInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowOneDrvIntf(UINT8 *pucDevName);

/*******************************************************************************
*    Func Name: SFE_ShowAllDrvInfo
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: ��ʾ�������������շ�������Ϣ
*  Description: ��ʾ�������������շ�������Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_ShowAllDrvIntf
*               SFE_ShowOneDrvIntf
*               SFE_ShowDrvInfoByVcpu
*               SFE_ShowAllDrvInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowAllDrvInfo(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowDrvInfoByVcpu
* Date Created: 2010-08-26
*       Author: zhangchi(00142640)
*      Purpose: ��ʾָ��VCPU�ϵ����������շ�������Ϣ
*  Description: ��ʾָ��VCPU�ϵ����������շ�������Ϣ
*        Input: UINT32 u32VcpuId: VCPU ID
*       Output: 
*       Return: VOID
*      Caution:
*        Since: DOPRA VISP V2R3C02
*    Reference: SFE_ShowAllDrvIntf
*               SFE_ShowOneDrvIntf
*               SFE_ShowDrvInfoByVcpu
*               SFE_ShowAllDrvInfo
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-26   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
VOID SFE_ShowDrvInfoByVcpu(UINT32 u32VcpuId);


#ifdef  __cplusplus
}
#endif

#endif


