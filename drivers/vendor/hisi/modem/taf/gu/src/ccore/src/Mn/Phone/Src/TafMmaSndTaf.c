/******************************************************************************

                  ��Ȩ���� (C), 2013-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaSndTaf.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��10��10��
  ����޸�   :
  ��������   : MMAģ�鷢�͵�TAF����Ϣ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��10��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/




/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafSdcCtx.h"
#include "TafLog.h"
#include "TafMmaSndTaf.h"
#include "TafMmaInterface.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_TAF_C


/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndPowerIndMsg
 ��������  : ֪ͨtafģ��ػ���Ϣ
 �������  : VOS_UINT32  ulUsimSta
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndPowerIndMsg(VOS_VOID)
{
    TAF_MMA_POWER_OFF_IND_STRU           *pstSndMsg;
    VOS_UINT32                          ulRst;

    pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_POWER_OFF_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_POWER_OFF_IND_STRU));
    if( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerIndMsg:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;

    pstSndMsg->enMsgId           = MMA_TAF_POWER_OFF_IND;

    PS_MEM_SET(pstSndMsg->aucReserve, 0x00, sizeof(pstSndMsg->aucReserve));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if( VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerIndMsg:Send Msg Failed");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSpmServiceStatusChangeNotify
 ��������  : MMA��SPM���ͷ���״̬�ı�֪ͨ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : s00217060
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndSpmServiceStatusChangeNotify(VOS_VOID)
{
    VOS_UINT32                                              ulRet;
    MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU              *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmServiceStatusChangeNotify:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = WUEPS_PID_TAF;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->ulLength         = sizeof(MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId          = ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    if ( VOS_OK != ulRet )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmServiceStatusChangeNotify:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSpmNetworkCapabilityChangeNotify
 ��������  : MMA��SPM�������������ı�֪ͨ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : s00217060
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndSpmNetworkCapabilityChangeNotify(VOS_VOID)
{
    VOS_UINT32                                              ulRet;
    MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmNetworkCapabilityChangeNotify:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = WUEPS_PID_TAF;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->ulLength         = sizeof(MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId          = ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    if ( VOS_OK != ulRet )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmNetworkCapabilityChangeNotify:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSpmRatChangeNotify
 ��������  : MMA��SPM����ģʽ�ı�֪ͨ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : s00217060
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndSpmRatChangeNotify(VOS_VOID)
{
    VOS_UINT32                                              ulRet;
    MMA_TAF_RAT_CHANGE_NOTIFY_STRU                         *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MMA_TAF_RAT_CHANGE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_TAF_RAT_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmRatChangeNotify:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_TAF_RAT_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = WUEPS_PID_TAF;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->ulLength         = sizeof(MMA_TAF_RAT_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId          = ID_MMA_TAF_RAT_CHANGE_NOTIFY;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    if ( VOS_OK != ulRet )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmRatChangeNotify:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMsgCsServiceChangeNotify
 ��������  : ��MSG����ģʽ���֪ͨ
 �������  : enCsState - cs����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SndMsgCsServiceChangeNotify(
    TAF_CS_SERVICE_ENUM_UINT32          enCsState
)
{
    VOS_UINT32                          ulRet;
    MMA_MSG_CS_SERVICE_IND             *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MMA_MSG_CS_SERVICE_IND *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_MSG_CS_SERVICE_IND) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsgCsServiceChangeNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_MSG_CS_SERVICE_IND) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = WUEPS_PID_TAF;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->ulLength         = sizeof(MMA_MSG_CS_SERVICE_IND) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId          = ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY;
    pstMsg->enCSState        = enCsState;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    if ( VOS_OK != ulRet )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsgCsServiceChangeNotify:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : MN_PH_SndMsgUsimStatus
 ��������  : ֪ͨMSGģ�鵱ǰ��״̬
 �������  : VOS_UINT32  ulUsimSta
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
VOS_VOID MN_PH_SndMsgUsimStatus(VOS_UINT32  ulUsimService)
{
    MNPH_USIM_STATUS_IND_STRU           *pstSndMsg;
    VOS_UINT32                          ulRst;

    pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MNPH_USIM_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(MNPH_USIM_STATUS_IND_STRU));
    if( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"MN_PH_SndMsgUsimStatus:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;

    pstSndMsg->enMsgId           = MN_USIM_STATUS_IND;

    if ( USIMM_CARD_SERVIC_AVAILABLE == ulUsimService )
    {
        pstSndMsg->enUsimStatus            = MNPH_USIM_STATUS_AVILABLE;
    }
    else
    {
        pstSndMsg->enUsimStatus            = MNPH_USIM_STATUS_NOT_AVAILABLE;
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if( VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"MN_PH_SndMsgUsimStatus:Send Msg Failed");
        return;
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSpmImsVoiceCapInd
 ��������  : MMA��SPM����IMS VOICE CAP֪ͨ
 �������  : ucAvail---IMS VOICE�Ƿ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : s00217060
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndSpmImsVoiceCapInd(
    VOS_UINT8                           ucAvail
)
{
    VOS_UINT32                                              ulRet;
    MMA_TAF_IMS_VOICE_CAP_IND_STRU                         *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MMA_TAF_IMS_VOICE_CAP_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(MMA_TAF_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmImsVoiceCapInd:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMA_TAF_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = WUEPS_PID_TAF;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->ulLength         = sizeof(MMA_TAF_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId          = ID_MMA_TAF_IMS_VOICE_CAP_IND;

    pstMsg->ucImsVoiceAvail  = ucAvail;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    if ( VOS_OK != ulRet )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndSpmImsVoiceCapInd:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;
}
#endif
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, end */


