/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdTimer.h
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2014��12��13��
  ����޸�   :
  ��������   : timer��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��13��
    ��    ��   : h00300378
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_HSD_TIMER_H__
#define __CNAS_HSD_TIMER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* HSD�ж�ʱ����ʱ�� */
#define TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN                  (30*1000)
#define TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN                  (6*1000)        /* ����12��Ϊ6s */

#define TI_CNAS_HSD_WAIT_EHSM_START_CNF_LEN                 (5*1000)

#define TI_CNAS_HSD_WAIT_HLU_START_CNF_LEN                  (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_START_CNF_LEN                  (5*1000)
#define TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF_LEN               (6*1000)
#define TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF_LEN              (21*1000)
#define TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF_LEN              (5*1000)
#define TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF_LEN               (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF_LEN               (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF_LEN                (6*1000)

#define TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF_LEN            (120*1000)  /* 20150407��65*16s��Ϊ120s */
#define TI_CNAS_HSD_WAIT_CAS_OHM_IND_LEN                    (60*1000)
#define TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN       (5*1000)
#define TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_ACQUIRE_CNF_LEN    (5*1000)
#define TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN         (15*3600*1000)  /* 15 hours */

#define TI_CNAS_HSD_AVAILABLE_LEN                           (5*1000)

#define TI_CNAS_HSD_AVAILABLE_RATIO                         (1000)

#define TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND_LEN           (200*1000)  /* HSM��180s֮�ڻ�ظ�Э�̽�� */
#define TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND_LEN         (65*1000)

#define TI_CNAS_HSD_WAIT_RRM_STATUS_IND_LEN                 (30*60*1000)

#define TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF_LEN            (120*1000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : CNAS_HSD_TIMER_ID_ENUM
 ö��˵��  : HSD��ʱ����ID
 1.��    ��   : 2014��12��14��
   ��    ��   : h00300378
   �޸�����   : �½�
*****************************************************************************/
enum CNAS_HSD_TIMER_ID_ENUM
{
    TI_CNAS_HSD_WAIT_CARD_FILE_CNF,
    TI_CNAS_HSD_WAIT_HSM_START_CNF,
    TI_CNAS_HSD_WAIT_HLU_START_CNF,
    TI_CNAS_HSD_WAIT_CAS_START_CNF,
    TI_CNAS_HSD_WAIT_HSM_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_HLU_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_CAS_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_CAS_SYSTEM_SYNC_CNF,
    TI_CNAS_HSD_WAIT_CAS_OHM_IND,
    TI_CNAS_HSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF,
    TI_CNAS_HSD_AVAILABLE_TIMER,

    TI_CNAS_HSD_AVAILABLE_MRU0_TIMER,

    TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,

    TI_CNAS_HSD_WAIT_SESSION_NEG_RSLT_IND,
    TI_CNAS_HSD_WAIT_CAS_SUSPEND_CNF,
    TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND,

    TI_CNAS_HSD_WAIT_EHSM_START_CNF,
    TI_CNAS_HSD_WAIT_EHSM_POWEROFF_CNF,
    TI_CNAS_HSD_WAIT_HSM_POWERSAVE_CNF,

    TI_CNAS_HSD_WAIT_RRM_STATUS_IND,

    TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF,

    TI_CNAS_HSD_TIMER_BUTT
};
typedef VOS_UINT32  CNAS_HSD_TIMER_ID_ENUM_UINT32;

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/




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

#endif /* end of CnasHsdTimerMgmt.h */
