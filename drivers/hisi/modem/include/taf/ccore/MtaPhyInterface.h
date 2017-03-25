/******************************************************************************

                  ��Ȩ���� (C), 2001-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtaPhyInterface.h
  �� �� ��   : ����
  ��    ��   : l00198894
  ��������   : 2013��02��26��
  ����޸�   :
  ��������   : MTA�������֮��Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��02��26��
    ��    ��   : l00198894
    �޸�����   : �����ļ�

 ******************************************************************************/

#ifndef __MTAPHYINTERFACE_H__
#define __MTAPHYINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafNvInterface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MTA_PHY_AFCLOCK_REPORT_DURATION     (500)

#define RCM_MTA_XO_COEF_NUM                 (4)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : MTA_PHY_GPS_RF_CLOCK_STATE_ENUM
 �ṹ˵��  : RFоƬGPSʱ��״̬ö��
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*****************************************************************************/
enum MTA_PHY_GPS_RF_CLOCK_STATE_ENUM
{
    MTA_PHY_GPS_RF_CLOCK_STATE_RUNNING          = 0,
    MTA_PHY_GPS_RF_CLOCK_STATE_STOP,
    MTA_PHY_GPS_RF_CLOCK_STATE_BUTT
};
typedef VOS_UINT16 MTA_PHY_GPS_RF_CLOCK_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_BODY_SAR_STATE_ENUM
 �ṹ˵��  : Body SAR ״̬ö��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : ����ö��
*****************************************************************************/
enum MTA_BODY_SAR_STATE_ENUM
{
    MTA_BODY_SAR_OFF                    = 0,                                    /* Body SAR���ܹر� */
    MTA_BODY_SAR_ON,                                                            /* Body SAR���ܿ��� */
    MTA_BODY_SAR_STATE_BUTT
};
typedef VOS_UINT16 MTA_BODY_SAR_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_PHY_RESULT_ENUM
 �ṹ˵��  : MTA������������ö��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : ����ö��
*****************************************************************************/
enum MTA_PHY_RESULT_ENUM
{
    MTA_PHY_RESULT_NO_ERROR             = 0,
    MTA_PHY_RESULT_ERROR,
    MTA_PHY_RESULT_PARA_ERROR,
    MTA_PHY_RESULT_BUTT
};
typedef VOS_UINT16 MTA_PHY_RESULT_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : MTA_PHY_EMERGENCY_CALL_STATUS_ENUM
 �ṹ˵��  : ��������״̬ö��
 1.��    ��   : 2013��04��09��
   ��    ��   : z00214637
   �޸�����   : ����
*****************************************************************************/
enum MTA_PHY_EMERGENCY_CALL_STATUS_ENUM
{
    MTA_PHY_EMERGENCY_CALL_END  = 0,                                            /* �������н��� */
    MTA_PHY_EMERGENCY_CALL_START,                                               /* �������з��� */
    MTA_PHY_EMERGENCY_CALL_STATUS_BUTT
};
typedef VOS_UINT16 MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHY_MTA_REFCLOCK_STATUS_ENUM
 ö��˵��  : GPS�ο�ʱ������״̬ö��

  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
enum PHY_MTA_REFCLOCK_STATUS_ENUM
{
    PHY_MTA_REFCLOCK_UNLOCKED           = 0,                                    /* GPS�ο�ʱ��Ƶ�ʷ�����״̬ */
    PHY_MTA_REFCLOCK_LOCKED,                                                    /* GPS�ο�ʱ��Ƶ������״̬ */
    PHY_MTA_REFCLOCK_STATUS_BUTT
};
typedef VOS_UINT16 PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHY_MTA_GPHY_XPASS_MODE_ENUM
 ö��˵��  : G XPASSģʽ

  1.��    ��   : 2014��12��18��
    ��    ��   : w00286360
    �޸�����   : seattle
*****************************************************************************/
enum PHY_MTA_GPHY_XPASS_MODE_ENUM
{
    PHY_MTA_GPHY_XPASS_MODE_DISABLE     = 0,                                    /* ��XPASSģʽ�����Ƹ��� */
    PHY_MTA_GPHY_XPASS_MODE_ENABLE         ,                                    /* XPASSģʽ�����Ƹ��� */
    PHY_MTA_GPHY_XPASS_MODE_BUTT
};
typedef VOS_UINT16 PHY_MTA_GPHY_XPASS_MODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : PHY_MTA_WPHY_HIGHWAY_MODE_ENUM
 ö��˵��  : W����ģʽ

  1.��    ��   : 2014��12��18��
    ��    ��   : w00286360
    �޸�����   : seattle
