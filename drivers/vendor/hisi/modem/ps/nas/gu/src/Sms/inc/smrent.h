/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmrEnt.h
  Description : smrʵ��ṹ����
  History     :
      1.  ��־��   2004.2.24   �°�����
  2.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
  3.Data :2007-08-20
    Author:z40661
    Modify:A32D12705
  4.��    ��   : 2009��3��23��
    ��    ��   : f62575
    �޸�����   : AT2D08752, W���뷽ʽ�£��źŽ���ʱ�������Ͷ������Ż�����Գ��ַ��Ͳ���ʧ�ܣ�
  5.��    ��   : 2010��3��1��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941�����Ӷ��Ź��������طŹ���
*******************************************************************************/
#ifndef _SMR_ENTITY_H_
#define _SMR_ENTITY_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

#define SMR_MIN_RP_DATA_LEN             0x05
#define SMR_MIN_RP_ACK_LEN              0x02
#define SMR_MIN_RP_ERROR_LEN            0x04

#define  SMR_MAX_ENT_NUM     1

/* TIMERʱ�� */
#define SMR_TIMER_TR1M_LENGTH           (45000)

#define SMR_TIMER_TRAM_LENGTH     30000
#define SMR_TIMER_TR2M_LENGTH     15000
#define SMR_TIMER_TRRM_LENGTH     10000


typedef struct{
    HTIMER                              TimerId;                                                  /* Timer Id                                 */
    VOS_UINT8                           ucTimerSta;                                               /* ��ʶTimer�Ƿ���Ч                        */
    VOS_UINT8                           aucReserved1[3];
}SMR_TIMER_MNG_STRU;

typedef struct
{
    struct{
        VOS_UINT8                       ucState;                                                      /* SMRʵ��״̬                              */
        VOS_UINT8                       ucMr;                                                         /* Message Reference                        */
        VOS_UINT8                       ucMemAvailFlg;                                                /* ��־�Ƿ���֪ͨ����                       */
        VOS_UINT8                       ucRetransFlg;                                                 /* �Ƿ��ش���־                             */
        SMR_TIMER_MNG_STRU              aTimerInfo[3];                                     /* TIMER��Ϣ                                */
    }SmrMo;
    struct{
        VOS_UINT8                       ucState;                                                      /* SMRʵ��״̬                              */
        VOS_UINT8                       ucMr;                                                         /* Message Reference                        */
        VOS_UINT8                       aucReserved1[2];
        SMR_TIMER_MNG_STRU              TimerInfo;                                         /* TIMER��Ϣ                                */
        SMR_TIMER_MNG_STRU              RelTimerInfo;                                          /* Release TIMER��Ϣ                        */
    } SmrMt;

} SMR_ENTITY_STRU;

extern SMR_ENTITY_STRU     g_SmrEnt;                                            /* smr��ʵ������                            */

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif

