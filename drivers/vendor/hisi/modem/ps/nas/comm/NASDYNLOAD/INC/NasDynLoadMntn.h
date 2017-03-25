/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasDynLoadMntn.h
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2015��8��27��
  ����޸�   :
  ��������   : NasDynLoadMntn.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��27��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NAS_DYNLOAD_MNTN_H__
#define __NAS_DYNLOAD_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "NasDynLoad.h"
#include "VosPidDef.h"
#include "NasMsccMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_DYNLOAD_SoftReboot(pstNasRebootInfo) NAS_Dynload_SoftReBoot_WithLineNoAndFileID( (__LINE__), (THIS_FILE_ID), (pstNasRebootInfo))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_DYNLOAD_MNTN_MSG_ID_ENUM
 �ṹ˵��  : NAS���͸�OM�Ŀ�ά�ɲ���Ϣ
  1.��    ��   : 2015��8��27��
    ��    ��   : w00242748
    �޸�����   : NAS���͸�OM�Ŀ�ά�ɲ���ϢIDö��
*****************************************************************************/
enum NAS_DYNLOAD_MNTN_MSG_ID_ENUM
{
    NAS_DYNLOAD_MNTN_MSG_REGISTER                       = ID_NAS_MSCC_MNTN_DYNLOAD_MSG_BASE, /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU */
    NAS_DYNLOAD_MNTN_MSG_DEREGISTER                             , /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU */
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT                            , /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU */
    NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD                          , /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU */
    NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD                         ,  /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU */
    NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD                        ,  /*_H2ASN_MsgChoice NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU */

    NAS_DYNLOAD_MNTN_MSG_BUTT
};
typedef VOS_UINT32 NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32;




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
 �ṹ��    : NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU
 �ṹ˵��  : ��ȡ��̬����ģ����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulInit;
    VOS_UINT32                          ulUnload;
}NAS_DYNLOAD_MNTN_MSG_REGISTER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU
 �ṹ˵��  : ��ȡ��̬����ģ����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
}NAS_DYNLOAD_MNTN_MSG_DEREGISTER_STRU;

/*****************************************************************************
 �ṹ��    : NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU
 �ṹ˵��  : ��ȡ��̬����ģ����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2013��06��05��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    NAS_DYNLOAD_CB_RAT_INFO_STRU        astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulInit;
}NAS_DYNLOAD_MNTN_MSG_EXCUTE_INIT_STRU;

/*****************************************************************************
 �ṹ��    : NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU
 �ṹ˵��  : ��ȡ��̬����ģ����Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��08��31��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    NAS_DYNLOAD_CB_RAT_INFO_STRU        astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
    VOS_RATMODE_ENUM_UINT32             enRatType;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          ulUnload;
}NAS_DYNLOAD_MNTN_MSG_EXCUTE_UNLOAD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_DYNLOAD_MNTN_MSG_START_MRV_LOAD_STRU
 �ṹ˵��  : ��ȡ��ʼ���õ���API��Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��08��31��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
}NAS_DYNLOAD_MNTN_MSG_START_DRV_LOAD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_DYNLOAD_MNTN_MSG_START_MRV_LOAD_STRU
 �ṹ˵��  : ��ȡ�������õ���API��Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��08��31��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 enMsgId;
    VOS_INT32                           lLoadResult;
    NAS_DYNLOAD_CB_RAT_INFO_STRU        astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
}NAS_DYNLOAD_MNTN_MSG_FINISH_DRV_LOAD_STRU;

/*****************************************************************************
 �ṹ��    : NAS_DYNLOAD_REBOOT_INFO_STRU
 �ṹ˵��  : ��̬���ظ�λ��Ϣ

 �޸ļ�¼  :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
}NAS_DYNLOAD_REBOOT_INFO_STRU;


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
    NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32                     enMsgId;                         /* _H2ASN_MsgChoice_Export NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_DYNLOAD_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} NAS_DYNLOAD_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    NAS_DYNLOAD_MNTN_MSG_DATA           stMsgData;
} NasDynloadMntn_MSG;



/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  NAS_DYNLOAD_LogRegisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit,
    VOS_UINT32                          ulUnload
);

VOS_VOID  NAS_DYNLOAD_LogDeregisterInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid
);

VOS_VOID  NAS_DYNLOAD_LogExcuteInitInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulInit
);

VOS_VOID  NAS_DYNLOAD_LogExcuteUnloadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_RATMODE_ENUM_UINT32             enRatType,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulUnload
);

VOS_VOID  NAS_DYNLOAD_LogStartDrvLoadInfo(
    VOS_RATMODE_ENUM_UINT32             enRatType
);

VOS_VOID  NAS_DYNLOAD_LogFinishDrvLoadInfo(
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstDynloadCbRatInfo,
    VOS_INT32                           lLoadResult
);

VOS_VOID NAS_Dynload_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_DYNLOAD_REBOOT_INFO_STRU       *pstRebootInfo
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

#endif /* end of TafSpmMntn.h */


