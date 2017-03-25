/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : W00176964
  ��������   : 2013��7��23��
  ����޸�   : 2013��7��23��
  ��������   : ���嶨ʱ������ģ��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��23��
    ��    ��   : W00176964
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  TAF_MMA_TIMER_MGMT_PROC_H
#define  TAF_MMA_TIMER_MGMT_PROC_H

#pragma pack(4)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MMA_MAX_TIMER_NUM                       (30)

/* �ȴ�PB���ļ�ˢ��ָʾ��ʱ�� */
#define TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT_LEN                 (10*1000)


/* �ȴ�MSCC�Ŀ����ظ���ʱ�� */
#define TI_TAF_MMA_WAIT_MSCC_START_CNF_LEN                        (70*1000)

/* �ȴ�MSCC�Ĺػ��ظ���ʱ�� */
#define TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF_LEN                    (61*1000)



/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
#define TI_TAF_MMA_WAIT_MSCC_ACQ_CNF_LEN                          (180*1000)

/* �ȴ�MSCC��REG_CNF��ʱ�� */
#define TI_TAF_MMA_WAIT_MSCC_REG_CNF_LEN                          (1200*1000)

/* �ȴ�MSCC��POWER_SAVE_CNF��ʱ�� */
#define TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF_LEN                   (23*1000)

/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

#define TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF_LEN                      (23*1000)

#define TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF_LEN                  (1*1000)
#define TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF_LEN                (1*1000)

#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF_LEN               (6*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF_LEN             (1*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF_LEN              (1*1000)

/*�յ�PS_USIM_REFRESH_IND ����CSҵ�񣬵ȴ�CSҵ���������*/
#define TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN                   (5*1000)
#define TI_TAF_MMA_WAIT_READ_SIM_FILES_LEN                       (10*1000)


#define TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF_LEN                   (5*1000)
#define TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF_LEN                    (5*1000)
#define TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_SET_CNF_LEN         (320*1000)
#define TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_RESEL_SET_CNF_LEN      (110*1000)
#define TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF_LEN         (5*1000)

#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF_LEN               (6*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF_LEN             (1*1000)
#define TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF_LEN              (1*1000)

#define TI_TAF_MMA_WAIT_MSCC_DETACH_CNF_LEN                       (95 * 1000)
#define TI_TAF_MMA_WAIT_MSCC_SYSCFG_DETACH_CNF_LEN                (44 * 1000)
/* ���� */
#define TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF_LEN                       (150 * 1000)
#define TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF_LEN                       (55 * 1000)

/* 4F36�ļ�Refresh�����ڲ�SYSCFG�������Գ��Զ�ʱ��ʱ�� */
#define TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING_LEN                (5*1000)


#define TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF_LEN                 (6*1000)
#define TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF_LEN                  (6*1000)

#define TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF_LEN             (215*1000)
#define TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF_LEN              (10*1000)

/* ��ȡ�����붨ʱ��Ĭ��ʱ�� */
#define TAF_MMA_GET_GEO_TIMER_DEFAULT_LEN                        (3*1000)

/* �ȴ�ֹͣ��ȡ�����붨ʱ��Ĭ��ʱ�� */
#define TAF_MMA_WAIT_STOP_GET_GEO_CNF_LEN                        (3*1000)



/* ��������Чʱ��Ĭ��ֵ����λΪ�� */
#define TAF_MMA_GEO_EFFECTIVE_TIME_DEFAULT_LEN                   (30*60)



#define TI_TAF_MMA_DEFAULT_FREQUENCE_OF_QRY_CDMA_SYS_INFO_LEN    (5*1000)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_MMA_TIMER_ID_ENUM
 ö��˵��  : MMA��ʱ����ID
 1.��    ��   : 2013��7��23��
   ��    ��   : W00176964
   �޸�����   : �½�

 2.��    ��   : 2014��1��26��
   ��    ��   : S00261364
   �޸�����   : ����L+C��������ʱ��
 3.��    ��   : 2015��9��30��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
