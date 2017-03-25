/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : VcMntn.c
  �� �� ��   : ����
  ��    ��   : j00174725
  ��������   : 2014��04��16��
  ����޸�   :
  ��������   : vc ��ά�ɲ��ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��04��16��
    ��    ��   : j00174725
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "VcCtx.h"
#include "VcMntn.h"
#include "NasComm.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:���±� 174725;������:���Ͻ�;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_VC_MNTN_C
/*lint +e767 �޸���:���±� 174725;������:���Ͻ�*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/


/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : VC_MNTN_TraceEvent
 ��������  : �����ά�ɲ�
 �������  : pMsg - ��ά�ɲ���Ϣ(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID VC_MNTN_TraceEvent(VOS_VOID *pMsg)
{

    DIAG_TraceReport(pMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : VC_MNTN_TraceCtxInfo
 ��������  : ����ȫ�ֱ���g_stVcStateMgmt������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��16��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID VC_MNTN_TraceCtxInfo(VOS_VOID)
{
    VC_MNTN_STATE_MGMT_STRU             stMntnStateMgmt;
    APP_VC_STATE_MGMT_STRU             *pstStateMgmt;

    pstStateMgmt = APP_VC_GetVcStateMgmtAddr();

    /* ��д��Ϣͷ */
    VC_MNTN_CFG_MSG_HDR(&stMntnStateMgmt, ID_VC_MNTN_HOOK_MSG_STATE_MGMT, (sizeof(VC_MNTN_STATE_MGMT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    PS_MEM_CPY(&stMntnStateMgmt.stVcCtxInfo.stVcEcallCtx, &pstStateMgmt->stEcallCtx, sizeof(VC_MNTN_ECALL_CTX_STRU));

    stMntnStateMgmt.stVcCtxInfo.ulInCall        = pstStateMgmt->bInCall;
    stMntnStateMgmt.stVcCtxInfo.ulVoiceTestFlag = pstStateMgmt->ulVoiceTestFlag;

    /* ������Ϣ */
    VC_MNTN_TraceEvent(&stMntnStateMgmt);

    return;
}

/* Added by n00269697 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
/* ��VcMain.c�ƹ����� */
/*****************************************************************************
 �� �� ��  : NAS_MNTN_FailtoOpenCsChannel
 ��������  : Ϊ��OM������ͨ����ʧ���¼���¼��־
 �������  : VOS_UINT16                          usPort Ҫ�򿪵�����ͨ���˿�
             VOS_UINT32                          ulOmOperResult OMִ�н��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : APP_VC_InputOutPutPortCfg
 ��������  : NAS_MMA_OutputUsimInfo

 �޸���ʷ      :
  1.��    ��   : 2010��11��29��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��29��
    ��    ��   : z60575
    �޸�����   : DTS2013062500138,ERROR_LOG�޸�
*****************************************************************************/
VOS_VOID NAS_MNTN_FailtoOpenCsChannel(
    VOS_UINT16                          usPort,
    VOS_UINT32                          ulOmOperResult
)
{
    VOS_UINT32                                      ulRet;
    NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU     stChannelOpenFailure;

    /* 1����OM������ͨ����ʧ���¼���� */
    /* 1��1����ʼ����־�¼��ֲ����� */
    PS_MEM_SET(&stChannelOpenFailure, 0x00, sizeof(stChannelOpenFailure));

    /* 1��2����ȡNAS���ĵ�SIM����Ϣ�� */
    NAS_MMA_OutputUsimInfo(&stChannelOpenFailure.stUsimInfo);

    /* 1��3����¼Ҫ�򿪵�����ͨ���˿ں�OMִ�н���� */
    stChannelOpenFailure.usPort         = usPort;
    stChannelOpenFailure.ulOmOperResult = ulOmOperResult;

    /* 2�������OM������ͨ����ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_VC,MNTN_NAS_ERRORLOG_CS_CHANNEL_OPEN_FAILURE),
                                &stChannelOpenFailure,
                                sizeof(stChannelOpenFailure));
    if (VOS_OK != ulRet)
    {
        VC_WARN_LOG("NAS_MNTN_FailtoOpenCsChannel: MNTN_RecordErrorLog fail.");
        (VOS_VOID)vos_printf("NAS_MNTN_FailtoOpenCsChannel: MNTN_RecordErrorLog fail.\n");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MNTN_CsMedTimeOut
 ��������  : ���MED���ֳ�ʱ�¼���ERROR LOG
 �������  : VOS_UINT32 ulTimerId ��ʱ����ʱ�¼�ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : APP_VC_TimeoutMsgProc
 ��������  : NAS_MMA_OutputUsimInfo

 �޸���ʷ      :
  1.��    ��   : 2010��12��2��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��29��
    ��    ��   : z60575
    �޸�����   : DTS2013062500138,ERROR_LOG�޸�
*****************************************************************************/
VOS_VOID NAS_MNTN_CsMedTimeOut(VOS_UINT32                          ulTimerId)
{
    VOS_UINT32                          ulRet;
    NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU  stCsMedTimeOut;

    /* ���˲����ĵĶ�ʱ����ʱ�¼�������ʱ����ʱ�¼�����Ϊ APP_VC_TIMER_START��
    APP_VC_TIMER_SET_DEV��APP_VC_TIMER_SET_CODEC��APP_VC_TIMER_STOP��
    ����ERROR LOG�ӿ��������־ */
    if ((APP_VC_TIMER_START     != ulTimerId)
     && (APP_VC_TIMER_SET_DEV   != ulTimerId)
     && (APP_VC_TIMER_SET_CODEC != ulTimerId)
     && (APP_VC_TIMER_STOP      != ulTimerId))
    {
        return;
    }

    /* 1��MED���ֳ�ʱ�¼���� */
    /* 1��1����ʼ����־�¼��ֲ����� */
    PS_MEM_SET(&stCsMedTimeOut, 0x00, sizeof(stCsMedTimeOut));

    /* 1��2����ȡNAS���ĵ�SIM����Ϣ�� */
    NAS_MMA_OutputUsimInfo(&stCsMedTimeOut.stUsimInfo);

    /* 1��3����¼��ʱ����ʱ�¼��� */
    stCsMedTimeOut.ulTimerId = ulTimerId;

    /* 2�������OM������ͨ����ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_VC,MNTN_NAS_ERRORLOG_CS_MED_TIMEOUT),
                                &stCsMedTimeOut,
                                sizeof(stCsMedTimeOut));
    if (VOS_OK != ulRet)
    {
        VC_WARN_LOG("NAS_MNTN_CsMedTimeOut: MNTN_RecordErrorLog fail.");
        (VOS_VOID)vos_printf("NAS_MNTN_CsMedTimeOut: MNTN_RecordErrorLog fail.\n");
    }
    return;
}
/* Added by n00269697 for V3R3C60_eCall��Ŀ, 2014-3-29, end */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : VC_MNTN_ShowAlAckInfo
 ��������  : ��ӡALAck ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��30��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID VC_MNTN_ShowAlAckInfo(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VC_AL_ACK_REPORT_INFO_STRU         *pstAlAckInfo = VOS_NULL_PTR;

    pstAlAckInfo = APP_VC_GetAlAckInfoAddr();

    (VOS_VOID)vos_printf("AlAck Info:\r\n");
    for (ulIndex = 0; ulIndex < VC_MAX_AL_ACK_NUM; ulIndex++)
    {
        (VOS_VOID)vos_printf("ALACK[%d]: TimeStamp[0x%x], Value[%d]\r\n", ulIndex,
                                pstAlAckInfo->astAlAckInfo[ulIndex].ulTimeStamp,
                                pstAlAckInfo->astAlAckInfo[ulIndex].ucAlAckValue);
    }

}

#endif


/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




