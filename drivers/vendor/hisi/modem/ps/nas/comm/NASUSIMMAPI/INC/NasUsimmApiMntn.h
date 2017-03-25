/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasUsimmApiMntn.h
  �� �� ��   : ����
  ��    ��   : s00217060
  ��������   : 2013��6��5��
  ����޸�   :
  ��������   : NasUsimmApiMntn.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NAS_USIMM_API_MNTN_H__
#define __NAS_USIMM_API_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "siappstk.h"
#include "UsimPsInterface.h"
#include "siapppb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_USIMM_AUTN_RANDLEN          (17)
#define NAS_USIMM_AUTN_AUTHLEN          (17)
#define NAS_USIMM_AUTH_RAND_LENGTH      (16)
#define NAS_USIMM_AUTH_AUTN_LENGTH      (16)
#define NAS_MO_CTRL_LAI_LEN             (0xf)
#define NAS_USSD_STR_MAX_LEN            (256)
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
#define NAS_MAX_USIM_FILE_MAX_RECORD    (255)
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_USIMM_API_MNTN_MSG_ID_ENUM
 �ṹ˵��  : NAS���͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : NAS���͸�OM�Ŀ�ά�ɲ���ϢIDö��
  2.��    ��   : 2013��8��29��
    ��    ��   : f62575
    �޸�����   : VSIM FEATURE
  3.��    ��   : 2014��5��12��
    ��    ��   : W00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
*****************************************************************************/
enum NAS_USIMM_API_MNTN_MSG_ID_ENUM
{
    NAS_LOG_USIMM_API_SET_FILE_REQ                       = 0x2000, /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_SET_FILE_REQ_STRU */
    NAS_LOG_USIMM_API_GET_FILE_REQ                               , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_FILE_REQ_STRU */
    NAS_LOG_USIMM_API_AUTH_REQ                                   , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_AUTH_REQ_STRU */
    NAS_LOG_USIMM_API_PIN_REQ                                    , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_PIN_REQ_STRU */
    NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ                       , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU*/
    NAS_LOG_USIMM_API_IS_TEST_CARD                               , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_IS_TEST_CARD_STRU */
    NAS_LOG_USIMM_API_GET_PIN_STATUS                             , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU */
    NAS_LOG_USIMM_API_GET_CARD_TYPE                              , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU */
    NAS_LOG_USIMM_API_GET_CACHED_FILE                            , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU */
    NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE                       , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU */
    NAS_LOG_USIMM_API_GET_CARD_IMSI                              , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU */
    NAS_LOG_USIMM_API_BDN_QUERY                                  , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_BDN_QUERY_STRU */
    NAS_LOG_USIMM_API_FDN_QUERY                                  , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_FDN_QUERY_STRU */
    NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME                        , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU */
    NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ                          , /*_H2ASN_MsgChoice NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU */
    NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND                     , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU */
    NAS_LOG_PIH_API_DEREG_USIM_CARD_STATUS_IND                   , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU*/
    NAS_LOG_PIH_API_REG_CARD_REFRESH_IND                         , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU */
    NAS_LOG_PIH_API_DEREG_CARD_REFRESH_IND                       , /*_H2ASN_MsgChoice NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU */
    NAS_LOG_PB_API_GET_ECC_NUM                                   , /*_H2ASN_MsgChoice NAS_LOG_PB_API_GET_ECC_NUMBER_STRU */
    NAS_LOG_STK_API_MT_CALL_EVENT                                , /*_H2ASN_MsgChoice NAS_LOG_STK_API_MT_CALL_CALL_EVENT_STRU */
    NAS_LOG_STK_API_CALL_CONNECT_EVENT                           , /*_H2ASN_MsgChoice NAS_LOG_STK_API_CALL_CONNECT_EVENT_STRU */
    NAS_LOG_STK_API_CALL_DISCONNECT_EVENT                        , /*_H2ASN_MsgChoice NAS_LOG_STK_API_CALL_DISCONNECT_EVENT_STRU*/
    NAS_LOG_STK_API_LOCI_EVENT                                   , /*_H2ASN_MsgChoice NAS_LOG_STK_API_LOCIS_EVENT_STRU */
    NAS_LOG_STK_API_ACC_CHANGE_EVENT                             , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ACC_CHANGE_EVENT_STRU*/
    NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT                      , /*_H2ASN_MsgChoice NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT_STRU */
    NAS_LOG_PB_API_FDN_NUM_CHECK                                 , /*_H2ASN_MsgChoice NAS_LOG_PB_API_FDN_NUM_CHECK_STRU */
    NAS_LOG_STK_API_ENVELOP_RSP_DECODE                           , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU */
    NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE                        , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU */
    NAS_LOG_STK_API_ENVELOP_DOWNLOAD                             , /*_H2ASN_MsgChoice NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU */
    NAS_LOG_STK_API_CC_RESULT_IND                                , /*_H2ASN_MsgChoice NAS_LOG_STK_API_CC_RESULT_IND_STRU */
    NAS_LOG_STK_API_SMS_CTRL_RESULT_IND                          , /*_H2ASN_MsgChoice NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU */
    NAS_LOG_VSIM_CTRL_INFO                                       , /*_H2ASN_MsgChoice TAF_SDC_VSIM_CTRL_INFO_STRU */
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
    NAS_LOG_PB_API_QRY_ECALL_NUM                                 , /*_H2ASN_MsgChoice NAS_LOG_PB_API_QRY_ECALL_NUM_STRU */
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */
    NAS_LOG_STK_API_ENVELOP_DOWN_CODE                            ,
    NAS_LOG_PB_API_GET_XECC_NUM                                  ,

