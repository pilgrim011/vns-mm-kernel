/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnTask.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2008��1��10��
  ����޸�   : 2008��1��10��
  ��������   : TAF FID��ڣ�ִ��FID��ʼ������Ϣ�ַ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
  2.��    ��   : 2008��10��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D06152��AT2D06151��, USIMM�Ż������SMSP�ļ���ض�д����ʧ��
  3.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : AT2D16304, STK PP DOWN�������ƺ�SMS��ص�(U)SIM�ļ�REFRESH
  4.��    ��   : 2010��2��21��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��: AT2D16941,���Ź��������ط�

  5.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "UsimPsInterface.h"
#include "Ssa_Define.h"
#include "MnCall.h"
#include "Taf_Aps.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include "TafMmcInterface.h"
#include "MnMsgExt.h"
#include "UsimPsInterface.h"
#include "MnComm.h"
#include "siapppih.h"
#include "MnCallTimer.h"
#include "RabmTafInterface.h"
#include "MmaAppLocal.h"
/* Added by L60609 for AT Project��2011-10-05,  Begin*/
#include "TafDrvAgentMain.h"
/* Added by L60609 for AT Project��2011-10-05,  End*/
#include "MnCallReqProc.h"
#include "TafApsMain.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlInterface.h"

#include "TafMtaMain.h"

#include "TafSdcCtx.h"
#include "TafSpmMain.h"
#include "MnMsgSmCommProc.h"

#include "NasUsimmApi.h"

 /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
#include "TafCbaProcUsim.h"
 /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-05, begin */
#include "MnCallImsaProc.h"
#include "TafMntn.h"
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-05, end */

#include "TafCsCallMain.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_taf_pif.h"
#include "TafXCallMain.h"
#include "TafXpdsMain.h"
#endif


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

extern VOS_VOID R_ITF_InitFlowCtrl(VOS_VOID);


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_TASK_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

VOS_VOID MN_MSG_RecurDataRestore(
    struct MsgCB                        *pstAppMsg
);

extern VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip);
extern VOS_VOID TAF_XSMS_PidMsgProc(MsgBlock* pstMsg);

VOS_UINT8                               g_ucMnOmConnectFlg       = VOS_FALSE;   /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
VOS_UINT8                               g_ucMnOmPcRecurEnableFlg = VOS_FALSE;   /* PC�������õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */
/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
MN_STK_MSG_FUNC_MAP_STRU                g_astTafStkMsgFuncMap[] =
{
    {STK_MSG_SEND_REQ,         MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT, MN_MSG_ProcAppSend},
    {STK_CALL_START_DTMF_REQ,  MN_CALL_APP_START_DTMF_REQ,        TAF_CALL_RcvStartDtmfReq},
    {STK_CALL_STOP_DTMF_REQ,   MN_CALL_APP_STOP_DTMF_REQ,         TAF_CALL_RcvStopDtmfReq},
    {STK_CALL_CALLORIG_REQ,    MN_CALL_APP_ORIG_REQ,              MN_CALL_StkCallOrigReqProc},
    {STK_CALL_SUPS_CMD_REQ,    MN_CALL_APP_SUPS_CMD_REQ,          MN_CALL_CallSupsCmdReqProc},
    {STK_SS_REGISTERSS_REQ,    TAF_MSG_REGISTERSS_MSG,            MN_SndAppMsgToSs},
    {STK_SS_ERASESS_REQ,       TAF_MSG_ERASESS_MSG,               MN_SndAppMsgToSs},
    {STK_SS_ACTIVATESS_REQ,    TAF_MSG_ACTIVATESS_MSG,            MN_SndAppMsgToSs},
    {STK_SS_DEACTIVATESS_REQ,  TAF_MSG_DEACTIVATESS_MSG,          MN_SndAppMsgToSs},
    {STK_SS_INTERROGATESS_REQ, TAF_MSG_INTERROGATESS_MSG,         MN_SndAppMsgToSs},
    {STK_SS_REGPWD_REQ,        TAF_MSG_REGPWD_MSG,                MN_SndAppMsgToSs},
    {STK_SS_USSD_REQ,          TAF_MSG_PROCESS_USS_MSG,           MN_SndAppMsgToSs},
    {SI_STK_ENVELOPE_CNF,    SI_STK_ENVELOPE_CNF,              TAF_ProcStkEnvelopeCnf}
};
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_Init
 ��������  : ��ʼ��TAF�ĸ���ģ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��4��20��
    ��    ��   : z00161729
    �޸�����   : �޸����ⵥAT2D18405
  3.��    ��   : 2011��12��2��
    ��    ��   : L00171473
    �޸�����   : �������س�ʼ��For DTS2011120201716
  4.��    ��   : 2012��12��26��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ������SDC��ʼ��
  5.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:����SPM�ĳ�ʼ��
  6.��    ��   : 2013��6��17��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
