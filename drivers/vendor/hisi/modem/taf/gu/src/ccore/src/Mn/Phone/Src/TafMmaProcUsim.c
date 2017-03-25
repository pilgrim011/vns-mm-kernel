/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaProcUsim.c
  �� �� ��   : ����
  ��    ��   : s00261364
  ��������   : 2014��4��17��
  ����޸�   :
  ��������   : MMa����usim��д�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��17��
    ��    ��   : s00261364
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "TafMmaProcUsim.h"

#include "TafAppMma.h"
#include "MmaAppLocal.h"
#include "NasUsimmApi.h"
#include "TafMmaTimerMgmt.h"

#include "Taf_Status.h"
#include "TafStdlib.h"
#include "TafMmaPreProcAct.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_PROC_USIM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
VOS_UINT32                              g_ulMmaReadSimFileFlg;
extern STATUS_CONTEXT_STRU              g_StatusContext;

extern MMA_ME_PERSONALISATION_STATUS_STRU      g_stMmaMePersonalisationStatus;


/*****************************************************************************
  3 �궨��
*****************************************************************************/
/*lint -save -e958 */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateCallMode
 ��������  : ����call mode
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateCallMode( VOS_VOID )
{
    VOS_UINT32                          ulFdnExistFlag;
    VOS_UINT32                          ulSdnExistFlag;
    VOS_UINT32                          ulEcallDataExistFlag;
    VOS_UINT32                          ulUsimFdnStatus;
    VOS_UINT32                          ulCsimFdnStatus;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        NAS_USIMMAPI_FdnQuery(&ulUsimFdnStatus, &ulCsimFdnStatus);

        ulEcallDataExistFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_ECALL_DATA);
        ulFdnExistFlag       = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_FDN);

        /* 5.3.40.1 eCall Only support
            Requirement: Service n�� 89 and Service n�� 2 are "available" and FDN service is enabled in EFEST. */
        if ((VOS_TRUE                   == ulUsimFdnStatus)
         && (PS_USIM_SERVICE_AVAILIABLE == ulEcallDataExistFlag)
         && (PS_USIM_SERVICE_AVAILIABLE == ulFdnExistFlag))
        {
            TAF_SDC_SetCurCallMode(TAF_SDC_ECALL_ONLY);

            return;
        }

        ulSdnExistFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SDN);

        /* 5.3.40.2 eCall and Normal call support
           Requirement: Service n�� 89 and Service n�� 4 are "available". */
        if ((PS_USIM_SERVICE_AVAILIABLE == ulEcallDataExistFlag)
         && (PS_USIM_SERVICE_AVAILIABLE == ulSdnExistFlag))
        {
            TAF_SDC_SetCurCallMode(TAF_SDC_ECALL_AND_NORMAL_CALL);

            return;
        }
    }

    return;
}