    NAS_LOG_USIMM_API_BUTT
};
typedef VOS_UINT32 NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_USIMM_API_TYPE_ENUM
 �ṹ˵��  : NAS����USIMM��API������
  1.��    ��   : 2013��6��5��
    ��    ��   : s00217060
    �޸�����   : NAS����USIMM��API������ö��
*****************************************************************************/
enum NAS_USIMM_API_TYPE_ENUM
{
    NAS_USIMM_API_TYPE_WITH_INSTANCE,                                           /* ���ô�INSTANCE��API */
    NAS_USIMM_API_TYPE_WITHOUT_INSTANCE,                                        /* ���ò���INSTANCE��API */
    NAS_USIMM_API_TYPE_BUTT
};
typedef VOS_UINT8 NAS_USIMM_API_TYPE_ENUM_UINT8;

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
 �ṹ��    : NAS_LOG_VSIM_CTRL_INFO_STRU
 �ṹ˵��  : VSIM���Բ���������Ϣ�ṹ�����У�
             ulVsimModem��־�Ƿ�VSIM MODEM
             ucVsimCtrlFlg��־NAS��VSIM���Կ���״̬��0:���Թر�,1:���Դ�
 1.��    ��   : 2013��8��29��
   ��    ��   : f62575
   �޸�����   : VSIM FEATURE
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulVsimModem;
    VOS_UINT8                           ucVsimCtrlFlg;
    VOS_UINT8                           aucReserved1[3];
}NAS_LOG_VSIM_CTRL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_PIN_STATUS_STRU
 �ṹ˵��  : PIN״̬�ṹ��

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPinType;                              /* PIN���� */
    VOS_UINT8                           ucPinBeEnable;                          /* PIN�Ƿ��� */
    VOS_UINT8                           ucPinBeNeed;                            /* PIN�Ƿ���Ҫ */
    VOS_UINT8                           ucPinRemainNum;                         /* PINʣ����� */
}NAS_PIN_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_SET_FILE_REQ_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_SetFileReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           aucContent[3];
}NAS_LOG_USIMM_API_SET_FILE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_MaxEFRecordNumReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usEfId;
    VOS_UINT16                          usRev;
}NAS_LOG_USIMM_API_MAX_EFRECORD_NUM_REQ_STRU;



