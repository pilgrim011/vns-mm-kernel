

#ifndef __CNAS_EHSM_COM_FUNC_H__
#define __CNAS_EHSM_COM_FUNC_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "ehsm_aps_pif.h"
#include "CnasCcb.h"
#include "ehsm_hsm_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#define CNAS_EHSM_OP_TRUE                 (1)
#define CNAS_EHSM_OP_FALSE                (0)
#define CNAS_EHSM_MAX_EPSB_ID             (15)                /*���ĳ��غ�*/
#define CNAS_EHSM_MIN_EPSB_ID             (5)                 /*��С�ĳ��غ�*/
#define CNAS_EHSM_UNASSIGNED_EPSB_ID      (0)                 /*δ����ĳ��غ�*/

#define CNAS_EHSM_MAX_SDF_PF_NUM          (16)                /*SDF��֧�ֵ����PF��*/
#define CNAS_EHSM_MAX_FLOW_LABEL_TYPE     (0xFFFFF)           /* ipv6������ǵ����ֵ */
#define CNAS_EHSM_SDF_PF_NUM_ONE          (1)                 /*SDF��PF��Ϊ1*/

#define CNAS_EHSM_MAX_UE_CONTRUL_CID_NUM      (CNAS_EHSM_MAX_UE_CONTRUL_CID + 1)
#define CNAS_EHSM_MAX_CID_NUM                 (CNAS_EHSM_MAX_CID + 1)              /*����������������������*/

#define CNAS_EHSM_MAX_UE_CONTRUL_CID      (20)                /*UE���Ƶ����CID*/
#define CNAS_EHSM_MIN_NW_CONTROL_CID      (21)                /*NW���Ƶ���СCID*/

#define CNAS_EHSM_MAX_CID                 (31)                /*����CID*/
#define CNAS_EHSM_MIN_CID                 (0)                 /*��С��CID*/
#define CNAS_EHSM_ILL_CID                 (32)                /*��Ч��CID*/
#define CNAS_EHSM_ATTACH_CID              (0)                 /*ע��CID*/

#define CNAS_EHSM_MSG_LOW_BIT             0x0F
#define CNAS_EHSM_MSG_HIGH_BIT            0xF0
#define CNAS_EHSM_MSG_HIGH_3_BIT          0xE0

#define CNAS_EHSM_MSG_TWO_LEN             2
#define CNAS_EHSM_MOVEMENT_2_BITS         2
#define CNAS_EHSM_MOVEMENT_3_BITS         3
#define CNAS_EHSM_MOVEMENT_4_BITS         4
#define CNAS_EHSM_MOVEMENT_5_BITS         5
#define CNAS_EHSM_MOVEMENT_6_BITS         6
#define CNAS_EHSM_MOVEMENT_7_BITS         7
#define CNAS_EHSM_MOVEMENT_8_BITS         8
#define CNAS_EHSM_MOVEMENT_16_BITS        16
#define CNAS_EHSM_MOVEMENT_24_BITS        24

#define CNAS_EHSM_SEA_TABLE_ERR_LOC       0xFF
#define CNAS_EHSM_EVENTTYPE_FAIL          0xFFFF

#define CNAS_EHSM_LOW_2_BIT_MASK          0x03

#define CNAS_EHSM_HIGH_5_BIT_MASK         0xF8


/* ���ض�Ӧ�ļ����Cid����Ϊ1 */
#define CNAS_EHSM_BEARER_ACT_CID_NUM_ONE  1

#define CNAS_EHSM_MSGID_OFFSET            (2)
#define CNAS_EHSM_32BIT_DATA_LEN                            (32)                    /* 32λ���ݵ�bit���� */
#define CNAS_EHSM_INVALID_CID                               (0xFF)

#define CNAS_EHSM_GET_CTTF_ERR_CODE_MAP_TBL_PTR()           (g_astCnasEhsmCttfErrCodeMapTbl)
#define CNAS_EHSM_GET_CTTF_ERR_CODE_MAP_TBL_SIZE()          (sizeof(g_astCnasEhsmCttfErrCodeMapTbl)/sizeof(CNAS_EHSM_CTTF_ERR_CODE_MAP_STRU))

