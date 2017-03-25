/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcNvim.c
  �� �� ��   : ����
  ��    ��   : h00313353
  ��������   : 2015��07��07��
  ����޸�   :
  ��������   : ����Nvim���ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "TafXCallCtx.h"
#include "NVIM_Interface.h"
#include "TafXCallProcNvim.h"
#include "TafLog.h"
#include "TafXCallMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
static const VOS_UINT8 g_aucDefKmcPubKey[] = {
    0x9F, 0x01, 0xD8, 0x5B, 0x82, 0xB7, 0x51, 0xE4, 0x15, 0x64,
    0xA7, 0xCD, 0x9B, 0x65, 0xFC, 0x2F, 0x5B, 0xDF, 0x07, 0xD4,
    0x7F, 0x81, 0x11, 0x1D, 0x3B, 0xCA, 0x2A, 0x71, 0x5E, 0xB4,
    0x96, 0xE3, 0x04, 0xB4, 0x1A, 0x18, 0x58, 0x84, 0xCB, 0xE6,
    0x4B, 0x73, 0x61, 0x5A, 0x7E, 0x20, 0x0C, 0xD1
};
#endif

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadEmcCallRedialPeriod
 ��������  : ��ȡ�������ز���ʱ��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : h00313353
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  TAF_XCALL_ReadEmcCallRedialPeriod(VOS_VOID)
{
    TAF_XCALL_CONFIG_STRU                                  *pstXcallConfig = VOS_NULL_PTR;
    TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU           stEmcCallRedialPeriod;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stEmcCallRedialPeriod, 0x0, sizeof(stEmcCallRedialPeriod));

    if (NV_OK != NV_Read(en_Nv_Item_EMC_REDIAL_PERIOD,
                         &stEmcCallRedialPeriod, sizeof(stEmcCallRedialPeriod)))
    {
        pstXcallConfig->ulEmcRedialPeriod   = TAF_XCALL_EMC_CALL_REDIAL_PERIOD_DEFAULT * 1000;

        return;
    }

    pstXcallConfig->ulEmcRedialPeriod = stEmcCallRedialPeriod.ulEmcCallRedialPeriod * 1000;

    TAF_XCALL_MNTN_LogEmcCallRedialPeriod();

    return;
}


