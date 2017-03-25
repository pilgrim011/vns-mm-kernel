/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmPreProc.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2014��4��16��
  ����޸�   :
  ��������   : NasMmPreProc.c�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��4��16��
    ��    ��   : w00176964
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Ext.h"
#include "NasMmlCtx.h"
#include "NasMmEcall.h"







#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MM_PREPORC_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -e958 �޸���: w00176964 for RSE 2014-06-19 begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc
 ��������  : CS��֧��ʱ��MMCת����MM��ϵͳ��Ϣ��Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc( VOS_VOID )
{
    /* ϵͳ��Ϣ��ָʾCS��֧�֣�MM��idle̬��״̬Ǩ�Ƶ�No cell available */
    if ((MM_IDLE_NORMAL_SERVICE         == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE   == g_MmGlobalInfo.ucState)
     || (MM_IDLE_LIMITED_SERVICE        == g_MmGlobalInfo.ucState)
     || (MM_IDLE_PLMN_SEARCH            == g_MmGlobalInfo.ucState)
     || (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState))
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);
    }

    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }

    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedDiscardMmcMmSysInfoInd
 ��������  : �ж��Ƿ���Ҫ����MMCת����MM��ϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����ϵͳ��Ϣ
             VOS_FALSE:����Ҫ����ϵͳ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_IsNeedDiscardMmcMmSysInfoInd( VOS_VOID )
{
    /* MM��TC״̬����������MMC��ϵͳ��Ϣ��
       GMM����Gmm_MsgDistribute_GMM_TC_ACTIVE ������������ */
    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        return VOS_TRUE;
    }

    /* ͨ���͵ȴ��������̣�������ϵͳ��Ϣ��ת���������ȴ��µ�ϵͳ��Ϣ */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((WAIT_FOR_OUTGOING_MM_CONNECTION            == g_MmGlobalInfo.ucState)
         || (WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState)
         || (MM_CONNECTION_ACTIVE                       == g_MmGlobalInfo.ucState))
        {
            if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
            {
                Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

                /* ֪ͨMMC HO SUCC */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
            }

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc
 ��������  : CS����Чʱ��MMCת����MM��ϵͳ��Ϣ��Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc( VOS_VOID )
{
    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS);

    /* �ǿ���̬,������CS����Ч */
    if (VOS_TRUE == NAS_MM_IsIdleState())
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    /* ֹͣecall��ʱ���Լ����ecall��ʱ����� */        
    NAS_MM_ClearEcallTimerInfo();
#endif

    Mm_ComCheckDelayMmConn(MM_FALSE);

    return;
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : NAS_MM_ProcMmcMmSysInfoInd_ECallOnly_PreProc
 ��������  : ecall onlyʱ��MMCת����MM��ϵͳ��Ϣ��Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
             VOS_FALSE:����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_ProcMmcMmSysInfoInd_ECallOnly_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT32                          ulT3242Status;
    VOS_UINT32                          ulT3243Status;

    /* ecall onlyģʽ��,MM����Ϊ��Ȼ����NMOII����,��Ϊ��ǰPS�ǲ�������attach�Լ�����PSҵ���
      ��Ϊ����likeB��� */
    g_MmGlobalInfo.ucLikeB = MM_TRUE;

    /* �������IDLE̬�����������̴���;�������CS��detach��
       ��ecall inactivityר�������Լ�����eCall��ض�ʱ�� */
    if ((VOS_FALSE              == NAS_MM_IsIdleState())    
     || (MM_IDLE_ECALL_INACTIVE == g_MmGlobalInfo.ucState))
    {
        return VOS_FALSE;
    }
    
    /* ����ecall��ʱ�� */
    NAS_MM_ProcEcallTimerStartNeededFlg();

    ulT3242Status = NAS_MM_QryTimerStatus(MM_TIMER_T3242);
    ulT3243Status = NAS_MM_QryTimerStatus(MM_TIMER_T3243);

    /* T3242��T3243������,����ҪǨ�Ƶ�eCall Inactive״̬ */
    if ((MM_TIMER_RUNNING       == ulT3242Status)
     || (MM_TIMER_RUNNING       == ulT3243Status))
    {
        return VOS_FALSE;
    }

    /* ����eCall Inactive�Ĵ��� */
    NAS_MM_PerformECallInactivity();

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_SndMmcForbidenRslt();
    }
    else
    {
        /* ֪ͨMMC��ǰCS��ע���� */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_ECALL_INACTIVE);
    }

    NAS_MM_ProcBufferMsg_MmIdleECallInactive();

    return VOS_TRUE;
}



#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_RcvMmcMmSysInfoInd_PreProc
 ��������  : Ԥ���� SYS INFO��Ϣ
 �������  : VOS_VOID *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��22��
    ��    ��   : z00161729
    �޸�����   : DTS2014102109190:��gmm��mm��ȫ�ֱ��������ӿ�ά�ɲ���Ϣ
*****************************************************************************/
VOS_UINT8   NAS_MM_RcvMmcMmSysInfoInd_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucEventID;

    ucEventID       = 5;

    NAS_MM_LogMmCtxInfo();

    /* ͣMM_TIMER_HO_WAIT_SYSINFO��MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO�Ĵ�����ԭ����ͬ:
       ֻ����CSFB��־����ʱ����ͣ��ʱ��. �����Ҫ��LAU���ȴ�LAU���;�������Ҫ��LAU, MM��ע�������
       ��������²�ͣ��ʱ�����ȶ�ʱ����ʱ */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

        /* ֪ͨMMC HO SUCC */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC);
    }

    /* �Ƿ���Ҫ����ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MM_IsNeedDiscardMmcMmSysInfoInd())
    {
        return MM_EVENT_ID_INVALID;
    }

    /* ���ϵͳ��Ϣ�ĺϷ��� */
    if (VOS_FALSE == NAS_MM_CheckMmcMmSysInfoIE(pRcvMsg))
    {
        return MM_EVENT_ID_INVALID;
    }
    
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        NAS_MM_UpdateNetworkInfo_GasSysInfo(pRcvMsg);
    }
    else
    {
        NAS_MM_UpdateNetworkInfo_WasSysInfo(pRcvMsg);
    }

    /* ���յ�ϵͳ��Ϣָʾ��ֹ��������ʱ����Ҫ�ͷ�MM���� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
    {
        if (VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
        {
            NAS_MM_RelBufferedServiceEstReqExceptEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
        }
    }

    if (VOS_TRUE == NAS_MM_IsCsNotSupport(pRcvMsg))
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc();
        
        return MM_EVENT_ID_INVALID;
    }

    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc();

        return MM_EVENT_ID_INVALID;
    }   

#if (FEATURE_ON == FEATURE_ECALL)
    if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
    {
        if (VOS_TRUE == NAS_MM_ProcMmcMmSysInfoInd_ECallOnly_PreProc(pRcvMsg))
        {
            return MM_EVENT_ID_INVALID;
        }

        return ucEventID;
    }
#endif

    return ucEventID;
}
/*lint -e958 �޸���: w00176964 for RSE 2014-06-19 end */


/*****************************************************************************
 �� �� ��  : NAS_MM_RcvMmcCoverageLostInd_PreProc
 ��������  : MMC�յ�MMCMM_COVERAGE_LOST_IND��Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvMmcCoverageLostInd_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucEventID;

    ucEventID       = 21;

    /* ͣMM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO��MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO�Ĵ�����ԭ����ͬ:
       ֻ����CSFB��־����ʱ����ͣ��ʱ��. �����Ҫ��LAU���ȴ�LAU���;�������Ҫ��LAU, MM��ע�������
       ��������²�ͣ��ʱ�����ȶ�ʱ����ʱ */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    return ucEventID;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

