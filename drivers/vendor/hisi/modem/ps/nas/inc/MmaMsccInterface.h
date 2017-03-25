/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MmaMsccInterface.h
  �� �� ��   : ����
  ��    ��   : z00161729
  ��������   : 2013��3��25��
  ����޸�   :
  ��������   : mma��mscc��Ϣ������ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��25��
    ��    ��   : z00161729
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _MMA_MSCC_INTERFACE_H_
#define _MMA_MSCC_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafAppMma.h"
#include "NasMsccPifInterface.h"
#include "TafMmaInterface.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MSCC_MMA_SECOND_COLORCODE_MAX_LENGTH                ( 5 )
#define MSCC_MMA_SUBNET_ID_MAX_LENGTH                       ( 16 )

#define     MSCC_MMA_CAS_STA_INVALID_SUBSTA                 (0xFF)

#define     MSCC_MMA_MAX_SRCHED_LAI_NUM  (18)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



enum MSCC_MMA_HRPD_SERVICE_STATUS_ENUM
{
    MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE         = 0,              /* HRPD is in normal service */
    MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE             = 1,              /* HRPD has no service */
    MSCC_MMA_HRPD_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32;


enum MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM
{
    MSCC_MMA_HRPD_ACQUIRED_RESULT_SUCC        = 0x00000000,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_FAIL        = 0x00000001,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_ABORTED     = 0x00000002,
    MSCC_MMA_HRPD_ACQUIRED_RESULT_BUTT
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM_UINT32;


enum MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM
{
    MSCC_MMA_SESSION_RELEASE_TYPE_0     = 0x00,
    MSCC_MMA_SESSION_RELEASE_TYPE_A     = 0x01,
    MSCC_MMA_SESSION_RELEASE_TYPE_BUTT  = 0x02
};
typedef VOS_UINT32 MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MSCC_MMA_ACQ_SYS_TYPE_ENUM
 ö��˵��  : ϵͳ���������
 1.��    ��   : 2015��2��10��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum MSCC_MMA_ACQ_SYS_TYPE_ENUM
{
    MSCC_MMA_ACQ_SYS_TYPE_3GPP,                                             /* GULģʽ��3GPP�µ�������ʼ�����ָʾ��ϵͳ����(����LTE ONLY)*/
    MSCC_MMA_ACQ_SYS_TYPE_1X,                                               /* 1X�Ĳ���ʼ�����ָʾ��ϵͳ���� */
    MSCC_MMA_ACQ_SYS_TYPE_DO,                                               /* CLģʽ���Ҳ�֧��LTEʱ,DO�Ĳ���ʼ�����ָʾ��ϵͳ���� */
    MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,                                           /* CLģʽ��֧��LTEʱ,DO��LTE����ʼ�����ָʾ��ϵͳ���� */
    MSCC_MMA_ACQ_SYS_TYPE_BUTT
};
typedef VOS_UINT32 MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMA_MSCC_HANDSET_INFO_TYPE_ENUM
 ö��˵��  : ��ѯ���ֻ���Ϣ����
 1.��    ��   : 2015��5��18��
   ��    ��   : z00316370
   �޸�����   : �½�
*****************************************************************************/
enum MMA_MSCC_HANDSET_INFO_TYPE_ENUM
{
    MMA_MSCC_HANDSET_INFO_TYPE_STATE,
    MMA_MSCC_HANDSET_INFO_TYPE_HVERSION,

