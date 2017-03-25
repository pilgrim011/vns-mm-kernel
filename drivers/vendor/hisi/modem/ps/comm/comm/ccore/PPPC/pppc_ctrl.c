

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ppp_inc.h"
#include "v_int.h"
#include "AtPppInterface.h"
#include "PppInterface.h"
#include "fwd_ppp.h"
#include "pppc_ctrl.h"
#include "taf_aps_ppp_pif.h"
#include "TTFLink.h"
#include "VosTaskPrioDef.h"
#include "NVIM_Interface.h"
#include "siapppih.h"
#include "pppc_pa_agent.h"
#include "CdsPppInterface.h"

#include "TTFMem.h"
#include "cttf_1x_rrlp_data_pif.h"
#include "ppp_trans_data_pif.h"
#include "rlp_ppp_pub_pif.h"
#include "cttf_1x_ppp_data_pif.h"
#include "cttf_hrpd_pa_public_pif.h"

#include "TtfNvInterface.h"
#include "pppc_eap_aka.h"
#include "pppc_ctrl.h"

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
#include "hdlc_hardware.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_CTRL_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern VOS_MSG_HOOK_FUNC                vos_MsgHook; /* AT2D01724 */

/* PPP����������Ϣ */
PPPC_CONTEXT_INFO_STRU                  g_stPppContext;

/* PPPC������ID */
VOS_UINT32                              g_ulPppcTaskId;

/* APS��Ϣ����,Ŀǰ��Ҫ���������ֻ�м����ȥ������Ϣ,�յ�����ȥ����INDֱ�������Դ����������� */
TTF_LINK_ST                             g_stApsCmdLink;

/* PPP�����ж��дӿյ��ǿյ�֪ͨ��Ϣ���� */
PPPC_DATA_Q_NOTIFY_CNT_STRU             g_stDataQNotifyCnt;

/* ��Ž���PPP��װ֮���CDS�������� */
VOS_UINT8                               g_aucUlEncapData[PPPC_MAX_UL_DATA_LEN];

PPPC_DATA_UL_ENCAP_MEM_STRU             g_astUlEncapMem[2];

/* PPPC��������ﵽ����֮������PPPC�����Ѷ�ʱ�� */
volatile HTIMER                         g_hReachMaxProcTimer = VOS_NULL_PTR;

/* PPPC���յ�terminate request�����restart timer, �ȴ�1s������taf����deact notify */
volatile HTIMER                         g_hRestartTimer     = VOS_NULL_PTR;
PS_BOOL_ENUM_UINT8                      g_ucLcpTermMask     = PS_FALSE;

/* PPPC���յ�PA�Ľ����Ȩ֪ͨ����ʱ����ȵ��յ�BSC�Ľ����ȨLCPЭ�̱��ĺ��ٴ��� */
volatile HTIMER                         g_hAADelayTimer     = VOS_NULL_PTR;

/* PPP������������ */
TTF_LINK_ST                             g_stPppUlLink;

/* PPP������������ */
TTF_LINK_ST                             g_stPppDlLink;

/* ���б��������Ƭ�������� */
extern TTF_LINK_ST                      g_stPppRebuildIncompleteSliceLink;

/* PPPC�����ݶ���ͳ����Ϣ�ṹ�� */
PPP_DATA_Q_STAT_STRU                    g_stPppcDataQueueStats;

/* ��PPPC��������ﵽ����ʱ����������������ʱ������,�˱�־λ��ʾ��ʱ���Ƿ�ʱ */
PS_BOOL_ENUM_UINT8                      g_enIsReachTimeout = PS_TRUE;

/* �յ�HRPD/eHRPD�ļ�����ϢʱҪ�ֱ���ʱ��,ȥ�����Ҫ�������̴��� */
/* 0:HRPD 1:eHRPD 2:PDN */
PPPC_ACT_HRPD_DELAY_PROC_TIMER_STRU     g_astActHrpdTimer[PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM];

/* �ж��Ƿ��ǳ�ʼ�Ľ����Ȩ,�յ�PA�Ľ����Ȩ֪ͨʱ��ΪPS_TRUE */
PS_BOOL_ENUM_UINT8                      g_enInitAccessAuth  = PS_FALSE;

#ifdef PPPC_HDLC_ST_TEST
VOS_UINT16                              g_usPppcUlDataProto = 0x0021;
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : PPPC_ShowPppContext
 ��������  : ��ȡPPP��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��25��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ShowPppContext(VOS_VOID)
{
    vos_printf("********************PPPC������Ϣ************************\n");
    vos_printf("enRatMode:            %d\n", g_stPppContext.enRatMode);
    vos_printf("enDialMode:           %d\n", g_stPppContext.enDialMode);
    vos_printf("enRatMode:            %d\n", g_stPppContext.enModemId);
    vos_printf("ulSendPid:            %d\n", g_stPppContext.ulSendPid);
    vos_printf("usMtu:                %d\n", g_stPppContext.usMru);
    vos_printf("ulPppIdBitMask:       %d\n", g_stPppContext.ulPppIdBitMask);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ShowDLProcStats
 ��������  : ��ȡPPP����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ShowDLProcStats(VOS_VOID)
{
    vos_printf("\n");
    vos_printf("********************PPPC����������Ϣ************************\n");
    vos_printf("PPPC�յ����������ݰ��ܸ���:            %d\n",
                g_stPppcDataQueueStats.ul1xDlFrameRcvCnt + g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt);
    vos_printf("����  1Xģʽ�յ����������ݰ��ܸ���:    %d\n", g_stPppcDataQueueStats.ul1xDlFrameRcvCnt);
    vos_printf("            �յ�������Э�̱��ĸ���:    %d\n", g_stPppcDataQueueStats.ul1xDlNegoRcvCnt);
    vos_printf("            ���͵�����IP������:        %d\n", g_stPppcDataQueueStats.ul1xDlIPDataSndCnt);
    vos_printf("      HRPDģʽ�յ����������ݰ��ܸ���:  %d\n", g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt);
    vos_printf("            �յ�������Э�̱��ĸ���:    %d\n", g_stPppcDataQueueStats.ulHrpdDlNegoRcvCnt);
    vos_printf("            ���͵�����IP������:        %d\n", g_stPppcDataQueueStats.ulHrpdDlIPDataSndCnt);
    vos_printf("PPPC�Ĵ洢����������������ڵ���:    %d\n", g_stPppcDataQueueStats.ulDlDataQMaxCnt);
    vos_printf("PPPC��������������ĵ�ǰ�ڵ���:        %d\n", g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt);
    vos_printf("PPPC���������������:                  %d\n", g_stPppcDataQueueStats.ulDlDataQEnqueueMsgCnt);
    vos_printf("PPPC���������ݳ��Ӵ�����:              %d\n", g_stPppcDataQueueStats.ulDlDataQProcMsgCnt);

    vos_printf("HDLC�����ڴ��������:                  %d\n", g_stPppcDataQueueStats.ulMemAllocDownlinkCnt);
    vos_printf("HDLC�����ڴ�����ʧ�ܴ���:              %d\n", g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt);
    vos_printf("HDLCӲ�����װIP����:                  %d\n", g_stPppcDataQueueStats.ulDownlinkSndDataCnt);

    vos_printf("PPPC���ж��нڵ����:                  %d\n", g_stPppDlLink.ulCnt);
    vos_printf("\n");

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ShowULProcStats
 ��������  : ��ȡPPP����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ShowULProcStats(VOS_VOID)
{
    vos_printf("\n");
    vos_printf("************************************************************\n");
    vos_printf("****��ǰ�ļ�FILE ID*****[%d]\n", PS_FILE_ID_PPPC_CTRL_C);
    vos_printf("********************PPPC����������Ϣ************************\n");
    vos_printf("PPPC�յ����������ݰ��ܸ���:            %d\n",
                g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt + g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt);
    vos_printf("����  1Xģʽ�յ�����������:            %d\n", g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt);
    vos_printf("            ���͵�����Э�̱��ĸ���:    %d\n", g_stPppcDataQueueStats.ul1xUlNegoSndCnt);
    vos_printf("            ���͵�����IP������:        %d\n", g_stPppcDataQueueStats.ul1xUlIPDataSndCnt);
    vos_printf("      HRPDģʽ�յ�����������:          %d\n", g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt);
    vos_printf("            ���͵�����Э�̱��ĸ���:    %d\n", g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt);
    vos_printf("            ���͵�����IP������:        %d\n", g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt);
    vos_printf("PPPC�Ĵ洢����������������ڵ���:    %d\n", g_stPppcDataQueueStats.ulUlDataQMaxCnt);
    vos_printf("PPPC��������������ĵ�ǰ�ڵ���:        %d\n", g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt);
    vos_printf("PPPC���������������:                  %d\n", g_stPppcDataQueueStats.ulUlDataQEnqueueMsgCnt);
    vos_printf("PPPC���������ݳ��Ӵ�����:              %d\n", g_stPppcDataQueueStats.ulUlDataQProcMsgCnt);

    vos_printf("HDLC�����ڴ��������:                  %d\n", g_stPppcDataQueueStats.ulMemAllocUplinkCnt);
    vos_printf("HDLC�����ڴ�����ʧ�ܴ���:              %d\n", g_stPppcDataQueueStats.ulMemAllocUplinkFailCnt);
    vos_printf("HDLCӲ����װ��Ч֡��:                  %d\n", g_stPppcDataQueueStats.ulUplinkSndDataCnt);
    vos_printf("HDLC�����ڴ��ͷŴ���:                  %d\n", g_stPppcDataQueueStats.ulMemFreeCnt);

    vos_printf("PPPC���ж��нڵ����:                  %d\n", g_stPppUlLink.ulCnt);

    vos_printf("\n");
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_GetUlEncapDataPtr
 ��������  : ��ȡ���з�װPPP֡���ݻ����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 *PPP_GetUlEncapDataPtr(VOS_VOID)
{
    return g_aucUlEncapData;
}

/*****************************************************************************
 �� �� ��  : PPP_InitEncapDataPtr
 ��������  : ��ʼ�����з�װPPP֡���ݻ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_InitEncapDataPtr(VOS_VOID)
{
    PS_MEM_SET(g_aucUlEncapData, 0, sizeof(g_aucUlEncapData));
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetInitAccessAuthMode
 ��������  : ���ó�ʼЯ��ģʽ
 �������  : enAccessAuth    ��ʼЯ��ģʽ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��8��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SetInitAccessAuthMode(PS_BOOL_ENUM_UINT8 enAccessAuth)
{
    g_enInitAccessAuth  = enAccessAuth;
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetInitAccessAuthMode
 ��������  : ��ȡ��ʼЭ��ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��8��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_GetInitAccessAuthMode(VOS_VOID)
{
    return g_enInitAccessAuth;
}

/*****************************************************************************
 �� �� ��  : PPPC_1X_IncreaseNegoRcvCnt
 ��������  : �յ���PPPЭ�̱�������һ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��18��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_1X_IncreaseNegoRcvCnt(VOS_VOID)
{
    g_stPppcDataQueueStats.ul1xDlNegoRcvCnt++;
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_IncreaseNegoRcvCnt
 ��������  : �յ���PPPЭ�̱�������һ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��18��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HRPD_IncreaseNegoRcvCnt(VOS_VOID)
{
    g_stPppcDataQueueStats.ulHrpdDlNegoRcvCnt++;
    return;
}



/*****************************************************************************
 �� �� ��  : PPP_GetActPppHeadNode
 ��������  : ��ȡ����PPP��Ϣ��ͷ�ڵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID *PPP_GetActPppHeadNode()
{
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

    return (VOS_VOID *)pstApsCurrHeadNode;
}

/*****************************************************************************
 �� �� ��  : PPP_GetConfigUserName
 ��������  : ��ȡ�û���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��05��29��
    ��    ��   : W00316385
    �޸�����   : ����ģʽ

*****************************************************************************/
VOS_UINT32 PPP_GetConfigUserName
(
    VOS_UINT8                          *pucUserName,
    VOS_UINT32                          ulPppId
)
{
    VOS_UINT32                          ulUserNameLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    if (VOS_NULL_PTR == pucUserName)
    {
        PPPC_WARNING_LOG("parameter is NULL.");

        return VOS_ERR;
    }

    pstPppCont  = &g_stPppContext;
    /* �жϵ�ǰ�Ƿ����ڽ��н����Ȩ */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)ulPppId);
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        ulUserNameLen = pstPppCont->stHrpdContext.ucAccessAuthLen;

        /* �Ѿ��ɹ��ӿ��ж�ȡ�˽����Ȩ��NAI��Ϣ */
        if ((0 != ulUserNameLen) && (ulUserNameLen <= CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN))
        {
            VOS_StrNCpy((VOS_CHAR *)pucUserName,
                (VOS_CHAR *)(pstPppCont->stHrpdContext.aucAccessAuthUserName),
                ulUserNameLen);
            *(VOS_UINT8 *)(pucUserName + ulUserNameLen) = '\0';

            return VOS_OK;
        }

        /* ���Ը���IMSI����NAI��Ϣ */
        return PPPC_UIM_BuildNAIByIMSI(pucUserName, CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN + 1);
    }

    ulUserNameLen = pstPppCont->ulUserNameLen;

    VOS_StrNCpy((VOS_CHAR *)pucUserName,
        (VOS_CHAR *)(pstPppCont->aucUserName),
        ulUserNameLen);
    *(VOS_UINT8 *)(pucUserName + ulUserNameLen) = '\0';

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_GetConfigPassWord
 ��������  : ��ȡ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��05��29��
    ��    ��   : W00316385
    �޸�����   : ����ģʽ

*****************************************************************************/
VOS_UINT32 PPP_GetConfigPassWord
(
    VOS_UINT8                          *pucPassWd
)
{
    VOS_UINT32                          ulPasswordLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;


    if (VOS_NULL_PTR == pucPassWd)
    {
        PPPC_WARNING_LOG("parameter is NULL.");

        return VOS_ERR;
    }

    pstPppCont  = &g_stPppContext;

    ulPasswordLen = pstPppCont->ulPasswordLen;

    VOS_StrNCpy((VOS_CHAR *)pucPassWd,
        (VOS_CHAR *)(pstPppCont->aucPassword),
        ulPasswordLen);
    *(VOS_UINT8 *)(pucPassWd + ulPasswordLen) = '\0';

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_GetDefaultMru
 ��������  : ��ȡĬ�ϵ�MRUֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��29��
    ��    ��   : W00316385
    �޸�����   :

*****************************************************************************/
VOS_UINT16 PPP_GetDefaultMru(VOS_VOID)
{
    return g_stPppContext.usMru;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetModemId
 ��������  : ��ȡPPP��Modem ID
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : c00199705
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 PPPC_GetModemId(VOS_VOID)
{
    return g_stPppContext.enModemId;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_GetAppType
 ��������  : ��ȡApplicationType
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��20��
    ��    ��   : w00316385
    �޸�����   :

*****************************************************************************/
VOS_UINT16 PPPC_HRPD_GetAppType(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.aenApplicationType[1];
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_GetStreamNumber
 ��������  : ��ȡStreamNumber
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��25��
    ��    ��   : c00184031
    �޸�����   :

*****************************************************************************/
VOS_UINT8 PPPC_HRPD_GetStreamNumber(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucStreamRN = 1;
    VOS_UINT8                           ucStreamSN = 2;
    VOS_UINT32                          ulSteamIndex;
    VOS_UINT32                          ulMaxSteamNum = 3;


    pstPppContext   = &g_stPppContext;

    /* Ŀǰֻ֧��DPA,EMPA��������������������� */
    for (ulSteamIndex = 0; ulSteamIndex < ulMaxSteamNum; ulSteamIndex++)
    {
        /* stream number����0Ϊ����,ʵ���д洢�����Ŵ�1��ʼ */
        if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex]))
        {
            ucStreamRN = (VOS_UINT8)(ulSteamIndex + 1);
        }
        else if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex]))
        {
            ucStreamSN = (VOS_UINT8)(ulSteamIndex + 1);
        }
        else
        {
            /* do nothing */
        }
    }

    /* �����ǰ���ڽ��н����Ȩ,����RN������ */
    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId)
    {
        return ucStreamRN;
    }
    else
    {
        return ucStreamSN;
    }
}

/*****************************************************************************
 �� �� ��  : PPPC_FidTask
 ��������  : PPPC��������
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-12-11
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_FidTask(VOS_VOID)
{
    MsgBlock*               pMsg;
    VOS_UINT32              ulEvent;
    VOS_UINT32              ulTaskID;
    VOS_UINT32              ulReturn;
    VOS_UINT32              ulEventMask;
    VOS_UINT32              ulExpectEVENT   = 0;
    VOS_UINT32              ulEventProcFlag = 0;


    ulTaskID = VOS_GetCurrentTaskID();

    if ( PS_NULL_UINT32 == ulTaskID )
    {
        PPPC_ERROR_LOG("PPPC, ERROR, reg Msg Func\r\n");
        return ;
    }

    if ( VOS_OK != VOS_CreateEvent( ulTaskID) )
    {
        PPPC_ERROR_LOG("PPPC, ERROR, create event FAIL\r\n");
        return ;
    }

    g_ulPppcTaskId = ulTaskID;

    ulExpectEVENT        = PPPC_UL_PKT_EVENT | PPPC_DL_PKT_EVENT | VOS_MSG_SYNC_EVENT;
    ulEventMask          = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    for(;;)
    {
        ulReturn = VOS_EventRead( ulExpectEVENT,
                                  ulEventMask,
                                  0,
                                  &ulEvent );

        ulEventProcFlag = 0;

        if(VOS_OK != ulReturn)
        {
            /* ������ֻ�ȡEventʧ�ܵ���RM���������ѭ�����л������������� */
            (VOS_VOID)VOS_TaskDelay(1);
            (VOS_VOID)LogPrint("WTTF_MAC_RLC_UlFidTask::RM read event error.\r\n" );
            continue;
        }

        /* �������б��ĵĴ��� */
        if ((PPPC_UL_PKT_EVENT == (ulEvent & PPPC_UL_PKT_EVENT))
            || (PPPC_DL_PKT_EVENT == (ulEvent & PPPC_DL_PKT_EVENT)))
        {

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkOpen();
#endif

            PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkClose();
#endif

            ulEventProcFlag = 1;
        }
        else
        {
            /* PCLINT */
        }

        if (1 == ulEventProcFlag)
        {
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg( ulTaskID );
        if  (VOS_NULL_PTR != pMsg)
        {
            if (VOS_NULL_PTR != vos_MsgHook)
            {
                
                /*lint -e522 by liukai*/
                (VOS_VOID)(vos_MsgHook)((VOS_VOID *)(pMsg));
                /*lint +e522 by liukai*/
            }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkOpen();
#endif

            PPPC_MsgProc(pMsg);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
            PPP_HDLC_HARD_PeriphClkClose();
#endif

            (VOS_VOID)VOS_FreeMsg(MSPS_PID_PPPC, pMsg);
        }
    }
    /*lint +e716*/
}

/*****************************************************************************
 �� �� ��  : PPPC_FidInit
 ��������  : PPPC��C�������ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-01-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32  ulResult = PS_FAIL;


    switch (ip)
    {
        case   VOS_IP_LOAD_CONFIG:

            /*ע��PPPC PID*/
            ulResult = VOS_RegisterPIDInfo(MSPS_PID_PPPC,
                                           PPPC_Init,
                                           PPPC_MsgProc);
            if (VOS_OK != ulResult)
            {
                vos_printf("PPPC_FidInit, register PPPC PID fail!\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterMsgTaskEntry(MSPS_FID_PPPC, PPPC_FidTask);
            if( VOS_OK != ulResult )
            {
                vos_printf("PPPC_FidInit, reg msg routine FAIL!,%d\n", ulResult);
                return VOS_ERR;
            }

            ulResult = VOS_RegisterTaskPrio(MSPS_FID_PPPC, PPPC_TASK_PRI);
            if( VOS_OK != ulResult )
            {
                vos_printf("PPPC_FidInit, register priority fail!\n");
                return VOS_ERR;
            }
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_QueueInit
 ��������  : ��ʼ�������ж���
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-10-30
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_QueueInit(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcDlDataQ;
    TTF_LINK_ST                        *pstPppcUlDataQ;


    /* ��ʼ�����ж��� */
    pstPppcDlDataQ    = &g_stPppDlLink;
    PS_MEM_SET(&g_stPppDlLink, 0, sizeof(g_stPppDlLink));

    TTF_LinkInit(MSPS_PID_PPPC, pstPppcDlDataQ);

    /* ��ʼ�����ж��� */
    pstPppcUlDataQ    = &(g_stPppUlLink);
    PS_MEM_SET(&g_stPppUlLink, 0, sizeof(g_stPppUlLink));

    TTF_LinkInit(MSPS_PID_PPPC, pstPppcUlDataQ);

    /* ��ʼ�������д�������Ϣ���� */
    PS_MEM_SET(&g_stDataQNotifyCnt, 0, sizeof(g_stDataQNotifyCnt));

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearDlDataQ
 ��������  : ������б��Ķ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ClearDlDataQ(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcDlDataQ;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT32                          ulRemainCnt;


    pstPppcDlDataQ    = &g_stPppDlLink;

    /* �ͷ�����Tx Entity��ص����ݡ��ڵ㻺�� */
    while (TTF_LINK_IS_NOT_EMPTY(pstPppcDlDataQ))
    {
        pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstPppcDlDataQ, &ulRemainCnt);

        /*�쳣:��������������һ��ʱ, �ݴ���, ����VOS_NULL_PTR*/
        if (VOS_NULL_PTR == pstDlDataNode)
        {
            return;
        }

        /* �ѱ�֤ѭ���ͷ�TTFMemory */
        TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

        pstDlDataNode->pstPduMem = VOS_NULL_PTR;

        /* �ͷ�TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);
        pstDlDataNode = VOS_NULL_PTR;
    }

    PPPC_INFO_LOG("PPP, PPPC_ClearDlDataQ, NORMAL, Clear Stat Info\n");

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearUlDataQ
 ��������  : ������б��Ķ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ClearUlDataQ(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcUlDataQ;
    PPPC_DATA_LINK_NODE_STRU           *pstUlDataNode;
    VOS_UINT32                          ulRemainCnt;


    pstPppcUlDataQ    = &g_stPppUlLink;

    /* �ͷ�����Tx Entity��ص����ݡ��ڵ㻺�� */
    while (TTF_LINK_IS_NOT_EMPTY(pstPppcUlDataQ))
    {
        pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstPppcUlDataQ, &ulRemainCnt);

        /*�쳣:��������������һ��ʱ, �ݴ���, ����VOS_NULL_PTR*/
        if (VOS_NULL_PTR == pstUlDataNode)
        {
            return;
        }

        /* �ͷ�TTFMemory,����һ���ڵ��Ӧһ��TTF�ڴ� */
        TTF_MemFree(MSPS_PID_PPPC, pstUlDataNode->pstPduMem);
        pstUlDataNode->pstPduMem = VOS_NULL_PTR;

        if (VOS_NULL_PTR != pstUlDataNode->pstUlDataInfo)
        {
            /* Free memory allocated for trace */
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode->pstUlDataInfo);
            pstUlDataNode->pstUlDataInfo    = VOS_NULL_PTR;
        }

        /* �ͷ�TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);
        pstUlDataNode = VOS_NULL_PTR;
    }

    PPPC_INFO_LOG("PPP, PPPC_ClearUlDataQ, NORMAL, Clear Stat Info\n");

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_AdapterTtfMemorytoMBuf
 ��������  : TtfMemory��������ת����MBUF
 �������  : pstTtfMem        TTFMemory��������
 �������  : ��
 �� �� ֵ  : PMBUF_S *        MBUF���͵�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PMBUF_S *PPPC_AdapterTtfMemorytoMBuf(TTF_MEM_ST *pstTtfMem)
{
    PMBUF_S                            *pstMBuf = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstCurrTtfMem = pstTtfMem;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;


    /* �ڲ����ñ�֤��ηǿ� */

    pstMBuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, pstCurrTtfMem->usUsed);
    if (VOS_NULL_PTR == pstMBuf)
    {
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
        PPPC_WARNING_LOG("Get MBuf Memory fail!");
        PPP_DBG_ERR_CNT(PPP_PHERR_873);
        return VOS_NULL_PTR;
    }

    while(VOS_NULL_PTR != pstCurrTtfMem)
    {
        pucData     = pstCurrTtfMem->pData;
        if (VOS_NULL_PTR == pucData)
        {
            PPPC_WARNING_LOG1("TTFMemory to MBuf Get Data Ptr fail!", pstCurrTtfMem->usUsed);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

            /* �ͷ�pstMBuf */
            PMBUF_Destroy(pstMBuf);
            PPP_DBG_ERR_CNT(PPP_PHERR_872);
            return VOS_NULL_PTR;
        }

        /* IP�����Ȳ��ܳ���1500�ֽ�����ת���ַ�Ҳ���ᳬ��3K,
        ÿ�ο�����ƫ��ulTotalDataLength,ulTotalDataLength���ڽӿ��ڲ���ˢ�� */
        ulRet   = PMBUF_CopyDataFromBufferToPMBuf(pstMBuf,
                                             pstMBuf->ulTotalDataLength,
                                             pstCurrTtfMem->usUsed,
                                             pucData,
                                             MSPS_PID_PPPC);
        if (VOS_OK != ulRet)
        {
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
            PPPC_WARNING_LOG1("Copy Data to MBuf Memory fail!\r\n", ulRet);
            /* �ͷ�pstMBuf */
            PMBUF_Destroy(pstMBuf);
            PPP_DBG_ERR_CNT(PPP_PHERR_874);
            return VOS_NULL_PTR;
        }

        pstCurrTtfMem   = pstCurrTtfMem->pNext;

    }

    TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

    return pstMBuf;
}

/*****************************************************************************
 �� �� ��  : PPP_AdapterMBuftoTtfMemory
 ��������  : MBUF��������ת����TTFMemory
 �������  : pstMBuf          MBUF��������
             ulMemPoolId      ������ڴ��Id
             ulOffset         MBUF��������ƫ����
             ulLength         MBUF��������ת��ΪTTFMemory���͵ĳ���
 �������  : ��
 �� �� ֵ  : TTF_MEM_ST *     TTFMemory���͵�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
TTF_MEM_ST *PPPC_AdapterMBuftoTtfMemory
(
    PMBUF_S                            *pstMBuf,
    VOS_UINT32                          ulMemPoolId,
    VOS_UINT32                          ulOffset,
    VOS_UINT32                          ulLength
)
{
    TTF_MEM_ST                         *pstTtfMem = VOS_NULL_PTR;
    VOS_UINT8                          *pucData;


    if (ulOffset > pstMBuf->ulTotalDataLength)
    {
        return VOS_NULL_PTR;
    }

    pucData     = pstMBuf->stDataBlockDescriptor.pucData + ulOffset;

    /* MBUFתΪTTFMemoryֻ�����ǵݽ���������ʱ������Ҫ�õ� */
    pstTtfMem   = TTF_MemBlkCopyAlloc(MSPS_PID_PPPC,
                ulMemPoolId, pucData, (VOS_UINT16)ulLength);

    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPPC_WARNING_LOG1("Copy Data to TTFMemory fail!\r\n", ulLength);
        PPP_DBG_ERR_CNT(PPP_PHERR_875);
        return VOS_NULL_PTR;
    }

    return pstTtfMem;
}


/*****************************************************************************
 �� �� ��  : PPPC_RcvRlpDlFrame
 ��������  : PPPģ���յ�RLP�����б���
 �������  : pstData          ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_RcvRlpDlFrame
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode,
    VOS_UINT8                           ucPppId
)
{
    /* �ڲ����ñ�֤��ηǿ� */


    /* ���÷�Ƭ���麯������ */
    FWD_PppRebuild(usSeqNr, pstData, ucRatMode, ucPppId);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_PrepareUlEncapMem
 ��������  : Ϊ��װ��������׼���ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_PrepareUlEncapMem(VOS_UINT16 usLen)
{
    VOS_UINT16                          usFrmedMaxLen;
    VOS_UINT16                          usFirstFragmentLen  = 0;
    VOS_UINT16                          usSecendFragmentLen = 0;

    /* ����(2*ԭʼ���ݳ���+13B)���� */
    VOS_UINT32                          ulMaxLen            = PPPC_MAX_UL_ENCAP_LEN - 7;


    if ((0 == usLen) || (usLen > ulMaxLen))
    {
        PPPC_WARNING_LOG1("Data len is invalid %d\r\n", usLen);
        return VOS_ERR;
    }

    /* ��װ����ܵ�������ݳ���(2*ԭʼ���ݳ���+13B) */
    usFrmedMaxLen = (VOS_UINT16)(2 * usLen + 13);
    usFirstFragmentLen  = (usFrmedMaxLen >= PPPC_MAX_UL_ENCAP_LEN) ? PPPC_MAX_UL_ENCAP_LEN : usFrmedMaxLen;
    usSecendFragmentLen = (usFrmedMaxLen >= PPPC_MAX_UL_ENCAP_LEN) ? (usFrmedMaxLen - usFirstFragmentLen) : 0;

    /* �����һ���ڴ� */
    if (PS_TRUE == g_astUlEncapMem[0].enPtrIsUsed)
    {
        TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[0].pstDataPtr);
        g_astUlEncapMem[0].pstDataPtr = VOS_NULL_PTR;
        g_astUlEncapMem[0].enPtrIsUsed = PS_FALSE;
    }

    g_astUlEncapMem[0].pstDataPtr  = TTF_MemBlkAlloc(MSPS_PID_PPPC,
        TTF_MEM_POOL_ID_UL_DATA, usFirstFragmentLen);

    /* ���벻���ڴ淵�ش��� */
    if (VOS_NULL_PTR == g_astUlEncapMem[0].pstDataPtr)
    {
        PPPC_INFO_LOG("Alloc Fail");
        return VOS_ERR;
    }
    g_astUlEncapMem[0].enPtrIsUsed = PS_TRUE;

    if (0 != usSecendFragmentLen)
    {
        /* ����ڶ����ڴ� */
        if (PS_TRUE == g_astUlEncapMem[1].enPtrIsUsed)
        {
            TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[1].pstDataPtr);
            g_astUlEncapMem[1].pstDataPtr = VOS_NULL_PTR;
            g_astUlEncapMem[1].enPtrIsUsed = PS_FALSE;
        }

        g_astUlEncapMem[1].pstDataPtr  = TTF_MemBlkAlloc(MSPS_PID_PPPC,
            TTF_MEM_POOL_ID_UL_DATA, usSecendFragmentLen);

        /* ���벻���ڴ淵�ش��� */
        if (VOS_NULL_PTR == g_astUlEncapMem[1].pstDataPtr)
        {
            PPPC_INFO_LOG("Alloc Fail");
            return VOS_ERR;
        }
        g_astUlEncapMem[1].enPtrIsUsed = PS_TRUE;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_DlEnqueueData
 ��������  : 1X��HRPD���õ����б�����ӽӿ�,�ڴ治������ӿ����ͷ�
 �������  : pstPppSdu         PPP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_DlEnqueueData
