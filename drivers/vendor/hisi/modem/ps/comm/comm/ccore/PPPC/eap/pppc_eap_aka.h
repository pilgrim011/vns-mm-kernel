
#ifndef      _PPPC_EAP_AKA_H_
#define      _PPPC_EAP_AKA_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtPppInterface.h"
#include "PsCommonDef.h"
#include "product_config.h"
#include "TTFUtil.h"
#include "v_IO.h"
#include "TTFComm.h"
#include "TTFLink.h"
#include "PsTypeDef.h"
#include "UsimPsInterface.h"

#include "TtfDrvInterface.h"
#include "pppc_uim.h"
#include "TtfIpComm.h"
#include "pppc_sha1.h"
#include "pppc_sha256.h"
#include "pppc_aes.h"
#include "pppc_eap_typ.h"
#include "ppp_dbug.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* EAP ��Ϣͷ������ */
#define PPPC_EAP_HEADER_LEN                             (4)

/* EAP-AKA Subtypes "RFC4187 Page671" */
#define PPPC_EAP_AKA_SUBTYPE_CHALLENGE                  (1)
#define PPPC_EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT      (2)
#define PPPC_EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE    (4)
#define PPPC_EAP_AKA_SUBTYPE_IDENTITY                   (5)
#define PPPC_EAP_AKA_SUBTYPE_NOTIFICATION               (12)
#define PPPC_EAP_AKA_SUBTYPE_REAUTHENTICATION           (13)
#define PPPC_EAP_AKA_SUBTYPE_CLIENT_ERROR               (14)


/* EAP-AKA and EAP-AKA' Attributes (0..127 non-skippable) */
#define PPPC_EAP_AKA_AT_RAND                            (1)
#define PPPC_EAP_AKA_AT_AUTN                            (2) /* only AKA */
#define PPPC_EAP_AKA_AT_RES                             (3) /* only AKA, only peer->server */
#define PPPC_EAP_AKA_AT_AUTS                            (4) /* only AKA, only peer->server */
#define PPPC_EAP_AKA_AT_PADDING                         (6) /* only encrypted */
#define PPPC_EAP_AKA_AT_PERMANENT_ID_REQ                (10)
#define PPPC_EAP_AKA_AT_MAC                             (11)
#define PPPC_EAP_AKA_AT_NOTIFICATION                    (12)
#define PPPC_EAP_AKA_AT_ANY_ID_REQ                      (13)
#define PPPC_EAP_AKA_AT_IDENTITY                        (14) /* only send */
#define PPPC_EAP_AKA_AT_FULLAUTH_ID_REQ                 (17)
#define PPPC_EAP_AKA_AT_COUNTER                         (19) /* only encrypted */
#define PPPC_EAP_AKA_AT_COUNTER_TOO_SMALL               (20) /* only encrypted */
#define PPPC_EAP_AKA_AT_NONCE_S                         (21) /* only encrypted */
#define PPPC_EAP_AKA_AT_CLIENT_ERROR_CODE               (22) /* only send */
#define PPPC_EAP_AKA_AT_KDF_INPUT                       (23) /* only AKA' */
#define PPPC_EAP_AKA_AT_KDF                             (24) /* only AKA' */
#define PPPC_EAP_AKA_AT_IV                              (129)
#define PPPC_EAP_AKA_AT_ENCR_DATA                       (130)
#define PPPC_EAP_AKA_AT_NEXT_PSEUDONYM                  (132) /* only encrypted */
#define PPPC_EAP_AKA_AT_NEXT_REAUTH_ID                  (133) /* only encrypted */
#define PPPC_EAP_AKA_AT_CHECKCODE                       (134)
#define PPPC_EAP_AKA_AT_RESULT_IND                      (135)
#define PPPC_EAP_AKA_AT_BIDDING                         (136)


/* AT_NOTIFICATION notification code values */
#define PPPC_EAP_AKA_GENERAL_FAILURE_AFTER_AUTH         (0)
#define PPPC_EAP_AKA_TEMPORARILY_DENIED                 (1026)
#define PPPC_EAP_AKA_NOT_SUBSCRIBED                     (1031)
#define PPPC_EAP_AKA_GENERAL_FAILURE_BEFORE_AUTH        (16384)
#define PPPC_EAP_AKA_SUCCESS                            (32768)

/* EAP-AKA' AT_KDF Key Derivation Function values */
#define PPPC_EAP_AKA_PRIME_KDF                          (1)

/* AT_CLIENT_ERROR_CODE error codes */
#define PPPC_EAP_AKA_UNABLE_TO_PROCESS_PACKET           (0)

/* IK�ĳ��� */
#define PPPC_EAP_AKA_IK_LEN                             (16)

/* CK�ĳ��� */
#define PPPC_EAP_AKA_CK_LEN                             (16)

/* K_encr�ĳ��� */
#define PPPC_EAP_AKA_K_ENCR_LEN                         (16)

/* EAP_AKA��K_aut�ĳ��� */
#define PPPC_EAP_AKA_K_AUT_LEN                          (16)

/* EAP_AKA'��K_aut�ĳ��� */
#define PPPC_EAP_AKA_PRIME_K_AUT_LEN                    (32)

/* EAP_AKA'��K_re�ĳ��� */
#define PPPC_EAP_AKA_PRIME_K_RE_LEN                     (32)

/* MKS�ĳ��� */
#define PPPC_EAP_AKA_MSK_LEN                            (64)

/* EMSK�ĳ��� */
#define PPPC_EAP_AKA_EMSK_LEN                           (64)

/* NONCE_S�ĳ��� */
#define PPPC_EAP_AKA_NONCE_S_LEN                        (16)

/* CHECK CODE����󳤶� */
#define PPPC_EAP_AKA_CHECKCODE_MAX_LEN                  (32)

/* CHECK CODE����С���� */
#define PPPC_EAP_AKA_CHECKCODE_MIN_LEN                  (20)

/* AT_NOTIFICATION��value���� */
#define PPPC_EAP_AKA_AT_NOTIFICATION_VALUE_LEN           (2)

/* AT_COUNTER��value���� */
#define PPPC_EAP_AKA_AT_COUNTER_VALUE_LEN                (2)

/* AT_KDF��value���� */
#define PPPC_EAP_AKA_AT_KDF_VALUE_LEN                    (2)

/* AT_RESULT_IND��value���� */
#define PPPC_EAP_AKA_AT_RESULT_IND_VALUE_LEN             (2)


/*AT_BIDDING��value���� */
#define PPPC_EAP_AKA_AT_BIDDING_VALUE_LEN                (2)


/* ��AT_ENCR_DATA������Ҫ�õ����м�ֵ */
#define PPPC_EAP_AKA_16_BYTE                             (16)



/* �������Ƶ���󳤶� */
#define PPPC_EAP_AKA_NETNAME_MAX_LEN                    (256)

/* MK�ĳ��� */
#define PPPC_EAP_AKA_MK_LEN                             (20)

/* RAND�ĳ��� */
#define PPPC_EAP_AKA_RAND_LEN                           (16)

/* AUTN�ĳ��� */
#define PPPC_EAP_AKA_AUTN_LEN                           (16)

/* AUTS�ĳ��� */
#define PPPC_EAP_AKA_AUTS_LEN                           (14)

/* AT_MAC value�ĳ��� */
#define PPPC_EAP_AKA_MAC_VALUE_LEN                      (16)

/* AT_MAC �ܵĳ��� */
#define PPPC_EAP_AKA_MAC_TOTAL_LEN                      (20)

/* HASH�㷨�������MAC��󳤶� */
#define PPPC_EAP_AKA_MAC_MAX_LEN                        (32)

/* AT_IV value�ĳ��� */
#define PPPC_EAP_AKA_IV_LEN                             (16)

/* KDF �������� */
#define PPPC_EAP_AKA_PRIME_KDF_MAX                      (10)