    MMA_MSCC_HANDSET_INFO_TYPE_BUTT
};
typedef VOS_UINT32 MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_P_REV_ENUM
{
    MSCC_MMA_1X_CAS_P_REV_JST_008               = 0x01,
    MSCC_MMA_1X_CAS_P_REV_IS_95                 = 0x02,
    MSCC_MMA_1X_CAS_P_REV_IS_95A                = 0x03,
    MSCC_MMA_1X_CAS_P_REV_IS_95B_CUSTOM         = 0x04,
    MSCC_MMA_1X_CAS_P_REV_IS_95B                = 0x05,
    MSCC_MMA_1X_CAS_P_REV_IS_2000               = 0x06,
    MSCC_MMA_1X_CAS_P_REV_IS_2000A              = 0x07,

    MSCC_MMA_1X_CAS_P_REV_ENUM_BUTT
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_STATE_ENUM_UINT8
 *
 * Description : When MS is in the different state, MS should perform
 * different actions.
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_STATE_ENUM
{
    MSCC_MMA_1X_CAS_INIT_STATE          = 0x00,
    MSCC_MMA_1X_CAS_IDLE_STATE          = 0x01,
    MSCC_MMA_1X_CAS_ACCESS_STATE        = 0x02,
    MSCC_MMA_1X_CAS_TCH_STATE           = 0x03,
    MSCC_MMA_1X_CAS_NO_SERVICE_STATE    = 0x04,
    MSCC_MMA_1X_CAS_STATE_ENUM_BUTT     = 0x05
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : MSCC_MMA_1X_CAS_SUB_STATE_ENUM_UINT8
 *
 * Description : .
 * Refers to  C.S0017 2.6.5.5
 *******************************************************************************/
enum MSCC_MMA_1X_CAS_SUB_STATE_ENUM
{
    MSCC_MMA_1X_CAS_SUB_STATE_NULL                          = 0x00,
    MSCC_MMA_1X_CAS_INIT_DETERM_SUB_STATE                   = 0x01,
    MSCC_MMA_1X_CAS_PILOT_CH_ACQ_SUB_STATE                  = 0x02,
    MSCC_MMA_1X_CAS_SYNC_CH_ACQ_SUB_STATE                   = 0x03,
    MSCC_MMA_1X_CAS_TIMING_CHNG_SUB_STATE                   = 0x04,
    MSCC_MMA_1X_CAS_IDLE_SUB_STATE                          = 0x10,
    MSCC_MMA_1X_CAS_UPDATE_OVERHEAD_SUB_STATE               = 0x20,
    MSCC_MMA_1X_CAS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE      = 0x21,
    MSCC_MMA_1X_CAS_PAG_RESP_SUB_STATE                      = 0x22,
    MSCC_MMA_1X_CAS_MOB_STATION_ORDR_RESP_SUB_STATE         = 0x23,
    MSCC_MMA_1X_CAS_REG_ACCESS_SUB_STATE                    = 0x24,
    MSCC_MMA_1X_CAS_MOB_STATION_MSG_TRANS_SUB_STATE         = 0x25,
    MSCC_MMA_1X_CAS_TCH_INIT_SUB_STATE                      = 0x30,
    MSCC_MMA_1X_CAS_REL_SUB_STATE                           = 0x31,
    MSCC_MMA_1X_CAS_WAIT_FOR_SERVICE_SUB_STATE              = 0x40,
    MSCC_MMA_1X_CAS_SUB_STATE_ENUM_BUTT                     = 0x41
};
typedef VOS_UINT8 MSCC_MMA_1X_CAS_SUB_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : MSCC_MMA_1X_CALL_STATE_ENUM
 �ṹ˵��  : 1X����״̬

 1.��    ��   : 2015��05��22��
   ��    ��   : z00316370
   �޸�����   : ����
*****************************************************************************/
enum MSCC_MMA_1X_CALL_STATE_ENUM
{
    MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ORDER,
    MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ANSWER,
    MSCC_MMA_1X_CALL_STATE_CONVERSATION,

    MSCC_MMA_1X_CALL_STATE_BUTT
};
typedef VOS_UINT8 MSCC_MMA_1X_CALL_STATE_ENUM_UINT8;





/*****************************************************************************
 ö����    :  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32
 ö��˵��  : CLϵͳ������������
 1.��    ��   : 2015��6��12��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
enum  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM
{
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_DO_SUCC,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_LTE_SUCC,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT
};
typedef VOS_UINT32  MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32;



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
 �ṹ��    : MMA_MSCC_PLMN_RAT_PRIO_STRU
 �ṹ˵��  : ��ǰ֧�ֽ��뼼���ͽ��뼼�����ȼ������ݽṹ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
 2.��    ��   : 2015��5��122��
   ��    ��   : W00176964
   �޸�����   : CDMA Iteration 10 modified
*****************************************************************************/
typedef  NAS_MSCC_PIF_RAT_PRIO_STRU MMA_MSCC_PLMN_RAT_PRIO_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PLMN_ID_STRU
 �ṹ˵��  : plmn id�����ݽṹ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
typedef  NAS_MSCC_PIF_PLMN_ID_STRU MMA_MSCC_PLMN_ID_STRU;

/* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
/*****************************************************************************
 �ṹ��    : MMA_MSCC_3GPP2_RAT_STRU
 �ṹ˵��  : MS 3GPP2�Ľ��뼼������
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_3GPP2_RAT_STRU MMA_MSCC_3GPP2_RAT_STRU;
/* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */

/*****************************************************************************
 �ṹ��    : MMA_MSCC_EPLMN_INFO_STRU
 �ṹ˵��  : MML��ǰEQUPLMN��Ϣ
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
typedef NAS_MSCC_PIF_EPLMN_INFO_STRU MMA_MSCC_EPLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_CAMP_CELL_INFO_STRU
 �ṹ˵��  : ��ǰפ��С������Ϣ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CAMP_CELL_INFO_STRU MMA_MSCC_CAMP_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_OPERATOR_NAME_INFO_STRU
 �ṹ˵��  : plmn id����Ӫ�̳�������Ϣ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
typedef NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU MMA_MSCC_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_UE_SUPPORT_FREQ_BAND_STRU
 �ṹ˵��  : ue ֧��band����
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
typedef NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU MMA_MSCC_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_RSSI_VALUE_STRU
 �ṹ˵��  : rssiֵ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
typedef NAS_MSCC_PIF_RSSI_VALUE_STRU MMA_MSCC_RSSI_VALUE_STRU;

/*******************************************************************************
 �ṹ��    :MMA_MSCC_SCELL_MEAS_TYPE_STRU
 �ṹ˵��  : union MMA_MSCC_SCELL_MEAS_TYPE_STRU��ԱstMeasReportType����
             bitλ��1��ʾ��������Ч
1.��    �� : 2014��6��5��
  ��    �� : b00269685
  �޸����� : �½�
*******************************************************************************/
typedef NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU MMA_MSCC_SCELL_MEAS_TYPE_STRU;

/*****************************************************************************
 ö����    : MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN
 �ṹ˵��  : MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN unMeasType�ϱ�����������
1. ��    ��: 2014��6��5��
   ��    ��: b00269685
   �޸�����: �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN MMA_MSCC_SCELL_MEAS_REPORT_TYPE_UN;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_RSSI_INFO_STRU
 �ṹ˵��  : rssi��Ϣ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
 2.��    ��: 2014��6��4��
   ��    ��: b00269685
   �޸�����: �����ϱ�����
*****************************************************************************/
typedef NAS_MSCC_PIF_RSSI_IND_STRU MSCC_MMA_RSSI_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CQI_INFO_STRU
 �ṹ˵��  : LTE�µ��ŵ�����,�������ֱַ�����Ӵ�CQI�Ϳ��CQI
 1.��    ��: 2014��11��28��
   ��    ��: w00281933
   �޸�����: ����
*****************************************************************************/
typedef NAS_MSCC_PIF_CQI_INFO_STRU MSCC_MMA_CQI_INFO_STRU;
/*****************************************************************************
 �ṹ��    : MMA_MSCC_LMM_CELL_SIGN_INFO_STRU
 �ṹ˵��  : LTE�µ��ŵ�����,����LTE�µ�Rssi��Rsrp��Rsrq,SINR,CQI
 1.��    ��: 2014��11��28��
   ��    ��: w00281933
   �޸�����: ����
*****************************************************************************/
typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU MMA_MSCC_LMM_CELL_SIGN_INFO_STRU;
/*****************************************************************************
 �ṹ��    : MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU
 �ṹ˵��  : ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND��Ӧ�Ľṹ��
 1.��    ��: 2014��11��28��
   ��    ��: w00281933
   �޸�����: ����
*****************************************************************************/
typedef NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_START_REQ_STRU
 �ṹ˵��  : mma��mscc���Ϳ����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��2��8��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
 3.��    ��   : 2015��5��122��
   ��    ��   : W00176964
   �޸�����   : CDMA Iteration 10 modified
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus;
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8              enRegDomain;        /* ��ԭ�ӿ�������������ע��ķ����� */
    NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8                     enRegCtrl;
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stRatPrio;
    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];
    NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8                       enCallMode;
    VOS_UINT8                                               ucIsCardChanged;    /* ����ICCID�Ƿ����仯�ı�ʶ */
    VOS_UINT8                                               aucReserved[1];
}MMA_MSCC_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_START_CNF_STRU
 �ṹ˵��  : mscc��mma���Ϳ����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_START_CNF_STRU MSCC_MMA_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_3GPP_SYS_INFO_IND_STRU
 �ṹ˵��  : mscc��mma����ϵͳ��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
 3.��    ��   : 2013��10��16��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseII ��Ŀ:����������Ϣ����
 4.��    ��   : 2014��01��17��
   ��    ��   : l00198894
   �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
 5.��    ��   : 2014��2��20��
   ��    ��   : z00161729
   �޸�����   : DTS2014022100125:����פ��g�����磬��˫����tl����������פ��g�����磬
               available��ʱ��list�������������б��last rplmn rat������ǰ�浼��g���ڵ�һ��
               �޷���l��tds������
 6.��    ��   : 2014��2��8��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���

*****************************************************************************/
typedef NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU MSCC_MMA_3GPP_SYS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_REG_RESULT_IND_STRU
 �ṹ˵��  : mscc��mma���;ܾ�ԭ��ֵ��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��8��15��
   ��    ��   : l00208543
   �޸�����   : �½�
 2.��    ��   : 2013��12��13��
   ��    ��   : w00176964
   �޸�����   : Volte_PhaseIII ��Ŀ:�޸Ľṹ��
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_RESULT_IND_STRU MSCC_MMA_REG_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_USIM_AUTH_FAIL_IND_STRU
 �ṹ˵��  : mscc��mma����USIM��Ȩʧ��ԭ��ֵ��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��11��15��
   ��    ��   : m00217266
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU MSCC_MMA_USIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SERVICE_STATUS_IND_STRU
 �ṹ˵��  : mscc��mma����ע��״̬�ͷ���״̬����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2013��11��20��
   ��    ��   : w00176964
   �޸�����   : Volte PhaseII��Ŀ�޸�:����CSPS��SIM��״̬
*****************************************************************************/
typedef NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU MSCC_MMA_SERVICE_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_MM_INFO_IND_STRU
 �ṹ˵��  : mscc��mma����MM INFORMATION����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_MM_INFO_IND_STRU MSCC_MMA_MM_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_SIGN_REPORT_REQ_STRU
 �ṹ˵��  : mma��mscc�����ź��ϱ����õ���Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU MMA_MSCC_SIGN_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_MODE_CHANGE_REQ_STRU
 �ṹ˵��  : mma��mscc����ģʽ�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU MMA_MSCC_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_ATTACH_REQ_STRU
 �ṹ˵��  : mma��mscc����attach �������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��2��8��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
typedef NAS_MSCC_PIF_ATTACH_REQ_STRU MMA_MSCC_ATTACH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_ATTACH_CNF_STRU
 �ṹ˵��  : mscc��mma����attach �������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_ATTACH_CNF_STRU MSCC_MMA_ATTACH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_DETACH_REQ_STRU
 �ṹ˵��  : mma��mscc����detach�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��2��8��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_REQ_STRU MMA_MSCC_DETACH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_DETACH_CNF_STRU
 �ṹ˵��  : mscc��mma����detach�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_CNF_STRU MSCC_MMA_DETACH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_DETACH_IND_STRU
 �ṹ˵��  : mscc��mma��������detach�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��4��1��
   ��    ��   : z00161729
   �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
*****************************************************************************/
typedef NAS_MSCC_PIF_DETACH_IND_STRU MSCC_MMA_DETACH_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PLMN_LIST_REQ_STRU
 �ṹ˵��  : mma��mscc����list�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_REQ_STRU MMA_MSCC_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PLMN_LIST_CNF_STRU
 �ṹ˵��  : mscc��mma����list�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_CNF_STRU MSCC_MMA_PLMN_LIST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PLMN_LIST_REJ_STRU
 �ṹ˵��  : mscc��mma����list�����������reject����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_REJ_STRU MSCC_MMA_PLMN_LIST_REJ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU
 �ṹ˵��  : mma��mscc����list������ֹ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PLMN_USER_RESEL_REQ_STRU
 �ṹ˵��  : mma��mscc�����û���ѡ�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU MMA_MSCC_PLMN_USER_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PLMN_SPECIAL_REQ_STRU
 �ṹ˵��  : mma��mscc�����û�ָ�������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU MMA_MSCC_PLMN_SPECIAL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : MSCC_MMA_COVERAGE_AREA_IND_STRU
 �ṹ˵��  : mscc��mma���ͽ������������뿪������ָʾ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU MSCC_MMA_COVERAGE_AREA_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_POWER_OFF_REQ_STRU
 �ṹ˵��  : mma��mscc���͹ػ��������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_OFF_REQ_STRU MMA_MSCC_POWER_OFF_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_POWER_OFF_CNF_STRU
 �ṹ˵��  : mscc��mma���͹ػ��ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_OFF_CNF_STRU MSCC_MMA_POWER_OFF_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU
 �ṹ˵��  : mscc��mma����srched plmn����Ϣ�ṹ
 1.��    ��   : 2015��9��1��
   ��    ��   : h00285180
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU;


typedef NAS_MSCC_PIF_SYSTEM_ACQUIRE_CNF_STRU MSCC_MMA_SYSTEM_ACQUIRE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU
 �ṹ˵��  : mscc��mma�����û�ָ�������ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PLMN_RESEL_CNF_STRU
 �ṹ˵��  : mscc��mma����at+cops=0�ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU MSCC_MMA_PLMN_RESEL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_DATATRAN_ATTRI_IND_STRU
 �ṹ˵��  : mscc��mma����pdp�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU MSCC_MMA_DATATRAN_ATTRI_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_SYS_CFG_SET_REQ_STRU
 �ṹ˵��  : mma��mscc����syscfg�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU MMA_MSCC_SYS_CFG_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SYS_CFG_SET_CNF_STRU
 �ṹ˵��  : mscc��mma����syscfg���ý������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU MSCC_MMA_SYS_CFG_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PLMN_SEARCH_REQ_STRU
 �ṹ˵��  : mma��mscc���������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MMA_MSCC_PLMN_SEARCH_REQ_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU
 �ṹ˵��  : mmc��mma���������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
}MSCC_MMA_SYSTEM_ACQUIRE_IND_STRU;


/*****************************************************************************
 �ṹ��    : MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU
 �ṹ˵��  : mmc��mma���������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32      enAcqRsltType;    /* ָʾϵͳ����ΪDO_LTEʱϵͳ����ʱ,������������ʧ��,HRPD�ɹ�����LTE�ɹ� */
}MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU;




