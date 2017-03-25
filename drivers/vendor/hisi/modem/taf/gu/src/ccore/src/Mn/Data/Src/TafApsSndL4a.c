
/******************************************************************************

                   ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndL4a.c��
  �� �� ��   : ����
  ��    ��   : S62952
  ��������   : 2011��12��14��
  ����޸�   :
  ��������   : ��L4A����Ϣ���ͺ���
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��14��
    ��    ��   : S62952
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#include "TafLog.h"
#include "TafApsComFunc.h"
#include "TafSdcLib.h"
#endif


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDL4A_C

#if (FEATURE_ON == FEATURE_LTE)

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aGetLteCsReq
 ��������  : ����ID_APS_L4A_GET_LTE_CS_REQ��Ϣ,
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��23��
    ��    ��   : h00135900
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aGetLteCsReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_LTECS_REQ_STRU              *pstLteScReq;
    APS_L4A_GET_LTE_CS_REQ_STRU        *pstLteCsReq;

    /* ������ʼ�� */
    pstLteScReq       = (TAF_PS_LTECS_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstLteCsReq   = (APS_L4A_GET_LTE_CS_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_GET_LTE_CS_REQ_STRU));
    if (VOS_NULL_PTR == pstLteCsReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aGetLteCsReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstLteCsReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_GET_LTE_CS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstLteCsReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstLteCsReq->ulReceiverPid        = MSP_L4_L4A_PID;
    pstLteCsReq->enMsgId              = ID_APS_L4A_GET_LTE_CS_REQ;

    /* ��д��Ϣ���� */
    pstLteCsReq->stCtrl.ulPid         = pstLteScReq->stCtrl.ulModuleId;
    pstLteCsReq->stCtrl.ulClientId    = pstLteScReq->stCtrl.usClientId;
    pstLteCsReq->stCtrl.ulOpId        = pstLteScReq->stCtrl.ucOpId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstLteCsReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgdcontReq: Send message failed.");
        return;
    }
    return;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aGetCemodeReq
 ��������  : ����ID_APS_L4A_GET_CEMODE_REQ��Ϣ,
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : w00182550
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aGetCemodeReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_CEMODE_REQ_STRU                    *pstTafCemodeReq;
    APS_L4A_GET_CEMODE_REQ_STRU               *pstCemodeReq;

    /* ������ʼ�� */
    pstTafCemodeReq       = (TAF_PS_CEMODE_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCemodeReq   = (APS_L4A_GET_CEMODE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_GET_CEMODE_REQ_STRU));
    if (VOS_NULL_PTR == pstCemodeReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aGetCemodeReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCemodeReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_GET_CEMODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCemodeReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstCemodeReq->ulReceiverPid        = MSP_L4_L4A_PID;
    pstCemodeReq->enMsgId              = ID_APS_L4A_GET_CEMODE_REQ;

    /* ��д��Ϣ���� */
    pstCemodeReq->stCtrl.ulPid         = pstTafCemodeReq->stCtrl.ulModuleId;
    pstCemodeReq->stCtrl.ulClientId    = pstTafCemodeReq->stCtrl.usClientId;
    pstCemodeReq->stCtrl.ulOpId        = pstTafCemodeReq->stCtrl.ucOpId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCemodeReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aGetCemodeReq: Send message failed.");
        return;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetPdprofReq
 ��������  : ����APN �û����������Ȩ��Ϣ�����������Ϣ��L4A
             (ID_APS_L4A_SET_PDPROF_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��15��
    ��    ��   : x00126983
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetPdprofReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_PROFILE_INFO_REQ_STRU          *pstPdprofInfoReq;
    APS_L4A_SET_PDPROFMOD_REQ_STRU            *pstPdprofmodReq;

    /* ������ʼ�� */
    pstPdprofInfoReq  = (TAF_PS_SET_PROFILE_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstPdprofmodReq      = (APS_L4A_SET_PDPROFMOD_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_PDPROFMOD_REQ_STRU));
    if (VOS_NULL_PTR == pstPdprofmodReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetPdprofReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstPdprofmodReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_PDPROFMOD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstPdprofmodReq->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstPdprofmodReq->ulReceiverPid               = MSP_L4_L4A_PID;
    pstPdprofmodReq->enMsgId                     = ID_APS_L4A_SET_PDPROFMOD_REQ;

    /* ��д��Ϣ���� */
    pstPdprofmodReq->stCtrl.ulPid                = pstPdprofInfoReq->stCtrl.ulModuleId;
    pstPdprofmodReq->stCtrl.ulClientId           = pstPdprofInfoReq->stCtrl.usClientId;
    pstPdprofmodReq->stCtrl.ulOpId               = pstPdprofInfoReq->stCtrl.ucOpId;

    pstPdprofmodReq->stPdprofmod.bitOpPdpType     = pstPdprofInfoReq->stPdpProfInfo.bitOpPdpType;
    pstPdprofmodReq->stPdprofmod.bitOpApn         = pstPdprofInfoReq->stPdpProfInfo.bitOpApn;
    pstPdprofmodReq->stPdprofmod.bitOpPassword    = pstPdprofInfoReq->stPdpProfInfo.bitOpPassword;
    pstPdprofmodReq->stPdprofmod.bitOpUsername    = pstPdprofInfoReq->stPdpProfInfo.bitOpUsername;
    pstPdprofmodReq->stPdprofmod.bitOpAuthType    = pstPdprofInfoReq->stPdpProfInfo.bitOpAuthType;
    pstPdprofmodReq->stPdprofmod.bitOpSpare       = pstPdprofInfoReq->stPdpProfInfo.bitOpSpare;

    pstPdprofmodReq->stPdprofmod.ucCid            = pstPdprofInfoReq->stPdpProfInfo.ucCid;
    pstPdprofmodReq->stPdprofmod.ucDefined        = pstPdprofInfoReq->stPdpProfInfo.ucDefined;
    pstPdprofmodReq->stPdprofmod.enPdpType        = pstPdprofInfoReq->stPdpProfInfo.enPdpType;
    PS_MEM_CPY((VOS_UINT8*)(pstPdprofmodReq->stPdprofmod.aucApn),
               (VOS_UINT8*)(pstPdprofInfoReq->stPdpProfInfo.aucApn),
               (APS_L4A_MAX_APN_LEN + 1));
    pstPdprofmodReq->stPdprofmod.ucAuthType       = pstPdprofInfoReq->stPdpProfInfo.ucAuthType;
    pstPdprofmodReq->stPdprofmod.ucPwdLen         = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstPdprofInfoReq->stPdpProfInfo.aucPassWord);
    pstPdprofmodReq->stPdprofmod.ucUserNameLen    = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstPdprofInfoReq->stPdpProfInfo.aucUserName);


    PS_MEM_CPY(pstPdprofmodReq->stPdprofmod.aucPassWord,
               pstPdprofInfoReq->stPdpProfInfo.aucPassWord,
               pstPdprofmodReq->stPdprofmod.ucPwdLen);

    PS_MEM_CPY(pstPdprofmodReq->stPdprofmod.aucUserName,
               pstPdprofInfoReq->stPdpProfInfo.aucUserName,
               pstPdprofmodReq->stPdprofmod.ucUserNameLen);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdprofmodReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetPdprofReq: Send message failed.");
        return;
    }
    return;
}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aIpv6InfoNotifyInd
 ��������  : ����ID_APS_L4A_IPV6_INFO_NOTIFY_IND��Ϣ
 �������  : ucRabId                    - RAB ID
             pstIpv6RaInfo              - IPv6 RA����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ (���ϵͳ�����Ƿ�֧��LTE�ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_SndL4aIpv6InfoNotifyInd(
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU          *pstIpv6RaInfo
)
{
    VOS_UINT32                          i;
    APS_L4A_IPV6_INFO_NOTIFY_IND_STRU  *pstL4aIpv6InfoNotifyInd;

    if (VOS_FALSE == TAF_SDC_IsPlatformSupportLte())
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndL4aIpv6InfoNotifyInd: Platform don't support LTE.");
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstL4aIpv6InfoNotifyInd = (APS_L4A_IPV6_INFO_NOTIFY_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                    WUEPS_PID_TAF,
                                    sizeof(APS_L4A_IPV6_INFO_NOTIFY_IND_STRU));
    if (VOS_NULL_PTR == pstL4aIpv6InfoNotifyInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndL4aIpv6InfoNotifyInd: Memory alloc failed.");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstL4aIpv6InfoNotifyInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_L4A_IPV6_INFO_NOTIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstL4aIpv6InfoNotifyInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstL4aIpv6InfoNotifyInd->ulReceiverPid   = MSP_L4_L4A_PID;
    pstL4aIpv6InfoNotifyInd->enMsgId         = ID_APS_L4A_IPV6_INFO_NOTIFY_IND;

    /* ��д��Ϣ���� */
    pstL4aIpv6InfoNotifyInd->ucRabId         = ucRabId;
    pstL4aIpv6InfoNotifyInd->ucIpv6PrefixNum = (VOS_UINT8)pstIpv6RaInfo->ulPrefixNum;
    for (i = 0; i < pstIpv6RaInfo->ulPrefixNum; i++)
    {
        pstL4aIpv6InfoNotifyInd->astIpv6PrefixArray[i].ucPrefixLen
                                             = pstIpv6RaInfo->astPrefixList[i].ulBitPrefixLen/8;

        PS_MEM_CPY(pstL4aIpv6InfoNotifyInd->astIpv6PrefixArray[i].aucPrefix,
                   pstIpv6RaInfo->astPrefixList[i].aucPrefix,
                   APS_L4A_MAX_IPV6_ADDR_LEN);
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstL4aIpv6InfoNotifyInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aIpv6InfoNotifyInd: Send message failed.");
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgdcontReq
 ��������  : ������PDP�����������������Ϣ��L4A
             (ID_APS_L4A_SET_CGDCONT_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ṹ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgdcontReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstPdpReq;
    APS_L4A_SET_CGDCONT_REQ_STRU               *pstCgdcontReq;

    /* ������ʼ�� */
    pstPdpReq       = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgdcontReq   = (APS_L4A_SET_CGDCONT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGDCONT_REQ_STRU));
    if (VOS_NULL_PTR == pstCgdcontReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgdcontReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgdcontReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGDCONT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgdcontReq->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstCgdcontReq->ulReceiverPid        = MSP_L4_L4A_PID;
    pstCgdcontReq->enMsgId              = ID_APS_L4A_SET_CGDCONT_REQ;

    /* ��д��Ϣ���� */
    pstCgdcontReq->stCtrl.ulPid         = pstPdpReq->stCtrl.ulModuleId;
    pstCgdcontReq->stCtrl.ulClientId    = pstPdpReq->stCtrl.usClientId;
    pstCgdcontReq->stCtrl.ulOpId        = pstPdpReq->stCtrl.ucOpId;

    pstCgdcontReq->stCgdcontInfo.bitOpPdpType       = pstPdpReq->stPdpContextInfo.bitOpPdpType;
    pstCgdcontReq->stCgdcontInfo.bitOpApn           = pstPdpReq->stPdpContextInfo.bitOpApn;
    pstCgdcontReq->stCgdcontInfo.bitOpPdpAddr       = pstPdpReq->stPdpContextInfo.bitOpPdpAddr;
    pstCgdcontReq->stCgdcontInfo.bitOpPdpDcomp      = pstPdpReq->stPdpContextInfo.bitOpPdpDcomp;
    pstCgdcontReq->stCgdcontInfo.bitOpPdpHcomp      = pstPdpReq->stPdpContextInfo.bitOpPdpHcomp;
    pstCgdcontReq->stCgdcontInfo.bitOpIPV4ADDRALLOC = pstPdpReq->stPdpContextInfo.bitOpIpv4AddrAlloc;
    pstCgdcontReq->stCgdcontInfo.bitOpEmergency     = pstPdpReq->stPdpContextInfo.bitOpEmergencyInd;
    pstCgdcontReq->stCgdcontInfo.bitOpImCnSignalFlg = pstPdpReq->stPdpContextInfo.bitOpImCnSignalFlg;
    pstCgdcontReq->stCgdcontInfo.bitOpPcscfDiscovery= pstPdpReq->stPdpContextInfo.bitOpPcscfDiscovery;
    pstCgdcontReq->stCgdcontInfo.bitOpPadding       = pstPdpReq->stPdpContextInfo.bitOpSpare;

    pstCgdcontReq->stCgdcontInfo.ucCid              = pstPdpReq->stPdpContextInfo.ucCid;
    pstCgdcontReq->stCgdcontInfo.enPdpType          = pstPdpReq->stPdpContextInfo.enPdpType;
    PS_MEM_CPY((VOS_UINT8*)(pstCgdcontReq->stCgdcontInfo.aucApn),
               (VOS_UINT8*)(pstPdpReq->stPdpContextInfo.aucApn),
               (APS_L4A_MAX_APN_LEN + 1));
    PS_MEM_CPY((VOS_UINT8*)(&(pstCgdcontReq->stCgdcontInfo.stPdpAddr)),
               (VOS_UINT8*)(&(pstPdpReq->stPdpContextInfo.stPdpAddr)),
               sizeof(APS_L4A_PDP_ADDR_STRU));
    pstCgdcontReq->stCgdcontInfo.enPdpDataComp      = pstPdpReq->stPdpContextInfo.enPdpDcomp;
    pstCgdcontReq->stCgdcontInfo.enPdpHeadComp      = pstPdpReq->stPdpContextInfo.enPdpHcomp;
    pstCgdcontReq->stCgdcontInfo.ucIPV4ADDRALLOC    = pstPdpReq->stPdpContextInfo.enIpv4AddrAlloc;
    pstCgdcontReq->stCgdcontInfo.enEmergency        = pstPdpReq->stPdpContextInfo.enEmergencyFlg;
    pstCgdcontReq->stCgdcontInfo.enImCnSignalFlg    = pstPdpReq->stPdpContextInfo.enImCnSignalFlg;
    pstCgdcontReq->stCgdcontInfo.enPcscfDiscovery   = pstPdpReq->stPdpContextInfo.enPcscfDiscovery;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgdcontReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgdcontReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgdscontReq
 ��������  : ���ʹ�PDP�����ĵ������������Ϣ��L4A
             (ID_L4A_APS_SET_CGDSCONT_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgdscontReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstPdpReq;
    APS_L4A_SET_CGDSCONT_REQ_STRU              *pstCgdscontReq;

    /* ������ʼ�� */
    pstPdpReq       = (TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgdscontReq  = (APS_L4A_SET_CGDSCONT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGDSCONT_REQ_STRU));
    if (VOS_NULL_PTR == pstCgdscontReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgdscontReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgdscontReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGDSCONT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgdscontReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCgdscontReq->ulReceiverPid       = MSP_L4_L4A_PID;
    pstCgdscontReq->enMsgId             = ID_APS_L4A_SET_CGDSCONT_REQ;

    /* ��д��Ϣ���� */
    pstCgdscontReq->stCtrl.ulPid        = pstPdpReq->stCtrl.ulModuleId;
    pstCgdscontReq->stCtrl.ulClientId   = pstPdpReq->stCtrl.usClientId;
    pstCgdscontReq->stCtrl.ulOpId       = pstPdpReq->stCtrl.ucOpId;

    pstCgdscontReq->stCgdscontInfo.bitOpPrimaryCid = pstPdpReq->stPdpContextInfo.bitOpLinkdCid;
    pstCgdscontReq->stCgdscontInfo.bitOpPdpDcomp   = pstPdpReq->stPdpContextInfo.bitOpPdpDcomp;
    pstCgdscontReq->stCgdscontInfo.bitOpPdpHcomp   = pstPdpReq->stPdpContextInfo.bitOpPdpHcomp;
    pstCgdscontReq->stCgdscontInfo.bitOpPadding    = pstPdpReq->stPdpContextInfo.bitOpSpare;

    pstCgdscontReq->stCgdscontInfo.ucSecondaryCid  = pstPdpReq->stPdpContextInfo.ucCid;
    pstCgdscontReq->stCgdscontInfo.ucPrimaryCid    = pstPdpReq->stPdpContextInfo.ucLinkdCid;
    pstCgdscontReq->stCgdscontInfo.enPdpDataComp   = pstPdpReq->stPdpContextInfo.enPdpDcomp;
    pstCgdscontReq->stCgdscontInfo.enPdpHeadComp   = pstPdpReq->stPdpContextInfo.enPdpHcomp;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgdscontReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgdscontReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgtftReq
 ��������  : ����TFT�����������������Ϣ��L4A
             (ID_APS_L4A_SET_CGTFT_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��28��
    ��    ��   : W00316404
    �޸�����   : R11 TFT Э������

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgtftReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_TFT_INFO_REQ_STRU       *pstTftReq;
    APS_L4A_SET_CGTFT_REQ_STRU         *pstCgtftReq;

    /* ������ʼ�� */
    pstTftReq   = (TAF_PS_SET_TFT_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgtftReq  = (APS_L4A_SET_CGTFT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGTFT_REQ_STRU));
    if (VOS_NULL_PTR == pstCgtftReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgtftReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgtftReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGTFT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgtftReq->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstCgtftReq->ulReceiverPid          = MSP_L4_L4A_PID;
    pstCgtftReq->enMsgId                = ID_APS_L4A_SET_CGTFT_REQ;

    /* ��д��Ϣ���� */
    pstCgtftReq->stCtrl.ulPid           = pstTftReq->stCtrl.ulModuleId;
    pstCgtftReq->stCtrl.ulClientId      = pstTftReq->stCtrl.usClientId;
    pstCgtftReq->stCtrl.ulOpId          = pstTftReq->stCtrl.ucOpId;

    pstCgtftReq->stTftInfo.bitOpPktFilterId     = pstTftReq->stTftInfo.bitOpPktFilterId;
    pstCgtftReq->stTftInfo.bitOpPrecedence      = pstTftReq->stTftInfo.bitOpPrecedence;
    pstCgtftReq->stTftInfo.bitOpSrcIp           = pstTftReq->stTftInfo.bitOpSrcIp;
    pstCgtftReq->stTftInfo.bitOpProtocolId      = pstTftReq->stTftInfo.bitOpProtocolId;
    pstCgtftReq->stTftInfo.bitOpDestPortRange   = pstTftReq->stTftInfo.bitOpDestPortRange;
    pstCgtftReq->stTftInfo.bitOpSrcPortRange    = pstTftReq->stTftInfo.bitOpSrcPortRange;
    pstCgtftReq->stTftInfo.bitOpSpi             = pstTftReq->stTftInfo.bitOpSpi;
    pstCgtftReq->stTftInfo.bitOpTosMask         = pstTftReq->stTftInfo.bitOpTosMask;
    pstCgtftReq->stTftInfo.bitOpFlowLable       = pstTftReq->stTftInfo.bitOpFlowLable;
    pstCgtftReq->stTftInfo.bitOpDirection       = pstTftReq->stTftInfo.bitOpDirection;
    pstCgtftReq->stTftInfo.bitOpNwPktFilterId   = pstTftReq->stTftInfo.bitOpNwPktFilterId;
    pstCgtftReq->stTftInfo.bitOpLocalIpv4AddrAndMask = pstTftReq->stTftInfo.bitOpLocalIpv4AddrAndMask;
    pstCgtftReq->stTftInfo.bitOpLocalIpv6AddrAndMask = pstTftReq->stTftInfo.bitOpLocalIpv6AddrAndMask;
    pstCgtftReq->stTftInfo.bitOpSpare           = pstTftReq->stTftInfo.bitOpSpare;

    pstCgtftReq->ulCid                          = pstTftReq->stTftInfo.ucCid;

    pstCgtftReq->stTftInfo.ucPacketFilterId     = pstTftReq->stTftInfo.ucPacketFilterId;
    pstCgtftReq->stTftInfo.ucPrecedence         = pstTftReq->stTftInfo.ucPrecedence;
    pstCgtftReq->stTftInfo.ucProtocolId         = pstTftReq->stTftInfo.ucProtocolId;

    PS_MEM_CPY(&(pstCgtftReq->stTftInfo.stSourceIpaddr),
               &(pstTftReq->stTftInfo.stSourceIpaddr),
               sizeof(TAF_PDP_ADDR_STRU));
    PS_MEM_CPY(&(pstCgtftReq->stTftInfo.stSourceIpMask),
               &(pstTftReq->stTftInfo.stSourceIpMask),
               sizeof(TAF_PDP_ADDR_STRU));

    PS_MEM_CPY(pstCgtftReq->stTftInfo.aucLocalIpv4Addr,
               pstTftReq->stTftInfo.aucLocalIpv4Addr,
               APS_L4A_MAX_IPV4_ADDR_LEN);
    PS_MEM_CPY(pstCgtftReq->stTftInfo.aucLocalIpv4Mask,
               pstTftReq->stTftInfo.aucLocalIpv4Mask,
               APS_L4A_MAX_IPV4_ADDR_LEN);
    PS_MEM_CPY(pstCgtftReq->stTftInfo.aucLocalIpv6Addr,
               pstTftReq->stTftInfo.aucLocalIpv6Addr,
               APS_L4A_MAX_IPV6_ADDR_LEN);
    pstCgtftReq->stTftInfo.ucLocalIpv6Prefix    = pstTftReq->stTftInfo.ucLocalIpv6Prefix;

    pstCgtftReq->stTftInfo.usLowDestPort        = pstTftReq->stTftInfo.usLowDestPort;
    pstCgtftReq->stTftInfo.usHighDestPort       = pstTftReq->stTftInfo.usHighDestPort;
    pstCgtftReq->stTftInfo.usLowSourcePort      = pstTftReq->stTftInfo.usLowSourcePort;
    pstCgtftReq->stTftInfo.usHighSourcePort     = pstTftReq->stTftInfo.usHighSourcePort;
    pstCgtftReq->stTftInfo.ulSecuParaIndex      = pstTftReq->stTftInfo.ulSecuParaIndex;
    pstCgtftReq->stTftInfo.ulFlowLable          = pstTftReq->stTftInfo.ulFlowLable;
    pstCgtftReq->stTftInfo.ucTypeOfService      = pstTftReq->stTftInfo.ucTypeOfService;
    pstCgtftReq->stTftInfo.ucTypeOfServiceMask  = pstTftReq->stTftInfo.ucTypeOfServiceMask;
    pstCgtftReq->stTftInfo.enTftFilterDirection = pstTftReq->stTftInfo.ucDirection;
    pstCgtftReq->stTftInfo.ucNwPktFilterId      = pstTftReq->stTftInfo.ucNwPktFilterId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgtftReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgtftReq: Send message failed.");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgautoReq
 ��������  : ����PS���Զ�Ӧ��״̬�����������Ϣ��L4A
             (ID_L4A_APS_SET_CGAUTO_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgautoReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU       *pstAnsModeReq;
    APS_L4A_SET_CGAUTO_REQ_STRU                *pstCgautoReq;

    /* ������ʼ�� */
    pstAnsModeReq   = (TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgautoReq    = (APS_L4A_SET_CGAUTO_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGAUTO_REQ_STRU));
    if (VOS_NULL_PTR == pstCgautoReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgautoReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgautoReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGAUTO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgautoReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstCgautoReq->ulReceiverPid         = MSP_L4_L4A_PID;
    pstCgautoReq->enMsgId               = ID_APS_L4A_SET_CGAUTO_REQ;

    /* ��д��Ϣ���� */
    pstCgautoReq->stCtrl.ulPid          = pstAnsModeReq->stCtrl.ulModuleId;
    pstCgautoReq->stCtrl.ulClientId     = pstAnsModeReq->stCtrl.usClientId;
    pstCgautoReq->stCtrl.ulOpId         = pstAnsModeReq->stCtrl.ucOpId;

    pstCgautoReq->enAnsMode             = (TAF_PDP_ANSWER_MODE_ENUM_UINT8)pstAnsModeReq->ulAnsMode;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgautoReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgautoReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgcontrdpReq
 ��������  : ������PDP�����Ķ�̬������ѯ�������Ϣ��L4A
             (ID_APS_L4A_SET_CGCONTRDP_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
�޸���ʷ      :
  2.��    ��   : 2012��1��9��
    ��    ��   : c00184452
    �޸�����   : ����CID��Ϊ���鴫��

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgcontrdpReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU      *pstDynamicPdpReq;
    APS_L4A_SET_CGCONTRDP_REQ_STRU                         *pstCgcontrdpReq;

    /* ������ʼ�� */
    pstDynamicPdpReq    = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgcontrdpReq     = (APS_L4A_SET_CGCONTRDP_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGCONTRDP_REQ_STRU));
    if (VOS_NULL_PTR == pstCgcontrdpReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgcontrdpReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgcontrdpReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGCONTRDP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgcontrdpReq->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstCgcontrdpReq->ulReceiverPid      = MSP_L4_L4A_PID;
    pstCgcontrdpReq->enMsgId            = ID_APS_L4A_SET_CGCONTRDP_REQ;

    /* ��д��Ϣ���� */
    pstCgcontrdpReq->stCtrl.ulPid       = pstDynamicPdpReq->stCtrl.ulModuleId;
    pstCgcontrdpReq->stCtrl.ulClientId  = pstDynamicPdpReq->stCtrl.usClientId;
    pstCgcontrdpReq->stCtrl.ulOpId      = pstDynamicPdpReq->stCtrl.ucOpId;

    if(0xff == pstDynamicPdpReq->ucCid)
    {
        if(VOS_ERR == TAF_APS_GetActivedCid(pstCgcontrdpReq->aucCid))
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstCgcontrdpReq);
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgcontrdpReq: Get actived cid failed.");
            return;
        }
    }
    else
    {
        pstCgcontrdpReq->aucCid[pstDynamicPdpReq->ucCid] = 1;
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgcontrdpReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgcontrdpReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgscontrdpReq
 ��������  : ���Ͷ���PDP�����Ķ�̬������ѯ�������Ϣ��L4A
             (ID_APS_L4A_SET_CGSCONTRDP_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgscontrdpReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU       *pstDynamicPdpReq;
    APS_L4A_SET_CGSCONTRDP_REQ_STRU                        *pstCgscontrdpReq;

    /* ������ʼ�� */
    pstDynamicPdpReq    = (TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgscontrdpReq    = (APS_L4A_SET_CGSCONTRDP_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGSCONTRDP_REQ_STRU));
    if (VOS_NULL_PTR == pstCgscontrdpReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgscontrdpReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgscontrdpReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGSCONTRDP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgscontrdpReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCgscontrdpReq->ulReceiverPid     = MSP_L4_L4A_PID;
    pstCgscontrdpReq->enMsgId           = ID_APS_L4A_SET_CGSCONTRDP_REQ;

    /* ��д��Ϣ���� */
    pstCgscontrdpReq->stCtrl.ulPid      = pstDynamicPdpReq->stCtrl.ulModuleId;
    pstCgscontrdpReq->stCtrl.ulClientId = pstDynamicPdpReq->stCtrl.usClientId;
    pstCgscontrdpReq->stCtrl.ulOpId     = pstDynamicPdpReq->stCtrl.ucOpId;

    if(0xff == pstDynamicPdpReq->ucCid)
    {
        if(VOS_ERR == TAF_APS_GetActivedCid(pstCgscontrdpReq->aucCid))
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstCgscontrdpReq);
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgcontrdpReq: Get actived cid failed.");
            return;
        }
    }
    else
    {
        pstCgscontrdpReq->aucCid[pstDynamicPdpReq->ucCid] = 1;
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgscontrdpReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgscontrdpReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgtftrdpReq
 ��������  : ����TFT�Ķ�̬������ѯ����L4A
             (ID_APS_L4A_SET_CGTFTRDP_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgtftrdpReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU       *pstDynamicTftReq;
    APS_L4A_SET_CGTFTRDP_REQ_STRU              *pstCgtftrdpReq;

    /* ������ʼ�� */
    pstDynamicTftReq    = (TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgtftrdpReq    = (APS_L4A_SET_CGTFTRDP_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGTFTRDP_REQ_STRU));
    if (VOS_NULL_PTR == pstCgtftrdpReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgtftrdpReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgtftrdpReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGTFTRDP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgtftrdpReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCgtftrdpReq->ulReceiverPid       = MSP_L4_L4A_PID;
    pstCgtftrdpReq->enMsgId             = ID_APS_L4A_SET_CGTFTRDP_REQ;

    /* ��д��Ϣ���� */
    pstCgtftrdpReq->stCtrl.ulPid        = pstDynamicTftReq->stCtrl.ulModuleId;
    pstCgtftrdpReq->stCtrl.ulClientId   = pstDynamicTftReq->stCtrl.usClientId;
    pstCgtftrdpReq->stCtrl.ulOpId       = pstDynamicTftReq->stCtrl.ucOpId;

    if(0xff == pstDynamicTftReq->ucCid)
    {
        if(VOS_ERR == TAF_APS_GetActivedCid(pstCgtftrdpReq->aucCid))
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstCgtftrdpReq);
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgcontrdpReq: Get actived cid failed.");
            return;
        }
    }
    else
    {
        pstCgtftrdpReq->aucCid[pstDynamicTftReq->ucCid] = 1;
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgtftrdpReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgtftrdpReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgeqosReq
 ��������  : ����EPS�������������������Ϣ��L4A
             (ID_APS_L4A_SET_CGEQOS_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgeqosReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU           *pstEpsQosReq;
    APS_L4A_SET_CGEQOS_REQ_STRU                *pstCgeqosReq;

    /* ������ʼ�� */
    pstEpsQosReq    = (TAF_PS_SET_EPS_QOS_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgeqosReq    = (APS_L4A_SET_CGEQOS_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_CGEQOS_REQ_STRU));
    if (VOS_NULL_PTR == pstCgeqosReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgeqosReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgeqosReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGEQOS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgeqosReq->ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstCgeqosReq->ulReceiverPid             = MSP_L4_L4A_PID;
    pstCgeqosReq->enMsgId                   = ID_APS_L4A_SET_CGEQOS_REQ;

    /* ��д��Ϣ���� */
    pstCgeqosReq->stCtrl.ulPid              = pstEpsQosReq->stCtrl.ulModuleId;
    pstCgeqosReq->stCtrl.ulClientId         = pstEpsQosReq->stCtrl.usClientId;
    pstCgeqosReq->stCtrl.ulOpId             = pstEpsQosReq->stCtrl.ucOpId;

    pstCgeqosReq->stCgeqosInfo.bitOpQCI     = pstEpsQosReq->stEpsQosInfo.bitOpQCI;
    pstCgeqosReq->stCgeqosInfo.bitOpDLGBR   = pstEpsQosReq->stEpsQosInfo.bitOpDLGBR;
    pstCgeqosReq->stCgeqosInfo.bitOpULGBR   = pstEpsQosReq->stEpsQosInfo.bitOpULGBR;
    pstCgeqosReq->stCgeqosInfo.bitOpDLMBR   = pstEpsQosReq->stEpsQosInfo.bitOpDLMBR;
    pstCgeqosReq->stCgeqosInfo.bitOpULMBR   = pstEpsQosReq->stEpsQosInfo.bitOpULMBR;

    pstCgeqosReq->stCgeqosInfo.ucCid        = pstEpsQosReq->stEpsQosInfo.ucCid;
    pstCgeqosReq->stCgeqosInfo.ucValQCI     = pstEpsQosReq->stEpsQosInfo.ucQCI;
    pstCgeqosReq->stCgeqosInfo.ulValDLGBR   = pstEpsQosReq->stEpsQosInfo.ulDLGBR;
    pstCgeqosReq->stCgeqosInfo.ulValULGBR   = pstEpsQosReq->stEpsQosInfo.ulULGBR;
    pstCgeqosReq->stCgeqosInfo.ulValDLMBR   = pstEpsQosReq->stEpsQosInfo.ulDLMBR;
    pstCgeqosReq->stCgeqosInfo.ulValULMBR   = pstEpsQosReq->stEpsQosInfo.ulULMBR;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgeqosReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgeqosReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetCgeqosrdpReq
 ��������  : ����EPS���������Ķ�̬������ѯ�������Ϣ��L4A
             (ID_APS_L4A_SET_CGEQOSRDP_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetCgeqosrdpReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU   *pstDynamicEpsQosReq;
    APS_L4A_SET_CGEQOSRDP_REQ_STRU             *pstCgeqosrdpReq;

    /* ������ʼ�� */
    pstDynamicEpsQosReq = (TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstCgeqosrdpReq     = (APS_L4A_SET_CGEQOSRDP_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                    WUEPS_PID_TAF,
                                    sizeof(APS_L4A_SET_CGEQOSRDP_REQ_STRU));
    if (VOS_NULL_PTR == pstCgeqosrdpReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgeqosrdpReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCgeqosrdpReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_CGEQOSRDP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstCgeqosrdpReq->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstCgeqosrdpReq->ulReceiverPid      = MSP_L4_L4A_PID;
    pstCgeqosrdpReq->enMsgId            = ID_APS_L4A_SET_CGEQOSRDP_REQ;

    /* ��д��Ϣ���� */
    pstCgeqosrdpReq->stCtrl.ulPid       = pstDynamicEpsQosReq->stCtrl.ulModuleId;
    pstCgeqosrdpReq->stCtrl.ulClientId  = pstDynamicEpsQosReq->stCtrl.usClientId;
    pstCgeqosrdpReq->stCtrl.ulOpId      = pstDynamicEpsQosReq->stCtrl.ucOpId;

    if(0xff == pstDynamicEpsQosReq->ucCid)
    {
        if(VOS_ERR == TAF_APS_GetActivedCid(pstCgeqosrdpReq->aucCid))
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstCgeqosrdpReq);
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgcontrdpReq: Get actived cid failed.");
            return;
        }
    }
    else
    {
        pstCgeqosrdpReq->aucCid[pstDynamicEpsQosReq->ucCid] = 1;
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCgeqosrdpReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetCgeqosrdpReq: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aSetAuthdataReq
 ��������  : �����û����������Ȩ��Ϣ�����������Ϣ��L4A
             (ID_APS_L4A_SET_AUTHDATA_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aSetAuthdataReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU          *pstAuthdataInfoReq;
    APS_L4A_SET_AUTHDATA_REQ_STRU              *pstAuthdataReq;

    /* ������ʼ�� */
    pstAuthdataInfoReq  = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU*)(pMsgData);

    /* ������Ϣ */
    pstAuthdataReq      = (APS_L4A_SET_AUTHDATA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SET_AUTHDATA_REQ_STRU));
    if (VOS_NULL_PTR == pstAuthdataReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetAuthdataReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstAuthdataReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_SET_AUTHDATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstAuthdataReq->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstAuthdataReq->ulReceiverPid               = MSP_L4_L4A_PID;
    pstAuthdataReq->enMsgId                     = ID_APS_L4A_SET_AUTHDATA_REQ;

    /* ��д��Ϣ���� */
    pstAuthdataReq->stCtrl.ulPid                = pstAuthdataInfoReq->stCtrl.ulModuleId;
    pstAuthdataReq->stCtrl.ulClientId           = pstAuthdataInfoReq->stCtrl.usClientId;
    pstAuthdataReq->stCtrl.ulOpId               = pstAuthdataInfoReq->stCtrl.ucOpId;

    pstAuthdataReq->stAuthData.ucCid            = pstAuthdataInfoReq->stAuthDataInfo.ucCid;
    pstAuthdataReq->stAuthData.ucDefined        = pstAuthdataInfoReq->stAuthDataInfo.ucDefined;
    pstAuthdataReq->stAuthData.usAuthType       = pstAuthdataInfoReq->stAuthDataInfo.enAuthType;
    pstAuthdataReq->stAuthData.ucPwdLen         = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstAuthdataInfoReq->stAuthDataInfo.aucPassWord);
    pstAuthdataReq->stAuthData.ucUserNameLen    = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstAuthdataInfoReq->stAuthDataInfo.aucUserName);

    TAF_APS_String2Hex(pstAuthdataInfoReq->stAuthDataInfo.aucPlmn,
                       (VOS_UINT16)(VOS_StrLen((VOS_CHAR*)pstAuthdataInfoReq->stAuthDataInfo.aucPlmn)),
                      &(pstAuthdataReq->stAuthData.ulPLMN));

    PS_MEM_CPY(pstAuthdataReq->stAuthData.aucPassword,
               pstAuthdataInfoReq->stAuthDataInfo.aucPassWord,
               pstAuthdataReq->stAuthData.ucPwdLen);

    PS_MEM_CPY(pstAuthdataReq->stAuthData.aucUserName,
               pstAuthdataInfoReq->stAuthDataInfo.aucUserName,
               pstAuthdataReq->stAuthData.ucUserNameLen);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstAuthdataReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aSetAuthdataReq: Send message failed.");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndL4aAbortReq
 ��������  : ����Abort��Ϣ��L4a
             (ID_APS_L4A_ABORT_REQ)
 �������  : VOS_VOID   pMsgData        - ��Ϣ����(��������Ϣͷ)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��16��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndL4aAbortReq(
    VOS_UINT8                           ucCid
)
{
    APS_L4A_ABORT_REQ_STRU             *pstAbortReq;

    /* ������Ϣ */
    pstAbortReq      = (APS_L4A_ABORT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_ABORT_REQ_STRU));
    if (VOS_NULL_PTR == pstAbortReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aAbortReq: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstAbortReq + VOS_MSG_HEAD_LENGTH,
           0x00,
           sizeof(APS_L4A_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstAbortReq->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstAbortReq->ulReceiverPid               = MSP_L4_L4A_PID;
    pstAbortReq->enMsgId                     = ID_APS_L4A_ABORT_REQ;

    /* ��д��Ϣ���� */
    pstAbortReq->ucCid                      = ucCid;


    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstAbortReq))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndL4aAbortReq: Send message failed.");
        return;
    }

    return;
}


#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