/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_GET_FILE_REQ_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_GetFileReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           ucReserved;
}NAS_LOG_USIMM_API_GET_FILE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_AUTH_REQ_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_AuthReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserved[3];
    USIMM_AUTH_TYPE_ENUM_UINT32         enChallengeType;
    VOS_UINT8                           aucRand[NAS_USIMM_AUTN_RANDLEN];
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT8                           aucAUTN[NAS_USIMM_AUTN_AUTHLEN];
    VOS_UINT8                           aucReserved2[3];
}NAS_LOG_USIMM_API_AUTH_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_GetPinStatus�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    NAS_PIN_STATUS_STRU                 stPinStatus;
}NAS_LOG_USIMM_API_GET_PIN_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_GetCardType�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           ucCardStatus;
    VOS_UINT16                          usCardType;
}NAS_LOG_USIMM_API_GET_CARD_TYPE_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_BDN_QUERY_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_BdnQuery�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulUsimState;
    VOS_UINT32                          ulCsimState;
}NAS_LOG_USIMM_API_BDN_QUERY_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_GetPinRemainTime�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    USIMM_PIN_REMAIN_STRU               stRemainTime;
}NAS_LOG_USIMM_API_GET_PIN_REMAIN_TIME_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_PIH_REG_USIM_CARD_STATUS_IND_STRU
 �ṹ˵��  : ����NAS_PIHAPI_RegUsimCardStatusIndMsg�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRegPID;
}NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_IS_TEST_CARD_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_IsTestCard�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
}NAS_LOG_USIMM_API_IS_TEST_CARD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_PIN_INFO_STRU
 �ṹ˵��  : pin��Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    USIMM_PIN_CMD_TYPE_ENUM_UINT32      enCmdType;
    USIMM_PIN_TYPE_ENUM_UINT32          enPINType;
    VOS_UINT8                           aucOldPIN[USIMM_PINNUMBER_LEN];
    VOS_UINT8                           aucNewPIN[USIMM_PINNUMBER_LEN];
}NAS_LOG_USIMM_PIN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_PIN_REQ_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_PinReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    NAS_LOG_USIMM_PIN_INFO_STRU         stPinInfo;
}NAS_LOG_USIMM_API_PIN_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_GetCachedFile�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucRsv[3];
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT16                          usFileID;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucContent[4];
}NAS_LOG_USIMM_API_GET_CACHED_FILE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_CACHED_FILE_INFO_STRU
 �ṹ˵��  : cache file��Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : s00217060
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFileID;
    VOS_UINT32                          ulDataLen;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT8                           aucContent[4];
}NAS_LOG_CACHED_FILE_INFO_STRU;


typedef NAS_LOG_USIMM_API_BDN_QUERY_STRU                NAS_LOG_USIMM_API_FDN_QUERY_STRU;
typedef NAS_LOG_PIH_API_REG_USIM_CARD_STATUS_IND_STRU   NAS_LOG_PIH_DEREG_USIM_CARD_STATUS_IND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_PIH_REG_CARD_REFRESH_IND_STRU
 �ṹ˵��  : ����NAS_PIHAPI_RegCardRefreshIndMsg�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRegPID;
}NAS_LOG_PIH_API_REG_CARD_REFRESH_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_PIH_DEREG_CARD_REFERESH_IND_STRU
 �ṹ˵��  : ����NAS_PIHAPI_DeregCardRefreshIndMsg�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulDeregPID;
}NAS_LOG_PIH_API_DEREG_CARD_REFERESH_IND_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_PB_API_GET_ECC_NUMBER_STRU
 �ṹ˵��  : ����NAS_PBAPI_GetEccNumber�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_PB_ECC_DATA_STRU                 stEccData;
}NAS_LOG_PB_API_GET_ECC_NUMBER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_PB_API_GET_XECC_NUMBER_STRU
 �ṹ˵��  : ����NAS_PBAPI_GetXeccNumber�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��07��28��
   ��    ��   : h00313353
   �޸�����   : ����

*****************************************************************************/
typedef NAS_LOG_PB_API_GET_ECC_NUMBER_STRU NAS_LOG_PB_API_GET_XECC_NUMBER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_MT_CALL_CALL_EVENT_STRU
 �ṹ˵��  : ����NAS_LogStkApiMtCallEvent�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_MT_CALL_EVENT_STRU           stCallEvent;
}NAS_LOG_STK_API_MT_CALL_CALL_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_CALL_CONNECT_EVENT_STRU
 �ṹ˵��  : ����NAS_STKAPI_CallConnectEvent�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           ucSDId;
    VOS_UINT8                           aucReserve[2];
    SI_STK_CALL_CONNECTED_EVENT_STRU    stCallConnectedEvent;
}NAS_LOG_STK_API_CALL_CONNECT_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_CALL_DISCONNECT_EVENT_STRU
 �ṹ˵��  : ����NAS_STKAPI_CallDisconnect�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           ucSDId;
    VOS_UINT8                           aucReserve[2];
    SI_STK_CALL_DISCONNECTED_EVENT_STRU stCallDisconnectedEvent;
}NAS_LOG_STK_API_CALL_DISCONNECT_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_LOCIS_EVENT_STRU
 �ṹ˵��  : ����NAS_STKAPI_LociSEvent�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
}NAS_LOG_STK_API_LOCIS_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_ACC_CHANGE_EVENT_STRU
 �ṹ˵��  : ����NAS_STKAPI_AccTChangeEvent�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;
    NAS_USIMM_API_TYPE_ENUM_UINT8                           enApiType;
    VOS_UINT8                                               aucReserve[3];
    SI_STK_ACCESS_TECHNOLOGY_CHANGE_EVENT_STRU              stSTKAccTCHangeEvent;
}NAS_LOG_STK_API_ACC_CHANGE_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT_STRU
 �ṹ˵��  : ����NAS_STKAPI_NetSearchChgEvent�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8                           enApiType;
    VOS_UINT8                                               aucReserve[3];
    SI_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT_STRU            stNetSearchModeEvent;
}NAS_LOG_STK_API_NET_SEARCH_CHANGE_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_GetCardIMSI�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;        /* ��Ϣͷ */        /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8                           enApiType;
    VOS_UINT8                                               aucReserve1[3];
    VOS_UINT32                                              ulRslt;
    VOS_UINT8                                               aucImsi[USIMM_EF_IMSI_LEN];
    VOS_UINT8                                               aucReserv2[3];
}NAS_LOG_USIMM_API_GET_CARD_IMSI_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_IsServiceAvailable�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��06��
   ��    ��   : z00161729
   �޸�����   : ����
 2.��    ��   : 2013��07��29��
   ��    ��   : y00245242
   �޸�����   : VOLTE�����������µ�USIM�ӿ�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    UICC_SERVICES_TYPE_ENUM_UINT32      enService;
    VOS_UINT32                          ulRslt;
}NAS_LOG_USIMM_API_IS_SERVICE_AVAILABLE_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_PB_API_FDN_NUM_CHECK_STRU
 �ṹ˵��  : ����NAS_PBAPI_FdnNumCheck�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��06��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_PB_FDN_NUM_STRU                  stFdnNum;
}NAS_LOG_PB_API_FDN_NUM_CHECK_STRU;


