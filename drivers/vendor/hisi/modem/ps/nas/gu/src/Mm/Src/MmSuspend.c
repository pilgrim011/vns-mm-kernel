/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MmSuspend.c
  Author       : s46746
  Version      : V200R001
  Date         : 2005-08-16
  Description  : ��C�ļ�������MMģ��SuspendProc��ģ���ʵ��
  Function List:
        1) MM_GetConnectState
        2) MM_GetMsg
        3) MM_HandleCmMsg
        4) MM_HandleMsg
        5) MM_InsertMsg
        6) MM_RelMsgBuf
        7) MM_Restore
        8) MM_SaveMsg
        9) MM_SndMsgFuncChg
       10) MM_SuspendProc
       11) MM_SuspendTimeout

  History      :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2.  s46746  2006.02.28  �������ⵥA32D02234�޸�
  3.  s46746  2006.02.28  �������ⵥA32D02235�޸�
  4.  s46746  2006.03.01  �������ⵥA32D02192�޸�
  5.  s46746  2006.03.07  �������ⵥA32D02356�޸�
  6.  s46746  2006-03-39  �������ⵥA32D02486�޸�
  7.  s46746  2006-04-17  �������ⵥA32D02829�޸�
  8.  x51137 2006/5/5 A32D03487
  9. ��    ��   : 2006��9��9��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D05803
  10.x51137 2006/11/3 A32D06511
  11.��    ��  : 2006��12��4��
     ��    ��  : luojian id:60022475
     �޸�����  : ���ⵥ��:A32D07777
  12.��    ��   : 2007��01��04��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D06408
  13.��    ��   : 2007��01��25��
     ��    ��   : x51137
     �޸�����   : �������ⵥ�ţ�A32D08545
  14.��    ��   : 2007��07��31��
     ��    ��   : luojian id:60022475
     �޸�����   : ���ⵥ��:A32D12640,MM�ܾ�SS��������Ӧ�û�EST_CNF��Ϣ
  15.��    ��   : 2007��09��05��
     ��    ��   : s46746
     �޸�����   : �������ⵥ�ţ�AT2D01456
  16.��    ��  : 2008��9��4��
     ��    ��  : ouyangfei id:00132663
     �޸�����  : ���ⵥ��:AT2D05490,�ؽ�����֧����ϵͳ�л�
  17.��    ��   : 2009��03��19��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D09743/AT2D10328,WAS�� D/F/P̬�¶�������
  18.��    ��   : 2009��07��24��
     ��    ��   : z40661
     �޸�����   : ��ϵͳ��ѡ�󣬽������в��ܽ�ͨ
  19.��    ��   : 2009��09��25��
     ��    ��   : s46746
     �޸�����   : AT2D14760,��ϵͳ��ѡ��ɺ������ϱ�����������NAS�ϱ�����״̬����ȷ
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Inc.h"
#include "MmSuspend.h"
#include "MmGsmDifMsg.h"
#include "MM_Share.h"
#include "MmCmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_SUSPEND_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/



/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
���ܣ������л��б����MMģ����Ϣ
ȡֵ��Χ��
��ȡ���ĺ�������̣�MM_HandleMsg
                    MM_Restore
                    MM_InsertMsg
                    MM_GetMsg
��ȡʱע�����
*****************************************************************************/
MM_SUSPEND_MSG_BUF_ST gstMmSuspendMsgQue;

MM_TIMER_ST  gstMmTimerSuspend;

extern VOS_UINT32   g_MmSuspendRspOpt;
extern VOS_UINT32   g_MmResumeRspOpt;

/* Deled by x51137 for A32D03487 at 2006/5/5 begin*/
/* extern VOS_UINT8 ucMmProcessFlg; */
/* Deled by x51137 for A32D03487 at 2006/5/5 end*/

/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MM_SaveSuspendInfo
 ��������  : ��RRMM_SUSPEND_IND_ST������ȫ�ֱ�����Ϣ���浽MM��ȫ�ֱ�����
 �������  : pstMsg:MMCת�������Ĺ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : h44270
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��4��1��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:���ӶԶ�Ŀ��RAT�ı���
*****************************************************************************/
VOS_VOID NAS_MM_SaveSuspendInfo(
    MMCMM_SUSPEND_IND_STRU             *pstMsg
)
{
    /* ��g_MmGlobalInfo.stSuspendShare���и�ֵ */
    g_MmGlobalInfo.stSuspendShare.enOldNetType      = pstMsg->ucSuspendOrigen;
    g_MmGlobalInfo.stSuspendShare.ucSuspendCause    = pstMsg->ucSuspendCause;
    g_MmGlobalInfo.stSuspendShare.ucSuspendFlg      = MM_SUSPEND_STATE;

    /*���Ӷ�Ŀ��RAT�ı���*/
    g_MmGlobalInfo.stSuspendShare.enDestSuspendRat  = pstMsg->ucSuspendDestination;

    PS_MEM_CPY(g_MmGlobalInfo.stSuspendShare.astReTxMsg,
                pstMsg->astReTxMsg, sizeof(NAS_RRC_RE_TX_MSG_STRU));
}

/*****************************************************************************
 �� �� ��  : NAS_MM_InitCcoFallbackCtx
 ��������  : ��CCO ����������Ҫ��MM�����Ľ��г�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_InitCcoFallbackCtx(VOS_VOID)
{
    g_MmGlobalInfo.stBackupShare.ucState                    = MM_STATE_NULL;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = MM_STATE_NULL;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = MM_NO_SERVICE;

    g_MmGlobalInfo.stBackupShare.ucNtMod                    = MM_NET_MODE_INVALID;

    g_MmGlobalInfo.stBackupShare.ucCsSigConnFlg             = VOS_FALSE;

    g_MmGlobalInfo.stBackupShare.enCsIntegrityProtect       = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.stBackupShare.usRac                      = 0;

    g_MmGlobalInfo.stBackupShare.ulT3212Value               = 0;

    /* ����LU��Ϣ */
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuType                  = MM_IE_LUT_TYPE_BUTT;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuAttmptCnt             = MM_CONST_NUM_0;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucRetryFlg                = MM_FALSE;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucEnterState              = MM_STATE_NULL;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3212ExpiredFlg         = MM_FALSE;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3213AttmptCnt          = MM_CONST_NUM_0;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucImmAccRejLuAttmptCnt    = MM_CONST_NUM_0;

    /* init CS��ȫ��Ϣ */
    g_MmGlobalInfo.stBackupShare.stCsSecutityInfo = g_MmGlobalInfo.CsSecutityInfo;

    /* init MS CS����Ϣ */
    g_MmGlobalInfo.stBackupShare.stMsCsInfo = g_MmGlobalInfo.MsCsInfo;

    g_MmGlobalInfo.stBackupShare.enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    PS_MEM_CPY(g_MmGlobalInfo.stBackupShare.aucTmsi,
               NAS_MML_GetUeIdTmsi(), NAS_MML_MAX_TMSI_LEN);

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo),
               NAS_MML_GetSimCsSecurity(), sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSuccLai),
               NAS_MML_GetCsLastSuccLai(), sizeof(NAS_MML_LAI_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stBackupEquPlmnInfo),
               NAS_MML_GetEquPlmnList(), sizeof(NAS_MML_EQUPLMN_INFO_STRU));
}


/*****************************************************************************
 �� �� ��  : NAS_MM_BackupCcoFallbackCtx
 ��������  : ��CCO ����������Ҫ��MM�����Ľ��б��ݣ���CCO����ʱ��MMֱ��
              ���Իָ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : h44270
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��03��08��
   ��    ��   : l00130025
   �޸�����   : DTS2012030107623: G->W Est_Rej_Cogest,CCO���˹��̣�Eplmn��ɾ������������פ��
 3.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011082402748:EST CNF fail����CCO����ʱ,3211����Ҫ�ָ�����
*****************************************************************************/
VOS_VOID NAS_MM_BackupCcoFallbackCtx(VOS_VOID)
{
    /* ��g_MmGlobalInfo.stBackupShare���и�ֵ����g_MmGlobalInfo.stBackupShare
       �ĳ�Աȡֵ������g_MmGlobalInfo��������Ա���� */

    g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucState;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucPreState;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;

    g_MmGlobalInfo.stBackupShare.ucNtMod                    = g_MmGlobalInfo.ucNtMod;

    g_MmGlobalInfo.stBackupShare.ucCsSigConnFlg             = g_MmGlobalInfo.ucCsSigConnFlg;

    g_MmGlobalInfo.stBackupShare.enCsIntegrityProtect       = g_MmSubLyrShare.MmShare.ucCsIntegrityProtect;

    g_MmGlobalInfo.stBackupShare.usRac                      = g_MmGlobalInfo.usRac;

    g_MmGlobalInfo.stBackupShare.ulT3212Value               = NAS_MM_GetNetworkT3212RandLen();

    /* ����LU��Ϣ */
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuType                  = g_MmGlobalInfo.LuInfo.ucLuType;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuAttmptCnt             = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucRetryFlg                = g_MmGlobalInfo.LuInfo.ucRetryFlg;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucEnterState              = g_MmGlobalInfo.LuInfo.ucEnterState;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3212ExpiredFlg         = g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3213AttmptCnt          = g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucImmAccRejLuAttmptCnt    = g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt;

    /* ����CS��ȫ��Ϣ */
    g_MmGlobalInfo.stBackupShare.stCsSecutityInfo = g_MmGlobalInfo.CsSecutityInfo;

    /*����MS CS����Ϣ */
    g_MmGlobalInfo.stBackupShare.stMsCsInfo = g_MmGlobalInfo.MsCsInfo;


    g_MmGlobalInfo.stBackupShare.enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    PS_MEM_CPY(g_MmGlobalInfo.stBackupShare.aucTmsi,
               NAS_MML_GetUeIdTmsi(), NAS_MML_MAX_TMSI_LEN);

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo),
               NAS_MML_GetSimCsSecurity(), sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSuccLai),
               NAS_MML_GetCsLastSuccLai(), sizeof(NAS_MML_LAI_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stBackupEquPlmnInfo),
               NAS_MML_GetEquPlmnList(), sizeof(NAS_MML_EQUPLMN_INFO_STRU));


    /* ����T3211�Ķ�ʱ��״̬ */
    g_MmGlobalInfo.stBackupShare.ucT3211Status = gstMmTimer[MM_TIMER_T3211].ucTimerStatus;


}