(
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode,
    TTF_LINK_ST                        *pstDataLink,
    VOS_UINT32                         *pulNonEmptyEvent
)
{
    VOS_UINT32                          ulTemporyEmptyEvent = PS_FALSE;
    VOS_UINT32                          ulRet;


    /* �����ݽ��������β�� */
    ulRet = TTF_LinkSafeInsertTail(MSPS_PID_PPPC, pstDataLink,
            &(pstDlNode->stNode), &ulTemporyEmptyEvent);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Insert Fail", ulRet);

        return ulRet;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendDlDataNotifyCommon
 ��������  : ������������Ҫ����֪ͨ��1X��HRPD��ʹ�øýӿ�
 �������  : pstDataLink         ����
             ulNonEmptyEvent     ��¼�����Ƿ������ɿյ��ǿյ�ת��
             ulSendMsgCnt        ���͸���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SendDlDataNotifyCommon
(
    TTF_LINK_ST                        *pstDataLink,
    VOS_UINT32                          ulSendMsgCnt
)
{
    g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt = TTF_LinkCnt(MSPS_PID_PPPC, pstDataLink);
    if (g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt > g_stPppcDataQueueStats.ulDlDataQMaxCnt)
    {
        /* ˢ�����ж����йҽӵ����ڵ�ͳ��ֵ */
        g_stPppcDataQueueStats.ulDlDataQMaxCnt = g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt;
        PPPC_INFO_LOG1("The DL Quene max count is %d.\n", g_stPppcDataQueueStats.ulDlDataQMaxCnt);
    }

    /*��PPP�������ݴ���ָʾ*/
    if (VOS_OK != PPPC_SndDlDataNotify())
    {
        /* ������Ϣ֪ͨʧ�ܣ���Ҫ����������� */
        PPPC_ClearDlDataQ();
        PPPC_WARNING_LOG("Send DL data notify fail.");
        return;
    }

    g_stPppcDataQueueStats.ulDlDataQEnqueueMsgCnt += ulSendMsgCnt;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_DlEnqueueData
 ��������  : ����HRPD�������
 �������  : pstPppSdu         PPP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HRPD_DlEnqueueData(RLP_PPP_HRPD_TRANS_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;   /* ��¼�����Ƿ������ɿյ��ǿյ�ת�� */
    VOS_UINT32                          ulRet;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;


    /* ����ڵ� */
    pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstDlNode)
    {
        PPPC_WARNING_LOG("Alloc Fail");

        /* �ͷ�RLP�����TTF�ڴ� */
        TTF_MemFree(MSPS_PID_PPPC, pstPackets->pstSdu);

        return;
    }

    PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstDlNode->ulPduCnt     = 1;
    pstDlNode->pstPduMem    = pstPackets->pstSdu;
    pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstDlNode->ucStreamNum  = pstPackets->ucStreamNumber;
    pstDlNode->usHigherLayerProtocol  = pstPackets->ucHigherLayerProtocol;

    /* TODO: aucReservLabel needs to copied
    pstDlNode->ucResvLabel  = pstPackets->ucReservationLabel;*/
    pstDlNode->enRatMode    = PPPC_GetRatMode();

    ulRet   = PPPC_DlEnqueueData(pstDlNode, &g_stPppDlLink, &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        /* �ͷ�RLP�����TTF�ڴ� */
        TTF_MemFree(MSPS_PID_PPPC, pstPackets->pstSdu);

        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    /* TODO:ĿǰHRPD����ÿ��ֻ��һ��,������Ҫ��PAһ���޸�Ϊ��1Xһ��һ�η���16�� */
    PPPC_SendDlDataNotifyCommon(&g_stPppDlLink, 1);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_FreePacketsTtmMem
 ��������  : �ͷ����б����е�TTF�ڴ�
 �������  : pstPackets         ���б���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��17��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_FreePacketsTtmMem(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulLoop;


    /* �ڲ����ñ�֤��ηǿ� */

    for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ulLoop++)
    {
        if (VOS_NULL_PTR != pstPackets->astDeliverSdus[ulLoop].pstSdu)
        {
            /* �ͷ�RLP�����TTF�ڴ� */
            TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_DlEnqueueData
 ��������  : ����1X�������
 �������  : pstPppSdu         PPP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_1X_DlEnqueueData(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;   /* ��¼�����Ƿ������ɿյ��ǿյ�ת�� */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPduIndex      = 0;
    TTF_LINK_ST                        *pstDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;

#if (FEATURE_OFF == FEATURE_HARDWARE_HDLC_ON_CCPU)
    TTF_MEM_ST                         *pstTtfMem       = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstNextTtfMem   = VOS_NULL_PTR;
#endif

    pstDataLink    = &g_stPppDlLink;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ++ulLoop)
     {
         if (VOS_NULL_PTR == pstPackets->astDeliverSdus[ulLoop].pstSdu)
         {
             PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", ulLoop);
             continue;
         }

         /* ����ڵ� */
         pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
         if (VOS_NULL_PTR == pstDlNode)
         {
             PPPC_WARNING_LOG1("Alloc Fail", ulLoop);

             /* �ͷ�RLP�����TTF�ڴ� */
             TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);

             continue;
         }

         PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
         pstDlNode->pstPduMem    = pstPackets->astDeliverSdus[ulLoop].pstSdu;
         pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
         pstDlNode->ucPdnId      = pstPackets->ucPdnId;
         pstDlNode->enRatMode    = PPPC_RAT_MODE_1X;
         pstDlNode->pstPduMem->usApp        = pstPackets->astDeliverSdus[ulPduIndex].usSeq;

         ulRet = PPPC_DlEnqueueData(pstDlNode, pstDataLink, &ulNonEmptyEvent);
         if (VOS_OK != ulRet)
         {
             PPPC_WARNING_LOG1("Insert Fail", ulLoop);

             /* �ͷ�RLP�����TTF�ڴ� */
             TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);

             /* �ͷŽڵ� */
             TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

             continue;
         }
     }

#else

    /* ����ڵ� */
    pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstDlNode)
    {
        PPPC_WARNING_LOG("Alloc Fail");

        PPPC_FreePacketsTtmMem(pstPackets);

        return;
    }

    /* �ڵ��ʼ�� */
    PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstDlNode->ucPdnId      = pstPackets->ucPdnId;
    pstDlNode->enRatMode    = PPPC_RAT_MODE_1X;
    pstDlNode->pstPduMem    = pstPackets->astDeliverSdus[ulPduIndex].pstSdu;

    pstTtfMem               = pstDlNode->pstPduMem;
    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPPC_WARNING_LOG("TTF Mem is null");

        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    pstTtfMem->usApp        = pstPackets->astDeliverSdus[ulPduIndex].usSeq;

    for (ulLoop = 1; ulLoop < pstPackets->ucSduCount; ++ulLoop)
    {
        pstTtfMem->pNext    = pstPackets->astDeliverSdus[ulLoop].pstSdu;
        pstNextTtfMem       = pstTtfMem->pNext;

        if (VOS_NULL_PTR == pstTtfMem->pNext)
        {
            PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", ulLoop);
            continue;
        }

        /* usApp���ڴ洢���к� */
        pstTtfMem->pNext->usApp = pstPackets->astDeliverSdus[ulLoop].usSeq;
        pstTtfMem               = pstNextTtfMem;
        ulPduIndex++;
    }
    pstTtfMem->pNext        = VOS_NULL_PTR;

    pstDlNode->ulPduCnt     = ulPduIndex + 1;
    /* �ڵ㸳ֵ��ϲ������ */
    ulRet = PPPC_DlEnqueueData(pstDlNode, pstDataLink, &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Insert Fail", ulLoop);

        PPPC_FreePacketsTtmMem(pstPackets);

        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

#endif

    /* ֪ͨPPPC������������ */
    PPPC_SendDlDataNotifyCommon(pstDataLink, pstPackets->ucSduCount);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_UlEnqueueData
 ��������  : 1X��HRPD���õ�����������ӽӿ�,�ڵ��ڴ�������ӿ����ͷ�
 �������  : pstNode         ���нڵ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��05��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_UlEnqueueData(PPPC_DATA_LINK_NODE_STRU *pstUlNode)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;    /* ��¼�����Ƿ������ɿյ��ǿյ�ת�� */
    VOS_UINT32                          ulRet;
    TTF_LINK_ST                        *pstUlDataLink;


    pstUlDataLink    = &g_stPppUlLink;

    /* �����ݽ��������β�� */
    ulRet = TTF_LinkSafeInsertTail(MSPS_PID_PPPC, pstUlDataLink,
            &(pstUlNode->stNode), &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        /* �ͷ�TTF�ڴ� */
        TTF_MemFree(MSPS_PID_PPPC, pstUlNode->pstPduMem);

        if (VOS_NULL_PTR != pstUlNode->pstUlDataInfo)
        {
            /* Free memory allocated for trace */
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlNode->pstUlDataInfo);
            pstUlNode->pstUlDataInfo    = VOS_NULL_PTR;
        }

        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlNode);

        PPPC_WARNING_LOG("The UL data node is failed to insert!\n");
        return;
    }

    g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt = TTF_LinkCnt(MSPS_PID_PPPC, pstUlDataLink);
    if (g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt > g_stPppcDataQueueStats.ulUlDataQMaxCnt)
    {
        /* ˢ�����ж����йҽӵ����ڵ�ͳ��ֵ */
        g_stPppcDataQueueStats.ulUlDataQMaxCnt = g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt;
        PPPC_INFO_LOG1("The UL Quene max count is %d.\n", g_stPppcDataQueueStats.ulUlDataQMaxCnt);
    }

    /*��PPP�������ݴ���ָʾ*/
    if (VOS_OK != PPPC_SndUlDataNotify())
    {
        PPPC_WARNING_LOG("Send UL data notify fail.\n");
        /* ������Ϣ֪ͨʧ�ܣ���Ҫ����������� */
        PPPC_ClearUlDataQ();
        return;
    }

    g_stPppcDataQueueStats.ulUlDataQEnqueueMsgCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_UlEnqueueData
 ��������  : PPPģ������HRPD���ݱ������
 �������  : pstNode         ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��05��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HRPD_UlEnqueueData(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    TTF_MEM_ST                         *pstTTFMem;


    /* ����ڵ� */
    pstUlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstUlNode)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_INFO_LOG("Alloc mem fail.");
        return;
    }

    PPP_MemSet(pstUlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstUlNode->ulPduCnt     = 1;
    pstUlNode->pstPduMem    = pstPppSdu->pstSdu;
    pstUlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstUlNode->ucPdnId      = pstPppSdu->ucPdnId;
    pstUlNode->enRatMode    = PPPC_GetRatMode();
    pstUlNode->ucStreamNum  = PPPC_HRPD_GetStreamNumber(1);

    /* enIpDataType ����rrlp */
    pstUlNode->enIpDataType = TTF_ParseIpDataType(MSPS_PID_PPPC, pstPppSdu->pstSdu);

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    if (PPPC_RAT_MODE_EHRPD == pstUlNode->enRatMode)
    {
        TTF_MEM_RESUME_TO_HDR(pstUlNode->pstPduMem, 1);
        pstUlNode->pstPduMem->pData[0] = pstUlNode->ucPdnId;
    }
#endif

    TTF_NodeInit(&(pstUlNode->stNode));

    /* ���нڵ��ڹ�����Ӻ������ͷ� */
    PPPC_UlEnqueueData(pstUlNode);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_1X_UlEnqueueData
 ��������  : PPPģ������1X���ݱ������
 �������  : pstNode         ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��04��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_1X_UlEnqueueData(const CDS_CDMA_1X_TRANS_DATA_STRU *pstPppSdu)
{
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    TTF_MEM_ST                         *pstTTFMem;


    /* ����ڵ� */
    pstUlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstUlNode)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_INFO_LOG("Alloc mem fail.");
        return;
    }

    PPP_MemSet(pstUlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstUlNode->ulPduCnt     = 1;
    pstUlNode->pstPduMem    = pstPppSdu->pstSdu;
    pstUlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstUlNode->ucPdnId      = pstPppSdu->ucPdnId;
    pstUlNode->enRatMode    = PPPC_RAT_MODE_1X;
    TTF_NodeInit(&(pstUlNode->stNode));

    /* enIpDataType ����rrlp */
    pstUlNode->enIpDataType = TTF_ParseIpDataType(MSPS_PID_PPPC, pstPppSdu->pstSdu);

    /* pstUlDataInfo����rrlp����trace��ȡ */
    pstUlNode->pstUlDataInfo    = (PS_DATA_EXT_INFO_STRU *)PS_MEM_ALLOC(
        MSPS_PID_PPPC, sizeof(PS_DATA_EXT_INFO_STRU));
    if (VOS_NULL_PTR == pstUlNode->pstUlDataInfo)
    {
        /* �ͷ�TTF�ڴ� */
        TTF_MemFree(MSPS_PID_PPPC, pstUlNode->pstPduMem);

        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlNode);

        PPPC_WARNING_LOG("pstUlDataInfo is failed to alloc!\n");
        return;
    }

    FWD_PppFillDataInfo(pstPppSdu->pstSdu->pData, pstUlNode->pstUlDataInfo);

    /* ���нڵ��ڹ�����Ӻ������ͷ� */
    PPPC_UlEnqueueData(pstUlNode);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_DlSoftProc
 ��������  : PPP�����������
 �������  : pstDlDataLink         ������·
             ucPppId                PPP ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_DlSoftProc
(
    TTF_LINK_ST                        *pstDlDataLink,
    VOS_UINT8                           ucPppId
)
{
    TTF_MEM_ST                         *pstTtfMem;
    TTF_MEM_ST                         *pstNextTtfMem;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT32                          ulRemainCnt;
    VOS_UINT16                          usSeq;
    VOS_UINT32                          ulPduIndex;


    pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
        pstDlDataLink, &ulRemainCnt);

    /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstDlDataNode )
    {
        PPPC_WARNING_LOG("PPP DL Queue is Empty!\r\n");
        return;
    }

    pstTtfMem   = pstDlDataNode->pstPduMem;
    usSeq       = pstTtfMem->usApp;

    for (ulPduIndex = 0; ulPduIndex < pstDlDataNode->ulPduCnt; ulPduIndex++)
    {
        /* ���ʱ�ѱ�֤���е�TTFMEM�ǿ� */
        pstNextTtfMem   = pstTtfMem->pNext;

        /* ���б��ĳ���ͳ�� */
        g_stPppcDataQueueStats.ulDlDataQProcMsgCnt++;

        /* ���TTFMEM�е�usUsed���ڿ��ܵ�����Ƭ���ĳ���,�����˷�Ƭ������һƬ���� */
        if (pstTtfMem->usUsed > TTF_BIT2BYTE(PPPC_MAX_FRAGMENT_BIT_LEN))
        {
            PPPC_WARNING_LOG1("Ttf Mem used len is invalid:%d\r\n", pstTtfMem->usUsed);
        }
        else
        {
            PPPC_RcvRlpDlFrame(usSeq, pstTtfMem, pstDlDataNode->enRatMode, ucPppId);
        }

        if (VOS_NULL_PTR != pstNextTtfMem)
        {
            pstTtfMem   = pstNextTtfMem;
            usSeq       = pstNextTtfMem->usApp;
        }
        else
        {
            break;
        }
    }

    TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

    /* �ͷŽڵ� */
    TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetupAAPppByState
 ��������  : �жϽ����ȨPPP��״̬�����Ƿ���ҪSetup
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��14��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SetupAAPppByState(VOS_VOID)
{
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;


    pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];

    /* �����Ȩֻ֧��CHAP, ���Ҳ���ʡ�� */
    PPPC_SetAuthSwitch(PPPC_AUTH_SWITCH_OFF, PPPC_AUTH_SWITCH_ON);

    if (VOS_NULL_PTR == pstPppInfo->pstLcpInfo)
    {
        /* ���LCPʵ��û�д�����ҪSetup�����ȨPPP */
        PPPC_SetupPpp(PPPC_PPP_ID_FOR_ACCESS_AUTH);
    }
    else
    {
        pstLcpInfo  = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
        if ((PPP_STATE_INITIAL == pstLcpInfo->stFsm.ucState)
            || (PPP_STATE_STARTING == pstLcpInfo->stFsm.ucState)
            || (PPP_STATE_CLOSED == pstLcpInfo->stFsm.ucState))
        {
           /* ���״̬Ϊinitial/starting/closed��ҪSetup�����ȨPPP */
            PPPC_SetupPpp(PPPC_PPP_ID_FOR_ACCESS_AUTH);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ActAccessAuth
 ��������  : ���н����Ȩ
 �������  : pstPppInfo             PPPʵ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ActAccessAuth(PPPINFO_S *pstPppInfo)
{
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulRet;

    ucPppId = (VOS_UINT8)pstPppInfo->ulRPIndex;

    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId)
    {
        /* ���ý����Ȩ״̬ */
        if (PS_FALSE == PPPC_IsDoingAccessAuth(ucPppId))
        {
            /* ֪ͨRPA�����Ȩ��ʼ */
            PPPC_HRPD_SendRpaAccessAuthPhaseInd();

            /* ���ý����Ȩ��־λ */
            PPPC_ChangeAccessAuthState(PS_TRUE, PPPC_PPP_ID_FOR_ACCESS_AUTH);

            /* ���PA��PPPC���͹������Ȩ֪ͨ˵���ǳ�ʼЭ�� */
            if (PS_TRUE == PPPC_GetInitAccessAuthMode())
            {
                if (VOS_NULL_PTR != g_hAADelayTimer)
                {
                    ulRet = VOS_StopRelTimer((HTIMER*)&g_hAADelayTimer);
                    if (VOS_OK != ulRet)
                    {
                        PPPC_WARNING_LOG("Stop AA delay proc timer fail!");
                    }
                    g_hAADelayTimer = VOS_NULL_PTR;
                }
            }

        }

     }
}

/*****************************************************************************
 �� �� ��  : PPPC_DlDequeueProc
 ��������  : ���б��ĳ��Ӵ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_DlDequeueProc()
{
    TTF_LINK_ST                        *pstDlDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRemainCnt;
#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT32                          ulDealCnt = 0;
#endif


    pstDlDataLink  = &g_stPppDlLink;

    pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlDataLink);
    /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstDlDataNode )
    {
        PPPC_WARNING_LOG("PPP DL Queue is Empty!\r\n");
        return;
    }

    /* ��ȡPPP ID */
    ulRet = PPPC_GetCurrentPppId(pstDlDataNode->enRatMode, pstDlDataNode->ucStreamNum, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG3("Get ppp id fail!\r\n", pstDlDataNode->enRatMode,
            pstDlDataNode->ucStreamNum, ucPppId);

        pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstDlDataLink, &ulRemainCnt);

        TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

        /* �ͷŽڵ� */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);

        return;
    }

    /* ����MAX PPP Inactive Timer */
    PPPC_StartPppInactiveTimer(ucPppId);

    if ((PS_FALSE == PPPC_IsDoingAccessAuth(ucPppId))
        && (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId))
    {
        /* ��������ȨPPP����initial/starting/closed״̬,�յ�����config
            ���Ĳ������κδ���,��Ҫ�ֶ�����һ�� */
        PPPC_SetupAAPppByState();
    }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    if (PPPC_RAT_MODE_EHRPD == pstDlDataNode->enRatMode)
    {
        PPPC_DlSoftProc(pstDlDataLink, ucPppId);
        return;
    }

    ulRet = PPPC_HDLC_HARD_DefPacket(pstDlDataLink, (VOS_UINT16)ucPppId, &ulDealCnt);

    /* ���б��ĳ���ͳ�� */
    g_stPppcDataQueueStats.ulDlDataQProcMsgCnt += ulDealCnt;

    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Def packet fail!\r\n", ucPppId);
        return;
    }

    return;

#else

    PPPC_DlSoftProc(pstDlDataLink, ucPppId);
    return;

#endif
}

/*****************************************************************************
 �� �� ��  : PPPC_UlDequeueProc
 ��������  : ���б��ĳ��Ӵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UlDequeueProc(VOS_VOID)
{
    TTF_LINK_ST                        *pstUlDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstUlDataNode;
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulRet = VOS_OK;
    VOS_UINT32                          ulRemainCnt;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulDealCnt = 0;
#endif

    pstUlDataLink  = &g_stPppUlLink;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlDataLink);

    if(VOS_NULL_PTR == pstUlDataNode)
    {
        PPPC_WARNING_LOG("PPP UL Queue is Empty!\r\n");
        return VOS_OK;
    }

    ucPdnId     = pstUlDataNode->ucPdnId;

    ulRet   = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", ucPdnId, ucPppId);

        /* ��ȡPPP IDʧ���Ѿ��޷���������,ɾ����ǰ�ڵ� */
        pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstUlDataLink, &ulRemainCnt);

        /* �ͷ�TTFMemory,����һ���ڵ��Ӧһ��TTF�ڴ� */
        TTF_MemFree(MSPS_PID_PPPC, pstUlDataNode->pstPduMem);
        pstUlDataNode->pstPduMem = VOS_NULL_PTR;

        if (VOS_NULL_PTR != pstUlDataNode->pstUlDataInfo)
        {
            /* Free memory allocated for trace */
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode->pstUlDataInfo);
            pstUlDataNode->pstUlDataInfo    = VOS_NULL_PTR;
        }

        /* �ͷ�TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);
        pstUlDataNode = VOS_NULL_PTR;

        return VOS_OK;
    }

    #ifdef PPPC_HDLC_ST_TEST
    ulRet   = PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, g_usPppcUlDataProto, pstUlDataLink, &ulDealCnt);
    #else

    /*���Э����*/
    if (PPPC_RAT_MODE_EHRPD == PPPC_GetRatMode())
    {
        ulRet   = PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, PPP_H_PF_VSNP, pstUlDataLink, &ulDealCnt);
    }
    else
    {
        ulRet   = PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, PPP_IP, pstUlDataLink, &ulDealCnt);
    }
    #endif

    /* ���б��ĳ�����ͳ�� */
    g_stPppcDataQueueStats.ulUlDataQProcMsgCnt += ulDealCnt;
    return ulRet;

#else

    pstUlDataNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlDataLink);
    /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstUlDataNode )
    {
        PPPC_WARNING_LOG("PPP UL Queue is Empty!\r\n");
        return VOS_OK;
    }

    if (VOS_NULL_PTR == pstUlDataNode->pstPduMem)
    {
        PPPC_WARNING_LOG("pstUlDataNode->pstPduMem is null!\r\n");
        return VOS_OK;
    }

    /* ׼�����������ڴ� */
    ulRet   = PPPC_PrepareUlEncapMem(pstUlDataNode->pstPduMem->usUsed);
    if (VOS_OK != ulRet)
    {
        PPPC_INFO_LOG("Alloc ul mem fail!\r\n");

        return VOS_OK;
    }

    pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
        pstUlDataLink, &ulRemainCnt);


    /* ���б��ĳ�����ͳ�� */
    g_stPppcDataQueueStats.ulUlDataQProcMsgCnt++;

    ucPdnId     = pstUlDataNode->ucPdnId;

    PPPC_RcvCdsUlFrame(ucPdnId, pstUlDataNode->pstPduMem, pstUlDataNode->enRatMode,
        pstUlDataNode->pstUlDataInfo, pstUlDataNode->ucStreamNum);

    /* �ͷŽڵ� */
    TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);

    return VOS_OK;

#endif
}

/*****************************************************************************
 �� �� ��  : PPPC_ProcLinkNodeByDirection
 ��������  : ����ʱ���������ߴ������ж��С����ж���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_ProcLinkNodeByDirection
(
    VOS_UINT32                              ulDlStamp,
    VOS_UINT32                              ulUlStamp,
    PPPC_PROC_LINK_DIRECTION_ENUM_UINT16    enProcDire,
    VOS_UINT32                             *pulPppcUlCallCnt
)
{
    VOS_UINT32                              ulRet = VOS_OK;


    switch (enProcDire)
    {
        case PPPC_PROC_DL_NODE:

            PPPC_DlDequeueProc();

            break;

        case PPPC_PROC_UL_NODE:

            ulRet = PPPC_UlDequeueProc();

            break;

        case PPPC_PROC_BY_STAMP:

            /* stampֵԽ���ʾ���Խ�� */
            if (ulDlStamp >= ulUlStamp)
            {
                (*pulPppcUlCallCnt)++;
                ulRet = PPPC_UlDequeueProc();
            }
            else
            {
                *pulPppcUlCallCnt = 0;
                PPPC_DlDequeueProc();
            }

            break;

        default:

            PPPC_WARNING_LOG3("Invalid direction!\r\n",
                enProcDire, ulDlStamp, ulUlStamp);

            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : PPPC_DequeueProc
 ��������  : �����б��İ����ʱ��˳�����
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_DequeueProc(PPPC_PROC_LINK_DIRECTION_ENUM_UINT16 enProcDire)
{
    TTF_LINK_ST                        *pstDlLink;
    TTF_LINK_ST                        *pstUlLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    VOS_UINT32                          ulDlStamp;
    VOS_UINT32                          ulUlStamp;
#if (FEATURE_OFF == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT32                          ulTimerLoop     = 0;
    VOS_UINT32                          ulDelayNoteLoop = 0;
#endif
    VOS_UINT32                          ulRet           = VOS_OK;
    /* ���������������ô��� */
    VOS_UINT32                          ulPppcUlCallCnt = 0;

    pstDlLink       = &g_stPppDlLink;
    pstUlLink       = &g_stPppUlLink;


    for (;;)
    {
        ulRet = VOS_OK;

#if (FEATURE_OFF == FEATURE_HARDWARE_HDLC_ON_CCPU)

        /* ��������ﵽ����ʱ��ʱ�����˳�PPPC���� */
        if (ulTimerLoop >= PPPC_MAX_NOTIFY_PPPC_PROC_CNT)
        {
            if ((VOS_NULL_PTR == g_hReachMaxProcTimer) && (PS_TRUE == g_enIsReachTimeout))
            {
                (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_hReachMaxProcTimer, MSPS_PID_PPPC,
                    PPPC_REACH_MAX_PROC_TIMER_AWAKE_LEN, 0, PPPC_AWAKE_SELF_REACH_MAX_PROC_TIMER,
                    VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
                g_enIsReachTimeout = PS_FALSE;
            }

            break;
        }

        /* ��������ﵽ����ʱ����ʱ�����ֹPPPCһֱռ��CPU */
        if (ulDelayNoteLoop >= PPPC_MAX_NOTIFY_PPPC_DELAY_CNT)
        {
            VOS_TaskDelay(1);
            ulDelayNoteLoop = 0;
        }

        ulTimerLoop++;
        ulDelayNoteLoop++;

        /* ������װʱ��һ��NODE������������20��TTF�ڴ棬���������100ʱ�����ȴ������� */
        if (pstDlLink->ulCnt > PPPC_MAX_DL_NODE_CNT)
        {
            /* ���ж�����ȴ�������ʱǿ�ƴ������ж��� */
            PPPC_DlDequeueProc();
            continue;
        }
#else
        /* HDLCӲ�����װʱ��һ��NODE���������1��TTF�ڴ棬���������1000ʱ�����ȴ������� */
        if (pstDlLink->ulCnt > PPPC_MAX_DL_NODE_CNT * 10)
        {
            /* ���ж�����ȴ�������ʱǿ�ƴ������ж��� */
            PPPC_DlDequeueProc();
            continue;
        }
#endif

        if (ulPppcUlCallCnt > PPPC_UL_CONTINUOUS_MAX_CALL_CNT)
        {
            /* �����������ô�������ʱǿ�ƴ������ж��� */
            ulPppcUlCallCnt = 0;
            PPPC_DlDequeueProc();
            continue;
        }

        pstDlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlLink);
        pstUlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlLink);

        if ((VOS_NULL_PTR == pstDlNode) && (VOS_NULL_PTR == pstUlNode))
        {
            /* �����ж��ж�Ϊ�յ�ʱ���˳�ѭ�� */
            PPPC_INFO_LOG("PPP DL and UL Queue is Empty!\r\n");
            break;
        }
        else if ((VOS_NULL_PTR != pstDlNode) && (VOS_NULL_PTR != pstUlNode))
        {
            ulDlStamp   = pstDlNode->ulTimeStamp;
            ulUlStamp   = pstUlNode->ulTimeStamp;

            ulRet = PPPC_ProcLinkNodeByDirection(ulDlStamp, ulUlStamp,
                enProcDire, &ulPppcUlCallCnt);
        }
        else if (VOS_NULL_PTR != pstDlNode)
        {
            /* ֻ�����ж����нڵ� */
            PPPC_DlDequeueProc();
        }
        else
        {
            /* ֻ�����ж����нڵ� */
            ulRet = PPPC_UlDequeueProc();
        }

        if (VOS_OK != ulRet)
        {
            break;
        }
    }


    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_AwakeSelfProcUlDataTimeoutProc
 ��������  : ���ڴ治��ʱPPPCÿ300ms�����Լ���������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_AwakeSelfProcUlDataTimeoutProc(VOS_VOID)
{
    PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_TracePackets
 ��������  : PPPCģ�鱨�ĸ���
 �������  : CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo
             TTF_MEM_ST                         *pstTtfMem
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��16��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_TracePackets
(
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo,
    TTF_MEM_ST                         *pstTtfMem
)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnTrace = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;


    /* ��ά�ɲ� */
    if ((VOS_NULL_PTR != pstMntnInfo) && (VOS_NULL_PTR != pstTtfMem))
    {
        if (VOS_NULL_PTR != pstTtfMem->pData)
        {
            ulDataLen   = pstMntnInfo->ulLength;

            pstMntnTrace = (CTTF_PPPC_TRACE_DATA_STRU *)PPP_Malloc(
                           PPPC_OM_TRANS_DATA_OFFSET_LEN + ulDataLen);
            if (VOS_NULL_PTR != pstMntnTrace)
            {
                PS_MEM_SET(pstMntnTrace, 0, PPPC_OM_TRANS_DATA_OFFSET_LEN + ulDataLen);
                PS_MEM_CPY(pstMntnTrace, pstMntnInfo, PPPC_OM_TRANS_DATA_OFFSET_LEN);

                (VOID)PS_MEM_CPY(pstMntnTrace->aucValue, pstTtfMem->pData, ulDataLen);

                PPP_MNTN_TRACE_MSG(pstMntnTrace);

                PPP_Free(pstMntnTrace);

                pstMntnTrace = VOS_NULL_PTR;
            }
        }
    }
    (VOS_VOID)pstMntnTrace;
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_CheckRlpPacketsAndFreeMem
 ��������  : 1Xģʽ���PPPCģ���յ�RLP�����б��Ķ�����Ч��
 �������  : pstPackets          PPP����
 �������  : ��
 �� �� ֵ  : VOS_ERR or VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��24��
    ��    ��   : c001114540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_1X_CheckRlpPacketsAndFreeMem
(
    CTTF_1X_RLP_PPP_DELIVER_DATA_STRU  *pstPackets
)
{
    VOS_UINT32                          ulLoop;

    /* ��ָ���� */
    if (VOS_NULL_PTR == pstPackets)
    {
        PPPC_WARNING_LOG("Null Pointer");

        return VOS_ERR;
    }

    /* ��������Ϊ0 */
    if (0 == pstPackets->ucSduCount)
    {
        PPPC_WARNING_LOG("SduCount is 0");

        return VOS_ERR;
    }

    /* ���������쳣 */
    if (pstPackets->ucSduCount > CTTF_1X_RLP_PPP_MAX_SDU_COUNT)
    {
        PPPC_WARNING_LOG1("SduCount is %d", pstPackets->ucSduCount);

        for (ulLoop = 0; ulLoop < CTTF_1X_RLP_PPP_MAX_SDU_COUNT; ++ulLoop)
        {
            if (VOS_NULL_PTR != pstPackets->astDeliverSdus[ulLoop].pstSdu)
            {
                TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);
            }
        }

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_PushRlpPacketsEvent
 ��������  : 1XģʽPPPCģ���յ�RLP�����б������
 �������  : pstPackets          PPP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��23��
    ��    ��   : c001114540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_PushRlpPacketsEvent(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    CDS_CDMA_1X_TRANS_DATA_STRU         stPppSdu;
    VOS_UINT32                          ulLoop;


    if (VOS_OK != PPPC_1X_CheckRlpPacketsAndFreeMem(pstPackets))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return VOS_ERR;
    }

    /* ������м�ģʽ��ֱ�ӵ���CDS�ӿ�͸������ */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        stPppSdu.ucPdnId = pstPackets->ucPdnId;
        for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ++ulLoop)
        {
            /* ��CDS�ж�pstPackets->astDeliverSdus[ulLoop].pstSdu�Ƿ�ΪVOS_NULL_PTR */
            stPppSdu.ulSduLen   = pstPackets->astDeliverSdus[ulLoop].ulSduLen;
            stPppSdu.pstSdu     = pstPackets->astDeliverSdus[ulLoop].pstSdu;
            CDS_CDMA_1X_DL_DataInd(&stPppSdu, g_stPppContext.enModemId);

        }
        CDS_CDMA_WakeupCds();

        return VOS_OK;
    }

    /* �����б��ļ������ */
    PPPC_1X_DlEnqueueData(pstPackets);

    g_stPppcDataQueueStats.ul1xDlFrameRcvCnt += pstPackets->ucSduCount;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_CheckRpaPackets
 ��������  : HRPDģʽ���PPPCģ���յ�RPA�����б��Ķ�����Ч��
 �������  : pstPppSdu          PPP����
 �������  : ��
 �� �� ֵ  : VOS_ERR or VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��16��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HRPD_CheckRpaPackets
