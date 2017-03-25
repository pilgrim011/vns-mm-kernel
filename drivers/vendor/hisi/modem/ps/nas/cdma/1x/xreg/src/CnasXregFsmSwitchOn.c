/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregFsmSwitchOn.c
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2015��01��05��
  ��������   : 1X XREG����״̬���¼�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasXregFsmSwitchOn.h"
#include  "CnasXregFsmSwitchOnTbl.h"
#include  "CnasMntn.h"
#include  "CnasXregCtx.h"
#include  "NasComm.h"
#include  "NasUsimmApi.h"
#include  "CnasXregProcess.h"
#include  "CnasXregTimer.h"
#include  "CnasXregSndInternalMsg.h"
#include  "CnasTimerMgmt.h"
#include  "CnasMntn.h"
#include  "siapppih.h"
#include  "NVIM_Interface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
extern VOS_UINT32 I1_PIH_RegCardRefreshIndMsg(VOS_UINT32 ulRegPID);
extern VOS_UINT32 I1_PIH_DeregCardRefreshIndMsg(VOS_UINT32 ulRegPID);
#endif

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvXsdStartReq_SwitchOn_Init
 ��������  : SwitchOn״̬������ʼ����״̬���յ�Xsd�Ŀ�����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvXsdStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus;
    MODEM_ID_ENUM_UINT16                enCdmaModeModemId;

    /* ���������Ϣ */
    CNAS_XREG_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��ȡNV������ */
    CNAS_XREG_ReadNvimInfo_SwitchOn();

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    /* ��ȡ���е��ļ� */
    if (CNAS_CCB_CARD_STATUS_ABSENT != enCsimCardStatus)
    {
        /* ��EFterm�ļ� */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CSIM_EFTERM_ID);
        }
        else
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CDMA_EFTERM_ID);
        }

        CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_TERM_FLG);

        /* ��EFssci�ļ� */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CSIM_EFSSCI_ID);
        }
        else
        {
            CNAS_XREG_SndCardReadFileReq(USIMM_CDMA_EFSSCI_ID);
        }

        CNAS_XREG_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_SSCI_FLG);

        /* Ǩ�Ƶ� CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* ����������ʱ��TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT */
        CNAS_XREG_StartTime(TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT, TI_CNAS_XREG_TIMER_CARDFILE_CNF_LEN);
    }
    else
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XREG_SndSwitchOnRlst(CNAS_XREG_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_XREG_QuitFsmL2();
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��ȡCdma������modem ID */
    enCdmaModeModemId = CNAS_CCB_GetCdmaModeModemId();

    /* ȥע���ӦģPID */
    if (MODEM_ID_1 == enCdmaModeModemId)
    {
        /* ע�ᵱǰPID */
        I1_PIH_RegCardRefreshIndMsg(UEPS_PID_XREG);

        PIH_DeregCardRefreshIndMsg(UEPS_PID_XREG);
    }
    else
    {
        I1_PIH_DeregCardRefreshIndMsg(UEPS_PID_XREG);

        /* ע�ᵱǰPID */
        PIH_RegCardRefreshIndMsg(UEPS_PID_XREG);
    }
#else
    /* ע�ᵱǰPID */
    PIH_RegCardRefreshIndMsg(UEPS_PID_XREG);

#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf
 ��������  : XREG��WAIT_CARD_FILE_CNF״̬�£��յ���ȡ���ļ���Ϣ�Ļظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId;


    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return VOS_TRUE;
    }

    /* ֹͣXREG��Ӧ��״̬������ʱ�� */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_CARDFILE_CNF_PT, 0);

    /* �����ȡ�ļ��ĵȴ���� */
    CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf((VOS_UINT16)enEfId);

    /* �����ļ���ȡȷ�� */
    CNAS_XREG_ProcCardReadFileCnf(pstMsg);

    /* �жϵ�ǰ�ļ��Ķ�ȡ�Ƿ��Ѿ���ɣ���û�ж�ȡ��ɣ���ֱ��return��״̬���� */
    if (CNAS_XREG_READ_CARD_FILE_FLG_NULL != CNAS_XREG_GetWaitCardFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XREG_SndSwitchOnRlst(CNAS_XREG_SWITCH_ON_RESULT_SUCCESS);

    /* ������ɣ��˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf
 ��������  : XREG��WAIT_CARD_FILE_CNF״̬�£��ȴ���ȡUIM���ļ���ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf:read Card file expired");

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XREG_SndSwitchOnRlst(CNAS_XREG_SWITCH_ON_RESULT_FAILURE);

    /* ������ɣ��˳����״̬��*/
    CNAS_XREG_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_SndCardReadFileReq
 ��������  : ����ʱ��ȡNV����ֵ
 �������  : enFileId -- �ļ�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_XREG_SndCardReadFileReq(USIMM_CUIM_FILEID_ENUM_UINT16 enFileId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    /* ��ȡEPRL�����θ���ԭ���Ľӿڣ��������ӿڶ�ȡ��ʱ��ͳһ�滻 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      enFileId,
                                      0);

    ulRet = NAS_USIMMAPI_GetFileReq(UEPS_PID_XREG, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* ��ӡ���ļ���ȡʧ�� */
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_SndCardReadFileReq: Read card file failure");

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf
 ��������  : ��MMA�·��Ŀ�״̬��Ϣת����CCBʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : ucCardStatus��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
)
{
    switch ( usEfId )
    {
        case USIMM_CDMA_EFTERM_ID:
        case USIMM_CSIM_EFTERM_ID:
            CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_TERM_FLG);
            break;

        case USIMM_CSIM_EFSSCI_ID:
        case USIMM_CDMA_EFSSCI_ID:
            CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XREG_READ_CARD_FILE_SSCI_FLG);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XREG, "CNAS_XREG_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ReadNvimInfo_SwitchOn
 ��������  : ����״̬�¶�ȡNV������.
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_ReadNvimInfo_SwitchOn(VOS_VOID)
{
    CNAS_NVIM_1X_LAST_SCI_STRU          stLastSci;
    CNAS_NVIM_NO_CARD_MODE_CFG_STRU     stNoCardModeCfg;

    CNAS_XREG_SetLastSciValue(CNAS_XREG_SCI_DEF_VALUE);

    if (NV_OK == NV_Read(en_NV_Item_1X_LAST_SCI, &stLastSci, sizeof(stLastSci)))
    {
        /* �����ж� */
        if (CNAS_XREG_SCI_MAX_VALUE >= stLastSci.ulSicValue)
        {
            CNAS_XREG_SetLastSciValue((VOS_UINT8)stLastSci.ulSicValue);
        }
        CNAS_MNTN_LogReadNVInfo(en_NV_Item_1X_LAST_SCI,
                                sizeof(stLastSci),
                                UEPS_PID_XREG,
                                (VOS_UINT8 *)&stLastSci);
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_ReadNvimInfo_SwitchOn:NV_Read Failed");
    }


    if (NV_OK == NV_Read(en_NV_Item_NO_CARD_MODE_CFG, &stNoCardModeCfg, sizeof(stNoCardModeCfg)))
    {
        /* �����ж� */
        if (VOS_FALSE != stNoCardModeCfg.ulEnableFlag)
        {
            CNAS_XREG_EnableNoCardMode();
        }
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_ReadNvimInfo_SwitchOn:NV_Read Failed");
    }



    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

