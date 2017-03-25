/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcSndGuAs.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2010��5��9��
  ����޸�   :
  ��������   : MMC����GUģ����Ϣ�Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��05��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "NasCommDef.h"
#include "NasMmcSndGuAs.h"
#include "NasComm.h"
#include "NasMmSublayerDef.h"
#include "NasMmcCtx.h"
#include "NasMmlCtx.h"
#include "Nasrrcinterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
#include "NasMmlLib.h"
#include "NasUtranCtrlInterface.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasMmcComFunc.h"
/* Modified by b00269685 for ����FR�Ż�, 2014-10-16, begin */
#include "NasMmcFsmPlmnSelection.h"
/* Modified by b00269685 for ����FR�Ż�, 2014-10-16, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_GUAS_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsPowerOffReq
 ��������  : ͨ��������PID����,NAS����Ӧ�Ľ���㷢�͹ػ�������Ϣ
 �������  : VOS_UINT32                          ulReceiverPid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
  3.��    ��   : 2013��7��4��
    ��    ��   : z00234330
    �޸�����   : ���ӿ���LOG
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsPowerOffReq(
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RRMM_POWER_OFF_REQ_STRU            *pstMsg = VOS_NULL_PTR;                  /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RRMM_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGasPowerOffReq:ERROR: Memory Alloc Error for pMsg");
        return ;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = ulReceiverPid;
    pstMsg->MsgHeader.ulLength          = sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRMM_POWER_OFF_REQ;

    /* ����VOS����ԭ�� */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGasPowerOffReq:ERROR:PS_SEND_MSG ");
        return ;
    }

    /* Modified by z00234330 for ����LOG, 2013-6-24, begin */
    (VOS_VOID)vos_printf("NAS_MMC_SndAsPowerOffReq, ulReceiverPid:%d, ulRet:%d. tick = 0x%x\r\n ", ulReceiverPid, ulRet,VOS_GetSlice());
    /* Modified by z00234330 for ����LOG, 2013-6-24, begin */

    NAS_TRACE_HIGH("Send poweroff req to %s!",
        (WUEPS_PID_WRR == ulReceiverPid) ? ((NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "WRRC" : "TRRC") : "GAS");

    return ;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsPlmnAnyCellSrchReq
 ��������  : ��AS����������������
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_START_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��9��3��
    ��    ��   : s46746
    �޸�����   : ͬ��V3R1�汾���ⵥDTS2011062001601
  3.��    ��   : 2011��11��11��
    ��    ��   : w00167002
    �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����
  4.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
  5.��    ��   : 2015��5��29��
    ��    ��   : z00301431
    �޸�����   : DTS2015051803192,֧��IMS���ǲ�֧��IMS������ʱ��Ҫ��������FR
  6.��    ��   : 2015��5��26��
    ��    ��   : w00167002
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/

VOS_VOID NAS_MMC_SndAsPlmnAnyCellSrchReq(VOS_UINT32 ulPid)
{
    /* ����ֵ���� */
    VOS_UINT32                                              ulRet;
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucImsVoiceFlag;

    /* ���� PLMN SPEC ����������� */
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                           sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    /* ���췢����Ϣ */
    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
        sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = ulPid;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = RRMM_PLMN_SEARCH_REQ;

    pstMsg->ulSearchType         = RRC_PLMN_SEARCH_SPEC;
    pstMsg->ulPlmnIdNum          = 0;
    pstMsg->aPlmnIdList[0].ulMcc = 0;
    pstMsg->aPlmnIdList[0].ulMnc = 0;

    /* ��ȡȫ�ֱ����е�FORB ROAM LA ��Ϣ */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                   stForbRoamLaInfo.astForbRomLaList);
    /* ����ǽ�����������µ�AnycellSearch��������CsfbFlg */
    ucImsVoiceFlag = NAS_MML_GetImsVoiceAvailFlg();
    if ((NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
     && (PS_TRUE == ucImsVoiceFlag))
    {
        pstMsg->enCsfbFlg = PS_TRUE;
    }

    /* ��ӽ�ֹLAI��Ϣ */
    NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(&(pstMsg->ulForbLaNum),
                                    pstMsg->aForbLaList,
                                    &stForbRoamLaInfo);

    pstMsg->enPlmnInfoCampFlg = PS_TRUE;
    pstMsg->enFftScanType     = RRMM_FFT_SCAN_TYPE_NONE;

    /* ����VOS����ԭ�� */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPlmnAnyCellSrchReq():WARNING:SEND AS PLMN ANYCELL SEARCH REQ FIAL");
        return;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSuspendReq
 ��������  : ��AS���͹�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsSuspendReq(VOS_UINT32 ulPid)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;
    /* ����ԭ������ָ�� */
    RRMM_SUSPEND_REQ_ST                *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_SUSPEND_REQ_ST *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_SUSPEND_REQ_ST));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSuspendReq():ERROR:Memory Alloc Error for pstMsg");
        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid             = ulPid;
    pstMsg->MsgHeader.ulMsgName                 = RRMM_SUSPEND_REQ;
    pstMsg->ucStopCause                         = MMC_AS_SUSPEND_STOP_DSP;

    /* ����VOS����ԭ�� */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndASSuspendReq():ERROR:Message sends fail");
        return;
    }

#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsPlmnSrchStopReq
 ��������  : ��AS����ֹͣ��Ϣ
 �������  : ulPid
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��14��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: �ڴ����ʧ�ܣ����Ӵ����ӡ

 3.��    ��   : 2011��10��17��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: ���pc�ط�

 4.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/

VOS_VOID NAS_MMC_SndAsPlmnSrchStopReq(VOS_UINT32 ulPid)
{
    VOS_UINT32                           ulRet;
    RRMM_PLMN_SEARCH_STOP_REQ_ST        *pstMsg = VOS_NULL_PTR;

    /*������Ϣ  */
    pstMsg = (RRMM_PLMN_SEARCH_STOP_REQ_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMC,
                                            sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST));

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPlmnSrchStopReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
        sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulMsgName         = RRMM_PLMN_SEARCH_STOP_REQ;
    pstMsg->MsgHeader.ulReceiverPid     = ulPid;

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    if( VOS_OK != ulRet)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPlmnSrchStopReq():WARNING:SEND AS PLMN SEARCH STOP REQ FIAL");
    }

    #ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
    #endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndGuAsEquPlmnReq
 ��������  : �������·�eplmn ����
 �������  : pstPlmnInfo: ������PLMN ID��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��24��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
  3.��    ��   : 2011��11��24��
    ��    ��   : w00167002
    �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
                ��������ͣ���������ȽϿ��ܻ����
  4.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯����
  5.��    ��   : 2012��8��15��
    ��    ��   : w00176964
    �޸�����   : V7R1C50_GUTL_PhaseII:��disabled RAT�е�PLMN�ӵ�ЧPLMN�б���ɾ�����͸�RRC
  6.��    ��   : 2012��12��4��
    ��    ��   : w00176964
    �޸�����   : DTS201212905979:֪ͨRRC��ǰEPLMNʱ,�����ֹPLMN
  7.��    ��   : 2014��1��2��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
**************************************************************************/
VOS_VOID NAS_MMC_SndGuAsEquPlmnReq(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    RRMM_EQU_PLMN_NOTIFY_REQ_STRU                          *pstMsg        = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_EQU_PLMN_NOTIFY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_EQU_PLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGuAsEquPlmnReq():ERROR:ALLOC MEM EQU PLMN LIST FIAL");
        /* ���� */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(RRMM_EQU_PLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_EQU_PLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;

    pstMsg->MsgHeader.ulMsgName           = RRMM_EQU_PLMN_NOTIFY_REQ;

    if (NAS_MML_NET_RAT_TYPE_GSM == enRatType)
    {
        pstMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    }
    else
    {
        pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    }

    if (VOS_NULL_PTR != pstEplmnInfo)
    {
        pstMsg->ulEquPlmnNum = pstEplmnInfo->ucEquPlmnNum;
        PS_MEM_CPY(pstMsg->aEquPlmnIdList, pstEplmnInfo->astEquPlmnAddr, sizeof(pstMsg->aEquPlmnIdList));
    }

    /* ����VOS����ԭ�� */
    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGuAsEquPlmnReq():WARNING:SEND AS EPLMN REQ FIAL");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsStartReq
 ��������  : ���Ϳ�������,������ֻ��ʹ����Wģ�Ľ���㿪������
 �������  : ulReceiverPid:������Ϣ������PID
 �������  : ��
 �� �� ֵ  : ��ʾ������Ϣ�Ƿ�ɹ����ɹ�����VOS_TRUE,ʧ�ܷ���VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

  3.��    ��   : 2011��8��19��
    ��    ��   : w00167002
    �޸�����   : V7R1 PHASEII �ع�: �����ֶ����㣬����طŴ���Ϣ�᲻ƥ��
  4.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯����
  5.��    ��   : 2012��8��20��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseII����
  6.��    ��   : 2012��8��25��
    ��    ��   : W00167002
    �޸�����   : V7R1 C50 GUTL PhaseII����
  7.��    ��   : 2012��8��25��
    ��    ��   : W00167002
    �޸�����   : V7R1 C50 GUTL PhaseII����׮����������GTR���̿��������쳣��
  8.��    ��   : 2012��8��30��
    ��    ��   : w00176964
    �޸�����   : GUTL PhaseII ����֪ͨRRC��ǰ��UTRAN MODE
  9.��    ��   : 2015��8��20��
    ��    ��   : w00242748
    �޸�����   : ��̬������Ŀ
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsStartReq(VOS_UINT32 ulReceiverPid)
{
    VOS_UINT32                      ulRet;
    RRMM_START_REQ_STRU            *pstMsg      = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU     *pstRatList  = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsStartReq: Alloc memeory Error");
        return ;
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH );
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = ulReceiverPid;
    pstMsg->MsgHeader.ulLength          = sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRMM_START_REQ;

    /* �޸ĵ��ú����� */
    pstMsg->ulSimStatus                 = NAS_MML_GetRrcSimStatus();

    /* ȡ�ý������ȼ��б� */
    pstRatList  = NAS_MML_GetMsPrioRatList();

    /* ���ý���ģʽ */
    pstMsg->aucRatPrioList[0]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_GSM, pstRatList);
    pstMsg->aucRatPrioList[1]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_WCDMA, pstRatList);
    pstMsg->aucRatPrioList[2]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_LTE, pstRatList);


    /* �����ǰ3GPP2�Ľ��뼼��Ϊ0�Ļ�������Ϊ��GULģʽ����L only����Ҳ��Ϊ��GULģʽ */
    if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
    {
        pstMsg->enUtranMode                = NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());
    }
    else
    {
        pstMsg->enUtranMode                = RRC_NAS_UTRAN_MODE_NULL;
    }

    /* ����VOS����ԭ�� */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    (VOS_VOID)vos_printf("NAS_MMC_SndAsStartReq, ulReceiverPid:%d, ulRet:%d. \n ", ulReceiverPid, ulRet);

    if (VOS_OK != ulRet)
    {
        return ;
    }

