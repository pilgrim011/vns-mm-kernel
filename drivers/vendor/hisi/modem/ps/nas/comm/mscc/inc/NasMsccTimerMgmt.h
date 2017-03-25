/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMsccTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��01��27��
  ����޸�   :
  ��������   : NasMsccTimerMgmt.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NAS_MSCC_TIMER_MGMT_H__
#define __NAS_MSCC_TIMER_MGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_THOUSAND_MILLISECOND_UNIT                   (1000)                         /* 1000MS */

#define TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN        (35*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_IMSA_START_CNF_LEN                  (3*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_START_CNF_LEN                   (70*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_XSD_START_CNF_LEN                   (35*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_START_CNF_LEN                   (35*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF_LEN              (3*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF_LEN               (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF_LEN               (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF_LEN               (60*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/*BSR Retry Timer length*/
#define TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF_LEN                 (335*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN              (22*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF_LEN              (7*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF_LEN               (11*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF_LEN             (335*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN              (11*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND_LEN               (145*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_AVAILABLE_TIMER_COUNT_FIRST_SEARCH       (10)

#define TI_NAS_MSCC_AVAILABLE_TIMER_FIRST_SEARCH_LEN         (300*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_AVAILABLE_TIMER_DEEP_SEARCH_LEN          (2400*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* �޸�Ĭ�ϵ�DO<->LTE֮���BSRʱ�� */
#define TI_NAS_MSCC_BSR_TIMER_LEN                            (180*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* δƥ��MSPL��¼ʱBSR��ʱ����defaultʱ�� */
#define TI_NAS_MSCC_DEFAULT_BSR_TIMER_LEN_WITH_UNMATCHED_MSPL_REC    (180*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)


