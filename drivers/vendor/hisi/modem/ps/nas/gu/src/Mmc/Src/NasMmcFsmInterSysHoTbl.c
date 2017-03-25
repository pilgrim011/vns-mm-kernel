/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmInterSysHoTbl.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2011��07��04��
  ����޸�   :
  ��������   : NAS ��Inter sys Ho״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��04��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcTimerMgmt.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcFsmInterSysHo.h"
#include "NasMmcFsmInterSysHoTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_HO_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysHoFsmDesc;

/* NAS_MMC_FSM_InterSysHo::NAS_MMC_INTER_SYS_HO_STA_INIT������ */
NAS_ACT_STRU   g_astNasInterSysHoInitActTbl[]             =
{
    /* �յ�was����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysHo_Init),

    /* �յ�Gas����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysHo_Init),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�EMM����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysHo_Init),
#endif

};

/* NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP������ */
NAS_ACT_STRU   g_astNasInterSysHoWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysHo_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysHo_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp),
};


/* NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND������ */
NAS_ACT_STRU   g_astNasInterSysHoWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysHo_WaitAsResumeInd),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysHo_WaitAsResumeInd),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_HANDOVER_INFO_IND,
                      NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_HANDOVER_INFO_IND,
                      NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd),

};

/* NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP������ */
NAS_ACT_STRU   g_astNasInterSysHoWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysHo_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysHo_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp),
};


/* InterSysHo״̬�� */
NAS_STA_STRU g_astNasMmcInterSysHoStaTbl[] =
{
     /* InterSysHo��ʼ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_INIT,
                     g_astNasInterSysHoInitActTbl ),

    /* ����㷢���InterSysHo�����еȴ�MM�Ĺ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysHoWaitMmSuspendRspActTbl ),

    /* ����㷢���InterSysHo�����еȴ������Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysHoWaitAsResumeIndActTbl ),

    /* ����㷢���InterSysHo�����еȴ�MM�Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysHoWaitMmResumeRspActTbl ),
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetInterSysHoStaTblSize
 ��������  : ��ȡinter sys Ho״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:inter sys Ho״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetInterSysHoStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysHoStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetInterSysHoFsmDescAddr
 ��������  : ��ȡ����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ�����״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysHoFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysHoFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