/*****************************************************************************
 �� �� ��  : NAS_MM_ResumeCcoFallbackCtx
 ��������  : ��CCO �������̣��ָ�CCO���̷���ʱ��MM����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : h44270
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��03��08��
   ��    ��   : l00130025
   �޸�����   : DTS2012030107830: G->W Est_Rej_Cogest,CCO���˹��̣�T3211û��ֹͣ�����´�����LAU,LAU Type����
 3.��    ��   : 2012��03��08��
   ��    ��   : l00130025
   �޸�����   : DTS2012030107623: G->W Est_Rej_Cogest,CCO���˹��̣�Eplmn��ɾ������������פ��
 4.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011082402748:EST CNF fail����CCO����ʱ,3211����Ҫ�ָ�����
*****************************************************************************/
VOS_VOID NAS_MM_ResumeCcoFallbackCtx(VOS_VOID)
{
    /* ��g_MmGlobalInfo�ĳ�Ա������ֵ����ֵ����Դ
       ������g_MmGlobalInfo.stBackupShare */


    VOS_UINT32                                              i;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstBackupEplmnList;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstCurrentEplmnList;

    Mm_ComSetMmState(g_MmGlobalInfo.stBackupShare.ucState);


    g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.stBackupShare.ucPreState;

    g_MmGlobalInfo.ucMmServiceState = g_MmGlobalInfo.stBackupShare.enMmServiceState;

    g_MmGlobalInfo.ucNtMod          = g_MmGlobalInfo.stBackupShare.ucNtMod;

    g_MmGlobalInfo.ucCsSigConnFlg   = g_MmGlobalInfo.stBackupShare.ucCsSigConnFlg;

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect = g_MmGlobalInfo.stBackupShare.enCsIntegrityProtect;

    g_MmGlobalInfo.usRac            = g_MmGlobalInfo.stBackupShare.usRac;

    NAS_MM_SetNetworkT3212RandLen(g_MmGlobalInfo.stBackupShare.ulT3212Value);

    /* ��ԭ LU��Ϣ */
    g_MmGlobalInfo.LuInfo.ucLuType                  = g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuType;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt             = g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuAttmptCnt;
    g_MmGlobalInfo.LuInfo.ucRetryFlg                = g_MmGlobalInfo.stBackupShare.stLuInfo.ucRetryFlg;
    g_MmGlobalInfo.LuInfo.ucEnterState              = g_MmGlobalInfo.stBackupShare.stLuInfo.ucEnterState;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg         = g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3212ExpiredFlg;
    g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt          = g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3213AttmptCnt;
    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt    = g_MmGlobalInfo.stBackupShare.stLuInfo.ucImmAccRejLuAttmptCnt;

    /* ��ԭCS��ȫ��Ϣ */
    g_MmGlobalInfo.CsSecutityInfo = g_MmGlobalInfo.stBackupShare.stCsSecutityInfo;

    /* ��ԭ MS CS����Ϣ */
    g_MmGlobalInfo.MsCsInfo = g_MmGlobalInfo.stBackupShare.stMsCsInfo;

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus)
        {
            gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;
        }
    }




    NAS_MML_SetUeIdTmsi(g_MmGlobalInfo.stBackupShare.aucTmsi);

    NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));

    PS_MEM_CPY(NAS_MML_GetCsLastSuccLai(),
               &(g_MmGlobalInfo.stBackupShare.stCsSuccLai), sizeof(NAS_MML_LAI_STRU));

    pstBackupEplmnList  = &(g_MmGlobalInfo.stBackupShare.stBackupEquPlmnInfo);

    pstCurrentEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == NAS_MML_IsEquPlmnInfoChanged(pstBackupEplmnList))
    {
        /* ��EPLMN���浽MMLȫ�ֱ��� */
        PS_MEM_CPY(pstCurrentEplmnList, pstBackupEplmnList, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

        /* ��EPLMN���µ�NV�� */
        NAS_MM_WriteEplmnNvim(pstCurrentEplmnList);
    }

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
    {
        NAS_MML_SetCsUpdateStatus(g_MmGlobalInfo.stBackupShare.enCsUpdateStatus);

        Mm_ComNasInfoSav(MM_STATUS_ATTACHED, NAS_MML_GetSimCsSecurityCksn());

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
        }
    }


    /* cco֮ǰT3211������CCO���˺�ָ�3211����״̬ */
    if (MM_TIMER_RUNNING == g_MmGlobalInfo.stBackupShare.ucT3211Status)
    {
        Mm_TimerResume(MM_TIMER_T3211);
    }
}



/*****************************************************************************
 Prototype      : MM_SaveMsg
 Description    : �洢��Ϣ
 Input          : pMsg ָ�������Ϣ��ָ��
                  ucEventId �洢��Ϣ�� ID
                  ulLength ��Ϣ����
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function

  2. x51137 2006/5/5 A32D03487
*****************************************************************************/
VOS_VOID MM_SaveMsg(const VOS_VOID* pMsg, VOS_UINT8 ucEventId, VOS_UINT32 ulLength)
{
    /* ��¼�����Ϣ���ڴ�ռ�ָ�� */
    VOS_VOID       *pMsgBuf;

    VOS_VOID       *pMsgSnd;

    NAS_LOG1(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_NORMAL,
                    "STATE MM_SUSPEND_STATE RECEIVE Msg Id",ucEventId);

    /* ��Ϣ�����쳣������������Ϣ */
    if (ulLength > MM_MAX_MSG_LENGTH)
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_SaveMsg: ERROR: Msg length is abnormal!");

        return;
    }

    pMsgBuf = PS_MEM_ALLOC(WUEPS_PID_MM, ulLength);

    if (VOS_NULL_PTR == pMsgBuf) /* ������Ϣ�ռ�ʧ�ܣ�������Ϣ������ */
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                "MM_SaveMsg : ERROR : Alloc Msg Memory Fail!");

        return;
    }
    pMsgSnd = pMsgBuf;

    /* ������Ϣ */
    PS_MEM_CPY(pMsgSnd, pMsg, ulLength);

    /* ���ú��� MM_InsertMsg ������Ϣ */
    MM_InsertMsg(pMsgSnd, ucEventId);
    return;
}


/*****************************************************************************
 Prototype      : MM_SndMsgFuncChg
 Description    : �ı������㷢����Ϣ�ĺ���ָ��
 Input          :
 Output         :
 Return Value   : ��
 Calls          :

 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
  2.��    ��  : 2010��7��10��
    ��    ��  : l00130025
    �޸�����  : ���ⵥ��:DTS2010062601081,2G->3G��ѡ��Nsd�����㣬�������ඪ��������Ϣ
  3.��    ��   : 2011��12��29��
    ��    ��   : l00130025
    �޸�����   : DTS2011082201679/DTS2011121504358,�л�ģʽ�����˺�W/G��ע��״̬û����NASͬ��
*****************************************************************************/
VOS_VOID MM_SndMsgFuncChg()
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* �� GSM ������ */
    {

        /* ����������ĺ���ָ��ָ�� GSM �����µķ��ͺ��� */
        g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc          = MM_GasRrEstReq;
        g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc          = MM_GasRrRelReq;

        /* ���������ݴ���ĺ���ָ��ָ�� GSM �����µķ��ͺ��� */
        g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc     = MM_GasRrDataReq;

        g_NasMmImportFunc.ucFuncEnvironment                 = NAS_MML_NET_RAT_TYPE_GSM;

    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType()) /* �� UMTS ������ */
    {
        g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc          = MM_WasRrEstReq;
        g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc          = As_RrRelReq;

        /* ���������ݴ���ĺ���ָ��ָ�� UMTS �����µķ��ͺ��� */
        g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc     = MM_WasRrDataReq;

        g_NasMmImportFunc.ucFuncEnvironment                 = NAS_MML_NET_RAT_TYPE_WCDMA;

        g_stMmNsd.ucNsdMod                                  = MM_NSD_MOD_R99_ONWARDS;
    }
    else
    {

    }

    return;
}

