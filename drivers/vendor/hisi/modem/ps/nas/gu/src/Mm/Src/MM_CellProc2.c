/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_CellProc2.c
  Description  : MM��������
  Function List:

  History:
      1. ��    ��   : 2006��11��25��
         ��    ��   : s46746
         �޸�����   : ���ⵥ�ţ�A32D07666
      2. ��    ��   : 2007��01��12��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ�ţ�A32D08357
      3. ��    ��   : 2007��3��5��
         ��    ��   : liurui id:40632
         �޸�����   : �������ⵥ�ţ�A32D09094
      4. ��    ��   : 2007��03��24��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ�ţ�A32D09756
      5. ��    ��   : 2007��04��20��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥ�ţ�A32D10235
      6. ��    ��   : 2007��05��14��
         ��    ��   : s46746
         �޸�����   : ���ⵥ�ţ�A32D10820
      7. ��    ��   : 2007��06��04��
         ��    ��   : luojian id:60022475
         �޸�����   : ���ⵥ��:A32D11456
      8. ��    ��   : 2007��08��19��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥ�ţ�A32D12706
      9. ��    ��   : 2007��09��05��
         ��    ��   : luojian id:60022475
         �޸�����   : �������ⵥ�ţ�AT2D01490,MM�յ�ϵͳ��Ϣ��Ҫ�ж�LAI�Ƿ�
                    �����ı��������Ƿ�ͣT3211
      10.��    ��   : 2007��9��21��
         ��    ��   : luojian id:107747
         �޸�����   : ���ⵥ�ţ�AT2D01703,MMCMM_COMBINED_RAU_ACCEPTED��Ϣ����
                      RealFlag��־
      11.��    ��   : 2007��10��23��
         ��    ��   : l39007
         �޸�����   : ���ⵥ�ţ�A32D13044,Mm_Cell_S17_E18,Mm_Cell_S17_E7�޸�
                      ��RauAttCounter���ڵ���5ʱ����һ��LAU�Ĵ���
      12.��    ��   : 2007��11��12��
         ��    ��   : l39007
         �޸�����   : �������ⵥA32D13044,ATTACHʧ��5��,֪ͨMM����һ��LAU,
                      �����ʱMM�Ѿ�ע��,�򲻷���
      13.��    ��   : 2007��12��27��
         ��    ��   : l39007
         �޸�����   : �������ⵥA32D13044,GPRS only Attached(#16),���С��5�Σ�
                      MM״̬�ָ�ǰ״̬���������5�Σ���CS��û��ע�ᣬ����һ��LAU
      19.��    ��   : 2008��05��13��
         ��    ��   : luojian id:107747
         �޸�����   : �������ⵥ�ţ�AT2D03371,MM IDLE ATTEMPTING TO UPDATE״̬��
                      LAI�ı����̷���LAU.
      20.��    ��   : 2008��7��23��
         ��    ��   : luojian id:107747
         �޸�����   : �������ⵥ��AT2D04627/AT2D04237,
                      ATTEMPT TO UPDATE/ATTACH ״̬��CM������
      21.��    ��   : 2008��7��25��
         ��    ��   : luojian 00107747
         �޸�����   : �������ⵥ��AT2D04142/AT2D04677,�޸�RAU ATTEMPT��������5�εĴ���
      22.��    ��   : 2008��7��28��
         ��    ��   : s46746
         �޸�����   : ���ⵥ��:AT2D03915,�޸�����RAU����,CS����Ѿ�����LAU�ɹ�����Ҫ
                      ����with IMSI Attach��RAU
      23.��    ��   : 2008��7��31��
         ��    ��   : s46746
         �޸�����   : ���ⵥ��:AT2D04800,�޸�����RAU����,�������RAUʧ�ܺ󣬵���
                      ����λ�ø�������
      24.��    ��   : 2008��8��13��
         ��    ��   : l0010747
         �޸�����   : ���ⵥ��:AT2D04996/AT2D05037,IDLE ATTEMPT TO UPDATE״ֻ̬����Normal LAU.
      25.��    ��   : 2008��8��21��
         ��    ��   : o00132663
         �޸�����   : ���ⵥ��:AT2D04652,��С���ı�ʱ��ֹͣ��ʱ�� T3211
      26.��    ��   : 2008��8��22��
         ��    ��   : ouyangfei 00132663
         �޸�����   : �������ⵥ��AT2D05087,��������ķ����ҵ�񣬲�����ֻ���״̬��
      27.��    ��   : 2008��8��23��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
      28.��    ��   : 2008��8��26��
         ��    ��   : o00132663
         �޸�����   : ���ⵥ��:AT2D05317,MM���ӹ�����ǿ
      29.��    ��   : 2008��09��03��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05403,mm״̬�޸�
      30.��    ��   : 2008��11��22��
         ��    ��   : o00132663
         �޸�����   : ���ⵥ�ţ�AT2D06931, �����־λucT3212ExpiredFlg
      31.��    ��   : 2009��03��19��
         ��    ��   : s46746
         �޸�����   : ���ⵥ�ţ�AT2D09167, �ػ����̨��ʾΪע�ᵽ2G
      32.��    ��   : 2009��04��03��
         ��    ��   : s46746
         �޸�����   : ���ⵥ�ţ�AT2D10632,TA��֤����Ҫ�ϱ�����״̬�¼��Լ�EPLMN��FPLMN��IMSI Detach�¼�
      33.��    ��   : 2009��04��17��
         ��    ��   : s46746
         �޸�����   : ���ⵥ�ţ�AT2D11062,MM��location update pend״̬������ѡ����ģʽ�����
                      ����λ�ø���ʧ�ܺ�û�������ٴη���λ�ø���
      34.��    ��   : 2009��05��11��
         ��    ��   : h44270
         �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
      35.��    ��   : 2009��06��24��
         ��    ��   : x00115505
         �޸�����   : AT2D12550,Wģʽ������ע��ɹ����û���������detach��δ�õ�������֮ǰ����ϵͳ��ѡ��
                      ��G�£�����ģʽ��ΪII��MM�յ�GSMϵͳ��Ϣ����֪ͨ�ϲ�detach�ɹ���Ȼ������Lu?
      36.��    ��   : 2009��07��03��
         ��    ��   : x00115505
         �޸�����   : AT2D12716,MM��Limited Service״̬��T3212��ʱ��֮���ֻص�
                      ֮ǰפ����С���������Lu������Normal���������ڵ�
      37.��    ��   : 2009��07��18��
         ��    ��   : s46746
         �޸�����   : AT2D12943��CS Detach�󣬲�ѯע��״̬��ȻΪע����������

      38.��    ��   : 2009��07��24��
         ��    ��   : z40661
         �޸�����   : ��ϵͳ��ѡ�󣬽������в��ܽ�ͨ
      39.��    ��   : 2009��09��28��
         ��    ��   : x00115505
         �޸�����   : ���õ����֧��PS�򣬷���CS���ź���ղ���
      40.��    ��   : 2009��10��31��
         ��    ��   : x00115505
         �޸�����   : AT2D15027,��PSע�ᣬ���ŷ�����CS��ʱû�з���ע��
      41.��    ��   : 2009��11��26��
         ��    ��   : x00115505
         �޸�����   : ���÷�����ΪPS ONLY��Ⱥ�����ţ�����һ���ɹ�
      42.��    ��   : 2009��12��24��
         ��    ��   : x00115505
         �޸�����   : ���ⵥ��:AT2D16025,2G�£�detach�����н���������detachʧ��

      43.��    ��   : 2010��3��2��
        ��    ��   : zhoujun /z40661
        �޸�����   : NAS R7Э������
*******************************************************************************/

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-10, begin */
#include        "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-10, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC2_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*lint -save -e958 */

/*******************************************************************************
  Module:   Mm_Cell_S3_E13
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.09  �°�����
  2.  s46746  2006.02.28  A32D03324
  3.  s46746  2006-06-24  �������ⵥA32D04439�޸�
  4. s46746  2006-07-27 �������ⵥA32D03975�޸�
  5. x51137 2006/11/3 A32D06511
  6.��    ��   : 2008��09��03��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  7.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  8.��    ��   : 2011��05��16��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ�DTS2011051005812������ģʽI,��ͬRAI,T3312��ʱʱ,
    ��֧��GPRS��3GС����ѡ����֧��GPRS��2GС������ѡ��ԭ����3GС��,������RAU.
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 11.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
 12.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
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

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);       /* ��¼���̺�ԭ��ֵ                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* �����־λ                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);
            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* ����DETACHԭ��ֵ�Ĺ�������               */
        }
    }
    else
    {                                                                           /* ���Ϊ��A+Iģʽ                          */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                 /* ��¼���̺�ԭ��ֵ                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* �����־λ                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }


            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* ����DETACHԭ��ֵ�Ĺ�������               */
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E15
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�GMMMM_LU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.  ��־��     2005.01.27  007005 for MM
      3.��    ��   : 2009��05��07��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ��AT2D11351/AT2D11735,����ģʽI,GPRS��֧��ʱ,MMע��ɹ���,����ͬλ������������LU
      4.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;
    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if(  (GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
       &&(VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
    {
        return;                                                              /*�Ƕ�ʱ����ʱ�����LU�����ǵ�LAIû�ı�ʱΪ��ȥ��Gs������ */
    }

    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && ((GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
      || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)))
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;        /* ����LU����Ϊ����                         */
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                /* ����LU����ΪNORMAL                       */
    }

    Mm_ComLuOnly();                                                          /* ����LU����                               */

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E16
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�
            GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E16(VOS_VOID *pMsg)
{
    VOS_UINT8 ucCause;

    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }
    Mm_ComAuthenRcvAuthenRej();                                                 /* ���ü�Ȩʧ�ܵĹ�������                   */

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E17
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�GMMMM_COMBINED_RAU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2003.12.09   �°�����
      2.  ��    ��   : 2008��8��21��
          ��    ��   : l00130025
          �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
      3.  ��    ��   : 2008��11��22��
          ��    ��   : o00132663
          �޸�����   : ���ⵥ�ţ�AT2D06931, �����־λucT3212ExpiredFlg
      4.  ��    ��   : 2011��07��15��
          ��    ��   : l65478
          �޸�����   : ���ⵥ�ţ�DTS2011071101580, ϵͳ����ѡ����ʧ��
      5.  ��    ��   : 2012��06��1��
          ��    ��   : z00161729
          �޸�����   : V7R1C50 GUL�������޸ģ�L�¿�������ע��eps only�ɹ���cs����δattach̬��
                       bg�Ѹ����ȼ�����ɹ�������ָ���ѳɹ�������ע�����syscfg����ps
                       only,mmֱ�ӻظ�detach cnf��cs reg result indǨ��limit service״̬��
                       �������յ�����ע��init��Ϣ��ӦǨ״̬
     6.��    ��   : 2012��12��22��
       ��    ��   : l65478
       �޸�����   : DTS2012122103936 �����������ʱMM״̬Ǩ�ƴ���
     7.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    8.��    ��   : 2013��7��25��
      ��    ��    : w00242748
      �޸�����    : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                    �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                    rau req�д�follow on��־,����ȷЭ������
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E17(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmCombinedRauInitiation(pMsg))
    {
        return;
    }
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return;
    }

    /* ��ΪMM_WAIT_FOR_ATTACHΪ��̬,�����ʱ����,������ע��ʧ��ʱ,
       ��ָ���ע��ǰ��״̬,��ʱ�ָ���MM_WAIT_FOR_ATTACH��Ӱ��ҵ�� */
    if (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    }
    Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E17:NORMAL: STATUS is  LOCATION_UPDATING_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E17
  Function: ��LOCATION UPDATING PENDING״̬���յ�GMMMM_COMBINED_RAU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ŷ����      2009.03.11   �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E17(VOS_VOID *pMsg)
{
    /* ��GSM�£����ԭ���յ�COMBINED_RAU_ACCEPTED with PS ONLY ACCEPTED, 5��ʧ�ܺ�MM������ʱ��MM_TIMER_DELAY_LU_GSM
       �ӳ�1�뷢��LU, �����ʱ���յ�GMM������ע�Ὺʼ��Ϣ������ͣ���ö�ʱ��������ͬʱ����RAU��LU */
    Mm_TimerStop(MM_TIMER_DELAY_LU_GSM);
}

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */

/*******************************************************************************
  Module:   Mm_Cell_S4_E5
  Function: ��MM IDLE LIMITED SERVICE״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.11  �°�����
      2.  s46746     2006.07.26  �������ⵥA32D03975�޸�
      3.��    ��   : 2006��10��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D05960
      4.��    ��   : 2007��04��20��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D10235
      5.��    ��   : 2010��11��09��
        ��    ��   : ŷ����
        �޸�����   : �������ⵥ�ţ�DTS2010111500211, GCF 9.4.3.3��LAUʧ��4�κ����б����ڼ䣬�û������������
                     ��ֹ�б��ѣ���ԭС�����к��У����н������MM�յ�ԭС����ϵͳ��Ϣ������
                     ��������LAU��Ӧ����T3212��ʱ���ٷ���LAU.
      6.��    ��   : 2011��7��16��
        ��    ��   : h44270
        �޸�����   : V7R1 PhaseII�׶ε�����ע������
      7.��    ��   : 2011��06��02��
        ��    ��   : l65478
        �޸�����   : DTS2011060103515 GCF���ԣ������Ʒ����£��û�ָ����ǰפ�����������ָ������ʱ��Э��ջ���ᷢ��ע��
      8.��    ��   : 2011��6��3��
        ��    ��   : c00173809
        �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
      8.��    ��   : 2011��10��15��
        ��    ��   : h44270
        �޸�����   : GUL NAS2�׶Σ������ó�PS ONLYʱ��������limit service�����ظ�ע�������
      9.��    ��   : 2011��11��22��
        ��    ��   : w00166186
        �޸�����   : DTS2011110902856,����ģʽI��CSȥע�ᣬ��Ϊ����ģʽII�󣬷���CS ATTACH��������ע��
      10.��    ��   : 2011��10��27��
        ��    ��   : s46746
        �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     11.��    ��   : 2012��02��29��
        ��    ��   : l00130025
        �޸�����   : DTS2012022206186:������LAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
     12.��    ��   : 2012��03��17��
        ��    ��   : s46746
        �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
     13.��    ��   : 2012��2��20��
         ��    ��   : z00161729
         �޸�����   : V7R1C50 ֧��CSFB�����޸�
     14.��    ��   : 2012��3��09��
         ��    ��   : w00167002
         �޸�����   : V7R1C50 ֧��CSFB�����޸�:��CSFB��־����ʱ�����𵥶���LAU
     15.��    ��   : 2012��3��09��
        ��    ��   : z00161729
        �޸�����   : V7R1C50 ֧��ISR�����޸�
     16.��    ��   : 2012��05��21��
        ��    ��   : z40661
        �޸�����   : DTS2012052308001:��L��ѡ��G�󷴸�����LAU
     17.��    ��   : 2012��10��22��
        ��    ��   : t00212959
        �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
     18.��    ��   : 2012��11��13��
        ��    ��   : l00167671
        �޸�����   : DTS2012111204799:L->W csfb,������L��Wʱ��PS�򱻾�11���绰�ҶϺ�û�з�������
     19.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
     20.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

     21.��    ��   : 2013��12��5��
        ��    ��   : w00167002
        �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                     PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                     �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                     �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ��¡�
     22.��    ��   : 2014��04��1��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż��Լ�ʹ��MML�е��滻MMȫ�ֱ���
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucLaChgFlg = VOS_FALSE;
    VOS_UINT8                           ucUserSpecificSearchFLg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }

    ucUserSpecificSearchFLg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    ucLaChgFlg = NAS_MML_IsCsLaiChanged();

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
     )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
             || (VOS_TRUE == ucUserSpecificSearchFLg))
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            {
                /* LAI�ı�,�����û������ָ������ʱ,����LU���� */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    }
    else
    {                                                                           /* ��A+Iģʽ                                */
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod)
        {
            if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                && (VOS_FALSE == ucLaChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType =
                                MM_IE_LUT_PERIODIC_UPDATING;            /* ����LU����                               */
                Mm_ComLuOnly();                                         /* ����LU REQ                               */
            }
            else if ( (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                   && (VOS_FALSE == ucLaChgFlg))
            {
                if ((MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
                 && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;
                    Mm_ComLuOnly();
                }
                else if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                           "Mm_Cell_S4_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");


                    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);
                }
                else
                {
                }
            }
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            else if ((VOS_FALSE        == NAS_MML_IsCampLaiInfoChanged())
                  && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (VOS_FALSE        == ucUserSpecificSearchFLg))
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            {
                /* ��ǰפ��С�����ϴ�פ��С����ͬ������T3212�������У���ʱ����Ҫ����LAU����T3212��ʱ���� */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
                /* �ϱ�ע��ʧ��,��֤����״̬����ȷ�� */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                Mm_ComLuOnly();                                         /* ����LU REQ                               */
            }
        }
        else
        {
            Mm_ComNetModeChange();
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    }

}

