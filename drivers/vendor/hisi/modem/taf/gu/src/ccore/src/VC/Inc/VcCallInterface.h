/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : VcCallInterface.h
  �� �� ��   : ����
  ��    ��   : h44270
  ��������   : 2009��7��05��
  ����޸�   : 2009��7��05��
  ��������   : VCģ���HPA֮��Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��7��05��
    ��    ��   : h44270
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  VC_CALL_INTERFACE_H
#define  VC_CALL_INTERFACE_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
#define CALL_VC_MSG_ID_BASE             0x0000
#define VC_CALL_MSG_ID_BASE             0x1000

/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
enum CALL_VC_MSG_ID_ENUM
{
    /*CALL->VC*/
    CALL_VC_CHANNEL_OPEN                = CALL_VC_MSG_ID_BASE + 0,              /* _H2ASN_MsgChoice CALL_VC_CHANNEL_INFO_MSG_STRU */
    CALL_VC_CHANNEL_CLOSE               = CALL_VC_MSG_ID_BASE + 1,              /* _H2ASN_MsgChoice CALL_VC_CHANNEL_INFO_MSG_STRU */
    CALL_VC_CHANNEL_PARA_CHANGE         = CALL_VC_MSG_ID_BASE + 2,              /* _H2ASN_MsgChoice CALL_VC_CHANNEL_INFO_MSG_STRU */
    /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
    CALL_VC_CHANNEL_CONNECT,                                /* _H2ASN_MsgChoice CALL_VC_CHANNEL_INFO_MSG_STRU *//* ��·�Ѿ���ͨ�����Դ������� */
    /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

    CALL_VC_SO_CTRL_ORDER_IND,                              /* _H2ASN_MsgChoice CALL_VC_SO_CTRL_ORDER_IND_STRU */       /* 1X SO״̬�ϱ� */
    CALL_VC_SO_CTRL_MSG_IND,                                /* _H2ASN_MsgChoice CALL_VC_SO_CTRL_MSG_IND_STRU */         /* 1X SO״̬�ϱ� */

    /*VC->CALL*/
    VC_CALL_END_CALL                    = VC_CALL_MSG_ID_BASE + 0,              /* _H2ASN_MsgChoice VC_CALL_MSG_STRU */
    /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
    VC_CALL_ECALL_TRANS_STATUS_NTF,                         /* _H2ASN_MsgChoice VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *//* eCall״̬�ϱ� */
    /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

    CALL_VC_MSG_BUTT
};
typedef VOS_UINT16 CALL_VC_MSG_ID_ENUM_U16;

/*****************************************************************************
 ö����    : CALL_VC_CODEC_TYPE_ENUM_U8
 ö��˵��  : CALL��VCģ�� CODEC���ͽӿڵĶ��壬��Ҫ��RRMM�ӿڶ���һ��
 1.��    ��   : 2012��2��9��
   ��    ��   : zhoujun 40661
   �޸�����   : modify
 2.��    ��   : 2013��07��20��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/

enum CALL_VC_CODEC_TYPE_ENUM
{
    CALL_VC_CODEC_TYPE_AMR,                                                     /* amr */
    CALL_VC_CODEC_TYPE_EFR,                                                     /* enhanced full rate */
    CALL_VC_CODEC_TYPE_FR,                                                      /* full rate */
    CALL_VC_CODEC_TYPE_HR,                                                      /* half rate */
    CALL_VC_CODEC_TYPE_AMR2,                                                    /* amr2 */
    CALL_VC_CODEC_TYPE_AMRWB,                                                    /* amr2 */
    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
    CALL_VC_CODEC_TYPE_G711,                                                    /* G711 */
    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */
    CALL_VC_CODEC_TYPE_EVRC,
    CALL_VC_CODEC_TYPE_EVRCB,
    CALL_VC_CODEC_TYPE_BUTT                                                     /* invalid value */
};
typedef VOS_UINT8  CALL_VC_CODEC_TYPE_ENUM_U8;

enum CALL_VC_RADIO_MODE_ENUM
{
    CALL_VC_MODE_GSM,
    CALL_VC_MODE_WCDMA,
    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    CALL_VC_MODE_IMS_EUTRAN,
    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */
    CALL_VC_MODE_CDMA,
    CALL_VC_MODE_BUTT
};
typedef VOS_UINT8  CALL_VC_RADIO_MODE_ENUM_U8;

