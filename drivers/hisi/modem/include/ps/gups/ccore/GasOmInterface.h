/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : GasOmInterface.h
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2008��5��6��
  ����޸�   :
  ��������   : GASģ���OM֮��Ľӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��05��06��
    ��    ��   : ���� y58800
    �޸�����   : �������ļ�
  2.��    ��   : 2013��07��23��
    ��    ��   : y00142674
    �޸�����   : ɾ���ظ�����LOG_MIN_FILE_ID_PS��for code_check_report compile warning

******************************************************************************/

#ifndef __GASOMINTERFACE_H__
#define __GASOMINTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C"{
    #endif
#endif /* __cplusplus */

/* ����ģ����뿪�ؼ��п��� */
#include "product_config.h"

#include "Nasrrcinterface.h"
#include "errorlog.h"

#include "PsLogdef.h"
#include "NVIM_Interface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "LRrcGuRrcCommInterface.h"
#include "LRrcGrrInterface.h"
#endif

#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
#include "TRrcGrrCommInterface.h"
#endif

#include "PsRrmInterface.h"

#include "PhyGasInterface.h"
#include "CssInterface.h"

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define GAS_OM_3G_NCELL_NUMBER            12                    /* 3G���������� */

#if (FEATURE_ON == FEATURE_LTE)
#define  GAS_OM_INVALID_LTE_RPT_PEROID_LEN         0xffff               /* �����ϱ�LTE���ڳ��ȵ���Чֵ */
#define  GAS_OM_MAX_LTE_NCELL_NUM                  32                   /* GAS�ϱ�OM��LTEС�������� */
#endif

/* Added by d00132956 for �ڴ��Ż���2011-10-21,begin */
#define GAS_OM_PRINT_MSG_MAX_NUM          40  
#define GAS_OM_PRINT_MSG_MIN_NUM          10        
/* Added by d00132956 for �ڴ��Ż���2011-10-21,end */

/* Added by j00178524 for ·������, 2012-11-09, begin */
#define GAS_OM_RD_TEST_UINT16_INVALID_VALUE         0xFFFF
#define GAS_OM_RD_TEST_INT16_INVALID_VALUE          (VOS_INT16)0x8000

#define GAS_OM_RD_TEST_UINT32_INVALID_VALUE         0xFFFFFFFF


#define GAS_OM_2G_NCELL_CNT_MAX_NUM                 6
#define GAS_OM_3G_NCELL_CNT_MAX_NUM                 96
#define GAS_OM_HOPPING_REQ_CNT_MAX_NUM              64
/* Added by j00178524 for ·������, 2012-11-09, end */

#define GAS_OM_APPLY_TASK_LIST_MAX_NUM           (8)                            /* ������Դ������������ */

#define GAS_OM_CSS_INTERFACE_OUPUT_PREF_FREQ_MAX_NUM    (4)
#define GAS_OM_CSS_INTERFACE_OUPUT_PREF_BAND_MAX_NUM    (50)
#define GAS_OM_CSS_INTERFACE_INPUT_PLMN_MAX_NUM         (19)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
 ö����    : OM_GAS_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : OM <-> GAS �ӿ���ϢID
*****************************************************************************/
/* ˵�� */
/* ���ڸ����ߵ�����/״̬�ϱ�ͨ��OM͸��ͨ����OM�������ߵİ�ͷ�޷�ȷ��������ģ�飬
   �����߶��壬��Ҫͨ���ϱ���ԭ��ָʾ����ģ�飬
   ��: ԭ��ĸ� 8 λ��ʾ����ģ�飬�����¶���:
   
   0xA0XX: ��ʾ GAS ģ�鷢��������/״̬�ϱ�
   0xB0XX: ��ʾ WAS ģ�鷢��������/״̬�ϱ�
   0xC0XX: ��ʾ NAS ģ�鷢��������/״̬�ϱ�
   0xD0XX: ��ʾ TTF ģ�鷢��������/״̬�ϱ�
   0xE0XX: ��ʾ GHPA ģ�鷢��������/״̬�ϱ�
   0xF0XX: ��ʾ HPA ģ�鷢��������/״̬�ϱ�

   �¼��ϱ�����ģ��䱣֤ԭ���Ψһ�ԣ���ΪOM��APP��ͷ�����˷�����ģ��ID��

 */
enum OM_GAS_MSG_ID_ENUM
{
    /* ָ��Ƶ��פ�� */
    ID_OM_GAS_SPECIFIC_FREQ_CAMP_REQ             = 0xA000,    /* _H2ASN_MsgChoice  OM_GAS_SPECIFIC_FREQ_CAMP_REQ_ST */        

    /* ����/״̬��ѯ���� */
    ID_OM_GAS_CELL_INFO_REQ                      = 0xA001,    /* _H2ASN_MsgChoice  OM_GAS_CELL_INFO_REQ_ST */
    ID_OM_GAS_CHANNEL_QUALITY_REQ                = 0xA002,    /* _H2ASN_MsgChoice  OM_GAS_CHANNEL_QUALITY_REQ_ST */    
    ID_OM_GAS_3G_NCELL_MEAS_REQ                  = 0xA003,    /* _H2ASN_MsgChoice  OM_GAS_3G_NCELL_MEAS_REQ_ST */    
    ID_OM_GAS_GSM_INFO_REQ                       = 0xA004,    /* _H2ASN_MsgChoice  OM_GAS_GSM_INFO_REQ_ST */    

    /* �տ���Ϣ�������� */
    ID_OM_GAS_OTA_REQ                            = 0xA005,    /* _H2ASN_MsgChoice  OM_GAS_OTA_REQ_STRUCT */

    /* ָ��Ƶ��פ�� */
    ID_GAS_OM_SPECIFIC_FREQ_CAMP_CNF             = 0xA010,    /* _H2ASN_MsgChoice  GAS_OM_SPECIFIC_FREQ_CAMP_CNF_ST */

    /* ����/״̬��ѯ��ȷ�� */
    ID_GAS_OM_CELL_INFO_CNF                      = 0xA011,    /* _H2ASN_MsgChoice  GAS_OM_CELL_INFO_CNF_ST */
    ID_GAS_OM_CHANNEL_QUALITY_CNF                = 0xA012,    /* _H2ASN_MsgChoice  GAS_OM_CHANNEL_QUALITY_CNF_ST */
    ID_GAS_OM_3G_NCELL_MEAS_CNF                  = 0xA013,    /* _H2ASN_MsgChoice  GAS_OM_INFO_CNF_ST */
    ID_GAS_OM_GSM_INFO_CNF                       = 0xA014,    /* _H2ASN_MsgChoice  GAS_OM_INFO_CNF_ST */

    /* �տ���Ϣ����ȷ�� */
    ID_GAS_OM_OTA_CNF                            = 0xA015,    /* _H2ASN_MsgChoice  GAS_OM_OTA_CNF_STRUCT */

    /* Added by d00132956 for �ڴ��Ż���2011-10-21,begin */
    /* ��ӡ������Ϣ */
    ID_GAS_OM_PRINT_MSG                          = 0xA016,
    /* Added by d00132956 for �ڴ��Ż���2011-10-21,end */

    /* ����/״̬�ϱ� */
    ID_GAS_OM_CELL_INFO_IND                      = 0xA021,    /* _H2ASN_MsgChoice GAS_OM_CELL_INFO_IND_ST */
    ID_GAS_OM_CHANNEL_QUALITY_IND                = 0xA022,    /* _H2ASN_MsgChoice GAS_OM_CHANNEL_QUALITY_IND_ST */
    ID_GAS_OM_3G_NCELL_MEAS_IND                  = 0xA023,    /* _H2ASN_MsgChoice GAS_OM_3G_NCELL_MEAS_IND_ST */
    ID_GAS_OM_GSM_INFO_IND                       = 0xA024,    /* _H2ASN_MsgChoice GAS_OM_GSM_INFO_IND_ST */

    /* �տ���Ϣ�ϱ� */
    ID_GAS_OM_OTA_IND                            = 0xA025,    /* _H2ASN_MsgChoice GAS_OM_OTA_IND_STRUCT */
    ID_GAS_OM_DEC_FAIL_CELL_IND                  = 0xA026,    /* _H2ASN_MsgChoice GAS_OM_EVENT_PLMN_SEARCH_DEC_CELL_STRU */
    ID_GAS_OM_RXLEV_CELL_IND                     = 0xA027,    /* _H2ASN_MsgChoice GAS_OM_EVENT_PLMN_SEARCH_RXLEV_STRU */
    ID_GAS_OM_PREFER_CELL_IND                    = 0xA028,    /* _H2ASN_MsgChoice GAS_OM_PREFER_CELL_ST */

    ID_GAS_OM_GSM_FORBIDDEN_LIST_IND             = 0xA029,

    ID_GAS_OM_GSM_UNAVAILABLE_LIST_IND           = 0xA02A,

    ID_GAS_OM_MM_INFO_IND                        = 0xA02B,
    /* Added by yangsicong for probe�ӿ��¿���, 2012-10-30, begin */
    ID_OM_GAS_ROAD_TEST_INFO_REQ                 = 0xA02C,   /* _H2ASN_MsgChoice GAS_OM_ROAD_TEST_INFO_REQ_STRU */
    ID_GAS_OM_ROAD_TEST_INFO_CNF                 = 0xA02D,   /* _H2ASN_MsgChoice GAS_OM_ROAD_TEST_INFO_CNF_STRU */
    ID_GAS_OM_ROAD_TEST_INFO_IND                 = 0xA02E,   /* _H2ASN_MsgChoice GAS_OM_ROAD_TEST_INFO_IND_STRU */
    /* Added by yangsicong for probe�ӿ��¿���, 2012-10-30, end */

    ID_GAS_OM_JAM_DETECT_CTX_IND                 = 0xA030,   /* _H2ASN_MsgChoice GAS_OM_JAM_DETECT_CTX_IND_STRU */

    ID_GAS_OM_GSM_FREQ_LOCKED                     = 0xA031,

    ID_GAS_OM_UNEXPECTED_MSG_RCVED                = 0xA032,

    ID_GAS_OM_NON_CHAN_REL_FR_TYPE                = 0xA033,

    ID_GAS_OM_GAS_GCOM_RF_RES_CTRL                = 0xA034,

    ID_GAS_OM_SCELL_RX_QUAL_INFO                  = 0xA035,

    #if (FEATURE_ON == FEATURE_LTE)
    ID_GAS_OM_LTE_UNSUPPORT_FREQ                  = 0xA036,
    #endif

    ID_GAS_OM_GAS_GCOM_CSS_BAND_SCAN_LIST_INFO    = 0xA037,
    ID_GAS_OM_GAS_GCOM_SAVED_CSS_BAND_SCAN_INFO   = 0xA038,

    ID_GAS_OM_GSM_HISTORY_SI_CTX_IND              = 0xA039,   /* _H2ASN_MsgChoice GAS_OM_GSM_HISTORY_SI_CONTEXT_STRU */

    /* Added by y00142674 for �����̳�, 2015-07-14, begin */
    ID_GAS_OM_GSM_HISTORY_NCELL_SI_CTX_IND        = 0xA03A,   /* _H2ASN_MsgChoice GAS_OM_GSM_HISTORY_NCELL_SI_CTX_IND_STRU */
    /* Added by y00142674 for �����̳�, 2015-07-14, end */

    /* Added by p00166345 for DTS2015052601104(α��վʶ��), 2015-08-02, begin */
    ID_GAS_OM_PSEUD_BTS_IDENT_INFO                = 0xA03B,   /* _H2ASN_MsgChoice GAS_OM_PSEUD_BTS_IDENT_INFO_STRU */
    /* Added by p00166345 for DTS2015052601104(α��վʶ��), 2015-08-02, end */

    ID_GAS_OM_PARALLEL_SRCH_CTX_IND               = 0xA03C,   /* _H2ASN_MsgChoice GAS_OM_PARALLEL_SRCH_CTX_STRU */
    ID_GAS_OM_PARALLEL_SRCH_RULE_IND              = 0xA03D,   /* _H2ASN_MsgChoice GAS_OM_PARALLEL_SRCH_RULE_STRU */

    ID_GAS_OM_PARALLEL_NCELL_NORMAL_CTX_IND       = 0xA03E,     /* _H2ASN_MsgChoice GAS_OM_PARALLEL_NCELL_NORMAL_CTX_STRU */

    ID_GAS_OM_DEDICATED_HO_INFO                   = 0xA040,     /* _H2ASN_MsgChoice GAS_GCOM_DEDICATED_HO_INFO_STRU */

    ID_GAS_OM_ARFCN_CELL_IDENT_INFO_LST           = 0xA041,     /* _H2ASN_MsgChoice GAS_GCOM_GSM_ARFCN_CELL_IDENT_INFO_LST_STRU */

    ID_GAS_OM_INTER_RESEL_EVALUATE_RLT            = 0xA042,     /* _H2ASN_MsgChoice GAS_OM_INTER_RESEL_EVALUATE_RLT_STRU */

    /* �¼��ϱ� */
    ID_GAS_OM_EVENT_GSM_RANDOM_ACCESS_REQUEST    = 0xA0A1,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */ 
    ID_GAS_OM_EVENT_GSM_LINK_FAILURE             = 0xA0A2,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_LINK_FAILURE_ST */
    ID_GAS_OM_EVENT_GSM_DOWNLINK_FAILURE         = 0xA0A3,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_DOWNLINK_FAILURE_ST */
    ID_GAS_OM_EVENT_GSM_RESELECT_START           = 0xA0A4,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_RESELECT_START_ST */
    ID_GAS_OM_EVENT_GSM_RESELECT_END             = 0xA0A5,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_RESELECT_END_ST */
    ID_GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START       = 0xA0A6,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START_ST */
    ID_GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END         = 0xA0A7,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END_ST */
    ID_GAS_OM_EVENT_GSM_RR_IN_SERVICE            = 0xA0A8,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_RR_OUT_OF_SERVICE        = 0xA0A9,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_PAGE_RECEIVED            = 0xA0AA,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */    
    ID_GAS_OM_EVENT_GPRS_PAGE_RECEIVED           = 0xA0AB,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GPRS_LINK_FAILURE            = 0xA0AC,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_PACKET_RANDOM_ACCESS_REQUEST = 0xA0AD,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START  = 0xA0AE,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END    = 0xA0AF,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_HANDOVER_START  = 0xA0B0,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_HANDOVER_END    = 0xA0B1,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GPRS_ACCESS_REJECT           = 0xA0B2,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE    = 0xA0B3,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE_ST */
    /* 2008-10-14 */
    ID_GAS_OM_EVENT_GPRS_INVALID_ASSIGN          = 0xA0B4,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GPRS_INVALID_ASSIGN_ST */
    ID_GAS_OM_EVENT_TIMER_ACTION                 = 0xA0B5,      /* _H2ASN_MsgChoice GAS_OM_EVENT_TIMER_ACTION_ST */

    /* 2008-04-02 */
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_UP_ONE      = 0xA0B6,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_UP_FIRST    = 0xA0B7,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_DOWN_ONE    = 0xA0B8,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_DOWN_FIRST  = 0xA0B9,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    
    ID_GAS_OM_EVENT_IMMEDIATE_ASSIGN_SECOND      = 0xA0BA,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */ 
    
    ID_GAS_OM_EVENT_OUT_OF_SERVICE               = 0xA0BB,      /* _H2ASN_MsgChoice GAS_OM_EVENT_OUT_OF_SERVICE_ST*/ 

    ID_GAS_OM_EVENT_DSP_LOAD_FAIL                = 0xA0BC,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */ 
    ID_GAS_OM_EVENT_RR_CONNECTION_ABNORMAL       = 0xA0BD,      /* _H2ASN_MsgChoice GAS_OM_EVENT_RR_CONNECTION_ABNORMAL_ST */

    ID_GAS_OM_EVENT_BUFFER_MESSAGE_DELETED       = 0xA0BE,      /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */   

    ID_GAS_OM_EVENT_2G_NCELL_LIST_CHANGE         = 0xA0BF,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_2G_NCELL_LIST_CHANGE_ST */
    ID_GAS_OM_EVENT_3G_NCELL_LIST_CHANGE         = 0xA0C0,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_3G_NCELL_LIST_CHANGE_ST */

    ID_GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START  = 0xA0C1,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END    = 0xA0C2,      /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END_ST */

    ID_GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START      = 0xA0C3,    /* _H2ASN_MsgChoice GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_ST */        
    ID_GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END        = 0xA0C4,    /* _H2ASN_MsgChoice GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END_ST */

    ID_GAS_OM_EVENT_PERIOD_CHECK_WEAK_SIGNAL_T_EXPIRED = 0xA0C5,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_INIT_WEAK_SIGNAL                   = 0xA0C6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INIT_WEAK_SIGNAL_ST */
    ID_GAS_OM_EVENT_PERIOD_WEAK_SIGNAL                 = 0xA0C7,    /* _H2ASN_MsgChoice GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_ST */
    ID_GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_LIST            = 0xA0C8,    /* _H2ASN_MsgChoice GAS_OM_EVENT_WEAK_SIGNAL_LIST_ST */

    #if (FEATURE_ON == FEATURE_LTE)