/*****************************************************************************
 �ṹ��    : MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU
 �ṹ˵��  : mscc��mma����list������ֹ�ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU
 �ṹ˵��  : mma��mscc����ָ��������ֹ�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU
 �ṹ˵��  : mscc��mma������ָֹ�������ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU
 �ṹ˵��  : mscc��mma�ϱ�W��cipher��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU
 �ṹ˵��  : mscc��mma�ϱ�G��cipher��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU
 �ṹ˵��  : mscc��MMA�����û�ָ���Ѿܾ��������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_AC_INFO_CHANGE_IND_STRU
 �ṹ˵��  : MSCC��MMA����С��������Ϣ�仯ָʾ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU MSCC_MMA_AC_INFO_CHANGE_IND_STRU;

/*******************************************************************************
 �ṹ��    : MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU
 �ṹ˵��  : MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU��Ϣ�ṹ
 1.��    ��  : 2013��04��16��
   ��    ��  : z00161729
   �޸�����  : �����ṹ
*******************************************************************************/
typedef NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_UPDATE_UPLMN_NTF_STRU
 �ṹ˵��  : mma��mscc����UPLMN����֪ͨ����Ϣ�ṹ
 1.��    ��   : 2013��7��31��
   ��    ��   : w00167002
   �޸�����   : �½��ṹ��
