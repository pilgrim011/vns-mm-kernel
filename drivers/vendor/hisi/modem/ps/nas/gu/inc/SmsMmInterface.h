/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmsMmInterface.h
  Description : SMS��MM�ӿ�ͷ�ļ�
  History     :
      1.  ��־��   2004.2.24   �°�����
      2.��    ��   : 2008��7��18��
        ��    ��   : luojian 00107747
        �޸�����   : �������ⵥ�ţ�AT2D04627/AT2D04237,
                     MM��IDEL ATTEMPT TO UPDATE״̬֧��SMS
*******************************************************************************/
#ifndef _SMS_MM_INTERFACE_H_
#define _SMS_MM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

/* SMC����MM����Ϣ                          */
#define MMSMS_EST_REQ                                       1
#define MMSMS_REL_REQ                                       3
#define MMSMS_ABORT_REQ                                     5
#define MMSMS_DATA_REQ                                      7

#define MMSMS_BEGIN_SESSION_NOTIFY                          (9)
#define MMSMS_END_SESSION_NOTIFY                            (11)

/* SMC����MM��ԭ��                          */
#define MMSMS_EST_CNF                                       0
#define MMSMS_EST_IND                                       2
#define MMSMS_REL_IND                                       4
#define MMSMS_DATA_IND                                      6
#define MMSMS_ERR_IND                                       8
#define MMSMS_REG_STATE_IND                                 10

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
#define MMSMS_NACK_DATA_IND                                (12)

/*****************************************************************************
 �ṹ��    : MMSMS_NACK_DATA_IND_STRU
 �ṹ˵��  : MMSMS_NACK_DATA_IND��Ϣ���Ӧ�������Ľṹ

  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK������DTS20121809369
*****************************************************************************/
typedef struct                                             
{                                                          
    MSG_HEADER_STRU                     MsgHeader;         
    NAS_MSG_STRU                        stNackMsg;
}MMSMS_NACK_DATA_IND_STRU;

/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/* ԭ��MMSMS_EST_REQ�Ľṹ��                */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ                                   */
    VOS_UINT32   ulTi;                                                               /* Transaction Id                           */

#define  RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL  15
    VOS_UINT32   ulEstCause;                                                         /* RRC���ӽ���ԭ��                          */
}MMSMS_EST_REQ_STRU;

/* ԭ��MMSMS_EST_CNF�Ľṹ��                */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                   */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                           */
}MMSMS_EST_CNF_STRU;

/* ԭ��MMSMS_EST_IND�Ľṹ��                */
typedef struct
{
    MSG_HEADER_STRU       MsgHeader;                                            /* ��Ϣͷ                                   */
    VOS_UINT32                 ulTi;                                                 /* Transaction Id                           */
    NAS_MSG_STRU          SmsMsg;                                               /* ��һ��SMC��Ϣ                            */
}MMSMS_EST_IND_STRU;

/* ԭ��MMSMS_REL_REQ�Ľṹ��                */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ                                   */
    VOS_UINT32               ulTi;                                                   /* transaction id                           */
}MMSMS_REL_REQ_STRU;

/* ԭ��MMSMS_REL_IND�Ľṹ��                */
#define   MMSMS_REL_CAUSE_ACCESS_BARRED         200                             /* access barred                            */
#define   MMSMS_REL_CAUSE_RR_CONN_EST_FAILURE   201                             /* RR connection establish failure          */
#define   MMSMS_REL_CAUSE_RR_CONN_FAILURE       202                             /* RR connection failure                    */
#define   MMSMS_REL_CAUSE_TIMER_TIMEOUT         203                             /* Timer timeout                            */
#define   MMSMS_REL_CAUSE_IMSI_DETACHED         204                             /* IMSI detached                            */
#define   MMSMS_REL_CAUSE_MM_EST_FAILURE        205                             /* MM��������ʧ��                           */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ                                   */
    VOS_UINT32   ulTi;                                                               /* Transaction Id                           */

    VOS_UINT32   ulRelCause;                                                         /* �ͷ�ԭ��                                 */
}MMSMS_REL_IND_STRU;

/* ԭ��MMSMS_DATA_REQ�Ľṹ��               */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulTi;                                                /* Transaction Id                           */
    NAS_MSG_STRU           SmsMsg;                                              /* ��Ҫ���͵�SMC��Ϣ                        */
}MMSMS_DATA_REQ_STRU;

/* ԭ��MMSMS_DATA_IND�Ľṹ��               */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulTi;                                                /* Transaction Id                           */
    NAS_MSG_STRU           SmsMsg;                                              /* MM�յ���SMC��Ϣ                          */
}MMSMS_DATA_IND_STRU;

/* ԭ��MMSMS_ABORT_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
}MMSMS_ABORT_REQ_STRU;

/*****************************************************************************
 ö����    : MMSMS_SESSION_TYPE_ENUM_UINT8
 ö��˵��  : SMS��SESSION����
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum MMSMS_SESSION_TYPE_ENUM
{
    MMSMS_SESSION_TYPE_MO_SMS,
    MMSMS_SESSION_TYPE_MT_SMS,
    MMSMS_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MMSMS_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : MMSMS_BEGIN_SESSION_NOTIFY_STRU
 �ṹ˵��  : SESSION��ʼָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSMS_SESSION_TYPE_ENUM_UINT8                   enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMSMS_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMSMS_END_SESSION_NOTIFY_STRU
 �ṹ˵��  : SESSION����ָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMSMS_SESSION_TYPE_ENUM_UINT8                   enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMSMS_END_SESSION_NOTIFY_STRU;



/* ԭ��MMSMS_REG_STATE_IND�Ľṹ�� */
#define    MM_SMS_REG_ATTACHED                              0                   /* �Ѿ�ע�� */
#define    MM_SMS_REG_DETACHED                              1                   /* û��ע��  */
#define    MM_SMS_REG_ATTACH_ATTEMPT_TO_UPDATE              2                   /* ������״̬��CM������񽫴���ע������ */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    VOS_UINT32                   ulRegSts;                                           /* ע��״̬                                 */
}MMSMS_REG_STATE_IND_STRU;

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
