/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_CellProc3.c
  Description  : MM��������
  Function List:

  History:
   1.��    ��   : 2009��09��23��
     ��    ��   : x00115505
     �޸�����   : AT2D14632,����ע��ʧ�ܣ���ѯCREG����1
  2.��    ��   : 2009��11��03��
     ��    ��   : x00115505
     �޸�����   : ���ⵥ�ţ�AT2D15222,��������������ע��
  3.��    ��   : 2009��11��09��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�AT2D15401,CS�ػ�Detach����ʱ��̫�̣�û�еȵ������ͷ����Ӿͳ�ʱ�����ͷ���

  4.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������

  5.��    ��   : 2010��3��23��
    ��    ��   : zhoujun /z40661
    �޸�����   : AMR���ʵ���
  6.��    ��   : 2010��5��3��
    ��    ��   : x00115505
    �޸�����   : ���ⵥ�ţ�AT2D18886,MM����WRR�����������ӽ����������
  7.��    ��   : 2010��11��22��
    ��    ��   : h44270
    �޸�����   : DTS201011700067,û�д���ϵͳ��Ϣ�����µ绰�ҶϺ�û�з���LAU��
*******************************************************************************/

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmlCtx.h"
#include        "NasMmSndOm.h"


 /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
#include "NasStkInterface.h"
 /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
#include "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-22, end */
#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC3_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/
extern VOS_UINT8 GMM_IsGasCellReselect(VOS_VOID);

/*lint -save -e958 */

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E66
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-24  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
     3.��    ��   : 2012��04��03��
       ��    ��   : l65478
       �޸�����   : DTS2012032702913:��CS���ں���ʱ�յ�SS���ͷ����������CS���ӱ�־
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E66(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */

        /*lint -e701*/
        if ((MM_CONST_NUM_7 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & (0x01 << g_MmSsRelReq.ulTi))))
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)(0x01 << g_MmSsRelReq.ulTi);                       /* ����ñ�־λ                             */
        }
        if ((MM_CONST_NUM_7 < g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_15 > g_MmSsRelReq.ulTi)
            && (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & (0x01 << (g_MmSsRelReq.ulTi - 8)))))
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)(0x01 << (g_MmSsRelReq.ulTi - 8));                 /* ����ñ�־λ                             */
        }
        if ((MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
          && (MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* MM��������                               */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E66:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */

            NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
        }


        /*lint +e701*/

    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E66
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬���յ�MMSS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746      06-11-21  Create for A32D07452
     2.��    ��   :2013��8��13��
       ��    ��   :z00161729
       �޸�����   :DTS2013081207431:mm����״̬�յ�cc��t303��ʱabort��Ϣ����Ҫ���棬�յ�resume indʱ�ٴ���
     3.��    ��   : 2014��5��22��
       ��    ��   : z00161729
       �޸�����   : DTS2014050601476:L��绰�ض���g�����е绰�Ҷϣ�mm����cc abort��g��ѯcsfb״̬�Ǵ��ڣ�lau������û����������FR���̵�L
     4.��    ��   : 2014��6��13��
       ��    ��   : w00242748
       �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E66(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                       )
{
    if (MM_FALSE == Mm_RcvSsRelReq(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E66:WARNING: Rcv SS Rel Req error.");
    }
    else
    {
        if ( (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI == g_MmSsRelReq.ulTi )
          && (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg))
        {
            /* ��ֹ��MM���ӽ��������ڽ�����             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if (( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
             && ( g_MmSsRelReq.ulTi == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }

    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S24_E13
  FUNCTION : ��LOCATION UPDATE REJECTED״̬��,�յ�MMCMM_NETWORK_DETACH_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2004.03.12  �°�����
     2.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* ��¼��ǰ������                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        ;                                                                       /* �մ���                                   */
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ����������Bģʽ��ȫ����                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                     (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);/* ��¼���̺�ԭ��ֵ                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            break;
        default:
            break;
        }
    }

}

/*******************************************************************************
  Module:   Mm_Cell_S3_E14
  Function: ��MM IDLE NORMAL SERVICE״̬��,
                �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��־��     2004.03.10  �°�����
      2.��    ��   : 2011��7��26��
        ��    ��   : l00130025
        �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
      3.��    ��   : 2011��11��22��
        ��    ��   : w00166186
        �޸�����   : DTS2011111003960,PSҵ�������ɹ���ԭ��ֵ32λǿ��ת��Ϊ8λ����
      4.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      5.��    ��   : 2013��06��04��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ��PS��ԭ��ֵ12�ܾ�,CSע��״̬��Ҫ����Ϊ0
      6.��    ��   : 2013��11��29��
        ��    ��   : w00242748
        �޸�����   : DTS2013112612348:CS����ԭ��ֵ15���ͷ����ӣ���LIMIT SERVICE
                     PS����ԭ��ֵ12����ʱ������������
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT8                                ucState;

    ucState                             = g_MmGlobalInfo.ucState;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
        {                                                                       /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
            if (MM_GMM_SR_PROC == ucActionType)
            {
                Mm_ComGmmSrCauseHandle(pstGmmActionRstInd->enCause);   /* ����SR����ԭ��ֵ�Ĺ�������               */
            }
        }
        else
        {                                                                       /* ���Ϊ��A+Iģʽ�ĳ���                    */
            if (MM_NULL_PROC != ucActionType)
            {
                Mm_ComCauseHandleAllProc(ucActionType,
                                         pstGmmActionRstInd->enCause); /* ����ԭ��ֵ�Ĵ���                         */

                if ( (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                  && ( (MM_IDLE_NORMAL_SERVICE == ucState)
                    || (MM_IDLE_ATTEMPTING_TO_UPDATE == ucState) ) )
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                            MM_MMC_LU_RESULT_FAILURE,
                            NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E14
  Function: ��LOCATION UPDATE REJECTED״̬��,
                �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.10  �°�����
      2.��    ��   : 2011��03��31��
        ��    ��   : c00173809
        �޸�����   : ���ⵥ��:DTS2011032802664,UEפ��VPLMN����BG��,פ�������ȼ�
                     ����,COMBINED RAU PS�ɹ�,CS�ܾ�ԭ��15,û�ѵ�ǰ����.
      3.��    ��   : 2012��11��30��
        ��    ��   : l00167671
        �޸�����   : ���ⵥ��:dts2012112800374,W��CS���ȱ��ܾ�ԭ��ֵ15��PS�򱻾�
                     15��MM����NORMAL SERVICE״̬
      4.��    ��   : 2014��4��2��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU       *pstGmmActionRstInd;
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S24_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                          (VOS_UINT8)pstGmmActionRstInd->enCause); /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if (MM_GMM_ATTACH_PROC == ucActionType)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmServiceState is MM_NO_IMSI");
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                    Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ��ȫ����                  */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                break;

            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                /* ��LOCATION UPDATE REJECTED״̬���յ�PS��ܾ�ԭ��ֵ15ʱ����CS�򱻾ܵ�ԭ��ֵ���� */
                break;

            default:
                break;
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E16
  Function: ��LOCATION UPDATE REJECTED״̬��,
                �յ�MMCMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.12  �°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S24_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S24_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* ����ɾ��IMSI�Ĺ�������                   */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E16:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
}

/*******************************************************************************
  Module:   Mm_Cell_S25_E16
  Function: ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬��,
                            �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.12  �°�����
      2. ��    ��   : 2007��08��19��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥ�ţ�A32D12706
       3.��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComToNoImsiHandle();

    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
    Mm_ComSetMmState(IMSI_DETACH_INITIATED);


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E16:NORMAL: STATUS is MM_STATE_NULL");
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E16
  Function: ��IMSI DETACH INITIATED״̬��,
                            �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.12  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S26_E16(VOS_VOID* pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_ComToNoImsiHandle();
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E22
  Function: ��MM IDLE NORMAL SERVICE״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2. ��־��        2005.01.27  007037 for MM
  3.  ��    ��   : 2008��09��03��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  4.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7. ��    ��   : 2012��3��15��
     ��    ��   : w00166186
     �޸�����   : V7R1 C50 CSFB&PPAC&ETWS&ISR����
   8.��    ��   : 2013��2��4��
     ��    ��   : w00176964
     �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
   9.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   10.��    ��   : 2013��6��18��
     ��    ��   : w00167002
     �޸�����  : SVLTE ��usim�ӿڵ����޸�
   11.��    ��   : 2013��11��11��
     ��    ��   : l65478
     �޸�����  : DTS2013110800070:3����̨�������������·���USSDҵ��,����CSҵ���쳣
  12.��    ��   : 2014��6��13��
     ��    ��   : w00242748
     �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                         /* ���ý�ֹע��CS��ı�ʶ                   */

                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;              /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
                Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                                 NAS_MML_GetSimCsSecurityCksn());     /* ����MM��Ϣ                               */

                /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
                if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                             & MM_WAIT_CS_DETACH))
                {
                    NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                    /* ����ȴ���־ */
                    g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
                }

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;          /* ����DETACH����                           */

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                     /* ��������TIMER                            */

                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
                g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* ���÷���״̬                             */
            }
        }
        else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);                             /* ���ý�ֹע��CS��ı�ʶ                   */
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                  /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E22:INFO: MmServiceState is MM_DETACHED");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* ����MM��Ϣ                               */

            /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        }
        else
        {

        }
    }

}
/*******************************************************************************
  Module:   Mm_Cell_S4_E22
  Function: ��MM IDLE LIMITED SERVICE״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2.  ��    ��   : 2008��09��03��
      ��    ��   : l00130025
      �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  3.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  6. ��    ��   : 2012��2��15��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ����
  7.��    ��   : 2012��12��25��
    ��    ��   : l00167671
    �޸�����   : ���ⵥ��DTS2012122509118��L�������������ʱ��W���ѵ����ϴ�ע����ͬ��С��
                   �ȷ�����LU
  8.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��6��8��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��������޸�:nO CELL AVAILABLE״̬ʱ��ʵҲ����ҪǨ��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                      /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E22:INFO: MmServiceState is MM_DETACHED");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        if ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E22:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }
}
/*****************************************************************************
 �� �� ��  : Mm_Cell_S6_E22
 ��������  : ��MM_IDLE_LOCATION_UPDATE_NEEDED״̬�յ�DETACH REQ�Ĵ���
 �������  : VOS_VOID* pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��15��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S6_E22(VOS_VOID* pMsg)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enServiceStatus;

    enServiceStatus = NAS_MM_GetLauUptNeededCsSrvStatus();

    if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
     || (MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus))
    {
        Mm_Cell_S3_E22(pMsg);
    }
    else
    {
        Mm_Cell_S4_E22(pMsg);
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S8_E22
  Function: ��MM IDLE NO IMSI״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.12  �°�����
      2. ��    ��   : 2012��1��12��
         ��    ��   : w00166186
         �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                       PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.

      3.��    ��   : 2013��6��21��
        ��    ��   : w00167002
        �޸�����   : �����ǰ����Ч����Ҫ֪ͨ״̬ΪNO IMSI
*******************************************************************************/
VOS_VOID Mm_Cell_S8_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S8_E22:INFO: MmServiceState is MM_NO_IMSI");

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_NO_IMSI);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    }
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E22
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2004.03.12  �°�����
  2.��    ��   : 2008��09��03��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  8.��    ��   : 2012��12��18��
    ��    ��   : l65478
    �޸�����   : DTS2012121405450:�ͷ�����ԭ��ֵ����
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 11.��    ��   : 2013��6��8��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��װ�����б��Ƿ���GMM����CS��DETACH��
 12.��    ��   :2013��9��14��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
 13.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
 14.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;



    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        /* ͣ�ȴ�������ʱ�� */
        Mm_TimerStop(MM_TIMER_T3218);

        /* �ڼ�Ȩ�����У��������Ȩ��־��Ϣ */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* ֹͣ������ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(IMSI_DETACH_PENDING);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_PENDING");
        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

                if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
                {
                    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
                }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                  /* ����DETACH����                           */

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                        g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());         /* ����MM��Ϣ                               */

            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);
                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* ��¼���̺�ԭ��ֵ                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));                  /* ��дMobileID                             */

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);

            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }

    }
}
/*******************************************************************************
  Module:   Mm_Cell_S12_E22
  Function: ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2.  ��־��     2005.01.27  007037 for MM
  3. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  4.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 8.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 9.��    ��   : 2013��05��15��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
10.��    ��   : 2013��6��5��
   ��    ��   : w00167002
   �޸�����   : SVLTE:sunxibo��������޸ģ�״̬����Ǩ�Ƶ�NO IMSI,Ǩ�Ƶ�LIMIT
                    SERVICE״̬��
                2. ֹͣWAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ״̬�ı�����ʱ��;
                3. �����ǰ��CS detach��GMM���д������ͷŵ�ǰ�����ӣ�GMM�յ�GPRS
                   RESUMEָʾ��Ϣ�󣬷���DETACH;
 11.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
 12.��    ��   : 2013��11��11��
    ��    ��   : l65478
    �޸�����  : DTS2013110800070:3����̨�������������·���USSDҵ��,����CSҵ���쳣
 13.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
 14.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */
        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                                g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;              /* ����DETACH����                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                /* �����ȴ�������� */
                return;
            }

            /* ֹͣWAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ״̬�ı�����ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;

            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* ��д��Ϣ,������Ϣ                        */

            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                         /* ��������TIMER                            */

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E22:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S14_E22
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2. ��־��        2005.01.27  007037 for MM
  3. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  6.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  7.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  8.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

  7.��    ��   : 2013��6��5��
    ��    ��   : w00167002
    �޸�����   : SVLTE:����CS���Detach,����Ҫ����������ʱ��:SYSCFG������Detach��
                 ����ʱ��Ϊ15s��cgcatt������Detach��ʱ��Ϊ90s
                 2.sunxibo�������:Mm_Cell_S14_E22��״̬��ǰû���������ӣ�����ο�
                 Mm_Cell_S12_E22
                 3. �����ǰ��CS detach��GMM���д������ͷŵ�ǰ�����ӣ�GMM�յ�GPRS
                   RESUMEָʾ��Ϣ�󣬷���DETACH;
  8.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  9.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;


    /* ��ǰ�Ƿ���GMM�����û������detach */
    if ( VOS_TRUE == NAS_MM_IsNeedGmmProcUserDetach() )
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(IMSI_DETACH_PENDING);

        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */

        if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;
        }

        return;
    }

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                         g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            NAS_MM_LocalDetach();

        }
        else
        {

            Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;                      /* ����DETACH����                           */

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);


            /* �Ƚ����ɹ����ٷ���IMSI DETACH */
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E23
  Function: ��MM_NULL״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2. ��    ��   : 2006��9��9��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D05803
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());                     /* ����MM��Ϣ                               */

    Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
    }

    Mm_ComSetMmState(MM_STATE_NULL);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E23:NORMAL: STATUS is MM_STATE_NULL");
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E23
  Function: ��MM IDLE NORMAL SERVICE״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2.  ��־��        2005.01.27  007037 for MM
  3. ��    ��   : 2006��9��9��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D05803
  4. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

  6.��    ��   : 2012��2��23��
    ��    ��   : z40661
    �޸�����   : ֧��Lģ����ע��ʱ���յ�Lģ�·��Ĺػ���������Ӧ
  7.��    ��   : 2012��3��15��
    ��    ��   : w00166186
    �޸�����   : V7R1 C50 CSFB&PPAC&ETWS&ISR����
  8.��    ��   : 2012��9��07��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 11.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

#if (FEATURE_ON == FEATURE_LTE)

    /* �����ǰפ��LTE,��ֱ�ӻظ��ػ� */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        Mm_SndMmcPowerOffCnf();                                                 /* ��MMC����MMCMM_POWER_OFF_CNF             */

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

        return;
    }
#endif

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {

        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_IMSI");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);

            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */

            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }

    }
    else if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        Mm_SndMmcPowerOffCnf();                                                 /* ��MMC����MMCMM_POWER_OFF_CNF             */

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E23:NORMAL: STATUS is MM_STATE_NULL");

    }
    else
    {
    }
    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E23
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2. ��    ��   : 2007��3��20��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�A32D09497
  3. ��    ��   : 2007��08��19��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D12706
  4. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2012��3��15��
    ��    ��   : w00166186
    �޸�����   : V7R1 C50 CSFB&PPAC&ETWS&ISR����
  8.��    ��   : 2012��9��07��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
  9.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 10.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 11.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 12.��    ��   :2013��9��12��
    ��    ��   :z00161729
     �޸�����  :DTS2013082903019:֧��ss�ط�����
 13.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
 14.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
            Mm_TimerStart(MM_TIMER_T3240);
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */
            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S12_E23
  Function: ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.12  �°�����
  2. ��־��        2005.01.27  007037 for MM
  3. ��    ��   : 2007��08��19��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D12706
  4. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2012��3��15��
    ��    ��   : w00166186
    �޸�����   : V7R1 C50 CSFB&PPAC&ETWS&ISR����
  7.��    ��   : 2012��9��07��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
  8.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 11.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
 12.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
 13.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;

    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
            Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                            /* ��д��Ϣ,������Ϣ                        */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E23
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
            �յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2. ��־��        2005.01.27  007037 for MM
  3. ��    ��   : 2007��3��20��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�A32D09497
  4. ��    ��   : 2007��08��19��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D12706
  5. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  6.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  7.��    ��   : 2012��3��15��
    ��    ��   : w00166186
    �޸�����   : V7R1 C50 CSFB&PPAC&ETWS&ISR����
  8.��    ��   : 2012��9��07��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
  9.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 10.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 11.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 12.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 13.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
 14.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
      && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {


            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);

            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

            Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
            Mm_ComSetMmState(IMSI_DETACH_INITIATED);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* ��д��Ϣ,������Ϣ                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* ����������ʱ��                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);
                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */

                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E23:INFO: MmServiceState is MM_NO_SERVICE");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S22_E23
  Function: WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2007��06��01��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥA32D10964�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_NEED_DELAY;                        /* ����DETACH����                           */
    Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
}
/*******************************************************************************
  Module:   Mm_Cell_S25_E23
  Function: ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E23(VOS_VOID* pMsg)
{

    if (MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg))
    {
        return;
    }

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */
}

