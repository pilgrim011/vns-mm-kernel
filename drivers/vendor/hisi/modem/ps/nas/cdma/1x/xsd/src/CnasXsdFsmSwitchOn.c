/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdFsmSwitchOn.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��07��03��
  ��������   : 1X SD����״̬���¼�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdFsmSwitchOn.h"
#include  "CnasXsdFsmSwitchOnTbl.h"
#include  "CnasXsdProcNvim.h"
#include  "CnasXsdProcCard.h"
#include  "CnasXsdSndXcc.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdMntn.h"
#include  "NasComm.h"
#include  "NasUsimmApi.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccStartReq_SwitchOn_Init
 ��������  : SwitchOn״̬������ʼ����״̬���յ�MSCC�Ŀ�����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��21��
    ��    ��   : w00242748
    �޸�����   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvMsccStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_START_REQ_STRU                                *pstStartReq;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCsimCardStatus;

    VOS_UINT8                           ucIsReadNvPrlDirectly;
    MODEM_ID_ENUM_UINT16                enPreModemId;
    VOS_UINT8                           ucIsReadDefaultPrl;
    USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId;
    USIMM_DEF_FILEID_ENUM_UINT32        enEPrlFileId;

    ucIsReadDefaultPrl                  = VOS_FALSE;
    enHomeSidNidFileId                  = USIMM_CDMA_EFCDMAHOME_ID;
    enEPrlFileId                        = USIMM_CDMA_EFEPRL_ID;

    pstStartReq = (MSCC_XSD_START_REQ_STRU*)pstMsg;

    /* ���������Ϣ */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    enPreModemId = CNAS_CCB_GetCdmaModeModemId();

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    if ((MODEM_ID_0 != pstStartReq->enModemId)
     && (MODEM_ID_1 != pstStartReq->enModemId))
    {
        /* ����ʱ��������õ�modemId����modem0Ҳ����modem1�Ļ���ֱ�ӷ���ʧ�� */
        NAS_TRACE_HIGH("CNAS_XSD_RcvMsccStartReq_SwitchOn_Init: MSCC Send XSD unexpected ModemId=%d\r\n!", pstStartReq->enModemId);

        /* ֪ͨMMA������� */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_XSD_QuitFsmL2();

        return VOS_TRUE;
    }

    CNAS_CCB_SetCdmaModeModemId(pstStartReq->enModemId);
#else

    CNAS_CCB_SetCdmaModeModemId(MODEM_ID_0);
