/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��5��9��
  ����޸�   :
  ��������   : TafSpmTimerMgmt.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_SPM_TIMERMGMT_H__
#define __TAF_SPM_TIMERMGMT_H__

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
/* ��ǿ�ͻ��鷢������ϵ�ˣ�����FDN/CC���ı���ʱ��������8s */
#define             TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF_LEN                (8000)
#define             TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF_LEN              (8000)

/* Added by y00245242 for VoLTE_PhaseII  ��Ŀ, 2013-9-23, begin */
/*
 * The following service request timer value dependence on:
 *  1. SMS: AT_SMS_CMGS_SET_PARA_TIME/AT_SMS_CMSS_SET_PARA_TIME
 *  2. SS: AT_SS_SET_PARA_TIME/AT_SS_QRY_PARA_TIME
 *  3. CC: AT_SET_PARA_TIME.
 * see ATCmdProc.h file.
 */
#define             TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL             (25000)             /* CCҵ�����󱣻���ʱ��ֵ */
#define             TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL            (30000)             /* SMSҵ�����󱣻���ʱ��ֵ */
#define             TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL             (30000)             /* SSҵ�����󱣻���ʱ��ֵ */
/* Added by y00245242 for VoLTE_PhaseII  ��Ŀ, 2013-9-23, end */

#define             TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL      (3000)      /* CCҵ�����󱣻���ʱ��Ĭ��ֵ */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
#define             TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL           (90000)             /* ecall CCҵ�����󱣻���ʱ��ֵ��T305+2*T308 */
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, end */

#define             TAF_SPM_MAX_TIMER_NUM                               (10)                /* spm��ͬʱ���еĶ�ʱ���������Ŀ */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_SPM_TIMER_STATUS_ENUM
 �ṹ˵��  : SPM��ʱ��״̬,ֹͣ������
  1.��    ��   : 2013��5��9��
    ��    ��   : W00176964
    �޸�����   : �½�
*****************************************************************************/
enum TAF_SPM_TIMER_STATUS_ENUM
{
    TAF_SPM_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    TAF_SPM_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    TAF_SPM_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_SPM_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_SPM_TIMER_ID_ENUM_UINT32
 ö��˵��  : MN��spmģ��Ķ�ʱ��IDö�ٶ���
 1.��    ��   : 2013��5��8��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/                     
enum TAF_SPM_TIMER_ID_ENUM
{
    TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF                             = MN_TIMER_CLASS_SPM,/* �ȴ�PB��FDN�����������ʱ�� */
    TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF,                                               /* �ȴ�USIM��call control�����������ʱ�� */
/* Added by y00245242 for VoLTE_PhaseII  ��Ŀ, 2013-9-23, begin */
    TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,                                                /* CC ҵ�����󱣻���ʱ�� */
    TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER,                                               /* SMS ҵ�����󱣻���ʱ�� */
    TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER,                                                /* SS ҵ�����󱣻���ʱ�� */
/* Added by y00245242 for VoLTE_PhaseII  ��Ŀ, 2013-9-23, end */
    
    TI_TAF_SPM_TIMER_BUTT
};
typedef VOS_UINT32 TAF_SPM_TIMER_ID_ENUM_UINT32;



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
 �ṹ��    : TAF_SPM_TIMER_CTX_STRU
 �ṹ˵��  : spm��ʱ������������
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId;                              /* ��ʱ����ID */
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[1];                          /* ����λ */
    VOS_UINT16                          usClientId;                             /* ��ʱ��������client PID */
} TAF_SPM_TIMER_CTX_STRU;


/*****************************************************************************
 �ṹ��    : TAF_SPM_TIMER_INFO_STRU
 �ṹ˵��  : log��SPM��ʱ���������
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           aucReserve[1];      /* ����λ */    
    VOS_UINT16                          usClientId;         /* ��ʱ������client ID */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_SPM_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 �ⲿ������������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  TAF_SPM_StartTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
);

VOS_VOID  TAF_SPM_StopTimer(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
);

TAF_SPM_TIMER_STATUS_ENUM_UINT8  TAF_SPM_GetTimerStatus(
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT16                          usClientId
);

VOS_VOID  TAF_SPM_InitAllTimers(
    TAF_SPM_TIMER_CTX_STRU              *pstSpmTimerCtx
);

VOS_VOID  TAF_SPM_SndOmTimerStatus(
    TAF_SPM_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_SPM_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT16                          usClientId
);

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

#endif /* end of TafSpmTimerMgmt.h */

