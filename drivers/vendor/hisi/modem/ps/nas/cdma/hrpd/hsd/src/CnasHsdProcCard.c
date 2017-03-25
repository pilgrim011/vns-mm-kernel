/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdProcCard.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��12��
  ��������   : HSD�����Ķ�ȡ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasHsdProcCard.h"
#include  "CnasHsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasHsdFsmSwitchOn.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_PROC_CARD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcCardReadFileCnf
 ��������  : �ӿ��ж�ȡ���и����ļ��Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��3��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU          *pstFile;
    USIMM_DEF_FILEID_ENUM_UINT32      enEfId;

    pstFile = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &enEfId))
    {
        return;
    }

    switch (enEfId)
    {
        case USIMM_CDMA_EFEPRL_ID:
        case USIMM_CSIM_EFEPRL_ID:
            CNAS_HSD_ProcCardReadFileCnf_EF_EPRL(pstMsg);
            break;

        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_HSD_ProcCardReadFileCnf_EF_PRL(pstMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCardReadFileCnf:WARNING: File Id Abnormal");
            break;

    }

    return;
}
/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcCardReadFileCnf_EF_EPRL
 ��������  : �ӿ��ж�ȡEFEPRL�Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCardReadFileCnf_EF_EPRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* �ж��ļ��Ķ�ȡ��� */
    if (VOS_OK != pstFile->stCmdResult.ulResult)
    {
        CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_RcvCardReadFileCnf_EF_EPRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);
    }
    else
    {
        CNAS_PRL_SetPrlRevInfo(CNAS_PRL_SSPR_P_REV_3);
        ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_3);

        if (VOS_TRUE == ulRslt)
        {
            CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_EPRL_FILE);
            return;
        }

        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCardReadFileCnf_EF_EPRL: EPRL Parse Fail!");
    }

    /* EF-EPRL��ȡʧ�ܣ���ȡEF-PRL�ļ� */
    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == CNAS_CCB_GetCsimCardStatus())
    {
        CNAS_HSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
    }
    else
    {
        CNAS_HSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
    }

    CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_HSD_READ_CARD_FILE_PRL_FLG);

    /* ����������ʱ��TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CARD_FILE_CNF, TI_CNAS_HSD_WAIT_CARD_FILE_CNF_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcCardReadFileCnf_EF_PRL
 ��������  : �ӿ��ж�ȡEF-PRL�Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��08��18��
   ��    ��   : x00306642
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcCardReadFileCnf_EF_PRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* �ļ��Ķ�ȡʧ�ܣ����� */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_ProcCardReadFileCnf_EF_PRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);

        return;
    }

    ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_1);

    if (VOS_TRUE != ulRslt)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_ProcCardReadFileCnf_EF_PRL: PRL Parse Fail!");
    }
    else
    {
        CNAS_HSD_LogPrlSourceType(CNAS_HSD_PRL_TYPE_PRL_FILE);
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





