


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/


#include "PsCommonDef.h"
#include "TafApsApi.h"
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "Taf_Aps.h"
#include "TafApsMntn.h"
#endif



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_API_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 �ⲿ��������
*****************************************************************************/

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
);
#endif


/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_PS_SndMsg
 ��������  : ����PS����Ϣ
 �������  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��21��
    ��    ��   : l00227485
    �޸�����   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_PS_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult = 0;
    TAF_PS_MSG_STRU                    *pstMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulPid;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    TAF_CTRL_STRU                      *pstCtrl  = VOS_NULL_PTR;

    pstCtrl = (TAF_CTRL_STRU *)pData;

    /* ��д��Ϣͷ */
    ulPid = AT_GetDestPid(pstCtrl->usClientId, ulTaskId);
#else
    ulPid = WUEPS_PID_TAF;
#endif

    /* ������Ϣ */
    pstMsg = (TAF_PS_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                ulPid,
                                sizeof(MSG_HEADER_STRU) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->stHeader.ulReceiverPid      = ulPid;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    /* ��д��Ϣ���� */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* ������Ϣ */
    ulResult = PS_SEND_MSG(ulPid, pstMsg);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetPrimPdpContextInfo
 ��������  : ����Primary PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstPdpContextInfo          - Primary PDP��������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�����޸ģ�����PID

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpContextInfo
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stSetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ��Ϣ */
    stSetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpCtxInfoReq.stPdpContextInfo  = *pstPdpContextInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ,
                             &stSetPdpCtxInfoReq,
                             sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetPrimPdpContextInfo
 ��������  : ��ȡPrimary PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�����޸ģ�����PID

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stGetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ,
                             &stGetPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetPdpContextInfo
 ��������  : ��ȡ���ʹ� PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : c00173809
    �޸�����   : DTS2012010604900
*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU        stGetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDPCONT_INFO_REQ,
                             &stGetPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetSecPdpContextInfo
 ��������  : ����Secondary PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstPdpContextInfo          - Secondary PDP��������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pstPdpContextInfo
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU    stSetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ��Ϣ */
    stSetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpCtxInfoReq.stPdpContextInfo  = *pstPdpContextInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ,
                             &stSetPdpCtxInfoReq,
                             sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetSecPdpContextInfo
 ��������  : ��ȡSecondary PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU    stGetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ,
                             &stGetPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetTftInfo
 ��������  : ����PDP TFT����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstTftInfo                 - TFT����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_TFT_INFO_REQ_STRU        stSetTftInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetTftInfoReq, 0x00, sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_TFT_INFO_REQ��Ϣ */
    stSetTftInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetTftInfoReq.stCtrl.usClientId = usClientId;
    stSetTftInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetTftInfoReq.stTftInfo         = *pstTftInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_TFT_INFO_REQ,
                             &stSetTftInfoReq,
                             sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetTftInfo
 ��������  : ��ȡPDP TFT����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_TFT_INFO_REQ_STRU        stGetTftInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetTftInfoReq, 0x00, sizeof(TAF_PS_GET_TFT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetTftInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetTftInfoReq.stCtrl.usClientId = usClientId;
    stGetTftInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_TFT_INFO_REQ,
                             &stGetTftInfoReq,
                             sizeof(TAF_PS_GET_TFT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetUmtsQosInfo
 ��������  : ����UMTS QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstUmtsQosInfo             - UMTS QOS����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU   stSetUmtsQosInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetUmtsQosInfoReq, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ��Ϣ */
    stSetUmtsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetUmtsQosInfoReq.stCtrl.usClientId = usClientId;
    stSetUmtsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetUmtsQosInfoReq.stUmtsQosInfo     = *pstUmtsQosInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ,
                             &stSetUmtsQosInfoReq,
                             sizeof(TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetUmtsQosInfo
 ��������  : ��ȡUMTS QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU   stGetUmtsQosInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetUmtsQosInfoReq, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ��Ϣ */
    stGetUmtsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetUmtsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetUmtsQosInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ,
                             &stGetUmtsQosInfoReq,
                             sizeof(TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetUmtsQosMinInfo
 ��������  : ����UMTS MIN QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstUmtsQosMinInfo          - UMTS MIN QOS����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosMinInfo
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU   stSetUmtsQosMinInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetUmtsQosMinInfoReq, 0x00, sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ��Ϣ */
    stSetUmtsQosMinInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetUmtsQosMinInfoReq.stCtrl.usClientId = usClientId;
    stSetUmtsQosMinInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetUmtsQosMinInfoReq.stUmtsQosMinInfo  = *pstUmtsQosMinInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ,
                             &stSetUmtsQosMinInfoReq,
                             sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetUmtsQosMinInfo
 ��������  : ��ȡUMTS MIN QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetUmtsQosMinInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU   stGetUmtsQosMinInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetUmtsQosMinInfoReq, 0x00, sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ��Ϣ */
    stGetUmtsQosMinInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetUmtsQosMinInfoReq.stCtrl.usClientId = usClientId;
    stGetUmtsQosMinInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ,
                             &stGetUmtsQosMinInfoReq,
                             sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDynamicUmtsQosInfo
 ��������  : ��ȡ��̬UMTS QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstCidListInfo             - CID�б�
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicUmtsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU   stGetDynamicUmtsQosInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicUmtsQosInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ��Ϣ */
    stGetDynamicUmtsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicUmtsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicUmtsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicUmtsQosInfoReq.stCidListInfo     = *pstCidListInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ,
                             &stGetDynamicUmtsQosInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetPdpContextState
 ��������  : ����ָ��CID(��)��Ӧ��PDP��״̬
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstCidListStateInfo        - CID�б�״̬
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STATE_STRU            *pstCidListStateInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_PDP_STATE_REQ_STRU       stSetPdpStateReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpStateReq, 0x00, sizeof(TAF_PS_SET_PDP_STATE_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_PDP_STATE_REQ��Ϣ */
    stSetPdpStateReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpStateReq.stCtrl.usClientId = usClientId;
    stSetPdpStateReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpStateReq.stCidListStateInfo   = *pstCidListStateInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                             &stSetPdpStateReq,
                             sizeof(TAF_PS_SET_PDP_STATE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetPdpContextState
 ��������  : ��ȡ�����Ѷ���CID��Ӧ��PDP��״̬
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpContextState(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_PDP_STATE_REQ_STRU       stGetPdpStateReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpStateReq, 0x00, sizeof(TAF_PS_GET_PDP_STATE_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_PDP_STATE_REQ��Ϣ */
    stGetPdpStateReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpStateReq.stCtrl.usClientId = usClientId;
    stGetPdpStateReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDP_CONTEXT_STATE_REQ,
                             &stGetPdpStateReq,
                             sizeof(TAF_PS_GET_PDP_STATE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_CallModify
 ��������  : �޸�PS CALL����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             TAF_CID_LIST_STRU          - CID�б�
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_CallModify(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_MODIFY_REQ_STRU         stCallModifyReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallModifyReq, 0x00, sizeof(TAF_PS_CALL_MODIFY_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ */
    stCallModifyReq.stCtrl.ulModuleId = ulModuleId;
    stCallModifyReq.stCtrl.usClientId = usClientId;
    stCallModifyReq.stCtrl.ucOpId     = ucOpId;
    stCallModifyReq.stCidListInfo     = *pstCidListInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                             &stCallModifyReq,
                             sizeof(TAF_PS_CALL_MODIFY_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_CallAnswer
 ��������  : Ӧ��PS CALL
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstAnsInfo                 - PS CALLӦ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_CallAnswer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_ANSWER_STRU                 *pstAnsInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ANSWER_REQ_STRU         stCallAnswerReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallAnswerReq, 0x00, sizeof(TAF_PS_CALL_ANSWER_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ */
    stCallAnswerReq.stCtrl.ulModuleId = ulModuleId;
    stCallAnswerReq.stCtrl.usClientId = usClientId;
    stCallAnswerReq.stCtrl.ucOpId     = ucOpId;
    stCallAnswerReq.stAnsInfo         = *pstAnsInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                             &stCallAnswerReq,
                             sizeof(TAF_PS_CALL_ANSWER_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_CallHangup
 ��������  : �Ҷ�PS CALL
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_CallHangup(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_HANGUP_REQ_STRU         stCallHangupReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallHangupReq, 0x00, sizeof(TAF_PS_CALL_HANGUP_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ */
    stCallHangupReq.stCtrl.ulModuleId = ulModuleId;
    stCallHangupReq.stCtrl.usClientId = usClientId;
    stCallHangupReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                             &stCallHangupReq,
                             sizeof(TAF_PS_CALL_HANGUP_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_CallOrig
 ��������  : ����PS CALL
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstDialParaInfo            - PS CALL����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_CallOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_ORIG_REQ_STRU           stCallOrigReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallOrigReq, 0x00, sizeof(TAF_PS_CALL_ORIG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ */
    stCallOrigReq.stCtrl.ulModuleId = ulModuleId;
    stCallOrigReq.stCtrl.usClientId = usClientId;
    stCallOrigReq.stCtrl.ucOpId     = ucOpId;
    stCallOrigReq.stDialParaInfo    = *pstDialParaInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_ORIG_REQ,
                             &stCallOrigReq,
                             sizeof(TAF_PS_CALL_ORIG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_CallEnd
 ��������  : ����PS CALL
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_CallEnd(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CALL_END_REQ_STRU            stCallEndReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stCallEndReq, 0x00, sizeof(TAF_PS_CALL_END_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ */
    stCallEndReq.stCtrl.ulModuleId = ulModuleId;
    stCallEndReq.stCtrl.usClientId = usClientId;
    stCallEndReq.stCtrl.ucOpId     = ucOpId;
    stCallEndReq.ucCid             = ucCid;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CALL_END_REQ,
                             &stCallEndReq,
                             sizeof(TAF_PS_CALL_END_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetPdpIpAddrInfo
 ��������  : ��ȡָ��CID(��)��PDP IP��ַ��Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstCidListInfo             - CID�б�
�������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpIpAddrInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_CID_LIST_STRU                  *pstCidListInfo
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU    stGetPdpIpAddrReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpIpAddrReq, 0x00, sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ��Ϣ */
    stGetPdpIpAddrReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpIpAddrReq.stCtrl.usClientId = usClientId;
    stGetPdpIpAddrReq.stCtrl.ucOpId     = ucOpId;
    stGetPdpIpAddrReq.stCidListInfo     = *pstCidListInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ,
                             &stGetPdpIpAddrReq,
                             sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetAnsModeInfo
 ��������  : ����PS�����Ӧ��ģʽ��Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ulAnsMode                  - Ӧ��ģʽ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulAnsMode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU    stSetAnsModeReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetAnsModeReq, 0x00, sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ��Ϣ */
    stSetAnsModeReq.stCtrl.ulModuleId = ulModuleId;
    stSetAnsModeReq.stCtrl.usClientId = usClientId;
    stSetAnsModeReq.stCtrl.ucOpId     = ucOpId;
    stSetAnsModeReq.ulAnsMode         = ulAnsMode;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ,
                             &stSetAnsModeReq,
                             sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetAnsModeInfo
 ��������  : ��ȡPS�����Ӧ��ģʽ��Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetAnsModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU    stGetAnsModeReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetAnsModeReq, 0x00, sizeof(TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ��Ϣ */
    stGetAnsModeReq.stCtrl.ulModuleId   = ulModuleId;
    stGetAnsModeReq.stCtrl.usClientId   = usClientId;
    stGetAnsModeReq.stCtrl.ucOpId       = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ,
                             &stGetAnsModeReq,
                             sizeof(TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDynamicPrimPdpContextInfo
 ��������  : ��ȡָ�����Ѷ���CID�Ķ�̬Primary PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicPrimPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                          ulResult;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU   stGetDynamicPrimPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicPrimPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetDynamicPrimPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicPrimPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicPrimPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicPrimPdpCtxInfoReq.ucCid             = ucCid;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ,
                             &stGetDynamicPrimPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDynamicSecPdpContextInfo
 ��������  : ��ȡָ�����Ѷ���CID�Ķ�̬Secondary PDP��������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicSecPdpContextInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                          ulResult;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU    stGetDynamicSecPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicSecPdpCtxInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetDynamicSecPdpCtxInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicSecPdpCtxInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicSecPdpCtxInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicSecPdpCtxInfoReq.ucCid             = ucCid;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ,
                             &stGetDynamicSecPdpCtxInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDynamicTftInfo
 ��������  : ��ȡָ�����Ѷ���CID�Ķ�̬TFT��Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicTftInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU    stGetDynamicTftInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicTftInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ��Ϣ */
    stGetDynamicTftInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicTftInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicTftInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicTftInfoReq.ucCid             = ucCid;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ,
                             &stGetDynamicTftInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetEpsQosInfo
 ��������  : ����ָ��CID��EPS QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstEpsQosInfo              - EPS QOS������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU    stSetEpsQosInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetEpsQosInfoReq, 0x00, sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ��Ϣ */
    stSetEpsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetEpsQosInfoReq.stCtrl.usClientId = usClientId;
    stSetEpsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetEpsQosInfoReq.stEpsQosInfo      = *pstEpsQosInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ,
                             &stSetEpsQosInfoReq,
                             sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetEpsQosInfo
 ��������  : ��ȡEPS QOS������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_EPS_QOS_INFO_REQ_STRU    stGetEpsQosInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetEpsQosInfoReq, 0x00, sizeof(TAF_PS_GET_EPS_QOS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ��Ϣ */
    stGetEpsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetEpsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetEpsQosInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ,
                             &stGetEpsQosInfoReq,
                             sizeof(TAF_PS_GET_EPS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDynamicEpsQosInfo
 ��������  : ��ȡָ�����Ѷ���CID�Ķ�̬EPS QOS����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicEpsQosInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU    stGetDynamicEpsQosInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDynamicEpsQosInfoReq, 0x00, sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ��Ϣ */
    stGetDynamicEpsQosInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDynamicEpsQosInfoReq.stCtrl.usClientId = usClientId;
    stGetDynamicEpsQosInfoReq.stCtrl.ucOpId     = ucOpId;
    stGetDynamicEpsQosInfoReq.ucCid             = ucCid;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ,
                             &stGetDynamicEpsQosInfoReq,
                             sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDsFlowInfo
 ��������  : ��ȡ����������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstQueryConfigInfo         - DSFLOW��ѯ���ò���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_DSFLOW_INFO_REQ_STRU     stGetDsFlowInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetDsFlowInfoReq, 0x00, sizeof(TAF_PS_GET_DSFLOW_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ��Ϣ */
    stGetDsFlowInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetDsFlowInfoReq.stCtrl.usClientId = usClientId;
    stGetDsFlowInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ,
                             &stGetDsFlowInfoReq,
                             sizeof(TAF_PS_GET_DSFLOW_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_ClearDsFlowInfo
 ��������  : �������������Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstClearConfigInfo         - ����������ò�����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_ClearDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_CLEAR_CONFIG_STRU       *pstClearConfigInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CLEAR_DSFLOW_REQ_STRU        stClearDsFlowReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stClearDsFlowReq, 0x00, sizeof(TAF_PS_CLEAR_DSFLOW_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ��Ϣ */
    stClearDsFlowReq.stCtrl.ulModuleId = ulModuleId;
    stClearDsFlowReq.stCtrl.usClientId = usClientId;
    stClearDsFlowReq.stCtrl.ucOpId     = ucOpId;
    stClearDsFlowReq.stClearConfigInfo = *pstClearConfigInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ,
                             &stClearDsFlowReq,
                             sizeof(TAF_PS_CLEAR_DSFLOW_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_ConfigDsFlowRpt
 ��������  : ���������ϱ�ģʽ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstReportConfigInfo        - �����ϱ����ò�����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigDsFlowRpt(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_REPORT_CONFIG_STRU      *pstReportConfigInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU   stConfigDsFlowRptReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stConfigDsFlowRptReq, 0x00, sizeof(TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ��Ϣ */
    stConfigDsFlowRptReq.stCtrl.ulModuleId = ulModuleId;
    stConfigDsFlowRptReq.stCtrl.usClientId = usClientId;
    stConfigDsFlowRptReq.stCtrl.ucOpId     = ucOpId;
    stConfigDsFlowRptReq.stReportConfigInfo   = *pstReportConfigInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ,
                             &stConfigDsFlowRptReq,
                             sizeof(TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetPdpDnsInfo
 ��������  : ����PDP DNS��Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstPdpDnsInfo              - PDP DNS��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_DNS_EXT_STRU               *pstPdpDnsInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_PDP_DNS_INFO_REQ_STRU    stSetPdpDnsInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpDnsInfoReq, 0x00, sizeof(TAF_PS_SET_PDP_DNS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ��Ϣ */
    stSetPdpDnsInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpDnsInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpDnsInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpDnsInfoReq.stPdpDnsInfo      = *pstPdpDnsInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ,
                             &stSetPdpDnsInfoReq,
                             sizeof(TAF_PS_SET_PDP_DNS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetPdpDnsInfo
 ��������  : ��ȡPDP DNS��Ϣ
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetPdpDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_PDP_DNS_INFO_REQ_STRU    stGetPdpDnsInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetPdpDnsInfoReq, 0x00, sizeof(TAF_PS_GET_PDP_DNS_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ��Ϣ */
    stGetPdpDnsInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetPdpDnsInfoReq.stCtrl.usClientId = usClientId;
    stGetPdpDnsInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ,
                             &stGetPdpDnsInfoReq,
                             sizeof(TAF_PS_GET_PDP_DNS_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_TrigGprsData
 ��������  : ��������GPRS����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstGprsDataInfo            - GPRS������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_TrigGprsData(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_GPRS_DATA_STRU                 *pstGprsDataInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_TRIG_GPRS_DATA_REQ_STRU      stTrigGprsDataReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stTrigGprsDataReq, 0x00, sizeof(TAF_PS_TRIG_GPRS_DATA_REQ_STRU));

    /* ����ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ��Ϣ */
    stTrigGprsDataReq.stCtrl.ulModuleId = ulModuleId;
    stTrigGprsDataReq.stCtrl.usClientId = usClientId;
    stTrigGprsDataReq.stCtrl.ucOpId     = ucOpId;
    stTrigGprsDataReq.stGprsDataInfo    = *pstGprsDataInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ,
                             &stTrigGprsDataReq,
                             sizeof(TAF_PS_TRIG_GPRS_DATA_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_ConfigNbnsFunction
 ��������  : ����NBNS����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ulEnabled                  - NBNS����ʹ�ܱ��
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_ConfigNbnsFunction(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulEnabled
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU    stConfigNbnsFunReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stConfigNbnsFunReq, 0x00, sizeof(TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU));

    /* ����ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ��Ϣ */
    stConfigNbnsFunReq.stCtrl.ulModuleId = ulModuleId;
    stConfigNbnsFunReq.stCtrl.usClientId = usClientId;
    stConfigNbnsFunReq.stCtrl.ucOpId     = ucOpId;
    stConfigNbnsFunReq.ulEnabled         = ulEnabled;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ,
                             &stConfigNbnsFunReq,
                             sizeof(TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU));

    return ulResult;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/*****************************************************************************
 �� �� ��  : TAF_PS_SetAuthDataInfo
 ��������  : ���ü�Ȩ������Ϣ(NDIS)
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstAuthDataInfo            - ��Ȩ����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_AUTHDATA_EXT_STRU              *pstAuthDataInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU   stSetAuthDataInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetAuthDataInfoReq, 0x00, sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ��Ϣ */
    stSetAuthDataInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetAuthDataInfoReq.stCtrl.usClientId = usClientId;
    stSetAuthDataInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetAuthDataInfoReq.stAuthDataInfo    = *pstAuthDataInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ,
                             &stSetAuthDataInfoReq,
                             sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetAuthDataInfo
 ��������  : ��ȡ��Ȩ������Ϣ(NDIS)
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetAuthDataInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_AUTHDATA_INFO_REQ_STRU   stGetAuthDataInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetAuthDataInfoReq, 0x00, sizeof(TAF_PS_GET_AUTHDATA_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ��Ϣ */
    stGetAuthDataInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetAuthDataInfoReq.stCtrl.usClientId = usClientId;
    stGetAuthDataInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ,
                             &stGetAuthDataInfoReq,
                             sizeof(TAF_PS_GET_AUTHDATA_INFO_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetGprsActiveType
 ��������  : ��ȡD����GPRS����(PPP����)
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstAtdPara                 - D����Ų���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetGprsActiveType(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_ATD_PARA_STRU                  *pstAtdPara
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU  stGetGprsActiveTypeReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetGprsActiveTypeReq, 0x00, sizeof(TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ��Ϣ */
    stGetGprsActiveTypeReq.stCtrl.ulModuleId = ulModuleId;
    stGetGprsActiveTypeReq.stCtrl.usClientId = usClientId;
    stGetGprsActiveTypeReq.stCtrl.ucOpId     = ucOpId;
    stGetGprsActiveTypeReq.stAtdPara         = *pstAtdPara;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ,
                             &stGetGprsActiveTypeReq,
                             sizeof(TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_PppDialOrig
 ��������  : ����PPP����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
             pstPppReqConfigInfo        - PPP���ò���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��5��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��5��16��
    ��    ��   : A00165503
    �޸�����   : DTS2014050703206: PPP���Žӿڵ���
*****************************************************************************/
VOS_UINT32 TAF_PS_PppDialOrig(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid,
    TAF_PPP_REQ_CONFIG_INFO_STRU       *pstPppReqConfigInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU       stPppDialOrigReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stPppDialOrigReq, 0x00, sizeof(TAF_PS_PPP_DIAL_ORIG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ */
    stPppDialOrigReq.stCtrl.ulModuleId          = ulModuleId;
    stPppDialOrigReq.stCtrl.usClientId          = usClientId;
    stPppDialOrigReq.stCtrl.ucOpId              = ucOpId;

    stPppDialOrigReq.stPppDialParaInfo.ucCid    = ucCid;

    stPppDialOrigReq.stPppDialParaInfo.bitOpPppConfigInfo = VOS_TRUE;
    PS_MEM_CPY(&(stPppDialOrigReq.stPppDialParaInfo.stPppReqConfigInfo),
               pstPppReqConfigInfo,
               sizeof(TAF_PPP_REQ_CONFIG_INFO_STRU));

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                             &stPppDialOrigReq,
                             sizeof(TAF_PS_PPP_DIAL_ORIG_REQ_STRU));

    return ulResult;
}

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
�� �� ��  : TAF_PS_GetLteCsInfo
��������  : ��ȡLTE CS Info
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
            VOS_ERR                    - ������Ϣʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2012��02��23��
   ��    ��   : h00135900
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_GetLteCsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId

)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_LTECS_REQ_STRU   stGetLteCsInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetLteCsInfoReq, 0x00, sizeof(TAF_PS_LTECS_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetLteCsInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetLteCsInfoReq.stCtrl.usClientId = usClientId;
    stGetLteCsInfoReq.stCtrl.ucOpId     = ucOpId;


    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_LTE_CS_REQ,
                             &stGetLteCsInfoReq,
                             sizeof(TAF_PS_LTECS_REQ_STRU));


    return ulResult;
}

/*****************************************************************************
�� �� ��  : TAF_PS_GetCemodeInfo
��������  : ��ȡCEMODE Info
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
            VOS_ERR                    - ������Ϣʧ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2012��03��20��
   ��    ��   : w00182550
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_GetCemodeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                                  ulResult;
    TAF_PS_CEMODE_REQ_STRU   stGetCemodeInfoReq;



    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stGetCemodeInfoReq, 0x00, sizeof(TAF_PS_CEMODE_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ��Ϣ */
    stGetCemodeInfoReq.stCtrl.ulModuleId = ulModuleId;
    stGetCemodeInfoReq.stCtrl.usClientId = usClientId;
    stGetCemodeInfoReq.stCtrl.ucOpId     = ucOpId;


    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CEMODE_REQ,
                             &stGetCemodeInfoReq,
                             sizeof(TAF_PS_CEMODE_REQ_STRU));


    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetPdpProfInfo
 ��������  : ����PDP_Profile ����
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             stPdpProfInfo            - PDP_Profile ����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 ��    ��   : 2012��3��12��
 ��    ��   : x00126983
 �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetPdpProfInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PROFILE_EXT_STRU           *stPdpProfInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_PROFILE_INFO_REQ_STRU    stSetPdpProfInfoReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetPdpProfInfoReq, 0x00, sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ��Ϣ */
    stSetPdpProfInfoReq.stCtrl.ulModuleId = ulModuleId;
    stSetPdpProfInfoReq.stCtrl.usClientId = usClientId;
    stSetPdpProfInfoReq.stCtrl.ucOpId     = ucOpId;
    stSetPdpProfInfoReq.stPdpProfInfo     = *stPdpProfInfo;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ,
                             &stSetPdpProfInfoReq,
                             sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU));

    return ulResult;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_PS_GetCidSdfParaInfo
 ��������  : ��ȡ����NV���е�SDF������Ϣ, ֧��ͬ�����첽���ַ�ʽ
             ��������ǿ� --- ͬ����ʽ(Ŀǰ��֧��C��)
             �������Ϊ�� --- �첽��ʽ
 �������  : ulModuleId                 - ��дPID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : pstSdfQueryInfo            - SDF������Ϣ
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��

�޸���ʷ  :

1.��    ��   : 2013��07��08��
  ��    ��   : Y00213812
  �޸�����   : VoLTE_PhaseI ��Ŀ������API

*****************************************************************************/
VOS_UINT32 TAF_PS_GetCidSdfParaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo
)
{
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    VOS_UINT8                           ucNum;
#endif
    VOS_UINT32                          ulResult;
    TAF_PS_SDF_INFO_REQ_STRU            stSdfInfoReq;

    ulResult = VOS_ERR;
    PS_MEM_SET(&stSdfInfoReq, 0x00, sizeof(TAF_PS_SDF_INFO_REQ_STRU));

    /* �������Ϊ�գ�������첽��ʽ��ȡSDF��Ϣ */
    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /* ����ID_MSG_TAF_GET_CID_SDF_REQ��Ϣ */
        stSdfInfoReq.stCtrl.ulModuleId = ulModuleId;
        stSdfInfoReq.stCtrl.usClientId = usClientId;
        stSdfInfoReq.stCtrl.ucOpId     = ucOpId;

        /* ������Ϣ */
        ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                                 ID_MSG_TAF_PS_GET_CID_SDF_REQ,
                                 &stSdfInfoReq,
                                 sizeof(TAF_PS_SDF_INFO_REQ_STRU));

        return ulResult;
    }

    PS_MEM_SET(pstSdfQueryInfo, 0, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));
/* ͬ����ʽĿǰ��֧��C�� */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    for (ucNum = 1; ucNum <= TAF_MAX_CID_NV; ucNum++)
    {
        if (VOS_OK == TAF_APS_GetSdfParaInfo(ucNum,
                              &(pstSdfQueryInfo->astSdfPara[pstSdfQueryInfo->ulSdfNum])))
        {
            pstSdfQueryInfo->ulSdfNum ++;
        }
    }
    ulResult = VOS_OK;

    /* ͬ����Ϣ���� */
    TAF_APS_TraceSyncMsg(ID_MSG_TAF_PS_GET_CID_SDF_REQ,
                         (VOS_UINT8 *)pstSdfQueryInfo,
                         sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));
#endif

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : TAF_PS_GetUnusedCid
 ��������  : ��ȡ����δ�����CID
             ��������ǿ� --- ͬ����ʽ(Ŀǰ��֧��C��)
             �������Ϊ�� --- �첽��ʽ
 �������  : ulModuleId                 - ��дPID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : puCid                      - ����δ����CID
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��

 �޸���ʷ  :

 1.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������API
*****************************************************************************/
VOS_UINT32 TAF_PS_GetUnusedCid(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *puCid
)
{
    VOS_UINT32                          ulResult;

    ulResult = VOS_OK;

    if (VOS_NULL_PTR == puCid)
    {
        /* Ŀǰ�ݲ�֧���첽��ʽ */
        return VOS_ERR;
    }

/* ͬ����ʽĿǰ��֧��C�� */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    /* ���ҿ����ڲ��ŵ�CID */
    *puCid = TAF_APS_FindCidForDial(ulModuleId);
    if ( TAF_INVALID_CID == *puCid )
    {
        ulResult = VOS_ERR;
    }

    /* ͬ����Ϣ���� */
    TAF_APS_TraceSyncMsg(ID_MSG_TAF_PS_GET_UNUSED_CID_REQ,
                         puCid,
                         sizeof(VOS_UINT8));
#endif

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDynamicDnsInfo
 ��������  : ��ȡָ��CID��DNS��Ϣ
 �������  : ulModuleId                 - ��дPID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucCid                      - CID
 �������  : ��

 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 �޸���ʷ  :

 1.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������API

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDynamicDnsInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          ulResult;

    TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU stNegoDns;

    /* ��ʼ�� */
    PS_MEM_SET(&stNegoDns, 0x00, sizeof(TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU));

    /* �����Ϣ�ṹ */
    stNegoDns.stCtrl.ulModuleId = ulModuleId;
    stNegoDns.stCtrl.usClientId = usClientId;
    stNegoDns.stCtrl.ucOpId     = ucOpId;
    stNegoDns.ucCid             = ucCid;

    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ,
                             &stNegoDns,
                             sizeof(TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetCqosPriInfo
 ��������  : ����CDMA QOS ����
 �������  : VOS_UINT32                                      ulModuleId
             VOS_UINT16                                      usClientId
             TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8  enPri
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetCqosPriInfo(
    VOS_UINT32                                      ulModuleId,
    VOS_UINT16                                      usClientId,
    TAF_PS_CDATA_1X_QOS_NON_ASSURED_PRI_ENUM_UINT8  enPri
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_1X_CQOS_PRI_REQ_STRU     stSetCqosPriReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetCqosPriReq, 0x00, sizeof(TAF_PS_SET_1X_CQOS_PRI_REQ_STRU));

    /* ����TAF_PS_SET_CQOS_PRI_REQ_STRU��Ϣ */
    stSetCqosPriReq.stCtrl.ulModuleId = ulModuleId;
    stSetCqosPriReq.stCtrl.usClientId = usClientId;
    stSetCqosPriReq.stCtrl.ucOpId     = 0;
    stSetCqosPriReq.enPri             = enPri;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CQOS_PRI_REQ,
                             &stSetCqosPriReq,
                             sizeof(TAF_PS_SET_1X_CQOS_PRI_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetApDsFlowRptCfg
 ��������  : ����AP�����ϱ�����
 �������  : ulModuleId                 - PID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstRptCfg                  - ���ò���
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_SetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU    stSetRptCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stSetRptCfgReq, 0x00, sizeof(TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ��Ϣ */
    stSetRptCfgReq.stCtrl.ulModuleId = ulModuleId;
    stSetRptCfgReq.stCtrl.usClientId = usClientId;
    stSetRptCfgReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&(stSetRptCfgReq.stRptCfg),
               pstRptCfg,
               sizeof(TAF_APDSFLOW_RPT_CFG_STRU));

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ,
                             &stSetRptCfgReq,
                             sizeof(TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetApDsFlowRptCfg
 ��������  : ��ȡAP�����ϱ�����
 �������  : ulModuleId                 - PID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_GetApDsFlowRptCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU    stGetRptCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stGetRptCfgReq, 0x00, sizeof(TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ��Ϣ */
    stGetRptCfgReq.stCtrl.ulModuleId = ulModuleId;
    stGetRptCfgReq.stCtrl.usClientId = usClientId;
    stGetRptCfgReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ,
                             &stGetRptCfgReq,
                             sizeof(TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetDsFlowNvWriteCfg
 ��������  : ��������дNV����
 �������  : ulModuleId                 - PID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstNvWriteCfg              - ����дNV����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_SetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstNvWriteCfg
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU stSetWriteNvCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stSetWriteNvCfgReq, 0x00, sizeof(TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ��Ϣ */
    stSetWriteNvCfgReq.stCtrl.ulModuleId = ulModuleId;
    stSetWriteNvCfgReq.stCtrl.usClientId = usClientId;
    stSetWriteNvCfgReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&(stSetWriteNvCfgReq.stNvWriteCfg),
               pstNvWriteCfg,
               sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ,
                             &stSetWriteNvCfgReq,
                             sizeof(TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetDsFlowNvWriteCfg
 ��������  : ��ȡ����дNV����
 �������  : ulModuleId                 - PID
             usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetDsFlowNvWriteCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU stGetNvWriteCfgReq;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stGetNvWriteCfgReq, 0x00, sizeof(TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_DSFLOW_WRITE_NV_CFG_REQ��Ϣ */
    stGetNvWriteCfgReq.stCtrl.ulModuleId = ulModuleId;
    stGetNvWriteCfgReq.stCtrl.usClientId = usClientId;
    stGetNvWriteCfgReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ,
                             &stGetNvWriteCfgReq,
                             sizeof(TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetCtaInfo
 ��������  : ����aps no data time len
 �������  : VOS_UINT32                          ulModuleId,
             VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
             VOS_UINT8                           ucTimeLen
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucTimeLen
)
{
    TAF_PS_SET_CTA_INFO_REQ_STRU        stSetPktCdataInactivityTmrlenReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stSetPktCdataInactivityTmrlenReq, 0x00, sizeof(stSetPktCdataInactivityTmrlenReq));

    /* ����ID_MSG_TAF_PS_GET_DSFLOW_WRITE_NV_CFG_REQ��Ϣ */
    stSetPktCdataInactivityTmrlenReq.stCtrl.ulModuleId  = ulModuleId;
    stSetPktCdataInactivityTmrlenReq.stCtrl.usClientId  = usClientId;
    stSetPktCdataInactivityTmrlenReq.stCtrl.ucOpId      = ucOpId;


    stSetPktCdataInactivityTmrlenReq.ucPktCdataInactivityTmrLen = ucTimeLen;


    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CTA_INFO_REQ,
                             &stSetPktCdataInactivityTmrlenReq,
                             sizeof(stSetPktCdataInactivityTmrlenReq));

    return ulResult;
}
/*****************************************************************************
 �� �� ��  : TAF_PS_GetCtaInfo
 ��������  : ��ȡaps no data time len
 �������  : VOS_UINT32                          ulModuleId,
             VOS_UINT16                          usClientId,
             VOS_UINT8                           ucOpId,
 �������  : ��
 �� �� ֵ  : VOS_OK                     - �ɹ�
             VOS_ERR                    - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetCtaInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_CTA_INFO_REQ_STRU        stGetPktCdataInactivityTmrlenReq;
    VOS_UINT32                                              ulResult;

    PS_MEM_SET(&stGetPktCdataInactivityTmrlenReq, 0x00, sizeof(stGetPktCdataInactivityTmrlenReq));

    stGetPktCdataInactivityTmrlenReq.stCtrl.ulModuleId  = ulModuleId;
    stGetPktCdataInactivityTmrlenReq.stCtrl.usClientId  = usClientId;
    stGetPktCdataInactivityTmrlenReq.stCtrl.ucOpId      = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CTA_INFO_REQ,
                             &stGetPktCdataInactivityTmrlenReq,
                             sizeof(stGetPktCdataInactivityTmrlenReq));

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : TAF_PS_GetCgmtuInfo
 ��������  : TAF PS Proc CGMTU AT Qry Command
 �������  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_GetCgmtuInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_CGMTU_VALUE_REQ_STRU     stGetCgmtuValueReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stGetCgmtuValueReq, 0x00, sizeof(stGetCgmtuValueReq));

    stGetCgmtuValueReq.stCtrl.ulModuleId = ulModuleId;
    stGetCgmtuValueReq.stCtrl.usClientId = usClientId;
    stGetCgmtuValueReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CGMTU_VALUE_REQ,
                             &stGetCgmtuValueReq,
                             sizeof(stGetCgmtuValueReq));

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : TAF_PS_SetCdataDialModeInfo
 ��������  : ����CDMA  PPP���ݴ���ģʽ����
 �������  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32 enDialMode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��02��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_SetCdataDialModeInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    TAF_PS_CDATA_DIAL_MODE_ENUM_UINT32  enDialMode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CDATA_DIAL_MODE_REQ_STRU     stDialModeReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stDialModeReq, 0x00, sizeof(TAF_PS_CDATA_DIAL_MODE_REQ_STRU));

    /* ����TAF_PS_CDATA_DIAL_MODE_REQ_STRU��Ϣ */
    stDialModeReq.stCtrl.ulModuleId     = ulModuleId;
    stDialModeReq.stCtrl.usClientId     = usClientId;
    stDialModeReq.stCtrl.ucOpId         = 0;
    stDialModeReq.enDialMode            = enDialMode;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CDMA_DIAL_MODE_REQ,
                             &stDialModeReq,
                             sizeof(TAF_PS_CDATA_DIAL_MODE_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetImsPdpCfg
 ��������  : ����IMS PDP
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             pstImsPdpCfg               - IMS PDP����
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : z00301431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_SetImsPdpCfg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_IMS_PDP_CFG_STRU               *pstImsPdpCfg
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_IMS_PDP_CFG_REQ_STRU     stSetImsPdpCfgReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&stSetImsPdpCfgReq, 0x00, sizeof(TAF_PS_SET_IMS_PDP_CFG_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ��Ϣ */
    stSetImsPdpCfgReq.stCtrl.ulModuleId = ulModuleId;
    stSetImsPdpCfgReq.stCtrl.usClientId = usClientId;
    stSetImsPdpCfgReq.stCtrl.ucOpId     = ucOpId;
    stSetImsPdpCfgReq.stImsPdpCfg       = *pstImsPdpCfg;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_IMS_PDP_CFG_REQ,
                             &stSetImsPdpCfgReq,
                             sizeof(TAF_PS_SET_IMS_PDP_CFG_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_SetCdmaDormantTimer
 ��������  : ����DORMANT TIMER
 �������  : usClientId                 - �ͻ���ID
             ucOpId                     - ������ID
             ucDormantTimer             - ʱ��
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_PS_SetCdmaDormantTimer(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucDormantTimer
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_1X_DORM_TIMER_REQ_STRU   st1xDormTimerReq;

    /* ��ʼ�� */
    ulResult = VOS_OK;
    PS_MEM_SET(&st1xDormTimerReq, 0x00, sizeof(TAF_PS_SET_1X_DORM_TIMER_REQ_STRU));

    /* ����ID_MSG_TAF_PS_SET_1X_DORMANT_TIMER_REQ��Ϣ */
    st1xDormTimerReq.stCtrl.ulModuleId = ulModuleId;
    st1xDormTimerReq.stCtrl.usClientId = usClientId;
    st1xDormTimerReq.stCtrl.ucOpId     = ucOpId;
    st1xDormTimerReq.ucDormantTimer    = ucDormantTimer;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_1X_DORM_TIMER_REQ,
                             &st1xDormTimerReq,
                             sizeof(TAF_PS_SET_1X_DORM_TIMER_REQ_STRU));

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_ProcCdmaDormTimerQryReq
 ��������  : TAF PS Proc CDORMTIMER AT Qry Command
 �������  : VOS_UINT32                          ulModuleId
             VOS_UINT16                          usClientId
             VOS_UINT8                           ucOpId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��14��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_PS_ProcCdmaDormTimerQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PS_GET_1X_DORM_TIMER_REQ_STRU   stGet1xDormTimerReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stGet1xDormTimerReq, 0x00, sizeof(stGet1xDormTimerReq));

    stGet1xDormTimerReq.stCtrl.ulModuleId = ulModuleId;
    stGet1xDormTimerReq.stCtrl.usClientId = usClientId;
    stGet1xDormTimerReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_1X_DORM_TIEMR_REQ,
                             &stGet1xDormTimerReq,
                             sizeof(stGet1xDormTimerReq));

    return ulResult;
}




/*****************************************************************************
 �� �� ��  : TAF_PS_GetCdataBearStatus
 ��������  : ��ȡPPP��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_PS_GetCdataBearStatus(
    VOS_UINT8                                               ucPdpId
)
{
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 ucCdataBearStatus;

    ucCdataBearStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    ucCdataBearStatus = TAF_APS_GetCdataBearStatusCommFun(ucPdpId);
#endif
#endif

    return ucCdataBearStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_PS_GetPppStatus
 ��������  : ��ν�ɲ��ѯ��ǰPPP״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8  TAF_PS_GetPppStatus( VOS_VOID )
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 enCurrCdataStatus;
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 enPreCdataStatus;

    enCurrCdataStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;
    enPreCdataStatus = TAF_PS_CDATA_BEAR_STATUS_INACTIVE;

    for (ucPdpId = 0; ucPdpId < TAF_PS_MAX_PDPID; ucPdpId++)
    {
        enCurrCdataStatus = TAF_PS_GetCdataBearStatus(ucPdpId);
        if ((enPreCdataStatus < enCurrCdataStatus)
        && (TAF_PS_CDATA_BEAR_STATUS_BUTT != enCurrCdataStatus))
        {
            enPreCdataStatus = enCurrCdataStatus;
        }

    }
    return enPreCdataStatus;
}



/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
