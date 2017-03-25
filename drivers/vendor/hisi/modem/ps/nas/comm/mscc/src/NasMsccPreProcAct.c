/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMsccPreProcAct.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��01��26��
  ��������   : MSCC moduleԤ�����¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��26��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MsccMmcInterface.h"
#include "MmaMsccInterface.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaMsccInterface.h"
#endif
#include "NasMsccPreProcAct.h"
#include "NasMsccSndMma.h"
#include "NasMsccSndImsa.h"
#include "NasMsccSndMmc.h"
#include "NasMsccCtx.h"
#include "NasMsccSndXsd.h"
#include "NasMsccSndHsd.h"
#include "hsd_mscc_pif.h"
#include "NasMsccComFunc.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMntn.h"
#include "NasMsccFsmMain.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccProcNvim.h"
#include "NasMsccFsmBsrTbl.h"
#include "NasMsccFsmSysAcqTbl.h"
#include "NasMsccMntn.h"

#include "NasMsccSysAcqStrategy.h"
#include "NasMsccFsmPowerOffTbl.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_PRE_PROC_ACT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef DMT
/* ����DMT���ԣ����ÿ���ʱ�Ƿ��Ͷ��������־��ģ�����ʧ�ܺͳ�ʱ�ĳ��� */
NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8 genCardReadStubTypeForDmt = NAS_MSCC_CARD_READ_STUB_TYPE_BUTT;
#endif