*****************************************************************************/
enum PHY_MTA_WPHY_HIGHWAY_MODE_ENUM
{
    PHY_MTA_WPHY_HIGHWAY_MODE_DISABLE     = 0,                                  /* W�Ǹ���ģʽ */
    PHY_MTA_WPHY_HIGHWAY_MODE_ENABLE         ,                                  /* W����ģʽ */
    PHY_MTA_WPHY_HIGHWAY_MODE_BUTT
};
typedef VOS_UINT16 PHY_MTA_WPHY_HIGHWAY_MODE_ENUM_UINT16;

#if 0
#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 ö����    : MTA_LPHY_COEX_BW_TYPE_ENUM
 ö��˵��  : LTE&WIFI�������ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum MTA_LPHY_COEX_BW_TYPE_ENUM
{
    MTA_LPHY_COEX_BAND_WIDTH_6RB        = 0,                                    /* ���1.4M */
    MTA_LPHY_COEX_BAND_WIDTH_15RB       = 1,                                    /* ���3M */
    MTA_LPHY_COEX_BAND_WIDTH_25RB       = 2,                                    /* ���5M */
    MTA_LPHY_COEX_BAND_WIDTH_50RB       = 3,                                    /* ���10M */
    MTA_LPHY_COEX_BAND_WIDTH_75RB       = 4,                                    /* ���15M */
    MTA_LPHY_COEX_BAND_WIDTH_100RB      = 5,                                    /* ���20M */
    MTA_LPHY_COEX_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 MTA_LPHY_COEX_BW_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTA_LPHY_COEX_CFG_ENUM
 ö��˵��  : LTE&WIFI���淽������ö��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
enum MTA_LPHY_COEX_CFG_ENUM
{
    MTA_LPHY_COEX_CFG_DISABLE           = 0,
    MTA_LPHY_COEX_CFG_ENABLE            = 1,
    MTA_LPHY_COEX_CFG_BUTT
};
typedef VOS_UINT16 MTA_LPHY_COEX_CFG_ENUM_UINT16;
#endif
#endif

/*****************************************************************************
 ö����    : PHY_MTA_AFC_CLK_STATUS_ENUM
 ö��˵��  : AFCʱ������״̬ö��

  1.��    ��   : 2015��9��7��
    ��    ��   : l00198894
    �޸�����   : ����ö��
*****************************************************************************/
enum PHY_MTA_AFC_CLK_STATUS_ENUM
{
    PHY_MTA_AFC_CLK_UNLOCKED           = 0,                                     /* AFCʱ��Ƶ�ʷ�����״̬ */
    PHY_MTA_AFC_CLK_LOCKED,                                                     /* AFCʱ��Ƶ������״̬ */

    PHY_MTA_AFC_CLK_STATUS_BUTT
};
typedef VOS_UINT16 PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
#define MTA_PHY_MSG_HEADER      VOS_MSG_HEADER \
                                VOS_UINT16  usMsgID; \
                                VOS_UINT16  usReserved0;

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
 ö����    : MTA_PHY_MSG_TYPE_ENUM
 �ṹ˵��  : ԭ���usMsgID
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : ����ö��
*****************************************************************************/
enum MTA_PHY_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                              /* ��ϢID */                    /* ��ע */
    /* �������APM�����Ϣ */
    ID_MTA_APM_BODY_SAR_SET_REQ                 = 0xD202,                       /* _H2ASN_MsgChoice MTA_APM_BODY_SAR_SET_REQ_STRU */
    ID_MTA_APM_EMERGENCY_CALL_STATUS_NOTIFY     = 0xD203,                       /* _H2ASN_MsgChoice MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU */
    ID_APM_MTA_BODY_SAR_SET_CNF                 = 0xD220,                       /* _H2ASN_MsgChoice APM_MTA_BODY_SAR_SET_CNF_STRU */
    ID_APM_MTA_REFCLOCK_STATUS_IND              = 0xD221,                       /* _H2ASN_MsgChoice APM_MTA_REFCLOCK_STATUS_IND_STRU */

    ID_MTA_APM_HANDLE_DETECT_SET_REQ            = 0xD222,                       /* _H2ASN_MsgChoice MTA_APM_HANDLE_DETECT_SET_REQ_STRU */
    ID_APM_MTA_HANDLE_DETECT_SET_CNF            = 0xD223,                       /* _H2ASN_MsgChoice APM_MTA_HANDLE_DETECT_SET_CNF_STRU */
    ID_MTA_APM_HANDLE_DETECT_QRY_REQ            = 0xD224,                       /* _H2ASN_MsgChoice MTA_APM_HANDLE_DETECT_QRY_REQ_STRU */
    ID_APM_MTA_HANDLE_DETECT_QRY_CNF            = 0xD225,                       /* _H2ASN_MsgChoice APM_MTA_HANDLE_DETECT_QRY_CNF_STRU */

    /* ��G, W�����APM�����Ϣ */
    ID_MTA_APM_GET_PHY_CHR_INFO_REQ             = 0xD226,                       /* _H2ASN_MsgChoice MTA_APM_GET_PHY_CHR_INFO_REQ_STRU */
    ID_APM_MTA_GET_PHY_CHR_INFO_CNF             = 0xD227,                       /* _H2ASN_MsgChoice APM_MTA_GET_PHY_CHR_INFO_CNF_STRU */

    /* ��T, L���������Ϣ */
    ID_MTA_TLPHY_GET_PHY_CHR_INFO_REQ           = 0xD228,                       /* _H2ASN_MsgChoice MTA_TLPHY_GET_PHY_CHR_INFO_REQ_STRU */
    ID_TLPHY_MTA_GET_PHY_CHR_INFO_CNF           = 0xD229,                       /* _H2ASN_MsgChoice TLPHY_MTA_GET_PHY_CHR_INFO_CNF_STRU */
    ID_AGENT_MTA_RFIC_SSI_RD_IND                = 0xD22A,                       /* _H2ASN_MsgChoice APM_MTA_RFICSSIRD_IND_STRU */

    /* ��G���������Ϣ */
    ID_MTA_GPHY_SET_GPS_RF_CLOCK_REQ            = 0x3401,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU */
    ID_MTA_GPHY_GET_TX_PWR_REQ                  = 0x3402,                       /* _H2ASN_MsgChoice MTA_GPHY_GET_TX_PWR_REQ_STRU */

    ID_GPHY_MTA_SET_GPS_RF_CLOCK_CNF            = 0x4301,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU */
    ID_GPHY_MTA_GET_TX_PWR_CNF                  = 0x4302,                       /* _H2ASN_MsgChoice GPHY_MTA_GET_TX_PWR_CNF_STRU */

    /* ��W���������Ϣ */
    ID_MTA_WPHY_SET_GPS_RF_CLOCK_REQ            = 0x5401,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU */

    /* ��UPHY�����Ϣ */
    ID_MTA_UPHY_START_UPHY_REQ                  = 0x6501,                       /* _H2ASN_MsgChoice MTA_UPHY_START_UPHY_REQ_STRU */
    ID_UPHY_MTA_START_UPHY_CNF                  = 0x5601,                       /* _H2ASN_MsgChoice UPHY_MTA_START_UPHY_CNF_STRU */


    /* ��G��W���������Ϣ */
    ID_MTA_GUPHY_SET_DPDTTEST_FLAG_NTF          = 0x5402,                       /* _H2ASN_MsgChoice MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU */
    ID_MTA_GUPHY_SET_DPDT_VALUE_NTF             = 0x5403,                       /* _H2ASN_MsgChoice MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU */
    ID_MTA_GUPHY_QRY_DPDT_VALUE_REQ             = 0x5404,                       /* _H2ASN_MsgChoice MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU */
    ID_MTA_WPHY_GET_TX_PWR_REQ                  = 0x5405,                       /* _H2ASN_MsgChoice MTA_WPHY_GET_TX_PWR_REQ_STRU */
    ID_WPHY_MTA_SET_GPS_RF_CLOCK_CNF            = 0x4501,                       /* _H2ASN_MsgChoice MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU */
    ID_GUPHY_MTA_QRY_DPDT_VALUE_CNF             = 0x4502,                       /* _H2ASN_MsgChoice GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU */
    ID_WPHY_MTA_GET_TX_PWR_CNF                  = 0x4503,                       /* _H2ASN_MsgChoice WPHY_MTA_GET_TX_PWR_CNF_STRU */

    /* G\W�������ϱ�ID��ID��0x6500��ʼ���� */
    ID_GPHY_MTA_XPASS_INFO_IND                  = 0x7501,                       /* _H2ASN_MsgChoice GPHY_MTA_XPASS_INFO_IND_STRU */
    ID_WPHY_MTA_XPASS_INFO_IND                  = 0x7502,                       /* _H2ASN_MsgChoice WPHY_MTA_XPASS_INFO_IND_STRU */


#if 0
#if(FEATURE_ON == FEATURE_LTE)
    ID_MTA_LPHY_LTE_WIFI_COEX_SET_REQ           = 0x7503,                       /* _H2ASN_MsgChoice MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU */
    ID_LPHY_MTA_LTE_WIFI_COEX_SET_CNF           = 0x7504,                       /* _H2ASN_MsgChoice LPHY_MTA_LTE_WIFI_COEX_SET_REQ_STRU */
#endif
#endif

    /* ��TLPHY�����Ϣ */
    ID_MTA_AGENT_AFCLOCK_STATUS_RPT_NTF         = 0x7503,                       /* _H2ASN_MsgChoice MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU */

    /* ��TLPHY�����Ϣ */
    ID_MTA_AGENT_RFIC_SSI_RD_NTF                = 0x7505,                       /* _H2ASN_MsgChoice MTA_AGENT_RFICSSIRD_REQ_STRU */
	
    /* CDMA����������Ϣ */
    ID_MTA_CTAS_SET_DPDTTEST_FLAG_NTF           = 0x8400,                       /* _H2ASN_MsgChoice MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU */
    ID_MTA_CTAS_SET_DPDT_VALUE_NTF              = 0x8401,                       /* _H2ASN_MsgChoice MTA_CTAS_SET_DPDT_VALUE_NTF_STRU */
    ID_MTA_CTAS_QRY_DPDT_VALUE_REQ              = 0x8402,                       /* _H2ASN_MsgChoice MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU */
    ID_CTAS_MTA_QRY_DPDT_VALUE_CNF              = 0x8500,                       /* _H2ASN_MsgChoice CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU */

    ID_MTA_RCM_AFC_CLK_INFO_QRY_REQ             = 0x7D01,                       /* _H2ASN_MsgChoice MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU */
    ID_RCM_MTA_AFC_CLK_INFO_QRY_CNF             = 0x7D02,                       /* _H2ASN_MsgChoice RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU */

    ID_MTA_PHY_MSG_TYPE_BUTT
};
typedef VOS_UINT16 MTA_PHY_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
ö����    : MTA_UPHY_INIT_STATUS_ENUM
�ṹ˵��  : UPHY��ʼ��״̬��ö��

  1.��    ��   : 2014��02��14��
    ��    ��   : h00246512
    �޸�����   : DSDS��Ŀ�����ӿ�
*****************************************************************************/
enum MTA_UPHY_INIT_STATUS_ENUM
{
    MTA_UPHY_INIT_STATUS_SUCCESS,
    MTA_UPHY_INIT_STATUS_FAIL,
    MTA_UPHY_INIT_STATUS_BUTT
};
typedef VOS_UINT16  MTA_UPHY_INIT_STATUS_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*******************************************************************************
 �ṹ��    : MTA_PHY_MSG_HEADER_STRU
 �ṹ˵��  : ��Ϣͷ
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
}MTA_PHY_MSG_HEADER_STRU;



/*******************************************************************************
 �ṹ��    : NAS_PHY_COM_INIT_REQ_STRU
 �ṹ˵��  : ��������㿪���ϵ��ʼ��
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/

    VOS_UINT32                                  ulSlice;            /* �����ʱ��� */
}NAS_PHY_COM_INIT_REQ_STRU;


/*******************************************************************************
 �ṹ��    : PHY_NAS_COM_INIT_CNF_STRU
 �ṹ˵��  : ������ϵ��ʼ���ɹ�
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulSlice;            /* �����ʱ��� */
}PHY_NAS_COM_INIT_CNF_STRU;


/*******************************************************************************
 �ṹ��    : MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU
 �ṹ˵��  : ��������㿪����ر�RFоƬ�ϵ�GPSʱ��
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/

    MTA_PHY_GPS_RF_CLOCK_STATE_ENUM_UINT16      enGpsClockState;    /* RFоƬGPSʱ��״̬ */
    VOS_UINT16                                  ausReserved1[1];    /* ����λ */
}MTA_PHY_SET_GPS_RF_CLOCK_REQ_STRU;