#ifdef NAS_STUB
    {
        VOS_UINT32               ulRet = 0;            /* �������VOS���ͺ����ķ���ֵ */
        RRMM_START_CNF_STRU*     pStartCnfMsg = VOS_NULL_PTR; /* ����ԭ������ָ�� */

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* ��TD����������TD�ظ�������� */
        if ( (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
           && (WUEPS_PID_WRR               == ulReceiverPid))
        {
            ulReceiverPid = TPS_PID_RRC;
        }
#endif

        /* �����ڴ�  */
        pStartCnfMsg = (RRMM_START_CNF_STRU *)PS_ALLOC_MSG(ulReceiverPid,
                                                   sizeof(RRMM_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pStartCnfMsg )
        {
            return ;
        }

        pStartCnfMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
        pStartCnfMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
        pStartCnfMsg->MsgHeader.ulMsgName           = RRMM_START_CNF;

        pStartCnfMsg->ulResult                      = MMC_START_SUCCESS;

        NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pStartCnfMsg);

        /* ����VOS����ԭ�� */
        ulRet = PS_SEND_MSG(ulReceiverPid, pStartCnfMsg);
        if(VOS_OK != ulRet)
        {
            return ;
        }
    }

#endif
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSuspendRelReq
 ��������  : ͨ��������PID����,NAS����Ӧ�Ľ����SUSPEND_REL_REQ
 �������  : VOS_UINT32                          ulReceiverPid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsSuspendRelReq(
    VOS_UINT32                          ulReceiverPid
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                       ulRet = 0;
    /* ����ԭ������ָ�� */
    RRMM_SUSPEND_REL_REQ_STRU       *pstAsMsg = VOS_NULL_PTR;

    /*������Ϣ  */
    pstAsMsg = (RRMM_SUSPEND_REL_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMC,
                                            sizeof(RRMM_SUSPEND_REL_REQ_STRU));

    /* �ڴ�����ʧ�� */
    if( VOS_NULL_PTR == pstAsMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSuspendRelReq: Alloc memeory Error");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAsMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstAsMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAsMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstAsMsg->MsgHeader.ulMsgName         = RRMM_SUSPEND_REL_REQ;

    pstAsMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAsMsg->MsgHeader.ulReceiverPid     = ulReceiverPid;

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstAsMsg);

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSuspendRelReq():NORMAL:MMC SEND AS SUSPEND REL REQ.");

    if(VOS_OK != ulRet)
    {
        /* ����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSuspendRelReq: pstAsMsg");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSyscfgReq
 ��������  : ʹ��V7�Ľӿ���GUas����SYSCFG������Ϣ
 �������  :  MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg, SYSCFG��Ϣ
               VOS_UINT32                          ulSimStatus, ��״̬
               VOS_UINT32                          ulReceiverPid������PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��5��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID  NAS_MMC_SndAsSyscfgReq(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgSetParm,
    VOS_UINT32                          ulReceiverPid
)
{
    /* ʹ��V7��SYSCFG�ӿڽ��з��� */
    RRMM_SYS_CFG_REQ_STRU              *pstSysCfgMsg        = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stRatList;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucSimPresentStatus;
    VOS_UINT32                          ulIsCLModeFlg;

    PS_MEM_SET(&stRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �����ڴ�  */
    pstSysCfgMsg = (RRMM_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSysCfgMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSyscfgReq,ERRORALLOC MEM RRMM_SYS_CFG_REQ FAIL");
        return ;
    }

    PS_MEM_SET( (VOS_INT8*)pstSysCfgMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstSysCfgMsg->MsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSysCfgMsg->MsgHeader.ulReceiverPid        = ulReceiverPid;
    pstSysCfgMsg->MsgHeader.ulLength             = sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSysCfgMsg->MsgHeader.ulMsgName            = RRMM_SYS_CFG_REQ;

    /* ����OPTΪVOS_TRUE */
    pstSysCfgMsg->bitOpBand                      = VOS_TRUE;
    pstSysCfgMsg->bitOpRat                       = VOS_TRUE;

    /* ����Ƶ����Ϣ */
    PS_MEM_CPY(&(pstSysCfgMsg->stBand.stLteBand), &(pstSysCfgSetParm->stBand.stLteBand), sizeof(LTE_BAND_STRU));
    pstSysCfgMsg->stBand.stWcdmaBand.ulWcdmaBand = pstSysCfgSetParm->stBand.unWcdmaBand.ulBand;
    pstSysCfgMsg->stBand.stGsmBand.ulGsmBand     = pstSysCfgSetParm->stBand.unGsmBand.ulBand;

    /* ���ý���ģʽ */
    PS_MEM_CPY(&stRatList, &(pstSysCfgSetParm->stRatPrioList), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    pstSysCfgMsg->aucRatPrioList[0]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_GSM, &stRatList);
    pstSysCfgMsg->aucRatPrioList[1]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_WCDMA, &stRatList);
    pstSysCfgMsg->aucRatPrioList[2]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_LTE, &stRatList);

    ulIsCLModeFlg = NAS_MML_IsCLModeSupportedInRatList(&(pstSysCfgSetParm->stRatPrioList));

    /************************************************************************************
    * SYSCFG utran mode��������ԭ��
    * 1��SYSCFG��GUL->GUL��utran modeֵ��Ҫ��PreUtranMode
    * 2��SYSCFG��CL->GUL��utran modeֵ��Ҫ��CurUtranMode
    * 3��SYSCFG��GUL->CL��utran modeֵ��Ҫ��null
    * 4��SYSCFG��CL->CL��utran modeֵ��Ҫ��null
    *************************************************************************************/

    if (VOS_TRUE == ulIsCLModeFlg)
    {
        pstSysCfgMsg->enUtranMode = RRC_NAS_UTRAN_MODE_NULL;
    }
    else
    {
        /* ������㷢����������ʱ��3GPP2ά���Ľ��뼼��������δ�����£����Դ�ʱ�ܹ�ʹ��3gpp2�б����ȫ�ֱ���
           ��3GPP�ı�����ʱ�ѱ����� */
        if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
        {
            pstSysCfgMsg->enUtranMode = NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(NAS_UTRANCTRL_GetPreUtranMode());
        }
        else
        {
            pstSysCfgMsg->enUtranMode = NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());
        }
    }

    /* ����sim��״̬��Ϣ */
    ucSimPresentStatus                           = NAS_MML_GetSimPresentStatus();
    pstSysCfgMsg->ulSimStatus                    = ucSimPresentStatus;


    /* ����VOS����ԭ�� */
    ulRslt = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstSysCfgMsg);

    if(VOS_OK != ulRslt)
    {
         NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSyscfgReq,ERROR:����ʧ��");
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSuspendRsp
 ��������  : ��GU as���͹���ظ������Ϣ
 �������  : RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,����ظ����
              VOS_UINT32                          ulReceiverPid,���ܽ�����PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��10��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID  NAS_MMC_SndAsSuspendRsp(
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulResult;
    RRMM_SUSPEND_RSP_ST                *pstAsMsg = VOS_NULL_PTR;

    /*������Ϣ  */

    pstAsMsg = (RRMM_SUSPEND_RSP_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMC,
                                                 sizeof(RRMM_SUSPEND_RSP_ST));

    /* �ڴ�����ʧ��,ֱ�ӷ��� */
    if( VOS_NULL_PTR == pstAsMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSuspendRsp():ERROR:Alloc Msg fail");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAsMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH );

    /*��д��Ϣ����*/
    pstAsMsg->MsgHeader.ulMsgName       = RRMM_SUSPEND_RSP;
    pstAsMsg->MsgHeader.ulReceiverPid   = ulReceiverPid;
    pstAsMsg->MsgHeader.ulLength        = sizeof(RRMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH;
    pstAsMsg->ucResult                  = enSuspendRslt;


    /*������Ϣ*/
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstAsMsg);

    if (VOS_OK != ulResult)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSuspendRsp():WARNING:MMC SEND AS SUSPEND RSP failed!");
    }

    return ;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsResumeRsp
 ��������  : ��GU as����Resume�����Ϣ
 �������  : VOS_UINT32                          ulReceiverPid,���ܽ�����PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsResumeRsp(
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulResult;
    RRMM_RESUME_RSP_ST                 *pstAsMsg;

    /*������Ϣ  */
    pstAsMsg = (RRMM_RESUME_RSP_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMC,
                                            sizeof(RRMM_RESUME_RSP_ST));

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstAsMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsResumeRsp():ERROR:Alloc Msg fail");

        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAsMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_RESUME_RSP_ST) - VOS_MSG_HEAD_LENGTH );

     /*��д��Ϣ����*/
    pstAsMsg->MsgHeader.ulMsgName       = RRMM_RESUME_RSP;
    pstAsMsg->MsgHeader.ulReceiverPid   = ulReceiverPid;


    /* ����VOS����ԭ�� */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstAsMsg);


    if(VOS_OK != ulResult)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsResumeRsp():WARNING:MMC SEND AS RESUME RSP failed!");
        return;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndWasInfoReportReq
 ��������  : ������ǰ����������ϱ�req
 �������  : VOS_UINT32                          ulReceiverPid,���ܽ�����PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 3.��    ��   : 2012��11��21��
   ��    ��   : z00161729
   �޸�����   : ֧��cerssi��nmr
 4.��    ��   : 2012��12��25��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:ƽ̨W/TD����֧��ʱ������Ҫ��Uģ����RRMM_AT_MSG_REQ
 5.��    ��   : 2013��1��9��
   ��    ��   : t00212959
   �޸�����   : DTS2013010809978,����ʱ����
*****************************************************************************/
VOS_VOID NAS_MMC_SndWasInfoReportReq(VOS_VOID)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet = 0;

    /* ����ԭ������ָ�� */
    RRMM_AT_MSG_REQ_ST                 *pstWasMsg = VOS_NULL_PTR;

    NAS_MMC_MAINTAIN_CTX_STRU          *pstMainCtx = VOS_NULL_PTR;

    /* ƽ̨W/TD����֧��ʱ������Ҫ��Uģ����RRMM_AT_MSG_REQ */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndWasInfoReportReq():NORMAL:Platform Not Support UMTS");

        /* ���� */
        return;
    }
    /*������Ϣ  */
    pstWasMsg = (RRMM_AT_MSG_REQ_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMC,
                                                        sizeof(RRMM_AT_MSG_REQ_ST));
    /* �ڴ�����ʧ�� */
    if( VOS_NULL_PTR == pstWasMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndWasInfoReportReq():ERROR:Alloc Msg fail");

        /* ���� */
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstWasMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_AT_MSG_REQ_ST) - VOS_MSG_HEAD_LENGTH );

    pstMainCtx                             = NAS_MMC_GetMaintainInfo();

    pstWasMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstWasMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstWasMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstWasMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;

    /* ��Ϣ���� */
    pstWasMsg->MsgHeader.ulMsgName         = RRMM_AT_MSG_REQ;

    /*������ʽ*/
    pstWasMsg->ucActionType                = pstMainCtx->ucActionType;

    /*WAS�ϱ�����Ϣ����*/
    pstWasMsg->ucMsgType                   = pstMainCtx->ucMsgType;

    pstWasMsg->ucSignThreshold             = pstMainCtx->ucSignThreshold;
    pstWasMsg->ucMinRptTimerInterval       = pstMainCtx->ucMinRptTimerInterval;

    /* ����VOS����ԭ�� */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstWasMsg);

    if(VOS_OK != ulRet)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndWasInfoReportReq():WARNING:MMC SEND WAS START AT INFO failed!");
        return;
    }

    /* ���� */
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndGasInfoReportReq
 ��������  : ������ǰ����������ϱ�req
 �������  : VOS_UINT32                          ulReceiverPid,���ܽ�����PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��21��
   ��    ��   : z00161729
   �޸�����   : ֧��cerssi��nmr
 3.��    ��   : 2012��12��25��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:ƽ̨��֧��GSMʱ������Ҫ��Gģ����GRRMM_AT_MSG_REQ
 4.��    ��   : 2013��1��9��
   ��    ��   : t00212959
   �޸�����   : DTS2013010809978