/*******************************************************************************
  Module:   Mm_Cell_S4_E15
  Function: ��MM IDLE LIMITED SERVICE״̬���յ�GMMMM_LU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2. ��    ��   : 2012��3��31��
         ��    ��   : z00161729
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU            *pstLuIniMsg;

    pstLuIniMsg  = (GMMMM_LU_INITIATION_STRU *)pMsg;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    if (GMMMM_T3412OrT3423_EXPIRED == pstLuIniMsg->enTimerExpiredFlg)
    {
        /* ����LU����Ϊ���� */
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                       /* ����LU����ΪNORMAL                       */
    }

    Mm_ComLuOnly();                                                             /* ����LU����                               */
}

/*******************************************************************************
  Module:   Mm_Cell_S6_E15
  Function: ��MM IDLE LOCATION UPDATE NEEDED״̬���յ�GMMMM_LU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ŷ����     2009.05.22  �°�����
      4. ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg) )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E5
  Function: ��MM IDLE ATTEMPTING TO UPDATE״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.11  �°�����
      2.  s46746     2006.07.27  �������ⵥA32D03975�޸�
      3.��    ��   : 2006��10��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D05960
      4.��    ��   : 2006��10��22��
        ��    ��   : l60022475
        �޸�����   : ���ⵥ�ţ�A32D07582
      5.��    ��   : 2006��10��22��
        ��    ��   : l60022475
        �޸�����   : ���ⵥ�ţ�A32D07583
      6.��    ��   : 2007��3��5��
        ��    ��   : liurui id:40632
        �޸�����   : �������ⵥ�ţ�A32D09094
      7.��    ��   : 2007��04��20��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D10235
      8.��    ��   : 2008��05��13��
        ��    ��   : luojian id:107747
        �޸�����   : �������ⵥ�ţ�AT2D03371
      9.��    ��   : 2008��8��13��
        ��    ��   : l0010747
        �޸�����   : ���ⵥ��:AT2D04996/AT2D05037
     10.��    ��   : 2009��01��15��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
     11.��    ��   : 2009��05��11��
        ��    ��   : h44270
        �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
     12.��    ��   : 2009��08��6��
        ��    ��   : l65478
        �޸�����   : �����»ص�ԭ����LA�󣬲�Ӧ�÷���LU
     13.��    ��   : 2010��11��21��
        ��    ��   : z00161729
        �޸�����  : ���ⵥ�ţ�DTS2010111602266:G��CSע��ʧ��ԭ������ָ�ɾܾ�,MM���յ�
                    RRMM_AC_INFORMATION_CHANGE_IND T3122��ʱ��Ϣ�󷴸�����LU,����PS��������ָ�,Ӱ����������
     14.��    ��   : 2011��7��16��
        ��    ��   : h44270
        �޸�����   : V7R1 PhaseII�׶ε�����ע������
     15.��    ��   : 2011��06��02��
        ��    ��   : l65478
        �޸�����   : DTS2011060103515 GCF���ԣ������Ʒ����£��û�ָ����ǰפ�����������ָ������ʱ��Э��ջ���ᷢ��ע��
     16.��    ��   : 2011��6��3��
        ��    ��   : c00173809
        �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
     17.��    ��   : 2011��10��27��
        ��    ��   : s46746
        �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     18.��    ��   : 2012��1��30��
        ��    ��   : l00130025
        �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
     19.��    ��   : 2012��03��17��
        ��    ��   : s46746
        �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
     20.��    ��   : 2012��2��15��
         ��    ��   : z00161729
         �޸�����   : V7R1C50 ֧��CSFB�����޸�
     21.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     22.��    ��   : 2012��3��09��
        ��    ��   : w00167002
        �޸�����   : V7R1C50 ֧��CSFB�����޸�:��CSFB��־����ʱ�����𵥶���LAU
     23.��    ��   : 2012��05��21��
        ��    ��   :  z40661
        �޸�����   :  DTS2012052308001:��L��ѡ��G�󷴸�����LAU
     24.��    ��   : 2012��10��22��
        ��    ��   : t00212959
        �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
     25.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
     26.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     27.��    ��   : 2013��07��05��
        ��    ��   : l65478
        �޸�����   : DTS2013070408274:MM����NORMAL SERVICE��û�д������CC��Ϣ
     28.��    ��   :2013��10��8��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     29.��    ��   : 2013��12��5��
        ��    ��   : w00167002
        �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                  PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                  �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                  �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ��¡�
     30.��    ��   : 2014��04��1��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż��Լ�ʹ��MML�е��滻MM��ȫ�ֱ���
     31.��    ��   : 2015��5��27��
        ��    ��   : b00269685
        �޸�����   : LAC�仯�����3213��ʱ��
     32.��    ��   : 2015��8��13��
        ��    ��   : l00289540
        �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E5(VOS_VOID *pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    VOS_UINT32                          ucLaChgFlg;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    VOS_UINT8                           ucUserSpecificSearchFlg;
    VOS_UINT32                          ul3211Status;

    VOS_UINT32                          ulT3213Status;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();

#endif

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, begin */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, end */



    ul3211Status = NAS_MM_QryTimerStatus(MM_TIMER_T3211);


    ulT3213Status = NAS_MM_QryTimerStatus(MM_TIMER_T3213);

    ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    ucLaChgFlg   = NAS_MML_IsCsLaiChanged();

    if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
    }

    if ( (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_T3213))
      && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg) )
    {
        /* ���С����Ϣ�ı䣬���������ʧ��ԭ��ֵ����T3213��ʱ����ʱʱ������LAU */
        NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (MM_FALSE == g_MmGlobalInfo.ucLikeNetmode2)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        if ( (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
          || (MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
          || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {                                                                       /* RACΪ0�ĳ���                             */
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
            if ((VOS_TRUE       == NAS_MML_IsCampLaiInfoChanged())
             || ((VOS_TRUE      == ucUserSpecificSearchFlg)
              && (MM_TIMER_STOP == ul3211Status)))
            {
                /* LAI�����ı�,�����û�ָ������ʱ,ǿ��ִ��LU���� */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
                   &&(MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* ����LU REQ                               */
                g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
            }
            else if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
                {
                    /* ��MMC����CSע����,��PSע��ʧ�ܣ���������Ҫ��MMC�ϱ�ԭ��ֵΪOTHER CAUSE */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);          /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
                }

            }
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        else
        {                                                                       /* RAC��������                              */
            /*stop T3211*/
            Mm_TimerStop(MM_TIMER_T3211);
            g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt          = 0;
        }
    }
    else
    {                                                                           /* ��A+I                                    */
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComNetModeChange();
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
             && (VOS_FALSE                              == ucLaChgFlg))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        {
            Mm_ComSysInfoHandleWithLaiNoChange(0);
            if (VOS_TRUE == ulIsTestCard)
            {
                Mm_TimerStop(MM_TIMER_T3213);
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        else if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
              || ((VOS_TRUE      == ucUserSpecificSearchFlg)
               && (MM_TIMER_STOP == ul3211Status)))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        {
            /* LAI�����ı�,�����û�ָ������ʱ,ǿ��ִ��LU���� */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
            && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
            Mm_ComLuOnly();                                                 /* ����LU REQ                               */
            g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
            {
                /* ��MMC����CSע����,��PSע��ʧ�ܣ���������Ҫ��MMC�ϱ�ԭ��ֵΪOTHER CAUSE */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);                 /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND,ʹMMCǨ��״̬ */
            }

        }

        /* ��·�ͷź������·���LAU,�������յ�sysinfo��û�з���LAU */
        if ((VOS_TRUE == g_MmGlobalInfo.ucRetryLauFlg)
            && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState))
        {
            Mm_ComLuOnly();
        }

    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */

    NAS_MM_ProcT3213AttemptCounter(ulT3213Status);

    /* ��־��λ */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    Mm_DealWithBuffMsg();

}

/*******************************************************************************
  Module:   Mm_Cell_S6_E5
  Function: ��MM_IDLE_LOCATION_UPDATE_NEEDED״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2004.04.09  �°�����
  2.  s46746     2006.07.26  �������ⵥA32D03975�޸�
  3.��    ��   : 2006��10��6��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D05960
  4.��    ��   : 2006��11��22��
    ��    ��   : l60022475
    �޸�����   : ���ⵥ�ţ�A32D07582
  5.��    ��   : 2007��04��20��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ�ţ�A32D10235
  6.��    ��   : 2007��09��05��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�AT2D01490
  7.��    ��   : 2008��08��21��
    ��    ��   : ouyangfei id:00132663
    �޸�����   : ���ⵥ�ţ�AT2D04652,��С���ı�ʱ��ֹͣ��ʱ�� T3211
  8.��    ��   : 2009��08��21��
    ��    ��   : ouyangfei id:00132663
    �޸�����   : ���ⵥ�ţ�AT2D13967,��С��δ�ı��ҷ���״̬ΪU1ʱ��MMǨ��IDLE_NORMAL_SERVICE��
  9.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  10.��    ��   : 2011��7��25��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  11.��    ��   : 2011��6��3��
     ��    ��   : c00173809
     �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
  12.��    ��   : 2012��2��15��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ����
  13.��    ��   : 2012��3��09��
     ��    ��   : w00167002
     �޸�����   : V7R1C50 ֧��CSFB�����޸�:��CSFB��־����ʱ�����𵥶���LAU
  14.��    ��   : 2012��10��22��
     ��    ��   : t00212959
     �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
  15.��    ��   : 2013��2��4��
     ��    ��   : w00176964
     �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  16.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  17.��    ��   : 2013��07��05��
     ��    ��   : l65478
     �޸�����   : DTS2013070408274:MM����NORMAL SERVICE��û�д������CC��Ϣ
  18.��    ��   : 2013��12��02��
     ��    ��   : w00242748
     �޸�����   : DTS2013112712538:W NMOI cs�ϴ���ĳλ����ע��ɹ����ٴο�����
                  �յ�ϵͳ��Ϣָʾ��λ��CS/PS��bar����ʱ������LAU������RAU�����ţ�
                  ���յ�ϵͳ��Ϣ��ָʾ��λ����CS����bar��PS��bar����ʱ������LAU
  19.��    ��   : 2013��12��5��
     ��    ��   : w00167002
     �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                  PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                  �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                  �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ��¡�
  20.��    ��   : 2014��3��21��
     ��    ��   : z00161729
     �޸�����   : DTS2014031906506:GCF 8.1.2.16,w������ע��ɹ������ϱ�ϵͳ��Ϣcsע���ֹ�����ϱ�csע�᲻��ֹ��psע�ᱻ����mm�յ�ϵͳ
                 ��Ϣ����lau����������������lau
  21.��    ��   : 2014��04��1��
     ��    ��   : w00176964
     �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
  22.��    ��   : 2015��3��20��
     ��    ��   : w00167002
     �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                  ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E5(VOS_VOID *pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, begin */
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-17, end */

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ((VOS_TRUE == ulLaiChangeFlag)
        || (g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }
    /* <==AT2D01490 */

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS             == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                               /* ���LAI����,����״̬ΪU1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;            /* ����LU����                               */
                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                    Mm_ComLuOnly();                                         /* ����LU REQ                               */
                }
                else
                {
                    Mm_ComNasInfoSav(
                             MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn()
                             );
                    g_MmGlobalInfo.ucMmServiceState =
                        MM_NORMAL_SERVICE;                          /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */


                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* ����LU REQ                               */
            }
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        else if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                                   /* ���LAI����,����״̬ΪU1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* ����LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* ����LU REQ                               */
                }
                else
                {
                    NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1();
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* ����LU REQ                               */
            }
        }
        else
        {                                                                       /* RAC��������                              */
            ;
        }
    }
    else
    {
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* ������ϵͳ��Ϣ�Ĺ�������                 */
    }


    Mm_DealWithBuffMsg();
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E13
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��
            �յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      3.��    ��   : 2013��9��12��
        ��    ��   : w00242748
        �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                     ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                     G��ԭС��ʱ��LAU
      4.��    ��   : 2013��9��14��
        ��    ��   : z00161729
        �޸�����   : DTS2013082903019:֧��ss�ط�����
      5.��    ��   : 2014��4��2��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
      6.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
      2.��    ��   : 2015��3��20��
        ��    ��   : w00167002
        �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E13(VOS_VOID *pMsg)
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

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* ��¼���̺�ԭ��ֵ                         */
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_TimerStop(MM_TIMER_T3230);                                       /* ֹͣT3230                                */
            if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
            {
                /* �ͷų������������д��ں����ڽ�����MM���� */
                Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
            }
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            if ((MM_FALSE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg)
                && (MMCC_EMERGENCY_CALL !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType))
            {
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����T3240                                */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E14
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��,
                �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.  ��־��        2005.01.27  007037 for MM
      3.��    ��   : 2011��03��31��
        ��    ��   : c00173809
        �޸�����   : ���ⵥ��:DTS2011032802664,UEפ��VPLMN����BG��,פ�������ȼ�
                     ����,COMBINED RAU PS�ɹ�,CS�ܾ�ԭ��15,û�ѵ�ǰ����.
      4.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      5.��    ��   : 2013��1��16��
        ��    ��   : w00176964
        �޸�����   : DTS2013011508939:A+Iģʽ,PSע��ʧ�ܴﵽ��������Ҫ��¼LIKEB���
      6.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      7.��    ��   : 2013��9��14��
        ��    ��   : z00161729
        �޸�����   : DTS2013082903019:֧��ss�ط�����
      8.��    ��   : 2014��4��2��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
      9.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType;
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
    {                                                                           /* ���Ϊʧ�ܵĳ���                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* ����ΪRAU�ĳ���                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* ����ΪATTACH�ĳ���                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* ����ΪSR�ĳ���                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            ucActionType = MM_NULL_PROC;
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {                                                                       /* ������Ͳ�Ϊ�յĳ���                     */
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* ֹͣT3230                                */
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");
                /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

                /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                {
                    /* �ͷų������������д��ں����ڽ�����MM���� */
                    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                }
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                if ((MM_FALSE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucEstingCallTypeFlg)
                    && (MMCC_EMERGENCY_CALL !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulCallType))
                {
                    Mm_TimerStart(MM_TIMER_T3240);                          /* ����T3240                                */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_TimerStop(MM_TIMER_T3210);                               /* ֹͣT3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                    {
                        /* �ͷų������������д��ں����ڽ�����MM���� */
                        Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                    }
                    Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

                    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                    if ((MM_FALSE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucEstingCallTypeFlg)
                        && (MMCC_EMERGENCY_CALL !=
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ulCallType))
                    {
                        Mm_TimerStart(MM_TIMER_T3240);                          /* ����T3240                                */
                        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    }
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ������Bģʽ��ȫ����                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:

                /* A+I��,PSע��ʧ�ܴﵽ������,MM���ڽ��н�������,��ʱ��Ҫ֪ͨMMC��ǰCS��������ע��
                   �ȴ�RRC����פ������LAU������attach */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }

                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E44
  Function: ��WAIT FOR OUTGOING MM CONNECTION״̬��
            �յ�RRMM_DATA_IND(MM STATUS)�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
        1.  ��־��     2003.12.09  �°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E44(VOS_VOID *pMsg)
{
    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E9
  Function: ��WAIT_FOR_NETWORK_COMMAND״̬��
            �յ�GMMMM_IMSI_DETACH_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
      3.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/

VOS_VOID Mm_Cell_S11_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;

    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* ͣT3240                                  */

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E11
  Function: ��WAIT_FOR_NETWORK_COMMAND״̬��
            �յ�GMMMM_GPRS_DETACH_INITIATION�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E11(VOS_VOID *pMsg)
{
    if (MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* ͣT3240                                  */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}


/*******************************************************************************
  Module:   Mm_Cell_S11_E13
  Function: ��WAIT_FOR_NETWORK_COMMAND״̬���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.��    ��   : 2014��4��2��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
      3.��    ��   : 2015��3��20��
        ��    ��   : w00167002
        �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                     ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E13(VOS_VOID *pMsg)
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

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* ����ɾ��IMSI�Ĺ�������                   */
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* ��¼���̺�ԭ��ֵ                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E14
  Function: ��WAIT_FOR_NETWORK_COMMAND״̬��
            �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.��    ��   : 2011��03��31��
        ��    ��   : c00173809
        �޸�����   : ���ⵥ��:DTS2011032802664,UEפ��VPLMN����BG��,פ�������ȼ�
                     ����,COMBINED RAU PS�ɹ�,CS�ܾ�ԭ��15,û�ѵ�ǰ����.
      3.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
      4.��    ��   : 2014��4��2��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ( MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg) )
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult )
    {                                                                           /* ���Ϊʧ�ܵĳ���                         */
        switch ( pstGmmActionRstInd->enGmmActionType )
        {
        case GMMMM_ACTION_RAU:                                                 /* ����ΪRAU�ĳ���                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* ����ΪATTACH�ĳ���                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* ����ΪSR�ĳ���                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if ( MM_NULL_PROC != ucActionType )
        {                                                                       /* �������Ϊ�յĳ���                       */
            switch ( pstGmmActionRstInd->enCause )
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                  (VOS_UINT8)pstGmmActionRstInd->enCause);        /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* ��¼���̺�ԭ��ֵ                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                    Mm_ComToNoImsiHandle();                                     /* ����ɾ��IMSI�Ĺ�������                   */
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ������Bģʽ��ȫ����                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* ��¼���̺�ԭ��ֵ                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:
                /* A+I��,PSע��ʧ�ܴﵽ������,MM���ڽ��н�������,��ʱ��Ҫ֪ͨMMC��ǰCS��������ע��
                   �ȴ�RRC����פ������LAU������attach */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E16
  Function: ��WAIT_FOR_NETWORK_COMMAND״̬��
            �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E16(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg) )
    {
        return;

    }
    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* ��¼���̺�ԭ��ֵ                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* ���÷���״̬                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* ����ɾ��IMSI�Ĺ�������                   */
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E13
  Function: ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��,
                �յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2003.12.09  �°�����
  2.��־��        2005.01.27  007037 for MM
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��9��14��
    ��    ��   : z00161729
    �޸�����   : DTS2013082903019:֧��ss�ط�����
  6.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  8.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* ��¼��ǰ������                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ֹͣT3230                                */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E13: Network IMSI detach, Could not make CS call");
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        Mm_ComToU2Handle();                                                     /* ����MM��U2�Ĵ���                         */
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
        /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_TimerStop(MM_TIMER_T3218);                                           /* ͣT3218                                  */
        Mm_ComDelRandRes();                                                     /* ɾ��RAND��RES                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3230);                                       /* ֹͣT3230                                */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ������Bģʽ��ȫ����                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            /* ���緢�� DETACH��MS����ATTACH:����ط��ظ�cs detach�����ʣ���Ӧ�ûظ�forb other */
            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                /* ���緢�� DETACH��MS����ATTACH:����ط��ظ�cs detach�����ʣ���Ӧ�ûظ�forb other */
                Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_ComNetDetachCauseHandle(
                                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E14
  Function: ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��,
                �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2003.12.09  �°�����
  2.��־��        2005.01.27  007037 for MM
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��1��16��
    ��    ��   : w00176964
    �޸�����   : DTS2013011508939:A+Iģʽ,PSע��ʧ�ܴﵽ��������Ҫ��¼LIKEB���
  6.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  7.��    ��   :2013��9��14��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E14(VOS_VOID* pMsg)
{

    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT32                               ulCsServExist;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;

    }

    ulCsServExist  = Mm_ComJudgeCsServExist();
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {
        return;
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {                                                                           /* ���Ϊʧ�ܵĳ���                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* ����ΪRAU�ĳ���                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* ����ΪATTACH�ĳ���                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* ����ΪSR�ĳ���                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* ֹͣT3230                                */
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                            g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
                    /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
                    /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* ������Bģʽ��ȫ����                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                if (MM_STATUS_ATTACHED ==
                                    g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                        /* ԭ��ֵ12���ܲ������������Ų������ٳ����ز�������״̬��MM_COM_SRVST_LIMITED_SERVICE_REGION,*/
                        if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
                        }
                        else
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
                        }

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* ֪ͨMMC��CS���ҵ���Ѿ�ֹͣ              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;

            default:
                /* A+I��,PSע��ʧ�ܴﵽ������,MM���ڽ��н�������,��ʱ��Ҫ֪ͨMMC��ǰCS��������ע��
                   �ȴ�RRC����פ������LAU������attach */
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E16
  Function: ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��,
                �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2003.12.09  �°�����
  2.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   :2013��9��14��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_Cell_S12_E16(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);                                            /* ͣ������ʱ��                             */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

    Mm_ComAuthenRcvAuthenRej();                                                 /* ���ü�Ȩʧ�ܵĹ�������                   */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, begin */
    /* Mm_SndMmcCmSvcInd��Mm_ComRelAllMmConn���ϱ� */
    /* Deleted by s00217060 for K3V3 ��ģ����������, 2014-07-22, end */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

}
/*******************************************************************************
  Module:   Mm_Cell_S14_E13
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
                �յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.11  ���ݶ��ڽӿڸ���,�°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E13(VOS_VOID *pMsg)
{
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        Mm_Cell_S9_E13(pMsg);
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ֹͣT3230                                */
    }
    else
    {
        Mm_Cell_S12_E13(pMsg);
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E14
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
                �յ�GMMMM_GMM_ACTION_RESULT_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.11  ���ݶ��ڽӿڸ���,�°�����
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E14(VOS_VOID *pMsg)
{
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_Cell_S9_E14(pMsg);
    }
    else
    {
        Mm_Cell_S12_E14(pMsg);
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S14_E16
  Function: ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��,
                �յ�GMMMM_AUTHENTICATON_FAILURE_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2004.03.11  ���ݶ��ڽӿڸ���,�°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E16(VOS_VOID *pMsg)
{
    Mm_ComAuthenRcvAuthenRej();
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E5
  Function: ��LOCATION UPDATING PENDING״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.11  �°�����
  2.  s46746     2006.07.26  �������ⵥA32D03975�޸�
  3.��    ��   : 2006��10��6��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D05960
  4.��    ��   : 2007��04��20��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D10235
  5.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2011��05��16��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ�DTS2011051005812������ģʽI,��ͬRAI,T3312��ʱʱ,��֧��GPRS��3GС����ѡ����֧��GPRS��2GС������ѡ��ԭ����3GС��,������RAU.
  7.��    ��   : 2011��6��3��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
  8.��    ��  : 2012��2��15��
    ��    ��  : w00167002
    �޸�����  : V7R1C50 ֧��CSFB�����޸ģ����ӶԴ���CSFB��־ʱ�Ĵ���
  9.��    ��  : 2012��2��15��
    ��    ��  : w00176964
    �޸�����  : DTS2012111301625:Pending״̬����Ҫ�ж�like B���
 10.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 11.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 12.��    ��   : 2013��07��05��
    ��    ��   : l65478
    �޸�����   : DTS2013070408274:MM����NORMAL SERVICE��û�д������CC��Ϣ

 13.��    ��   : 2013��12��5��
    ��    ��   : w00167002
    �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                  PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                  �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                  �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ���
 14.��    ��   : 2014��04��1��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */

    /* CS ONLY��PS ONLY��nmo1��GMM��������ע�� */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
     /* pending״̬����Ҫ�ж�like B��� */
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
    )
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            {                                                               /* LAI�仯�ĳ���                            */
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    }
    else
    {                                                                           /* ��A+Iģʽ                                */
        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComNetModeChange();
        }
        else
        {   /* A+II����Bģʽ                            */
            ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
            Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* ������ϵͳ��Ϣ�Ĺ�������                 */
        }
    }

    Mm_DealWithBuffMsg();
}


/*******************************************************************************
  Module:   Mm_Cell_S17_E7
  Function: ��LOCATION UPDATING PENDING״̬��,
                �յ�GMMMM_COMBINED_ATTACH_ACCEPTED�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.  x51137  2006/4/14 A32D02955
      3.  s46746  2006-06-24  �������ⵥA32D04439�޸�
      4.��    ��   : 2007��10��23��
        ��    ��   : l39007
        �޸�����   : ���ⵥ�ţ�A32D13044
      5.��    ��   : 2007��11��12��
        ��    ��   : l39007
        �޸�����   : �������ⵥA32D13044,ATTACHʧ��5��,֪ͨMM����һ��LAU,
                     �����ʱMM�Ѿ�ע��,�򲻷���
      6.��    ��   : 2007��12��27��
        ��    ��   : l39007
        �޸�����   : �������ⵥA32D13044,GPRS only Attached(#16),���С��5�Σ�
                     MM״̬�ָ�ǰ״̬���������5�Σ���CS��û��ע�ᣬ����һ��LAU
      7.��    ��   : 2008��7��25��
        ��    ��   : luojian 00107747
        �޸�����   : �������ⵥ��AT2D04142/AT2D04677,�޸�RAU ATTEMPT��������5�εĴ���
      8.��    ��   : 2010��9��30��
        ��    ��   : ŷ���� 00132663
        �޸�����   : �������ⵥ��DTS2010092902368,TMSIֻ�ڵ�ЧPLMN����Ч
      9.��    ��   : 2010��11��24��
        ��    ��   : ��ë 00166186
        �޸�����   : �������ⵥ��DTS2010112205253,����ATTACH�ɹ��ķ�֧�����LAU������
    10. ��    ��   : 2010��12��24��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
    11.��    ��   : 2011��7��25��
       ��    ��   : h44270
       �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    12.��    ��   : 2011��12��25��
       ��    ��   : w00166186
       �޸�����   : DT2011121903902,��ѡL�󣬻�W������ע�ᱻ16��5�κ󣬲�����LAU
    13.��    ��   : 2012��3��1��
       ��    ��   : w00176964
       �޸�����   : DTS2012022407450:GMM��������ע��ʱ��֪ͨ��MM,MM��¼����
    14.��    ��   : 2012��03��17��
       ��    ��   : s46746
       �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
    15.��    ��   : 2013��05��15��
       ��    ��   : s46746
       �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
    16.��    ��   : 2013��07��5��
       ��    ��   : w00176964
       �޸�����   : DTS2013062503351:LAU�ɹ�ʱ���µ�ǰ��RAC��Ϣ
    17.��    ��   : 2014��2��18��
       ��    ��   : l00215384
       �޸�����   : DTS2014021006453��ע��ɹ����Ȩ�ܾ���������
    18.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
    19.��    ��   : 2015��3��20��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
    20.��    ��   : 2015��8��13��
       ��    ��   : l00289540
       �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E7(VOS_VOID *pMsg)
{

    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU     *pCombinedAttatchAccpt;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    if ( MM_FALSE == Mm_RcvGmmCombinedAttachAccept(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pCombinedAttatchAccpt = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU*)pMsg;
    if ( GMMMM_ATTACH_RESLUT_COMBINED ==
                        pCombinedAttatchAccpt->enAttachResult )
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* ͣT3211                                  */
        Mm_ComSaveProcAndCauseVal(MM_COMB_ATTACH_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NORMAL_SERVICE");
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        /* ��¼ע��ɹ���RAC����������ģʽ�ı�,�Ƚ�RAI�Ƿ����ı� */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* ��������ģʽ�ı�,RAI���ı�ʱ,MMû�и�������ģʽ,��GMMģ����ܻ�
           �������Ϲ��̣�Ϊ��֤����������GMMһ�£��˴���Ҫ��������ģʽ */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        if ( GMMMM_MS_ID_TYPE_IMSI ==
                                pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* ����TMSI��Ч                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if ( GMMMM_MS_ID_TYPE_TMSI ==
                            pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                    MM_MS_ID_TMSI_PRESENT;      /* ����TMSI��Ч                             */
            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       pCombinedAttatchAccpt->stMsIdentity.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        }
        else
        {

        }
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* LAU ���������� */

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
        pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;


        /* ��ʾMM���ڽ�������ע�� */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pCombinedAttatchAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
            Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
            Mm_TimerStop( MM_TIMER_T3211 );                                         /* ͣT3211                                  */
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_ATTACH_PROC,
                                      (VOS_UINT8)pCombinedAttatchAccpt->enCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* ���ý�NO IMSI�Ĺ�������                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
            if ( pCombinedAttatchAccpt->ulAttachAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
                {

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                }

                if( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                }
            }
            else
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    if(( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg ) && ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg ))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* ����LU����                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* ����LU����                               */
                    }
                    Mm_ComLuOnly();                                                                     /* ����LU REQ                               */
                }
                else
                {
                    Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);

                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S17_E7:WARNING: Cause Abnormal");
            /* WUEPS_ASSERT(0); */                                                    /* �쳣������                             */
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttatchAccpt->enCause);
    }
    Mm_ComProcCauseClear();
    Mm_ComCheckDelayMmConn( MM_TRUE );
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E8
  Function: ��LOCATION UPDATING PENDING״̬��
            �յ�GMMMM_COMBINED_ATTACH_REJECTED�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.  s46746  2006.02.28  A32D03324
  3 . x51137  2006/4/14 A32D02955
  4.��    ��   : 2008��7��25��
    ��    ��   : luojian 00107747
    �޸�����   : �������ⵥ��AT2D04142/AT2D04677
  5.��    ��   : 2008��8��21��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
  6.��    ��   : 2008��9��3��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:At2D05403
  7.��    ��   : 2010��12��24��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�DTS2010121400435���������ע��ʧ�ܺ�ֻ������һ��CSע��
  8.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  9.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 10.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������
 11.��    ��   : 2011��11��15��
    ��    ��   : w00166186
    �޸�����   : DTS201111402055,����ģʽI�±�17��ԭ��ֵ�ܾ�5�κ�MM��ͣ�ķ���ע��
 12.��    ��   : 2012��02��23��
    ��    ��   : l65478
    �޸�����   : DTS2012021302593,GCF���ԣ�PSע��ʧ�ܺ����̷���CSע�ᵼ��PS��������û�з��ͳɹ�
 13.��    ��   : 2012��02��29��
    ��    ��   : l00130025
    �޸�����   : DTS2012022206186:������LAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
 14.��    ��   : 2012��3��1��
    ��    ��   : w00176964
    �޸�����   : DTS2012022407450:GMM��������ע��ʱ��֪ͨ��MM,MM��¼����
 15.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 16.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 17.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                ���з�װ��
 18.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E8(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_ATTACH_REJECTED_STRU        *pCombinedAttachRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucState;                           /* MM״̬                                   */

    if ( MM_FALSE == NAS_MM_RcvGmmCombinedAttachRej(pMsg) )
    {
        return;
    }

    pCombinedAttachRjct = (GMMMM_COMBINED_ATTACH_REJECTED_STRU*)pMsg;

    /* ��ʾMM���ڽ�������ע�� */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pCombinedAttachRjct->enCause,pCombinedAttachRjct->ulAttachAttCounter);

    switch(pCombinedAttachRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);     /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NO_IMSI");

        Mm_ComToNoImsiHandle();                                                 /* ���ý�NO IMSI�Ĺ�������                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NO_IMSI");

        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() ) &&
                (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                if ( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause11(MM_ATTACH);                                         /* ����ԭ��ֵΪ#11�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause13(MM_ATTACH);                                         /* ����ԭ��ֵΪ#13�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* ��¼���̺�ԭ��ֵ                         */


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    default:

        if (pCombinedAttachRjct->ulAttachAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pCombinedAttachRjct->enCause);
        }

        else if ( pCombinedAttachRjct->ulAttachAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* ���÷���״̬                             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pCombinedAttachRjct->enCause);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                NAS_MM_UpdateEquPlmnInfo(pCombinedAttachRjct->enCause);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* ����MM��Ϣ                               */
                Mm_ComDelLai();                                                 /* ɾ��LAI                                  */
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
                NAS_MML_InitUeIdTmsiInvalid();
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
                }

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pCombinedAttachRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }


            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");

            /*PS����ʧ�ܺ�CS���Ե�������һ��λ�ø���A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                Mm_ComLuOnly();
            }
            else
            {
                /* G�£�GASͬʱ����CELL UPDATE��LU�����⣬GCF 44.2.1.2.8 FAIL, �˴����⴦��
                   �ӳ�1���ٷ��� LU ���̡� */
                /* ��ʱ״̬���䣬��Ϊ: LOCATION UPDATING PENDING */
                Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
            }
            return;
        }
        else
        {
            ucState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            g_MmGlobalInfo.ucPreState = ucState;                 /* ��¼ǰ״̬                               */
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}