/*******************************************************************************
 �ṹ��    : MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU
 �ṹ˵��  : ����㿪����ر�RFоƬ�ϵ�GPSʱ�ӽ���ظ�
 1.��    ��   : 2012��06��25��
   ��    ��   : h44270
   �޸�����   : Added for AGPS
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/

    MTA_PHY_RESULT_ENUM_UINT16                  enResultType;       /* �����Ϣ���� */
    VOS_UINT16                                  ausReserved1[1];    /* ����λ */

}MTA_PHY_SET_GPS_RF_CLOCK_CNF_STRU;

/*******************************************************************************
 �ṹ��    : MTA_GPHY_GET_TX_PWR_REQ_STRU
 �ṹ˵��  : ��ѯG����㷢�书������
 1.��    ��   : 2015��07��2��
   ��    ��   : w00286360
   �޸�����   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
}MTA_GPHY_GET_TX_PWR_REQ_STRU;

/*******************************************************************************
 �ṹ��    : GPHY_MTA_GET_TX_PWR_CNF_STRU
 �ṹ˵��  : ��ѯG����㷢�书��CNF
 1.��    ��   : 2015��07��2��
   ��    ��   : w00286360
   �޸�����   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16                  enResult;           /* ������� */
    VOS_INT16                                   sTxPwr;             /* ���书�ʣ�0.1dBm���� */
}GPHY_MTA_GET_TX_PWR_CNF_STRU;

