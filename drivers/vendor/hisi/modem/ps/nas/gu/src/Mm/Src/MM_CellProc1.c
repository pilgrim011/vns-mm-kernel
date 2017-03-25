/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_CellProc.c
  Description  : MM״̬Ǩ�Ʊ��ӦCELL����
  Function List:
History:
      1.  s46746    2006-04-14  �������ⵥA32D03088�޸�
      2.  s46746    2006-04-17  �������ⵥA32D02829�޸�
      3.  s46746  2006-06-24  �������ⵥA32D04439�޸�
      4.  s46746  2006-07-25  �������ⵥA32D05058�޸�
      5. s46746  2006-07-27 �������ⵥA32D03975�޸�
      6. ��    ��   : 2006��10��8��
         ��    ��   : luojian id:60022475
         �޸�����   : OSA�Ż���������©��A32D05845���ⵥ���޸�,�ֲ���
                      ���ⵥ��:A32D06583
      7.��    ��   : 2006��10��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D05960
      8.x51137 2006/11/3 A32D06511
      8.x51137 2006/11/3 A32D06821
      9.��    ��   : 2006��11��25��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D07666
     10.��    ��   : 2007��03��09��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥA32D09099�޸�
     11.��    ��   : 2007��04��20��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D10235
     12.��    ��   : 2007��07��31��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D12629,�ڴ��ڼ���ܷ���Ƶ���ض��壬
                     ʱ��Ϊ50�룬������Ӷ�ʱ������
     13.��    ��   : 2007��09��05��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�AT2D01490,MM�յ�ϵͳ��Ϣ��Ҫ�ж�LAI�Ƿ�
                     �����ı��������Ƿ�ͣT3211
     14.��    ��   : 2007��9��29��
        ��    ��   : luojian id:107747
        �޸�����   : �������ⵥ�ţ�A32D12966,���Ӳ���״̬��RRMM_REL_IND�Ĵ���
     15.��    ��   : 2007��10��06��
        ��    ��   : l65478
        �޸�����   : �������ⵥ�ţ�A32D12977
     16.��    ��   : 2007��11��20��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�A32D13510,������״ָ̬ʾ�����P/TMSI
     17.��    ��   : 2007��12��11��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�A32D13845,����������MMC����������ϵͳ��ͬPLMN
                     ����
     18.��    ��   : 2007��12��29��
        ��    ��   : l0010747
        �޸�����   : ���ⵥ��:A32D13958,����״̬�¶�RRMM_REL_IND�����޸�
     19.��    ��   : 2008��5��27��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D03209,�����б�����ʱ��ӦѰ������
     20.��    ��   : 2008��8��20��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:AT2D05154,�����ؽ�������λ�����ı䣬����֪ͨGMM���Ӳ�����
     21.��    ��   : 2008��8��21��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ��:AT2D04652,��С���ı�ʱ��ֹͣ��ʱ�� T3211
     22.��    ��   : 2008��8��22��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ��:AT2D05087,���Ӻ��� Mm_Cell_S4_E31
     23.��    ��   : 2008��8��23��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
     24.��    ��   : 2008��8��25��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ��:AT2D05268,�ں��� Mm_Cell_S14_E32�У�ɾ������MMCC_REEST_CNF(ESTING)����ش���
     25.��    ��   : 2008��8��26��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ��:AT2D05317,MM���ӹ�����ǿ
     26.��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mm״̬�޸�
     27.��    ��   : 2008��10��08��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ�ţ�AT2D06064,����ֻ��Ѿ�������detach,��ô��ʹ�յ���IMSI Paging��Ҳ����ӦѰ����
     28.��    ��   : 2008��11��22��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ�ţ�AT2D06931, �����־λucT3212ExpiredFlg
     29.��    ��   : 2008��12��1��
        ��    ��   : o00132663
        �޸�����   : AT2D07041, ���û������LIST����������HPLMN����ʱ��CREG,CGREG��ͣ�ϱ���
     30.��    ��   : 2009��02��28��
        ��    ��   : o00132663
        �޸�����   : AT2D09507, �ڶ���ʱ��CREG,CGREG�ϱ�2:û��ע�ᣬ��MT������ѰҪע����µ���Ӫ�̡�
     31.��    ��   : 2009��04��29��
        ��    ��   : x00115505
        �޸�����   : AT2D11365,2G��MM�����������ӱ�����ʱ���ĳ��ȹ�������190s�޸�Ϊ15s��
     32.��    ��   : 2009��05��11��
        ��    ��   : h44270
        �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
     33.��    ��   : 2009��07��24��
        ��    ��   : z40661
        �޸�����   : ��ϵͳ��ѡ�󣬽������в��ܽ�ͨ
     34.��    ��   : 2009��07��31��
        ��    ��   : x00115505
        �޸�����   : AT2D13428,2G������ע���ȥע��PS��֮�����������У�����ظ�Cm Service Reject��#4��������ʧ�ܡ�
     35.��    ��   : 2009��9��7��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�AT2D14311������������GMM��������ʱ�Ƚ����������ͷţ��ᵼ�·���״̬��ʱ����ΪNormal service
     36.��    ��   : 2009��09��28��
        ��    ��   : x00115505
        �޸�����   : ���õ����֧��PS�򣬷���CS���ź���ղ���
     37.��    ��   : 2009��11��26��
        ��    ��   : x00115505
        �޸�����   : ���÷�����ΪPS ONLY��Ⱥ�����ţ�����һ���ɹ�
     38.��    ��   : 2010��04��21��
        ��    ��   : x00115505
        �޸�����   : ���ⵥ��:AT2D17739,�����ض�������������Ҫ��һ��
     39.��    ��   : 2010��11��30��
        ��    ��   : h44270
        �޸�����   : ���ⵥ�ţ�DTS2010112905048/DTS201011270072,CS��IMSI��Чʱ��û����MMC�ظ���Ϣ�յ���Ϣ
*******************************************************************************/
#include        "MM_Inc.h"
#include        "NasCommDef.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"

#include        "NasMmSndOm.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-10, begin */
#include        "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-10, end */
#include        "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC1_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MM_StoreCsUnavailableInfo
 ��������  : CS�򲻿�����Ϣ�洢
 �������  : VOS_UINT8   ucCause            RAU��LAU������ܾ���ԭ��ֵ
 �������  : NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
                                            CS�򲻿�����Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_StoreCsUnavailableInfo(
    VOS_UINT16                          usCause,
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
)
{
    VOS_UINT32                          ulPos;

    /* �¼���¼��־����һ: ���Դ��������� */
    if (NAS_MNTN_CS_ATTEMPT_MAX == pstCsUnavailableInfo->ucTimes)
    {
        pstCsUnavailableInfo->bRecordRequired = VOS_TRUE;
    }

    /* �¼���¼��־���ö�: ע��ʧ��ԭ��ֵָʾ��ǰפ��λ�޷��ṩ������ѡ���ٳ���ע�� */
    NAS_MNTN_ServiceUnavailableType(usCause, &pstCsUnavailableInfo->bRecordRequired);

    /* �쳣����ֱ���˳�һ: ע��ʧ��ԭ��ֵû��ָʾ��ǰפ��λ�޷��ṩ����
       ��ע��ʧ�ܼ�����ֵΪ0 */
    if ((VOS_TRUE != pstCsUnavailableInfo->bRecordRequired)
     && (0 == g_MmGlobalInfo.LuInfo.ucLuAttmptCnt))
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StoreCsUnavailableInfo: Error Counter.");
        return;
    }

    /* �쳣����ֱ���˳���: ע��ʧ�ܼ�����ֵ�������ֵ */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt > NAS_MNTN_CS_ATTEMPT_MAX)
    {
        return;
    }

    /* ��¼ע��ʧ��ԭ��ֵ��ȫ�ֱ��� */
    if (0 != g_MmGlobalInfo.LuInfo.ucLuAttmptCnt)
    {
        ulPos = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt - 1;

    }
    else
    {
        ulPos = 0;
    }

    pstCsUnavailableInfo->aulCause[ulPos]= usCause;
    pstCsUnavailableInfo->ucTimes = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_RcvCcEstReq_CSFB
 ��������  : פ��L��CC MO CSFB�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 3.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 4.��    ��   : 2013��11��14��
   ��    ��   : z00161729
   �޸�����   : DTS2013111308141:cc csfb L���������У�mm��idle normal serviceδǨ��interrat change֮ǰ����ssҵ��ʧ��δ�����ط���ʱ����mm rel ind�ͷ�ԭ��ֵ��ӦΪother cause
 5.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : DSDS ������
 6.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log

*****************************************************************************/
VOS_VOID NAS_MM_RcvCcEstReq_CSFB(VOS_VOID)
{
    VOS_UINT32                          ulCsfbExistFlg;
    ulCsfbExistFlg = NAS_MML_IsCsfbServiceStatusExist();

    if ((MM_CONST_NUM_8  > g_MmCcEstReq.ulTransactionId)
     || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
     || (VOS_TRUE == ulCsfbExistFlg))
    {
        if (VOS_TRUE == ulCsfbExistFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);
        }
        else
        {
            /* ti�Ƿ����ظ�NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }

        /* Mm_RcvCcEstReq�����ж�����ǽ�����������ucEstingCallTypeFlg����Ҫ��� */
        if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg = MM_FALSE;
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        return;
    }

    /* ���潨������ */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

    /* ����CSFB״̬ */
    if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        /* ��¼CSFBҵ������ʼ */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_START);
    }
    else
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        /* ��¼CSFBҵ������ʼ */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START);
    }

    /* ��L����CSFB���̿�ʼ����,CSFB�Ƿ���Է�����ж���LMM���������������,
       L��ظ�LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MM_RcvSsEstReq_CSFB
 ��������  : פ��L��SS MO CSFB�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   :2013��9��14��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 3.��    ��   : 2013��11��14��
   ��    ��   : z00161729
   �޸�����   : DTS2013111308141:cc csfb L���������У�mm��idle normal serviceδǨ��interrat change֮ǰ����ssҵ��ʧ��δ�����ط���ʱ����mm rel ind�ͷ�ԭ��ֵ��ӦΪother cause
 4.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : DSDS ������
 5.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log

*****************************************************************************/
VOS_VOID NAS_MM_RcvSsEstReq_CSFB(VOS_VOID)
{
    /* �Ѿ���CSFB���̣�������������CSFB��������Ӧ���ظ�SS����ʧ�� */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);

        return;
    }

    if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
     || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
    {                                                                       /* TI���Ϸ� */
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

        return;
    }

    /* ���潨������ */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);

    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* ����CSFB״̬ */
    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* ��L����CSFB���̿�ʼ����,CSFB�Ƿ���Է�����ж���LMM���������������,
       L��ظ�LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_START);

    return;

}
#endif
/*******************************************************************************
  MODULE   : Mm_Cell_S3_E24
  FUNCTION : ��MM IDLE NORMAL SERVICE״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-09  �°�����
     2.  ��־��        2005.01.27  007037 for MM
     3.  ��    ��   : 2009��05��25��
         ��    ��   : l65478
         �޸�����   : ���ⵥ:AT2D10870,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
     4.  ��    ��   : 2011��10��27��
         ��    ��   : s46746
         �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     5.  ��    ��   : 2012��2��14��
         ��    ��   : z00161729
         �޸�����   : V7R1C50 ֧��CSFB�����޸�
     6.  ��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
     7. ��    ��    : 2012��10��29��
        ��    ��    : z00161729
        �޸�����    : DTS2012083102536:֧��cc�����ؽ�
     8. ��    ��    : 2012��12��11��
        ��    ��    : w00176964
        �޸�����    : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
     9 .��    ��   : 2012��12��21��
        ��    ��   : L00171473
        �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
    10.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
    11.��    ��   :2014��6��27��
       ��    ��   :s00217060
       �޸�����   :K3V3 ��ģ����������
    12.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
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

        /* �����ǰפ��LTE,��ֱ�ӻظ�CCʧ�� */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S3_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
        
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);      /* ֪ͨCC����ʧ��                           */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
    }

    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();
    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, end */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCcEstReq_IdleLimitedService
 ��������  : ��MM IDLE LIMITED SERVICE״̬���յ�MMCC_EST_REQ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��2��19��
    ��    ��   : z00359541
    �޸�����   : DTS2016020301907:���ݲ�ͬMM��״̬���ж�֪ͨCM RELԭ��ֵ������Ӱ���ز�
*****************************************************************************/
VOS_VOID NAS_MM_ProcCcEstReq_IdleLimitedService(VOS_VOID)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
    enRelCause              = NAS_MM_GetMmCmRelCause();

    if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCcEstReq_IdleLimitedService: CSFB MT exists, snd MM REL IND to CC to start redial proc");
    
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */
    
        return;
    }

    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {                                                                   /* �ǽ�������                               */
        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
    }
    else
    {                                                                   /* ���ǽ�������                             */
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
         && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCcEstReq_IdleLimitedService: PS ONLY mode and NV 9056 not active, Could not make CS call");
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);      /* ֪ͨCC����ʧ��                           */
        }
        else
        {
            /*״̬ΪNO IMSI���߷�����ΪPS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* no imsiʱ����ͨ���л�cs detach������ */
                NAS_NORMAL_LOG1(WUEPS_PID_MM, "NAS_MM_ProcCcEstReq_IdleLimitedService: MM Substate ", g_MmGlobalInfo.ucState);
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, enRelCause);                      /* ֪ͨCC����ʧ��                           */
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /*����÷������󲢽���CSע��*/
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
                {
                    NAS_MM_SndGmmRegisterInit();
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();
                }
            }

        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end*/

    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S4_E24
  FUNCTION : ��MM IDLE LIMITED SERVICE״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-09  �°�����
     2.  ��־��        2005.01.27  007037 for MM
     3.��    ��   : 2011��03��01��
       ��    ��   : A00165503
       �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                    ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����

     4.��    ��   : 2011��8��12��
       ��    ��   : zhoujun 40661
       �޸�����   : MMLģ�黮�֣�ȫ�ֱ�������
     5.��    ��   : 2011��10��27��
       ��    ��   : s46746
       �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     6.��    ��   : 2012��03��03��
      ��    ��   : s62952
      �޸�����   : BalongV300R002 Build�Ż���Ŀ:ʹ��NV�滻NAS_FEATURE_SUPPORT_H3G_REQ��
     7.��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
     8.��    ��   : 2012��8��14��
       ��    ��   : z00161729
       �޸�����   : DCM������������������޸�
     9.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
   10. ��    ��    : 2012��12��11��
       ��    ��    : w00176964
       �޸�����    : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
   11 .��    ��   : 2012��12��21��
       ��    ��   : L00171473
       �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
   12.��    ��   :2013��9��12��
      ��    ��   :z00161729
      �޸�����  :DTS2013082903019:֧��ss�ط�����
   13.��    ��   :2014��9��24��
      ��    ��   :s00217060
      �޸�����   :for cs_err_log

   14.��    ��   : 2015��8��27��
      ��    ��   : w00167002
      �޸�����   : DTS2015082401001:�ſ�LIMIT SERVICE�����µ�MO CALL�������GU������
                   �ɹ�������������к�ͨ�ʡ�
                   ��L��ע��ʧ�ܺ�L��֪ͨMMC��ǰע������̣�MM��Ǩ�Ƶ�LIMIT SERVICE.
                   ���ʱ����绰����ʵ���п��ܳɹ��ġ���LNAS��lihong��������ǰCSFB
                   �����Է���LNAS������LNAS���б��Ƿ����ִ�С�
                   ����L��#12��MM����LIMIT service,�������������GU��Ҳ�ǿ��ܳɹ��ġ�
   15.��    ��   : 2016��2��19��
      ��    ��   : z00359541
      �޸�����   : DTS2016020301907:���ݲ�ͬMM��״̬���ж�֪ͨCM RELԭ��ֵ������Ӱ���ز�
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;


    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
        {
           /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* ��MM_IDLE_NO_IMSI״̬ʱ�յ���ͨ��������ֱ�ӻظ�CS_SIM_INVALID,
           ����״̬һ�����յ�ϵͳ��Ϣ��δע��ʱ������,��ʱ�޷��ṩCS������Ҫ�ز� */
        if ( (VOS_FALSE           == NAS_MML_GetSimCsRegStatus())
          && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* ֪ͨCC����ʧ��                           */

            return;
        }

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

            /* �����ǰPS ONLYʱ֧��CSҵ��NVδ���������ʧ�� */
            if ( (NAS_MML_MS_MODE_PS_ONLY  == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
              && (MMCC_MO_NORMAL_CALL      == g_MmCcEstReq.ulCallType) )
            {
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S4_E24: PS ONLY mode and NV 9056 not active, Could not make CS call");
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);       /* ֪ͨCC����ʧ��                           */

                return;
            }

            NAS_MM_RcvCcEstReq_CSFB();

            return;
        }
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* ��¼�յ���������ʱ��״̬                 */

        /* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        /* Modified by z00161729 for DCM�����������������, 2012-8-20, end */
        {
            /* TI���Ϸ�                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);            /* ֪ͨCC����ʧ��                           */
        }
        else
        {
            NAS_MM_ProcCcEstReq_IdleLimitedService();
        }
    }

    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();
    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E24
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      03-12-09  �°�����
  2.��    ��   : 2007��10��06��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�A32D12977
  3.��    ��   : 2009��02��21��
    ��    ��   : l65478
    �޸�����   : AT2D09308,�����Ʒ����£�����ǽ������У�ֱ�Ӿܾ�
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  8.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  9.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
  10.��    ��   : 2012��12��15��
    ��    ��   : l65478
    �޸�����   : DTS2012120508936:�ڷ����������ʱ��Ҫdisable LTE
 11.��    ��   : 2012��12��21��
    ��    ��   : L00171473
    �޸�����   : DTS2012122007141:L��ģʱ�յ���������ֱ����CC�ظ�ʧ��
 12.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
 13.��    ��   :2014��2��22��
    ��    ��   :y00245242
    �޸�����   :dts201412901179:CC��SSҵ������ͬʱ����ʱ����������ݴ���
 14.��    ��   :2014��3��23��
    ��    ��   :y00245242
    �޸�����   :dts2014031406746:����MT call���ڽ��������У��յ�MO call��ͻ����
                ����dts201412901179������Mm_IsMultiSrvCollisionAllow��ͳһ����
 15.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E24(
                        VOS_VOID            *pRcvMsg                           /* ������Ϣ��ͷ��ַ                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ��������Ҳ�������״̬����ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* �����ǰΪL��ģ��ֱ�ӻظ�CCʧ�� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* �����ǰפ��LTE,��ֱ�ӻظ�CCʧ�� */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE);                              /* ֪ͨCC����ʧ��                           */

            return;
        }