    /* ���� G �� L ������ ��ά�ɲ���Ϣ */
    ID_GAS_OM_EVENT_GSM_TO_LTE_RESEL_START             = 0xA0C9,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_RESEL_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_RESEL_END               = 0xA0CA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_RESEL_END_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_RESEL_START             = 0xA0CB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_RESEL_START_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_RESEL_END               = 0xA0CC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_RESEL_END_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_CCO_START               = 0xA0CD,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_CCO_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_CCO_END                 = 0xA0CE,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_CCO_END_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_CCO_START               = 0xA0CF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_CCO_START_ST */    
    ID_GAS_OM_EVENT_LTE_TO_GSM_CCO_END                 = 0xA0D0,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_CCO_END_ST */
    ID_OM_GAS_LTE_NCELL_MEAS_REPORT_REQ                = 0xA0D1,    /* _H2ASN_MsgChoice OM_GAS_INFO_REQ_ST */
    ID_GAS_OM_LTE_NCELL_MEAS_REPORT_CNF                = 0xA0D2,
    ID_GAS_OM_LTE_NCELL_MEAS_IND                       = 0xA0D3,    /* _H2ASN_MsgChoice GAS_OM_LTE_NCELL_MEAS_IND_ST */    
    ID_GAS_OM_EVENT_GSM_TO_LTE_REDIR_START             = 0xA0D4,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_REDIR_END               = 0xA0D5,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_LTE_REDIR_END_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_REDIR_START             = 0xA0D6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_REDIR_START_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_REDIR_END               = 0xA0D7,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_REDIR_END_ST */

    #endif

    ID_GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL            = 0xA0D8,    /* _H2ASN_MsgChoice  GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL            = 0xA0D9,    /* _H2ASN_MsgChoice  GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL_ST */

    ID_GAS_OM_EVENT_RCV_SI_ON_PCH                      = 0xA0DA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_RCV_SI_ON_PCH_STRU */

    ID_GAS_OM_EVENT_CLEAR_FORBIDDEN_LIST               = 0xA0DB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */            
    ID_GAS_OM_EVENT_RESET_FORBIDDEN_LIST_FAIL_TIMES    = 0xA0DC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START       = 0xA0DD,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END         = 0xA0DE,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START       = 0xA0DF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END         = 0xA0E0,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_START               = 0xA0E1,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INTER_RESEL_EVALUATE_START_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_TIMER_START         = 0xA0E2,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_START_ST */
    ID_GAS_OM_EVENT_RESEL_EVALUATE_TIMER_EXPIRED       = 0xA0E3,    /* _H2ASN_MsgChoice GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_EXPIRED_ST */

    ID_GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_RESULT      = 0xA0E6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_END_ST */   
    ID_GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END            = 0xA0E7,    /* _H2ASN_MsgChoice  GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END_ST */        

#if (FEATURE_ON == FEATURE_LTE)
    ID_GAS_OM_EVENT_LTE_TO_GSM_ANR_END                 = 0xA0E8,   /* _H2ASN_MsgChoice  GAS_OM_EVENT_LTE_TO_GSM_ANR_END_ST */

#endif
    
    ID_GAS_OM_EVENT_BG_PLMN_SEARCH_LTE_END             = 0xA0E9,    /* _H2ASN_MsgChoice GAS_OM_ABNORMAL_EVENT_BG_PLMN_SEARCH_LTE_ST */
    ID_GAS_OM_EVENT_DSP_INIT_FAILED                    = 0xA0EA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_DISCARD_REASSEMBLED_APDU           = 0xA0EB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_RRLP_MESSAGE_OVER_MAX_LENGTH       = 0xA0EC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_RRLP_MESSAGE_REQ                   = 0xA0ED,
    ID_GAS_OM_EVENT_RRLP_MESSAGE_RSP                   = 0xA0EE,

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START         = 0xA0EF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END           = 0xA0F0,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START         = 0xA0F1,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END           = 0xA0F2,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START       = 0xA0F3,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END         = 0xA0F4,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START         = 0xA0F5,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END           = 0xA0F6,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END_ST */

    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HO_START          = 0xA0F7,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HO_END            = 0xA0F8,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW           = 0xA0F9,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW_ST */

    ID_GAS_OM_EVENT_CS_PS_TRANSACTION_INFO             = 0xA0FA,    
    
    ID_GAS_OM_EVENT_RR_POOR_RXQUAL                     = 0xA0FB,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_FAST_RETURN_VALID = 0xA0FC,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_FAST_RETURN_INVALID = 0xA0FD,  /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START       = 0xA0FE,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START_ST */
    ID_GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END         = 0xA0FF,    /* _H2ASN_MsgChoice GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END_ST */

    /* Added by y00142674 for GSM�����ض���LTE, 2013-06-21, begin */
    ID_GAS_OM_EVENT_GSM_TO_LTE_AUTO_FAST_RETURN_VALID   = 0xA100,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GSM_TO_LTE_AUTO_FAST_RETURN_INVALID = 0xA101,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_EVENT_GAS_INTERNAL_MSG_LENGTH_TOO_LONG    = 0xA102,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_OM_EVENT_GAS_INTERNAL_MSG_QUEUE_IS_FULL      = 0xA103,   /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    /* Added by y00142674 for GSM�����ض���LTE, 2013-06-21, end */

#if (FEATURE_ON == FEATURE_LTE)
    ID_GAS_OM_EVENT_LTE_TO_GSM_HO_START                 = 0xA104,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_START_ST */
    ID_GAS_OM_EVENT_LTE_TO_GSM_HO_END                   = 0xA105,    /* _H2ASN_MsgChoice GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_END_ST */
#endif /* end of (FEATURE_ON == FEATURE_LTE) */    

    ID_GAS_OM_EVENT_W_NON_NCELL_MEAS_START              = 0xA106,    /* _H2ASN_MsgChoice GAS_OM_EVENT_W_NON_NCELL_MEAS_START_ST */

#if ( FEATURE_ON == FEATURE_DSDS )
    ID_GAS_OM_EVENT_RF_RESOURCE_TASK_LIST               = 0xA107,     /* _H2ASN_MsgChoice GAS_OM_EVENT_RF_RESOURCE_TASK_LIST_STRU */
#endif

    ID_GAS_OM_EVENT_PLMN_SEARCH_CELL_SATISFACTION_LIST_IND  = 0xA108,    /* _H2ASN_MsgChoice GAS_OM_PLMN_SRCH_CELL_SATISFACTION_RESULT_ST */

    ID_GAS_OM_EVENT_C1_CUSTOMIZE_VALID                  = 0xA109,

    ID_GAS_OM_EVENT_C1_CUSTOMIZE_INVALID                = 0xA10A,

    ID_GAS_OM_EVENT_C1_RESEL_CANCELED_FOR_C1_CUSTOMIZE  = 0xA10B,
    

    ID_GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START         = 0xA10C,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START_ST */
    ID_GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END           = 0xA10D,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END_ST */
    ID_GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START         = 0xA10E,    /* _H2ASN_MsgChoice GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START_ST */

    ID_GAS_OM_EVENT_RA_CNF_FAIL_NO_RF                    = 0xA10F,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */

    ID_GAS_OM_AFC_INFO_IND                              = 0xA110,    /* _H2ASN_MsgChoice GAS_OM_AFC_INFO_IND_ST */

    /* Added by y00142674 for ���������Ż�, 2015-04-30, begin */
    ID_GAS_OM_EVENT_SB_IND_FAIL_NO_RF                   = 0xA111,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    /* Added by y00142674 for ���������Ż�, 2015-04-30, end */

    ID_GAS_OM_EVENT_LAU_REQ_INFO                        = 0xA112,     /* _H2ASN_MsgChoice GAS_OM_EVENT_LAU_REQ_INFO_STRU */

    ID_GAS_OM_EVENT_UTRAN_CELL_BAR                      = 0xA113,

    ID_GAS_OM_SEARCH_PROC_INFO                          = 0xA114,   /* _H2ASN_MsgChoice GAS_OM_SEARCH_PROC_INFO_STRU */
    ID_GAS_OM_SEARCHED_FREQ_LIST                        = 0xA115,   /* _H2ASN_MsgChoice GAS_OM_SEARCHED_FREQ_LIST_STRU */

    ID_GAS_OM_EVENT_START_TIMER_FAIL                    = 0xA116,

    ID_GAS_OM_EVENT_CSS_CLOUD_INTERFACE                 = 0xA117,   /* _H2ASN_MsgChoice GAS_OM_CSS_CLOUD_INTERFACE_STRU */

    ID_OM_GAS_WRITE_NV_REQ                             = 0xAAA7,    /* _H2ASN_MsgChoice GAS_OM_WRITE_NV_REQ_ST */
    ID_GAS_OM_WRITE_NV_CNF                             = 0xAAA8,

    ID_SDT_GAS_CONNECTED_IND                           = 0xAAAA,    /* _H2ASN_MsgChoice GAS_OM_EVENT_IND_COMMON_ST */
    ID_GAS_SDT_CONNECTED_CNF                           = 0xAAAB,

    ID_GAS_OM_MSG_BUTT
};
typedef VOS_UINT16  OM_GAS_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : OM_GAS_REPORT_ACTION_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : OM -> GAS ����Ϣ����
*****************************************************************************/
enum OM_GAS_REPORT_ACTION_ENUM
{
    OM_GAS_REPORT_STOP            = 0,
    OM_GAS_REPORT_START           = 1,
    
    OM_GAS_REPORT_BUTT
};
typedef VOS_UINT16 OM_GAS_REPORT_ACTION_ENUM_UINT16;

/*****************************************************************************
 ö����    : OM_GAS_REPORT_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : OM -> GAS ����Ϣ�ϱ�����
*****************************************************************************/
/* ��Ϣ�ϱ������� */
enum OM_GAS_REPORT_TYPE_ENUM
{
    OM_GAS_REPORT_TYPE_NULL       = 0,
    OM_GAS_REPORT_TYPE_ONCE       = 1,
    OM_GAS_REPORT_TYPE_PERIODIC   = 2,
    /*OM_GAS_REPORT_TYPE_CHANGED    = 4,*/          /*�ϱ�����̫�࣬���ṩ�иı��ϱ�������*/

    OM_GAS_REPORT_TYPE_BUTT
};
typedef VOS_UINT16 OM_GAS_REPORT_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : GAS_OM_STATE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM GAS״̬�ϱ�
*****************************************************************************/
enum GAS_OM_STATE_ENUM
{
    GAS_OM_STATE_IDLE             = 0,        /* ����̬ */
    GAS_OM_STATE_DEDICATED        = 1,        /* CSר��̬ */
    GAS_OM_STATE_TRANSFER         = 2,        /*  PS����̬ */

    GAS_STATE_BUTT
};
typedef VOS_UINT16 GAS_OM_STATE_ENUM_UINT16; 


/*****************************************************************************
 ö����    : GAS_DCH_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM ��ǰר���ŵ�����
*****************************************************************************/
enum GAS_DCH_TYPE_ENUM
{
    GAS_DCH_TYPE_NONE            = 0,          /* ��ǰû��ר���ŵ� */
    GAS_DCH_TYPE_DCH             = 1,          /* CS���ר���ŵ�: SDCCH��TCH */
    GAS_DCH_TYPE_PDTCH           = 2,          /* PS���ר���ŵ�: PDTCH */
    
    GAS_DCH_TYPE_BUTT
};
typedef VOS_UINT16 GAS_DCH_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : GAS_OM_GSM_BAND_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM GSM ��Ƶ������
*****************************************************************************/
enum GAS_OM_GSM_BAND_ENUM
{
    GAS_BAND_GSM850               = 0,         /* GSM850Ƶ�� */
    GAS_BAND_GSM900               = 1,         /* GSM900Ƶ�� */
    GAS_BAND_DCS                  = 2,         /* DCS1800Ƶ�� */
    GAS_BAND_PCS                  = 3,         /* PCS1900Ƶ�� */

    GAS_BAND_BUTT                 = 65535
};
typedef VOS_UINT16  GAS_OM_GSM_BAND_ENUM_UINT16;


/*****************************************************************************
 ö����    : GAS_OM_RRC_RR_CNF_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   RRC�ظ�RR�Ľ��
*****************************************************************************/
enum GAS_OM_RRC_RR_CNF_ENUM
{
    GAS_OM_RRC_RR_CNF_SUCCESS                    = 0,
    GAS_OM_RRC_RR_CNF_FAILURE                    = 1,
    GAS_OM_RRC_RR_CNF_MESSAGE_INVALID            = 2,
    GAS_OM_RRC_RR_CNF_PROTOCOL_ERROR             = 3,
    GAS_OM_RRC_RR_CNF_UNSUPORTED_CONFIGURATION   = 4,
    GAS_OM_RRC_RR_CNF_PHY_CHANNEL_FAILURE        = 5,

    GAS_OM_RRC_RR_CNF_BUTT
};
typedef VOS_UINT32 GAS_OM_RRC_RR_CNF_ENUM_UINT32;

/*****************************************************************************
 ö����    : GAS_OM_RLC_MODE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   RLCģʽ
*****************************************************************************/
enum GAS_OM_RLC_MODE_ENUM
{
    GAS_OM_RLC_MODE_AM                      = 0,            /* ȷ��ģʽ */
    GAS_OM_RLC_MODE_UM                      = 1,            /* ��ȷ��ģʽ */

    GAS_OM_RLC_MODE_BUTT
};
typedef VOS_UINT8 GAS_OM_RLC_MODE_ENUM_UINT8;


/*****************************************************************************
 ö����    : GAS_OM_MAC_MODE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   MACģʽ
*****************************************************************************/
enum GAS_OM_MAC_MODE_ENUM
{
    GAS_OM_MAC_MODE_FIXED_ALLOC             = 0,            /* �̶����� */         
    GAS_OM_MAC_MODE_DYN_ALLOC               = 1,            /* ��̬���� */
    GAS_OM_MAC_MODE_EXT_DYN_ALLOC           = 2,            /* ��չ��̬���� */
    GAS_OM_MAC_MODE_SINGLE_BLOCK_ALLOC      = 3,            /* ���� */
    GAS_OM_MAC_MODE_MULTI_BLOCK_ALLOC       = 4,            /* ������� */
    
    GAS_OM_MAC_MODE_BUTT
};
typedef VOS_UINT8 GAS_OM_MAC_MODE_ENUM_UINT8;


/*****************************************************************************
 ö����    : GAS_OM_CS_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   ���뷽ʽ
*****************************************************************************/
enum GAS_OM_CS_TYPE_ENUM
{
    GAS_OM_CS_TYPE_CS1                      = 0,            /* ���뷽ʽ CS1 */
    GAS_OM_CS_TYPE_CS2                      = 1,            /* ���뷽ʽ CS2 */
    GAS_OM_CS_TYPE_CS3                      = 2,            /* ���뷽ʽ CS3 */
    GAS_OM_CS_TYPE_CS4                      = 3,            /* ���뷽ʽ CS4 */

    GAS_OM_CS_TYPE_BUTT
};
typedef VOS_UINT8 GAS_OM_CS_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_RESEL_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   С����ѡ����
*****************************************************************************/
enum GAS_OM_RESEL_TYPE_ENUM
{
    GAS_OM_RESEL_TYPE_NONE                  = 0,            /* ���� */
    GAS_OM_RESEL_TYPE_ACTIVE                = 1,            /* ������ѡ */
    GAS_OM_RESEL_TYPE_PASSIVE               = 2,            /* ������ѡ */

    GAS_OM_RESEL_TYPE_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : GAS_OM_RESEL_CAUSE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   С����ѡԭ��
  1.��    ��   : 2015��12��21��
    ��    ��   : x00220225
    �޸�����   : ������ѡԭ������ͺ�GasGcomcPublicCellReselection.hһ�£�for DTS20151219018810 
*****************************************************************************/
enum GAS_OM_RESEL_CAUSE_ENUM
{
    GAS_OM_RESEL_CAUSE_ACTIVE_C2                    = 0,   /* С����ѡԭ��:��������ѡ */
    GAS_OM_RESEL_CAUSE_PASSIVE_PATH_LOSS            = 1,   /* С����ѡԭ��:����С��·�����̫�� */
    GAS_OM_RESEL_CAUSE_PASSIVE_NETWORK_CONTROL      = 2,   /* С����ѡԭ��:�������С����ѡ */
    GAS_OM_RESEL_CAUSE_PASSIVE_NAS_REQUEST          = 3,   /* С����ѡԭ��:NAS��ָʾ����С����ѡ */
    GAS_OM_RESEL_CAUSE_PASSIVE_DOWNLINK_FAILURE     = 4,   /* С����ѡԭ��:������·ʧ�� */
    GAS_OM_RESEL_CAUSE_PASSIVE_SI_FAILURE           = 5,   /* С����ѡԭ��:ϵͳ��Ϣ����ʧ�� */
    GAS_OM_RESEL_CAUSE_PASSIVE_GRR_N3102            = 6,   /* С����ѡԭ��:N3102���� */
    GAS_OM_RESEL_CAUSE_PASSIVE_RR_ACCESS_FAILURE    = 7,   /* С����ѡԭ��:�������ʧ�� */
    GAS_OM_RESEL_CAUSE_PASSIVE_RADIOLINK_FAILURE    = 8,   /* С����ѡԭ��:������·ʧЧ(reserved) */
    GAS_OM_RESEL_CAUSE_PASSIVE_RR_NAS_ABORT         = 9,   /* С����ѡԭ��:RR���յ�NAS������ԭ��RRMM_ABORT_REQ */
    GAS_OM_RESEL_CAUSE_PASSIVE_RR_CAMP_FAILURE      = 10,  /* С����ѡԭ��:RR�뿪ר��̬��פ��ʧ�ܵ���*/
    GAS_OM_RESEL_CAUSE_PASSIVE_CELL_BARRED          = 11,  /* С����ѡԭ��:С��Barred*/
    GAS_OM_RESEL_CAUSE_PASSIVE_NOT_SUITABLE         = 12,  /* С����ѡԭ��:С����������ʵ�С������*/
    GAS_OM_RESEL_CAUSE_PASSIVE_GRR_ACCESS_FAILURE   = 13,  /* С����ѡԭ��:GRR�������ʧ�� */
    GAS_OM_RESEL_CAUSE_PASSIVE_BAND_NOT_SUPPORT     = 14,  /* С����ѡԭ��:Ƶ�β�֧�� */
    GAS_OM_RESEL_CAUSE_PASSIVE_SCELL_TIMING_ERR     = 15,  /* С����ѡԭ��:����С��ʱ����� */
    GAS_OM_RESEL_CAUSE_PASSIVE_ROAD_TEST_FORCE_RESEL= 16,  /* С����ѡԭ��:·��ǿ����ѡ */

