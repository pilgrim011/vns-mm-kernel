

#ifndef __LCSLPPINTERFACE_H__
#define __LCSLPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "LocCommonInterface.h"



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 Macro
*****************************************************************************/
#define PS_MSG_ID_LCS_TO_LPP_BASE 0
#define PS_MSG_ID_LPP_TO_LCS_BASE 100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : LCS_LPP_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LCS��LPP֮�����Ϣö��
*****************************************************************************/
enum    LCS_LPP_MSG_ID_ENUM
{
    /* LCS����LPP����Ϣԭ�� */
    ID_LCS_LPP_GNSS_ASSISTDATA_CNF      = 0x01+PS_MSG_ID_LCS_TO_LPP_BASE,       /* _H2ASN_MsgChoice LCS_LPP_GNSS_ASSISTDATA_CNF_STRU */
    ID_LCS_LPP_LOCATION_INFO_NTF        = 0x02+PS_MSG_ID_LCS_TO_LPP_BASE,       /* _H2ASN_MsgChoice LCS_LPP_LOCATION_INFO_NTF_STRU */

    /* LPP���͸�LCS����Ϣԭ��*/
    ID_LPP_LCS_GNSS_ASSISTDATA_REQ      = 0x01+PS_MSG_ID_LPP_TO_LCS_BASE,       /* _H2ASN_MsgChoice LPP_LCS_GNSS_ASSISTDATA_REQ_STRU */

    ID_LCS_LPP_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LCS_LPP_MSG_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : LCS_LPP_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LCS��LPP֮��Ľ������
*****************************************************************************/
enum    LCS_LPP_RSLT_ENUM
{
    LCS_LPP_RSLT_SUCC                   = 0,
    LCS_LPP_RSLT_FAIL                   = 1,

    LCS_LPP_RSLT_BUTT
};
typedef VOS_UINT32 LCS_LPP_RSLT_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ����: LPP_LCS_GNSS_ASSISTDATA_REQ_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��: LPP����LCS��ȡGNSS��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulLppMsgSize;
    VOS_UINT8                           aucLppMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ����� */
}LPP_LCS_GNSS_ASSISTDATA_REQ_STRU;

/*****************************************************************************
 �ṹ����: LCS_LPP_GNSS_ASSISTDATA_CNF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    LCS_LPP_RSLT_ENUM_UINT32            enRslt;
}LCS_LPP_GNSS_ASSISTDATA_CNF_STRU;

/*****************************************************************************
 �ṹ����: LCS_LPP_LOCATION_INFO_NTF_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpLocationEstimate   :1;
    VOS_UINT32                          bitOpVelocityEstimate   :1;
    VOS_UINT32                          bitOpSpare              :30;
    LOC_COM_COORDINATE_STRU             stLocationEstimate;             /* λ����Ϣ */
    LOC_COM_VELOCITY_STRU               stVelocityEstimate;             /* �ٶ���Ϣ */
}LCS_LPP_LOCATION_INFO_NTF_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


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

#endif /* end of LcsLppInterface.h */