*****************************************************************************/
typedef NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU MMA_MSCC_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_EOPLMN_SET_REQ_STRU
 �ṹ˵��  : AT��MMA��EOPLMN���ýӿ�
 1.��    ��  : 2013��10��15��
   ��    ��  : s00190137
   �޸�����  : �����ṹ
 2.��    ��  : 2013��11��26��
   ��    ��  : s00190137
   �޸�����  : ��ӷ�����ƣ����������������50��OPLMN
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU MMA_MSCC_EOPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_EOPLMN_SET_CNF_STRU
 �ṹ˵��  : mscc��mma����AT^EOPLMN���ûظ�����Ϣ�ṹ
 1.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU MSCC_MMA_EOPLMN_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_EOPLMN_SET_ABORT_STRU
 �ṹ˵��  : AT^EOPLMN���ó�ʱ֪ͨMSCC�ж���Ϣ����Ľṹ
 1.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU MSCC_MMA_EOPLMN_SET_ABORT_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_NET_SCAN_REQ_STRU
 �ṹ˵��  : MMA��MSCC��NETSCAN���ýӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_REQ_STRU MMA_MSCC_NET_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_NET_SCAN_INFO_STRU
 �ṹ˵��  : ɨ��ĳ��Ƶ���������Ϣ
 1.��    ��   : 2013��8��24��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_INFO_STRU MSCC_MMA_NET_SCAN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_NET_SCAN_CNF_STRU
 �ṹ˵��  : MSCC�ϱ���MMA��NETSCAN CNF�ӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef NAS_MSCC_PIF_NET_SCAN_CNF_STRU MSCC_MMA_NET_SCAN_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SERV_REJ_IND_STRU
 �ṹ˵��  : mscc��mma���ͷ��񱻾ܵ���Ϣ�ṹ
 1.��    ��   : 2014��4��1��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SERV_REJ_IND_STRU MSCC_MMA_SERV_REJ_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_ABORT_NET_SCAN_REQ_STRU
 �ṹ˵��  : MMA��MSCC��NETSCAN���ýӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU MMA_MSCC_ABORT_NET_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_ABORT_NET_SCAN_CNF_STRU
 �ṹ˵��  : MSCC�ϱ���MMA��NETSCAN CNF�ӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU MSCC_MMA_ABORT_NET_SCAN_CNF_STRU;

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-9, begin */
/*******************************************************************************
 �ṹ��    : MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU
 �ṹ˵��  : ֪ͨ����ҵ����Ϣ������Ϣ
 1.��    ��  : 2013��7��9��
   ��    ��  : y00245242
   �޸�����  : �����ṹ
*******************************************************************************/
typedef NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU;
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-9, end */

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
/*****************************************************************************
 �ṹ��    : MSCC_MMA_CAMP_ON_IND_STRU
 �ṹ˵��  : MSCC����MMA��פ����Ϣ�ṹ
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �½��ṹ��
*****************************************************************************/
typedef NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU MSCC_MMA_CAMP_ON_IND_STRU_STRU;
/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

