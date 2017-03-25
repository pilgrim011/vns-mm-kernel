/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMsccPifInterface.h
  �� �� ��   : ����
  ��    ��   : z00161729
  ��������   : 2013��3��25��
  ����޸�   :
  ��������   : mma,mscc,mmc��Ϣ������ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��25��
    ��    ��   : z00161729
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _NAS_MSCC_PIF_INTERFACE_H_
#define _NAS_MSCC_PIF_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafTypeDef.h"
#include "TafNvInterface.h"
#include "NasNvInterface.h"
#include "ComInterface.h"

#include "TafAppMma.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_PIF_CELL_MAX_NUM            (8)                                /* С��������� */
#define NAS_MSCC_PIF_MAX_PLMN_CNT            (37)

#if (FEATURE_ON == FEATURE_CSG)
#define NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM                    (35)
#else
#define NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM                    (1)
#endif

#if (FEATURE_ON == FEATURE_CSG)
#define NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN                (48)
#define NAS_MSCC_PIF_CSG_TYPE_LEN                           (12)
#else
#define NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN                (4)
#define NAS_MSCC_PIF_CSG_TYPE_LEN                           (4)
#endif

#define NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT       (12)

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_MSCC_PIF_MAX_RAT_NUM             (3)                                /* ��ǰ֧�ֵĽ��뼼������ */
#else
#define NAS_MSCC_PIF_MAX_RAT_NUM             (2)                                /* ��ǰ֧�ֵ�GU���뼼������ */
#endif

#define NAS_MSCC_PIF_CAUSE_NULL              (0)

#define NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM   (20)

#define NAS_MSCC_PIF_MAX_EQUPLMN_NUM         (18)                               /* ��Ч��PLMN�������� */
#define NAS_MSCC_PIF_TDS_ARFCN_MAX_NUM       (9)                                /* TDDƵ���б������� */
#define NAS_MSCC_PIF_LTE_ARFCN_MAX_NUM       (8)                                /* LTEƵ���б������� */


#define NAS_MSCC_PIF_REG_MAX_PLMN_NUM        (8)
#define NAS_MSCC_PIF_REG_MAX_CELL_NUM        (8)


#define NAS_MSCC_PIF_MAX_CFPLMN_NUM          (20)

#define NAS_MSCC_PIF_MAX_OPER_LONG_NAME_LEN                 (100)               /* spn ����ucs2����ʱ��Ҫ�ĳ���Ϊ32�����һ��\0 ���뵽36λ,��Ϊ�����39��long name ,������40*/
#define NAS_MSCC_PIF_MAX_OPER_SHORT_NAME_LEN                (100)               /* spn ����ucs2����ʱ��Ҫ�ĳ���Ϊ32 ,���һ��\0 ���뵽36λ */
#define NAS_MSCC_PIF_MAX_USER_OPLMN_VERSION_LEN             (8)                 /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MSCC_PIF_MAX_GROUP_CFG_OPLMN_DATA_LEN           (250)               /* ��������OPLMN������ֽ���*/

#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_NONE                   (0x00)              /* AT��ѯ�ϱ�  */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV                  (0x01)              /* RXLEV�仯�������ϱ� */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXQUALITY              (0x02)              /* RXQUALITY�仯�������ϱ� */
#define NAS_MSCC_PIF_SCELL_MEAS_TYPE_CELLID                 (0x04)              /* CELL ID�仯�������ϱ� */

#define NAS_MSCC_PIF_MAX_PLMN_NUM                           (256)

#define NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM              (16)
#define NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM               (16)

#define NAS_MSCC_PIF_MAX_EHPLMN_NUM                         (16)                    /* EHPLMN���ĸ��� */
#define NAS_MSCC_PIF_MAX_USERPLMN_NUM                       (100)                   /* USERPLMN���ĸ��� */
#define NAS_MSCC_PIF_MAX_OPERPLMN_NUM                       (256)                   /* OPERPLMN���ĸ��� */


#define NAS_MSCC_PIF_SRV_ACQ_RAT_NUM_MAX                    (3)

#define NAS_MSCC_PIF_MAX_WHITE_LOCK_SID_NUM                 (20)

#define NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM                     (18)
#define NAS_MSCC_PIF_MAX_IMSI_LEN                           (9)                     /* ���IMSI���� */
#define NAS_MSCC_PIF_MAX_DPLMN_NUM                          (256)
#define NAS_MSCC_PIF_INFO_VERSION_LEN                       (9)

#define NAS_MSCC_PIF_MAX_NUM_MSPL_REC                        (24)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/** ****************************************************************************
 * Name        : MSCC_PIF_MSG_TYPE_ENUM_UINT32
 * Description : MSCC������ģ�����ϢID����
 *******************************************************************************/
enum MSCC_PIF_MSG_TYPE_ENUM
{
    /***************************** MMA <-> MSCC *****************************/
    /* MMA����MSCC����Ϣԭ�� */
    ID_MMA_MSCC_START_REQ                               = 0x0001,               /* _H2ASN_MsgChoice MMA_MSCC_START_REQ_STRU */
    ID_MMA_MSCC_SIGN_REPORT_REQ                         = 0x0002,               /* _H2ASN_MsgChoice MMA_MSCC_SIGN_REPORT_REQ_STRU */
    ID_MMA_MSCC_MODE_CHANGE_REQ                         = 0x0003,               /* _H2ASN_MsgChoice MMA_MSCC_MODE_CHANGE_REQ_STRU */
    ID_MMA_MSCC_ATTACH_REQ                              = 0x0004,               /* _H2ASN_MsgChoice MMA_MSCC_ATTACH_REQ_STRU */
    ID_MMA_MSCC_DETACH_REQ                              = 0x0005,               /* _H2ASN_MsgChoice MMA_MSCC_DETACH_REQ_STRU */
    ID_MMA_MSCC_PLMN_LIST_REQ                           = 0x0006,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_LIST_REQ_STRU */
    ID_MMA_MSCC_PLMN_LIST_ABORT_REQ                     = 0x0007,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_LIST_ABORT_REQ_STRU */
    ID_MMA_MSCC_PLMN_USER_RESEL_REQ                     = 0x0008,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_USER_RESEL_REQ_STRU */
    ID_MMA_MSCC_PLMN_SPECIAL_REQ                        = 0x0009,               /* _H2ASN_MsgChoice MMA_MSCC_PLMN_SPECIAL_REQ_STRU */
    ID_MMA_MSCC_POWER_OFF_REQ                           = 0x000A,               /* _H2ASN_MsgChoice MMA_MSCC_POWER_OFF_REQ_STRU */
    ID_MMA_MSCC_SYS_CFG_SET_REQ                         = 0x000B,               /* _H2ASN_MsgChoice MMA_MSCC_SYS_CFG_SET_REQ_STRU */
    ID_MMA_MSCC_SYSTEM_ACQUIRE_REQ                      = 0x000C,               /* _H2ASN_MsgChoice MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU */
    ID_MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ              = 0x000D,               /* _H2ASN_MsgChoice MMA_MSCC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU */
    ID_MMA_MSCC_OM_MAINTAIN_INFO_IND                    = 0x000E,               /* _H2ASN_MsgChoice MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU */


    /* �û�ͨ��CPOL�������UPLMN��Ϣ֪ͨ��MSCC */
    ID_MMA_MSCC_UPDATE_UPLMN_NTF                        = 0x000F,               /* _H2ASN_MsgChoice MMA_MSCC_UPDATE_UPLMN_NTF_STRU */

    ID_MMA_MSCC_EOPLMN_SET_REQ                          = 0x0010,               /* _H2ASN_MsgChoice MMA_MSCC_EOPLMN_SET_REQ_STRU */

    ID_MMA_MSCC_NET_SCAN_REQ                            = 0x0011,               /* _H2ASN_MsgChoice MMA_MSCC_NET_SCAN_REQ_STRU */
    ID_MMA_MSCC_ABORT_NET_SCAN_REQ                      = 0x0012,               /* _H2ASN_MsgChoice MMA_MSCC_ABORT_NET_SCAN_REQ_STRU */

    ID_MMA_MSCC_OTHER_MODEM_INFO_NOTIFY                 = 0x0013,               /* _H2ASN_MsgChoice MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU */

    ID_MMA_MSCC_NCELL_INFO_NOTIFY                       = 0x0014,               /* _H2ASN_MsgChoice MMA_MSCC_NCELL_INFO_NOTIFY_STRU */

    ID_MMA_MSCC_PS_TRANSFER_NOTIFY                      = 0x0015,               /* _H2ASN_MsgChoice MMA_MSCC_PS_TRANSFER_NOTIFY_STRU */

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
    ID_MMA_MSCC_ACQ_REQ                                 = 0x0016,               /* _H2ASN_MsgChoice MMA_MSCC_ACQ_REQ_STRU */
    ID_MMA_MSCC_REG_REQ                                 = 0x0017,               /* _H2ASN_MsgChoice MMA_MSCC_REG_REQ_STRU */
    ID_MMA_MSCC_POWER_SAVE_REQ                          = 0x0018,               /* _H2ASN_MsgChoice MMA_MSCC_POWER_SAVE_REQ_STRU */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */

    ID_MMA_MSCC_SRV_ACQ_REQ                             = 0x0019,               /* _H2ASN_MsgChoice MMA_MSCC_SRV_ACQ_REQ_STRU */
    ID_MMA_MSCC_BEGIN_SESSION_NOTIFY                    = 0x001A,               /* _H2ASN_MsgChoice MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU */
    ID_MMA_MSCC_END_SESSION_NOTIFY                      = 0x001B,               /* _H2ASN_MsgChoice MMA_MSCC_END_SESSION_NOTIFY_STRU */
    ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY                     = 0x001C,               /* _H2ASN_MsgChoice MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU */
    ID_MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY     = 0x001D,               /* _H2ASN_MsgChoice MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU */

    ID_MMA_MSCC_CDMA_MO_CALL_START_NTF                  = 0x001E,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU */
    ID_MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF         = 0x001F,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU */
    ID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF                = 0x0020,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU */
    ID_MMA_MSCC_CDMA_MO_CALL_END_NTF                    = 0x0021,               /* _H2ASN_MsgChoice MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU*/ /**< @sa MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU */
    ID_MMA_MSCC_CFREQ_LOCK_NTF                          = 0x0022,               /* _H2ASN_MsgChoice MMA_MSCC_CFREQ_LOCK_NTF_STRU */
    ID_MMA_MSCC_CDMACSQ_SET_REQ                         = 0x0023,               /* _H2ASN_MsgChoice MMA_MSCC_CDMACSQ_SET_REQ_STRU*/

    ID_MMA_MSCC_CFPLMN_SET_REQ                          = 0x0024,               /* _H2ASN_MsgChoice MMA_MSCC_CFPLMN_SET_REQ_STRU*/
    ID_MMA_MSCC_CFPLMN_QUERY_REQ                        = 0x0025,               /* _H2ASN_MsgChoice MMA_MSCC_CFPLMN_QUERY_REQ_STRU*/
    ID_MMA_MSCC_SDT_CONNECTED_IND                       = 0x0026,               /* _H2ASN_MsgChoice MMCM_OM_MAINTAIN_INFO_IND_STRU*/

    ID_MMA_MSCC_PREF_PLMN_SET_REQ                       = 0x0027,               /* _H2ASN_MsgChoice MMA_MSCC_PREF_PLMN_SET_REQ_STRU*/
    ID_MMA_MSCC_PREF_PLMN_QUERY_REQ                     = 0x0028,               /* _H2ASN_MsgChoice MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU*/

    ID_MMA_MSCC_IMS_START_REQ                           = 0x0029,               /* _H2ASN_MsgChoice MMA_MSCC_IMS_START_REQ_STRU */
    ID_MMA_MSCC_IMS_STOP_REQ                            = 0x002A,               /* _H2ASN_MsgChoice MMA_MSCC_IMS_STOP_REQ_STRU */
    ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND                 = 0x002B,               /* _H2ASN_MsgChoice MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU */
    ID_MMA_MSCC_AUTO_RESEL_SET_REQ                      = 0x002C,               /* _H2ASN_MsgChoice MMA_MSCC_AUTO_RESEL_SET_STRU */

    ID_MMA_MSCC_HANDSET_INFO_QRY_REQ                    = 0x002D,               /* _H2ASN_MsgChoice MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU*/

    ID_MMA_MSCC_GET_GEO_REQ                             = 0x002E,               /* _H2ASN_MsgChoice MMA_MSCC_GET_GEO_REQ_STRU */
    ID_MMA_MSCC_STOP_GET_GEO_REQ                        = 0X002F,               /* _H2ASN_MsgChoice MMA_MSCC_STOP_GET_GEO_REQ_STRU */

    ID_MMA_MSCC_PS_RAT_TYPE_NTF                         = 0x0030,               /* _H2ASN_MsgChoice MMA_MSCC_PS_RAT_TYPE_NTF_STRU */
    ID_MMA_MSCC_QUIT_CALL_BACK_NTF                      = 0x0031,               /* _H2ASN_MsgChoice MMA_MSCC_QUIT_CALL_BACK_NTF_STRU */
    ID_MMA_MSCC_SET_CSIDLIST_REQ                        = 0x0032,               /* _H2ASN_MsgChoice MMA_MSCC_SET_CSIDLIST_REQ_STRU */

    ID_MMA_MSCC_DPLMN_SET_REQ                           = 0x0033,               /* _H2ASN_MsgChoice MMA_MSCC_DPLMN_SET_REQ_STRU */

    ID_MMA_MSCC_CSG_LIST_SEARCH_REQ                     = 0x0034,               /* _H2ASN_MsgChoice MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU */
    ID_MMA_MSCC_CSG_LIST_ABORT_REQ                      = 0x0035,               /* _H2ASN_MsgChoice MMA_MSCC_CSG_LIST_ABORT_REQ_STRU */

    /* MSCC���͸�MMA����Ϣԭ��*/
    ID_MSCC_MMA_START_CNF                               = 0x1001,               /* _H2ASN_MsgChoice MSCC_MMA_START_CNF_STRU */
    ID_MSCC_MMA_3GPP_SYS_INFO_IND                       = 0x1002,               /* _H2ASN_MsgChoice MSCC_MMA_3GPP_SYS_INFO_IND_STRU */
    ID_MSCC_MMA_SERVICE_STATUS_IND                      = 0x1003,               /* _H2ASN_MsgChoice MSCC_MMA_SERVICE_STATUS_IND_STRU */
    ID_MSCC_MMA_MM_INFO_IND                             = 0x1004,               /* _H2ASN_MsgChoice MSCC_MMA_MM_INFO_IND_STRU */
    ID_MSCC_MMA_ATTACH_CNF                              = 0x1005,               /* _H2ASN_MsgChoice MSCC_MMA_ATTACH_CNF_STRU */
    ID_MSCC_MMA_DETACH_CNF                              = 0x1006,               /* _H2ASN_MsgChoice MSCC_MMA_DETACH_CNF_STRU */
    ID_MSCC_MMA_DETACH_IND                              = 0x1007,               /* _H2ASN_MsgChoice MSCC_MMA_DETACH_IND_STRU */
    ID_MSCC_MMA_PLMN_LIST_CNF                           = 0x1008,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_LIST_CNF_STRU */
    ID_MSCC_MMA_PLMN_LIST_REJ                           = 0x1009,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_LIST_REJ_STRU */
    ID_MSCC_MMA_COVERAGE_AREA_IND                       = 0x100A,               /* _H2ASN_MsgChoice MSCC_MMA_COVERAGE_AREA_IND_STRU */
    ID_MSCC_MMA_POWER_OFF_CNF                           = 0x100B,               /* _H2ASN_MsgChoice MSCC_MMA_POWER_OFF_CNF_STRU */
    ID_MSCC_MMA_RSSI_IND                                = 0x100C,               /* _H2ASN_MsgChoice MSCC_MMA_RSSI_IND_STRU */
    ID_MSCC_MMA_PLMN_SPECIAL_SEL_CNF                    = 0x100D,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU */
    ID_MSCC_MMA_DATATRAN_ATTRI_IND                      = 0x100E,               /* _H2ASN_MsgChoice MSCC_MMA_DATATRAN_ATTRI_IND_STRU */
    ID_MSCC_MMA_SYS_CFG_CNF                             = 0x100F,               /* _H2ASN_MsgChoice MSCC_MMA_SYS_CFG_SET_CNF_STRU */
    ID_MSCC_MMA_SYSTEM_ACQUIRE_END_IND                  = 0x1010,               /* _H2ASN_MsgChoice MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU */
    ID_MSCC_MMA_PLMN_LIST_ABORT_CNF                     = 0x1011,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU */
    ID_MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF              = 0x1012,               /* _H2ASN_MsgChoice MSCC_MMA_SPEC_PLMN_SEARCH_ABORT_CNF_STRU */
    ID_MSCC_MMA_UMTS_CIPHER_INFO_IND                    = 0x1013,               /* _H2ASN_MsgChoice MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU */
    ID_MSCC_MMA_GPRS_CIPHER_INFO_IND                    = 0x1014,               /* _H2ASN_MsgChoice MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU */
    ID_MSCC_MMA_PLMN_SPECIAL_SEL_REJ                    = 0x1015,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_SPECIAL_SEL_REJ_STRU */
    ID_MSCC_MMA_AC_INFO_CHANGE_IND                      = 0x1016,               /* _H2ASN_MsgChoice MSCC_MMA_AC_INFO_CHANGE_IND_STRU */
    ID_MSCC_MMA_PLMN_RESEL_CNF                          = 0x1017,               /* _H2ASN_MsgChoice MSCC_MMA_PLMN_RESEL_CNF_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    ID_MSCC_MMA_REG_RESULT_IND                          = 0x1018,               /* _H2ASN_MsgChoice MSCC_MMA_REG_RESULT_IND_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    ID_MSCC_MMA_SYSTEM_ACQUIRE_START_IND                = 0x1019,               /* _H2ASN_MsgChoice MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU */

    ID_MSCC_MMA_EOPLMN_SET_CNF                          = 0x101A,               /* _H2ASN_MsgChoice MSCC_MMA_EOPLMN_SET_CNF_STRU */
    ID_MSCC_MMA_USIM_AUTH_FAIL_IND                      = 0x101B,               /* _H2ASN_MsgChoice MSCC_MMA_USIM_AUTH_FAIL_IND_STRU */

    ID_MSCC_MMA_NET_SCAN_CNF                            = 0x101C,               /* _H2ASN_MsgChoice MSCC_MMA_NET_SCAN_CNF_STRU */
    ID_MSCC_MMA_ABORT_NET_SCAN_CNF                      = 0x101D,               /* _H2ASN_MsgChoice MSCC_MMA_ABORT_NET_SCAN_CNF_STRU */

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-9, begin */
    ID_MSCC_MMA_NETWORK_CAPABILITY_INFO_IND             = 0x101E,               /* _H2ASN_MsgChoice MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU */
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-9, end */
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    ID_MSCC_MMA_CAMP_ON_IND                             = 0x101F,               /* _H2ASN_MsgChoice MSCC_MMA_CAMP_ON_IND_STRU_STRU */
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    ID_MSCC_MMA_EPLMN_INFO_IND                          = 0x1020,               /* _H2ASN_MsgChoice MSCC_MMA_EPLMN_INFO_IND_STRU */

    ID_MSCC_MMA_CS_SERVICE_CONN_STATUS_IND              = 0x1021,               /* _H2ASN_MsgChoice MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU */

    ID_MSCC_MMA_SRV_REJ_IND                             = 0x1022,               /* _H2ASN_MsgChoice MSCC_MMA_SERV_REJ_IND_STRU */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
    ID_MSCC_MMA_ACQ_CNF                                 = 0x1023,               /* _H2ASN_MsgChoice MSCC_MMA_ACQ_CNF_STRU */
    ID_MSCC_MMA_REG_CNF                                 = 0x1024,               /* _H2ASN_MsgChoice MSCC_MMA_REG_CNF_STRU */
    ID_MSCC_MMA_POWER_SAVE_CNF                          = 0x1025,               /* _H2ASN_MsgChoice MSCC_MMA_POWER_SAVE_CNF_STRU */
    ID_MSCC_MMA_ACQ_IND                                 = 0x1026,               /* _H2ASN_MsgChoice MSCC_MMA_ACQ_IND_STRU */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */


    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
    ID_MSCC_MMA_PS_SERVICE_CONN_STATUS_IND              = 0x1027,               /* _H2ASN_MsgChoice MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU */
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
    ID_MSCC_MMA_RF_AVAILABLE_IND                        = 0x1028,               /* _H2ASN_MsgChoice MSCC_MMA_RF_AVAILABLE_IND_STRU */
    ID_MSCC_MMA_SRV_ACQ_CNF                             = 0x1029,               /* _H2ASN_MsgChoice MSCC_MMA_SRV_ACQ_CNF_STRU */
    ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND           = 0x102A,               /* _H2ASN_MsgChoice MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU */
    ID_MSCC_MMA_IMS_VOICE_CAP_IND                       = 0x102B,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_VOICE_CAP_IND_STRU */

    ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND              = 0x102C,               /* _H2ASN_MsgChoice MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU */
    ID_MSCC_MMA_CDMACSQ_SET_CNF                         = 0x102D,               /* _H2ASN_MsgChoice MSCC_MMA_CDMACSQ_SET_CNF_STRU*/
    ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND              = 0x102E,               /* _H2ASN_MsgChoice MSCC_MMA_CDMACSQ_IND_STRU*/

    ID_MSCC_MMA_HRPD_SERVICE_STATUS_IND                 = 0x102F,                /* _H2ASN_MsgChoice MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU*/

    ID_MSCC_MMA_CFPLMN_SET_CNF                          = 0x1030,               /* _H2ASN_MsgChoice MSCC_MMA_CFPLMN_SET_CNF_STRU*/
    ID_MSCC_MMA_CFPLMN_QUERY_CNF                        = 0x1031,               /* _H2ASN_MsgChoice MSCC_MMA_CFPLMN_QUERY_CNF_STRU*/

