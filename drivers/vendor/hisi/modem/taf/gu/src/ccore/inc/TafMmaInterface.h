/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaInterface.h
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��9��9��
  ����޸�   :
  ��������   : Taf pid��Mma pid֮��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��9��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_MMA_INTERFACE_H__
#define __TAF_MMA_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "NasStkInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_MMA_PID_MSG_TYPE_ENUM
 �ṹ˵��  : TAF PID��MMA PID֮�����Ϣ�ӿ�ö��
*****************************************************************************/
enum TAF_MMA_PID_MSG_TYPE_ENUM
{
    MMCM_OM_MAINTAIN_INFO_IND                               = 0x00000000,       /* _H2ASN_MsgChoice MMCM_OM_MAINTAIN_INFO_IND_STRU */

    MN_USIM_STATUS_IND                                      = 0x00000001,       /* _H2ASN_MsgChoice MNPH_USIM_STATUS_IND_STRU */
    MMA_TAF_POWER_OFF_IND                                   = 0x00000002,       /* _H2ASN_MsgChoice TAF_MMA_POWER_OFF_IND_STRU */
    ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY                     = 0x00000003,       /* _H2ASN_MsgChoice MMA_MSG_CS_SERVICE_IND */
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, begin */
    ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY                 = 0x00000004,       /* _H2ASN_MsgChoice MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU */
    ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY             = 0x00000005,       /* _H2ASN_MsgChoice MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU */
    ID_MMA_TAF_RAT_CHANGE_NOTIFY                            = 0x00000006,       /* _H2ASN_MsgChoice MMA_TAF_RAT_CHANGE_NOTIFY_STRU */
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, end */

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, begin */
    ID_MMA_TAF_IMS_VOICE_CAP_IND                            = 0x00000007,       /* _H2ASN_MsgChoice MMA_TAF_IMS_VOICE_CAP_IND_STRU */
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, end */

    /* �ƶ���tafappmma.h �� */


    ID_MMA_TAF_1X_SERVICE_STATUS_IND,                                           /* _H2ASN_MsgChoice MMA_TAF_1X_SERVICE_STATUS_IND_STRU */

    ID_MMA_TAF_POWER_ON_IND,                                                    /* _H2ASN_MsgChoice TAF_MMA_POWER_ON_IND_STRU */
    ID_MMA_APS_EPDSZID_INFO_IND,                                                /* _H2ASN_MsgChoice MMA_APS_EPDSZID_INFO_IND_STRU */



    ID_MMA_APS_CL_SERVICE_STATUS_IND,                                           /* _H2ASN_MsgChoice MMA_APS_CL_SERVICE_STATUS_IND_STRU */


    ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND,                                      /* _H2ASN_MsgChoice MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU */

    ID_MMA_TAF_SYS_CFG_INFO_IND,                                                /* _H2ASN_MsgChoice MMA_TAF_SYS_CFG_INFO_IND_STRU */