#endif
/*****************************************************************************
 �� �� ��  : TAF_MMA_GetWaitSimFilesCnfFlg
 ��������  : ���������л�ȡ��ȡSIM���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡSIM���ļ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_MMA_GetWaitSimFilesCnfFlg(VOS_VOID)
{
    return g_ulMmaReadSimFileFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetWaitSimFilesCnfFlg
 ��������  : ��������������SIM���ļ��ظ����
 �������  : enSimFileCnfFlg - SIM���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    TAF_MMA_SetWaitSimFilesCnfFlg(
    TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
)
{
    g_ulMmaReadSimFileFlg |= enSimFileCnfFlg;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ClearWaitSimFilesCnfFlg
 ��������  : ���������������ȡSIM���ļ��ظ����
 �������  : enSimFileCnfFlg - SIM���ļ��ظ����
             ulAppType       - APP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��11��2��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_VOID  TAF_MMA_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
)
{
    switch (usEfId)
    {
        case USIMM_GSM_EFSPN_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_SIM_SPN_FILE_ID_FLG;
            break;

        case USIMM_USIM_EFSPN_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_USIM_SPN_FILE_ID_FLG;
            break;

        case USIMM_GSM_EFONS_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_CPHS_FILE_ID_FLG;
            break;

        case USIMM_GSM_EFPNN_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_SIM_PNN_FILE_ID_FLG;
            break;

        case USIMM_USIM_EFPNN_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_USIM_PNN_FILE_ID_FLG;
            break;

        case USIMM_GSM_EFOPL_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_SIM_OPL_FILE_ID_FLG;
            break;

        case USIMM_USIM_EFOPL_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_USIM_OPL_FILE_ID_FLG;
            break;

        case USIMM_GSM_EFSPDI_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_SIM_SPDI_FILE_ID_FLG;
            break;

        case USIMM_USIM_EFSPDI_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_USIM_SPDI_FILE_ID_FLG;
            break;

        case USIMM_GSM_EFCSP_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_CUSTOM_SRV_PROFILE_FILE_ID_FLG;
            break;

        case USIMM_USIM_EFAD_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_USIM_EFAD_FILE_ID_FLG;
            break;

        case USIMM_GSM_EFAD_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_SIM_EFAD_FILE_ID_FLG;
            break;

        case USIMM_USIM_EFEHPLMN_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_USIM_EFEHPLMN_FILE_ID_FLG;
            break;

        case USIMM_CDMA_EFRUIMID_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_CDMA_RUIMID_FILE_ID_FLG;
            break;

        case USIMM_CSIM_EFRUIMID_ID:
            g_ulMmaReadSimFileFlg &= ~TAF_MMA_READ_CSIM_RUIMID_FILE_ID_FLG;
            break;


        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ClearAllWaitSimFilesFlg_SwitchOn
 ��������  : ����������������ж�ȡSIM���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-03-13
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_MMA_ClearAllWaitSimFilesCnfFlg(VOS_VOID)
{
    g_ulMmaReadSimFileFlg = TAF_MMA_READ_USIM_FILE_FLG_NULL;
}

/*lint -e438 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MMA_UsimGetFileRspPreProc
 ��������  : MMA��ȡ�ļ��ظ�����
 �������  : USIMM_READFILE_CNF_STRU* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2015��3��13��
     ��    ��   : z00161729
     �޸�����   : at&t phaseII�޸�
   2.��    ��   : 2015��9��14��
     ��    ��   : z00359541
     �޸�����   : DTS2015090605112
*****************************************************************************/
VOS_UINT32 TAF_MMA_UsimGetFileRspPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_PH_USIM_SPN_CNF_STRU            stSpnTmp;
    MMA_GET_ICC_ID_ST                  *pstIccId     = VOS_NULL_PTR;
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg  = VOS_NULL_PTR;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    PS_MEM_SET(&stSpnTmp, 0xFF, sizeof(TAF_PH_USIM_SPN_CNF_STRU));

    pUsimTafMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;
    if (VOS_OK != USIMM_ChangePathToDefFileID(pUsimTafMsg->stCmdResult.enApptype, pUsimTafMsg->stFilePath.ulPathLen, pUsimTafMsg->stFilePath.acPath, &enFileID))
    {
        return VOS_FALSE;
    }

    pstIccId     = TAF_MMA_GetIccIdInfo();
    pUsimTafMsg  = (USIMM_READFILE_CNF_STRU*)pstMsg;

    TAF_MMA_ClearWaitSimFilesCnfFlg(enFileID);

    switch (enFileID)
    {
        case USIMM_USIM_EFSPN_ID:
        case USIMM_GSM_EFSPN_ID:
            if (MMA_SUCCESS == pUsimTafMsg->stCmdResult.ulResult)
            {
                if (pUsimTafMsg->usEfLen > sizeof(TAF_PH_USIM_SPN_CNF_STRU))
                {
                    MMA_MEM_CPY(&stSpnTmp, (VOS_UINT8*)(VOS_UINT32)(pUsimTafMsg->aucEf), sizeof(TAF_PH_USIM_SPN_CNF_STRU));
                }
                else
                {
                    MMA_MEM_CPY(&stSpnTmp, pUsimTafMsg->aucEf, pUsimTafMsg->usEfLen);
                }

                MMA_ReadSpnFileCnf((TAF_PH_USIM_SPN_CNF_STRU *)&stSpnTmp, enFileID);
            }
            break;

         case USIMM_GSM_EFONS_ID:
            TAF_MMA_ReadCphsFileCnf(pUsimTafMsg);
            break;

        case USIMM_ICCID_ID:
            MMA_MEM_SET(&(pstIccId->stIccId), 0, sizeof(TAF_PH_ICC_ID_STRU));
            MMA_MEM_CPY(pstIccId->stIccId.aucIccId,
                        pUsimTafMsg->aucEf,
                        pUsimTafMsg->usEfLen);
            pstIccId->stIccId.ucLen = (VOS_UINT8)pUsimTafMsg->usEfLen;
            TAF_MMA_ReadIccIdFileCnf();
            break;
        case USIMM_USIM_EFIMSI_ID:
        case USIMM_GSM_EFIMSI_ID:

            ulRet = MMA_CheckPin1SatusSimple();

            if ( MMA_NONEED_PIN1 == ulRet )
            {
                if (pUsimTafMsg->usEfLen< 10 )
                {
                    MMA_MEM_CPY(TAF_SDC_GetSimImsi(), pUsimTafMsg->aucEf, pUsimTafMsg->usEfLen);

                    /* ����Ƿ����� */
                    (VOS_VOID)MMA_CheckMePersonalisationStatus();
                }
            }
            break;
        case USIMM_USIM_EFPNN_ID:
        case USIMM_GSM_EFPNN_ID:
            TAF_MMA_ReadPnnFileCnf(pUsimTafMsg, enFileID);
            break;

        case USIMM_USIM_EFOPL_ID:
        case USIMM_GSM_EFOPL_ID:
            TAF_MMA_ReadOplFileCnf(pUsimTafMsg, enFileID);

            break;

        case USIMM_USIM_EFSPDI_ID:
        case USIMM_GSM_EFSPDI_ID:
            TAF_MMA_ReadSpdiFileCnf(pUsimTafMsg, enFileID);

            break;


        case USIMM_USIM_EFAD_ID:
        case USIMM_GSM_EFAD_ID:
            TAF_MMA_GetUsimHplmnMncLenFileInd(pUsimTafMsg);
            break;

        case USIMM_GSM_EFCSP_ID:
            TAF_MMA_RcvCustomerServiceProfileFile(pUsimTafMsg->stCmdResult.ulResult,
                                                  pUsimTafMsg->usEfLen,
                                                  pUsimTafMsg->aucEf);
            break;

 #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case USIMM_CSIM_EFRUIMID_ID:
        case USIMM_CDMA_EFRUIMID_ID:
            TAF_MMA_RcvUsimmReadRuimidFile(pUsimTafMsg);
            break;
#endif

        case USIMM_USIM_EFEHPLMN_ID:
            TAF_MMA_GetUsimEHplmnFileInd(pUsimTafMsg);
            break;

        case USIMM_ATTGSM_EFACTINGHPLMN_ID:
            TAF_MMA_GetSimActingHplmnFileInd(pUsimTafMsg);
            break;

        default:
            MMA_WARNINGLOG("TAf_MMA_UsimGetFileRspMsgProc():WARNING:UNKNOW EFID RECEIVE!");
            break;
    }

    if (TAF_MMA_READ_USIM_FILE_FLG_NULL == TAF_MMA_GetWaitSimFilesCnfFlg())
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_READ_SIM_FILES);
    }

    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    return VOS_TRUE;
    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
}
/*lint +e438 +e830*/

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadSimCphsOperNameFile
 ��������  : ���ڿ�����ȡCPHS���͵� SIM���� 6F14�ļ�,���ú�����֤������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��2��28��
    ��    ��   : b00269685
    �޸�����   : at&t�޸�
*****************************************************************************/
VOS_VOID  TAF_MMA_ReadSimCphsOperNameFile(VOS_VOID)
{
    VOS_UINT8    ucSimType;
    VOS_UINT32   ulRet;

    NAS_USIMM_GETFILE_INFO_STRU stGetFileInfo;


    ucSimType = 0;
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    /*ֻ��SIM���ſ���ʹ��CPHS�ļ�*/
    if (USIMM_CARD_SIM != ucSimType)
    {
        return;
    }
    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_GSM_EFONS_ID,
                                    0);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA, 0, &stGetFileInfo);

    TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_CPHS_FILE_ID_FLG);

    if (USIMM_API_SUCCESS != ulRet)
    {
        MMA_ERRORLOG("MMA_ReadSimCPHSOperNameStr():ERROR:Get File Req failed");
    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadSpnFile
 ��������  : ������ȡSPN�ļ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��28��
   ��    ��   : b00269685
   �޸�����   : at&t�޸�
*****************************************************************************/
VOS_VOID TAF_MMA_ReadSpnFile(VOS_VOID)
{
    VOS_UINT32                          ulSpnExistFlag;
    VOS_UINT8                           ucSimType;

    /* ��USIM�л�ȡSPN�ļ�,�ļ�ID:0x6F46 */
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
    ulSpnExistFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SPN);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */

    ucSimType = 0;

    if (PS_USIM_SERVICE_AVAILIABLE == ulSpnExistFlag)
    {
        (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

        (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_GSM_EFSPN_ID);

        TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_SIM_SPN_FILE_ID_FLG);

        if (USIMM_CARD_USIM == ucSimType)
        {
            (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_USIM_EFSPN_ID);
            TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_USIM_SPN_FILE_ID_FLG);
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadOplFile
 ��������  : ������ȡOPL�ļ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��9��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ReadOplFile(VOS_VOID)
{
    VOS_UINT8                           ucSimType;
    VOS_UINT32                          ulOplExistFlag;

    ucSimType      = 0;
    ulOplExistFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_LIST);

    if (PS_USIM_SERVICE_AVAILIABLE != ulOplExistFlag)
    {
        return;
    }

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_GSM_EFOPL_ID);

    TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_SIM_OPL_FILE_ID_FLG);

    if (USIMM_CARD_USIM == ucSimType)
    {
        (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_USIM_EFOPL_ID);
        TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_USIM_OPL_FILE_ID_FLG);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadPnnFile
 ��������  : ������ȡPNN�ļ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��9��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ReadPnnFile(VOS_VOID)
{
    VOS_UINT8                           ucSimType;
    VOS_UINT32                          ulPnnExistFlag;

    ucSimType      = 0;
    ulPnnExistFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_NTWRK_NAME);

    if (PS_USIM_SERVICE_AVAILIABLE != ulPnnExistFlag)
    {
        return;
    }

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_GSM_EFPNN_ID);

    TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_SIM_PNN_FILE_ID_FLG);

    if (USIMM_CARD_USIM == ucSimType)
    {
        (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_USIM_EFPNN_ID);
        TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_USIM_PNN_FILE_ID_FLG);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadSpdiFile
 ��������  : ������ȡSPDI�ļ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��3��3��
   ��    ��   : c00318887
   �޸�����   : at&t phaseII����
*****************************************************************************/
VOS_VOID TAF_MMA_ReadSpdiFile(VOS_VOID)
{
    VOS_UINT32                          ulSpdiExistFlag;
    VOS_UINT8                           ucSimType;

    ucSimType = 0;

    /* 31102Э������If service n��51 is "available", this file shall be present.*/
    ulSpdiExistFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SP_DISP_INFO);

    if (PS_USIM_SERVICE_AVAILIABLE != ulSpdiExistFlag)
    {
        return;
    }

    /* ��ȡ�ļ�,����������ʱ�� */
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_GSM_EFSPDI_ID);

    TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_SIM_SPDI_FILE_ID_FLG);

    if (USIMM_CARD_USIM == ucSimType)
    {
        (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_GUTL_APP, USIMM_USIM_EFSPDI_ID);
        TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_USIM_SPDI_FILE_ID_FLG);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn
 ��������  : ������6F15�ļ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ��� ��
                 Client ID �� PID��ת������ ����η�װ�ɽṹ�塣
  3.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
*****************************************************************************/
VOS_VOID TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn(VOS_VOID)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));

    /* ����ѡ��˵����ƹ���δʹ�� */
    if (VOS_TRUE != TAF_MMA_GetNetworkSelectionMenuEnableFlg())
    {
        return;
    }

    /* ���ļ���PIN�뱣����ֻ�п�״̬ΪAVAILBALEʱ�Ŷ�ȡ������ֱ�ӷ���VOS_ERR*/
    if (MMA_NONEED_PIN1 != MMA_CheckPin1SatusSimple())
    {
        return;
    }

    /* ��6F15�ļ������ļ�����Ϊtransparent�����Լ�¼��Ϊ0 */
    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_GSM_EFCSP_ID,
                                    0);

    if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA,
                                              0,
                                              &stGetFileInfo))
    {
        return;
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SendUsimFileReq
 ��������  : ����������Ϣȥ��ȡUSIM���ļ�
 �������  : USIMM_APP_TYPE_ENUM_UINT32          enAppType
             VOS_UINT16                          usEfId
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��3��3��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                    enAppType,
                    usEfId,
                    0);

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA, 0, &stGetFileInfo);

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadCphsFileCnf
 ��������  : CPHS SIM�ϱ�6f14 OperNameStr�ļ�������
 �������  : USIMM_READFILE_CNF_STRU *pUsimTafMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��01��09��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��2��26��
    ��    ��   : b00269685
    �޸�����   : at&t�޸�
*****************************************************************************/
VOS_VOID   TAF_MMA_ReadCphsFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
)
{
    TAF_SDC_CPHS_FILE_INFO_STRU        *pstChpsFileInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pCPHSOperNameStr = VOS_NULL_PTR;
    VOS_UINT8                           ucSpareBitNumInLastOctet;
    VOS_UINT32                          ulSrcStrLen;
    VOS_UINT32                          ulDestStrLen;
    VOS_UINT8                           aucOperatorName[TAF_SDC_MAX_OPER_NAME_NUM];

    pstChpsFileInfo  = TAF_SDC_GetChpsFileInfo();
    pCPHSOperNameStr = aucOperatorName;
    PS_MEM_SET(aucOperatorName, 0xFF, TAF_SDC_MAX_OPER_NAME_NUM);

    if ((MMA_SUCCESS != pUsimTafMsg->stCmdResult.ulResult)
     || (0xff == pUsimTafMsg->aucEf[0]))
    {
        return;
    }

    if (0 == pUsimTafMsg->usEfLen)
    {
        MMA_ERRORLOG("TAF_MMA_ReadCphsFileCnf(): usEfLen is 0");
        return;
    }

    if (pUsimTafMsg->usEfLen > TAF_SDC_MAX_OPER_LONG_NAME_LEN)
    {
        MMA_MEM_CPY(aucOperatorName, (VOS_UINT8*)(VOS_UINT32)(pUsimTafMsg->aucEf), TAF_SDC_MAX_OPER_LONG_NAME_LEN);
    }
    else
    {
        MMA_MEM_CPY(aucOperatorName, pUsimTafMsg->aucEf, pUsimTafMsg->usEfLen);
    }

    for (ulSrcStrLen = 0 ;ulSrcStrLen < TAF_SDC_MAX_OPER_LONG_NAME_LEN ;  ulSrcStrLen++)
    {
         if (0xFF == pCPHSOperNameStr[ulSrcStrLen])
         {
            break;
         }
    }

    /* �� bit 8Ϊ0��Gsm 7bitת��Ϊѹ���� 7bit���� */
    ulDestStrLen = (VOS_UINT32)(((ulSrcStrLen * 7) + 7) / 8); /* ѹ������ֽڸ��� */

    if (VOS_OK != TAF_STD_Pack7Bit(pCPHSOperNameStr,
                                    ulSrcStrLen,
                                    0,
                                    pstChpsFileInfo->stCPHSOperName.aucOperatorName,
                                    &ulDestStrLen))
    {
        MMA_ERRORLOG("MMA_ReadCPHSOperNameStrFileCnf():Error:TAF_STD_Pack7Bit failed!");
        return;
    }


    /* octet3: ext 1,coding scheme:Gsm 7bit, Add CI:0,Number of spare bits in last octet */
    ucSpareBitNumInLastOctet = (VOS_UINT8)((ulDestStrLen * 8) - (ulSrcStrLen * 7));

    pstChpsFileInfo->stCPHSOperName.bitExt    = 0x01;
    pstChpsFileInfo->stCPHSOperName.ucLength  = (VOS_UINT8)ulDestStrLen;
    pstChpsFileInfo->stCPHSOperName.bitCoding = 0;
    pstChpsFileInfo->stCPHSOperName.bitSpare  = ucSpareBitNumInLastOctet;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_USIMRefreshFileProc
 ��������  : MMA���տ��ļ�����ָʾ��Ϣ�����Ӧ�ļ��ɹ���Ĵ���
 �������  : VOS_UINT16 usEfId
             VOS_UINT16 usEfLen
             VOS_UINT8 *pucEf
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��09��18��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��05��7��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL BG�����޸�
  3.��    ��   : 2012��6��13��
    ��    ��   : l60609
    �޸�����   : AT&T&DCM:����6F15�ļ��Ĵ���
  4.��    ��   : 2012��12��26��
    ��    ��   : ���� /z00214637
    �޸�����   : PS_USIM_GET_FILE_RLT_SUCCESS�滻ΪVOS_OK
*****************************************************************************/
VOS_VOID TAF_MMA_USIMRefreshFileProc(
    VOS_UINT16                          usEfId,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    USIMM_READFILE_CNF_STRU           *pUsimTafMsg;
    VOS_UINT8                         *pucImsi = VOS_NULL_PTR;
    MMA_GET_ICC_ID_ST                 *pstIccId = VOS_NULL_PTR;

    pucImsi  = TAF_SDC_GetSimImsi();
    pstIccId = TAF_MMA_GetIccIdInfo();

    switch (usEfId)
    {
        case USIMM_GSM_EFONS_ID:
            /*lint -e961*/
            pUsimTafMsg = (USIMM_READFILE_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, (VOS_UINT32)(sizeof(USIMM_READFILE_CNF_STRU) - 4 + usEfLen));
            /*lint +e961*/
            if (VOS_NULL_PTR == pUsimTafMsg)
            {
                MMA_ERRORLOG("MMA_USIMReadRefreshFileProc():ERROR:MALLOC FAIL");
                return;
            }
            /*lint -e961*/
            PS_MEM_SET(pUsimTafMsg, 0, (VOS_UINT32)(sizeof(USIMM_READFILE_CNF_STRU) - 4 + usEfLen));
            /*lint +e961*/


           pUsimTafMsg->stCmdResult.ulResult = MMA_SUCCESS;
           pUsimTafMsg->usEfLen  = usEfLen;
           PS_MEM_CPY(pUsimTafMsg->aucEf, pucEf, usEfLen);

           TAF_MMA_ReadCphsFileCnf(pUsimTafMsg);

           PS_MEM_FREE(WUEPS_PID_MMA, pUsimTafMsg);
           break;

        case USIMM_ICCID_ID:
            MMA_MEM_SET(&(pstIccId->stIccId), 0, sizeof(TAF_PH_ICC_ID_STRU));
            MMA_MEM_CPY(pstIccId->stIccId.aucIccId,
                        pucEf,
                        usEfLen);
            pstIccId->stIccId.ucLen = (VOS_UINT8)usEfLen;
            TAF_MMA_ReadIccIdFileCnf();
            break;

        case USIMM_USIM_EFIMSI_ID:
        case USIMM_GSM_EFIMSI_ID:
            /* �ж�IMSI�Ƿ�ı� */
            if (0 != VOS_MemCmp(pucImsi, pucEf, NAS_MAX_IMSI_LENGTH))
            {
                if (TAF_MMA_FSM_MAIN != TAF_MMA_GetCurrFsmId())
                {
                    TAF_MMA_SndInterUsimChangeInd();

                    break;
                }

                if (STA_FSM_NULL == g_StatusContext.ulFsmState)
                {
                   break;
                }

                TAF_MMA_SndInterUsimChangeInd();
            }

            MMA_WARNINGLOG("MMA_USIMReadRefreshFileProc():WARNING:Refresh File Id IMSI");
            break;

        case USIMM_USIM_EFPNN_ID:
        case USIMM_USIM_EFPNNI_ID:
            MMA_INFOLOG("MMA_USIMReadRefreshFileProc():INFO:Refresh File PNN");
            break;

        case USIMM_USIM_EFOPL_ID:
        case USIMM_GSM_EFOPL_ID:
            MMA_INFOLOG("MMA_USIMReadRefreshFileProc():INFO:Refresh File OPL");
            break;

        case USIMM_GSM_EFCSP_ID:
            TAF_MMA_RcvCustomerServiceProfileFile(VOS_OK, usEfLen, pucEf);
            break;

        case USIMM_ATTUSIM_EFRATMODE_ID:
            TAF_MMA_RcvRatModeFileRefresh(usEfLen, pucEf);
            break;

        default:
            MMA_WARNINGLOG("MMA_USIMReadRefreshFileProc():WARNING:UNKNOW EFID RECEIVE!");
            break;
    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UsimRefreshIndFileListChangedMsgProc
 ��������  : MMA���տ��ļ�refresh��Ϣָʾ�ض��ļ��������µĴ���
 �������  : PS_USIM_REFRESH_IND_STRU* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��17��
    ��    ��   : x00115505
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��29��
    ��    ��   : l60609
    �޸�����   : AT&T&DCM������ATT�ļ��Ĵ���
  3.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  4.��    ��   : 2013��6��4��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
  6.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����ust/est/fdn/sdn�ļ�ˢ��ָʾ����
  7.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ�
  8.��    ��   : 2015��2��15��
    ��    ��   : c00318887
    �޸�����   : AT&T phaseII ����AT^FILECHANGE�ϱ���0x6FCD,0x6FC5,0x6FC6�ļ����µĴ���
*****************************************************************************/
VOS_VOID TAF_MMA_UsimRefreshIndFileListChangedMsgProc(USIMM_STKREFRESH_IND_STRU *pUsimTafMsg)
{
    VOS_UINT16                          usEfId;
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          i;
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT8                          *pucOldImsi;
    VOS_UINT8                           aucNewImsi[TAF_SDC_MAX_IMSI_LEN];
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                           aucIMSIM[NAS_MAX_IMSIM_DATA_LEN];

    PS_MEM_SET(aucIMSIM, 0x00, sizeof(aucIMSIM));
#endif

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));


    pucEf = VOS_NULL_PTR;

    usEfId    = USIMM_DEF_FILEID_BUTT;
    ulEfLen   = 0;

    /*���ζ�ȡ�ϱ���refresh�ļ�*/
    for (i = 0; i < pUsimTafMsg->usEfNum; i++)
    {
        usEfId = pUsimTafMsg->astEfId[i].usFileId;

        switch (usEfId)
        {
            case USIMM_USIM_EFSPN_ID:
            case USIMM_GSM_EFSPN_ID:
                TAF_MMA_ReadSpnFile();

                break;

            case USIMM_USIM_EFSPDI_ID:
            case USIMM_GSM_EFSPDI_ID:
                TAF_MMA_ReadSpdiFile();

                break;

            case USIMM_USIM_EFPNN_ID:
            case USIMM_GSM_EFPNN_ID:
                TAF_MMA_ReadPnnFile();

                break;

            case USIMM_USIM_EFOPL_ID:
            case USIMM_GSM_EFOPL_ID:
                TAF_MMA_ReadOplFile();

                break;


#if (FEATURE_ON == FEATURE_ECALL)
            case USIMM_USIM_EFUST_ID:
            case USIMM_GSM_EFSST_ID:
            case USIMM_USIM_EFEST_ID:
                (VOS_VOID)TAF_MMA_ProcPihUsimRefreshIndEfUstFileChanged_PreProc();
                break;
#endif

            /* ���IMSI������������Ϳ�״̬�����������ҵ��������ʱ�� */
            case USIMM_USIM_EFIMSI_ID:
            case USIMM_GSM_EFIMSI_ID:
                pucOldImsi      = TAF_SDC_GetLastSimImsi();
                PS_MEM_SET(aucNewImsi, 0, sizeof(aucNewImsi));
                if (USIMM_API_SUCCESS == USIMM_GetCardIMSI(aucNewImsi))
                {
                    if (0 != VOS_MemCmp(pucOldImsi, aucNewImsi, TAF_SDC_MAX_IMSI_LEN))
                    {
                        if (VOS_TRUE == TAF_SDC_GetCsEccExistFlg())
                        {
                            /* ����CSҵ����������ʱ���ȴ�CSҵ�������ػ� */
                            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN, TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN);
                        }
                        else
                        {
                            TAF_MMA_SndInterUsimChangeInd();
                        }
                    }
                }
                break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case USIMM_CSIM_EFEPRL_ID:
            case USIMM_CDMA_EFEPRL_ID:
            case USIMM_CDMA_EFPRL_ID:
            case USIMM_CSIM_EFPRL_ID:
                TAF_MMA_SndInterUsimChangeInd();
                break;
            case USIMM_CDMA_EFIMSIM_ID:
            case USIMM_CSIM_EFIMSIM_ID:
                pucOldImsi      = TAF_SDC_GetCsimImsi();
                PS_MEM_SET(aucNewImsi, 0x00, sizeof(aucNewImsi));
                if (USIMM_API_SUCCESS != USIMM_GetCdmaIMSIM(aucIMSIM))
                {
                    MMA_WARNINGLOG("USIMM_GetCdmaIMSIM:Get Imsim Failed");

                    break;
                }

                (VOS_VOID)TAF_SDC_ConvertCImsiBcdCode(aucIMSIM, aucNewImsi);

                if (0 != VOS_MemCmp(pucOldImsi, aucNewImsi, TAF_SDC_MAX_IMSI_LEN))
                {
                    PS_MEM_CPY(pucOldImsi, aucNewImsi, TAF_SDC_MAX_IMSI_LEN);

                    if (VOS_TRUE == TAF_SDC_GetCsEccExistFlg())
                    {
                        /* ����CSҵ����������ʱ���ȴ�CSҵ�������ػ� */
                        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN, TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN);
                    }
                    else
                    {
                        TAF_MMA_SndInterUsimChangeInd();
                    }
                }
                break;
#endif
            default:
                ulResult = NAS_USIMMAPI_GetCachedFile(usEfId, &ulEfLen, &pucEf, pUsimTafMsg->astEfId[i].enAppType);

                if (USIMM_API_SUCCESS != ulResult)
                {
                    /*����ǰ�ļ�ʧ�ܣ���ȡ��һ���ļ�*/
                    MMA_ERRORLOG("MMA_UsimRefreshFileIndMsgProc():ERROR:READ FILE FAIL!");
                    continue;
                }

                /* ���ӿ�ά�ɲ� */
                TAF_MMA_SndOmGetCacheFile(usEfId, ulEfLen, pucEf);


                /*��ȡ�ļ��ɹ���MMA�ڲ�����Ӧ����*/
                TAF_MMA_USIMRefreshFileProc(usEfId, (VOS_UINT16)ulEfLen, pucEf);

                break;
        }

    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadIccIdFileCnf
 ��������  : �յ�USIM�ظ��ϱ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��8��23��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���
  2.��    ��   : 2007��9��26��
    ��    ��   : luojian id:107747
    �޸�����   : ���ⵥ�ţ�A32D12931,��ѯAPI�ӿ����Ӵ������ϱ�
  3.��    ��   : 2015��2��27��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_VOID TAF_MMA_ReadIccIdFileCnf(VOS_VOID)
{
    MMA_GET_ICC_ID_ST                  *pstIccId = VOS_NULL_PTR;

    MMA_NORMAILLOG("TAF_MMA_ReadIccIdFileCnf():NORMAL:GET ICC ID SUCCESSFUL");

    pstIccId = TAF_MMA_GetIccIdInfo();

    MMA_ParaQueryReport(pstIccId->ClientId,
                        pstIccId->OpId,
                        TAF_PH_ICC_ID,
                        TAF_ERR_NO_ERROR,
                        (VOS_VOID*)(&pstIccId->stIccId));

    /*ֹͣ��ʱ��*/
    MMA_StopInternalTimer();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadSpdiFileCnf
 ��������  : MMA��ȡSPDI�ļ��ظ�����
 �������  : pUsimTafMsg  - ��Ϣ����
             enUpdateType - usim app����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��3��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ReadSpdiFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
)
{
    TAF_SDC_SPDI_FILE_INFO_STRU        *pstSpnFileInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucCurrentPos  = VOS_NULL_PTR;
    VOS_UINT8                           ulValueLen;
    TAF_SDC_SIM_FORMAT_PLMN_ID          stSimPlmn;
    VOS_UINT32                          ulIdx;

    ulValueLen = 0;
    PS_MEM_SET(&stSimPlmn, 0 ,sizeof(stSimPlmn));

    /* �����ȡ�ļ�ʧ�� */
    if (MMA_SUCCESS != pUsimTafMsg->stCmdResult.ulResult)
    {
       MMA_ERRORLOG ("TAF_MMA_ReadSpdiFileCnf(): Read usim file failed");
       return;
    }

    if (0 == pUsimTafMsg->usEfLen)
    {
        MMA_ERRORLOG("TAF_MMA_ReadSpdiFileCnf(): usEfLen is 0");
        return;
    }

    pstSpnFileInfo = TAF_SDC_GetUsimSpdiFileInfo();

    if (USIMM_GSM_EFSPDI_ID == enFileID)
    {
        pstSpnFileInfo = TAF_SDC_GetSimSpdiFileInfo();
    }

    pucCurrentPos = pUsimTafMsg->aucEf;

    if (TAF_SPDI_PLMN_LIST_IEI != *pucCurrentPos)
    {
        MMA_ERRORLOG("TAF_MMA_ReadSpdiFileCnf(): TAF_SPDI_PLMN_LIST_IEI not found");
        return;
    }

    /* ָ�򳤶� */
    pucCurrentPos++;

    ulValueLen = *pucCurrentPos;

    pstSpnFileInfo->ucServiceProviderPlmnNum = (ulValueLen / 3);

    if (TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM < pstSpnFileInfo->ucServiceProviderPlmnNum)
    {
        pstSpnFileInfo->ucServiceProviderPlmnNum = TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM;
    }

    /* ָ���һ��PLMN */
    pucCurrentPos++;

    /*lint -e670 -e662*/
    for (ulIdx = 0; ulIdx < pstSpnFileInfo->ucServiceProviderPlmnNum; ulIdx++)
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pucCurrentPos, TAF_SDC_SIM_FORMAT_PLMN_LEN);  /* [false alarm]: �����Ѷ�̬���� */
        TAF_SDC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &pstSpnFileInfo->astSeriveProviderPlmn[ulIdx]);

        pucCurrentPos += TAF_SDC_SIM_FORMAT_PLMN_LEN;
    }
    /*lint -e670 -e662*/

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadPnnFileCnf
 ��������  : MMA��ȡPnn�ļ��ظ�����
 �������  : pUsimTafMsg  - ��Ϣ����
             enUpdateType - usim app����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��15��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ReadPnnFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
)
{
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucCurrentPos  = VOS_NULL_PTR;
    VOS_UINT8                           ucEfLen;
    VOS_UINT8                           ucValueLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulPnnNum;

    pstPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    ucEfLen        = 0;
    ucValueLen     = 0;
    ulPnnNum       = 0;

    if (USIMM_GSM_EFPNN_ID == enFileID)
    {
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }

    /*�����ȡ�ļ�ʧ��*/
    if (MMA_SUCCESS != pUsimTafMsg->stCmdResult.ulResult)
    {
        MMA_ERRORLOG("TAF_MMA_ReadPnnFileCnf(): Read usim pnn file failed");
        return;
    }

    if (0 == pUsimTafMsg->usEfLen)
    {
        MMA_ERRORLOG("TAF_MMA_ReadPnnFileCnf(): usEfLen is 0");
        return;
    }

    pstPnnFileInfo->ulPnnRecordNum = 0;
    pstPnnFileInfo->ulPnnEfLen     = pUsimTafMsg->usEfLen;

    ucEfLen = (VOS_UINT8)pUsimTafMsg->usEfLen;

    /* 24008 10.5.3.5a ��Network Name��ʽ����
      octet 1 Network Name IEI
      octet 2 Length of Network Name contents
      octet 3 ext1(bit8)  coding scheme(bit7-bit5)  AddCI(bit4)  Number of spare bits in last octet(bit3-bit1)
    */
    for (i = 0; i < pUsimTafMsg->ucTotalNum; i++)
    {
        pucCurrentPos = pUsimTafMsg->aucEf + (ucEfLen * i);

        if (FULL_NAME_IEI != *pucCurrentPos++)
        {
            continue;
        }

        ucValueLen = *pucCurrentPos - 1;
        pucCurrentPos++;

        /* ��ȡ���� */
        pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameLong.ucLength  = ucValueLen;
        pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameLong.bitExt    = (*pucCurrentPos & 0x80) >> TAF_SDC_OCTET_MOVE_SEVEN_BITS;
        pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameLong.bitCoding = (0x70 & *pucCurrentPos) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
        pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameLong.bitAddCi  = *pucCurrentPos & 0x08;
        pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameLong.bitSpare  = *pucCurrentPos & 0x07;
        pucCurrentPos++;

        if (TAF_SDC_MAX_OPER_LONG_NAME_LEN < ucValueLen)
        {
            PS_MEM_CPY(pstPnnFileInfo->astPnnRecordInfo[i].stOperatorNameLong.aucOperatorName, pucCurrentPos, TAF_SDC_MAX_OPER_LONG_NAME_LEN);
        }
        else
        {
            PS_MEM_CPY(pstPnnFileInfo->astPnnRecordInfo[i].stOperatorNameLong.aucOperatorName, pucCurrentPos, ucValueLen);
        }

        pucCurrentPos += ucValueLen;

        /* ��ȡ���� */
        if (SHORT_NAME_IEI == *pucCurrentPos++)
        {
            ucValueLen = *pucCurrentPos - 1;
            pucCurrentPos++;

            pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameShort.ucLength   = ucValueLen;
            pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameShort.bitExt     = (*pucCurrentPos & 0x80) >> TAF_SDC_OCTET_MOVE_SEVEN_BITS;
            pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameShort.bitCoding  = (0x70 & *pucCurrentPos) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
            pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameShort.bitAddCi   = *pucCurrentPos & 0x08;
            pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].stOperatorNameShort.bitSpare   = *pucCurrentPos & 0x07;
            pucCurrentPos++;

            if (TAF_SDC_MAX_OPER_SHORT_NAME_LEN < ucValueLen)
            {
                PS_MEM_CPY(pstPnnFileInfo->astPnnRecordInfo[i].stOperatorNameShort.aucOperatorName, pucCurrentPos, TAF_SDC_MAX_OPER_SHORT_NAME_LEN);
            }
            else
            {
                PS_MEM_CPY(pstPnnFileInfo->astPnnRecordInfo[i].stOperatorNameShort.aucOperatorName, pucCurrentPos, ucValueLen);
            }

            pucCurrentPos += ucValueLen;
        }

        /* ��ȡadditional��Ϣ */
        if (PLMN_ADDITIONAL_INFO_IEI == *pucCurrentPos++)
        {
            ucValueLen = *pucCurrentPos++;

            if (TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN < ucValueLen)
            {
                ucValueLen = TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN;
            }

            pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].ucPlmnAdditionalInfoLen = ucValueLen;

            PS_MEM_CPY(pstPnnFileInfo->astPnnRecordInfo[ulPnnNum].aucPlmnAdditionalInfo, pucCurrentPos, ucValueLen);
        }

        pstPnnFileInfo->ulPnnRecordNum++;
        ulPnnNum++;
    }
}