/*****************************************************************************
 Prototype      : MM_RetransferMsg
 Description    : MMģ�����뿪����״̬�����·��͹���ǰ�����δ���ͳɹ�����Ϣ
 Input          : �����δ�ɹ����͵���Ϣ
 Output         :
 Return Value   : ��
 Calls          :

 Called By      :

 History        : ---
  1.Date        : 2006-12-12
    Author      : s46746
    Modification: Created function
  2.��    ��   : 2011��7��12��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε������滻g_MmSubLyrShare.MmSuspendShare��ȫ�ֱ���
  3.��    ��   : 2011��07��14��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase IIȫ�ֱ��������޸�,�滻classmark2
  4.��    ��   : 2014��04��03��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.CurLai�滻��MML�е�
  5.��    ��   : 2015��08��04��
    ��    ��   : j00174725
    �޸�����   :  DTS2015080400959
*****************************************************************************/
VOS_VOID MM_RetransferMsg()
{
    RRMM_EST_REQ_STRU  *pEstReqMsg;
    VOS_UINT8          *pData = VOS_NULL_PTR;
    RRMM_DATA_REQ_STRU *pDataReqMsg;
    IDNNS_STRU          stIdnnsInfo;
    VOS_INT32           Result = VOS_ERR;
    VOS_UINT8           i;
    VOS_UINT8           ucPd;

    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability;

    pstMsCapability = NAS_MML_GetMsCapability();

    for (i = 0; i < NAS_RRC_MAX_RE_TX_MSG_NUM; i ++)
    {
        if ( NAS_RRC_NULL_RE_TX_MSG == g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType )
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,
                        "MM_RetransferMsg: INFO: Have not message retransfered.!");
            continue;
        }
        else if (NAS_RRC_RE_TX_EST_REQ_MSG == g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType)
        {
            pEstReqMsg = (RRMM_EST_REQ_STRU *)g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].aucNasReTxMsg;

            if (RRC_NAS_CS_DOMAIN != pEstReqMsg->ulCnDomainId)
            {
                continue;
            }
            stIdnnsInfo.ucEnterPara = (VOS_UINT8)pEstReqMsg->enSplmnSameRplmn;
            stIdnnsInfo.ucIdnnsType = (VOS_UINT8)pEstReqMsg->ulIdnnsType;
            switch (g_MmGlobalInfo.ucSuspendPreState)
            {
            case WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING :
                if (g_MmGlobalInfo.stSuspendShare.enOldNetType
                        != NAS_MML_GetCurrNetRatType())
                {
                    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                    {
                        if (MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0])
                        {
                            pEstReqMsg->FisrtNasMsg.ulNasMsgSize -= 5;
                        }
                    }
                    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                    {
                        /*����classmark2*/
                        if (MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0])
                        {
                            pEstReqMsg->FisrtNasMsg.aucNasMsg[pEstReqMsg->FisrtNasMsg.ulNasMsgSize]
                                = 0x33;

                            MM_Fill_IE_ClassMark2(&pEstReqMsg->FisrtNasMsg.aucNasMsg[pEstReqMsg->FisrtNasMsg.ulNasMsgSize+1]);

                            pEstReqMsg->FisrtNasMsg.ulNasMsgSize += 5;
                        }
                    }
                    else
                    {
                    }
                }
                Result = g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc(pEstReqMsg->ulOpId,
                                                           RRC_NAS_CS_DOMAIN,
                                                           pEstReqMsg->ulEstCause,
                                                           &stIdnnsInfo,
                                                           /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                                                           (RRC_PLMN_ID_STRU *)NAS_MML_GetCurrCampPlmnId(),
                                                           /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                                                           pEstReqMsg->FisrtNasMsg.ulNasMsgSize,
                                                           (VOS_INT8*)pEstReqMsg->FisrtNasMsg.aucNasMsg);
                if (VOS_OK != Result)
                {
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_RetransferMsg: Failed RrEstReqFunc.");
                }
                g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
                Mm_ComSetMmState(g_MmGlobalInfo.ucSuspendPreState);
                break;
            case WAIT_FOR_RR_CONNECTION_MM_CONNECTION :
            case WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF :
            case WAIT_FOR_OUTGOING_MM_CONNECTION :
            case WAIT_FOR_RR_CONNECTION_IMSI_DETACH :
                Result = g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc(pEstReqMsg->ulOpId,
                                                           RRC_NAS_CS_DOMAIN,
                                                           pEstReqMsg->ulEstCause,
                                                           &stIdnnsInfo,
                                                           /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                                                           (RRC_PLMN_ID_STRU *)NAS_MML_GetCurrCampPlmnId(),
                                                           /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                                                           pEstReqMsg->FisrtNasMsg.ulNasMsgSize,
                                                           (VOS_INT8*)pEstReqMsg->FisrtNasMsg.aucNasMsg);
                if (VOS_OK != Result)
                {
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_RetransferMsg: Failed RrEstReqFunc.");
                }
                g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
                Mm_ComSetMmState(g_MmGlobalInfo.ucSuspendPreState);
                break;
            default:
                break;
            }
        }
        else if (NAS_RRC_RE_TX_DATA_REQ_MSG == g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType)
        {
            pDataReqMsg = (RRMM_DATA_REQ_STRU *)g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].aucNasReTxMsg;
            if (RRC_NAS_CS_DOMAIN != pDataReqMsg->ulCnDomainId)
            {
                continue;
            }

            pData = (VOS_UINT8 *)pDataReqMsg->SendNasMsg.aucNasMsg;
            ucPd = pData[0] & MM_IE_PD_MASK;
            if ((MM_IE_PD_MM_MSG == ucPd) || (MM_IE_PD_CALL_CONTROL == ucPd)
               || (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucPd))
            {
                g_stMmNsd.ucNsd = (pData[1] >> 6) % g_stMmNsd.ucNsdMod;
            }

            Result = g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc(RRC_NAS_CS_DOMAIN,
                                                            (VOS_UINT8)pDataReqMsg->ulPriorityInd,
                                                            pDataReqMsg->SendNasMsg.ulNasMsgSize,
                                                            (VOS_INT8 *)pDataReqMsg->SendNasMsg.aucNasMsg);
            if (VOS_OK != Result)
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_RetransferMsg: Failed RrEstReqFunc.");
            }
            g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
        }
        else
        {
            g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                        "MM_RetransferMsg: WARNING: Message retransfered type is error.!");
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : MM_Restore
 Description    : MMģ�����뿪����״̬�����Ϣ�Ļָ�����
 Input          : MsgQue �������Ϣ����
 Output         :
 Return Value   : ��
 Calls          :

 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_Restore()
{
    /* ��Ϣ��Ԫ�ṹָ�� */
    MM_SUSPEND_MSG_CELL_ST             *pstMsgCell;

    /* ѭ������ */
    VOS_UINT8                           i;

    /* ����״̬��Ϣ�ṹ */
    MM_MSG_MM_STATUS_STRU               stMsg;

    /* ������Ϣ������ֵ */
    if (gstMmSuspendMsgQue.ucMsgNum < MM_MAX_MSG_NUM)
    {
        /* �ӵ�һ����Ϣ��ʼ�ָ� */
        gstMmSuspendMsgQue.ucIndex      = MM_CONST_NUM_0;
    }

    /* ������������Ϣ��������Ϣ */
    i = gstMmSuspendMsgQue.ucMsgNum;
    for ( ; i > MM_CONST_NUM_0; i --)
    {
        /* ���һ����Ϣ��Ԫ */
        pstMsgCell = MM_GetMsg();
        if (VOS_NULL_PTR == pstMsgCell)
        {
            /* �����������Ϣ */
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_Restore: ERROR: Msg got from Msg buf is NULL!");

            continue;
        }

        if (MM_EVENT_ID_STATUS_95 == pstMsgCell->ucEventId)/* ��Ϣ ID Ϊ MM_EVENT_ID_STATUS_95 */
        {
            /* ������ HSS4100 V100R001 ��ͬ */
            PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

            stMsg.MmIeRjctCause.ucRejCause
                                        = NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG;
            Mm_ComMsgMmStatusSnd(&stMsg);

            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                    "MM_Restore: WARNING: Msg ID is MM_EVENT_ID_STATUS_95,send STATUS!");
        }
        else if (MM_EVENT_ID_STATUS_96 == pstMsgCell->ucEventId)/* ��Ϣ ID Ϊ MM_EVENT_ID_STATUS_96 */
        {
            /* ������ HSS4100 V100R001 ��ͬ */
            PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

            stMsg.MmIeRjctCause.ucRejCause
                                        = NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF;
            Mm_ComMsgMmStatusSnd(&stMsg);

            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                    "MM_Restore: WARNING: Msg ID is MM_EVENT_ID_STATUS_96,send STATUS!");
        }
        else /* ������Ϣ */
        {
            NAS_LOG1(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,
                    "MM_Restore: INFO: After suspend handle msg id.",pstMsgCell->ucEventId);

            /* ���ú��� aMmStateTable ���д��� */
            /*lint -e961*/
            gaMmStateTable[pstMsgCell->ucEventId - 1][g_MmGlobalInfo.ucState]
                    (pstMsgCell->pstMsg);
            /*lint +e961*/
        }

        /* �ͷŴ�����Ϣ��Դ */
        /*VOS_FreeMsg(WUEPS_PID_MM, (MsgBlock* )pstMsgCell->pstMsg);*/
        PS_MEM_FREE(WUEPS_PID_MM, pstMsgCell->pstMsg);
        pstMsgCell->pstMsg              = VOS_NULL_PTR;
    }

    gstMmSuspendMsgQue.ucMsgNum         = 0;
    gstMmSuspendMsgQue.ucIndex          = 0;

    return;
}

/*****************************************************************************
 Prototype      : MM_InsertMsg
 Description    : �򻺴��������һ����Ϣ
 Input          : MsgQue ��Ϣ������еĽṹ
                  pMsg Ҫ���ӵľ�����Ϣ
                  ucEventId ������Ϣ��Ӧ���¼�ID
 Output         :
 Return Value   : MM_TRUE  ������Ϣ�ɹ�
                  MM_FALSE ������Ϣʧ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_InsertMsg(VOS_VOID *pMsg, VOS_UINT8 ucEventId)
{
    /* ��Ϣ��Ԫ�ṹָ�� */
    MM_SUSPEND_MSG_CELL_ST             *pstMsgCell;

    /* ������Ϣ�����ҵ�������Ϣ�����ڻ��������λ�� */
    pstMsgCell = &(gstMmSuspendMsgQue.astMsg[gstMmSuspendMsgQue.ucIndex]);

    if (VOS_NULL_PTR != pstMsgCell->pstMsg)
    {
        /*VOS_FreeMsg(WUEPS_PID_MM, (MsgBlock* )pstMsgCell->pstMsg);*/
        PS_MEM_FREE(WUEPS_PID_MM, pstMsgCell->pstMsg);
        pstMsgCell->pstMsg              = VOS_NULL_PTR;
    }

    /* �� pMsg �� ucEvendId ���浽���������Ӧ����Ϣ��Ԫ�� */
    pstMsgCell->pstMsg                  = pMsg;
    pstMsgCell->ucEventId               = ucEventId;

    /* ��Ϣ��������Ϣ��Ŀ�� 1 */
    if (gstMmSuspendMsgQue.ucMsgNum < MM_MAX_MSG_NUM)
    {
        gstMmSuspendMsgQue.ucMsgNum    += MM_CONST_NUM_1;
    }

    /* ��Ϣ��������Ϣ������ 1 */
    gstMmSuspendMsgQue.ucIndex         += MM_CONST_NUM_1;
    gstMmSuspendMsgQue.ucIndex          = gstMmSuspendMsgQue.ucIndex % MM_MAX_MSG_NUM;

    return;
}

