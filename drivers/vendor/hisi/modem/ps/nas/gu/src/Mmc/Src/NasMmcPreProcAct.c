/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcPreProcAct.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2010��11��15��
  ����޸�   :
  ��������   :Ԥ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��11��12��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasCommDef.h"
#include "NasMmcPreProcAct.h"
#include "NasMmcProcNvim.h"
#include "NasMmcMain.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcSndMscc.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmcTimerMgmt.h"
#include "UsimPsInterface.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcProcRegRslt.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NVIM_Interface.h"
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"
#include "NasUsimmApi.h"

#include  "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcCtx.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
#include "NasMmcFsmBgPlmnSearchTbl.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */
#include "NasMmcFsmBgPlmnSearch.h"
#include "NasMmcSndCss.h"

#if   (FEATURE_ON == FEATURE_LTE)
#include "NasMmcSndLmm.h"
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMta.h"
#include "NasUtranCtrlCtx.h"
#include "GmmExt.h"
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif

#include "NasMmcProcSuspend.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCBGPREPROC_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if defined (__PS_WIN32_RECUR__)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RestoreFixedContextData_PreProc
 ��������  : �ָ�MMCȫ�ֱ�����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ҫ�ָ���ȫ�ֱ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2009��05��11��
   ��    ��   : ŷ���� 00132663
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��20��
   ��    ��   : zhoujun 40661
   �޸�����   : ȫ�ֱ�����������PC�ط��޸�

 3.��    ��   : 2011��8��20��
   ��    ��   : l00130025
   �޸�����   : PC�ط��޸�,�����µĽṹ
 4.��    ��   : 2011��11��30��
   ��    ��   : z00161729
   �޸�����   : ʵ��pc�ط�ѹ�������޸�
 5.��    ��   : 2013��05��17��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RestoreFixedContextData_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FIXED_CONTEXT_MSG_STRU                          stRcvMsgCB;
    NVIM_EQUIVALENT_PLMN_LIST_STRU                          stEquivPlmn;
    VOS_UINT8                                               i;
    NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU                    stNetworkCap;/*network capability*/
    NAS_NVIM_RPLMN_WITH_RAT_STRU                            stRplmn;
    VOS_UINT32                                              ulSrcLen;
    VOS_UINT32                                              ulDataLen;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstRcMsg;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCount;
    VOS_UINT32                                              ulNvLength;

    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU               stQuickStartFlg;
    NAS_NVIM_AUTOATTACH_STRU                            stAutoattachFlag;
    NAS_NVIM_HPLMN_FIRST_TIMER_STRU                     stHplmnTimerLen;
    NAS_NVIM_SELPLMN_MODE_STRU                          stSelplmnMode;

    stQuickStartFlg.ulQuickStartSta = 0;
    PS_MEM_SET(&stAutoattachFlag, 0x00, sizeof(NAS_NVIM_AUTOATTACH_STRU));

    PS_MEM_SET(&stHplmnTimerLen, 0x00, sizeof(NAS_NVIM_HPLMN_FIRST_TIMER_STRU));
    PS_MEM_SET(&stSelplmnMode, 0x00, sizeof(NAS_NVIM_SELPLMN_MODE_STRU));
    ulNvLength = 0;

    ulSrcLen  = 0;
    ulDataLen = sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU);

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pstMsg;
    pucSrc   = pstRcMsg->aucData;

    /* �����ܳ��� */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulDataLen != ulCount )
    {
        return VOS_FALSE;
    }

    NAS_MML_UnCompressData(&stRcvMsgCB, &ulDataLen,
                           pucSrc, &ulSrcLen);

    /* NV��Ļָ�,�ָ�IMEI������ */
    NV_Write(en_NV_Item_IMEI, stRcvMsgCB.aucImeisv, NAS_MML_MAX_IMEISV_LEN);

    /* NV��Ļָ�,�ָ�����ģʽ */
    stSelplmnMode.usSelPlmnMode = (VOS_UINT16)stRcvMsgCB.enSelectionMode;
    NV_Write(en_NV_Item_SelPlmn_Mode, &stSelplmnMode, sizeof(NAS_NVIM_SELPLMN_MODE_STRU));

    /* NV��Ļָ�,�ָ���ЧPLMN */
    PS_MEM_SET(&stEquivPlmn, 0, sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));
    stEquivPlmn.ucCount = stRcvMsgCB.stEquPlmnInfo.ucEquPlmnNum;

    for (i=0; i<stEquivPlmn.ucCount; i++)
    {
        stEquivPlmn.struPlmnList[i].ucMcc[0]
            = (VOS_UINT8)(stRcvMsgCB.stEquPlmnInfo.astEquPlmnAddr[i].ulMcc & 0x0f);
        stEquivPlmn.struPlmnList[i].ucMcc[1]
            = (VOS_UINT8)((stRcvMsgCB.stEquPlmnInfo.astEquPlmnAddr[i].ulMcc>>8) & 0x0f);
        stEquivPlmn.struPlmnList[i].ucMcc[2]
            = (VOS_UINT8)((stRcvMsgCB.stEquPlmnInfo.astEquPlmnAddr[i].ulMcc>>16) & 0x0f);
        stEquivPlmn.struPlmnList[i].ucMnc[0]
            = (VOS_UINT8)(stRcvMsgCB.stEquPlmnInfo.astEquPlmnAddr[i].ulMnc & 0x0f);
        stEquivPlmn.struPlmnList[i].ucMnc[1]
            = (VOS_UINT8)((stRcvMsgCB.stEquPlmnInfo.astEquPlmnAddr[i].ulMnc>>8) & 0x0f);
        stEquivPlmn.struPlmnList[i].ucMnc[2]
            = (VOS_UINT8)((stRcvMsgCB.stEquPlmnInfo.astEquPlmnAddr[i].ulMnc>>16) & 0x0f);
    }

    NV_Write(en_NV_Item_EquivalentPlmn, &stEquivPlmn, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    /* NV��Ļָ�,�ָ���Ч�������� */
    stNetworkCap.aucNetworkCapability[0] = stRcvMsgCB.stMsNetworkCapability.ucNetworkCapabilityLen;

    if (stRcvMsgCB.stMsNetworkCapability.ucNetworkCapabilityLen > NAS_MML_MAX_NETWORK_CAPABILITY_LEN)
    {
        stNetworkCap.aucNetworkCapability[0] = NAS_MML_MAX_NETWORK_CAPABILITY_LEN;
    }

    /* ������������ */
    PS_MEM_CPY(&(stNetworkCap.aucNetworkCapability[1]),
               stRcvMsgCB.stMsNetworkCapability.aucNetworkCapability,
               stNetworkCap.aucNetworkCapability[0]);

    NV_Write(en_NV_Item_NetworkCapability, &stNetworkCap, NV_ITEM_NET_CAPABILITY_MAX_SIZE);

    /* NV��Ļָ�,�ָ�RPLMN��Ϣ */
    stRplmn.ucLastRplmnRat          = stRcvMsgCB.stRplmnCfg.enLastRplmnRat;
    stRplmn.ucLastRplmnRatEnableFlg = stRcvMsgCB.stRplmnCfg.ucLastRplmnRatFlg;
    stRplmn.stGRplmn.ulMcc          = stRcvMsgCB.stRplmnCfg.stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = stRcvMsgCB.stRplmnCfg.stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = stRcvMsgCB.stRplmnCfg.stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = stRcvMsgCB.stRplmnCfg.stWRplmnInNV.ulMnc;

    NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(stRplmn));

    /* �ָ� Ps Auto attach */
    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulNvLength);
    stAutoattachFlag.usAutoattachFlag = (VOS_UINT16)stRcvMsgCB.ucPsAutoAttachFlg;
    NV_Write(en_NV_Item_Autoattach, &(stAutoattachFlag.usAutoattachFlag), ulNvLength);

    /* NV��Ļָ�,�ָ�HPLMN��ʱ��ʱ��,NV�������Է����������,ʵ����������ʱ��ʱ��Ҫ��ms������ */
    stHplmnTimerLen.ucHplmnTimerLen = (VOS_UINT8)((stRcvMsgCB.stBGSrchCfg.ulFirstStartHplmnTimerLen) / (NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND));
    NV_Write(en_NV_Item_HPlmnFirstTimer, &(stHplmnTimerLen.ucHplmnTimerLen), NV_ITEM_HPLMN_FIRST_SEARCH_SIZE);

    /* NV��Ļָ�,�ָ����ٿ��� */
    stQuickStartFlg.ulQuickStartSta = stRcvMsgCB.ulQuickStartFlag;
    NV_Write(en_NV_Item_FollowOn_OpenSpeed_Flag, &(stQuickStartFlg.ulQuickStartSta), sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU));


    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_RestoreFixedContextData_PreProc - data is restored.");

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RestoreContextData_PreProc
 ��������  : �ָ�MMCȫ�ֱ�����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ҫ�ָ���ȫ�ֱ���
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2009��01��10��
   ��    ��   : ŷ���� 00132663
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��20��
   ��    ��   : zhoujun 40661
   �޸�����   : ȫ�ֱ�����������PC�ط��޸�

 3.��    ��   : 2012��2��1��
   ��    ��   : l00130025
   �޸�����   : �طŵ����������ָ���ָ���ַ����
 4.��    ��   : 2011��11��30��
   ��    ��   : z00161729
   �޸�����   : pc�ط�ѹ�������޸�
 5.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RestoreContextData_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CONTEXT_STRU                                    *pstMmcCtx;
    NAS_MML_CTX_STRU                                        *pstMmlCtx;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;

    pstMmcCtx     = NAS_MMC_GetMmcCtxAddr();
    pstMmlCtx     = NAS_MML_GetMmlCtx();
    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_MML_CTX_STRU)
                  + sizeof(MM_SUB_LAYER_SHARE_STRU)
                  + sizeof(NAS_MMC_CONTEXT_STRU)
                  + sizeof(TAF_PLMN_ID_STRU);

    /*ע��״̬��*/
    NAS_MMC_RegFsm();

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pstMsg;
    pucSrc   = pstRcMsg->aucData;

    /* �����ܳ��� */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* g_stNasMmlCtxĿ���ַ */
    pucDest     = (VOS_UINT8 *)pstMmlCtx;
    ulDestLen   = sizeof(NAS_MML_CTX_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    /* ����ԭ�ڲ���Ϣ����Ϊ�п����ڲ���Ϣ������������������ˣ�Ȼ��RECUR����Ҫ�����ڲ���Ϣ��*/
    pstMmlCtx->stInternalMsgQueue.ucHeader = 0;
    pstMmlCtx->stInternalMsgQueue.ucTail = 0;

    pucSrc += (ulItemCount);

    /* g_MmSubLyrShareĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_MmSubLyrShare;
    ulDestLen   = sizeof(MM_SUB_LAYER_SHARE_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_stNasMmcCtxĿ���ַ */
    pucDest     = (VOS_UINT8 *)pstMmcCtx;
    ulDestLen   = sizeof(NAS_MMC_CONTEXT_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    NAS_MMC_ReloadFsmDesc(NAS_MMC_GetCurFsmAddr(), pstMmcCtx->stCurFsm.enFsmId);

    /* ����PC�ط���Ϣ����PC������״̬����FsmStack��ַ���¸�ֵ */
    NAS_MMC_RestoreFsmStack(&pstMmcCtx->stFsmStack);

#if (FEATURE_ON == FEATURE_LTE)
#ifdef WIN32
    PS_MEM_CPY(&g_stSetRplmn,pucSrc,sizeof(TAF_PLMN_ID_STRU));
#endif
#endif
     pucSrc += sizeof(TAF_PLMN_ID_STRU);


    NAS_INFO_LOG(WUEPS_PID_MMC, "MMC: NAS_MMC_RestoreContextData - data is restored.");

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RestoreFsmDesc
 ��������  : ����PC�ط���Ϣ����PC������״̬����FsmDesc��ַ���¸�ֵ
 �������  : NAS_MMC_CONTEXT_STRU               *pstPcMmcCtx
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��21��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RestoreFsmStack(
    NAS_MMC_FSM_STACK_STRU             *pstPcFsmStack
)
{
    NAS_MMC_FSM_CTX_STRU               *pstFsmCtx   = VOS_NULL_PTR;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    VOS_UINT32                          ulPcRecurFsmId;
    VOS_UINT32                          i;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();

    PS_MEM_CPY(pstFsmStack, pstPcFsmStack, sizeof(NAS_MMC_FSM_STACK_STRU));

    /* ��ʼ��ջ�еĵ�ǰ״̬����FsmDesc */
    for ( i = 0 ; i < (pstPcFsmStack->usStackDepth); i++ )
    {
        pstFsmCtx                           = &(pstFsmStack->astFsmStack[i]);

        ulPcRecurFsmId                      = pstPcFsmStack->astFsmStack[i].enFsmId;

        NAS_MMC_ReloadFsmDesc(pstFsmCtx, ulPcRecurFsmId);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmDesc
 ��������  : ����FsmIdȡ��PC�����е���Ӧ״̬���ĵ�ַ
 �������  : VOS_UINT32                          ulPcRecurFsmId
 �������  : NAS_FSM_DESC_STRU                  *pstFsmDesc
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��21��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��5��
   ��    ��   : zhoujun 40661
   �޸�����   : ״̬������
*****************************************************************************/
VOS_VOID NAS_MMC_ReloadFsmDesc(
    NAS_MMC_FSM_CTX_STRU               *pstFsmCtx,
    VOS_UINT32                          ulPcRecurFsmId
)
{
    switch ( ulPcRecurFsmId )
    {
        case NAS_MMC_FSM_L1_MAIN :
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetMainFsmDescAddr();
            break;

        case NAS_MMC_FSM_SWITCH_ON :
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MMC_FSM_POWER_OFF :
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MMC_FSM_PLMN_SELECTION :
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_MMC_FSM_ANYCELL_SEARCH :
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetAnyCellSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_SYSCFG:
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetSysCfgFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CELLRESEL:
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetInterSysCellReselFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_OOS:
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetInterSysOosFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_HO:
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetInterSysHoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CCO:
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetInterSysCcoFsmDescAddr();
            break;

        case NAS_MMC_FSM_PLMN_LIST:
            pstFsmCtx->pstFsmDesc       = NAS_MMC_GetPlmnListFsmDescAddr();
            break;

        case NAS_MMC_FSM_BG_PLMN_SEARCH:
            pstFsmCtx->pstFsmDesc               = NAS_MMC_GetBgPlmnSearchFsmDescAddr();
            break;

        default:
            break;
    }

}


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccModeChange_PreProc
 ��������  : Ԥ����Mode CHange Change ��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��15��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��28��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase III ����ע���޸�
  3.��    ��   : 2011��10��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 phase III ����ע���޸�
  4.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  5.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
  6.��    ��   : 2012��2��24��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 ֧��CSFB�����޸�:ɾ��LTE UE OPERATION MODE NVIM�Ĳ���
  7.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  8.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : for CS/PS mode 1,��Disable LTEԭ��ֵ
  9.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 10.��    ��   : 2013��6��3��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE:ģʽ�仯ʱ�����¶����������ȫ�ֱ���
 11.��    ��   : 2013��2��28��
    ��    ��   : w00176964
    �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
 12.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccModeChange_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    MSCC_MMC_MODE_CHANGE_REQ_STRU                          *pstModeChangeReq = VOS_NULL_PTR;
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;
    VOS_UINT8                                              *pucEf           = VOS_NULL_PTR;
    NAS_MML_MS_MODE_ENUM_UINT8                              enOldMsMode;
    NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM_UINT8           enCsChgType;
    VOS_UINT32                                              ulEfLen;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDisableLteRoamFlg;
#endif

    VOS_UINT32                                              ulFileId;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        ulFileId = USIMM_USIM_EFLOCI_ID;
    }
    else
    {
        ulFileId = USIMM_GSM_EFLOCI_ID;
    }

    /* �������ĺϷ��� */
    pstModeChangeReq    = (MSCC_MMC_MODE_CHANGE_REQ_STRU*)pstMsg;

    enMsMode = NAS_MMC_ConvertMsccMsModeToMmlMsMode(pstModeChangeReq->enMsMode);

    /* �쳣���:�������ʹ���ֱ�ӷ��� */
    if (NAS_MML_MS_MODE_BUTT == enMsMode)
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
    {
        ulEfLen         = 0;

        /* ��ȡԭ�����ֻ�ģʽ */
        enOldMsMode = NAS_MML_GetMsMode();

        /* ��ȡCS�������仯���� */
        enCsChgType = NAS_MMC_GetCsDomainCapaChangeType(enOldMsMode, enMsMode);

        /* CS���ɲ�֧�ֵ�֧��ʱ����ӦSVLTE��˫���е����������
            MODEM0��Ҫͬ��һ��֮ǰMODEM1��USIM�ϸ��¹���CS��������Ϣ */
        if (NAS_MMC_CS_DOMAIN_CAPA_UNAVAIL_TO_AVAIL == enCsChgType)
        {
            /* ͬ��SIM���е�EFloci��EFkeys�ļ� */
            if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, USIMM_GUTL_APP))
            {
                /* ��ȡ�ļ��ɹ���MMC�ڲ�����Ӧ���� */
                NAS_MMC_ProcAgentUsimReadFileCnf_PreProc((VOS_UINT16)ulFileId, (VOS_UINT16)ulEfLen, pucEf);
            }

            if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCachedFile(USIMM_USIM_EFKEYS_ID, &ulEfLen, &pucEf, USIMM_GUTL_APP))
            {
                /* ��ȡ�ļ��ɹ���MMC�ڲ�����Ӧ���� */
                NAS_MMC_ProcAgentUsimReadFileCnf_PreProc(USIMM_USIM_EFKEYS_ID, (VOS_UINT16)ulEfLen, pucEf);
            }
        }
        else
        {

        }

    }

    /* ����MML�����MODE */
    NAS_MML_SetMsMode(enMsMode);

    /* ֪ͨGMMģ��ģʽ�ı� */
    NAS_MMC_SndGmmModeChangeReq(enMsMode);

    /* ֪ͨMMģ��ģʽ�ı� */
    NAS_MMC_SndMmModeChangeReq(enMsMode);

#if (FEATURE_ON == FEATURE_LTE)

    ulDisableLteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

    /* �ж��Ƿ���Ҫdisable LTE */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ModeChange())
    {
        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON);
        }
        else
        {
             NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
        }

        if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        }
        else
        {
            /* ������ε��µ�disable�Ѿ�֪ͨ��GU�����,��ʱ����Ҫ���ظ�֪ͨ */
            if (VOS_FALSE == ulDisableLteRoamFlg)
            {
                NAS_MMC_SndDisableLteNotify(NAS_MML_GetDisableLteReason());

                /* ��¼disable lteʱפ����������Ϣ */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
        }

        return VOS_TRUE;
    }

    /* �ж��Ƿ���Ҫenable LTE */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_ModeChange())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisableLteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PreProcMmInfo
 ��������  : Ԥ����MMCGMM_INFO_IND��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��16��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��08��
   ��    ��   : s46746
   �޸�����   : V7R1 phase II�����ȼ�״̬��ʵ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMCGMM_INFO_IND_STRU                *pRcvMsg = VOS_NULL_PTR;

    pRcvMsg = (MMCGMM_INFO_IND_STRU *)pstMsg;

    NAS_MMC_SndMsccMmInfo(&pRcvMsg->stMmInfo);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_PreProcPdpStatusInd
 ��������  : Ԥ����MMCGMM_PDP_STATUS_IND��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��16��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPdpStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMCGMM_PDP_STATUS_IND_STRU          *pstRcvMsg;

    pstRcvMsg = (MMCGMM_PDP_STATUS_IND_STRU*)pstMsg;
    if ( (MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST != pstRcvMsg->ulPdpStatusFlg)
      && (MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST != pstRcvMsg->ulPdpStatusFlg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvPdpStatusInd_PreProc:Msg is invalid.");
        return VOS_TRUE;
    }
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

    if ( MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST == pstRcvMsg->ulPdpStatusFlg)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
    }
    else
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
    }

    return VOS_TRUE;

}



/* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-15, begin */
/* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-15, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmInfo_PreProc
 ��������  : Ԥ����MMCMM_INFO_IND��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��17��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��08��
   ��    ��   : s46746
   �޸�����   : V7R1 phase II�����ȼ�״̬��ʵ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMCMM_INFO_IND_STRU                 *pstRcvMsg;

    pstRcvMsg = (MMCMM_INFO_IND_STRU *)pstMsg;

    NAS_MMC_SndMsccMmInfo(&(pstRcvMsg->stMmInfo));

    return VOS_TRUE;
}

/* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-15, begin */
/* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-15, end */



/*****************************************************************************
 �� �� ��  : NAS_MMC_PreProcGasScellRxINd
 ��������  : Ԥ����GRRMM_SCELL_MEAS_IND��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��17��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��12��
    ��    ��   : l00130025
    �޸�����   : DTS2012010504965,SYSCFG����Ϊ��ģʱ��ģʽ�仯û���ϱ�������ATģʽ�������ʴ���
  3.��    ��   : 2012��4��9��
    ��    ��   : l00130025
    �޸�����   : DTS2012033006643,��פ��״̬���ź�ǿ�Ȳ��ܼ�ʱ����
  4.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr
  5.��    ��   : 2012��12��30��
    ��    ��   : w00176964
    �޸�����   : DTS2012122805087:G��ר��̬��,�ź������仯ʱ,NAS����Ҫ�ϱ�RSSI��CERSSI
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��

  7.��    ��   : 2013��10��16��
    ��    ��   : z00234330
    �޸�����   : gas���������ϱ��ź�����������mma��Ϊ��Wģʽ�����ϱ���at����
                 ��gas�ϱ��ź��������������䣬nas�������жϣ�����δ�ϱ���AT
                 dts2013101605557
  8.��    ��   : 2014��6��4��
    ��    ��   : b00269685
    �޸�����   : ��ber�仯ʱ��֪ͨmma�ı�ȫ�ֱ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasScellRxInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    GRRMM_SCELL_MEAS_IND_ST            *pstScellRx      = VOS_NULL_PTR;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulReportRssiFlg;
    VOS_UINT32                          ulReportCellIdFlg;
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;

    pstCampCellInfo         =  NAS_MML_GetCampCellInfo();
    pstScellRx              = (GRRMM_SCELL_MEAS_IND_ST *)pstMsg;
    ulReportRssiFlg         = VOS_FALSE;
    ulReportCellIdFlg       = VOS_FALSE;

    /*�����ʳ���99���ź�ǿ�ȴ���0��С��-114����Ϊ����*/
    if ( (pstScellRx->ucChannelQual > NAS_MML_GSM_CHANNEL_QUAL_INVALID)
      || (pstScellRx->sRxlev > NAS_MML_RSSI_UPPER_LIMIT)
      || (pstScellRx->sRxlev < NAS_MML_RSSI_LOWER_LIMIT))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC ,"NAS_MMC_PreProcGasScellRxInd():WARNING:Value is unvalid");
        return VOS_TRUE;
    }

    /* ���ж��Ƿ����ϴε���ֵһ��,��GAS���ȷ��,��ȫ����GAS�ϱ���ֵ */
    if (((GRRMM_SCELL_MEAS_TYPE_RXLEV == (pstScellRx->unMeasReportType.ucMeasReportType & GRRMM_SCELL_MEAS_TYPE_RXLEV))
      || (GRRMM_SCELL_MEAS_TYPE_NONE == pstScellRx->unMeasReportType.ucMeasReportType)) )
    {
        ulReportRssiFlg = VOS_TRUE;
    }

    /* ��ber�ı�ʱ����Ҫ֪ͨmma�ı�ȫ�ֱ��� */
    if ((GRRMM_SCELL_MEAS_TYPE_RXLEV     != (pstScellRx->unMeasReportType.ucMeasReportType & GRRMM_SCELL_MEAS_TYPE_RXLEV))
     || (GRRMM_SCELL_MEAS_TYPE_RXQUALITY == (pstScellRx->unMeasReportType.ucMeasReportType & GRRMM_SCELL_MEAS_TYPE_RXQUALITY)))
    {
        ulReportRssiFlg = VOS_TRUE;
    }


    /* פ��̬���ϱ�����ָʾ��CELL ID���ѯ�ϱ�ʱ,CELL ID�仯���ϱ�CELL ID */
    if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
     && ((GRRMM_SCELL_MEAS_TYPE_CELLID == (pstScellRx->unMeasReportType.ucMeasReportType & GRRMM_SCELL_MEAS_TYPE_CELLID))
      || (GRRMM_SCELL_MEAS_TYPE_NONE == pstScellRx->unMeasReportType.ucMeasReportType)))
    {
        ulReportCellIdFlg = VOS_TRUE;
    }

    /*ͨ����Ϣ����ȫ�ֱ���*/
    pstCampCellInfo->ucCellNum                      = 1;
    pstCampCellInfo->ucRssiNum                      = 1;

    /*�����ź�����*/
    pstCampCellInfo->astRssiInfo[0].sRssiValue      = pstScellRx->sRxlev;

    /*����������*/
    pstCampCellInfo->astRssiInfo[0].ucChannalQual   = pstScellRx->ucChannelQual;
    pstCampCellInfo->sUeRfPower                     = pstScellRx->sUeRfPower;
    pstCampCellInfo->usCellDlFreq                   = pstScellRx->usCellDlFreq;
    pstCampCellInfo->usCellUlFreq                   = pstScellRx->usCellUlFreq;

    pstCampCellInfo->astCellInfo[0].sCellRssi       = pstScellRx->sRxlev;



    /* CELL ID�����仯 */
    if (VOS_TRUE == ulReportCellIdFlg)
    {
        pstCampCellInfo->astCellInfo[0].ulCellId = pstScellRx->usCellId;
        NAS_MMC_SndMsccSysInfo();
    }

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));
    unMeasReportType.ucMeasReportType = pstScellRx->unMeasReportType.ucMeasReportType;

    /*���ú�����TAF�ϱ����*/
    if ( VOS_TRUE == ulReportRssiFlg )
    {
        NAS_MMC_SndMsccRssiInd(&unMeasReportType);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasCellSubMode_PreProc
 ��������  : ���������ϱ�����ģʽ��Ϣ
 �������  : enSubMode----��ģʽ��Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvWasCellSubMode_PreProc(
    RRC_NAS_AT_MSG_SUBMODE_ENUM_UINT8   enSubMode
)
{
    /* �ϱ�W������ģʽ,R99 */
    if (RRC_NAS_AT_R99_ONLY == enSubMode)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_R99_ONLY);
    }
    /* �ϱ�W������ģʽ,HSDPA */
    else if (RRC_NAS_AT_HSDPA_ONLY == enSubMode)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA);
    }
    /* �ϱ�W������ģʽ,HSUPA */
    else if (RRC_NAS_AT_HSUPA_ONLY == enSubMode)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_HSUPA);
    }
    /* �ϱ�W������ģʽ,HSUPA+HSDPA */
    else if (RRC_NAS_AT_HSDPA_AND_HSUPA == enSubMode)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA_AND_HSUPA);
    }
    /* �ϱ�W������ģʽ,HSPA+ */
    else if (RRC_NAS_AT_HSPA_PLUS == enSubMode)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_HSPA_PLUS);
    }
    else if (RRC_NAS_AT_DC_HSPA_PLUS == enSubMode)
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_DC_HSPA_PLUS);
    }
    else if ( RRC_NAS_AT_DC_MIMO == enSubMode )
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_DC_MIMO);
    }
    else
    {
        ;
    }
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_PreProcWasAtMsgInd
 ��������  : Ԥ����RRMM_AT_MSG_IND��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��17��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��12��
   ��    ��   : W00167002
   �޸�����   : NAS_MMC_RcvWasCellId_PreProc����������Ϣ�����ݣ�������������Ϣ
 3.��    ��   : 2012��1��12��
   ��    ��   : l00130025
   �޸�����   : DTS2012010504965,SYSCFG����Ϊ��ģʱ��ģʽ�仯û���ϱ�������ATģʽ�������ʴ���
 4.��    ��   : 2012��4��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012033006643,�ƶ�פ��״̬���жϵ�Cell_Id���ж��У���Ϊ��פ��״̬���ź�ǿ�Ȳ��ܼ�ʱ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasAtMsgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    RRMM_AT_MSG_IND_ST                  *pstAtMsg;

    pstAtMsg = (RRMM_AT_MSG_IND_ST *)pstMsg;

    /* �ϱ�С��ID */
    if ( RRC_NAS_AT_CELL_ID == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_ID) )
    {
        NAS_MMC_RcvWasCellId_PreProc((RRC_NAS_CELL_ID_ST*)pstAtMsg->aucData);
    }

    /* �ϱ�С��Bler */
    if ( RRC_NAS_AT_CELL_BLER == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_BLER) )
    {
        NAS_MMC_RcvWasCellBler_PreProc((RRC_NAS_CELL_TRCH_BLER_STRU_LIST*)pstAtMsg->aucData);
    }

    /* �ϱ�С���ź����� */
    if  (RRC_NAS_AT_CELL_SIGN == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_SIGN) )
    {
        NAS_MMC_RcvWasCellRssi_PreProc((RRC_NAS_CELL_RSCP_STRU_LIST*)pstAtMsg->aucData);
    }

    if (RRC_NAS_AT_CELL_SUBMODE == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_SUBMODE) )
    {
        NAS_MMC_RcvWasCellSubMode_PreProc((RRC_NAS_AT_MSG_SUBMODE_ENUM_UINT8)pstAtMsg->aucData[0]);
    }



    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasAcInfoChange_PreProc
 ��������  : Ԥ����RRMM_W_AC_INFO_CHANGE_IND��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��14��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMSCC
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2014��4��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����CSPS����״̬
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasAcInfoChange_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_W_AC_INFO_CHANGE_IND_STRU     *pstWasAcInfoChangeInd = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucOldCsResTrictionRegister;
    VOS_UINT8                           ucOldPsResTrictionRegister;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-28, begin */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLastSuccLai  = VOS_NULL_PTR;

    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    pstCampInfo      = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai   = NAS_MML_GetCsLastSuccLai();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-28, end */

    pstWasAcInfoChangeInd       = (RRMM_W_AC_INFO_CHANGE_IND_STRU*)pstMsg;
    pstNetWorkInfo              =  NAS_MML_GetNetworkInfo();
    ucOldCsResTrictionRegister  = NAS_MML_GetCsRestrictRegisterFlg();
    ucOldPsResTrictionRegister  = NAS_MML_GetPsRestrictRegisterFlg();

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����CS PSע��������Ϣ */
    NAS_MMC_UpdateCsPsRestriction_AcChangeInd(pstWasAcInfoChangeInd, pstNetWorkInfo);

    /* ��MM����AC INFO CHANGE */
    NAS_MMC_SndMmWasAcInfoChangeInd(pstWasAcInfoChangeInd->stCsRestriction.enRestrictRegister,
                                    pstWasAcInfoChangeInd->stPsRestriction.enRestrictRegister,
                                    ucOldCsResTrictionRegister,
                                    ucOldPsResTrictionRegister);

    /* ��GMM����AC INFO CHANGE */
    NAS_MMC_SndGmmWasAcInfoChangeInd(pstWasAcInfoChangeInd->stCsRestriction.enRestrictRegister,
                                     pstWasAcInfoChangeInd->stPsRestriction.enRestrictRegister,
                                     ucOldCsResTrictionRegister,
                                     ucOldPsResTrictionRegister);

    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_WAS_AC_INFO_CHANGE);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_TAS_AC_INFO_CHANGE);
    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);

        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        /* ��unbar��bar , lai�����仯���ϱ�CS���Ʒ���,CSע��״̬Ϊδע��δ���� */
        if ((VOS_FALSE == ucOldCsResTrictionRegister)
         && (VOS_TRUE  == pstWasAcInfoChangeInd->stCsRestriction.enRestrictRegister))
        {
            if (VOS_FALSE == NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai))
            {
                NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
                NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }
        }
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);

        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        /* ��unbar��bar , rai�����仯���ϱ�PS���Ʒ���,PSע��״̬Ϊδע��δ���� */
        if ((VOS_FALSE == ucOldPsResTrictionRegister)
         && (VOS_TRUE == pstWasAcInfoChangeInd->stPsRestriction.enRestrictRegister))
        {
            if (VOS_TRUE == NAS_MML_IsRaiChanged())
            {
                NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }
        }
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_PreProcWasAtMsgCnf
 ��������  : Ԥ����RRMM_AT_MSG_CNF��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��17��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : ������Ϣ���������ݶ�����������Ϣ
 3.��    ��   : 2012��1��12��
   ��    ��   : l00130025
   �޸�����   : DTS2012010504965,SYSCFG����Ϊ��ģʱ��ģʽ�仯û���ϱ�������ATģʽ�������ʴ���
 4.��    ��   : 2012��4��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012033006643,��פ��״̬���ź�ǿ�Ȳ��ܼ�ʱ����,פ��̬ʱ����Ҫ�ϱ�Cell_ID�����⵼��MSCCģʽ���´���
 5.��    ��   : 2012��11��21��
   ��    ��   : z00161729
   �޸�����  : ֧��cerssi��nmr

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasAtMsgCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    RRMM_AT_MSG_CNF_ST                  *pstAtMsg = VOS_NULL_PTR;

    pstAtMsg = (RRMM_AT_MSG_CNF_ST *)pstMsg;

    /* �ж���Ϣ����Ч��*/
    if ( RRC_NAS_AT_VALID != pstAtMsg->ucMsgFlg)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC ,"NAS_MMC_RcvWasAtMsgCnf_PreProc():WARNING:the msg is not valid!");

        return VOS_TRUE;
    }

    if (RRC_NAS_AT_START_FOREVER == pstAtMsg->ucActionType)
    {
        /* W��ѵ�ǰС���ź������ϱ������账���ȴ�at msg ind��Ϣ*/
        return VOS_TRUE;
    }

    if ( RRC_NAS_AT_CELL_ID == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_ID) )
    {
        NAS_MMC_RcvWasCellId_PreProc((RRC_NAS_CELL_ID_ST*)pstAtMsg->aucData);
    }

    if ( RRC_NAS_AT_CELL_BLER == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_BLER) )
    {
        NAS_MMC_RcvWasCellBler_PreProc((RRC_NAS_CELL_TRCH_BLER_STRU_LIST*)pstAtMsg->aucData);
    }

    if  (RRC_NAS_AT_CELL_SIGN == (pstAtMsg->ucMsgType & RRC_NAS_AT_CELL_SIGN) )
    {
        NAS_MMC_RcvWasCellRssi_PreProc((RRC_NAS_CELL_RSCP_STRU_LIST*)pstAtMsg->aucData);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PreProcPlmnQryReq
 ��������  : ����WRR��GAS���͹�����PLMN INFO��ѯ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��29��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnQryReqPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    NAS_MMC_SndRrcPlmnQueryCnf(((RRMM_PLMN_QUERY_REQ_STRU *)pstMsg)->enQueryWPlmn);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmNotCampOn_PreProc
 ��������  : �յ��ײ�NOT CAMP ON��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��07��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmNotCampOn_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmEplmnQuery_PreProc
 ��������  : �յ�������ѯEPLMN����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��07��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : �޸Ļ�ȡ��ǰ��Rplmn
 3.��    ��   : 2011��09��02��
   ��    ��   : l65478
   �޸�����   : DTS2011052600767,�����Ʒ���״̬�²�ѯEPLMN��Ϣ����,AS�޷�����ϵͳ����ѡ
 4.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,��ȷ����ıȽ����ͣ�
                ������ܵ��±Ƚϳ���
 5.��    ��   : 2012��8��15��
   ��    ��   : w00176964
   �޸�����   : V7R1C50_GUTL_PhaseII:��disabled RAT�е�PLMN�ӵ�ЧPLMN�б���ɾ�����͸�RRC
 6.��    ��   : 2012��12��4��
   ��    ��   : w00176964
   �޸�����   : DTS201212905979:֪ͨRRC��ǰEPLMNʱ,�����ֹPLMN
 7.��    ��   : 2013��10��15��
   ��    ��   : z00161729
   �޸�����   : DTS2013082907281:UE��w���н������й���rrc rej�ض���g����Ϣ��
                ���н������޷��ɹ��ض���wԭС������Ϊ������ѯplmnʱnasֻ����gС��plmn
 8.��    ��   : 2013��11��18��
   ��    ��   : z00161729
   �޸�����   : DTS2013111807881:������ѯeplmn����ǰפ��������Ҫ�ж��Ƿ�Ϊ��ֹ���磬�������֪ͨ�����
 9.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 10.��    ��   : 2015��4��23��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmEquplmnQuery_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EQUIVALENT_PLMN_STRU                                    stEplmn;
    VOS_UINT8                                               i;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId      = VOS_NULL_PTR;
    RRMM_EPLMN_QUERY_REQ_STRU                              *pstEqueryMsg;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    NAS_MML_PLMN_ID_STRU                                    stCurPlmnId;
    VOS_UINT32                                              ulOpCurPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    VOS_UINT32                                              ulIsPlmnIdInDestPlmnWithRatList;
    VOS_UINT32                                              ulIsPlmnIdInForbidPlmnList;

    ulOpCurPlmnId     = VOS_FALSE;
    stCurPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stCurPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
    ulEplmnValidFlg   = NAS_MML_GetEplmnValidFlg();
    ulRegFlag         = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    pstEqueryMsg = (RRMM_EPLMN_QUERY_REQ_STRU*)pstMsg;

    PS_MEM_SET(&stEplmn, 0, sizeof(stEplmn));
    pstEquPlmnList  = NAS_MML_GetEquPlmnList();

    pstPlmnId       = NAS_MML_GetCurrCampPlmnId();

    if (WUEPS_PID_WRR == pstEqueryMsg->MsgHeader.ulSenderPid)
    {
        stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_WCDMA;
    }
    else
    {
        stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        stPlmnWithRat.stPlmnId = pstUserSpecPlmnId->stPlmnId;
    }
    else
    {
        stPlmnWithRat.stPlmnId = *pstPlmnId;
    }

    ulIsPlmnIdInDestPlmnWithRatList = NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat);

    ulIsPlmnIdInForbidPlmnList = NAS_MML_IsPlmnIdInForbidPlmnList(&stPlmnWithRat.stPlmnId);

    if ((VOS_FALSE == ulIsPlmnIdInDestPlmnWithRatList)
     && (VOS_FALSE == ulIsPlmnIdInForbidPlmnList))
    {
        ulOpCurPlmnId     = VOS_TRUE;
        stCurPlmnId.ulMcc = stPlmnWithRat.stPlmnId.ulMcc;
        stCurPlmnId.ulMnc = stPlmnWithRat.stPlmnId.ulMnc;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* �ֶ�����ģʽ�ж�eplmn�б��Ƿ���Ч����Ч�򷵻� */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            stEplmn.ulEquPlmnNum = 0;

            NAS_MMC_SndAsEquPlmnQueryCnf(&stEplmn, ulOpCurPlmnId, &stCurPlmnId, pstMsg->ulSenderPid);
            return VOS_TRUE;
        }
    }

    /* �ѵ�Чplmn������������ */
    for ( i = 0; i < pstEquPlmnList->ucEquPlmnNum; i++ )
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstEquPlmnList->astEquPlmnAddr[i]),
                         (VOS_UINT8)stEplmn.ulEquPlmnNum, (NAS_MML_PLMN_ID_STRU *)stEplmn.aEquPlmnIdList))
        {
            continue;
        }

        if (WUEPS_PID_WRR == pstEqueryMsg->MsgHeader.ulSenderPid)
        {
            stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_WCDMA;

        }
        else
        {
            stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;
        }

        /* ��������뼼����PLMN ID */
        stPlmnWithRat.stPlmnId      = pstEquPlmnList->astEquPlmnAddr[i];

        /* �жϵ�ЧPLMN�Ƿ��ڽ�ֹ���뼼����PLMN�б���,������򲻽���PLMN ID����RRC */
        if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstEquPlmnList->astEquPlmnAddr[i])))
        {
            continue;
        }

        stEplmn.aEquPlmnIdList[stEplmn.ulEquPlmnNum].ulMcc = pstEquPlmnList->astEquPlmnAddr[i].ulMcc;
        stEplmn.aEquPlmnIdList[stEplmn.ulEquPlmnNum].ulMnc = pstEquPlmnList->astEquPlmnAddr[i].ulMnc;
        stEplmn.ulEquPlmnNum++;
    }


    NAS_MMC_SndAsEquPlmnQueryCnf(&stEplmn, ulOpCurPlmnId, &stCurPlmnId, pstMsg->ulSenderPid);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmLimitServiceCamp_PreProc
 ��������  : �յ�WRR�Ľ������Ʒ���ָʾ�������Ϣ��ָʾ�������ӣ���Ҫ���·���״̬
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��07��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��12��
   ��    ��   : w00166186
   �޸�����   : W OOS�����޸�
 3.��    ��   : 2012��1��18��
   ��    ��   : s46746
   �޸�����   : ���ⵥ�ţ�DTS2012011605061,OOS���̣�������ϱ�limited camp ind��,һ��ʱ��MMC����������
 4.��    ��   : 2012��5��10��
   ��    ��   : l00130025
   �޸�����   : DTS2012050301244: �ֶ�ģʽ��LimitedServiceCmapInd�󣬶����ؽ���������MMCû���ϱ�����״̬
 5.��    ��   : 2013��1��7��
   ��    ��   : L00167671
   �޸�����   : DTS2013010705508: ����ע����w�ϣ������������ϱ���limit service
 6.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 7.��    ��   : 2013��06��27��
   ��    ��   : l65478
   �޸�����   : DTS2013062406563:EMO�Ŀ���OOSʱû��פ����SBM������
 8.��    ��   : 2014��04��21��
   ��    ��   : w00242748
   �޸�����   : DTS2014041708017:�յ�LIMIT SERVICE CAMP INDʱ��ע��״̬δǨ�ƣ�
                ���б���ʱ���յ�LMM��ע��״̬�ϱ�ʱ�����䶪����
 9.��    ��   : 2014��5��24��
   ��    ��   : w00242748
   �޸�����   : DTS2014052106103:֧�ֽ��뼼����0102���ó�010203�����������ȼ�����
                ��������������L�޸��ǣ���������LTEʱ��ϳ���15s�ڣ�AP���·�detach
                ���󣬵���ʱMSCC�ķ���״̬Ϊ�����������Ե���DETACHʧ�ܣ��Ӷ�AP��
                �������и�λ��
10.��    ��   : 2014��05��23��
   ��    ��   : w00176964
   �޸�����   : V3R3C60_eCall��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmLimitServiceCamp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_LIMIT_SERVICE_CAMP_IND_STRU    *pstLimitServiceMsg;
    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   *pstSearchCtrl;

    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enCsMsccServiceStatus;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enPsMsccServiceStatus;
    NAS_MML_REG_STATUS_ENUM_UINT8        enCsRegStatus;
    NAS_MML_REG_STATUS_ENUM_UINT8        enPsRegStatus;

    pstSearchCtrl        = NAS_MMC_GetPlmnSearchCtrl();

    pstLimitServiceMsg   = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmLimitServiceCamp_PreProc: receive wrong message");
        return VOS_TRUE;
    }

    if(VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmLimitServiceCamp_PreProc: sim is not present");
        return VOS_TRUE;
    }


    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_WAS_LIMITED_CAMP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_TAS_LIMITED_CAMP);
    }

    if (RRC_LIMIT_CAMP_ACTION_START == pstLimitServiceMsg->enLimitCampAction)
    {
        pstSearchCtrl->ucWrrLimitServiceInd     = VOS_TRUE;

        if (VOS_FALSE == pstLimitServiceMsg->ulServiceAvailFlag)
        {
            /* RRMM_LIMIT_SERVICE_CAMP_INDʱϵͳ��Ϣ����仯��Ϊ�˱�֤MMA�����ӳ��ϱ�����ҪPS��CS�ķ���״̬һ���ϱ� */
            NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,
                                           NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE);

        }
        else
        {
            /* RRMM_LIMIT_SERVICE_CAMP_INDʱϵͳ��Ϣ����仯��Ϊ�˱�֤MMA�����ӳ��ϱ�����ҪPS��CS�ķ���״̬һ���ϱ� */
            NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,
                                           NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);

        }

        enCsRegStatus = NAS_MML_GetCsRegStatus();
        enPsRegStatus = NAS_MML_GetPsRegStatus();

        if ( (NAS_MML_REG_REGISTERED_HOME_NETWORK == enCsRegStatus)
          || (NAS_MML_REG_REGISTERED_ROAM == enCsRegStatus) )
        {

            NAS_MMC_ErrLogRecordCsOosCause(enCsRegStatus, NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ErrLogClrNwSearchCount(enCsRegStatus, NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            /* �ϱ�ע��״̬�����ı� */
            NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        if ( (NAS_MML_REG_REGISTERED_HOME_NETWORK == enPsRegStatus)
          || (NAS_MML_REG_REGISTERED_ROAM == enPsRegStatus) )
        {
            /* �ϱ�ע��״̬�����ı� */
            NAS_MMC_ErrLogRecordPsOosCause(enPsRegStatus, NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ErrLogClrNwSearchCount(enPsRegStatus, NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        /* ֻ���ڿ����ṩ����,����RRC����,��ǰ�Ĳ���Ϊstart,
           �����ϱ���PLMN������Ϊ0ʱ,��Ҫ��������,��״̬���������������״̬��������VOS_TRUE */
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_Oos(pstLimitServiceMsg))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
    else if (RRC_LIMIT_CAMP_ACTION_END == pstLimitServiceMsg->enLimitCampAction)
    {
        pstSearchCtrl->ucWrrLimitServiceInd     = VOS_FALSE;

        /* ulServiceAvailFlagΪVOS_TRUE,�����ؽ����������ϱ�֮ǰ�ķ���״̬ */
        if (VOS_TRUE == pstLimitServiceMsg->ulServiceAvailFlag)
        {
            enCsMsccServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);
            enPsMsccServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);

            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

            NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                           enCsMsccServiceStatus);

            NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                           enPsMsccServiceStatus);

            /* �ϱ�ע��״̬�����ı� */
            NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MML_GetCsRegStatus());

            /* �ϱ�ע��״̬�����ı� */
            NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MML_GetPsRegStatus());
        }
        /* ulServiceAvailFlagΪVOS_FALSE�������������ģʽ�л����˴����ϱ�����״̬ */
        else
        {
            /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-23, begin */
            /* PS����Ч��CS����Ч,���W�ϱ�LIMITED CAMP ONָʾ������,��Ҫ���ϱ�һ�ο�״̬ */
            if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
            {
                /* �ϱ�ע��״̬�����ı� */
                NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MML_GetCsRegStatus());
            }

            if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
            {
                /* �ϱ�ע��״̬�����ı� */
                NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MML_GetPsRegStatus());
            }
            /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-23, end */
        }

        return VOS_FALSE;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmLimitServiceCamp_PreProc: receive wrong message");
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PostProcActingHplmnRefresh_PreProc
 ��������  : acting-hplmn���µĴ���
 �������  : ��
 �������  : pulBufferRefresh �Ƿ���Ҫ����ACTING-HPLMN REFRESH
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��20��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��28��
    ��    ��   : w00167002
    �޸�����   : ��ǰUTRAN����ģʽΪTDDʱ�򣬲�����������
  3.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  4.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : svlte��usim�ӿڵ���
  6.��    ��   : 2013��12��20��
    ��    ��   : w00167002
    �޸�����   : DTS2013112917981:guNASɾ����TDģʽ�²��ܽ���bg�ѵ����ơ�
  7.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���
  8.��    ��   : 2014��10��25��
    ��    ��   : b00269685
    �޸�����   : TD��High_Rat_Hplmn_Search���Ե���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcActingHplmnRefresh_PreProc(
    VOS_UINT8                              *pucBufferRefresh
)
{
    VOS_UINT32                              ulEfLen;
    VOS_UINT8                              *pucEf               = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU           *pstEHplmnList       = VOS_NULL_PTR;
    VOS_UINT32                              ulFileId;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        ulFileId = USIMM_ATTUSIM_EFACTINGHPLMN_ID;
    }
    else
    {
        ulFileId = USIMM_ATTGSM_EFACTINGHPLMN_ID;
    }

    *pucBufferRefresh = VOS_FALSE;


    ulEfLen = 0;

    /* �����������NVδ�򿪣�ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MML_GetActingHplmnSupportFlg())
    {
        return;
    }

    pstEHplmnList                       = NAS_MML_GetSimEhplmnList();

    /* ����API��ȡUSIM�ļ� */
    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, USIMM_GUTL_APP))
    {
        /*����ǰ�ļ�ʧ�ܣ���ȡ��һ���ļ�*/
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcActingHplmnRefresh_PreProc():ERROR:READ FILE FAIL!");
        return;
    }

    NAS_MMC_SndOmGetCacheFile(ulFileId, ulEfLen, pucEf);

    /* BG��״̬���������� */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
    {
        *pucBufferRefresh = VOS_TRUE;
    }

    /* ��ȡ�ļ��ɹ���MMC�ڲ�����Ӧ���� */
    NAS_MMC_ProcAgentUsimReadFileCnf_PreProc((VOS_UINT16)ulFileId, (VOS_UINT16)ulEfLen, pucEf);

    /* ����HPLMN���뼼�� */
    NAS_MMC_UpdateEhplmnRat();

    /* ��HPLMN���ֹ�б���ɾ�� */
    if (VOS_FALSE == NAS_MML_DelForbPlmn(&(pstEHplmnList->astEhPlmnInfo[0].stPlmnId)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcActingHplmnRefresh_PreProc():ERROR:NAS_MML_DelForbPlmn FAIL!");
    }

    /* ��ʼ�������ȼ������б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    /* �����㷢�͵�ǰ��HPLMN��EHPLMN */
    NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);
    NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

    /* ֹͣ�����ȶ�ʱ���������Գ��Զ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);
    NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH);
    NAS_MMC_StopTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER);
    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
    NAS_MMC_InitTdHighRatSearchCount();

    /* �ж��Ƿ���Ҫ����BG�� */


    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioPlmn())
    {
        return;
    }

    /* ���������ȼ����Զ�ʱ����ʱ��1s */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH, TI_NAS_MMC_ACTING_HPLMN_REFRESH_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);

    return;
}

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_DelayBgSearch
 ��������  : �����ȼ������ļ����´���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��28��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_DelayBgSearch(VOS_VOID)
{
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        return;
    }

    /* ���HPLMN��ʱ����������,ֹͣ�ö�ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);

        /* HPLMN TIMERֹͣ�¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_STOP,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
    {
        /* ��������HPLMN */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER,
                           NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchDelayLen());

        /* HPLMN TIMER�����¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��HPLMN������������Ϊ���״����� */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProHighPrioPlmnRefreshInd_PreProc
 ��������  : �����ȼ�������´���
 �������  : usEfId:���µ��ļ�ID
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��11��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���

 2.��    ��   : 2013��8��1��
   ��    ��   : w00167002
   �޸�����   : DTS2013072402166:�û�����CPOL����UPLMN��MMCû��ˢ�¸����ȼ��б�
                ����û�����������ȼ�������ʱ����
 3.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
 4.��    ��   : 2015��4��16��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProHighPrioPlmnRefreshInd_PreProc(VOS_VOID)
{

    /* ��ǰ״̬����ʶ */
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* ��ǰ״̬����״̬ */
    VOS_UINT32                          ulState;

    enFsmId = NAS_MMC_GetCurrFsmId();
    ulState = NAS_MMC_GetFsmTopState();

    /* ֪ͨMSCC��ѡPLMN��Ϣ */
    NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_OPLMN);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_UPLMN);
    }

    /* BG��״̬����������,���浱ǰ��Ϣ����BG״̬���˳����� */
    if ( NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId )
    {
        return VOS_FALSE;
    }

    /* ��ʼ�������ȼ������б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    /* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */

    if (VOS_TRUE == NAS_MML_GetHighPrioPlmnRefreshTriggerBGSearchFlag())
    {
        NAS_MMC_DelayBgSearch();
    }
    /* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

    /* ����ϵͳ��ON Plmn״̬�������������ȼ�������ʱ�� */
    if ( (NAS_MMC_FSM_INTER_SYS_CELLRESEL == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_OOS       == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_HO        == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_CCO       == enFsmId)
      || ( (NAS_MMC_FSM_L1_MAIN           == enFsmId)
        && (NAS_MMC_L1_STA_ON_PLMN        == ulState) ) )
    {
        /* �ж��Ƿ�����HPLMN */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* ������ʱ�� */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }
    }

    /* ��Ϣ������ɣ�ֱ���˳� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsHighPrioPlmnFileRefreshed
 ��������  : �ж�refresh���ļ��Ƿ���������ȼ��������
 �������  : usEfId - refresh���ļ�id
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
10.��    ��   : 2015��3��2��
   ��    ��   : c00318887
   �޸�����   : AT&T phaseII����0x6F7B�Ĵ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsHighPrioPlmnFileRefreshed(
    VOS_UINT32                          ulFileId
)
{
    VOS_UINT32                          ulNvOplmnAvail;

    /* ����UPLMN��OPLMN�ĸ���Ϊ0����ʹ��NAS_MML_READ_PLMN_SEL_FILE_ID���ļ����ݳ�ʼ�������ȼ��б� */
    ulNvOplmnAvail = NAS_MML_IsNvimOplmnAvail();

    if ((USIMM_USIM_EFPLMNWACT_ID == ulFileId)
     || (USIMM_GSM_EFPLMNWACT_ID == ulFileId)
     || ( (VOS_FALSE == ulNvOplmnAvail)
       && ((USIMM_USIM_EFOPLMNWACT_ID == ulFileId)
        || (USIMM_GSM_EFOPLMNWACT_ID  == ulFileId)) )
     || (USIMM_GSM_EFPLMNSEL_ID == ulFileId)
     || (USIMM_USIM_EFFPLMN_ID  == ulFileId)
     || (USIMM_GSM_EFFPLMN_ID   == ulFileId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvUsimRefreshFileInd_PreProc
 ��������  : MMC�յ����ļ�����֪ͨ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:״̬���������
             VOS_FALSE:״̬��δ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��07��
   ��    ��   : l00130025
   �޸�����   : ����V3R1�� Usim�ӿ�
 3.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 4.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������
 5.��    ��   : 2012��6��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ
   ��    ��   : l60609
   �޸�����   : AT&T&DCM��������6F31�ļ��ɹ��������������ƹ��ܵĴ���
 6.��    ��   : 2012��8��21��
   ��    ��   : w00167002
   �޸�����   : HPLMN WITH RAT�ļ��Լ�EHPLMN�ļ�ˢ�º���Ҫ����ˢ���ڴ��е�HPLMN WITH RAT�б�
 7.��    ��   : 2012��12��13��
   ��    ��   : L00171473
   �޸�����   : DTS2012121802573, TQE����
 8.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
 9.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : ���Ŷ��ƣ����������OPLMN���򲻴���
10.��    ��   : 2015��02��06��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���
11.��    ��   : 2015��3��2��
   ��    ��   : c00318887
   �޸�����   : AT&T phaseII����0x6F7B�Ĵ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvUsimRefreshFileInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_STKREFRESH_IND_STRU          *pstUsimRefreshInd = VOS_NULL_PTR;
    VOS_UINT8                          *pucOldImsi;
    VOS_UINT8                           aucNewImsi[NAS_MML_MAX_IMSI_LEN];
    VOS_UINT32                          i;
    VOS_UINT32                          ulHighPrioPlmnRefreshFlag;
    VOS_UINT32                          ulFileId;
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf = VOS_NULL_PTR;

    /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
    NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU    *pstRefreshFileContent   = VOS_NULL_PTR;
    /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

    VOS_UINT8                           ucBufferRefreshFlg;

    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;

    pstEHPlmnInfo                       = NAS_MML_GetSimEhplmnList();

    pstUsimRefreshInd                   = (USIMM_STKREFRESH_IND_STRU *)pstMsg;

    if ( (USIMM_REFRESH_FILE_LIST != pstUsimRefreshInd->enRefreshType)
      /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
      && (USIMM_REFRESH_ALL_FILE != pstUsimRefreshInd->enRefreshType))
      /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */
    {
        /* refresh��ϢĿǰֻ����ָ���ļ�������ͺ�ALL���� */
        return VOS_TRUE;
    }

    pucOldImsi = NAS_MML_GetSimImsi();
    if (USIMM_API_SUCCESS == USIMM_GetCardIMSI(aucNewImsi))
    {
        if (0 != VOS_MemCmp(pucOldImsi, aucNewImsi, NAS_MML_MAX_IMSI_LEN))
        {
            /* ��IMSI REFRESHָʾд��ȫ�ֱ�������ȫ�ֱ������ڿ��ػ�ʱ��� */
            NAS_MML_SetImsiRefreshStatus(VOS_TRUE);
        }
    }

    /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
    pstRefreshFileContent = (NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                         sizeof(NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU));

    if (VOS_NULL_PTR == pstRefreshFileContent)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvUsimRefreshFileInd_PreProc:ERROR:Alloc Mem Fail.");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstRefreshFileContent, 0x00, sizeof(NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU));

    NAS_MMC_BuildRefreshFileList(pstUsimRefreshInd, pstRefreshFileContent);
    /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

    ulHighPrioPlmnRefreshFlag   =  VOS_FALSE;

    ucBufferRefreshFlg          =  VOS_FALSE;


    ulEfLen                     = 0;

    /* һ�α���USIM�ϱ����ļ�ID */
    /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
    for (i = 0; i < pstRefreshFileContent->usEfNum; i++ )
    {
        ulFileId = pstRefreshFileContent->astRefreshFile[i].usFileId;

        if (((USIMM_ATTGSM_EFACTINGHPLMN_ID == ulFileId)
        || (USIMM_ATTUSIM_EFACTINGHPLMN_ID == ulFileId))
         && (USIMM_GUTL_APP == pstRefreshFileContent->astRefreshFile[i].enAppType))
        {
            NAS_MMC_ProcActingHplmnRefresh_PreProc(&ucBufferRefreshFlg);
            continue;
        }

        /* Modified by c00318887 for file refresh��Ҫ����������, 2015-6-3, begin */
        /* ����6f73 6f7e������ע��ʱ����ʧ�� */
        if ( (USIMM_USIM_EFPSLOCI_ID == ulFileId)
           ||(USIMM_USIM_EFLOCI_ID == ulFileId)
           ||(USIMM_GSM_EFLOCI_ID == ulFileId))
        {
            continue;
        }
        /* Modified by c00318887 for file refresh��Ҫ����������, 2015-6-3, end */

        /* ����API��ȡUSIM�ļ� */
        if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, pstRefreshFileContent->astRefreshFile[i].enAppType))
        {
            /*����ǰ�ļ�ʧ�ܣ���ȡ��һ���ļ�*/
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvUsimRefreshFileInd_PreProc():ERROR:READ FILE FAIL!");
            continue;
        }

        NAS_MMC_SndOmGetCacheFile(ulFileId, ulEfLen, pucEf);

        if (VOS_TRUE == NAS_MMC_IsHighPrioPlmnFileRefreshed(ulFileId))
        {
            ulHighPrioPlmnRefreshFlag = VOS_TRUE;
        }

        /* ��ȡ�ļ��ɹ���MMC�ڲ�����Ӧ���� */
        NAS_MMC_ProcAgentUsimReadFileCnf_PreProc((VOS_UINT16)ulFileId, (VOS_UINT16)ulEfLen, pucEf);

        if (USIMM_USIM_EFEHPLMN_ID == ulFileId)
        {
            /* ��Ҫ���¸����ȼ������б��� */
            ulHighPrioPlmnRefreshFlag = VOS_TRUE;

            /* ����HPLMN���뼼�� */
            NAS_MMC_UpdateEhplmnRat();

            /* ɾ��FPLMN�е�HPLMN */
            NAS_MMC_DelHplmnInFplmn();

            /* �����㷢�͵�ǰ��HPLMN��EHPLMN */
            NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);
            NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);
        }
        if ((USIMM_USIM_EFHPLMNwACT_ID == ulFileId)
            || (USIMM_GSM_EFHPLMNACT_ID == ulFileId))
        {
            /* ��Ҫ���¸����ȼ������б��� */
            ulHighPrioPlmnRefreshFlag = VOS_TRUE;

            /* HOME PLMN WITH RAT������ˢ�º���Ҫ��SIM�е�EHplmn���з��򹹽���
              �������뼼�����г�ʼ��ΪĬ��ֵ��ɾ���ظ���PLMN ID */
            NAS_MML_ResumeSimEhplmnList(&pstEHPlmnInfo->ucEhPlmnNum,
                                         pstEHPlmnInfo->astEhPlmnInfo);

            /* ����HPLMN���뼼�� */
            NAS_MMC_UpdateEhplmnRat();
        }

        /* 6F31�ļ������������� */
        if ((USIMM_USIM_EFHPPLMN_ID == ulFileId)
            || (USIMM_GSM_EFHPLMN_ID == ulFileId))
        {
            NAS_MMC_ProcScanCtrl_PreProc((VOS_UINT16)ulEfLen, pucEf);
        }

    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRefreshFileContent);
    /* Modified by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */




    /* H��U��O�ļ������仯��Ҫˢ��ʱ,���BG����״̬��������ʱ,Ϊ����Ե�ǰ�����б����Ӱ��
       �Ȼ��浱ǰUSIM�ļ�ˢ����Ϣ��BG����״̬���˳�����ˢ�¸����ȼ������б�;����ֱ��ˢ����
       �ȼ������б� */

    if (VOS_TRUE == ucBufferRefreshFlg)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == ulHighPrioPlmnRefreshFlag)
    {
        return NAS_MMC_ProHighPrioPlmnRefreshInd_PreProc();
    }


    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccUpdateUplmnNtf_PreProc
 ��������  : MMC�յ�MSCC�ĸ���UPLMN���ļ�֪ͨ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:״̬���������
             VOS_FALSE:״̬��δ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��31��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccUpdateUplmnNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;

    /* ���и����ȼ��б�ˢ�µ�Ԥ���� */
    ulRslt = NAS_MMC_ProHighPrioPlmnRefreshInd_PreProc();

    return ulRslt;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcAgentUsimReadFileCnf_PreProc
 ��������  : MMC�����ȡUSIM�ļ��ظ��Ĵ���
 �������  : VOS_UINT16 usEfId
             VOS_UINT16 usEfLen
             VOS_UINT8 *pucEf
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� /z00214637
    �޸�����   : PS_USIM_GET_FILE_RLT_SUCCESS�滻ΪVOS_OK
  3.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcAgentUsimReadFileCnf_PreProc(
    VOS_UINT16                          usEfId,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    USIMM_READFILE_CNF_STRU            *pstUsimMmcMsg   = VOS_NULL_PTR;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulPathLength;

    ulPathLength    = 0;

    if (VOS_OK != USIMM_ChangeDefFileToPath(usEfId, &pucFilePathStr))
    {
        return;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return;
    }

    /*lint -e961*/
    pstUsimMmcMsg = (USIMM_READFILE_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, (VOS_UINT32)(sizeof(USIMM_READFILE_CNF_STRU) - 4 + usEfLen));
    /*lint +e961*/
    if (VOS_NULL_PTR == pstUsimMmcMsg)
    {
       NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcAgentUsimReadFileCnf_PreProc():ERROR:MALLOC FAIL");
       return;
    }
    /*lint -e961*/
    PS_MEM_SET(pstUsimMmcMsg, 0, (VOS_UINT32)(sizeof(USIMM_READFILE_CNF_STRU) - 4 + usEfLen));
    /*lint +e961*/
    /* ��ȡ��USIM�ļ����ݿ������� */
    pstUsimMmcMsg->stCmdResult.ulResult = VOS_OK;
    pstUsimMmcMsg->usEfLen  = usEfLen;
    pstUsimMmcMsg->stFilePath.ulPathLen = ulPathLength;
    PS_MEM_CPY(pstUsimMmcMsg->stFilePath.acPath, pucFilePathStr, pstUsimMmcMsg->stFilePath.ulPathLen + 1);
    PS_MEM_CPY(pstUsimMmcMsg->aucEf, pucEf, usEfLen);

    NAS_MMC_RcvAgentUsimReadFileCnf((PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU*)pstUsimMmcMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstUsimMmcMsg);

}

/* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsMsccAttachTypeValid
 ��������  : �ж�MSCC�����Attach��Ϣ��Attach type�Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : ��Ч
             VOS_FALSE : ��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��12��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsMsccAttachTypeValid(
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enAttachType
)
{
    if ((NAS_MSCC_PIF_ATTACH_TYPE_IMSI      != enAttachType)
     && (NAS_MSCC_PIF_ATTACH_TYPE_GPRS      != enAttachType)
     && (NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI != enAttachType))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccAttachReq_PreProc
 ��������  : MMC�յ�ATTACH�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��19��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��11��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV BBIT����
  3.��    ��   : 2012��4��20��
    ��    ��   : w00166186
    �޸�����   : DTS2012032304808����ǰ������GPRS��ֹ�б�CS ONLY ��ΪCS+PS����ѡ�����������PS��ע��
  4.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  5.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  6.��    ��   : 2012��9��4��
    ��    ��   : s00217060
    �޸�����   : DTS2012082703201����ǰ���뼼��ΪLʱ�����ֻATTACH CS������Ҫ����PS����ע��
  7.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  8.��    ��   : 2014��2��13��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������Ҫ�����Attach����֪ͨMM,GMM����ע�� */
    MSCC_MMC_ATTACH_REQ_STRU           *pstTafAttachReq;
    VOS_UINT32                          ulForbType = NAS_MML_PLMN_FORBID_NULL;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     ucCurrNetRatType;

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif


    pstTafAttachReq = (MSCC_MMC_ATTACH_REQ_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    ucCurrNetRatType = NAS_MML_GetCurrNetRatType();

    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* attach���ʹ��󣬶��� */
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    if (VOS_FALSE == NAS_MMC_IsMsccAttachTypeValid(pstTafAttachReq->enAttachType))
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMsccAttachReq_PreProc: NORMAL: Attach Type is invalid.");
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (NAS_MSCC_PIF_ATTACH_TYPE_IMSI != pstTafAttachReq->enAttachType))
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_AttachPs())
        {
            /* LTE�������ε��µ�disable LTE,��ʱ����֪ͨGU����� */
            if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
             && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
            {
                NAS_MMC_SndEnableLteNotify();
                NAS_MMC_ClearDisabledLtePlmnId();
                NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
        }
    }


#endif



    /* Modified by s00261364  for L-C��������Ŀ, 2014-3-7, begin */
    if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        ulForbType = NAS_MMC_GetCurrentLaiForbbidenType();
    }
    /* Modified by s00261364  for L-C��������Ŀ, 2014-3-7, end */

    NAS_MMC_SetAttachReqOpId(pstTafAttachReq->ulOpID);

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ǰ��L�£���������ֹL��ʱ��֪ͨLMM����ATTACH,���յ�LTE��ATTACH CNFʱ���ж��Ƿ���Ҫ�������� */
    if ( (VOS_TRUE                 == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE))
      && (NAS_MML_NET_RAT_TYPE_LTE == ucCurrNetRatType) )
    {
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
         NAS_MMC_SndLmmAttachReq(pstTafAttachReq->ulOpID, pstTafAttachReq->enAttachType, pstTafAttachReq->enEpsAttachReason);
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */

#ifdef NAS_STUB
        if (NAS_MSCC_PIF_ATTACH_TYPE_IMSI != pstTafAttachReq->enAttachType)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        }
#endif
#ifdef __PC_TRACE_RECUR__
        if (NAS_MSCC_PIF_ATTACH_TYPE_IMSI != pstTafAttachReq->enAttachType)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        }
#endif
        return VOS_TRUE;
    }
#endif

    if (NAS_MML_PLMN_FORBID_NULL != ulForbType)
    {
        if (VOS_TRUE == NAS_MMC_ProcMsccAttachReqInForbLa_PreProc(pstTafAttachReq, ulForbType))
        {
            return VOS_TRUE;
        }
    }


#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM����ATTACH���� */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
        NAS_MMC_SndLmmAttachReq(pstTafAttachReq->ulOpID, pstTafAttachReq->enAttachType, pstTafAttachReq->enEpsAttachReason);
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */

#ifdef NAS_STUB
        if (NAS_MSCC_PIF_ATTACH_TYPE_IMSI != pstTafAttachReq->enAttachType)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        }
#endif
#ifdef __PC_TRACE_RECUR__
        if (NAS_MSCC_PIF_ATTACH_TYPE_IMSI != pstTafAttachReq->enAttachType)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        }
#endif
    }

    else
#endif
    {
        /* ��MM����ATTACH���� */
        NAS_MMC_SndMmAttachReq(pstTafAttachReq->ulOpID, pstTafAttachReq->enAttachType);

        /* ��GMM����ATTACH���� */
        NAS_MMC_SndGmmAttachReq(pstTafAttachReq->ulOpID, pstTafAttachReq->enAttachType);
    }


    return VOS_TRUE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmGprsServiceInd_PreProc
 ��������  : MMC�յ�GMM��gprs service ind�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmGprsServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMCGMM_GPRS_SERVICE_IND_STRU                           *pstGprsServiceInd;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
    pstGprsServiceInd     = (MMCGMM_GPRS_SERVICE_IND_STRU *)pstMsg;

    if (NAS_MMC_GMM_GPRS_SERVICE_ATTACH == pstGprsServiceInd->enGprsServiceType)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_AttachPs())
        {
            /* LTE�������ε��µ�disable LTE,��ʱ����֪ͨGU����� */
            if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
             && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
            {
                NAS_MMC_SndEnableLteNotify();
                NAS_MMC_ClearDisabledLtePlmnId();
                NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
        }
    }
#endif

    return VOS_TRUE;
}

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccSignReportReq_PreProc
 ��������  : MMC�յ�mscc��ID_MSCC_MMC_SIGN_REPORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��5��
    ��    ��   : s00217060
    �޸�����   : ����״̬��ʾ�Ż� PhaseI����MMC֪ͨLMM�ź������ϱ����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccSignReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_SIGN_REPORT_REQ_STRU       *pstSignReport = VOS_NULL_PTR;
    NAS_MMC_MAINTAIN_CTX_STRU           *pstMainCtx    = VOS_NULL_PTR;

    pstSignReport = (MSCC_MMC_SIGN_REPORT_REQ_STRU *)pstMsg;


    if ( (pstSignReport->ucActionType > NAS_MMC_AT_ACTION_TYPE_STOP)
      || (pstSignReport->ucRrcMsgType > NAS_MML_SIGN_REPORT_MSG_TYPE))
    {

        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMsccSignReportReq_PreProc: NORMAL: ucActionType or ucRrcMsgType is invalid.");
        return VOS_TRUE;
    }

    pstMainCtx = NAS_MMC_GetMaintainInfo();

    pstMainCtx->ucActionType  = pstSignReport->ucActionType;
    pstMainCtx->ucMsgType     = pstSignReport->ucRrcMsgType;

    if ((pstSignReport->ucSignThreshold != pstMainCtx->ucSignThreshold)
     || (pstSignReport->ucMinRptTimerInterval != pstMainCtx->ucMinRptTimerInterval))
    {
        pstMainCtx->ucSignThreshold       = pstSignReport->ucSignThreshold;
        pstMainCtx->ucMinRptTimerInterval = pstSignReport->ucMinRptTimerInterval;

        /* �ź��������޻��߼��ʱ��ı�ʱдnv */
        NAS_MMC_WriteCellSignReportCfgNvim(pstMainCtx->ucSignThreshold,pstMainCtx->ucMinRptTimerInterval);
    }

    /* ֪ͨ������ź��������޺�ʱ���� */
    NAS_MMC_SndWasInfoReportReq();
    NAS_MMC_SndGasInfoReportReq();
#if (FEATURE_LTE == FEATURE_ON)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    return VOS_TRUE;
}

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-3-30, end */

/* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccOtherModemInfoNotify_PreProc
 ��������  : MMC�յ�mscc��ID_MSCC_MMC_OTHER_MODEM_INFO_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccOtherModemInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                                    stOtherModemPlmnId;
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                    stSndLmmOtherModemInfoMsg;
#endif

    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstOtherModemInfoNotify    = VOS_NULL_PTR;

    NAS_MMC_NCELL_SEARCH_INFO_STRU                         *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();

    pstOtherModemInfoNotify = (MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    PS_MEM_SET(&stSndLmmOtherModemInfoMsg, 0, sizeof(stSndLmmOtherModemInfoMsg));

    if (VOS_TRUE == pstOtherModemInfoNotify->bitOpCurrCampPlmnId)
    {
        stOtherModemPlmnId.ulMcc = pstOtherModemInfoNotify->stCurrCampPlmnId.ulMcc;
        stOtherModemPlmnId.ulMnc = pstOtherModemInfoNotify->stCurrCampPlmnId.ulMnc;
        NAS_MMC_SetOtherModemPlmnId(&stOtherModemPlmnId);

        /* ƽ̨����֧��L��֪ͨL */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
        {
            stSndLmmOtherModemInfoMsg.bitOpCurrCampPlmnId = VOS_TRUE;
            NAS_MML_ConvertNasPlmnToLMMFormat(&(stSndLmmOtherModemInfoMsg.stCurrCampPlmnId), &stOtherModemPlmnId);

            /* ֪ͨL����פ��plmn��Ϣ */
            NAS_MMC_SndLmmOtherModemInfoNotify(&stSndLmmOtherModemInfoMsg);
        }
    }
#endif

    if (VOS_TRUE == pstOtherModemInfoNotify->bitOpEplmnInfo)
    {
        pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum = pstOtherModemInfoNotify->stEplmnInfo.ucEquPlmnNum;
        PS_MEM_CPY(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr, pstOtherModemInfoNotify->stEplmnInfo.astEquPlmnAddr,
                   sizeof(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccOtherModemDplmnNplmnInfoNotify_PreProc
 ��������  : MMC�յ�mma��other modem dplmn nplmn info ind��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11����
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccOtherModemDplmnNplmnInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU      *pstOtherModemDplmnNplmnInfoNotify    = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                                              *pucImsi = VOS_NULL_PTR;
    VOS_UINT32                                              ulStep;
    NAS_MML_LAI_STRU                                        stTempLai;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_PLMN_ID_STRU                                    stHplmnId;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    VOS_UINT16                                              usSimRat;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain;
    VOS_UINT32                                              usIsInDplmnList;
    VOS_UINT32                                              usIsInNplmnList;

    pstOtherModemDplmnNplmnInfoNotify = (MSCC_MMC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)pstMsg;

    /* ȡ���ֻ�����IMSI����Ϣ */
    pucImsi    = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHplmnId                = NAS_MML_GetImsiHomePlmn(pucImsi);

    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));
    enRegDomain              = NAS_MMC_REG_DOMAIN_BUTT;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* ��ǰ��Hplmn Id����Other Modem���͹�����EHplmn�У��򲻸���DPLMN */
    if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimBcdPlmnList(&stHplmnId,
                                                              pstOtherModemDplmnNplmnInfoNotify->ucEHplmnNum,
                                                              pstOtherModemDplmnNplmnInfoNotify->aucEHplmnList))
    {
        return VOS_TRUE;
    }

    pstNvimCfgDPlmnNPlmnInfo = (NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstNvimCfgDPlmnNPlmnInfo)
    {
        return VOS_TRUE;
    }

    PS_MEM_CPY(pstNvimCfgDPlmnNPlmnInfo,
        &pstOtherModemDplmnNplmnInfoNotify->stSelfLearnDplmnNplmnInfo, sizeof(NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU));

    /* ��other modem��DPLMN�ͱ�modem��DPLMNƴ������nplmn��ƴ */
    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-30, begin */
        (VOS_VOID)PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList + (ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);
        stTempLai.stPlmnId = stTempPlmn;

        /* �洢PLMN��Ӧ��RAT */
        usSimRat    = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                                 | pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        /* other Modem��DPLMNƴ�ӵ���MODEMʱ��������Ϣ��Ϊ��ѧϰ���ͣ������޸��˱�MODEM��Ԥ��������Ϣ */
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-30, end */

        /* ���LTE RAT��¼ */
        if (NAS_MML_SIM_RAT_E_UTRN == (NAS_MML_SIM_RAT_E_UTRN & usSimRat))
        {
            usIsInDplmnList = VOS_FALSE;
            usIsInDplmnList = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, NAS_MML_SIM_RAT_E_UTRN, pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            usIsInNplmnList = VOS_FALSE;
            usIsInNplmnList = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, NAS_MML_SIM_RAT_E_UTRN, pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            /* ������Ҫ��ӵ�DPLMN����NPLMNҲ����DPLMN�У�����Ҫ��� */
            if ((VOS_TRUE != usIsInDplmnList)
                && (VOS_TRUE != usIsInNplmnList))
            {
                stTempLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_LTE;
                NAS_MMC_UpdateDPlmnNPlmnList(&stTempLai, enRegDomain, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum,pstDPlmnNPlmnCfgInfo->astDPlmnList);
            }
        }

        /* ���WCDMA RAT��¼ */
        if (NAS_MML_SIM_RAT_UTRN == (NAS_MML_SIM_RAT_UTRN & usSimRat))
        {
            usIsInDplmnList = VOS_FALSE;
            usIsInDplmnList = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, NAS_MML_SIM_RAT_UTRN, pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            usIsInNplmnList = VOS_FALSE;
            usIsInNplmnList = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, NAS_MML_SIM_RAT_UTRN, pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            /* ������Ҫ��ӵ�DPLMN��NPLMN�У�����Ҫ��� */
            if ((VOS_TRUE != usIsInDplmnList)
                && (VOS_TRUE != usIsInNplmnList))
            {
                stTempLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_WCDMA;
                NAS_MMC_UpdateDPlmnNPlmnList(&stTempLai, enRegDomain, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum,pstDPlmnNPlmnCfgInfo->astDPlmnList);
            }
        }

        /* ���GSM RAT��¼ */
        if (NAS_MML_SIM_RAT_GSM == (NAS_MML_SIM_RAT_GSM & usSimRat))
        {
            usIsInDplmnList = VOS_FALSE;
            usIsInDplmnList = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, NAS_MML_SIM_RAT_GSM, pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            usIsInNplmnList = VOS_FALSE;
            usIsInNplmnList = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, NAS_MML_SIM_RAT_GSM, pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            /* ������Ҫ��ӵ�DPLMN��NPLMN�У�����Ҫ��� */
            if ((VOS_TRUE != usIsInDplmnList)
                && (VOS_TRUE != usIsInNplmnList))
            {
                stTempLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_GSM;
                NAS_MMC_UpdateDPlmnNPlmnList(&stTempLai, enRegDomain, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum,pstDPlmnNPlmnCfgInfo->astDPlmnList);
            }
        }
    }

    NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

    NAS_MMC_LogDplmnNplmnList();

    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgDPlmnNPlmnInfo);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccNcellInfoNotify_PreProc
 ��������  : MMC�յ�mscc��ID_MSCC_MMC_NCELL_INFO_NOTIFY��Ϣ��Ԥ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccNcellInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_NCELL_INFO_NOTIFY_STRU                         *pstNcellInfoInd = VOS_NULL_PTR;
    NAS_MMC_NCELL_SEARCH_INFO_STRU                         *pstMmcNcellSearchInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucIsNeedNcellSearch;
    VOS_UINT8                                               ucIsNcellInfoChgFromNone;

    ucIsNcellInfoChgFromNone = VOS_FALSE;
    ucIsNeedNcellSearch      = VOS_FALSE;

    pstNcellInfoInd = (MSCC_MMC_NCELL_INFO_NOTIFY_STRU *)pstMsg;
    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();

    if (((0 == pstMmcNcellSearchInfo->stTdsNcellInfo.ucTdsArfcnNum)
      && (0 == pstMmcNcellSearchInfo->stLteNcellInfo.ucLteArfcnNum) )
     && ((0 != pstNcellInfoInd->stTdsNcellInfo.ucTdsArfcnNum)
      || (0 != pstNcellInfoInd->stLteNcellInfo.ucLteArfcnNum) ) )
    {
        ucIsNcellInfoChgFromNone = VOS_TRUE;
    }

    /* ����mmc ���ֵ�ncell���ȫ�ֱ���*/
    pstMmcNcellSearchInfo->stTdsNcellInfo.ucTdsArfcnNum = pstNcellInfoInd->stTdsNcellInfo.ucTdsArfcnNum;
    PS_MEM_CPY(pstMmcNcellSearchInfo->stTdsNcellInfo.ausTdsArfcnList, pstNcellInfoInd->stTdsNcellInfo.ausTdsArfcnList,
               sizeof(pstMmcNcellSearchInfo->stTdsNcellInfo.ausTdsArfcnList));

    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteArfcnNum = pstNcellInfoInd->stLteNcellInfo.ucLteArfcnNum;
    PS_MEM_CPY(pstMmcNcellSearchInfo->stLteNcellInfo.aulLteArfcnList, pstNcellInfoInd->stLteNcellInfo.aulLteArfcnList,
               sizeof(pstMmcNcellSearchInfo->stLteNcellInfo.aulLteArfcnList));


    /* �յ�tds��lte����Ƶ����Ϣ�������ʱ��ͨ��available��ʱ�������У�
       ����1 mian������Ҫֹͣ��������1s��ʱ����1s��ʱ����ʱ����ncell�� */
    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        ucIsNeedNcellSearch = NAS_MMC_IsNeedNcellSearch();
    }

    if ((NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
     && (VOS_TRUE == ucIsNeedNcellSearch)
     && (VOS_TRUE == ucIsNcellInfoChgFromNone))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPsTransferInd_PreProc
 ��������  : MMC�յ�mscc��ID_MSCC_MMC_PS_TRANSFER_IND��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��6��
    ��    ��   : z00161729
    �޸�����   : DTS2014010202583:SVLTE�Ż�G-TL ps�л������޸�
  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
  3.��    ��   : 2014��03��28��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ,������ѡ�����Ҳ����Available��ʱ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPsTransferInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PS_TRANSFER_NOTIFY_STRU       *pstPsTransferInd    = VOS_NULL_PTR;
    /* Added by s00246516 for L-C��������Ŀ, 2014-03-28, Begin */

    /* Added by s00246516 for L-C��������Ŀ, 2014-03-28, ENd */
    NAS_MMC_TIMER_STATUS_ENUM_U8        enAvailableTimerStatus;
    VOS_UINT8                           ucPsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);
    ucPsAttachAllow        = NAS_MML_GetPsAttachAllowFlg();
    enMsMode               = NAS_MML_GetMsMode();

    pstPsTransferInd       = (MSCC_MMC_PS_TRANSFER_NOTIFY_STRU *)pstMsg;

    /* ���pstransfer�ϱ�Ϊ1���ҵ�ǰavailable��ʱ�������У���ֹͣ��������available��ʱ�� */
    if ( (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
      && (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
      && (VOS_FALSE == ucPsAttachAllow)
      && (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        /* ������ʽ��ѡ����������ʱ�� */
        if (MTC_PS_TRANSFER_OFF_AREA != pstPsTransferInd->enSolutionCfg)
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
        }
        /* Added by s00246516 for L-C��������Ŀ, 2014-03-28, Begin */
        else
        {
            /* �趨Ϊ�ڶ��׶� */
            NAS_MMC_ResetOosPhaseNum();
            NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());
            NAS_MMC_AddOosPhaseNum();

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
        }
        /* Added by s00246516 for L-C��������Ŀ, 2014-03-28, Edn */
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcMsccAttachReqInForbLa_PreProc
 ��������  : ��פ���ڽ�ֹLAʱ��MSCC��Attach������
 �������  : pstTafAttachReq
              ulForbType
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
             VOS_FALSE:δ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��10��
   ��    ��   : s00210760
   �޸�����   : DTS2012102902559:�ֶ�����ʱ����ʹPLMN��ForbLa�б��ҲҪ�ж��Ƿ���ҪDisable Lte
 3.��    ��   : 2012��12��24��
   ��    ��   : l00171473
   �޸�����   : DTS2012121005587: Ŀǰ�ú�������ֵ����ȷ, ȫ����FALSE
 4.��    ��   : 2013��01��23��
   ��    ��   : s00217060
   �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER

 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 6.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcMsccAttachReqInForbLa_PreProc(
    MSCC_MMC_ATTACH_REQ_STRU           *pstTafAttachReq,
    VOS_UINT32                          ulForbType
)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enCsMsccServiceStatus;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enPsMsccServiceStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                           ulDisableLteRoamFlg;

    VOS_UINT32                           ulNeedEnableLte;
#endif

    VOS_UINT32                           ulResult;

#if (FEATURE_ON == FEATURE_LTE)
    ulDisableLteRoamFlg         = NAS_MML_GetDisableLteRoamFlg();
#endif

    enCsMsccServiceStatus       = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);
    enPsMsccServiceStatus       = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);
#if (FEATURE_ON == FEATURE_LTE)
    ulNeedEnableLte             = VOS_FALSE;
#endif

    ulResult                    = VOS_FALSE;

    switch (pstTafAttachReq->enAttachType)
    {
        case NAS_MSCC_PIF_ATTACH_TYPE_GPRS:

            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);

            /* PS Attach��Fobid,�ظ�Attach��� */
            NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                    enPsMsccServiceStatus,
                                    pstTafAttachReq->ulOpID);

#if (FEATURE_ON == FEATURE_LTE)
            ulNeedEnableLte = NAS_MMC_IsNeedEnableLte_AttachPs();
#endif

            /* ��ǰ���ڽ�ֹ����, ���ܷ��� PS ATTACH ����, ������� */
            ulResult        = VOS_TRUE;

            break;

        case NAS_MSCC_PIF_ATTACH_TYPE_IMSI :

            if (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS != ulForbType)
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

                /* ֱ�ӻظ�ATTACH ��� */
                NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                        enCsMsccServiceStatus,
                                        pstTafAttachReq->ulOpID);


                /* ��������ܷ��� IMSI ATTACH, ������� */
                ulResult = VOS_TRUE;

            }
            else
            {
                /* GPRS��ֹ����¿��Է��� IMSI ATTACH, ��������Ҫ��������, δ������� */
                ulResult = VOS_FALSE;

            }

            break;

        case NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI :
            if (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulForbType)
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);

                /* CS+PS Attach,��gprs not allow,����CS Attach */
                NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                        enPsMsccServiceStatus,
                                        pstTafAttachReq->ulOpID);
                pstTafAttachReq->enAttachType = NAS_MSCC_PIF_ATTACH_TYPE_IMSI;


                /* ��������Է��� IMSI ATTACH, ��������Ҫ��������, δ������� */
                ulResult = VOS_FALSE;

            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);

                /* ֱ�ӻظ���� */
                NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                        enCsMsccServiceStatus,
                                        pstTafAttachReq->ulOpID);
                NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                        enPsMsccServiceStatus,
                                        pstTafAttachReq->ulOpID);


                /* ��������ܷ��� GPRS_IMSI ATTACH, ������� */
                ulResult = VOS_TRUE;
            }

#if (FEATURE_ON == FEATURE_LTE)
            ulNeedEnableLte = NAS_MMC_IsNeedEnableLte_AttachCsPs();
#endif
            break;

        default:

            /* attach���ʹ��󣬶��� */
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMsccAttachReq_PreProc: NORMAL: Attach Type is invalid.");
            return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)


    /* �ж��Ƿ���Ҫenable LTE */
    if (VOS_TRUE == ulNeedEnableLte)
    {
        ulDisableLteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisableLteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

#endif

    return ulResult;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSndRfAvailInd
 ��������  : �Ƿ���Ҫ����RfAvailInd
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedSndRfAvailInd()
{
    VOS_UINT32                          ulState;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    ulState = NAS_MMC_GetFsmTopState();
    enFsmId = NAS_MMC_GetCurrFsmId();

    if (NAS_MMC_FSM_L1_MAIN == enFsmId)
    {
        if (NAS_MMC_L1_STA_DEACT == ulState)
        {
            return VOS_FALSE;
        }
    }
    else if (NAS_MMC_FSM_POWER_OFF == enFsmId)
    {
        return VOS_FALSE;
    }
    else
    {}

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccDetachReq_PreProc
 ��������  : MMC�յ�DETACH REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��19��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��19��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸�

 3.��    ��   : 2011��11��30��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:disable/enable �����Լ�detach����
 4.��    ��   : 2012��5��10��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 6.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���

 7.��    ��   : 2014��6��25��
   ��    ��   : w00167002
   �޸�����   : DSDS III:��NO RF������MSCCά�ַ���ע��״̬��������û�����SYSCFG
                DETACH��������MSCC����ά�ַ���״̬��
                ����û�ִ�дβ�����MSCC����ά������״̬����ص��·���״̬��һ�¡�

 8.��    ��   : 2015��4��11��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
 9.��    ��   : 2015��6��12��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccDetachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MSCC_MMC_DETACH_REQ_STRU           *pstTafDetachReq = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulLteOnlyFlg;
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason;

    pstTafDetachReq = (MSCC_MMC_DETACH_REQ_STRU *)pstMsg;

    if ( (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
      && ( (NAS_MSCC_PIF_DETACH_TYPE_IMSI == pstTafDetachReq->enDetachType)
        || (NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI == pstTafDetachReq->enDetachType) ) )
    {
        if (NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI == pstTafDetachReq->enDetachType)
        {
            /* ֪ͨMSCCʧ�� */
            NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                     MM_COM_SRVST_NORMAL_SERVICE,
                                     pstTafDetachReq->ulOpID,
                                     NAS_MSCC_PIF_OPER_RESULT_REJECT);
        }

        /* ֪ͨMSCCʧ�� */
        NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                 MM_COM_SRVST_NORMAL_SERVICE,
                                 pstTafDetachReq->ulOpID,
                                 NAS_MSCC_PIF_OPER_RESULT_REJECT);
        return VOS_TRUE;
    }

    /* �����������ĺϷ��� */
    if ( ( pstTafDetachReq->enDetachType > NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI )
      || ( pstTafDetachReq->enDetachType == NAS_MSCC_PIF_DETACH_NULL ))
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_RcvMsccDetachReq_PreProc:invalid parm", pstTafDetachReq->enDetachType);
        return VOS_TRUE;
    }

    NAS_MMC_RecordOosEventForDetachReason(pstTafDetachReq->enDetachReason);



    if (VOS_TRUE == NAS_MMC_IsNeedSndRfAvailInd())
    {
        /* ��NO RF����������û���SYSCFG/DETACH����,��֪ͨMSCC���NO RF STATUS */
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);
            NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);
        }
    }

    /* ������Ϣ���ȼ��Ƚ�,�жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬���������Ϣ�Ļ��� */
    ulRet = NAS_MMC_ProcMsgPrio(ulEventType, pstMsg);

    /* ��Ҫ��ϵ�ǰ״̬���������Ϣ�Ļ���,���ʾԤ������� */
    if ( VOS_TRUE == ulRet )
    {
        /* ����LMM��MM/GMM����detach ����,����������Ϣʱ
           �ٷ���detach ���� */
        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ����detach����,����Ϣ������ɲ��ٽ���״̬
       ������ */
#if   (FEATURE_ON == FEATURE_LTE)
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    ulLteOnlyFlg = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());

    if (( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     || (VOS_TRUE                  == ulLteOnlyFlg))
    {
        /* ��LMM����DETACH���� */
        NAS_MMC_SndLmmDetachReq(pstTafDetachReq->ulOpID,
                                (VOS_UINT8)pstTafDetachReq->enDetachType,
                                pstTafDetachReq->enDetachReason);
    }
    else
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */
#endif
    {
        if ((NAS_MSCC_PIF_DETACH_REASON_3GPP2_ATTACHED == pstTafDetachReq->enDetachReason)
         || (NAS_MSCC_PIF_DETACH_REASON_BUTT       == pstTafDetachReq->enDetachReason))
        {
            enDetachReason = MMC_MM_PIF_DETACH_REASON_BUTT;
        }
        else
        {
            enDetachReason = (MMC_MM_DETACH_REASON_ENUM_UINT32)pstTafDetachReq->enDetachReason;
        }

        /* ��MM����DETACH���� */
        NAS_MMC_SndMmDetachReq(pstTafDetachReq->ulOpID,
                               (MMC_MM_DETACH_TYPE_ENUM_UINT32)pstTafDetachReq->enDetachType,
                               enDetachReason);

        /* ��GMM����DETACH���� */
        NAS_MMC_SndGmmDetachReq(pstTafDetachReq->ulOpID,
                               (MMC_GMM_DETACH_TYPE_ENUM_UINT32)pstTafDetachReq->enDetachType,
                               (MMC_GMM_DETACH_REASON_ENUM_UINT32)enDetachReason);
    }

    /* ����detach���������� */
    NAS_MMC_GetDetachReqCtxAddr()->enDetachReason = (NAS_MMC_DETACH_REASON_ENUM_UINT32)pstTafDetachReq->enDetachReason;
    NAS_MMC_GetDetachReqCtxAddr()->enDetachType   = (NAS_MMC_DETACH_TYPE_ENUM_UINT32)pstTafDetachReq->enDetachType;


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAttachCnf_PreProc
 ��������  :������ϢMMCMM_ATTACH_CNF
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��07��11��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��4��27��
   ��    ��   : l00130025
   �޸�����   : DTS2012032303156:MMC�ķ���״̬��MM/GMM�ķ���״̬��Ҫת��
 3.��    ��   : 2012��06��13��
   ��    ��   : s46746
   �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
 4.��    ��   : 2012��7��27��
   ��    ��   : s00217060
   �޸�����   : for CS/PS mode 1,��Disable LTEԭ��ֵ
 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 6.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_ATTACH_CNF_STRU              *pstMmAttachCnf;


    pstMmAttachCnf = (MMCMM_ATTACH_CNF_STRU*)pstMsg;

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* ��װ��Ϣ����MSCC����ATTACH��� */
    NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                            (NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8)pstMmAttachCnf->ulServiceStatus,
                            pstMmAttachCnf->ulOpid);


#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_AttachCs())
    {
        /* ��ǰ����ΪLTE������ʱ������disable LTE��Ϣ */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        }
        else
        {
            /* ������ε��µ�disable�Ѿ�֪ͨ��GU�����,��ʱ����Ҫ���ظ�֪ͨ */
            if (VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
            {
                NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);

                /* ��¼disable lteʱפ����������Ϣ */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
        }

        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_DETACH);
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
        }

    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmAttachCnf_PreProc
 ��������  : ����MMCGMM_ATTACH_CNF
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��07��11��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:����enable LTE�߼�
 3.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
 4.��    ��   : 2012��4��27��
   ��    ��   : l00130025
   �޸�����   : DTS2012032303156:MMC�ķ���״̬��MM/GMM�ķ���״̬��Ҫת��
 5.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : for CS/PS mode 1:����Disable/Enable����
 6.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_ATTACH_CNF_STRU             *pstGmmAttachCnf;


    pstGmmAttachCnf = (MMCGMM_ATTACH_CNF_STRU*)pstMsg;

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* ��װ��Ϣ����MSCC����ATTACH��� */
    NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                            (NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8)pstGmmAttachCnf->ulServiceStatus,
                            pstGmmAttachCnf->ulOpid);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmDetachCnf_PreProc
 ��������  :
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ

 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��07��11��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��07��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����:GU MO detach �ɹ���Ҫ֪ͨLMM
  3.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  4.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��4��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����CSPS����״̬
  8.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  9.��    ��   :2015��3��13��
    ��    ��   :n00269697
    �޸�����   :CHR �Ż���Ŀ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_DETACH_CNF_STRU              *pstMmDetachCnf = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisableLteRoamFlg;
#endif
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */


    VOS_UINT8                           ucSimCsRegStatus;

    pstMmDetachCnf = (MMCMM_DETACH_CNF_STRU*)pstMsg;

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, end */

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ����������CS����attach���ΪFALSE���޸�Ϊ���Ʒ����ϱ�-���򲻱� */
    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    if( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (NAS_MMC_NORMAL_SERVICE == enCsServiceStatus) )
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */


    /* ��MSCC����DETACH��� */
    NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                            (NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8)pstMmDetachCnf->ulServiceStatus,
                            pstMmDetachCnf->ulOpid,
                            NAS_MSCC_PIF_OPER_RESULT_SUCCESS);


    /* ���CS������ע�����CS����Ч���ϱ�csע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        /* GU��MO detach �ɹ���Ҫ֪ͨLMM */
        NAS_MMC_SndLmmMoDetachIndActionResultReq(MMC_LMM_MO_DET_CS_ONLY);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_DetachCs())
    {
        ulDisableLteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisableLteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_MoDetachIndRecord(pstMmDetachCnf->ulDetachType);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartAvailableTimer_PsDetachCnf
 ��������  : mmc�յ�ps detach cnfʱ��Ҫ�ж��Ƿ���Ҫ����available��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����available��ʱ��
             VOS_FALSE:����Ҫ����available��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : z00161729
    �޸�����   : DTS2014032105704:����TDS����˲���һ�ԭС��psǨ��modem1���ٻ�Ǩmodem0
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedStartAvailableTimer_PsDetachCnf(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT8                           ucIsSvlteSupportFlag;
    VOS_UINT8                           ucCsAttachAllowFlg;
    VOS_UINT8                           ucPsAttachAllowFlg;
    VOS_UINT32                          ulIsUsimStatusValid;
    NAS_MMC_TIMER_STATUS_ENUM_U8        enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    ucIsSvlteSupportFlag   = NAS_MML_GetSvlteSupportFlag();
    ucCsAttachAllowFlg     = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllowFlg     = NAS_MML_GetPsAttachAllowFlg();
    ulIsUsimStatusValid    = NAS_MML_IsUsimStausValid();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* psǨ�Ƶ�modem0�����l��tds 15sδע��ɹ���Ӧ�ñ�����ʱ����ʱ�Ὣps��Ǩ��modem1��
       modem0 detach ps���������l��tdsû�б�������ϵͳ��Ϣ���ᵼ��available��ʱ��δ����psǨ�Ʋ���modem0
       mmc �յ�detach cnf�ж����svlte ������cs ps������ע�ᣬ����Ч����������״̬����available��ʱ��δ������
       ������available��ʱ�� */
    if ((VOS_TRUE == ucIsSvlteSupportFlag)
     && (VOS_FALSE == ucCsAttachAllowFlg)
     && (VOS_FALSE == ucPsAttachAllowFlg)
     && (VOS_TRUE == ulIsUsimStatusValid)
     && (NAS_MMC_FSM_PLMN_SELECTION != enFsmId)
     && (NAS_MMC_FSM_ANYCELL_SEARCH != enFsmId)
     && (NAS_MMC_TIMER_STATUS_RUNING != enAvailableTimerStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmDetachCnf_PreProc
 ��������  : ������Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ

 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��07��11��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  3.��    ��   : 2011��12��07��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����:GU MO detach �ɹ���Ҫ֪ͨLMM
  4.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
  5.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  6.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  7.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : for CS/PS mode 1,��Disable LTEԭ��ֵ
  8.��    ��   : 2012��11��10��
    ��    ��   : s00217060
    �޸�����   : DTS2012102902559:�յ�GMM��Detach Cnf������Ѿ�Detach CS,��ҪEnable Lte
  9.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  10.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 11.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 12.��    ��   : 2014��3��21��
    ��    ��   : z00161729
    �޸�����   : DTS2014032105704:����TDS����˲���һ�ԭС��psǨ��modem1���ٻ�Ǩmodem0
 13.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ������CSPS����״̬
 14.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 15.��    ��   :2015��3��13��
    ��    ��   :n00269697
    �޸�����   :CHR �Ż���Ŀ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_DETACH_CNF_STRU             *pstGmmDetachCnf;

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    VOS_UINT8                           ucSimPsRegStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisableLteRoamFlg;

    ulDisableLteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    pstGmmDetachCnf = (MMCGMM_DETACH_CNF_STRU*)pstMsg;

    /* ����PS����״̬ */
    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, end */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ����������pS����attach���ΪFALSE���޸�Ϊ���Ʒ����ϱ�-���򲻱� */
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();
    if( (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (NAS_MMC_NORMAL_SERVICE == enPsServiceStatus) )
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    }
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */


    /* ��MSCC����DETACH��� */
    NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                            (NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8)pstGmmDetachCnf->ulServiceSts,
                            pstGmmDetachCnf->ulOpid,
                            NAS_MSCC_PIF_OPER_RESULT_SUCCESS);


    /* ���PS������ע�����PS����Ч���ϱ�psע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();
    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        /* GU��MO detach ��Ҫ֪ͨLMM */
        NAS_MMC_SndLmmMoDetachIndActionResultReq((MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32)(pstGmmDetachCnf->ulDetachType));
    }

    /* �ж��Ƿ���Ҫdisable LTE */
    if ( VOS_TRUE == NAS_MMC_IsNeedDisableLte_DetachPs())
    {
        /* ������ε��µ�disable�Ѿ�֪ͨ��GU�����,��ʱ����Ҫ���ظ�֪ͨ */
        if (VOS_FALSE == ulDisableLteRoamFlg)
        {
            /* ��WAS/GAS����disable LTE֪ͨ��Ϣ */
            NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);
            NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);

            /* ��LMM����disable LTE��Ϣ */
            NAS_MMC_SndLmmDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_PS_DETACH);

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_DETACH);

        /* ���detach ������������Ϣ */
        NAS_MMC_InitDetachReqCtx(NAS_MMC_GetDetachReqCtxAddr());
    }

    /* �յ�GMM��Detach Cnf������Ѿ�Detach CS,��ҪEnable Lte */
    if ( VOS_TRUE == NAS_MMC_IsNeedEnableLte_DetachPs())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisableLteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    if (VOS_TRUE == NAS_MMC_IsNeedStartAvailableTimer_PsDetachCnf())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
    }

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_MoDetachIndRecord(pstGmmDetachCnf->ulDetachType);
#endif

    return VOS_TRUE;
}

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-13, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmNetworkCapabilityInfoInd_PreProc
 ��������  : �յ�GMM�ϱ�����������������Ϣ��ת����MSCC
 �������  : ulEventType:PID+MSG TYPE�������е���Ϣ
             *pstMsg:GMM���͹�������Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��30��
    ��    ��   : b00269685
    �޸�����   : DTS2014050604659�޸�
  3.��    ��   : 2014��6��16��
    ��    ��   : y00245242
    �޸�����   : dts2014052905705�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmNetworkCapabilityInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU    *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulState;

    ulState   = NAS_MMC_GetFsmTopState();

    /* BG��״̬��ϵͳ��Ϣ�����ӳٷ��ͣ���Ҫ��ע��״̬�ͷ���״̬֮ǰ֪ͨMMA */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH                         == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND       == ulState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  == ulState)))
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }

    pstRcvMsg = (GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU *)pstMsg;

    NAS_MMC_SndMsccNetworkCapabilityInfoInd((NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8)pstRcvMsg->enNwImsVoCap,
                                           (NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8)pstRcvMsg->enNwEmcBsCap,
                                           (NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8)pstRcvMsg->enLteCsCap);

    return VOS_TRUE;
}
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-13, end */



#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmTinInd_PreProc
 ��������  :
 �������  : ulEventType:PID+MSG TYPE�������е���Ϣ
             *pstMsg:GMM���͹�������Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��21��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��18��
    ��    ��   : zhoujun /40661
    �޸�����   : TIN�ĸ�����Ҫ�ȱȽ�NV�ٴ���DTS2011111402309
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmTinInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enGmmTinType;
    MMCGMM_TIN_TYPE_IND_STRU           *pstTinTypeMsg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstTinTypeMsg   = (MMCGMM_TIN_TYPE_IND_STRU*)pstMsg;

    enGmmTinType    = pstTinTypeMsg->enTinType;


    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    if ( enGmmTinType != pstRplmnCfgInfo->enTinType)
    {
        NAS_MMC_WriteTinInfoNvim(enGmmTinType, pstRplmnCfgInfo->aucLastImsi);
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTinInd_PRE
 ��������  : ����LMM��TIN�ı����Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��30��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��18��
    ��    ��   : zhoujun /40661
    �޸�����   : TIN�ĸ�����Ҫ�ȱȽ�NV�ٴ���DTS2011111402309

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTinInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TIN_TYPE_IND_STRU          *pstTinTypeMsg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstTinTypeMsg  = (LMM_MMC_TIN_TYPE_IND_STRU*)pstMsg;

    /*��Ϣ��TINΪGUTIʱ*/
    if ( MMC_LMM_TIN_GUTI == pstTinTypeMsg->ulTinType )
    {
        /*����ȫ�ֱ�����TIN����ΪGUTI*/
        enTinType = NAS_MML_TIN_TYPE_GUTI;
    }
    else if ( MMC_LMM_TIN_RAT_RELATED_TMSI == pstTinTypeMsg->ulTinType )
    {
        /*��Ϣ��TINΪRAT-RELATED-TMSIʱ*/
        /*����ȫ�ֱ�����TIN����ΪRAT-RELATED-TMSI*/
        enTinType = NAS_MML_TIN_TYPE_RAT_RELATED_TMSI;
    }
    else if ( MMC_LMM_TIN_P_TMSI == pstTinTypeMsg->ulTinType )
    {
        /*��Ϣ��TINΪPTMSIʱ*/
        /*����ȫ�ֱ�����TIN����ΪPTMSI*/
        enTinType = NAS_MML_TIN_TYPE_PTMSI;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "Invalid Tin Type");
        return VOS_TRUE;
    }

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();
    if ( enTinType != pstRplmnCfgInfo->enTinType )
    {
        NAS_MMC_WriteTinInfoNvim(enTinType, pstRplmnCfgInfo->aucLastImsi);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmDetachCnf_PreProc
 ��������  : MMC�յ�LMM ATTACH CNF�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��19��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : �޸�Ϊ����detach����

 3.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�

 4.��    ��   : 2011��11��30��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:disable/enable �����Լ�detach����
 5.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 6.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ
 7.��    ��   : 2014��3��21��
   ��    ��   : z00161729
   �޸�����   : DTS2014032105704:����TDS����˲���һ�ԭС��psǨ��modem1���ٻ�Ǩmodem0
 8.��    ��   :2015��3��13��
   ��    ��   :n00269697
   �޸�����   :CHR �Ż���Ŀ
 9.��    ��   : 2016��1��18��
   ��    ��   : w00176964
   �޸�����   : DTS2016011802320�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf     = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    VOS_UINT8                           ucSimCsRegStatus;

    ulRet           = VOS_TRUE;

    pstLmmDetachCnf = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    /* ��װ��Ϣ����MSCC����DETACH��� */
    switch (pstLmmDetachCnf->ulReqType)
    {
        case MMC_LMM_MO_DET_PS_ONLY:

            ulRet = NAS_MMC_ProcEpsOnlyDetachCnf_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_MO_DET_CS_ONLY:

            ulRet = NAS_MMC_ProcCsOnlyDetachCnf_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_MO_DET_CS_PS:

            ulRet = NAS_MMC_ProcCsPsDetachCnf_PreProc(pstLmmDetachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_PreProc:Unexpected detach request type!");
            break;
    }


    /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_LmmDetachCnf(pstLmmDetachCnf))
    {
        NAS_MMC_ProcEmcPdpRelease_DetachPs();
    }
    /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */


    /* ���CS������ע�����CS����Ч���ϱ�csע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }


    if (VOS_TRUE == NAS_MMC_IsNeedStartAvailableTimer_PsDetachCnf())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
    }

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_MoDetachIndRecord(pstLmmDetachCnf->ulReqType);
#endif

    /* CLģʽ�����PS��detach,֪ͨMSCC��ǰLTE������,��Ҫ����DO */
    if ((VOS_FALSE               == NAS_MML_IsGULModeConfigured())
     && ((MMC_LMM_MO_DET_PS_ONLY == pstLmmDetachCnf->ulReqType)
      || (MMC_LMM_MO_DET_CS_PS   == pstLmmDetachCnf->ulReqType)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(NAS_MMC_GetMmssLteUnavailableReasonByDetachReason(NAS_MMC_GetDetachReqCtxAddr()->enDetachReason));
    }

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcAttachCnfAuthRej_PreProc
 ��������  : �յ�LMM��attach ��Ȩ���ܵ�Ԥ����
 �������  : pstLmmAttachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcAttachCnfAuthRej_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_ATTACH_AUTH_REJ);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,NAS_MMC_LIMITED_SERVICE);
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsOnlyAttachCnf_PreProc
 ��������  : �յ�LMM��LMM_MMC_ATTACH_CNF�ظ���Ԥ����
 �������  : pstLmmAttachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  2.��    ��   : 2015��12��21��
    ��    ��   : z00359541
    �޸�����   : DTS2015120105585: �յ�LMM ATTACH CNF������MMC����״̬
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcEpsOnlyAttachCnf_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{

    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enPsMmaServiceStatus;

    /* attach������� */
    switch (pstLmmAttachCnf->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:

            NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                    MM_COM_SRVST_NORMAL_SERVICE,
                                    pstLmmAttachCnf->ulOpId);

            return;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FAILURE:

            /* �����κδ��� */
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ:

            NAS_MMC_ProcAttachCnfAuthRej_PreProc(pstLmmAttachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcEpsOnlyAttachCnf_PreProc:Unexpected detach result!");
            break;
    }

    enPsMmaServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* ��ȡ��ǰPS����״̬ */
    NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                            enPsMmaServiceStatus,
                            pstLmmAttachCnf->ulOpId);
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsOnlyAttachCnf_PreProc
 ��������  : �յ�LMM��attach�ɹ���Ԥ����
 �������  : pstLmmattachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  2.��    ��   : 2015��12��21��
    ��    ��   : z00359541
    �޸�����   : DTS2015120105585: �յ�LMM ATTACH CNF������MMC����״̬
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcCsOnlyAttachCnf_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enCsMmaServiceStatus;

    switch (pstLmmAttachCnf->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                    MM_COM_SRVST_NORMAL_SERVICE,
                                    pstLmmAttachCnf->ulOpId);

            return;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FAILURE:

            /* �����κδ��� */
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ:

        NAS_MMC_ProcAttachCnfAuthRej_PreProc(pstLmmAttachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsOnlyAttachCnf_PreProc:Unexpected detach result!");
            break;
    }

    enCsMmaServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);

    NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                            enCsMmaServiceStatus,
                            pstLmmAttachCnf->ulOpId);

    return ;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsPsAttachCnf_PreProc
 ��������  : �յ�LMM��Attach�ɹ���Ԥ����
 �������  : pstLmmattachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  2.��    ��   : 2015��12��21��
    ��    ��   : z00359541
    �޸�����   : DTS2015120105585: �յ�LMM ATTACH CNF������MMC����״̬
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcCsPsAttachCnf_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enCsMmaServiceStatus;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enPsMmaServiceStatus;

    switch (pstLmmAttachCnf->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                    MM_COM_SRVST_NORMAL_SERVICE,
                                    pstLmmAttachCnf->ulOpId);

            NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                    MM_COM_SRVST_NORMAL_SERVICE,
                                    pstLmmAttachCnf->ulOpId);

            return;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FAILURE:

            /* �����κδ��� */
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ:

            NAS_MMC_ProcAttachCnfAuthRej_PreProc(pstLmmAttachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsPsAttachCnf_PreProc:Unexpected detach result!");
            break;
    }

    enCsMmaServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);
    enPsMmaServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);

    NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                            enCsMmaServiceStatus,
                            pstLmmAttachCnf->ulOpId);

    NAS_MMC_SndMsccAttachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                            enPsMmaServiceStatus,
                            pstLmmAttachCnf->ulOpId);
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachCnf_PreProc
 ��������  : MMC�յ�LMM ATTACH CNF�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��19��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��01��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  3.��    ��   : 2012��1��08��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV attach cnf�ṹ�����޸�

  4.��    ��   : 2012��4��4��
    ��    ��   : z40661
    �޸�����   : ���ⵥ��DTS2012032801382��PS ONLYʱ,��ѡ��Lģ������CS+PS
                 ��δ��GU�½���פ��
  5.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  6.��    ��   : 2012��06��7��
    ��    ��   : w00176964
    �޸�����   : DTS2012060607438:CS+PS disable LTE���û�attach PS��enable LTE
                 PS only PS����Ч,����CS+PS,��disable LTE
  7.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  8.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  9.��    ��   : 2012��9��3��
    ��    ��   : s00217060
    �޸�����   : DTS2012082703201:Disable LTEʱ������Disable Lte��־��ԭ��ֵ����returnǰ��
 10.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
 11.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 12.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 13.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 14.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_ATTACH_CNF_STRU             *pstLmmAttachCnf;
    NAS_MMC_FSM_ID_ENUM_UINT32           enFsmId;
    VOS_UINT32                           ulDisableLteRoamFlg;

    VOS_UINT32                           ulNeedEnableLte;
    VOS_UINT32                           ulNeedDisableLte;


    pstLmmAttachCnf = (LMM_MMC_ATTACH_CNF_STRU*)pstMsg;


    /* ��װ��Ϣ����MSCC����ATTACH��� */

    ulNeedEnableLte  = VOS_FALSE;
    ulNeedDisableLte = VOS_FALSE;


    switch (pstLmmAttachCnf->ulReqType)
    {
        case MMC_LMM_ATT_REQ_TYPE_PS_ONLY:
            NAS_MMC_ProcEpsOnlyAttachCnf_PreProc(pstLmmAttachCnf);

            ulNeedEnableLte = NAS_MMC_IsNeedEnableLte_AttachPs();

            break;

        case MMC_LMM_ATT_REQ_TYPE_CS_PS:
            NAS_MMC_ProcCsPsAttachCnf_PreProc(pstLmmAttachCnf);

            ulNeedEnableLte = NAS_MMC_IsNeedEnableLte_AttachCsPs();
            ulNeedDisableLte = NAS_MMC_IsNeedDisableLte_AttachCsPs();

            break;

        case MMC_LMM_ATT_REQ_TYPE_CS_ONLY:
            NAS_MMC_ProcCsOnlyAttachCnf_PreProc(pstLmmAttachCnf);

            ulNeedDisableLte = NAS_MMC_IsNeedDisableLte_AttachCs();
            break;

        default:
            /* �쳣��ӡ */
            break;
    }


    /* �ж��Ƿ���Ҫenable LTE */
    if (VOS_TRUE == ulNeedEnableLte)
    {
        ulDisableLteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisableLteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
        return VOS_TRUE;
    }

    enFsmId = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* �ж��Ƿ���Ҫdisable LTE */
    if (VOS_TRUE == ulNeedDisableLte)
    {
        /* ��¼����disable LTE�ı��,����L��Ϊ��ģ��֪ͨLMM,WAS,GAS */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_DETACH);
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
        }

        /* ON PLMN��ֱ�ӿ��Դ��� */
        if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
        && (NAS_MMC_FSM_L1_MAIN == enFsmId))
        {
           /* �����ǰEPS�������Ӵ��ڣ��򻺴湹���������Ϣ */
           if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
           {
               NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE);

               return VOS_TRUE;
           }
        }

        /* ����״̬�����д��� */
        return VOS_FALSE;
    }



    /* L->LWG�󣬻���DETACH CS/PS��MSCC���յ�SYSCFG CNFʱ�����·�ATTACH CS/PS��ATTACHʧ��ʱ��Ҫ�������� */
    if ( VOS_TRUE == NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch(pstLmmAttachCnf) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* ɾ����LMM��ʽ��EPSע��״̬��ת��ΪMML��ע��״̬�Ľӿ�
   NAS_MMC_CovertLmmRegStatusToMmlRegStatus() */

/* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�   NAS_MMC_RcvLmmRegStatusChangeInd_PreProc()������ */

/* ɾ����LMM�ϱ��ķ���״̬ת��ΪMMC�ķ���״̬�Ľӿ�
   NAS_MMC_ConvertLmmServiceStatusToMmcServiceStatus() */

/* ɾ����LMM�ϱ��ķ���״̬ת��ΪMMC�ϱ��õķ���״̬�Ľӿ�
   NAS_MMC_ConvertLmmServiceStatusToMmcReportSrvSt() */

/* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�*/



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmErrInd_PreProc
 ��������  : LMM�ϱ���ERR IND��Ϣ�ӿ�
 �������  : ulEventType:ID_LMM_MMC_ERR_IND��ϢID
              pstMsg: ID_LMM_MMC_ERR_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��

  3.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmErrInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����OAM�Ľӿ�ֱ�ӽ��и�λ  */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_ERR_IND);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendCnf_PreProc
 ��������  : �յ�LMM�Ĺ���ظ���Ϣ�Ĵ���
 �������  : ulEventType:ID_LMM_MMC_SUSPEND_CNF��ϢID
             pstMsg: ID_LMM_MMC_SUSPEND_CNF��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
  3.��    ��   : 2012��06��7��
    ��    ��   : w00176964
    �޸�����   : DTS2012060607438:disable LTE��Ҫ����������¹���L��GU��֪ͨGUL disable LTE
  4.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : for CS/PS mode 1,��Disable LTEԭ��ֵ
  5.��    ��   : 2012��12��15��
    ��    ��   : l65478
    �޸�����   : DTS2012120508936:�ڷ����������ʱ��Ҫdisable LTE
  6.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : SVLTE �޸�
  7.��    ��   : 2014��5��7��
    ��    ��   : s00217060
    �޸�����   : DTS2014043000876:���������Disable LTEʱ��Ҫ�ж�IMS�Ƿ����
  8.��    ��   : 2014��11��18��
    ��    ��   : b00269685
    �޸�����   : DPLMN&NPLMN�޸�
  9.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucEmcFlg;
    VOS_UINT8                           ucImsVoiceAvail;

    /* Lģʱ�������¸�ʽת�� */
    pstLmmSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* ��������Ϊ�ɹ�������״̬������ */
    if ( MMC_LMM_SUCC != pstLmmSuspendCnf->ulRst)
    {
        return VOS_FALSE;
    }

    /* �ж��Ƿ���Ҫdisable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
    {
        /* ������ε��µ�disable�Ѿ�֪ͨ��GU�����,��ʱ����Ҫ���ظ�֪ͨ */
        if (VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
        {
            NAS_MMC_SndDisableLteNotify(NAS_MML_GetDisableLteReason());

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());

            if (MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED == NAS_MML_GetDisableLteReason())
            {
                NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);
            }
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

        NAS_MML_SetDisableLteReason(NAS_MML_GetDisableLteReason());
    }
    else
    {
        /* �ڽ������в���ͨ��CSFB��GUʱ,����rel-11 24.301 4.3.1��Ҫdisable LTE.Ŀǰ������һ��disableʱ��Ϊ5MINS.
           5mins������enable LTE */
        /* 3GPP 24.301 Selection 4.3.1:
           if the UE needs to initiate a CS fallback emergency call but it is unable to perform CS fallback,
           the UE shall attempt to select GERAN or UTRAN radio access technology,
           and a UE with "IMS voice not available" should disable the E-UTRA capability (see subclause 4.5) to allow a potential callback,
           and then progress the CS emergency call establishment;

           NOTE 2: Unable to perform CS fallback or 1xCS fallback means that either the UE was not allowed to attempt CS fallback or 1xCS fallback,
           or CS fallback or 1xCS fallback attempt failed.
        */
        /* Disable LTEʱ��Ҫ�ж�IMS�Ƿ���ã�IMS����ʱ��Disable LTE */
        ucEmcFlg        = NAS_MML_GetCsEmergencyServiceFlg();
        ucImsVoiceAvail = NAS_MML_GetImsVoiceAvailFlg();
        if (((NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
          || (VOS_TRUE == ucEmcFlg))
         && (VOS_FALSE  == ucImsVoiceAvail))

        {
            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL);

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsfbEmgCallEnableLteTimerLen());
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachInd_PreProc
 ��������  : �յ�LMM�ı���detach�Ĵ���
 �������  : ulEventType:ID_LMM_MMC_DETACH_IND��ϢID
             pstMsg: ID_LMM_MMC_DETACH_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2013��12��23��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ

  5.��    ��   : 2014��4��14��
    ��    ��   : w00242748
    �޸�����   : DTS2014041506202:����L��DETACH����CM SERVICE REJ����ԭ��ֵ���ϱ���


  4.��    ��   : 2014��3��10��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:L��ѡ��Cʱ��L�»���DETACH״̬����ʱMM/GMM��֪ͨ
                 ΪNO SERVICE״̬����ʱ���յ�LMM��DETACH INDʱ�򣬲���Ҫ���õ�ǰΪ
                 LIMIT SERVICE��
  5.��    ��   : 2014��4��14��
    ��    ��   : w00242748
    �޸�����   : DTS2014041506202:����L��DETACH����CM SERVICE REJ����ԭ��ֵ���ϱ���
  6.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8                  enDetachType;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCause;

    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    enDetachType        = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_BUTT;
    enCause             = NAS_MML_REG_FAIL_CAUSE_BUTT;

    if ( VOS_FALSE == pstDetachMsg->bitOpCnCause )
    {
        enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }
    else
    {
        NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstDetachMsg->ucCnCause,
                                                &enCause);
    }

    /* UE����DETACH���磺ȥ�������г��أ�ͨ��DETACH������MMC_LMM_DETACH_LOCAL
    ֪ͨMMC����Я������ֵ */
    if (MMC_LMM_DETACH_LOCAL == pstDetachMsg->ulDetachType)
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_LOCAL_DETACH);

        /* Modified by w00167002 for L-C��������Ŀ, 2014-3-10, begin */
        if (NAS_MMC_NO_SERVICE != NAS_MMC_GetPsServiceStatus())
        {
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
        }
        else
        {
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_NO_SERVICE);
        }

        if (NAS_MMC_NO_SERVICE != NAS_MMC_GetCsServiceStatus())
        {
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
        }
        else
        {
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_NO_SERVICE);
        }

        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        /* Modified by w00167002 for L-C��������Ŀ, 2014-3-10, end */

        /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
        /* ����PDN���Ӵ���ʱ:������Ӵ��ڱ�־����LMM/GUAS����EPLMN֪ͨ��ɾ��Forb Plmn */
        NAS_MMC_ProcEmcPdpRelease_DetachPs();
        /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */

        /* ��GMM��MMת��ע������Ϣ */
        NAS_MMC_SndMmLmmLocalDetachInd(pstDetachMsg);
        NAS_MMC_SndGmmLmmLocalDetachInd(pstDetachMsg);

        /* CLģʽ�����PS��detach,֪ͨMSCC��ǰLTE������,��Ҫ����DO */
        if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_MT_DETACH);
        }

        return VOS_TRUE;
    }

    if ( VOS_TRUE == pstDetachMsg->bitOpCnReqType )
    {
        NAS_MMC_ConvertLmmDetachIndTypeToMmcType(pstDetachMsg->ulCnReqType, &enDetachType);

        NAS_MMC_SndMsccDetachInd(NAS_MSCC_PIF_SRVDOMAIN_PS, (VOS_UINT32)enDetachType, (VOS_UINT32)enCause);
    }

    return VOS_FALSE;
}

/* Modified by z40661 for V7R1 ��� , 2012-02-20, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PreProc
 ��������  : �յ�LMM�ķ���״̬��Ԥ����
 �������  : ulEventType:ID_LMM_MMC_STATUS_IND��ϢID
              pstMsg: ID_LMM_MMC_STATUS_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��20��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��02��
    ��    ��   : l00130025
    �޸�����   : DTS2012022102014:L->G->L->G��û�����·���TLLI,����G��RAU������ImplicityDetached
  3.��    ��   : 2012��11��08��
    ��    ��   : s00217060
    �޸�����   : �յ�LMM��Status_Ind��Ϣʱ������EPS������״̬
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2014��06��27��
    ��    ��   : s00217060
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;


    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PreProc:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);


    NAS_MMC_SndGmmLmmStatusInd(pstLmmStatusIndMsg);


    if ( MMC_LMM_CONNECTED_DATA == pstLmmStatusIndMsg->ulConnState )
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_DATA);

        /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-16, Begin */
        NAS_MMC_SndMsccPsServiceConnStatusInd(VOS_TRUE, MSCC_MMC_PS_SIGNALING_TYPE_LTE);
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-16, End */
    }
    else
    {
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_IDLE);
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
        NAS_MMC_SndMsccPsServiceConnStatusInd(VOS_FALSE, MSCC_MMC_PS_SIGNALING_TYPE_LTE);
        /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
    }

    /* ����δ������� */
    return VOS_FALSE;
}

/* Modified by z40661 for V7R1 ��� , 2012-02-20, end */




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PreProc
 ��������  : �յ�LMM�Ķ�����Ԥ����
 �������  : ulEventType:ID_LMM_MMC_AREA_LOST_IND��ϢID
             pstMsg: ID_LMM_MMC_AREA_LOST_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��12��
    ��    ��   : w00167002
    �޸�����   : DSDS III:��NO RF������֪ͨMSCC
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU         *pstLmmAreaLostMsg   = VOS_NULL_PTR;

    pstLmmAreaLostMsg   = (LMM_MMC_AREA_LOST_IND_STRU *)pstMsg;

    if (MMC_LMM_AREA_LOST_REASON_NO_RF == pstLmmAreaLostMsg->enAreaLostReason)
    {
        /* ����area lost no rf */
        NAS_MMC_ProcNoRfAreaLost_PreProc(NAS_MML_NET_RAT_TYPE_LTE);

        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LMM_NO_RF_AREA_LOST);

        return VOS_FALSE;
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LMM_NORMAL_AREA_LOST);

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLteSrvDoaminToMmcSrvDomain
 ��������  : ��LTE��sim�����������ת��Ϊmmc sim�����������
 �������  : enLteSimSrvDomain    - Lte sim�����������
 �������  : penSrvDomain         - MMC��ʽ�ķ�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��6��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLteSrvDoaminToMmcSrvDomain(
    LMM_MMC_SRV_DOMAIN_ENUM_UINT8       enLteSimSrvDomain,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32           *penSrvDomain
)
{
    switch (enLteSimSrvDomain)
    {
        case LMM_MMC_SRV_DOMAIN_CS:
           *penSrvDomain = NAS_MSCC_PIF_SRVDOMAIN_CS;
            break;

        case LMM_MMC_SRV_DOMAIN_PS:
           *penSrvDomain = NAS_MSCC_PIF_SRVDOMAIN_PS;
            break;

        case LMM_MMC_SRV_DOMAIN_CS_PS:
           *penSrvDomain = NAS_MSCC_PIF_SRVDOMAIN_CS_PS;
            break;

        default:
           *penSrvDomain = NAS_MSCC_PIF_SRVDOMAIN_CS_PS;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLteSimAuthFailToMmcSimAuthFail
 ��������  : ��LTE��sim�������ʽת��Ϊmmc sim�������ʽ
 �������  : enLteSimAuthFailRejCause    - Lte sim����ԭ��ֵ
 �������  : penMmcSimAuthFailRejCause   - MMC��ʽ��simԭ��ֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��6��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLteSimAuthFailToMmcSimAuthFail(
    LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16   enLteSimAuthFailRejCause,
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16  *penMmcSimAuthFailRejCause
)
{
    switch (enLteSimAuthFailRejCause)
    {
        case LMM_MMC_SIM_AUTH_FAIL_NULL:
           *penMmcSimAuthFailRejCause = NAS_MML_SIM_AUTH_FAIL_NULL;
            break;

        case LMM_MMC_SIM_AUTH_FAIL_MAC_FAILURE:
           *penMmcSimAuthFailRejCause = NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE;
            break;

        case LMM_MMC_SIM_AUTH_FAIL_SYNC_FAILURE:
           *penMmcSimAuthFailRejCause = NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE;
            break;

        case LMM_MMC_SIM_AUTH_FAIL_OTHER:
           *penMmcSimAuthFailRejCause = NAS_MML_SIM_AUTH_FAIL_LTE_OTHER_FAILURE;
            break;

        default:
           *penMmcSimAuthFailRejCause = NAS_MML_SIM_AUTH_FAIL_LTE_OTHER_FAILURE;
            break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSimAuthFailInd_PreProc
 ��������  : �յ�LMM��sim fail����Ϣ
 �������  : ulEventType:ID_LMM_MMC_SIM_AUTH_FAIL_IND��ϢID
             pstMsg: ID_LMM_MMC_SIM_AUTH_FAIL_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��5��
    ��    ��   : b00269685
    �޸�����   : �յ�LMM sim ������Ϣ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSimAuthFailInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SIM_AUTH_FAIL_IND_STRU     *pstLmmSimAuthFailMsg   = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32            enSrvDomain;
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enRejCause;

    pstLmmSimAuthFailMsg   = (LMM_MMC_SIM_AUTH_FAIL_IND_STRU *)pstMsg;

    NAS_MMC_ConvertLteSrvDoaminToMmcSrvDomain(pstLmmSimAuthFailMsg->enSrvDomain, &enSrvDomain);

    NAS_MMC_ConvertLteSimAuthFailToMmcSimAuthFail(pstLmmSimAuthFailMsg->enSimAuthFailValue, &enRejCause);

    NAS_MMC_SndMsccUsimAuthFailInd(enSrvDomain, enRejCause);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTimerStateNotify_PreProc
 ��������  : �յ�LMM��ʱ��״̬��Ϣ�Ĵ���
 �������  : ulEventType - ID_LMM_MMC_TIMER_STATE_NOTIFY��ϢID
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��27��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTimerStateNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerInfoNotify;

    pstTimerInfoNotify = (LMM_MMC_TIMER_STATE_NOTIFY_STRU *)pstMsg;

    if ((VOS_TRUE == pstTimerInfoNotify->bitOpT3412)
     && (LMM_MMC_TIMER_BUTT != pstTimerInfoNotify->enT3412State))
    {
        NAS_MML_SetT3412Status((VOS_UINT8)(pstTimerInfoNotify->enT3412State));
    }

    if ((VOS_TRUE == pstTimerInfoNotify->bitOpT3423)
     && (LMM_MMC_TIMER_BUTT != pstTimerInfoNotify->enT3423State))
    {
        NAS_MML_SetT3423Status((VOS_UINT8)(pstTimerInfoNotify->enT3423State));
    }

    if ((VOS_TRUE == pstTimerInfoNotify->bitOpT3402)
     && (LMM_MMC_TIMER_BUTT != pstTimerInfoNotify->enT3402State))
    {
        NAS_MML_SetT3402Status((VOS_UINT8)(pstTimerInfoNotify->enT3402State));

        return VOS_TRUE;
    }

    /* ��MM��GMMת����ʱ��״̬��Ϣ */
    NAS_MMC_SndGmmLmmTimerStateNotify(pstTimerInfoNotify);
    NAS_MMC_SndMmLmmTimerStateNotify(pstTimerInfoNotify);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcNotCampOnInd_PreProc
 ��������  : �յ�LMM��NOT_CAMP_ON_IND��Ϣ�Ĵ���
 �������  : ulEventType - ID_LMM_MMC_NOT_CAMP_ON_IND��ϢID
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcNotCampOnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmCellSignReportInd_PreProc
 ��������  : �յ�LMM��CELL SIGNAL REPORT IND����Ϣ
 �������  : ulEventType:ID_LMM_MMC_CELL_SIGN_REPORT_IND��ϢID
             pstMsg: ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : w00281933
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmCellSignReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                      *pstMsg
)
{
    LMM_MMC_CELL_SIGN_REPORT_IND_STRU  *pStSignReportIndMsg = VOS_NULL_PTR;
    MSCC_MMC_LMM_CELL_SIGN_INFO_STRU     stLteCellSignInfo;
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));
    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    PS_MEM_SET(((VOS_UINT8*)&stLteCellSignInfo), 0, sizeof(MSCC_MMC_LMM_CELL_SIGN_INFO_STRU));

    /*��ȡLTE ��Ϣ���ź��ϱ�����*/
    pStSignReportIndMsg                 = (LMM_MMC_CELL_SIGN_REPORT_IND_STRU*)pstMsg;

    stLteCellSignInfo.sRsrp             = ((NAS_MMC_RSRP_UNVALID == pStSignReportIndMsg->sRsrp)?NAS_MMC_RSRP_UNVALID:pStSignReportIndMsg->sRsrp/NAS_MMC_SIGNAL_DIVISOR);
    stLteCellSignInfo.sRsrq             = ((NAS_MMC_RSRQ_UNVALID == pStSignReportIndMsg->sRsrq)?NAS_MMC_RSRQ_UNVALID:pStSignReportIndMsg->sRsrq/NAS_MMC_SIGNAL_DIVISOR);
    stLteCellSignInfo.sRssi             = ((NAS_MMC_RSSI_INVALID == pStSignReportIndMsg->sRssi)?NAS_MMC_RSSI_INVALID:pStSignReportIndMsg->sRssi/NAS_MMC_SIGNAL_DIVISOR);
    stLteCellSignInfo.sRsd              =  pStSignReportIndMsg->sRsd;

    stLteCellSignInfo.lSINR             = pStSignReportIndMsg->lSinr;
    stLteCellSignInfo.stCQI.usRI        = pStSignReportIndMsg->stCQI.usRI;
    stLteCellSignInfo.stCQI.ausCQI[0]   = pStSignReportIndMsg->stCQI.ausCQI[0];
    stLteCellSignInfo.stCQI.ausCQI[1]   = pStSignReportIndMsg->stCQI.ausCQI[1];


    /*�ϱ��ź�ǿ�ȸ�MMA����LMM CELL SIGN INFO REPORT IND ��Ϣ*/
    NAS_MMC_SndMsccMsgLmmCellSignInfoInd(&unMeasReportType, &stLteCellSignInfo);

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvOmMsg_PreProc
 ��������  : MMC��������OM����Ϣ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��22��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : ɾ���ϴ���
 3.��    ��   : 2015��07��23��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvOmOtaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    OM_NAS_OTA_REQ_STRUCT              *pstOtaReq;
    VOS_UINT32                          ulErrCode;

    pstOtaReq   = ( OM_NAS_OTA_REQ_STRUCT* )pstMsg;

    /*����NAS OTA��Ϣ�Ŀ���*/
    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvOmOtaReq_PreProc: NORMAL: Specified NAS OTA switch is , Old switch is ",
                 (long)pstOtaReq->ulOnOff, NAS_GetNasOtaSwitch());

    /* �жϿտ���Ϣ�����Ƿ���Ч */
    if ( (NAS_OTA_SWITCH_ON != pstOtaReq->ulOnOff )
      && (NAS_OTA_SWITCH_OFF != pstOtaReq->ulOnOff))
    {
        /* �տ���Ϣ���ô��� */
        ulErrCode = NAS_OTA_CNF_ERRCODE_YES;
        /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
        NAS_MMC_SndOmOtaCnf(ulErrCode, pstOtaReq);
        /* Modified by wx270776 for OM�ں�, 2015-7-23, end */
        return VOS_TRUE;
    }

    NAS_SetNasOtaSwitch(pstOtaReq->ulOnOff);
    ulErrCode = NAS_OTA_CNF_ERRCODE_NO;

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvOmMsg_PreProc: NORMAL: Specified NAS OTA switch is , Old switch is ",
                 (long)pstOtaReq->ulOnOff, NAS_GetNasOtaSwitch());

    /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
    NAS_MMC_SndOmOtaCnf(ulErrCode, pstOtaReq);
    /* Modified by wx270776 for OM�ں�, 2015-7-23, end */

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvOmInquireReq_PreProc
 ��������  : ��������OM�Ĳ�ѯ��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   :
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvOmInquireReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    ID_NAS_OM_INQUIRE_STRU             *pstOmMsg = VOS_NULL_PTR;

    pstOmMsg = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvOmInquireReq_PreProc:  ");

    NAS_MMC_SndOmInquireCnfMsg(pstOmMsg);

    return VOS_TRUE;

}


/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndOmConfigTimerReportCnfMsg
 ��������  : �ظ����Թ��ߵ�������ϢID_NAS_OM_CONFIG_TIMER_REPORT_REQ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��28��
   ��    ��   : luokaihui 00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��7��1��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
*****************************************************************************/
/* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
VOS_VOID NAS_MMC_SndOmConfigTimerReportCnfMsg(
    NAS_OM_CONFIG_TIMER_REPORT_REQ_STRU    *pstTimerReportCfgReq
)
{
    NAS_OM_CONFIG_TIMER_REPORT_CNF_STRU    *pstNasSndOmTimerReportCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;
    VOS_UINT32                              ulRet;

    /* ������Ϣ */
    ulMsgLen     = sizeof(NAS_OM_CONFIG_TIMER_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNasSndOmTimerReportCnf = (NAS_OM_CONFIG_TIMER_REPORT_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstNasSndOmTimerReportCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmConfigTimerReportCnf: Message Alloc Failed!");

        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstNasSndOmTimerReportCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    /* ��д��Ϣ���� */
    pstNasSndOmTimerReportCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstNasSndOmTimerReportCnf->ulMsgId          = ID_NAS_OM_CONFIG_TIMER_REPORT_CNF;
    pstNasSndOmTimerReportCnf->usOriginalId     = pstTimerReportCfgReq->usOriginalId;
    pstNasSndOmTimerReportCnf->usTerminalId     = pstTimerReportCfgReq->usTerminalId;
    pstNasSndOmTimerReportCnf->ulTimeStamp      = pstTimerReportCfgReq->ulTimeStamp;
    pstNasSndOmTimerReportCnf->ulSN             = pstTimerReportCfgReq->ulSN;

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstNasSndOmTimerReportCnf);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmConfigTimerReportCnf: WARNING: Send msg fail.");
    }

    return;
}
/* Modified by wx270776 for OM�ں�, 2015-7-23, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvOmInquireReq_PreProc
 ��������  : ��������OM�Ĳ�ѯ��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��28��
   ��    ��   : luokaihui 00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��07��23��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvOmConfigTimerReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
    NAS_OM_CONFIG_TIMER_REPORT_REQ_STRU *pstTimerReportCfgReq = VOS_NULL_PTR;
    NAS_TIMER_EVENT_INFO_STRU           *pstTimerEventCfg     = VOS_NULL_PTR;
    VOS_UINT32                           ulTimerEventNum;

    pstTimerEventCfg     = NAS_GetTimerEventReportCfg();

    pstTimerReportCfgReq = (NAS_OM_CONFIG_TIMER_REPORT_REQ_STRU*)pstMsg;
    /* Modified by wx270776 for OM�ں�, 2015-7-23, end */

    if ( NAS_MMC_REPORT_TIMER_OTA_EVENT_START == pstTimerReportCfgReq->ulCommand )
    {
        ulTimerEventNum = pstTimerReportCfgReq->stTimerMsg.ulItems;

        if(pstTimerReportCfgReq->stTimerMsg.ulItems > NAS_MAX_TIMER_EVENT)
        {
            ulTimerEventNum = NAS_MAX_TIMER_EVENT;
        }
        else
        {
            pstTimerEventCfg->ulItems = ulTimerEventNum;
        }

        PS_MEM_CPY(pstTimerEventCfg->aulTimerMsg, pstTimerReportCfgReq->stTimerMsg.aulTimerMsg, ulTimerEventNum*sizeof(VOS_UINT32));
    }
    else
    {
        pstTimerEventCfg->ulItems = 0;
    }

    /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
    NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_RcvOmConfigTimerReportReq_PreProc: Updated Timer Events.",
                  pstTimerEventCfg->ulItems);

    /* �ظ�����cnf��Ϣ */
    NAS_MMC_SndOmConfigTimerReportCnfMsg(pstTimerReportCfgReq);
    /* Modified by wx270776 for OM�ں�, 2015-7-23, end */

    return VOS_TRUE;

}
/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedUpdateHighPrioPlmnSearchList
 ��������  : �ж�band�ı��Ƿ���Ҫ���¸����ȼ������б�
 �������  : pstSysCfgSetBand:��ǰ�û�syscfg���õ�Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��6��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID NAS_MMC_IsNeedUpdateHighPrioPlmnSearchList(
    MSCC_MMC_UE_SUPPORT_FREQ_BAND_STRU   *pstSysCfgSetBand
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU                              *pstMsBandInfo        = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstMsBandInfo        = NAS_MML_GetMsSupportBand();
    pstPlmnSelectionList = NAS_MMC_GetHighPrioPlmnList();

    /* ���G��Ƶ�η����ı䣬��Ҫ���¸����ȼ������б������н��뼼��ΪG������״̬Ϊδ���� */
    if (pstMsBandInfo->unGsmBand.ulBand != pstSysCfgSetBand->unGsmBand.ulBand)
    {
        for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
        {
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                    NAS_MMC_NET_STATUS_NO_SEARCHED,
                                                    &pstPlmnSelectionList->astPlmnSelectionList[i]);
        }
    }

    /* ���W��Ƶ�η����ı䣬��Ҫ���¸����ȼ������б������н��뼼��ΪW������״̬Ϊδ���� */
    if (pstMsBandInfo->unWcdmaBand.ulBand != pstSysCfgSetBand->unWcdmaBand.ulBand)
    {
        for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
        {
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                   NAS_MMC_NET_STATUS_NO_SEARCHED,
                                                   &pstPlmnSelectionList->astPlmnSelectionList[i]);
        }
    }

#if (FEATURE_ON == FEATURE_LTE)

/* ���L��Ƶ�η����ı䣬��Ҫ���¸����ȼ������б������н��뼼��ΪL������״̬Ϊδ���� */
    if ((pstMsBandInfo->stLteBand.aulLteBand[0] != pstSysCfgSetBand->stLteBand.aulLteBand[0])
     || (pstMsBandInfo->stLteBand.aulLteBand[1] != pstSysCfgSetBand->stLteBand.aulLteBand[1]))
    {
        for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
        {
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(NAS_MML_NET_RAT_TYPE_LTE,
                                                   NAS_MMC_NET_STATUS_NO_SEARCHED,
                                                   &pstPlmnSelectionList->astPlmnSelectionList[i]);
        }
    }
#endif

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PreProc
 ��������  : ��MSCC����������SYSCFG��Ϣ����Ԥ����,�ж��Ƿ��ܽ���SYSCFG�ж�
             �Ƿ���Ҫ֪ͨ��ǰ״̬���˳�,
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��
 3.��    ��   : 2012��9��4��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 4.��    ��   : 2012��11��7��
   ��    ��   : s00217060
   �޸�����   : DTS2012060507813 ����������CSҵ��ʱ��SYSCFG����ʧ�ܣ�AT��ԭ��ֵ��
                 GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ����������ͷź󣬿��·�SYSCFG
 5.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 6.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��

 7.��    ��   : 2014��6��25��
   ��    ��   : w00167002
   �޸�����   : DSDS III:��NO RF����������û�����SYSCFG���ã���MSCC���ٱ���ԭ��״̬��
 8.��    ��   : 2014��7��16��
   ��    ��   : z00161729
   �޸�����   : DTS2014071601162:syscfg����mmc���������ϱ�mma rf����

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafSysCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSyscfgNeedPlmnSrchRslt;
    VOS_UINT32                          ulCsServiceExist;

    /* Modified by z00161729 for DCM�����������������, 2012-9-4, begin */
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrFsmId;
    /* Modified by z00161729 for DCM�����������������, 2012-9-4, end */

    pstSysCfgSetParm         = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)pstMsg;

    /* �жϵ�ǰSYSCFG�����Ƿ���Ҫ�������� */
    ulSyscfgNeedPlmnSrchRslt = NAS_MMC_IsPlmnSelectionNeeded_SysCfg(pstSysCfgSetParm);

    /* �жϵ�ǰ�Ƿ���CSҵ����� */
    ulCsServiceExist         = NAS_MML_GetCsServiceExistFlg();

    /* ���SYSCFG������Ҫ�����ҵ�ǰ��ҵ����ڻ����л����ҵ�����
       ��ô������SYSCFG���ã���MSCC����SYSCFG ����ʧ��*/


    /* GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ����������ͷź󣬿��·�SYSCFG����L�Ĵ�����ͬ
       ����CSҵ��ʱ��MMC��MSCC�ϱ�SYSCFG���Ϊ��CSҵ����� */
    if (VOS_TRUE == ulSyscfgNeedPlmnSrchRslt)
    {
        if (VOS_TRUE == ulCsServiceExist)
        {
            NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST);
            return VOS_TRUE;
        }
        else
        {

        }
    }

    /* Modified by z00161729 for DCM�����������������, 2012-9-4, begin */
    enCurrFsmId = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enCurrFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* ���ڻ���Ľ��������ҵ�ǰ�������ڽ������д�����anycell״̬����syscfg������������ҲҪ�ȴ���������У�syscfg����ʧ��  */
    if ((VOS_TRUE == NAS_MML_IsExistBufferedEmgCall())
     && (NAS_MMC_FSM_ANYCELL_SEARCH == enCurrFsmId))
    {
        NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);
        return VOS_TRUE;
    }
    /* Modified by z00161729 for DCM�����������������, 2012-9-4, end */

    /* ���Ƶ�η����ı䣬��Ҫ���¸����ȼ������б�������״̬ */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
    NAS_MMC_IsNeedUpdateHighPrioPlmnSearchList((MSCC_MMC_UE_SUPPORT_FREQ_BAND_STRU *)&pstSysCfgSetParm->stBand);
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */

    /* �жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬�� �������Ϣ�Ļ��� */
    ulRet = NAS_MMC_ProcMsgPrio(ulEventType, pstMsg);

    /* ��Ҫ��ϵ�ǰ״̬���������Ϣ�Ļ���,���ʾԤ������� */
    if ( VOS_TRUE == ulRet )
    {
        return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;
}

/* Added by s00261364 for L-C��������Ŀ, 2014-3-13, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafAcqReq_PreProc
 ��������  : ��MSCC����������acq req��Ϣ����Ԥ����
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��13��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰ״̬����ʶ */
      NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

      MSCC_MMC_PLMN_ID_STRU                stPlmnId;

      enFsmId = NAS_MMC_GetCurrFsmId();

      /* ����ϵͳ��ON Plmn״̬�������������ȼ�������ʱ�� */
    if ( (NAS_MMC_FSM_INTER_SYS_CELLRESEL == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_OOS       == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_HO        == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_CCO       == enFsmId))
    {

       stPlmnId.ulMcc     = NAS_MML_INVALID_MCC;
       stPlmnId.ulMnc     = NAS_MML_INVALID_MNC;
       NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_FAILURE, &stPlmnId, 0);

       return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafRegReq_PreProc
 ��������  : ��MSCC����������reg req��Ϣ����Ԥ����
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��13��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafRegReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰ״̬����ʶ */
      NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

      MSCC_MMC_PLMN_ID_STRU                stPlmnId;

      enFsmId = NAS_MMC_GetCurrFsmId();

      /* ����ϵͳ��ON Plmn״̬�������������ȼ�������ʱ�� */
    if ( (NAS_MMC_FSM_INTER_SYS_CELLRESEL == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_OOS       == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_HO        == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_CCO       == enFsmId))
    {

       stPlmnId.ulMcc     = NAS_MML_INVALID_MCC;
       stPlmnId.ulMnc     = NAS_MML_INVALID_MNC;
       NAS_MMC_SndMsccRegCnf(MMC_LMM_CL_REG_STATUS_BUTT, NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE, &stPlmnId, 0x0);

       return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;
}
/* Added by s00261364 for L-C��������Ŀ, 2014-3-13, end */




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccUserSpecPlmnSearch_PreProc
 ��������  : �û�ָ������Ϣ��Ԥ����
 �������  : ulEventType: ��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��01��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��12��20��
   ��    ��   : w00167002
   �޸�����   : DTS2011122001697:��ON PLMN״̬����ǰָ���ѵ�������ǰפ��������
                 ��ͬ����ǰ������������״̬�Ҳ������������У��Ų������û�ָ������
                �����ڸ����ȼ�ָ������ʱ���߿���ָ����ʱ�����û�ָ���Ѵ�ϣ�
                ���û�ָ�����������ǰפ����������ͬ�������ȼ�����״̬���˳���
                �᲻�����û�ָ���ѡ�
 3.��    ��   : 2012��6��6��
   ��    ��   : l00130025
   �޸�����   : DTS2012060604313:������ע��ɹ����û�����Ը������ָ������ʱ��Ҫ��������ע��

 4.��    ��   : 2012��10��9��
   ��    ��   : z40661
   �޸�����   : DTS2012091102394

 5.��    ��   : 2012��11��24��
   ��    ��   : s00217060
   �޸�����   : DTS2012082007133:�����ѡ״̬�����յ��û�ָ���ѣ��û�ָ��������͵�ǰפ����������ͬ��
       ���ҵ�ǰפ�����������ṩ���������򲻴����ѡ״̬����ֱ�ӻظ������ɹ�
 6.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 7.��    ��   : 2013��3��14��
   ��    ��   : W00176964
   �޸�����   : DTS2013031400138, ��Ʒ��������:PSҵ�����ʱ����ָ������
 8.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 9.��    ��   : 2013��11��1��
   ��    ��   : z00161729
   �޸�����  : DTS2013111103301:svlte��Ҫ�ػ�״̬֧��cops���ã�����nv������ģʽ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccUserSpecPlmnSearch_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserSelReqMsg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstUserSpecPlmnId = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulCsServiceStatusFlg;
    VOS_UINT32                          ulRslt;

    NAS_MML_PLMN_WITH_RAT_STRU          stUserSpecPlmnInfo;

    VOS_UINT32                          ulSpecPlmnSearchFlg;

    pstUserSelReqMsg  = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    /* ָ���û�ָ��������Ϣ�е�PlmnId */
    pstUserSpecPlmnId = (NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId);

    /* ������� */
    if ( VOS_FALSE == NAS_MMC_CheckUserSpecPlmnSearchParamMsg_PreProc(pstMsg) )
    {
        /* ��MSCC�����û�ָ�������ܾ�������������ģʽ */
        NAS_MMC_SndMsccUserSpecPlmnSearchRej();
        return VOS_TRUE;
    }

    /* �ػ�״̬���svlte nv����������cops����дnv������û�ָ��plmn��Ϣ,��mma�ظ��ɹ� */
    enFsmId = NAS_MMC_GetCurrFsmId();
    if ((NAS_MMC_L1_STA_NULL == NAS_MMC_GetFsmTopState())
     && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
        NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);

        /* ����ǰ��ѡģʽд��NVIM�� */
        NAS_MMC_WritePlmnSelectionModeNvim();

        stUserSpecPlmnInfo.stPlmnId.ulMcc = pstUserSpecPlmnId->ulMcc;
        stUserSpecPlmnInfo.stPlmnId.ulMnc = pstUserSpecPlmnId->ulMnc;
        stUserSpecPlmnInfo.enRat          = pstUserSelReqMsg->enAccessMode;

        NAS_MMC_SetUserSpecPlmnId(&stUserSpecPlmnInfo);

        /* ��MSCC�����û�ָ�������ɹ� */
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);

        return VOS_TRUE;
    }

    /* ������λ����Ч�Ĵ��� */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid() )
    {
        /* �����ֶ��������� */
        NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc(pstUserSpecPlmnId,
                                                           pstUserSelReqMsg->enAccessMode);

        /* ��MSCC�����û�ָ������ʧ�� */
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
         return VOS_TRUE;
    }

    enFsmId = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* �ػ�����·�����Чֵ */
    /* �����ѡ״̬�����յ��û�ָ���ѣ��û�ָ��������͵�ǰפ����������ͬ��
       ���ҵ�ǰפ�����������ṩ���������򲻴����ѡ״̬����ֱ�ӻظ������ɹ� */
    if ( ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
       && (NAS_MMC_FSM_L1_MAIN == enFsmId))
      || (NAS_MMC_FSM_INTER_SYS_CELLRESEL == enFsmId) )
    {
        /* �ж��û�ָ��������͵�ǰפ���������Ƿ���ͬ */
        ulRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                                    pstUserSpecPlmnId);
        enCurrRatType = NAS_MML_GetCurrNetRatType();
        if ( (VOS_TRUE == ulRslt)
          && (pstUserSelReqMsg->enAccessMode == enCurrRatType) )
        {

            /* ��ǰ������������״̬��δ���й������������ڸ����ȼ�ָ������ʱ
               ���߿���ָ����ʱ�����û�ָ���Ѵ�ϣ����û�ָ�����������ǰפ����
               ������ͬ�������ȼ�����״̬���˳��󣬻᲻�����û�ָ���� */
            ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

            if ( (VOS_FALSE == NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn())
              && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg) )
            {

                /* �����ֶ��������� */
                NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc(pstUserSpecPlmnId,
                                                                   pstUserSelReqMsg->enAccessMode);

                /* ���õ�ǰע��״̬Ϊ�ɹ� */
                NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

                /* ��MSCC�����û�ָ�������ɹ� */
                NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
                return VOS_TRUE;
            }
        }
    }

    ulCsServiceStatusFlg = NAS_MML_GetCsServiceExistFlg();

    if (VOS_TRUE == ulCsServiceStatusFlg)
    {
        /* ��MSCC�����û�ָ������ʧ�� */
        /* ��MSCC�����û�ָ�������ܾ�������������ģʽ */
        NAS_MMC_SndMsccUserSpecPlmnSearchRej();
        return VOS_TRUE;
    }

    /* �жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬�� */
    ulRslt = NAS_MMC_ProcMsgPrio(ulEventType, pstMsg);

    if (VOS_TRUE == ulRslt)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvUserReselReq_PreProc
 ��������  : �û������Զ���ѡ��Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��9��24��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase II �����ȼ���������

 3.��    ��   : 2011��10��21��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II-2 ��ҵ�����ʱ����AT+COPS=0������ģʽδ����Ϊ�Զ�ģʽ

 4.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 5.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : DTS2011111603447:���л���������Ĵ���,ɾ��Ԥ�������汣��
                �������������.

 6.��    ��   : 2011��11��23��
   ��    ��   : w00167002
   �޸�����   : DTS2011112303107:�ֶ�תΪ�Զ�ģʽ��������HPLMN TIMER������Ϊ
                 �´�����Ϊ�ǵ�һ������

 7.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton����֧��
 8.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvUserReselReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU                      *pUserReselReq       = VOS_NULL_PTR;

    pUserReselReq  = (MSCC_MMC_PLMN_USER_RESEL_REQ_STRU*)pstMsg;

    /* �û������ֶ���ѡ��Ŀǰ��֧�� */
    if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO != pUserReselReq->enPlmnSelMode)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvUserReselReq_PreProc:Entered!");
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_REJ);

        return VOS_TRUE;
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_AUTO_SEL);

    /* CLģʽ��ֱ�Ӹ���ȫ�ֱ�����NV����������� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        /* ����ѡ��ģʽ */
        NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_AUTO);

        /* ����ǰ��ѡģʽд��NVIM�� */
        NAS_MMC_WritePlmnSelectionModeNvim();

        /* ����Ҫ�ظ��������MSCCֱ�ӻظ��ɹ� */

        return VOS_TRUE;
    }
#endif

    /* ��ǰ������������״̬ */
    if (VOS_TRUE != NAS_MMC_IsNormalServiceStatus())
    {
        return NAS_MMC_ProcUserReselReqUnNormalSrv_PreProc(pUserReselReq);
    }
    else
    {
        return NAS_MMC_ProcUserReselReqNormalService_PreProc(pUserReselReq);
    }

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiAvailTimerExpired_PreProc
 ��������  : available timer��ʱ����ʱ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : DTS2011111603447:���л���������Ĵ���
 3.��    ��   : 2011��11��26��
   ��    ��   : w00167002
   �޸�����   : DTS2011112507242:����פ������£��û�ָ��������ע�ᱻ��
                ���µ�ǰ����ΪFORBPLMN(��#11),AVAILABLE TIMER��ʱ�󷴸�
                ����ANYCELL������
 4.��    ��   : 2012��04��25��
   ��    ��   : w00166186
   �޸�����   : DTS2012041907605:LTE ONLY פ������£��û�ָ��������ע�ᱻ��
                ���µ�ǰ����ΪGPRS FORBPLMN,AVAILABLE TIMER��ʱ�󷴸�
                ����ANYCELL������
 5.��    ��   : 2012��9��24��
   ��    ��   : s46746
   �޸�����   : ���ⵥ��DTS2012092003660���޷���ʱ���Ͷ��ţ����º������ٷ�������

 6.��    ��   : 2014��4��21��
   ��    ��   : w00167002
   �޸�����   : DSDS II:NO RFʱ����Ԥ����ֹͣAVAILABLE��ʱ����������������������
                ��ʱ���������ڿ�ά�ɲ⡣
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiAvailTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRrcConnExistFlag;

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet;
#endif

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulForbPlmnFlag;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;            /* ��ǰ״̬����ʶ */
    VOS_UINT32                                              ulState;            /* ��ǰ״̬��״̬ */

    enSelectionMode   = NAS_MMC_GetPlmnSelectionMode();

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
    ulForbPlmnFlag    = NAS_MML_IsPlmnIdInForbidPlmnList( &(pstUserSpecPlmnId->stPlmnId) );

    /* ��ȡ��ǰ״̬��ID����״̬ */
    enFsmId           = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulState           = NAS_MMC_GetFsmTopState();


    if (VOS_TRUE == NAS_MMC_IsNeedRestartAvailableTimer())
    {
        /* ������ʱ���������������ǲ��ı䶨ʱ�������� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());

        return VOS_TRUE;
    }

    /* ��ǰΪ�ֶ�ģʽ���û�ָ���������ڽ�ֹ�����б��У��ҵ�ǰ��ΪOOC״̬��
       ��˴�����û�����壬�ʲ�����AvailTimer��ʱ��Ϣ */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
      && (VOS_TRUE                           == ulForbPlmnFlag)
      && (NAS_MMC_FSM_L1_MAIN                == enFsmId)
      && (NAS_MMC_L1_STA_OOC                 != ulState) )
    {
        return VOS_TRUE;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* LTE ONLY ��ǰΪ�ֶ�ģʽ���û�ָ���������ڽ�ֹGPRS�б��У��ҵ�ǰ��ΪOOC״̬��
       ��˴�����û�����壬�ʲ�����AvailTimer��ʱ��Ϣ */
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                  pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                                  pstForbidPlmnInfo->astForbGprsPlmnList);

    if ((VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
     && (VOS_TRUE == ulRet )
     && (NAS_MMC_FSM_L1_MAIN == enFsmId)
     && (NAS_MMC_L1_STA_OOC != ulState))
    {
        return VOS_TRUE;
    }
#endif

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag          = NAS_MML_IsRrcConnExist();

    /* ������ʱ������CTX�еı�����¼��Ҫ����*/
    if (VOS_TRUE == ulRrcConnExistFlag)
    {
        NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED);

        return VOS_TRUE;
    }

    /* ��״̬���ﴥ������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddPhaseNumRcvPhaseTotalTimerExpired_PreProc
 ��������  : Phase X Total Timer Expired ֮���Ƿ���Ҫ�ۼ�ָʾ��ǰ���ĸ��׶�
             ��ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��17��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddPhaseNumRcvPhaseTotalTimerExpired_PreProc(VOS_VOID)
{
    NAS_MMC_OOS_PHASE_ENUM_UINT8        enCurrOosPhaseNum;
    NAS_MMC_OOS_PHASE_ENUM_UINT8        enNextOosPhaseNum;

    enCurrOosPhaseNum = NAS_MMC_GetCurrOosSearchPhaseNum();
    enNextOosPhaseNum = NAS_MMC_GetOosPhaseNum();

    /* ��ǰ���������׶�֮����ٽ�㣬Available Timer��ʱ֮���Ѿ��ۼӹ������Դ˴�����Ҫ���ۼ� */
    if (enCurrOosPhaseNum != enNextOosPhaseNum)
    {
        return VOS_FALSE;
    }

    /* ��ǰ�Ѵ������һ���׶Σ�����Ҫ���ۼ� */
    if (NAS_MMC_OOS_PHASE_MAX == enNextOosPhaseNum)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedRestartAvailableTimer
 ��������  : available��ʱ����ʱʱ���Ƿ���Ҫ��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��31��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedRestartAvailableTimer( VOS_VOID )
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;

    enCurrNetRat = NAS_MML_GetCurrNetRatType();

    /* ����������ʱ����ʱʱ�������ǰ����NO RF�����Ϣ��������������������ʱ�� */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedRestartAvailableTimer: RfAvailFlg = VOS_FALSE");

        return VOS_TRUE;
    }

    /* GSM��tbf���Ӳ�׼��GMM����ע������У�������������������ʱ�� */
    if ((VOS_TRUE == NAS_GMM_IsInRegisterProcedure())
     && (NAS_MML_NET_RAT_TYPE_GSM   == enCurrNetRat))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedRestartAvailableTimer: GMM is In Register Procedure");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPlmnSearchPhaseOneTotalTimerExpired_PreProc
 ��������  : TI_NAS_MMC_CONTROL_FIRST_PLMN_SEARCH_TIMER��ʱ����ʱ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��26��
   ��    ��   : c00318887
   �޸�����   : �½�
 2.��    ��   : 2015��10��08��
   ��    ��   : zwx247453
   �޸�����   : ���Coverity�澯

 3.��    ��   : 2015��10��31��
   ��    ��   : w00167002
   �޸�����   : DTS2015103009549:��ANYCELL����״̬�����棬�յ���ʱ��Ϣ�ұ����档
               ANYCELL״̬���˳�ʱ�򣬻�������phaseONE�ܿض�ʱ���������ڳ�ʱ��Ϣ��
               ��ֹͣ�´˶�ʱ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPlmnSearchPhaseOneTotalTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                    ulNormalCount;

    ulNormalCount                               = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiControlFirstPlmnSearchTimerExpired_PreProc entered.");

    /* ������״̬���³�ʱ������ֱ��L1 MAIN �ٴ��� */
    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);

        /* ����Ѿ��������ڶ��׶Σ��򷵻� */
        if (NAS_MMC_OOS_PHASE_ONE != NAS_MMC_GetOosPhaseNum())
        {
            NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvTiControlFirstPlmnSearchTimerExpired_PreProc WANRING: ue is in plmn search phaseII",
                                ulNormalCount, NAS_MMC_GetOosPhaseNum());

        }

        /* ���������ڶ��׶�,�������ж�ʱ������ */
        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());
        NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();
        NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn();
        NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn();
        NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main();

        if (VOS_TRUE == NAS_MMC_IsNeedAddPhaseNumRcvPhaseTotalTimerExpired_PreProc())
        {
            NAS_MMC_AddOosPhaseNum();
        }

        /* �����ǰavailable���������У���������ʱ���ȴ��䳬ʱ������������ */
        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
        }

        /* ��ѡ��״̬����Ϻ��򴥷�AVAILABLE��ʱ����ʱ����������ѡ������ */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, 500);

        return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;

}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasCellId_PreProc
 ��������  : �յ�WAS���͵�С��ID�����Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : ���ӱ���ϵͳ��ģʽ
 3.��    ��   : 2012��3��12��
   ��    ��   : l00130025
   �޸�����   : DTS2012021305344,ͬ�����ⵥDTS2010072900978��AT_MSG_IND��Ϣ���ٸ���CELL ID��Ϣ��ͳһ��
                 �յ�SYS INFO����£�����С�����������ı���ϱ�Ӧ��
 4.��    ��   : 2012��4��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012033006643,��פ��״̬���ź�ǿ�Ȳ��ܼ�ʱ����,פ��̬ʱ����Ҫ�ϱ�Cell_ID�����⵼��MSCCģʽ���´���
 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID NAS_MMC_RcvWasCellId_PreProc(
    RRC_NAS_CELL_ID_ST                  *pstWasCellId
)
{
    NAS_MML_CAMP_CELL_INFO_STRU         *pstCampCellInfo     = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCurrCampPlmnInfo = VOS_NULL_PTR;


    /* ������פ��̬�򲻴�����Ϣ�ϱ� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn() )
    {
        return;
    }


    /*�ϱ�С����������8����Ϊ���� */
    if (pstWasCellId->ucIDNum > RRC_NAS_AT_CELL_MAX_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC ,"NAS_MMC_RcvWasAtMsgCnf():WARNING:the NUM is out limit.");
        return;
    }


    pstCampCellInfo     = NAS_MML_GetCampCellInfo();
    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* ��С�����ı䣬�����������ı�ʱ�����ϱ�*/
    if ( (pstCampCellInfo->astCellInfo[0].ulCellId == pstWasCellId->aulCellId[0])
       &&(pstCurrCampPlmnInfo->enSysSubMode != pstWasCellId->enSysSubMode))
    {
        /* ����WRR�ϱ��ĵ�ǰС������̬�µ�ϵͳ��ģʽ */
        pstCurrCampPlmnInfo->enSysSubMode = pstWasCellId->enSysSubMode;

        /*����С����Ϣ�ϱ��������ϱ�tafС����Ϣ*/
        NAS_MMC_SndMsccSysInfo();
    }


}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasCellBler_PreProc
 ��������  : �յ�WAS���͵�С�������������Ϣ�ϱ�
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : ���ܾ�ȷ�ϣ��Ǹ�RssiNum��ֵ
 3.��    ��   : 2014��6��4��
   ��    ��   : b00269685
   �޸�����   : NAS_MMC_SndMsccRssiInd�޸�
*****************************************************************************/

VOS_VOID NAS_MMC_RcvWasCellBler_PreProc(
    RRC_NAS_CELL_TRCH_BLER_STRU_LIST    *pstWasCellBler
)
{
    VOS_UINT32                           i;
    NAS_MML_CAMP_CELL_INFO_STRU         *pstCampCellInfo;
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN    unMeasReportType;

    pstCampCellInfo  = NAS_MML_GetCampCellInfo();

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));
    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXQUALITY;

    /*�����ʳ���8����Ϊ��Ϣ��Ч */
    if ( pstWasCellBler->ucTrchNum > RRC_NAS_AT_CELL_MAX_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvWasAtMsgCnf():WARNING:the BLER NUM is out limit.");
        return;
    }


    /*�����ϱ���������Ϣ*/
    pstCampCellInfo->ucRssiNum = pstWasCellBler->ucTrchNum;

    for ( i = 0; i < pstWasCellBler->ucTrchNum ; i++ )
    {
        if ( pstWasCellBler->stTrchBlerInfo[i].ucDlTrChBler > NAS_MML_UTRA_BLER_INVALID)
        {
            pstCampCellInfo->astRssiInfo[i].ucChannalQual = NAS_MML_UTRA_BLER_INVALID;
        }
        else
        {
            pstCampCellInfo->astRssiInfo[i].ucChannalQual = pstWasCellBler->stTrchBlerInfo[i].ucDlTrChBler;
        }
    }

    /*�����ϱ��ź�ǿ��*/
    NAS_MMC_SndMsccRssiInd(&unMeasReportType);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasCellRssi_PreProc
 ��������  : �յ�WAS���͵�С���ź����������Ϣ�ϱ�
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��25��
   ��    ��   : s46746
   �޸�����   : DTS2011120501503,��ѯע��״̬ʱ��λ������Ϣ����
 3.��    ��   : 2012��11��21��
   ��    ��   : z00161729
   �޸�����   : ֧��cerssi��nmr
 4.��    ��   : 2014��6��4��
   ��    ��   : b00269685
   �޸�����   : NAS_MMC_SndMsccRssiInd�޸�

*****************************************************************************/

VOS_VOID NAS_MMC_RcvWasCellRssi_PreProc(
    RRC_NAS_CELL_RSCP_STRU_LIST         *pstWasCellRscp
)
{
    VOS_UINT32                           i;
    NAS_MML_CAMP_CELL_INFO_STRU         *pstCampCellInfo;
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN    unMeasReportType;

    pstCampCellInfo  = NAS_MML_GetCampCellInfo();

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));
    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    if ( pstWasCellRscp->usCellNum > RRC_NAS_AT_CELL_MAX_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC ,"NAS_MMC_RcvWasCellRssi_PreProc():WARNING:RSCP NUM is out limit.");
        return;
    }

    pstCampCellInfo->ucRssiNum  = (VOS_UINT8)pstWasCellRscp->usCellNum;

    for ( i = 0; i < pstWasCellRscp->usCellNum ; i++ )
    {
        if ( (pstWasCellRscp->stCellRscp[i].sCellRSCP > NAS_MML_RSCP_UPPER_LIMIT)
          || (pstWasCellRscp->stCellRscp[i].sCellRSCP < NAS_MML_RSCP_LOWER_LIMIT))
        {
            pstCampCellInfo->astRssiInfo[i].sRscpValue = NAS_MML_UTRA_RSCP_UNVALID;
        }
        else
        {
            pstCampCellInfo->astRssiInfo[i].sRscpValue = pstWasCellRscp->stCellRscp[i].sCellRSCP;
        }

        if ((pstWasCellRscp->stCellRscp[i].sRSSI > NAS_MML_RSSI_UPPER_LIMIT)
         || (pstWasCellRscp->stCellRscp[i].sRSSI < NAS_MML_RSSI_LOWER_LIMIT))
        {
            pstCampCellInfo->astRssiInfo[i].sRssiValue = NAS_MML_RSSI_UNVALID;
        }
        else
        {
            pstCampCellInfo->astRssiInfo[i].sRssiValue  = pstWasCellRscp->stCellRscp[i].sRSSI;
        }
    }

    pstCampCellInfo->usCellDlFreq   = pstWasCellRscp->usCellDlFreq;
    pstCampCellInfo->usCellUlFreq   = pstWasCellRscp->usCellUlFreq;
    pstCampCellInfo->sUeRfPower     = pstWasCellRscp->sUeRfPower;

    for ( i = 0; i < pstWasCellRscp->usCellNum ; i++ )
    {
        if ((pstWasCellRscp->stCellRscp[i].sCellRSCP > NAS_MML_RSCP_UPPER_LIMIT)
            ||(pstWasCellRscp->stCellRscp[i].sCellRSCP < NAS_MML_RSCP_LOWER_LIMIT))
        {
            pstCampCellInfo->astCellInfo[i].sCellRSCP = NAS_MML_UTRA_RSCP_UNVALID;
        }
        else
        {
            pstCampCellInfo->astCellInfo[i].sCellRSCP = pstWasCellRscp->stCellRscp[i].sCellRSCP;
        }
    }

    /*�����ϱ��ź�ǿ��*/
    NAS_MMC_SndMsccRssiInd(&unMeasReportType);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc
 ��������  : �����û�ָ�������Ĳ���
 �������  : pstPlmnId: �û�ָ����PLMN
             ucAccessMode: �û�ָ���Ľ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��01��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��01��
   ��    ��   : w00167002
   �޸�����   : DTS2011102405359:����ָ����ʱ����Ҫֹͣ�������еĸ����ȼ�/bg����
 3.��    ��   : 2013��4��16��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
 4.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
 5.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���
 6.��    ��   : 2014��10��25��
   ��    ��   : b00269685
   �޸�����   : TD��High_Rat_Hplmn_Search���Ե���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucAccessMode
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stUserSpecPlmn;

    /* �����û�ָ����PlmnID������뼼�� */
    stUserSpecPlmn.stPlmnId.ulMcc = pstPlmnId->ulMcc;
    stUserSpecPlmn.stPlmnId.ulMnc = pstPlmnId->ulMnc;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, begin */
    stUserSpecPlmn.enRat          = ucAccessMode;
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, end */
    NAS_MMC_SetUserSpecPlmnId(&stUserSpecPlmn);

    /* ����ָ������ǰפ����PlmnID�����뼼�� */
    NAS_MMC_SaveUserReselPlmnInfo();

    /* ��ǰģʽ����MANUAL���򲻸���NV */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    /* ���õ�ǰע��״̬δע�� */
    NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_FALSE);

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);


    /* ��������ȼ�������ʱ�������й����У���ֹͣ�ö�ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);

        /* HPLMN TIMER ֹͣ�¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_STOP,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    /* ������ڸ����ȼ�������ʱ�������й����У���ֹͣ�ö�ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH);
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER);
        NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
        NAS_MMC_InitTdHighRatSearchCount();
    }

    /* ����ǰ����ģʽд��NVIM�� */
    NAS_MMC_WritePlmnSelectionModeNvim();

    /* ����ģʽ�仯�ϱ�USIM */
    if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
    {
        NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CheckUserSpecPlmnSearchParamMsg_PlmnSelection
 ��������  : ����û�ָ��������Ϣ�Ƿ���ȷ
 �������  : pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- �û�ָ������Ϣ��Ч
             VOS_FALSE  -- �û�ָ������Ϣ��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��21��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
               ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
               ��������ͣ���������ȽϿ��ܻ����
 3.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��NAS_FEATURE_BLACK_WHITE_PLMN��
 4.��    ��   : 2012��10��11��
   ��    ��   : w00176964
   �޸�����   : DTS201201002303:���ƶ����ƺ�������פ��TDС��,ָ���Ѻ���������,NAS����anycell
                ��פ��WС������Ȼ����available timer
 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_MMC_CheckUserSpecPlmnSearchParamMsg_PreProc(
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserSelReqMsg   = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstUserSpecPlmnId  = VOS_NULL_PTR;

    pstUserSelReqMsg = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    /* ָ���û�ָ��������Ϣ�е�PlmnId */
    pstUserSpecPlmnId  = (NAS_MML_PLMN_ID_STRU*)&(pstUserSelReqMsg->stPlmnId);

    /* �ж��û�ָ����Plmn�Ƿ���Ч����Ч���򷵻�VOS_FALSE */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstUserSpecPlmnId))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_CheckUserSpecPlmnSearchParamMsg_PlmnSelection():plmn invalid");
        return VOS_FALSE;
    }

    /* ��PLMN ID�Ƿ�������������PLMN �б��� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(pstUserSpecPlmnId))
    {
        return VOS_FALSE;
    }

    /* ָ��PLMN ����������, ����VOS_FALSE */
    if ( VOS_TRUE != NAS_MML_IsPlmnIdRoamingAllowed(pstUserSpecPlmnId) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListReq_PreProc
 ��������  : ID_MSCC_MMC_PLMN_LIST_REQ��Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��5��
   ��    ��   : w00176964
   �޸�����   : V7R1 C50 GUL BG��Ŀ:W�º�L����PSҵ���жϲ�׼ȷ,����RRC�����ж��ܷ����LIST����
 3.��    ��   : 2013��05��07��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ��ɾ���б�����L�µ����������ж�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ��ǰ��PSҵ���жϲ�׼ȷ,�յ�LIST��������RRC�ж��ܷ���,
       CSҵ��ֱ�ӻظ�REJ */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        /* ����LIST REJ��MSCC */
        NAS_Mmc_SndMsccPlmnListRej();

        return VOS_TRUE;
    }



    /* �����Գ����ڲ�LIST������ʱ�������У���ֹͣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(
                                       TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST))
    {
        /* ֹͣTI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST);
    }

    /* ��״̬������״̬�����ܴ���������� */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCsgListAbortReq_PreProc
 ��������  : CSG LIST ABORT��Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg    - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;
    NAS_MMC_FSM_ID_ENUM_UINT32          ulCurrentFsmId;
    VOS_UINT32                          ulFsmIdInFsmStackFlg;

    /* �û�CSG LIST������Ϣ*/
    ulCacheEventType     = NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);
    ulCurrentFsmId       = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= ulCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulFsmIdInFsmStackFlg = NAS_MMC_IsFsmIdInFsmStack(NAS_MMC_FSM_PLMN_LIST);

    /* ���û�CSG LIST�������� */
    if (VOS_TRUE == ulExistFlg )
    {
        /* ������� */
        NAS_MMC_ClearCacheMsg(ulCacheEventType);

        /* ��MSCC�ظ�ID_MMC_MSCC_CSG_LIST_ABORT_CNF */
        NAS_MMC_SndMsccUserCsgListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* �����Գ����û�CSG LIST������ʱ���Ƿ������� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH);

        /* ��MSCC�ظ�list abort cnf */
        NAS_MMC_SndMsccUserCsgListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* CSG LIST����״̬��δ���У�Ϊ��֤ATͨ����������ʱҲ��MSCC�ظ���� */
    if ((ulCurrentFsmId != NAS_MMC_FSM_PLMN_LIST)
     && (VOS_FALSE == ulFsmIdInFsmStackFlg))
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCsgListAbortReq_PreProc:ERROR");

        /* ��MSCC�ظ�LIST ABORT CNF */
        NAS_MMC_SndMsccUserCsgListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* ��״̬������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListSearchReq_PreProc
 ��������  : CSG �б�������Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg    - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enAsCellCampOn;

    enAsCellCampOn = NAS_MMC_GetAsCellCampOn();

    /* ��ǰ��֧��CSG���ܣ�ֱ�ӷ���list rej */
    if (VOS_FALSE == NAS_MML_IsSupportLteCsg())
    {
        /* ����LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();

        return VOS_TRUE;
    }

    /* ��ǰ��PSҵ���жϲ�׼ȷ,�յ�LIST��������RRC�ж��ܷ���,
       CSҵ��ֱ�ӻظ�REJ */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        /* ����LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();

        return VOS_TRUE;
    }

    /* TDS��פ��̬��֧��csg list����ֱ�ӻظ�ʧ�� */
    if((VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    && (NAS_MMC_AS_CELL_CAMP_ON == enAsCellCampOn))
    {
        /* ����LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();

        return VOS_TRUE;
    }

    /* �����Գ����ڲ�LIST������ʱ�������У���ֹͣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(
                                       TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST))
    {
        /* ֹͣTI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST);
    }

    /* ��״̬������״̬�����ܴ���������� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PreProc
 ��������  : �����Գ���CSG�б�������ʱ����ʱ��Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg    - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰ��֧��CSG���ܣ�ֱ�ӷ���list rej */
    if (VOS_FALSE == NAS_MML_IsSupportLteCsg())
    {
        /* ����LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();

        return VOS_TRUE;
    }

    /* ��ǰ��PSҵ���жϲ�׼ȷ,�յ�LIST��������RRC�ж��ܷ���,
       CSҵ��ֱ�ӻظ�REJ */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        /* ����LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();

        return VOS_TRUE;
    }

    /* �����Գ����ڲ�LIST������ʱ�������У���ֹͣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(
                                       TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST))
    {
        /* ֹͣTI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST);
    }

    /* ��״̬������״̬�����ܴ���������� */
    return VOS_FALSE;
}

#endif
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PreProc
 ��������  : TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST��ʱ����ʱ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��5��
   ��    ��   : w00176964
   �޸�����   : V7R1 C50 GUL BG��Ŀ:W�º�L����PSҵ���жϲ�׼ȷ,����RRC�����ж��ܷ����LIST����
 3.��    ��   : 2013��05��07��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ��ɾ���б�����L�µ����������ж�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ��ǰ��PSҵ���жϲ�׼ȷ,�յ�LIST��������RRC�ж��ܷ���,
       CSҵ��ֱ�ӻظ�REJ */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        /* ����LIST REJ��MSCC */
        NAS_Mmc_SndMsccPlmnListRej();

        return VOS_TRUE;
    }



    /* ��״̬������״̬�����ܴ���������� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PreProc
 ��������  : TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��ʱ����ʱ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��06��13��
   ��    ��   : s46746
   �޸�����   : For CS/PS mode 1������������Ҫ����������GU����
 3.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 4.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
 5.��    ��   : 2013��3��11��
   ��    ��   : w00176964
   �޸�����   : DTS2014030508059:�ڲ�LIST��ֻ�ڷ�פ�������CSҵ��ʱ����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCsSigConnStatusFlg;
    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enCampStaus;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurFsmId;

    VOS_UINT32                          ulSingleDomainNeedPlmnSrch;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRatType;

    enCurRatType                = NAS_MML_GetCurrNetRatType();
#endif

    ulSingleDomainNeedPlmnSrch  = NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* ����Ѿ�������Available��ʱ����������������Ҫ�����ڲ��б��ѳ�ʱ��Ϣ����������Ϣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        return VOS_TRUE;
    }

    /* ��ǰ��������,��������Ϣ */
    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
#if   (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == enCurRatType)
        {
            if (VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU())
            {
                return VOS_TRUE;
            }
        }
        else
        {
            if ((VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
             && (VOS_FALSE == ulSingleDomainNeedPlmnSrch))
            {
                return VOS_TRUE;
            }
        }
#else
        if ((VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
         && (VOS_FALSE == ulSingleDomainNeedPlmnSrch))
        {
            return VOS_TRUE;
        }
#endif
    }

    /* ��ǰ�޿�ʱ����������Ϣ */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_TRUE;
    }

    /* ��ǰ״̬��ID */
    enCurFsmId = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enCurFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* ��״̬�����е��ж� */
    if ( NAS_MMC_FSM_L1_MAIN != enCurFsmId)
    {
        /* Ŀǰֻ��������״̬�����й����ж�������Ϣ */
        if ((NAS_MMC_FSM_PLMN_SELECTION == enCurFsmId)
          ||(NAS_MMC_FSM_ANYCELL_SEARCH == enCurFsmId))
        {
            return VOS_TRUE;
        }

        /* ����״̬������ʱ������ʱ�������Գ��� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);

        return VOS_TRUE;
    }

    enCampStaus                 = NAS_MMC_GetAsCellCampOn();
    ucCsSigConnStatusFlg        = NAS_MML_GetCsSigConnStatusFlg();

    /* ��ǰ��PSҵ���жϲ�׼ȷ,�յ�LIST��������RRC�ж��ܷ���,
       CSҵ������CS�������ӻ�δפ��ʱ������������LIST��������ʱ������ */
    if ((VOS_TRUE                    == NAS_MML_GetCsServiceExistFlg())
     || (NAS_MMC_AS_CELL_NOT_CAMP_ON == enCampStaus)
     || (VOS_TRUE                    == ucCsSigConnStatusFlg))
    {
        /* ������ʱ��TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);

        return VOS_TRUE;
    }


    /* ����L1 MAIN���� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcInterPlmnListReq_PreProc
 ��������  : �ڲ�LIST������Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��27��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��06��13��
   ��    ��   : s46746
   �޸�����   : For CS/PS mode 1������������Ҫ����������GU����
 3.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
 4.��    ��   : 2013��3��11��
   ��    ��   : w00176964
   �޸�����   : DTS2014030508059:�ڲ�LIST��ֻ�ڷ�פ�������CSҵ��ʱ����������
 5.��    ��   : 2015��10��13��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterPlmnListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCsSigConnStatusFlg;
    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enCampStaus;
    VOS_UINT32                          ulSingleDomainNeedPlmnSrch;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRatType;

    enCurRatType            = NAS_MML_GetCurrNetRatType();
#endif

    ulSingleDomainNeedPlmnSrch = NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* �����Գ����û�LIST������ʱ�������У��򲻴����ڲ�LIST��,��������Ϣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST))
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CSG)
    /* �����Գ����û�CSG LIST������ʱ�������У��򲻴����ڲ�LIST��,��������Ϣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH))
    {
        return VOS_TRUE;
    }
#endif

    /* ��ǰ����������Ҳ���CS/PS mode 1פ��LTE����������GSM��WCDMA����,
       ��������Ϣ */
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
#if   (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == enCurRatType)
        {
            if (VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU())
            {
                return VOS_TRUE;
            }
        }
        else
        {
            if ((VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
             && (VOS_FALSE == ulSingleDomainNeedPlmnSrch))
            {
                return VOS_TRUE;
            }
        }
#else
        if ((VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
         && (VOS_FALSE == ulSingleDomainNeedPlmnSrch))
        {
            return VOS_TRUE;
        }
#endif
    }

    /* ��ǰ�޿�ʱ����������Ϣ */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_TRUE;
    }

    enCampStaus                 = NAS_MMC_GetAsCellCampOn();
    ucCsSigConnStatusFlg        = NAS_MML_GetCsSigConnStatusFlg();

    /* ��ǰ��PSҵ���жϲ�׼ȷ,�յ�LIST��������RRC�ж��ܷ���,
       CSҵ������CS�������ӻ�δפ��ʱ������������LIST��������ʱ������ */
    if ((VOS_TRUE                    == NAS_MML_GetCsServiceExistFlg())
     || (NAS_MMC_AS_CELL_NOT_CAMP_ON == enCampStaus)
     || (VOS_TRUE                    == ucCsSigConnStatusFlg))
    {
        /* ������ʱ��TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);

        return VOS_TRUE;
    }


    /* L1 MAIN�ϣ���״̬���ﴥ������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_PreProc
 ��������  : ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ԥ����
 �������  : ulEventType
             *pstMsg
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��9��24��
   ��    ��   : w00166186
   �޸�����   : V7R1 PHASE II
 3.��    ��   : 2011��12��7��
   ��    ��   : z00161729
   �޸�����   : V7R1 PHASE IV
 4.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;
    NAS_MMC_FSM_ID_ENUM_UINT32          ulCurrentFsmId;
    VOS_UINT32                          ulFsmIdInFsmStackFlg;

    /* �û�LIST������Ϣ*/
    ulCacheEventType     = NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);
    ulCurrentFsmId       = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= ulCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulFsmIdInFsmStackFlg = NAS_MMC_IsFsmIdInFsmStack(NAS_MMC_FSM_PLMN_LIST);

    /* ���û�LIST�������� */
    if (VOS_TRUE == ulExistFlg )
    {
        /* ������� */
        NAS_MMC_ClearCacheMsg(ulCacheEventType);

        /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
        NAS_MMC_SndMsccPlmnListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* �����Գ����û�LIST������ʱ���Ƿ������� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST))
    {
        /* ֹͣTI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST);

        /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
        NAS_MMC_SndMsccPlmnListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* LIST����״̬��δ���У�Ϊ��֤ATͨ����������ʱҲ��MSCC�ظ���� */
    if ((ulCurrentFsmId != NAS_MMC_FSM_PLMN_LIST)
     && (VOS_FALSE == ulFsmIdInFsmStackFlg))
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_PreProc:ERROR");

        /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
        NAS_MMC_SndMsccPlmnListAbortCnf(VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* ��״̬������ */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PreProc
 ��������  : ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ��Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;
    NAS_MMC_FSM_ID_ENUM_UINT32          ulCurrentFsmId;
    VOS_UINT32                          ulFsmIdInFsmStackFlg;

    /* �û�ָ��������Ϣ*/
    ulCacheEventType     = NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);
    ulCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    ulFsmIdInFsmStackFlg = NAS_MMC_IsFsmIdInFsmStack(NAS_MMC_FSM_PLMN_SELECTION);

    if (NAS_FSM_BUTT <= ulCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* ���û�ָ���������� */
    if (VOS_TRUE == ulExistFlg )
    {
        /* ������� */
        NAS_MMC_ClearCacheMsg(ulCacheEventType);

        /* ��MSCC�ظ�TAFMMC_SPEC_PLMN_SEARCH_ABORT_CNF */
        NAS_MMC_SndMsccSpecPlmnSearchAbortCnf();
        return VOS_TRUE;
    }

    /* ָ������״̬��δ�����У�Ϊ��֤ATͨ����������ʱҲ��MSCC�ظ���� */
    if ((ulCurrentFsmId != NAS_MMC_FSM_PLMN_SELECTION)
     && (VOS_FALSE == ulFsmIdInFsmStackFlg))
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PreProc:ERROR");

        /* ��MSCC�ظ�TAFMMC_SPEC_PLMN_SEARCH_ABORT_CNF */
        NAS_MMC_SndMsccSpecPlmnSearchAbortCnf();
        return VOS_TRUE;
    }

    /* ��״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDplmnNplmnList_PreProc
 ��������  : ����DPLMN/NPLMN��Ӧ��ȫ�ֱ�����NVIM
 �������  : MSCC_MMC_DPLMN_SET_REQ_STRU                            *pstRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��12��
    ��    ��   : s00217060
    �޸�����   : DTS2015120901555�޸�:AT������ehplmn����8��ʱ��Ⱥ����dplmnlistnum

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcDplmnSetReq_PreProc(
    MSCC_MMC_DPLMN_SET_REQ_STRU                            *pstRcvMsg
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU                       *pstDPlmnNPlmnCfgCtx = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MMC_L1_STA_ENUM_UINT32                              enMmcL1Sta;
    NAS_MML_PLMN_ID_STRU                                    stTmpPlmn;
    VOS_UINT32                                              i;

    pstDPlmnNPlmnCfgCtx     = NAS_MMC_GetDPlmnNPlmnCfgCtx();
    pstDPlmnNPlmnCfgInfo    = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    enMmcL1Sta              = NAS_MMC_GetFsmTopState();

    /* DPLMN����ʱ, seq���ô�:
       ����ж���AT�����·�DPLMN��1��ʾ��ʼ��0xFF��ʾ����;
       ���ֻ��1����0xFF�ȱ�ʾ��ʼҲ��ʾ���� */

    /* seq����Ч��ΧΪ1-0xFF,Ϊ0��ʾ�쳣 */
    if (VOS_FALSE == NAS_MMC_IsDplmnSetSeqValid(pstRcvMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ProcDplmnSetReq_PreProc seq error");

        NAS_TRACE_HIGH("ERROR:NAS_MMC_ProcDplmnSetReq_PreProc seq error");

        return VOS_FALSE;
    }

    /* ���ÿ�ʼ */
    if ((1 == pstRcvMsg->ucSeq)
     || ((0xFF == pstRcvMsg->ucSeq)
      && (VOS_FALSE == pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg)))
    {
        if (NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE == pstRcvMsg->enApPresetDplmnScene)
        {
            pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy = (NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                                                              sizeof(NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU));

            if (VOS_NULL_PTR == pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy)
            {
                NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_ProcDplmnSetReq_PreProc mem alloc error");

                NAS_TRACE_HIGH("ERROR:NAS_MMC_ProcDplmnSetReq_PreProc mem alloc error");

                return VOS_FALSE;
            }

            PS_MEM_SET(pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy, 0x00, sizeof(NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU));

            pstDPlmnNPlmnCfgInfo = pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy;
        }

        /* �����������߷ǻ��������ػ�״̬�£�ȫ�ֱ����е�Ehplmn�Լ���ѧϰ��Dplmn/Nplmn������Чֵ */
        if ((NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE == pstRcvMsg->enApPresetDplmnScene)
         || (NAS_MMC_L1_STA_NULL == enMmcL1Sta))
        {
            NAS_MMC_ReadDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);

            /* Ap�·���Ehplmn List���ϴ����õ�Ehplmn List�н���������Ҫ�ȴ�NV�ж�ȡ��ѧϰ��Dplmn/Nplmn��Ϣ�������浽ȫ�ֱ����� */
            if (VOS_TRUE == NAS_MML_IsTheIntersectionOfSpecPlmnListsEmpty(pstDPlmnNPlmnCfgInfo->ucEHplmnNum,
                                                                          pstDPlmnNPlmnCfgInfo->astEHplmnList,
                                                                          pstRcvMsg->stDplmnInfo.ucEhPlmnNum,
                                                                          pstRcvMsg->stDplmnInfo.astEhPlmnInfo))
            {
                NAS_MMC_ReadSelfLearnDplmnNplmnCfgNvim(pstDPlmnNPlmnCfgInfo);
            }
        }

        /* ���֮ǰAPԤ�õ�DPLMN������UE��ѧϰ�õ���DPLMN */
        (VOS_VOID)PS_MEM_MOVE(&(pstDPlmnNPlmnCfgInfo->astDPlmnList[0]),
                              &(pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usPresetDplmnNum]),
                              (pstDPlmnNPlmnCfgInfo->usDplmnListNum - pstDPlmnNPlmnCfgInfo->usPresetDplmnNum) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg        = VOS_TRUE;
        pstDPlmnNPlmnCfgInfo->usDplmnListNum     -= pstDPlmnNPlmnCfgInfo->usPresetDplmnNum;
        pstDPlmnNPlmnCfgInfo->usPresetDplmnNum    = 0;
        pstDPlmnNPlmnCfgCtx->enApPresetDplmnScene = pstRcvMsg->enApPresetDplmnScene;
    }

    /* ���������£��ǵ�һ����������Ҳ��Ҫʹ��workcopy */
    if (NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE == pstDPlmnNPlmnCfgCtx->enApPresetDplmnScene)
    {
        pstDPlmnNPlmnCfgInfo = pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy;
    }

    /* ����ȫ�ֱ����е� DPLMN & NPLMN */
    NAS_MMC_UpdateDplmnNplmnList_PreProc(pstRcvMsg, pstDPlmnNPlmnCfgInfo);

    /* ���ý��� */
    if (0xFF == pstRcvMsg->ucSeq)
    {
        /* �������ý�����ʶ */
        pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg = VOS_FALSE;

        /* �汾��*/
        PS_MEM_CPY(pstDPlmnNPlmnCfgInfo->aucVersionId, pstRcvMsg->aucVersionId, TAF_MMA_VERSION_INFO_LEN);

        /* Note: pstDPlmnNPlmnCfgInfo->ucEHplmnNum���Ϊ8��,��ʶ��Щ������ʹ�õ�ǰ��DPLMN
           pstRcvMsg->stDplmnInfo.ucEhPlmnNum���Ϊ17��16���ÿ���Ӧ��EHPLMN��1��IMSI�Ƶ�������,IMSI�Ƶ������������һ�� */

        /* ��IMSI�Ƶ������ķ���EHPLMN�б��еĵ�һ�� */
        if (pstRcvMsg->stDplmnInfo.ucEhPlmnNum > TAF_MMA_MAX_EHPLMN_NUM)
        {
            pstRcvMsg->stDplmnInfo.ucEhPlmnNum = TAF_MMA_MAX_EHPLMN_NUM;
        }

        pstDPlmnNPlmnCfgInfo->astEHplmnList[0].ulMcc    = pstRcvMsg->stDplmnInfo.astEhPlmnInfo[pstRcvMsg->stDplmnInfo.ucEhPlmnNum - 1].ulMcc;
        pstDPlmnNPlmnCfgInfo->astEHplmnList[0].ulMnc    = pstRcvMsg->stDplmnInfo.astEhPlmnInfo[pstRcvMsg->stDplmnInfo.ucEhPlmnNum - 1].ulMnc;
        pstDPlmnNPlmnCfgInfo->ucEHplmnNum = 1;

        /* �ٴ�ʣ�µ�EHPLMN������7�� */
        for (i = 0; i < (VOS_UINT32)(pstRcvMsg->stDplmnInfo.ucEhPlmnNum - 1); i++)
        {
            PS_MEM_SET(&stTmpPlmn, 0xFF, sizeof(NAS_MML_PLMN_ID_STRU));
            stTmpPlmn.ulMcc = pstRcvMsg->stDplmnInfo.astEhPlmnInfo[i].ulMcc;
            stTmpPlmn.ulMnc = pstRcvMsg->stDplmnInfo.astEhPlmnInfo[i].ulMnc;

            /* û���ظ��ļӵ��б��� */
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stTmpPlmn, pstDPlmnNPlmnCfgInfo->ucEHplmnNum, pstDPlmnNPlmnCfgInfo->astEHplmnList))
            {
                pstDPlmnNPlmnCfgInfo->astEHplmnList[pstDPlmnNPlmnCfgInfo->ucEHplmnNum].ulMcc    = stTmpPlmn.ulMcc;
                pstDPlmnNPlmnCfgInfo->astEHplmnList[pstDPlmnNPlmnCfgInfo->ucEHplmnNum].ulMnc    = stTmpPlmn.ulMnc;
                pstDPlmnNPlmnCfgInfo->ucEHplmnNum++;
            }

            /* �ﵽ������ʱ���ټӵ��б��� */
            if (pstDPlmnNPlmnCfgInfo->ucEHplmnNum >= NAS_MMC_MAX_CFG_HPLMN_NUM)
            {
                break;
            }
        }

        /* ����NVIM */
        NAS_MMC_WriteApPresetAndSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

        if (NAS_MSCC_PIF_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE == pstDPlmnNPlmnCfgCtx->enApPresetDplmnScene)
        {
            PS_MEM_FREE(WUEPS_PID_MMC, pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy);
            pstDPlmnNPlmnCfgCtx->pstDplmnNplmnInfoWorkCopy = VOS_NULL_PTR;

            /* ���ǵ���״̬�仯ʱ����һ����������ڹػ�״̬���ڶ�����������ڿ���״̬��ȫ�ֱ����п��ܱ����³�ʼ������Ҫ���¶�NV */
            NAS_MMC_InitUserDPlmnNPlmnInfo(pstDPlmnNPlmnCfgCtx);

            NAS_MMC_ReadDplmnNplmnInfoNvim();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsDplmnSetSeqValid
 ��������  : �ж�Ap���·��ĸ���DPlmn��Ϣ�е�ucSeq�Ƿ�Ϊ��Чֵ
 �������  : VOS_UINT8                           ucSeq
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��2��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��11��
    ��    ��   : s00217060
    �޸�����   : DTS2015120901555:�޸ĺ�����Σ�����EHPLMN�������ж�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDplmnSetSeqValid(
    MSCC_MMC_DPLMN_SET_REQ_STRU                           *pstDPlmnSetReq
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU                      *pstDPlmnNPlmnCfgCtx = VOS_NULL_PTR;

    pstDPlmnNPlmnCfgCtx     = NAS_MMC_GetDPlmnNPlmnCfgCtx();

    if (VOS_NULL_PTR == pstDPlmnSetReq)
    {
        return VOS_FALSE;
    }

    /* seq����Ч��ΧΪ1-0xFF,Ϊ0��ʾ�쳣 */
    if (0 == pstDPlmnSetReq->ucSeq)
    {
        return VOS_FALSE;
    }

    /* AP�·��Ķ�����������ĵ�һ����ucSeq���Ǵ�1��ʼ������Ϊ����Ч��ucSeq */
    if ((1 != pstDPlmnSetReq->ucSeq)
     && (0xFF != pstDPlmnSetReq->ucSeq)
     && (VOS_FALSE == pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg))
    {
        return VOS_FALSE;
    }

    /* EHPLMN����Ϊ0������FALSE */
    if (0 == pstDPlmnSetReq->stDplmnInfo.ucEhPlmnNum)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDplmnNplmnList_PreProc
 ��������  : ��APԤ�õ�DPLMN���µ�ȫ�ֱ����У����DPLMN Ҳ��NPLMN List�У������NPLMN List��ɾ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateDplmnNplmnList_PreProc(
    MSCC_MMC_DPLMN_SET_REQ_STRU                            *pstRcvMsg,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstSelfLearnDplmnInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usPresetDplmnNum;                                       /* �������õ�Dplmn�ĸ��� */
    VOS_UINT16                                              usSelfLearningDplmnNum;
    VOS_UINT16                                              usTotalDplmnNum;
    VOS_UINT32                                              i;

    /* ����ѧϰ��DPLMN���ݵ�pstSelfLearnDplmnInfo�� */
    usSelfLearningDplmnNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum - pstDPlmnNPlmnCfgInfo->usPresetDplmnNum;

    if (usSelfLearningDplmnNum > 0)
    {
        pstSelfLearnDplmnInfo = (NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU*)PS_MEM_ALLOC(
                                                          WUEPS_PID_MMC,
                                                          usSelfLearningDplmnNum*sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
        if (VOS_NULL_PTR == pstSelfLearnDplmnInfo)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:NAS_MMC_UpdateDplmnNplmnList_PreProc Mem Alloc Failed");
            return;
        }

        PS_MEM_CPY(pstSelfLearnDplmnInfo,
                   &(pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usPresetDplmnNum]),
                   usSelfLearningDplmnNum*sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
    }


    /* ���DPLMN�б�ȫ�ֱ��� */
    usPresetDplmnNum  = pstDPlmnNPlmnCfgInfo->usPresetDplmnNum;

    /* DPLMN�ĸ��� */
    usTotalDplmnNum = usPresetDplmnNum + pstRcvMsg->stDplmnInfo.usDplmnNum;
    pstDPlmnNPlmnCfgInfo->usDplmnListNum    = NAS_MML_MIN(usTotalDplmnNum, NAS_MMC_MAX_CFG_DPLMN_NUM);

    for (i = usPresetDplmnNum; i < pstDPlmnNPlmnCfgInfo->usDplmnListNum; i++)
    {
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = pstRcvMsg->stDplmnInfo.astDplmnList[i-usPresetDplmnNum].stPlmn.ulMcc;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = pstRcvMsg->stDplmnInfo.astDplmnList[i-usPresetDplmnNum].stPlmn.ulMnc;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MMC_ConvertApPresetRatToSimRat(pstRcvMsg->stDplmnInfo.astDplmnList[i-usPresetDplmnNum].usRat);
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_CS;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enType                            = NAS_MMC_DPLMN_NPLMN_PRESETTING_TYPE;

        /* �����ǰDPLMNҲ��NPLMN�У������NPLMN List��ɾ�� */
        NAS_MMC_RemoveSpecDplmnFromNplmnList(&(pstDPlmnNPlmnCfgInfo->astDPlmnList[i]), pstDPlmnNPlmnCfgInfo);
    }

    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum;

    /* ���֮ǰ������ѧϰDPLMN������������APԤ�õ�DPLMN�󣬽���ѧϰ��DPLMN�ӵ�DPLMN List���� */
    if (VOS_NULL_PTR != pstSelfLearnDplmnInfo)
    {
        for (i = 0; i < usSelfLearningDplmnNum; i++)
        {
            if (pstDPlmnNPlmnCfgInfo->usDplmnListNum >= NAS_MMC_MAX_CFG_DPLMN_NUM)
            {
                break;
            }

            if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&(pstSelfLearnDplmnInfo[i].stSimPlmnWithRat.stPlmnId),
                                                                                 pstSelfLearnDplmnInfo[i].stSimPlmnWithRat.usSimRat,
                                                                                 pstDPlmnNPlmnCfgInfo->usDplmnListNum,
                                                                                 pstDPlmnNPlmnCfgInfo->astDPlmnList))
            {
                continue;
            }

            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum] = pstSelfLearnDplmnInfo[i];
            pstDPlmnNPlmnCfgInfo->usDplmnListNum++;
        }

        PS_MEM_FREE(WUEPS_PID_MMC, pstSelfLearnDplmnInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccDplmnSetReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_DPLMN_SET_REQ��Ϣ�Ĵ���
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
VOS_UINT32 NAS_MMC_RcvMsccDplmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_DPLMN_SET_REQ_STRU                            *pstRcvMsg = VOS_NULL_PTR;
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU                        stInterDplmnSetReq;
    VOS_UINT32                                              ulRet;

    ulRet     = VOS_TRUE;

    pstRcvMsg = (MSCC_MMC_DPLMN_SET_REQ_STRU *)pstMsg;

    if (0xFF == pstRcvMsg->ucSeq)
    {
        /* ����MMCMMC_INTER_DPLMN_SET_REQ��Ϣ */
        PS_MEM_SET(&stInterDplmnSetReq, 0x00, sizeof(NAS_MMC_INTER_DPLMN_SET_REQ_STRU));

        NAS_MMC_BuildInterDplmnSetReqMsg(pstRcvMsg->aucVersionId,
                                         pstRcvMsg->stDplmnInfo.ucEhPlmnNum,
                                         pstRcvMsg->stDplmnInfo.astEhPlmnInfo,
                                         &stInterDplmnSetReq);

        /* �жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬�� �������Ϣ�Ļ��� */
        ulRet = NAS_MMC_ProcMsgPrio(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_DPLMN_SET_REQ),
                                    (struct MsgCB *)&stInterDplmnSetReq);
    }

    /* ����DPLMN/NPLMN�б� */
    if (VOS_FALSE == NAS_MMC_ProcDplmnSetReq_PreProc(pstRcvMsg))
    {
        NAS_MMC_SndMsccDplmnSetCnf(VOS_ERR, &(pstRcvMsg->stCtrl));

        return VOS_TRUE;
    }

    /* MMC��MSCC����ID_MMC_MSCC_DPLMN_SET_CNF��Ϣ,�ϱ����ý�� */
    NAS_MMC_SndMsccDplmnSetCnf(VOS_OK, &(pstRcvMsg->stCtrl));

    /* ��ӡԤ�ú��DPLMN/NPLMN�б� */
    NAS_MMC_LogDplmnNplmnList();

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccStopGetGeoReq_PreProc
 ��������  : ID_MSCC_MMC_STOP_GET_GEO_REQ��Ϣ��Ԥ����
 �������  : ulEventType - �¼�����
             *pstMsg     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��12��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccStopGetGeoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;
    NAS_MMC_FSM_ID_ENUM_UINT32          ulCurrentFsmId;
    VOS_UINT32                          ulFsmIdInFsmStackFlg;

    /* �û���ȡ��������Ϣ*/
    ulCacheEventType     = NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_GET_GEO_REQ);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);
    ulCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    ulFsmIdInFsmStackFlg = NAS_MMC_IsFsmIdInFsmStack(NAS_MMC_FSM_GET_GEO);

    if (NAS_FSM_BUTT <= ulCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* �û���ȡ�����뻺�� */
    if (VOS_TRUE == ulExistFlg )
    {
        /* ������� */
        NAS_MMC_ClearCacheMsg(ulCacheEventType);

        /* ��MSCC�ظ�ID_MMC_MSCC_STOP_GET_GEO_CNF */
        NAS_MMC_SndMsccStopGetGeoCnf();
        return VOS_TRUE;
    }

    /* ��ȡ������״̬��δ�����У���ʱҲ��MSCC�ظ���� */
    if ((ulCurrentFsmId != NAS_MMC_FSM_GET_GEO)
     && (VOS_FALSE == ulFsmIdInFsmStackFlg))
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccStopGetGeoReq_PreProc:ERROR");

        /* ��MSCC�ظ�ID_MMC_MSCC_STOP_GET_GEO_CNF */
        NAS_MMC_SndMsccStopGetGeoCnf();

        return VOS_TRUE;
    }

    /* ��״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsConnExist_BgPlmnSearch_PreProc
 ��������  : �жϵ�ǰ�Ƿ��������ӻ�ҵ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : �����������ӻ�ҵ������
             VOS_FALSE : �������������ӻ�ҵ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsConnExist_BgPlmnSearch_PreProc( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat     = NAS_MML_GetCurrNetRatType();

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    /* ����CS�����������,��������BG���� */
    if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsConnExist_BgPlmnSearch_PreProc: Cs Signal Conn exit");

        return VOS_TRUE;
    }

    /* ����CS���ҵ��򻺴��ҵ��,��������BG���� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsConnExist_BgPlmnSearch_PreProc: Cs service exit");

        return VOS_TRUE;
    }

    /* ����PS��Ļ����ҵ��,��������BG���� */
    if ( VOS_TRUE == pstConnStatus->ucPsServiceBufferFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsConnExist_BgPlmnSearch_PreProc: Ps service buffer flg is true");

        return VOS_TRUE;
    }

    /* GSMģʽ��,TBF����,��������BG���� */
    if ((VOS_TRUE == pstConnStatus->ucPsTbfStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsConnExist_BgPlmnSearch_PreProc: ps tbf exit under gsm");

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* L��PS�����������ӻ�ҵ����ڣ���������BG���� */
    if ((NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
     && ((VOS_TRUE == pstConnStatus->ucEpsSigConnStatusFlg)
      || (VOS_TRUE == pstConnStatus->ucEpsServiceConnStatusFlg)))
    {
        NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_IsConnExist_BgPlmnSearch_PreProc: ucEpsSigConnStatusFlg ucEpsServiceConnStatusFlg",
                            pstConnStatus->ucEpsSigConnStatusFlg, pstConnStatus->ucEpsServiceConnStatusFlg);

        return VOS_TRUE;
    }
#endif

    /* PS�򴥷���TC����ҵ�����,��������BG���� */
    if ( VOS_TRUE == pstConnStatus->ucPsTcServiceFlg )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsConnExist_BgPlmnSearch_PreProc: ucPsTcServiceFlg is true");

        return VOS_TRUE;
    }

    /* ���������Ϊ������ҵ�����������,���Է���BG���� */
    return VOS_FALSE;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsEnableBgPlmnSearch_PreProc
 ��������  : �жϵ�ǰ�Ƿ���������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : ����������������
             VOS_FALSE : ������������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��28��
    ��    ��   : w00167002
    �޸�����   : ��ǰUTRAN����ģʽΪTDDʱ�򣬲�����������
  3.��    ��   : 2013��12��20��
    ��    ��   : w00167002
    �޸�����   : DTS2013112917981:guNASɾ����TDģʽ�²��ܽ���bg�ѵ����ơ�
  4.��    ��   : 2015��10��13��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsEnableBgPlmnSearch_PreProc( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat     = NAS_MML_GetCurrNetRatType();

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();


    /* ����Ѿ�������Available��ʱ����������������Ҫ���𱳾����� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "TI_NAS_MMC_AVAILABLE_TIMER running ");
        
        return VOS_FALSE;
    }

    /* ��������Գ����û��б�������ʱ�������й����У��������𱳾����� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST running ");
        
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_CSG)
    /* ��������Գ����û�CSG�б�������ʱ�������й����У��������𱳾����� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH running ");
        
        return VOS_FALSE;
    }
#endif


    /* ��������Գ����ڲ��б�������ʱ�������й����У��������𱳾����� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST running ");
        
        return VOS_FALSE;
    }

    /* ���������ϱ�not camp on��Ϣ���������𱳾����� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "CURR:NAS_MMC_AS_CELL_NOT_CAMP_ON ");
        
        return VOS_FALSE;
    }

    /* Ϊ�˱��ⷴ�����ø����ȼ������Ĵ�����10s�����Գ��Զ�ʱ�������ڼ䲻�����̷��𱳾����� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH RUNNING");
        
        return VOS_FALSE;
    }

    /* �����������ӻ�ҵ�����Ӳ������𱳾����� */
    if (VOS_TRUE == NAS_MMC_IsConnExist_BgPlmnSearch_PreProc())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsEnableBgPlmnSearch_PreProc: connect exit");
        return VOS_FALSE;
    }

    /* ����״̬��������,�����з��𱳾����� */
    if( NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrFsmId IS NOT NAS_MMC_FSM_L1_MAIN");
        
        return VOS_FALSE;
    }

    /* GSMģʽ�£�RRC���Ӵ��ڲ������𱳾�������
       WCDMAģʽ�£�RRC���Ӵ���P̬,�����𱳾�������*/
    if ((VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_WCDMA != enCurrRat))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "enCurrRat IS NOT WCDMA AND ucRrcStatusFlg IS TRUE");
        
        return VOS_FALSE;
    }

    /* ����������Է���BG���� */
    return VOS_TRUE;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiHplmnTimerExpired_PreProc
 ��������  : Ԥ���������յ�HPLMN��ʱ����ʱ��Ϣ,�ж��ܷ���и����ȼ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_TRUE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�
 3.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 4.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������
 5.��    ��   : 2012��11��2��
   ��    ��   : t00212959
   �޸�����   : DTS2012091401559,Ԥ�����н���enable LTE
 6.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���:ɾ��enable L���߼�,���ڿ���ָ������
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiHplmnTimerExpired_PreProc(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchList = VOS_NULL_PTR;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg            = VOS_NULL_PTR;


    /* ��ȡ�����ȼ������б���Ϣ */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();


    /* HPLMN TIMER�����¼��ϱ� */
    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_EXPIRE,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


    /* ��Ҫ�ж�HPLMN Timer��ʱ���˿��Ƿ���Ч����Ч��ֱ�Ӷ�������Ϣ */
    if ( VOS_FALSE == NAS_MMC_IsHighPrioPlmnSearchVaild() )
    {
        return VOS_TRUE;
    }

    pstBgSearchCfg            = NAS_MML_GetBgSearchCfg();

    /* �Ѿ�פ����������ȼ���������ֱ�ӷ��ض�������Ϣ */
    if ( VOS_TRUE == NAS_MMC_IsCampOnHighestPrioPlmn() )
    {
        /* �����ǿ��Hplmn����,���綨�����Կ��ش�: ����Hplmn Timer��ʱ��,
           ֻҪû��פ����home PLMN��,Ҳ��Ҫ�����˶�ʱ��,��һ������2Min,��������T Min����*/
        if ((VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
         && (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER,  NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        }
        else
        {
            /* �Ѿ�פ����������ȼ�������,������ǿHPLMN����δ����,�´ΰ��״�����HPLMN��ʱ�� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_TRUE);
        }

        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "CampOnHighestPrioPlmn,ucEnhancedHplmnSrchFlg is",pstBgSearchCfg->ucEnhancedHplmnSrchFlg);

        return VOS_TRUE;
    }

    /* �޷����и����ȼ�����ʱ,����10s�����Գ��Ը����ȼ�������ʱ�� */
    if ( VOS_FALSE == NAS_MMC_IsEnableBgPlmnSearch_PreProc() )
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);

        /* ɾ��enable L���߼�,�ŵ�����ָ������������ */

        /* ��ʼ�������ȼ������б� */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);

        return VOS_TRUE;
    }



    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiTryingHighPrioPlmnSearchExpired_PreProc
 ��������  : Ԥ�������յ������Գ��Ը����ȼ�������ʱ����ʱ�ж��ܷ���и����ȼ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�
 3.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������
 4.��    ��   : 2012��6��20��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiTryingHighPrioPlmnSearchExpired_PreProc(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg  = VOS_NULL_PTR;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��Ҫ�ж�10s�����Գ��Ը����ȼ�������ʱ���˿��Ƿ���Ч����Ч��ֱ�Ӷ�������Ϣ,Ԥ������� */

    /* �ֶ�ģʽ�·�����Ч */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcTiTryingHighPrioPlmnSearchExpired_PreProc: manual mode");
        return VOS_TRUE;
    }

    /* SIM������λ��CS��PS��Ŀ�����Чʱ������Ч */
    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcTiTryingHighPrioPlmnSearchExpired_PreProc: sim not present");
        return VOS_TRUE;
    }

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcTiTryingHighPrioPlmnSearchExpired_PreProc: Sim reg status false");
        return VOS_TRUE;
    }

    NAS_MMC_LogCurrPlmnRelatedInfo();
    NAS_MMC_LogPlmnRegRejInfo();

    pstBgSearchCfg            = NAS_MML_GetBgSearchCfg();

    /* �Ѿ�פ����������ȼ���������ֱ�ӷ��ض�������Ϣ */
    if ( VOS_TRUE == NAS_MMC_IsCampOnHighestPrioPlmn() )
    {
        /* �����ǿ��Hplmn����,���綨�����Կ��ش�: ����Hplmn Timer��ʱ��,
           ֻҪû��פ����home PLMN��,Ҳ��Ҫ�����˶�ʱ��,��һ������2Min,��������T Min����*/
        if ((VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
         && (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER,  NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        }
        else
        {
            /* �Ѿ�פ����������ȼ�������,������ǿHPLMN����δ����,�´ΰ��״�����HPLMN��ʱ�� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    /* �޷����и����ȼ�����ʱ,����10s�����Գ��Ը����ȼ�������ʱ�� */
    if ( VOS_FALSE == NAS_MMC_IsEnableBgPlmnSearch_PreProc() )
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiHplmnTimerExpired_PreProc
 ��������  : Ԥ���������յ�HPLMN��ʱ����ʱ��Ϣ,�ж��ܷ���и����ȼ�����
 �������  : ulEventType:��Ϣ����
             pstMsg:HPLMN��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_TRUE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiHplmnTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    ulRst = NAS_MMC_ProcTiHplmnTimerExpired_PreProc();
    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_PreProc
 ��������  : Ԥ�������յ������Գ��Ը����ȼ�������ʱ����ʱ�ж��ܷ���и����ȼ�����
 �������  : ulEventType:��Ϣ����
             pstMsg:�����Գ��Ը����ȼ�������ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    ulRst = NAS_MMC_ProcTiTryingHighPrioPlmnSearchExpired_PreProc();

    return ulRst;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvStkSteerRoamingInd_PreProc
 ��������  : �յ�STEER ROAMINGָʾ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:STK_NAS_STEERING_OF_ROAMING_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��9��20��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 3.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ��ǰû��BG/�����ȼ�������ʱ�������У�
                �򵱳�ʱ���д���������1s����������ʱ����
 4.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������

 5.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL_BG ��Ŀ����
 6.��    ��   : 2013��1��17��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:ֻ����UtranModeΪTDDʱ���Ų���HPLMN��ʱ��
 7.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : ���Ŷ��ƣ����������OPLMN���򲻴���
 8.��    ��    : 2013��11��26��
   ��    ��    : s00190137
   �޸�����    : �����֧�����õ�OPLMN��չ��256��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvStkSteerRoamingInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    VOS_UINT16                          usOplmnNum;
    VOS_UINT8                           ucUpdateUsimForbPlmnFlg;
    VOS_UINT32                          i;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstOplmnAddr      = VOS_NULL_PTR;
    STK_NAS_STEERING_OF_ROAMING_STRU   *pstSteerOfRoamMsg = VOS_NULL_PTR;

    pstSteerOfRoamMsg = (STK_NAS_STEERING_OF_ROAMING_STRU *)pstMsg;

    /* SteeringOfRoaming�����Կ��عرղ��������Ϣ */
    if (VOS_FALSE == NAS_MML_GetStkSteeringOfRoamingSupportFlg())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MML_IsNvimOplmnAvail())
    {
        return VOS_TRUE;
    }

    /* ��ȡȫ�ֱ����ĵ�ַ */
    pstOperPlmnInfo               = NAS_MML_GetSimOperPlmnList();
    pstOplmnAddr                  = pstOperPlmnInfo->astOperPlmnInfo;
    ucUpdateUsimForbPlmnFlg       = VOS_FALSE;

    usOplmnNum        = (VOS_UINT16)(pstSteerOfRoamMsg->usOplmnListLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);

    if ( usOplmnNum > NAS_MML_MAX_OPERPLMN_NUM )
    {
        usOplmnNum = NAS_MML_MAX_OPERPLMN_NUM;
    }

    /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
    NAS_MMC_ConverPlmnInfoFromSim(pstSteerOfRoamMsg->aucOplmnList, usOplmnNum, pstOplmnAddr);

    if ( usOplmnNum > pstOperPlmnInfo->usOperPlmnNum )
    {
        /* ����OPLMN�ĸ��� */
        pstOperPlmnInfo->usOperPlmnNum = usOplmnNum;
    }

    for (i = 0; i < usOplmnNum; i++)
    {
        /* STK_NAS_STEERING_OF_ROAMING_IND��Ϣ��Я����OPLMN��ӽ�ֹ������ɾ�� */
        if (VOS_TRUE == NAS_MML_DelForbPlmn(&pstOplmnAddr[i].stPlmnId))
        {
            ucUpdateUsimForbPlmnFlg = VOS_TRUE;
        }

        NAS_MML_DelForbGprsPlmn(&pstOplmnAddr[i].stPlmnId);
    }

    /* ��ֹ�����б����ı䣬��Ҫ֪ͨUSIM */
    if (VOS_TRUE == ucUpdateUsimForbPlmnFlg)
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* BG����״̬��������,������������Ϣ���ȼ��Ƚ� */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    /* ��ʼ�������ȼ������б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    /* ���HPLMN��ʱ����������,ֹͣ�ö�ʱ��,����1S��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        /* ֹͣHPLMN��ʱ��,����10s�����Գ��Ը����ȼ�������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);


        /* HPLMN TIMERֹͣ�¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_STOP,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* ��ǰUTRAN����ģʽ��ΪTDDʱ���������ڱ����� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH, TI_NAS_MMC_STK_STEERING_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);

        return VOS_TRUE;
    }

    /* ���10s�����Գ��Ը����ȼ�������ʱ����������,��ֹͣ�ö�ʱ��,��������1S��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        /* ֹͣ10s�����Գ��Ը����ȼ�������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH);
    }

    /* ��ǰUTRAN����ģʽ��ΪTDDʱ���������ڱ����� */
    /* ��ǰû��BG����״̬������ʱ��������,�򵱳�ʱ���д���,������1s��ʱ��ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH,
                       TI_NAS_MMC_STK_STEERING_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PreProc
 ��������  : �յ�STEER ROAMINGָʾ��Ԥ����
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SUSPEND_CNF��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
              VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��17��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��8��26��
    ��    ��   : w00242748
    �޸�����   : ��̬������Ŀ

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
#endif

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_SUCCESS == pstSuspendCnf->ucResult)
    {
        /* CBS�ϱ�*/
        NAS_MMC_SndMsccMsgNoNetWorkInd();
    }

#endif

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    /* �����GAS�Ļ�����ֱ�ӽ�״̬������������� */
    if (NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_CNF) == ulEventType)
    {
        return VOS_FALSE;
    }

    /* �����TDS/W������Ļ���������Ҫִ�дμ��ز������Է�ֹ���³�������:
       ����֪ͨ�����FDD������FDD��������ʧ�ܣ�����TDD��������TDD������ʧ�ܣ�
       ��ʱ��Ҫ��FDD�����ڼ��ص��ڴ��У��Է�ֹGSM����LTEפ��������FDD���л�����
       ��FDD�����ڴ��ж���λ
    */
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        enUtranMode = NAS_UTRANCTRL_GetPreUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }
#endif

    return VOS_FALSE;
}


/* NAS_MMC_RcvRrMmGetTransactionReq_PreProc�Ƶ�MM���� */


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcDetachCnfSucc_PreProc
 ��������  : �յ�LMM��eps detach�ɹ���Ԥ����
 �������  : pstLmmDetachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  3.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  4.��    ��   : 2012��12��5��
    ��    ��   : w00176964
    �޸�����   : DTS2012120300431:UE��detach�������Re-attach��ͻ,����UE���ٴ���attach
  5.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  6.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcDetachCnfSucc_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32           enFsmId;

    VOS_UINT32                           ulNeedEnableLte;
    VOS_UINT32                           ulNeedDisableLte;

    enFsmId         = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulNeedEnableLte  = VOS_FALSE;
    ulNeedDisableLte = VOS_FALSE;

    /* ��װ��Ϣ����MSCC����DETACH��� */
    switch (pstLmmDetachCnf->ulReqType)
    {
        case MMC_LMM_MO_DET_PS_ONLY:

#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
            /* ���л��������ֵ���������������Ϊ�˱�֤PC����ͨ�� */
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
#endif

            /* ת��detach�����GMM */
            NAS_MMC_SndGmmLmmMoDetachInd(pstLmmDetachCnf);

            ulNeedDisableLte = NAS_MMC_IsNeedDisableLte_DetachPs();

            NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc();
            NAS_MMC_ProcPsRegStateAndPsServiceState_DetachCnfSucc();
            break;

        case MMC_LMM_MO_DET_CS_ONLY:

            /* ת��detach�����MM */
            NAS_MMC_SndMmLmmMoDetachInd(pstLmmDetachCnf);

            NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc();

            ulNeedEnableLte = NAS_MMC_IsNeedEnableLte_DetachCs();
            break;

        case MMC_LMM_MO_DET_CS_PS:

#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
            /* ���л��������ֵ���������������Ϊ�˱�֤PC����ͨ�� */
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
#endif

            /* ת��detach�����MM */
            NAS_MMC_SndMmLmmMoDetachInd(pstLmmDetachCnf);

            /* ת��detach�����GMM */
            NAS_MMC_SndGmmLmmMoDetachInd(pstLmmDetachCnf);

            ulNeedDisableLte = NAS_MMC_IsNeedDisableLte_DetachCsPs();
            ulNeedEnableLte = NAS_MMC_IsNeedEnableLte_DetachCsPs();

            NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc();
            NAS_MMC_ProcPsRegStateAndPsServiceState_DetachCnfSucc();

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcDetachCnfSucc_PreProc:Unexpected detach request type!");

            break;
    }

    if (VOS_TRUE == ulNeedEnableLte)
    {
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* ��ǰ������disable LTE������ */
    if (VOS_FALSE == ulNeedDisableLte)
    {
        /* ����ֱ�ӷ��ز���Ҫ�������� */
        return VOS_TRUE;
    }

    /* ��¼����disable LTE�ı��,����L��Ϊ��ģ��֪ͨLMM,WAS,GAS */
    NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

    NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_DETACH);

    /* ���detach ������������Ϣ */
    NAS_MMC_InitDetachReqCtx(NAS_MMC_GetDetachReqCtxAddr());

    /* ON PLMN��ֱ�ӿ��Դ��� */
    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
    && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
       /* �����ǰEPS�������Ӵ��ڣ��򻺴湹���������Ϣ */
       if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
       {
           NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE);

           return VOS_TRUE;
       }

       return VOS_FALSE;
    }

    /* ����L1������״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcDetachCnfAuthRej_PreProc
 ��������  : �յ�LMM��detach ��Ȩ���ܵ�Ԥ����
 �������  : pstLmmDetachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  4.��    ��   : 2014��4��24��
    ��    ��   : w00242748
    �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                 ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ
  5.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�,
                 MMC���յ�LMMģ��ȥע��ظ����,��Ȩ���ܾ��������ע��״̬�ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcDetachCnfAuthRej_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    enFsmId = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* ת��detach�����MM/GMM */
    NAS_MMC_SndMmLmmMoDetachInd(pstLmmDetachCnf);
    NAS_MMC_SndGmmLmmMoDetachInd(pstLmmDetachCnf);

    /* ���������л��ж�CS����Ч��־�������Ҫ���� */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

    /* MMC���յ�LMMģ��ȥע��ظ����,��Ȩ���ܾ��������ע��״̬�ϱ� */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,NAS_MMC_LIMITED_SERVICE);


    /* ON PLMN��ֱ�ӿ��Դ��� */
    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
    && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
       /* �����ǰEPS�������Ӵ��ڣ��򻺴湹���������Ϣ */
       if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
       {
            NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

           return VOS_TRUE;
       }

       return VOS_FALSE;
    }

    /* ����L1������״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsOnlyDetachCnf_PreProc
 ��������  : �յ�LMM��EPS detach�ظ���Ԥ����
 �������  : pstLmmDetachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��07��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

  5.��    ��   : 2015��10��5��
    ��    ��   : w00167002
    �޸�����   : DTS2015091902138:��L��DETACH���ؽ��ΪMMC_LMM_DETACH_RSLT_ACCESS_BARED��
                 ʵ��CGATT����ؽ��ΪERROR.ԭ��Ϊ��ǰ��NORMAL SERVICE.��DETACH��
                 ������״̬�Ż�IIǰ��L�᷵��limit service���Ż��󣬵�ǰ��Ȼά��NORMAL
                 SERVICE,����CGATT����ERROR.
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcEpsOnlyDetachCnf_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{

    VOS_UINT32                           ulRet;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enPsMsccServiceStatus;

    ulRet                = VOS_TRUE;


    /* detach������� */
    switch (pstLmmDetachCnf->ulDetachRslt)
    {
        case MMC_LMM_DETACH_RSLT_SUCCESS:

            /* ����detach�ɹ����д��� */
            ulRet = NAS_MMC_ProcDetachCnfSucc_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_DETACH_RSLT_ACCESS_BARED:
        case MMC_LMM_DETACH_RSLT_FAILURE:


            /* ����detach�ɹ����д��� */
            ulRet = NAS_MMC_ProcDetachCnfSucc_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            /* ��Ȩ���ܵĴ��� */
            ulRet = NAS_MMC_ProcDetachCnfAuthRej_PreProc(pstLmmDetachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcEpsOnlyDetachCnf_PreProc:Unexpected detach result!");
            break;
    }

    /* ��Ҫ�ȸ���״̬���������ϱ� */

    enPsMsccServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* ��ȡ��ǰPS����״̬ */
    NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                            enPsMsccServiceStatus,
                            pstLmmDetachCnf->ulOpId,
                            NAS_MSCC_PIF_OPER_RESULT_SUCCESS);
    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsOnlyDetachCnf_PreProc
 ��������  : �յ�LMM��detach�ɹ���Ԥ����
 �������  : pstLmmDetachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��07��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcCsOnlyDetachCnf_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{

    VOS_UINT32                           ulRet;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enCsMsccServiceStatus;


    ulRet   = VOS_TRUE;


    /* detach������� */
    switch (pstLmmDetachCnf->ulDetachRslt)
    {
        case MMC_LMM_DETACH_RSLT_SUCCESS:

            /* ����detach�ɹ����д��� */
            ulRet = NAS_MMC_ProcDetachCnfSucc_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_DETACH_RSLT_ACCESS_BARED:
        case MMC_LMM_DETACH_RSLT_FAILURE:


            /* ����detach�ɹ����д��� */
            ulRet = NAS_MMC_ProcDetachCnfSucc_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            /* ��Ȩ���ܵĴ��� */
            ulRet = NAS_MMC_ProcDetachCnfAuthRej_PreProc(pstLmmDetachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsOnlyDetachCnf_PreProc:Unexpected detach result!");
            break;
    }

    /* ��ȡ��ǰCS����״̬ */
    enCsMsccServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);

    NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                            enCsMsccServiceStatus,
                            pstLmmDetachCnf->ulOpId,
                            NAS_MSCC_PIF_OPER_RESULT_SUCCESS);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsPsDetachCnf_PreProc
 ��������  : �յ�LMM��detach�ɹ���Ԥ����
 �������  : pstLmmDetachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��07��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��27��
    ��    ��   : l00130025
    �޸�����   : DTS2012032303156:MMC�ķ���״̬���ϱ��ķ���״̬��Ҫת��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcCsPsDetachCnf_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{

    VOS_UINT32                           ulRet;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enCsMsccServiceStatus;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enPsMsccServiceStatus;

    ulRet                = VOS_TRUE;


    /* detach������� */
    switch (pstLmmDetachCnf->ulDetachRslt)
    {
        case MMC_LMM_DETACH_RSLT_SUCCESS:

            /* ����detach�ɹ����д��� */
            ulRet = NAS_MMC_ProcDetachCnfSucc_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_DETACH_RSLT_ACCESS_BARED:
        case MMC_LMM_DETACH_RSLT_FAILURE:


            /* ����detach�ɹ����д��� */
            ulRet = NAS_MMC_ProcDetachCnfSucc_PreProc(pstLmmDetachCnf);

            break;

        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            /* ��Ȩ���ܵĴ��� */
            ulRet = NAS_MMC_ProcDetachCnfAuthRej_PreProc(pstLmmDetachCnf);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsPsDetachCnf_PreProc:Unexpected detach result!");
            break;
    }
    /* ��ȡ��ǰ�ϱ��õ�CS_PS����״̬ */
    enCsMsccServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS);
    enPsMsccServiceStatus = NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS);

    NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_CS,
                            enCsMsccServiceStatus,
                            pstLmmDetachCnf->ulOpId,
                            NAS_MSCC_PIF_OPER_RESULT_SUCCESS);

    NAS_MMC_SndMsccDetachCnf(NAS_MSCC_PIF_SRVDOMAIN_PS,
                            enPsMsccServiceStatus,
                            pstLmmDetachCnf->ulOpId,
                            NAS_MSCC_PIF_OPER_RESULT_SUCCESS);

    return ulRet;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-28, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmServiceRsltInd_PreProc
 ��������  : ��lmm���͵�service result ind��Ϣ����Ԥ����
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��26��
   ��    ��   : z0161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��4��14��
   ��    ��   : w00242748
   �޸�����   : DTS2014041506202:����L��DETACH����CM SERVICE REJ����ԭ��ֵ���ϱ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmServiceRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCause;

    enCause       = NAS_MML_REG_FAIL_CAUSE_BUTT;

    pstSerRsltMsg = (LMM_MMC_SERVICE_RESULT_IND_STRU *)pstMsg;

    NAS_MMC_ConverLmmServiceRsltToMMLCause(pstSerRsltMsg,&enCause);

    NAS_MMC_SndMsccServRejRsltInd(NAS_MSCC_PIF_SRVDOMAIN_PS, (VOS_UINT16)enCause);

    /* �жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬�� �������Ϣ�Ļ��� */
    ulRet = NAS_MMC_ProcMsgPrio(ulEventType, pstMsg);

    /* ��Ҫ��ϵ�ǰ״̬���������Ϣ�Ļ���,���ʾԤ������� */
    if ( VOS_TRUE == ulRet )
    {
        return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-28, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmEmmInfoInd_PreProc
 ��������  : ��lmm���͵�LMM_EMM_INFO_IND��Ϣ���д���
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��12��11��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��01��09��
   ��    ��   : l65478
   �޸�����   : DTS2013010809507���������ϱ�����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmEmmInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MM_INFO_IND_STRU                                   *pstSendMsg    = VOS_NULL_PTR;
    LMM_MMC_EMM_INFO_IND_STRU                              *pstLmmEmmInfo = VOS_NULL_PTR;
    NAS_MML_OPERATOR_NAME_INFO_STRU                        *pstCurrOperatorName = VOS_NULL_PTR;
    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;
    VOS_UINT8                                               ucNvWriteFlg;
    NAS_MML_OPERATOR_NAME_INFO_STRU                         stOldOperatorName;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    ucNvWriteFlg        = VOS_FALSE;
    PS_MEM_CPY(&stOldOperatorName, pstCurrOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
    pstLmmEmmInfo = (LMM_MMC_EMM_INFO_IND_STRU *)pstMsg;

    PS_MEM_SET(stNvimOperatorName.aucOperatorNameLong, 0, NAS_NVIM_MAX_OPER_LONG_NAME_LEN);
    PS_MEM_SET(stNvimOperatorName.aucOperatorNameShort, 0, NAS_NVIM_MAX_OPER_SHORT_NAME_LEN);

    if ((VOS_FALSE == pstLmmEmmInfo->stLteEmmInfo.bitOpDaylightTime)
     &&(VOS_FALSE == pstLmmEmmInfo->stLteEmmInfo.bitOpLocTimeZone)
     &&(VOS_FALSE == pstLmmEmmInfo->stLteEmmInfo.bitOpUniTimeLocTimeZone)
     &&(VOS_FALSE == pstLmmEmmInfo->stLteEmmInfo.bitOpLongName)
     &&(VOS_FALSE == pstLmmEmmInfo->stLteEmmInfo.bitOpShortName))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmEmmInfoInd_PreProc():No userful info");
        return VOS_TRUE;
    }

    /* �����ڴ� */
    pstSendMsg = (NAS_MM_INFO_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                sizeof(NAS_MM_INFO_IND_STRU));

    if( VOS_NULL_PTR == pstSendMsg )
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmEmmInfoInd_PreProc():ERROR:Memory Alloc Error.");
       return VOS_TRUE;
    }

    PS_MEM_SET(pstSendMsg, 0, sizeof(NAS_MM_INFO_IND_STRU));

    if (VOS_TRUE == pstLmmEmmInfo->stLteEmmInfo.bitOpLocTimeZone)
    {
        pstSendMsg->ucIeFlg |= NAS_MM_INFO_IE_LTZ;
        pstSendMsg->cLocalTimeZone = pstLmmEmmInfo->stLteEmmInfo.cLocTimeZone;
    }

    if (VOS_TRUE == pstLmmEmmInfo->stLteEmmInfo.bitOpUniTimeLocTimeZone)
    {
        pstSendMsg->ucIeFlg |= NAS_MM_INFO_IE_UTLTZ;
        pstSendMsg->stUniversalTimeandLocalTimeZone.ucYear    = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.ucYear;
        pstSendMsg->stUniversalTimeandLocalTimeZone.ucMonth   = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.ucMonth;
        pstSendMsg->stUniversalTimeandLocalTimeZone.ucDay     = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.ucDay;
        pstSendMsg->stUniversalTimeandLocalTimeZone.ucHour    = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.ucHour;
        pstSendMsg->stUniversalTimeandLocalTimeZone.ucMinute  = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.ucMinute;
        pstSendMsg->stUniversalTimeandLocalTimeZone.ucSecond  = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.ucSecond;
        pstSendMsg->stUniversalTimeandLocalTimeZone.cTimeZone = pstLmmEmmInfo->stLteEmmInfo.stTimeZoneAndTime.cTimeZone;
    }

    if (VOS_TRUE == pstLmmEmmInfo->stLteEmmInfo.bitOpDaylightTime)
    {
        pstSendMsg->ucIeFlg |= NAS_MM_INFO_IE_DST;
        pstSendMsg->ucDST = pstLmmEmmInfo->stLteEmmInfo.enDaylightSavingTime;
    }

    if (VOS_TRUE == pstLmmEmmInfo->stLteEmmInfo.bitOpLongName)
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, pstLmmEmmInfo->stLteEmmInfo.aucOperatorNameLong, NAS_MML_MAX_OPER_LONG_NAME_LEN);

        ucNvWriteFlg = VOS_TRUE;
    }

    if (VOS_TRUE == pstLmmEmmInfo->stLteEmmInfo.bitOpShortName)
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, pstLmmEmmInfo->stLteEmmInfo.aucOperatorNameShort, NAS_MML_MAX_OPER_SHORT_NAME_LEN);

        ucNvWriteFlg = VOS_TRUE;
    }

    if (VOS_TRUE == ucNvWriteFlg)
    {
        /* �����Ϣ���������������֮ǰ��������ݲ�ͬ,��ҪдNV */
        if (0 != VOS_MemCmp(pstCurrOperatorName, &stOldOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU)))
        {
            if ((NAS_NVIM_MAX_OPER_SHORT_NAME_LEN > (pstCurrOperatorName->aucOperatorNameShort[0]))
             && (NAS_NVIM_MAX_OPER_LONG_NAME_LEN > (pstCurrOperatorName->aucOperatorNameLong[0])))
            {
                PS_MEM_CPY(stNvimOperatorName.aucOperatorNameLong, pstCurrOperatorName->aucOperatorNameLong, NAS_NVIM_MAX_OPER_LONG_NAME_LEN);
                PS_MEM_CPY(stNvimOperatorName.aucOperatorNameShort, pstCurrOperatorName->aucOperatorNameShort, NAS_NVIM_MAX_OPER_SHORT_NAME_LEN);
                stNvimOperatorName.stOperatorPlmnId.ulMcc = pstCurrOperatorName->stOperatorPlmnId.ulMcc;
                stNvimOperatorName.stOperatorPlmnId.ulMnc = pstCurrOperatorName->stOperatorPlmnId.ulMnc;

                if (NV_OK != NV_Write(en_NV_Item_Network_Name_From_MM_Info,
                                      &stNvimOperatorName,
                                      sizeof(NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU)))
                {
                    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmEmmInfoInd_PreProc:Write NV fail.");
                }
            }
            else
            {
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmEmmInfoInd_PreProc: Operator name length out of range.");
            }

        }
    }
    if (NAS_MM_INFO_IE_NULL ==pstSendMsg->ucIeFlg)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSendMsg);
        return VOS_TRUE;
    }

    NAS_MMC_SndMsccMmInfo(pstSendMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstSendMsg);

    return VOS_TRUE;
}


/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-13, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmEmcPdpStatusNotify_PreProc
 ��������  : ��lmm���͵�ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY��Ϣ���д���
 �������  : ulEventType:��ϢID
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmEmcPdpStatusNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU *pstEmcPdpStatus = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enCurrNetRat    = NAS_MML_GetCurrNetRatType();
    pstEmcPdpStatus = (LMM_MMC_EMC_PDP_STATUS_NOTIFY_STRU *)pstMsg;

    /* �������PDP���Ӽ��� */
    if (VOS_TRUE == pstEmcPdpStatus->ucIsEmcPdpActive)
    {
        NAS_MML_SetEmcPdpStatusFlg(VOS_TRUE);
    }
    else
    {

        /* �������PDN���ӱ�־ */
        NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);

        /* �����ڲ��ҵ�ǰ��ģ��Lģʱ��LMM����EPLMN֪ͨ��ɾ��Forb Plmn */
        if ( (VOS_TRUE == NAS_MML_GetSimPresentStatus())
          && (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat) )
        {
            pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
            PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
            NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
            NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

            NAS_MMC_SndOmEquPlmn();
        }
    }

    return VOS_TRUE;
}
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-13, end */


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmLocalDetachInd_PreProc
 ��������  : �յ�MMCGMM_LOCAL_DETACH_IND��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_LOCAL_DETACH_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2014��05��04��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmLocalDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMCGMM_LOCAL_DETACH_IND_STRU                           *pstLocalDetachInd;
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32                ulLocalDetachType;

    pstLocalDetachInd = (MMCGMM_LOCAL_DETACH_IND_STRU *)pstMsg;

    if (NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI == pstLocalDetachInd->ulDetachCause)
    {
        ulLocalDetachType = MMC_LMM_GU_LOCAL_DET_IMSI_PAGING;

        /* ֪ͨL GU����imsi paging detach */
        NAS_MMC_SndLmmLocalDetachIndActionResultReq(ulLocalDetachType);
    }
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_GUT_LOCAL_DETACH);

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PreProc
 ��������  : �յ�RRMM_REL_INDָʾ��Ԥ����
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_REL_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
              VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : L65478
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��6��
    ��    ��   : w00167002
    �޸�����   : DTS2014120301093:NAS��BG�ѣ�W�ϱ�SUSPEND IND��NAS���棬���Ÿ���
                ��ռ��Դ������W��REL ALL��NAS�������SUSPEND IND��Ϣ����W����
                �����ϱ�RESUME IND��Ϣ�����¸�λ������W���ϱ�SUSPEND IND��Ϣ��NAS
                Ҳ�ᴥ��������λ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrMmRelInd = VOS_NULL_PTR;

    VOS_UINT32                          ulCacheEventType;

    pstRrMmRelInd = (RRMM_REL_IND_STRU*)pstMsg;

    if (RRC_RRC_CONN_STATUS_ABSENT == pstRrMmRelInd->ulRrcConnStatus)
    {
        /* ���RRC����״̬ */
        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
    }


    /* ��ǰ��UTRAN FDDģʽ�£��յ�WAS���쳣�ͷ����SUSPEND IND������Ϣ */
    if (VOS_TRUE == NAS_MMC_IsCurrentWcdmaMode())
    {
        if (RRC_REL_CAUSE_UTRAN_RELEASE != pstRrMmRelInd->ulRelCause)
        {
            /* ��������SUSPEND IND ��Ϣ���˺�W���ϱ�REUME IND��Ϣ */
            ulCacheEventType = NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND);
            NAS_MMC_ClearCacheMsg(ulCacheEventType);
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmRrConnInfoInd_PreProc
 ��������  : �յ�MMCMM_RR_CONN_INFO_INDָʾ��Ԥ����
 �������  : ulEventType:��Ϣ����
              pstMsg:MMCMM_RR_CONN_INFO_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : w00167002
    �޸�����   : DTS2015040707329:��L��CSFB ��������GU,���LAI�ı䣬��û�з���LAU/RAU,
                �ҽ��������������LTE�󴥷�COMBINED TA/LA UPDATING WITH IMSI ATTACH��
                MMC���յ�MM��RR��·֪ͨʱ��Ҳ֪ͨ��LMM�������жϵ�ǰ�������н��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{

#if (FEATURE_ON == FEATURE_LTE)
    MMCMM_RR_CONN_INFO_IND_STRU        *pstMmCsRrConnInfInd    = VOS_NULL_PTR;  /* ����ԭ������ָ��                         */
    VOS_UINT8                           ucCsServiceConnStatusFlg;               /* CS��ҵ�������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucCsRrConnStatusFlg;                    /* CS��RR�����Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */
    VOS_UINT8                           ucCsEmergencyConnStatusFlg;             /* CS�����ҵ�������Ƿ����,VOS_FALSE:������,VOS_TRUE:���� */

    pstMmCsRrConnInfInd                 = (MMCMM_RR_CONN_INFO_IND_STRU *)pstMsg;
    ucCsRrConnStatusFlg                 = VOS_FALSE;
    ucCsServiceConnStatusFlg            = NAS_MML_GetCsServiceConnStatusFlg();
    ucCsEmergencyConnStatusFlg          = VOS_FALSE;

    /* RR���Ӵ��ڱ�־ */
    if (MMC_MM_RR_CONN_ESTED            == pstMmCsRrConnInfInd->ulRrConnFlg)
    {
        ucCsRrConnStatusFlg             = VOS_TRUE;
    }

    /* ����ҵ����·���ڱ�־ */
    if ( (VOS_TRUE                      == NAS_MML_GetCsEmergencyServiceFlg())
      && (VOS_TRUE                      == ucCsServiceConnStatusFlg) )
    {
        ucCsEmergencyConnStatusFlg      = VOS_TRUE;
    }

    /* ֪ͨLMM��ǰCS�������״̬ */
    NAS_MMC_SndLmmCsConnStatusNotify(ucCsRrConnStatusFlg, ucCsEmergencyConnStatusFlg);

#endif

    /* ������״̬������ */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmCipherInfoInd_PreProc
 ��������  : �յ�RRMM_CIPHER_INFO_IND��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��02��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCipherInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CIPHER_INFO_IND_STRU          *pstCipherInfoInd;

    /* ��ʼ����Ϣ */
    pstCipherInfoInd = (RRMM_CIPHER_INFO_IND_STRU*)pstMsg;

    /* ֱ�ӽ��յ���WAS��Cipher��Ϣ�ϱ���MSCC */
    NAS_MMC_SndMsccWCipherInfoInd(pstCipherInfoInd);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmCipherInfoInd_PreProc
 ��������  : �յ�GMMMMC_CIPHER_INFO_IND��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��02��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmCipherInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_GMM_CIPHER_INFO_IND_STRU       *pstCipherInfoInd;

    /* ��ʼ����Ϣ */
    pstCipherInfoInd = (MMC_GMM_CIPHER_INFO_IND_STRU*)pstMsg;

    /* ֱ�ӽ��յ���WAS��Cipher��Ϣ�ϱ���MSCC */
    NAS_MMC_SndMsccGCipherInfoInd(pstCipherInfoInd);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PreProc
 ��������  : �յ�MMMMC_CS_REG_RESULT_IND��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:MMMMC_CS_REG_RESULT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��28��
    ��    ��   : w00167002
    �޸�����   : ��IMS�绰��SRVCC��G,û��ϵͳ��Ϣ�����·���TMSI����䣬���µ�ǰ��RAT
                 ΪGSM;���ж�RATû�иı䣬û�и�MSCC�ϱ�ϵͳ��Ϣ�����½���һֱ��ʾΪ4G.
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU                           *pstCsRegRslt = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8               enSpecPlmnSearchState;
#endif

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();
#endif

    /* �����л����̣�����û��ϵͳ��Ϣ�������⴦�� */
    if  ((MM_MMC_LU_RESULT_SUCCESS       == pstCsRegRslt->enLuResult)
      && (NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC == pstCsRegRslt->enRegFailCause))
    {
        (VOS_VOID)NAS_MMC_ProcCsRegFailCause419InterRatChangeSucc();

        return VOS_TRUE;
    }
    if  ((MM_MMC_LU_RESULT_SUCCESS       == pstCsRegRslt->enLuResult)
      && (NAS_MML_REG_FAIL_CAUSE_HO_WAIT_SYSINFO_TIMEOUT == pstCsRegRslt->enRegFailCause))
    {
        (VOS_VOID)NAS_MMC_ProcCsRegFailCause421HoWaitSysinfoTimeout();

        return VOS_TRUE;
    }
#if   (FEATURE_ON == FEATURE_LTE)
    if  ((NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL == pstCsRegRslt->enRegFailCause)
      && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING        == enSpecPlmnSearchState))
    {
        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRslt->enRegFailCause))
         && (VOS_FALSE == pstCsRegRslt->ucIsComBined))
        {
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = pstCsRegRslt->enRegFailCause;
            stActionRslt.ulAttemptCount = pstCsRegRslt->ulLuAttemptCnt;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
    }
#endif

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PreProc
 ��������  : �յ�GMMMMC_PS_REG_RESULT_IND��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:GMMMMC_PS_REG_RESULT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��04��11��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��2��
    ��    ��   : s46746
    �޸�����   : for CS/PS mode 1:����Disable/Enable����
  3.��    ��   : 2014��12��19��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI HO������Ԥ�����������⴦��
  4.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDisablteRoamFlg;

    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
#endif
    GMMMMC_PS_REG_RESULT_IND_STRU                          *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt         = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �����л����̣�����û��ϵͳ��Ϣ�������⴦�� */
    if ((GMM_MMC_ACTION_RESULT_SUCCESS  == pstPsRegRslt->enActionResult)
     && (NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC == pstPsRegRslt->enRegFailCause))
    {
        (VOS_VOID)NAS_MMC_ProcPsRegFailCause419InterRatChangeSucc();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    enLUeMode            = NAS_MML_GetLteUeOperationMode();

    /* ����PS detachҲ�ᷢ�͸���Ϣ����������PS detach������Ҫ����Enable�Ĵ��� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    if ((VOS_TRUE == NAS_MMC_IsNeedEnableLte_AttachPs())
     && (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode))
    {
        ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

       /* ����disable LTE������� */
       NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return VOS_FALSE;
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
  1.��    ��   : 2012��04��21��
    ��    ��   : L00171473
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��16��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafOmMaintainInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, begin */
    MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU   *pstOmMaintainInfoInd;

    pstOmMaintainInfoInd = (MSCC_MMC_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, end */

    /* ����SDT���ӱ�־ */
    NAS_MML_SetOmConnectFlg(pstOmMaintainInfoInd->ucOmConnectFlg);

    /* ����PC�ط�ʹ�ܱ�־ */
    NAS_MML_SetOmPcRecurEnableFlg(pstOmMaintainInfoInd->ucOmPcRecurEnableFlg);

    /* �������״̬������ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserReselReqUnNormalSrv_PreProc
 ��������  : ����������״̬�յ��û���ѡ�Ĵ���
 �������  : pUserReselReq �û���ѡ��Ϣ
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��9��22��
   ��    ��   : z00161729
   �޸�����   : DTS2012091403828:����������״̬����ģʽ���ֶ���Ϊ�Զ�δ���״�����HPLMN��ʱ����־Ϊtrue�����º�������hplmn��ʱʱ����Ϊ2min
 3.��    ��   : 2013��4��7��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
 4.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
 5.��    ��   :2013��8��21��
   ��    ��   :z00161729
   �޸�����   :DTS2013081607507:�������������к�̨����·�at+cops=0��mmc�жϷ���������ͣ��ϵ�ǰ���������������¿����ٶ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcUserReselReqUnNormalSrv_PreProc(
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU  *pUserReselReq
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    VOS_UINT32                                              ulCsServiceExist;
    VOS_UINT32                                              ulPsServiceExist;

    VOS_UINT32                                              ulIsNeedPlmnSearch;

    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    /* �жϵ�ǰ�Ƿ���CSҵ����� */
    ulCsServiceExist         = NAS_MML_GetCsServiceExistFlg();

    /* �жϵ�ǰ�Ƿ���PSҵ����� */
    ulPsServiceExist         = NAS_MML_GetPsServiceExistFlg();

    /* �ֶ����Զ�ģʽ��Ҫ���״�����hplmn��ʱ����־��Ϊtrue */
    if ( NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ���綨�ƣ���ǿ��Hplmn�������Դ�ʱ���Զ�ģʽ�޸�Ϊ�ֶ�ģʽ��
           ֹͣHPLMN��ʱ�����û��ٴν��ֶ�ģʽ�޸�Ϊ�Զ�ģʽ������HPLMN������������
           ����HPLMN��ʱ������Ϊ�����״�����HPLMN��ʱ��*/
        if (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg)
        {
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }
        else
        {
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_TRUE);
        }
    }

    /* ��ҵ��ʱ������Ҫ�������� */
    if ( (VOS_FALSE == ulCsServiceExist)
      && (VOS_FALSE == ulPsServiceExist))
    {
        /* ��״̬���ﴥ������ */
        /* ��ǰΪ�Զ�ѡ��ģʽ��������������MSCC�ظ������ɹ� */
        ulIsNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_UserReselReq();

        if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
         && (VOS_FALSE == ulIsNeedPlmnSearch))
        {
            NAS_MMC_SndMsccPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ��ǰΪ�Զ�ѡ��ģʽ */
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��¼�������� */

        if (VOS_TRUE == NAS_MML_GetUserAutoReselActiveFlg())
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED;
        }
    }
    else
    {
        /* ����ѡ��ģʽ */
        NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_AUTO);

        /* ����ǰ��ѡģʽд��NVIM�� */
        NAS_MMC_WritePlmnSelectionModeNvim();

        /* ģʽ�ı����STK����¼� */
        if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
        {
            NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_AUTO);
        }

        /* ��¼�������� */

        if (VOS_TRUE == NAS_MML_GetUserAutoReselActiveFlg())
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_MANUAL_CHANGE_AUTO_MODE;
        }

    }


    /* ����������Ϣ */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, enPlmnSearchScene);

    /* ��MSCC�ظ������ɹ� */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
    NAS_MMC_SndMsccPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */


    /* ��ҵ��ʱ�������������ٽ���״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserReselReqNormalServiceFun
 ��������  : ��������״̬ʱ�յ��û���ѡ�Ĵ���
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��5��5��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserReselReqNormalServiceFun(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulCampOnHplmnFlag;
    VOS_UINT32                          ulCsServiceExist;

    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��HPLMN��ͬ��������פ��HPLMN�� */
    ulCampOnHplmnFlag = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    /* �жϵ�ǰ�Ƿ���CSҵ����� */
    ulCsServiceExist         = NAS_MML_GetCsServiceExistFlg();

    if ((VOS_FALSE == NAS_MML_GetUserAutoReselActiveFlg())
     || (VOS_TRUE  == ulCampOnHplmnFlag))
    {
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
        NAS_MMC_SndMsccPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */

        return VOS_TRUE;
    }
    else
    {
        if (VOS_TRUE == ulCsServiceExist)
        {
            /* ������Ϣ���ظ��ɹ� */
            NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE,
                        NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL);

            NAS_MMC_SndMsccPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);

            return VOS_TRUE;
        }
        else
        {
            /* ��״̬���ﴥ������ */
            return VOS_FALSE;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserReselReqNormalService_PreProc
 ��������  : ��������״̬�յ��û���ѡ�Ĵ���
 �������  : pUserReselReq �û���ѡ��Ϣ
 �������  : VOS_UINT32
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 3.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
 4.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���
 5.��    ��   : 2014��5��5��
   ��    ��   : b00269685
   �޸�����   : ������CSҵ��ʱ������������Ϣ��ֱ�ӻظ��ɹ�
 6.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_ProcUserReselReqNormalService_PreProc(
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU      *pUserReselReq
)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg      = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();



    /* ��ǰ�Ѿ����Զ�ѡ��ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return NAS_MMC_ProcUserReselReqNormalServiceFun();
    }

    /* ����ѡ��ģʽ */
    NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_AUTO);

    /* ����ǰ��ѡģʽд��NVIM�� */
    NAS_MMC_WritePlmnSelectionModeNvim();

    /* ����ģʽ�仯�ϱ�USIM */
    if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
    {
        NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_AUTO);
    }

    /* �ֶ�ģʽ�޸�Ϊ�Զ�ģʽ����ǰ���������������£���Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
    if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
    {
        /* ���綨�ƣ���ǿ��Hplmn�������Դ�ʱ���Զ�ģʽ�޸�Ϊ�ֶ�ģʽ��
           ֹͣHPLMN��ʱ�����û��ٴν��ֶ�ģʽ�޸�Ϊ�Զ�ģʽ������HPLMN������������
           ����HPLMN��ʱ������Ϊ�����״�����HPLMN��ʱ��*/
        if (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg)
        {
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }
        else
        {
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_TRUE);
        }

        /* ������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


        /* HPLMN TIMER�����¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* ������ʱ�� */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }


    return NAS_MMC_ProcUserReselReqNormalServiceFun();

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcScanCtrl_PreProc
 ��������  : �������ƹ��ܵĴ���
 �������  : VOS_UINT16                          usEfLen
             VOS_UINT8                          *pucEf
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��11��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��3��
    ��    ��   : z40661
    �޸�����   : DTS2012081801644,SIM����HPLMN����Ϊ0ʱ,�����������������Դ�ʱδ���������Զ�ʱ��
  3.��    ��   : 2012��8��28��
    ��    ��   : w00167002
    �޸�����   : ��ǰUTRAN����ģʽTDDʱ��������HPLMN TIMER
  4.��    ��   : 2013��12��20��
    ��    ��   : w00167002
    �޸�����   : DTS2013112917981:guNASɾ����TDģʽ�²��ܽ���bg�ѵ�����
  5.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���
  6.��    ��   : 2014��10��27��
    ��    ��   : b00269685
    �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcScanCtrl_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    VOS_UINT32                          ulHplmnTimerLen;

    /* �����������NVδ�򿪣�ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MML_GetScanCtrlEnableFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcScanCtrl_PreProc:ERROR: Scan Ctrl NV is deactive.");
        return;
    }

    /* �ļ����Ȳ���ȷ��ֱ�ӷ��� */
    if (NAS_MML_HPLMN_PERI_FILE_LEN != usEfLen)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcScanCtrl_PreProc:ERROR: File length is invalid.");
        return;
    }


    /* ʱ������Ԥ������ˢ�£�ֱ�ӻ�ȡ */
    ulHplmnTimerLen = NAS_MMC_GetHplmnTimerLen();


    /* �����ǰ�����ȼ�������ʱ���������У�����ֹͣ */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        /* ֹͣ��ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);

        /* ��ǰUTRAN����ģʽ��TDD,��ʱ����0���������� */
        if (0 != ulHplmnTimerLen)
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, ulHplmnTimerLen);
        }
    }
    else
    {
        /* ������״̬���������У�ֱ�ӷ��� */
        if (NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
        {
            return;
        }

        /* �����Գ��Ը����ȼ������Ķ�ʱ���������У�ˢ�º��ʱ��Ϊ0����Ҫֹͣ */
        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
        {
            if (0 == ulHplmnTimerLen)
            {
                NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH);
            }

            return;
        }

        /* ����NAS_MMC_IsNeedStartHPlmnTimer�ж��Ƿ���Ҫ������ʱ�� */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* ������ʱ�� */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCmServiceRejectInd_PreProc
 ��������  : �յ�CM_SERVICE_REJECT_IND��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
              pstMsg:CM_SERVICE_REJECT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
              VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  3.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind����û���ϱ�^rejinfo
  4.��    ��   : 2014��4��24��
    ��    ��   : w00242748
    �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                 ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ
  5.��    ��   : 2014��4��30��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  6.��    ��   : 2015��1��7��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI�޸�
  7.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  8.��    ��   :2015��3��13��
    ��    ��   :n00269697
    �޸�����   :CHR �Ż���Ŀ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCmServiceRejectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;
#endif
    pstRcvMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

    ulState   = NAS_MMC_GetFsmTopState();

    /* BG��״̬��ϵͳ��Ϣ�����ӳٷ��ͣ���Ҫ��ע��״̬�ͷ���״̬֮ǰ֪ͨMMA */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH                         == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND       == ulState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  == ulState)))
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_CM_SERVICE_REJ);

    NAS_MMC_SndMsccServRejRsltInd(NAS_MSCC_PIF_SRVDOMAIN_CS,
                                (VOS_UINT16) pstRcvMsg->ulCause);

    if ( NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstRcvMsg->ulCause )
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_CmServiceRejErrRecord(pstRcvMsg->ulCause, pstRcvMsg->ulServiceStatus);
#endif

    if ( (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstRcvMsg->ulCause)
      && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR != pstRcvMsg->ulCause) )
    {
        return VOS_TRUE;
    }


#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_CmServiceRejectInd((VOS_UINT16)pstRcvMsg->ulCause))
    {
        ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

#endif

    return VOS_FALSE;
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCustomizedForbLaTimerExpired_PreProc
 ��������  : �յ�ɾ����ֹLA�б�ʱ����ʱ��ϢԤ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : g00322017
    �޸�����   : �¼�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCustomizedForbLaTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_PreProc");

    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();
    enFsmId                             = NAS_MMC_GetCurrFsmId();

    /* ON PLMN״̬��ʱ��Ҫɾ��CUSTOMIZED FORB LA����Ϊ��ON PLMN��״̬������ʱ����ʹ�ã�
        ����״̬�����������ɾ��  */
    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
     && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod))
    {
        /* ��ֹLA�б��б仯��֪ͨ����� */
        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    /* ������ʱ�� */
    NAS_MML_StartCustomizedForbLaTimer();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvForbidLaTimerExpired_PreProc
 ��������  : �յ�forbidden LA��ʱ����ʱ��ϢԤ����,
             ȷ����timer��ʱ�� ɾ��forbid LA�б�
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : g00322017
    �޸�����   : �¼�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvForbidLaTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    enFsmId             = NAS_MMC_GetCurrFsmId();

    /* ON PLMN״̬��ʱ��Ҫɾ��FORB LA����Ϊ��ON PLMN��״̬������ʱ����ʹ�ã�
        ����״̬�����������ɾ��  */
    if (   (NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
        && (NAS_MMC_FSM_L1_MAIN == enFsmId)   )
    {
        return VOS_FALSE;
    }
    pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();
    pstForbidPlmnInfo->ucForbRegLaNum   = 0;
    pstForbidPlmnInfo->ucForbRoamLaNum   = 0;

    NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPeriodDeleteDisabledPlmnWithRatExpired_PreProc
 ��������  : �յ�����ɾ����ֹ���뼼�������б�ʱ����ʱ��ϢԤ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  2.��    ��   : 2015��4��23��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvPeriodDeleteDisabledPlmnWithRatExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulIsNeedSndEplmn;
    VOS_UINT32                                              ulIsExistNeedDeleteDisabledPlmn;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurFsmId;

    ulIsExistNeedDeleteDisabledPlmn = VOS_FALSE;
    ulIsNeedSndEplmn                = VOS_FALSE;
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(stSndEquPlmnInfo));

    ulIsExistNeedDeleteDisabledPlmn = NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList();

    /* ��ǰ״̬��ID */
    enCurFsmId = NAS_MMC_GetCurrFsmId();

    if ((NAS_MMC_L1_STA_ON_PLMN != NAS_MMC_GetFsmTopState())
     || (NAS_MMC_FSM_L1_MAIN != enCurFsmId))
    {
        return VOS_TRUE;
    }

    /* ��L1 MAIN,on plmn��Ҫ����֪ͨ��ǰģ��Чplmn��Ϣ */
    ulIsNeedSndEplmn = NAS_MMC_IsNeedSndEplmn();

    if ((VOS_TRUE == ulIsExistNeedDeleteDisabledPlmn)
     && (VOS_TRUE == ulIsNeedSndEplmn))
    {
#if   (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
            PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
            NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
            NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
            NAS_MMC_SndOmEquPlmn();

            return VOS_TRUE;
        }
#endif

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));

        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();
        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAbortInd_PreProc
 ��������  : �յ�MM_ABORT_IND��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
              pstMsg:MM_ABORT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
              VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  3.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmAbortInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMMMC_ABORT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT32              ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

    pstRcvMsg = (MMMMC_ABORT_IND_STRU*)pstMsg;

    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_MmAbortInd(pstRcvMsg->enAbortCause))
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmT3402LenNotify_PreProc
 ��������  : �յ�֪ͨT3402��ʱ��ʱ����Ϣ��Ԥ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmT3402LenNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_T3402_LEN_NOTIFY_STRU      *pstT3402LenNotifyMsg = VOS_NULL_PTR;

    pstT3402LenNotifyMsg = (LMM_MMC_T3402_LEN_NOTIFY_STRU*)pstMsg;

    /* ����T3402��ʱ��ʱ�� */
    NAS_MML_SetT3402Len(pstT3402LenNotifyMsg->ulT3402Len);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmEutranNotAllowNotify_PreProc
 ��������  : �յ�ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY��Ϣ��Ԥ����
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : w00167002
    �޸�����   : DTS2015032709270:������������LTE��ATTACH/TAU����#15��,LNAS��
                 �б�ǰ�Ƿ�֧��4G�������ҪguNAS��DISABLE LTE. �����Ͳ���ä�ض���
                 ��LTE���硣
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmEutranNotAllowNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU                   *pstEutanNotAllowNotifyMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT32                                              i;

    pstEutanNotAllowNotifyMsg = (LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU*)pstMsg;

    /* ����ǰDISABLE��PLMN�б�����ֹ���뼼���б����� */
    if (pstEutanNotAllowNotifyMsg->ucPlmnNum > MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM)
    {
        pstEutanNotAllowNotifyMsg->ucPlmnNum = MMC_LMM_MAX_EUTRAN_NOT_ALLOW_PLMN_NUM;
    }

    /* ��ǰ���뼼��ΪLTE,PLMN IDΪ��Чֵ */
    stPlmnWithRat.enRat = NAS_MML_NET_RAT_TYPE_LTE;
    stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    for (i = 0; i < pstEutanNotAllowNotifyMsg->ucPlmnNum; i++)
    {
        /* ��LMM��PLMNת��ΪGU���͵�PLMN */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstEutanNotAllowNotifyMsg->astPlmnIdList[i], &stPlmnWithRat.stPlmnId);


        /* ��ת�����PLMN���뵽��ֹ���뼼���б��� */
        NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                      NAS_MML_ONE_SECOND_TIME_SLICES * pstEutanNotAllowNotifyMsg->ulTimerLen,
                                                      MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW);
    }

    /* ��ǰPLMN 4G��֧��,�����ǰû��֪ͨ�����DISABLE,����Ҫ֪ͨ�����DISABLE LTE */
    if (VOS_TRUE == NAS_MMC_IsEutranNotAllowedNeedDisableL())
    {
        /* ����disable LTE�������,����ģ��֪ͨDISABLE LTE */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        /* ��ǰLTE������ģ��֪ͨASȥDISABLE LTE,����ȹ���LTE����֪ͨ */
        if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW);

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
        }

        NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW);

        /* ����ENABLE ��ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, pstEutanNotAllowNotifyMsg->ulTimerLen * NAS_MML_ONE_THOUSAND_MILLISECOND);
    }

    /* ����FORBIDEN PLMN�����Ϣ��LOG��ӡ */
    NAS_MMC_LogForbiddenPlmnRelatedInfo();

    /* ������ϣ�����������״̬������ */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvEnableLteExpired_PreProc
 ��������  : �յ�TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER��ʱ��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:MM_ABORT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  3.��    ��   : 2015��4��21��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvEnableLteExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    VOS_UINT32              ulDisablteRoamFlg;

    NAS_MML_PLMN_RAT_PRIO_STRU          *pstPrioRatList = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32           enCurFsmId;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();


    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_EnableLteTimerExp())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            /* enable lte��Ҫ���������ҵ�ǰsyscfg����LTE���뼼�����ȼ���� */
            if ((VOS_TRUE == NAS_MML_GetEnableLteTrigPlmnSearchFlag())
             && (NAS_MML_NET_RAT_TYPE_LTE == pstPrioRatList->aucRatPrio[0]))
            {
                /* �������csҵ�����csҵ���������enable lte���������psҵ�����ӣ�
                   MMC��Ҫ�����ͷ����ӣ������ͷź���enable lte */
                if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
                {
                    NAS_MMC_SetEnableLteTimerExpireFlag(VOS_TRUE);
                    return VOS_TRUE;
                }

                /* ��ǰ״̬��ID */
                enCurFsmId = NAS_MMC_GetCurrFsmId();

                if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
                 && (NAS_MMC_FSM_L1_MAIN == enCurFsmId))
                {
                    /* ����ѡ��״̬�����������ȡ��ע�� */
                    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

                    /* enable lte����Ҫ���������������ڲ�������Ϣ */
                    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH,VOS_NULL_PTR, 0);
                }
            }

            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);

            /* 24301_CR1623R2_(Rel-11)_C1-130770 rev of C1-130593 rev of C1-130263 24301 guard time to re-enable E-UTRA caps
            ��Ӧ24301 4.5�½�
            As an implementation option, the UE may start a timer for enabling E-UTRA  when the UE's attach attempt
            counter or tracking area updating attempt counter reaches 5 and the UE disables E-UTRA capability for cases
            described in subclauses 5.5.1.3.4.3, 5.5.1.3.6, 5.5.3.3.4.3 and 5.5.3.3.6. On expiry of this timer and if T3346 is not running then:
            -   if the UE is in Iu mode or A/Gb mode and is in idle mode as specified in 3GPP TS 24.008 [13] on expiry of the timer, the UE should enable the E-UTRA capability;
            -   if the UE is in Iu mode or A/Gb mode and an RR connection exists, the UE shall delay enabling E-UTRA capability  until the RR connection is released; and
            -   if the UE is in Iu mode and a PS signalling connection exists but  no RR connection exists, the UE may abort the PS signalling connection before enabling E-UTRA capability.
            �������ps����������GMM����ע�����̣�����psҵ�����ʱ�������ͷ�����,��CR����Э��汾���� */
            if (VOS_TRUE == NAS_MMC_IsNeedRelPsConnEnableLteTimerExpired())
            {
                NAS_MMC_SndGmmRelReq();
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_BUTT);
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsfbAbortInd_PreProc
 ��������  : ����csfb abort ind ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������

 �޸���ʷ      :
 1.��    ��   : 2015��5��7��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsfbAbortInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    /* �жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬�� �������Ϣ�Ļ��� */
    ulRet = NAS_MMC_ProcMsgPrio(ulEventType, pstMsg);

    /* ��Ҫ��ϵ�ǰ״̬���������Ϣ�Ļ���,���ʾԤ������� */
    if (VOS_TRUE == ulRet)
    {
        return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCLAssociatedInfoNtf_PreProc
 ��������  : ����ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : y00346957
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU                   *pstCLAssociatedInfoNtfMsg;
    NAS_MMC_CL_ASSOCIATED_INFO_NTF_STRU                    *pstCLAssociatedInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrFsmId;
    VOS_UINT32                                              ulState;

    pstCLAssociatedInfoNtfMsg  = (MSCC_MMC_CL_ASSOCIATED_INFO_NTF_STRU *)pstMsg;

    pstCLAssociatedInfo        = NAS_MMC_GetCLAssociatedInfoAddr();
    enCurrFsmId                = NAS_MMC_GetCurrFsmId();
    ulState                    = NAS_MMC_GetFsmTopState();

    /* �����1x���ȼ��ߵ�lte��sys pri class */
    pstCLAssociatedInfo->ucAllowSrchLteFlg      = pstCLAssociatedInfoNtfMsg->ucAllowSrchLteFlg;
    pstCLAssociatedInfo->enLteSysPriClass       = pstCLAssociatedInfoNtfMsg->enLteSysPriClass;

    /* ���ݵ�ǰ״̬����״̬�ж��Ƿ���Ҫ��״̬������ */
    /* �ڵ�plmn����������ߵ�ע�����������״̬������ */
    if ((NAS_MMC_FSM_PLMN_SELECTION == enCurrFsmId)
     && ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulState)
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND         == ulState)))
    {
        return VOS_FALSE;
    }

    /* ��������ʱ���ڵ�����������ߵȿ�������������ߵ�ע�����������״̬������ */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == enCurrFsmId)
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF   == ulState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF == ulState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND              == ulState)))
    {
        return VOS_FALSE;
    }

    /* on plmnפ��̬�������״̬������ */
    if ((NAS_MMC_FSM_L1_MAIN == enCurrFsmId)
     && (NAS_MMC_L1_STA_ON_PLMN == ulState))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCLInterSysStartNtf_PreProc
 ��������  : ����ID_MSCC_MMC_CL_INTERSYS_START_NTF����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : y00346957
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccCLInterSysStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_CL_INTERSYS_START_NTF_STRU                    *pstInterSysStart = VOS_NULL_PTR;
    MMC_LMM_SYS_CHNG_TYPE_ENUM_UINT32                       enSuspendCause;

    pstInterSysStart = (MSCC_MMC_CL_INTERSYS_START_NTF_STRU *)pstMsg;

    enSuspendCause = NAS_MMC_ConvertMsccInterSysCauseToMmcFormat(pstInterSysStart->enInterSysCause);

    NAS_MMC_SndLmmCLInterSysStartNtf(enSuspendCause);

    return VOS_TRUE;
}
#endif
#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPlmnSearchGUSearchState_UserReselReq
 ��������  : GUģʽ������״̬�����ж��Ƿ���Ҫ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedPlmnSearchGUSearchState_UserReselReq(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    VOS_UINT32                          ulUserAutoReselActiveFlg,
    VOS_UINT32                          ulIsCurrSearchingPlmnHplmn,
    VOS_UINT32                          ulCurrState
)
{
    /* ����״̬�������У���GU�����͹���״̬ʱ��Ҫ�жϵ�ǰ���������������Ƿ�Ϊhplmn��nv 9705��ʱ�����������hplmn�������� */
    if ( (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
      && (VOS_TRUE == ulUserAutoReselActiveFlg)
      && (VOS_TRUE == ulIsCurrSearchingPlmnHplmn)
      && ((NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || (NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPlmnSearch_UserReselReq
 ��������  : �ж�at+cops=0�Ƿ���Ҫ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ
             VOS_TRUE:��Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��12��11��
    ��    ��   : z00234330
    �޸�����   : dts2013121106833,��Ȧ���Ӷ�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_UserReselReq(VOS_VOID)
{
    VOS_UINT32                                              ulCurrState;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsCurrSearchingPlmnHplmn;
    VOS_UINT32                                              ulUserAutoReselActiveFlg;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    VOS_UINT32                                              ulIsUsimStatusValid;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                                   *pstCsPsMode1ReCampLtePlmn;
    VOS_UINT32                                              ulIsReCampLtePlmnHplmn;
#endif

    enFsmId                    = NAS_MMC_GetCurrFsmId();
    ulCurrState                = NAS_MMC_GetFsmTopState();
    ulUserAutoReselActiveFlg   = NAS_MML_GetUserAutoReselActiveFlg();
    pstCurrSearchingPlmn       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    ulIsCurrSearchingPlmnHplmn = NAS_MML_ComparePlmnIdWithHplmn(&pstCurrSearchingPlmn->stPlmnId);
    ulIsUsimStatusValid        = NAS_MML_IsUsimStausValid();

#if (FEATURE_ON == FEATURE_LTE)
    pstCsPsMode1ReCampLtePlmn  = NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection();
    ulIsReCampLtePlmnHplmn     = NAS_MML_ComparePlmnIdWithHplmn(pstCsPsMode1ReCampLtePlmn);
#endif


    /* ����Ѿ����Զ�ģʽ��������״̬�����ڲ��б���״̬���򱳾���״̬�������ٴ�ϵ�ǰ״̬������������֧���û���ѡ���Ƶ�NV��9074�رգ�ֱ�ӻظ�ok */
    if ((VOS_FALSE == ulUserAutoReselActiveFlg)
     && ((NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId)
      || (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId)))
    {
        return VOS_FALSE;
    }



    if ( VOS_FALSE == NAS_MMC_IsNeedPlmnSearchGUSearchState_UserReselReq(
                    enFsmId,ulUserAutoReselActiveFlg,ulIsCurrSearchingPlmnHplmn,ulCurrState) )
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ����״̬�������У���L�����͹���״̬ʱ��Ҫ�жϵ�ǰ���������������Ƿ�Ϊhplmn��nv 9705��ʱ�����������hplmn�������� */
    if ((NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
     && (VOS_TRUE == ulUserAutoReselActiveFlg))
    {
        if ((VOS_TRUE == ulIsCurrSearchingPlmnHplmn)
         && ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
          || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)))
        {
            return VOS_FALSE;
        }

        if ((VOS_TRUE ==ulIsReCampLtePlmnHplmn)
         && (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE == ulCurrState))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }
#endif


    /* anycell״̬�������������ǰ����Ч�����������·���anycell�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == enFsmId)
     && (VOS_FALSE == ulIsUsimStatusValid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPlmnSearch_Oos
 ��������  : ���RRMM_LIMIT_SERVICE_CAMP_IND�Ƿ񴥷������Ƿ���Ҫ��״̬������
 �������  : pstRrmmLimitCampOnMsg  - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ
             VOS_TRUE:��Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��27��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_Oos(
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg
)
{
    /* ����RRC����,��ǰ�Ĳ���Ϊstart,�����ϱ���PLMN������Ϊ0ʱ,��Ҫ�������� */

    if (RRC_RRC_CONN_STATUS_PRESENT != pstRrmmLimitCampOnMsg->enRrcConnStatus)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    if ((0 == pstRrmmLimitCampOnMsg->stPlmnIdList.ulHighPlmnNum)
     && (0 == pstRrmmLimitCampOnMsg->stPlmnIdList.ulLowPlmnNum))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAcpuOmErrLogRptReq_PreProc
 ��������  : �յ�ID_OM_ERROR_LOG_REPORT_REQ��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_OM_ERROR_LOG_REPORT_REQ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAcpuOmErrLogRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_CHAR                           *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                          ulBufUseLen;
    VOS_UINT32                          ulRealLen;
    VOS_UINT32                          ulTotalLen;
    NAS_ERR_LOG_MNTN_EVENT_STRU         stNasErrLogMntnEvent;

    /* RING BUFFER���ݳ��� */
    ulBufUseLen = NAS_MML_GetErrLogRingBufUseBytes();
    ulTotalLen = ulBufUseLen + sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU);

    pbuffer = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_MMC_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        return VOS_TRUE;
    }

    PS_MEM_SET(pbuffer, 0, ulTotalLen);

    /* ��ȡRING BUFFER������ */
    ulRealLen = NAS_MML_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_MMC_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        PS_MEM_FREE(WUEPS_PID_MMC, pbuffer);
        return VOS_TRUE;
    }

    /* �����������������Ϣ׷����RingBuf���� */
    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stNasErrLogMntnEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_MNTN,
                                      NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MNTN),
                                      VOS_GetSlice(),
                                      (sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNasErrLogMntnEvent.ulCount = NAS_MML_GetErrlogOverflowCnt();

    PS_MEM_CPY(pbuffer + ulBufUseLen, &stNasErrLogMntnEvent, sizeof(stNasErrLogMntnEvent));

    /* ��ȡ���˺���Ҫ��RINGBUFFER��� */
    NAS_MML_CleanErrLogRingBuf();

    /* ����������� */
    NAS_MML_SetErrlogOverflowCnt(0);

    /* ��ά�ɲ�BUF����Ĺ��� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MNTN,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stNasErrLogMntnEvent,
                           sizeof(stNasErrLogMntnEvent));

    /* ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM */
    NAS_MMC_SndAcpuOmErrLogRptCnf(pbuffer, ulTotalLen);

    PS_MEM_FREE(WUEPS_PID_MMC, pbuffer);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAcpuOmErrLogCtrlInd_PreProc
 ��������  : �յ�ID_OM_ERR_LOG_CTRL_IND��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_OM_ERR_LOG_CTRL_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAcpuOmErrLogCtrlInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    OM_ERROR_LOG_CTRL_IND_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_ERROR_LOG_CTRL_IND_STRU*)pstMsg;

    /* ����ERRLOG���Ʊ�ʶ */
    if ((VOS_FALSE == pstRcvMsg->ucAlmStatus)
     || (VOS_TRUE  == pstRcvMsg->ucAlmStatus))
    {
        NAS_MML_SetErrlogCtrlFlag(pstRcvMsg->ucAlmStatus);
    }

    if ((pstRcvMsg->ucAlmLevel >= NAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstRcvMsg->ucAlmLevel <= NAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_MML_SetErrlogAlmLevel(pstRcvMsg->ucAlmLevel);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAcpuOmFtmCtrlInd_PreProc
 ��������  : �յ�ID_OM_FTM_CTRL_IND��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_OM_FTM_CTRL_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAcpuOmFtmCtrlInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    OM_FTM_CTRL_IND_STRU               *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_FTM_CTRL_IND_STRU*)pstMsg;

    /* ���¹��̲˵����Ʊ�ʶ */
    if ((VOS_FALSE == pstRcvMsg->ucActionFlag)
     || (VOS_TRUE  == pstRcvMsg->ucActionFlag))
    {
        NAS_MML_SetFtmCtrlFlag(pstRcvMsg->ucActionFlag);
    }

    /* ����ǹر�ָʾ��ʲô�������� */
    if (VOS_FALSE == pstRcvMsg->ucActionFlag)
    {
        return VOS_TRUE;
    }

    /* �յ��򿪹��̲˵���ָʾ����Ҫ����ǰ��TMSI/PTMSI�ϱ����ϲ�Ӧ�� */
    NAS_MMC_SndAcpuOmCurTmsi();
    NAS_MMC_SndAcpuOmCurPtmsi();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMtaGetNasChrInfoReq_PreProc
 ��������  : �յ�MTAģ���ȡNAS��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��13��
   ��    ��   : g00322017
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMtaGetNasChrInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndMtaGetNasChrInfoCnf();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccEOPlmnSetReq_PreProc
 ��������  : Ԥ�����յ�EOPLMN��Ϣ�����Ϣ���浽NV��
 �������  : ulEventType:��Ϣ����
             pstMsg:����plmn����Ϣ�ṹ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��26��
   ��    ��   : s00190137
   �޸�����   : ��ӷ�����ƣ����֧������256��OPLMN,���������������50��OPLMN
 3.��    ��   : 2014��2��19��
   ��    ��   : s00217060
   �޸�����   : coverity����
 4.��    ��   : 2014��3��28��
   ��    ��   : w00242748
   �޸�����   : DTS2014032803821:EOPLMN����֮���ٽ��в�ѯ��ʾʱ�����ֶ����Ч��
                �ַ���
5.��    ��   : 2014��6��17��
  ��    ��   : z00234330
  �޸�����   : PCINT����

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccEOPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulLen;
    VOS_UINT16                                              usNewOPlmnNum;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    VOS_UINT32                                              ucMmcTopState;
    /* Added by s00217060 for coverity����, 2014-02-17, begin */
    VOS_UINT32                                              ulOffset;
    VOS_UINT32                                              ulOplmnNum;
    /* Added by s00217060 for coverity����, 2014-02-17, end */
    MSCC_MMC_EOPLMN_SET_REQ_STRU                            *pstEOPlmnSetMsg     = VOS_NULL_PTR;
    NAS_MML_USER_CFG_OPLMN_INFO_STRU                       *pstUserCfgOPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU                *pstNvimCfgOPlmnInfo = VOS_NULL_PTR;

    pstEOPlmnSetMsg = (MSCC_MMC_EOPLMN_SET_REQ_STRU *)pstMsg;

    ulLen           = 0;
    usNewOPlmnNum   = 0;

    /*д��NV*/
    pstNvimCfgOPlmnInfo = (NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_MMC,
                                                      sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));

    if (VOS_NULL_PTR == pstNvimCfgOPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccEOPlmnSetReq_PreProc():ERROR: Memory Alloc Error");
        NAS_MMC_SndMsccEOPlmnSetCnf(VOS_ERR);
        return VOS_TRUE;
    }

    PS_MEM_SET(pstNvimCfgOPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));

    /* ��NV��en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST��ʧ�ܣ�ֱ�ӷ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST, &ulLen);

    if (NV_OK != NV_Read(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST,
                         pstNvimCfgOPlmnInfo, ulLen))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccEOPlmnSetReq_PreProc():WARNING: read en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST Error");
        /* �����Ϣ */
        NAS_MMC_SndMsccEOPlmnSetCnf(VOS_ERR);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return VOS_TRUE;
    }

    /* ���õ�1������(index =0 )ʱ����Ҫ�����NV�оɵ�OPLMN���� */
    if (0 == pstEOPlmnSetMsg->ucIndex)
    {
        pstNvimCfgOPlmnInfo->usOplmnListNum = 0;
        PS_MEM_SET(pstNvimCfgOPlmnInfo->aucOPlmnList, 0x00, NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN);
    }

    /* �����µķ�������ʱ����Ҫ���ǰ��ķ��������Ƿ����óɹ���ֻ֧���������� */
    /* Modified by z00234330 for PCLINT����, 2014-06-16, begin */
    if ((NAS_MML_MAX_GROUP_CFG_OPLMN_NUM * pstEOPlmnSetMsg->ucIndex) != pstNvimCfgOPlmnInfo->usOplmnListNum )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccEOPlmnSetReq_PreProc():WARNING: check old index data Error");
        /* �����Ϣ */
        NAS_MMC_SndMsccEOPlmnSetCnf(VOS_ERR);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return VOS_TRUE;
    }
    /* Modified by z00234330 for PCLINT����, 2014-06-16, end */

    /* ���ú��µ�OPLMN�������ܴ���256�� */
    usNewOPlmnNum = pstNvimCfgOPlmnInfo->usOplmnListNum + (VOS_UINT16)pstEOPlmnSetMsg->ucOPlmnCount;
    if (NAS_MML_MAX_USER_CFG_OPLMN_NUM < usNewOPlmnNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccEOPlmnSetReq_PreProc():WARNING: check max oplmn num Error");
        /* �����Ϣ */
        NAS_MMC_SndMsccEOPlmnSetCnf(VOS_ERR);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return VOS_TRUE;
    }


    PS_MEM_CPY(pstNvimCfgOPlmnInfo->aucVersion,
                pstEOPlmnSetMsg->aucVersion,
                NAS_MML_MAX_USER_OPLMN_VERSION_LEN * sizeof(VOS_INT8));

    /* Modified by s00217060 for coverity����, 2014-02-19, begin */
    /* ������OPLMN���ݱ��浽��Ӧ�ķ���λ�� */
    ulOffset    = NAS_MML_OPLMN_WITH_RAT_UNIT_LEN * pstNvimCfgOPlmnInfo->usOplmnListNum;
    ulOplmnNum  = NAS_MML_OPLMN_WITH_RAT_UNIT_LEN * pstEOPlmnSetMsg->ucOPlmnCount;

    if (NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN >= (ulOffset + ulOplmnNum))
    {

        PS_MEM_CPY(pstNvimCfgOPlmnInfo->aucOPlmnList + ulOffset,
                    pstEOPlmnSetMsg->aucOPlmnWithRat,
                    ulOplmnNum);
    }
    /* Modified by s00217060 for coverity����, 2014-02-19, end */

    pstNvimCfgOPlmnInfo->usOplmnListNum = usNewOPlmnNum;

    if (NV_OK != NV_Write(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST,
                          pstNvimCfgOPlmnInfo,
                          sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccEOPlmnSetReq_PreProc():ERROR: Write NV Failed");
        NAS_MMC_SndMsccEOPlmnSetCnf(VOS_ERR);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return VOS_TRUE;
    }

    /*NV����ɹ��󼴿�֪ͨTAF*/
    NAS_MMC_SndMsccEOPlmnSetCnf(VOS_OK);

    enFsmId         = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    ucMmcTopState   = (VOS_UINT8)NAS_MMC_GetFsmTopState();

    /*�ػ�״̬�·�����Чֵ,����Ҫ֪ͨMMCˢ��OPLMN*/
    if ( ( NAS_MMC_FSM_L1_MAIN == enFsmId )
      && ( NAS_MMC_L1_STA_NULL == ucMmcTopState ))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
        return VOS_TRUE;
    }

    /*����NVȫ�ֱ���*/
    pstUserCfgOPlmnInfo                 = NAS_MML_GetUserCfgOPlmnInfo();

    pstUserCfgOPlmnInfo->usOplmnListNum = usNewOPlmnNum;
    PS_MEM_CPY(pstUserCfgOPlmnInfo->aucVersion,
                pstEOPlmnSetMsg->aucVersion,
                NAS_MML_MAX_USER_OPLMN_VERSION_LEN * sizeof(VOS_INT8));


    PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);

    /*����MMC�ڲ�OPLMNˢ������*/
    NAS_MMC_SndInterNvimOPlmnRefreshInd();
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcInterNvimOPlmnRefreshInd_PreProc
 ��������  : ����OPLMN��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:����plmn����Ϣ�ṹ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��15��
   ��    ��   : x65241
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��26��
   ��    ��   : s00190137
   �޸�����   : ��ӷ�����ƣ����֧������256��OPLMN,���������������50��OPLMN

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcInterNvimOPlmnRefreshInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_USER_CFG_OPLMN_INFO_STRU                        *pstUserCfgOPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU                 *pstNvimCfgOPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                          *pstOperPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                               ulEfLen;
    VOS_UINT8                                               *pucEf = VOS_NULL_PTR;
    VOS_UINT32                                               ulLen;
    VOS_UINT32                                               ulRet;
    VOS_UINT32                                               ulFileId;

    ulEfLen = 0;
    ulLen   = 0;
    ulRet   = 0;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        ulFileId = USIMM_USIM_EFOPLMNWACT_ID;
    }
    else
    {
        ulFileId = USIMM_GSM_EFOPLMNWACT_ID;
    }

    /* ����MMC�е�OPLMN*/
    pstUserCfgOPlmnInfo = NAS_MML_GetUserCfgOPlmnInfo();

    if (VOS_TRUE == NAS_MML_IsNvimOplmnAvail())
    {
        pstNvimCfgOPlmnInfo = (NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU*)PS_MEM_ALLOC(
                                                          WUEPS_PID_MMC,
                                                          sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));

        if (VOS_NULL_PTR == pstNvimCfgOPlmnInfo)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcInterNvimOPlmnRefreshInd_PreProc():ERROR: Memory Alloc Error");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstNvimCfgOPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));

        (VOS_VOID)NV_GetLength(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST, &ulLen);

        /* ��NV��en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST��ʧ�ܣ�ֱ�ӷ��� */
        if (NV_OK != NV_Read(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST,
                             pstNvimCfgOPlmnInfo, ulLen))
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcInterNvimOPlmnRefreshInd_PreProc():WARNING: read en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST Error");
            PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);
            return VOS_TRUE;
        }

        NAS_MMC_UpdateOPlmnInfoFromNvim(pstNvimCfgOPlmnInfo->aucOPlmnList, pstUserCfgOPlmnInfo->usOplmnListNum);
        PS_MEM_FREE(WUEPS_PID_MMC, pstNvimCfgOPlmnInfo);

    }
    else /* �����ǰ��NV��Ч������Ҫ�ѿ��ڵ���Ϣ������*/
    {
        /* ���ڵ���Ϣ��������*/
        ulRet = NAS_USIMMAPI_IsServiceAvailable(USIM_SVR_OPLMN_SEL_WACT);

        if ( PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, USIMM_GUTL_APP))
            {
                NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMmcInterNvimOPlmnRefreshInd_PreProc():ERROR:READ FILE FAIL!");

                /* ��ȡȫ�ֱ����ĵ�ַ */
                pstOperPlmnInfo = NAS_MML_GetSimOperPlmnList();

                /* ��ʼ��ȫ�ֱ����е�OPLMN��Ϣ */
                NAS_MML_InitSimOperPlmnInfo(pstOperPlmnInfo);
            }
            else
            {
                NAS_MMC_SndOmGetCacheFile(ulFileId, ulEfLen, pucEf);

                /* ��ȡ�ļ��ɹ���MMC�ڲ�����Ӧ���� */
                NAS_MMC_ProcAgentUsimReadFileCnf_PreProc((VOS_UINT16)ulFileId, (VOS_UINT16)ulEfLen, pucEf);
            }
        }
        else /* ������ļ�Ҳ�����ã����������*/
        {
            /* ��ȡȫ�ֱ����ĵ�ַ */
            pstOperPlmnInfo = NAS_MML_GetSimOperPlmnList();

            /* ��ʼ��ȫ�ֱ����е�OPLMN��Ϣ */
            NAS_MML_InitSimOperPlmnInfo(pstOperPlmnInfo);

        }
    }

    /* ���¸����ȼ���������*/
    return NAS_MMC_ProHighPrioPlmnRefreshInd_PreProc();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCmServiceInd_PreProc
 ��������  : ����MM cm service ind ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������

 �޸���ʷ      :
 1.��    ��   : 2014��03��03��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCmServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstCmServiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucCsServiceConnStatusFlag;

    VOS_UINT8                           ucEnableLteTimerExpFlag;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurFsmId;
    VOS_UINT32                          ulState;

    pstPrioRatList          = NAS_MML_GetMsPrioRatList();
    ucEnableLteTimerExpFlag = NAS_MMC_GetEnableLteTimerExpireFlag();

    pstCmServiceInd           = (MMCMM_CM_SERVICE_IND_STRU *)pstMsg;
    ucCsServiceConnStatusFlag = NAS_MML_GetCsServiceConnStatusFlg();

    if ((MM_CS_SERV_EXIST == pstCmServiceInd->ulCsServFlg)
     && (VOS_TRUE == ucCsServiceConnStatusFlag))
    {
        NAS_MMC_SndMsccCsServiceConnStatusInd(VOS_TRUE);
        return VOS_FALSE;
    }

    if (MM_CS_SERV_NOT_EXIST == pstCmServiceInd->ulCsServFlg)
    {
        NAS_MMC_SndMsccCsServiceConnStatusInd(VOS_FALSE);

        /* ���֮ǰenable lte��ʱ����ʱ��ʶΪtrue��csҵ���������Ҫenable
           lte����������*/
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == ucEnableLteTimerExpFlag)
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_BUTT);

            /* ��ǰ״̬��ID */
            enCurFsmId = NAS_MMC_GetCurrFsmId();
            ulState    = NAS_MMC_GetFsmTopState();

            /* enable lte����Ҫ����������syscfg����LTE���뼼�����ȼ���ߣ������ڲ�������Ϣ */
            if ((VOS_TRUE == NAS_MML_GetEnableLteTrigPlmnSearchFlag())
             && (NAS_MML_NET_RAT_TYPE_LTE == pstPrioRatList->aucRatPrio[0])
             && (NAS_MMC_L1_STA_ON_PLMN == ulState)
             && (NAS_MMC_FSM_L1_MAIN == enCurFsmId))
            {
                /* ����ѡ��״̬�����������ȡ��ע�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH,VOS_NULL_PTR, 0);
            }
        }
#endif
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmSimAuthRej_PreProc
 ��������  : ����MM��GMM�����ϱ���sim����Ȩʧ����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:M��GMM�����ϱ���sim����Ȩʧ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������

 �޸���ʷ      :
 1.��    ��   : 2013��11��16��
   ��    ��   : m00217266
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSimAuthFail_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_SIM_AUTH_FAIL_IND_STRU       *pstSimAuthFail;

    pstSimAuthFail  = (MMCMM_SIM_AUTH_FAIL_IND_STRU *)pstMsg;

    NAS_MMC_SndMsccUsimAuthFailInd(pstSimAuthFail->enSrvDomain, pstSimAuthFail->enSimAuthFailValue);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSimAuthFail_PreProc
 ��������  : ����MM��GMM�����ϱ���sim����Ȩʧ����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:M��GMM�����ϱ���sim����Ȩʧ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��16��
   ��    ��   : m00217266
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSimAuthFail_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_SIM_AUTH_FAIL_IND_STRU      *pstSimAuthFail;

    pstSimAuthFail  = (MMCGMM_SIM_AUTH_FAIL_IND_STRU *)pstMsg;

    NAS_MMC_SndMsccUsimAuthFailInd(pstSimAuthFail->enSrvDomain, pstSimAuthFail->enSimAuthFailValue);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNetScanConflictWithFsmId_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �� �� ��  : NAS_MMC_ProcessNetScanReq_PreProc
 ��������  : �ú�����MMC�ܵ�NETSCAN����������Զ�ʱ����ʱ������
 �������  : enFsmId - mmc��״̬��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: NETSCAN��mmc��״̬����ͻ
             VOS_FALSE:NETSCAN��mmc��״̬������ͻ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNetScanConflictWithFsmId_PreProc(
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId
)
{
    /* �ڲ��б��ѡ�BG�ѡ���ϵͳʱ��ֱ�ӻظ�ERROR */
    if ( (NAS_MMC_FSM_PLMN_LIST             == enFsmId)
      || (NAS_MMC_FSM_BG_PLMN_SEARCH        == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_OOS         == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_HO          == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_CCO         == enFsmId)
      || (NAS_MMC_FSM_INTER_SYS_CELLRESEL   == enFsmId) )
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNetRatTypeWcdmaOrGsm
 ��������  : �жϽ���ģʽ�Ƿ���GW
 �������  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8          enRat
 �������  : VOS_TRUE��ʾGW
             VOS_FALSE��ʾ��GW
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNetRatTypeWcdmaOrGsm(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* ��ǰʱWCDMAʱ�򣬷���VOS_TRUE */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enRat) )
    {
        return VOS_TRUE;
    }

    /* ��ǰ��GSMʱ�򣬷���VOS_TRUE */
    if ( NAS_MML_NET_RAT_TYPE_GSM == enRat )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsEnableEndNetScanReq_PreProc
 ��������  : MMC�Ƿ��ܹ�ֱ�Ӹ�MSCC�ظ�ʧ��
 �������  : ��
 �������  : MMC_MSCC_NET_SCAN_CAUSE_ENUM_UINT8  *penCause
 �� �� ֵ  : VOS_TRUE  ֱ�Ӹ�MSCC�ظ�NETSCAN����ʧ��
             VOS_FALSE ��Ҫ������һ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��15��
    ��    ��   : w00167002
    �޸�����   : �ɼ��̹淶�޸�:ɾ����Ч����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsEnableEndNetScanReq_PreProc(
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8  *penCause
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    VOS_UINT32                                              ulCsServiceExistFlg;
    VOS_UINT32                                              ulPsServiceExistFlg;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8               enSpecPlmnSearchState;

    ulCsServiceExistFlg   = NAS_MML_GetCsServiceExistFlg();
    ulPsServiceExistFlg   = NAS_MML_GetPsServiceExistFlg();
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /* ����ģʽ���ԣ�ֱ�ӷ���VOS_TRUE */
    if ( VOS_FALSE == NAS_MMC_IsNetRatTypeWcdmaOrGsm(NAS_MML_GetCurrNetRatType()) )
    {
        *penCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_RAT_TYPE_ERROR;

        return VOS_TRUE;
    }

    /* ����ҵ�����ӣ���MSCCģ��ظ����ʧ�ܣ�ԭ��ֵ��ͻ */
    if ( (VOS_TRUE == ulCsServiceExistFlg)
      || (VOS_TRUE == ulPsServiceExistFlg) )
    {
        *penCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_SERVICE_EXIST;

        return VOS_TRUE;
    }

    enFsmId = NAS_MMC_GetCurrFsmId();

    /* �ڲ��б��ѡ�BG�ѡ���ϵͳʱ��ֱ�ӻظ�ERROR */
    if ( VOS_TRUE == NAS_MMC_IsNetScanConflictWithFsmId_PreProc(enFsmId) )
    {
        *penCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_CONFLICT;

        return VOS_TRUE;
    }

    /* ��ǰ������״̬����OOCʱ���п�������Ϊδפ��������ERROR */
    if ( ( (NAS_MMC_L1_STA_OOC  == NAS_MMC_GetFsmTopState())
         && (NAS_MMC_FSM_L1_MAIN == enFsmId) )
      || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState) )
    {

        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {
            *penCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_NOT_CAMPED;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartPeriodicNetScanTimer_PreProc
 ��������  : MMC�Ƿ���Ҫ����������ɨ�趨ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE ������������ɨ�趨ʱ��
             VOS_FALSE �������һ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartPeriodicNetScanTimer_PreProc(VOS_VOID)
{

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8               enSpecPlmnSearchState;

    enFsmId               = NAS_MMC_GetCurrFsmId();
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /* ��ǰ������״̬����OOCʱ���޿������������Զ�ʱ�� */
    if ( ( (NAS_MMC_L1_STA_OOC  == NAS_MMC_GetFsmTopState())
         && (NAS_MMC_FSM_L1_MAIN == enFsmId) )
      || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState) )
    {
        if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
        {
            return VOS_TRUE;
        }
    }

    /* �������Ӵ��ڣ������������Զ�ʱ�� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccNetScanReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��10��29��
    ��    ��   : w00167002
    �޸�����   : ���Ӷ��ϱ�MSCC����Ϣ�ĳ�ʼ��������ucFreqNum�����Ǹ����ֵ��MSCC
                 ����AT�ϱ�ʱ�򣬻ᵼ���ڴ��쳣���ʡ�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcessNetScanReq_PreProc(
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    MMC_MSCC_NET_SCAN_CNF_STRU           stNetScanCnf;

    /* ��ǰ�Ƿ���Ҫֱ�Ӹ�MSCC�ظ� */
    if ( VOS_TRUE == NAS_MMC_IsEnableEndNetScanReq_PreProc(&enCause) )
    {
        PS_MEM_SET(&stNetScanCnf, 0X00, sizeof(MMC_MSCC_NET_SCAN_CNF_STRU));

        stNetScanCnf.enResult = NAS_MSCC_PIF_NET_SCAN_RESULT_FAILURE;
        stNetScanCnf.enCause  = enCause;
        NAS_MMC_SndMsccNetScanCnf(&stNetScanCnf);

        return;
    }

    /* ��ǰ�Ƿ���Ҫ����������ɨ�趨ʱ�� */
    if ( VOS_TRUE == NAS_MMC_IsNeedStartPeriodicNetScanTimer_PreProc() )
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER, TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER_LEN);

        return;
    }

    /* ��GUAS����NETSCAN���� */
    NAS_MMC_SndAsNetScanReq(NAS_MML_GetCurrNetRatType(), pstNetScanReq);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccNetScanReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq       = VOS_NULL_PTR;

    pstNetScanReq = (MSCC_MMC_NET_SCAN_REQ_STRU*)pstMsg;

    /* ����MSCCģ�鷢�͹�����NETSCAN���������Զ�ʱ����ʱ����ʹ�� */
    NAS_MMC_SetNetScanReq(pstNetScanReq);

    NAS_MMC_ProcessNetScanReq_PreProc(pstNetScanReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccNetScanReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccAbortNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU     stAbortNetScanCnf;

    PS_MEM_SET(&stAbortNetScanCnf, 0x00, sizeof(stAbortNetScanCnf));

    if ( NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER);

        /* ��MSCC���Ϳյ�ɨ���� */
        NAS_MMC_SndMsccAbortNetScanCnf(&stAbortNetScanCnf);
    }
    else
    {
        if ( VOS_TRUE == NAS_MMC_IsNetRatTypeWcdmaOrGsm(NAS_MML_GetCurrNetRatType()) )
        {
            /* ������㷢��ֹͣɨ������ */
            NAS_MMC_SndAsNetScanStopReq(NAS_MML_GetCurrNetRatType());
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccAbortNetScanReq_PreProc:rcv unexpected abort net scan req!");
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccNetScanReq_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvPeriodicNetScanExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq = VOS_NULL_PTR;

    /* ��ȡ�Ѿ������NETSCAN REQ */
    pstNetScanReq         = NAS_MMC_GetNetScanReq();

    NAS_MMC_ProcessNetScanReq_PreProc(pstNetScanReq);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertNetScanRrcBandToNasFormat
 ��������  : ��RRC�ϱ���Ƶ������ת��ΪMMCά����Ƶ�θ�ʽ
 �������  : ulBand               - ������ʽ��Ƶ����Ϣ
 �������  : pstNasBand           - MMC��ʽ��Ƶ����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertNetScanRrcBandToNasFormat(
    VOS_UINT32                          ulBand,
    NAS_MML_MS_BAND_INFO_STRU          *pstNasBand
)
{
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstReq              = VOS_NULL_PTR;

    /* ��ȡ�����NETSCAN���� */
    pstReq                              = NAS_MMC_GetNetScanReq();

    if ( NAS_MML_NET_RAT_TYPE_GSM == pstReq->ucRat )
    {
        pstNasBand->unGsmBand.ulBand    = ulBand;

        return;
    }

    pstNasBand->unWcdmaBand.ulBand      = ulBand;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcCauseToNasFormat
 ��������  : ��RRC�ϱ���causeת��ΪMMCά����cause��ʽ
 �������  : enRrcCause  - ������ʽ��CAUSE��Ϣ
 �������  : penMmcCause - MMC��ʽ��CAUSE��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcCauseToNasFormat(
    RRC_NAS_NET_SCAN_CAUSE_ENUM_UINT8   enRrcCause,
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8  *penMmcCause
)
{
    switch ( enRrcCause )
    {
        case RRC_NAS_NET_SCAN_CAUSE_SIGNAL_EXIST :
            *penMmcCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_SIGNAL_EXIST;
            break;

        case RRC_NAS_NET_SCAN_CAUSE_STATE_NOT_ALLOWED :
            *penMmcCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_STATE_NOT_ALLOWED;
            break;

        case RRC_NAS_NET_SCAN_CAUSE_FREQ_LOCK :
            *penMmcCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_FREQ_LOCK;
            break;

        case RRC_NAS_NET_SCAN_CAUSE_PARA_ERROR :
            *penMmcCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_PARA_ERROR;
            break;

        default:
            *penMmcCause = NAS_MSCC_PIF_NET_SCAN_CAUSE_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcNetScanCnfToNasFormat
 ��������  : ��RRC�ϱ���NETSCAN CNF��Ϣת��ΪMMCά����NETSCAN CNF��ʽ
 �������  : pstRrmmNetScanCnfMsg - ������ʽ��NETSCAN CNF��Ϣ
 �������  : pstNetScanCnf        - MMC��ʽ��NETSCAN CNF��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcNetScanCnfToNasFormat(
    RRMM_NET_SCAN_CNF_STRU             *pstRrmmNetScanCnfMsg,
    MMC_MSCC_NET_SCAN_CNF_STRU          *pstNetScanCnf
)
{
    VOS_UINT32                          i;

    pstNetScanCnf->enResult             = pstRrmmNetScanCnfMsg->enResult;
    pstNetScanCnf->ucFreqNum            = pstRrmmNetScanCnfMsg->ucFreqNum;

    NAS_MMC_ConvertRrcCauseToNasFormat(pstRrmmNetScanCnfMsg->enCause, &pstNetScanCnf->enCause);

    if ( NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM < pstNetScanCnf->ucFreqNum )
    {
        pstNetScanCnf->ucFreqNum        = NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM;
    }

    for ( i = 0 ; i < pstNetScanCnf->ucFreqNum; i++ )
    {
        pstNetScanCnf->astNetScanInfo[i].usArfcn        = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usArfcn;
        pstNetScanCnf->astNetScanInfo[i].usC1           = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usC1;
        pstNetScanCnf->astNetScanInfo[i].usC2           = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usC2;
        pstNetScanCnf->astNetScanInfo[i].usLac          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usLac;
        pstNetScanCnf->astNetScanInfo[i].ulMcc          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].ulMcc;
        pstNetScanCnf->astNetScanInfo[i].ulMnc          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].ulMnc;
        pstNetScanCnf->astNetScanInfo[i].usBsic         = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usBsic;
        pstNetScanCnf->astNetScanInfo[i].sRxlev         = pstRrmmNetScanCnfMsg->astNetScanInfo[i].sRxlev;
        pstNetScanCnf->astNetScanInfo[i].sRssi          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].sRssi;
        pstNetScanCnf->astNetScanInfo[i].ulCellId       = pstRrmmNetScanCnfMsg->astNetScanInfo[i].ulCellId;

        NAS_MMC_ConvertNetScanRrcBandToNasFormat(pstRrmmNetScanCnfMsg->astNetScanInfo[i].aulBand[0],
                                          &pstNetScanCnf->astNetScanInfo[i].stBand);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmNetScanCnf_PreProc
 ��������  : MMC�յ�ID_MSCC_MMC_NET_SCAN_REQ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_NET_SCAN_CNF_STRU             *pstRcvRrmmMsg       = VOS_NULL_PTR;
    MMC_MSCC_NET_SCAN_CNF_STRU           stNetScanCnf;

    pstRcvRrmmMsg = (RRMM_NET_SCAN_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    /* �����������ӵ�ʱ����Ҫ�������ڳ��Զ�ʱ�� */
    if ( (RRC_NAS_NET_SCAN_RESULT_FAILURE     == pstRcvRrmmMsg->enResult)
      && (RRC_NAS_NET_SCAN_CAUSE_SIGNAL_EXIST == pstRcvRrmmMsg->enCause) )
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER, TI_NAS_MMC_PERIODIC_NET_SCAN_TIMER_LEN);

        return VOS_TRUE;
    }

    NAS_MMC_ConvertRrcNetScanCnfToNasFormat(pstRcvRrmmMsg, &stNetScanCnf);
    NAS_MMC_SndMsccNetScanCnf(&stNetScanCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcNetScanStopCnfToNasFormat
 ��������  : ��RRC�ϱ���STOP NETSCAN CNF��Ϣת��ΪMMCά����NETSCAN CNF��ʽ
 �������  : RRMM_NET_SCAN_STOP_CNF_STRU        *pstRrmmNetScanCnfMsg
 �������  : MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstNetScanCnf
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��15��
    ��    ��   : w00167002
    �޸�����   : �ɼ��̹淶�޸�:i�޸�Ϊ32λ
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcNetScanStopCnfToNasFormat(
    RRMM_NET_SCAN_STOP_CNF_STRU        *pstRrmmNetScanCnfMsg,
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstNetScanCnf
)
{
    VOS_UINT32                          i;

    pstNetScanCnf->ucFreqNum = pstRrmmNetScanCnfMsg->ucFreqNum;

    if ( NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM < pstNetScanCnf->ucFreqNum )
    {
        pstNetScanCnf->ucFreqNum = NAS_MSCC_PIF_NET_SCAN_MAX_FREQ_NUM;
    }

    for ( i = 0 ; i < pstNetScanCnf->ucFreqNum; i++ )
    {
        pstNetScanCnf->astNetScanInfo[i].usArfcn        = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usArfcn;
        pstNetScanCnf->astNetScanInfo[i].usC1           = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usC1;
        pstNetScanCnf->astNetScanInfo[i].usC2           = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usC2;
        pstNetScanCnf->astNetScanInfo[i].usLac          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usLac;
        pstNetScanCnf->astNetScanInfo[i].ulMcc          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].ulMcc;
        pstNetScanCnf->astNetScanInfo[i].ulMnc          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].ulMnc;
        pstNetScanCnf->astNetScanInfo[i].usBsic         = pstRrmmNetScanCnfMsg->astNetScanInfo[i].usBsic;
        pstNetScanCnf->astNetScanInfo[i].sRxlev         = pstRrmmNetScanCnfMsg->astNetScanInfo[i].sRxlev;
        pstNetScanCnf->astNetScanInfo[i].sRssi          = pstRrmmNetScanCnfMsg->astNetScanInfo[i].sRssi;
        pstNetScanCnf->astNetScanInfo[i].ulCellId       = pstRrmmNetScanCnfMsg->astNetScanInfo[i].ulCellId;

        NAS_MMC_ConvertNetScanRrcBandToNasFormat(pstRrmmNetScanCnfMsg->astNetScanInfo[i].aulBand[0],
                                          &pstNetScanCnf->astNetScanInfo[i].stBand);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmNetScanStopCnf_PreProc
 ��������  : MMC�յ�RRMM_NET_SCAN_STOP_CNF�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmNetScanStopCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_NET_SCAN_STOP_CNF_STRU        *pstRcvRrmmMsg       = VOS_NULL_PTR;
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU     stAbortNetScanCnf;

    pstRcvRrmmMsg = (RRMM_NET_SCAN_STOP_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stAbortNetScanCnf, 0x00, sizeof(MMC_MSCC_ABORT_NET_SCAN_CNF_STRU));

    /* ��������ϱ���ֹͣɨ����ת����NAS�Ľṹ */
    NAS_MMC_ConvertRrcNetScanStopCnfToNasFormat(pstRcvRrmmMsg, &stAbortNetScanCnf);

    /* ��MSCCģ��ת��������ϱ���STOP CNF���� */
    NAS_MMC_SndMsccAbortNetScanCnf(&stAbortNetScanCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasNcellMonitorInd_PreProc
 ��������  : MMC�յ�RRMM_NCELL_MONITOR_IND�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��02��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasNcellMonitorInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRC_NAS_NCELL_MONITOR_IND_STRU     *pstNcellMonitorInd;

    pstNcellMonitorInd = (RRC_NAS_NCELL_MONITOR_IND_STRU*)pstMsg;

    if ( RRC_NAS_NCELL_STATE_3G == pstNcellMonitorInd->enNcellState)
    {
        NAS_MML_SetRrcUtranNcellExistFlg(VOS_TRUE);
        NAS_MML_SetRrcLteNcellExistFlg(VOS_FALSE);
    }
    else if ( RRC_NAS_NCELL_STATE_4G == pstNcellMonitorInd->enNcellState)
    {
        NAS_MML_SetRrcLteNcellExistFlg(VOS_TRUE);
        NAS_MML_SetRrcUtranNcellExistFlg(VOS_FALSE);
    }
    else if ( RRC_NAS_NCELL_STATE_3G4G == pstNcellMonitorInd->enNcellState)
    {
        NAS_MML_SetRrcUtranNcellExistFlg(VOS_TRUE);
        NAS_MML_SetRrcLteNcellExistFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetRrcUtranNcellExistFlg(VOS_FALSE);
        NAS_MML_SetRrcLteNcellExistFlg(VOS_FALSE);
    }


    return VOS_TRUE;
}


/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PreProc
 ��������  : �յ�MSCC��ID_MSCC_MMC_IMS_VOICE_CAP_IND��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_IMS_VOICE_CAP_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  3.��    ��   : 2015��2��12��
    ��    ��   : s00217060
    �޸�����   : VOLTE SWITCH�޸ģ�cs onlyʱ��Ҳ��Ҫdisable LTE
  4.��    ��   : 2015��4��20��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  5.��    ��   : 2015��12��24��
    ��    ��   : j00174725
    �޸�����   : DTS2015121106874
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
#endif
    NAS_MMC_TIMER_STATUS_ENUM_U8        enAvaiStatus;


    pstImsVoiceInd = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ��֮ǰ���,����ı�ʱ֪ͨLMM��ǰIMS VOICE�Ƿ���� */
    if (NAS_MML_GetImsVoiceAvailFlg() != pstImsVoiceInd->ucAvail)
    {
#if (FEATURE_ON == FEATURE_LTE)
        NAS_MMC_SndLmmImsVoiceCapChangeNtf(pstImsVoiceInd->ucAvail);
#endif

        /* �洢IMS�Ƿ������Ϣ��MML��ȫ�ֱ����� */
        NAS_MML_SetImsVoiceAvailFlg(pstImsVoiceInd->ucAvail);
    }

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_SetPersistentBearerState(pstImsVoiceInd->ucIsExistPersistentBearer);

    /* ON PLMN��ֱ�ӿ��Դ��� */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
     && (NAS_MMC_FSM_L1_MAIN    == enFsmId))
    {
        /* cs onlyʱ��ims�����ô�����ͬ������Ҫ�ж��Ƿ�Disable LTE */
        if ( (NAS_MML_CS_VOICE_ONLY != NAS_MML_GetVoiceDomainPreference())
          && (VOS_TRUE == pstImsVoiceInd->ucAvail) )
        {
            return VOS_TRUE;
        }

        /* ������IMS voice������ʱ��Disable Lģ����������һ������ */
        if (VOS_FALSE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PreProc: NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail");
            return VOS_TRUE;
        }

        /* �����ǰ����������GU����available��ʱ���������У�����ҪDisable LTE */
        enAvaiStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);
        if ( (VOS_TRUE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU())
          && (NAS_MMC_TIMER_STATUS_RUNING == enAvaiStatus) )
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccImsVoiceCapInd_PreProc: NAS_MMC_IsCsPsMode1NeedPeriodSearchGU");
            return VOS_TRUE;
        }

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

        /* GU�²���Ҫ�ٴδ�������,����ֱ��֪ͨRRC����Disable Lģ */
        if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());

            return VOS_TRUE;
        }

        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        /* �����ǰL��EPS�������Ӵ��ڣ��򻺴湹���������Ϣ */
        if (VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE);

            NAS_MMC_SndLmmRelReq();

            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
#else
    return VOS_TRUE;
#endif
}
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasAreaLostInd_PreProc
 ��������  : Ԥ���������յ�Was��RRMM_AREA_LOST_IND��Ϣ,���Ӷ�NO RFʧ����Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND_STRU��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��29��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���

 2.��    ��   : 2014��6��12��
   ��    ��   : w00167002
   �޸�����   : DSDS III:��NO RF������֪ͨMSCC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasAreaLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU            *pstAreaLost         = VOS_NULL_PTR;

    pstAreaLost         = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    if (RRC_NAS_NO_RF_AREA_LOST == pstAreaLost->ulRptMode)
    {
        /* ����area lost no rf */
        NAS_MMC_ProcNoRfAreaLost_PreProc(NAS_MML_NET_RAT_TYPE_WCDMA);

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_WAS_NO_RF_AREA_LOST);
        }
        else
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_TAS_NO_RF_AREA_LOST);
        }

        return VOS_FALSE;
    }

    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_WAS_NORMAL_AREA_LOST);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_TAS_NORMAL_AREA_LOST);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasAreaLostInd_PreProc
 ��������  : Ԥ���������յ�Gas��RRMM_AREA_LOST_IND��ʱ��Ϣ,���Ӷ�NO RFʧ����Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND_STRU��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��29��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��12��
   ��    ��   : w00167002
   �޸�����   : DSDS III:��NO RF������֪ͨMSCC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasAreaLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU            *pstAreaLost         = VOS_NULL_PTR;

    pstAreaLost         = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    if (RRC_NAS_NO_RF_AREA_LOST == pstAreaLost->ulRptMode)
    {
        /* ����area lost no rf */
        NAS_MMC_ProcNoRfAreaLost_PreProc(NAS_MML_NET_RAT_TYPE_GSM);

        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_GAS_NO_RF_AREA_LOST);

        return VOS_FALSE;
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_GAS_NORMAL_AREA_LOST);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmPsStatusInd_PreProc
 ��������  : Ԥ�������յ�RRM��PS STATUS IND��Ϣ��֪ͨRRM����ȥע��
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_RRM_PS_STATUS_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��21��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��7��26��
   ��    ��   : b00269685
   �޸�����   : DSDS IV�ӿ��޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmPsStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRM_PS_STATUS_IND_STRU             *pstRrmPsStatusInd = VOS_NULL_PTR;
    VOS_RATMODE_ENUM_UINT32             enRrmPsRatType;

    pstRrmPsStatusInd   = (RRM_PS_STATUS_IND_STRU*)pstMsg;
    enRrmPsRatType      = pstRrmPsStatusInd->enRatType;

    /* ��RRM����ȥע����Ϣ,MMC����֪ͨ��ͬRAT��NO RFʱ,RRM֪ͨ��Դ����Ҳ��֪ͨ��Ӧ�Ĳ�ͨRAT��
       RF��Դ���� */
    NAS_MMC_DeregisterRrmResourceNtf(enRrmPsRatType, RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* ���������ж��Ƿ���Ҫ�������� */
    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_PreProc
 ��������  : Ԥ���������յ�TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER��ʱ����ʱ��Ϣ,�ж��ܷ���и����ȼ�RAT��HPLMN����
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMERʱ��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_TRUE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��4��10��
   ��    ��   : w00242748
   �޸�����   : DTS2014040905679:���뼼��˳��030201����ǰפ����GSM�ϣ�
                �����ȼ����뼼��HPLMN����Lʧ�ܣ�����W�ɹ����ɹ�ע����ٴ�
                ���������ȼ����뼼��HPLMNʱ����ʱ��ʱ������ȷ��
 3.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
 4.��    ��   : 2014��11��18��
   ��    ��   : b00269685
   �޸�����   : td����ϵͳ��L��ʱ����ʱ����Ҫ��һ��count

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCurrHighRatHplmnTdCount;
    VOS_UINT8                                               ucNvHighRatHplmnTdThreshold;

    if (VOS_FALSE == NAS_MMC_IsHighPrioRatHplmnSearchVaild())
    {
        return VOS_TRUE;
    }

    ucCurrHighRatHplmnTdCount   = NAS_MMC_GetTdHighRatSearchCount();
    ucNvHighRatHplmnTdThreshold = NAS_MML_GetHighPrioRatHplmnTimerTdThreshold();

    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        if (ucCurrHighRatHplmnTdCount < ucNvHighRatHplmnTdThreshold)
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen());

            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();

            return VOS_TRUE;
        }
    }

    /* פ������HPLMN�϶�������Ϣ */
    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    /* פ����HPLMN��Ϊ������ȼ��Ľ��뼼����λ��ʱ���������� */
    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioRatHplmn())
    {
        NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

        NAS_MMC_InitTdHighRatSearchCount();

        return VOS_TRUE;
    }

    /* ���������ϱ�not camp on��Ϣ���������𱳾����� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        return VOS_FALSE;
    }

    /* �޷����и����ȼ�����ʱ���������ö�ʱ������ */
    if (VOS_FALSE == NAS_MMC_IsEnableBgPlmnSearch_PreProc())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerRetryLen());
        NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmServiceRequestResultInd_PreProc
 ��������  : �յ�GMMMMC_SERVICE_REQUEST_RESULT_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstGmmServReqRsltInd = VOS_NULL_PTR;

    pstGmmServReqRsltInd  = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /* ���񱻾ܳ�����Ҫ�����ϱ� */
    if (GMM_MMC_ACTION_RESULT_FAILURE == pstGmmServReqRsltInd->enActionResult)
    {
        NAS_MMC_SndMsccServRejRsltInd(NAS_MSCC_PIF_SRVDOMAIN_PS,
                                     pstGmmServReqRsltInd->enRegFailCause);
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmSuspendInd_PreProc
 ��������  : �յ�RRMM_SUSPEND_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00234330
    �޸�����   : dts2014040806903,פ���ڵ�ǰģʽ��,�յ�����ģʽ�Ĺ�������,ֱ�ӻظ�����ʧ��
  2.��    ��   : 2014��8��1��
    ��    ��   : w00167002
    �޸�����   : ������״̬�յ���ϵͳ��Ϣ����ֱ�ӻظ�ʧ�ܡ�
  3.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrmmSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST            *pstSuspendMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32      enFsmId;

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enAsCellCampOn;
    enAsCellCampOn = NAS_MMC_GetAsCellCampOn();

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
      && ( WUEPS_PID_WRR == pstSuspendMsg->MsgHeader.ulSenderPid ))
    {
        /* ��ǰ����פ����Wģʽ�£����ع���ʧ�� */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

        return VOS_TRUE;
    }

    if ( ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
      && ( UEPS_PID_GAS == pstSuspendMsg->MsgHeader.ulSenderPid ))
    {
        /* ��ǰ����פ����Gģʽ�£����ع���ʧ�� */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);

        return VOS_TRUE;
    }

    if ( pstSuspendMsg->ucSuspendCause >= MMC_SUSPEND_CAUSE_BUTT )
    {
        /* ��������Ƿ� */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

        return VOS_TRUE;
    }

    /* ���Ϊ��ǰģʽ,�Ѿ�����ϵͳ״̬����,�ٴ��յ�������Ϣ,ֱ�Ӹ�λ */
    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( ( NAS_MMC_FSM_INTER_SYS_HO == enFsmId )
      || ( NAS_MMC_FSM_INTER_SYS_CELLRESEL == enFsmId )
      || ( NAS_MMC_FSM_INTER_SYS_OOS == enFsmId ) )
    {
        if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
          && ( WUEPS_PID_WRR == pstSuspendMsg->MsgHeader.ulSenderPid ))
        {
            if ( NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_WAS_SUSPEND_IND);
            }
            else
            {
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_TD_SUSPEND_IND);
            }
        }
        if ( ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
          && ( UEPS_PID_GAS == pstSuspendMsg->MsgHeader.ulSenderPid ))
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_GAS_SUSPEND_IND);
        }

        return VOS_TRUE;
    }


    /* ��ǰNASΪδפ��״̬ */
    if ( (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING  == NAS_MMC_GetSpecPlmnSearchState())
       && (NAS_MMC_AS_CELL_NOT_CAMP_ON      == enAsCellCampOn) )
    {
        /* ��������Ƿ� */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

        return VOS_TRUE;
    }

    /* ����״̬������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmResumeInd_PreProc
 ��������  : �յ�RRMM_RESUME_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00234330
    �޸�����   : dts2014040806903,פ���ڵ�ǰģʽ��,�յ�����ģʽ�Ĺ�������,ֱ�ӻظ�����ʧ��
  2.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrmmResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_RESUME_IND_ST                   *pstResumeMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32            enFsmId;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8       enCurrNetRatType;

    pstResumeMsg = (RRMM_RESUME_IND_ST*)pstMsg;

    /* ���Ϊ��ǰģʽ,�Ѿ�����ϵͳ״̬����,�ٴ��յ�������Ϣ,ֱ�Ӹ�λ */
    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( ( NAS_MMC_FSM_INTER_SYS_HO != enFsmId )
      && ( NAS_MMC_FSM_INTER_SYS_CELLRESEL != enFsmId )
      && ( NAS_MMC_FSM_INTER_SYS_OOS != enFsmId )
      && ( NAS_MMC_FSM_INTER_SYS_CCO != enFsmId ))
    {
        enCurrNetRatType = NAS_MML_GetCurrNetRatType();
        /* �жϷ���id */
        if ( ( ( NAS_MML_NET_RAT_TYPE_GSM == enCurrNetRatType)
            && ( UEPS_PID_GAS != pstResumeMsg->MsgHeader.ulSenderPid ))
         ||  ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRatType)
            && ( WUEPS_PID_WRR != pstResumeMsg->MsgHeader.ulSenderPid ))
         ||    ( NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType ))
        {
            if ( UEPS_PID_GAS == pstResumeMsg->MsgHeader.ulSenderPid )
            {
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_GAS_RESUME_IND);
            }
            else if ( NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode() )
            {
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_WAS_RESUME_IND);
            }
            else
            {
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_TD_RESUME_IND);
            }
        }

        return VOS_TRUE;
    }

    /* ����״̬������ */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_DSDS)
#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcSessionTypeToLmmFormat
 ��������  : ��mmc��rrc�ӿ��е�session typeת��Ϊmmc��lmm��session type
 �������  : enRrcSessionType    - mmc��rrc�ӿ��е�session type
 �������  : pucLmmSessionType   - mmc��lmm��session type
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcSessionTypeToLmmFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType,
    MMC_LMM_SESSION_TYPE_ENUM_UINT8    *puclmmSessionType
)
{
    switch (enRrcSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_CS_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_CS_MO_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_STREAM_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_PS_INTERACT_CALL;
            break;

         case RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

         case RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *puclmmSessionType = MMC_LMM_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndBeginSessionNotify
 ��������  : ��AS����RRMM_BEGIN_SESSION_NOTIFY
 �������  : enRrcSessionType - ֪ͨgu������session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��4��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_VOID NAS_MMC_SndBeginSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;

#if(FEATURE_ON == FEATURE_LTE)
     MMC_LMM_SESSION_TYPE_ENUM_UINT8    enLmmSessionType;
#endif

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));

    /* ƽ̨֧��W/TD������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_MMC_SndAsBeginSessionNotify(WUEPS_PID_WRR, enRrcSessionType);
    }

    /* ƽ̨֧��G������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_MMC_SndAsBeginSessionNotify(UEPS_PID_GAS, enRrcSessionType);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* ƽ̨֧��LTE������end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_MMC_SndLmmBeginSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* ��дCTLͷ */
        stCtrl.ulModuleId = WUEPS_PID_MMC;

        MTC_SetBeginSessionInfo(&stCtrl,enMtcSessionType);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndEndSessionNotify
 ��������  : ��AS����RRMM_END_SESSION_NOTIFY
 �������  : enRrcSessionType - ֪ͨgu������session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��18��
    ��    ��   : b00269685
    �޸�����   : �����ӳ�ʱ��

*****************************************************************************/
VOS_VOID NAS_MMC_SndEndSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;

#if(FEATURE_ON == FEATURE_LTE)
     MMC_LMM_SESSION_TYPE_ENUM_UINT8    enLmmSessionType;
#endif
    NAS_MML_SESSION_TYPE_ENUM_UINT8     enMmlSessionType;


    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));

    if ( (RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL    == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_SS             == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_SMS            == enRrcSessionType) )
    {
        NAS_MMC_ConvertToMmlSessionType(enRrcSessionType, &enMmlSessionType);
        if (VOS_TRUE == NAS_MML_GetCsMoSessionSndFlag(enMmlSessionType))
        {
            return;
        }
    }

    /* ƽ̨֧��W/TD������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_MMC_SndAsEndSessionNotify(WUEPS_PID_WRR, enRrcSessionType, 0);
    }

    /* ƽ̨֧��G������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_MMC_SndAsEndSessionNotify(UEPS_PID_GAS, enRrcSessionType, 0);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* ƽ̨֧��LTE������end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_MMC_SndLmmEndSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* ��дCTLͷ */
        stCtrl.ulModuleId = WUEPS_PID_MMC;

        MTC_SetEndSessionInfo(&stCtrl,enMtcSessionType);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertSrvTypeToRrcSessionType
 ��������  : ��mscc��mmc�ӿ�ҵ������ת��Ϊmmc�ͽ����ӿ�session type
 �������  : enMsccMmcSrvType      - MSCC��MMC�ӿ�ҵ������
 �������  : pucRrcNasSessionType - MMC�ͽ����ӿ�session type
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertSrvTypeToRrcSessionType(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8         enMsccMmcSrvType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcNasSessionType
)
{
    switch (enMsccMmcSrvType)
    {
        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_SS:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_CS_MO_SS;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_CS_MO_SMS;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *pucRrcNasSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccSrvAcqReq_PreProc
 ��������  : MMC�յ�mscc��srv acq req��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��2��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulState;
    MSCC_MMC_SRV_ACQ_REQ_STRU           *pstSrvAcqReq = VOS_NULL_PTR;

    pstSrvAcqReq = (MSCC_MMC_SRV_ACQ_REQ_STRU*)pstMsg;
    enFsmId      = NAS_MMC_GetCurrFsmId();
    ulState      = NAS_MMC_GetFsmTopState();

    /* ����ǽ������д���������ǰ����on plmn��ֱ�ӻظ��������Ϊ�ɹ���
       �������ͨҵ�񴥷�������ǰ����on plmn��cs ps��һ������ṩ����������ظ��������Ϊ�ɹ� */
    if ((NAS_MMC_FSM_L1_MAIN           == enFsmId)
     && (NAS_MMC_L1_STA_ON_PLMN        == ulState))
    {
        if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == pstSrvAcqReq->enSrvType)
        {
            NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);
            return VOS_TRUE;
        }

        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);
            return VOS_TRUE;
        }
    }

    /* �����ǰanycell״̬���������Ҳ��ǽ�������ֱ�ӻظ�����ʧ�ܽ�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == enFsmId)
     && (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != pstSrvAcqReq->enSrvType))
    {
        NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccBeginSessionNotify_PreProc
 ��������  : MMC�յ�mscc��begin session notify��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccBeginSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU  *pstBeginSessionNotify = VOS_NULL_PTR;
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcNasSessionType;

    pstBeginSessionNotify = (MSCC_MMC_BEGIN_SESSION_NOTIFY_STRU *)pstMsg;

    NAS_MMC_ConvertSrvTypeToRrcSessionType(pstBeginSessionNotify->enSrvType, &enRrcNasSessionType);

    NAS_MMC_SndBeginSessionNotify(enRrcNasSessionType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccEndSessionNotify_PreProc
 ��������  : MMC�յ�mscc��end session notify��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccEndSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_END_SESSION_NOTIFY_STRU    *pstEndSessionNotify = VOS_NULL_PTR;
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcNasSessionType;

    pstEndSessionNotify = (MSCC_MMC_END_SESSION_NOTIFY_STRU *)pstMsg;

    NAS_MMC_ConvertSrvTypeToRrcSessionType(pstEndSessionNotify->enSrvType,
                                           &enRrcNasSessionType);

    NAS_MMC_SndEndSessionNotify(enRrcNasSessionType);

    return VOS_TRUE;
}

#endif

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PreProc
 ��������  : �յ�LMM_MMC_SUSPEND_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00234330
    �޸�����   : dts2014040806903,פ���ڵ�ǰģʽ��,�յ�����ģʽ�Ĺ�������,ֱ�ӻظ�����ʧ��
  2.��    ��   : 2014��8��1��
    ��    ��   : w00167002
    �޸�����   : ������״̬�յ���ϵͳ��Ϣ����ֱ�ӻظ�ʧ�ܡ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_SUSPEND_IND_STRU           *pstSuspendMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enAsCellCampOn;
    enAsCellCampOn = NAS_MMC_GetAsCellCampOn();

    pstSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* ��ǰ����פ����Lģʽ�£����ع���ʧ�� */
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

        return VOS_TRUE;
    }

    if ( pstSuspendMsg->ulSysChngType >= MMC_LMM_SUS_TYPE_BUTT )
    {
        /* ��������Ƿ� */
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

        return VOS_TRUE;
    }

    /* ���Ϊ��ǰģʽ,�Ѿ�����ϵͳ״̬����,�ٴ��յ�������Ϣ,ֱ�Ӹ�λ */
    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( ( NAS_MMC_FSM_INTER_SYS_HO == enFsmId )
      || ( NAS_MMC_FSM_INTER_SYS_CELLRESEL == enFsmId )
      || ( NAS_MMC_FSM_INTER_SYS_OOS == enFsmId ) )
    {
        if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_LMM_SUSPEND_IND);
        }

        return VOS_TRUE;
    }


    /* ��ǰNASΪδפ��״̬����������SUSPEND IND�Գ峡���²��ܴ���SUSPEND */
    if ( (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING  == NAS_MMC_GetSpecPlmnSearchState())
       && (NAS_MMC_AS_CELL_NOT_CAMP_ON      == enAsCellCampOn) )
    {
        /* ״̬����ȷ */
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

        return VOS_TRUE;
    }

    /* ����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmResumeInd_PreProc
 ��������  : �յ�LMM_MMC_RESUME_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00234330
    �޸�����   : dts2014040806903,פ���ڵ�ǰģʽ��,�յ�����ģʽ�Ĺ�������,ֱ�ӻظ�����ʧ��
  2.��    ��   : 2015��6��9��
    ��    ��   : l00324781
    �޸�����   : ��ϵͳ�л�����HRPD-->LTE����ǰLTE���ڴ�ģ��״̬ΪNAS_MMC_L1_STA_DEACT
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    NAS_MMC_L1_STA_ENUM_UINT32          enCurrState;

    /* ���Ϊ��ǰģʽ,������ϵͳ״̬����,�ٴ��յ�����ģʽ�Ļָ���Ϣ,ֱ�Ӹ�λ */
    enFsmId = NAS_MMC_GetCurrFsmId();
    enCurrState = NAS_MMC_GetFsmTopState();

    /* ���յ�LMM_MMC_RESUME_IND��Ϣ����ǰ״̬ΪDEACT��״̬��IDΪNAS_MMC_FSM_L1_MAIN��˵��LTE��ǰ���ڴ�ģ
       ����û���κζ�����ִ�У��������Ϣ
    */
    if ((NAS_MMC_L1_STA_DEACT == enCurrState)
         && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
        return VOS_FALSE;
    }

    if ( ( NAS_MMC_FSM_INTER_SYS_HO != enFsmId )
      && ( NAS_MMC_FSM_INTER_SYS_CELLRESEL != enFsmId )
      && ( NAS_MMC_FSM_INTER_SYS_OOS != enFsmId )
      && ( NAS_MMC_FSM_INTER_SYS_CCO != enFsmId ))
    {
        if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_LMM_RESUME_IND);
        }

        return VOS_TRUE;
    }

    /* ����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmInfoChangeNotifyInd_PreProc
 ��������  : �յ�LMM_MMC_INFO_CHANGE_NOTIFY_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��5��22��
    ��    ��   : b00269685
    �޸�����   : DTS2014050604659,����LMM �� MMC info change notify ����
  1.��    ��   : 2014��6��16��
    ��    ��   : y00245242
    �޸�����   : dts2014052905705�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmInfoChangeNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_INFO_CHANGE_NOTIFY_STRU                        *pstRcvMsg = VOS_NULL_PTR;
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                      stEmergencyNumList;
    NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8                   enNwEmcBS;
    NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8                enNwImsVoPS;
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8                enLteCsCap;
    VOS_UINT32                                              ulState;

    ulState   = NAS_MMC_GetFsmTopState();

    /* BG��״̬��ϵͳ��Ϣ�����ӳٷ��ͣ���Ҫ��ע��״̬�ͷ���״̬֮ǰ֪ͨMMA */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH                         == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND       == ulState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  == ulState)))
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }

    pstRcvMsg = (LMM_MMC_INFO_CHANGE_NOTIFY_STRU *)pstMsg;

    PS_MEM_SET(((VOS_UINT8*)&stEmergencyNumList) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* update LTE CS capability */
    NAS_MML_SetAdditionUpdateRslt((NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8)pstRcvMsg->enLteCsCap);

    enNwEmcBS = (NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8)pstRcvMsg->enNwEmcBS;

    enNwImsVoPS = (NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8)pstRcvMsg->enNwImsVoPS;

    NAS_MML_SetLteNwImsVoiceSupportFlg((NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8)enNwImsVoPS);

    switch (pstRcvMsg->enLteCsCap)
    {
        case LMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO:
            enLteCsCap = NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO;
            break;

        case LMM_MMC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER:
            enLteCsCap = NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER;
            break;

        case LMM_MMC_LTE_CS_CAPBILITY_SMS_ONLY:
            enLteCsCap = NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY;
            break;

        case LMM_MMC_LTE_CS_CAPBILITY_NOT_ATTACHED:
        default:
            enLteCsCap = NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED;
            break;
    }

    NAS_MMC_SndMsccNetworkCapabilityInfoInd(enNwImsVoPS, enNwEmcBS, enLteCsCap);

    /* ��GMM���ͽ������б� */
    stEmergencyNumList.ucOpEmcNumList       = VOS_TRUE;
    stEmergencyNumList.ucEmergencyNumAmount = pstRcvMsg->ucEmergencyNumAmount;
    PS_MEM_CPY(stEmergencyNumList.astEmergencyNumList, pstRcvMsg->astEmergencyNumList,
                sizeof(LMM_MMC_EMERGENCY_NUM_STRU) * LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS);

    NAS_MMC_SndGmmEmergencyNumList(&stEmergencyNumList);

    return VOS_TRUE;
}

#endif

/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSigStateInd_PreProc
 ��������  : �յ�MMCGMM_SIGNALING_STATUS_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : s00217060
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSigStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_SIGNALING_STATUS_IND_STRU                       *pstGmmSigStateInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpStatusFlg;


    pstGmmSigStateInd           = (MMCGMM_SIGNALING_STATUS_IND_STRU*)pstMsg;

    /* ��ȡ��ǰPdp״̬ */
    ucPdpStatusFlg = NAS_MML_GetConnStatus()->ucPdpStatusFlg;

    /* ��ǰ״̬��ΪMMC_GMM_SIGNALING_STATUS_ABSENT��PDP�Ѿ����� */
    if ( (MMC_GMM_SIGNALING_STATUS_ABSENT != pstGmmSigStateInd->ulSignalingSts)
      && (VOS_TRUE == ucPdpStatusFlg) )
    {
        NAS_MMC_SndMsccPsServiceConnStatusInd(VOS_TRUE, MSCC_MMC_PS_SIGNALING_TYPE_GU);
    }

    /* GMM�������Ӳ����� */
    if (MMC_GMM_SIGNALING_STATUS_ABSENT == pstGmmSigStateInd->ulSignalingSts)
    {
        NAS_MMC_SndMsccPsServiceConnStatusInd(VOS_FALSE, MSCC_MMC_PS_SIGNALING_TYPE_GU);
    }

    return VOS_FALSE;
}
/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcNoRfAreaLost_PreProc
 ��������  : Ԥ��������no rf����
 �������  : ���뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : b00269685
   �޸�����   : DSDS III��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRfAreaLost_PreProc(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    /* ����NO RF���ڱ����Ϣ */
    NAS_MML_SetCurrRatRfAvailFlg(enNasRat, VOS_FALSE);

    /*��RRM����ע����Ϣ*/
    NAS_MMC_RegisterRrmResourceNtf(enNasRat, RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* ��MSCC֪ͨ��ǰNO RF��Ϣ  */
    NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

    return;
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsSrvInfoNotify_PreProc
 ��������  : �յ�ID_MSCC_MMC_IMS_SRV_INFO_NOTIFY��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��11��06��
    ��    ��   : s00217060
    �޸�����   : DTS2014110608091,IMS�绰ʱ������cs���paging ind
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsSrvInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU   *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg   = (MSCC_MMC_IMS_SRV_INFO_NOTIFY_STRU *)pstMsg;

    NAS_MML_SetImsCallFlg(pstRcvMsg->ucImsCallFlg);

    return VOS_TRUE;
}
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsSwitchStateInd_PreProc
 ��������  : �յ�ID_MSCC_MMC_IMS_SWITCH_STATE_IND��ϢIMS���ظı�ʱ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsSwitchStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_SWITCH_STATE_IND_STRU *pstRcvMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulDisablteRoamFlg;

    pstRcvMsg           = (MSCC_MMC_IMS_SWITCH_STATE_IND_STRU *)pstMsg;
    ulDisablteRoamFlg   = NAS_MML_GetDisableLteRoamFlg();

    /* ����ȫ�ֱ��� */
    NAS_MML_SetLteImsSupportFlg(pstRcvMsg->enImsSwitch);

    /* IMS���ش�ʱ�ж��Ƿ���Ҫ����Enable LTE
       IMS���عر�ʱ������Ҫ�κβ������Ƿ���Ҫdisable LTE����ԭ�����̱�֤��
    */
    if (NAS_MSCC_PIF_IMS_SWITCH_STATE_ON == pstRcvMsg->enImsSwitch)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_ImsSwitchOnOrNotCsOnly())
        {
            /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
            if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
             && (VOS_FALSE == ulDisablteRoamFlg))
            {
                NAS_MMC_SndEnableLteNotify();
                NAS_MMC_ClearDisabledLtePlmnId();
                NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
            }

            /* ͣENABLE LTE��ʱ�� */
            if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
            {
                NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);

            /* �����Ҫ������״̬���ﴥ������ */
            if (VOS_TRUE == NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly())
            {
                return VOS_FALSE;
            }

            /* ����Ҫ����ʱ������TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER
               ���εĳ��������ǣ������л�LTE����������֤ */
            if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
            {
                /* ������ʱ�� */
                if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
                {
                    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                    NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
                }
            }
        }
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccVoiceDomainChangeInd_PreProc
 ��������  : �յ�ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccVoiceDomainChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU              *pstRcvMsg   = VOS_NULL_PTR;
    VOS_UINT32                                              ulDisablteRoamFlg;

    ulDisablteRoamFlg   = NAS_MML_GetDisableLteRoamFlg();

    pstRcvMsg = (NAS_MSCC_PIF_VOICE_DOMAIN_CHANGE_IND_STRU *)pstMsg;

    /* ����ȫ�ֱ���: NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8��MMA_MMC_VOICE_DOMAIN_ENUM_UINT32��ȡֵ��ͬ */
    NAS_MML_SetVoiceDomainPreference((NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8)pstRcvMsg->enVoiceDomain);

    /* ƽ̨��֧��LTEʱ������Ҫ��LTE����ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        /* ֪ͨGMM voice domain�����ı䣬����GMM RAU���� */
        NAS_MMC_SndGmmVoiceDomainChangeNotify();

        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmVoiceDomainChangeInd():NORMAL:Platform Not Support LTE");

        /* ���� */
        return VOS_TRUE;
    }

    /* ֪ͨLMM voice domain�����ı� */
    NAS_MMC_SndLmmVoiceDomainChangeInd((MMC_LMM_VOICE_DOMAIN_ENUM_UINT32)pstRcvMsg->enVoiceDomain);

    /* cs onlyʱ�жϲ����Ƿ���Ҫdisable LTE,��wangchenȷ�ϣ�cs only�ᴥ��LTE��TAU,
       TAU����֮�󲻹����������Ƿ�仯MMA����֪ͨIMSA service change ind��IMSA��֪ͨMMA ims�����ã�mmc�յ�ims��������ȥ�ж��Ƿ���ҪDisable LTE
       ����Disable LTEǰ���ȹ���LTE�����LTE�µ�TAU���� */

    /* ��cs onlyʱ�ж��Ƿ���Ҫenable LTE,������Ӧ�Ĵ��� */
    if (NAS_MSCC_PIF_VOICE_DOMAIN_CS_ONLY != pstRcvMsg->enVoiceDomain)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_ImsSwitchOnOrNotCsOnly())
        {
            /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
            if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
             && (VOS_FALSE == ulDisablteRoamFlg))
            {
                NAS_MMC_SndEnableLteNotify();
                NAS_MMC_ClearDisabledLtePlmnId();
                NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
            }

            /* ͣENABLE LTE��ʱ�� */
            if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
            {
                NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);

            /* �����Ҫ������״̬���ﴥ������ */
            if (VOS_TRUE == NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly())
            {
                return VOS_FALSE;
            }

            /* ����Ҫ����ʱ������TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER
               ���εĳ��������ǣ������л�LTE����������֤ */
            if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
            {
                /* ������ʱ�� */
                if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
                {
                    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                    NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
                }
            }
        }
    }

    /* ��ҪȥLTE����ʱ����֪ͨGMM voice domain�仯�������������̻��RAU���̳�ͻ
       �����ٻ���GU��ʱ�����voice domain��֮ǰ����rauʱ��voice domain��ͬ���ᴥ��GU��������RAU
       �������ʱ֪ͨGMM voice domain�����ı䣬����GMM RAU���� */
    NAS_MMC_SndGmmVoiceDomainChangeNotify();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCFPlmnSetReq_PreProc
 ��������  : �û�ָ��plmn����������
 �������  : ulEventType: ��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��5��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCFPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_CFPLMN_SET_REQ_STRU       *pstCFPlmnReqMsg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulChgFlag;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnList = VOS_NULL_PTR;

    pstCFPlmnReqMsg = (MSCC_MMC_CFPLMN_SET_REQ_STRU *)pstMsg;

    /* ָ���û�ָ����PlmnId */
    pstUserSpecPlmnId = (NAS_MML_PLMN_ID_STRU *)(&pstCFPlmnReqMsg->stPlmnInfo);

    if (NAS_MSCC_PIF_CFPLMN_TYPE_ADD_ONE == pstCFPlmnReqMsg->enCmdType)
    {
        /* ����forbidden plmn list�е�plmn����hplmn�ż���,�����ֹ���� */
        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn((NAS_MML_PLMN_ID_STRU *)pstUserSpecPlmnId))
        {
            /* �ϱ����ý����*/
            NAS_MMC_SndMsccCFPlmnSetCnf(NAS_MSCC_PIF_CFPLMN_OPER_RESULT_FAILURE);
            return VOS_TRUE;
        }

        /* �����ֹ�б� */
        ulChgFlag = NAS_MML_AddForbPlmn((NAS_MML_PLMN_ID_STRU *)pstUserSpecPlmnId);

        if (VOS_TRUE == ulChgFlag)
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }
    }
    else if ((NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ONE == pstCFPlmnReqMsg->enCmdType)
          || (NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ALL == pstCFPlmnReqMsg->enCmdType))
    {
        ulChgFlag = VOS_FALSE;

        /* ��ȡ��Ҫɾ����PLMN */
        pstForbidPlmnList = NAS_MML_GetForbidPlmnInfo();

        /* �����ɾ�����н�ֹPLMN��ֱ�ӵ���ɾ�����н�ֹPLMN�����������ؽ�� */
        if (NAS_MSCC_PIF_CFPLMN_TYPE_DEL_ALL == pstCFPlmnReqMsg->enCmdType)
        {
            if (0 != pstForbidPlmnList->ucForbPlmnNum)
            {
                pstForbidPlmnList->ucForbPlmnNum = 0;
                ulChgFlag = VOS_TRUE;
            }
        }
        else
        {
            ulChgFlag = NAS_MML_DelForbPlmn(pstUserSpecPlmnId);
        }

        if (VOS_TRUE == ulChgFlag)
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }
    }
    else
    {
        NAS_MMC_SndMsccCFPlmnSetCnf(NAS_MSCC_PIF_CFPLMN_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    NAS_MMC_SndMsccCFPlmnSetCnf(NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCFPlmnQueryReq_PreProc
 ��������  : �û�ָ��plmn����������
 �������  : ulEventType: ��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ����״̬������
             VOS_FALSE: ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��5��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCFPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnList = VOS_NULL_PTR;
    VOS_UINT8                           ucForbPlmnNum;
    NAS_MSCC_PIF_CFPLMN_LIST_STRU       stCFPlmnListInfo;

    PS_MEM_SET(&stCFPlmnListInfo, 0x00, sizeof(NAS_MSCC_PIF_CFPLMN_LIST_STRU));

    /* ��ȡ��ֹ�б��� */
    pstForbidPlmnList                = NAS_MML_GetForbidPlmnInfo();
    stCFPlmnListInfo.ucPlmnNum       = pstForbidPlmnList->ucForbPlmnNum;

    if (stCFPlmnListInfo.ucPlmnNum > NAS_MSCC_PIF_MAX_CFPLMN_NUM)
    {
        stCFPlmnListInfo.ucPlmnNum = NAS_MSCC_PIF_MAX_CFPLMN_NUM;
    }

    for (ucForbPlmnNum = 0; ((ucForbPlmnNum < stCFPlmnListInfo.ucPlmnNum) && (ucForbPlmnNum < NAS_MML_MAX_FORBPLMN_NUM)); ucForbPlmnNum++)
    {
        stCFPlmnListInfo.astPlmn[ucForbPlmnNum].ulMcc = pstForbidPlmnList->astForbPlmnIdList[ucForbPlmnNum].ulMcc;
        stCFPlmnListInfo.astPlmn[ucForbPlmnNum].ulMnc = pstForbidPlmnList->astForbPlmnIdList[ucForbPlmnNum].ulMnc;
    }

    NAS_MMC_SndMsccCFPlmnQueryCnf(NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS, &stCFPlmnListInfo);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSDTConnInd_PreProc
 ��������  : �յ�ID_MSCC_MMC_SDT_CONNECTED_IND��Ԥ����
 �������  : ulEventType:   ��Ϣ����
             pstMsg:        ��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��5��
   ��    ��   : f00279542
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafSDTConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlg;

    ulRrcConnExistFlg = NAS_MML_IsRrcConnExist();

    pstConnStatus     = NAS_MML_GetConnStatus();

    /* PS���е�ǰҵ�����, �򲻷��ͻط���Ϣ */
    if ((VOS_TRUE == pstConnStatus->ucPdpStatusFlg)
      &&(VOS_TRUE == ulRrcConnExistFlg))
    {
        return VOS_TRUE;
    }

    /* UTRANCTRLģ��Ļط���Ϣ */
    NAS_UTRANCTRL_SndOutsideContextData();

    NAS_MMC_SndOutsideContextData();
    NAS_MM_SndOutsideContextData();
    NAS_GMM_SndOutsideContextData();

    /* �������״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FillPrefPlmnFile
 ��������  : ��USIM����ʽ������ȼ��б��ļ�����
 �������  : VOS_UINT16                           usUpdateFile,
             VOS_UINT8                           *pucEfFile,
             NAS_MSCC_PIF_USER_PLMN_LIST_STRU    *pstUPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_VOID NAS_MMC_FillPrefPlmnFile(
    VOS_UINT16                          usUpdateFile,
    VOS_UINT8                          *pucEfFile,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU   *pstUPlmnInfo
)
{
    VOS_UINT8                           ucRecordLen;
    VOS_UINT16                          i;
    VOS_UINT16                          usRatMode;

    if (USIMM_GSM_EFPLMNSEL_ID == usUpdateFile)
    {
        ucRecordLen = 3;
    }
    else
    {
        ucRecordLen = 5;
    }

    for (i = 0; i < pstUPlmnInfo->usPlmnNum; i++)
    {
        pucEfFile[i*ucRecordLen]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].ulMcc >> 4));
        pucEfFile[i*ucRecordLen] <<= 4;
        pucEfFile[i*ucRecordLen] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].ulMcc >> 8));

        pucEfFile[(i*ucRecordLen)+1]  = (VOS_UINT8)(0x0f & pstUPlmnInfo->Plmn[i].ulMcc);
        if (0xF0 == (0xf0 & (pstUPlmnInfo->Plmn[i].ulMnc >>4)))
        {
            pucEfFile[(i*ucRecordLen)+1] |= (VOS_UINT8)(0xf0 & (pstUPlmnInfo->Plmn[i].ulMnc >>4));

            pucEfFile[(i*ucRecordLen)+2]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].ulMnc));
            pucEfFile[(i*ucRecordLen)+2] <<= 4;
            pucEfFile[(i*ucRecordLen)+2] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].ulMnc >>4));
        }
        else
        {
            pucEfFile[(i*ucRecordLen)+1] |= (VOS_UINT8)(0xf0 & (pstUPlmnInfo->Plmn[i].ulMnc <<4));

            pucEfFile[(i*ucRecordLen)+2]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].ulMnc >>4));
            pucEfFile[(i*ucRecordLen)+2] <<= 4;
            pucEfFile[(i*ucRecordLen)+2] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].ulMnc >>8));
        }

        if (5 == ucRecordLen)
        {
            usRatMode = pstUPlmnInfo->ausPlmnRat[i];
            pucEfFile[(i*ucRecordLen)+3] = (VOS_UINT8)(usRatMode >> 8);
            pucEfFile[(i*ucRecordLen)+4] = (VOS_UINT8)(usRatMode & 0xFF);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUsimPrefPlmn
 ��������  : ����USIM pref plmn
 �������  : VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
             TAF_USER_PLMN_LIST_STRU            *pstUPlmnInfo,
             VOS_UINT16                          usUpdateFile
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_UpdateUsimPrefPlmn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU   *pstUPlmnInfo,
    VOS_UINT16                          usUpdateFile
)
{
    VOS_UINT8                          *pucEfFile;
    VOS_UINT16                          usEfLen;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    if ((USIMM_USIM_EFPLMNWACT_ID == usUpdateFile)
      || (USIMM_USIM_EFOPLMNWACT_ID == usUpdateFile)
      || (USIMM_USIM_EFHPLMNwACT_ID == usUpdateFile)
      || (USIMM_GSM_EFPLMNWACT_ID == usUpdateFile)
      || (USIMM_GSM_EFOPLMNWACT_ID == usUpdateFile)
      || (USIMM_GSM_EFHPLMNACT_ID == usUpdateFile))
    {
        usEfLen = (VOS_UINT16)(5 * (pstUPlmnInfo->usPlmnNum));
    }
    else
    {
        /*PlmnSel*/
        usEfLen = (VOS_UINT16)(3 * (pstUPlmnInfo->usPlmnNum));
    }

    pucEfFile = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, usEfLen);
    if (VOS_NULL_PTR == pucEfFile)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pucEfFile, 0, usEfLen);

    NAS_MMC_FillPrefPlmnFile(usUpdateFile, pucEfFile, pstUPlmnInfo);

    stSetFileInfo.usEfId       = usUpdateFile;
    stSetFileInfo.ucRecordNum  = 0;
    stSetFileInfo.enAppType    = USIMM_GUTL_APP;
    stSetFileInfo.ucRsv        = 0;
    stSetFileInfo.ulEfLen      = usEfLen;
    stSetFileInfo.pucEfContent = pucEfFile;

    if(USIMM_API_SUCCESS != NAS_USIMMAPI_SetFileReq(WUEPS_PID_MMC, 0, &stSetFileInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucEfFile);
        return VOS_FALSE;
    }

    /* ������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF, TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF_LEN);

    PS_MEM_FREE(WUEPS_PID_MMC, pucEfFile);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ModPrefPlmnInfo
 ��������  : �յ�ID_MSCC_MMC_PREF_PLMN_SET_REQ��Ϣ��Ԥ����
 �������  : MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_ModPrefPlmnInfo(
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
)
{
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                    *pstPrefPlmnOpt           = VOS_NULL_PTR;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo              = VOS_NULL_PTR;
    VOS_UINT16                                              usMaxIndex;
    VOS_UINT16                                              usUpdateFile;
    VOS_UINT32                                              i;
    MMC_MODIFY_PLMN_INFO_STRU                              *pstPrefPlmnCtx;


    pstPrefPlmnOpt      = &(pstPrefPlmnSetReq->stPrefPlmnOpt);

    pstPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));
    if (VOS_NULL_PTR == pstPlmnInfo)
    {
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_MEM_ALLOC_FAIL;
    }

    PS_MEM_SET(pstPlmnInfo, 0x00, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));
    if (VOS_FALSE == NAS_MMC_GetPlmnInfo(pstPrefPlmnSetReq->enPrefPlmnParaType, pstPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_GET_PLMNINFO_FAIL;
    }

    usMaxIndex = pstPlmnInfo->usPlmnNum;

    if ((pstPrefPlmnOpt->ulIndex > usMaxIndex)
     || (0 == pstPrefPlmnOpt->ulIndex))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMN_INDEX_ERR;
    }

    NAS_MMC_PlmnId2NasStyle(&pstPrefPlmnOpt->stPlmn);
    NAS_MMC_PlmnId2Bcd(&pstPrefPlmnOpt->stPlmn);

    /* �ж��޸ĵ�PLMN ID�Ƿ�͵�ǰ���е�PLMN ID�ظ�,����ظ����������� */
    for (i = 0; i < usMaxIndex ; i++)
    {
        /* ��ǰ���޸�������ж� */
        if (i == (pstPrefPlmnOpt->ulIndex - 1))
        {
            continue;
        }

        /* ��������Pref PLMN��Ϣ�ظ�ʱֱ�ӷ���error  */
        if ((pstPlmnInfo->Plmn[i].ulMcc == pstPrefPlmnOpt->stPlmn.ulMcc)
          && (pstPlmnInfo->Plmn[i].ulMnc == pstPrefPlmnOpt->stPlmn.ulMnc)
          && ((pstPlmnInfo->ausPlmnRat[i] == pstPrefPlmnOpt->usRat)
          || (0 != (pstPlmnInfo->ausPlmnRat[i] & (pstPrefPlmnOpt->usRat)))))
        {

            PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);
            return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SAME_PLMNID;
        }
    }

    /* �����޸ĺ��PLMN ID */
    pstPlmnInfo->Plmn[pstPrefPlmnOpt->ulIndex - 1].ulMcc = pstPrefPlmnOpt->stPlmn.ulMcc;
    pstPlmnInfo->Plmn[pstPrefPlmnOpt->ulIndex - 1].ulMnc = pstPrefPlmnOpt->stPlmn.ulMnc;
    pstPlmnInfo->ausPlmnRat[pstPrefPlmnOpt->ulIndex - 1] = pstPrefPlmnOpt->usRat;

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();
    pstPrefPlmnCtx->stPlmnId.ulMcc = pstPlmnInfo->Plmn[pstPrefPlmnOpt->ulIndex - 1].ulMcc ;
    pstPrefPlmnCtx->stPlmnId.ulMnc = pstPlmnInfo->Plmn[pstPrefPlmnOpt->ulIndex - 1].ulMnc;
    pstPrefPlmnCtx->PlmnRat        = pstPlmnInfo->ausPlmnRat[pstPrefPlmnOpt->ulIndex - 1];
    pstPrefPlmnCtx->usIndex        = (VOS_UINT16)(pstPrefPlmnOpt->ulIndex - 1);

    usUpdateFile = NAS_MMC_GetUpdateFileForPrefPlmn(pstPrefPlmnSetReq->enPrefPlmnParaType);

    if (VOS_TRUE != NAS_MMC_UpdateUsimPrefPlmn(pstPrefPlmnSetReq->stCtrl.usClientId,
                                                pstPrefPlmnSetReq->stCtrl.ucOpId,
                                                pstPlmnInfo,
                                                usUpdateFile))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_UPDATA_USIM_PLMN;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

    return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_DelPrefPlmnInfo
 ��������  : �յ�ID_MSCC_MMC_PREF_PLMN_SET_REQ��Ϣ��Ԥ����
 �������  : MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_DelPrefPlmnInfo(
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
)
{
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                    *pstPrefPlmnOpt = VOS_NULL_PTR;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo    = VOS_NULL_PTR;
    VOS_UINT16                                              usIndex        = 0;
    VOS_UINT16                                              usMaxIndex;
    VOS_UINT16                                              usUpdateFile;
    MMC_MODIFY_PLMN_INFO_STRU                              *pstPrefPlmnCtx;

    pstPrefPlmnOpt      = &(pstPrefPlmnSetReq->stPrefPlmnOpt);

    pstPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));
    if (VOS_NULL_PTR == pstPlmnInfo)
    {
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_MEM_ALLOC_FAIL;
    }

    PS_MEM_SET(pstPlmnInfo, 0x00, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    if (VOS_FALSE == NAS_MMC_GetPlmnInfo(pstPrefPlmnSetReq->enPrefPlmnParaType, pstPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_GET_PLMNINFO_FAIL;
    }

    usMaxIndex  = pstPlmnInfo->usPlmnNum;

    if (((VOS_UINT16)pstPrefPlmnOpt->ulIndex > usMaxIndex)
     || ((VOS_UINT16)pstPrefPlmnOpt->ulIndex == 0))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMN_INDEX_ERR;
    }

    usIndex = (VOS_UINT16)(pstPrefPlmnOpt->ulIndex - 1);

    /* ����PLMN IDΪ��Чֵ */
    pstPlmnInfo->Plmn[usIndex].ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnInfo->Plmn[usIndex].ulMnc = NAS_MML_INVALID_MNC;
    pstPlmnInfo->ausPlmnRat[usIndex] = NAS_MMC_USIM_NO_RAT;

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();
    pstPrefPlmnCtx->stPlmnId.ulMcc   = pstPlmnInfo->Plmn[usIndex].ulMcc ;
    pstPrefPlmnCtx->stPlmnId.ulMnc   = pstPlmnInfo->Plmn[usIndex].ulMnc;
    pstPrefPlmnCtx->PlmnRat          = pstPlmnInfo->ausPlmnRat[usIndex];
    pstPrefPlmnCtx->usIndex          = usIndex;

    usUpdateFile = NAS_MMC_GetUpdateFileForPrefPlmn(pstPrefPlmnSetReq->enPrefPlmnParaType);

    if (VOS_TRUE != NAS_MMC_UpdateUsimPrefPlmn(pstPrefPlmnSetReq->stCtrl.usClientId,
                                               pstPrefPlmnSetReq->stCtrl.ucOpId,
                                               pstPlmnInfo,
                                               usUpdateFile))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_UPDATA_USIM_PLMN;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);
    return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddPrefPlmnInfo
 ��������  : �յ�ID_MSCC_MMC_PREF_PLMN_SET_REQ��Ϣ��Ԥ����
 �������  : MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_AddPrefPlmnInfo(
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
)
{
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                    *pstPrefPlmnOpt           = VOS_NULL_PTR;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo              = VOS_NULL_PTR;
    VOS_UINT16                                              usMaxIndex;
    VOS_UINT16                                              usUpdateFile;
    VOS_BOOL                                                bFindInvalidPlmn;
    VOS_UINT16                                              usFindIndex;
    VOS_BOOL                                                bFindSamePlmnId;
    VOS_UINT32                                              i;
    MMC_MODIFY_PLMN_INFO_STRU                              *pstPrefPlmnCtx;

    pstPrefPlmnOpt      = &(pstPrefPlmnSetReq->stPrefPlmnOpt);

    pstPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));
    if (VOS_NULL_PTR == pstPlmnInfo)
    {
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_MEM_ALLOC_FAIL;
    }

    PS_MEM_SET(pstPlmnInfo, 0, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    if (VOS_FALSE == NAS_MMC_GetPlmnInfo(pstPrefPlmnSetReq->enPrefPlmnParaType, pstPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_GET_PLMNINFO_FAIL;
    }

    usMaxIndex        = pstPlmnInfo->usPlmnNum;

    bFindInvalidPlmn  = VOS_FALSE;
    usFindIndex       = 0;
    bFindSamePlmnId   = VOS_FALSE;

    NAS_MMC_PlmnId2NasStyle(&pstPrefPlmnOpt->stPlmn);
    NAS_MMC_PlmnId2Bcd(&pstPrefPlmnOpt->stPlmn);

    /* ��Ѱ���е�PLMN ID */
    for (i = 0; i < usMaxIndex; i++)
    {
        if (VOS_FALSE == bFindInvalidPlmn)
        {
            if (VOS_FALSE == NAS_MMC_IsPlmnValid(&(pstPlmnInfo->Plmn[i])))
            {
                /* PLMN ID��Ч */
                usFindIndex = (VOS_UINT16)i;
                bFindInvalidPlmn = VOS_TRUE;
            }
        }

        /* ������ͬPLMN�Ľ��뼼�����ж� */
        if ((pstPlmnInfo->Plmn[i].ulMcc == pstPrefPlmnOpt->stPlmn.ulMcc)
          && (pstPlmnInfo->Plmn[i].ulMnc == pstPrefPlmnOpt->stPlmn.ulMnc)
          && ((pstPlmnInfo->ausPlmnRat[i] == pstPrefPlmnOpt->usRat)
          || (0 != (pstPlmnInfo->ausPlmnRat[i] & (pstPrefPlmnOpt->usRat)))))
        {
            bFindSamePlmnId = VOS_TRUE;
            break;
        }
    }

    if ((VOS_FALSE == bFindInvalidPlmn)
      || (VOS_TRUE == bFindSamePlmnId))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_PLMNID_INVAILD;
    }

    /* �������Ӻ��PLMN IDֵ */
    pstPlmnInfo->Plmn[usFindIndex].ulMcc = pstPrefPlmnOpt->stPlmn.ulMcc;
    pstPlmnInfo->Plmn[usFindIndex].ulMnc = pstPrefPlmnOpt->stPlmn.ulMnc;
    pstPlmnInfo->ausPlmnRat[usFindIndex] = pstPrefPlmnOpt->usRat;

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();
    pstPrefPlmnCtx->stPlmnId.ulMcc       = pstPlmnInfo->Plmn[usFindIndex].ulMcc ;
    pstPrefPlmnCtx->stPlmnId.ulMnc       = pstPlmnInfo->Plmn[usFindIndex].ulMnc;
    pstPrefPlmnCtx->PlmnRat              = pstPlmnInfo->ausPlmnRat[usFindIndex];
    pstPrefPlmnCtx->usIndex              = usFindIndex;

    usUpdateFile = NAS_MMC_GetUpdateFileForPrefPlmn(pstPrefPlmnSetReq->enPrefPlmnParaType);

    if (VOS_TRUE != NAS_MMC_UpdateUsimPrefPlmn(pstPrefPlmnSetReq->stCtrl.usClientId,
                                                pstPrefPlmnSetReq->stCtrl.ucOpId,
                                                pstPlmnInfo,
                                                usUpdateFile))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);
        return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_UPDATA_USIM_PLMN;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnInfo);

    return NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPrefPlmnSetReq_PreProc
 ��������  : �յ�ID_MSCC_MMC_PREF_PLMN_SET_REQ��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPrefPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU                        *pstPrefPlmnSetReq       = VOS_NULL_PTR;
    NAS_MSCC_PIF_PREF_PLMN_OPERATE_STRU                    *pstPrefPlmnOperate      = VOS_NULL_PTR;
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt;

    pstPrefPlmnSetReq       = (MSCC_MMC_PREF_PLMN_SET_REQ_STRU *)pstMsg;
    pstPrefPlmnOperate      = &(pstPrefPlmnSetReq->stPrefPlmnOpt);

    if (NAS_MSCC_PREF_PLMN_DEL_ONE == pstPrefPlmnOperate->enPrefPlmnOperType)
    {
        enRslt = NAS_MMC_DelPrefPlmnInfo(pstPrefPlmnSetReq);
    }
    else if (NAS_MSCC_PREF_PLMN_MODIFY_ONE == pstPrefPlmnOperate->enPrefPlmnOperType)
    {
        enRslt = NAS_MMC_ModPrefPlmnInfo(pstPrefPlmnSetReq);
    }
    else if (NAS_MSCC_PREF_PLMN_ADD_ONE == pstPrefPlmnOperate->enPrefPlmnOperType)
    {
        enRslt = NAS_MMC_AddPrefPlmnInfo(pstPrefPlmnSetReq);
    }
    else
    {
        enRslt = NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_FAILURE;
    }

    if (NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS != enRslt)
    {
        NAS_MMC_SndMsccPrefPlmnSetCnf(enRslt);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPrefPlmnQueryReq_PreProc
 ��������  : �յ�ID_MSCC_MMC_PREF_PLMN_QUERY_REQ��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPrefPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU  *pstPrefPlmnQueryReq = VOS_NULL_PTR;
    MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU  *pstPrefPlmnQueryRsp = VOS_NULL_PTR;
    VOS_UINT32                          ulPlmnNum;
    VOS_UINT32                          ulRemainPlmnNum;
    VOS_UINT32                          ulTotal;

    pstPrefPlmnQueryReq = (MSCC_MMC_PREF_PLMN_QUERY_REQ_STRU*)pstMsg;

    /* ���÷��������־�ͷ����ϱ���Ӫ�̸���: �����͵���Ӫ��������һ����Ϣ��
        �����͵���Ӫ�����������ý�����־���������д�������Ӫ����Ϣ */
    ulTotal = NAS_MMC_GetSpecificPlmnTblSize(pstPrefPlmnQueryReq->stCpolInfo.enPrefPLMNType);

    if (pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex > ulTotal)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPrefPlmnQueryReq_PreProc: abnormal request!");

        ulPlmnNum = 0;
    }
    else
    {
        ulRemainPlmnNum = ulTotal - pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex;

        if (ulRemainPlmnNum < pstPrefPlmnQueryReq->stCpolInfo.ulPlmnNum)
        {
            ulPlmnNum   = ulRemainPlmnNum;
        }
        else
        {
            ulPlmnNum   = pstPrefPlmnQueryReq->stCpolInfo.ulPlmnNum;
        }
    }

    pstPrefPlmnQueryRsp = (MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnQueryRsp)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPrefPlmnQueryReq_PreProc ERROR:Memory Alloc Error for pstPrefPlmnQueryRsp ");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8*)pstPrefPlmnQueryRsp) + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    pstPrefPlmnQueryRsp->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryRsp->stMsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstPrefPlmnQueryRsp->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnQueryRsp->stMsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstPrefPlmnQueryRsp->stMsgHeader.ulLength          = sizeof(MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPrefPlmnQueryRsp->stMsgHeader.ulMsgName         = ID_MMC_MSCC_PREF_PLMN_QUERY_CNF;

    /* �����Ϣ���� */
    pstPrefPlmnQueryRsp->enCmdType                     = pstPrefPlmnQueryReq->enCmdType;
    pstPrefPlmnQueryRsp->ulFromIndex                   = pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex;
    pstPrefPlmnQueryRsp->ulValidPlmnNum                = pstPrefPlmnQueryReq->stCpolInfo.ulValidPlmnNum;
    pstPrefPlmnQueryRsp->stPlmnName.bPlmnSelFlg        = pstPrefPlmnQueryReq->bPlmnSelFlg;

    /* ��ȡpref plmn */
    if (VOS_TRUE != NAS_MMC_QryPrefPlmnId(pstPrefPlmnQueryReq->stCpolInfo.enPrefPLMNType,
                            pstPrefPlmnQueryReq->stCpolInfo.ulFromIndex,
                            ulPlmnNum,
                            &pstPrefPlmnQueryRsp->stPlmnName))
    {
        pstPrefPlmnQueryRsp->enRslt = NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_FAILURE;
    }
    else
    {
        pstPrefPlmnQueryRsp->usPlmnNum            = (VOS_UINT16)pstPrefPlmnQueryRsp->stPlmnName.ulPlmnNum;
        pstPrefPlmnQueryRsp->stPlmnName.ulPlmnNum = ulPlmnNum;
        pstPrefPlmnQueryRsp->enRslt = NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMC, pstPrefPlmnQueryRsp);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvUsimSetFileCnf_PreProc
 ��������  : �յ�USIMM_UPDATEFILE_CNF��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvUsimSetFileCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileCnf;
    VOS_UINT32                          ulEfId;
    VOS_UINT32                          ulRet;

    pUsimSetFileCnf = (USIMM_UPDATEFILE_CNF_STRU *)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pUsimSetFileCnf->stFilePath.ulPathLen, pUsimSetFileCnf->stFilePath.acPath, &ulEfId))
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF))
    {
        if ((USIMM_GSM_EFPLMNSEL_ID    == ulEfId)
         || (USIMM_USIM_EFPLMNWACT_ID  == ulEfId)
         || (USIMM_GSM_EFPLMNWACT_ID   == ulEfId)
         || (USIMM_USIM_EFOPLMNWACT_ID == ulEfId)
         || (USIMM_GSM_EFOPLMNWACT_ID  == ulEfId)
         || (USIMM_USIM_EFHPLMNwACT_ID == ulEfId)
         || (USIMM_GSM_EFHPLMNACT_ID   == ulEfId))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_USIM_SET_FILE_CNF);

            /* �ж���Ϣ��Ч�� */
            if (VOS_OK != pUsimSetFileCnf->stCmdResult.ulResult)
            {
                ulRet = pUsimSetFileCnf->stCmdResult.ulErrorCode;
            }
            else
            {
                ulRet = VOS_OK;

                /* �����ڴ��еı��� */
                NAS_MMC_UpdatePlmnInfo((VOS_UINT16)ulEfId);
            }

            /*���û�������Ϣ*/
            NAS_MMC_SndMsccPrefPlmnSetCnf(ulRet);

            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_WaitUsimSetFileExpired_PreProc
 ��������  : MMC�ȴ�Usim Set File��ʱ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��08��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_WaitUsimSetFileExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*���û�������Ϣ*/
    NAS_MMC_SndMsccPrefPlmnSetCnf(NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_TIMEOUT);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccPlmnPriClassQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU                 *pstPlmnPriClassQryReq;
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU              stPlmnPriClassListInfo;
    NAS_MML_PLMN_ID_STRU                                    stTmpPlmnId;
    VOS_UINT8                                               i;

    pstPlmnPriClassQryReq = (MSCC_MMC_PLMN_PRI_CLASS_QUERY_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stPlmnPriClassListInfo, 0x0, sizeof(NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU));

    stPlmnPriClassListInfo.ucHighPlmnNum = NAS_MML_MIN(pstPlmnPriClassQryReq->stPlmnListInfo.ucHighPlmnNum, NAS_MSCC_PIF_MAX_HIGH_QUALITY_PLMN_NUM);

    for (i = 0; i < stPlmnPriClassListInfo.ucHighPlmnNum; i++)
    {
        stTmpPlmnId.ulMcc = pstPlmnPriClassQryReq->stPlmnListInfo.astHighPlmnID[i].ulMcc;
        stTmpPlmnId.ulMnc = pstPlmnPriClassQryReq->stPlmnListInfo.astHighPlmnID[i].ulMnc;

        stPlmnPriClassListInfo.astHighPlmnPriClassInfo[i].stPlmnId = pstPlmnPriClassQryReq->stPlmnListInfo.astHighPlmnID[i];

        /* first check if it's forbidden plmn */
        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&stTmpPlmnId))
        {
            stPlmnPriClassListInfo.astHighPlmnPriClassInfo[i].ucIsForbidden = VOS_TRUE;
        }

        stPlmnPriClassListInfo.astHighPlmnPriClassInfo[i].enPriClass = NAS_MMC_GetPlmnPrioClass(&stTmpPlmnId);
    }

    stPlmnPriClassListInfo.ucLowPlmnNum = NAS_MML_MIN(pstPlmnPriClassQryReq->stPlmnListInfo.ucLowPlmnNum, NAS_MSCC_PIF_MAX_LOW_QUALITY_PLMN_NUM);

    for (i = 0; i < stPlmnPriClassListInfo.ucLowPlmnNum; i++)
    {
        stTmpPlmnId.ulMcc = pstPlmnPriClassQryReq->stPlmnListInfo.astLowPlmnID[i].ulMcc;
        stTmpPlmnId.ulMnc = pstPlmnPriClassQryReq->stPlmnListInfo.astLowPlmnID[i].ulMnc;

        stPlmnPriClassListInfo.astLowPlmnPriClassInfo[i].stPlmnId = pstPlmnPriClassQryReq->stPlmnListInfo.astLowPlmnID[i];

        /* first check if it's forbidden plmn */
        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&stTmpPlmnId))
        {
            stPlmnPriClassListInfo.astLowPlmnPriClassInfo[i].ucIsForbidden = VOS_TRUE;
        }

        stPlmnPriClassListInfo.astLowPlmnPriClassInfo[i].enPriClass = NAS_MMC_GetPlmnPrioClass(&stTmpPlmnId);
    }

    stPlmnPriClassListInfo.enRat = pstPlmnPriClassQryReq->stPlmnListInfo.enRat;

    NAS_MMC_SndMsccQueryPlmnPriClassCnf(&stPlmnPriClassListInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccAutoReselSetReq_PreProc
 ��������  : �յ�ID_MSCC_MMC_AUTO_RESEL_SET_REQ��Ϣ��Ԥ����
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��5��30��
    ��    ��   : b00269685
    �޸�����   : new
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccAutoReselSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_AUTO_RESEL_SET_REQ_STRU   *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg   = (MSCC_MMC_AUTO_RESEL_SET_REQ_STRU *)pstMsg;

    NAS_MML_SetUserAutoReselActiveFlg(pstRcvMsg->ucActiveFlg);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)

VOS_UINT32  NAS_MMC_RcvMsccBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulPsServiceExist;
    MSCC_MMC_BG_SEARCH_REQ_STRU        *pstMsccMmcBgSearchReq = VOS_NULL_PTR;

    pstMsccMmcBgSearchReq = (MSCC_MMC_BG_SEARCH_REQ_STRU *)pstMsg;

    /* current, PS service is exist,abort search network, response mscc abort */
    ulPsServiceExist = NAS_MML_GetPsServiceExistFlg();
    if (VOS_TRUE == ulPsServiceExist)
    {
        NAS_MMC_SndMsccBgSearchCnf(MMC_LMM_BG_SRCH_RLT_ABORT, 0, VOS_NULL_PTR);
        return VOS_TRUE;
    }

    /* judge enRatMode,must be hrpd */
    if (VOS_RATMODE_HRPD != pstMsccMmcBgSearchReq->enRatMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "pstMsccMmcBgSearchReq->enRatMode is not HRPD");
        NAS_MMC_SndMsccBgSearchCnf(MMC_LMM_BG_SRCH_RLT_FAIL, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }
    /* send MMC_LMM_BG_SEARCH_HRPD_REQ message to lmm */
    NAS_MMC_SndLmmBgSearchHrpdReq();

    /* send request message, start protect timer */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF,
                                   TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmBgSearchHrpdCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_BG_SEARCH_HRPD_CNF_STRU    *pstLmmMmcBgSearchHrpdCnf = VOS_NULL_PTR;

    /* recived response message, stop timer */
    (VOS_VOID)NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF);

    pstLmmMmcBgSearchHrpdCnf = (LMM_MMC_BG_SEARCH_HRPD_CNF_STRU *)pstMsg;

    /* send MMC_MSCC_BG_SEARCH_HRPD_CNF message to mscc */
    NAS_MMC_SndMsccBgSearchCnf(pstLmmMmcBgSearchHrpdCnf->enRlst, pstLmmMmcBgSearchHrpdCnf->ucHrpdSysNum,
        pstLmmMmcBgSearchHrpdCnf->astHrpdSysList);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmStopBgSearchHrpdCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* send MMC_MSCC_STOP_BG_SEARCH_HRPD_CNF message to mscc */
    NAS_MMC_SndMsccStopBgSearchCnf();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMsccStopBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop the Wait LMM Stop BG Search Protect timer */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_SEARCH_HRPD_CNF);

    /* send MMC_LMM_STOP_BG_SEARCH_HRPD_REQ message to LMM */
    NAS_MMC_SndLmmStopBgSearchHrpdReq();

    /* ��LMM����stopbgsearchreq��Ϣ��������������ʱ�������û���յ�cnf��Ϣ��
        �ϲ�msccģ����Լ���ʱ�����볬ʱ����
    */


    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_WaitLmmBgSearchHrpdExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_WaitLmmBgSearchHrpdExpired_PreProc: timer expired!");

    /* protect timer expired, directly response fail to mscc */
    NAS_MMC_SndMsccBgSearchCnf(MMC_LMM_BG_SRCH_RLT_FAIL, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmPlmnSearchInd_PreProc
 ��������  : �յ�MMģ������ָʾ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmPlmnSearchInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    /* �жϵ�ǰ�Ƿ���Ҫ��ϵ�ǰ״̬�� �������Ϣ�Ļ��� */
    ulRet = NAS_MMC_ProcMsgPrio(ulEventType, pstMsg);

    /* ��Ҫ��ϵ�ǰ״̬���������Ϣ�Ļ���,���ʾԤ������� */
    if (VOS_TRUE == ulRet)
    {
        return VOS_TRUE;
    }

    /* ��Ҫ�������״̬������ */
    return VOS_FALSE;
}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

