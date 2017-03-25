/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsSndMm.c
  Description  : ����MM��Ϣ�Ĵ���
  Function List:
      1.  Ss_SndMmMsg                 SS��MM������Ϣ
      2.  Ss_SndMmssEstReq            SS֪ͨMM����MM����
      3.  Ss_SndMmssDataReq           ��MM��������
      4.  Ss_SndMmssRelReq            SS�ø�ԭ��Ҫ��MM�ͷ�MM����
  History:
      1.  ��־�� 2004.03.09   �°�����
      2.��    ��   : 2007��06��04��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D11456
*******************************************************************************/

#include "SsInclude.h"
#include "NasOmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_SNDMM_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_SS_ReportM2NOtaMsg
 ��������  : ��trace�й�ȡSS�Ŀտ���Ϣ
 �������  : pNasMsg - ��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_SS_ReportM2NOtaMsg(
    SS_MSG_STRU                         *pNasMsg
)
{
    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT8                           ucMsgType;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    /* Message Type�ֶ�����Ϣ�е�����λ�� */
    ucMsgType = pNasMsg->aucSsMsg[1];

    SS_NORM_LOG1("NAS_SS_ReportM2NOtaMsg: [MsgType]", pNasMsg->aucSsMsg[1]);

    /* ��NAS���пտ���ϢID���ϱ���OM����ϢID��Ӧ����ͨ��OM���й�ȡ��ʾ */
    switch(ucMsgType)
    {
        case SS_MSG_REGISTER:
            enNasOtaMsyId = NAS_OTA_MSG_SS_REGISTER_UP;
            break;
        case SS_MSG_FACILITY:
            enNasOtaMsyId = NAS_OTA_MSG_SS_FACILITY_UP;
            break;
        case SS_MSG_RELCMPL:
            enNasOtaMsyId = NAS_OTA_MSG_SS_RELCMPL_UP;
            break;
        default:
            break;
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
        SS_WARN_LOG1("NAS_SS_ReportN2MOtaMsg: invalid msg type!", enNasOtaMsyId);
        /* ������SSģ��Ŀտ���Ϣ������trace����ʾ */
        return;
    }

    /*�ϱ��տ���Ϣ��OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_SS,
                       enNasOtaMsyId,
                       NAS_OTA_DIRECTION_UP,
                       pNasMsg->ulSsMsgSize + 4,
                       (VOS_UINT8*)pNasMsg);

    return;
}

/***********************************************************************
*  MODULE   : Ss_SndMmssEstReq
*  FUNCTION : SS֪ͨMM����MM����
*  INPUT    : VOS_UINT8     ucTi         ��Ӧ��MM���ӵ�TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
************************************************************************/

VOS_VOID Ss_SndMmssEstReq(
    VOS_UINT8                           ucTi,                                   /* ��Ӧ��MM���ӵ�TI                         */
    VOS_UINT8                           ucRedialFlg
)
{
    VOS_VOID    *pMsg;                                                              /* ������Ϣ������                           */

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, sizeof(MMSS_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        return;
    }


    (( MMSS_EST_REQ_STRU *)pMsg )->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    (( MMSS_EST_REQ_STRU *)pMsg )->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;       /* ������Ϣ����                             */
    (( MMSS_EST_REQ_STRU *)pMsg )->MsgHeader.ulMsgName = MMSS_EST_REQ;          /* ������Ϣ����                             */
    (( MMSS_EST_REQ_STRU *)pMsg )->ulTi = ucTi;                                 /* ���ö�Ӧ��MM���ӵ�TI                     */
    (( MMSS_EST_REQ_STRU *)pMsg )->ucRedialFlg  = ucRedialFlg;                  /* �ز���־ */
    (( MMSS_EST_REQ_STRU *)pMsg )->aucReserve[0]= 0;
    (( MMSS_EST_REQ_STRU *)pMsg )->aucReserve[1]= 0;
    (( MMSS_EST_REQ_STRU *)pMsg )->aucReserve[2]= 0;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pMsg))                                               /* ��MM����                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssEstReq():WARNING:SEND MSG FIAL");
    }
}

/***********************************************************************
*  MODULE   : Ss_SndMmssDataReq
*  FUNCTION : ��MM��������
*  INPUT    : VOS_UINT8     ucTi            ��Ӧ��MM���ӵ�TI
*             VOS_UINT8     *pucSsMsg       ���������ݣ���̬�ڴ棬�ڲ��ͷţ�
*             VOS_UINT32     ulSsMsgSize     ��Ϣ����
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־��   04-03-09  �°�����
*     2.  ��־��   05-01-14  ɾ����ָ��pucSsMsg���ͷ�
      3.��    ��   : 2007��06��04��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D11456
	  4.��    ��   : 2012��12��11��
	    ��    ��   : l00167671
	    �޸�����   : DTS2012121802573, TQE����
      5.��    ��   : 2012��12��29��
        ��    ��   : l00198894
        �޸�����   : DTS2012122702627: ����SS�տ���Ϣ��ά�ɲ�
************************************************************************/
VOS_VOID Ss_SndMmssDataReq(
                       VOS_UINT8 ucTi,                                              /* ��Ӧ��MM���ӵ�TI                         */
                       VOS_UINT8 *pucSsMsg,                                         /* ����������                               */
                       VOS_UINT32 ulSsMsgSize                                        /* ��Ϣ����                                 */
                       )
{
    VOS_VOID            *pMsg;                                                  /* ������Ϣ������                           */
    MMSS_DATA_REQ_STRU  *pSndMsg;
    VOS_UINT32   ulMsgLen;                                                           /* ������Ϣ���ȱ���                         */

    ulMsgLen = (sizeof( MMSS_DATA_REQ_STRU ) + ulSsMsgSize) - 4;                  /* ������Ϣ����                             */
    if ( ulMsgLen < sizeof( MMSS_DATA_REQ_STRU ) )
    {
        ulMsgLen = sizeof( MMSS_DATA_REQ_STRU );
    }

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, ulMsgLen - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        return;
    }
    pSndMsg = (MMSS_DATA_REQ_STRU *)pMsg;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;                       /* ������Ϣ����                             */
    pSndMsg->MsgHeader.ulMsgName = MMSS_DATA_REQ;                               /* ������Ϣ����                             */
    pSndMsg->ulTi = ucTi;                                                       /* ���ö�Ӧ��MM���ӵ�TI                     */
    pSndMsg->SsMsg.ulSsMsgSize = ulSsMsgSize;                                   /* ������Ϣ����                             */
    Ss_MemCpy(pSndMsg->SsMsg.aucSsMsg,
        pucSsMsg, ulSsMsgSize );                                                /* ������Ϣ�е�����                         */

    /* ͨ��OM��ȡSS�տ���Ϣ */
    NAS_SS_ReportM2NOtaMsg(&pSndMsg->SsMsg);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pSndMsg))                           /* ��MM����                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssRelReq():WARNING:SEND MSG FIAL");
    }
}

/***********************************************************************
*  MODULE   : Ss_SndMmssRelReq
*  FUNCTION : SS�ø�ԭ��Ҫ��MM�ͷ�MM����
*  INPUT    : VOS_UINT8     ucTi        ��Ӧ��MM���ӵ�TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
      2.��    ��   : 2007��06��04��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D11456
	  3.��    ��   : 2012��12��11��
	    ��    ��   : l00167671
	    �޸�����   : DTS2012121802573, TQE����
************************************************************************/