/*****************************************************************************
 �� �� ��  : NAS_MM_IsNeedStopT3213_EstCnf
 ��������  : �ж��ǲ�����Ҫֹͣ3213��ʱ����ԭ��ֵ
 �������  : RRC_NAS_EST_RESULT_ENUM_UINT32
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MM_IsNeedStopT3213_EstCnf(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulResult
)
{
    if ((RRC_EST_RANDOM_ACCESS_REJECT != ulResult)
     && (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO != ulResult)
     && (RRC_EST_RJ_RA_FAIL != ulResult)
     && (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO != ulResult))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S22_E32
  Function: ��WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��,�յ�RRMM_EST_CNF�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2.  ��־��     2005.01.27  007037 for MM
  3. ��    ��   : 2006��11��22��
     ��    ��   : l60022475
     �޸�����   : ���ⵥ�ţ�A32D07583
  4. ��    ��   : 2007��08��03��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�A32D12650
  5. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  6.��    ��   : 2008��11��22��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�AT2D06900,mmע��״̬�޸�
  7.��    ��   : 2009��08��25��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D14020,MM LU�����У�����ʧ�ܣ�cause: RRC_EST_EST_CONN_FAIL���ӹ淶��˵��
                 ��û��Ҫ�����LAI����ЧPLMN���������ˣ��ᵼ���ֶ�����ģʽ�£�MMCת����GMM��ϵͳ��Ϣ
                 �н�forbidden��־��λ��
  8.��    ��   : 2009��08��27��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D14089,������������G�£�LU����ʧ�ܣ�cause: RR_CONN_FAIL��T3211��ʱ��δ����LU.
  9.��    ��   : 2011��11��22��
    ��    ��   : z00161729
    �޸�����  : ���ⵥ�ţ�DTS2010111602266,G��CSע��ʧ��ԭ������ָ�ɾܾ�,MM���յ�
                RRMM_AC_INFORMATION_CHANGE_IND T3122��ʱ��Ϣ�󷴸�����LU,����PS��������ָ�,Ӱ����������
  10.��    ��   : 2011��01��27��
     ��    ��   : w00176964
     �޸�����   : ���ⵥ�ţ�DTS2011012701891,Cs connfail 4�κ󣬽��뵽LAI��ͬ�Ĳ�ͬС����û�з���LAU
  11.��    ��   : 2011��7��16��
     ��    ��   : h44270
     �޸�����   : V7R1 PhaseII�׶ε�����ע������
  12.��    ��   : 2011��7��25��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  13.��    ��   : 2012��2��15��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ����
  14.��    ��   : 2012��11��20��
     ��    ��   : l65478
     �޸�����   :DTS2012111901564:û��֪ͨMMCע����������MMC�쳣��������
  15.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  16.��    ��   : 2013��6��11��
     ��    ��   : w00167002
     �޸�����   : V9R1_SVLTE��������޸�:��LAU������ʱ���յ�CS���DETACH����ȵ�
                  �յ������������д�����������ɹ�����ֱ�������෢��DETACH,����
                  ֱ�ӱ���DETACH.
  17.��    ��   : 2013��08��07��
     ��    ��   : l65478
     �޸�����   : �޸����ⵥDTS2013080502397,����ѡ��G�½���LU��,Ȼ��GASָʾ�ض���Wԭ����С��ʱ�����Gs�ڲ�����,��Ҫ��������RAU
  18.��    ��   : 2013��6��11��
     ��    ��   : w00167002
     �޸�����   : DTS2013080802492:����ָ�ɾܾ���ɾ��EPLMN.

  19.��    ��   : 2013��8��22��
     ��    ��   : w00167002
     �޸�����   : DTS2013081604476:w��ѡ��G�º󣬱�����ָ�ɾܾ���GAS����T3122
                  ��ʱ���������û�����绰��NAS����LAU,GAS����T3122���У�ֱ�ӻظ�
                  ����ʧ�ܡ�MM������T3211,�����ֳ����£�NAS����Ҫ����T3211��ʱ����

                  TS24.008:4.4.4.9 Abnormal cases on the mobile station side
                  d)RR connection failure
                    The procedure is aborted and the mobile station proceeds as specified below.
                    In cases d) to h) (except in the case f.1) above and for repeated failures as defined in c) above the mobile station proceeds as follows. Timer T3210 is stopped if still running. The RR Connection is aborted in case of timer T3210 timeout. The attempt counter is incremented. The next actions depend on the Location Area Identities (stored and received from the BCCH of the current serving cell) and the value of the attempt counter.
                    -the update status is UPDATED, and the stored LAI is equal to the one received on the BCCH from the current serving cell and the attempt counter is smaller than 4:
                    The mobile station shall keep the update status to UPDATED, the MM IDLE sub-state after the RR connection release is NORMAL SERVICE. The mobile station shall memorize the location updating type used in the location updating procedure. It shall start timer T3211 when the RR connection is released. When timer T3211 expires the location updating procedure is triggered again with the memorized location updating type;

                    -either the update status is different from UPDATED, or the stored LAI is different from the
                    one received on the BCCH from the current serving cell, or the attempt counter is greater or
                    equal to 4:
                    When the RR connection is released the mobile station shall delete any LAI, TMSI, ciphering key
                    sequence number stored in the SIM/USIM, and list of equivalent PLMNs,
                    set the update status to NOT UPDATED and
                    enter the MM IDLE sub-state ATTEMPTING TO UPDATE
                    (see subclause 4.2.2.2 for the subsequent actions) or optionally the MM IDLE sub-state PLMN SEARCH (see subclause 4.2.1.2) in order to perform a PLMN selection according to 3GPP TS 23.122 [14]. If the attempt counter is smaller than 4, the mobile station shall

   20.��    ��   : 2014��4��2��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  21.��    ��   : 2014��6��4��
     ��    ��   : w00167002
     �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.
    22.��    ��   : 2013��3��28��
       ��    ��   : y00176023
       �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�RRC_EST_RJ_NO_RF�Ĵ���
    23.��    ��   : 2014��8��14��
       ��    ��   : z00161729
       �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau

    24.��    ��   : 2015��1��27��
       ��    ��   : w00167002
       �޸�����   : DTS2015012305099:BETA�����ֻ����йػ�����ǰ�ֻ�״̬Ϊ22��û��
                    ����LOG����������������������Ǩ��״̬ʱ��ͣ������ʱ��������ͣ��
	25.��    ��   : 2015��3��17��
       ��    ��   : b00269685
       �޸�����   : ���Ӷ�access bar�Ĵ���
    26.��    ��   : 2015��3��16��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:����ʧ�ܺ�����T3212��ʱ��������һ��Сʱ���
                    LAU�ɹ����û������޸�Ϊ��RR����ʧ�ܺ�����T3212��ʱ��ʱ��
                   ����NV�������á�
   27.��    ��   : 2015��6��3��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
   28.��    ��   : 2015��8��13��
      ��    ��   : l00289540
      �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E32(VOS_VOID* pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    RRMM_EST_CNF_STRU*                                      pRrcEstCnf;
    VOS_UINT8                                               ucTiValidFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsGsmOnlyEstCnfRslt;
    VOS_UINT32                                  ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    ucTiValidFlg = MM_TRUE;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;



    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);


    /* ����ǰ�����CS��ȥע�� */
    /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4�½�����:If a RR connection
       exists and the ATT flag indicates that no detach procedure is required,
       the MM sublayer will release locally any ongoing MM connections before
       releasing the RR connection. If a MM specific procedure is active,
       the release of the RR connection may be delayed until the MM specific
       procedure is complete. lau�����������ͷ�ʱ��������detach,���lau����ʧ����������detach */
    if (VOS_TRUE == NAS_MM_IsNeedProcBufferedCsDetach_RcvLauEstCnf(pRrcEstCnf->ulResult))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrcEstCnf);

        return;
    }



    if (NAS_MM_IsNeedStopT3213_EstCnf(pRrcEstCnf->ulResult))
    {
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
        Mm_TimerStop(MM_TIMER_T3213);                                           /* ֹͣ�������ʧ�ܵĹ��� */
    }

    if ((RRC_EST_SUCCESS != pRrcEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrcEstCnf->ulResult))
    {
        /*���PS ONLY����ֱ�ӽ���limit service*/
        if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            Mm_ComCheckDelayMmConn(MM_FALSE);

            /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* PS ONLY��ECALL ONLYģʽ�²�����CS������attach���*/
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            return;
        }
    }

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION PRESENT!");
        }

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        Mm_TimerStart(MM_TIMER_T3210);                                          /* ����������ʱ��                           */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* �������������Ѵ���                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR���ӽ����ɹ�                           */
        Mm_ComSetMmState(LOCATION_UPDATING_INITIATED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING: RR CONNECTION ESTING!");
        break;

    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:


    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        /* ����2G�����´�����ԭ��RRC_EST_RANDOM_ACCESS_REJECT */
        ulIsGsmOnlyEstCnfRslt = NAS_MM_IsGsmOnlyEstCnfRslt(pRrcEstCnf->ulResult);

        if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
         && (VOS_TRUE == ulIsGsmOnlyEstCnfRslt))
        {
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;

            /* ������������������������ʧ�ܳ��� */
            if (g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                Mm_TimerStop(MM_TIMER_T3213);
                Mm_TimerStart(MM_TIMER_T3213);                                  /* ����T3213 */
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                break;
            }

            Mm_TimerStop(MM_TIMER_T3213);                                       /* ֹͣ�������ʧ�ܵĹ��� */
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;

            if ( (VOS_TRUE == ulIsTestCard)
              && ((RRC_EST_RANDOM_ACCESS_REJECT == pRrcEstCnf->ulResult)
               || (RRC_EST_RJ_RA_FAIL == pRrcEstCnf->ulResult)) )
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
        }

        NAS_MM_ProcLuAttemptCounter(pRrcEstCnf->ulResult);


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* ���LAI����,�Ҹ���״̬ΪU1��ʱ��         */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_NORMAL_SERVICE");


                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                              MM_MMC_LU_RESULT_FAILURE,
                                              NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); */           /* ��MMC����MMCMM_LU_RESULT_IND             */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);            /* ��MMC����MMCMM_LU_RESULT_IND             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn());
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
                g_T3211Flag = 1;
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");


                /* GSM�½���ʧ�ܣ�����RR_CONNECTION_FAILURE����, W�½���ʧ�ܣ��������̲��ı� */

                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* ��U2�Ĺ������� */
                Mm_ComToU2Handle();
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */

                Mm_TimerStart(MM_TIMER_T3211);                                  /* ����T3211                                */
            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E32:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* ��U2״̬�����浱ǰ��LAI��Ϣ */
            pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
            pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

            pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
            pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
            pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */

            NAS_MM_StartT3212Timer(NAS_MM_ConvertLauEstCnfRsltToT3212StartScean(pRrcEstCnf->ulResult));
        }


        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */

             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_ACCESS_BARRED:
        /* ����2G�����´�����ԭ��RRC_EST_IMMEDIATE_ASSIGN_REJECT */
        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
          && (RRC_EST_IMMEDIATE_ASSIGN_REJECT == pRrcEstCnf->ulResult) )
        {
            break;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt++;

        if ((RRC_EST_REGISTER_ACCESS_BARRED == pRrcEstCnf->ulResult)
         || (RRC_EST_ACCESS_BARRED          == pRrcEstCnf->ulResult))
        {
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);                       /* ��MMC����MMCMM_LU_RESULT_IND             */

            Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        }
        else
        {


            /* ����ָ�ɾܾ���ɾ��EPLMN */

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);                       /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E32:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");

        if (MM_FALSE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                                       /* û�еȴ���CC��������Ҫ������MM����       */
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���ӽ���ʧ��                           */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if (MM_FALSE == ucTiValidFlg)
            {
                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);
        break;

    case RRC_EST_RJ_T3122_RUNNING :

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);


        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

        if ( VOS_FALSE == NAS_MM_NotifyBufferedServiceRRConnNotExist() )
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        NAS_MM_EndBufferedCSServiceExceptEmergencyCall_ImmediateAssignReject();

        Mm_ComCheckDelayMmConn(MM_FALSE);

        break;


    case RRC_EST_RJ_NO_RF:
        NAS_MM_ProcLauEstCnfNoRf();
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E32:WARNING:  Result Abnormal");
        break;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

}
/*******************************************************************************
  Module:   Mm_Cell_S25_E32
  Function: ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬��,�յ�RRMM_EST_CNF�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2.  ��־��     2005.01.27  006044 for MM
  3.  ��־��     2005.01.27  007037 for MM
  4. ��    ��   : 2007��01��17��
     ��    ��   : luojian id:60022475
     �޸�����   : ���ⵥ�ţ�A32D08396
  5. ��    ��   : 2007��3��20��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�A32D09497
  6. ��    ��   : 2007��9��29��
     ��    ��   : luojian id:107747
     �޸�����   : ���ⵥ�� A32D12966
  7. ��    ��   : 2008��7��21��
     ��    ��   : luojian 00107747
     �޸�����   : ���ⵥ�ţ�AT2D04201/AT2D04536
  8. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  9.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  10.��    ��   : 2011��7��25��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  11.��    ��   : 2012��2��15��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ����
  12.��    ��   : 2012��12��11��
     ��    ��   : w00176964
     �޸�����   : ɾ������С����ֹҵ����,ͳһ��MMC�յ�ϵͳ��Ϣ��AC INFO CHANGEά��
  13.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  14.��    ��   : 2013��08��15��
     ��    ��   : l65478
     �޸�����   : DTS2013081404782MM�����ͷź�û��֪ͨGMM CSҵ�����
  15.��    ��   : 2013��8��22��
     ��    ��   : w00167002
     �޸�����   : DTS2013081604476:w��ѡ��G�º󣬱�����ָ�ɾܾ���GAS����T3122
                  ��ʱ���������û�����绰��NAS����LAU,GAS����T3122���У�ֱ�ӻظ�
                  ����ʧ�ܡ�MM������T3211,�����ֳ����£�NAS����Ҫ����T3211��ʱ����
  16.��    ��   : 2013��4��10��
     ��    ��   : y00176023
     �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�RRC_EST_RJ_NO_RF�Ĵ���
  17.��    ��   : 2014��8��14��
     ��    ��   : z00161729
     �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau


 18.��    ��   : 2014��9��29��
    ��    ��   : w00167002
    �޸�����   : DTS2014092501419:�ڽ���DETACHʱ�򣬴���RRC_EST_OTHER_ACCESS_BARRED��Ϣ
 19.��    ��   : 2015��7��22��
    ��    ��   : z00161729
    �޸�����   : DTS2015060807763:apͨ��cgcatt�·�imsi detach������ʧ�ܺ�mm
                 ����detach���ظ�detach cnfʱӦ�ô�limit service������normal
                 service��at����ظ�ok������error
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E32(VOS_VOID* pMsg)
{
    RRMM_EST_CNF_STRU*      pRrcEstCnf;

    if (MM_FALSE == Mm_RcvRrcEstCnf(pMsg))
    {
        return;
    }

    pRrcEstCnf = (RRMM_EST_CNF_STRU*)pMsg;
    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    NAS_MM_SetEstCnfResult(pRrcEstCnf->ulResult);

    switch(pRrcEstCnf->ulResult)
    {
    case RRC_EST_SUCCESS:
    case RRC_EST_PRESENT:
        if (RRC_EST_PRESENT == pRrcEstCnf->ulResult)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION PRESENT!");
            return;
        }

        Mm_TimerStart(MM_TIMER_T3220);                                          /* ����T3220                                */
        g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;                 /* �������������Ѵ���                       */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S25_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);                            /* RR���ӽ����ɹ�                           */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        break;
    case RRC_EST_ESTING:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: RR CONNECTION ESTING!");
        break;
    case RRC_EST_RJ_CONGEST:
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_REGISTER_ACCESS_BARRED:
    case RRC_EST_ACCESS_BARRED:

    case RRC_EST_OTHER_ACCESS_BARRED:

    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CELL_BAR:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
    case RRC_EST_RJ_SNW:

    case RRC_EST_RJ_NO_RF:

    case RRC_EST_RJ_T3122_RUNNING:

    case RRC_EST_RJ_INTER_RAT:
    case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
    case RRC_EST_RANDOM_ACCESS_REJECT:
    case RRC_EST_RJ_RA_FAIL:
    case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:

    case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        /* �����������ޣ����ñ�־λ */
        if (RRC_EST_REGISTER_ACCESS_BARRED  == pRrcEstCnf->ulResult)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }

        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-18, begin */
        /* �ǽ������в���������ע���Ѱ����� */
        if  (((RRC_EST_ACCESS_BARRED  == pRrcEstCnf->ulResult)
           || (RRC_EST_RJ_CELL_BAR == pRrcEstCnf->ulResult))
          && (MMCC_EMERGENCY_CALL   !=  g_MmCcEstReq.ulCallType))
        {
            NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
            NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        }
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-18, end */


        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */
            Mm_SndMmcPowerOffCnf();                                             /* ��MMC����MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E32:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E32:WARNING: Result Abnormal");
        break;
    }

}
/*****************************************************************************
 �� �� ��  :  Mm_Cell_S22_E33
 ��������  : ��WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��
             �յ�RRMM_REL_IND�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2008��10��15��
   ��    ��   : x00115505
   �޸�����   : ���ⵥAT2D06189

 2.��    ��   : 2010��8��9��
   ��    ��   : ŷ����
   �޸�����   : DTS2010080502211������������ֱ�ӻظ�RRMM_REL_IND��Ϣ��MMδ
                ����T3211���·���LU.
 3.��    ��   : 2011��7��16��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 4.��    ��   : 2011��11��10��
   ��    ��   : w00167002
   �޸�����   : ɾ������:g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                 ע��ʧ�ܴ����ﵽ���ʱ�������㣬���ǵȵ�Э��(24008: 4.4.4.5 Attempt Counter)
                 �������������������,�������³�����������:CS��ע��ʧ��4�Σ�PSʧ��5�Σ�MMC
                 ���ɵȴ�CSע�����ϱ�.ԭ����CSʧ��4�κ��յ�RRMM_REL_IND���յ�ϵͳ��Ϣ��
                 MM���������ϱ���ϵͳ��Ϣ����Attemp CounterָʾΪ0��MMC������ȴ�CSע�������ϱ���
 5.��    ��   : 2012��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2012021405430:W��ע��PS����15��CSע��δ��ɱ������ͷ�RRC���ӣ�
                ������W��ע��ɹ����쳣�����LAC��Ϣ���������յ��µ�ϵͳ��Ϣ��
                ��������LAU
 6.��    ��   : 2012��11��14��
   ��    ��   : t00212959
   �޸�����   : DTS2012111304815:TD�½���ʧ�ܣ�ֱ�ӻظ�rel_ind,MM�Ĵ�������
  7.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  8.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2014��01��09��
    ��    ��   : l65478
    �޸�����   : DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
 10.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
 11.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.

 12.��    ��   : 2015��3��16��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:����ʧ�ܺ�����T3212��ʱ��������һ��Сʱ���
                 LAU�ɹ����û������޸�Ϊ��RR����ʧ�ܺ�����T3212��ʱ��ʱ��
                 ����NV�������á�
*****************************************************************************/
VOS_VOID Mm_Cell_S22_E33(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucValidFlg;
    RRMM_REL_IND_STRU                   *pMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRst;
    MM_LAI_STRU                        *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCampLaiInfo  = VOS_NULL_PTR;

    pMsg = (RRMM_REL_IND_STRU *)pRcvMsg;
    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        ucRst = NAS_MM_RetryCurrentProcedureCheck(pMsg->ulRelCause,
                    pMsg->ulRrcConnStatus);
        if (VOS_TRUE == ucRst)
        {
            /* LAU���յ�ϵͳ��Ϣ�������·��� */
            g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;

            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* ��CS�����ڽ���CS������ʱ,���PS������Ҫ���ͷ����ڽ�����PS������,
           ��������������ͷ��������ڽ���������,�Ӷ���Ӱ�쵽CS���ҵ��.
           Ϊ�����������,�涨��������½�����NAS���͵������ͷ�ָʾ�е�
           ԭ��ֵ��ΪRRC_REL_CAUSE_NAS_REL_SUCCESS,MM���յ���ԭ��ֵ���ͷ�
           ָʾ֮����Ϊ����ʧ��,�����ȴ�����������ϱ�ϵͳ��Ϣ,���·�������.*/
        if (RRC_REL_CAUSE_NAS_REL_SUCCESS == pMsg->ulRelCause)
        {
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            /* �������LU���� */
            if (MM_FALSE == Mm_ComChkLu())
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
            }
        }
        else
        {

            /*���PS ONLY����ֱ�ӽ���limit service*/
            if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
            {
                 Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

                 NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                 Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                 PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                 Mm_ComCheckDelayMmConn(MM_FALSE);

                 /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
                /* PS ONLY��ECALL ONLYģʽ�²�����CS������attach���*/
                if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
                {
                    return;
                }
#endif
                /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, end */
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
                return;
            }



            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;
            }


            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

            if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
            {
                NAS_MM_ProcConnFailLauAttmptCntLess4_RcvRelInd(pMsg->ulRelCause);
            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E33:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
                NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);

                /* ��U2�Ĺ������� */
                Mm_ComToU2Handle();
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */


                /* T3212��ʱ���������� */
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_LAU_RRC_EST_REL_BY_AS);

            }

            NAS_MM_SndMmcRrConn_RcvRelInd();

            Mm_ComCheckDelayMmConn(MM_FALSE);
        }

        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S22_E33:WARNING: ulRelCause Abnormal");
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S23_E33
  Function: ��LOCATION UPDATING INITIATED״̬��,�յ�RRMM_REL_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����

  2.��    ��   : 2006��4��14��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D03031
  3.��    ��   : 2006��11��22��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ�ţ�A32D07583
  4.��    ��   : 2007��3��5��
    ��    ��   : liurui id:40632
    �޸�����   : �������ⵥ�ţ�A32D09094
  5.��    ��   : 2010��8��24��
    ��    ��   : w00167002
    �޸�����   : �������ⵥ�ţ�DTS2010081802144
  6.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  7.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  8.��    ��   : 2011��11��10��
    ��    ��   : w00167002
    �޸�����   : ɾ������:g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                 ע��ʧ�ܴ����ﵽ���ʱ�������㣬���ǵȵ�Э��(24008: 4.4.4.5 Attempt Counter)
                 �������������������,�������³�����������:CS��ע��ʧ��4�Σ�PSʧ��5�Σ�MMC
                 ���ɵȴ�CSע�����ϱ�.ԭ����CSʧ��4�κ��յ�RRMM_REL_IND���յ�ϵͳ��Ϣ��
                 MM���������ϱ���ϵͳ��Ϣ����Attemp CounterָʾΪ0��MMC������ȴ�CSע�������ϱ���
  9.��    ��   : 2012��2��28��
    ��    ��   : w00176964
    �޸�����   : DTS2012021405430:W��ע��PS����15��CSע��δ��ɱ������ͷ�RRC���ӣ�
                 ������W��ע��ɹ����쳣�����LAC��Ϣ���������յ��µ�ϵͳ��Ϣ��
                 ��������LAU
 10.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 11.��    ��   : 2014��01��09��
    ��    ��   : l65478
    �޸�����   : DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
 12.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
 13.��    ��   : 2014��5��5��
    ��    ��   : w00167002
    �޸�����   : dsds_ii:��Ȧ���Ӷȣ���REL:NO RF�쳣����£�
                 ����ͬRRC_REL_CAUSE_OTHER_REASON
 14.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.
 15.��    ��   : 2014��06��15��
    ��    ��   : s00217060
    �޸�����   : DTS2014061003286:TD2G��ѡ��G��RAU�����У��û�ָ����TD�����磬���粻��Ӧ����ҵ��accept
 16.��    ��   : 2015��6��23��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 17.��    ��   :2016��1��9��
    ��    ��   :z00359541
    �޸�����   :DTS2015111402223:����С���Ƿ�֧��CSMO��ʶ
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E33(VOS_VOID* pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
    RRMM_REL_IND_STRU*                                      pRrcRelInd;
    VOS_UINT8                                               ucTiValidFlg = MM_TRUE;
    VOS_UINT8                                               ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                                               ucRst;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    pRrcRelInd = (RRMM_REL_IND_STRU*)pMsg;

    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S23_E33: Rcv RR REL IND, Set CellNotSupportCsmoFlg to TRUE");
    NAS_MML_SetCellNotSupportCsmoFlg(VOS_TRUE);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*Ǩ��״̬��limit service*/
        /*���ñ�־Attach not allow*/
        /*ָʾ�ϲ�ҵ��ʧ��*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrcRelInd->ulRelCause,
                pRrcRelInd->ulRrcConnStatus);
    if (VOS_TRUE == ucRst)
    {
        /* LAU���յ�ϵͳ��Ϣ�������·��� */
        g_MmGlobalInfo.ucRetryLauFlg = VOS_TRUE;
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
        return;
    }


    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

    NAS_MM_UpdateLauRetryFlg_RcvRelInd(pRrcRelInd);



    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* ��Ҫ���MM�����GMM��causeֵ */
    Mm_ComProcCauseClear();

    /* ����ǰ�����CS��ȥע�� */
    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S24_E33
  Function: ��LOCATION UPDATE REJECTED״̬��,�յ�RRMM_REL_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2. ��    ��   : 2008��7��11��
     ��    ��   : l0010747
     �޸�����   : ���ⵥ��:AT2D03814
  3.��    ��   : 2011��11��10��
    ��    ��   : w00167002
    �޸�����   : ɾ������:if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt >= MM_CONST_NUM_4)
                            {
                                g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                            }
                 ע��ʧ�ܴ����ﵽ���ʱ�������㣬���ǵȵ�Э��(24008: 4.4.4.5 Attempt Counter)
                 �������������������,�������³�����������:CS��ע��ʧ��4�Σ�PSʧ��5�Σ�MMC
                 ���ɵȴ�CSע�����ϱ�.ԭ����CSʧ��4�κ��յ�RRMM_REL_IND���յ�ϵͳ��Ϣ��
                 MM���������ϱ���ϵͳ��Ϣ����Attemp CounterָʾΪ0��MMC������ȴ�CSע�������ϱ���
  4.��    ��   :2014��01��09��
    ��    ��   :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E33(VOS_VOID* pMsg)
{
    VOS_UINT8                   ucOldCsUpdateStatus;
    VOS_UINT8                   ucTempCsUpdateStatus;
    VOS_UINT8                   ucTiValidFlg = MM_TRUE;
    VOS_UINT8                   ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }

    NAS_MM_ClearAuthInfo();

    Mm_TimerStop(MM_TIMER_T3240);                                               /* ֹͣT3240                                */


    ucOldCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);                             /* ����ԭ��ֵ�Ĺ�������                     */
    ucTempCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    NAS_MML_SetCsUpdateStatus(ucOldCsUpdateStatus);

    NAS_MML_SetCsUpdateStatus(ucTempCsUpdateStatus);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();

    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_ComCheckDelayDetach();
}
/*****************************************************************************
 �� �� ��  : Mm_Cell_S25_E33
 ��������  : ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬��
             �յ�RRMM_REL_IND�Ĵ���,���������ΪAS�쳣,���Detach����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��29��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���,�������ⵥ�� A32D12966
  2.��    ��   : 2008��7��21��
    ��    ��   : luojian 00107747
    �޸�����   : ���ⵥ�ţ�AT2D04201/AT2D04536
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��2��28��
    ��    ��   : w00176964
    �޸�����   : DTS2012021405430:W��ע��PS����15��CSע��δ��ɱ������ͷ�RRC���ӣ�
                 ������W��ע��ɹ����쳣�����LAC��Ϣ���������յ��µ�ϵͳ��Ϣ��
                 ��������LAU
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2014��01��09��
    ��    ��   :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
  7.��    ��   : 2015��7��22��
    ��    ��   : z00161729
    �޸�����   : DTS2015060807763:apͨ��cgcatt�·�imsi detach������ʧ�ܺ�mm
                ����detach���ظ�detach cnfʱӦ�ô�limit service������normal service��
                at����ظ�ok������error
*****************************************************************************/
VOS_VOID  Mm_Cell_S25_E33( VOS_VOID* pMsg )
{
    VOS_UINT8                           ucValidFlg;

    ucValidFlg = Mm_RcvRrcRelInd(pMsg);

    if (MM_TRUE == ucValidFlg)
    {
        NAS_MM_ClearAuthInfo();

        Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
        {
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            Mm_SndMmcPowerOffCnf();
            Mm_ComSetMmState(MM_STATE_NULL);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is MM_STATE_NULL");
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E33:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
        }

        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E33:WARNING: ulRelCause Abnormal");
    }
    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E33
  Function: ��IMSI DETACH INITIATED״̬��,�յ�RRMM_REL_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����

  2.��    ��   : 2006��5��27��
    ��    ��   : liuyang id:48197
    �޸�����   : A32D04016
  3.��    ��   : 2007��06��01��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥA32D10964�޸�
  4.��    ��   : 2007��01��05��
    ��    ��   : l60022475
    �޸�����   : �������ⵥ�ţ�A32D12621
  5.��    ��   : 2007��08��19��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D12706
  6.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  7.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  8.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
   6.��    ��   : 2012��2��28��
     ��    ��   : w00176964
     �޸�����   : DTS2012021405430:W��ע��PS����15��CSע��δ��ɱ������ͷ�RRC���ӣ�
                  ������W��ע��ɹ����쳣�����LAC��Ϣ���������յ��µ�ϵͳ��Ϣ��
                  ��������LAU
   7.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   8.��    ��   :2014��01��09��
     ��    ��   :l65478
     �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ

*******************************************************************************/
VOS_VOID Mm_Cell_S26_E33(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    if (MM_FALSE == Mm_RcvRrcRelInd(pMsg))
    {
        return;
    }
    NAS_MM_ClearAuthInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* ֹͣT3220                                */
    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                          NAS_MML_GetSimCsSecurityCksn());

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E33:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /* ��Ҫ���MM�����GMM��causeֵ */
    Mm_ComProcCauseClear();
}
/*******************************************************************************
  Module:   Mm_Cell_S23_E51
  Function: ��LOCATION UPDATING INITIATED״̬��,���յ�T3210����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2. ��    ��   : 2008��7��11��
     ��    ��   : l0010747
     �޸�����   : ���ⵥ��:AT2D03814
  3. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  4.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E51(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    Mm_TimerStop(MM_TIMER_T3210);                                               /* ֹͣT3210                                */

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);          /* ��¼���̺�ԭ��ֵ                         */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_TimerStart(MM_TIMER_T3240);                                              /* ����T3240                                */
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {                                                                           /* �ж�LU Counter�Ƿ�С��4                  */
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ((VOS_FALSE == NAS_MML_IsCsLaiChanged()) &&
            (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {                                                                       /* �ж�LAI�Ƿ�δ�ı�,�Ҹ���״̬ΪU1         */
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* ���÷���״̬                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
    }

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E51:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E52
  Function: ��MM IDLE NORMAL SERVICE״̬��,���յ�T3211����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
      2.��    ��   : 2009��05��11��
        ��    ��   : h44270
        �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
      3.��    ��   : 2012��2��11��
        ��    ��   : l00130025
        �޸�����   : DTS2012020402238, GU->L->GU,CS֧���ҿ���Чʱ��T3211��ʱ��LAU������д����
      4.��    ��   : 2015��1��5��
        ��    ��   : z00161729
        �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E52(VOS_VOID* pMsg)
{
    /* AT&T ��������GSM-BTR-1-0644��GSM-BTR-1-0650��GSM-BTR-1-0652
       ��GSM-BTR-1-0656Ҫ������ģʽII��CS lau����#17��PS attach�ɹ���
       MM T3211��ʱ����ʱCS��lau����#17��Ҫ��PS��Ҫ��rau,�ó���MM��Ҫ֪ͨGMM��RAU*/
    if ((VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
      && (MM_NET_MODE_II == g_MmGlobalInfo.ucNewNtMod))
    {
        NAS_MM_SndGmmT3211ExpiredNotify(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);
    }

    if (g_MmGlobalInfo.LuInfo.ucLuType >= MM_IE_LUT_TYPE_BUTT)
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
    }

    Mm_ComLuOnly();                                                             /* ����LU REQ                               */
}


VOS_VOID Mm_Cell_S9_E52(VOS_VOID* pMsg)
{
    Mm_TimerStart(MM_TIMER_T3211);
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E53
  Function: ��MM IDLE NO CELL AVAILABLE״̬��,���յ�T3212����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
      2.  x51137  2006/4/14 A32D02955
      3.��    ��   : 2012��07��02��
        ��    ��   : l65478
        �޸�����   : DTS2012070206731, �ֶ�����ģʽ�ڳ���������T3212��ʱ�ؽ���������û�з���LAU
      4.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��

      5.��    ��   : 2014��9��20��
        ��    ��   : w00167002
        �޸�����   : DTS2014092400817:��A������ע�ᱻ��17�ﵽ������������T3212��ʱ��
                     ������������ʱ����ʱ�󴥷�������������ʱ��T3212��ʱ��������û��
                     ���ATTEMPT COUNTER,���º���ֻ������һ��LAU,����������T3212.
                     GCF26.7.4.3.3ʧ�ܡ�
      6.��    ��   : 2015��1��5��
        ��    ��   : z00161729
        �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S1_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;

        if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        }
        return;
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }

        if (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;                      /* ����T3212����ı�ʶ                      */
    }


    /* T3212��ʱ����ʱ��ATTEMPT 2 UPDATE״̬����Ҫ���COUNTERֵ */
    if (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetCsUpdateStatus())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E53
  Function: ��MM IDLE NORMAL SERVICE״̬��,���յ�T3212����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
      2.  x51137  2006/4/14 A32D02955
      3.��    ��   : 2007��05��11��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10713
      4.��    ��   : 2010��07��16��
        ��    ��   : l65478
        �޸�����   : ���ⵥ��:DTS2010070600029,����ģʽI��,ATTACHʧ�ܺ����LU,T3212��ʱ��ִ��LU����ʧ��
      5.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
      6.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      7.��    ��   : 2013��12��6��
        ��    ��   : w00242748
        �޸�����   : DTS2013120505497:G NMOI��PS����RAU����#17 5�κ�LAU�ɹ���T3212
                     Ӧ����LAU����DTS2010070600029���������Ҫ��GCF����ʱ������LAU��
                     ������Ҫ������GCF��������
      8.��    ��   : 2015��1��5��
        ��    ��   : z00161729
        �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    /* ����ģʽI�£����GMM�Ѿ�ע��������ڽ���ע�ᣬT3212������
    GCF44.2.1.2.8 */
    /* �˴��Ӳ��Կ��ж���Ϊ����GCF����ʱ��������LAU��������������Ҫ����LAU */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
          && (MM_NET_MODE_I    == g_MmGlobalInfo.ucNtMod))
        {
            if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
            {
                return;
            }
        }
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
             g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;           /* ����LU����                               */
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        Mm_ComLuOnly();                                                         /* ����LU REQ                               */
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E53
  Function: ��MM IDLE ATTEMPTING TO UPDATE״̬��,���յ�T3212����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
      2.  x51137  2006/4/14 A32D02955
      3.��    ��   : 2010��11��21��
        ��    ��   : z00161729
        �޸�����   : ���ⵥ�ţ�DTS2010111602266:G��CSע��ʧ��ԭ������ָ�ɾܾ�,MM���յ�
                     RRMM_AC_INFORMATION_CHANGE_IND T3122��ʱ��Ϣ�󷴸�����LU,����PS��������ָ�,Ӱ����������
      4.��    ��   : 2011��11��10��
        ��    ��   : w00167002
        �޸�����   : The attempt counter is reset in case of service state
                      ATTEMPTING to UPDATE, expiry of timer T3212;
                      ��Э��(24008: 4.4.4.5 Attempt Counter)
      5.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
      6.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      7.��    ��   : 2015��1��5��
        ��    ��   : z00161729
        �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E53(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    if ((VOS_TRUE  == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
    {
        if (MM_TRUE == g_MmGlobalInfo.ucLikeNetmode2)
        {
             g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* ����LU����                               */
             Mm_ComLuOnly();
        }
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* ����LU����                               */
        Mm_ComLuOnly();                                                         /* ����LU REQ                               */
    }

    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;

}

/*******************************************************************************
  Module:   Mm_Cell_S6_E54
  Function: ��MM_IDLE_LOCATION_UPDATE_NEEDED״̬��,
            ���յ�T3213����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  l40632  2006.04.20 create
      2.��    ��   : 2009��08��6��
        ��    ��   : l65478
        �޸�����   : ���ⵥ�ţ�AT2D13610������GCF����26.7.4.3.1ʧ�ܣ�ԭ��������ѡ��ԭ����С��������LAU
      3.��    ��   : 2014��8��14��
        ��    ��   : z00161729
        �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau
      4.��    ��   : 2015��8��13��
        ��    ��   : l00289540
        �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E54(VOS_VOID* pMsg)
{
    RRC_NAS_EST_RESULT_ENUM_UINT32      enEstCnfResult;

    enEstCnfResult = NAS_MM_GetEstCnfResult();

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        /* 24008 4.4.4.9������:
        c)  Random access failure (A/Gb mode only)
        Timer T3213 is started. When it expires the procedure is attempted again if still necessary.
        NOTE 1: As specified in 3GPP TS 45.008 [34], a cell reselection then takes place, with return to
        the cell inhibited for 5 seconds if there is at least one other suitable cell. Typically the
        selection process will take the mobile station back to the cell where the random access failed
        after 5 seconds.
        If at the expiry of timer T3213 a new cell has not been selected due to the lack of
        valid information (see 3GPP TS 45.008 [34]), the mobile station may as an option delay
        the repeated attempt for up to 8 seconds to allow cell re-selection to take place.
        In this case the procedure is attempted as soon as a new cell has been selected or
        the mobile station has concluded that no other cell can be selected.
        */
        if((VOS_TRUE == GMM_IsGasCellReselect())
        || (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
        || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult))
        {
            if(g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt < MM_CONST_NUM_2)
            {
                Mm_TimerStart(MM_TIMER_T3213);
            }
            else
            {
                Mm_TimerStart(MM_TIMER_T3211);
            }
        }
        else
        {
            Mm_ComLuOnly();
            g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt++;
        }

        if ( (RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO == enEstCnfResult)
          || (RRC_EST_RJ_RA_FAIL_NO_VALID_INFO           == enEstCnfResult) )
        {
            NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S26_E58
  Function: ��IMSI DETACH INITIATED״̬��,���յ�T3220����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2. ��    ��   : 2007��08��19��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D12706
  3. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  4.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.

  6.��    ��   : 2012��11��16��
    ��    ��   : z40661
    �޸�����   : DTS2012111403885,T3220��ʱ����ʱ,δ֪ͨ������ͷ�����
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S26_E58(VOS_VOID* pMsg)
{
    VOS_UINT8  ucTiValidFlg = MM_TRUE;
    VOS_UINT8  ucRrConnRelFlg = MM_TRUE;

    Mm_TimerStop(MM_TIMER_T3220);                                               /* ֹͣT3220                                */
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    switch(g_MmGlobalInfo.ucDetachType)
    {
    case MM_DETACH_CS_POWEROFF:
        Mm_TimerStop(MM_TIMER_STOP_ALL);
        Mm_ComSetMmState(MM_STATE_NULL);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_STATE_NULL");
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_SndMmcPowerOffCnf();
        break;
    case MM_DETACH_CS_NORMAL:
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());

        /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E58:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S26_E58:WARNING: Detach type Abnormal");
        break;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
}

/*******************************************************************************
  Module:   Mm_Cell_S24_E60
  Function: ��LOCATION UPDATE REJECTED״̬��,���յ�T3240����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.15  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E60(VOS_VOID* pMsg)
{
    Mm_T3240Expire();
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S23_E45
 ��������  : ��LOCATION UPDATING INITIATED״̬��,
            �յ�RRMM_DATA_IND(LOCATION UPDATING ACCEPT)�Ĵ���
 �������  : VOS_VOID* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��־��     2004.03.15  �°�����

  2.��    ��   : 2010��8��18��
    ��    ��   : ŷ����
    �޸�����   : DTS2010081702506,Normal LAU�ɹ���36����ַ�����������LAU
  3.��    ��   : 2010��9��8��
    ��    ��   : ��ë/00166186
    �޸�����   : DTS2010081902050
  4.��    ��   : 2010��9��30��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �������ⵥ��DTS2010092902368,TMSIֻ�ڵ�ЧPLMN����Ч
  5.��    ��   : 2010��11��28��
    ��    ��   : z00161729
    �޸�����  : DTS2010112604710:������LAU accpet��Ϣ�����LAI��Ϣ�ı��ҺϷ����������Ӧȫ�ֱ�����ֵ
  6.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  7.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  8.��    ��   : 2011��10��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 PHASEII EPLMN/RPLMN��MM/GMMά���޸�
  9.��    ��   : 2012��03��17��
    ��    ��   : s46746
    �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
 10.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
 11.��    ��   : 2012��3��6��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�
 12.��    ��   : 2012��3��27��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
 13.��    ��   : 2012��10��12��
    ��    ��   : s00217060
    �޸�����   : DTS2012082204735:LAU�����������б�ʱ,�ϴ�RAU�еĽ�����������Ȼ��Ч
 14.��    ��   : 2012��09��21��
    ��    ��   : z00161729
    �޸�����   : DTS2012090706407 :����lau accept��Я����ϵͳ��Ϣ�в�ͬ��non broadcast laiʱ��Ҫ����lau
 15.��    ��   : 2012��10��26��
    ��    ��   : W00176964
    �޸�����   : DTS2012090303157:����EPLMN��Ч���
 16.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
 17.��    ��   : 2013��4��22��
    ��    ��   : w00176964
    �޸�����   : DTS2013032507710:follow ON��Ǵ���ʱ����MM�ķ���״̬�ϱ�
 18.��    ��   : 2013��4��26��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
 19.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 20.��    ��   : 2013��07��5��
    ��    ��  : w00176964
    �޸�����  : DTS2013062503351:LAU�ɹ�ʱ���µ�ǰ��RAC��Ϣ
 21.��    ��   : 2014��2��18��
    ��    ��   : l00215384
    �޸�����   : DTS2014021006453��ע��ɹ����Ȩ�ܾ���������
 22.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai��CurLai�滻��MML�е�
 23.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID Mm_Cell_S23_E45(VOS_VOID* pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    MM_LAI_STRU                                             stCurLai;
    NAS_MML_LAI_STRU                                       *pstCurrCampLai = VOS_NULL_PTR;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT8                                               ucLacChangeFlg;
    NAS_MML_LAI_STRU                                       *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnAddr = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stTempEplmnAddr;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;
    NAS_MML_EMERGENCY_NUM_LIST_STRU                        *pstEmergencyNumList;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai();

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    pstCurrCampLai = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat(pstCurrCampLai, &stCurLai);
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    ucLacChangeFlg                              = VOS_FALSE;
    g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;


    PS_MEM_SET(&stTempEplmnAddr, 0x00, sizeof(stTempEplmnAddr));

    if (MM_TRUE == g_MmMsgLuAccpt.ucEmcFlg)
    {
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-26, begin */
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        pstEmergencyNumList->ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-26, end */
    }

    else if (0 != pstEmergencyNumList->ucEmergencyNumber)
    {
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        /* ��Ϣ�а������������б�֮ǰ�洢�˽������б�,�������ͬһ�����ҵ�mcc��ɾ��֮ǰ�洢�Ľ��������б�
        24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6��4.7.3.1.3��4.7.5.1.3��������:
        The emergency number(s) received in the Emergency Number List IE are valid only
        in networks with in.the same MCCcountry as in  the cell on which this IE
        is received.*/
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstEmergencyNumList->ulMcc, pstCurrCampLai->stPlmnId.ulMcc))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        {
            pstEmergencyNumList->ulMcc = 0xFFFFFFFF;

            for (i = 0; i < pstEmergencyNumList->ucEmergencyNumber; i++)
            {
                pstEmergencyNumList->aucEmergencyList[i].ucCategory = 0xFF;

                for (j = 0; j < NAS_MML_EMERGENCY_NUM_MAX_LEN; j++)
                {
                    pstEmergencyNumList->aucEmergencyList[i].aucEmcNum[j] = 0xFF;
                }
            }

            pstEmergencyNumList->ucEmergencyNumber = 0;
        }

        Mm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }
    else
    {
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    if (VOS_FALSE ==  MM_ComCmpLai(g_MmMsgLuAccpt.MmIeLAI.IeLai, stCurLai))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S23_E45:WARNING: LU ACCEPTED LAI ERROR!");
        ucLacChangeFlg = VOS_TRUE;
    }

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    g_MmGlobalInfo.ucRejectCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_T3210);

    /* ֹͣT3212��ʱ�������ظ�Ϊ���õ�Ĭ��ʱ�� */
    Mm_TimerStop(MM_TIMER_T3212);

    NAS_MM_SetNetworkT3212RandLen(MM_CONST_NUM_0);


    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
    pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;
    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                        /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E45:INFO: MmServiceState is MM_NORMAL_SERVICE");
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    /* ��¼ע��ɹ���RAC����������ģʽ�ı�,�Ƚ�RAI�Ƿ����ı� */
    g_MmGlobalInfo.MsCsInfo.ucOldRac
        = NAS_MML_GetCurrCampRac();

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    pstCsSuccLai->stPlmnId.ulMcc = pstCurrCampLai->stPlmnId.ulMcc;
    pstCsSuccLai->stPlmnId.ulMnc = pstCurrCampLai->stPlmnId.ulMnc;
    pstCsSuccLai->aucLac[0]      = pstCurrCampLai->aucLac[0];
    pstCsSuccLai->aucLac[1]      = pstCurrCampLai->aucLac[1];
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

    /* �����·���non broadcase lai��ϵͳ��Ϣ�Ĳ�ͬ�ҺϷ�����Ҫ����last success lai�������ͷź���Ҫ����lau */
    if ((VOS_TRUE == ucLacChangeFlg)
     && (MM_INVALID_LAI != g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac))
    {
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        pstCsSuccLai->stPlmnId.ulMcc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc                  = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMnc;
        pstCsSuccLai->aucLac[0]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac >> 8) & (0x00FF);
        pstCsSuccLai->aucLac[1]                       = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac) & (0x00FF);

        PS_MEM_CPY(pstCurrCampLai, pstCsSuccLai, sizeof(NAS_MML_LAI_STRU));
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        g_MmGlobalInfo.ucLauAcceptContainDiffNbLaiFlg = VOS_TRUE;
    }

    if (MM_TRUE == g_MmMsgLuAccpt.ucMobileIDFlg)
    {
        if (MM_MS_ID_IMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                         & MM_MS_ID_IMSI_PRESENT))
        {                                                                       /* �������IMSI                             */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* ����TMSI��Ч                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if (MM_MS_ID_TMSI_PRESENT ==
            (g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                            & MM_MS_ID_TMSI_PRESENT))
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |= MM_MS_ID_TMSI_PRESENT;/* ����TMSI��Ч                             */

            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            Mm_ComMsgTmsiRelocCpltSnd();                                        /* �����෢��TMSI REALLOCATION COMPLETE     */
        }
        else
        {
        }
    }

    NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);                  /* ���ø���״̬                             */
    Mm_ComNasInfoSav(
                     MM_STATUS_ATTACHED,
                     NAS_MML_GetSimCsSecurityCksn()
                     );                                                         /* ֪ͨRRC,MM��Attach״̬                   */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
    }


    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;



    /* LAU�ɹ�������EPLMN/RPLMN */

    /* �������·���EPLMN�б���ɾ����Ч ����ֹ�Ͳ��������ε����� */
    if ( MM_TRUE == g_MmMsgLuAccpt.ucPlmnListFlg )
    {
        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList((VOS_UINT32)g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                           (NAS_MML_PLMN_ID_STRU *)g_MmMsgLuAccpt.MmIePlmnList.aPlmnId);

        /* ����EPlmn��Ϣ�б�  */
        NAS_MM_GenerateEPlmnInfo(g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum,
                                 g_MmMsgLuAccpt.MmIePlmnList.aPlmnId,
                                 &stTempEplmnAddr);
    }
    else
    {
        stTempEplmnAddr.ucEquPlmnNum = 0x1;
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        stTempEplmnAddr.astEquPlmnAddr[0].ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stTempEplmnAddr.astEquPlmnAddr[0].ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    }

    pstEplmnAddr = NAS_MML_GetEquPlmnList();


    /* ��EPLMN���浽MMLȫ�ֱ��� */
    PS_MEM_CPY(pstEplmnAddr, &stTempEplmnAddr, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    /* ��EPLMN���µ�NV�� */
    NAS_MM_WriteEplmnNvim(pstEplmnAddr);


    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    if (VOS_TRUE == NAS_MM_IsGURplmnChanged(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType()))
    {
        /* ����RPlmn��Ϣ��ȫ�ֱ����� */
        NAS_MML_UpdateGURplmn(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType());

        NAS_MM_WriteRplmnWithRatNvim(NAS_MML_GetRplmnCfg());
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_SUCCESS,
                                NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                             NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_ACCEPT,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);                   /* ��¼���̺�ԭ��ֵ                         */

    if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
    {
        g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
    }


    g_MmSubLyrShare.MmShare.ucSpecProFlg = MM_UPDATED_SPECIFIC_PROCEDURE;

    if (MM_TRUE == g_MmMsgLuAccpt.ucFollowOFlg)
    {                                                                           /* �����Follow On����                      */
        Mm_ComFollowOnProc();                                                   /* ����Follow On�Ĺ�������                  */
    }
    else
    {
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E45:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ֹͣT3240                                */
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulDeactiveIsrFlg = NAS_MM_IsNeedDeactiveIsrAfterLau();
    if (VOS_TRUE == ulDeactiveIsrFlg)
    {
        /* ȥ����ISR,����TINֵΪP-TMSI */
        NAS_MM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-11, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-11, end */
}

/* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertMmLuTypeToStkLuType
 ��������  : ��������ת��:LAU_TYPE_ENUM_UINT8->NAS_STK_UPDATE_TYPE_ENUM_UINT8
 �������  : LAU_TYPE_ENUM_UINT8 enMmLuType MM���LAU TYPE
 �������  :
 �� �� ֵ  : PS_STK_UPDATE_TYPE_ENUM_UINT8 �ϱ���STK��LAU TYPE
 ���ú���  : NAS_MM_SndStkLauRej
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

*****************************************************************************/
NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_MM_ConvertMmLuTypeToStkLuType (LAU_TYPE_ENUM_UINT8 enMmLuType)
{
    switch (enMmLuType)
    {
        case MM_IE_LUT_NORMAL_LU:
             return NAS_STK_LUT_NORMAL_LU;

        case MM_IE_LUT_PERIODIC_UPDATING:
             return NAS_STK_LUT_PERIODIC_UPDATING;

        case MM_IE_LUT_IMSI_ATTACH:
             return NAS_STK_LUT_IMSI_ATTACH;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmLuTypeToStkLuType:WARNING: The input in invalid");
            return NAS_STK_UPDATE_TYPE_ENUM_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertMmRatTypeToStkRatType
 ��������  : ����RAT����ת��:NAS_MML_NET_RAT_TYPE_ENUM_UINT8->TAF_MMA_RAT_TYPE_ENUM_UINT8
 �������  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType MM���RAT TYPE
 �������  : ��
 �� �� ֵ  : TAF_PH_RAT_TYPE_ENUM_UINT8�ϱ���STK��RAT TYPE
 ���ú���  : NAS_MM_SndStkLauRej
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_MM_ConvertMmRatTypeToStkRatType (NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType)
{
    switch (enMmRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ConvertMmRatTypeToStkRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_SndStkLauRej
 ��������  : MM�ϱ�STK Network Rejection Event
 �������  : ucCause   �ܾ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  : Mm_Cell_S23_E46
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

*****************************************************************************/
VOS_VOID NAS_MM_SndStkLauRej(VOS_UINT8 ucCause)
{
    NAS_STK_NETWORK_REJECTION_EVENT_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAI_STRU                                       *pstLai = VOS_NULL_PTR;

    /* �����ڴ� */
    ulLength = sizeof(NAS_STK_NETWORK_REJECTION_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_NETWORK_REJECTION_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MM_ERR_LOG("NAS_MM_ReportStkLauRej: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stNetworkRejectionEvent), 0, sizeof(NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU));

    /* ��д����Ϣ���� */
    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstLai      =  NAS_MML_GetCurrCampLai();
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mcc = pstLai->stPlmnId.ulMcc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.stCurPlmnID.Mnc = pstLai->stPlmnId.ulMnc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stLacInfo.usLac           = (pstLai->aucLac[0] << 8) | (pstLai->aucLac[1]);

    pstMsg->stNetworkRejectionEvent.enRejType                             = NAS_STK_LAU_REJECT;

    pstMsg->stNetworkRejectionEvent.enRat                                 = NAS_MM_ConvertMmRatTypeToStkRatType(pstLai->enCampPlmnNetRat);

    pstMsg->stNetworkRejectionEvent.ucCauseCode                           = ucCause;

    pstMsg->stNetworkRejectionEvent.enUpdateAttachType                    = NAS_MM_ConvertMmLuTypeToStkLuType(NAS_MM_GetLuType());

    pstMsg->ulMsgName                                                     = ID_NAS_STK_NETWORK_REJECTION_EVENT;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstMsg))
    {
        MM_ERR_LOG("NAS_MM_SndStkLauRej: PS_SEND_MSG ERROR");
    }

    return;
}
/* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

/*******************************************************************************
  Module:   Mm_Cell_S23_E46
  Function: ��LOCATION UPDATING INITIATED״̬��,
            ���յ�RRMM_DATA_IND(LOCATION UPDATING REJECT)�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.15  �°�����
  2. ��    ��   : 2007��3��5��
     ��    ��   : liurui id:40632
     �޸�����   : �������ⵥ�ţ�A32D09094
  3. ��    ��   : 2008��7��11��
     ��    ��   : l0010747
     �޸�����   : ���ⵥ��:AT2D03814
  4. ��    ��   : 2008��8��13��
     ��    ��   : l0010747
     �޸�����   : ���ⵥ��:AT2D04996/AT2D05037
  5. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  6. ��    ��   : 2009��01��22��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�AT2D08462,MM֧����Э��汾REL-6��GSMģʽ��GCF����ΪREL-4����ԭ��ֵΪ95,96,97,99,111ʱ��GCF�����޷�ͨ��

  7.��    ��   : 2010��11��18��
    ��    ��   : zhoujun /40661
    �޸�����   : ���ⵥDTS2010111601893,�յ��ܾ�ԭ��ֵΪ102-110��
                 ����Ӧ�ú�ԭ��ֵ111�Ĵ���һ��
  8.��    ��   : 2011��01��14��
    ��    ��   : w00176964
    �޸�����   : ���ⵥDTS2011011301553,[V3R1B067][����ר��]UE����פ��W����Ϊ
                �ֶ�������G��LAU���ܣ�ԭ��ֵΪ11#,��Ϊ�Զ�������פ����ԭW��
                С������ʱΪ����LAU/RAU�����ܲ���paging
  9.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  10.��    ��   : 2011��7��25��
     ��    ��   : z00161729
     �޸�����   : V7R1 PhaseII�׶�ȫ�ֱ�������
  11.��    ��   : 2012��3��6��
     ��    ��   : z00161729
     �޸�����   : ֧��ISR�����޸�
  12.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  13.��    ��   : 2013��07��13��
     ��    ��   : l00208543
     �޸�����   : ����NAS_MM_ReportStkLauRej���ϱ�����STK�ϱ�reject��Ϣ
  14.��    ��   : 2014��5��21��
     ��    ��   : w00167002
     �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                MMɾ����SOR�����⴦��
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E46(VOS_VOID* pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulT3423StatusChgNeedRegFlg;
    VOS_UINT32                                              ulT3412StatusChgNeedRegFlg;
#endif

    g_MmGlobalInfo.ucRejectCause = g_MmMsgLuRjct.MmIeRejCause.ucRejCause;
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    Mm_TimerStop(MM_TIMER_T3210);                                               /* ֹͣT3210                                */
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */
    Mm_ComSaveProcAndCauseVal(MM_LU_PROC,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);           /* ��¼���̺�ԭ��ֵ                         */

    /* Added by l00208543 for V9R1 STK����, 2013-07-11, begin */
    NAS_MM_SndStkLauRej(g_MmMsgLuRjct.MmIeRejCause.ucRejCause);
    /* Added by l00208543 for V9R1 STK����, 2013-07-11, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LAU_REJECT,
                              g_MmMsgLuRjct.MmIeRejCause.ucRejCause);

    switch(g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        /* ����CS����Ч��һ��Ҫ���յ��ܾ�ԭ��ֵʱ����
           ��ΪGMM����GMM��Ϣʱ���жϴ˱�־ */
        NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
        break;
    default:
        if ((g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            <= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX)
         && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause
            >= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_TRUE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;
        }
#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
            /*
            Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS
            should set the attempt counter to 4.
            */
        if (   (NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == g_MmMsgLuRjct.MmIeRejCause.ucRejCause)
            || ( (g_MmMsgLuRjct.MmIeRejCause.ucRejCause > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
              && (g_MmMsgLuRjct.MmIeRejCause.ucRejCause <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) )
            )
        {
            /* now only WAS and WTTF support REL-6 */
            /* WCDMA/GSM���޸�Ϊ4��:
                3GPP 24008 4.4.4.9 Abnormal cases on the mobile station side:
                g)Location updating reject, other causes than those treated in subclause 4.4.4.7,
                and cases of MM cause values #22 and #25, if considered as abnormal cases according to subclause 4.4.4.7
                Upon reception of the cause codes #22, # 95, # 96, # 97, # 99 and # 111 the MS should set the attempt counter to 4.
            */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }
#endif

        /* ����Ҫ��������ʱ���Ѵ����޸�Ϊ4�� */
        if (VOS_FALSE == NAS_MM_IsLauRejNeedRetry(g_MmMsgLuRjct.MmIeRejCause.ucRejCause))
        {
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_4;
        }


        if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
        {                                                                       /* �ж�LU Counter�Ƿ�С��4                  */
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* �ж�LAI�Ƿ�δ�ı�,�Ҹ���״̬ΪU1         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_NORMAL_SERVICE");

            }
            else
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            }
        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */

            /* Steering of Roaming ���� */
            /* SOR ����: 4������ʧ��,���������������פ���ڱ��ܾ������磬�ն���Ҫ�ٳ���һ��ע�� */



            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E46:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        }
        break;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 3GPP 23401 4.3.5.6 Idle mode signalling reduction function����ȥ����ISR������
       After a LAU procedure if the UE has CS fallback and/or SMS over SGs activated.*/
    ulT3423StatusChgNeedRegFlg = NAS_MM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3423Status());

    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
    }

    ulT3412StatusChgNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                         NAS_MML_GetTinType(), NAS_MML_GetT3412Status());

    if (VOS_TRUE == ulT3412StatusChgNeedRegFlg)
    {
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif
    NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                g_MmGlobalInfo.usCauseVal);
    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             g_MmGlobalInfo.usCauseVal);
    Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E46:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
    Mm_TimerStart(MM_TIMER_T3240);                                              /* ֹͣT3240                                */
}