#define CNAS_EHSM_GET_HSM_ERR_CODE_MAP_TBL_PTR()            (g_astEhsmHsmErrCodeMapTbl)
#define CNAS_EHSM_GET_HSM_ERR_CODE_MAP_TBL_SIZE()           (sizeof(g_astEhsmHsmErrCodeMapTbl)/sizeof(HSM_EHSM_ERR_CODE_MAP_STRU))

#define CNAS_EHSM_GET_CTTF_PDN_TYPE_MAP_TBL_PTR()           (g_astCttfEhsmPdnTypeMapTbl)
#define CNAS_EHSM_GET_CTTF_PDN_TYPE_MAP_TBL_SIZE()          (sizeof(g_astCttfEhsmPdnTypeMapTbl)/sizeof(CTTF_EHSM_PDN_TYPE_MAP_STRU))

#define CNAS_EHSM_GET_EHSM_PDN_TYPE_MAP_TBL_PTR()           (g_astApsEhsmPdnTypeMapTbl)
#define CNAS_EHSM_GET_EHSM_PDN_TYPE_MAP_TBL_SIZE()          (sizeof(g_astApsEhsmPdnTypeMapTbl)/sizeof(CTTF_EHSM_PDN_TYPE_MAP_STRU))

#define CNAS_EHSM_GET_APS_PDN_TYPE_MAP_TBL_PTR()            (g_astApsCttfPdnTypeMapTbl)
#define CNAS_EHSM_GET_APS_PDN_TYPE_MAP_TBL_SIZE()           (sizeof(g_astApsCttfPdnTypeMapTbl)/sizeof(CNAS_EHSM_APS_CTTF_PDN_TYPE_MAP_STRU))

#define CNAS_EHSM_GET_CCB_PS_RAT_TYPE_MAP_TBL_PTR()         (g_astApsCcbPsRatTypeMapTbl)
#define CNAS_EHSM_GET_CCB_PS_RAT_TYPE_MAP_TBL_SIZE()        (sizeof(g_astApsCcbPsRatTypeMapTbl)/sizeof(APS_CCB_PS_RAT_TYPE_MAP_STRU))

#define CNAS_EHSM_GET_EHSM_AUTH_TYPE_MAP_TBL_PTR()         (g_astApsEhsmAuthTypeMapTbl)
#define CNAS_EHSM_GET_EHSM_AUTH_TYPE_MAP_TBL_SIZE()        (sizeof(g_astApsEhsmAuthTypeMapTbl)/sizeof(CNAS_EHSM_APS_EHSM_AUTH_TYPE_MAP_STRU))

#define CNAS_EHSM_GET_EHSM_ATTACH_TYPE_MAP_TBL_PTR()        (g_astCttfEhsmAttachTypeMapTbl)
#define CNAS_EHSM_GET_EHSM_ATTACH_TYPE_MAP_TBL_SIZE()       (sizeof(g_astCttfEhsmAttachTypeMapTbl)/sizeof(CTTF_EHSM_ATTACH_TYPE_MAP_STRU))

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/
enum CNAS_EHSM_CAUSE_ENUM
{
    CNAS_EHSM_CAUSE_SUCCESS                                   = 0,/*UE�Զ���*/
    CNAS_EHSM_CAUSE_ERROR                                     = 1,/*UE�Զ���*/