/*******************************************************************************
 �ṹ��    : MTA_WPHY_GET_TX_PWR_REQ_STRU
 �ṹ˵��  : ��ѯW����㷢�书������
 1.��    ��   : 2015��07��2��
   ��    ��   : w00286360
   �޸�����   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
}MTA_WPHY_GET_TX_PWR_REQ_STRU;

/*******************************************************************************
 �ṹ��    : WPHY_MTA_GET_TX_PWR_CNF_STRU
 �ṹ˵��  : ��ѯW����㷢�书��CNF
 1.��    ��   : 2015��07��2��
   ��    ��   : w00286360
   �޸�����   : Added
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16                  enResult;           /* ������� */
    VOS_INT16                                   sTxPwr;             /* ���书�ʣ�0.1dBm���� */
}WPHY_MTA_GET_TX_PWR_CNF_STRU;


/*******************************************************************************
 �ṹ��    : MTA_APM_BODY_SAR_SET_REQ_STRU
 �ṹ˵��  : ����Body SAR�����ر�״̬���������޲����ṹ��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_BODY_SAR_STATE_ENUM_UINT16      enState;                    /* Body SAR״̬ */
    VOS_UINT16                          ausReserved1[1];            /* ����λ */
    MTA_BODY_SAR_PARA_STRU              stBodySARPara;              /* Body SAR�������޲��� */
}MTA_APM_BODY_SAR_SET_REQ_STRU;

/*******************************************************************************
 �ṹ��    : APM_MTA_BODY_SAR_SET_CNF_STRU
 �ṹ˵��  : �ظ�Body SAR���ò�������ṹ��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                              /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16          enResult;                   /* ������� */
    VOS_UINT16                          ausReserved1[1];            /* ����λ */
}APM_MTA_BODY_SAR_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_PHY_EMERGENCY_CALL_STATUS_NTF
 �ṹ˵��  : ֪ͨPHY��������״̬�ṹ
 1.��    ��  : 2013��03��28��
   ��    ��  : z00214637
   �޸�����  : �½��ṹ��
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                              /*_H2ASN_Skip*/
    MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16           enEmergencyCallStatus;      /* ������״̬ */
    VOS_UINT16                                          ausReserved1[1];            /* ����λ */
}MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU;

/*******************************************************************************
 �ṹ��    : APM_MTA_REFCLOCK_STATUS_IND_STRU
 �ṹ˵��  : �����APM�����ϱ�GPS�ο�ʱ������״̬�ṹ��
 1.��    ��   : 2013��02��27��
   ��    ��   : l00198894
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16 enStatus;                               /* ʱ��Ƶ������״̬ */
    VOS_UINT16                          ausReserved1[1];                        /* ����λ */
} APM_MTA_REFCLOCK_STATUS_IND_STRU;

/*******************************************************************************
 �ṹ��    : APM_MTA_RFICSSIRD_IND_STRU
 �ṹ˵��  : �����APM�ϱ�rfic�Ĵ���ֵ�ṹ��
 1.��    ��   : 2015��10��30��
   ��    ��   : x00316382
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulRegValue;                             /* �Ĵ�����ֵ */
} APM_MTA_RFICSSIRD_IND_STRU;

