/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmcEnt.h
  Description : SMCʵ��ṹ����
  History     :
      1.  ��־��   2004.2.24   �°�����
      2.  h44270  2006.02.07  �޸�TC1M�ļ�ʱ����ʱʱ��  A32D01938
  3.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
  4.Data :2007-08-20
    Author:z40661
    Modify:A32D12705
  5.Date         : 2008-05-07
    Author       : f62575
    Modification : MS�ڵȴ��������һ��CP-ACKʱ���յ�CP-DATA��Я��RP-DATA������
                   Ϊ�����Ľ��յ�ǰһ�����CP-ACK���µ�CP-DATA�¼����ο���Э��24011 5.3.4, 5.4
                   ���޸�TP-MMS�������ͷ�MM�����޹�
  6.��    ��   : 2009��3��23��
    ��    ��   : f62575
    �޸�����   : AT2D08752, W���뷽ʽ�£��źŽ���ʱ�������Ͷ������Ż�����Գ��ַ��Ͳ���ʧ�ܣ�
  7.��    ��   : 2010��2��20��
    ��    ��   : f62575
    �޸�����   : AT2D16941�����Ӷ��������طŹ���
*******************************************************************************/
#ifndef _SMC_ENTITY_H_
#define _SMC_ENTITY_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

#define SMC_MAX_EXPIRE_TIMES    2

#define SMC_TIMER_TC1M_LENGTH           (20000)

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
#define SMS_TPDU_MTI_PS                 (0x24)
#define SMS_TPDU_SCLEN_PS               (0x22)
#define SMS_TPDU_MTI_CS                 (0x28)
#define SMS_TPDU_SCLEN_CS               (0x26)
#define SMT_TP_RD_RETRANS               (0x04)                                                 /* RETRANSFER                               */
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */
#define    SMS_TPDU_SCLEN_LTE_PS        (0x26)
#define    SMS_TPDU_MTI_LTE_PS          (0x28)

/*****************************************************************************
 �ṹ��    : NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8
 �ṹ˵��  : SMS�л������Ϣ����

1. ��    ��   : 2015��1��27��
   ��    ��   : s00217060
   �޸�����   : ����ö��
*****************************************************************************/
enum NAS_SMS_HOLD_MSG_TYPE_ENUM
{
    NAS_SMS_HOLD_MSG_GU_MT_RP_ACK       = 0, 
    NAS_SMS_HOLD_MSG_LTE_MT_RP_ACK      = 1,
    NAS_SMS_HOLD_MSG_GU_MO_RP_DATA      = 2, 
    NAS_SMS_HOLD_MSG_LTE_MO_RP_DATA     = 3, 

    NAS_SMS_HOLD_MSG_BUTT
};
typedef VOS_UINT8 NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8;


typedef struct{
    VOS_UINT32                          ulMsgLen ;                                                   /* ��Ϣ����                                 */
    VOS_VOID                            *pMsg;                                                       /* ��Ϣ�׵�ַ                               */
}SMC_SAVE_MSG_STRU ;
typedef struct{
    HTIMER                              TimerId;                                                  /* Timer Id                                 */
    VOS_UINT8                           ucTimerSta;                                               /* ��ʶTimer�Ƿ���Ч                        */
    VOS_UINT8                           ucExpireTimes;                                            /* Timer��ʱ����                            */
    VOS_UINT8                           aucReserved1[2];
}SMC_TIMER_MNG_STRU;


typedef struct
{
    struct{
        VOS_UINT8                       ucState;                                                   /* SMC MOʵ���״̬                         */
        VOS_UINT8                       ucTi;                                                      /* Transaction ID                           */
        VOS_UINT8                       ucPreTi;                                                   /* ǰһ��TIֵ                               */
        VOS_UINT8                       ucMr;                                                      /* Message Reference                        */
        VOS_UINT8                       ucCpAckFlg;    /*�ò��������Ƿ���Ҫ������ظ�CP-ACK��Ϣ*/                                            /* �Ƿ���CP-ACK                           */
        NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8                  enHoldSndMsgType;                           /* SMS�л������Ϣ���� */
        VOS_UINT8                       aucReserved1[2];
        SMC_TIMER_MNG_STRU              TimerInfo;                                          /* ��ʵ���Ӧ��TIMER��Ϣ                    */
        SMC_SAVE_MSG_STRU               HoldRcvMsg;                                         /* ���������Ϣ�ĵ�ַ                       */
        SMC_SAVE_MSG_STRU               HoldSndMsg;                                         /* ���淢����Ϣ�ĵ�ַ                       */
    }SmcMo;
    struct{
          VOS_UINT8                     ucState;                                                 /* SMC MO��״̬                             */
          VOS_UINT8                     ucTi;                                                    /* Transaction ID                           */
          VOS_UINT8                     ucMr;                                                    /* Message Reference                        */
          NAS_SMS_HOLD_MSG_TYPE_ENUM_UINT8                  enHoldSndMsgType;                       /* SMS�л������Ϣ���� */
          SMC_TIMER_MNG_STRU            TimerInfo;                                        /* ��ʵ���Ӧ��TIMER��Ϣ                    */
          SMC_SAVE_MSG_STRU             HoldSndMsg;                                       /* ���淢����Ϣ�ĵ�ַ                       */
    }SmcMt;
}SMC_ENTITY_STRU;

extern SMC_ENTITY_STRU     g_SmcPsEnt;                                          /* sms ps���ʵ������                       */
extern SMC_ENTITY_STRU     g_SmcCsEnt;                                          /* sms cs���ʵ������                       */

extern VOS_UINT8               g_ucPsServiceStatus;                             /* GMM��PS���Ƿ�ע���־                    */
extern VOS_UINT8               g_ucCsRegFlg;                                          /* MM��CS���Ƿ�ע���־                    */

extern VOS_UINT8               g_ucSmsMR;
extern VOS_UINT8               g_ucCurSendDomain;
extern VOS_UINT8               g_SndDomain;                                   /* ������ */

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

