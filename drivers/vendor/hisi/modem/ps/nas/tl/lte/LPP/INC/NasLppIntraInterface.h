

#ifndef __NASLPPINTRAINTERFACE_H__
#define __NASLPPINTRAINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"
#include    "NasLppPublic.h"
#include    "LppMtaInterface.h"
#include    "v_typdef.h"
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/


#define LPP_INTRA_MSG_HDR  0

/*��װдLPP DL��Ϣͷ�ĺ�*/
#define NAS_ETC_WRITE_LPP_MSG_HEAD(pstMsg, ulLppMsgID)\
                    (pstMsg)->enMsgName         = (ulLppMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_LPP;


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : ETC_LPP_MSG_TYPE_ENUM
 ö��˵��  : ETC��LPP��Ϣ����
 ����      : lifuxin 00253982 2015-09-01 �¿���
*****************************************************************************/
enum NAS_LPP_INTRA_MSG_ID_ENUM
{
    ID_NAS_LPP_INTRA_DATA_CNF           = 0,    /* _H2ASN_MsgChoice NAS_LPP_INTRA_DATA_CNF_STRU */

    ID_NAS_LPP_INTRA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LPP_INTRA_MSG_ID_ENUM_UINT32;

/*******************************************************************************
  �ṹ��    :NAS_LPP_INTRA_DATA_CNF_STRU
  �ṹ˵��  :
  1.��    ��   : 2015��07��06��
    ��    ��   : Xiaojun
    �޸�����   : Added for LPP
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    NAS_LPP_INTRA_MSG_ID_ENUM_UINT32    ulMsgId;                /*_H2ASN_Skip*//* ��Ϣ ID */

    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;
    /*enRslt=NAS_LPP_CONN_MANAGE_FAILʱ����Я��stLppMsgIdentiy���������ڽ��е�transaction�����̶�����*/
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enRslt;
    VOS_UINT32                          ulOpId;
}NAS_LPP_INTRA_DATA_CNF_STRU;


/*****************************************************************************
 5. STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : ETC_LPP_RESET_POSTION_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ETC��LPP֮��ĸ�λ������Ϣ���߼�
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    NAS_LPP_INTRA_MSG_ID_ENUM_UINT32    ulMsgId;                /*_H2ASN_Skip*//* ��Ϣ ID */

    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity;
    VOS_UINT8                           aucMsgData[4];          /* ������Ϣ�洢 */
}NAS_LPP_INTRA_MSG_STRU;

typedef struct
{
    NAS_LPP_INTRA_MSG_ID_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export NAS_LPP_INTRA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_LPP_INTRA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}LPP_INTRA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    LPP_INTRA_MSG_DATA                     stMsgData;
}LppIntraInterface_MSG;


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

#endif /* end of EmmLppInterface.h */