/*******************************************************************************
 �ṹ��    : MTA_APM_HANDLE_DETECT_SET_REQ_STRU
 �ṹ˵��  : ���������ֲ����Ľṹ��
 1.��    ��   : 2013��08��06��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          usHandle;                               /* ���������� */
    VOS_UINT16                          ausReserved1[1];                        /* ����λ */
}MTA_APM_HANDLE_DETECT_SET_REQ_STRU;

/*******************************************************************************
 �ṹ��    : APM_MTA_HANDLE_DETECT_SET_CNF_STRU
 �ṹ˵��  : �ظ����������ò�������ṹ��
 1.��    ��   : 2013��08��06��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16          enResult;                               /* ������� */
    VOS_UINT16                          ausReserved1[1];                        /* ����λ */
}APM_MTA_HANDLE_DETECT_SET_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_APM_HANDLE_DETECT_QRY_REQ_STRU
 �ṹ˵��  : �����ֲ�����ѯ��Ϣ�ṹ
 1.��    ��   : 2013��08��06��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved1[2];                        /* ����λ */
} MTA_APM_HANDLE_DETECT_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : APM_MTA_HANDLE_DETECT_QRY_CNF_STRU
 �ṹ˵��  : �����ֲ�����ѯ�ظ���Ϣ�ṹ
 1.��    ��   : 2013��08��06��
   ��    ��   : f00179208
   �޸�����   : �����ṹ��
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          usHandle;                               /* ���������� */
    MTA_PHY_RESULT_ENUM_UINT16          enResult;                               /* ������� */
} APM_MTA_HANDLE_DETECT_QRY_CNF_STRU;


/*******************************************************************************
�ṹ��    : MTA_UPHY_START_UPHY_REQ_STRU
�ṹ˵��  : ID_MTA_UPHY_START_UPHY_REQ_����Ϣ�ṹ
1.��    ��   : 2014��1��5��
  ��    ��   : z00161729
  �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved1[2];                         /*����λ*/
} MTA_UPHY_START_UPHY_REQ_STRU;

/*******************************************************************************
�ṹ��    : MTA_UPHY_INIT_STATUS_IND_STRU
�ṹ˵��  : ID_MTA_UPHY_INIT_STATUS_IND����Ϣ�ṹ
1.��    ��   : 2014��1��5��
  ��    ��   : z00161729
  �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_UPHY_INIT_STATUS_ENUM_UINT16     enInitStatus;                          /* ������ʼ��״̬ */
    VOS_UINT16                           ausReserved1[1];                       /*����λ*/
} UPHY_MTA_START_UPHY_CNF_STRU;


/*****************************************************************************
�ṹ��    : MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU
�ṹ˵��  : ���������㷨�򿪡��ر���Ϣ�ṹ

  1.��    ��  : 2014��04��01��
    ��    ��  : g00261581
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          usDpdtTest;
    VOS_UINT16                          ausReserved1[1];
} MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU;

/*****************************************************************************
�ṹ��    : MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU
�ṹ˵��  : �������ߵ�ǰDPDT Valueֵ����Ϣ�ṹ

  1.��    ��  : 2014��04��01��
    ��    ��  : g00261581
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU;

/*****************************************************************************
�ṹ��    : MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU
�ṹ˵��  : ��ѯ��ǰ����״̬��Ϣ�ṹ

  1.��    ��  : 2014��04��01��
    ��    ��  : g00261581
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved1[2];
} MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
�ṹ��    : GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU
�ṹ˵��  : ��ѯ��Ӧ�������ʾ��ǰ����DPDTֵ

  1.��    ��  : 2014��04��01��
    ��    ��  : g00261581
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
�ṹ��    : GPHY_MTA_XPASS_INFO_IND_STRU
�ṹ˵��  : GPHY�ϱ�XPASS��ص���Ϣ

  1.��    ��  : 2014��12��19��
    ��    ��  : w00286360
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    PHY_MTA_GPHY_XPASS_MODE_ENUM_UINT16 enXpassMode;                            /* G xpassģʽ */
    VOS_UINT16                          usReserved;
} GPHY_MTA_XPASS_INFO_IND_STRU;

/*****************************************************************************
�ṹ��    : WPHY_MTA_XPASS_INFO_IND_STRU
�ṹ˵��  : WPHY�ϱ�XPASS��ص���Ϣ

  1.��    ��  : 2014��12��19��
    ��    ��  : w00286360
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    PHY_MTA_WPHY_HIGHWAY_MODE_ENUM_UINT16   enHighwayMode;                      /* W����ģʽ */
    VOS_UINT16                              usReserved;
} WPHY_MTA_XPASS_INFO_IND_STRU;