VOS_VOID TAF_XCALL_Read1xVoiceSoCfgNvim()
{
    TAF_XCALL_SO_TYPE_ENUM_UINT16      *penSoType = VOS_NULL_PTR;
    TAF_NVIM_1X_VOICE_SO_CFG            st1xVoiceSoCfg;

    penSoType = &(TAF_XCALL_GetConfigInfo()->enSoInitType);

    PS_MEM_SET(&st1xVoiceSoCfg, 0x0, sizeof(st1xVoiceSoCfg));

    if (NV_OK != NV_Read(en_Nv_Item_1X_VOICE_SO_CFG,
                         &st1xVoiceSoCfg, sizeof(st1xVoiceSoCfg)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_Read1xVoiceSoCfgNvim:Read Nvim Failed");

       *penSoType = TAF_XCALL_SO_3_EVRC;
        return;
    }

    if ((TAF_XCALL_SO_3_EVRC    != st1xVoiceSoCfg.usSo)
     && (TAF_XCALL_SO_68_EVRC_B != st1xVoiceSoCfg.usSo))
    {
        *penSoType = TAF_XCALL_SO_3_EVRC;

    }
    else
    {
        *penSoType = st1xVoiceSoCfg.usSo;
    }

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadStartAndStopContDtmfIntervalLen
 ��������  : ��ȡ ����Stop Cont DTMF Req��Start Cont DTMF Reqʱ������ʱ��ʱ������λΪ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : l00324781
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadStartAndStopContDtmfIntervalLen(VOS_VOID)
{
    TAF_XCALL_CONFIG_STRU                                  *pstXcallConfig = VOS_NULL_PTR;
    TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU   stStartAndStopContDtmfInterVal;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stStartAndStopContDtmfInterVal, 0x0, sizeof(stStartAndStopContDtmfInterVal));

    if (NV_OK != NV_Read(en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL,
                         &stStartAndStopContDtmfInterVal, sizeof(stStartAndStopContDtmfInterVal)))
    {
        /* ��ȡʧ�ܣ�ʹ����Сʱ����Ϊ360ms */
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN;

        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_ReadStartAndStopContDtmfIntervalLen():WARNING: en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL Error");
        return;
    }

    /* NV���ü�� */
    if (TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN > stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen)
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN;
    }
    else if (TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX < stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen)
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX;
    }
    else
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen;
    }

    /* ��ά�ɲ⣬���� */
    TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval();

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadEmcCallBackCfgNvim
 ��������  : ��ȡ�������Ƿ����غ�ģʽ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��9��
    ��    ��   : w00242748
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  TAF_XCALL_ReadEmcCallBackCfgNvim(VOS_VOID)
{
    TAF_NVIM_1X_CALLBACK_CFG_STRU       stNvCallBackCfg;
    TAF_XCALL_CONFIG_STRU              *pstXcallConfig = VOS_NULL_PTR;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stNvCallBackCfg, 0x00, sizeof(TAF_NVIM_1X_CALLBACK_CFG_STRU));

    if (NV_OK != NV_Read(en_Nv_Item_EMC_CALLBACK_CFG,
                         &stNvCallBackCfg, sizeof(TAF_NVIM_1X_CALLBACK_CFG_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_ReadEmcCallBackCfgNvim:Read Nvim Failed");

        /* ��ȡʧ�� Ĭ�Ϲر�CallBack */
        pstXcallConfig->ulCallBackEnableFlg = VOS_FALSE;

        return;
    }

    pstXcallConfig->ulCallBackEnableFlg = stNvCallBackCfg.ulCallBackEnableFlg;

    return;
}


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadVoiceEncryptPublicKeyAndVersionNumber
 ��������  : ��ȡECC�Ĺ�Կ�Լ���Կ�汾��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadVoiceEncryptPublicKeyAndVersionNumber(VOS_VOID)
{
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo = VOS_NULL_PTR;
    TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU                 stNvimEccPubKeyInfo;

    pstEccPubKeyInfo    = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();

    PS_MEM_SET(&stNvimEccPubKeyInfo, 0x00, sizeof(TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_PUBLICKEY_AND_VERSION_INFO,
                         &stNvimEccPubKeyInfo,
                         sizeof(TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU)))
    {
        pstEccPubKeyInfo->ucVerNum  = 0;

        PS_MEM_CPY(&(pstEccPubKeyInfo->aucPubKey[0]),
                   &g_aucDefKmcPubKey[0],
                   sizeof(pstEccPubKeyInfo->aucPubKey));

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptPublicKeyAndVersionNumber():WARNING: en_NV_Item_VOICE_ENCRYPT_PUBLICKEY_AND_VERSION_INFO Error");
        return;
    }

    pstEccPubKeyInfo->ucVerNum  = stNvimEccPubKeyInfo.ucVerNum;
    PS_MEM_CPY(pstEccPubKeyInfo->aucPubKey, stNvimEccPubKeyInfo.aucPubKey, sizeof(VOS_UINT8) * TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    TAF_XCALL_MNTN_LogVoiceEncPubKeyAndVerInfo(stNvimEccPubKeyInfo.ucVerNum, stNvimEccPubKeyInfo.aucPubKey);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber
 ��������  : дECC�Ĺ�Կ�Լ���Կ�汾��
 �������  : pucPubKey -- ��ԿK0
             ucVerNum  -- �汾��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber(
    VOS_UINT8                          *pucPubKey,
    VOS_UINT8                           ucVerNum
)
{
    TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU                 stNvimEccPubKeyInfo;

    PS_MEM_SET(&stNvimEccPubKeyInfo, 0x00, sizeof(TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU));
    stNvimEccPubKeyInfo.ucVerNum        = ucVerNum;

    PS_MEM_CPY(stNvimEccPubKeyInfo.aucPubKey, pucPubKey, sizeof(VOS_UINT8) * TAF_NVIM_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    if (NV_OK != NV_Write(en_NV_Item_VOICE_ENCRYPT_PUBLICKEY_AND_VERSION_INFO,
                         &stNvimEccPubKeyInfo,
                         sizeof(TAF_NVIM_ENCVOICE_ECC_PUB_KEY_INFO_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber:Write Nvim Failed");

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadVoiceEncryptCapCfgPara
 ��������  : ��ȡ���������������ò����������������Լ���̬���ÿ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadVoiceEncryptCapCfgPara(VOS_VOID)
{
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCapInfo = VOS_NULL_PTR;
    TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU                 stNvimEccSrvCapInfo;

    pstEccSrvCapInfo    = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    PS_MEM_SET(&stNvimEccSrvCapInfo, 0x00, sizeof(TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO,
                         &stNvimEccSrvCapInfo,
                         sizeof(TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU)))
    {
        pstEccSrvCapInfo->ucEccSrvCap       = VOS_FALSE;
        pstEccSrvCapInfo->ucEccSrvStatus    = VOS_FALSE;

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptCapCfgPara():WARNING: en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO Error");
        return;
    }

    /* ����������ȡ��ֵ��� */
    if (VOS_FALSE != stNvimEccSrvCapInfo.ucEccSrvCap)
    {
        stNvimEccSrvCapInfo.ucEccSrvCap     = VOS_TRUE;
    }

    /* ����״̬��ȡ��ֵ��� */
    if (VOS_FALSE != stNvimEccSrvCapInfo.ucEccSrvStatus)
    {
        stNvimEccSrvCapInfo.ucEccSrvStatus  = VOS_TRUE;
    }

    pstEccSrvCapInfo->ucEccSrvCap           = stNvimEccSrvCapInfo.ucEccSrvCap;
    pstEccSrvCapInfo->ucEccSrvStatus        = stNvimEccSrvCapInfo.ucEccSrvStatus;

    TAF_XCALL_MNTN_LogVoiceEncryptCapCfgPara(stNvimEccSrvCapInfo.ucEccSrvCap, stNvimEccSrvCapInfo.ucEccSrvStatus);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_WriteVoiceEncryptCapCfgPara
 ��������  : д���������������ò����������������Լ���̬���ÿ���
 �������  :
             ucEccSwithOnFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_WriteVoiceEncryptCapCfgPara(
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap,
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus
)
{
    TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU                 stNvimEccSrvCapInfo;
    VOS_UINT8                                               ucEccSrvCap;
    VOS_UINT8                                               ucEccSrvStatus;

    ucEccSrvCap                                             = VOS_FALSE;
    ucEccSrvStatus                                          = VOS_FALSE;

    if (TAF_CALL_APP_ECC_SRV_CAP_ENABLE == enEccSrvCap)
    {
        ucEccSrvCap                                         = VOS_TRUE;
    }

    if (TAF_CALL_APP_ECC_SRV_STATUS_OPEN == enEccSrvStatus)
    {
        ucEccSrvStatus                                      = VOS_TRUE;
    }

    PS_MEM_SET(&stNvimEccSrvCapInfo, 0x00, sizeof(TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU));
    stNvimEccSrvCapInfo.ucEccSrvCap                         = ucEccSrvCap;
    stNvimEccSrvCapInfo.ucEccSrvStatus                      = ucEccSrvStatus;

    if (NV_OK != NV_Write(en_NV_Item_VOICE_ENCRYPT_CAP_PARA_INFO,
                         &stNvimEccSrvCapInfo,
                         sizeof(TAF_NVIM_ENCVOICE_ECC_SRV_CAP_INFO_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_WriteVoiceEncryptCapCfgPara:Write Nvim Failed");

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadVoiceEncryptSecInfoEraseSysTime
 ��������  : ��ȡ��ȫ��Ϣ����ϵͳʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadVoiceEncryptSecInfoEraseSysTime(VOS_VOID)
{
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstLastInfoEraseTime = VOS_NULL_PTR;
    TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU       stNvimSecInfoEraseSystime;

    pstLastInfoEraseTime    = TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime();

    PS_MEM_SET(&stNvimSecInfoEraseSystime, 0x0, sizeof(TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_SECINFO_ERASE_SYSTIME_INFO,
                         &stNvimSecInfoEraseSystime,
                         sizeof(TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU)))
    {
        PS_MEM_SET(pstLastInfoEraseTime, 0x00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptSecInfoEraseSysTime():WARNING: en_NV_Item_VOICE_ENCRYPT_SECINFO_ERASE_SYSTIME_INFO Error");
        return;
    }

    pstLastInfoEraseTime->usYear        = stNvimSecInfoEraseSystime.usYear;
    pstLastInfoEraseTime->usMonth       = stNvimSecInfoEraseSystime.usMonth;
    pstLastInfoEraseTime->usDay         = stNvimSecInfoEraseSystime.usDay;
    pstLastInfoEraseTime->usHour        = stNvimSecInfoEraseSystime.usHour;
    pstLastInfoEraseTime->usMinute      = stNvimSecInfoEraseSystime.usMinute;
    pstLastInfoEraseTime->usSecond      = stNvimSecInfoEraseSystime.usSecond;

    TAF_XCALL_MNTN_LogVoiceEncryptLastInfoEraseTime((TAF_STD_TIME_ZONE_TYPE_STRU *)&stNvimSecInfoEraseSystime);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime
 ��������  : д��ȫ��Ϣ����ϵͳʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstSysTime
)
{
    TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU       stNvimSecInfoEraseSystime;

    PS_MEM_SET(&stNvimSecInfoEraseSystime, 0x00, sizeof(TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU));

    stNvimSecInfoEraseSystime.usYear                        = pstSysTime->usYear;
    stNvimSecInfoEraseSystime.usMonth                       = pstSysTime->usMonth;
    stNvimSecInfoEraseSystime.usDay                         = pstSysTime->usDay;
    stNvimSecInfoEraseSystime.usHour                        = pstSysTime->usHour;
    stNvimSecInfoEraseSystime.usMinute                      = pstSysTime->usMinute;
    stNvimSecInfoEraseSystime.usSecond                      = pstSysTime->usSecond;

    if (NV_OK != NV_Write(en_NV_Item_VOICE_ENCRYPT_SECINFO_ERASE_SYSTIME_INFO,
                         &stNvimSecInfoEraseSystime,
                         sizeof(TAF_NVIM_ENCVOICE_SECINFO_ERASE_SYSTIME_INFO_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime:Write Nvim Failed");

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadVoiceEncryptPassWordResetSysTime
 ��������  : ��ȡ��������ϵͳʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadVoiceEncryptPassWordResetSysTime(VOS_VOID)
{
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstLastPassworResetTime = VOS_NULL_PTR;
    TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU        stNvimPasswdResetSystime;

    pstLastPassworResetTime    = TAF_XCALL_GetVoiceEncryptPassWordResetSysTime();

    PS_MEM_SET(&stNvimPasswdResetSystime, 0x0, sizeof(TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_PASSWD_RESET_SYSTIME_INFO,
                         &stNvimPasswdResetSystime,
                         sizeof(TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU)))
    {
        PS_MEM_SET(pstLastPassworResetTime, 0x00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptPassWordResetSysTime():WARNING: en_NV_Item_VOICE_ENCRYPT_PASSWD_RESET_SYSTIME_INFO Error");
        return;
    }

    pstLastPassworResetTime->usYear        = stNvimPasswdResetSystime.usYear;
    pstLastPassworResetTime->usMonth       = stNvimPasswdResetSystime.usMonth;
    pstLastPassworResetTime->usDay         = stNvimPasswdResetSystime.usDay;
    pstLastPassworResetTime->usHour        = stNvimPasswdResetSystime.usHour;
    pstLastPassworResetTime->usMinute      = stNvimPasswdResetSystime.usMinute;
    pstLastPassworResetTime->usSecond      = stNvimPasswdResetSystime.usSecond;

    TAF_XCALL_MNTN_LogVoiceEncryptLastPassworResetTime((TAF_STD_TIME_ZONE_TYPE_STRU *)&stNvimPasswdResetSystime);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime
 ��������  : д��������ϵͳʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstSysTime
)
{
    TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU        stNvimPasswdResetSystime;

    PS_MEM_SET(&stNvimPasswdResetSystime, 0x00, sizeof(TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU));

    stNvimPasswdResetSystime.usYear                         = pstSysTime->usYear;
    stNvimPasswdResetSystime.usMonth                        = pstSysTime->usMonth;
    stNvimPasswdResetSystime.usDay                          = pstSysTime->usDay;
    stNvimPasswdResetSystime.usHour                         = pstSysTime->usHour;
    stNvimPasswdResetSystime.usMinute                       = pstSysTime->usMinute;
    stNvimPasswdResetSystime.usSecond                       = pstSysTime->usSecond;

    if (NV_OK != NV_Write(en_NV_Item_VOICE_ENCRYPT_PASSWD_RESET_SYSTIME_INFO,
                         &stNvimPasswdResetSystime,
                         sizeof(TAF_NVIM_ENCVOICE_PASSWD_RESET_SYSTIME_INFO_STRU)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime:Write Nvim Failed");

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ReadVoiceEncryptTimerCfgInfo
 ��������  : ��ȡ����������ʱ��Կ������ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadVoiceEncryptTimerCfgInfo(VOS_VOID)
{
    TAF_XCALL_ENCRYPT_VOICE_PARA_INFO_CTX                  *pstEncVoiceInfoCtx = VOS_NULL_PTR;
    TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU                   stNvimEncVoiceTimerCfg;

    pstEncVoiceInfoCtx = TAF_XCALL_GetEncVoiceInfoCtxAddr();

    PS_MEM_SET(&stNvimEncVoiceTimerCfg, 0x0, sizeof(stNvimEncVoiceTimerCfg));

    if (NV_OK != NV_Read(en_NV_Item_VOICE_ENCRYPT_TIMER_CFG_INFO,
                         &stNvimEncVoiceTimerCfg,
                         sizeof(TAF_NVIM_ENCVOICE_TIMER_CFG_INFO_STRU)))
    {
        pstEncVoiceInfoCtx->usDelayEncVoiceReqTimerLen  = (VOS_UINT16)TAF_XCALL_ENCVOICE_REQ_DEFAULT_DELAY_TIMER_LEN;
        pstEncVoiceInfoCtx->usRemoteCtrlAnswerTimerLen  = (VOS_UINT16)TI_TAF_XCALL_REMOTE_CTRL_ANSWER_DEFAULT_TIMER_LEN;

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptTimerCfgInfo():WARNING: en_NV_Item_VOICE_ENCRYPT_ENCVOICE_REQ_DELAY_INFO Error");
        return;
    }

    /* �ӳ�ʱ����Сֵ��1����С��1����ֵΪ2�� */
    if (0 == stNvimEncVoiceTimerCfg.ucDelayEncVoiceReqTimerLen)
    {
        pstEncVoiceInfoCtx->usDelayEncVoiceReqTimerLen = (VOS_UINT16)TAF_XCALL_ENCVOICE_REQ_DEFAULT_DELAY_TIMER_LEN;

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptTimerCfgInfo():WARNING: en_NV_Item_VOICE_ENCRYPT_ENCVOICE_REQ_DELAY_INFO Nv Value Less Than 1");
    }
    else
    {
        pstEncVoiceInfoCtx->usDelayEncVoiceReqTimerLen = TAF_XCALL_MIN(stNvimEncVoiceTimerCfg.ucDelayEncVoiceReqTimerLen,
                                                                       TAF_XCALL_ENCVOICE_REQ_MAX_DELAY_TIMER_LEN);
    }

    if (0 == stNvimEncVoiceTimerCfg.usRemoteCtrlAnswerTimerLen)
    {
        pstEncVoiceInfoCtx->usRemoteCtrlAnswerTimerLen = (VOS_UINT16)TI_TAF_XCALL_REMOTE_CTRL_ANSWER_DEFAULT_TIMER_LEN;

        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_XCALL_ReadVoiceEncryptTimerCfgInfo(): usRemoteCtrlAnswerTimerLen = 0!!!");
    }
    else
    {
        pstEncVoiceInfoCtx->usRemoteCtrlAnswerTimerLen = TAF_XCALL_MIN(stNvimEncVoiceTimerCfg.usRemoteCtrlAnswerTimerLen,
                                                                       TI_TAF_XCALL_REMOTE_CTRL_ANSWER_MAX_TIMER_LEN);
    }

    TAF_XCALL_MNTN_LogVoiceEncryptTimerCfgInfo(pstEncVoiceInfoCtx->usDelayEncVoiceReqTimerLen,
                                               pstEncVoiceInfoCtx->usRemoteCtrlAnswerTimerLen);

    return;
}
#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