    ID_TAF_MMA_PID_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MMA_PID_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : MNPH_USIM_STATUS_ENUM
 �ṹ˵��  : MNPH_USIM_STATUS_ENUM��Ϣ�е� enUsimStatus
*****************************************************************************/
enum MNPH_USIM_STATUS_ENUM
{
    MNPH_USIM_STATUS_AVILABLE         = 0, /* ����Ч */
    MNPH_USIM_STATUS_NOT_AVAILABLE    = 1, /* ����Ч */
    MNPH_USIM_STATUS_BUTT
};
typedef VOS_UINT32 MNPH_USIM_STATUS_ENUM_U32;


/* ת�Ƶ�tafappmma.h �� */

/*****************************************************************************
 ö����    : MMA_APS_RAT_TYPE_ENUM_UINT32
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2014��10��19��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
enum MMA_TAF_RAT_TYPE_ENUM
{
    MMA_TAF_RAT_TYPE_NULL,          /* ��ǰδ���κ�������פ�� */
    MMA_TAF_RAT_TYPE_GSM,           /* GSM���뼼�� */
    MMA_TAF_RAT_TYPE_WCDMA,         /* WCDMA���뼼�� */
    MMA_TAF_RAT_TYPE_LTE,           /* LTE���뼼�� */
    MMA_TAF_RAT_TYPE_1X,            /* CDMA-1X���뼼�� */
    MMA_TAF_RAT_TYPE_HRPD,          /* CDMA-HRPD���뼼�� */
    MMA_TAF_RAT_TYPE_EHRPD,         /* CDMA-EHRPD���뼼�� */
    MMA_TAF_RAT_TYPE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 MMA_TAF_RAT_TYPE_ENUM_UINT32;


enum MMA_APS_SYS_ACQUIRE_ENUM
{
    MMA_APS_SYS_ACQUIRE_NULL,          /* ��ǰδ���κ�������פ�� */
    MMA_APS_SYS_ACQUIRE_LTE,           /* LTE���뼼�� */
    MMA_APS_SYS_ACQUIRE_1X,            /* CDMA-1X���뼼�� */
    MMA_APS_SYS_ACQUIRE_EVDO,          /* CDMA-EVDO���뼼�� */
    MMA_APS_SYS_ACQUIRE_1X_EVDO,       /* CDMA-1X&EVDO���뼼�� */
    MMA_APS_SYS_ACQUIRE_BUTT           /* ��Ч�Ľ��뼼�� */
};
typedef VOS_UINT32 MMA_APS_SYS_ACQUIRE_ENUM_UINT32;


/*****************************************************************************
 ö����    : MMA_TAF_CL_STATUS_ENUM_UINT32
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2015��06��09��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
enum MMA_TAF_CL_STATUS_ENUM
{
    MMA_TAF_CL_STATUS_DO_NO_SERVICE,                  /* DO���з����Ϊ�޷��� */
    MMA_TAF_CL_STATUS_LTE_NO_SERVICE,                 /* LTE���з����Ϊ�޷��� */
    MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE,              /* ��ǰDO��LTE����������δ���κ�������פ�� */
    MMA_TAF_CL_STATUS_LTE_NORMAL_SERVICE,             /* LTE�������� */
    MMA_TAF_CL_STATUS_HRPD_NORMAL_SERVICE,            /* HRPD�������� */
    MMA_TAF_CL_STATUS_EHRPD_NORMAL_SERVICE,           /* EHRPD�������� */
    MMA_TAF_CL_STATUS_BUTT                            /* ��Ч��ֵ */
};
typedef VOS_UINT32 MMA_TAF_CL_STATUS_ENUM_UINT32;


/*****************************************************************************
 ö����    : MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32
 �ṹ˵��  : ��ǰ�Ľ��뼼��
 1.��    ��   : 2015��12��16��
   ��    ��   : y00314741
   �޸�����   : �½�
*****************************************************************************/
enum MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM
{
    MMA_TAF_HRPD_ACQUIRED_RESULT_SUCC,                  /* DO�з��� */
    MMA_TAF_HRPD_ACQUIRED_RESULT_FAIL,                  /* DO�޷��� */
    MMA_TAF_HRPD_ACQUIRED_RESULT_ABORT,                 /* DO��������� */
    MMA_TAF_HRPD_ACQUIRED_RESULT_NO_RF,                 /* DO������Դ */
    MMA_TAF_HRPD_ACQUIRED_RESULT_BUTT                   /* ��Ч��ֵ */
};
typedef VOS_UINT32 MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32;
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
typedef struct
{
    VOS_MSG_HEADER
    unsigned long                       ulMsgName;

    VOS_UINT8                           ucOmConnectFlg;                         /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM���õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */

    VOS_UINT8                           aucRsv2[2];                             /* ����   */
}MMCM_OM_MAINTAIN_INFO_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus;
}MNPH_USIM_STATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[4];
}TAF_MMA_POWER_OFF_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_MSG_CS_SERVICE_IND
 �ṹ˵��  : MMA��MSG����CS�����ṹ��
1.��    ��   : 2013��06��03��
  ��    ��   : s00217060
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    TAF_CS_SERVICE_ENUM_UINT32          enCSState;
}MMA_MSG_CS_SERVICE_IND;

/*****************************************************************************
 �ṹ��    : MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU
 �ṹ˵��  : MMA��SPM���ͷ���״̬����ṹ��
1.��    ��   : 2013��09��18��
  ��    ��   : s00217060
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU
 �ṹ˵��  : MMA��SPM����������������ṹ��
1.��    ��   : 2013��09��18��
  ��    ��   : s00217060
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : MMA_TAF_MODE_CHANGE_NOTIFY_STRU
 �ṹ˵��  : MMA��SPM����ģʽ����ṹ��
1.��    ��   : 2013��09��18��
  ��    ��   : s00217060
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}MMA_TAF_RAT_CHANGE_NOTIFY_STRU;

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, begin */
/*****************************************************************************
 �ṹ��    : MMA_TAF_IMS_VOICE_CAP_IND_STRU
 �ṹ˵��  : MMA��SPM����ims voice cap�ṹ��
1.��    ��   : 2013��12��31��
  ��    ��   : W00176964
  �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucImsVoiceAvail;                        /* IMS VOICE�Ƿ����:VOS_TRUE:IMS voice����; VOS_FALSE: IMS VOICE������ */
    VOS_UINT8                           aucReserve[3];                         /* ���� */
}MMA_TAF_IMS_VOICE_CAP_IND_STRU;

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, end */

/* �ƶ���tafappmma.h�� */


/*****************************************************************************
 �ṹ��    : MMA_TAF_1X_SERVICE_STATUS_IND_STRU
 �ṹ˵��  : MMA֪ͨTAF ����״̬��ز���
 1.��    ��   : 2014��10��19��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulExist1XService;
}MMA_TAF_1X_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMA_APS_CL_SERVICE_STATUS_IND_STRU
 �ṹ˵��  : MMA֪ͨAPS PS�����״̬��ز���
 1.��    ��   : 2015��05��24��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    MMA_TAF_CL_STATUS_ENUM_UINT32       enClStatus;
    VOS_UINT8                           ucIsNewSession;
    VOS_UINT8                           aucReserved[3];
}MMA_APS_CL_SERVICE_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : MMA_APS_CL_SERVICE_STATUS_IND_STRU
 �ṹ˵��  : MMA֪ͨAPS PS�����״̬��ز���
 1.��    ��   : 2015��05��24��
   ��    ��   : Y00213812
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgName;          /* _H2ASN_Skip */
    MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32          enHrpdSysAcqRst;
    MMA_TAF_RAT_TYPE_ENUM_UINT32                            enRatType;

}MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMA_TAF_SYS_CFG_INFO_IND_STRU
 �ṹ˵��  : MMA֪ͨAPS SYSCFG���
 1.��    ��   : 2015��12��29��
   ��    ��   : y00314741
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgName;          /* _H2ASN_Skip */
    TAF_MMA_RAT_ORDER_STRU              stOldRatOrder;
    TAF_MMA_RAT_ORDER_STRU              stNewRatOrder;
}MMA_TAF_SYS_CFG_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
}TAF_MMA_POWER_ON_IND_STRU;



/*****************************************************************************
 �ṹ��    : MMA_APS_EPDSZID_INFO_IND_STRU
 �ṹ˵��  : MMA֪ͨTAF EPDSZID��ز���
 1.��    ��   : 2014��12��24��
   ��    ��   : g00261581
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAF_MMA_PID_MSG_TYPE_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT8                           ucPzid;
    VOS_UINT8                           ucReserved[3];
}MMA_APS_EPDSZID_INFO_IND_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/* ASN�����ṹ */
typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_MMA_PID_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_PID_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_DATA                    stMsgData;
}TafMmaInterface_MSG;

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

#endif /* end of TafMmaInterface.h */