/*******************************************************************************
  Module:   Mm_Cell_S17_E11
  Function: ��LOCATION UPDATING PENDING״̬��
            �յ�GMMMM_GPRS_DETACH_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.��    ��   : 2008��9��3��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,MMע��״̬�޸�
      3.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E11(VOS_VOID *pMsg)
{
    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E13
  Function: ��LOCATION UPDATING PENDING״̬���յ�GMMMM_NETWORK_DETACH_IND�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.��    ��   : 2008��9��3��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,MMע��״̬�޸�
      3.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
      4.��    ��   : 2015��3��20��
        ��    ��   : w00167002
        �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                     ���з�װ��
      5.��    ��   : 2015��6��29��
        ��    ��   : z00161729
        �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_NOATTACH == pstNetWkDetachInd->enDetachType )
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* ����Net Detach�Ĵ���                     */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* ����������Bģʽ��ȫ����                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm��tbf�ͷź󲻻�����ϵͳ��Ϣ����Ҫ����MM_TIMER_DELAY_LU_GSM��ʱ����lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* ����Net Detach�Ĵ���                     */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm��tbf�ͷź󲻻�����ϵͳ��Ϣ����Ҫ����MM_TIMER_DELAY_LU_GSM��ʱ����lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }

            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
    else
    {

    }
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E15
  Function: ��LOCATION UPDATING PENDING״̬���յ�GMMMM_LU_INITIATION�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.  ��־��     2005.01.27  007005 for MM
      3.��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
      4.��    ��   : 2012��3��31��
        ��    ��   : z00161729
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if ( MM_FALSE == Mm_RcvGmmLuIni(pMsg) )
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pMsg;

    if ( GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* ����LU����ΪNORMAL                       */
    }
    else
    {
        if (((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus() )
           && (VOS_FALSE == ucPsRestrictionFlg)
           && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
          || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
        {                                                                       /* �������״̬ΪU1�ĳ���                   */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* ����LU����Ϊ����                         */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* ����LU����ΪNORMAL                       */
        }
    }
    Mm_ComLuOnly();                                                             /* ����LU����                               */
}


/*******************************************************************************
  Module:   Mm_Cell_S17_E18
            �յ�GMMMM_COMBINED_RAU_ACCEPTED�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
   1.  ��־��     2003.12.10  �°�����
   2.  s46746  2006-02-28  A32D03324

   3.��    ��   : 2006��4��10��
     ��    ��   : liuyang id:48197
     �޸�����   : ���ⵥ�ţ�A32D02352
   4.��    ��   : 2007��9��21��
     ��    ��   : luojian id:107747
     �޸�����   : ���ⵥ�ţ�AT2D01703
   5.��    ��   : 2007��10��23��
     ��    ��   : l39007
     �޸�����   : ���ⵥ�ţ�A32D13044
   6.��    ��   : 2007��11��12��
     ��    ��   : l39007
     �޸�����   : �������ⵥA32D13044,ATTACHʧ��5��,֪ͨMM����һ��LAU,
                  �����ʱMM�Ѿ�ע��,�򲻷���
   7.��    ��   : 2007��12��27��
     ��    ��   : l39007
     �޸�����   : �������ⵥA32D13044,GPRS only Attached(#16),���С��5�Σ�
                  MM״̬�ָ�ǰ״̬���������5�Σ���CS��û��ע�ᣬ����һ��LAU
   8.��    ��   : 2008��7��25��
     ��    ��   : luojian 00107747
     �޸�����   : �������ⵥ��AT2D04142/AT2D04677
   9.��    ��   : 2009��8��18��
     ��    ��   : ŷ���� 00132663
     �޸�����   : AT2D13774,���������������з�����ϵͳ��ѡ��W->G,NMOII->NMOI��LAI�ı䣬
                  ����RAU�ɹ���δ���𻺴��CSҵ��
  10.��    ��   : 2010��9��30��
     ��    ��   : ŷ���� 00132663
     �޸�����   : �������ⵥ��DTS2010092902368,TMSIֻ�ڵ�ЧPLMN����Ч
  11.��    ��   : 2010��11��24��
     ��    ��   : ��ë 00166186
     �޸�����   : �������ⵥ��DTS2010112205253,RAU�ɹ��ķ�֧�����LAU������
  12.��    ��   : 2010��12��21��
     ��    ��   : ŷ���� 00132663
     �޸�����   : �������ⵥ��DTS2010121602598,PS ONLY������CS SMSҵ�񣬴���GMM����ע�ᣬע��ɹ���
                  δ���𻺴��SMSҵ��
  13. ��    ��   : 2011��01��7��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��:DTS2011010403819,����ģʽI���յ������ϵͳ��Ϣ�����Loci�ļ�д������
                     ����̬���֧��location status event��������ϱ�ϵͳ��ϢҲ���򿨷��ʹ��¼�
  14.��    ��   : 2011��7��25��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  15.��    ��   : 2011��11��26��
     ��    ��   : w00167002
     �޸�����   : DTS2011111605875:����ģʽI,�ڱ�����ע��ʱ,����PS�ɹ���CS����
                   #16,��ʱ�յ�SUSPEND_IND,���Ǩ�Ƶ���ǰ������״̬������MMģ�鲻��
                   MMCģ��ظ�SUSPEND_RSP��
  16.��    ��   : 2012��1��18��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�DTS2012011601544,����ģʽI ����ע���PS�ɹ�,�������к�CSָʾ��������
  17.��    ��   : 2012��3��1��
     ��    ��   : w00176964
     �޸�����   : DTS2012022407450:GMM��������ע��ʱ��֪ͨ��MM,MM��¼����
  18.��    ��   : 2012��3��16��
     ��    ��   : s46746
     �޸�����   : DTS2012030603347:GSM��,GMM��������ע��,��PS�ɹ�,5�δ���CSע��,CS����ע��ʧ��,
                  �����ָ�GPRSʧ�ܵ����ֽ�������RAU,�γ�ע��ѭ��
  19.��    ��   : 2012��03��17��
     ��    ��   : s46746
     �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
  20.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  21.��    ��   : 2013��07��5��
     ��    ��   : w00176964
     �޸�����   : DTS2013062503351:LAU�ɹ�ʱ���µ�ǰ��RAC��Ϣ
  22.��    ��   : 2013��7��4��
     ��    ��   : w00167002
     �޸�����   : SVLTE_bbit:W�£�II,��46002��ע��ɹ�,�û�ָ����24005�ϣ�I,PS/CSע��ʧ��
                 ԭ��Ϊ����ʧ��(7)=>
                 1.�յ�ϵͳ��Ϣ��PSע��״̬Ǩ�Ƶ���5(��ΪGMM��MMC�ϱ���ע��ɹ�)��
                    -->GMM֪ͨMMCע��״̬ʧ�ܣ�CAUSE401;
                 2. MMC����������(��Ϊ��ON PLMN״̬��GMM��MMC�ϱ�401ԭ�򣬸�MM�ϱ�
                 ԭ��410��MM��MMC֪ͨ410�󣬴���������)��
                    -->MM�յ�GMM��ǰ����ԭ��410ʱ��ת����401ԭ��֪ͨMMC;
                 3.�����ɹ�����ԭС���յ�ϵͳ��Ϣ��MMC�ظ���������(GMM֪ͨMM��ǰ
                   PS��ǰע��ɹ���CSԭ��16������MM��MMC�ϱ�16ԭ��ֵ������ѭ������)��
                   -->GMM��ATTEMPT TO UPDATE״̬��֪ͨMM����ԭ��410��

  23.��    ��   : 2013��7��20��
     ��    ��   : w00167002
     �޸�����   : DTS2013071900098:MM״̬Ǩ�Ʋ���ȷ��
  24.��    ��   : 2014��4��2��
     ��    ��   : w00176964
     �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E18(VOS_VOID *pMsg)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    VOS_UINT32                              ulCsServExist;
    NAS_MML_LAI_STRU                       *pstCsSuccLai        = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_ACCEPTED_STRU       *pstCombinedRauAccpt = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    if ( MM_FALSE == Mm_RcvGmmCombinedRauAccepted(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pstCombinedRauAccpt = (GMMMM_COMBINED_RAU_ACCEPTED_STRU*)pMsg;

    if ( GMMMM_RAU_RESULT_COMBINED == pstCombinedRauAccpt->enRauResult )
    {
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* ����������Bģʽ��ȫ����                  */
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* ͣT3211                                  */
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);                           /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NORMAL_SERVICE");
        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        /* ��¼ע��ɹ���RAC����������ģʽ�ı�,�Ƚ�RAI�Ƿ����ı� */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* ��������ģʽ�ı�,RAI���ı�ʱ,MMû�и�������ģʽ,��GMMģ����ܻ�
           �������Ϲ��̣�Ϊ��֤����������GMMһ�£��˴���Ҫ��������ģʽ */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);              /* ���ø���״̬                             */
        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        /* ==>AT2D01703 */
        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if ( GMMMM_MS_ID_TYPE_IMSI == pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                        ~MM_MS_ID_TMSI_PRESENT; /* ����TMSI��Ч                             */
                NAS_MML_InitUeIdTmsiInvalid();
            }
            else if ( GMMMM_MS_ID_TYPE_TMSI ==
                                pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                        MM_MS_ID_TMSI_PRESENT;
                PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                           pstCombinedRauAccpt->stMsIdentity.aucTmsi,
                           NAS_MML_MAX_TMSI_LEN);

                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            }
            else
            {

            }
        }
        /* <==AT2D01703 */
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }
        }
        else
        {
            NAS_MM_NotifyAsInfoChgReq();
        }

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /*LAU ���������� */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        /* ��ʾMM���ڽ�������ע�� */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pstCombinedRauAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauAccpt->enCause);   /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* ���÷���״̬                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NO_IMSI");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* ���ý�NO IMSI�Ĺ�������                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:


            /* �˴�Э��δ��ȷ����������������������´���
               ע��ʧ�ܴ���С��5������LAI�����ҵ�ǰMM��״̬ΪUPDATED,�����Ϊ
               NORMAL SERVICE,����ǰ״̬ΪMM_IDLE_ATTEMPTING_TO_UPDATE��
               �ο�Э��24008:4.7.5.2.6 */
            if ( (pstCombinedRauAccpt->ulRauAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
              || (GMMMM_REAL_PROCEDURE != pstCombinedRauAccpt->enRealProFlg))
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* ���LAI����,����״̬ΪU1�ĳ��� */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬ */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;  /* ���÷���״̬ */

                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬ */

                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                }
            }

            else if ((NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
                  || (MM_FALSE == g_MmGlobalInfo.ucLikeB))
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
                    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
                     && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                     && (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* ����LU����                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                    }
                }
                else
                {

                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                }
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* G�£�GASͬʱ����CELL UPDATE��LU�����⣬GCF 44.2.3.2.3-2 FAIL, �˴����⴦��
                       �ӳ�1���ٷ��� LU ���̡� */
                    /* ��ʱ״̬���䣬��Ϊ: LOCATION UPDATING PENDING */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
            }
            else
            {
                NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

                g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            }
            break;


        /* GMM�յ�ϵͳ��Ϣʱ��֪ͨMM�ļ�����ԭ��ֵ�����ᴥ��MMC�������� */
        case NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;

        default:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(pstCombinedRauAccpt->enRealProFlg,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauAccpt->enCause);
    }
    Mm_ComProcCauseClear();

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Mm_ComCheckDelayMmConn( MM_TRUE );
        Mm_ComCheckDelayDetach();
    }
    else
    {
        /* G�£����յ�GMM ����RAU�ɹ���Ϣ�󣬲������Ϸ��𻺴��CSҵ����Ϊ��ʱGMM��RAU���̻�δ��ȫ����,
           ���ܻ���RAU COMPLETE��Ϣ��Ҫ�ظ�������TLLI ָ�ɵȵȣ������ʱ���Ϸ���MM�Ľ�������GAS���ܹ���
           GMM������RAU���̲�����������
           Ŀǰ�Ľ������������1�붨ʱ�����ӳٷ���CSҵ�� */
        ulCsServExist = Mm_ComJudgeCsServExist();

        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState) && (MM_CS_SERV_NONE_EXIST != ulCsServExist))
        {
            Mm_TimerStart(MM_TIMER_DELAY_CS_SERVICE_GSM);
        }
        else
        {
            Mm_ComCheckDelayMmConn( MM_TRUE );
            Mm_ComCheckDelayDetach();
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E19
  Function: ��LOCATION UPDATING PENDING״̬��
            �յ�GMMMM_COMBINED_RAU_REJECTED�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.  s46746  2006.02.28  A32D03324
  3. ��    ��   : 2008��07��22��
     ��    ��   : luojian id:107747
     �޸�����   : �������ⵥ�ţ�AT2D04163
  4. ��    ��   : 2008��7��25��
     ��    ��   : luojian 00107747
     �޸�����   : �������ⵥ��AT2D04142/AT2D04677
  5. ��    ��   : 2008��9��3��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,MMע��״̬�޸�
  6. ��    ��   : 2010��11��24��
     ��    ��   : ��ë 00166186
     �޸�����   : �������ⵥ��DTS2010112205253,NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED
                  ��֧����Ҫ����ר�����
  7.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  8.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  9.��    ��   : 2011��7��26��
    ��    ��   : l00130025
    �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
 10.��    ��   : 2011��11��15��
    ��    ��   : w00166186
    �޸�����   : DTS201111402055,����ģʽI�±�17��ԭ��ֵ�ܾ�5�κ�MM��ͣ�ķ���ע��
 11.��    ��   : 2012��3��1��
    ��    ��   : w00176964
    �޸�����   : DTS2012022407450:GMM��������ע��ʱ��֪ͨ��MM,MM��¼����
 12.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 13.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

 14.��    ��   : 2013��7��4��
    ��    ��   : w00167002
    �޸�����   : SVLTE_bbit:W�£�II,��46002��ע��ɹ�,�û�ָ����24005�ϣ�I,PS/CSע��ʧ��
                 ԭ��Ϊ����ʧ��(7)=>
                 1.�յ�ϵͳ��Ϣ��PSע��״̬Ǩ�Ƶ���5(��ΪGMM��MMC�ϱ���ע��ɹ�)��
                    -->GMM֪ͨMMCע��״̬ʧ�ܣ�CAUSE401;
                 2. MMC����������(��Ϊ��ON PLMN״̬��GMM��MMC�ϱ�401ԭ�򣬸�MM�ϱ�
                 ԭ��410��MM��MMC֪ͨ410�󣬴���������)��
                    -->MM�յ�GMM��ǰ����ԭ��410ʱ��ת����401ԭ��֪ͨMMC;
                 3.�����ɹ�����ԭС���յ�ϵͳ��Ϣ��MMC�ظ���������(GMM֪ͨMM��ǰ
                   PS��ǰע��ɹ���CSԭ��16������MM��MMC�ϱ�16ԭ��ֵ������ѭ������)��
                   -->GMM��ATTEMPT TO UPDATE״̬��֪ͨMM����ԭ��410��
 15.��    ��   : 2013��7��19��
    ��    ��   : w00167002
    �޸�����   : DTS2013071900239:W������ģʽI,����ע��PS only�ɹ���CSʧ��ԭ��
                  #17,����ģʽ��I--->II,��ʱ��Ӧ��������ATTACH.
                  �����ʱ��Ȼ������ģʽI,���û�����ΪPS ONLY,��Ҳ���÷���
                  ����ATTACH.
 16.��    ��   : 2013��7��20��
    ��    ��   : w00167002
    �޸�����   : DTS2013071900098:MM״̬Ǩ�Ʋ���ȷ��

 17.��    ��   : 2014��5��12��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
 18.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
 19.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
 20.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E19(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_RAU_REJECTED_STRU           *pstCombinedRauRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;


    if ( MM_FALSE == Mm_RcvGmmCombinedRauRejected(pMsg) )
    {
        return;
    }

    pstCombinedRauRjct = (GMMMM_COMBINED_RAU_REJECTED_STRU*)pMsg;

    /* ��ʾMM���ڽ�������ע�� */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pstCombinedRauRjct->enCause,pstCombinedRauRjct->ulRauAttCounter);

    switch(pstCombinedRauRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);            /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NO_IMSI");


        Mm_ComToNoImsiHandle();                                                 /* ���ý�NO IMSI�Ĺ�������                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* ����������Bģʽ��ȫ����                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* ����LU����                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* ���÷���״̬                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* ��MMC����MMCMM_LU_RESULT_IND             */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                    /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* ���÷���״̬                             */


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_LIMITED_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* ����MM��Ϣ                               */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause11(MM_RAU);                                            /* ����ԭ��ֵΪ#11�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        Mm_ComRejectCause13(MM_RAU);                                            /* ����ԭ��ֵΪ#13�Ĵ���                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* ��¼���̺�ԭ��ֵ                         */
        break;
    default:
        if (pstCombinedRauRjct->ulRauAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pstCombinedRauRjct->enCause);
        }
        if ( pstCombinedRauRjct->ulRauAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, begin */
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-12, end */
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* ���LAI����,����״̬ΪU1�ĳ���           */
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);/* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* ���÷���״̬                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                MM_STATUS_ATTACHED,
                                NAS_MML_GetSimCsSecurityCksn()
                                );                                              /* ����MM��Ϣ                               */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);    /* ��¼���̺�ԭ��ֵ                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* ���÷���״̬                             */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* ����MM��Ϣ                               */

                Mm_ComDelLai();                                                 /* ɾ��LAI                                  */

                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
                NAS_MML_InitUeIdTmsiInvalid();
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
                }
                else
                {
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                    Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
                }


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstCombinedRauRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauRjct->enCause);    /* ��¼���̺�ԭ��ֵ                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* ���÷���״̬                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* ����MM��Ϣ                               */
            Mm_ComDelLai();                                                     /* ɾ��LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
            NAS_MML_InitUeIdTmsiInvalid();

            if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* ����SIM������״̬                        */
            }
            else
            {
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* ����SIM������״̬                        */
            }


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE");

            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            /*PS����ʧ�ܺ�CS���Ե�������һ��λ�ø���A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstCombinedRauRjct->enCause);
            return;
        }
        else
        {
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
        }
        break;
    }


    /* ֪ͨMM��״̬Ϊ401�� */
    if ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES == pstCombinedRauRjct->enCause )
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauRjct->enCause);
    }

    NAS_MM_UpdateEquPlmnInfo(pstCombinedRauRjct->enCause);

    g_MmGlobalInfo.ucProc    = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );

    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;

    Mm_ComCheckDelayDetach();
}