    GAS_OM_RESEL_CAUSE_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_RESULT_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   ִ�н��
*****************************************************************************/
enum GAS_OM_RESULT_ENUM
{
    GAS_OM_RESULT_FAILURE                           = 0,   /* ʧ�� */
    GAS_OM_RESULT_SUCCESS                           = 1,   /* �ɹ� */

    GAS_OM_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_RESULT_ENUM_UINT8;


/*****************************************************************************
 ö����    : GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   TBF�쳣�ͷ�ԭ��
*****************************************************************************/
enum GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM
{
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_OTHERS                    = 0,   /* ���� */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3162_TIMEOUT             = 1,   /* T3162��ʱ */  
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3164_TIMEOUT             = 2,   /* T3164��ʱ */  
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3166_TIMEOUT             = 3,   /* T3166��ʱ */ 
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3168_TIMEOUT             = 4,   /* T3168��ʱ */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3146_OR_T3170_TIMEOUT    = 5,   /* T3146/T3170��ʱ */    
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_T3186_TIMEOUT             = 6,   /* T3186��ʱ */ 
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_UL_ACK_TIMEOUT            = 7,   /* EVT_GAS_GRR_PT_WAIT_PKT_UL_ACK��ʱ */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_SINGLE_BLOCK_TIMEOUT      = 8,   /* T3168��ʱ */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_ACTIVE_PHY_FAIL           = 9,   /* ���������ʧ�� */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_GRR_PT_MPHP_PDCH_REL      = 10,  /* PDCH������ʱ����ʱ */
    GAS_OM_PKT_TBF_RELEASE_ABNORMAL                         = 11,  /* packet tbf release */
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_BUTT
};
typedef VOS_UINT8 GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   RR�����쳣����
*****************************************************************************/
enum GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM
{
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_EST   = 0,      /* ��·����ʧ�� */
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_REL   = 1,      /* ��·�쳣�ͷ� */
    
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_BUTT
};
typedef VOS_UINT32 GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM   RR�����쳣ԭ��
*****************************************************************************/
enum GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM
{
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_OTHERS                   = 0, /* ���� */                        
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_APPLY_RESOURCE_FAIL      = 1, /* ������Դʧ�� */                
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_PT_TIMEOUT               = 2, /* ������ʱ����ʱ */              
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_IMMASS_INVALID           = 3, /* ����ָ�ɷǷ� */                
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_CHANNEL_REQ_INVALID      = 4, /* ����CHANNEL REQUESTʧ�� */     
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_RA_SEND_FAIL             = 5, /* RA����ʧ�� */                  
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_BY_NETWORK           = 6, /* ���������ͷ���· */            
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_RRMM_ABORT_EXCEPTION = 7, /* �쳣�ͷ���· */                                 
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_HANDOVER_EXCEPTION   = 8, /* �쳣�ͷ���· */                                   
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_REL_RADIO_LINK_FAILURE   = 9, /* �쳣�ͷ���· */                             
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_BUTT                                      
};
typedef VOS_UINT32 GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : OM_GAS_OTA_SWITCH_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : OM -> GAS �տ���Ϣ���ÿ���
*****************************************************************************/
enum OM_GAS_OTA_SWITCH_ENUM
{
    GSM_OTA_SWITCH_OFF   = 0,     /* ֹͣ�ϱ��տ���Ϣ */
    GSM_OTA_SWITCH_ON    = 1      /* ��ʼ�ϱ��տ���Ϣ */
};
typedef VOS_UINT32   GSM_OTA_SWITCH_ENUM_UINT32;
/*****************************************************************************
 ö����    : GSM_OTA_CNF_ERRCODE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM �տ���Ϣ���ý��
*****************************************************************************/
enum GSM_OTA_CNF_ERRCODE_ENUM
{
    GSM_OTA_CNF_ERRCODE_NO    = 0,     /* �տ����óɹ� */
    GSM_OTA_CNF_ERRCODE_YES   = 1      /* �տ�����ʧ�� */
};
typedef VOS_UINT32   GSM_OTA_CNF_ERRCODE_ENUM_UINT32;
/*****************************************************************************
 ö����    : GSM_OTA_DIRECTION_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS -> OM �տ���Ϣ����
*****************************************************************************/
enum GAS_OM_OTA_CNF_RESULT_ENUM
{
    GSM_OTA_DIRECTION_UP     = 0,     /* �տ����÷���: ����(MS-->Network) */
    GSM_OTA_DIRECTION_DOWN   = 1      /* �տ����÷���: ����(Network-->MS) */
};
typedef VOS_UINT8   GSM_OTA_DIRECTION_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ı�ԭ��ö��
*****************************************************************************/
enum GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM
{
    GAS_NCELL_LIST_CHANGE_CAUSE_INDIVIDUAL_NET_CTRL       = 0, /*�����ı���������൥���·���PMO, PCCO�����*/
    GAS_NCELL_LIST_CHANGE_CAUSE_SYSTEM_INFORMATION_UPDATE = 1  /*�����ı�����ϵͳ��Ϣ���������*/
};
typedef VOS_UINT8 GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_REDIR_L2G_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ض��� L2G��ʧ��ԭ��ֵ
*****************************************************************************/
enum GAS_OM_REDIR_L2G_RESULT_ENUM
{
    GAS_OM_REDIR_L2G_RESULT_SUCC                        = 0 ,   /* �ض���ɹ� */
    GAS_OM_REDIR_L2G_RESULT_FAIL_UE_NOT_SUPPORT             ,   /* UE��֧�� GSM����Ƶ�� */
    GAS_OM_REDIR_L2G_RESULT_FAIL_LOAD_DSP                   ,   /* ����DSPʧ�� */
    GAS_OM_REDIR_L2G_RESULT_NO_SUITABLE_CELL                ,   /* ȫƵ������ϵͳ��Ϣ����Ȼû������������С�����ض���ʧ�� */
    GAS_OM_REDIR_L2G_RESULT_LRRC_STOP_REDIR                 ,   /* LRRCҪ��ֹͣ�ض��� */

    GAS_OM_REDIR_L2G_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_REDIR_L2G_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_ANR_L2G_RESULT_ENUM
 ö��˵��  : ANR L2G���˳�ԭ��ֵ
 �޸���ʷ  : 
 1.��    ��    : 2012-04-19
   ��    ��    : w00176595
   �޸�����    : �½�ö������
*****************************************************************************/
enum GAS_OM_ANR_L2G_RESULT_ENUM
{
    GAS_OM_ANR_L2G_RESULT_SUCC                        = 0 ,   /* ANR�ɹ� */
    GAS_OM_ANR_L2G_RESULT_ABNORMAL                        ,   /* Gģ��֧�ֻ���Ƶ�㲻֧�� */
    GAS_OM_ANR_L2G_PHY_START_FAIL                         ,   /* ���������ANRʧ�� */
    GAS_OM_ANR_L2G_PHY_START_TIMEOUT                      ,   /* ���������ANR��ʱ */
    GAS_OM_ANR_L2G_MEAS_RESULT_INVALID                    ,   /* �������������Ч */
    GAS_OM_ANR_L2G_BCCH_READ_FAIL                         ,   /* ϵͳ��Ϣ��ȡʧ��  */
    GAS_OM_ANR_L2G_BCCH_READ_TIMEOUT                      ,   /* ��ϵͳ��Ϣ��ʱ  */
    GAS_OM_ANR_L2G_MEAS_TIMEOUT                           ,   /* ����������ʱ */
    GAS_OM_ANR_L2G_STOP_MEAS_TIMEOUT                      ,   /* �����ֹͣ������ʱ */
    GAS_OM_ANR_L2G_STOP_BCCH_READING_TIMEOUT              ,   /* �����ֹͣ��ϵͳ��Ϣ��ʱ */

    GAS_OM_ANR_L2G_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_ANR_L2G_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_RESEL_CCO_W2G_RESULT_ENUM
 ö��˵��  : W2G Resel/CCO���˳�ԭ��ֵ
 �޸���ʷ  : 
 1.��    ��    : 2012-04-19
   ��    ��    : w00176595
   �޸�����    : �½�ö������
*****************************************************************************/
enum GAS_OM_RESEL_CCO_W2G_RESULT_ENUM
{
    GAS_OM_RESEL_CCO_W2G_RESULT_SUCC                        = 0 ,   /* Resel/CCO�ɹ� */
    GAS_OM_RESEL_CCO_W2G_RESULT_FAIL                            ,   /* Resel/CCO������ʧ�� */
    GAS_OM_RESEL_CCO_W2G_RESULT_NOT_EPLMN                       ,   /* �ǵ�ЧPLMN */
    GAS_OM_RESEL_CCO_W2G_RESULT_FORBIDDEN_LAI                   ,   /* LAI���� */
    GAS_OM_RESEL_CCO_W2G_RESULT_CELL_BARRED                     ,   /* С����BAR */
    GAS_OM_RESEL_CCO_W2G_RESULT_ACCESS_NOT_PERMIT               ,   /* С�������ֹ  */
    GAS_OM_RESEL_CCO_W2G_RESULT_C1                              ,   /* C1С��0  */

    GAS_OM_RESEL_CCO_W2G_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_CCO_W2G_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM
 ö��˵��  : ������ʽ�б��ѽ��ֵ
 �޸���ʷ  : 
  1.��    ��   : 2012-05-07
    ��    ��   : s00184266
    �޸�����   : �½�ö������
  2.��    ��   : 2014��3��15��
    ��    ��   : s00184266
    �޸�ԭ��   : multi-mode evolution phase I, ����WRRC��ص��б��ѽ��ֵ
*****************************************************************************/
enum GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM
{
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_SUCC                        = 0x0 ,       /* �б��ѳɹ� */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_FULL_LIST_CNF_ERROR           ,       /* �б��� GSMɨƵ���� */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_FULL_LIST_CNF_TIMEOUT         ,       /* �б��� GSMɨƵ�ظ���ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_START_FAIL                   ,       /* �б��� WCDMA����WRRCʧ�� */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_START_TIMEOUT                ,       /* �б��� WCDMA����WRRC��ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_IND_TIMEOUT                  ,       /* �б��� WCDMA�ȴ������ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_WRRC_STOP_TIMEOUT                 ,       /* �б��� WCDMAͣWRRC��ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_START_FAIL                   ,       /* �б��� LTE����LRRCʧ�� */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_START_TIMEOUT                ,       /* �б��� LTE����LRRC��ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_START_FAIL                    ,       /* �б��� WCDMA/LTE����GPHYʧ�� */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_START_TIMEOUT                 ,       /* �б��� WCDMA/LTE����GPHY��ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_IND_TIMEOUT                  ,       /* �б��� LTE�ȴ������ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_STOP_TIMEOUT                  ,       /* �б��� WCDMA/LTEͣGPHY��ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_LRRC_STOP_TIMEOUT                 ,       /* �б��� LTEͣLRRC��ʱ */

    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_FREQ_SEARCH_TIMEOUT               ,       /* �б��� GSMɨƵ��ʱ */
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_MPH_FULL_LIST_STOP_TIMEOUT        ,       /* �б��� GSMֹͣɨƵ��ʱ */

    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_NO_RF,

    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : GAS_OM_BG_PLMN_SEARCH_LTE_EVENT_ENUM
 ö��˵��  : ������LTE���ֵ
 �޸���ʷ  : 
 1.��    ��    : 2012-05-14
   ��    ��    : w00146666
   �޸�����    : �½�ö������
*****************************************************************************/
enum GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_ENUM
{
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_START_TIMEOUT     = 0x0 ,       /* ������LTE */
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_RESUME_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_GPHY_START_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_SEARCH_IND_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_GPHY_STOP_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_STOP_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_LRRC_SUSPEND_TIMEOUT,
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_GPHY_CNF_TYPE_DISMATCH,
    
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_BUTT
};

typedef VOS_UINT8 GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_ENUM_UINT8;


/*****************************************************************************
 ö����    : GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ��ѡ����ʧ�ܵ�ԭ��ֵ��ʧ�ܵ�С��Ҫ����ѡ�����б���ɾ��
*****************************************************************************/
enum GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ENUM
{
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_RAT_NOT_SUPPORTED                      = 0 ,   /* ���뼼����֧�� */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ARFCN_NOT_SUPPORTED                    ,       /* Ƶ�㲻֧�� */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ARFCN_DELETED                          ,       /* Ƶ�㱻ɾ�� */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_NCELL_DELETED                          ,       /* С����ɾ�� */
    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_NOT_PASS_EVALUATION                    ,       /* ��������ѡ���� */

    GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_BUTT
};
typedef VOS_UINT8 GAS_OM_RESEL_EVALUATE_RMV_CELL_CAUSE_ENUM_UINT8;

/* Added by yangsicong for probe�ӿ��¿���, 2012-10-30, begin */
/*****************************************************************************
 ö����    : GAS_ROAD_TEST_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Ϊ·�����PROBE�ṩ����Ϣ����
*****************************************************************************/
enum GAS_ROAD_TEST_INFO_TYPE_ENUM
{
    GAS_ROAD_TEST_INFO_TYPE_MEAS_RESULT         =   0x00,   /* ������� */
    GAS_ROAD_TEST_INFO_TYPE_SCELL_PARA                  ,   /* ����С������ */
    GAS_ROAD_TEST_INFO_TYPE_SCELL_DCH_CHAN_PARA         ,   /* DCH���� */
    GAS_ROAD_TEST_INFO_TYPE_BUTT  
};
typedef VOS_UINT16 GAS_ROAD_TEST_INFO_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : GAS_OM_GSM_RUNNING_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Ϊ·�����PROBE�ṩ�ĵ�ǰ��GSM����״̬( ���л����� )����
*****************************************************************************/
enum GAS_OM_GSM_RUNNING_MODE_ENUM
{
    GAS_OM_GSM_RUNNING_MODE_IDLE              =   0x01,   /* GSM ����ģʽ */
    GAS_OM_GSM_RUNNING_MODE_DEDICATE                  ,   /* GSM ר��ģʽ */
    GAS_OM_GSM_RUNNING_MODE_BUTT  
};
typedef VOS_UINT16 GAS_OM_GSM_RUNNING_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : GAS_OM_GPRS_RUNNING_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Ϊ·�����PROBE�ṩ�ĵ�ǰ��GPRS����״̬( ���л����� )����
*****************************************************************************/
enum GAS_OM_GPRS_RUNNING_MODE_ENUM
{
    GAS_OM_GPRS_RUNNING_MODE_IDLE              =   0x01,  /* GPRS ����ģʽ */
    GAS_OM_GPRS_RUNNING_MODE_DATA_TRANSFER             ,  /* GPRS ����ģʽ */
    GAS_OM_GPRS_RUNNING_MODE_BUTT  
};
typedef VOS_UINT16 GAS_OM_GPRS_RUNNING_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : GAS_OM_RR_CIPHER_ALGORITHM_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CS������㷨ö��
*****************************************************************************/
enum GAS_OM_RR_CIPHER_ALGORITHM_ENUM
{
    GAS_OM_RR_CIPHER_ALGORITHM_NONE             =   0,
    GAS_OM_RR_CIPHER_ALGORITHM_A51              =   1,
    GAS_OM_RR_CIPHER_ALGORITHM_A52              =   2,
    GAS_OM_RR_CIPHER_ALGORITHM_A53              =   3,
    GAS_OM_RR_CIPHER_ALGORITHM_A54              =   4,
    GAS_OM_RR_CIPHER_ALGORITHM_A55              =   5,
    GAS_OM_RR_CIPHER_ALGORITHM_A56              =   6,
    GAS_OM_RR_CIPHER_ALGORITHM_A57              =   7,

    GAS_OM_RR_CIPHER_ALGORITHM_BUTT
};
typedef VOS_UINT16 GAS_OM_RR_CIPHER_ALGORITHM_ENUM_UINT16;

/*****************************************************************************
 ö����    : GAS_OM_NETWORK_CONTROL_ORDER_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������ģʽö��
*****************************************************************************/
enum GAS_OM_NETWORK_CONTROL_ORDER_ENUM
{
    GAS_OM_NETWORK_CONTROL_ORDER_NC0              =   0,
    GAS_OM_NETWORK_CONTROL_ORDER_NC1              =   1,
    GAS_OM_NETWORK_CONTROL_ORDER_NC2              =   2,

