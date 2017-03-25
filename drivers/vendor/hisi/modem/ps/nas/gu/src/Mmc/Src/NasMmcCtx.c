
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcCtx.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��04��22��
  ����޸�   :
  ��������   : NAS MMC CTX�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasCommDef.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcMain.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcFsmGetGeoTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcFsmPowerOff.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#include "NasMmcFsmPlmnSelection.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* MMC CTX,���ڱ���MMC״̬��,������ */
NAS_MMC_CONTEXT_STRU                    g_stNasMmcCtx;

/*lint -save -e958 */

/*****************************************************************************
 ȫ�ֱ�����    : g_aulFsmEntryEventType
 ȫ�ֱ���˵��  : ״̬���������Ϣ
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���
 3.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/

VOS_UINT32 g_aulFsmEntryEventType[] =
{
    NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),

    NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_CSG)
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
    NAS_BuildEventType(UEPS_PID_MSCC, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
#endif
    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_LIST_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ),
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_ANYCELL_SEARCH_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HPLMN_TIMER),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_GET_GEO_REQ),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND)
#endif
};


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMmcCtxAddr
 ��������  : ��ȡ��ǰMMC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰMMC��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_CONTEXT_STRU* NAS_MMC_GetMmcCtxAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRegCtrlAddr
 ��������  : ��ȡ��ǰ״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetCurFsmAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmStackAddr
 ��������  : ��ȡ��ǰ״̬��ջ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬��ջ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_STACK_STRU* NAS_MMC_GetFsmStackAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stFsmStack);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurFsmDesc
 ��������  : ��ȡ��ǰ״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* NAS_MMC_GetCurFsmDesc(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrFsmMsgAddr
 ��������  : ��ȡ��ǰ״̬�������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrFsmMsgAddr
 ��������  : ��ȡ��ǰ״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetCurrFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enFsmId);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrFsmEventType
 ��������  : ��ȡ��ǰ״̬������Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��29��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCurrFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.stEntryMsg.ulEventType);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetParentFsmId
 ��������  : ��ȡ�ϲ�״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ϲ�״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��29��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetParentFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enParentFsmId);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetParentFsmEventType
 ��������  : ��ȡ�ϲ�״̬������Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ϲ�״̬������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��29��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetParentFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.ulParentEventType);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetParentFsmCtx
 ��������  : ��ȡ�ϲ�״̬��������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ϲ�״̬������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_EXTRA_CTX_UNION* NAS_MMC_GetParentFsmCtx(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.punParentFsmCtx);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCachMsgBufferAddr
 ��������  : ��ȡ��ǰ�Ļ�����Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS MMC������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_MSG_QUEUE_STRU* NAS_MMC_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBufferEntryMsgQueue);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_PushFsm
 ��������  : ��״̬������ѹջ
 �������  : *pstFsmStack:״̬��ջ
             *pstNewFsm:��Ҫѹ���״̬��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��10��
   ��    ��   : zhoujun /40661
   �޸�����   :  �޸�ջ��ȵ�����

*****************************************************************************/
VOS_VOID NAS_MMC_FSM_PushFsm(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack,
    NAS_MMC_FSM_CTX_STRU                *pstNewFsm
)
{
    NAS_MMC_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= NAS_MMC_MAX_STACK_DEPTH )
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* ����ǰ״̬������CTX����Ҫ�������� */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(NAS_MMC_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_PopFsm
 ��������  : ��״̬�����г�ջ
 �������  : ��
             ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��10��
   ��    ��   : zhoujun /40661
   �޸�����   :  �޸�ջ��ȵ�����

*****************************************************************************/
VOS_VOID NAS_MMC_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();
    pstCurFsm                       = NAS_MMC_GetCurFsmAddr();

    /* ջ�ѿ� */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* ���õ�ǰ״̬�� */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(NAS_MMC_FSM_CTX_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetL1MainFsm
 ��������  : ��״̬��ջ�л�ȡ�ײ�״̬���ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��1��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetBottomFsmInFsmStack(VOS_VOID)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack     = VOS_NULL_PTR;

    /* ��ȡ״̬��ջ�ĵ�ַ */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();

    /* ��ջֱ���˳� */
    if (0 == pstFsmStack->usStackDepth)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetBottomFsmInFsmStack:FsmStack is empty.");
        return VOS_NULL_PTR;
    }

    return &(pstFsmStack->astFsmStack[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCurEntryMsg
 ��������  : ���浱ǰ״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
              pstMsg             :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-04-19
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����NAS_MMC�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 =   NAS_MMC_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    /* ����ǿ���Ϣ */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_MMC_SaveCurEntryMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_LoadSubFsmInfo
 ��������  : ����L2״̬������Ϣ
 �������  : enFsmId:L2״̬��ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��9��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��14��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: ����SYSCFG��״̬���Ĵ���

 3.��    ��   : 2011��7��20��
   ��    ��   : w00176964
   �޸�����   : V7R1 PHASEII �ع�: ����cellresel,ho,cco��״̬���Ĵ���

 4.��    ��   : 2011��7��20��
   ��    ��   : s46746
   �޸�����   : V7R1 PHASEII �ع�: ����plmn selection��״̬���Ĵ���

 5.��    ��   : 2011��9��24��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: ����HIGH_PRIO_PLMN_SEARCH��״̬���Ĵ���

 6.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������

 7.��    ��   : 2015��05��08��
   ��    ��   : s00193151
   �޸�����   : ���������Ż�: ����COMM SEARCH��״̬���Ĵ���
*****************************************************************************/
VOS_VOID  NAS_MMC_LoadSubFsm(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case NAS_MMC_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = NAS_MMC_SWITCH_ON_STA_SWITCH_ON_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MMC_FSM_POWER_OFF :
            pstCurFsm->ulState                  = NAS_MMC_POWER_OFF_STA_POWEROFF_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MMC_FSM_PLMN_SELECTION :
            pstCurFsm->ulState                  = NAS_MMC_PLMN_SELECTION_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_MMC_FSM_ANYCELL_SEARCH :
            pstCurFsm->ulState                  = NAS_MMC_ANYCELL_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetAnyCellSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_SYSCFG :
            pstCurFsm->ulState                  = NAS_MMC_SYSCFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSysCfgFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CELLRESEL :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCellReselFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_HO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_HO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysHoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CCO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CCO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCcoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_OOS:
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_OOS_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysOosFsmDescAddr();
            break;



        case NAS_MMC_FSM_PLMN_LIST:
            pstCurFsm->ulState                  = NAS_MMC_PLMN_LIST_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnListFsmDescAddr();
            break;



        case NAS_MMC_FSM_BG_PLMN_SEARCH:
            pstCurFsm->ulState                  = NAS_MMC_BG_PLMN_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetBgPlmnSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_GET_GEO:
            pstCurFsm->ulState                  = NAS_MMC_GET_GEO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetGeoFsmDescAddr();
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadSubFsm:Invalid Fsm Id");
            break;
    }


    /*ִ�г�ʼ��L2״̬���ĺ���*/
    pstCurFsm->pstFsmDesc->pfInitHandle();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_InitFsmL2
 ��������  : MMC����һ��L2��L3��״̬�����������̵�ͬʱ����״̬�Լ�������ʱ��?
              �ú��������ѹջ����,�������Ҫ����Э��ջѹջ,���뱣֤�˳�ǰ����
 �������  : enFsmId:L2״̬��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��9��
   ��    ��   : huwen /44270
   �޸�����   : ���ӵ�ǰ״̬������һ��״̬���������Ϣ
*****************************************************************************/
VOS_VOID NAS_MMC_FSM_InitFsmL2(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    VOS_UINT16                          usStackDepth;                           /* ��ǰѹջ��״̬���� */

    enParentFsmId                       = NAS_FSM_BUTT;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();
    pstFsmStack                         = NAS_MMC_GetFsmStackAddr();

    /*  ��ӡѹջǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();


    /* ��¼ѹջǰ��״̬�����������Ϣ���� */
    enParentFsmId                       = pstCurFsm->enFsmId;
    ulParentEventType                   = pstCurFsm->stEntryMsg.ulEventType;

    /* ����ǰ״̬��ѹջ���� */
    NAS_MMC_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId                  = enFsmId;

    /* ����L2״̬�� */
    NAS_MMC_LoadSubFsm(enFsmId, pstCurFsm);

    /* ��¼�ϲ�״̬�����������Ϣ���� */
    pstCurFsm->enParentFsmId            = enParentFsmId;
    pstCurFsm->ulParentEventType        = ulParentEventType;

    usStackDepth = pstFsmStack->usStackDepth;

    pstCurFsm->punParentFsmCtx = VOS_NULL_PTR;

    /* ����״̬��ջ����쳣���� */
    if ( (0            < usStackDepth)
      && (usStackDepth <= NAS_MMC_MAX_STACK_DEPTH) )
    {
        /* ��¼�ϲ�״̬�����������ݵ�ַ */
        pstCurFsm->punParentFsmCtx          = &(pstFsmStack->astFsmStack[(usStackDepth - 1)].unFsmCtx);
    }


    /*  ��ӡ��ǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_QuitFsmL2
 ��������  : ����L2״̬��������������̣�״̬������״̬ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_FSM_QuitFsmL2( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();

    /* QUITʱ��յ�ǰL2״̬����CTX */
    pstCurFsm->pstFsmDesc->pfInitHandle();

    /*  ��ӡѹջǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();

    /* ״̬����ջ���� */
    NAS_MMC_FSM_PopFsm();

    /*  ��ӡ��ǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_SetCurrState
 ��������  : ���õ�ǰ��ҪǨ�Ƶ�״̬
 �������  : ulCurrState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = NAS_MMC_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /*  ��ӡ��ǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_FSM_GetFsmTopState
 ��������  : ��ȡ״̬�������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬���Ķ���״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��19��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetFsmTopState( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* ��ȡ��ǰ״̬�� */
    pstCurFsm               = NAS_MMC_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmStackDepth
 ��������  : ��ȡ��ǰЭ��ջ��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��22��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��10��
   ��    ��   : zhoujun /40661
   �޸�����   :  �޸�ջ��ȵ�����
*****************************************************************************/
VOS_UINT16  NAS_MMC_GetFsmStackDepth( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetTimerAddr
 ��������  : ��ȡMMC CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��25��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_TIMER_CTX_STRU*  NAS_MMC_GetTimerAddr( VOS_VOID )
{
    return g_stNasMmcCtx.astMmcTimerCtx;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCacheMsgInMsgQueue
 ��������  : ��������Ϣ����Ļ����ڴ����
 �������  : ulEventType:��ϢID+PID
             pMsg      :��Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_MMC_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= NAS_MMC_MAX_MSG_QUEUE_NUM )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:No Empty buffer");

        NAS_MMC_LogBufferQueueMsg(VOS_TRUE);

        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCacheMsg
 ��������  : ���浱ǰ��Ҫ����Ļ���
 �������  : ulEventType:��ϢID+PID
             pMsg      :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����ɹ�
             VOS_FALSE:����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��11��9��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�:������DPLMN SET REQ��
                 ����

*****************************************************************************/
VOS_VOID NAS_MMC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if ( pstMsgHeader->ulLength >= ( NAS_MMC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:Len too Long");
        return;
    }

    /* �Ƚ���Ϣ���ȼ�,�ж��Ƿ���Ҫ�����ڻ������ */
    if ( VOS_FALSE == NAS_MMC_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:already exist msg");
        return;
    }

    /* ����Ϣ�����ڻ����ڴ���� */
    NAS_MMC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextInterSysCachedMsg
 ��������  : ��ȡ��ǰ���ڵ���ϵͳ��ѡ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��7��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextInterSysCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextInterSysCachedMsg:No Empty suspend buffer");
            break;
    }

    return ulCacheFlg;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextUserCachedMsg
 ��������  : ��ȡ�����User������Ϣ
 �������  : ��
 �������  : pstEntryMsg:������û���Ϣ
 �� �� ֵ  : VOS_TRUE:�����ȼ��Ļ������
             VOS_FALSE:�����ȼ��Ļ��治����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 3.��    ��   : 2015��9��6��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextUserCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ)  :
#if (FEATURE_ON == FEATURE_CSG)
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ):
#endif
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextUserCachedMsg:No Empty buffer");
            break;
    }
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

    return ulCacheFlg;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextHighPrioCachedMsg
 ��������  : ɨ������ȼ��Ļ����Ƿ����
 �������  : ��
 �������  : pstEntryMsg:�����ȼ��Ļ���
 �� �� ֵ  : VOS_TRUE:�����ȼ��Ļ������
             VOS_FALSE:�����ȼ��Ļ��治����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : ���¸������ȼ���ȡ������Ϣ

  3.��    ��   : 2011��11��7��
    ��    ��   : zhoujun 40661
    �޸�����   : RRMM_SUSPEND_IND��Ϣ�����ȼ��Ƚϸ�,��Ҫ���Ȼ�ȡ����Ϣ��

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextHighPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          i;
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheFlg  ;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    ulCacheFlg                          = VOS_FALSE;


    /* �����Ȼ�ȡ���е�״̬���ķ������Ϣ */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* ���Ȼ�ȡ״̬���������Ϣ */
        if ( VOS_FALSE == NAS_MMC_IsFsmEntryEventType(pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType) )
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;

        }

        /* �ҵ������ȼ�����Ϣ����ɸ����ȼ���Ϣ�Ŀ�������� */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* ��Ϊintersys��Ϣ�����ȼ����û�������Ϣ�����ȼ���,Ŀǰ����BG��������
       ��,�յ�rrmm_suspend_ind��Ϣ����ϵ�ǰ״̬������intersys��Ϣ*/
    /* �����Ȼ�ȡ���е�intersys��Ϣ */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        if ( VOS_TRUE == NAS_MMC_GetNextInterSysCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry)) )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;
        }

        /* �ҵ������ȼ�����Ϣ����ɸ����ȼ���Ϣ�Ŀ�������� */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* �����Ȼ�ȡ���еĸ����ȼ���Ϣ */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* �û��Ļ�����Ϣ���ȼ��θ� */
        ulCacheFlg = NAS_MMC_GetNextUserCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry));
        if ( VOS_TRUE == ulCacheFlg )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
        }


        /* �ҵ������ȼ�����Ϣ����ɸ����ȼ���Ϣ�Ŀ�������� */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }



    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextNormalPrioCachedMsg
 ��������  : ��ȡ��ͨ�Ļ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextNormalPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* ���������ȳ�ԭ��,Ĭ��ȡ��1���������� */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astMsgQueue[0].stMsgEntry),
               sizeof(NAS_MMC_ENTRY_MSG_STRU));

    /* ��Ϣ�Ѿ�ȡ���������ǰ���� */
    NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextCachedMsg
 ��������  : ��ȡ��ǰ��Ҫ����Ļ���
 �������  : ��
 �������  : pstEntryMSg:��ǰ���ȼ���ߵĻ�����Ϣ
 �� �� ֵ  : VOS_OK:��ȡ�ɹ�
             VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : ���Ȼ�ȡ�����ȼ��Ļ�����Ϣ
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }


    /* ������ڸ����ȼ�����Ϣ,�ȷ��ظ����ȼ�����Ϣ, ���ȼ��ߵ���Ϣ���ȵõ����� */
    if ( VOS_TRUE == NAS_MMC_GetNextHighPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    /* ��ȡ��ͨ�Ļ�����Ϣ�ɹ�,������ͨ�Ļ�����Ϣ */
    if ( VOS_TRUE == NAS_MMC_GetNextNormalPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsExistCacheMsg
 ��������  : �жϵ�ǰ��Ϣ�Ƿ��Ѿ�����
 �������  : ulEventType:��ϢID
 �������  : pulIndex   :�������Ϣ����
 �� �� ֵ  : VOS_TRUE:���ڻ������Ϣ
             VOS_FALSE:�����ڻ������Ϣ
 ���ú���  :pulIndex
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }

    }


    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearCacheMsg
 ��������  : ���ָ���Ļ�����Ϣ
 �������  : ulEventType:������󻺴����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��06��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* ���ҵ���Ҫ������Ļ��� */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
        }
    }

    /* δ�ҵ�����Ϣ����ֱ�ӷ��� */
    if ( -1 == cCachePos )
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* Ϊ��֤�����ȳ�,��Ҫ���������Ϣ�Ƶ�ǰ�� */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY��Ϣ���� */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

    }

    /* �����������һ */
    pstMsgQueue->ucCacheMsgNum--;

    /* ����ǰ�������ӡ���� */
    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllCacheMsg
 ��������  : ������еĻ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllCacheMsg( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    pstMsgQueue->ucCacheMsgNum          = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_MSG_QUEUE_NUM ; i++ )
    {
        PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   0x00,
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
    }

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_L1Main
 ��������  : ��ʼ��L1״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��1��2��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
  3.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���
  4.��    ��   : 2015��6��4��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_L1Main(VOS_VOID)
{
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();

    NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    NAS_MMC_ClearAllRegAttemptCount_L1Main();

    /* Ĭ��AVAILABLE COUNTERΪNORMAL���� */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_SwitchOn
 ��������  : NAS_MMC_InitFsmCtx_SwitchOn
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��13��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:,���ĵ�ǰ�Ŀ���˳��ΪG->L->W����ʼ��
                  ����״̬��������ʱ

  3.��    ��   : 2013��2��25��
    ��    ��   : w00167002
    �޸�����   : DTS2013022500811:LAST RPLMN rat���Կ�������λ�����û��
                  ʹ��SYSCFG���õ�˳����RPLMN.
  4.��    ��   : 2016��04��10��
    ��    ��   : j00174725
    �޸�����   : DTS2016040901340
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;

    VOS_UINT8                                              *pucLastImsi = VOS_NULL_PTR;

    VOS_UINT32                                              i;
    VOS_UINT8                                               *pucLastTmsi    = VOS_NULL_PTR;
    VOS_UINT8                                               *pucLastPtmsi   = VOS_NULL_PTR;
    VOS_UINT8                                               *pucLastRai     = VOS_NULL_PTR;
    VOS_UINT8                                               *pucLastLai     = VOS_NULL_PTR;

    pucLastTmsi     = NAS_MMC_GetLastTmsi_SwitchOn();
    pucLastPtmsi    = NAS_MMC_GetLastPtmsi_SwitchOn();
    pucLastRai      = NAS_MMC_GetLastRai_SwitchOn();
    pucLastLai      = NAS_MMC_GetLastLai_SwitchOn();

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pstSwitchOnRecord                   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnRecord->aucSwitchOnRatPrio;

    pucLastImsi = NAS_MMC_GetLastImsi_SwitchOn();

    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn();
    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn();

    /* Switch On״̬�������������ý���㿪�����ȼ�˳����Ϣ�ĳ�ʼ��:
       ����������ʼ��Ϊ0,ÿ�����㷢�Ϳ����󣬸���������1����ʾҪ��������ģ�Ľ���ģʽ */
    pstSwitchOnRecord->ucSwitchOnIndex = 0;

    /* ������Ҫ�·��������뼼�����ܸ��� */
    pstSwitchOnRecord->ucTotalSwitchOnRatNum = 0;

    /* SYSCFG״̬�������������ý�������ȼ�˳����Ϣ�ĳ�ʼ��:
       ����ģʽȫ����ʼ��ΪNAS_MML_NET_RAT_TYPE_BUTT */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pucSwitchOnRatPrio[i]           = NAS_MML_NET_RAT_TYPE_BUTT;
    }


    /* ��ʼ��״̬���������еĿ���Ǯ��IMSI��Ϣ */
    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pucLastImsi[i] = NAS_MML_IMSI_INVALID;
    }

    /* ��ʼ��Ptmsi */
    for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
    {
        pucLastPtmsi[i] = NAS_MML_PTMSI_INVALID;
    }

    /* ��ʼ��Tmsi */
    for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
    {
        pucLastTmsi[i] = NAS_MML_TMSI_INVALID;
    }

    /* ��ʼ��RAI */
    PS_MEM_SET(pucLastRai, 0x0, sizeof(VOS_UINT8) * NAS_MML_SIM_MAX_RAI_LEN);

    /* ��ʼ��LAI */
    PS_MEM_SET(pucLastLai, 0x0, sizeof(VOS_UINT8) * NAS_MML_SIM_MAX_LAI_LEN);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn
 ��������  : ��ȡ״̬���е�NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU�ṹֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : SwitchOn״̬���������еļ�¼�����㷢�Ϳ������Ⱥ�˳����Ϣ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012-08-03
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