#endif

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-13, begin */

        /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-13, end */
        if(VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            if(MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
            {
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                          /* ֪ͨCC����ʧ��                           */

                return;
            }
        }

        if ((MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S9_E24: snd MM REL IND to CC in MM_IDLE_PLMN_SEARCH state");

            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);                          /* ֪ͨCC����ʧ��                           */
            return;
        }

        /* ����ҵ���ͻ�Ƿ����� */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S9_E24: Call collision, snd MM REL IND to CC to start redial proc");

            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S9_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
        
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */
        
            return;
        }

        /*����÷������� */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E24
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-09    �°�����
     2.  ��־��          2004.03.12  ���ڸ���
     3.  ��־��      04-03-22    MM_MT_����_BUG_003
     4.  ��    ��   : 2011��05��11��
         ��    ��   : f00179208
         �޸�����   : DTS2011042504198:��CS�򷢶���ʧ�ܺ�����SMS��MM�ӿڼ������⣬�޷���PS���ط�����
     5. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     6.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
    7.��    ��   : 2012��12��11��
      ��    ��   : w00176964
      �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
    8.��    ��   :2013��9��12��
      ��    ��   :z00161729
      �޸�����  :DTS2013082903019:֧��ss�ط�����
    9.��    ��   : 2014��5��28��
      ��    ��   : z00234330
      �޸�����   : covertity�޸�
   10.��    ��   :2014��9��24��
      ��    ��   :s00217060
      �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request�ṹ��                 */
    VOS_UINT8                           ucRst;

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    PS_MEM_SET(&CmSvcReq,0x00,sizeof(CmSvcReq));
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        ucRst = Mm_ComJudgeLimitSvc();
        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
            || (MM_TRUE == ucRst))
        {                                                                       /* TI���Ϸ����������޷���״̬               */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                   /* ֪ͨCC����ʧ��                           */
        }
        /*lint -e701*/
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] &
            (0x01 << (g_MmCcEstReq.ulTransactionId - 8))))
        /*lint +e701*/
        {                                                                       /* Ҫ������MM�����Ѿ�����                 */
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* ������������                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* ���CM SERVICE REQUEST�ṹ��             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_FALSE;                                                 /* ���ǽ�������                             */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
            }
            else if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* ���н�������                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* ���CM SERVICE REQUEST�ṹ��             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_TRUE;                                                  /* �ǽ�������                               */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
            }
            else
            {
            }
            Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* �����෢�ͽ���MM���ӵ�����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;                                           /* ��¼�ؽ�MM���ӵ�TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                (VOS_UINT8)g_MmCcEstReq.ulTransactionId;                        /* ��¼���ڽ�����MM����                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;            /* ��¼���ڽ�����MM���ӵ�PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E24:NORMAL: STATUS is  WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        /*lint +e701*/
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E24
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����
     2. ��    ��   : 2006��11��25��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D07666
     3. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     4. ��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     5 .��    ��   : 2012��12��11��
        ��    ��   : w00176964
        �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
     6.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     7.��    ��   :2014��3��23��
       ��    ��   :y00245242
       �޸�����   :dts2014031406746:����MT call���ڽ��������У��յ�MO call��ͻ����
     8.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E24:WARNING: MMCC_EST_REQ check fail.");;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            /* �Ѿ�����һ��������MM���ӽ�������         */
            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                             /* ֪ͨCC����ʧ��                           */
        }

        /* ����ҵ���ͻ�Ƿ����� */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S11_E24: Call collision, snd MM REL IND to CC to start redial proc");

            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S11_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
        
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                            NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);     /* ֪ͨCC����ʧ�� */
        
            return;
        }

        /* ������Ϣ */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
      }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S19_E24
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMCC_EST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746   2005-11-05
     2. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     3.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     4.��    ��   : 2012��12��11��
       ��    ��   : w00176964
       �޸�����   : �޸� NAS_MML_GetCsRestrictNormalServiceFlg������
     5.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     6.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S19_E24(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        MM_WARN_LOG(" \nMM:Recieve CC EST REQUEST ERROR!\r " );
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /* �ǽ���������ǰС������ҵ�������򲻴��� */
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* ֪ͨCC����ʧ��                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI���Ϸ�,֪ͨCC����ʧ�� */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI�Ϸ�                                   */
            if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* �ǽ�������                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* ��¼�յ���������ʱ��״̬                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                {
                    /* �Ѿ�����һ��������MM���ӽ�������,֪ͨCC����ʧ�� */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                if (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE))
                {
                    NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S19_E24: CSFB MT exists, snd MM REL IND to CC to start redial proc");
                
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
  MODULE   : Mm_Cell_S10_E25
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMCC_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����

     3.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
     3.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     4.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     5.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E25(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if (MM_FALSE == Mm_RcvCcRelReq(pRcvMsg))
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if (MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType)
        {                                                                       /* �ͷ�����Ϊ�ͷ�ָ����MM����               */
            /*lint -e701*/
            if ((MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId)
                && (MM_CONST_NUM_0 !=
               (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & (0x01 << g_MmCcRelReq.ulTransactionId))))
            {                                                                   /* �ͷ����ཨ����MM���Ӳ��Ҵ���             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & (~(VOS_UINT8)(0x01 << g_MmCcRelReq.ulTransactionId)));    /* ���MM���Ӵ��ڱ�־                       */
            }
            else if ((MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_0 != (g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & (0x01 << (g_MmCcRelReq.ulTransactionId - 8)))))
            {                                                                   /* �ͷ�CC������MM���Ӳ��Ҵ���               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & (~(VOS_UINT8)(0x01 <<
                    (g_MmCcRelReq.ulTransactionId - 8))));                      /* ���MM���Ӵ��ڱ�־                       */
            }
            else
            {
                /* ָ���ͷŵ�MM���Ӳ�����, ֪ͨCCָ���ͷŵ�MM���Ӳ����� */
                Mm_SndCcRelInd(g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
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
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* û��MM���Ӵ���                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                    ucStaOfRcvXXEstReq;                                         /* ������е�״̬                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
        else
        {                                                                       /* �ͷ�����Ϊ�ͷ����е�MM����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* �����ͷ����ཨ����MM����                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* �����ͷ�CC������MM����                   */
            if ( ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* û��MM���Ӵ���                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                          /* ������е�״̬                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E25
  FUNCTION : ��WAIT FOR REESTABLISH (WAIT FOR REEST REQ) ״̬��
             �յ�MMCC_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����
     2.  ��־��        2005.01.27  007037 for MM

     3.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�CS���ҵ�����״̬
     4.��    ��   : 2011��7��28��
       ��    ��   : w00167002
       �޸�����   : V7R1 PHASEII �ع�: PC_LINT�޸�
     5.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     6.��    ��   : 2013��9��12��
       ��    ��   : w00242748
       �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                    ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                    G��ԭС��ʱ��LAU
     7.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     8.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
     9.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
    10.��    ��   : 2015��3��20��
       ��    ��   : w00167002
       �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                    ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E25(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* �ͷ�����Ϊ�ͷ�ָ����MM����               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* �ͷ������ؽ���MM���Ӳ��Ҵ���             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* ���MM�����ؽ���־                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] & ( 0x01 <<
                ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* �ͷ�CC�ؽ���MM���Ӳ��Ҵ���               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[1] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* ���MM�����ؽ���־                       */
            }
            else
            {
                /* ָ���ͷŵ�MM���Ӳ�����                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCCָ���ͷŵ�MM���Ӳ�����             */
            }
            if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
                && (MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
            {                                                                   /* û�еȴ��ؽ���MM���Ӵ���                 */
                Mm_TimerStop(MM_TIMER_PROTECT_CC);                              /* ��������TIMER                            */
                if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
                    && ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ) )
                {                                                               /* ȫ���ͷţ�û��Ҫ���ؽ���MM����           */
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* ��¼Ǩ��֮ǰ��״̬                       */
                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                         || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                          && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)))
                        {
                            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        }


                    }
                }
                else
                {
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* ��¼Ǩ��֮ǰ��״̬                       */
                    Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
                    Mm_TimerStart(MM_TIMER_T3230);                              /* ��������TIMER                            */

                    MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                        = NAS_MML_GetCsLastSuccMcc();
                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                        = NAS_MML_GetCsLastSuccMnc();
                    MsgReEstReq.MmIeLai.IeLai.ulLac
                        = NAS_MML_GetCsLastSuccLac();
                    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

                    NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

                    Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
                }
            }
        }
        else
        {                                                                       /* �ͷ�����Ϊ�ͷ����е�MM����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                = 0;                                                            /* �����ͷ����ཨ����MM����                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                = 0;                                                            /* �����ͷ�CC������MM����                   */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ������е�״̬                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }

        /*lint +e701*/
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E25
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬��
             �յ�MMCC_REL_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10    �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е����Ӵ���״̬
     3.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     4.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     5.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E25(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/

        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* �ͷ�����Ϊ�ͷ�ָ����MM����               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* �ͷ����ཨ����MM���Ӳ��Ҵ���             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]=
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* ���MM���Ӵ��ڱ�־                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
               ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* �ͷ�CC������MM���Ӳ��Ҵ���               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* ���MM���Ӵ��ڱ�־                       */
            }
            else if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId == g_MmCcRelReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;                                                 /* ���ò����ڻ����MM���� */

            }
            else
            {
                /* ָ���ͷŵ�MM���Ӳ�����                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCCָ���ͷŵ�MM���Ӳ�����             */
            }
        }
        else
        {                                                                       /* �ͷ�����Ϊ�ͷ����е�MM����               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* �����ͷ����ཨ����MM����                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* �����ͷ�CC������MM����                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* ���ò����ڻ����MM����                   */
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();


        /*lint +e701*/
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S32_E26
 ��������  : ��MM_INTER_RAT_CHANGE״̬�յ�MMCC_ABORT_REQ�Ĵ���
 �������  : pRcvMsg - �յ���ԭ��ͷָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2012��2��15��
     ��    ��   : z00161729
     �޸�����   : �����ɺ���
   2.��    ��   : 2013��4��02��
     ��    ��   : y00176023
     �޸�����   : DSDS GUNAS II��Ŀ:����CSFB������abort��֪ͨĿ��RAT
   3.��    ��   : 2014��5��22��
     ��    ��   : z00161729
     �޸�����   : DTS2014050601476:L��绰�ض���g�����е绰�Ҷϣ�mm����cc abort��g��ѯcsfb״̬�Ǵ��ڣ�
                  lau������û����������FR���̵�L
   4.��    ��   :2014��9��24��
     ��    ��   :s00217060
     �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        /* ��Ϣ�����ʧ�� */
        ;
    }
    else
    {
        /* ��Ϣ������ɹ�*/
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            /* ����MMCC_ABORT_REQ��Ӧ����Ҫ��MM���ڽ��������ӱ�������
               ���MM���ڽ��������ӱ��û������������˵�LTEʱ��������ҵ���Ǵ��ڣ��ͻᴥ���ͷ�ҵ�������
            */
            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);


#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
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
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S2_E26
  FUNCTION : �� MM IDLE PLMN SEARCH,
                MM IDLE ATTEMPTING TO UPDATE,
                WAIT FOR OUTGOING MM CONNECTION,
                WAIT FOR NETWORK COMMAND,
                WAIT FOR RR CONNECTION (MM CONNECTION),
                WAIT FOR REESTABLISH(WAIT FOR REEST REQ),
                WAIT FOR REESTABLISH(WAIT FOR EST_CNF),
                WAIT FOR ADDITIONAL OUTGOING MM CONNECTION,
                LOCATION UPDATING PENDING,
                IMSI DETACH PENDING,
                WAIT FOR ATTACH,
                WAIT FOR RR CONNECTION (LOCATION UPDATING),
                LOCATION UPDATING INITIATED,
                LOCATION UPDATE REJECTED,
                WAIT FOR RR CONNECTION (IMSI DETACH),
                IMSI DETACH INITIATED
             ״̬���յ�MMCC_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��    ��   : 2007��03��09��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥA32D09099����
  2.��    ��   : 2007��10��06��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�A32D12977
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��2��15��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 ֧��CSFB�����޸�
  5.��    ��   : 2014��6��10��
    ��    ��   : w00242748
    �޸�����   : DTS2014061001560:L�����У�CSFB��NMOI W�£���LAU/RAU��LAU�����У�
                 �Ҷϵ绰������ʱ��������δ�ͷţ�MM��GMM����MMGMM_CS_CONNECT_NOT_EXIST��
                 ����GMM����·���ڵ������һֱ����RAU��
  6.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  7.��    ��   : 2014��9��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014092302846:L�²���绰������w�±�#12�ܾ���С�����绰ʧ�ܺ���ѡ��l��mm���cc�෢һ��mmcc rel ind
  8.��    ��   : 2016��2��2��
    ��    ��   : z00359541
    �޸�����   : DTS2016011809099:����Ҫ����CSFB ABORT��Ϣ���״̬����CSFB�绰�������յ�CALL STARTUS NOTIFY��Ϣʱ����
*******************************************************************************/
VOS_VOID Mm_Cell_S2_E26(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        ;
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }


            if ( VOS_FALSE == ucCsSigConnStatusFlg )
            {
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
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
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E26
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�MMCC_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����
     2.��    ��   : 2012��1��21��
       ��    ��   : s46746
       �޸�����   : ����MML_CTX�е�����ҵ��״̬
     3.��    ��   : 2012��1��30��
       ��    ��   : s46746
       �޸�����   : ҵ����������������ֹҵ��ʱ��Ҫ���CSҵ���־
     4.��    ��   : 2012��2��15��
       ��    ��   : z00161729
       �޸�����   : V7R1C50 ֧��CSFB�����޸�
     5.��    ��   : 2014��6��13��
       ��    ��   : w00242748
       �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E26(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ���ص����յ�����MM��������ʱ��״̬       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* ����TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
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

        NAS_MM_UpdateCsServiceConnStatusFlg();
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E26
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMCC_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��   05-02-01  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�����ҵ��״̬
     3.��    ��   : 2012��2��15��
       ��    ��   : z00161729
       �޸�����   : V7R1C50 ֧��CSFB�����޸�
     4.��    ��   : 2014��6��13��
       ��    ��   : w00242748
       �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E26(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    /*lint -e701*/
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
        .aucMMConnExtFlg[1]
            & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            if (((0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1])
                &&(0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[0]))
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* ���ص����յ�����MM��������ʱ��״̬       */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E26:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* ����TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM��������                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT8)(0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    /*lint +e701*/
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E26
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬���յ�MMCC_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��   05-02-01  �°�����

  2.��    ��   : 2007��10��06��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�A32D12977

  3.��    ��   : 2010��4��15��
    ��    ��   : o00132663
    �޸�����   : AT2D18449,MM δ������ȫ�ֱ���������CC�жϺ��к�MM��Ȼ��
                 ��ҵ��������
  4.��    ��   :2013��8��13��
    ��    ��   :z00161729
    �޸�����   :DTS2013081207431:mm����״̬�յ�cc��t303��ʱabort��Ϣ����Ҫ���棬�յ�resume indʱ�ٴ���
  5.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        return;
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcAbortReq.ulTransactionId )
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

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
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
             && (g_MmCcAbortReq.ulTransactionId ==
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
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E26
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬��
             �յ�MMCC_ABORT_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����
     2.��    ��   : 2012��2��15��
       ��    ��   : z00161729
       �޸�����   : V7R1C50 ֧��CSFB�����޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E26(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* ��ֹ��MM���ӽ��������ڽ�����             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣT3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* ������ڽ�����MM���ӵı�־               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E26:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
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
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E27
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�MMCC_DATA_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����
     2.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     3.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E27(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if ( ( MM_CONST_NUM_7 == pMmCcDataReq->ulTransactionId )
            || ( MM_CONST_NUM_15 == pMmCcDataReq->ulTransactionId ) )
        {                                                                       /* TIO ����111                              */
            Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��CC����Ϣ������ȥ                       */
        }
        else
        {                                                                       /* TIO ������111                            */
            /*lint -e701*/
            if ( ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0]
                & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
                || ( ( MM_CONST_NUM_7 < pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1]
                & ( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) ) ) ) ) )
            {                                                                   /* ��TI��MM���Ӵ���                         */
                Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* ��CC����Ϣ������ȥ                       */
            }
            else
            {
                /* ��TI��MM���Ӳ�����                       */
                Mm_SndCcRelInd(pMmCcDataReq->ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* ֪ͨCC����ʧ��                           */
            }

            /*lint +e701*/
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E28
  FUNCTION : ��WAIT FOR REESTABLISH ( WAIT FOR REEST REQ )״̬��
             �յ�MMCC_REEST_REQ�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-10  �°�����
     2.  ��־��        2005.01.27  007037 for MM
     3.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     4.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     5.��    ��   : 2014��4��2��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ�޸�:g_MmGlobalInfo.MsCsInfo.OldLai�滻��MML�е�
     6.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E28(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcReestReq(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmCcReestReq.ulTransactionId )
        {                                                                       /* �����ཨ����MM�����ؽ�                   */
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
            & ( 0x01 << g_MmCcReestReq.ulTransactionId ) ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] |
                    ( 0x01 << g_MmCcReestReq.ulTransactionId ) );               /* ���������ؽ���MM���ӵı�־               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnReestFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] &
                    (~(VOS_UINT8)( 0x01 << g_MmCcReestReq.ulTransactionId ) ) );    /* ��������ؽ���MM���ӵı�־               */
            }
            else
            {
                Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* ֪ͨCC�ؽ���ʧ��                         */
            }

        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
            & ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* ��CC������MM�����ؽ�                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] |
                ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) );           /* ���������ؽ���MM���ӵı�־               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] &
                (~(VOS_UINT8)( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) );/* ��������ؽ���MM���ӵı�־               */
        }
        else
        {
            /* Ҫ���ؽ���MM���Ӳ�����                   */
            Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                                  /* ֪ͨCC�ؽ���ʧ��                         */
        }
        /*lint +e701*/
        if ( ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
            && (MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
        {                                                                       /* û�еȴ��ؽ���MM���Ӵ���                 */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E28:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
            MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                = NAS_MML_GetCsLastSuccMcc();
            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                = NAS_MML_GetCsLastSuccMnc();
            MsgReEstReq.MmIeLai.IeLai.ulLac
                = NAS_MML_GetCsLastSuccLac();
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */

            NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

            Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S2_E31
  FUNCTION : ��MM IDLE PLMN SEARCH״̬���յ�RRMM_PAGING_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.s46746      08-05-02  �°�����
  2.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S2_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{

    if (MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "Mm_Cell_S2_E31:WARNING: Msg is invalid.");
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

    /* ֪ͨMMC CS����Ҫ������Ҫֹͣ���� */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO,
           "Mm_Cell_S2_E31:INFO: Rcv Paging in Plmn Search, Wait camping.");

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S3_E31
  FUNCTION : ��MM IDLE NORMAL SERVICE״̬���յ�RRMM_PAGING_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      03-12-10  �°�����
  6.��־��        2005.01.27  007037 for MM
  3.s46746     2005.09.27  modify for HSS 4100 V200R001
  4.s46746     2006.01.17  modify for A32D01587
  5.s46746     2006.02.28  modify for A32D03324
  6.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }

    CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();            /* �洢CKSN                                 */
    g_MmGlobalInfo.ucStaOfRcvXXEstReq
        = g_MmGlobalInfo.ucState;

    NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* ��ǰ���� GSM ���� */
    {
        /* �� GAS ���ͽ��� RR ���� */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS ���� */
    {
        Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* ��䲢���� PAGING RESPONSE ��Ϣ          */
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* ��������TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}
/*****************************************************************************
 �� �� ��  : Mm_Cell_S4_E31
 ��������  : MM IDLE LIMITED SERVICE״̬���յ�RRMM_PAGING_IND�Ĵ���
 �������  : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��8��19��
    ��    ��   : ŷ����  ID: 00132663
    �޸�����   : �����ɺ��� for AT2D05087
  2.��    ��   : 2008��10��08��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D06064,����ֻ��Ѿ�������detach,��ô��ʹ�յ���IMSI Paging��Ҳ����ӦѰ����
  3.��    ��   : 2011��03��01��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011021202242/DTS2011021400322����Ӻ꿪���ж�
                 ������ΪPS_ONLYʱ��CS����źͺ���ҵ���Ƿ��ܹ�����
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
*****************************************************************************/
VOS_VOID Mm_Cell_S4_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                        )
{
    MM_MSG_PAGING_RSP_STRU              CmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */



    enMsMode        = NAS_MML_GetMsMode();

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* 24.008��4.2.2.3��it may respond to paging (with IMSI).*/
    if (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
       && (VOS_TRUE == ucCsAttachAllow))
       || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
          &&(NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)))
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }
    
        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* �洢CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&CmRspRsp.MmIeMobileId.MobileID);

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* ��ǰ���� GSM ���� */
        {
            /* �� GAS ���ͽ��� RR ���� */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS ���� */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                 /* ��䲢���� PAGING RESPONSE ��Ϣ          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E31
  FUNCTION : ��MM IDLE ATTEMPTING TO UPDATE״̬���յ�RRMM_PAGING_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      03-12-10  �°�����
  2.��־��        2005.01.27  007037 for MM
  3.s46746     2005.09.08  modify for HSS 4100 V200R001
  4.s46746     2006.01.17  modify for A32D01587
  5.s46746     2006.01.17  modify for A32D03324
  6.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  7.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E31(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* �� IMEI Ѱ���Ĵ��� */
    if (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* �洢CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* ��ǰ���� GSM ���� */
        {
            /* �� GAS ���ͽ��� RR ���� */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS ���� */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* ��䲢���� PAGING RESPONSE ��Ϣ          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    }

    return;
}
/*****************************************************************************
 �� �� ��  : Mm_Cell_S6_E31
 ��������  : MM��MM_IDLE_LOCATION_UPDATE_NEEDED״̬�յ�Ѱ����Ϣ�Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
*****************************************************************************/
VOS_VOID Mm_Cell_S6_E31(
    VOS_VOID                           *pstRcvMsg
)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;                                       /* Ҫ���͵�PAGING RSP��Ϣ                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    enMsMode                = NAS_MML_GetMsMode();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    if (MM_FALSE == Mm_RcvRrcPagingInd(pstRcvMsg))
    {
        return;
    }

    /* ��ǰС��PAGING�����򲻴��� */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* MM_IDLE_LOCATION_UPDATE_NEEDED״̬�����ǰCS ע��״̬��Ӧ��ͨѰ����
       ����ֻ����Ӧ IMSI Ѱ�� */
    if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
     || (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
        && (VOS_TRUE == ucCsAttachAllow))
      || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
        && (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))))
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        stCmRspRsp.MmIeCksn.ucCksn            = NAS_MML_GetSimCsSecurityCksn(); /* �洢CKSN                                 */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq     = g_MmGlobalInfo.ucState;
        NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())            /* ��ǰ���� GSM ���� */
        {
            /* �� GAS ���ͽ��� RR ���� */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0,
                           VOS_NULL_PTR);
        }
        else /* UMTS ���� */
        {
            Mm_ComMsgPagingRspSnd(&stCmRspRsp);                                 /* ��䲢���� PAGING RESPONSE ��Ϣ          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* ��������TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E32
  FUNCTION : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��
             �յ�RRMM_EST_CNF�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  ��־��        2005.01.27  007037 for MM
     3.  ��    ��   : 2009��05��25��
         ��    ��   : l65478
         �޸�����   : ���ⵥ:AT2D10870,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
     4.  ��    ��   : 2010��01��08��
         ��    ��   : l65478
         �޸�����   : ���ⵥ:AT2D16252,���յ�RRMM_EST_CNFʱ���ѻ����SS����Ϣ����ˣ�����SSҵ���޷�����
     5.  ��    ��   : 2010��5��17��
         ��    ��   : o00132663
         �޸�����   : AT2D19083, ����������ظ�����ʧ�ܣ�����MM/WASֱ�ӽ���ƹ�Ҳ�
                      ������Ϣ���������
     6.  ��    ��   : 2013��6��8��
         ��    ��   : w00167002
         �޸�����   : V9R1_SVLTE:�յ������������������ɹ�������cs���DETACH.
                      ����ֱ�ӱ���DETACH;
     7.��    ��   : 2014��8��14��
       ��    ��   : z00161729
       �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau
     8.��    ��   :2015��3��13��
       ��    ��   :n00269697
       �޸�����   :CHR �Ż���Ŀ�����CS PAGING FAIL�쳣��¼
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E32(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    RRMM_EST_CNF_STRU       *pRrMmEstCnf;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */

        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);


        /* ����ǰ�����CS��ȥע�� */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        /* �ڽ���CS���н��������У���������ظ�����ʧ�ܣ�ԭ��ֵΪ: Conn_Fail��
             �Աȱ�ˣ����ֱ�˻����·���������ֱ��CC T303��ʱ���ж�Ϊֹ,
            ����������ߵ绰��ͨ�� */
        if (  (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
           && ((RRC_EST_EST_CONN_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_NOT_ALLOW == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_TIME_OUT == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_RA_RESOURCE_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL == pRrMmEstCnf->ulResult))
           && (MM_IE_PD_CALL_CONTROL == g_MmGlobalInfo.ucMMConnEstingPD))
        {
            g_MmGlobalInfo.ucCallRetryCount++;

            /* Ϊ�˷�ֹMM/GAS��������ƹ�Ҳ���������ϵͳ��Ϣ������������Ƴ��Դ��� */
            if (g_MmGlobalInfo.ucCallRetryCount < MM_CALL_RETRY_MAX_TIMES)
            {
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }
        }

#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_RecordCsPagingFail_WaitForRrConnection(pRrMmEstCnf->ulResult);
#endif

        /* �����Ϣ�����־               */
        NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

        /* ֻ�н��������RRC_EST_SUCCESS����RRC_EST_PRESENT������Ҫ����ҵ����ڱ�־ */

        NAS_MM_ProcEstCnfCauseAtState12(pRrMmEstCnf->ulResult);
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E32
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_EST_CNF�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  ��־��        2005.01.27  007037 for MM

     3.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е����Ӵ���״̬
     4.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�

     5.��    ��   : 2013��6��11��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE:����ǰ�����CS��ȥע��
     6.��    ��   : 2013��8��22��
       ��    ��   : w00167002
       �޸�����   : DTS2013081604476:w��ѡ��G�º󣬱�����ָ�ɾܾ���GAS����T3122
                    ��ʱ���������û�����绰��NAS����LAU,GAS����T3122���У�ֱ�ӻظ�
                    ����ʧ�ܡ�MM������T3211,�����ֳ����£�NAS����Ҫ����T3211��ʱ����
     7.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     8.��    ��   : 2013��4��10��
       ��    ��   : y00176023
       �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�RRC_EST_RJ_NO_RF�Ĵ���
     9.��    ��   : 2014��8��14��
       ��    ��   : z00161729
       �޸�����   : gas��lau����ʧ��ԭ��ֵrandom access reject no valid information����δ��Э��ʵ��8s�ڲ�����lau��t3213 4s��ʱ�ͷ�����lau
    10.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E32(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* ѭ����������                             */
    RRMM_EST_CNF_STRU       *pRrMmEstCnf;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;


        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);

        /* ����ǰ�����CS��ȥע�� */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */
        switch ( pRrMmEstCnf->ulResult)
        {
        case RRC_EST_SUCCESS:                                                   /* �������ӽ����ɹ�                         */
        case RRC_EST_PRESENT:                                                   /* �����������Ѿ�����                       */
            if ( RRC_EST_PRESENT == pRrMmEstCnf->ulResult )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION PRESENT !");
            }
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );

            Mm_TimerStart(MM_TIMER_T3230);                                      /* ����TIMER3230                            */
            g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
            break;
        /* case RRC_EST_DELING:  */                                                  /* ���������������ͷ�                       */
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:

        case RRC_EST_RJ_SNW:

        case RRC_EST_RJ_NO_RF:

        case RRC_EST_RJ_T3122_RUNNING:

        case RRC_EST_OTHER_ACCESS_BARRED:
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        /* RRC_EST_RJ_RA_FAIL�Ǵ�ԭ����RRC_EST_RANDOM_ACCESS_REJECT�ɲ�����ģ���RRC_EST_RANDOM_ACCESS_REJECT�Ĵ�����һ��
           RRC_EST_RJ_CELL_BAR �Ǵ�ԭ����RRC_EST_ACCESS_BARRED�в�����ģ���RRC_EST_ACCESS_BARRED�Ĵ�����һ�� */
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_CELL_BAR:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:
            /*lint -e701*/
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM�������ڵȴ��ؽ� */
                    Mm_SndCcRelInd(i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM�������ڵȴ��ؽ� */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);/* ֪ͨCC,MM�����ؽ�ʧ��                    */
                }
            }

            /*lint +e701*/

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E32:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
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

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                  NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);   /* ֪ͨCC����ʧ��                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
            }

            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: ulResult Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E33
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  s46746     05-09-24  modify for HSS 4100 V200R001
     3.��    ��   : 2012��9��07��
       ��    ��   : l00171473
       �޸�����   : DTS2012081701006, ���MM״̬�Ŀ�ά�ɲ���Ϣ
     4.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     5.��    ��   : 2013��6��6��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE:CSδע���£���ǰ��PSҵ�񣬽���������ͷţ���Ҫ����LAU��
                    2. �����ǰ�Ĵ���ע��Ļ��棬�ڽ����������յ�REL IND����ֱ��
                       ����ȥע�ᡣ
     6.��    ��   : 2013��8��28��
       ��    ��   : l65478
       �޸�����   : DTS2013082607368:����פ���ڽ�ֹ��������,CSҵ�����������LU
     7.��    ��   : 2013��9��12��
       ��    ��   : z00161729
       �޸�����   : DTS2013082903019:֧��ss�ط�����
     8.��    ��   : 2014��01��09��
       ��    ��   : l65478
       �޸�����   : DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
     9.��    ��   : 2014��04��03��
       ��    ��   : w00176964
       �޸�����   : V3R3C60_eCall��Ŀ����
    10.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
    11.��    ��   : 2015��1��28��
       ��    ��   : w00167002
       �޸�����   : DTS2015011400748:��G��RL FAILURE����FR,������������쳣���޸�Ϊ
                    G�ϱ�RRC_REL_CAUSE_G_RL_FAILԭ��ֵ������NAS�Ͳ�����CC �ؽ���
    12.��    ��   :2016��1��9��
       ��    ��   :z00359541
       �޸�����   :DTS2015111402223:����С���Ƿ�֧��CSMO��ʶ
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E33(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{

    RRMM_REL_IND_STRU                   *pRrmmRelInd;
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;
    VOS_UINT8                           ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                           ucRst;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S9_E33: Rcv RR REL IND, Set CellNotSupportCsmoFlg to TRUE");
        NAS_MML_SetCellNotSupportCsmoFlg(VOS_TRUE);

        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrmmRelInd->ulRelCause,
                    pRrmmRelInd->ulRrcConnStatus);

        if (VOS_TRUE == ucRst)
        {
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

            /* ���·���ǰMM CONNECTION�������� */
            NAS_MM_RetryMmConnectionProc(g_MmGlobalInfo.ucMMConnEstingPD);
            return;
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */

            /* �ͷŵ�ǰ���ڽ�����MM���ӵ�TI */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();

            /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* ����LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
                Mm_ComLuOnly();

                return ;
            }

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
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* ֪ͨCC����ʧ��                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_NotifyCcErrInd
 ��������  : MM֪ͨCC����ʧЧ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  3.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_NotifyCcErrInd(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause
)
{
    VOS_UINT8   i;

    i = 0;

    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* �ؽ���MM����                             */
        /*lint -e701*/
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndCcErrInd(i, enCause);                                         /* ֪ͨCC,MM����ʧЧ                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndCcErrInd(i + 8, enCause);                                              /* ֪ͨCC,MM����ʧЧ                        */
        }


        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSsRelInd(i, enCause);                                                  /* ֪ͨSS,MM����ʧЧ                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSsRelInd(i + 8, enCause);                                              /* ֪ͨSS,MM����ʧЧ                        */
        }

        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSmsRelInd(i, enCause);                 /* ֪ͨSS,MM����ʧЧ                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* ��TI��MM����ʧЧ                         */
            Mm_SndSmsRelInd((i + 8), enCause);          /* ֪ͨSS,MM����ʧЧ                        */
        }
        /*lint +e701*/

    }
}