/*****************************************************************************
 �ṹ��    : MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU
 �ṹ˵��  : modem1����ϢĿǰֻ��פ����Ϣ
 1.��    ��   : 2013��11��23��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
typedef NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU
 �ṹ˵��  : modem1��dplmn/nplmn��Ϣ
 1.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�

*****************************************************************************/
typedef NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;

/*******************************************************************************
 �ṹ��    : MMA_MSCC_TDS_NCELL_INFO_STRU
 �ṹ˵��  : GSM�µ�TDSƵ���б�

 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*******************************************************************************/
typedef NAS_MSCC_PIF_TDS_NCELL_INFO_STRU MMA_MSCC_TDS_NCELL_INFO_STRU;

/*******************************************************************************
 �ṹ��    : MMA_MSCC_LTE_NCELL_INFO_STRU
 �ṹ˵��  : GSM�µ�LTEƵ���б�

 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*******************************************************************************/
typedef NAS_MSCC_PIF_LTE_NCELL_INFO_STRU MMA_MSCC_LTE_NCELL_INFO_STRU;

/*******************************************************************************
 �ṹ��    : MMA_MSCC_NCELL_INFO_NOTIFY_STRU
 �ṹ˵��  : ID_MMA_MSCC_NCELL_INFO_NOTIFY��Ϣ��Ӧ�Ľṹ��
             ����GSM�µ�TDS/LTE�����ṹ�е�TDS/LTE��Ƶ���б�

 1.��    ��   : 2013��12��23��
   ��    ��   : z00161729
   �޸�����   : �����ɽṹ

*******************************************************************************/
typedef NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU MMA_MSCC_NCELL_INFO_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_EPLMN_INFO_IND_STRU
 �ṹ˵��  : ��Чplmn��Ϣ
 1.��    ��   : 2013��12��23��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_EPLMN_INFO_IND_STRU MSCC_MMA_EPLMN_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU
 �ṹ˵��  : mscc�ϱ�csҵ����������״ָ̬ʾ��Ϣ�ṹ
 1.��    ��   : 2014��3��4��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU;