****************************************************************************/
NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU* NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSwitchOnSettingRecord_SwitchOn,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.stSwitchOnRecord);
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_AddSwitchOnIndex_SwitchOn
 ��������  : ������һ����Ҫ����SwitchOnģ�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddSwitchOnIndex_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;

    /* �����ǰ״̬������NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSwitchOnIndex_SwitchOn,ERROR:FsmId Error");
    }

    /* ��ȡ״̬���е�Ҫ����SwitchOn����ģ����Ӧ���������б��ַ */
    pstSwitchOnRecord   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* ����INDEX����,ָ����һ��Ҫ����SwitchOn���õĽ��뼼�� */
    pstSwitchOnRecord->ucSwitchOnIndex ++;

    /* ���� */
    return ;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSettingRat_SwitchOn
 ��������  : ��ȡ��һ����Ҫ����SwitchOnģ�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8����:���뼼��,�о�����
             NAS_MML_NET_RAT_TYPE_GSM,
             NAS_MML_NET_RAT_TYPE_WCDMA,
             NAS_MML_NET_RAT_TYPE_LTE,
             NAS_MML_NET_RAT_TYPE_BUTT

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSendingRat_SwitchOn(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucNextSwitchOnRat;

    /* �����ǰ״̬������NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSendingRat_SwitchOn,ERROR:FsmId Error");
    }

    pstSwitchOnRecord      = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* ��ȡ״̬���е�Ҫ����SwitchOn����ģ����Ӧ���������б��ַ */
    pucSwitchOnRatPrio     = pstSwitchOnRecord->aucSwitchOnRatPrio;

    /* ��������Ե������õ��ܸ��������ؽ��뼼��Ϊ��Чֵ����ʾSwitchOn���ý��� */
    if ( pstSwitchOnRecord->ucSwitchOnIndex >= pstSwitchOnRecord->ucTotalSwitchOnRatNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* ȡ����������������Ӧ�Ľ��뼼�� */
    ucNextSwitchOnRat                     = pucSwitchOnRatPrio[pstSwitchOnRecord->ucSwitchOnIndex];

    /* ������ҪSwitchOn���õĽ��뼼�� */
    return ucNextSwitchOnRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn
 ��������  : �����������·�SwitchOn���Ⱥ�˳��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��3��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��26��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:����Ϊֻ��ƽ̨֧�ֵĽ���㷢�Ϳ�������
*****************************************************************************/
VOS_VOID NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio       = VOS_NULL_PTR;
    VOS_UINT8                                               ucRatIndex;

    /* �����ǰ״̬������NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSwitchOnSendingOrder_SwitchOn,ERROR:FsmId Error");
    }

    ucRatIndex                          = 0;

    /* ȡ�õ�ǰ SwitchOn״̬���������еļ�¼���ý�������ȼ�˳����Ϣ */
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnSettingRecord->aucSwitchOnRatPrio;

    /* �����·�SwitchOn�����˳��ΪGLW,��LTE��֧�֣���ΪGW */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif

    /* ���ƽ̨֧��W��TD����Ҫ��Uģ���������� */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    /* ������Ҫ�·������������ܸ��� */
    pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum = ucRatIndex;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastTmsi_SwitchOn
 ��������  : ��ȡNV���м�¼����һ�ε�Tmsi
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش洢����ǰNV�б����Tmsi�����ݵ��׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* NAS_MMC_GetLastTmsi_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastTmsi_SwitchOn,ERROR:FsmId Error");
    }

    /* ���ش洢����ǰNV�б����TMSI�����ݵ��׵�ַ */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastTmsi;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLastTmsi_SwitchOn
 ��������  : ��¼NV���м�¼����һ�ε�tmsi
 �������  : pucTmsi 
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastTmsi_SwitchOn(VOS_UINT8 *pucTmsi)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLastTmsi_SwitchOn,ERROR:FsmId Error");
    }

    /* �洢����ǰNV�б����TMSI������ */
    PS_MEM_CPY(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastTmsi,
               pucTmsi,
               sizeof(VOS_UINT8) * NAS_MML_MAX_TMSI_LEN);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastPtmsi_SwitchOn
 ��������  : ��ȡNV���м�¼����һ�ε�Ptmsi
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش洢����ǰNV�б����Ptmsi�����ݵ��׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* NAS_MMC_GetLastPtmsi_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastPtmsi_SwitchOn,ERROR:FsmId Error");
    }

    /* ���ش洢����ǰNV�б����PTMSI�����ݵ��׵�ַ */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastPtmsi;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLastPtmsi_SwitchOn
 ��������  : ��¼NV���м�¼����һ�ε�Ptmsi
 �������  : pucPtmsi 
 �������  : ��
 �� �� ֵ  : �洢����ǰNV�б����Ptmsi������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastPtmsi_SwitchOn(VOS_UINT8 *pucPtmsi)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLastPtmsi_SwitchOn,ERROR:FsmId Error");
    }

    /* �洢����ǰNV�б����PTMSI������ */
    PS_MEM_CPY(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastPtmsi,
               pucPtmsi,
               sizeof(VOS_UINT8) * NAS_MML_MAX_PTMSI_LEN);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastLai_SwitchOn
 ��������  : ��ȡNV���м�¼����һ�ε�Lai
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش洢����ǰNV�б����Lai�����ݵ��׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* NAS_MMC_GetLastLai_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastLai_SwitchOn,ERROR:FsmId Error");
    }

    /* ���ش洢����ǰNV�б����LAI�����ݵ��׵�ַ */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastLai;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLastLai_SwitchOn
 ��������  : ��¼NV���м�¼����һ�ε�LAI
 �������  : pucLai
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastLai_SwitchOn(VOS_UINT8 *pucLai)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLastLai_SwitchOn,ERROR:FsmId Error");
    }

    /* �洢����ǰNV�б����LAI������ */
    PS_MEM_CPY(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastLai,
               pucLai,
               sizeof(VOS_UINT8) * NAS_MML_SIM_MAX_LAI_LEN);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastRai_SwitchOn
 ��������  : ��ȡNV���м�¼����һ�ε�Lai
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش洢����ǰNV�б����Rai�����ݵ��׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* NAS_MMC_GetLastRai_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastRai_SwitchOn,ERROR:FsmId Error");
    }

    /* ���ش洢����ǰNV�б����RAI�����ݵ��׵�ַ */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastRai;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLastRai_SwitchOn
 ��������  : ��¼NV���м�¼����һ�ε�RAI
 �������  : pucRai
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastRai_SwitchOn(VOS_UINT8 *pucRai)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLastRai_SwitchOn,ERROR:FsmId Error");
    }

    /* �洢����ǰNV�б����RAI������ */
    PS_MEM_CPY(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastRai,
               pucRai,
               sizeof(VOS_UINT8) * NAS_MML_SIM_MAX_RAI_LEN);
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastImsi_SwitchOn
 ��������  : ��ȡ��һ����Ҫ����SwitchOnģ�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ش洢����ǰNV�б����IMSI�����ݵ��׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��2��25��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8* NAS_MMC_GetLastImsi_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastImsi_SwitchOn,ERROR:FsmId Error");
    }

    /* ���ش洢����ǰNV�б����IMSI�����ݵ��׵�ַ */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastImsi;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_PowerOff
 ��������  : ��ʼ���ػ�״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��17��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII: ��ʼ���ػ�ʱ��ǰ����ģ������
  3.��    ��   : 2013��1��15��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE: ��ʼ���ػ�ʱ�Ĵ�ģ�б�

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_PowerOff(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff();
    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

    NAS_MMC_SetMasterModeRat_PowerOff( NAS_MML_NET_RAT_TYPE_BUTT );

    /* ��ʼ���ػ�ʱ�Ĵ�ģ�б� */
    pstSlaveModeRatList           = NAS_MMC_GetSlaveModeRatList_PowerOff();
    pstSlaveModeRatList->ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstSlaveModeRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_PlmnSelection
 ��������  : ��ʼ��Plmn Selection״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��7��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ʼ��ѡ��״̬���Ľ�ֹ����LA

 3.��    ��   : 2012��5��10��
   ��    ��   : l65478
   �޸�����   : DTS2012050500988:NMO Iʱ,PSע��ʧ��#11,�յ�ϵͳ��Ϣ���ַ�����ע��
 4.��    ��   : 2012��06��11��
   ��    ��   : s00217060
   �޸�����   : For CS/PS mode 1����ʼ����Ҫ����פ����LTE����
 5.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 6.��    ��   : 2013��8��5��
   ��    ��   : w00167002
   �޸�����   : DTS2013073106748:�����ֶ�ģʽG����24003 CS��ע��ɹ���PS��
                ע��ʧ��17����ѡ��״̬�����û�����绰���л���W�µ�46002�����ϡ�
                �绰�ҶϺ�W�ϱ�����,ѡ��״̬����ANYCELL������û����ԭ�е�24003���硣
                �޸�Ϊѡ��״̬����ע����ʱ������յ�HO�л��ɹ������˳�
                ѡ��״̬��,���绰����������L1 MAIN����ѡ��״̬����
                Ĭ�Ͻ��뼼����ʼ��ΪBUTT.
 7.��    ��   :2013��8��21��
   ��    ��   :z00161729
   �޸�����   :DTS2013081607507:�������������к�̨����·�at+cops=0��mmc�жϷ���������ͣ��ϵ�ǰ���������������¿����ٶ���
 8.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�
 9.��    ��   : 2015��5��23��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU                              stInvalidPlmnId;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
#endif

    /* ����Abort��־ΪVOS_FALSE */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_FALSE);

    /* ����Rel Request��־ΪVOS_FALSE */
    NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetInterSysSuspendRat_PlmnSelection(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ���õȴ�ע���־ΪNULL */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* ����CSע���������ĺ�������ΪBUTT */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ����PSע���������ĺ�������ΪBUTT */
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ��ʼ��CS��PS causeֵΪBUTT */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    /* ��ʼ�������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    PS_MEM_SET(pstPlmnSelectionListInfo, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* ��ʼ������״̬���������в�ͬ���뼼���ĸ��Ǽ�������Ϣ */
    NAS_MMC_InitSearchRatInfo_PlmnSelection();

    pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
    PS_MEM_SET(pstForbRoamLaInfo, 0X0, sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU));

    PS_MEM_SET(NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(),
               0X0, sizeof(NAS_MML_PLMN_ID_STRU));

#if (FEATURE_ON == FEATURE_LTE)
    stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(&stPlmnId);
#endif

    PS_MEM_SET(&stInvalidPlmnId, 0x0, sizeof(stInvalidPlmnId));
    stInvalidPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stInvalidPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;

    NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(&stInvalidPlmnId);

    NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_BUTT);

    NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_CL_REG_STATUS_BUTT);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_AnyCellSearch
 ��������  : ��ʼ��ANYCELL����״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��27��
    ��    ��   : L00171473
    �޸�����   : V7R1 phase II �޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList      = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

    pstAnyCellSearchCtx = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    /* ��ȡMS��ǰ֧�ֵĽ��뼼�� */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /* ��ʼ��ANYCELL״̬���Ľ��뼼��Ϊ��ǰMS֧�ֵĽ��뼼�� */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio = (*pstRatPrioList);

    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    /* ��ʼ�����뼼��Ϊδ������ */
    for (i = 0; i < ucRatNum; i++)
    {
        pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_FALSE;
    }

    /* ����Abort��־ΪVOS_FALSE */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_FALSE);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_BgPlmnSearch
 ��������  : ��ʼ��Bg Plmn Search״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��21��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��29��
   ��    ��   : w00167002
   �޸�����   : DTS2011112301233:��ʼ��״̬���������еĴ���¼�����
 3.��    ��   : 2012��6��25��
   ��    ��   : L60609
   �޸�����   : AT&T&DCM:��ʼ���Ƿ���Ҫ����ϵͳ��Ϣ�ı�־
 4.��    ��   : 2014��5��28��
   ��    ��   : z00234330
   �޸�����   : covertity�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_BgPlmnSearch()
{
    NAS_MML_PLMN_ID_STRU                stInvalidPlmnId;
    NAS_MML_EQUPLMN_INFO_STRU           stEquPlmnInfo;

    stInvalidPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    PS_MEM_SET(&stEquPlmnInfo, 0x00, sizeof(stEquPlmnInfo));
    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */


    /* ��¼״̬����������Abort�¼�����0xFFFFFFFF */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(NAS_MML_INVALID_EVENT_TYPE);

    /* ��ʼ��ABORT��־Ϊ�޴�� */
    NAS_MMC_SetAbortType_BgPlmnSearch(NAS_MMC_ABORT_BUTT);

    NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_FALSE);

#if (FEATURE_OFF == FEATURE_LTE)
    /* ��ʼ�������ֶ� */
    PS_MEM_SET(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve,
               0X00,
               sizeof(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve));
#endif

    /* ��ʼ��RegInfo��Ϣ */
    NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ��ʼ����ǰ���ڳ��Եĸ����ȼ����缰����뼼����Ϣ */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ʼ��VPlmn��Ϣ */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ʼ��EPlmn��Ϣ */
    NAS_MML_InitEquPlmnInfo(&stEquPlmnInfo);
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(&stInvalidPlmnId, &stEquPlmnInfo);

    /* Added by w00176964 for coverity����, 2014-3-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_FALSE);
#endif
    /* Added by w00176964 for coverity����, 2014-3-10, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_InterSysCellResel
 ��������  : ��ʼ����ϵͳ��ѡ״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��16��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133��Abort��־��ʼ��

  3.��    ��   : 2014��2��26��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:UT���û�г�ʼ��
*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCellResel(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel();
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_FALSE);
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_FALSE);

    /* Added by w00167002 for L-C��������Ŀ, 2014-2-26, begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_BUTT);
    /* Added by w00167002 for L-C��������Ŀ, 2014-2-26, end */
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_InterSysHo
 ��������  : ��ʼ����ϵͳ�л�״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysHo(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysHo();
    NAS_MMC_ClearAllResumeRspFlag_InterSysHo();

    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_InterSysCco
 ��������  : ��ʼ����ϵͳCOO״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCco(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCco();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCco();
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_InterSysOos
 ��������  : ��ʼ����ϵͳOOS״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysOos(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysOos();
    NAS_MMC_ClearAllResumeRspFlag_InterSysOos();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_PlmnList
 ��������  : ��ʼ��PLMN LIST״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2015��9��30��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/

VOS_VOID  NAS_MMC_InitFsmCtx_PlmnList(VOS_VOID)
{
    /* ��ʼ�������Ľ��뼼����Ϣ*/
    NAS_MMC_InitSearchRatInfo_PlmnList();

    /* ����״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_FALSE);

    /* ����֪ͨMSCC���Ϊ�� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_FALSE);

    /* ��ʼ�����ѵ��ĸ���������Ϣ */
    NAS_MMC_InitSearchedPlmnListInfo_PlmnList();

    /* ����ȴ�������ı����Ϣ */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* ���CS/PS��additionֵ */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

#if (FEATURE_ON == FEATURE_LTE)
    /* ���浱ǰL disable״̬��״̬�������� */
    NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
#endif

    /* ����anycell������� */
    NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_FALSE);

#if (FEATURE_ON == FEATURE_CSG)
    /* ��ʼ��CSG��������CSG ID����б���Ϣ */
    NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList();
#endif

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_GetGeo
 ��������  : ��ʼ��GetGeo״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��08��
    ��    ��   : sunjitan 00193151
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmCtx_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_GET_GEO_CTX_STRU       *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx    = NAS_MMC_GetFsmCtxAddr_GetGeo();

    /* ״̬�������������ʼ�� */
    PS_MEM_SET(pstGetGeoCtx, 0, sizeof(NAS_MMC_FSM_GET_GEO_CTX_STRU));

    /* ����״̬��ABORT��ʶΪ��Ч */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_FALSE);

    /* ����֪ͨMSCC�ظ����Ϊ��Ч */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_FALSE);

    /* ����״̬������׶�ΪBUTT */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_BUTT);

    /* ��ʼ��GET GEO���뼼�����ȼ��б� */
    pstGetGeoCtx->stGetGeoRatInfoList.ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enRatType      = NAS_MML_NET_RAT_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].ucIsSrchedFlag = VOS_FALSE;
    }

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSearchCtrlCtx
 ��������  : ��ʼ��PLMN�������ƿ�������
 �������  : enInitType:��ʼ������,��ʼ������ػ�
 �������  : pstPlmnSearchCtrl:��������������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��30��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��17��
   ��    ��   : s46746
   �޸�����   : �����ȼ�״̬�������������޸�,�޸Ľ����פ��������,����NAS�Ƿ�����״̬

 3.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : DTS2011111603447:���л���������ĳ�ʼ������
 4.��    ��   : 2011��12��24��
   ��    ��   : w00166186
   �޸�����   : DTS2011122204051:�ֶ�ģʽ����פ����ACC BAR��С������ѡ����ЧPLMN������ע��
 5.��    ��   : 2012��2��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012020604181:�������µ磬�ֶ�ģʽ����פ����ACC BAR��С����
                ��ѡ����ЧPLMN������ע��,��Ϊ����ʱRplmn��Eplmn�������Ƚϴ����޸�Ĭ��ֵΪVOS_TRUE
 6.��    ��   : 2013��11��23��
   ��    ��   : z00161729
   �޸�����    : SVLTE�Ż�G-TL ps�л������޸�
 7.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 8.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
 9.��    ��   : 2013��4��4��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:����NO RF ��ر�������
 10.��    ��   : 2014��2��22��
   ��    ��   : w00167002
   �޸�����   : ������ʼ��ΪMMC����
 11.��    ��   : 2014��6��13��
    ��    ��   : w00167002
    �޸�����   : ��ʼ��֪ͨMSCC��ǰNO RF��״̬
 12.��    ��   : 2014��6��24��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
 13.��    ��   : 2014��12��29��
    ��    ��   : z00161729
    �޸�����   : DSDSҵ���ز�ʱno rfδ������������ҵ��ʧ�ܣ�mm��no cell available״̬no rfʱ��mmc����cm service ind��������
 14.��    ��   : 2014��11��4��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�
 15.��    ��   : 2015��1��6��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 16.��    ��   : 2015��9��17��
    ��    ��   : y00346957
    �޸�����   : DTS2015070910885 �޸�
 17.��    ��   : 2015��11��2��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_InitPlmnSearchCtrlCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   *pstPlmnSearchCtrl
)
{
    pstPlmnSearchCtrl->ucWrrLimitServiceInd             = VOS_FALSE;
    pstPlmnSearchCtrl->stUserSpecPlmnId.enRat           = NAS_MML_NET_RAT_TYPE_BUTT;

    if ( NAS_MMC_INIT_CTX_STARTUP  == enInitType )
    {
        pstPlmnSearchCtrl->enSelectionMode                  = NAS_MMC_PLMN_SELECTION_MODE_AUTO;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;

        pstPlmnSearchCtrl->ucUserSpecPlmnRegStatus          = VOS_TRUE;
    }

    pstPlmnSearchCtrl->stUserReselPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = VOS_FALSE;
    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    pstPlmnSearchCtrl->enAsCellCampOn                   = NAS_MMC_AS_CELL_NOT_CAMP_ON;
    pstPlmnSearchCtrl->enSpecPlmnSearchState            = NAS_MMC_SPEC_PLMN_SEARCH_STOP;

    NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    /* Ĭ�ϲ�֧��ncell���� */
    NAS_MMC_SetNcellSearchFirstTimerLen(0);
    NAS_MMC_SetNcellSearchSecondTimerLen(0);


    NAS_MMC_SetNcellSearchFlag(VOS_FALSE);
    NAS_MML_InitEquPlmnInfo(&pstPlmnSearchCtrl->stNcellSearchInfo.stOtherModemEplmnInfo);
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo));
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo));


    /* Added by w00167002 for L-C��������Ŀ, 2014-2-22, begin */
    NAS_MMC_SetRegCtrl(NAS_MMC_REG_CONTROL_BY_3GPP_MMC);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by w00167002 for L-C��������Ŀ, 2014-2-22, end */

    NAS_MMC_InitUserDPlmnNPlmnInfo(&pstPlmnSearchCtrl->stDplmnNplmnCtx);

    NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
    NAS_MMC_ClearDisabledLtePlmnId();

    NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);

    NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(VOS_FALSE);
    NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg(&pstPlmnSearchCtrl->stNonOosPlmnSearchFeatureSupportCfg);
    NAS_MMC_InitOosSearchStrategyInfo(&pstPlmnSearchCtrl->stOosPlmnSearchStrategyInfo);

    NAS_MMC_InitGetGeoInfo(&pstPlmnSearchCtrl->stGetGeoInfo);

    pstPlmnSearchCtrl->stLastCampedPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stLastCampedPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstPlmnSearchCtrl->stLastCampedPlmnId.enRat = NAS_MML_NET_RAT_TYPE_BUTT;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstPlmnSearchCtrl->stCLAssociatedInfoNtf.ucAllowSrchLteFlg         = VOS_TRUE;
    pstPlmnSearchCtrl->stCLAssociatedInfoNtf.enLteSysPriClass          = NAS_MSCC_PIF_PLMN_PRIORITY_ANY;
