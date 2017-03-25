/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcNvim.h
  �� �� ��   : ����
  ��    ��   : h00313353
  ��������   : 2015��07��07��
  ����޸�   :
  ��������   : TafXCallProcNvim.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_X_CALL_PROC_NVIM_H__
#define __TAF_X_CALL_PROC_NVIM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "TafAppCall.h"
#include "TafStdlib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_ReadEmcCallRedialPeriod(VOS_VOID);

VOS_VOID TAF_XCALL_Read1xVoiceSoCfgNvim(VOS_VOID);
VOS_VOID TAF_XCALL_ReadStartAndStopContDtmfIntervalLen(VOS_VOID);

VOS_VOID  TAF_XCALL_ReadEmcCallBackCfgNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_ReadVoiceEncryptPublicKeyAndVersionNumber(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber(
    VOS_UINT8                          *pucPubKey,
    VOS_UINT8                           ucVerNum
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptCapCfgPara(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptCapCfgPara(
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap,
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptSecInfoEraseSysTime(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstSysTime
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptPassWordResetSysTime(VOS_VOID);

VOS_VOID TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstSysTime
);

VOS_VOID TAF_XCALL_ReadVoiceEncryptTimerCfgInfo(VOS_VOID);
#endif
#endif

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

#endif /* end of TafXCallProcNvim.h */