    GAS_OM_NETWORK_CONTROL_ORDER_BUTT
};
typedef VOS_UINT16 GAS_OM_NETWORK_CONTROL_ORDER_ENUM_UINT16;

/*****************************************************************************
 ö����    : GAS_OM_VOICE_CHANNEL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����������ʹ�õ��ŵ�����
*****************************************************************************/
enum GAS_OM_VOICE_CHANNEL_TYPE_ENUM
{
    GAS_OM_VOICE_CHANNEL_TYPE_TCH_F         = 1,             /* TCH_F */
    GAS_OM_VOICE_CHANNEL_TYPE_TCH_H            ,             /* TCH_H  */
    GAS_OM_VOICE_CHANNEL_TYPE_SDCCH_4          ,             /* SDCCH_4  */
    GAS_OM_VOICE_CHANNEL_TYPE_SDCCH_8          ,             /* SDCCH_8 */
    
    GAS_OM_VOICE_CHANNEL_TYPE_BUTT
};
typedef VOS_UINT16  GAS_OM_VOICE_CHANNEL_TYPE_ENUM_UINT16;


/*****************************************************************************
 ö����    : GAS_OM_SPECCH_CODEC_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������뷽ʽ
*****************************************************************************/
enum GAS_OM_SPECCH_CODEC_ENUM
{
    GAS_OM_SPECCH_CODEC_ONLY,            /* ������ģʽ*/
    GAS_OM_SPECCH_CODEC_FR,             /* Full Rate */
    GAS_OM_SPECCH_CODEC_EFR,            /* Enhanced Full Rate  */
    GAS_OM_SPECCH_CODEC_AFS,            /* Enhanced Full Rate  */
    GAS_OM_SPECCH_CODEC_CSD_2400,
    GAS_OM_SPECCH_CODEC_CSD_4800,
    GAS_OM_SPECCH_CODEC_CSD_9600,
    GAS_OM_SPECCH_CODEC_CSD_14400,
    GAS_OM_SPECCH_CODEC_HR,             /* half Rate */
    GAS_OM_SPECCH_CODEC_AHR,            /* half Rate */
    GAS_OM_SPECCH_CODEC_H24,            /* Adaptive Multi-Rate */
    GAS_OM_SPECCH_CODEC_H48,            /* Adaptive Multi-Rate */
    GAS_OM_SPECCH_CODEC_WFS,            /* Adaptive Multi-Rate,WFSҵ�� */
    
    GAS_OM_SPECCH_CODEC_BUTT
};
typedef VOS_UINT16  GAS_OM_SPECCH_CODEC_ENUM_UINT16;


/* Added by yangsicong for probe�ӿ��¿���, 2012-10-30, end */


#if ( FEATURE_ON == FEATURE_DSDS )
/*******************************************************************************
 ö����    : GAS_OM_TASK_STATUS_ENUM_UINT16
 �ṹ˵��  : OM�����������Դ״̬
 1.��    ��   : 2014��02��12��
   ��    ��   : l67237
   �޸�����   : Added for GAS DSDS
*******************************************************************************/
enum GAS_OM_TASK_STATUS_ENUM
{
    GAS_OM_TASK_STATUS_NONE                             = 0,                    /* ��״̬ */
    GAS_OM_TASK_STATUS_APPLYING                         = 1,                    /* ������Դ���������� */
    GAS_OM_TASK_STATUS_USING                            = 2,                    /* ������Դ������ɣ�ʹ���� */
    GAS_OM_TASK_STATUS_BUTT
};
typedef VOS_UINT16 GAS_OM_TASK_STATUS_ENUM_UINT16;
#endif

/*****************************************************************************
 ö �� ��  : GAS_OM_SEARCH_PROC_ENUM
 ö��˵��  : ��������ö��
 �޸���ʷ  :
  1.��  ��   : 2015��9��10��
    ��  ��   : s00184266
    �޸����� : ������ö��

*****************************************************************************/
enum GAS_OM_SEARCH_PROC_ENUM
{
    GAS_OM_SEARCH_PROC_L_REDIR_G_SPEC_SRCH              = 0,
    GAS_OM_SEARCH_PROC_L_REDIR_G_HISTORY_SRCH              ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_CLOUD_FREQ_SRCH           ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_OPERATE_CUSTOM_FREQ_SRCH  ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_HISTORY_FREQ_BAND_SRCH    ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_PRESET_FREQ_BAND_SRCH     ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_PRESET_BAND_SRCH          ,
    GAS_OM_SEARCH_PROC_L_REDIR_G_FULL_LIST_SRCH            ,

    GAS_OM_SEARCH_PROC_SPEC_SRCH_HISOTRY_FREQ_SRCH         ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_CLOUD_FREQ_SRCH           ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_OPERATE_CUSTOM_FREQ_SRCH  ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_HISTORY_FREQ_BAND_SRCH    ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_PRESET_FREQ_BAND_SRCH     ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_PRESET_BAND_SRCH          ,
    GAS_OM_SEARCH_PROC_SPEC_SRCH_FULL_LIST_SRCH            ,

    GAS_OM_SEARCH_PROC_GOOS_SRCH_HISTORY_FREQ_SRCH         ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_CLOUD_FREQ_SRCH           ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_OPERATE_CUSTOM_FREQ_SRCH  ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_HISTORY_FREQ_BAND_SRCH    ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_PRESET_FREQ_BAND_SRCH     ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_PRESET_BAND_SRCH          ,
    GAS_OM_SEARCH_PROC_GOOS_SRCH_FULL_LIST_SRCH            ,

    GAS_OM_SEARCH_PROC_BUTT
};
typedef VOS_UINT8 GAS_OM_SEARCH_PROC_ENUM_UINT8;

/*****************************************************************************
 ö �� ��  : GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM
 ö��˵��  : ���̹���Ƶ���б���
 �޸���ʷ  :
  1.��  ��   : 2015��9��10��
    ��  ��   : s00184266
    �޸����� : ������ö��
  2.��    ��   : 2015��12��16��
    ��    ��   : s00184266
    �޸�ԭ��   : dts2015121505454, ������ȡCSSƵ����Ϣʧ�ܵ�ö��

*****************************************************************************/
enum GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM
{
    GAS_OM_SEARCH_PROC_BUILD_RESULT_SUCC                = 0,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_NV_DISABLE             ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_BUILD_NULL_FREQ_LIST   ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_FILTER_ALL_FREQ_LIST   ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_BUILD_NULL_BAND_LIST   ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_NULL_FREQ_IN_BAND      ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_ALL_BAND_HAD_SRCHED    ,
    GAS_OM_SEARCH_PROC_BUILD_RESULT_ERROR_DURING_GET_CSS_BAND,

    GAS_OM_SEARCH_PROC_BUILD_RESULT_BUTT
};
typedef VOS_UINT8 GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö �� ��  : GAS_OM_CSS_INTERFACE_NAME_ENUM
 ö��˵��  : GAS����CSS�ṩ���ƶ˺�����ö��
 �޸���ʷ  :
  1.��  ��   : 2015��11��5��
    ��  ��   : s00184266
    �޸����� : ������ö��

*****************************************************************************/
enum GAS_OM_CSS_INTERFACE_NAME_ENUM
{
    GAS_OM_CSS_INTERFACE_NAME_IS_MCC_FREQ_EXIST         = 0,
    GAS_OM_CSS_INTERFACE_NAME_GET_PREFER_FREQ_INFO         ,
    GAS_OM_CSS_INTERFACE_NAME_GET_PREFER_BAND_INFO         ,
    GAS_OM_CSS_INTERFACE_NAME_INPUT_PLMN_INFO              ,
    
    GAS_OM_CSS_INTERFACE_NAME_BUTT
};
typedef VOS_UINT32 GAS_OM_CSS_INTERFACE_NAME_ENUM_UINT32;


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
 �� �� ��  : DIAG_GAS_MSG_COMM_HEAD_ST
 �ṹ����  : DIAG��Ϣ����ͷ
 �޸���ʷ      :
  1.��    ��   : 2016��6��23��
    ��    ��   : ���� h00166210
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */

    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;
} DIAG_GAS_MSG_COMM_HEAD_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_INFO_REQ_ST
 �ṹ����  : OM��Ϣ��ѯ�Ľṹ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          usReportPeriod;   /* ��λ: s */
    VOS_UINT16                          usReserved;
} OM_GAS_INFO_REQ_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_INFO_CNF_ST
 �ṹ����  : GAS�ظ���Ϣȷ�ϵĽṹ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT16                          usResult;
    VOS_UINT16                          usReserved;
    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
} GAS_OM_INFO_CNF_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_IND_STRUCT
 Э����  :
 ASN.1���� :
 �ṹ˵��  :Э��ջ��OM�¼��ϱ��ṹ
*****************************************************************************/
typedef struct
{
    OM_GAS_MSG_ID_ENUM_UINT16           usEventId;          /*_H2ASN_MsgChoice_Export OM_GAS_MSG_ID_ENUM_UINT16*/
    VOS_UINT16                          usReserved;
    VOS_UINT32                          ulModuleId;         /*����ģ��PID �����߸���PID����������Ϣ*/
    VOS_UINT8                           aucData[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_GAS_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}GAS_OM_EVENT_IND_ST;
/*****************************************************************************
 �� �� ��  : GAS_OM_CELL_BASIC_INFO_ST
 �ṹ����  : С��������Ϣ�Ľṹ�塣

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                       usArfcn;
    VOS_UINT8                        ucNcc;
    VOS_UINT8                        ucBcc;
    GAS_OM_GSM_BAND_ENUM_UINT16      enBand;
    VOS_INT16                        sRxLev;
    VOS_INT16                        sC1;
    VOS_INT16                        sC2;
    VOS_INT16                        sC31;
    VOS_INT16                        sC32;
    VOS_UINT16                       usLac;
    VOS_UINT8                        ucRac; 
    VOS_UINT8                        ucPriorityClass; 
    VOS_UINT16                       usTimerStatus;          /* ��ʱ��״̬,0Ϊδ������1Ϊ���� */
    VOS_UINT16                       usRsv;
} GAS_OM_CELL_BASIC_INFO_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_CELL_INFO_REQ_ST
 �ṹ����  : OM ������ С����Ϣ��ѯ����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_CELL_INFO_REQ_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_CELL_INFO_CNF_ST
 �ṹ����  : GAS��С����Ϣ��ѯ�����ȷ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_CELL_INFO_CNF_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_CELL_COMM_INFO_ST
 �ṹ����  : GAS��OM�ϱ�����С����һ����Ϣ��

 �޸���ʷ      :
  1.��    ��   : 2008��10��13��
    ��    ��   : ���¹�  00126771
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    NAS_GMM_STATE_ENUM_UINT8                enGmmState;
    VOS_UINT8                               ucCRH;
    VOS_UINT8                               ucRecentReselection;
    VOS_UINT8                               ucPbcchFlag;
    VOS_UINT8                               ucEgprsFlag;
    VOS_UINT8                               astRsv[3];    /*����λ*/
}GAS_OM_CELL_COMM_INFO_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_CELL_INFO_IND_ST
 �ṹ����  : GAS��OM�ϱ�����С������ǿ������Ϣ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16          enReportType;
    VOS_UINT16                              us2GNCellNum;
    GAS_OM_CELL_COMM_INFO_ST                stCommInfo;
    GAS_OM_CELL_BASIC_INFO_ST               stSCellInfo;
    GAS_OM_CELL_BASIC_INFO_ST               astNCellInfo[6];
} GAS_OM_CELL_INFO_IND_ST;

/*****************************************************************************
 �� �� ��  : GAS_MSP_CELL_INFO_IND_ST
 �ṹ����  : GAS��MSP�ϱ�����С������ǿ������Ϣ��

 �޸���ʷ      :
  1.��    ��   : 2015��9��18��
    ��    ��   : ���� h00166210
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          us2GNCellNum;
    GAS_OM_CELL_COMM_INFO_ST            stCommInfo;
    GAS_OM_CELL_BASIC_INFO_ST           stSCellInfo;
    GAS_OM_CELL_BASIC_INFO_ST           astNCellInfo[6];
} GAS_MSP_CELL_INFO_IND_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_DCH_QUALITY_ST
 �ṹ����  : GAS��OM�ϱ�DCH�ŵ����ŵ�����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_INT16         sRxlevFull;
    VOS_INT16         sRxlevSub;
    VOS_UINT16        usNumBitMeasFull;
    VOS_UINT16        usNumBitMeasSub;
    VOS_UINT16        usNumErrBitFull;
    VOS_UINT16        usNumErrBitSub;
    VOS_UINT16        usBERFull;
    VOS_UINT16        usBERSub;
    VOS_UINT16        usRxqualFull;
    VOS_UINT16        usRxqualSub;
} GAS_OM_DCH_QUALITY_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_PDTCH_QUALITY_ST
 �ṹ����  : GAS��OM�ϱ�PDTCH�ŵ����ŵ�����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16         usBitsErrNum;
    VOS_UINT16         usBitsTotalNum;
    VOS_UINT16         usBER;
    VOS_UINT16         usRxqual;
    VOS_UINT16         usSCellC;
    VOS_UINT16         usSignalVar;
    VOS_UINT16         ausInLevelTn[8];
} GAS_OM_PDTCH_QUALITY_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_CHANNEL_QUALITY_REQ_ST
 �ṹ����  : OM ������ �ŵ�������ѯ����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_CHANNEL_QUALITY_REQ_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_CHANNEL_QUALITY_CNF_ST
 �ṹ����  : GAS���ŵ�������ѯ�����ȷ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_CHANNEL_QUALITY_CNF_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_CHANNEL_QUALITY_IND_ST
 �ṹ����  : GAS��OM�ϱ��ŵ�����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    GAS_DCH_TYPE_ENUM_UINT16            enDchType;
    GAS_OM_DCH_QUALITY_ST               stDchQuality;
    GAS_OM_PDTCH_QUALITY_ST             stPdtchQuality;
} GAS_OM_CHANNEL_QUALITY_IND_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_3G_NCELL_INFO_ST
 �ṹ����  : GAS��OM�ϱ�3G(WCDMA)��������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                     usUARFCN;          /* Ƶ�� */
    VOS_UINT16                     usPSC;             /* ������ */

    VOS_INT16                      sRSCP;             /* RSCPֵ */
    VOS_INT16                      sEcNo;             /* EcNoֵ */
    VOS_INT16                        s3GNcellRSSI;
    VOS_INT16                        sReserved;

} GAS_OM_3G_NCELL_INFO_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_3G_NCELL_MEAS_REQ_ST
 �ṹ����  : OM ������ 3G��С��������Ϣ��ѯ����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_3G_NCELL_MEAS_REQ_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_3G_NCELL_MEAS_CNF_ST
 �ṹ����  : GAS��3G��С��������ѯ�����ȷ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_3G_NCELL_MEAS_CNF_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_3G_SETTINGS_ST
 �ṹ����  : GAS�ϱ�3G������������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��10��13��
    ��    ��   : ���¹�  00126771
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucQsearch_I;
    VOS_UINT8                               ucQsearch_C;
    VOS_UINT8                               ucQsearch_P;
    VOS_INT8                                cFDD_Qmin;
    VOS_INT16                               sFDD_Qoffset;
    VOS_UINT16                              usRsv;
}GAS_OM_3G_SETTINGS_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_3G_NCELL_MEAS_IND_ST
 �ṹ����  : GAS�ϱ�3G��С��������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          us3GNcellNum;
    GAS_OM_3G_SETTINGS_ST               st3GSettings;
    GAS_OM_3G_NCELL_INFO_ST             ast3GNcellInfo[GAS_OM_3G_NCELL_NUMBER];
} GAS_OM_3G_NCELL_MEAS_IND_ST;

/*****************************************************************************
 �� �� ��  : GAS_MSP_3G_NCELL_MEAS_IND_ST
 �ṹ����  : GAS�ϱ�3G��С��������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2015��9��18��
    ��    ��   : ���� h00166210
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          us3GNcellNum;
    GAS_OM_3G_SETTINGS_ST               st3GSettings;
    GAS_OM_3G_NCELL_INFO_ST             ast3GNcellInfo[GAS_OM_3G_NCELL_NUMBER];
} GAS_MSP_3G_NCELL_MEAS_IND_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_GSM_INFO_REQ_ST
 �ṹ����  : OM ������ GSM ��Ϣ��ѯ����

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_GSM_INFO_REQ_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_GSM_INFO_CNF_ST
 �ṹ����  : GAS�� GSM ��Ϣ��ѯ�����ȷ��

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_GSM_INFO_CNF_ST;

/*****************************************************************************
 �� �� ��  : GAS_GSM_INFO_ST
 �ṹ����  : GSM������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT32                             ulMcc;           /* �ƶ������� */
    VOS_UINT32                             ulMnc;           /* �ƶ������� */
    VOS_UINT16                             usLAC;           /* λ������ */
    VOS_UINT16                             usCellId;        /* С�� ID */
    VOS_UINT16                             usBcchArfcn;     /* �㲥Ƶ��� */
    GAS_OM_STATE_ENUM_UINT16               enGasState;      /* GAS״̬ */
}GAS_GSM_INFO_ST;

