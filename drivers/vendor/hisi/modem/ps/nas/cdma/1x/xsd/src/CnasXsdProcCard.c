/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdProcCard.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��07��08��
  ��������   : XSD�����Ķ�ȡ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��08��
    ��    ��   : h00246512
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdProcCard.h"
#include  "CnasXsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdFsmSwitchOn.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_PROC_CARD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCardReadFileCnf
 ��������  : �ӿ��ж�ȡ���и����ļ��Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 1.��    ��   : 2015��02��05��
   ��    ��   : h00313353
   �޸�����   : Usimm���ӿڵ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          ulEfId;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;
    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &ulEfId))
    {
        return;
    }

    switch (ulEfId)
    {
        case USIMM_CSIM_EFEPRL_ID: /* EF_CUIM_EPRL */
        case USIMM_CDMA_EFEPRL_ID:
            CNAS_XSD_ProcCardReadFileCnf_EF_EPRL(pstMsg);
            break;
        case USIMM_CDMA_EFPRL_ID: /* EF_CUIM_PRL */
        case USIMM_CSIM_EFPRL_ID:
            CNAS_XSD_ProcCardReadFileCnf_EF_PRL(pstMsg);
            break;

        case USIMM_CDMA_EFCDMAHOME_ID: /* EF_CUIM_HOME */
        case USIMM_CSIM_EFCDMAHOME_ID:
            CNAS_XSD_ProcCardReadFileCnf_EF_HOME(pstMsg);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCardReadFileCnf:WARNING: File Id Abnormal");
            break;

    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCardReadFileCnf_EF_EPRL
 ��������  : �ӿ��ж�ȡEFEPRL�Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��02��05��
   ��    ��   : h00313353
   �޸�����   : Usimm���ӿڵ���
 3.��    ��   : 2015��06��30��
   ��    ��   : z00316370
   �޸�����   : Usimm��״̬����
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf_EF_EPRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU                                *pstFile = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCsimCardStatus;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    /* �ж��ļ��Ķ�ȡ��� */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_RcvCardReadFileCnf_EF_EPRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);
    }
    else
    {
        /* ʹ��EPRL��ʽ������EPRL */
        CNAS_PRL_SetPrlRevInfo(CNAS_PRL_SSPR_P_REV_3);
        ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_3);

        if (VOS_TRUE == ulRslt)
        {
            CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_EPRL_FILE);
            return;
        }

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCardReadFileCnf_EF_EPRL: EPRL Parse Fail!");
    }

    /* EF-EPRL��ȡʧ�ܣ���ȡEF-PRL�ļ� */
    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        CNAS_XSD_SndCardReadFileReq(USIMM_CSIM_EFPRL_ID); /* EF_CUIM_PRL */
    }
    else
    {
        CNAS_XSD_SndCardReadFileReq(USIMM_CDMA_EFPRL_ID); /* EF_CUIM_PRL */
    }

    CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(CNAS_XSD_READ_CARD_FILE_PRL_FLG);

    /* ����������ʱ��TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CARD_FILE_CNF, TI_CNAS_XSD_WAIT_CARD_FILE_CNF_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCardReadFileCnf_EF_PRL
 ��������  : �ӿ��ж�ȡEF-PRL�Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��02��05��
   ��    ��   : h00313353
   �޸�����   : Usimm���ӿڵ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf_EF_PRL(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* �ļ��Ķ�ȡʧ�ܣ����� */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_ProcCardReadFileCnf_EF_PRL:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);

        return;
    }

    ulRslt = CNAS_PRL_ProcPrlInfo(&(pstFile->aucEf[0]), pstFile->usEfLen, CNAS_PRL_SSPR_P_REV_1);

    if (VOS_TRUE != ulRslt)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ProcCardReadFileCnf_EF_PRL: PRL Parse Fail!");
    }
    else
    {
        CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_PRL_FILE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCardReadFileCnf_EF_HOME
 ��������  : �ӿ��ж�ȡEF-HOME(HOME SID NID LIST)�Ĵ���
 �������  : pstMsg:struct MsgCB
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��5��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��02��05��
   ��    ��   : h00313353
   �޸�����   : Usimm���ӿڵ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCardReadFileCnf_EF_HOME(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile             = VOS_NULL_PTR;
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList   = VOS_NULL_PTR;
    VOS_UINT8                          *pucTmpdata          = VOS_NULL_PTR;
    VOS_UINT8                           ucRecNum;
    VOS_UINT32                          i;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* �ļ��Ķ�ȡʧ�ܣ����� */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_ProcCardReadFileCnf_EF_HOME:ERROR: Read Error:", pstFile->stCmdResult.ulErrorCode);

        return;
    }

    pucTmpdata = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XSD, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN);

    if (VOS_NULL_PTR == pucTmpdata)
    {
        return;
    }

    NAS_MEM_SET_S(pucTmpdata, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN, 0x00, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN);
    NAS_MEM_CPY_S(pucTmpdata, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN, pstFile->aucEf, pstFile->ucTotalNum * CNAS_XSD_HOME_SID_NID_LEN);

    pstHomeSidNidList = CNAS_CCB_GetHomeSidNidList();
    ucRecNum    = (VOS_UINT8)pstFile->ucTotalNum;

    /* ������ȳ������������������ֻȡ������ */
    if (ucRecNum > CNAS_CCB_MAX_HOME_SID_NID_LIST)
    {
         ucRecNum = CNAS_CCB_MAX_HOME_SID_NID_LIST;
    }

    i = 0;
    while (i < ucRecNum)
    {
        /*
          Bytes  Description                M/O     Length
          1 ~ 2  CDMA Home SID (SIDp)       M       2 bytes
          3 ~ 4  CDMA Home NID (NIDp)       M       2 bytes
          5      Band Class                 M       1 byte
          */
        pstHomeSidNidList->astHomeSidNid[i].usSid   = (VOS_UINT16)(pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN] | ((pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_1_OFFSET] & 0x7F) << CNAS_XSD_BIT_LEN_8_BIT));
        pstHomeSidNidList->astHomeSidNid[i].usNid   = (VOS_UINT16)(pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_2_OFFSET] | (pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_3_OFFSET] << CNAS_XSD_BIT_LEN_8_BIT));
        pstHomeSidNidList->astHomeSidNid[i].usBand  = (VOS_UINT16)(pucTmpdata[i * CNAS_XSD_HOME_SID_NID_LEN + CNAS_XSD_HOME_SID_NID_4_OFFSET] & 0x1F);
        i++;
    }

    PS_MEM_FREE(UEPS_PID_XSD, pucTmpdata);

    pstHomeSidNidList->ucSysNum = ucRecNum;
    CNAS_XSD_LogHomeSidNidList(pstHomeSidNidList);

    return;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