    ID_MSCC_MMA_PREF_PLMN_SET_CNF                       = 0x1032,               /* _H2ASN_MsgChoice MSCC_MMA_PREF_PLMN_SET_CNF_STRU*/
    ID_MSCC_MMA_PREF_PLMN_QUERY_CNF                     = 0x1033,               /* _H2ASN_MsgChoice MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU*/

    ID_MSCC_MMA_HRPD_OVERHEAD_MSG_IND                   = 0x1034,                /* _H2ASN_MsgChoice MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU*/
    ID_MSCC_MMA_HRPD_SYS_ACQ_CNF                        = 0x1035,                /* _H2ASN_MsgChoice MSCC_MMA_HRPD_SYS_ACQ_CNF_STRU*/

    ID_MSCC_MMA_1X_SYSTEM_TIME_IND                      = 0x1036,               /* _H2ASN_MsgChoice MSCC_MMA_1X_SYSTEM_TIME_IND_STRU */

    ID_MSCC_MMA_IMS_SWITCH_STATE_IND                    = 0x1038,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_SWITCH_STATE_IND_STRU */
    ID_MSCC_MMA_IMS_START_CNF                           = 0x1039,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_START_CNF_STRU */
    ID_MSCC_MMA_IMS_STOP_CNF                            = 0x103A,               /* _H2ASN_MsgChoice MSCC_MMA_IMS_STOP_CNF_STRU */

    ID_MSCC_MMA_INTERSYS_START_IND                      = 0x103B,               /* _H2ASN_MsgChoice MSCC_MMA_INTERSYS_START_IND_STRU */
    ID_MSCC_MMA_INTERSYS_END_IND                        = 0x103C,               /* _H2ASN_MsgChoice MSCC_MMA_INTERSYS_END_IND_STRU */



    ID_MSCC_MMA_HANDSET_INFO_QRY_CNF                    = 0x103D,               /* _H2ASN_MsgChoice MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU */

    ID_MSCC_MMA_GET_GEO_CNF                             = 0x103E,               /* _H2ASN_MsgChoice MSCC_MMA_GET_GEO_CNF_STRU */
    ID_MSCC_MMA_STOP_GET_GEO_CNF                        = 0x103F,               /* _H2ASN_MsgChoice MSCC_MMA_STOP_GET_GEO_CNF_STRU */

    ID_MSCC_MMA_1X_SID_NID_IND                          = 0x1042,               /* _H2ASN_MsgChoice MSCC_MMA_1X_SID_NID_IND_STRU */
    ID_MSCC_MMA_SET_CSIDLIST_CNF                        = 0x1043,               /* _H2ASN_MsgChoice MSCC_MMA_SET_CSIDLIST_CNF_STRU */
    ID_MSCC_MMA_1X_EMC_CALL_BACK_IND                    = 0x1044,               /* _H2ASN_MsgChoice MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU */
    ID_MSCC_MMA_SYNC_SERVICE_AVAIL_IND                  = 0x1045,               /* _H2ASN_MsgChoice MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU */

    ID_MSCC_MMA_SRCHED_PLMN_INFO_IND                    = 0x1046,

    ID_MSCC_MMA_1X_UE_STATUS_IND                        = 0x1047,               /* _H2ASN_MsgChoice MSCC_MMA_UE_STATE_IND_STRU */
    ID_MMA_MSCC_HDR_CSQ_SET_REQ                         = 0x1048,               /* _H2ASN_MsgChoice MMA_MSCC_HDR_CSQ_SET_REQ_STRU*/
    ID_MSCC_MMA_HDR_CSQ_SET_CNF                         = 0x1049,               /* _H2ASN_MsgChoice MSCC_MMA_HDR_CSQ_SET_CNF_STRU*/
    ID_MSCC_MMA_HDR_CSQ_QUALITY_IND                     = 0x104A,               /* _H2ASN_MsgChoice MSCC_MMA_HDR_CSQ_IND_STRU*/

    ID_MSCC_MMA_DPLMN_SET_CNF                           = 0x104B,               /* _H2ASN_MsgChoice MSCC_MMA_DPLMN_SET_CNF_STRU */

    ID_MSCC_MMA_CSG_LIST_SEARCH_CNF                     = 0x104C,               /* _H2ASN_MsgChoice MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU */
    ID_MSCC_MMA_CSG_LIST_ABORT_CNF                      = 0x104D,               /* _H2ASN_MsgChoice MSCC_MMA_CSG_LIST_ABORT_CNF_STRU */
    ID_MSCC_MMA_CSG_LIST_REJ                            = 0x104E,               /* _H2ASN_MsgChoice MSCC_MMA_CSG_LIST_REJ_STRU */

    ID_MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND            = 0x104F,               /* _H2ASN_MsgChoice MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU*/

    /***************************** MSCC <-> XSD *****************************/
    ID_MSCC_XSD_MSG_BASE                                = 0x2000,

    ID_MSCC_XSD_START_REQ                               = ID_MSCC_XSD_MSG_BASE + 0x0000,    /* _H2ASN_MsgChoice MSCC_XSD_START_REQ_STRU*/ /**< @sa MSCC_XSD_START_REQ_STRU */
    ID_XSD_MSCC_START_CNF                               = ID_MSCC_XSD_MSG_BASE + 0x0001,    /* _H2ASN_MsgChoice XSD_MSCC_START_CNF_STRU*/ /**< @sa XSD_MSCC_START_CNF_STRU */
    ID_MSCC_XSD_POWER_OFF_REQ                           = ID_MSCC_XSD_MSG_BASE + 0x0002,    /* _H2ASN_MsgChoice MSCC_XSD_POWER_OFF_REQ_STRU*/ /**< @sa MSCC_XSD_POWER_OFF_REQ_STRU */
    ID_XSD_MSCC_POWER_OFF_CNF                           = ID_MSCC_XSD_MSG_BASE + 0x0003,    /* _H2ASN_MsgChoice XSD_MSCC_POWER_OFF_CNF_STRU*/ /**< @sa XSD_MSCC_POWER_OFF_CNF_STRU */
    ID_MSCC_XSD_MO_CALL_START_NTF                       = ID_MSCC_XSD_MSG_BASE + 0x0004,    /* _H2ASN_MsgChoice MSCC_XSD_MO_CALL_START_NTF_STRU*/ /**< @sa MSCC_XSD_MO_CALL_START_NTF_STRU */
    ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF          = ID_MSCC_XSD_MSG_BASE + 0x0005,    /* _H2ASN_MsgChoice MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*/ /**< @sa MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU */
    ID_MSCC_XSD_MO_CALL_SUCCESS_NTF                     = ID_MSCC_XSD_MSG_BASE + 0x0006,    /* _H2ASN_MsgChoice MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU*/ /**< @sa MSCC_XSD_CALL_SUCCESS_NTF_STRU */
    ID_MSCC_XSD_MO_CALL_END_NTF                         = ID_MSCC_XSD_MSG_BASE + 0x0007,    /* _H2ASN_MsgChoice MSCC_XSD_1X_MO_CALL_END_NTF_STRU*/ /**< @sa MSCC_XSD_CALL_END_NTF_STRU */
    ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ                      = ID_MSCC_XSD_MSG_BASE + 0x0008,    /* _H2ASN_MsgChoice MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU*/ /**< @sa MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU */
    ID_XSD_MSCC_SYSTEM_ACQUIRE_CNF                      = ID_MSCC_XSD_MSG_BASE + 0x0009,    /* _H2ASN_MsgChoice XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU*/ /**< @sa XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU */
    ID_XSD_MSCC_SYSTEM_ACQUIRE_IND                      = ID_MSCC_XSD_MSG_BASE + 0x000A,    /* _H2ASN_MsgChoice XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU*/ /**< @sa XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU */
    ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND                = ID_MSCC_XSD_MSG_BASE + 0x000B,    /* _H2ASN_MsgChoice XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU*/ /**< @sa XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU */
    ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND              = ID_MSCC_XSD_MSG_BASE + 0x000C,    /* _H2ASN_MsgChoice XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU */
    ID_MSCC_XSD_CFREQLOCK_NTF                           = ID_MSCC_XSD_MSG_BASE + 0x000D,    /* _H2ASN_MsgChoice MSCC_XSD_CFREQ_LOCK_NTF_STRU */
    ID_MSCC_XSD_CDMACSQ_SET_REQ                         = ID_MSCC_XSD_MSG_BASE + 0x000E,    /* _H2ASN_MsgChoice MSCC_XSD_CDMACSQ_SET_REQ_STRU*/
    ID_XSD_MSCC_CDMACSQ_SET_CNF                         = ID_MSCC_XSD_MSG_BASE + 0x000F,    /* _H2ASN_MsgChoice XSD_MSCC_CDMACSQ_SET_CNF_STRU*/
    ID_XSD_MSCC_CDMACSQ_SIGNAL_QUALITY_IND              = ID_MSCC_XSD_MSG_BASE + 0x0010,    /* _H2ASN_MsgChoice XSD_MSCC_CDMACSQ_IND_STRU*/
    ID_XSD_MSCC_1X_SYSTEM_TIME_IND                      = ID_MSCC_XSD_MSG_BASE + 0x0011,    /* _H2ASN_MsgChoice XSD_MSCC_1X_SYSTEM_TIME_IND_STRU*/

    ID_MSCC_XSD_POWER_SAVE_REQ                          = ID_MSCC_XSD_MSG_BASE + 0x0012,    /* _H2ASN_MsgChoice MSCC_XSD_POWER_SAVE_REQ_STRU */
    ID_XSD_MSCC_POWER_SAVE_CNF                          = ID_MSCC_XSD_MSG_BASE + 0x0013,    /* _H2ASN_MsgChoice XSD_MSCC_POWER_SAVE_CNF_STRU */
    ID_MSCC_XSD_CAS_STATUS_IND                          = ID_MSCC_XSD_MSG_BASE + 0x0014,    /* _H2ASN_MsgChoice MSCC_XSD_CAS_STATUS_IND_STRU */
    ID_MSCC_XSD_SYS_CFG_REQ                             = ID_MSCC_XSD_MSG_BASE + 0x0015,    /* _H2ASN_MsgChoice MSCC_XSD_SYS_CFG_REQ_STRU */
    ID_XSD_MSCC_SYS_CFG_CNF                             = ID_MSCC_XSD_MSG_BASE + 0x0016,    /* _H2ASN_MsgChoice XSD_MSCC_SYS_CFG_CNF_STRU */

    ID_XSD_MSCC_RF_AVAILABLE_IND                        = ID_MSCC_XSD_MSG_BASE + 0x0017,    /* _H2ASN_MsgChoice NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU */

    ID_MSCC_XSD_SRV_ACQ_REQ                             = ID_MSCC_XSD_MSG_BASE + 0x0018,    /* _H2ASN_MsgChoice MSCC_XSD_SRV_ACQ_REQ_STRU */
    ID_XSD_MSCC_SRV_ACQ_CNF                             = ID_MSCC_XSD_MSG_BASE + 0x0019,    /* _H2ASN_MsgChoice XSD_MSCC_SRV_ACQ_CNF_STRU */
    ID_MSCC_XSD_BEGIN_SESSION_NOTIFY                    = ID_MSCC_XSD_MSG_BASE + 0x001A,    /* _H2ASN_MsgChoice MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU */
    ID_MSCC_XSD_END_SESSION_NOTIFY                      = ID_MSCC_XSD_MSG_BASE + 0x001B,    /* _H2ASN_MsgChoice MSCC_XSD_END_SESSION_NOTIFY_STRU */

    ID_MSCC_XSD_HANDSET_INFO_QRY_REQ                    = ID_MSCC_XSD_MSG_BASE + 0x001C,    /* _H2ASN_MsgChoice MSCC_XSD_HANDSET_INFO_QRY_STRU*/
    ID_XSD_MSCC_HANDSET_INFO_QRY_CNF                    = ID_MSCC_XSD_MSG_BASE + 0x001D,    /* _H2ASN_MsgChoice XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU*/

    ID_XSD_MSCC_EMC_CALLBACK_IND                        = ID_MSCC_XSD_MSG_BASE + 0x001E,    /* _H2ASN_MsgChoice XSD_MSCC_EMC_CALLBACK_IND_STRU */
    ID_MSCC_XSD_END_EMC_CALLBACK_NTF                    = ID_MSCC_XSD_MSG_BASE + 0x001F,    /* _H2ASN_MsgChoice MSCC_XSD_END_EMC_CALLBACK_NTF_STRU */

    ID_XSD_MSCC_SID_NID_IND                             = ID_MSCC_XSD_MSG_BASE + 0x0020,    /* _H2ASN_MsgChoice MSCC_XSD_SID_IND_STRU*/

    ID_MSCC_XSD_SET_CSIDLIST_REQ                        = ID_MSCC_XSD_MSG_BASE + 0x0021,    /* _H2ASN_MsgChoice MSCC_XSD_SET_CSIDLIST_REQ_STRU*/
    ID_XSD_MSCC_SET_CSIDLIST_CNF                        = ID_MSCC_XSD_MSG_BASE + 0x0022,    /* _H2ASN_MsgChoice XSD_MSCC_SET_CSIDLIST_CNF_STRU*/
    ID_XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND              = ID_MSCC_XSD_MSG_BASE + 0x0023,    /* _H2ASN_MsgChoice XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU*/

    ID_XSD_MSCC_CDMA_UE_STATUS_IND                      = ID_MSCC_XSD_MSG_BASE + 0x0024,    /* _H2ASN_MsgChoice XSD_MSCC_UE_STATE_IND_STRU*/

    ID_XSD_MSCC_1X_NO_SERVICE_IND                       = ID_MSCC_XSD_MSG_BASE + 0x0025,    /* _H2ASN_MsgChoice XSD_MSCC_1X_NO_SERVICE_IND_STRU*/

    /***************************** MSCC <-> HSD *****************************/
    ID_MSCC_HSD_MSG_BASE                                = 0x3000,
    ID_MSCC_HSD_START_REQ                               = ID_MSCC_HSD_MSG_BASE + 0x0000,    /*_H2ASN_MsgChoice MSCC_HSD_START_REQ_STRU */
    ID_HSD_MSCC_START_CNF                               = ID_MSCC_HSD_MSG_BASE + 0x0001,    /*_H2ASN_MsgChoice HSD_MSCC_START_CNF_STRU */
    ID_MSCC_HSD_POWER_OFF_REQ                           = ID_MSCC_HSD_MSG_BASE + 0x0002,    /*_H2ASN_MsgChoice MSCC_HSD_POWER_OFF_REQ_STRU */
    ID_HSD_MSCC_POWER_OFF_CNF                           = ID_MSCC_HSD_MSG_BASE + 0x0003,    /*_H2ASN_MsgChoice HSD_MSCC_POWER_OFF_CNF_STRU */
    ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ                      = ID_MSCC_HSD_MSG_BASE + 0x0004,    /*_H2ASN_MsgChoice MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU */
    ID_HSD_MSCC_SYSTEM_ACQUIRE_START_IND                = ID_MSCC_HSD_MSG_BASE + 0x0005,    /*_H2ASN_MsgChoice HSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU */
    ID_HSD_MSCC_SYSTEM_ACQUIRE_CNF                      = ID_MSCC_HSD_MSG_BASE + 0x0006,    /*_H2ASN_MsgChoice HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU */
    ID_HSD_MSCC_SYSTEM_ACQUIRE_END_IND                  = ID_MSCC_HSD_MSG_BASE + 0x0007,    /*_H2ASN_MsgChoice HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU */
    ID_MSCC_HSD_DATA_CALL_START_NTF                     = ID_MSCC_HSD_MSG_BASE + 0x0008,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_START_NTF_STRU */
    ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ            = ID_MSCC_HSD_MSG_BASE + 0x0009,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU */
    ID_HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF            = ID_MSCC_HSD_MSG_BASE + 0x000A,    /*_H2ASN_MsgChoice HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU */
    ID_MSCC_HSD_DATA_CALL_SUCC_NTF                      = ID_MSCC_HSD_MSG_BASE + 0x000B,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_SUCC_NTF_STRU */
    ID_MSCC_HSD_DATA_CALL_END_NTF                       = ID_MSCC_HSD_MSG_BASE + 0x000C,    /*_H2ASN_MsgChoice MSCC_HSD_DATA_CALL_END_NTF_STRU */
    ID_HSD_MSCC_HRPD_IRAT_TO_LTE_NTF                    = ID_MSCC_HSD_MSG_BASE + 0x000D,    /*_H2ASN_MsgChoice HSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU */

    ID_HSD_MSCC_SESSION_NEG_RSLT_IND                    = ID_MSCC_HSD_MSG_BASE + 0x000E,    /*_H2ASN_MsgChoice HSD_MSCC_SESSION_NEG_RSLT_IND_STRU */
    ID_HSD_MSCC_OVERHEAD_MSG_IND                        = ID_MSCC_HSD_MSG_BASE + 0x000F,    /*_H2ASN_MsgChoice HSD_MSCC_OVERHEAD_MSG_IND_STRU */

    ID_MSCC_HSD_1X_SYS_CHANGE_IND                       = ID_MSCC_HSD_MSG_BASE + 0x0010,    /* _H2ASN_MsgChoice MSCC_HSD_1X_SYS_CHANGE_IND_STRU */
    ID_MSCC_HSD_DISABLE_LTE_NTF                         = ID_MSCC_HSD_MSG_BASE + 0x0011,    /* _H2ASN_MsgChoice MSCC_HSD_DISABLE_LTE_NTF_STRU */
    ID_HSD_MSCC_INTERSYS_START_IND                      = ID_MSCC_HSD_MSG_BASE + 0x0012,    /* _H2ASN_MsgChoice HSD_MSCC_INTERSYS_START_IND_STRU */
    ID_HSD_MSCC_INTERSYS_END_IND                        = ID_MSCC_HSD_MSG_BASE + 0x0013,    /* _H2ASN_MsgChoice HSD_MSCC_INTERSYS_END_IND_STRU */

    ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ                   = ID_MSCC_HSD_MSG_BASE + 0x0014,    /* _H2ASN_MsgChoice MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU */
    ID_HSD_MSCC_QRY_HRPD_SYS_INFO_CNF                   = ID_MSCC_HSD_MSG_BASE + 0x0015,    /* _H2ASN_MsgChoice HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU */
    ID_MSCC_HSD_BG_SEARCH_REQ                           = ID_MSCC_HSD_MSG_BASE + 0x0016,    /* _H2ASN_MsgChoice MSCC_HSD_BG_SEARCH_REQ_STRU */
    ID_HSD_MSCC_BG_SEARCH_CNF                           = ID_MSCC_HSD_MSG_BASE + 0x0017,    /* _H2ASN_MsgChoice HSD_MSCC_BG_SEARCH_CNF_STRU */
    ID_MSCC_HSD_SYS_CFG_REQ                             = ID_MSCC_HSD_MSG_BASE + 0x0018,    /* _H2ASN_MsgChoice MSCC_HSD_SYS_CFG_REQ_STRU */
    ID_HSD_MSCC_SYS_CFG_CNF                             = ID_MSCC_HSD_MSG_BASE + 0x0019,    /* _H2ASN_MsgChoice HSD_MSCC_SYS_CFG_CNF_STRU */
    ID_HSD_MSCC_SYSTEM_SYNC_IND                         = ID_MSCC_HSD_MSG_BASE + 0x001A,    /* _H2ASN_MsgChoice HSD_MSCC_SYSTEM_SYNC_IND_STRU */
    ID_HSD_MSCC_SESSION_INFO_IND                        = ID_MSCC_HSD_MSG_BASE + 0x001B,    /* _H2ASN_MsgChoice HSD_MSCC_SESSION_INFO_IND_STRU */
    ID_MSCC_HSD_POWER_SAVE_REQ                          = ID_MSCC_HSD_MSG_BASE + 0x001C,    /* _H2ASN_MsgChoice MSCC_HSD_POWER_SAVE_REQ_STRU */
    ID_HSD_MSCC_POWER_SAVE_CNF                          = ID_MSCC_HSD_MSG_BASE + 0x001D,    /* _H2ASN_MsgChoice HSD_MSCC_POWER_SAVE_CNF_STRU */
    ID_HSD_MSCC_CAS_STATUS_IND                          = ID_MSCC_HSD_MSG_BASE + 0x001E,    /* _H2ASN_MsgChoice HSD_MSCC_CAS_STATUS_IND_STRU */
    ID_MSCC_HSD_STOP_BG_SEARCH_REQ                      = ID_MSCC_HSD_MSG_BASE + 0x001F,    /* _H2ASN_MsgChoice MSCC_HSD_STOP_BG_SEARCH_REQ_STRU */
    ID_HSD_MSCC_STOP_BG_SEARCH_CNF                      = ID_MSCC_HSD_MSG_BASE + 0x0020,    /* _H2ASN_MsgChoice HSD_MSCC_STOP_BG_SEARCH_CNF_STRU */

    ID_HSD_MSCC_RF_AVAILABLE_IND                        = ID_MSCC_HSD_MSG_BASE + 0x0021,    /* _H2ASN_MsgChoice NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU */

    ID_MSCC_HSD_SRV_ACQ_REQ                             = ID_MSCC_HSD_MSG_BASE + 0x0022,    /* _H2ASN_MsgChoice MSCC_HSD_SRV_ACQ_REQ_STRU */
    ID_HSD_MSCC_SRV_ACQ_CNF                             = ID_MSCC_HSD_MSG_BASE + 0x0023,    /* _H2ASN_MsgChoice HSD_MSCC_SRV_ACQ_CNF_STRU */
    ID_MSCC_HSD_BEGIN_SESSION_NOTIFY                    = ID_MSCC_HSD_MSG_BASE + 0x0024,    /* _H2ASN_MsgChoice MSCC_HSD_BEGIN_SESSION_NOTIFY_STRU */
    ID_MSCC_HSD_END_SESSION_NOTIFY                      = ID_MSCC_HSD_MSG_BASE + 0x0025,    /* _H2ASN_MsgChoice MSCC_HSD_END_SESSION_NOTIFY_STRU */