VOS_VOID Ss_SndMmssRelReq(
                      VOS_UINT8 ucTi                                                /* ��Ӧ��MM���ӵ�TI                         */
                      )
{
    VOS_VOID    *pMsg;                                                              /* ������Ϣ������                           */

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, sizeof(MMSS_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        NAS_MSG_FAIL();
        return;
    }
    /*A32D11456==>*/
    (( MMSS_REL_REQ_STRU *)pMsg )->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    (( MMSS_REL_REQ_STRU *)pMsg )->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;       /* ������Ϣ����                             */
    /*<==A32D11456*/
    (( MMSS_REL_REQ_STRU *)pMsg )->MsgHeader.ulMsgName = MMSS_REL_REQ;          /* ������Ϣ����                             */
    (( MMSS_REL_REQ_STRU *)pMsg )->ulTi = ucTi;                                 /* ���ö�Ӧ��MM���ӵ�TI                     */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pMsg))                                               /* ��MM����                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssRelReq():WARNING:SEND MSG FIAL");
    }                                                        /* ��MM����                                 */
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_SS_SndMmBeginSessionNotify
 ��������  : ��MM����begin session notify
 �������  : enSessionType - session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : z00161729
    �޸�����   : DSDS III����

*****************************************************************************/
VOS_VOID NAS_SS_SndMmBeginSessionNotify(
    MMSS_SESSION_TYPE_ENUM_UINT8        enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSS_BEGIN_SESSION_NOTIFY_STRU     *pstBeginSessionNotify = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstBeginSessionNotify = (MMSS_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SS,
                                         sizeof(MMSS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "NAS_SS_SndMmBeginSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SS;
    pstBeginSessionNotify->stMsgHeader.ulLength         = sizeof(MMSS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName        = MMSS_BEGIN_SESSION_NOTIFY;
    pstBeginSessionNotify->enSessionType                = enSessionType;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SS, pstBeginSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "NAS_SS_SndMmBeginSessionNotify():WARNING:SEND FAIL");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_SS_SndMmEndSessionNotify
 ��������  : ��MM����end session notify
 �������  : enSessionType - session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : z00161729
    �޸�����   : DSDS III����

*****************************************************************************/
VOS_VOID NAS_SS_SndMmEndSessionNotify(
    MMSS_SESSION_TYPE_ENUM_UINT8        enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSS_END_SESSION_NOTIFY_STRU       *pstEndSessionNotify = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstEndSessionNotify = (MMSS_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SS,
                                         sizeof(MMSS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "NAS_SS_SndMmEndSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SS;
    pstEndSessionNotify->stMsgHeader.ulLength         = sizeof(MMSS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName        = MMSS_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType    = enSessionType;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SS, pstEndSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "NAS_SS_SndMmEndSessionNotify():WARNING:SEND FAIL");
        return;
    }

    return;
}

#endif


/*****************************************************************************
 �� �� ��  : Ss_SndMmssSsStatusNty
 ��������  : ��MM����end session notify
 �������  : enSessionType - session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��18��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Ss_SndMmssSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
)
{
    VOS_UINT32                          ulRet;
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstSsStatusNty = (MMSS_STATUS_NTY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SS,
                                         sizeof(MMSS_STATUS_NTY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSsStatusNty )
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "Ss_SndMmssSsStatusNty():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSsStatusNty + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSS_STATUS_NTY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSsStatusNty->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSsStatusNty->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstSsStatusNty->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSsStatusNty->stMsgHeader.ulSenderPid      = WUEPS_PID_SS;
    pstSsStatusNty->stMsgHeader.ulLength         = sizeof(MMSS_STATUS_NTY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSsStatusNty->stMsgHeader.ulMsgName        = MMSS_SS_STATUS_NOTIFY;
    pstSsStatusNty->enSsStatus                   = enSsStatus;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SS, pstSsStatusNty );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssSsStatusNty():WARNING:SEND FAIL");
        return;
    }

    return;
}

/***********************************************************************
*  MODULE   : Ss_SndMmssAbortReq
*  FUNCTION : SS�ø�ԭ��Ҫ��MM�ͷ�MM����
*  INPUT    : VOS_UINT8     ucTi        ��Ӧ��MM���ӵ�TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
      1.��    ��   : 2008��05��09��
        ��    ��   : ����
        �޸�����   : ���ⵥ��:AT2D03224
	  2.��    ��   : 2012��12��11��
	    ��    ��   : l00167671
	    �޸�����   : DTS2012121802573, TQE����
************************************************************************/
VOS_VOID Ss_SndMmssAbortReq(
                      VOS_UINT8 ucTi                                                /* ��Ӧ��MM���ӵ�TI                         */
                      )
{
    VOS_VOID    *pMsg;                                                              /* ������Ϣ������                           */

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, sizeof(MMSS_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        NAS_MSG_FAIL();
        return;
    }
    (( MMSS_ABORT_REQ_STRU *)pMsg )->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    (( MMSS_ABORT_REQ_STRU *)pMsg )->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;   /* ������Ϣ����                             */
    (( MMSS_ABORT_REQ_STRU *)pMsg )->MsgHeader.ulMsgName = MMSS_ABORT_REQ;          /* ������Ϣ����                             */
    (( MMSS_ABORT_REQ_STRU *)pMsg )->ulTransactionId = ucTi;                        /* ���ö�Ӧ��MM���ӵ�TI                     */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pMsg))                                               /* ��MM����                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssAbortReq():WARNING:SEND MSG FIAL");
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