*****************************************************************************/
VOS_VOID NAS_MMC_SndGasInfoReportReq(VOS_VOID)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                       ulRet = 0;

    /* ����ԭ������ָ�� */
    GRRMM_AT_MSG_REQ_ST             *pstGasMsg = VOS_NULL_PTR;

    NAS_MMC_MAINTAIN_CTX_STRU       *pstMainCtx = VOS_NULL_PTR;
    /* ƽ̨��֧��Gģʱ������Ҫ��Gģ����GRRMM_AT_MSG_REQ */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGasInfoReportReq():NORMAL:Platform Not Support GSM");

        /* ���� */
        return;
    }

    /*������Ϣ  */
    pstGasMsg = (GRRMM_AT_MSG_REQ_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                    WUEPS_PID_MMC,
                                                    sizeof(GRRMM_AT_MSG_REQ_ST));

    /* �ڴ�����ʧ�� */
    if( VOS_NULL_PTR == pstGasMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGasInfoReportReq():ERROR:Alloc Msg fail");

        /* ���� */
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstGasMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(GRRMM_AT_MSG_REQ_ST) - VOS_MSG_HEAD_LENGTH );

    pstMainCtx                             = NAS_MMC_GetMaintainInfo();
    pstGasMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstGasMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstGasMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstGasMsg->MsgHeader.ulReceiverPid     = UEPS_PID_GAS;

    /* ��Ϣ���� */
    pstGasMsg->MsgHeader.ulMsgName        = GRRMM_AT_MSG_REQ;
    /*GAS�ϱ���С����Ϣ��ϵͳ��Ϣ���ϱ��������ʺ��ź�����ʹ��ͬһ���ṹ
    �ϱ�����������Ϣ����*/
    pstGasMsg->ucActionType               = pstMainCtx->ucActionType;

    pstGasMsg->ucSignThreshold            = pstMainCtx->ucSignThreshold;

    pstGasMsg->ucMinRptTimerInterval      = pstMainCtx->ucMinRptTimerInterval;


    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstGasMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstGasMsg);

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGasInfoReportReq():NORMAL:MMC SEND GAS START AT INFO");

    if(VOS_OK != ulRet)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGasInfoReportReq():WARNING:MMC SEND GAS START AT INFO failed!");
        return;
    }

    /* ���� */
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_FillForbLaToPlmnSrchReq
 ��������  : ����ֹ���� LA��ӵ�aForbRomLaList�У���Ҫ�����Ƿ��û������ָ������
 �������  : pstSrchPlmnId   : �û�ָ��������PLMN
             ulUserSpecSearch: �Ƿ���ָ������. VOS_TRUE--�ǣ�VOS_FALSE--����
 �������  : pulForbidLaNum: ��ӵ�aForbRomLaList�б��еĽ�ֹ���� LA �ĸ���
             aForbLaList   : ���н�ֹ���� LA��Ϣ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����

*****************************************************************************/
VOS_VOID NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(
    VOS_UINT32                                             *pulForbidLaNum,
    RRC_FORB_LA_STRU                                        aForbLaList[],
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    VOS_UINT32                          i;

    /* ��ֹ���� LA �ĸ���Ϊ0������ForbLa�б��н������, ֱ�ӷ��� */
    if ( 0 == pstForbRoamLaInfo->ucForbRoamLaNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* ��ָ�������������н�ֹ���� LA ��ӵ�ForbLa�б� */
    for ( i = 0; i < pstForbRoamLaInfo->ucForbRoamLaNum; i++ )
    {
        aForbLaList[i].PlmnId.ulMcc =
            pstForbRoamLaInfo->astForbRomLaList[i].stPlmnId.ulMcc;
        aForbLaList[i].PlmnId.ulMnc =
            pstForbRoamLaInfo->astForbRomLaList[i].stPlmnId.ulMnc;
        aForbLaList[i].ulForbLac    =
            pstForbRoamLaInfo->astForbRomLaList[i].aucLac[0] << 8;
        aForbLaList[i].ulForbLac    |=
            pstForbRoamLaInfo->astForbRomLaList[i].aucLac[1];
    }

    /* �����ӵ�ForbLa�б��еĽ�ֹ���� LA �ĸ��� */
    (*pulForbidLaNum) = pstForbRoamLaInfo->ucForbRoamLaNum;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildAsSpecPlmnSearchReqMsg
 ��������  : ���������㷢�͵�ָ��������Ϣ
 �������  : pstDestPlmn
             ulUserSpecSearch
 �������  : pstMsg
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��21��
   ��    ��   : sunxibo 46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����
 3.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 4.��    ��   : 2014��10��15��
   ��    ��   : b00269685
   �޸�����   : ����FR�Ż�
 5.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
 6.��    ��   : 2015��10��16��
   ��    ��   : j00174725
   �޸�����   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MMC_BuildAsSpecPlmnSearchReqMsg(
    RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    VOS_UINT32                                      ulIndex;
    NAS_MML_PLMN_WITH_RAT_STRU                     *pstDestPlmn = VOS_NULL_PTR;
    VOS_UINT8                                       ucCsfbMoFlag;
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enCsfbMtTimerStatus;

    pstDestPlmn                           = &(pstDestPlmnList->astPlmnId[0]);

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
         sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulMsgName           = RRMM_PLMN_SEARCH_REQ;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSearchType                  = RRC_PLMN_SEARCH_SPEC;
    pstMsg->enFftScanType                 = RRMM_FFT_SCAN_TYPE_NONE;
    pstMsg->enPlmnInfoCampFlg             = PS_TRUE;


    pstMsg->ulPlmnIdNum                   = NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, RRC_MAX_EQUPLMN_NUM);

    for ( ulIndex = 0 ; ulIndex < pstMsg->ulPlmnIdNum; ulIndex++ )
    {
        pstMsg->aPlmnIdList[ulIndex].ulMcc          = pstDestPlmnList->astPlmnId[ulIndex].stPlmnId.ulMcc;
        pstMsg->aPlmnIdList[ulIndex].ulMnc          = pstDestPlmnList->astPlmnId[ulIndex].stPlmnId.ulMnc;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == pstDestPlmn->enRat)
    {
        pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    }
    else
    {
        pstMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    }

    /* ��ӽ�ֹLAI��Ϣ */
    NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(&(pstMsg->ulForbLaNum),
                                                pstMsg->aForbLaList,
                                                pstForbRoamLaInfo);

    enCsfbMtTimerStatus = NAS_MML_GetCsfbMtPagingTimerStatus();
    ucCsfbMoFlag        = NAS_MML_GetCsfbMoSetupFlg();

    /* Added by b00269685 for ����FR�Ż�, 2014-10-15, begin */
    if ( (VOS_TRUE == ucCsfbMoFlag)
      || (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == enCsfbMtTimerStatus) )
    {
        pstMsg->enCsfbFlg = PS_TRUE;
    }
    else
    {
        pstMsg->enCsfbFlg = PS_FALSE;
    }
    /* Added by b00269685 for ����FR�Ż�, 2014-10-15, end */

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSpecPlmnSearchReq
 ��������  : �����Ƿ��û�ָ������ʱ�������㷢��ָ������������Ϣ
 �������  : stDestPlmn
             ulUserSpecSearch
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��  : s46746
   �޸�����  : �����ɺ���

 2.��    ��   : 2011��8��17��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: ���pc�ط�

 3.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����

  4.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
  5.��    ��   : 2014��3��19��
    ��    ��   : w00242748
    �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                 ��Ҫ��HPLMN/EHPLMN��������㡣
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsSpecPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSpecPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    NAS_MMC_BuildAsSpecPlmnSearchReqMsg(pstMsg, pstDestPlmnList, pstForbRoamLaInfo);

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSpecPlmnSearchReq():WARNING:SEND AS PLMN SEARCH REQ FIAL");
        return;
    }

#ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif


}