    ID_MSCC_HSD_CFREQLOCK_NTF                           = ID_MSCC_HSD_MSG_BASE + 0x0026,    /* _H2ASN_MsgChoice NAS_MSCC_SndHsdCfreqLockNtf */

    ID_HSD_MSCC_HRPD_NO_SERVICE_IND                     = ID_MSCC_HSD_MSG_BASE + 0x0027,    /* _H2ASN_MsgChoice HSD_MSCC_HRPD_NO_SERVICE_IND_STRU */
    ID_MSCC_HSD_HDR_CSQ_SET_REQ                         = ID_MSCC_HSD_MSG_BASE + 0x0028,    /* _H2ASN_MsgChoice MSCC_HSD_HDR_CSQ_SET_REQ_STRU */
    ID_HSD_MSCC_HDR_CSQ_SET_CNF                         = ID_MSCC_HSD_MSG_BASE + 0x0029,    /* _H2ASN_MsgChoice HSD_MSCC_HDR_CSQ_SET_CNF_STRU */
    ID_HSD_MSCC_HDR_CSQ_IND                             = ID_MSCC_HSD_MSG_BASE + 0x002A,    /* _H2ASN_MsgChoice HSD_MSCC_HDR_CSQ_IND_STRU */


    /***************************** MSCC <-> MMC *****************************/
    ID_MSCC_MMC_MSG_BASE                                = 0x4000,
    /* MSCC����MMC����Ϣԭ�� */
    ID_MSCC_MMC_START_REQ                               = ID_MSCC_MMC_MSG_BASE + 0,     /* _H2ASN_MsgChoice MSCC_MMC_START_REQ_STRU */
    ID_MSCC_MMC_SIGN_REPORT_REQ                         = ID_MSCC_MMC_MSG_BASE + 2,     /* _H2ASN_MsgChoice MSCC_MMC_SIGN_REPORT_REQ_STRU */
    ID_MSCC_MMC_MODE_CHANGE_REQ                         = ID_MSCC_MMC_MSG_BASE + 4,     /* _H2ASN_MsgChoice MSCC_MMC_MODE_CHANGE_REQ_STRU */
    ID_MSCC_MMC_ATTACH_REQ                              = ID_MSCC_MMC_MSG_BASE + 6,     /* _H2ASN_MsgChoice MSCC_MMC_ATTACH_REQ_STRU */
    ID_MSCC_MMC_DETACH_REQ                              = ID_MSCC_MMC_MSG_BASE + 8,     /* _H2ASN_MsgChoice MSCC_MMC_DETACH_REQ_STRU */
    ID_MSCC_MMC_PLMN_LIST_REQ                           = ID_MSCC_MMC_MSG_BASE + 10,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_LIST_REQ_STRU */
    ID_MSCC_MMC_PLMN_LIST_ABORT_REQ                     = ID_MSCC_MMC_MSG_BASE + 12,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_LIST_ABORT_REQ_STRU */
    ID_MSCC_MMC_PLMN_USER_RESEL_REQ                     = ID_MSCC_MMC_MSG_BASE + 14,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_USER_RESEL_REQ_STRU */
    ID_MSCC_MMC_PLMN_SPECIAL_REQ                        = ID_MSCC_MMC_MSG_BASE + 16,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_SPECIAL_REQ_STRU */
    ID_MSCC_MMC_POWER_OFF_REQ                           = ID_MSCC_MMC_MSG_BASE + 18,    /* _H2ASN_MsgChoice MSCC_MMC_POWER_OFF_REQ_STRU */
    ID_MSCC_MMC_SYS_CFG_SET_REQ                         = ID_MSCC_MMC_MSG_BASE + 20,    /* _H2ASN_MsgChoice MSCC_MMC_SYS_CFG_SET_REQ_STRU */
    ID_MSCC_MMC_PLMN_SEARCH_REQ                         = ID_MSCC_MMC_MSG_BASE + 22,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_SEARCH_REQ_STRU */
    ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ              = ID_MSCC_MMC_MSG_BASE + 24,    /* _H2ASN_MsgChoice MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ_STRU */
    ID_MSCC_MMC_OM_MAINTAIN_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 26,    /* _H2ASN_MsgChoice MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU */


    /* �û�ͨ��CPOL�������UPLMN��Ϣ֪ͨ��MMC */
    ID_MSCC_MMC_UPDATE_UPLMN_NTF                        = ID_MSCC_MMC_MSG_BASE + 28,    /* _H2ASN_MsgChoice MSCC_MMC_UPDATE_UPLMN_NTF_STRU */

    ID_MSCC_MMC_EOPLMN_SET_REQ                          = ID_MSCC_MMC_MSG_BASE + 30,    /* _H2ASN_MsgChoice MSCC_MMC_EOPLMN_SET_REQ_STRU */

    ID_MSCC_MMC_NET_SCAN_REQ                            = ID_MSCC_MMC_MSG_BASE + 32,    /* _H2ASN_MsgChoice MSCC_MMC_NET_SCAN_REQ_STRU */
    ID_MSCC_MMC_ABORT_NET_SCAN_REQ                      = ID_MSCC_MMC_MSG_BASE + 34,    /* _H2ASN_MsgChoice MSCC_MMC_ABORT_NET_SCAN_REQ_STRU */

    ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY                 = ID_MSCC_MMC_MSG_BASE + 36,    /* _H2ASN_MsgChoice MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU */

    ID_MSCC_MMC_NCELL_INFO_NOTIFY                       = ID_MSCC_MMC_MSG_BASE + 38,    /* _H2ASN_MsgChoice MSCC_MMC_NCELL_INFO_NOTIFY_STRU */

    ID_MSCC_MMC_PS_TRANSFER_NOTIFY                      = ID_MSCC_MMC_MSG_BASE + 40,    /* _H2ASN_MsgChoice MSCC_MMC_PS_TRANSFER_NOTIFY_STRU */
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-2, begin */
    ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY                    = ID_MSCC_MMC_MSG_BASE + 42,    /* _H2ASN_MsgChoice MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU */
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-2, end */

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
    ID_MSCC_MMC_ACQ_REQ                                 = ID_MSCC_MMC_MSG_BASE + 44,    /* _H2ASN_MsgChoice MSCC_MMC_ACQ_REQ_STRU */
    ID_MSCC_MMC_REG_REQ                                 = ID_MSCC_MMC_MSG_BASE + 46,    /* _H2ASN_MsgChoice MSCC_MMC_REG_REQ_STRU */
    ID_MSCC_MMC_POWER_SAVE_REQ                          = ID_MSCC_MMC_MSG_BASE + 48,    /* _H2ASN_MsgChoice MSCC_MMC_POWER_SAVE_REQ_STRU */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */

    ID_MSCC_MMC_SRV_ACQ_REQ                             = ID_MSCC_MMC_MSG_BASE + 50,    /* _H2ASN_MsgChoice MSCC_MMC_SRV_ACQ_REQ_STRU */
    ID_MSCC_MMC_BEGIN_SESSION_NOTIFY                    = ID_MSCC_MMC_MSG_BASE + 52,    /* _H2ASN_MsgChoice MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU */
    ID_MSCC_MMC_END_SESSION_NOTIFY                      = ID_MSCC_MMC_MSG_BASE + 54,    /* _H2ASN_MsgChoice MSCC_MMC_END_SESSION_NOTIFY_STRU */
    ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY                     = ID_MSCC_MMC_MSG_BASE + 56,    /* _H2ASN_MsgChoice MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU */
    ID_MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY     = ID_MSCC_MMC_MSG_BASE + 58,    /* _H2ASN_MsgChoice MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU */

    ID_MSCC_MMC_CFPLMN_SET_REQ                          = ID_MSCC_MMC_MSG_BASE + 60,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_SET_REQ_STRU */
    ID_MSCC_MMC_CFPLMN_QUERY_REQ                        = ID_MSCC_MMC_MSG_BASE + 62,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_SET_REQ_STRU */
    ID_MSCC_MMC_SDT_CONNECTED_IND                       = ID_MSCC_MMC_MSG_BASE + 64,    /* _H2ASN_MsgChoice MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU */

    ID_MSCC_MMC_PREF_PLMN_SET_REQ                       = ID_MSCC_MMC_MSG_BASE + 66,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_SET_REQ_STRU */
    ID_MSCC_MMC_PREF_PLMN_QUERY_REQ                     = ID_MSCC_MMC_MSG_BASE + 68,    /* _H2ASN_MsgChoice MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU */

    ID_MSCC_MMC_IMS_SWITCH_STATE_IND                    = ID_MSCC_MMC_MSG_BASE + 70,    /* _H2ASN_MsgChoice MSCC_MMC_IMS_SWITCH_STATE_IND_STRU */
    ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND                 = ID_MSCC_MMC_MSG_BASE + 72,    /* _H2ASN_MsgChoice MSCC_MMC_VOICE_DOMAIN_CHANGE_IND_STRU */

    ID_MSCC_MMC_BG_SEARCH_REQ                           = ID_MSCC_MMC_MSG_BASE + 74,    /* _H2ASN_MsgChoice MSCC_MMC_BG_SEARCH_REQ_STRU */
    ID_MSCC_MMC_INTERSYS_HRPD_NTF                       = ID_MSCC_MMC_MSG_BASE + 76,    /* _H2ASN_MsgChoice MSCC_MMC_INTERSYS_HRPD_NTF_STRU */
    ID_MSCC_MMC_MMSS_INFO_NTF                           = ID_MSCC_MMC_MSG_BASE + 78,    /* _H2ASN_MsgChoice MSCC_MMC_MMSS_INFO_NTF_STRU */
    ID_MSCC_MMC_STOP_BG_SEARCH_REQ                      = ID_MSCC_MMC_MSG_BASE + 80,    /* _H2ASN_MsgChoice MSCC_MMC_STOP_BG_SEARCH_REQ_STRU */
    ID_MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ                = ID_MSCC_MMC_MSG_BASE + 82,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU */
    ID_MSCC_MMC_AUTO_RESEL_SET_REQ                      = ID_MSCC_MMC_MSG_BASE + 84,    /* _H2ASN_MsgChoice MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU */

    ID_MSCC_MMC_GET_GEO_REQ                             = ID_MSCC_MMC_MSG_BASE + 86,    /* _H2ASN_MsgChoice MSCC_MMC_GET_GEO_REQ_STRU */
    ID_MSCC_MMC_STOP_GET_GEO_REQ                        = ID_MSCC_MMC_MSG_BASE + 88,    /* _H2ASN_MsgChoice MSCC_MMC_STOP_GET_GEO_REQ_STRU */

    ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF                  = ID_MSCC_MMC_MSG_BASE + 90,    /* _H2ASN_MsgChoice MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU */

    ID_MSCC_MMC_DPLMN_SET_REQ                           = ID_MSCC_MMC_MSG_BASE + 92,    /* _H2ASN_MsgChoice MSCC_MMC_DPLMN_SET_REQ_STRU */

    ID_MSCC_MMC_CSG_LIST_SEARCH_REQ                     = ID_MSCC_MMC_MSG_BASE + 94,    /* _H2ASN_MsgChoice MSCC_MMC_CSG_LIST_SEARCH_REQ_STRU */
    ID_MSCC_MMC_CSG_LIST_ABORT_REQ                      = ID_MSCC_MMC_MSG_BASE + 96,    /* _H2ASN_MsgChoice MSCC_MMC_CSG_LIST_ABORT_REQ_STRU */

    ID_MSCC_MMC_CL_INTERSYS_START_NTF                  = ID_MSCC_MMC_MSG_BASE + 98,    /* _H2ASN_MsgChoice MSCC_MMC_CL_INTERSYS_START_NTF_STRU */

    /* MMC���͸�MSCC����Ϣԭ��*/
    ID_MMC_MSCC_START_CNF                               = ID_MSCC_MMC_MSG_BASE + 1,     /* _H2ASN_MsgChoice MMC_MSCC_START_CNF_STRU */
    ID_MMC_MSCC_SYS_INFO_IND                            = ID_MSCC_MMC_MSG_BASE + 3,     /* _H2ASN_MsgChoice MMC_MSCC_SYS_INFO_IND_STRU */
    ID_MMC_MSCC_SERVICE_STATUS_IND                      = ID_MSCC_MMC_MSG_BASE + 5,     /* _H2ASN_MsgChoice MMC_MSCC_SERVICE_STATUS_IND_STRU */
    ID_MMC_MSCC_MM_INFO_IND                             = ID_MSCC_MMC_MSG_BASE + 7,     /* _H2ASN_MsgChoice MMC_MSCC_MM_INFO_IND_STRU */
    ID_MMC_MSCC_ATTACH_CNF                              = ID_MSCC_MMC_MSG_BASE + 9,     /* _H2ASN_MsgChoice MMC_MSCC_ATTACH_CNF_STRU */
    ID_MMC_MSCC_DETACH_CNF                              = ID_MSCC_MMC_MSG_BASE + 11,    /* _H2ASN_MsgChoice MMC_MSCC_DETACH_CNF_STRU */
    ID_MMC_MSCC_DETACH_IND                              = ID_MSCC_MMC_MSG_BASE + 13,    /* _H2ASN_MsgChoice MMC_MSCC_DETACH_IND_STRU */
    ID_MMC_MSCC_PLMN_LIST_CNF                           = ID_MSCC_MMC_MSG_BASE + 15,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_LIST_CNF_STRU */
    ID_MMC_MSCC_PLMN_LIST_REJ                           = ID_MSCC_MMC_MSG_BASE + 17,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_LIST_REJ_STRU */
    ID_MMC_MSCC_COVERAGE_AREA_IND                       = ID_MSCC_MMC_MSG_BASE + 19,    /* _H2ASN_MsgChoice MMC_MSCC_COVERAGE_AREA_IND_STRU */
    ID_MMC_MSCC_POWER_OFF_CNF                           = ID_MSCC_MMC_MSG_BASE + 21,    /* _H2ASN_MsgChoice MMC_MSCC_POWER_OFF_CNF_STRU */
    ID_MMC_MSCC_RSSI_IND                                = ID_MSCC_MMC_MSG_BASE + 23,    /* _H2ASN_MsgChoice MMC_MSCC_RSSI_IND_STRU */
    ID_MMC_MSCC_PLMN_SPECIAL_SEL_CNF                    = ID_MSCC_MMC_MSG_BASE + 25,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU */
    ID_MMC_MSCC_DATATRAN_ATTRI_IND                      = ID_MSCC_MMC_MSG_BASE + 27,    /* _H2ASN_MsgChoice MMC_MSCC_DATATRAN_ATTRI_IND_STRU */
    ID_MMC_MSCC_SYS_CFG_CNF                             = ID_MSCC_MMC_MSG_BASE + 29,    /* _H2ASN_MsgChoice MMC_MSCC_SYS_CFG_SET_CNF_STRU */
    ID_MMC_MSCC_PLMN_SELECTION_RLST_IND                 = ID_MSCC_MMC_MSG_BASE + 31,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU */
    ID_MMC_MSCC_PLMN_LIST_ABORT_CNF                     = ID_MSCC_MMC_MSG_BASE + 33,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU */
    ID_MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF              = ID_MSCC_MMC_MSG_BASE + 35,    /* _H2ASN_MsgChoice MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU */
    ID_MMC_MSCC_UMTS_CIPHER_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 37,    /* _H2ASN_MsgChoice MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU */
    ID_MMC_MSCC_GPRS_CIPHER_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 39,    /* _H2ASN_MsgChoice MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU */
    ID_MMC_MSCC_PLMN_SPECIAL_SEL_REJ                    = ID_MSCC_MMC_MSG_BASE + 41,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU */
    ID_MMC_MSCC_AC_INFO_CHANGE_IND                      = ID_MSCC_MMC_MSG_BASE + 43,    /* _H2ASN_MsgChoice MMC_MSCC_AC_INFO_CHANGE_IND_STRU */
    ID_MMC_MSCC_PLMN_RESEL_CNF                          = ID_MSCC_MMC_MSG_BASE + 45,    /* _H2ASN_MsgChoice MMC_MSCC_PLMN_RESEL_CNF_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    ID_MMC_MSCC_REG_RESULT_IND                          = ID_MSCC_MMC_MSG_BASE + 47,    /* _H2ASN_MsgChoice  MMC_MSCC_REG_RESULT_IND_STRU */
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    ID_MMC_MSCC_PLMN_SELE_START_IND                     = ID_MSCC_MMC_MSG_BASE + 49,    /* _H2ASN_MsgChoice  MMC_MSCC_PLMN_SELECTION_START_IND_STRU */

    ID_MMC_MSCC_EOPLMN_SET_CNF                          = ID_MSCC_MMC_MSG_BASE + 51,    /* _H2ASN_MsgChoice  MMC_MSCC_EOPLMN_SET_CNF_STRU */
    ID_MMC_MSCC_USIM_AUTH_FAIL_IND                      = ID_MSCC_MMC_MSG_BASE + 53,    /* _H2ASN_MsgChoice  MMC_MSCC_USIM_AUTH_FAIL_IND_STRU */

    ID_MMC_MSCC_NET_SCAN_CNF                            = ID_MSCC_MMC_MSG_BASE + 55,    /* _H2ASN_MsgChoice  MMC_MSCC_NET_SCAN_CNF_STRU */
    ID_MMC_MSCC_ABORT_NET_SCAN_CNF                      = ID_MSCC_MMC_MSG_BASE + 57,    /* _H2ASN_MsgChoice  MMC_MSCC_ABORT_NET_SCAN_CNF_STRU */

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-9, begin */
    ID_MMC_MSCC_NETWORK_CAPABILITY_INFO_IND             = ID_MSCC_MMC_MSG_BASE + 59,    /* _H2ASN_MsgChoice MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU */
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-9, end */
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    ID_MMC_MSCC_CAMP_ON_IND                             = ID_MSCC_MMC_MSG_BASE + 61,    /* _H2ASN_MsgChoice MMC_MSCC_CAMP_ON_IND_STRU_STRU */
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    ID_MMC_MSCC_EPLMN_INFO_IND                          = ID_MSCC_MMC_MSG_BASE + 63,    /* _H2ASN_MsgChoice MMC_MSCC_EPLMN_INFO_IND_STRU */

    ID_MMC_MSCC_CS_SERVICE_CONN_STATUS_IND              = ID_MSCC_MMC_MSG_BASE + 65,    /* _H2ASN_MsgChoice MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU */

    ID_MMC_MSCC_SRV_REJ_IND                             = ID_MSCC_MMC_MSG_BASE + 67,    /* _H2ASN_MsgChoice MMC_MSCC_SERV_REJ_IND_STRU */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, Begin */
    ID_MMC_MSCC_ACQ_CNF                                 = ID_MSCC_MMC_MSG_BASE + 69,    /* _H2ASN_MsgChoice MMC_MSCC_ACQ_CNF_STRU */
    ID_MMC_MSCC_REG_CNF                                 = ID_MSCC_MMC_MSG_BASE + 71,    /* _H2ASN_MsgChoice MMC_MSCC_REG_CNF_STRU */
    ID_MMC_MSCC_POWER_SAVE_CNF                          = ID_MSCC_MMC_MSG_BASE + 73,    /* _H2ASN_MsgChoice MMC_MSCC_POWER_SAVE_CNF_STRU */
    ID_MMC_MSCC_ACQ_IND                                 = ID_MSCC_MMC_MSG_BASE + 75,    /* _H2ASN_MsgChoice MMC_MSCC_ACQ_IND_STRU */
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */


    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
    ID_MMC_MSCC_PS_SERVICE_CONN_STATUS_IND              = ID_MSCC_MMC_MSG_BASE + 77,    /* _H2ASN_MsgChoice MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU */
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
    ID_MMC_MSCC_RF_AVAILABLE_IND                        = ID_MSCC_MMC_MSG_BASE + 79,    /* _H2ASN_MsgChoice MMC_MSCC_RF_AVAILABLE_IND_STRU */
    ID_MMC_MSCC_SRV_ACQ_CNF                             = ID_MSCC_MMC_MSG_BASE + 81,    /* _H2ASN_MsgChoice MMC_MSCC_SRV_ACQ_CNF_STRU */
    ID_MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND           = ID_MSCC_MMC_MSG_BASE + 83,    /* _H2ASN_MsgChoice MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU */

    ID_MMC_MSCC_CFPLMN_SET_CNF                          = ID_MSCC_MMC_MSG_BASE + 87,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_SET_CNF_STRU */
    ID_MMC_MSCC_CFPLMN_QUERY_CNF                        = ID_MSCC_MMC_MSG_BASE + 89,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_SET_CNF_STRU */
    ID_MMC_MSCC_PREF_PLMN_SET_CNF                       = ID_MSCC_MMC_MSG_BASE + 91,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_SET_CNF_STRU */
    ID_MMC_MSCC_PREF_PLMN_QUERY_CNF                     = ID_MSCC_MMC_MSG_BASE + 93,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU */

    ID_MMC_MSCC_BG_SEARCH_CNF                           = ID_MSCC_MMC_MSG_BASE + 95,    /* _H2ASN_MsgChoice MMC_MSCC_BG_SEARCH_CNF_STRU */
    ID_MMC_MSCC_STOP_BG_SEARCH_CNF                      = ID_MSCC_MMC_MSG_BASE + 97,    /* _H2ASN_MsgChoice MMC_MSCC_STOP_BG_SEARCH_CNF_STRU */
    ID_MMC_MSCC_PREF_PLMN_INFO_IND                      = ID_MSCC_MMC_MSG_BASE + 99,    /* _H2ASN_MsgChoice MMC_MSCC_PREF_PLMN_INFO_IND_STRU */
    ID_MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND                = ID_MSCC_MMC_MSG_BASE + 101,   /* _H2ASN_MsgChoice MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU */
    ID_MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF                = ID_MSCC_MMC_MSG_BASE + 103,   /* _H2ASN_MsgChoice MMC_MSCC_PLMN_PRI_CLASS_QUERY_CNF_STRU */
    ID_MMC_MSCC_GET_GEO_CNF                             = ID_MSCC_MMC_MSG_BASE + 105,   /* _H2ASN_MsgChoice MMC_MSCC_GET_GEO_CNF_STRU */
    ID_MMC_MSCC_STOP_GET_GEO_CNF                        = ID_MSCC_MMC_MSG_BASE + 107,   /* _H2ASN_MsgChoice MMC_MSCC_STOP_GET_GEO_CNF_STRU */
    ID_MMC_MSCC_SRCHED_PLMN_INFO_IND                    = ID_MSCC_MMC_MSG_BASE + 109,   /* MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU */

    ID_MMC_MSCC_DPLMN_SET_CNF                           = ID_MSCC_MMC_MSG_BASE + 111,   /* _H2ASN_MsgChoice MMC_MSCC_DPLMN_SET_CNF_STRU */

    ID_MMC_MSCC_INTERSYS_START_IND                      = ID_MSCC_MMC_MSG_BASE + 113,   /* MMC_MSCC_INTERSYS_START_IND_STRU */
    ID_MMC_MSCC_INTERSYS_END_IND                        = ID_MSCC_MMC_MSG_BASE + 115,   /* MMC_MSCC_INTERSYS_END_IND_STRU */

    ID_MMC_MSCC_CSG_LIST_SEARCH_CNF                     = ID_MSCC_MMC_MSG_BASE + 117,   /* _H2ASN_MsgChoice MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU */
    ID_MMC_MSCC_CSG_LIST_ABORT_CNF                      = ID_MSCC_MMC_MSG_BASE + 119,   /* _H2ASN_MsgChoice MMC_MSCC_CSG_LIST_ABORT_CNF_STRU */
    ID_MMC_MSCC_CSG_LIST_REJ                            = ID_MSCC_MMC_MSG_BASE + 121,   /* _H2ASN_MsgChoice MMC_MSCC_CSG_LIST_REJ_STRU */

    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    ID_MMC_MSCC_PS_REG_CN_RSLT_IND                      = ID_MSCC_MMC_MSG_BASE + 129,   /* _H2ASN_MsgChoice MMC_MSCC_PS_REG_CN_RSLT_IND_STRU */
    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    ID_MSCC_PIF_MSG_TYPE_BUTT
};