#if 0
#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
�ṹ��    : MTA_LPHY_COEX_PARA_STRU
�ṹ˵��  : LTE&WIFI��������ṹ��

  1.��    ��  : 2015��5��22��
    ��    ��  : w00316404
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_LPHY_COEX_BW_TYPE_ENUM_UINT16       enCoexBWType;
    MTA_LPHY_COEX_CFG_ENUM_UINT16           enCfg;
    VOS_UINT16                              usTxBegin;
    VOS_UINT16                              usTxEnd;
    VOS_INT16                               sTxPower;
    VOS_UINT16                              usRxBegin;
    VOS_UINT16                              usRxEnd;
    VOS_UINT16                              usReserved;                         /* ����λ */
} MTA_LPHY_COEX_PARA_STRU;

/*****************************************************************************
�ṹ��    : MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU
�ṹ˵��  : MTA֪ͨLPHY����LTE&WIFI������������ṹ��

  1.��    ��  : 2015��5��22��
    ��    ��  : w00316404
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usCoexParaNum;
    VOS_UINT16                              usCoexParaSize;
    VOS_UINT8                               aucCoexPara[4];
} MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU;

/*****************************************************************************
�ṹ��    : LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU
�ṹ˵��  : LPHY�ظ�MTA LTE&WIFI�����������ý���ṹ��

  1.��    ��  : 2015��5��22��
    ��    ��  : w00316404
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16              enResult;                           /* ���ý�� */
    VOS_UINT16                              usReserved;                         /* ����λ */
} LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU;
#endif
#endif

/*****************************************************************************
�ṹ��    : TLPHY_MTA_AFCLOCK_AFCSTATUS_IND_STRU
�ṹ˵��  : TLPHY_PID_RTTAGENT�ϱ���UEPS_PID_MTA������״̬��Ϣ�ṹ��

  1.��    ��  : 2015��06��17��
    ��    ��  : zwx247453
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usStatus;                           /* AFC����״̬: 0, ʧ��; 1, ���� */
    VOS_UINT16                              ausReserved1[1];
} TLPHY_MTA_AFCLOCK_AFCSTATUS_IND_STRU;

/*****************************************************************************
�ṹ��    : MTA_AGENT_AFCLOCK_AFCSTATUS_NIF_STRU
�ṹ˵��  : UEPS_PID_MTA���͵�TLPHY_PID_RTTAGENT��AFC����״̬NTF��Ϣ�ṹ��

  1.��    ��  : 2015��06��17��
    ��    ��  : zwx247453
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usReportCtrolflag;                  /* 0:ֹͣ�ϱ���1:�����ϱ� */
    VOS_UINT16                              usReportCount;                      /* �ϱ�����������0xffff�������ϱ� */
    VOS_UINT16                              usReportDuration;                   /* �ϱ��������msΪ��λ������Ϊ10ms���������ϱ���������1ʱ��Ч */
    VOS_UINT16                              ausReserved1[1];
} MTA_AGENT_AFCLOCK_AFCSTATUS_NTF_STRU;

/*****************************************************************************
�ṹ��    : MTA_AGENT_RFICSSIRD_REQ_STRU
�ṹ˵��  : MTA���͵�TLPHY_PID_RTTAGENT��RFICRD��Ϣ�ṹ��

  1.��    ��  : 2015��10��29��
    ��    ��  : x0016382
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    VOS_UINT16                              usChannelNo;                        /* rficͨ�� */
    VOS_UINT16                              usRficReg;                          /* �Ĵ�����ַ */
} MTA_AGENT_RFICSSIRD_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU
�ṹ˵��  : ���������㷨�򿪡��ر���Ϣ�ṹ

 1.��    ��  : 2015��11��18��
   ��    ��  : h00313353
   ��������  : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          usDpdtTest;
    VOS_UINT16                          usReserved;
} MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU;

