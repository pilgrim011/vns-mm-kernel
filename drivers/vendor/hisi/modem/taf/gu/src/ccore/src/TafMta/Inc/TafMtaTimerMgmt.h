/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaTimerMgmt.h
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2012��6��27��
  ����޸�   :
  ��������   : MTAģ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��6��27��
    ��    ��   : Y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ����

******************************************************************************/

#ifndef __TAFMTATIMERMGMT_H__
#define __TAFMTATIMERMGMT_H__

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
/*����ʱ������ת����DOPRA��ʱ������ĺ��룬��Ҫ����1000 */
#define TIMER_S_TO_MS_1000                      (1000)

/* MTA ����CPOS�·�XML�������̱�����ʱ��ʱ�� */
#define TI_TAF_MTA_CPOS_TIMER_LEN               (2 * TIMER_S_TO_MS_1000)

/* MTA��ͣGPS RFʱ�����̱�����ʱ��ʱ�� */
#define TI_TAF_MTA_GPS_TIMER_LEN                (1 * TIMER_S_TO_MS_1000)

/* ^nmr�ȴ������ظ�nmr���ݲ�ѯ���������ʱ��ʱ�� */
#define TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF_TIMER_LEN            (3 * TIMER_S_TO_MS_1000)

#define TAF_MTA_CTX_MAX_TIMER_NUM                           (6)                 /* ����Rf&Lcd���Ź����Ŀ������ʱ����Դ��5������6�� by j00174725 */

#define TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF_TIMER_LEN       (1 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF_TIMER_LEN  (2 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF_TIMER_LEN  (2 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)

/* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
#define TI_TAF_MTA_WAIT_AS_ECID_SET_CNF_TIMER_LEN           (3 * TIMER_S_TO_MS_1000)
/* Added by l00198894 for ����+ECID����, 2013-12-10, end */


#define TAF_MTA_RF_LCD_TIMER_INTERVAL_DEFAULT               (60 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF_TIMER_LEN        (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_DSP_INIT_CNF_TIMER_LEN              (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF_TIMER_LEN        (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_OPTION_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_STATE_CNF_TIMER_LEN        (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_PREFERENCE_CNF_TIMER_LEN           (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_SIB16_NETWORK_TIME_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_BSSI_SIGNAL_LEVEL_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_NETWORK_INFO_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_EMBMS_STATUS_CNF_TIMER_LEN              (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_UNSOLICITED_CFG_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_LOW_POWER_CONSUMPTION_CNF_TIMER_LEN     (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_INTERESTLIST_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_AVL_SERVICE_LIST_CNF_TIMER_LEN     (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_LTE_WIFI_COEX_CNF_TIMER_LEN             (6 * TIMER_S_TO_MS_1000)


#define TI_TAF_MTA_WAIT_SET_FR_CNF_TIMER_LEN                (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND_TIMER_LEN       (1 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF_TIMER_LEN         (2 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF_TIMER_LEN      (2 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF_TIMER_LEN  (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF_TIMER_LEN     (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF_TIMER_LEN  (3 * TIMER_S_TO_MS_1000)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define TI_TAF_MTA_WAIT_UIMID_READ_CNF_LEN                  (5 * TIMER_S_TO_MS_1000)
#endif
#define TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_TIMER_LEN          (20 * TIMER_S_TO_MS_1000)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_MTA_TIMER_ID_ENUM
 ö��˵��  : MTA��ʱ����ID
 1.��    ��   : 2012��6��27��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A-GPS��Ŀ����
 2.��    ��   : 2012��11��21��
   ��    ��   : z00161729
   �޸�����  : ֧��cerssi��nmr
  3.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�
 4.��    ��   : 2013��03��13��
   ��    ��   : z00214637
   �޸�����   : BodySAR��Ŀ
 5.��    ��   : 2013��06��04��
   ��    ��   : s00217060
   �޸�����   : for V9R1_SVLTE

*****************************************************************************/
enum TAF_MTA_TIMER_ID_ENUM
{
    /* CPOS��MTA�ȴ�AT�·�XML����������ʱ�� */
    TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF                 = 0,