/*****************************************************************************
 �� �� ��  : TAF_MMA_SndPowerOnIndMsg
 ��������  : ֪ͨtafģ�鿪����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndPowerOnIndMsg(VOS_VOID)
{
    TAF_MMA_POWER_ON_IND_STRU          *pstSndMsg;

    pstSndMsg = (TAF_MMA_POWER_ON_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(TAF_MMA_POWER_ON_IND_STRU));
    if( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerOnIndMsg:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;
    pstSndMsg->ulLength          = sizeof(TAF_MMA_POWER_ON_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->enMsgId           = ID_MMA_TAF_POWER_ON_IND;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndApsEpdszidInfoInd
 ��������  : MMA Send EPDSZID INFO to Taf
 �������  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT8                           ucPzid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndApsEpdszidInfoInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
)
{
    MMA_APS_EPDSZID_INFO_IND_STRU    *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MMA_APS_EPDSZID_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                WUEPS_PID_MMA,
                                                sizeof(MMA_APS_EPDSZID_INFO_IND_STRU));
    if( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndApsEpdszidInfoInd:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulReceiverPid  = WUEPS_PID_TAF;
    pstSndMsg->enMsgId        = ID_MMA_APS_EPDSZID_INFO_IND;

    pstSndMsg->usSid          = usSid;
    pstSndMsg->usNid          = usNid;
    pstSndMsg->ucPzid         = ucPzid;

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}



VOS_VOID TAF_MMA_SndTaf1XServiceStatusInd(
    VOS_UINT32                          ulExist1XService
)
{
    MMA_TAF_1X_SERVICE_STATUS_IND_STRU    *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MMA_TAF_1X_SERVICE_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(MMA_TAF_1X_SERVICE_STATUS_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndTaf1XServiceStatusInd:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;
    pstSndMsg->ulLength          = sizeof(MMA_TAF_1X_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->enMsgId           = ID_MMA_TAF_1X_SERVICE_STATUS_IND;
    pstSndMsg->ulExist1XService  = ulExist1XService;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_SndTafCLServiceStatusInd
 ��������  : MMA֪ͨAPS��ǰ��PS�����ݷ���״̬
 �������  : MMA_TAF_RAT_TYPE_ENUM_UINT32        enRatType
             VOS_UINT8                           ucIsNewSession
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndTafCLServiceStatusInd(
    MMA_TAF_CL_STATUS_ENUM_UINT32       enClStatus,
    VOS_UINT8                           ucIsNewSession
)
{
    MMA_APS_CL_SERVICE_STATUS_IND_STRU    *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MMA_APS_CL_SERVICE_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(MMA_APS_CL_SERVICE_STATUS_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndTafCLServiceStatusInd:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;
    pstSndMsg->ulLength          = sizeof(MMA_APS_CL_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->enMsgId           = ID_MMA_APS_CL_SERVICE_STATUS_IND;
    pstSndMsg->enClStatus        = enClStatus;
    pstSndMsg->ucIsNewSession    = ucIsNewSession;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SndTafHrpdDataCallSysAcqInd
 ��������  : MMA֪ͨAPS��ǰhrpd������ҵ�񴥷������Ľ��
 �������  : MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32          enHrpdSysAcqRst
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndTafHrpdDataCallSysAcqInd(
    MMA_TAF_HRPD_DATA_CALL_SYS_ACQ_RST_ENUM_UINT32          enHrpdSysAcqRst,
    NAS_MSCC_PIF_PS_RAT_TYPE_ENUM_UINT32                    enRatType
)
{
    MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU                *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndTafHrpdDataCallSysAcqInd:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;
    pstSndMsg->ulLength          = sizeof(MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->ulMsgName         = ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND;
    pstSndMsg->enHrpdSysAcqRst   = enHrpdSysAcqRst;

    if (NAS_MSCC_PIF_PS_RATTYPE_HRPD == enRatType)
    {
        pstSndMsg->enRatType     = MMA_TAF_RAT_TYPE_HRPD;
    }
    else
    {
        pstSndMsg->enRatType     = MMA_TAF_RAT_TYPE_EHRPD;
    }


    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SndTafSysCfgInfoInd
 ��������  : MMA֪ͨTAF��ǰSYSCFG���ý��
 �������  : TAF_MMA_RAT_ORDER_STRU             *pstOldRatOrder,
             TAF_MMA_RAT_ORDER_STRU             *pstNewRatOrder
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndTafSysCfgInfoInd(
    TAF_MMA_RAT_ORDER_STRU             *pstOldRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstNewRatOrder
)
{
    MMA_TAF_SYS_CFG_INFO_IND_STRU      *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (MMA_TAF_SYS_CFG_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(MMA_TAF_SYS_CFG_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndTafSysCfgInfoInd:Alloc Msg Failed");
        return;
    }

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_TAF;
    pstSndMsg->ulLength          = sizeof(MMA_TAF_SYS_CFG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->ulMsgName         = ID_MMA_TAF_SYS_CFG_INFO_IND;

    PS_MEM_CPY(&(pstSndMsg->stOldRatOrder), pstOldRatOrder, sizeof(TAF_MMA_RAT_ORDER_STRU));
    PS_MEM_CPY(&(pstSndMsg->stNewRatOrder), pstNewRatOrder, sizeof(TAF_MMA_RAT_ORDER_STRU));

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSrvAcqCnf
 ��������  : ��SPM����ID_TAF_MMA_SRV_ACQ_CNF
 �������  : enResult - �������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��6��17��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SndSrvAcqCnf(
    TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8   enResult
)
{
    TAF_MMA_SRV_ACQ_CNF_STRU           *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SRV_ACQ_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SRV_ACQ_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrvAcqCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_TAF;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SRV_ACQ_CNF;
    pstSndMsg->enResult                 = enResult;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrvAcqCnf:Send Msg Failed");
        return;
    }

    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



