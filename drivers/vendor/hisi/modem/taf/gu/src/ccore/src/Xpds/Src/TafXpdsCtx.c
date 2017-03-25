/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXpdsCtx.c
  �� �� ��   : ����
  ��    ��   : �ȴ���
  ��������   : 2015��7��14��
  ����޸�   :
  ��������   : XPDS Cagps Ctx Info
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��14��
    ��    ��   : g00261581
    �޸�����   : CDMA-AGPS��Ŀ����

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID            PS_FILE_ID_TAF_XPDS_CTX_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafLog.h"
#include "TafXpdsMntn.h"
#include "TafXpdsCtx.h"
#include "TafXpdsFsmMainTbl.h"
#include "cprocstime.h"
#include "TafXpdsFsmUpLinkCtrlTbl.h"
#include "TafXpdsFsmCpLinkCtrlTbl.h"
#include "TafXpdsFsmMpcProcTbl.h"
#include "TafXpdsFsmPdeProcTbl.h"
#include "TafXpdsFsmCpPdeProcTbl.h"
#include "TafXpdsCommFunc.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
/*****************************************************************************
  2 Global variable
*****************************************************************************/
TAF_XPDS_CONTEXT_STRU            g_stTafXpdsCtx;

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitCurrFsmCtx
 ��������  : ��ʼ����ǰ״̬��������
 �������  : TAF_XPDS_FSM_CTX_STRU             *pstCurrFsmCtx
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitCurrFsmCtx(
    TAF_XPDS_FSM_CTX_STRU             *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   TAF_XPDS_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   TAF_XPDS_GetMainFsmDescAddr();
    pstCurrFsmCtx->enParentFsmId            =   TAF_XPDS_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;
    pstCurrFsmCtx->ulState                  =   TAF_XPDS_L1_STA_INIT;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               TAF_XPDS_MAX_MSG_BUFFER_LEN);

    /* unFsmCtx���ε������漰 */
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitFsmStackCtx
 ��������  : ��ʼ��״̬��ջ������
 �������  : TAF_XPDS_FSM_STACK_STRU           *pstFsmStack
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitFsmStackCtx(
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < TAF_XPDS_MAX_FSM_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = TAF_XPDS_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = TAF_XPDS_L1_STA_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitPosCtx
 ��������  : ��ʼ����λ���ȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitPosCtx(VOS_VOID)
{
    TAF_XPDS_InitDefaultCfgInfo();

    PS_MEM_SET(TAF_XPDS_GetCtrlInfoAddr(), 0, sizeof(TAF_XPDS_CTRL_INFO_STRU));

    PS_MEM_SET(TAF_XPDS_GetPublicDataAddr(), 0, sizeof(TAF_XPDS_PUBLIC_DATA_STRU));

    TAF_XPDS_InitPdePublicDataPdeInit();

    PS_MEM_SET(TAF_XPDS_GetMpcCtxAddr(), 0, sizeof(TAF_XPDS_MPC_CTX_STRU));

    PS_MEM_SET(TAF_XPDS_GetUpLinkCtxAddr(), 0, sizeof(TAF_XPDS_CAGPS_UPLINK_CTX_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitCtx
 ��������  : ��ʼ��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitCtx(VOS_VOID)
{
    TAF_XPDS_CONTEXT_STRU              *pstXpdsCtx = VOS_NULL_PTR;

    pstXpdsCtx = TAF_XPDS_GetCtxAddr();

    /* ��ʼ��XPDS��ʱ�������� */
    TAF_XPDS_InitAllTimers(pstXpdsCtx->astTimerCtx);

    /* ��ʼ��XPDS��ǰ״̬�������� */
    TAF_XPDS_InitCurrFsmCtx(&(pstXpdsCtx->stCurFsm));

    /* ��ʼ��XPDS״̬��ջ������ */
    TAF_XPDS_InitFsmStackCtx(&(pstXpdsCtx->stFsmStack));

    TAF_XPDS_InitInternalBuffer(&(pstXpdsCtx->stIntMsgQueue));

    TAF_XPDS_InitPdePublicDataTaskInit();

    TAF_XPDS_InitPosCtx();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitFsmCtx_L1Main
 ��������  : ��ʼ��L1״̬��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitFsmCtx_L1Main(VOS_VOID)
{
    /* ���ε������漰 */

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_LoadSubFsm
 ��������  : ����L2״̬������Ϣ
 �������  : TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId
             TAF_XPDS_FSM_CTX_STRU              *pstCurFsm
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_XPDS_LoadSubFsm(
    TAF_XPDS_FSM_ID_ENUM_UINT32         enFsmId,
    TAF_XPDS_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case TAF_XPDS_FSM_LINK_CTRL:
            pstCurFsm->ulState          = TAF_XPDS_UP_LINK_CTRL_SUBSTA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetFsmUpLinkFsmDescAddr();
            break;

        case TAF_XPDS_FSM_CP_LINK_CTRL:
            pstCurFsm->ulState          = TAF_XPDS_CP_LINK_CTRL_SUBSTA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetFsmCpLinkFsmDescAddr();
            break;

        case TAF_XPDS_FSM_MPC_PROC:
            pstCurFsm->ulState          = TAF_XPDS_L2_MPC_PROC_STA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetL2MpcProcFsmDescAddr();
            break;

        case TAF_XPDS_FSM_PDE_PROC:
            pstCurFsm->ulState          = TAF_XPDS_L2_PDE_PROC_STA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetL2PdeProcFsmDescAddr();
            break;

        case TAF_XPDS_FSM_CP_PDE_PROC:
            pstCurFsm->ulState          = TAF_XPDS_CP_L2_PDE_PROC_STA_INIT;
            pstCurFsm->pstFsmDesc       = TAF_XPDS_GetCpL2PdeProcFsmDescAddr();
            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*ִ�г�ʼ��L2״̬���ĺ���*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_PushFsm
 ��������  : ��״̬������ѹջ
 �������  : pstFsmStack -- ״̬��ջ
             pstNewFsm   -- ��Ҫѹ���״̬��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_PushFsm(
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack,
    TAF_XPDS_FSM_CTX_STRU             *pstNewFsm
)
{
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;

    /* ���ָ���� */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        XPDS_ERROR_LOG("TAF_XPDS_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* ջ��ȼ�� */
    if (pstFsmStack->usStackDepth >= TAF_XPDS_MAX_FSM_STACK_DEPTH)
    {
        XPDS_ERROR1_LOG("TAF_XPDS_PushFsm: Fsm Stack Depth = %d Error!",
                        pstFsmStack->usStackDepth);

        return;
    }

    /* push��ǰ״̬����������ջ */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(TAF_XPDS_FSM_CTX_STRU));

    /* ջ������� */
    pstFsmStack->usStackDepth++;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_PopFsm
 ��������  : ��״̬�����г�ջ
 �������  : ��
             ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_PopFsm(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack = TAF_XPDS_GetFsmStackAddr();
    pstCurFsm   = TAF_XPDS_GetCurFsmAddr();

    /* ���ջ�ռ��Ƿ�Ϊ�� */
    if (0 == pstFsmStack->usStackDepth)
    {
        XPDS_ERROR_LOG("TAF_XPDS_PopFsm: FSM Stack is empty");

        return;
    }

    /* ״̬��ջ��ȼ��� */
    pstFsmStack->usStackDepth--;

    /* ���õ�ǰ״̬�� */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(TAF_XPDS_FSM_CTX_STRU));
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitFsmL2
 ��������  : XPDS����һ��L2��״̬�����������̵�ͬʱ����״̬�Լ�������ʱ��
             �ú��������ѹջ����,�������Ҫ����ѹջ, ���뱣֤�˳�ǰ����
 �������  : TAF_XPDS_FSM_ID_ENUM_UINT32        enFsmId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitFsmL2(
    TAF_XPDS_FSM_ID_ENUM_UINT32        enFsmId
)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;
    TAF_XPDS_FSM_ID_ENUM_UINT32        enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    /* ��ӡѹջǰ��״̬����״̬ID */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());

    /* ��¼ѹջǰ��״̬�����������Ϣ���� */
    enParentFsmId     = TAF_XPDS_GetCurrFsmId();
    ulParentEventType = TAF_XPDS_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* ����ǰ״̬��ѹջ���� */
    pstFsmStack = TAF_XPDS_GetFsmStackAddr();
    pstCurFsm   = TAF_XPDS_GetCurFsmAddr();
    TAF_XPDS_PushFsm(pstFsmStack, pstCurFsm);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId = enFsmId;

    /* ����L2״̬�� */
    TAF_XPDS_LoadSubFsm(enFsmId, pstCurFsm);

    /* ��¼�ϲ�״̬�����������Ϣ���� */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    /* ��ӡѹջǰ��״̬����״̬ID */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_QuitFsmL2
 ��������  : ����L2״̬��������������̣�״̬������״̬ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_QuitFsmL2(VOS_VOID)
{
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm = TAF_XPDS_GetCurFsmAddr();

    /* QUITʱ��յ�ǰL2״̬����CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  ��ӡѹջǰ��L1��L2״̬ */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());

    /* ״̬����ջ���� */
    TAF_XPDS_PopFsm();

    /*  ��ӡ��ǰ��L1��L2״̬ */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), TAF_XPDS_GetFsmTopState());

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCtxAddr
 ��������  : ��ȡ�����ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_CONTEXT_STRU* TAF_XPDS_GetCtxAddr(VOS_VOID)
{
    return  &g_stTafXpdsCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCurFsmAddr
 ��������  : ��ȡ��ǰ״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_FSM_CTX_STRU* TAF_XPDS_GetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stCurFsm);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetFsmStackAddr
 ��������  : ��ȡ��ǰ״̬��ջ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬��ջ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_FSM_STACK_STRU* TAF_XPDS_GetFsmStackAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stFsmStack);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCurFsmDesc
 ��������  : ��ȡ��ǰ״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_FSM_DESC_STRU* TAF_XPDS_GetCurFsmDesc(VOS_VOID)
{
    return (TAF_XPDS_GetCtxAddr()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCurrFsmEntryMsgAddr
 ��������  : ��ȡ��ǰ״̬�������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_MSG_STRU* TAF_XPDS_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCurrFsmId
 ��������  : ��ȡ��ǰ״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_FSM_ID_ENUM_UINT32 TAF_XPDS_GetCurrFsmId(VOS_VOID)
{
    return (TAF_XPDS_GetCtxAddr()->stCurFsm.enFsmId);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetFsmTopState
 ��������  : ��ȡ״̬�������״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetFsmTopState(VOS_VOID)
{
    return (TAF_XPDS_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetFsmStackDepth
 ��������  : ��ȡ��ǰЭ��ջ��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  TAF_XPDS_GetFsmStackDepth(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetCurrFsmState
 ��������  : ���õ�ǰ״̬��״̬
 �������  : VOS_UINT32                          ulCurrState
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    TAF_XPDS_FSM_CTX_STRU             *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = TAF_XPDS_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /*  ��ӡ��ǰ��L1��L2״̬ */
    TAF_XPDS_MNTN_LogFsmInfo(UEPS_PID_XPDS, TAF_XPDS_GetCurrFsmId(), ulCurrState);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetFsmStackPopFlg
 ��������  : ����״̬��ջpop��־
 �������  : ucStackPopFlg:ջpop��־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_XPDS_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetFsmStackPopFlg
 ��������  : ��ȡ״̬��ջpop��־
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  TAF_XPDS_GetFsmStackPopFlg(VOS_VOID)
{
    TAF_XPDS_FSM_STACK_STRU           *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_XPDS_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SaveCurEntryMsg
 ��������  : ���浱ǰ״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
              pstMsg             :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��08��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_MSG_STRU                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����CNAS XSD�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 = TAF_XPDS_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetIntMsgQueueAddr
 ��������  : ��ȡ�ڲ���Ϣ�����׵�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_INT_MSG_QUEUE_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_XPDS_INT_MSG_QUEUE_STRU* TAF_XPDS_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(TAF_XPDS_GetCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitInternalBuffer
 ��������  : ��ʼ��HSD�ڲ���Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XPDS_InitInternalBuffer(
    TAF_XPDS_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < TAF_XPDS_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_PutMsgInIntMsgQueue
 ��������  : ����Ϣ�ŵ��ڲ���Ϣ������
 �������  : pSndMsg:�����͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��13��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_XPDS_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = TAF_XPDS_GetIntMsgNum();

    /* ����ڲ���Ϣ���У��Ƿ��л���������� */
    if (TAF_XPDS_MAX_INT_MSG_QUEUE_NUM <= ucIntMsgNum)
    {
        PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

        XPDS_ERROR_LOG("TAF_XPDS_PutMsgInIntMsgQueue: msg queue is full!");

        return;
    }

    /* ���浱ǰ��Ϣ */
    TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetNextIntMsg
 ��������  : ��ȡ�ڲ���Ϣ�����е���һ�����õ��ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ڲ���Ϣ���е�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 *TAF_XPDS_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* ��ȡ��һ���������Ϣ��Ϣ */
        pstIntMsg = TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* �ڲ���Ϣ��Ŀ����һ�� */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* ǰ���ڲ���Ϣ */
            PS_MEM_MOVE(&(TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[0]),
                        &(TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[1]),
                        ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* ����Ϣ������β������Ϣ��Ϊ��ָ�� */
        TAF_XPDS_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetIntMsgNum
 ��������  : ��ȡ��ǰHSD�ڲ���Ϣ����
 �������  : ��
 �������  :
 �� �� ֵ  : ��ǰ���ڵ��ڲ���Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = TAF_XPDS_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetTimerCtxAddr
 ��������  : ��ȡXPDS Timer Context
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_TIMER_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��22��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_TIMER_CTX_STRU* TAF_XPDS_GetTimerCtxAddr(VOS_VOID)
{
    return g_stTafXpdsCtx.astTimerCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCgpsInitialType
 ��������  : ��ȡAGPS������ԭ��SI or NI
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_INITIAL_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_INITIAL_TYPE_ENUM_UINT32 TAF_XPDS_GetCgpsInitialType(VOS_VOID)
{
    return g_stTafXpdsCtx.stCagpsCfg.enAgpsType;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetAgpsFixMode
 ��������  : ��ȡCAGPS����Mode
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_FIX_MODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_FIX_MODE_ENUM_UINT8 TAF_XPDS_GetAgpsFixMode(VOS_VOID)
{
    return g_stTafXpdsCtx.stCagpsCfg.enFixMode;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetAgpsFixMode
 ��������  : set the Fix mode to
                TAF_XPDS_MSA_MODE,
                TAF_XPDS_MSB_MODE,
                TAF_XPDS_MSS_MODE,
                TAF_XPDS_AFLT_MODE,
 �������  : TAF_XPDS_FIX_MODE_ENUM_UINT8 enFixMode
 �������  : TAF_XPDS_FIX_MODE_ENUM_UINT8
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��15��
    ��    ��   : A00903922
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetAgpsFixMode(TAF_XPDS_FIX_MODE_ENUM_UINT8 enFixMode)
{
    g_stTafXpdsCtx.stCagpsCfg.enFixMode = enFixMode;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetAgpsCfg
 ��������  : ��ȡ��ǰCAGPS����ģʽ��������/�û��� MSA/MSB����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_CFG_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_CFG_INFO_STRU* TAF_XPDS_GetAgpsCfg(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stCagpsCfg);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCtrlInfoAddr
 ��������  : ��ȡ��ǰCAGPSҵ����صĿ�����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_CTRL_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_CTRL_INFO_STRU* TAF_XPDS_GetCtrlInfoAddr(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stCtrlInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPublicDataAddr
 ��������  : ��ȡAGPS��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_PUBLIC_DATA_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_PUBLIC_DATA_STRU* TAF_XPDS_GetPublicDataAddr(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stPublicData);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetPosProcRslt
 ��������  :
 �������  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPosProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPosProcRslt
)
{
    TAF_XPDS_GetPublicDataAddr()->enPosProcRslt = enPosProcRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPosProcRslt
 ��������  :
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetPosProcRslt(VOS_VOID)
{
    return TAF_XPDS_GetPublicDataAddr()->enPosProcRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetUpLinkStatus
 ��������  : ��ȡ�û������ݴ���ͨ����MPC or PDE��·
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8 TAF_XPDS_GetUpLinkStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetUpLinkStatus
 ��������  : ���µ�ǰ���ݴ���ͨ��
 �������  : TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enUpLinkStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_UpdateUpLinkStatus(VOS_VOID)
{
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enMpcBindStatus;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enPdeBindStatus;

    enMpcBindStatus = TAF_XPDS_GetMpcServerStatus();
    enPdeBindStatus = TAF_XPDS_GetPdeServerStatus();

    if ((AT_XPDS_SERVER_BIND_STATUS_CONNECT == enMpcBindStatus)
     && (AT_XPDS_SERVER_BIND_STATUS_CONNECT == enPdeBindStatus))
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED;
    }
    else if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == enMpcBindStatus)
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_MPC_CONNECTED;
    }
    else if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == enPdeBindStatus)
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_PDE_CONNECTED;
    }
    else
    {
        g_stTafXpdsCtx.stUplinkCtx.enCurrLinkStatus = TAF_XPDS_UP_LINK_NOT_EXISTED;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetDataCallStatus
 ��������  : ��ȡCAGPS Data Call Status
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32 TAF_XPDS_GetDataCallStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enDataCallState;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetDataCallStatus
 ��������  : ����CAGPS Data Call Status
 �������  : AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32         enDataCallState
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��29��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetDataCallStatus(
    AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32         enDataCallState
)
{
    g_stTafXpdsCtx.stUplinkCtx.enDataCallState = enDataCallState;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetMpcServerStatus
 ��������  : ��ȡ��ǰMPC Server Bind Status
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetMpcServerStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enMpcBindStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPdeServerStatus
 ��������  : ��ȡ��ǰPDE Server Bind Status
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32 TAF_XPDS_GetPdeServerStatus(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enPdeBindStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetMpcServerStatus
 ��������  : ����MPC������Bind״̬
 �������  : AT_XPDS_CHSTATE_ENUM_UINT32         enMpcServerStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetMpcServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enMpcServerStatus
)
{
    g_stTafXpdsCtx.stUplinkCtx.enMpcBindStatus = enMpcServerStatus;

    TAF_XPDS_UpdateUpLinkStatus();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetPdeServerStatus
 ��������  : ����PDE������Bind״̬
 �������  : AT_XPDS_CHSTATE_ENUM_UINT32         enPdeServerStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPdeServerStatus(
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32         enPdeServerStatus
)
{
    g_stTafXpdsCtx.stUplinkCtx.enPdeBindStatus = enPdeServerStatus;

    TAF_XPDS_UpdateUpLinkStatus();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetUpLinkAbortScene
 ��������  : ��ȡ�쳣Abort�ĳ���ֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetUpLinkAbortScene(VOS_VOID)
{
    return g_stTafXpdsCtx.stUplinkCtx.enUpLinkAbortScene;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetUplinkAbortScene
 ��������  : �����쳣Abort�ĳ���ֵ
 �������  : TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enUpLinkAbortScene
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��10��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetUplinkAbortScene(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enUpLinkAbortScene
)
{
    g_stTafXpdsCtx.stUplinkCtx.enUpLinkAbortScene = enUpLinkAbortScene;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetCorrelationId
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  TAF_XPDS_GetCorrelationId(VOS_VOID)
{
    VOS_UINT8                           ucCorrelationId = 0;

    ucCorrelationId  = TAF_XPDS_GetMpcCtxAddr()->ucCurCorrelationId;

    TAF_XPDS_GetMpcCtxAddr()->ucCurCorrelationId++;

    return ucCorrelationId;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetFwdPdMsgHeader
 ��������  : Set forward PD msg head to ctx
 �������  : TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��14��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetFwdPdMsgHeader(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
)
{
    PS_MEM_CPY(&(TAF_XPDS_GetPdePublicData()->stFwdPdMsgHeader),
               pstPdMsgHeader,
               sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitDefaultCfgInfo
 ��������  : ��ʼ��CAGPSĬ������
 �������  : TAF_XPDS_CFG_INFO_STRU *pstCagpsCfg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitDefaultCfgInfo(VOS_VOID)
{
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    VOS_UINT8                           ucLastOmTestFlag;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    /* ��Ҫ������һ�ε�OM test ��־ */
    ucLastOmTestFlag = pstCagpsCfg->ucIsOmTestMode;

    PS_MEM_SET(pstCagpsCfg, 0x0, sizeof(TAF_XPDS_CFG_INFO_STRU));

    pstCagpsCfg->enFixMode      = TAF_XPDS_MSA_MODE;
    pstCagpsCfg->enAgpsType     = TAF_XPDS_SI;
    pstCagpsCfg->enCallType     = TAF_XPDS_USER_PLANE;
    pstCagpsCfg->usFixNum       = 1;
    pstCagpsCfg->enOmFixRslt    = NAS_OM_CDMA_GPS_FIX_RSLT_BUTT;

    pstCagpsCfg->ucIsOmTestMode = ucLastOmTestFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitProvGpsEph
 ��������  : Init ProvGpsEph
 �������  : VOS_VOID
 �������  : pstProvEph
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitProvGpsEph(
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                      *pstProvEph
)
{
    PS_MEM_SET(pstProvEph, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitProvGpsAlm
 ��������  : Init ProvGpsAlm
 �������  : VOS_VOID
 �������  : pstProvEph
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitProvGpsAlm(
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                 *pstProvAlm
)
{
    PS_MEM_SET(pstProvAlm, 0x00, sizeof(TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetTimeStamp
 ��������  :
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetTimeStamp(
    TAF_XPDS_TIME_STAMP_STRU            *pstTimeStamp
)
{
    VOS_UINT64                          ullSecNum = 0;

    if (TAF_SDC_SYS_MODE_EVDO == TAF_SDC_GetSysMode())
    {
        ullSecNum = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_HRPD) * 8 / 100;
    }
    else
    {
        ullSecNum = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X)  * 8 / 100;
    }

    pstTimeStamp->ulWeekNum = (VOS_UINT32)(ullSecNum / (7 * 24 * 3600));
    pstTimeStamp->ulSecNum  = (VOS_UINT32)(ullSecNum % (7 * 24 * 3600));

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPdePublicData
 ��������  : ��ȡPDE��������ָ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_PDE_PUBLIC_DATA_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_PDE_PUBLIC_DATA_STRU * TAF_XPDS_GetPdePublicData(VOS_VOID)
{
    return &(g_stTafXpdsCtx.stPdePubData);
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitPdePublicDataTaskInit
 ��������  : Task��ʼ��ʱ��ʼ��PDE������صĹ�������
 �������  : pstPdePubData - PDE��������ָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitPdePublicDataTaskInit(VOS_VOID)
{
    PS_MEM_SET(TAF_XPDS_GetPdePublicData(), 0, sizeof(TAF_XPDS_PDE_PUBLIC_DATA_STRU));
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_InitPdePublicDataPdeInit
 ��������  : PDE���̳�ʼ��ʱ��ʼ��PDE������صĹ�������
             ����Position Determination Data Message�е�sess_tag��Ҫ������һ��session����ʱ��ֵ
 �������  : pstPdePubData - PDE��������ָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_InitPdePublicDataPdeInit(VOS_VOID)
{
    TAF_XPDS_PDE_PUBLIC_DATA_STRU      *pstPdePubData = VOS_NULL_PTR;
    VOS_UINT8                           ucLastSessTag;

    pstPdePubData = TAF_XPDS_GetPdePublicData();

    ucLastSessTag = pstPdePubData->ucSessTagInRsvPdMsgHeader;

    PS_MEM_SET(pstPdePubData, 0, sizeof(TAF_XPDS_PDE_PUBLIC_DATA_STRU));

    pstPdePubData->ucSessTagInRsvPdMsgHeader = ucLastSessTag;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetGpsEphDataFinishedFlag
 ��������  : ����GPS EPH�����Ƿ�����ı�־
 �������  : ucIsFinisehd - �����Ƿ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetGpsEphDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
)
{
    TAF_XPDS_GetPdePublicData()->ucIsGpsEphDataFinished = ucIsFinisehd;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetGpsEphDataFinishedFlag
 ��������  : ��ȡGPS EPH�����Ƿ�����ı�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - GPS EPH�����ѽ���
             VOS_FALSE - GPS EPH����δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetGpsEphDataFinishedFlag(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucIsGpsEphDataFinished);
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetGpsAlmDataFinishedFlag
 ��������  :
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetGpsAlmDataFinishedFlag(
    VOS_UINT8                           ucIsFinisehd
)
{
    TAF_XPDS_GetPdePublicData()->ucIsGpsAlmDataFinished = ucIsFinisehd;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetGpsAlmDataFinishedFlag
 ��������  : ��ȡGPS ALM�����Ƿ�����ı�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - GPS ALM�����ѽ���
             VOS_FALSE - GPS ALM����δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetGpsAlmDataFinishedFlag(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucIsGpsAlmDataFinished);
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetPdeSessionStatus
 ��������  : ��ȡPDE session״̬
 �������  : enPdeSessionStatus - PDE session״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPdeSessionStatus(
    TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8                  enPdeSessionStatus
)
{
    (TAF_XPDS_GetPdePublicData()->enPdeSessionStatus) = enPdeSessionStatus;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPdeSessionStatus
 ��������  : ��ȡPDE session״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8 - PDE session״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_PDE_SESSION_STATUS_ENUM_UINT8 TAF_XPDS_GetPdeSessionStatus(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->enPdeSessionStatus);
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetPdeSessionTriggerType
 ��������  : ����PDE session��������
 �������  : enPdeSessionTriggerType - PDE session��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetPdeSessionTriggerType(
    TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8            enPdeSessionTriggerType
)
{
    (TAF_XPDS_GetPdePublicData()->enPdeSessionTriggerType) = enPdeSessionTriggerType;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPdeSessionTriggerType
 ��������  : ��ȡPDE session��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8 - PDE session��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_ENUM_UINT8 TAF_XPDS_GetPdeSessionTriggerType(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->enPdeSessionTriggerType);
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetSessTagInRsvPdMsgHeader
 ��������  : ���÷���PDE Position Determination Data Message�е�sess_tagֵ
 �������  : ucSessTag - sess_tagֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetSessTagInRsvPdMsgHeader(VOS_UINT8 ucSessTag)
{
    (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader) = ucSessTag;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetSessTagInRsvPdMsgHeader
 ��������  : ��ȡ����PDE Position Determination Data Message�е�sess_tagֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 - sess_tagֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetSessTagInRsvPdMsgHeader(VOS_VOID)
{
    return (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader);
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader
 ��������  : ����PDE Position Determination Data Message�е�sess_tagֵ
             ÿ�μ�1���������32����0��ʼ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader(VOS_VOID)
{
    VOS_UINT8                           ucLastSessTag;

    ucLastSessTag = TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader;

    (TAF_XPDS_GetPdePublicData()->ucSessTagInRsvPdMsgHeader) = (ucLastSessTag + 1) % 32;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPrmTimerLimitLen
 ��������  : CAGPS ����MS�ظ�PRM��Ϣ�Ķ�ʱ��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��01��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetPrmTimerLimitLen(VOS_VOID)
{
    VOS_UINT8                           ucPrefRespQual;

    ucPrefRespQual = TAF_XPDS_GetPdePublicData()->stFwdReqPsuRangeMeas.ucPrefRespQual;

    return TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(ucPrefRespQual);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetPilotPhaseTimerLimitLen
 ��������  : CAGPS ����MS�ظ�PILOT PHASE��Ϣ�Ķ�ʱ��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_GetPilotPhaseTimerLimitLen(VOS_VOID)
{
    VOS_UINT8                           ucPrefRespQual;

    ucPrefRespQual = TAF_XPDS_GetPdePublicData()->stFwdReqPilotPhaseMeas.ucPrefRespQual;

    return TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(ucPrefRespQual);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetGpsClientId
 ��������  : ���GPSͨ��ʹ�õ�ClientId
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_XPDS_GetGpsClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usGpsClientId;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetApClientId
 ��������  : ���APͨ��ʹ�õ�ClientId
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_XPDS_GetApClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usApClientId;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetUtsClientId
 ��������  : ���UTSͨ��ʹ�õ�ClientId
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��05��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_XPDS_GetUtsClientId(VOS_VOID)
{
    return TAF_XPDS_GetAgpsCfg()->usUtsClientId;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetGpsClientId
 ��������  : ����GPSͨ��ʹ�õ�ClientId
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetGpsClientId(
    VOS_UINT16                              usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usGpsClientId = usClientId;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetApClientId
 ��������  : ����APͨ��ʹ�õ�ClientId
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetApClientId(
    VOS_UINT16                              usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usApClientId = usClientId;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetUtsClientId
 ��������  : ����UTSͨ��ʹ�õ�ClientId
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetUtsClientId(
    VOS_UINT16                          usClientId
)
{
    TAF_XPDS_GetAgpsCfg()->usUtsClientId = usClientId;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetMpcCtxAddr
 ��������  : ��ȡMPC��ص�ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_XPDS_MPC_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��14��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_MPC_CTX_STRU* TAF_XPDS_GetMpcCtxAddr(
    VOS_VOID
)
{
    return &(g_stTafXpdsCtx.stMpcCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_CAGPS_UPLINK_CTX_STRU
 ��������  : ��ȡUSER PLANE��ص�ȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_XPDS_MPC_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��17��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_CAGPS_UPLINK_CTX_STRU* TAF_XPDS_GetUpLinkCtxAddr(
    VOS_VOID
)
{
    return &(g_stTafXpdsCtx.stUplinkCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetOmTestFlag
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmTestFlag(VOS_UINT8 ucIsOmTestMode)
{
    TAF_XPDS_GetAgpsCfg()->ucIsOmTestMode = ucIsOmTestMode;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetOmTestFlag
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetOmTestFlag(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->ucIsOmTestMode);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetOmFixRslt
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmFixRslt(VOS_UINT8 enFixRslt)
{
    TAF_XPDS_GetAgpsCfg()->enOmFixRslt = enFixRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetOmFixRslt
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 TAF_XPDS_GetOmFixRslt(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->enOmFixRslt);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetOmTestAbortFlag
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmTestAbortFlag(VOS_UINT8 isAborted)
{
    TAF_XPDS_GetAgpsCfg()->ucIsOmTestAborted = isAborted;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetOmTestAbortFlag
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_XPDS_GetOmTestAbortFlag(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->ucIsOmTestAborted);
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_SetOmTestPdeProcRslt
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_SetOmTestPdeProcRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enPdeProcRslt
)
{
    TAF_XPDS_GetAgpsCfg()->enOmTestPdeProcRslt = enPdeProcRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_GetOmTestPdeProcRslt
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetOmTestPdeProcRslt(VOS_VOID)
{
    return (TAF_XPDS_GetAgpsCfg()->enOmTestPdeProcRslt);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