    /* GPSʱ��Gģʽ��ͣ������ʱ�� */
    TI_TAF_MTA_WAIT_GPHY_SET_CGPSCLOCK_CNF,

    /* GPSʱ��Wģʽ��ͣ������ʱ�� */
    TI_TAF_MTA_WAIT_WPHY_SET_CGPSCLOCK_CNF,

    TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF,

    TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,

    TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,

    TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,

    TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF,

    TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF,

    TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,
    TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,

    TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,
    TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,

    /* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
    TI_TAF_MTA_WAIT_AS_ECID_SET_CNF,
    /* Added by l00198894 for ����+ECID����, 2013-12-10, end */
    TI_TAF_MTA_WAIT_DSP_INIT_CNF,

    TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT,

    TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,

    TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,

    TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,

    TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,

    TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,
    TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,

    TI_TAF_MTA_WAIT_SET_FR_CNF,

    TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,
    TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF,

    TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF,

    TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF,

    TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF,
    TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF,

    TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF,
    TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF,
    TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF,

    TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF,

    TI_TAF_MTA_WAIT_UIMID_READ_CNF,

    TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF,
    TI_TAF_MTA_TIMER_BUTT
};
typedef VOS_UINT32  TAF_MTA_TIMER_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_MTA_TIMER_STATUS_ENUM
 �ṹ˵��  : MTA��ʱ��״̬,ֹͣ������
 1.��    ��   : 2012��6��27��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A-GPS��Ŀ����
*****************************************************************************/
enum TAF_MTA_TIMER_STATUS_ENUM
{
    TAF_MTA_TIMER_STATUS_STOP                       = 0,    /* ��ʱ��ֹͣ״̬ */
    TAF_MTA_TIMER_STATUS_RUNING,                            /* ��ʱ������״̬ */
    TAF_MTA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MTA_TIMER_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_MTA_TIMER_START_RESULT_ENUM
 �ṹ˵��  : MTA��ʱ�������������ֵ
 1.��    ��   : 2012��6��27��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A-GPS��Ŀ����
*****************************************************************************/
enum TAF_MTA_TIMER_START_RESULT_ENUM
{
    TAF_MTA_TIMER_START_SUCCEE              = 0,            /* ��ʱ�������ɹ� */
    TAF_MTA_TIMER_START_FAILURE,                            /* ��ʱ������ʧ�� */

    TAF_MTA_TIMER_START_BUTT
};
typedef VOS_UINT8 TAF_MTA_TIMER_START_RESULT_ENUM_UINT8;
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
 �ṹ��    : TAF_MTA_TIMER_CXT_STRU
 �ṹ˵��  : MTA��ʱ������������
  1.��    ��   : 2012��6��27��
    ��    ��   : Y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ����
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;             /* ��ʱ��������ָ�� */
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;          /* ��ʱ����ID */
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucReserve[3];      /* ����λ */
} TAF_MTA_TIMER_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_TIMER_INFO_STRU
 �ṹ˵��  : log��MTA��ʱ���������
  1.��    ��   : 2012��6��27��
    ��    ��   : Y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* ��ʱ��״̬ */
    VOS_UINT8                           aucReserve[3];      /* ����λ */
    VOS_UINT32                          ulLen;              /* ��ʱ��ʱ�� */
}TAF_MTA_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_TIMER_PRECISION_STRU
 �ṹ˵��  : ��32K���ȶ�ʱ����Ϣ��
  1.��    ��   : 2015��6��17��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ����
*****************************************************************************/
typedef struct
{
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;          /* TimerID */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;        /* ��ʱ������ */
}TAF_MTA_TIMER_PRECISION_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  10 ��������
*****************************************************************************/
/*lint -e958*/
VOS_VOID  TAF_MTA_SndOmTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus
);
/*lint +e958*/

VOS_VOID  TAF_MTA_InitAllTimers(
    TAF_MTA_TIMER_CTX_STRU              *pstMtaTimerCtx
);

TAF_MTA_TIMER_START_RESULT_ENUM_UINT8  TAF_MTA_StartTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  TAF_MTA_StopTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
);

TAF_MTA_TIMER_STATUS_ENUM_UINT8  TAF_MTA_GetTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
);

/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

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

#endif