#endif

    /* ��ȡNV������ */
    CNAS_XSD_ReadNvimInfo_SwitchOn();

    /* �洢��״̬ */
    CNAS_XSD_SaveCardStatus_SwitchOn(pstStartReq->enCardStatus);

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        enHomeSidNidFileId              = USIMM_CSIM_EFCDMAHOME_ID;
        enEPrlFileId                    = USIMM_CSIM_EFEPRL_ID;
    }

    /* ��ȡ���е��ļ� */
    ucIsReadNvPrlDirectly            = CNAS_XSD_GetTestConfig()->ucReadNvPrlDirectly;

    ucIsReadDefaultPrl               = CNAS_XSD_GetTestConfig()->ucReadDefaultPrl;

    if ((VOS_FALSE                    == ucIsReadNvPrlDirectly)
     && (VOS_FALSE                    == ucIsReadDefaultPrl)
     && (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus))
    {
        if ((VOS_FALSE   == CNAS_PRL_GetPrlInfoValidFlag())
         || (VOS_TRUE    == pstStartReq->ucIsCardChanged))
        {
            /* ��ʼ��PRL�����¶��� */
            CNAS_PRL_InitPrlCtx(VOS_FALSE);

            /* ��ȡ����PRL */
            /* �ȶ�EPRL */
            CNAS_XSD_SndCardReadFileReq(enEPrlFileId);
            CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

            CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_EPRL_FLG);
            CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

            /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

            /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

            return VOS_TRUE;
        }
    }

    /* ��������*/
    if ((VOS_TRUE == ucIsReadNvPrlDirectly)
     || (VOS_TRUE == ucIsReadDefaultPrl))
    {
        CNAS_XSD_ProcTestConfig_SwitchOn_Init(ucIsReadNvPrlDirectly,
                                              ucIsReadDefaultPrl,
                                              enCsimCardStatus,
                                              enHomeSidNidFileId);

        return VOS_TRUE;
    }

    if ( (enPreModemId != CNAS_CCB_GetCdmaModeModemId())
      && (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus) )
    {
        /* ��ʼ��PRL�����¶��� */
        CNAS_PRL_InitPrlCtx(VOS_FALSE);

        /* ��ȡ����PRL */
        /* �ȶ�EPRL */
        CNAS_XSD_SndCardReadFileReq(enEPrlFileId);
        CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_EPRL_FLG);
        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

        /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    if ((VOS_FALSE  == CNAS_PRL_GetPrlInfoValidFlag())
     || (VOS_TRUE   == pstStartReq->ucIsCardChanged))
    {
        /* ��ʼ��PRL�����¶�ȡNv��DefaultPrl */
        CNAS_PRL_InitPrlCtx(VOS_FALSE);

        CNAS_XSD_ReadPrlNvim();

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            CNAS_XSD_ReadDefaultPrl();
        }

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* ֪ͨMMA������� */
            CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

            /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
            CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

            /* ������ɣ��˳����״̬��*/
            CNAS_XSD_QuitFsmL2();

            return VOS_TRUE;
        }
    }
    else
    {
        CNAS_PRL_LogHeaderInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader));
        CNAS_PRL_LogAcqRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo));
        CNAS_PRL_LogSysRecInfo(&(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo));
    }

    if (CNAS_CCB_CARD_STATUS_ABSENT  != enCsimCardStatus)
    {
        /* ��ȡ���е�Home Sid/Nid List */
        CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

        /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    /* ֪ͨXCC���� */
    CNAS_XSD_SndXccStartReq();

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvGetCardFileCnf_SwitchOn_WaitUimFileCnf
 ��������  : XSD��WAIT_CARD_FILE_CNF״̬�£��յ���ȡ���ļ���Ϣ�Ļظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
 �޸���ʷ      :
  2.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : Usimm���ӿڵ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          ulEfId;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &ulEfId))
    {
        return VOS_FALSE;
    }

    /* �����ȡ�ļ��ĵȴ���� */
    CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf((VOS_UINT16)ulEfId);

    /* �����ļ���ȡȷ�� */
    CNAS_XSD_ProcCardReadFileCnf(pstMsg);

    /* �жϵ�ǰ�ļ��Ķ�ȡ�Ƿ��Ѿ���ɣ���û�ж�ȡ��ɣ���ֱ��return��״̬���� */
    if (CNAS_XSD_READ_CARD_FILE_FLG_NULL != CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    /* ������ж�ȡ�����ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF);

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ��ȡNV��PRL������PRL */
        CNAS_XSD_ReadPrlNvim();
    }

    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ��ȡdefault PRL */
        CNAS_XSD_ReadDefaultPrl();
    }

    /* ���default PRL����ʧ�ܣ�֪ͨ�ϲ㿪��ʧ�� */
    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ֪ͨMMA������� */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_XSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ֪ͨXCC���� */
    CNAS_XSD_SndXccStartReq();

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf
 ��������  : XSD��WAIT_CARD_FILE_CNF״̬�£��ȴ���ȡUIM���ļ���ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��30��
   ��    ��   : z00316370
   �޸�����   : ��״̬����

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                    enCsimCardStatus;

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf:read Card file expired");

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    if (CNAS_XSD_READ_CARD_FILE_EPRL_FLG == (CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_XSD_READ_CARD_FILE_EPRL_FLG))
    {
        /* ����ȴ���ȡEF-EPRL�ļ���־ */
        CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFEPRL_ID);

        /* ��ȡEF-PRL */

        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_XSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }

        /* ���õȴ���ȡEF-PRL�ļ���־ */
        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_PRL_FLG);

        /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return VOS_TRUE;
    }

    if (CNAS_XSD_READ_CARD_FILE_PRL_FLG == (CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn() & CNAS_XSD_READ_CARD_FILE_PRL_FLG))
    {
        /* ����ȴ���ȡEF-PRL�ļ���־ */
        if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
        {
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
        }
        else
        {
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
        }
        /* ��ȡNV��PRL������PRL */
        CNAS_XSD_ReadPrlNvim();

        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* ��ȡdefault PRL */
            CNAS_XSD_ReadDefaultPrl();
        }

        /* ���default PRL����ʧ�ܣ�֪ͨ�ϲ㿪��ʧ�� */
        if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
        {
            /* ֪ͨMMA������� */
            CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

            /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
            CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

            /* ������ɣ��˳����״̬��*/
            CNAS_XSD_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SndXccStartReq();

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf
 ��������  : XSD��WAIT_XCC_START_CNF ״̬��,�յ�XCC�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXccStartCnf_SwitchOn_WaitXccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF);

    /* ֪ͨXREG���� */
    CNAS_XSD_SndXregStartReq();

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_START_CNF, TI_CNAS_XSD_WAIT_XREG_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf
 ��������  : XSD��WAIT_XCC_START_CNF ״̬��,�ȴ�XCC�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiXccStartCnfExpired_SwitchOn_WaitXccStartCnf:wait xcc start cnf expired");

    /* ֪ͨXREG���� */
    CNAS_XSD_SndXregStartReq();

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XREG_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_START_CNF, TI_CNAS_XSD_WAIT_XREG_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf
 ��������  : XSD��WAIT_XREG_START_CNF ״̬��,�յ�XREG�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��15��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXregStartCnf_SwitchOn_WaitXregStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_START_REQ_STRU            *pstStartReq = VOS_NULL_PTR;

    /* ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XREG_START_CNF);

    pstStartReq = (MSCC_XSD_START_REQ_STRU *)&(CNAS_XSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer[0]);

    /* ֪ͨCAS���� */
    CNAS_XSD_SndCasStartReq(pstStartReq);


    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_CAS_START_CNF */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_START_CNF, TI_CNAS_XSD_WAIT_CAS_START_CNF_LEN);
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf
 ��������  : XSD��WAIT_XREG_START_CNF ״̬��,�ȴ�XREG�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��15��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_START_REQ_STRU            *pstStartReq = VOS_NULL_PTR;

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiXregStartCnfExpired_SwitchOn_WaitXregStartCnf: wait xreg start cnf expired");

    pstStartReq = (MSCC_XSD_START_REQ_STRU *)&(CNAS_XSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer[0]);

    /* ֪ͨCAS���� */
    CNAS_XSD_SndCasStartReq(pstStartReq);

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_CAS_START_CNF */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_START_CNF, TI_CNAS_XSD_WAIT_CAS_START_CNF_LEN);
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CAS_START_CNF);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf
 ��������  : XSD��WAIT_CAS_START_CNF ״̬��,�յ�CAS�Ŀ���ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCasStartCnf_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_START_CNF_STRU         *pstStartCnf;

    pstStartCnf = (CAS_CNAS_1X_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("result=%d", pstStartCnf->enRslt);

    /* ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_START_CNF);

    /* ֪ͨMMA������� */
    if (CNAS_CAS_1X_RSLT_FAILURE == pstStartCnf->enRslt)
    {
        /* ֪ͨMMA����ʧ�� */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_XSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ֪ͨMMA�����ɹ� */
    CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_SUCC);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_SUCCESS);

    /* ������ɣ��˳����״̬��*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf
 ��������  : XSD��WAIT_CAS_START_CNF ״̬��,�ȴ�CAS�Ŀ���ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiCasStartCnfExpired_SwitchOn_WaitCasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ֪ͨMMA������� */
    CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

    /* ������ɣ��˳����״̬��*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadNvimInfo_SwitchOn
 ��������  :  ����ʱ��ȡNV����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����7����
  3.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17

*****************************************************************************/
VOS_VOID  CNAS_XSD_ReadNvimInfo_SwitchOn(VOS_VOID)
{
    /* ��ȡNV�е�MRU��Ϣ */
    CNAS_XSD_ReadMruNvim();

    /* read NVIM of Bandclass Information */
    CNAS_XSD_ReadBandClassNvim();

    /* ��ȡNV�е�HOME SID NID��Ϣ */
    CNAS_XSD_ReadHomeSidNidNvim();

    CNAS_XSD_ReadSearchIntervalNvim();

    CNAS_XSD_ReadChanRepeatScanScheduleConfigNvim();

    CNAS_XSD_ReadTestConfigNvim();

    CNAS_XSD_ReadAddAvoidListCfgNvim();

    CNAS_XSD_ReadNegPrefSysCmpCtrlNvim();

    CNAS_XSD_ReadHomeSidNidDependOnCfgNvim();

    CNAS_XSD_ReadOperLockSysWhiteListInfoNvim();

    CNAS_XSD_ReadCTCCCustomizeFreqNvim();

    CNAS_XSD_ReadCdmaStandardChannelsNvim();

    /* ��ȡCallBackģʽ���� */
    CNAS_XSD_ReadCallBackCfgNvim();

    /* ��ȡCDMA 1X ��ѡƵ����Ϣ */
    CNAS_XSD_ReadCdma1XCustomPrefChannelsNvim();

    CNAS_XSD_Read1xSupportBandClassMaskNvim();

    CNAS_XSD_ReadNoCardModeCfgNvim();

    CNAS_XSD_ReadEmcRedialSysAcqCfgNvim();

    CNAS_XSD_Read1xAvoidScheduleInfoNvim();

    CNAS_XSD_Read1xPowerOffCampOnCtrlFlgNvim();

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadNvimInfo_SwitchOn
 ��������  :  ����ʱ��ȡNV����ֵ
 �������  : enFileId -- �ļ�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_XSD_SndCardReadFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileId)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT32                          ulRet;

    /* ��ȡEPRL�����θ���ԭ���Ľӿڣ��������ӿڶ�ȡ��ʱ��ͳһ�滻 */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      (VOS_UINT16)enFileId,
                                      0);

    ulRet = NAS_USIMMAPI_GetFileReq(UEPS_PID_XSD, 0, &stGetFileInfo);

    if (USIMM_API_SUCCESS != ulRet)
    {
        /* ��ӡ���ļ���ȡʧ�� */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_SndCardReadFileReq: Read card file failure");
        return;
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveCardStatus_SwitchOn
 ��������  : ��MMA�·��Ŀ�״̬��Ϣת����CCBʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : ucCardStatus��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��15��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��6��30��
   ��    ��   : z00316370
   �޸�����   : ��״̬����

*****************************************************************************/
VOS_VOID  CNAS_XSD_SaveCardStatus_SwitchOn(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8     enCardStatus
)
{
    if (NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT == enCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_UIM_PRESENT);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCardStatus)
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_CSIM_PRESENT);
    }
    else
    {
        CNAS_CCB_SetCsimCardStatus(CNAS_CCB_CARD_STATUS_ABSENT);
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveCardStatus_SwitchOn
 ��������  : ��MMA�·��Ŀ�״̬��Ϣת����CCBʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : ucCardStatus��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��15��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf(
    VOS_UINT16                          usEfId
)
{
    switch ( usEfId )
    {
        case USIMM_CDMA_EFEPRL_ID: /* EF_CUIM_EPRL */
        case USIMM_CSIM_EFEPRL_ID:
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_EPRL_FLG);
            break;

        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_PRL_FLG);
            break;

        case USIMM_CDMA_EFCDMAHOME_ID: /* EF_CUIM_HOME */
        case USIMM_CSIM_EFCDMAHOME_ID:
            CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "NAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn_WaitCardFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadDefaultPrl
 ��������  : ��ȡdefault PRL������

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadDefaultPrl(VOS_VOID)
{
    VOS_UINT8                          *pucPrlBuf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    /* ����default PRL */
    pucPrlBuf = CNAS_PRL_GetDefaultPrl();

    ulRslt = CNAS_PRL_ProcPrlInfo(pucPrlBuf, CNAS_PRL_GetDefaultPrlSize(), CNAS_PRL_SSPR_P_REV_3);

    if (VOS_TRUE == ulRslt)
    {
        CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_HARD_CODE);
    }

#if 0
    /* �õ�ǰdefault PRLд�뵽NVRM�� */
    if (CNAS_PRL_GetDefaultPrlSize() <= NV_PREFERRED_ROAMING_LIST_SIZE)
    {
        if (NV_OK != NV_Write(en_NV_Item_PRL_LIST, pucPrlBuf, NV_PREFERRED_ROAMING_LIST_SIZE))
        {
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadPrlNvim:Write Nvim Failed!");
        }
    }
#endif

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcTestConfig_SwitchOn_Init
 ��������  : ����������Կ�����
 �������  : VOS_UINT8                           ucIsReadNvPrlDirectly
             VOS_UINT8                           ucIsReadDefaultPrl
             CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus
             USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��31��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcTestConfig_SwitchOn_Init(
    VOS_UINT8                           ucIsReadNvPrlDirectly,
    VOS_UINT8                           ucIsReadDefaultPrl,
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus,
    USIMM_DEF_FILEID_ENUM_UINT32        enHomeSidNidFileId
)
{
    /* ��֧�ּ�Ҫ��NV�еģ���Ҫ��ȱʡ�� */
    if ((VOS_TRUE == ucIsReadNvPrlDirectly)
     && (VOS_TRUE == ucIsReadDefaultPrl))
    {
        /* ֪ͨMMA������� */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_XSD_QuitFsmL2();

        return;
    }

    /* ��ʼ��PRL�� */
    CNAS_PRL_InitPrlCtx(VOS_FALSE);

    /* ��NV�е�PRL */
    if (VOS_TRUE == ucIsReadNvPrlDirectly)
    {
        CNAS_XSD_ReadPrlNvim();
    }

    /* ��Ĭ�ϵ�PRL */
    if (VOS_TRUE == ucIsReadDefaultPrl)
    {
        CNAS_XSD_ReadDefaultPrl();
    }

    /* ��PRLʧ�� */
    if (VOS_FALSE == CNAS_PRL_GetPrlInfoValidFlag())
    {
        /* ֪ͨMMA������� */
        CNAS_XSD_SndMsccStartCnf(XSD_MSCC_START_RESULT_FAIL);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSwitchOnRlst(CNAS_XSD_SWITCH_ON_RESULT_FAILURE);

        /* ������ɣ��˳����״̬��*/
        CNAS_XSD_QuitFsmL2();

        return;
    }

    /* �п���NV�ʹ��ʱ���Ŵӿ��ж�Home sid��nid */
    if ((VOS_FALSE == ucIsReadNvPrlDirectly)
     && (CNAS_CCB_CARD_STATUS_ABSENT != enCsimCardStatus))
    {
        /* ��ȡ���е�Home Sid/Nid List */
        CNAS_XSD_SndCardReadFileReq(enHomeSidNidFileId);

        CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_HOME_SID_NID_FLG);

        /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF״̬ */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_CARD_FILE_CNF);

        /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

        return;
    }

    /* ֪ͨXCC���� */
    CNAS_XSD_SndXccStartReq();

    /* Ǩ�Ƶ� CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_START_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SWITCH_ON_STA_WAIT_XCC_START_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_START_CNF, TI_CNAS_XSD_WAIT_XCC_START_CNF_LEN);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



