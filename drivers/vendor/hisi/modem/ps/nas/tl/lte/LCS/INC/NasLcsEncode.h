


#ifndef __NASLCSENCODE_H__
#define __NASLCSENCODE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLcsDecode.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_LCS_NW_MSG_MAX_LEN                (1024)
#define NAS_LCS_VERIFICATION_RSP_TAG          (0x80)
#define NAS_LCS_MOLR_TYPE_TAG                 (0x80)
#define NAS_LCS_MOLR_LOC_METHOD_TAG           (0x81)
#define NAS_LCS_MOLR_QOS_TAG                  (0xA2)
#define NAS_LCS_CLIENT_EXT_ID_TAG             (0xA3)
#define NAS_LCS_SUPP_GAD_SHAPES_TAG           (0x86)
#define NAS_LCS_MOLR_MULI_POS_PROTOC_PDUS_TAG (0xB5)
#define NAS_LCS_MOLR_QOS_HOR_ACC_TAG          (0x80)
#define NAS_LCS_MOLR_QOS_VER_REQ_TAG          (0x81)
#define NAS_LCS_MOLR_QOS_VER_ACC_TAG          (0x82)
#define NAS_LCS_MOLR_QOS_VEL_REQ_TAG          (0x85)
#define NAS_LCS_CLIENT_EXT_ID_ADDR_TAG        (0x80)
#define NAS_LCS_PROTOCOL_DISCRIMINATOR        (0x0B)
#define NAS_LCS_MOLR_POS_PDUS_MAX_NUM         (3)
#define NAS_LCS_MOLR_POS_PDU_MAX_LEN          (240)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 �ṹ����: NAS_LCS_MOLR_TYPE_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: �տڱ�����mo-lr����ö��
*****************************************************************************/
enum NAS_LCS_MOLR_TYPE_ENUM
{
    NAS_LCS_MOLR_LOCATION_ESTIMATE           = 0,
    NAS_LCS_MOLR_ASSISTANCE_DATA             = 1,
    NAS_LCS_MOLR_DECIPHER_KEYS               = 2,
    NAS_LCS_MOLR_DEFER_TTTP_INIT             = 3,
    NAS_LCS_MOLR_DEFER_SELF_LOC_INIT         = 4,
    NAS_LCS_MOLR_TTTP_LOC_ESTIMATE           = 5,
    NAS_LCS_MOLR_CANCELLATION                = 6,

    NAS_LCS_MOLR_TYPE_BUTT
};
typedef VOS_UINT8 NAS_LCS_MOLR_TYPE_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_NW_MOLR_METHOD_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: �տڱ�����locationMethodö��, TAF��Ϣ��Я����Method��Ҫת��
*****************************************************************************/
enum NAS_LCS_NW_MOLR_METHOD_ENUM
{
    NAS_LCS_NW_MOLR_METHOD_EOTD              = 0,       /* msBasedEOTD */
    NAS_LCS_NW_MOLR_METHOD_AEOTD             = 1,       /* msAssistedEOTD */
    NAS_LCS_NW_MOLR_METHOD_AGPS              = 2,       /* assistedGPS */
    NAS_LCS_NW_MOLR_METHOD_OTDOA             = 3,       /* msBasedOTDOA */
    NAS_LCS_NW_MOLR_METHOD_AGANSS            = 4,       /* assistedGANSS */
    NAS_LCS_NW_MOLR_METHOD_AGPS_GANSS        = 5,       /* assistedGPSandGANSS */

    NAS_LCS_NW_MOLR_METHOD_BUTT
};
typedef VOS_UINT8 NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8;

/*****************************************************************************
 �ṹ����: NAS_LCS_VER_RSP_ENUM
 Э����:
 ASN.1 ����:
 �ṹ˵��: �տڱ�����verificationResponseö��, TAF��Ϣ��Я����RSP��Ҫת��
*****************************************************************************/
enum NAS_LCS_VER_RSP_ENUM
{
    NAS_LCS_VER_RSP_PERMISSON_DENIED          = 0,
    NAS_LCS_VER_RSP_PERMISSON_GRANTED         = 1,

    NAS_LCS_VER_RSP_BUTT
};
typedef VOS_UINT8 NAS_LCS_VER_RSP_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ����: NAS_LCS_POS_PDU_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����ǰPDU�ṹ,ÿ����������Ϣ��Ϣ�������Ϊ240
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucPduLen;
    VOS_UINT8                       *pucPdu;
}NAS_LCS_POS_PDU_STRU;
/*****************************************************************************
 �ṹ����: NAS_LCS_POS_PDUS_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: ����ǰPOS PDUS�ṹ,LCS���Я��3����������Ϣ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucPduNum;
    VOS_UINT8                       aucRsv[3];
    NAS_LCS_POS_PDU_STRU            astPosPdu[NAS_LCS_MOLR_POS_PDUS_MAX_NUM];
}NAS_LCS_POS_PDUS_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRelComplete
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRegister
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enMsgType,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRelCmpIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocNtfRsp
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeVerifyRsp
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
);
extern NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_PackTL
(
    VOS_UINT8                           ucTag,
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusCodeLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_EncodeLength
(
    VOS_UINT16                          usSrcLen,
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT8                           *pucCodeLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRegisterIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeAssDataMoLrReq
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDUS_STRU               *pstPosPdus
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeMuliPosPDUS
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDUS_STRU               *pstPosPdus
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodePosPDU
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDU_STRU                *pstPosPdu
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocEstimateMoLrReq
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeSuppGADShapes
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeClentExtId
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLcsQos
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
);
extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeMolrType
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_MOLR_TYPE_ENUM_UINT8         enMolrType
);
extern VOS_VOID NAS_LCS_EncodeLocationMethod
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_METHOD_ENUM_UINT8           enMethod
);

extern NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
);
extern NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8 NAS_LCS_MapLocationMethod(LCS_MOLR_METHOD_ENUM_UINT8  enMethod);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif











