/*****************************************************************************
 �� �� ��  : GAS_TBF_INFO_ST
 �ṹ����  : GRPS�� TBF ��Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RLC_MODE_ENUM_UINT8             enRlcMode;       /* RLCģʽ */
    GAS_OM_MAC_MODE_ENUM_UINT8             enMacMode;       /* MACģʽ */
    VOS_UINT8                              ucTsNum;         /* TBF����ʱ϶��: [0,8] */
    VOS_UINT8                              ucTsMask;        /* ʱ϶���� */
                                                            /* 0xf0��ʾ����ʱ϶ 0~3 */
    
    GAS_OM_CS_TYPE_ENUM_UINT8              enCS;            /* ���뷽ʽ */
    VOS_UINT8                              ucRsv[3];        /* ���� */
}GAS_TBF_INFO_ST;

/*****************************************************************************
 �� �� ��  : GAS_GPRS_INFO_ST
 �ṹ����  : �ϱ���OM��GRPS��Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucGprsSupport;   /* GRPS �Ƿ�֧��: 0-��֧��, 1-֧�� */
    VOS_UINT8                              ucEgprsSupport;  /* EGPRS �Ƿ�֧��: 0-��֧��, 1-֧�� */
    VOS_UINT8                              ucRAC;           /* ·������ */
    VOS_UINT8                              ucPbcchPresent;  /* PBCCH�Ƿ����: 0-������, 1-����*/

    VOS_UINT8                              ucUlTbfPresent;  /* ����TBF�Ƿ����: 0-������, 1-����*/
    VOS_UINT8                              ucDlTbfPresent;  /* ����TBF�Ƿ����: 0-������, 1-����*/
    VOS_UINT16                             usReserved;      /* ���� */
    
    GAS_TBF_INFO_ST                        stUlTbfInfo;     /* ����TBF��Ϣ */
    GAS_TBF_INFO_ST                        stDlTbfInfo;     /* ����TBF��Ϣ */
}GAS_GPRS_INFO_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_GSM_INFO_IND_ST
 �ṹ����  : GAS�ϱ� GSM/GPRS ��Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��19��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16         enReportType;
    VOS_UINT16                             usReserved;
    GAS_GSM_INFO_ST                        stGsmInfo;       /* GSM��Ϣ */
    GAS_GPRS_INFO_ST                       stGprsInfo;      /* GPRS��Ϣ */
}GAS_OM_GSM_INFO_IND_ST;





/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_LINK_FAILURE_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8              ucLinkInitVaule;     /* ������·��ʼֵ����Χ[4,64] */
    VOS_UINT8              aucReserved[3];      /* ���� */
} GAS_OM_EVENT_GSM_LINK_FAILURE_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_DOWNLINK_FAILURE_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8              ucDscInitValue;       /* ������·��������ʼֵ����Χ[10,45] */
    VOS_UINT8              aucReserved[3];
} GAS_OM_EVENT_GSM_DOWNLINK_FAILURE_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_RESELECT_START_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RESEL_TYPE_ENUM_UINT8      enReselType;    /* ��ѡ���� */
    GAS_OM_RESEL_CAUSE_ENUM_UINT8     enReselCause;   /* ��ѡԭ�� */
    VOS_UINT8                         aucRsv[2];      /* ���� */
    VOS_UINT16                        usTargetArfcn;  /* Ŀ��Ƶ�� */
    VOS_UINT8                         ucNcc;          /* ����ɫ�� */
    VOS_UINT8                         ucBcc;          /* ��վɫ�� */
} GAS_OM_EVENT_GSM_RESELECT_START_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_RESELECT_END_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucResult;        /* ִ�н�� */
    VOS_UINT8                           aucReserved[3];  /* ���� */
} GAS_OM_EVENT_GSM_RESELECT_END_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                        usTargetArfcn;  /* Ŀ��Ƶ�� */
    VOS_UINT8                         ucNcc;          /* ����ɫ�� */
    VOS_UINT8                         ucBcc;          /* ��վɫ�� */
} GAS_OM_EVENT_GSM_CAMP_ATTEMPT_START_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RESULT_ENUM_UINT8          enResult;        /* ִ�н����0-ʧ�ܣ�1-�ɹ� */
    VOS_UINT8                         aucReserved[3];  /* ���� */
} GAS_OM_EVENT_GSM_CAMP_ATTEMPT_END_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RESEL_TYPE_ENUM_UINT8      enReselType;   /* ��ѡ���� */  
    VOS_UINT8                         aucRsv[3];     /* ���� */
    VOS_UINT16                        usUArfcn;      /* Ƶ��� */
    VOS_UINT16                        usPSC;         /* ������ */
} GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_START_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RESULT_ENUM_UINT8          enResult;        /* ִ�н����0-ʧ�ܣ�1-�ɹ� */
    VOS_UINT8                         aucReserved[3];  /* ���� */
} GAS_OM_EVENT_GSM_TO_WCDMA_RESELECT_END_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2010��4��15��
    ��    ��   : h00129908
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                         aucReserve1[4];                         /* 4�ֽڶ��룬���� */
} GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_START_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2010��4��15��
    ��    ��   : h00129908
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RESULT_ENUM_UINT8          enResult;        /* ִ�н����0-ʧ�ܣ�1-�ɹ� */
    VOS_UINT8                         aucReserved[3];  /* ���� */
} GAS_OM_EVENT_GSM_TO_WCDMA_AFTER_CHAN_REL_SELECT_END_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_TBF_ABNORMAL_REL_CAUSE_ENUM_UINT8    enReleaseCause;  /* TBF�쳣�ͷ�ԭ�� */
    VOS_UINT8                                   aucReserved[3];  /* ���� */
} GAS_OM_EVENT_GPRS_TBF_ABNORMAL_RELEASE_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_RR_CONNECTION_ABNORMAL_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2009��4��21��
    ��    ��   : yaoqinbo
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_RR_CONNECTION_ABNORMAL_TYPE_ENUM_UINT32     enAbnormalType;  /* RR�����쳣���� */
    GAS_OM_RR_CONNECTION_ABNORMAL_CAUSE_ENUM_UINT32    enAbnormlCause;  /* RR�����쳣ԭ�� */
} GAS_OM_EVENT_RR_CONNECTION_ABNORMAL_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_GPRS_INVALID_ASSIGN_ST
 �ṹ����  : GAS��OM�ϱ��¼�������

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulInvalidCause;  /* �쳣ԭ�� */
} GAS_OM_EVENT_GPRS_INVALID_ASSIGN_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_OTA_REQ_STRUCT
 �ṹ����  : OM��GAS���͵Ŀտ�������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT32                          ulOnOff;                                /* 0 - ֹͣ�ϱ� 1 - ��ʼ�ϱ� */
}OM_GAS_OTA_REQ_STRUCT;

/*****************************************************************************
 �� �� ��  : GAS_OM_OTA_CNF_STRUCT
 �ṹ����  : GAS��OM���͵Ŀտ�����ȷ����Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT32                          ulErrCode;
}GAS_OM_OTA_CNF_STRUCT;

/*****************************************************************************
 �� �� ��  : OM_GAS_SPECIFIC_FREQ_CAMP_REQ_ST
 �ṹ����  : OM��GAS���͵�ָ��Ƶ��������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    VOS_UINT16                          usFreqInfo;                             /* Ƶ����Ϣ */
    VOS_UINT16                          usReserved;                             /* ���� */
}OM_GAS_SPECIFIC_FREQ_CAMP_REQ_ST;

typedef GAS_OM_OTA_CNF_STRUCT  GAS_OM_SPECIFIC_FREQ_CAMP_CNF_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_TIMER_ACTION_ST
 Description    : GAS��ʱ���¼��ϱ�
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2008��11��05��
    ��    ��    :  ���¹� 00126771
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimerName;
    VOS_UINT32                          ulStartOrStop;
    VOS_UINT32                          ulLength;
}GAS_OM_EVENT_TIMER_ACTION_ST;

typedef struct
{
    VOS_UINT32    ulOutofServiceCause;  /* out_of_serviceԭ�� */
}GAS_OM_EVENT_OUT_OF_SERVICE_ST;


/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_2G_NCELL_LIST_CHANGE_ST
 Description    : 2G �����ı�֪ͨ�ṹ��
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2010��02��21��
    ��    ��    : ���� 00146666
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM_UINT8 en2GNCellListChangeCause;  /*2G�����ı�ԭ��*/
    VOS_UINT8                                 aucReserved[3];           /* ���� */
}GAS_OM_EVENT_GSM_2G_NCELL_LIST_CHANGE_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_3G_NCELL_LIST_CHANGE_ST
 Description    : 2G �����ı�֪ͨ�ṹ��
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2010��02��21��
    ��    ��    : ���� 00146666
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_OM_NCELL_LIST_CHANGE_CAUSE_ENUM_UINT8 en3GNCellListChangeCause;     /*3G�����ı�ԭ��*/
    VOS_UINT8                                 aucReserved[3];               /* ���� */
}GAS_OM_EVENT_GSM_3G_NCELL_LIST_CHANGE_ST;


/*****************************************************************************
 ö����    : OM_GAS_FREQ_MEAS_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : GAS����Ƶ������
*****************************************************************************/
enum OM_GAS_FREQ_MEAS_TYPE_ENUM
{
    GAS_OM_FREQ_MEAS_TYPE_STORE_LIST   = 0,
    GAS_OM_FREQ_MEAS_TYPE_FULL_LIST    = 1,
    GAS_OM_FREQ_MEAS_TYPE_BUTT
};
typedef VOS_UINT8 OM_GAS_FREQ_MEAS_TYPE_ENUM_UINT8;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_STs
 Description    :
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2010��12��21��
    ��    ��    : ���� 00146666
    �޸�����    : �����ṹ��
  2.��    ��    : 2014��05��16��
    ��    ��    : q00261930
    �޸�����    : ����ΪGAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_ST

*****************************************************************************/
typedef struct
{
    OM_GAS_FREQ_MEAS_TYPE_ENUM_UINT8       enFreqMeasType;       /* Ƶ���������(��ʷƵ���ѣ�ȫƵ����)*/
    VOS_UINT8                              aucReserved;          /* ���� */
    VOS_UINT16                             usFreqNum;            /* Ƶ��������ܸ��� */
}GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END_ST
 Description    :
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2010��12��21��
    ��    ��    : ���� 00146666
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                             usQualFreqNum;           /* ����������Ƶ����� */
    VOS_UINT8                              aucReserved[2];          /* ���� */
}GAS_OM_EVENT_X_BG_SEARCH_G_FREQ_MEAS_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_INIT_WEAK_SIGNAL_ST
 Description    : ������ʼ�������ź��¼�����ʱ�ϱ�OM�¼��Ľṹ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��02��25��
    ��    ��    : L00167020
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_MNTN_INIT_WEAK_SIGNAL_EVT_STRU         stInitWeakSignal;   /*����������ϱ�3�����ź��¼��������Ϣ*/
    
}GAS_OM_EVENT_INIT_WEAK_SIGNAL_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_ST
 Description    : ��ǰ���ӷ��������ź���Ϣ�ϱ�OM�¼��Ľṹ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��02��25��
    ��    ��    : L00167020
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_MNTN_WEAK_SIGNAL_INFO_STRU      stCurWeakSignalInfo;    /*ÿ���ӷ������źż������Ϣ*/
    
}GAS_OM_EVENT_PERIOD_WEAK_SIGNAL_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_WEAK_SIGNAL_LIST_ST
 Description    : ÿ30�����������ϱ����ź�ʱ�ϱ�OM���¼��ṹ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��02��25��
    ��    ��    : L00167020
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_MNTN_PERIOD_WEAK_SIGNAL_LIST_EVT_STRU    stPeriodWeakSignalList;  /*30����ÿ���ӷ��������źż������Ϣ*/

}GAS_OM_EVENT_WEAK_SIGNAL_LIST_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_RCV_SI_ON_PCH_STRU
 Description    : ��PCH�ŵ����յ�ϵͳ��Ϣ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��02��25��
    ��    ��    : L00167020
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usSiType;        /* ϵͳ��Ϣ���� */
    VOS_UINT16 usChanType;      /* �߼��ŵ����� */
}GAS_OM_EVENT_RCV_SI_ON_PCH_STRU;

/*****************************************************************************
 �� �� ��  : OM_GAS_LTE_NCELL_MEAS_REQ_ST
 �ṹ����  : OM ������ LTE��С��������Ϣ��ѯ����

 �޸���ʷ      :
  1.��    ��   : 2011��03��21��
    ��    ��   : g00149376
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef OM_GAS_INFO_REQ_ST  OM_GAS_LTE_NCELL_MEAS_REQ_ST;

/*****************************************************************************
 �� �� ��  : OM_GAS_LTE_NCELL_MEAS_CNF_ST
 �ṹ����  : GAS��LTE��С��������ѯ�����ȷ��

 �޸���ʷ      :
  1.��    ��   : 2011��03��21��
    ��    ��   : g00149376
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef GAS_OM_INFO_CNF_ST  GAS_OM_LTE_NCELL_MEAS_CNF_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_LTE_SETTINGS_ST
 �ṹ����  : GAS�ϱ�LTE������������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2011��03��21��
    ��    ��   : g00149376
    �޸�����   : �����ɺ���,for V7R1
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucLteQsearchP;      /* QSearchP */
    VOS_UINT8                               ucLteQsearchC;      /* QSearchC */
    VOS_UINT8                               ucThreshPriSearch;  /* ���ȼ����� */
    VOS_UINT8                               aucRsv[1];          /* ����λ */
}GAS_OM_LTE_SETTINGS_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_LTE_NCELL_INFO_ST
 �ṹ����  : GAS��OM�ϱ�LTE��������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2011��03��21��
    ��    ��   : g00149376
    �޸�����   : �����ɺ���,for V7R1
*****************************************************************************/
typedef struct
{
    VOS_UINT16                     usArfcn;            /* Ƶ�� */
    VOS_UINT16                     usArfcnPri;         /* Ƶ�����ȼ� */
    VOS_UINT16                     usCellId;           /* С��id */
    VOS_INT16                      sRsrp;              /* RSRP����ֵ,ȡֵ��Χ[-141*8,-44*8]�� ��λ:dBm������ 1/8  */
    VOS_INT16                      sRsrq;              /* RSRQ����ֵ ,ȡֵ��Χ[-40*4��-6*4]�� ��λ:dB�� ���� 1/8  */
    VOS_INT16                      sRssi;              /* RSSI����ֵ ,ȡֵ��Χ[-110*8,-20*8], ��λ:dBm������ 1/8  */
} GAS_OM_LTE_NCELL_INFO_ST;