enum CALL_VC_CHANNEL_RATE_ENUM
{
    CALL_VC_CHANNEL_RATE_475,                                                   /* rate 4.75kbps/s */
    CALL_VC_CHANNEL_RATE_515,                                                   /* rate 5.15kbps/s */
    CALL_VC_CHANNEL_RATE_59,                                                    /* rate 5.9kbps/s */
    CALL_VC_CHANNEL_RATE_67,                                                    /* rate 6.7kbps/s */
    CALL_VC_CHANNEL_RATE_74,                                                    /* rate 7.4kbps/s */
    CALL_VC_CHANNEL_RATE_795,                                                   /* rate 7.95kbps/s */
    CALL_VC_CHANNEL_RATE_102,                                                   /* rate 10.2kbps/s */
    CALL_VC_CHANNEL_RATE_122,                                                   /* rate 12.2kbps/s */
    CALL_VC_CHANNEL_RATE_BUFF                                                   /* invalid value */
};
typedef VOS_UINT8  CALL_VC_CHANNEL_RATE_ENUM_U8;

/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
/*****************************************************************************
 ö����    : VC_CALL_ECALL_TRANS_STATUS _ENUM
 ö��˵��  : ECALL��ǰ�Ĵ���״̬
1.��    ��   : 2014��3��27��
  ��    ��   : h00246512
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
enum VC_CALL_ECALL_TRANS_STATUS_ENUM
{
    VC_CALL_ECALL_MSD_TRANSMITTING_START,                                       /* ��ǰMSD�����Ѿ���ʼ���� */
    VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS,                                     /* ��ǰMSD�����Ѿ����ͳɹ� */
    VC_CALL_ECALL_MSD_TRANSMITTING_FAIL,                                        /* ��ǰMSD�����Ѿ�����ʧ�� */
    VC_CALL_ECALL_PSAP_MSD_REQUIRETRANSMITTING,                                 /* PSAPҪ�����MSD���� */
    VC_CALL_ECALL_TRANS_STATUS_BUTT
};
typedef VOS_UINT8  VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM
 ö��˵��  : ECALL�Ĵ���ʧ��ԭ��
1.��    ��   : 2014��3��27��
  ��    ��   : h00246512
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
enum VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM
{
    VC_CALL_ECALL_CAUSE_WAIT_PSAP_TIME_OUT,                                     /* �ȴ�PSAP�Ĵ���ָʾ��ʱ */
    VC_CALL_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT,                              /* MSD���ݴ��䳬ʱ */
    VC_CALL_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT,                                   /* �ȴ�Ӧ�ò��ȷ�ϳ�ʱ */
    VC_CALL_ECALL_CAUSE_UNSPECIFIC_ERROR,                                       /* �����쳣���� */
    VC_CALL_ECALL_CAUSE_BUTT
};
typedef VOS_UINT8  VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : CALL_VC_CALL_TYPE_ENUM_UINT16
 ö��˵��  : ECALL�ĺ�������
1.��    ��   : 2014��4��20��
  ��    ��   : y00245242
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
enum CALL_VC_CALL_TYPE_ENUM
{
    CALL_VC_CALL_TYPE_NORMAL_CALL,
    CALL_VC_CALL_TYPE_ECALL,
    CALL_VC_CALL_TYPE_BUTT
};
typedef VOS_UINT16 CALL_VC_CALL_TYPE_ENUM_UINT16;
/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
/*****************************************************************************
 ö����    : APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32
 ö��˵��  : CODEC����
 1.��    ��   : 2013��7��20��
   ��    ��   : s00217060
   �޸�����   : ����
*****************************************************************************/
enum APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM
{
    APP_VC_OPEN_CHANNEL_CAUSE_SUCC                = 0,                          /* �ɹ� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED,                                     /* HIFI�Ѿ����� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_PORT_CFG_FAIL,                               /* �˿�����ʧ�� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_DEVICE_FAIL,                             /* ����Deviceʧ�� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL,                              /* startʧ�� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL,                             /* ��������ʧ�� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL,                            /* ���ʲ���ʧ�� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED,                            /* start������ʱ����ʱ */

    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_BUTT
};
typedef VOS_UINT32  APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32;
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */


typedef struct
{
    CALL_VC_RADIO_MODE_ENUM_U8          enMode;                                 /*GSM|WCDMA*/
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
    /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
    CALL_VC_CALL_TYPE_ENUM_UINT16       enCallType;                             /* eCall type */
    /* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */
 } CALL_VC_CHANNEL_PARAM_STRU;

typedef struct
{
    VOS_BOOL                            bChannelEnable;
    CALL_VC_CHANNEL_PARAM_STRU          stChannelParam;                         /* channel rate */
} CALL_VC_CHANNEL_INFO_STRU;