    CNAS_EHSM_CAUSE_OPERATOR_DETERMINE_BARRING                = 8,
    CNAS_EHSM_CAUSE_INSUFFICIENT_RESOURCES                    = 26,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_UNKNOWN_OR_MISSING_APN                    = 27,
    CNAS_EHSM_CAUSE_UNKNOWN_PDN_TYPE                          = 28,
    CNAS_EHSM_CAUSE_USER_AUTH_FAIL                            = 29,
    CNAS_EHSM_CAUSE_REQ_REJ_BY_SGW_OR_PGW                     = 30,
    CNAS_EHSM_CAUSE_REQ_REJ_UNSPECITY                         = 31,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_SERVICE_OPTION_NOT_SUPPORT                = 32,
    CNAS_EHSM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED                = 33,
    CNAS_EHSM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER             = 34,
    CNAS_EHSM_CAUSE_PTI_ALREADY_IN_USED                       = 35,
    CNAS_EHSM_CAUSE_REGULAR_DEACTIVATION                      = 36,
    CNAS_EHSM_CAUSE_EPS_QOS_NOT_ACCEPT                        = 37,
    CNAS_EHSM_CAUSE_NETWORK_FAILURE                           = 38,
    CNAS_EHSM_CAUSE_FEATURE_NOT_SUPPORTED                     = 40,
    CNAS_EHSM_CAUSE_SEMANTIC_ERR_IN_TFT                       = 41,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_SYNTACTIC_ERR_IN_TFT                      = 42,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_INVALID_EPS_BEARER_IDENTITY               = 43,
    CNAS_EHSM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER             = 44,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER           = 45,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_BEARER_WITHOUT_TFT_ACT                    = 46,/*UE���ܷ�����*/
    CNAS_EHSM_CAUSE_PTI_MISMATCH                              = 47,
    CNAS_EHSM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED              = 49,
    CNAS_EHSM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED                 = 50,
    CNAS_EHSM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED                 = 51,
    CNAS_EHSM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED           = 52,
    CNAS_EHSM_CAUSE_ESM_INFORMATION_NOT_RECEIVED              = 53,
    CNAS_EHSM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST             = 54,
    CNAS_EHSM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED = 55,
    CNAS_EHSM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST  = 56,
    CNAS_EHSM_CAUSE_UNSUPPORTED_QCI_VALUE                     = 59,
    CNAS_EHSM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN   = 66,
    CNAS_EHSM_CAUSE_INVALID_PTI_VALUE                         = 81,
    CNAS_EHSM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE            = 95,
    CNAS_EHSM_CAUSE_INVALID_MANDATORY_INFORMATION             = 96,
    CNAS_EHSM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED = 97,
    CNAS_EHSM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA = 98,
    CNAS_EHSM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED = 99,
    CNAS_EHSM_CAUSE_CONDITIONAL_IE_ERROR                      = 100,
    CNAS_EHSM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA      = 101,
    CNAS_EHSM_CAUSE_PROTOCOL_ERROR                            = 111,

    CNAS_EHSM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER = 112,

    CNAS_EHSM_CAUSE_MSG_TOO_SHORT                             = 200
};
typedef VOS_UINT8   CNAS_EHSM_CAUSE_ENUM_UINT8;
/** ****************************************************************************
 * Name        : EHSM_APS_PDN_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum CNAS_EHSM_PDN_TYPE_ENUM
{
    CNAS_EHSM_PDN_TYPE_INVALID           = 0x00,
    CNAS_EHSM_PDN_TYPE_IPV4              = 0x01,
    CNAS_EHSM_PDN_TYPE_IPV6              = 0x02,
    CNAS_EHSM_PDN_TYPE_IPV4V6            = 0x03,
    CNAS_EHSM_PDN_TYPE_BUTT              = 0x04
};
typedef VOS_UINT8 CNAS_EHSM_PDN_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CNAS_EHSM_ATTACH_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum CNAS_EHSM_ATTACH_TYPE_ENUM
{
    CNAS_EHSM_ATTACH_TYPE_INITIAL                     = 0x01,
    CNAS_EHSM_ATTACH_TYPE_HANDOVER                    = 0x03,
    CNAS_EHSM_ATTACH_TYPE_ENUM_BUTT                   = 0x04
};
typedef VOS_UINT8 CNAS_EHSM_ATTACH_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : EHSM_ESM_PDN_OPTION_ENUM_UINT32
 *
 * Description :
 *******************************************************************************/
enum CNAS_EHSM_PDN_OPTION_ENUM
{
    CNAS_EHSM_PDN_OPT_CONNECTED          = 0x00000000,
    CNAS_EHSM_PDN_OPT_MODIFIED           = 0x00000001,
    CNAS_EHSM_PDN_OPT_DISCONNECTED       = 0x00000002,
    CNAS_EHSM_PDN_OPTION_ENUM_BUTT       = 0x00000003
};
typedef VOS_UINT32 CNAS_EHSM_PDN_OPTION_ENUM_UINT32;

enum CNAS_EHSM_GET_IPV6_DNS_CTRL_ENUM
{
    CNAS_EHSM_GET_IPV6_DNS_CTRL_OFF        = 0x00 ,
    CNAS_EHSM_GET_IPV6_DNS_CTRL_ON         = 0x01,

