/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��28��
  ��������   : CnasTimerMgmt.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��28��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef _CNAS_TIMER_MGMT_H_
#define _CNAS_TIMER_MGMT_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ע: �ݶ���CANS����timer�������ĿΪ20��������ȷ��ÿ��ģ��ͬʱ������ʱ���������Ŀʱ���� */
#define CNAS_MAX_TIMER_RUNNING_NUM                          (20)

#define CNAS_TIMER_TICK                                     (10)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_TIMER_STATUS_ENUM
 ö��˵��  : ��ʱ��״̬IDö�ٶ���
 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_TIMER_STATUS_ENUM
{
    CNAS_TIMER_STATUS_STOP                              = 0x00,

    CNAS_TIMER_STATUS_RUNNING                           = 0x01,

    CNAS_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_TIMER_STATUS_ENUM_UINT8;

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
 �ṹ��    : CNAS_TIMER_INFO_STRU
 �ṹ˵��  : CNAS��ʱ����Ϣ�ṹ

 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerId;          /* ��ʱ����ʶ */
    VOS_UINT32                          ulParam;            /* ��ʱ��������ʶ, ����ͬtimer ID��ͬ���ױ�ʶ */
    VOS_UINT32                          ulTimerLen;         /* ��ʱ��ʱ�� */
    VOS_UINT32                          ulTimerPrecision;   /* ��ʱ������ */
}CNAS_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CNAS_TIMER_CTX_STRU
 �ṹ˵��  : CNAS��ʱ����Ϣ�ṹ

 1.��    ��   : 2014��07��03��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    HTIMER                              pTimerHandle;       /* timer ���*/
    VOS_UINT32                          ulPid;              /* ����timer��PID���� */
    VOS_UINT32                          ulParam;            /* ��ʱ��������ʶ */
    VOS_UINT32                          ulTimerId;          /* timer��ʶ */
    CNAS_TIMER_STATUS_ENUM_UINT8        enTimerStatus;      /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserved1[3];    /* �ֽڶ��뱣��λ */
}CNAS_TIMER_CTX_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
CNAS_TIMER_CTX_STRU* CNAS_GetTimerCtxAddr(VOS_VOID);

VOS_VOID CNAS_InitTimerCtx(VOS_VOID);

CNAS_TIMER_CTX_STRU* CNAS_GetAFreeTimerCtx(VOS_VOID);

VOS_VOID CNAS_StartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
);

VOS_VOID CNAS_RestartTimer(
    VOS_UINT32                          ulPid,
    CNAS_TIMER_INFO_STRU               *pstTimerInfo
);

VOS_VOID CNAS_StopTimer(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ucTimerId,
    VOS_UINT32                          ulPara
);

VOS_VOID CNAS_StopAllTimerWithSpecifiedPid(
    VOS_UINT32                          ulPid
);

CNAS_TIMER_CTX_STRU* CNAS_GetSpecifiedTimerCtx(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulPara
);

CNAS_TIMER_STATUS_ENUM_UINT8 CNAS_GetSpecifiedTimerStatus(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulTimerId,
    VOS_UINT32                          ulParam
);

VOS_UINT32 CNAS_GetSpecifiedTimerRemainLen(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ucTimerId,
    VOS_UINT32                          ulPara
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

#endif /* end of CnasTimerMgmt.h */