/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildAsHistoryPlmnSearchReqMsg
 ��������  : ���������㷢�͵�ָ����ʷƵ��������Ϣ
 �������  : pstDestPlmn
             ulUserSpecSearch
 �������  : pstMsg
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��25��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��2��
   ��    ��   : j00174725
   �޸�����   : DTS2015102004448

*****************************************************************************/
VOS_VOID NAS_MMC_BuildAsHistoryPlmnSearchReqMsg(
    RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    VOS_UINT32                                      ulIndex;
    VOS_UINT32                                      ulReceiverPid;
    NAS_MML_PLMN_WITH_RAT_STRU                     *pstDestPlmn = VOS_NULL_PTR;
    VOS_UINT8                                       ucCsfbMoFlag;
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enCsfbMtTimerStatus;

    pstDestPlmn                           = &(pstDestPlmnList->astPlmnId[0]);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == pstDestPlmn->enRat)
    {
        ulReceiverPid       = WUEPS_PID_WRR;
    }
    else
    {
        ulReceiverPid       = UEPS_PID_GAS;
    }

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        ulReceiverPid,
                        RRMM_PLMN_SEARCH_REQ,
                        sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstMsg->ulSearchType                  = RRC_PLMN_SEARCH_HISTORY;
    pstMsg->enFftScanType                 = RRMM_FFT_SCAN_TYPE_NONE;
    pstMsg->enPlmnInfoCampFlg             = PS_TRUE;
    pstMsg->ulPlmnIdNum                   = NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, RRC_MAX_EQUPLMN_NUM);

    for ( ulIndex = 0 ; ulIndex < pstMsg->ulPlmnIdNum; ulIndex++ )
    {
        pstMsg->aPlmnIdList[ulIndex].ulMcc          = pstDestPlmnList->astPlmnId[ulIndex].stPlmnId.ulMcc;
        pstMsg->aPlmnIdList[ulIndex].ulMnc          = pstDestPlmnList->astPlmnId[ulIndex].stPlmnId.ulMnc;
    }


    /* ��ӽ�ֹLAI��Ϣ */
    NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(&(pstMsg->ulForbLaNum),
                                                pstMsg->aForbLaList,
                                                pstForbRoamLaInfo);

    ucCsfbMoFlag            = NAS_MML_GetCsfbMoSetupFlg();
    enCsfbMtTimerStatus     = NAS_MML_GetCsfbMtPagingTimerStatus();

    if ( (VOS_TRUE == ucCsfbMoFlag)
      || (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == enCsfbMtTimerStatus) )
    {
        pstMsg->enCsfbFlg = PS_TRUE;
    }
    else
    {
        pstMsg->enCsfbFlg = PS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsHistoryPlmnSearchReq
 ��������  : �����㷢��ָ����ʷƵ������������Ϣ
 �������  : stDestPlmn
             ulUserSpecSearch
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��25��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsHistoryPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(RRMM_PLMN_SEARCH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsHistoryPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    NAS_MMC_BuildAsHistoryPlmnSearchReqMsg(pstMsg, pstDestPlmnList, pstForbRoamLaInfo);

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsHistoryPlmnSearchReq():WARNING:SEND AS PLMN SEARCH REQ FIAL");
        return;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildAsPrefBandPlmnSearchReqMsg
 ��������  : ���췢�͸�AS��pref band������Ϣ
 �������  : RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg
             NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList
             NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��2��
   ��    ��   : j00174725
   �޸�����   : DTS2015102004448

*****************************************************************************/
VOS_VOID NAS_MMC_BuildAsPrefBandPlmnSearchReqMsg(
    RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    VOS_UINT32                                      ulIndex;
    NAS_MML_PLMN_WITH_RAT_STRU                     *pstDestPlmn = VOS_NULL_PTR;
    VOS_UINT8                                       ucCsfbMoFlag;
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enCsfbMtTimerStatus;

    pstDestPlmn                           = &(pstDestPlmnList->astPlmnId[0]);

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
         sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulMsgName           = RRMM_PLMN_SEARCH_REQ;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSearchType                  = RRC_PLMN_SEARCH_PREF_BAND;
    pstMsg->enFftScanType                 = RRMM_FFT_SCAN_TYPE_NONE;
    pstMsg->enPlmnInfoCampFlg             = PS_TRUE;


    pstMsg->ulPlmnIdNum                   = NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, RRC_MAX_EQUPLMN_NUM);

    for ( ulIndex = 0 ; ulIndex < pstMsg->ulPlmnIdNum; ulIndex++ )
    {
        pstMsg->aPlmnIdList[ulIndex].ulMcc          = pstDestPlmnList->astPlmnId[ulIndex].stPlmnId.ulMcc;
        pstMsg->aPlmnIdList[ulIndex].ulMnc          = pstDestPlmnList->astPlmnId[ulIndex].stPlmnId.ulMnc;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == pstDestPlmn->enRat)
    {
        pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;
    }
    else
    {
        pstMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    }

    /* ��ӽ�ֹLAI��Ϣ */
    NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(&(pstMsg->ulForbLaNum),
                                                pstMsg->aForbLaList,
                                                pstForbRoamLaInfo);

    enCsfbMtTimerStatus = NAS_MML_GetCsfbMtPagingTimerStatus();
    ucCsfbMoFlag        = NAS_MML_GetCsfbMoSetupFlg();

    if ( (VOS_TRUE == ucCsfbMoFlag)
      || (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == enCsfbMtTimerStatus) )
    {
        pstMsg->enCsfbFlg = PS_TRUE;
    }
    else
    {
        pstMsg->enCsfbFlg = PS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsPrefBandPlmnSearchReq
 ��������  : ��AS����pref band��������Ϣ
 �������  : NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList
             NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsPrefBandPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(RRMM_PLMN_SEARCH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPrefBandPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    NAS_MMC_BuildAsPrefBandPlmnSearchReqMsg(pstMsg, pstDestPlmnList, pstForbRoamLaInfo);

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPrefBandPlmnSearchReq():WARNING:SEND AS PLMN SEARCH REQ FIAL");
        return;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsNcellSpecPlmnSearchReq
 ��������  : ֪ͨ��������ncell����
 �������  : pstTdsNcellInfo        - tdsƵ���б���Ϣ
             pstOtherModemEplmnInfo - ��Чplmn��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsNcellSpecPlmnSearchReq(
    NAS_MMC_TDS_NCELL_INFO_STRU        *pstTdsNcellInfo,
    NAS_MML_EQUPLMN_INFO_STRU          *pstOtherModemEplmnInfo
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSpecPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulMsgName           = RRMM_PLMN_SEARCH_REQ;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSearchType                  = RRC_PLMN_SEARCH_NCELL_SPEC;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_WRR;

    pstMsg->stNcellInfo.ucTdsArfcnNum = pstTdsNcellInfo->ucTdsArfcnNum;
    PS_MEM_CPY(pstMsg->stNcellInfo.ausTdsArfcnList, pstTdsNcellInfo->ausTdsArfcnList,
               sizeof(pstMsg->stNcellInfo.ausTdsArfcnList));

    pstMsg->stNcellInfo.ucEplmnIdNum = pstOtherModemEplmnInfo->ucEquPlmnNum;
    PS_MEM_CPY(pstMsg->stNcellInfo.astEplmnIdList, pstOtherModemEplmnInfo->astEquPlmnAddr,
                sizeof(pstMsg->stNcellInfo.astEplmnIdList));

    pstMsg->enPlmnInfoCampFlg             = PS_TRUE;
    pstMsg->enFftScanType                 = RRMM_FFT_SCAN_TYPE_NONE;

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSpecPlmnSearchReq():WARNING:SEND AS PLMN SEARCH REQ FIAL");
        return;
    }

#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsCsgListSearchReq
 ��������  :�����㷢��CSG LIST����������Ϣ
 �������  : ulReceiverPid - ����pid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��15��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsCsgListSearchReq(
    VOS_UINT32                          ulReceiverPid
)
{
    RRMM_CSG_LIST_SEARCH_REQ_STRU      *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_CSG_LIST_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsCsgListSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        ulReceiverPid,
                        RRMM_CSG_LIST_SEARCH_REQ,
                        sizeof(RRMM_CSG_LIST_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsCsgListSearchReq():WARNING:SEND AS CSG PLMN SEARCH REQ FIAL");
        return;
    }

}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsPlmnListReq
 ��������  :�����㷢��LIST����������Ϣ
 �������  : ulReceiverPid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��22��
   ��    ��   :  W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 3.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsPlmnListReq(
    VOS_UINT32                          ulReceiverPid
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPlmnListReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulMsgName           = RRMM_PLMN_SEARCH_REQ;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSearchType                  = RRC_PLMN_SEARCH_LIST;

    pstMsg->MsgHeader.ulReceiverPid       = ulReceiverPid;

    pstMsg->enPlmnInfoCampFlg             = PS_TRUE;
    pstMsg->enFftScanType                 = RRMM_FFT_SCAN_TYPE_NONE;

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsPlmnListReq():WARNING:SEND AS PLMN SEARCH REQ FIAL");
        return;
    }

#ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAvailPlmnMsg
 ��������  : ֪ͨGU AS��ѯPLMN���
 �������  : pAvailPlmnPara:PLMN��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 3.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/

VOS_VOID NAS_MMC_SndAsAvailPlmnMsg(
    NAS_MMC_AVAIL_PLMN_STRU             *pAvailPlmnInfo
)
{
    VOS_UINT8                           i;
    RRMM_PLMN_QUERY_CNF_STRU           *pstMsg = VOS_NULL;
    VOS_UINT32                          ulRet;

    pstMsg = (RRMM_PLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MMC,sizeof(RRMM_PLMN_QUERY_CNF_STRU));

    if( VOS_NULL == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsAvailPlmnMsg():ERROR:Memory Alloc Error for pstMsg");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0x00,
         sizeof(RRMM_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulMsgName         = RRMM_PLMN_QUERY_CNF;

    pstMsg->ulAvailPlmnIdNum= pAvailPlmnInfo->ulAvailPlmnNum;
    for(i = 0; i < pAvailPlmnInfo->ulAvailPlmnNum; i++)
    {
        pstMsg->astAvailPlmnIdList[i] = pAvailPlmnInfo->astAvailPlmnIdList[i];
    }

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsAvailPlmnMsg():Error: Failed in NAS_UTRANCTRL_SndAsMsg()");
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_JudgePlmnIfInAvailPlmnList
 ��������  : �ж������plmn�Ƿ��Ѿ���available plmn�б���
 �������  : pstAvailPlmn - ����������������Ϣ�б�
              stPlmnId     - ����������������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �����plmn����available plmn�б���
              VOS_FALSE - �����plmn����available plmn�б���
 ���ú���  :
 ��������  :
 �޸���ʷ  :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnInAvailPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MMC_AVAIL_PLMN_STRU            *pstAvailPlmn
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstAvailPlmn->ulAvailPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn((NAS_MML_PLMN_ID_STRU *)&pstAvailPlmn->astAvailPlmnIdList[i],
                                                            pstPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildAsPlmnInfo
 ��������  : ����PLMN�б���Ϣ
 �������  : ��
 �������  : pstAvailPlmn:�����PLMN����Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��6��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_BuildAsFirstPlmnInfo(
    NAS_MMC_AVAIL_PLMN_STRU            *pstAvailPlmn
)
{
    NAS_MML_PLMN_WITH_RAT_STRU              *pstUserPlmnInfo;
    NAS_MML_SIM_EHPLMN_INFO_STRU            *pstEhplmnInfo;

    pstEhplmnInfo   = NAS_MML_GetSimEhplmnList();


    pstUserPlmnInfo = NAS_MMC_GetUserSpecPlmnId();

    PS_MEM_SET(pstAvailPlmn, 0, sizeof(NAS_MMC_AVAIL_PLMN_STRU));

    /* ���Ȱ�HPLMN/UPlmn������б���,Ȼ���RPLMN������б��� */

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        pstAvailPlmn->astAvailPlmnIdList[pstAvailPlmn->ulAvailPlmnNum].ulMcc = pstUserPlmnInfo->stPlmnId.ulMcc;
        pstAvailPlmn->astAvailPlmnIdList[pstAvailPlmn->ulAvailPlmnNum].ulMnc = pstUserPlmnInfo->stPlmnId.ulMnc;
    }
    else
    {
        pstAvailPlmn->astAvailPlmnIdList[pstAvailPlmn->ulAvailPlmnNum].ulMcc = pstEhplmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc;
        pstAvailPlmn->astAvailPlmnIdList[pstAvailPlmn->ulAvailPlmnNum].ulMnc = pstEhplmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc;
    }

    pstAvailPlmn->ulAvailPlmnNum++;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRrcPlmnQueryCnf
 ��������  : ֪ͨGU AS��ѯPLMN���
 �������  : RRMM_EQU_PLMN_NOTIFY_REQ_STRU
 �������  : RRMM_EQU_PLMN_NOTIFY_REQ_STRU
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : eplmn����Ҫ����rplmn
 3.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList

*****************************************************************************/

VOS_VOID NAS_MMC_SndRrcPlmnQueryCnf(
    PS_BOOL_ENUM_UINT8                  enQueryWPlmn
)
{
    NAS_MMC_AVAIL_PLMN_STRU                 stAvailPlmn;
    VOS_UINT32                              i;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8  enSelectionMode;

    NAS_MML_RPLMN_CFG_INFO_STRU            *pstRplmnCfg     = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU              *pstEquPlmnInfo  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                   *pstCurrPlmnId   = VOS_NULL_PTR;

    pstRplmnCfg     = NAS_MML_GetRplmnCfg();
    pstEquPlmnInfo  = NAS_MML_GetEquPlmnList();
    pstCurrPlmnId   = NAS_MML_GetCurrCampPlmnId();

    /* �����һ��PLMN�б� */
    NAS_MMC_BuildAsFirstPlmnInfo(&stAvailPlmn);

    if(PS_FALSE == enQueryWPlmn)
    {
        enSelectionMode = NAS_MMC_GetPlmnSelectionMode();
        if( (VOS_TRUE == NAS_MML_IsPlmnIdValid(&(pstRplmnCfg->stGRplmnInNV)))
         && (NAS_MMC_PLMN_SELECTION_MODE_AUTO == enSelectionMode) )
        {
            /* �ж�g_MmcGlobalCtrl.stGRplmnInNV�Ƿ��Ѿ�������stAvailPlmn��,���������������� */
            if (VOS_FALSE == NAS_MMC_IsPlmnInAvailPlmnList(&(pstRplmnCfg->stGRplmnInNV),
                                                           &stAvailPlmn))
            {
                stAvailPlmn.astAvailPlmnIdList[stAvailPlmn.ulAvailPlmnNum].ulMcc = pstRplmnCfg->stGRplmnInNV.ulMcc;
                stAvailPlmn.astAvailPlmnIdList[stAvailPlmn.ulAvailPlmnNum].ulMnc = pstRplmnCfg->stGRplmnInNV.ulMnc;
                stAvailPlmn.ulAvailPlmnNum++;
            }
        }
    }


    /* Eplmn����ʱ�����Eplmn  */
    if ( pstEquPlmnInfo->ucEquPlmnNum > 0 )
    {
        for(i = 0; i < pstEquPlmnInfo->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstEquPlmnInfo->astEquPlmnAddr[i]),
                             (VOS_UINT8)stAvailPlmn.ulAvailPlmnNum, (NAS_MML_PLMN_ID_STRU *)stAvailPlmn.astAvailPlmnIdList))
            {
                continue;
            }

            stAvailPlmn.astAvailPlmnIdList[stAvailPlmn.ulAvailPlmnNum].ulMcc = pstEquPlmnInfo->astEquPlmnAddr[i].ulMcc;
            stAvailPlmn.astAvailPlmnIdList[stAvailPlmn.ulAvailPlmnNum].ulMnc = pstEquPlmnInfo->astEquPlmnAddr[i].ulMnc;
            stAvailPlmn.ulAvailPlmnNum++;
        }

    }
    /*Rplmn������ʱ��ֻ��ӵ�ǰ����*/
    else
    {
        stAvailPlmn.astAvailPlmnIdList[stAvailPlmn.ulAvailPlmnNum].ulMcc = pstCurrPlmnId->ulMcc;
        stAvailPlmn.astAvailPlmnIdList[stAvailPlmn.ulAvailPlmnNum].ulMnc = pstCurrPlmnId->ulMnc;
        stAvailPlmn.ulAvailPlmnNum++;
    }

    NAS_MMC_SndAsAvailPlmnMsg(&stAvailPlmn);
}


/*****************************************************************************
 �� �� ��  : NAs_MMC_SndEPlmnQueryCnf
 ��������  : NAS�ظ�������ЧpLMN����������
 �������  : *pEquPlmnList - ��ЧPLMN����������
              ulOpCurPlmnId - ��ǰפ�������Ƿ���Ч
              pstCurPlmnId  - ��ǰפ������plmn id
             ulPid - ����RRMM_EPLMN_QUERY_REQ�����PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��16��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 3.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 4.��    ��   : 2013��10��15��
   ��    ��   : z00161729
   �޸�����   : DTS2013082907281:UE��w���н������й���rrc rej�ض���g����Ϣ��
                ���н������޷��ɹ��ض���wԭС������Ϊ������ѯplmnʱnasֻ����gС��plmn
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsEquPlmnQueryCnf(
    EQUIVALENT_PLMN_STRU               *pstEquPlmnList,
    VOS_UINT32                          ulOpCurPlmnId,
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId,
    VOS_UINT32                          ulPid
)
{
    VOS_UINT8                           i;
    RRMM_EPLMN_QUERY_CNF_STRU          *pstMsg = VOS_NULL;
    VOS_UINT32                          ulRet;

    pstMsg = (RRMM_EPLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MMC,sizeof(RRMM_EPLMN_QUERY_CNF_STRU));
    if( VOS_NULL == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsEquPlmnQueryCnf():ERROR:Memory Alloc Error for pstMsg");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
         sizeof(RRMM_EPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstMsg->MsgHeader.ulReceiverPid = ulPid;
    pstMsg->MsgHeader.ulMsgName     = RRMM_EPLMN_QUERY_CNF;
    pstMsg->ulEPlmnIdNum            = pstEquPlmnList->ulEquPlmnNum;
    for(i = 0;i < pstEquPlmnList->ulEquPlmnNum;i++)
    {
        pstMsg->astEPlmnIdList[i].ulMcc = pstEquPlmnList->aEquPlmnIdList[i].ulMcc;
        pstMsg->astEPlmnIdList[i].ulMnc = pstEquPlmnList->aEquPlmnIdList[i].ulMnc;
    }

    if (VOS_TRUE == ulOpCurPlmnId)
    {
        pstMsg->bitOpCurPlmn = VOS_TRUE;
        pstMsg->stCurCampedPlmnId.ulMcc = pstCurPlmnId->ulMcc;
        pstMsg->stCurCampedPlmnId.ulMnc = pstCurPlmnId->ulMnc;
    }

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "Failed in NAS_UTRANCTRL_SndAsMsg()");
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRrMmCellSelReq
 ��������  : ��RRC����RRMM_CELL_SELECTION_CTRL_REQ�Ĵ���
 �������  : ucSrhType - ����ԭ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��16��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��14��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: �ڴ����ʧ�ܣ����Ӵ����ӡ������Ÿ�ֵ����

 3.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 4.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/

VOS_VOID   NAS_MMC_SndRrMmCellSelReq(
    VOS_UINT8                           ucSrhType
)
{
    VOS_UINT8                           i;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLac;
    RRMM_CELL_SELECTION_CTRL_REQ_STRU  *pstMsg        = VOS_NULL_PTR;                                   /* ����ԭ������ָ��                          */
    VOS_UINT32                          ulRet;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList;
    NAS_MML_LAI_STRU                                       *pstLai;


    pstMsg = (RRMM_CELL_SELECTION_CTRL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                WUEPS_PID_MMC,sizeof(RRMM_CELL_SELECTION_CTRL_REQ_STRU));
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmCellSelReq():ERROR:Memory Alloc Error for pstMsg");

        return ;
    }

    /* ����δ��ʼ������PC�ط�ʱ���� */
    PS_MEM_SET(pstMsg->aForbLaList, 0,sizeof(RRC_FORB_LA_STRU)*RRC_MAX_FORBLA_NUM);

    pstForbidInfo           = NAS_MML_GetForbidPlmnInfo();

    pstMsg->ulForbLaNum     = pstForbidInfo->ucForbRoamLaNum;

    for ( i= 0; i < pstForbidInfo->ucForbRoamLaNum; i++ )
    {
        usLac = ( ((pstForbidInfo->astForbRomLaList[i].aucLac[0]) << 8 )
                | ((pstForbidInfo->astForbRomLaList[i].aucLac[1])));

        pstMsg->aForbLaList[i].ulForbLac      = usLac;
        pstMsg->aForbLaList[i].PlmnId.ulMcc   =
                    pstForbidInfo->astForbRomLaList[i].stPlmnId.ulMcc;

        pstMsg->aForbLaList[i].PlmnId.ulMnc   =
                    pstForbidInfo->astForbRomLaList[i].stPlmnId.ulMnc;
    }

    pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
    for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
    {
        pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if ( (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, pstForbidInfo->ucForbRoamLaNum, pstForbidInfo->astForbRomLaList))
          && (pstMsg->ulForbLaNum < RRC_MAX_FORBLA_NUM) )
        {
            usLac = ( ((pstLai->aucLac[0]) << 8 ) | ((pstLai->aucLac[1])));
            pstMsg->aForbLaList[pstMsg->ulForbLaNum].ulForbLac      =
                        usLac;
            pstMsg->aForbLaList[pstMsg->ulForbLaNum].PlmnId.ulMcc   =
                        pstLai->stPlmnId.ulMcc;
            pstMsg->aForbLaList[pstMsg->ulForbLaNum].PlmnId.ulMnc   =
                        pstLai->stPlmnId.ulMnc;
            (pstMsg->ulForbLaNum)++;
        }
    }

    pstMsg->MsgHeader.ulMsgName = RRMM_CELL_SELECTION_CTRL_REQ;                          /* ��Ϣ����                                  */

    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pstMsg->MsgHeader.ulReceiverPid     = UEPS_PID_GAS;
    }
    else
    {
        pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    }

    pstMsg->ulReselectInd                   = ucSrhType;

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "Failed in NAS_UTRANCTRL_SndAsMsg()");
    }

}