/*******************************************************************************
  Module:   Mm_Cell_S0_E2
  Function: ��MM VOS_NULL_PTR state״̬��,
            ���յ�MMCMM_ATTACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  x51137     2006.04.11  �°�����
      2.��    ��   : 2011��07��18��
        ��    ��   : w00166186
        �޸�����   : V7R1 PHASE II ATTACH/DETACH����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
    }

    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E2
  Function: ��MM IDLE NO CELL AVAILABLE״̬��,
            ���յ�MMCMM_ATTACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.20  �°�����
      2.��    ��   : 2011��07��18��
        ��    ��   : w00166186
        �޸�����   : V7R1 PHASE II ATTACH/DETACH����
      3.��    ��   : 2012��12��25��
        ��    ��   : l00167671
        �޸�����   : ���ⵥ��DTS2012122509118��L�������������ʱ��W���ѵ����ϴ�ע����ͬ��С��
                     �ȷ�����LU
      4.��    ��   : 2013��1��22��
        ��    ��   : W00176964
        �޸�����   : DTS2013012105162:MM��ĳЩ״̬����Ҫ�ϱ�����״̬��MMC
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucRet;

    ucRet = Mm_RcvMmcAttachReq( pMsg );
    if (MM_FALSE == ucRet)
    {
    }
    else
    {

        /*������״̬��Ҫֱ�ӻظ����*/
        if (( MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState )
            || ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
#if (!defined(__PS_WIN32_RECUR__)) && ( VOS_WIN32 != VOS_OS_VER )
            || ( MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState )
#endif
            )
        {
            /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
            if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                    & MM_WAIT_CS_ATTACH))
            {
                NAS_MM_SndMmcAttachCnf();
            }
            g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

            /* ɾ��ԭ���˴�����״̬�ϱ�*/
        }
        else
        {
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S4_E2
  Function: ��MM IDLE LIMITED SERVICE״̬��,
            ���յ�MMCMM_ATTACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.20  �°�����
  2.��    ��   : 2010��12��24��
    ��    ��   : ŷ����
    �޸�����   : ���ⵥDTS2010122402276������ģʽI���û���������ȥע�����
                 ����CSע�ᣬʧ��
  3.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2011��07��18��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����

  7.��    ��   : 2012��9��27��
    ��    ��   : z40661
    �޸�����   : DTS2012082705793,����ģʽI�£�PS��access barʱ,�û�����attach cs��δ����ע��
  8.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  9.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 10.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E2(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    MMCMM_ATTACH_REQ_STRU                      *pRcvMsg             = VOS_NULL_PTR;
    VOS_UINT8                                   ucPsAttachAllow;
    VOS_UINT8                                   ucSimPsRegStatus;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucPsRestrictRegisterFlg;

    ucPsAttachAllow  = NAS_MML_GetPsAttachAllowFlg();
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    ucPsRestrictRegisterFlg = NAS_MML_GetPsRestrictRegisterFlg();

    pRcvMsg = (MMCMM_ATTACH_REQ_STRU*)pMsg;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (VOS_TRUE == ucSimPsRegStatus)
         && (VOS_FALSE == ucPsRestrictRegisterFlg)
         && ((VOS_TRUE == ucPsAttachAllow)
          || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pRcvMsg->enAttachType)))
        {                                                                       /* ����ģʽI                                */
        }
        else
        {                                                                       /* ����ģʽII                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
                {
                    /*��ǰС����barʱ��ֱ�ӻظ�MMCMM_ATTACH_CNF,����ȴ�ATTACH�����־λ */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* ��MMC����MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);           /* ��MMC����MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);


                    return;
                }

                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* ���LAI����,����״̬ΪU1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        /* ��ǰ���update״̬��U1״̬��ֱ�ӻظ�MMCMM_ATTACH_CNF,����ȴ�ATTACH�����־λ */

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* ����LU����                               */

                        Mm_ComLuOnly();                                         /* ����LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */

                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
            }
        }

    }
}