#endif
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitServiceInfo
 ��������  : ��ʼ��MMC�ķ���״̬��Ϣ
 �������  : ��
 �������  : pstServiceInfo:�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��13��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_InitServiceInfo(
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo
)
{
    pstServiceInfo->enCsCurrService = NAS_MMC_NO_SERVICE;
    pstServiceInfo->enPsCurrService = NAS_MMC_NO_SERVICE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitMaintainCtx
 ��������  : ��ʼ��MMC��ά�ɲ�������
 �������  : pstMaintainInfo:��ά�ɲ���Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  3.��    ��   : 2012��4��24��
    ��    ��   : l00171473
    �޸�����   : DTS2012041805606
  4.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr
*****************************************************************************/
VOS_VOID  NAS_MMC_InitMaintainCtx(
    NAS_MMC_MAINTAIN_CTX_STRU           *pstMaintainInfo
)
{
    pstMaintainInfo->ucGcfCh9_4_3_AND_Ch26_7_4_3    = VOS_FALSE;

    pstMaintainInfo->ucActionType                   = NAS_MMC_AT_ACTION_TYPE_START_FOREVER;
    pstMaintainInfo->ucMsgType                      = NAS_MMC_AT_MSG_TYPE_CELL_SIGN;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_ID;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_BLER;


    pstMaintainInfo->ucSignThreshold       = 0;   /* Ĭ�Ͻ����ȡȱʡֵ*/

    pstMaintainInfo->ucMinRptTimerInterval = 0; /*Ĭ�ϼ��ʱ��*/
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnRegRejCtx
 ��������  : ��ʼ��PLMNע�ᱻ����Ϣ������
 �������  : ��
 �������  : pstPlmnRegRejInfo:ע�ᱻ����Ϣ������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��30��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU

*****************************************************************************/
VOS_VOID  NAS_MMC_InitPlmnRegRejCtx(
    NAS_MMC_PLMN_REG_REJ_CTX_STRU          *pstPlmnRegRejInfo
)
{
    VOS_UINT32                          i;

    pstPlmnRegRejInfo->ucPlmnRegInfoNum     = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_REG_PLMN_INFO_NUM ; i++ )
    {
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#if (FEATURE_ON == FEATURE_LTE)
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitCurrFsmCtx
 ��������  : ��ʼ����ǰ״̬��������
 �������  : ��
 �������  : pstCurrFsmCtx:��ǰ״̬����������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��30��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��2��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 3.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���
 4.��    ��   : 2014��4��22��
   ��    ��   : w00167002
   �޸�����   : ��ʼ��AVAILABLE�����ͣ������ʼ��ΪNAS_MMC_AVAILABLE_TIMER_TYPE_NCELL
 5.��    ��   : 2015��6��6��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_InitCurrFsmCtx(
    NAS_MMC_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   NAS_MMC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   NAS_MMC_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   NAS_MMC_L1_STA_NULL;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    pstCurrFsmCtx->enParentFsmId            =   NAS_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;


    /* Ĭ��AVAILABLE COUNTERΪNORMAL���� */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);

    NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               NAS_MMC_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmStackCtx
 ��������  : ��ʼ��״̬��ջ������
 �������  : ��
 �������  : pstFsmStack:״̬��ջ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��30��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : ����ջpop��־��ʼ��
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmStackCtx(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < NAS_MMC_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = NAS_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = NAS_MMC_L1_STA_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitInternalBuffer
 ��������  : ����ڲ�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_InitInternalBuffer(
    NAS_MMC_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    pstBufferEntryMsgQueue->ucCurrIndex     = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(pstBufferEntryMsgQueue->astMsgQueue));
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitHighPrioPlmnSearchCtx
 ��������  : ��ʼ��NETSCAN����������
 �������  : NETSCAN����������ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitNetScanReqCtx(
    NAS_MMC_NET_SCAN_REQ_CTX_STRU      *pstNetScanReqCtx
)
{
    PS_MEM_SET( &(pstNetScanReqCtx->stNetScanReq), 0X00, sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) );

    pstNetScanReqCtx->stNetScanReq.ucRat = NAS_MML_NET_RAT_TYPE_BUTT;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrEntryMsg
 ��������  : ��ȡ��ǰ״̬���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬���������Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrEntryMsg(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.stEntryMsg);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSearchCtrl
 ��������  : ��ȡ��ǰPLMN��������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMN��������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU *NAS_MMC_GetPlmnSearchCtrl(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSelectionMode
 ��������  : ��ȡ��ǰPLMN����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMN����ģʽ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionMode(VOS_VOID)
{
    /* CLģʽ�������������Զ����� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        return NAS_MMC_PLMN_SELECTION_MODE_AUTO;
    }
#endif

    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUtranSkipWPlmnSearchFlag
 ��������  : ��ȡUTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ���£��Ƿ���Ҫ����w�����ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����w;VOS_FALSE:��w
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��23��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetOtherModemPlmnId
 ��������  : ��ȡ����פ��plmn id
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����פ��plmn id
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetOtherModemPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetOtherModemPlmnId
 ��������  : ���ø���פ��plmn id
 �������  : pstPlmnId - plmn id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
*****************************************************************************/
VOS_VOID NAS_MMC_SetOtherModemPlmnId(NAS_MML_PLMN_ID_STRU *pstPlmnId)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId = *pstPlmnId;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetUtranSkipWPlmnSearchFlag
 ��������  : ����UTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ���£��Ƿ���Ҫ����w�����ı�ʶ
 �������  : ucUtranSkipWPlmnSearchFlag - UTRAN����״̬������T/W״̬�и���gsm�й�����Ϣ��ǰ�����Ƿ���Ҫ����w�����ı�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��23��
   ��    ��   : z00161729
   �޸�����    :SVLTE�Ż�G-TL ps�л������޸�
*****************************************************************************/
VOS_VOID NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8 ucUtranSkipWPlmnSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNcellSearchInfo
 ��������  : ��ȡncell���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ncell���������Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
NAS_MMC_NCELL_SEARCH_INFO_STRU* NAS_MMC_GetNcellSearchInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNcellSearchInfo);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNcellSearchFlag
 ��������  : ��ȡ�Ƿ�֧��ncell������ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��;VOS_FALSE:��֧��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNcellSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNcellSearchFlag
 ��������  : �����Ƿ�֧��ncell������ʶ
 �������  : ucNcellSearchFlag - �Ƿ�֧��ncell������ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_VOID NAS_MMC_SetNcellSearchFlag(VOS_UINT8 ucNcellSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag = ucNcellSearchFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNcellSearchFirstTimerLen
 ��������  : ��ȡ��һ�׶�����Ƶ������������Ե�ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ʱ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNcellSearchFirstTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNcellSearchFirstTimerLen
 ��������  : ���õ�һ�׶�����Ƶ������������Ե�ʱ����
 �������  : ucNcellSearchTimerLen - ncell����ʱ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
*****************************************************************************/
VOS_VOID NAS_MMC_SetNcellSearchFirstTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen = ucNcellSearchTimerLen;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNcellSearchSecondTimerLen
 ��������  : ��ȡ�ڶ��׶�����Ƶ������������Ե�ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ʱ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNcellSearchSecondTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNcellSearchSecondTimerLen
 ��������  : ���õڶ��׶�����Ƶ������������Ե�ʱ����
 �������  : ucNcellSearchTimerLen - ncell����ʱ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
*****************************************************************************/
VOS_VOID NAS_MMC_SetNcellSearchSecondTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen = ucNcellSearchTimerLen;
}



/*******************************************************************************
  �� �� ��  : NAS_MMC_GetPlmnSelectionMode
  ��������  : ��ȡ��ǰPLMN����ģʽ,��SI_STK_ProvideLocalInfo_SearchMode��������
              �ӿ�����
  �������  : ��
  �������  : ��
  �� �� ֵ  : PLMN����ģʽ
  ���ú���  :
  ��������  :
  �޸���ʷ      :
  1.��    ��   : 2011-08-24
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID Mmc_ComGetPlmnSearchMode(VOS_UINT8 *pucReselMode)
{
    *pucReselMode = NAS_MMC_GetPlmnSelectionMode();
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPlmnSelMode
 ��������  : ��ȡ��ǰPLMN����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMN����ģʽ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetPlmnSelectionMode(
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8      enSelectionMode
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode = enSelectionMode;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAsCellCampOn
 ��������  : ��ȡ������ϱ���פ��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������ϱ���פ��״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-10-17
   ��    ��   : s46746
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8 NAS_MMC_GetAsCellCampOn(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAsCellCampOn
 ��������  : ���ý�����ϱ���פ��״̬
 �������  : enAsCellCampOn
 �������  : ��
 �� �� ֵ  : ������ϱ���פ��״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-29
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8   enAsCellCampOn)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn = enAsCellCampOn;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecPlmnSearchState
 ��������  : ��ȡMMC�Ƿ�ָ������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : MMC�Ƿ�ָ������״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-10-17
   ��    ��   : s46746
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 NAS_MMC_GetSpecPlmnSearchState(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSpecPlmnSearchState
 ��������  : ����ָ������״̬
 �������  : enSpecPlmnSearchState
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-29
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState = enSpecPlmnSearchState;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUserSpecPlmnId
 ��������  : ��ȡ�û�ָ��������PLMNID
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û�ָ��������PLMNID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/

NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserSpecPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUserSpecPlmnRegisterStatus
 ��������  : ��ȡ�û�ָ��������ע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û�ָ��������ע��״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-08-2
   ��    ��   : s46746
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 NAS_MMC_GetUserSpecPlmnRegisterStatus()
{
    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUserReselPlmnId
 ��������  : ��ȡָ������ǰפ����PLMNID�ͽ��뼼��,��ͬʱָ������ע��ɹ���Ҳ����¸�ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û�ָ������ǰפ����PLMNID�ͽ��뼼��,��ͬʱָ������ע��ɹ���Ҳ����¸�ֵ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/

NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserReselPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserReselPlmnId);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetUserSpecPlmnId
 ��������  : �����û�ָ��������PLMNID
 �������  : pstPlmnInfo:�û�ָ��������PLMNID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_SetUserSpecPlmnId(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId),
               pstPlmnInfo,
               sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetUserSpecPlmnRegisterStatus
 ��������  : �����û�ָ��������ע��״̬
 �������  : ucRegisterStatus:ע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-08-2
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��08��20��
   ��    ��   : l65478
   �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
               �����������פ��EPLMN��

  3.��    ��   : 2012��9��20��
    ��    ��   : z40661
    �޸�����   : �Զ�ģʽ���յ�ָ���������󣬻Ὣ�����������ΪVOS_FALSE����
                 �����ܽ����Զ�ģʽ���жϡ�
*****************************************************************************/

VOS_VOID NAS_MMC_SetUserSpecPlmnRegisterStatus(
    VOS_UINT8                           ucRegisterStatus
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus = ucRegisterStatus;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetUserReselPlmnId
 ��������  : ����ָ������ǰפ����PLMNID�ͽ��뼼��
 �������  : pstPlmnInfo:�û�ָ��������PLMNID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��6��
   ��    ��   : L00171473
   �޸�����   : ��������޸�
*****************************************************************************/

VOS_VOID NAS_MMC_SetUserReselPlmnId(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserReselPlmn = VOS_NULL_PTR;

    pstUserReselPlmn = NAS_MMC_GetUserReselPlmnId();

    pstUserReselPlmn->stPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstUserReselPlmn->stPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstUserReselPlmn->enRat          = enRat;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnRegRejInfo
 ��������  : ��ȡ��ǰPLMNע�ᱻ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMNע�ᱻ��������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_PLMN_REG_REJ_CTX_STRU *NAS_MMC_GetPlmnRegRejInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnRegInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetServiceInfo
 ��������  : ��ȡ��ǰMMC����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰMMC����״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SERVICE_INFO_CTX_STRU *NAS_MMC_GetServiceInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stServiceInfo);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrCsService
 ��������  : ��ȡ��ǰMMC CS����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰMMC����״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014-10-22
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrCsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrPsService
 ��������  : ��ȡ��ǰMMC CS����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰMMC����״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014-10-22
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrPsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService);
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCsNormalService
 ��������  : �жϵ�ǰCS���Ƿ���������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPsNormalService
 ��������  : �жϵ�ǰPS���Ƿ���������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNormalServiceStatus
 ��������  : �ж�MMC�Ƿ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��������
             VOS_FALSE:������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNormalServiceStatus(VOS_VOID)
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMaintainInfo
 ��������  : ��ȡ��ǰMMC��ά�ɲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰMMC��ά�ɲ���Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-11
   ��    ��   : z40661
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_MAINTAIN_CTX_STRU *NAS_MMC_GetMaintainInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stMaintainInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverMmStatusToMmc
 ��������  : MM��GMM�ķ���״̬ת��ΪMMC�ķ���״̬
 �������  : enServiceStatus:MM��GMM�ķ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8  NAS_MMC_ConverMmStatusToMmc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8           enRegDomain,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8    enServiceStatus
)
{
    switch ( enServiceStatus )
    {
        case MM_COM_SRVST_NORMAL_SERVICE :
            return NAS_MMC_NORMAL_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE_REGION :
            return NAS_MMC_LIMITED_SERVICE_REGION;

        case MM_COM_SRVST_NO_IMSI :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_NO_SERVICE :
            return NAS_MMC_NO_SERVICE;

        default:
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ConverMmStatusToMmc,", enServiceStatus);
            break;
    }

    if ( NAS_MMC_REG_DOMAIN_CS == enRegDomain )
    {
        return NAS_MMC_GetCsServiceStatus();
    }
    else
    {
        return NAS_MMC_GetPsServiceStatus();
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDomainServiceStatus
 ��������  : ���·������״̬
 �������  : enCurrDomain  :��ǰ�ķ�����
              enCurrService :����µ�ǰ�������״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-11-3
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_UpdateDomainServiceStatus(
    VOS_UINT8                           enCurrDomain,
    NAS_MMC_SERVICE_ENUM_UINT8          enCurrService
)
{
    /* �������CS�������CS��Ľ�� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_CS == (NAS_MMC_WAIT_REG_RESULT_IND_CS & enCurrDomain) )
    {
        NAS_MMC_SetCsServiceStatus(enCurrService);
    }

    /* �������PS�������PS��Ľ�� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_PS == (NAS_MMC_WAIT_REG_RESULT_IND_PS & enCurrDomain) )
    {
        NAS_MMC_SetPsServiceStatus(enCurrService);
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsServiceStatus
 ��������  : ���µ�ǰCS����״̬
 �������  : CS����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-13
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID    NAS_MMC_SetCsServiceStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService
)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enCsCurrService = enCsCurrService;
}
/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsInValidCampPlmn
 ��������  : ���µ�ǰפ�������Ƿ���Ч
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014-04-30
   ��    ��   : s00261364
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32  NAS_MMC_IsInValidCampPlmn( VOS_VOID )
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo = VOS_NULL_PTR;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* �ж���ǰפ��PLMNΪ��Чֵ */
    if ( (NAS_MML_INVALID_MCC == pstCampPlmnInfo->stLai.stPlmnId.ulMcc )
      && (NAS_MML_INVALID_MNC == pstCampPlmnInfo->stLai.stPlmnId.ulMnc ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsServiceStatus
 ��������  : ���µ�ǰPS����״̬
 �������  : PS����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-13
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_SetPsServiceStatus(NAS_MMC_SERVICE_ENUM_UINT8   enPsCurrService)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enPsCurrService = enPsCurrService;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsServiceStatus
 ��������  : ��ȡ��ǰCS����״̬
 �������  : CS����״̬
 �������  : ��
 �� �� ֵ  : ��ǰCS����״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-19
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/

NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enCsCurrService;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsServiceStatus
 ��������  : ��ȡ��ǰPS����״̬
 �������  : PS����״̬
 �������  : ��
 �� �� ֵ  : ��ǰPS����״̬
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011-07-19
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/

NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetPsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enPsCurrService;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextAvailableTimerValue
 ��������  : ��ȡ��ǰAvailableTimer��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰAvailableTimer��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��29��
    ��    ��   : z40661
    �޸�����   : DTS2012080908811,available timer��ʱ����������1��
  3.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
  4.��    ��   : 2014��1��26��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
  5.��    ��   : 2015��10��26��
    ��    ��   : h00281185
    �޸�����   : ����PrefBand��
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextAvailableTimerValue(VOS_VOID)
{

    VOS_UINT32                          ulTimerLen;

    //Fen = Ncell Priority?
    if (VOS_TRUE == NAS_MMC_IsNeedStartNcellAvailableTimer())
    {
        /* NCELLȫ�ֱ����д��ֻ�����֣�����ת�����Ժ���Ϊ��λ */
        if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchFirstTimerLen();
        }
        else
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchSecondTimerLen();
        }
    }
    else
    {
        ulTimerLen  = NAS_MMC_GetNextSearchSleepTimerLen();
    }

    return ulTimerLen;
}






/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchSleepTimerLen
 ��������  : ��ȡPrefBand��ʱ��ʱ����ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchSleepTimerLen(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                          *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU                          *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;

    VOS_UINT32                                              ulTimerLen;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen);
    }
    else
    {
        ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen);
    }

    return ulTimerLen;
}

/*************************************** L1 MAIN״̬�������Ĳ������� *************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurNormalAvailableTimerCount_L1Main
 ��������  : ��ȡavailble timer��ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��2��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main
 ��������  : Reset normal available timer��ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��2��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_VOID    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = 0;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddCurNormalAvailableTimerCount_L1Main
 ��������  : ������ͨavailble timer��ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��29��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��2��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_VOID    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount++;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-03-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurNormalAvailableTimerCount
 ��������  : ����availble timer��ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��3��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID   NAS_MMC_SetCurNormalAvailableTimerCount(
    VOS_UINT32                          ulCurTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = ulCurTimerCount;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-03-28, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartNcellAvailableTimer
 ��������  : �ж��Ƿ���Ҫ����ncell available
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����ncell available��VOS_FALSE:����Ҫ����ncell available
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
 3.��    ��   : 2014��6��17��
   ��    ��   : z00234330
   �޸�����   : PCINT����
*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedStartNcellAvailableTimer(VOS_VOID)
{
    VOS_UINT8                           ucNcellSearchFlag;
    VOS_UINT8                           ucNcellSearchTimerLen;
    VOS_UINT32                          ulAvailableSearchTimeLen;

    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucCsAttachAllowFlag;



    ucNcellSearchFlag          = NAS_MMC_GetNcellSearchFlag();
    ucPsAttachAllowFlag        = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlag        = NAS_MML_GetCsAttachAllowFlg();

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��ȡ��һ�׶�availableʱ������ncellʱ���� */
        ulAvailableSearchTimeLen    = NAS_MMC_GetPhaseOnePeriodicSleepTimerLen();
        ucNcellSearchTimerLen       = NAS_MMC_GetNcellSearchFirstTimerLen();
    }
    else
    {
        /* ��ȡ�ڶ��׶�availableʱ������ncellʱ���� */
        ulAvailableSearchTimeLen    = NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen();
        ucNcellSearchTimerLen       = NAS_MMC_GetNcellSearchSecondTimerLen();
    }

    /*
       1��֧��ncell��������nv����:
        -- modem1 gas�ϱ�����t��l������Ƶ����Ϣ����������Ϊ0ʱҲ������ncell�Ѷ�ʱ��
        -- ��ǰΪPS attach not allow/cs attach not allow,��ֹ������������ù���
        -- �����ͨavailable��ʱ��Ϊ5s��NCELL availableʱ��Ϊ10s��
          ��ʱ����Ҫ����NCELL available��ʱ������������5s ��ͨavailable��ʱ������ʱ��
          ��ͨ available������
          ���Ҫ����NCELL available��ʱ���Ļ�������������ͨavailable��ʱ��ʱ����
          ���ٿ���������NCELL available��ʱ������һ��NCELL available��ʱ����ʱ��NCELL�����ѣ�
          �ڶ��γ�ʱ����ͨAvailable��
        -- ���ncellʱ��Ϊ0����������ͨavailable��ʱ��
   */
   /* Modified by z00234330 for PCLINT����, 2014-06-16, begin */
    if ((VOS_TRUE == ucNcellSearchFlag)
     && (0 != ucNcellSearchTimerLen)
     && (ulAvailableSearchTimeLen >= (2*ucNcellSearchTimerLen))
     && (VOS_FALSE == ucPsAttachAllowFlag)
     && (VOS_FALSE == ucCsAttachAllowFlag))
    {
        return VOS_TRUE;
    }
    /* Modified by z00234330 for PCLINT����, 2014-06-16, end */

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartHistoryTimer
 ��������  : �Ƿ���Ҫ��history�Ѷ�ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��11��
    ��    ��   : c00318887
    �޸�����   : Ԥ��Ƶ�������Ż�,
  3.��    ��   : 2015��10��17��
    ��    ��   : h00281185
    �޸�����   : Ԥ��Ƶ�������Ż�, ���ñ�����ϵ�߼�

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedStartHistoryTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;

    VOS_UINT8                           ucHistoryNum;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();



    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��ȡ��һ�׶���ʷ�Ѵ��� */
        ucHistoryNum = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
    }
    else
    {
        /* ��ȡ�ڶ��׶���ʷ�Ѵ��� */
        ucHistoryNum = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
    }

    /* ����Ϊ0����ʾhistory���Թرգ�����Ҫ����history�Ѷ�ʱ�� */

    if (0 < ucHistoryNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartPrefBandTimer
 ��������  : �Ƿ���Ҫ��PrefBand�Ѷ�ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��09��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedStartPrefBandTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU      *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT8                           ucPrefBandNum;


    pstPhaseOneOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��ȡ��һ�׶�PrefBand�Ѵ��� */
        ucPrefBandNum = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
    }
    else
    {
        /* ��ȡ�ڶ��׶�PrefBand�Ѵ��� */
        ucPrefBandNum = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
    }

    /* ����Ϊ0����Ҫ����PrefBand�Ѷ�ʱ�� */
    if (0 < ucPrefBandNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAvailableTimerType_OnPlmn
 ��������  : ��ȡavailable��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��7��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����

*****************************************************************************/
NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8  NAS_MMC_GetAvailableTimerType_OnPlmn(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAvailableTimerType_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAvailableTimerType_OnPlmn
 ��������  : ����available��ʱ������
 �������  : enAvailableTimerType - available��ʱ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��7��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����

*****************************************************************************/
VOS_VOID  NAS_MMC_SetAvailableTimerType_OnPlmn(
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableTimerType
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAvailableTimerType_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType = enAvailableTimerType;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn
 ��������  : ��ȡncell������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn
 ��������  : Reset ncell������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
VOS_VOID  NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount = 0;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn
 ��������  : ���� ncell ������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
VOS_VOID  NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount++;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn
 ��������  : ��ȡhistory������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurHistorySearchTimerCount_OnPlmn
 ��������  : ����history������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SetCurHistorySearchTimerCount(
    VOS_UINT32                          ulCurHistorySearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = ulCurHistorySearchTimerCount;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn
 ��������  : ����history�Ѷ�ʱ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn
 ��������  : ���� history ������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount++;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn
 ��������  : �������PLMN Search��ض�ʱ���ļ���ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��11��05��
    ��    ��   : d00305650
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    /* Reset Normal Available Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount                 = 0;
    /* Reset NCell Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount      = 0;
    /* Reset History Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount    = 0;
    /* Reset PrefBand Timer Count */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount   = 0;
    /* Reset OOS Phase Num */
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn
 ��������  : ��ȡPrefBand������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��12��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurPrefBandSearchTimerCount_OnPlmn
 ��������  : ����PrefBand������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��12��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SetCurPrefBandSearchTimerCount(
    VOS_UINT32                          ulCurPrefBandSearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount = ulCurPrefBandSearchTimerCount;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn
 ��������  : ����PrefBand�Ѷ�ʱ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn
 ��������  : ���� PrefBand ������ǰ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��12��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount++;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetOosCurInfo
 ��������  : ��õ�ǰOOS״̬history timer/prefband timer/fullband timer�����Ĵ���
 �������  : NSA_MML_OOS_INFO_STRU              *pstOosInfo;

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��1��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_GetOosCurInfo(
    NAS_MML_OOS_INFO_STRU              *pstOosInfo
)
{
    NAS_MMC_FSM_CTX_STRU               *pstL1MainFsm = VOS_NULL_PTR;

    /* ��ǰ��NAS_MMC_FSM_L1_MAIN״̬�� */
    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        pstOosInfo->ucCurOosPhaseNum          = NAS_MMC_GetCurrOosSearchPhaseNum();
        pstOosInfo->ulCurHistoryTimerCount    = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();
        pstOosInfo->ulCurPrefBandTimerCount   = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();
        pstOosInfo->ulCurFullBandTimerCount   = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();
        return;
    }

    /* ��ǰ����NAS_MMC_FSM_L1_MAIN״̬����ȥջ�л�ȡNAS_MMC_FSM_L1_MAIN������ */
    pstL1MainFsm = NAS_MMC_GetBottomFsmInFsmStack();

    if (VOS_NULL_PTR == pstL1MainFsm)
    {
        pstOosInfo->ucCurOosPhaseNum = NAS_MMC_OOS_PHASE_BUTT;
        return;
    }

    pstOosInfo->ucCurOosPhaseNum        = NAS_MMC_GetCurrOosSearchPhaseNum();
    pstOosInfo->ulCurHistoryTimerCount  = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
    pstOosInfo->ulCurPrefBandTimerCount = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurPrefBandSearchTimerCount;
    pstOosInfo->ulCurFullBandTimerCount = pstL1MainFsm->unFsmCtx.stL1MainCtx.ulCurTimerCount;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsRegAdditionalAction_L1Main
 ��������  : ��ȡ״̬���������е�CSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �ڲ��б���������L1 MAIN�����Ľṹ
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_L1Main(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsRegAdditionalAction_L1Main
 ��������  : ����״̬���������е�CSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �ڲ��б���������L1 MAIN�����Ľṹ

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsRegAdditionalAction_L1Main
 ��������  : ��ȡ״̬���������е�PSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �ڲ��б���������L1 MAIN�����Ľṹ

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsRegAdditionalAction_L1Main
 ��������  : ����״̬���������е�PSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �ڲ��б���������L1 MAIN�����Ľṹ

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCLRegAdditionalAction_L1Main
 ��������  : ��ȡ״̬���������е�CLģʽ��ע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��1��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCLRegAdditionalAction_L1Main(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCLRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCLRegAdditionalAction_L1Main
 ��������  : ����״̬���������е�CLģʽ��ע���������ĺ�������
 �������  : NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��1��16��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetCLRegAdditionalAction_L1Main(
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enCLRegAdditionalAction
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCLRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction = enCLRegAdditionalAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllRegAdditionalAction_L1Main
 ��������  : ���״̬���������е�CS/PSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �ڲ��б���������L1 MAIN�����Ľṹ

 3.��    ��   : 2016��1��18��
   ��    ��   : w00176964
   �޸�����   : DTS2016011802320����:����CLģʽ�µĺ�������
*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllRegAdditionalAction_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCLRegAdditionalAction = NAS_MMC_CL_ADDITIONAL_ACTION_BUTT;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsRegAttemptCount_L1Main
 ��������  : ����״̬���������е�CSע�᳢�Դ���
 �������  : ulCsCount CSע�᳢�Դ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAttemptCount_L1Main(
    VOS_UINT32      ulCsCount
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = ulCsCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsRegAttemptCount_L1Main
 ��������  : ����״̬���������е�PSע�᳢�Դ���
 �������  : ulPsCount PSע�᳢�Դ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAttemptCount_L1Main(
    VOS_UINT32      ulPsCount
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = ulPsCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsRegAttemptCount_L1Main
 ��������  : ��ȡ״̬���������е�CSע�᳢�Դ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : CSע�᳢�Դ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCsRegAttemptCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsRegAttemptCount_L1Main
 ��������  : ��ȡ״̬���������е�PSע�᳢�Դ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : PSע�᳢�Դ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPsRegAttemptCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllRegAttemptCount_L1Main
 ��������  : ���״̬���������е�CS/PSע�᳢�Դ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllRegAttemptCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = 0;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = 0;
}

/*************************************** �������״̬�������Ĳ������� *************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn
 ��������  : ���������л�ȡMMģ�鿪���ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : MMģ�鿪���ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn
 ��������  : ���������л�ȡ��ȡSIM���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡSIM���ļ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32   NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitSimFilesFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearMmStartCnfFlg_SwitchOn
 ��������  : �������������MM/GMM�Ŀ����ظ����
 �������  : MM/GMM�����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg &= ~enMmStartCnfFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn
 ��������  : �������������MM��GMM�Ŀ����ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg = NAS_MMC_WAIT_MMGMM_START_CNF_NULL;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllAsStartCnfFlg_SwitchOn
 ��������  : ���������������ȡSIM���ļ��ظ����
 �������  : SIM���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg &= ~enSimFileCnfFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllWaitSimFilesFlg_SwitchOn
 ��������  : ����������������ж�ȡSIM���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitSimFilesFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg = NAS_MML_READ_USIM_FILE_FLG_NULL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn
 ��������  : ��������������MM/GMMģ�鿪���ظ����
 �������  : MM/GMMģ�鿪���ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg |= enMmStartCnfFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn
 ��������  : ��������������SIM���ļ��ظ����
 �������  : SIM���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg |= enSimFileCnfFlg;
}

/*************************************** �ػ����״̬�������Ĳ������� *************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMmPowerOffCnfFlg_PowerOff
 ��������  : ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : MM/GMMģ��ػ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetMmPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMmPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAsPowerOffCnfFlg_PowerOff
 ��������  : ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ػ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetAsPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAsPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetMmPowerOffCnfFlag_PowerOff
 ��������  : ����MM/GMMģ��ػ��ظ����
 �������  : MM/GMMģ��ػ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg |= enMmPowerOffFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAsPowerOffCnfFlag_PowerOff
 ��������  : ����ASģ��ػ��ظ����
 �������  : ASģ��ػ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_SetAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg |= enAsPowerOffFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff
 ��������  : ���MM/GMMģ��ػ��ظ����
 �������  : MM/GMMģ��ػ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg &= ~enMmPowerOffFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMasterModeRat_PowerOff
 ��������  : ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ػ���ģ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-08-17
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetMasterModeRat_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMasterModeRat_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetMasterModeRat_PowerOff
 ��������  : ���ùػ�ʱ��ģ�Ľ��뼼����־
 �������  : MM/GMMģ��ػ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-17
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetMasterModeRat_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMasterModeRat_PowerOff:ENTERED");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat = enMasterModeRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSlaveModeRatList_PowerOff
 ��������  : ��ȡ�ػ�״̬���������еĴ�ģ�ػ�������˳��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������ģ�ػ�������˳��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-12-26
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MML_PLMN_RAT_PRIO_STRU *NAS_MMC_GetSlaveModeRatList_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSlaveModeRatList_PowerOff:ENTERED");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stPowerOffCtx.stSlaveModeList);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildSlaveModeRatList_PowerOff
 ��������  : �ػ�ʱ��������ģ������ģ�б�
 �������  : enMasterModeRat:��ǰ��ģ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��26��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_BuildSlaveModeRatList_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                 *pstSlaveModeList = VOS_NULL_PTR; /* ���͹ػ�����Ĵ�ģ�б� */
    VOS_UINT8                                   ucRatIndex;
    VOS_UINT8                                   i;

    pstSlaveModeList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    ucRatIndex = 0;

    /* �Ȱ�ƽ̨���뼼��������LWG���ӵ���ģ�б��� */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif


    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

    pstSlaveModeList->ucRatNum = ucRatIndex;

    /* ����ģ���б���ɾ�� */
    for (i = 0; i < ucRatIndex; i++)
    {
        if (pstSlaveModeList->aucRatPrio[i] == enMasterModeRat)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstSlaveModeList->aucRatPrio[i]),
                        &(pstSlaveModeList->aucRatPrio[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1) * sizeof(pstSlaveModeList->aucRatPrio[i]));
            /*lint +e961*/
            pstSlaveModeList->ucRatNum--;
            break;
        }
    }

    return;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff
 ��������  : ���ASģ��ػ��ظ����
 �������  : ASģ��ػ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg &= ~enAsPowerOffFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff
 ��������  : �������MM/GMMģ��ػ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg = NAS_MMC_MMGMM_POWER_OFF_NULL_FLG;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff
 ��������  : �������ASģ��ػ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff:ENTERED");

    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg = NAS_MMC_AS_POWER_OFF_NULL_FLG;

    return;
}

/*************************************** ��ϵͳ��ѡ���״̬�������Ĳ������� *************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendRspFlg_InterSysCellResel
 ��������  : ��ȡ����ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetResumeRspFlg_InterSysCellResel
 ��������  : ��ȡ�ָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetResumeOrign_InterSysCellResel
 ��������  : ��ȡ�ָ�����ö��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ָ�����ö��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014-01-27
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
*****************************************************************************/
MMC_RESUME_ORIGEN_ENUM_UINT8 NAS_MMC_GetResumeOrign_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetResumeOrign_InterSysCellResel
 ��������  : ���ûָ�����ö��
 �������  : �ָ�����ö��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014-01-27
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetResumeOrign_InterSysCellResel(
    MMC_RESUME_ORIGEN_ENUM_UINT8        enResumeOrign
)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeOrign_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign = enResumeOrign;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSuspendRspFlag_InterSysCellResel
 ��������  : �������ظ����
 �������  : ��Ҫ����Ĺ���ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearResumeRspFlag_InterSysCellResel
 ��������  : ����ָ��ظ����
 �������  : ��Ҫ����Ļָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSuspendRspFlag_InterSysCellResel
 ��������  : ����ָ��ظ����
 �������  : ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetResumeRspFlag_InterSysCellResel
 ��������  : ����ָ��ظ����
 �������  : �ָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel
 ��������  : ������й���ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel
 ��������  : ������лָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortFlag_InterSysCellResel
 ��������  : ����С����ѡ״̬���������е�Abort��־
 �������  : ulAbortFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��15��
    ��    ��  : s00217060
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_InterSysCellResel(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg = ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortFlag_InterSysCellResel
 ��������  : ��ȡС����ѡ״̬���������е�Abort��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulAbortFlg��Abort��־
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��15��
    ��    ��  : s00217060
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAbortFlag_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel
 ��������  : ����С����ѡ״̬���������е��Ƿ��Ѿ���������LMM���͹�SuspendRelReq��־
 �������  : ucSndSuspendRelReqFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��21��
    ��    ��  : s00217060
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(
    VOS_UINT8                           ucSndSuspendRelReqFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg = ucSndSuspendRelReqFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel
 ��������  : ��ȡС����ѡ״̬���������е��Ƿ��Ѿ���������LMM���͹�SuspendRelReq��־��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucSndSuspendRelReqFlg���Ƿ��Ѿ���������LMM���͹�SuspendRelReq��־
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��21��
    ��    ��  : s00217060
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg;
}


/*************************************** ��ϵͳOOS���״̬�������Ĳ������� *************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendRspFlg_InterSysOos
 ��������  : ��ȡ����ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetResumeRspFlg_InterSysOos
 ��������  : ��ȡ�ָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSuspendRspFlag_InterSysOos
 ��������  : �������ظ����
 �������  : ��Ҫ����Ĺ���ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearResumeRspFlag_InterSysOos
 ��������  : ����ָ��ظ����
 �������  : ��Ҫ����Ļָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSuspendRspFlag_InterSysOos
 ��������  : ����ָ��ظ����
 �������  : ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetResumeRspFlag_InterSysOos
 ��������  : ����ָ��ظ����
 �������  : �ָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllSuspendRspFlag_InterSysOos
 ��������  : ������й���ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllResumeRspFlag_InterSysOos
 ��������  : ������лָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*************************************** ��ϵͳHO���״̬�������Ĳ������� *************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendRspFlg_InterSysHo
 ��������  : ��ȡ����ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetResumeRspFlg_InterSysHo
 ��������  : ��ȡ�ָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSuspendRspFlag_InterSysHo
 ��������  : �������ظ����
 �������  : ��Ҫ����Ĺ���ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearResumeRspFlag_InterSysHo
 ��������  : ����ָ��ظ����
 �������  : ��Ҫ����Ļָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSuspendRspFlag_InterSysHo
 ��������  : ����ָ��ظ����
 �������  : ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetResumeRspFlag_InterSysHo
 ��������  : ����ָ��ظ����
 �������  : �ָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllSuspendRspFlag_InterSysHo
 ��������  : ������й���ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllResumeRspFlag_InterSysHo
 ��������  : ������лָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsSigExistFlag_InterSysHo
 ��������  : ����CS�������Ӵ��ڱ��
 �������  : CS�������Ӵ��ڱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-11-26
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetCsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg = ucSigExistFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsSigExistFlag_InterSysHo
 ��������  : ����PS�������Ӵ��ڱ��
 �������  : PS�������Ӵ��ڱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-11-26
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetPsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg = ucSigExistFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsSigExistFlag_InterSysHo
 ��������  : ��ȡCS�������Ӵ��ڱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : CS�������Ӵ��ڱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  NAS_MMC_GetCsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsSigExistFlag_InterSysHo
 ��������  : ��ȡPS�������Ӵ��ڱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS�������Ӵ��ڱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  NAS_MMC_GetPsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg;
}



/*************************************** ��ϵͳCCO���״̬�������Ĳ������� *************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSuspendRspFlg_InterSysCco
 ��������  : ��ȡ����ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetResumeRspFlg_InterSysCco
 ��������  : ��ȡ�ָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ָ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSuspendRspFlag_InterSysCco
 ��������  : �������ظ����
 �������  : ��Ҫ����Ĺ���ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearResumeRspFlag_InterSysCco
 ��������  : ����ָ��ظ����
 �������  : ��Ҫ����Ļָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSuspendRspFlag_InterSysCco
 ��������  : ����ָ��ظ����
 �������  : ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetResumeRspFlag_InterSysCco
 ��������  : ����ָ��ظ����
 �������  : �ָ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllSuspendRspFlag_InterSysCco
 ��������  : ������й���ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllResumeRspFlag_InterSysCco
 ��������  : ������лָ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011-07-11
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetL1MainCtx_L1Main
 ��������  : ��ȡL1MAIN״̬�������ĵĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : L1MAIN״̬�������ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��5��
    ��    ��  : w00167002
    �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_L1_MAIN_CTX_STRU* NAS_MMC_GetL1MainCtx_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetL1MainCtx_L1Main,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSelectionCtx_PlmnSelection
 ��������  : ��ȡѡ��״̬�������ĵĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ѡ��״̬�������ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��5��
    ��    ��  : w00167002
    �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU* NAS_MMC_GetPlmnSelectionCtx_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionCtx_PlmnSelection,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx);
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortFlag_PlmnSelection
 ��������  : ��ȡ״̬���������е�Abort��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAbortFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortFlag_PlmnSelection
 ��������  : ����״̬���������е�Abort��־
 �������  : ulAbortFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_PlmnSelection(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg = ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRelRequestFlag_PlmnSelection
 ��������  : ��ȡ״̬���������е�Rel Request��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetRelRequestFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRelRequestFlag_PlmnSelection
 ��������  : ����״̬���������е�Rel Request��־
 �������  : ucRelRequestFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetRelRequestFlag_PlmnSelection(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnSelectionRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg = ucRelRequestFlg;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection
 ��������  : ��ȡ״̬���������е�searched plmn info�Ƿ��ϱ�������rplmn��hplmn��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ����
             VOS_FALSE - ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection
 ��������  : ����״̬���������е�searched plmn info�Ƿ��ϱ�������rplmn��hplmn��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ����
             VOS_FALSE - ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(
    VOS_UINT8                           ucExistRplmnOrHplmnFlag
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag = ucExistRplmnOrHplmnFlag;
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetInterSysSuspendRat_PlmnSelection
 ��������  : ��������״̬���������е��յ�SUSPEND_IND��ʾ��ϵͳʱ�Ľ��뼼��
 �������  : enRat
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��8��5��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetInterSysSuspendRat_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat = enRat;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetInterSysSuspendRat_PlmnSelection
 ��������  : ��ȡ��������״̬���������е��յ�SUSPEND_IND��ʾ��ϵͳʱ�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_RAT_SEARCH_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��8��5��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetInterSysSuspendRat_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitRegRsltFlag_PlmnSelection
 ��������  : ��ȡ״̬���������еĵȴ�CS/PS��ע�����ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��22��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetWaitRegRsltFlag_PlmnSelection
 ��������  : ����״̬���������еĵȴ�CS/PS��ע�����ı�־
 �������  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��22��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(VOS_UINT8 ucWaitFlag)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection
 ��������  : ���״̬���������еĵȴ�ָ�����ע�����ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��22��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(
    VOS_UINT8                           ucRegDomain
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection
 ��������  : ���״̬���������еĵȴ�CS/PS���ע�����ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��22��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection()
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsRegAdditionalAction_PlmnSelection
 ��������  : ��ȡ״̬���������е�CSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(VOS_VOID)
{

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsRegAdditionalAction_PlmnSelection
 ��������  : ����״̬���������е�CSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsRegAdditionalAction_PlmnSelection
 ��������  : ��ȡ״̬���������е�PSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsRegAdditionalAction_PlmnSelection
 ��������  : ����״̬���������е�PSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsRegCause_PlmnSelection
 ��������  : ��ȡ״̬���������е�CSע������ Cause
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetCsRegCause_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsRegCause_PlmnSelection
 ��������  : ��ȡ״̬���������е�PSע������ Cause
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetPsRegCause_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsRegCause_PlmnSelection
 ��������  : ����״̬���������е�CSע������ Cause
 �������  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause = enCsCause;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsRegCause_PlmnSelection
 ��������  : ����״̬���������е�PSע������ Cause
 �������  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause = enPsCause;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection
 ��������  : ��ȡ����ѡ��״̬���������е������б���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��7��11��
   ��    ��  : s46746
   �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU * NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection()
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stPlmnSelectionListInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection
 ��������  : ��ȡ����״̬����������ĳ���뼼���յ�������searched plmn info ind�Ƿ���й������ʶ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��30��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection
 ��������  : ��������״̬����������ĳ���뼼���յ�������searched plmn info ind�Ƿ���й������ʶ
 �������  : enRat                        - ���뼼��
             ucSearchedRoamPlmnSortedFlag - �յ�������searched plmn info ind�Ƿ���й������ʶ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��30��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchedRoamPlmnSortedFlag
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = ucSearchedRoamPlmnSortedFlag;
            return;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHistorySearchedFlag_PlmnSelection
 ��������  : ��ȡ����״̬����������ĳ���뼼�����Ƿ������HISTORY������
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");

        return VOS_FALSE;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetHistorySearchedFlag_PlmnSelection
 ��������  : ��������״̬����������ĳ���뼼���Ƿ���ɸ�������HISTORY������
 �������  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
             VOS_UINT8                           ucHistorySearchedFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucHistorySearchedFlag
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag = ucHistorySearchedFlag;

            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection
 ��������  : ָ���Ľ��뼼���б��Ƿ��������HISTORY����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:ָ���Ľ��뼼���б��������HISTORY����
             VOS_FALSE:ָ���Ľ��뼼���б����δHISTORY������RAT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��1��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* �ҵ�δ����HISTORY�ѵ�RAT */
        if (VOS_FALSE == NAS_MMC_GetHistorySearchedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_FALSE;
        }
    }

    /* ָ���Ľ��뼼���б��������HISTORY���� */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection
 ��������  : ָ���Ľ��뼼���б����Ƿ���������������RAT
 �������  : ��
 �� �� ֵ  : VOS_TRUE:ָ���Ľ��뼼���б���������������RAT
             VOS_FALSE:ָ���Ľ��뼼���б����������������RAT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��1��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* �ҵ��Ź����RAT,�򷵻�TRUE */
        if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    /* ��û���Ź���,�򷵻�FALSE */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAllBandSearch_PlmnSelection
 ��������  : ��ȡ����״̬����������ĳ���뼼�����Ƿ�ȫƵ������־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��26��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAllBandSearch_PlmnSelection
 ��������  : ��������״̬���������е��Ƿ�ȫƵ������־
 �������  : enRat
             ucAllBandSearch
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucAllBandSearch
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand = ucAllBandSearch;
            return;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRatCoverage_PlmnSelection
 ��������  : ��������״̬���������е��Ƿ���ڸ��Ǳ�־
 �������  : enRat
             enCoverType
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:��չ���Ǳ�����,���ָߵ����������縲��
*****************************************************************************/
VOS_VOID NAS_MMC_SetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType = enCoverType;
            return ;
        }
    }

    /* ��δ�ҵ����µĽ��뼼���������LOG��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:NOT FOUND THE enRAT");
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRatCoverage_PlmnSelection
 ��������  : ��ȡ����״̬���������е��Ƿ���ڸ��Ǳ�־
 �������  : enRat

 �������  : enCoverType
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return NAS_MMC_COVERAGE_TYPE_BUTT;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType;

        }
    }

    return NAS_MMC_COVERAGE_TYPE_BUTT;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchRplmnAndHplmnFlg
 ��������  : ��ȡ����״̬����������ĳ���뼼���Ƿ���й�RPLMN+HPLMN��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��22��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchRplmnAndHplmnFlg
 ��������  : ��������״̬����������ĳ���뼼���Ƿ���й�RPLMN+HPLMN��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��22��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = ucSearchRplmnAndHplmnFlg;
            return;
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection
 ��������  : ��ȡ����״̬����������ĳ���뼼���Ƿ���й�RPLMN+EPLMN��
 �������  : enRat - ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection
 ��������  : ��������״̬����������ĳ���뼼���Ƿ���й�RPLMN+EPLMN������ʶ
 �������  : enRat - ���뼼��
             ucSearchRplmnAndEplmnFlg - �Ƿ���й�rplmn+eplmn������ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndEplmnFlg
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = ucSearchRplmnAndEplmnFlg;
            return;
        }
    }
}


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection
 ��������  : �����Ż������п�������HPLMN���ȣ���ȡ�Ƿ��Ѿ��ѹ�HPLMN�ı�ʾ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��18��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection
 ��������  : �����Ż������п�������HPLMN���ȣ������Ƿ��Ѿ��ѹ�HPLMN�ı�ʾ
 �������  : enRat                        - ���뼼��
             ucSwithOnAddHplmnFlg         - �Ƿ��Ѿ��ѹ�HPLMN�ı�ʾ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��18��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchDplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = ucSearchDplmnAndHplmnFlg;
            return;
        }
    }
}
/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

/*lint -e438 -e830*/
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitSearchRatInfo_PlmnSelection
 ��������  : ��ʼ������״̬���������в�ͬ���뼼���ĸ��Ǽ�������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��26��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 3.��    ��   : 2013��02��01��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:����ƽ̨���뼼���������ж�
 4.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 5.��    ��   : 2014��9��9��
   ��    ��   : z00161729
   �޸�����   : DTS2014082807343:csfb������gu��mmc�����������rplmn+eplmn���������������T303��ʱ����ʧ�ܳ���
 6.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�

 7.��    ��   : 2015��5��21��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
 8.��    ��   : 2015-5-18
   ��    ��   : c00318887
   �޸�����   : DPlmn���ݺ����Ƚ���HPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo = VOS_NULL_PTR;

    pstSearchRatInfo = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);

     /* �Ƚ��г�ʼ������ʣ��ĳ�ʼ��Ϊ��Чֵ */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg   = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucHistorySearchedFlag    = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

    }

    i = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        /* ����LTE���뼼��δȫƵ����,�����ڸ��� */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_LTE;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

        i++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        /* ����WCDMA���뼼��δȫƵ����,�����ڸ��� */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

        i++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        /* ����GSM���뼼��δȫƵ����,�����ڸ��� */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_GSM;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

        i++;
    }

    return;
}

/*lint +e438 +e830*/


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetForbRoamLaInfo_PlmnSelection
 ��������  : ��ȡ����ѡ��״̬���������еĽ�ֹ����λ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ֹ����λ������Ϣ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��11��11��
   ��    ��  : w00167002
   �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU* NAS_MMC_GetForbRoamLaInfo_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbRoamLaInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbRoamLaInfo);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection
 ��������  : ��ȡ����ѡ��״̬���������еĽ�ֹPLMN FOR GPRS��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ֹPLMN��Ϣ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2012��05��10��
   ��    ��  : l65478
   �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbGprsPlmn);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurrSearchingPlmn_PlmnSelection
 ��������  : ����PLMN SELECTION״̬��������������������plmn��Ϣ
 �������  : pstPlmnId -- PLMN SELECTION��ǰ����������plmn��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��21��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn = *pstPlmnId;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrSearchingPlmn_PlmnSelection
 ��������  : ����PLMN SELECTION״̬���������еĵ�ǰ����������PLMN��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMN SELECTION״̬������������plmn��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��08��21��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurrSearchingType_PlmnSelection
 ��������  : ����PLMN SELECTION״̬����������������plmn����
 �������  : enCurrSearchingPlmnType -- PLMN����������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurrSearchingType_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enCurrSearchingType
)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType = enCurrSearchingType;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrSearchingType_PlmnSelection
 ��������  : ��ȡPLMN SELECTION״̬����������������plmn����
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMN SELECTION״̬��������plmn����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
1.��    ��   : 2015��05��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MMC_GetCurrSearchingType_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType);
}



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection
 ��������  : ����PLMN SELECTION״̬������������Ҫ����פ��LTE��PLMN��Ϣ
 �������  : pstPlmnId -- PLMN SELECTIONʱפ����PLMN ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn = *pstPlmnId;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection
 ��������  : ����PLMN SELECTION״̬���������еĵ�ǰפ����PLMN��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_ID_STRU* -- PLMN SELECTIONʱפ����PLMN ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��11��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection()
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn);
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortFlag_AnyCellSearch
 ��������  : ��ȡAnycellPlmnSrch״̬���������е�Abort��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��26��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAbortFlag_AnyCellSearch(VOS_VOID)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortFlag_AnyCellSearch
 ��������  : ����AnycellPlmnSrch״̬���������е�Abort��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��26��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_AnyCellSearch(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag = ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmCtxAddr_AnyCellSearch
 ��������  : ��ȡAnyCellSearch״̬���������ĵ�ָ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��27��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU* NAS_MMC_GetFsmCtxAddr_AnyCellSearch(VOS_VOID)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_AnyCellSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRatNum_AnyCellSearch
 ��������  : ��ȡAnyCell״̬��֧�ֵĽ��뼼���ĸ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��27��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRatNum_AnyCellSearch(VOS_VOID)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatNum_AnyCellSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio.ucRatNum;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelMsUnsupportRat
 ��������  : ɾ��MS��֧�ֵĽ��뼼��
 �������  : pstRatPrioList:���뼼�����ȼ��б�
 �������  : pstRatPrioList:ɾ����MS��֧�ֵĽ��뼼�����ȼ��б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��8��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_DelMsUnsupportRat(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stNewPrioList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstMsPrioRatList  = VOS_NULL_PTR;
    VOS_UINT32                          ulRatIndex;
    VOS_UINT32                          ulMsRatIndex;

    VOS_UINT8                          ucNewRatNum;
    ucNewRatNum      = NAS_MMC_NUM_ZERO;
    pstMsPrioRatList = NAS_MML_GetMsPrioRatList();

    /*��ʼ���м�ṹ����*/
    stNewPrioList.ucRatNum = ucNewRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        stNewPrioList.aucRatPrio[ulRatIndex] = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    for ( ulRatIndex = 0 ; ulRatIndex < pstRatPrioList->ucRatNum; ulRatIndex++ )
    {
        for ( ulMsRatIndex = 0 ; ulMsRatIndex < pstMsPrioRatList->ucRatNum; ulMsRatIndex++ )
        {
            if (pstRatPrioList->aucRatPrio[ulRatIndex] == pstMsPrioRatList->aucRatPrio[ulMsRatIndex])
            {
                stNewPrioList.aucRatPrio[ucNewRatNum]= pstRatPrioList->aucRatPrio[ulRatIndex];
                ucNewRatNum++;
                stNewPrioList.ucRatNum = ucNewRatNum;
            }
        }
    }

    pstRatPrioList->ucRatNum = stNewPrioList.ucRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        pstRatPrioList->aucRatPrio[ulRatIndex] = stNewPrioList.aucRatPrio[ulRatIndex];
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRatPrioList_AnyCellSearch
 ��������  : ����AnyCell״̬��֧�ֵĽ��뼼���б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��12��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��8��
   ��    ��   : z00161729
   �޸�����   : DTS2012083007796:�޿�֧������ҵ��ʱ����Ӧ����ѡ��gu��anycellפ��
 3.��    ��   : 2015��9��17��
   ��    ��   : w00167002
   �޸�����   : DTS2015091602371:�ĵ���������2G/3G anycell����
*****************************************************************************/
VOS_VOID NAS_MMC_SetRatPrioList_AnyCellSearch(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstAnycellPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulIsLteOnly;
    VOS_UINT8                           ucSupportCsServiceFlg;
    VOS_UINT8                           ucSimCsPsRegStatus;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulIsSupportLte;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    /* Added by w00167002 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */

    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    ucLowPrioAnycellSearchLteFlg        = NAS_MML_GetLowPrioAnycellSearchLteFlg();
    /* Added by w00167002 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, end */

    pstSimStatus          = NAS_MML_GetSimStatus();
    ucSimCsPsRegStatus    = VOS_TRUE;
    ulIsLteOnly           = NAS_MML_IsLteOnlyMode(pstRatPrioList);
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();
    ulIsSupportLte        = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                       pstRatPrioList);
    ucIndex               = 0;
    enMsMode              = NAS_MML_GetMsMode();
    PS_MEM_SET(&stAnycellSrchRatList, (VOS_CHAR)0x0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        ucSimCsPsRegStatus = VOS_FALSE;
    }
#endif

    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatPrioList_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnycellPrioList = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio);

    pstAnycellPrioList->ucRatNum = pstRatPrioList->ucRatNum;

    for ( i = 0 ; i < pstRatPrioList->ucRatNum; i++ )
    {
        pstAnycellPrioList->aucRatPrio[i] = pstRatPrioList->aucRatPrio[i];
    }

    /* 45008Э������: If the mobile station supports CS voice services,the MS shall avoid
       reselecting acceptable(but not suitable) E-UTRA cells regardless of the priorities
       in system information,֧��cs����ҵ���޿���csps������Ч���µ�anycell�ѣ���L��ģ������ps only
       (����������ps only��3��6��8�ܾ���Ҫ����L),��L�Ľ��뼼��������� */
#if (FEATURE_ON == FEATURE_LTE)

    /* Modified by w00167002 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */
    if ( (((VOS_FALSE == NAS_MML_GetSimPresentStatus())
         || (VOS_FALSE == ucSimCsPsRegStatus)
         || (VOS_TRUE == ucLowPrioAnycellSearchLteFlg))
        && (VOS_TRUE == ucSupportCsServiceFlg)
        && (VOS_FALSE == ulIsLteOnly)
        && (VOS_TRUE == ulIsSupportLte)
        && (NAS_MML_MS_MODE_PS_ONLY != enMsMode)))
    /* Modified by w00167002 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */
    {
        for (i = 0; i < pstRatPrioList->ucRatNum; i++)
        {
            if (pstRatPrioList->aucRatPrio[i] != NAS_MML_NET_RAT_TYPE_LTE)
            {
                stAnycellSrchRatList.aucRatPrio[ucIndex] = pstRatPrioList->aucRatPrio[i];
                ucIndex++;
            }
        }

        stAnycellSrchRatList.aucRatPrio[ucIndex] = NAS_MML_NET_RAT_TYPE_LTE;
        ucIndex++;
        stAnycellSrchRatList.ucRatNum = ucIndex;
        PS_MEM_CPY(pstAnycellPrioList, &stAnycellSrchRatList, sizeof(stAnycellSrchRatList));
    }
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchRat_AnyCellSearch
 ��������  : ANY CELL����ʱ��ȡ�¸�Ҫ������������뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8: ���뼼��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��27��
    ��    ��   : L00171473
    �޸�����   : V7R1 phase II �޸�
  3.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable �����Լ�detach����

  4.��    ��   : 2012��9��15��
    ��    ��   : z40661
    �޸�����   : DTS2012082006273,δ֪ͨL
****************************************************************************/

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSearchRat_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();
    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    for ( i = 0; i < ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* ��ȡLTE������״̬ */
        enLteCapabilityStatus   = NAS_MML_GetLteCapabilityStatus();

        /* ���뼼��ΪLTE�ҵ�ǰLTE״̬Ϊdisableʱ����ѡ��LTE�Ľ��뼼�� */
        if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS  == enLteCapabilityStatus))
         && (NAS_MML_NET_RAT_TYPE_LTE   == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i]))
        {
            continue;
        }