*****************************************************************************/
VOS_UINT32  MN_Init(enum VOS_INIT_PHASE_DEFINE  ip)
{
    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    switch( ip )
    {
    case VOS_IP_INITIAL:

        NAS_PIHAPI_RegCardRefreshIndMsg(WUEPS_PID_TAF);

        pstSdcCtx = TAF_SDC_GetSdcCtx();
        TAF_SDC_InitCtx(TAF_SDC_INIT_CTX_STARTUP, pstSdcCtx);

        /* ��ʼ��CCA */
        MN_CALL_Init(MN_CALL_POWER_STATE_ON);

        /* ��ʼ��SMA */
        MN_MSG_Init();

        /* ��ʼ��APS */
        Aps_Init();

        TAF_SPM_Init();

        /* ��ʼ��SSA */
        SSA_Init();
        /* ��ʼ��GNA */

        /* �Ѿ���lijun,hefeng,xiamiaofangȷ�ϣ�����ɾ�����س�ʼ�� */

        TAF_CSCALL_Init(TAF_CSCALL_INIT_TYPE_STARTUP);

        break;

    default:
        break;
    }

    return VOS_OK;
}

VOS_VOID Taf_ProcCallCtrlAllowNoModification(struct MsgCB * pstMsg)
{
/*
    switch ��������
        case ����:
        if (�ҵ�����CCA_CALL_CTRL_PROCEEDING״̬�ĺ���ʵ��)
        {
            ��Call Control״̬����ΪCCA_CALL_CTRL_END
            ����Cca_CallOrigReqProc
        }
        break;

        #if 0
        case ����ҵ��:
        ����
        break;

        case ����:
        ����
        break;
        #endif

        default:
        break;
*/
}


VOS_VOID Taf_ProcCallCtrlNotAllow(struct MsgCB * pstMsg)
{
/*
    switch ��������
        case ����:
            �����Ӧ��CCA״̬��:
            �ϱ��¼�������ֵΪTAF_ERR_CALL_CONTROL_REJECTED
            break;

        case ����ҵ��:
        case USSDҵ��:
            �����Ӧ��SSA״̬��
            �ϱ��¼�������ֵΪTAF_ERR_CALL_CONTROL_REJECTED
            break;

        case ����:
            �����Ӧ��APS״̬��
            �ϱ��¼�������ֵΪTAF_ERR_CALL_CONTROL_REJECTED
            break;

        default:
            break;

*/

}

VOS_VOID Taf_ProcCallCtrlAllowWithModification(struct MsgCB * pstMsg)
{

/*
    ��������ת������

    switch ��������
        case ����:
            if (�ҵ�����CCA_CALL_CTRL_PROCEEDING״̬�ĺ���ʵ��)
            {
                ���¶�Ӧʵ���״̬��Ϣ
                ����Cca_CallOrigReqProc
            }
            break;

        case ����ҵ��:
        case USSDҵ��:
            if (֮ǰ�Ĳ����ǲ�����SSA�����Call control����)
            {
                ��ն�Ӧ�������ʵ���״̬(CCA����APS)
            }

            ���ù���������(MMI�ִ������������ú�����ʵ�ַ�ʽ����,
                             ��CCA������ɺ�����ȷ��)
            ����SSA�Ľӿ�(�˴�����Ҫ�����°��SSA��ʵ�ַ�ʽ��ȷ��)
            break;

        case ����:
            ����APS��PDP����ӿ�(�˴�����Ҫ�����°��APS��ʵ�ַ�ʽ��ȷ��)
            break;

        default:
            break;

    �ϱ��¼�����֪Ӧ������call control��ԭ�򣬺��з����˸ı�

*/
}

/*****************************************************************************
 �� �� ��  : Taf_ProcSimaMsg
 ��������  : ��������Sima����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  Taf_ProcSimaMsg (struct MsgCB * pstMsg)
{
/*
    switch (��������)
        #ifdef hw_feature_call_control
        case ����Ϊcall control:
        {
            switch (result)
            {
                case �������޸�:
                    ����Taf_ProcCallCtrlAllowNoModification
                    break;

                case ������:
                    ����Taf_ProcCallCtrlNotAllow
                    break;

                case �����޸�:
                    ����Taf_ProcCallCtrlAllowWithModification
                    break;

                default:
                    break;
            }
        }
        break;
        #endif

        default:
        break;

*/
}

/*****************************************************************************
 �� �� ��  : MN_ProcTimerMsg
 ��������  : ����ʱ����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2008��1��10��
   ��    ��   : ���� 49431
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��19��
   ��    ��   : h44270
   �޸�����   : modified by PS Project���޸���Ϣ��ں���
 3.��    ��   : 2014��11��17��
   ��    ��   : w00176964
   �޸�����   : CDMA 1x��Ŀ����5�޸�
*****************************************************************************/
VOS_VOID  MN_ProcTimerMsg (struct MsgCB * pstMsg)
{
    REL_TIMER_MSG * pstTmrMsg = (REL_TIMER_MSG *)pstMsg;

    switch (pstTmrMsg->ulName & MN_TIMER_CLASS_MASK)
    {
    case MN_TIMER_CLASS_CCA:
    case MN_TIMER_CLASS_XCALL:
        TAF_CSCALL_ProcTimerOutMsg((REL_TIMER_MSG *)pstMsg);
        break;

    case MN_TIMER_CLASS_MSG:
        /* ����SMA�Ķ�ʱ����Ϣ������ */
        MN_MSG_ProcTimeoutMsg((REL_TIMER_MSG *)pstMsg);
        break;

    case MN_TIMER_CLASS_SSA:
        /* ����SSA�Ķ�ʱ����Ϣ������ */
        break;

    case MN_TIMER_CLASS_MMA:
        /* ����MMA�Ķ�ʱ����Ϣ������ */
        break;

    case MN_TIMER_CLASS_APS:
        TAF_APS_ProcMsg(pstMsg);
        break;

    default:
        MN_ERR_LOG("MN_ProcTimerMsg: Unknown timer class.");
        break;
    }
}