/*******************************************************************************
  Module:   Mm_Cell_S19_E2
  Function: ��WAIT FOR ATTACH״̬��,
            ���յ�MMCMM_ATTACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.20  �°�����
  2.  s46746  2005.11.23  �޸�
  3.  s46746  2006-08-03  �������ⵥA32D03975�޸�
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��07��18��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  6.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  7.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  8.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S19_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucRet = Mm_RcvMmcAttachReq(pMsg);

    if (MM_FALSE == ucRet)
    {
    }
    else
    {
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
        {                                                                       /* ����ģʽI                                */
            ;
        }
        else
        {                                                                       /* ����ģʽII                               */
            if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* ���LAI����,����״̬ΪU1                 */
                    if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
                    {
                        Mm_ComNasInfoSav(
                                         MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn()
                                         );
                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S19_E2:INFO: MmServiceState is MM_NORMAL_SERVICE");
                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);                /* ��MMC����MMCMM_LU_RESULT_IND             */
                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S19_E2:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* ����LU����                               */
                        Mm_ComLuOnly();                                         /* ����LU REQ                               */
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E20
  Function: ��MM IDLE NO CELL AVAILABLE״̬��,
            ���յ�MMCMM_ MODE_CHANGE_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.20  �°�����
  2.��    ��   : 2014��05��22��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                    ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU  *pRcvMsg;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_FALSE == ucRet )
    {
    }
    else
    {
        pRcvMsg = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pRcvMsg->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        case NAS_MML_MS_MODE_NULL:
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S1_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

/*******************************************************************************
  Module:   Mm_Cell_S22_E1
  Function: ��WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��,
            ���յ�MMCMM_START_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.03.20  �°�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  6.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E1(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvMmcStartReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());
        Mm_ComInit();                                                           /* ȫ�ֱ�����ʼ��                           */
        Mm_ComStart();                                                          /* �����յ�MMCMM_START_REQ�Ĺ�������        */
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E2
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��,
            ���յ�MMCMM_ATTACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.20  �°�����
      2.  ��6746     2006.08.03  �������ⵥA32D03975�޸�
      3.��    ��   : 2011��07��18��
        ��    ��   : w00166186
        �޸�����   : V7R1 PHASE II ATTACH/DETACH����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E2(VOS_VOID* pMsg)
{
    VOS_UINT8                                               ucRet;

    ucRet = Mm_RcvMmcAttachReq(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
        if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                & MM_WAIT_CS_ATTACH))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E12
  Function: ��MM IDLE NORMAL SERVICE״̬��,
            ���յ�GMMMM_GPRS_DETACH_COMPLETED�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.20  �°�����
      2. ��    ��   : 2009��06��09��
         ��    ��   : l00130025
         �޸�����   : ���ⵥAT2D12278,NMO I��GPRS Detach��MSû�з���LAU��IMSI ATTACH����CS���к��б���,ԭ��ΪIMSI unkown in VLR
      3. ��    ��   : 2012��11��07��
         ��    ��   : l65478
         �޸�����   : DTS2012110503477,���ó�CS ONLY��MMû�з���LU
       4.��    ��   : 2013��2��4��
         ��    ��   : w00176964
         �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
       2.��    ��   : 2015��3��20��
         ��    ��   : w00167002
         �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                      ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽΪI,���û�ģʽΪA�ĳ���          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* ������Bģʽ�ĳ���                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E12:INFO: MmLikeB is MM_TRUE");

                if (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S4_E12
  Function: ��MM IDLE LIMITED SERVICE״̬��,
            ���յ�GMMMM_GPRS_DETACH_COMPLETED�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.20  �°�����

  1.��    ��   : 2012��9��7��
    ��    ��   : z40661
    �޸�����   : DTS2012081605654,����ģʽI�£�RAU��#9�ܾ���,MMδ����LAU

  2.��    ��   : 2012��12��7��
    ��    ��   : w00167002
    �޸�����   : DTS2012120608772:CS���绰ʱ���û�����PS detach��PS DETACH
                 �ɹ����û��޷��Ҷϵ绰�����ڴ�绰ʱ��MM����MM CONNECTION
                 ACTIVE״̬����ʱ�յ�PS detach����״̬Ǩ�Ƶ�IDLE NORMAL SERVICE�ˣ�
                 ���²�����CC��MM�������ͷ�������Ϣ�������쳣��
  3.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  4.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E12(VOS_VOID* pMsg)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    VOS_UINT32                          ulCurrMMState;

    ulCurrMMState  = Mm_GetState();

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽΪI,���û�ģʽΪA�ĳ���          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* ������Bģʽ�ĳ���                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����Ϊ����Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( (VOS_TRUE               == NAS_MM_IsCsEnableLau())
              && (MM_IDLE_LIMITED_SERVICE == ulCurrMMState) )
            {

                /* λ����û�иı�,����Ҫ���� */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}


/*****************************************************************************
 �� �� ��  : Mm_Cell_S17_E12
 ��������  : ��LOCATION UPDATING PENDING״̬��,
             ���յ�GMMMM_GPRS_DETACH_COMPLETED�Ĵ���
 �������  : VOS_VOID                           *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*****************************************************************************/
VOS_VOID Mm_Cell_S17_E12(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8   ucRet;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enUpdateStatus;

    enUpdateStatus = NAS_MML_GetCsUpdateStatus();

    ucRet = Mm_RcvGmmGprsDetechCmpl(pMsg);
    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ����ģʽΪI,���û�ģʽΪA�ĳ���          */
            if ((MM_TRUE == g_MmGlobalInfo.ucLikeB)
               || (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
            {                                                                   /* ������Bģʽ�ĳ���                        */
                ;
            }
            else
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����Ϊ����Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
            }


            if ( VOS_TRUE == NAS_MM_IsCsEnableLau() )
            {
                /* λ����û�иı�,����Ҫ���� */
                if ( (VOS_TRUE == NAS_MML_IsCsLaiChanged())
                  || (NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED == enUpdateStatus))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    Mm_ComLuOnly();
                }
                else
                {

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E12:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
            }

        }
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S0_E20
  Function: ��MM_NULL״̬��,
            ���յ�MMCMM_ MODE_CHANGE_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2004.03.20  �°�����
  2.x51137  2006/4/14 A32D02955
  3.��    ��   : 2008��8��21��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��05��22��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
         g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;

        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {                                                                       /* SIM���ڵĳ���                            */
            NAS_MML_SetSimCsRegStatus(VOS_TRUE);
        }
        else
        {                                                                       /* SIM�����ڵĳ���                          */
            NAS_MML_SetSimCsRegStatus(VOS_FALSE);
        }

        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ԭ״̬                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {                                                                   /* ���ڻ���ϵͳ��Ϣ�ĳ���                   */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM��Ч�ĳ���                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ԭ״̬                               */
            if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
            {
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {                                                               /* SIM��Ч�ĳ���                            */
                    Mm_ComSetMmState(MM_IDLE_NO_IMSI);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                }
                else
                {
                    Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);


                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
                }
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E20:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
            }
            break;
        default:
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E20
  Function: ��MM IDLE NORMAL SERVICE״̬��,
            ���յ�MMCMM_ MODE_CHANGE_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.20  �°�����
      2.  ��    ��   : 2009��01��20��
          ��    ��   : l00130025
          �޸�����   : ���ⵥ��:AT2D08378,��������ı�ʱ,MM/GMMû�ж�UE��mode���иı�;GMM��RAU�������յ�Detach����ʱ,ֱ�ӷ���,û�д���
      3.  ��    ��   : 2014��05��22��
          ��    ��   : w00176964
          �޸�����   : V3R3C60_eCall��Ŀ����
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if (MM_TRUE != ucRet)
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* ����ģʽΪI�ĳ���                        */
                if (MM_TIMER_STOP != gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                {
                    Mm_TimerStop(MM_TIMER_T3212);                               /* ͣT3212                                  */
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S3_E20
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��,
            ���յ�MMCMM_ MODE_CHANGE_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.20  �°�����
      2.  ��    ��   : 2009��01��20��
          ��    ��   : l00130025
          �޸�����   : ���ⵥ��:AT2D08378,��������ı�ʱ,MM/GMMû�ж�UE��mode���иı�;GMM��RAU�������յ�Detach����ʱ,ֱ�ӷ���,û�д���
      3.  ��    ��   : 2014��05��22��
          ��    ��   : w00176964
          �޸�����   : V3R3C60_eCall��Ŀ����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E20(VOS_VOID* pMsg)
{
    VOS_UINT8                        ucRet;
    MMCMM_MODE_CHANGE_REQ_STRU      *pModChgReq = VOS_NULL_PTR;

    ucRet = Mm_RcvMmcModeChngReq(pMsg);

    if ( MM_TRUE != ucRet )
    {
    }
    else
    {
        pModChgReq = (MMCMM_MODE_CHANGE_REQ_STRU*)pMsg;
        switch (pModChgReq->enMsMode)
        {
        case NAS_MML_MS_MODE_PS_CS:                                                     /* Aģʽ�ĳ���                              */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            if (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            {                                                                   /* ����ģʽΪI�ĳ���                        */
                if (MM_TRUE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E20:INFO: MmLikeB is MM_FALSE");
                }
            }
            break;
        case NAS_MML_MS_MODE_PS_ONLY:                                                    /* CGģʽ�ĳ���                             */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ecall onlyģʽ����ΪPS ONLY��Ӱ��CS��attach��� */
            if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
            {
                return;
            }
#endif
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-22, end */

            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        case NAS_MML_MS_MODE_CS_ONLY:                                                    /* CCģʽ�ĳ���                             */
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E20:WARNING: MsMode Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E27
  FUNCTION : ��wait for network command״̬���յ�MMCC_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-04-09    �°�����
     2.  s46746     05-11-24    �޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E27(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;

    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if (MM_FALSE == Mm_RcvCcDataReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((pMmCcDataReq->ulTransactionId <= 15)
            && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
        {                                                                       /* TIO ����111������CS����������            */
            Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                            &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);                          /* ��CC����Ϣ������ȥ                       */
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E50
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-04-09    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E50(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                       /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = (RRMM_DATA_IND_STRU *) pRcvMsg;            /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop(MM_TIMER_T3212);                                               /* ͣT3212                                  */

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(VOS_MEMPOOL_INDEX_MM,
                            pRrDataInd->RcvNasMsg.ulNasMsgSize,
                            WUEPS_MEM_NO_WAIT);                                 /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S14_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
               sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);         /* ��ʼ���ڴ�                               */

    PS_MEM_CPY (pucCMMsg,
                &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
                pRrDataInd->RcvNasMsg.ulNasMsgSize);                            /* �õ���Ϣ����                             */
    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                            /* �õ�CC��Ϣ�е�TI                         */
    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI))
        && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* ��CC����MMCC_EST_IND                     */
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S22_E5
  Function: ��WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��,
            �յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.    ��־��     2004.04.13  �°�����
  2.  ��־��        2005.01.27  007037 for MM
  3.��    ��   : 2006��10��6��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D05960
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��03��17��
    ��    ��   : s46746
    �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
  6.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2013��12��5��
    ��    ��   : w00167002
    �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                  PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                  �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                  �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ���
  8.��    ��   : 2014��04��1��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E5(VOS_VOID* pMsg)
{

    VOS_UINT8  ucTiValidFlg = MM_TRUE;

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if (MM_FALSE == ucTiValidFlg)
            {
                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                   /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
             Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                      /* RR���Ӳ�����                             */
             NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S23_E5
  Function: ��LOCATION UPDATING INITIATED״̬��, �յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.04.13  �°�����
  2.��    ��   : 2006��10��6��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D05960
  3.��    ��   : 2008��7��11��
    ��    ��   : l0010747
    �޸�����   : ���ⵥ��:AT2D03814
  4.��    ��   : 2008��09��03��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  5.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2012��03��17��
    ��    ��   : s46746
    �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2014��04��1��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E5(VOS_VOID* pMsg)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    if ((MMCMM_NO_FORBIDDEN !=
         g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
        && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* ͣT3210                                  */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */
        if (MMCMM_FORBIDDEN_PLMN ==
            (MMCMM_FORBIDDEN_PLMN &
                g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN); /* ��¼���̺�ԭ��ֵ                         */
        }
        else if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
            == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                & g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            )
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS);   /* ��¼���̺�ԭ��ֵ                         */
        }
        else
        {
            Mm_ComSaveProcAndCauseVal(MM_LU_PROC, NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM); /* ��¼���̺�ԭ��ֵ                         */
        }
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(LOCATION_UPDATE_REJECTED);

        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

        NAS_MM_UpdateEquPlmnInfo(g_MmGlobalInfo.usCauseVal);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    g_MmGlobalInfo.usCauseVal);
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 g_MmGlobalInfo.usCauseVal);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E5:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ����TIMER3240                            */
    }
    else
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;
    }
}

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

/*******************************************************************************
  Module:   Mm_Cell_S23_E22
  Function: ��LOCATION UPDATING INITIATED״̬��,
            �յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��    2005.01.31  �°�����
  2.��    ��   : 2008��7��21��
    ��    ��   : luojian 00107747
    �޸�����   : ���ⵥ�ţ�AT2D04201/AT2D04536
  3.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����

  3.��    ��   : 2013��6��5��
    ��    ��   : w00167002
    �޸�����   : �����ǰRR���Ӵ��ڣ���ֱ���ڵ�ǰ��RR��·�Ϸ���CS���ȥע�᣻
                 �������½���RR���ӣ�
                 �ڼ�Ȩ�����У��������Ȩ��־��Ϣ��
  4.��    ��   : 2013��6��24��
    ��    ��   : w00167002
    �޸�����   : ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF
  5.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  6.��    ��   : 2015��6��3��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S23_E22(VOS_VOID* pMsg)
{
    MM_MSG_IMSI_DETACH_IND_STRU         stMsg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }


    /* ��LAUʱ�������ǰ���������ѽ������ˣ���ֱ�ӷ���DETACH REQ������ */
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        /* 24008_CR1201R1_(Rel-8)_C1-082683 24008 4.3.4�½�����:If a RR connection
           exists and the ATT flag indicates that no detach procedure is required,
           the MM sublayer will release locally any ongoing MM connections before
           releasing the RR connection. If a MM specific procedure is active,
           the release of the RR connection may be delayed until the MM specific
           procedure is complete.*/
        if (MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
        {
            return;
        }

        /* �ڼ�Ȩ�����У��������Ȩ��־��Ϣ */
        if ( MM_RCV_AUTH_CNF_FLG == (g_MmGlobalInfo.ucRcvAgentFlg & MM_RCV_AUTH_CNF_FLG) )
        {
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

            /* ֹͣ������ʱ�� */
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        }


        /* ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF */
        g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

        /* ���CS���������Ӵ���                     */
        /* ֹͣLAU�ı�����ʱ��T3210 */
        Mm_TimerStop(MM_TIMER_T3210);
        NAS_MM_FillMobileID(&(stMsg.MmIeMobileId.MobileID));

        Mm_ComSetMmState(IMSI_DETACH_INITIATED);
        Mm_ComMsgImsiDetachIniSndOfDataReq(&stMsg);                             /* ��д��Ϣ,������Ϣ                        */
        Mm_TimerStart(MM_TIMER_T3220);                                          /* ����T3220                                */
    }

    /* �����ǰ������δ�����ã�����յ�EST_CNF�����DETACH�Ĵ���  */

    return;

}
/*******************************************************************************
  Module:   Mm_Cell_S24_E22
  Function: ��LOCATION UPDATE REJECTED״̬��,
            �յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��    2005.01.31  �°�����
  2. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  3.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2013��6��8��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:���ע�������¿���Ч���򷵻�
                 ��������޸�:ɾ���Ƿ���GMM�����û�detachͳһ����
  7.��    ��   : 2013��6��24��
    ��    ��   : w00167002
    �޸�����   : ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF
  8.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S24_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;



    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ֹͣT3212                                */

        /* ���ע�������¿���Ч���򷵻�  */
        if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
        {
            NAS_MM_LocalDetach();
            return;
        }

        if ((MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg)
            || (MM_STATUS_ATTACHED !=
                            g_MmSubLyrShare.MmShare.ucCsAttachState))
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            Mm_ComSaveProcAndCauseVal(MM_IMSI_DETACH, NAS_MML_REG_FAIL_CAUSE_NULL);       /* ��¼���̺�ԭ��ֵ                         */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����T3240                                */
        }
        else
        {
            NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));


            /* ����DETACH���ͣ��������յ�RELʱ�򣬲��ظ�MMC��DETACH CNF */
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_NORMAL;

            Mm_ComSetMmState(IMSI_DETACH_INITIATED);
            Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                           /* ��д��Ϣ,������Ϣ                        */
            Mm_TimerStart(MM_TIMER_T3220);                                      /* ����T3220                                */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E22:NORMAL: STATUS is IMSI_DETACH_INITIATED");
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S6_E53
  Function: ��MM IDLE LOCATION UPDATE NEEDED״̬��,���յ�T3212����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.08  �°�����
      2.��    ��   : 2015��1��5��
        ��    ��   : z00161729
        �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E53(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3212);                                               /* ֹͣT3212                                */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
        return;
    }

    if (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E14
  Function: ��MM NULL״̬��,���յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.08  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E14(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E13
  Function: ��MM NULL״̬��,���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.08  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E13(VOS_VOID* pMsg)
{
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

}
/*******************************************************************************
  Module:   Mm_Cell_S4_E13
  Function: ��MM IDLE LIMITED SERVICE״̬���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2005.01.13  003018 for MM
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

  3.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd = VOS_NULL_PTR;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }
    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ���ΪA+Iģʽ                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* ���ΪA+Iģʽ                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* ����������Bģʽ                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E13:INFO: MmLikeB is MM_TRUE");
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );
            Mm_ComDelLai();
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S5_E13
  Function: ��MM IDLE ATTEMPT TO UPDATE״̬���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.13  003018 for MM
      2. ��    ��   : 2008��8��23��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�

      3. ��    ��   : 2013��2��4��
         ��    ��   : w00176964
         �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
       4.��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
      5.��    ��   : 2015��3��20��
        ��    ��   : w00167002
        �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                     ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    VOS_UINT8                           ucOldUpdateSts;
    VOS_UINT8                           ucTempUpdateSts;

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
        {                                                                       /* ���ΪA+Iģʽ                            */
            if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
            {
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ����������Bģʽ                          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
    }
    else
    {
        switch(pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
            {                                                                   /* ���ΪA+Iģʽ                            */
                if (MM_FALSE == g_MmGlobalInfo.ucLikeB)
                {
                    g_MmGlobalInfo.ucLikeB = MM_TRUE;                           /* ����������Bģʽ                          */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmLikeB is MM_TRUE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E13:INFO: MmServiceState is MM_LIMITED_SERVICE");
            ucOldUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED);          /* ���ø���״̬                             */
            ucTempUpdateSts = NAS_MML_GetCsUpdateStatus();
            NAS_MML_SetCsUpdateStatus(ucOldUpdateSts);
            NAS_MML_SetCsUpdateStatus(ucTempUpdateSts);
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            break;
        default:
            break;
        }
    }
}

/* add by ��־��    2005-1-31 for MM 003018 end */
/*******************************************************************************
  Module:   Mm_Cell_S6_E24
  Function: ��MM IDLE LOCATION UPDATE NEEDED״̬��,���յ�MMCC_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.19  �°�����
      2.  s46746  2005-11-15  �޸�
      3.  ��    ��   : 2011��10��27��
          ��    ��   : s46746
          �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
      4.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
      5.��    ��   : 2012��8��13��
        ��    ��   : z00161729
        �޸�����   : DCM������������������޸�,֧��L���������޸�
      6.��    ��   : 2012��9��25��
        ��    ��   : z00161729
        �޸�����   : DTS2012071907985:cs��bar��mm�յ�cc�Ľ�������Ӧ�ظ�rel ind�����ǵ�t303��ʱ
      7.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      8.��    ��   : 2012��12��11��
        ��    ��   : w00176964
        �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
      9.��    ��   : 2012��12��21��
        ��    ��   : L00171473
        �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
      10.��    ��   :2013��9��12��
         ��    ��   :z00161729
         �޸�����   :DTS2013082903019:֧��ss�ط�����
      11.��    ��   : 2014��8��4��
         ��    ��   : w00167002
         �޸�����   : DTS2014080407625:��L��ע��ɹ���ACCESS BAR,MM״̬Ǩ�Ƶ�LOCATION
                      UPDATE NEEDED,��ʱ�û�����绰ʧ�ܡ�
      12.��    ��   :2014��9��24��
         ��    ��   :s00217060
         �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID    Mm_Cell_S6_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* NAS�޸Ĳ����ص绰 */


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
#endif

        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ�� */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }

        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S6_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
            
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */
            
                return;
            }

            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* �ǽ�������                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* ��¼�յ���������ʱ��״̬                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
                {
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;

                    /* TI�Ϸ�  */
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                    {
                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                  /* ֪ͨCC����ʧ��                           */
                    }
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

                    /* GU��location update needed״̬�յ�cc��est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
                    /* MM��unbar to bar����LMM��access bar��ʱ��Ż�Ǩ��location update needed״̬ */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S6_E62
  Function: ��MM IDLE LOCATION UPDATE NEEDED״̬��,���յ�MMSMS_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.19  �°�����
      2.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
      3.��    ��   : 2012��12��11��
        ��    ��   : w00176964
        �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
      4.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����  :DTS2013082903019:֧��ss�ط�����
      5.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID    Mm_Cell_S6_E62( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);            /* ֪ͨSMS����ʧ��                           */
            return;
        }

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat
                = NAS_MML_GetCurrNetRatType();

            /* ���CM SERVICE REQUEST�ṹ�� */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &stCmSvcReq);

            /* ���CM SERVICE REQUEST ��Ϣ */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );
            }

            /* ��¼���ڽ�����MM���ӵ�TI��PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = (VOS_UINT8)g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;

            /* ����������ʱ�� */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* ֪ͨMMC/GMM��CS���ҵ���Ѿ����� */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* ��¼״̬ */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");

            /* ����ҵ����ڱ�־ */
            NAS_MM_UpdateCsServiceBufferStatusFlg();
            NAS_MM_UpdateCsServiceConnStatusFlg();
        }
        else
        {
            /* GU��location update needed״̬�յ�sms��est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM��access bar����LMM��access bar��ʱ��Ż�Ǩ��location update needed״̬ */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                                /* ֪ͨSMS����ʧ��                           */
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S6_E65
  Function: ��MM IDLE LOCATION UPDATE NEEDED״̬��,���յ�MMSS_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.19  �°�����
      2. ��    ��   : 2007��07��31��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ��:A32D12640
      3. ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
      4. ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
      5.��    ��   : 2012��12��11��
        ��    ��   : w00176964
        �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
      6.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����  :DTS2013082903019:֧��ss�ط�����
      7.��    ��   : 2014��8��4��
        ��    ��   : w00167002
        �޸�����   : DTS2014080407625:��L��ע��ɹ���ACCESS BAR,MM״̬Ǩ�Ƶ�LOCATION
                      UPDATE NEEDED,��ʱ�û�����绰ʧ�ܡ� NAS�޸Ĳ������Ρ�
      8.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID    Mm_Cell_S6_E65( VOS_VOID* pMsg)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;
    VOS_UINT16                          usMsgSize = 0;
    VOS_UINT8                          *pucCmSvcReq = 0;

    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰפ��LTE,��ֱ�ӷ��� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

           /* ������������ */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            /* ���CM SERVICE REQUEST�ṹ�� */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);

            /* ���CM SERVICE REQUEST ��Ϣ */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );
            if (VOS_NULL_PTR == pucCmSvcReq)
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S6_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;
            }
            else
            {
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);
            }

            /* ��¼���ڽ�����MM���ӵ�TI��PD */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = (VOS_UINT8)g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;

            /* ����������ʱ�� */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

            /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

            /* ��¼״̬ */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }
        else
        {
            /* ==>A32D12640 */
            /* GU��location update needed״̬�յ�ss��est_req,NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR */
            /* MM��access bar����LMM��access bar��ʱ��Ż�Ǩ��location update needed״̬ */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S5_E24
  Function: ��MM IDLE ATTEMPTING TO UPDATE״̬��,���յ�MMCC_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.19  �°�����
      2.  ��    ��   : 2011��10��27��
          ��    ��   : s46746
          �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
      3. ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
      4. ��    ��   : 2012��8��14��
         ��    ��   : z00161729
         �޸�����   : DCM������������������޸�,֧��L���������޸�
      5.��    ��   : 2012��9��25��
        ��    ��   : z00161729
        �޸�����   : DTS2012071907985:cs��bar��mm�յ�cc�Ľ�������Ӧ�ظ�rel ind�����ǵ�t303��ʱ
      6.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      7.��    ��   : 2012��12��11��
        ��    ��   : w00176964
        �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
      8.��    ��   : 2012��12��21��
        ��    ��   : L00171473
        �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
      9.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      10.��    ��   :2013��9��12��
         ��    ��   :z00161729
         �޸�����   :DTS2013082903019:֧��ss�ط�����

      11.��    ��   : 2014��8��11��
         ��    ��   : w00167002
         �޸�����   : DTS2014080407625:��ATTEMPT TO UPDATE״̬Ҳ���Է�����ͨ���С�
      12.��    ��   :2014��9��24��
         ��    ��   :s00217060
         �޸�����   :for cs_err_log
      13.��    ��   : 2015��1��5��
         ��    ��   : z00161729
         �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID    Mm_Cell_S5_E24( VOS_VOID* pMsg)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)


        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            /* �����ǰפ��LTE,��Ҳ���Է�����ͨ���� */

            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