#endif

        if ( VOS_FALSE == pstAnyCellSearchCtx->aucSearchedFlag[i])
        {
            /* ��ȡ�¸�δ�������Ľ��뼼�� */
            return pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i];
        }
    }

    /* ��ȡ�¸�δ�������Ľ��뼼��ʧ�� */
    return NAS_MML_NET_RAT_TYPE_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSearchedFlag_AnyCellSearch
 ��������  : ���ݴ���Ľ��뼼�������øý��뼼��������״̬Ϊ���ѹ�
 �������  : enSpecRat:����µĽ��뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��27��
    ��    ��   : L00171473
    �޸�����   : V7R1 phase II �޸�
****************************************************************************/

VOS_VOID NAS_MMC_SetSearchedFlag_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    /* ��ȡAnyCell����״̬���������ĵ�ַ */
    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    for (i = 0; i < NAS_MMC_GetRatNum_AnyCellSearch(); i++)
    {
        if ( enSpecRat == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i])
        {
            /* ���øý��뼼��Ϊ���ѹ� */
            pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_TRUE;
        }
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmCtx_SysCfg
 ��������  : SYSCFG״̬�������ĵĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011-07-10
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��1��
   ��    ��   : w00176964
   �޸�����   : GUNAS V7R1 PhaseIV �׶ε���
 3.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 4.��    ��   : 2015��9��16��
   ��    ��   : wx270776
   �޸�����   : SYSCFG�ϱ�˳���޸�
****************************************************************************/
VOS_VOID NAS_MMC_InitFsmCtx_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord  = VOS_NULL_PTR;

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pstSyscfgSettingRecord              = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_FALSE);

    /* SYSCFG״̬���������������ĳ�ʼ��:Ĭ�ϲ���Ҫ���� */
    NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_FALSE);

    /* SYSCFG״̬�������������ý�������ȼ�˳����Ϣ�ĳ�ʼ��:
       ����������ʼ��Ϊ0,ÿ����SYSCFG�󣬸���������1����ʾҪ����SYSCFG�Ľ���ģʽ */
    pstSyscfgSettingRecord->ucSetCurrSyscfgIndex = 0;

    /* ������Ҫ�·�SYSCFG���ܸ��� */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = 0;

    /* ��ʼ�����·�SYSCFG�����˳��ΪLUG�����ƽ̨��֧��ĳ�����뼼���������ý��뼼���������� */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_LTE;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_GSM;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[2]= NAS_MML_NET_RAT_TYPE_BUTT;