enum TAF_MMA_TIMER_ID_ENUM
{
    /* �ȴ�PB���ļ�ˢ��ָʾ��ʱ�� */
    TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT                  = MN_TIMER_CLASS_MMA ,

    /* ɾ����ʱ������ */

    /* �ȴ�MSCC�Ŀ����ظ���ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_START_CNF,

    /* �ȴ�MSCC�Ĺػ��ظ���ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF,

    /* ɾ����ʱ������ */

    /* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
    /* �ȴ�MSCC��MSCC_ACQ_CNF��ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_ACQ_CNF,

    /* �ȴ�MSCC��REG_CNF��ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_REG_CNF,

    /* �ȴ�MSCC��POWER_SAVE_CNF��ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF,
    /* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

    /* �ȴ�mscc srv acq cnfҵ�񴥷����������Ϣ��ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF,

    /* ɾ����ʱ������ */

    /* ɾ����ʱ������ */

    TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF,
    TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF,

    TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF,
    TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF,
    TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF,

    /*�յ�PS_USIM_REFRESH_IND ����CSҵ�񣬵ȴ�CSҵ���������*/
    TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN                 ,
    TI_TAF_MMA_WAIT_READ_SIM_FILES,

    /* �ȴ�MSCC��IMS�����ظ���ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF,

    /* �ȴ�MSCC��IMS�رջظ���ʱ�� */
    TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF,

    TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF,
    TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF,
    TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF,
    TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF,
    TI_TAF_MMA_WAIT_MSCC_DETACH_CNF,
    TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF,
    TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF,

    /* 4F36�ļ�Refresh����SYSCFG�������Գ��Զ�ʱ��*/
    TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING,


    TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF,
    TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF,


    TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF,
    TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF,

    TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS              ,

    TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO,

    TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,
    TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE,

    TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF,
    TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF,

    TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE,                             /* �ӳ��ϱ�CL�޷���ʱ�� */
    TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE,                             /* �ӳ��ϱ�DO�޷���ʱ�� */

    TI_TAF_MMA_TIMER_BUTT
};
typedef VOS_UINT32  TAF_MMA_TIMER_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_MMA_TIMER_STATUS_ENUM
 �ṹ˵��  : MMA��ʱ��״̬,ֹͣ������
  1.��    ��   : 2013��7��23��
    ��    ��   : W00176964
    �޸�����   : �½�
*****************************************************************************/
enum TAF_MMA_TIMER_STATUS_ENUM
{
    TAF_MMA_TIMER_STATUS_STOP,              /* ��ʱ��ֹͣ״̬ */
    TAF_MMA_TIMER_STATUS_RUNING,            /* ��ʱ������״̬ */
    TAF_MMA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MMA_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
  3 �ṹ����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_MMA_TIMER_CXT_STRU
 �ṹ˵��  : MMA��ʱ������������
 1.��    ��   : 2013��7��23��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId;                              /* ��ʱ����ID */
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[3];
} TAF_MMA_TIMER_CTX_STRU;


/*****************************************************************************
 �ṹ��    : TAF_MMA_TIMER_INFO_STRU
 �ṹ˵��  : log��MMA��ʱ���������
 1.��    ��   : 2013��7��23��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_MMA_TIMER_INFO_STRU;

/*****************************************************************************
  4 ��������
*****************************************************************************/
VOS_VOID  TAF_MMA_StartTimer(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  TAF_MMA_StopTimer(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId
);

TAF_MMA_TIMER_STATUS_ENUM_UINT8  TAF_MMA_GetTimerStatus(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId
);

VOS_VOID  TAF_MMA_SndOmTimerStatus(
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enTimerStatus,
    TAF_MMA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
);

extern VOS_UINT32  TAF_MMA_GetPlmnListAbortTimerLen(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* TAF_MMA_TIMER_MGMT_H */