/*****************************************************************************
 �� �� ��  : MMC_ComJudgeLai
 ��������  : �ṩ��������API�ӿ�,��������ж�LAI�Ƿ�Ϸ�
 �������  : stPlmn:PLMN ID
             usLac:λ����
 �������  : penLaiValidFlg:��λ�����Ƿ�Ϸ�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList

*****************************************************************************/
VOS_UINT32 MMC_ComJudgeLai(
    RRC_PLMN_ID_STRU                    stPlmn,
    VOS_UINT16                          usLac,
    PS_BOOL_ENUM_UINT8                 *penLaiValidFlg
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserPlmn;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmn;
    NAS_MML_LAI_STRU                    stLai;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;
    VOS_UINT32                          ulRlstLaiInForbidRegLaiList;
    VOS_UINT32                          ulRlstLaiInForbidRoamLaiList;

    pstEquPlmn                          = NAS_MML_GetEquPlmnList();
    pstUserPlmn                         = NAS_MMC_GetUserSpecPlmnId();
    *penLaiValidFlg                     = PS_TRUE;

    /* ��ȡFPLMN��Ϣ*/
    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();

    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList((NAS_MML_PLMN_ID_STRU*)&stPlmn))
    {
       *penLaiValidFlg =  PS_FALSE;
    }

    stLai.stPlmnId.ulMcc = stPlmn.ulMcc;
    stLai.stPlmnId.ulMnc = stPlmn.ulMnc;
    stLai.aucLac[0]      = (usLac & 0xFF00) >> 8;
    stLai.aucLac[1]      = (usLac & 0xFF);

    ulRlstLaiInForbidRegLaiList         = NAS_MML_IsLaiInDestLaiList(&stLai,
        pstForbidPlmnInfo->ucForbRegLaNum, pstForbidPlmnInfo->astForbRegLaList);
    ulRlstLaiInForbidRoamLaiList        = NAS_MML_IsLaiInDestLaiList(&stLai,
        pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList);

    if ( (VOS_TRUE == NAS_MML_IsInForbLaWithValidPeriodList(&stLai))
      || (VOS_TRUE == ulRlstLaiInForbidRegLaiList)
      || (VOS_TRUE == ulRlstLaiInForbidRoamLaiList) )
    {
       *penLaiValidFlg =  PS_FALSE;
    }


    /* �ֶ�ģʽ��,�û�ָ������PLMN ID����EPLMN�� */
    enSelectionMode = NAS_MMC_GetPlmnSelectionMode();
    if ( (PS_TRUE == *penLaiValidFlg)
      && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode) )
    {
        if ( VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList((NAS_MML_PLMN_ID_STRU*)&stPlmn,
                                                        1,
                                                        &(pstUserPlmn->stPlmnId)))
        {
            if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList((NAS_MML_PLMN_ID_STRU*)&stPlmn,
                                                pstEquPlmn->ucEquPlmnNum,
                                                pstEquPlmn->astEquPlmnAddr))
            {
                *penLaiValidFlg = PS_FALSE;
            }
        }


    }


    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRrMmRelReq
 ��������  : ֪ͨWRR�ͷ�����
 �������  : ulCnDomain  �ͷ�ָ���������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��24��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID NAS_MMC_SndRrMmRelReq(
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomain
)
{
    RRMM_REL_REQ_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMC,
                        sizeof(RRMM_REL_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: memery alloc failed.");

        return;
    }

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulMsgName       = RRMM_REL_REQ;

    pstMsg->ulCnDomainId              = ulCnDomain;

    /* MMC�ͷ�����ʱ����ֵʼ��Ϊno barred */
    pstMsg->enBarValidFlg             = RRC_CELL_UNBARRED;

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmRelReq: send message failed.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsFastPlmnSearchReq
 ��������  : �����㷢�����ָ��������Ϣ
 �������  : ulReceiverPid -- ������PID
             pstPlmnId     -- ����ָ���ѵ�PlmnId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��24��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��17��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: ���pc�ط�

 3.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����
 4.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 5.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsFastPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsSpecPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = ulReceiverPid;
    pstMsg->MsgHeader.ulMsgName           = RRMM_PLMN_SEARCH_REQ;
    pstMsg->MsgHeader.ulLength            = sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ulSearchType                  = RRC_PLMN_SEARCH_SPEC_FAST;
    pstMsg->ulPlmnIdNum                   = 1;
    pstMsg->aPlmnIdList[0].ulMcc          = pstPlmnId->ulMcc;
    pstMsg->aPlmnIdList[0].ulMnc          = pstPlmnId->ulMnc;

    /* ��ȡȫ�ֱ����е�FORB ROAM LA ��Ϣ */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* ��ӽ�ֹLAI��Ϣ */
    NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(&(pstMsg->ulForbLaNum),
                                    pstMsg->aForbLaList,
                                    &stForbRoamLaInfo);

    NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                   stForbRoamLaInfo.astForbRomLaList);
    pstMsg->enPlmnInfoCampFlg = PS_TRUE;
    pstMsg->enFftScanType     = RRMM_FFT_SCAN_TYPE_NONE;

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsFastPlmnSearchReq():WARNING:SEND AS PLMN SEARCH REQ FIAL");
    }

    #ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
    #endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsBgPlmnSearchReq
 ��������  : �����㷢�𱳾�����Ϣ
 �������  : ulReceiverPid -- ������PID
             pstPlmnId     -- ����ָ���ѵ�PlmnId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��24��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��17��
   ��    ��   : w00167002
   �޸�����   : V7R1 PHASEII �ع�: ���pc�ط�

 3.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����
 4.��    ��   : 2012��5��7��
   ��    ��   : w00176964
   �޸�����   : GUL_BG��Ŀ����
 5.��    ��   : 2012��7��14��
   ��    ��   : W00176964
   �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsBgPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid,
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
)
{
    RRMM_BG_PLMN_SEARCH_REQ_ST                             *pstMsg = VOS_NULL_PTR;

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbPlmnInfo = VOS_NULL_PTR;

    pstMsg = (RRMM_BG_PLMN_SEARCH_REQ_ST *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        WUEPS_PID_MMC,
                        sizeof(RRMM_BG_PLMN_SEARCH_REQ_ST));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBgPlmnSearchReq: memery alloc failed.");

        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(RRMM_BG_PLMN_SEARCH_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = ulReceiverPid;

    pstMsg->MsgHeader.ulMsgName       = RRMM_BG_PLMN_SEARCH_REQ;

    pstMsg->stPlmnId.stPlmnId.ulMcc   = pstPlmnId->stPlmnId.ulMcc ;
    pstMsg->stPlmnId.stPlmnId.ulMnc   = pstPlmnId->stPlmnId.ulMnc ;

    /* ��MMC�ڲ���RATת��Ϊ��AS�ӿ��е����� */
    switch (pstPlmnId->enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            pstMsg->stPlmnId.ulRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            pstMsg->stPlmnId.ulRat = RRC_NAS_RAT_GSM;
            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            pstMsg->stPlmnId.ulRat = RRC_NAS_RAT_LTE;
            break;
#endif

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBgPlmnSearchReq: Unexpected rat type.");
            break;
    }

    /* ��ȡȫ�ֱ����е�FORB ROAM LA ��Ϣ */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* ��ȡ��ֹλ�����б� */
    NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(&(pstMsg->ulForbLaNum),
                                    pstMsg->aForbLaList,
                                    &stForbRoamLaInfo);


    NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                   stForbRoamLaInfo.astForbRomLaList);

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBgPlmnSearchReq: send message failed.");
    }


    #ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
    #endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsBgStopPlmnSearchReq
 ��������  : �����㷢��ֹͣBG������Ϣ
 �������  : VOS_UINT32                          ulReceiverPid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��24��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