/*lint -e661 -e662*/
/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadOplFileCnf
 ��������  : MMA��ȡPnn�ļ��ظ�����
 �������  : pUsimTafMsg  - ��Ϣ����
             enUpdateType - usim app����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��15��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ReadOplFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
)
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucEfLen;
    VOS_UINT8                          *pucContent = VOS_NULL_PTR;
    VOS_UINT32                          i;
    TAF_SDC_SIM_FORMAT_PLMN_ID          stSimPlmn;

    pstOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
    PS_MEM_SET(&stSimPlmn, 0, sizeof(stSimPlmn));

    if (USIMM_GSM_EFOPL_ID == enFileID)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
    }

    /*�����ȡ�ļ�ʧ��*/
    if (MMA_SUCCESS != pUsimTafMsg->stCmdResult.ulResult)
    {
       MMA_ERRORLOG("TAF_MMA_ReadOplFileCnf(): Read usim opl file failed");

       return;
    }

    if (0 == pUsimTafMsg->usEfLen)
    {
        MMA_ERRORLOG("TAF_MMA_ReadOplFileCnf(): usEfLen is 0");
        return;
    }

    ucEfLen    = (VOS_UINT8)pUsimTafMsg->usEfLen;
    pucContent = pUsimTafMsg->aucEf;

    pstOplFileInfo->ulOplRecordNum = pUsimTafMsg->ucTotalNum;
    pstOplFileInfo->ulOplEfLen     = (VOS_UINT32)pUsimTafMsg->usEfLen;

    for (i = 0; i < pstOplFileInfo->ulOplRecordNum; i++)
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pucContent, TAF_SDC_SIM_FORMAT_PLMN_LEN);  /* [false alarm]: �����Ѷ�̬���� */
        TAF_SDC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &pstOplFileInfo->astOplRecordInfo[i].stPlmnId);

        pstOplFileInfo->astOplRecordInfo[i].usLacRangeLow  =  (*(pucContent + TAF_SDC_OCTET_MOVE_THREE_BYTES) << TAF_SDC_OCTET_MOVE_EIGHT_BITS) + (*(pucContent + TAF_SDC_OCTET_MOVE_FOUR_BYTES));/* [false alarm]: �����Ѷ�̬���� */
        pstOplFileInfo->astOplRecordInfo[i].usLacRangeHigh =  (*(pucContent + TAF_SDC_OCTET_MOVE_FIVE_BYTES) << TAF_SDC_OCTET_MOVE_EIGHT_BITS) + (*(pucContent + TAF_SDC_OCTET_MOVE_SIX_BYTES));/* [false alarm]: �����Ѷ�̬���� */
        pstOplFileInfo->astOplRecordInfo[i].usPnnIndex     =  pucContent[TAF_SDC_OCTET_MOVE_SEVEN_BYTES];                  /* [false alarm]: �����Ѷ�̬���� */

        pucContent += ucEfLen;
    }

    return;

}
/*lint +e661 +e662*/