/*******************************************************************************
�ṹ��    : MMA_MSCC_PS_TRANSFER_NOTIFY_STRU
�ṹ˵��  : ID_MMA_MSCC_PS_TRANSFER_NOTIFY��Ϣ�ṹ
1.��    ��   : 2014��1��5��
  ��    ��   : z00161729
  �޸�����   : �½�
2.��    ��   : 2014��01��17��
  ��    ��   : l00198894
  �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*******************************************************************************/
typedef NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU MMA_MSCC_PS_TRANSFER_NOTIFY_STRU;

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, begin */
/*****************************************************************************
 �ṹ��    : MMA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU
 �ṹ˵��  : MMA֪ͨMSCC��ǰIMS VOICE�Ƿ���õ���Ϣ
 1.��    ��   : 2013��12��10��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MMA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU;
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, end */

/* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
/*****************************************************************************
 �ṹ��    : MMA_MSCC_ACQ_REQ_STRU
 �ṹ˵��  : ��ȡ��Ϣ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_ACQ_REQ_STRU MMA_MSCC_ACQ_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_ACQ_CNF_STRU
 �ṹ˵��  : ��ȡ����Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_ACQ_CNF_STRU MSCC_MMA_ACQ_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_REG_CELL_INFO_STRU
 �ṹ˵��  : ע����Ϣ��Cell Info�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_CELL_INFO_STRU MMA_MSCC_REG_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_REG_REQ_STRU
 �ṹ˵��  : ע����Ϣ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_REQ_STRU MMA_MSCC_REG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_REG_CNF_STRU
 �ṹ˵��  : ע�����Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_REG_CNF_STRU MSCC_MMA_REG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_POWER_SAVE_REQ_STRU
 �ṹ˵��  : Power save��Ϣ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_SAVE_REQ_STRU MMA_MSCC_POWER_SAVE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_POWER_SAVE_CNF_STRU
 �ṹ˵��  : Power save����Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_POWER_SAVE_CNF_STRU MSCC_MMA_POWER_SAVE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_ACQ_IND_STRU
 �ṹ˵��  : ��ȡָʾ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef  NAS_MSCC_PIF_ACQ_CNF_STRU MSCC_MMA_ACQ_IND_STRU;
/* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */

/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
/*****************************************************************************
 �ṹ��    : MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU
 �ṹ˵��  : mscc�ϱ�psҵ����������״ָ̬ʾ��Ϣ�ṹ
 1.��    ��   : 2014��6��27��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef  NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU;
/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, end */

/*****************************************************************************
 �ṹ��    : MSCC_MMA_RF_AVAILABLE_IND_STRU
 �ṹ˵��  : MSCC֪ͨMMA��ǰ�Ƿ���RF��Դ����
 1.��    ��   : 2014��6��30��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU MSCC_MMA_RF_AVAILABLE_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_SRV_ACQ_REQ_STRU
 �ṹ˵��  : ҵ�񴥷�����ָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SRV_ACQ_REQ_STRU MMA_MSCC_SRV_ACQ_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SRV_ACQ_CNF_STRU
 �ṹ˵��  : ҵ�񴥷��������
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SRV_ACQ_CNF_STRU MSCC_MMA_SRV_ACQ_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU
 �ṹ˵��  : ҵ�񴥷�������ʼָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_END_SESSION_NOTIFY_STRU
 �ṹ˵��  : ҵ�񴥷���������ָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU MMA_MSCC_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU
 �ṹ˵��  : ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY�Ľṹ��
 1.��    ��   : 2014��11��06��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_IMS_VOICE_CAP_NOTIFY
 �ṹ˵��  : ID_MSCC_MMA_IMS_VOICE_CAP_NOTIFY�Ľṹ��
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU MSCC_MMA_IMS_VOICE_CAP_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enSrvSta;
    VOS_UINT8                                               ucIsNewSession;
    VOS_UINT8                                               ucIsEhrpdSupport;   /* ��ʾ��ǰSession������HRPD��EHRPD����enSrvStaΪNORMAL_SERVICEʱ��Ч */
    VOS_UINT8                                               aucReserved[2];
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType;
} MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT32                                  ulMcc;
    VOS_UINT8                                   ucUATIColorCode;
    VOS_UINT8                                   ucSubNetMask;
    VOS_UINT8                                   ucSecondaryColorCodeCount;
    VOS_UINT8                                   aucSecondaryColorCode[MSCC_MMA_SECOND_COLORCODE_MAX_LENGTH];
    VOS_UINT8                                   aucSectorId[MSCC_MMA_SUBNET_ID_MAX_LENGTH];
    VOS_INT32                                   lLongitude;
    VOS_INT32                                   lLatitude;
    VOS_UINT32                                  ulSector24;
} MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    MSCC_MMA_HRPD_SYS_ACQ_RSLT_ENUM_UINT32                  enSysAcqRslt;
} MSCC_MMA_HRPD_SYS_ACQ_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CDMA_MO_CALL_START_NTF�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU;




