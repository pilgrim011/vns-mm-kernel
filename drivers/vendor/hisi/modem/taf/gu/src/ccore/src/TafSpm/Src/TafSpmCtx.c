/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmCtx.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��5��8��
  ����޸�   :
  ��������   : TafSpmCtx.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��8��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmFsmMainTbl.h"
#include "TafSpmMain.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafLog.h"
#include "MnComm.h"
#include "UsimPsInterface.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmMntn.h"
#include "NasUsimmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_CTX_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
/* ���湲�õ�CTX */
TAF_SPM_CONTEXT_STRU                    g_stTafSpmCtx;

/*****************************************************************************
 ȫ�ֱ�����    : gastSpmGetClientIdList
 ȫ�ֱ���˵��  : ��ȡ��ǰ��Ϣ����Ӧ��client ID�Ĵ������б�
 1.��    ��   : 2013��5��8��
   ��    ��   : w00176964
   �޸�����   : �½�
 2.��    ��   : 2013��6��26��
   ��    ��   : f62575
   �޸�����   : V9R1 STK����
*****************************************************************************/
TAF_SPM_GET_MSG_CLIENT_ID_LIST_STRU gastSpmGetClientIdList[] =
{
    {WUEPS_PID_AT,      TAF_SPM_GetClientIdWithAppMsg},
    {MAPS_STK_PID,      TAF_SPM_GetClientIdWithStkMsg},
    {WUEPS_PID_USIM,    TAF_SPM_GetClientIdWithUsimMsg},
    {MAPS_PB_PID,       TAF_SPM_GetClientIdWithPbMsg},
    {WUEPS_PID_TAF,     TAF_SPM_GetClientIdWithTafMsg},
    {VOS_PID_TIMER,     TAF_SPM_GetClientIdWithVosTimerMsg},
};