/*****************************************************************************
 �� �� ��  : NAS_MM_HandleRelIndCause15AtS10
 ��������  : ��MM CONNECTION ACTIVE״̬���յ�RRMM_REL_IND��ԭ��ֵΪ15�Ĵ���
 �������  : VOS_UINT8    ucRrConnRelFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е����Ӵ���״̬
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_HandleRelIndCause15AtS10(VOS_UINT8    ucRrConnRelFlg)
{
    VOS_UINT8    ucTiValidFlg;

    ucTiValidFlg = MM_TRUE;

    NAS_MM_NotifyCcErrInd(NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];      /* ��¼��Ҫ�ؽ��ı�־                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];      /* ��¼��Ҫ�ؽ��ı�־                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */

    if ((MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
        || (MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]))
    {
        Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
        Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* ��������TIMER                            */
    }
    else
    {
        if (MM_TRUE == ucRrConnRelFlg)
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        Mm_ComProcCauseProcess();

        if ( MM_FALSE == Mm_ComChkLu() )
        {
            if ((MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
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

            Mm_ComCheckDelayDetach();
        }
        else
        {
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
            {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndCcRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* ֪ͨCC����ʧ��                           */
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSmsRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
            {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
            }
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E33
  FUNCTION : ��MM CONNECTION ACTIVE״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  ��־��        2005.01.27  007037 for MM
     3.  s46746    05-09-24  modify for HSS 4100 V200R001
     4.  s46746     2006.08.09  �������ⵥA32D05269�޸�
     5.  ��    ��   : 2009��05��25��
         ��    ��   : l65478
         �޸�����   : ���ⵥ:AT2D10870,��MM���ӽ��������з���LAI�ı�,û�з���LU,���º���ʧ��
     6.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�

  3.��    ��   : 2013��4��16��
    ��    ��   : z00234330
    �޸�����   : DTS2013041604521:CSFB��������,PS����·����,����ֱ���·�rel ind,mm δ����Lau

  4.��    ��   : 2013��6��6��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:CSδע���£���ǰ��PSҵ�񣬽������������ͷţ���Ҫ����LAU��
  5.��    ��   : 2013��8��28��
    ��    ��   : l65478
    �޸�����   : DTS2013082607368:����פ���ڽ�ֹ��������,CSҵ�����������LU
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��01��09��
    ��    ��   :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log

  9.��    ��   : 2015��1��28��
    ��    ��   : w00167002
    �޸�����   : DTS2015011400748:��G��RL FAILURE����FR,������������쳣���޸�Ϊ
                 G�ϱ�RRC_REL_CAUSE_G_RL_FAILԭ��ֵ������NAS�Ͳ�����CC �ؽ���
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E33(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        /* RRC_REL_CAUSEת��ΪMMCC_REL_CAUSE */
        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);

        if ((MM_TRUE == ucRrConnRelFlg)
         && (RRC_REL_CAUSE_RL_FAILURE != pRrmmRelInd->ulRelCause))
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
                NAS_MM_HandleRelIndCause15AtS10(ucRrConnRelFlg);
                break;

            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_ComRelAllMmConn(enMmCcRelCause);

                                                              /* �ͷ�����mm����                           */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();

                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);         /* RR���Ӳ�����                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                /* added by z00234330 for DTS2013041604521CSFB��������,PS����·����,����ֱ���·�rel ind,mm δ����Lau 2013-04-11 begin */


                /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
                if ( VOS_TRUE == ucEmergencyLauFlg )
                {
                    /* ����LAU */
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
                    Mm_ComLuOnly();

                    return ;
                }

                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                    Mm_ComCheckDelayMmConn( MM_FALSE );

                    Mm_ComCheckDelayDetach();
                }
                /* added by z00234330 for DTS2013041604521CSFB��������,PS����·����,����ֱ���·�rel ind,mm δ����Lau 2013-04-11 end */
                break;

            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E33
  FUNCTION : ��WAIT FOR NETWORK COMMAND״̬���յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  s46746     05-09-24  modify for HSS 4100 V200R001
     3.��    ��   : 2013��01��23��
       ��    ��   : s00217060
       �޸�����   : ���ⵥ: DTS2013012106172,�յ�RRMM_REL_INDʱ�������������־
     4.��    ��   : 2013��6��6��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE:CSδע���£���ǰ��PSҵ�񣬽������������ͷţ���Ҫ����LAU��

     4.��    ��   : 2013��7��27��
       ��    ��   : w00167002
       �޸�����   : DTS2013072604691:w��II,PS attachʧ��ԭ��11��csע��ɹ���
                     CS��/ps����ѭ��ע��.�޸�ΪCS������ѭ��ע�ᡣ

     6.��    ��   : 2013��8��28��
       ��    ��   : l65478
       �޸�����   : DTS2013082607368:����פ���ڽ�ֹ��������,CSҵ�����������LU
     7.��    ��   :2014��01��09��
       ��    ��   :l65478
       �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
    8.��    ��   : 2014��5��4��
      ��    ��   : z00161729
      �޸�����   : DTS2014042816166:l csfb ��w��rau��12�ܾ���lau�ɹ�û�����forbidden��Ϣ������fast return��l��csfb��w��ͬС���绰ʧ��
    9.��    ��   :2014��9��24��
      ��    ��   :s00217060
      �޸�����   :for cs_err_log
   10.��    ��   : 2015��01��16��
      ��    ��   : f00179208
      �޸�����   : DTS2015011311068:��Щ������û�н�CS��ķ���״̬���,����CHR�ظ���¼
   11.��    ��   : 2015��1��28��
      ��    ��   : w00167002
      �޸�����   : DTS2015011400748:��G��RL FAILURE����FR,������������쳣���޸�Ϊ
                   G�ϱ�RRC_REL_CAUSE_G_RL_FAILԭ��ֵ������NAS�Ͳ�����CC �ؽ���
   12.��    ��   : 2015��1��26��
      ��    ��   : z00161729
      �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E33(
    VOS_VOID                           *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
)
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT8                           ucCsServiceConnStatusFlg;
#endif

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

        }

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* MT�ĳ����ҷ�CSFB MT���¼�쳣 */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            /* �յ�CS PAGING�����ӽ����ɹ�������δ�յ�ҵ����Ϣ���յ��ײ��ͷ�ָʾ���쳣��¼ */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_RELEASED);
        }

        /* ��CSFB MT������ʱ����ʱ״̬���յ�REL IND�����CSFB��״̬��Ϣ */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_TimerStop( MM_TIMER_T3240 );
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

                /*����Э��4.7.5.1.4��ATTACH����RAU�ܾ�ԭ��ֵΪ15������LAU*/
                if (( (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal))
                 && (  (MM_GMM_RAU_PROC                       == g_MmGlobalInfo.ucProc)
                    || (MM_GMM_ATTACH_PROC                    == g_MmGlobalInfo.ucProc) )
                 && (MM_NORMAL_SERVICE                        == g_MmGlobalInfo.ucMmServiceState) )
                {
                    /* �Աȱ��:��PSע��ʧ��#15ʱ,��Ӱ��CS��ע�����.
                       ��PS��ע��ʧ��,CSע��ɹ�ʱ,MMC��ɾ����ֹLAI,Ȼ��PS���ٷ���һ��ע��,���ս���ǵ�ǰ��LAI�����ֹLAI�б��� */
                    /*Mm_ComProcCauseProcess�н�ȫ�ֱ���g_MmGlobalInfo.ucProc��
                      g_MmGlobalInfo.ucCauseVal���*/
                    /* Mm_ComProcCauseProcess(); */
                    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
                    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
                    Mm_ComProcCauseProcess_Handling_LU_PROC();
                }
                else
                {
                    Mm_ComProcCauseProcess();

                    /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                       �ж������ǰ��PSҵ����Ҫ����LAU */
                    if ( VOS_TRUE == ucEmergencyLauFlg )
                    {
                        /* ����LAU */
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* ����LU����                               */
                        Mm_ComLuOnly();

                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return ;
                    }

                    if ((MM_TRUE == Mm_ComChkLu())
                      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING ==
                                                g_MmGlobalInfo.ucState))
                    {
                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return;
                    }
                }

                /*����LAU�����ѷ���LAU�������´���:*/

                (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                Mm_ComCheckDelayMmConn(MM_FALSE);

                NAS_MM_UpdateCsServiceConnStatusFlg();

                /*û�л���ҵ�����ʱ,�������������ΪPS ONLY��ҪDetach CS*/
                Mm_ComCheckDelayDetach();

                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}
/*****************************************************************************
 �� �� ��  :  Mm_Cell_S12_E33
 ��������  : ��WAIT FOR RR CONNECTION (MM CONNECTION)״̬��
             �յ�RRMM_REL_IND�Ĵ���,���������ΪAS�쳣,�ͷŵ����е�MM����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��29��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���,�������ⵥ�� A32D12966

  2.��    ��   : 2010��4��30��
    ��    ��   : o00132663
    �޸�����   : AT2D19011,G���ں��н��������У�С����ѡ������ģʽI,MMδ����-

 3.��    ��   : 2012��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2012021405430:W��ע��PS����15��CSע��δ��ɱ������ͷ�RRC���ӣ�
                ������W��ע��ɹ����쳣�����LAC��Ϣ���������յ��µ�ϵͳ��Ϣ��
                ��������LAU
 4.��    ��   : 2012��10��29��
   ��    ��   : z00161729
   �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 5.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����

 6.��    ��   : 2013��6��6��
   ��    ��   : w00167002
   �޸�����   : V9R1_SVLTE:CSδע���£���ǰ��PSҵ�񣬽������������ͷţ���Ҫ����LAU��
 7.��    ��   : 2013��8��28��
   ��    ��   : l65478
   �޸�����   : DTS2013082607368:����פ���ڽ�ֹ��������,CSҵ�����������LU
 8.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 9.��    ��   :2014��01��09��
   ��    ��   :l65478
   �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
10.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log

*****************************************************************************/
VOS_VOID    Mm_Cell_S12_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;

    RRMM_REL_IND_STRU                  *pstRelMsg  = VOS_NULL_PTR;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT8                           ucCsServiceConnStatusFlg;