    CNAS_EHSM_GET_IPV6_DNS_CTRL_BUTT
};
typedef VOS_UINT32  CNAS_EHSM_GET_IPV6_DNS_CTRL_ENUM_UINT32;

enum CNAS_EHSM_ERROR_CODE_ENUM
{
    CNAS_EHSM_SUCCESS                                         = 0,         /*ESM ģ�麯�����سɹ�*/
    CNAS_EHSM_FAILURE                                            ,         /*ESM ģ�麯������ʧ��*/
    CNAS_EHSM_MSG_DISCARD                                        ,         /*������Ϣ*/
    CNAS_EHSM_MSG_HANDLED                                                 /*��Ϣ�Ѵ��� */
};

/*****************************************************************************
 * Name        : CNAS_EHSM_AUTH_TYPE_ENUM_UINT8
 *
 * Description : ��Ȩ����
*****************************************************************************/
enum CNAS_EHSM_AUTH_TYPE_ENUM
{
    CNAS_EHSM_AUTH_TYPE_NONE             = 0x00,
    CNAS_EHSM_AUTH_TYPE_PAP              = 0x01,
    CNAS_EHSM_AUTH_TYPE_CHAP             = 0x02,
    CNAS_EHSM_AUTH_TYPE_PAP_OR_CHAP      = 0x03,
    CNAS_EHSM_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_EHSM_AUTH_TYPE_ENUM_UINT8;
/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/


/*ESM ��¼�տ���ϢIE�����ݽṹ*/
typedef struct
{
    VOS_UINT8                           ucLen;              /* IE�ĳ���       */
    VOS_UINT8                           aucReserve1[3];     /* ���ֽڶ��룬���� */
    VOS_UINT8                          *pucValue;           /* IE���׵�ַ     */
}CNAS_EHSM_MSG_IE_COMMON_STRU;
/*ESM ��¼�տ���Ϣ��TAD��Ϣ*/

/*ESM ��¼�տ���Ϣ��Notification Indicator��Ϣ*/
typedef struct
{
    VOS_UINT8                           ucValue;
    VOS_UINT8                           aucRsv[3];
}CNAS_EHSM_NOTIFICATION_IND_STRU;

/*****************************************************************************
 �ṹ��  : CNAS_EHSM_CTTF_ERR_CODE_MAP_STRU
 �ṹ˵��: CTTF��ԭ��ֵ��APS���ԭ��ֵת����

 �޸���ʷ      :
  1.��    ��   : 2015��05��26��
    ��    ��   : h00246512
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    EHSM_APS_CAUSE_ENUM_UINT32               enEsmApsCause;
    VOS_UINT32                               ulCttfErrCode;
} CNAS_EHSM_CTTF_ERR_CODE_MAP_STRU;
/*****************************************************************************
 �ṹ��  : HSM_EHSM_ERR_CODE_MAP_STRU
 �ṹ˵��: TAF��������EHSM������ӳ��ṹ

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : y00322978
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    EHSM_HSM_RSLT_ENUM_UINT32           enHsmCause;
    EHSM_APS_CAUSE_ENUM_UINT32          enApsCause;
} HSM_EHSM_ERR_CODE_MAP_STRU;

/*****************************************************************************
 �ṹ��  : CTTF_EHSM_PDN_TYPE_MAP_STRU
 �ṹ˵��: cttf  ��ehsm��pdnn typeӳ��

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : f00279542
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8 enCttfPdnType;
    CNAS_EHSM_PDN_TYPE_ENUM_UINT8       enEhsmPdnType;
    VOS_UINT8                           aucReserved[2];
} CTTF_EHSM_PDN_TYPE_MAP_STRU;

/*****************************************************************************
 �ṹ��  : CNAS_EHSM_APS_EHSM_PDN_TYPE_MAP_STRU
 �ṹ˵��: aps  ��ehsm��pdnn typeӳ��

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : f00279542
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    EHSM_APS_PDN_TYPE_ENUM_UINT8        enApsPdnType;
    CNAS_EHSM_PDN_TYPE_ENUM_UINT8       enEhsmPdnType;
    VOS_UINT8                           aucReserved[2];
} CNAS_EHSM_APS_EHSM_PDN_TYPE_MAP_STRU;
/*****************************************************************************
 �ṹ��  : CNAS_EHSM_APS_CTTF_PDN_TYPE_MAP_STRU
 �ṹ˵��: cttf  ��APS ��pdnn typeӳ��

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : f00279542
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    EHSM_APS_PDN_TYPE_ENUM_UINT8        enApsPdnType;
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8 enCttfPdnType;
    VOS_UINT8                           aucReserved[2];
} CNAS_EHSM_APS_CTTF_PDN_TYPE_MAP_STRU;

/*****************************************************************************
 �ṹ��  : APS_CCB_PS_RAT_TYPE_MAP_STRU
 �ṹ˵��: aps  ��ccb ��ps rat typeӳ��

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : f00279542
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    APS_EHSM_PS_RATTYPE_ENUM_UINT32     enAspPsRatType;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enCcbPsRatType;
} APS_CCB_PS_RAT_TYPE_MAP_STRU;

/*****************************************************************************
 �ṹ��  : CNAS_EHSM_APS_EHSM_AUTH_TYPE_MAP_STRU
 �ṹ˵��: APS �� EHSM ��AUTH TYPEӳ��

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
typedef struct
{
    EHSM_APS_AUTH_TYPE_ENUM_UINT8       enAuthType;
    CNAS_EHSM_AUTH_TYPE_ENUM_UINT8      enEhsmAuthType;
    VOS_UINT8                           aucReserved[2];
} CNAS_EHSM_APS_EHSM_AUTH_TYPE_MAP_STRU;

/*****************************************************************************
 �ṹ��  : APS_CCB_PS_RAT_TYPE_MAP_STRU
 �ṹ˵��: cctf  ��ehsm ��attach typeӳ��

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : f00279542
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_UINT8                  enCttfAttachType;
    CNAS_EHSM_ATTACH_TYPE_ENUM_UINT8                        enEhsmAttachType;
    VOS_UINT8                                               aucReserved[2];
} CTTF_EHSM_ATTACH_TYPE_MAP_STRU;
/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
VOS_UINT8 CNAS_EHSM_GetCidFromLteBitCid(
    VOS_UINT32                          ulBitCid
);

VOS_UINT32 CNAS_EHSM_IsPsRatTypeChanged
(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enCcbPsRatType,
    APS_EHSM_PS_RATTYPE_ENUM_UINT32     enPsRatType
);


EHSM_APS_CAUSE_ENUM_UINT32 CNAS_EHSM_MapCttfErrCode(
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16   enErrorCode
);

VOS_UINT32 CNAS_EHSM_MapHsmCauseToAps(
    EHSM_HSM_RSLT_ENUM_UINT32        enCause
);
CNAS_EHSM_PDN_TYPE_ENUM_UINT8 CNAS_EHSM_MapCttfPdnTypeToEhms(
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enCttfPdnType
);

CNAS_EHSM_PDN_TYPE_ENUM_UINT8 CNAS_EHSM_MapApsPdnTypeToEhsm(
    EHSM_APS_PDN_TYPE_ENUM_UINT8        enPdnType
);

CNAS_EHSM_ATTACH_TYPE_ENUM_UINT8 CNAS_EHSM_MapCttfAttachTypeToEhsm(
    CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_UINT8                  enAttachType
);
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_EHSM_MapApsPsRatTypeToCcb(
    APS_EHSM_PS_RATTYPE_ENUM_UINT32     enApsPsRatType
);

VOS_UINT32 CNAS_EHSM_IsCommonConnRetryNeeded(
    EHSM_HSM_RSLT_ENUM_UINT32 ulHsmCommConnEstCnfResult
);

CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8 CNAS_EHSM_MapEhsmPdnTypeToCttf(
    CNAS_EHSM_PDN_TYPE_ENUM_UINT8       enPdnType
);



EHSM_APS_PDN_TYPE_ENUM_UINT8 CNAS_EHSM_MapEhsmPdnTypeToAps(
    CNAS_EHSM_PDN_TYPE_ENUM_UINT8       enPdnType
);

CNAS_EHSM_AUTH_TYPE_ENUM_UINT8 CNAS_EHSM_MapApsAuthTypeToEhsm(
    EHSM_APS_AUTH_TYPE_ENUM_UINT8       enAuthType
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

#endif /* end of CnasEhsmComFunc.h */


