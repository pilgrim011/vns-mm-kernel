/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : VcCtx.c
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2012��03��03��
  ����޸�   :
  ��������   : VCģ�������Ĵ����ļ�
  �����б�   :

  �޸���ʷ   :
   1. ��    ��   : 2012��03��03��
      ��    ��   : s62952
      �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "VcCtx.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define THIS_FILE_ID                    PS_FILE_ID_VC_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
APP_VC_STATE_MGMT_STRU                  g_stVcStateMgmt;
/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

#if 0
/* VC CTX,���ڱ���VC������ */
APP_VC_STATE_MGMT_STRU                  g_stAppVcCtx;
#endif


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
#if 0
/*****************************************************************************
 �� �� ��  : APP_VC_GetCtx
 ��������  : ��ȡ��ǰVC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰVC��CTX
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��3��
   ��    ��   : s62952
   �޸�����   : �����ɺ���

*****************************************************************************/
APP_VC_STATE_MGMT_STRU*  APP_VC_GetCtx( VOS_VOID )
{
    return &(g_stAppVcCtx);
}
#endif
/*****************************************************************************
 �� �� ��  : APP_VC_GetVcStateMgmtAddr
 ��������  : ��ȡ��ǰVC��״̬����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VC״̬������ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��5��13��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
APP_VC_STATE_MGMT_STRU*  APP_VC_GetVcStateMgmtAddr( VOS_VOID )
{
    return &(g_stVcStateMgmt);
}


/*****************************************************************************
 �� �� ��  : APP_VC_GetCustomCfgInfo
 ��������  : ��ȡVC�б������Զ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VC�б������Զ���������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��3��
   ��    ��   : s62952
   �޸�����   : �����ɺ���

 2.��    ��   : 2014��08��30��
   ��    ��   : l00198894
   �޸�����   : DTS2014082905824

*****************************************************************************/
APP_VC_MS_CFG_INFO_STRU* APP_VC_GetCustomCfgInfo( VOS_VOID )
{
    return &(APP_VC_GetVcStateMgmtAddr()->stMsCfgInfo);
}

/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : APP_VC_GetEcallMsdAddr
 ��������  : ��ȡVC�б���Ecall MSD���ݵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VC�б���Ecall MSD���ݵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��3��27��
   ��    ��   : j00174725
   �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_UINT8* APP_VC_GetEcallMsdAddr( VOS_VOID )
{
    return &(APP_VC_GetVcStateMgmtAddr()->stEcallCtx.aucMsdData[0]);
}

/*****************************************************************************
 �� �� ��  : APP_VC_SetNewEcallCfg
 ��������  : ����APP�·�������Ecall����
 �������  : usMode -- ���ݴ���ģʽ
             usVocConfig --���ݴ���ʱ�Ƿ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SetNewEcallCfg(
    VOS_UINT16                          usMode,
    VOS_UINT16                          usVocConfig
)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallMode         = usMode;
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallVocConfig    = usVocConfig;
}

/*****************************************************************************
 �� �� ��  : APP_VC_UpdateCurrEcallCfg
 ��������  : ����Ecall��ǰ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_UpdateCurrEcallCfg(VOS_VOID)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallMode        = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallMode;
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallVocConfig   = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enNewEcallVocConfig;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetCurrEcallCfg
 ��������  : ���õ�ǰEcall����
 �������  : ��
 �������  : pusMode -- ���ݴ���ģʽ
             pusVocConfig --���ݴ���ʱ�Ƿ��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_GetCurrEcallCfg(
    VOS_UINT16                         *pusMode,
    VOS_UINT16                         *pusVocConfig
)
{
    *pusMode        = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallMode;
    *pusVocConfig   = APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enCurrEcallVocConfig;
}

/*****************************************************************************
 �� �� ��  : APP_VC_SetInEcallFlag
 ��������  : ��eCall��ʶ
 �������  : PS_BOOL_ENUM_UINT8 -- ���ñ�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SetInEcallFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enInECall = enFlag;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetInEcallFlag
 ��������  : ��ȡeCall��ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
PS_BOOL_ENUM_UINT8 APP_VC_GetInEcallFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enInECall;
}

/*****************************************************************************
 �� �� ��  : APP_VC_SetMsdFlag
 ��������  : ��ʶ�·�MSD ���ݱ�ʶ
 �������  : PS_BOOL_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enMsdFlag = enFlag;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetMsdFlag
 ��������  : ��ȡ�·�MSD ���ݱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
PS_BOOL_ENUM_UINT8 APP_VC_GetMsdFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enMsdFlag;
}


/*****************************************************************************
 �� �� ��  : APP_VC_SetEcallState
 ��������  : ����Ecall ״̬
 �������  : APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 -- ״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SetEcallState(APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 enState)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enEcallState = enState;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetEcallState
 ��������  : ��ȡEcall��״̬
 �������  : ��
 �������  : APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 --ecll״̬
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 APP_VC_GetEcallState(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enEcallState;
}

/*****************************************************************************
 �� �� ��  : APP_VC_SetEcallDescription
 ��������  : ����Ecall ״̬����
 �������  : VOS_UINT32 -- ״̬����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SetEcallDescription(VOS_UINT32 ulDesc)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.ulEcallDescription = ulDesc;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetEcallDescription
 ��������  : ��ȡ��ǰEcall��״̬����
 �������  : ��
 �������  : APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 --ecll״̬
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_UINT32 APP_VC_GetEcallDescription(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.ulEcallDescription;
}

/*****************************************************************************
 �� �� ��  : APP_VC_SetAllowSetMsdFlag
 ��������  : �����Ƿ���������MSD���ݵı�־
 �������  : PS_BOOL_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VOS_VOID APP_VC_SetAllowSetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enAllowSetMsdFlag = enFlag;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetAllowSetMsdFlag
 ��������  : ��ȡ�Ƿ���������MSD���ݵı�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��3��27��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
PS_BOOL_ENUM_UINT8 APP_VC_GetAllowSetMsdFlag(VOS_VOID)
{
    return APP_VC_GetVcStateMgmtAddr()->stEcallCtx.enAllowSetMsdFlag;
}

/*****************************************************************************
 �� �� ��  : APP_VC_GetAlAckInfoAddr
 ��������  : ��ȡAlAck��¼��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VC_AL_ACK_REPORT_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2014��6��30��
  ��    ��   : j00174725
  �޸�����   : V3R3C60_eCall��Ŀ
*****************************************************************************/
VC_AL_ACK_REPORT_INFO_STRU* APP_VC_GetAlAckInfoAddr(VOS_VOID)
{
    return &(APP_VC_GetVcStateMgmtAddr()->stEcallCtx.stVcAlAckReportInfo);
}


#endif
/* Added by j00174725 for V3R3C60_eCall��Ŀ, 2014-3-29, End */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