typedef VOS_UINT32 MSCC_PIF_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8
 ö��˵��  : NAS_MSCC_PIF_START_REQ_STRU��Ϣ�е� ulCardStatus
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_CARD_STATUS_ENUM
{
    NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT      = 0,                              /* sim present */
    NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT     = 1,                              /* usim present */
    NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT      = 2,
    NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT     = 3,
    NAS_MSCC_PIF_CARD_STATUS_ABSENT           = 4,                              /* card absent */
    NAS_MSCC_PIF_CARD_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_BAND_CLASS_ENUM
 �ṹ˵��  : List of Band Classes (�ο�3GPP2 C.S0057-E��Table 1.5-1: )

 1.��    ��   : 2015��05��16��
   ��    ��   : W00176964
   �޸�����   : ����

*****************************************************************************/
enum NAS_MSCC_PIF_BAND_CLASS_ENUM
{
    NAS_MSCC_PIF_BAND_CLASS_TYPE_0                              = 0,    /* 800 MHz cellular band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_1                              = 1,    /* 1.8 to 2.0 GHz PCS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_2                              = 2,    /* 872 to 960 MHz TACS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_3                              = 3,    /* 832 to 925 MHz JTACS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_4                              = 4,    /* 1.75 to 1.87 GHz Korean PCS band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_5                              = 5,    /* 450 MHz NMT band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_6                              = 6,    /* 2 GHz IMT-2000 band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_7                              = 7,    /* 700 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_8                              = 8,    /* 1800 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_9                              = 9,    /* 900 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_10                             = 10,   /* Secondary 800 MHz band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_11                             = 11,   /* 400 MHz European PAMR band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_12                             = 12,   /* 800 MHz PAMR band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_13                             = 13,   /* 2.5 GHz IMT-2000 Extension Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_14                             = 14,   /* US PCS 1.9GHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_15                             = 15,   /* AWS Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_16                             = 16,   /* US 2.5GHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_17                             = 17,   /* US 2.5GHz Forward Link Only Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_18                             = 18,   /* 700 MHz Public Safety Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_19                             = 19,   /* Lower 700 MHz Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_20                             = 20,   /* L-Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_21                             = 21,   /* S-Band */

    NAS_MSCC_PIF_BAND_CLASS_TYPE_31                             = 31,   /* Wildcard Band Class */

    NAS_MSCC_PIF_BAND_CLASS_BUTT
};
typedef VOS_UINT16 NAS_MSCC_PIF_BAND_CLASS_ENUM_UINT16;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_NEG_SYS_ENUM
 �ṹ˵��  : Preferred/negative system

 1.��    ��   : 2015��05��16��
   ��    ��   : W00176964
   �޸�����   : ����

*****************************************************************************/
enum NAS_MSCC_PIF_PREF_NEG_SYS_ENUM
{
    NAS_MSCC_PIF_PREF_NEG_SYS_NEG                               = 0, /* This field is set to '0' if the mobile station is
                                                                                    not allowed to operate on the system associated
                                                                                    with this record */
    NAS_MSCC_PIF_PREF_NEG_SYS_PREF                              = 1, /* This field is set to ��1�� if the mobile station
                                                                                    is allowed to operate on the system associated with
                                                                                    this record */
    NAS_MSCC_PIF_PREF_NEG_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREF_NEG_SYS_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_STATUS_ENUM
 �ṹ˵��  : PLMN ״̬ ����AT���ϱ�����״̬
 1.��    ��   : 2012��4��7��
   ��    ��   : z00161729
   �޸�����   : ����
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_STATUS_ENUM
{
    NAS_MSCC_PIF_PLMN_STATUS_UNKNOW           = 0,                                    /* ��ǰ����״̬δ֪ */
    NAS_MSCC_PIF_PLMN_STATUS_AVAILIBLE        = 1,                                    /* ��ǰ������� */
    NAS_MSCC_PIF_PLMN_STATUS_CURRENT          = 2,                                    /* ��ǰ������ע�� */
    NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN        = 3,                                    /* ��ǰ�����ֹ */
    NAS_MSCC_PIF_PLMN_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_NET_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_NET_RAT_TYPE_GSM,           /* GSM���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_LTE,           /* LTE���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_1X,            /* 1X���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_HRPD,          /* 1X���뼼�� */
    NAS_MSCC_PIF_NET_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT8 NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_REG_STATE_ENUM_UINT8
 �ṹ˵��  : ע����
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_REG_STATE_ENUM
{
    NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH,      /* δע��δ���� */
    NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK,        /* ע�ᣬע���� HOME PLMN */
    NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING,       /* δע�ᣬ��������PLMN�������ڸ��Ź��� */
    NAS_MSCC_PIF_REG_REGISTERED_DENIED,              /* ע�ᱻ�ܾ�����ǰ�û�����������ע�ᣬ�������񱻽�ֹ */
    NAS_MSCC_PIF_REG_UNKNOWN,                        /* ������� */
    NAS_MSCC_PIF_REG_REGISTERED_ROAM,                /* ע�ᣬע���ڷ� HOME PLMN */
    NAS_MSCC_PIF_REG_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REG_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32
 �ṹ˵��  : �ػ�ԭ��ֵ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM
{
    NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE,
    NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL,
    NAS_MSCC_PIF_POWER_OFF_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8
 �ṹ˵��  : ��������
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM
{
    NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON                 = 0,
    NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF                = 1,
    NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON                = 2,
    NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF               = 3,
    NAS_MSCC_PIF_ROAM_UNCHANGE                                 = 4,
    NAS_MSCC_PIF_ROAM_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_ROAM_FEATURE_ENUM_U8
 �ṹ˵��  : ��������
 1.��    ��   : 2014��4��7��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_ROAM_FEATURE_ENUM
{
    NAS_MSCC_PIF_ROAM_FEATURE_OFF                = 0,
    NAS_MSCC_PIF_ROAM_FEATURE_ON                 = 1,
    NAS_MSCC_PIF_ROAM_FEATURE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ROAM_FEATURE_ENUM_U8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM
 �ṹ˵��  : �������
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : ����
 2.��    ��   : 2015��08��25��
   ��    ��   : m00312079
   �޸�����   : DTS2015082004682:����L2Cԭ��ֵ
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM
{
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE    = 0,                        /* �������� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE   = 1,                        /* ���Ʒ��� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE        = 2,                        /* �޷��� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT         = 3,                        /* �������ж� */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF             = 4,
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C               = 5,                        /* CL������L2C */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM
 �ṹ˵��  : ������ʼ������������ʾ
 1.��    ��   : 2013��10��09��
   ��    ��   : l00208543
   �޸�����   : ���� DTS2013100904573
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM
{
    NAS_MSCC_PIF_PLMN_SELECTION_START    = 0,                        /* ������ʼ */
    NAS_MSCC_PIF_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32
 �ṹ˵��  : syscfg���ý����Ϣ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS                  = 0,
    NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER            = 1,
    NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST    = 2,
    NAS_MSCC_PIF_SYS_CFG_SET_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32;

/******************************************************************************
�ṹ��    : NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8
�ṹ˵��  : С�������ֹ��Ϣö������
1.��    ��: 2013��3��25��
  ��    ��: z00161729
  �޸�����: ����
******************************************************************************/
enum  NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM
{
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NONE                   = 0,                   /* ��ǰС���������κ�ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                   /* ��ǰС����������ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                   /* ��ǰС�����ƽ���ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                   /* ��ǰС����������ҵ��ͽ���ҵ�� */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8   NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32
 �ṹ˵��  : attach����
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_ATTACH_TYPE_ENUM
{
    NAS_MSCC_PIF_ATTACH_TYPE_GPRS          = 1,
    NAS_MSCC_PIF_ATTACH_TYPE_IMSI          = 2,
    NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI     = 3,
    NAS_MSCC_PIF_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32
 �ṹ˵��  : detach����
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_DETACH_TYPE_ENUM
{
    NAS_MSCC_PIF_DETACH_NULL               = 0,
    NAS_MSCC_PIF_DETACH_TYPE_GPRS          = 1,
    NAS_MSCC_PIF_DETACH_TYPE_IMSI          = 2,
    NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI     = 3,
    NAS_MSCC_PIF_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM_UINT32
 �ṹ˵��  : NAS_MSCC_PIF_PLMN_USER_SEL_REQ_STRU��ulModeȡֵ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM
{
    NAS_MSCC_PIF_PLMN_CFG_MODE_USER_SEL           = 1,                               /* ֪ͨ�û�ѡ����PLMN��Ϣ */
    NAS_MSCC_PIF_PLMN_CFG_MODE_USER_RESEL         = 2,                               /* ����PLMN��User reselection */
    NAS_MSCC_PIF_PLMN_CFG_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_CFG_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32
 �ṹ˵��  : ����ģʽ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM
{
    NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO           = 0,                                   /* �Զ�����ģʽ */
    NAS_MSCC_PIF_PLMN_SEL_MODE_MANUAL         = 1,                                   /* �ֶ�����ģʽ */
    NAS_MSCC_PIF_PLMN_SEL_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32
 �ṹ˵��  : �������ı�ģʽ����ʧ������
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM
{
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST          = 0,                        /* �������� */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENTER         = 1,                        /* �������� */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_MS_MODE_ENUM_UINT32
 �ṹ˵��  : �ֻ�ģʽ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_MS_MODE_ENUM
{
    NAS_MSCC_PIF_MS_MODE_CC                  = 0,                                    /* cs mode */
    NAS_MSCC_PIF_MS_MODE_CG                  = 1,                                    /* ps mode */
    NAS_MSCC_PIF_MS_MODE_A                   = 2,                                    /* cs ps mode */
    NAS_MSCC_PIF_MS_MODE_B                   = 4,                                    /* mode B */
    NAS_MSCC_PIF_MS_MODE_NULL                = 5,                                    /* mode null */
    NAS_MSCC_PIF_MS_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_MS_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32
 �ṹ˵��  : ����״̬
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_SERVICE_STATUS_ENUM
{
    NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* �������� */
    NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* ���Ʒ��� */
    NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION   = 2,                        /* ������������� */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI                  = 3,                        /* ��imsi */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE               = 4,                        /* �޷��� */
    NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE                = 5,
    NAS_MSCC_PIF_SERVICE_STATUS_DEEP_SLEEP               = 6,
    NAS_MSCC_PIF_SERVICE_STATUS_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_OPERATION_STATUS_ENUM_UINT32
 �ṹ˵��  : �����Ƿ�����
 1.��    ��: 2015��12��23��
   ��    ��: j00174725
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_OPER_RESULT_SUCCESS               = 0,                         /* �����ɹ� */
    NAS_MSCC_PIF_OPER_RESULT_FAILURE               = 1,                         /* ����ʧ�� */
    NAS_MSCC_PIF_OPER_RESULT_REJECT                = 2,                         /* ��������иò��� */
    NAS_MSCC_PIF_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32
 �ṹ˵��  : ������
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_SRVDOMAIN_ENUM
{
    NAS_MSCC_PIF_SRVDOMAIN_NO_DOMAIN               = 0,
    NAS_MSCC_PIF_SRVDOMAIN_CS                      = 1,
    NAS_MSCC_PIF_SRVDOMAIN_PS                      = 2,
    NAS_MSCC_PIF_SRVDOMAIN_CS_PS                   = 3,
    NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE               = 4,
    NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING  = 5,
    NAS_MSCC_PIF_SRVDOMAIN_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32;

/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-6, begin */
/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PS_REG_PROC_ENUM_UINT32
 �ṹ˵��  : ��ǰLע����������
 1.��    ��: 2016��4��6��
   ��    ��: z00359541
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_PS_REG_PROC_ENUM
{
    NAS_MSCC_PIF_L_ATT_REAL_PROC        = 0,
    NAS_MSCC_PIF_L_TAU_REAL_PROC        = 1,
    NAS_MSCC_PIF_L_TAU_UNREAL_PROC      = 2,
    NAS_MSCC_PIF_L_REG_PROC_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PS_REG_PROC_ENUM_UINT32;
/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-6, end */

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8
 �ṹ˵��  : pdp�������
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM
{
    NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT          = 0,
    NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT        = 1,
    NAS_MSCC_PIF_DATATRAN_ATTRI_R99_ONLY         = 2,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA            = 3,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSUPA            = 4,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA_AND_HSUPA  = 5,
    NAS_MSCC_PIF_DATATRAN_ATTRI_HSPA_PLUS        = 6,
    NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_DATA         = 7,
    NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_IDLE         = 8,
    NAS_MSCC_PIF_DATATRAN_ATTRI_DC_HSPA_PLUS     = 9,
    NAS_MSCC_PIF_DATATRAN_ATTRI_DC_MIMO          = 10,
    NAS_MSCC_PIF_DATATRAN_ATTRI_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8
 �ṹ˵��  : ��������������ע��ķ�����
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM
{
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL     = 0,                                    /* ��ע��cs��ps */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS       = 1,                                    /* ֻע��PS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS       = 2,                                    /* ֻע��CS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS    = 3,                                    /* ע��CS+PS */
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8
 �ṹ˵��  : �û�ָ���������
 1.��    ��: 2013��4��7��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM
{
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS = 0,                                /* �ɹ� */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL    = 1,                                /* ʧ�� */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_REJ     = 2,
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8
 �ṹ˵��  : CSG ID����
1.��    ��   : 2015��9��6��
  ��    ��   : z00161729
  �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM
{
    NAS_MSCC_PIF_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST                  = 1,  /* CSG ID��Allowed CSG List��*/
    NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN    = 2,  /* CSG ID��Operator CSG List�в��ڽ�ֹCSG ID�б��� */
    NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN        = 3,  /* CSG ID��Operator CSG List�в����ڽ�ֹCSG ID�б���*/
    NAS_MSCC_PIF_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST = 4,  /* CSG ID����Allowed CSG List��Operator CSG List��*/
    NAS_MSCC_PIF_CSG_ID_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM
 �ṹ˵��  : �����IMS voice֧������
 1.��    ��: 2013��7��9��
   ��    ��: y00245242
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM
{
    NAS_MSCC_PIF_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    NAS_MSCC_PIF_NW_IMS_VOICE_SUPPORTED        = 1,

    NAS_MSCC_PIF_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM
 �ṹ˵��  : �����EMC BS֧������
 1.��    ��: 2013��7��9��
   ��    ��: y00245242
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM
{
    NAS_MSCC_PIF_NW_EMC_BS_NOT_SUPPORTED       = 0,
    NAS_MSCC_PIF_NW_EMC_BS_SUPPORTED           = 1,

    NAS_MSCC_PIF_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM
 �ṹ˵��  : LTE CS����
 1.��    ��: 2013��7��9��
   ��    ��: y00245242
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM
{
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    NAS_MSCC_PIF_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8;

/*****************************************************************************
    ö����    : NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM
    ö��˵��  : ims����ͨע��״̬
  1.��    ��: 2013��12��16��
    ��    ��: w00176964
    �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM
{
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_DEREG        = 0x00,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_DEREGING     = 0x01,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_REGING       = 0x02,
    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_REG          = 0x03,

    NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_BUTT         = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_PIF_IMS_NORMAL_REG_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_U8
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_REG_CONTROL_ENUM
{
    NAS_MSCC_PIF_REG_CONTROL_BY_3GPP_MMC = 0,                 /* ������������Ƿ�ע�ᰴĿǰ3GPPЭ��ģ��MMC���� */
    NAS_MSCC_PIF_REG_CONTROL_BY_3GPP2_CBP,                    /*������������Ƿ�ע����3GPP2Э��CDMA Baseband Protocol���� */
    NAS_MSCC_PIF_REG_CONTROL_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REG_CONTROL_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X = 0,
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM
 �ṹ˵��  : ����EPSע���ԭ��ö��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM
{
    NAS_MSCC_PIF_EPS_ATTACH_REASON_INITIAL          = 0,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_HANDOVER         = 1,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_DETACH_REASON_ENUM
 �ṹ˵��  : ����EPSȥע���ԭ��ö��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
enum NAS_MSCC_PIF_DETACH_REASON_ENUM
{
    NAS_MSCC_PIF_DETACH_REASON_USER_DETACH          = 0,/* �û�������detach���� */
    NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH   = 1,/* system configure��RAT��band������detach */
    NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH    = 2,/* system configure�з����򴥷���detach */
    NAS_MSCC_PIF_DETACH_REASON_3GPP2_ATTACHED       = 3,/* 3GPP2������attach */
    NAS_MSCC_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM
 �ṹ˵��  : PLMN�����ȼ����
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM
{
    NAS_MSCC_PIF_PLMN_PRIORITY_HOME               = 0,    /* home or ehome plmn */
    NAS_MSCC_PIF_PLMN_PRIORITY_PREF               = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_PIF_PLMN_PRIORITY_ANY                = 2,    /* Acceptable PLMN */
    NAS_MSCC_PIF_PLMN_PRIORITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_ACQ_REASON_ENUM
 �ṹ˵��  : ��ȡԭ��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��5��12��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration 10����
*****************************************************************************/
enum NAS_MSCC_PIF_ACQ_REASON_ENUM
{
    NAS_MSCC_PIF_ACQ_REASON_POWER_UP        = 0,
    NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY   = 1,
    NAS_MSCC_PIF_ACQ_REASON_OTHER           = 2,
    NAS_MSCC_PIF_ACQ_REASON_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_ACQ_RESULT_ENUM
 �ṹ˵��  : ��ȡ���ö��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_ACQ_RESULT_ENUM
{
    NAS_MSCC_PIF_ACQ_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_ACQ_RESULT_FAILURE          = 1,
    NAS_MSCC_PIF_ACQ_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_REG_RESULT_ENUM
 �ṹ˵��  : ע����ö��
 1.��    ��   : 2014��1��2��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_REG_RESULT_ENUM
{
    NAS_MSCC_PIF_REG_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE      = 1,
    NAS_MSCC_PIF_REG_RESULT_REG_FAILURE      = 2,
    NAS_MSCC_PIF_REG_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_CALL_MODE_ENUM
 �ṹ˵��  : ����ģʽö��
 1.��    ��   : 2014��4��1��
   ��    ��   : s00261364
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_CALL_MODE_ENUM
{
    NAS_MSCC_PIF_ECALL_ONLY            = 0,
    NAS_MSCC_PIF_ECALL_AND_NORMAL_CALL = 1,
    NAS_MSCC_PIF_ECALL_MODE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_CALL_MODE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
enum NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM
{
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_EUTRAN_FDD         ,
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8
 * Description : Call type
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM
{
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL      = 0x00,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL   = 0x01,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL    = 0x02,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL    = 0x03,
    NAS_MSCC_PIF_CDMA_CALL_TYPE_BUTT                   = 0x04
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8
 * Description : Call cause
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM
{
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE                           = 0x01, /**<  No Service\x{ff0c}Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_MAX_ACCESS_PROBES                    = 0x02, /**<  Max Access Probes, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_NORMAL                       = 0x03, /**<  Reorder Order, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REORDER_LOW_RSSI                     = 0x04, /**<  Reorder Order, Call Redial, RSSI<=-100dB */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_DENYIED                       = 0x05, /**<  Access Denied, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE_NORMAL                   = 0x06, /**<  Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE_LOW_RSSI                 = 0x07, /**<  Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_NORMAL        = 0x08, /**<  Access Time Out, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CHANNEL_ASSIGN_TIMEOUT_LOW_RSSI      = 0x09, /**<  Access Time Out, Call Redial, RSSI<=-100dB */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCT_BLOCK                           = 0x0A, /**<  Acct Block, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_NDSS                                 = 0x0B, /**<  Access Control based on Call Type, redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_REDIRECTION                          = 0x0C, /**<  Redirection, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ABORT                                = 0x0D, /**<  State can not Process Call, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_INTERNAL_NO_SERVICE                  = 0x0E, /* Internal No Service\x{ff0c}Call Redial */

    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_IN_PROGRESS                   = 0x0F, /* Access In Progress, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ACCESS_FAIL                          = 0x10, /* Access fail, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_SIGNAL_FADE                          = 0x11, /* Signal Fade, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_BS_RELEASE                           = 0x12, /* BS, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_CCS_NOT_SUPPORT                      = 0x13, /* Concurrent Service not Support, Call Redial */
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_RTC_RTCACK_FAILURE                   = 0x14, /* RTC ACK FAIL, Call Redial */

    NAS_MSCC_PIF_CDMA_CALL_CAUSE_BUTT                                 = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_SUCC                         = 0x00,
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL                         = 0x01,
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_BUTT                         = 0x02
};
typedef VOS_UINT8 NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM
{
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_SUCC                         = 0x00,
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_FAIL                         = 0x01,
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_BUTT                         = 0x02
};
typedef VOS_UINT8 NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8
 * Description : Service status
 *******************************************************************************/
enum NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM
{
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_DISABLE                          = 0x00,
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENABLE                           = 0x01,
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_BUTT                             = 0x02
};

typedef VOS_UINT8 NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_START_RESULT_ENUM_UINT32
 * Description : start result
 *******************************************************************************/
enum	NAS_MSCC_PIF_START_RESULT_ENUM
{
    NAS_MSCC_PIF_START_RESULT_SUCC,
    NAS_MSCC_PIF_START_RESULT_FAIL
};

typedef VOS_UINT32 NAS_MSCC_PIF_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM��Ϣ�е�RESULT;
*****************************************************************************/

enum NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS          = 0,
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_FAILURE          = 1,
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_CFPLMN_SET_STRU��Ϣ�е�cmdtype;
*****************************************************************************/
enum NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM
{
    NAS_MSCC_PIF_CFPLMN_TYPE_QUERY     = 0,
    NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ALL   = 1,
    NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ONE   = 2,
    NAS_MSCC_PIF_CFPLMN_TYPE_ADD_ONE   = 3,
    NAS_MSCC_PIF_CFPLMN_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM��Ϣ�е�RESULT;
*****************************************************************************/

enum NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM
{
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS             = 0,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_FAILURE             = 1,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_TIMEOUT             = 2,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_MEM_ALLOC_FAIL      = 3,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_GET_PLMNINFO_FAIL   = 4,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMN_INDEX_ERR      = 5,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_UPDATA_USIM_PLMN    = 6,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMNID_INVAILD      = 7,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SAME_PLMNID         = 8,
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM
 �ṹ˵��  : PREFPLMN��ѯ��������ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM
{
    NAS_MSCC_PIF_PREF_PLMN_QUERY      = 0,  /* PREFPLMN��ѯ���� */
    NAS_MSCC_PIF_PREF_PLMN_TEST       = 1,  /* PREFPLMN�������� */
    NAS_MSCC_PIF_PREF_PLMN_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PARA_TYPE_ENUM
 �ṹ˵��  : PREFPLMN��ѯ��������ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PARA_TYPE_ENUM
{
    NAS_MSCC_PLMN_LIST_INFO,           /*��ȡ������PLMN�б�*/
    NAS_MSCC_OPLMN_INFO,
    NAS_MSCC_UPLMN_INFO,
    NAS_MSCC_HPLMN_INFO,
    NAS_MSCC_PLMNSEL_INFO,

    /*����MMCȫ�ֱ�������*/
    NAS_MSCC_BEGIN_SET_MMC_PARA,
    NAS_MSCC_SET_PLMNSEL_INFO,
    NAS_MSCC_SET_OPLMN_INFO,
    NAS_MSCC_SET_UPLMN_INFO,
    NAS_MSCC_END_SET_MMC_PARA,
    NAS_MSCC_PARA_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_ID_ENUM
 �ṹ˵��  : PREFPLMN����ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM
{
    NAS_MSCC_PREF_PLMN_UPLMN,
    NAS_MSCC_PREF_PLMN_OPLMN,
    NAS_MSCC_PREF_PLMN_HPLMN,
    NAS_MSCC_PREF_PLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM
 �ṹ˵��  : PREFPLMN��ɾ�Ĳ�������ö��
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM
{
    NAS_MSCC_PREF_PLMN_QUREY,
    NAS_MSCC_PREF_PLMN_DEL_ONE,
    NAS_MSCC_PREF_PLMN_ADD_ONE,
    NAS_MSCC_PREF_PLMN_MODIFY_ONE,
    NAS_MSCC_PREF_PLMN_OPERATE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM_UINT8;

typedef enum
{
    EN_MMC_PLMN_LIST_INFO,           /*��ȡ������PLMN�б�*/
    EN_MMC_OPLMN_INFO,
    EN_MMC_UPLMN_INFO,
    EN_MMC_HPLMN_INFO,
    EN_MMC_PLMNSEL_INFO,

    /*����MMCȫ�ֱ�������*/
    EN_MMC_BEGIN_SET_MMC_PARA,
    EN_MMC_SET_PLMNSEL_INFO,
    EN_MMC_SET_OPLMN_INFO,
    EN_MMC_SET_UPLMN_INFO,
    EN_MMC_END_SET_MMC_PARA,
    MMC_MMA_PARA_TYPE_BUTT
}MMC_MMA_PARA_TYPE_ENUM;

/** ****************************************************************************
 ö����    : NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM
 �ṹ˵��  : ϵͳ������
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
 *******************************************************************************/
enum NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC        = 0x00000000,
    NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL        = 0x00000001,
    NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED     = 0x00000002,
    NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF       = 0x00000003,
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_BUTT   = 0x00000004
};
typedef VOS_UINT32 NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32;

typedef VOS_UINT16 NAS_MSCC_USIM_RAT;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8
 �ṹ˵��  : ����detach ind��ָʾ��detach����
 1.��    ��: 2014��4��1��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
enum NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM
{
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_REATTACH      = 1,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_NOATTACH      = 2,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_IMSI          = 3,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8;


enum MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM
{
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE    = 0,                        /* Normal service*/
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE   = 1,                        /* Limited service */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE        = 2,                        /* No service */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT         = 3,                        /* sevice interrupted */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_RF             = 4,
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_BUTT
};
typedef VOS_UINT32 MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM
 �ṹ˵��  : NAS_MSCC_PIF_NET_SCAN_CNF_STRU��Ϣ�е�enResult;
*****************************************************************************/
enum NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM
{
    NAS_MSCC_PIF_NET_SCAN_RESULT_SUCCESS     = 0,
    NAS_MSCC_PIF_NET_SCAN_RESULT_FAILURE     = 1,
    NAS_MSCC_PIF_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM
 �ṹ˵��  : ɨ��ʧ��ԭ��
 1.��    ��   : 2013��10��10��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM
{
    NAS_MSCC_PIF_NET_SCAN_CAUSE_SIGNAL_EXIST        = 0,                /* ������������ */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_STATE_NOT_ALLOWED   = 1,                /* ��ǰδפ�� */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_FREQ_LOCK           = 2,                /* ��ǰ��Ƶ״̬ */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_PARA_ERROR          = 3,                /* �������󣬰������뼼����֧�֣�Ƶ�β�֧�֣�Ƶ������������޴��� */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_CONFLICT            = 4,                /* ����ԭ��ֵ��ͻ */
    NAS_MSCC_PIF_NET_SCAN_CAUSE_SERVICE_EXIST,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_NOT_CAMPED,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_RAT_TYPE_ERROR,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_REJ_TYPE_ENUM
 �ṹ˵��  : �ܾ�����
 1.��    ��   : 2014��4��1��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_REJ_TYPE_ENUM
{
    NAS_MSCC_PIF_REJ_TYPE_REG        = 0,
    NAS_MSCC_PIF_REJ_TYPE_USIM_AUTH  = 1,
    NAS_MSCC_PIF_REJ_TYPE_SERV_REQ   = 2,
    NAS_MSCC_PIF_REJ_TYPE_NETWORK_DETACH_IND = 3,
    NAS_MSCC_PIF_REJ_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_REJ_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8
 ö��˵��  : CS���PS��SESSION����
 1.��    ��   : 2014��5��22��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_TYPE_ENUM
{
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_SS,
    NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS,
    NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL,
    NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    NAS_MSCC_PIF_SRV_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8
 ö��˵��  : ҵ�񴥷��������
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM
{
    NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS = 0,                                /* �ɹ� */
    NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL    = 1,                                /* ʧ�� */
    NAS_MSCC_PIF_SRV_ACQ_RESULT_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32
 �ṹ˵��  : VOIDE DOMAIN����
  1.��    ��   : 2015��04��13��
    ��    ��   : f00179208
    �޸�����   : �½�
 *****************************************************************************/
enum NAS_MSCC_PIF_VOICE_DOMAIN_ENUM
{
    NAS_MSCC_PIF_VOICE_DOMAIN_CS_ONLY            = 0,    /* CS voice only */
    NAS_MSCC_PIF_VOICE_DOMAIN_IMS_PS_ONLY        = 1,    /* IMS PS voice only */
    NAS_MSCC_PIF_VOICE_DOMAIN_CS_PREFERRED       = 2,    /* CS vocie preferred, IMS PS voice as secondary */
    NAS_MSCC_PIF_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,    /* IMS PS voice preferred, CS vocie as secondary */

    NAS_MSCC_PIF_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32  NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8
 �ṹ˵��  : IMSЭ��ջ���ػ�״̬ö������
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM
{
    NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF        = 0,
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ON         = 1,
    NAS_MSCC_PIF_IMS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32
 �ṹ˵��  : IMSЭ��ջ�������ö������
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_START_RESULT_ENUM
{
    NAS_MSCC_PIF_IMS_START_RESULT_SUCC       = 0,
    NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT    = 1,

    NAS_MSCC_PIF_IMS_START_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32
 �ṹ˵��  : IMSЭ��ջ�ػ����ö������
 1.��    ��   : 2015��04��13��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM
{
    NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC       = 0,
    NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT    = 1,

    NAS_MSCC_PIF_IMS_STOP_RESULT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM
{
    NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT    = 0x00000000,
    NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR       = 0x00000001,
    NAS_MSCC_PIF_INTERSYS_CAUSE_HO          = 0x00000002,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_BUTT   = 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum MSCC_MMC_CL_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_SUCC    = 0x00000000,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_FAIL    = 0x00000001,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ABORTED = 0x00000002,
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_BUTT= 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_PRI_CLASS_ENUM
 *
 * Description :
 *******************************************************************************/
enum NAS_MSCC_PIF_PRI_CLASS_ENUM
{
    NAS_MSCC_PIF_PRI_CLASS_HOME             = 0x00,
    NAS_MSCC_PIF_PRI_CLASS_PREF             = 0x01,
    NAS_MSCC_PIF_PRI_CLASS_ANY              = 0x0F,
    NAS_MSCC_PIF_PRI_CLASS_ENUM_BUTT        = 0xF0
};
typedef VOS_UINT8 NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8
 ö��˵��  : ҵ�񴥷�������RAT����
 1.��    ��   : 2014��5��15��
   ��    ��   : l00301449
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8;





/*****************************************************************************
 ö����    : NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8
 ö��˵��  : RF AVAILABLE��RAT����
 1.��    ��   : 2014��5��15��
   ��    ��   : l00301449
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_3GPP,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_1X,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_HRPD,
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PS_RATTYPE_ENUM_UINT32
 �ṹ˵��  : CDMA PS RATTYPE ö������
 1.��    ��   : 2015��05��11��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_PS_RAT_TYPE_ENUM
{
    NAS_MSCC_PIF_PS_RATTYPE_NULL   = 0,
    NAS_MSCC_PIF_PS_RATTYPE_1X     = 1,
    NAS_MSCC_PIF_PS_RATTYPE_HRPD   = 2,
    NAS_MSCC_PIF_PS_RATTYPE_EHRPD  = 3,
    NAS_MSCC_PIF_PS_RATTYPE_LTE    = 4,
    NAS_MSCC_PIF_PS_RATTYPE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32
 �ṹ˵��  : EMC_CALLBACK_MODEö������
 1.��    ��   : 2015��07��16��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM
{
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_DISABLE  = 0,
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE   = 1,

    NAS_MSCC_PIF_EMC_CALLBACK_MODE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MMC_MSCC_CL_REG_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CL��VIA��̬ʹ�õ�ATTACHע�����ϱ�ʱ�����Ľ׶�
*****************************************************************************/
enum MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM
{
    MMC_MSCC_CL_REG_STATUS_ATTACH_NOT_SEND            = 0x00,
    MMC_MSCC_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP    = 0x01,
    MMC_MSCC_CL_REG_STATUS_ATTACH_RCV_CN_REJ          = 0x02,
    MMC_MSCC_CL_REG_STATUS_ATTACH_RCV_CN_ACP          = 0x03,
    MMC_MSCC_CL_REG_STATUS_ATTACH_T3410_EXP           = 0x04,
    MMC_MSCC_CL_REG_STATUS_ATTACH_CMP_SEND            = 0x05,

    MMC_MSCC_CL_REG_STATUS_BUTT
};
typedef VOS_UINT8 MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM8;

/*****************************************************************************
ö����    : MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8
ö��˵��  : PS��Ϣ����
1.��    ��   : 2015��10��14��
  ��    ��   : j00174725
  �޸�����   : DTS2015093005685
*****************************************************************************/
enum MSCC_MMC_PS_SIGNALING_TYPE_ENUM
{
    MSCC_MMC_PS_SIGNALING_TYPE_GU           = 0,                                /* GU��PS���� */
    MSCC_MMC_PS_SIGNALING_TYPE_LTE          = 1,                                /* LTE��PS���� */

    MSCC_MMC_PS_SIGNALING_TYPE_BUTT
};
typedef VOS_UINT8 MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM
 �ṹ˵��  : PLMN��������
 1.��    ��   : 2015��12��10��
   ��    ��   : w00176964
   �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
enum NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM
{
    NAS_MSCC_PIF_PLMN_SEARCH_SPEC        = 0,       /* ָ������,Ĭ�ϰ�װȫƵ�εķ�ʽ���� */
    NAS_MSCC_PIF_PLMN_SEARCH_HISTORY     = 1,       /* ��ʷƵ������ */
    NAS_MSCC_PIF_PLMN_SEARCH_PERF_BAND   = 2,       /*����Ԥ��band������㲻��Ҫ����ȫband����������Ҫ����Ԥ��band,�����Ԥ��band
                                                    ��Ӳ��֧�ֵ�band��ȫ�ص����������Ҫ����������н����й�ȫbandɨƵ�ı�־λ��λ*/
    NAS_MSCC_PIF_PLMN_SEARCH_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32;


/*****************************************************************************
ö����    : NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8
ö��˵��  : MSCC�·�POWER SAVE����Я����ԭ��ֵ
1.��    ��   : 2016��02��02��
  ��    ��   : h00313353
  �޸�����   : DTS2016013000558
*****************************************************************************/
enum NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM
{
    NAS_MSCC_PIF_POWER_SAVE_TYPE_UNKNOWN = 0,                                /* ����POWERSAVE��ԭ��ֵδ֪ */
    NAS_MSCC_PIF_POWER_SAVE_TYPE_SLEEP   = 1,                                /* SLEEP����POWERSAVE */
    NAS_MSCC_PIF_POWER_SAVE_TYPE_SYSCFG  = 2,                                /* SYSCFG����POWERSAVE */

    NAS_MSCC_PIF_POWER_SAVE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8;

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
/*******************************************************************************
 * Name        : MSCC_MSG_HEADER_STRU
 *
 * Description : MSCC������ģ����Ϣͷ�ṹ
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    MSCC_PIF_MSG_TYPE_ENUM_UINT32       ulMsgName;
}MSCC_MSG_HEADER_STRU;


/*******************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_BAND_STRU
 *
 * Description : CDMA��Ƶ��
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBC0_A:1;
    VOS_UINT32                          bitOpBC0_B:1;
    VOS_UINT32                          bitOpBC1:1;
    VOS_UINT32                          bitOpBC2:1;
    VOS_UINT32                          bitOpBC3:1;
    VOS_UINT32                          bitOpBC4:1;
    VOS_UINT32                          bitOpBC5:1;
    VOS_UINT32                          bitOpBC6:1;
    VOS_UINT32                          bitOpBC7:1;
    VOS_UINT32                          bitOpBC8:1;
    VOS_UINT32                          bitOpBC9:1;
    VOS_UINT32                          bitOpBC10:1;
    VOS_UINT32                          bitOpBC11:1;
    VOS_UINT32                          bitOpBC12:1;
    VOS_UINT32                          bitOpBC14:1;
    VOS_UINT32                          bitOpBC15:1;
    VOS_UINT32                          bitOpSpare:16;
}NAS_MSCC_PIF_CDMA_BAND_STRU;

/*******************************************************************************
 �ṹ��    : CDMA_BAND_SET_UN
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDMAƵ��union����
1.��    �� : 2015��4��15��
  ��    �� : y00245242
  �޸����� : �޸�WCDMA��Ƶ��Ϊ32λ��,֧��W��band19
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulCdmaBand;

    NAS_MSCC_PIF_CDMA_BAND_STRU         stCdmaBitBand;
}NAS_MSCC_CDMA_BAND_SET_UN;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_ID_STRU
 �ṹ˵��  : plmn id����Ϣ
 1.��    ��   : 2015��2��25��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_MSCC_PIF_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU
 �ṹ˵��  : Ƶ�κ�Ƶ����Ϣ
   1.��    ��   : 2015��5��16��
    ��    ��   : W00176964
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_BAND_CLASS_ENUM_UINT16                     enBandClass;
    VOS_UINT16                                              usChannel;
}NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CAMP_POSITION_STRU
 �ṹ˵��  : ��ǰפ��λ����Ϣ
 1.��    ��   : 2015��2��25��
   ��    ��   : g00322017
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulCellId;
    VOS_UINT16                                              usLac;
    VOS_UINT8                                               ucRac;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enNetRatType;
}NAS_MSCC_PIF_CAMP_POSITION_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_PLMN_ID_STRU                               stInitAcqPlmnId;
}NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;                                  /* plmn rat in the plmn list */
    VOS_UINT8                                               ucHighPlmnNum;
    VOS_UINT8                                               ucLowPlmnNum;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astHighPlmnID[NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astLowPlmnID[NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM];
}NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU
 �ṹ˵��  : plmn id with pri class type����Ϣ
 1.��    ��   : 2015��5��4��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPriClass;
    VOS_UINT8                                               ucIsForbidden;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat;                                  /* plmn rat in the plmn list */
    VOS_UINT8                                               ucHighPlmnNum;
    VOS_UINT8                                               ucLowPlmnNum;
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU                   astHighPlmnPriClassInfo[NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM];
    NAS_MSCC_PIF_PLMN_PRI_CLASS_INFO_STRU                   astLowPlmnPriClassInfo[NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM];
}NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU
 �ṹ˵��  : PREFPLMN��������
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPLMNType;
    NAS_MSCC_PIF_PREFPLMN_OPERATE_TYPE_ENUM_UINT8           enPrefPlmnOperType;
    NAS_MSCC_USIM_RAT                                       usRat;              /* USIM��ʽ�� ���뼼�� */
    VOS_UINT32                                              ulIndex;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmn;
} NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU
 �ṹ˵��  : PREFPLMN��������
 1.��    ��   : 2015��02��06��
   ��    ��   : y00307564
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlmnNum;
    VOS_UINT8                           aucReserved[2];
    NAS_MSCC_PIF_PLMN_ID_STRU           Plmn[NAS_MSCC_PIF_MAX_PLMN_NUM];
    NAS_MSCC_USIM_RAT                   ausPlmnRat[NAS_MSCC_PIF_MAX_PLMN_NUM];
}NAS_MSCC_PIF_USER_PLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_RAT_PRIO_STRU
 �ṹ˵��  : MS band������
 1.��    ��   : 2011��6��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2014��5��22��
   ��    ��   : W00176964
   �޸�����   : ECALL����:LTE��ر�ʱ�ֽڲ�����
 3.��    ��   : 2015��5��12��
   ��    ��   : W00176964
   �޸�����   : CDMA iteration 10 modified
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRatNum;                                   /* ��ǰ֧�ֵĽ��뼼������  */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    aucRatPrio[NAS_MSCC_PIF_MAX_RAT_NUM];       /* �������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
#if (FEATURE_OFF == FEATURE_LTE)
    VOS_UINT8                               aucRsv[1];
#endif
}NAS_MSCC_PIF_RAT_PRIO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_3GPP2_RAT_STRU
 �ṹ˵��  : MS 3GPP2�Ľ��뼼������
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRatNum;                                   /* ��ǰ֧�ֵĽ��뼼������  */
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8                  auc3GPP2Rat[NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT];
    VOS_UINT8                                               aucReserve[1];
}NAS_MSCC_PIF_3GPP2_RAT_STRU;
/* Added by s00246516 for L-C��������Ŀ, 2014-01-26, End */

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_EPLMN_INFO_STRU
 �ṹ˵��  : MSCC��ǰEQUPLMN��Ϣ
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEquPlmnNum;                           /* ��ǰEquPLMN�ĸ��� */                                                                                /* EPLMN��ɾ����EPLMN����Ϊ0ʱ��Ч,�����������Ч */
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_PLMN_ID_STRU           astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];/* ��ǰEquPLMN�б� */
}NAS_MSCC_PIF_EPLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CAMP_CELL_INFO_STRU
 �ṹ˵��  : ��ǰפ��С������Ϣ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCellNum;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          aulCellId[NAS_MSCC_PIF_CELL_MAX_NUM];
}NAS_MSCC_PIF_CAMP_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU
 �ṹ˵��  : plmn id����Ӫ�̳�������Ϣ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_MSCC_PIF_MAX_OPER_SHORT_NAME_LEN];/* ��ǰפ��������Ӫ�̵Ķ����� */
    VOS_UINT8                           aucOperatorNameLong[NAS_MSCC_PIF_MAX_OPER_LONG_NAME_LEN];  /* ��ǰפ��������Ӫ�̵ĳ����� */
}NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU
 �ṹ˵��  : ue ֧��band����
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
 2.��    ��   : 2015��4��15��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
typedef struct
{
    WCDMA_BAND_SET_UN                   unWcdmaBand;                            /* wcdma��ǰ����֧�ֵ�Ƶ�� */
    GSM_BAND_SET_UN                     unGsmBand;                              /* gsm��ǰ����֧�ֵ�Ƶ�� */
    LTE_BAND_STRU                       stLteBand;                              /* lte��ǰ����֧�ֵ�Ƶ�� */
    NAS_MSCC_CDMA_BAND_SET_UN           unCdmaBand;                             /* cdma��ǰ����֧�ֵ�Ƶ�� */
}NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_RSSI_VALUE_STRU
 �ṹ˵��  : rssiֵ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRssiValue;
    VOS_INT16                           sRscpValue;
    VOS_UINT8                           ucBer;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_RSSI_VALUE_STRU;

/*******************************************************************************
 �ṹ��    :NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU
 �ṹ˵��  : union NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU��ԱstMeasReportType����
             bitλ��1��ʾ��������Ч
1.��    �� : 2014��6��5��
  ��    �� : b00269685
  �޸����� : �½�
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMeasRxlevType          :1;             /* Rxlev�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                           ucMeasRxqualityType      :1;             /* Rxquality�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                           ucMeasCellIdType         :1;             /* Rxquality�ı䴥���Ĳ����ϱ� */
    VOS_UINT8                           ucMeasTypeSpare5         :5;
}NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN
 �ṹ˵��  : NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN unMeasType�ϱ�����������
1. ��    ��: 2014��6��5��
   ��    ��: b00269685
   �޸�����: �½�
*****************************************************************************/
typedef union
{
    VOS_UINT8                           ucMeasReportType;

    NAS_MSCC_PIF_SCELL_MEAS_TYPE_STRU   stMeasReportType;
    VOS_UINT8                           aucReserved1[4];
}NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_RSSI_INFO_STRU
 �ṹ˵��  : rssi��Ϣ
 1.��    ��: 2013��3��25��
   ��    ��: z00161729
   �޸�����: ����
 2.��    ��: 2014��6��4��
   ��    ��: b00269685
   �޸�����: �����ϱ�����
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                                               ucRssiNum;
    VOS_UINT8                                               ucReserved;
    VOS_UINT16                                              usCellDlFreq;                           /*С��Ƶ��(����)*/
    VOS_UINT16                                              usCellUlFreq;                           /*��ǰƵ��(����)*/
    VOS_INT16                                               sUeRfPower;                             /*���书��*/
    NAS_MSCC_PIF_RSSI_VALUE_STRU                            astRssi[NAS_MSCC_PIF_CELL_MAX_NUM];
    NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN                  unMeasReportType;                       /* �����ϱ����� */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8     enRat;                                  /*��ǰ�ϱ��źŵ���ʽ*/
    VOS_UINT8                           aucReserved1[3];
}NAS_MSCC_PIF_RSSI_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CQI_INFO_STRU
 �ṹ˵��  : LTE�µ��ŵ�����,�������ֱַ�����Ӵ�CQI�Ϳ��CQI
 1.��    ��: 2014��11��28��
   ��    ��: w00281933
   �޸�����: ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRI;                                   /* RI */
    VOS_UINT8                           aucRes[2];
    VOS_UINT16                          ausCQI[2];                              /* CQI�������� */

}NAS_MSCC_PIF_CQI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MMC_LMM_CELL_SIGN_INFO_STRU
 �ṹ˵��  : LTE�µ��ŵ�����,����LTE�µ�Rssi��Rsrp��Rsrq,SINR,CQI
 1.��    ��: 2014��11��28��
   ��    ��: w00281933
   �޸�����: ����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRssi;                                  /* Rssi*/
    VOS_INT16                           sRsd;                                   /* ����ֶ�*/
    VOS_INT16                           sRsrp;                                  /* ��Χ��(-141,-44), 99Ϊ��Ч */
    VOS_INT16                           sRsrq;                                  /* ��Χ��(-40, -6) , 99Ϊ��Ч */
    VOS_INT32                           lSINR;                                  /* SINR RS_SNR */
    NAS_MSCC_PIF_CQI_INFO_STRU          stCQI;                                  /* Channle Quality Indicator*/
}NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MMC_LMM_CELL_SIGN_INFO_STRU
 �ṹ˵��  : ID_MMC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND��Ӧ�Ľṹ��
 1.��    ��: 2014��11��28��
   ��    ��: w00281933
   �޸�����: ����
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                          MsgHeader;                    /* _H2ASN_Skip */

    NAS_MSCC_PIF_SCELL_MEAS_REPORT_TYPE_UN        unMeasReportType;             /* �����ϱ����� */
    NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_STRU          stLteRssi;                    /* LTE cell Signal INFO */
}NAS_MSCC_PIF_LMM_CELL_SIGN_INFO_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_START_CNF_STRU
 �ṹ˵��  : mmc��mma���Ϳ����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_START_RESULT_ENUM_UINT32                   ulResult;
}NAS_MSCC_PIF_START_CNF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU
 �ṹ˵��  : mmc��mma����ϵͳ��Ϣ����Ϣ�ṹ
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
 7.��    ��   : 2015��7��20��
   ��    ��   : w000316404
   �޸�����   : R11Э������(LTEƵ������ֵ��չ)

*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enCurNetWork;                           /* ��ǰ�������� */
    VOS_UINT8                                               ucRac;
    VOS_UINT8                                               ucSysSubMode;                           /* פ�������ϵͳ��ģʽ��ȡֵ��RRC_NAS_SYS_SUBMODE_ENUM��ͬ */
    VOS_UINT8                                               ucIsFobbiddenPlmnFlag;
    VOS_UINT16                                              usLac;                                  /* λ������Ϣ */
    VOS_UINT8                                               ucRoamFlag;                             /* ��ǰ�Ƿ������� */
    VOS_UINT8                                               ucPsSupportFlg;                         /* ��ǰ�Ƿ�֧��PS�� */
    NAS_MSCC_PIF_CAMP_CELL_INFO_STRU                        stCellId;                               /* С����Ϣ */
    VOS_UINT8                                               ucPsAttachAllowFlag;
    VOS_UINT8                                               ucCsAttachAllowFlag;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    NAS_MSCC_PIF_LMM_ACCESS_TYPE_ENUM_UINT8                 enLmmAccessType;
    VOS_UINT32                                              ulArfcn;
}NAS_MSCC_PIF_3GPP_SYS_INFO_IND_STRU;

typedef VOS_UINT16 NAS_MSCC_PIF_REG_FAIL_CAUSE_UINT16;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_REG_RESULT_IND_STRU
 �ṹ˵��  : mmc��mma���;ܾ�ԭ��ֵ��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��8��15��
   ��    ��   : l00208543
   �޸�����   : �½�
 2.��    ��   : 2013��12��13��
   ��    ��   : w00176964
   �޸�����   : Volte_PhaseIII ��Ŀ:�޸Ľṹ��
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId;
    VOS_UINT8                                ucRegRslt;                              /* VOS_TRUE:ָ����ע��ɹ�; ��֮ע��ʧ�� */
    VOS_UINT8                                ucReportCauseCtrl;                      /* �Ƿ���Ҫ�ϱ�ԭ��ֵ */
    NAS_MSCC_PIF_REG_FAIL_CAUSE_UINT16       enRejCause;
    VOS_UINT8                                ucOriginalRejCause;
    VOS_UINT8                                aucReserve[3];
    NAS_MSCC_PIF_CAMP_POSITION_STRU          stCampPostion;
}NAS_MSCC_PIF_REG_RESULT_IND_STRU;

typedef VOS_UINT16 NAS_MSCC_PIF_SIM_AUTH_FAIL_UINT16;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU
 �ṹ˵��  : mmc��mma����USIM��Ȩʧ��ԭ��ֵ��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��11��15��
   ��    ��   : m00217266
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        MsgHeader;                      /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32          enCnDomainId;
    NAS_MSCC_PIF_SIM_AUTH_FAIL_UINT16           enRejCause;
    VOS_UINT8                                   aucReserve[2];
    NAS_MSCC_PIF_CAMP_POSITION_STRU             stCampPostion;
}NAS_MSCC_PIF_USIM_AUTH_FAIL_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU
 �ṹ˵��  : mmc��mma����ע��״̬�ͷ���״̬����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2013��11��20��
   ��    ��   : w00176964
   �޸�����   : Volte PhaseII��Ŀ�޸�:����CSPS��SIM��״̬
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                         MsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT32                                   bitOpSrvSta     : 1;
    VOS_UINT32                                   bitOpRegSta     : 1;
    VOS_UINT32                                   bitSpare        : 30;

    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32           enCnDomainId;
    VOS_UINT8                                    ucSimCsRegStatus;
    VOS_UINT8                                    ucSimPsRegStatus;
    VOS_UINT8                                    aucReserved[1];
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8            enRegState;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32      enServiceStatus;
    VOS_UINT32                                   ulOosCause;
}NAS_MSCC_PIF_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_MM_INFO_IND_STRU
 �ṹ˵��  : mmc��mma����MM INFORMATION����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT8                                               ucIeFlg;
    VOS_INT8                                                cLocalTimeZone;
    VOS_UINT8                                               ucDST;
    VOS_UINT8                                               aucLSAID[3];
    VOS_UINT8                                               aucReserve[2];
    TIME_ZONE_TIME_STRU                                     stUniversalTimeandLocalTimeZone;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    stName;
}NAS_MSCC_PIF_MM_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU
 �ṹ˵��  : mma��mmc�����ź��ϱ����õ���Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucActionType;
    VOS_UINT8                           ucRrcMsgType;
    VOS_UINT8                           ucSignThreshold;                        /* �ź������ı�����ֵ */
    VOS_UINT8                           ucMinRptTimerInterval;                  /* ����ϱ���ʱ��   */
}NAS_MSCC_PIF_SIGN_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU
 �ṹ˵��  : mma��mmc����ģʽ�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsMode;
}NAS_MSCC_PIF_MODE_CHANGE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ATTACH_REQ_STRU
 �ṹ˵��  : mma��mmc����attach �������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��2��8��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enAttachType;
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32              enEpsAttachReason;
}NAS_MSCC_PIF_ATTACH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ATTACH_CNF_STRU
 �ṹ˵��  : mmc��mma����attach �������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
}NAS_MSCC_PIF_ATTACH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DETACH_REQ_STRU
 �ṹ˵��  : mma��mmc����detach�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��2��8��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enDetachType;
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32                  enDetachReason;
}NAS_MSCC_PIF_DETACH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DETACH_CNF_STRU
 �ṹ˵��  : mmc��mma����detach�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    VOS_UINT32                                              ulOpID;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    NAS_MSCC_PIF_OPER_RESULT_ENUM_UINT32                    enOperRslt;       /* ������� */
}NAS_MSCC_PIF_DETACH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DETACH_IND_STRU
 �ṹ˵��  : mmc��mma��������detach�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2014��4��1��
   ��    ��   : z00161729
   �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    VOS_UINT32                                              ulDetachCause;
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8             enNetworkDetachType;
    VOS_UINT8                                               ucOriginalDetachCause;
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_PIF_CAMP_POSITION_STRU                         stCampPostion;
}NAS_MSCC_PIF_DETACH_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_LIST_REQ_STRU
 �ṹ˵��  : mma��mmc����list�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_LIST_CNF_STRU
 �ṹ˵��  : mmc��mma����list�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulCnt;
    NAS_MSCC_PIF_PLMN_ID_STRU           aPlmnList[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucPlmnStatus[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucRaMode[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_PLMN_LIST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_LIST_REJ_STRU
 �ṹ˵��  : mmc��mma����list�����������reject����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_REJ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU
 �ṹ˵��  : mma��mmc����list������ֹ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_LIST_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU
 �ṹ˵��  : mma��mmc�����û���ѡ�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32                  enPlmnSelMode;
}NAS_MSCC_PIF_PLMN_USER_RESEL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU
 �ṹ˵��  : mma��mmc�����û�ָ�������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enAccessMode;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_SPECIAL_REQ_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU
 �ṹ˵��  : mmc��mma���ͽ������������뿪������ָʾ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENUM_UINT32      enCoverageChgMode;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enCsSvcSta;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enPsSvcSta;
    VOS_UINT32                                              ulTimMaxFlg;
}NAS_MSCC_PIF_COVERAGE_AREA_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_POWER_OFF_REQ_STRU
 �ṹ˵��  : mma��mmc���͹ػ��������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32                enCause;
}NAS_MSCC_PIF_POWER_OFF_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_POWER_OFF_CNF_STRU
 �ṹ˵��  : mmc��mma���͹ػ��ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_POWER_OFF_CNF_STRU;


typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult;
}NAS_MSCC_PIF_SYSTEM_ACQUIRE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU
 �ṹ˵��  : mmc��mma�����û�ָ�������ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            MsgHeader;                  /* _H2ASN_Skip */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8 enResult;
    VOS_UINT8                                       aucReserved[3];
}NAS_MSCC_PIF_PLMN_SPECIAL_SEL_CNF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU
 �ṹ˵��  : mmc��mma����at+cops=0�ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8         enResult;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_RESEL_CNF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU
 �ṹ˵��  : mmc��mma����pdp�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8                  enDataTranAttri;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_DATATRAN_ATTRI_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU
 �ṹ˵��  : mma��mmc����syscfg�����������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_RAT_PRIO_STRU                              stRatPrioList;
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;
    NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8                 enRoamCapability;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    VOS_UINT8                                               aucReserved[1];
}NAS_MSCC_PIF_SYS_CFG_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CL_ASSOCIATED_INFO_NTF_STRU
 �ṹ˵��  : MSCC�յ�1xϵͳ������Ϣ���MMC����CL_ASSOCIATED_INFO
 1.��    ��   : 2015��9��11��
   ��    ��   : y00346957
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enLteSysPriClass;
    VOS_UINT8                                               ucAllowSrchLteFlg;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_CL_ASSOCIATED_INFO_NTF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU
 �ṹ˵��  : mmc��mma����syscfg���ý������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32             enRst;
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PIF_SYS_CFG_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CDMA_INIT_LOC_INFO_STRU
 �ṹ˵��  : cdma��λ����Ϣ
 1.��    ��   : 2015��12��10��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulMcc;
    VOS_INT32       lSid;
    VOS_INT32       lNid;
} NAS_MSCC_PIF_CDMA_INIT_LOC_INFO_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU
 �ṹ˵��  : mscc��mmc���������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2/4/2015
   ��    ��   : w00176964
   �޸�����   : CDMA Iteraiton 10 Modified
 3.��    ��   : 30/5/2015
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 12
 4.��    ��   : 10/12/2015
   ��    ��   : l00324781
   �޸�����   : CL_MUTIMODE_OPTIMIZE ����stCdmaInitLocInfo
 5.��    ��   : 2015/12/10
   ��    ��   : w00176964
   �޸�����   : CL_MUTIMODE_OPTIMIZE������������
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32                     enAcqReason;
    NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32               enSrchType;
    NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU                    stInitAcqPlmnInfo;
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stHighPrioPlmnList;

    NAS_MSCC_PIF_CDMA_INIT_LOC_INFO_STRU                    stCdmaInitLocInfo;
}NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU;


typedef NAS_MSCC_PIF_PLMN_SEARCH_REQ_STRU MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU
 �ṹ˵��  : mmc��mma���������������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2015��4��14��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration Modified:add coverage flag
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enResult;
    VOS_UINT8                                               ucLteCoverageFlg;   /* VOS_TRUE:lte exist coverage; VOS_FALSE:LTE exist no coverage */
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_PIF_PLMN_SELECTION_RLST_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU
 �ṹ˵��  : mmc��mma����������ʼ��ʾ�Ľṹ
 1.��    ��   : 2013��10��09��
   ��    ��   : l00208543
   �޸�����   : �½�,DTS2013100904573
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_SELECTION_START_FLAG_ENUM_UINT32      enPlmnSeleStartFlag;
}NAS_MSCC_PIF_PLMN_SELECTION_START_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU
 �ṹ˵��  : mmc��mma����list������ֹ�ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulCnt;
    NAS_MSCC_PIF_PLMN_ID_STRU           aPlmnList[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucPlmnStatus[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucRaMode[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                           aucReserved2[3];
}NAS_MSCC_PIF_PLMN_LIST_ABORT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU
 �ṹ˵��  : mma��mmc����ָ��������ֹ�������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU
 �ṹ˵��  : mmc��mma������ָֹ�������ظ�����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_SPEC_PLMN_SEARCH_ABORT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU
 �ṹ˵��  : mmc��mma�ϱ�W��cipher��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucCipherAlgorForCSDomain;
    VOS_UINT8                           ucCipherAlgorForPSDomain;
    VOS_UINT8                           aucRcv[2];
}NAS_MSCC_PIF_UMTS_CIPHER_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU
 �ṹ˵��  : mmc��mma�ϱ�G��cipher��Ϣ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucGprsCipherAlg;
    VOS_UINT8                           ucGprsCipher;
    VOS_UINT8                           aucRcv[2];
}NAS_MSCC_PIF_GPRS_CIPHER_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU
 �ṹ˵��  : MMC��MMA�����û�ָ���Ѿܾ��������Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_PLMN_SPECIAL_SEL_REJ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU
 �ṹ˵��  : MMC��MMA����С��������Ϣ�仯ָʾ����Ϣ�ṹ
 1.��    ��   : 2013��3��25��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_CELL_RESTRICTION_TYPE_ENUM_UINT8           enCellAcType;
    VOS_UINT8                                               ucRestrictRegister;
    VOS_UINT8                                               ucRestrictPagingRsp;
    VOS_UINT8                                               ucReserved;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId;
}NAS_MSCC_PIF_AC_INFO_CHANGE_IND_STRU;


/*******************************************************************************
 �ṹ��    : NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU
 �ṹ˵��  : NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU��Ϣ�ṹ
 1.��    ��  : 2013��04��16��
   ��    ��  : z00161729
   �޸�����  : �����ṹ
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */

    VOS_UINT8                           ucOmConnectFlg;                         /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM���õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */
    VOS_UINT8                           aucRsv2[2];                             /* ����   */
} NAS_MSCC_PIF_OM_MAINTAIN_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU
 �ṹ˵��  : mma��mmc����UPLMN����֪ͨ����Ϣ�ṹ
 1.��    ��   : 2013��7��31��
   ��    ��   : w00167002
   �޸�����   : �½��ṹ��
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv4[4];                             /* ����   */
}NAS_MSCC_PIF_UPDATE_UPLMN_NTF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU
 �ṹ˵��  : AT��MMA��EOPLMN���ýӿ�
 1.��    ��  : 2013��10��15��
   ��    ��  : s00190137
   �޸�����  : �����ṹ
 2.��    ��  : 2013��11��26��
   ��    ��  : s00190137
   �޸�����  : ��ӷ�����ƣ����������������50��OPLMN
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    TAF_UINT8                           aucVersion[NAS_MSCC_PIF_MAX_USER_OPLMN_VERSION_LEN];        /* OPLMN List�汾�� */
    TAF_UINT8                           ucIndex;                                /* ��ǰ���õ���Index */
    TAF_UINT8                           ucOPlmnCount;                           /* ����ʵ������OPLMN�ĸ��� */
    TAF_UINT8                           aucOPlmnWithRat[NAS_MSCC_PIF_MAX_GROUP_CFG_OPLMN_DATA_LEN];  /* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MSCC_PIF_EOPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU
 �ṹ˵��  : mmc��mma����AT^EOPLMN���ûظ�����Ϣ�ṹ
 1.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulResult;                               /* OPLMN��nv������*/
}NAS_MSCC_PIF_EOPLMN_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU
 �ṹ˵��  : AT^EOPLMN���ó�ʱ֪ͨMMC�ж���Ϣ����Ľṹ
 1.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_EOPLMN_SET_ABORT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_NET_SCAN_REQ_STRU
 �ṹ˵��  : MMA��MMC��NETSCAN���ýӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */

    VOS_UINT16                                              usCellNum;          /* ��Ҫɨ����������޵�С������ */
    VOS_INT16                                               sCellPow;           /* С������ֵ */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    ucRat;              /* ��Ҫɨ��Ľ���ģʽ */
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;             /* ��¼GUƵ��*/
}NAS_MSCC_PIF_NET_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_NET_SCAN_INFO_STRU
 �ṹ˵��  : ɨ��ĳ��Ƶ���������Ϣ
 1.��    ��   : 2013��8��24��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;                                /* Ƶ�� */
    VOS_UINT16                                              usC1;                                   /* ����GSMС����ѡ��C1ֵ(�ݲ�֧��) */
    VOS_UINT16                                              usC2;                                   /* ����GSMС����ѡ��C2ֵ(�ݲ�֧��) */
    VOS_UINT16                                              usLac;                                  /* λ������ */
    VOS_UINT32                                              ulMcc;                                  /* PLMN������ */
    VOS_UINT32                                              ulMnc;                                  /* PLMN������ */
    VOS_UINT16                                              usBsic;                                 /* GSMС����վ�� */
    VOS_INT16                                               sRxlev;                                 /* ���յ����ź�ǿ�� */
    VOS_INT16                                               sRssi;                                  /* GSM��BCCH�ŵ���RSSI��WCDMA��RSCP */
    VOS_UINT8                                               aucReserve[2];
    VOS_UINT32                                              ulCellId;                               /* С��ID */
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU                  stBand;                               /* ����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β��� */
}NAS_MSCC_PIF_NET_SCAN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_NET_SCAN_CNF_STRU
 �ṹ˵��  : MMC�ϱ���MMA��NETSCAN CNF�ӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */

    NAS_MSCC_PIF_NET_SCAN_RESULT_ENUM_UINT8                 enResult;
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8                  enCause;
    VOS_UINT8                                               ucFreqNum;          /* �ϱ���Ƶ����� */
    VOS_UINT8                                               aucReserve[1];
    NAS_MSCC_PIF_NET_SCAN_INFO_STRU                         astNetScanInfo[NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM];
}NAS_MSCC_PIF_NET_SCAN_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SERV_REJ_IND_STRU
 �ṹ˵��  : mmc��mma���ͷ��񱻾ܵ���Ϣ�ṹ
 1.��    ��   : 2014��4��1��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId;
    VOS_UINT16                          usRejCause;
    VOS_UINT8                           ucOriginalRejCause;
    VOS_UINT8                           aucReserve[1];
    NAS_MSCC_PIF_CAMP_POSITION_STRU     stCampPostion;
}NAS_MSCC_PIF_SERV_REJ_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU
 �ṹ˵��  : MMA��MMC��NETSCAN���ýӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_ABORT_NET_SCAN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU
 �ṹ˵��  : MMC�ϱ���MMA��NETSCAN CNF�ӿ�
 1.��    ��  : 2013��10��10��
   ��    ��  : w00242748
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */

    VOS_UINT8                           ucFreqNum;                                      /* �ϱ���Ƶ����� */
    VOS_UINT8                           aucReserve[3];
    NAS_MSCC_PIF_NET_SCAN_INFO_STRU     astNetScanInfo[NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM];
}NAS_MSCC_PIF_ABORT_NET_SCAN_CNF_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU
 �ṹ˵��  : ֪ͨ����ҵ����Ϣ������Ϣ
 1.��    ��  : 2013��7��9��
   ��    ��  : y00245242
   �޸�����  : �����ṹ
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */
    NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8                enNwImsVoCap ;
    NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8                   enNwEmcBsCap ;
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8                enLteCsCap ;
    VOS_UINT8                                               aucReserve[1];
}NAS_MSCC_PIF_NETWORK_CAPABILITY_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CAMP_ON_IND_STRU
 �ṹ˵��  : MMC����MMA��פ����Ϣ�ṹ
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �½��ṹ��
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT8                           ucCampOnFlg;                            /* VOS_TRUE:פ��;VOS_FALSE:δפ�� */
    VOS_UINT8                           aucRsv[3];                              /* ����   */
}NAS_MSCC_PIF_CAMP_ON_IND_STRU_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU
 �ṹ˵��  : modem1����ϢĿǰֻ��פ����Ϣ
 1.��    ��   : 2013��11��23��
   ��    ��   : z00161729
   �޸�����   : �½�
 2.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU         stMsgHeader;                                   /*_H2ASN_Skip*/
    VOS_UINT32                   bitOpCurrCampPlmnId:1;

    VOS_UINT32                   bitOpEplmnInfo:1;
    VOS_UINT32                   bitSpare:30;

    NAS_MSCC_PIF_PLMN_ID_STRU    stCurrCampPlmnId;                              /* ������д��ǰפ��С����PLMN������������߹ػ��ȷ�פ��״̬��ͳһ��дȫ0xff */
    NAS_MSCC_PIF_EPLMN_INFO_STRU stEplmnInfo;
} NAS_MSCC_PIF_OTHER_MODEM_INFO_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU
 �ṹ˵��  : modem1��dplmn/nplmn��Ϣ
 1.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�

*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                   stMsgHeader;         /*_H2ASN_Skip*/

    VOS_UINT8                                               ucEHplmnNum;
    VOS_UINT8                                               aucReserved[3];
    VOS_UINT8                                               aucEHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                  stSelfLearnDplmnNplmnInfo;
} NAS_MSCC_PIF_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MSCC_PIF_TDS_NCELL_INFO_STRU
 �ṹ˵��  : GSM�µ�TDSƵ���б�

 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                          /* 0��ʾTDDƵ�㲻���� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausTdsArfcnList[NAS_MSCC_PIF_TDS_ARFCN_MAX_NUM];
}NAS_MSCC_PIF_TDS_NCELL_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_MSCC_PIF_LTE_NCELL_INFO_STRU
 �ṹ˵��  : GSM�µ�LTEƵ���б�

 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2015��7��20��
   ��    ��   : w000316404
   �޸�����   : R11Э������(LTEƵ������ֵ��չ)

*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                          /* 0��ʾLTEƵ�㲻���� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          aulLteArfcnList[NAS_MSCC_PIF_LTE_ARFCN_MAX_NUM];
}NAS_MSCC_PIF_LTE_NCELL_INFO_STRU;


/*******************************************************************************
 �ṹ��    : NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU
 �ṹ˵��  : ID_NAS_MSCC_PIF_NCELL_INFO_NOTIFY��Ϣ��Ӧ�Ľṹ��
             ����GSM�µ�TDS/LTE�����ṹ�е�TDS/LTE��Ƶ���б�

 1.��    ��   : 2013��12��23��
   ��    ��   : z00161729
   �޸�����   : �����ɽṹ

*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_TDS_NCELL_INFO_STRU    stTdsNcellInfo;
    NAS_MSCC_PIF_LTE_NCELL_INFO_STRU    stLteNcellInfo;
}NAS_MSCC_PIF_NCELL_INFO_NOTIFY_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_EPLMN_INFO_IND_STRU
 �ṹ˵��  : ��Чplmn��Ϣ
 1.��    ��   : 2013��12��23��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_EPLMN_INFO_STRU        stEplmnInfo;
}NAS_MSCC_PIF_EPLMN_INFO_IND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU
 �ṹ˵��  : mmc�ϱ�csҵ����������״ָ̬ʾ��Ϣ�ṹ
 1.��    ��   : 2014��3��4��
   ��    ��   : z00161729
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           ucCsServiceConnStatusFlag;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_CS_SERVICE_CONN_STATUS_IND_STRU;

/*******************************************************************************
�ṹ��    : NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU
�ṹ˵��  : ID_NAS_MSCC_PIF_PS_TRANSFER_NOTIFY��Ϣ�ṹ
1.��    ��   : 2014��1��5��
  ��    ��   : z00161729
  �޸�����   : �½�
2.��    ��   : 2014��01��17��
  ��    ��   : l00198894
  �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    MTC_PS_TRANSFER_ENUM_UINT8          enSolutionCfg;                          /* PS��Ǩ�Ʒ��� */
    VOS_UINT8                           ucCause;                                /* PS���л�ԭ��ֵ */
    VOS_UINT8                           aucReserved[2];                         /*����λ*/
} NAS_MSCC_PIF_PS_TRANSFER_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU
 �ṹ˵��  : MMA֪ͨMMC��ǰIMS VOICE�Ƿ���õ���Ϣ
 1.��    ��   : 2013��12��10��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2015��4��24��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    MsgHeader;          /* _H2ASN_Skip */

    VOS_UINT8                                               ucAvail;            /* IMS VOICE�Ƿ���� */

    VOS_UINT8                                               ucIsExistPersistentBearer;  /* 0:�����ڣ�1������*/
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_PIF_IMS_VOICE_CAP_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ACQ_REQ_STRU
 �ṹ˵��  : ��ȡ��Ϣ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��4��24��
   ��    ��   : w00176964
   �޸�����   : CDMA 1x Iteration 10 Modified
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32 enAcqReason;
    VOS_UINT8                           ucNotRegAfterAcqSucc;                  /* �����ɹ����Ƿ���ע��:
                                                                                   VOS_FALSE:�����ɹ�����ע��(default)
                                                                                   VOS_TRUE:�����ɹ��󲻷���ע�� */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_PIF_ACQ_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ACQ_CNF_STRU
 �ṹ˵��  : ��ȡ����Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��7��20��
   ��    ��   : w000316404
   �޸�����   : R11Э������(LTEƵ������ֵ��չ)
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32                     enAcqRslt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulArfcn;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_ACQ_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_REG_CELL_INFO_STRU
 �ṹ˵��  : ע����Ϣ��Cell Info�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��7��20��
   ��    ��   : w000316404
   �޸�����   : R11Э������(LTEƵ������ֵ��չ)
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8       ucRat;
    VOS_UINT8                                  ucPlmnNum;
    VOS_UINT8                                  ucCellNum;
    VOS_UINT8                                  aucReserved[1];
    VOS_UINT32                                 ulArfcn;
    NAS_MSCC_PIF_PLMN_ID_STRU                  astPlmnId[NAS_MSCC_PIF_REG_MAX_PLMN_NUM];
    VOS_UINT16                                 ausCellId[NAS_MSCC_PIF_REG_MAX_CELL_NUM];
} NAS_MSCC_PIF_REG_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_REG_REQ_STRU
 �ṹ˵��  : ע����Ϣ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT32                                              bitOpPrioClass  : 1;
    VOS_UINT32                                              bitOpCellInfo   : 1;
    VOS_UINT32                                              bitSpare        : 30;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_REG_CELL_INFO_STRU                         stCellInfo;
}NAS_MSCC_PIF_REG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_REG_CNF_STRU
 �ṹ˵��  : ע�����Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��7��20��
   ��    ��   : w000316404
   �޸�����   : R11Э������(LTEƵ������ֵ��չ)
 3.��    ��   : 2015��8��20��
   ��    ��   : wx270776
   �޸�����   : VIA CL DTS2015031602665
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32                     enRegRslt;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulArfcn;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass;
    MMC_MSCC_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus;
    VOS_UINT8                                               aucReserve[2];
}NAS_MSCC_PIF_REG_CNF_STRU;


enum NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM
{
    NAS_MSCC_PIF_POWER_SAVE_SUCCESS             = 0 ,
    NAS_MSCC_PIF_POWER_SAVE_FAILURE             = 1 ,
    NAS_MSCC_PIF_POWER_SAVE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_POWER_SAVE_REQ_STRU
 �ṹ˵��  : Power save��Ϣ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                       stMsgHeader;                     /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_SAVE_TYPE_ENUM_UINT8    enPowerSaveReason;               /* POWER SAVEԭ��ֵ */
    VOS_UINT8                                  aucReserve[3];
}NAS_MSCC_PIF_POWER_SAVE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_POWER_SAVE_CNF_STRU
 �ṹ˵��  : Power save����Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
 2.��    ��   : 2015��4��07��
   ��    ��   : m00270891
   �޸�����   : Added the result Enum.
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;                     /* _H2ASN_Skip */
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_POWER_SAVE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_ACQ_IND_STRU
 �ṹ˵��  : ��ȡָʾ�Ľṹ��
 1.��    ��   : 2014��1��26��
   ��    ��   : s00246516
   �޸�����   : �½�
*****************************************************************************/
typedef  NAS_MSCC_PIF_ACQ_CNF_STRU NAS_MSCC_PIF_ACQ_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU
 �ṹ˵��  : mmc�ϱ�psҵ����������״ָ̬ʾ��Ϣ�ṹ
 1.��    ��   : 2014��6��27��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                                       ucPsServiceConnStatusFlag;
    MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8           enPsSigType;
    VOS_UINT8                                       aucReserved[2];
}NAS_MSCC_PIF_PS_SERVICE_CONN_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU
 �ṹ˵��  : MMC֪ͨMMA��ǰ�Ƿ���RF��Դ����
 1.��    ��   : 2014��6��30��
   ��    ��   : W00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*/
    NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_ENUM_UINT8           enRatType;
    VOS_UINT8                                               ucRfAvailFlg;       /* VOS_TRUE:��Ƶ��Դ����;VOS_FALSE:RF��Դ������ */
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU
 �ṹ˵��  : ҵ�񴥷�����������ģʽ�б�
 1.��    ��   : 2015��5��15��
   ��    ��   : L00301449
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucRatNum;
    NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_ENUM_UINT8                aenRatType[NAS_MSCC_PIF_SRV_ACQ_RAT_NUM_MAX];
}NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SRV_ACQ_REQ_STRU
 �ṹ˵��  : ҵ�񴥷�����ָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
} NAS_MSCC_PIF_SRV_ACQ_REQ_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SRV_ACQ_CNF_STRU
 �ṹ˵��  : ҵ�񴥷��������
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8          enResult;
    VOS_UINT8                                       aucReserved[3];
} NAS_MSCC_PIF_SRV_ACQ_CNF_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU
 �ṹ˵��  : ҵ�񴥷�������ʼָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
}NAS_MSCC_PIF_BEGIN_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU
 �ṹ˵��  : ҵ�񴥷���������ָʾ
 1.��    ��   : 2014��5��28��
   ��    ��   : h00246512
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*/
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType;
    VOS_UINT8                           aucReserved[3];
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU  stRatList;
}NAS_MSCC_PIF_END_SESSION_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU
 �ṹ˵��  : ID_NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY�Ľṹ��
 1.��    ��   : 2014��11��06��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                       stMsgHeader;                     /* _H2ASN_Skip */
    VOS_UINT8                                  ucImsCallFlg;
    VOS_UINT8                                  aucReserve[3];
}NAS_MSCC_PIF_IMS_SRV_INFO_NOTIFY_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU
 * Description : Mo Call start notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_START_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU
 * Description : Call redial notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8     enCause;
    VOS_UINT8                                   aucReserve[2];
}NAS_MSCC_PIF_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU
 * Description : Mo Call success notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_SUCCESS_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU
 * Description : Mo Call end notification
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8      enCallType;
    VOS_UINT8                                   aucReserve[3];
}NAS_MSCC_PIF_CDMA_MO_CALL_END_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU
 * Description : Start confirm
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;                    /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENUM_UINT8 enFreqLockMode;
    VOS_UINT8                                   aucReserve[1];
    VOS_UINT16                                  usCdmaBandClass;
    VOS_UINT16                                  usSid;
    VOS_UINT16                                  usNid;
    VOS_UINT16                                  usCdmaFreq;
    VOS_UINT16                                  usCdmaPn;
    VOS_UINT16                                  usHrpdBandClass;
    VOS_UINT16                                  usHrpdFreq;
    VOS_UINT16                                  usHrpdPn;
    VOS_UINT8                                   aucReserve1[2];
}NAS_MSCC_PIF_CFREQ_LOCK_NTF_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU
 * Description : CdmaCsq set parameters
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRssiRptThreshold;
    VOS_UINT8                           ucEcIoRptThreshold;
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           aucReserve[1];
}NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU  stCdmaCsq;
}NAS_MSCC_PIF_CDMACSQ_SET_REQ_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                /* _H2ASN_Skip */
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt;
    VOS_UINT8                                       auReserved[3];
}NAS_MSCC_PIF_CDMACSQ_SET_CNF_STRU;