/* ɾ��ԭ MN_GetUsimMsgClient�ӿں��� */

/*****************************************************************************
 �� �� ��  : MN_GetUsimMsgServerType
 ��������  : ��USIM��������Ϣ�г�ȡҵ������
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��  : 2012��12��26��
    ��    ��  : ���� id:00214637
    �޸�����  : �ο� MN_GetUsimMsgClient ��д����ȡ��Ϣҵ������
  2.��    ��  : 2013��5��15��
    ��    ��  : w00176964
    �޸�����  : SS FDN&Call Control��Ŀ:fdn�ظ����ͳһʹ��client ID,����CALL/MSG��
                FDN���ŵ�SPM�п���ͳһ��SPM�д���
  3.��    ��   : 2013��6��5��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
  4.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
  5.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_UINT32 MN_GetUsimMsgServerType(struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulServerType;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope;

    /*��USIM��������Ϣ�г�ȡҵ������,����FDN IND��Ϣ��Ҫ MSG �� CALLģ�鴦��*/
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        /* �޸���FDN���ظ��Ľṹ,SSʹ��client ID,CALL/MSG��Ҫʹ��client ID�ж� */
        case SI_PB_EVENT_FDNCHECK_CNF:
            ulServerType  = TAF_SERVICE_TYPE_UNASSIGNED;
            break;

        case USIMM_READFILE_CNF:
            ulServerType  = TAF_SERVICE_TYPE_UNASSIGNED;
            break;

        case SI_STK_ENVELOPE_CNF:
            pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
            if (SI_STK_ENVELOPE_CALLCRTL == pstEnvelope->enEnvelopeType)
            {
                ulServerType  = TAF_SERVICE_TYPE_CALL;
            }
            else
            {
                ulServerType  = TAF_SERVICE_TYPE_MSG;
            }
            break;
        default:
            ulServerType  = TAF_SERVICE_TYPE_MSG;
            break;
    }
    return ulServerType;
}

