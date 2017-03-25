/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmProcNvim.c
  �� �� ��   : ����
  ��    ��   : W00176964
  ��������   : 2013��5��22��
  ����޸�   :
  ��������   : TafSpmProcNvim.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��22��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmCtx.h"
#include "TafLog.h"
#include "PsNvId.h"
#include "NVIM_Interface.h"
#include "TafNvInterface.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_PROC_NVIM_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/


/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_SPM_ReadFdnInfoNvim
 ��������  : ��ȡen_NV_Item_FDN_Info��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��22��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_ReadFdnInfoNvim(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfgInfo = VOS_NULL_PTR;
    TAF_FDN_NVIM_CONFIG_STRU            stFdnConfig;

    pstServiceCtrlCfgInfo               = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_FDN_Info,
                         &stFdnConfig,
                         sizeof(TAF_FDN_NVIM_CONFIG_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadNvimInfo():WARNING: en_NV_Item_FDN_Info Error");
        pstServiceCtrlCfgInfo->ulMeStatus = TAF_FDN_CHECK_FEATURE_OFF;

        return;
    }

    pstServiceCtrlCfgInfo->ulMeStatus   = stFdnConfig.ulMeStatus;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_ReadSimCallCtrlNvim
 ��������  : ��ȡen_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��22��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_ReadSimCallCtrlNvim(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU                     *pstServiceCtrlCfgInfo = VOS_NULL_PTR;
    MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU                  stSimCallCtrlFlg;

    pstServiceCtrlCfgInfo                           = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG,
                        &stSimCallCtrlFlg,
                        sizeof(MN_CALL_NVIM_SIM_CALL_CONTROL_FLG_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadNvimInfo():WARNING: en_NV_Item_NVIM_SIM_CALL_CONTROL_SUPPORT_FLG Error");
        pstServiceCtrlCfgInfo->ucSimCallCtrlSupportFlg  = VOS_FALSE;

        return;
    }

    pstServiceCtrlCfgInfo->ucSimCallCtrlSupportFlg = stSimCallCtrlFlg.ucSimCallCtrlSupportFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim
 ��������  : ��ȡNV�л���cc/ss/sms�������󱣻���ʱ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��9��
    ��    ��   : c00318887
    �޸�����   : �½�����
*****************************************************************************/
VOS_VOID TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim(VOS_VOID)
{
    TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU      stSrvReqProtectTimerCfg;
    TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU          *pstSrvReqProtectTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulNvLen                   = 0;

    pstSrvReqProtectTimerInfo                               = TAF_SPM_GetBufferServiceReqProtectTimerInfo();

    PS_MEM_SET(&stSrvReqProtectTimerCfg, 0x00, sizeof(stSrvReqProtectTimerCfg));

    (VOS_VOID)NV_GetLength(en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG, &ulNvLen);

    if ( ulNvLen > sizeof(TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim:read en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG len failed");
        return;
    }

    /* ��ȡNV */
    if (NV_OK != NV_Read(en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG,
                         &stSrvReqProtectTimerCfg,
                         sizeof(TAF_NVIM_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim:read en_NV_Item_BUFFER_SERVICE_REQ_PROTECT_TIMER_CFG failed");
        return;
    }

    /* ��NV��ȡ�����ݱ�����ȫ�ֱ����� */
    pstSrvReqProtectTimerInfo->ulBufferCcProtectTimerLen    = (stSrvReqProtectTimerCfg.ucBufferCcProtectTimerLen * NAS_SPM_ONE_THOUSAND_MILLISECOND);
    pstSrvReqProtectTimerInfo->ulBufferSmsProtectTimerLen   = (stSrvReqProtectTimerCfg.ucBufferSmsProtectTimerLen * NAS_SPM_ONE_THOUSAND_MILLISECOND);
    pstSrvReqProtectTimerInfo->ulBufferSsProtectTimerLen    = (stSrvReqProtectTimerCfg.ucBufferSsProtectTimerLen * NAS_SPM_ONE_THOUSAND_MILLISECOND);

    /* ��ֹNVֵ���ù��� */
    if (TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL < pstSrvReqProtectTimerInfo->ulBufferCcProtectTimerLen)
    {
        pstSrvReqProtectTimerInfo->ulBufferCcProtectTimerLen    = TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL;
    }
    
    if (TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL < pstSrvReqProtectTimerInfo->ulBufferSmsProtectTimerLen)
    {
        pstSrvReqProtectTimerInfo->ulBufferSmsProtectTimerLen   = TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL;
    }
    
    if (TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL < pstSrvReqProtectTimerInfo->ulBufferSsProtectTimerLen)
    {
        pstSrvReqProtectTimerInfo->ulBufferSsProtectTimerLen    = TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL;
    } 

    return;
}


/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-15, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_ReadVideoCallNvim
 ��������  : ��ȡen_NV_Item_VIDEO_CALL��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_ReadVideoCallNvim(VOS_VOID)
{
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU                     *pstServiceCtrlCfgInfo = VOS_NULL_PTR;
    MN_CALL_NV_ITEM_VIDEO_CALL_STRU                         stVideoCall;

    pstServiceCtrlCfgInfo                           = TAF_SPM_GetServiceCtrlCfgInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_VIDEO_CALL,
                        &stVideoCall,
                        sizeof(MN_CALL_NV_ITEM_VIDEO_CALL_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ReadVideoCallNvim():WARNING: en_NV_Item_VIDEO_CALL Error");

        return;
    }

    if (VOS_TRUE == stVideoCall.ucStatus)
    {
        pstServiceCtrlCfgInfo->enVpCfgState = stVideoCall.ucVpCfgState;
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-15, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_ReadNvimInfo
 ��������  : ��ȡSPMģ���NV��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��22��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_ReadNvimInfo(VOS_VOID)
{
    TAF_SPM_ReadFdnInfoNvim();

    TAF_SPM_ReadSimCallCtrlNvim();

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-15, begin */
    TAF_SPM_ReadVideoCallNvim();
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-15, end */

    TAF_SPM_ReadBufferServiceReqProtectTimerCfgNvim();
    
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