/** ****************************************************************************
 * Name        : XSD_MMA_CDMACSQ_IND_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    VOS_INT16                               sCdmaRssi;
    VOS_INT16                               sCdmaEcIo;
}NAS_MSCC_PIF_CDMACSQ_IND_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU
 * Description : HDRCsq set parameters
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimeInterval;
    VOS_UINT8                           ucRssiThreshold;
    VOS_UINT8                           ucSnrThreshold;
    VOS_UINT8                           ucEcioThreshold;
}NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_REQ_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /* _H2ASN_Skip */
    NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU  stHdrCsq;
}NAS_MSCC_PIF_HDR_CSQ_SET_REQ_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_HDR_CSQ_SET_CNF_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                            stMsgHeader;                /* _H2ASN_Skip */
    NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_ENUM_UINT8      enRslt;
    VOS_UINT8                                       auReserved[3];
}NAS_MSCC_PIF_HDR_CSQ_SET_CNF_STRU;


/** ****************************************************************************
 * Name        : XSD_MMA_HDR_CSQ_IND_STRU
 * Description :
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    VOS_INT16                               sHrpdRssi;
    VOS_INT16                               sHrpdSnr;
    VOS_INT16                               sHrpdEcio;
    VOS_UINT8                               aucRsv[2];
}NAS_MSCC_PIF_HDR_CSQ_IND_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_REG_INFO_STRU
 * Description : Register info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRegZone;      /**<  Registration zone */
    VOS_UINT8                           ucRegZoneNum;   /**<  Number of registration zones to be retained */

    /* for reg */
    VOS_UINT8                           ucZoneTimer;    /**<  Zone timer length */

    /* for reg */
    VOS_UINT8                           ucMultiSidFlg;  /**<  Multiple SID storage indicator */

    /* for reg */
    VOS_UINT8                           ucMultiNidFlg;  /**<  Multiple NID storage indicator */

    /* for reg */
    VOS_UINT16                          usRegDistance;  /**<  Registration distance */

    /* for reg */
    VOS_UINT8                           ucRegPeriod;    /**<  Registration period */

    /* for reg */
    VOS_UINT8                           ucHomeReg;      /**<  Home registration indicator */

    /* for roam */
    VOS_UINT8                           ucSidRoamReg;   /**<  SID roamer registration indicator */

    /* for roam */
    VOS_UINT8                           ucNidRoamReg;   /**<  NID roamer registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerUpReg;   /**<  Power-up registration indicator */

    /* for reg */
    VOS_UINT8                           ucPowerDownReg; /**<  Power-down registration indicator */

    /* for reg */
    VOS_UINT8                           ucParameterReg; /**<  Parameter-change registration indicator */

    /* for reg */
    VOS_UINT8                           aucReserve[1];
}NAS_MSCC_PIF_OHM_REG_INFO_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_SERVICE_INFO_STRU
 * Description : Service info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMaxAltSo;            /**<  Max. Num. of alternative service options,for Origination or Page Response Message */
    VOS_UINT8                           ucSDBSupported;        /**<  Short Data Burst supported indicator */
    VOS_UINT8                           ucMoQos;               /**<  permission indicator for QoS in Origination message */
    VOS_UINT8                           ucConcurrentSupported; /**<  concurrent service supported */
    VOS_UINT8                           ucMoPosSupported;      /**<  MS initiated position location supported */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usImsi11_12;           /**<  11th and 12th digits of the IMSI */
    VOS_UINT32                          ulMcc;                 /**<  Mobile country code */
    VOS_UINT16                          usMnc;                 /**<  Mobile network code */
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU;