#define TI_NAS_MSCC_BSR_RETRY_TIMER_LEN                      (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_SCAN_TIMER_LEN                           (600*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_SLEEP_TIMER_LEN                          (180*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_CARD_READ_CNF_LEN                   (5*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF_LEN               (101*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF_LEN       (6*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF_LEN          (11*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF_LEN               (181*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF_LEN          (7*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF_LEN      (1*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF_LEN                 (5*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF_LEN                 (5*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF_LEN                 (52*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_RESELCT_LEN: 35s */
/* MSCC_WAIT_CL_INTERSYS_END_IND_L2C_RESEL_LEN: 35+2 = 37s (mscc��L2C��ѡ�����Ķ�ʱ��ʱ���Դ���mmc��L2C��ѡ�����Ķ�ʱ��ʱ��,�ݶ�Ϊ��2s) */
#define TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_L2C_RESEL_LEN    (37*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_REDIR_LEN: 180s */
/* MSCC_WAIT_CL_INTERSYS_END_IND_L2C_REDIR_LEN: 180+2=182s (mscc��L2C�ض�������Ķ�ʱ��ʱ���Դ���mmc��L2C�ض�������Ķ�ʱ��ʱ��,�ݶ�Ϊ��2s) */
#define TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_L2C_REDIR_LEN    (182*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* HSD_WAIT_CAS_IRAT_OR_RESUME_IND_LEN: 65s */
/* MSCC_WAIT_CL_INTERSYS_END_IND_C2L_RESEL_LEN=65+2=67s (mscc��C2L��ѡ�����Ķ�ʱ��ʱ���Դ���hsd��C2L��ѡ�����Ķ�ʱ��ʱ��,�ݶ�Ϊ��2s) */
#define TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_C2L_RESEL_LEN    (67*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/*
   MMC_WAIT_SUSPEND_REL_CNF_LEN: 8s
   MMC_WAIT_SUSPEND_CNF_LEN    :10s
   MSCC_WAIT_CL_INTERSYS_MMC_POWERSAVE_CNF_LEN = 8+10+2=20s (mscc��mmc��ϵͳ power save �ظ���ʱ���Դ���mmc���ͷŹ���ظ�ʱ�����ϵȹ���ظ�ʱ��(8+10),�ݶ�Ϊ��2s
*/
#define TI_NAS_MSCC_WAIT_CL_INTERSYS_MMC_POWERSAVE_CNF_LEN    (20*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define NAS_MSCC_TIMER_TICK                                   (10)

/* 1x�з���ʱavailable��ʱ���׶�1����ʱ��,��λ�� */
#define TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_TOTAL_TIMER_LEN    (650)

/* 1x�з���ʱavailable��ʱ���׶�1��Ĭ��sleepʱ��,��λ�� */
#define TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_SLEEP_TIMER_LEN    (5)

/* 1x�з���ʱ�ӽ׶�1�����׶�2�Ĺ���ʱ�� */
#define TI_NAS_MSCC_DEFAULT_AVAILABLE_TIMER_SKIP_LEN    (500)

/* 1x�з���ʱ�׶�1ʱȫƵ���������� */
#define NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_ONE_FULL_BAND_SRCH_NUM    (10)

/* 1x�з���ʱ�׶�1ʱ��ʷƵ���������� */
#define NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_ONE_HISTORY_SRCH_NUM    (5)

/* 1x�з���ʱavailable��ʱ���׶�2��Ĭ��sleepʱ��,��λ�� */
#define TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_TWO_SLEEP_TIMER_LEN    (20)

/* 1x�з���ʱ�׶�2ʱ��ʷƵ���������� */
#define NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_TWO_HISTORY_SRCH_NUM    (1)

/* 1x�з���ʱ�׶�2ʱȫƵ���������� */
#define NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_TWO_FULL_BAND_SRCH_NUM    (1)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_MSCC_TIMER_ID_ENUM
 ö��˵��  : MSCC��ʱ����ID
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �½�

*****************************************************************************/
enum NAS_MSCC_TIMER_ID_ENUM
{
    /* Timer for start confirmation from IMSA */
    TI_NAS_MSCC_WAIT_IMSA_START_CNF,
    /* Timer for power off confirmation from IMSA */
    TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF,
    /* Timer for start confirmation from XSD */
    TI_NAS_MSCC_WAIT_XSD_START_CNF,
    /* Timer for power off confirmation from XSD */
    TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF,
    /* Timer for start confirmation from HSD */
    TI_NAS_MSCC_WAIT_HSD_START_CNF,
    /* Timer for power off confirmation from HSD */
    TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF,
    /* Timer for start confirmation from MMC */
    TI_NAS_MSCC_WAIT_MMC_START_CNF,
    /* Timer for power off confirmation from MMC */
    TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF,
    /* �ȴ�IMSA��IMS VOICE CAP��Ϣ�ı�����ʱ�� */
    TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY,

    TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF,

    TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF,

    TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF,

    /* Timer for BSR timer */
    TI_NAS_MSCC_BSR_TIMER,
    /* Timer for BSR period trying high pri SYSTEM*/
    TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
    TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
    TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
    TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND,
    TI_NAS_MSCC_SCAN_TIMER,
    TI_NAS_MSCC_SLEEP_TIMER,
    TI_NAS_MSCC_AVAILABLE_TIMER,

    TI_NAS_MSCC_WAIT_CARD_READ_CNF,

    TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF,
    TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF,
    TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF,

    TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF,
    /* Timer for System config confirmation from HSD */
    TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF,
    /* Timer for System config confirmation from MMC */
    TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF,

    TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND,

    TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER,     /* 1x�з���ʱCLϵͳ�����һ�׶�������ʱ�� */

    TI_NAS_MSCC_TIMER_BUTT
};
typedef VOS_UINT32  NAS_MSCC_TIMER_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MSCC_TIMER_STATUS_ENUM
 �ṹ˵��  : MSCC��ʱ��״̬,ֹͣ������
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_TIMER_STATUS_ENUM
{
    NAS_MSCC_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    NAS_MSCC_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    NAS_MSCC_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_TIMER_STATUS_ENUM_UINT8;

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
 �ṹ��    : NAS_MSCC_TIMER_CTX_STRU
 �ṹ˵��  : MSCC��ʱ������������
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId;                              /* ��ʱ����ID */
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[3];
}NAS_MSCC_TIMER_CTX_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_TIMER_INFO_STRU
 �ṹ˵��  : log��MSCC��ʱ���������
 1.��    ��   : 2015��1��27��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ*/ /*_H2ASN_Skip*/
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;                                  /* ��ʱ��ʱ�� */
}NAS_MSCC_TIMER_INFO_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  NAS_MSCC_SndOmTimerStatus(
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus,
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
);

VOS_UINT32  NAS_MSCC_StartTimer(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
);


VOS_VOID  NAS_MSCC_StopTimer(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId
);

NAS_MSCC_TIMER_STATUS_ENUM_UINT8  NAS_MSCC_GetTimerStatus(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId
);

VOS_VOID NAS_MSCC_StopAllTimer(VOS_VOID);

VOS_VOID NAS_MSCC_GetRemainTimerLen(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                         *pulRemainTimeLen
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

#endif /* end of NasMsccTimerMgmt.h */
