/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmSwitchOn.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��09��
  ��������   : HRPD ����״̬���¼�������
  �����б�   :
  �޸���ʷ   :
 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasHsdFsmSwitchOn.h"
#include  "CnasHsdFsmSwitchOnTbl.h"
#include  "CnasHsdProcNvim.h"
#include  "CnasHsdProcCard.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "NasComm.h"
#include  "NasUsimmApi.h"
#include  "CnasHsdFsmSwitchOn.h"
#include  "CnasHsdSndHlu.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdSndEhsm.h"
#include  "NVIM_Interface.h"
#include  "CnasPrlMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccStartReq_SwitchOn_Init
 ��������  : SwitchOn״̬������ʼ����״̬���յ�MMA�Ŀ�����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��08��
    ��    ��   : z00316370
    �޸�����   : ��״̬��ȡ�ӿڱ��
  3.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : �ȸ�HSM����

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvMsccStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_START_REQ_STRU            *pstStartReq;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enModeType;
    VOS_UINT32                          ul1xSupportFlag;
    VOS_UINT8                           ucIsReadNvPrlDirectly;
    VOS_UINT8                           ucIsReadDefaultPrl;

    pstStartReq = (MSCC_HSD_START_REQ_STRU *)pstMsg;

    /* ���������Ϣ */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    if ((MODEM_ID_0 != pstStartReq->enModemId)
     && (MODEM_ID_1 != pstStartReq->enModemId))
    {
        /* ����ʱ��������õ�modemId����modem0Ҳ����modem1�Ļ���ֱ�ӷ���ʧ�� */
        NAS_TRACE_HIGH("CNAS_HSD_RcvMsccStartReq_SwitchOn_Init: MSCC Send HSD unexpected ModemId=%d\r\n!", pstStartReq->enModemId);

        /* ֪ͨMMA������� */
        CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_FAIL);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_HSD_QuitFsmL2();

        return VOS_TRUE;
    }

    CNAS_CCB_SetCdmaModeModemId(pstStartReq->enModemId);

    /* ����9203NV�ж�ƽ̨����ʮ��֧��1X */
    ul1xSupportFlag = CNAS_HSD_Is1xSupport(pstStartReq->enModemId);

#else
    CNAS_CCB_SetCdmaModeModemId(MODEM_ID_0);

    /* ����9203NV�ж�ƽ̨����ʮ��֧��1X */
    ul1xSupportFlag = CNAS_HSD_Is1xSupport(MODEM_ID_0);