#endif

    pstRelMsg = (RRMM_REL_IND_STRU *)pRcvMsg;

    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

    NAS_MM_ClearAuthInfo();

    enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pstRelMsg->ulRelCause);


    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if (MM_TRUE == ucValidFlg)
    {
        /* ֹͣ������ʱ�� */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* ֪ͨMMC���Ӳ����� */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

        /* ��¼Ǩ��֮ǰ��״̬  */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* ״̬Ǩ��   */
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* �������MM���ӽ��������з���LAI�ı䣬����Ҫ�ͷ�����MM����,���ڽ���MM���� */
        if(VOS_FALSE == g_MmGlobalInfo.ucPendingLu)
        {
            Mm_ComRelAllMmConn(enMmCcRelCause);
        }

        /* �������LU���� */


        /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
        if ( VOS_TRUE == ucEmergencyLauFlg )
        {
            /* ����LAU */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* ����LU����                               */
            Mm_ComLuOnly();

            return ;
        }

        if (MM_FALSE == Mm_ComChkLu())
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
        }

        g_MmGlobalInfo.ucPendingLu = VOS_FALSE;

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* �յ�CS PAGING�����ӽ���ʱ�յ��ײ��ͷ�ָʾ���쳣��¼ */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_RELEASED);
        }

        /* ��CSFB MT������ʱ����ʱ״̬���յ�REL IND�����CSFB��״̬��Ϣ */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        Mm_ComCheckDelayDetach();

        /* ��Ҫ���MM�����GMM��causeֵ */
        Mm_ComProcCauseClear();

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: ulRelCause Abnormal");
    }
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E33
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  s46746     05-09-24  modify for HSS 4100 V200R001

     3.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е����Ӵ���״̬
     4.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     5.��    ��   : 2013��6��6��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE:CSδע���£���ǰ��PSҵ�񣬽������������ͷţ���Ҫ����LAU��
     6.��    ��   : 2013��8��28��
       ��    ��   : l65478
       �޸�����   : DTS2013082607368:����פ���ڽ�ֹ��������,CSҵ�����������LU
     7.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     8.��    ��   :2014��01��09��
       ��    ��   :l65478
       �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
     9.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
    10.��    ��   : 2015��1��28��
       ��    ��   : w00167002
       �޸�����   : DTS2015011400748:��G��RL FAILURE����FR,������������쳣���޸�Ϊ
                    G�ϱ�RRC_REL_CAUSE_G_RL_FAILԭ��ֵ������NAS�Ͳ�����CC �ؽ���
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E33(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* ѭ����������                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd    = VOS_NULL_PTR;
    VOS_UINT8                ucTiValidFlg   = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        Mm_TimerStop( MM_TIMER_T3230 );                                         /* ͣTIMER3230                              */
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);       /* ֪ͨCC,MM���ӽ���ʧ��                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {
                    /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();


            /* CSδע���£��������������յ�attach cs�����Ȼظ�attach��������������������ͷź�
                   �ж������ǰ��PSҵ����Ҫ����LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* ����LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* ����LU����                               */
                Mm_ComLuOnly();

                return ;
            }

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
                    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                /* WAIT FOR REESTABLISH(WAIT FOR EST_CNF)�յ�rel ind�����ز� */
                NAS_MM_RelBufferedServiceEstReq(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E33
  FUNCTION : ��WAIT FOR ADDITIONAL OUTGOING MM CONNECTION״̬��
             �յ�RRMM_REL_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2.  ��־��        2005.01.27  007037 for MM
     3.  s46746     05-09-24  modify for HSS 4100 V200R001

     4.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
     5.��    ��   : 2012��10��29��
       ��    ��   : z00161729
       �޸�����   : DTS2012083102536:֧��cc�����ؽ�
     6.��    ��   : 2013��6��8��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE:�������CSȥע�������
                    ��ȫ���Ӷȣ�
     7.��    ��   :2013��9��12��
       ��    ��   :z00161729
       �޸�����   :DTS2013082903019:֧��ss�ط�����
     8.��    ��   :2014��01��09��
       ��    ��   :l65478
       �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
     9.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
    10.��    ��   : 2015��1��28��
       ��    ��   : w00167002
       �޸�����   : DTS2015011400748:��G��RL FAILURE����FR,������������쳣���޸�Ϊ
                    G�ϱ�RRC_REL_CAUSE_G_RL_FAILԭ��ֵ������NAS�Ͳ�����CC �ؽ���
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E33(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* ѭ����������                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;


    NAS_MM_ClearAuthInfo();

    /* ����ǰ�����CS��ȥע�� */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* �������ɹ���ֱ�ӱ���DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR���Ӳ�����                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        Mm_TimerStop( MM_TIMER_T3230 );                                         /* ͣTIMER3230                              */

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);


        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* ԭ��ֵ                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcErrInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                        /* ֪ͨCC,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndCcErrInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                    /* ֪ͨCC,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSsRelInd(i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                        /* ֪ͨSS,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSsRelInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                    /* ֪ͨSS,MM����ʧЧ                        */

                }
                if ( MM_CONST_NUM_0 !=
                    (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSmsRelInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );        /* ֪ͨSS,MM����ʧЧ                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[1]  & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM����ʧЧ                         */
                    Mm_SndSmsRelInd( (i + 8), NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE ); /* ֪ͨSS,MM����ʧЧ                        */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];/* ��¼��Ҫ�ؽ��ı�־                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];/* ��¼��Ҫ�ؽ��ı�־                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* ������ڵ�MM���ӱ�־                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            if ( ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[0] )
                || ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[1] )
                )
            {
                Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: STATUS is  WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
                Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* ��������TIMER                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();
                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    if ( ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                        RcvXXEstReq.ucFlg ) )
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

                    Mm_ComCheckDelayDetach();
                }
                else
                {
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                 NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* ֪ͨCC����ʧ��                           */

                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* �еȴ���CC��������Ҫ������MM����         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                    }
                }
            }
            break;
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection��Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC�����쳣: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS ��ʱ���� RR �ͷ� */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* ����ԭ��                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* û����Ƶ��Դ */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_ComRelAllMmConn(enMmCcRelCause);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
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
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR���Ӳ�����                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                             NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* ֪ͨCC����ʧ��                           */
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
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* �еȴ���CC��������Ҫ������MM����         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S16_E33:WARNING: ulRelCause Abnormal");
            break;
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E34
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11    �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е�ҵ�����״̬
     3.��    ��   :2013��9��14��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E34(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if (( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
            && ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState))
        {
            Mm_TimerStop( MM_TIMER_T3212 );                                     /* ͣT3212                                  */
        }
        if ( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* �����Ա����Ͱ�ȫģʽ����                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */
            switch ( g_MmGlobalInfo.ucMMConnEstingPD )
            {                                                                   /* ȷ�����ĸ�PD������MM����                 */
            case MM_IE_PD_CALL_CONTROL:                                         /* CCҪ������MM����                       */
                Mm_SndCcEstCnf(
                    (VOS_UINT32)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                        ucMMConnEstingTI), MMCC_EST_SUCCESS );  /* ��MM���ӽ����ɹ�                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
                {                                                               /*TIС��7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI ) );                                   /* ����MM���Ӵ��ڱ�־                       */
                }
                else
                {                                                               /*TI����7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[1] |
                        (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI - 8 )) );                              /* ����MM���Ӵ��ڱ�־                       */
                }
                /*lint +e701*/
                /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
                /* ����eCall��ʱ��������ʶ */
                NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
                /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* ������ڽ�����MM���ӵı�־               */
                break;
            case MM_IE_PD_SMS_MSG:                                              /* SMSҪ������MM����                      */
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())      /* ��GSM�����ж���Ϣ������Ҫ����SAPI3       */
                {
                    if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)            /* ���� */
                    {
                        if (MM_FALSE == MM_SndSapi3EstReq())
                        {
                            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E34: ERROR: snd SAPI3 est fail.");

                            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;       /* ����û�����ڽ���������           */

                            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                            g_MmGlobalInfo.ucPagingType     = MM_NO_PAGING;

                            return;
                        }

                        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                        g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                        return;
                    }
                }

                Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    ucMMConnEstingTI );                                         /* ��MM���ӽ����ɹ�                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
                {                                                               /*TIС��7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[0] |=
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI );                                     /* ����MM���Ӵ��ڱ�־                       */
                }
                else
                {                                                               /*TI����7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI - 8 ) );                               /* ����MM���Ӵ��ڱ�־                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* ������ڽ�����MM���ӵı�־               */
                break;
            case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                  /* SSҪ������MM����                       */
                Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI, MMSS_EST_SUCCESS );                       /* ��MM���ӽ����ɹ�                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
                {                                                               /*TIС��7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[0]
                     |= (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI );                                     /* ����MM���Ӵ��ڱ�־                       */
                }
                else
                {                                                               /*TI����7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI - 8 ) );                               /* ����MM���Ӵ��ڱ�־                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* ������ڽ�����MM���ӵı�־               */
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E34:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
                break;
            }
            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                /* ����û�����ڽ���������                   */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E34:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }
        else if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            && ((RR_SYN_TCH == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
                 ||(RR_SYN_TCH_MODIFY == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* ��CCָʾר���ŵ��Ѿ������ı�           */
            }
        }
        else
        {
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E34
  FUNCTION : ��MM CONNECTION ACTIVE״̬��
             �յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E34(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_WARNING,
                "Mm_Cell_S10_E34: WARNING: Receive RR Security false.");

        return;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState) || (WAIT_FOR_NETWORK_COMMAND == g_MmGlobalInfo.ucState))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* ��CCָʾר���ŵ��Ѿ������ı�           */
            }
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E34
  FUNCTION : ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
             �յ�RRMM_SECURITY_IND�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2. ��    ��   : 2006��12��5��
        ��    ��   : luojian 60022475
        �޸�����   : Maps3000�ӿ��޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E34(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* ѭ����������                             */

    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* ��Ϣ�����ʧ��                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* ��Ϣ������ɹ�                         */
        if (RRC_SECURITY_CS_SMC_CMPL ==
                    g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* �����Ա����Ͱ�ȫģʽ����                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* ͣTIMER3230                              */
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* �ؽ���MM����                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM�����ؽ��ɹ�                     */
                    Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS );                  /* ֪ͨCC,MM�����ؽ��ɹ�                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* ��TI��MM�����ؽ��ɹ�                     */
                    Mm_SndCcReestCnf( ( i + 8 ), MMCC_REEST_SUCCESS );          /* ֪ͨCC,MM�����ؽ��ɹ�                    */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ucPreState  = g_MmGlobalInfo.ucState;                /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E34:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */

            /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* ����eCall��ʱ��������ʶ */
            NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
            /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E35
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬���յ�RRMM_SYNC_IND�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
     2. ��    ��   : 2007��02��16��
        ��    ��   : luojian 60022475
        �޸�����   : 3000�ӿ��޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E35(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSyncInd(pRcvMsg) )
    {
        return;
    }

    Mm_SndCcSyncInd();                                                      /* ��CCָʾר���ŵ��Ѿ������ı�           */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E36
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(AUTHENTICATION REQUEST)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E36(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
    Mm_ComAuthenRcvAuthenReq();                                                 /* �յ�AUTHEN REQ�Ĵ���                     */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E37
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(AUTHENTICATION REJECT)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  ��־��      03-12-11    �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��10��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 PhaseII EPLMN/RPLMN��MM/GMMά���޸�
  4.��    ��   : 2011��04��23��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ�ţ�DTS2011032903294,[�����������������翨�����������ٻ�ԭС����UEֻ��������T3212������û�з���LAU
  5.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E37(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8       ucCause;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5�½���������:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);    }

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

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E38
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(IDENTITY REQUEST)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E38(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_ComIdentity();                                                           /* IDENTITY���̵Ĵ���                       */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E39
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(TMSI REALLOCATION COMMAND)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E39(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_ComTmsiReloc();                                                          /* TMSI RELOC����                           */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E40
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(CM SERVICE ACCEPT)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е����Ӵ���״̬
     3.��    ��   :2013��9��14��
       ��    ��   :z00161729
       �޸�����  :DTS2013082903019:֧��ss�ط�����
     4.��    ��   :2014��9��24��
       ��    ��   :s00217060
       �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E40(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣTIMER3230                              */
    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* ȷ�����ĸ�PD������MM����                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CCҪ������MM����                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI )
        {                                                                       /*TIС��7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI ) );                                           /* ����MM���Ӵ��ڱ�־                       */
        }
        else
        {                                                                       /*TI����7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                 | (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI - 8 ) ) );                                     /* ����MM���Ӵ��ڱ�־                       */
        }
        /*lint +e701*/
        Mm_SndCcEstCnf( (VOS_UINT32)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI), MMCC_EST_SUCCESS );                               /* ��MM���ӽ����ɹ�                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* ������ڽ�����MM���ӵı�־               */

        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        /* ����eCall��ʱ��������ʶ */
        NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
        break;
    case MM_IE_PD_SMS_MSG:                                                      /* SMSҪ������MM����                      */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* ��GSM�����ж���Ϣ������Ҫ����SAPI3       */
        {
            if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)                    /* ���� */
            {
                if (MM_FALSE == MM_SndSapi3EstReq())
                {
                    Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E40: ERROR: snd SAPI3 est fail.");

                    g_MmGlobalInfo.ucMMConnEstingPD         = NO_MM_CONN_ESTING; /* ����û�����ڽ���������           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                    g_MmGlobalInfo.ucPagingType             = MM_NO_PAGING;

                    return;
                }

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                return;
            }
        }
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI )
        {                                                                       /*TIС��7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI ) ;                                            /* ����MM���Ӵ��ڱ�־                       */
        }
        else
        {                                                                       /*TI����7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI - 8 ) );                                       /* ����MM���Ӵ��ڱ�־                       */
        }
        /*lint +e701*/
        Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI);                                                  /* ��MM���ӽ����ɹ�                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* ������ڽ�����MM���ӵı�־               */
        break;
    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SSҪ������MM����                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI )
        {                                                                       /*TIС��7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI );                                             /* ����MM���Ӵ��ڱ�־                       */
        }
        else
        {                                                                       /*TI����7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI - 8 ) );                                       /* ����MM���Ӵ��ڱ�־                       */
        }
        /*lint +e701*/
        Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI, MMSS_EST_SUCCESS );                               /* ��MM���ӽ����ɹ�                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* ������ڽ�����MM���ӵı�־               */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E40:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* ����û�����ڽ���������                   */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E40:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* ����Ƿ��б�������Ҫ������MM����         */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCmServiceRej_CcExist
 ��������  : CCҵ�����ʱ�յ�CM SERVICE REJ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_CcExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* ԭ��ֵ4ʱ������CM��ҵ�񣬵ȴ�Lu��ɺ����·���CMҵ�� */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* ԭ��ֵ22ʱ��֪ͨCCҵ��ʧ�ܣ������Ƿ�Я��T3246��Я��T3246ʱ����Ҫ�ز� */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

            break;

        /* ����ԭ��ֵ */
        default:

            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                /* ֪ͨCC,MM���ӽ���ʧ��                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCmServiceRej_SsExist
 ��������  : SSҵ�����ʱ�յ�CM SERVICE REJ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_SsExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* ԭ��ֵ4ʱ������CM��ҵ�񣬵ȴ�Lu��ɺ����·���CMҵ�� */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* ԭ��ֵ22ʱ��֪ͨCCҵ��ʧ�ܣ������Ƿ�Я��T3246��Я��T3246ʱ����Ҫ�ز� */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

            break;

         /* ����ԭ��ֵ */
         default:

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI           /* ������ڽ���MM���ӵı�־ */
                = NO_MM_CONN_ESTING;

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ProcCmServiceRej_SmsExist
 ��������  : SMSҵ�����ʱ�յ�CM SERVICE REJ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_SmsExist( VOS_VOID )


{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* ԭ��ֵ4ʱ������CM��ҵ�񣬵ȴ�Lu��ɺ����·���CMҵ�� */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* ԭ��ֵ22ʱ��֪ͨCCҵ��ʧ�ܣ������Ƿ�Я��T3246��Я��T3246ʱ����Ҫ�ز� */
         case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

             if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

             }
             else
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* ֪ͨCC,MM���ӽ���ʧ��:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
             }


             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                 = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

             break;

        /* ����ԭ��ֵ */
         default:

             Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* ������ڽ���MM���ӵı�־ */

             break;
    }

    return;
}