/*****************************************************************************
 Prototype      : MM_GetMsg
 Description    : �ӻ��������ȡ��һ����Ϣ
 Input          : MsgQue ������Ϣ�Ķ���
 Output         :
 Return Value   : ȡ�õľ�����Ϣ
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
MM_SUSPEND_MSG_CELL_ST* MM_GetMsg()
{
    /* ��Ϣ��Ԫ�ṹָ�� */
    MM_SUSPEND_MSG_CELL_ST  *pstMsgCell;

    if (gstMmSuspendMsgQue.ucMsgNum > MM_CONST_NUM_0) /* ������Ϣ��Ŀ������ */
    {
        /* ������Ϣ�����ҵ���ǰ����ȡ��Ϣ��Ԫ */
        pstMsgCell = &(gstMmSuspendMsgQue.astMsg[gstMmSuspendMsgQue.ucIndex]);

        /* ��Ϣ������ 1 */
        gstMmSuspendMsgQue.ucIndex     += 1;
        gstMmSuspendMsgQue.ucIndex      = gstMmSuspendMsgQue.ucIndex % MM_MAX_MSG_NUM;

        /* ��Ϣ��������Ϣ��Ŀ�� 1 */
        gstMmSuspendMsgQue.ucMsgNum    -= 1;

        /* ���� pstMsgCell */
        if (VOS_NULL_PTR == pstMsgCell->pstMsg)
        {
            /* ����ϢΪ�գ���ӡ�쳣 */
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_GetMsg: ERROR: Msg pointer in Msg buf is NULL!");

            return VOS_NULL_PTR;
        }
        return pstMsgCell;
    }
    else
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                    "MM_GetMsg: WARNING: Msg buf is empty!");

        /* ���ؿ�ָ�� */
        return VOS_NULL_PTR;
    }
}

/*****************************************************************************
 Prototype      : MM_RelMsgBuf
 Description    : �ͷŻ��������Ϣ
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_RelMsgBuf()
{
    /* ��Ϣ��Ԫ�ṹָ�� */
    MM_SUSPEND_MSG_CELL_ST             *pstMsgCell;

    /* ������Ϣ������ֵ */
    if (gstMmSuspendMsgQue.ucMsgNum < MM_MAX_MSG_NUM)
    {
        /* �ӵ�һ����Ϣ��ʼ�ͷ� */
        gstMmSuspendMsgQue.ucIndex      = MM_CONST_NUM_0;
    }

    /* �����ͷ���Ϣ��������Ϣ��Դ */
    while (gstMmSuspendMsgQue.ucMsgNum > MM_CONST_NUM_0) /* ������зǿ� */
    {
        /* ���ú��� MM_GetMsg ���һ����Ϣ��Ԫ */
        pstMsgCell = MM_GetMsg();
        if (VOS_NULL_PTR == pstMsgCell)
        {
            /* �����������Ϣ */
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_Restore: ERROR: Msg got from Msg buf is NULL!");

            continue;
        }

        /* �ͷŴ���Ϣ��Ԫ��Դ */
        /*VOS_FreeMsg(WUEPS_PID_MM, (MsgBlock* )pstMsgCell->pstMsg);*/
        PS_MEM_FREE(WUEPS_PID_MM, pstMsgCell->pstMsg);
        pstMsgCell->pstMsg              = VOS_NULL_PTR;
    }

    gstMmSuspendMsgQue.ucIndex          = MM_CONST_NUM_0;
    return;
}

/*****************************************************************************
 Prototype      : MM_SuspendTimeout
 Description    : ������б�����ʱ����ʱ�Ĵ���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function

  2. x51137 2006/5/5 A32D03487
  3.��    ��  : 2006��12��4��
    ��    ��  : luojian id:60022475
    �޸�����  : ���ⵥ��:A32D07777
  4.��    ��   : 2011��7��12��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε������滻g_MmSubLyrShare.MmSuspendShare��ȫ�ֱ���
*****************************************************************************/
VOS_VOID MM_SuspendTimeout()
{
    MMCMM_RESUME_IND_STRU               stResumeInd;;

    NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
            "MM_SuspendTimeout: WARNING: Timer MM_TIMER_PROTECT_SUSPEND expire!");
    #if 0

    if ((MM_TIMER_STOPPED == gstMmTimerSuspend.ucTimerStatus) || (MM_TIMER_ERROR == gstMmTimerSuspend.ucTimerStatus))
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
            "MM_SuspendTimeout: WARNING: Timer MM_TIMER_PROTECT_SUSPEND have been stopped!");

        return;
    }

    gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;

    /* ��ǰ���ڹ���״̬ */
    if (MM_SUSPEND_STATE == g_MmSubLyrShare.MmSuspendShare.ucSuspendFlg)
    {

        /* �ͷŻ��������Դ */
        MM_RelMsgBuf();
    }
    else /* �ǹ���״̬���ָ����������Ϣ */
    {

        /* ���ú��� MM_SndMsgFuncChg �л������㷢����Ϣ�ĺ��� */
        MM_SndMsgFuncChg();

        /* �ñ��¼ MM ���ӵ�ȫ�ֱ���ֵ */
        g_MmSubLyrShare.MmShare.MmSuspendCause = MM_INVALID_SUSPEND_CAUSE;

        /* ���ú��� MM_Restore �����������Ϣ */
        MM_Restore();
    }
    #endif

    /* ��ǰ���ڹ���״̬ */
    if (MM_SUSPEND_STATE == g_MmGlobalInfo.stSuspendShare.ucSuspendFlg)
    {
        /* restart timer */
        if (VOS_OK != Mm_StartRelTimer(&(gstMmTimerSuspend.stTimer),
                                            WUEPS_PID_MM,
                                            gstMmTimerSuspend.ulTimerLength,
                                            MM_TIMER_PROTECT_SUSPEND,
                                            MM_CONST_NUM_0,
                                            VOS_RELTIMER_NOLOOP))
        {
            gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"restart MM_TIMER_PROTECT_SUSPEND fail");
        }
        else
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"restart MM_TIMER_PROTECT_SUSPEND success");
        }
    }
    else /* �ǹ���״̬���ָ����������Ϣ */
    {
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;

        /* ԭ�д����Ǵ���ָ����룬������Mm_Cell_S32_E85�У�ֻ�ж���CS���
           PS��Ľ��������������˸����⴦������ɹ���ԭ�д����ж�Ҳ��
           ��������ģ�����MM�Ż�ʱ����������*/
        stResumeInd.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
        stResumeInd.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
        Mm_Cell_S32_E85( &stResumeInd );
    }

    return;
}


/*****************************************************************************
 Prototype      : Mm_Cell_S3_E84
 Description    : process after MMCMM_SUSPEND_IND
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.��    ��  : 2006��12��4��
    ��    ��  : luojian id:60022475
    �޸�����  : ���ⵥ��:A32D07777
  3.��    ��  : 2008��9��4��
    ��    ��  : ouyangfei id:00132663
    �޸�����  : ���ⵥ��:AT2D05490,�ؽ�����֧����ϵͳ�л�
  4.��    ��   : 2010��09��27��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ��AT2D19560:���ⵥ��AT2D19560:W�ض���GС����NAS�޸ĺ���,��ϵͳ�л�����ǰ���ڽ�������״̬��ģ�ⷢEST_CNF(fail)�����������
  5.��    ��   : 2011��7��12��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε��������ڻ���CCO�����е�MMȫ�ֱ���
  6.��    ��   : 2011��07��28��
    ��    ��   : w00167002
    �޸�����   : v7r1_phaseII �ڲ���Ϣ���͵���
  7.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011082402748:EST CNF fail����CCO����ʱ,3211����Ҫ�ָ�����
  8.��    ��   : 2013��9��22��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseII��Ŀ����:����CS��ȫ�����Ļ�ȡ����
  9.��    ��   : 2015��1��4��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI HO��ʱ���޸�
*****************************************************************************/
VOS_VOID Mm_Cell_S3_E84( VOS_VOID* pMsg )
{
    VOS_UINT8                           i = 0;

    /* ͣMM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO��MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO�Ĵ�����ԭ����ͬ:
       ֻ����CSFB��־����ʱ����ͣ��ʱ��. �����Ҫ��LAU���ȴ�LAU���;�������Ҫ��LAU, MM��ע�������
       ��������²�ͣ��ʱ�����ȶ�ʱ����ʱ */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    /* ���浱ǰSUSPEND��Ϣ�е���Ϣ��MM��ȫ�ֱ����� */
    NAS_MM_SaveSuspendInfo((MMCMM_SUSPEND_IND_STRU*)pMsg);

    if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == ((MMCMM_SUSPEND_IND_STRU*)pMsg)->ucSuspendCause )
      && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState ) )
    {
        /* ����MM��ȫ�ֱ���������CCO����ʱʹ�� */
        NAS_MM_BackupCcoFallbackCtx();
    }

    /* suspend timer except period timer */
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    for ( i=0; i< MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    {
        if ( MM_TIMER_RUNNING == gstMmTimer[i].ucTimerStatus )
        {
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-24, begin */
            /* T3242��T3243��ʱ������ͣ,��Ϊ��Ӧ��INTRAT_CHANGE״̬Ҳ�����˴��� */
            if ((MM_TIMER_T3212 != i)
             && (MM_TIMER_T3242 != i)
             && (MM_TIMER_T3243 != i)
             && (MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE != i))
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-24, end */
            {
                Mm_TimerPause(i);
            }
        }
    }

    g_MmGlobalInfo.ucSuspendPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(MM_INTER_RAT_CHANGE);

    /* ������Ϣ�������������ֵ */
    gstMmSuspendMsgQue.ucIndex  = MM_CONST_NUM_0;

    if (VOS_OK != Mm_StartRelTimer(&(gstMmTimerSuspend.stTimer),
                                            WUEPS_PID_MM,
                                            gstMmTimerSuspend.ulTimerLength,
                                            MM_TIMER_PROTECT_SUSPEND,
                                            MM_CONST_NUM_0,
                                            VOS_RELTIMER_NOLOOP))
    {
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"start MM_TIMER_PROTECT_SUSPEND fail");
    }
    else
    {
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_START;
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"start MM_TIMER_PROTECT_SUSPEND success");
    }

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* L��GU���л�����,����CS��ȫ�����ĵĻ�ȡ���� */
    if  ((MMC_SUSPEND_CAUSE_HANDOVER  == ((MMCMM_SUSPEND_IND_STRU*)pMsg)->ucSuspendCause)
      && (MMC_SUSPEND_ORIGEN_LTE      == ((MMCMM_SUSPEND_IND_STRU*)pMsg)->ucSuspendOrigen))
    {
        /* ����MML�İ�ȫ����������ʧ�ܻ��� */
        PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo),
                   NAS_MML_GetSimCsSecurity(), sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

        /* ����ID_MM_LMM_HO_SECU_INFO_REQ��Ϣ��LMM */
        NAS_MM_SndLmmHoSecuInfoReq();

        /* ����������ʱ��MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF */
        Mm_TimerStart(MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

        return;
    }