/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
/*****************************************************************************
 �ṹ��    : NAS_LOG_PB_API_QRY_ECALL_NUM_STRU
 �ṹ˵��  : ����NAS_PBAPI_QryECallNumber�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2014��05��12��
   ��    ��   : w00176964
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucRsv[3];
    SI_PB_STORATE_TYPE                  enPbType;
    VOS_UINT8                           ucListLen;
    VOS_UINT8                           aucList[NAS_MAX_USIM_FILE_MAX_RECORD];
}NAS_LOG_PB_API_QRY_ECALL_NUM_STRU;
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU
 �ṹ˵��  : ����NAS_STKAPI_EnvelopeRspDataFree�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��06��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_ENVELOPE_RSP_STRU            stEvelopRsp;
}NAS_LOG_STK_API_ENVELOP_RSP_DATA_FREE_STRU;


/*****************************************************************************
 �ṹ��    : NAS_CALL_CTRL_SPECIAL_STRU
 �ṹ˵��  : CALL CTRL����ṹ���е�special data��Ϣ�ṹ��

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTag;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           aucRsv[2];
    VOS_UINT8                           aucSpecialData[NAS_USSD_STR_MAX_LEN];
}NAS_CALL_CTRL_SPECIAL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOCATION_INFO_STRU
 �ṹ˵��  : CALL CTRL����ṹ���е�LAC��Ϣ�ṹ��

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucATSLI[NAS_MO_CTRL_LAI_LEN];
    VOS_UINT8                           aucRsv[3];
}NAS_LOCATION_INFO_STRU;


/*****************************************************************************
 �ṹ��    : NAS_CALL_CONTROL_STRU
 �ṹ˵��  : CALL CTRL�ṹ��

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          OP_Capability1:1;
    VOS_UINT32                          OP_Subaddr:1;
    VOS_UINT32                          OP_LocInfo:1;
    VOS_UINT32                          OP_Capability2:1;
    VOS_UINT32                          OP_BCRepInd:1;
    VOS_UINT32                          OP_SepcialData:1;
    VOS_UINT32                          OP_Reserved:26;

    NAS_LOCATION_INFO_STRU              stLocInfo;
    NAS_CALL_CTRL_SPECIAL_STRU          stSpecialData;
}NAS_CALL_CONTROL_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU
 �ṹ˵��  : ����NAS_STKAPI_EnvelopeDownload�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��06��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulSendPara;
    NAS_CALL_CONTROL_STRU               stCallCtrl;
    SI_STK_ENVELOPE_TYPE_UINT32         enEnvelopeType;
    SI_STK_DEVICE_IDENTITIES_STRU       stDeviceId;
    VOS_UINT8                           aucData[SI_STK_DATA_MAX_LEN];
}NAS_LOG_STK_API_ENVELOP_DOWNLOAD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CALL_CTRL_RSP_STRU
 �ṹ˵��  : CALL CTRL�ظ��ṹ��

 �޸ļ�¼  :
 1.��    ��   : 2013��06��17��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          OP_CCP1:1;
    VOS_UINT32                          OP_SubAddr:1;
    VOS_UINT32                          OP_Alaph:1;
    VOS_UINT32                          OP_BCRepInd:1;
    VOS_UINT32                          OP_CCP2:1;
    VOS_UINT32                          OP_SepcialData:1;
    VOS_UINT32                          OP_Reserved:26;

    NAS_CALL_CTRL_SPECIAL_STRU          stSpecialData;
}NAS_CALL_CTRL_RSP_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU
 �ṹ˵��  : ����NAS_STKAPI_EnvelopeRsp_Decode�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��06��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    NAS_CALL_CTRL_RSP_STRU              stCallCtrlRslt;
    SI_STK_ENVELOPE_TYPE_UINT32         enEnvelopeType;
    VOS_UINT32                          ulResult;
}NAS_LOG_STK_API_ENVELOP_RSP_DECODE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU
 �ṹ˵��  : ����SI_STK_EnvelopeData_Code�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��02��17��
   ��    ��   : h00313353
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucEvent[256];
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulOffSet;
}NAS_LOG_STK_API_ENVELOP_DOWN_CODE_STRU;


/*****************************************************************************
 �ṹ��    : NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU
 �ṹ˵��  : ����NAS_USIMMAPI_DeactiveCardReq�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��08��
   ��    ��   : z00161729
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
}NAS_LOG_USIMM_API_DEACTIVE_CARD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_CC_RESULT_IND_STRU
 �ṹ˵��  : ����NAS_STKAPI_CCResultInd�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��13��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_ENVELOPE_RSP_STRU            stRspData;
}NAS_LOG_STK_API_CC_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU
 �ṹ˵��  : ����NAS_STKAPI_SMSCtrlResultInd�ӿڣ�����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��13��
   ��    ��   : w00242748
   �޸�����   : ����

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType;
    VOS_UINT8                           aucReserve[3];
    SI_STK_ENVELOPE_RSP_STRU            stRspData;
}NAS_LOG_STK_API_SMS_CTRL_RESULT_IND_STRU;
/*****************************************************************************
 �ṹ��    : NAS_USIMM_GETFILE_INFO_STRU
 �ṹ˵��  : ��ȡ�ļ�

 1.��    ��   : 2015��02��03��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
}NAS_USIMM_MNTN_GETFILE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_USIMM_GETFILE_INFO_STRU
 �ṹ˵��  : ��ȡ�ļ�

 1.��    ��   : 2015��02��03��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32   enAppType;      /* Ӧ������ */
    VOS_UINT16                  usEfId;         /* �ļ�ID */
    VOS_UINT8                   ucRecordNum;    /* �ļ���¼�ţ��������ļ���0 */
    VOS_UINT8                   ucRsv;          /* ���� */
    VOS_UINT32                  ulEfLen;        /* �������ݳ��� */
    VOS_UINT8                  *pucEfContent;   /* ������������ */
}NAS_USIMM_MNTN_SETFILE_INFO_STRU;

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
    NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32      enMsgId;                         /* _H2ASN_MsgChoice_Export NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_USIMM_API_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} NAS_USIMM_API_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    NAS_USIMM_API_MNTN_MSG_DATA         stMsgData;
} NasUsimmApiMntn_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID *pMsg);

VOS_VOID  NAS_LogUsimmApiSetFileReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_USIMM_MNTN_SETFILE_INFO_STRU   *pstSetFileInfo
);
VOS_VOID  NAS_LogUsimmApiGetFileReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_USIMM_MNTN_GETFILE_INFO_STRU   *pstGetFileInfo
);
VOS_VOID  NAS_LogUsimmApiAuthReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                           ucChallengeType,
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn
);
VOS_VOID  NAS_LogUsimmApiPinReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_LOG_USIMM_PIN_INFO_STRU        *pstPinInfo
);
VOS_VOID  NAS_LogUsimmApiMaxEFRecordNumReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
);
VOS_VOID  NAS_LogUsimmApiIsTestCard(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);
VOS_VOID  NAS_LogUsimmApiGetPinStatus(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    NAS_PIN_STATUS_STRU                *pstPinStatus
);

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
VOS_VOID  NAS_LogUsimmApiIsServiceAvailable(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    UICC_SERVICES_TYPE_ENUM_UINT32      enService
);
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */


VOS_VOID  NAS_LogUsimmApiGetCachedFile(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                         **ppucData
);
VOS_VOID  NAS_LogUsimmApiGetCardIMSI(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                          *pucImsi
);

VOS_VOID  NAS_LogUsimmApiGetCardType(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                           ucCardStatus,
    VOS_UINT16                          ucCardType
);

VOS_VOID  NAS_LogUsimmApiBdnQuery(
    VOS_UINT32                          ulState,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);
VOS_VOID  NAS_LogUsimmApiFdnQuery(
    VOS_UINT32                          ulUsimState,
    VOS_UINT32                          ulCsimState,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);

VOS_VOID  NAS_LogUsimmApiGetPinRemainTime(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    USIMM_PIN_REMAIN_STRU              *pstRemainTime
);
VOS_VOID  NAS_LogPihApiRegUsimCardStatusInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulRegPid
);

VOS_VOID  NAS_LogPihApiDeregUsimCardStatusInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDeregId
);

VOS_VOID  NAS_LogPihApiRegCardRefreshInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulRegId
);

VOS_VOID  NAS_LogPihApiDeregCardRefreshInd(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulDeregPID
);

VOS_VOID  NAS_LogPbApiGetEccNumber(
    VOS_UINT32                           ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_ECC_DATA_STRU                *pstEccData
);

/* Deleted by l00208543 for V9R1 STK����, 2013-7-13, begin */
/* Deleted by l00208543 for V9R1 STK����, 2013-7-13, end */

VOS_VOID  NAS_LogPbApiGetXeccNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_ECC_DATA_STRU                *pstEccData
);

VOS_VOID  NAS_LogPbApiFdnNumCheck(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_FDN_NUM_STRU                 *pstFdnNum
);

VOS_VOID  NAS_LogStkApiEnvelopRspDecode(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstEnvelopeRsp
);

VOS_VOID  NAS_LogStkApiEnvelopReqCode(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT8                          *pucEvent,
    VOS_UINT32                          ulDataLen,
    VOS_UINT32                          ulOffSet
);

VOS_VOID  NAS_LogStkApiEnvelopRspDataFree(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstEnvelopeRsp
);

VOS_VOID  NAS_LogStkApiEnvelopDownload(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
);

VOS_VOID  NAS_LogUsimmApiDeactiveCardReq(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType
);

VOS_VOID  NAS_LogSTKApiCCResultInd(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
);


VOS_VOID  NAS_LogSTKApiSMSCtrlResultInd(
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
);

VOS_VOID NAS_LogVsimIsRequireVsimCtrl(
    VOS_UINT32                          ulVsimModem,
    VOS_UINT8                           ucVsimCtrlFlg
);

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
VOS_VOID  NAS_LogPbApiQryEcallNumber(
    VOS_UINT32                          ulRslt,
    NAS_USIMM_API_TYPE_ENUM_UINT8       enApiType,
    SI_PB_STORATE_TYPE                  enPbType,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
);
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */

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

#endif /* end of TafSpmMntn.h */