/*****************************************************************************
 �� �� ��  : GAS_OM_LTE_NCELL_MEAS_IND_ST
 �ṹ����  : GAS�ϱ�LTE��С��������Ϣ

 �޸���ʷ      :
 1.��    ��   : 2011��03��21��
    ��    ��   : g00149376
    �޸�����   : �����ɺ���,for V7R1
*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          usLteNcellNum;
    GAS_OM_LTE_SETTINGS_ST              stLteSettings;
    GAS_OM_LTE_NCELL_INFO_ST            astLteNcellInfo[GAS_OM_MAX_LTE_NCELL_NUM];
} GAS_OM_LTE_NCELL_MEAS_IND_ST;

/*****************************************************************************
 �� �� ��  : GAS_MSP_LTE_NCELL_MEAS_IND_ST
 �ṹ����  : GAS�ϱ�LTE��С��������Ϣ

 �޸���ʷ      :
 1.��    ��    : 2015��09��18��
    ��    ��   : h00166210
    �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReserved;

    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
    VOS_UINT16                          usLteNcellNum;
    GAS_OM_LTE_SETTINGS_ST              stLteSettings;
    GAS_OM_LTE_NCELL_INFO_ST            astLteNcellInfo[GAS_OM_MAX_LTE_NCELL_NUM];
} GAS_MSP_LTE_NCELL_MEAS_IND_ST;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_RESEL_START_ST
 Description    : GAS �� OM �ϱ� G �� L ��ѡ��ʼ, Я��Ŀ��С����Ϣ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    /* Ŀ��С�� Ƶ�� */
    VOS_UINT16  usEArfcn;

    /* Ŀ��С�� С�� ID */    
    VOS_UINT16  usCellId;

    /* Ŀ��С���� ������� */
    VOS_INT16   sRsrp;
    VOS_INT16   sRsrq;
    VOS_INT16   sRssi;
    VOS_UINT8   aucRsv[2];
}GAS_OM_EVENT_GSM_TO_LTE_RESEL_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_RESEL_END_ST
 Description    : GAS �� OM �ϱ� G �� L ��ѡ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulGLReselRlt;
}GAS_OM_EVENT_GSM_TO_LTE_RESEL_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_RESEL_START_ST
 Description    : GAS �� OM �ϱ� L �� G ��ѡ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMNɫ��  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) ��վɫ��  */
}GAS_OM_EVENT_LTE_TO_GSM_RESEL_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_RESEL_END_ST
 Description    : GAS �� OM �ϱ� L �� G ��ѡ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulLGReselRlt;
}GAS_OM_EVENT_LTE_TO_GSM_RESEL_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_CCO_START_ST
 Description    : GAS �� OM �ϱ� G �� L CCO ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usEArfcn;
    VOS_UINT16  usCellId;
}GAS_OM_EVENT_GSM_TO_LTE_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_CCO_END_ST
 Description    : GAS �� OM �ϱ� G �� L CCO ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulGLCCORlt;
}GAS_OM_EVENT_GSM_TO_LTE_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_CCO_START_ST
 Description    : GAS �� OM �ϱ� L �� G CCO ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMNɫ��  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) ��վɫ��  */
}GAS_OM_EVENT_LTE_TO_GSM_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_CCO_END_ST
 Description    : GAS �� OM �ϱ� L �� G CCO ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��03��10��
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_RESEL_RESULT_ENUM_UINT32   ulLGCCORlt;
}GAS_OM_EVENT_LTE_TO_GSM_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST
 Description    : GAS�� OM�ϱ� LRRC�ض�������� GSMС��
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��15��
    ��    ��    : s00184266
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    LRRC_GRR_BANDINDICATOR_ENUM_UINT16  enBandInd;
    VOS_UINT16                          usSysInfoPres;
    VOS_UINT8                           aucData[2];
}GAS_OM_REDIRECTED_INFO_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST
 Description    : GAS �� OM �ϱ� G �� L �ض��� ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��15��
    ��    ��    : s00184266
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   	ulRedirInfoNum;
    GRR_LRRC_REDIRECTED_INFO_STRU   astGrrRedirInfo[LRRC_GURRC_LTE_ARFCN_MAX_NUM];
}GAS_OM_EVENT_GSM_TO_LTE_REDIR_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_LTE_REDIR_END_ST
 Description    : GAS �� OM �ϱ� G �� L �ض��� ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��15��
    ��    ��    : s00184266
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_REDIRECTED_RESULT_ENUM_UINT32  enLrrcGrrRedirRlt;
}GAS_OM_EVENT_GSM_TO_LTE_REDIR_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_REDIR_START_ST
 Description    : GAS �� OM �ϱ� L �� G �ض��� ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��15��
    ��    ��    : s00184266
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_CELL_CAMPEDON_TYPE_ENUM_UINT8    enCellCampedType;
    VOS_UINT8                                   aucData[1];

    VOS_UINT16                                  ulGsmCellCount;
    GAS_OM_REDIRECTED_INFO_ST                   astGsmCellInfo[LRRC_GURRC_GERAN_ARFCN_MAX_NUM];
}GAS_OM_EVENT_LTE_TO_GSM_REDIR_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_LTE_TO_GSM_REDIR_END_ST
 Description    : GAS �� OM �ϱ� L �� G �ض��� ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��15��
    ��    ��    : s00184266
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_OM_REDIR_L2G_RESULT_ENUM_UINT8  enGrrLrrcRedirRlt;
    VOS_UINT8                           aucData[3];
}GAS_OM_EVENT_LTE_TO_GSM_REDIR_END_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_LTE_TO_GSM_ANR_END_ST
 �ṹ˵��  : ��OM�ϱ�L��G ANR�Ľ��
 �޸���ʷ :
 1.��    ��    : 2012��04��19��
   ��    ��    : w00176595
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_OM_ANR_L2G_RESULT_ENUM_UINT8    enGrrLrrcAnrRlt;
    VOS_UINT8                           aucData[3];
}GAS_OM_EVENT_LTE_TO_GSM_ANR_END_ST;
#endif /* #if (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END_ST
 ��������  : GAS �� OM �ϱ� �б��ѽ��
 �޸���ʷ  : 
  1.��    ��   : 2011��06��27��
    ��    ��   : s00184266
    �޸�����   : �����ɽṹ
    
*****************************************************************************/
typedef struct
{
    GAS_OM_BG_PLMN_LIST_SEARCH_RESULT_ENUM_UINT8            enBgPlmnListSearchRlt;
    VOS_UINT8                                               aucData[3];
} GAS_OM_EVENT_BG_PLMN_LIST_SEARCH_END_ST;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_BG_PLMN_SEARCH_ST
 ��������  : GAS��OM��������LTE�����еĽ��
 �޸���ʷ  : 
  1.��    ��   : 20112��05��07��
    ��    ��   : w00146666
    �޸�����   : �����ɽṹ
*****************************************************************************/
typedef struct
{
    GAS_OM_BG_PLMN_SEARCH_LTE_ABNORMAL_EVENT_ENUM_UINT8           enBgPlmnSearchLEvent;
    VOS_UINT8                                                     aucData[3];
} GAS_OM_ABNORMAL_EVENT_BG_PLMN_SEARCH_LTE_ST;

#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START_ST
 ��������  : GAS �� OM �ϱ� GSM �� UTRAN TDD ��ѡ��ʼ, Я��Ŀ��С����Ϣ
 �޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : W00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    /* Ŀ��С�� Ƶ�� */
    VOS_UINT16  usTddArfcn;

    /* Ŀ��С�� С�� ID */
    VOS_UINT16  usCellParaId;

    /* Ŀ��С���� ������� */
    VOS_INT16   sRsrp;

    /* С����ѡ���� :
        0:GAS_GCOMC_CELL_RESEL_TYPE_NON
        1:GAS_GCOMC_CELL_RESEL_TYPE_ACTIVE
        2:GAS_GCOMC_CELL_RESEL_TYPE_PASSIVE
                                   */
    VOS_UINT8   ucCellReselType;

    VOS_UINT8   aucRsv;   /* ����ֶ�  */
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_START_ST;

/*****************************************************************************
��Ϣ����  : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END_ST
��������  : GAS �� OM �ϱ� G �� UTRAN TDD ��ѡ����
�޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulGTReselRlt;
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_RESEL_END_ST;

/*****************************************************************************
��Ϣ����  : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START_ST
��������  : GAS �� OM �ϱ� UTRAN TDD �� G ��ѡ��ʼ
�޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMNɫ��  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) ��վɫ��  */
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_START_ST;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END_ST
 ��������  : GAS �� OM �ϱ� UTRAN TDD �� G ��ѡ����
 �޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulTGReselRlt;
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_RESEL_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START_ST
 Description    : GAS �� OM �ϱ� G �� UTRAN_TDD CCO ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2012��02��21��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usTddArfcn;      /* Ŀ��С�� Ƶ�� */
    VOS_UINT16  usCellParaId;    /* Ŀ��С�� С�� ID */
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END_ST
 Description    : GAS �� OM �ϱ� G �� UTRAN_TDD CCO ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2012��02��21��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulGTCCORlt;
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START_ST
 Description    : GAS �� OM �ϱ� UTRAN_TDD �� G CCO ��ʼ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2012��02��21��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMNɫ��  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) ��վɫ��  */
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_START_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END_ST
 Description    : GAS �� OM �ϱ� UTRAN_TDD �� G CCO ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2012��02��21��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    TRRC_GRR_CELL_RESEL_CCO_RESULT_ENUM_UINT32   ulTGCCORlt;
}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_CCO_END_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HANDOVER_END_ST
 Description    : GAS �� OM �ϱ� UTRAN_TDD �� G HANDOVER ����
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2012��02��21��
    ��    ��    : L00167020
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    TRRC_GRR_HANDOVER_RESULT_ENUM_UINT32   ulT2gHoRlt;

}GAS_OM_EVENT_UTRAN_TDD_TO_GSM_HANDOVER_END_ST;

/*****************************************************************************
 ��Ϣ����   : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START_ST
 ��������   : GAS �� OM �ϱ� G �� UTRAN TDD �ض��� ��ʼ

 �޸���ʷ :
  1.��    ��    : 2013��05��16��
    ��    ��    : y00142674
    �޸�����    : �����ṹ�壬GUTL ׼FR
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulUtranTddCellCnt;
    RRC_CELL_SEL_UTRAN_TDD_CELL_STRU        astUtranTddCell[RR_TRRC_MAX_UTRAN_TDD_CELL_NUM];
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_START_ST;

/*****************************************************************************
 ��Ϣ����   : GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END_ST
 ��������   : GAS �� OM �ϱ� G �� UTRAN TDD �ض��� ����

 �޸���ʷ :
  1.��    ��    : 2013��05��16��
    ��    ��    : y00142674
    �޸�����    : �����ṹ�壬GUTL ׼FR
*****************************************************************************/
typedef struct
{
    TRRC_GRR_REDIRECTED_RESULT_ENUM_UINT32  enTrrcGrrRedirRlt;
}GAS_OM_EVENT_GSM_TO_UTRAN_TDD_REDIR_END_ST;

#endif

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START_ST
 ��������  : GAS �� OM �ϱ� GSM �� UTRAN FDD ��ѡ��ʼ, Я��Ŀ��С����Ϣ
 �޸���ʷ  :
  1.��    ��    : 2012��02��25��
    ��    ��    : j00178524
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    /* Ŀ��С�� Ƶ�� */
    VOS_UINT16  usFddArfcn;

    /* Ŀ��С�� С�� ���� */
    VOS_UINT16  usScramblingCode;

    /* Ŀ��С���� ������� */
    VOS_INT16   sRsrp;
    VOS_INT16   sEcno;

    /* С����ѡ���� :
        0:GAS_GCOMC_CELL_RESEL_TYPE_NON
        1:GAS_GCOMC_CELL_RESEL_TYPE_ACTIVE
        2:GAS_GCOMC_CELL_RESEL_TYPE_PASSIVE
                                   */
    VOS_UINT8   ucCellReselType;

    VOS_UINT8   aucRsv[3];   /* ����ֶ�  */
}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_START_ST;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END_ST
 ��������  : GAS �� OM �ϱ� GSM �� UTRAN FDD ��ѡ��ʼ, Я��Ŀ��С����Ϣ
 �޸���ʷ  :
  1.��    ��    : 2012��02��25��
    ��    ��    : j00178524
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    /* ��ѡ��� */
    VOS_UINT32              ulResult;
}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_RESEL_END_ST;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START_ST
 ��������  : GAS �� OM �ϱ� GSM �� UTRAN FDD CCO��ʼ, Я��Ŀ��С����Ϣ
 �޸���ʷ  :
  1.��    ��    : 2012��02��25��
    ��    ��    : j00178524
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    /* Ŀ��С�� Ƶ�� */
    VOS_UINT16  usFddArfcn;

    /* Ŀ��С�� С�� ���� */
    VOS_UINT16  usScramblingCode;

}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_START_ST;

/*****************************************************************************
 ö����    : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_ENUM
 ö��˵��  : �� OM�ϱ� GAS CCO �� UTRAN FDD С���Ľ��
 �޸���ʷ  :
 1.��    ��    : 2012��03��06��
   ��    ��    : j00178524
   �޸�����    : �½�ö������, for V7R1 GTL PhaseII
*****************************************************************************/
enum GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_ENUM
{
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_SUCC                               = 0x1,        /* �ɹ� */
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_FAIL_TIMER_EXPIRE                  = 0x2,        /* CCO ���̳�ʱ */
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_FAIL_CONNECTION_REJECT             = 0x3,        /* Ŀ��С�����뱻�� */
    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_FAIL_OTHER                         = 0x4,        /* ����ʧ��ԭ�� */

    GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_BUTT
};

typedef VOS_UINT32 GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_RESULT_ENUM32;

/**********************************************************************************************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END_ST
 ��������  : GAS �� OM �ϱ� GSM �� UTRAN FDD CCO��ʼ, Я��Ŀ��С����Ϣ
 �޸���ʷ  :
  1.��    ��    : 2012��02��25��
    ��    ��    : j00178524
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    /* ��ѡ��� */
    VOS_UINT32              ulResult;
}GAS_OM_EVENT_GSM_TO_UTRAN_FDD_CCO_END_ST;

#define GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_LST_SIZE          (32)

/*****************************************************************************
 ��Ϣ����  : GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU
 ��������  : GAS �� OM �ϱ���ϵͳ�������
 �޸���ʷ  :
  1.��    ��    : 2016-01-06
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    VOS_UINT16                                              usCellId;

    VOS_INT16                                               sThreshXXXhigh;
    VOS_INT16                                               sThreshXXXLow;

    VOS_INT16                                               sSValue;
    VOS_UINT8                                               ucPrio;
    VOS_UINT8                                               ucEvaluateRlt;
}GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU
 ��������  : GAS �� OM �ϱ���ϵͳ�������
 �޸���ʷ  :
  1.��    ��    : 2016-01-06
    ��    ��    : p00166345
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   sQoffset;
    VOS_INT16                                   sFddQmin;
    VOS_INT16                                   sFddQminOffset;
    VOS_INT16                                   sFddRscpmin;
}GAS_OM_INTER_RESEL_RANKING_PARA_STRU;

typedef struct
{
    VOS_UINT8                                   ucScellPrio;
    VOS_UINT8                                   ucGsmLowFlg;
    VOS_UINT16                                  usThreshGsmLow;

    VOS_INT16                                   sSCellC1;
    VOS_UINT8                                   aucRsv[1];
    VOS_UINT8                                   ucInterCellCnt;

    GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_STRU  astInterCellLst[GAS_OM_INTER_RESEL_CELL_EVALUATE_INFO_LST_SIZE];

    GAS_OM_INTER_RESEL_RANKING_PARA_STRU        stRankingBasedParas;
}GAS_OM_INTER_RESEL_EVALUATE_RLT_STRU;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_INTER_RESEL_EVALUATE_START_ST
 ��������  : GAS �� OM �ϱ���ϵͳ��ѡ������ʼ���¼�
 �޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8          ucReselType;                           /*  ������ѡ�򱻶���ѡ */
    VOS_UINT8          ucBaseOnPrior;                         /*  �Ƿ�������ȼ���ѡ */
    VOS_UINT8          aucResv[2];                            /* ����λ */
}GAS_OM_EVENT_INTER_RESEL_EVALUATE_START_ST;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_START_ST
 ��������  : GAS �� OM �ϱ���ϵͳ��ѡ������ʱ���������¼�
 �޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTimerId;                            /*  ��ʱ����ID */
    VOS_UINT32          ulTimerLen;                           /*  ��ʱ���ĳ��� */
}GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_START_ST;

/*****************************************************************************
 ��Ϣ����  : GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_EXPIRED_ST
 ��������  : GAS �� OM �ϱ���ϵͳ��ѡ������ʱ����ʱ���¼�
 �޸���ʷ  :
  1.��    ��    : 2011��11��20��
    ��    ��    : w00176595
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTimerId;                            /*  ��ʱ����ID */
}GAS_OM_EVENT_INTER_RESEL_EVALUATE_TIMER_EXPIRED_ST;


/*****************************************************************************
 Structure      : GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL_ST
 Description    : GAS �� OM �ϱ� ��ϵͳ��ѡ������С����Χ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��22��
    ��    ��    : j00178524
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellType;                             /* С������ */
    VOS_UINT8                           aucResv[3];                             /* ����λ */
    VOS_UINT16                          usArfcn;                                /* С��Ƶ�� */
    VOS_UINT16                          usCellData;                             /* С����ʶ�������С��ID */
}GAS_OM_EVENT_RESEL_EVALUATE_ADD_CELL_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL_ST
 Description    : GAS �� OM �ϱ� ��ϵͳ��ѡ����С���Ӻ�ѡ�б���ɾ��
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2011��07��22��
    ��    ��    : j00178524
    �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCause;                                /* С���Ӻ�ѡ�б���ɾ����ԭ�� */
    VOS_UINT8                           ucCellType;                             /* С������ */
    VOS_UINT8                           aucResv[2];                             /* ����λ */
    VOS_UINT16                          usArfcn;                                /* С��Ƶ�� */
    VOS_UINT16                          usCellData;                             /* С����ʶ�������С��ID */
}GAS_OM_EVENT_RESEL_EVALUATE_RMV_CELL_ST;


#define GAS_OM_PLMN_LIST_SEARCHED_FREQ_MAX_NUM           (60)
#define GAS_OM_FREQ_SEARCHING_USED_MAX_NUM               (150)
#define GAS_OM_MAX_PREFER_CELL_NUM                     (15)

/*****************************************************************************
 �ṹ��    : GAS_OM_DEC_FAIL_ARFCN_ST
 �ṹ˵��  : ÿ��LIST������ʱ��, ��¼����δ�ɹ���С��
 �޸���ʷ :
 1.��    ��    : 2011��08��04��
   ��    ��    : w00176595
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16    usArfcn;
    VOS_INT16     sRxlev;
}GAS_OM_DEC_FAIL_ARFCN_ST;

/*****************************************************************************
 Structure      : GAS_OM_FREQUENCY_RXLEV_MEAS_RESULT_ST
 Description    : Ƶ�����ʱ�����յ�L1�����Ĳ��������GCOM����BCCH��Ϣ�Ľ��պͼ�����
                  ������й���֤С���Ƿ�Ϊ���ʵ�С����Ϣ�������´μ���ʱʹ�á�
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;                /* ������Ƶ�� */
    VOS_INT16                               sPower;                 /* �ź�ǿ�� */
} GAS_OM_FREQUENCY_RXLEV_MEAS_RESULT_ST;


