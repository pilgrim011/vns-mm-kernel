/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHluSndHsm.c
  �� �� ��   : ����
  ��    ��   : y00213812
  ��������   : 2014��12��16��
  ����޸�   :
  ��������   : HLU���͸�HSM����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��16��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasHluSndHsm.h"
#include "PsCommonDef.h"
#include "CnasHluComm.h"
#include "CnasHluCtx.h"
#include "CnasMain.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_SND_HSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_HLU_SndHsmHandoffCnf(
    CNAS_HLU_HSM_1X_TO_HRPD_HANDOFF_RSLT_ENUM_UINT32             enHandOffResult
)
{
    HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU     *pstInternalMsg;

#if defined(DMT)
    pstInternalMsg = (HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU,
                                        sizeof(HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU));
#else
    /* alloc message memory*/
    pstInternalMsg = (HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HLU,
                                        sizeof(HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU));
#endif
    if (VOS_NULL_PTR == pstInternalMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_HsmSndHandoffCnf:"
                                        "memory allocation failure.");
        return;
    }

    NAS_MEM_SET_S((VOS_VOID*)pstInternalMsg, sizeof(HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU), 0, sizeof(HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU));
    CNAS_HLU_FILL_MSG_HDR(pstInternalMsg, UEPS_PID_HLU, UEPS_PID_HSM);

    /* set message */
    pstInternalMsg->enMsgId  = ID_HLU_HSM_1X_TO_HRPD_HANDOFF_CNF;

    pstInternalMsg->ulCause  = (VOS_UINT32)enHandOffResult;


    pstInternalMsg->ulLength = sizeof(HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU)
                                    - VOS_MSG_HEAD_LENGTH;
#if defined (DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstInternalMsg);
#else
    /* send message */
    (VOS_VOID)CNAS_SndInternalMsg(pstInternalMsg);
#endif

    return;
}



VOS_VOID CNAS_HLU_UpdateHsmLocValue(
    const CNAS_HLU_CTX_STRU            *pstLocVal
)
{
    HLU_HSM_LOC_CHANGED_IND_STRU       *pstInternalMsg;

#if defined(DMT)
    pstInternalMsg = (HLU_HSM_LOC_CHANGED_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU,
                                        sizeof(HLU_HSM_LOC_CHANGED_IND_STRU));
#else
    /* alloc message memory*/
    pstInternalMsg = (HLU_HSM_LOC_CHANGED_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HLU,
                                        sizeof(HLU_HSM_LOC_CHANGED_IND_STRU));
#endif

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_UpdateHsmLocValue:"
                                        "memory allocation failure.");
        return;
    }

    NAS_MEM_SET_S((VOS_VOID*)pstInternalMsg, sizeof(HLU_HSM_LOC_CHANGED_IND_STRU), 0, sizeof(HLU_HSM_LOC_CHANGED_IND_STRU));

    CNAS_HLU_FILL_MSG_HDR(pstInternalMsg, UEPS_PID_HLU, UEPS_PID_HSM);

    /* set message */
    pstInternalMsg->enMsgId             = ID_HLU_HSM_LOC_CHANGED_IND;
    pstInternalMsg->usSid               = pstLocVal->stLocCtx.stLocVal.usSID;
    pstInternalMsg->usNid               = pstLocVal->stLocCtx.stLocVal.usNID;
    pstInternalMsg->ucPktZoneId         = pstLocVal->stLocCtx.stLocVal.ucPacketZoneID;
    pstInternalMsg->ulLength            = sizeof(HLU_HSM_LOC_CHANGED_IND_STRU)
                                           - VOS_MSG_HEAD_LENGTH;
    /* TODO: need to add value for pstHandOffCnf->ucCause after discussion with HSM team */

#if defined (DMT)
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstInternalMsg);
#else
    /* send message */
    (VOS_VOID)CNAS_SndInternalMsg(pstInternalMsg);
#endif

    return;

}



CNAS_HLU_HSM_1X_TO_HRPD_HANDOFF_RSLT_ENUM_UINT32 CNAS_HLU_GetHandOffRslt(
    CTTF_HRPD_SNP_RSLT_ENUM_UINT32      enHandOffRslt
)
{
    if (CTTF_HRPD_SNP_RLST_SUCC == enHandOffRslt)
    {

        return CNAS_HLU_HSM_HANDOFF_SUCCESS;
    }
    else
    {
        return CNAS_HLU_HSM_HANDOFF_FAILURE;
    }
}


/*lint -restore*/

#endif







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