(
    RLP_PPP_HRPD_TRANS_DATA_STRU       *pstPppSdu
)
{
    /* ��ָ���� */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* ����TTF�ڴ�Ϊ�շ��ش��� */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* ����֡��Ϊ0���ش��� */
    if (0 == pstPppSdu->ulSduLen)
    {
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_IsPacketByPass
 ��������  : HRPD/eHRPDģʽRLP���б����Ƿ�͸����CDS,���͸�RN�ı���Ҫ�ݽ���PPP 0,
             Ȼ���ж��Ƿ����м�ģʽ,�м�ģʽ͸��,����ģʽPPPC�Լ�����
 �������  : ucStreamNum      ����,�����жϱ����Ƿ��Ƿ��͸�RN��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��8��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_HRPD_IsPacketByPass(VOS_UINT8 ucStreamNum)
{
    VOS_UINT32                          ulRet;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;


    ulRet = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, ucStreamNum);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Get app type fail!\r\n", ucStreamNum);
        return PS_FALSE;
    }

    /* �����Ӧ���а󶨵���RN,�򲻹����м�ģʽ��������ģʽ���Ķ�ҪPPPC�Լ����� */
    if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN == enAppType)
        || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_RN == enAppType)
        || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_RN == enAppType))
    {
        return PS_FALSE;
    }

    /* ����󶨵Ĳ���RN,����Ҫ�ж��м�ģʽ,�������͸�� */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : PPP_HRPD_DL_DataInd
 ��������  : HRPD/eHRPDģʽRLP���б��ķ��͵�PPPC
 �������  : pstPppSdu      ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��1��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_HRPD_DL_DataInd(RLP_PPP_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    CDS_CDMA_HRPD_TRANS_DATA_STRU       stPppData;
    VOS_UINT32                          ulMinPppMntnLen;
    PS_BOOL_ENUM_UINT8                  enIsByPass;


    if (VOS_OK != PPPC_HRPD_CheckRpaPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    /* ��ά�ɲ� */
    PS_MEM_SET(&g_stPppRlpMntnInfo, 0, sizeof(g_stPppRlpMntnInfo));
    pstMntnInfo     = &g_stPppRlpMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);

    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = CTTF_PID_HRPD_FPA;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_RCV_DL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucStreamNum     = pstPppSdu->ucStreamNumber;
    pstMntnInfo->usHigherLayerProtocol  = pstPppSdu->ucHigherLayerProtocol;
    pstMntnInfo->ucNumReservLabels      = pstPppSdu->ucNumReservLabels;
    PS_MEM_CPY(pstMntnInfo->aucReservLabel, pstPppSdu->aucReservLabel, CTTF_HRPD_PA_MAX_NUM_RESERV_LABELS);
    pstMntnInfo->enRatMode       = PPPC_GetRatMode();
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);
    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    enIsByPass = PPPC_HRPD_IsPacketByPass(pstPppSdu->ucStreamNumber);
    if (PS_TRUE == enIsByPass)
    {
        stPppData.ucPdnId  = 1;
        stPppData.ulSduLen = pstPppSdu->ulSduLen;
        stPppData.pstSdu   = pstPppSdu->pstSdu;
        pstPppSdu->pstSdu  = VOS_NULL_PTR;
        CDS_CDMA_HRPD_DL_DataInd(&stPppData, g_stPppContext.enModemId);

        CDS_CDMA_WakeupCds();

        return;
    }

    /* �����б��ļ������ */
    PPPC_HRPD_DlEnqueueData(pstPppSdu);

    g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_1X_CheckCdsPackets
 ��������  : 1Xģʽ���PPPCģ���յ�CDS�����б��Ķ�����Ч��
 �������  : pstPppSdu          PPP����
 �������  : ��
 �� �� ֵ  : VOS_ERR or VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��16��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_1X_CheckCdsPackets
(
    const CDS_CDMA_1X_TRANS_DATA_STRU  *pstPppSdu
)
{
    TTF_MEM_ST                         *pstTTFMem;


    /* ��ָ���� */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* ����TTF�ڴ�Ϊ�շ��ش��� */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* ����֡��Ϊ0���ش��� */
    if (0 == pstPppSdu->ulSduLen)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_1X_PullPacketEvent
 ��������  : 1Xģʽ��PPPģ���յ�CDS�����б�����Ӵ���
 �������  : pstPppSdu        PPP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_1X_PullPacketEvent(const CDS_CDMA_1X_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stTmpSdu;
    VOS_UINT32                          ulMinPppMntnLen;
    TTF_MEM_ST                         *pstTTFMem;
    VOS_UINT32                          ulRet   = VOS_OK;
    VOS_UINT8                           ucPppId = 0;

    if (VOS_OK != PPPC_1X_CheckCdsPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    ulRet   = PPPC_GetPppIdByPdn(pstPppSdu->ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", pstPppSdu->ucPdnId, ucPppId);
        return;
    }

    /* ��ά�ɲ� */
    /* 1XģʽPPPCģ���յ�CDS�����б��ĸ��� */
    PS_MEM_SET(&g_stPppCdsMntnInfo, 0, sizeof(g_stPppCdsMntnInfo));
    pstMntnInfo     = &g_stPppCdsMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);
    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = UEPS_PID_CDS;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_FRAME_RCV_UL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucPdnId         = pstPppSdu->ucPdnId;
    pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);

    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    /* ������м�ģʽ��ֱ�ӵ���RLP�ӿ�͸������ */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        PS_MEM_SET(&stTmpSdu, 0, sizeof(PPP_RLP_1X_TRANS_DATA_STRU));
        stTmpSdu.ucPdnId            = pstPppSdu->ucPdnId;
        stTmpSdu.ulSduLen           = pstPppSdu->ulSduLen;
        stTmpSdu.pstSdu             = pstPppSdu->pstSdu;
        stTmpSdu.enIpDataType       = IP_DATA_TYPE_NULL;
        stTmpSdu.ucTotalPppFrgmt    = 1;
        stTmpSdu.ucCurrPppFrgmt     = 0;

        CTTF_1X_RLP_ReverseLink_DataReq(&stTmpSdu);

        CTTF_1X_RLP_ReverseLink_TriggerDataProc();

        PPPC_INFO_LOG("The Dial Mode is relay!\n");

        return;
    }

    /* TODO comment out for UT*/
#if 0
    /* ���PdnId */
    if (pstPppSdu->ucPdnId != g_stPppContext.ucPdnId)
    {
        TTF_MemFree(MSPS_PID_PPPC, pstPppSdu->pstSdu);
        PPPC_WARNING_LOG("Pdn Id is error!");
        return;
    }
#endif

    /* �����б��ļ������ */
    PPPC_1X_UlEnqueueData(pstPppSdu);


    g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_CheckCdsPackets
 ��������  : HRPDģʽ���PPPCģ���յ�CDS�����б��Ķ�����Ч��
 �������  : pstPppSdu          PPP����
 �������  : ��
 �� �� ֵ  : VOS_ERR or VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��16��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_HRPD_CheckCdsPackets
(
    const CDS_CDMA_HRPD_TRANS_DATA_STRU    *pstPppSdu
)
{
    TTF_MEM_ST                         *pstTTFMem;


    /* ��ָ���� */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* ����TTF�ڴ�Ϊ�շ��ش��� */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* ����֡��Ϊ0���ش��� */
    if (0 == pstPppSdu->ulSduLen)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_PullPacketEvent
 ��������  : HRPDģʽ��PPPģ���յ�CDS�����б�����Ӵ���
 �������  : pstPppSdu        PPP����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HRPD_PullPacketEvent(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType;
    VOS_UINT32                          ulMinPppMntnLen;
    TTF_MEM_ST                         *pstTTFMem;
    VOS_UINT32                          ulRet   = VOS_OK;
    VOS_UINT8                           ucPppId = 0;


    if (VOS_OK != PPPC_HRPD_CheckCdsPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    ulRet   = PPPC_GetPppIdByPdn(pstPppSdu->ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", pstPppSdu->ucPdnId, ucPppId);
        return;
    }

    /* ��ά�ɲ� */
    /* HRPDģʽPPPCģ���յ�CDS�����б��ĸ��� */
    PS_MEM_SET(&g_stPppCdsMntnInfo, 0, sizeof(g_stPppCdsMntnInfo));
    pstMntnInfo     = &g_stPppCdsMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MIN_MNTN_INFO_LEN);
    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = UEPS_PID_CDS;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_RCV_UL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucPdnId         = pstPppSdu->ucPdnId;
    pstMntnInfo->enRatMode       = PPPC_GetRatMode();
    pstMntnInfo->ucStreamNum     = PPPC_HRPD_GetStreamNumber(1);
    /* ��ȡstream2�İ�Ӧ����Ϣ */
    enAppType                    = g_stPppContext.stHrpdContext.aenApplicationType[1];
    pstMntnInfo->ucNumReservLabels = 1;
    pstMntnInfo->aucReservLabel[0] = PPPC_HRPD_PaAgentGetResvLabel(enAppType);
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);

    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    /* ������м�ģʽ��ֱ�ӵ���RLP�ӿ�͸������ */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        stHrpdSdu.ucReservationLabel    = PPPC_HRPD_PA_BEST_EFFORT;

        /* CDS���ݹ��������ݱ�Ȼ��Ҫͨ��stream sn���͵������,��˲�����Ϊҵ��ppp id */
        stHrpdSdu.ucStreamNumber        = PPPC_HRPD_GetStreamNumber(1);
        stHrpdSdu.ulSduLen              = pstPppSdu->ulSduLen;
        stHrpdSdu.pstSdu                = pstPppSdu->pstSdu;
        stHrpdSdu.enStreamMode          = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;
        stHrpdSdu.enIpDataType          = IP_DATA_TYPE_NULL;
        stHrpdSdu.ucTotalPppFrgmt       = 1;
        stHrpdSdu.ucCurrPppFrgmt        = 0;

        CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

        return;
    }

    /* �����б��ļ������ */
    PPPC_HRPD_UlEnqueueData(pstPppSdu);


    g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendTafOrHsmReconnInd
 ��������  : Send reconnection indication msg to Taf or Hsm when PPP finds no link.
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-24
    ��    ��   : d00314740
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendTafOrHsmReconnInd
(
    VOS_UINT8                           ucPdnId
)
{
    PPP_APS_RECONN_IND_STRU            *pstReconnInd;

    pstReconnInd    = (PPP_APS_RECONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(PPP_APS_RECONN_IND_STRU));

    if (VOS_NULL_PTR == pstReconnInd)
    {
        PPPC_WARNING_LOG1("Alloc pstReconnInd Mem Fail! PppId:", ucPdnId);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstReconnInd + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(PPP_APS_RECONN_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstReconnInd->ulReceiverPid     = g_stPppContext.ulSendPid;
    pstReconnInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstReconnInd->enMsgId           = ID_PPP_APS_RECONN_IND;
    pstReconnInd->usOpId            = 0;
    pstReconnInd->ucPdnId           = ucPdnId;

    /* Send reconnection ind msg */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstReconnInd))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_PPP_APS_RECONN_IND msg fail! PdnId:%d\n", ucPdnId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendEhsmReconnInd
 ��������  : Send reconnection indication msg to Ehsm when PPP finds no link.
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-24
    ��    ��   : d00314740
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendEhsmReconnInd(VOS_VOID)
{
    CTTF_CNAS_EHRPD_RECONN_IND_STRU    *pstReconnInd;

    pstReconnInd    = (CTTF_CNAS_EHRPD_RECONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_RECONN_IND_STRU));

    if (VOS_NULL_PTR == pstReconnInd)
    {
        PPPC_WARNING_LOG("Alloc pstReconnInd Mem Fail!");

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstReconnInd + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(CTTF_CNAS_EHRPD_RECONN_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstReconnInd->ulReceiverPid     = g_stPppContext.ulSendPid;
    pstReconnInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstReconnInd->enMsgId           = ID_CTTF_CNAS_EHRPD_RECONN_IND;
    pstReconnInd->usOpId            = 0;

    /* Send reconnection ind msg */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstReconnInd))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_RECONN_IND msg fail! PdnId:%d\n");
    }

    return;
}
#if (PPPC_FEATURE_OFF == PPPC_FEATURE_MULTI_MODEM)
/*****************************************************************************
 �� �� ��  : I1_TAF_APS_GetPppLinkStatus
 ��������  : �����ڶ�modemʱ��׮Modem1��ȡ��·״̬����ֹ������ʱ����ʧ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-12-18
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 I1_TAF_APS_GetPppLinkStatus(VOS_VOID)
{
    PPPC_WARNING_LOG("Do not support multi modem,modem1!");

    return TAF_APS_PPP_LINK_STATUS_BUTT;
}
#endif

#if (PPPC_FEATURE_OFF == PPPC_FEATURE_MODEM_2)
/*****************************************************************************
 �� �� ��  : I2_TAF_APS_GetPppLinkStatus
 ��������  : �����ڶ�modemʱ��׮Modem2��ȡ��·״̬����ֹ������ʱ����ʧ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-12-18
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 I2_TAF_APS_GetPppLinkStatus(VOS_VOID)
{
    PPPC_WARNING_LOG("Do not support multi modem,modem2!");

    return TAF_APS_PPP_LINK_STATUS_BUTT;
}

#endif
/*****************************************************************************
 �� �� ��  : PPPC_GetLinkStatus
 ��������  : ��ȡ��·״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_APS_PPP_LINK_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-12-18
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_APS_PPP_LINK_STATUS_ENUM_UINT8 PPPC_GetLinkStatus(VOS_VOID)
{
    TAF_APS_PPP_LINK_STATUS_ENUM_UINT8  enLinkStatus;

    if (MODEM_ID_0 == g_stPppContext.enModemId)
    {
        enLinkStatus = TAF_APS_GetPppLinkStatus();
    }
    else if (MODEM_ID_1 == g_stPppContext.enModemId)
    {
        enLinkStatus = I1_TAF_APS_GetPppLinkStatus();
    }
    else
    {
        enLinkStatus = I2_TAF_APS_GetPppLinkStatus();
    }

    return enLinkStatus;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetConnectionStatus
 ��������  : ��ȡconnection��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : connection״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-28
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_UINT8 PPPC_GetConnectionStatus(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.enConnectionStatus;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendRpaReConnInd
 ��������  : ��PA����conneciton�ؽ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-28
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendRpaReConnReq(VOS_VOID)
{
    CTTF_HRPD_PPP_PA_RECONN_REQ_STRU   *pstPppReConnReq;

    pstPppReConnReq = (CTTF_HRPD_PPP_PA_RECONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_HRPD_PPP_PA_RECONN_REQ_STRU));
    if (VOS_NULL_PTR == pstPppReConnReq)
    {
        PPPC_ERROR_LOG("Alloc ID_CTTF_HRPD_PPP_PA_RECONN_REQ Mem Fail!\r\n");
        return;
    }

    pstPppReConnReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppReConnReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppReConnReq->enMsgId        = ID_CTTF_HRPD_PPP_PA_RECONN_REQ;
    pstPppReConnReq->usOpId         = 0;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppReConnReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_HRPD_PPP_PA_RECONN_REQ msg fail!");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPPC_ULSendNegoFrame
 ��������  : ���з���PPPЭ�̱���
 �������  : pstMBuf    PPPЭ������
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-05
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_ULSendNegoFrame(PMBUF_S *pstMBuf, VOS_UINT32 ulRPIndex)
{
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTotalLen;
    VOS_UINT32                          ulMinPppMntnLen;
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    VOS_UINT8                           ucPdnId = 0;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;


    /* �ڲ�����pstMBuf��Ϊ�� */

    ulTotalLen  = (VOS_UINT32)pstMBuf->ulTotalDataLength;

    /* Э�̱��Ľ϶̣������ο�����ֻ�追��һ�Σ��ֽ���С��1500Byte */
    pstTtfMem = PPPC_AdapterMBuftoTtfMemory(pstMBuf, TTF_MEM_POOL_ID_UL_DATA, 0, pstMBuf->ulTotalDataLength);
    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_894);
        /* ���ݿ�����TtfMemoryʧ��Ҳ��Ҫ�ͷ�MBUF */
        PMBUF_Destroy(pstMBuf);
        return VOS_ERR;
    }

    PMBUF_Destroy(pstMBuf);

    enRatMode   = PPPC_GetRatMode();

    if (PPPC_RAT_MODE_1X == enRatMode)
    {
        ulRet     = PPPC_1X_GetPdnId((VOS_UINT8)ulRPIndex, &ucPdnId);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get PDN Id Fail! ulRPIndex:%d, ucPdnId:%d\r\n", ulRPIndex, ucPdnId);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
            return VOS_ERR;
        }

        /* �������ݱ��ķ��͵�RLP */
        stRlpSdu.ucPdnId            = ucPdnId;
        stRlpSdu.enIpDataType       = IP_DATA_TYPE_NULL;
        stRlpSdu.ucTotalPppFrgmt    = 1;
        stRlpSdu.ucCurrPppFrgmt     = 0;
        stRlpSdu.ulSduLen           = ulTotalLen;
        stRlpSdu.pstSdu             = pstTtfMem;

        /* ��ά�ɲ� */
        /* 1XģʽPPPCģ�鷢�͵�RLP�����б��ĸ��� */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(ulTotalLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = MSPS_PID_1X_RRLP;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_NEGO_UL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stRlpSdu.ucPdnId;
        pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stRlpSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        /* 1x ����CNAS�����󣬵�����pppЭ��ʱ�������ǰ��·�����ڣ�����CNAS����ReconnectInd */
        /* 1x ����CNAS�����󣬵�����pppЭ��ʱ�������ǰ��·������, ����ǰ��Э�̱��Ķ����� */
        if (TAF_APS_PPP_LINK_NOT_EXISTED == PPPC_GetLinkStatus())
        {
            PPPC_WARNING_LOG("Nego when tch not exist, 1x");

            PPPC_WARNING_LOG("Nego for not ACCESS_AUTH when link not exists, 1x");
            TTF_MemFree(MSPS_PID_PPPC, stRlpSdu.pstSdu);

            /* ��CNAS����ReconnectReq */
            PPPC_SendTafOrHsmReconnInd(ucPdnId);
        }
        else
        {
            CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

            /* ����RLP�������б��� */
            CTTF_1X_RLP_ReverseLink_TriggerDataProc();

            /* ����Э�̱��ļ�����1 */
            g_stPppcDataQueueStats.ul1xUlNegoSndCnt++;
        }
    }
    else
    {
        /* ��ȡstream2��Ӧ�ð���Ϣ */
        stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber((VOS_UINT8)ulRPIndex);
        ulRet = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, stHrpdSdu.ucStreamNumber);

        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get App Type Fail! ulRPIndex, StreamNumber",
                ulRPIndex, stHrpdSdu.ucStreamNumber);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

            return VOS_ERR;
        }

        stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
        stHrpdSdu.ulSduLen          = ulTotalLen;
        stHrpdSdu.pstSdu            = pstTtfMem;
        stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;
        stHrpdSdu.enIpDataType      = IP_DATA_TYPE_NULL;
        stHrpdSdu.ucTotalPppFrgmt   = 1;
        stHrpdSdu.ucCurrPppFrgmt    = 0;

        /* ��ά�ɲ� */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(ulTotalLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = CTTF_PID_HRPD_RPA;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_NEGO_UL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucStreamNum     = stHrpdSdu.ucStreamNumber;
        pstMntnInfo->ucNumReservLabels = 1;
        pstMntnInfo->aucReservLabel[0] = stHrpdSdu.ucReservationLabel;
        pstMntnInfo->enRatMode       = PPPC_GetRatMode();
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stHrpdSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        /* ����CNAS�����󣬵�����pppЭ��ʱ�������ǰ��·�����ڣ�����CNAS����ReconnectInd */
        /* ����CNAS�����󣬵�����pppЭ��ʱ�������ǰ��·������, ���ǽ����Ȩ������ǰ��Э�̱��Ķ���;
            �ǽ����Ȩ, �������� */
        if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ulRPIndex)
        {
            /* ���connection�����ڣ���PA����connection�ؽ���Ϣ */
            if (CTTF_HRPD_PA_CONNECTION_NOT_EXIST_ENUM == PPPC_GetConnectionStatus())
            {
                TTF_MemFree(MSPS_PID_PPPC, stHrpdSdu.pstSdu);
                PPPC_WARNING_LOG("Nego for ACCESS_AUTH when Connection not exists");

                PPPC_SendRpaReConnReq();
            }
            else
            {
                CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                /* ����Э�̱��ļ�����1 */
                g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
            }
        }
        else
        {
            if (PPPC_RAT_MODE_HRPD == enRatMode)
            {
                if (TAF_APS_PPP_LINK_NOT_EXISTED == PPPC_GetLinkStatus())
                {
                    PPPC_WARNING_LOG("Nego for not ACCESS_AUTH when link not exists, HRPD");
                    TTF_MemFree(MSPS_PID_PPPC, stHrpdSdu.pstSdu);

                    ulRet     = PPPC_1XHrpdGetPdnId((VOS_UINT8)ulRPIndex, &ucPdnId);
                    if (VOS_OK != ulRet)
                    {
                        PPPC_WARNING_LOG2("Get PDN Id Fail! ulRPIndex:%d, ucPdnId:%d\r\n", ulRPIndex, ucPdnId);
                        return VOS_ERR;
                    }

                    /* ��CNAS����ReconnectReq, HRPD */
                    PPPC_SendTafOrHsmReconnInd(ucPdnId);
                }
                else
                {
                    CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                    /* ����Э�̱��ļ�����1 */
                    g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
                }
            }
            else
            {
                /* EHRPD */
                if (CNAS_CTTF_EHRPD_LINK_NOT_EXISTED == CNAS_EHSM_GetPdnLinkStatus())
                {
                    PPPC_WARNING_LOG("Nego for not ACCESS_AUTH when link not exists, EHRPD");
                    TTF_MemFree(MSPS_PID_PPPC, stHrpdSdu.pstSdu);

                    /* ��CNAS����ReconnectReq, EHRPD */
                    PPPC_SendEhsmReconnInd();
                }
                else
                {
                    CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

                    /* ����Э�̱��ļ�����1 */
                    g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
                }
            }
        }
    }

    /* ����MAX PPP Inactive Timer */
    PPPC_StartPppInactiveTimer((VOS_UINT8)ulRPIndex);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_RcvCdsUlFrame
 ��������  : �յ�CDS���б��Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_RcvCdsUlFrame
(
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstTtfMemory,
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo,
    VOS_UINT8                           ucStreamNum
)
{
    TTF_MEM_ST                         *pstData;
    VOS_INT32                           lTotalLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRlpSduLen = 0;
    VOS_UINT32                          ulAccmValue = 0;
    VOS_UINT32                          ulAsynDataLen = 0;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucPppId  = 0;
    PPPINFO_S                          *pstPppInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;
    VOS_UINT8                          *pucDstDataPtr;
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;
    VOS_UINT32                          ulLoop;


    if (VOS_NULL_PTR == pstTtfMemory)
    {
        PPPC_WARNING_LOG2("Input para is null!\r\n", ucPdnId, enRatMode);
        return VOS_ERR;
    }

    if (PPPC_RAT_MODE_BUTT <= enRatMode)
    {
        PPPC_WARNING_LOG2("Invalid Rat Mode", ucPdnId, enRatMode);
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);
        return VOS_ERR;
    }

    ulRet       = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_895);
        PPPC_WARNING_LOG1("Get Ppp Id Fail!\r\n", ucPppId);
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);
        return VOS_ERR;
    }

    /* ���������Ip�����������ͣ���rlpʹ�� */
    enIpDataType    = TTF_ParseIpDataType(MSPS_PID_PPPC, pstTtfMemory);

    pstPppInfo                  = &g_astPppPool[ucPppId];
    ulAccmValue    = (pstPppInfo->ulLocalAccm | pstPppInfo->ulRemoteAccm);

    /* ���ý����������ݺ�����ֱ��� */
    ulRet   = FWD_PppEncap(ucPdnId, pstTtfMemory->pData, pstTtfMemory->usUsed,
                ulAccmValue, &ulAsynDataLen);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_897);
        PPPC_WARNING_LOG2("Encap PPP Fail!\r\n", ulAsynDataLen, ulRet);

        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);

        return VOS_ERR;
    }

    /* �����Ѵ�����Ͽ����ͷ��ڴ� */
    TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);

    lTotalLen  = (VOS_INT32)ulAsynDataLen;
    pucDstDataPtr   = PPP_GetUlEncapDataPtr();

    /* TCP ACK ��ǰ��ز�����ֵ */
    stRlpSdu.enIpDataType       = enIpDataType;
    stRlpSdu.ucTotalPppFrgmt    = (VOS_UINT8)((lTotalLen / PPPC_MAX_UL_ENCAP_LEN) + 1);
    stHrpdSdu.enIpDataType      = enIpDataType;
    stHrpdSdu.ucTotalPppFrgmt   = (VOS_UINT8)((lTotalLen / PPPC_MAX_UL_ENCAP_LEN) + 1);

    enAppType = CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_BUTT;

    if ((PPPC_RAT_MODE_HRPD == enRatMode) || (PPPC_RAT_MODE_EHRPD == enRatMode))
    {
        /* ��ȡstream2��Ӧ�ð���Ϣ */
        ulRet = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, ucStreamNum);

        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get App Type Fail!", ucStreamNum, ucPppId);

            /* �ͷ��ڴ� */
            for (ulLoop = 0; ulLoop < PPPC_MAX_UL_ENCAP_MEM_NUM; ulLoop++)
            {
                if (VOS_NULL_PTR != g_astUlEncapMem[ulLoop].pstDataPtr)
                {
                    TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[ulLoop].pstDataPtr);
                    g_astUlEncapMem[ulLoop].pstDataPtr = VOS_NULL_PTR;
                }
            }

            return VOS_ERR;
        }
    }

    /* �ӵ�һ�鿪ʼ������ */
    ulIndex   = 0;
    pstData   = g_astUlEncapMem[ulIndex].pstDataPtr;

    while ((lTotalLen > 0) && (ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM)
        && (pstData != VOS_NULL_PTR))
    {
        ulRlpSduLen     = (VOS_UINT32)PS_MIN(lTotalLen, PPPC_MAX_UL_ENCAP_LEN);

        (VOID)PS_MEM_CPY(pstData->pData, pucDstDataPtr, ulRlpSduLen);
        pstData->usUsed = (VOS_UINT16)ulRlpSduLen;

        if (PPPC_RAT_MODE_1X == enRatMode)
        {
            /* �������ݱ��ķ��͵�RLP */
            stRlpSdu.ucPdnId            = ucPdnId;
            stRlpSdu.ucCurrPppFrgmt     = (VOS_UINT8)ulIndex;
            stRlpSdu.ulSduLen           = ulRlpSduLen;
            stRlpSdu.pstSdu             = pstData;
            if (VOS_NULL_PTR != pstUlDataInfo)
            {
                PS_MEM_CPY(&(stRlpSdu.stUlDataInfo), pstUlDataInfo, sizeof(PS_DATA_EXT_INFO_STRU));
                PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataInfo);
            }

            CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

            /* ����IP�����ļ�����1 */
            g_stPppcDataQueueStats.ul1xUlIPDataSndCnt++;
        }
        else
        {
            /* CDS���ݹ��������ݱ�Ȼ��Ҫͨ��stream sn���͵������,��˲�����Ϊҵ��ppp id */
            stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber(1);
            stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
            stHrpdSdu.ulSduLen          = ulRlpSduLen;
            stHrpdSdu.pstSdu            = pstData;
            stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;
            stHrpdSdu.ucCurrPppFrgmt    = (VOS_UINT8)ulIndex;

            CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

            /* ����IP�����ļ�����1 */
            g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt++;
        }

        g_astUlEncapMem[ulIndex].enPtrIsUsed    = PS_FALSE;
        g_astUlEncapMem[ulIndex].pstDataPtr     = VOS_NULL_PTR;

        lTotalLen           -= (VOS_INT32)ulRlpSduLen;
        pucDstDataPtr       += ulRlpSduLen;
        ulIndex++;

        if (ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM)    /* ��ֹ����Խ�� */
        {
            pstData   = g_astUlEncapMem[ulIndex].pstDataPtr;
        }
    }

    if (PPPC_RAT_MODE_1X == enRatMode)
    {
        /* ����RLP�������б��� */
        CTTF_1X_RLP_ReverseLink_TriggerDataProc();
    }

    /* ����MAX PPP Inactive Timer */
    PPPC_StartPppInactiveTimer((VOS_UINT8)pstPppInfo->ulRPIndex);

    return VOS_OK;
}

/** **************************************************************************
  Generate high layer data info trace msg and send it.

  @param[in]    pstUlDataInfo   Pointer to struct containing high layer data info.

  @return   VOS_VOID
*/