/*****************************************************************************
 �� �� ��  : MN_ProcUsimMsg
 ��������  : ��������USIM����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��12��16��
    ��    ��   : f62575
    �޸�����   : ���Ӷ�PS_USIM_REFRESH_FILE_IND�¼� �Ĵ���
  3.��    ��   : 2011��6��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011062201273 MO SMS CONTROL
  4.��    ��   : 2012��02��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project    Ϊ����FDNҵ��USIM��Ϣ������̰��ͻ����ദ��
  5.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM �ϱ���Ϣ�ķַ�����
  6.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
*****************************************************************************/
VOS_VOID  MN_ProcUsimMsg (struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulServerType;

    ulServerType = MN_GetUsimMsgServerType(pstMsg);

    /* ����ulClient��USIM��Ϣ�ַ�����ҵ����Ŀǰ������ҵ����ģ�� */
    switch(ulServerType)
    {
        case TAF_SERVICE_TYPE_MSG:
            MN_MSG_DispatchUsimMsg(pstMsg);
            break;

        case TAF_SERVICE_TYPE_CALL:
            TAF_CSCALL_ProcUsimMsg(pstMsg);
            break;

        case TAF_SERVICE_TYPE_UNASSIGNED:
            MN_MSG_DispatchUsimMsg(pstMsg);
            TAF_CSCALL_ProcUsimMsg(pstMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            TAF_APS_ProcMsg(pstMsg);

#endif

            break;

        default:
            MN_WARN_LOG("MN_ProcUsimMsg: Rcv Invalid ulClient.");
            break;

    }
    return;
}

/*****************************************************************************
 �� �� ��  : MN_ProcPihMsg
 ��������  : ��������Pih����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  2.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID  MN_ProcPihMsg (struct MsgCB * pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    if (USIMM_STKREFRESH_IND == pstMsgHeader->ulMsgName)
    {
        TAF_CBA_ProcRefreshInd((USIMM_STKREFRESH_IND_STRU *)pstMsgHeader);
        MN_MSG_RcvUsimRefreshInd((USIMM_STKREFRESH_IND_STRU *)pstMsgHeader);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_ProcMmcMsg
 ��������  : ��������Mmc����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : ֧��ALS����
  3. ��    ��   : 2010��12��27��
     ��    ��   : h44270
     �޸�����   : Modified by PS Project, �����µ���Ϣ��������ڣ�ɾ������SPY����Ϣ
  4.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_VOID  MN_ProcMmcMsg (struct MsgCB * pstMsg)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
        case TAFMMC_CBS_NO_NETWORK_IND:
        case TAFMMC_CBS_CURR_NET_MODE_IND:
            TAF_CBA_MsgProc(pstMsg);
            break;
#endif

        case TAFMMC_APS_SERVICE_STATE_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcMmcMsg:Rcv Invalid Msg Type");
            break;
    }
}

/*****************************************************************************
 �� �� ��  : MN_ProcOmMsg
 ��������  : ��������Mmc����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ��������
*****************************************************************************/
VOS_VOID  MN_ProcOmMsg (struct MsgCB * pstMsg)
{
    ID_NAS_OM_INQUIRE_STRU              *pstOmInquire;

    pstOmInquire = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    switch ( pstOmInquire->ulMsgId)
    {
        case ID_NAS_OM_SET_CODEC_TYPE_REQUIRE :
        case ID_NAS_OM_CODEC_TYPE_INQUIRE :
            MN_CALL_ProcOmMsg(pstMsg);
            break;
        case ID_NAS_OM_SET_DSFLOW_RPT_REQ :
            TAF_APS_ProcMsg(pstMsg);
            break;
        default:
            MN_NORM_LOG("MN_CALL_ProcOmMsg:wrong PrimId!");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_ProcUsimStatus
 ��������  : ��������MMA���͵Ŀ���λ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  3.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  4.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : for V9R1 STK������Ŀ
  5.��    ��   : 2013��8��30��
    ��    ��   : l00208543
    �޸�����   : DTS2013082902121
  6.��    ��   : 2013��9��10��
    ��    ��   : z00161729
    �޸�����   : ֧��ss�ط�
  7.��    ��   : 2015��03��14��
    ��    ��   : y00245242
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID MN_ProcUsimStatus(
    struct MsgCB                        * pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU           *pstUsimStatus;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);
    /* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;
    MN_MSG_CfgDataInit(pstUsimStatus->enUsimStatus);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    TAF_CBA_MsgProc(pstMsg);

#endif

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        MN_CALL_LineInfo(pstUsimStatus->enUsimStatus);
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* ��PID init��ȡ�����ؽ�nv��ʱ���ж��Ƿ��ǲ��Կ�������������ʱ�����⵼���жϽ������
       ���������ʱ�ٶ�����һ�ζ�ȡNV�ĺ������ں������ж��Ƿ��ǲ��Կ� */
    MN_CALL_ReadCallRedialCfgNvim();

    MN_CALL_ReadCallRedialCmSrvRejCfgNvim();

    /* ��PID init��ȡss�ؽ�nv��ʱ���ж��Ƿ��ǲ��Կ�������������ʱ������usimδ��ʼ����������usim�ӿ�
       ��ȡ�Ƿ��ǲ��Կ����ز�׼�����жϽ���������������ʱ�ٶ�����һ�ζ�ȡNV�ĺ�����
       �ں������ж��Ƿ��ǲ��Կ� */
    TAF_SSA_ReadSsRetryCfgNvim();

    TAF_SSA_ReadSsRetryCmSrvRejCfgNvim();

}

#ifndef __PS_WIN32_RECUR__
/*****************************************************************************
 �� �� ��  : TAF_RcvMmaOmMaintainInfoInd
 ��������  : ��������MMA��PC���߿�ν�ɲ�������Ϣ
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��24��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_RcvMmaOmMaintainInfoInd(
    struct MsgCB                       *pstMsg
)
{
    MMCM_OM_MAINTAIN_INFO_IND_STRU     *pstOmMaintainInfo;

    pstOmMaintainInfo = (MMCM_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    /* ����ȫ�ֱ�����ֵ */
    g_ucMnOmConnectFlg       = pstOmMaintainInfo->ucOmConnectFlg;
    g_ucMnOmPcRecurEnableFlg = pstOmMaintainInfo->ucOmPcRecurEnableFlg;

    if ( (VOS_TRUE == g_ucMnOmConnectFlg)
      && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
    {
        NAS_MSG_SndOutsideContextData_Part1();
        NAS_MSG_SndOutsideContextData_Part2();
        NAS_MSG_SndOutsideContextData_Part3();
    }
}
#endif
/*****************************************************************************
 �� �� ��  : MN_ProcMmaMsg
 ��������  : ��������Mma����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��11��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��5��13��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS֧��CBS

  3.��    ��   : 2011��3��28��
    ��    ��   : zhoujun /40661
    �޸�����   : USIM��״̬֪ͨ�޸�Ϊ��MMAģ��֪ͨ
  4.��    ��   : 2012��4��24��
    ��    ��   : l00171473
    �޸�����   : DTS2012041805606
  5.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : for V9R1_SVLTE:MSG�յ�MMA CS��������������Ϣ�Ĵ���
  6.��    ��   : 2014��04��26��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����

  7.��    ��   : 2014��10��17��
    ��    ��   : y00218312
    �޸�����   : ����MMA֪ͨAPS����仯�Ĵ���
  8.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
*****************************************************************************/
VOS_VOID  MN_ProcMmaMsg (
    struct MsgCB                        *pstMsg
)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
    case MN_USIM_STATUS_IND:
        MN_ProcUsimStatus(pstMsg);
        break;

#ifndef __PS_WIN32_RECUR__
        case MMCM_OM_MAINTAIN_INFO_IND:
            TAF_RcvMmaOmMaintainInfoInd(pstMsg);

            break;
#endif

        case ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY:
            TAF_MSG_RcvMmaCsServiceChangeNotify(pstMsg);
            break;

        case MMA_TAF_POWER_OFF_IND:
            Aps_PowerOff();
            /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
            break;

        case ID_MMA_TAF_POWER_ON_IND:

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            TAF_APS_ProcMsg(pstMsg);
#endif

            TAF_CSCALL_ProcMmaMsg(pstMsg);
            break;

        case ID_MMA_APS_EPDSZID_INFO_IND:

            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_TAF_1X_SERVICE_STATUS_IND:
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            TAF_APS_ProcMsg(pstMsg);

            break;

        case ID_MMA_APS_CL_SERVICE_STATUS_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_TAF_SYS_CFG_INFO_IND:
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            TAF_APS_ProcMsg(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcMmaMsg:Rcv Invalid Msg Type");
            break;
    }
}

/*****************************************************************************
 �� �� ��  : MN_SndAppMsgToSs
 ��������  : ��AT��STK������Ϣ����SS
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸ĺ�����ڲ���
*****************************************************************************/
VOS_VOID  MN_SndAppMsgToSs (struct MsgCB *pstMsg)
{
    MN_APP_REQ_MSG_STRU                *pstSsMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLen;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
    ulMsgLen    = pstAppMsg->ulLength;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ������Ϣ */
    pstSsMsg = (MN_APP_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);

    if (VOS_NULL_PTR == pstSsMsg)
    {
        MN_WARN_LOG("MN_SndAppMsgToSs: alloc msg fail!");

        return;
    }

    PS_MEM_CPY( ((VOS_UINT8 *)pstSsMsg + VOS_MSG_HEAD_LENGTH), ((VOS_UINT8 *)pstAppMsg+ VOS_MSG_HEAD_LENGTH), ulMsgLen);

    /* �����Ϣͷ */
    pstSsMsg->ulReceiverPid = WUEPS_PID_SS;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSsMsg);

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_SndAppMsgToSs: send msg fail!");
        return;
    }

    return;
}