/*******************************************************************************
  MODULE   : Mm_Cell_S9_E41
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(CM SERVICE REJECT)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      03-12-11  �°�����
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : OSA�Ż���������©��A32D05845���ⵥ���޸�,�ֲ���
                 ���ⵥ��:A32D06583

  3.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е�ҵ�����״̬
  4.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  6.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  7.��    ��   :2013��9��14��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  8.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
  9.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E41(
                        VOS_VOID            *pRcvMsg                                /* ������Ϣ��ͷ��ַ                         */
                    )
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                        /* ͣT3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣMM_TIMER_T3230                         */

    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* ȷ�����ĸ�PD������MM����                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CCҪ������MM����                       */

        NAS_MM_ProcCmServiceRej_CcExist();

        break;

    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SSҪ������MM����                       */

        NAS_MM_ProcCmServiceRej_SsExist();

        break;

    case MM_IE_PD_SMS_MSG:                                                      /* SMSҪ������MM����                      */

        NAS_MM_ProcCmServiceRej_SmsExist();

        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E41:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }

    Mm_SndMmcCmSvcRejInd( g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause );

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* �ܾ�ԭ��ֵ                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* �ܾ�ԭ��ֵ#4                             */
        Mm_ComRejectCause4();                                                   /* �ܾ�ԭ��ֵ#4�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* �ܾ�ԭ��ֵ#6                             */
        Mm_ComRejectCause6();                                                   /* �ܾ�ԭ��ֵ#6�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
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
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ��¼Ҫ�����״̬                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* ����TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }

        break;
    default:
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
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* û��MM���Ӵ���                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* ��¼Ҫ�����״̬                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM��������                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* ����TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* ��¼Ǩ��֮ǰ��״̬                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* ����Ƿ��б�������Ҫ������MM����         */
        }

        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* ����û�����ڽ���������                   */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S14_E41
  FUNCTION : ��WAIT FOR REESTABLISH��WAIT FOR EST_CNF��״̬��
             �յ�RRMM_DATA_IND(CM SERVICE REJECT)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.��־��      03-12-11  �°�����

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ����MML_CTX�е����Ӵ���״̬
  3.��    ��   : 2011��7��22��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  6.��    ��   :2013��9��14��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E41(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* ѭ����������                             */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣMM_TIMER_T3230                         */

    for ( i = 0; i < MM_CONST_NUM_7; i++ )
    {                                                                           /* �ؽ���MM����                             */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( i, (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));             /* ֪ͨCC,MM���ӽ���ʧ��                    */
        }
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( ( i + 8 ), (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                            /* ֪ͨCC,MM���ӽ���ʧ��                    */
        }
        /*lint +e701*/
    }

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                                       /* ������ڵ�MM���ӱ�־                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                                       /* ������ڵ�MM���ӱ�־                     */

    Mm_SndMmcCmSvcRejInd(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause);

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* �ܾ�ԭ��ֵ                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* �ܾ�ԭ��ֵ#4                             */
        Mm_ComRejectCause4();                                                   /* �ܾ�ԭ��ֵ#4�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* �ܾ�ԭ��ֵ#6                             */
        Mm_ComRejectCause6();                                                   /* �ܾ�ԭ��ֵ#6�Ĺ�������                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* ��¼Ҫ�����״̬                         */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM��������                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* ��¼Ǩ��֮ǰ��״̬                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* ����TIMER3240                            */
        break;
    default:
        break;
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E42
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(ABORT)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11    �°�����
     2.��    ��   : 2012��7��12��
       ��    ��   : s00217060
       �޸�����   : �ܾ�ԭ��ֵ#6,#17ʱ��֪ͨMMC Abort��Ϣ

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E42(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* ͣT3212                                  */

    switch (g_MmMsgAbort.MmIeRejCause.ucRejCause )
    {                                                                           /* �ܾ�ԭ��ֵ                               */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* �ܾ�ԭ��ֵ#6                             */
        Mm_ComAbortCause6();                                                    /* �ܾ�ԭ��ֵ#6�Ĺ�������                   */
        /* ֪ͨMMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:                                          /* �ܾ�ԭ��ֵ#17                            */

#if (FEATURE_ON == FEATURE_PTM)
        /* MT�ĳ����� �ñ��ΪTRUEʱΪMT */
        if (VOS_TRUE == NAS_MML_GetCsServiceConnStatusFlg())
        {
            /* �յ�CS PAGING�����ӽ����ɹ�������δ�յ�ҵ����Ϣ���յ�����ABORT���쳣��¼ */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_ABORT);
        }
#endif

        Mm_ComAbortCause17();                                                   /* �ܾ�ԭ��ֵ#17�Ĺ�������                  */
        /* ֪ͨMMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);
        break;
    default:
        break;
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E43
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND(MM INFORMATION)�Ĵ���
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-11    �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E43(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* ͣT3212                                  */
    }

    Mm_ComInfo();                                                               /* MM INFO���̵Ĵ���                        */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E50
  FUNCTION : ��WAIT FOR OUTGOING MM CONNECTION״̬��
             �յ�RRMM_DATA_IND( CM Message)�Ĵ���
  INPUT    : VOS_VOID            *pRcvMsg  �յ���ԭ��ͷָ��
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  ��־��      03-12-12  �°�����

     2.��    ��   : 2011��7��14��
       ��    ��   : zhoujun 40661
       �޸�����   : ����MML_CTX�е����Ӵ���״̬

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E50(
                        VOS_VOID            *pRcvMsg                            /* ������Ϣ��ͷ��ַ                         */
                    )
{
    VOS_UINT8           ucTI = 0;                                               /* CC��Ϣ�е�TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* ��ϢRRMM_DATA_IND�Ľṹ��ָ��            */
    VOS_UINT8          *pucCMMsg = VOS_NULL_PTR;                                /* ָ������ת��                             */
    VOS_UINT8          *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }
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
        /*lint -e701*/
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

            /* BEGIN: Modified by ŷ����  ID: 00132663, 2008/8/26   PN:AT2D05317*/
            /* Ŀǰ������״̬����øú���
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                ͳһ״̬��Ǩ�� WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION */
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* ��¼Ǩ��֮ǰ��״̬                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E50:NORMAL: STATUS is  WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
            /* END:   Modified by ŷ����  ID: 00132663, 2008/8/26 */
        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC������MM����                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* �����Ӵ���                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* ��CC����MMCC_DATA_IND                    */
        }
        /*lint +e701*/

    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* �ͷ��������Ϣ                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E1
  Function: MM_NULL ״̬,�յ� MMCMM_START_REQ ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.09   �°�����
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_ComStart();                                                          /* �����յ�MMCMM_START_REQ�Ĺ�������        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E1
  Function: MM_IDLE_NO_CELL_AVAILABLE ״̬,�յ� MMCMM_START_REQ ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.��־��   2003.12.09   �°�����
  2.s46746     05-09-27  modify for HSS 4100 V200R001
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2013��9��14��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E1:NORMAL: STATUS is MM_STATE_NULL");

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
  Module:   Mm_Cell_S1_E3
  Function: MM_IDLE_NO_CELL_AVAILABLE ״̬,�յ� MMCMM_PLMN_SEARCH_INITIATED
            ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��   2003.12.09   �°�����
      2.  s46746     05-09-27  modify for HSS 4100 V200R001
      3.��    ��   : 2008��12��1��
        ��    ��   : o00132663
        �޸�����   : AT2D07041, ���û������LIST����������HPLMN����ʱ��CREG,CGREG��ͣ�ϱ���
      4.��    ��   : 2011��12��7��
        ��    ��   : w00176964
        �޸�����   : V7R1 PhaseIV ����:RRC���ӵ���
      5.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
      6.��    ��   : 2013��10��15��
        ��    ��   : l65478
        �޸�����   : DTS2013102501008���յ�����ģʽ���ó��Զ�����ģʽ��û�з���ע��
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E3(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */

        /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
        if ((MM_IDLE_NO_CELL_AVAILABLE != g_MmGlobalInfo.ucState)
         && (MM_IDLE_PLMN_SEARCH       != g_MmGlobalInfo.ucState))
        {
            g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;
        }

        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E6
  Function: MM_IDLE_NORMAL_SERVICE ״̬,�յ� GMMMM_COMBINED_ATTACH_INITIATION
            ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.��    ��   : 2008��11��22��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D06931, �����־λucT3212ExpiredFlg
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��2��15��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 ֧��CSFB/ISR�����޸�
  6. ��    ��   : 2012��06��1��
     ��    ��   : z00161729
     �޸�����   : V7R1C50 GUL�������޸ģ�L�¿�������ע��eps only�ɹ���cs����δattach̬��
                   bg�Ѹ����ȼ�����ɹ�������ָ���ѳɹ�������ע�����syscfg����ps
                   only,mmֱ�ӻظ�detach cnf��cs reg result indǨ��limit service״̬��
                   �������յ�����ע��init��Ϣ��ӦǨ״̬

  7.��    ��   : 2012��12��22��
    ��    ��   : l65478
    �޸�����   : DTS2012122103936 �����������ʱMM״̬Ǩ�ƴ���
  8.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                 �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                 rau req�д�follow on��־,����ȷЭ������
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E6(
                    VOS_VOID     *pMsg                                              /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvGmmCombinedAttachIni(pMsg))
    {

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E6:NORMAL: STATUS is LOCATION_UPDATING_PENDING");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E1
  Function: WAIT_FOR_OUTGOING_MM_CONNECTION ״̬,�յ� MMCMM_START_REQ ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2013��9��14��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E1(
                    VOS_VOID     *pMsg                                              /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ͣtimer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S9_E4 */


/*******************************************************************************
  Module:   Mm_Cell_S10_E1
  Function: MM_CONNECTION_ACTIVE ״̬,�յ� MMCMM_START_REQ ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   :2013��9��14��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  7.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E1(
                    VOS_VOID     *pMsg                                              /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S10_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S11_E1
  Function: WAIT_FOR_NETWORK_COMMAND ״̬,�յ� MMCMM_START_REQ ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  4.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3240].ucTimerStatus)
        {                                                                       /* ���timer 3240��������,��ֹͣ            */
            Mm_TimerStop(MM_TIMER_T3240);                                       /* ͣtimer 3240                             */
        }
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S11_E4 */


/*******************************************************************************
  Module:   Mm_Cell_S12_E1
  Function: WAIT_FOR_RR_CONNECTION_MM_CONNECTION ״̬,�յ� MMCMM_START_REQ
            ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  ��־��        2005.01.27  007037 for MM
  3.  s46746     05-09-27  modify for HSS 4100 V200R001
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  6.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E1:NORMAL: STATUS is  MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S12_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S13_E1
  Function: WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ ״̬,�յ� MMCMM_START_REQ
            ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  ��־��        2005.01.27  007037 for MM
  3.  s46746     05-09-27  modify for HSS 4100 V200R001
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  7.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  9.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E1:NORMAL: STATUS is MM_STATE_NULL");

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
/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S13_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S14_E1
  Function: WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF ״̬,�յ� MMCMM_START_REQ ԭ��
            �Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  ��־��        2005.01.27  007037 for MM
  3.  s46746     05-09-27  modify for HSS 4100 V200R001
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  6.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
  8.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* ��������TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S14_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S16_E1
  Function: WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION ״̬,�յ� MMCMM_START_REQ
            ԭ��Ĵ���
  Input:    VOS_VOID     *pMsg,  ��ǰ�������Ϣ
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��   2003.12.09   �°�����
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
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
VOS_VOID Mm_Cell_S16_E1(
                    VOS_VOID     *pMsg                                          /* ��ǰ�������Ϣ                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* ͣtimer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);



        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ����ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E1:NORMAL: STATUS is MM_STATE_NULL");

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

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S16_E4 */

/* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ��Mm_Cell_S19_E4 */

/*******************************************************************************
  Module:   Mm_Get_UserSpecificSearchFlg_From_SysInfo
  Function: ��MMC����MM��sys info��Ϣ�л�ȡUserSpecificSearchFlg��־��Ϣ
  Input:    VOS_VOID * pRcvMsg   - sys info ��Ϣָ��
  Output:
  NOTE:
  Return:   VOS_UINT8  - UserSpecificSearchFlg ��־
  History:
      1.  ŷ����    2009.1.22  �°�����
  2.��    ��   : 2013��07��25��
    ��    ��   : l65478
    �޸�����   : ��ǰ����פ��,���û�ָ��������ǰ������ʱ,MM������ע��,GCFʧ��
*******************************************************************************/

VOS_UINT8 Mm_Get_UserSpecificSearchFlg_From_SysInfo(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;
    MMCMM_SYS_INFO_IND_STRU            *pSysInfoInd             = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pGsmSysInfoInd          = VOS_NULL_PTR;

    pSysInfoInd      = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;
    pGsmSysInfoInd   = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    if (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
    {
        return VOS_FALSE;
    }

    if (MMCMM_SYS_INFO_IND == pSysInfoInd->MsgHeader.ulMsgName )
    {
        ucUserSpecificSearchFlg = pSysInfoInd->ucUserSpecificSearchFlg;
    }
    else
    {
        ucUserSpecificSearchFlg = pGsmSysInfoInd->ucUserSpecificSearchFlg;
    }

    return ucUserSpecificSearchFlg;
}

/*******************************************************************************
  Module:   Mm_Cell_S1_E5
  Function: ��MM IDLE NO CELL AVAILABLE״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  ��־��     2003.12.10  �°�����
  2.  s46746  05-09-27  modify for HSS 4100 V200R001
  3.��    ��   : 2006��10��6��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�A32D05960
  4.��    ��   : 2007��04��20��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D10235
  5.��    ��   : 2007��09��05��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�AT2D01490
  6.��    ��   : 2008��08��21��
    ��    ��   : ouyangfei id:00132663
    �޸�����   : ���ⵥ�ţ�AT2D04652,��С���ı�ʱ��ֹͣ��ʱ�� T3211
  7.��    ��   : 2008��09��03��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  8.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  9.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 10.��    ��   : 2011��6��3��
    ��    ��   : c00173809
    �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
 11.��    ��   : 2011��10��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 PhaseII EPLMN/RPLMN��MM/GMMά���޸�
 12.��    ��   : 2012��02��29��
    ��    ��   : l00130025
    �޸�����   : DTS2012022206186:������LAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
 13.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
 14.��    ��   : 2012��3��09��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 ֧��CSFB�����޸�:��CSFB��־����ʱ�����𵥶���LAU
 15.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 16.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 17.��    ��   : 2013��12��5��
    ��    ��   : w00167002
    �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                 PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                 �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                 �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ��¡�
 18.��    ��   : 2014��04��1��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż��Լ�ȫ�ֱ����滻��MML�е�
 19.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/

VOS_VOID Mm_Cell_S1_E5(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if ((VOS_TRUE == ulLaiChangeFlag)
     || (MM_TRUE  == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }

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

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
    /* CS ONLY��PS ONLY,��NMO1����Ҫ��������ע�� */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: mmLikeB is MM_TRUE");

            if (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( ( VOS_FALSE == ulLaiChangeFlag ) &&
                     ( NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
                {
                    if ( MM_TRUE
                     == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                            MM_IE_LUT_PERIODIC_UPDATING;                /* ����LU����                               */
                        Mm_ComLuOnly();                                 /* ����LU REQ                               */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn());

                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* ���÷���״̬                             */

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* ����LU����                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
            }
            else
            {
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
                if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
                /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* ����LU����                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
                else
                {
                    switch ( NAS_MML_GetCsUpdateStatus() )
                    {
                    case NAS_MML_LOCATION_UPDATE_STATUS_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                            MM_NORMAL_SERVICE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);    /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* ��MMC����MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬                               */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        break;
                    case NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                        MM_ATTEMPTING_TO_UPDATE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_FAILURE,
                                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);    /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* ��MMC����MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬                               */
                        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {   /* A+II����Bģʽ                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* ������ϵͳ��Ϣ�Ĺ�������                 */
    }
}

/*******************************************************************************
  Module:   Mm_MakeCcEstReq
  Function: ���ݻ������Ϣ������Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2007��09��29��
        ��    ��   : l65478
        �޸�����   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeCcEstReq(MMCC_EST_REQ_STRU *pMsg)
{
    pMsg->ulCallPri =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallPri;
    pMsg->ulCallType =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;
    pMsg->ulTransactionId =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;
    pMsg->ulCallMode =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallMode;

}
/*******************************************************************************
  Module:   Mm_MakeSmsEstReq
  Function: ���ݻ������Ϣ������Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2007��09��29��
        ��    ��   : l65478
        �޸�����   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeSmsEstReq(MMSMS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId;
    pMsg->ulEstCause = g_MmSmsEstReq.ulEstCause;
}
/*******************************************************************************
  Module:   Mm_MakeSsEstReq
  Function: ���ݻ������Ϣ������Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2007��09��29��
        ��    ��   : l65478
        �޸�����   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeSsEstReq(MMSS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId;
}

/*******************************************************************************
  Module:   Mm_MakeGPagingInd
  Function: ���ݻ������Ϣ������Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2008��05��02��
        ��    ��   : s46746
        �޸�����   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeGPagingInd(GRRMM_PAGING_IND_ST *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = GRRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = UEPS_PID_GAS;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(GRRMM_PAGING_IND_ST) - VOS_MSG_HEAD_LENGTH;
    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ucMSIDType                = GAS_TMSI;
    }
    else
    {
        pMsg->ucMSIDType                = GAS_IMSI;
    }
    pMsg->ucPagingType                  = 0;

    return;
}

/*******************************************************************************
  Module:   Mm_MakeWPagingInd
  Function: ���ݻ������Ϣ������Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2008��05��02��
        ��    ��   : s46746
        �޸�����   : creat function
      2.��    ��   : 2012��09��01��
        ��    ��   : s46746
        �޸�����  : DTS2012090405619 :DCM�ⳡ����,����RAU��������ӦѰ��������abort
*******************************************************************************/
VOS_VOID Mm_MakeWPagingInd(RRMM_PAGING_IND_STRU *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = RRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(RRMM_PAGING_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pMsg->ulPagingCause                 = g_MmGlobalInfo.ucPagingCause;
    pMsg->ulCnDomainId                  = RRC_NAS_CS_DOMAIN;

    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ulPagingUeId              = RRC_TMSI_GSM_MAP_P_TMSI;
    }
    else
    {
        pMsg->ulPagingUeId              = RRC_IMSI_GSM_MAP;
    }

    pMsg->ulPagingType                  = 0;
}

/*******************************************************************************
  Module:   Mm_DealWithBuffMsg
  Function: ���������Ϣ
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.��    ��   : 2007��09��29��
        ��    ��   : l65478
        �޸�����   : creat function
      2.��    ��   : 2010��11��23��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:DTS2010111604795������Attempt update״̬�Ĵ���
      3.��    ��   : 2012��12��27��
        ��    ��   : t00212959
        �޸�����   : DTS2012122607665:������MM_WAIT_FOR_ATTACH״̬��Ҫ����
      4.��    ��   : 2013��07��05��
        ��    ��   : l65478
        �޸�����   : DTS2013070408274:MM����NORMAL SERVICE��û�д������CC��Ϣ
*******************************************************************************/
VOS_VOID Mm_DealWithBuffMsg(VOS_VOID)
{
    MMCC_EST_REQ_STRU                   CcEstReqMsg;
    MMSMS_EST_REQ_STRU                  SmsMsg;                                 /* ������յ�����Ϣ����ָ��                 */
    MMSS_EST_REQ_STRU                   SsMsg;                                  /* ������յ�����Ϣ����ָ��                 */
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: deal with buffer message! ");
    if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start CC message preceed! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[23][g_MmGlobalInfo.ucState](&CcEstReqMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[61][g_MmGlobalInfo.ucState](&SmsMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[64][g_MmGlobalInfo.ucState](&SsMsg);
            /*lint +e961*/
        }
        else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
                /*lint +e961*/
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
                /*lint +e961*/
            }
        }
        else
        {
        }
    }
    else if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState )
        && (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState )
        && (WAIT_FOR_RR_CONNECTION_MM_CONNECTION != g_MmGlobalInfo.ucState)
        && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState ))
    {
        if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start EMC! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E24(&CcEstReqMsg);

        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E62(&SmsMsg);
        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E65(&SsMsg);
        }
        else
        {
        }
    }
    else if (MM_WAIT_FOR_ATTACH == g_MmGlobalInfo.ucState)
    {
        if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {/* ��ʱС���϶�û�з����仯 */
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                Mm_Cell_S3_E31(&stGPagingMsg);
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                Mm_Cell_S3_E31(&stWPagingMsg);
            }
        }
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
            /* ����LAU���� �н������Ƚ��н�����*/
            enLauType = NAS_MM_GetLuType();

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);
        }

    }
    else
    {
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}