#endif

    NAS_MM_SndMmcSuspendRsp();
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_SUSPEND_IND_RECEIVED, 0);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_EndCsfbFlow
 ��������  : ����CSFB���̵Ĵ���
 �������  : enCsfbServiceStatus - CSFB״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 5.��    ��   :2014��6��13��
   ��    ��   :w00242748
   �޸�����   :DSDS III ������
 6.��    ��   :2014��9��20��
   ��    ��   :s00217060
   �޸�����   :cs_err_logԭ��ֵ�ϱ�
 7.��    ��   :2015��10��16��
   ��    ��   :j00174725
   �޸�����   :DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_EndCsfbFlow(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 enCsfbServiceStatus,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause
)
{

    /* LAUЯ��CSMT��־��������ʱ�����б��� */
    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);
    Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

    /* MO CSFB��������L�»ָ�����ΪCSFBʧ�ܣ���CC��SS�ظ�����ʧ�ܣ��建�� */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                            enRelCause);     /* ֪ͨCC����ʧ�� */

            NAS_MM_ClearConnCtrlInfo(MM_IE_PD_CALL_CONTROL);
        }

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* ����CSFB״̬ */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        return;
    }

     /* MO CSFB��������L�»ָ�����ΪCSFBʧ�ܣ���CC��SS�ظ�����ʧ�ܣ��建�� */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == enCsfbServiceStatus)
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, enRelCause);

            NAS_MM_ClearConnCtrlInfo(MM_IE_PD_NON_CALL_RLT_SS_MSG);
        }

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* ����CSFB״̬Ϊ������ */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        return;
    }

    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus)
    {
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                      enRelCause);     /* ֪ͨCC����ʧ�� */

        /* Mm_RcvCcEstReq�����ж�����ǽ�����������ucEstingCallTypeFlg����Ҫ��� */
        if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg = MM_FALSE;
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        NAS_MM_ClearConnCtrlInfo(MM_IE_PD_CALL_CONTROL);

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* ����CSFB״̬Ϊ������ */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        return;
    }

    /* ��ǰ����CSFB���� */
    if (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbServiceStatus)
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* ����CSFB״̬Ϊ������ */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
        /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
    }

    return;
}


/*****************************************************************************
�� �� ��  : NAS_MM_ResumeBackToGU_CSFB
��������  : CSFB������ϵͳ�任��GU
�������  : enCsfbServiceStatus - CSFB״̬
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��2��14��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2012��3��27��
  ��    ��   : w00166186
  �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
3.��    ��   : 2014��05��30��
  ��    ��   : s00217060
  �޸�����   : ֧��ultra_flash_csfbʱ���յ�resume_indֱ�ӷ�cm_service_request,����MO CSFB�绰��ͨ�ٶ�
*****************************************************************************/
VOS_VOID NAS_MM_ResumeBackToGU_CSFB(
    MMCMM_RESUME_IND_STRU                                  *pstResumeInd,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus
)
{
    VOS_UINT8                                               ucUltraFlashCsfbFlg;

    ucUltraFlashCsfbFlg = NAS_MML_GetUltraFlashCsfbSupportFlg();

    if (MMC_RESUME_RESULT_SUCCESS != pstResumeInd->ucCsResumeResult)
    {
        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_RESUME_TO_GU_FAIL,
                                  NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CSFB MT�쳣 */
        NAS_MM_CsfbMtFailRecord();
#endif

        /* ��ϵͳʧ�ܣ���ΪCSFB����ʧ�� */
        NAS_MM_EndCsfbFlow(enCsfbServiceStatus, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL);
        return;
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_RESUME_IND_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    /* ֻ����CSFB��־����ʱ�Ż��ߵ����� */
    if (MMC_SUSPEND_CAUSE_HANDOVER == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
    {
        /* CSFB����֧��HO��GU,MM_CONNECTION_ACTIVE�յ�resume_indֱ�ӷ�cm_service_request,����MO CSFB�绰��ͨ�ٶ� */
        /* MTʱ����Ҫ��cm_service_request��ֱ�ӵ������setup_ind */
        if ((VOS_TRUE             == ucUltraFlashCsfbFlg)
         && (MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState))
        {
            Mm_ComCheckDelayMmConn(MM_FALSE);

            NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_CS_HO_WAIT_SYSINFO);
        }
        else
        {
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus)
            {
                /* ������ϵͳ��Ϣ�Ķ�ʱ�� */
                NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
            }
            else
            {
                NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
            }
        }
    }

}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcResumeIndBackToLTE
 ��������  : ������ϵͳ�ص�LTE���յ�resume ind��Ϣ�Ĵ���
 �������  : pstResumeMsg----MMC��resume ind��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��18��
   ��    ��   : w00242748
   �޸�����   : DTS2014011302424:L�����У�CSFBʧ�ܣ����˵�L��MMģ���CCģ�鷢��
                �ͷ��������󣬵绰ҵ����ֹ��Ϊ����û����飬������˵�L�Ļ�������
                ����������
 3.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
 4.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�
 5.��    ��   : 2015��10��16��
   ��    ��   : j00174725
   �޸�����   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToLTE(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    VOS_UINT8                           ucTimerId;

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /* ֹͣ����CSFB MT������ʱ����������ж�ʱ�� */
        ucTimerId = MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE;
        NAS_MM_TimerStopExceptSpecialTimers(1, &ucTimerId);
    }
    else
    {
        /* ֹͣ����T3212��������ж�ʱ�� */
        ucTimerId = MM_TIMER_T3212;
        NAS_MM_TimerStopExceptSpecialTimers(1, &ucTimerId);
    }


    g_MmGlobalInfo.enPreRatType = NAS_MML_NET_RAT_TYPE_LTE;


    /* W��ϵͳ��LTE�����������ע�Ὠ��ʧ�ܴ��� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
    }

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    /* LTE��GU��handover����,���˵�LTEʱ��Ҫ����CS�İ�ȫ������ */
    if ((MMC_SUSPEND_CAUSE_HANDOVER == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_LTE   == g_MmGlobalInfo.stSuspendShare.enOldNetType))
    {
        NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));
    }

#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MM_GetSrvccFlg())
    {
        NAS_MM_ProcResumeIndBackToLTE_Srvcc();
    }
#endif
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    /* Modified by z00234330 for ISR���Է�������, 2013-3-25, begin */
    NAS_MM_ChgStateIntoLMode();
    /* Modified by z00234330 for ISR���Է�������, 2013-3-25, end */

    /* ���MML�е�CS���������Ϣ */
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);

    if (MM_CS_SIG_CONN_ABSENT != g_MmGlobalInfo.ucCsSigConnFlg)
    {
        g_MmGlobalInfo.ucCsSigConnFlg  = MM_CS_SIG_CONN_ABSENT;

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);


    /* ��ϵͳʧ�ܻ��˵�LTEʱ����¼�쳣״̬ΪCSFB MT�������� */
    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LTE_RESUME_IND_RECEIVED,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE);


    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* ��ϵͳ�ػ�LTE������Ҫ��MMC�������� */
        NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE);

    }
    else
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE);

        NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

        Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

        NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CSFB MT�쳣 */
        NAS_MM_CsfbMtFailRecord();
#endif
    }

    MM_RelMsgBuf();

    return;
}

#endif

/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcResumeToHRPD
 ��������  : ������ϵͳ��HRPD���յ�resume ind��Ϣ�Ĵ���
 �������  : pstResumeMsg----MMC��resume ind��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��1��27��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeToHRPD(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    /* ֹͣ���еĶ�ʱ�� */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* ״̬Ǩ�Ƶ��޷���״̬ */
    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* ���MML�е�CS���������Ϣ */
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);

    if (MM_CS_SIG_CONN_ABSENT != g_MmGlobalInfo.ucCsSigConnFlg)
    {
       g_MmGlobalInfo.ucCsSigConnFlg  = MM_CS_SIG_CONN_ABSENT;

       NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    /* �ͷ�����MM���� */
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD);

    /* �ͷŹ�������еĻ��� */
    MM_RelMsgBuf();

    return;
}
#endif
/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

