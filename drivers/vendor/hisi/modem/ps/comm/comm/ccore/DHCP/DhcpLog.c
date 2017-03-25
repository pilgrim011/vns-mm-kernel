/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : DhcpLog.c
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��9��30��
  ����޸�   :
  ��������   : DHCP trace�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��30��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "DhcpLog.h"
#include "msp_diag_comm.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_DHCP_LOG_C


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
DHCP_LOG_ENT_STRU                   g_stDhcpLogEnt;                             /* DHCP�����ӡʵ�� */


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : DHCP_MNTN_InitLogEnt
 ��������  : ��ʼ��LOGʵ���¼��Ϣ
 �������  : DHCP_LOG_ENT_STRU *pstLogEnt  LOGʵ���ַ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID DHCP_MNTN_InitLogEnt(DHCP_LOG_ENT_STRU *pstLogEnt)
{
    VOS_INT32                          lLockKey;

    /* ���� */
    lLockKey            = VOS_SplIMP();

    pstLogEnt->ulCnt    = 0;

    /* ���� */
    VOS_Splx(lLockKey);

    return;
}

/*****************************************************************************
 �� �� ��  : DHCP_MNTN_LogSave
 ��������  : ����1��LOG��¼��Ϣ
 �������  :
            DHCP_LOG_ENT_STRU              *pstLogEnt,  LOGʵ���ַ
            VOS_UINT32                      ulPid,      ��ǰ�����LOG��¼����PID
            LOG_LEVEL_EN                    enLevel,    LOG��¼�澯����
            PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,     LOG��¼�����ļ���
            VOS_UINT32                      ulLine,     LOG��¼�����ļ��к�
            VOS_INT32                       lpara1,     LOG��¼Я������
            VOS_INT32                       lpara2,     LOG��¼Я������
            VOS_INT32                       lpara3,     LOG��¼Я������
            VOS_INT32                       lpara4      LOG��¼Я������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID DHCP_MNTN_LogSave
(
    DHCP_LOG_ENT_STRU              *pstLogEnt,
    VOS_UINT32                      ulPid,
    LOG_LEVEL_EN                    enLevel,
    PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,
    VOS_UINT32                      ulLine,
    VOS_INT32                       lpara1,
    VOS_INT32                       lpara2,
    VOS_INT32                       lpara3,
    VOS_INT32                       lpara4
)
{
    VOS_UINT32                      ulCnt;
    VOS_UINT32                      ulCurrentSlice;
    VOS_INT32                       lLockKey;

    /* ���� */
    lLockKey        = VOS_SplIMP();

    ulCnt           = pstLogEnt->ulCnt;

    ulCurrentSlice  = mdrv_timer_get_normal_timestamp();
    if( ulCnt < DHCP_LOG_RECORD_MAX_NUM )
    {
        pstLogEnt->astData[ulCnt].ulTick        = ulCurrentSlice;
        pstLogEnt->astData[ulCnt].enFile        = enFile;
        pstLogEnt->astData[ulCnt].ulLine        = ulLine;
        pstLogEnt->astData[ulCnt].enLevel       = enLevel;
        pstLogEnt->astData[ulCnt].alPara[0]     = lpara1;
        pstLogEnt->astData[ulCnt].alPara[1]     = lpara2;
        pstLogEnt->astData[ulCnt].alPara[2]     = lpara3;
        pstLogEnt->astData[ulCnt].alPara[3]     = lpara4;
        ulCnt++;
        pstLogEnt->ulCnt                        = ulCnt;
    }

    /* ���� */
    VOS_Splx(lLockKey);

    /* ��¼���ˣ��Զ����� */
    if( ulCnt >= DHCP_LOG_RECORD_MAX_NUM )
    {
        DHCP_MNTN_LogOutput(pstLogEnt, ulPid);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DHCP_MNTN_LogOutput
 ��������  : ���LOG��¼��Ϣ
 �������  :
            DHCP_LOG_ENT_STRU              *pstLogEnt,  LOGʵ���ַ
            VOS_UINT32                      ulPid,      ��ǰ�����LOG��¼����PID
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID DHCP_MNTN_LogOutput(DHCP_LOG_ENT_STRU *pstLogEnt, VOS_UINT32 ulPid)
{
    CTTF_DHCP_TRACE_LOG_MSG_STRU        stDhcpTraceLogMsg;


    /*  ����ݹ���ѭ�� */
    if( (pstLogEnt->ulCnt > DHCP_LOG_RECORD_MAX_NUM) || (0 == pstLogEnt->ulCnt) )
    {
        DHCP_MNTN_InitLogEnt(pstLogEnt);
        return ;
    }

    stDhcpTraceLogMsg.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stDhcpTraceLogMsg.ulSenderPid       = ulPid;
    stDhcpTraceLogMsg.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stDhcpTraceLogMsg.ulReceiverPid     = ulPid;
    stDhcpTraceLogMsg.ulLength          = (sizeof(CTTF_DHCP_TRACE_LOG_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    stDhcpTraceLogMsg.usMsgType         = ID_CTTF_DHCP_TRACE_LOG_MSG;
    stDhcpTraceLogMsg.usTransId         = 0;

    (VOS_VOID)mdrv_memcpy( &stDhcpTraceLogMsg.stLogMsgCont, pstLogEnt, sizeof(DHCP_LOG_ENT_STRU) );

    (VOS_VOID)DIAG_TraceReport(&stDhcpTraceLogMsg);

    DHCP_MNTN_InitLogEnt(pstLogEnt);

    return ;
}




/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