/*****************************************************************************
 Structure      : GAS_OM_EVENT_PLMN_SEARCH_DEC_CELL_STRU
 Description    : ����������ʹ�õĺ���������
 Message origin :
 �޸���ʷ :
 1.��    ��    : 2011��08��04��
   ��    ��    : w00176595
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                usCount;
    VOS_UINT8                 ucRsv[2];
    GAS_OM_DEC_FAIL_ARFCN_ST  astDecFailArfcn[GAS_OM_PLMN_LIST_SEARCHED_FREQ_MAX_NUM];
}GAS_OM_EVENT_PLMN_SEARCH_DEC_CELL_STRU;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_PLMN_SEARCH_RXLEV_STRU
 Description    : ���������е�ƽ���˺�ʣ��������ĵ�ƽ����
 Message origin :
 �޸���ʷ :
 1.��    ��    : 2011��08��04��
   ��    ��    : w00176595
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                usCount;
    VOS_UINT8                 ucRsv[2];
    GAS_OM_FREQUENCY_RXLEV_MEAS_RESULT_ST  astArfcnRxlev[GAS_OM_FREQ_SEARCHING_USED_MAX_NUM];
}GAS_OM_EVENT_PLMN_SEARCH_RXLEV_STRU;

typedef struct
{
    VOS_UINT32    ulMcc;
    VOS_UINT32    ulMnc;
    VOS_UINT16    usArfcnCount;
    VOS_UINT16    usRsv;
    VOS_UINT16    ausArfcn[GAS_OM_PLMN_LIST_SEARCHED_FREQ_MAX_NUM];
}GAS_OM_PREFER_PLMN_CELL_ST;

/*****************************************************************************
 �ṹ��       : GAS_OM_PREFER_CELL_ST
 �ṹ˵��  : ÿ��LIST����������, �������ѡС����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                     usPreferCellCount;
    VOS_UINT16                     usRsv;
    GAS_OM_PREFER_PLMN_CELL_ST     astPreferCell[GAS_OM_MAX_PREFER_CELL_NUM];
} GAS_OM_PREFER_CELL_ST;


/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_END_ST
 �ṹ˵��  : ��OM�ϱ�W��G Resel/CCO�Ľ��
 �޸���ʷ :
 1.��    ��    : 2012��04��19��
   ��    ��    : w00176595
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    GAS_OM_RESEL_CCO_W2G_RESULT_ENUM_UINT8    enReselCCORst;
    VOS_UINT8                                 aucData[3];
}GAS_OM_EVENT_WCDMA_TO_GSM_RESEL_CCO_END_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_LOG_RECORD_STRU
 Э����  :
 ASN.1���� : GAS��ӡ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeStamp; /* �ϱ���Ϣ��ʱ��� */
    VOS_UINT32                          enLevel;     /* �ϱ���Ϣ�Ĵ�ӡ���� */
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;      /* �ϱ���Ϣ���ļ��� */
    VOS_UINT32                          ulLine;      /* �ϱ���Ϣ���к� */
    VOS_INT32                           alPara[4];
}GAS_OM_LOG_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_LOG_INFO_STRU
 Э����  :
 ASN.1���� : GAS��ӡ��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSavedMsgCnt;
    GAS_OM_LOG_RECORD_STRU              astData[GAS_OM_PRINT_MSG_MAX_NUM];
}GAS_OM_LOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : Gas_WRITE_PREFER_CELL_SWITCH_TO_NV_MSG
 �ṹ˵��  : 
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSwitch;
}Gas_WRITE_PREFER_CELL_SWITCH_TO_NV_MSG;

/*****************************************************************************
 �ṹ��    : Gas_WRITE_PREFER_PLMN_NUM_TO_NV_MSG
 �ṹ˵��  : 
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usPlmnCnt;          
}Gas_WRITE_PREFER_PLMN_NUM_TO_NV_MSG;

/*****************************************************************************
 �ṹ��    : Gas_PREFER_CELL_PLMN_LIST_STRU
 �ṹ˵��  : ��ѡС��NV����plmn list�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct 
{
    VOS_UINT32                          ulMcc;            
    VOS_UINT32                          ulMnc;        
    VOS_UINT16                          usArfCnt;         
    VOS_UINT16                          aArfs[60];          
}Gas_PREFER_CELL_PLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : Gas_WRITE_PREFER_CELL_TO_NV_MSG
 �ṹ˵��  : 
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
    Gas_PREFER_CELL_PLMN_LIST_STRU      aPlmnlist[5];     
}Gas_WRITE_PREFER_CELL_TO_NV_MSG;

/*****************************************************************************
 �ṹ��    : GAS_OM_WRITE_NV_REQ_ST
 �ṹ˵��  : 
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                           /* _H2ASN_Skip */        
    VOS_UINT16                          usMsgID;             /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];           /* _H2ASN_Skip */
    VOS_UINT16                          usNvItem;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucData[4];    
    /*********************************************************************
        _H2ASN_Array2String
    **********************************************************************/
}GAS_OM_WRITE_NV_REQ_ST;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_UTRAN_CELL_BAR_INFO_STRU
 Description    : ����UTRANС�����ͷ��Ŀ�ά�ɲ�ṹ����Ϣ
 Message origin :
 �޸���ʷ :
 1.��    ��    : 2015��07��24��
   ��    ��    : w00146666
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usArfcn;      /* UTRANС��Ƶ�� */

    VOS_UINT16 usCellData;  /* FDDС���˲�����ʾ����,TDDС���˲�����ʾCellParaID */

    VOS_UINT32 ulTimerLen;  /* �ͷ���ʱ��, ��λms */
}GAS_OM_EVENT_UTRAN_CELL_BAR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_IND_COMMON_ST
 �ṹ˵��  : ��ӦGAS_OM_EVENT_IND_ST��aucData[4]
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4];      
}GAS_OM_EVENT_IND_COMMON_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_AFC_INFO_IND_ST
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AFC��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAfcLockFlag;    /* AFC�Ƿ�������־    */
    VOS_UINT32                          ulWrittenTcxoCount;   /* дafc�Ĵ��� */
    VOS_UINT16                          usAfcCurrVal;     /* ��ǰAFCֵ          */
    VOS_UINT16                          usInitFreqency;   /* ����ʱ��AFCֵ */
    VOS_UINT16                          usDynFreqency;    /* �ϴ�NV�б����AFCֵ         */
    VOS_UINT16                          usResereved;   
} GAS_OM_AFC_INFO_IND_ST;

#if ( FEATURE_ON == FEATURE_DSDS )
/*****************************************************************************
 �ṹ��    : GAS_OM_APPLY_TASK_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSDS GAS�������Դ����ṹ
*****************************************************************************/
typedef struct
{
    RRM_PS_TASK_TYPE_ENUM_UINT16            enOmApplyTaskType;                  /* ������������� */
    GAS_OM_TASK_STATUS_ENUM_UINT16          enOmApplyTaskStatus;                /* ���������״̬ */
}GAS_OM_APPLY_TASK_INFO_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_APPLY_TASK_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSDS GAS�������Դ�����б�
*****************************************************************************/
typedef struct
{
    GAS_OM_APPLY_TASK_INFO_STRU              astOmApplyTaskInfo[GAS_OM_APPLY_TASK_LIST_MAX_NUM]; /* ����������б� */
}GAS_OM_APPLY_TASK_LIST_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_RF_RESOURCE_TASK_LIST_STRU
 �ṹ˵��  : �ϱ�������Դ�����б�
 �޸���ʷ  : 
 1.��    ��    : 2014��02��25��
   ��    ��    : l67237
   �޸�����    : �½��ṹ�� GAS DSDS
*****************************************************************************/
typedef struct
{
    GAS_OM_APPLY_TASK_LIST_STRU                stGasRfResTaskList;
}GAS_OM_EVENT_RF_RESOURCE_TASK_LIST_STRU;
#endif


/*****************************************************************************
 �ṹ��    : GAS_OM_MSG_DATA
 �ṹ˵��  : 
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
    OM_GAS_MSG_ID_ENUM_UINT16           usMsgID;          /*_H2ASN_MsgChoice_Export OM_GAS_MSG_ID_ENUM_UINT16*/
    VOS_UINT16                          usReserved1;
    VOS_UINT8                           aucData[4];

    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_GAS_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}GAS_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : GasOmInterface_MSG
 �ṹ˵��  : GasOmInterface ���ڵ�
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER             

    GAS_OM_MSG_DATA                     stMsgData;
}GasOmInterface_MSG;

/*****************************************************************************
 �ṹ��    : GasEvent_MSG
 �ṹ˵��  : GASEvent ���ڵ�
 �޸���ʷ  : 
 1.��    ��    : 2012��09��26��
   ��    ��    : z00206003
   �޸�����    : �½��ṹ�� DTS2012092601774
*****************************************************************************/
typedef struct   
{
    GAS_OM_EVENT_IND_ST                 stMsgData;
}GasEvent_MSG;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW_ST
 �ṹ˵��  : ��Ϣ�������ʱ�ϱ���OM�¼��Ľṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��09��29��
   ��    ��    : w00176595
   �޸�����    : �½��ṹ�� DTS2012092900233
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgId;        /* ��������Ϣ��MSG ID */
    VOS_UINT8                           ucModule;       /* ��Ϣ���������GCOMģ��  */
    VOS_UINT8                           ucRsv;          /* ����λ  */
}GAS_OM_EVENT_GCOM_CACHED_MSG_OVERFLOW_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_TRANSACTION_INFO_ST
 �ṹ˵��  : ��ѯNAS����״̬����Ĵ�ӡ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��16��
   ��    ��    : w00176595
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct   
{
    VOS_UINT8                           ucCsTransactInfo;   /* CS�ĺ���״̬ */
    VOS_UINT8                           ucIsCallActive;     /* ҵ��״̬ */
    VOS_UINT8                           aucRsv[2];          /* ����λ  */
}GAS_OM_EVENT_TRANSACTION_INFO_ST;

#if (FEATURE_ON == FEATURE_AGPS)
#define GAS_OM_RRLP_MESSAGE_MAX_LENGTH (1024) /* ÿ��APDU��RRLP��Ϣ�Ϊ247������ٶ����Ϊ4�� */
#define GAS_OM_RRLP_MESSAGE_HEAD       (4) /* ÿ��RRLP��Ϣͷ���� usMsgID + usLength */

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_RRLP_MSG_STRU
 �ṹ˵��  : RR��LCS֮�佻���Ķ�λ��ص���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgID;                                /* REQ or RSP */
    VOS_UINT16                          usLength;                               /* RRLP���� */
    VOS_UINT8                           aucData[GAS_OM_RRLP_MESSAGE_MAX_LENGTH];/* RRLP���� */
}GAS_OM_EVENT_RRLP_MSG_STRU;

#endif


/* Added by yangsicong for probe�ӿ��¿���, 2012-10-30, begin */
/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_INFO_REQ_STRU
 �ṹ˵��  : ·������ OM��GAS�����ϱ���Ϣ��ԭ��ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16        enReportType;
    VOS_UINT16                            usReportPeriod;   /* ��λ: ms */
    GAS_ROAD_TEST_INFO_TYPE_ENUM_UINT16   enRtInfoType;
}GAS_OM_ROAD_TEST_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_INFO_CNF_STRU
 �ṹ˵��  : ·������ GAS��OM�ظ��������ϱ���Ϣȷ�ϵ�ԭ��ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;

    GAS_OM_RESULT_ENUM_UINT8            enResult;
    VOS_UINT8                           ausResv[3];
    OM_GAS_REPORT_ACTION_ENUM_UINT16    enStartOrStop;
    OM_GAS_REPORT_TYPE_ENUM_UINT16      enReportType;
}GAS_OM_ROAD_TEST_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_MEAS_RESULT_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��ķ���С�����������Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usArfcn;           /* ȡֵ��Χ[0,1023],��Чֵ=65535 */
    GAS_OM_GSM_BAND_ENUM_UINT16     enBand;            /* ȡֵ��Χ[0, 3],��Чֵ=65535 */
    VOS_UINT16                      usBsic;            /* ȡֵ��Χ[0, 77],��Чֵ=65535 */
    VOS_INT16                       sRxlevFull;        /* ȡֵ��Χ[-110, 47],��Чֵ=-32768 */
    VOS_INT16                       sRxlevSub;         /* ȡֵ��Χ[-110, 47],��Чֵ=-32768 */
    VOS_INT16                       sRxlevIdle;        /* ȡֵ��Χ[-110, 47],��Чֵ=-32768 */
    VOS_UINT16                      usRxQualFull;      /* ȡֵ��Χ[0, 7],��Чֵ=65535 */
    VOS_UINT16                      usRxQualSub;       /* ȡֵ��Χ[0, 7],��Чֵ=65535 */
    VOS_UINT16                      usRltMax;          /* ȡֵ��Χ[0, 64],��Чֵ=65535 */
    VOS_UINT16                      usRltAct;          /* ȡֵ��Χ[0, 64],��Чֵ=65535 */
    VOS_UINT16                      usErrBitNumFull;   /* ȡֵ��Χ[0, 65535],��Чֵ=0 */
    VOS_UINT16                      usBitNumFull;      /* ȡֵ��Χ[0, 65535],��Чֵ=0 */
    VOS_UINT16                      usErrBitNumSub;    /* ȡֵ��Χ[0, 65535],��Чֵ=0 */
    VOS_UINT16                      usBitNumSub;       /* ȡֵ��Χ[0, 65535],��Чֵ=0 */
    VOS_INT16                       sC1;               /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_INT16                       sC2;               /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_INT16                       sC31;              /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_INT16                       sC32;              /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_UINT16                      usMeanBep;          /* ȡֵ��Χ[0, 31],��Чֵ=65535 */
    VOS_UINT16                      usCvBep;            /* ȡֵ��Χ[0, 7],��Чֵ=-32768 */
}GAS_OM_ROAD_TEST_SCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_GNCELL_MEAS_RESULT_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ���G��С�����������Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usArfcn;                               /* ȡֵ��Χ[0,1023],��Чֵ=65535 */
    GAS_OM_GSM_BAND_ENUM_UINT16     enBand;            /* ȡֵ��Χ[0, 3],��Чֵ=65535 */
    VOS_UINT16  usBsic;                                /* ȡֵ��Χ[0, 77],��Чֵ=65535 */
    VOS_INT16   sRxlev;                                /* ȡֵ��Χ[-110, 47],��Чֵ=-32768 */
    VOS_INT16   sC1;                                   /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_INT16   sC2;                                   /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_INT16   sC31;                                  /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
    VOS_INT16   sC32;                                  /* ȡֵ��Χ[-127, 127],��Чֵ=-32768 */
}GAS_OM_ROAD_TEST_GNCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_3G_FCELL_MEAS_RESULT_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ���3G��С�����������Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usUArfcn;            /* ȡֵ��Χ[0, 16383],��Чֵ=65535 */
    VOS_UINT16 usPsc;               /* ȡֵ��Χ[0, 511],��Чֵ=65535 */
    VOS_UINT16 usDiversity;         /* ȡֵ��Χ[0, 1],��Чֵ=65535 */
    VOS_INT16  sRscp;               /* ȡֵ��Χ[-115 -25],��Чֵ=-32768 */
    VOS_INT16  sEcn0;               /* ȡֵ��Χ[-48, 2],��Чֵ=-32768 , 1/2���� */
    VOS_UINT8   aucResv[2];
}GAS_OM_ROAD_TEST_3G_FCELL_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_MEAS_RESULT_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��Ĳ��������Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    GAS_OM_ROAD_TEST_SCELL_MEAS_RESULT_STRU     stScellMeasResult;              
    VOS_UINT16                                  usGNCellNum;                    /* ȡֵ��Χ[0, 6],��Чֵ=65535 */
    VOS_UINT16                                  us3GFCellNum;                   /* ȡֵ��Χ[0, 96],��Чֵ=65535 */
    GAS_OM_ROAD_TEST_GNCELL_MEAS_RESULT_STRU    astNcellMeasResult[GAS_OM_2G_NCELL_CNT_MAX_NUM];          
    GAS_OM_ROAD_TEST_3G_FCELL_MEAS_RESULT_STRU  ast3GFCellMeasResult[GAS_OM_3G_NCELL_CNT_MAX_NUM];       
}GAS_OM_ROAD_TEST_MEAS_RESULT_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_CELL_FULL_ID_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��ķ���С����ʶ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;           	/* ȡֵ��Χ[0, 1023],��Чֵ=65535 */
    VOS_UINT16                          usBsic;            	/* ȡֵ��Χ[0, 77],��Чֵ=65535 */
    GAS_OM_GSM_BAND_ENUM_UINT16         enBand;            	/* ȡֵ��Χ[0, 3],��Чֵ=65535 */
    VOS_UINT16                          usCi;              	/* ȡֵ��Χ[0, 65535],��Чֵ=65535 */
    VOS_UINT32                          ulMcc;             	/* ȡֵ��Χ[000, 999],��Чֵ=65535 */
    VOS_UINT32                          ulMnc;             	/* ȡֵ��Χ[000, 999],��Чֵ=65535 */
    VOS_UINT16                          usLac;             	/* ȡֵ��Χ[0, 65535],��Чֵ=65535 */
    VOS_UINT16                          usRac;              /* ȡֵ��Χ[0,255],��Чֵ=65535 */   // TODO: ��ȷ��
}GAS_OM_ROAD_TEST_CELL_FULL_ID_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_CCCH_PARA_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��ķ���С��CCCH�����ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usAttachAllowed;    /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    VOS_UINT16  usAgBlk;            /* ȡֵ��Χ[0,7],��Чֵ=65535 */
    VOS_UINT16  usT3212;            /* ȡֵ��Χ[0,63],��Чֵ=65535 */
    VOS_UINT16  usMfrms;            /* ȡֵ��Χ[2,9],��Чֵ=65535 */
}GAS_OM_ROAD_TEST_CCCH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_CCCH_PARA_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��ķ���С��RACH�����ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usTxInt;            /* ȡֵ��Χ[3,50],��Чֵ=65535 */
    VOS_UINT16  usMaxRetrans;       /* ȡֵ��Χ[1,7],��Чֵ=65535 */
    VOS_UINT16  usCba;              /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    VOS_UINT16  usReestablishment;  /* ȡֵ��Χ[0,1],��Чֵ=65535 */
}GAS_OM_ROAD_TEST_RACH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_CELL_SEL_RESEL_PARA_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��ķ���С����ѡ�����ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usMsTxPwrMaxCch;        /* ȡֵ��Χ[0,31],��Чֵ=65535 */
    VOS_INT16   sRxlevAccessMin;        /* ȡֵ��Χ[-110,-47],��Чֵ=-32768 */
    VOS_UINT16  usPowerOffsetValid;     /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    VOS_UINT16  usPowerOffset;          /* ȡֵ��Χ[0,3],��Чֵ=65535 */
    VOS_UINT16  usCellReselHysteresis;  /* ȡֵ��Χ[0,14],��Чֵ=65535 */
    VOS_UINT16  usCellReselOffset;      /* ȡֵ��Χ[0,63],��Чֵ=65535 */
    VOS_UINT16  usTmpOffset;            /* ȡֵ��Χ[0,7],��Чֵ=65535 */
    VOS_UINT16  usPenaltyTime;          /* ȡֵ��Χ[0,31],��Чֵ=65535 */ 
    VOS_UINT16  usCbq;                  /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    VOS_UINT16  usCellPri;              /* ȡֵ��Χ[0,1],��Чֵ=65535 */
}GAS_OM_ROAD_TEST_CELL_SEL_RESEL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_SCELL_CELL_PARA_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ��ķ���С����Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usGprsSupported;    /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    VOS_UINT16                                      usEGprsSupported;   /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    GAS_OM_NETWORK_CONTROL_ORDER_ENUM_UINT16        enNcMode;           /* ȡֵ��Χ[0,2],��Чֵ=65535 */
    VOS_UINT16                                      usPbcchTs;          /* ȡֵ��Χ[0,7],��Чֵ=65535 */ 
    GAS_OM_ROAD_TEST_CELL_FULL_ID_STRU              stCellFullID;
    GAS_OM_ROAD_TEST_CCCH_PARA_STRU                 stCcchPara;
    GAS_OM_ROAD_TEST_RACH_PARA_STRU                 stRachPara;
    GAS_OM_ROAD_TEST_CELL_SEL_RESEL_PARA_STRU       stSelReselPara;
}GAS_OM_ROAD_TEST_SCELL_CELL_PARA_STRU;