/*****************************************************************************
 �� �� ��  : NAS_MM_ResumeSuspendInfo
 ��������  : �ָ�������Ϣ
 �������  : pstResumeMsg--MMCת��������resume ind��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ResumeSuspendInfo(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    VOS_UINT8                           i;

    /* �����CCO���˵��µĹ���ԭ����ָ������� */
    if ((MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
     && (MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.stBackupShare.ucState))
    {
        NAS_MM_ResumeCcoFallbackCtx();
    }
    else if (TEST_CONTROL_ACTIVE !=  g_MmGlobalInfo.ucSuspendPreState)
    {
        /* ��Ϊ��ǰΪ����״̬,�����ʱ���ݴ�״̬,����Ҫ�ָ���ԭ����״̬ʱ,
           �ᵼ��MM״̬����,���Դ�ʱ���ܱ���ԭ����״̬ */
        /* g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState; */
        Mm_ComSetMmState(g_MmGlobalInfo.ucSuspendPreState);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ResumeSuspendInfo:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    }

    /* resume timer  */
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus )
        {
            /* CCO����ʱ,����ģʽ���,3211ͨ�����ݵ�״̬�ָ����� */
            if ((g_MmGlobalInfo.stSuspendShare.enOldNetType != NAS_MML_GetCurrNetRatType())
             && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK      == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
             && (MM_TIMER_T3211 == i))
            {
                continue;
            }

            Mm_TimerResume(i);
        }
    }

    /* ֹͣ������б�����ʱ�� */
    if ( MM_TIMER_START == gstMmTimerSuspend.ucTimerStatus )
    {
        if (VOS_OK != Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_PROTECT_SUSPEND, &(gstMmTimerSuspend.stTimer)))
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"Stop MM_TIMER_PROTECT_SUSPEND fail.");
        }
        else
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"Stop MM_TIMER_PROTECT_SUSPEND success");
        }
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcResumeIndInterSysChanged
 ��������  : ������ϵͳ�任��GU���յ�resume ind����Ϣ����
 �������  : pstResumeMsg--MMCת��������resume ind��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndInterRatChangedToGU(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    RRMM_EST_CNF_STRU                  *pucNasMsg = VOS_NULL_PTR;

    /* ���뼼�������ı� ɾ��RRC���� */
    if (MMC_SUSPEND_CAUSE_HANDOVER != g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
    {
        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
    }

    if (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
    {
        /* MM ״̬Ǩ�ص�������ǰ��״̬ */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    /* ���������ϵͳ��ı䣬��Ҫ֪ͨ�����PTMSI��Ϣ */
    NAS_MM_NotifyAsInfoChgReq();

    /* ��ϵͳ�л�W��G */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;
    }

    if ((g_MmGlobalInfo.ucState  == WAIT_FOR_RR_CONNECTION_IMSI_DETACH)
     || ((g_MmGlobalInfo.ucState == WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF)
      && (g_MmGlobalInfo.ucCsSigConnFlg != MM_CS_SIG_CONN_PRESENT)))
    {
        g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
        pucNasMsg  = (RRMM_EST_CNF_STRU *)MM_MEM_ALLOC(VOS_MEMPOOL_INDEX_MM,
                                  sizeof(RRMM_EST_CNF_STRU),WUEPS_MEM_NO_WAIT);
        if( VOS_NULL_PTR == pucNasMsg )
        {
            /* �ڴ�����ʧ��                             */
             PS_NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR, "NAS_MM_ProcResumeIndInterRatChangedToGU:ERROR: MALLOC RRMM_EST_CNF_STRU ERROR!");
             return;
        }

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            pucNasMsg->MsgHeader.ulSenderPid = UEPS_PID_GAS;
        }
        else
        {
            pucNasMsg->MsgHeader.ulSenderPid = WUEPS_PID_WRR;
        }

        pucNasMsg->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
        pucNasMsg->ulCnDomainId            = RRC_NAS_CS_DOMAIN;
        pucNasMsg->ulOpId                  = g_MmGlobalInfo.ucRrEstReqOpid;
        pucNasMsg->ulResult                = RRC_EST_RJ_UNSPEC;
        /*lint -e961*/
        gaMmStateTable[32 - 1][g_MmGlobalInfo.ucState](pucNasMsg);/* the event of RRMM_REL_IND is 32 */
        /*lint +e961*/
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucNasMsg );
    }
    else if ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
          || (LOCATION_UPDATING_INITIATED              == g_MmGlobalInfo.ucState))
    {
        NAS_MM_ProcInterRatReselInLuProcedure();
    }
    else
    {
        if (g_MmGlobalInfo.ucCsSigConnFlg != MM_CS_SIG_CONN_PRESENT)
        {
            g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;

            NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);
        }
    }

     /* W��ѡ/CCO��G��CS���ӿ϶������ڣ���Ҫ�ϲ������ͷ� */
    if (((MMC_SUSPEND_CAUSE_CELLCHANGE   == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
      || (MMC_SUSPEND_CAUSE_CELLRESELECT == g_MmGlobalInfo.stSuspendShare.ucSuspendCause))
     && (MM_CS_SIG_CONN_PRESENT          == g_MmGlobalInfo.ucCsSigConnFlg))
    {
        /* ����֮ǰ����̬���ܻ��յ�ϵͳ��Ϣ����ϵͳ��ѡ������������ϱ�ϵͳ��Ϣ��
        ���֮ǰ�����ϵͳ��Ϣ�����ٴ���LAU����Ҫ��� */
        g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /*����MM_RelMsgBuf�ͷŻ�����Ϣ*/
        MM_RelMsgBuf();

        Mm_RcvRrmmRelInd();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcResumeIndBackToGU
 ��������  : ������ϵͳ�ص�GU���յ�resume ind��Ϣ�Ĵ���
 �������  : pstResumeMsg--MMCת��������resume ind��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��19��
   ��    ��   : s00217060
   �޸�����   : coverity����
 3.��    ��   : 2014��4��08��
   ��    ��   : y00245242
   �޸�����   : warning����
 4.��    ��   : 2014��12��13��
   ��    ��   : s00217060
   �޸�����   : ����״̬��ʾ�Ż�PhaseI ��ϵͳ�л������޸�
 5.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToGU(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8  enCsfbStatus;
#endif
    /* Modified by s00217060 for coverity����, 2014-02-19, begin */
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT8                               ucSrvccFlg;
#endif
    /* Modified by s00217060 for coverity����, 2014-02-19, end */
    /* W��ϵͳ��GSM�����������ע�Ὠ��ʧ�ܴ��� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
    }

    /* ��ϵͳ�л�����ǰ���ڽ�������״̬��ģ�ⷢEST_CNF(fail)����������� */
    if (NAS_MML_GetCurrNetRatType() != g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        NAS_MM_ProcResumeIndInterRatChangedToGU(pstResumeMsg);
    }

#if (FEATURE_ON == FEATURE_IMS)
    ucSrvccFlg      = NAS_MM_GetSrvccFlg();

    if (VOS_TRUE == ucSrvccFlg)
    {
        NAS_MM_ProcResumeIndBackToGU_Srvcc();
    }
#endif

#if (FEATURE_ON == FEATURE_LTE)
    enCsfbStatus    = NAS_MML_GetCsfbServiceStatus();

    if (NAS_MML_NET_RAT_TYPE_LTE == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        /* Modified by s00217060 for coverity����, 2014-02-19, begin */
        if ( (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
          && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enCsfbStatus) )
        /* Modified by s00217060 for coverity����, 2014-02-19, end */
        {
            NAS_MM_ResumeBackToGU_CSFB((MMCMM_RESUME_IND_STRU*)pstResumeMsg, enCsfbStatus);
        }

        /* ��SRVCC����,LTE�л���GU����Ҫ����CS�İ�ȫ������,��֤RRC�յ�resume rsp��ȡCK/IK����ȷ�� */
        if ((MMC_SUSPEND_CAUSE_HANDOVER == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
#if (FEATURE_ON == FEATURE_IMS)
         && (VOS_FALSE                  == ucSrvccFlg)
#endif
            )
        {
            NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));
        }
    }
#endif

    /* GU֮����л�ҲҪ����ʱ����ϵͳ��Ϣ����ʱ����ʱ֮��MMC����ϵͳ��Ϣ֪ͨMMA,��֪ͨMMA����״̬ */
    /* GU֮����л����ֲ������Ƿ�Ϊ�������ˣ�ͳһ��LTE��HO��GU�Ķ�ʱ��ʱ����ʱ��NV������ */
    if (VOS_TRUE == NAS_MM_IsHoBetweenGU(g_MmGlobalInfo.stSuspendShare.enOldNetType,
                                          NAS_MML_GetCurrNetRatType(),
                                          g_MmGlobalInfo.stSuspendShare.ucSuspendCause))
    {
        NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcSrvccSuccess
 ��������  : SRVCC�ɹ��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
 3.��    ��   : 2014��05��30��
   ��    ��   : s00217060
   �޸�����   : ultra flash csfbʱ����Ҫ֪ͨccģ��srvcc�ɹ�

 4.��    ��   : 2014��12��16��
   ��    ��   : w00167002
   �޸�����   : DTS2014120200900:��SRVCC�󣬶Զ˷�DISC��Я����TI�쳣��Ϊ8����Ϊ��ǰ
                �������У�CC֪ͨTI ���Ϸ���֪ͨMM REL, ����ACTIVE״̬�յ�REL����
                ״̬Ǩ�Ƶ���MM NULL,��Ҫ�����ͷź��ԭ��ֵ��
 5.��    ��   : 2015��11��11��
   ��    ��   : c00318887
   �޸�����   : DTS2015110909408 IMS�绰��ͨ��L handover ��W���绰����û��LAU
****************************************************************************/
VOS_VOID NAS_MM_ProcSrvccSuccess(VOS_VOID)
{
    /* 3GPP.24008 Э���й���SRVCC������MM�Ĵ���:
    An MM connection can be established locally in the MS due to an SRVCC handover (see 3GPP TS 23.216 [126]), i.e.
    without dedicated MM signalling. That is the case when the MS has a voice media stream carried over the PS domain
    that is handed over to the CS domain in A/Gb mode or Iu mode via SRVCC.
    An MS in MM state MM IDLE shall establish the MM connection locally when it receives an indication from lower
    layers that a SRVCC handover was completed successfully.
    After completing MM connection establishment, MM layer shall indicate "MM connection establishment due to
    SRVCC handover" to upper layer and shall enter state MM CONNECTION ACTIVE. */

    if (VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* ֪ͨCCģ��SRVCC�ĳɹ���� */
        NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_SUCCESS);

        /* ͨ��������ϢID_MM_LMM_SRVCC_STATUS_NOTIFY֪ͨLMM��ǰSRVCC �ɹ� */
        NAS_MM_SndLmmSrvccStatusNotify(NAS_MMCC_SRVCC_STATUS_SUCCESS);

        /* CS HOʱ(����SRVCC)������ϵͳ��Ϣ�Ķ�ʱ�����������㲻��ϵͳ��Ϣ����ʱ����ʱ��MMC����ϵͳ��Ϣ��MMA��֪���뼼���仯 */
        NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

    /* ��¼��ǰMM�����̱���Լ���������ʱMM��״̬ */
    Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucSuspendPreState;


    /* ��SRVCC����ACTIVE״̬�յ�REL����״̬Ǩ�Ƶ���MM NULL,��Ҫ�����ͷź��ԭ��ֵ */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;

    /* Ǩ��״̬��MM CONNECTION ACTIVE */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);

    /* ����RRC���Ӵ��� */
    NAS_MML_SetRrcConnStatusFlg(VOS_TRUE);

    /* ����MM�������Ӵ��� */
    NAS_MML_SetCsSigConnStatusFlg(VOS_TRUE);
    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;

    /* ֪ͨGMM��MMC��ǰCS�������Ӵ��� */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);

    /* ֪ͨMMC��ǰCSҵ���Ѿ����� */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

    /* ����CSҵ������״̬ */
    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    /* 3GPP 24007 11.2.3.2.3.2 The  sequenced message transfer operation is initiated by establishing
    a RR connection.The send state variables V(SD) are set to 0.After successful completion of SRVCC
    handover (see 3GPP TS 23.216 [27]), the mobile station shall set the send state variable V(SD) to 0.*/
    g_stMmNsd.ucNsd = MM_NSD_INITAL_VALUE;

    /* д���ļ� */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcSrvccFail
 ��������  : SRVCCʧ�ܵĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��10��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��05��30��
   ��    ��   : s00217060
   �޸�����   : ultra flash csfbʱ����Ҫ֪ͨccģ��srvcc�ɹ�
****************************************************************************/
VOS_VOID NAS_MM_ProcSrvccFail(VOS_VOID)
{
    /* ����CS�İ�ȫ������ */
    NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));

    if (VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* ���ͬ��������TI��Ϣ */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = MM_CONST_NUM_0;

        /* ֪ͨCCģ��SRVCC��ʧ�ܽ�� */
        NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_FAIL);

#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_SrvccFailRecord(NAS_ERR_LOG_SRVCC_FAIL_RESUME_IND_BACK_TO_LTE);
#endif
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcSrvccNoCallNum
 ��������  : SRVCCЯ��CALLNUMΪ0�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��10��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
****************************************************************************/
VOS_VOID NAS_MM_ProcSrvccNoCallNum(VOS_VOID)
{
    /* �ͷ�RRC���� */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucState;
    Mm_TimerStart(MM_TIMER_T3240);

    /* MM״̬Ǩ�� */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);

    Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);

    /* ֪ͨCCģ��SRVCC��ʧ�ܽ�� */
    NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_FAIL);

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_SrvccFailRecord(NAS_ERR_LOG_SRVCC_FAIL_NO_CALL_NUM);
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcResumeIndBackToGU_Srvcc
 ��������  : SRVCC�������յ�resume ind�е�GU�µĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��9��24��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��10��
   ��    ��   : f00179208
   �޸�����   : DTS2015100907818:BSRVCC�ĳ�����IMSA����TAFͬ��CALLINFO��Ϣ������MM/TAF��״̬�쳣��
                ���IMSA��ͬ��CALLINFO��Ϣ������SRVCCʧ�ܴ����ͷ�RRC����
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToGU_Srvcc(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucRcvSrvccCallInfoFlg;

    ucRcvSrvccCallInfoFlg               = NAS_MM_GetRcvSrvccCallInfoFlg();
#endif

    /* ���SRVCC���̱�� */
    NAS_MM_SetSrvccFlg(VOS_FALSE);

#if (FEATURE_ON == FEATURE_LTE)
    /* ����ǰ���뼼��ΪLTE,�����ΪGU,˵��SRVCC�ɹ� */
    if (NAS_MML_NET_RAT_TYPE_LTE == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
#if 0
        /* ���MMδ�յ�CC��ͬ��TI��Ϣ,���ʱ����������,��Ϊ�쳣,����SRVCCʧ�ܴ��� */
        if (MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
        {
            NAS_MM_ProcSrvccFail();

            return;
        }
#endif
        /* ���SRVCC�����յ�CALLINFO�ı�ʶ */
        NAS_MM_SetRcvSrvccCallInfoFlg(VOS_FALSE);

        /* ����յ�CCͬ��������CALLINFO��CALLNUMΪ0 */
        if ((VOS_TRUE       == ucRcvSrvccCallInfoFlg)
         && (MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
         && (MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]))
        {
            NAS_MM_ProcSrvccNoCallNum();

            return;
        }

        NAS_MM_ProcSrvccSuccess();
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcResumeIndBackToLTE_Srvcc
 ��������  : SRVCC�������յ�resume ind�е�LTE�µĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��9��24��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToLTE_Srvcc(VOS_VOID)
{
    /* ���SRVCC���̱�� */
    NAS_MM_SetSrvccFlg(VOS_FALSE);

    /* ������RAT��ԭʼRAT����(����ͬ��������MM��TI FLAGΪ0,��Ϊδ�յ�CCͬ��TI����Ϣ,�쳣
       ����),����L��GU��SRVCCʧ��,�ָ�CS��ȫ������ */
    if (NAS_MML_NET_RAT_TYPE_LTE == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        NAS_MM_ProcSrvccFail();
    }

    return;
}

#endif
#endif
/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-24, end */


/* Added by z00234330 for ISR���Է�������,dts2013041604521 2013-3-25, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_ChgStateIntoLMode
 ��������  : Ǩ�Ƶ�Lģ��MMǨ�Ʒ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��25��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MM_ChgStateIntoLMode( VOS_VOID )
{
    if ( VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
    {
        return;
    }

    switch ( g_MmGlobalInfo.ucState )
    {
        case WAIT_FOR_OUTGOING_MM_CONNECTION :
        case MM_CONNECTION_ACTIVE:
        case WAIT_FOR_RR_CONNECTION_MM_CONNECTION:
        case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
        case WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF:
        case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        case PROCESS_CM_SERVICE_PROMPT:
        case TEST_CONTROL_ACTIVE:
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            break;
        case WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING :
        case LOCATION_UPDATING_INITIATED :
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            break;
        case LOCATION_UPDATE_REJECTED :
            Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            break;
        case WAIT_FOR_NETWORK_COMMAND :
            if ( MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc )
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }
            else if ( MM_LU_PROC == g_MmGlobalInfo.ucProc )
            {
                Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            }
            break;
        default:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            break;
    }

}

/* Added by z00234330 for ISR���Է�������,dts2013041604521 2013-3-25, end */


/*****************************************************************************
 Prototype      : Mm_Cell_S32_E85
 Description    : process after MMCMM_RESUME_IND
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.��    ��  : 2006��12��4��
    ��    ��  : luojian id:60022475
    �޸�����  : ���ⵥ��:A32D07777
  3.��    ��   : 2007��01��04��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D06408
  4.��    ��  : 2008��9��4��
    ��    ��  : ouyangfei id:00132663
    �޸�����  : ���ⵥ��:AT2D05490,�ؽ�����֧����ϵͳ�л�
  5.��    ��   : 2009��03��19��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D09743/AT2D10328,WAS�� D/F/P̬�¶�������
  6.��    ��   : 2009��9��18��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D14551,����ģʽII��,��2Gͨ��PCCO���̵�3G��,��W�·����RRC��������ԭ��ֵ������Э��Ҫ��
  7.��    ��   : 2010��05��14��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:AT2D19292,MM��Ѱ����������ʱ���յ�ϵͳ��Ϣ����״̬Ǩ��NORMAL״̬������GCFʧ��
  8.��    ��   : 2010��09��27��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ��AT2D19560:W�ض���GС����NAS�޸ĺ���,��ϵͳ�л�����ǰ���ڽ�������״̬��ģ�ⷢEST_CNF(fail)�����������
  9.��    ��   : 2011��3��3��
    ��    ��   : z00161729
    �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
 10.��    ��   : 2011��7��12��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε��������ڻָ�CCO�����е�MMȫ�ֱ���,�滻g_MmSubLyrShare.MmSuspendShare��ȫ�ֱ���
 11.��    ��   : 2011��07��15��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2011071101580, ϵͳ����ѡ����ʧ��
 12.��    ��   : 2011��12��25��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2011122307328, ע���������ѡ������MMC����
 13.��    ��   : 2011��12��1��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����:RRC����ά������
 14.��    ��   : 2012��03��08��
    ��    ��   : l00130025
    �޸�����   : DTS2012030107830: G->W Est_Rej_Cogest,CCO���˹��̣�T3211û��ֹͣ�����´�����LAU,LAU Type����
 15.��    ��   : 2012��04��24��
    ��    ��   : w00166186
    �޸�����   : DTS2012042303735����L CCO��G������ѡ��L����һ��TAUʧ��
 16. ��    ��   : 2012��2��14��
     ��    ��   : z00161729
     �޸�����   : V7R1C50 ֧��CSFB�����޸�
 17.��    ��   : 2012��04��11��
    ��    ��   : z00161729
    �޸�����  : csfb mt L�ض���Wʧ�ܻ��˵�L����csfb mtʧ��
 16.��    ��   : 2012��05��21��
    ��    ��   :  z40661
    �޸�����  :  DTS2012052308001:��L��ѡ��G�󷴸�����LAU
 17.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1��CS��������������ѡ��L��û�����GMM��CS���ӱ�־
 18.��    ��   : 2012��10��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
 19.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 20.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011082402748:EST CNF fail����CCO����ʱ,3211����Ҫ�ָ�����
 21.��    ��   : 2013��3��25��
    ��    ��   : z00234330
    �޸�����   : ISR���Է�������,W����̬��Lģ���ػ�ʱ��MM��֪ͨWRR����detach
 22.��    ��   :2013��8��13��
    ��    ��   :z00161729
    �޸�����   :DTS2013081207431:mm����״̬�յ�cc��t303��ʱabort��Ϣ����Ҫ���棬�յ�resume indʱ�ٴ���
 22.��    ��   :2013��9��23��
    ��    ��   :w00242748
    �޸�����   :DTS2013091407626:W��UE���У�δ�յ����ཨ��CNFǰ�������ض���G��δ����LAU
 23.��    ��   :2013��10��18��
    ��    ��   :z00161729
    �޸�����   :DTS2013101900866:mm��wait for mm connection״̬�յ�gas������Ϣû�и�cc�ظ�rel ind���º���T303��ʱ����ʧ��
 24.��    ��   : 2013��9��22��
    ��    ��   : w00176964
    �޸�����   : Volte_phaseII ��Ŀ:����SRVCC���̴�����������ú���
 25.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
 26.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E85( VOS_VOID* pMsg )
{
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    MMCMM_RESUME_IND_STRU              *pstResumeIndMsg = VOS_NULL_PTR;
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,  "MM leave SUSPEND state");

    /* �ָ�MMģ���״̬�Լ���ʱ�������Ϣ */
    NAS_MM_ResumeSuspendInfo((MMCMM_RESUME_IND_STRU*)pMsg);

    /* MM��mmc����resume rsp */
    NAS_MM_SndMmcResumeRsp();

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    pstResumeIndMsg = (MMCMM_RESUME_IND_STRU*)pMsg;

    /* ��ϵͳ�任��EHRPD�µĴ��� */
    if ( MMC_RESUME_ORIGEN_HRPD == pstResumeIndMsg->ucResumeOrigen )
    {
        NAS_MM_ProcResumeToHRPD(pstResumeIndMsg);

        return;
    }
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ϵͳ�任��LTE�µĴ��� */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
       NAS_MM_ProcResumeIndBackToLTE((MMCMM_RESUME_IND_STRU*)pMsg);

       return;
    }
#endif

    /* ��ϵͳ�任��GU�µĴ��� */
    NAS_MM_ProcResumeIndBackToGU((MMCMM_RESUME_IND_STRU*)pMsg);

    /* ���ú��� MM_SndMsgFuncChg �л������㷢����Ϣ�ĺ��� */
    MM_SndMsgFuncChg();

    switch ( g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
    {
        case MMC_SUSPEND_CAUSE_HANDOVER :
        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            if ( MM_RESUME_RESULT_FAILURE == (((MMCMM_RESUME_IND_STRU*)pMsg)->ucCsResumeResult) )
            {
                NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_NORMAL,"MM:HANDOVER Resume Failure.");

                /* ���� MM_RelMsgBuf �ͷŻ�����Ϣ */
                MM_RelMsgBuf();

                Mm_RcvRrmmRelInd();
            }
            else
            {
                NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_NORMAL,"Resume Success");

                /* ����ǰû�з��ͳɹ�����Ϣ���·��� */
                MM_RetransferMsg();
                /* ���ú��� MM_Restore �����������Ϣ */
                MM_Restore();
            }
            break;

        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            if ( MM_RESUME_RESULT_SUCCESS != (((MMCMM_RESUME_IND_STRU*)pMsg)->ucCsResumeResult) )
            {
                /* add by z40661 for AT2D12429,MMCMM_RESUME_INDʧ��, �����ǰ��CSҵ����Ҫ֪ͨ */
                /* ֹͣ������ʱ�� */
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                /* ���� MM_RelMsgBuf �ͷŻ�����Ϣ */
                MM_RelMsgBuf();

                Mm_RcvRrmmRelInd();

               Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL);
            }
            else
            {
                /* ���ú��� MM_Restore �����������Ϣ */
                MM_Restore();
            }

            break;

        default:
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,"SUSPEND cause is error");
            break;
    }

    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_TimerExpire
 Description    : process after timer expire
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
*****************************************************************************/
VOS_VOID Mm_Cell_S32_TimerExpire( VOS_VOID* pMsg )
{
    /* ��Ϣͷ�ṹ�������ж���Ϣ���� */
    MSG_HEADER_STRU                    *pMsgHeader;

    /* ��ȡ��Ϣͷ */
    pMsgHeader                          = (MSG_HEADER_STRU* )pMsg;

    /* �ж���Ϣ���ͣ����ֱ��� */
    MM_SaveMsg(pMsg, g_MmSubLyrShare.MmShare.MmSuspendEvent, pMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    return;

}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_DataTransfer
 Description    : process after data req at SUSPEND state
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
*****************************************************************************/
VOS_VOID Mm_Cell_S32_DataTransfer( VOS_VOID* pMsg )
{
    /* ��Ϣͷ�ṹ�������ж���Ϣ���� */
    MSG_HEADER_STRU                    *pMsgHeader;

    /* ��ȡ��Ϣͷ */
    pMsgHeader                          = (MSG_HEADER_STRU* )pMsg;

    /* ���ú��� MM_SaveMsg ���д��� */
    MM_SaveMsg(pMsg, g_MmSubLyrShare.MmShare.MmSuspendEvent, pMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_CCEstREQ
 Description    : process after CC est req  at SUSPEND state
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  3.��    ��   : 2013��8��17��
    ��    ��   : z00161729
    �޸�����  : DTS2013062406563:EMO�Ŀ���OOSʱû��פ����SBM������
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_CCEstREQ( VOS_VOID* pMsg )
{
    /* MM refuse the est req of CC */
    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /*WUEPS_ASSERT(0);
 */
    }
    else
    {
        if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
         && (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType))
        {
            /* oos���̱Ƚϳ�����ǽ���������Ҫ���oos���� */
            /*����÷������� */
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }
        else
        {
           Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
        }

    }
    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_SMSEstREQ
 Description    : process after SMS est req  at SUSPEND state
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_SMSEstREQ( VOS_VOID* pMsg )
{
    /* MM refuse the est req of SMS */
    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /*WUEPS_ASSERT(0);
 */
    }
    else
    {
        Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
    }
    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_SSEstREQ
 Description    : process after SS est req  at SUSPEND state
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.��    ��   : 2007��07��31��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D12640
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_SSEstREQ( VOS_VOID* pMsg )
{
    /* MM refuse the est req of SS */
    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /*WUEPS_ASSERT(0);
 */
    }
    else
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
    }
    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_E23
 Description    : process MMC_MM_POWER_OFF
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
 1.Date        : 2006-05-05
   Author      : x51137
   Modification: Created function
 2.��    ��   : 2006��9��9��
   ��    ��   : sunxibo id:46746
   �޸�����   : �������ⵥ�ţ�A32D05803
 3.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 4.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 5.��    ��   : 2013��05��15��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 6.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E23( VOS_VOID* pMsg )
{
    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg) )
    {
        return;
    }

    /* ֹͣ������б�����ʱ�� */
    if ( MM_TIMER_START == gstMmTimerSuspend.ucTimerStatus )
    {
        if (VOS_OK != Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_PROTECT_SUSPEND, &(gstMmTimerSuspend.stTimer)))
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"Stop MM_TIMER_PROTECT_SUSPEND fail.");
        }
        else
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"Stop MM_TIMER_PROTECT_SUSPEND success.");
        }
    }

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    MM_RelMsgBuf();

    Mm_TimerStop(MM_TIMER_STOP_ALL);

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;

    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    Mm_ComNasInfoSav(
                     MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    Mm_SndMmcPowerOffCnf();


    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
    }

    Mm_ComSetMmState(MM_STATE_NULL);

}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S32_E22
 ��������  : MM�ڹ���״̬�յ�detach��Ϣ�Ĵ���
 �������  : VOS_VOID* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��15��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

*****************************************************************************/
VOS_VOID Mm_Cell_S32_E22( VOS_VOID* pMsg )
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        /* ����ȫ�ֱ�����CS����б���detach����Ҫ����ɾ�� */
        if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
          && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucSuspendPreState ) )
        {
            NAS_MM_InitCcoFallbackCtx();
        }

        /* ����mmǨ����״̬,3212�ڹ���״̬δֹͣ,��ʱ��Ҫֹͣ */
        Mm_TimerStop(MM_TIMER_T3212);


        if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucSuspendPreState)
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
            g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_NO_IMSI;
            g_MmGlobalInfo.ucPreState = MM_IDLE_NO_IMSI;

        }
        else
        {
            g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_LIMITED_SERVICE;
            g_MmGlobalInfo.ucPreState = MM_IDLE_LIMITED_SERVICE;
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucSuspendPreState;

        g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucSuspendPreState;

        g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