/*****************************************************************************
 �� �� ��  : MMA_ReadSPNFileCnf
 ��������  : USIM�ϱ�SPN�ļ�������
 �������  : TAF_PH_USIM_SPN_CNF_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��9��15��
    ��    ��   : liuyang
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��11��20��
    ��    ��   : ouyang fei 00132663
    �޸�����   : ���ⵥAT2D06705������ AT^SPN ����֧��
  3.��    ��   : 2008��12��29��
    ��    ��   : ouyang fei 00132663
    �޸�����   : ���ⵥAT2D07646��AT^SPN����disp_rplmn�����ϱ�b1b2��λ��
  4.��    ��   : 2009��8��23��
    ��    ��   : l0013025
    �޸�����   : ���ⵥAT2D13562��AT^SPN����disp_rplmn�����޸�Ϊ�ϱ�b1λ,���˱���һ�¡�
  5.��    ��   : 2009��10��12��
    ��    ��   : l0013025
    �޸�����   : ���ⵥAT2D15082��AT^SPN����disp_rplmn�����޸�Ϊ�ϱ�b1λ,��DispCode������λ����Cops��ʾ�ж���
  6.��    ��   : 2010��02��02��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��: AT2D16519,SPN��0x00�ضϴ���UCCII������Ҫ������ʾ
  7.��    ��   : 2015��2��27��
    ��    ��   : b00269685
    �޸�����   : at&t�޸�
*****************************************************************************/
VOS_VOID MMA_ReadSpnFileCnf(
    TAF_PH_USIM_SPN_CNF_STRU           *pMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
)
{
    TAF_UINT8                           ulSrcStrLen;
    TAF_SDC_SPN_FILE_INFO_STRU         *pstSpnFileInfo = VOS_NULL_PTR;

    pstSpnFileInfo = TAF_SDC_GetUsimSpnFileInfo();

    if (USIMM_GSM_EFSPN_ID == enFileID)
    {
        pstSpnFileInfo = TAF_SDC_GetSimSpnFileInfo();
    }

    /* Ŀǰʹ�� b1b2 �� */
    pstSpnFileInfo->ucDispRplmnMode = pMsg->ucDispRplmnMode & 0x03;

    for (ulSrcStrLen = 0; ulSrcStrLen < TAF_PH_SPN_NAME_MAXLEN; ulSrcStrLen++)
    {
         if (0xFF == pMsg->aucSpnName[ulSrcStrLen])
         {
            break;
         }
    }

    if (0 == ulSrcStrLen)
    {
        /* ������Ϊ0����Ҫ������ */
        pstSpnFileInfo->stSpnOperName.ucLength = 0;

        return;
    }

    pstSpnFileInfo->stSpnOperName.ucLength = (VOS_UINT8)ulSrcStrLen;

    pstSpnFileInfo->stSpnOperName.bitCoding = TAF_PH_GSM_7BIT_DEFAULT;

    /* �����ʽ */
    if ((0x80 == pMsg->aucSpnName[0])
     || (0x81 == pMsg->aucSpnName[0])
     || (0x82 == pMsg->aucSpnName[0]))
    {
        pstSpnFileInfo->stSpnOperName.bitCoding = TAF_PH_RAW_MODE;
    }

    /* �������� */
    PS_MEM_CPY(pstSpnFileInfo->stSpnOperName.aucOperatorName, &pMsg->aucSpnName[0], ulSrcStrLen);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCustomerServiceProfileFile
 ��������  : ����6F15�ļ�
 �������  : VOS_UINT32                          ulRslt,
             VOS_UINT16                          usEfLen,
             VOS_UINT8                          *pucEf
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� /z00214637
    �޸�����   : PS_USIM_GET_FILE_RLT_SUCCESS�滻ΪVOS_OK
*****************************************************************************/
VOS_VOID TAF_MMA_RcvCustomerServiceProfileFile(
    VOS_UINT32                          ulRslt,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* Ԥ�������������Ҫ��һ������ */
    if (VOS_TRUE == TAF_MMA_RcvCustomerServiceProfileFile_PreProc(usEfLen, pucEf))
    {
        return;
    }

    /* ����6F15�ļ� */
    TAF_MMA_ProcCustomerServiceProfileFile();

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadRuimidFile
 ��������  : ������ȡuimid�ļ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��14��
    ��    ��   : y00322978
    �޸�����   :
*****************************************************************************/
VOS_VOID TAF_MMA_ReadRuimidFile( VOS_VOID )
{
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;

    enCsimType                          = TAF_SDC_GetCsimType();

    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        return;
    }

    if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFRUIMID_ID);
        TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_CDMA_RUIMID_FILE_ID_FLG);

        return;
    }

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        (VOS_VOID)TAF_MMA_SendUsimFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFRUIMID_ID);
        TAF_MMA_SetWaitSimFilesCnfFlg(TAF_MMA_READ_CSIM_RUIMID_FILE_ID_FLG);

        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvUsimmReadRuimidFile
 ��������  : ��ȡruimid���ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_RcvUsimmReadRuimidFile(
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg
)
{
    /* Read file fail */
    if (MMA_SUCCESS != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
       MMA_ERRORLOG("TAF_MMA_RcvUsimmReadRuimidFile: Read RUIMID FAIL");
       return;
    }

    if (0 == pstUsimmReadCnfMsg->usEfLen)
    {
        MMA_ERRORLOG("TAF_MMA_RcvUsimmReadRuimidFile(): Parse Content Failed! usEfLen is 0");
        return;
    }

    if (pstUsimmReadCnfMsg->usEfLen > TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT)
    {
        MMA_ERRORLOG("TAF_MMA_RcvUsimmReadRuimidFile(): Parse Content Failed! usEfLen > 8");
        return;
    }

    PS_MEM_CPY( TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.aucRuimid,
                pstUsimmReadCnfMsg->aucEf,
                TAF_SDC_MIN(TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT, pstUsimmReadCnfMsg->usEfLen));
}

#endif
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