/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_ProcStkEnvelopeCnf
 ��������  : �ַ�����STK��
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����������
  2.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID TAF_ProcStkEnvelopeCnf(struct MsgCB * pstMsg)
{
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope = VOS_NULL_PTR;

    pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */
    if (SI_STK_ENVELOPE_CALLCRTL != pstEnvelope->enEnvelopeType)
    {
        MN_MSG_RcvUsimEnvelopeCnf(pstMsg);
    }
    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    return;
}
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : MN_DispatchStkMsg
 ��������  : �ַ�����STK����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
                 DTS2011111004869AT PROJECT ��������STK��ҵ��������Ϣ
                 ��ԭ��������TAF�����޸�Ϊʵ�ʵ�STKģ�鷢����
  2.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ
  3.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸���Ϣ�ַ�����
*****************************************************************************/

VOS_VOID MN_DispatchStkMsg(struct MsgCB * pstMsg)
{
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulFuncNum;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    TAF_STK_MSG_FUNC_MAP                pStkMsgFunc = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    ulFuncNum = sizeof(g_astTafStkMsgFuncMap) / sizeof(g_astTafStkMsgFuncMap[0]);

    for (ulLoop = 0; ulLoop < ulFuncNum; ulLoop ++ )
    {
        if (pstMsgHeader->ulMsgName == g_astTafStkMsgFuncMap[ulLoop].ulMsgName)
        {
            pStkMsgFunc             = g_astTafStkMsgFuncMap[ulLoop].pStkMsgFunc;

            /*
                 �����������������ԴPID����STK��ҵ������ṹ��AT��һ�£���Ϣ����һ�£�
                 ��Ϊ�������жϵ���Ϣ������AT����Ϣ�������ｫSTK����Ϣ������ΪAPP����Ϣ��
              */
            pstMsgHeader->ulMsgName = g_astTafStkMsgFuncMap[ulLoop].ulAppMsgName;
            break;
        }
    }

    if (VOS_NULL_PTR == pStkMsgFunc)
    {
        MN_WARN_LOG("MN_DispatchStkMsg: Invalid Msg Name");
        return;
    }

    pStkMsgFunc(pstMsg);

    return;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, begin */
/*****************************************************************************
 �� �� ��  : MN_DispatchTafMsg
 ��������  : �ַ�����TAF����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_DispatchTafMsg (struct MsgCB * pstMsg)
{
    /* TAF->TAF����Ϣ����һ��ͳһ�Ľṹ��,ȡ����Ϣ�ֶ� */
    TAF_INTERNAL_MSG_STRU              *pstTafMsg = VOS_NULL_PTR;

    pstTafMsg = (TAF_INTERNAL_MSG_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgId & ID_TAF_MNTN_MSG_MASK)
    {
        /* ����APS API����Ϣ����APS���� */
        case ID_TAF_APS_INTERNAL_BASE:
            TAF_APS_ProcMsg(pstMsg);
            break;

        /* ���͸�MSG����Ϣ��MSG���� */
        /* Ŀǰֻ��ID_TAF_SPM_SMMA_REQ,MSG�ȷ��͵�SPM������ѡ��,��ѡ��֮���ٵ�MSG���� */
        case ID_TAF_MSG_INTERNAL_BASE:
            TAF_MSG_ProcTafMsg(pstMsg);
            break;

        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
        case ID_TAF_CALL_INTERNAL_BASE:
            TAF_CALL_ProcTafMsg(pstMsg);
            break;
        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, end */

        /* ������Ϣ����Ҫ���� */
        default:
            MN_NORM_LOG("MN_DispatchTafMsg: Unknown message type.");
            break;
    }

    return;
}
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, end */

