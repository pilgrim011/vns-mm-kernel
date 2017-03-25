/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallSndXsms.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��10��22��
  ��������   : TAF X CALL���͸�SMS����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "taf_xcall_xsms_pif.h"
#include "TafXCallSndXsms.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_SND_XSMS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendXsmsKmcMsgSendReq
 ��������  : ����XSMS����KMC��Ϣ
 �������  : usOpId -- ��ǰ��Ϣ�Ĳ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_SendXsmsKmcMsgSendReq(
    VOS_UINT16                          usOpId,
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucUserData
)
{
    XCALL_XSMS_KMC_MSG_SEND_REQ_STRU   *pstXsmsReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen   = sizeof(XCALL_XSMS_KMC_MSG_SEND_REQ_STRU) - 4 * sizeof(VOS_UINT8) + usDataLen;

    /* ������Ϣ */
    pstXsmsReq = (XCALL_XSMS_KMC_MSG_SEND_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, ulMsgLen);

    if (VOS_NULL_PTR == pstXsmsReq)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstXsmsReq + VOS_MSG_HEAD_LENGTH,
               0,
               ulMsgLen - VOS_MSG_HEAD_LENGTH);

    /* ��дVOS��Ϣͷ */
    pstXsmsReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstXsmsReq->ulSenderPid     = WUEPS_PID_TAF;
    pstXsmsReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstXsmsReq->ulReceiverPid   = UEPS_PID_XSMS;
    pstXsmsReq->ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstXsmsReq->enMsgId         = ID_XCALL_XSMS_KMC_MSG_SEND_REQ;
    pstXsmsReq->usOpId          = usOpId;
    pstXsmsReq->usDataLen       = usDataLen;

    PS_MEM_CPY(&(pstXsmsReq->aucData[0]),
               pucUserData,
               usDataLen);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstXsmsReq);
}
#endif

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