/** ****************************************************************************
 * Name        : XSD_MMA_OHM_BASE_STATION_INFO_STRU
 * Description : Base station info of Overhead Message
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usBaseId;        /**<  Base station identification */

    /* for user zone */
    VOS_UINT8                           ucBaseClass;     /**<  Base station class */
    VOS_UINT8                           aucReserve[1];
    VOS_INT32                           lBaseLatitude;  /**<  Base station latitude */

    /* reg & zone */
    VOS_INT32                           lBaseLongitude; /**<  Base station longitude */

    /* reg & zone */
}NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_1X_SYS_TIME_STRU
 *
 * Description : System time info
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSysTime[5];
    VOS_UINT8                           ucLpSec;
    VOS_INT8                            cLtmOff;
    VOS_UINT8                           ucDaylt;
} NAS_MSCC_PIF_1X_SYS_TIME_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_SYSTEM_TIME_IND_STRU
 * Description : System service Info indication
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    NAS_MSCC_PIF_1X_SYS_TIME_STRU           stSysTime;
}NAS_MSCC_PIF_1X_SYSTEM_TIME_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU
 * Description : System info
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                                  usBandClass;
    VOS_UINT16                                  usFreq;
    VOS_UINT16                                  usSid;             /**<  System identification */
    VOS_UINT16                                  usNid;             /**<  Network identification */
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus;
    VOS_UINT8                                   ucRoamingInd;
    VOS_UINT8                                   ucPrevInUse;
    VOS_UINT8                                   ucPzid;    /* Packet Zone Id */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8           en1xPriClass;         /* 1x priority class */
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8           enAIPriClass;         /* AI priority class */
    PS_BOOL_ENUM_UINT8                          enRegInfoIncl;
    PS_BOOL_ENUM_UINT8                          enBaseStationInfoIncl;
    PS_BOOL_ENUM_UINT8                          enServiceInfoIncl;
    NAS_MSCC_PIF_OHM_REG_INFO_STRU              stRegInfo;
    NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU     stBaseStationInfo;
    NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU          stServiceInfo;
}NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_SERVICE_INFO_IND_STRU
 * Description : System service Info indication
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;                        /* _H2ASN_Skip */
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU       stSysSrvInfo;
}NAS_MSCC_PIF_1X_SYSTEM_SERVICE_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU
 �ṹ˵��  : MMA��MMC��SET CFPLMN REQ�ӿ�
 1.��    ��  : 2015��2��4��
   ��    ��  : f00279542
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8             enCmdType;
    VOS_UINT8                                               aucReserve[3];
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnInfo;
}NAS_MSCC_PIF_CFPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU
 �ṹ˵��  : MMA��MMC��SET CFPLMN QRY REQ�ӿ�
 1.��    ��  : 2015��2��4��
   ��    ��  : f00279542
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserve[4];
}NAS_MSCC_PIF_CFPLMN_QUERY_REQ_STRU;

/*****************************************************************************
 ö����    : NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM_UINT8
 �ṹ˵��  : ApԤ��Dplmn�ĳ���
 1.��    �� : 2015��11��02��
   ��    �� : l00289540
   �޸����� : �����ṹ
*****************************************************************************/
enum NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM
{
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_SWITCH_ON,                                     /* �ϵ翪��Ԥ��DPLMN���� */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_DPLMN_UPDATE,                                  /* Ap Dplmn���ݿ��и��´�������������DPLMN�ĳ��� */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE,                                   /* ���������ĸ���DPLMN�ĳ��� */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_BUTT
};