#endif



    /* �洢��״̬ */
    CNAS_HSD_SaveCardStatus_SwitchOn(pstStartReq->enCsimStatus,
                                     pstStartReq->enUsimStatus);

    /* ����MSCC�Ŀ��������ж��ǻ��ģʽ���ǻ��ģʽ */
    enModeType = CNAS_HSD_CheckHybridMode(pstStartReq->ucSuppRatNum, &pstStartReq->aenRatMode[0]);

    /* ���õ�ǰ����ģʽ */
    CNAS_HSD_SetSysModeType(enModeType);

    /* ��ȡNV������ */
    CNAS_HSD_ReadNvimInfo_SwitchOn(ul1xSupportFlag);

    if (VOS_FALSE == ul1xSupportFlag)
    {
        /* ��ȡ���е��ļ��������п�����1X��֧��ʱ����Ҫ��ȡ */
        enCsimCardStatus                 = CNAS_CCB_GetCsimCardStatus();
        ucIsReadNvPrlDirectly            = CNAS_HSD_GetTestConfig()->ucReadNvPrlDirectly;
        ucIsReadDefaultPrl               = CNAS_HSD_GetTestConfig()->ucReadDefaultPrl;

        if ((VOS_FALSE                    == ucIsReadNvPrlDirectly)
         && (VOS_FALSE                    == ucIsReadDefaultPrl)
         && (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus))
        {
            if ((VOS_FALSE  == CNAS_PRL_GetPrlInfoValidFlag())
             || (VOS_TRUE   == pstStartReq->ucIsCardChanged))
            {
                /* ��ʼ��PRL�����¶��� */
                CNAS_PRL_InitPrlCtx(VOS_FALSE);

                /* �ȶ�EPRL */
                if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
                {
                    CNAS_HSD_SndCardReadFileReq(USIMM_CSIM_EFEPRL_ID);
                }
                else
                {
                    CNAS_HSD_SndCardReadFileReq(USIMM_CDMA_EFEPRL_ID);
                }

                CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_EPRL_FLG);

                /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);
                CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF, TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN);

                return VOS_TRUE;
            }
        }

        if ((VOS_FALSE  == CNAS_PRL_GetPrlInfoValidFlag())
         || (VOS_TRUE   == pstStartReq->ucIsCardChanged))
        {
            /* ��ʼ��PRL�����¶�ȡNv��DefaultPrl */
            CNAS_PRL_InitPrlCtx(VOS_FALSE);

            if (VOS_FALSE == ucIsReadDefaultPrl)
            {
                CNAS_HSD_ReadPrlNvim();
            }

            if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
            {
                CNAS_HSD_ReadDefaultPrl();
            }

            if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
            {
                /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
                CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

                /* ������ɣ��˳����״̬��*/
                CNAS_HSD_QuitFsmL2();

                return VOS_TRUE;
            }
        }
        else
        {
            CNAS_PRL_LogHeaderInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader));
            CNAS_PRL_LogAcqRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo));
            CNAS_PRL_LogSysRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo));
        }
    }

    /* �����й����Ŷ����¼� */
    CNAS_HSD_ProcessCTCCCustomize();

    /* ֪ͨHSM���� */
    CNAS_HSD_SndHsmStartReq();

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_XCC_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF, TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvGetCardFileCnf_SwitchOn_WaitUimFileCnf
 ��������  : HSD��WAIT_CARD_FILE_CNF״̬�£��յ���ȡ���ļ���Ϣ�Ļظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  3.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : ��HSM����
  4.��    ��   : 2015��08��18��
    ��    ��   : x00306642
    �޸�����   : ���Ӷ�PRL�ļ�ʧ�ܵ�����

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          enEfId;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return VOS_TRUE;
    }

    /* �����ȡ�ļ��ĵȴ���� */
    CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf((VOS_UINT16)enEfId);

    /* ֹͣHSD��Ӧ��״̬������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF);

    /* �����ļ���ȡȷ�� */
    CNAS_HSD_ProcCardReadFileCnf(pstMsg);

    /* �жϵ�ǰ�ļ��Ķ�ȡ�Ƿ��Ѿ���ɣ���û�ж�ȡ��ɣ���ֱ��return��״̬���� */
    if (CNAS_HSD_READ_CARD_FILE_FLG_NULL != CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ��ȡNV��PRL������PRL */
        CNAS_HSD_ReadPrlNvim();
    }

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ��ȡdefault PRL */
        CNAS_HSD_ReadDefaultPrl();
    }

    /* ���default PRL����ʧ�ܣ�֪ͨ�ϲ㿪��ʧ�� */
    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_HSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����й����Ŷ����¼� */
    CNAS_HSD_ProcessCTCCCustomize();

    /* ֪ͨHSM���� */
    CNAS_HSD_SndHsmStartReq();

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_XCC_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF, TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf
 ��������  : HSD��WAIT_CARD_FILE_CNF״̬�£��ȴ���ȡUIM���ļ���ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : ��HSM����

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf:read Card file expired");

    if (CNAS_HSD_READ_CARD_FILE_EPRL_FLG == (CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_HSD_READ_CARD_FILE_EPRL_FLG))
    {
        /* ����ȴ���ȡEF-EPRL�ļ���־ */
        CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFEPRL_ID);

        /* ��ȡEF-PRL */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == CNAS_CCB_GetCsimCardStatus())
        {
            CNAS_HSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_HSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }

        /* ���õȴ���ȡEF-PRL�ļ���־ */
        CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_PRL_FLG);

        /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF, TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    if (CNAS_HSD_READ_CARD_FILE_PRL_FLG == (CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_HSD_READ_CARD_FILE_PRL_FLG))
    {
        /* ����ȴ���ȡEF-PRL�ļ���־ */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == CNAS_CCB_GetCsimCardStatus())
        {
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }

        /* ��ȡNV��PRL������PRL */
        CNAS_HSD_ReadPrlNvim();

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* ��ȡdefault PRL */
            CNAS_HSD_ReadDefaultPrl();
        }

        /* ���default PRL����ʧ�ܣ�֪ͨ�ϲ㿪��ʧ�� */
        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
            CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

            /* ������ɣ��˳����״̬��*/
            CNAS_HSD_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* �����й����Ŷ����¼� */
    CNAS_HSD_ProcessCTCCCustomize();

    /* ֪ͨHSM���� */
    CNAS_HSD_SndHsmStartReq();

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_XCC_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HSM_START_CNF);
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF, TI_CNAS_HSD_WAIT_HSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHsmStartCnf_SwitchOn_WaitHsmStartCnf
 ��������  : HSD��WAIT_HSM_START_CNF ״̬��,�յ�HSM�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvHsmStartCnf_SwitchOn_WaitHsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣHSD��Ӧ��״̬������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HSM_START_CNF);

    /* ֪ͨEHSM���� */
    CNAS_HSD_SndEhsmStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_EHSM_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_EHSM_START_CNF, TI_CNAS_HSD_WAIT_EHSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf
 ��������  : HSD��WAIT_HSM_START_CNF ״̬��,�ȴ�HSM�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��15��
    ��    ��   : z00316370
    �޸�����   : ��EHSM���Ϳ�������

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiHsmStartCnfExpired_SwitchOn_WaitHsmStartCnf:wait hsm start cnf expired");

    /* ֪ͨEHSM���� */
    CNAS_HSD_SndEhsmStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_EHSM_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_EHSM_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_EHSM_START_CNF, TI_CNAS_HSD_WAIT_EHSM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHluStartCnf_SwitchOn_WaitHluStartCnf
 ��������  : HSD��WAIT_HLU_START_CNF ״̬��,�յ�HLU�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : ��CAS����
*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvHluStartCnf_SwitchOn_WaitHluStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣHSD��Ӧ��״̬������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_HLU_START_CNF);

    /* ֪ͨCAS���� */
    CNAS_HSD_SndCasStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_CAS_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_START_CNF, TI_CNAS_HSD_WAIT_CAS_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf
 ��������  : HSD��WAIT_HLU_START_CNF ״̬��,�ȴ�HLU�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : ��CAS����

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiHluStartCnfExpired_SwitchOn_WaitHluStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiHluStartCnfExpired_SwitchOn_WaitHluStartCnf: wait hlu start cnf expired");

    /* ֪ͨCAS���� */
    CNAS_HSD_SndCasStartReq((MSCC_HSD_START_REQ_STRU *)(CNAS_HSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer));

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_CAS_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_START_CNF, TI_CNAS_HSD_WAIT_CAS_START_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf
 ��������  : HSD��WAIT_CAS_START_CNF ״̬��,�յ�CAS�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��18��
    ��    ��   : z00316370
    �޸�����   : �ϱ������������״̬��
*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_START_CNF_STRU       *pstStartCnf;

    pstStartCnf = (CAS_CNAS_HRPD_START_CNF_STRU *)pstMsg;

    NAS_TRACE_HIGH("result=%d", pstStartCnf->enStartRslt);

    /* ֹͣHSD��Ӧ��״̬������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_START_CNF);

    /* ֪ͨMMA������� */
    if (VOS_OK != pstStartCnf->enStartRslt)
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);
    }
    else
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_SUCCESS);
    }

    /* ������ɣ��˳����״̬��*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf
 ��������  : HSD��WAIT_CAS_START_CNF ״̬��,�ȴ�CAS�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_HSD_SndSwitchOnRlst(CNAS_HSD_SWITCH_ON_RESULT_FAILURE);

    /* ������ɣ��˳����״̬��*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ReadNvimInfo_SwitchOn
 ��������  :  ����ʱ��ȡNV����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_HSD_ReadNvimInfo_SwitchOn(VOS_UINT32 ul1xSupportFlag)
{
    /* ��ȡNV�е�MRU��Ϣ */
    CNAS_HSD_ReadMruNvim();

    /* ��ȡNV�еĴ洢������ʱ������Ϣ */
    CNAS_HSD_ReadSearchIntervalNvim();

    CNAS_HSD_ReadHrpdSupportBandClassMaskNvim();

    if (VOS_FALSE == ul1xSupportFlag)
    {
        CNAS_HSD_ReadOperLockSysWhiteListInfoNvim();

        CNAS_HSD_ReadCTCCCustomizeFreqNvim();
    }

    CNAS_HSD_ReadTestConfigNvim();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCardReadFileReq
 ��������  :  ����ʱ��ȡ���ļ��Ĵ���
 �������  : enFileId -- �ļ�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��3��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_HSD_SndCardReadFileReq(USIMM_CUIM_FILEID_ENUM_UINT16 enFileId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;


    /* ��ǰֻ����һ�¶������̣�����������Ϣ����������������ʱ���ٽ�һ������ */

    /* ��ȡEPRL�����θ���ԭ���Ľӿڣ��������ӿڶ�ȡ��ʱ��ͳһ�滻 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      enFileId,
                                      0);

    ulRet = NAS_USIMMAPI_GetFileReq(UEPS_PID_HSD, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* ��ӡ���ļ���ȡʧ�� */
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndCardReadFileReq: Read card file failure");
        return;
    }

    CNAS_MNTN_LogUsimmApiGetFileReq(UEPS_PID_HSD, ulRet, (CNAS_MNTN_LOG_GETFILE_INFO_STRU *)&stGetFileInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveCardStatus_SwitchOn
 ��������  : ��MMA�·��Ŀ�״̬��Ϣת����CCBʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : ucCardStatus��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : ���Ӵ洢USIM״̬

*****************************************************************************/
VOS_VOID  CNAS_HSD_SaveCardStatus_SwitchOn(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enCsimCardStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
)
{
    /* ����CSIM��״̬ */
    if (NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT == enCsimCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_UIM_PRESENT);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_CSIM_PRESENT);
    }
    else
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_ABSENT);
    }

    /* ����USIM��״̬ */
    if (NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT == enUsimCardStatus)
    {
        CNAS_CCB_SetUsimCardStatus(CNAS_CCB_CARD_STATUS_SIM_PRESENT);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT == enUsimCardStatus)
    {
        CNAS_CCB_SetUsimCardStatus(CNAS_CCB_CARD_STATUS_USIM_PRESENT);
    }
    else
    {
        CNAS_CCB_SetUsimCardStatus(CNAS_CCB_CARD_STATUS_ABSENT);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveCardStatus_SwitchOn
 ��������  : ��MMA�·��Ŀ�״̬��Ϣת����CCBʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : usEfId:�ļ�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
)
{
    switch ( usEfId )
    {
        case USIMM_CDMA_EFEPRL_ID:
        case USIMM_CSIM_EFEPRL_ID:
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_EPRL_FLG);
            break;

        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_PRL_FLG);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSD, "NAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvEhsmStartCnf_SwitchOn_WaitEhsmStartCnf
 ��������  : HSD��WAIT_HSM_START_CNF ״̬��,�յ�HSM�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2015��06��05��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvEhsmStartCnf_SwitchOn_WaitEhsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣHSD��Ӧ��״̬������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_EHSM_START_CNF);

    /* ֪ͨHLU���� */
    CNAS_HSD_SndHluStartReq();

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_HLU_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HLU_START_CNF, TI_CNAS_HSD_WAIT_HLU_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf
 ��������  : HSD��WAIT_EHSM_START_CNF ״̬��,�ȴ�EHSM�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��05��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvTiEhsmStartCnfExpired_SwitchOn_WaitEhsmStartCnf:wait ehsm start cnf expired");

    /* ֪ͨHLU���� */
    CNAS_HSD_SndHluStartReq();

    /* Ǩ�Ƶ� CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF״̬,������������ʱ��TI_CNAS_HSD_WAIT_HLU_START_CNF */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_SWITCH_ON_STA_WAIT_HLU_START_CNF);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_HLU_START_CNF, TI_CNAS_HSD_WAIT_HLU_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ReadDefaultPrl
 ��������  : ��ȡdefault PRL������

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��18��
   ��    ��   : x00306642
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_ReadDefaultPrl(VOS_VOID)
{
    VOS_UINT8                          *pucPrlBuf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    /* ����default PRL */
    pucPrlBuf = CNAS_PRL_GetDefaultPrl();

    ulRslt = CNAS_PRL_ProcPrlInfo(pucPrlBuf, CNAS_PRL_GetDefaultPrlSize(), CNAS_PRL_SSPR_P_REV_3);

    if (VOS_TRUE == ulRslt)
    {
        CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_HARD_CODE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_Is1xSupport
 ��������  : �ж�plat�Ƿ�֧��1X
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_Is1xSupport(MODEM_ID_ENUM_UINT16                enModemId)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stModem0PlatRat;
    VOS_UINT16                          i;

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Platform_RAT_CAP, &stModem0PlatRat,
                           sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Is1xSupport read NV en_NV_Item_Platform_RAT_CAP failed!\r\n");
        return VOS_FALSE;
    }

    for (i = 0; i < stModem0PlatRat.usRatNum; i++)
    {
        if (PLATFORM_RAT_1X == stModem0PlatRat.aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