VOS_VOID PPP_TraceDlHighLayerInfo
(
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
)
{
    PPPC_TRACE_HIGH_LAYER_INFO_STRU     stHighLayerInfoMsg;

    stHighLayerInfoMsg.ulSenderPid      = MSPS_PID_PPPC;
    stHighLayerInfoMsg.ulReceiverPid    = MSPS_PID_PPPC;
    stHighLayerInfoMsg.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stHighLayerInfoMsg.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stHighLayerInfoMsg.ulLength         = sizeof(PPPC_TRACE_HIGH_LAYER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stHighLayerInfoMsg.enMsgId          = ID_CTTF_1X_PPPC_TRACE_HIGH_LAYER_INFO_DL;
    PS_MEM_CPY(&(stHighLayerInfoMsg.stUlDataInfo), pstUlDataInfo, sizeof(PS_DATA_EXT_INFO_STRU));

    TTF_TRACE_MSG(&stHighLayerInfoMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_SendRlpDlDatatoCds
 ��������  : ���б��ķ��͵�CDS
 �������  : ucPdnId      ���غ�
             pstSynMBuf   MBUF��ʽ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPP_SendRlpDlDatatoCds
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
)
{
    CDS_CDMA_1X_TRANS_DATA_STRU         stPppSdu;
    PS_DATA_EXT_INFO_STRU               stDataInfo;
    CDS_CDMA_HRPD_TRANS_DATA_STRU       stHrpdSdu;
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    VOS_UINT32                          ulMinPppMntnLen;


    PPP_MemSet(&stPppSdu, 0, sizeof(stPppSdu));
    PPP_MemSet(&stHrpdSdu, 0, sizeof(stHrpdSdu));

    if (PPPC_RAT_MODE_1X == ucRatMode)
    {
        stPppSdu.ucPdnId    = ucPdnId;
        stPppSdu.ulSduLen   = pstData->usUsed;
        stPppSdu.pstSdu     = pstData;

        /* �����Ż�����ȡtrace */
        FWD_PppFillDataInfo(pstData->pData, &(stDataInfo));
        stDataInfo.usStartSN    = usStartSeq;
        stDataInfo.usEndSN      = usEndSeq;
        PPP_TraceDlHighLayerInfo(&(stDataInfo));

        /* ��ά�ɲ� */
        /* 1XģʽPPPCģ�鷢�͵�CDS�����б��ĸ��� */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(stPppSdu.ulSduLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = UEPS_PID_CDS;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_FRAME_SEND_DL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stPppSdu.ucPdnId;
        pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stPppSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CDS_CDMA_1X_DL_DataInd(&stPppSdu, g_stPppContext.enModemId);
        CDS_CDMA_WakeupCds();

        /* ���з���IP��������1 */
        g_stPppcDataQueueStats.ul1xDlIPDataSndCnt++;
    }
    else
    {
        stHrpdSdu.ucPdnId    = ucPdnId;
        stHrpdSdu.ulSduLen   = pstData->usUsed;
        stHrpdSdu.pstSdu     = pstData;

        /* ��ά�ɲ� */
        /* HRPDģʽPPPCģ�鷢�͵�CDS�����б��ĸ��� */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(stHrpdSdu.ulSduLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = UEPS_PID_CDS;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_SEND_DL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stHrpdSdu.ucPdnId;
        pstMntnInfo->enRatMode       = ucRatMode;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stHrpdSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CDS_CDMA_HRPD_DL_DataInd(&stHrpdSdu, g_stPppContext.enModemId);
        CDS_CDMA_WakeupCds();

        /* ���з���IP��������1 */
        g_stPppcDataQueueStats.ulHrpdDlIPDataSndCnt++;
    }

    return;
}


#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

/*****************************************************************************
 �� �� ��  : PPPC_ProcAsFrmDataInd
 ��������  : ��������֡����
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ProcAsFrmDataInd(struct MsgCB * pMsg)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstHdlcEnable;
    VOS_UINT16                               usPppId;
    VOS_UINT16                               usProtocol;
    TTF_MEM_ST                              *pstMem;


    pstHdlcEnable = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU*)pMsg;

    usPppId       = pstHdlcEnable->usPppId;
    usProtocol    = pstHdlcEnable->usProtocol;
    pstMem        = pstHdlcEnable->pstMem;


    PPPC_HDLC_HARD_ProcAsFrmPacket(usPppId, usProtocol, pstMem);

    return;
}

#endif


/*****************************************************************************
 �� �� ��  : PPPC_AwakeSelfReachMaxProcTimeoutProc
 ��������  : ����������ﵽ����ʱ,PPPCÿ��ʱ�����Լ���������������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_AwakeSelfReachMaxProcTimeoutProc(VOS_VOID)
{
    g_hReachMaxProcTimer = VOS_NULL_PTR;
    g_enIsReachTimeout   = PS_TRUE;
    PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_AccessAuthDelayTimeoutproc
 ��������  : PPPC�յ�PA�Ľ����Ȩ��Ϣʱ��ʱ5s�ȵ��յ�BSC��LCPЭ�̱��ĺ��ٴ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_AccessAuthDelayTimeoutproc()
{
    g_hAADelayTimer = VOS_NULL_PTR;

    /* Ϊ�˸�PA�ظ������ȨRESPONSE�����ý����Ȩ��־λ */
    PPPC_ChangeAccessAuthState(PS_TRUE, PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* ֪ͨPA�����������Ȩ */
    PPPC_HRPD_SendRpaAccessAuthRsp(CTTF_HRPD_PPP_NO_ACCESS_AUTH);

    /* �ָ������Ȩ��־λ */
    PPPC_ChangeAccessAuthState(PS_FALSE, PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* ���ó�ʼ�����Ȩ��־λ */
    PPPC_SetInitAccessAuthMode(PS_FALSE);

    /* �������û��Ĳ������� */
    /* ��ʱ��������Ҫ�������Ȩ��������Ȩ�ɹ���ͬ���� */
    PPPC_AccessAuthSuccProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_AccessAuthDelayProcTimeoutProc
 ��������  : �����Ȩ��ʱ������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_AccessAuthDelayProcTimeoutProc
(
    PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16 enActMode
)
{
    switch(enActMode)
    {
        case PPPC_ACCESS_AUTH_ACT_MODE_HRPD:

            if (VOS_NULL_PTR == g_astActHrpdTimer[0].pstMsgPtr)
            {
                PPPC_WARNING_LOG1("Invalid input ptr\r\n", enActMode);
                return;
            }

            PPPC_RespApsActFail((APS_PPP_ACT_REQ_STRU *)g_astActHrpdTimer[0].pstMsgPtr);

            PPP_Free(g_astActHrpdTimer[0].pstMsgPtr);
            g_astActHrpdTimer[0].pstMsgPtr       = VOS_NULL_PTR;
            g_astActHrpdTimer[0].hDelayProcTimer = VOS_NULL_PTR;

            break;

        case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH:

            if (VOS_NULL_PTR == g_astActHrpdTimer[1].pstMsgPtr)
            {
                PPPC_WARNING_LOG1("Invalid input ptr\r\n", enActMode);
                return;
            }

            PPPC_RespEhsmAttachFail((CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)g_astActHrpdTimer[1].pstMsgPtr);

            PPP_Free(g_astActHrpdTimer[1].pstMsgPtr);
            g_astActHrpdTimer[1].pstMsgPtr       = VOS_NULL_PTR;
            g_astActHrpdTimer[1].hDelayProcTimer = VOS_NULL_PTR;

            break;

        case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN:

            if (VOS_NULL_PTR == g_astActHrpdTimer[2].pstMsgPtr)
            {
                PPPC_WARNING_LOG1("Invalid input ptr\r\n", enActMode);
                return;
            }

            PPPC_RespEhsmPdnConnectFail((CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)g_astActHrpdTimer[2].pstMsgPtr);

            PPP_Free(g_astActHrpdTimer[2].pstMsgPtr);
            g_astActHrpdTimer[2].pstMsgPtr       = VOS_NULL_PTR;
            g_astActHrpdTimer[2].hDelayProcTimer = VOS_NULL_PTR;

            break;

        default:

            PPPC_WARNING_LOG1("Invalid rate mode\r\n", enActMode);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetDialMode
 ��������  : ��ȡ����ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��28��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 PPPC_GetDialMode(VOS_VOID)
{
    return g_stPppContext.enDialMode;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetDialMode
 ��������  : ���ò���ģʽ��ֻ֧���м̺�����ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��01��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SetDialMode(TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 enDialMode)
{
    g_stPppContext.enDialMode = enDialMode;
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetRatMode
 ��������  : ��ȡ��ǰģʽ��1X,HRPD����eHRPD
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PPPC_RAT_MODE_ENUM_UINT8 PPPC_GetRatMode(VOS_VOID)
{
    return g_stPppContext.enRatMode;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetRatMode
 ��������  : �趨��ǰģʽ1X,HRPD����eHRPD
 �������  : PPPC_RAT_MODE_ENUM_UINT8 enRatMode
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_SetRatMode(PPPC_RAT_MODE_ENUM_UINT8 enRatMode)
{
    g_stPppContext.enRatMode = enRatMode;
    return;
}


/*****************************************************************************
 �� �� ��  : PPPC_GetCurrentPdnId
 ��������  : ��ȡ��ǰ��PDN ID,�˽ӿڿ�����PPPЭ�̹�����ʹ��
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_GetCurrentPdnId(VOS_UINT8 *pucPdnId)
{
    PPPC_DATA_LINK_NODE_STRU           *pstApsCurrHeadNode  = VOS_NULL_PTR;
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode          = PPPC_RAT_MODE_BUTT;

    enRateMode  = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_BUTT >= enRateMode)
    {
        pstApsCurrHeadNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(
                    MSPS_PID_PPPC, &g_stApsCmdLink);

        if (VOS_NULL_PTR != pstApsCurrHeadNode)
        {
            *pucPdnId = pstApsCurrHeadNode->ucPdnId;

            return VOS_OK;
        }
        else
        {
            PPPC_WARNING_LOG("Node is null\r\n");
        }
    }
    else
    {
        /* Invalid rate mode */
        PPPC_WARNING_LOG1("Invalid rate mode!enRateMode\r\n", enRateMode);
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPPC_1X_GetPdnId
 ��������  : 1Xģʽ��ȡ��ǰ��PDN ID
 �������  : VOS_UINT8 ucPppId
 �������  : VOS_UINT8 *pucPdnId
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��27��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_1X_GetPdnId(VOS_UINT8 ucPppId, VOS_UINT8 *pucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucBit;


    pstPppContext   = &g_stPppContext;
    for (ucBit = 0; ucBit < A11_MAX_PDN_NUM; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucBit))
        {
            *pucPdnId = ucBit;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetServicePppId
 ��������  : ��ȡҵ��PPP Id
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��28��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_GetServicePppId(VOS_VOID)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT32                          ulIndex;


    pstPppContext   = &g_stPppContext;

    for (ulIndex = PPPC_PPP_ID_MIN; ulIndex <= PPPC_PPP_ID_MAX; ++ulIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, ulIndex))
        {
            break;
        }
    }

    /* ���ҵ��PPP ID����������Ĭ�Ϸ�����Сֵ1,��ǰҵ��PPP ID��ʵֻ����1 */
    if (PPPC_PPP_ID_MIN != ulIndex)
    {
        PPPC_WARNING_LOG1("PPP id invalid!", ulIndex);
        ulIndex = PPPC_PPP_ID_MIN;
    }

    return ulIndex;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetCurrentPppId
 ��������  : ��ȡPPP Id
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��27��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_GetCurrentPppId
(
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode,
    VOS_UINT8                           ucStreamNum,
    VOS_UINT8                          *pucPppId
)
{
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16  enAppType;
    VOS_UINT32                          ulRet;


    if (PPPC_RAT_MODE_1X == enRateMode)
    {
        *pucPppId   = (VOS_UINT8)PPPC_GetServicePppId();
    }
    else
    {
        ulRet   = PPPC_HRPD_GetAppTypeByStreamNum(&enAppType, ucStreamNum);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get app fail\r\n", enRateMode, ucStreamNum);
            return ulRet;
        }

        if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_RN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_RN == enAppType))
        {
            *pucPppId   = PPPC_PPP_ID_FOR_ACCESS_AUTH;
        }
        else if ((CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_SN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_MULTIFLOW_PACKET_SN == enAppType)
            || (CTTF_HRPD_PA_APPLICATION_TYPE_ENHANCED_MULTIFLOW_PACKET_SN == enAppType))
        {
            *pucPppId   = (VOS_UINT8)PPPC_GetServicePppId();
        }
        else
        {
            PPPC_WARNING_LOG2("Get invalid app type\r\n", enRateMode, ucStreamNum);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_1XHrpdGetPdnId
 ��������  : ����PPP Id��PDN ID֮���ӳ���ϵ��ȡPdn Id,ֻ��1X��HRPD����ʹ��,
             eHRPDģʽһ��PPP Id���Զ�Ӧ���PDN ID������ͨ�����ַ�ʽ��ȡ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_1XHrpdGetPdnId(VOS_UINT16 usPppId, VOS_UINT8 *pucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT32                          ulPdnIndex;


    pstPppContext   = &g_stPppContext;

    for (ulPdnIndex = 0; ulPdnIndex < A11_MAX_PDN_NUM; ulPdnIndex++)
    {
        if (0 != TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[usPppId], ulPdnIndex))
        {
            *pucPdnId = (VOS_UINT8)ulPdnIndex;

            return VOS_OK;
        }
    }

    PPP_DBG_ERR_CNT(PPP_PHERR_806);

    PPPC_WARNING_LOG1("Get Pdn Id Fail!ucPppId\r\n", usPppId);

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetPppIdByPdn
 ��������  : ����PPP Id��PDN Id֮���ӳ���ϵ��ȡPPP Id
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_GetPppIdByPdn(VOS_UINT8 ucPdnId, VOS_UINT8 *pucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdIndex;


    /* ���PDN id */
    pstPppContext   = &g_stPppContext;
    for (ucPppIdIndex = PPPC_PPP_ID_MIN; ucPppIdIndex <= PPPC_PPP_ID_MAX; ++ucPppIdIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppIdIndex], ucPdnId))
        {
            *pucPppId = ucPppIdIndex;
            if ((PPPC_PPP_ID_MIN != ucPppIdIndex) && (0 != ucPppIdIndex))
            {
                /* PPP ID����1��0ʱ�����쳣�� */
                PPPC_WARNING_LOG4("ucPppId %d,ucPdnId %d,ppp1 %d ppp0 %d\r\n",
                    ucPppIdIndex, ucPdnId, pstPppContext->aulPppIdMapPdnId[1], pstPppContext->aulPppIdMapPdnId[0]);
            }
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPPC_IsPdnIdUnique
 ��������  : �жϵ�ǰPDN ID�ǲ���Ψһ��
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��05��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_IsPdnIdUnique(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppId;
    VOS_UINT8                           ucBit;
    VOS_UINT8                           ucPdnNum = 0;


    if (VOS_OK != PPPC_GetPppIdByPdn(ucPdnId, &ucPppId))
    {
        return VOS_ERR;
    }

    pstPppContext   = &g_stPppContext;
    for (ucBit = 0; ucBit < A11_MAX_PDN_NUM; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucBit))
        {
            ++ucPdnNum;
        }
    }
    if (PPPC_PDN_ID_UNIQUE == ucPdnNum)
    {
        return VOS_OK;
    }
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPPC_MappingPppIdandPdnId
 ��������  : ��¼PPP Id��Pdn Id֮���ӳ���ϵ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��05��27��
    ��    ��   : w00316385
    �޸�����   : RabId��ΪPdnId

*****************************************************************************/
VOS_VOID PPPC_MappingPppIdandPdnId(VOS_UINT8 ucPppId, VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* ��¼PPP Id��Pdn Id��ӳ���ϵ */
    TTF_SET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucPdnId);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearMappingByPppId
 ��������  : ����Ppp Id���PPP Id��Pdn Id֮���ӳ���ϵ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��05��27��
    ��    ��   : w00316385
    �޸�����   : RabId��ΪPdnId

*****************************************************************************/
VOS_VOID PPPC_ClearMappingByPppId(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;

    pstPppContext   = &g_stPppContext;
    pstPppContext->aulPppIdMapPdnId[ucPppId] = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearMappingByPdnId
 ��������  : ����Pdn Id���PPP Id��Pdn Id֮���ӳ���ϵ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��27��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ClearMappingByPdnId(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppId;


    pstPppContext   = &g_stPppContext;
    for (ucPppId = PPPC_PPP_ID_MIN; ucPppId <= PPPC_PPP_ID_MAX; ++ucPppId)
    {
        TTF_CLEAR_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucPdnId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_CheckPdnId
 ��������  : ���PDN id�Ƿ���Ч
 �������  : VOS_UINT8 ucPdnId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_CheckPdnId(VOS_UINT8 ucPdnId)
{
    /* PDN ID��ȡֵ��ΧΪ0~14 */
    if (ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error! PDN Id = %d\r\n", ucPdnId);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_CheckRateMode
 ��������  : ���Rate mode�Ƿ���Ч
 �������  : TAF_APS_PPP_RAT_MODE_ENUM_UINT8 enMode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_CheckRateMode(TAF_APS_PPP_RAT_MODE_ENUM_UINT8 enMode)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    switch(enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
        case TAF_APS_PPP_RAT_MODE_HRPD:
            ulRet = VOS_OK;
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : PPPC_CheckPdnType
 ��������  : ���Pdn Type�Ƿ���Ч
 �������  : TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_CheckPdnType(TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    switch(enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            ulRet = VOS_OK;
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : PPPC_IsPdnIdUsing
 ��������  : ���PDN id�Ƿ���ʹ����
 �������  : VOS_UINT8 ucPdnId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsPdnIdUsing(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdIndex;


    /* ���PDN id */
    pstPppContext   = &g_stPppContext;
    for (ucPppIdIndex = PPPC_PPP_ID_MIN; ucPppIdIndex <= PPPC_PPP_ID_MAX; ++ucPppIdIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppIdIndex], ucPdnId))
        {
            return PS_TRUE;
        }
    }
    return PS_FALSE;
}

/*****************************************************************************
 �� �� ��  : PPPC_IsDoingAccessAuth
 ��������  : �Ƿ����ڽ��н����Ȩ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-07-23
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsDoingAccessAuth(VOS_UINT8 ucPppId)
{
    PPPINFO_S                          *pstPppInfo;


    if (ucPppId > PPP_MAX_USER_NUM)
    {
        PPPC_WARNING_LOG1("Invalid ppp id!\r\n", ucPppId);
        return PS_FALSE;
    }

    pstPppInfo                  = &g_astPppPool[ucPppId];

    return pstPppInfo->enIsDoingAccessAuth;
}

/*****************************************************************************
 �� �� ��  : PPPC_ChangeAccessAuthState
 ��������  : ���ý����Ȩ״̬
 �������  : PS_BOOL_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-07-23
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_ChangeAccessAuthState
(
    PS_BOOL_ENUM_UINT8                  enIsDoingAcessAuth,
    VOS_UINT8                           ucPppId
)
{
    PPPINFO_S                          *pstPppInfo;


    pstPppInfo                      = &g_astPppPool[ucPppId];
    pstPppInfo->enIsDoingAccessAuth = enIsDoingAcessAuth;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_AddPppId
 ��������  : ����һ��PppId
 �������  : ��
 �������  : VOS_UINT8 *pucPppId
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_AddPppId(VOS_UINT8 *pucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* ��ǰҵ��Э��ֻ֧��һ·PPP�������������ٷſ� */
#if 0
    for (ucPppIdBit = PPPC_PPP_ID_MIN; ucPppIdBit <= PPPC_PPP_ID_MAX; ++ucPppIdBit)
    {
        if (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, ucPppIdBit))
        {
            TTF_SET_A_BIT(pstPppContext->ulPppIdBitMask, ucPppIdBit);
            *pucPppId = ucPppIdBit;
            return VOS_OK;
        }
    }
#endif
    /* ��ʱ���쳣��PPPID�̶�����1��ҵ����Իָ� */
    if (PPPC_BIT_MASK_EMPTY != TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, PPPC_PPP_ID_MIN))
    {
        PPPC_WARNING_LOG1("Ppp id bitmask abnormal!", pstPppContext->ulPppIdBitMask);
    }
    TTF_SET_A_BIT(pstPppContext->ulPppIdBitMask, PPPC_PPP_ID_MIN);

    *pucPppId = PPPC_PPP_ID_MIN;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_DeletePppId
 ��������  : ɾ��һ��PppId
 �������  : ��
 �������  : VOS_UINT8 ucPppId
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_DeletePppId(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* ��PPP Id����Ч�Խ��м�� */
    TTF_CLEAR_A_BIT(pstPppContext->ulPppIdBitMask, ucPppId);
    pstPppContext->aulPppIdMapPdnId[ucPppId] = 0;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_SndUlDataNotify
 ��������  : PPP������Ϣ�����ڽ�����Ϊ0ʱ����PPP�������ݴ���ָʾ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_SndUlDataNotify(VOS_VOID)
{

    (VOS_VOID)VOS_EventWrite(g_ulPppcTaskId, PPPC_UL_PKT_EVENT);


    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_SndDlDataNotify
 ��������  : PPP������Ϣ�����ڽ�����Ϊ0ʱ����PPP�������ݴ���ָʾ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��4��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_SndDlDataNotify(VOS_VOID)
{
    (VOS_VOID)VOS_EventWrite(g_ulPppcTaskId, PPPC_DL_PKT_EVENT);


    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_ApsCmdLinkInit
 ��������  : ��ʼ��APS����Ϣ����,Ŀǰ��Ҫ���������ֻ�м����ȥ������Ϣ,
             �յ�����ȥ����INDֱ�������Դ�����������
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-05
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ApsCmdLinkInit(VOS_VOID)
{
    TTF_LinkInit(MSPS_PID_PPPC, &g_stApsCmdLink);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearApsCmdLinkNode
 ��������  : ���APS����PPP����Ϣ����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-06
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ClearApsCmdLinkNode(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    while (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearEhsmPdnCmdLinkNode
 ��������  : ���EHSM����PPP��PDN��Ϣ����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ClearEhsmPdnCmdLinkNode(VOS_UINT8 ucPdnId)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstNextNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    while (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        pstNextNode         = VOS_NULL_PTR;
        (VOS_VOID)TTF_LinkPeekNext(MSPS_PID_PPPC, pstEhsmPppCmdLink, (TTF_NODE_ST *)pstCurrentHeadNode, (TTF_NODE_ST **)&pstNextNode);

        if (pstCurrentHeadNode->ucPdnId == ucPdnId)
        {
            TTF_LinkRemoveNode(MSPS_PID_PPPC, pstEhsmPppCmdLink, (TTF_NODE_ST *)pstCurrentHeadNode);
            PPP_Free(pstCurrentHeadNode);
        }
        pstCurrentHeadNode  = pstNextNode;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetIpCapability
 ��������  : ����IP��ַ����
 �������  : VOS_UINT8 ucPdnType
 �������  : PPPINFO_S *pstPppInfo
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-12
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SetIpCapability
(
    VOS_UINT8                           ucPdnType,
    PPPINFO_S                          *pstPppInfo,
    VOS_UINT32                          ulSendPid
)
{
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is NULL.");
        return;
    }

    switch(ucPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV4;
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV6;
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            /* 1X��HRPD��֧��IPV6,eHRPD��֧��IPV6,Ŀǰ��PID������ */
            if (UEPS_PID_EHSM == ulSendPid)
            {
                pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_ALL;
            }
            else
            {
                pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV4;
            }
            break;
        default:
            PPPC_WARNING_LOG1("ucPdnType is error. %d", ucPdnType);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ClearUlEncapMem
 ��������  : ������������ڴ�
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-07-02
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ClearUlEncapMem(VOS_VOID)
{
    VOS_UINT32                          ulIndex;


    for (ulIndex = 0; ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR != g_astUlEncapMem[ulIndex].pstDataPtr)
        {
            TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[ulIndex].pstDataPtr);
        }
    }

    PS_MEM_SET(&g_astUlEncapMem[0], 0, sizeof(g_astUlEncapMem));

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetupPpp
 ��������  : ����PPP��·����������LCP����������Ϣ
 �������  : ucPppId    PPP Id
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SetupPpp(VOS_UINT8 ucPppId)
{
    PPP_LUPPARA_S                       stPPPMsg;
    VOS_UINT32                          ulRet;


    ulRet = PPP_StartNegoTimer(ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Start timer fail!\r\n", ucPppId, ulRet);
    }

    PPP_MemSet(&stPPPMsg, 0, sizeof(PPP_LUPPARA_S));

    /* ulRPIndexָʾPPP Id,��1��ʼ���ǺϷ���,��ǰֻ����1,������Ҫ��TAF������ */
    ulRet = Ppp_UsmIoCtl(ucPppId, PPP_ISLUP, (CHAR *)&stPPPMsg);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_811);
        PPPC_WARNING_LOG2("notify ppp fail,ulRpIndex, ulRet", ucPppId, ulRet);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_LinkDown
 ��������  : Э��ɾ��PPP��·
 �������  : ucPppId    PPP Id
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_LinkDown
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                          ulLcpSendFlag
)
{
    PPPINFO_S                              *pstPppInfo;


    pstPppInfo                  = &g_astPppPool[ucPppId];

    if(VOS_TRUE == ulLcpSendFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_948);
        PPPC_INFO_LOG("[ppp]PPP_A11MsgProc: (VOS_TRUE == pstA11Msg->ucLcpSendFlag)\r\n ");

        PPP_DBG_OK_CNT(PPP_PHOK_949);
        pstPppInfo->bFailFlag = PPPA11DOWN;
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        return;
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_951);
        pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;

        (VOID)PPP_Shell_ISLIoCtl(ucPppId, PPP_ISLDOWN, (CHAR *)VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_FillPdnInfo
 ��������  : ������Ϣ��PDN context
 �������  : PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-05
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_FillPdnInfo
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode
)
{
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    ulRet = PPP_GetPDNContextByPDNID(pstCurrentHeadNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstCurrentHeadNode->ucPdnId);
        return;
    }

    pstPDNContext->stEhrpd.ucPdnId      = pstCurrentHeadNode->ucPdnId;
    pstPDNContext->stEhrpd.enAttachType = pstCurrentHeadNode->stEhsmCmdNode.enAttachType;
    pstPDNContext->stEhrpd.enPdnType    = pstCurrentHeadNode->stEhsmCmdNode.enPdnType;
    pstPDNContext->stEhrpd.ucAddressAllocCause    = pstCurrentHeadNode->stEhsmCmdNode.ucAddressAllocCause;

    /* ����APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* ����PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* ����PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* ����Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstCurrentHeadNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ExtractPdnInfoFromHeadNode
 ��������  : ��ͷ�������ȡPDN ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-26
    ��    ��   : h00309869
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ExtractPdnInfoFromHeadNode(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    /* ������Ϣ��PDN context */
    PPPC_FillPdnInfo(pstCurrentHeadNode);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetAuthSwitch
 ��������  : ���ü�Ȩ����
 �������  : VOS_UINT32        ulPapSwitch
             VOS_UINT32        ulChapSwitch
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-19
    ��    ��   : c003338085
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SetAuthSwitch
(
    VOS_UINT32        ulPapSwitch,
    VOS_UINT32        ulChapSwitch
)
{
    g_ulAuthPapOnoff = ulPapSwitch;
    g_ulAuthChapOnoff = ulChapSwitch;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetAuthSwitch
 ��������  : �������õļ�Ȩ���ͼ����롢�û�����Ϣ����ü�Ȩ����ȡֵ
 �������  : TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8    enAuthType
             PPPC_CONTEXT_INFO_STRU             *pstPppCont
 �������  : VOS_UINT32*                         pulPapSwitch
             VOS_UINT32*                         pulChapSwitch
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-20
    ��    ��   : c003338085
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_GetAuthSwitch
(
    TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8    enAuthType,
    PPPC_CONTEXT_INFO_STRU             *pstPppCont,
    VOS_UINT32*                         pulOutPapSwitch,
    VOS_UINT32*                         pulOutChapSwitch
)
{
    VOS_UINT32                          ulPapSwitch = PPPC_AUTH_SWITCH_ON;
    VOS_UINT32                          ulChapSwitch = PPPC_AUTH_SWITCH_ON;
    PS_BOOL_ENUM_UINT8                  enUsrOrPwdEmpty = PS_FALSE;

    enUsrOrPwdEmpty = ((0 == pstPppCont->ulUserNameLen) || (0 == pstPppCont->ulPasswordLen));

    switch(enAuthType)
    {
        /* ��Ȩ����ΪNoneʱ�������м�Ȩ */
        case TAF_APS_PPP_AUTH_TYPE_NONE:
            ulPapSwitch = PPPC_AUTH_SWITCH_OFF;
            ulChapSwitch = PPPC_AUTH_SWITCH_OFF;
            break;

        /* ��Ȩ����ΪPAPʱ�������û��������������ֻ����PAP��Ȩ���� */
        case TAF_APS_PPP_AUTH_TYPE_PAP:
            ulPapSwitch = PPPC_AUTH_SWITCH_ON;
            ulChapSwitch = PPPC_AUTH_SWITCH_OFF;
            break;

        /* ��Ȩ����ΪCHAPʱ���û��������벻Ϊ�յ�������Ž���CHAP��Ȩ���� */
        case TAF_APS_PPP_AUTH_TYPE_CHAP:
            ulPapSwitch = PPPC_AUTH_SWITCH_OFF;
            ulChapSwitch = ((PS_FALSE == enUsrOrPwdEmpty)? PPPC_AUTH_SWITCH_ON : PPPC_AUTH_SWITCH_OFF);
            break;

        /* ��Ȩ����ΪPAP/CHAPʱ��PAP��Ȩʼ�մ����û��������벻Ϊ�յ�������Ž���CHAP��Ȩ���� */
        case TAF_APS_PPP_AUTH_TYPE_PAP_OR_CHAP:
            ulPapSwitch = PPPC_AUTH_SWITCH_ON;
            ulChapSwitch = ((PS_FALSE == enUsrOrPwdEmpty)? PPPC_AUTH_SWITCH_ON : PPPC_AUTH_SWITCH_OFF);
            break;

        default:
            PPPC_WARNING_LOG3("Invalid AuthType %d.\r\n", enAuthType, pstPppCont->ulUserNameLen, pstPppCont->ulPasswordLen);
            break;
    }

    *pulOutPapSwitch = ulPapSwitch;
    *pulOutChapSwitch = ulChapSwitch;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_AttachReqMsgNodeProc
 ��������  : PPPCģ��Attach Request��Ϣ�ڵ㴦��(Ϊ��֤���д�����Ϣ���ڵ����)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_AttachReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    PPPINFO_S                              *pstPppInfo;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* �洢�յ�������ϢʱAPS��PID�ͽ���ģʽ */
    g_stPppContext.ulSendPid = pstCurrentHeadNode->ulSenderPid;
    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    /* ���ǶԳ峡�������뱣֤���д��� */
    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        PPP_HDLC_HARD_SetUp(pstCurrentHeadNode->ucPppId);

#endif

        /* eHrpd��֧��PAP��CHAP */
        PPPC_SetAuthSwitch(PPPC_AUTH_SWITCH_OFF, PPPC_AUTH_SWITCH_OFF);

        PPPC_FillPdnInfo(pstCurrentHeadNode);

        pstPppInfo = &g_astPppPool[pstCurrentHeadNode->ucPppId];

        /* ���û��LCPʵ�����PHASE����ETWORKֱ�ӷ���PPP����(HANDOVER��INITIAL���ж�����һ��) */
        if ((VOS_NULL_PTR == pstPppInfo->pstLcpInfo)
                || (PPP_PHASE_NETWORK != pstPppInfo->usPhase))
        {
            /* PPP������ */
            PPPC_SetupPpp(pstCurrentHeadNode->ucPppId);
        }
        else/*������VSNCPЭ�� */
        {
            PPP_VSNCP_NotifyVSNCPStart(pstPppInfo, pstCurrentHeadNode->ucPdnId);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_DisConnAllPDN
 ��������  : �Ͽ�����PDN����
 �������  : ucPppId    PPP ID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-20
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_DisConnAllPDN(VOS_UINT8 ucPppId)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulRet;
    PPPINFO_S                          *pstPppInfo;
    PDN_CONTEXT_S                      *pstPDNContext;
    PS_BOOL_ENUM_UINT8                  enNeedLcpTerm = PS_TRUE;

    pstPppInfo = &g_astPppPool[ucPppId];

    for ( ucPdnId = 0; ucPdnId < A11_MAX_PDN_NUM; ucPdnId++)
    {
        if (PS_TRUE != PPPC_IsPdnIdUsing(ucPdnId))
        {
            continue;
        }

        ulRet = PPP_GetPDNContextByPDNID(ucPdnId, &pstPDNContext);
        if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
        {
            PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
            continue;
        }

        if (PPP_STATE_INITIAL != pstPDNContext->stEhrpd.stVSNCP.ucState)
        {
            enNeedLcpTerm = PS_FALSE;

            /* PPP����VSNCPȥ���� */
            PPP_VSNCP_NotifyVSNCPStop(pstPppInfo, ucPdnId);
        }
    }

    if (PS_TRUE == enNeedLcpTerm)
    {
        /* PPP����PPPȥ���� */
        PPPC_LinkDown(ucPppId, VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_DetachReqMsgNodeProc
 ��������  : PPPCģ��Detach Request��Ϣ�ڵ㴦��(Ϊ��֤���д�����Ϣ���ڵ����)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_DetachReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;

    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    /* ���ǶԳ峡�������뱣֤���д��� */
    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;
        PPPC_DisConnAllPDN(pstCurrentHeadNode->ucPppId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_PdnConnectReqMsgNodeProc
 ��������  : PPPCģ��PDN Connect Request��Ϣ�ڵ㴦��(Ϊ��֤���д�����Ϣ���ڵ����)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_PdnConnectReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsHandling    = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    /* �洢�յ�������ϢʱAPS��PID */
    g_stPppContext.ulSendPid = pstCurrentHeadNode->ulSenderPid;

    /* ���ǶԳ峡�������뱣֤���д��� */
    enIsHandling    = pstCurrentHeadNode->enIsHandling;
    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        PPPC_FillPdnInfo(pstCurrentHeadNode);
        /* PPP����VSNCPЭ�� */
        PPP_VSNCP_NotifyVSNCPStart(&g_astPppPool[pstCurrentHeadNode->ucPppId], pstCurrentHeadNode->ucPdnId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_PdnDisconnectReqMsgNodeProc
 ��������  : PPPCģ��PDN Disconnect Request��Ϣ�ڵ㴦��(Ϊ��֤���д�����Ϣ���ڵ����)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_PdnDisconnectReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    /* ���ǶԳ峡�������뱣֤���д��� */
    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        /* PPP����VSNCPȥ���� */
        PPP_VSNCP_NotifyVSNCPStop(&g_astPppPool[pstCurrentHeadNode->ucPppId], pstCurrentHeadNode->ucPdnId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmMsgNodeProc
 ��������  : PPPCģ����Ϣ�ڵ㴦��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmMsgNodeProc(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    PS_BOOL_ENUM_UINT8                      enIsDoingInitAA = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    /* �����ǰ���ڽ��н����Ȩ,����ͬʱ��PPP��ҵ��Э�� */
    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsDoingInitAA)
    {
        PPPC_WARNING_LOG("It is now doing access authentication!\r\n");
        return;
    }

    enMsgType           = pstCurrentHeadNode->stEhsmCmdNode.enMsgType;
    switch(enMsgType)
    {
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            PPPC_AttachReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            PPPC_DetachReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            PPPC_PdnConnectReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            PPPC_PdnDisconnectReqMsgNodeProc();

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmAttachCheckParam
 ��������  : ���Attach��Ϣ����
 �������  : CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_EhsmAttachCheckParam
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    if (pstAttachReq->enModemId >= MODEM_ID_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid modem id!", pstAttachReq->enModemId);
        return VOS_ERR;
    }

    if (pstAttachReq->ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error!", pstAttachReq->ucPdnId);
        return VOS_ERR;
    }

    if (pstAttachReq->enAttachType >= CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid enAttachType!", pstAttachReq->enAttachType);
        return VOS_ERR;
    }

    if ((CNAS_CTTF_EHRPD_PDN_TYPE_INVALID == pstAttachReq->enPdnType)
        || (pstAttachReq->enPdnType > CNAS_CTTF_EHRPD_PDN_TYPE_IPV4V6))
    {
        PPPC_WARNING_LOG1("Invalid enPdnType", pstAttachReq->enPdnType);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmAttachReqProc
 ��������  : PPPCģ�鴦��Ehsm��Attach����
 �������  : CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmAttachReqProc
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstEhsmAttachInfo;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT32                          ulRet;
    PPPINFO_S                          *pstPppInfo;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsInitAccessAuth;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    /* ������ */
    ulRet = PPPC_EhsmAttachCheckParam(pstAttachReq);
    if (VOS_OK != ulRet)
    {
        PPPC_RespEhsmAttachFail(pstAttachReq);
        PPPC_WARNING_LOG("Ehsm attah check param fail!");
        return;
    }

    /* ����ǳ�ʼ�����Ȩ���������ʱ���ȵ������Ȩ��ɺ��ٴ��� */
    enIsInitAccessAuth = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsInitAccessAuth)
    {
        /* EHSM�����ظ�ATTACH,Ԫ��1ר�Ŵ洢Attach��Ϣ */
        if (VOS_NULL_PTR != g_astActHrpdTimer[1].hDelayProcTimer)
        {
            PPPC_WARNING_LOG1("Ehsm reattach!\r\n", pstAttachReq->ucPdnId);
            return;
        }

        pstEhsmAttachInfo = (CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)PPP_Malloc(
                        sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU));
        if (VOS_NULL_PTR == pstEhsmAttachInfo)
        {
            PPPC_WARNING_LOG1("Alloc mem fail.", pstAttachReq->ucPdnId);
            return;
        }

        PS_MEM_CPY(pstEhsmAttachInfo, pstAttachReq,
                sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU));

        g_astActHrpdTimer[1].pstMsgPtr = (VOS_VOID *)pstEhsmAttachInfo;
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_astActHrpdTimer[1].hDelayProcTimer,
            MSPS_PID_PPPC, PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN,
            (VOS_UINT32)PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH,
            PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        return;
    }

    /* �յ�EHSM����PPP��Attach��Ϣֱ����� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid                = pstAttachReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType    = pstAttachReq->enMsgId;
    pstEhsmMsgNode->usOpId                     = pstAttachReq->usOpId;
    pstEhsmMsgNode->ucPdnId                    = pstAttachReq->ucPdnId;
    pstEhsmMsgNode->stEhsmCmdNode.enPdnType    = pstAttachReq->enPdnType;
    pstEhsmMsgNode->stEhsmCmdNode.enAttachType = pstAttachReq->enAttachType;
    pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause = pstAttachReq->ucAddressAllocCause;
    pstEhsmMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_AddPppId(&pstEhsmMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Add Ppp Id fail!");
        PPP_Free(pstEhsmMsgNode);
        PPPC_RespEhsmAttachFail(pstAttachReq);
        return;
    }

    pstPppCont  = &g_stPppContext;

    /* �����û��� */
    ulUserNameLen    = VOS_StrNLen((VOS_CHAR *)pstAttachReq->aucUserName,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucUserName,
        (VOS_CHAR *)pstAttachReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* �������� */
    ulPasswordLen    = VOS_StrNLen((VOS_CHAR *)pstAttachReq->aucPassword,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucPassword,
        (VOS_CHAR *)pstAttachReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    /* ����APN */
    PS_MEM_CPY(&(pstEhsmMsgNode->stEhsmCmdNode.stApn),
        &(pstAttachReq->stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* ����PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPdnAddress),
        (VOS_INT8 *)&(pstAttachReq->stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* ����PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPco),
        (VOS_INT8 *)&(pstAttachReq->stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* ����Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstEhsmMsgNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstAttachReq->aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    pstEhsmPppCmdLink           = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    /* �洢modem id */
    g_stPppContext.enModemId    = pstAttachReq->enModemId;

    /* ӳ��ppp id��Pdn id */
    PPPC_MappingPppIdandPdnId(pstEhsmMsgNode->ucPppId, pstAttachReq->ucPdnId);

    PPPC_EhsmMsgNodeProc();

    pstPppInfo                  = &g_astPppPool[pstEhsmMsgNode->ucPppId];

    pstPppInfo->bEhrpdUser      = VOS_TRUE;

    /* ppp idӳ�䵽PPP�ڲ���Ҫ���� */
    pstPppInfo->ulRPIndex   = pstEhsmMsgNode->ucPppId;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmDetachReqProc
 ��������  : PPPCģ�鴦��Ehsm��Detach����
 �������  : pstDetachReq    TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmDetachReqProc
(
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsDoingInitAA;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    /* �����ppp deact״̬��, �յ�EHsm��DeactReq��Ϣ����ֱ�Ӹ�EHsm��DeactSucc */
    if (PPPC_MIN_ACTIVE_ENTITY >= g_stPppContext.ulPppIdBitMask)
    {
        PPPC_WARNING_LOG("Rcv EhsmDetachReq Msg when ppp deact.");
        PPPC_RespEhsmDetach(CNAS_CTTF_EHRPD_RSLT_SUCCESS, pstDetachReq);
        return;
    }

    enIsDoingInitAA = PPPC_EhsmDetachProcWhenAccessAuth();
    if (PS_TRUE == enIsDoingInitAA)
    {
        PPPC_RespEhsmDetach(CNAS_CTTF_EHRPD_RSLT_SUCCESS, pstDetachReq);
        return;
    }

    /* �յ�detach��ϢӦ���ȴ�����ʱҪ��ն����е����нڵ� */
    PPPC_ClearApsCmdLinkNode();

    /* �յ�APS����PPP��ȥ������Ϣֱ����� */
    pstEhsmMsgNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid             = pstDetachReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType = pstDetachReq->enMsgId;
    pstEhsmMsgNode->usOpId                  = pstDetachReq->usOpId;
    pstEhsmMsgNode->enIsHandling            = PS_FALSE;

    pstEhsmMsgNode->ucPppId                 = (VOS_UINT8)PPPC_GetServicePppId();

    pstEhsmPppCmdLink                       = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmPdnConnectCheckParam
 ��������  : ���PdnConnect��Ϣ����
 �������  : CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU    *pstPdnConnectReq
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_EhsmPdnConnectCheckParam
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    if (pstPdnConnectReq->ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error!", pstPdnConnectReq->ucPdnId);
        return VOS_ERR;
    }

    if (pstPdnConnectReq->enAttachType >= CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_BUTT)
    {
        PPPC_WARNING_LOG1("Invalid enAttachType!", pstPdnConnectReq->enAttachType);
        return VOS_ERR;
    }

    if ((CNAS_CTTF_EHRPD_PDN_TYPE_INVALID == pstPdnConnectReq->enPdnType)
        || (pstPdnConnectReq->enPdnType > CNAS_CTTF_EHRPD_PDN_TYPE_IPV4V6))
    {
        PPPC_WARNING_LOG1("Invalid enPdnType", pstPdnConnectReq->enPdnType);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmPdnConnectReqProc
 ��������  : PPPCģ�鴦��Ehsm��PDN Connect����
 �������  : pstPdnConnectReq    EHSM����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnConnectReqProc
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT32                          ulRet;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnInfo;
    PS_BOOL_ENUM_UINT8                  enIsInitAccessAuth;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    ulRet = PPPC_EhsmPdnConnectCheckParam(pstPdnConnectReq);
    if (VOS_OK != ulRet)
    {
        PPPC_RespEhsmPdnConnectFail(pstPdnConnectReq);
        PPPC_WARNING_LOG("Pdn connect check param fail!");
        return;
    }

    /* ����ǳ�ʼ�����Ȩ���������ʱ���ȵ������Ȩ��ɺ��ٴ��� */
    enIsInitAccessAuth = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsInitAccessAuth)
    {
        /* PDN�����ظ�����,Ԫ��2ר�Ŵ洢PDN CONN��Ϣ */
        if (VOS_NULL_PTR != g_astActHrpdTimer[2].hDelayProcTimer)
        {
            PPPC_WARNING_LOG1("PDN reconnect!\r\n", pstPdnConnectReq->ucPdnId);
            return;
        }

        pstPdnConnInfo = (CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)PPP_Malloc(
                        sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU));
        if (VOS_NULL_PTR == pstPdnConnInfo)
        {
            PPPC_WARNING_LOG1("Alloc mem fail.", pstPdnConnectReq->ucPdnId);
            return;
        }

        PS_MEM_CPY(pstPdnConnInfo, pstPdnConnectReq,
                sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU));

        g_astActHrpdTimer[2].pstMsgPtr = (VOS_VOID *)pstPdnConnInfo;
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_astActHrpdTimer[2].hDelayProcTimer,
            MSPS_PID_PPPC, PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN,
            (VOS_UINT32)PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN,
            PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        return;
    }

    /* �յ�APS����PPP�ļ�����Ϣֱ����� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid                = pstPdnConnectReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType    = pstPdnConnectReq->enMsgId;
    pstEhsmMsgNode->usOpId                     = pstPdnConnectReq->usOpId;
    pstEhsmMsgNode->ucPdnId                    = pstPdnConnectReq->ucPdnId;
    pstEhsmMsgNode->stEhsmCmdNode.enAttachType = pstPdnConnectReq->enAttachType;
    pstEhsmMsgNode->stEhsmCmdNode.enPdnType    = pstPdnConnectReq->enPdnType;
    pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause    = pstPdnConnectReq->ucAddressAllocCause;
    pstEhsmMsgNode->enIsHandling               = PS_FALSE;

    pstPppCont = &g_stPppContext;

    /* �����û��� */
    ulUserNameLen    = VOS_StrNLen((VOS_CHAR *)pstPdnConnectReq->aucUserName,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucUserName,
        (VOS_CHAR *)pstPdnConnectReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* �������� */
    ulPasswordLen    = VOS_StrNLen((VOS_CHAR *)pstPdnConnectReq->aucPassword,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucPassword,
        (VOS_CHAR *)pstPdnConnectReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    /* ����APN */
    PS_MEM_CPY(&(pstEhsmMsgNode->stEhsmCmdNode.stApn),
        &(pstPdnConnectReq->stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* ����PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPdnAddress),
        (VOS_INT8 *)&(pstPdnConnectReq->stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* ����PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPco),
        (VOS_INT8 *)&(pstPdnConnectReq->stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* ����Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstEhsmMsgNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPdnConnectReq->aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);


    pstEhsmMsgNode->ucPppId      = (VOS_UINT8)PPPC_GetServicePppId();

    pstEhsmPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    /* ӳ��ppp id��Pdn id */
    PPPC_MappingPppIdandPdnId(pstEhsmMsgNode->ucPppId, pstPdnConnectReq->ucPdnId);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmDisconnReqProcWhenAccessAuth
 ��������  : �����Ȩʱ�յ�Disconn������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-10
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EhsmDisconnReqProcWhenAccessAuth(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingAA;


    enIsDoingAA = PPPC_GetInitAccessAuthMode();

    if (PS_TRUE == enIsDoingAA)
    {
        if (VOS_NULL_PTR != g_astActHrpdTimer[2].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[2].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
            }
            g_astActHrpdTimer[2].hDelayProcTimer  = VOS_NULL_PTR;

            if (VOS_NULL_PTR != g_astActHrpdTimer[2].pstMsgPtr)
            {
                PPP_Free(g_astActHrpdTimer[2].pstMsgPtr);
                g_astActHrpdTimer[2].pstMsgPtr = VOS_NULL_PTR;
            }
        }

        /* ����������밴��ȨDisconn����Ҫ��Ӵ��� */
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmDetachProcWhenAccessAuth
 ��������  : �����Ȩʱ�յ�Detach������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-10
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EhsmDetachProcWhenAccessAuth(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingInitAA;


    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();

    if (PS_TRUE == enIsDoingInitAA)
    {
        if (VOS_NULL_PTR != g_astActHrpdTimer[1].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[1].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
            }
            g_astActHrpdTimer[1].hDelayProcTimer  = VOS_NULL_PTR;

            if (VOS_NULL_PTR != g_astActHrpdTimer[1].pstMsgPtr)
            {
                PPP_Free(g_astActHrpdTimer[1].pstMsgPtr);
                g_astActHrpdTimer[1].pstMsgPtr = VOS_NULL_PTR;
            }
        }

        /* �յ�Detachʱ��PDN Conn����Ҳ����Ҫ������ */
        (VOS_VOID)PPPC_EhsmDisconnReqProcWhenAccessAuth();

        /* ������������ȨDetach����Ҫ���� */
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmPdnDisconnectReqProc
 ��������  : PPPCģ�鴦��Ehsm��PDN Disconnect����
 �������  : pMsg    TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnDisconnectReqProc
(
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsContinue;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnDisconnectReq->ucPdnId))
    {
        PPPC_RespEhsmPdnDisconnect(CNAS_CTTF_EHRPD_RSLT_FAILURE, pstPdnDisconnectReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    enIsContinue = PPPC_EhsmDisconnReqProcWhenAccessAuth();
    if (PS_FALSE == enIsContinue)
    {
        PPPC_RespEhsmPdnDisconnect(CNAS_CTTF_EHRPD_RSLT_SUCCESS, pstPdnDisconnectReq);
        return;
    }

    /* �յ�APS����PPP��ȥ������Ϣֱ����� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid             = pstPdnDisconnectReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType = pstPdnDisconnectReq->enMsgId;
    pstEhsmMsgNode->usOpId                  = pstPdnDisconnectReq->usOpId;
    pstEhsmMsgNode->ucPdnId                 = pstPdnDisconnectReq->ucPdnId;
    pstEhsmMsgNode->enIsHandling            = PS_FALSE;

    if (VOS_OK != PPPC_GetPppIdByPdn(pstEhsmMsgNode->ucPdnId, &pstEhsmMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Get Ppp Id fail!");
        PPP_Free(pstEhsmMsgNode);
        PPPC_RespEhsmPdnDisconnect(CNAS_CTTF_EHRPD_RSLT_FAILURE, pstPdnDisconnectReq);
        return;
    }

    pstEhsmPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmPdnDisconnectIndProc
 ��������  : PPPCģ�鴦��EHSM�ı���ȥ��������
 �������  : pstDeActInd    EHSM����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnDisconnectIndProc
(
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *pstPdnDisconnectInd
)
{
    VOS_UINT8                               ucPppId;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnDisconnectInd->ucPdnId))
    {
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* �����������ʱ���� */
    (VOS_VOID)PPPC_EhsmDisconnReqProcWhenAccessAuth();

    if (VOS_OK != PPPC_GetPppIdByPdn(pstPdnDisconnectInd->ucPdnId, &ucPppId))
    {
        PPPC_WARNING_LOG("Get Ppp Id fail!\r\n");
        return;
    }

    PPPC_ClearEhsmPdnCmdLinkNode(pstPdnDisconnectInd->ucPdnId);
    PPPC_ClearMappingByPdnId(pstPdnDisconnectInd->ucPdnId);

    /* ȫ�ֱ��� PDN�����Ϣ����� */
    PPP_VSNCP_ClearPdnContext(pstPdnDisconnectInd->ucPdnId);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_DetachSelf
 ��������  : ���������eHRPDģʽ�յ��л���1X/HRPDģʽ����Ϣ��Ҫ�ȱ���ȥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-12-29
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_DetachSelf(VOS_VOID)
{
    PPPINFO_S                              *pstPppInfo;
    VOS_UINT8                               ucPppId;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    ucPppId                 = (VOS_UINT8)PPPC_GetServicePppId();
    pstPppInfo              = &g_astPppPool[ucPppId];

    /* �����������ʱ���� */
    (VOS_VOID)PPPC_EhsmDetachProcWhenAccessAuth();

    /* �������������������Դ */
    PPPC_ClearApsCmdLinkNode();
    PPP_DeleteCB(pstPppInfo, PS_FALSE);

    PPPC_DeletePppId(ucPppId);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_EhsmLocDetachIndProc
 ��������  : PPPCģ�鴦��EHSM�ı���ȥ��������
 �������  : pstDetachInd    EHSM����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_EhsmLocDetachIndProc(CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *pstDetachInd)
{
    PPPC_DetachSelf();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_MsgEhsmProc
 ��������  : PPPCģ�鴦��EHSM����
 �������  : pMsg    EHSM����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_MsgEhsmProc(struct MsgCB * pMsg)
{
    Cnas_cttf_ehrpd_ehsm_ppp_pif_MSG       *pstEhsmPppPublicInfo;
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU        *pstAttachReq;
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU        *pstDetachReq;
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU      *pstPdnConnectReq;
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU      *pstPdnDisconnectReq;
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU  *pstPdnDiscconectInd;
    CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU    *pstDetachInd;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;


    /* ǰ���Ѿ���֤pMsg�ǿ� */

    pstEhsmPppPublicInfo        = (Cnas_cttf_ehrpd_ehsm_ppp_pif_MSG *)pMsg;
    enMsgType                   = pstEhsmPppPublicInfo->stMsgReq.ulMsgId;

    switch(enMsgType)
    {
        /* Attach���� */
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            pstAttachReq         = (CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)pMsg;

            PPPC_EhsmAttachReqProc(pstAttachReq);

            break;
        /* Detach���� */
        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            pstDetachReq         = (CNAS_CTTF_EHRPD_DETACH_REQ_STRU *)pMsg;

            PPPC_EhsmDetachReqProc(pstDetachReq);

            break;
        /* PDN Connect���� */
        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            pstPdnConnectReq        = (CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)pMsg;

            PPPC_EhsmPdnConnectReqProc(pstPdnConnectReq);

            break;
        /* PDN Disconnect���� */
        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            pstPdnDisconnectReq     = (CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU *)pMsg;

            PPPC_EhsmPdnDisconnectReqProc(pstPdnDisconnectReq);

            break;

        /* ����PDN�Ͽ� */
        case ID_CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND:

            pstPdnDiscconectInd     = (CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *)pMsg;

            PPPC_EhsmPdnDisconnectIndProc(pstPdnDiscconectInd);

            break;

        /* ����ȥ���� */
        case ID_CNAS_CTTF_EHRPD_LOC_DETACH_IND:

            pstDetachInd            = (CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *)pMsg;

            PPPC_EhsmLocDetachIndProc(pstDetachInd);

            break;

        /* NAS֪ͨ����·״̬��Ϣ���������� */
        case ID_CNAS_CTTF_EHRPD_LINK_STATUS_NTF:

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ActReqMsgNodeProc
 ��������  : PPPCģ�鼤����Ϣ�ڵ㴦��(Ϊ��֤���д�����Ϣ���ڵ����)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ActReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    VOS_UINT32                              ulPapSwitch = PPPC_AUTH_SWITCH_ON;
    VOS_UINT32                              ulChapSwitch = PPPC_AUTH_SWITCH_ON;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    if (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        enIsHandling    = pstApsCurrHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* �洢�յ�������ϢʱAPS��PID�ͽ���ģʽ */
    g_stPppContext.ulSendPid = pstApsCurrHeadNode->ulSenderPid;

    switch(pstApsCurrHeadNode->stApsCmdNode.enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
            PPPC_SetRatMode(PPPC_RAT_MODE_1X);
            PPPC_GetAuthSwitch(pstApsCurrHeadNode->stApsCmdNode.enAuthType, &g_stPppContext, &ulPapSwitch, &ulChapSwitch);
            break;
        case TAF_APS_PPP_RAT_MODE_HRPD:
            PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
            PPPC_GetAuthSwitch(pstApsCurrHeadNode->stApsCmdNode.enAuthType, &g_stPppContext, &ulPapSwitch, &ulChapSwitch);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Rate Mode is %d.\r\n", pstApsCurrHeadNode->stApsCmdNode.enMode);
            break;
    }

    /* ���ǶԳ峡�������뱣֤���д��� */
    if (PS_FALSE == enIsHandling)
    {
        pstApsCurrHeadNode->enIsHandling = PS_TRUE;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        PPP_HDLC_HARD_SetUp(pstApsCurrHeadNode->ucPppId);

#endif
        /* ���ü�Ȩ���� */
        PPPC_SetAuthSwitch(ulPapSwitch, ulChapSwitch);

        /* PPP������ */
        PPPC_SetupPpp(pstApsCurrHeadNode->ucPppId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_DeActReqMsgNodeProc
 ��������  : PPPCģ��ȥ������Ϣ�ڵ㴦��(Ϊ��֤���д�����Ϣ���ڵ����)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_DeActReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    VOS_UINT32                              ulLcpSendFlag;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    /* ���ǶԳ峡�������뱣֤���д��� */
    if (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        enIsHandling    = pstApsCurrHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstApsCurrHeadNode->enIsHandling = PS_TRUE;

        /* ��ʱ��Ҫ����ppp terminateЭ�̱��� */
        ulLcpSendFlag                    = 1;

        /* PPP����PPPȥ���� */
        PPPC_LinkDown(pstApsCurrHeadNode->ucPppId, ulLcpSendFlag);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPPC_TafMsgNodeProc
 ��������  : PPPCģ����Ϣ�ڵ㴦��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_TafMsgNodeProc(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    PS_BOOL_ENUM_UINT8                      enIsDoingInitAA = PS_FALSE;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* �����ǰ���ڽ��г�ʼ�����Ȩ,����ͬʱ��PPP��ҵ��Э�� */
    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();
    if (PS_TRUE == enIsDoingInitAA)
    {
        PPPC_WARNING_LOG("It is now doing access authentication!\r\n");
        return;
    }

    enMsgType           = pstCurrentHeadNode->stApsCmdNode.enMsgType;
    switch(enMsgType)
    {
        case ID_APS_PPP_ACT_REQ:

            PPPC_ActReqMsgNodeProc();

            break;

        case ID_APS_PPP_DEACT_REQ:

            PPPC_DeActReqMsgNodeProc();

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
�� �� ��  : PPPC_RespApsPdnIsActived
��������  : �ɹ�����1X���Ӻ����ظ���PdnId�ٴμ��PPP�ظ��ɹ��������Ϣ
�������  :    APS_PPP_ACT_REQ_STRU    *pApsActReq,
                VOS_VOID               *pPppInfo,
                VOS_UINT32              ulResult
�������  : ��
�� �� ֵ  : VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015-07-28
��    ��   : zWX297122
�޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsPdnIsActived
(
    APS_PPP_ACT_REQ_STRU               *pApsActReq,
    VOS_VOID                           *pPppInfo,
    VOS_UINT32                          ulResult
)
{
    PPPINFO_S                          *pstPppInfo;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;


    /* ������Ӧ��Ϣ�ڴ� */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsActCnf->ulReceiverPid         = pApsActReq->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pApsActReq->usOpId;
    pstApsActCnf->ulResult              = ulResult;
    pstApsActCnf->ucPdnId               = pApsActReq->ucPdnId;
    pstApsActCnf->enPdnType             = pApsActReq->enPdnType;

    pstApsActCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pPppInfo)
    {
        /* �ǿ�˵��Ӧ���Ǽ���ɹ�����Ҫ��DNS��IP��ַ���� */
        pstPppInfo                                = (PPPINFO_S *)pPppInfo;
        pstLcpInfo                                = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
        pstIpcpInfo                               = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
        pstIpv6cpInfo                             = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

        if (VOS_NULL_PTR != pstLcpInfo)
        {
            pstApsActCnf->usMtu                   = pstLcpInfo->stHisOptions.mru;
        }

        if (VOS_NULL_PTR != pstIpcpInfo)
        {
            pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
            pstApsActCnf->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
            pstApsActCnf->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
            PS_MEM_CPY(pstApsActCnf->aucIpv4Addr, &(pstIpcpOption->ouraddr),
                sizeof(pstApsActCnf->aucIpv4Addr));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS));
        }

        if (VOS_NULL_PTR != pstIpv6cpInfo)
        {
            pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);

            PS_MEM_CPY(pstApsActCnf->aucIpv6Addr + TAF_APS_PPP_IPV6_ADDR_LEN/2,
                pstIpv6cpOption->OurV6InId, TAF_APS_PPP_IPV6_ADDR_LEN/2);
        }
    }

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : PPPC_AccessAuthSuccProc
 ��������  : ��ʼ�����Ȩ�ɹ�ʱ�Ĵ���,��Ҫͣ��ʱ������������Ϣ,���ⲻ�������ͷ�
             ������Ϣ���ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-10
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_AccessAuthSuccProc(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRet;


    for (ulIndex = 0; ulIndex < PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR == g_astActHrpdTimer[ulIndex].hDelayProcTimer)
        {
            continue;
        }

        ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[ulIndex].hDelayProcTimer);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Stop timer fail!", ulRet, ulIndex);
        }

        g_astActHrpdTimer[ulIndex].hDelayProcTimer = VOS_NULL_PTR;

        if (VOS_NULL_PTR == g_astActHrpdTimer[ulIndex].pstMsgPtr)
        {
            continue;
        }

        if (0 == ulIndex)
        {
            /* ����HRPD����Ϣ��Ӵ��� */
            PPPC_TafActReqProc((APS_PPP_ACT_REQ_STRU *)g_astActHrpdTimer[ulIndex].pstMsgPtr);
            PPP_Free(g_astActHrpdTimer[ulIndex].pstMsgPtr);
        }
        else
        {
            /* ����eHRPD��Attach��Ϣ��PDN��Ϣ��Ӵ��� */
            PPPC_MsgEhsmProc((struct MsgCB *)g_astActHrpdTimer[ulIndex].pstMsgPtr);
            PPP_Free(g_astActHrpdTimer[ulIndex].pstMsgPtr);
        }
        g_astActHrpdTimer[ulIndex].pstMsgPtr    = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_StopAccessAuthDelayProcTimer
 ��������  : TAFȥ����PPPʱ��Ҫ�жϵ�ǰ�Ƿ������������Ȩ.�����������ʼ�����Ȩ,
             ����Ƿ���HRPD����ʱ��ʱ��������,����ͣ��ʱ��.
 �������  : pstPppActReq    TAF������Ϣ
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8 PS_TRUE:�������ִ�� PS_FALSE:����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_StopAllAccessAuthDelayProcTimer(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRet;


    for (ulIndex = 0; ulIndex < PPPC_ACCESS_AUTH_DELAY_PROC_TIMER_MAX_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR != g_astActHrpdTimer[ulIndex].pstMsgPtr)
        {
            switch ((PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16)ulIndex)
            {
                case PPPC_ACCESS_AUTH_ACT_MODE_HRPD:
                    PPPC_RespApsActFail((APS_PPP_ACT_REQ_STRU *)g_astActHrpdTimer[0].pstMsgPtr);
                    break;
                case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_ATTACH:
                    PPPC_RespEhsmAttachFail((CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)g_astActHrpdTimer[1].pstMsgPtr);
                    break;
                case PPPC_ACCESS_AUTH_ACT_MODE_EHRPD_PDN:
                    PPPC_RespEhsmPdnConnectFail((CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)g_astActHrpdTimer[2].pstMsgPtr);
                    break;
                default:
                    break;
            }
            PPP_Free(g_astActHrpdTimer[ulIndex].pstMsgPtr);
            g_astActHrpdTimer[ulIndex].pstMsgPtr = VOS_NULL_PTR;
        }

        if (VOS_NULL_PTR != g_astActHrpdTimer[ulIndex].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[ulIndex].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG2("Stop timer fail!", ulRet, ulIndex);
                continue;
            }

            g_astActHrpdTimer[ulIndex].hDelayProcTimer = VOS_NULL_PTR;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_TafDeactProcWhenAccessAuth
 ��������  : TAFȥ����PPPʱ��Ҫ�жϵ�ǰ�Ƿ������������Ȩ.�����������ʼ�����Ȩ,
             ����Ƿ���HRPD����ʱ��ʱ��������,����ͣ��ʱ��.
 �������  : pstPppActReq    TAF������Ϣ
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8 PS_TRUE:�������ִ�� PS_FALSE:����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_TafDeactProcWhenAccessAuth
(
    TAF_APS_PPP_RAT_MODE_ENUM_UINT8     enRateMode
)
{
    VOS_UINT32                          ulRet;
    PS_BOOL_ENUM_UINT8                  enIsDoingInitAA;


    /* ��������ʼ�����Ȩ,����ԭ�����̼���ִ�� */
    enIsDoingInitAA = PPPC_GetInitAccessAuthMode();
    if (PS_FALSE == enIsDoingInitAA)
    {
        return PS_TRUE;
    }


    if (TAF_APS_PPP_RAT_MODE_1X == enRateMode)
    {
        PPPC_WARNING_LOG("Receive 1X deact msg when doing InitAccessAuth");
        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* ��ʼ�����ȨֻҪ����һ�μ��� */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        PPPC_StopAllAccessAuthDelayProcTimer();
        return PS_TRUE;
    }
    else
    {
        PPPC_WARNING_LOG("Receive HRPD deact msg when doing InitAccessAuth");
        if (VOS_NULL_PTR != g_astActHrpdTimer[0].hDelayProcTimer)
        {
            ulRet = VOS_StopRelTimer((HTIMER*)&g_astActHrpdTimer[0].hDelayProcTimer);
            if (VOS_OK != ulRet)
            {
                PPPC_WARNING_LOG1("Stop timer fail!", ulRet);
            }

            if (VOS_NULL_PTR != g_astActHrpdTimer[0].pstMsgPtr)
            {
                PPP_Free(g_astActHrpdTimer[0].pstMsgPtr);
                g_astActHrpdTimer[0].pstMsgPtr = VOS_NULL_PTR;
            }

            g_astActHrpdTimer[0].hDelayProcTimer = VOS_NULL_PTR;

        }
        return PS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : PPPC_TafActProcWhenInitAccessAuth
 ��������  : TAF����PPPʱ��Ҫ�жϵ�ǰ�Ƿ������������Ȩ.�����������ʼ�����Ȩ,
             ����1Xʱ��Ҫͣ��ʱ��,��ֹͣ�����Ȩ;����HRPDʱ����ʱ����ʱ����.
 �������  : pstPppActReq    TAF������Ϣ
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8 PS_TRUE:�������ִ�� PS_FALSE:����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-9
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_TafActProcWhenInitAccessAuth
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    APS_PPP_ACT_REQ_STRU               *pstHrpdInfo;
    PS_BOOL_ENUM_UINT8                  enIsInitAccessAuth;
    PPPINFO_S                          *pstPppInfo;


    /* ��������ʼ�����Ȩ,����ԭ�����̼���ִ�� */
    enIsInitAccessAuth = PPPC_GetInitAccessAuthMode();
    if (PS_FALSE == enIsInitAccessAuth)
    {
        PPPC_WARNING_LOG1("It is not doing AA now.", enIsInitAccessAuth);
        return PS_TRUE;
    }

    if (TAF_APS_PPP_RAT_MODE_1X == pstPppActReq->enMode)
    {
        PPPC_WARNING_LOG2("Receive 1X act msg when doing AA.",
            enIsInitAccessAuth, pstPppActReq->enMode);

        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];

        if (PS_FALSE != PPPC_GetInitAccessAuthMode())
        {
            /* ��ʼ�����ȨֻҪ����һ�μ��� */
            PPPC_SetInitAccessAuthMode(PS_FALSE);
        }

        PPPC_StopAllAccessAuthDelayProcTimer();

        PPP_Core_NotifyUperLcpDown(pstPppInfo);

        return PS_TRUE;
    }
    else
    {
        /* NAS�����ظ����� */
        if (VOS_NULL_PTR != g_astActHrpdTimer[0].hDelayProcTimer)
        {
            PPPC_WARNING_LOG1("Hrpd act timer has been already run.",
                    pstPppActReq->ucPdnId);
            return PS_FALSE;
        }

        pstHrpdInfo = (APS_PPP_ACT_REQ_STRU *)PPP_Malloc(
                        sizeof(APS_PPP_ACT_REQ_STRU));
        if (VOS_NULL_PTR == pstHrpdInfo)
        {
            PPPC_WARNING_LOG1("Alloc mem fail.", pstPppActReq->ucPdnId);
            return PS_FALSE;
        }

        PS_MEM_CPY(pstHrpdInfo, pstPppActReq, sizeof(APS_PPP_ACT_REQ_STRU));

        g_astActHrpdTimer[0].pstMsgPtr = (VOS_VOID *)pstHrpdInfo;
        /* ���������ʼ�����Ȩʱ�յ�����HRPD������������ʱ����ʱ����,����FALSE */
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_astActHrpdTimer[0].hDelayProcTimer,
            MSPS_PID_PPPC, PPPC_ACCESS_AUTH_HRPD_ACT_DELAY_PROC_TIMER_LEN,
            (VOS_UINT32)PPPC_ACCESS_AUTH_ACT_MODE_HRPD, PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER,
            VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

        return PS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : PPPC_TafActReqProc
 ��������  : PPPCģ�鴦��TAF��PPP��������
 �������  : pMsg    TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-24
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_TafActReqProc
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulRetVal;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsContinue;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    /* ��ucPdnId���м�� */
    if (VOS_OK != PPPC_CheckPdnId(pstPppActReq->ucPdnId))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input PdnId is too large! %d\r\n", pstPppActReq->ucPdnId);
        return;
    }

    /* ��enMode���м�� */
    if (VOS_OK != PPPC_CheckRateMode(pstPppActReq->enMode))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input Rate mode is error! %d\r\n", pstPppActReq->enMode);
        return;
    }

    /* ��enPdnType���м�� */
    if (VOS_OK != PPPC_CheckPdnType(pstPppActReq->enPdnType))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input Pdn type is error! %d\r\n", pstPppActReq->enPdnType);
        return;
    }

    /* 1Xģʽ��һ��PppIdֻ��һ��PdnId��Ӧ����Ҫ����ظ���PdnId*/
    ulRetVal = PPPC_GetPppIdByPdn(pstPppActReq->ucPdnId, &ucPppId);
    if (VOS_OK == ulRetVal)
    {
        pstPppInfo = &g_astPppPool[ucPppId];

        /* ����е�PdnId�ѳɹ��������� */
        if ((PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
            &&  (1 == pstPppInfo->bPppSuccess))
        {
            /* PPP���ͼ���ɹ�����Ϣ */
            PPPC_RespApsPdnIsActived(pstPppActReq, pstPppInfo, VOS_OK);

            PPPC_WARNING_LOG2("The PDN has been actived! %d\r\n",
                ucPppId, pstPppActReq->ucPdnId);

            return ;
        }
    }

    /* �ж��Ƿ�������ʼ�����Ȩ�����Ƿ�����ڵ���Ӽ�������ִ�� */
    enIsContinue = PPPC_TafActProcWhenInitAccessAuth(pstPppActReq);
    if (PS_TRUE != enIsContinue)
    {
        PPPC_WARNING_LOG2("It is doing AA now! %d\r\n",
            ucPppId, pstPppActReq->ucPdnId);
        return;
    }

    /* �յ�APS����PPP�ļ�����Ϣֱ����� */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstApsMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstApsMsgNode->stNode));

    pstApsMsgNode->ulSenderPid               = pstPppActReq->ulSenderPid;
    pstApsMsgNode->stApsCmdNode.enMsgType    = pstPppActReq->enMsgId;
    pstApsMsgNode->usOpId                    = pstPppActReq->usOpId;
    pstApsMsgNode->ucPdnId                   = pstPppActReq->ucPdnId;
    pstApsMsgNode->stApsCmdNode.enMode       = pstPppActReq->enMode;
    pstApsMsgNode->stApsCmdNode.enPdnType    = pstPppActReq->enPdnType;
    pstApsMsgNode->stApsCmdNode.enAuthType   = pstPppActReq->enAuthType;
    pstApsMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_AddPppId(&pstApsMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Add Ppp Id fail!");
        PPP_Free(pstApsMsgNode);
        PPPC_RespApsActFail(pstPppActReq);
        return;
    }

    pstPppCont       = &g_stPppContext;

    /* �����û��� */
    ulUserNameLen    = VOS_StrNLen((VOS_CHAR *)pstPppActReq->aucUserName,
                            TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_CHAR *)pstPppCont->aucUserName,
        (VOS_CHAR *)pstPppActReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* �������� */
    ulPasswordLen    = VOS_StrNLen((VOS_CHAR *)pstPppActReq->aucPassword,
                            TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_CHAR *)(pstPppCont->aucPassword),
        (VOS_CHAR *)(pstPppActReq->aucPassword), ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    pstApsPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstApsPppCmdLink, &(pstApsMsgNode->stNode));


    /* �洢modem id */
    g_stPppContext.enModemId    = VOS_GetModemIDFromPid(pstPppActReq->ulSenderPid);

    /* ӳ��Pdn id��ppp id */
    PPPC_MappingPppIdandPdnId(pstApsMsgNode->ucPppId, pstPppActReq->ucPdnId);

    PPPC_TafMsgNodeProc();

    pstPppInfo                  = &g_astPppPool[pstApsMsgNode->ucPppId];
    PPPC_SetIpCapability(pstPppActReq->enPdnType, pstPppInfo, pstApsMsgNode->ulSenderPid);

    pstPppInfo->bEhrpdUser      = VOS_FALSE;

    /* ppp idӳ�䵽PPP�ڲ���Ҫ���� */
    pstPppInfo->ulRPIndex       = pstApsMsgNode->ucPppId;

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_TafDeActReqProc
 ��������  : PPPCģ�鴦��TAF��PPPȥ��������
 �������  : pMsg    TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-24
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_TafDeActReqProc(APS_PPP_DEACT_REQ_STRU *pstPppDeActReq)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsContinue;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    if (VOS_OK != PPPC_CheckPdnId(pstPppDeActReq->ucPdnId))
    {
        PPPC_RespApsDeActFail(pstPppDeActReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* �����ppp deact״̬��, �յ�taf��DeactReq��Ϣ����ֱ�Ӹ�taf��DeactSucc */
    if (PPPC_MIN_ACTIVE_ENTITY >= g_stPppContext.ulPppIdBitMask)
    {
        PPPC_WARNING_LOG("Rcv TafDeActReq Msg when ppp deact.");
        PPPC_RespApsDeActDirect(PS_SUCC, pstPppDeActReq);
        return;
    }

    enIsContinue = PPPC_TafDeactProcWhenAccessAuth(pstPppDeActReq->enMode);
    if (PS_FALSE == enIsContinue)
    {
        PPPC_RespApsDeActDirect(PS_SUCC, pstPppDeActReq);
        return;
    }

    /* �յ�deact��ϢӦ���ȴ�����ʱҪ��ն����е����нڵ� */
    PPPC_ClearApsCmdLinkNode();

    /* �յ�APS����PPP��ȥ������Ϣֱ����� */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstApsMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstApsMsgNode->stNode));

    pstApsMsgNode->ulSenderPid               = pstPppDeActReq->ulSenderPid;
    pstApsMsgNode->stApsCmdNode.enMsgType    = pstPppDeActReq->enMsgId;
    pstApsMsgNode->usOpId                    = pstPppDeActReq->usOpId;
    pstApsMsgNode->ucPdnId                   = pstPppDeActReq->ucPdnId;
    pstApsMsgNode->stApsCmdNode.enMode       = pstPppDeActReq->enMode;
    pstApsMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_GetPppIdByPdn(pstApsMsgNode->ucPdnId, &pstApsMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG1("Get Ppp Id fail! ucPdnID:%d.\n", pstApsMsgNode->ucPdnId);
        PPP_Free(pstApsMsgNode);
        PPPC_RespApsDeActFail(pstPppDeActReq);
        return;
    }

    pstApsPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstApsPppCmdLink, &(pstApsMsgNode->stNode));

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_TafDeActIndProc
 ��������  : PPPCģ�鴦��TAF�ı���ȥ��������
 �������  : pstDeActInd    TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_TafDeActIndProc(APS_PPP_DEACT_IND_STRU *pstDeActInd)
{
    PPPINFO_S                              *pstPppInfo;
    VOS_UINT8                               ucPppId;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    if (VOS_OK != PPPC_CheckPdnId(pstDeActInd->ucPdnId))
    {
        PPPC_WARNING_LOG1("Input PdnId is too large! ucPdnId:%d\r\n", pstDeActInd->ucPdnId);
        return;
    }

    /* ����������ִ��,����Ҫ�ж�����ֵ */
    (VOS_VOID)PPPC_TafDeactProcWhenAccessAuth(pstDeActInd->enMode);

    if (VOS_OK != PPPC_GetPppIdByPdn(pstDeActInd->ucPdnId, &ucPppId))
    {
        PPPC_WARNING_LOG1("Get Ppp Id fail! ucPdnId:%d\r\n", pstDeActInd->ucPdnId);
        return;
    }

    pstPppInfo              = &g_astPppPool[ucPppId];

    /* �������������������Դ */
    PPPC_ClearApsCmdLinkNode();
    PPP_DeleteCB(pstPppInfo, PS_FALSE);

    PPPC_DeletePppId(ucPppId);

    /* ��PDN��Ϣ������� */
    /* todo */

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_TafModeChangeNtfProc
 ��������  : PPPCģ�鴦��TAF��ģʽ�л�����
 �������  : pstModeChangeNtf   TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-04
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_TafModeChangeNtfProc(APS_PPP_MODE_CHANGE_NTF_STRU *pstModeChangeNtf)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    PPPINFO_S                          *pstPppInfo;


    /* �ڲ����ñ�ָ֤����ηǿ� */

    if (VOS_OK != PPPC_CheckPdnId(pstModeChangeNtf->ucPdnId))
    {
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    enRatMode = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_EHRPD == enRatMode)
    {
        PPPC_DetachSelf();
        PPPC_WARNING_LOG("Rat mode is eHRPD,should detach self!\r\n");
        return;
    }
    else if (PPPC_RAT_MODE_1X == enRatMode)
    {
        /* ��1X��HRPD��ҵ��PPP���ڼ���̬ʱ��Ҫ֪ͨPA���� */
        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_MIN];

        if ((TAF_APS_PPP_RAT_MODE_HRPD == pstModeChangeNtf->enMode)
            && (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg))
        {
            PPPC_HRPD_SendOpenStreamReq();
        }
    }
    else
    {
        /* ��̹淶 */
    }

    switch(pstModeChangeNtf->enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
            PPPC_SetRatMode(PPPC_RAT_MODE_1X);

            /* ��hrpd�е�1xʱ����Ҫ��hrpd��صĶ�ʱ����ͣ�� */
            PPPC_StopAllAccessAuthDelayProcTimer();
            break;
        case TAF_APS_PPP_RAT_MODE_HRPD:
            PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Rate Mode is %d.\r\n", pstModeChangeNtf->enMode);
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_TafDialModeNtfProc
 ��������  : PPPCģ�鴦��TAF�Ĳ���ģʽ�л�����
 �������  : pstDialModeNtf   TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-07-01
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_TafDialModeNtfProc(APS_PPP_DIAL_MODE_NTF_STRU *pstDialModeNtf)
{
    /* �ڲ����ñ�ָ֤����ηǿ� */

    switch(pstDialModeNtf->enDialMode)
    {
        case TAF_APS_PPP_CDATA_DIAL_MODE_RELAY:
        case TAF_APS_PPP_CDATA_DIAL_MODE_NETWORK:
            PPPC_SetDialMode(pstDialModeNtf->enDialMode);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Dial Mode is %d.\r\n", pstDialModeNtf->enDialMode);
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : PPPC_HRPD_RcvCommittedIndProc
 ��������  : PPPCģ���յ�RPA��committed������Ϣ����,����APP��Stream��ӳ���ϵ
 �������  : pMsg    PA������Ϣ
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_RcvCommittedIndProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_COMMITTED_IND_STRU   *pstCommttedInd;
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    VOS_UINT32                          ulIndex;


    pstCommttedInd  = (CTTF_PPP_HRPD_COMMITTED_IND_STRU*)pMsg;

    g_stPppContext.enModemId    = pstCommttedInd->enModemId;

    pstHrpdContext  = &(g_stPppContext.stHrpdContext);

    for (ulIndex = 0; ulIndex < PPPC_MAX_PA_BINDING_APP_NUM; ulIndex++)
    {
        /* �ֱ���Stream1,2,3 */
        pstHrpdContext->aenApplicationType[ulIndex]
            = pstCommttedInd->enApplicationType[ulIndex];
    }

    pstHrpdContext->enIsSendOpenFlag = PS_FALSE;

    /* ��ȡ���ļ� */
    (VOS_VOID)PPPC_ReadFixedData();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_RcvReservationsIndProc
 ��������  : PPPCģ���յ�RPA��Reservation����������Ϣ����,���浽��������
 �������  : pMsg    PA������Ϣ
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_RcvReservationsIndProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_RESERVATIONS_IND_STRU    *pstReservationsInd;


    pstReservationsInd      = (CTTF_PPP_HRPD_RESERVATIONS_IND_STRU*)pMsg;

    PA_AGENT_HRPD_SetMaxReservNum(pstReservationsInd);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_SendOpenStreamReq
 ��������  : PPPCģ��׼�����շ�����ʱ֪ͨPA��Stream
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendOpenStreamReq(VOS_VOID)
{
    PPPC_HRPD_CONTEXT_STRU                 *pstHrpdContext;
    PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU  *pstPppOpenStreamReq;


    pstHrpdContext      = &(g_stPppContext.stHrpdContext);

    /* ����Ѿ�����������Ҫ���ʹ�����������Ϣ */
    if (PS_TRUE == pstHrpdContext->enIsSendOpenFlag)
    {
        PPPC_WARNING_LOG("No need to send open stream request!\r\n");
        return;
    }
    pstHrpdContext->enIsSendOpenFlag = PS_TRUE;

    pstPppOpenStreamReq = (PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU));
    if (VOS_NULL_PTR == pstPppOpenStreamReq)
    {
        PPPC_ERROR_LOG("Alloc Ppp Open Stream Mem Fail!\r\n");
        return;
    }

    pstPppOpenStreamReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppOpenStreamReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppOpenStreamReq->enMsgId        = ID_PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ;
    pstPppOpenStreamReq->usOpId         = 0;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppOpenStreamReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_SendCloseStreamReq
 ��������  : PPPCģ�鲻���շ�����ʱ֪ͨPA�ر�Stream
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendCloseStreamReq(VOS_VOID)
{
    PPPC_HRPD_CONTEXT_STRU              *pstHrpdContext;
    PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU  *pstPppCloseStreamReq;


    pstHrpdContext      = &(g_stPppContext.stHrpdContext);
    /* ����Ѿ�����������Ҫ���͹ر�����������Ϣ */
    if (PS_FALSE == pstHrpdContext->enIsSendOpenFlag)
    {
        PPPC_WARNING_LOG("No need to send close stream request!\r\n");
        return;
    }
    pstHrpdContext->enIsSendOpenFlag = PS_FALSE;

    pstPppCloseStreamReq = (PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU));
    if (VOS_NULL_PTR == pstPppCloseStreamReq)
    {
        PPPC_ERROR_LOG("Alloc ppp close stream mem fail!\r\n");
        return;
    }

    pstPppCloseStreamReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppCloseStreamReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppCloseStreamReq->enMsgId        = ID_PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ;
    pstPppCloseStreamReq->usOpId         = 0;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppCloseStreamReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_GetStreamNumByAppType
 ��������  : ����Ӧ�����ʹ��������л�ȡ����
 �������  : enAppType    Ӧ��Я����QoS��Ϣ
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_GetStreamNumByAppType
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType,
    VOS_UINT8                                  *pucStreamNum
)
{
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    VOS_UINT32                          ulIndex;


    pstHrpdContext  = &(g_stPppContext.stHrpdContext);
    for (ulIndex = 0; ulIndex < PPPC_MAX_PA_BINDING_APP_NUM; ulIndex++)
    {
        if (enAppType == pstHrpdContext->aenApplicationType[ulIndex])
        {
            *pucStreamNum   = (VOS_UINT8)ulIndex + 1;
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG1("Warning:Do not have this app info!", enAppType);

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_GetAppTypeByStreamNum
 ��������  : �������Ż�ȡӦ������
 �������  : ucStreamNum    ����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-09-29
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_GetAppTypeByStreamNum
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16  *penAppType,
    VOS_UINT8                                   ucStreamNum
)
{
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;


    if ((ucStreamNum > PPPC_MAX_PA_BINDING_APP_NUM) || (0 == ucStreamNum))
    {
        PPPC_WARNING_LOG1("Input invalid stream number!", ucStreamNum);
        return VOS_ERR;
    }

    pstHrpdContext  = &(g_stPppContext.stHrpdContext);
    *penAppType     = pstHrpdContext->aenApplicationType[ucStreamNum-1];

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : PPPC_HRPD_SendOpenQoSReq
 ��������  : PPPCģ��֪ͨPA��QoSЭ��
 �������  : pstQoSInfo    Ӧ��Я����QoS��Ϣ
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendOpenQoSReq(PPPC_HRPD_RESERVATION_QOS_INFO_STRU *pstQoSInfo)
{
    PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU    *pstQoSReq;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStreamNum;


    if (VOS_NULL_PTR == pstQoSInfo)
    {
        PPPC_WARNING_LOG("Warning:Input parameter is null!");
        return;
    }

    ulRet   = PPPC_HRPD_GetStreamNumByAppType(pstQoSInfo->enApplicationType, &ucStreamNum);
    if (VOS_OK != ulRet)
    {
        return;
    }

    pstQoSReq   = (PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU));
    if (VOS_NULL_PTR == pstQoSReq)
    {
        PPPC_ERROR_LOG("Alloc ppp open qos mem fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstQoSReq + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstQoSReq->ulReceiverPid    = CTTF_PID_HRPD_RPA;
    pstQoSReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQoSReq->enMsgId          = ID_PPP_CTTF_HRPD_MFPA_QOS_REQ;
    pstQoSReq->usOpId           = 0;
    pstQoSReq->ucStreamNumber   = ucStreamNum;
    pstQoSReq->ucNumFwdReservations = pstQoSInfo->ucNumFwdReservations;
    pstQoSReq->ucNumRevReservations = pstQoSInfo->ucNumRevReservations;
    PS_MEM_CPY(pstQoSReq->astFwdReservations, pstQoSInfo->astFwdReservations,
                sizeof(pstQoSReq->astFwdReservations));
    PS_MEM_CPY(pstQoSReq->astRevReservations, pstQoSInfo->astRevReservations,
                sizeof(pstQoSReq->astRevReservations));

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstQoSReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_MFPA_QOS_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_SendCloseQoSReq
 ��������  : PPPCģ��֪ͨPA���ر�QoSЭ��
 �������  : pstCloseQoSInfo    Ӧ��Я����QoS��Ϣ
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendCloseQoSReq
(
    PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU *pstQoSCloseInfo
)
{
    PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU  *pstQoSCloseReq;


    if (VOS_NULL_PTR == pstQoSCloseInfo)
    {
        PPPC_WARNING_LOG("Warning:Input parameter is null!");
        return;
    }

    pstQoSCloseReq   = (PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU));
    if (VOS_NULL_PTR == pstQoSCloseReq)
    {
        PPPC_ERROR_LOG("Alloc ppp close qos mem fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstQoSCloseReq + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstQoSCloseReq->ulReceiverPid    = CTTF_PID_HRPD_RPA;
    pstQoSCloseReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQoSCloseReq->enMsgId          = ID_PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ;
    pstQoSCloseReq->usOpId           = 0;
    pstQoSCloseReq->ucNumFwdReservations = pstQoSCloseInfo->ucNumFwdReservations;
    pstQoSCloseReq->ucNumRevReservations = pstQoSCloseInfo->ucNumRevReservations;

    PS_MEM_CPY(pstQoSCloseReq->aucFwdReservationLabels, pstQoSCloseInfo->aucFwdReservationLabels,
                sizeof(pstQoSCloseReq->aucFwdReservationLabels));
    PS_MEM_CPY(pstQoSCloseReq->aucRevReservationLabels, pstQoSCloseInfo->aucRevReservationLabels,
                sizeof(pstQoSCloseReq->aucRevReservationLabels));

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstQoSCloseReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_GetFileReq
 ��������  : ��ȡ�ļ�֪ͨ
 �������  : USIMM_DEF_FILEID_ENUM_UINT32 enFileID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-07-25
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_HRPD_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileID)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;
    VOS_CHAR                           *pcFilePath;


    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        /*���غ���������Ϣ*/
        return VOS_ERR;
    }

    /* ������Ϣ�ڴ� */
    pstMsg   = (USIMM_READFILE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_READFILE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*�����Ϣ����*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (MODEM_ID_0 == g_stPppContext.enModemId)
    {
        pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_USIM;
    }
    else
    {
        pstMsg->stMsgHeader.ulReceiverPid     = I1_WUEPS_PID_USIM;
    }
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_CDMA_APP;

    pstMsg->stFilePath.ulPathLen              = VOS_StrLen(pcFilePath);
    VOS_MemCpy(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_READFILE_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_IsCaveAlgorithmEnable
 ��������  : HRPDģʽ�����Ȩ�Ƿ�֧��CAVE�㷨
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8 PS_FALSE��֧�֣�PS_TRUE֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��01��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsCaveAlgorithmEnable(VOS_VOID)
{
    return g_stPppContext.enCaveEnable;
}

/*****************************************************************************
 �� �� ��  : PPPC_SaveAccessAuthUserNameInfo
 ��������  : ��������Ȩ���û�����Ϣ
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��25��
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SaveAccessAuthUserNameInfo(VOS_UINT8 *pstMsg)
{
    VOS_UINT8                          *pucTemp = pstMsg;
    VOS_UINT8                           ucNAILen;


    /* refer to 3GPP2 C.S0016-D v2.0 Section 3.5.8.13 */
    /* MsgLen | NAILen | Access Auth User Name |
         8bit     8bit        1~127Butes         */
    pucTemp++;
    ucNAILen = *pucTemp;
    pucTemp++;

    if (ucNAILen <= CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN)
    {
        PS_MEM_CPY(g_stPppContext.stHrpdContext.aucAccessAuthUserName, pucTemp, ucNAILen);
        g_stPppContext.stHrpdContext.aucAccessAuthUserName[ucNAILen] = '\0';
        g_stPppContext.stHrpdContext.ucAccessAuthLen    = ucNAILen;
    }
    else
    {
        PPPC_WARNING_LOG1("the length of access auth user name is error. NAILen:%d.\n", ucNAILen);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SaveRunCaveRandu
 ��������  : ����RAND
 �������  : VOS_UINT32 ulRandu
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SaveRunCaveRandu(VOS_UINT32 ulRandu)
{
    g_stPppContext.stHrpdContext.ulRandu = ulRandu;
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetRunCaveRandu
 ��������  : ����RAND
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_GetRunCaveRandu(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.ulRandu;
}

/*****************************************************************************
 �� �� ��  : PPPC_UsimmCdmaSpecAuthProc
 ��������  : CHAP��ȨMD5�㷨����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��29��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_UsimmCdmaSpecAuthProc(USIMM_CDMASPECAUTH_CNF_STRU *pstMsg)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstActPppNode = VOS_NULL_PTR;
    PPPINFO_S                          *pstPppInfo;
    PPPCHAPINFO_S                      *pstChapInfo;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;
    PS_BOOL_ENUM_UINT8                  enIsCaveAlgorithmEnable;
    VOS_UINT32                          ulRandu;


    /* ֹͣ��ʱ�� */

    if (USIMM_CDMASPEC_COMPUTEIP != pstMsg->enAuthType)
    {
        PPPC_WARNING_LOG("enAuthType isn't USIMM_CDMASPEC_COMPUTEIP.\n");
        return;
    }

    if (USIMM_COMPUTEIP_HRPD != pstMsg->uAuthCnf.stComputeIPCnf.enComputeIPType)
    {
        PPPC_WARNING_LOG("enComputeIPType isn't USIMM_COMPUTEIP_CHAP.\n");
        return;
    }

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* �����Ȩ����Ҫ�ӽڵ��ȡ���� */
        enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstMsg->stCmdResult.ulSendPara);
        if (PS_TRUE != enIsDoingAccessAuth)
        {
            pstActPppNode = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_GetActPppHeadNode();

            if (VOS_NULL_PTR == pstActPppNode)
            {
                PPPC_WARNING_LOG("pstActPppNode is NULL.\n");
                return;
            }

            pstPppInfo = &g_astPppPool[pstActPppNode->ucPppId];
        }
        else
        {
            pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];
        }

        pstChapInfo = pstPppInfo->pstChapInfo;
        if (VOS_NULL_PTR == pstChapInfo)
        {
            PPPC_WARNING_LOG("pstChapInfo is NULL.\n");
            return;
        }

        /*����Response ������*/
        PS_MEM_CPY(pstChapInfo->szResponse, pstMsg->uAuthCnf.stComputeIPCnf.aucRspData,
            pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen);

        pstChapInfo->szResponse[pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen] = 0;
        pstChapInfo->ucRespLen = (VOS_UINT8)pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen;
        PPP_CHAP_SendResponse(pstPppInfo);
    }
    else
    {
        PPPC_WARNING_LOG1("The result of MD5 CHAP AUTH error. ErrorCode:%d.\n", pstMsg->stCmdResult.ulErrorCode);
        /* ��֧��CAVE�㷨������£�ʹ��MD5�㷨�����Ȩʧ��ʱ����ʹ��CAVE�㷨��Ȩ */
        enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pstMsg->stCmdResult.ulSendPara);
        enIsCaveAlgorithmEnable = PPPC_IsCaveAlgorithmEnable();
        if ((PS_TRUE == enIsDoingAccessAuth) && (PS_TRUE == enIsCaveAlgorithmEnable))
        {
            ulRandu = PPPC_GetRunCaveRandu();
            PPPC_UIM_RunCaveAuthReq(ulRandu);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_UsimCaveAuthCnfProc
 ��������  : �յ�CAVE��Ȩ�����Ϣ�Ĵ���
 �������  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UsimCaveAuthCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf)
{
    PS_BOOL_ENUM_UINT8                      enIsDoingAccessAuth;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstActPppNode = VOS_NULL_PTR;
    PPPINFO_S                              *pstPppInfo;
    PPPCHAPINFO_S                          *pstChapInfo;
    USIMM_RUNCAVE_AUTH_CNF_STRU            *pstUsimmRuncaveAuthCnf;


    /* ��Ȩʧ�ܣ����ø�BS�ظ���Ӧ��BS��ʱ���� */
    if (USIMM_AUTH_CDMA_SUCCESS != pUsimAuthCnf->enResult)
    {
        PPPC_WARNING_LOG1("PPPC_UsimAuthenticationCnfProc: Auth fail", pUsimAuthCnf->enResult);
        return VOS_ERR;
    }

    /* ȡAUTHUֵ */
    pstUsimmRuncaveAuthCnf          = &(pUsimAuthCnf->uCnfData.stRunCaveCnf);

    /* �����Ȩ����Ҫ�ӽڵ��ȡ���� */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth((VOS_UINT8)pUsimAuthCnf->stCmdResult.ulSendPara);
    if (PS_TRUE != enIsDoingAccessAuth)
    {
        pstActPppNode = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_GetActPppHeadNode();

        if (VOS_NULL_PTR == pstActPppNode)
        {
            PPPC_WARNING_LOG("pstActPppNode is NULL.\n");
            return VOS_ERR;
        }

        pstPppInfo = &g_astPppPool[pstActPppNode->ucPppId];
    }
    else
    {
        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (VOS_NULL_PTR == pstChapInfo)
    {
        PPPC_WARNING_LOG("pstChapInfo is NULL.\n");
        return VOS_ERR;
    }

    /*����Response ������*/
    PS_MEM_SET(pstChapInfo->szResponse, 0, sizeof(pstChapInfo->szResponse));
    pstChapInfo->szResponse[0] = pstUsimmRuncaveAuthCnf->aucAuthr[0];
    pstChapInfo->szResponse[1] = pstUsimmRuncaveAuthCnf->aucAuthr[1];
    pstChapInfo->szResponse[2] = pstUsimmRuncaveAuthCnf->aucAuthr[2];
    pstChapInfo->ucRespLen = CHAP_MAX_RESPONSE_LENGTH;
    PPP_CHAP_SendResponse(pstPppInfo);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_UsimEapAuthCnfProc
 ��������  : �յ�EAP��Ȩ�����Ϣ�Ĵ���
 �������  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UsimEapAuthCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf)
{
    PPPC_EAP_AUTH_RESULT_STRU           stAuthRes;
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstTELECnf;
    const VOS_UINT8                     ucLen = 1;                              /* ���������г���ռ���ֽ��� */

    enResult = pstUsimAuthCnf->enResult;
    switch ( enResult )
    {
        case USIMM_AUTH_UMTS_SUCCESS :
        case USIMM_AUTH_GSM_SUCCESS :
        case USIMM_AUTH_IMS_SUCCESS :
        case USIMM_AUTH_CDMA_SUCCESS :

            stAuthRes.enResult = PPPC_USIMM_AUTH_SUCCESS;
            break;

        case USIMM_AUTH_MAC_FAILURE :

            stAuthRes.enResult = PPPC_USIMM_AUTH_MAC_FAILURE;
            break;

        case USIMM_AUTH_SYNC_FAILURE :

            stAuthRes.enResult = PPPC_USIMM_AUTH_SYNC_FAILURE;
            break;

        default:

            stAuthRes.enResult = PPPC_USIMM_AUTH_OTHER_FAILURE;
            break;
    }

    pstTELECnf = &(pstUsimAuthCnf->uCnfData.stTELECnf);

    stAuthRes.ucAuthRseLen = pstTELECnf->aucAuthRes[0];

    PS_MEM_CPY(stAuthRes.aucAuthRes, pstTELECnf->aucAuthRes + ucLen , sizeof(stAuthRes.aucAuthRes));
    PS_MEM_CPY(stAuthRes.aucAuts, pstTELECnf->aucAuts + ucLen, sizeof(stAuthRes.aucAuts));
    PS_MEM_CPY(stAuthRes.aucCK, pstTELECnf->aucCK + ucLen, sizeof(stAuthRes.aucCK));
    PS_MEM_CPY(stAuthRes.aucIK, pstTELECnf->aucIK + ucLen, sizeof(stAuthRes.aucIK));

    stAuthRes.ucIdentifier = (VOS_UINT8)pstUsimAuthCnf->stCmdResult.ulSendPara;

    PPPC_EAP_AKA_ReciveAuthRes(&stAuthRes);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_UsimmAuthenticationCnfProc
 ��������  : �յ���Ȩ�����Ϣ�Ĵ���
 �������  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��08��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 PPPC_UsimmAuthenticationCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf)
{
    USIMM_AUTH_TYPE_ENUM_UINT32             enAuthType;
    VOS_UINT32                              ulRet;


    enAuthType = pUsimAuthCnf->enAuthType;

    switch (enAuthType)
    {
        case USIMM_RUNCAVE_AUTH:

            ulRet = PPPC_UsimCaveAuthCnfProc(pUsimAuthCnf);

            break;

        case USIMM_EAP_AUTH:
        case USIMM_3G_AUTH:

            ulRet = PPPC_UsimEapAuthCnfProc(pUsimAuthCnf);

            break;

        default:

            /* �������ͣ����ﲻ�ô��� */
            PPPC_WARNING_LOG1("PPPC_UsimAuthenticationCnfProc: enAuthType", pUsimAuthCnf->enAuthType);
            ulRet = VOS_ERR;

            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : PPPC_MsgTafProc
 ��������  : PPPCģ�鴦��TAF����
 �������  : pMsg    TAF����
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-04
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_MsgTafProc(struct MsgCB * pMsg)
{
    Taf_aps_ppp_pif_MSG                    *pstApsPppPublicInfo;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    APS_PPP_ACT_REQ_STRU                   *pstPppActReq;
    APS_PPP_DEACT_REQ_STRU                 *pstPppDeActReq;
    APS_PPP_DEACT_IND_STRU                 *pstPppDeActInd;
    APS_PPP_MODE_CHANGE_NTF_STRU           *pstModeChangeNtf;
    APS_PPP_DIAL_MODE_NTF_STRU             *pstDialModeNtf;


    /* ǰ���Ѿ���֤pMsg�ǿ� */

    pstApsPppPublicInfo         = (Taf_aps_ppp_pif_MSG *)pMsg;
    enMsgType                   = pstApsPppPublicInfo->stMsgData.enMsgId;

    /*����ǽ��յ���TE������������֡*/
    switch(enMsgType)
    {
        /* PPP����ȥ������Ϣ��ͬһ���ط�break */
        case ID_APS_PPP_ACT_REQ:

            pstPppActReq            = (APS_PPP_ACT_REQ_STRU *)pMsg;

            PPPC_TafActReqProc(pstPppActReq);

            break;

        case ID_APS_PPP_DEACT_REQ:

            pstPppDeActReq          = (APS_PPP_DEACT_REQ_STRU *)pMsg;

            PPPC_TafDeActReqProc(pstPppDeActReq);

            break;

        case ID_APS_PPP_DEACT_IND:

            pstPppDeActInd          = (APS_PPP_DEACT_IND_STRU *)pMsg;

            PPPC_TafDeActIndProc(pstPppDeActInd);

            break;

        case ID_APS_PPP_MODE_CHANGE_NTF:

            pstModeChangeNtf        = (APS_PPP_MODE_CHANGE_NTF_STRU *)pMsg;

            PPPC_TafModeChangeNtfProc(pstModeChangeNtf);

            break;

        case ID_APS_PPP_DIAL_MODE_NTF:

            pstDialModeNtf          = (APS_PPP_DIAL_MODE_NTF_STRU *)pMsg;

            PPPC_TafDialModeNtfProc(pstDialModeNtf);

            break;

        /* NAS֪ͨ����·״̬��Ϣ���������� */
        case ID_APS_PPP_LINK_STATUS_NTF:

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_GetDataLinkStatus
 ��������  : ��ȡ������������Ƿ�Ϊ�յ�״̬
 �������  : ��
 �������  : penUlDataLinkNotNull    PS_FALSE:���п� PS_TRUE:���зǿ�
             penDlDataLinkNotNull    PS_FALSE:���п� PS_TRUE:���зǿ�
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-12-28
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_GetUlDlDataLinkStatus
(
    PS_BOOL_ENUM_UINT8                 *penUlDataLinkNotNull,
    PS_BOOL_ENUM_UINT8                 *penDlDataLinkNotNull
)
{
    TTF_LINK_ST                        *pstDlLink;
    TTF_LINK_ST                        *pstUlLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;


    /* �ڲ����ñ�֤��ηǿ� */
    pstDlLink       = &g_stPppDlLink;
    pstUlLink       = &g_stPppUlLink;

    /* �ж������������Ƿ�Ϊ�� */
    pstDlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlLink);
    pstUlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlLink);
    if (VOS_NULL_PTR != pstDlNode)
    {
        *penDlDataLinkNotNull = PS_TRUE;
    }

    if (VOS_NULL_PTR != pstUlNode)
    {
        *penUlDataLinkNotNull = PS_TRUE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_WakeSelf
 ��������  : ����ʱ��Ϊ���һ���������Ҫ����ʱPPPC�����Լ�
 �������  : penUlDataLinkNotNull    PS_FALSE:���п� PS_TRUE:���зǿ�
             penDlDataLinkNotNull    PS_FALSE:���п� PS_TRUE:���зǿ�
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-12-28
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_WakeSelf
(
    PS_BOOL_ENUM_UINT8                  enUlDataLinkNotNull,
    PS_BOOL_ENUM_UINT8                  enDlDataLinkNotNull
)
{
    /* �����ʱ���ǿ��Ѿ��л��ѻ��Ʋ���Ҫ�����Լ� */
    if (VOS_NULL_PTR != g_hReachMaxProcTimer)
    {
        return;
    }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    /* ���Ӳ��HDLC���벻���ڴ��Ѿ�������ʱ������Ҫ�Ի��� */
    if (VOS_NULL_PTR != g_stHdlcConfigInfo.stHdlcFrmTimerHandle)
    {
        return;
    }
#endif

    if (PS_TRUE == enUlDataLinkNotNull)
    {
        PPPC_WARNING_LOG("PPPC Wakeself for ul link!");
        PPPC_SndUlDataNotify();
    }
    else if (PS_TRUE == enDlDataLinkNotNull)
    {
        PPPC_WARNING_LOG("PPPC Wakeself for dl link!");
        PPPC_SndDlDataNotify();
    }
    else
    {
        /* ��̹淶 */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_SendRpaAccessAuthPhaseInd
 ��������  : PPPC֪ͨPA�����Ȩ��ʼ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��28��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PPPC_HRPD_SendRpaAccessAuthPhaseInd(VOS_VOID)
{
    CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND_STRU    *pstPppAccessAuthPhase;
    PS_BOOL_ENUM_UINT8                              enIsDoingAccesAuth;

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth(PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* �����ǰ���������Ȩ��˵���Ѿ�֪ͨ��PA�����Ȩ��ʼ��������֪ͨ */
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        PPPC_WARNING_LOG("Send PA Access Auth Begin Error");
        return;
    }

    pstPppAccessAuthPhase = (CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND_STRU));
    if (VOS_NULL_PTR == pstPppAccessAuthPhase)
    {
        PPPC_ERROR_LOG("Alloc RPA Access Auth Phase Ind msg Memory Fail!\r\n");
        return;
    }

    pstPppAccessAuthPhase->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppAccessAuthPhase->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppAccessAuthPhase->enMsgId        = ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND;
    pstPppAccessAuthPhase->usOpId         = 0;

    /* ���ͽ����Ȩ��Ϣ����PPP�׶� */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppAccessAuthPhase))
    {
        PPPC_WARNING_LOG("Send ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_PHASE_IND msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_SendRpaAccessAuthRsp
 ��������  : PPPC֪ͨPA�����Ȩ����
 �������  : enResult       �����Ȩ���
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��28��
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_SendRpaAccessAuthRsp
(
    CTTF_HRPD_PPP_ACCESS_AUTH_RESULT_ENUM_UINT8 enResult
)
{
    CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP_STRU  *pstPppAccessAuthRsp;
    PS_BOOL_ENUM_UINT8                      enIsDoingAccesAuth;

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth(PPPC_PPP_ID_FOR_ACCESS_AUTH);

    /* �����ǰû�����������Ȩ��֪ͨPA�����Ȩ���� */
    if (PS_FALSE == enIsDoingAccesAuth)
    {
        PPPC_WARNING_LOG1("Send PA Access Auth Rsp Error", enResult);
        return;
    }

    /* ��ʼ�����Ȩ��־��� */
    PPPC_SetInitAccessAuthMode(PS_FALSE);

    pstPppAccessAuthRsp = (CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP_STRU));
    if (VOS_NULL_PTR == pstPppAccessAuthRsp)
    {
        PPPC_ERROR_LOG("Alloc Access Auth Rsp Ind Mem Fail!\r\n");
        return;
    }

    pstPppAccessAuthRsp->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppAccessAuthRsp->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppAccessAuthRsp->enMsgId        = ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP;
    pstPppAccessAuthRsp->usOpId         = 0;
    pstPppAccessAuthRsp->enResult       = enResult;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppAccessAuthRsp))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_HRPD_PPP_PA_ACCESS_AUTH_RSP msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_AccessAuthProc
 ��������  : PPPCģ���յ�CTTF_PID_HRPD_RPA��������Ϣ�Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-12-11
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_AccessAuthProc(struct MsgCB * pMsg)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode;


    if (VOS_NULL_PTR != g_hAADelayTimer)
    {
        (VOS_VOID)VOS_StopRelTimer((HTIMER*)&g_hAADelayTimer);
    }

    (VOS_VOID)VOS_StartRelTimer((HTIMER*)&(g_hAADelayTimer), MID_PPPC, PPPC_AA_DELAY_TIMER_LEN,
        0, PPPC_ACCESS_AUTH_DELAY_PROC_TIMER, VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);

    /* ���ó�ʼ�����Ȩ��־λ */
    PPPC_SetInitAccessAuthMode(PS_TRUE);

    enRateMode  = PPPC_GetRatMode();
    if ((PPPC_RAT_MODE_HRPD != enRateMode) && (PPPC_RAT_MODE_EHRPD != enRateMode))
    {
        /* ��Ҫ�����Ȩ,ֻ����HRPD��eHRPDģʽ,��ʱPAû��֪ͨ,����ΪHRPDģʽ���� */
        PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_AccessAuthFinsh
 ��������  : PPPC�յ�PA���͵�ACCESS AUTH Finsh����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-28
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_AccessAuthFinsh(VOS_VOID)
{
    PPPINFO_S                          *pstPppInfo;

    pstPppInfo = &(g_astPppPool[0]);
    PPP_CHAP_ReceiveSuccess(pstPppInfo);

    /* ��ʱ�Ѿ������ٷ�Э�̱����ˣ���ҪDOWN�� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, PPP_EVENT_LCPDOWN, NULL);
}

/*****************************************************************************
 �� �� ��  : PPPC_HRPD_UpdateConnectionStatus
 ��������  : ����connection��״̬
 �������  : pMsg       PA����PPP����·״̬��Ϣ
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-28
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_UpdateConnectionStatus(struct MsgCB * pMsg)
{
    CTTF_HRPD_PA_PPP_CONNECTION_STATUS_IND_STRU    *pstConnectionStatus;
    CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_UINT8       enStatus;

    pstConnectionStatus = (CTTF_HRPD_PA_PPP_CONNECTION_STATUS_IND_STRU *)pMsg;
    enStatus            = pstConnectionStatus->enStatus;

    if (CTTF_HRPD_PA_CONNECTION_STATUS_ENUM_BUTT > enStatus)
    {
        g_stPppContext.stHrpdContext.enConnectionStatus = enStatus;
    }
    else
    {
        PPPC_WARNING_LOG1("Error Connection Status", enStatus);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_MsgHrpdRpaProc
 ��������  : PPPCģ���յ�CTTF_PID_HRPD_RPA��������Ϣ�Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-03
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_HRPD_MsgRpaProc(struct MsgCB * pMsg)
{
    CTTF_HRPD_PA_PPP_PIF_MSG_TYPE_ENUM_UINT16     enMsgType;


    enMsgType   = *(CTTF_HRPD_PA_PPP_PIF_MSG_TYPE_ENUM_UINT16 *)(pMsg->aucValue);

    switch (enMsgType)
    {
        case ID_CTTF_PPP_HRPD_COMMITTED_IND:

            PPPC_HRPD_RcvCommittedIndProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_RESERVATIONS_IND:

            PPPC_HRPD_RcvReservationsIndProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_OPEN_RESERVATION_IND:

            PPPC_HrpdPaAgentRcvOpenReservProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_CLOSE_RESERVATIONS_IND:

            PPPC_HrpdPaAgentRcvCloseReservProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_RESERVATION_DL_MSG:

            PPPC_HRPD_PaAgentRcvReservDlMsgProc(pMsg);

            break;

        case ID_CTTF_HRPD_PA_PPP_ACCESS_AUTH_IND:

            PPPC_HRPD_AccessAuthProc(pMsg);

            break;
        case ID_CTTF_HRPD_PA_PPP_ACCESS_FINISH_IND:

            PPPC_HRPD_AccessAuthFinsh();

            break;
        case ID_CTTF_HRPD_PA_PPP_CONNECTION_STATUS_IND:

            PPPC_HRPD_UpdateConnectionStatus(pMsg);

            break;
        default:

            PPPC_WARNING_LOG1("Rcv invalid PA message!\r\n", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_MsgUsimmProc
 ��������  : PPPCģ���յ�WUEPS_PID_USIM��������Ϣ�Ĵ���
 �������  : PPPC_UIM_MSG_STRU *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-29
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_MsgUsimmProc(PPPC_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case USIMM_CDMASPECAUTH_CNF:
            PPPC_UsimmCdmaSpecAuthProc((USIMM_CDMASPECAUTH_CNF_STRU *)pstMsg);
            break;

        /* ��Ȩ��Ӧ */
        case USIMM_AUTHENTICATION_CNF:
            PPPC_UsimmAuthenticationCnfProc((USIMM_AUTHENTICATION_CNF_STRU *)pstMsg);
            break;

        /* ��ȡ�ļ�����CNF */
        case USIMM_READFILE_CNF:
            PPPC_UsimmReadFileCnfProc((USIMM_READFILE_CNF_STRU *)pstMsg);
            break;

        default:

            PPPC_WARNING_LOG1("Invalid Usim msg", pstMsg->ulMsgName);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_MsgPihProc
 ��������  : PPPCģ���յ�MAPS_PIH_PID��������Ϣ�Ĵ���
 �������  : PPPC_UIM_MSG_STRU *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-08-13
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_MsgPihProc(PPPC_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case USIMM_CARDSTATUS_IND:
            PPPC_PihUsimStatusIndProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_Init
 ��������  : PPPCģ���ʼ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-10-30
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_Init(enum VOS_INIT_PHASE_DEFINE enPhase )
{
    TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU   stNvCfgOptions;
    VOS_UINT32                          ulDefaultTimerLen = 86400;           /* MAX PPP Inactive TimerĬ��ʱ��24Сʱ */

    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:

        /* ��ʼ���̶����ݼ��� */
        PPPC_InitFixedData();

        /* ��ʼ��OM��ά�ɲ���Ϣ*/
        PPP_MNTN_CMO_Init();

        /* ��ʼ��PPP������ */
        PS_MEM_SET(&g_stPppContext, 0, sizeof(g_stPppContext));

        if (NV_OK != NV_Read(en_NV_Item_TTF_PPPC_CONFIG_OPTIONS, &stNvCfgOptions, sizeof(TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU)))
        {
            g_stPppContext.usMru                = PPPC_MAX_FRAME_LEN;
            g_stPppContext.enCaveEnable         = PS_FALSE;
            g_stPppContext.stHrpdContext.ulPppInactTimerLen = ulDefaultTimerLen;
        }
        else
        {
            g_stPppContext.usMru                = stNvCfgOptions.usMru;
            g_stPppContext.enCaveEnable         = (stNvCfgOptions.ucCaveEnable > 0) ? PS_TRUE : PS_FALSE;
            g_stPppContext.stHrpdContext.ulPppInactTimerLen = stNvCfgOptions.ulPppInactTimerLen;
            if ((g_stPppContext.usMru < PPPC_MIN_FRAME_LEN)
                || (g_stPppContext.usMru > PPPC_MAX_FRAME_LEN))
            {
                g_stPppContext.usMru = PPPC_MAX_FRAME_LEN;
            }

            /* ����0������Чֵ��������ΪĬ��ֵ24Сʱ */
            if (g_stPppContext.stHrpdContext.ulPppInactTimerLen > 0)
            {
                g_stPppContext.stHrpdContext.ulPppInactTimerLen = ulDefaultTimerLen;
            }

        }

        PPP_TaskInit();
        PPP_TaskEntry();

        /* ��ʼ�������ж��� */
        PPPC_QueueInit();

        /* ��ʼ��APS��Ϣ���� */
        PPPC_ApsCmdLinkInit();

        /* ��ʼ��PA AGENT������ */
        PPPC_HRPD_PaAgentInit();

        /* ��ʼ�����������ڴ� */
        PS_MEM_SET(&g_astUlEncapMem[0], 0, sizeof(g_astUlEncapMem));

        /* ��ʼ����ʼ�����Ȩʱ�յ�NAS�ļ�������ʱ��ʱ����Ķ�ʱ�� */
        PS_MEM_SET(&g_astActHrpdTimer[0], 0, sizeof(g_astActHrpdTimer));

        /* ��ʼ�������Ȩconnection״̬ */
        g_stPppContext.stHrpdContext.enConnectionStatus = CTTF_HRPD_PA_CONNECTION_NOT_EXIST_ENUM;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        /* ��ʼ��HDLC */
        if (VOS_OK != PPP_HDLC_HARD_Init())
        {
            return VOS_ERR;
        }

#endif

        /* ע�ᵽPIH��׼�����տ�״̬��Ϣ */
        PIH_RegUsimCardStatusIndMsg(MSPS_PID_PPPC);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        /* ע�ᵽPIH��׼�����տ�1״̬��Ϣ */
        I1_PIH_RegUsimCardStatusIndMsg(MSPS_PID_PPPC);
#endif

        break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

        default:
            vos_printf("1X RMAC, ERROR, INIT_PHASE = %d \r", enPhase);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPPC_MsgProc
 ��������  : PPPģ���е���Ϣ��������������ʱ����Ϣ�Լ���ATģ���
             �յ����������ɹ�������VOS_OK������ΪVOS_ERR��
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-10-30
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_MsgProc(struct MsgCB * pMsg)
{
    if(VOS_NULL_PTR == pMsg)
    {
        PPPC_WARNING_LOG("PPPC_MsgProc pMsg is NULL!\r\n");
        return;
    }

#if defined (CTTF_PC_ST_SWITCH)
    CTTF_HookMsg(pMsg);
#endif

    switch (pMsg->ulSenderPid)
    {
        /*����Ƕ�ʱ����������Ϣ*/
        case VOS_PID_TIMER:

            PPPC_MsgTimerProc((VOS_VOID *)pMsg);

            break;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:

            PPPC_MsgTafProc((VOS_VOID *)pMsg);

            break;

        case UEPS_PID_EHSM:

            PPPC_MsgEhsmProc((VOS_VOID *)pMsg);

            break;

        case CTTF_PID_HRPD_RPA:

            PPPC_HRPD_MsgRpaProc((VOS_VOID *)pMsg);

            break;

        case WUEPS_PID_USIM:
        case I1_WUEPS_PID_USIM:

            PPPC_MsgUsimmProc((PPPC_UIM_MSG_STRU *)pMsg);

            break;

        case MAPS_PIH_PID:
        case I1_MAPS_PIH_PID:

            PPPC_MsgPihProc((PPPC_UIM_MSG_STRU *)pMsg);

            break;

        case MSP_PID_DIAG_APP_AGENT:
        case MSP_PID_DIAG_AGENT:

            PPP_MNTN_CMO_MsgProc(pMsg);

            break;

        default:

            PPPC_WARNING_LOG1("PPPC_MsgProc Sender Pid is Invalid!\r\n", pMsg->ulSenderPid);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespApsActFail
 ��������  : PPP�ظ�APS Actʧ��
 �������  : pstPppActReq   APS_PPP_ACT_REQ_STRU
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsActFail
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;


    if (VOS_NULL_PTR == pstPppActReq)
    {
        return;
    }
    /* ������Ӧ��Ϣ�ڴ� */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_ERROR_LOG("Alloc Ppp Act Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsActCnf->ulReceiverPid         = pstPppActReq->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pstPppActReq->usOpId;
    pstApsActCnf->ulResult              = VOS_ERR;
    pstApsActCnf->ucPdnId               = pstPppActReq->ucPdnId;
    pstApsActCnf->enPdnType             = pstPppActReq->enPdnType;

    g_ucLcpTermMask = PS_FALSE;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_PPP_APS_ACT_CNF!!!\n");

    /* OM��ά�ɲ���Ϣ:ʧ�ܴ�����1 */
    g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
    PPP_MNTN_CalcOtherFailCnt();
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespApsDeActFail
 ��������  : PPP�ظ�APS DeActʧ��
 �������  : pstPppDeActReq   APS_PPP_DEACT_REQ_STRU
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActFail
(
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;


    /* ������Ӧ��Ϣ�ڴ� */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_ERROR_LOG("Alloc Ppp DeAct Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDeActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDeActCnf->ulReceiverPid         = pstPppDeActReq->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId               = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId                = pstPppDeActReq->usOpId;
    pstApsDeActCnf->ulResult              = VOS_ERR;
    pstApsDeActCnf->ucPdnId               = pstPppDeActReq->ucPdnId;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_PPP_APS_DEACT_CNF!!!\n");
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespApsActCmd
 ��������  : PPP�ظ�APS����PPP����
 �������  : pPppInfo       PPP��Ϣ������ʧ��ʱ��VOS_NULL_PTR,����ǿ�
             ulResult       VOS_OK/VOS_ERR
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-05
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsActCmd(VOS_VOID* pPppInfo, VOS_UINT32 ulResult, TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType)
{
    PPPINFO_S                          *pstPppInfo;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enUsedPdnType = enPdnType;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_WARNING_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK != ulResult)
    {
        PPPC_DeletePppId(pstApsMsgNode->ucPppId);
        enUsedPdnType = pstApsMsgNode->stApsCmdNode.enPdnType;

        g_ucLcpTermMask = PS_FALSE;

        /* OM��ά�ɲ���Ϣ:ʧ�ܴ�����1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;

        PPP_MNTN_CalcOtherFailCnt();
    }
    else
    {
        /* OM��ά�ɲ���Ϣ:�ɹ�������1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulSuccCnt++;
    }

    /* OMά���ϱ� */
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    /* ������Ӧ��Ϣ�ڴ� */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        /* ������Ӧ��Ϣʧ��ҲҪɾ���ڵ� */
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsActCnf->ulReceiverPid         = pstApsMsgNode->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pstApsMsgNode->usOpId;
    pstApsActCnf->ulResult              = ulResult;
    pstApsActCnf->ucPdnId               = pstApsMsgNode->ucPdnId;
    pstApsActCnf->enPdnType             = enUsedPdnType;

    pstApsActCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pPppInfo)
    {
        /* �ǿ�˵��Ӧ���Ǽ���ɹ�����Ҫ��DNS��IP��ַ���� */
        pstPppInfo                                = (PPPINFO_S *)pPppInfo;
        pstLcpInfo                                = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
        pstIpcpInfo                               = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
        pstIpv6cpInfo                             = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

        if ((VOS_NULL_PTR != pstLcpInfo)
             && (1 == pstLcpInfo->stHisOptions.neg_mru))
        {
            pstApsActCnf->usMtu                   = pstLcpInfo->stHisOptions.mru;
        }

        if (VOS_NULL_PTR != pstIpcpInfo)
        {
            pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
            pstApsActCnf->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
            pstApsActCnf->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
            PS_MEM_CPY(pstApsActCnf->aucIpv4Addr, &(pstIpcpOption->ouraddr),
                sizeof(pstApsActCnf->aucIpv4Addr));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS));
        }

        if (VOS_NULL_PTR != pstIpv6cpInfo)
        {
            pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
            PS_MEM_CPY(pstApsActCnf->aucIpv6Addr + TAF_APS_PPP_IPV6_ADDR_LEN/2,
                pstIpv6cpOption->OurV6InId, TAF_APS_PPP_IPV6_ADDR_LEN/2);
        }
    }

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    /* ������ϣ���������ɾ���ڵ㲢�ͷ��ڴ� */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstApsPppCmdLink);

    PPP_Free(pstApsMsgNode);

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespApsDeActCmd
 ��������  : ����ҪЭ��ֱ�ӻظ�ȥ������Ϣ
 �������  : ulResult   ȥ������
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-10-10
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActDirect
(
    VOS_UINT32                          ulResult,
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;


    /* ������Ӧ��Ϣ�ڴ� */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp DeAct Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDeActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDeActCnf->ulReceiverPid       = pstPppDeActReq->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId             = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId              = pstPppDeActReq->usOpId;
    pstApsDeActCnf->ulResult            = ulResult;
    pstApsDeActCnf->ucPdnId             = pstPppDeActReq->ucPdnId;

    /* ����ȥ������Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespApsDeActCmd
 ��������  : �ظ�ȥ������Ϣ
 �������  : ulResult   ȥ������
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-05
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActCmd(VOS_UINT32 ulResult)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_WARNING_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    PPPC_DeletePppId(pstApsMsgNode->ucPppId);

    /* ������Ӧ��Ϣ�ڴ� */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp DeAct Cnf Mem Fail!\r\n", ulResult);

        /* ������Ӧ��Ϣʧ��ҲҪɾ���ڵ� */
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDeActCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDeActCnf->ulReceiverPid       = pstApsMsgNode->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId             = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId              = pstApsMsgNode->usOpId;
    pstApsDeActCnf->ulResult            = ulResult;
    pstApsDeActCnf->ucPdnId             = pstApsMsgNode->ucPdnId;

    /* ����ȥ������Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    /* ������ϣ���������ɾ���ڵ㲢�ͷ��ڴ� */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstApsPppCmdLink);

    PPP_Free(pstApsMsgNode);

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_IsNegoComplete
 ��������  : �ж�IPV4V6Э���Ƿ������
 �������  : pstPppInfo
 �������  : penUsedPdnType         PPPʵ��ʹ�õĵ�ַ����
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-08-31
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_IsNegoComplete
(
    VOS_VOID                           *pPppInfo,
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enPdnType,
    VOS_UINT32                          ulSenderPid,
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    *penUsedPdnType
)
{
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT32                          ulRet = VOS_ERR ;


    pstPppInfo  = (PPPINFO_S*)pPppInfo;

    switch(enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            if (pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
                *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV4;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            if (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
                *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV6;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            /* ֻ��eHRPD����Ҫ֧��Э��IPV6 */
            if (UEPS_PID_EHSM == ulSenderPid)
            {
                if ((pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
                    && (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS))
                {
                    ulRet = VOS_OK;
                    *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV4V6;
                }
            }
            else
            {
                /* 1X��HRPDֻ��Э��IPV4,��ʱ��Ҫ��NAS����ʵ��ʹ�õĵ�ַ����IPV4 */
                if (pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
                {
                    ulRet = VOS_OK;
                    *penUsedPdnType = TAF_APS_PPP_ADDR_TYPE_IPV4;
                }
            }
            break;
        default:

            PPPC_WARNING_LOG2("Pdntype and sender pid value", enPdnType, ulSenderPid);
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespApsModifyIndCmd
 ��������  : �ظ�APS IP��ַ�޸���Ϣ
 �������  : pstPppInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-08-31
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespApsModifyIndCmd(PPPINFO_S* pstPppInfo)
{
    PPP_APS_MODIFY_IND_STRU            *pstApsModifyInd;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    VOS_UINT8                           ucPdnId = 0;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enUsedPdnType = TAF_APS_PPP_ADDR_TYPE_BUTT;
    VOS_UINT32                          ulRet;


    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is null!\r\n");
        return;
    }

    ulRet = PPPC_IsNegoComplete((VOS_VOID *)pstPppInfo,
            g_stPppContext.enPdnType, g_stPppContext.ulSendPid, &enUsedPdnType);

    if (VOS_OK != ulRet)
    {
        return;
    }

    if (VOS_OK != PPPC_1X_GetPdnId((VOS_UINT8)pstPppInfo->ulRPIndex, &ucPdnId))
    {
        PPPC_WARNING_LOG1("Get Pdn Id failed, ucPppId:[%d]\n", pstPppInfo->ulRPIndex);
        return;
    }

    /* ������Ӧ��Ϣ�ڴ� */
    pstApsModifyInd    = (PPP_APS_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstApsModifyInd)
    {
        PPPC_WARNING_LOG("Alloc Ppp Modify Ind Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsModifyInd + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsModifyInd->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstApsModifyInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsModifyInd->enMsgId             = ID_PPP_APS_MODIFY_IND;
    pstApsModifyInd->usOpId              = 0;
    pstApsModifyInd->ucPdnId             = ucPdnId;
    pstApsModifyInd->enPdnType           = enUsedPdnType;

    pstLcpInfo                           = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
    pstIpcpInfo                          = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstIpv6cpInfo                        = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

    if (VOS_NULL_PTR != pstLcpInfo)
    {
        pstApsModifyInd->usMtu           = pstLcpInfo->stHisOptions.mru;
    }
    else
    {
        pstApsModifyInd->usMtu           = PPPC_MAX_FRAME_LEN;
    }

    if (VOS_NULL_PTR != pstIpcpInfo)
    {
        pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
        pstApsModifyInd->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
        pstApsModifyInd->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
        PS_MEM_CPY(pstApsModifyInd->aucIpv4Addr, &(pstIpcpOption->ouraddr),
            sizeof(pstApsModifyInd->aucIpv4Addr));
        PS_MEM_CPY(pstApsModifyInd->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
            sizeof(pstApsModifyInd->stIpv4Dns.aucIpv4PrimDNS));
        PS_MEM_CPY(pstApsModifyInd->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
            sizeof(pstApsModifyInd->stIpv4Dns.aucIpv4SecDNS));
    }

    if (VOS_NULL_PTR != pstIpv6cpInfo)
    {
        pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
        PS_MEM_CPY(pstApsModifyInd->aucIpv6Addr + TAF_APS_PPP_IPV6_ADDR_LEN/2,
            pstIpv6cpOption->OurV6InId, TAF_APS_PPP_IPV6_ADDR_LEN/2);
    }

    /* ����ȥ������Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsModifyInd))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_MODIFY_IND msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_IsReadyToRespActCmd
 ��������  : ����Э����ɺ󣬸���PDNType���ж��Ƿ�֪ͨAPS
 �������  : pPppInfo       PPP��Ϣ������ʧ��ʱ��VOS_NULL_PTR,����ǿ�
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_IsReadyToRespActCmd(VOS_VOID* pPppInfo)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    VOS_UINT32                          ulRet = VOS_ERR;
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8    enUsedPdnType = TAF_APS_PPP_ADDR_TYPE_BUTT;


    if (VOS_NULL_PTR == pPppInfo)
    {
        return;
    }

    pstPppInfo        = (PPPINFO_S *)pPppInfo;

    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_RespApsModifyIndCmd(pstPppInfo);
        return;
    }

    ulRet = PPPC_IsNegoComplete(pPppInfo,
            pstApsMsgNode->stApsCmdNode.enPdnType, pstApsMsgNode->ulSenderPid, &enUsedPdnType);

    if (VOS_OK == ulRet)
    {
        g_stPppContext.enPdnType = pstApsMsgNode->stApsCmdNode.enPdnType;
        PPPC_RespApsActCmd(pPppInfo, VOS_OK, enUsedPdnType);
    }

}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmAttachFail
 ��������  : PPP�ظ�Ehsm Attachʧ��
 �������  : pstAttachReq   CNAS_CTTF_EHRPD_ATTACH_REQ_STRU
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmAttachFail
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pstAttachCnf;


    if (VOS_NULL_PTR == pstAttachReq)
    {
        return;
    }

    /* ������Ӧ��Ϣ�ڴ� */
    pstAttachCnf    = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnf)
    {
        PPPC_ERROR_LOG("Alloc Ehsm Attach Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAttachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstAttachCnf->ulReceiverPid         = pstAttachReq->ulSenderPid;
    pstAttachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstAttachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_ATTACH_CNF;
    pstAttachCnf->usOpId                = pstAttachReq->usOpId;
    pstAttachCnf->ucPdnId               = pstAttachReq->ucPdnId;
    pstAttachCnf->enAttachRslt          = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstAttachCnf->enErrorCode           = CNAS_CTTF_EHRPD_ERROR_CODE_PARA_ERROR;
    pstAttachCnf->enAttachType          = pstAttachReq->enAttachType;
    pstAttachCnf->enPdnType             = pstAttachReq->enPdnType;

    if (CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL == pstAttachCnf->enAttachType)
    {
        g_ucLcpTermMask = PS_FALSE;
    }

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstAttachCnf))
    {
        PPPC_WARNING_LOG("Error:Send ID_CTTF_CNAS_EHRPD_ATTACH_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_ATTACH_CNF!!!\n");

    /* OM��ά�ɲ���Ϣ:ʧ�ܴ�����1 */
    g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
    PPP_MNTN_CalcOtherFailCnt();
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmDetach
 ��������  : PPP�ظ�Ehsm Detachʧ��
 �������  : enResult       �ظ��ɹ���ʧ��
             pstDetachReq   CNAS_CTTF_EHRPD_DETACH_REQ_STRU
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmDetach
(
    CNAS_CTTF_EHRPD_RSLT_ENUM_UINT8     enResult,
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
)
{
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU    *pstDetachCnf;


    /* ������Ӧ��Ϣ�ڴ� */
    pstDetachCnf    = (CTTF_CNAS_EHRPD_DETACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU));
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        PPPC_ERROR_LOG("Alloc Ehsm Detach Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDetachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstDetachCnf->ulReceiverPid         = pstDetachReq->ulSenderPid;
    pstDetachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstDetachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_DETACH_CNF;
    pstDetachCnf->usOpId                = pstDetachReq->usOpId;
    pstDetachCnf->enDetachRslt          = enResult;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachCnf))
    {
        PPPC_WARNING_LOG("Error:Send ID_CTTF_CNAS_EHRPD_DETACH_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_DETACH_CNF!!!\n");
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmPdnConnectFail
 ��������  : PPP�ظ�PDN Connectʧ��
 �������  : pstPdnConnectReq   CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnConnectFail
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnConnectCnf;


    if (VOS_NULL_PTR == pstPdnConnectReq)
    {
        return;
    }

    /* ������Ӧ��Ϣ�ڴ� */
    pstPdnConnectCnf = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnConnectCnf)
    {
        PPPC_WARNING_LOG("Alloc PDN Connect Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnConnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnConnectCnf->ulReceiverPid         = pstPdnConnectReq->ulSenderPid;
    pstPdnConnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnConnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF;
    pstPdnConnectCnf->usOpId                = pstPdnConnectReq->usOpId;
    pstPdnConnectCnf->enPdnConnRslt         = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstPdnConnectCnf->ucPdnId               = pstPdnConnectReq->ucPdnId;
    pstPdnConnectCnf->enErrorCode           = CNAS_CTTF_EHRPD_ERROR_CODE_PARA_ERROR;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnConnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF!!!\n");

    /* OM��ά�ɲ���Ϣ:ʧ�ܴ�����1 */
    g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
    PPP_MNTN_CalcOtherFailCnt();
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmPdnDisconnect
 ��������  : PPP�ظ�Ehsm PDN Disconnectʧ��
 �������  : pstPdnDisconnectReq   CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnDisconnect
(
    CNAS_CTTF_EHRPD_RSLT_ENUM_UINT8     enResult,
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
)
{
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU  *pstPdnDisconnectCnf;


    /* ������Ӧ��Ϣ�ڴ� */
    pstPdnDisconnectCnf  = (CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnDisconnectCnf)
    {
        PPPC_WARNING_LOG("Alloc PDN Disconnect Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnDisconnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnDisconnectCnf->ulReceiverPid         = pstPdnDisconnectReq->ulSenderPid;
    pstPdnDisconnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnDisconnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF;
    pstPdnDisconnectCnf->usOpId                = pstPdnDisconnectReq->usOpId;
    pstPdnDisconnectCnf->enDiscRslt            = enResult;
    pstPdnDisconnectCnf->ucPdnId               = pstPdnDisconnectReq->ucPdnId;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDisconnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF!!!\n");
    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmAttachCmd
 ��������  : PPP�ظ�Ehsm����PPP����
 �������  : pIpcpInfo      IPCP��Ϣ������ʧ��ʱ��VOS_NULL_PTR,����ǿ�
             ulResult       VOS_OK/VOS_ERR
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmAttachCmd(VOS_VOID* pVsncpInfo, VOS_UINT32 ulResult)
{
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPVSNCPINFO_S                     *pstVsncpInfo;
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pstAttachCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstEhsmMsgNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstEhsmMsgNode->ucPdnId);

        /* ������Ӧ��Ϣʧ��ҲҪɾ���ڵ� */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);
        return;
    }

    /* ������Ӧ��Ϣ�ڴ� */
    pstAttachCnf    = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnf)
    {
        PPPC_WARNING_LOG1("Alloc Attach Cnf Mem Fail!\r\n", ulResult);

        /* ������Ӧ��Ϣʧ��ҲҪɾ���ڵ� */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstAttachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstAttachCnf->ulReceiverPid         = pstEhsmMsgNode->ulSenderPid;
    pstAttachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstAttachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_ATTACH_CNF;
    pstAttachCnf->usOpId                = pstEhsmMsgNode->usOpId;
    pstAttachCnf->ucPdnId               = pstEhsmMsgNode->ucPdnId;

    if (VOS_OK == ulResult)
    {
        pstAttachCnf->enAttachRslt      = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
        pstAttachCnf->enErrorCode       = CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_BUTT;

        /* OM��ά�ɲ���Ϣ:�ɹ�������1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulSuccCnt++;
    }
    else
    {
        pstAttachCnf->enAttachRslt      = CNAS_CTTF_EHRPD_RSLT_FAILURE;
        pstAttachCnf->enErrorCode       = pstPDNContext->stEhrpd.enErrorCode;

        PPPC_ClearMappingByPppId(pstEhsmMsgNode->ucPppId);
        PPPC_DeletePppId(pstEhsmMsgNode->ucPppId);

         if (CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL == pstAttachCnf->enAttachType)
        {
            g_ucLcpTermMask = PS_FALSE;
        }

        /* OM��ά�ɲ���Ϣ:ʧ�ܴ�����1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;
        PPP_MNTN_CalcOtherFailCnt();
    }

    /* OMά���ϱ� */
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    pstAttachCnf->enAttachType          = pstEhsmMsgNode->stEhsmCmdNode.enAttachType;
    pstAttachCnf->enPdnType             = pstEhsmMsgNode->stEhsmCmdNode.enPdnType;
    pstAttachCnf->ucAddressAllocCause   = pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause;
    pstAttachCnf->usMtu                 = PPP_GetDefaultMru();

    if (VOS_NULL_PTR != pVsncpInfo)
    {
        pstVsncpInfo                    = (PPPVSNCPINFO_S *)pVsncpInfo;
        pstPppInfo                      = (PPPINFO_S *)(pstVsncpInfo->pstPppInfo);

        if (VOS_NULL_PTR != pstPppInfo)
        {
            pstLcpInfo                  = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;

            if ((VOS_NULL_PTR != pstLcpInfo)
                 && (1 == pstLcpInfo->stHisOptions.neg_mru))
            {
                pstAttachCnf->usMtu     = pstLcpInfo->stHisOptions.mru;
            }
        }
    }

    /* ����APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* ����AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* ����PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* ����PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* ����Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstAttachCnf->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstAttachCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_ATTACH_CNF msg fail!");
    }
    else
    {
        if (VOS_OK == ulResult)
        {
            /* ��ʱ�����շ����ݣ�֪ͨPA open stream */
            PPPC_HRPD_SendOpenStreamReq();
        }
    }

    /* ������ϣ���������ɾ���ڵ㲢�ͷ��ڴ� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmDetachCmd
 ��������  : �ظ�ȥ������Ϣ
 �������  : ulResult   ȥ������
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmDetachCmd(VOS_UINT32 ulResult)
{
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU    *pstDetachCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK == ulResult)
    {
        /* ��ʱû��PDN���Ӳ����շ����ݣ�֪ͨPA close stream */
        PPPC_HRPD_SendCloseStreamReq();
    }

    PPPC_DeletePppId(pstEhsmMsgNode->ucPppId);

    /* ������Ӧ��Ϣ�ڴ� */
    pstDetachCnf    = (CTTF_CNAS_EHRPD_DETACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU));
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        PPPC_WARNING_LOG1("Alloc PPP Detach Cnf Mem Fail!\r\n", ulResult);

        /* ������Ӧ��Ϣʧ��ҲҪɾ���ڵ� */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDetachCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstDetachCnf->ulReceiverPid       = pstEhsmMsgNode->ulSenderPid;
    pstDetachCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDetachCnf->enMsgId             = ID_CTTF_CNAS_EHRPD_DETACH_CNF;
    pstDetachCnf->usOpId              = pstEhsmMsgNode->usOpId;

    if (VOS_OK == ulResult)
    {
        pstDetachCnf->enDetachRslt    = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
    }
    else
    {
        pstDetachCnf->enDetachRslt    = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    }

    /* ����ȥ������Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_DETACH_CNF msg fail!");
    }

    /* ������ϣ���������ɾ���ڵ㲢�ͷ��ڴ� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    /* �ظ�NAS Detach����Ҫ����detach_ind */
    g_ucLcpTermMask = PS_FALSE;

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendPdnConnectCnf
 ��������  : ����PDN Connect Cnf��Ϣ
 �������  : pstMsgLinkNode      �ڵ���Ϣ
             ulResult            VOS_OK/VOS_ERR
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-07-13
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendPdnConnectCnf
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstMsgLinkNode,
    VOS_UINT32                          ulResult
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnConnectCnf;
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    ulRet = PPP_GetPDNContextByPDNID(pstMsgLinkNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstMsgLinkNode->ucPdnId);

        return;
    }

    /* ������Ӧ��Ϣ�ڴ� */
    pstPdnConnectCnf    = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnConnectCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnConnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnConnectCnf->ulReceiverPid         = pstMsgLinkNode->ulSenderPid;
    pstPdnConnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnConnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF;
    pstPdnConnectCnf->usOpId                = pstMsgLinkNode->usOpId;

    if (VOS_OK == ulResult)
    {
        pstPdnConnectCnf->enPdnConnRslt     = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
        pstPdnConnectCnf->enErrorCode       = CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_BUTT;

        /* OM��ά�ɲ���Ϣ:�ɹ�������1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulSuccCnt++;
    }
    else
    {
        pstPdnConnectCnf->enPdnConnRslt     = CNAS_CTTF_EHRPD_RSLT_FAILURE;
        pstPdnConnectCnf->enErrorCode       = pstPDNContext->stEhrpd.enErrorCode;

        PPPC_ClearMappingByPdnId(pstMsgLinkNode->ucPdnId);

        /* OM��ά�ɲ���Ϣ:ʧ�ܴ�����1 */
        g_stPppcStatRpt.stPppcStatisticInfo.ulFailCnt++;

        PPP_MNTN_CalcOtherFailCnt();
    }

    /* OMά���ϱ� */
    PPP_MNTN_CMO_SendOmResourceStateInfo();


    pstPdnConnectCnf->ucPdnId               = pstMsgLinkNode->ucPdnId;
    pstPdnConnectCnf->enAttachType          = pstPDNContext->stEhrpd.enAttachType;
    pstPdnConnectCnf->enPdnType             = pstPDNContext->stEhrpd.enPdnType;
    pstPdnConnectCnf->ucAddressAllocCause   = pstPDNContext->stEhrpd.ucAddressAllocCause;

    /* ����APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* ����AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* ����PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* ����PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* ����Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstPdnConnectCnf->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnConnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmPdnConnectCmd
 ��������  : PPP�ظ�Ehsm PDN Connect Request��Ϣ
 �������  : pIpcpInfo      IPCP��Ϣ������ʧ��ʱ��VOS_NULL_PTR,����ǿ�
             ulResult       VOS_OK/VOS_ERR
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnConnectCmd
(
    VOS_VOID                           *pVsncpInfo,
    VOS_UINT32                          ulResult
)
{
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (ID_CNAS_CTTF_EHRPD_ATTACH_REQ == pstEhsmMsgNode->stEhsmCmdNode.enMsgType)
    {
        PPPC_RespEhsmAttachCmd(pVsncpInfo, ulResult);
        return;
    }
#if 0
    if (VOS_OK == PPPC_IsPdnIdUnique(pstEhsmMsgNode->ucPdnId))
    {
        PPPC_INFO_LOG("The PDN Id is unique!\r\n");
        PPPC_RespEhsmAttachCmd(pVsncpInfo, ulResult);
        return;
    }
#endif
    if (ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ != pstEhsmMsgNode->stEhsmCmdNode.enMsgType)
    {
        PPPC_WARNING_LOG("No PDNConnReq!\r\n");
        return;
    }

    /* ����PDN Connect Cnf��Ϣ */
    PPPC_SendPdnConnectCnf(pstEhsmMsgNode, ulResult);

    /* ������ϣ���������ɾ���ڵ㲢�ͷ��ڴ� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    if (VOS_OK == ulResult)
    {
        /* ��ʱ�����շ����ݣ�֪ͨPA open stream */
        PPPC_HRPD_SendOpenStreamReq();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_RespEhsmPdnDisconnectCmd
 ��������  : �ظ�Ehsm PDN Disconnect Request��Ϣ
 �������  : ulResult   PDN Disconnect���
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnDisconnectCmd(VOS_UINT32 ulResult)
{
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU  *pstPdnDisconnectCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ != pstEhsmMsgNode->stEhsmCmdNode.enMsgType)
    {
        PPPC_WARNING_LOG("No PDNDisConnReq!\r\n");
        return;
    }

    PPPC_ClearMappingByPdnId(pstEhsmMsgNode->ucPdnId);

    /* ������Ӧ��Ϣ�ڴ� */
    pstPdnDisconnectCnf    = (CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnDisconnectCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Disconnect Cnf Mem Fail!\r\n", ulResult);

        /* ������Ӧ��Ϣʧ��ҲҪɾ���ڵ� */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnDisconnectCnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstPdnDisconnectCnf->ulReceiverPid       = pstEhsmMsgNode->ulSenderPid;
    pstPdnDisconnectCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPdnDisconnectCnf->enMsgId             = ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF;
    pstPdnDisconnectCnf->usOpId              = pstEhsmMsgNode->usOpId;
    pstPdnDisconnectCnf->ucPdnId             = pstEhsmMsgNode->ucPdnId;

    if (VOS_OK == ulResult)
    {
        pstPdnDisconnectCnf->enDiscRslt      = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
    }
    else
    {
        pstPdnDisconnectCnf->enDiscRslt      = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    }

    /* ����ȥ������Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDisconnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF msg fail!");
    }

    /* ������ϣ���������ɾ���ڵ㲢�ͷ��ڴ� */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_JudgeApsCmdRseultWhenDeleteCB
 ��������  : �жϵ�ɾ��PPP���ƿ�ʱ�Ƿ���Ҫ����дʲô��Ӧ��Ϣ�ͽ��,�����ȥ����
             ��Ϣ,��ʹЭ��ʧ��Ҳ��ɾ��PPP���ƿ���˿���ֱ�ӻظ��ɹ�
 �������  : ucPppId
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-05
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_JudgeApsCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_SendApsDeactNotify(ucPppId);
        PPPC_INFO_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    enMsgType   = pstApsMsgNode->stApsCmdNode.enMsgType;
    if (ID_APS_PPP_ACT_REQ == enMsgType)
    {
        /* ����ڵ��е���Ϣ������PPP������Ϣ����ʱȴɾ��PPP���ƿ�˵��Э��ʧ�� */
        PPPC_RespApsActCmd(VOS_NULL_PTR, VOS_ERR, TAF_APS_PPP_ADDR_TYPE_BUTT);
    }
    else if (ID_APS_PPP_DEACT_REQ == enMsgType)
    {
        /* ����ڵ��е���Ϣ������PPPȥ������Ϣ����ʱ�ѴﵽĿ�ģ��ظ��ɹ� */
        PPPC_RespApsDeActCmd(VOS_OK);
    }
    else
    {
        /* nothing */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_JudgeEhsmCmdRseultWhenDeleteCB
 ��������  : �жϵ�ɾ��PPP���ƿ�ʱ�Ƿ���Ҫ����дʲô��Ӧ��Ϣ�ͽ��,�����ȥ����
             ��Ϣ,��ʹЭ��ʧ��Ҳ��ɾ��PPP���ƿ���˿���ֱ�ӻظ��ɹ�
 �������  : ucPppId
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_JudgeEhsmCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    TTF_LINK_ST                                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU                        *pstEhsmMsgNode;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16            enMsgType;


    /* ������Ͽ�����PDN���ӵ���PPP�ͷ���· */
    if (PS_TRUE == g_astPppPool[ucPppId].enServerTermReq)
    {
        PPPC_SendEhsmDetachNotify(ucPppId);
        return;
    }

    pstEhsmPppCmdLink = &g_stApsCmdLink;

    /* ��EHSM����������ȡͷ�ڵ� */
    pstEhsmMsgNode    = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_SendEhsmDetachNotify(ucPppId);
        PPPC_INFO_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    enMsgType   = pstEhsmMsgNode->stEhsmCmdNode.enMsgType;

    switch(enMsgType)
    {
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            /* ����ڵ��е���Ϣ�����Ǽ�����Ϣ����ʱȴɾ��PPP���ƿ�˵��Э��ʧ�� */
            PPPC_RespEhsmAttachCmd(VOS_NULL_PTR, VOS_ERR);

            break;

        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            /* ����ڵ��е���Ϣ������ȥ������Ϣ����ʱ�ѴﵽĿ�ģ��ظ��ɹ� */
            PPPC_RespEhsmDetachCmd(VOS_OK);

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            PPPC_RespEhsmPdnConnectCmd(VOS_NULL_PTR, VOS_ERR);

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            PPPC_RespEhsmPdnDisconnectCmd(VOS_OK);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_JudgeCmdRseultWhenDeleteCB
 ��������  : �жϵ�ɾ��PPP���ƿ�ʱ�Ƿ���Ҫ����дʲô��Ӧ��Ϣ�ͽ��,�����ȥ����
             ��Ϣ,��ʹЭ��ʧ��Ҳ��ɾ��PPP���ƿ���˿���ֱ�ӻظ��ɹ�
 �������  : ucPppId
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_JudgeCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;


    if (PPPC_PPP_ID_FOR_ACCESS_AUTH == ucPppId)
    {
        PPPC_WARNING_LOG1("Access auth no need to send result to nas!", ucPppId);
        return;
    }

    enRatMode = PPPC_GetRatMode();
    switch(enRatMode)
    {
        case PPPC_RAT_MODE_1X:
        case PPPC_RAT_MODE_HRPD:

            PPPC_JudgeApsCmdRseultWhenDeleteCB(ucPppId);

            break;

        case PPPC_RAT_MODE_EHRPD:

            PPPC_JudgeEhsmCmdRseultWhenDeleteCB(ucPppId);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Rat mode", enRatMode);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendApsDeactNotify
 ��������  : ��APS����ȥ����֪ͨ
 �������  : ucPppId    PPP ID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014-11-05
    ��    ��   : c00184031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendApsDeactNotify(VOS_UINT8 ucPppId)
{
    PPP_APS_DEACT_NTF_STRU             *pstDeactNotify;
    VOS_UINT8                           ucPdnId = 0;

    /* ������յ�LCP TIMERNATE REQ������û��֪ͨNAS ,��֪ͨNAS�����򲻴���*/
    if (PS_TRUE != g_ucLcpTermMask)
    {
        return;
    }
    g_ucLcpTermMask = PS_FALSE;

    if (VOS_OK != PPPC_1X_GetPdnId(ucPppId, &ucPdnId))
    {
        PPPC_WARNING_LOG1("Get Pdn Id failed, ucPppId:[%d]\n", ucPppId);
        PPPC_DeletePppId(ucPppId);
        return;
    }

    PPPC_DeletePppId(ucPppId);

    pstDeactNotify  = (PPP_APS_DEACT_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_NTF_STRU));
    if (VOS_NULL_PTR == pstDeactNotify)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Deact Notify Mem Fail! PppId:%d\n", ucPppId);
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDeactNotify + VOS_MSG_HEAD_LENGTH, 0, (sizeof(PPP_APS_DEACT_NTF_STRU) - VOS_MSG_HEAD_LENGTH));
    pstDeactNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstDeactNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDeactNotify->enMsgId             = ID_PPP_APS_DEACT_NTF;
    pstDeactNotify->usOpId              = 0;
    pstDeactNotify->ucPdnId             = ucPdnId;
    pstDeactNotify->enMode              = PPPC_GetRatMode();

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDeactNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_PPP_APS_DEACT_NOTIFY msg fail! PppId:%d\n", ucPppId);
    }

    PPP_DeleteCB(&g_astPppPool[ucPppId], PS_FALSE);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendEhsmPdnDisconnectNotify
 ��������  : ��EHSM����PDN Disconnect֪ͨ
 �������  : ucPdnId    PDN ID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendEhsmPdnDisconnectNotify(VOS_UINT8 ucPdnId)
{
    CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU  *pstPdnDiscNotify;
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulLcpSendFlag;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;


    if (VOS_OK == PPPC_IsPdnIdUnique(ucPdnId))
    {
        PPPC_INFO_LOG("The pdn Id is unique!\r\n");
        if (VOS_OK == PPPC_GetPppIdByPdn(ucPdnId, &ucPppId))
        {
            PPPC_INFO_LOG("Get PppId successed!\r\n");

            pstEhsmPppCmdLink  = &g_stApsCmdLink;

            /* ��APS����������ȡͷ�ڵ�,�������Ϊ��˵�������緢�����Э��,��Ҫ��Detach Ind */
            pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
            if (VOS_NULL_PTR == pstEhsmMsgNode)
            {
                PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
                g_astPppPool[ucPppId].enServerTermReq = PS_TRUE;
            }

            /* ��ʱ��Ҫ����ppp terminateЭ�̱��� */
            ulLcpSendFlag                    = 1;

            /* PPP����PPPȥ���� */
            PPPC_LinkDown(ucPppId, ulLcpSendFlag);
        }
        else
        {
            PPPC_WARNING_LOG1("Get PppId failed! PdnId:%d\n", ucPdnId);
        }
        return;
    }

    PPPC_ClearMappingByPdnId(ucPdnId);

    pstPdnDiscNotify  = (CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU));
    if (VOS_NULL_PTR == pstPdnDiscNotify)
    {
        PPPC_WARNING_LOG("Alloc Ppp Pdn Disconnect Notify Mem Fail!\r\n");

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstPdnDiscNotify + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstPdnDiscNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstPdnDiscNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPdnDiscNotify->enMsgId             = ID_CTTF_CNAS_EHRPD_PDN_DISC_IND;
    pstPdnDiscNotify->usOpId              = 0;
    pstPdnDiscNotify->ucPdnId             = ucPdnId;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDiscNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_IND msg fail! PdnID:%d\n", ucPdnId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendEhsmDetachNotify
 ��������  : ��EHSM����ȥ����֪ͨ
 �������  : ucPppId    PPP ID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendEhsmDetachNotify(VOS_UINT8 ucPppId)
{
    CTTF_CNAS_EHRPD_DETACH_IND_STRU    *pstDetachNotify;

    /* ��ʱPPPC���ܷ�������,֪ͨPA�ر��� */
    PPPC_HRPD_SendCloseStreamReq();

    /* ������յ�LCP TIMERNATE REQ������û��֪ͨNAS ,��֪ͨNAS�����򲻴���
        ���Attachû�гɹ���Ҳ����֪ͨNAS Detach_ind */
    if ((PS_TRUE != g_ucLcpTermMask) || (PS_TRUE != g_astPppPool[ucPppId].enInactiveTimerEnable))
    {
        PPPC_WARNING_LOG2("No need to Notify EHSM", g_ucLcpTermMask,
                g_astPppPool[ucPppId].enInactiveTimerEnable);
        return;
    }
    g_ucLcpTermMask = PS_FALSE;

    PPPC_DeletePppId(ucPppId);

    pstDetachNotify  = (CTTF_CNAS_EHRPD_DETACH_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_IND_STRU));
    if (VOS_NULL_PTR == pstDetachNotify)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Detach Notify Mem Fail! PppId:%d\n", ucPppId);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstDetachNotify + VOS_MSG_HEAD_LENGTH, 0,
                (sizeof(CTTF_CNAS_EHRPD_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH));
    pstDetachNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstDetachNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDetachNotify->enMsgId             = ID_CTTF_CNAS_EHRPD_DETACH_IND;
    pstDetachNotify->usOpId              = 0;

    /* ���ͼ�����Ӧ��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_CTTF_CNAS_EHRPD_DETACH_IND msg fail! PppId:%d\n", ucPppId);
    }

    PPP_DeleteCB(&g_astPppPool[ucPppId], PS_FALSE);

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_ReceiveLCPTermReq
 ��������  : �յ�����ȥ����֪ͨ
 �������  : ucPppId    PPP ID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-05-24
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_ReceiveLCPTermReq(VOS_UINT8 ucPppId)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;

    enRatMode = PPPC_GetRatMode();
    switch(enRatMode)
    {
        case PPPC_RAT_MODE_1X:
        case PPPC_RAT_MODE_HRPD:

            PPPC_SendApsDeactNotify(ucPppId);

            break;

        case PPPC_RAT_MODE_EHRPD:

            PPPC_SendEhsmDetachNotify(ucPppId);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Rat mode", enRatMode);

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_UIM_MD5ChapAuthReq
 ��������  : HRPDģʽ��CHAP��Ȩ����UIM��ʹ��MD5�㷨���㣬��SIM������Response
 �������  : PPPINFO_S *pstPppInfo, PPPAUTHMSG_S *pstAuthMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-06-29
    ��    ��   : w00316385
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PPPC_UIM_MD5ChapAuthReq(PPPINFO_S *pstPppInfo, PPPC_AUTH_MSG_STRU *pstAuthMsg)
{
    USIMM_CDMASPECAUTH_REQ_STRU        *pstMsg;


    /* �ڲ����ã���֤��ηǿ� */

    /* ������Ϣ�ڴ� */
    pstMsg   = (USIMM_CDMASPECAUTH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_CDMASPECAUTH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*�����Ϣ����*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_CDMASPECAUTH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (MODEM_ID_0 == g_stPppContext.enModemId)
    {
        pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_USIM;
    }
    else
    {
        pstMsg->stMsgHeader.ulReceiverPid     = I1_WUEPS_PID_USIM;
    }
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_CDMASPECAUTH_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_CDMA_APP;

    pstMsg->enAuthType                        = USIMM_CDMASPEC_COMPUTEIP;
    pstMsg->uAuthData.stComputeIP.enComputeIPType = USIMM_COMPUTEIP_HRPD;
    pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.ucCHAPID = pstAuthMsg->ucPktID;
    pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.stChapChallenge.ucDataLen = pstAuthMsg->ucPwdLen;


    PS_MEM_CPY(pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.stChapChallenge.aucData,
                pstAuthMsg->szPwd, pstAuthMsg->ucPwdLen);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_CDMASPECAUTH_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : PPPC_GetPppAuthInfo
 ��������  : ��ȡpppContext
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-12-10
    ��    ��   : q00359829
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID PPPC_GetPppAuthInfo(CTTF_PPPC_AUTH_INFO_STRU *pstPppAuthInfo)
{
    pstPppAuthInfo->ulUserNameLen = g_stPppContext.ulUserNameLen;
    pstPppAuthInfo->ulPasswordLen = g_stPppContext.ulPasswordLen;
    PS_MEM_CPY(&(pstPppAuthInfo->aucUserName[0]),&(g_stPppContext.aucUserName[0]),
                    sizeof(pstPppAuthInfo->aucUserName));
    PS_MEM_CPY(&(pstPppAuthInfo->aucPassword[0]),&(g_stPppContext.aucPassword[0]),
                    sizeof(pstPppAuthInfo->aucPassword));

    pstPppAuthInfo->ucAANaiLen = g_stPppContext.stHrpdContext.ucAccessAuthLen;
    PS_MEM_CPY(&(pstPppAuthInfo->aucAANai[0]),&(g_stPppContext.stHrpdContext.aucAccessAuthUserName[0]),
                    sizeof(pstPppAuthInfo->aucAANai));
}

/*****************************************************************************
 �� �� ��  : PPPC_StartPppInactiveTimer
 ��������  : ����MAX PPP Inactive Timer
 �������  : ucPppId         PPP ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-12-31
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_StartPppInactiveTimer(VOS_UINT8 ucPppId)
{
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTimerLen = VOS_TIMER_MAX_LENGTH;


    pstPppInfo = &g_astPppPool[ucPppId];

    /* �ж�Max PPP Inactive Timer�����Ƿ�� */
    if (PS_TRUE != pstPppInfo->enInactiveTimerEnable)
    {
        return;
    }

    /* ����MAX PPP Inactive Timer */
    if (VOS_NULL_PTR != pstPppInfo->hPppInactiveTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstPppInfo->hPppInactiveTimer));
        pstPppInfo->hPppInactiveTimer = VOS_NULL_PTR;
    }
    /* VOS��ʱ��ʱ�����Ϊ18Сʱ��ulTimerLen��λ�Ǻ��룬ulPppInactTimerLen��λ���룬�����ת�� */
    if (pstPppInfo->ulPppInactTimerLen < ulTimerLen/1000)
    {
        ulTimerLen = pstPppInfo->ulPppInactTimerLen*1000;
    }
    pstPppInfo->ulPppInactTimeOutCnt = 0;
    ulRet = VOS_StartRelTimer(&(pstPppInfo->hPppInactiveTimer),
                      MID_PPPC,
                      ulTimerLen,
                      pstPppInfo->ulRPIndex,
                      PPPC_MAX_PPP_INACTIVE_TIMER,
                      VOS_TIMER_NOLOOP,
                      VOS_TIMER_PRECISION_0);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Start PPP Inactive Timer Failed", ucPppId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_InactivePppTimeoutProc
 ��������  : MAX PPP Inactive Timer��ʱ
 �������  : ucPppId         PPP ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-12-31
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_InactivePppTimeoutProc(VOS_UINT8 ucPppId)
{
    PPPINFO_S                          *pstPppInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTimerLen = VOS_TIMER_MAX_LENGTH;
    VOS_UINT32                          ulReminTimerLen;

    pstPppInfo = &g_astPppPool[ucPppId];

    pstPppInfo->ulPppInactTimeOutCnt++;

    pstPppInfo->hPppInactiveTimer = VOS_NULL_PTR;

    if (pstPppInfo->ulPppInactTimeOutCnt * ulTimerLen/1000 >= pstPppInfo->ulPppInactTimerLen)
    {
        g_ucLcpTermMask = PS_TRUE;
        PPPC_DisConnAllPDN(ucPppId);
        /*PPPC_SendEhsmDetachNotify(ucPppId);*/
    }
    else
    {
        /* VOS��ʱ��ʱ�����Ϊ18Сʱ��ulTimerLen��λ�Ǻ��룬ulPppInactTimerLen��λ���룬�����ת�� */
        ulReminTimerLen = pstPppInfo->ulPppInactTimerLen -  pstPppInfo->ulPppInactTimeOutCnt * ulTimerLen/1000;
        if (ulReminTimerLen < ulTimerLen/1000)
        {
            ulTimerLen = ulReminTimerLen*1000;
        }
        ulRet = VOS_StartRelTimer(&(pstPppInfo->hPppInactiveTimer),
                      MID_PPPC,
                      ulTimerLen,
                      pstPppInfo->ulRPIndex,
                      PPPC_MAX_PPP_INACTIVE_TIMER,
                      VOS_TIMER_NOLOOP,
                      VOS_TIMER_PRECISION_0);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG1("Start PPP Inactive Timer Failed", ucPppId);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SetAttachErrorCode
 ��������  : ����Attachʧ�ܵ�ԭ��ֵ
 �������  : enErrorCode         ʧ�ܵ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-12
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SetAttachErrorCode(CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16  enErrorCode)
{
    VOS_UINT32                          ulRet;
    PDN_CONTEXT_S                      *pstPDNContext = VOS_NULL_PTR;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;

    if ((CNAS_CTTF_EHRPD_ERROR_CODE_LCP_EAP_FAILURE == enErrorCode)
         || (CNAS_CTTF_EHRPD_ERROR_CODE_LCP_OTHER_FAILURE == enErrorCode))
    {
        /* EAP��Ȩʧ�ܺ�ESTABLISH�׶�LCP�ش������ﵽ���޵��µ�Attachʧ��Ӧ�Ӷ���ͷ�ڵ���ȡPDN ID */

        pstEhsmPppCmdLink  = &g_stApsCmdLink;

        /* ��APS����������ȡͷ�ڵ� */
        pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
        if (VOS_NULL_PTR == pstEhsmMsgNode)
        {
            PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
            return;
        }

        ulRet = PPP_GetPDNContextByPDNID(pstEhsmMsgNode->ucPdnId,&pstPDNContext);
        if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext) )
        {
            PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
            return;
        }

        pstPDNContext->stEhrpd.enErrorCode = enErrorCode;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPPC_SendNasModify
 ��������  : ֪ͨNAS Modify
 �������  : pstVSNCPInfo       VSNCPʵ��
             pstPDNContext      PDN������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-01-12
    ��    ��   : t00359887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID PPPC_SendEhsmModifyInd(PPPVSNCPINFO_S *pstVSNCPInfo)
{
    CTTF_CNAS_EHRPD_MODIFY_IND_STRU    *pstModify;
    PDN_CONTEXT_S                      *pstPDNContext;
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    VOS_UINT32                          ulRet;

    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* ��APS����������ȡͷ�ڵ� */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    /* �����ǰ���нڵ�Ϊ�ջ��ߵ�ǰ������нڵ��е�PDN ID��VSNCPʵ���е�PDN ID����ͬ˵������Э�̲���Ҫ֪ͨNAS Modify */
    if ((VOS_NULL_PTR != pstEhsmMsgNode)
         && (pstEhsmMsgNode->ucPdnId == pstVSNCPInfo->ucPDNID))
    {
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID,
                                     &pstPDNContext);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return;
    }

    pstModify = (CTTF_CNAS_EHRPD_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstModify)
    {
        PPPC_ERROR_LOG("Alloc NAS Ehrpd Modify Ind Mem Fail!\r\n");
        return;
    }

    pstModify->ulReceiverPid    = UEPS_PID_EHSM;
    pstModify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstModify->enMsgId          = ID_CTTF_CNAS_EHRPD_MODIFY_IND;
    pstModify->usOpId           = 0;
    pstModify->ucPdnId          = pstVSNCPInfo->ucPDNID;
    pstModify->usMtu            = PPP_GetDefaultMru();

    if (VOS_NULL_PTR != pstVSNCPInfo)
    {
        pstPppInfo                      = (PPPINFO_S *)(pstVSNCPInfo->pstPppInfo);

        if (VOS_NULL_PTR != pstPppInfo)
        {
            pstLcpInfo                  = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;

            if ((VOS_NULL_PTR != pstLcpInfo)
                 && (1 == pstLcpInfo->stHisOptions.neg_mru))
            {
                pstModify->usMtu     = pstLcpInfo->stHisOptions.mru;
            }
        }
    }

    /* ����Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstModify->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);
    /* ����APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* ����AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* ����PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* ����PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstModify->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));

    /* ����Modify��Ϣ */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstModify))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_MODIFY_IND msg fail!");
    }

    return;
}
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

