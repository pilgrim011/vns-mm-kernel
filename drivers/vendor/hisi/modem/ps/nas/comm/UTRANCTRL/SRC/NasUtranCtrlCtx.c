/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NASUTRANCTRLCtx.c
  �� �� ��   : ����
  ��    ��   : w00167002
  ��������   : 2012��7��12��
  ����޸�   :
  ��������   : NASUTRANCTRLCtx.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��7��12��
    ��    ��   : w00167002
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "PsTypeDef.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcMain.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasComm.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmMainTbl.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#include "NasUtranCtrlMain.h"
#include "NasUtranCtrlMntn.h"
#include "NasMmlLib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_CTX_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* ��������ģ�鹲�õ�CTX */
NAS_UTRANCTRL_CTX_STRU                    g_stNasUtranCtrlCtx;
#endif

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetUtranCtrlCtx
 ��������  : ��ȡ��ǰMMAGENT��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰMMAGENT��CTX
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_UTRANCTRL_CTX_STRU* NAS_UTRANCTRL_GetUtranCtrlCtx( VOS_VOID )
{
    return &(g_stNasUtranCtrlCtx);
}

/*****************************************************************************
�� �� ��  : NAS_UTRANCTRL_InitCustomCfgInfo
��������  : ��ʼ���ͻ���������
�������  : ��
�������  : pstCustomCfg:��ʼ���ͻ���������
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

3.��    ��   : 2013��11��18��
  ��    ��   : w00167002
  �޸�����   : DTS2013112006986:������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                TD�²�����SMC���̡�
               Ĭ����Ҫ����SMC���̡� 
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitCustomCfgInfo(
    NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU   *pstCustomCfg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch;

    pstUtranModeAutoSwitch                      = &(pstCustomCfg->stUtranModeAutoSwitch);

    /* Ĭ�ϳ�ʼ��ΪTDDģʽ */
    pstCustomCfg->enCurrUtranMode               = NAS_UTRANCTRL_UTRAN_MODE_TDD;
    pstCustomCfg->enPreUtranMode                = NAS_UTRANCTRL_UTRAN_MODE_BUTT;

    pstCustomCfg->ucIsUtranTddCsSmcNeeded       = VOS_TRUE;
    pstCustomCfg->ucIsUtranTddPsSmcNeeded       = VOS_TRUE;

    pstCustomCfg->enCurUtranSwitchMode          = NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY;
    pstUtranModeAutoSwitch->ucUtranSwitchMode   = NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY;

    /* Ĭ���й������б����Ϊ0�� */
    pstUtranModeAutoSwitch->ucTdMccListNum      = 0;

    /* Ĭ��IMSI�е������б����Ϊ0�� */
    pstUtranModeAutoSwitch->ucImsiPlmnListNum   = 0;

    /* ��ʼ�������ֶ� */
    PS_MEM_SET( pstUtranModeAutoSwitch->aucReserve,
                0,
                sizeof(pstUtranModeAutoSwitch->aucReserve) );

    /* ��ʼ��TD��������б� */
    PS_MEM_SET( pstUtranModeAutoSwitch->aulTdMccList,
                0,
                sizeof(pstUtranModeAutoSwitch->aulTdMccList) );

    /* ��ʼ��IMSI PLMN LIST�����б� */
    PS_MEM_SET( pstUtranModeAutoSwitch->astImsiPlmnList,
                0,
                sizeof(pstUtranModeAutoSwitch->astImsiPlmnList) );
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitMsCfgCtx
 ��������  : ��ʼ��MML_CTX���ֻ����������Ϣ
 �������  : pstMsCfgInfo:�ֻ�������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitMsCfgCtx(
    NAS_UTRANCTRL_MS_CFG_INFO_STRU       *pstMsCfgInfo
)
{

    NAS_UTRANCTRL_InitCustomCfgInfo(&(pstMsCfgInfo->stCustomCfg));
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitCurrFsmCtx
 ��������  : ��ʼ����ǰ״̬��������
 �������  : ��
 �������  : pstCurrFsmCtx:��ǰ״̬����������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitCurrFsmCtx(
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                = NAS_UTRANCTRL_FSM_MAIN;
    pstCurrFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                = NAS_UTRANCTRL_MAIN_STA_INIT;
    pstCurrFsmCtx->stEntryMsg.ulEventType = 0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitMainCtrlInfo
 ��������  : ��ʼ����ǰUTRANCTRLģ���������Ϣ
 �������  : ��
 �������  : pstMainCtrl:��ǰUTRANCTRLģ���������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��14��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��14��
   ��    ��   : w00176964
   �޸�����   : �޸ĺ�����
 3.��    ��   : 2014��11��25��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitMainCtrlInfo(
    NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU  *pstMainCtrl
)
{
    /* ��ʼ����ǰ������Ϣ */
    pstMainCtrl->ucReplaceMmcMsgFlg     = VOS_FALSE;

    PS_MEM_SET( pstMainCtrl->aucReserve,
                (VOS_UINT8)0x00,
                sizeof(pstMainCtrl->aucReserve) );


    PS_MEM_SET( &(pstMainCtrl->stBufferUtranSndMmcMsg),
                (VOS_UINT8)0x00,
                sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU) );

    PS_MEM_SET( &(pstMainCtrl->stBufferMmcSndUtranMsg),
                (VOS_UINT8)0x00,
                sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU) );

    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx
 ��������  : ��ʼ��������Ϣ����������
 �������  : ��
 �������  : pstCurrFsmCtx:��ǰ������Ϣ����������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx(
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferEntryMsgQueue
)
{
    /* ��ʼ��������Ϣ���������� */
    pstBufferEntryMsgQueue->ucCurrIndex   = 0;
    pstBufferEntryMsgQueue->ucCacheMsgNum = 0;

    PS_MEM_SET( pstBufferEntryMsgQueue->aucReserve,
                (VOS_UINT8)0x00,
                sizeof(pstBufferEntryMsgQueue->aucReserve) );


    PS_MEM_SET( pstBufferEntryMsgQueue->astMsgQueue,
                (VOS_UINT8)0x00,
                sizeof(pstBufferEntryMsgQueue->astMsgQueue) );

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx
 ��������  : ��ʼ����������������
 �������  : ��
 �������  : pstPlmnSearchCtrl:�������ƽṹ������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx(
    NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU       *pstPlmnSearchCtrl
)
{
    /* ��ʼ���������ƽṹ������ */
    pstPlmnSearchCtrl->ucSearchedSpecTdMccFlg = VOS_FALSE;

    PS_MEM_SET( pstPlmnSearchCtrl->aucReserve,
                (VOS_UINT8)0x00,
                sizeof(pstPlmnSearchCtrl->aucReserve) );

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitMaintainInfo
 ��������  : ��ʼ��UTRANCTRL_CTX�п�ά�ɲⲿ��
 �������  : pstMaintainInfo:��ά�ɲ�ȫ�ֱ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitMaintainInfo(
    NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8                  enInitType,
    NAS_UTRANCTRL_MAINTAIN_CTX_STRU                        *pstMaintainInfo
)
{
    /* �ϵ翪��ʱ����Ҫ��ʼ�����±��� */
    if (NAS_UTRANCTRL_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* ��ʼĬ�ϲ�����PC�ط���Ϣ */
    pstMaintainInfo->stUeMaintainInfo.ucUeSndPcRecurFlg    = VOS_FALSE;

    /* ��ʼ�������ֶ�Ϊ0 */
    PS_MEM_SET( pstMaintainInfo->stUeMaintainInfo.aucRsv3,
                (VOS_UINT8)0X00,
                sizeof(pstMaintainInfo->stUeMaintainInfo.aucRsv3) );

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SwitchCurrFsmCtx
 ��������  : �л���ǰ��״̬����������
 �������  : ��
 �������  : enNewFsmId:�µ�״̬������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��6��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SwitchCurrFsmCtx(
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enNewFsmId
)
{
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsmCtx;
    NAS_UTRANCTRL_CTX_STRU             *pstCtx;

    pstCtx          = NAS_UTRANCTRL_GetUtranCtrlCtx();
    pstCurFsmCtx    = &(pstCtx->stCurFsm);

    if (VOS_NULL_PTR == pstCurFsmCtx->pstFsmDesc)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SwitchCurrFsmCtx:Invalid pstFsmDesc");
    }

    switch (enNewFsmId)
    {
        case NAS_UTRANCTRL_FSM_MAIN:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetMainFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_MAIN_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_SWITCH_ON:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetSwitchOnFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_SWITCH_ON_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_POWER_OFF:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetPowerOffFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_POWER_OFF_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_PLMN_SELECTION:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_SYSCFG:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetSysCfgFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_SYSCFG_STA_INIT;
            break;

        case NAS_UTRANCTRL_FSM_MODE_CHANGE:
            pstCurFsmCtx->enFsmId                = enNewFsmId;
            pstCurFsmCtx->pstFsmDesc             = NAS_UTRANCTRL_GetModeChangeFsmDescAddr();
            pstCurFsmCtx->ulState                = NAS_UTRANCTRL_MODE_CHANGE_STA_INIT;
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SwitchCurrFsmCtx:Invalid Fsm Id");

            return;
    }

    /* ��ʼ��UTRANCTRL״̬�������� */
    pstCurFsmCtx->pstFsmDesc->pfInitHandle();

    /* ��ά�ɲ�״̬����Ϣ��ӡ */
    NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo();

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SaveCurEntryMsg
 ��������  : ���浱ǰ״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
              pstMsg             :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��30��
    ��    ��   : w00167002
    �޸�����   : ʹ��NAS_UTRANCTRL_ENTRY_MSG_STRU����
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰUTRANCTRLģ��״̬�������Ϣ�Ļ�������ַ */
    pstEntryMsg                 = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
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
 �� �� ��  : NAS_UTRANCTRL_FSM_SetCurrState
 ��������  : ���õ�ǰ��ҪǨ�Ƶ�״̬
 �������  : ulCurrState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = NAS_UTRANCTRL_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /* ��ά�ɲ�״̬����Ϣ��ӡ */
    NAS_UTRANCTRL_SndOmUtranCtrlFsmInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_FSM_GetCurrState
 ��������  : ��ȡ��ǰ��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulCurrState:��ǰǨ�Ƶ�״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_FSM_GetCurrState(VOS_VOID)
{
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬����Ϣ */
    pstCurFsm                   = NAS_UTRANCTRL_GetCurFsmAddr();

    /* ��ȡ��ǰ״̬ */
    return (pstCurFsm->ulState);
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitCtx
 ��������  : ������ʼ��NAS_UTRANCTRL��ʱCTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��7��
   ��    ��   : w00176964
   �޸�����   : �޸�ע��״̬��������
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_InitCtx(
    VOS_UINT8                           ucInitType
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    NAS_UTRANCTRL_CTX_STRU             *pstCtx;

    pstCtx = NAS_UTRANCTRL_GetUtranCtrlCtx();

    /* ��ʼ��MS������Ϣ */
    NAS_UTRANCTRL_InitMsCfgCtx(&(pstCtx->stMsCfgInfo));

    /* ��ʼ��UTRANCTRL��ǰ״̬�������� */
    NAS_UTRANCTRL_InitCurrFsmCtx(&(pstCtx->stCurFsm));


    /* ��ʼ��UTRANCTRLģ��������Ϣ */
    NAS_UTRANCTRL_InitMainCtrlInfo(&(pstCtx->stMainCtrlInfo));

    /* ��ʼ��UTRANCTRL״̬��������Ϣ���������� */
    NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx(&(pstCtx->stBufferEntryMsgQueue));

    /* ��ʼ��UTRANCTRL״̬���������������� */
    NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx(&(pstCtx->stPlmnSearchCtrl));

    /* ��ʼ����ά�ɲ���Ϣ */
    NAS_UTRANCTRL_InitMaintainInfo( ucInitType,
                                    &(pstCtx->stMaintainInfo));

    /* ״̬����ĳ�ʼ�� */
    NAS_UTRANCTRL_RegFsm();

#endif
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurrUtranMode
 ��������  : ��ȡ��ǰ��UTRANģʽ,����ⲿģ�������Ҫȷ��Ϊפ��״̬,������ܻ᲻׼ȷ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8:��ǰ��UTRANģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �½�����
 2.��    ��   : 2012��8��14��
   ��    ��   : w00176964
   �޸�����   : ����UTRAN���л�ģʽ��ȡ����ģʽ
 3.��    ��   : 2012��12��25��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:ƽ̨���뼼������ֻ֧��W/TD�е�һ��ʱ��
                UtranModeΪTDD��FDD���䣬���߶���֧��ʱΪBUTT
*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetCurrUtranMode(VOS_VOID)
{
    /* !!��ȡ��ǰ��UTRANģʽ,����ⲿģ�������Ҫȷ��Ϊפ��״̬,������ܻ᲻׼ȷ */
    
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();
#endif

    /* ƽ̨��W��TD����֧��ʱ��UtranModeΪBUTT */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportUtran())
    {
        return NAS_UTRANCTRL_UTRAN_MODE_BUTT;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    /* ƽ̨���뼼������ֻ֧��Wʱ��UtranModeΪFDD */
    if (VOS_FALSE == ulSupportTddFlg)
    {
        return NAS_UTRANCTRL_UTRAN_MODE_FDD;
    }

    /* ƽ̨���뼼������ֻ֧��TDʱ��UtranModeΪTDD */
    if (VOS_FALSE == ulSupportFddFlg)
    {
        return NAS_UTRANCTRL_UTRAN_MODE_TDD;
    }

    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return NAS_UTRANCTRL_UTRAN_MODE_FDD;
    }

    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return NAS_UTRANCTRL_UTRAN_MODE_TDD;
    }

    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurrUtranMode;
#else
    return NAS_UTRANCTRL_UTRAN_MODE_FDD;
#endif
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetRatModeBasedOnUtranMode
 ��������  : ����ǰ��utran modeֵת������Ӧ�Ľ��뼼��
 �������  : NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
 �������  : ��
 �� �� ֵ  : VOS_RATMODE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��2��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_RATMODE_ENUM_UINT32 NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    VOS_RATMODE_ENUM_UINT32             enRatMode;

    enRatMode = VOS_RATMODE_BUTT;

    switch (enUtranMode)
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            enRatMode = VOS_RATMODE_WCDMA;
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            enRatMode = VOS_RATMODE_TDS;
            break;
#endif

        default:
            enRatMode = VOS_RATMODE_BUTT;
            break;
    }

    return enRatMode;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg
 ��������  : ��ȡUTRANCTRL�б����UTRAN TDDģʽ���Ƿ���Ҫ���CS SMC����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: UTRAN TDDģʽ����Ҫ���CS SMC����
             VOS_FALSE:UTRAN TDDģʽ�²���Ҫ���CS SMC����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��18��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
   
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddCsSmcNeeded);

#else

    /* ƽ̨������TDD���Ժ�ʱ������Ҫ����SMC */
    return VOS_TRUE;

#endif    
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg
 ��������  : ��ȡUTRANCTRL�б����UTRAN TDDģʽ���Ƿ���Ҫ���PS SMC����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: UTRAN TDDģʽ����Ҫ���PS SMC����
             VOS_FALSE:UTRAN TDDģʽ�²���Ҫ���PS SMC����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��18��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
   
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddPsSmcNeeded);

#else

    /* ƽ̨������TDD���Ժ�ʱ������Ҫ����SMC */
    return VOS_TRUE;

#endif    
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_IsUtranCsSmcNeeded
 ��������  : ��ȡUTRANCTRL�б����UTRAN TDDģʽ���Ƿ���Ҫ���CS SMC����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: UTRAN ģʽ����Ҫ���CS SMC����
             VOS_FALSE:UTRAN ģʽ�²���Ҫ���CS SMC����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��18��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_IsUtranCsSmcNeeded(VOS_VOID)
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;

    ucIsUtranTddCsSmcNeeded             = NAS_UTRANCTRL_GetUtranTddCsSmcNeededFlg();
    
    /* ��ǰ����UTRANģʽ�£�����ҪUTRAN SMC��� */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* ��ǰ��TDDģʽ�£����û����ò���ҪCS SMC���򷵻ز���ҪSMC��� */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (VOS_FALSE                    == ucIsUtranTddCsSmcNeeded) )
    {
        return VOS_FALSE;
    }
    
    /* ��ǰ��FDDģʽ�»���TDDʱ��Ҫ���SMCʱ������Ҫ����SMC */
    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_IsUtranPsSmcNeeded
 ��������  : ��ȡUTRANCTRL�б����UTRAN TDDģʽ���Ƿ���Ҫ���PS SMC����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: UTRAN ģʽ����Ҫ���PS SMC����
             VOS_FALSE:UTRAN ģʽ�²���Ҫ���PS SMC����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��18��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_IsUtranPsSmcNeeded(VOS_VOID)
{
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;

    ucIsUtranTddPsSmcNeeded             = NAS_UTRANCTRL_GetUtranTddPsSmcNeededFlg();
    
    /* ��ǰ����UTRANģʽ�£�����ҪUTRAN SMC��� */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* ��ǰ��TDDģʽ�£����û����ò���ҪCS SMC���򷵻ز���ҪSMC��� */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (VOS_FALSE                    == ucIsUtranTddPsSmcNeeded) )
    {
        return VOS_FALSE;
    }
    
    /* ��ǰ��FDDģʽ�»���TDDʱ��Ҫ���SMCʱ������Ҫ����SMC */
    return VOS_TRUE;

}


#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetCurrUtranMode
 ��������  : ����UTRANCTRL�б����UTRANģʽ
 �������  : UTRANģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetCurrUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurrUtranMode = enUtranMode;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg
 ��������  : ����UTRANCTRL�б����UTRAN TDDģʽ���Ƿ���Ҫ���CS SMC����
 �������  : ucIsUtranTddSmcNeeded
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��18��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddCsSmcNeeded = ucIsUtranTddCsSmcNeeded;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg
 ��������  : ����UTRANCTRL�б����UTRAN TDDģʽ���Ƿ���Ҫ���PS SMC����
 �������  : ucIsUtranTddSmcNeeded
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��18��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.ucIsUtranTddPsSmcNeeded = ucIsUtranTddPsSmcNeeded;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag
 ��������  : ����UTRANCTRLģ�����Ƿ�Ϊ������������
 �������  : ucSwitchOnPlmnSearchFlag - �Ƿ��ǿ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��25��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(
    VOS_UINT8                           ucSwitchOnPlmnSearchFlag
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucSwitchOnPlmnSearchFlag = ucSwitchOnPlmnSearchFlag;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag
 ��������  : ��ȡUTRANCTRLģ�����Ƿ�Ϊ��������������ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����������ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��25��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag(VOS_VOID)
{
    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucSwitchOnPlmnSearchFlag;
}




/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetReplaceMmcMsgFlg
 ��������  : ����UTRANCTRLģ�����滻MMC��Ϣ�ı��
 �������  : ucReplaceFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��8��
   ��    ��   : w00176964
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetReplaceMmcMsgFlg(
    VOS_UINT8                           ucReplaceFlg
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucReplaceMmcMsgFlg = ucReplaceFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetReplaceMmcMsgFlg
 ��������  : ��ȡUTRANCTRLģ�����滻MMC��Ϣ�ı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : UTRANCTRLģ�����滻MMC��Ϣ�ı��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��8��
   ��    ��   : w00176964
   �޸�����   : �½�����

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetReplaceMmcMsgFlg(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.ucReplaceMmcMsgFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetPreUtranMode
 ��������  : ��ȡUTRANCTRL�б�����ϴη���RRC��UTRANģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : UTRANCTRL�б����UTRANģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetPreUtranMode(VOS_VOID)
{
    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enPreUtranMode;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetPreUtranMode
 ��������  : ����UTRANCTRL�б�����ϴη���RRC��UTRANģʽ
 �������  : UTRANģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : w00167002
   �޸�����   : �½�����

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetPreUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enPreUtranMode = enUtranMode;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurFsmAddr
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
NAS_UTRANCTRL_FSM_CTX_STRU* NAS_UTRANCTRL_GetCurFsmAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurFsmDesc
 ��������  : ��ȡ��ǰ״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* NAS_UTRANCTRL_GetCurFsmDesc(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurrEntryMsgAddr
 ��������  : ��ȡ��ǰ״̬�������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetCurrEntryMsgAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurrFsmId
 ��������  : ��ȡ��ǰ״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_UTRANCTRL_FSM_ID_ENUM_UINT32 NAS_UTRANCTRL_GetCurrFsmId(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.enFsmId);
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCachMsgBufferAddr
 ��������  : ��ȡ��ǰ�Ļ�����Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS UTRANCTRL������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��7��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_UTRANCTRL_MSG_QUEUE_STRU* NAS_UTRANCTRL_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stBufferEntryMsgQueue);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_ClearCacheMsg
 ��������  : ���ָ���Ļ�����Ϣ
 �������  : ulEventType:������󻺴����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��05��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferMsgQueue   = VOS_NULL_PTR;

    pstBufferMsgQueue = NAS_UTRANCTRL_GetCachMsgBufferAddr();
    cCachePos         = -1;

    /* ���ҵ���Ҫ������Ļ��� */
    for ( i = 0 ; i < pstBufferMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstBufferMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstBufferMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
        }
    }

    /* δ�ҵ�����Ϣ����ֱ�ӷ��� */
    if ( -1 == cCachePos )
    {
        return;
    }

    /* Ϊ��֤�����ȳ�,��Ҫ���������Ϣ�Ƶ�ǰ�� */
    for ( i = cCachePos ; i < (pstBufferMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY��Ϣ���� */
        PS_MEM_CPY(&(pstBufferMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstBufferMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU));

    }

    /* �����������һ */
    pstBufferMsgQueue->ucCacheMsgNum--;

    /* ��ά�ɲ⻺�������Ϣ��ӡ */
    NAS_UTRANCTRL_SndOmBufferQueueMsg();

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitCachBufferMsgQueue
 ��������  : ��ʼ���ⲿ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��8��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_InitCachBufferMsgQueue( VOS_VOID )
{
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferMsgQueue;

    pstBufferMsgQueue                   = NAS_UTRANCTRL_GetCachMsgBufferAddr();

    /* �������Լ�����ĸ������� */
    pstBufferMsgQueue->ucCurrIndex      = 0;
    pstBufferMsgQueue->ucCacheMsgNum    = 0;

    /* ����Ϣ������� */
    PS_MEM_SET(pstBufferMsgQueue->aucReserve, 0X0, sizeof(pstBufferMsgQueue->aucReserve));
    PS_MEM_SET(pstBufferMsgQueue->astMsgQueue, 0X0, sizeof(NAS_UTRANCTRL_CACH_MSG_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetNextCachBufferMsg
 ��������  : ��ȡ��һ�����õ��ⲿ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ڲ���Ϣ���е�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��8��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID* NAS_UTRANCTRL_GetNextCachBufferMsg( VOS_VOID )
{
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferMsgQueue;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstMsgEntry;

    pstBufferMsgQueue = NAS_UTRANCTRL_GetCachMsgBufferAddr();

    /* �����Ϣ��ȡ�꣬����VOS_NULL_PTR */
    if ( pstBufferMsgQueue->ucCacheMsgNum <= pstBufferMsgQueue->ucCurrIndex)
    {
        NAS_UTRANCTRL_InitCachBufferMsgQueue();

        return VOS_NULL_PTR;
    }

    pstMsgEntry = &(pstBufferMsgQueue->astMsgQueue[pstBufferMsgQueue->ucCurrIndex].stMsgEntry);

    /* ָ����һ��������ⲿ��Ϣ */
    pstBufferMsgQueue->ucCurrIndex++;

    /* ��ά�ɲ⻺�������Ϣ��ӡ */
    NAS_UTRANCTRL_SndOmBufferQueueMsg();

    /* ����ȡ�û�����ⲿ��Ϣ */
    return (VOS_VOID*)(pstMsgEntry->aucEntryMsgBuffer);

}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SaveCacheMsgInMsgQueue
 ��������  : ��������Ϣ����Ļ����ڴ����
 �������  : ulEventType:��ϢID+PID
             pMsg      :��Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��15��
    ��    ��   : w00167002
    �޸�����   : �����Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ��

*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_UTRANCTRL_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= NAS_UTRANCTRL_MAX_MSG_QUEUE_NUM )
    {
        /* ��ά�ɲ⻺�������Ϣ��ӡ */
        NAS_UTRANCTRL_SndOmBufferQueueMsg();

        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveCacheMsgInMsgQueue:No Empty buffer");

        return ;
    }

    /* ��Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ�� */
    if ( (pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH) > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveCacheMsgInMsgQueue:Msg too big to save ");
        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    /* ��ά���ɲ⻺�������Ϣ��ӡ */
    NAS_UTRANCTRL_SndOmBufferQueueMsg();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurrFsmEventType
 ��������  : ��ȡ��ǰ״̬������Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��19��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetCurrFsmEventType(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.stEntryMsg.ulEventType);
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg
 ��������  : ���滺��ķ��͸�W/TD��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��15��
    ��    ��   : w00167002
    �޸�����   : �����Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ��
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����ķ��͸�UTRAN��������Ϣ�Ļ�������ַ */
    pstEntryMsg                 =   NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr();
    pstMsgHeader                =   (MSG_HEADER_STRU*)pstMsg;

    /* ����ǿ���Ϣ */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ��Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ�� */
    if ( ulLen > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg:Msg too big to save ");
        return ;
    }

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg
 ��������  : ��ջ���ķ��͸�UTRAN��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg(VOS_VOID)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;

    /* ��õ�ǰ����ķ��͸�UTRAN��������Ϣ�Ļ�������ַ */
    pstEntryMsg                 =   NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr();

     /* ��ն�Ӧ�Ļ����� */
    PS_MEM_SET(pstEntryMsg, (VOS_UINT8)0x00, sizeof(NAS_UTRANCTRL_ENTRY_MSG_STRU));
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr
 ��������  : ��ȡ״̬������ķ��͸�UTRAN��������Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ķ��͸�UTRAN��������Ϣ��ַ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.stBufferMmcSndUtranMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetBufferedPlmnSearchReqType
 ��������  : ��ȡ״̬�������������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-15
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012-08-24
    ��    ��   : W00167002
    �޸�����   : ȡ�������Ϣ����PID��WUEPS_PID_MMC��������WRR
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(VOS_VOID)
{
    RRMM_PLMN_SEARCH_REQ_STRU           stPlmnSearchReqMsg;
    VOS_UINT32                          ulEventType;

    ulEventType = NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->ulEventType;


    /* ���ڻ����UTRAN��������Ϣ�������ָ������������Ϣ��˵�����쳣 */
    if (ulEventType != NAS_BuildEventType(WUEPS_PID_MMC, RRMM_PLMN_SEARCH_REQ))
    {
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_UTRANCTRL_GetBufferedPlmnSearchReqType Invalid Event type!" );

        return RRC_PLMN_SEARCH_TYPE_BUTT;
    }

    stPlmnSearchReqMsg = *(RRMM_PLMN_SEARCH_REQ_STRU*)(NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);

    return stPlmnSearchReqMsg.ulSearchType;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetSearchedSpecTdMccFlg
 ��������  : ��ȡ�ѵ�ָ��td��MCC�ı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:�ѵ�ָ��TD��MCC�ı��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetSearchedSpecTdMccFlg(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stPlmnSearchCtrl.ucSearchedSpecTdMccFlg);
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetSpecTdMccListNum
 ��������  : ��ȡ���Ƶ�TD�������б����
 �������  : ��
 �������  : ���ƵĹ������б����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   NAS_UTRANCTRL_GetSpecTdMccListNum(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.stUtranModeAutoSwitch.ucTdMccListNum);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetSpecTdMccList
 ��������  : ��ȡ���Ƶ�TD�������б�
 �������  : ��
 �������  : pulMcc ���Ƶ�TD�������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32* NAS_UTRANCTRL_GetSpecTdMccList(VOS_VOID)
{
    return NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.stUtranModeAutoSwitch.aulTdMccList;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetCurUtranSwitchMode
 ��������  : ���õ�ǰUTRAN���л�ģʽ
 �������  : ucSwitchMode:UTRAND���л�ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012-08-10
    ��    ��   : W00176964
    �޸�����   : �޸ĺ�����
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SetCurUtranSwitchMode(
    VOS_UINT8                               ucSwitchMode
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurUtranSwitchMode) = ucSwitchMode;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetUePcRecurFlg
 ��������  : ��ȡ��ǰ��UE���PC�طű�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��UE���PC�طű�־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��08��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetUePcRecurFlg(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetUePcRecurFlg
 ��������  : ����UE��PC�ط�ʹ�ܱ�־
 �������  : ucUePcRecurFlg: UE���PC�طű�־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��08��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
)
{
    NAS_UTRANCTRL_GetUtranCtrlCtx()->stMaintainInfo.stUeMaintainInfo.ucUeSndPcRecurFlg = ucUePcRecurFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetCurUtranSwitchMode
 ��������  : ��ȡUTRAN���л�ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:UTRAN���л�ģʽ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012-08-14
    ��    ��   : W00176964
    �޸�����   : �޸ĺ�����
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetCurUtranSwitchMode(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.enCurUtranSwitchMode);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmCtx_Main
 ��������  : ��ʼ����״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Main(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmCtx_SwitchOn
 ��������  : ��ʼ������״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_SwitchOn(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmCtx_PowerOff
 ��������  : ��ʼ���ػ�״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PowerOff(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmCtx_PlmnSelection
 ��������  : ��ʼ������״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PlmnSelection(VOS_VOID)
{
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_FALSE);

    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmCtx_Syscfg
 ��������  : ��ʼ��syscfg״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Syscfg(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_InitFsmCtx_ModeChange
 ��������  : ��ʼ��ģʽ�ı�״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_ModeChange(VOS_VOID)
{
    NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange();
    return;
}

/* ����״̬�������Ĳ������� */
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetAbortFlg_PlmnSelection
 ��������  : ����״̬����ϱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:״̬����ϱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(
    VOS_UINT8       ucAbortFlg
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg) = ucAbortFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetAbortFlg_PlmnSelection
 ��������  : ��ȡ״̬����ϱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:״̬����ϱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetAbortFlg_PlmnSelection(VOS_VOID)
{
    return  (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection
 ��������  : ����״̬����ϱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:״̬����ϱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-12-17
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(
    VOS_UINT8                           ucRcvMmcAbortFsmReqMsgFlg
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRcvMmcAbortFsmReqMsgFlg) = ucRcvMmcAbortFsmReqMsgFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection
 ��������  : ��ȡ״̬����ϱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8:״̬����ϱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015-12-17
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_VOID)
{
    return  (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRcvMmcAbortFsmReqMsgFlg);
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg
 ��������  : ����UTRANģ�黺���W/TD����MMC����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��15��
    ��    ��   : w00167002
    �޸�����   : �����Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ��
*****************************************************************************/
VOS_VOID NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����Ļ�������ַ */
    pstEntryMsg                         = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstMsgHeader                        = (MSG_HEADER_STRU *)pstMsg;

    /* ����ǿ���Ϣ */
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg Entry Message Pointer is NULL!" );

        return;
    }


    /* ���滺��ǰ����»��� */
    PS_MEM_SET(pstEntryMsg->aucEntryMsgBuffer, (VOS_UINT8)0x00, sizeof(pstEntryMsg->aucEntryMsgBuffer) );

    ulLen                               = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ��Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ�� */
    if ( ulLen > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg:Msg too big to save! ");
        return ;
    }

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType            = ulEventType;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr
 ��������  : ��ȡUTRANģ�黺���W/TD����MMC����Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : UTRANģ�黺���W/TD����MMC����Ϣ��ַ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stMainCtrlInfo.stBufferUtranSndMmcMsg);
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetUtranModeAutoSwtich
 ��������  : ��ȡ�洢��ǰUTRAN MODE�Զ��л���NVIM����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��9��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU* NAS_UTRANCTRL_GetUtranModeAutoSwtich(VOS_VOID)
{
    return &(NAS_UTRANCTRL_GetUtranCtrlCtx()->stMsCfgInfo.stCustomCfg.stUtranModeAutoSwitch);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange
 ��������  : ��ȡ�Ƿ��Ѿ��յ�Gass��ģʽ����ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE����Ҫ�ȴ���ģ��ģʽ����ظ�
              VOS_FALSE������Ҫ�ȴ���ģ��ģʽ����ظ�
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-8-8
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange(VOS_VOID)
{
    return (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange
 ��������  : �����Ƿ���Ҫ�ȴ���ģ��ģʽ����ظ����
 �������  : ucWaitSlaveModeUtranModeCnfFlg:�Ƿ���Ҫ�ȴ���ģ��ģʽ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-8-8
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitSlaveModeUtranModeCnfFlg
)
{
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg) |= ucWaitSlaveModeUtranModeCnfFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange
 ��������  : ����ȴ�ģʽ����ظ���־
 �������  : ucWaitUtranModeCnfFlg:�Ƿ���Ҫ�ȴ�ģʽ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-8-8
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitUtranModeCnfFlg
)
{
    /* �����ǰ״̬������MODE CHANGE״̬�� */
    if (NAS_UTRANCTRL_FSM_MODE_CHANGE != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange:ENTERED");
    }

    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg) &= ~ucWaitUtranModeCnfFlg;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_ClearAllWaitUtranModeCnfFlg_ModeChange
 ��������  : ����ȴ�ģʽ����ظ���־
 �������  : ucWaitUtranModeCnfFlg:�Ƿ���Ҫ�ȴ�ģʽ����ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-8-8
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange(VOS_VOID)
{
    /* �����ǰ״̬������MODE CHANGE״̬�� */
    if (NAS_UTRANCTRL_FSM_MODE_CHANGE != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ClearAllWaitUtranModeCnfFlg_ModeChange:ENTERED");
    }

    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stCurFsm.unFsmCtx.stModeChangeCtx.ucWaitSlaveModeUtranModeCnfFlg) = NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_NULL;

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_SetSearchedSpecTdMccFlg
 ��������  : ���õ�ǰ�ѵ���ָ��TD��MCC�ı��
 �������  : ucFlg:��ǰ�ѵ���ָ��TD��MCC�ı��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-6
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(
    VOS_UINT8       ucFlg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    (NAS_UTRANCTRL_GetUtranCtrlCtx()->stPlmnSearchCtrl.ucSearchedSpecTdMccFlg) = ucFlg;
#endif
    return;
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