/*****************************************************************************
 �� �� ��  : MN_DispatchAppMsg
 ��������  : �ַ�����Ӧ�ò����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��07��
    ��    ��   : f00179208
    �޸�����   : AT Project, ɾ����MN_APP_MSG_CLASS_QRY��֧�еĴ���
  3.��    ��   : 2011��12��19��
    ��    ��   : h44270
    �޸�����   : PS Project, �޸�MN_APP_MSG_CLASS_PS��֧�Ĵ��������µĴ�����
  4.��    ��   : 2013��5��19��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:SPM������������Ϣ��Ҫ���͵�SSA��������
  5.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  6.��    ��   : 2013��10��05��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ
*****************************************************************************/
VOS_VOID  MN_DispatchAppMsg (struct MsgCB * pstMsg)
{
    MN_APP_REQ_MSG_STRU * pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    switch (pstAppMsg->usMsgName & MN_APP_MSG_CLASS_MASK)
    {
    case MN_APP_MSG_CLASS_CALL:
        TAF_CSCALL_ProcAppReqMsg(pstMsg);
        break;

    case MN_APP_MSG_CLASS_MSG:
        /* ����SMA API����Ϣ������SMA���� */
        MN_MSG_ProcAppReqMsg(pstAppMsg);
        break;

    case MN_APP_MSG_CLASS_SSA:
        /* ����SSA API����Ϣ������SSA���� */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        MN_SndAppMsgToSs(pstMsg);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
        break;

    case MN_APP_MSG_CLASS_MMA:
        /* ����MMA API����Ϣ������MMA���� */
        break;

    /* Deleted by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-05, begin */
    /* �Ƶ�MN_DispatchTafMsg�д��� */
    /* Deleted by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-05, end */

    case MN_APP_MSG_CLASS_QRY:
        /* AT��MNģ����ѯ���������Ϣ */

        break;

    default:
        MN_ERR_LOG("MN_DispatchAppMsg: Unknown message type.");
        break;
    }
}



/*****************************************************************************
 �� �� ��  : MN_DispatchAppMsg
 ��������  : �ַ�����Ӧ�ò����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2008��1��10��
   ��    ��   : ���� 49431
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��24��
   ��    ��   : h44270
   �޸�����   : modified by PS Project,�޸���Ϣ��ں������˴�����ֱ���滻
*****************************************************************************/
VOS_VOID  MN_DispatchRabmMsg (
    VOS_VOID                            *pstMsg
)
{
    MN_RABM_IND_MSG_STRU                *pstRabmMsg;

    pstRabmMsg = (MN_RABM_IND_MSG_STRU *)pstMsg;

    /* ����RABM������Ϣ��APS��CALL����ģ����д�����MsgName��ȡֵ��Χ
       ��RABM��CALL֮��Ķ����ʱ����������������������ԭ�к������� */
    if (pstRabmMsg->usMsgName > RABM_CALL_MSG_CLASS_BASE)
    {
        MN_CALL_ProcRabmCallPrimitive(pstRabmMsg);
        return;
    }

    TAF_APS_ProcMsg((struct MsgCB *)pstMsg);

}

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : MN_DispatchImsaMsg
 ��������  : �ַ�����IMSA����Ϣ
 �������  : pMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��9��24��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseII ��Ŀ�޸�:����SRVCC�����Ϣ�Ĵ���
*****************************************************************************/
VOS_VOID MN_DispatchImsaMsg (
    VOS_VOID                           *pMsg
)
{
    MSG_HEADER_STRU                   *pstImsaMsg = VOS_NULL_PTR;

    pstImsaMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstImsaMsg->ulMsgName & TAF_IMSA_MSG_MASK)
    {
        case TAF_MSG_IMSA_MSG_BASE:
            /* ��������IMSA��SMS��MSG */
            TAF_MSG_ProcImsaMsg(pstImsaMsg);
            break;

        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-24, begin */
        case TAF_CALL_IMSA_MSG_BASE:
            TAF_CALL_ProcImsaMsg(pstImsaMsg);
            break;
        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-24, end */

        default:
            break;
    }
}
#endif
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : MN_DispatchXccMsg
 ��������  : ��XCC����Ϣ���зַ�����
 �������  : struct MsgCB * pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��25��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  MN_DispatchXccMsg (struct MsgCB * pstMsg)
{
    /* XCC->TAF����Ϣ����һ��ͳһ�Ľṹ��,ȡ����Ϣ�ֶ� */
    MSG_HEADER_STRU                    *pstTafMsg = VOS_NULL_PTR;

    pstTafMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgName & TAF_XCC_TAF_MSG_MASK)
    {
        /* ����APS API����Ϣ����APS���� */
        case TAF_XCC_APS_MSG_BASE:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case TAF_XCC_XCALL_MSG_BASE:
            TAF_XCALL_ProcXccMsg(pstMsg);
            break;

        /* ������Ϣ����Ҫ���� */
        default:
            MN_NORM_LOG("MN_DispatchXccMsg: Unknown message type.");
            break;
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : MN_DispatchMsg
 ��������  : �ַ�TAF FID�յ�����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��2��23��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��AT2D17029�����Ӷ��Ź��������طŹ���
  3.��    ��   : 2011��11��07��
    ��    ��   : f00179208
    �޸�����   : AT Project, �޸�AT�����WUEPS_PID_TAFΪWUEPS_PID_AT
  4.��    ��   : 2011��11��10��
    ��    ��   : f62575
    �޸�����   : DTS2011111004869 STKҵ��������ϢԴPID��ԭ����TAF���ΪMAPS_STK_PID��
                 ����MAPS_STK_PID�¼������֧
  5. ��    ��   : 2010��12��27��
     ��    ��   : h44270
     �޸�����   : Modified by PS Project, �����µ���Ϣ��������ڣ�ɾ������SPY����Ϣ
  6.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  7.��    ��   : 2012��7��13��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseI:֧��TD-SCDMA����ʱ�������Ϣ�������䴦��
  8.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ��չOM��Ϣ�Ĵ���
  9.��    ��   : 2013��5��08��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:���͵�MN����Ϣ���Ⱦ���SPMģ���ȴ���
  10.��    ��   : 2013��6��4��
     ��    ��   : z00161729
     �޸�����   : SVLTE ��usim�ӿڵ����޸�
  11.��    ��   : 2013��6��26��
     ��    ��   : f62575
     �޸�����   : V9R1 STK����
  12.��    �� : 2013��07��08��
     ��    �� : Y00213812
     �޸����� : VoLTE_PhaseI ��Ŀ������TAFģ�����Ϣ����
  13.��    ��   : 2013��09��24��
     ��    ��   : s00217060
     �޸�����   : VoLTE_PhaseII��Ŀ
*****************************************************************************/
VOS_VOID  MN_DispatchMsg (struct MsgCB * pstMsg)
{
    struct MsgCB                      *pstSrcMsg = VOS_NULL_PTR;
    struct MsgCB                      *pstDestMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* svlte���Կ���ʱ��modem1�����յ�usim0����Ϣ����Ҫ����Ϣ��send pid����ת�� */
        pstMsg->ulSenderPid = TAF_SDC_ConvertOamSendPid(pstMsg->ulSenderPid);
    }


    /* ֧��TD-SCDMA����ʱ�������Ϣ�������䴦�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_MsgProc(pstMsg, &pstDestMsg) )
    {
        /* ��Ϣ��UTRANCTRLģ�鴦����ɣ�ֱ�ӷ��أ�������������� */
        return;
    }

    pstSrcMsg = pstDestMsg;

    if (VOS_TRUE == TAF_SPM_MsgProc(pstSrcMsg, &pstDestMsg))
    {
        /* ��Ϣ��SPMģ�鴦�����,ֱ�ӷ���,����Ҫ����������� */
        return;
    }

    /* �滻��Ϣָ�� */
    switch (pstDestMsg->ulSenderPid)
    {
    case VOS_PID_TIMER:
        MN_ProcTimerMsg(pstDestMsg);
        break;

    case UEPS_PID_CST:
        MN_CALL_ProcCstCallPrimitive(pstDestMsg);
        break;

    case MAPS_STK_PID:
        MN_DispatchStkMsg(pstDestMsg);
        break;

    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    case WUEPS_PID_TAF:
    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
        /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, begin */
        MN_DispatchTafMsg(pstDestMsg);
        break;
        /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, end */

    case WUEPS_PID_AT:
        MN_DispatchAppMsg(pstDestMsg);
        break;

    case WUEPS_PID_CC:
        MN_CALL_ProcMnccPrimMsg(pstDestMsg);
        break;

    case WUEPS_PID_MMC:
        MN_ProcMmcMsg(pstDestMsg);
        break;

    case WUEPS_PID_MMA:
        MN_ProcMmaMsg(pstDestMsg);
        break;

    case WUEPS_PID_MM:
        break;

    case WUEPS_PID_SS:
        break;

    case WUEPS_PID_SMS:
        MN_MSG_ProcSmsMsg((VOS_VOID*)pstDestMsg);
        break;

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
#if (FEATURE_IMS == FEATURE_ON)
    case PS_PID_IMSA:
        MN_DispatchImsaMsg((VOS_VOID*)pstDestMsg);
        break;
#endif
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

    case WUEPS_PID_SM:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_ESM:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case MSP_L4_L4A_PID:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

#endif

    case WUEPS_PID_RABM:
        MN_DispatchRabmMsg(pstDestMsg);
        break;

    case UEPS_PID_SN:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case WUEPS_PID_USIM:
    case MAPS_PB_PID:
        MN_ProcUsimMsg(pstDestMsg);
        break;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    case MAPS_PIH_PID:
        MN_ProcPihMsg(pstDestMsg);
        break;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    case MSP_PID_DIAG_APP_AGENT:
        MN_ProcOmMsg(pstDestMsg);
        break;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    case WUEPS_PID_VC:
         TAF_CSCALL_ProcVcMsg(pstDestMsg);
        break;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    case UEPS_PID_GAS:
    case WUEPS_PID_BMC:
#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_ERRC:
#endif
    case WUEPS_PID_WRR:
        TAF_CBA_MsgProc(pstDestMsg);
        break;

#endif

    case UEPS_PID_NDCLIENT:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    case ACPU_PID_TAFAGENT:
        TAF_APS_ProcMsg(pstDestMsg);
        break;
    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    case UEPS_PID_XCC:
        MN_DispatchXccMsg(pstMsg);
        break;

    case MSPS_PID_PPPC:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case UEPS_PID_CDS:
        TAF_APS_ProcMsg(pstDestMsg);
        break;


    case UEPS_PID_XREG:
        TAF_APS_ProcMsg(pstDestMsg);
        break;
    case UEPS_PID_HSM:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_DHCP:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_EHSM:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_XSMS:
        TAF_CSCALL_ProcXsmsMsg(pstMsg);
        break;

    case MSPS_PID_1X_RMAC:
    case MSPS_PID_1X_FMAC:
        TAF_CSCALL_ProcCttfMsg(pstMsg);
        break;
#endif
    default:
        MN_ERR_LOG1("MN_DispatchMsg: Unknown message sender, SenderPid, ", (VOS_INT32)pstMsg->ulSenderPid);
        break;
    }
}