/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_DCH_CHAN_PARA_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ���DCH��Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{

    VOS_UINT16                                  usTSC;              /* ȡֵ��Χ[0,7],��Чֵ=65535 */
    VOS_UINT16                                  usMsDtx;            /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    GAS_OM_VOICE_CHANNEL_TYPE_ENUM_UINT16       enChanType;         /* ȡֵ��Χ[1,4],��Чֵ=65535 */
    VOS_UINT16                                  usTchArfcn;         /* ȡֵ��Χ[0,1023],��Чֵ=65535 */
    VOS_UINT16                                  usTsNum;            /* ȡֵ��Χ[0,7],��Чֵ=65535 */
    GAS_OM_SPECCH_CODEC_ENUM_UINT16             enSpeechCodec;      /* ȡֵ��Χ[0,8],��Чֵ=65535 */
    GAS_OM_RR_CIPHER_ALGORITHM_ENUM_UINT16      enCipherAlgorithm;   /* ȡֵ��Χ[0,8],��Чֵ=65535 */
    VOS_UINT16                                  usSubChanNum;       /* ȡֵ��Χ[0,7],��Чֵ=65535 */
    VOS_UINT16                                  usHoppingState;     /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    VOS_UINT16                                  usHoppingFreqCnt;   /* ȡֵ��Χ[0,64],��Чֵ=65535 */    
    VOS_UINT16                                  ausHoppingFreq[GAS_OM_HOPPING_REQ_CNT_MAX_NUM]; /* ȡֵ��Χ[0,1023],��Чֵ=65535 */
    VOS_UINT16                                  usMaio;             /* ȡֵ��Χ[0,63],��Чֵ=65535 */
    VOS_UINT16                                  usHsn;              /* ȡֵ��Χ[0,63],��Чֵ=65535 */

}GAS_OM_ROAD_TEST_DCH_CHAN_PARA_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_RUN_MODE_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ���GAS��ǰ������״̬��Ϣ�ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    GAS_OM_GSM_RUNNING_MODE_ENUM_UINT16  enGsmMode;          /* ȡֵ��Χ[0,1],��Чֵ=65535 */
    GAS_OM_GPRS_RUNNING_MODE_ENUM_UINT16  enGprsMode;         /* ȡֵ��Χ[0,1],��Чֵ=65535 */
}GAS_OM_ROAD_TEST_RUN_MODE_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_ROAD_TEST_INFO_IND_STRU
 �ṹ˵��  : ·������ GAS��OM�ϱ���Ϣԭ��ṹ
 �޸���ʷ  : 
 1.��    ��    : 2012��11��07��
   ��    ��    : y49634
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    OM_GAS_REPORT_TYPE_ENUM_UINT16          enReportType;                       /* �ϱ���ʽ */
    GAS_ROAD_TEST_INFO_TYPE_ENUM_UINT16     enRtInfoTypeChoice;                 /* �ϱ���Ϣ���� */
    
    union
    {
        GAS_OM_ROAD_TEST_MEAS_RESULT_STRU        stRtMeasResult;                /* ����������� */
        GAS_OM_ROAD_TEST_SCELL_CELL_PARA_STRU    stRtScellPara;                 /* ����С���������� */
        GAS_OM_ROAD_TEST_DCH_CHAN_PARA_STRU      stRtDchChan;                   /* DCH�������� */
    }u;
    
    GAS_OM_ROAD_TEST_RUN_MODE_STRU          stRtRunMode;                        /* GSM/GPRS״̬ */
    
}GAS_OM_ROAD_TEST_INFO_IND_STRU;
/* Added by yangsicong for probe�ӿ��¿���, 2012-10-30, end */


/*****************************************************************************
 �ṹ��      : GAS_OM_JAM_DETECT_CTX_IND_STRU
 ����        : GAS��OM�ϱ���Jamming Detection ������
 
 �޸���ʷ :
 1.��    ��   : 2015��2��17��
   ��    ��   : y00142674
   �޸�����   : �����ṹ, for W Jamming Detection

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usHighRxlevArfcnNum;                    /* ȫ��ǿ�ź�Ƶ�� */
    VOS_UINT16                          usJammingArfcnNum;                      /* ͬ��ʧ�ܵĸ���Ƶ����� */
    VOS_UINT8                           ucRptedJamRlt;                          /* ���ϱ��ĸ��ż������0:�޸���, 1:�и��� */

    VOS_UINT8                           ucMode;                                 /* JAM���õ�ģʽ��0:�ر�, 1:�� */
    VOS_UINT8                           ucMethod;                               /* JAM���ʹ�õķ�����1:����1��2:����2,Ŀǰֻ֧��2 */
    VOS_UINT8                           ucFreqNum;                              /* �����Ҫ�ﵽ��Ƶ�������ȡֵ��Χ:[0,255] */
    VOS_INT8                            cThreshold;                             /* �����Ҫ�ﵽ��Ƶ�����ֵ��ȡֵ��Χ:[-70,0] */
    VOS_UINT8                           ucJamDetectingTmrLen;                   /* ǿ�ź�Ƶ������������޺󣬼��ͬ������Ķ�ʱ��ʱ��(s) */
    VOS_UINT8                           ucJamDetectedTmrLen;                    /* ��⵽���ź󣬵ȴ�����������ʱ��(s) */
    VOS_UINT8                           ucFastReportFlag;                       /* �����������Ƿ���Ҫ�����ϱ� */  
}GAS_OM_JAM_DETECT_CTX_IND_STRU;

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_START_ST
 �ṹ˵��  : GAS �� OM �ϱ� ��ȡLTE�л���GSMָ���SLICEֵ
 �޸���ʷ  : 
 1.��    ��    : 2013��12��18��
   ��    ��    : s00184266
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulCurSlice;
}GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_START_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_END_ST
 �ṹ˵��  : GAS �� OM �ϱ� Lte �� Geran HANDOVER ����
 �޸���ʷ  : 
 1.��    ��    : 2013��9��13��
   ��    ��    : s00184266
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    LRRC_GURRC_HANDOVER_RESULT_ENUM_UINT32   enL2gHoRlt;
}GAS_OM_EVENT_LTE_TO_GSM_HANDOVER_END_ST;
#endif /* end of (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 �ṹ��    : GAS_OM_EVENT_LAU_REQ_INFO_STRU
 �ṹ˵��  : GAS �� OM �ϱ� LAU �������Ϣ
 �޸���ʷ  : 
 1.��    ��    : 2015��05��11��
   ��    ��    : p00166345
   �޸�����    : �½��ṹ�� 
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlt;
    NAS_LAU_TYPE_ENUM_UINT8             enLauType;
    VOS_UINT8                           ucFollowOnFlg;
    NAS_ADDITION_UPDATE_PARA_ENUM_UINT8 enAdditionUpdatePara;

    VOS_UINT8                           aucRsv[1];
}GAS_OM_EVENT_LAU_REQ_INFO_STRU;

/*****************************************************************************
 Structure      : GAS_OM_EVENT_W_NON_NCELL_MEAS_START_ST
 Description    : W ���������������¼�
 Message origin :
*****************************************************************************/
typedef struct
{
    /* ������ʱ��ʱ�� */
    VOS_UINT32                          ulTimerLen;
}GAS_OM_EVENT_W_NON_NCELL_MEAS_START_ST;

#define GAS_OM_PLMN_SEARCH_CELL_SATISFACTION_RESULT_MAX_NUM           (60)

/*****************************************************************************
 �ṹ��    : GAS_OM_CELL_SATISFACTION_RESULT_ST
 �ṹ˵��  : С�����о����
 �޸���ʷ :
  1.��    ��   : 2014��04��01��
    ��    ��   : w00176595
    �޸�����   : �����ṹ��
  2.��    ��   : 2015��8��19��
    ��    ��   : y00142674
    �޸�����   : �ϱ����ֽ�������ȼ���for ParallelSrch

*****************************************************************************/
typedef struct
{
    VOS_UINT16      usArfcn;                                        /* Ƶ�� */
    VOS_UINT8       ucSatisfactionResult;                           /* �о���� */
    VOS_UINT8       ucCellPriorityFlag;                             /* ���ȼ� */                                         
}GAS_OM_CELL_SATISFACTION_RESULT_ST;

/*****************************************************************************
 �ṹ��    : GAS_OM_PLMN_SRCH_CELL_SATISFACTION_RESULT_ST
 �ṹ˵��  : С�����о����
 �޸���ʷ :
 1.��    ��    : 2014��04��01��
   ��    ��    : w00176595
   �޸�����    : �����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                               usCellCount;
    VOS_UINT16                               usRsv;        
    GAS_OM_CELL_SATISFACTION_RESULT_ST       astCellSatisfaction[GAS_OM_PLMN_SEARCH_CELL_SATISFACTION_RESULT_MAX_NUM];
}GAS_OM_PLMN_SRCH_CELL_SATISFACTION_RESULT_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START_ST
 �ṹ˵��  : GAS �� OM �ϱ� UTRAN_FDD �� G CCO ��ʼ
 �޸���ʷ  :
  1.��  ��   : 2014��5��5��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucNcc;                                  /* (3bit) PLMNɫ��  */
    VOS_UINT8                           ucBcc;                                  /* (3bit) ��վɫ��  */
}GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_START_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END_ST
 �ṹ˵��  : GAS �� OM �ϱ� UTRAN_FDD �� G CCO ����
 �޸���ʷ  :
  1.��  ��   : 2014��5��5��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulW2GCcoRlt;
}GAS_OM_EVENT_UTRAN_FDD_TO_GSM_CCO_END_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START_ST
 �ṹ˵��  : GAS �� OM �ϱ� UTRAN_FDD �� G RESEL ��ʼ
 �޸���ʷ  :
  1.��  ��   : 2014��5��20��
    ��  ��   : s00186226
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulArfcn;
    VOS_UINT32                          ulNcc;                                  /* (3bit) PLMNɫ��  */
    VOS_UINT32                          ulBcc;                                  /* (3bit) ��վɫ��  */
}GAS_OM_EVENT_UTRAN_FDD_TO_GSM_RESEL_START_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_FREQ_INFO_LIST_STRU
 �ṹ˵��  : OM�ϱ�Ƶ���б�
 �޸���ʷ  :
  1.��  ��   : 2015��9��10��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqNum; 
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          ausFreqInfo[SEARCH_FREQ_BA_MAX_NUM];  
}GAS_OM_FREQ_INFO_LIST_STRU;

/*****************************************************************************
 �� �� ��  : GAS_OM_SEARCH_PROC_INFO_STRU
 �ṹ˵��  : GAS�������������Ϣ�ϱ�
 �޸���ʷ  :
  1.��  ��   : 2015��9��10��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_SEARCH_PROC_ENUM_UINT8               enSrchProc;
    GAS_OM_SEARCH_PROC_BUILD_RESULT_ENUM_UINT8  enBuildResult;
    VOS_UINT16                                  usBandInfo;
    GAS_OM_FREQ_INFO_LIST_STRU                  stFreqInfoList;
}GAS_OM_SEARCH_PROC_INFO_STRU;

/*****************************************************************************
 �� �� ��  : GAS_OM_SEARCHED_FREQ_LIST_STRU
 �ṹ˵��  : GAS�������б��ϱ�
 �޸���ʷ  :
  1.��  ��   : 2015��9��10��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    GAS_OM_FREQ_INFO_LIST_STRU                  stFreqInfoList;
}GAS_OM_SEARCHED_FREQ_LIST_STRU;

/*****************************************************************************
 �� �� ��  : GAS_OM_CSS_CLOUD_INTERFACE_STRU
 �ṹ˵��  :
 �޸���ʷ  :
  1.��  ��   : 2015��11��5��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulReturnValue;
    GAS_OM_CSS_INTERFACE_NAME_ENUM_UINT32       enCssInterfaceName;
    VOS_UINT32                                  ulPlmnNum;
    union
    {
        CSS_PREF_FREQ_INFO_STRU                 astPrefFreq[GAS_OM_CSS_INTERFACE_OUPUT_PREF_FREQ_MAX_NUM];

        CSS_PREF_BAND_INFO_STRU                 astPrefBand[GAS_OM_CSS_INTERFACE_OUPUT_PREF_BAND_MAX_NUM];
        
        CSS_PLMN_ID_STRU                        astPlmn[GAS_OM_CSS_INTERFACE_INPUT_PLMN_MAX_NUM];
    }u;
}GAS_OM_CSS_CLOUD_INTERFACE_STRU;

/*****************************************************************************
 Structure      : OM_GAS_NV_WRITE_REQ_STRU
 Description    : CI NV�޸�ģ��ṹ��
 Message origin :
*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          usNvItem;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucData[4];
}OM_GAS_NV_WRITE_REQ_STRU;

typedef GAS_OM_OTA_CNF_STRUCT  GAS_OM_NV_WRITE_CNF_STRU;

/*****************************************************************************
 �� �� ��  : SDT_GAS_CONNECTED_IND_STRU
 �ṹ����  : OM��GAS���͵�HiDS������Ϣ

 �޸���ʷ      :
  1.��    ��   : 2015��6��24��
    ��    ��   : ���� h00166210
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    DIAG_GAS_MSG_COMM_HEAD_ST           stMsgCommHead;
}SDT_GAS_CONNECTED_IND_STRU;

typedef GAS_OM_OTA_CNF_STRUCT  GAS_SDT_CONNECTED_CNF_STRU;

/*****************************************************************************
 �ṹ��    : GAS_OM_TRANS_IND_ST
 Э����  :
 ASN.1���� : ͸����Ϣ�ϱ������ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserved;
    VOS_UINT8   aucData[4];
}GAS_OM_TRANS_IND_ST;

/*****************************************************************************
 �� �� ��  : GAS_OM_OTA_IND_STRUCT
 �ṹ����  : GAS��OM�ϱ��տ���Ϣ

 �޸���ʷ      :
  1.��    ��   : 2008��4��21��
    ��    ��   : ���� y58800
    �޸�����   : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16    usOtaMsgID;
    VOS_UINT8     ucUpDown;
    VOS_UINT8     ucRsv;
    VOS_UINT32    ulLengthASN;
    VOS_UINT8     aucData[4];
}GAS_OM_OTA_IND_STRUCT;

/******************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 ��������
*****************************************************************************/




#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif /* __cplusplus */


#endif /* __GASOMINTERFACE_H__ */