#endif

        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ�� */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq =
            g_MmGlobalInfo.ucState;                                             /* ��¼�յ���������ʱ��״̬                 */

        /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S5_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
            
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */
            
                return;
            }
        
            if ( MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType )
            {                                                                   /* �ǽ�������                               */
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                /* ���ǽ�������                             */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* �Ѿ�����һ��������MM���ӽ�������         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* ֪ͨCC����ʧ��                           */

                    return;
                }

                if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
                {
                    /* �������ز���ԭ��ֵ */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
                    return;
                }

                /* ������Ϣ */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
                if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
                {
                    NAS_MM_SndGmmRegisterInit();                                    /* ֪ͨGMM����ע��                          */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
            }
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E22
  Function: ��MM NULL״̬��,�յ�MMCMM_DETACH_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.05.28  �°�����
  2.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  5.��    ��   : 2013��6��13��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:��NULL״̬�²�Ǩ�Ƶ�LIMIT SERVICE״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E22(VOS_VOID* pMsg)
{
    MMCMM_DETACH_REQ_STRU*   pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pMsg) )
    {
        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S0_E22:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        switch ( pMmcDetachReq->enDetachType )
        {
        case MMC_MM_CS_DETACH:
        case MMC_MM_PS_CS_DETACH:
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MM_DETACHED);

                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }

            if ( MM_STATE_NULL != Mm_GetState() )
            {
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            }

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S0_E22:WARNING: Detach Cause Abnormal");
            break;
        }
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E59
  Function: ��MM NULL״̬��,�յ�T3230����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.28  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E59(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3230);                                               /* ֹͣTIMER3230                            */
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E60
  Function: ��MM NULL״̬��,�յ�T3240����Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E60(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_T3240);                                               /* ֹͣTIMER3230                            */
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E36
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�AUTHENTICATION REQUEST�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
      2.��    ��   : 2013��7��23��
        ��    ��   : w00167002
        �޸�����   : DTS2013072205858:2g rf 13.2���������쳣��
                      �յ�Ѱ��ʱ�����಻�·�SETUP,���Եײ�����ָ�ꡣ
                      T3240��ʱ���ͷ��˵�ǰ���ӣ�������������ʧ�ܡ�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E36(VOS_VOID* pMsg)
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComAuthenRcvAuthenReq();
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E37
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�AUTHENTICATION REJECT�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2004.05.31  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E37(VOS_VOID* pMsg)
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣT3240                                  */

    Mm_TimerStart( MM_TIMER_T3240 );                                            /* ����T3240                                */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5�½���������:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);


    Mm_ComAuthenRcvAuthenRej();                                                 /* �յ�AUTHEN REJ�Ĵ���                     */

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E38
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�IDENTITY REQUEST�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
      2.��    ��   : 2013��7��23��
        ��    ��   : w00167002
        �޸�����   : DTS2013072205858:2g rf 13.2���������쳣��
                  �յ�Ѱ��ʱ�����಻�·�SETUP,���Եײ�����ָ�ꡣ
                  T3240��ʱ���ͷ��˵�ǰ���ӣ�������������ʧ�ܡ�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E38(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComIdentity();                                                           /* IDENTITY���̵Ĵ���                       */

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E39
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�TMSI REALLOCATION COMMAND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
      2.��    ��   : 2013��7��23��
        ��    ��   : w00167002
        �޸�����   : DTS2013072205858:2g rf 13.2���������쳣��
                  �յ�Ѱ��ʱ�����಻�·�SETUP,���Եײ�����ָ�ꡣ
                  T3240��ʱ���ͷ��˵�ǰ���ӣ�������������ʧ�ܡ�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E39(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComTmsiReloc();
    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E43
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�MM INFORMATION�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
      2.��    ��   : 2013��7��23��
        ��    ��   : w00167002
        �޸�����   : DTS2013072205858:2g rf 13.2���������쳣��
                      �յ�Ѱ��ʱ�����಻�·�SETUP,���Եײ�����ָ�ꡣ
                    T3240��ʱ���ͷ��˵�ǰ���ӣ�������������ʧ�ܡ�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E43(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    Mm_ComInfo();                                                               /* MM INFO���̵Ĵ���                        */
    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E44
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�MM STATUS�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
      2.��    ��   : 2013��7��23��
        ��    ��   : w00167002
        �޸�����   : DTS2013072205858:2g rf 13.2���������쳣��
                      �յ�Ѱ��ʱ�����಻�·�SETUP,���Եײ�����ָ�ꡣ
                    T3240��ʱ���ͷ��˵�ǰ���ӣ�������������ʧ�ܡ�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E44(VOS_VOID* pMsg)
{
    Mm_TimerStop( MM_TIMER_T3212 );                                             /* ͣT3212                                  */


    /* WaitForNetworkCommand״̬����T3240 */
    NAS_MM_RestartT3240_WaitForNetworkCommand();

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E47
  Function: ��WAIT FOR NETWORK COMMAND״̬��,�յ�CM SERVICE PROMPT�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.05.31  �°�����
      2.  ��־��     2005.01.27  007037 for MM
      3.  ��    ��   : 2012��8��10��
          ��    ��   : L00171473
          �޸�����   : DTS2012082204471, TQE����
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E47(VOS_VOID* pMsg)
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));


    MM_Fill_IE_ClassMark2(aucClassmark2);

    if (MM_STATUS_DETACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        return;
    }
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */

    if ( MM_CONST_NUM_0 == ( aucClassmark2[3] & 0x04 ) )
    {                                                                           /* ��֧��CCBS                               */
        MsgMmStatus.MmIeRjctCause.ucRejCause =
            NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;                            /* Msg type non-existent or not implemented */
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                   /* ��䲢���� MM STATUS ��Ϣ                */
    }
    else
    {                                                                           /* ֧��CCBS                                 */
        Mm_SndCcPromptInd();                                                    /* ��CC����MMCC_PROMPT_IND                  */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(PROCESS_CM_SERVICE_PROMPT);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E62
  Function: ��MM IDLE ATTEMPTING TO UPDATE״̬��,�յ�MMSMS_EST_REQ�Ĵ���
            �յ�MMSMS_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.06.08  �°�����
      2.  ��    ��   : 2011��10��27��
          ��    ��   : s46746
          �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
        3.��    ��   : 2012��2��15��
          ��    ��   : w00166186
          �޸�����   : CSFB&PPAC&ETWS&ISR ����
        4.��    ��   : 2012��12��11��
          ��    ��   : w00176964
          �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
        5.��    ��   : 2013��2��4��
          ��    ��   : w00176964
          �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
        6.��    ��   :2013��9��12��
          ��    ��   :z00161729
          �޸�����   :DTS2013082903019:֧��ss�ط�����
        7.��    ��   :2014��9��24��
          ��    ��   :s00217060
          �޸�����   :for cs_err_log
        8.��    ��   : 2015��1��5��
          ��    ��   : z00161729
          �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID    Mm_Cell_S5_E62( VOS_VOID*pMsg )
{


    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);/* ֪ͨSMS����ʧ��                          */
            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰפ��LTE,��ֱ�ӻظ�SMSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* ֪ͨSMS����ʧ��                          */

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI���Ϸ�                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            /* �������ز���ԭ��ֵ */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* ֪ͨGMM����ע��                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }


    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E65
  Function: ��MM IDLE ATTEMPTING TO UPDATE״̬��,�յ�MMSS_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.06.08  �°�����
      2.  ��    ��   : 2011��10��27��
          ��    ��   : s46746
          �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
      3. ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
       4.��    ��   : 2012��12��11��
         ��    ��   : w00176964
         �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
       5.��    ��   : 2013��2��4��
         ��    ��   : w00176964
         �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
       6.��    ��   :2013��9��12��
         ��    ��   :z00161729
         �޸�����  :DTS2013082903019:֧��ss�ط�����
       7.��    ��   : 2014��8��11��
         ��    ��   : w00167002
         �޸�����   : DTS2014080407625:��ATTEMPT TO UPDATE״̬Ҳ���Է�����ͨ���С�
       8.��    ��   :2014��9��24��
         ��    ��   :s00217060
         �޸�����   :for cs_err_log
       9.��    ��   : 2015��1��5��
         ��    ��   : z00161729
         �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID    Mm_Cell_S5_E65( VOS_VOID*pMsg )
{
    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* ��ATTEMPT TO UPDATE״̬���Է��𲹳�ҵ�� */
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi ) )
        {                                                                       /* TI���Ϸ�                                 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

            return;
        }
        if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;
        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        {
            NAS_MM_SndGmmRegisterInit();                                        /* ֪ͨGMM����ע��                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                                 /* LU REQ                                   */
        }
    }

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S22_E24
  Function: ��WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬��,�յ�MMCC_EST_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.06.08  �°�����
      2.  ��    ��   : 2011��10��27��
          ��    ��   : s46746
          �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
      3. ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
      4. ��    ��   : 2012��6��9��
         ��    ��   : z00161729
         �޸�����   : DTS2012060705413:V7R1C50 GUL�������޸ģ�L���յ�ϵͳ��ϢmmǨ��location update pending״̬
                      δ����cc��������
      5.��    ��   : 2012��8��14��
        ��    ��   : z00161729
        �޸�����   : DCM������������������޸�,���������޸�
      6.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      7.��    ��   : 2012��12��11��
        ��    ��   : w00176964
        �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
      8.��    ��   : 2012��12��21��
        ��    ��   : L00171473
        �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
      9.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
      10.��    ��   : 2015��5��6��
         ��    ��   : z00161729
         �޸�����   : 24301 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID    Mm_Cell_S22_E24( VOS_VOID*pMsg )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState)
            {
                /* �쳣����:LTE�²���Ǩ�Ƶ��⼸��״̬ */
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);                              /* ֪ͨCC����ʧ��                           */

                return;
            }

            /* �����ǰפ��LTE,MM LOCATION_UPDATING_PENDING״̬�յ��������л���ͨ������Ҫ��LMM
               ����ID_MM_LMM_CSFB_SERVICE_START_NOTIFY��tauע�ᱻ��#17 1�Σ�mm��Ǩ��location update pending */
            NAS_MM_RcvCcEstReq_CSFB();
            return;


            /* DTS2012060705413�����ǰפ��LTE,MM LOCATION_UPDATING_PENDING״̬�յ���ͨ������Ҫ���棬
               ������LMM����ID_MM_LMM_CSFB_SERVICE_START_NOTIFY*/
        }
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
#endif
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);                              /* ֪ͨCC����ʧ��                           */

            return;
        }


        if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                || ( MM_TRUE ==
               g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg )
                )
            {
                /* �Ѿ�����һ��������MM���ӽ�������         */
                Mm_SndCcRelInd(
                    g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                        /* ֪ͨCC����ʧ��                           */
            }
            else
            {
                if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
                {
                    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S22_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
                
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */
                
                    return;
                }

                /* ������Ϣ */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E40
  FUNCTION : ��WAIT FOR NETWORK COMMAND ״̬���յ�
                RRMM_DATA_IND(CM SERVICE ACCEPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E40(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */


    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* ��䲢���� MM STATUS ��Ϣ                */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S1_E24
  FUNCTION : ��MM IDLE NO CELL AVAILABLE״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.15 �¹�����
     4.  ��־��        2005.01.27  007037 for MM
     5.  ��    ��   : 2011��10��27��
         ��    ��   : s46746
         �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     6.  ��    ��   : 2012��8��13��
         ��    ��   : z00161729
         �޸�����   : DCM������������������޸�,֧��L�½�������
     7.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     8 .��    ��   : 2012��12��21��
        ��    ��   : L00171473
        �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
     9.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
    10.��    ��   : 2014��12��29��
       ��    ��   : z00161729
       �޸�����   : DSDSҵ���ز�ʱno rfδ������������ҵ��ʧ�ܣ�
                    mm��no cell available״̬no rfʱ��mmc����cm service ind��������
    11.��    ��   : 2015��8��3��
       ��    ��   : n00269697
       �޸�����   : DTS2015072802941�������ǰפ��LTE����ͨ���и���������һ����
                    ����CSFB
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E24(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {


            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
#endif

        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
        /* ��ǰno rfʱ�յ�ҵ������mm��Ҫ֪ͨmmc�ȴ�����������ͨ������Ҫ����Ч������ҵ������ */
        if (VOS_TRUE == NAS_MM_IsCcServiceNeedTriggerPlmnSearch())
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */
        {
            /*����÷������� */
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        if ( MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);        /* ֪ͨCC����ʧ��                           */
        }
        else
        {
            if ( MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState )
            {
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* �Ѿ�����һ��������MM���ӽ�������         */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );                     /* ֪ͨCC����ʧ��                           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                }

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;                                     /* ��¼�յ���������ʱ��״̬                 */
                if ( (MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
                    ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
                {
                    /* TI���Ϸ�                                 */
                    Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                      /* ֪ͨCC����ʧ��                           */
                }
                else
                {
                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                }
            }
            else
            {
                Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                     /* ֪ͨCC����ʧ��                           */
            }
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E71
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�TCMM_TEST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E71(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    TCMM_TEST_REQ_STRU           *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_ACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerPause(MM_TIMER_STOP_ALL);                                       /* ��ͣ����Timer                            */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ԭ״̬Ǩ��                               */
        Mm_ComSetMmState(TEST_CONTROL_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  TEST_CONTROL_ACTIVE\r " );                      */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E71:NORMAL: STATUS is TEST_CONTROL_ACTIVE");
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E72
  FUNCTION : ��TEST_CONTROL_ACTIVE״̬���յ�TCMM_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E72(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    TCMM_DATA_REQ_STRU          *pTcmmDataReq;

    pTcmmDataReq = ( TCMM_DATA_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "SendTcMsg = %d \r",pTcmmDataReq->SendTcMsg.ulTcMsgSize); */

    Mm_SndRrDataReq(
                pTcmmDataReq->SendTcMsg.ulTcMsgSize,
                &pTcmmDataReq->SendTcMsg.aucTcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��TC����Ϣ������ȥ                       */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E73
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�RRMM_DATA_IND(TC MSG)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����

  1.��    ��   : 2012��9��21��
    ��    ��   : z40661
    �޸�����   : DTS2012092702799 ֧��AGPSʱ���ϱ�TC��Ϣ����TCģ����EST_REQ���󣬵���T3240��ʱ��δֹͣ
                 ��ʱ�������ͷ�
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E73(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    RRMM_DATA_IND_STRU          *pRrmmDataInd;

    pRrmmDataInd = ( RRMM_DATA_IND_STRU* )pRcvMsg;


    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */

    Mm_SndTcDataInd(
                pRrmmDataInd->RcvNasMsg.ulNasMsgSize,
                pRrmmDataInd->RcvNasMsg.aucNasMsg);
}

/*******************************************************************************
  MODULE   : Mm_Cell_S31_E71
  FUNCTION : ��TEST_CONTROL_ACTIVE״̬���յ�TCMM_TEST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����
     2.  ��    ��   : 2008��09��03��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05487,mmע��״̬�޸�
       3.��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
       4.��    ��   : 2013��9��12��
         ��    ��   : w00242748
         �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                      ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                      G��ԭС��ʱ��LAU
       5.��    ��   : 2015��3��20��
         ��    ��   : w00167002
         �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                      ���з�װ��
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E71(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    TCMM_TEST_REQ_STRU          *pTcmmTestReq;

    pTcmmTestReq = ( TCMM_TEST_REQ_STRU* )pRcvMsg;

    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "ulMode = %d \r",pTcmmTestReq->ulMode);       */

    if ( TC_RB_TEST_DEACTIVE == pTcmmTestReq->ulMode )
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
        }
        else
        {
            switch ( g_MmGlobalInfo.ucMmServiceState )
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_NORMAL_SERVICE\r " );           */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  MM_IDLE_LIMITED_SERVICE\r " );          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");


                if (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }

                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;
            case MM_DETACHED:
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                /*WUEPS_TRACE(MM_LOG_LEVEL_1,                                   */
                /*    "\nMM:ucState = %d\r", g_MmGlobalInfo.ucState);           */
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E71:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S31_E71:WARNING: g_MmGlobalInfo.ucMmServiceState Abnormal");
                break;
            }
        }
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S31_E33
  FUNCTION : ��TEST_CONTROL_ACTIVE״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2004.06.18 �¹�����
     2.  ��    ��   : 2008��12��26��
         ��    ��   : o00132663
         �޸�����   : ���ⵥAT2D07880,���ز���ʱ��T3240û�м�ʱֹͣ��
     3.  ��    ��   : 2011��10��11��
         ��    ��   : l00171473
         �޸�����   : V7R1 phase II, TC���ص���
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E33(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣ��ͷ��ַ                         */
)
{
    /*WUEPS_TRACE(MM_LOG_LEVEL_4, "RRMM_REL_IND = %d \r",RRMM_REL_IND);         */

    Mm_TimerStop( MM_TIMER_T3240 );

    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_ABSENT;
    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                             /* RR���Ӳ�����                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

    /* TC״̬���յ�����������ͷ���Ϣʱ����TC����TCMM_RR_REL_IND */
    NAS_MM_SndTcRrRelInd();
}


/*******************************************************************************
  MODULE   : Mm_Cell_S0_E21
  FUNCTION : ��NULL״̬���յ�MMCMM_COVERAGE_LOST_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.01.06 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E21(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                        /* �����쳣����                             */
    }

}


/*******************************************************************************
  MODULE   : Mm_Cell_S3_E34
  FUNCTION : ��MM IDLE NORMAL SERVICE״̬���յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.01.06 �¹�����
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E34(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* �����쳣����                             */
    }

}



/*******************************************************************************
  MODULE   : Mm_Cell_S25_E24
  FUNCTION : ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.27  006045 for MM
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E24(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */                                                        /* �����쳣����                             */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        Mm_SndCcRelInd(
                        g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH );                 /* ֪ͨCC����ʧ��                           */
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S22_E13
  FUNCTION : ��WAIT FOR RR CONNECTION (LOCATION UPDATING)״̬���յ�
                GMMMM_NETWORK_DETACH_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��    2005.01.27 �¹�����
  2.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E13(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT( 0 ); */

        return;
    }

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* ��¼��ǰ������                           */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                              */
    /*    " \nMM:MmServiceState is MM_NET_DETACH_PROC \r " );                   */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* Mm_SndRrRelReq(); */                                                 /* ��RRC����RRMM_REL_REQ(CS��)              */
        /* Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);  */                         /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* ���÷���״̬                             */
        /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                          */
        /*    " \nMM:MmServiceState is MM_ATTEMPTING_TO_UPDATE \r " );          */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        Mm_ComToU2Handle();                                                     /* ����MM��U2�Ĵ���                         */
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);


    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* ��RRC����RRMM_REL_REQ(CS��)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* ����DETACH���̵�ԭ��ֵ����               */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S22_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                  /* ��RRC����RRMM_REL_REQ(CS��)              */
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);
            /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause); */ /* ����DETACH���̵�ԭ��ֵ����               */
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
                Mm_ComNetDetachCauseHandle(
                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);                              /* ��RRC����RRMM_REL_REQ(CS��)              */
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pstNetWkDetachInd->ulDetachCause);
                /* Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd
                ->ulDetachCause); */                                            /* ����DETACH���̵�ԭ��ֵ����               */
            }
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S23_E13
  FUNCTION : ��LOCATION UPDATING INITIATED״̬���յ�
                GMMMM_NETWORK_DETACH_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��  2005.01.27 �¹�����
     2.  ��    ��   : 2008��09��03��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
     3.  ��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     4.  ��    ��   : 2014��4��2��
         ��    ��   : w00176964
         �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
     5.  ��    ��   : 2015��3��20��
         ��    ��   : w00167002
         �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                      ���з�װ��
*******************************************************************************/

VOS_VOID Mm_Cell_S23_E13(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */

        return;
    }

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pRcvMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3210);                                           /* ֹͣT3210                                */
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ����TIMER3240                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* ֹͣT3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6,                                      */
            /*    " \nMM:MmServiceState is MM_NO_IMSI \r " );                   */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MmLikeB is MM_TRUE \r " );    */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S23_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_TimerStop(MM_TIMER_T3210);                                       /* ֹͣT3210                                */
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E13:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E16
  FUNCTION : ��NULL״̬���յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  ��־��   2005.01.27 �¹�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E16(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )

{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* �����쳣����                             */
        return;
    }

    NAS_MML_SetSimCsRegStatus(VOS_FALSE);


    Mm_ComDelLai();                                                            /* ɾ��LAI     */
    NAS_MML_InitUeIdTmsiInvalid();
    NAS_MML_SetSimCsSecurityCksn(NAS_MML_CKSN_INVALID);


}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E33
  FUNCTION : ��NULL״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.10  003020 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E33(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */

        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    return;
}

/*****************************************************************************
 �� �� ��  :  Mm_Cell_S2_E33
 ��������  : ��MM IDLE PLMN SEARCH״̬��
             �յ�RRMM_REL_IND�Ĵ���,���������ΪAS�쳣,�ͷŵ����е�MM����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2007��9��29��
   ��    ��   : luojian id:107747
   �޸�����   : �����ɺ���,�������ⵥ�� A32D12966
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2012��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2012021405430:W��ע��PS����15��CSע��δ��ɱ������ͷ�RRC���ӣ�
                ������W��ע��ɹ����쳣�����LAC��Ϣ���������յ��µ�ϵͳ��Ϣ��
                ��������LAU
 4.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 5.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 6.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
 7.��    ��   : 2016��2��19��
   ��    ��   : z00359541
   �޸�����   : DTS2016020301907:���ݲ�ͬMM��״̬���ж�֪ͨCM RELԭ��ֵ������Ӱ���ز�
*****************************************************************************/
VOS_VOID Mm_Cell_S2_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enRelCause;

    ucValidFlg                          = Mm_RcvRrcRelInd(pRcvMsg);
    enRelCause                          = NAS_MM_GetMmCmRelCause();

    if ( MM_TRUE == ucValidFlg )
    {
        Mm_TimerStop(MM_TIMER_WAIT_CONNECT_REL);

        /* ֪ͨMMC���Ӳ����� */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);        
        
        /* �ͷ�����MM����,���ڽ���MM���� */
        /* imsi detach pending״̬�յ�rel ind��
           �ײ����쳣��CS��Ӧ��δע��ɹ����ͷ����е�MM���ӣ����ز� */
        NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_Cell_S2_E33: MM Substate ", g_MmGlobalInfo.ucState);
        Mm_ComRelAllMmConn(enRelCause);


        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S2_E33:WARNING: ulRelCause Abnormal");
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S26_E37
  Function: ��IMSI DETACH INITIATED״̬��,
                            �յ�RRMM_DATA_IND(AUTHENTICATION REJECT)�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2005.01.27  003025 for MM
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S26_E37(VOS_VOID* pMsg)
{
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_ComToNoImsiHandle();
    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5�½���������:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_MM_SndGmmAuthFailInd();
    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);


    /* �ж�DETACH�ȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

}

/*******************************************************************************
  MODULE   : Mm_Cell_S17_E22
  FUNCTION : ��LOCATION UPDATING PENDING״̬���յ�MMCMM_DETACH_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  ��־��   2005.01.07 �¹�����
  2.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2012��01��12��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2012010602762:SYSCFG���ó�֧��CS ONLY��
                 PS��Ȼ��ʾ��������
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E22(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )

{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if ( MM_FALSE == Mm_RcvMmcDetachReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0);  */                                                      /* �����쳣����                             */

        return;
    }

    pMmcDetachReq = ( MMCMM_DETACH_REQ_STRU* )pRcvMsg;

    if ( MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType )
    {
        /* ������RAU�����У��յ�DETACH_REQ ��Ϣ��GMM���ᷢ�� DETACH���̣�MM��Ҫ���ñ�־λ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_CS_DETACH;
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S17_E23
  FUNCTION : ��LOCATION UPDATING PENDING״̬���յ�MMCMM_POWER_OFF_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   2005.01.07 �¹�����

  1.��    ��   : 2012��8��24��
    ��    ��   : z40661
    �޸�����   : DTS2012081702937
    2.��    ��   : 2012��9��07��
      ��    ��   : l00171473
      �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
    3.��    ��   : 2013��05��15��
      ��    ��   : s46746
      �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    4.��    ��   : 2014��04��03��
      ��    ��   : w00176964
      �޸�����   : V3R3C60_eCall��Ŀ����
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E23(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )

{
    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                       /* �����쳣����                             */

        return;
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-7, begin */
#if (FEATURE_ON == FEATURE_LTE)

    /* �����ǰפ��LTE,��ֱ�ӻظ��ػ� */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */
        Mm_ComSetMmState(MM_NULL);

        return;
    }