2.��    ��   : 2011��10��17��
  ��    ��   : w00167002
  �޸�����   : V7R1 PHASEII �ع�: ���pc�ط�

3.��    ��   : 2012��7��14��
  ��    ��   : W00176964
  �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsBgStopPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid
)
{
    RRMM_BG_PLMN_STOP_REQ_ST           *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_BG_PLMN_STOP_REQ_ST *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMC,
                        sizeof(RRMM_BG_PLMN_STOP_REQ_ST));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBgStopPlmnSearchReq: memery alloc failed.");

        return;
    }

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = ulReceiverPid;

    pstMsg->MsgHeader.ulMsgName       = RRMM_BG_PLMN_STOP_REQ;

    pstMsg->aucReserve1[0] = 0;
    pstMsg->aucReserve1[1] = 0;
    pstMsg->aucReserve1[2] = 0;
    pstMsg->aucReserve1[3] = 0;

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBgStopPlmnSearchReq: send message failed.");
    }

    #ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
    #endif

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsGetGeoPlmnSearchReq
 ��������  : ��GU AS���ͻ�ȡ������Ϣ������Ϣ
 �������  : VOS_UINT32    ���շ�PID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsGetGeoPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)NAS_MMC_ALLOC_MSG_WITH_HDR(sizeof(RRMM_PLMN_SEARCH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsGetGeoPlmnSearchReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        ulReceiverPid,
                        RRMM_PLMN_SEARCH_REQ,
                        sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstMsg->ulSearchType                = RRC_PLMN_SEARCH_GET_GEO;
    pstMsg->enFftScanType               = RRMM_FFT_SCAN_TYPE_LOW;
    pstMsg->enPlmnInfoCampFlg           = PS_FALSE;

    /* ����VOS����ԭ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsGetGeoPlmnSearchReq:WARNING:SEND AS PLMN SEARCH REQ FAIL");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsStopGetGeoPlmnSearchReq
 ��������  : ��GU AS����ֹͣ��ȡ������Ϣ������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsStopGetGeoPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid
)
{
    NAS_MMC_SndAsPlmnSrchStopReq(ulReceiverPid);
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsNasCommInfoChangeReq
 ��������  : ��AS����RRMM_NAS_COMM_INFO_CHANGE_REQ
 �������  : ulReceiverPid          :������Ϣ��PID
             pstNasComInfo          :NAS_COMM_INFO_STRU
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
 3.��    ��   : 2013��3��1��
   ��    ��   : t00212959
   �޸�����   : DTS2013030106126
 3.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsNasCommInfoChangeReq(
    VOS_UINT32                          ulReceiverPid,
    NAS_COMM_INFO_STRU                 *pstNasComInfo
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;
    /* ����ԭ������ָ�� */
    RRMM_NAS_COMM_INFO_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_NAS_COMM_INFO_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_NAS_COMM_INFO_REQ_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNasCommInfoChangeReq():ERROR:Memory Alloc Error for pstMsg");
        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(RRMM_NAS_COMM_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid             = ulReceiverPid;
    pstMsg->MsgHeader.ulMsgName                 = RRMM_NAS_COMM_INFO_CHANGE_REQ;

    /* ����ǿ�ָ�� */
    if ( VOS_NULL_PTR == pstNasComInfo)
    {
        pstMsg->stNasCommInfo.bitOpUsimValid        = VOS_FALSE;


        pstMsg->stNasCommInfo.bitOpLTECapability    = VOS_FALSE;

        pstMsg->stNasCommInfo.bitOpEHPlmn           = VOS_FALSE;
        pstMsg->stNasCommInfo.bitOpHPlmn            = VOS_FALSE;

        pstMsg->stNasCommInfo.bitOpUTRANCapability  = VOS_FALSE;
        pstMsg->stNasCommInfo.bitOpGSMCapability    = VOS_FALSE;

        /* ����VOS����ԭ�� */
        ulRet = NAS_UTRANCTRL_SndAsMsg( WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);
        /* ����ʧ�� */
        if ( VOS_OK != ulRet)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNasCommInfoChangeReq():ERROR:Message sends fail");
        }
        return;
    }

    PS_MEM_CPY(&(pstMsg->stNasCommInfo), pstNasComInfo, sizeof(NAS_COMM_INFO_STRU));


    /*������Ϣ*/
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNasCommInfoChangeReq():ERROR:Message sends fail");
        return;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsNasUsimStatus
 ��������  : ��G/U����㷢��NAS�Ŀ�״̬��Ϣ
 �������  : enUsimStatus - ��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��28��
   ��    ��  :  w00167002
   �޸�����  :  �����ɺ���
 2.��    ��   : 2012��11��9��
   ��    ��  :  z00161729
   �޸�����  :  DTS2012110808375:W��ע�ᱻ��#3����cs ps����Ч��֪ͨGas,����w acceptableС����ѡ��g��
                g��֪����Ч�ᷢ��suitableС����ѡ��L
 3.��    ��   : 2012��12��27��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:ƽ̨���뼼��������W/TD����֧��ʱ������Ҫ��WRR������Ϣ
                ƽ̨���뼼��������֧��Gʱ������Ҫ��GAS������Ϣ

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsNasUsimStatus(
    RRC_NAS_USIM_STATUS_ENUM_UINT32     enUsimStatus
)
{

    NAS_COMM_INFO_STRU                 stNasComInfo;

    PS_MEM_SET( &stNasComInfo, 0X0, sizeof(NAS_COMM_INFO_STRU) );

    /* ���췢�͸���������Ϣ */
    stNasComInfo.bitOpUsimValid         = VOS_TRUE;
    stNasComInfo.enUsimStatus           = enUsimStatus;


    /* ƽ̨���뼼������֧��W��TDʱ����Ҫ��WRR������Ϣ */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        /* ��WAS���Ϳ���Чָ֪ͨʾ */
        NAS_MMC_SndAsNasCommInfoChangeReq(WUEPS_PID_WRR, &stNasComInfo);
    }

    /* ƽ̨���뼼������֧��Gʱ����Ҫ��GAS������Ϣ */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        /* ��GAS���Ϳ���Чָ֪ͨʾ */
        NAS_MMC_SndAsNasCommInfoChangeReq(UEPS_PID_GAS, &stNasComInfo);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsRatCapabilityStatusChangeInfo
 ��������  : �����뼼���Ľ�ֹ��Ϣ�����仯ʱ���͸�AS
 �������  : stRatCapaStatusNasCommInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 Ŀǰ��֧���������ֽ�ֹ���뼼�������
    1. NUM = 1; RAT = LTE;
    2. NUM = 2; RAT = LTE + 3G;
 ���Ŀǰ����������������Ϣʱ�������������������

 �޸���ʷ     :
 1.��    ��   : 2013��11��01��
   ��    ��   :  l00208543
   �޸�����   :  �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsRatCapabilityStatusChangeInfo(VOS_VOID)
{
    NAS_COMM_INFO_STRU                  stNasComInfo;
    VOS_UINT8                           ucIsNeedSendAsChangeInfo;

    PS_MEM_SET( &stNasComInfo, 0X00, sizeof(NAS_COMM_INFO_STRU) );

    ucIsNeedSendAsChangeInfo = VOS_FALSE;

    /* ��ȡNVʱ����������飬���NUM��1�Ļ�����Disable Lte Only;
                                 NUM��2�Ļ�����Disable LTE+UTRAN */

    if (NAS_MML_RAT_CAPABILITY_STATUS_BUTT != NAS_MML_GetLteForbiddenStatusFlg())
    {
        ucIsNeedSendAsChangeInfo            = VOS_TRUE;
        stNasComInfo.bitOpLTECapability     = VOS_TRUE;
        stNasComInfo.enLCapabilityStatus    = NAS_MML_GetLteForbiddenStatusFlg();
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_BUTT != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        ucIsNeedSendAsChangeInfo            = VOS_TRUE;
        stNasComInfo.bitOpUTRANCapability   = VOS_TRUE;
        stNasComInfo.enUCapabilityStatus    = NAS_MML_GetUtranForbiddenStatusFlg();
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_BUTT != NAS_MML_GetGsmForbiddenStatusFlg())
    {
        ucIsNeedSendAsChangeInfo            = VOS_TRUE;
        stNasComInfo.bitOpGSMCapability     = VOS_TRUE;
        stNasComInfo.enGCapabilityStatus    = NAS_MML_GetGsmForbiddenStatusFlg();
    }

    /* ���ȫ��BUTT������Ҫ���� */
    if (VOS_FALSE == ucIsNeedSendAsChangeInfo)
    {
        return;
    }

    /* ���ƽ̨֧��GSM����GAS������Ϣ */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportGsm() )
    {
        NAS_MMC_SndAsNasCommInfoChangeReq(UEPS_PID_GAS, &stNasComInfo);
    }

    /* ���ƽ̨֧��UTRAN����UTRAN��ʹ���ֶ���Ч������WRR������Ϣ */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportUtran() )
    {
        NAS_MMC_SndAsNasCommInfoChangeReq(WUEPS_PID_WRR, &stNasComInfo);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsLteCapabilityStatus
 ��������  : ��G/U����㷢��LTE�Ŀ�״̬��Ϣ
 �������  : ulReceiverPid
             enLteCapabilityStatus
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��5��
   ��    ��  :  w00176964
   �޸�����  :  �����ɺ���
 2.��    ��   : 2012��12��27��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:ƽ̨���뼼��������W/TD����֧��ʱ������Ҫ��WRR������Ϣ
               ƽ̨���뼼��������֧��Gʱ������Ҫ��GAS������Ϣ

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsLteCapabilityStatus(
    VOS_UINT32                                              ulReceiverPid,
    RRC_NAS_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus
)
{
    NAS_COMM_INFO_STRU                  stNasComInfo;

    PS_MEM_SET( &stNasComInfo, 0X0, sizeof(NAS_COMM_INFO_STRU) );

    /* ���췢�͸���������Ϣ */
    stNasComInfo.bitOpLTECapability     = VOS_TRUE;
    stNasComInfo.enLCapabilityStatus    = (VOS_UINT8)enLteCapabilityStatus;

    /* ulReceiverPidΪWRR������ƽ̨֧��UTRANʱ����WRR������Ϣ */
    if ( (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
      && (WUEPS_PID_WRR == ulReceiverPid) )
    {
        /* ��WAS����LTE����״ָ̬ʾ */
        NAS_MMC_SndAsNasCommInfoChangeReq(WUEPS_PID_WRR, &stNasComInfo);
    }

    /* ulReceiverPidΪGAS������ƽ̨֧��GSMʱ����GAS������Ϣ */
    if ( (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
      && (UEPS_PID_GAS == ulReceiverPid) )
    {
        /* ��GAS����LTE����״ָ̬ʾ */
        NAS_MMC_SndAsNasCommInfoChangeReq(UEPS_PID_GAS, &stNasComInfo);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SndGuAsUeOocStatus
 ��������  : ֪ͨ��ǰWAS��GAS UE�Ѿ����������������
 �������  : ulReceiverPid:������Ϣ��PID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��31��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��14��
    ��    ��   : W00176964
    �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
*****************************************************************************/
VOS_VOID  NAS_MMC_SndGuAsUeOocStatus(
    VOS_UINT32                          ulReceiverPid
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                                  ulRet;
    /* ����ԭ������ָ�� */
    RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGuAsUeOocStatus():ERROR:Memory Alloc Error for pstMsg");
        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(RRMM_UE_OOC_STATUS_NOTIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid             = ulReceiverPid;
    pstMsg->MsgHeader.ulMsgName                 = RRMM_UE_OOC_STATUS_NOTIFY_IND;


    /*������Ϣ*/
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGuAsUeOocStatus():WARNING:MMC SEND AS SUSPEND RSP failed!");
    }

}
/* NAS_MMC_SndAsTransactionStatus�Ƶ�MM���� */


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsHplmnReq
 ��������  : ��AS����HPLMN��EHPLMN
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : W00166186
    �޸�����   : AT&T&DCM��������
  2.��    ��   : 2012��12��27��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE:ƽ̨���뼼��������W/TD����֧��ʱ������Ҫ��WRR������Ϣ
               ƽ̨���뼼��������֧��Gʱ������Ҫ��GAS������Ϣ

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsHplmnReq(
    VOS_UINT32                          ulReceiverPid
)
{
    NAS_COMM_INFO_STRU                  stNasCommInfoChange;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stImsiHplmn;
    VOS_UINT8                           i;
    NAS_MML_HPLMN_TYPE_ENUM_UINT8       enHplmnType;

    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;

    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    PS_MEM_SET(&stNasCommInfoChange, 0, sizeof(NAS_COMM_INFO_STRU));

    stNasCommInfoChange.bitOpHPlmn  = 1;
    stNasCommInfoChange.bitOpEHPlmn = 1;

    enHplmnType   = NAS_MML_GetHPlmnType();

    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    /* ��ǰHPLMN����ΪHPLMN����ACTING-HPLMN */
    if ((NAS_MML_HPLMN_TYPE_HPLMN == enHplmnType)
     || (NAS_MML_HPLMN_TYPE_ACTING_HPLMN == enHplmnType))
    {
        /* ��ֵHPLMN */
        stNasCommInfoChange.stHPlmn.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc;
        stNasCommInfoChange.stHPlmn.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc;

        /* ��EHPLMN�ĸ�������Ϊ0 */
        stNasCommInfoChange.stEHPlmn.ucEHPlmnNum = 0;

    }
    /* ��ǰHPLMN����ΪEHPLMN */
    else if (NAS_MML_HPLMN_TYPE_EHPLMN == enHplmnType)
    {
        /* ��ֵHPLMN */
        stImsiHplmn = NAS_MML_GetImsiHomePlmn(pstMsIdentity->aucImsi);
        stNasCommInfoChange.stHPlmn.ulMcc = stImsiHplmn.ulMcc;
        stNasCommInfoChange.stHPlmn.ulMnc = stImsiHplmn.ulMnc;

        /* ��ֵEPLMN */
        stNasCommInfoChange.stEHPlmn.ucEHPlmnNum = pstEHPlmnInfo->ucEhPlmnNum;

        for (i = 0; i < pstEHPlmnInfo->ucEhPlmnNum; i++)
        {
            stNasCommInfoChange.stEHPlmn.astEHPlmnList[i].ulMcc = pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc;
            stNasCommInfoChange.stEHPlmn.astEHPlmnList[i].ulMnc = pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc;
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsHplmnReq(): HPLMN TYPE ERROR");
        return;
    }

    /* ulReceiverPidΪWRR������ƽ̨֧��UTRANʱ����WRR������Ϣ */
    if ( (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
      && (WUEPS_PID_WRR == ulReceiverPid) )
    {
        /* ��AS����HPLMN��EHPLMN */
        NAS_MMC_SndAsNasCommInfoChangeReq(WUEPS_PID_WRR, &stNasCommInfoChange);
    }

    /* ulReceiverPidΪGAS������ƽ̨֧��GSMʱ����GAS������Ϣ */
    if ( (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
      && (UEPS_PID_GAS == ulReceiverPid) )
    {
        /* ��AS����HPLMN��EHPLMN */
        NAS_MMC_SndAsNasCommInfoChangeReq(UEPS_PID_GAS, &stNasCommInfoChange);
    }
}

#if (FEATURE_ON == FEATURE_DSDS)

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsBeginSessionNotify
 ��������  : ��AS����RRMM_BEGIN_SESSION_NOTIFY
 �������  : ulReceivedPid - ����pid
             enSessionType - ֪ͨ������session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsBeginSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    VOS_UINT32                          ulRet;
    RRMM_BEGIN_SESSION_NOTIFY_STRU     *pstMsg    = VOS_NULL_PTR;

    pstMsg = (RRMM_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBeginSessionNotify():ERROR:Memory Alloc Error for pstMsg");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid             = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName                 = RRMM_BEGIN_SESSION_NOTIFY;
    pstMsg->enSessionType                         = enSessionType;

    /*������Ϣ*/
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    /* ����ʧ�� */
    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsBeginSessionNotify():ERROR:Message sends fail");

        return;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsEndSessionNotify
 ��������  : ��AS����RRMM_END_SESSION_NOTIFY
 �������  : ulReceivedPid - ����pid
             enSessionType - ֪ͨ������session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��18��
    ��    ��   : b00269685
    �޸�����   : �����ӳ�ʱ��

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsEndSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType,
    VOS_UINT32                          ulDelayTime
)
{
    VOS_UINT32                          ulRet;
    RRMM_END_SESSION_NOTIFY_STRU       *pstMsg    = VOS_NULL_PTR;


    pstMsg = (RRMM_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_END_SESSION_NOTIFY_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsEndSessionNotify():ERROR:Memory Alloc Error for pstMsg");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid             = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName                 = RRMM_END_SESSION_NOTIFY;
    pstMsg->enSessionType                         = enSessionType;
    pstMsg->enCsRelAll                            = VOS_FALSE;
    pstMsg->enPsRelAll                            = VOS_FALSE;
    pstMsg->ulDelayTime                           = ulDelayTime;

    /*������Ϣ*/
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsEndSessionNotify():ERROR:Message sends fail");

        return;
    }
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsNetScanReq
 ��������  : ��AS����RRMM_NET_SCAN_REQ
 �������  : enRat                  :������Ϣ�Ľ��뼼��
             pstNetScanReq          :��Ҫ���͸�AS������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsNetScanReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceiverPid;

    /* ����ԭ������ָ�� */
    RRMM_NET_SCAN_REQ_STRU             *pstMsg    = VOS_NULL_PTR;

    pstMsg = (RRMM_NET_SCAN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_NET_SCAN_REQ_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNetScanReq():ERROR:Memory Alloc Error for pstMsg");
        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(RRMM_NET_SCAN_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    if ( NAS_MML_NET_RAT_TYPE_GSM == enRat )
    {
        ulReceiverPid = UEPS_PID_GAS;
    }
    else
    {
        ulReceiverPid = WUEPS_PID_WRR;
    }

    pstMsg->stMsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid             = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName                 = RRMM_NET_SCAN_REQ;

    /* ����ǿ�ָ�� */
    NAS_MMC_ConvertNasRatToRrcFormat(pstNetScanReq->ucRat, &(pstMsg->enRat));
    pstMsg->usFreqNum                      = pstNetScanReq->usCellNum;
    pstMsg->sPower                         = pstNetScanReq->sCellPow;
    pstMsg->stBand.stGsmBand.ulGsmBand     = pstNetScanReq->stBand.unGsmBand.ulBand;
    pstMsg->stBand.stWcdmaBand.ulWcdmaBand = pstNetScanReq->stBand.unWcdmaBand.ulBand;

    PS_MEM_CPY(&pstMsg->stBand.stLteBand, &pstNetScanReq->stBand.stLteBand, sizeof(pstMsg->stBand.stLteBand));

    /*������Ϣ*/
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNetScanReq():ERROR:Message sends fail");
        return;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsStopNetScanReq
 ��������  : ��AS����RRMM_NET_SCAN_STOP_REQ
 �������  : enRat          :������Ϣ�Ľ��뼼��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndAsNetScanStopReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulReceiverPid;

    /* ����ԭ������ָ�� */
    RRMM_NET_SCAN_STOP_REQ_STRU        *pstMsg    = VOS_NULL_PTR;

    pstMsg = (RRMM_NET_SCAN_STOP_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_NET_SCAN_STOP_REQ_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNetScanStopReq():ERROR:Memory Alloc Error for pstMsg");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(RRMM_NET_SCAN_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    if ( NAS_MML_NET_RAT_TYPE_GSM == enRat )
    {
        ulReceiverPid = UEPS_PID_GAS;
    }
    else
    {
        ulReceiverPid = WUEPS_PID_WRR;
    }

    pstMsg->stMsgHeader.ulSenderCpuId             = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid             = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName                 = RRMM_NET_SCAN_STOP_REQ;

    /*������Ϣ*/
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MMC, (struct MsgCB **)&pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsNetScanStopReq():ERROR:Message sends fail");

        return;
    }
}






#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRrmRegisterInd
 ��������  : ��RRM����ID_PS_RRM_REGISTER_IND��Ϣ
 �������  : enModemId          :��ǰ��MODEM ID
             enTaskType         :ע����������
             enRatType          :����ģʽ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��26��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�ӿ��޸�

*****************************************************************************/
VOS_VOID NAS_MMC_SndRrmRegisterInd(
    MODEM_ID_ENUM_UINT16               enModemId,
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType,
    VOS_RATMODE_ENUM_UINT32            enRatType
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrmRegisterInd():ERROR:Memory Alloc Error for pstMsg");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = enModemId;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = enRatType;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrmRegisterInd():ERROR:Message sends fail");

        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRrmDeRegisterInd
 ��������  : ��RRM����ID_PS_RRM_DEREGISTER_IND��Ϣ
 �������  : enModemId          :��ǰ��MODEM ID
             enTaskType         :ע����������
             enRatType          :����ģʽ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��26��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�ӿ��޸�

*****************************************************************************/

VOS_VOID NAS_MMC_SndRrmDeRegisterInd(
    MODEM_ID_ENUM_UINT16               enModemId,
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType,
    VOS_RATMODE_ENUM_UINT32            enRatType
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrmRegisterInd():ERROR:Memory Alloc Error for pstMsg");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = enModemId;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = enRatType;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    /* ����ʧ�� */
    if ( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrmDeRegisterInd():ERROR:Message sends fail");

        return;
    }

    return;
}

#endif
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