/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsNetworkCapInfoChanged
 ��������  : �ж�����������Ϣ�Ƿ����ı�
 �������  : pstNewNwCapInfo---�յ�����������ָʾ

 �������  : ��
 �� �� ֵ  : VOS_TRUE, ����������Ϣ�����ı�
             VOS_FALSE,����������Ϣ�������ı�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNetworkCapInfoChanged(
    NAS_MSCC_NETWORK_CAP_INFO_STRU      *pstNewNwCapInfo
)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU      *pstOldNwCapInfo = VOS_NULL_PTR;

    /* �Ȼ�ȡLTE������������Ϣ */
    pstOldNwCapInfo = NAS_MSCC_GetLteNwCapInfo();

    /* �¾������Ƿ��б仯 */
    if ((pstOldNwCapInfo->enLteCsCap   != pstNewNwCapInfo->enLteCsCap)
     || (pstOldNwCapInfo->enNwEmcBsCap != pstNewNwCapInfo->enNwEmcBsCap)
     || (pstOldNwCapInfo->enNwImsVoCap != pstNewNwCapInfo->enNwImsVoCap))
    {
        return VOS_TRUE;
    }

    /* �ٻ�ȡGU������������Ϣ */
    pstOldNwCapInfo = NAS_MSCC_GetGuNwCapInfo();

    /* �¾������Ƿ��б仯 */
    if ((pstOldNwCapInfo->enLteCsCap   != pstNewNwCapInfo->enLteCsCap)
     || (pstOldNwCapInfo->enNwEmcBsCap != pstNewNwCapInfo->enNwEmcBsCap)
     || (pstOldNwCapInfo->enNwImsVoCap != pstNewNwCapInfo->enNwImsVoCap))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetNetworkCapabilityInfo
 ��������  : ����ϵͳģʽ���¶�Ӧ����������Ϣ

 �������  : enSysMode    -- ϵͳģʽ
             pstNwCapInfo -- �µ�����������Ϣ

 �������  : ��
 �� �� ֵ  : ��������������Ϣ����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SetNetworkCapabilityInfo(
    NAS_MSCC_SYS_MODE_ENUM_UINT8        enSysMode,
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstNwCapInfo
)
{
    if (NAS_MSCC_SYS_MODE_LTE == enSysMode)
    {
        NAS_MSCC_SetLteNwCapInfo(pstNwCapInfo);
    }
    else
    {
        NAS_MSCC_SetGuNwCapInfo(pstNwCapInfo);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsImsVoiceSupportedByNW
 ��������  : �ж������Ƿ�֧��IMS VOICE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:IMS VOICE��֧��
             VOS_TRUE: IMS VOICE֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsImsVoiceSupportedByNW(VOS_VOID)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstCurNwCapInfo = VOS_NULL_PTR;
    NAS_MSCC_SYS_INFO_STRU             *pstSysInfo      = VOS_NULL_PTR;

    pstSysInfo = NAS_MSCC_GetCurrSysInfo();

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        pstCurNwCapInfo = NAS_MSCC_GetLteNwCapInfo();
    }
    else
    {
        pstCurNwCapInfo = NAS_MSCC_GetGuNwCapInfo();
    }

    if (NAS_MSCC_NW_IMS_VOICE_NOT_SUPPORTED == pstCurNwCapInfo->enNwImsVoCap)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsImsVoiceSupportedByUE
 ��������  : �ж�UE�Ƿ�֧��IMS VOICE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:IMS VOICE��֧��
             VOS_TRUE: IMS VOICE֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsImsVoiceSupportedByUE(VOS_VOID)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* ��ǰIMS��RAT NV��֧�ֻ�������ѡ��ΪCS ONLY�����粻֧��IMSʱ ��ΪIMS VOICE������*/
    if ((VOS_FALSE                     == NAS_MSCC_GetImsSupportFlag())
     || (NAS_MSCC_VOICE_DOMAIN_CS_ONLY == pstImsCfgInfo->enVoiceDomain))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsCGIInfoChanged
 ��������  : �ж�MSCC�е�פ����CGI��Ϣ(cell id��rat��lac��plmn id)�Ƿ����ı�
 �������  : pstOldSysInfo---��ǰMSCC������ϵͳ��Ϣ
             pstMmcSysInfo---�յ�ϵͳ��Ϣ���º�SDC�е�פ��PLMN��Ϣ

 �������  : ��
 �� �� ֵ  : VOS_TRUE, פ��ϵͳ��Ϣ�����ı�
             VOS_FALSE,פ��ϵͳ��Ϣδ�����ı�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��28��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��23��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsCGIInfoChanged(
    NAS_MSCC_3GPP_SYS_INFO_STRU         *pstOldSysInfo,
    MMC_MSCC_SYS_INFO_IND_STRU          *pstMmcSysInfo
)
{
    /* check CGI is changed */
    if ((pstOldSysInfo->stPlmnId.ulMcc  != pstMmcSysInfo->stPlmnId.ulMcc)
     || (pstOldSysInfo->stPlmnId.ulMnc  != pstMmcSysInfo->stPlmnId.ulMnc)
     || (pstOldSysInfo->usLac           != pstMmcSysInfo->usLac)
     || (pstOldSysInfo->ucRac           != pstMmcSysInfo->ucRac)
     || (pstOldSysInfo->ulCellId        != pstMmcSysInfo->stCellId.aulCellId[0])
     || (pstOldSysInfo->ucRoamFlag      != pstMmcSysInfo->ucRoamFlag)
     || (pstOldSysInfo->enSysMode       != pstMmcSysInfo->enCurNetWork)
     || (pstOldSysInfo->enLmmAccessType != pstMmcSysInfo->enLmmAccessType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcMmaUserReselReqIn1XMode_PreProc
 ��������  : ����Xģ�µ������Զ���������
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ����Ҫ��������
             VOS_FALSE -- ��Ҫ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��29��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_ProcMmaUserReselReqIn1XMode_PreProc(VOS_VOID)
{
    /* ���1X�з���ֱ�ӷ��سɹ���������AP��Լ������ʱ����ȥ����DO&L���� */
    if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
    {
        return VOS_TRUE;
    }

    /* �����ǰ״̬����power save״̬�������ں����������� */
    if (NAS_MSCC_FSM_POWER_OFF == NAS_MSCC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    /* ��ǰ1Xû�м����Ҫ������ر�־ */
    if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
    {
        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

    /*************************************************************************
     ������״̬�����������߼�:
     1. �����ǰL1״̬����deactive״̬�£�
        a. ��Ҫֹͣsleep ��ʱ��������scan��ʱ��;
        b. �����֧��L���򼤻�L��������
        c. �����֧��DO������Ҫ����DO��
        d. ���DO&L��֧�֣���Ҫ����MSCCϵͳ����״̬��������������;
     2. �����ǰ���ڽ���power save����(power off״̬����)������Ϣ��Ҫ��������棬��power save
        ������ɺ��ٴ����������̣�
     3. �����ǰ��L1״̬����active״̬�£���available��ʱ�������У���Ҫ����DO&L������

     3. ������L1��L2״̬��������Ҫ����
        a. �������ϵͳ�л�״̬���У�������ǰDO��L����������Ҫ����PS��������
        b. �����ϵͳ����״̬���У������������������У�����Ҫ����PS������
        c. �����BSR״̬���У��������ǰDO��L����������Ҫ����PS��������
        d. �ڿ���״̬���Լ�sys cfg״̬���У�����MMAĿǰ��ʵ�֣�����Ϣ�ǲ����·��ģ�
     *************************************************************************/
    return VOS_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcNetworkCapability_PreProc
 ��������  : ��������MMC��LTE ���������������ϱ���������Ϣ����ת����IMSA, ͬʱ
             ֪ͨMMA
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
  3.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcNetworkCapabilityInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU               *pstRcvMsg       = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    NAS_MSCC_SYS_INFO_STRU                                  *pstSysInfo      = VOS_NULL_PTR;
    NAS_MSCC_NETWORK_CAP_INFO_STRU                           stNewNwCapInfo;
    VOS_UINT32                                               ulNwCapInfoChanged;
#endif

    pstRcvMsg = (MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_IMS)
    stNewNwCapInfo.enNwEmcBsCap = (NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8)pstRcvMsg->enNwEmcBsCap;
    stNewNwCapInfo.enNwImsVoCap = (NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8)pstRcvMsg->enNwImsVoCap;

    switch (pstRcvMsg->enLteCsCap)
    {
        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_NO_ADDITION_INFO;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_SMS_ONLY;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_NOT_SUPPORTED;
            break;

        default:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_BUTT;
            break;
    }

    /* �жϵ�ǰ������������GU��L����������Ƿ����˸ı� */
    ulNwCapInfoChanged = NAS_MSCC_IsNetworkCapInfoChanged(&stNewNwCapInfo);

    if (VOS_TRUE == ulNwCapInfoChanged)
    {
        pstSysInfo = NAS_MSCC_GetCurrSysInfo();

        /* update informaton to the corresponding global variable according to RAT */
        NAS_MSCC_SetNetworkCapabilityInfo(pstSysInfo->st3gppSysInfo.enSysMode, &stNewNwCapInfo);
    }


#endif

    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaNetworkCapabilityInfoInd(pstRcvMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcSysInfoInd_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��07��
   ��    ��   : t00323010
   �޸�����   : �޸ģ�Iteration 10�����ϱ�λ����Ϣ�洢���ж�����BSR��ʱ��
 3. Date      : 2015-04-07
    Author    : a00295761
    Content   : Added code for updating LTE location info.
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcSysInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SYS_INFO_IND_STRU         *pstMmcSysInfo     = VOS_NULL_PTR;
    NAS_MSCC_3GPP_SYS_INFO_STRU         stOld3gppSysInfo;

    pstMmcSysInfo     = (MMC_MSCC_SYS_INFO_IND_STRU*)pstMsg;

    PS_MEM_SET(&stOld3gppSysInfo, 0x0, sizeof(NAS_MSCC_3GPP_SYS_INFO_STRU));
    PS_MEM_CPY(&stOld3gppSysInfo, NAS_MSCC_Get3gppSysInfoAddr(), sizeof(NAS_MSCC_3GPP_SYS_INFO_STRU));

    /* update 3gpp sys info */
    NAS_MSCC_Update3gppSysInfo(pstMmcSysInfo);

    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMma3gppSysInfoInd(pstMmcSysInfo);

#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        if (VOS_TRUE == NAS_MSCC_IsCGIInfoChanged(&stOld3gppSysInfo, pstMmcSysInfo))
        {
            NAS_MSCC_SndImsaCampInfoChangeInd();
        }
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcRegResultInd_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��12��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_REG_RESULT_IND_STRU       *pstRegResultInd   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulUeSupportIms;
#endif

    pstRegResultInd = (MMC_MSCC_REG_RESULT_IND_STRU *)pstMsg;

    /* ת������Ϣ��MMA */
    NAS_MSCC_SndMmaRegResultInd(pstRegResultInd);

#if (FEATURE_ON == FEATURE_IMS)
    if ((NAS_MSCC_PIF_SRVDOMAIN_PS    == pstRegResultInd->enCnDomainId)
     || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstRegResultInd->enCnDomainId))
    {
        ulUeSupportIms = NAS_MSCC_IsImsVoiceSupportedByUE();

        /* PSע��ʧ��ֱ��֪ͨIMS������ */
        /* ��ǰIMS��RAT NV��֧�ֻ�������ѡ��ΪCS ONLY�����粻֧��IMSʱ ��ΪIMS VOICE������*/
        if ((VOS_FALSE == NAS_MSCC_IsImsVoiceSupportedByNW())
         || (VOS_FALSE == pstRegResultInd->ucRegRslt)
         || (VOS_FALSE == ulUeSupportIms))
        {

            /* ֪ͨMMC��ǰIMS voice������ */
            NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
            NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
            NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

            /* ֪ͨMMA��ǰIMS voice������ */
            NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

            return VOS_TRUE;
        }

    }
#else
    /* ֪ͨMMC��ǰIMS voice�Ƿ���� */
    NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
    NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
    NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcServiceStatusInd_PreProc
 ��������  : ����MMC����״̬�ϱ�ָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��07��
   ��    ��   : m00312079
   �޸�����   : CLģʽ�£�����CL״̬��
 3.��    ��   : 2015��04��08��
   ��    ��   : t00323010
   �޸�����   : ����פ��״̬��ϢIteration 10
 4. Date      : 2015-04-14
    Author    : a00295761
    Content   : Added Update Location Info NVIM step
5.��    ��   : 2015��10��14��
  ��    ��   : c00318887
  �޸�����   : DTS2015082002854:
               ����1:��L��TAU�ɹ��������������DETACH L,MMC��Ȼά��NORMAL SERVICE.
               L���·���ATTACH�ɹ�����ID_MMC_MSCC_NETWORK_CAPABILITY_INFO_IND֪ͨ��MSCC,
               MSCCͨ��ID_MSCC_IMSA_SERVICE_CHANGE_IND��Ϣ֪ͨ��IMSA,���ڴ�ʱL��ATTACH
               �ɹ���Ϣ��û��֪ͨ��ESM������û�д���IMSA��ע�ᡣ����MMC��ATTACH�ɹ���Ӧ��
               ��������֪ͨ��MSCC,MSCC�б����״̬û�иı䣬���Բ�֪ͨIMSA��û�д���IMS��
               ע�ᡣ�޸�˼·��MSCC�ſ���PS����״̬�Ƿ�ı���жϡ�
               ����2: DTS2015082002854: ���α�ǲ�׼
  6.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ����ʱlimit service û�з���IMSA������IMSûȥע�ᣬ��������ʾ����;
                 ����2: ����״̬û�䵼�����α��û����IMSA
  7.��    ��   : 2015��12��21��
    ��    ��   : j00174725
    �޸�����   : DTS2015121106874  ����TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY��ʱ������ע��״̬�Ƶ�����״̬֪ͨIMSʱ.
                 �����޸�Ϊ������������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstSrvStatusInd;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT8                           ucRoamingValid;

    VOS_UINT8                           ucCurr3gppRoamingFlg;
#endif
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enCurrPsSrvStatus;

    pstSrvStatusInd                     = (MMC_MSCC_SERVICE_STATUS_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_IMS)
    ucRoamingValid                      = VOS_FALSE;
    ucCurr3gppRoamingFlg                = VOS_FALSE;
#endif

    /* ת������Ϣ��MMAģ�� */
    NAS_MSCC_SndMmaServiceStatusInd(pstSrvStatusInd);

    NAS_MSCC_SetSimCsRegStatus(pstSrvStatusInd->ucSimCsRegStatus);

    NAS_MSCC_SetSimPsRegStatus(pstSrvStatusInd->ucSimPsRegStatus);

    /*ע��״̬�ϱ�����: CS��PS����һ����ע������ʱ������3GPP�����α�ʾ */
    if (VOS_TRUE == pstSrvStatusInd->bitOpRegSta)
    {
        NAS_MSCC_UpdateRoamFlag(pstSrvStatusInd->enRegState);
    }

    /* ���´���ֻ���PS����״̬�ϱ��Ŵ��� */
    if ((VOS_TRUE                      == pstSrvStatusInd->bitOpSrvSta)
     && ((NAS_MSCC_PIF_SRVDOMAIN_PS    == pstSrvStatusInd->enCnDomainId)
      || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstSrvStatusInd->enCnDomainId)
      || (NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING == pstSrvStatusInd->enCnDomainId)))
    {
        enCurrPsSrvStatus = NAS_MSCC_ConvertMmcServiceStatusToMsccFormat(pstSrvStatusInd->enServiceStatus);

#if (FEATURE_ON == FEATURE_IMS)
        ucCurr3gppRoamingFlg = NAS_MSCC_GetCurr3gppRoamingFlg();

        if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == enCurrPsSrvStatus)
        {
            ucRoamingValid              = VOS_TRUE;

        }

        /* ֻҪ����֧�־͸�IMSA�� */
        if (VOS_TRUE          == NAS_MSCC_GetImsSupportFlag())
        {
            NAS_MSCC_SndImsaSrvInfoNotify(enCurrPsSrvStatus, ucRoamingValid, ucCurr3gppRoamingFlg);

            /* ֹͣ�ȴ�IMSA��IMS voice�Ƿ������Ϣ��ʱ�� */
            NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY);

            /* ��PSע��ɹ�ʱ����������ʱ���ȴ�IMSע����ɺ��ϱ�IMS voice�Ƿ���� */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY, NAS_MSCC_GetWaitImsVoiceAvailTimerLen());
        }
#endif

        /* ���浱ǰ3GPP��PS����״̬ */
        NAS_MSCC_SetCurr3gppPsServiceStatus(enCurrPsSrvStatus);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        return NAS_MSCC_ProcPsServiceStatusIndInCLMode_PreProc(pstSrvStatusInd);
#endif
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaSignReportReq_PreProc
 ��������  : �յ�ID_MMA_MSCC_SIGN_REPORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��29��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSignReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SIGN_REPORT_REQ_STRU      *pstSignReport = VOS_NULL_PTR;
    pstSignReport = (MMA_MSCC_SIGN_REPORT_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcSignalReportReq(pstSignReport);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaModeChangeReq_PreProc
 ��������  : Ԥ����Mode CHange Change ��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaModeChangeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_MODE_CHANGE_REQ_STRU      *pstModeChangeReq = VOS_NULL_PTR;
    pstModeChangeReq = (MMA_MSCC_MODE_CHANGE_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcModeChangeReq(pstModeChangeReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaAttachReq_PreProc
 ��������  : MSCC�յ�ATTACH�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_ATTACH_REQ_STRU           *pstAttachReq = VOS_NULL_PTR;

    pstAttachReq = (MMA_MSCC_ATTACH_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcAttachReq(pstAttachReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaDetachReq_PreProc
 ��������  : MMC�յ�DETACH REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaDetachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_DETACH_REQ_STRU           *pstDetachReq = VOS_NULL_PTR;

    pstDetachReq = (MMA_MSCC_DETACH_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcDetachReq(pstDetachReq);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcCsgListSearchCnf_PreProc
 ��������  : ����MMC CSG list���������Ϣ
 �������  : ulEventType  �¼�����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCsgListSearchCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaCsgListSearchCnf((MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcCsgListRej_PreProc
 ��������  : ����MMC CSG list rej��Ϣ
 �������  : ulEventType  �¼�����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCsgListRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_CSG_LIST_REJ_STRU         *pstCsgListRej = VOS_NULL_PTR;

    pstCsgListRej = (MMC_MSCC_CSG_LIST_REJ_STRU *)pstMsg;

    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaCsgListRej(pstCsgListRej);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcCsgListAbortCnf_PreProc
 ��������  : ����MMC CSG list abort��Ϣ
 �������  : ulEventType  �¼�����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCsgListAbortCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU   *pstCsgListAbortCnf = VOS_NULL_PTR;

    pstCsgListAbortCnf = (MMC_MSCC_CSG_LIST_ABORT_CNF_STRU *)pstMsg;

    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaCsgListAbortCnf(pstCsgListAbortCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCsgListSearchReq_PreProc
 ��������  : �յ�CSG�б�������Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg    - ��Ϣ��ַ
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCsgListSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU  *pstCsgListSearchReq = VOS_NULL_PTR;
    MMC_MSCC_CSG_LIST_REJ_STRU          stCsgListRej;

    PS_MEM_SET(&stCsgListRej, 0, sizeof(stCsgListRej));
    pstCsgListSearchReq = (MMA_MSCC_CSG_LIST_SEARCH_REQ_STRU *)pstMsg;

    /* if current rat setting support HRPD,we directly reply fail to upp layer */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* reply upp layer with reject result */
        NAS_MSCC_SndMmaCsgListRej(&stCsgListRej);

        return VOS_TRUE;
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcCsgListSearchReq(pstCsgListSearchReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCsgListAbortReq_PreProc
 ��������  : csg list abort��Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg    - ��Ϣ��ַ
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��12��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCsgListAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CSG_LIST_ABORT_REQ_STRU   *pstCsgListAbortReq = VOS_NULL_PTR;

    pstCsgListAbortReq = (MMA_MSCC_CSG_LIST_ABORT_REQ_STRU *)pstMsg;

    /* if current rat setting support HRPD,we directly reply fail to upp layer */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndMmaCsgListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcCsgListAbortReq(pstCsgListAbortReq);

    return VOS_TRUE;
}

#endif
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvTafPlmnListReq_PreProc
 ��������  : ID_MMA_MSCC_PLMN_LIST_REQ��Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 4/4/2015
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPlmnListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* if current rat setting support HRPD,we directly reply fail to upp layer */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* reply upp layer with reject result */
        NAS_MSCC_SndMmaPlmnListRej((MMC_MSCC_PLMN_LIST_REJ_STRU*)pstMsg);

        return VOS_TRUE;
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcPlmnListReq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaPlmnListAbortReq_PreProc
 ��������  : ID_MMA_MSCC_PLMN_LIST_ABORT_REQ��Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 4/4/2015
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPlmnListAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU   stMmcMsccPlmnListAbortCnf;

    PS_MEM_SET(&stMmcMsccPlmnListAbortCnf, 0x0, sizeof(stMmcMsccPlmnListAbortCnf));

    /* if current rat setting support HRPD,we directly reply fail to upp layer */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndMmaPlmnListAbortCnf(&stMmcMsccPlmnListAbortCnf);

        return VOS_TRUE;
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcPlmnListAbortReq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvUserReselReq_PreProc
 ��������  : �û������Զ���ѡ��Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��12��25��
   ��    ��   : y00245242
   �޸�����   : CLģʽ�£����������������Կ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaUserReselReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���1X֧�֣������Զ����������XSD */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_TRUE;

    /* CL ģʽ */
    if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
    {
        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
        {
            /* ����Xģ�£��û�����������������Զ��������� */
            ulRslt = NAS_MSCC_ProcMmaUserReselReqIn1XMode_PreProc();
        }

        /* ƽ̨����֧��LTE����Ҫ������ģʽ����MMC */
        if (VOS_TRUE == NAS_MSCC_IsPlatformSupportLte())
        {
            NAS_MSCC_SndMmcPlmnUserReselReq((MMA_MSCC_PLMN_USER_RESEL_REQ_STRU *)pstMsg);
        }

        /* �����ȸ�MMA�ظ����������ɹ� */
        NAS_MSCC_SndMmaPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);

        return ulRslt;
    }
#endif

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcPlmnUserReselReq((MMA_MSCC_PLMN_USER_RESEL_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaUserSpecPlmnSearch_PreProc
 ��������  : �û�ָ������Ϣ��Ԥ����
 �������  : ulEventType: ��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 4/4/2015
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaUserSpecPlmnSearch_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU     *pstPlmnSpecialReq  = VOS_NULL_PTR;

    pstPlmnSpecialReq = (MMA_MSCC_PLMN_SPECIAL_REQ_STRU *)pstMsg;

    /* GUL mode or current active mode is LTE, transfer user resel
       request to MMC module */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* reply upp layer with failed result */
        NAS_MSCC_SndMmaPlmnSpecialSelRej((MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU*)pstMsg);

        return VOS_TRUE;
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcPlmnSpecialReq(pstPlmnSpecialReq);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection
 ��������  : �յ�ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :


 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 4/4/2015
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSpecPlmnSearchAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* GUL mode or current active mode is LTE, transfer user resel
       request to MMC module */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf((MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU*)pstMsg);

        return VOS_TRUE;
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcSpecPlmnSearchAbortReq();

    return VOS_TRUE;
}

/*****************************************************************************
  �� �� ��  : NAS_MMC_RcvTafOmMaintainInfoInd_PreProc
 ��������  : �յ�TAFMMC_SDT_INFO_IND��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaOmMaintainInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstMaintainInfoInd = VOS_NULL_PTR;

    pstMaintainInfoInd = (MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcOmMaintainInfoInd(pstMaintainInfoInd);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaUpdateUplmnNtf_PreProc
 ��������  : �յ�ID_MSCC_MMC_UPDATE_UPLMN_NTF��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaUpdateUplmnNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcUpdateUplmnNotify();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaEOPlmnSetReq_PreProc
 ��������  : Ԥ�����յ�EOPLMN��Ϣ�����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:����plmn����Ϣ�ṹ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaEOPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_EOPLMN_SET_REQ_STRU       *pstEOPlmnSetReq = VOS_NULL_PTR;

    pstEOPlmnSetReq = (MMA_MSCC_EOPLMN_SET_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcEOPlmnSetReq(pstEOPlmnSetReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaNetScanReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_NET_SCAN_REQ_STRU         *pstNetScanReq = VOS_NULL_PTR;

    pstNetScanReq = (MMA_MSCC_NET_SCAN_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcNetScanMsgReq(pstNetScanReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaAbortNetScanReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaAbortNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcAbortNetScanMsgReq();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaAcqReq_PreProc
 ��������  : ��MMA����������acq req��Ϣ����Ԥ����
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_ACQ_REQ_STRU              *pstAcqReq = VOS_NULL_PTR;

    pstAcqReq = (MMA_MSCC_ACQ_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcAcqReq(pstAcqReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaRegReq_PreProc
 ��������  : ��MMA����������reg req��Ϣ����Ԥ����
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaRegReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_REG_REQ_STRU              *pstRegReq = VOS_NULL_PTR;

    pstRegReq = (MMA_MSCC_REG_REQ_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcRegReq(pstRegReq);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_PhoneRssiInd
 ��������  : �յ�MMC�ϱ���MSCC_RSSI_IND��Ϣ
 �������  : MMC_MSCC_RSSI_IND_STRU *pMsg MSCC�ϴ�����������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ     :
  1.��    ��  : 2015��01��30��
    ��    ��  : x00314862
    �޸�����  : �½�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPhoneRssiInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaRssiInd((MMC_MSCC_RSSI_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : Sta_MmInfo
 ��������  : ����MM INFO��Ϣ�ϱ�
 �������  : MMC_MSCC_MM_INFO_IND_STRU *pstMmInfo - MM INFO�ṹָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ     :
  1.��    ��  : 2015��01��30��
    ��    ��  : x00314862
    �޸�����  : �½�
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStaMmInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaMmInfo((MMC_MSCC_MM_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : MSCC_ProcPlmnSelectStartInd
 ��������  : ����MMC�ϱ���������ʼ��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2015��01��30��
    ��    ��  : x00314862
    �޸�����  : �½�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSelectStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_START_IND_STRU                  *pstPlmnStartInd    = VOS_NULL_PTR;

    pstPlmnStartInd = (MMC_MSCC_PLMN_SELECTION_START_IND_STRU *)pstMsg;

    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    if (NAS_MSCC_PIF_PLMN_SELECTION_START == pstPlmnStartInd->enPlmnSeleStartFlag)
    {
        /* GULģʽ����ԭ���߼�֪ͨMMA������ʼ,ģʽΪ3GPP */
        if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
        {
            NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_3GPP);

            return VOS_TRUE;
        }

        /* CLģʽ�²��ڲ���������,֪ͨMMA������ʼ,ģʽΪDO_LTE��������CL�������̿�ʼʱ֪ͨ */
        if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
        {
            NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcEOPlmnSetCnf
 ��������  : MSCCģ���յ�MMCģ�鷢�͵�ID_MMC_MSCC_EOPLMN_SET_CNF
 �������  : MMC_MSCC_EOPLMN_SET_CNF_STRU         *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ     :
  1.��    ��  : 2015��01��30��
    ��    ��  : x00314862
    �޸�����  : �½�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcEOPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_EOPLMN_SET_CNF_STRU                  *pstMmcMsg       = VOS_NULL_PTR;

    pstMmcMsg   = (MMC_MSCC_EOPLMN_SET_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaEOPlmnSetCnf(pstMmcMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_SaveWCipherInfo
 ��������  : ��MSCC������Cipher��Ϣ���浽ȫ�ֱ���
             (D_MSCC_UMTS_CIPHER_INFO_IND)
 �������  : const MSCC_UMTS_CIPHER_INFO_IND_STRU* pstCipherInfoInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  �޸���ʷ     :
  1.��    ��  : 2015��01��30��
    ��    ��  : x00314862
    �޸�����  : �½�
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcWCipherInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;

    pstCipherInfoInd = (MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaWCipherInfo(pstCipherInfoInd);

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndMmaGCipherInfoInd
 ��������  : ��MSCC������Cipher��Ϣ���浽ȫ�ֱ���
             (D_MSCC_GPRS_CIPHER_INFO_IND)
 �������  : const MSCC_GPRS_CIPHER_INFO_IND_STRU* pstCipherInfoInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcGCipherInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;
    pstCipherInfoInd = (MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaGCipherInfo(pstCipherInfoInd);

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
}

/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcAcInfoChangeInd
 ��������  : MSCC�յ�MSCC D_MSCC_AC_INFO_CHANGE_IND��Ϣ�Ĵ���
 �������  : MMC_MSCC_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAcInfoChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd;
    pstAcInfoChangeInd = (MMC_MSCC_AC_INFO_CHANGE_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaAcInfoChangeInd(pstAcInfoChangeInd);

    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcCampOnInd_PreProc
 ��������  : ��������MMC��פ��ָʾ��Ϣ
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCampOnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_CAMP_ON_IND_STRU_STRU      *pstCampOnInd = VOS_NULL_PTR;

    pstCampOnInd = (MMC_MSCC_CAMP_ON_IND_STRU_STRU*)pstMsg;

    NAS_MSCC_SndMmaCampOnInd(pstCampOnInd);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcRfAvailableInd_PreProc
 ��������  : ��������MSCC��RfAvailableInd
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��05��20��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  3.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU*)pstMsg;

    /* the current rat is the master mode, just transfer it to mma */

    NAS_MSCC_SndMmaRfAvailInd(pstRfAvail);

    /* �������غ�ģʽ�£�ֻ͸������Ϣ������������ */
    if (NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE == NAS_MSCC_GetEmcCallExistFlag())
    {
        return VOS_TRUE;
    }

    /* ��ǰMMC���û�б�����Ļ�����Ҫ��״̬�������п��ܴ������� */
    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MSCC_Sta_DataTranAttri
 ��������  : �յ�MSCC�ϱ���MSCC_DATATRAN_ATTRI_IND��Ϣ
 �������  : ucDataTranAttri MSCC�ϴ�����������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStaDataTranAttri_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU    *pstDataTranAttri;

    pstDataTranAttri = (MMC_MSCC_DATATRAN_ATTRI_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaDataTranAttri(pstDataTranAttri);

    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
}


/*****************************************************************************
 �� �� ��  : MSCC_Sta_CoverageAreaInd
 ��������  : �յ�MMC��������CoverageAreaInd
 �������  : MMC_MSCC_COVERAGE_AREA_IND_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��30��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��07��
    ��    ��   : y00307564
    �޸�����   : �޸�
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStaCoverageAreaInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_COVERAGE_AREA_IND_STRU    *pCoverageAreaInd = VOS_NULL_PTR;

    pCoverageAreaInd = (MMC_MSCC_COVERAGE_AREA_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaCoverageInd(pCoverageAreaInd);

    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == NAS_MSCC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcNetScanCnf_PreProc
 ��������  : �յ�MSCC��������netscan�ظ�
 �������  : MMC_MSCC_NET_SCAN_CNF_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_NET_SCAN_CNF_STRU         *pstMmcNetScanCnf = VOS_NULL_PTR;

    pstMmcNetScanCnf = (MMC_MSCC_NET_SCAN_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaNetScanCnf(pstMmcNetScanCnf);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcAbortNetScanCnf_PreProc
 ��������  : �յ�MSCC�������Ĵ��netscan�ظ�
 �������  : MMC_MSCC_NET_SCAN_CNF_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAbortNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstMmcAbortNetScanCnf = VOS_NULL_PTR;

    pstMmcAbortNetScanCnf = (MMC_MSCC_ABORT_NET_SCAN_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaAbortNetScanCnf(pstMmcAbortNetScanCnf);
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcEplmnInfoInd_PreProc
 ��������  : �յ�MSCC ��Чplmn��Ϣ
 �������  : pstEplmnInfoIndMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcEplmnInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_EPLMN_INFO_IND_STRU       *pstEplmnInfoIndMsg  = VOS_NULL_PTR;

    pstEplmnInfoIndMsg   = (MMC_MSCC_EPLMN_INFO_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaEplmnInfoInd(pstEplmnInfoIndMsg);


    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcAcqCnf_PreProc
 ��������  : �յ�MSCCģ���acq cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��20��
    ��    ��   : m00312079
    �޸�����   : ��CL����״̬����NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_INDʱ����Ϣ
                 ��״̬������
  3.��    ��   : 2015��07��23��
    ��    ��   : y00307564
    �޸�����   : DTS2015072802714
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_FSM_ID_ENUM_UINT32          enCurrFsmId;
    NAS_MSCC_FSM_CTX_STRU               *pstCurFsm;
#endif
    MMC_MSCC_ACQ_CNF_STRU               *pstMmcMsccAcqCnf;



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    /* in CL system acquire fsm, then enter fsm to proc this msg */
    if (NAS_MSCC_FSM_SYS_ACQ == enCurrFsmId)
    {
        /* Get the current FSM address*/
        pstCurFsm   = NAS_MSCC_GetCurFsmAddr();

        if (NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND == pstCurFsm->ulState)
        {
             return VOS_FALSE;
        }
    }
#endif

    pstMmcMsccAcqCnf = (MMC_MSCC_ACQ_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaAcqCnf(pstMmcMsccAcqCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaPowerSaveReq_PreProc
 ��������  : �յ�MMA��Power Save������������״̬��
 �������  : ulEventType:��Ϣ����
           : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��05��22��
   ��    ��   : W00176964
   �޸�����   : CDMA Iteration 10 Modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPowerSaveReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SetPowerSaveReplyFlg(VOS_TRUE);

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcPowerSaveReq();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcMsgLmmCellSignInfoInd_PreProc
 ��������  : �յ�MMC��LMM��С���ź���Ϣָʾ��Ϣ
 �������  : pstEplmnInfoIndMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcMsgLmmCellSignInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU            *pstLmmCellSignInfoInd = VOS_NULL_PTR;

    pstLmmCellSignInfoInd = (MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU *)pstMsg;

    /* ת������Ϣ��MMAģ�� */
    NAS_MSCC_SndMmaLmmCellSignInfoReportInd(pstLmmCellSignInfoInd);

    return VOS_TRUE;
}









/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcRegCnf_PreProc
 ��������  : �յ�MSCCģ���reg cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcRegCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaRegCnf((MMC_MSCC_REG_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcPowerSaveCnf_PreProc
 ��������  : �յ�MSCCģ���power save cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��11��
   ��    ��   : W00176964
   �޸�����   : CDMA Iteration 10 Modified
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERVICE_STATUS_IND_STRU    stServiceSta;
    MMC_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf;

    pstPowerSaveCnf = (MMC_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

    PS_MEM_SET(&stServiceSta, 0X0, sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU));

    if (NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult)
    {
        NAS_MSCC_Set3gppActiveFlg(VOS_FALSE);
        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        /* notify mma no service */
        NAS_MSCC_SetCurr3gppPsServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        stServiceSta.bitOpSrvSta      = VOS_TRUE;
        stServiceSta.enServiceStatus  = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
        stServiceSta.enCnDomainId     = NAS_MSCC_PIF_SRVDOMAIN_CS_PS;
        stServiceSta.ucSimCsRegStatus = NAS_MSCC_GetSimCsRegStatus();
        stServiceSta.ucSimPsRegStatus = NAS_MSCC_GetSimPsRegStatus();

        NAS_MSCC_SndMmaServiceStatusInd(&stServiceSta);

        /* need reply to upplayer */
        if (VOS_TRUE == NAS_MSCC_GetPowerSaveReplyFlg())
        {
            NAS_MSCC_SndMmaPowerSaveCnf((MMC_MSCC_POWER_SAVE_CNF_STRU*)pstMsg);

            NAS_MSCC_SetPowerSaveReplyFlg(VOS_FALSE);
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
        {
            NAS_MSCC_SndHsdDisableLteNtf();
        }
#endif
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcUsimAuthFailInd_PreProc
 ��������  : �յ�MMC��������USIM��Ȩʧ��ԭ��ֵ��Ϣ���д���
 �������  : MMC_MSCC_USIM_AUTH_FAIL_IND_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcUsimAuthFailInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU    *pstAuthFailInd  = VOS_NULL_PTR;

    pstAuthFailInd            = (MMC_MSCC_USIM_AUTH_FAIL_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaUsimAuthFailInd(pstAuthFailInd);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcCsServiceConnStatusInd_PreProc
 ��������  : �յ�MMC�ϱ���csҵ����������״ָ̬ʾ��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCsServiceConnStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU                *pstCsServiceConnStatusInd = VOS_NULL_PTR;


    pstCsServiceConnStatusInd = (MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaCsServiceConnStatusInd(pstCsServiceConnStatusInd);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcServRejInd_PreProc
 ��������  : �յ�MMC�������ķ��񱻾�ԭ��ֵ��Ϣ���д���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcServRejInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERV_REJ_IND_STRU          *pstServRejInd = VOS_NULL_PTR;


    pstServRejInd = (MMC_MSCC_SERV_REJ_IND_STRU *) pstMsg;

    (VOS_VOID)NAS_MSCC_SndMmaServRejRsltInd(pstServRejInd);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcAttachCnf_PreProc
 ��������  : �յ�MMC��������attach cnf���д���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ATTACH_CNF_STRU            *pstAttachCnf = VOS_NULL_PTR;

    pstAttachCnf = (MMC_MSCC_ATTACH_CNF_STRU*)pstMsg;

    NAS_MSCC_SndMmaAttachCnf(pstAttachCnf);

    /* ����״̬������ */
    return VOS_TRUE;
}


/*****************************************************************************
  �� �� ��  : MSCC_RcvMmcDetachInd_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���


*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_DETACH_IND_STRU            *pstDetachInd = VOS_NULL_PTR;
    pstDetachInd = (MMC_MSCC_DETACH_IND_STRU *) pstMsg;

    NAS_MSCC_SndMmaDetachInd(pstDetachInd);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcDetachCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaDetachCnf((MMC_MSCC_DETACH_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPlmnListCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnListCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaPlmnListCnf((MMC_MSCC_PLMN_LIST_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPlmnListRej_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnListRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaPlmnListRej((MMC_MSCC_PLMN_LIST_REJ_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPlmnSpecialSelCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSpecialSelCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaPlmnSpecialSelCnf((MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPlmnListAbortCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnListAbortCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaPlmnListAbortCnf((MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcSpecPlmnSearchAbortCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcSpecPlmnSearchAbortCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf((MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPlmnSpecialSelRej_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSpecialSelRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaPlmnSpecialSelRej((MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPlmnReselCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnReselCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaPlmnReselCnf(((MMC_MSCC_PLMN_RESEL_CNF_STRU*)pstMsg)->enResult);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCFPlmnSetReq_PreProc
 ��������  : �յ�ID_MSCC_MMA_CFPLMN_SET_REQ��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��7��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCFPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcCFPlmnSetReq((MMA_MSCC_CFPLMN_SET_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCFPlmnQueryReq_PreProc
 ��������  : �յ�ID_MSCC_MMA_CFPLMN_QUERY_REQ��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��7��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCFPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcCFPlmnQueryReq((MMA_MSCC_CFPLMN_QUERY_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcCFPlmnSetCnf_PreProc
 ��������  : ����MSCCȷ����Ϣ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 1.��    ��   : 2015��02��7��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCFPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaCFPlmnSetCnf((MMC_MSCC_CFPLMN_SET_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcCFPlmnQueryCnf_PreProc
 ��������  : ����MSCCȷ����Ϣ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 1.��    ��   : 2015��02��7��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCFPlmnQueryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaCFPlmnQueryCnf((MMC_MSCC_CFPLMN_QUERY_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
  �� �� ��  : NAS_MSCC_RcvMmaSdtConnedInd_PreProc
 ��������  : �յ�ID_MMA_MSCC_SDT_CONNECTED_IND��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 1.��    ��   : 2015��02��7��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSdtConnedInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcSdtConnedInd((MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaPrefPlmnSetReq_PreProc
 ��������  : ����MMC����״̬�ϱ�ָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPrefPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������prefplmn��Ϣת����mmc */
    NAS_MSCC_SndMmcPrefPlmnSetReq((MMA_MSCC_PREF_PLMN_SET_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaPrefPlmnQueryReq_PreProc
 ��������  : ����MMA

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��3��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPrefPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ѯprefplmn��Ϣת����mmc */
    NAS_MSCC_SndMmcPrefPlmnQueryReq((MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaDplmnSetReq_PreProc
 ��������  : MSCC��DPLMN SET REQ��Ϣת����MMC
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaDplmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_DPLMN_SET_REQ_STRU        *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (MMA_MSCC_DPLMN_SET_REQ_STRU *)pstMsg;

    /* ��DPLMN SET REQ��Ϣת����MMC */
    NAS_MSCC_SndMmcDplmnSetReq(pstRcvMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPrefPlmnQueryCnf_PreProc
 ��������  : ����MMA

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��03��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPrefPlmnQueryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ѯprefplmnӦ����Ϣת����mma */
    NAS_MSCC_SndMmaPrefPlmnQueryCnf((MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPrefPlmnSetCnf_PreProc
 ��������  : ����MMA

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��03��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPrefPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������prefplmnӦ����Ϣת����mma */
    NAS_MSCC_SndMmaPrefPlmnSetCnf((MMC_MSCC_PREF_PLMN_SET_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcPrefPlmnInfoInd_PreProc(
    VOS_UINT32                                               ulEventType,
    struct MsgCB                                            *pstMsg
)
{
    MMC_MSCC_PREF_PLMN_INFO_IND_STRU                        *pstPrefPlmnInd      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU                       *pstMsccEhPlmnInfo   = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                     *pstMsccUserPlmnInfo = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                     *pstMsccOperPlmnInfo = VOS_NULL_PTR;

    pstPrefPlmnInd = (MMC_MSCC_PREF_PLMN_INFO_IND_STRU *)pstMsg;


    if (NAS_MSCC_PREF_PLMN_UPLMN == pstPrefPlmnInd->enPrefPlmnType)
    {
        pstMsccUserPlmnInfo = NAS_MSCC_GetUserPlmnInfoAddr();

        PS_MEM_CPY(pstMsccUserPlmnInfo, &(pstPrefPlmnInd->stUplmnInfo),
                   sizeof(NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU));
    }

    if (NAS_MSCC_PREF_PLMN_HPLMN == pstPrefPlmnInd->enPrefPlmnType)
    {
        pstMsccEhPlmnInfo   = NAS_MSCC_GetEhPlmnInfoAddr();

        PS_MEM_CPY(pstMsccEhPlmnInfo,   &(pstPrefPlmnInd->stEhplmnInfo),
                   sizeof(NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU));
    }

    if (NAS_MSCC_PREF_PLMN_OPLMN == pstPrefPlmnInd->enPrefPlmnType)
    {
        pstMsccOperPlmnInfo = NAS_MSCC_GetOperPlmnInfoAddr();

        PS_MEM_CPY(pstMsccOperPlmnInfo, &(pstPrefPlmnInd->stOplmnInfo),
                   sizeof(NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU));
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaGetGeoReq_PreProc
 ��������  : MSCC�յ�ID_MMA_MSCC_GET_GEO_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaGetGeoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;

    NAS_TRACE_HIGH("NAS_MSCC_RcvMmaGetGeoReq_PreProc():Mscc Start Get Geo Proc");

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();

    pstNoCardInitSearchLocInfo->ucIsLocInfoUsed  = VOS_TRUE;

    /* ƽ̨����֧��LTE������GUL��GET_GEO_REQ */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportLte())
    {
        NAS_MSCC_SndMmcGetGeoReq((MMA_MSCC_GET_GEO_REQ_STRU *)pstMsg);

        NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_GUL);
    }
    else
    {
        /* ƽ̨����֧��1x������Xģ���� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
        {
            /* ���ƽ̨������֧��GUL��֧��1X����xsd�����޿�����,��ȡ1x��λ����Ϣ */
            NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_INIT_SEARCH);

            NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X);
        }
        else
#endif
        {
            /* ƽ̨����GUL��1x����֧�֣�ֱ�ӻظ�mma���޿�����λ����Ϣ��Ч */
            NAS_MSCC_ResetNoCardInitSearchInfo();

            NAS_MSCC_SndMmaGetGeoCnf(pstNoCardInitSearchLocInfo);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcGetGeoCnf_PreProc
 ��������  : ����MMC��ID_MMC_MSCC_GET_GEO_CNF��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��23��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcGetGeoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;
    MMC_MSCC_GET_GEO_CNF_STRU                              *pstMsccMmaGetGeoCnf        = VOS_NULL_PTR;

    pstMsccMmaGetGeoCnf        = (MMC_MSCC_GET_GEO_CNF_STRU *)pstMsg;

    /* ���޿����ѵ�lteλ����Ϣ���и��� */
    NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(pstMsccMmaGetGeoCnf->stPlmnId.ulMcc,
                                              pstMsccMmaGetGeoCnf->stPlmnId.ulMnc);

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();
    /* GUL���ѳɹ�������λ����Ϣ��λ����Ϣδ��ʹ�ã�����ΪFALSE */
    pstNoCardInitSearchLocInfo->ucIsLocInfoUsed = VOS_FALSE;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
    {
        /* ���ƽ̨����֧��1x����ȡLTE��GEOλ����Ϣ֮����xsd�����޿����� */
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_INIT_SEARCH);

        NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X);
    }
    else
#endif
    {
        /* ����ȡ����λ����Ϣ�ظ�ת����mma */
        NAS_MSCC_SndMmaGetGeoCnf(pstNoCardInitSearchLocInfo);

        NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaStopGetGeoReq_PreProc
 ��������  : MSCC�յ�ID_MMA_MSCC_STOP_GET_GEO_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��01��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaStopGetGeoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType;

    enNoCardInitSearchWaitType = NAS_MSCC_GetNoCardInitSearchWaitType();

    /* ���ݵ�ǰ�ȴ����ѵ�״̬��ѡ���Ǵ��gul�ĳ��ѣ�����1x�ĳ��ѣ�1x�ĳ��Ѵ�Ͻ���power_save */
    if (NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_GUL == enNoCardInitSearchWaitType)
    {
        /* ��ֹͣ��ȡ����λ����Ϣ����ת����mmc */
        NAS_MSCC_SndMmcStopGetGeoReq((MMA_MSCC_STOP_GET_GEO_REQ_STRU *)pstMsg);
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X == enNoCardInitSearchWaitType)
    {
        /* ����power_save,���1x��ȡ����λ����Ϣ */
        NAS_MSCC_SndXsdPowerSaveReq(NAS_MSCC_PIF_POWER_SAVE_TYPE_SLEEP);
    }
#endif
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaStopGetGeoReq_PreProc:ERROR!!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcStopGetGeoCnf_PreProc
 ��������  : ����MMC��ID_MMC_MSCC_STOP_GET_GEO_CNF��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��01��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStopGetGeoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���޿����ѵȴ���������Ϊ��Ч */
    NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT);

    /* ��ֹͣ��ȡ����λ����Ϣ�ظ�ת����mma */
    NAS_MSCC_SndMmaStopGetGeoCnf((MMC_MSCC_STOP_GET_GEO_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcDplmnSetCnf_PreProc
 ��������  : MSCC�յ�ID_MMC_MSCC_DPLMN_SET_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcDplmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* MSCC��DPLMN SET CNF��Ϣת����MMA */
    NAS_MSCC_SndMmaDplmnSetCnf((MMC_MSCC_DPLMN_SET_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc
 ��������  : �յ�MMA��Cdma Mo Call Start Ntf��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��27��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf = VOS_NULL_PTR;

    pstCdmaMoCallStartNtf = (MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU*)pstMsg;

    /* ת������Ϣ��hxd ��xsdģ�� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallStartNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallStartNtf(pstCdmaMoCallStartNtf);
    }
    else
    {
        NAS_MSCC_Set1xSysAcqMoCallFlag(VOS_TRUE);

        NAS_MSCC_SndXsdCdmaMoCallStartNtf(pstCdmaMoCallStartNtf);

        /* ��ǰ�����������������Ĭ��1X RAT��֧�ֵģ�������ж�1X�Ƿ񼤻� */
        if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
        {
            NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

            NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCdmaMoCallRedialSysAcqNtf_PreProc
 ��������  : �յ�MMA��Cdma Mo Call Start Ntf��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��13��
    ��    ��   : w00242748
    �޸�����   : DTS2016010609093:�������ѵ�ʱ�����MSCC����L2״̬����ʱ����
                 ���л��档
*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmaMoCallRedialSysAcqNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf = VOS_NULL_PTR;

    pstCdmaMoCallRedialSysAcqNtf = (MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU*)pstMsg;

    /* ת������Ϣ��hxd ��xsdģ�� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallRedialSysAcqNtf->enCallType)
    {
        /* ������ԭ���߼��У���������:
           1�������ǰ1X���񲻴��ڣ���ֱ�ӷ��ؿ���ʧ��
           2�������ǰMSCC������L1״̬������ֱ�ӷ���ʧ��
           �޸ĳ�:
           1�������ǰ1X���񲻴��ڣ���ֱ�ӷ��ؿ���ʧ��
           2�������ǰMSCC������L1״̬�����򻺴����Ϣ
        */
        /* HRPD��֧�ֵ�ʱ��ֱ�ӷ��� */
        if ( VOS_FALSE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD) )
        {
            NAS_MSCC_SndMmaDataCallRedialSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL, VOS_FALSE);

            return VOS_TRUE;
        }

        /* ֻ�д���1X�����ʱ�򣬲Ÿ�HSD���ز�����ָʾ(����) */
        if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE != NAS_MSCC_GetCurr1xServiceStatus())
        {
            NAS_MSCC_SndMmaDataCallRedialSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL, VOS_FALSE);

            return VOS_TRUE;
        }

        /* ��L1 MAIN״̬��, ˵����������,��Ҫ�Ȼ�����,Ŀǰ����ֻ��SYSCFG��������Ҫ������ */
        if (NAS_MSCC_FSM_L1_MAIN == NAS_MSCC_GetCurrFsmId())
        {
            /* Modified by w00176964 for CL�����л��Ż�, 2015-12-11, begin */
            if (VOS_TRUE == NAS_MSCC_IsNeedSndHsdCdmaMoCallRedialSysAcqNtf_PreProc())
            {
                /* ���available��ʱ��������,ֹͣ�ö�ʱ�� */
                NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

                NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf(pstCdmaMoCallRedialSysAcqNtf);

                NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

                NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
            }
            else
            {
                NAS_MSCC_SndMmaDataCallRedialSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL, VOS_FALSE);
            }
        }
        else
        {
            return VOS_FALSE;
        }

        /* TO DO:����Ҫ���͸�HSD��ʱ����yanzhiji����ظ���APS��Ϣ���߼� */
        /* Modified by w00176964 for CL�����л��Ż�, 2015-12-11, end */
    }
    else
    {
        NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf(pstCdmaMoCallRedialSysAcqNtf);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc
 ��������  : �յ�MMA��Cdma Mo Call Start Ntf��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmaMoCallSuccessNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU   *pstCdmaMoCallSuccessNtf = VOS_NULL_PTR;

    pstCdmaMoCallSuccessNtf = (MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU *)pstMsg;

    /* ת������Ϣ��hxd ��xsdģ�� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallSuccessNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallSuccessNtf(pstCdmaMoCallSuccessNtf);
    }
    else
    {
        NAS_MSCC_SndXsdCdmaMoCallSuccessNtf(pstCdmaMoCallSuccessNtf);
    }

    if ((VOS_TRUE == NAS_MSCC_GetEmcCallBackEnableFlag())
     && (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL == pstCdmaMoCallSuccessNtf->enCallType))
    {
        NAS_MSCC_SetEmcCallExistFlag(VOS_TRUE);

        return VOS_FALSE;
    }

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCdmaMoCallEndNtf_PreProc
 ��������  : �յ�mma��CdmaMoCallEndNtf��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU   *pstCdmaMoCallEndNtf = VOS_NULL_PTR;

    pstCdmaMoCallEndNtf = (MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *)pstMsg;

    /* ת������Ϣ��hxd ��xsdģ�� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallEndNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallEndNtf(pstCdmaMoCallEndNtf);
    }
    else
    {
        NAS_MSCC_Set1xSysAcqMoCallFlag(VOS_FALSE);

        NAS_MSCC_SndXsdCdmaMoCallEndNtf(pstCdmaMoCallEndNtf);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCfreqLockNtf_PreProc
 ��������  : �յ�MMA��CfreqLockNtf��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

  2.��    ��   : 2016��1��6��
    ��    ��   : m00312079
    �޸�����   : DTS2016010507928:���͸�XSD����ƵЯ���Ƿ�֧��1x�ı��
*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCfreqLockNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CFREQ_LOCK_NTF_STRU   *pstCfreqLockNtf = VOS_NULL_PTR;
    VOS_UINT32                      ulIsSupport1x;

    pstCfreqLockNtf = (MMA_MSCC_CFREQ_LOCK_NTF_STRU *)pstMsg;

    /* �ַ�����Ϣ��hsd��xsdģ�� */
    ulIsSupport1x = NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X);

    if (VOS_FALSE == ulIsSupport1x)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaCfreqLockNtf_PreProc:1x unSupport!");
    }

    NAS_MSCC_SndXsdCfreqLockNtf(pstCfreqLockNtf, ulIsSupport1x);

    NAS_MSCC_SndHsdCfreqLockNtf(pstCfreqLockNtf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCdmacsqSetReq_PreProc
 ��������  : �յ�MMA��CdmacsqSetReq��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmacsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMACSQ_SET_REQ_STRU   *pstCdmacsqSetReq = VOS_NULL_PTR;

    pstCdmacsqSetReq = (MMA_MSCC_CDMACSQ_SET_REQ_STRU *)pstMsg;

    /* ת������Ϣ��hxd ��xsdģ�� */
    /*if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmacsqSetReq->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallEndNtf(pstCdmacsqSetReq);
    }
    else
    {
        NAS_MSCC_SndXsdCdmacsqSetReq(pstCdmacsqSetReq);
    }*/
    NAS_MSCC_SndXsdCdmacsqSetReq(pstCdmacsqSetReq);
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdCdmacsqSetCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdCdmacsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaCdmacsqSetCnf((XSD_MSCC_CDMACSQ_SET_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdCdmacsqSignalQualityInd_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdCdmacsqSignalQualityInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaCdmacsqSignalQualityInd((XSD_MSCC_CDMACSQ_IND_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcCLAssociatedInfoNtfWith1xLocInfo_PreProc
Description     :   ����1X��λ����Ϣ����CL������Ϣ֪ͨ
Input parameters:   VOS_VOID
Output parameters:  VOS_VOID
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-10-24
        Author  :   w00176964
        Modify content :Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcCLAssociatedInfoNtfWith1xLocInfo_PreProc(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysSrvInfoInd
)
{
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enLteSysPriClass;
    VOS_UINT8                                               ucPreAllowSrchLteFlg;
    VOS_UINT8                                               ucCurAllowSrchLteFlg;

    ucPreAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();

    /* ����1X��Ϣ��ȡLTE�Ƿ����������Լ�����������pri class */
    ucCurAllowSrchLteFlg = NAS_MSCC_GetAllowedSrchLtePriClassWith1xLocInfo(pst1xSysSrvInfoInd, &enLteSysPriClass);

    NAS_MSCC_SetAllowSrchLteFlg(ucCurAllowSrchLteFlg);

    NAS_MSCC_SndMmcCLAssociatedInfoNtf(enLteSysPriClass, ucCurAllowSrchLteFlg);

    /* ����LTE�������ѵ����,��ʱ֪ͨMMCֱ�ӹر�LTE,��1Xλ����Ϣ�����仯ʱ,MSPL�е����ȼ�
       �����仯ʱ,LTE��Ϊ������������֪ͨmmc����LTE;

       [ע��]:������ֻ��Բ��ܽ���CL��ģ�����ĳ���;����ܽ���CL��ģ����,LTE����������ʱ,MMC
       ֪ͨ��MSCC����ʧ��,MSCC��ر�LTE��HRPD,����Ҫ�������ӹر�LTE���߼���
    */
    if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        return;
    }

    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        return;
    }

    if ((VOS_TRUE  == NAS_MSCC_Get3gppActiveFlg())
     && (VOS_FALSE == ucCurAllowSrchLteFlg))
    {
        NAS_MSCC_SndMmcPowerSaveReq();
    }

    if ((VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
     && (VOS_TRUE  == ucCurAllowSrchLteFlg)
     && (VOS_FALSE == ucPreAllowSrchLteFlg))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcNoCardInitSearchWhenRcv1xSidNidInd_PreProc
 ��������  : ����1x���ϱ�������sid,nid,����MMA_GET_GEO_CNF
 �������  : MSCC_XSD_SID_NID_IND_STRU              *pst1xSidNidInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_ProcNoCardInitSearchWhenRcv1xSidNidInd_PreProc(
    MSCC_XSD_SID_NID_IND_STRU          *pst1xSidNidInd
)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();

    NAS_MSCC_Update1xNoCardInitSearchLocInfo((VOS_INT32)pst1xSidNidInd->usSid,
                                             (VOS_INT32)pst1xSidNidInd->usNid);

    NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT);

    /* Xģ���ѳɹ�������λ����Ϣ��λ����Ϣδʹ�ã�����ΪVOS_FALSE */
    pstNoCardInitSearchLocInfo->ucIsLocInfoUsed = VOS_FALSE;

    /* 1x�������,�ظ�mma�޿�����λ����Ϣ */
    NAS_MSCC_SndMmaGetGeoCnf(pstNoCardInitSearchLocInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcNoCardInitSearchWhenRcvXsdPowerSaveCnf_PreProc
 ��������  : 1x���ѱ���ϣ��ظ�MMA_GET_GEO_CNF
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_ProcNoCardInitSearchWhenRcvXsdPowerSaveCnf_PreProc(VOS_VOID)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();

    NAS_MSCC_Update1xNoCardInitSearchLocMcc(NAS_MSCC_INVALID_MCC);

    NAS_MSCC_Update1xNoCardInitSearchLocInfo(NAS_MSCC_INVALID_SID,
                                             NAS_MSCC_INVALID_NID);

    NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT);

    /* 1x���ѱ����,�ظ�mma�޿�����λ����Ϣ */
    /* ����Ҫ�ظ�stop get geo cnf��mma�ˣ�mma��stop get geo cnf״̬���£��յ�get geo cnf�жԳ崦�� */
    NAS_MSCC_SndMmaGetGeoCnf(pstNoCardInitSearchLocInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcNoCardInitSearchWhenRcv1xSystemServiceInfoInd_PreProc
 ��������  : 1x����ʧ�ܣ��ϱ���1xϵͳ��Ϣ���޷��񣬸���1x������Ϣ��Чֵ���ظ�MMA_GET_GEO_CNF
 �������  : XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysSrvInfoInd
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_ProcNoCardInitSearchWhenRcv1xSystemServiceInfoInd_PreProc(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysSrvInfoInd
)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;

    if (NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE == pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus)
    {
        pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();

        NAS_MSCC_Update1xNoCardInitSearchLocMcc(NAS_MSCC_INVALID_MCC);

        NAS_MSCC_Update1xNoCardInitSearchLocInfo(NAS_MSCC_INVALID_SID,
                                                 NAS_MSCC_INVALID_NID);

        NAS_MSCC_SetNoCardInitSearchWaitType(NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT);

        /* 1x����ʧ��,�ظ�mma�޿�����λ����Ϣ */
        NAS_MSCC_SndMmaGetGeoCnf(pstNoCardInitSearchLocInfo);
    }

    return;
}

 /*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdCdmacsqSetCnf_PreProc
 ��������  : ����MMCϵͳ��Ϣָʾ

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��11��
   ��    ��   : m00312079
   �޸�����   : CDMA1X Iteration 10 Modified
 3.��    ��   : 2015��04��11��
   ��    ��   : a00295761
   �޸�����   : CDMA1X Iteration 10 Modified
 4.��    ��   : 2015��09��11��
   ��    ��   : y00346957
   �޸�����   : modify for DTS2015070910885
 5.��    ��   : 2015��12��11��
   ��    ��   : w00176964
   �޸�����   : CL_MUTIMODE_OPTIMIZE����
 6.��    ��   : 2015��12��10��
   ��    ��   : j00354216
   �޸�����   : CL_MUTIMODE_OPTIMIZE����

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsd1xSystemServiceInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysSrvInfoInd;
    MSCC_HSD_1X_SYS_INFO_STRU                               st1xSysInfo;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8                      en1xServiceStatus;
    VOS_UINT8                                               ucIs1xLocationInfoChanged;
    NAS_MSCC_1X_SYS_INFO_STRU                              *pstOld1xSysInfo;
    VOS_UINT8                                               ucIs1xAvail;
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType;

    pst1xSysSrvInfoInd  = (XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU *)pstMsg;
    pstOld1xSysInfo     = NAS_MSCC_Get1xSysInfoAddr();

    enNoCardInitSearchWaitType = NAS_MSCC_GetNoCardInitSearchWaitType();

    if ((NAS_MSCC_FSM_L1_MAIN == NAS_MSCC_GetCurrFsmId())
     && (NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X == enNoCardInitSearchWaitType))
    {
        /* �����յ�ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND,���1x�޷���˵��1x����ʧ�ܣ���Ҫ����1xλ����ϢΪ��Чֵ */
        NAS_MSCC_ProcNoCardInitSearchWhenRcv1xSystemServiceInfoInd_PreProc(pst1xSysSrvInfoInd);

        return VOS_TRUE;
    }

    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE  == pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus)
     || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus))
    {
        ucIs1xAvail = VOS_TRUE;
    }
    else
    {
        ucIs1xAvail = VOS_FALSE;
    }

    NAS_MSCC_ProcCLAssociatedInfoNtfWith1xLocInfo_PreProc(pst1xSysSrvInfoInd);

    st1xSysInfo.usBandClass = pst1xSysSrvInfoInd->stSysSrvInfo.usBandClass;
    st1xSysInfo.usChannel   = pst1xSysSrvInfoInd->stSysSrvInfo.usFreq;
    st1xSysInfo.usSid       = pst1xSysSrvInfoInd->stSysSrvInfo.usSid;
    st1xSysInfo.usNid       = pst1xSysSrvInfoInd->stSysSrvInfo.usNid;

    /* Send the 1x Sys Change Ind to HSD if EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        NAS_MSCC_SndHsd1xSysChgInd(ucIs1xAvail, &st1xSysInfo);
    }

    if ((pstOld1xSysInfo->ulMcc != pst1xSysSrvInfoInd->stSysSrvInfo.stServiceInfo.ulMcc)
     || (pstOld1xSysInfo->ulMnc != pst1xSysSrvInfoInd->stSysSrvInfo.stServiceInfo.usMnc)
     || (pstOld1xSysInfo->usSid != pst1xSysSrvInfoInd->stSysSrvInfo.usSid)
     || (pstOld1xSysInfo->usNid != pst1xSysSrvInfoInd->stSysSrvInfo.usNid))
    {
        ucIs1xLocationInfoChanged = VOS_TRUE;
    }
    else
    {
        ucIs1xLocationInfoChanged = VOS_FALSE;
    }

    en1xServiceStatus = NAS_MSCC_Convert1xServiceStatusToMsccFormat(pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus);

    NAS_MSCC_SetCurr1xServiceStatus(en1xServiceStatus);

    NAS_MSCC_Update1xSysInfo(pst1xSysSrvInfoInd);

    NAS_MSCC_SndMma1xSystemServiceInfoInd(pst1xSysSrvInfoInd);

    if ((VOS_TRUE == ucIs1xLocationInfoChanged)
     && (VOS_TRUE == ucIs1xAvail))
    {
        /* Update the 1x location info to NVIM if 1x has normal service and location info has changed */
        NAS_MSCC_UpdateLocationInfoToNvim();
    }

    /* in CL system acquire fsm, then enter fsm to proc this msg */
    if (NAS_MSCC_FSM_SYS_ACQ == NAS_MSCC_GetCurrFsmId())
    {
        if (NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND == NAS_MSCC_GetFsmTopState())
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsd1xSystemTimeInd_PreProc
 ��������  : ����1Xϵͳʱ���ϱ�

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��04��
   ��    ��   : L00256032
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsd1xSystemTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMma1xSystemTimeInd((XSD_MSCC_1X_SYSTEM_TIME_IND_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdSidNidInd_PreProc
 ��������  : mscc����xsd��sid�����ϱ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : BOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdSidNidInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SID_NID_IND_STRU                              *pstRcvMsg = VOS_NULL_PTR;
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType;

    enNoCardInitSearchWaitType = NAS_MSCC_GetNoCardInitSearchWaitType();

    pstRcvMsg = (MSCC_XSD_SID_NID_IND_STRU *)pstMsg;

    if ((NAS_MSCC_FSM_L1_MAIN == NAS_MSCC_GetCurrFsmId())
     && (NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X == enNoCardInitSearchWaitType))
    {
        /* �����յ�ID_XSD_MSCC_1X_SID_NID_IND,����sid,nid,����MMA_GET_GEO_CNF */
        NAS_MSCC_ProcNoCardInitSearchWhenRcv1xSidNidInd_PreProc(pstRcvMsg);

        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSidNidInd(pstRcvMsg->usSid,
                             pstRcvMsg->usNid);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_CovertSessionType_PreProc
 ��������  : ��HSD_MSCC֮���session typeת��ΪMSCC_MMA֮���session type
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
*****************************************************************************/
MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32 NAS_MSCC_CovertSessionType_PreProc(
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32               enSessionRelType
)
{
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType;

    if (HSD_MSCC_SESSION_RELEASE_TYPE_0 == enSessionRelType)
    {
        enCurrSessionRelType = MSCC_MMA_SESSION_RELEASE_TYPE_0;
    }
    else if (HSD_MSCC_SESSION_RELEASE_TYPE_A == enSessionRelType)
    {
        enCurrSessionRelType = MSCC_MMA_SESSION_RELEASE_TYPE_A;
    }
    else
    {
        enCurrSessionRelType = MSCC_MMA_SESSION_RELEASE_TYPE_BUTT;
    }

    return enCurrSessionRelType;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvHsdSessionInfoInd_PreProcs
Description     :   Receive and process the HSD session
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   VOS_TRUE------------the current event is finished


Modify History  :
1)  Date           : 2015-02-04
    Author         : w00208541
    Modify content : Create
2)  Date           : 2015-04-07
    Author         : t00323010
    Modify content : store service status info for Iteration 10
3)  Date           : 2015-04-16
    Author         : y00307564
    Modify content : Iteration 10 Modify
4)  Date           : 2015-05-30
    Author         : l00324781
    Modify content : Iteration 12 Modify, NAS_MSCC_SndMmaHrpdServiceStatusInd add one para
5)  Date           : 2015-08-24
    Author         : m00312079
    Modify content : DTS2015082004682:�յ�session�ɹ���������scan timer�������У���ͣ����
                     ��ҪӦ����L2C������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdSessionNegRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SESSION_NEG_RSLT_IND_STRU                     *pstSessionInfo = VOS_NULL_PTR;
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enSessionRelType;

    pstSessionInfo = (HSD_MSCC_SESSION_NEG_RSLT_IND_STRU *)pstMsg;

    if (VOS_TRUE == NAS_MSCC_IsNeedDiscardHsdServiceStatusInd_PreProc(pstSessionInfo->enRslt))
    {
        NAS_MSCC_MNTN_LogDiscardServStaInfo(NAS_MSCC_DISCARD_HSD_SERVICE_STATUS_IND);

        return VOS_TRUE;
    }

    if (HSD_MSCC_SESSION_NEG_RESULT_SUCC == pstSessionInfo->enRslt)
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

        enSessionRelType = NAS_MSCC_CovertSessionType_PreProc(pstSessionInfo->enCurrSessionRelType);

        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE,
                                            pstSessionInfo->ucIsNewSession,
                                            pstSessionInfo->ucIsEhrpdSupport,
                                            enSessionRelType);

        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE);

        /* �ж��Ƿ���Ҫ������������BSR Timer */
        if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
        {
            if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
            {
                NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
                NAS_MSCC_StartBsrTimer();
            }
            else
            {
                if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
                {
                    NAS_MSCC_StartBsrTimer();
                }
            }
        }
    }
    else
    {
        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            pstSessionInfo->ucIsNewSession,
                                            pstSessionInfo->ucIsEhrpdSupport,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);

        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdOverheadMsgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstHsdMsccOhm            = VOS_NULL_PTR;
    NAS_MSCC_HRPD_SYS_INFO_STRU         stOldHrpdSysInd;

    pstHsdMsccOhm = (HSD_MSCC_OVERHEAD_MSG_IND_STRU *)pstMsg;

    PS_MEM_SET(&stOldHrpdSysInd, 0x0, sizeof(NAS_MSCC_HRPD_SYS_INFO_STRU));
    PS_MEM_CPY(&stOldHrpdSysInd, NAS_MSCC_GetHrpdSysInfoAddr(), sizeof(NAS_MSCC_HRPD_SYS_INFO_STRU));

    NAS_MSCC_UpdateHrpdSysInfo(pstHsdMsccOhm);

    NAS_MSCC_SndMmaHrpdOverheadMsgInd((HSD_MSCC_OVERHEAD_MSG_IND_STRU *)pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvHsdDataCallRedialAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU             *pstDataCallSysAcqCnf;

    pstDataCallSysAcqCnf = (HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaDataCallRedialSysAcqInd(pstDataCallSysAcqCnf->enRslt, pstDataCallSysAcqCnf->ucIsEhrpdSupport);



    return VOS_TRUE;

}


VOS_UINT32 NAS_MSCC_RcvHsdHrpdCasStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_CAS_STATUS_IND_STRU       *pstHsdMsccCasStatusInd   = VOS_NULL_PTR;

    pstHsdMsccCasStatusInd = (HSD_MSCC_CAS_STATUS_IND_STRU *)pstMsg;

    if (HSD_MSCC_HRPD_CAS_STATUS_ENUM_CONN == pstHsdMsccCasStatusInd->enCasStatus)
    {
        NAS_MSCC_SetHrpdConnExistFlg(VOS_TRUE);
    }
    else
    {
        NAS_MSCC_SetHrpdConnExistFlg(VOS_FALSE);
    }

    /* send cas status to xsd */
    NAS_MSCC_SndXsdHrpdCasStatusInd((HSD_MSCC_CAS_STATUS_IND_STRU *)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_ProcBsrTimerExpired_PreProc
Description     :   This function is used to check whether satisfy conditions to enter BSR FSM
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:������BSR����
                    VOS_FALSE:����BSR����
Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_ProcBsrTimerExpired_PreProc(VOS_VOID)
{
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enMsccSleepTimerStatus;
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enMsccAvailTimerStatus;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurrFsmId;
    VOS_UINT8                           ucHrpdConnExistFlg;
    VOS_UINT8                           ucLteEpsConnExistFlg;
    NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU    stBsrCtrlInfo;

    enMsccSleepTimerStatus  = NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_SLEEP_TIMER);
    enMsccAvailTimerStatus  = NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_AVAILABLE_TIMER);
    ucHrpdConnExistFlg      = NAS_MSCC_GetHrpdConnExistFlg();
    ucLteEpsConnExistFlg    = NAS_MSCC_GetLteEpsConnExistFlg();
    enCurrFsmId             = NAS_MSCC_GetCurrFsmId();

    /* log ��ӡ */
    stBsrCtrlInfo.en3gppPsServiceStatus     = NAS_MSCC_GetCurr3gppPsServiceStatus();
    stBsrCtrlInfo.ucSimPsRegStatus          = NAS_MSCC_GetSimPsRegStatus();
    stBsrCtrlInfo.enHrpdPsServiceStatus     = NAS_MSCC_GetCurrHrpdServiceStatus();
    stBsrCtrlInfo.enCsimCardStatus          = NAS_MSCC_GetCsimCardStatus();
    stBsrCtrlInfo.enUsimCardStatus          = NAS_MSCC_GetUsimCardStatus();
    stBsrCtrlInfo.ucMlplMsplValidFlag       = NAS_MSCC_GetMlplMsplValidFlag();
    stBsrCtrlInfo.ulIsHrpdLteBothSupported  = NAS_MSCC_IsHrpdAndLteBothSupported();
    stBsrCtrlInfo.ucHrpdConnExistFlg        = ucHrpdConnExistFlg;
    stBsrCtrlInfo.ucLteEpsConnExistFlg      = ucLteEpsConnExistFlg;
    stBsrCtrlInfo.enMsccSleepTimerStatus    = enMsccSleepTimerStatus;
    stBsrCtrlInfo.enMsccAvailTimerStatus    = enMsccAvailTimerStatus;
    stBsrCtrlInfo.enCurrFsmId               = enCurrFsmId;

    NAS_MSCC_MNTN_LogBsrCtrlInfo(&stBsrCtrlInfo);


    /* �����������ض�ʱ�������У�����Ҫ����BSR FSM */
    if ((NAS_MSCC_TIMER_STATUS_RUNING == enMsccAvailTimerStatus)
     || (NAS_MSCC_TIMER_STATUS_RUNING == enMsccSleepTimerStatus))
    {
        return VOS_TRUE;
    }

    /* ���MSCC����״̬��ִ�й����У�����BSR Retry��ʱ�����ȴ� */
    /* ���������ҵ������У�����BSR Retry��ʱ�����ȴ� */
    if ((NAS_MSCC_FSM_L1_MAIN != enCurrFsmId)
     || (VOS_TRUE == ucLteEpsConnExistFlg)
     || (VOS_TRUE == ucHrpdConnExistFlg))
    {
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                      TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);

        return VOS_TRUE;
    }

    /* �����ǰ���粻��������ȼ����磬��Ҫ����BSR FSM */
    if (VOS_TRUE == NAS_MSCC_IsBgSearchHighPriSysAllowed())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    return NAS_MSCC_ProcBsrTimerExpired_PreProc();
}


VOS_UINT32 NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_ProcBsrTimerExpired_PreProc();
}


VOS_UINT32 NAS_MSCC_RcvXsdSysAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU   *pstXsdSysAcqCnf = VOS_NULL_PTR;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdSrvst;

    pstXsdSysAcqCnf = (XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU *)pstMsg;

    /* power off�����л���SCAN��ʱ����ʱ����������յ�XSD�ϱ��������,ֱ���ϱ�MMA����ʧ�� */
    if (NAS_MSCC_FSM_POWER_OFF == NAS_MSCC_GetCurrFsmId())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL),
                                           MSCC_MMA_ACQ_SYS_TYPE_1X,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
        return VOS_TRUE;
    }

    /* Get the final result to send to MMA */
    NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstXsdSysAcqCnf->enRslt),
                                       MSCC_MMA_ACQ_SYS_TYPE_1X,
                                       MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);

    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstXsdSysAcqCnf->enRslt)
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

        return VOS_TRUE;
    }

    /* if bothe 1x,lte and hrpd are no service, start scan timer */
    if (NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL == pstXsdSysAcqCnf->enRslt)
    {


        enHrpdSrvst = NAS_MSCC_GetCurrHrpdServiceStatus();

        if ((NAS_MSCC_SERVICE_STATUS_NO_SERVICE == NAS_MSCC_GetCurr3gppPsServiceStatus())
         && (NAS_MSCC_SERVICE_STATUS_NO_SERVICE == enHrpdSrvst))
        {
            /* we start the timer only in CL mode */
            if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
            {
                (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
            }
        }
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvXsdSysAcqStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

    NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_1X);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvHsdSysAcqStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

    /* �����֧��LTE,��ΪHRPD�����Ĳ�������;֪ͨ����ʼ��ϵͳģʽΪDO */
    if (VOS_FALSE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
    {
        NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO);

        return VOS_TRUE;
    }

    /* CLģʽ�²��ڲ���������,֪ͨMMA������ʼ,ģʽΪDO_LTE��������CL�������̿�ʼʱ֪ͨ */
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);
    }

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsNeedDiscardHsdServiceStatusInd_PreProc
Description     :   �Ƿ���Ҫ����״̬�ϱ�.
Input parameters:   HSD_MSCC_SESSION_NEG_RSLT_ENUM_UINT32       enRslt
Output parameters:  None.
Return Value    :   TRUE
Modify History:
    1)  Date    :   2015-04-14
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNeedDiscardHsdServiceStatusInd_PreProc(
    HSD_MSCC_SESSION_NEG_RSLT_ENUM_UINT32       enRslt
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm  = VOS_NULL_PTR;

    pstCurFsm = NAS_MSCC_GetCurFsmAddr();
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == pstCurFsm->enFsmId)
    {
        if ((NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF            == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE  == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF_REACQ_LTE == pstCurFsm->ulState))
        {
            return VOS_TRUE;
        }

        if (HSD_MSCC_SESSION_NEG_RESULT_SUCC != enRslt)
        {
            if (NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF == pstCurFsm->ulState)
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaHandsetInfoQryReq_PreProc
 ��������  : �յ�MMA��HandsetInfoQryReq��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaHandsetInfoQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU   *pstInfoQryReq = VOS_NULL_PTR;

    pstInfoQryReq = (MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU *)pstMsg;

    /* ��XSD���Ͳ�ѯ���� */
    NAS_MSCC_SndXsdHandsetInfoQryReq((VOS_UINT32)pstInfoQryReq->enInfoType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdHandsetInfoQryReq_PreProc
 ��������  : �յ�XSD��ID_XSD_MSCC_HANDSET_INFO_QRY_CNF��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32 NAS_MSCC_RcvXsdHandsetInfoQryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstCnfMsg  = VOS_NULL_PTR;
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU  stInfoCnf;

    PS_MEM_SET(&stInfoCnf, 0x00, sizeof(MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU));

    pstCnfMsg = (XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *)pstMsg;

    stInfoCnf.enInfoType     = (MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32)pstCnfMsg->ulInfoType;
    stInfoCnf.ucCasState     = pstCnfMsg->ucCasState;
    stInfoCnf.ucCasSubSta    = pstCnfMsg->ucCasSubSta;
    stInfoCnf.enHighVer      = (MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8)pstCnfMsg->ucHighVer;

    /* ��MMA���Ͳ�ѯ�ظ� */
    NAS_MSCC_SndMmaHandsetInfoQryCnf(&stInfoCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaPsRatTypeNtf_Main_PreProc
 ��������  : �յ�MMAģ���ID_MMA_MSCC_PS_RAT_TYPE_NTF��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��06��04��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPsRatTypeNtf_Main_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 1x�з���ʱ�Ѿ�������available��ʱ����������L */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaQuitCallBackInd_PreProc
 ��������  : �յ�MMAģ���ID_MMA_MSCC_QUIT_CALL_BACK_IND��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��08��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaQuitCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndXsdEndEmcCallBackNtf();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaSetCSidListReq_PreProc
 ��������  : AT CSIDLIST
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSetCSidListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SET_CSIDLIST_REQ_STRU     *pstSndMsg = VOS_NULL_PTR;
    MMA_MSCC_SET_CSIDLIST_REQ_STRU     *pstRcvMsg = VOS_NULL_PTR ;

    pstRcvMsg = (MMA_MSCC_SET_CSIDLIST_REQ_STRU *)pstMsg;
    /* �����ڴ�  */
    pstSndMsg = (MSCC_XSD_SET_CSIDLIST_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaSetCSidListReq_PreProc:ERROR: Memory Alloc Error for pMsg");
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
                     sizeof(MSCC_XSD_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstSndMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_SET_CSIDLIST_REQ;
    PS_MEM_CPY(&pstSndMsg->stSidWhiteList, &pstRcvMsg->stSidWhiteList, sizeof(NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU));

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdSetCSidListCnf_PreProc
 ��������  : set csid list ����ϱ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdSetCSidListCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SET_CSIDLIST_CNF_STRU     *pstSndMsg = VOS_NULL_PTR;
    XSD_MSCC_SET_CSIDLIST_CNF_STRU     *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (XSD_MSCC_SET_CSIDLIST_CNF_STRU *)pstMsg;
        /* ������Ϣ�� */
    pstSndMsg = (MSCC_MMA_SET_CSIDLIST_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvXsdSetCSidListCnf_PreProc():ERROR:Memory Alloc Error!");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(MSCC_MMA_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstSndMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(MSCC_MMA_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_MSCC_MMA_SET_CSIDLIST_CNF;
    pstSndMsg->ulRslt                        = pstRcvMsg->ulRslt;

    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* ������Ϣ */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdEmcCallBackNtf_PreProc
 ��������  : call back ģʽ�����ϱ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdEmcCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_EMC_CALLBACK_IND_STRU                         *pstEmcCallBackInd = VOS_NULL_PTR;
    NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32              enCallBackMode;
    VOS_UINT8                                               ucPreEmcCallExistFlag;

    pstEmcCallBackInd     = (XSD_MSCC_EMC_CALLBACK_IND_STRU *)pstMsg;
    enCallBackMode        = pstEmcCallBackInd->enCallBackState;
    ucPreEmcCallExistFlag = NAS_MSCC_GetEmcCallExistFlag();

    /* ֪ͨMMA�������غ�ģʽ */
    NAS_MSCC_SndMmaEmcCallBackInd(enCallBackMode);

    /* ����������غ�ģʽ����ر�HRPD��LTE */
    if ( (NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE != enCallBackMode)
      && (VOS_TRUE == ucPreEmcCallExistFlag) )
    {
        /* ��״̬���������� */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdServiceAvailableInd_PreProc
 ��������  : MSCCģ���յ�XSD�ϱ��ķ������ָʾ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��25��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdSyncServiceAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pst1xSyncSrvAvailableInd = VOS_NULL_PTR;
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                    stSyncSrvAvailInd;

    pst1xSyncSrvAvailableInd = (XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU *)pstMsg;

    PS_MEM_SET(&stSyncSrvAvailInd, 0x00, sizeof(stSyncSrvAvailInd));
    stSyncSrvAvailInd.usBandClass     = pst1xSyncSrvAvailableInd->usBandClass;
    stSyncSrvAvailInd.usFreq          = pst1xSyncSrvAvailableInd->usFreq;
    stSyncSrvAvailInd.usSid           = pst1xSyncSrvAvailableInd->usSid;
    stSyncSrvAvailInd.usNid           = pst1xSyncSrvAvailableInd->usNid;
    stSyncSrvAvailInd.enServiceStatus = pst1xSyncSrvAvailableInd->enServiceStatus;
    stSyncSrvAvailInd.ucRoamingInd    = pst1xSyncSrvAvailableInd->ucRoamingInd;

    NAS_MSCC_SndMmaSyncServiceAvailInd(&stSyncSrvAvailInd);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdCurUeStatusInd_PreProc
 ��������  : MSCCģ���յ�XSD�ϱ���UE STATUS
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��17��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdCurUeStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_UE_STATE_IND_STRU         *pstUeStatusInd;

    pstUeStatusInd = (XSD_MSCC_UE_STATE_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaUeStatusInd(pstUeStatusInd->ucUeMainState,
                               pstUeStatusInd->ucUeSubState);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaHdrcsqSetReq_PreProc
 ��������  : �յ�MMA��HdrcsqSetReq��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaHdrcsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_HDR_CSQ_SET_REQ_STRU   *pstHdrcsqSetReq = VOS_NULL_PTR;

    pstHdrcsqSetReq = (MMA_MSCC_HDR_CSQ_SET_REQ_STRU *)pstMsg;

    NAS_MSCC_SndHsdHdrcsqSetReq(pstHdrcsqSetReq);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdHdrcsqSetCnf_PreProc
 ��������  : �յ�hsd��HdrcsqSetcnf��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32 NAS_MSCC_RcvHsdHdrcsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_HDR_CSQ_SET_CNF_STRU      *pstHdrcsqSetCnf= VOS_NULL_PTR;

    pstHdrcsqSetCnf = (HSD_MSCC_HDR_CSQ_SET_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaHdrcsqSetCnf(pstHdrcsqSetCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdHdrcsqInd_PreProc
 ��������  : �յ�hsd��Hdrcsqind��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32 NAS_MSCC_RcvHsdHdrcsqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_HDR_CSQ_IND_STRU          *pstHdrcsqInd = VOS_NULL_PTR;

    pstHdrcsqInd = (HSD_MSCC_HDR_CSQ_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaHdrcsqSignalQualityInd(pstHdrcsqInd);

    return VOS_TRUE;
}

/* Added by w00176964 for CL�����л��Ż�, 2015-12-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdHdrcsqInd_PreProc
 ��������  : �Ƿ���Ҫ��HSD���Ϳ�����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��13��
    ��    ��   : w00242748
    �޸�����   : DTS2016010609093:�������ѵ�ʱ�����MSCC����L2״̬����ʱ����
                 ���л��棬���ú����е��߼��Ƴ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNeedSndHsdCdmaMoCallRedialSysAcqNtf_PreProc(VOS_VOID)
{
    VOS_UINT8                           ucHrdpActiveFlg;
    VOS_UINT8                           uc3gppActiveFlg;


    /* DO����active״̬�Լ�L��DO������deactive̬ʱ���Է��Ϳ������������HSD */
    ucHrdpActiveFlg = NAS_MSCC_GetHrpdActiveFlg();
    uc3gppActiveFlg = NAS_MSCC_Get3gppActiveFlg();

    if (VOS_TRUE == ucHrdpActiveFlg)
    {
        return VOS_TRUE;
    }

    if ((VOS_FALSE == ucHrdpActiveFlg)
     && (VOS_FALSE == uc3gppActiveFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for CL�����л��Ż�, 2015-12-11, end */






#endif


#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcAcqInd_PreProc
 ��������  : �յ�MSCCģ���acq ind��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ACQ_IND_STRU               *pstMmcMmaAcqInd = VOS_NULL_PTR;

    pstMmcMmaAcqInd = (MMC_MSCC_ACQ_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaAcqInd(pstMmcMmaAcqInd);

    return VOS_TRUE;
}
#endif



#if ((FEATURE_ON == FEATURE_MULTI_MODEM) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))

/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcPsServiceConnStatusInd_PreProc
 ��������  : �յ�MSCCģ��PS�������״̬��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��07��
   ��    ��   : t00323010
   �޸�����   : �洢����״̬��mscc ctx,for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPsServiceConnStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU                *pstPsServiceConnStatusInd = VOS_NULL_PTR;

    pstPsServiceConnStatusInd = (MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU *)pstMsg;

    if (VOS_TRUE == pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag)
    {
        NAS_MSCC_SetLteEpsConnExistFlg(VOS_TRUE);
    }
    else
    {
        NAS_MSCC_SetLteEpsConnExistFlg(VOS_FALSE);
    }

    NAS_MSCC_SndMmaPsServiceConnStatusInd(pstPsServiceConnStatusInd);

    return VOS_TRUE;
}
#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaOtherModemInfoNotify_PreProc
 ��������  : �յ�ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaOtherModemInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstOtherModemInfoNtf = VOS_NULL_PTR;

    pstOtherModemInfoNtf = (MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcOtherModemInfoNotify(pstOtherModemInfoNtf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaOtherModemDplmnNplmnInfoNotify_PreProc
 ��������  : �յ�mma��ID_MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY��Ϣ��Ԥ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��05��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaOtherModemDplmnNplmnInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       *pstOhterModemDplmnNplmnInfoNtf = VOS_NULL_PTR;

    pstOhterModemDplmnNplmnInfoNtf = (MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify(pstOhterModemDplmnNplmnInfoNtf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaNcellInfoNotify_PreProc
 ��������  : �յ�mma��ID_MSCC_MMC_NCELL_INFO_NOTIFY��Ϣ��Ԥ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaNcellInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU    *pstNcellInfoNtf = VOS_NULL_PTR;

    pstNcellInfoNtf = (MMA_MSCC_NCELL_INFO_NOTIFY_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcNcellInfoNotify(pstNcellInfoNtf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaPsTransferNotify_PreProc
 ��������  : �յ�ID_MSCC_MMC_PS_TRANSFER_IND��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPsTransferNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU   *pstPsTransferNtf = VOS_NULL_PTR;

    pstPsTransferNtf = (MMA_MSCC_PS_TRANSFER_NOTIFY_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcPsTransferNotify(pstPsTransferNtf);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaSrvAcqReq_PreProc
 ��������  : MMC�յ�mma��srv acq req��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��21��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList    = VOS_NULL_PTR;
    VOS_UINT32                          i;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulEnterFsmFlg;
    VOS_UINT32                          ulState;
#endif

    pstSrvAcqReq = (MMA_MSCC_SRV_ACQ_REQ_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    ulEnterFsmFlg = VOS_FALSE;
#endif
    pstRatList    = &(pstSrvAcqReq->stRatList);

    for (i = 0; i < pstRatList->ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_DSDS)
        /* ĿǰCLģʽ��û������ʹ�ó����������ȱ��� */
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL == pstRatList->aenRatType[i])
        {
            /* Set the Camp On flag to FALSE */
            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

            /* ת������Ϣ��MMCģ�� */
            NAS_MSCC_SndMmcSrvAcqReq(pstSrvAcqReq);
        }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X == pstRatList->aenRatType[i])
        {
            ulState = NAS_MSCC_GetFsmTopState();

            if ( (NAS_MSCC_FSM_L1_MAIN == NAS_MSCC_GetCurrFsmId())
              && (NAS_MSCC_L1_STA_DEACTIVE == ulState) )
            {
                /* MSCC����deactive״̬�Ļ�����Ҫ��״̬������ */
                ulEnterFsmFlg = VOS_TRUE;
            }
            else
            {
                NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

                NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

                /* ת������Ϣ��1Xģ�� */
                NAS_MSCC_SndXsdSrvAcqReq(pstSrvAcqReq);
            }
        }

        /* Ŀǰû������ʹ�ó����������ȱ��� */
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD == pstRatList->aenRatType[i])
        {
            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

            /* ת������Ϣ��HSDģ�� */
            NAS_MSCC_SndHsdSrvAcqReq(pstSrvAcqReq);
        }
#endif
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == ulEnterFsmFlg)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaBeginSessionNotify_PreProc
 ��������  : �յ�mma��begin session notify��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��21��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaBeginSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstBeginSessionNtf = (MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *)pstMsg;

    pstRatList = &(pstBeginSessionNtf->stRatList);

    for (i = 0; i < pstRatList->ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_DSDS)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL == pstRatList->aenRatType[i])
        {
            /* ת������Ϣ��MMCģ�� */
            NAS_MSCC_SndMmcBeginSessionNotify(pstBeginSessionNtf);
        }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X == pstRatList->aenRatType[i])
        {
            /* ת������Ϣ��1Xģ�� */
            NAS_MSCC_SndXsdBeginSessionNotify(pstBeginSessionNtf);
        }

        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD == pstRatList->aenRatType[i])
        {
            /* ��������û��HSD�Ĵ��뿪����Ŀǰû��Ӧ�ó��� */

            /* ת������Ϣ��HSDģ�� */
            NAS_MSCC_SndHsdBeginSessionNotify(pstBeginSessionNtf);
        }
#endif
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaEndSessionNotify_PreProc
 ��������  : �յ�mma��end session notify��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��21��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaEndSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEndSessionNtf = (MMA_MSCC_END_SESSION_NOTIFY_STRU *)pstMsg;

    pstRatList = &(pstEndSessionNtf->stRatList);

    for (i = 0; i < pstRatList->ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_DSDS)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL == pstRatList->aenRatType[i])
        {
            /* ת������Ϣ��MMCģ�� */
            NAS_MSCC_SndMmcEndSessionNotify(pstEndSessionNtf);
        }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X == pstRatList->aenRatType[i])
        {
            /* ת������Ϣ��1Xģ�� */
            NAS_MSCC_SndXsdEndSessionNotify(pstEndSessionNtf);
        }

        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD == pstRatList->aenRatType[i])
        {
            /* ת������Ϣ��HSDģ�� */
            NAS_MSCC_SndHsdEndSessionNotify(pstEndSessionNtf);
        }
#endif
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : MSCC_RcvMmcSrvAcqCnf_PreProc
 ��������  : �յ�mmc��srv acq cnf��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��02��
   ��    ��   : x00314862
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SRV_ACQ_CNF_STRU           *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (MMC_MSCC_SRV_ACQ_CNF_STRU *)pstMsg;

    /* Ŀǰ������1X��LTEһ���ѵó���������CDMA֧��IMS��CLģʽʱ������ͬʱ��1X��LTE��
       ֻҪ��һ�����뼼���ɹ�����͸�MMA�ظ��ɹ���Ŀǰû��ʹ�ó��� */

    if (NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        NAS_MSCC_Set3gppCampOnFlag(VOS_TRUE);
    }

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmaSrvAcqCnf(pstSrvAcqCnf);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdSrvAcqCnf_PreProc
 ��������  : �յ�XSD��srv acq cnf��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��21��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SRV_ACQ_CNF_STRU          *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (XSD_MSCC_SRV_ACQ_CNF_STRU *)pstMsg;

    /* Ŀǰ������1X��LTEһ���ѵó���������CDMA֧��IMS��CLģʽʱ������ͬʱ��1X��LTE��
       ֻҪ��һ�����뼼���ɹ�����͸�MMA�ظ��ɹ���Ŀǰû��ʹ�ó��� */

    if (NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        NAS_MSCC_Set1xCampOnFlag(VOS_TRUE);
    }

    /* ת������Ϣ��MMCģ�飬����MMC��MSCC�Ľӿڶ���ת������NAS_MSCC_PIF_SRV_ACQ_CNF_STRU
       �������ֱ��ǿ��ת�����и��� */
    NAS_MSCC_SndMmaSrvAcqCnf((MMC_MSCC_SRV_ACQ_CNF_STRU *)pstSrvAcqCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdSrvAcqCnf_PreProc
 ��������  : �յ�HSD��srv acq cnf��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��21��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SRV_ACQ_CNF_STRU          *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (XSD_MSCC_SRV_ACQ_CNF_STRU *)pstMsg;

    if (NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        NAS_MSCC_SetHrpdCampOnFlag(VOS_TRUE);
    }

    /* ת������Ϣ��MMCģ�飬����MMC��MSCC�Ľӿڶ���ת������NAS_MSCC_PIF_SRV_ACQ_CNF_STRU
       �������ֱ��ǿ��ת�����и��� */
    NAS_MSCC_SndMmaSrvAcqCnf((MMC_MSCC_SRV_ACQ_CNF_STRU *)pstSrvAcqCnf);

    return VOS_TRUE;
}
#endif



#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMsccImsSrvInfoNotify_PreProc
 ��������  : �յ�ID_MMA_MSCC_IMS_SRV_INFO_NOTIFY��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��30��
   ��    ��   : l00208516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaImsSrvInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU  *pstImsSrvInfoNtf = VOS_NULL_PTR;

    pstImsSrvInfoNtf = (MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU *)pstMsg;

    /* ת������Ϣ��MMCģ�� */
    NAS_MSCC_SndMmcImsSrvInfoNotify(pstImsSrvInfoNtf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvImsaImsVoiceCapNotify_PreProc
 ��������  : �յ�CAS��ѯϵͳ�Ƿ���negativeϵͳ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��26��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��25��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  3.��    ��   : 2015��8��14��
    ��    ��   : n00269697
    �޸�����   : DTS2015072803051��ims������ע��Ҳ���ϱ�IMS������������֮ǰ�ж�
                 ��ʱ���Ƿ����е������ſ�
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvImsaImsVoiceCapNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU                    *pstImsVoiceCap = VOS_NULL_PTR;
    VOS_UINT8                                               ucImsVoiceAvail;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8                      enOldImsVoiceCap;
    NAS_MSCC_FSM_CTX_STRU                                   *pstCurFsm = VOS_NULL_PTR;

    enOldImsVoiceCap = NAS_MSCC_GetImsVoiceCapability();

    pstImsVoiceCap          = (IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;



    /* ֹͣ�ȴ�IMSA��IMS voice�Ƿ������Ϣ��ʱ�� */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY);

    /* ����IMS voice�Ƿ������Ϣ��SDC�� */
    if (MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE == pstImsVoiceCap->enImsVoiceCap)
    {
        ucImsVoiceAvail = VOS_TRUE;
    }
    else
    {
        ucImsVoiceAvail = VOS_FALSE;
    }

    /* ֪ͨMMC��ǰIMS voice�Ƿ���� */
    /* ����ǹػ����̣��򲻸�MMC��ImsVoiceCapInd����Ϊ��EPS ONLY�£���disable lte���Ϳ��ܵ��¹ػ�ʱ����detach */
    pstCurFsm = NAS_MSCC_GetCurFsmAddr();
    if ((NAS_MSCC_FSM_POWER_OFF != pstCurFsm->enFsmId)
     || (NAS_MSCC_POWER_OFF_STA_WAIT_IMSA_POWER_OFF_CNF != pstCurFsm->ulState))
    {
        NAS_MSCC_SndMmcImsVoiceCapNotify(ucImsVoiceAvail, pstImsVoiceCap->ucIsExistPersistentBearer);
    }

    NAS_MSCC_SetPersistentBearerState(pstImsVoiceCap->ucIsExistPersistentBearer);

    NAS_MSCC_SetImsVoiceCapability(pstImsVoiceCap->enImsVoiceCap);

    if (enOldImsVoiceCap != pstImsVoiceCap->enImsVoiceCap)
    {
        /* ֪ͨMMA��ǰIMS VOICE�Ƿ���� */
        NAS_MSCC_SndMmaImsVoiceCapInd(ucImsVoiceAvail);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvTiWaitImsaImsVoiceCapNtfExpired_PreProc
 ��������  : �յ���ʱ��TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY��ʱ��Ϣ��Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��25��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

  3.��    ��   : 2015��12��2��
    ��    ��   : w00167002
    �޸�����   : DTS2015111102897:��L��EPS ONLYע��ɹ���CSע��ʧ��17��imsע��ɹ���
                 ��IMS�绰ʱ�򣬷�����С���л�����ôLNAS֪ͨMMC��ǰTAU�ɹ���
                 MMC��֪ͨ��MSCC��MSCC����35s��ʱ�ڡ�
                 MMC֪ͨMSCC��ǰ�������񣬵�����Ϊ����״̬û�иı䣬����û��֪ͨ��
                 IMSA.35S��ʱ����ʱ��MSCC�������޸�IMSΪ�����ã�����disable lte��IMS�绰
                 ʧ�ܡ�
                 ��lihongȷ�ϣ�IMSA��IMS���������ı�ʱ�򣬻�֪ͨ��MSCC�����MSCC֪ͨ
                 IMSA��ǰ�ķ���״̬����IMSAҲ��֪ͨMSCC��ǰIMS��Ϣ�������������,
                 ��35S��ʱ����ʱʱ��MSCC��֪ͨMMC�Լ�ά����IMS��Ϣ��
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaImsVoiceCapNtfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucImsVoiceAvailFlg;
    VOS_UINT8                           ucIsExistPersistentBearer;

    ucImsVoiceAvailFlg                  = VOS_FALSE;
    ucIsExistPersistentBearer           = VOS_FALSE;

    if (MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE == NAS_MSCC_GetImsVoiceCapability())
    {
        ucImsVoiceAvailFlg              = VOS_TRUE;
    }

    if (NAS_MSCC_PERSISTENT_BEARER_STATE_EXIST == NAS_MSCC_GetPersistentBearerState())
    {
        ucIsExistPersistentBearer       = VOS_TRUE;
    }

    NAS_MSCC_SndMmcImsVoiceCapNotify(ucImsVoiceAvailFlg, ucIsExistPersistentBearer);

    NAS_MSCC_SndMmaImsVoiceCapInd(ucImsVoiceAvailFlg);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaImsStartReq_PreProc
 ��������  : �յ�ID_MMA_MSCC_IMS_START_REQ��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
  1.��    ��   : 2015��4��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��26��
    ��    ��   : f00179208
    �޸�����   : DTS2015052504823�����Ӵ�IMSЭ��ջ�Ĳ�������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaImsStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֪ͨIMSA����IMSЭ��ջ */
    NAS_MSCC_SndImsaStartReq(MSCC_IMSA_START_TYPE_IMS_SWITCH_ON);

    /* Start timer TI_NAS_MSCC_WAIT_IMSA_START_CNF */
    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_START_CNF, TI_NAS_MSCC_WAIT_IMSA_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaImsStopReq_PreProc
 ��������  : �յ�ID_MMA_MSCC_IMS_STOP_REQ��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
  1.��    ��   : 2015��4��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��26��
    ��    ��   : f00179208
    �޸�����   : DTS2015052504823�����Ӵ�IMSЭ��ջ�Ĳ�������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaImsStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֪ͨIMSA�ر�IMSЭ��ջ */
    NAS_MSCC_SndImsaStopReq(MSCC_IMSA_STOP_TYPE_IMS_SWITCH_OFF);

    /* Start timer TI_NAS_IMSA_WAIT_IMSA_POWER_OFF_CNF */
    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF, TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaVoiceDomainChangeInd_PreProc
 ��������  : �յ�ID_MMA_MSCC_VOICE_DOMAIN_CHANGE_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��4��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaVoiceDomainChangeInd_PreProc(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU                  *pstVoiceDomainInd = VOS_NULL_PTR;
    NAS_MSCC_IMS_CONFIG_PARA_STRU                          *pstImsCfgInfo = VOS_NULL_PTR;

    pstImsCfgInfo     = NAS_MSCC_GetImsCfgInfo();
    pstVoiceDomainInd = (MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU *)pstMsg;

    /* ����VOICE DOMAIN��ֵ */
    pstImsCfgInfo->enVoiceDomain = pstVoiceDomainInd->enVoiceDomain;

    /* ֪ͨIMSA�仯���VOICE DOMAINֵ */
    NAS_MSCC_SndImsaVoiceDomainChangeInd(pstVoiceDomainInd->enVoiceDomain);

    /* ֪ͨMMC�仯���VOICE DOMAINֵ */
    NAS_MSCC_SndMmcVoiceDomainChangeInd(pstVoiceDomainInd->enVoiceDomain);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvImsaStartCnf_PreProc
 ��������  : �յ�ID_IMSA_MSCC_START_CNF��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ     :
 1.��    ��   : 2015��4��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
  3.��    ��   : 2015��12��18��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: L��ע��ɹ���̬��IMS�����α�ǲ���ȷ
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvImsaStartCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enPsSrvStatus;
    VOS_UINT8                           ucRoamingValid;
    VOS_UINT8                           ucCurr3gppRoamingFlg;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    enPsSrvStatus                       = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
    ucRoamingValid                      = VOS_FALSE;
    ucCurr3gppRoamingFlg                = VOS_FALSE;

    /* �жϵ�ǰ״̬����״̬��������ڿ�����״̬���棬����Ϊ��IMS SWITCH�����Ŀ������� */
    if (NAS_MSCC_FSM_SWITCH_ON != enFsmId)
    {
        /* ����IMSҵ������ */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_TRUE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_TRUE;

        /* Stop the timer */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_START_CNF);

        /* ֪ͨMMC��ǰIMS�Ŀ���״̬ */
        NAS_MSCC_SndMmcImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_ON);

        /* ֪ͨIMSA פ����Ϣ */
        NAS_MSCC_SndImsaCampInfoChangeInd();

        enPsSrvStatus  = NAS_MSCC_GetCurr3gppPsServiceStatus();

        if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == enPsSrvStatus)
        {
            ucRoamingValid              = VOS_TRUE;
            ucCurr3gppRoamingFlg        = NAS_MSCC_GetCurr3gppRoamingFlg();
        }

        /* ֪ͨIMSA Service Change Ind, ����IMSA���ۣ��˴���ҪЯ��������ָʾ���Ա�IMSA��NORMAL SERVICE
           �������ܹ�����ע������ */
        NAS_MSCC_SetPsRegSuccProcType(NAS_MSCC_PIF_L_TAU_REAL_PROC);
        NAS_MSCC_SndImsaSrvInfoNotify(enPsSrvStatus, ucRoamingValid, ucCurr3gppRoamingFlg);


        /* ��IMSA�ظ�START CNF��Ϣ */
        NAS_MSCC_SndMmaImsStartCnf(NAS_MSCC_PIF_IMS_START_RESULT_SUCC);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvImsaStopCnf_PreProc
 ��������  : �յ�ID_IMSA_MSCC_STOP_CNF��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ     :
 1.��    ��   : 2015��4��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��12��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvImsaStopCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* �жϵ�ǰ״̬����״̬��������ڹػ���״̬���棬����Ϊ��IMS SWITCH�����Ĺػ����� */
    if (NAS_MSCC_FSM_POWER_OFF != enFsmId)
    {
        /* ����IMSҵ������ */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_FALSE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_FALSE;

        /* Stop the timer */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF);

        /* ֪ͨMMC��ǰIMS�Ŀ���״̬ */
        NAS_MSCC_SndMmcImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

        /* ֪ͨMMC��ǰIMS voice������ */
        NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

        /* ֪ͨMMA��ǰIMS VOICE������ */
        NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

        /* ��IMSA�ظ�STOP CNF��Ϣ */
        NAS_MSCC_SndMmaImsStopCnf(NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvTiWaitImsaStartCnfExpired_PreProc
 ��������  : �յ���ʱ��TI_NAS_MSCC_WAIT_IMSA_START_CNF��ʱ��Ϣ��Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaStartCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* �жϵ�ǰ״̬����״̬��������ڿ�����״̬���棬����Ϊ��IMS SWITCH�����Ŀ������� */
    if (NAS_MSCC_FSM_SWITCH_ON != enFsmId)
    {
        /* ����IMSҵ������ */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_FALSE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_FALSE;

        /* ��MMA�ظ�START CNF��Ϣ */
        NAS_MSCC_SndMmaImsStartCnf(NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PreProc
 ��������  : �յ���ʱ��TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF��ʱ��Ϣ��Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��4��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* �жϵ�ǰ״̬����״̬��������ڹػ���״̬���棬����Ϊ��IMS SWITCH�����Ĺػ����� */
    if (NAS_MSCC_FSM_POWER_OFF != enFsmId)
    {
        /* ����IMSҵ������ */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_FALSE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_FALSE;

        /* ֪ͨMMC��ǰIMS�Ŀ���״̬ */
        NAS_MSCC_SndMmcImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

        /* ֪ͨMMC��ǰIMS voice������ */
        NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);


        /* ֪ͨMMA��ǰIMS VOICE������ */
        NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

        /* ��IMSA�ظ�STOP CNF��Ϣ */
        NAS_MSCC_SndMmaImsStopCnf(NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcPsRegCnRsltInd_PreProc
 ��������  : �յ�MMC��ID_MMC_MSCC_PS_REG_CN_RSLT_IND��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��4��5��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPsRegCnRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PS_REG_CN_RSLT_IND_STRU   *pstPsRegCnRsltInd = VOS_NULL_PTR;

    pstPsRegCnRsltInd = (MMC_MSCC_PS_REG_CN_RSLT_IND_STRU *)pstMsg;

    NAS_MSCC_SetPsRegSuccProcType(pstPsRegCnRsltInd->enPsRegCnRslt);

    return VOS_TRUE;
}
/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdPowerSaveCnf_PreProc
 ��������  : �յ�XSDģ���power save cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��5��12��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
 3.��    ��   : 2015��12��10��
   ��    ��   : j00354216
   �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                st1xSysSrvInfoInd;
    XSD_MSCC_POWER_SAVE_CNF_STRU                           *pstPowerSaveCnf;
    MSCC_HSD_1X_SYS_INFO_STRU                               st1xSysInfo;

    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType;

    pstPowerSaveCnf = (XSD_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

    enNoCardInitSearchWaitType = NAS_MSCC_GetNoCardInitSearchWaitType();

    if ((NAS_MSCC_FSM_L1_MAIN == NAS_MSCC_GetCurrFsmId())
     && (NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_1X == enNoCardInitSearchWaitType))
    {
        /* �޿������յ�ID_XSD_MSCC_POWER_SAVE_CNF,˵��GU������ɣ�1x���ѱ���ϣ��ظ�MMA_GET_GEO_CNF��MMA_STOP_GET_GEO_CNF */
        NAS_MSCC_ProcNoCardInitSearchWhenRcvXsdPowerSaveCnf_PreProc();

        return VOS_TRUE;
    }

    if (NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult)
    {
        NAS_MSCC_Set1xActiveFlg(VOS_FALSE);
        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        /* notify mma no service */
        NAS_MSCC_SetCurr1xServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        PS_MEM_SET(&st1xSysSrvInfoInd, 0x0, sizeof(XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU));
        st1xSysSrvInfoInd.stSysSrvInfo.enServiceStatus       = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
        st1xSysSrvInfoInd.stSysSrvInfo.enBaseStationInfoIncl = PS_TRUE;

        NAS_MSCC_SndMma1xSystemServiceInfoInd(&st1xSysSrvInfoInd);

        /* power save 1Xϵͳ�����HRPDϵͳ֧�֣�֪ͨһ��HSD */
        if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
        {
            PS_MEM_SET(&st1xSysInfo, 0, sizeof(MSCC_HSD_1X_SYS_INFO_STRU));

            NAS_MSCC_SndHsd1xSysChgInd(VOS_FALSE, &st1xSysInfo);
        }
        /* 1X�ر�ʱ���LTE��������, ��ʱ��Ҫ����LTE������any����,
           ���LTE֮ǰ���ڲ������ѱ�power save��, �ر�1X��SYSCFG
           ���̻����´�����һ��LTE */
        if (VOS_FALSE == NAS_MSCC_GetAllowSrchLteFlg())
        {
            NAS_MSCC_SetAllowSrchLteFlg(VOS_TRUE);

            NAS_MSCC_SndMmcCLAssociatedInfoNtf(NAS_MSCC_PIF_PLMN_PRIORITY_ANY, VOS_TRUE);
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdPowerSaveCnf_PreProc
 ��������  : �յ�HSDģ���power save cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��05��30��
   ��    ��   : l00324781
   �޸�����   : Iteration 12 �޸ģ�NAS_MSCC_SndMmaHrpdServiceStatusInd ����һ������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf;

    pstPowerSaveCnf = (HSD_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

    if (NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult)
    {
        NAS_MSCC_SetHrpdActiveFlg(VOS_FALSE);
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        /* notify mma no service */
        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            VOS_FALSE,
                                            VOS_FALSE,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsNeedDiscardMmcServiceStatusInd_PreProc
 ��������  : �ж��Ƿ���Ҫ����MMC�ķ���״ָ̬ʾ
 �������  : enServiceStatus---MMC service status
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNeedDiscardMmcServiceStatusInd_PreProc(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32      enServiceStatus
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    pstCurFsm = NAS_MSCC_GetCurFsmAddr();

    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == pstCurFsm->enFsmId)
    {
        if ((NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF                == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD     == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF_REACQ_HRPD == pstCurFsm->ulState))
        {
            return VOS_TRUE;
        }

        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE != enServiceStatus)
        {
            if (NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF == pstCurFsm->ulState)
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcPsServiceStatusIndInCLMode_PreProc
 ��������  : CLģʽ�´���PS��ķ���״ָ̬ʾ
 �������  : pstSrvStatusInd---mmc service status ind
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_ProcPsServiceStatusIndInCLMode_PreProc(
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstSrvStatusInd
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimCardStatus;

    /* �����Ƿ�CLģʽ,ͳһ����NV */
    if ((VOS_TRUE                                   == NAS_MSCC_IsLtePlmnIdChanged())
     && (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstSrvStatusInd->enServiceStatus))
    {
        /* Update the location info to NVIM if the service status is normal service and the location info is changed */
        NAS_MSCC_UpdateLocationInfoToNvim();
    }

    /* SYSCFGEX��ͬʱ֧��HRPD+LTE�򲻴������Ϣ */
    if (VOS_FALSE == NAS_MSCC_IsHrpdAndLteBothSupported())
    {
        return VOS_TRUE;
    }

    /* MLPL��MSPL��Ч�򲻴������Ϣ */
    if (VOS_FALSE== NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_TRUE;
    }

    enUsimCardStatus   = NAS_MSCC_GetUsimCardStatus();
    enCsimCardStatus   = NAS_MSCC_GetCsimCardStatus();

    /* ��CSIM+USIMӦ���򲻴������Ϣ */
    if ((NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT != enUsimCardStatus)
     || (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT != enCsimCardStatus))
    {
        return VOS_TRUE;
    }

    /* BG�����������ж��Ƿ���Ҫ�����÷���״ָ̬ʾ��Ϣ */
    if (VOS_TRUE == NAS_MSCC_IsNeedDiscardMmcServiceStatusInd_PreProc(pstSrvStatusInd->enServiceStatus))
    {
        NAS_MSCC_MNTN_LogDiscardServStaInfo(NAS_MSCC_DISCARD_MMC_SERVICE_STATUS_IND);

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_StartBsrTimer();
        }
        else
        {
            if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdRfAvailableInd_PreProc
 ��������  : MSCC�յ�HSD RF��Դ�Ƿ������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��20��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2016��1��6��
   ��    ��   : w00242748
   �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
 3.��    ��   : 2016��1��4��
   ��    ��   : w00176964
   �޸�����   : CL_MUTIMODE_OPTIMIZE
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaRfAvailInd(pstRfAvail);

    /* �������غ�ģʽ�£�ֻ͸������Ϣ������������ */
    if (NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE == NAS_MSCC_GetEmcCallExistFlag())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_Is3gppNormalService())
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvHsdRfAvailableInd_PreProc discard due to lte normal service");
        return VOS_TRUE;
    }

    /* if HRPD is deactive, mscc should enter active state to do */
    if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdRfAvailableInd_PreProc
 ��������  : MSCC�յ�XSD RF��Դ�Ƿ������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��20��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaRfAvailInd(pstRfAvail);

    if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


#endif


#ifdef DMT
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMsccMofiyMlplRecordReq_PreProc
 ��������  : �յ��޸�MLPL��¼������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccMofiyMlplRecordReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlplInfo;
    NAS_MSCC_MSCC_MODIFY_MLPL_RECORD_REQ_STRU              *pstMdyMlplRecReq;
    VOS_UINT8                                               ucMlplRecIndex;
    VOS_UINT8                                               ucMlplRecTagIndex;
    VOS_UINT8                                               i;

    pstMdyMlplRecReq = (NAS_MSCC_MSCC_MODIFY_MLPL_RECORD_REQ_STRU *)pstMsg;
    pstMlplInfo      = NAS_MSCC_GetMlplInfoAddr();

    pstMlplInfo->ucIsContainDefRec = pstMdyMlplRecReq->ucIsContainDefRec;

    for ( i = 0; i < pstMdyMlplRecReq->ucRecNum; i++)
    {
        ucMlplRecIndex = pstMdyMlplRecReq->astMlplRecord[i].ucMlplRecIndex;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->ucIsRecValid   = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucIsRecValid;
        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->ucLocParamType = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucLocParamType;
        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->ucMsplIndex = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucMsplIndex;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->stLocParamVal.usMcc
                        = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.usMcc;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->stLocParamVal.usMnc
                        = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.usMnc;

        ucMlplRecTagIndex = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucSysLocTagIndex;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->stLocParamVal.astSysLocTag[ucMlplRecTagIndex]
                    = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.stSysLocTag;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMsccMofiyMsplIdReq_PreProc
 ��������  : �յ��޸�MSPL��¼������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccMofiyMsplIdReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSPL_STRU                                     *pstMsplInfo;
    NAS_MSCC_MSCC_MODIFY_MSPL_ID_REQ_STRU                  *pstMdyMsplIdReq;
    VOS_UINT8                                               ucMsplIdIndex;
    VOS_UINT8                                               ucMsplRecIndex;
    VOS_UINT8                                               i;

    pstMdyMsplIdReq = (NAS_MSCC_MSCC_MODIFY_MSPL_ID_REQ_STRU *)pstMsg;
    pstMsplInfo     = NAS_MSCC_GetMsplInfoAddr();

    for ( i = 0; i < pstMdyMsplIdReq->ucRecNum; i++)
    {
        ucMsplIdIndex = pstMdyMsplIdReq->astMsplId[i].ucMlplIdIndex;

        pstMsplInfo->apstMsplId[ucMsplIdIndex]->ucIsMsplIdValid = pstMdyMsplIdReq->astMsplId[i].stMsplId.ucIsMsplIdValid;
        pstMsplInfo->apstMsplId[ucMsplIdIndex]->ucMsplId        = pstMdyMsplIdReq->astMsplId[i].stMsplId.ucMsplId;

        ucMsplRecIndex = pstMdyMsplIdReq->astMsplId[i].stMsplId.ucMsplRecIndex;

        pstMsplInfo->apstMsplId[ucMsplIdIndex]->astMsplRec[ucMsplRecIndex]  = pstMdyMsplIdReq->astMsplId[i].stMsplId.stMsplRec;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMsccSetSendCardReadReqFlag_PreProc
 ��������  : �յ����÷��Ͷ��������־��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��25��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvSetCardReadStubTypeReq_PreProc(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ_STRU              *pstStubReqMsg;

    pstStubReqMsg = (NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ_STRU *)pstMsg;

    genCardReadStubTypeForDmt = pstStubReqMsg->enStubType;

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaAutoReselSetReq_PreProc
 ��������  : �յ�mma auto resel set�Ĵ���
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��3��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaAutoReselSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_AUTO_RESEL_SET_STRU       *pstAutoReselSetReq;

    pstAutoReselSetReq = (MMA_MSCC_AUTO_RESEL_SET_STRU *)pstMsg;

    NAS_MSCC_SndMmcAutoReselSetReq(pstAutoReselSetReq->ucActiveFlg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcSrchedPlmnInfo_PreProc
 ��������  : ����MMC srched plmn info

 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��18��
   ��    ��   : h00285180
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcSrchedPlmnInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* ת����Ϣ��MMA */
    NAS_MSCC_SndMmaSrchedPlmnInfo((MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdInterSysEndInd_PreProc
 ��������  : mscc�յ���ϢHSD_MSCC_INTERSYS_END_IND_STRU������Я���Ĳ���ѡ��ͬ��������
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��5��30��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2015070910837:����CL��ϵͳ״̬��
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysEndInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_INTERSYS_END_IND_STRU     *pstInterSysEndInd       = VOS_NULL_PTR;

    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurFsmId;

    pstInterSysEndInd = (HSD_MSCC_INTERSYS_END_IND_STRU*)pstMsg;
    enCurFsmId        = NAS_MSCC_GetCurrFsmId();

    /* CLģʽ�£�LTE2HRPD��hsd�յ�CAS_CNAS_HRPD_IRAT_FROM_LTE��Ϣ����mscc���͸���Ϣ
        ��ʱ����Ϣ������дVOS_RATMODE_BUTT
    */
    if (VOS_RATMODE_BUTT == pstInterSysEndInd->enCurrRatMode)
    {
        NAS_MSCC_Set3gppActiveFlg(VOS_FALSE);
        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

        NAS_MSCC_SndMmcInterSysHrpdInd();
    }
    /* CLģʽ�£�HRPD2LTE, ʧ�ܻ��˵�HRPD���յ�CAS_CNAS_RESUME_ID��Ϣ����mscc����END_IND��������дVOS_RATMODE_HRPD.
    */
    else if (VOS_RATMODE_HRPD == pstInterSysEndInd->enCurrRatMode)
    {

    }
    /* CLģʽ�£�HRPD2LTE, �ɹ���hsd�յ�CAS_CNAS_HRPD_IRAT_TO_LTE��Ϣ����mscc����END_IND��������дVOS_RATMODE_LTE */
    else if (VOS_RATMODE_LTE == pstInterSysEndInd->enCurrRatMode)
    {
        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);
        NAS_MSCC_SetHrpdActiveFlg(VOS_FALSE);
    }
    else  /* ����ֵ���쳣����ӡ��¼ */
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvHsdInterSysEndInd_PreProc:The IE enCurrRatMode value is error!");
    }

    /* ֻ����ϵͳ�����ﴦ����ϵͳ����ָʾ */
    if (NAS_MSCC_FSM_CL_INTERSYS == enCurFsmId)
    {
        return VOS_FALSE;
    }

    NAS_WARNING_LOG(UEPS_PID_MSCC,
            "NAS_MSCC_RcvHsdInterSysStartInd_PreProc(): receive intersyss end ind while not in intersys fsm");

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdInterSysStartInd_PreProc
 ��������  : mscc�յ���ϢHSD_MSCC_INTERSYS_START_IND_STRU,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��5��30��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2015070910837:����CL��ϵͳ״̬��
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_INTERSYS_START_IND_STRU                       *pstInterSysStartInd;
    NAS_MSCC_FSM_ID_ENUM_UINT32                             enCurFsmId;

    pstInterSysStartInd = (HSD_MSCC_INTERSYS_START_IND_STRU *)pstMsg;
    enCurFsmId          = NAS_MSCC_GetCurrFsmId();

    /* ͸����mmc C2L ��ϵͳ�л��Ŀ�ʼָʾ */
    NAS_MSCC_SncMmcCLInterSysStartNtf(pstInterSysStartInd->enInterSysCause);

    if ((NAS_MSCC_FSM_L1_MAIN                   == enCurFsmId)
     || (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == enCurFsmId))
    {
        return VOS_FALSE;
    }

    /* mscc�ڷ�main״̬���л���intersys cause��Ϊ ��ѡ���յ�hsd��ϵͳ��ʼָʾ��ֱ�Ӷ����������� */
    NAS_WARNING_LOG(UEPS_PID_MSCC,
        "NAS_MSCC_RcvHsdInterSysStartInd_PreProc(): when receive hsd intersyss start ind not in L1 main or bsr fsm, just discard it");

    return VOS_TRUE;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdHrpdNoSrv_PreProc
 ��������  : mscc�յ���ϢID_HSD_MSCC_REPORT_HRPD_NO_SERVICE_IND��������Ϣ
             ��mma�ϱ�MSCC_MMA_HRPD_SERVICE_STATUS_IND��Ϣ��Я���޷���
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��9��30��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdHrpdNoSrv_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                        VOS_FALSE,
                                        VOS_FALSE,
                                        MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);

    /* ��MMA�ϱ��޷��񣬺�MMA���ַ���״̬һ�£��˴�Ҳ�����޷��� */
    NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsd1xNoSrv_PreProc
 ��������  : mscc�յ���ϢID_XSD_MSCC_REPORT_1X_NO_SERVICE_IND��������Ϣ
             ��mma�ϱ�ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND��Ϣ��Я���޷���
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��10��08��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsd1xNoSrv_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                st1xSysSrvInfoInd;

    PS_MEM_SET(&st1xSysSrvInfoInd, 0x0, sizeof(XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU));
    st1xSysSrvInfoInd.stSysSrvInfo.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

    NAS_MSCC_SndMma1xSystemServiceInfoInd(&st1xSysSrvInfoInd);

    /* ��MMA�ϱ��޷��񣬺�MMA���ַ���״̬һ�£��˴�Ҳ�����޷��� */
    NAS_MSCC_SetCurr1xServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

    return VOS_TRUE;
}
#endif


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcInterSysStartInd_PreProc
 ��������  : mscc�յ���ϢID_MMC_MSCC_INTERSYS_START_IND,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��11��11��
   ��    ��   : y00346957
   �޸�����   : DTS2015070910837:����
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_FSM_ID_ENUM_UINT32                             enCurFsmId;
    MMC_MSCC_INTERSYS_START_IND_STRU                       *pstInterSysStartInd;

    enCurFsmId          = NAS_MSCC_GetCurrFsmId();
    pstInterSysStartInd = (MMC_MSCC_INTERSYS_START_IND_STRU *)pstMsg;

    /* ��ϵͳ�������̻�bsr��active��״̬��Ҫ����mmc��ϵͳ��ʼָʾ */
    if ((NAS_MSCC_FSM_L1_MAIN                   != enCurFsmId)
     && (NAS_MSCC_FSM_SYS_ACQ                   != enCurFsmId)
     && (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != enCurFsmId))
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC,
        "NAS_MSCC_RcvMmcInterSysStartInd_PreProc(): when receive intersys start ind not in syscfg or bsr or  L1 main fsm,just discard it");

        return VOS_TRUE;
    }

    /* ֻ��intersys casuse Ϊ��ѡ���ض������Ҫ����mmc��ϵͳ��ʼָʾ */
    if ((NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT != pstInterSysStartInd->enInterSysCause)
     && (NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR    != pstInterSysStartInd->enInterSysCause))
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC,
        "NAS_MSCC_RcvMmcInterSysStartInd_PreProc(): when receive intersys start ind with not reselect or redir,just discard it");

        return VOS_TRUE;
    }

    /* ֻ����ϵͳ����ΪL2C����Ҫ����mmc��ϵͳ��ʼָʾ */
    if ((VOS_RATMODE_LTE  != pstInterSysStartInd->enOrignRatMode)
     || (VOS_RATMODE_HRPD != pstInterSysStartInd->enDestRatMode))
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC,
        "NAS_MSCC_RcvMmcInterSysStartInd_PreProc(): when receive intersys start ind with not L2C,just discard it");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcInterSysEndInd_PreProc
 ��������  : mscc�յ���ϢHSD_MSCC_INTERSYS_END_IND_STRU������Я���Ĳ���ѡ��ͬ��������
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��11��11��
   ��    ��   : y00346957
   �޸�����   : DTS2015070910837:����
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysEndInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurFsmId;

    enCurFsmId = NAS_MSCC_GetCurrFsmId();

    /* ֻ����ϵͳ�����ﴦ����ϵͳ����ָʾ */
    if (NAS_MSCC_FSM_CL_INTERSYS == enCurFsmId)
    {
        return VOS_FALSE;
    }

    NAS_WARNING_LOG(UEPS_PID_MSCC,
            "NAS_MSCC_RcvMmcInterSysEndInd_PreProc(): receive intersyss end ind while not in intersys fsm");

    return VOS_TRUE;
}

#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



