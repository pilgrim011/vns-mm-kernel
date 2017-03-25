/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregSndAps.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��12��31��
  ����޸�   :
  ��������   : 1x REG(Register)����APS����Ϣ����
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��12��31��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXregSndAps.h"
#include  "xreg_aps_pif.h"
#include  "CnasXregProcess.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_SND_APS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : CNAS_XREG_SndApsRegBeginInd
 ��������  : ��APSģ�鷢��ID_XREG_APS_REG_BEGIN_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_SndApsRegBeginInd(VOS_VOID)
{
    XREG_APS_REG_BEGIN_IND_STRU        *pstMsg;
    VOS_UINT8                          *pucContent;
    CNAS_XREG_SYS_MSG_CONTENT_STRU     *pstSysMsgCont;

    /*������Ϣ*/
    pstMsg  = (XREG_APS_REG_BEGIN_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_XREG,
                        sizeof(XREG_APS_REG_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pucContent = (VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH;

    PS_MEM_SET(pucContent, 0, sizeof(XREG_APS_REG_BEGIN_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /*��д����*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId         = ID_XREG_APS_REG_BEGIN_IND;

    pstSysMsgCont = CNAS_XREG_GetSysMsgAddr();

    pstMsg->usSid           = pstSysMsgCont->stSysInfo.usSid;

    pstMsg->usNid           = pstSysMsgCont->stSysInfo.usNid;
    pstMsg->ucPzid          = pstSysMsgCont->stSysInfo.ucPacketZoneId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    PS_SEND_MSG(UEPS_PID_XREG, pstMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