/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSpmCtxAddr
 ��������  : ��ȡ��ǰspm��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰspm��CTX
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��8��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_CONTEXT_STRU* TAF_SPM_GetSpmCtxAddr( VOS_VOID )
{
    return &(g_stTafSpmCtx);
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_SetCurrEntityFsmState
 ��������  : ���õ�ǰclient IDʵ������Ӧ��״̬��״̬
 �������  : ulState:״̬��״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_SetCurrEntityFsmState(
    VOS_UINT32                          ulState
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.ulState = ulState;

    TAF_SPM_LogFsmInfo();
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmState
 ��������  : ��ȡ��ǰclient IDʵ������Ӧ��״̬��״̬
 �������  : ��
 �������  : ulState:��ǰclient IDʵ������Ӧ��״̬��״̬
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_SPM_GetCurrEntityFsmState( VOS_VOID )
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.ulState);
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_SetCurrEntityFsmClientId
 ��������  : ���õ�ǰclient IDʵ������Ӧ��client ID
 �������  : usClientId:client ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_SetCurrEntityFsmClientId(
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->usClientId = usClientId;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmClientId
 ��������  : ��ȡ��ǰclient IDʵ������Ӧ��client ID
 �������  : ��
 �������  : usClientId:client ID
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16  TAF_SPM_GetCurrEntityFsmClientId( VOS_VOID )
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->usClientId);
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_SetCurrEntityFsmAddr
 ��������  : ���õ�ǰclient idʵ������Ӧ��״̬����ַ
 �������  : ucFsmIndex:client id��״̬����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SPM_SetCurrEntityFsmAddr(
    VOS_UINT8                           ucFsmIndex
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm = &(TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex]);
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmAddr
 ��������  : ��ȡ��ǰclient idʵ������Ӧ��״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰclient idʵ������Ӧ��״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmAddr(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetCurrEntityFsmRunFlg
 ��������  : ���õ�ǰclient idʵ������Ӧ��״̬�����б��
 �������  : ucRunFlg:��ǰclient id��ʵ���Ӧ��״̬�����б��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_SetCurrEntityFsmRunFlg(
    VOS_UINT8                           ucRunFlg
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->ucRunFlg = ucRunFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmRunFlg
 ��������  : ��ȡ��ǰclient idʵ������Ӧ��״̬�����б��
 �������  : ��
 �������  : ��ǰclient idʵ������Ӧ��״̬�����б��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  TAF_SPM_GetCurrEntityFsmRunFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->ucRunFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmId
 ��������  : ��ȡ��ǰclient idʵ������Ӧ��״̬��ID
 �������  : ��
 �������  : ��ǰclient idʵ������Ӧ��״̬��ID
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_FSM_ID_ENUM_UINT32  TAF_SPM_GetCurrEntityFsmId(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.enFsmId);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmCtxAddr
 ��������  : ��ȡ��ǰclient Idʵ������Ӧ��״̬�������ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰCLIENT IDʵ������Ӧ��״̬�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmCtxAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrMainFsmAddr
 ��������  : ��ȡ��ǰ��״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SPM_MAIN_FSM_CTX_STRU* TAF_SPM_GetCurrMainFsmAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stCurMainFsm);
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_GetEntityFsmRunFlgByFsmIndex
 ��������  : ��ȡָ��������CLIENT IDʵ��״̬�����б��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ָ��������client IDʵ��״̬�����б��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetEntityFsmRunFlgByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return (TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].ucRunFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetEntityFsmCtxAddrByFsmIndex
 ��������  : ��ȡָ��������client IDʵ������Ӧ��״̬�������ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ָ��������client IDʵ������Ӧ��״̬�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return &(TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].stFsmCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitEntityFsmCtx
 ��������  : ��ʼ��CLIENT IDʵ��״̬��������
 �������  : ��
 �������  : pstCurrFsmCtx:��ǰclient IDʵ��״̬����������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SPM_InitEntityFsmCtx(
    TAF_SPM_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId    = TAF_SPM_FSM_BUTT;
    pstCurrFsmCtx->pstFsmDesc = VOS_NULL_PTR;
    pstCurrFsmCtx->ulState    = TAF_SPM_SERVICE_CTRL_STA_BUTT;

    PS_MEM_SET(&pstCurrFsmCtx->stEntryMsg,
               0,
               sizeof(pstCurrFsmCtx->stEntryMsg));
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitMainCtrlInfo
 ��������  : ��ʼ����ǰSPMģ���������Ϣ
 �������  : ��
 �������  : pstMainCtrl:��ǰSPMģ���������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_InitMainCtrlInfo(
    TAF_SPM_MAIN_CTRL_INFO_STRU        *pstMainCtrl
)
{
    /* ��ʼ����ǰ������Ϣ */
    pstMainCtrl->ucUpdateEntryMsgFlg     = VOS_FALSE;

    PS_MEM_SET( pstMainCtrl->aucRsv,
                (VOS_UINT8)0x00,
                sizeof(pstMainCtrl->aucRsv) );

    PS_MEM_SET( &(pstMainCtrl->stServiceCtrlEntryMsg),
                (VOS_UINT8)0x00,
                sizeof(TAF_SPM_ENTRY_MSG_STRU) );

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitServiceCtrlCfgInfo
 ��������  : ��ʼ����ǰSPMģ���service ctrl��������Ϣ
 �������  : ��
 �������  : pstServiceCtrlCfg:service ctrl��������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��6��5��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�

*****************************************************************************/
VOS_VOID  TAF_SPM_InitServiceCtrlCfgInfo(
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfg
)
{
    pstServiceCtrlCfg->ulMeStatus                               = TAF_FDN_CHECK_FEATURE_OFF;
    pstServiceCtrlCfg->ucSimCallCtrlSupportFlg                  = VOS_FALSE;

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-15, begin */
    pstServiceCtrlCfg->enVpCfgState                             = TAF_SPM_VP_MO_MT_BOTH;
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-15, end */


    
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferCcProtectTimerLen 
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferSmsProtectTimerLen
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferSsProtectTimerLen
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;

    
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitFsmCtx_Main
 ��������  : ��ʼ����״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  TAF_SPM_InitFsmCtx_Main(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitFsmCtx_ServiceCtrl
 ��������  : ��ʼ��service ctrl״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  TAF_SPM_InitFsmCtx_ServiceCtrl(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_FSM_InitEntityFsm
 ��������  : ����client IDʵ��״̬��
 �������  : enFsmId:״̬��ID
             pstFsmDesc:״̬��������
             ulState:״̬������״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
****************************************************************************/
VOS_VOID TAF_SPM_FSM_InitEntityFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_SPM_FSM_CTX_STRU               *pstCurrEntityFsmCtx         = VOS_NULL_PTR;

    /*  ��ȡ��ǰclient IDʵ��״̬�������� */
    pstCurrEntityFsmCtx                 = TAF_SPM_GetCurrEntityFsmCtxAddr();

    pstCurrEntityFsmCtx->enFsmId      = enFsmId;
    pstCurrEntityFsmCtx->pstFsmDesc   = pstFsmDesc;
    pstCurrEntityFsmCtx->ulState      = ulState;

    TAF_SPM_SetCurrEntityFsmRunFlg(VOS_TRUE);

    /* ��ʼ��״̬�������� */
    pstCurrEntityFsmCtx->pstFsmDesc->pfInitHandle();

    TAF_SPM_LogFsmInfo();
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_FSM_InitMainFsm
 ��������  : ������״̬��
 �������  : enFsmId:״̬��ID
             pstFsmDesc:״̬��������
             ulState:״̬������״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��15��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
****************************************************************************/
VOS_VOID TAF_SPM_FSM_InitMainFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_SPM_MAIN_FSM_CTX_STRU          *pstCurrMainFsm  = VOS_NULL_PTR;

    /*  ��ȡ��ǰmain״̬����Ϣ */
    pstCurrMainFsm               = TAF_SPM_GetCurrMainFsmAddr();

    pstCurrMainFsm->stFsmCtx.enFsmId      = enFsmId;
    pstCurrMainFsm->stFsmCtx.pstFsmDesc   = pstFsmDesc;
    pstCurrMainFsm->stFsmCtx.ulState      = ulState;

    /* ��ʼ��״̬�������� */
    pstCurrMainFsm->stFsmCtx.pstFsmDesc->pfInitHandle();
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_FSM_QuitCurrEntityFsm
 ��������  : �˳���ǰclient IDʵ��״̬��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-5-15
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_FSM_QuitCurrEntityFsm(VOS_VOID)
{
    TAF_SPM_FSM_CTX_STRU               *pstCurrFsmCtx = VOS_NULL_PTR;

    /*  ��ȡ��ǰ��client IDʵ��״̬�������� */
    pstCurrFsmCtx               = TAF_SPM_GetCurrEntityFsmCtxAddr();

    /* ���״̬���������״̬��ID */
    pstCurrFsmCtx->pstFsmDesc   = VOS_NULL_PTR;
    pstCurrFsmCtx->enFsmId      = TAF_SPM_FSM_BUTT;
    pstCurrFsmCtx->ulState      = TAF_SPM_SERVICE_CTRL_STA_BUTT;

    TAF_SPM_SetCurrEntityFsmClientId(TAF_SPM_INVALID_CLIENT_ID);
    TAF_SPM_SetCurrEntityFsmRunFlg(VOS_FALSE);

    TAF_SPM_LogFsmInfo();
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_InitEntityFsm
 ��������  : client IDʵ��״̬���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_InitEntityFsm(VOS_VOID)
{
    VOS_UINT8                           i;

    /* for ѭ������ʼ������ʵ��״̬�������� */
    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        /* �������õ�ǰ��ʵ��״̬�� */
        TAF_SPM_SetCurrEntityFsmAddr(i);

        /* ��ʼ��ʵ�������� */
        TAF_SPM_InitEntityFsmCtx(TAF_SPM_GetCurrEntityFsmCtxAddr());

        TAF_SPM_SetCurrEntityFsmRunFlg(VOS_FALSE);

        TAF_SPM_SetCurrEntityFsmClientId(TAF_SPM_INVALID_CLIENT_ID);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitMainFsm
 ��������  : ��״̬���ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_InitMainFsm(VOS_VOID)
{
    TAF_SPM_MAIN_FSM_CTX_STRU          *pstMainFsmCtx = VOS_NULL_PTR;

    pstMainFsmCtx = TAF_SPM_GetCurrMainFsmAddr();

    pstMainFsmCtx->stFsmCtx.enFsmId         = TAF_SPM_FSM_BUTT;
    pstMainFsmCtx->stFsmCtx.ulState         = TAF_SPM_MAIN_STA_BUTT;
    pstMainFsmCtx->stFsmCtx.pstFsmDesc      = VOS_NULL_PTR;

    PS_MEM_SET(&pstMainFsmCtx->stFsmCtx.stEntryMsg,
               0,
               sizeof(pstMainFsmCtx->stFsmCtx.stEntryMsg));

}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmEntryMsgAddr
 ��������  : ��ȡ��ǰclient idʵ���״̬���������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰclient idʵ��״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetCurrEntityFsmEntryMsgAddr(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;

    /*  ��ȡ��ǰ��client ID״̬�������ĵ�ַ */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    return &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmEntryMsgSndPid
 ��������  : ��ȡ��ǰclient idʵ���״̬���������Ϣ�ķ���PID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰclient idʵ��״̬�������Ϣ�ķ���pid
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetCurrEntityFsmEntryMsgSndPid(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg                = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg                  = VOS_NULL_PTR;
    VOS_UINT32                                              ulSndPid;

    /*  ��ȡ��ǰ��client ID״̬�������ĵ�ַ */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    pstEntryMsg  = &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
    pstAppMsg    = (MN_APP_REQ_MSG_STRU*)pstEntryMsg->aucEntryMsgBuffer;
    ulSndPid     = pstAppMsg->ulSenderPid;

    return ulSndPid;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCurrEntityFsmEntryMsgName
 ��������  : ��ȡ��ǰclient idʵ���״̬���������Ϣ����Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰclient idʵ��״̬�������Ϣ����Ϣ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_SPM_GetCurrEntityFsmEntryMsgName(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg                = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg                  = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgName;

    /*  ��ȡ��ǰ��client ID״̬�������ĵ�ַ */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    pstEntryMsg  = &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
    pstAppMsg    = (MN_APP_REQ_MSG_STRU*)pstEntryMsg->aucEntryMsgBuffer;
    usMsgName    = pstAppMsg->usMsgName;

    return usMsgName;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetEntityFsmClientIdByFsmIndex
 ��������  : ����״̬�������������ȡ״̬����client ID
 �������  : ucFsmIndex:״̬�����������
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����Ӧ��client ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_SPM_GetEntityFsmClientIdByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return (TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].usClientId);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetEntityFsmIndexByClientId
 ��������  : ����״̬����client ID��ȡ״̬�����������
 �������  : usClientId:״̬����client ID
 �������  : ��
 �� �� ֵ  : ״̬�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetEntityFsmIndexByClientId(
    VOS_UINT16                          usClientId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucFsmIndex;
    VOS_UINT16                          usCurClientId;
    VOS_UINT8                           ucRunFlg;

    ucFsmIndex = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    /* client ID��Ч�����в���ֱ�ӷ��� */
    if (TAF_SPM_INVALID_CLIENT_ID == usClientId)
    {
        return ucFsmIndex;
    }

    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        usCurClientId   = TAF_SPM_GetEntityFsmClientIdByFsmIndex(i);
        ucRunFlg        = TAF_SPM_GetEntityFsmRunFlgByFsmIndex(i);

        if ((usClientId == usCurClientId)
         && (VOS_TRUE   == ucRunFlg))
        {
            ucFsmIndex = i;
            break;
        }
    }

    return ucFsmIndex;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_GetIdleEntityFsmIndex
 ��������  : ��client IDʵ��״̬�������л�ȡ���е�״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����״̬������ ��Ч��ʾ�޿���״̬��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetIdleEntityFsmIndex(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucRunFlg;
    VOS_UINT8                           ucIndex;

    ucIndex = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        ucRunFlg = TAF_SPM_GetEntityFsmRunFlgByFsmIndex(i);

        if (VOS_FALSE == ucRunFlg)
        {
            ucIndex = i;
            break;
        }
    }

    return ucIndex;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_SaveCurrEntityFsmEntryMsg
 ��������  : ���浱ǰclient IDʵ��״̬������״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
             pstMsg                 :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-5-9
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SaveCurrEntityFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ���������Ϣ�Ļ�������ַ */
    /* ��õ�ǰ����SPM�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 =   TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;
    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_GetTimerCtxAddr
 ��������  : ��ȡspm CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : spm CTXģ���ж�ʱ����������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_TIMER_CTX_STRU*  TAF_SPM_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_SPM_GetSpmCtxAddr()->astSpmTimerCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetServiceCtrlCfgInfoAddr
 ��������  : ��ȡspm CTXģ����service ctrl��CFG��Ϣ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : spm CTXģ����service ctrl��CFG��Ϣ��������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU*  TAF_SPM_GetServiceCtrlCfgInfoAddr( VOS_VOID )
{
    return &(TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetBufferServiceReqProtectTimerInfo
 ��������  : ��ȡ����cc sms ss �������󱣻���ʱ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU:�����������ʱ������ʱ����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��9��
   ��    ��   : c00318887
   �޸�����   : �½�����
*****************************************************************************/
TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU* TAF_SPM_GetBufferServiceReqProtectTimerInfo(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_Spm_GetBufferCcProtectTimerLen
 ��������  : ��ȡ����cc ��������ʱ������ʱ��ʱ������λ ms
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������ʱ��ʱ������λ ms
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��10��9��
    ��    ��   : c00318887
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32   TAF_Spm_GetBufferCcProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferCcProtectTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetBufferSmsProtectTimerLen
 ��������  : ��ȡ����Sms ��������ʱ������ʱ��ʱ������λ ms
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������ʱ��ʱ������λ ms
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��9��
    ��    ��   : c00318887
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32   TAF_SPM_GetBufferSmsProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferSmsProtectTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetBufferSsProtectTimerLen
 ��������  : ��ȡ����Ss ��������ʱ������ʱ��ʱ������λ ms
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������ʱ��ʱ������λ ms
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��9��
    ��    ��   : c00318887
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32   TAF_SPM_GetBufferSsProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferSsProtectTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetUpdateEntryMsgFlg
 ��������  : ����SPMģ�����滻APP����SS��Ϣ�ı��
 �������  : ucReplaceFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID TAF_SPM_SetUpdateEntryMsgFlg(
    VOS_UINT8                           ucReplaceFlg
)
{
    TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.ucUpdateEntryMsgFlg = ucReplaceFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetUpdateEntryMsgFlg
 ��������  : ��ȡSPMģ���и���service ctrl�����Ϣ�ı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : SPMģ���и���service ctrl�����Ϣ�ı��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��8��
   ��    ��   : w00176964
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetUpdateEntryMsgFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.ucUpdateEntryMsgFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_UpdateServiceCtrlEntryMsg
 ��������  : ����service ctrl�������Ϣ
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-05-8
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_UpdateServiceCtrlEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����ķ��͸�SS��������Ϣ�Ļ�������ַ */
    pstEntryMsg                 =   TAF_SPM_GetServiceCtrlEntryMsgAddr();
    pstMsgHeader                =   (MSG_HEADER_STRU*)pstMsg;
    ulLen                       =   pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ��Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ�� */
    if ( ulLen > TAF_SPM_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_UpdateServiceCtrlEntryMsg:Msg too big to save ");
        return ;
    }

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetServiceCtrlEntryMsgAddr
 ��������  : ��ȡSPMģ���и���service ctrl�����Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : SPMģ���и���service ctrl�����Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-05-8
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetServiceCtrlEntryMsgAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.stServiceCtrlEntryMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientIdWithAppMsg
 ��������  : ��ȡAT��STK��Ϣ��Ӧ��CLIENT ID
 �������  : pstMsg:�������Ϣ
 �������  : pusClientId - client ID
 �� �� ֵ  : VOS_TRUE:��ȡclient ID�ɹ�
             VOS_FALS:��ȡclient IDʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    *pusClientId =  pstAppMsg->clientId;

    return VOS_TRUE;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientIdWithStkMsg
 ��������  : ��ȡSTK��Ϣ��Ӧ��CLIENT ID
 �������  : pstMsg:�������Ϣ
 �������  : pusClientId - client ID
 �� �� ֵ  : VOS_TRUE:��ȡclient ID�ɹ�
             VOS_FALS:��ȡclient IDʧ��
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
VOS_UINT32 TAF_SPM_GetClientIdWithStkMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope     = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;
    if (SI_STK_ENVELOPE_CNF == pstMsgHeader->ulMsgName)
    {
        pstEnvelope  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
		/* ��16λΪCliendId */
        *pusClientId = (VOS_UINT16)(pstEnvelope->stCmdResult.ulSendPara  & 0x0000ffff);
    }
    else
    {
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)pstMsg;

        *pusClientId =  pstAppMsg->clientId;
    }

    return VOS_TRUE;
}
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetOpIdWithAppMsg
 ��������  : ��ȡAT��STK��Ϣ��Ӧ��OP ID
 �������  : pstMsg:�������Ϣ
 �������  : pucOpId - OP ID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_GetOpIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucOpId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    *pucOpId =  pstAppMsg->opId;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientIdWithVosTimerMsg
 ��������  : ��ȡOSA timer��Ϣ��Ӧ��CLIENT ID
 �������  : pstMsg:�������Ϣ
 �������  : pusClientId - client ID
 �� �� ֵ  : VOS_TRUE:��ȡclient ID�ɹ�
             VOS_FALS:��ȡclient IDʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithVosTimerMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    switch (pstRcvTimerMsg->ulName)
    {
        case TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF:
        case TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF:

            *pusClientId = (VOS_UINT16)pstRcvTimerMsg->ulPara;
            ulRet = VOS_TRUE;

            break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientIdWithUsimMsg
 ��������  : ��ȡUSIM��Ϣ��Ӧ��CLIENT ID
 �������  : pstMsg:�������Ϣ
 �������  : pusClientId - client ID
 �� �� ֵ  : VOS_TRUE:��ȡclient ID�ɹ�
             VOS_FALS:��ȡclient IDʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithUsimMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope = VOS_NULL_PTR;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case SI_STK_ENVELOPE_CNF:
             pstEnvelope  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
            *pusClientId  = (VOS_UINT16)pstEnvelope->stCmdResult.ulSendPara;
             ulRet        = VOS_TRUE;
             break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientIdWithPbMsg
 ��������  : ��ȡPB��Ϣ��Ӧ��CLIENT ID
 �������  : pstMsg:�������Ϣ
 �������  : pusClientId - client ID
 �� �� ֵ  : VOS_TRUE:��ȡclient ID�ɹ�
             VOS_FALS:��ȡclient IDʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithPbMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    PB_FDN_CHECK_CNF_STRU              *pstCheckCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case SI_PB_EVENT_FDNCHECK_CNF:

            pstCheckCnf     = (PB_FDN_CHECK_CNF_STRU*)pstMsg;
            /* ��16λΪCliendId */
           *pusClientId     = (VOS_UINT16)(pstCheckCnf->ulSendPara & 0x0000ffff);
            ulRet           = VOS_TRUE;
            break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientIdWithTafMsg
 ��������  : ��ȡTAF��Ϣ��Ӧ��CLIENT ID
 �������  : pstMsg:�������Ϣ
 �������  : pusClientId - client ID
 �� �� ֵ  : VOS_TRUE:��ȡclient ID�ɹ�
             VOS_FALS:��ȡclient IDʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithTafMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU     *pstServiceCtrlRsltInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND:

             pstServiceCtrlRsltInd  = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;
            *pusClientId            = pstServiceCtrlRsltInd->usClientId;
             ulRet                  = VOS_TRUE;
             break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetClientId
 ��������  : ������Ϣת��client ID
 �������  : pstMsg
 �������  : pusClientId
 �� �� ֵ  : VOS_TRUE :��ȡCLIENT ID�ɹ�
             VOS_FALSE:��ȡclient IDʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_SPM_GetClientId(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    VOS_UINT32                          ulSndPid;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR  pCurFuncProc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    ulTblSize       = sizeof(gastSpmGetClientIdList)/sizeof(gastSpmGetClientIdList[0]);
    pstMsgHeader    = (MSG_HEADER_STRU *)pstMsg;
    ulSndPid        = pstMsgHeader->ulSenderPid;

     /* �ȸ�����Ϣ�ķ���PIDӳ�����Ӧ��client ID */
    for (i = 0; i < ulTblSize; i++)
    {
        if (ulSndPid == gastSpmGetClientIdList[i].ulSndPid)
        {
            pCurFuncProc = gastSpmGetClientIdList[i].pGetMsgClientIdProcFunc;
            break;
        }
    }


    if (VOS_NULL_PTR != pCurFuncProc)
    {
        ulRet = pCurFuncProc(pstMsg, pusClientId);

        return ulRet;
    }

    /* �Ҳ�����Ӧ�Ĵ����� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitServiceReqBufferMsgQueue
 ��������  : ��ʼ��������Ϣ����

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitServiceReqBufferMsgQueue(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU  *pstBufferMsgQueue = VOS_NULL_PTR;

    /* get address of buffer message queue */
    pstBufferMsgQueue = TAF_SPM_GetBufferMsgQueueAddr();

    /* init buffer CC message queue */
    TAF_SPM_InitBufferCcMsgQueue(&(pstBufferMsgQueue->stCcMsgQueue));

    /* init buffer SMS message queue */
    TAF_SPM_InitBufferSmsMsgQueue(&(pstBufferMsgQueue->stSmsMsgQueue));

    /* init buffer SS message queue */
    TAF_SPM_InitBufferSsMsgQueue(&(pstBufferMsgQueue->stSsMsgQueue));
}

#if (FEATURE_IMS == FEATURE_ON)
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_InitDomainSelCtx
 ��������  : ��ʼ����ѡ�����������

 �������  : pstDomainSelCtx -- ��ѡ��������ָ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitDomainSelCtx(TAF_SPM_DOMAIN_SEL_CTX_STRU *pstDomainSelCtx)
{
    /* ɾ��IMSע��״̬���Ƶ�SDC�� */

    /* ��ʼ��IMS���ŷ��ͱ�־ */
    pstDomainSelCtx->ucImsSmsSendingFlg  = VOS_FALSE;

    /* ��ʼ���ϴ�PS����״̬ */
    pstDomainSelCtx->enLastPsStatus      = TAF_SPM_SERVICE_STATUS_NO_SERVICE;

    /* set IMS SMS supported to TRUE by server */
    TAF_SPM_SetImsSmsSupportedOnImsServer(VOS_TRUE);

    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
    /* ҵ��������Ϣ���г�ʼ���Ƶ�����TAF_SPM_InitServiceReqBufferMsgQueue��ʵ�� */
    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-28, end */

    /* ��ʼ�����л����ز����� */
    TAF_SPM_InitCallRedialBuffer(&(pstDomainSelCtx->stRedialMsgQueue.stCcMsgQueue));

    /* ��ʼ�����Ż����ز����� */
    TAF_SPM_InitSmsRedialBuffer(&(pstDomainSelCtx->stRedialMsgQueue.stSmsMsgQueue));

    /* subscript IMS register status */
    pstDomainSelCtx->ulSubscriptId = 0;
    (VOS_VOID)IMSA_AddSubscription(WUEPS_PID_TAF, IMSA_SUBCRIBE_TYPE_NORMAL_REG, 0, &(pstDomainSelCtx->ulSubscriptId));
}
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, end */

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, begin */
/* ɾ��IMSע��״̬��غ������Ƶ�SDC�� */

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetImsSmsSupportedOnImsServer
 ��������  : ����IMS�������Ƿ�֧��IMS����
 �������  : IMS�������Ƿ�֧��IMS����:VOS_TRUE:֧�֣�VOS_FALSE:��֧��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID TAF_SPM_SetImsSmsSupportedOnImsServer(
    VOS_UINT8                           ucImsSmsSupported
)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSupported = ucImsSmsSupported;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetImsSmsSupportedOnImsServer
 ��������  : ��ȡIMS�������Ƿ�֧��IMS����
 �������  : ��
 �������  : ��
 �� �� ֵ  : IMS�������Ƿ�֧��IMS����:VOS_TRUE:֧�֣�VOS_FALSE:��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��22��
   ��    ��   : s00217060
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetImsSmsSupportedOnImsServer(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSupported);
}

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-22, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetImsSmsSendingFlg
 ��������  : ��ȡIMS�������ڷ��ͱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- IMS�����ڷ���
             VOS_FALSE -- ��IMS�����ڷ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��31��
   ��    ��   : y00245242
   �޸�����   : �½�����
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetImsSmsSendingFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSendingFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetImsSmsSendingFlg
 ��������  : ����IMS�������ڷ��ͱ�־
 �������  : ucImsSmsSendingFlg ���� IMS�������ڷ��ͱ�־
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��31��
   ��    ��   : y00245242
   �޸�����   : �½�����
*****************************************************************************/
VOS_VOID TAF_SPM_SetImsSmsSendingFlg(VOS_UINT8 ucImsSmsSendingFlg)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSendingFlg = ucImsSmsSendingFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetLastPsServiceStatus
 ��������  : ��ȡ�ϴ�PS����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ϴ�PS����״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��2��
   ��    ��   : y00245242
   �޸�����   : �½�����
*****************************************************************************/
TAF_SPM_SERVICE_STATUS_ENUM_UINT8 TAF_SPM_GetLastPsServiceStatus(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.enLastPsStatus);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetImsSmsSendingFlg
 ��������  : ���õ�ǰ��PS����״̬
 �������  : enCurrPsStatus ���� ��ǰ��PS����״̬
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��2��
   ��    ��   : y00245242
   �޸�����   : �½�����
*****************************************************************************/
VOS_VOID TAF_SPM_SetLastPsServiceStatus(TAF_SPM_SERVICE_STATUS_ENUM_UINT8 enCurrPsStatus)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.enLastPsStatus = enCurrPsStatus;
}
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, begin */
#endif /* end of FEATURE_IMS */
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, end */


/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-9-23, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_GetBufferMsgQueueAddr
 ��������  : ��ȡbuffer��Ϣ�����׵�ַ


 �������  : ��
 �������  : ��
 �� �� ֵ  : ����buffer��Ϣ�����׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU *TAF_SPM_GetBufferMsgQueueAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.stBufferMsgQueue);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitBufferCcMsgQueue
 ��������  : ��ʼ��CC ����message����

 �������  :
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitBufferCcMsgQueue(
    TAF_SPM_MSG_CC_QUEUE_STRU          *pstCcMsgQueue
)
{
    VOS_UINT8                           i;

    pstCcMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstCcMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstCcMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitBufferSmsMsgQueue
 ��������  : ��ʼ��SMS ����message����

 �������  :
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitBufferSmsMsgQueue(
    TAF_SPM_MSG_SMS_QUEUE_STRU              *pstSmsMsgQueue
)
{
    VOS_UINT8                           i;

    pstSmsMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_SMS_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstSmsMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstSmsMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitBufferSmsMsgQueue
 ��������  : ��ʼ��SS ����message����

 �������  :
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitBufferSsMsgQueue(
TAF_SPM_MSG_SS_QUEUE_STRU              *pstSsMsgQueue)
{
    VOS_UINT8                           i;

    pstSsMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_SS_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstSsMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstSsMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCcMsgQueueNum
 ��������  : ��ȡ��ǰ�����л���CC��Ϣ����Ŀ


 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰ�����л����CC��Ϣ��Ŀ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetCcMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetCcMsgQueueNum
 ��������  : ���¶����л����CC��Ϣ��Ŀ


 �������  : ucCacheMsgNum -- ��ǰ�������Ϣ��Ŀ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SetCcMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsCcMsgQueueFull
 ��������  : ����CC��Ϣqueue�Ƿ�Ϊfull


 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE -- queue full
             VOS_FALSE -- queue not full

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsCcMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_CC_MSG_QUEUE_NUM == TAF_SPM_GetCcMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue
 ��������  : ��CC��Ϣ��������л�ȡָ��λ�õĻ�����Ϣ��ַ

 �������  : ucIndex ���� ��Ϣ����
 �������  : ��
 �� �� ֵ  : ����CC��Ϣ���������ָ��λ�õ���Ϣ��ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_PutMessageToCcQueue
 ��������  : �����Ϣ��CC������Ϣ������

 �������  : ulEventType -- ��Ϣ�¼�����
             pstMsg -- ��Ϣ��ַ

 �������  : ��
 �� �� ֵ  : ���ػ�����Ϣ���
             VOS_TRUE  -- ��Ϣ�ѷŵ����������
             VOS_FALSE -- �����Ϣʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMessageToCcQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetCcMsgQueueNum();

    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetCcMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_SPM_FreeSpecificedIndexMessageInCcQueue
 ��������  : �ͷ�queue��ָ�������������Ϣ�����»�����Ϣ��Ŀ������ǰ�ƶ����л������Ϣ��
             �����������

 �������  : ucIndex ���� ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInCcQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetCcMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetCcMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSmsMsgQueueNum
 ��������  : ��ȡ��ǰ����SMS��Ϣ���е���Ϣ��Ŀ

 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ػ���SMS��Ϣ���е���Ϣ��Ŀ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetSmsMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetSmsMsgQueueNum
 ��������  : ���¶����л����SMS��Ϣ��Ŀ


 �������  : ucCacheMsgNum -- ��ǰ�������Ϣ��Ŀ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SetSmsMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsSmsMsgQueueFull
 ��������  : ����SMS��Ϣqueue�Ƿ�Ϊfull


 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE -- queue full
             VOS_FALSE -- queue not full

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmsMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SMS_MSG_QUEUE_NUM == TAF_SPM_GetSmsMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue
 ��������  : ��SMS��Ϣ��������л�ȡָ��λ�õĻ�����Ϣ��ַ

 �������  : ucIndex ���� ��Ϣ����
 �������  : ��
 �� �� ֵ  : ����SMS��Ϣ���������ָ��λ�õ���Ϣ��ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_PutMessageToSmsQueue
 ��������  : ����Ϣ��SMS������Ϣ������

 �������  : ulEventType -- ��Ϣ�¼�����
             pstMsg ���� ������Ϣ��ַ

 �������  : ��
 �� �� ֵ  : ���ػ�����Ϣ���
             VOS_TRUE  -- ��Ϣ�ѷŵ����������
             VOS_FALSE -- �����Ϣʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��2��14��
    ��    ��   : j00174725
    �޸�����   : TQE
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMessageToSmsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetSmsMsgQueueNum();

    if (ucCacheMsgNum >= TAF_SPM_MAX_SMS_MSG_QUEUE_NUM)
    {
        return VOS_FALSE;
    }

    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetSmsMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}


/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_SPM_FreeSpecificedIndexMessageInSmsQueue
 ��������  : �ͷ�queue��ָ�������Ļ�����Ϣ�����»�����Ϣ��Ŀ������ǰ�ƶ����л������Ϣ��
             �����������

 �������  : ucIndex ���� ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the first cached message in queue */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetSmsMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetSmsMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}
/*lint -restore */


/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSsMsgQueueNum
 ��������  : ��ȡ��ǰ����SS��Ϣ���е���Ϣ��Ŀ


 �������  : ��
 �������  :
 �� �� ֵ  : ���ػ���SS��Ϣ���е���Ϣ��Ŀ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetSsMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetSsMsgQueueNum
 ��������  : ���¶����л����SS��Ϣ��Ŀ


 �������  : ucCacheMsgNum -- ��ǰ�������Ϣ��Ŀ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SetSsMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SsMsgQueueIsFull
 ��������  : ����SS��Ϣqueue�Ƿ�Ϊfull


 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE -- queue full
             VOS_FALSE -- queue not full

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSsMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SS_MSG_QUEUE_NUM == TAF_SPM_GetSsMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue
 ��������  : ��SS��Ϣ��������л�ȡָ��λ�õĻ�����Ϣ��ַ

 �������  : ucIndex ���� ��Ϣ����
 �������  : ��
 �� �� ֵ  : ����SS��Ϣ���������ָ��λ�õ���Ϣ��ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_PutMessageToSsQueue
 ��������  : ����Ϣ��SS������Ϣ������

 �������  : ulEventType ���� ��Ϣ�¼�����
             pstMsg ���� ������Ϣ��ַ

 �������  : ��
 �� �� ֵ  : ���ػ�����Ϣ���
             VOS_TRUE  -- ��Ϣ�ѷŵ����������
             VOS_FALSE -- �����Ϣʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMessageToSsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetSsMsgQueueNum();

    if (ucCacheMsgNum >= TAF_SPM_MAX_SS_MSG_QUEUE_NUM)
    {
        return VOS_FALSE;
    }
    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetSsMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_SPM_FreeFirstCachedMessagesInSsQueue
 ��������  : �ͷ�queue��ָ�������Ļ�����Ϣ�����»�����Ϣ��Ŀ������ǰ�ƶ����л������Ϣ��
             �����������

 �������  : ucIndex ���� ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSsQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the first cached message in queue */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetSsMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetSsMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}
/* Added by y00245242 for VoLTE_PhaseII ��Ŀ, 2013-9-23, end */
/*lint -restore */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, begin */
#if (FEATURE_IMS == FEATURE_ON)
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, end */
/*****************************************************************************
 �� �� ��  : TAF_SPM_GetRedialMsgQueueAddr
 ��������  : ��ȡ�ز�������Ϣ�����׵�ַ


 �������  : ��
 �������  : ��
 �� �� ֵ  : ����buffer��Ϣ�����׵�ַ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_REDIAL_MSG_CTX_STRU *TAF_SPM_GetRedialMsgQueueAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.stRedialMsgQueue);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitCallRedialBuffer
 ��������  : ��ʼ���ز�����

 �������  : ��

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitCallRedialBuffer(
    TAF_SPM_CC_REDIAL_QUEUE_STRU       *pstCallRedialQueue
)
{
    PS_MEM_SET(pstCallRedialQueue, 0, sizeof(TAF_SPM_CC_REDIAL_QUEUE_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetNumberOfCallRedialBuffer
 ��������  : ��ȡ�����ز�������Ŀ

 �������  : ��

 �������  : ��
 �� �� ֵ  : ���غ����ز���������Ϣ��Ŀ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��25��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetNumberOfCallRedialBuffer(VOS_VOID)
{
    return (TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsCallRedialBufferEmpty
 ��������  : check�����ز������Ƿ�Ϊ��

 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- �ز�����Ϊ��
             VOS_FALSE -- �ز����治Ϊ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsCallRedialBufferEmpty(VOS_VOID)
{
    return (VOS_UINT8)((0 == TAF_SPM_GetNumberOfCallRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsCallRedialBufferFull
 ��������  : �������ز������Ƿ�Ϊ��

 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- �ز�����Ϊ��
             VOS_FALSE -- �ز����治��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsCallRedialBufferFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM == TAF_SPM_GetNumberOfCallRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetNumberOfCallRedialBuffer
 ��������  : ���ú����ز����������Ŀ


 �������  : ucCacheMsgNum ���� ������Ϣ��Ŀ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SetNumberOfCallRedialBuffer(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSpecificedIndexFromCallRedialBuffer
 ��������  : ��ȡָ�������ĺ����ز�����

 �������  : ucIndex ���� ��Ϣ���ز������е�������

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(VOS_UINT8 ucIndex)
{
    return &(TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_PutMsgIntoCallRedialBuffer
 ��������  : ��ȡָ�������ĺ����ز�����

 �������  : ulEventType ���� ��Ϣ�¼�����
             pstMsg      ���� ��Ϣ��ַ

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* �����Ϣ���ȣ�����Խ�� */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* ��ȡ�ز����л�����Ŀ */
    ucCacheMsgNum   = TAF_SPM_GetNumberOfCallRedialBuffer();

    /* ��ȡָ���ز������ַ */
    pstCacheMsgInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(ucCacheMsgNum);

    /* ������Ϣ */
    pstCacheMsgInfo->ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->aucEntryMsgBuffer[0]),
               pstMsg,
               pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetNumberOfCallRedialBuffer(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_FreeSpecificedIndexCallRedialBuffer
 ��������  : ���ָ�������ĺ����ز�����

 �������  : ucIndex ���� ��Ϣ���ز������е�������

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexCallRedialBuffer(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetNumberOfCallRedialBuffer(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_ENTRY_MSG_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_ENTRY_MSG_STRU));
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitSmsRedialBuffer
 ��������  : ��ʼ���ز�����

 �������  : ��

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_InitSmsRedialBuffer(
    TAF_SPM_SMS_REDIAL_QUEUE_STRU      *pstSmsRedialQueue
)
{
    PS_MEM_SET(pstSmsRedialQueue, 0, sizeof(TAF_SPM_SMS_REDIAL_QUEUE_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetNumberOfSmsRedialBuffer
 ��������  : ��ȡ�����ز�������Ŀ

 �������  : ��

 �������  : ��
 �� �� ֵ  : ���غ����ز���������Ϣ��Ŀ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetNumberOfSmsRedialBuffer(VOS_VOID)
{
    return (TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetNumberOfSmsRedialBuffer
 ��������  : ���ú����ز����������Ŀ


 �������  : ucCacheMsgNum ���� ������Ϣ��Ŀ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SetNumberOfSmsRedialBuffer(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsSmsRedialBufferEmpty
 ��������  : check�����ز������Ƿ�Ϊ��

 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- �ز�����Ϊ��
             VOS_FALSE -- �ز����治Ϊ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��12��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmsRedialBufferEmpty(VOS_VOID)
{
    return (VOS_UINT8)((0 == TAF_SPM_GetNumberOfSmsRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsSmsRedialBufferFull
 ��������  : �������ز������Ƿ�Ϊ��

 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- �ز�����Ϊ��
             VOS_FALSE -- �ز����治��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmsRedialBufferFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM == TAF_SPM_GetNumberOfSmsRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer
 ��������  : ��ȡָ�������ĺ����ز�����

 �������  : ucIndex ���� ��Ϣ���ز������е�������

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(VOS_UINT8 ucIndex)
{
    return &(TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_PutMsgIntoSmsRedialBuffer
 ��������  : ��ȡָ�������ĺ����ز�����

 �������  : ulEventType ���� ��Ϣ�¼�����
             pstMsg      ���� ��Ϣ��ַ

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* �����Ϣ���ȣ�����Խ�� */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* ��ȡ�ز����л�����Ŀ */
    ucCacheMsgNum   = TAF_SPM_GetNumberOfSmsRedialBuffer();
    if (ucCacheMsgNum >= TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM)
    {
        return VOS_FALSE;
    }
    /* ��ȡָ���ز������ַ */
    pstCacheMsgInfo = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(ucCacheMsgNum);

    /* ������Ϣ */
    pstCacheMsgInfo->ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->aucEntryMsgBuffer[0]),
               pstMsg,
               pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetNumberOfSmsRedialBuffer(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_FreeSpecificedIndexSmsRedialBuffer
 ��������  : ���ָ�������ĺ����ز�����

 �������  : ucIndex ���� ��Ϣ���ز������е�������

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetNumberOfSmsRedialBuffer();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetNumberOfSmsRedialBuffer(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_ENTRY_MSG_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_ENTRY_MSG_STRU));
    }
}

/*lint -restore */

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetCallEconfInfoAddr
 ��������  : ��ȡ��ǿ�Ͷ෽ͨ����Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_SPM_CALL_ECONF_INFO_STRU  �������м�¼��ǿ�Ͷ෽ͨ����Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SPM_CALL_ECONF_INFO_STRU* TAF_SPM_GetCallEconfInfoAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stEconfInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitEconfInfo
 ��������  : ��ʼ��Call Econf ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_SPM_InitEconfInfo(VOS_VOID)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstCallEconfAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstCallEconfAddr = TAF_SPM_GetCallEconfInfoAddr();

    PS_MEM_SET(pstCallEconfAddr, 0x0, sizeof(TAF_SPM_CALL_ECONF_INFO_STRU));

    for (ulIndex = 0; ulIndex < TAF_CALL_MAX_ECONF_CALLED_NUM; ulIndex++)
    {
        pstCallEconfAddr->astEconfCheckInfo[ulIndex].enCheckRslt    = TAF_CS_CAUSE_SUCCESS;
        pstCallEconfAddr->astEconfCheckInfo[ulIndex].ulCheckCnfFlag = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg
 ��������  : ��ȡ��ǰ��Ϣ��EventType
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg(VOS_VOID)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg   = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    return TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_SetEcallHangUpImsFlag
 ��������  : �����Ƿ��·����ͷ�IMS call
 �������  : ucFlag
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��04��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SPM_SetEcallHangUpImsFlag(
    VOS_UINT8                           ucFlag
)
{
    TAF_SPM_GetSpmCtxAddr()->ucEcallHangUpImsFlag = ucFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_GetEcallHangUpImsFlag
 ��������  : ��ȡ�Ƿ��·����ͷ�IMS call
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��04��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetEcallHangUpImsFlag(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->ucEcallHangUpImsFlag;
}




#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