/*****************************************************************************
 �ṹ��    : MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CDMA_MO_CALL_END_NTF�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_CDMACSQ_SET_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_CDMACSQ_SET_REQ�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU MMA_MSCC_CDMACSQ_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_CFREQ_LOCK_NTF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CFREQ_LOCK_NTF�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU MMA_MSCC_CFREQ_LOCK_NTF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_1X_SYSTEM_TIME_IND_STRU
 �ṹ˵��  : ID_MSCC_MMA_1X_SYSTEM_TIME_IND��Ϣ�Ľṹ��
 1.��    ��   : 2015��03��4��
   ��    ��   : L00256032
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_1X_SYSTEM_TIME_IND_STRU MSCC_MMA_1X_SYSTEM_TIME_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU
 �ṹ˵��  : ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND��Ϣ�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_1X_SYSTEM_SERVICE_INFO_IND_STRU MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CDMACSQ_SET_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_CDMACSQ_SET_CNF��Ϣ�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU MSCC_MMA_CDMACSQ_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CDMACSQ_IND_STRU
 �ṹ˵��  : ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND��Ϣ�Ľṹ��
 1.��    ��   : 2015��02��4��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CDMACSQ_IND_STRU MSCC_MMA_CDMACSQ_IND_STRU;




/*****************************************************************************
 �ṹ��    : MMA_MSCC_CFPLMN_SET_REQ_STRUS
 �ṹ˵��  : ID_MMA_MSCC_CPLMN_REQ�Ľṹ��
 1.��    ��   : 2015��2��4��
   ��    ��   : f00279542
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU MMA_MSCC_CFPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_CFPLMN_QUERY_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_CPLMN_REQ�Ľṹ��
 1.��    ��   : 2015��2��4��
   ��    ��   : f00279542
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU MMA_MSCC_CFPLMN_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CFPLMN_SET_CNF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CPLMN_SET_CNF�Ľṹ��
 1.��    ��   : 2015��2��4��
   ��    ��   : f00279542
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU MSCC_MMA_CFPLMN_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CFPLMN_QUERY_CNF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CPLMN_QRY_CNF�Ľṹ��
 1.��    ��   : 2015��2��4��
   ��    ��   : f00279542
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU MSCC_MMA_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CFPLMN_OPERATE_TYPE_ENUM_UINT8
 �ṹ˵��  : ��������
 1.��    ��   : 2015��2��4��
   ��    ��   : f00279542
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8 MSCC_MMA_CFPLMN_OPERATE_TYPE_ENUM_UINT8;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_PREF_PLMN_QUERY_REQ�Ľṹ��
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_PREF_PLMN_QUERY_CNF�Ľṹ��
 1.��    ��   : 2015��02��04��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_PREF_PLMN_SET_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_PREF_PLMN_SET_REQ�Ľṹ��
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU MMA_MSCC_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_PREF_PLMN_SET_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_PREF_PLMN_SET_CNF�Ľṹ��
 1.��    ��   : 2015��02��04��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU MSCC_MMA_PREF_PLMN_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU
 �ṹ˵��  : ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND�Ľṹ��
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_IMS_START_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_IMS_START_REQ�Ľṹ��
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_START_REQ_STRU MMA_MSCC_IMS_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_IMS_START_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_IMS_START_CNF�Ľṹ��
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_START_CNF_STRU MSCC_MMA_IMS_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_IMS_STOP_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_IMS_STOP_REQ�Ľṹ��
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_STOP_REQ_STRU MMA_MSCC_IMS_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_IMS_STOP_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_IMS_STOP_CNF�Ľṹ��
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_STOP_CNF_STRU MSCC_MMA_IMS_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_IMS_SWITCH_STATE_IND_STRU
 �ṹ˵��  : ID_MSCC_MMA_IMS_SWITCH_STATE_IND�Ľṹ��
 1.��    ��   : 2015��04��15��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU MSCC_MMA_IMS_SWITCH_STATE_IND_STRU;




/** ****************************************************************************
 * Name        : MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32   enSysType;
}MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU;



/*****************************************************************************
 �ṹ��    : MMA_MSCC_CDMA_PS_RATTYPE_NTF_STRU
 �ṹ˵��  : ID_MMA_MSCC_CDMA_PS_RATTYPE_NTF�Ľṹ��
 1.��    ��   : 2015��05��11��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU MMA_MSCC_PS_RAT_TYPE_NTF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_AUTO_RESEL_SET_STRU
 �ṹ˵��  : ID_MMA_MSCC_AUTO_RESEL_SET �Ľṹ��
 1.��    ��   : 2015��6��3��
   ��    ��   : B00269685
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_AUTO_RESEL_SET_STRU MMA_MSCC_AUTO_RESEL_SET_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_CSG_LIST_SEARCH_REQ �Ľṹ��
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CSG_LIST_REJ_STRU
 �ṹ˵��  : Mscc��mma����CSG list�����������reject����Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_REJ_STRU MSCC_MMA_CSG_LIST_REJ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU
 �ṹ˵��  : mscc��mma����CSG list���������Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_CSG_LIST_ABORT_CNF_STRU
 �ṹ˵��  : mscc��mma����CSG list abort�����Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU MSCC_MMA_CSG_LIST_ABORT_CNF_STRU;
/****************************************************************
 �ṹ��    : MMA_MSCC_CSG_LIST_ABORT_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_CSG_LIST_ABORT_REQ �Ľṹ��
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU MMA_MSCC_CSG_LIST_ABORT_REQ_STRU;

/** ****************************************************************************
 �ṹ��    : MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU
 �ṹ˵��  : mma��mscc���ͻ�ȡ�ֻ�״̬��Ϣ����Ϣ�ṹ
 1.��    ��   : 2015��5��16��
   ��    ��   : z00316370
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;                              /* _H2ASN_Skip */
    MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32                  enInfoType;
}MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU
 �ṹ˵��  : MSCC��MMA�ظ����ֻ�״̬��Ϣ����Ϣ�ṹ
 1.��    ��   : 2015��5��16��
   ��    ��   : z00316370
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32                  enInfoType;         /* �������Ϣ���� */
    VOS_UINT8                                               ucCasState;         /* ��״̬ */
    VOS_UINT8                                               ucCasSubSta;        /* ��״̬ */
    MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8                        enHighVer;          /* cas�ϱ�����֧�ֵ���ߵİ汾 */
    VOS_UINT8                                               aucRsv[1];
}MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU;