/**************************************************************************
RFC4282:Support for an NAI length of 253 octets is RECOMMENDED.
RFC1421:This line length is easily printable and is gurateed to satisfy SMTP's
        1000-character transmitted line length limit.
**************************************************************************/
#define PPPC_EAP_AKA_IDENTITY_REC_LEN                   (253)                               /* NAI���Ƽ����� */

/* ����IDENTITY����󳤶�, ��������PPPC_EAP_AKA_IDENTITY_REC_LEN���������
   �������䶨��ΪPPPC_EAP_AKA_IDENTITY_REC_LEN�Ĵ�С�͹���, ������ʹ����ʱ,
   �����ʵ���ȷ���һ��, �������ڽṹ����,
   ���IDENTITYռ�õĿռ䰴��4�ֽڶ���, ����256 */
#define PPPC_EAP_AKA_IDENTITY_MAX_LEN                   (256)

/* �������ݵ���󳤶�AT_NEXT_PSEUDONYM(260)+AT_NEXT_REAUTH_ID(260)+AT_COUNTER(4)+AT_NONCE_S(20) */
#define PPPC_EAP_AKA_ENRC_DATA_LEN                      (544)

/* ����IdMsg��Ϣ����󳤶�3*(Identity_Request + Identity_Response), ��(260+8)*3 + (4+8)*3 */
#define PPPC_EAP_AKA_ID_MSG_MAX_LEN                     (840)

/* ATTRIBUTEƫ����(ָAttribute Type + Length����ռ�õ��ֽ���) */
#define PPPC_EAP_AKA_ATTRIBUTE_TYPE_VALUE_OFFSET         (2)

/* ATTRIBUTEƫ������ƫ����(�е�������Rerseved��, ָ�������ռ�õ��ֽ���) */
#define PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET     (2)

/* AKA CHECKCODE value ���� */
#define PPPC_EAP_AKA_CHECKCODE_LEN                       (20)

/* AKA��CHECKCODE value ���� */
#define PPPC_EAP_AKA_PRIME_CHECKCODE_LEN                 (32)

/* AT_PADDING����󳤶� */
#define PPPC_EAP_AKA_PADDING_MAX_LEN                     (12)

/* ����EAP���ĳ��� */
#define PPPC_EAP_MAX_PACKET_LEN                          (512)

/* EAP_AKA'�ؼ�Ȩ��MK�ĳ��� */
#define PPPC_EAP_AKA_REAUTH_MK_LEN                       (128)

/* EAP_AKA'����MKʱ"EAP-AKA'"�ĳ��� */
#define PPPC_EAP_AKA_PRF_STR_LEN                          (8)

/* EAP_AKA'�ؼ�ȨEAP-AKA' re-auth"�ĳ��� */
#define PPPC_EAP_AKA_REAUTH_PRF_STR_LEN                   (16)

/* EAP_AKA����KeyʱBuf�ĳ��� */
#define PPPC_EAP_AKA_BUF_LEN                             (160)

/* SQN�ĳ��� */
#define PPPC_EAP_AKA_SQN_LEN                              (6)

/* IK|CK�ĳ��� */
#define PPPC_EAP_AKA_IK_AND_CK_LEN                        (32)

/* ����IK',CK'ʱS��L0,L1�ĳ��� */
#define PPPC_EAP_AKA_S_L_LEN                              (2)

/* AT_COUNTER value��ռ���ֽڳ��� */
#define PPPC_EAP_AKA_COUNTER_LEN                          (2)

/* EAP_AKA'��MK�ĳ��� */
#define PPPC_EAP_AKA_PRIME_MK_LEN                        (208)

/* Peer����Ŀ����ؼ�Ȩ�������� */
#define PPPC_EAP_AKA_MAX_FAST_REAUTHS                    (1000)

/* �����NAI��ʶ */
#define PPPC_EAP_AKA_CLEAR_PSEUDONYM                     (0x01)
#define PPPC_EAP_AKA_CLEAR_REAUTH_ID                     (0x02)
#define PPPC_EAP_AKA_CLEAR_EAP_ID                        (0x04)