/*****************************************************************************
�ṹ��    : MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU
�ṹ˵��  : ��ѯ��ǰ����״̬��Ϣ�ṹ

  1.��    ��  : 2015��11��18��
    ��    ��  : h00313353
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT16                          ausReserved[2];
} MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU;

/*****************************************************************************
�ṹ��    : MTA_CTAS_SET_DPDT_VALUE_NTF_STRU
�ṹ˵��  : �������ߵ�ǰDPDT Valueֵ

  1.��    ��  : 2015��11��18��
    ��    ��  : h00313353
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} MTA_CTAS_SET_DPDT_VALUE_NTF_STRU;

/*****************************************************************************
�ṹ��    : CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU
�ṹ˵��  : ��ѯ��Ӧ�������ʾ��ǰ����DPDTֵ

  1.��    ��  : 2015��11��18��
    ��    ��  : h00313353
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDpdtValue;
} CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_PHY_CHR_INFO_QRY_REQ_STRU
 �ṹ˵��  : MTA����PHY��TX Power��ѯ����

  1.��    ��   : 2015��10��20��
    ��    ��   : ���巼 z00328328
    �޸�����   : ����, for ���з��书���ռ�
  2.��    ��   : 2015��12��01��
    ��    ��   : ������ g00322017
    �޸�����   : �޸�, for �������Ϣ�ռ�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER
    VOS_UINT16                              ausReserved1[2];                    /* ����λ */
} MTA_PHY_CHR_INFO_QRY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_MTA_PHY_INFO_QRY_CNF_STRU
 �ṹ˵��  : PHY����MTA��TX Power��ѯ���

  1.��    ��   : 2015��10��20��
    ��    ��   : ���巼 z00328328
    �޸�����   : ����, for ���з��书���ռ�
  2.��    ��   : 2015��12��01��
    ��    ��   : ������ g00322017
    �޸�����   : �޸�, for �������Ϣ�ռ�

*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER
    VOS_UINT16                          usCellid;       /* С��id */
    VOS_UINT16                          usDlFreqInfo;   /* ����Ƶ�� */
    VOS_UINT16                          usUlFreqInfo;   /* ����Ƶ�� */
    VOS_UINT16                          usBandInfo;     /* BAND */
    VOS_INT16                           sRxPower;       /* Rxlev(GSM), RSCP(UMTS,TDS),Rsrp(LTE) */
    VOS_INT16                           sChanelQuality; /* Rxqual(GSM), EcN0(UMTS), Scale(TDS),RsrQ(LTE) */
    VOS_INT32                           lTxPwr;         /* ���з��书��, 0.1dBm���� */
    VOS_UINT32                          ulSavedSlice;   /* ��ǰ�ϱ�ʱ�� */
}PHY_MTA_PHY_CHR_INFO_QRY_CNF_STRU;


/*****************************************************************************
�ṹ��    : MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU
�ṹ˵��  : MTA��RCM��ѯAFCʱ��Ƶƫ��Ϣ��XO�²�ϵ������ṹ��

  1.��    ��  : 2015��9��7��
    ��    ��  : l00198894
    ��������  : �½�
*****************************************************************************/
typedef MTA_UPHY_START_UPHY_REQ_STRU    MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU;

/*****************************************************************************
�ṹ��    : RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU
�ṹ˵��  : RCM�ظ�MTA��ѯAFCʱ��Ƶƫ��Ϣ��XO�²�ϵ���ṹ��

  1.��    ��  : 2015��9��7��
    ��    ��  : l00198894
    ��������  : �½�
*****************************************************************************/
typedef struct
{
    MTA_PHY_MSG_HEADER                                                          /*_H2ASN_Skip*/
    MTA_PHY_RESULT_ENUM_UINT16          enResult;
    
    PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus;
    VOS_INT32                           lDeviation;                             /* Ƶƫ��Ϣ */

    /* �¶ȷ�Χ */
    VOS_INT16                           sCoeffStartTemp;
    VOS_INT16                           sCoeffEndTemp;

    /* ����ʽϵ�� */
    VOS_UINT32                          aulCoeffMantissa[RCM_MTA_XO_COEF_NUM];  /* a0,a1,a2,a3��β�� */
    VOS_UINT16                          ausCoeffExponent[RCM_MTA_XO_COEF_NUM];  /* a0,a1,a2,a3��ָ�� */

} RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU;



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
    MTA_PHY_MSG_TYPE_ENUM_UINT16        enMsgId;                    /*_H2ASN_MsgChoice_Export MTA_PHY_MSG_TYPE_ENUM_UINT16*/
    VOS_UINT16                          usRsv;                      /* ����λ */
    VOS_UINT16                          ausMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTA_PHY_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MTA_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MTA_PHY_MSG_DATA                    stMsgData;
}MtaPhyInterface_MSG;

/*****************************************************************************
  10 ��������
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
#endif

#endif /* end of MtaPhyInterface.h */