/*****************************************************************************
 �ṹ��    : CALL_VC_CHANNEL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ŵ���Ϣ�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CALL_VC_MSG_ID_ENUM_U16             enMsgName;                              /* _H2ASN_Skip *//* ԭ������ */
    VOS_UINT16                          usReserve;                              /* ���� */
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;
}CALL_VC_CHANNEL_INFO_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CALL_VC_MSG_ID_ENUM_U16                     enMsgName;                              /* _H2ASN_Skip *//* ԭ������ */
    VOS_UINT8                                   aucReserve[2];                              /* ���� */
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32  enCause;
}VC_CALL_MSG_STRU;

/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
/*****************************************************************************
 �ṹ��    : VC_CALL_ECALL_CONNECTED_NTF_STRU
 �ṹ˵��  : CALLģ��֪ͨVC����ǰ��ECALL��ͨ
 1.��    ��   : 2014��03��27��
   ��    ��   : h44270
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CALL_VC_MSG_ID_ENUM_U16             enMsgName;                              /* ԭ������*/
    VOS_UINT8                           aucReserve1[2];                         /* �����������ֽڶ��� */
} VC_CALL_ECALL_CONNECTED_NTF_STRU;

/*****************************************************************************
 �ṹ��    : CALL_VC_ECALL_SESSION_END_NTF_STRU
 �ṹ˵��  : MEDģ��֪ͨVC����ǰ��ECALL�ĻỰ�Ѿ�����
 1.��    ��   : 2014��03��27��
   ��    ��   : h44270
   �޸�����   : ������Ϊ֧��eCall����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CALL_VC_MSG_ID_ENUM_U16             enMsgName;                              /* ԭ������*/
    VOS_UINT8                           aucReserve[2];                          /* �����������ֽڶ��� */
} CALL_VC_ECALL_SESSION_END_NTF_STRU;

/*****************************************************************************
 �ṹ��    : VC_CALL_ECALL_TRANS_STATUS_NTF_STRU
 �ṹ˵��  : MEDģ��֪ͨVC����ǰ�Ĵ���״̬
 1.��    ��   : 2014��3��27��
   ��    ��   : h00246512
   �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CALL_VC_MSG_ID_ENUM_U16                     enMsgName;                      /* _H2ASN_Skip *//* ԭ������*/
    VOS_UINT8                                   aucReserve1[2];                 /* �����������ֽڶ��� */
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus;             /* eCall MSD����״̬ */
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause;          /* eCall MSD����ʧ��ԭ�� */
    VOS_UINT8                                   aucReserve2[2];                 /* ���� */
} VC_CALL_ECALL_TRANS_STATUS_NTF_STRU;

/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

/*****************************************************************************
 �ṹ��    : CALL_VC_SO_CTRL_ORDER_IND_STRU
 �ṹ˵��  : ֪ͨVC SO_CTRL_ORDER_IND
 1.��    ��   : 2014��9��17��
   ��    ��   : y00213812
   �޸�����   : CDMA 1X��Ŀ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CALL_VC_MSG_ID_ENUM_U16             enMsgName;                              /* _H2ASN_Skip *//* ԭ������*/
    VOS_UINT8                           aucReserve1[2];                         /* �����������ֽڶ��� */
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
    VOS_UINT8                           ucORDQ;
    VOS_UINT8                           aucReserve2[2];
} CALL_VC_SO_CTRL_ORDER_IND_STRU;

/*****************************************************************************
 �ṹ��    : CALL_VC_SO_CTRL_MSG_IND_STRU
 �ṹ˵��  : ֪ͨVC SO_CTRL_MSG_IND
 1.��    ��   : 2014��9��17��
   ��    ��   : y00213812
   �޸�����   : CDMA 1X��Ŀ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CALL_VC_MSG_ID_ENUM_U16             enMsgName;                              /* _H2ASN_Skip *//* ԭ������*/
    VOS_UINT8                           aucReserve1[2];                         /* �����������ֽڶ��� */
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
    VOS_UINT8                           ucRateReduc;
    VOS_UINT8                           ucMobileToMobile;
    VOS_UINT8                           ucInitCodec;
} CALL_VC_SO_CTRL_MSG_IND_STRU;


/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    CALL_VC_MSG_ID_ENUM_U16            enMsgId;                                /* _H2ASN_MsgChoice_Export CALL_VC_MSG_ID_ENUM_UINT16 */
    VOS_UINT8                          aucMsg[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CALL_VC_MSG_ID_ENUM_UINT16
    ****************************************************************************/
} VC_CALL_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    VC_CALL_MSG_DATA                    stMsgData;
} VcCallInterface_MSG;



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

#endif /* VC_CALL_INTERFACE_H */