/* ulAttrExistCtrlFlag */
#define PPPC_EAP_AKA_RAND_BIT                            (0x00)
#define PPPC_EAP_AKA_AUTN_BIT                            (0x01)
#define PPPC_EAP_AKA_MAC_BIT                             (0x02)
#define PPPC_EAP_AKA_IV_BIT                              (0x03)
#define PPPC_EAP_AKA_ENCR_BIT                            (0x04)
#define PPPC_EAP_AKA_NONCE_S_BIT                         (0x05)
#define PPPC_EAP_AKA_CHECKCODE_BIT                       (0x06)
#define PPPC_EAP_AKA_KDF_BIT                             (0x07)
#define PPPC_EAP_AKA_KDF_INPUT_BIT                       (0x08)
#define PPPC_EAP_AKA_NEXT_PSEUDONYM_BIT                  (0x09)
#define PPPC_EAP_AKA_NEXT_REAUTH_BIT                     (0x0A)
#define PPPC_EAP_AKA_COUNTER_BIT                         (0x0B)
#define PPPC_EAP_AKA_PADDING_BIT                         (0x0C)
#define PPPC_EAP_AKA_PERMANENT_BIT                       (0x0D)
#define PPPC_EAP_AKA_NOTIFICATION_BIT                    (0x0E)
#define PPPC_EAP_AKA_ANY_ID_BIT                          (0x0F)
#define PPPC_EAP_AKA_FULLAUTH_ID_BIT                     (0x10)
#define PPPC_EAP_AKA_RESULT_IND_BIT                      (0x11)
#define PPPC_EAP_AKA_BIDDING_BIT                         (0x12)

/*
   ����NAI��realm�����������̶ֹ��ַ���(e.g., nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org)
   nai.epc.mnc | .mcc | .3gppnetwork.org
*/
#define PPPC_EAP_PERMANENT_NAI_REALM_MAX_PART              (3)

/*
   ����NAI��realm���и��̶��ַ���, �������ַ��� �����ֵ
   max(size(nai.epc.mnc), size(.mcc), size(.3gppnetwork.org))
*/
#define PPPC_EAP_PERMANENT_NAI_REALM_PER_PART_MAX_CHAR_NUM  (16)

#define PPPC_EAP_AKA_NOTIFICATION_P_IS_1                  (0x4000)
#define PPPC_EAP_AKA_NOTIFICATION_INVALID_VALUE           (0xffff)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/** ****************************************************************************
 * Name        : PPPC_EAP_METHOD_TYPE_ENUM_UINT16
 *
 * Description : EAP METHOD TYPE
 *******************************************************************************/
enum PPPC_EAP_METHOD_TYPE_ENUM
{
    PPPC_EAP_METHOD_TYPE_AKA                = 0x0000,
    PPPC_EAP_METHOD_TYPE_AKA_PRIME          = 0x0001,
    PPPC_EAP_METHOD_TYPE_ENUM_BUTT          = 0xFFFF
};
typedef VOS_UINT16 PPPC_EAP_METHOD_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16
 *
 * Description : ID REQ TYPE
 *******************************************************************************/
enum PPPC_EAP_AKA_ID_REQ_TYPE_ENUM
{
    PPPC_EAP_AKA_ANY_ID_REQ               = 0x0000,
    PPPC_EAP_AKA_FULLAUTH_ID_REQ          = 0x0001,
    PPPC_EAP_AKA_PERMANENT_ID_REQ         = 0x0002,
    PPPC_EAP_AKA_ID_REQ_BUTT              = 0x0003
};
typedef VOS_UINT16 PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_EAP_AKA_STATE_ENUM_UINT16
 *
 * Description : EAP-AKA STATE
 *******************************************************************************/