#else
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
#endif

    NAS_MMC_SetPrePrioRatList_SysCfg(&stPrePrioRatList);
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */
    return ;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SysCfg_GetSyscfgSettingRecord
 ��������  : ��ȡ״̬���е�NAS_MMC_SYSCFG_SETTING_CTRL_STRU�ṹֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : SYSCFG״̬���������еļ�¼���ý�������ȼ�˳����Ϣ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011-07-10
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

****************************************************************************/
NAS_MMC_SYSCFG_SETTING_CTRL_STRU* NAS_MMC_GetSysCfgSettingRecord_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSysCfgSettingRecord_SysCfg,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.stSyscfgSettingRecord);
}

/* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPrePrioRatList_SysCfg
 ��������  : ����״̬����������syscfg����ǰ�Ľ��뼼�������ȼ�
 �������  : pstPrePrioRatList - ���뼼�������ȼ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012-08-15
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

****************************************************************************/
VOS_VOID NAS_MMC_SetPrePrioRatList_SysCfg(
    NAS_MML_PLMN_RAT_PRIO_STRU          *pstPrePrioRatList
)
{
    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList
                   = *pstPrePrioRatList;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPrePrioRatList_SysCfg
 ��������  : ��ȡ״̬����������syscfg����ǰ�Ľ��뼼�������ȼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���뼼�������ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012-08-15
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

****************************************************************************/
NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MMC_GetPrePrioRatList_SysCfg(VOS_VOID)
{
    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList);
}

/* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddSysCfgIndex_SysCfg
 ��������  : ������һ����Ҫ����SYSCFGģ�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddSysCfgIndex_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSysCfgIndex_SysCfg,ERROR:FsmId Error");
    }

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pstSysCfgRecord   = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* ����INDEX����,ָ����һ��Ҫ����SYSCFG���õĽ��뼼�� */
    pstSysCfgRecord->ucSetCurrSyscfgIndex ++;

    /* ���� */
    return ;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSettingRat_SysCfg
 ��������  : ��ȡ��һ����Ҫ����SYSCFGģ�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8����:���뼼��,�о�����
             NAS_MML_NET_RAT_TYPE_GSM,
             NAS_MML_NET_RAT_TYPE_WCDMA,
             NAS_MML_NET_RAT_TYPE_LTE,
             NAS_MML_NET_RAT_TYPE_BUTT

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSettingRat_SysCfg(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *pucSyscfgRatPrio    = VOS_NULL_PTR;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     ucNextSyscfgRat;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstSysCfgRecord      = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pucSyscfgRatPrio     = pstSysCfgRecord->aucSyscfgRatPrio;

    /* ��������Ե������õ��ܸ��������ؽ��뼼��Ϊ��Чֵ����ʾSYSCFG���ý��� */
    if ( pstSysCfgRecord->ucSetCurrSyscfgIndex >= pstSysCfgRecord->ucTotalSyscfgNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* ȡ����������������Ӧ�Ľ��뼼�� */
    ucNextSyscfgRat                     = pucSyscfgRatPrio[pstSysCfgRecord->ucSetCurrSyscfgIndex];

    /* ������ҪSYSCFG���õĽ��뼼�� */
    return ucNextSyscfgRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSearchFlag_SysCfg
 ��������  : ��ȡSYSCFG״̬�����Ƿ���Ҫ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����SYSCFG״̬�����Ƿ���Ҫ��������Ϣ��ַ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011-07-18
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

****************************************************************************/
VOS_UINT32  NAS_MMC_GetPlmnSearchFlag_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    return (pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPlmnSearchFlag_SysCfg
 ��������  : ����SYSCFG״̬�����Ƿ���Ҫ��������Ϣ
 �������  : �Ƿ���Ҫ��������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011-07-20
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

****************************************************************************/
VOS_VOID NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_UINT32 ulNeedSearchPlmnFlag)
{
    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag = ulNeedSearchPlmnFlag;
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SysCfg_SetSendingSysCfgOrder
 ��������  : �����������·�SYSCFG���Ⱥ�˳��
 �������  : enDestRat: Ŀ��ģ�Ľ��뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��30��
   ��    ��   : w00167002
   �޸�����   : DTS2011113001438:����MMC֪ͨGUL�����˳�����ΪĿ��ģ���֪ͨ.

                �޸�ԭ��:syscfgex����ģʽ��Ƶ�θı�ʱMMC��Ҫ֪ͨGUL 3������ģ��
                Ŀǰ֪ͨ3��������˳��Ϊ�ȷ���ģ���ٷ��ʹ�ģ����ģ��˳��Ĭ��
                ΪL������W������G����at^syscfgex=? ^syscfgex:"0201",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,0,0.
                ��ǰפ��Wģ,����at^syscfgex="03",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,0,0
                ����ֻ֧��L,MMC�ȸ���ģW����RRMM_SYS_CFG_REQ,�յ�W��RRMM_SYS_CFG_CNF�ظ�,
                �ٸ�L����ID_MMC_LMM_SYS_CFG_REQ,�յ�L��ID_LMM_MMC_SYS_CFG_CNF,
                ����G����RRMM_SYS_CFG_REQ����ģW�յ�RRMM_SYS_CFG_REQ�����
                deactive�Լ���֪ͨL��������������ʱL��û�յ�ID_MMC_LMM_SYS_CFG_REQ
                ֪ͨL֧�֣����޷���������syscfg���ú�û����ģ���á���MMC
                ��Ҫ�޸�֪ͨGUL 3��������˳��ΪĿ��ģ���֪ͨ��

 3.��    ��   : 2012��12��26��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:����Ϊֻ��ƽ̨֧�ֵĽ���㷢��SYSCFG����

 4.��    ��   : 2015��9��7��
   ��    ��   : wx270776
   �޸�����   : 1.�����㣺
                  Austin����������MODEM0��MODEM2��GPHY����һ��GBBP����������һ��GPHYʹ��GBBP֮��
                  ��Ҫ�ȵ�GBBP��ȫ˯�ߺ���һ��GPHY����ʹ��GBBP��
                2.���з��������У�SYSCFG˳���������У���
                  ������������GAS��SYSCFG���̵ȵ�GBBP˯�ߺ󣬸�NAS�ظ�SYSCFG_CNF��
                  ����������W��ģ��G��ģ��W����G��SYSCFGȥ����Gģ��GAS���յ�SYSCFG_REQ��
                            GAS�޷���ֹͣWPHY������ֹͣGPHY�Ĳ�����Ҳ�����޷�����ͣ��W����G��
                            ��Ҳ���޷��ȵ�GPHY˯���ٻظ�SYSCFG_CNF��
                3.SYSCFG˳�����������
                  ����������ģʽ�����·����������֮�䲻ָ��˳�� ʣ�µ�ģʽ����ģ�ٴ�ģ��
                  �����ģ֮�䲻ָ��˳�򣬶����ģ֮�䲻ָ��˳��

*****************************************************************************/
VOS_VOID NAS_MMC_SetSysCfgSendingOrder_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg
)
{
    VOS_UINT32                          i;
    /* ���������Ľ��뼼���б� */
    NAS_MML_PLMN_RAT_PRIO_STRU          stTempRatList;
    /* ����SYSCFG�ϱ���˳�� */
    NAS_MML_PLMN_RAT_PRIO_STRU          stSyscfgSendingOrder;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord = VOS_NULL_PTR;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSysCfgSendingOrder_SysCfg,ERROR:FsmId Error");
    }

    /* ȡ�õ�ǰ SYSCFG״̬���������еļ�¼���ý�������ȼ�˳����Ϣ */
    pstSyscfgSettingRecord  = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* ��ʼ�� */
    PS_MEM_SET(&stSyscfgSendingOrder, 0x00, sizeof(stSyscfgSendingOrder));
    stSyscfgSendingOrder.ucRatNum = pstSyscfgSettingRecord->ucTotalSyscfgNum;
    PS_MEM_CPY( stSyscfgSendingOrder.aucRatPrio,
                pstSyscfgSettingRecord->aucSyscfgRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    /* 1. �ҳ������Ľ��뼼����������ʱ���б��� */
    NAS_MML_GetNewRatFromRatList( NAS_MML_GetMsPrioRatList(),
                                  &(pstSysCfgMsg->stRatPrioList),
                                  &stTempRatList );

    /* 2. ����ǰ��ģ���ȼ����õ���� */
    NAS_MML_SortSpecRatPrioHighest( NAS_MML_GetCurrNetRatType(),
                                    &stSyscfgSendingOrder );

    /* 3. �������Ľ��뼼�����򵽽��뼼���б���� */
    for ( i = stTempRatList.ucRatNum; i > 0 ; i-- )
    {
        NAS_MML_SortSpecRatPrioHighest( stTempRatList.aucRatPrio[i-1],
                                        &stSyscfgSendingOrder );
    }

    /* ��SYSCFG�ϱ�˳�����ȫ�ֱ����� */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = stSyscfgSendingOrder.ucRatNum;
    PS_MEM_CPY( pstSyscfgSettingRecord->aucSyscfgRatPrio,
                stSyscfgSendingOrder.aucRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRelRequestFlag_SysCfg
 ��������  : ��ȡSysCfg״̬���������е��Ƿ������������ӱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE :����������
             VOS_FALSE:�����ȴ��ͷ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��01��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRelRequestFlag_SysCfg(VOS_VOID)
{
    /* �����ǰ״̬������ SysCfg, �쳣��ӡ */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_SysCfg,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRelRequestFlag_SysCfg
 ��������  : ����SysCfg״̬���������е��Ƿ������������ӱ�־
 �������  : ucRelRequestFlg: �Ƿ������������ӱ�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��01��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetRelRequestFlag_SysCfg(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* �����ǰ״̬������ SysCfg, �쳣��ӡ  */
    if (NAS_MMC_FSM_SYSCFG !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_SysCfg,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg = ucRelRequestFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg
 ��������  : �ж�SYSCFG���õ��µ�ǰפ���������Ƿ���������
 �������  : pstSysCfgSetParm:�û�SYSCFG���õ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : SYSCFG���õ��µ�ǰפ����������������
             VOS_FALSE : SYSCFG���õ��µ�ǰפ�������粻��������
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011��08��04��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
               ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
               ��������ͣ���������ȽϿ��ܻ����
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg          = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId           = VOS_NULL_PTR;
    VOS_UINT32                          ulFlg;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg,ERROR:FsmId Error");
    }

    pstRoamCfg      = NAS_MML_GetRoamCfg();

    /* ȡ�õ�ǰפ����PLMN ID */
    pstPlmnId       = NAS_MML_GetCurrCampPlmnId();

    /* ��HPLMN��ͬ��ֱ�ӷ������� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /* �������Կ��عرգ�ֱ�ӷ������� */
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg)
    {
        return VOS_TRUE;
    }

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    /* ��������ʱֱ�ӷ������� */
    if (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
    {
        return VOS_TRUE;
    }


    /* �жϵ�ǰ�����Ƿ���������������б��� */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNationalRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );

    /* ��SYSCFG����׼����й������Σ��ҵ�ǰ������������������б��У�����׼������ */
    if ( (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability)
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    /* ��SYSCFG���ò�׼����й������Σ��ҵ�ǰ���������β�֧��ʱ����ע�������У�����׼������ */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNotRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );
    if ( ( (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
        || (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability) )
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }
	/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* ���򷵻ز��������� */
    return VOS_FALSE;
}

/* LIST����״̬�������Ĳ������� */
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitSearchRatInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����г�ʼ����Ҫ�����Ľ��뼼����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* ����һ����ʱ���뼼���б�, ���ڵ��� */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ǰ���뼼������,��ǰ���뼼��������ǰ�� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* ��ʼ�����뼼�����ȼ��б��Լ�������� */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchRatInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ�����Ľ��뼼�����ȼ��б���Ϣ�Լ�������¼
 �������  : ��
 �������  : ��
 �� �� ֵ  : PLMN LIST�����Ľ��뼼�����ȼ��б���Ϣ�Լ�������¼
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *NAS_MMC_GetSearchCtrlInfo_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRatInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnListCtrlInfo[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchingRat_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ�¸���Ҫ�����Ľ��뼼��
 �������  : ��
 �������  : penRat �¸���Ҫ�����Ľ��뼼��
 �� �� ֵ  : ��ȡ������VOS_TRUE
             ��ȡ��������VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32  NAS_MMC_GetNextSearchingRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucRatNum;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;

    for ( i = 0; i < ucRatNum; i++)
    {
        if ( VOS_FALSE == pstSearchRatInfo[i].ucSearchedFlag)
        {
            /* ��ȡ�¸�δ�������Ľ��뼼�� */
            *penRat  = pstSearchRatInfo[i].enRat;
            return VOS_TRUE;
        }
    }

    /* ��ȡ�¸�δ�������Ľ��뼼��ʧ�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetOrigenSearchRat_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ��ʼ�����Ľ��뼼��
 �������  : ��
 �������  : penRat ��ʼ�����Ľ��뼼��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_GetOrigenSearchRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetOrigenSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    *penRat = pstSearchRatInfo[0].enRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSearchedFlag_PlmnList
 ��������  : PLMN LIST����״̬�����й���������ָ���Ľ��뼼��������
 �������  : enSpecRat �Ѿ��������Ľ��뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_SetSearchedFlag_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    VOS_UINT32                              i;
    VOS_UINT8                               ucRatNum;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU     *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU   *pstListInfo      = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_PlmnList,ERROR:FsmId Error");
       return ;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;
    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i = 0; i < ucRatNum; i++)
    {
       if ( enSpecRat == pstSearchRatInfo[i].enRat )
       {
           pstSearchRatInfo[i].ucSearchedFlag = VOS_TRUE;

           /* �����������������б��������Ľ��뼼�������ں������ݽ��뼼�����б���и��� */
           pstListInfo[i].enRatType           = enSpecRat;
           break;
       }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortFlag_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ״̬����ϱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ״̬����ϱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT8 NAS_MMC_GetAbortFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortFlag_PlmnList
 ��������  : PLMN LIST����״̬�����й���������״̬����ϱ��
 �������  : ״̬����ϱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_SetAbortFlag_PlmnList(
    VOS_UINT8                           ucAbortFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg = ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNotifyMsccFlag_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ֪ͨMSCC����ı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ�֪ͨMSCC����ı��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNotifyMsccFlag_PlmnList
 ��������  : PLMN LIST����״̬�����й���������֪ͨMSCC����ı��
 �������  : ֪ͨMSCC����ı��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_SetNotifyMsccFlag_PlmnList(
    VOS_UINT8                           ucNotifyFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg= ucNotifyFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitRegRsltFlag_PlmnList
 ��������  : ��ȡ״̬���������еĵȴ�CS/PS��ע�����ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetWaitRegRsltFlag_PlmnList
 ��������  : ����״̬���������еĵȴ�CS/PS��ע�����ı�־
 �������  : NAS_MMC_WAIT_REG_RSLT_IND_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnList(
    VOS_UINT8       ucWaitFlag
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList
 ��������  : ���״̬���������еĵȴ�ָ�����ע�����ı�־
 �������  : ucRegRslt    CS+PSע����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(
    VOS_UINT8                           ucRegRslt
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag &= ~ucRegRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList
 ��������  : ���״̬���������еĵȴ�CS/PS���ע�����ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsRegAdditionalAction_PlmnList
 ��������  : ��ȡ״̬���������е�CSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnList(VOS_VOID)
{

    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsRegAdditionalAction_PlmnList
 ��������  : ����״̬���������е�CSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsRegAdditionalAction_PlmnList
 ��������  : ��ȡ״̬���������е�PSע���������ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnList(VOS_VOID)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsRegAdditionalAction_PlmnList
 ��������  : ����״̬���������е�PSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRegRsltInfo_PlmnList
 ��������  : ��ȡ״̬���������е�ע������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU *NAS_MMC_GetRegRsltInfo_PlmnList(VOS_VOID)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRegRsltInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitSearchedPlmnListInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����г�ʼ���������������б���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:��ʼ�����縲������
*****************************************************************************/

VOS_VOID NAS_MMC_InitSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId() )
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i= 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* �����ȼ��б� */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* �����ȼ��б� */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitSearchedPlmnListInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ�������������б���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��Ҫ�����������б���Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnSearchInfo[0]);
}

#if (FEATURE_ON == FEATURE_CSG)

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����г�ʼ��CSG�������������б���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��15��
   ��    ��   : s00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ*/
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitCsgSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    /* ��ʼ��CSG��������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    PS_MEM_SET(pstCsgPlmnIdList, 0, sizeof(NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU));

    for ( i= 0; i < RRC_NAS_MAX_PLMN_CSG_ID_NUM; i++ )
    {
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId                      = NAS_MML_INVALID_CSG_ID_VALUE;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat          = RRC_NAS_RAT_TYPE_BUTT;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ��������CSG�����б���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ״̬���б����CSG�����б��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��16��
   ��    ��   : s00193151
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stCsgListSearchedPlmnInfoList);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList
 ��������  : ��鵱ǰPLMN�Ƿ��Ѿ���PLMN LIST����״̬����ĳ���뼼�������������
 �������  : NAS_MML_PLMN_ID_STRU*                    ���жϵ�PLMN
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STR*     �Ѿ������õ�ĳ���뼼���µ���������б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE: �Ѿ��ڴ��б���; VOS_FALSE: ���ڴ��б���
 ���ú���  : ���ô˺����ĺ������뱣֤��β�Ϊ��ָ��
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��16��
   ��    ��   : s00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(
    NAS_MML_PLMN_ID_STRU                          *pstPlmnId,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU          *pstSearchedPlmnList
)
{
    /* ����ظ���ֻҪ�ߵ������б�����һ���Ѿ����ڴ�PLMN���򷵻��Ѿ��ڱ��� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                    (VOS_UINT8)NAS_MML_MIN(pstSearchedPlmnList->ulHighPlmnNum, NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM),
                    pstSearchedPlmnList->astHighPlmnList))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList(pstPlmnId,
                    (VOS_UINT8)NAS_MML_MIN(pstSearchedPlmnList->ulLowPlmnNum, NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM),
                    pstSearchedPlmnList->astLowPlmnList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList
 ��������  : PLMN LIST����״̬�����й����н�CSG�б��ѽ�����µ��������������б���Ϣ
 �������  : pstRrcList  �������������б���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  : ���ô˺����ĺ������뱣֤��β�Ϊ��ָ��
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��16��
   ��    ��   : s00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrio = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList,ERROR:FsmId Error");
       return;
    }

    /* ʵ��˼·�ܼ򵥣���״̬���������б����CSG ID��������б��У�ȡ��ÿ��PLMN ID�����浽״̬��������ԭ
    �����Ǹ������ȼ���������б��У��������ĸ��µ��������б��У��������ĸ��µ��������б��У�����ʱ����
    �ظ��������������Ѿ����˴�PLMN������������� */

    /* �ֲ�������ʼ�� */
    ulIndex         = 0;
    pstRatPrio      = NAS_MML_GetMsPrioRatList();
    ucRatNum        = pstRatPrio->ucRatNum;
    stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    pstRatPrio      = NAS_MML_GetMsPrioRatList();

    /* ����������б���������Ӧ���뼼�����б� */
    for (i = 0; i < ucRatNum; i++)
    {
        for (j = 0; j < NAS_MML_MIN(pstCsgPlmnList->ulHighPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); j++)
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat, &enRat);

            /* ����жϵ�PLMN�뵱ǰѭ���ĵ�i�����뼼����ͬ�����һ�������Ƿ���뵱ǰ���뼼���ĸ����ȼ��б� */
            if (enRat == pstListInfo[i].enRatType)
            {
                stPlmnId.ulMcc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

                /* ����ظ����������û�д�PLMN������ӣ�������� */
                if (VOS_TRUE != NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(&stPlmnId, &pstListInfo[i]))
                {
                    ulIndex = pstListInfo[i].ulHighPlmnNum;
                    pstListInfo[i].astHighPlmnList[ulIndex].ulMcc = stPlmnId.ulMcc;
                    pstListInfo[i].astHighPlmnList[ulIndex].ulMnc = stPlmnId.ulMnc;
                    pstListInfo[i].ulHighPlmnNum ++;

                    /* ��֤���鲻Խ�� */
                    if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                    {
                        /* ����Խ�磬�������ѭ�� */
                        i = ucRatNum;
                        break;
                    }
                }
            }
        }
    }

    /* ����������б���������Ӧ���뼼�����б� */
    for (i = 0; i < ucRatNum; i++)
    {
        /* ��ȥ��������PLMN��ʣ�µĶ��ǵ�������PLMN��������ʼλ���Ǵ����1��������PLMN����1����ʼ */
        for (j = pstCsgPlmnList->ulHighPlmnNum; j < NAS_MML_MIN(pstCsgPlmnList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); j++)
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat, &enRat);

            /* ����жϵ�PLMN�뵱ǰѭ���ĵ�i�����뼼����ͬ�����һ�������Ƿ���뵱ǰ���뼼���ĵ����ȼ��б� */
            if (enRat == pstListInfo[i].enRatType)
            {
                stPlmnId.ulMcc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

                /* ����ظ����������û�д�PLMN������ӣ�������� */
                if (VOS_TRUE != NAS_MMC_IsBcchPlmnIdInSearchedPlmnList_PlmnList(&stPlmnId, &pstListInfo[i]))
                {
                    ulIndex = pstListInfo[i].ulLowPlmnNum;
                    pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc = stPlmnId.ulMcc;
                    pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc = stPlmnId.ulMnc;
                    pstListInfo[i].astLowPlmnList[ulIndex].lRscp = pstCsgPlmnList->astCsgListSearchedPlmnInfoList[j].lRscp;
                    pstListInfo[i].ulLowPlmnNum ++;

                    /* ��֤���鲻Խ�� */
                    if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                    {
                        /* ����Խ�磬�������ѭ�� */
                        i = ucRatNum;
                        break;
                    }
                }
            }
        }
    }

    /* ���ݸߵ������������¸������� */
    for (i = 0; i < ucRatNum; i++)
    {
        pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;

        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;
        }

        if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;
        }
    }

    return;

}


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList
 ��������  : PLMN LIST����״̬�����й����и����������������б���Ϣ
 �������  : pstRrcList  �������������б���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
*****************************************************************************/

VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(
    RRC_PLMN_ID_LIST_STRU              *pstRrcList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    ucRatNum        = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* ����������б���������Ӧ���뼼�����б� */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulHighPlmnNum; j++ )
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[j].ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulHighPlmnNum;
                pstListInfo[i].astHighPlmnList[ulIndex].ulMcc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMcc;

                pstListInfo[i].astHighPlmnList[ulIndex].ulMnc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMnc;

                pstListInfo[i].ulHighPlmnNum ++;

                /* ��֤���鲻Խ�� */
                if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                {
                    /* ����Խ�磬�������ѭ�� */
                    i = ucRatNum;
                    break;
                }
            }

        }
    }

    /* ����������б���������Ӧ���뼼�����б� */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulLowPlmnNum; j++ )
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[j].PlmnId.ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulLowPlmnNum;
                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMcc;

                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMnc;

                pstListInfo[i].astLowPlmnList[ulIndex].lRscp
                       = pstRrcList->aLowPlmnList[j].lRscp;

                pstListInfo[i].ulLowPlmnNum ++;

                /* ��֤���鲻Խ�� */
                if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                {
                    /* ����Խ�磬�������ѭ�� */
                    i = ucRatNum;
                    break;
                }
            }
        }
    }

    /* ���ݸߵ������������¸������� */
    for ( i = 0; i < ucRatNum; i++ )
    {
        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
        }
        else if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
        }
        else
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPreLteDisableFlg_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡL disable��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : Lte capability״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��8��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT8 NAS_MMC_GetPreLteDisableFlg_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPreLteDisableFlg_PlmnList
 ��������  : PLMN LIST����״̬�����й���������L disable��״̬
 �������  : enLteCapStatus - Lte capability״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��8��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_SetPreLteDisableFlg_PlmnList(
    VOS_UINT8                           ucPreLteDisableFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg = ucPreLteDisableFlg;
    return;

}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAnyCellSrchFlg_PlmnList
 ��������  : PLMN LIST����״̬�����й����л�ȡ��Ҫ����anycell�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : anycell�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��31��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT8 NAS_MMC_GetAnyCellSrchFlg_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAnyCellSrchFlg_PlmnList
 ��������  : PLMN LIST����״̬�����й���������anycell�������
 �������  : anycell�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��31��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_SetAnyCellSrchFlg_PlmnList(
    VOS_UINT8                           ucAnyCellSrchFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg = ucAnyCellSrchFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitHighPrioPlmnSearchCtx
 ��������  : ��ʼ�������ȼ���������������
 �������  : �����ȼ���������������ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��2��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��2��
   ��    ��   : w00167002
   �޸�����   : ���Ӷ�RESERVE�ֶεĳ�ʼ��
 3.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE��������Ŀ:�������������г�ʼ����
 4.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����TD�³�ʱ����
*****************************************************************************/
VOS_VOID NAS_MMC_InitHighPrioPlmnSearchCtx(NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU *pstHighPrioPlmnSearchCtrl)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstHighPrioPlmnSearchCtrl->ucFirstStartHPlmnTimerFlg                       = VOS_TRUE;
    pstHighPrioPlmnSearchCtrl->enPlmnSelectionListType                         = NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST;
    pstHighPrioPlmnSearchCtrl->ucTdHighRatSearchCount                          = 0;
    pstHighPrioPlmnSearchCtrl->aucReserve[0]                                   = 0;

    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.usSearchPlmnNum = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[0]   = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[1]   = 0;

    for (i = 0; i < NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST; i++)
    {
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].enPlmnType     = NAS_MMC_PLMN_TYPE_BUTT;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].ucRatNum       = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[0]  = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[1]  = 0;

        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality   = NAS_MMC_NET_QUALITY_BUTT;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].ucReserve   = 0;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHighPrioPlmnList
 ��������  : ��ȡ�����ȼ������б�ָ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ȼ������б�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��20��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *NAS_MMC_GetHighPrioPlmnList(VOS_VOID)
{

    return &(g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.stHighPrioPlmnSearchListInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSelectionListType
 ��������  : ��ȡ��ǰMMC�����ȫ�ֱ����е�ѡ���б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionListType(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPlmnSelectionListType
 ��������  : ���õ�ǰ��MMC��ȫ�ֱ����б����ѡ���б�����
 �������  : enPlmnSelectionListType:���õ�ǰ��MMC��ȫ�ֱ����б����ѡ���б�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetPlmnSelectionListType(
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8             enListType
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType = enListType;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetTdHighRatSearchCount
 ��������  : ��ȡ��ǰMMC�����ȫ�ֱ����еĸ����ȼ�������ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucTdHighRatSearchCount
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetTdHighRatSearchCount(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddTdHighRatSearchCount
 ��������  : ���ӵ�ǰMMC�����ȫ�ֱ����еĸ����ȼ�������ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucTdHighRatSearchCount
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_AddTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount++;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitTdHighRatSearchCount
 ��������  : ��ʼ����ǰMMC�����ȫ�ֱ����еĸ����ȼ�������ʱ����������
 �������  : enPlmnSelectionListType:���õ�ǰ��MMC��ȫ�ֱ����б����ѡ���б�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNetScanReq
 ��������  : ��ȡ�����NetScan REQ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NetScan����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��16��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
MSCC_MMC_NET_SCAN_REQ_STRU *NAS_MMC_GetNetScanReq(VOS_VOID)
{
    return &(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNetScanReq
 ��������  : ��ȡ�����NetScan REQ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NetScan����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��16��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetNetScanReq(
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    PS_MEM_CPY(&(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq),
                pstNetScanReq,
                sizeof(MSCC_MMC_NET_SCAN_REQ_STRU));

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecRatPrio
 ��������  : ��ȡ�ض����뼼���ڽ��뼼���б��е����ȼ�
 �������  : NAS_MMC_NET_RAT_TYPE_ENUM_U8        enRat
 �������  : ��
 �� �� ֵ  : RRC_NAS_RAT_PRIO_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��10��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : V7_phaseII����

*****************************************************************************/
RRMM_RAT_PRIO_ENUM_UINT8 NAS_MMC_GetSpecRatPrio(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
)
{
    VOS_UINT32                          i;

    /* ���Ҷ�Ӧ���뼼���Ƿ���֧���б��� */
    for ( i = 0; i < pstRatList->ucRatNum; i++ )
    {
        if ( (pstRatList->aucRatPrio[i] == enRat)
          && (enRat < NAS_MML_NET_RAT_TYPE_BUTT) )
        {
            break;
        }
    }

    /* ���ҳɹ�,���ض�Ӧ�Ľ��뼼�����ȼ� */
    if ( i < pstRatList->ucRatNum )
    {
        /*���뼼�������ȼ����Ӹߵ������� */
        return (VOS_UINT8)(RRMM_RAT_PRIO_HIGH - i);
    }

    /* ����֧���б���ʱ���������ȼ�ΪNULL*/
    else
    {
        return RRMM_RAT_PRIO_NULL;
    }

}




/*****************************************************************************
 �� �� ��  : NAS_MMC_GetEHPlmn
 ��������  : �ṩ��������ȡEHPLMN��API�ӿں���
 �������  : ��
 �������  : NAS_MML_PLMN_ID_STRU *pstEHPlmn:EHPLMN�б���Ҫ�ܴ洢32��PLMNID
             VOS_UINT32 *pulEHPlmnNum:EHPLMN����
 �� �� ֵ  : VOS_OK :��ȡ�ɹ�������EHPLMN����home plmn(��֧��EHPLMN����EHPLMN�б�Ϊ��)
             VOS_ERR:��ȡʧ�ܣ��������ʧ�ܻ����޿����߿�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��13��
   ��    ��   : W00167002
   �޸�����   : ͬ����V7R1_PHASEII

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetEHPlmn(
    RRC_PLMN_ID_STRU                   *pstEHPlmn,
    VOS_UINT8                          *pucEHPlmnNum
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHplmn = VOS_NULL_PTR;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSimFlg;

    /* ��ȡ��ǰ��SIM��״̬��Ϣ */
    pstSimStatus = NAS_MML_GetSimStatus();
    ucSimFlg    = pstSimStatus->ucSimPresentStatus;

    if ((VOS_NULL_PTR == pstEHPlmn) || (VOS_NULL_PTR == pucEHPlmnNum))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, input para is null.");
        return VOS_ERR;
    }

    if (VOS_FALSE == ucSimFlg)
    {

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, sim is absent or locked");
        return VOS_ERR;
    }

    pstSimEHplmn = NAS_MML_GetSimEhplmnList();

    /* ���EHPLMN�ĸ��� */
    *pucEHPlmnNum  = pstSimEHplmn->ucEhPlmnNum;

    /* ��ȡEHPLMN */
    for (i = 0; i < (*pucEHPlmnNum); i++)
    {
        pstEHPlmn[i].ulMcc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmn[i].ulMnc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMnc;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateGURegRlstRPlmnIdInNV
 ��������  : ע��ɹ�����µ�ǰ��RPLMN��RAT��RPLMN��ȫ�ֱ�����NV����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��6��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateGURegRlstRPlmnIdInNV(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PlMN��ʶ */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    VOS_UINT32                          ulGRplmnChangeFlag;
    VOS_UINT32                          ulWRplmnChangeFlag;
    VOS_UINT32                          ulRatChangeFlag;

    ulGRplmnChangeFlag = VOS_FALSE;
    ulWRplmnChangeFlag = VOS_FALSE;
    ulRatChangeFlag    = VOS_FALSE;

    /* ���ڻ�ȡRPLMN�Ķ���������Ϣ */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* ��ȡ��ǰ�Ľ��뼼�� */
    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* �������һ��ע��ɹ���PLMN,û��Rplmnʱ������ʧ�� */
    if (VOS_FALSE == NAS_MML_GetRPlmn(enCurrRat, &stPlmnId))
    {
        return;
    }

    /* ����ȫ�ֱ����е�LastRPLMN�Ľ��뼼�� */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        ulRatChangeFlag = VOS_TRUE;
        NAS_MML_SetLastRplmnRat(enCurrRat);
    }


    /* ����ȫ�ֱ����е�RPLMN */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
        ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stWRplmnInNV);
        /* ��֧��˫RPLMN����W��G��RPLMN������ */
        pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;
        pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;

    }
    else
    {
        /* ֧��˫RPLMN, ��ֻ���¶�Ӧ���뼼����RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
            pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;

        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                                 &pstRplmnCfgInfo->stWRplmnInNV);
            pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;
        }
        else
        {
            ;
        }
    }

    if ((VOS_TRUE ==ulRatChangeFlag)
     || (VOS_TRUE == ulWRplmnChangeFlag)
     || (VOS_TRUE == ulGRplmnChangeFlag))
    {
        NAS_MMC_WriteRplmnWithRatNvim();
    }

    return;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveUserReselPlmnInfo
 ��������  : ���û�ָ������ǰ�����浱ǰ��������Ϣ��
             ����������״̬�£����浱ǰ������ID�Ͷ�Ӧ��RAT;
             �����Ʒ����£�����HOME PLMN�������û����õ����ȼ�����RAT��
             ���û�ָ������ʧ�ܣ���ʾ�ص�ԭ��������ʱʹ�ô���Ϣ��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��2��21��
   ��    ��   : l65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��20��
   ��    ��   : L00171473
   �޸�����   : V7R1 phase II �޸�

*****************************************************************************/
VOS_VOID NAS_MMC_SaveUserReselPlmnInfo(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList    = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        /* ����������״̬�£����浱ǰפ��������ID�Ͷ�Ӧ��RAT */
        NAS_MMC_SetUserReselPlmnId( NAS_MML_GetCurrCampPlmnId(),
                                    NAS_MML_GetCurrNetRatType() );
    }
    else
    {
        /* ԭ�����Զ�ģʽ����Ҫ���档
           ԭ�����ֶ�����ģʽ�������Ʒ���״̬��˵���ɵ�PLMN��Ϣ�Ѿ�����,��ʱ����
           Ҫ�ٱ��棬�����ԭ����PLMN ID��Ϣ��� */
        if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            enRatType    = NAS_MML_GetCurrNetRatType();

            /* ��ȡMML�б���ĵ�ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ� */
            pstPlmnRatList = NAS_MML_GetMsPrioRatList();

            /* ��ȡ�û����õ����ȼ�RAT */
            if (pstPlmnRatList->ucRatNum != 0)
            {
                enRatType = pstPlmnRatList->aucRatPrio[0];
            }

            /* �����Ʒ����£�����HOME PLMN�����û����õ����ȼ�RAT */
            NAS_MMC_SetUserReselPlmnId(&(NAS_MML_GetSimEhplmnList()->astEhPlmnInfo[0].stPlmnId),
                                       enRatType);
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPlmnRegRejInfo
 ��������  : ��PlmnID,��,Causeֵ���RegInfo
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : L00171473
    �޸�����   : V7R1 PhaseII �޸�

  3.��    ��   : 2011��8��6��
    ��    ��   : zhoujun 40661
    �޸�����   : REG INFO�ṹ�����仯�������ú���
  4.��    ��   : 2011��11��2��
    ��    ��   : z00161729
    �޸�����   : ����ע���޸�L֧��cs��Ҫ����reg info
  5.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
*****************************************************************************/
VOS_VOID  NAS_MMC_SetPlmnRegRejInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    NAS_MML_LAI_STRU                   *pstCurrLai;
    VOS_UINT32                          i;
    VOS_UINT8                           ucCurrCampRac;

    if (VOS_NULL_PTR == pstPlmnRegInfo)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnRegRejInfo:WARNING:pstPlmnRegInfo IS NULL POINTER");
        return;
    }

    /* ��ȡ��ǰ�Ľ��뼼�� */
    enCurrRat     = NAS_MML_GetCurrNetRatType();
    pstCurrLai    = NAS_MML_GetCurrCampLai();
    ucCurrCampRac = NAS_MML_GetCurrCampRac();

    pstPlmnRegInfo->stPlmnId = *pstPlmnId;

    for (i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstPlmnRegInfo->aucLac[i] = pstCurrLai->aucLac[i];
    }
    pstPlmnRegInfo->ucRac = ucCurrCampRac;

    NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MMC_SetPlmnRegRejInfo: PLMN MCC, MNC, Domain and Reg Fail Cause",
                    pstPlmnRegInfo->stPlmnId.ulMcc,
                    pstPlmnRegInfo->stPlmnId.ulMnc,
                    enDomain,
                    enCause);

    NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MMC_SetPlmnRegRejInfo: RAT, LAI and RAC ",
                    enCurrRat,
                    pstPlmnRegInfo->aucLac[0],
                    pstPlmnRegInfo->aucLac[1],
                    pstPlmnRegInfo->ucRac);

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enWCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enWPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
#if   (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_EPS == enDomain)
        {
            pstPlmnRegInfo->enLPsRegStatus  = enCause;
            return;
        }
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enLCsRegStatus = enCause;
            return;
        }
    }
#endif
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_FillPlmnRegInfo: NORMAL: enCurrRat is wrong!");
    }


}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnRegInfoList
 ��������  : ����g_MmcPlmnSrchCtrl.astPlmnRegInfoList�ж�ӦPlmnId��ע����
             ��ǰPlmnID���б���ʱ�����£�
             �����б���ʱ����ӣ�
             �б�����ʱ�������������Ϣ,������ϢǨ��
 �������  : pstPlmn,��Ҫ���µ�����
             enDomain,��Ҫ���µķ�����
             enCause,���µ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : L00171473
    �޸�����   : V7R1 PhaseII �޸�
  3.��    ��   : 2011��12��12��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  4.��    ��   : 2012��1��9��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:����������ע��ԭ��ֵʱ������PLMN����ע���
                 ������CauseֵΪNAS_MML_REG_FAIL_CAUSE_NULL,�򲻱��档�ܾ�����
                 ������һֱ���������������ע��ԭ��ֵʱ����ô����ܱ���64����
                 ��һֱ���ػ�������£��ڻ��������ʱ�򣬴������⣬Ӧ���Ӵ˴��޸ġ�
  5.��    ��   : 2014��5��28��
    ��    ��   : z00234330
    �޸�����   : covertity�޸�
  6.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ȡע��ԭ���б��ָ�� */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* �жϵ�ǰ�����Ƿ�����ע���б���   */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);


    /* ��ǰ������ע�ᱻ���б��� */
    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    if ( ulIndex < NAS_MML_MIN(pstPlmnRegRejInfo->ucPlmnRegInfoNum ,(NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */
    {
        /* �����������б��д���,����ע��ԭ��ֵ */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause, (pstPlmnRegList + ulIndex));
        /*lint -e961*/
        /* �ж������Ƿ����ע��ʧ�ܵ�����Ϣ����δ����ע��ʧ�ܵ�����Ϣ���򽫴�����ӱ�����Ϣ����ɾ�� */
        if ( VOS_TRUE == NAS_MMC_IsPlmnRegInfoAllSucc( pstPlmnRegList + ulIndex ) )
        {
            (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList + ulIndex, (pstPlmnRegList + ulIndex + 1),
                (pstPlmnRegRejInfo->ucPlmnRegInfoNum - ulIndex - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

            /* �����б��еĸ��� */
            pstPlmnRegRejInfo->ucPlmnRegInfoNum--;
        }
        /*lint +e961*/
        return;
    }

    /* �����粻��ע�������ע��ԭ��ֵΪNULL,�򲻱��� */
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == enCause )
    {
        return;
    }

    /* ��ǰ���粻�ڱ�����б��л��б�Ϊ�� */
    if (pstPlmnRegRejInfo->ucPlmnRegInfoNum < NAS_MMC_MAX_REG_PLMN_INFO_NUM)
    {
        /* �б�δ����׷��ע��ԭ���б��� */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
                     (pstPlmnRegList + pstPlmnRegRejInfo->ucPlmnRegInfoNum));

        /* �����б��еĸ��� */
        pstPlmnRegRejInfo->ucPlmnRegInfoNum++;
    }
    else
    {
        /* �б�����, ����ļ�¼�ƶ������� */
        (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList, (pstPlmnRegList + 1),
                   (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

        /* ����ע��ԭ���б��� */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
              (pstPlmnRegList + (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)));
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertHplmnRegStatusToDomainInfo
 ��������  : ����ע����ת��Ϊ��������Ϣ
 �������  : pstPlmnRegInfo - hplmnע������Ϣ
 �������  : pucDomainInfo  - ��������Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertHplmnRegStatusToDomainInfo(
    VOS_UINT8                          *pucDomainInfo,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    enNetRatType   = NAS_MML_GetCurrNetRatType();
    *pucDomainInfo = NAS_MMC_REG_DOMAIN_NONE;

    switch (enNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_EPS;
                return;
            }
            return;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertHplmnRegStatusToDomainInfo:invalid rat type");
            return;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHplmnRejDomainInfo
 ��������  : ��ȡEhplmn��Hplmn���ܾ�����
 �������  : ��
 �������  : pucRejDomainRlst,��ǰPlmn��ע�ᱻ������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��5��
   ��    ��   : luokaihui / l00167671
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��15��
   ��    ��   : W00167002
   �޸�����   : ����ǰ���粻ΪHPLMN��ֱ�ӷ���ǰ��Ҫ���ܾ�����дΪ0������Ϊ���ֵ�����ܳ���
 3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU

 4.��    ��   : 2014��5��28��
   ��    ��   : z00234330
   �޸�����   : covertity�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_GetHplmnRejDomainInfo(
    VOS_UINT8                          *pucRejDomainRlst
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* ��ȡ��ǰפ����PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* ���ڻ�ȡHPLMNע�ᱻ�ܵ��б� */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ǰפ��PLMN����HPLMN�б��У���ֱ�ӷ��� */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;

        return;
    }

    /* �жϵ�ǰ�����Ƿ���HPLMNע�ᱻ���б��� */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);


    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    if (ulIndex < NAS_MML_MIN(pstRegRejCtx->ucPlmnRegInfoNum, (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    {
        /* ����������HPLMNע�ᱻ���б��У������䱻���� */
        NAS_MMC_ConvertHplmnRegStatusToDomainInfo(pucRejDomainRlst,
                                             &pstRegRejCtx->astPlmnRegInfoList[ulIndex]);

    }
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */
    else
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearHplmnRejDomainInfo
 ��������  : ��ĳ��Ehplmn��Hplmn��ע��ɹ�ʱ�������Ӧ��ı�����Ϣ
 �������  : pstPlmn,��Ҫ�����������Ϣ������
             ucAcceptCnDomain,��Ҫ����ķ�����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��24��
    ��    ��   : likelai
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : L00171473
    �޸�����   : V7R1 PhaseII �޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ClearHplmnRejDomainInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    VOS_UINT8                           ucAcceptCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    VOS_UINT8                           ucIdx;

    /* ��ȡHPLMNע�ᱻ�ܵ��б� */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* ��HPLMNע�ᱻ���б���δ���ҵ���ǰפ��PLMN����ֱ�ӷ��� */
    ucIdx = (VOS_UINT8)NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (ucIdx >= pstRegRejCtx->ucPlmnRegInfoNum)
    {
        return;
    }

    /* �����Ӧ��ı�����Ϣ */
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                      ucAcceptCnDomain, NAS_MML_REG_FAIL_CAUSE_NULL);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortEventType_BgPlmnSearch
 ��������  : ��ȡBG_PLMN_SEARCH״̬���������е�ABORT�¼�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ABORT�¼�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAbortEventType_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortEventType_BgPlmnSearch
 ��������  : ����BG_PLMN_SEARCH״̬���������е�ABORT�¼�����
 �������  : ulAbortEventType: ABORT��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��29��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortEventType_BgPlmnSearch(
    VOS_UINT32                          ulAbortEventType
)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType = ulAbortEventType;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortType_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������е�ABORT��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ABORT_FSM_IMMEDIATELY: �������
             NAS_MMC_ABORT_FSM_DELAY      : �ӳٴ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��21��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ABORT_FSM_TYPE_UINT8 NAS_MMC_GetAbortType_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortType_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�ABORT��־
 �������  : enAbortType: ABORT��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��21��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortType_BgPlmnSearch(
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType = enAbortType;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�ucNeedSndSysInfo��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�ucNeedSndSysInfo��־
 �������  : VOS_UINT8 ucNeedSndSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(
    VOS_UINT8                           ucNeedSndSysInfo
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo = ucNeedSndSysInfo;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRelRequestFlag_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������е��Ƿ������������ӱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE :����������
             VOS_FALSE:�����ȴ��ͷ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRelRequestFlag_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRelRequestFlag_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е��Ƿ������������ӱ�־
 �������  : ucRelRequestFlg: �Ƿ������������ӱ�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetRelRequestFlag_BgPlmnSearch(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg = ucRelRequestFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������еĵȴ�CS/PS��ע�����ı�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������еĵȴ�CS/PS��ע�����ı�־
 �������  : VOS_UINT8                           ucWaitFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucWaitFlag
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch
 ��������  : ���BG PLMN SEARCH״̬���������еĵȴ�ָ�����ע�����ı�־
 �������  : VOS_UINT8                           ucRegDomain
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucRegDomain
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch
 ��������  : ���״̬���������еĵȴ�CS/PS���ע�����ı�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������е�CSע���������ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�CSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������е�PSע���������ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�PSע���������ĺ�������
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������еĵ�ǰ���ڳ��Եĸ����ȼ��������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_WITH_RAT_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������еĵ�ǰ���ڳ��Եĸ����ȼ��������Ϣ
 �������  : NAS_MML_PLMN_ID_STRU                stPlmnId
             NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.enRat    = enRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPreCampPlmn_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������еķ���BG����ʱפ����PLMN��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : BG��֮ǰפ����VPLMN����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetPreCampPlmn_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPreCampPlmn_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������еķ���BG����ʱפ����PLMN��Ϣ
 �������  : stPlmnId -- ����BG����ʱפ����PLMN ID
             enRat    -- ����BG����ʱפ����PLMN�Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreCampPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������еķ���BG����ʱפ����PLMN���뼼����Ϣ
 �������  : enRat    -- ����BG����ʱפ����PLMN�Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��4��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������е�EquPlmn����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ����״̬����������VPLMN��EPLMN��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_EQUPLMN_INFO_STRU* NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�EQUPLMN��Ϣ
 �������  : NAS_MML_PLMN_ID_STRU                pstCurrCampPlmnId
             NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");

        return;
    }

    /* ��һ��EQUPLMN(��RPLMN)�뵱ǰפ��������ͬ, �򱣴浱ǰפ�������EQUPLMN��״̬�������� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &(pstEquPlmnInfo->astEquPlmnAddr[0])))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo = *pstEquPlmnInfo;
    }
    else
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.ucEquPlmnNum = 0x1;
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.astEquPlmnAddr[0] = *pstCurrCampPlmnId;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е�L disable��״̬
 �������  : enLteCapStatus - Lte capability״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus
)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_TRUE;
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_FALSE;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch
 ��������  : ��ȡBG PLMN SEARCH״̬���������е�L disable��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : Lte capability״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch
 ��������  : ����BG PLMN SEARCH״̬���������е��Ƿ���Ҫenbale LTE��״̬
 �������  : ucNeedEnableLteFlg   �Ƿ���Ҫenable LTE��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��5��15��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_UINT8 ucNeedEnableLteFlg)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg = ucNeedEnableLteFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch
 ��������  : �õ�BG PLMN SEARCH״̬���������е��Ƿ���Ҫenbale LTE��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : BG PLMN SEARCH״̬���������е��Ƿ���Ҫenbale LTE��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��5��15��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MML_IsLteSearched_AreaLost
 ��������  : LTE����ʱ���ж��Ƿ�������LTE
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��15��
    ��    ��   : g00322017
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MML_IsLteSearched_AreaLost(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                                              i;

    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if ((NAS_MSCC_PIF_NET_RAT_TYPE_LTE == pstSearchedPlmnListInfo[i].enRatType)
        && ((VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucPrefBandSearchedFlg)
         || (VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucSpecSearchedFlg)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetFirstStartHPlmnTimerFlg
 ��������  : �����Ƿ�Ϊ�״�����HPLMN��ʱ��
 �������  : ulFirstStartHPlmnTimer - �״λ���״�����HPLMN��ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��25��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetFirstStartHPlmnTimerFlg(
    VOS_UINT8                           ucFirstStartHPlmnTimer
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg = ucFirstStartHPlmnTimer;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFirstStartHPlmnTimerFlg
 ��������  : ��ȡ�״λ���״�����HPLMN��ʱ����־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�״�����HPLMN��ʱ��
             VOS_FALSE:���״�����HPLMN��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��25��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetFirstStartHPlmnTimerFlg(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHplmnTimerLen
 ��������  : ��ȡ��ǰHPLMN��ʱ����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��ʱ����ʱ������λ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHplmnTimerLen( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulHplmnTimerLen;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (VOS_TRUE == NAS_MMC_GetFirstStartHPlmnTimerFlg())
    {
        /* �״���������NV��en_NV_Item_HPlmnFirstTimer�ж�ȡ��Ĭ��Ϊ2���� */
        ulHplmnTimerLen = pstBgSearchCfg->ulFirstStartHplmnTimerLen;
    }
    else
    {
        ulHplmnTimerLen = NAS_MML_GetSimHplmnTimerLen();
        
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "GetHplmnTimerLen:NAS_MML_GetSimHplmnTimerLen is",ulHplmnTimerLen);
    }

    /* H3G����: VPLMN�·��״���HPLMN���ڿ���NV������ */
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        if (VOS_TRUE != NAS_MMC_GetFirstStartHPlmnTimerFlg())
        {
            /* ���״���������NV: en_NV_Item_SearchHplmnTtimerValue�л�ȡ������USIM�ļ���
               ��ȡֵ��NV: en_NV_Item_Default_Max_Hplmn_Srch_Peri��ȡ��ֵ�Ƿ���Ч */
            ulHplmnTimerLen = pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen;

            NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetHplmnTimerLen:nvim ulNonFirstHplmnTimerLen is",ulHplmnTimerLen);
        }
    }

    return ulHplmnTimerLen;
}





/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCacheNum
 ��������  : ��ȡ��ǰ���ڵĻ������
 �������  : ��
 �������  : ��ǰ���ڵĻ������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCacheNum( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetFsmStackPopFlg
 ��������  : ����״̬��ջpop��־
 �������  : ucStachPopFlg:ջpop��־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SetFsmStackPopFlg(
    VOS_UINT16                          ucStachPopFlg
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStachPopFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmStackPopFlg
 ��������  : ��ȡ״̬��ջpop��־
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  NAS_MMC_GetFsmStackPopFlg( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsFsmEntryEventType
 ��������  : �ж���Ϣ�Ƿ���״̬�������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsFsmEntryEventType(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_aulFsmEntryEventType) / sizeof(VOS_UINT32)) ; i++ )
    {
        if ( ulEventType == g_aulFsmEntryEventType[i] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetBufferedPlmnSearchFlg
 ��������  : ȡ�õ�ǰ�Ƿ��л���ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ȡ�õ�ǰ�Ƿ��л���ı�־����available timer��ʱ����ʱ���µ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��12��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : ���ĺ�����

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetBufferedPlmnSearchFlg( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetBufferedPlmnSearchFlg
 ��������  : ȡ�õ�ǰ�������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ȡ�õ�ǰ�������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : ��������

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32  NAS_MMC_GetBufferedPlmnSearchScene( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetBufferedPlmnSearchInfo
 ��������  : ���û����������Ϣ
 �������  : ulPlmnSearchFlg:   ������־
              enPlmnSearchScene: ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��12��
   ��    ��   : z40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : ���ĺ�����

*****************************************************************************/
VOS_VOID NAS_MMC_SetBufferedPlmnSearchInfo(
    VOS_UINT32                                              ulPlmnSearchFlg,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = ulPlmnSearchFlg;
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene = enPlmnSearchScene;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSrvStaChngInfo
 ��������  : ���û����������Ϣ
 �������  : ulPlmnSearchFlg:   ������־
              enPlmnSearchScene: ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��12��
   ��    ��   : z40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : ���ĺ�����

*****************************************************************************/
NAS_MMC_SRV_STA_CHNG_INFO_STRU* NAS_MMC_GetSrvStaChngInfo( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastSrvStaInfo;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastPlmnid
 ��������  : ���ö���ʱ��PLMN ID��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��02��18��
   ��    ��   : t00173447
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��09��
   ��    ��   : c00318887
   �޸�����   : ���ӽ��뼼��

*****************************************************************************/
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetLastCampedPlmnid( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.stPlmnId;
}


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastCampedPlmnRat
 ��������  : ��ȡ���פ����PLMN ���뼼��
 �������  :
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��09��
   ��    ��   : c00318887
   �޸�����   : Ԥ��Ƶ�������Ż�

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetLastCampedPlmnRat( VOS_VOID )
{
    return g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLastCampedPlmnRat
 ��������  : �������פ����PLMN ���뼼��
 �������  :
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��09��
   ��    ��   : c00318887
   �޸�����   : Ԥ��Ƶ�������Ż�

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastCampedPlmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat = enRat;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveLastCampedPlmnWithRat
 ��������  : �洢�ϴ�פ�������PLMNID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��02��25��
   ��    ��   : t00173447
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��09��
   ��    ��   : c00318887
   �޸�����   : ���ӽ��뼼��
*****************************************************************************/
/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
VOS_VOID NAS_MMC_SaveLastCampedPlmnWithRat(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_ID_STRU             *pstLastPlmnid;

    pstLastPlmnid = NAS_MMC_GetLastCampedPlmnid();

    pstLastPlmnid->ulMcc = ulMcc;
    pstLastPlmnid->ulMnc = ulMnc;

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    NAS_MMC_SetLastCampedPlmnRat(enRat);
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

    return;
}
/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */




/*****************************************************************************
 �� �� ��  : NAS_MMC_IsFsmIdInFsmStack
 ��������  : �ж�FSM ID�Ƿ���״̬��ջ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - FSM ID��״̬��ջ������
             VOS_FALSE- FSM ID����״̬��ջ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��7��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsFsmIdInFsmStack(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    for (i = 0; i < pstFsmStack->usStackDepth; i++)
    {
        if (enFsmId == pstFsmStack->astFsmStack[i].enFsmId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn
 ��������  : �û�ָ��������ǰ����ʱ���Ƿ���Ҫ����Plmn����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��������
              VOS_FALSE:������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��6��6��
   ��    ��   : l00130025
   �޸�����   : DTS2012060604313:������ע��ɹ����û�����Ը������ָ������ʱ��Ҫ��������ע��
*****************************************************************************/
VOS_UINT32 NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn(VOS_VOID)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsCurrService;


    pstSimStatus     = NAS_MML_GetSimStatus();
    enCsCurrService  = NAS_MMC_GetCsServiceStatus();
    enPsCurrService  = NAS_MMC_GetPsServiceStatus();

    /* �û�ָ����ǰפ��Plmn,CS/PSͬʱ��Ϊ��������ʱ������Ҫ�������� */
    if (( NAS_MMC_NORMAL_SERVICE == enCsCurrService)
     && ( NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* �û�ָ����ǰפ��Plmn,CS��������,PS������ע���PS����Чʱ������Ҫ�������� */
    if ((( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enCsCurrService))
    {
        return VOS_FALSE;
    }

    /* �û�ָ����ǰפ��Plmn,PS��������,CS������ע���CS����Чʱ������Ҫ�������� */
    if (( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* ��������£���Ҫ�������� */
    return VOS_TRUE;

}






/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen
 ��������  : ��ȡ�ȴ�WAS�������ظ��Ķ�ʱ��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ȴ�WAS�������ظ��Ķ�ʱ��ʱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��12��27��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:����ƽ̨���뼼���������صȴ�WAS�������ظ��Ķ�ʱ��ʱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();

    /* ���ͬʱ֧��FDD��TDD����ʱ��ʱ��Ϊ301s */
    if ( (VOS_TRUE == ulSupportFddFlg)
      && (VOS_TRUE == ulSupportTddFlg) )
    {
        return TI_NAS_MMC_WAIT_UTRAN_PLMN_SEARCH_CNF_LEN;
    }

    /* ���ֻ֧��FDD��TDD�е�һ������ʱ��ʱ��Ϊ150s */
    if (ulSupportFddFlg != ulSupportTddFlg)
    {
        return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;
    }
#endif

    return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;

}







/* Deleted by w00167002 for L-C��������Ŀ, 2014-4-16, begin */
/* Deleted by w00167002 for L-C��������Ŀ, 2014-4-16, end */




/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection
 ��������  : �����Ƿ����ҵ�񴥷�������ʶ
 �������  : ucSrvTriggerPlmnSearchFlag - ҵ�񴥷�������ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection(
    VOS_UINT8                           ucSrvTriggerPlmnSearchFlag
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag = ucSrvTriggerPlmnSearchFlag;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection
 ��������  : ��ȡ�Ƿ����ҵ�񴥷�������ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ҵ�񴥷�������ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHighPrioRatHplmnTimerLen
 ��������  : ��ȡ�����ȼ����뼼����HPLMN��ʱ����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��ʱ����ʱ������λ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulHplmnTimerLen;
    VOS_UINT32                                              ulCount;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();
    ulCount                 = NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    if (ulCount < pstHighRatHplmnTimerCfg->ulFirstSearchTimeCount)
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* ��Ҫת��Ϊ���� */
    }
    else
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* ��Ҫת��Ϊ���� */
    }

    return ulHplmnTimerLen;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHighPrioRatHplmnTimerRetryLen
 ��������  : ��ȡ�����ȼ����뼼����HPLMN��ʱ��������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��ʱ��������ʱ������λ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerRetryLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* ��Ҫת��Ϊ���� */
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main
 ��������  : ��ȡ��ǰ�����ȼ����뼼����HPLMN��ʱ���״���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�����ȼ����뼼����HPLMN��ʱ���״���������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��22��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main
 ��������  : Reset�����ȼ����뼼����HPLMN��ʱ���״���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��22��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount= 0;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main
 ��������  : ���������ȼ����뼼����HPLMN��ʱ���״���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��22��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount++;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo
 ��������  : APû��Ԥ��DPLMN��Ϣʱ����UEȫ�ֱ����е�Ehplmn���µ�DplmnNplmnCfg
             ȫ�ֱ����Լ�NV��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo(VOS_VOID)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo     = VOS_NULL_PTR;
    VOS_UINT8                                              *pucImsi              = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stHPlmn;
    VOS_UINT8                                               i,j;

    pucImsi = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHPlmn                   = NAS_MML_GetImsiHomePlmn(pucImsi);
    pstDPlmnNPlmnCfgInfo      = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstSimEhplmnInfo          = NAS_MML_GetSimEhplmnList();

    j = 0;
    pstDPlmnNPlmnCfgInfo->astEHplmnList[j++] = stHPlmn;
    pstDPlmnNPlmnCfgInfo->ucEHplmnNum = j;

    for (i = 0; i < pstSimEhplmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId),
                                                              pstDPlmnNPlmnCfgInfo->ucEHplmnNum,
                                                              pstDPlmnNPlmnCfgInfo->astEHplmnList))
        {
            continue;
        }

        pstDPlmnNPlmnCfgInfo->astEHplmnList[j++] = pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId;

        if (j >= NAS_MMC_MAX_CFG_HPLMN_NUM)
        {
            break;
        }
    }

    pstDPlmnNPlmnCfgInfo->ucEHplmnNum = j;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetDPlmnNPlmnCfgInfo
 ��������  : ��ȡNV����DPLMN NPLMN �б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : NV����DPLMN NPLMN �б�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��11��2��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU* NAS_MMC_GetDPlmnNPlmnCfgInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnCtx.stDplmnNplmnInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetDPlmnNPlmnCfgInfo
 ��������  : ��ȡ�洢DPLMN/NPLMN�����Ϣ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ָ��洢DPLMN/NPLMN�����Ϣ�������ĵ�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��02��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU* NAS_MMC_GetDPlmnNPlmnCfgCtx( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitUserDPlmnNPlmnInfo
 ��������  : ��ʼ��MMC_CTX��dplmn��nplmn��Ϣ
 �������  : pstUserDPlmnNPlmnInfo - dplmn��nplmn��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��10��21��
   ��    ��   : l00289540
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_InitUserDPlmnNPlmnInfo(
    NAS_MMC_DPLMN_NPLMN_CFG_CTX_STRU                      *pstDPlmnNPlmnCfgCtx
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo;

    VOS_UINT32                                              i;

    if (VOS_TRUE != pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg)
    {
        pstDPlmnNPlmnCfgCtx->ucDplmnSetFlg = VOS_FALSE;
    }

    pstDPlmnNPlmnCfgInfo                                    = &(pstDPlmnNPlmnCfgCtx->stDplmnNplmnInfo);
    pstDPlmnNPlmnCfgInfo->ucEHplmnNum                       = 0;
    pstDPlmnNPlmnCfgInfo->usDplmnListNum                    = 0;
    pstDPlmnNPlmnCfgInfo->usNplmnListNum                    = 0;
    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum                  = 0;

    PS_MEM_SET(pstDPlmnNPlmnCfgInfo->aucVersionId, 0x00, NAS_MCC_INFO_VERSION_LEN*sizeof(VOS_UINT8));

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_HPLMN_NUM; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astEHplmnList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_DPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_NPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRoamPlmnSelectionSortActiveFlg
 ��������  : ��ȡNV������ѡ�������Ƿ�����־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: NV��������ѡ������
             VOS_FALSE:nv����������ѡ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRoamPlmnSelectionSortActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRoamPlmnSelectionSortActiveFlg
 ��������  : ����NV������ѡ�������Ƿ�����־
 �������  : ucRoamPlmnSelectionSortFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg = ucRoamPlmnSelectionSortFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSrchUOplmnPriorToDplmnFlg
 ��������  : ������������ʱ�Ƿ�����DPLMN֮ǰ����UOPLMN�ı�־
 �������  : ucSrchUOplmnPriorToDplmnFlg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��09��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSrchUOplmnPriorToDplmnFlg(
    VOS_UINT8 ucSrchUOplmnPriorToDplmnFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucSrchUOplmnPriorToDplmnFlg = ucSrchUOplmnPriorToDplmnFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSrchUOplmnPriorToDplmnFlg
 ��������  : ��ȡ��������ʱ�Ƿ�����DPLMN֮ǰ����UOPLMN�ı�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����UOPLMN,VOS_FALSE:����DPLMN
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��09��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSrchUOplmnPriorToDplmnFlg(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucSrchUOplmnPriorToDplmnFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetGeoPlmn
 ��������  : ��ȡ״̬���������е�GeoPlmn
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_WITH_RAT_STRU:PLMN+RAT
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��22��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetGeoPlmn(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetGeoPlmn
 ��������  : ����״̬���������е�GeoPlmn
 �������  : NAS_MML_PLMN_WITH_RAT_STRU:PLMN+RAT
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��5��22��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_SetGeoPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn = *pstGeoPlmn;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg
 ��������  : ��ȡNV����history�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU:history�������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��23��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU* NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNonOosPlmnSearchFeatureSupportCfg);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNonOosSceneHistorySearchActiveFlg
 ��������  : ��ȡNV��history���Ƿ�����־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: NV����history����
             VOS_FALSE:nv������histrory����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��26��
    ��    ��   : h00281185
    �޸�����   : �޸ĳɻ؂� ucHistoryActiveFlg. ���ԭ��NV�ṹ
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNonOosSceneHistorySearchActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNonOosPlmnSearchFeatureSupportCfg.ucHistoryActiveFlg);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPrefBandSearchInfo
 ��������  : ��ȡNV�������������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU:���������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU* NAS_MMC_GetOosPlmnSearchStrategyInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo
 ��������  : ��ȡ��һ�׶�������ʱ��ʱ��Ѷ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU:��һ�׶����������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU* NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.stPhaseOnePatternCfg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo
 ��������  : ��ȡ�ڶ��׶�������ʱ��ʱ��Ѷ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU:�ڶ��׶����������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU* NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.stPhaseTwoPatternCfg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedGoToNextPhaseByHistory
 ��������  : ����History Count����OOS Phase�Ƿ������һ�׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByHistory( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurHistoryCount       = 0;
    VOS_UINT8                                               ucTotalHistoryCount     = 0;
    VOS_UINT8                                               ucTotalPrefBandCount    = 0;
    VOS_UINT8                                               ucTotalFullBandCount    = 0;

    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurHistoryCount                           = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��һ�׶� */
        ucTotalHistoryCount     = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
        ucTotalPrefBandCount    = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount    = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
         /* �ڶ��׶� */
        ucTotalHistoryCount     = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
        ucTotalPrefBandCount    = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount    = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    /* ����������һ�׶���historyΪ���ʱ���������һ�׶� */
    if((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
     &&(0 == ucTotalPrefBandCount)
     &&(0 == ucTotalFullBandCount)
     &&((ulCurHistoryCount == ucTotalHistoryCount)))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedGoToNextPhaseByPrefBand
 ��������  : ����PrefBand Count����OOS Phase�Ƿ������һ�׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByPrefBand( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurPrefBandCount;
    VOS_UINT8                                               ucTotalPrefBandCount = 0;
    VOS_UINT8                                               ucTotalFullBandCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurPrefBandCount                          = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��һ�׶� */
        ucTotalPrefBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
        /* �ڶ��׶� */
        ucTotalPrefBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
        ucTotalFullBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    /* ����������һ�׶���PrefbandΪ���ʱ���������һ�׶� */
    if((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
     &&(0 == ucTotalFullBandCount)
     && (ulCurPrefBandCount == ucTotalPrefBandCount))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedGoToNextPhaseByFullBand
 ��������  : ����PrefBand Count����OOS Phase�Ƿ������һ�׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedGoToNextPhaseByFullBand( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurFullBandCount;
    VOS_UINT8                                               ucTotalFullBandCount;


    pstPhaseOneOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();


    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��һ�׶� */
        ucTotalFullBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum;
    }
    else
    {
         /* �ڶ��׶� */
        ucTotalFullBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum;
    }

    ulCurFullBandCount          = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();

    /* ��Fullband�����趨ִ�д�����Ŀǰ��������һ�׶��������һ�׶� */
    if ((NAS_MMC_OOS_PHASE_MAX != NAS_MMC_GetOosPhaseNum())
      &&(ulCurFullBandCount == ucTotalFullBandCount))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetOosPhaseNum
 ��������  : ��ȡĿǰ��OOS�еĵڼ��׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:Ŀǰ��OOS�еĵڼ��׶�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��05��
    ��    ��   : d00305650
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_OOS_PHASE_ENUM_UINT8 NAS_MMC_GetOosPhaseNum( VOS_VOID )
{

    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ResetOosPhaseNum
 ��������  : ����OOS�׶�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��05��
    ��    ��   : d00305650
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ResetOosPhaseNum(VOS_VOID)
{

    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum = NAS_MMC_OOS_PHASE_ONE;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddOosPhaseNum
 ��������  : ���� OOS�׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��11��05��
    ��    ��   : d00305650
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_AddOosPhaseNum(VOS_VOID)
{

    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enNextOosSearchPhaseNum++;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCurrSearchPhaseNum
 ��������  : ���õ�ǰOOS�������˵ڼ��׶�
 �������  : NAS_MMC_OOS_PHASE_ENUM_UINT8    enCurrPhaseNum
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetCurrOosSearchPhaseNum(
    NAS_MMC_OOS_PHASE_ENUM_UINT8        enCurrPhaseNum
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum = enCurrPhaseNum;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrOosSearchPhaseNum
 ��������  : ��ȡĿǰ������OOS�еĵڼ��׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_OOS_PHASE_ENUM_UINT8:Ŀǰ��OOS�еĵڼ��׶�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_OOS_PHASE_ENUM_UINT8 NAS_MMC_GetCurrOosSearchPhaseNum( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOosPlmnSearchStrategyInfo.enCurrOosSearchPhaseNum);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitOosSearchStrategyInfo
 ��������  : ��ʼ��history/PrefBand/FullBand�������Ϣ
 �������  : NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU   *pstSearchTypeStrategyInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitOosSearchStrategyInfo(
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU                 *pstSearchTypeStrategyInfo
)
{
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.usSleepTimerLen    = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucHistoryNum       = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucPrefBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.ucFullBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseOnePatternCfg.usTotalTimerLen    = 0;

    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.usSleepTimerLen    = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucHistoryNum       = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucPrefBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.ucFullBandNum      = 0;
    pstSearchTypeStrategyInfo->stPhaseTwoPatternCfg.usTotalTimerLen    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPhaseOnePeriodicSleepTimerLen
 ��������  : ��ȡ��һ�׶�������ʱ��ʱ��Ѷ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulPhaseOnePeriodicSleepTimerLen: "ȫƵ��"���˯��ʱ��,
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPhaseOnePeriodicSleepTimerLen( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulPhaseOnePeriodicSleepTimerLen;

    pstPhaseOneOosPlmnSearchPatternInfo                     = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    ulPhaseOnePeriodicSleepTimerLen                         = 0;

    if (0 != pstPhaseOneOosPlmnSearchPatternInfo->ucFullBandNum)
    {
        /*
        sleep = FullBandlength = Len(H+1)(P+1)
        ex: F=1, P=0, H=2
        OOS:_H_H_F, Len => (2+1)(0+1) = 3
        ex: F=1, P=2, H=0
        OOS:_P_P_F, Len => (0+1)(2+1) = 3
        ex: F=1, P=2, H=1
        OOS:_H_P_H_P_H_F, Len => (1+1)(2+1) = 6
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum + 1) * (pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum + 1);
    }
    else if (0 != pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum)
    {
        /*
        ex: F=0, P=2, H=0
        OOS:_P          , Len => (0+1) = 1
        ex: F=0, P=2, H=1
        OOS:_H_P        , Len => (1+1) = 2
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum + 1);
    }
    else
    {
        /*
        ex: F=0, P=0, H=2
        OOS:_H, Len => Len
        */
        ulPhaseOnePeriodicSleepTimerLen =
          pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen;
    }
        /*
        ex: F=0, P=0, H=0 --> read NV ��ر�, ��� F=1, P=0, H=0
        */
    return ulPhaseOnePeriodicSleepTimerLen;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen
 ��������  : ��ȡ�ڶ��׶�������ʱ��ʱ��Ѷ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulFullBandSleepTimerLen: ȫƵ�Ѽ��˯��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen( VOS_VOID )
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulPhaseTwoPeriodicSleepTimerLen;

    pstPhaseTwoOosPlmnSearchPatternInfo                     = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulPhaseTwoPeriodicSleepTimerLen                         = 0;

    if (0 != pstPhaseTwoOosPlmnSearchPatternInfo->ucFullBandNum)
    {
        /*
        sleep = FullBandlength = Len(H+1)(P+1)
        ex: F=1, P=0, H=2
        OOS:_H_H_F, Len => (2+1)(0+1) = 3
        ex: F=1, P=2, H=0
        OOS:_P_P_F, Len => (0+1)(2+1) = 3
        ex: F=1, P=2, H=1
        OOS:_H_P_H_P_H_F, Len => (1+1)(2+1) = 6
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum + 1) * (pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum + 1);
    }
    else if (0 != pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum)
    {
        /*
        ex: F=0, P=2, H=0
        OOS:_P          , Len => (0+1) = 1
        ex: F=0, P=2, H=1
        OOS:_H_P        , Len => (1+1) = 2
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen * (pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum + 1);
    }
    else
    {
        /*
        ex: F=0, P=0, H=2
        OOS:_H, Len => Len
        */
        ulPhaseTwoPeriodicSleepTimerLen =
          pstPhaseTwoOosPlmnSearchPatternInfo->usSleepTimerLen;
    }
        /*
        ex: F=0, P=0, H=0 --> read NV ��ر�, ��� F=1, P=0, H=0
        */
    return ulPhaseTwoPeriodicSleepTimerLen;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg
 ��������  : ��ʼ��history�������Ϣ
 �������  : NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstHistoryInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��26��
    ��    ��   : h00281185
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0

*****************************************************************************/
VOS_VOID NAS_MMC_InitNonOosPlmnSearchFeatureSupportCfg(
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosPlmnSearchFeatureSupportCfg
)
{
    PS_MEM_SET(pstNonOosPlmnSearchFeatureSupportCfg, 0,
               sizeof(NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU));

    /* Ĭ�ϲ�����history������ */
    pstNonOosPlmnSearchFeatureSupportCfg->ucHistoryActiveFlg                        = VOS_FALSE;

    /* Ĭ�ϲ�����PrefBand������ */
    pstNonOosPlmnSearchFeatureSupportCfg->ucPrefBandActiveFlg                       = VOS_FALSE;

    /* Ĭ��area lost����history֮�����spec�� */
    pstNonOosPlmnSearchFeatureSupportCfg->enSearchTypeAfterHistoryInAreaLostScene   = NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_SPEC;
    return;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitCsgListSearchRatInfo_PlmnList
 ��������  : CSG LIST����״̬�����й����г�ʼ����Ҫ�����Ľ��뼼����Ϣ,Ŀǰֻ֧��lte csg
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��12��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID NAS_MMC_InitCsgListSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitCsgListSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* ����һ����ʱ���뼼���б�, ���ڵ��� */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ǰ���뼼������,��ǰ���뼼��������ǰ�� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* ��ʼ�����뼼�����ȼ��б��Լ��������,Ŀǰֻ֧��LTE CSG,gu������Ϊtrue */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;

        if (NAS_MML_NET_RAT_TYPE_LTE != stTmpPrioRatList.aucRatPrio[i])
        {
            pstSearchRatInfo[i].ucSearchedFlag  = VOS_TRUE;
        }
    }
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitGetGeoInfo
 ��������  : ��ʼ��get_geo�����Ϣ
 �������  : NAS_MMC_GET_GEO_INFO_STRU          *pstGetGeoInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitGetGeoInfo(
    NAS_MMC_GET_GEO_INFO_STRU          *pstGetGeoInfo
)
{
    /* ��ʼ��GEO PLMN */
    NAS_MMC_InitGeoPlmn();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitGeoPlmn
 ��������  : ��ʼ��GEO PLMN
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitGeoPlmn(VOS_VOID)
{

    NAS_MML_PLMN_WITH_RAT_STRU                              stGeoPlmn;

    PS_MEM_SET(&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    stGeoPlmn.enRat             = NAS_MML_NET_RAT_TYPE_BUTT;
    stGeoPlmn.stPlmnId.ulMcc    = NAS_MML_INVALID_MCC;
    stGeoPlmn.stPlmnId.ulMnc    = NAS_MML_INVALID_MNC;

    NAS_MMC_SetGeoPlmn(&stGeoPlmn);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetDisabledLtePlmnId
 ��������  : ��ȡdisable lteʱפ����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : disable lteʱפ����������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MML_PLMN_ID_STRU *NAS_MMC_GetDisabledLtePlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetDisabledLtePlmnId
 ��������  : ����disable lteʱפ����������Ϣ
 �������  : pstPlmnId - plmn��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID NAS_MMC_SetDisabledLtePlmnId(
    NAS_MML_PLMN_ID_STRU              *pstPlmnId
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = pstPlmnId->ulMcc;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = pstPlmnId->ulMnc;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearDisabledLtePlmnId
 ��������  : ���disable lteʱפ����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ClearDisabledLtePlmnId(VOS_VOID)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = NAS_MML_INVALID_MCC;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = NAS_MML_INVALID_MNC;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetEnableLteTimerExpireFlag
 ��������  : ��ȡenable lte��ʱ���Ƿ�ʱ��ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : enable lte��ʱ���Ƿ�ʱ��ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetEnableLteTimerExpireFlag( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetEnableLteTimerExpireFlag
 ��������  : ����enable lte��ʱ���Ƿ�ʱ��ʶ
 �������  : ucEnableLteTimerExpireFlag - enable lte��ʱ���Ƿ�ʱ��ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_VOID NAS_MMC_SetEnableLteTimerExpireFlag(
    VOS_UINT8                           ucEnableLteTimerExpireFlag
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag = ucEnableLteTimerExpireFlag;
    return;
}



/* Added by s00246516 for L-C��������Ŀ, 2014-02-13, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRegCtrl
 ��������  : ��ȡע�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_REG_CONTROL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��14��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_REG_CONTROL_ENUM_UINT8 NAS_MMC_GetRegCtrl( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRegCtrl
 ��������  : ����ע�������Ϣ
 �������  : NAS_MMC_REG_CONTROL_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��14��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetRegCtrl(
    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl) = enRegCtrl;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAsAnyCampOn
 ��������  : ��ȡ������Ƿ�Any cellפ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��14��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAsAnyCampOn( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAsAnyCampOn
 ��������  : ���ý�����Ƿ�Any cellפ��
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��14��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAsAnyCampOn(
    VOS_UINT8                          ucAsAnyCampOn
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn) = ucAsAnyCampOn;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveRegReqNCellInfo
 ��������  : ����MSCC REG REQ������Ϣ�е�CellInfo��Ϣ��NCELLȫ�ֱ�����
 �������  : pstCellInfo:��Ҫ�����CellInfo��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SaveRegReqNCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    /* Ŀǰ��֧��ע��������Я��LTE��NCell��Ϣ */
    if (NAS_MML_NET_RAT_TYPE_LTE != pstCellInfo->ucRat)
    {
        return;
    }

    /* ����NCELL��Ϣ */
    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteArfcnNum       = 1;
    pstMmcNcellSearchInfo->stLteNcellInfo.aulLteArfcnList[0]  = pstCellInfo->ulArfcn;

    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum        = NAS_MML_MIN(pstCellInfo->ucCellNum, NAS_MMC_LTE_CELL_MAX_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stLteNcellInfo.ausLteCellList, pstCellInfo->ausCellId,
               ((pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum) * sizeof(VOS_UINT16)));

    pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum = NAS_MML_MIN(pstCellInfo->ucPlmnNum, NAS_MML_MAX_EQUPLMN_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr, pstCellInfo->astPlmnId,
               ((pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum) * sizeof(NAS_MML_PLMN_ID_STRU)));

    return;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-02-13, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPrefPlmnPara
 ��������  : ���ڴ�MMC�л�ȡMMC��ȫ�ֱ�����Ϣ
 �������  : MMC_MMA_SHARE_PARA_ST *pMmcPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32  VOS_FALSE:��ʾʧ�ܣ�VOS_TRUE:��ʾ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    /* ������Ч���ж� */
    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* ָ��Ϊ��ָ�룬���ش��� */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:NULL PTR ");
        return VOS_FALSE;
    }

    if (pstMmcPara->enMmaParaType >= EN_MMC_BEGIN_SET_MMC_PARA)
    {
        /* ���Ͳ�������,���ش���ֵ */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(&(pstMmcPara->u.stOPlmnInfo));
            break;

        case EN_MMC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        case EN_MMC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(&(pstMmcPara->u.stHPlmnInfo));
            break;


        /* PLMNSEL �� UPLMN ֻ���ܳ���һ�����ʶ����� stUPlmnInfo �� */
        case EN_MMC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        default:
            /* ��ӡ������Ϣ,���س����־ */
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPrefPlmnPara
 ��������  : ��������MMC��ȫ�ֱ�����Ϣ
 �������  : MMC_MMA_SHARE_PARA_ST *pMmcPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32  VOS_FALSE:��ʾʧ�ܣ�VOS_TRUE:��ʾ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_SetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    VOS_UINT32                          ulI = 0;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmn  = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmn = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* ָ��Ϊ��ָ�룬���ش��� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:Set Para Point is NULL");
        return VOS_FALSE;
    }

    pstUserPlmn = NAS_MML_GetSimUserPlmnList();
    pstSelPlmn  = NAS_MML_GetSimSelPlmnList();

    if ((pstMmcPara->enMmaParaType < EN_MMC_BEGIN_SET_MMC_PARA)
      || (pstMmcPara->enMmaParaType > EN_MMC_END_SET_MMC_PARA))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_SET_UPLMN_INFO:
             pstUserPlmn->ucUserPlmnNum      = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
             for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
             {
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
                 pstUserPlmn->astUserPlmnInfo[ulI].usSimRat       = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].usRaMode;
             }

             break;

        case  EN_MMC_SET_PLMNSEL_INFO:
            pstSelPlmn->ucSelPlmnNum    = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
            for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
            {
                pstSelPlmn->astPlmnId[ulI].ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                pstSelPlmn->astPlmnId[ulI].ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
            }

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;

    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnInfo
 ��������  : ��MMC�л�ȡMMC��ȫ�ֱ�����Ϣ
 �������  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
            NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPlmnInfo(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
)
{
    VOS_UINT32                          ulLoop;
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccSelPlmnList = VOS_NULL_PTR;

    pstRptMsccSelPlmnList = (MMC_TAF_PLMN_LIST_INFO_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(MMC_TAF_PLMN_LIST_INFO_ST));
    if (VOS_NULL_PTR == pstRptMsccSelPlmnList)
    {
        return VOS_FALSE;
    }

    switch (enPrefPlmnParaType)
    {
        case NAS_MSCC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        /* PLMNSEL �� UPLMN ֻ���ܳ���һ�����ʶ����� stUPlmnInfo �� */
        case NAS_MSCC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        default:
            /* ��ӡ������Ϣ,���س����־ */
            PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnInfo:WARNING:PARA TYPE WRONG IN DEFAULT ");
            return VOS_FALSE;
    }

    pstPlmnInfo->usPlmnNum = pstRptMsccSelPlmnList->usCurPlmnNum;
    for ( ulLoop = 0; ulLoop < pstRptMsccSelPlmnList->usCurPlmnNum ; ulLoop++ )
    {
        pstPlmnInfo->Plmn[ulLoop].ulMcc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMcc;
        pstPlmnInfo->Plmn[ulLoop].ulMnc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMnc;
        NAS_MMC_PlmnId2Bcd(&(pstPlmnInfo->Plmn[ulLoop]));
        pstPlmnInfo->ausPlmnRat[ulLoop] = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].usRaMode;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecificPlmnTblSize
 ��������  : ��ȡplmn tbl size
 �������  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8            enPrefPLMNType
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetSpecificPlmnTblSize(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                                              usCurPlmnNum;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU                   *pstHplmnWithRat = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnInfo  = VOS_NULL_PTR;

    usCurPlmnNum = 0;
    switch(enPrefPLMNType)
    {
        case NAS_MSCC_UPLMN_INFO:
            pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
            usCurPlmnNum    = pstUserPlmnList->ucUserPlmnNum;
            break;
        case NAS_MSCC_PLMNSEL_INFO:
            pstSelPlmnInfo  = NAS_MML_GetSimSelPlmnList();
            usCurPlmnNum    = pstSelPlmnInfo->ucSelPlmnNum;
            break;
        case NAS_MSCC_OPLMN_INFO:
            pstOperPlmnList = NAS_MML_GetSimOperPlmnList();
            usCurPlmnNum    = pstOperPlmnList->usOperPlmnNum;
            break;
        case NAS_MSCC_HPLMN_INFO:
            pstHplmnWithRat = NAS_MML_GetSimHplmnWithRatList();
            usCurPlmnNum    = pstHplmnWithRat->ucHPlmnWithRatNum;
            break;
        default:
            break;
    }

    return usCurPlmnNum;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnInfo
 ��������  : ����pref plmn
 �������  : VOS_UINT16                          usEfId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnInfo(
    VOS_UINT16                          usEfId
)
{
    MMC_MMA_SHARE_PARA_ST              *pstMsccPara;
    VOS_UINT16                          usIndex;
    MMC_MODIFY_PLMN_INFO_STRU          *pstPrefPlmnCtx;

    pstMsccPara = (MMC_MMA_SHARE_PARA_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                            sizeof(MMC_MMA_SHARE_PARA_ST));

    if (VOS_NULL_PTR == pstMsccPara)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_UpdatePlmnInfo: Alloc memory fail.");
        return ;
    }

    if (USIMM_GSM_EFPLMNSEL_ID == usEfId ) /* EFPLMNsel */
    {
        pstMsccPara->enMmaParaType = EN_MMC_PLMNSEL_INFO;
    }
    else if ((USIMM_USIM_EFPLMNWACT_ID == usEfId) /* EFPLMNwAcT */
         || ((USIMM_GSM_EFPLMNWACT_ID  == usEfId)))
    {
        pstMsccPara->enMmaParaType = EN_MMC_UPLMN_INFO;
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->enMmaParaType = EN_MMC_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = EN_MMC_HPLMN_INFO;
    }

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();

    usIndex = pstPrefPlmnCtx->usIndex;

    if (usIndex >= NAS_MML_MAX_USERPLMN_NUM)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);
        return ;
    }

    (VOS_VOID)NAS_MMC_GetPrefPlmnPara(pstMsccPara);

    if ( (USIMM_GSM_EFPLMNSEL_ID   == usEfId ) /* EFPLMNsel */
      || (USIMM_USIM_EFPLMNWACT_ID == usEfId)
      || (USIMM_GSM_EFPLMNWACT_ID  == usEfId)) /* EFPLMNwAcT */
    {
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

        /* UPLMN��Ҫ���и��� */
        NAS_MMC_SndMmcUpdateUplmnNotify();
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

    }
    else
    {
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;
    }


    if (EN_MMC_UPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_UPLMN_INFO;
    }
    else if (EN_MMC_PLMNSEL_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_PLMNSEL_INFO;
    }
    else if (EN_MMC_OPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = MMC_MMA_PARA_TYPE_BUTT;
    }

    (VOS_VOID)NAS_MMC_SetPrefPlmnPara(pstMsccPara);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_QryPrefPlmnId
 ��������  : ��ѯpref plmn
 �������  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8   enPrefPLMNType,
             VOS_UINT32                          ulFromIndex,
             VOS_UINT32                          ulPlmnNum,
             NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU  *pstPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_QryPrefPlmnId(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8       enPrefPLMNType,
    VOS_UINT32                              ulFromIndex,
    VOS_UINT32                              ulPlmnNum,
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU      *pstPlmnInfo
)
{
    VOS_UINT32                                              i;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstOrgPlmnInfo;

    pstOrgPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOrgPlmnInfo)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pstOrgPlmnInfo, 0x00, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    /* ��ȡ���������б� */
    if (VOS_TRUE != NAS_MMC_GetPlmnInfo(enPrefPLMNType, pstOrgPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

        return VOS_FALSE;
    }

    pstPlmnInfo->ulPlmnNum = pstOrgPlmnInfo->usPlmnNum;

    for (i = 0; i < ulPlmnNum; i++ )
    {
        pstPlmnInfo->ausPlmnRat[i]                         = pstOrgPlmnInfo->ausPlmnRat[(i + ulFromIndex)];
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMcc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMcc;
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMnc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMnc;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPrefPlmnCtx
 ��������  : ��ʼ������pref plmn��������������
 �������  : MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��15��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitPrefPlmnCtx(
    MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
)
{
    pstPreflmnInfo->stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    pstPreflmnInfo->stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstPreflmnInfo->usIndex         = 0;
    pstPreflmnInfo->PlmnRat         = NAS_MMC_RAT_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPrefPlmnCtx
 ��������  : ��ʼ������pref plmn��������������
 �������  : ��
 �������  : prefPlmn nas_mmc_ctx�����ĵ�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��15��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
MMC_MODIFY_PLMN_INFO_STRU* NAS_MMC_GetPrefPlmnCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPreflmnInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitDetachReqCtx
 ��������  : ��ʼ������detach request����������
 �������  : NAS_MMC_DETACH_REQ_CTX_STRU          *pstDetachReqCtx
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitDetachReqCtx(
    NAS_MMC_DETACH_REQ_CTX_STRU        *pstDetachReqCtx
)
{
    pstDetachReqCtx->enDetachReason = NAS_MSCC_PIF_DETACH_REASON_BUTT;

    pstDetachReqCtx->enDetachType   = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetDetachReqCtxAddr
 ��������  : ��ȡdetach���������ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_DETACH_REQ_CTX_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_DETACH_REQ_CTX_STRU *NAS_MMC_GetDetachReqCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stDetachReqCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitAttachReqCtx
 ��������  : ��ʼ������attach request����������
 �������  : NAS_MMC_DETACH_REQ_CTX_STRU          *pstDetachReqCtx
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitAttachReqCtx(
    NAS_MMC_ATTACH_REQ_CTX_STRU        *pstAttachReqCtx
)
{
    pstAttachReqCtx->ulOpID = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAttachReqOpId
 ��������  : ��ȡattach���������ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAttachReqOpId(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAttachReqOpId
 ��������  : ����attach����OpId
 �������  : ulOpId -- ����ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��17��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAttachReqOpId(VOS_UINT32 ulOpId)
{
    NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID = ulOpId;
}

/*lint -restore */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmCtxAddr_GetGeo
 ��������  : ��ȡGetGeo״̬���������ĵ�ָ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_FSM_GET_GEO_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_FSM_GET_GEO_CTX_STRU* NAS_MMC_GetFsmCtxAddr_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetGeoRatInfoList_GetGeo
 ��������  : ��ȡGetGeo״̬���Ľ��뼼�����ȼ��б������ĵ�ָ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��06��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU* NAS_MMC_GetGeoRatInfoList_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetGeoRatListInfo_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.stGetGeoRatInfoList);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAbortFlag_GetGeo
 ��������  : ��ȡGetGeo״̬���������е�ABORT��ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetAbortFlag_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAbortFlag_GetGeo
 ��������  : ����GET GEO״̬���������е�ABORT��ʶ
 �������  : VOS_UINT8    ulAbortFlag     ABORT��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetAbortFlag_GetGeo(
    VOS_UINT8                           ucAbortFlag
)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag = ucAbortFlag;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNotifyMsccFlag_GetGeo
 ��������  : ��ȡGetGeo״̬���������е�֪ͨMSCC����ı��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��08��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetNotifyMsccFlag_GetGeo
 ��������  : ����GET GEO״̬���������е�֪ͨMSCC����ı��
 �������  : VOS_UINT8    ucNotifyMsccFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��08��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetNotifyMsccFlag_GetGeo(
    VOS_UINT8                           ucNotifyMsccFlg
)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg = ucNotifyMsccFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetTaskPhase_GetGeo
 ��������  : ��ȡGetGeo״̬��������׶�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��06��03��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8 NAS_MMC_GetFsmTaskPhase_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetTaskPhase_GetGeo
 ��������  : ����GetGeo״̬��������׶�
 �������  : NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��06��03��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetFsmTaskPhase_GetGeo(
    NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8     enGetGeoTaskPhase
)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase = enGetGeoTaskPhase;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection
 ��������  : ��ȡ��ǰMMC�����ȫ�ֱ����еĵ�NO RF�µ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : l00305157
    �޸�����   : �����ɺ��� ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection(VOS_VOID)
{
    return g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNoRfPlmnSearchScene_PlmnSelection
 ��������  : ���õ�ǰ��MMC��ȫ�ֱ����б����NO RF�µ���������
 �������  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32:���õ�ǰ��MMC��ȫ�ֱ����б����NO RF�µ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : l00305157
    �޸�����   : �����ɺ��� ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32             enPlmnSearchScene
)
{
    g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene = enPlmnSearchScene;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection
 ��������  : ��ȡ��ǰMMC�����ȫ�ֱ����еĵ�NO RF�µ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : l00305157
    �޸�����   : �����ɺ��� ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU* NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.astHistorySearchRatInfo[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BackupNoRfSearchInfo_PlmnSelection
 ��������  : ��ȡ�����б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_RAT_SEARCH_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
NAS_MMC_RAT_SEARCH_INFO_STRU* NAS_MMC_GetSearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BackupNoRfSearchInfo_PlmnSelection
 ��������  : NO RF�����,����HISTORY���������Լ������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;


    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����HISTORY�������� */
    pstSearchRatInfo                    = NAS_MMC_GetSearchRatInfo_PlmnSelection();
    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    PS_MEM_SET(pstHsirotySearchRatInfo, 0, sizeof(NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstHsirotySearchRatInfo[i].enRatType                = pstSearchRatInfo[i].enRatType;
        pstHsirotySearchRatInfo[i].ucHistorySearchedFlag    = pstSearchRatInfo[i].ucHistorySearchedFlag;
    }

    /* ������������ */
    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(enPlmnSearchScene);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection
 ��������  : NO RF�����,��ȡ����HISTORY�����б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_RAT_SEARCH_INFO_STRU*  astSearchRatInfo
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection(
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo

)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;

    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    /* �ָ�HISTORY�������� */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType             = pstHsirotySearchRatInfo[i].enRatType;
        pstSearchRatInfo[i].ucHistorySearchedFlag = pstHsirotySearchRatInfo[i].ucHistorySearchedFlag;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitNoRFBackUpSearchedInfoCtx
 ��������  : NO RF�����,��ʼ�����ݵ�HISTORY�����б�/��������
 �������  : NAS_MMC_NO_RF_BACK_UP_SEARCH_INFO_STRU*         pstNoRFBackSearchInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_InitNoRFBackUpSearchedInfoCtx(
    NAS_MMC_BACK_UP_SEARCH_INFO_STRU*         pstBackSearchInfo
)
{
    VOS_UINT32                                              i;

    pstBackSearchInfo->stNoRFBackUpSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].enRatType                        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].ucHistorySearchedFlag            = VOS_FALSE;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[0]                   = 0;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[1]                   = 0;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCampPosition
 ��������  : ��õ�ǰλ��
 �������  : NAS_MSCC_PIF_CAMP_POSITION*         pstCampPosition
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : g00322017
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_GetCampPosition(
    NAS_MSCC_PIF_CAMP_POSITION_STRU    *pstCampPosition
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;

    pstCampPlmnInfo               = NAS_MML_GetCurrCampPlmnInfo();

    pstCampPosition->stPlmnId     = pstCampPlmnInfo->stLai.stPlmnId;
    pstCampPosition->ulCellId     = pstCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId;
    pstCampPosition->usLac        = (pstCampPlmnInfo->stLai.aucLac[0] << 8) | (pstCampPlmnInfo->stLai.aucLac[1]);
    pstCampPosition->ucRac        = pstCampPlmnInfo->ucRac;
    pstCampPosition->enNetRatType = NAS_MML_GetCurrNetRatType();

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLmmAttachReqSendRslt_PlmnSelection
 ��������  : ��ȡLMM������Attachע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ȫ�ֱ���g_stNasMmcCtx�е�Attachע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

*****************************************************************************/
MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8 NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection( VOS_VOID )
{
    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLmmAttachReqSendRslt_PlmnSelection
 ��������  : ����LMM������Attachע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus = enLmmAttachClRegStatus;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCountryCode_PlmnSelection
 ��������  : ��ȡ��ǰפ��С���Ĺ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��2��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCountryCode_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                          ulCurrCampPlmnMcc;
    VOS_UINT32                          ulLastCampedPlmnMcc;

    ulCurrCampPlmnMcc   = NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc;
    ulLastCampedPlmnMcc = NAS_MMC_GetLastCampedPlmnid()->ulMcc;

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_GetCountryCode_PlmnSelection: ulCurrCampPlmnMcc, ulLastCampedPlmnMcc",
        ulCurrCampPlmnMcc, 
        ulLastCampedPlmnMcc);

    if (NAS_MML_INVALID_MCC != ulCurrCampPlmnMcc)
    {
        /* ��ǰפ��С��������Ϊ��Чֵ��ֱ�ӷ��� */
        return ulCurrCampPlmnMcc;
    }

    /* ��ǰפ��С����Ϣ�ѱ������ȡ��һ�γɹ�פ��С����MCC */
    return ulLastCampedPlmnMcc;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCLAssociatedInfoAddr
 ��������  : ȡ��mmc�������е�CLAssociatedInfoNtf
 �������  : ��
 �������  : ��
 �� �� ֵ  : stCLAssociatedInfoNtf�ĵ�ַ

 �޸���ʷ      :
  1.��    ��   : 2015��9��11��
    ��    ��   : y00346957
    �޸�����   : add for DTS2015070910885

*****************************************************************************/
NAS_MMC_CL_ASSOCIATED_INFO_NTF_STRU* NAS_MMC_GetCLAssociatedInfoAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stPlmnSearchCtrl.stCLAssociatedInfoNtf);
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MML_GetLastAreaLostPlmnCnt
 ��������  : ��ȡ�ϴε���PLMN�ĵ�������
 �������  : NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU *
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MML_GetLastAreaLostPlmnCnt(
    NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU *pstLastAreaLostPlmnInfoAddr
)
{
    return pstLastAreaLostPlmnInfoAddr->ucSearchCnt;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateLastAreaLostPlmnWIthRatAndCnt
 ��������  : �����ϴε�����PLMNID ��Ϣ�ʹ���
 �������  : NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU* ״̬���������б����ϴ�פ�������PLMNID��ַ
             NAS_MML_PLMN_ID_STRU* ��ǰPLMNID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2016��03��16��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateLastAreaLostPlmnWIthRatAndCnt(
    NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU *pstLastAreaLostPlmn,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat

)
{
    if ( (pstLastAreaLostPlmn->stPlmnId.ulMcc == pstPlmnId->ulMcc)
      && (pstLastAreaLostPlmn->stPlmnId.ulMnc == pstPlmnId->ulMnc)
      && (enRat == pstLastAreaLostPlmn->enRat) )
    {
        pstLastAreaLostPlmn->ucSearchCnt++;
    }
    else
    {
        pstLastAreaLostPlmn->stPlmnId.ulMcc = pstPlmnId->ulMcc;
        pstLastAreaLostPlmn->stPlmnId.ulMnc = pstPlmnId->ulMnc;
        pstLastAreaLostPlmn->enRat          = enRat;

        pstLastAreaLostPlmn->ucSearchCnt    = NAS_MMC_NUM_ONE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsGuRrcSearchedAreaLostPlmn
 ��������  : �ж�GU������ڵ���ʱ�Ƿ��ѹ���ǰPLMN����
 �������  : RRMM_AREA_LOST_IND_STRU*
 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2016��03��16��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsGuRrcSearchedAreaLostPlmn(
    RRMM_AREA_LOST_IND_STRU            *pstAreaLostMsg
)
{
    if ( (VOS_TRUE == pstAreaLostMsg->stSearchedType.ucHistorySearchedFlg)
      || (VOS_TRUE == pstAreaLostMsg->stSearchedType.ucPrefBandSearchedFlg)
      || (VOS_TRUE == pstAreaLostMsg->stSearchedType.ucSpecSearchedFlg) )
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsLmmSearchedAreaLostPlmn
 ��������  : �ж�LTE������ڵ���ʱ�Ƿ��ѹ���ǰPLMN����
 �������  : LMM_MMC_AREA_LOST_IND_STRU*
 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2016��03��16��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLmmSearchedAreaLostPlmn(
    LMM_MMC_AREA_LOST_IND_STRU            *pstLmmAreaLostMsg
)
{
    if ( (VOS_TRUE == pstLmmAreaLostMsg->stSearchedType.ucHistorySearchedFlg)
      || (VOS_TRUE == pstLmmAreaLostMsg->stSearchedType.ucPrefBandSearchedFlg)
      || (VOS_TRUE == pstLmmAreaLostMsg->stSearchedType.ucSpecSearchedFlg) )
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastAreaLostPLmnInfoCtx_PlmnSelection
 ��������  : ��ȡ��״̬���б����ϴε���PLMN�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��03��16��
    ��    ��  : j00174725
    �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU* NAS_MMC_GetLastAreaLostPLmnInfoCtx_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������ PLMN SELECTION, �쳣��ӡ  */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastAreaLostPLmnInfoCtx_PlmnSelection,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection()->stLastAreaLostPlmnInfo);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastAreaLostPLmnInfoCtx_BgPlmnSearch
 ��������  : ��ȡ������״̬���������б����ϴε���PLMN��Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��03��16��
    ��    ��  : j00174725
    �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU* NAS_MMC_GetLastAreaLostPLmnInfoCtx_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastAreaLostPLmnInfoCtx_BgPlmnSearch,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stLastAreaLostPlmnInfo);
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