/** ****************************************************************************
 * Name        : MSCC_MMA_UE_STATE_IND_STRU
 * Description : UE STATE indication
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    MSCC_PIF_MSG_TYPE_ENUM_UINT32                           enMsgId;    /* _H2ASN_Skip */
    VOS_UINT8                                               ucUeMainState;
    VOS_UINT8                                               ucUeSubState;
    VOS_UINT8                                               aucReserve[2];
}MSCC_MMA_UE_STATE_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_GET_GEO_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_GET_GEO_REQ�Ľṹ��
 1.��    ��   : 2015��05��12��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_GET_GEO_REQ_STRU MMA_MSCC_GET_GEO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_GET_GEO_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_GET_GEO_CNF�Ľṹ��
 1.��    ��   : 2015��05��12��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_GET_GEO_CNF_STRU MSCC_MMA_GET_GEO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_STOP_GET_GEO_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_STOP_GET_GEO_REQ�Ľṹ��
 1.��    ��   : 2015��06��01��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU MMA_MSCC_STOP_GET_GEO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_STOP_GET_GEO_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_STOP_GET_GEO_CNF�Ľṹ��
 1.��    ��   : 2015��06��01��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU MSCC_MMA_STOP_GET_GEO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MMA_MSCC_DPLMN_SET_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_DPLMN_SET_REQ�Ľṹ��
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_DPLMN_SET_REQ_STRU MMA_MSCC_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_DPLMN_SET_CNF_STRU
 �ṹ˵��  : ID_MSCC_MMA_DPLMN_SET_CNF�Ľṹ��
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_DPLMN_SET_CNF_STRU MSCC_MMA_DPLMN_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MSCC_MMA_1X_SID_NID_IND_STRU
 �ṹ˵��  : MSCC��MMA�ϱ���sid��Ϣ
 1.��    ��   : 2015��5��16��
   ��    ��   : y00322978
   �޸�����   : �½�
 2.��    ��   : 2015��12��10��
   ��    ��   : l00324781
   �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�
*****************************************************************************/
typedef NAS_MSCC_PIF_SID_NID_IND_STRU MSCC_MMA_1X_SID_NID_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_QUIT_CALL_BACK_IND_STRU
 �ṹ˵��  : mma  snd  mscc   QUIT CALL BACK MODE cnf msg stru
 1.��    ��   : 2015��5��16��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU MMA_MSCC_QUIT_CALL_BACK_NTF_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_SET_CSIDLIST_REQ_STRU
 �ṹ˵��  : MMA SND MSCC REQ set csidlist
 1.��    ��   : 2015��5��16��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU MMA_MSCC_SET_CSIDLIST_REQ_STRU;
/*****************************************************************************
 �ṹ��    : MSCC_MMA_SET_CSIDLIST_CNF_STRU
 �ṹ˵��  :  mscc snd  mma   set csidlist cnf msg stru
 1.��    ��   : 2015��5��16��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU MSCC_MMA_SET_CSIDLIST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_SET_CSIDLIST_CNF_STRU
 �ṹ˵��  :  mscc snd  mma   set csidlist cnf msg stru
 1.��    ��   : 2015��5��16��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_SYNC_SERVICE_AVAILABLE_IND_STRU MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU;


/*****************************************************************************
 �ṹ��    : MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU
 �ṹ˵��  : MSCC��MMA�ظ�������CALLBACKģʽ״̬����Ϣ�ṹ
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_EMC_CALLBACK_IND_STRU MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    MSCC_PIF_MSG_TYPE_ENUM_UINT32       enMsgID;    /*_H2ASN_MsgChoice_Export MMA_MSCC_MSG_ID_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMA_MSCC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMA_MSCC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMA_MSCC_MSG_DATA    stMsgData;
}MmaMsccInterface_MSG;


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

#endif