enum PPPC_EAP_AKA_STATE_ENUM
{
    PPPC_EAP_AKA_STATE_CONTINUE             = 0x0000,
    PPPC_EAP_AKA_STATE_RESULT_SUCCESS       = 0x0001,
    PPPC_EAP_AKA_STATE_SUCCESS              = 0x0002,
    PPPC_EAP_AKA_STATE_FAILURE              = 0x0003,
    PPPC_EAP_AKA_STATE_BUTT                 = 0xFFFF
};
typedef VOS_UINT16 PPPC_EAP_AKA_STATE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM_UINT8
 *
 * Description : ����NAI��realm���й̶��ַ��ζκ�(��3��)
 *******************************************************************************/
enum PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM
{
    PPPC_EAP_PERMANENT_NAI_REALM_PART_ONE      = 0,
    PPPC_EAP_PERMANENT_NAI_REALM_PART_TWO      = 1,
    PPPC_EAP_PERMANENT_NAI_REALM_PART_THREE    = 2,
    PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM_BUTT
};
typedef VOS_UINT8 PPPC_EAP_PERMANENT_NAI_REALM_PART_ENUM_UINT8;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/** ****************************************************************************
* Name        : PPPC_EAP_AKA_KEY_DATA_STRU
*
* Description : �洢EAP_AKA/EAP_AKA'��������Ĳ���
*******************************************************************************/
typedef struct
{
    VOS_UINT8         aucIK[PPPC_EAP_AKA_IK_LEN];
    VOS_UINT8         aucCK[PPPC_EAP_AKA_CK_LEN];
    VOS_UINT8         aucIKPrime[PPPC_EAP_AKA_IK_LEN];
    VOS_UINT8         aucCKPrime[PPPC_EAP_AKA_CK_LEN];
    VOS_UINT8         aucPrimeK_aut[PPPC_EAP_AKA_PRIME_K_AUT_LEN];
    VOS_UINT8         aucK_aut[PPPC_EAP_AKA_K_AUT_LEN];
    VOS_UINT8         aucK_encr[PPPC_EAP_AKA_K_ENCR_LEN];
    VOS_UINT8         aucK_re[PPPC_EAP_AKA_PRIME_K_RE_LEN]; /* EAP-AKA' only */
    VOS_UINT8         aucMSK[PPPC_EAP_AKA_MSK_LEN];
    VOS_UINT8         aucEMSK[PPPC_EAP_AKA_EMSK_LEN];
    VOS_UINT8         aucMk[PPPC_EAP_AKA_MK_LEN]; /* EAP-AKA only */
    VOS_UINT8         ucRerserve[2];
}PPPC_EAP_AKA_KEY_DATA_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_AUTH_PARA_STRU
*
* Description : �洢����������ģ�Peer��ʹ�õ�һЩ���Բ���
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNonce_s[PPPC_EAP_AKA_NONCE_S_LEN];
    VOS_UINT8                           aucRand[PPPC_EAP_AKA_RAND_LEN]; /* 128bits */
    VOS_UINT8                           aucAutn[PPPC_EAP_AKA_AUTN_LEN];
    VOS_UINT8                           aucNetworkName[PPPC_EAP_AKA_NETNAME_MAX_LEN];
    VOS_UINT16                          usCounter;
    VOS_UINT16                          usNetworkNameLen;
    VOS_UINT16                          usKdf;
}PPPC_EAP_AKA_AUTH_PARA_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ID_INFO_STRU
*
* Description : �洢EAP-AKA��Identity��Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPermenentId[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usPermenentIdLen;
    VOS_UINT8                           aucPseudonym[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usPseudonymLen;
    VOS_UINT8                           aucReauthId[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usReauthIdLen;
    VOS_UINT8                           aucLastEapIdentity[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                          usLastEapIdentityLen;
}PPPC_EAP_AKA_ID_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_eap_aka_data
*
* Description : EAP-AKA��ʵ����Ϣ
*******************************************************************************/
typedef struct
{
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;        /* EAP-AKA or EAP-AKA' */
    PPPC_EAP_AKA_STATE_ENUM_UINT16      enEapAkaState;      /* EAP AKA STATE */
    PS_BOOL_ENUM_UINT8                  enReauth;           /* PS_TRUE: Re-auth, PS_FALSE: Full-auth */
    PS_BOOL_ENUM_UINT8                  enKdfNegotiation;
    VOS_UINT8                           ucNumNotification;  /* ���յ���notification�ļ��� */
    VOS_UINT8                           ucNumIdReq;         /* ���յ�Identification��Ϣ�ļ��� */
    VOS_UINT16                          usPrevId;          /* ��һ����Ϣ��ID */
    VOS_UINT8                           ucIdMsgs[PPPC_EAP_AKA_ID_MSG_MAX_LEN];         /* EAP-AKA/Identification��Ϣ*/
    VOS_UINT16                          usIdMsgLen;         /* Id_Msg���ֽڳ��� */
    VOS_UINT8                           aucPppcInputMsg[PPPC_EAP_MAX_PACKET_LEN]; /* ����Eap�ݹ����ı��� */
    VOS_UINT16                          usInputMsgLen;   /* Eap�ݹ����ı��ĳ��� */
    PS_BOOL_ENUM_UINT8                  enResultInd; /* AKA-Challenge or AKA-Reauthentication will include AT_Result_Ind */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usCounterTooSmall;
    PPPC_EAP_AKA_KEY_DATA_STRU          stEapAkaKey;        /* EAP-AKA��Ȩ�����е�Key��Ϣ */
    PPPC_EAP_AKA_AUTH_PARA_STRU         stEapAkaAuthPara;   /* ��Ȩ��һЩ������Ϣ */
    PPPC_EAP_AKA_ID_INFO_STRU           stEapAkaIdInfo;     /* ID��Ϣ */
}PPPC_EAP_AKA_DATA_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATTRS_STRU
*
* Description : ��EAP���ݰ���������������Ϣ
*******************************************************************************/
typedef struct
{
    /*ulAttrExistCtrlFlag has 32bits
      bit0:enExistRand,  bit1:enExistRutn,  bit2:enExistMac,  bit3:enExistIv,
      bit4:enExistEncrData,  bit5:enExistNonce_s,  bit6:enExistCheckCode,  bit7:enExistKdf,
      bit8:enExistKdfInput,  bit9:enExistNextPseudonym,  bit10:enExistNextReauthId,  bit11:enExistCounter
    */
    VOS_UINT32                              ulAttrExistCtrlFlag;
    VOS_UINT8                               aucRand[PPPC_EAP_AKA_RAND_LEN]; /* 128bits */
    VOS_UINT8                               aucAutn[PPPC_EAP_AKA_AUTN_LEN];
    VOS_UINT8                               aucMac[PPPC_EAP_AKA_MAC_VALUE_LEN];
    VOS_UINT8                               aucIv[PPPC_EAP_AKA_IV_LEN];
    VOS_UINT8                               aucEncrData[PPPC_EAP_AKA_ENRC_DATA_LEN];
    VOS_UINT16                              usEncrDataLen;
    VOS_UINT8                               aucNonce_s[PPPC_EAP_AKA_NONCE_S_LEN];
    VOS_UINT8                               aucCheckCode[PPPC_EAP_AKA_CHECKCODE_MAX_LEN]; /* EAP-AKA:20bytes, EAP-AKA':32bytes */
    VOS_UINT16                              usCheckCodeLen;
    VOS_UINT16                              ausKdf[PPPC_EAP_AKA_PRIME_KDF_MAX];
    VOS_UINT16                              usKdfCount;
    VOS_UINT8                               aucKdfInput[PPPC_EAP_AKA_NETNAME_MAX_LEN];
    VOS_UINT16                              usKdfInputLen;
    VOS_UINT8                               aucNextPseudonym[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                              usNextPseudonymLen;
    VOS_UINT8                               aucNextReauthId[PPPC_EAP_AKA_IDENTITY_MAX_LEN];
    VOS_UINT16                              usNextReauthIdLen;
    PS_BOOL_ENUM_UINT8                      enResultInd;
    VOS_UINT8                               aucRerserve1[1];
    VOS_UINT16                              usNotification;
    VOS_UINT16                              usCounter;
    PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16    enEapAkaIdReqType;
    VOS_UINT16                              usBidding;
    VOS_UINT8                               aucRerserve2[2];
}PPPC_EAP_AKA_ATTRS_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATTR_INFO_STRU
*
* Description : EAP-AKA������Ϣ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAttrId;
    VOS_UINT8                           aucRerserve1[3];
    VOS_UINT16                          usValue;
    VOS_UINT16                          usDataLen;    /* ��λ: �ֽ� */
    VOS_UINT8                          *pData;
}PPPC_EAP_AKA_ATTR_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU
*
* Description : ����NAI��realm���и��̶��ַ��ε������ṹ
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPartCharNum;    /* �̶��ַ������ַ����� */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPartChar[PPPC_EAP_PERMANENT_NAI_REALM_PER_PART_MAX_CHAR_NUM];
}PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU;

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATT_WALKER_STRU
*
* Description : ��������Ҫ��һЩ�м����
******************************************************************************/
typedef struct
{
    VOS_UINT8                       *pucAttPos;
    VOS_UINT16                       usAttrLen;
    VOS_UINT8                        aucReserved[1];
    PS_BOOL_ENUM_UINT8               enEncr;
    PPPC_EAP_AKA_ATTRS_STRU         *pstPppcEapAkaPktAttrInfo;
} PPPC_EAP_AKA_ATT_WALKER_STRU;

/*define a function pointer to register a func to match muxtype1 header info*/
typedef VOS_UINT32 (*PPPC_EAP_AKA_MATCH_FUNC)(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);

/** ****************************************************************************
* Name        : PPPC_EAP_AKA_ATTRIBUTE_DATA_STRU
*
* Description : �洢ATTRIBUTE���ͺͶ�Ӧ������ָ��
*******************************************************************************/
typedef struct
{
    VOS_UINT8                                          aucAttributeType;
    VOS_UINT8                                          aucReserved[3];
    PPPC_EAP_AKA_MATCH_FUNC                            pfuncMatchHead;
}PPPC_EAP_AKA_ATTRIBUTE_DATA_STRU;


/** ****************************************************************************
* Name        : PPPC_EAP_AKA_TRACE_INFO_STRU
*
* Description : EAP_AKA Trace Info
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    PPPC_TRACE_MSG_TYPE_ENUM_UINT16     enMsgId;            /* Trace Msg Type */
    VOS_UINT16                          usVersion;          /* Trace Version */
    PPPC_EAP_AKA_AUTH_PARA_STRU         stEapAkaAuthPara;   /* ��Ȩ��һЩ������Ϣ */
    PPPC_EAP_AKA_KEY_DATA_STRU          stEapAkaKey;        /* EAP-AKA��Ȩ�����е�K��Ϣ */
}PPPC_EAP_AKA_TRACE_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_Init
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType
);
VOS_VOID PPPC_EAP_AKA_InitState(VOS_VOID);
VOS_VOID PPPC_EAP_AKA_NotifyResult(VOS_UINT32 ulRes);
VOS_VOID PPPC_EAP_AKA_ProcessPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInputs
);
VOS_UINT32 PPPC_EAP_GetIdentity
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType,
    VOS_UINT8                           aucIdentity[],
    VOS_UINT16                         *pusIdentityLen
);
VOS_UINT32 PPPC_EAP_AKA_AttRandParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttAutnParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttPaddingParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttPermanentParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttMacParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNotificationParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttAnyParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttFullauthParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttCounterParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNonceSParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttKdfInputParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttKdfParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttIvParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttEncrParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNextPseudonymParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttNextReauthParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttCheckcodeParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttResultParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_UINT32 PPPC_EAP_AKA_AttBiddingParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker);
VOS_VOID PPPC_EAP_AKA_ReciveAuthRes
(
    PPPC_EAP_AUTH_RESULT_STRU           *pstResult
);
PS_BOOL_ENUM_UINT8 PPPC_EAP_AKA_PreProcessPkt
(
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