#endif

    if (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
        Mm_ComSetMmState(MM_NULL);
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
    }
    else
    {

        Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-7, end */


    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S25_E76
  FUNCTION : ��WAIT FOR RR CONNECTION (IMSI DETACH)״̬��MM_TIMER_PROTECT_DETACH���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  ��־��        2005.01.27  007037 for MM
  2.  ��    ��   : 2007��3��20��
      ��    ��   : s46746
      �޸�����   : ���ⵥ�ţ�A32D09497
  3. ��    ��   : 2007��06��01��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥA32D10964�޸�
  4.��    ��   : 2008��7��21��
    ��    ��   : luojian 00107747
    �޸�����   : ���ⵥ�ţ�AT2D04201/AT2D04536
  5.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  6.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2015��7��22��
    ��    ��   : z00161729
    �޸�����   : DTS2015060807763:apͨ��cgcatt�·�imsi detach������ʧ�ܺ�mm
                ����detach���ظ�detach cnfʱӦ�ô�limit service������normal service��
                at����ظ�ok������error
*******************************************************************************/
VOS_VOID Mm_Cell_S25_E76(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /*A32D10964==>*/
    MM_MSG_IMSI_DETACH_IND_STRU     Msg;
    if ((MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
      && (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg))
    {
        NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));
        Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);
    }
    /*<==A32D10964*/
    switch(g_MmGlobalInfo.ucDetachType)
    {
        case MM_DETACH_CS_POWEROFF:
        /*A32D10964==>*/
        case MM_DETACH_NEED_DELAY:
        /*<==A32D10964*/
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());                     /* ����MM��Ϣ                               */

            Mm_SndMmcPowerOffCnf();                                                     /* ��MMC����MMCMM_POWER_OFF_CNF             */

            Mm_ComSetMmState(MM_STATE_NULL);
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is  MM_STATE_NULL");
            Mm_TimerStop(MM_TIMER_STOP_ALL);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
            }

            break;
        case MM_DETACH_CS_NORMAL:
            /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
            if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                         & MM_WAIT_CS_DETACH))
            {
                NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

                /* ����ȴ���־ */
                g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
            }
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E76:NORMAL: STATUS is",g_MmGlobalInfo.ucState);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S25_E76:WARNING: Detach type is unexpect.");
            break;

    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E75
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��MM_TIMER_PROTECT_AGENT���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E75(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /* WUEPS_ASSERT(0); */
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E77
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��MM_TIMER_PROTECT_SIGNALLING���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.27  007037 for MM
     2.  s46746     2006.01.21  �������ⵥA32D01682�޸�

  2.��    ��   : 2012��3��2��
    ��    ��   : z40661
    �޸�����   : DTS2012021703361���ȴ�GAS��WAS������ʱ����ʱ��Ĵ���
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E77(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /* WUEPS_ASSERT(0); */
    VOS_UINT8 ucCause;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E77:WARNING: Wait for RRMM_EST_CNF expired");

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_RR_CONN_EST_FAIL;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;              /* ��¼Ǩ��֮ǰ��״̬                       */


    if (NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
    {
        /* CC�����RR���ӵĽ���                     */
        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI,
            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* ֪ͨCC����ʧ��                           */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {                                                                   /* SS�����RR���ӵĽ���                     */
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else if (NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {                                                                   /* SMS�����RR���ӵĽ���                    */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);          /* ֪ͨSMS,MM���ӽ���ʧ��                   */

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
            NO_MM_CONN_ESTING;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else
    {                                                                   /* û�����ڽ�����MM���ӣ�������             */

#if (FEATURE_ON == FEATURE_PTM)
        /* �յ�CS PAGING�����ӽ�����ʱ���쳣��¼ */
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_TIMEOUT);
#endif

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
    Mm_TimerStart(MM_TIMER_T3240);
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E77:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    /* ��Ҫ����LU�����ͷŻ����ҵ�� */
    if (MM_TRUE == Mm_ComChkLu())
    {
        if (MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* ֪ͨCC����ʧ��                           */
        }

        if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }

    }


}

/*******************************************************************************
  MODULE   : Mm_Cell_S22_E77
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��MM_TIMER_PROTECT_SIGNALLING���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
*******************************************************************************/
VOS_VOID Mm_Cell_S22_E77(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    Mm_RcvRrmmEstCnf();
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E77
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��MM_TIMER_PROTECT_SIGNALLING���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746     2006.04.17  Create

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬

     3.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     4.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     5.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E77(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8 i;
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E77:WARNING: MM_TIMER_PROTECT_SIGNALLING expire at WAIT FOR REESTABLISH(WAIT FOR EST_CNF).");


    /*lint -e701*/
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                   /* �ؽ���MM����                             */
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);       /* ֪ͨCC,MM�����ؽ�ʧ��                    */
        }
        if ( MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcRelInd( ( i + 8 ),NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);/* ֪ͨCC,MM�����ؽ�ʧ��                    */

        }
    }

    /*lint +e701*/

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E77:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    if ( MM_FALSE == Mm_ComChkLu() )
    {

        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        else
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                            RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);                          /* ֪ͨCC����ʧ��                           */
        }

        if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                        RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                               /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT);

        }

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();


}


/*******************************************************************************
  MODULE   : Mm_Cell_S6_E74
  FUNCTION : ��MM IDLE LOCATION UPDATE NEEDED״̬���յ�RRMM_AC_INFORMATION_CHANGE_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��       2005.01.10  004005 for MM
     2.  ��    ��   : 2008��09��03��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
     3.  ��    ��   : 2010��12��05��
         ��    ��   : o00132663
         �޸�����   : ���ⵥ�ţ�DTS2010120400767,W�£�CS��bar��PS UNBAR,����ģʽII��PDP�������Ӻ�
                      �û��ֶ���CS��Ϊ��bar,MMδ����LAU��
       4.��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
       5.��    ��   : 2012��12��11��
         ��    ��   : w00176964
         �޸�����   : ����С����ֹ����ҵ����
       6.��    ��   : 2013��2��4��
         ��    ��   : w00176964
         �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
       7.��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
       8.��    ��   : 2015��3��20��
         ��    ��   : w00167002
         �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                      ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E74(VOS_VOID *pRcvMsg)
{
    RRMM_AC_INFO_CHANGE_IND_STRU               *pRrMmAcInfoChgInd;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    pRrMmAcInfoChgInd = (RRMM_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvRrcAcInfoChgInd(pRcvMsg) )
    {
        return;
    }
    if (( RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
     || ( RRC_NAS_T3122_EXPIRE == pRrMmAcInfoChgInd->ulAcChangeInd) )
    {
        if (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd)
        {
            NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
            NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
            /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
            NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
            /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        }

        if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
         && (VOS_FALSE == ucPsRestrictionFlg))
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);

            NAS_MM_SndGmmRegisterInit();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E74:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if (( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* ���LAI����,����״̬ΪU1                 */
                if ( MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* ����LU����                               */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            }

            if ((g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt < MM_CONST_NUM_4)
             || (RRC_NAS_AC_NOT_BAR == pRrMmAcInfoChgInd->ulAcChangeInd))
            {
                Mm_ComLuOnly();                                                 /* ����LU REQ                               */
            }

            if (g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt >= MM_CONST_NUM_4)
            {
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S0_E24
  FUNCTION : ��NULL״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.08  001030 for MM
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvCcEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */                                                     /* �����쳣����                             */
        return;
    }
    else
    {
        /* ��Ϣ������ɹ�                         */
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);                      /* ֪ͨCC����ʧ��                           */
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E40
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.11  Status for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E40(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU    Msg;

    Msg.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;

    Mm_ComMsgMmStatusSnd(&Msg);
}

/*******************************************************************************
  Module:   Mm_Cell_S31_E1
  Function: ��TEST_CONTROL_ACTIVE״̬��,�յ�MMCMM_START_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2005.01.27  �°�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2012��8��29��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, TC״̬����ʱ������REL_REQ
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E1(VOS_VOID* pMsg)
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {


        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* ȫ�ֱ�����ʼ��                           */
        Mm_ComStart();                                                          /* �����յ�MMCMM_START_REQ�Ĺ�������        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_Cell_S0_E78
  Function: ��MM NULL״̬��,�յ�MM_AGENT_INQUIRE�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.01.28  �°�����
      2. ��    ��   : 2007��01��26��
         ��    ��   : h44270
         �޸�����   : ���ⵥ�ţ�A32D08575,������������ʾ����,������Ҫ�޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S0_E78(VOS_VOID* pMsg)
{
#if 0
    PS_OM_MSG_HEAD_STRU *pNewMsg;
    pNewMsg = (PS_OM_MSG_HEAD_STRU *)pMsg;

    switch (pNewMsg->ulMsgID)
    {
        case AGENT_MM_INQUIRE:
            Mm_RcvMmAgentInquire(pMsg);
            break;
        case MM_TRANS_STATUS_INFO_REQ:
            Mm_SndAgentTransInfo(pNewMsg);
            break;
        default:
            break;
    }
#endif
}
/*******************************************************************************
  Module:   Mm_Cell_S31_E23
  Function: ��TEST_CONTROL_ACTIVE״̬��,�յ�MMCMM_POWER_OFF_REQ�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2005.01.28  �¹�����
  2. ��    ��   : 2007��3��20��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�A32D09497
  3. ��    ��   : 2007��08��19��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D12706
  4. ��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2012��3��15��
    ��    ��   : w00166186
    �޸�����   : V7R1 C50 CSFB&PPAC&ETWS&ISR����
  7.��    ��   : 2012��9��07��
    ��    ��   : l00171473
    �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
  8.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 11.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 12.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : DSDS ������
 13.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_Cell_S31_E23(VOS_VOID* pMsg)
{

    MM_MSG_IMSI_DETACH_IND_STRU     Msg;

    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg) )
    {
        return;
    }


    /* TC״̬���յ��ػ�����ʱ����������REL_REQ */
    if ( g_MmGlobalInfo.ucCsSigConnFlg == MM_CS_SIG_CONN_PRESENT )
    {
        NAS_MM_SndTcRrRelInd();

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    }


    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {                                                                           /* ���ΪA+Iģʽ                            */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (MM_FALSE == g_MmGlobalInfo.ucLikeB)
         && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
        {

            Mm_TimerStart(MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                /* ����DETACH����                           */
            return;                                                             /* ��������B����A+IIģʽ�ĳ���              */
        }
    }
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;                        /* ����DETACH����                           */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
    {
        if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                /* ==>A32D12706 */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);
                Mm_ComSetMmState(IMSI_DETACH_INITIATED);
                /* <==A32D12706 */
            }
            else
            {
                MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
                Mm_SndMmcPowerOffCnf();
                Mm_ComSetMmState(MM_STATE_NULL);

            }
            g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                    /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
            Mm_ComNasInfoSav(
                             MM_STATUS_DETACHED,
                             NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
        }
        else
        {
            if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                Mm_ComSetMmState(IMSI_DETACH_INITIATED);

                Mm_ComMsgImsiDetachIniSndOfDataReq(&Msg);                       /* ��д��Ϣ,������Ϣ                        */
                Mm_TimerStart(MM_TIMER_T3220);                                  /* ����������ʱ��                           */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is IMSI_DETACH_INITIATED");
            }
            else
            {
                NAS_MM_FillMobileID(&(Msg.MmIeMobileId.MobileID));

                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
                Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_IMSI_DETACH);

                Mm_ComMsgImsiDetachIniSndOfEstReq(&Msg);                        /* ��д��Ϣ,������Ϣ                        */
                Mm_TimerStart(MM_TIMER_PROTECT_DETACH);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");
            }

        }
    }
    else
    {
        if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
        {
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;                        /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S31_E23:INFO: MmServiceState is MM_NO_SERVICE");
        Mm_ComNasInfoSav(
                         MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
        }

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S31_E23:NORMAL: STATUS is MM_STATE_NULL");
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E79
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��MM_TIMER_PROTECT_CC���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.28  �¹�����
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E79(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

}

/*******************************************************************************
  MODULE   : Mm_Cell_S13_E79
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR REEST REQ)״̬��MM_TIMER_PROTECT_CC���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746        2006.04.17  Create
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E79(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8 ucTiValidFlg;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S13_E79:WARNING: MM_TIMER_PROTECT_CC expire at WAIT FOR REESTABLISH(WAIT FOR REEST REQ).");

    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E79:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_ComProcCauseProcess();

    if ( MM_FALSE == Mm_ComChkLu() )
    {
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                      .RcvXXEstReq.ucFlg)
            ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                      .RcvXXEstReq.ucFlg))
        {
            ucTiValidFlg = Mm_ComTiChk();
            if ( MM_FALSE == ucTiValidFlg )
            {
                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );     /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
            else
            {
                Mm_ComSigRelForDelayMmConnRej();
            }
        }
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);                      /* ֪ͨCC����ʧ��                           */
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndSmsRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                .RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
        if ( MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg )
        {                                                           /* �еȴ���CC��������Ҫ������MM����         */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
        }
    }

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT);
}