/*****************************************************************************
 �� �� ��  : WuepsTafFidInit
 ��������  : ��ʼ��TAF FID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

extern VOS_UINT32 WuepsVCPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  APP_VC_MsgProc(MsgBlock* pMsg);

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_VOID   At_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
#endif

/*****************************************************************************
 �� �� ��  : WuepsTafFidInit
 ��������  : TAF FID��ʼ������
 �������  : ip - ��ʼ���׶�
 �������  : ��
 �� �� ֵ  : ��ʼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��26��
    ��    ��   : o00132663
    �޸�����   : AT2D19540, ���ź���g_ATCtrSendSem��ǰ��TAF_FID��ʼ��������
                 ��������ֹ����δ������ʹ�õ���ϵͳ���������⡣

  2.��    ��   : 2010��7��20��
    ��    ��   : s62952
    �޸�����   : DTS2010071302886

  3.��    ��   : 2011��10��3��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project: AT PIDע���TAF FID��ɾ���������Դ�������ɾ��������AT AGENT pid
  4.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  5.��    ��   : 2012��5��9��
    ��    ��   : z60575
    �޸�����   : DTS2012050905268, C���������ȼ�����

  6.��    ��   : 2012��6��30��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ����MTAģ��ĳ�ʼ������Ϣ����ע��

*****************************************************************************/
VOS_UINT32 WuepsTafFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{

    VOS_UINT32 ulRslt = VOS_OK;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
            /* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */

            /* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_TAF,
                                        (Init_Fun_Type) MN_Init,
                                        (Msg_Fun_Type) MN_DispatchMsg  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_VC,
                                         (Init_Fun_Type)WuepsVCPidInit,
                                         (Msg_Fun_Type)APP_VC_MsgProc  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            /* Added by l60609 for AT Project��2011-10-03,  Begin*/
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_DRV_AGENT,
                                         (Init_Fun_Type)DRVAGENT_Init,
                                         (Msg_Fun_Type)DRVAGENT_DispatchMsg  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            /* Added by l60609 for AT Project��2011-10-03,  End*/
            #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            /* Added by h00300778 for 1XSMS Project��2014-11-02,  Begin*/
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_XSMS,
                                         (Init_Fun_Type)TAF_XSMS_PidInit,
                                         (Msg_Fun_Type)TAF_XSMS_PidMsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
            #endif
            /* Added by h00300778 for 1XSMS Project��2014-11-02,  End*/

            /* Added by L60609 for AT Project��2011-10-20,  Begin*/
            #if (VOS_WIN32 == VOS_OS_VER)
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AT,
                                         (Init_Fun_Type)At_PidInit,
                                         (Msg_Fun_Type)At_MsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
            #endif
            /* Added by L60609 for AT Project��2011-10-20,  Begin*/


            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_TAF, VOS_PRIORITY_M5);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_MTA,
                                        (Init_Fun_Type)TAF_MTA_InitPid,
                                        (Msg_Fun_Type)TAF_MTA_ProcMsg );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_XPDS,
                                        (Init_Fun_Type)TAF_XPDS_InitPid,
                                        (Msg_Fun_Type)TAF_XPDS_MsgProc );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
#endif
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
    }

    return VOS_OK;
}


#ifdef  __cplusplus
#if  __cplusplus
}
#endif
#endif