typedef VOS_UINT8 NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DPLMN_QRY_REQ_STRU
 �ṹ˵��  : MMA��MSCC��DPLMN QRY�ӿ�
  1.��    ��   : 2015��10��8��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* _H2ASN_Skip */
    TAF_MMA_CTRL_STRU                                       stCtrl;
    VOS_UINT8                                               aucReserve[4];
}NAS_MSCC_PIF_DPLMN_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_WITH_RAT_STRU
 �ṹ˵��  : MMA��MSCC��DPLMN SET REQ�ӿ�
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmn;
    VOS_UINT16                                              usRat;
    VOS_UINT8                                               aucReserve[2];
}NAS_MSCC_PIF_PLMN_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MMA_DPLMN_INFO_SET_STRU
 �ṹ˵��  : set dplmnlist������dplmn�б���Ϣ��ehplmn�б���Ϣ�ṹ��
  1.��    ��   : 2015��10��13��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDplmnNum;                                     /* Ԥ��DPLMN�б�ĸ��� */
    VOS_UINT8                           ucEhPlmnNum;                                    /* EHPLMN�ĸ���*/
    VOS_UINT8                           ucReserve;
    NAS_MSCC_PIF_PLMN_ID_STRU           astEhPlmnInfo[TAF_MMA_MAX_EHPLMN_NUM];          /* EHPLMN ID�б� */
    NAS_MSCC_PIF_PLMN_WITH_RAT_STRU     astDplmnList[TAF_MMA_MAX_DPLMN_NUM];            /* DPLMN�б� */
}NAS_MSCC_PIF_DPLMN_INFO_SET_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DPLMN_SET_REQ_STRU
 �ṹ˵��  : MMA��MSCC��DPLMN SET REQ�ӿ�
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    TAF_MMA_CTRL_STRU                                       stCtrl;
    VOS_UINT8                                               ucSeq;                                          /* ��ˮ�� */
    NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_ENUM_UINT8           enApPresetDplmnScene;
    VOS_UINT8                                               aucVersionId[NAS_MSCC_PIF_INFO_VERSION_LEN];     /* �汾�ţ��̶�Ϊxx.xx.xxx */
    VOS_UINT8                                               ucReserved;
    NAS_MSCC_PIF_DPLMN_INFO_SET_STRU                        stDplmnInfo;
}NAS_MSCC_PIF_DPLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CFPLMN_LIST_STRU
 �ṹ˵��  : MMC��MSCC �ϱ�����Ϣ
 1.��    ��  : 2015��2��4��
   ��    ��  : f00279542
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_CFPLMN_OPERATE_TYPE_ENUM_UINT8             ulCmdType;
    VOS_UINT8                                               ucPlmnNum;          /* plmnnum��astplmn���ڴ�Ų�ѯ�Ľ�� */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_PIF_PLMN_ID_STRU                               astPlmn[NAS_MSCC_PIF_MAX_CFPLMN_NUM];
}NAS_MSCC_PIF_CFPLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU
 �ṹ˵��  : MMA��MMC�� CFPLMN CNF�ӿ�
 1.��    ��  : 2015��2��4��
   ��    ��  : f00279542
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enResult;
}NAS_MSCC_PIF_CFPLMN_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU
 �ṹ˵��  : MMA��MMC�� CFPLMN CNF�ӿ�
 1.��    ��  : 2015��2��4��
   ��    ��  : f00279542
   �޸�����  : �����ṹ
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enResult;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT8                                               ucPlmnNum;                         /* plmnnum��astplmn���ڴ�Ų�ѯ�Ľ�� */
    NAS_MSCC_PIF_PLMN_ID_STRU                               astPlmn[NAS_MSCC_PIF_MAX_CFPLMN_NUM];
}NAS_MSCC_PIF_CFPLMN_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_CTRL_STRU
 �ṹ˵��  : NAS_MSCC���ƽṹ��

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulModuleId;         /* ����PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}NAS_MSCC_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_CTRL_STRU
 �ṹ˵��  : NAS_MSCC_PLMN_NAME_LIST_STRU

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    astPlmnName[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT16                                              ausPlmnRat[NAS_MSCC_PIF_MAX_PLMN_CNT];
    VOS_UINT8                                               aucReserved[2];
}NAS_MSCC_PLMN_NAME_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_CTRL_STRU
 �ṹ˵��  : NAS_MSCC_PLMN_NAME_LIST_STRU

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : B00269685
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulPlmnNum;
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    astPlmnName[NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT];
    VOS_UINT16                                              ausPlmnRat[NAS_MSCC_PIF_MAX_CPOL_PLMN_CNT];
}NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU;

/*****************************************************************************
�ṹ��    : NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU
�ṹ˵��  : AT+CPOL��ѯ����ṹ

�޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 �½�
*******************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType;                         /* ��ѯ��Ӫ�����Ƶ����� */
    VOS_UINT8                                               aucReserved1[3];
    VOS_UINT32                                              ulFromIndex;                            /* ��ѯ��Ӫ�����Ƶ���ʼλ�� */
    VOS_UINT32                                              ulPlmnNum;                              /* ��ѯ��Ӫ�����Ƶĸ���������A�˺�C��ͨѶ����Ϣ��С�����ƣ����һ������ѯ50����¼ */
    VOS_UINT32                                              ulValidPlmnNum;                         /* ��Ч�������Ӫ�����Ƹ��� */
}NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU
 �ṹ˵��  : ��ѯ����PREFPLMN����ӿ�
 1.��    ��   : 2015��02��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8              enCmdType;
    VOS_UINT8                                               aucReserve[3];
    VOS_BOOL                                                bPlmnSelFlg;
    NAS_MSCC_CPOL_INFO_QUERY_REQ_STRU                       stCpolInfo;
}NAS_MSCC_PIF_PREF_PLMN_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU
 �ṹ˵��  : ��ѯ����PREFPLMN����ظ��ӿ�
 1.��    ��   : 2015��02��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_CMD_TYPE_ENUM_UINT8              enCmdType;
    VOS_UINT8                                               aucReserve[1];
    VOS_UINT16                                              usPlmnNum;          /* ���ڲ���������� */
    VOS_UINT32                                              ulFromIndex;
    VOS_UINT32                                              ulValidPlmnNum;     /* ��Ч�������Ӫ�����Ƹ��� */
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU                       stPlmnName;
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;
}NAS_MSCC_PIF_PREF_PLMN_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU
 �ṹ˵��  : ����PREFPLMN����ӿ�
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_CTRL_STRU                                      stCtrl;
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                     stPrefPlmnOpt;
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType;
    VOS_UINT8                                               aucReserve[3];
}NAS_MSCC_PIF_PREF_PLMN_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU
 �ṹ˵��  : ����PREFPLMN����ظ��ӿ�
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : Iteration 8 �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /* _H2ASN_Skip */
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;
}NAS_MSCC_PIF_PREF_PLMN_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MMC_TAF_PLMN_INFO_ST
 �ṹ˵��  : ��¼PLMN��Ϣ
 1.��    ��   : 2011��7��20��
   ��    ��   : z00161729
   �޸�����   : ԭMMC_PLMN_ID_STRUɾ���滻ΪTAFMMC_PLMN_ID_STRU
 2.��    ��   : 2013��4��7��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmn;
    VOS_UINT16                          usRaMode;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucReserve1[1];
}MMC_TAF_PLMN_INFO_ST;

typedef struct
{
    MMC_TAF_PLMN_INFO_ST    astPlmnInfo[NAS_MSCC_PIF_MAX_PLMN_NUM];
    VOS_UINT16              usCurPlmnNum;
    VOS_UINT8               aucReserve1[2];
}MMC_TAF_PLMN_LIST_INFO_ST;

/*****************************************************************************
 �ṹ��    : MMC_MMA_SHARE_PARA_ST
 �ṹ˵��  : ��¼MMA��MMC���õ�ȫ�ֱ���
 1.��    ��   : 2011��7��20��
   ��    ��   : z00161729
   �޸�����   : ԭMMC_PLMN_ID_STRUɾ���滻ΪTAFMMC_PLMN_ID_STRU
 2.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : ֧��CEREG�޸ģ���ucGmmRegStatus��ΪucPsRegStatus
 3.��    ��   : 2013��4��7��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
typedef struct
{
    MMC_MMA_PARA_TYPE_ENUM    enMmaParaType;
    union
    {
        MMC_TAF_PLMN_LIST_INFO_ST           stHPlmn;            /*��ȡHPLMN�б�*/
        MMC_TAF_PLMN_LIST_INFO_ST           stUPlmnInfo;
        MMC_TAF_PLMN_LIST_INFO_ST           stOPlmnInfo;
        MMC_TAF_PLMN_LIST_INFO_ST           stHPlmnInfo;
    }u;
}MMC_MMA_SHARE_PARA_ST;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU
 �ṹ˵��  : ָʾIMS�ر�״̬�Ľӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8    enImsSwitch;                    /* IMS��������,1:��,0:�ر� */
    VOS_UINT8                                   aucReserved[3];
}NAS_MSCC_PIF_IMS_SWITCH_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU
 �ṹ˵��  : ָʾVOICE DOMAIN�仯�Ľӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32       enVoiceDomain;                  /* ������ѡ�� */
}NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_START_REQ_STRU
 �ṹ˵��  : ����IMS�����Ľӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;
    VOS_UINT8                           aucReserve[4];
}NAS_MSCC_PIF_IMS_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_START_CNF_STRU
 �ṹ˵��  : IMS��������Ļظ��ӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32   enResult;
}NAS_MSCC_PIF_IMS_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_STOP_REQ_STRU
 �ṹ˵��  : ����IMS�رյĽӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;
    VOS_UINT8                           aucReserve[4];
}NAS_MSCC_PIF_IMS_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_IMS_STOP_CNF_STRU
 �ṹ˵��  : IMS�ر�����Ļظ��ӿ�
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32    enResult;
}NAS_MSCC_PIF_IMS_STOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMC_MMA_LAI_STRU
 �ṹ˵��  : ID_MMC_MMA_SRCHED_PLMN_INFO_IND��Ϣ��lai�Ľṹ��
 1.��    ��   : 2015��01��15��
   ��    ��   : h00285180
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                  stPlmnId;

    VOS_UINT16                                 usLac;
    VOS_UINT8                                  aucReserve[2];
}NAS_MSCC_PIF_LAI_STRU;

/*****************************************************************************
 �ṹ��    : MMC_MMA_SRCHED_PLMN_INFO_IND_STRU
 �ṹ˵��  : ID_MMC_MMA_SRCHED_PLMN_INFO_IND�Ľṹ��
 1.��    ��   : 2015��01��15��
   ��    ��   : h00285180
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                       stMsgHeader;

    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8       enRat;
    VOS_UINT8                                  aucReserved[3];

    VOS_UINT32                                 ulLaiNum;
    NAS_MSCC_PIF_LAI_STRU                      astLai[NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM];
}NAS_MSCC_PIF_SRCHED_PLMN_INFO_IND_STRU;






/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_START_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_START_IND_STRU;

/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_END_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               aucRsv[2];
    NAS_MSCC_PIF_CL_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
}NAS_MSCC_PIF_CL_SYSTEM_ACQUIRE_END_IND_STRU;


typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmnId;                               /* PLMN ID */
    VOS_UINT16                          usSimRat;                               /* SIM����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU;


typedef struct
{
    VOS_UINT8                           ucEhPlmnNum;                        /* EHPLMN�ĸ���*/
    VOS_UINT8                           aucRsv[3];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astEhPlmnInfo[NAS_MSCC_PIF_MAX_EHPLMN_NUM];/* EHPLMN ID�б� */
}NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU
 �ṹ˵��  : SIM���еĵ�ǰUSERPLMN��Ϣ
 1.��    ��   : 2015��4��14��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUserPlmnNum;                          /* UPLMN�ĸ���*/
    VOS_UINT8                           aucReserve3[3];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astUserPlmnInfo[NAS_MSCC_PIF_MAX_USERPLMN_NUM];/* UPLMN���б�*/
}NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU
 �ṹ˵��  : ���浱ǰOPERPLMN��Ϣ
 1.��    ��   : 2015��4��14��
   ��    ��   : w00176964
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOperPlmnNum;                          /* OPLMN�ĸ���*/
    VOS_UINT8                           aucReserve2[2];
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU astOperPlmnInfo[NAS_MSCC_PIF_MAX_OPERPLMN_NUM];/* OPLMN���б�*/
}NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU
 �ṹ˵��  :  PS RATTYPE
 1.��    ��   : 2015��04��13��
   ��    ��   : f0017928
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32        enPsRatType;
}NAS_MSCC_PIF_PS_RAT_TYPE_NTF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_AUTO_RESEL_SET_STRU
 �ṹ˵��  : ����auto resel
 1.��    ��   : 2015��6��3��
   ��    ��   : b00269685
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;
    VOS_UINT8                           ucActiveFlg;                            /* �Ƿ��� */
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_PIF_AUTO_RESEL_SET_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DPLMN_QRY_CNF_STRU
 �ṹ˵��  : DPLMN QRY CNF��Ӧ�Ľṹ��
  1.��    ��   : 2015��10��9��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;
    TAF_MMA_CTRL_STRU                           stCtrl;
    VOS_UINT16                                  ulRslt;
    VOS_UINT8                                   aucVersionId[NAS_MSCC_PIF_INFO_VERSION_LEN];
    VOS_UINT8                                   ucRererse;
}NAS_MSCC_PIF_DPLMN_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_DPLMN_SET_CNF_STRU
 �ṹ˵��  : DPLMN SET CNF��Ӧ�Ľṹ��
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    TAF_MMA_CTRL_STRU                           stCtrl;
    VOS_UINT32                                  ulRslt;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_DPLMN_SET_CNF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_ID_WITH_RAT_STRU
 �ṹ˵��  : �����뼼��plmn id��Ϣ
 1.��    ��   : 2015��9��10��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRatType;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_PLMN_ID_WITH_RAT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU
 �ṹ˵��  : CSG �б���������ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_CSG_LIST_SEARCH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CSG_LIST_REJ_STRU
 �ṹ˵��  : mmc��mma����CSG list����reject����Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_CSG_LIST_REJ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_STRU
 �ṹ˵��  : mscc��mma����CSG list���������Ϣ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    VOS_UINT32                                              ulCsgId;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRatType;
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8           enPlmnWithCsgIdType;
    VOS_UINT8                                               ucCsgTypeLen;
    VOS_UINT8                                               ucReserved;
    VOS_UINT8                                               aucCsgType[NAS_MSCC_PIF_CSG_TYPE_LEN];
    VOS_UINT8                                               ucHomeNodeBNameLen;
    VOS_UINT8                                               aucReserved2[3];
    VOS_UINT8                                               aucHomeNodeBName[NAS_MSCC_PIF_MAX_HOME_NODEB_NAME_LEN];
}NAS_MSCC_PIF_PLMN_WITH_CSG_ID_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU
 �ṹ˵��  : mmc��mma����CSG list���������Ϣ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnWithCsgIdNum;

    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_STRU  astPlmnWithCsgIdList[NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM];
}NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU
 �ṹ˵��  : mscc��mma����CSG list�����������Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU stCsgIdInfo;
}NAS_MSCC_PIF_CSG_LIST_SEARCH_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU
 �ṹ˵��  : mmc��mma����CSG list������ֹ�ظ�����Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    MsgHeader;                              /* _H2ASN_Skip */
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU stCsgIdInfo;
}NAS_MSCC_PIF_CSG_LIST_ABORT_CNF_STRU;



/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU
 �ṹ˵��  : ����CSG list������ֹ����Ϣ�ṹ
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                MsgHeader;                              /* _H2ASN_Skip */
    VOS_UINT32                          ulReserved;
}NAS_MSCC_PIF_CSG_LIST_ABORT_REQ_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_GET_GEO_REQ_STRU
 �ṹ˵��  : ��ȡ������Ϣ�����Ӧ�Ľṹ��
 1.��    ��   : 2015��05��13��
   ��    ��   : s00217060
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_GET_GEO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_GET_GEO_CNF_STRU
 �ṹ˵��  : ��ȡ������Ϣ�ظ���Ӧ�Ľṹ��
 1.��    ��   : 2015��05��13��
   ��    ��   : s00217060
   �޸�����   : �½�
 2.��    ��   : 2015��12��10��
   ��    ��   : l00324781
   �޸�����   : CL_MUTIMODE_OPTIMIZE �޸ģ�����sid��nid
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    NAS_MSCC_PIF_PLMN_ID_STRU                   stPlmnId;
    VOS_INT32                                   lSid; /* Я��Xģ���ѻ�õ�Sid���������δ�ܻ�ȡSid,��д-1 */
    VOS_INT32                                   lNid; /* Я��Xģ���ѻ�õ�Nid���������δ�ܻ�ȡNid,��д-1 */
}NAS_MSCC_PIF_GET_GEO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU
 �ṹ˵��  : ֹͣ��ȡ������Ϣ�����Ӧ�Ľṹ��
 1.��    ��   : 2015��06��01��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_STOP_GET_GEO_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU
 �ṹ˵��  : ֹͣ��ȡ������Ϣ�ظ���Ӧ�Ľṹ��
 1.��    ��   : 2015��06��01��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;
    VOS_UINT8                                   aucReserve[4];
}NAS_MSCC_PIF_STOP_GET_GEO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SID_NID_IND_STRU
 �ṹ˵��  : SIDָʾ
 1.��    ��   : 2015��7��2��
   ��    ��   : y00245242
   �޸�����   : �½�
 2.��    ��   : 2015��12��15��
   ��    ��   : l00324781
   �޸�����   : CL_MUTIMODE_OPTIMIZE ����Nid����Ϣ���ָ�ΪSID_NID
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;                            /*_H2ASN_Skip*//* ��Ϣͷ    */
    VOS_UINT16                          usSid;                                  /* SID */
    VOS_UINT16                          usNid;                                  /* NID */
}NAS_MSCC_PIF_SID_NID_IND_STRU;

/*****************************************************************************
 �ṹ��    : XSD_MSCC_EMC_CALLBACK_IND_STRU
 �ṹ˵��  : ������CALLBACKģʽ״̬����Ϣ�ṹ
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                        stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32  enCallBackState;    /* �Ƿ���CallBackģʽ�� */
} NAS_MSCC_PIF_EMC_CALLBACK_IND_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU
 �ṹ˵��  : �ظ��˳�������CallBack�������Ϣ�ṹ
 1.��    ��   : 2015��07��02��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
} NAS_MSCC_PIF_END_EMC_CALLBACK_IND_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SID_WHITE_LIST_STRU
 �ṹ˵��  : �����SID��MCC��Ϣ

 1.��    ��   : 2015��7��2��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStartSid;
    VOS_UINT16                          usEndSid;
    VOS_UINT32                          ulMcc;
}NAS_MSCC_PIF_SID_WHITE_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_OPER_LOCK_WHITE_SID_STRU
 �ṹ˵��  : �����SID��������Ϣ
  1.��    ��   : 2015��7��2��
    ��    ��   : y00322978
    �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                          /* �������Ƿ�ʹ�� */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    NAS_MSCC_PIF_SID_WHITE_LIST_STRU    astSysInfo[NAS_MSCC_PIF_MAX_WHITE_LOCK_SID_NUM];
}NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU
 �ṹ˵��  : sid white list ��������ṹ��
 1.��    ��   : 2015��07��02��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                    stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU   stSidWhiteList;
}NAS_MSCC_PIF_SET_CSIDLIST_REQ_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU
 �ṹ˵��  : sid white list ���ûظ��ṹ��
 1.��    ��   : 2015��07��02��
   ��    ��   : y00322978
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    VOS_UINT32                          ulRslt;
}NAS_MSCC_PIF_SET_CSIDLIST_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_SERVICE_AVAILABLE_IND_STRU
 �ṹ˵��  : ���������Ϣ�ṹ
 1.��    ��   : 2015��07��25��
   ��    ��   : w00242748
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;        /*_H2ASN_Skip*//* ��Ϣͷ    */
    VOS_UINT16                                              usBandClass;
    VOS_UINT16                                              usFreq;
    VOS_UINT16                                              usSid;             /**<  System identification */
    VOS_UINT16                                              usNid;             /**<  Network identification */
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    VOS_UINT8                                               ucRoamingInd;
    VOS_UINT8                                               aucReserved[3];
}NAS_MSCC_PIF_SYNC_SERVICE_AVAILABLE_IND_STRU;


/** ****************************************************************************
 * Name        : NAS_MSCC_PIF_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU
 *
 * Description : ����ҵ�񴥷��������
 1.��    ��   : 2015��12��16��
   ��    ��   : y00314741
   �޸�����   : �½�
 *******************************************************************************/
typedef struct
{
    MSCC_MSG_HEADER_STRU                                    stMsgHeader;         /*_H2ASN_Skip*//* ��Ϣͷ                                   */
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32                enRslt;
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32                    enRatType;
} NAS_MSCC_PIF_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU;

typedef NAS_MSCC_PIF_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU    MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU;

/*****************************************************************************
 �ṹ��    : MSCC_MMA_HDR_CSQ_SET_REQ_STRU
 �ṹ˵��  : ID_MMA_MSCC_HDR_CSQ_SET_REQ_STRU��Ϣ�ṹ
 1.��    ��   : 2015��10��21��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_HDR_CSQ_SET_REQ_STRU    MMA_MSCC_HDR_CSQ_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSCC_HDR_CSQ_SET_CNF_STRU
 �ṹ˵��  : ID_MMA_MSCC_HDR_CSQ_SET_CNF_STRU��Ϣ�ṹ
 1.��    ��   : 2015��10��21��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_HDR_CSQ_SET_CNF_STRU    MSCC_MMA_HDR_CSQ_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_PIF_HDR_CSQ_IND_STRU
 �ṹ˵��  : ID_NAS_MSCC_PIF_HDR_CSQ_IND��Ϣ�ṹ
 1.��    ��   : 2015��10��21��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
typedef NAS_MSCC_PIF_HDR_CSQ_IND_STRU       MSCC_MMA_HDR_CSQ_IND_STRU;

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

#endif