/*******************************************************************************
  MODULE   : Mm_Cell_S9_E15
  FUNCTION : ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬��GMMMM_LU_INITIATION���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��        2005.01.28  �¹�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E15(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if ( MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */                                                      /* �쳣������                             */
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E5
  Function: ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬��,
            ���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2005.02.01  �°�����
      2.  ��    ��   : 2006��10��6��
          ��    ��   : s46746
          �޸�����   : ���ⵥ�ţ�A32D05960
      3.  ��    ��   : 2009��05��25��
          ��    ��   : l65478
          �޸�����   : ���ⵥ:AT2D10870,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
      4.  ��    ��   : 2009��8��25��
          ��    ��   : ŷ���� 00132663
          �޸�����   : AT2D14050,��NAS R6Э���������ԡ�פ����ϵͳ��Ϣ�ı䣬ָʾDSAC PS��BAR��
                       ������ͨ�绰,ͨ���ڼ�T3312��ʱ���ͷź����˴����������LAU��
      5.  ��    ��   : 2010��10��11��
          ��    ��   : w00166186
          �޸�����   : DTS2010093000095,ͨ������LAI�ı䣬ͨ���������һ��LAU����ʧ�ܡ�
      6.  ��    ��   : 2010��11��22��
          ��    ��   : h44270
          �޸�����   : DTS201011700067,û�д���ϵͳ��Ϣ�����µ绰�ҶϺ�û�з���LAU��
      7.  ��    ��   : 2013��2��4��
          ��    ��   : w00176964
          �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      8.  ��    ��   : 2014��04��1��
          ��    ��   : w00176964
          �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E5(VOS_VOID* pMsg)
{
    MMCMM_SYS_INFO_IND_STRU            *pstSysInfoMsg;

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

    /* G���ڸ�״̬�յ�ϵͳ��Ϣ��Ԥ�����������ֻ����W���յ�����Ϣ */
    pstSysInfoMsg   = (MMCMM_SYS_INFO_IND_STRU*)pMsg;

    /* �����ǰCSע���Ϊ���ޣ���Ҫ�������ý���ǰ״̬ */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* �����ǰCSע���Ϊ�����ޣ���Ҫ�������ý���ǰ״̬ */
    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
    /* MM����ͨ���У�PS��bar���ڼ�T3312��ʱ��GMM��֪ͨMM����ʱMM�ὫT3212��ʱ��־
       ��λTRUE,�˺����PS�ִ�barתΪ��bar, MM��Ҫ��T3212��ʱ��־�������
       ���򣬵�ͨ������ʱ��Mm_ComChkLu���� ��⵽�ñ�־λ�󣬻ᷢ��������LU���̡� */
    if (  (VOS_TRUE == pstSysInfoMsg->ucPsChanged2UnBarFlg)
        &&(MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
    {
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

    if (VOS_TRUE == pstSysInfoMsg->ucCsChanged2UnBarFlg)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E5
  Function: ��WAIT_FOR_RR_CONNECTION_MM_CONNECTION״̬��,
            ���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.z40661     2009.07.23  �°�����
  2.��    ��   : 2009��08��07��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ:AT2D13560,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
  3.��    ��   : 2010��05��14��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:AT2D19292,MM��Ѱ����������ʱ���յ�ϵͳ��Ϣ����״̬Ǩ��NORMAL״̬������GCFʧ��
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��05��13��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ�ţ�DTS201104300028����������������������ͷŽ�������MM�쳣������T3212
  6.��    ��   : 2011��03��18��
    ��    ��   : c00173809
    �޸�����   : ���ⵥ�ţ�DTSs2011031600590������H3G�ź�����,���������ʲ��ɹ�
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  8.��    ��   : 2012��10��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
  9.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 10.��    ��   : 2013��7��21��
    ��    ��   : w00242748
    �޸�����   : DTS2013071802235:���Ź����У���ϵͳ�л���G��λ�����仯������LAU�����·��Ͳ�������
 11.��    ��   : 2013��08��15��
    ��    ��   : l65478
    �޸�����   : DTS2013081404782MMҵ�������û��֪ͨGMM CSҵ�����
 12.��    ��   : 2013��09��03��
    ��    ��   : l65478
    �޸�����   : DTS2013041602825:CSFB���ӽ���ʧ�ܺ�û�з���LU
 13.��    ��   :2013��9��23��
    ��    ��   :w00242748
    �޸�����   :DTS2013091407626:W��UE���У�δ�յ����ཨ��CNFǰ�������ض���G��δ����LAU
 14.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
 15.��    ��   : 2013��12��5��
    ��    ��   : w00167002
    �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                  PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                  �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                  �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ��¡�

                  ɾ������Mm_ComIsLaiForbidden�����÷�װ����NAS_MM_ProcNoGprsForbidenFlg_RcvSysInfoInd
 16.��    ��   : 2014��04��1��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
 17.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
 18.��    ��   :2015��5��21��
    ��    ��   :b00269685
    �޸�����   :��LAI�仯����һ��paging
*******************************************************************************/

VOS_VOID Mm_Cell_S12_E5(VOS_VOID* pMsg)
{
    VOS_UINT8                           ucLaiChange;
    VOS_UINT32                          ulCsServExist;

    VOS_UINT32                          ulCsfbEmgCallLaiChgLauFirstFlg;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */
    ucLaiChange    = NAS_MML_IsCsLaiChanged();
    ulCsServExist  = Mm_ComJudgeCsServExist();
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    /* �����ǰCSע���Ϊ���ޣ���Ҫ�������ý���ǰ״̬ */
    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* �����ǰCSע���Ϊ�����ޣ���Ҫ�������ý���ǰ״̬ */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == NAS_MML_GetCsRegisterBarToUnBarFlg())
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    /* פ���������磬�ҵ�ǰ�޽����������� */
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {

        g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

        /* ����פ��������������������������ڽ��������н���פ��������С����״̬δˢ�£�����T3212���쳣
           ֹͣ�����ҽ���������������ϱ���������״̬ */
        if ( (MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
          && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg) )
        {
            if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
            {
                g_MmGlobalInfo.ucMmServiceState   = MM_LIMITED_SERVICE;
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = MM_IDLE_LIMITED_SERVICE;
            }

            return;
        }

        ulCsfbEmgCallLaiChgLauFirstFlg = NAS_MML_GetCsfbEmgCallLaiChgLauFirstFlg();

        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange)
         && (VOS_TRUE == ulCsfbEmgCallLaiChgLauFirstFlg))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
        }

        return;
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, begin */
    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, end */
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }
    else
    {
        /* ����ϵͳ�л�������ҵ���������з���λ�����ı� */
        if ((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
         && (VOS_TRUE == ucLaiChange))
        {
            g_MmGlobalInfo.ucPendingLu  = VOS_TRUE;
            g_MmGlobalInfo.ucConnRcvSysFlg = MM_TRUE;

            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

            /* �ͷ����ӣ��������ͷź����Ƚ���LU/RAU��Ȼ��������������Ϣ */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
            return;
        }

        /* ���cs update״̬��U0,LAIδ�����仯���ϱ�ע����
           ��Ӧ����: LAU������(LOCATION UPDATING INITIATED״̬)�յ�ҵ�����󣬻���
           δ�յ�LAU accept��ֱ��rel ind��MMǨ��idle normal service״̬���������ҵ������
           ҵ����������(WAIT FOR RR CONNECTION (MM CONNECTION)״̬)�յ�ϵͳ��Ϣ������ע��ɹ�
           �����ڵ绰�����У��������ʾ�޷�������Ʒ��� */
        if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
         && (VOS_FALSE == ucLaiChange)
         && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
        {
            /* ��MMC����MMCMM_LU_RESULT_IND */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL);

            /* ��GMM����MMGMM_LU_RESULT_IND */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL);
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E50
  FUNCTION : ��MM_CONNECTION_ACTIVE״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      2005.02.02  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E50(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   ucTI = 0;                                                           /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S10_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }

    /*lint -e701*/
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
        sizeof( VOS_UINT8 ) * pRrDataInd->RcvNasMsg.ulNasMsgSize );                 /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�CC��Ϣ�е�TI                         */
    if ( ( MM_CONST_NUM_7 == ucTI ) || ( MM_CONST_NUM_15 == ucTI ) )
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* ��CC����MMCC_EST_IND                     */
    }
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��CC����MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��CC����MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC������MM����                           */
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��CC����MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��CC����MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
    }
    else
    {

    }


    /*lint +e701*/

    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* �ͷ��������Ϣ                           */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E80
  FUNCTION : ��MM IDLE ATTEMPTING TO UPDATE,WAIT FOR NETWORK COMMAND״̬���յ�
             MMSS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
       1.��    ��   : 2007��3��9��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥA32D09099����
       2.��    ��   : 2012��2��29��
         ��    ��   : w00167002
         �޸�����   : V7R1C50 ֧��CSFB�����޸�:
                      ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־
       3.��    ��   : 2014��6��13��
         ��    ��   : w00242748
         �޸�����   : DSDS ������
       4.��    ��   : 2014��9��23��
         ��    ��   : z00161729
         �޸�����   : DTS2014092302846:L�²���绰������w�±�#12�ܾ���С�����绰ʧ�ܺ���ѡ��l��mm���cc�෢һ��mmcc rel ind
       5.��    ��   : 2016��2��2��
         ��    ��   : z00359541
         �޸�����   : DTS2016011809099:����Ҫ����CSFB ABORT��Ϣ���״̬����CSFB�������յ�SS STARTUS NOTIFY��Ϣʱ����
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            if (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* ֪ͨL CSFB ������ֹ */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }

            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S32_E80
 ��������  : ��MM_INTER_RAT_CHANGE״̬�յ�ss abort req��Ϣ����
 �������  : pRcvMsg - �յ���ԭ��ͷָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��22��
    ��    ��   : z00161729
    �޸�����   : DTS2014050601476:L��绰�ض���g�����е绰�Ҷϣ�mm����cc abort��g��ѯcsfb״̬�Ǵ��ڣ�lau������û����������FR���̵�L
  2.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E80(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* ֪ͨL CSFB ������ֹ */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }
            }
#endif
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}




/*******************************************************************************
  MODULE   : Mm_Cell_S9_E80
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMSS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
     2.��    ��   : 2012��2��29��
       ��    ��   : w00167002
       �޸�����   : V7R1C50 ֧��CSFB�����޸�:
                      ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־
     3.��    ��   : 2014��7��7��
       ��    ��   : w00242748
       �޸�����   : DSDS III������
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E81
  FUNCTION : ��MM IDLE ATTEMPTING TO UPDATE,WAIT FOR NETWORK COMMAND״̬���յ�
             MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
      1. ��    ��   : 2007��3��9��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥA32D09099����
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmSmsAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E81
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAN");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E80
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
     3.��    ��   : 2012��2��29��
       ��    ��   : w00167002
       �޸�����   : V7R1C50 ֧��CSFB�����޸�:
                     ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */

        /*lint -e701*/

        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        /*    & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 )))) */
            & (0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            if ( ( ( 0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT32)(0x01 << ( g_MmSsAbortReq.ulTransactionId - 8 ));
            }

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E81
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/

        if ( 0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            if ( ( ( 0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ) ) ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] )
                &&(0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] ) )
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                  */
                /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );         */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                &= ~(VOS_UINT32)(0x01 << ( g_MmSmsAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSmsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

        /*lint +e701*/

    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E80
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬���յ�MMSS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
     2.��    ��   : 2012��2��29��
       ��    ��   : w00167002
       �޸�����   : V7R1C50 ֧��CSFB�����޸�:
                     ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־
     3.��    ��   :2013��8��13��
       ��    ��   :z00161729
       �޸�����   :DTS2013081207431:mm����״̬�յ�cc��t303��ʱabort��Ϣ����Ҫ���棬�յ�resume indʱ�ٴ���
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {
            /* ��ֹ��MM���ӽ��������ڽ�����             */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E80:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */


#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif

            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E81
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬���յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E81:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S16_E80
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬��
             �յ�MMSS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
     2.��    ��   : 2012��2��29��
       ��    ��   : w00167002
       �޸�����   : V7R1C50 ֧��CSFB�����޸�:
                     ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E80(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSsAbortReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI ==
            g_MmSsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E80:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */

#if (FEATURE_ON == FEATURE_LTE)

            /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            }
#endif
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.
                                                        ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;

#if (FEATURE_ON == FEATURE_LTE)

                /* ��ǰ���ڲ���ҵ���CSFB���̣������CSFB���ڱ�־ */
                if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == NAS_MML_GetCsfbServiceStatus())
                {
                    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                }
#endif
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S16_E81
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬��
             �յ�MMSMS_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E81(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsAbortReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                 */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E81:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmSsAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }

            NAS_MM_UpdateCsServiceBufferStatusFlg();
        }
    }

    return;
}


/*******************************************************************************
  MODULE   : Mm_Cell_S16_E66
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬���յ�MMSS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2005.03.28  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E66(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSsRelReq.ulTi ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT32)( 0x01 << g_MmSsRelReq.ulTi );                          /* ����ñ�־λ                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT32)( 0x01 << ( g_MmSsRelReq.ulTi - 8 ) );                  /* ����ñ�־λ                             */
        }
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                RcvXXEstReq.ulTransactionId == g_MmSsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* ���ò����ڻ����MM���� */
        }
        if ( ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
          && ( MM_CONST_NUM_0 ==
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
            /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                      */
            /*    " \nMM:STATUS is  WAIT_FOR_OUTGOING_MM_CONNECTION\r " );      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E66:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E82
  FUNCTION : ��PROCESS CM SERVICE PROMPT״̬��
             �յ�MM_TIMER_PROTECT_CCBS EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2005.04.14  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E82(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */
    /*WUEPS_TRACE( MM_LOG_LEVEL_6, " \nMM:MM_TIMER_PROTECT_CCBS EXPIRED\r " );  */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S27_E82:INFO: MM_TIMER_PROTECT_CCBS EXPIRED");
    MsgMmStatus.MmIeRjctCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER;  /* Service option temporarily out of order  */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* ��䲢���� MM STATUS ��Ϣ                */

    if ( MM_FALSE == Mm_ComMmConnExist( ) )
    {                                                                           /* û�д��ڵ�MM���� */
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
            ucStaOfRcvXXEstReq;                                                 /* ������е�״̬                           */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM��������                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  WAIT_FOR_NETWORK_COMMAND\r " );                 */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart(MM_TIMER_T3240);                                          /* ����TIMER3240                            */
    }
    else
    {                                                                           /* �д��ڵ�MM���� */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        /*WUEPS_TRACE( MM_LOG_LEVEL_1,                                          */
        /*    " \nMM:STATUS is  MM_CONNECTION_ACTIVE\r " );                     */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E82:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    }
}



/* Mm_Cell_S27_E33_Handling_REL_CAUSE_NOT_RL_FAILURE����ʹ�ã�ɾ�� */


/* ɾ��S27E33 */



/*****************************************************************************
 Prototype      : Mm_Cell_S9_E83
 Description    : ��״̬��WAIT FOR OUTGOING MM CONNECTION
                  �յ�GRRMM_EST_SAPI3_CNF�Ĵ���
 Input          : *pRcvMsg  �յ���ԭ��ͷָ��
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-10-22
    Author      : sxbo
    Modification: Created function

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е�ҵ�����״̬

  3.��    ��   : 2013��5��16��
    ��    ��   : w00167002
    �޸�����   : DTS2013051408623:�����Ž���ʱ���û�����绰������绰����ʱ��
                 PD����������µ绰����ʧ�ܡ�
  4.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S9_E83(VOS_VOID *pRcvMsg)
{
    GRRMM_EST_SAPI3_CNF_ST             *pstEstSapi3Cnf;

    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "Mm_Cell_S9_E83:STATE: WAIT_FOR_OUTGOING_MM_CONNECTION Receive GRRMM_EST_SAPI3_CNF.");

    /* ��Ϣ��� */
    if (MM_IE_PD_SMS_MSG != g_MmGlobalInfo.ucMMConnEstingPD)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                    "Mm_Cell_S9_E83: WARNING: Receive GRRMM_EST_SAPI3_CNF error.");

        return;
    }

    /* ��Ϣ������ɹ� */
    pstEstSapi3Cnf = (GRRMM_EST_SAPI3_CNF_ST*)pRcvMsg;

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);  /* ֹͣ����TIMER */

    if (MM_EST_SAPI3_SUCCESS == pstEstSapi3Cnf->ucResult)
    {
        /* ��MM���ӽ����ɹ� */
        Mm_SndSmsEstCnf(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        /*lint -e701*/
        /* TI С��7 */
        if (MM_CONST_NUM_7 >
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
        {
            /* ����MM���Ӵ��ڱ�־ */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]   |=
                (VOS_UINT8)(0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI);
        }
        else /*TI����7 */
        {
            /* ���� MM ���Ӵ��ڱ�־ */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]   |=
                (VOS_UINT8)(0x01 << (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI - 8 ) );
        }
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;  /* ��¼Ǩ��֮ǰ��״̬               */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E83:NORMAL: STATUS is MM_CONNECTION_ACTIVE");

        g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* ����û�����ڽ���������           */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                            = NO_MM_CONN_ESTING;
        Mm_ComCheckDelayMmConn(MM_FALSE);                          /* ����Ƿ��б�������Ҫ������MM���� */

        NAS_MM_UpdateCsServiceConnStatusFlg();

        return;
    }
    else /* SAPI3 ����ʧ�� */
    {
        /* ֪ͨ SMS, MM ���ӽ���ʧ�� */
        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL);

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "Mm_Cell_S9_E83: ERROR: SAPI3 est fail.");
    }

    g_MmGlobalInfo.ucMMConnEstingPD     = NO_MM_CONN_ESTING;       /* ����û�����ڽ���������           */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*****************************************************************************
 Prototype      : Mm_Cell_S9_E86
 Description    : ��״̬��WAIT FOR OUTGOING MM CONNECTION
                  �յ�GRRMM_EST_SAPI3_CNF�Ĵ���
 Input          : *pRcvMsg  �յ���ԭ��ͷָ��
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-10-22
    Author      : sxbo
    Modification: Created function
 2.��    ��  : 2008��12��2��
   ��    ��  : s62952
   �޸�����  : �������ⵥA32D07110�޸�

  3.��    ��   : 2010��3��23��
    ��    ��   : zhoujun /z40661
    �޸�����   : AMR���ʵ���
*****************************************************************************/
VOS_VOID Mm_Cell_S6_E86(VOS_VOID *pRcvMsg)
{
    GAS_RR_CHAN_MOD_IND_ST   *pChanMod;
    MMCC_CHANNEL_MODE_ENUM_U32        enMmCcChanMode;

    pChanMod = (GAS_RR_CHAN_MOD_IND_ST *)pRcvMsg;

    /* ����GSM�����²������ԣ���ʼ��ΪĬ��ֵ */
    g_RrMmSyncInd.ulRabCnt = 1;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabId = 0;
    g_RrMmSyncInd.NasSyncInfo[0].ulCnDomainId = 0;
    g_RrMmSyncInd.ulReason = MMCC_GSM_RES_ASSIGNED;
    g_RrMmSyncInd.NasSyncInfo[0].ulRabSyncInfo = 0;

    enMmCcChanMode = MM_ComGetChanMode(pChanMod->enChanMod);
    if(MMCC_CHAN_MOD_SIG_ONLY == enMmCcChanMode)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_WARNING,
                        "Mm_Cell_S6_E86:  Receive GAS_RR_CHAN_MOD_IND, parameter is error.");
    }

    g_RrMmSyncInd.ulChannelMode = enMmCcChanMode;

    g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg = VOS_TRUE;

    Mm_SndCcSyncInd();
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcInterRatReselInLuProcedure
 ��������  : �ڽ���LU�Ĺ����У�����ϵͳ����ѡ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�

  4.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.ɾ�����õ�ȫ�ֱ���.
  5.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
  6.��    ��   : 2015��6��23��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MM_ProcInterRatReselInLuProcedure(VOS_VOID)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_T3210);

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        /*Ǩ��״̬��limit service*/
        /*���ñ�־Attach not allow*/
        /*ָʾ�ϲ�ҵ��ʧ��*/
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E33:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt++;

    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4)
    {
        enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
        if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
         &&  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_NORMAL_SERVICE");

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
            Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn());
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ProcInterRatReselInLuProcedure:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */

            g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;

        }
        else
        {
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

            /* ��U2�Ĺ������� */
            Mm_ComToU2Handle();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */

            Mm_TimerStop(MM_TIMER_T3211);
            Mm_TimerStart(MM_TIMER_T3211);                                      /* ����T3211                                */
        }
    }
    else
    {
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_ProcInterRatReselInLuProcedure:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

        /* ��U2״̬�����浱ǰ��LAI��Ϣ */
        pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
        pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

        pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
        pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
        pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);

        /* ��U2�Ĺ������� */
        Mm_ComToU2Handle();
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */

        Mm_TimerStop(MM_TIMER_T3212);                                           /* T3212�Ƚ���ֹͣ                                */
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    NAS_MM_ProcDelayService();

    if ((VOS_FALSE  == NAS_MM_IsNeedGmmProcUserDetach())
     && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)))
    {
        NAS_MM_LocalDetach();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcDelayService
 ��������  : �������MMҵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcDelayService(VOS_VOID)
{
    VOS_UINT8                                   ucRrConnRelFlg;
    VOS_UINT8                                   ucTiValidFlg;

    ucRrConnRelFlg = Mm_ComRrConnRelChk();
    if (MM_TRUE == ucRrConnRelFlg)
    {
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                           /* RR���Ӳ�����                             */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }
    else
    {
        ucTiValidFlg = Mm_ComTiChk();
        if (MM_FALSE == ucTiValidFlg)
        {
            Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);                       /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        else
        {
            Mm_ComSigRelForDelayMmConnRej();
        }
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S2_E15
 ��������  : mm��idle limite service/idle plmn search/no cell available״̬�յ�GMMMM_LU_INITIATION�Ĵ���
 �������  : pRcvMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S2_E15(
    VOS_VOID                           *pRcvMsg
)
{
    GMMMM_LU_INITIATION_STRU           *pstMmcLuIni = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvGmmLuIni(pRcvMsg))
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pRcvMsg;

    if ( GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }
}



/*****************************************************************************
 �� �� ��  : Mm_Cell_S3_E54
 ��������  : mm��MM IDLE NORMAL SERVICE ״̬�յ�T3213��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��26��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S3_E54(VOS_VOID* pMsg)
{
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == ulIsTestCard)
    {
        return;
    }

    /* LTE�²��ܷ���LAU */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* ����LAU */
        Mm_ComLuOnly();
    }

    return;
}

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
