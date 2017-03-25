/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasDynLoadApi.c
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2015��8��11��
  ����޸�   :
  ��������   : NasDynLoadApi.c�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��11��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasDynLoadApi.h"
#include "mdrv.h"
#include "NasDynLoad.h"
#include "NasMntn.h"
#include "NasDynLoadMntn.h"
#include "NVIM_Interface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_DYNLOAD_API_C

NAS_DYNLOAD_CB_RAT_INFO_STRU            g_astNasDynloadCbRatInfo[VOS_RATMODE_BUTT];
VOS_RATMODE_ENUM_UINT32                 g_enCurRatModeInCached[NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT] = {VOS_RATMODE_BUTT};
NAS_DYNLOAD_CTRL_STRU                   g_stNasDynloadCtrl;
WAS_QueryCSNR                           g_pfTafQueryCsnrCb = VOS_NULL_PTR;


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
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : TAF_RegQueryCSNR
 ��������  : ���ػص�����WAS_MNTN_QUERYCSNR��ע�ắ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_RegQueryCsnrCallBack(
    WAS_QueryCSNR                      pfQueryCsnr
)
{
    g_pfTafQueryCsnrCb = pfQueryCsnr;
}

/*****************************************************************************
 �� �� ��  : TAF_GetTafQueryCsnrAddr
 ��������  : ���ػص�����WAS_MNTN_QUERYCSNR��ע�ắ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : WAS_QueryCSNR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
WAS_QueryCSNR TAF_GetWasQueryCsnrAddr(VOS_VOID)
{
    return g_pfTafQueryCsnrCb;
}


#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim
 ��������  : ��NVIM�л�ȡ��̬���ش���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim(VOS_VOID)
{
    NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU                    stDynloadExceptionCtrl;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Dynload_Exception_CTRL, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_DYNLOAD_EXCEPTION_CTRL_STRU))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim(): en_NV_Item_Dynload_Exception_CTRL length Error");

        NAS_DYNLOAD_SetTWMaxAttemptCount(0);

        return;
    }

    PS_MEM_SET(&stDynloadExceptionCtrl, 0x00, sizeof(stDynloadExceptionCtrl));

    if (NV_OK != NV_Read(en_NV_Item_Dynload_Exception_CTRL,
                        (VOS_VOID *)&stDynloadExceptionCtrl,
                        ulLength))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                     "NAS_DYNLOAD_ReadDynloadExceptionCtrlNvim():en_NV_Item_Dynload_Exception_CTRL Error");

        NAS_DYNLOAD_SetTWMaxAttemptCount(0);

        return;
    }

    if (stDynloadExceptionCtrl.ucTWMaxAttemptCount > NAS_DYNLOAD_MAX_ATTEMPT_COUNT)
    {
        NAS_DYNLOAD_SetTWMaxAttemptCount(NAS_DYNLOAD_MAX_ATTEMPT_COUNT);
    }
    else
    {
        NAS_DYNLOAD_SetTWMaxAttemptCount(stDynloadExceptionCtrl.ucTWMaxAttemptCount);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_ReadDynloadCtrlNvim
 ��������  : ��NVIM�л�ȡ��̬���ؿ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_ReadDynloadCtrlNvim(VOS_VOID)
{
    NAS_NVIM_DYNLOAD_CTRL_STRU          stDynloadCtrl;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Dynload_CTRL, &ulLength);

    if (ulLength > sizeof(NAS_NVIM_DYNLOAD_CTRL_STRU))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_ReadDynloadCtrlNvim(): en_NV_Item_Dynload_CTRL length Error");

        if (MODEM_ID_0 == VOS_GetModemIDFromPid(UEPS_PID_MSCC))
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_TRUE);
        }
        else
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_FALSE);
        }

        return;
    }

    PS_MEM_SET(&stDynloadCtrl, 0x00, sizeof(stDynloadCtrl));

    if (NV_OK != NV_Read(en_NV_Item_Dynload_CTRL,
                        (VOS_VOID *)&stDynloadCtrl,
                        ulLength))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                     "NAS_DYNLOAD_ReadDynloadCtrlNvim():en_NV_Item_Dynload_CTRL Error");

        if (MODEM_ID_0 == VOS_GetModemIDFromPid(UEPS_PID_MSCC))
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_TRUE);
        }
        else
        {
            NAS_DYNLOAD_SetEnableDynloadTWFlg(VOS_FALSE);
        }

        return;
    }

    NAS_DYNLOAD_SetEnableDynloadTWFlg(stDynloadCtrl.ucEnableDynloadTW);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_ConvertVosRatTypeToDrvType
 ��������  : RAT TYPE����ת��
 �������  : VOS_RATMODE_ENUM_UINT32    enVosRatType
 �������  : ��
 �� �� ֵ  : NAS_DYNLOAD_RAT_TYPE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
DRV_RAT_MODE_ENUM NAS_DYNLOAD_ConvertVosRatTypeToDrvType(
    VOS_RATMODE_ENUM_UINT32             enVosRatType
)
{
    DRV_RAT_MODE_ENUM                   enRatType;

    switch (enVosRatType)
    {
        case VOS_RATMODE_WCDMA :
            enRatType = DRV_RAT_MODE_UMTS_FDD;
            break;
        case VOS_RATMODE_TDS :
            enRatType = DRV_RAT_MODE_UMTS_TDD;
            break;
        default:
            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_ConvertVosRatTypeToDrvType enRatType InValid!\r\n");
            enRatType = DRV_RAT_MODE_BUTT;
            break;
    }

    return enRatType;
}


/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_SaveCbRatInfo
 ��������  : �����ض�ģ��ļ��ػص�����
 �������  : NAS_DYNLOAD_RAT_TYPE_ENUM_UINT32 enRatMode
             VOS_UINT32 ulPID
             NAS_DYNLOAD_INIT_CB pfInit
             NAS_DYNLOAD_UNLOAD_CB pfUnload
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_SaveCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID,
    NAS_DYNLOAD_INIT_CB                 pfInit,
    NAS_DYNLOAD_UNLOAD_CB               pfUnload
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatMode);

    if (VOS_NULL_PTR == pstCbRatInfo)
    {
        return VOS_FALSE;
    }

    /* ��ȡ��ǰPID����Ӧ���뼼����ģ���е����� */
    for (i = 0; i < pstCbRatInfo->ulNum; i++)
    {
        if (ulPID == pstCbRatInfo->astModule[i].ulPid)
        {
            break;
        }
    }

    /* ���δ�ҵ�PID����������������һ����¼ */
    if (i == pstCbRatInfo->ulNum)
    {
        if (pstCbRatInfo->ulNum == NAS_DYNLOAD_CB_MODULE_NUM)
        {
            NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_DYNLOAD_SaveCbRatInfo module num is max!\r\n");
            return VOS_FALSE;
        }

        pstCbRatInfo->astModule[i].ulPid      = ulPID;
        pstCbRatInfo->astModule[i].pfInitCb   = pfInit;
        pstCbRatInfo->astModule[i].pfUnloadCb = pfUnload;
        pstCbRatInfo->ulNum++;
    }
    else
    {
        pstCbRatInfo->astModule[i].pfInitCb   = pfInit;
        pstCbRatInfo->astModule[i].pfUnloadCb = pfUnload;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_ClearCbRatInfo
 ��������  : ����ض�ģ��ļ��ػص�����
 �������  : VOS_RATMODE_ENUM_UINT32 enRatMode
             VOS_UINT32 ulPID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_ClearCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatMode);

    if (VOS_NULL_PTR == pstCbRatInfo)
    {
        return VOS_FALSE;
    }

    /* ��ȡ��ǰPID����Ӧ���뼼����ģ���е����� */
    for (i = 0; i < pstCbRatInfo->ulNum; i++)
    {
        if (ulPID == pstCbRatInfo->astModule[i].ulPid)
        {
            break;
        }
    }

    if (i < pstCbRatInfo->ulNum)
    {
        /* ɾ��һ����¼ */
        PS_MEM_MOVE(&(pstCbRatInfo->astModule[i]),
                    &(pstCbRatInfo->astModule[i+1]),
                    (pstCbRatInfo->ulNum-i-1)*sizeof(NAS_DYNLOAD_CB_MODULE_INFO_STRU));

        pstCbRatInfo->ulNum--;

        PS_MEM_SET(&pstCbRatInfo->astModule[pstCbRatInfo->ulNum], 0x00, sizeof(NAS_DYNLOAD_CB_MODULE_INFO_STRU));
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_RegLoadCallBack
 ��������  : ���ػص�������ע�ắ��
 �������  : VOS_RATMODE_ENUM_UINT32 enRatMode
             VOS_UINT32 ulPID
             NAS_DYNLOAD_INIT_CB pfInit
             NAS_DYNLOAD_UNLOAD_CB pfUnload
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��11��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_RegLoadCallBack(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID,
    NAS_DYNLOAD_INIT_CB                 pfInit,
    NAS_DYNLOAD_UNLOAD_CB               pfUnload
)
{
    NAS_TRACE_HIGH("NAS_DYNLOAD_RegLoadCallBack enRatMode=%d, ulPid=%d, pfInit=%d, pfUnload=%d\r\n",
                    enRatMode, ulPID, pfInit, pfUnload);

    NAS_DYNLOAD_LogRegisterInfo(enRatMode, ulPID, (VOS_UINT32)pfInit, (VOS_UINT32)pfUnload);

    (VOS_VOID)NAS_DYNLOAD_SaveCbRatInfo(enRatMode, ulPID, pfInit, pfUnload);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_DeRegLoadCallBack
 ��������  : ȥע��ص�����
 �������  : VOS_RATMODE_ENUM_UINT32             enRatMode
             VOS_UINT32                          ulPID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_DeRegLoadCallBack(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    VOS_UINT32                          ulPID
)
{
    NAS_TRACE_HIGH("NAS_DYNLOAD_DeRegLoadCallBack enRatMode=%d, ulPid=%d\r\n", enRatMode, ulPID);

    NAS_DYNLOAD_LogDeregisterInfo(enRatMode, ulPID);

    (VOS_VOID)NAS_DYNLOAD_ClearCbRatInfo(enRatMode, ulPID);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_UnloadAS
 ��������  : ж�ؽ�����API����
 �������  : VOS_RATMODE_ENUM_UINT32                                 enRatType
             NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_UnloadAS(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatType
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatType);

    /* ������Ч�Լ�� */
    if ( (VOS_RATMODE_BUTT <= enRatType)
      || (NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT <= enRatCombType) )
    {
        return VOS_FALSE;
    }

    /* �����Ҫж�صĽ���ģʽ�ѱ�ж�أ���ֱ�ӷ���ж�سɹ� */
    if (enRatType != NAS_DYNLOAD_GetCurRatInCached(enRatCombType))
    {
        return VOS_TRUE;
    }

     /* ������Ӧģ��ļ��غ��� */
    for ( i = 0; i < pstCbRatInfo->ulNum; i++ )
    {
        NAS_DYNLOAD_LogExcuteUnloadInfo(g_astNasDynloadCbRatInfo,
                                        enRatType,
                                        pstCbRatInfo->astModule[i].ulPid,
                                        (VOS_UINT32)pstCbRatInfo->astModule[i].pfUnloadCb);

        pstCbRatInfo->astModule[i].pfUnloadCb();
    }

    NAS_DYNLOAD_SetCurRatInCached(enRatCombType, VOS_RATMODE_BUTT);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_LoadAS
 ��������  : ���ؽ�����API����
 �������  : VOS_RATMODE_ENUM_UINT32                                 enRatType
             NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_DYNLOAD_LoadAS(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatType
)
{
    NAS_DYNLOAD_CB_RAT_INFO_STRU       *pstCbRatInfo = VOS_NULL_PTR;
    NAS_DYNLOAD_REBOOT_INFO_STRU        stRebootInfo;
    VOS_UINT32                          i;
    VOS_INT32                           lIsAsLoaded;
    DRV_RAT_MODE_ENUM                   enDrvRatMode;
    VOS_UINT32                          ulTime;

    pstCbRatInfo = NAS_DYNLOAD_GetSpecCbRatInfo(enRatType);

    lIsAsLoaded = MDRV_ERROR;

    PS_MEM_SET(&stRebootInfo, 0x00, sizeof(stRebootInfo));

    /* ����ǰ��Ҫ���صĽ��뼼����ת�����ڲ����� */

    /* ������Ч�Լ�� */
    if ( (VOS_RATMODE_BUTT <= enRatType)
      || (NAS_DYNLOAD_LOAD_RATCOMB_TYPE_BUTT <= enRatCombType) )
    {
        return VOS_FALSE;
    }

    /* �����Ҫ���صĽ���ģʽ�ѱ����أ���ֱ�ӷ��ؼ��سɹ� */
    if (enRatType == NAS_DYNLOAD_GetCurRatInCached(enRatCombType))
    {
        return VOS_TRUE;
    }

    /* ��ִ�е�ǰ����ģʽ��ж�ز��� */
    (VOS_VOID)NAS_DYNLOAD_UnloadAS(enRatCombType, NAS_DYNLOAD_GetCurRatInCached(enRatCombType));

    for ( ulTime = 0; ulTime < (NAS_DYNLOAD_GetTWMaxAttemptCount() + 1); ulTime++)
    {
        NAS_DYNLOAD_LogStartDrvLoadInfo(enRatType);

        enDrvRatMode = NAS_DYNLOAD_ConvertVosRatTypeToDrvType(enRatType);

        lIsAsLoaded = mdrv_loadas(enDrvRatMode);

        NAS_DYNLOAD_LogFinishDrvLoadInfo(g_astNasDynloadCbRatInfo, lIsAsLoaded);

        if (MDRV_OK == lIsAsLoaded)
        {
            break;
        }
    }

    if (MDRV_ERROR == lIsAsLoaded)
    {
        stRebootInfo.ulPid    = UEPS_PID_MSCC;
        stRebootInfo.enRatMode = enRatType;

        /* ��λ */
        NAS_DYNLOAD_SoftReboot(&stRebootInfo);

        return VOS_FALSE;
    }

    /* ������Ӧģ��ļ��غ��� */
    for ( i = 0; i < pstCbRatInfo->ulNum; i++ )
    {
        NAS_DYNLOAD_LogExcuteInitInfo(g_astNasDynloadCbRatInfo,
                                      enRatType,
                                      pstCbRatInfo->astModule[i].ulPid,
                                      (VOS_UINT32)pstCbRatInfo->astModule[i].pfInitCb);

        pstCbRatInfo->astModule[i].pfInitCb();
    }

    NAS_DYNLOAD_SetCurRatInCached(enRatCombType, enRatType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_GetCurRatInCached
 ��������  : ��ȡ��ǰcache�еĽ��뼼��
 �������  : NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
 �������  : ��
 �� �� ֵ  : VOS_RATMODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_RATMODE_ENUM_UINT32 NAS_DYNLOAD_GetCurRatInCached(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
)
{
    return g_enCurRatModeInCached[enRatCombType];
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_SetCurRatInCached
 ��������  : ����cache�еĽ��뼼��
 �������  : NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType
             VOS_RATMODE_ENUM_UINT32                                 enRatMode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_DYNLOAD_SetCurRatInCached(
    NAS_DYNLOAD_LOAD_RATCOMB_TYPE_ENUM_UINT32               enRatCombType,
    VOS_RATMODE_ENUM_UINT32                                 enRatMode
)
{
    g_enCurRatModeInCached[enRatCombType] = enRatMode;
}


/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 ��������  : ��ȡTW�Ƿ�̬���صı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_DYNLOAD_CTRL_STRU* NAS_DYNLOAD_GetDynloadCtrl(VOS_VOID)
{
    return &g_stNasDynloadCtrl;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 ��������  : ��ȡTW�Ƿ�̬���صı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_DYNLOAD_GetEnableDynloadTWFlg(VOS_VOID)
{
    return NAS_DYNLOAD_GetDynloadCtrl()->ucEnableDynloadTW;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_SetEnableDynloadTWFlg
 ��������  : ��ȡTW�Ƿ�̬���صı��
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_SetEnableDynloadTWFlg(
    VOS_UINT8                           ucEnableFlg
)
{
    NAS_DYNLOAD_GetDynloadCtrl()->ucEnableDynloadTW = ucEnableFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 ��������  : ��ȡTW�Ƿ�̬���صı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_DYNLOAD_GetTWMaxAttemptCount(VOS_VOID)
{
    return NAS_DYNLOAD_GetDynloadCtrl()->ucTWMaxAttemptCount;
}

/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_SetEnableDynloadTWFlg
 ��������  : ��ȡTW�Ƿ�̬���صı��
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_DYNLOAD_SetTWMaxAttemptCount(
    VOS_UINT8                           ucTWMaxAttemptCount
)
{
    NAS_DYNLOAD_GetDynloadCtrl()->ucTWMaxAttemptCount = ucTWMaxAttemptCount;
}


/*****************************************************************************
 �� �� ��  : NAS_DYNLOAD_GetEnableDynloadTWFlg
 ��������  : ��ȡTW�Ƿ�̬���صı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_DYNLOAD_CB_RAT_INFO_STRU* NAS_DYNLOAD_GetSpecCbRatInfo(
    VOS_RATMODE_ENUM_UINT32             enRatMode
)
{
    if (enRatMode >= VOS_RATMODE_BUTT)
    {
        return VOS_NULL_PTR;
    }

    return &g_astNasDynloadCbRatInfo[enRatMode];
}
#endif



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


