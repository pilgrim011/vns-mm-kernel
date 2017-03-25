/******************************************************************************

                  ��Ȩ���� (C), 2014-2021, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2014��11��7��
  ����޸�   :
  ��������   : TafXCallTimerMgmt.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_XCALL_TIMERMGMT_H__
#define __TAF_XCALL_TIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define             TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD_LEN                (30000)  /* silently redial �ܶ�ʱ��ʱ�� */
#define             TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN              (4000)   /* silently redial ���ʱ�� */
#define             TAF_XCALL_TIMER_TICK                                     (10)

#define             TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN      (360)   /* ͬһ��Stop Cont DTMF��Start�ļ��ʱ������Сֵ,��λ:ms */
#define             TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX      (1000)  /* ͬһ��Stop Cont DTMF��Start�ļ��ʱ�������ֵ,��λ:ms */

#define             TI_TAF_XCALL_TX01_LEN                                   (30000) /* TX01(�������TX101, TX201��TX401)Ϊ30s */
#define             TI_TAF_XCALL_T301_LEN                                   (50000) /* T301Ϊ50s */
#define             TI_TAF_XCALL_TX02_LEN                                   (6000)  /* TX02Ϊ6s */
#define             TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_LEN            (1000)  /* �ȴ�����ʱ��Ϊ1s */
#define             TI_TAF_XCALL_DELAY_SEND_ENCRYPT_LEN                     (2000)  /* �ܻ�������ʱ��������ʱ�� */
#define             TI_TAF_XCALL_REMOTE_CTRL_ANSWER_DEFAULT_TIMER_LEN       (600)   /* 10����, ��λs */
#define             TI_TAF_XCALL_REMOTE_CTRL_ANSWER_MAX_TIMER_LEN           (1800)  /* 30����, ��λs*/


#define             TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_LEN                (10000) /* ��Կ���¹����еȴ�KMC�ĸ���ȷ����Ϣʱ��Ϊ10s */

#define             TAF_XCALL_EMC_CALL_REDIAL_PERIOD_DEFAULT                (600)
#define             TAF_XCALL_ENCVOICE_REQ_DEFAULT_DELAY_TIMER_LEN          (2)     /* 2��    */
#define             TAF_XCALL_ENCVOICE_REQ_MAX_DELAY_TIMER_LEN              (10)    /* 10��   */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XCALL_TIMER_STATUS_ENUM
 �ṹ˵��  : XCALL��ʱ��״̬,ֹͣ������
  1.��    ��   : 2014��11��17��
    ��    ��   : W00176964
    �޸�����   : �½�
*****************************************************************************/
enum TAF_XCALL_TIMER_STATUS_ENUM
{
    TAF_XCALL_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    TAF_XCALL_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    TAF_XCALL_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_XCALL_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XCALL_TIMER_ID_ENUM_UINT32
 ö��˵��  : XCALLģ��Ķ�ʱ��IDö�ٶ���
 1.��    ��   : 2014��11��17��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
enum TAF_XCALL_TIMER_ID_ENUM
{
    TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD                             = MN_TIMER_CLASS_XCALL,/* silently redial �ܶ�ʱ�� */
    TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL,                                               /* silently redial �����ʱ�� */

    TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,                 /* Stop CONT DTMF�����Start Cont DTMF����֮��ļ����
                                                                        ���յ�Start Cont DTMF��������Ĭ��ʱ��360ms����ͨ��nv���� */

    TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER,                 /* �ܻ������еȴ�Orig����timer */

    TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,                            /* ��ʱ��Կ�����Ͷ�ʱ�� */

    TI_TAF_XCALL_TX01_TIMER,                                        /* TX01��ʱ�� */

    TI_TAF_XCALL_TX02_TIMER,                                        /* TX02��ʱ�� */

    TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER,                     /* ��Կ���¹����еȴ���Կ����ȷ����Ϣ��ʱ�� */

    TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER,                  /* Զ�̿��Ƶȴ�APӦ��ʱ�� */

    TI_TAF_XCALL_TIMER_BUTT
};
typedef VOS_UINT32 TAF_XCALL_TIMER_ID_ENUM_UINT32;



/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_XCALL_TIMER_CTX_STRU
 �ṹ˵��  : XCALL��ʱ������������
 1.��    ��   : 2014��11��17��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId;                              /* ��ʱ����ID */
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           ucCallId;                               /* ��ʱ������call ID */
    VOS_UINT8                           aucReserve[2];                          /* ����λ */
} TAF_XCALL_TIMER_CTX_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XCALL_TIMER_INFO_STRU
 �ṹ˵��  : log��XCALL��ʱ���������
 1.��    ��   : 2014��11��17��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           ucCallId;           /* ��ʱ������call ID */
    VOS_UINT8                           aucReserve[2];      /* ����λ */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_XCALL_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 �ⲿ������������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID  TAF_XCALL_StartTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
);

VOS_VOID  TAF_XCALL_StopTimer(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
);

TAF_XCALL_TIMER_STATUS_ENUM_UINT8  TAF_XCALL_GetTimerStatus(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId
);

VOS_VOID  TAF_XCALL_InitAllTimers(
    TAF_XCALL_TIMER_CTX_STRU           *pstXcallTimerCtx
);

VOS_VOID  TAF_XCALL_SndOmTimerStatus(
    TAF_XCALL_TIMER_STATUS_ENUM_UINT8   enTimerStatus,
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_GetRemainTimerLen(
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId,
    VOS_UINT8                           ucCallId,
    VOS_UINT32                         *pulRemainTimeLen
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafXCallTimerMgmt.h */


