/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallSendCst.c
  �� �� ��   : ����
  ��    ��   : h44270
  ��������   : 2010��5��18��
  ����޸�   :
  ��������   : ��CST��صĴ��봦��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��5��18��
    ��    ��   : h44270
    �޸�����   : �����ļ�

******************************************************************************/
#ifdef  __cplusplus
  #if  __cplusplus
          extern "C"{
  #endif
#endif
/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnCallTimer.h"
#include "MnCallApi.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "CstNasInterface.h"
#include "MnCallReqProc.h"

#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_CSTPROC_C


/*lint -save -e958 */

/*****************************************************************************
  2 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_CALL_ProcCstErrorInd
 ��������  : ����ID_CST_CC_ERROR_INDԭ��
 �������  : pMsg - CST����CC����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ,CS��������ϱ�
  4.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����
*****************************************************************************/
VOS_VOID  MN_CALL_ProcCstErrorInd(
    const VOS_VOID                      *pMsg
)
{
    MN_CALL_END_PARAM_STRU              stEndParm;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_INFO_STRU                   stCallInfo;
    VOS_UINT32                          ulRet;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

     stEndParm.enEndCause = MN_CALL_INTERWORKING_UNSPECIFIED;


    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    /* ���ҵ�ǰ���ڵ�video call��������ڣ����˳�ѭ�� */
    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    for ( i = 0; i < ulNumOfCalls; i++ )
    {
        enCallType = MN_CALL_GetCallType(aCallIds[i]);
        if ( MN_CALL_TYPE_VIDEO == enCallType )
        {
            break;
        }

    }

    if ( ulNumOfCalls == i )
    {
        MN_WARN_LOG("MN_CALL_ProcCstErrorInd: no video type call exist.");
        return;
    }

    MN_CALL_GetCallInfoByCallId(aCallIds[i],&stCallInfo);

    ulRet = MN_CALL_InternalCallEndReqProc(stCallInfo.clientId,
                                           0,
                                           aCallIds[i],
                                           &stEndParm);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_WARN_LOG("MN_CALL_ProcCstErrorInd: Fail to MN_CALL_InternalCallEndReqProc.");
    }

}


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcCstSetupCnf
 ��������  : ����ID_CST_CC_SETUP_CNFԭ��
 �������  : pMsg - CST����CC����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcCstSetupCnf(
    const VOS_VOID                      *pMsg
)
{

    CST_CALL_SETUP_CNF_STRU             *pstSetupCnfMsg;

    pstSetupCnfMsg = (CST_CALL_SETUP_CNF_STRU *)pMsg;

    /* ֹͣ��Ӧ�ļ�ʱ�� */
    MN_CALL_StopTimer(MN_CALL_TID_WAIT_CST_SETUP);

    /* �����ŵ��򿪵ı�ʶ */
    MN_CALL_SetVideoCallChannelOpenFlg(VOS_TRUE,(MN_CALL_ID_T)pstSetupCnfMsg->usTransId);
}




/*****************************************************************************
 �� �� ��  : NAS_CC_SendCstSetupReqMsg
 ��������  : ��CST����ԭ��ID_CC_CST_SETUP_REQ��Ϣ
 �������  : entityId     - CCʵ��ID
              enMsgType   - ԭ������
  �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_SendCstSetupReqMsg(
    VOS_UINT8                           ucCallId
)
{

   CALL_CST_SETUP_REQ_STRU             *pstTmpMsg;


    /* ����VOS��Ϣ */
    pstTmpMsg = (CALL_CST_SETUP_REQ_STRU *)
        PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, sizeof(CALL_CST_SETUP_REQ_STRU));
    if (VOS_NULL_PTR == pstTmpMsg)
    {
        MN_ERR_LOG("API_CcSyncInd: Failed to alloc VOS message.");
        return;
    }

    /* ��дVOS��Ϣͷ */
    pstTmpMsg->ulSenderCpuId                = VOS_LOCAL_CPUID;
    pstTmpMsg->ulSenderPid                  = WUEPS_PID_TAF;
    pstTmpMsg->ulReceiverCpuId              = VOS_LOCAL_CPUID;
    pstTmpMsg->ulReceiverPid                = UEPS_PID_CST;

    /* �ⲿ����Ϣ��CSTģ����Ҫ�õ��Ĳ���ֵ */
    pstTmpMsg->usMsgType                    = ID_CALL_CST_SETUP_REQ;
    pstTmpMsg->usTransId                    = ucCallId;
    pstTmpMsg->stCSTPara.enTranType         = CST_TRAN_TYPE_TRANSPARENT;
    pstTmpMsg->stCSTPara.enTranMode         = CST_TRAN_MODE_UMTS;
    pstTmpMsg->stCSTPara.ucRbId             = (VOS_UINT8)MN_CALL_GetRbId(ucCallId);
    pstTmpMsg->stCSTPara.enSyncType         = CST_SYNC_TYPE_SYNC;

    /* Ŀǰ���ӵ绰������Щ��ֵ������Ҫ��ֻ��Ϊ��CSTģ�������ȥ�Ĵ���
       ������һ������Чֵ��Χ�ڵ�ֵ */
    pstTmpMsg->stCSTPara.enUsrRate          = CST_RATE_VALUE_64K;
    pstTmpMsg->stCSTPara.enTchType          = CST_TCH_F_144;
    pstTmpMsg->stCSTPara.enParityType       = CST_FORC_0_PARITY;
    pstTmpMsg->stCSTPara.enDataBitNum       = CST_DATA_BIT_NUM_7;
    pstTmpMsg->stCSTPara.enStopBitNum       = CST_STOP_BIT_NUM_1;
    pstTmpMsg->stCSTPara.enCompressAdopt    = CST_COMPRESS_NOT_ADOPT;
    pstTmpMsg->stCSTPara.ucFaxCall          = VOS_NO;
    pstTmpMsg->stCSTPara.enCallDir          = CST_CALL_DIR_MO;
    pstTmpMsg->stCSTPara.enFaxClass         = CST_FAX_CLASS_1_0;
    (VOS_VOID)VOS_MemSet(pstTmpMsg->stCSTPara.ucRsv, 0, sizeof(pstTmpMsg->stCSTPara.ucRsv));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstTmpMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCstSetupReqMsg():WARNING:SEND MSG FIAL");  
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_SendCstRelReqMsg
 ��������  : ��CST����ԭ����Ϣ
 �������  : entityId     - CCʵ��ID
              enMsgType   - ԭ������
  �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_SendCstRelReqMsg(
    VOS_UINT8                           ucCallId
)
{

    CALL_CST_REL_REQ_STRU               *pstTmpMsg;

    /* ����VOS��Ϣ */
    pstTmpMsg = (CALL_CST_REL_REQ_STRU *)
        PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, sizeof(CALL_CST_REL_REQ_STRU));
    if (VOS_NULL_PTR == pstTmpMsg)
    {
        MN_ERR_LOG("API_CcSyncInd: Failed to alloc VOS message.");
        return;
    }

    /* ��дVOS��Ϣͷ */
    pstTmpMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstTmpMsg->ulSenderPid        = WUEPS_PID_TAF;
    pstTmpMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstTmpMsg->ulReceiverPid      = UEPS_PID_CST;

    pstTmpMsg->usMsgType    = ID_CALL_CST_REL_REQ;
    pstTmpMsg->usTransId    = (VOS_UINT16)MN_CALL_GetCcTi(ucCallId);
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstTmpMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCstRelReqMsg():WARNING:SEND MSG FIAL");
    }
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