/*******************************************************************************
  Module:   Mm_Cell_S18_E5
  Function: ��IMSI DETACH PENDING״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��     2003.12.11  �°�����
  2.��    ��   : 2011��7��16��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2011��12��23��
    ��    ��   : w00167002
    �޸�����   : DTS2011111901055:�������ϱ�ԭ��ֵ��NAS_MML_REG_FAIL_CAUSE_NULL
                  �޸�ΪNAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                  �޸�ԭ��:��ON PLMN״̬���յ��˼�������Ϣ����ԭ��ֵС��
                  NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE������ܷ���������
  5. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
   6.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
   7.��    ��   : 2014��04��1��
     ��    ��   : w00176964
     �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
 *******************************************************************************/

VOS_VOID Mm_Cell_S18_E5(VOS_VOID *pMsg)
{
    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
    {
        /* ��״̬������ģʽ�仯����Lu��ֱ�����ϲ�ظ�Detach�ɹ� */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;                     /* ��������ģʽ                             */
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                          /* ���÷���״̬                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S18_E5:INFO: MmServiceState is MM_DETACHED");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* ����MM��Ϣ                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E5:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }


    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);
    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S18_E10
  Function: ��IMSI DETACH PENDING״̬���յ�GMMMM_IMSI_DETACH_COMPLETED�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.  s46746  2005-11-14  �޸�
  3.  s46746  2006-05-24  �������ⵥA32D03784�޸�
  4. ��    ��   : 2007��01��12��
     ��    ��   : luojian id:60022475
     �޸�����   : ���ⵥ�ţ�A32D08357
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/

VOS_VOID Mm_Cell_S18_E10(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmImsiDetechComplete(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }


    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E10:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
}

/*******************************************************************************
  Module:   Mm_Cell_S18_E12
  Function: ��IMSI DETACH PENDING״̬���յ�GMMMM_GPRS_DETACH_COMPLETED�Ĵ���
  Input:    VOS_VOID*  pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.  s46746  2005-11-14  �޸�
  3.  s46746  2006-05-24  �������ⵥA32D03784�޸�
  4. ��    ��   : 2008��9��3��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05487,MMע��״̬�޸�
  5.��    ��   : 2011��7��26��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��MM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S18_E12(VOS_VOID *pMsg)
{

    if (MM_FALSE == Mm_RcvGmmGprsDetechCmpl(pMsg))
    {
        return;
    }

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* ͣT3218                                  */
    Mm_ComDelRandRes();                                                         /* ɾ��RAND��RES                            */
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {                                                                           /* �ػ��ĳ���                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);

        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_STATE_NULL");
    }
    else
    {
        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
            /* ����ȴ���־ */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

}

/*******************************************************************************
  Module:   Mm_Cell_S9_E48
  Function: WAIT FOR OUTGOING MM CONNECTION״̬���յ�
            AGENT_USIM_AUTHENTICATION_CNF�Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��   2003.12.12   �°�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��  : 2013��11��30��
    ��    ��  : l65478
    �޸�����  : DTS2013121919477,�����յ������������Ȩ��Ϣ,����ѵ�һ����Ϣ����Ӧ��Ϊ�ڶ����������Ӧ,���¼�Ȩʧ��
  4.��    ��  : 2013��7��22��
    ��    ��  : y00245242
    �޸�����  : VoIP�����������µ�USIM�ӿ�
  5.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E48(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    USIMM_AUTHENTICATION_CNF_STRU     *pstUsimAuthCnf = VOS_NULL_PTR;

    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;

    /* ��ǰ���ڵȴ�����Ϣ,���� */
    NAS_MM_LogAuthInfo((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara), g_MmGlobalInfo.AuthenCtrlInfo.ucOpId);

    if ((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara) != g_MmGlobalInfo.AuthenCtrlInfo.ucOpId)
    {
        return;
    }

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, begin */
    if ((USIMM_3G_AUTH != pstUsimAuthCnf->enAuthType )
     && (USIMM_2G_AUTH != pstUsimAuthCnf->enAuthType ))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E48:ERROR: authentication type is not expected!");

        return;
    }
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, end */

    /* SIM �� || USIM ������Ȩ�����в����� AUTN */
    if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        || (MM_IE_AUTN_PRESENT != g_MmMsgAuthReq.ucAutnFlg))
    {
        MM_RcvSimAuthCnf(pMsg);
        return;

    }

    if (MM_TRUE == Mm_RcvAgntUsimAuthenticationCnf(pMsg))
    {                                                                           /* ���ճɹ�                                 */
        Mm_ComAuthenRcvUsimCnf();                                               /* ���ü�Ȩ������������ */
    }
    else
    {                                                                           /* ����ʧ��                                 */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E55
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3214_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E55(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* ����T3214����T3216����Ĵ���             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E55:INFO: RECEIVE MM T3214 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E56
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3216_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E56(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* ����T3214����T3216����Ĵ���             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E56:INFO: RECEIVE MM T3216 EXPIRED");
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E57
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3218_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E57(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_ComT3218Expired();                                                       /* T3218����Ĵ���                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E57:INFO: RECEIVE MM T3218 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E59
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�T3230_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E59(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_T3230Expire();                                                           /* T3230����Ĵ���                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E59:INFO: RECEIVE MM T3230 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E60
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬��
             �յ�T3240_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E60(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    Mm_T3240Expire();                                                           /* T3230����Ĵ���                          */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S0_E61
  FUNCTION : ��MM_NULL״̬���յ�TIMER_PROTECT_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.  ��־��       2004.05.20  MM_IT_BUG_027��Ӧ
     3.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

}
/*******************************************************************************
  MODULE   : Mm_Cell_S1_E61
  FUNCTION : ��MM IDLE NO CELL AVAILABLE״̬���յ�TIMER_PROTECT_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
     3.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E61
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��
             �յ�TIMER_PROTECT_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
     3.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E61
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR REEST REQ)״̬��
             �յ�TIMER_PROTECT_EXPIRED�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-22  �°�����
     2.
     3.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E61(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
}

/*******************************************************************************
  MODULE   : NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬���յ�setup��Ϣ������л���
  INPUT    : VOS_UINT8 *pucCMMsg
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.����      15-6-15    �°�����

*******************************************************************************/
VOS_VOID NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(VOS_UINT8 *pucCMMsg)
{
    if (MM_CC_MSG_SETUP == (pucCMMsg[MM_CC_MSG_TYPE_POS] & 0x3f))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E50
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      03-12-12    �°�����

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е����Ӵ���״̬
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  5.��    ��   :2015��6��15��
    ��    ��   :b00269685
    �޸�����   :��������´������л���

*******************************************************************************/
VOS_VOID Mm_Cell_S11_E50(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8            ucTI = 0;                                              /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU  *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;            /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8           *pucCMMsg = VOS_NULL_PTR;                               /* ָ������ת��                             */
    VOS_UINT8           *pucBakCMMsg = VOS_NULL_PTR;

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if(VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S11_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */

    PS_MEM_SET(pucCMMsg, 0,
        sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);                /* ��ʼ���ڴ�                               */

    PS_MEM_CPY (pucCMMsg, &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
        pRrDataInd->RcvNasMsg.ulNasMsgSize);                                    /* �õ���Ϣ����                             */

    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                           /* �õ�CC��Ϣ�е�TI                         */

    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI)))
    {                                                                           /* TIO = 111                                */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* ��CC����MMCC_EST_IND                     */
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /*lint -e701*/
    if ((MM_CONST_NUM_7 > ucTI))
    {                                                                           /* ���ཨ����MM����                         */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );    /* ��CC����MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
            (VOS_UINT8)(0x01 << ucTI);                                          /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

    }
    else if (((MM_CONST_NUM_7 < ucTI) && (MM_CONST_NUM_15 > ucTI))
        && (MMC_MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {                                                                           /* CC������MM����                           */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);     /* ��CC����MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
            (VOS_UINT8)(0x01 << (ucTI - 8));                                    /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {

    }

    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S14_E40
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_DATA_IND(CM SERVICE ACCEPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-01-06  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E40(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* ѭ����������                             */
    /*lint -e701*/
    Mm_TimerStop(MM_TIMER_T3230);                                               /* ͣTIMER3230                              */
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* �ؽ���MM����                             */
        if (MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & (0x01 << i)))
        {                                                                       /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS);                           /* ֪ͨCC,MM�������ڽ�                      */
        }
        if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << i)))
        {                                                                       /* ��TI��MM�������ڵȴ��ؽ�                 */
            Mm_SndCcReestCnf((i + 8), MMCC_REEST_SUCCESS);                      /* ֪ͨCC,MM�������ڽ�                      */
        }
    }
    /*lint +e701*/
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E40:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* ����Ƿ��б�������Ҫ������MM����         */

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* ����eCall��ʱ��������ʶ */
    NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S0_E3
  Function: MM_NULL ״̬,�յ� MMCMM_PLMN_SEARCH_INITIATED
            ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��    2004.02.11   �°�����
      2.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E3(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S3_E65
  FUNCTION : ��MM IDLE NORMAL SERVICE״̬���յ�MMSS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      04-03-08  �°�����
  2.��־��        2005.01.27  007037 for MM
  3.��    ��   : 2009��05��25��
    ��    ��   : l65478
    �޸�����   : ���ⵥ:AT2D10870,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  6. ��    ��   : 2012��2��14��
     ��    ��   : z00161729
     �޸�����   : V7R1C50 ֧��CSFB�����޸�
  7. ��    ��   : 2012��2��15��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ����
   8.��    ��   : 2012��12��11��
     ��    ��   : w00176964
     �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
   9.��    ��   :2013��9��12��
     ��    ��   :z00161729
     �޸�����   :DTS2013082903019:֧��ss�ط�����
  10.��    ��   :2014��9��24��
     ��    ��   :s00217060
     �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E65(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                                  /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if (MM_FALSE == Mm_RcvSsEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
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
        /* �����ǰΪL��ģ��ֱ�ӻظ�ssʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

        if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
            || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
        {
            /* TI���Ϸ� */

            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* ���CM SERVICE REQUEST�ṹ��             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* ���CM SERVICE REQUEST ��Ϣ              */
            if (VOS_NULL_PTR == pucCmSvcReq)
            {                                                                   /* ��Ϣ����ʧ��                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* ����                                     */
            }
            else
            {                                                                   /* ��Ϣ�����ɹ�                             */
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);                           /* ������Ϣ                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                   /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* ��¼���ڽ�����MM���ӵ�PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S4_E65
  FUNCTION : ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬���յ�MMSS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08  �°�����
     2.��    ��   : 2011��03��01��
       ��    ��   : A00165503
       �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                    ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
     3.��    ��   : 2011��10��27��
       ��    ��   : s46746
       �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     4.��    ��   : 2012��03��03��
       ��    ��   : s62952
       �޸�����   : BalongV300R002 Build�Ż���Ŀ:ʹ��NV�滻NAS_FEATURE_SUPPORT_H3G_REQ��
     5.��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
     6.��    ��   : 2012��12��11��
       ��    ��   : w00176964
       �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
     7.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     8.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
     9.��    ��   : 2016��2��19��
       ��    ��   : z00359541
       �޸�����   : DTS2016020301907:���ݲ�ͬMM��״̬���ж�֪ͨCM RELԭ��ֵ������Ӱ���ز�
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E65(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();
    enRelCause                            = NAS_MM_GetMmCmRelCause();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
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

            /* CS����Ч���򲻴�����ҵ�� */
            if (VOS_FALSE  == NAS_MML_GetSimCsRegStatus())
            {
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                return;
            }
            
            /* �����ǰPS ONLYʱ֧��CSҵ��NVδ�����SSʧ�� */
            if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg) )
            {
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E65: PS ONLY mode and NV 9056 not active under L mode, Could not make SS call");
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
                
                return;
            }
            
            /* ��LIMIT SRVICE״̬�ſ�SSҵ���CSFB���� */
            if (MM_IDLE_LIMITED_SERVICE == Mm_GetState())
            {
                NAS_MM_RcvSsEstReq_CSFB();

                return;
            }            

            
            /* LTE��UE��null��no imsi��wait for attach״̬�޷�����ssҵ�� */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }


        
