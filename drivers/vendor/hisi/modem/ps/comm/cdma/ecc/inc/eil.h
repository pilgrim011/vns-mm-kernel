/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Eil.h
  �� �� ��   : ����
  ��    ��   : chenqihang
  ��������   : 2015��10��20��
  ����޸�   :
  ��������   : Eil.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��20��
    ��    ��   : chenqihang
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __EIL_H__
#define __EIL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_INT32 CAS_1X_GetPower(VOS_VOID);

VOS_INT32 CAS_1X_GetRssi(VOS_VOID);

VOS_INT32 CAS_1X_GetEcio(VOS_VOID);

VOS_INT32 CAS_1X_GetPilotStrength(VOS_VOID);
#endif
#endif
VOS_UINT32 eil_get_power(VOS_VOID);

VOS_UINT32 eil_get_battery(VOS_VOID);

VOS_UINT32 eil_get_rssi(VOS_VOID);

VOS_UINT32 eil_get_ecio(VOS_VOID);

VOS_UINT32 eil_get_pilot_strength(VOS_VOID);

VOS_UINT32 eil_get_time(VOS_VOID);

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

#endif /* end of eil.h */