/*******************************************************************************
  Module:   Mm_Cell_S2_E5
  Function: ��MM IDLE PLMN SEARCH״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
   1.  ��־��     2003.12.10  �°�����
   2.  s46746  05-09-27  modify for HSS 4100 V200R001
   3.  s46746 2006-02-28 �������ⵥA32D02503�޸�
   4.  s46746  2006-06-24  �������ⵥA32D04439�޸�
   5.  s46746  2006-07-25  �������ⵥA32D05058�޸�
   6.��    ��   : 2006��10��6��
     ��    ��   : s46746
     �޸�����   : ���ⵥ�ţ�A32D05960
   7.��    ��   : 2007��04��20��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�A32D10235
   8.��    ��   : 2007��09��05��
     ��    ��   : luojian id:60022475
     �޸�����   : �������ⵥ�ţ�AT2D01490
   9.��    ��   : 2007��10��06��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�A32D12977
  10.��    ��   : 2008��08��21��
     ��    ��   : ouyangfei id:00132663
     �޸�����   : ���ⵥ�ţ�AT2D04652,��С���ı�ʱ��ֹͣ��ʱ�� T3211
  11.��    ��   : 2008��09��03��
     ��    ��   : l00130025
     �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
  12.��    ��   : 2008��11��22��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�AT2D06900,mmע��״̬�޸�
  13.��    ��   : 2009��02��21��
     ��    ��   : l65478
     �޸�����   : AT2D09308,�����Ʒ����£����������Ϣ
  14.��    ��   : 2009��05��11��
     ��    ��   : h44270
     �޸�����   : AT2D11661/AT2D11804,�����ֶ��������LAU���̣����������ɹ���������LAU
  15.��    ��   : 2009��8��23��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�AT2D13980,��LUʧ�ܺ󣬸ı�С���󣬴˺��ٲ��ᷢ��LU,��Ϊ���յ�ϵͳ��Ϣʱ����T3211ֹͣ��
  16.��    ��   : 2010��03��20��
     ��    ��   : l65478
     �޸�����   : ���ⵥ�ţ�AT2D17070,������ָֹ������ʱ��MMC����û�з�������
  17.��    ��   : 2010��11��30��
     ��    ��   : h44270
     �޸�����   : ���ⵥ�ţ�DTS2010112905048/DTS201011270072,CS��IMSI��Чʱ��û����MMC�ظ���Ϣ�յ���Ϣ
  18.��    ��   : 2011��7��16��
     ��    ��   : h44270
     �޸�����   : V7R1 PhaseII�׶ε�����ע������
  19.��    ��   : 2011��7��25��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  20.��    ��   : 2011��6��3��
     ��    ��   : c00173809
     �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
  21.��    ��   : 2011��10��27��
     ��    ��   : s46746
     �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  22.��    ��   : 2011��12��2��
     ��    ��   : s46746
     �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
  23.��    ��   : 2012��03��20��
     ��    ��   : l00130025
     �޸�����   : DTS2012030105247,NASֻ������ʵ�ʷ����Ȩʱ,֪ͨW SecurityKey�������������WAS���ö�Ӧ�ӿڻ�ȡ
  24.��    ��  : 2012��2��15��
     ��    ��  : w00167002
     �޸�����  : V7R1C50 ֧��CSFB�����޸ģ����ӶԴ���CSFB��־ʱ�Ĵ���
  25.��    ��   : 2012��8��22��
     ��    ��   : z00161729
     �޸�����   : DCM������������������޸�
  26.��    ��   : 2013��2��4��
     ��    ��   : w00176964
     �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  27.��    ��   : 2013��05��15��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  28.��    ��   : 2013��12��5��
     ��    ��   : w00167002
     �޸�����   : DTS2013113006231:W�£�������LAC1��ע��ɹ�����ѡ��LAC2�ϣ�CSע��ɹ�
                  PSע�ᱻ��#13,��ѡ��LAC1�ϣ�ע��ɹ�������������С��פ����LAC2
                  �ϣ�������ע�ᣬ��ѡ��LAC1�ϣ���ⲻ����ע�ᡣ
                  �޸�Ϊ���յ�ϵͳ��Ϣʱ�򣬲�����UPDATE״̬�ĸ��¡�
 21.��    ��   : 2014��04��1��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
 22.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/

VOS_VOID Mm_Cell_S2_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurrentRatType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    NAS_MM_NotifyAsInfoChgReq();


    enCurrentRatType = NAS_MML_GetCurrNetRatType();

    if (( MM_CKSN_INVALID != NAS_MML_GetSimCsSecurityCksn() )
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrentRatType))
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
    }

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
    /* �����ǰLAI��֮ǰפ����LAI��ȷ����仯,��Ҫ���atttemp conterֵ */
    if (VOS_TRUE == NAS_MM_IsNeedClearAttemptCounter())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }

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

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
    /* CS ONLY,PS ONLY��NMO1��GMM��Ҫ��������ע�� */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
        )
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: LikeB is MM_TRUE");

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

            if ( ( VOS_FALSE == ulLaiChangeFlag )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
            {
                if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                        /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                        {
                            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                        }

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                    {
                        /* Modified by z00161729 for DCM�����������������, 2012-8-23, begin */
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);
                        /* Modified by z00161729 for DCM�����������������, 2012-8-23, end */

                    }
                    else if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                        /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* ���÷���״̬                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* ��MMC����MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
            }
            else
            {
                /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */
            }
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        }
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {
        /* A+II����Bģʽ                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* ������ϵͳ��Ϣ�Ĺ�������                 */
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */

    Mm_DealWithBuffMsg();
}

/*******************************************************************************
  Module:   Mm_Cell_S2_E21
  Function: ��MM IDLE PLMN SEARCH״̬���յ�MMCMM_COVERAGE_LOST_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2.  s46746  05-09-27  modify for HSS 4100 V200R001
      3.��    ��   : 2008��08��15��
        ��    ��   : l65478
        �޸�����   : ���ⵥ�ţ�AT2D04830����״̬�ϱ�����
      4.��    ��   : 2009��01��14��
        ��    ��   : l65478
        �޸�����   : ���ⵥ�ţ�AT2D07971,������״̬���ϱ��Ľ��뼼������
      5.��    ��   : 2011��10��11��
        ��    ��   : l00171473
        �޸�����   : V7R1 phase II, TC���ص�����֪ͨTC�����ͷ�
      6.��    ��   : 2012��9��24��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��DTS2012092003660���޷���ʱ���Ͷ��ţ����º������ٷ�������
      7.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      8.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
      9.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����   :DTS2013082903019:֧��ss�ط�����
     10.��    ��   : 2013��10��15��
        ��    ��   : l65478
        �޸�����   : DTS2013102501008���յ�����ģʽ���ó��Զ�����ģʽ��û�з���ע��
     11.��    ��   : 2014��05��31��
        ��    ��   : s00246516
        �޸�����   : ·�������¹����г�������������л����Detach��û�лظ�
     12.��    ��   : 2014��04��29��
        ��    ��   : y00245242
        �޸�����   : eCall��Ŀ�޸�
     13.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
     14.��    ��   : 2014��12��29��
        ��    ��   : z00161729
        �޸�����   : DSDSҵ���ز�ʱno rfδ������������ҵ��ʧ�ܣ�mm��no cell available״̬no rfʱ��mmc����cm service ind��������
*******************************************************************************/

VOS_VOID Mm_Cell_S2_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        return;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        /* �����EMC�������ȴ��ϲ����ֹ, �����ǰno rfֱ�Ӹ�cc�ظ�ʧ�� */
        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         || (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))

        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                        /* ֪ͨSMS����ʧ��                          */
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);

        /* TC״̬�յ�COVERAGE LOST��Ϣʱ��֪ͨTC�����ͷ� */
        NAS_MM_SndTcRrRelInd();
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_SERVICE);

        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* ����MM��Ϣ                               */

        /* ����ȴ���־ */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E21:INFO: MmServiceState is MM_NO_SERVICE");
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E21
  Function: ��WAIT FOR REESTABLISH(WAIT FOR EST_CNF)״̬��
            �յ�MMCMM_COVERAGE_LOST_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  s46746  06-05-20  Add for A32D03824
      2.��    ��   : 2008��08��15��
        ��    ��   : l65478
        �޸�����   : ���ⵥ�ţ�AT2D04830����״̬�ϱ�����

      3.��    ��   : 2011��7��14��
        ��    ��   : zhoujun 40661
        �޸�����   : ����MML_CTX�е����Ӵ���״̬
      4.��    ��   : 2011��11��22��
        ��    ��   : w00166186
        �޸�����   : DTS2011112101648,OOS�ȴ�ϵͳ��Ϣ��ʱ���������ӱ�־û����������º���AVAILABLE
                     ��ʱ����ʱ��û�з�������
      5.��    ��   : 2012��10��29��
        ��    ��   : z00161729
        �޸�����   : DTS2012083102536:֧��cc�����ؽ�
      6.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
      7.��    ��   : 2013��07��23��
        ��    ��   : l65478
        �޸�����   : DTS2013071809030,MMC�յ�RRMM_SUSPEND_REL_CNF��û�����̴������SYSCFG
      8.��    ��   :2013��9��12��
        ��    ��   :z00161729
        �޸�����  :DTS2013082903019:֧��ss�ط�����
      9.��    ��   :2013��10��18��
        ��    ��   :z00161729
        �޸�����   :DTS2013101900866:mm��wait for mm connection״̬�յ�gas������Ϣû�и�cc�ظ�rel ind���º���T303��ʱ����ʧ��
     10.��    ��   : 2013��10��15��
        ��    ��   : l65478
        �޸�����   : DTS2013102501008���յ�����ģʽ���ó��Զ�����ģʽ��û�з���ע��
     11.��    ��   : 2014��04��29��
        ��    ��   : y00245242
        �޸�����   : eCall��Ŀ�޸�
     12.��    ��   :2014��9��24��
        ��    ��   :s00217060
        �޸�����   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E21:WARNING: MMCMM_COVERAGE_LOST_IND is not correct.");
        return;
    }

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                                  /* ��������TIMER                            */

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
        
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); 
    }

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E21:INFO: MmServiceState is MM_NO_SERVICE");




    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);


    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    return;
}

/*******************************************************************************
  Module:   Mm_RcvRrmmRelInd
  Function:
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:

  1.��    ��   : 2010��05��14��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:AT2D19292,MM��Ѱ����������ʱ���յ�ϵͳ��Ϣ����״̬Ǩ��NORMAL״̬������GCFʧ��

*******************************************************************************/
VOS_VOID Mm_RcvRrmmRelInd()
{
    RRMM_REL_IND_STRU                   RrRelInd;

    /* ��дEST CNF��Ϣ���� */
    RrRelInd.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrRelInd.MsgHeader.ulMsgName        = RRMM_REL_IND;

    RrRelInd.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrRelInd.ulRrcConnStatus            = RRC_RRC_CONN_STATUS_ABSENT;
    RrRelInd.ulRelCause                 = RRC_REL_CAUSE_RR_NORM_EVENT;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrRelInd.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrRelInd.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*ֱ�ӵ���GMM������ϢRRMM_REL_IND�ĺ���*/
    /*lint -e961*/
    gaMmStateTable[33 - 1][g_MmGlobalInfo.ucState](&RrRelInd);
    /*lint +e961*/
    return;
}
/*******************************************************************************
  Module:   Mm_RcvRrmmEstCnf
  Function:
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:

*******************************************************************************/
VOS_VOID Mm_RcvRrmmEstCnf()
{
    RRMM_EST_CNF_STRU                   RrEstCnf;

    /* ��дEST CNF��Ϣ���� */
    RrEstCnf.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrEstCnf.MsgHeader.ulMsgName        = RRMM_EST_CNF;

    RrEstCnf.ulOpId                     = g_MmGlobalInfo.ucRrEstReqOpid;
    RrEstCnf.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrEstCnf.ulResult                   = RRC_EST_EST_CONN_FAIL;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrEstCnf.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrEstCnf.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*lint -e961*/
    gaMmStateTable[31][g_MmGlobalInfo.ucState](&RrEstCnf);
    /*lint +e961*/

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E21
  Function: ��WAIT_FOR_OUTGOING_MM_CONNECTION״̬��
            �յ�MMCMM_COVERAGE_LOST_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
 1.��    ��   : 2008��8��21��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:At2D05016,MMע��״̬�޸�
 2.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 3.��    ��   : 2011��11��22��
   ��    ��   : w00166186
   �޸�����   : DTS2011112101648,OOS�ȴ�ϵͳ��Ϣ��ʱ���������ӱ�־û����������º���AVAILABLE
                ��ʱ����ʱ��û�з�������
 4. ��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 5 .��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  6.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 7. ��    ��   : 2013��07��23��
    ��    ��   : l65478
    �޸�����   : DTS2013071809030,MMC�յ�RRMM_SUSPEND_REL_CNF��û�����̴������SYSCFG
 8. ��    ��   : 2013��9��12��
    ��    ��   : w00242748
    �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                 ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                 G��ԭС��ʱ��LAU
 9.��    ��   :2013��9��12��
   ��    ��   :z00161729
   �޸�����  :DTS2013082903019:֧��ss�ط�����
10.��    ��   : 2013��10��15��
   ��    ��   : l65478
   �޸�����   : DTS2013102501008���յ�����ģʽ���ó��Զ�����ģʽ��û�з���ע��
11.��    ��   : 2014��04��29��
   ��    ��   : y00245242
   �޸�����   : eCall��Ŀ�޸�
12.��    ��   : 2014��6��4��
   ��    ��   : w00167002
   �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU
 13.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
 14.��    ��   : 2015��3��20��
    ��    ��   : w00167002
    �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                 ���з�װ��
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E21(VOS_VOID *pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg))
    {
        return;
    }

    switch (g_MmGlobalInfo.ucState)
    {
        case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        case WAIT_FOR_OUTGOING_MM_CONNECTION:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
            break;
        case LOCATION_UPDATING_INITIATED:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
             || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* ��U2״̬�����浱ǰ��LAI��Ϣ */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );
                Mm_ComDelLai();
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

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

                Mm_TimerStart(MM_TIMER_T3211);
            }
            break;
        case LOCATION_UPDATE_REJECTED:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* ͣT3218                                  */
            Mm_ComDelRandRes();
            Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            break;
        case WAIT_FOR_NETWORK_COMMAND:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* ͣT3218                                  */
            Mm_ComDelRandRes();
            break;
        case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            break;
        default:
            break;
    }

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
     && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* �����������ǰ��״̬,�������ɹ��������ж�LAI�Ƿ�ı� */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    Mm_ComProcCauseClear();

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E21:INFO: MmServiceState is MM_NO_SERVICE");

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetStaOfRcvXXEstReq_CSFB
 ��������  : CSFB�����л�ȡ���ӽ���ǰ��״̬
 �������  : ��
 �������  : ���ӽ���ǰ��MM״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��9��13��
   ��    ��   : s46746
   �޸�����  : �����ɺ���
 2.��    ��   :2013��9��6��
    ��    ��   :z00161729
    �޸�����  :DTS2013083007549:G fast return���ܿ�����ap����4���·�����ҵ���ѯ��3�β�ѯʧ�ܣ�mm״̬Ϊattempt to updateά������

*****************************************************************************/
VOS_UINT8 NAS_MM_GetStaOfRcvXXEstReq_CSFB(VOS_VOID)
{
    VOS_UINT8                           ucState;
    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_NO_CELL_AVAILABLE:
        case MM_IDLE_PLMN_SEARCH:
        case LOCATION_UPDATING_PENDING:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_WAIT_FOR_ATTACH:
            if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
            {
                ucState = MM_IDLE_NO_IMSI;
            }
            else if ( ( MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                   && ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
            {
                ucState = MM_IDLE_LIMITED_SERVICE;
            }
            else if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
            {
                ucState = MM_IDLE_LOCATION_UPDATE_NEEDED;
            }
            else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                  || (VOS_TRUE == ulLaiChangeFlag))
            {
                ucState = MM_IDLE_ATTEMPTING_TO_UPDATE;
            }
            else
            {
                ucState = MM_IDLE_NORMAL_SERVICE;
            }
            break;

        default:
            ucState = g_MmGlobalInfo.ucState;
            break;
    }

    return ucState;
}
#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MM_ResponseLmmPagingInd_CSFB
 ��������  : MT CSFB������ӦѰ���Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��14��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2012��09��01��
   ��    ��   : s46746
   �޸�����   : DTS2012091304207:DCM�ⳡ����,csfb������w���Ҷϵ绰u2l�л���mm״̬����δ��Ӧsuspend ind�������л�ʧ��

*****************************************************************************/
VOS_VOID NAS_MM_ResponseLmmPagingInd_CSFB(VOS_VOID)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;

    Mm_TimerStop(MM_TIMER_T3211);

    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }
    
    stCmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();                /* �洢CKSN                                 */


    NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())                /* ��ǰ���� GSM ���� */
    {
        /* �� GAS ���ͽ��� RR ���� */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS ���� */
    {
        g_MmGlobalInfo.ucPagingCause = RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL;
        Mm_ComMsgPagingRspSnd( &stCmRspRsp );                                   /* ��䲢���� PAGING RESPONSE ��Ϣ          */
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */

    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* ��������TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MM_PerformBufferedSsService
 ��������  : �������SSҵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��14��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��01��
   ��    ��   : s46746
   �޸�����   : DTS2012091304207:DCM�ⳡ����,csfb������w���Ҷϵ绰u2l�л���mm״̬����δ��Ӧsuspend ind�������л�ʧ��

*****************************************************************************/
VOS_VOID NAS_MM_PerformBufferedSsService(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;                               /* Ҫ���͵�CM SERVICE REQ��Ϣ               */
    VOS_UINT16                          usMsgSize = 0;                          /* ��Ϣ����,���ֽ�Ϊ��λ                    */
    VOS_UINT8                          *pucCmSvcReq = 0;                        /* Ҫ���͵�CM SERVICE REQ��Ϣָ��           */


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

    Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);      /* ���CM SERVICE REQUEST�ṹ��             */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );       /* ���CM SERVICE REQUEST ��Ϣ              */
    if (VOS_NULL_PTR == pucCmSvcReq)
    {                                                                           /* ��Ϣ����ʧ��                             */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_PerformBufferedSsService: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                                 /* ����                                     */
    }
    else
    {                                                                           /* ��Ϣ�����ɹ�                             */
        Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
           MM_FALSE, usMsgSize, pucCmSvcReq);                                   /* ������Ϣ                                 */
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                        /* �ͷ�CM SERVICE REQUEST ��Ϣ�ṹ��        */
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        (VOS_UINT8)g_MmSsEstReq.ulTi;                                           /* ��¼���ڽ�����MM���ӵ�TI                 */
    g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;             /* ��¼���ڽ�����MM���ӵ�PD                 */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* ֪ͨMMC��CS���ҵ���Ѿ�����              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼Ǩ��֮ǰ��״̬                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MM_RcvSysInfo_CSFB
 ��������  : CSFB�����յ�ϵͳ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��8��
   ��    ��   : w00167002
   �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:TC�����ձ�������������ΪLAIδ����
                �ı䣬��ֱ�ӽ���ҵ��
 3.��    ��   : 2012��4��7��
   ��    ��   : W00166186
   �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR EMERGENCY CALL ����
 4.��    ��   : 2012��8��14��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 5.��    ��   : 2012��09��01��
   ��    ��   : s46746
   �޸�����  : DTS2012091304207:DCM�ⳡ����,csfb������w���Ҷϵ绰u2l�л���mm״̬����δ��Ӧsuspend ind�������л�ʧ��
 6.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
 7.��    ��   : 2012��10��25��
   ��    ��   : z00161729
   �޸�����   : DTS2012102305986:csfb��gu access barС���޷������������
 8.��    ��   : 2012��12��10��
   ��    ��   : w00167002
   �޸�����   : DTS2012112603831:L��ע��ɹ��󣬷���ATD117,CSFB���ΪSERVICE
                FAILURE��������W���յ�ϵͳ��Ϣ��ֱ�ӷ����˵绰ҵ���ڵ绰
                ҵ������У���ʾ��ǰ������״̬Ϊ������״̬���źŸ���Ϊ�ա�
                ����ڵ绰ҵ��ʱ����Ҫ����CREG״̬�ϱ�֪ͨ��AP�ࡣ
  9.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                 �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                 rau req�д�follow on��־,����ȷЭ������
 10.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������

  11.��    ��   : 2014��12��2��
    ��    ��   : w00167002
    �޸�����   : DTS2014092806342:CSFB��G��LAUʧ�ܣ�����������CSMT��־��ʱ����
                 ���Ӻ�ͨ�ʡ�
  12.��    ��   : 2015��6��8��
     ��    ��   : z00161729
     �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
  13.��    ��   : 2015��10��16��
     ��    ��   : j00174725
     �޸�����   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_RcvSysInfo_CSFB(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    VOS_UINT32                                              ulLaiChangeFlag;

    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus  = NAS_MML_GetCsUpdateStatus();

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();

    /* CSFB ���̣����LAI�ı䣬��LAU, ���LAIδ�䣬��ֱ�ӷ���ҵ�� */
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:

            /* 3GPP 24008 4.4.1:
               indicating to the network that the MS, configured to use CS fallback
               and SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell in
               NMO II or III, after intersystem change from S1 mode to Iu or A/Gb mode,
               the TIN indicates "GUTI" and the location area of the current cell is the
               same as the stored location area; NOTE1:The location updating procedure
               can be delayed when the intersystem change is due to CS fallback.
               In this case, the MS has to remember that it has to perform a
               location updating procedure after the RR connection is released,
               if the MS is still in GERAN/UTRAN.*/

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {

                /* ��ǰ���ڻ����CCҵ�񣬷���CCҵ�� */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* ��¼�յ���������ʱ��״̬                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* ��MMC����MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                    return;
                }

                /* �޻����CCҵ�񣬽����쳣���� */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* ����LAU����,LAU�ɹ������CSFB������ */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            Mm_ComLuOnly();

            return ;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                /* ��ǰ���ڻ����SSҵ�񣬷��𻺴��SSҵ�� */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                {
                    /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* ��¼�յ���������ʱ��״̬                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* ��MMC����MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_PerformBufferedSsService();
                    return;
                }

                /* �޻����CCҵ�񣬽����쳣���� */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:SS BUFFER SERVICE NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                /* �ͷ��Ѿ�����MM���ӵ�ҵ��:��Ӧ���������ݿ��ش򿪣�ssҵ������У������UE���P̬��W2L��ѡ��MMC��������W */
                NAS_MM_RelAllExistSsConn(SSA_SS_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

                /* LAIδ�ı䣬����Ҫ��LAU��״̬Ǩ�Ƶ�MM_IDLE_NORMAL_SERVICE */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                return;
            }

            /* ����LAU����,LAU�ɹ������CSFB��SSҵ�� */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:

            if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
            {
                /* ����LAUЯ��CSMT��־ */
                NAS_MM_SetCsfbMtLauFlg(VOS_TRUE);
            }

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);       /* ��MMC����MMCMM_LU_RESULT_IND */

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());            /* CREG״̬Ǩ�� */

                /* ��GU�£��ظ�paging response */
                NAS_MM_ResponseLmmPagingInd_CSFB();

                /* ��¼״̬ΪCSFB MT�ѷ���paging response */
                NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND,
                                          NAS_MML_REG_FAIL_CAUSE_NULL);

                /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                return;
            }

            /* �޸�Ϊ���յ�CSFBѰ��ʱ��������ʱ�� */

            /* ����LAU���� */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            /* ��¼״̬ΪCSFB MT����LAU���� */
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_TRAG_LAU,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
            /* ���lai��ͬ��ע����������lauֱ�ӷ���������� */
            if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
            {
                /* NV����lai�ı�����lau�ٽ��н������У�����LAU���� */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

                Mm_ComLuOnly();
                return;
            }

            /* ��ǰ���ڻ����CCҵ�񣬷���CCҵ�� */
            if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
            {
                /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* ��¼�յ���������ʱ��״̬                 */

                /* ������CSFB��GU,����Ҫ��LAUʱ���ϱ�CS��ע��״̬ */
                NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist();

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }

            /* �޻����CCҵ�񣬽����쳣���� */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
            return;

         default:
            break;
    }

    return;
}
#endif

/*******************************************************************************
  Module:   Mm_Cell_S3_E5
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�MMCMM_SYS_INFO_IND�Ĵ���
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.10  �°�����
      2.  s46746  05-09-27  modify for HSS 4100 V200R001
      3. s46746  2006-07-27 �������ⵥA32D03975�޸�
      4.��    ��   : 2006��10��6��
        ��    ��   : s46746
        �޸�����   : ���ⵥ�ţ�A32D05960
      5.��    ��   : 2007��1��26��
        ��    ��   : liurui id:40632
        �޸�����   : �������ⵥ�ţ�A32D08577
      6.��    ��   : 2007��04��20��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D10235
      7.��    ��   : 2007��09��05��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�AT2D01490
      8.��    ��   : 2008��08��21��
        ��    ��   : ouyangfei id:00132663
        �޸�����   : ���ⵥ�ţ�AT2D04652,��С���ı�ʱ��ֹͣ��ʱ�� T3211
      9.��    ��   : 2008��09��03��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
      10.��    ��   : 2008��11��22��
        ��    ��   : l65478
        �޸�����   : ���ⵥ�ţ�AT2D06900,mmע��״̬�޸�
      11.��    ��   : 2009��10��03��
        ��    ��   : o00132663
        �޸�����   : ���ⵥ�ţ�AT2D14942,��ϵͳС����ѡ�ɹ������ϱ����޷��񣬵�ע��������ٸ��·���״̬��
      12.��    ��   : 2011��7��16��
         ��    ��   : h44270
         �޸�����   : V7R1 PhaseII�׶ε�����ע������
      13.��    ��   : 2011��6��3��
         ��    ��   : c00173809
         �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011060102833,�ӽ�ֹPLMN�л����ǽ�ֹPLMNʱ���ǽ�ֹ���������ģʽΪIʱ��û�з�������RAU��������Э�� ��
      14.��    ��   : 2011��10��27��
         ��    ��   : s46746
         �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
      15.��    ��   : 2010��4��09��
         ��    ��   : z00161729
         �޸�����   : ���ⵥ��DTS2011032601795:����ģʽII��MM������LAU�����������ʧ��,
                      T3211����ʱ����С����ѡ��δ����LAU�����ǵ�T3212��ʱ��ŷ���
      16.��    ��   : 2011��7��14��
         ��    ��   : k66584
         �޸�����   : ���ⵥ��:DTS2011070603156,ϵͳ��ϢָʾPS��bar,LAIû�б仯,
                      ����T3212ǰ�����ж�����,����ģʽI�²�����;�������������T3212 ��
      17.��    ��   : 2012��02��29��
         ��    ��   : l00130025
         �޸�����   : DTS2012022206186:������LAU,��ע��ɹ�ʱ����Ҫͬ��ע��״̬��AS
      18.��    ��   : 2012��03��17��
         ��    ��   : s46746
         �޸�����   : DTS2012030705720:RAI������ģʽ�����ı�,��Ҫ����LAU����
      19.��    ��   : 2012��2��15��
         ��    ��   : z00161729
         �޸�����   : V7R1C50 ֧��CSFB�����޸�
      20.��    ��   : 2012��2��15��
         ��    ��   : w00166186
         �޸�����   : CSFB&PPAC&ETWS&ISR ����
      19.��    ��   : 2012��05��21��
        ��    ��   :  z40661
        �޸�����   : DTS2012052308001:��L��ѡ��G�󷴸�����LAU
     22.��    ��   : 2012��10��22��
        ��    ��   : t00212959
        �޸�����   : DTS2012101907218:NAS�����㷢��LAU����ʱ��Establishment cause����Э��дΪRegistration
     23.��    ��   : 2012��11��15��
        ��    ��   : t00212959
        �޸�����   : DTS2012041801803:CFSB��FLAС����������ʧ��
     24.��    ��   : 2012��12��24��
        ��    ��   : l65478
        �޸�����   : DTS2012122402486:��ϵͳ��ѡ������T3212��ʱ��ѡ������û�з�������LU
     25.��    ��   : 2013��1��23��
        ��    ��   : W00176964
        �޸�����   : DTS2013012301238:GCF 26.7.4.3.4����ʧ��
     26.��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
     27.��    ��   : 2013��05��15��
        ��    ��   : s46746
        �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
     28.��    ��   : 2013��9��12��
        ��    ��   : w00242748
        �޸�����   : DTS2013090308589:MM�����ؽ�״̬ʱ���յ�CC REL REQ����Ǩ��
                    ԭ״̬(IDLE NORMAL SERVICE)��δ����T3212��ʱ�������������ػ�
                    G��ԭС��ʱ��LAU
     29.��    ��   :2013��9��23��
        ��    ��   :w00242748
        �޸�����   :DTS2013091407626:W��UE���У�δ�յ����ཨ��CNFǰ�������ض���G��δ����LAU
     30.��    ��   : 2014��04��1��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
     31.��    ��   : 2015��3��20��
        ��    ��   : w00167002
        �޸�����   : DTS2015030305199:LAU����ʧ�ܴﵽ��������ʹ��NV�ж��Ƶ�T3212ʱ��,T3212����ͳһ
                     ���з�װ��
     32.��    ��   : 2015��5��21��
        ��    ��   : b00269685
        �޸�����   : ��������ҪLAU���򲻴�����
******************************************************************************/
VOS_VOID Mm_Cell_S3_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrentNetRatType;
    VOS_UINT8                           ucT3211RunFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg  = Mm_ComJudgeCsServExist();

    /* ȡ��CSFB�Ƿ���ڵı�־ */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    enCurrentNetRatType = NAS_MML_GetCurrNetRatType();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    ucT3211RunFlg       = VOS_FALSE;

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ( (VOS_TRUE == ulLaiChangeFlag) ||
        ((g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE) && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
        {
            ucT3211RunFlg = VOS_TRUE;
            Mm_TimerStop(MM_TIMER_T3211);
        }
    }
    /* <==AT2D01490 */

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

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
      )
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    {                                                                           /* ���ΪA+I,�Ҳ�������B��A+II����ĳ���    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
        /* RACΪ0�ĳ��� */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, begin */
            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-3, end */
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* ����LU����                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                if ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
                            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
        else
        {                                                                       /* RAC������0                               */
            if ( VOS_TRUE == ulLaiChangeFlag )
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* ��¼ǰ״̬                               */
                Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
            }
        }
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

        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComNetModeChange();
        }
        else
        {
            if ( VOS_TRUE == ulLaiChangeFlag )
            {                                                               /* ���LAI��                                */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                if (VOS_TRUE == ucT3211RunFlg)
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* A+0ģʽ,PS��֧��ʱ,LAI���ı�ʱ,3212��ʱ����LAU����Ӧ�ٴ��յ�ϵͳ��Ϣ��Ӧ��
                       �ٴη���LAU */
                    if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                     && (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                                        MM_IE_LUT_PERIODIC_UPDATING;            /* ����LU����                               */
                        Mm_ComLuOnly();                                         /* ����LU REQ                               */
                        return;
                    }

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }

                if (enCurrentNetRatType != g_MmGlobalInfo.enPreRatType)
                {
                    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */

                    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

                    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
                    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                            & MM_WAIT_CS_ATTACH))
                    {
                        NAS_MM_SndMmcAttachCnf();
                    }
                    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
                }


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            }
        }
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-2, end */
    }

    if ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
     && ((MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
      || (VOS_TRUE == ulEmergencyCallFlg)))
    {
        Mm_DealWithBuffMsg();
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S3_E9
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�GMMMM_IMSI_DETACH_INITIATION�Ĵ���
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2. ��    ��   : 2008��09��03��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
       3.��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* ��¼ǰ״̬                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E11
  Function: ��MM IDLE NORMAL SERVICE״̬���յ�GMMMM_GPRS_DETACH_INITIATION�Ĵ���
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��     2003.12.09  �°�����
      2. ��    ��   : 2008��09��03��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ�ţ�AT2D05403,mmע��״̬�޸�
       3.��    ��   : 2013��05��15��
         ��    ��   : s46746
         �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E11(VOS_VOID *pMsg)
{
    GMMMM_GPRS_DETACH_INITIATION_STRU   *pGprsDetachInit;

    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    pGprsDetachInit = (GMMMM_GPRS_DETACH_INITIATION_STRU*)pMsg;

    if ( GMMMM_GPRS_DETACH_NORMAL == pGprsDetachInit->enDetachType )
    {
        ;                                                                       /* �մ���                                   */
    }
    else
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* ��¼ǰ״̬                               */
        Mm_ComSetMmState(IMSI_DETACH_PENDING);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
    }
}

/*****************************************************************************
 �� �� ��  : Mm_Cell_S32_E32
 ��������  : ����״̬����est cnf��Ϣ��������est req�ͽ����suspend ind��Ϣ�Գ�ĳ���
 �������  : pRcvMsg -��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log

*****************************************************************************/
VOS_VOID Mm_Cell_S32_E32(
    VOS_VOID                           *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
    }
    else
    {
        if (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            if (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
            {
                /* CC�����RR���ӵĽ���, ֪ͨCC����ʧ��             */
                Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
            {
                /* SS�����RR���ӵĽ��� ��֪ͨSS,MM���ӽ���ʧ��      */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
            {
                /* SMS�����RR���ӵĽ��� ,֪ͨSMS,MM���ӽ���ʧ��      */
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else
            {
                /* û�����ڽ�����MM���ӣ������� */
            }

            /* ҵ�񴥷��Ľ������� */
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
            {

                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

            /* �����Ϣ�����־ */
            NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

            g_MmGlobalInfo.ucSuspendPreState = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
        }
    }

    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