#endif
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if ((NAS_MML_MS_MODE_PS_ONLY  == NAS_MML_GetMsMode())
         && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E65: PS ONLY mode and NV 9056 not active, Could not make SS call");
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*״̬��Ϊlimited service���߷�����ΪPS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_Cell_S4_E65: MM Substate ", g_MmGlobalInfo.ucState);
                /* UE��null��no imsi״̬�޷�����ssҵ�� */
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi, enRelCause);
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                /*����÷������󲢽���CSע��*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_TRUE;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                    = g_MmSsEstReq.ulTi;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
                    = 0;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
                    = 0;
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();
                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
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

        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E65
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08  �°�����
     2.  ��    ��   : 2011��05��11��
         ��    ��   : f00179208
         �޸�����   : DTS2011042504198:��CS�򷢶���ʧ�ܺ�����SMS��MM�ӿڼ������⣬�޷���PS���ط�����
     3. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     4.��    ��   : 2012��12��11��
       ��    ��   : w00176964
       �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
     5.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     6.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E65(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU          CmSvcReq;                                   /* CM service request�ṹ��                 */
    VOS_UINT8                       ucRst;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
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
        /*lint -e701*/
        ucRst = Mm_ComJudgeLimitSvc();
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI���Ϸ����������޷���״̬               */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &
            ( 0x01 << ( g_MmSsEstReq.ulTi - 8 ) ) ) )
        {                                                                       /* Ҫ������MM�����Ѿ�����                 */
            Mm_SndSsEstCnf( g_MmSsEstReq.ulTi, MMSS_EST_SUCCESS );              /* ֪ͨSS��MM���ӽ����ɹ�                   */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* ���CM SERVICE REQUEST�ṹ��             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* �����෢�ͽ���MM���ӵ�����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;                                           /* ��¼�ؽ�MM���ӵ�TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                       /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* ��¼���ڽ�����MM���ӵ�PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E65:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E65
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬���յ�MMSS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      04-03-08    �°�����
  2.��    ��   : 2006��11��25��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D07666
  3.��    ��   : 2010��09��12��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�DTS2010090702204,Hplmn������,PS Service�������ź�SSҵ�������ж�����, ע��Rplmn,����ҵ��
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  6.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  7.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
  8.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  9.��    ��   :2014��2��22��
    ��    ��   :y00245242
    �޸�����   :dts201412901179:CC��SSҵ������ͬʱ����ʱ����������ݴ���
 10.��    ��   :2014��3��23��
    ��    ��   :y00245242
    �޸�����   :��dts201412901179������Mm_IsMultiSrvCollisionAllow��ͳһ����
 11.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E65(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E65:WARNING: MMSS_EST_REQ check fail.");
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
        /* �����ǰΪL��ģ��ֱ�ӻظ�ssʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        /* L����LOCATION_UPDATING_PENDING״̬�յ�ss����mm�軺�� */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
         && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                                       /* �Ѿ�����һ��������MM���ӽ�������         */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        /* ����ҵ���ͻ�Ƿ����� */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_SS))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);

            return;
        }

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();


    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S3_E62
  FUNCTION : ��MM IDLE NORMAL SERVICE״̬���յ�MMSMS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      04-03-08  �°�����
  2.��־��        2005.01.27  007037 for MM
  3.��    ��   : 2007��06��04��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D11456
  4.��    ��   : 2009��05��25��
    ��    ��   : l65478
    �޸�����   : ���ⵥ:AT2D10870,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
  5.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  8.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
  9.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
 10.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E62(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                  usMsgSize = 0;                                  /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */


    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            /* ֪ͨSMS����ʧ�� */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
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

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI���Ϸ�                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();


            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* ���CM SERVICE REQUEST�ṹ��             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* ���CM SERVICE REQUEST ��Ϣ              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                                   /* ��Ϣ����ʧ��                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* ����                                     */
            }
            else
            {                                                                   /* ��Ϣ�����ɹ�                             */
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );                                    /* ������Ϣ                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );               /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* ��¼���ڽ�����MM���ӵ�PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            /*A32D11456==>*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            /*<==A32D11456*/
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection
 ��������  : ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬���յ�MMSMS_EST_REQ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU                     CmSvcReq;                            /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                                 usMsgSize = 0;                        /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                                 *pucCmSvcReq = 0;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;

    enCsUpdateStatus                      = NAS_MML_GetCsUpdateStatus();

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

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
    if ((VOS_FALSE                               == NAS_MML_IsCsLaiChanged())
     || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED  != enCsUpdateStatus))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
        {
            NAS_MM_SndGmmRegisterInit();                                /* ֪ͨGMM����ע��                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                         /* LU REQ                                   */
        }
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq); /* ���CM SERVICE REQUEST�ṹ��             */

        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&CmSvcReq, &usMsgSize); /* ���CM SERVICE REQUEST ��Ϣ              */

        if (VOS_NULL_PTR == pucCmSvcReq)
        {                                                           /* ��Ϣ����ʧ��                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S4_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* ����                                     */
        }
        else
        {                                                           /* ��Ϣ�����ɹ�                             */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                            MM_FALSE,
                            usMsgSize, pucCmSvcReq );                                /* ������Ϣ                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);        /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = (VOS_UINT8)g_MmSmsEstReq.ulTi;                        /* ��¼���ڽ�����MM���ӵ�TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* ��¼���ڽ�����MM���ӵ�PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S4_E62
  FUNCTION : ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬���յ�MMSMS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      04-03-08  �°�����
  2.��    ��   : 2011��03��01��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                 ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  6.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:ʹ��NV�滻NAS_FEATURE_SUPPORT_H3G_REQ��
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  8.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
  9.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
 10.��    ��   : 2014��4��2��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
 11.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
 12.��    ��   : 2014��12��29��
    ��    ��   : z00161729
    �޸�����   : DSDSҵ���ز�ʱno rfδ������������ҵ��ʧ�ܣ�mm��no cell available״̬no rfʱ��mmc����cm service ind��������
 13.��    ��   : 2016��2��19��
    ��    ��   : z00359541
    �޸�����   : DTS2016020301907:���ݲ�ͬMM��״̬���ж�֪ͨCM RELԭ��ֵ������Ӱ���ز�
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E62(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU       *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    VOS_UINT8                                  ucSimCsRegStatus;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32             enRelCause;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();
    enRelCause                            = NAS_MM_GetMmCmRelCause();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            /* ֪ͨSMS����ʧ�� */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* ��MM_IDLE_NO_IMSI״̬ʱ�յ�����ҵ������ֱ�ӻظ�CS_SIM_INVALID,
           ����״̬һ�����յ�ϵͳ��Ϣ��δע��ʱ������,��ʱ�޷��ṩCS������Ҫ�ز� */
        if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState)
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* ֪ͨCC����ʧ��                           */

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
        /* ���no rf���Ȼ���ҵ������֪ͨmmc�������� */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState)
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SMS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
         && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E62: PS ONLY mode and NV 9056 not active, Could not start SMS service");
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*״̬��Ϊlimited service���߷�����ΪPS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                NAS_NORMAL_LOG1(WUEPS_PID_MM, "Mm_Cell_S4_E62: MM Substate ", g_MmGlobalInfo.ucState);
                /* UE��null��no imsi��WAIT FOR RR CONNECTION (IMSI DETACH)��IMSI DETACH INITIATED
                   ״̬�޷�����smsҵ�� */
                Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, enRelCause);
            }
            else
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;         /* ��¼�յ���������ʱ��״̬                 */

                if ((MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi)
                    || (MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi))
                {                                                                   /* TI���Ϸ�                                 */
                    Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                /* ֪ͨSMS����ʧ��                          */
                }
                else
                {
                    NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection();
                }
            }

        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    }


    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E62
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSMS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08  �°�����
     2.  ��    ��   : 2011��05��11��
         ��    ��   : f00179208
         �޸�����   : DTS2011042504198:��CS�򷢶���ʧ�ܺ�����SMS��MM�ӿڼ������⣬�޷���PS���ط�����
     3.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E62(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request�ṹ��                 */
    VOS_UINT8                           ucRst = MM_FALSE;
    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ucRst = Mm_ComJudgeLimitSvc(); */
        if (MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState)
        {                                                                       /* �����޷���                               */
            ucRst = MM_TRUE;                                                    /* ���������޷���                           */
        }

        if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
         && ((MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState)
          || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )))
        {
            ucRst = MM_TRUE;                                                 /* ���������޷���                           */
        }
        /*lint -e701*/
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI���Ϸ����������޷���״̬               */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
        }
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &
            (0x01 << (g_MmSmsEstReq.ulTi - 8))))
        {                                                                       /* Ҫ������MM�����Ѿ�����                 */
            Mm_SndSmsEstCnf( g_MmSmsEstReq.ulTi );                              /* ֪ͨSMS��MM���ӽ����ɹ�                  */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* ���CM SERVICE REQUEST�ṹ��             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* �����෢�ͽ���MM���ӵ�����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;                                           /* ��¼�ؽ�MM���ӵ�TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* ��¼���ڽ�����MM���ӵ�TI                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* ��¼���ڽ�����MM���ӵ�PD                 */
            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E62:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E62
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬���յ�MMSMS_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      04-03-08    �°�����
  2.��    ��   : 2006��11��25��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D07666
  3.��    ��   : 2010��09��12��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�DTS2010090702204,Hplmn������,PS Service�������ź�SSҵ�������ж�����, ע��Rplmn,����ҵ��
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  6.��    ��   : 2012��06��01��
    ��    ��   : f62575
    �޸�����   : DTS2012052904375��������������н��յ�SMS��EST_REQû�лظ�REL_IND����
  7.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
  8.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  9.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E62(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E62:WARNING: MMSMS_EST_REQ check fail.");
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            /* ֪ͨSMS����ʧ�� */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                                       /* �Ѿ�����һ��������MM���ӽ�������         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }

            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                                       /* �Ѿ�����һ��������MM���ӽ�������         */
            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }

    }


    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E68
  FUNCTION : ��PROCESS CM SERVICE PROMPT״̬���յ�MMCC_PROMPT_REJ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
     3.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E68(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */

    if ( MM_FALSE == Mm_RcvCcPromptRej( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
        Mm_TimerStop(MM_TIMER_T3240);
        MsgMmStatus.MmIeRjctCause.ucRejCause = (VOS_UINT8)(g_MmCcPromptRej.ulRefuseCause);
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼Ǩ��֮ǰ��״̬                       */
        if ( MM_FALSE == Mm_ComMmConnExist( ) )
        {                                                                       /* û�д��ڵ�MM���� */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                ucStaOfRcvXXEstReq;                                             /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {                                                                       /* �д��ڵ�MM���� */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            Mm_ComCheckDelayMmConn(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E47
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�
                RRMM_DATA_IND(CM SERVICE PROMPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E47(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */

    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* ͣT3212                                  */
    }
    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* ��䲢���� MM STATUS ��Ϣ                */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E47
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�
                RRMM_DATA_IND(CM SERVICE PROMPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
     4.  ��־��        2005.01.27  007037 for MM
     5.��    ��   : 2012��8��10��
       ��    ��   : L00171473
       �޸�����   : DTS2012082204471, TQE����
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E47(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS ��Ϣ�ṹ��                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));

    MM_Fill_IE_ClassMark2(aucClassmark2);

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
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E27
  FUNCTION : ��PROCESS CM SERVICE PROMPT״̬���յ�MMCC_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-08    �°�����
     6.  ��־��        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E27(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
           && ( MM_CONST_NUM_0 ==
           ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
           & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
        {                                                                       /* ����Ϣ�е�TIС��7�����ڲ���TIO !=111     */
        }
        else if(((MM_CONST_NUM_7  < pMmCcDataReq->ulTransactionId)
            &&(MM_CONST_NUM_15 > pMmCcDataReq->ulTransactionId))
            && (MM_CONST_NUM_0 ==
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << (pMmCcDataReq->ulTransactionId - 8)))))
        {                                                                       /* ����Ϣ�е�TI����7�����ڲ���TIO !=111     */
            Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) );   /* ���ø�TI����                             */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E27:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
        else
        {

        }
        Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                        &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                        RRC_NAS_MSG_PRIORTY_HIGH);                              /* ��CC����Ϣ������ȥ                       */

        /*lint +e701*/
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E69
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND( SS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E69(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                                                   /* ָ������ת��                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E69:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SS��Ϣ�е�TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSsDataInd (
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SS����MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SS����MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* �����Ѿ����ڵ�MM���ӵı�־λ             */

            /* BEGIN: Modified by ŷ����  ID: 00132663, 2008/8/26   PN:AT2D05263*/
            /* Ŀǰ������״̬����øú���
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                ��������״̬���ֲ��䡣*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
            /* END:   Modified by ŷ����  ID: 00132663, 2008/8/26 */
        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS������MM����                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSsDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SS����MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SS����MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* �ͷ��������Ϣ                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E70
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND( SMS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E70(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* SMS��Ϣ�е�TI                            */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                           /* ָ������ת��                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E70:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SMS��Ϣ�е�TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSmsDataInd(
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SMS����MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SMS����MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* �����Ѿ����ڵ�MM���ӵı�־λ             */

            /* BEGIN: Modified by ŷ����  ID: 00132663, 2008/8/26   PN:AT2D05263*/
            /* Ŀǰ������״̬����øú���
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                ��������״̬���ֲ��䡣*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
            /* END:   Modified by ŷ����  ID: 00132663, 2008/8/26 */
        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS������MM����                          */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndSmsDataInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��SMS����MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* �����Ӳ�����                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* ��SMS����MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E69
  FUNCTION : ��WAIT_FOR_NETWORK_COMMAND ״̬��
             �յ�RRMM_DATA_IND( SS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E69(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SS��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E69:WARNING: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    /*lint -e701*/
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SS��Ϣ�е�TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* ��SS����MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
        ( VOS_UINT8 )( 0x01 << ucTI );                                              /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );

    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS������MM����                           */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* ��SS����MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                                /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E70
  FUNCTION : ��WAIT_FOR_NETWORK_COMMAND ״̬��
             �յ�RRMM_DATA_IND( SMS Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E70(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SMS��Ϣ�е�TI                            */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* ָ������ת��                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* ͣTIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* �����ڴ�                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* �ڴ�����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E70:WARNING: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* ��ʼ���ڴ�                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* �õ���Ϣ����                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* �õ�SMS��Ϣ�е�TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* ���ཨ����MM����                         */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* ��SMS����MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
            ( VOS_UINT8 )( 0x01 << ucTI );                                          /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS������MM����                          */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* ��SMS����MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* �����Ѿ����ڵ�MM���ӵı�־λ             */
        /*lint +e701*/

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E67
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSS_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����
     2.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     3.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E67(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMSS_DATA_REQ_STRU      *pMmSsDataReq;
    pMmSsDataReq = ( MMSS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSsDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* ��TI��MM���Ӵ���                         */
            Mm_SndRrDataReq( pMmSsDataReq->SsMsg.ulSsMsgSize,
                &pMmSsDataReq->SsMsg.aucSsMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��SS����Ϣ������ȥ                       */
        }
        else
        {                                                                       /* ��TI��MM���Ӳ�����                       */
            Mm_SndSsRelInd( pMmSsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                               /* ֪ͨSS����ʧ��                           */
        }

        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E64
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSMS_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-11  �°�����
     2.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     3.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E64(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMSMS_DATA_REQ_STRU      *pMmSmsDataReq;
    pMmSmsDataReq = ( MMSMS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSmsDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSmsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSmsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* ��TI��MM���Ӵ���                         */
            Mm_SndRrDataReq( pMmSmsDataReq->SmsMsg.ulNasMsgSize,
                &pMmSmsDataReq->SmsMsg.aucNasMsg[0],
                RRC_NAS_MSG_PRIORTY_LOW);                                       /* ��SMS����Ϣ������ȥ                      */
        }
        else
        {                                                                       /* ��TI��MM���Ӳ�����                       */
            Mm_SndSmsRelInd(pMmSmsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* ֪ͨSMS����ʧ��                          */
        }

        /*lint +e701*/
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E25
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMCC_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-15  �°�����
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E25(
    VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
          && ( ( ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
              && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ulTransactionId
            == g_MmCcRelReq.ulTransactionId ) )
            || ( MMCC_RELEASE_ALL == g_MmCcRelReq.ulReleaseType ) ) )
        {                                                                       /* Ҫ���ͷŵ�MM�����Ǳ������       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;                                                     /* ���ò����ڻ����MM���� */
        }
        else
        {
            /* ���ֵ���ᱨ��ȥ����ΪCC�ڷ�MMCC_REL_REQʱ������ʱCC���CALL��MNCC_REL_IND,MNCC_REL_CNF,MNCC_REJ_IND
               ����Ǳ��У�setup���ʧ�ܣ�ring��û����ȥ��������CEND�ϱ� */
            Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ);/* ֪ͨCCָ���ͷŵ�MM���Ӳ�����             */
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();

     }

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S12_E25
 ��������  : ��WAIT FOR RR CONNECTION (MM CONNECTION)  �յ�cc rel req��Ϣ����
 �������  : pRcvMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   :2013��8��13��
    ��    ��  :z00161729
    �޸�����  :DTS2013081207431:mm����״̬�յ�cc��t303��ʱabort��Ϣ����Ҫ���棬�յ�resume indʱ�ٴ���
 2.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : DSDS ������
*****************************************************************************/
VOS_VOID Mm_Cell_S12_E25(VOS_VOID  *pRcvMsg)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcRelReq.ulTransactionId )
        {
            /* ��ֹ��MM���ӽ��������ڽ�����,������뼼����ͬ����rel req */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );

            /* ���MM���ȫ�ֱ��� */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI  = NO_MM_CONN_ESTING;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             && (g_MmCcRelReq.ulTransactionId ==
                     g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}



/*****************************************************************************
 �� �� ��  : Mm_Cell_S1_E63
 ��������  : ��MM IDLE NO CELL AVAILABLE״̬�յ�MMSMS_REL_REQ�Ĵ���
 �������  : VOS_VOID    *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S1_E63(VOS_VOID    *pRcvMsg)
{
    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*�������SMS����SS�Ļ��棬��Ҫ���*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S32_E63
 ��������  : ��MM_INTER_RAT_CHANGE״̬�յ�MMSMS_REL_REQ�Ĵ���
 �������  : VOS_VOID    *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S32_E63(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*�������SMS����SS�Ļ��棬��Ҫ���*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
        NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}





/*******************************************************************************
  MODULE   : Mm_Cell_S10_E63
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMSMS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      04-03-24  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E63(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                         /* ����ñ�־λ                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );                 /* ����ñ�־λ                             */
        }
        /*lint +e701*/
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
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E63
  FUNCTION : �� WAIT FOR RR CONNECTION (MM CONNECTION)״̬���յ�MMSMS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1. ��    ��   : 2007��03��24��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ�ţ�A32D09756
     2.��    ��   :2013��8��13��
       ��    ��   :z00161729
       �޸�����   :DTS2013081207431:mm����״̬�յ�cc��t303��ʱabort��Ϣ����Ҫ���棬�յ�resume indʱ�ٴ���
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E63(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E63:WARNING:  CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsRelReq.ulTi )
        {
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                /* ��ֹ��MM���ӽ��������ڽ�����             */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
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
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E63
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬���յ�MMSMS_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��    2005.03.28  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E63(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                     /* ����ñ�־λ                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TIС��7���Ҹ�MM���Ӵ���                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );             /* ����ñ�־λ                             */
        }
        /*lint +e701*/
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
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
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E63:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S3_E49
 ��������  : ����������״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S3_E49(
    VOS_VOID                           *pRcvMsg
)
{
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E49:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S11_E49
 ��������  : �ڵȴ������ͷ�״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��12��
   ��    ��   : w00242748
   �޸�����   : DTS2014021003925:en_NV_Item_User_Auto_Resel_Switch��NV��ʱ��CS��
                ��������PS��DEREGISTER LIMIT SERVICE״̬���·�AT+COPS=0����������
                ���������У�����δ���·���״̬�����������������У��·�AT+COPS?��ѯ
                �����Ϊ�������񡣵������������У�MMC�ѽ�CS/PSע��״̬���ó�δע��
                ��Ҫ������
 3.��    ��   : 2015��3��20��
   ��    ��   : w00167002
   �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                ���з�װ��

*****************************************************************************/
VOS_VOID Mm_Cell_S11_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

    if ( (MM_LU_PROC == g_MmGlobalInfo.ucProc)
      && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }

        Mm_ComProcCauseClear();
    }
    else if ( (MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc)
           && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        Mm_ComProcCauseClear();
    }
    else
    {
        Mm_ComProcCauseProcess();
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E49:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S9_E49
 ��������  : ��WAIT FOR OUTGOING MM CONNECTION�������յ�MM�������ͷ�����
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��06��23��
   ��    ��   : l65478
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S9_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E49:NORMAL: STATUS is WAIT FOR OUTGOING MM CONNECTION");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S10_E49
 ��������  : ��MM CONNECTION ACTIVE�������յ�MM�������ͷ�����
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��06��23��
   ��    ��   : l65478
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S10_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E49:NORMAL: STATUS is MM CONNECTION ACTIVE");

    return;
}


/*****************************************************************************
 �� �� ��  : Mm_Cell_S12_E49
 ��������  : ��WAIT FOR RR CONNECTION�������յ�MM�������ͷ�����
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��06��23��
   ��    ��   : l65478
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S12_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* ��RRC����RRMM_REL_REQ(CS��)              */

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E49:NORMAL: STATUS is WAIT FOR RR CONNECTION");

    return;
}


/*****************************************************************************
 �� �� ��  : Mm_Cell_S22_E49
 ��������  : �ڵȴ����ӽ���״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S22_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S23_E49
 ��������  : ��λ�ø������ڽ���״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��08��12��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 3.��    ��   : 2014��06��12��
   ��    ��   : s00217060
   �޸�����   : DTS2014061003286:TD2G��ѡ��G��RAU�����У��û�ָ����TD�����磬���粻��Ӧ����ҵ��accept
*****************************************************************************/
VOS_VOID Mm_Cell_S23_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3211);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);


    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_ClearAuthInfo();

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    /* ��Ϊ����LAUʧ�� */
    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* ����RAU attempt counter�Ĵ���            */

    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;


    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E49:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S24_E49
 ��������  : ��λ�ø��±���״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Mm_Cell_S24_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();
    Mm_ComProcCauseProcess();

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E49:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S25_E49
 ��������  : ��Detach�ȴ����ӽ���״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASE II ATTACH/DETACH����
 3.��    ��   : 2015��7��22��
   ��    ��   : z00161729
   �޸�����   : DTS2015060807763:apͨ��cgcatt�·�imsi detach������ʧ�ܺ�mm ����detach���ظ�detach cnfʱӦ�ô�limit service������normal service��at����ظ�ok������error
*****************************************************************************/
VOS_VOID Mm_Cell_S25_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    /* �жϵȴ���־�Ƿ���ڣ������������MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S26_E49
 ��������  : ����������״̬���յ�MMC���͵��ͷ�������
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���
 2.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

*****************************************************************************/
VOS_VOID Mm_Cell_S26_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* ��RRC����RRMM_REL_REQ(CS��) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3220);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

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

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E49:NORMAL: STATUS is IMSI_DETACH_INITIATED");

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E87
  FUNCTION : ��PROCESS CM SERVICE PROMPT״̬���յ�MMCC_START_CC�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.z40661      09-12-22    �°�����

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е�ҵ�����״̬
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E87(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU *pstMsg;
    VOS_UINT8                           ucTi;

    pstMsg = (MMCC_DATA_REQ_STRU *)pRcvMsg;

    ucTi = (VOS_UINT8)pstMsg->ulTransactionId;
    /*lint -e701*/
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]  =
    (VOS_UINT8)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
               | (0x01 << (ucTi - 0x08)) );
    /*lint +e701*/
    Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    Mm_SndRrDataReq(pstMsg->SendCcMsg.ulCcMsgSize,
                            &pstMsg->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);

    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_ComCheckDelayMmConn(VOS_FALSE);

    NAS_MM_UpdateCsServiceConnStatusFlg();
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S3_E88
 ��������  : ����������״̬���յ�MMC���͵�RRMM_W_AC_INFO_CHANGE_IND
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��2��15��
    ��    ��  : w00166186
    �޸�����  : CSFB&PPAC&ETWS&ISR ����

*****************************************************************************/
VOS_VOID Mm_Cell_S3_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* ��ǰС����Ϊע�����ޣ���ҪǨ��MM״̬ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        g_MmGlobalInfo.ucMmServiceState = NAS_MM_GetLauUptNeededCsSrvStatus();
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    }
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S6_E88
 ��������  : ��MM_IDLE_LIMITED_SERVICE���յ�MMC���͵�RRMM_W_AC_INFO_CHANGE_IND
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��2��15��
    ��    ��  : w00166186
    �޸�����  : CSFB&PPAC&ETWS&ISR ����
 2 .��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  3.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*****************************************************************************/
VOS_VOID Mm_Cell_S6_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* ��ǰС����CSע�����ޱ�Ϊ������ */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        /* �û����ò�֧��CS */
        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        /* ��ǰ�����ڽ�ֹ�б��� */
        if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* ���÷���״̬                             */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
        {
            /* ����PSע������ */
            if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            {                                                                   /* RACΪ0�ĳ���                             */
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            /* ����GPRS��֧�ֻ�GPRS��ֹ */
            else if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
             || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            {
                NAS_MM_SetLikeBFlg();
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            else
            {
            }
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeII();
        }
    }
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S9_E88
 ��������  : ����̬�յ�AC_INFO_CHANGE_IND�Ĵ���
 �������  : pRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1. ��    ��   : 2012��2��15��
    ��    ��  : w00166186
    �޸�����  : CSFB&PPAC&ETWS&ISR ����
 2. ��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��

*****************************************************************************/
VOS_VOID Mm_Cell_S9_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU            *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* �����ǰCSע���Ϊ���ޣ���Ҫ�������ý���ǰ״̬ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq       = MM_IDLE_LOCATION_UPDATE_NEEDED;
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd  = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* �����ǰCSע���Ϊ�����ޣ���Ҫ�������ý���ǰ״̬ */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-29, end */
    {
        /* ����ģʽI���ֻ�ģʽA��PSע������ޱ�Ϊ������ */
        if ((NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
         && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : Mm_Cell_S3_E89
 ��������  : ��MM IDLE NORMAL SERVICE ״̬���յ�L��T3412��ʱ����ʱ��Ϣ
 �������  : pRcvMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��3��5��
    ��    ��  : z00161729
    �޸�����  : V7R1 C50 ISR�����޸�
 2.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
 3.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID Mm_Cell_S3_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    /* ����ģʽI�£����GMM�Ѿ�ע��������ڽ���ע�ᣬ���账�� */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {
        if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
        {
            return;
        }
    }

    /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       - when the periodic tracking area update timer T3412 expires and the
       network operates in network operation mode II or III
    */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();

    return;

}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S5_E89
 ��������  : ��MM IDLE ATTEMPTING TO UPDATE ״̬�յ�L��T3412��ʱ����ʱ��Ϣ
 �������  : pRcvMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��3��5��
    ��    ��  : z00161729
    �޸�����  : V7R1 C50 ISR�����޸�
 2.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
 3.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID Mm_Cell_S5_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008��4.4.1  Location updating procedure�½��������£�
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();
    return;
}

#endif

/*****************************************************************************
 �� �� ��  : Mm_Cell_S1_E65
 ��������  : ��mm no cell available ״̬�յ�ss��������Ĵ���
 �������  : pRcvMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 2.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
 3.��    ��   : 2014��12��29��
   ��    ��   : z00161729
   �޸�����   : DSDSҵ���ز�ʱno rfδ������������ҵ��ʧ�ܣ�mm��no cell available״̬no rfʱ��mmc����cm service ind��������
*****************************************************************************/
VOS_VOID Mm_Cell_S1_E65(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucSimCsRegStatus;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* ��ǰС������ҵ�������򲻴��� */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* �����ǰפ��LTE,��ֱ�ӻظ�SSʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }
#endif
        /* �����ǰno rf����Ҫ����ҵ������֪ͨmmc�������� */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S25_E65
 ��������  : mm��wait for rr connection(imsi detach)��imsi detach initiated״̬�յ�ss��������Ĵ���
 �������  : pRcvMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 2.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S25_E65(VOS_VOID  *pRcvMsg)
{

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
