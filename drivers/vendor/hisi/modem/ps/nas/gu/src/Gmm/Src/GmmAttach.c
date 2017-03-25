/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmAttach.c
  Description   : GMM ATTACH������ش�����Դ�ļ�
  Function List :
    01.   Gmm_FillRaiForRcv
    02.   Gmm_AttachRauAcceptJudgeRai
    03.   Gmm_FillPtmsiSignature
    04.   Gmm_FillRaiForSnd
    05.   Gmm_FillPtmsi
    06.   Gmm_FillDrxPara
    07.   Gmm_AttachRequestMsgMake
    08.   Gmm_AttachCompleteMsgMake
    09.   Gmm_DelPsLocInfoUpdateUsim
    10.   Gmm_AttachRejectCause3
    11.   Gmm_AttachRejectCause11
    12.   Gmm_AttachRejectCause11
    13.   Gmm_AttachRejectCause12
    14.   Gmm_AttachRejectCause14
    15.   Gmm_AttachAttemptCounter
    16.   Gmm_RcvAttachRejectMsg
    17.   Gmm_AttachRauAcceptCause16
    18.   Gmm_AttachRauAcceptCause2
    19.   Gmm_SaveTimerValue
    20.   Gmm_AttachAcceptResolveIe
    21.   Gmm_AttachAcceptGprsOnly
    22.   Gmm_AttachAcceptCombined
    23.   Gmm_AttachAcceptHandle
    24.   Gmm_SndAttachReq
    25.   Gmm_AttachInitiate
    26.   Gmm_RcvSmEstablishReq
    27.   Gmm_RcvSmEstablishReq
    28.   Gmm_RcvAttachAcceptMsg
    29.   Gmm_RcvMmcGmmAttachReq
    30.   Gmm_RcvMmcGmmAttachReq_RegInit
    31.   Gmm_RcvMmcGmmAttachReq_RauInit
    32.   Gmm_RcvMmcGmmAttachReq_ServReqInit
    33.   Gmm_RcvMmcGmmAttachReq_DeregNmlServ
    34.   Gmm_RcvMmcGmmAttachReq_DeregLimitServ
    35.   Gmm_RcvMmcGmmAttachReq_RegLimitServ
    36.   Gmm_RcvMmcGmmAttachReq_DeregAtmpToAtch
    37.   Gmm_RcvMmcGmmAttachReq_RegNmlServ
    38.   Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdt
    39.   Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm
    40.   Gmm_AttachAcceptMsgJudge
  History       :
    1.  ��־��  2003.12.08  �¹�����
    2.  s46746  2006.04.20  �������ⵥA32D03221�޸�
    3.  s46746  2006.04.28  �������ⵥA32D03507�޸�
    4.  l40632  2006.04.29  �������ⵥA32D03506�޸�
    5.  x51137 2006/4/28 A32D02889
    6.  l40632  2006.05.20  �������ⵥA32D03865�޸�
    7.  l40632  2006.05.29  �������ⵥA32D04010�޸�
    8.  l40632  2006.06.19  �������ⵥA32D04282�޸�
    9. ��    ��   : 2006��9��9��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D05604
    10.x51137 2006/11/3 A32D06511
    11.��    ��   : 2006��11��7��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D06823
    12.��    ��   : 2006��11��8��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D06867
    13.��    ��   : 2007��1��10��
       ��    ��   : x51137
       �޸�����   : A32D08308
    14.��    ��   : 2007��1��10��
       ��    ��   : x51137
       �޸�����   : A32D08318
    15.��    ��   : 2007��02��01��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D08656
    16.��    ��   : 2007��04��20��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D10240
    17.��    ��   : 2007��06��16��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D11726
    18.��    ��   : 2007��07��05��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D11970,�����ϢIE����spareλ�������.
    19.��    ��   : 2007��11��12��
       ��    ��   : luowei id:39007
       �޸�����   : �������ⵥA32D13044,GSM����,ATTACHʧ��5��,֪ͨMM����һ��LAU
                    ��ʱ������Ϊ��GMM����ATTACH COMPLETE֮��
    20.��    ��   : 2007��12��04��
       ��    ��   : s46746
       �޸�����   : 1.GMMģ�����ATTACH��RAUʱ�������ʱ����������������
                      �ᵼ��LLC��ATTACH��RAU�ӳٷ��ͣ�ʹ��ATTACH��RAUʱ�������
                    2.GMM�ڽ���RAU����ʱ�����DRX�������ı䣬����������Ϣ��
                      ��DRX������������SGSN��RAUʱ�����ܵ������಻ʶ��UE��DR
                      X������  ʹ��RAU���ܳɹ���
    21.��    ��   : 2007��12��12��
       ��    ��   : luojian id:107747
       �޸�����   : �������ⵥ�ţ�A32D13866,Ŀǰ����ģʽIIIʱֻ֧��CS����Ҫͬʱ֧��PS
    22.��    ��   : 2007��12��15��
       ��    ��   : l00107747
       �޸�����   : ���ⵥ��:A32D13897,SIM����W�½���GMM ATTACH����CKSN��Ϊ��Ч
    23.��    ��   : 2007��12��21��
       ��    ��   : l00107747
       �޸�����   : ���ⵥ��:A32D13951
    24.��    ��   : 2007��12��28��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
    25.��    ��   : 2008��7��2��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�AT2D03900,GMM��ATTACH ACCEPT�������ʱû�����FOLLOW ON��־
    26.��    ��   : 2008��7��24��
       ��    ��   : luojian 00107747
       �޸�����   : �������ⵥ�ţ�AT2D04627/AT2D04237,
                    ATTEMPT TO UPDATE/ATTACH ״̬��CM������
    27.��    ��   : 2008��7��25��
       ��    ��   : luojian 00107747
       �޸�����   : �������ⵥ��AT2D04142/AT2D04677,�޸�RAU ATTEMPT��������5�εĴ���
    28.��    ��   : 2008��10��20��
       ��    ��   : o00132663
       �޸�����   : ���ⵥ��:AT2D06266, ���ӶԲ�֧��CELL NOTIFICATION�Ĵ���
    29.��    ��   : 2009��02��13��
       ��    ��   : o00132663
       �޸�����   : ���ⵥ��:AT2D08906,��TA ��֤�����ⳡ����-HK��smartone UEû�д���attach״̬,�ͷ�����ҵ������.
    30.��    ��   : 2009��05��14��
       ��    ��   : h44270
       �޸�����   : ���ⵥ��:AT2D11898/AT2D11828,��IDLE̬�·���PS����ţ�û�а���ATTACH ACCEPT��Ϣ��Radio Priority for SMS��������Դ
    31.��    ��   : 2009��6��30��
       ��    ��   : s46746
       �޸�����   : AT2D12561,3G2����GPRS��δ�������ܣ�NASָ�ɲ�2�����㷨�󣬲�2���������ݽ����˼���
    32.��    ��   : 2009��08��24��
       ��    ��   : x00115505
       �޸�����   : AT2D14023,����GCF����44.2.2.1.9ʧ��
    33.��    ��   : 2009��09��30��
       ��    ��   : x00115505
       �޸�����   : AT2D14857,פ����FPLMN�ϣ�GMM������״̬�޸�ΪGU3��
    34.��    ��   : 2009��11��03��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ�ţ�AT2D15222,��������������ע��
    35.��    ��   : 2010��11��30��
       ��    ��   : h44270
       �޸�����   : ���ⵥ��:DTS2010112400547/DTs010112303273,û��ָ���µ�TLLI,����PS��ע��ʧ��
    36.��    ��   : 2013��07��11��
       ��    ��   : l00208543
       �޸�����   : ��Ӻ�����STK�ϱ�Network Rejection Event
*******************************************************************************/
#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "GmmCasMain.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasCommDef.h"
#include "NasGmmProcLResult.h"
#endif

#include "NasUtranCtrlInterface.h"
#include "NasMmlCtx.h"
#include "NasUsimmApi.h"

 /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
#include "NasStkInterface.h"
 /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */
#include "NasMmlLib.h"

#include "NasGmmSndOm.h"

#include "NasCcIe.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_ATTACH_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

extern VOS_UINT16 NAS_MMC_GetUserSetGsmBand(VOS_VOID);


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MNTN_ServiceUnavailableType
 ��������  : �ж�RAU��LAU������ܾ���ԭ��ֵ�Ƿ񴥷�д�¼�
 �������  : VOS_UINT8   ucCause            RAU��LAU������ܾ���ԭ��ֵ
 �������  : VOS_BOOL   *pbEventRequired    �Ƿ񴥷�д�¼�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��14��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MNTN_ServiceUnavailableType(
    VOS_UINT16                          usCause,
    VOS_BOOL                           *pbEventRequired
)
{
    switch(usCause)
    {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:

            /* ���ϴ���ԭ��ֵ������Ҫֱ�Ӽ�¼�¼���:
            UE��Ϊ����ԭ��ֵ����ע��ʧ����Ҫ��ѡ��Żᷢ���µ�ע������ */
            *pbEventRequired = VOS_TRUE;
            break;
        default:
            *pbEventRequired = VOS_FALSE;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_StorePsUnavailableInfo
 ��������  : CS�򲻿�����Ϣ�洢
 �������  : VOS_UINT8   ucCause            RAU��LAU������ܾ���ԭ��ֵ
 �������  : NAS_MNTN_PS_UNAVAILABLE_INFO_STRU  *pstPsUnavailableInfo
                                            PS�򲻿�����Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��17��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_StorePsUnavailableInfo(
    VOS_UINT8                           ucCause,
    NAS_MNTN_PS_UNAVAILABLE_INFO_STRU  *pstPsUnavailableInfo
)
{
    VOS_UINT32                          ulPos;

    /* �¼���¼��־����һ: ���Դ��������� */
    if (g_GmmRauCtrl.ucRauAttmptCnt > NAS_MNTN_PS_ATTEMPT_MAX)
    {
        return;
    }

    /* �¼���¼��־���ö�: ע��ʧ��ԭ��ֵָʾ��ǰפ��λ�޷��ṩ������ѡ���ٳ���ע�� */
    NAS_MNTN_ServiceUnavailableType(ucCause, &pstPsUnavailableInfo->bRecordRequired);

    /* �쳣����ֱ���˳�һ: ע��ʧ��ԭ��ֵû��ָʾ��ǰפ��λ�޷��ṩ����
       ��ע��ʧ�ܼ�����ֵΪ0 */
    if ((VOS_TRUE != pstPsUnavailableInfo->bRecordRequired)
     && (0 == g_GmmRauCtrl.ucRauAttmptCnt))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_StorePsUnavailableInfo: Error Counter.");
        return;
    }

    /* �쳣����ֱ���˳���: ע��ʧ�ܼ�����ֵ�������ֵ */
    if (NAS_MNTN_PS_ATTEMPT_MAX == pstPsUnavailableInfo->ucTimes)
    {
        pstPsUnavailableInfo->bRecordRequired = VOS_TRUE;
    }

    /* ��¼ע��ʧ��ԭ��ֵ��ȫ�ֱ��� */
    if (0 != g_GmmRauCtrl.ucRauAttmptCnt)
    {
        ulPos = g_GmmRauCtrl.ucRauAttmptCnt - 1;
    }
    else
    {
        ulPos = 0;
    }

    pstPsUnavailableInfo->aulCause[ulPos]= ucCause;
    pstPsUnavailableInfo->ucTimes = g_GmmRauCtrl.ucRauAttmptCnt;

    return;
}

/*******************************************************************************
  Module   : Gmm_FillRaiForRcv
  Function : ���տ���Ϣ�е�RAI��д��ȫ�ֱ���
  Input    : GMM_RAI_STRU *pRaiDes  ָ��GMM_RAI_STRU�ṹ��ָ�����
             VOS_UINT8        *pRaiSrc  ָ��RAI��ָ�����
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
*******************************************************************************/
VOS_VOID Gmm_FillRaiForRcv(
                       GMM_RAI_STRU *pRaiDes,                                   /* ָ��GMM_RAI_STRU�ṹ��ָ�����           */
                       VOS_UINT8        *pRaiSrc                                    /* ָ��RAI��ָ�����                        */
                       )
{
    /* �洢MCC */
    pRaiDes->Lai.PlmnId.aucMccDigit[0] = (VOS_UINT8)(pRaiSrc[0] & 0x0F);
    pRaiDes->Lai.PlmnId.aucMccDigit[1] = (VOS_UINT8)(pRaiSrc[0] >> 4);
    pRaiDes->Lai.PlmnId.aucMccDigit[2] = (VOS_UINT8)(pRaiSrc[1] & 0x0F);

    /* �洢MNC */
    pRaiDes->Lai.PlmnId.ucMncCnt = 3;
    pRaiDes->Lai.PlmnId.aucMncDigit[2] = (VOS_UINT8)(pRaiSrc[1] >> 4);
    if (0xF0 == (pRaiSrc[1] & 0xF0))
    {                                                                           /* 2��MNC                                   */
        pRaiDes->Lai.PlmnId.ucMncCnt = 2;
    }
    pRaiDes->Lai.PlmnId.aucMncDigit[0] = (VOS_UINT8)(pRaiSrc[2] & 0x0F);
    pRaiDes->Lai.PlmnId.aucMncDigit[1] = (VOS_UINT8)(pRaiSrc[2] >> 4);

    /* �洢LAC */
    pRaiDes->Lai.aucLac[0] = pRaiSrc[3];
    pRaiDes->Lai.aucLac[1] = pRaiSrc[4];

    /* �洢RAC */
    pRaiDes->ucRac = pRaiSrc[5];

    return;
}

/*****************************************************************************
�� �� ��  : NAS_GMM_JudgeLaiIfLegal
��������  : �ж�RAU ACCPECT��Ϣ�е�LAI�Ƿ�Ϸ�
�������  : pMsg - ָ��NAS_MSG_STRU�ṹ��ָ��
�������  : ��
�� �� ֵ  : VOS_TRUE - �Ϸ�
            VOS_FALSE - �Ƿ�
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2010��11��28��
    ��    ��   : z00161729
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 NAS_GMM_JudgeLaiIfLegal(NAS_MSG_FOR_PCLINT_STRU *pMsg)
{
    if (((pMsg->aucNasMsg[4] & 0x0F) > 9)
    || (((pMsg->aucNasMsg[4] >> 4 ) & 0x0F) > 9)
    || ((pMsg->aucNasMsg[5] & 0x0F) > 9)
    || ((pMsg->aucNasMsg[6] & 0x0F) > 9)
    || (((pMsg->aucNasMsg[6] >> 4) & 0x0F) > 9))
    {                                                                           /* MCC��MNC��ȡֵ����                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_JudgeLaiIfLegal:WARNING: IE\"RAI\" is invalid in RAU ACCEPT");
        return VOS_FALSE;
    }

    if ((((pMsg->aucNasMsg[5] >> 4) & 0x0F) > 9)
     && (((pMsg->aucNasMsg[5] >> 4) & 0x0F) != 0x0F))
    {                                                                           /* MNC3ȡֵ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_JudgeLaiIfLegal:WARNING: IE\"MNC3\" is invalid in RAU ACCEPT");
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*******************************************************************************
  Module   : Gmm_AttachRauAcceptJudgeRai
  Function : �ж��յ���ATTACH & RAU ACCEPT��Ϣ�е�RAI��ϵͳ��Ϣ�е�RAI�Ƿ�һ��
  Input    : NAS_MSG_STRU *pMsg  ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE   ��ͬ
             GMM_FALSE  ��ͬ
  History  :
    1. ��־��  2003.12.09  �¹�����
    2. ��    ��   : 2010��5��10��
       ��    ��   : z00161729
       �޸�����  : DTS2010112604710:������LAU accpet��Ϣ�����LAI��Ϣ�ı��ҺϷ����������Ӧȫ�ֱ�����ֵ
*******************************************************************************/
VOS_UINT8 Gmm_AttachRauAcceptJudgeRai(
                                  NAS_MSG_FOR_PCLINT_STRU *pMsg
                                  )
{
    GMM_RAI_STRU    RaiTemp;                                                    /* ����GMM_RAI_STRU���͵���ʱ����           */
    VOS_UINT8           ucRet = GMM_FALSE;                                          /* ���ڻ�����ֵΪFALSE                      */

    NAS_MML_RAI_STRU                       *pstLastSuccRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ���е���ATTACH����                   */
        Gmm_FillRaiForRcv(&RaiTemp, &(pMsg->aucNasMsg[5]));                     /* ���ú����洢RAI����ʱ������              */
    }
    else
    {                                                                           /* ��ǰ���е���RAU����                      */
        Gmm_FillRaiForRcv(&RaiTemp, &pMsg->aucNasMsg[4]);                       /* ���ú����洢RAI����ʱ������              */
    }
    if (GMM_TRUE == Gmm_Com_CmpPlmnid(&RaiTemp.Lai.PlmnId))
    {                                                                           /* PLMN IDһ��                              */
        if ((RaiTemp.Lai.aucLac[0]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0])
            && (RaiTemp.Lai.aucLac[1]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1]))
        {                                                                       /* LACһ��                                  */
            if (RaiTemp.ucRac == g_GmmGlobalCtrl.SysInfo.Rai.ucRac)
            {                                                                   /* RACһ��                                  */
                pstLastSuccRai->ucRac               = RaiTemp.ucRac;
                pstLastSuccRai->stLai.aucLac[0]     = RaiTemp.Lai.aucLac[0];
                pstLastSuccRai->stLai.aucLac[1]     = RaiTemp.Lai.aucLac[1];
                NAS_GMM_ConvertPlmnIdToMmcFormat(&(RaiTemp.Lai.PlmnId),
                    &(pstLastSuccRai->stLai.stPlmnId));

                ucRet = GMM_TRUE;
            }
        }
    }

    if (GMM_FALSE == ucRet)
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            if (VOS_TRUE == NAS_GMM_JudgeLaiIfLegal(pMsg))
            {
                pstLastSuccRai->ucRac               = RaiTemp.ucRac;
                pstLastSuccRai->stLai.aucLac[0]     = RaiTemp.Lai.aucLac[0];
                pstLastSuccRai->stLai.aucLac[1]     = RaiTemp.Lai.aucLac[1];
                NAS_GMM_ConvertPlmnIdToMmcFormat(&(RaiTemp.Lai.PlmnId),
                    &(pstLastSuccRai->stLai.stPlmnId));
            }
        }
        else
        {
            pstLastSuccRai->ucRac               = g_GmmGlobalCtrl.SysInfo.Rai.ucRac;
            pstLastSuccRai->stLai.aucLac[0]     = g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0];
            pstLastSuccRai->stLai.aucLac[1]     = g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1];
            NAS_GMM_ConvertPlmnIdToMmcFormat(&(g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId),
                &(pstLastSuccRai->stLai.stPlmnId));

        }
        ucRet = GMM_TRUE;
    }

    /* ����ע��ɹ�ʱ���ڵ�С����Ϣ */
    g_GmmGlobalCtrl.SysInfo_Registered = g_GmmGlobalCtrl.SysInfo;

    return ucRet;
}


/*==>A32D11726*/
/*******************************************************************************
  Module   : GMM_FillReadyTimerParaIe
  Function : ��д�տ���Ϣ�е�Requested READY timer value
  Input    : VOS_UINT8 *pAddr  ��дRequested READY timer value���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.��    ��   : 2007��06��16��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D11726����
*******************************************************************************/
VOS_VOID    GMM_FillReadyTimerParaIe (VOS_UINT8 *pAddr)
{
    /* IEI  */
    pAddr[0] = GMM_IEI_REQUESTED_READY_TIMER_VALUE;
    /* ��дReady timerֵ                     */
    pAddr[1] = GMM_REQUESTED_READY_TIMER_VALUE;
    return;
}
/*<==A32D11726*/

/*******************************************************************************
  Module   : Gmm_FillPtmsi
  Function : ��д�տ���Ϣ�е�P-TMSI
  Input    : VOS_UINT8 *pAddr  ��дP-TMSI���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/
VOS_VOID Gmm_FillPtmsi(
                   VOS_UINT8 *pAddr                                                 /* ��дP-TMSI���׵�ַ                       */
                   )
{
    VOS_UINT8                          *pucMmlPtmsi;

    pAddr[0]  = 5;                                                              /* Length of mobile identity contents       */
    pAddr[1]  = 0xF0;                                                           /* ��4bit��"1111"                           */
    pAddr[1] |= GMM_MOBILE_ID_TMSI_PTMSI;                                       /* Type of identity                         */

    /* ��дP-TMSI           */
    pucMmlPtmsi = NAS_MML_GetUeIdPtmsi();
    pAddr[2] = pucMmlPtmsi[0];
    pAddr[3] = pucMmlPtmsi[1];
    pAddr[4] = pucMmlPtmsi[2];
    pAddr[5] = pucMmlPtmsi[3];

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_FillPtmsiFromSrc
 ��������  : NAS_GMM_FillPtmsiFromSrc
 �������  : VOS_UINT8                           *pucDestAddr
             VOS_UINT8                           *pucSrcAddr
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_Fill_IE_PtmsiFromSrc(
    VOS_UINT8                           *pucDestAddr,
    VOS_UINT8                           *pucSrcAddr
)
{
    pucDestAddr[0]  = 5;                                                        /* Length of mobile identity contents       */
    pucDestAddr[1]  = 0xF0;                                                     /* ��4bit��"1111"                           */
    pucDestAddr[1] |= GMM_MOBILE_ID_TMSI_PTMSI;                                 /* Type of identity                         */

    /* ��дP-TMSI */
    PS_MEM_CPY(&pucDestAddr[2], pucSrcAddr, NAS_MML_MAX_PTMSI_LEN);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_Fill_IE_RaiFromSrc
 ��������  : NAS_GMM_FillPtmsiFromSrc
 �������  : VOS_UINT8                           *pucDestAddr
             VOS_UINT8                           *pucSrcAddr
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_Fill_IE_RaiFromSrc(
    VOS_UINT8                          *pucDestAddr,                           /* ��дP-TMSI���׵�ַ                       */
    GMM_RAI_STRU                       *pstRaiAddr
)
{
    pucDestAddr[0]  = pstRaiAddr->Lai.PlmnId.aucMccDigit[0];         /* ��дMCC                                  */

    pucDestAddr[0] |=
        (VOS_UINT8)( pstRaiAddr->Lai.PlmnId.aucMccDigit[1] << 4);
    pucDestAddr[1]  = pstRaiAddr->Lai.PlmnId.aucMccDigit[2];

    pucDestAddr[1] |=
        (VOS_UINT8)( pstRaiAddr->Lai.PlmnId.aucMncDigit[2] << 4);  /* ��дMNC                                  */
    pucDestAddr[2]  = pstRaiAddr->Lai.PlmnId.aucMncDigit[0];
    pucDestAddr[2] |=
        (VOS_UINT8)(pstRaiAddr->Lai.PlmnId.aucMncDigit[1] << 4);

    pucDestAddr[3]  = pstRaiAddr->Lai.aucLac[0];                     /* ��дLAC                                  */
    pucDestAddr[4]  = pstRaiAddr->Lai.aucLac[1];

    pucDestAddr[5]  = pstRaiAddr->ucRac;                             /* ��дRAC                                  */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_Fill_IE_RaiFromSrc
 ��������  : NAS_GMM_FillPtmsiFromSrc
 �������  : VOS_UINT8                           *pucDestAddr
              VOS_UINT8                           *pucSrcAddr
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��26��
    ��    ��   : w00167002
    �޸�����   : DTS2011122602440:�޸�AdditionalOldRaiѡ��IEI�ĳ���ֵΪ6
*****************************************************************************/
VOS_VOID NAS_GMM_Fill_IE_AdditionalOldRaiFromSrc(
    VOS_UINT8                          *pucDestAddr,                            /* ��дP-TMSI���׵�ַ                       */
    GMM_RAI_STRU                       *pucSrcRaiAddr
)
{
    /* 24008:10.5.5.15a Routing area identification 2 */
    /* TS 24.008: ATTACH REQUEST message content */
    pucDestAddr[0]  = GMM_IEI_ADDITIONAL_OLD_RAI_VALUE;


    /* Length of IEI */
    pucDestAddr[1]  = NAS_MML_ADDITIONAL_OLD_RAI_IEI_LEN;

    pucDestAddr[2]  = pucSrcRaiAddr->Lai.PlmnId.aucMccDigit[0];                 /* ��дMCC                                  */

    pucDestAddr[2] |=
        (VOS_UINT8)( pucSrcRaiAddr->Lai.PlmnId.aucMccDigit[1] << 4);
    pucDestAddr[3]  = pucSrcRaiAddr->Lai.PlmnId.aucMccDigit[2];

    pucDestAddr[3] |=
        (VOS_UINT8)( pucSrcRaiAddr->Lai.PlmnId.aucMncDigit[2] << 4);            /* ��дMNC                                  */
    pucDestAddr[4]  = pucSrcRaiAddr->Lai.PlmnId.aucMncDigit[0];
    pucDestAddr[4] |=
        (VOS_UINT8)(pucSrcRaiAddr->Lai.PlmnId.aucMncDigit[1] << 4);

    pucDestAddr[5]  = pucSrcRaiAddr->Lai.aucLac[0];                             /* ��дLAC                                  */
    pucDestAddr[6]  = pucSrcRaiAddr->Lai.aucLac[1];

    pucDestAddr[7]  = pucSrcRaiAddr->ucRac;                                     /* ��дRAC                                  */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_Gmm_Fill_IE_AttachTypeAndCksn
 ��������  : ��䵱ǰ��ATTACH���ͺ�CKSN
 �������  : VOS_UINT8                          *pucAddr
 �������  : VOS_UINT8                          *pucAddr
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��13��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 3.��    ��   : 2012��2��23��
   ��    ��   : w00176964
   �޸�����   : DTS2012022107470:WG֮��������ҵ�������л�ʱ,��G�е�W����RAU��
                ����#9,NAS��������RAU���������ж�
  4.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*****************************************************************************/
VOS_UINT8 NAS_Gmm_Fill_IE_AttachTypeAndCksn(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucNumber;
    VOS_UINT8                           ucAttachType;
    VOS_UINT8                           ucSpecProc;
    VOS_UINT8                           ucCksn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulUsimDoneGsmPsAuthFlg;

    enNetRatType                        = NAS_MML_GetCurrNetRatType();
    enSimType                           = NAS_MML_GetSimType();
    ucSpecProc                          = NAS_GMM_GetSpecProc();
    ucNumber                            = 1;

    ulUsimDoneGsmPsAuthFlg              = NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth();

    /* ��CSҵ�����ʱ,RAU���ܵ��µ�����attach��Ȼ��Ҫ������ͨ��attach
       ����ᵼ��CSҵ���ж� */
    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_NORMAL          == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_TRUE                   == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {                                                                           /* ���ݵ�ǰ��specific�����ж�attach������   */
        ucAttachType = GMM_GPRS_ATTACH;                                         /* ����ATTACH����                           */
    }
    else if (GMM_ATTACH_WHILE_IMSI_ATTACHED == ucSpecProc)
    {
        /*ucAttachType = GMM_GPRS_ATTACH_WHILE_IMSI_ATTACH;*/                   /* ����ATTACH����                           */
        ucAttachType = GMM_COMBINED_GPRS_IMSI_ATTACH;
    }
    else
    {
        ucAttachType = GMM_COMBINED_GPRS_IMSI_ATTACH;                           /* ����ATTACH����                           */
    }

    pucAddr[0] = ucAttachType;                                                  /* attach type                              */

    if (VOS_TRUE == NAS_GMM_IsFollowOnPend())
    {                                                                           /* ��Ҫ����follow on                        */
        pucAddr[0] |= GMM_FOLLOW_ON_REQ_PENDING;                                /* follow on                                */
    }

    /* SIM����W�����з���ATTACH,��CKSN��Ϊ��Ч */
    if ( (VOS_TRUE                      == ulUsimDoneGsmPsAuthFlg)
      || ((NAS_MML_NET_RAT_TYPE_WCDMA   == enNetRatType)
       && (NAS_MML_SIM_TYPE_SIM         == enSimType)) )
    {
        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);

        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
   }

    ucCksn          = NAS_MML_GetSimPsSecurityCksn();
    pucAddr[0]     |= ((ucCksn << 4) & 0xF0);                                   /* CKSN */

    return ucNumber;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_FillPtmsiFromSrc
 ��������  : NAS_GMM_FillPtmsiFromSrc
 �������  : VOS_UINT8                           *pucDestAddr
             VOS_UINT8                           *pucSrcAddr
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_Fill_IE_PtmsiSignFromSrc(
    VOS_UINT8                           *pucDestAddr,                           /* ��дP-TMSI���׵�ַ                       */
    VOS_UINT8                           *pucSrcAddr
)
{
    pucDestAddr[0]  = GMM_IEI_P_TMSI_SIGNATURE;                                                              /* Length of mobile identity contents       */

    /* ��дP-TMSI Signature*/
    PS_MEM_CPY(&pucDestAddr[1], pucSrcAddr, NAS_MML_MAX_PTMSI_SIGNATURE_LEN);

    return;
}

/*******************************************************************************
  Module   : MM_Fill_IE_ClassMark2
  Function : ��д�տ���Ϣ�е�ClassMark2 IE (TLV)
  Input    : VOS_VOID *pAddr  ��дClassMark2 IE�ĵ�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��    ��   : 2014��10��8��
     ��    ��   : b00269685
     �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID GMM_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2                             /* ��дClassMark2 IE���׵�ַ   */
)
{
    VOS_UINT8                           aucClassMark2[GMM_MSG_LEN_CLASSMARK2];

    PS_MEM_SET(aucClassMark2, 0, sizeof(aucClassMark2));

    aucClassMark2[0] = GMM_IEI_CLASSMARK2;

    NAS_MML_Fill_IE_ClassMark2(&aucClassMark2[1]);

    PS_MEM_CPY(pClassMark2, aucClassMark2, GMM_MSG_LEN_CLASSMARK2);

    return;
}

/*******************************************************************************
  Module   : GMM_Fill_IE_FDD_ClassMark3
  Function : ��дFDD�տ���Ϣ�е�ClassMark3 IE (TLV)
  Input    : VOS_VOID *pAddr  ��дClassMark3 IE�ĵ�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��    ��   : 2014��10��8��
     ��    ��   : b00269685
     �޸�����   : �����ɺ���
*******************************************************************************/
VOS_UINT8 GMM_Fill_IE_FDD_ClassMark3(
    VOS_UINT8                          *pClassMark3                             /* ��дClassMark3 IE���׵�ַ   */
)
{
    VOS_UINT8                           aucClassMark3[MS_CLASSMARK3_MAX_LEN];
    VOS_UINT8                           ucLen;

    PS_MEM_SET(aucClassMark3, 0, sizeof(aucClassMark3));

    aucClassMark3[0] = GMM_IEI_CLASSMARK3;

    NAS_MML_Fill_IE_FddClassMark3(&aucClassMark3[1]);

    /* ��һλΪ����,����tag �� len */
    ucLen = aucClassMark3[1] + 2;
    PS_MEM_CPY(pClassMark3, aucClassMark3, ucLen);

    return ucLen;
}

/*******************************************************************************
  Module   : GMM_Fill_IE_TDD_ClassMark3
  Function : ��дTDD�տ���Ϣ�е�ClassMark3 IE (TLV)
  Input    : VOS_VOID *pAddr  ��дClassMark3 IE�ĵ�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��    ��   : 2014��10��8��
     ��    ��   : b00269685
     �޸�����   : �����ɺ���
*******************************************************************************/
VOS_UINT8 GMM_Fill_IE_TDD_ClassMark3(
    VOS_UINT8                          *pClassMark3                             /* ��дClassMark3 IE���׵�ַ   */
)
{
    VOS_UINT8                           aucClassMark3[MS_CLASSMARK3_MAX_LEN];
    VOS_UINT8                           ucLen;

    PS_MEM_SET(aucClassMark3, 0, sizeof(aucClassMark3));

    aucClassMark3[0] = GMM_IEI_CLASSMARK3;

    NAS_MML_Fill_IE_TddClassMark3(&aucClassMark3[1]);

    /* ��һλΪ����,����tag �� len */
    ucLen = aucClassMark3[1] + 2;
    PS_MEM_CPY(pClassMark3, aucClassMark3, ucLen);

    return ucLen;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_FillUmtsSupCodecList
 ��������  : ��дUMTS֧�ֵ�codec list
 �������  : ��
 �������  : punCodecList :��ǰUMTS֧�ֵ�codec����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��8��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  GMM_CALL_FillUmtsSupCodecList(
    GMM_CALL_SUPPORT_CODEC_UNION       *punCodecList
)
{
    NAS_MML_CALL_UMTS_CODEC_TYPE_STRU  *pstUmtsCodecType = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstUmtsCodecType = NAS_MML_CALL_GetCallUmtsCodecType();

    for ( i = 0 ; i < pstUmtsCodecType->ucCnt ; i++ )
    {
        switch (pstUmtsCodecType->aucUmtsCodec[i])
        {
            case NAS_MML_CALL_UMTS_CODEC_TYPE_AMR :
                punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
                break;

            case NAS_MML_CALL_UMTS_CODEC_TYPE_AMR2 :
                punCodecList->stSupportCodec.CodecType_UMTSAMR2    = VOS_TRUE;
                break;

            case NAS_MML_CALL_UMTS_CODEC_TYPE_AMRWB :
                punCodecList->stSupportCodec.CodecType_UMTSAMRWB   = VOS_TRUE;
                break;
            default:
                NAS_WARNING_LOG(WUEPS_PID_GMM, "GMM_CALL_FillUmtsSupCodecList: invalid speech version");
                break;
        }
    }
}

/*****************************************************************************
 �� �� ��  : GMM_CALL_FillGsmSupCodecList
 ��������  : ��дGSM֧�ֵ�codec list
 �������  : ��
 �������  : punCodecList :��ǰGSM֧�ֵ�codec����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��8��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  GMM_CALL_FillGsmSupCodecList(
    GMM_CALL_SUPPORT_CODEC_UNION       *punCodecList
)
{
    NAS_MML_CALL_GSM_CODEC_TYPE_STRU   *pstGsmCodecType = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstGsmCodecType = NAS_MML_CALL_GetCallGsmCodeType();

    for ( i = 0 ; i < pstGsmCodecType->ucCodecTypeNum; i++ )
    {
        switch (pstGsmCodecType->aucCodecType[i])
        {
            case NAS_MML_CALL_BC_VAL_SPH_VER_FR_1 :
                punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
                break;

            case NAS_MML_CALL_BC_VAL_SPH_VER_FR_2 :
                punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
                break;

            case NAS_MML_CALL_BC_VAL_SPH_VER_FR_3 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
                break;

            case NAS_MML_CALL_BC_VAL_SPH_VER_HR_1 :
                punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
                break;

            case NAS_MML_CALL_BC_VAL_SPH_VER_HR_3 :
                punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
                break;

            case NAS_MML_CALL_BC_VAL_SPH_VER_FR_5 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
                break;
            default:
                NAS_WARNING_LOG(WUEPS_PID_GMM, "GMM_CALL_FillGsmSupCodecList: invalid speech version");
                break;
        }
    }
}

/*****************************************************************************
 �� �� ��  : GMM_CALL_FillIeSupCodecList
 ��������  : ��д֧�ֵ�codec list�б�
 �������  : ��
 �������  : pstCodecList - ֧�ֵ�codec list  (TLV)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��8��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  GMM_CALL_FillIeSupCodecList(
    VOS_UINT8                          *pstCodecList                            /* ��дsupport codec IE���׵�ַ   */
)
{
    GMM_CALL_SUPPORT_CODEC_UNION        unCodec;
    NAS_CC_IE_CODEC_INFO_STRU           astCodecList[2];
    VOS_UINT8                           ucLen;

    /* ����֧�ֵ��б�Ŀǰ������GSM��UMTS֧�ֵ�codec list,
       00 ��ʾGSM, 04��ʾUMTS */
    /* ���帳ֵ�ĺ���μ�26.103 */

    PS_MEM_SET(&unCodec, 0x00, sizeof(unCodec));
    astCodecList[0].SysId = 0x04;
    astCodecList[0].LastOctOffsetengthOfBitMap = 0x02;
    GMM_CALL_FillUmtsSupCodecList(&(unCodec));
    astCodecList[0].CodecBitmapL = (VOS_UINT8)(unCodec.usSupportCodec);
    astCodecList[0].CodecBitmapH = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

    /* ��дGSM֧�ֵ�codec���� */
    PS_MEM_SET(&unCodec, 0x00, sizeof(unCodec));
    GMM_CALL_FillGsmSupCodecList(&(unCodec));
    astCodecList[1].SysId = 0x00;
    astCodecList[1].LastOctOffsetengthOfBitMap = 0x02;
    astCodecList[1].CodecBitmapL = (VOS_UINT8)(unCodec.usSupportCodec);
    astCodecList[1].CodecBitmapH = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

    pstCodecList[0] = GMM_IEI_SUPPORTED_CODEC_LIST;
    pstCodecList[1] = sizeof(astCodecList);
    PS_MEM_CPY(&pstCodecList[2], astCodecList, sizeof(astCodecList));

    ucLen = sizeof(astCodecList) + 2;
    return ucLen;
}


/*******************************************************************************
  Module   : Gmm_FillDrxPara
  Function : ��д�տ���Ϣ�е�DRX parameter��Value����
  Input    : VOS_VOID *pAddr  ��дDRX parameter���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.18  �¹�����

  2.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
*******************************************************************************/
VOS_VOID Gmm_FillDrxPara(
                     VOS_UINT8 *pAddr                                               /* ��дDRX parameter���׵�ַ                */
                     )
{
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */
    pAddr[0]  = NAS_MML_GetSplitPgCycleCode();                                  /* ��дSPLIT PG CYCLE CODE                  */
    pAddr[1]  = NAS_MML_GetNonDrxTimer();                                       /* ��дnon-DRXtimer                         */
    pAddr[1] |= (VOS_UINT8)(NAS_MML_GetSplitOnCcch() << NAS_MML_OCTET_MOVE_THREE_BITS);     /* ��дSPLIT on CCCH                        */
    pAddr[1] |= (VOS_UINT8)(NAS_MML_GetUeUtranPsDrxLen() << NAS_MML_OCTET_MOVE_FOUR_BITS);  /* CN Specific DRX cycle length coefficient */
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */

    return;
}

/*******************************************************************************
  Module   : Gmm_Fill_NetworkCapability
  Function : ��д�տ���Ϣ�е�NetworkCapability IE (LV)
  Input    : VOS_VOID *pAddr  ��дNetworkCapability IE���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : IE���ȡ�
  History  :
    1. ŷ����  2009.05.10  �¹�����
    2. ��    ��   : 2009��09��1��
       ��    ��   : ŷ���� o00132663
       �޸�����   : AT2D14179,���ݵ�ǰ֧�ֵİ汾��Ϣ����Revision Level Indicator IE
    3. ��    ��   : 2011��07��26��
       ��    ��   : z00161729
       �޸�����   : ȫ�ֱ�������
     4.��    ��   : 2011��10��27��
       ��    ��   : s46746
       �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
     5.��    ��   : 2012��03��15��
       ��    ��   : s46746
       �޸�����   : ����R7��R8������Ϣ��Ԫ,ʹ��Э��汾����

     6.��    ��   : 2012��3��24��
       ��    ��   : z40661
       �޸�����   : DTS2012032004429 MS networkcapablity������ˢ��
    7.��    ��   : 2012��2��27��
      ��    ��   : z00161729
      �޸�����   : V7R1 C50 ֧��ISR�޸�
    8.��    ��   : 2012��5��21��
       ��    ��   : z40661
       �޸�����   : DTS2012051702389 EPC��������Ҫ�ж�֧��Lģ�͵�ǰ��SIM��
    9.��    ��   : 2012��6��9��
      ��    ��   : z00161729
      �޸�����   : V7R1C50 GUL �������޸ģ����L�Ѿ�disable��Э��涨�����ϱ�ISR����
   10.��    ��   : 2013��5��23��
     ��    ��   : z00234330
     �޸�����   : DTS2013052301419, ISR����ͨ��NVIM�����
  11.��    ��   : 2014��5��9��
     ��    ��   : b00269685
     �޸�����   : DTS2014042103974, ��֧��LTEʱ����Ҫ�ϱ�SRVCC����
  12.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����

  13.��    ��   : 2014��8��29��
     ��    ��   : w00167002
     �޸�����   : DTS2014082609066:���人�����£���ǰ����ΪUG��������ΪLUG����
                  L�·���TAUʱ������ܾ�17�����Ϊ�ڲ�֧��L�����ǽ�EPC��������Ϊ��0����L��ע��ʧ�ܡ��޸�Ϊ
                  1����L��ע��ɹ���

                  ������CR�����У��ж�EPC���õ�����:
                  C1-122511
                  Reason for change:
If the UE set the EPC capability to "EPC not supported" when the UE disables E-UTRA capability,
ongoing data transmission would be disconnected when the UE re-enable E-UTRA capability.
So, the LTE-capable UE should always set the EPC capability to "EPC supported" even if the
UE disables E-UTRA capability.
However, in current specification, the setting method of EPC capability bit of the
MS network capability IE is not described. So, the clarification of setting method of this IE is needed.

Summary of change:
Following clarification is introduced.
- The LTE-capable UE should always set the EPC capability to "EPC supported" even if the UE disables E-UTRA capability.
Consequences if
not approved:The UE might make a mistake in setting method of EPC capability bit of the MS network capability IE and this would cause a disconnection of data transmission.

                   �޸�PS INTER RAT HO FORM GERAN TO E-UTRAN ������CR��������(C1-143148)
So to provide a clear guidance on the UE implementation, it should be clearly specified that
which bit needs to be changed after disabling of the UE's E-UTRA capability. When seeing the
bits in the MS network capability IE, there are below capabilities related to LTE:

"<PS inter-RAT HO from GERAN to E-UTRAN S1 mode capability: bit>
<EMM Combined procedures Capability: bit>
<ISR support: bit>
<SRVCC to GERAN/UTRAN capability: bit>
<EPC capability: bit>"

<ISR support: bit> and <EPC capability: bit> were already clearly covered in the above bullets.
For <EMM Combined procedures Capability: bit>, it is not related to the inter-RAT mobility so
the UE needs not to change it due to disabling of the UE's E-UTRA capability.
Furthermore, the PS/CS mode 1 UE needs to set this bit to indicate
the SGSN to initiate the Gs association establishment for the UE if CSFB is supported.

For <SRVCC to GERAN/UTRAN capability: bit>, it will not enable the SGSN to move
the UE back to LTE, so the UE needs not to change this bit due to disabling of the UE's E-UTRA capability.

So only for <PS inter-RAT HO from GERAN to E-UTRAN S1 mode capability: bit>, the UE
needs not set this bit to avoid the NW initiating the PSHO to move the UE back to LTE.
 14.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_UINT8 Gmm_Fill_IE_NetworkCapability(
                                     VOS_UINT8 *pAddr                           /* ��дNetworkCapability IE���׵�ַ                */
                                    )
{
    VOS_UINT8                           ucLen;
    VOS_INT8                            cVersion;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType;

    VOS_UINT32                          ulLteCapDisablFlg;
    VOS_UINT8                           ucIsrSupport;

    ucIsrSupport = NAS_MML_GetIsrSupportFlg();

    enMsMode = NAS_MML_GetMsMode();
#endif

    pstMsCapability = NAS_MML_GetMsCapability();


    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);


    ucLen = NAS_MML_DEFAULT_NETWORKCAPABILITY_LEN;
    Gmm_MemCpy (pAddr + 1, pstMsCapability->stMsNetworkCapability.aucNetworkCapability, ucLen);

    /* Update Revision Level Indicator IE
 */
    if (PS_PTL_VER_PRE_R99 == cVersion)
    {
        pAddr[1] &= 0xfe;
    }
    else
    {
        pAddr[1] |= 0x01;
    }

    if (PS_PTL_VER_R7 <= cVersion)
    {
        /* ĿǰNV����Network cap��д����Ϊ2,���Э��汾ΪR7��R7֮��,�䳤��Ϊ3 */
        ucLen++;

        if (pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen > 2)
        {
            pAddr[3] = pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2];
        }
        else
        {
            pAddr[3] = 0x0;
        }

#if (FEATURE_ON == FEATURE_LTE)


        /* ��ǰSIM��ʱ,�����ϱ�֧��EPC������ */
        enSimType = NAS_MML_GetSimType();

        if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {
            pAddr[3] &= 0xFB;
        }



        /* ���֧��LTE��ģʽΪCS_PSʱ��Ϊ֧��EMM Combined procedures capability */
        if ((VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
         && (NAS_MML_MS_MODE_PS_CS == enMsMode))
        {
            pAddr[3] |= 0x20;
        }
        else
#endif
        {
            pAddr[3] &= 0xDF;
        }

        /* ���֧��LTE,����Ϊ֧��ISR, ISR support��Ӧbit��1 */
#if (FEATURE_ON == FEATURE_LTE)
        /* L����Ѿ���disable�������ϱ�ISR���� */
        ulLteCapDisablFlg = NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(),
                                                            NAS_MML_GetDisableLteRoamFlg());

        /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        if ((VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
         || (VOS_TRUE  == ulLteCapDisablFlg))
        {
            /* 4301_CR1440R1_(Rel-11)_C1-122224 ��24301_CR1446R4_(Rel-11)_C1-122511
            ��C1-143148(rev of C1-142842)_24.301_MS NW cap after disabling LTE cap-R11��
            ��Ӧ24301 4.5�½�:
            <ISR support: bit> and <EPC capability: bit> were already clearly covered in the above bullets.
            <EMM Combined procedures Capability: bit>, it is not related to the inter-RAT
            mobility so the UE needs not to change it due to disabling of the UE's E-UTRA capability.
            Furthermore, the PS/CS mode 1 UE needs to set this bit to indicate the SGSN to initiate the
            Gs association establishment for the UE if CSFB is supported.
            <SRVCC to GERAN/UTRAN capability: bit>, it will not enable the SGSN to move the UE back to LTE,
            so the UE needs not to change this bit due to disabling of the UE's E-UTRA capability.
            <PS inter-RAT HO from GERAN to E-UTRAN S1 mode capability: bit>, the UE needs not set this bit to avoid the NW initiating the
            PSHO to move the UE back to LTE. ��CR����Э��汾���ơ�
            ��֧��LTEʱ��SRVCC�����ϱ����䣬��l�Ƿ�disable�޹�*/


            /* ��֧��PS INTER RAT HO FORM GERAN TO E-UTRAN */
            pAddr[3] &= 0xBF;

        }
        /* Modified by z00234330 for PCLINT����, 2014-06-24, end */


        /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        if ((VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
         && (VOS_FALSE == ulLteCapDisablFlg)
         && (VOS_TRUE == ucIsrSupport))

        /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
        {
            pAddr[3] |= 0x10;
        }
        else
#endif
        {
            pAddr[3] &= 0xEF;
        }
    }

    pAddr[0] = ucLen;

    /* ��Ҫ����MS Net Cap IE(LV���)�ܳ��ȣ����ucLen��Ҫ��1 */
    ucLen++;

    return ucLen;
}
/*******************************************************************************
  Module   : Gmm_Fill_RadioAccessCapability
  Function : ��д�տ���Ϣ�е�Gmm_Fill_RadioAccessCapability IE (LV)
  Input    : VOS_VOID *pAddr  ��дGmm_Fill_RadioAccessCapability IE���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : IE���ȡ�
  History  :
    1. ŷ����  2009.05.10  �¹�����

    2.��    ��   : 2012��7��14��
      ��    ��   : W00176964
      �޸�����   : V7R1 C50 GUTL PhaseI����:���͸�WRR����Ϣͳһ������㺯���滻
    3.��    ��   : 2014��2��27��
      ��    ��   : w00242748
      �޸�����   : DTS2014022805239
*******************************************************************************/
VOS_UINT8 Gmm_Fill_IE_RadioAccessCapability(VOS_UINT8 *pAddr)
{
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                              *pucRadioCpb            = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
	VOS_UINT32                                              ulRst;
    NAS_GAS_MS_CAP_TYPE_ENUM_UINT8                          enMsCapType;
    GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU            *pstMsRadioAccessCapInd = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurNetRatType;
    RRC_PLMN_ID_STRU                                        stRrmmPlmnId;
#endif

#if (FEATURE_ON == FEATURE_LTE)
    enCurNetRatType        = NAS_MML_GetCurrNetRatType();

    pstMsRadioAccessCapInd = (GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_MMC, sizeof(GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU));
#endif

    if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
#if (FEATURE_ON == FEATURE_LTE)
        enMsCapType = NAS_GAS_MS_CAP_TYPE_UTRAN_TDD_RAC;
#endif
        pucRadioCpb = g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb;
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)
        enMsCapType = NAS_GAS_MS_CAP_TYPE_UTRAN_FDD_RAC;
#endif
        pucRadioCpb = g_GmmGlobalCtrl.UeInfo.aucRadioCpb;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ǰNV�򿪣������ڴ�ɹ��ҵ�ǰģ����GSM */
    if ( (VOS_TRUE == NAS_MML_GetIsDelFddBandSwitchOnFlg())
      && (VOS_NULL_PTR != pstMsRadioAccessCapInd)
      && (NAS_MML_NET_RAT_TYPE_GSM != enCurNetRatType) )
    {

        PS_MEM_SET(pstMsRadioAccessCapInd, 0x00, sizeof(GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU));

        stRrmmPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stRrmmPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;

        /* ����GAS�ӿڻ�ȡUE RADIO���� */
        ulRst = GASGCOM_GetMsCapability(&stRrmmPlmnId, enMsCapType,
                                                sizeof(GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND_STRU),
                                                (VOS_UINT8*)pstMsRadioAccessCapInd);

        /* ��ά�ɲ� */
        NAS_GMM_LogGasGmmRadioAccessCapability(ulRst, enMsCapType,
                                                sizeof(pstMsRadioAccessCapInd->aucData),
                                                pstMsRadioAccessCapInd->aucData);

        if ( VOS_TRUE == ulRst )
        {
            pucRadioCpb = pstMsRadioAccessCapInd->aucData;
        }
    }
#endif

    ucLen = pucRadioCpb[0] + 1;
    Gmm_MemCpy (pAddr, pucRadioCpb, ucLen);

#if (FEATURE_ON == FEATURE_LTE)
    if ( VOS_NULL_PTR != pstMsRadioAccessCapInd )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstMsRadioAccessCapInd);
    }
#endif

    return ucLen;
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillPtmsiIeForSnd
 ��������  : ���ATTCH ��PTMSI��IE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��13��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 3.��    ��   : 2013��05��21��
   ��    ��   : l65478
   �޸�����   : DTS2013053002449ϣ������:����֧��LTEʱ,ʹ��GU�µ�ID
 4.��    ��   :2013��8��29��
   ��    ��   :z00161729
   �޸�����  :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability

*****************************************************************************/
VOS_UINT8 NAS_Gmm_FillPtmsiIeWhenGUL(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                          *pucImsi             = VOS_NULL_PTR;
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucNumber;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    VOS_UINT32                          ulIsSupportLteCapability;

    /* ȡ�ñ���ά����IMSI�ĵ�ַ */
    pucImsi             = NAS_MML_GetSimImsi();

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* ����Ĭ����ΪPTMSI�ĳ���6 */
    ucNumber            = GMM_MSG_LEN_LV_PTMSI;

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();
    ulLocalPtmsiFlg     = VOS_FALSE;

    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }


    /* reference to 24.008 4.7.3.1.1 */

    ulIsSupportLteCapability = NAS_MML_IsSupportLteCapability();

    /* syscfg���ò�֧��L����L �Ѿ�disable�������guti�л�ȡptimsi */
    if (VOS_FALSE == ulIsSupportLteCapability)
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            NAS_GMM_Fill_IE_PtmsiFromSrc(pucAddr, pucPtmsiAddr);
        }
        else
        {
            PS_MEM_CPY( pucAddr, pucImsi, pucImsi[0]+1 );
            ucNumber = pucImsi[0]+1;
        }

        return ucNumber;
    }

    ulGetGutiRst            = NAS_GMM_MapPtmsiFromGUTI();
    enTinType               = NAS_MML_GetTinType();

    /* 4.7.3.1.1 GPRS attach procedure initiation (GMM_MAPPED_INFO_FROM_EPS_STRU)
       If the MS supports S1 mode, the MS shall handle the P-TMSI or IMSI IE as follows
    */
    if ( (NAS_MML_TIN_TYPE_GUTI == enTinType) && (VOS_OK == ulGetGutiRst) )
    {
        NAS_GMM_Fill_IE_PtmsiFromSrc(pucAddr, pucMappedPtmsiAddr);
    }
    else if ( ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType) || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
           && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        NAS_GMM_Fill_IE_PtmsiFromSrc(pucAddr, pucPtmsiAddr);
    }
    /*If the TIN is deleted,and the MS doesnot holds a valid P-TMSI and a RAI,and the MS holds a valid GUTI, the MS shall map the GUTI into the P-TMSI  */
    else if ( (NAS_MML_TIN_TYPE_INVALID  == enTinType)
           && (VOS_FALSE            == ulLocalPtmsiFlg)
           && (VOS_OK               == ulGetGutiRst) )
    {
        NAS_GMM_Fill_IE_PtmsiFromSrc(pucAddr, pucMappedPtmsiAddr);
    }
    else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType) && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        NAS_GMM_Fill_IE_PtmsiFromSrc(pucAddr, pucPtmsiAddr);
    }
    else
    {
        PS_MEM_CPY( pucAddr, pucImsi, pucImsi[0]+1 );

        /* ȡ��IMSI�ĳ��� */
        ucNumber = pucImsi[0]+1;
    }

    return ucNumber;

}
#endif

/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillPtmsiIeForSnd
 ��������  : ���ATTCH ��PTMSI��IE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��13��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���

*****************************************************************************/
VOS_UINT8 NAS_Gmm_FillPtmsiIeForSnd(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucNumber;
#if (FEATURE_ON != FEATURE_LTE)
    VOS_UINT8                          *pucPtmsiAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT8                          *pucImsi      = VOS_NULL_PTR;
#endif

    /* ����Ĭ����ΪPTMSI�ĳ���6 */
    ucNumber           = GMM_MSG_LEN_LV_PTMSI;

#if (FEATURE_ON == FEATURE_LTE)

    /* ֧��Lģʱ��PTMSI IE���    */
    ucNumber = NAS_Gmm_FillPtmsiIeWhenGUL(pucAddr);

    return ucNumber;

#else


    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr       = NAS_MML_GetUeIdPtmsi();

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ucUeIdMask         = NAS_GMM_GetUeIdMask();
    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        NAS_GMM_Fill_IE_PtmsiFromSrc(pucAddr, pucPtmsiAddr);
    }
    else
    {                                                                           /* IMSI                                     */
        /* ȡ�ñ���ά����IMSI�ĵ�ַ */
        pucImsi = NAS_MML_GetSimImsi();
        PS_MEM_CPY( pucAddr, pucImsi, pucImsi[0]+1 );

        /* ȡ��IMSI�ĳ��� */
        ucNumber = pucImsi[0]+1;
    }

    return ucNumber;
#endif

}



/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillPtmsiIeForSnd
 ��������  : ���ATTCH ��Old P-TMSI signature��IE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��21��
    ��    ��   : l65478
    �޸�����   : DTS2013053002449ϣ������:����֧��LTEʱ,ʹ��GU�µ�ID
  3.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����  :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
  4.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������
*****************************************************************************/
VOS_UINT8 NAS_Gmm_FillPtmsiSignatureIeForSnd(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                          *pucPtmsiSign       = VOS_NULL_PTR;
    VOS_UINT8                           ucNumber;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;
    VOS_BOOL                            bLocalPtmsiSignFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                          *pucMappedPtmsiSign = VOS_NULL_PTR;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulGetGutiRst;

    VOS_UINT32                          ulIsSupportLteCapability;

    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;

    ucLDisabledRauUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();
#endif

    /* ����Ĭ����ΪPTMSI Signatrue�ĳ���4*/
    ucNumber  = GMM_MSG_LEN_PTMSI_SIGNATURE;

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg     = VOS_FALSE;
    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }
    /* GU���ص�PTMSI Signatrue �Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    bLocalPtmsiSignFlg  = VOS_FALSE;
    if ( GMM_UEID_P_TMSI_SIGNATURE == ( ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE) )
    {
        bLocalPtmsiSignFlg = VOS_TRUE;
    }

    /* ��ȡ�洢PTMSI signature�����ݵ�ַ */
    pucPtmsiSign        = NAS_MML_GetUeIdPtmsiSignature();

#if (FEATURE_ON == FEATURE_LTE)

    /* reference to 24.008 4.7.3.1.1 and 4.7.5.1.1 */
    ulIsSupportLteCapability = NAS_MML_IsSupportLteCapability();

    /* syscfg���ò�֧��L����L �Ѿ�disable attach �������guti�л�ȡptimsi signature, rau nv �����Ƿ���Ҫ��guti��ȡptmsi signature */
    if (VOS_FALSE == ulIsSupportLteCapability)
    {
        if (!((GMM_RAU_COMBINED == (g_GmmGlobalCtrl.ucSpecProc & GMM_RAU_COMBINED))
            && (VOS_TRUE == ucLDisabledRauUseLInfoFlag)))
        {
            if ( (VOS_TRUE == ulLocalPtmsiFlg)
              && (VOS_TRUE == bLocalPtmsiSignFlg) )
            {
                NAS_GMM_Fill_IE_PtmsiSignFromSrc(pucAddr, pucPtmsiSign);
            }
            else
            {
                ucNumber = 0;
            }

            return ucNumber;
        }
    }


    /* 4.7.3.1.1 GPRS attach procedure initiation (GMM_MAPPED_INFO_FROM_EPS_STRU)
       If the MS supports S1 mode, the MS shall handle the P-TMSI or IMSI IE as follows
    */
    ulGetGutiRst        = NAS_GMM_MapPtmsiSignFromGUTIAndNasToken();
    enTinType           = NAS_MML_GetTinType();
    pucMappedPtmsiSign  = NAS_GMM_GetMappedPtmsiSignAddr();

    if ( ((NAS_MML_TIN_TYPE_GUTI == enTinType)
        && (VOS_OK  == ulGetGutiRst))
      || ((NAS_MML_TIN_TYPE_INVALID == enTinType)
       && (VOS_OK == ulGetGutiRst)
       && (VOS_FALSE == ulLocalPtmsiFlg)) )
    {
        NAS_GMM_Fill_IE_PtmsiSignFromSrc(pucAddr, pucMappedPtmsiSign);
    }
    else if ( ( (NAS_MML_TIN_TYPE_PTMSI == enTinType)
              || (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
              || (NAS_MML_TIN_TYPE_INVALID == enTinType) )
           && (VOS_TRUE  == ulLocalPtmsiFlg )
           && ( VOS_TRUE == bLocalPtmsiSignFlg ))
    {
        NAS_GMM_Fill_IE_PtmsiSignFromSrc(pucAddr, pucPtmsiSign);
    }
    else
    {
        ucNumber = 0;
    }

    return ucNumber;

#else
    if ( (VOS_TRUE == ulLocalPtmsiFlg)
      && (VOS_TRUE == bLocalPtmsiSignFlg) )
    {
        NAS_GMM_Fill_IE_PtmsiSignFromSrc(pucAddr, pucPtmsiSign);
    }
    else
    {
        ucNumber = 0;
    }

    return ucNumber;
#endif

}

/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillPtmsiIeForSnd
 ��������  : ���ATTCH ��Old routing area identification��IE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��21��
    ��    ��   : l65478
    �޸�����   : DTS2013053002449ϣ������:����֧��LTEʱ,ʹ��GU�µ�ID
  3.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����   :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
  4.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������
*****************************************************************************/
VOS_UINT8 NAS_Gmm_FillRaiForSnd(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucNumber;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    GMM_RAI_STRU                       *pstMappedRai = VOS_NULL_PTR;
    VOS_UINT32                          ulGetGutiRst;

    VOS_UINT32                          ulIsSupportLteCapability;


    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    /* ����Ĭ����ΪRAI�ĳ���6 */
    ucNumber  = GMM_MSG_LEN_OLD_RAI;

#if (FEATURE_ON == FEATURE_LTE)
    ucLDisabledRauUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();

    /* reference to 24.008 4.7.3.1.1 and 4.7.5.1.1 */
    ulIsSupportLteCapability = NAS_MML_IsSupportLteCapability();

    /* syscfg���ò�֧��L����L �Ѿ�disable attach�����guti�л�ȡptimsi,rau nv������Ƿ��guti�л�ȡ */
    if (VOS_FALSE == ulIsSupportLteCapability)
    {
        if (!((GMM_RAU_COMBINED == (g_GmmGlobalCtrl.ucSpecProc & GMM_RAU_COMBINED))
            && (VOS_TRUE == ucLDisabledRauUseLInfoFlag)))
        {
            NAS_GMM_Fill_IE_RaiFromSrc(pucAddr, &stGmmRai);

            return ucNumber;
        }
    }



    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg     = VOS_FALSE;
    ucUeIdMask         = NAS_GMM_GetUeIdMask();
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    ulGetGutiRst            = NAS_GMM_MapRaiFromGUTI();
    enTinType               = NAS_MML_GetTinType();
    pstMappedRai            = NAS_GMM_GetMappedRaiAddr();

    /* 4.7.3.1.1 GPRS attach procedure initiation */
    if ( ((NAS_MML_TIN_TYPE_GUTI  == enTinType)
        && (VOS_OK  == ulGetGutiRst))
      || ((NAS_MML_TIN_TYPE_INVALID == enTinType)
        && (VOS_OK  == ulGetGutiRst)
        && (VOS_FALSE == ulLocalPtmsiFlg)) )
    {
        NAS_GMM_Fill_IE_RaiFromSrc(pucAddr, pstMappedRai);
        return ucNumber;
    }

    /* If the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI,
    the MS shall indicate the P-TMSI in the P-TMSI or IMSI IE and the RAI in the Old routing area identification IE.  */
    if ( ((NAS_MML_TIN_TYPE_PTMSI == enTinType) || (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
      && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        NAS_GMM_Fill_IE_RaiFromSrc(pucAddr, &stGmmRai);
        return ucNumber;
    }
#endif

    NAS_GMM_Fill_IE_RaiFromSrc(pucAddr, &stGmmRai);

    return ucNumber;
}


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_Gmm_Fill_IE_AdditionalOldRAI
 ��������  : ���ATTCH ��Additional old routing area identification��IE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ�����·�װLMM�ṩ�Ľӿں���

*****************************************************************************/
VOS_UINT8 NAS_Gmm_Fill_IE_AdditionalOldRAI(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucNumber;
    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    NAS_LMM_INFO_STRU                   stLmmInfo;
    VOS_UINT32                          ulLocalPtmsiFlg;

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    /* �ֱ��ȡ�洢GU��RAI�Լ��洢��Lģӳ������RAI��ַ */

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg     = VOS_FALSE;
    if ( GMM_UEID_P_TMSI == ( NAS_GMM_GetUeIdMask() & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    /* ��ȡGUTI�Ƿ���Ч */
    ulGetGutiRst        = NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo );

    enTinType           = NAS_MML_GetTinType();
    if ( (NAS_MML_TIN_TYPE_GUTI == enTinType)
      && (VOS_TRUE              == ulGetGutiRst)
      && (VOS_TRUE              == ulLocalPtmsiFlg) )
    {
        NAS_GMM_Fill_IE_AdditionalOldRaiFromSrc(pucAddr, &stGmmRai);

        /* ���ĳ���Ϊ8 */
        ucNumber  = GMM_MSG_LEN_ADDITIONAL_OLD_RAI;
    }
    else
    {
        ucNumber = 0;
    }

    return ucNumber;

}


/*****************************************************************************
 �� �� ��  : NAS_Gmm_Fill_IE_AdditionalMobileIdentity
 ��������  : ���ATTCH ��Additional mobile identity��IE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��13��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ�����·�װLMM�ṩ�Ľӿں���

*****************************************************************************/
VOS_UINT8 NAS_Gmm_Fill_IE_AdditionalMobileIdentity(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                          *pucPtmsiAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucNumber;
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT32                          ulLocalPtmsiFlg;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        enTinType;
    NAS_LMM_INFO_STRU                   stLmmInfo;

    /* Additional mobile identity ����Ĭ����Ϊ 7 */
    ucNumber            = GMM_MSG_LEN_ADDITIONAL_MOBILE_IDENTITY;

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr = NAS_MML_GetUeIdPtmsi();

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg     = VOS_FALSE;
    if ( GMM_UEID_P_TMSI == ( NAS_GMM_GetUeIdMask() & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    /* ��ȡGUTI�Ƿ���Ч  */
    ulGetGutiRst        = NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo );

    enTinType           = NAS_MML_GetTinType();

    /* 4.7.3.1.1 GPRS attach procedure initiation  */
    if ( (NAS_MML_TIN_TYPE_GUTI == enTinType)
      && (VOS_TRUE == ulGetGutiRst)
      && (VOS_TRUE == ulLocalPtmsiFlg) )
    {
        /* ��дIEI Ϊ0x1A */
        pucAddr[0] = GMM_IEI_ADDITIONAL_MOBILE_IDENTITY_VALUE;

        /* ��дPTMSI */
        NAS_GMM_Fill_IE_PtmsiFromSrc(&pucAddr[1], pucPtmsiAddr);
    }
    else
    {
        ucNumber = 0;
    }

    return ucNumber;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_Fill_IE_UeNetwrokCapacity
 ��������  : ���UE Network Capacility
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��14��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  3.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��

  4.��    ��   : 2012��5��10��
    ��    ��   : z40661
    �޸�����   : DTS2012041105159,UE Network Capability�����޸�Ϊ��LMM����
*****************************************************************************/
VOS_UINT8  NAS_GMM_Fill_IE_UeNetwrokCapacity(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucMsgLen;

    NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNetworkCap = VOS_NULL_PTR;

    pstUeNetworkCap = NAS_MML_GetUeNetWorkCapability();

    ucMsgLen   = 0x0;

    if ( (0 == pstUeNetworkCap->ucUeNetCapLen)
      || (pstUeNetworkCap->ucUeNetCapLen > NAS_MML_MAX_UE_NETWORK_CAPABILITY_LEN))
    {
        /* ����Ϊ0�򳤶ȷǷ�ʱ����Ҫ���UeNetwrokCapacity */
        return ucMsgLen;
    }

    /* ���� */
    ucMsgLen = pstUeNetworkCap->ucUeNetCapLen + 2;

    /* ��дIEI Ϊ0x58 */
    pucAddr[0] = GMM_IEI_UE_NETWORK_CAPACITY_VALUE;

    pucAddr[1] = pstUeNetworkCap->ucUeNetCapLen;

    /* ��MML��ȡNV�ж�ȡ��UE NETWORK CAPACITY,��䵽pucAddr[2] */
    PS_MEM_CPY(&(pucAddr[2]), pstUeNetworkCap->aucUeNetCap, pstUeNetworkCap->ucUeNetCapLen);


    return ucMsgLen;
}



/*****************************************************************************
 �� �� ��  : NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting
 ��������  : ���UE Voice domain preference and UE's usage setting IE��
 �������  : ��
 �������  : pucAddr,����Voice domain preference and UE's usage setting IE����������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

    TS24008-960 :Table 10.5.166A/3GPP TS 24.008: Voice domain preference and UE's usage setting information element

    Voice domain preference and UE's usage setting value (octet 3, bit 1 to 3)
    UE's usage setting (1 bit field)
    Bit
    3
    0               Voice centric
    1               Data centric

    Voice domain preference for E-UTRAN (2 bit field)
    Bit
    2   1
    0   0           CS Voice only
    0   1           IMS PS Voice only
    1   0           CS voice preferred, IMS PS Voice as secondary
    1   1           IMS PS voice preferred, CS Voice as secondary
    MS not supporting IMS voice shall indicate ��CS Voice only��.
    MS only supporting IMS voice shall indicate ��IMS PS Voice only��.

*****************************************************************************/
VOS_UINT8  NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                                               ucMsgLen;
    VOS_UINT8                                               ucIndex;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;
    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enLteUeUsageSetting;

    /* ���VoiceDomain��Ϣ */
    enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();

    /* ���UsageSetting��Ϣ */
    enLteUeUsageSetting     = NAS_MML_GetLteUeUsageSetting();

    /* �����VoiceDomain, UsageSetting����Ϣ�쳣������� */
    if ( (NAS_MML_VOICE_DOMAIN_PREFER_BUTT == enVoiceDomainPreference)
      || (NAS_MML_LTE_UE_USAGE_SETTIN_BUTT == enLteUeUsageSetting) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting:VOICE DOMAIN INVALID");
        ucMsgLen = 0;
        return ucMsgLen;
    }

    /* ��ʼ�����IE������  */
    ucIndex = 0;

    /* ��ʼ����Ϣ����Ϊ3���ֽ� */
    ucMsgLen = GMM_MSG_LEN_TLV_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING_LEN;

    /* ��дIEIΪ0x5D */
    pucAddr[ucIndex] = GMM_IEI_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING;
    ucIndex++;

    /* ��д������Ϊ1 */
    pucAddr[ucIndex] = GMM_MSG_LEN_V_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING_LEN;
    ucIndex++;

    /* �������ֽڳ�ʼ��Ϊ0 */
    pucAddr[ucIndex] = 0;

    /* �������ֽ�BITλ1��BITλ2��д����VoiceDomainPreference */
    pucAddr[ucIndex] |= enVoiceDomainPreference & NAS_MML_OCTET_LOW_TWO_BITS;

    /* �������ֽ�BITλ3��д����LteUeUsageSetting */
    pucAddr[ucIndex] |= (VOS_UINT8)(enLteUeUsageSetting << NAS_MML_OCTET_MOVE_TWO_BITS);

    return ucMsgLen;
}


#endif


/*****************************************************************************
 �� �� ��  : NAS_GMM_GetAttachRequestMsgIELength
 ��������  : ����IE�ĳ��ȣ���24008 Table 9.4.1
             �ó�������Ҫ���IE����󳤶�,IE��ʵ�ʳ����к����ֶθ���
 �������  : ��
 �������  : ������Ҫ���IE����󳤶�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_GMM_GetAttachRequestMsgIELength( VOS_VOID )
{
    VOS_UINT32                          ulMsgLen;

    /* Protocol discriminator IE����1/2�ֽڣ�
     Skip indicator IE����1/2,Attach request message identity IE����1�ֽ� */
    ulMsgLen = 2;

    /* MS Network Capability IE ����3-9�ֽ� */
    ulMsgLen += 9;

    /* Attach type IE����1/2�ֽڣ�GPRS ciphering key sequence number IE����1/2�ֽ� */
    ulMsgLen += 1;

    /* DRX parameter IE����2�ֽ� */
    ulMsgLen += 2;

    /* Mobile identity IE����6-9�ֽ� */
    ulMsgLen += 9;

    /* Old routing area identification  IE����6�ֽ� */
    ulMsgLen += 6;

    /* MS Radio Access capability IE ����6-51�ֽ� */
    ulMsgLen += 51;

    /* Old P-TMSI signature IE����4�ֽ� */
    ulMsgLen += 4;

    /* Requested READY timer value IE����2�ֽ� */
    ulMsgLen += 2;

    /* TMSI status IE����1�ֽ� */
    ulMsgLen += 1;

    /* PS LCS Capability IE����3�ֽ� */
    ulMsgLen += 3;

    /* Mobile station classmark 2 IE����5�ֽ� */
    ulMsgLen += 5;

    /* Mobile station classmark 3 IE����2-34�ֽ� */
    ulMsgLen += 34;

    /* Supported Codecs IE����5-n�ֽ� */
    ulMsgLen += 10;

    /* UE network capability IE���� 4-15�ֽ� */
    ulMsgLen += 15;

    /* Additional mobile identity IE����7�ֽ� */
    ulMsgLen += 7;

    /* Additional old routing area identification IE����8�ֽ� */
    ulMsgLen += 8;

    /* Voice domain preference and UE's usage setting IE����3�ֽ� */
    ulMsgLen += 3;

    /* Device properties IE����1�ֽ� */
    ulMsgLen += 1;

    /* P-TMSI type IE����1�ֽ� */
    ulMsgLen += 1;

    /* MS network feature support IE����1�ֽ� */
    ulMsgLen += 1;

    /* Old location area identification IE����7�ֽ� */
    ulMsgLen += 7;

    /* Additional update type IE����1�ֽ� */
    ulMsgLen += 1;

    /* TMSI based NRI container IE����4�ֽ� */
    ulMsgLen += 4;

    /* T3324 value IE����3�ֽ� */
    ulMsgLen += 3;

    /* T3312 extended value IE����3�ֽ� */
    ulMsgLen += 3;

    return ulMsgLen;
}



/*******************************************************************************
  Module   : Gmm_AttachRequestMsgMake
  Function : ATTACH Request��Ϣ����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *pAttachRequest  ָ��NAS_MSG_STRU�ṹ��ָ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2.��    ��   : 2007��06��16��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D11726
  3.��    ��   : 2007��12��15��
    ��    ��   : l00107747
    �޸�����   : ���ⵥ��:A32D13897
  4.��    ��  : 2007��12��21��
    ��    ��  : l00107747
    �޸�����  : ���ⵥ��:A32D13951
  5.��    ��  : 2011��03��04��
    ��    ��  : f00179208
    �޸�����  : ���ⵥ��:DTS2011030202965,WCDMA2100/900���������(�������ء�ON-OFF TIME MASK��PRACH����)�������һ�λػ����ӽ��в��ԣ���������ʾ�����²����쳣
  6.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  7.��    ��   : 2011��10��27��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
  8.��    ��   : 2012��02��23��
    ��    ��   : l65478
    �޸�����   : DTS2012021304254,GCF���ԣ�PS ATTACH/RAU���͵����ݰ���REL9֮�����Ϣ
  9.��    ��   : 2012��2��15��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:���������UE֧��E-UTRAN������֧��
                  CS fallback and SMS over SGs,��ATTACH��RAU������Ϣ����Ҫ��Voice
                  domain preference and UE's usage setting IE�
                  This IE shall be included:

             TS24008 9.4.1.11 Voice domain preference and UE's usage setting
                This IE shall be included:
                  if the MS supports CS fallback and SMS over SGs, or the MS is configured to support IMS voice, or both; and
                  if the MS is E-UTRAN capable.
  9.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��
  10.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
 10.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
 11.��    ��   : 2012��8��15��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
 12.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ�����·�װLMM�ṩ�Ľӿں���
 13.��    ��   : 2013��02��18��
    ��    ��   : l65478
    �޸�����   : DTS2013021700426:LTE disableʱ���ϱ���UE CAPABILITY��Ϣ
 14.��    ��   : 2013��7��8��
    ��    ��   : w00167002
    �޸�����   : DTS2013070506409:fortify�������
 15.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����   :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
 16.��    ��   : 2014��10��8��
    ��    ��   : b00269685
    �޸�����   : ��֧��srvcc����Ҫ��дclassmark1,classmark2,support code
 17.��    ��   : 2015��2��12��
    ��    ��   : s00217060
    �޸�����   : VOLTE SWITCH�޸ģ�voice domain�仯ʱ��Ҫ��RAU
 18.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 19.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
*******************************************************************************/
NAS_MSG_STRU *Gmm_AttachRequestMsgMake(VOS_VOID)
{
    NAS_MSG_STRU                               *pAttachRequest = VOS_NULL_PTR;          /* ָ��NAS_MSG_STRU�ṹ��ָ�����           */
    VOS_UINT8                                   ucNumber;                               /* ��дIEʱ��������                         */
    VOS_UINT32                                  ulMsgLen;
    VOS_UINT8                                  *pucImsi = VOS_NULL_PTR;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    VOS_UINT8                                  *pucNetworkCapabilityBuf = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_LMM_INFO_STRU                   stLmmInfo;
    VOS_INT8                                    cVersion;

    VOS_UINT32                                  ulIsLteCapabilityDisabled;

#endif

    /* �������Ϣ������ڴ��ֽڳ��ȣ���ȷ���㹻������䣬Ŀǰ������õ�172���ֽ� */
    ulMsgLen = NAS_GMM_GetAttachRequestMsgIELength();
    ucNumber                            = 2;

    pAttachRequest = (NAS_MSG_STRU*)
        PS_MEM_ALLOC(WUEPS_PID_GMM, ((sizeof(NAS_MSG_STRU) + ulMsgLen) - 4));     /* �����ڴ�ռ�                             */

    if (VOS_NULL_PTR == pAttachRequest)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_AttachRequestMsgMake:ERROR: MALLOC FAIL!");
        return pAttachRequest;                                                  /* ����                                     */
    }

    PS_MEM_SET(pAttachRequest, 0, ((sizeof(NAS_MSG_STRU) + ulMsgLen) - 4));

    pAttachRequest->aucNasMsg[0] = GMM_PD_GMM;                                  /* ��дProtocol discriminator               */
    pAttachRequest->aucNasMsg[1] = GMM_MSG_ATTACH_REQUEST;                      /* ��дAttach request message identity      */

    /*��д��������*/

    pucNetworkCapabilityBuf = &pAttachRequest->aucNasMsg[2];
    ucNumber += Gmm_Fill_IE_NetworkCapability(pucNetworkCapabilityBuf);

    /*��дAttach type and GPRS ciphering key sequence number*/
    ucNumber += NAS_Gmm_Fill_IE_AttachTypeAndCksn(&pAttachRequest->aucNasMsg[ucNumber]);

    Gmm_FillDrxPara(&pAttachRequest->aucNasMsg[ucNumber]);                      /* DRX parameter                            */
    ucNumber += 2;                                                              /* DRX parameter����Ϊ2                     */

    /* Added by t00212959 for DCM�����������������, 2012-8-16, begin */
    g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA;
    /* Added by t00212959 for DCM�����������������, 2012-8-16, end */

    /* ��д P-TMSI or imsi IE */
    /* ״̬ΪDEREGISTERED_NORMAL_SERVICE,U2ʱ ���ʹ��IMSI    */
    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();
    if ( (GMM_DEREGISTERED_NORMAL_SERVICE == NAS_GMM_GetGmmState())
      && (NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED == enPsUpdateStatus) )
    {
        /* ȡ�ñ���ά����IMSI�ĵ�ַ */
        pucImsi            = NAS_MML_GetSimImsi();
        Gmm_MemCpy(&pAttachRequest->aucNasMsg[ucNumber],
                   &pucImsi[0],
                   pucImsi[0] + 1);
        ucNumber += pucImsi[0] + 1;
    }
    else
    {
        ucNumber += NAS_Gmm_FillPtmsiIeForSnd(&pAttachRequest->aucNasMsg[ucNumber]);
    }

    /* ��д RAI IE */
    ucNumber += NAS_Gmm_FillRaiForSnd(&pAttachRequest->aucNasMsg[ucNumber]);                    /* ��дRAI                                  */

    /* ���߽���������д */
    /* Modified by z00161729 for DCM�����������������, 2012-8-17, begin */
#if (FEATURE_ON == FEATURE_LTE)
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq = g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs;
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-17, end */

    ucNumber += Gmm_Fill_IE_RadioAccessCapability(&pAttachRequest->aucNasMsg[ucNumber]);

    /* ��д P-TMSI Signature IE */
    ucNumber += NAS_Gmm_FillPtmsiSignatureIeForSnd(&pAttachRequest->aucNasMsg[ucNumber]);

    /*==>A32D11726*/
    GMM_FillReadyTimerParaIe(&pAttachRequest->aucNasMsg[ucNumber]);
    ucNumber += 2;
    /*<==A32D11726*/

    if (VOS_TRUE == NAS_GMM_IsRegNeedFillTmsiStatusIE())
    {                                                                           /* ATTACH����Ϊcombined����TMSI��Ч         */

        /* ��дTMSI status */
        pAttachRequest->aucNasMsg[ucNumber] = GMM_IEI_TMSI_STATUS_NO_VALID;     /* [false alarm]: �����Ѷ�̬���� */
        ucNumber += 1;
    }

#if (FEATURE_ON == FEATURE_LTE)

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    if (cVersion >= PS_PTL_VER_R9)
    {
        if (VOS_TRUE == NAS_MML_GetSupportSrvccFlg())
        {
            /* ��дclassmark2 */
            GMM_Fill_IE_ClassMark2(&pAttachRequest->aucNasMsg[ucNumber]);
            ucNumber += GMM_MSG_LEN_CLASSMARK2;

            /* ��дclassmark3 */
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                ucNumber += GMM_Fill_IE_FDD_ClassMark3(&pAttachRequest->aucNasMsg[ucNumber]);
            }
            else if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                ucNumber += GMM_Fill_IE_TDD_ClassMark3(&pAttachRequest->aucNasMsg[ucNumber]);
            }
            else
            {
            }

            /* ��дsupport code list */
            ucNumber += GMM_CALL_FillIeSupCodecList(&pAttachRequest->aucNasMsg[ucNumber]);

        }

        /* An MS supporting S1 mode shall include this IE to indicate its capabilities to the network */
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            /* ��дUE network Capacility */
            ulIsLteCapabilityDisabled = NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(),
                                                                NAS_MML_GetDisableLteRoamFlg());

            if (VOS_FALSE == ulIsLteCapabilityDisabled)
            {
                ucNumber += NAS_GMM_Fill_IE_UeNetwrokCapacity(&pAttachRequest->aucNasMsg[ucNumber]);
            }



            /* ��дAdditional mobile identity */
            ucNumber += NAS_Gmm_Fill_IE_AdditionalMobileIdentity(&pAttachRequest->aucNasMsg[ucNumber]);

            /* ��дAdditional old routing area identification */
            ucNumber += NAS_Gmm_Fill_IE_AdditionalOldRAI(&pAttachRequest->aucNasMsg[ucNumber]);

        }


        if (VOS_TRUE == NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE())
        {
            /* ��дVoice domain preference and UE's usage setting IE��,����Ϊ3 */
            ucNumber += NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting(&pAttachRequest->aucNasMsg[ucNumber]);
        }


        /* �����ά�ɲ���Ϣ */
        if ( VOS_TRUE == NAS_GMM_GetLteInfo(NAS_LMM_GUTI, &stLmmInfo))
        {
            NAS_GMM_LogGutiInfo(&(stLmmInfo.u.stGuti));
        }
    }
#endif
    g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq  = NAS_MML_GetVoiceDomainPreference();

    /* ��дms network feature support IE��,����Ϊ1 */
    if (PS_PTL_VER_R11 <= cVersion)
    {
        ucNumber += NAS_GMM_FillMsNetworkFeatureSupportIE(&pAttachRequest->aucNasMsg[ucNumber]);
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE())
    {
        ucNumber += NAS_GMM_FillOldLocationAreaIdentificationIE(&pAttachRequest->aucNasMsg[ucNumber]);
    }
#endif

    if (VOS_TRUE == NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE())
    {
        ucNumber += NAS_GMM_FillTmsiBasedNRIContainerIE(&pAttachRequest->aucNasMsg[ucNumber]);
    }

    /* ��д�տ���Ϣ����*/
    pAttachRequest->ulNasMsgSize = ucNumber;

    /* ����Attach���̣�����GMM��·�ͷſ��Ʊ��� */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_FALSE;



    return pAttachRequest;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetAttachComPleteMsgLen
 ��������  : ��ȡATTACH COMPLETE��Ϣ�ĳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ATTACH COMPLETE��Ϣ�ĳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��12��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��13��
   ��    ��   : L00171473
   �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetAttachComPleteMsgLen()
{
    VOS_UINT16                          usMsgLen;
    VOS_UINT8                           ucInterRatInfoFlag;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT16                          ucEUeCapDataLen = 0;
    VOS_UINT8                           aucEUeCapData[LTE_NAS_INTER_RAT_UETRAN_CAP_LEN];
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    VOS_UINT8                           ucEUtranInterRatInfoFlag = VOS_FALSE;


    PS_MEM_SET(&stLmmPlmn, 0x00, sizeof(MMC_LMM_PLMN_ID_STRU));
#endif

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag)
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&stLmmPlmn,NAS_MML_GetCurrCampPlmnId());

            ucEUeCapDataLen = LTE_NAS_INTER_RAT_UETRAN_CAP_LEN;
            if (MMC_LMM_SUCC == Nas_GetEutraUeCap(stLmmPlmn, (VOS_UINT16*)&ucEUeCapDataLen, aucEUeCapData))
            {
                if (0 != ucEUeCapDataLen)
                {
                    ucEUtranInterRatInfoFlag = VOS_TRUE;
                }
            }

        }
#endif

    if ( (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
      && (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg)
      && (0 != g_GmmInterRatInfoCtrl.ucDataLen))
    {
        ucInterRatInfoFlag = VOS_TRUE;
    }
    else
    {
        ucInterRatInfoFlag = VOS_FALSE;
    }

    usMsgLen = sizeof(NAS_MSG_STRU);

    if ((VOS_TRUE == ucInterRatInfoFlag)
#if (FEATURE_ON == FEATURE_LTE)
      || (VOS_TRUE == ucEUtranInterRatInfoFlag)
#endif
     )
     {
         usMsgLen = (sizeof(NAS_MSG_STRU) - 4) + GMM_MSG_LEN_ATTACH_COMPLETE;
     }

    /* ����UTRAN INTER RAT INFOMATION */
    if (VOS_TRUE == ucInterRatInfoFlag)
    {
        usMsgLen += 2 + g_GmmInterRatInfoCtrl.ucDataLen ;
    }

    /* ����E-UTRAN INTER RAT INFORMATION */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == ucEUtranInterRatInfoFlag)
    {
        usMsgLen += 2 + ucEUeCapDataLen;
    }
#endif

    return usMsgLen;

}

/*******************************************************************************
  Module   : Gmm_AttachCompleteMsgMake
  Function : ATTACH Complete��Ϣ����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *pAttachComplete    ָ��NAS_MSG_STRU�ṹ��ָ��
  History  :
  1. ��־��  2003.12.09  �¹�����

  2.��    ��   : 2010��3��29��
    ��    ��   : o00132663
    �޸�����   : NAS R7Э��������InterRatHandoverInfo��Ϣ�ӿڱ��
 12.��    ��   : 2012��05��13��
    ��    ��   : W00166186
    �޸�����   : DTS201204261955,RAU COMPLETEû�лظ�
 13.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
*******************************************************************************/
NAS_MSG_STRU* Gmm_AttachCompleteMsgMake(VOS_VOID)
{
    NAS_MSG_STRU                       *pAttachComplete = VOS_NULL_PTR;                                       /* ָ��NAS_MSG_STRU�ṹ��ָ�����           */
    VOS_UINT16                          usMsgLen;
    VOS_BOOL                            bInterRatInfoFlg;
    VOS_UINT16                          usIeOffset       = GMM_MSG_LEN_ATTACH_COMPLETE;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT16                          usEUeCapDataLen = 0;
    VOS_UINT8                           aucEUeCapData[LTE_NAS_INTER_RAT_UETRAN_CAP_LEN] = {0};
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;


    PS_MEM_SET(&stLmmPlmn, 0x00, sizeof(stLmmPlmn));
#endif

    if ( (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
      && (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg)
      && (0 != g_GmmInterRatInfoCtrl.ucDataLen))
    {
        bInterRatInfoFlg = VOS_TRUE;
    }
    else
    {
        bInterRatInfoFlg = VOS_FALSE;
    }

    usMsgLen = NAS_GMM_GetAttachComPleteMsgLen();

    pAttachComplete = (NAS_MSG_STRU *)Gmm_MemMalloc(usMsgLen);
    if (VOS_NULL_PTR == pAttachComplete)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_AttachCompleteMsgMake:ERROR: MALLOC FAIL!");
        return VOS_NULL_PTR;
    }

    Gmm_MemSet(pAttachComplete, 0, usMsgLen);

    /* ��д�տ���Ϣ����             */
    pAttachComplete->ulNasMsgSize = GMM_MSG_LEN_ATTACH_COMPLETE;
    pAttachComplete->aucNasMsg[0] = GMM_PD_GMM;
    pAttachComplete->aucNasMsg[1] = GMM_MSG_ATTACH_COMPLETE;

    if (VOS_TRUE == bInterRatInfoFlg)
    {
        /*lint -e961*/
        pAttachComplete->ulNasMsgSize = GMM_MSG_LEN_ATTACH_COMPLETE
                                        + 2 + g_GmmInterRatInfoCtrl.ucDataLen;
        pAttachComplete->aucNasMsg[usIeOffset++] = GMM_IEI_INTER_RAT_HANDOVER_INFORMATION;
        pAttachComplete->aucNasMsg[usIeOffset++] = g_GmmInterRatInfoCtrl.ucDataLen;
        /*lint +e961*/
        Gmm_MemCpy(&(pAttachComplete->aucNasMsg[4]), g_GmmInterRatInfoCtrl.aucData,
                    g_GmmInterRatInfoCtrl.ucDataLen);
        usIeOffset += g_GmmInterRatInfoCtrl.ucDataLen;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ȡUTRAN INTER RAT INFO */
    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag)
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&stLmmPlmn,NAS_MML_GetCurrCampPlmnId());

        usEUeCapDataLen = LTE_NAS_INTER_RAT_UETRAN_CAP_LEN;
        if (MMC_LMM_SUCC != Nas_GetEutraUeCap(stLmmPlmn, &usEUeCapDataLen, aucEUeCapData))
        {
            usEUeCapDataLen = 0;
        }
    }

    if ((VOS_TRUE == g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag)
     && (0 != usEUeCapDataLen))
    {
        pAttachComplete->ulNasMsgSize += 2 + usEUeCapDataLen;
        /*lint -e961*/
        pAttachComplete->aucNasMsg[usIeOffset++] = GMM_IEI_E_UTRAN_INTER_RAT_HANDOVER_INFORMATION;      /* [false alarm]: �����Ѷ�̬���� */
        pAttachComplete->aucNasMsg[usIeOffset++] = (VOS_UINT8)usEUeCapDataLen;                          /* [false alarm]: �����Ѷ�̬���� */
        /*lint +e961*/
        Gmm_MemCpy(&(pAttachComplete->aucNasMsg[usIeOffset]), aucEUeCapData,
                    usEUeCapDataLen);
    }

    /* ��ȡUTRAN INTER RAT INFO �󽫱�־��� */
    g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag = VOS_FALSE;

#endif

    /* ȫ�ֱ�����λ */
    Gmm_MemSet(&g_GmmInterRatInfoCtrl, 0, sizeof(GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU));

    return pAttachComplete;
}

/*******************************************************************************
  Module   : Gmm_DelPsLocInfoUpdateUsim
  Function : ɾ��SIM�������Ϣ�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.08  �¹�����
  2. ��־��  2004.10.27  CK��IK�洢�ṹ���
  3. ��    ��   : 2006��11��7��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D06823
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ,PTMSI�����ı�ʱ�ϱ���OM
*******************************************************************************/
VOS_VOID Gmm_DelPsLocInfoUpdateUsim(VOS_VOID)
{
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_PLMN_ID_STRU                        stGmmPlmnId;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmPlmnId);

    g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_P_TMSI;                /* ���P_TMSI����MASK                       */
    g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_P_TMSI_SIGNATURE;      /* ���P_TMSI_SIGNATURE����MASK             */

    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {                                                                       /* sim����Ч                                */
        /* �����ر�־ */
        NAS_GMM_ClearIMSIOfUeID();
    }

    /* ��PTMSI�� Ptmsi Signature����Ϊ��Ч  */
    NAS_MML_InitUeIdPtmisInvalid();
    NAS_MML_InitUeIdPtmsiSignatureInvalid();

    pstLastSuccRai->stLai.aucLac[0]            = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstLastSuccRai->stLai.aucLac[1]            = NAS_MML_LAC_HIGH_BYTE_INVALID;


    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);      /* ֪ͨAGENTɾ��PSlocation information      */
    }
    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                        /* ֪ͨRRC NAS����Ϣ�仯                    */

#if (FEATURE_ON == FEATURE_PTM)
    /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
    NAS_GMM_SndAcpuOmChangePtmsi();
#endif

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);
    }
    if (NAS_MML_CKSN_INVALID != NAS_MML_GetSimPsSecurityCksn())
    {                                                                           /* ԭ����Key�鱨��Ч                        */
        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);            /* ɾ��CKSN                                 */
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();

        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);                    /* ֪ͨAGENTɾ��PS�������Ϣ                */

        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DEL_KEY);                      /* ֪ͨRRC NAS����Ϣ�仯                    */

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_DelPsLocInfoUpdateUsim: NAS_MML_CKSN_INVALID");
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachRejectCause3
  Function : �տ���ϢATTACH REJECTԭ��ֵΪ#3,#6,#7,#8�Ĵ���
  Input    : VOS_UINT32 ulGmmCause  ʧ��ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2006��9��9��
    ��    ��   : sunxibo id:46746
    �޸�����   : �������ⵥ�ţ�A32D05604
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2011��10��08��
    ��    ��   : W00167002
    �޸�����  : V7R1 PhaseII�׶ε���������/ɾ��Eplmn�Ĺ�����ԭ�ȵ�MMCģ�����Ϊ
                 GMM/MMģ�鴦��
*******************************************************************************/
VOS_VOID Gmm_AttachRejectCause3(
                            VOS_UINT32 ulGmmCause                                    /* ʧ��ԭ��                                 */
                            )
{
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */

    /* ����GMM�Ŀ���Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    Gmm_DelPsLocInfoUpdateUsim();                                               /* ���ú���ɾ��PS LOCATION INFO             */

    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* ����״̬��������                         */

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || ( GMM_ATTACH_NORMAL      == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* NORMAL ATTACH                            */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulGmmCause);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {                                                                           /* ��ǰ����Ϊcombined attach����            */
        NAS_GMM_SndMmCombinedAttachRejected(ulGmmCause);                        /* ����MMCGMM_COMBINED_ATTACH_REJECTED��MMC */

    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulGmmCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &ulGmmCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    NAS_GMM_DeleteEPlmnList();

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachRejectCause11
  Function : �տ���ϢATTACH REJECTԭ��ֵΪ#11�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.02.03  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��10��08��
    ��    ��   : W00167002
    �޸�����  : V7R1 PhaseII�׶ε���������/ɾ��Eplmn�Ĺ�����ԭ�ȵ�MMCģ�����Ϊ
                 GMM/MMģ�鴦��
*******************************************************************************/
VOS_VOID Gmm_AttachRejectCause11(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */
    Gmm_DelPsLocInfoUpdateUsim();                                               /* ���ú���ɾ��PS LOCATION INFO             */
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* ����״̬��������                         */

    g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                      /* attach attempt counter��0                */

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* NORMAL ATTACH                            */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {                                                                           /* combined attach����                      */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */

        NAS_GMM_SndMmCombinedAttachRejected(enCause);          /* ����MMCGMM_COMBINED_ATTACH_REJECTED��MMC */
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 enCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &enCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    NAS_GMM_DeleteEPlmnList();


    return;
}
/*******************************************************************************
  Module   : Gmm_AttachRejectCause12
  Function : �տ���ϢATTACH REJECTԭ��ֵΪ#12,#13,#15�Ĵ���
  Input    : VOS_UINT32 ulGmmCause  ʧ��ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.02.03  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��10��8��
    ��    ��   : s46746
    �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��
*******************************************************************************/
VOS_VOID Gmm_AttachRejectCause12(
                             VOS_UINT32 ulGmmCause,                                   /* ʧ��ԭ��                                 */
                             VOS_BOOL   bUpdateSimFlg
                             )
{
    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == ulGmmCause)
    {
        g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
    }
    if (VOS_TRUE == bUpdateSimFlg)
    {
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */
        Gmm_DelPsLocInfoUpdateUsim();                                               /* ���ú���ɾ��PS LOCATION INFO             */
    }
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* ����״̬��������                         */
    g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                      /* attach attempt counter��0                */

    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == ulGmmCause)
    {                                                                           /* ԭ��ֵΪLA_NOT_ALLOW(12)                 */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
    }
    else if (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == ulGmmCause)
    {
        NAS_GMM_DeleteEPlmnList();

        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;
    }
    else
    {                                                                           /* ԭ��ֵΪ13,15  */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;
    }

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* NORMAL ATTACH                            */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulGmmCause);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {                                                                           /* combined attach����                      */
        NAS_GMM_SndMmCombinedAttachRejected(ulGmmCause);                           /* ����MMCGMM_COMBINED_ATTACH_REJECTED��MMC */
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulGmmCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &ulGmmCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    return;
}

/*******************************************************************************
  Module   : Gmm_AttachRejectCause14
  Function : �տ���ϢATTACH REJECTԭ��ֵΪ#14�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.02.03  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2015��6��3��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachRejectCause14(VOS_BOOL   bUpdateSimFlg)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.3.1.4�½���������:
    #14 The MS shall delete any RAI, P-TMSI, P-TMSI signature, and GPRS ciphering
    key sequence number stored, shall set the GPRS update status to GU3 ROAMING
    NOT ALLOWED (and shall store it according to subclause 4.1.3.2), shall reset
    the GPRS attach attempt counter and shall change to state GMM-DEREGISTERED */

    g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

    if (VOS_TRUE == bUpdateSimFlg)
    {
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */
        Gmm_DelPsLocInfoUpdateUsim();                                               /* ���ú���ɾ��PS LOCATION INFO             */
    }
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN_FOR_GPRS;
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* ����״̬��������                         */

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* NORMAL ATTACH                            */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN);                                    /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {                                                                           /* combined attach                          */
        NAS_GMM_SndMmCombinedAttachRejected(
                                     NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN); /* ����MMCGMM_COMBINED_ATTACH_REJECTED��MMC */
    }

    enCause = NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN;
    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 enCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &enCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAttemptCounter
  Function : Attach Attempt Counter�Ĵ���
  Input    : VOS_UINT32 ulGmmCause  ʧ��ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2011��10��08��
    ��    ��   : W00167002
    �޸�����  : V7R1 PhaseII�׶ε���������/ɾ��Eplmn�Ĺ�����ԭ�ȵ�MMCģ�����Ϊ
                 GMM/MMģ�鴦��
  4.��    ��   : 2011��10��08��
    ��    ��   : m00217266
    �޸�����  : PS��������ϱ��޸�, GMM/SM�ӿڵ���, ����ԭ��ֵ�ϱ�
  5.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Gmm_AttachAttemptCounter(
                              VOS_UINT32 ulGmmCause                                  /* ʧ��ԭ��                                 */
                              )
{
    g_GmmAttachCtrl.ucAttachAttmptCnt++;                                        /* Attach Attempt Counter��1                */
    Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);                       /* ����״̬��������                         */


    if (5 > g_GmmAttachCtrl.ucAttachAttmptCnt)
    {                                                                           /* Attach attempt counter<5                 */
        Gmm_TimerStart(GMM_TIMER_T3311);                                        /* ����Timer3311                            */
    }
    else
    {                                                                           /* Attach attempt counter>=5                */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* ����״̬��ΪGU2                          */

        /* ��U2״̬��Ǩ��attempting to attach״̬���浱ǰ��RAI��Ϣ */
        NAS_GMM_SetAttemptUpdateRaiInfo(NAS_MML_GetCurrCampPlmnInfo());

        Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOCATION INFO             */

        Gmm_TimerStart(GMM_TIMER_T3302);                                        /* ����Timer3302                            */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                           /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ATTACH_MAX_TIMES);       /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }

        NAS_GMM_DeleteEPlmnList();

    }

    if (NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT == ulGmmCause)
    {                                                                       /* T3310 time-out 5��                       */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                                /* �ͷ�PS ��ϵͳ��Ϣ                        */
    }

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* NORMAL ATTACH                            */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulGmmCause);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {                                                                           /* combined attach                          */
        NAS_GMM_SndMmCombinedAttachRejected(ulGmmCause);                           /* ����MMCGMM_COMBINED_ATTACH_REJECTED��MMC */
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulGmmCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    (VOS_VOID*)&ulGmmCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    return;
}


/*******************************************************************************
  Module   : Gmm_RcvAttachRejectMsg_T3302_Handling
  Function : ���տտ���ϢATTACH REJECT,��T3302��ʱ���Ĵ���
  Input    : NAS_MSG_STRU *pMsg  ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : VOS_UINT8, GMM_FAILURE/GMM_SUCCESS
  History  :
    1. ŷ����  2010.01.03  �����Ӷȣ������º���
    2.��    ��   : 2011��3��3��
      ��    ��   : z00161729
      �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
    3.��    ��   : 2013��11��18��
      ��    ��   : w00167002
      �޸�����   : DTS2013112006986:������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                   TD�²�����SMC���̡�
    4.��    ��   : 2015��6��10��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_UINT8 Gmm_RcvAttachRejectMsg_T3302_Handling(NAS_MSG_FOR_PCLINT_STRU *pMsg)
{
    NAS_MSG_STRU        *pGmmStatus;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* 24.008: 9.4.4
      In Iu mode, the MS shall ignore the contents of this IE if this message is received without
      integrity protection.
      If this IE is not included or if in Iu mode the message is not integrity protected,
      the MS shall use the default value. */
    if (GMM_IEI_T3302_VALUE == pMsg->aucNasMsg[GMM_MSG_LEN_ATTACH_REJECT])
    {                                                                       /* ��Ϣ�к���T3302 value                    */
        if (((GMM_MSG_LEN_ATTACH_REJECT + 1)==pMsg->ulNasMsgSize)
            || ((GMM_MSG_LEN_ATTACH_REJECT + 2)==pMsg->ulNasMsgSize))
        {
        }
        else
        {
            if (1 != pMsg->aucNasMsg[GMM_MSG_LEN_ATTACH_REJECT + 1])
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachRejectMsg:WARNING: Semantically incorrect message!");
                pGmmStatus = Gmm_GmmStatusMsgMake(
                                 NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);
                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

                return GMM_FAILURE;
            }

            if ( (VOS_TRUE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())
              && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE != g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) )
            {                                                               /* If in Iu mode the message is not integrity protected, the MS shall use the default value */
                g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
            }
            else
            {
                Gmm_SaveTimerValue(GMM_TIMER_T3302,
                   pMsg->aucNasMsg[GMM_MSG_LEN_ATTACH_REJECT + 2]); /* �洢T3302ʱ��                            */

                PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(),sizeof(stPlmnWithRat.stPlmnId));
                stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

                NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);
            }
        }
    }
    else
    {                                                                       /* If this IE is not included , the MS shall use the default value */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
    }

    return GMM_SUCCESS;
}

/*******************************************************************************
  Module   : Gmm_RcvAttachRejectMsg_Cause_Handling_Other_Cause
  Function : ���տտ���Ϣ�տ���ϢATTACH REJECT,��Rej Cause:ȱʡԭ��ֵ�Ĵ���
  Input    : VOS_UINT8 ucCause : Reject Cause
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.ŷ����  2010.01.03  �����Ӷȣ������º���
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Gmm_RcvAttachRejectMsg_Cause_Handling_Other_Cause(VOS_UINT8 ucCause)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachRejectMsg:WARNING: GMM CAUSE is abnormal");

    NAS_GMM_UpdateAttemptCounterForSpecialCause(VOS_TRUE, ucCause);

    if ((NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN    <= ucCause)
        && (NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX >= ucCause))
    {
        g_GmmAttachCtrl.ucRetryFlg = GMM_TRUE;                              /* �û�С������ATTACH��־                   */
    }
    else
    {
        g_GmmAttachCtrl.ucRetryFlg = GMM_FALSE;                             /* �����С������ATTACH��־                 */
    }

    Gmm_AttachAttemptCounter(ucCause);                           /* �����쳣������                         */

    return;

}

/*****************************************************************************
 �� �� ��  : Gmm_RcvAttachRejectMsg_Cause_Handling
 ��������  :��ATTACH�ܾ���ԭ��ַ�����
 �������  : ucGmmCause   �ܾ���ԭ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��20��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2. ��    ��   : 2011��7��10��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������

  4.��    ��   : 2012��8��25��
    ��    ��   : m00217266
    �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                ���浼��Attachʧ�ܵ�ԭ��ֵ
*****************************************************************************/
VOS_VOID Gmm_RcvAttachRejectMsg_Cause_Handling(VOS_UINT8 ucCause)
{
    /* ����ע��ʧ��ԭ��ֵ */
    NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(ucCause));

    switch (ucCause)
    {                                                                           /* GMM CAUSE                                */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Gmm_AttachRejectCause3(ucCause);                             /* ����#3,#6,#7,#8������                  */
        if (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW == ucCause)
        {                                                                       /* ԭ��ֵ7                                  */
            if ((GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg)
                && (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg))
            {                                                                   /* Ҫ����LU                                 */
                NAS_GMM_SndMmLuInitiation(MMC_GMM_NO_TIMER_EXPIRED);              /* ֪ͨMM����LU                             */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        Gmm_AttachRejectCause11();                                              /* ����#11������                          */
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Gmm_AttachRejectCause12(ucCause, VOS_TRUE);                            /* ����#12,#13,#15������                  */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        Gmm_AttachRejectCause14(VOS_TRUE);                                              /* ����#14������                          */
        if ((GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg)
            && (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg))
        {                                                                       /* Ҫ����LU                                 */
            NAS_GMM_SndMmLuInitiation(MMC_GMM_NO_TIMER_EXPIRED);                  /* ֪ͨMM����LU                             */
        }
        break;
    default:
        Gmm_RcvAttachRejectMsg_Cause_Handling_Other_Cause(ucCause);
        break;
    }

    NAS_GMM_CheckCauseToStartT3340(ucCause);
}

/* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */

/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertGmmAttachTypeToStkRauType
 ��������  : ��������ת��:NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8->NAS_STK_UPDATE_TYPE_ENUM_UINT8
 �������  : NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8 enGmmRauType MM���Attach TYPE
 �������  :
 �� �� ֵ  : NAS_STK_UPDATE_TYPE_ENUM_UINT8 �ϱ���STK��Attach TYPE
 ���ú���  : NAS_GMM_SndStkAttachRej
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

*****************************************************************************/
NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_GMM_ConvertGmmAttachTypeToStkRauType (
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enGmmAttachType
)
{
    switch (enGmmAttachType)
    {
        case GMM_ATTACH_COMBINED:
             return NAS_STK_ATTACH_COMBINED;

        case GMM_ATTACH_WHILE_IMSI_ATTACHED:
             return NAS_STK_ATTACH_WHILE_IMSI_ATTACHED;

        case GMM_ATTACH_NORMAL:
             return NAS_STK_ATTACH_NORMAL;

        case GMM_ATTACH_NORMAL_CS_TRANS:
             return NAS_STK_ATTACH_NORMAL_CS_TRANS;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ConvertGmmAttachTypeToStkRauType:WARNING: The input in invalid");
            return NAS_STK_UPDATE_TYPE_ENUM_BUTT;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ReportStkAttachRej
 ��������  : GMM�ϱ�Network Rejection Event
 �������  : ucGmmCause   �ܾ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  : Gmm_RcvAttachRejectMsg()
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

*****************************************************************************/
VOS_VOID NAS_GMM_SndStkAttachRej(VOS_UINT8 ucCause)
{
    NAS_STK_NETWORK_REJECTION_EVENT_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAI_STRU                                       *pstRai = VOS_NULL_PTR;

    /* �����ڴ� */
    ulLength = sizeof(NAS_STK_NETWORK_REJECTION_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_NETWORK_REJECTION_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ReportStkAttachRej: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stNetworkRejectionEvent), 0, sizeof(NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU));

    /* ��д����Ϣ���� */
    pstMsg->ulReceiverPid   = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstRai =  NAS_MML_GetCurrCampLai();
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.stCurPlmnID.Mcc = pstRai->stPlmnId.ulMcc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.stCurPlmnID.Mnc = pstRai->stPlmnId.ulMnc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.usLac           = (pstRai->aucLac[0] << 8) | (pstRai->aucLac[1]);
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.ucRac           = NAS_MML_GetCurrCampRac();
    pstMsg->stNetworkRejectionEvent.enRejType                 = NAS_STK_ATTACH_REJECT;

    pstMsg->stNetworkRejectionEvent.enRat                     = NAS_GMM_ConvertGmmRatTypeToStkRatType(pstRai->enCampPlmnNetRat);

    pstMsg->stNetworkRejectionEvent.ucCauseCode               = ucCause;

    pstMsg->stNetworkRejectionEvent.enUpdateAttachType        = NAS_GMM_ConvertGmmAttachTypeToStkRauType(NAS_GMM_GetSpecProc());

    pstMsg->ulMsgName                                         = ID_NAS_STK_NETWORK_REJECTION_EVENT;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_GMM, pstMsg))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ReportStkAttachRej: PS_SEND_MSG ERROR");
    }

    return;
}
/* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

/*****************************************************************************
 �� �� ��  : NAS_GMM_ResetRejCauseChangedCounter
 ��������  : �յ�Accept��Ϣʱresetȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��  : 2014��10��27��
    ��    ��  : h00285180
    �޸�����  : ���ⵥ��:DTS2014110307415
*****************************************************************************/
VOS_VOID NAS_GMM_ResetRejCauseChangedCounter (VOS_VOID)
{
    NAS_MML_ResetHplmnPsRejCauseChangedCounter();
    NAS_MML_ResetVplmnPsRejCauseChangedCounter();
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleHplmnRejCauseChange
 ��������  : HPLMN�޸ľܾ�ԭ��ֵ�������Ҫ���ܾ�ԭ��ֵ�޸�Ϊ#17��ά���޸�Ϊ#17������ȫ�ֱ���
 �������  : NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType��������
             VOS_UINT8                          *pucRcvMsgԭ�оܾ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : h00285180
    �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
*****************************************************************************/
VOS_VOID NAS_GMM_HandleHplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
)
{
    VOS_UINT8                           ucAdaptCause = 0;

    ucAdaptCause = NAS_MML_GetHplmnChangeNWCause(enChangeRejType, *pucRcvMsg);
    if (ucAdaptCause == *pucRcvMsg)
    {
        /* δ���ҵ��滻��ԭ��ֵ�����滻��ԭ��ֵ���� */
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucAdaptCause)
    {
        if (VOS_TRUE != NAS_MML_GetHplmnPsRejChangeTo17Flg())
        {
            /* ����滻��ԭ��ֵΪ#17�����滻�������Ѿ��ﵽ���ޣ������滻 */
            return;
        }

        /* ������+1 */
        NAS_MML_IncHplmnPsRejCauseChangedCounter();
    }

    /* ����滻���ԭ��ֵ��#17�����滻���ԭ��ֵΪ#17���滻����δ�ﵽ���ޣ����滻 */
    *pucRcvMsg = ucAdaptCause;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleVplmnRejCauseChange
 ��������  : VPLMN�޸ľܾ�ԭ��ֵ�������Ҫ���ܾ�ԭ��ֵ�޸�Ϊ#17��ά���޸�Ϊ#17������ȫ�ֱ���
 �������  : NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType��������
             VOS_UINT8                          *pucRcvMsgԭ�оܾ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : h00285180
    �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
*****************************************************************************/
VOS_VOID NAS_GMM_HandleVplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
)
{
    VOS_UINT8                           ucAdaptCause = 0;

    ucAdaptCause = NAS_MML_GetVplmnChangeNWCause(enChangeRejType, *pucRcvMsg);
    if (ucAdaptCause == *pucRcvMsg)
    {
        /* δ���ҵ��滻��ԭ��ֵ�����滻��ԭ��ֵ���� */
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucAdaptCause)
    {
        if (VOS_TRUE != NAS_MML_GetVplmnPsRejChangeTo17Flg())
        {
            /* ����滻��ԭ��ֵΪ#17�����滻�������Ѿ��ﵽ���ޣ������滻 */
            return;
        }

        /* ������+1 */
        NAS_MML_IncVplmnPsRejCauseChangedCounter();
    }

    /* ����滻���ԭ��ֵ��#17�����滻���ԭ��ֵΪ#17���滻����δ�ﵽ���ޣ����滻 */
    *pucRcvMsg = ucAdaptCause;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ChangeRegRejCauseAvoidInvalidSim
 ��������  : ע�����(ATTACH/RAU)�ܾ�ԭ��ֵ����Ӧ
 �������  : VOS_UINT8 *pucRcvMsg  ָ��ԭʼ�ܾ�ԭ��ֵ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : h00285180
    �޸�����   : �ܾ�ԭ��ֵPhaseII DTS2014110307415
*****************************************************************************/
VOS_VOID NAS_GMM_ChangeRegRejCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ChangeRegRejCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    NAS_MML_SetOriginalRejectCause(*pucRcvMsg);
    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_GMM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_PS_REG, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_GMM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_PS_REG, pucRcvMsg);
    }
}

/*******************************************************************************
  Module   : Gmm_RcvAttachRejectMsg
  Function : ���տտ���Ϣ�տ���ϢATTACH REJECT�Ĵ���
  Input    : NAS_MSG_STRU *pMsg  ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��    ��   : 2006��11��7��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D06823
    3.��    ��   : 2011��3��6��
      ��    ��   : l65478
      �޸�����   : DTS2011052703809,GCF����9.4.2.2.1ʧ��,��ΪGMM������������GMM STATUS��Ϣ
    4.��    ��   : 2013��7��13��
      ��    ��   : l00208543
      �޸�����   : STK������Ŀ������NAS_GMM_ReportStkAttachRej�ĵ�����STK�ϱ�reject��Ϣ
    5.��    ��   : 2013��10��9��
      ��    ��   : l00208543
      �޸�����   : DTS2013100904573
    6.��    ��   : 2014��10��20��
      ��    ��   : h00285180
      �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
*******************************************************************************/
VOS_VOID Gmm_RcvAttachRejectMsg(
                            NAS_MSG_FOR_PCLINT_STRU *pMsg
                            )
{
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8            ucRst;


    if (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
    {
        /* GMM״̬����GMM_REGISTERED_INITIATED����������Ϣ */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachRejectMsg:WARNING: GMM's state is not GMM_REGISTERED_INITIATED");

        return;
    }

    if (GMM_MSG_LEN_ATTACH_REJECT > pMsg->ulNasMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachRejectMsg:WARNING: The Msg's length is not enough!");
        /* ��Ϣ����                                 */
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    ucRst = Gmm_RcvAttachRejectMsg_T3302_Handling(pMsg);

    if( GMM_FAILURE == ucRst)
    {
        return;
    }

    NAS_GMM_ChangeRegRejCauseAvoidInvalidSim(&(pMsg->aucNasMsg[2]));

    /* Added by l00208543 for V9R1 STK����, 2013-07-11, begin */
    NAS_GMM_SndStkAttachRej(pMsg->aucNasMsg[2]);
    /* Added by l00208543 for V9R1 STK����, 2013-07-11, end */

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ֹͣTimer3310                            */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    Gmm_RcvAttachRejectMsg_Cause_Handling(pMsg->aucNasMsg[2]);

    if (VOS_FALSE == NAS_GMM_IsAttachOtherCause(pMsg->aucNasMsg[2]))
    {
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                           /* ATTACH��������SM������                   */

            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE,
                                  NAS_GMM_TransGmmNwCause2GmmSmCause(pMsg->aucNasMsg[2]));    /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
        }

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
    }

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                         /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                         /* ������ڽ��е�specific���̱�־           */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvAttachRejectMsg:INFO: specific procedure ended");

    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���fallowon��־                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachRauAcceptCause16
  Function : ATTACH��RAU������ʱԭ��ֵΪ16��17��22�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2008��7��25��
      ��    ��   : luojian 00107747
      �޸�����   : �������ⵥ��AT2D04142/AT2D04677
    3.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachRauAcceptCause16(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGmmCause
)
{
    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    else
    {
        /* ����״̬��������  */
        Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM);

        /**************************************************************************
        3gpp 24.008 4.7.3,4.7.3.2.3.2 The GPRS attach attempt counter shall be reset
        and the routing area updating attempt counter shall be incremented  when:a
        combine GPRS attach procedure is completed for GPRS services only with cause
        #2, #16, #17 or #22;
        ***************************************************************************/
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        g_GmmRauCtrl.ucRauAttmptCnt++;

        /* 24008_CR2203R2_(Rel-11)_C1-123379 24008 4.7.3.2.3.2��������:
        #22 :The MS shall change to state GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM.
        The timer T3310 shall be stopped if still running. The MS shall set the routing area
        updating attempt counter to 5 and shall start the timer T3302.
        4.7.5.2.3.2��������:
        #22:The MS shall change to state GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM.
        The timer T3310 shall be stopped if still running. The MS shall set the routing
        area updating attempt counter to 5 and shall start timer T3302.*/
        if ((PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
         && (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enGmmCause))
        {
            g_GmmRauCtrl.ucRauAttmptCnt = GMM_ATTACH_RAU_ATTEMPT_MAX_CNT;
            Gmm_TimerStop(GMM_TIMER_T3310);
        }

        if (GMM_ATTACH_RAU_ATTEMPT_MAX_CNT > g_GmmRauCtrl.ucRauAttmptCnt)
        {                                                                           /* RAU attempt counterû�дﵽ���          */
            Gmm_TimerStart(GMM_TIMER_T3311);                                        /* ����Timer3311                            */
        }
        else
        {                                                                           /* RAU attempt counter�ﵽ���              */
            Gmm_TimerStart(GMM_TIMER_T3302);                                        /* ����Timer3302                            */
        }
    }

    return;
}



/*******************************************************************************
  Module   : Gmm_SaveTimerValue
  Function : �洢T3302/T3312ʱ��
  Input    : VOS_UINT8 ucTimNam   Timer����
             VOS_UINT8 ucMsgByte  ��Ϣ��ʱ��λ�õ��ֽ�
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2011��3��3��
      ��    ��   : z00161729
      �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
*******************************************************************************/
VOS_VOID Gmm_SaveTimerValue(
                        VOS_UINT8 ucTimNam,                                         /* Timer����                                */
                        VOS_UINT8 ucMsgByte                                         /* ��Ϣ��ʱ��λ�õ��ֽ�                     */
                        )
{
    VOS_UINT8   ucUnit       = 0;                                                   /* ������ʱ�����洢ʱ����λ                 */
    VOS_UINT8   ucTimerValue = 0;                                                   /* ������ʱ�����洢ʱ��                     */
    VOS_UINT32  ulT3312OldValue = 0;                                                /* ������ʱ�����洢T3312��ǰʱ��            */

    ulT3312OldValue = g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal;

    ucUnit = (VOS_UINT8)(ucMsgByte >> 5);                                           /* �õ�ʱ����λ                             */
    ucTimerValue = (VOS_UINT8)(ucMsgByte & 0x1F);                                   /* �õ�Timer Value                          */
    switch (ucUnit)
    {                                                                           /* �ж�ʱ����λ                             */
    case 0:                                                                     /* 2 seconds                                */
        g_GmmTimerMng.aTimerInf[ucTimNam].ulTimerVal
            = ucTimerValue * 2 * 1000;
        break;
    case 1:                                                                     /* 1 minute                                 */
        g_GmmTimerMng.aTimerInf[ucTimNam].ulTimerVal
            = ucTimerValue * 60 * 1000;
        break;
    case 2:                                                                     /* decihours                                */
        g_GmmTimerMng.aTimerInf[ucTimNam].ulTimerVal
            = ucTimerValue * 360 * 1000;
        break;
    case 7:                                                                     /* timer is deactivated                     */
        g_GmmTimerMng.aTimerInf[ucTimNam].ulTimerVal = 0;
        break;
    default:
        g_GmmTimerMng.aTimerInf[ucTimNam].ulTimerVal
            = ucTimerValue * 60 * 1000;
        break;
    }

    /* 24.008: 4.7.2.2
      In Iu mode, if the value of timer T3312 is received in a message without integrity protection
      and the indicated value is larger than the last received value,
      or the indicated value is "deactivated" or zero, the MS shall use the last received value.*/
    if (GMM_TIMER_T3312 == ucTimNam)
    {

        /* �����ǰ��TD�£����ò���Ҫ���PS���SMC������ΪSMC�Ѿ��յ��� */
        if ((VOS_TRUE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())
         && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE != g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect))
        {
            if ((g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal > ulT3312OldValue)
                || (0 == g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal))
            {
                if (0 != ulT3312OldValue)
                {                                                           /* �ɵ�3312ֵ��Ч������Ϊ�ɵ�ֵ                 */
                    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal = ulT3312OldValue;
                }
                else
                {                                                           /* �ɵ�3312ֵ��Ч������Ϊ3312��ȱʡֵ           */
                    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal = GMM_TIMER_T3312_VALUE;
                }

            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  :NAS_GMM_DecodeT3323ValueIERcvAttachAccept
 ��������  :��Ȧ���Ӷȣ���attach accept��Ϣ�н���T3323 value IE����
 �������  :pRauAcceptIe - ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��
            pMsg         - ָ��NAS_MSG_STRU�ṹ��ָ��
            ucIeOffset   - T3323 value IE����Ϣ������λ��
 �������  :��
 �� �� ֵ  :VOS_TRUE  - ����ɹ�
            VOS_FALSE - ����ʧ��
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_DecodeT3323ValueIERcvAttachAccept(
    GMM_MSG_RESOLVE_STRU              *pAttachAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU           *pMsg,
    VOS_UINT8                          ucIeOffset
)

{
    if ( (ucIeOffset + 3) > (VOS_UINT8)pMsg->ulNasMsgSize )
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_DecodeT3323ValueIERcvAttachAccept:WARNING: IE\"T332\" length error in ATTACH ACCEPT");
        return VOS_FALSE;
    }

    if (GMM_ATTACH_ACCEPT_IE_T3323_VALUE_FLG == (pAttachAcceptIe->ulOptionalIeMask & GMM_ATTACH_ACCEPT_IE_T3323_VALUE_FLG) )
    {
        return VOS_TRUE;
    }

    Gmm_SaveTimerValue(GMM_TIMER_T3323,
                       pMsg->aucNasMsg[ucIeOffset + 2]);

    pAttachAcceptIe->ulOptionalIeMask
        |= GMM_ATTACH_ACCEPT_IE_T3323_VALUE_FLG;

    pAttachAcceptIe->aucIeOffset[NAS_GMM_ATTACH_ACCEPT_IE_T3323_VALUE] = ucIeOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  :NAS_GMM_DecodeT3312ExtendedValueIE_RcvAttachAccept
 ��������  :��attach accept��Ϣ�н���T3312 extended value IE����
 �������  :pRauAcceptIe - ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��
            pMsg         - ָ��NAS_MSG_STRU�ṹ��ָ��
            ucIeOffset   - T3312 extended value IE����Ϣ������λ��
 �������  :��
 �� �� ֵ  :VOS_TRUE  - ����ɹ�
            VOS_FALSE - ����ʧ��
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_DecodeT3312ExtendedValueIE_RcvAttachAccept(
    GMM_MSG_RESOLVE_STRU              *pAttachAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU           *pMsg,
    VOS_UINT8                          ucIeOffset
)
{
    if ((ucIeOffset + NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN) > (VOS_UINT8)pMsg->ulNasMsgSize )
    {
        return VOS_FALSE;
    }

    if (NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG == (pAttachAcceptIe->ulOptionalIeMask & NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG) )
    {
        return VOS_TRUE;
    }

    /* 24.008: 4.7.3.1.3�½���������:
    If the ATTACH ACCEPT message contains the T3312 extended value IE, then the
    MS shall use the value in T3312 extended value IE as periodic routing area
    update timer (T3312). If the ATTACH ACCEPT message does not contain T3312
    extended value IE, then the MS shall use the value in the Periodic RA update
    timer IE as periodic routing area update timer (T3312).*/
    if (PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
    {
        NAS_GMM_SaveGprsTimer3Value(GMM_TIMER_T3312,
                       pMsg->aucNasMsg[ucIeOffset + 2]);


        pAttachAcceptIe->ulOptionalIeMask
            |= NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG;

        pAttachAcceptIe->aucIeOffset[NAS_GMM_ATTACH_ACCEPT_IE_T3312_EXTENDED_VALUE] = ucIeOffset;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_Gmm_SaveAttachAcceptGmmCause
 ��������  : ����Attach accept�е�gmm cause
 �������  : GMM_MSG_RESOLVE_STRU  *pstAttachAcceptIe ָ��GMM_MSG_RESOLVE_STRU
             �ṹ��ָ��
 �������  : ��
 �� �� ֵ  : rau ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : g00322017
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_Gmm_SaveAttachAcceptGmmCause(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU               *pstAttachAcceptIe
)
{
    VOS_UINT32                          ulOptionalIeMask;
    VOS_UINT8                           ucGmmCause;

    ulOptionalIeMask = pstAttachAcceptIe->ulOptionalIeMask;
    if ( (GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG == (ulOptionalIeMask & GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG))
      && (pstAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_GMM_CAUSE] < 254))
    {
        ucGmmCause = pMsg->aucNasMsg[pstAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_GMM_CAUSE] + 1];
    }
    else
    {
        ucGmmCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    NAS_MML_SetOriginalRejectCause(ucGmmCause);
    return;
}
/*******************************************************************************
  Module   : Gmm_AttachAcceptResolveIe
  Function : ����ATTACH ACCEPT��IE
  Input    : GMM_MSG_RESOLVE_STRU  *pAttachAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                        �ṹ��ָ��
             NAS_MSG_STRU          *pMsg                ָ��NAS_MSG_STRU�ṹ
                                                        ��ָ��
  Output   : GMM_MSG_RESOLVE_STRU  *pAttachAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                        �ṹ��ָ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2012��3��20��
      ��    ��   : z00161729
      �޸�����   : ֧��ISR�����޸�
    3.��    ��   : 2012��3��27��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
    4.��    ��   : 2013��09��10��
      ��    ��   : l65478
      �޸�����   : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
    5.��    ��   : 2013��10��25��
      ��    ��   : w00167002
      �޸�����   : DTS2013102201891:���ӶԽ����������쳣�Ĵ���
                 1.���ս�������д���ܳ���ֵ�������ᳬ��������Ϣ�ĳ��ȣ�����Ϊ�쳣��
                 2.����ÿ���ӽ�������Ϣ�ĳ���ֵ�����������˽�������д���ܳ���ֵ������Ϊ�쳣��

                 ����NAS_MM_DecodeEMC������MML��NAS_MML_DecodeEmergencyNumList��
                 ��GMM/MM����������б�ʹ�á�
    6.��    ��   : 2015��6��8��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptResolveIe(
                               GMM_MSG_RESOLVE_STRU *pAttachAcceptIe,           /* ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��       */
                               NAS_MSG_FOR_PCLINT_STRU         *pMsg
                               )
{
    VOS_UINT8                           ucIeOffset = GMM_MSG_LEN_ATTACH_ACCEPT;  /* ������ʱ�����洢�洢IE��ƫ����           */
    VOS_UINT8                           ucEndFlg   = GMM_FALSE;                  /* ���ڻ�������־ΪFALSE                    */

    VOS_UINT16                          usIeOffsetAdapt;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    usIeOffsetAdapt         = 0;

    Gmm_SaveTimerValue(GMM_TIMER_T3312, pMsg->aucNasMsg[3]);                    /* �洢T3312ʱ��                            */

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (0 == ((pMsg->aucNasMsg[2]) & 0x08))
        {
            g_GmmGlobalCtrl.ucFopFlg = GMM_TRUE;
        }

        else
        {
            g_GmmGlobalCtrl.ucFopFlg = GMM_FALSE;
        }
    }

    for (; ((ucIeOffset<pMsg->ulNasMsgSize) && (GMM_FALSE == ucEndFlg));)
    {                                                                           /* �洢IE��ƫ����С�ڿտ���Ϣ�ĳ���         */
        switch (pMsg->aucNasMsg[ucIeOffset])
        {                                                                       /* IEI                                      */
        case GMM_IEI_P_TMSI_SIGNATURE:                                          /* P-TMSI signature                         */
            if ((ucIeOffset + 4) > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"P-TMSI\" length error in ATTACH ACCEPT");
                return;
            }
            if (GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE_FLG ) )
            {
                ucIeOffset += 4;
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE]
                = ucIeOffset;
            ucIeOffset += 4;
            break;
        case GMM_IEI_NEGOTIATED_READY_TIMER_VALUE:                              /* Negotiated READY timervalue              */
            if ((ucIeOffset + 2) > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"READY timer\" length error in ATTACH ACCEPT");
                return;
            }
            if (GMM_ATTACH_ACCEPT_IE_READY_TIMER_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_READY_TIMER_FLG ) )
            {
                ucIeOffset += 2;
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_READY_TIMER_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_READY_TIMER]
                = ucIeOffset;
            ucIeOffset += 2;
            break;
        case GMM_IEI_ALLOCATED_PTMSI:                                           /* Allocated P-TMSI                         */
            if ((ucIeOffset + 7) > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"P-TMSI\" length error in ATTACH ACCEPT");
                return;
            }
            if (GMM_ATTACH_ACCEPT_IE_PTMSI_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_PTMSI_FLG ) )
            {
                ucIeOffset += 7;
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_PTMSI_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_PTMSI]
                = ucIeOffset;
            ucIeOffset += 7;
            break;
        case GMM_IEI_MS_IDENTITY:                                               /* MS identity                              */
            if (GMM_MOBILE_ID_IMSI == (pMsg->aucNasMsg[ucIeOffset + 2] & 0x07))
            {                                                                   /* IE����IMSI                               */
                if ((ucIeOffset + 10) > (VOS_UINT8)pMsg->ulNasMsgSize )
                {
                    /* IMSI����ʱ,��ʹ���Ȳ���,Ҳ��Ҫ���� */
                    pAttachAcceptIe->ulOptionalIeMask
                        |= GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG;
                    pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_MS_IDENTITY]
                        = ucIeOffset;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"MS ID\" length error in ATTACH ACCEPT");
                    return;
                }
                if (GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG ==
                    (pAttachAcceptIe->ulOptionalIeMask
                     & GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG ) )
                {
                    ucIeOffset += 10;
                    break;
                }
            }
            else if (GMM_MOBILE_ID_TMSI_PTMSI == (pMsg->aucNasMsg[ucIeOffset + 2] & 0x07))
            {                                                                   /* IE����TMSI                               */
                if ((ucIeOffset + 7) > (VOS_UINT8)pMsg->ulNasMsgSize )
                {
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"MS ID\" length error in ATTACH ACCEPT");
                    return;
                }
                if (GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG ==
                    (pAttachAcceptIe->ulOptionalIeMask
                     & GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG ) )
                {
                    ucIeOffset += 7;
                    break;
                }
            }
            else
            {
                ucIeOffset += pMsg->aucNasMsg[ucIeOffset + 1] + 2 ;
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_MS_IDENTITY]
                = ucIeOffset;

            ucIeOffset += pMsg->aucNasMsg[ucIeOffset + 1] + 2 ;
            break;
        case GMM_IEI_GMM_CAUSE:                                                 /* GMM cause                                */
            if ( (ucIeOffset + 2) > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"GMM cause\" length error in ATTACH ACCEPTT");
                return;
            }
            if (GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG ) )
            {
                ucIeOffset += 2;
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_GMM_CAUSE]
                = ucIeOffset;
            ucIeOffset += 2;
            break;
        case GMM_IEI_T3302_VALUE:                                               /* T3302 value                              */
            if ( (ucIeOffset + 3) > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"T3302\" length error in ATTACH ACCEPT");
                return;
            }
            if (GMM_ATTACH_ACCEPT_IE_T3302_VALUE_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_T3302_VALUE_FLG ) )
            {
                ucIeOffset += 3;
                break;
            }

            Gmm_SaveTimerValue(GMM_TIMER_T3302,
                               pMsg->aucNasMsg[ucIeOffset + 2]);                /* �洢T3302ʱ��                            */

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(),sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_T3302_VALUE_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_T3302_VALUE]
                = ucIeOffset;
            ucIeOffset += 3;
            break;
        case GMM_IEI_CELL_NOTIFICATION:                                         /* Cell Notification                        */
            if (GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION_FLG ) )
            {
                ucIeOffset += 1;
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION]
                = ucIeOffset;
            ucIeOffset += 1;
            break;
        case GMM_IEI_EQUIVALENT_PLMNS:                                          /* Equivalent PLMNs                         */
            if ( (ucIeOffset + (2 + pMsg->aucNasMsg[ucIeOffset + 1]))
                 > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"Equivalent PLMNs\" length error in ATTACH ACCEPT");
                return;
            }
            if (GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG ==
                (pAttachAcceptIe->ulOptionalIeMask
                 & GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG ) )
            {
                ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
                break;
            }

            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG;
            pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN]
                = ucIeOffset;
            ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            break;
        case GMM_IEI_EMERGENCY_NUMBER_LIST:                                     /* Emergency Number List                    */
            if ( (ucIeOffset + (2 + pMsg->aucNasMsg[ucIeOffset + 1]))
                 > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAcceptResolveIe:WARNING: IE\"emergency number\" length error in ATTACH ACCEPT");
                return;
            }
            pAttachAcceptIe->ulOptionalIeMask
                |= GMM_ATTACH_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG;

            usIeOffsetAdapt = ucIeOffset;
            (VOS_VOID)NAS_MML_DecodeEmergencyNumList(&usIeOffsetAdapt, pMsg->aucNasMsg, (VOS_UINT16)pMsg->ulNasMsgSize);
            ucIeOffset      = (VOS_UINT8)usIeOffsetAdapt;

            break;

        case NAS_GMM_IEI_T3323_VALUE:
            if (VOS_FALSE == NAS_GMM_DecodeT3323ValueIERcvAttachAccept(pAttachAcceptIe, pMsg, ucIeOffset))
            {
                return;
            }

            ucIeOffset += NAS_GMM_IE_T3323_VALUE_LEN;
            break;

        case NAS_GMM_IEI_T3312_EXTENDED_VALUE:
            if (VOS_FALSE == NAS_GMM_DecodeT3312ExtendedValueIE_RcvAttachAccept(pAttachAcceptIe, pMsg, ucIeOffset))
            {
                return;
            }

            ucIeOffset += NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN;
            break;


        default:
            if(GMM_IEI_NETWORK_FEATURE_SUPPORT == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            { /* Network feature support                  */
                ucIeOffset += 1;
            }
            else if (GMM_IEI_REQUESTED_MS_INFORMATION == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            {/* Requested MS information                 */
                pAttachAcceptIe->ulOptionalIeMask
                    |= GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG;
                pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION]
                    = ucIeOffset;
                ucIeOffset += 1;
            }
            /* TV���͵�IE, reference 27.007 11.2.4 */
            else if(GMM_IEI_FORMAT_T_TYPE == (pMsg->aucNasMsg[ucIeOffset] & GMM_IEI_FORMAT_TYPE_INFO))
            {
                ucIeOffset += 1;
            }
            /* TLV���͵�IE */
            /*lint -e961*/
            else if (ucIeOffset + 2 + pMsg->aucNasMsg[ucIeOffset + 1] < pMsg->ulNasMsgSize)
            /*lint +e961*/
            {
                ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            }
            else
            {
                ucEndFlg = GMM_TRUE;
            }
            break;
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptGprsOnly
  Function : ATTACH ACCEPT�Ľ����GPRS only attached�Ĵ���
  Input    : GMM_MSG_RESOLVE_STRU *pAttachAcceptIe  ָ��GMM_MSG_RESOLVE_STRU
                                                    �ṹ��ָ��
             NAS_MSG_STRU         *pMsg             ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2007��11��12��
    ��    ��   : luowei id:39007
    �޸�����   : A32D13044
  3.��    ��   : 2008��11��25��
    ��    ��   : l65478
    �޸�����   : �������ⵥ�ţ�AT2D06903��GSMģʽ�£������յ�����ATTACH accept��Ϣ��
                 GMM����attach complete
  4.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2012��03��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����
  7.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  7.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
  8.��    ��   : 2014��8��5��
    ��    ��   : b00269685
    �޸�����   : DTS2014072107208�޸�
  9.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 *******************************************************************************/
VOS_VOID Gmm_AttachAcceptGprsOnly(
    GMM_MSG_RESOLVE_STRU                *pAttachAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_BOOL                            bTlliUpdateFlg,
    VOS_UINT8                           ucInterRatInfoFlg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGmmCause;                                                    /* ������ʱ�����洢GMM CAUSE                */

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
    VOS_UINT8                           ucDrxLength;
    VOS_UINT8                           ucSysInfoDrxLength;
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    enGmmCause = NAS_MML_REG_FAIL_CAUSE_NULL;

    if (GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG
        == (pAttachAcceptIe->ulOptionalIeMask
        & GMM_ATTACH_ACCEPT_IE_GMM_CAUSE_FLG))
    {
        enGmmCause = pMsg->aucNasMsg
            [pAttachAcceptIe->aucIeOffset[GMM_ATTACH_ACCEPT_IE_GMM_CAUSE] + 1]; /* �õ�GMM CAUSE                            */
    }

    /* R11����:   24008 4.7.3.2.3.2    Other GMM causevalues and the case that no GMM cause IE
       was received are considered as abnormal cases. The combined attach procedure shall be
       considered as failed for non-GPRS services */
    if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                       /* ��ǰ��specific������COMBINED ATTACH      */
        if ((NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE         != enGmmCause)
         && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE         != enGmmCause)
         && (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION    != enGmmCause)
         && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR     != enGmmCause))
        {                                                                  /* ����ԭ��ֵ                               */

            enGmmCause = NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE;
        }
    }

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc)
        || ((VOS_FALSE == bTlliUpdateFlg) && (GMM_NULL_PROCEDURE == g_GmmGlobalCtrl.ucSpecProc)))
    {                                                                           /* ��ǰ��specific������NORMAL ATTACH        */
        if ((GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg) && (GMM_FALSE == ucInterRatInfoFlg))
        {
            /* ���Attach Accept��Ϣ�д���Request Ms Info IE,��GMM��Ҫ��WRR������Ϣ������
               InterRatHandover��Ϣ���ȴ�WRR�ظ���������ظ�Attach Complete��Ϣ������Attach
               ���̲���������ڴ�֮ǰ������SM�ظ�Est_Cnf��Ϣ�������̽�������֪ͨSM. */

            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
        }

        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* ����״̬��������                         */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* attach attempt counter��0                */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* routing area updating attempt counter��0 */

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);


        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA
                        );

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    }
    else
    {                                                                           /* combined����                             */
        if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == enGmmCause)
        {                                                                       /* ԭ��ֵΪ2                                */
            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                   /* ATTACH��������SM������                   */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);  /* ֪ͨSM GMMע��ʧ��                       */

                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                         /* ��ucSmCnfFlg��־                         */
            }

            /* 24008_CR1253R1_(Rel-8)_C1-090834 24008 4.7.3.2.3.2�½���������:
            #2:The MS shall stop timer T3310 if still running and shall reset the
            routing area updating attempt counter. The MS shall set the update
            status to U3 ROAMING NOT ALLOWED and shall delete any TMSI, LAI and
            ciphering key sequence number. The MS shall enter state GMM-REGISTERED.NORMAL-SERVICE.
            The new MM state is MM IDLE*/
            Gmm_TimerStop(GMM_TIMER_T3310);
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

            NAS_GMM_SndMmCombinedAttachAccept(GMMMM_ATTACH_RESLUT_PS_ONLY,
                                              enGmmCause,
                                              pMsg,
                                              pAttachAcceptIe);                    /* ����MMCGMM_COMBINED_ATTACH_ACCEPTED��MMC */

            /* ��MMC����PSע���� */


            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         enGmmCause);


            /* �¼��ϱ� */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_ATTACH_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);

            /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
            if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                     & GMM_WAIT_PS_ATTACH))
            {
                NAS_GMM_SndMmcAttachCnf();
            }
            g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
        }
        else
        {                                                                       /* ԭ��ֵΪ16,17,22                         */
            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                   /* ATTACH��������SM������                   */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS); /* ֪ͨSM GMMע��ʧ��                       */

                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                         /* ��ucSmCnfFlg��־                         */
            }

            Gmm_AttachRauAcceptCause16(enGmmCause);                                       /* ����ԭ��ֵ16��17��22������             */

            if((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                ||(5 > g_GmmRauCtrl.ucRauAttmptCnt))
            {
                NAS_GMM_SndMmCombinedAttachAccept(GMMMM_ATTACH_RESLUT_PS_ONLY,
                                                  enGmmCause,
                                                  pMsg,
                                                  pAttachAcceptIe);             /* ����MMCGMM_COMBINED_ATTACH_ACCEPTED��MMC */


                /* ��MMC����PSע���� */

                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             enGmmCause);

                /* ����ATTACH������ */
                if(5 <= g_GmmAttachCtrl.ucAttachAttmptCnt)
                {
                    g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
                }

                /* �¼��ϱ� */
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_ATTACH_SUCC,
                                VOS_NULL_PTR,
                                NAS_OM_EVENT_NO_PARA);

                /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
                if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                         & GMM_WAIT_PS_ATTACH))
                {
                    NAS_GMM_SndMmcAttachCnf();
                }
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
            }
        }
    }

    /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */
    ucDrxLength        = NAS_MML_GetUeUtranPsDrxLen();
    ucSysInfoDrxLength = NAS_MML_GetWSysInfoDrxLen();
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DRX);                          /* ֪ͨGAS DRX������� */
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
         &&  (ucSysInfoDrxLength != ucDrxLength) )
    {                                                                           /* DRX length�������                       */
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DRX);                          /* ֪ͨRRC DRX�������                      */
    }
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */
    else
    {
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptCombined
  Function : ATTACH ACCEPT�Ľ����combined attached�Ĵ���
  Input    : GMM_MSG_RESOLVE_STRU  *pAttachAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                        �ṹ��ָ��
             NAS_MSG_STRU          *pMsg                ָ��NAS_MSG_STRU�ṹ
                                                        ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����  : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����  : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptCombined(
                              GMM_MSG_RESOLVE_STRU  *pAttachAcceptIe,           /* ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��       */
                              NAS_MSG_FOR_PCLINT_STRU          *pMsg
                              )
{
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */
    VOS_UINT8                           ucDrxLength;
    VOS_UINT8                           ucSysInfoDrxLength;

    ucDrxLength                       = NAS_MML_GetUeUtranPsDrxLen();
    ucSysInfoDrxLength                = NAS_MML_GetWSysInfoDrxLen();
	g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                      /* attach attempt counter��0                */
    g_GmmRauCtrl.ucRauAttmptCnt       = 0;                                      /* routing area updating attempt counter��0 */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DRX);                          /* ֪ͨGAS DRX������� */
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
          && (ucSysInfoDrxLength != ucDrxLength))
    {                                                                           /* DRX length�������                       */
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DRX);                          /* ֪ͨRRC DRX�������                      */
    }
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */
    else
    {
    }
    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* ����״̬��������                         */

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                 NAS_MML_REG_FAIL_CAUSE_NULL);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_SUCC,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA
                    );

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ��specific������NORMAL ATTACH        */
        NAS_GMM_SndMmGmmActionResultInd(
                      GMMMM_ACTION_SUCCESS,
                      NAS_MML_REG_FAIL_CAUSE_NULL);  /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {                                                                           /* combined����                             */
        NAS_GMM_SndMmCombinedAttachAccept(GMMMM_ATTACH_RESLUT_COMBINED,
                                          NAS_MML_REG_FAIL_CAUSE_NULL,
                                          pMsg,
                                          pAttachAcceptIe);                        /* ����MMCGMM_COMBINED_ATTACH_ACCEPTED��MMC */

        /* ����ATTACH������ */
        if(5 <= g_GmmAttachCtrl.ucAttachAttmptCnt)
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptHandle_Emergency_Num_Handling
  Function : Gmm_AttachAcceptHandle���������Ӷ�: ���������봦��
  Input    :
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.15  �¹�����
    2.��    ��   : 2012��3��20��
      ��    ��   : z00161729
      �޸�����   : ����������ȫ�ֱ����滻
    3.��    ��   : 2012��3��27��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
    4.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptHandle_Emergency_Num_Handling(
                                   GMM_MSG_RESOLVE_STRU        AttachAcceptIe
                            )
{
    VOS_UINT8           i,j;

    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList;

    NAS_MML_PLMN_ID_STRU               stMmcPlmnId;

    PS_MEM_SET(&stMmcPlmnId, 0, sizeof(stMmcPlmnId));

    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    if (GMM_ATTACH_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG
        == (AttachAcceptIe.ulOptionalIeMask
                & GMM_ATTACH_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG))
    {                                                                           /* ��Ϣ�а����������б�                     */
        pstEmergencyNumList->ulMcc =
            g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[0]
            | (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[1] << 8)
            | (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[2] << 16);

        Gmm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }
    else if (0 != pstEmergencyNumList->ucEmergencyNumber)
    {
        /* ��Ϣ�а������������б�֮ǰ�洢�˽������б�,�������ͬһ�����ҵ�mcc��ɾ��֮ǰ�洢�Ľ��������б�
        24008_CR2107R1_(Rel-11)_C1-121605 24008 4.4.4.6��4.7.3.1.3��4.7.5.1.3��������:
        The emergency number(s) received in the Emergency Number List IE are valid only
        in networks with in.the same MCCcountry as in  the cell on which this IE
        is received.*/
        NAS_GMM_ConvertPlmnIdToMmcFormat(&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId, &stMmcPlmnId);

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstEmergencyNumList->ulMcc, stMmcPlmnId.ulMcc))
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
        Gmm_SndCcEmergencyNumberList(pstEmergencyNumList);
    }
    else
    {
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptHandle_PTMSI_Handling
  Function : Gmm_AttachAcceptHandle���������Ӷ�: PTMSI/PTMSI SIGNATURE����
  Input    :
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ŷ���� 2009.06.15  �¹�����
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ,PTMSI�����ı�ʱ�ϱ���OM
  4.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptHandle_PTMSI_Handling(
                                   NAS_MSG_FOR_PCLINT_STRU    *pMsg,
                                   GMM_MSG_RESOLVE_STRU        AttachAcceptIe,
                                   VOS_UINT8                  *pucSndCompleteFlg
                            )
{
    if (GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE_FLG
        == (AttachAcceptIe.ulOptionalIeMask
            & GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE_FLG))
    {                                                                           /* �տ���Ϣ����P-TMSI signature             */
        /* �洢P-TMSI signature         */
        NAS_MML_SetUeIdPtmsiSignature(&(pMsg->aucNasMsg[AttachAcceptIe.aucIeOffset[GMM_ATTACH_ACCEPT_IE_PTMSI_SIGNATURE] + 1]));
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* ����UE ID���ڱ�־                        */
    }
    else
    {                                                                           /* �տ���Ϣ��û��P-TMSI signature           */
        /* ɾ��P-TMSI signature         */
        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ��UE ID���ڱ�־                          */
    }
    if (GMM_ATTACH_ACCEPT_IE_PTMSI_FLG
        == (AttachAcceptIe.ulOptionalIeMask & GMM_ATTACH_ACCEPT_IE_PTMSI_FLG))
    {                                                                           /* �տ���Ϣ����P-TMSI                       */
        /* �洢P-TMSI                   */
        NAS_MML_SetUeIdPtmsi(&(pMsg->aucNasMsg[AttachAcceptIe.aucIeOffset[GMM_ATTACH_ACCEPT_IE_PTMSI] + 3]));

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;              /* ����UE ID���ڱ�־                        */
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                    /* ֪ͨRRC NAS����Ϣ�仯                    */
        *pucSndCompleteFlg = GMM_TRUE;                                            /* �趨��Ҫ����RAU COMPLETE��Ϣ             */

#if (FEATURE_ON == FEATURE_PTM)
        /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
        NAS_GMM_SndAcpuOmChangePtmsi();
#endif
    }
    else
    {
        /* 2G������ATTACH��ɺ������GAS֪ͨPTMSIֵ */
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptHandle_REQUESTED_MS_INFORMATION_IE_Handling
  Function : Gmm_AttachAcceptHandle���������Ӷ�: REQUESTED_MS_INFORMATION IE����
  Input    :
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.15  �¹�����
    2. ��    ��   : 2012��05��13��
       ��    ��   : W00166186
       �޸�����   : DTS201204261955,RAU COMPLETEû�лظ�
    3. ��    ��   : 2012��12��26��
       ��    ��   : s46746
       �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�������
    4.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*******************************************************************************/
VOS_VOID Gmm_AttachAcceptHandle_REQUESTED_MS_INFORMATION_IE_Handling(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU                AttachAcceptIe,
    VOS_UINT8                          *pucSndCompleteFlg,
    VOS_UINT8                          *pucInterRatInfoFlg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList;

#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulSurpportLteFlag;
#endif

    pstRatList = NAS_MML_GetMsPrioRatList();

#if   (FEATURE_ON == FEATURE_LTE)
    ulSurpportLteFlag = NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ˫ģ�²ſɻ�ø���Ϣ */

    if ( (( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_WCDMA))
#if   (FEATURE_ON == FEATURE_LTE)
      && (VOS_FALSE == ulSurpportLteFlag)
#endif
      )
      || ( 1 == pstRatList->ucRatNum ))
    {
        return;
    }



    if (GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG
        == (AttachAcceptIe.ulOptionalIeMask
            & GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG))
    {                                                                           /* ��Ϣ�а��� IE:Requested MS information   */
        g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg = VOS_FALSE;

        /* ƽ̨֧��UTRAN */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
        {
            if (0x08 == (0x08 & (pMsg->aucNasMsg
                    [AttachAcceptIe.aucIeOffset[GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION]])))
            {                                                                   /* ��Ϣ��ָʾ Inter RAT information container IE requested */
                *pucSndCompleteFlg = GMM_TRUE;                                        /* �趨��Ҫ����RAU COMPLETE��Ϣ             */
                *pucInterRatInfoFlg = GMM_TRUE;
            }
        }

#if   (FEATURE_ON == FEATURE_LTE)
        /* ƽ̨֧��LTE */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
        {
            if (0x04 == (0x04 & (pMsg->aucNasMsg
                                            [AttachAcceptIe.aucIeOffset[GMM_ATTACH_ACCEPT_IE_REQUESTED_MS_INFORMATION]])))
            {
                *pucSndCompleteFlg = GMM_TRUE;                                        /* �趨��Ҫ����RAU COMPLETE��Ϣ             */
                g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag = VOS_TRUE;
            }
        }
#endif
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptHandle_Attach_Result_IE_Handling
  Function : Gmm_AttachAcceptHandle���������Ӷ�: Attach_Result IE����
  Input    :
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.15  �¹�����
 2.��    ��   : 2012��8��13��
   ��    ��   : L65478
   �޸�����   : DTS2012080301606:ע��ʧ�ܺ����ֶ�����ʧ��
 3.��    ��  : 2012��08��24��
   ��    ��  : m00217266
   �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
 4.��    ��  : 2014��08��4��
   ��    ��  : b00269685
   �޸�����  : ����ע��ʱ�յ�ps only accept������csʧ�ܣ�ps�ɹ�����
 5.��    ��   : 2015��6��5��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_UINT8 Gmm_AttachAcceptHandle_Attach_Result_IE_Handling(
                                   NAS_MSG_FOR_PCLINT_STRU    *pMsg,
                                   GMM_MSG_RESOLVE_STRU        AttachAcceptIe,
                                   VOS_UINT8                   ucUpdateStaPre,
                                   VOS_UINT8                  *pucSndCompleteFlg,
                                   VOS_BOOL                    bTlliUpdateFlg,
                                   VOS_UINT8                   ucInterRatInfoFlg
                            )
{

    if (GMM_COMBINED_GPRS_IMSI_ATTACHED == (pMsg->aucNasMsg[2] & 0x03))
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg) && (GMM_FALSE == ucInterRatInfoFlg))
        {
            /* ���Attach Accept��Ϣ�д���Request Ms Info IE,��GMM��Ҫ��WRR������Ϣ������
               InterRatHandover��Ϣ���ȴ�WRR�ظ���������ظ�Attach Complete��Ϣ������Attach
               ���̲���������ڴ�֮ǰ������SM�ظ�Est_Cnf��Ϣ�������̽�������֪ͨSM. */

            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
        }
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_TRUE;
        Gmm_AttachAcceptCombined(&AttachAcceptIe, pMsg);                        /* ���ú�������combined attached            */

        if (GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG
            == (AttachAcceptIe.ulOptionalIeMask
            & GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG))
        {                                                                       /* ��IE����                                 */
            if (GMM_MOBILE_ID_TMSI_PTMSI
                == (GMM_MOBILE_ID_TMSI_PTMSI &
                pMsg->aucNasMsg[AttachAcceptIe.aucIeOffset
                [GMM_ATTACH_ACCEPT_IE_MS_IDENTITY] + 2]))
            {                                                                   /* IE_MS_IDENTITY��Я��TMSI                 */
                *pucSndCompleteFlg = GMM_TRUE;                                    /* �趨��Ҫ����RAU COMPLETE��Ϣ             */
            }
        }
    }
    else
    {                                                                           /* Attach�����GPRS attached only           */
        Gmm_AttachAcceptGprsOnly(&AttachAcceptIe, pMsg, bTlliUpdateFlg, ucInterRatInfoFlg);        /* ���ú�������GPRS only attached           */
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

    }

    return GMM_TRUE;
}

/*******************************************************************************
 �� �� ��  : Gmm_AttachAcceptHandle_ucSndCompleteFlg_Handling
 ��������  : ucSndCompleteFlg ����
 �������  : VOS_UINT8                     ucSndCompleteFlg
             VOS_UINT8                     ucInterRatInfoFlg
             VOS_UINT8                     ucReadychangFLG
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��12��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��3��29��
    ��    ��   : o00132663
    �޸�����   : NAS R7Э��������InterRatHandoverInfo��Ϣ�ӿڱ��
  3.��    ��   : 2010��4��12��
    ��    ��   : l65478
    �޸�����   : AT2D18389,�ڳ�ʼС������ʱ��GMMӦ��֪ͨLLC����NULL֡
  4.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  5.��    ��   : 2014��6��13��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptHandle_ucSndCompleteFlg_Handling(
    VOS_UINT8                     ucSndCompleteFlg,
    VOS_UINT8                     ucInterRatInfoFlg,
    VOS_UINT8                     ucReadychangFLG
                            )
{
    NAS_MSG_STRU    *pSendNasMsg = VOS_NULL_PTR;
    VOS_UINT32      ulRst;

    if (VOS_TRUE == ucSndCompleteFlg)
    {
        /* ��Ҫ��WRR��ȡInterRatInfo��Ϣ */
        if (VOS_TRUE == ucInterRatInfoFlg)
        {
            ulRst = NAS_GMM_SndRrmmInterRatHandoverInfoReq();

            if (VOS_OK == ulRst)
            {
                g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg = VOS_TRUE;
                g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg       = VOS_FALSE;
                g_GmmInterRatInfoCtrl.ucDataLen                     = 0;
            }
            else
            {
                ucInterRatInfoFlg = VOS_FALSE;
            }
        }

        /* ����Ҫ��WRR��ȡInterRatInfo��Ϣ, ���߻�ȡ��Ϣʧ��ʱ��ֱ�ӻظ�����
           Attach Complete��Ϣ */
        if (VOS_FALSE == ucInterRatInfoFlg)
        {
            g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg = VOS_FALSE;

            pSendNasMsg = Gmm_AttachCompleteMsgMake();
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

        }

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            /* attach������ֻ����READY TIMER����֪ͨLLC cell update */
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = VOS_FALSE;

            if ( VOS_TRUE == ucReadychangFLG )
            {
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_READY_TIMER);
            }

            GMM_InitCellUpdate(ucReadychangFLG);       /* CELL update */
        }
    }
    else
    {
        if ( GMM_TRUE == GMM_IsCasGsmMode() )
        {
            if ( VOS_TRUE == ucReadychangFLG )
            {

                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_READY_TIMER);

                gstGmmCasGlobalCtrl.ucCellUpdateFlg = VOS_TRUE;

                /* ����24.008 4.7.2.1.1 If a new READY timer value is negotiated,
                the MS shall upon the reception of the ATTACH ACCEPT or ROUTING
                AREA UPDATE ACCEPT message perform a initial cell update
                (either by transmitting a LLC frame or, if required, a ATTACH
                COMPLETE or ROUTING AREA UPDATE COMPLETE message), in order to
                apply the new READY timer value immediately. If both the network
                and the MS supports the Cell Notification, the initial cell
                update shall useany LLC frame except the LLC NULL frame. */
                GMM_InitCellUpdate(ucReadychangFLG);
            }
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptHandle_TLLI_Handling
  Function : Gmm_AttachAcceptHandle���������Ӷ�: TLLI ����
  Input    :
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ŷ���� 2009.06.15  �¹�����
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptHandle_TLLI_Handling(
                                   VOS_BOOL                bTlliUpdateFlg
                            )
{
    VOS_UINT32                  ulNewTlli = 0;

    if ((GMM_TRUE==GMM_IsCasGsmMode())
      &&(GMM_UEID_P_TMSI==(g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
         & GMM_UEID_P_TMSI))
       )
    {
        if (VOS_TRUE == bTlliUpdateFlg )
        {
            GMM_CharToUlong(&ulNewTlli,
                            NAS_MML_GetUeIdPtmsi());                            /* �µ�PTMSI */
            GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);                      /* ������TLLI */
            if ( GMM_FALSE == GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI) )
            {
                GMM_LOG_WARN("Gmm_AttachAcceptHandle():Error: new TLLI assigned unsuccessfully!");
            }
            else
            {
                Gmm_TimerStart(GMM_TIMER_PROTECT_OLD_TLLI);
            }
        }
        else
        {
            Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
            Gmm_TimerStart(GMM_TIMER_PROTECT_OLD_TLLI);
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_AttachAcceptHandle
  Function : ����ATTACH ACCEPT��Ϣ
  Input    : NAS_MSG_STRU *pMsg     ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. x51137 2006/4/28 A32D02889
    3. ��    ��   : 2006��11��8��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D06867
    4. ��    ��   : 2008��10��20��
       ��    ��   : o00132663
       �޸�����   : ���ⵥ��:AT2D06266, ���ӶԲ�֧��CELL NOTIFICATION�Ĵ���
    5. ��    ��   : 2008��11��25��
       ��    ��   : l65478
       �޸�����   : �������ⵥ�ţ�AT2D06903��GSMģʽ�£������յ�����ATTACH accept��Ϣ��GMM����attach complete
    6.��    ��   : 2011��10��08��
      ��    ��   : W00167002
      �޸�����  : V7R1 PhaseII�׶ε���������Eplmn�Ĺ�����ԭ�ȵ�MMCģ�����Ϊ
                   GMM/MMģ�鴦��
    7.��    ��   : 2012��1��08��
      ��    ��   : z00161729
      �޸�����   : V7R1 PhaseIV�׶ε���,TIN typeֱ�Ӹ���MMLȫ�ֱ�����дnv��ͨ����Ϣ֪ͨMMC��MMC����
    8.��    ��   : 2013��12��24��
      ��    ��   : f00261443
      �޸�����   : ��¼GU��IMS Voice������
    9.��    ��   : 2014��6��13��
      ��    ��   : w00242748
      �޸�����   : DSDS ������
   10.��    ��   : 2014��7��18��
      ��    ��   : b00269685
      �޸�����   : DSDS IV�޸�
   11.��    ��   : 2014��9��30��
      ��    ��   : z00161729
      �޸�����   : DTS2014073003377: attach�ɹ��������·�����ptmsi��ͨ��nas comm info֪ͨ������ptmsi���ϵģ����º���ps service����#10�ܾ�
   12.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_AttachAcceptHandle(
                            NAS_MSG_FOR_PCLINT_STRU *pMsg,
                            VOS_BOOL                bTlliUpdateFlg
                            )
{
    VOS_UINT8                           ucUpdateStaPre  = 0;                                                /* ������ʱ�����洢ԭ����״̬               */
    GMM_MSG_RESOLVE_STRU                AttachAcceptIe;                                 /* ������ʱ����                             */
    VOS_UINT8                           ucSndCompleteFlg = GMM_FALSE;                   /* �Ƿ���RAU COMPLETE��Ϣ                 */
    VOS_UINT8                           ucReadychangFLG = GMM_FALSE;
    VOS_UINT8                           ucInterRatInfoFlg = GMM_FALSE;
    VOS_UINT8                           ucRst;

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
#endif

    Gmm_MemSet(&AttachAcceptIe, 0, sizeof(GMM_MSG_RESOLVE_STRU));               /* ��ʱ�������㴦��                         */
    ucUpdateStaPre = NAS_MML_GetPsUpdateStatus();
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_UPDATED);             /* �ø���״̬ΪGU1                          */
    Gmm_AttachAcceptResolveIe(&AttachAcceptIe, pMsg);                           /* ���ú�������ATTACH ACCEPT��Ϣ��IE        */
    NAS_Gmm_SaveAttachAcceptGmmCause(pMsg, &AttachAcceptIe);
#if   (FEATURE_ON == FEATURE_LTE)
     pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

     if ( NAS_MML_TIN_TYPE_PTMSI != pstRplmnCfgInfo->enTinType)
     {
         NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
     }
#endif


    Gmm_AttachAcceptHandle_REQUESTED_MS_INFORMATION_IE_Handling(pMsg,
                                                                AttachAcceptIe,
                                                               &ucSndCompleteFlg,
                                                               &ucInterRatInfoFlg);

    Gmm_AttachAcceptHandle_Emergency_Num_Handling(AttachAcceptIe);


    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, begin */
    /* report network feature information in UMTS. According to VoLTE SRS document,
     * In utran network, the related capability information reported is not supported
     * now.
     */
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2014-01-13, begin */
    NAS_GMM_SndMmcNetworkCapabilityInfoInd(GMM_MMC_NW_EMC_BS_NOT_SUPPORTED,
                                           NAS_MML_NW_IMS_VOICE_NOT_SUPPORTED,
                                           GMM_MMC_LTE_CS_CAPBILITY_NOT_SUPPORTED);
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2014-01-13, end */
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-24, end */


    ucRst = Gmm_AttachAcceptHandle_Attach_Result_IE_Handling(pMsg,
                                                             AttachAcceptIe,
                                                             ucUpdateStaPre,
                                                             &ucSndCompleteFlg,
                                                             bTlliUpdateFlg,
                                                             ucInterRatInfoFlg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    Gmm_AttachAcceptHandle_PTMSI_Handling(pMsg,
                                          AttachAcceptIe,
                                         &ucSndCompleteFlg);

    NAS_GMM_AttachAcceptHandle_UpdateEPlmn(&AttachAcceptIe, pMsg);

    /* 2Gģʽ�����µ�local TLLIֵ */
    Gmm_AttachAcceptHandle_TLLI_Handling(bTlliUpdateFlg);

    if (GMM_ATTACH_ACCEPT_IE_READY_TIMER_FLG
        == (AttachAcceptIe.ulOptionalIeMask & GMM_ATTACH_ACCEPT_IE_READY_TIMER_FLG))
    {
        ucReadychangFLG = GMM_TRUE;
        GMM_SaveReadyTimerValue(
            pMsg->aucNasMsg[AttachAcceptIe.aucIeOffset\
                [GMM_ATTACH_ACCEPT_IE_READY_TIMER] + 1]);                       /* ����READY TIMERЭ��ֵ */
    }
    else
    {
        if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg )
        {
            ucReadychangFLG = GMM_TRUE;
            GMM_SaveReadyTimerValue( GMM_REQUESTED_READY_TIMER_VALUE );
            gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg = GMM_FALSE;
        }
    }

    if (GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION_FLG
        == (AttachAcceptIe.ulOptionalIeMask
            & GMM_ATTACH_ACCEPT_IE_CELL_NOTIFICATION_FLG))
    {
        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_TRUE;     /* cell notificaion��Ч��־ */
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_FALSE;     /* cell notificaion��Ч��־ */
    }


    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);      /* ����AGENT_USIM_UPDATE_FILE_REQ��AGENT    */
    }

    Gmm_AttachAcceptHandle_ucSndCompleteFlg_Handling(ucSndCompleteFlg,
                                                     ucInterRatInfoFlg,
                                                     ucReadychangFLG);


    if (GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* CSͨ���е�NORMAL ATTACH                  */
        if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {                                                                       /* CS����ͨ����                             */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific ���̱�־          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachAcceptHandle:INFO: specific procedure ended");
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* ����RAU����                              */
        }
        else
        {                                                                       /* CSͨ����                                 */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific ���̱�־          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachAcceptHandle:INFO: specific procedure ended");
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_ATTACH_NORMAL;            /* �洢CSͨ���н���specific���̱�־         */
        }
    }
    else
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ���е�specific ���̱�־          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachAcceptHandle:INFO: specific procedure ended");
    }


    return;
}
/*******************************************************************************
  Module   : Gmm_SndAttachReq
  Function : ����ATTACH REQUEST
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2010��09��14��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:DTS2010091402018, CS onlyʱ��G->W->G��PDP����ʧ��
  3.��    ��   : 2010��11��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010112400547/DTs010112303273,û��ָ���µ�TLLI,����PS��ע��ʧ��
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��23��
    ��    ��   : w00176964
    �޸�����   : DTS2012022107470:WG֮��������ҵ�������л�ʱ,��G�е�W����RAU��
                 ����#9,NAS��������RAU���������ж�
  6.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  7.��    ��   : 2012��2��23��
    ��    ��   : w00176964
    �޸�����   : DTS2012061907255:UE��G��С��פ��,��ѡ��LA��ֹ��WС��,���Ʒ���פ��
                 �����ص�GС��,pdp�����,PING��������ͨ
  8.��    ��   : 2012��10��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012101907218:NAS�����㷢��Attach����ʱ��Establishment cause����Э��дΪRegistration
  9.��    ��   : 2012��9��1��
    ��    ��   : s46746
    �޸�����   : DTS2012082907374:UE��G��С��פ��,����GCF��������44.2.1.2.8ʱ,
                 ����Ҫÿ��Attach��ȥָ�ɲ�2
 10.��    ��   : 2013��1��4��
    ��    ��   : w00176964
    �޸�����   : DTS2013010400031:ȫ�ֱ���g_ucGcfInd�滻ΪUSIM�ṩAPI����USIMM_IsTestCard
 11.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 12.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : svlte��usim�ӿڵ���
 13.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_SndAttachReq(VOS_VOID)
{
    NAS_MSG_STRU    *pSendNasMsg = VOS_NULL_PTR;                                /* ����NAS_MSG_STRU���͵�ָ�����           */
    VOS_UINT8        ucAttachType;

    GMM_CasFsmStateChangeTo(GMM_REGISTERED_INITIATED);

    /*24008_CR1906R2_(Rel-11)_C1-113744 Stopping of timer T3311 and T3302 24008
    4.7.3.1.1�½���������:
    In state GMM-DEREGISTERED, the MS initiates the GPRS attach procedure by sending an
    ATTACH REQUEST message to the network, starts timer T3310 and enters state GMM-REGISTERED-INITIATED.
    If timer T3302 is currently running, the MS shall stop timer T3302. If timer T3311 is currently running,
    the MS shall stop timer T3311.
    4.7.3.2.1�½���������:
    If the MS is in GMM state GMM-DEREGISTERED and in MM state MM IDLE, the MS initiates the
    combined GPRS attach procedure by sending an ATTACH REQUEST message to the network, starts timer T3310
    and enters state GMM-REGISTERED-INITIATED and MM LOCATION UPDATING PENDING.
    If timer T3302 is currently running, the MS shall stop timer T3302. If timer T3311
    is currently running, the MS shall stop timer T3311.*/
    Gmm_TimerStop(GMM_TIMER_T3311);
    Gmm_TimerStop(GMM_TIMER_T3302);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_SndAttachReq:NORMAL: STATUS IS GMM_REGISTERED_INITIATED");

    g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;
    }

    pSendNasMsg = Gmm_AttachRequestMsgMake();                                   /* ����ATTACH REQUEST��Ϣ                   */

    gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;                                /* ϵͳ��ϢҪ���RAU���̱�־��� */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

        /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

        /*When ciphering is requested at GPRS attach, the authentication and
        ciphering procedure shall be performed since the MS does not store
        the ciphering algorithm at detach. Upon GPRS attach, if ciphering is
        to be used, an AUTHENTICATION AND CIPHERING REQUEST message shall
        be sent to the MS to start ciphering.*/
        gstGmmCasGlobalCtrl.ucGprsCipher          = VOS_FALSE;

        NAS_GMM_SndMmcCipherInfoInd();

        GMM_UpdateSysTlli(GMM_FOREIGN_TLLI);                                    /* ���foreign TLLI */
        /* ָ��TLLI��׼����LLC����GMM��Ϣ */

        if ((VOS_FALSE == NAS_USIMMAPI_IsTestCard())
         && (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
        {
            /* �˴���Ҫ�ͷ�ϵͳ��TILI,ָʾLLC���·���TILI���ָ����� */
            GMM_FreeSysTlli();
        }
        GMM_AssignSysTlli();                                                /* ָ�䵱ǰϵͳTLLIֵ */

        /* �ڷ���attachʱ���п���ԭ��������LLC���������ڷ���ATTACHǰ����Ҫ�ָ�LLC */
        if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ALL);
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
        }
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��PS��������                             */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);              /* ��RRMM_DATA_REQ����ATTACH REQUEST��Ϣ    */
        Gmm_TimerStart(GMM_TIMER_T3310);                                        /* ����Timer3310                            */
    }
    else
    {                                                                           /* û��PS��������                           */
        if (GMM_TRUE == g_GmmAttachCtrl.ucPagingWithImsiFlg)
        {                                                                       /* ����attach��pagging����Ӧ                */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_FALSE;                    /* �����־                                 */

            Gmm_SndRrmmEstReq(RRC_EST_CAUSE_REGISTRATION,
                              RRC_IDNNS_IMSI_PAGE_RSP,
                              pSendNasMsg);                                     /* ��RRMM_EST_REQ����ATTACH REQUEST��Ϣ     */
        }
        else
        {                                                                       /* ����attach����pagging����Ӧ              */

            Gmm_SndRrmmEstReq(RRC_EST_CAUSE_REGISTRATION,
                              GMM_RRC_IDNNS_UNKNOWN,
                              pSendNasMsg);
        }

        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);                        /* ���������������ӱ���Timer                */

    }
    if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_ATTACH_COMBINED         == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ATTACH���Ͳ���normal attach              */
        NAS_GMM_SndMmCombinedAttachInitiation();                                   /* ��MMCGMM_COMBINED_ATTACH_INITIATION��MMC */
    }

    /* ��CSҵ�����ʱ,RAU���ܵ��µ�����attach��Ȼ��Ҫ������ͨ��attach
       ����ᵼ��CSҵ���ж� */
    if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_NORMAL          == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_TRUE                   == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        ucAttachType = NAS_OM_GMM_GPRS_ATTACH;
    }
    else if (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
    {
        ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;
    }
    else
    {
        ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;
    }
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_REQ,
                    (VOS_VOID *)&ucAttachType,
                    NAS_OM_EVENT_ATTACH_REQ_LEN);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_SndAttachReq
 ��������  : ����ATTACH REQUEST
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : luokaihui /00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
  3.��    ��   : 2012��8��15��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  4.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����   :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
  5.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
*****************************************************************************/
VOS_VOID NAS_GMM_SndAttachReq(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_LTE)
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    VOS_UINT32                          ucIsSupportLteCapaFlg;

    ucIsSupportLteCapaFlg  = NAS_MML_IsSupportLteCapability();

    /* 1��L disable״̬��syscfg�������ò�֧��L����ȫ�ֱ�����¼GAS����㷢�͵�MS Radio Access capability IE��֧��LTE�ģ�
       2��L enalbe״̬��syscfg����֧��L,��ȫ�ֱ�����¼GAS����㷢�͵�MS Radio Access capability IE�ǲ�֧��LTE�ģ�
       ��Ҫ������ʱ���ȴ�GAS������ϱ����µ�MS Radio Access capability IE��Ϣ*/
    if ( ucIsSupportLteCapaFlg != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs)
    {
        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);

        Gmm_ComStaChg(GMM_REGISTERED_INITIATED);
        return;
    }
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */


    /* ֧��L������tinֵΪguti����²����ȡL�İ�ȫ������ */
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType() )
     && (VOS_FALSE == gstGmmSuspendCtrl.ucGetLteSecContext )
     && (VOS_TRUE == ucIsSupportLteCapaFlg))
    {
        if ( VOS_TRUE == NAS_GMM_GetLmmSecInfoFlg() )
        {
            return;
        }

        NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_ATTACH);

        NAS_GMM_SetLmmSecInfoFlg(VOS_TRUE);

        Gmm_ComStaChg(GMM_REGISTERED_INITIATED);

        /* ��Lģ����GMM_LMM_RESEL_SECU_INFO_REQ */
        NAS_GMM_SndLmmReselSecuInfoReq();

        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);
    }
    else
#endif

    {
        Gmm_SndAttachReq();
    }

}

/*******************************************************************************
  Module   : Gmm_AttachInitiate
  Function : GMM ATTACH���ܵ���ں���
  Input    : VOS_UINT8   ucSpecProc         ָ��attach��������
                       = GMM_NULL_PROCEDURE Ĭ������
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2007��1��10��
    ��    ��   : x51137
    �޸�����   : A32D08318
  3.��    ��   : 2007��12��12��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D13866
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��2��15��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����������ǰ����CSFBҵ���־����ֻ��ATTACH
  6.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  7.��    ��   : 2012��9��25��
    ��    ��   : h00216089
    �޸�����   : DTS2012090304976:����������Detach(re-attach not required)��MM��ʱ����ʱ����LU��
                  LU�������յ�ϵͳ��ϢGMM�����ٷ���Attach
  8.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
  9.��    ��   : 2014��6��17��
    ��    ��   : s00217060
    �޸�����   : DTS2014061003286:attach��������3311��ʱ����ʱ��־
  10.��    ��   : 2015��1��15��
     ��    ��   : z00161729
     �޸�����   : AT&T ֧��DAM�����޸�
  11.��    ��   : 2015��4��3��
     ��    ��   : w00167002
     �޸�����   : DTS2015040102624:attach�������T3212��ʱ��ǣ�����attach�ɹ�
                  ����������������RAU
*******************************************************************************/
VOS_VOID Gmm_AttachInitiate(VOS_UINT8 ucSpecProc)
{
    VOS_UINT8                           ucCsRestrictRegister;
    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /*����Attachʱ������յ�����detach��ʶ*/
    g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_FALSE;

    if ((GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
        && (0x10 != (g_GmmGlobalCtrl.ucState & 0xF0)))
    {                                                                           /* GMM context����                          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachInitiate:WARNING: Attach procedure shall not be activated");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {                                                                           /* PS��ATTACH����ֹ                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: Attach procedure is not allowed");


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }

    g_GmmAttachCtrl.ucT3310outCnt = 0;

    /* attach��������3311��ʱ����ʱ��־ */
    g_GmmRauCtrl.ucT3311ExpiredFlg  = GMM_FALSE;

    /* attach�������T3212��ʱ��ǣ�����attach�ɹ�����������������RAU */
    NAS_GMM_SetT3312ExpiredFlg(GMM_FALSE);

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());


    /* ����CS��������ʱ������NORMAL ATTACH */
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        /* ����ģʽI, ��PS�򵥶�ע��ɹ����յ�ϵͳ��Ϣ����Ҫ�ٴδ���COMBINED ATTACH */
        if ( GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod )
        {
            NAS_GMM_SetSpecProcInCsTrans(GMM_ATTACH_NORMAL);
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;                         /* �洢��ǰ���е�specific����               */
        NAS_GMM_SndAttachReq();                                                 /* ���ú�������ATTACH REQUEST               */
        return;
    }


    if (GMM_NULL_PROCEDURE != ucSpecProc)
    {/* ָ��attach����������Ч */
        g_GmmGlobalCtrl.ucSpecProc = ucSpecProc;
        NAS_GMM_SndAttachReq();
        return;
    }

    /* �ο��������,CS����attachʱ,NMO 1�²������ֻ�ģʽֱ�ӽ�������ע�� */
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;                         /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: normal attach procedure start");

        NAS_GMM_SndAttachReq();                                                     /* ���ú�������ATTACH REQUEST               */
        return;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS��SIM��Ч                              */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {                                                                       /* CS���Ѿ�ע��                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {                                                                   /* CS����ͨ����                             */
                g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL_CS_TRANS;        /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: normal attach procedure during cs transaction started");

                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
            }
            else
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_WHILE_IMSI_ATTACHED;    /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: GPRS attach while IMSI attached procedure started");
            }
        }
        else
        {                                                                       /* CS��ûע��                               */

            if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
             || (VOS_TRUE == ucCsRestrictRegister))
            {                                                                   /* CS��ATTACH����ֹ                         */
                g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;                 /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: normal attach procedure start");
            }
            else
            {                                                                   /* CS��ATTACHû����ֹ                       */
                if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                {                                                               /* CS����ͨ����                             */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL_CS_TRANS;    /* �洢��ǰ���е�specific����               */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: normal attach procedure during cs transaction started");
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;   /* ���CSͨ���е�����                       */
                }
                else
                {                                                               /* CS����ͨ����                           */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_COMBINED;           /* �洢��ǰ���е�specific����               */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: combined attach procedure started");
                }
            }
        }
    }
    else
    {                                                                           /* SIM��Ч                                  */
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;                         /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_AttachInitiate:INFO: normal attach procedure start");
    }

    NAS_GMM_SndAttachReq();                                                         /* ���ú�������ATTACH REQUEST               */

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvSmEstablishReq
  Function : ����SM��GMMSM_ESTABLISH_REQԭ��Ĵ���
  Input    : VOS_VOID *pMsg         ָ��ԭ��GMMSM_ESTABLISH_REQ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��־��  2005.03.23  NAS_IT_BUG_026��Ӧ
    3. ��    ��   : 2007��1��10��
       ��    ��   : x51137
       �޸�����   : A32D08308
    4. ��    ��   : 2007��12��12��
       ��    ��   : luojian id:60022475
       �޸�����   : �������ⵥ�ţ�A32D13866
    5. ��    ��   : 2008��7��24��
       ��    ��   : luojian 00107747
       �޸�����   : �������ⵥ�ţ�AT2D04627/AT2D04237
    6. ��    ��   : 2010��9��9��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�DTS2010090600355�������ȼ��б�����ʱ��CS ONLY����Ȼ��Ҫ�ܴ���PS Attach
    7. ��    ��   : 2010��10��05��
       ��    ��   : o00132663
       �޸�����   : �������ⵥ�ţ�DTS2010093001174��GCF12.9.6,��PS����ע��ʱ�������ǰGMM����δע������״̬��
                    �ܾ�SM������
    8. ��    ��   : 2010��12��05��
       ��    ��   : o00132663
       �޸�����   : �������ⵥ�ţ�DTS2010120203079��GCF12.9.6�����޸ĺ󣬵��¿��������У�����û�ֱ�ӷ���PDP���
                    Ҳ�ᱻGMM�ܾ���MP��ʾ619�����������GCF����׮��
    9. ��    ��   : 2010��12��31��
       ��    ��   : A00165503
       �޸�����   : ���ⵥ�ţ�DTS2010123000205��ע�ᵽ��������磬GMM������״̬�£���SIM����Ч����SM�����ע������ֱ�ӷ���ʧ��
    10.��    ��   : 2011��7��25��
       ��    ��   : h44270
       �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
   11. ��    ��   : 2011��05��13��
       ��    ��   : h44270
       �޸�����   : �������ⵥ�ţ�DTS2011051203553����ATTACH�����з�����ѡ����ϵͳRAi��ͬʱ��GMM״̬����ȷ������ҵ�񲻿���
   12.��    ��  : 2012��08��24��
       ��    ��  : m00217266
       �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
   13.��    ��   : 2012��8��15��
      ��    ��   : z00161729
      �޸�����   : DCM������������������޸�
   14.��    ��   : 2012��9��15��
      ��    ��   : z00161729
      �޸�����   : DTS2012091707434:pdp��������ģʽII,gmm����attach���Ͳ���Ӧ��Ϊgprs-attach
   15.��    ��   : 2012��11��02��
      ��    ��   : l65478
      �޸�����   : DTS2012110104636:�ڽ�ֹPLMN�Ͻ�����ATTACH
   16.��    ��   : 2013��1��4��
      ��    ��   : w00176964
      �޸�����   : DTS2013010400031:ȫ�ֱ���g_ucGcfInd�滻ΪUSIM�ṩAPI����USIMM_IsTestCard
   17.��    ��   : 2013��3��8��
      ��    ��   : t00212959
      �޸�����   : DTS2013030407991
   18.��    ��   : 2013��6��5��
      ��    ��   : w00242748
      �޸�����   : svlte��usim�ӿڵ���
   19.��    ��   : 2014��02��13��
      ��    ��   : f62575
      �޸�����   : DTS2014012902032: ��ֹSVLTE��Ʒ����˫PSע��
*******************************************************************************/
VOS_VOID Gmm_RcvSmEstablishReq(VOS_VOID  *pMsg)
{
    /* Modified by z00161729 for DCM�����������������, 2012-8-30, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-30, end */
    VOS_UINT32                                              ulIsTestCard;
    VOS_UINT32                                              ulPsAttachAllowFlg;
    VOS_UINT32                                              ulCsOnlyDataServiceSupportFlg;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();

    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {                                                                           /* PS�Ѿ�ע��                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmEstablishReq:WARNING: GMM has been attached");

        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* ��SM��CNF                                */

        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);

        return;
    }

    if (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {                                                                           /* PS�Ѿ�ע��                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmEstablishReq:WARNING: GMM has been attached");

        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);        /* ��SM��CNF                                */

        return;
    }

    ulPsAttachAllowFlg              = NAS_MML_GetPsAttachAllowFlg();
    ulCsOnlyDataServiceSupportFlg   = NAS_MML_GetCsOnlyDataServiceSupportFlg();

    if ((VOS_TRUE != ulPsAttachAllowFlg)
     && (VOS_TRUE != ulCsOnlyDataServiceSupportFlg))

    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
        "Gmm_RcvSmEstablishReq:WARNING: GMM attached not allow.");

        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);        /* ��SM��CNF                                */

        return;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_TRUE;                                  /* �ø�SM��EST_CNF��־ΪTRUE                */
        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
        if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
        {                                                                           /* PS�Ѿ�ע��                               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmEstablishReq:WARNING: GMM has been attached");

            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ACCESS_BARRED);        /* ��SM��CNF                                */

            return;
        }

        NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_ATTACH);

        g_GmmAttachCtrl.ucSmCnfFlg             = GMM_TRUE;                      /* �ø�SM��EST_CNF��־ΪTRUE                */
        g_GmmGlobalCtrl.ucFollowOnFlg          = GMM_TRUE;                      /* ����follow on ��־                       */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

#if (FEATURE_ON == FEATURE_LTE)
        enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

        if (VOS_TRUE == NAS_GMM_IsNeedEnableLte_AttachPs())
        {
            /* LTE�������ε��µ�disable LTE,��ʱ����֪ͨGU����� */
            if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
             && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus)
             && (VOS_FALSE == g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs))
            {
                g_GmmGlobalCtrl.ucSpecProc = NAS_GMM_GetAttachType();

                /* ��Ҫenable lte ���� ����Ҫ������ʱ���ȴ�gas�ϱ�ms radio capability���� */
                Gmm_TimerStart(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
                Gmm_ComStaChg(GMM_REGISTERED_INITIATED);
                return;
            }
        }
#endif

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                  /* ���ú�������attach ����                  */
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

        break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_RcvCmServReq_DeregAtmpToAtch(pMsg);
        break;

    case GMM_DEREGISTERED_PLMN_SEARCH:
        if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
        {
            /* GCF����12.9.6��PSע��������ǰδע�ᣬ�Ҵ�������״̬����ʱ�յ�SM��ҵ�����󣬲����壬ֱ�ӻظ�ʧ�ܡ� */
            if ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
              && (VOS_TRUE == ulIsTestCard))
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ACCESS_BARRED);
            }
            else
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);

                g_GmmAttachCtrl.ucSmCnfFlg             = GMM_TRUE;              /* �ø�SM��EST_CNF��־ΪTRUE                */
                g_GmmGlobalCtrl.ucFollowOnFlg          = GMM_TRUE;              /* ����follow on ��־                       */
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
                Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_ATTACH);
                /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

            }
        }
        else
        {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_SIM_PS_DOMAIN_REG_INVALID); /* ��SM��CNF                                */
        }
        break;

    default:
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_UNKNOWN);         /* ��SM��CNF                                */
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAttachAcceptMsg
  Function : ���տտ���Ϣ�տ���ϢATTACH ACCEPT�Ĵ���
  Input    : NAS_MSG_STRU *pMsg     ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2008��7��2��
      ��    ��   : l00107747
      �޸�����   : �������ⵥ�ţ�AT2D03900,GMM��ATTACH ACCEPT�������ʱû�����FOLLOW ON��־
    3.��    ��   : 2008��11��25��
      ��    ��   : l65478
      �޸�����   : �������ⵥ�ţ�AT2D06903��GSMģʽ�£������յ�����ATTACH accept��Ϣ��GMM����attach complete
    4.��    ��   : 2010��09��24��
      ��    ��   : l00167671
      �޸�����   : ���ⵥ��: DTS2010092001266���ָ�GPRS�����RAU�����г������������½���ͬ·����û���ٴη���RAU����
    5.��    ��   : 2011��7��14��
      ��    ��   : h44270
      �޸�����   : V7R1 PhaseII�׶ε�����ע������
    6.��    ��   : 2012��01��12��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�DTS2012010602762:SYSCFG���ó�֧��CS ONLY��
                 PS��Ȼ��ʾ��������
    7.��    ��   : 2012��08��24��
      ��    ��   : m00217266
      �޸�����   : ɾ��GMM_ClearErrCode��PS��������ϱ���Ŀ��
    8.��    ��   : 2012��8��14��
      ��    ��   : t00212959
      �޸�����   : DCM�����������������

    9.��    ��   : 2013��6��26��
      ��    ��   : w00167002
      �޸�����   : SVLTE STC:��ATTACHʱ��G�£��û�����PS detach��UE�����緢��
                   detach ���󣬺������·���ATTACH ACEPT �Գ壬��Ҫ����ATTACH ACPT
                   ��Ϣ��

   10.��    ��   : 2013��11��19��
      ��    ��   : l00208543
      �޸�����   : DTS2013111904411 �ܾ�ԭ��ֵת��

   11.��    ��   : 2014��2��18��
      ��    ��   : l00215384
      �޸�����   : DTS2014021006453��ע��ɹ����Ȩ�ܾ���������
   12.��    ��   : 2014��10��20��
      ��    ��   : h00285180
      �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
   13.��    ��   : 2014��12��17��
      ��    ��   : b00269685
      �޸�����   : ��Attach�ɹ���ֹͣ3314��ʱ��
*******************************************************************************/
VOS_VOID Gmm_RcvAttachAcceptMsg(
                            NAS_MSG_FOR_PCLINT_STRU *pMsg
                            )
{
    NAS_MSG_STRU        *pGmmStatus;
    VOS_BOOL            bTlliUpdateFlag = VOS_TRUE;

    NAS_MML_RAI_STRU                   *pstLastSuccRai = VOS_NULL_PTR;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;

    if ((GMM_TRUE == GMM_IsCasGsmMode())
        && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        bTlliUpdateFlag = VOS_FALSE;
    }
    else if ( ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType()) && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState) )
           || (GMM_DEREGISTERED_INITIATED    == g_GmmGlobalCtrl.ucState))
    {                                                                           /* GMM״̬����GMM_REGISTERED_INITIATED      */
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachAcceptMsg:WARNING: GMM is not in GMM_REGISTERED_INITIATED");

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }
    else
    {
    }

    if (GMM_MSG_LEN_ATTACH_ACCEPT > pMsg->ulNasMsgSize)
    {                                                                           /* ��Ϣ����                                 */
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachAcceptMsg:WARNING: ATTACH ACCEPT is too short");

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if (GMM_FAILURE == Gmm_IECheck_AttachAccept(pMsg))                          /* ���ú����ж�ATTACH ACCEPT��Ϣ����ȷ��    */
    {
        pGmmStatus =
            Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachAcceptMsg:WARNING: ATTACH ACCEPT is semantically incorrect");

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if (GMM_FALSE == Gmm_AttachRauAcceptJudgeRai(pMsg))
    {                                                                           /* ATTACH ACCEPT��RAI��ϵͳ��Ϣ��RAI��һ��  */
        pGmmStatus =
            Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAttachAcceptMsg:WARNING: RAI in ATTACH ACCEPT is differenct with current RAI");

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

        return;
    }
    NAS_GMM_ResetRejCauseChangedCounter();


    g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ֹͣTimer3310                            */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    /* 4.7.2.1.2 Handling of READY timer in the MS in Iu mode and S1 mode
       The READY timer is not applicable for Iu mode and S1 mode.
       Upon completion of a successful GPRS attach or routing area updating
       procedure in Iu mode, the MS may stop the READY timer, if running.
       Upon completion of a successful EPS attach or tracking area updating
       procedure, the MS may stop the READY timer, if running. */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
    }

    Gmm_AttachAcceptHandle(pMsg, bTlliUpdateFlag);                                               /* ���ú�������ATTACH REQUEST��IE           */

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
    pstAuthRejInfo->ucHplmnPsAuthRejCounter = 0;


    /* Added by t00212959 for DCM�����������������, 2012-8-14, begin */
    /*attach �ɹ�������Drx����Я��״̬*/
    NAS_MML_SetPsRegContainDrx(g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx);

    /* ��ά�ɲ�������Ϣ��ӡ */
    NAS_GMM_LogPsRegContainDrxInfo(g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx);

    /* Added by t00212959 for DCM�����������������, 2012-8-14, end */


    /* ȡ�õ�ǰע��ɹ���RAI��Ϣ��ע��:����Ϣ�Ļ�ȡҪ���ڽ�����RAI��Ϣ֮�� */
    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();

    /* ��GUģ��RPlmn��Ϣ�����˸ı䣬�򱣴�RPlmn��Ϣ��ȫ�ֱ����У������µ�NVIM�� */
    if ( VOS_TRUE == NAS_GMM_IsGURplmnChanged( &(pstLastSuccRai->stLai.stPlmnId),
                                               NAS_MML_GetCurrNetRatType() ) )
    {
        /* ����RPlmn��Ϣ��ȫ�ֱ����� */
        NAS_MML_UpdateGURplmn( &(pstLastSuccRai->stLai.stPlmnId),
                               NAS_MML_GetCurrNetRatType() );

        /* ��ȫ�ֱ����е�RPlmn��Ϣ���µ�NVIM�� */
        NAS_GMM_WriteRplmnWithRatNvim( NAS_MML_GetRplmnCfg() );
    }

    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���follow on ��־                       */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    if (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg)
    {                                                                           /* �ȴ�����RAU                              */
        if (0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
        {                                                                       /* ATTACH���̳ɹ�����                       */
            if (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg)
            {                                                                   /* ��Ҫ����MM����LU                         */
                if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
                    && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
                {                                                               /* ����ģʽ�ı�                             */
                    NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
                    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
                    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;

                    if (   (GMM_FALSE == GMM_IsCasGsmMode())
                        && (GMM_FALSE == g_GmmGlobalCtrl.ucFopFlg))
                    {
                        Gmm_TimerStart(GMM_TIMER_T3340);
                    }

                    return;
                }
            }
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
        }
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
    }
    else
    {
        if (GMM_MSG_HOLD_FOR_DETACH
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
        {                                                                           /* ����б�����DETACHԭ��                   */
            Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* ��������Ϣ�ַ�                           */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
        }
    }


    if (   (GMM_FALSE == GMM_IsCasGsmMode())
        && (GMM_FALSE == g_GmmGlobalCtrl.ucFopFlg))
    {
        Gmm_TimerStart(GMM_TIMER_T3340);
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ�Ĵ���
  Input    : VOS_VOID   *pMsg                     ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.03.11  �¹�����
  2.��    ��   : 2007��12��12��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D13866
  3.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������

  4.��    ��   : 2013��4��1��
    ��    ��   : w00167002
    �޸�����   : DTS2013032708183:L��ע��ɹ����û�����CGATT=0����W������,��
                  ���������У��û�����CGATT=1�����UE��L������ע��ɹ���MM/GMM
                  û�лظ�ATTACH CNF,����ATͨ��һ�±�������GCF9.2.2.1.8��������ʧ�ܡ�
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq(
    VOS_VOID                           *pMsg                                       /* ��Ϣָ��                                 */
)
{
    MMCGMM_ATTACH_REQ_STRU             *pAttach;                                         /* ����ָ��                                 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;

    pAttach     = (MMCGMM_ATTACH_REQ_STRU *)pMsg;                                   /* ��ʼ��ָ��                               */
    enRatType   = NAS_MML_GetCurrNetRatType();
    /* �˴���attach�����޸�,MMC����PS���л���,�յ�ATTACH����ʱ,
    ��Gģ�����ж�����MM��״̬,MM���������򶪵���Attach,����MM
    ע��ɹ�����ϵͳ��Ϣ����ʱ,GMM���ϱ���ǰ����״̬*/
    if ((MMC_MM_SIGNALING_STATUS_PRESENT == MM_GetSignalingStatus ())
     && (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF,��ֹAT��һֱ��CGATT�������� */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


        NAS_INFO_LOG(WUEPS_PID_GMM,"Gmm_RcvMmcGmmAttachReq:Mm Conn is exist");
        return;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* GMM״̬                                  */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvMmcGmmAttachReq_RegInit(pAttach);                                /* ���ú�������                             */
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvMmcGmmAttachReq_DeregInit(pAttach);                              /* ���ú�������                             */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvMmcGmmAttachReq_RauInit(pAttach);                                /* ���ú�������                             */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvMmcGmmAttachReq_ServReqInit(pAttach);                            /* ���ú�������                             */
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvMmcGmmAttachReq_DeregNmlServ(pAttach);                           /* ���ú�������                             */
        break;
    case GMM_DEREGISTERED_LIMITED_SERVICE:
        Gmm_RcvMmcGmmAttachReq_DeregLimitServ(pAttach);                         /* ���ú�������                             */
        break;
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_RcvMmcGmmAttachReq_DeregAtmpToAtch(pAttach);                        /* ���ú�������                             */
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_RcvMmcGmmAttachReq_RegNmlServ((MMCGMM_ATTACH_REQ_STRU *)pMsg);                                /* ���ú�������                             */
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdt(pAttach);                          /* ���ú�������                             */
        break;
    case GMM_REGISTERED_LIMITED_SERVICE:
        Gmm_RcvMmcGmmAttachReq_RegLimitServ(pAttach);                           /* ���ú�������                             */
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm(pAttach);                        /* ���ú�������                             */
        break;

    #if ((defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER ))
    case GMM_DEREGISTERED_PLMN_SEARCH:
        break;

    case GMM_REGISTERED_PLMN_SEARCH:
        break;
    #endif

    /* ������״ֱ̬�ӻظ�ATTACH CNF,��ֹAT��һ�±�CGATT=1�������� */
    default:


        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq:WARNING: Attach can't be proceeded g_GmmGlobalCtrl.ucState!");
        GMM_PrintState();
        break;
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_RegInit
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_REGISTERED_INITIATED״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.11  �¹�����
    2.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_RegInit(
                                    MMCGMM_ATTACH_REQ_STRU    *pMsg             /* ��Ϣָ��                                 */
                                    )
{
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if ((MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
            || (MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pMsg->enAttachType))
        {                                                                       /* ע��CS�����PS,CS��ע��                  */
            if ((GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* ��ǰ����ΪNORMAL ATTACH                  */
                g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;              /* ���̽���֮�����RAU                      */
                g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;             /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
            }
        }
    }
    return;
}
/*******************************************************************************
 �� �� ��  : Gmm_RcvMmcGmmAttachReq_DeregInit
 ��������  : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_DEREGISTERED_INITIATED״̬�Ĵ���
 �������  : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��5��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_DeregInit(
                                    MMCGMM_ATTACH_REQ_STRU    *pMsg             /* ��Ϣָ��*/
                                    )
{
    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
     && (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {
        /*�������ڽ���ʱ���ͷ����ӣ���Ϊdetach��attach���Ѿ����*/
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;

    }
    else
    {
       /*���ӽ�����ɣ���Ϊdetach��ɣ����½���attach*/
       Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

       Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                  /* ����attach */
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_RauInit
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_ROUTING_AREA_UPDATING_INITIATED
             ״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.11  �¹�����
    2.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_RauInit(
                                     MMCGMM_ATTACH_REQ_STRU    *pMsg            /* ��Ϣָ��                                 */
                                     )
{
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if ((MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
            || (MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pMsg->enAttachType))
        {                                                                       /* ע��CS�����PS,CS��ע��                  */
            if ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* ��ǰ����ΪNORMAL ATTACH                  */
                g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;              /* ���̽���֮�����RAU                      */
                g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;             /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
            }
        }
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_ServReqInit
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_SERVICE_REQUEST_INITIATED״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.11  �¹�����
    2.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_ServReqInit(
                                        MMCGMM_ATTACH_REQ_STRU    *pMsg         /* ��Ϣָ��                                 */
                                        )
{
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
        {                                                                       /* ע��CS��                                 */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* ͣT3317                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU����                              */
        }
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_DeregNmlServ
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_DEREGISTERED_NORMAL_SERVICE״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.03.11  �¹�����
  2.��    ��   : 2007��02��01��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D08656
  3.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_DeregNmlServ(
                                         MMCGMM_ATTACH_REQ_STRU    *pMsg        /* ��Ϣָ��                                 */
                                         )
{
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_DeregNmlServ:WARNING: PS ATTACH is not allowed");
        return;
    }
    if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
     && (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
     && (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* ע��CS��                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_DeregNmlServ:WARNING: CS shall be registered by MM in A+II");
        return;
    }

    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {

        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);                          /* ״̬Ǩ��                                 */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                      /* ״̬Ǩ��                                 */

        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }
    else if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
    }
    else
    {
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����ATTACH����                           */
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_DeregLimitServ
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_DEREGISTERED_LIMITED_SERVICE״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.03.11  �¹�����
  2.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����  : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����  : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_DeregLimitServ(
                                          MMCGMM_ATTACH_REQ_STRU    *pMsg       /* ��Ϣָ��                                 */
                                          )
{
    VOS_UINT32                          ulCause = NAS_MML_REG_FAIL_CAUSE_NULL;                                /* ������ʱ����                             */


    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {                                                                           /* PS������ע��                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_DeregLimitServ:WARNING: PS ATTACH is not allowed");
        return;
    }
    if (GMM_FORBIDDEN_PLMN
        == (g_GmmGlobalCtrl.SysInfo.ucForbMask & GMM_FORBIDDEN_PLMN))
    {                                                                           /* ��GMM_FORBIDDEN_PLMN�б�                 */
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
    }
    else if (GMM_FORBIDDEN_PLMN_FOR_GPRS
        == (g_GmmGlobalCtrl.SysInfo.ucForbMask & GMM_FORBIDDEN_PLMN_FOR_GPRS))
    {                                                                           /* ��GMM_FORBIDDEN_PLMN_FOR_GPRS�б�        */
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
    }
    else if (GMM_FORBIDDEN_LA_FOR_ROAM
        == (g_GmmGlobalCtrl.SysInfo.ucForbMask & GMM_FORBIDDEN_LA_FOR_ROAM))
    {                                                                           /* ��GMM_FORBIDDEN_LA_FOR_ROAM�б�          */
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
    }
    else if (GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS
                    == (g_GmmGlobalCtrl.SysInfo.ucForbMask
                                        & GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS))
    {                                                                           /* ��GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS�б�  */
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
    }
    else
    {
    }

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if (NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS == ulCause)
        {                                                                       /* ԭ��ֵΪ��14                             */
            if (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
            {                                                                   /* ע��CS��                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcGmmAttachReq_DeregLimitServ:NORMAL: Attach Type is MMC_GMM_ATTACH_TYPE_IMSI");
                g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~GMM_WAIT_CS_ATTACH;
                return;
            }
        }
        else
        {
            if(GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {                                                                   /* CS ͨ����                                */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_ATTACH_NORMAL;
            }
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcGmmAttachReq_DeregLimitServ:INFO: normal attach procedure during cs transaction started");
        }
    }


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_RegLimitServ
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_REGISTERED_LIMITED_SERVICE״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.03.12  �¹�����
  2.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_RegLimitServ(
                                         MMCGMM_ATTACH_REQ_STRU    *pMsg        /* ��Ϣָ��                                 */
                                         )
{

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {                                                                           /* PS������ע��                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_RegLimitServ:WARNING: PS ATTACH is not allowed");
        return;
    }

    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;                        /* ���ü����̱�־                           */

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {                                                                       /* CS ͨ����                                */
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_RAU_NORMAL;
        }
    }


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcGmmAttachReq_RegLimitServ:INFO: specific procedure ended");

    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_DeregAtmpToAtch
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH
             ״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.12  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_DeregAtmpToAtch(
                                            MMCGMM_ATTACH_REQ_STRU    *pMsg     /* ��Ϣָ��                                 */
                                            )
{
    if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪII                */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
        {                                                                       /* ע��CS��                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_DeregAtmpToAtch:WARNING: CS shall be registered by MM in A+II");
            return;
        }
    }

    if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* T3302��������                            */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ֹͣT3302                                */
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ֹͣT3311                                */
    }
    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                       /* ����ATTACH����                           */
    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_RegNmlServ
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_REGISTERED_NORMAL_SERVICE״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2004.03.12  �¹�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_RegNmlServ(
                                       MMCGMM_ATTACH_REQ_STRU    *pMsg          /* ��Ϣָ��                                 */
                                       )
{
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
         && (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType))
        {                                                                       /* ע��CS��                                 */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {                                                                   /* CS ͨ����                                */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_ATTACH_NORMAL;        /* ����CSͨ���е�����,Ϊ��CSͨ�Ž����󴥷�  *
                                                                                 * combined RAU with IMSI attach            */
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(
                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);                       /* ����RAU����                              */
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_RegNmlServ:WARNING: PS has been attached");
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_RegNmlServ:WARNING: PS has been attached");
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdt
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_REGISTERED_ATTEMPTING_TO_UPDATE
             ״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.12  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdt(
                                          MMCGMM_ATTACH_REQ_STRU    *pMsg       /* ��Ϣָ��                                 */
                                          )
{
    if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪII                */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
        {                                                                       /* ע��CS��                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdt:WARNING: CS shall be registered by MM in A+II");
            return;
        }
    }
    g_GmmRauCtrl.ucRauAttmptCnt = 0;                                            /* RAU attempt counter ��0                  */
    if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* T3302��������                            */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ֹͣT3302                                */
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ֹͣT3311                                */
    }
    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);                   /* ����RAU����                              */

    return;
}
/*******************************************************************************
  Module   : Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm
  Function : �յ�ԭ��MMCGMM_ATTACH_REQ��GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
             ״̬�Ĵ���
  Input    : MMCGMM_ATTACH_REQ_STRU   *pMsg        ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.12  �¹�����
    2.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm(
                                            MMCGMM_ATTACH_REQ_STRU    *pMsg     /* ��Ϣָ��                                 */
                                            )
{
    /* �ο��������,NMO1��,��ͨ���ֻ�ģʽ�жϷ�������ע�� */
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �û�ģʽΪA������ģʽΪI                 */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pMsg->enAttachType)
        {                                                                       /* ע��CS��                                 */
            if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* T3302��������                            */
                Gmm_TimerStop(GMM_TIMER_T3302);                                 /* ֹͣT3302                                */
            }
            else
            {
                Gmm_TimerStop(GMM_TIMER_T3311);                                 /* ֹͣT3311                                */
            }
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* ����RAU����                              */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm:WARNING: PS has been attached");
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm:WARNING: CS shall be registered by MM ");
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_AttachAccept_Mandatory_Ie_Check
  Function : ��Attach Accept��Ϣ�еı�ѡ����м��
  Input    : NAS_MSG_STRU *pMsg
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
    2.��    �� : 2011��08��01��
      ��    �� : k66584
      �޸����� : ���ⵥ��:DTS2011070804524, ɾ����RAI�жϲ��ִ���
*******************************************************************************/
VOS_UINT8 Gmm_AttachAccept_Mandatory_Ie_Check(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *pNeedReturn)
{
    VOS_UINT8   ucForceToStandby = 0;

    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAccept_Mandatory_Ie_Check:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    if ((1 != ((pMsg->aucNasMsg[2]) & 0x07))
       && (3 != ((pMsg->aucNasMsg[2]) & 0x07)))
    {                                                                           /* wrong Attach Result                      */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAccept_Mandatory_Ie_Check:WARNING: IE\"Attach result\" is error in ATTACH ACCEPT");
        return GMM_FAILURE;
    }

    ucForceToStandby = (VOS_UINT8)((pMsg->aucNasMsg[2] >> 4) & 0x07);

    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }

    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_AttachAccept_Mandatory_Ie_Check:WARNING:WARNING: IE\"Force to standby\" is error in ATTACH ACCEPT");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    gstGmmCasGlobalCtrl.enRaPrioLevFosSms = pMsg->aucNasMsg[4] & 0x07;

    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}
/*******************************************************************************
  Module   : Gmm_IECheck_Allocated_Ptmsi
  Function : ��IE Allocated P-TMSI���м��
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
*******************************************************************************/
VOS_UINT8 Gmm_IeCheck_Allocated_Ptmsi(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn)
{
    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IECheck_Allocated_Ptmsi:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ucIeOffset + 2))
    {
        return GMM_SUCCESS;
    }

    if (pMsg->aucNasMsg[ucIeOffset + 1] != 5)
    {                                                                           /* wrong Length of mobile identity contents */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IECheck_Allocated_Ptmsi:WARNING: Length of IE\"P-TMSI\" is invalid");
        return GMM_FAILURE;
    }

    if ((VOS_UINT8)(pMsg->ulNasMsgSize)
         < (ucIeOffset + pMsg->aucNasMsg[ucIeOffset + 1] + 2))
    {
        return GMM_SUCCESS;
    }

    if (pMsg->aucNasMsg[ucIeOffset + 2] != 0xF4)
    {                                                                           /* wrong Type of identity& Identity digit 1 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IECheck_Allocated_Ptmsi:WARNING: IE\"P-TMSI\" is invalid");
        return GMM_FAILURE;
    }

    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}
/*******************************************************************************
  Module   : Gmm_IeCheck_Ms_Identity_Imsi
  Function : ��IE MS identity Imsi���м��
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
    2.��    �� : 2013��09��10��
      ��    �� : l65478
      �޸����� : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
*******************************************************************************/
VOS_UINT8 Gmm_IeCheck_Ms_Identity_Imsi(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn)
{
    VOS_UINT8   ucImsiLen  = 0;

    ucImsiLen = pMsg->aucNasMsg[*ucIeOffset + 1];


    *ucIeOffset += (ucImsiLen + 2);

    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}
/*******************************************************************************
  Module   : Gmm_IeCheck_Ms_Identity
  Function : ��IE MS identity���м��
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
    2.��    �� : 2013��09��10��
      ��    �� : l65478
      �޸����� : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
*******************************************************************************/
VOS_UINT8 Gmm_IeCheck_Ms_Identity(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn)
{
    VOS_UINT8   ucNeedReturn = GMM_TRUE;
    VOS_UINT8   ucResult   = GMM_SUCCESS;

    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn) || (VOS_NULL == ucIeOffset))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_Ms_Identity:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (*ucIeOffset + 2))
    {
        return GMM_SUCCESS;
    }


    if ((VOS_UINT8)(pMsg->ulNasMsgSize)
         < (*ucIeOffset + pMsg->aucNasMsg[*ucIeOffset + 1] + 2))
    {
        return GMM_SUCCESS;
    }

    if (GMM_MOBILE_ID_IMSI == (pMsg->aucNasMsg[*ucIeOffset + 2] & 0x07))
    {                                                                           /* IE����IMSI                               */
        ucResult = Gmm_IeCheck_Ms_Identity_Imsi(pMsg, ucIeOffset, &ucNeedReturn);

        if (GMM_TRUE == ucNeedReturn)
        {
            return ucResult;
        }
    }
    else if (GMM_MOBILE_ID_TMSI_PTMSI == (pMsg->aucNasMsg[*ucIeOffset + 2] & 0x07))
    {                                                                           /* IE����TMSI                               */
        if (pMsg->aucNasMsg[*ucIeOffset + 2] != 0xF4)
        {                                                                       /* wrong Type of identity& Identity digit 1 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_Ms_Identity:WARNING: TMSI shall not be occured");
            return GMM_FAILURE;
        }

        if (pMsg->aucNasMsg[*ucIeOffset + 1] != 5)
        {                                                                       /* wrong Length of mobile identity contents */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_Ms_Identity:WARNING: Length of IE\"TMSI\" is invalid");
            return GMM_FAILURE;
        }

        *ucIeOffset += 7;
    }
    else
    {
        /* ����IEֱ������,eg:imei,imeisv,no identity */
        *ucIeOffset += pMsg->aucNasMsg[*ucIeOffset + 1] + 2;
    }

    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}
/*******************************************************************************
  Module   : Gmm_IeCheck_T3302_Value
  Function : ��IE T3302 value���м��
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
    2.��    �� : 2013��09��10��
      ��    �� : l65478
      �޸����� : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
*******************************************************************************/
VOS_UINT8 Gmm_IeCheck_T3302_Value(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                              VOS_UINT8    ucIeOffset,
                                              VOS_UINT8    *pNeedReturn)
{

    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_T3302_Value:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ucIeOffset + 2))
    {
        return GMM_SUCCESS;
    }


    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}
/*******************************************************************************
  Module   : Gmm_IeCheck_Equivalent_Plmns
  Function : ��IE Equivalent PLMNs value���м��
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
    2.��    �� : 2013��09��10��
      ��    �� : l65478
      �޸����� : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
*******************************************************************************/
VOS_UINT8 Gmm_IeCheck_Equivalent_Plmns(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                              VOS_UINT8    ucIeOffset,
                                              VOS_UINT8    *pNeedReturn)
{

    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_Equivalent_Plmns:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ucIeOffset + 2))
    {
        return GMM_SUCCESS;
    }

    if ((pMsg->aucNasMsg[ucIeOffset + 1] > 45)
        || (pMsg->aucNasMsg[ucIeOffset + 1] < 3)
        || ((pMsg->aucNasMsg[ucIeOffset + 1] % 3 ) != 0))
    {                                                                           /* wrong Length of PLMN List contents       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_Equivalent_Plmns:WARNING: Length of \"Equivalent PLMNs\" is error");
        return GMM_SUCCESS;
    }

    if ((VOS_UINT8)(pMsg->ulNasMsgSize)
         < (ucIeOffset + pMsg->aucNasMsg[ucIeOffset + 1] + 2))
    {
        return GMM_SUCCESS;
    }

    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}

/*******************************************************************************
  Module   : Gmm_IECheck_AttachAccept
  Function : �Կտ���ϢAttachAccept��IE���м��
  Input    : NAS_MSG_STRU *pMsg
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1. ��־��  2005.01.27  �¹�����
    2. ��־��  2005.04.02  NAS_IT_BUG_044��Ӧ
    3.��    ��   : 2007��07��05��
      ��    ��   : luojian id:60022475
      �޸�����   : �������ⵥ�ţ�A32D11970,�����ϢIE����spareλ�������.
    4.��    ��   : 2009��05��14��
      ��    ��   : h44270
      �޸�����   : ���ⵥ��:AT2D11898/AT2D11828,��IDLE̬�·���PS����ţ�û�а���ATTACH ACCEPT��Ϣ��Radio Priority for SMS��������Դ
    5.��    ��   : 2013��09��10��
      ��    ��   : l65478
      �޸�����   : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
    6.��    ��   : 2015��6��8��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_UINT8 Gmm_IECheck_AttachAccept(NAS_MSG_FOR_PCLINT_STRU *pMsg)
{
    VOS_UINT8   ucIeOffset = GMM_MSG_LEN_ATTACH_ACCEPT;                         /* ������ʱ�����洢�洢IE��ƫ����           */
    VOS_UINT8   ucEndFlg   = GMM_FALSE;                                         /* ���ڻ�������־ΪFALSE                    */
    VOS_UINT8   ucResult   = GMM_SUCCESS;
    VOS_UINT8   ucNeedReturn = GMM_TRUE;

    ucResult = Gmm_AttachAccept_Mandatory_Ie_Check(pMsg, &ucNeedReturn);

    if (GMM_TRUE == ucNeedReturn)
    {
        return ucResult;
    }

    /* ��ѡIE��� */
    for (; ((ucIeOffset < pMsg->ulNasMsgSize) && (GMM_FALSE == ucEndFlg)); )
    {                                                                           /* �洢IE��ƫ����С�ڿտ���Ϣ�ĳ���         */
        switch (pMsg->aucNasMsg[ucIeOffset])
        {                                                                       /* IEI                                      */
        case GMM_IEI_P_TMSI_SIGNATURE:                                          /* P-TMSI signature������Ҫ���             */
            ucIeOffset += 4;
            break;
        case GMM_IEI_NEGOTIATED_READY_TIMER_VALUE:                              /* Negotiated READY timervalue������Ҫ���  */
            ucIeOffset += 2;
            break;
        case GMM_IEI_ALLOCATED_PTMSI:                                           /* Allocated P-TMSI                         */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_Allocated_Ptmsi(pMsg, ucIeOffset, &ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }
            ucIeOffset += 7;
            break;
        case GMM_IEI_MS_IDENTITY:                                               /* MS identity                              */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_Ms_Identity(pMsg, &ucIeOffset, &ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }
            break;
        case GMM_IEI_GMM_CAUSE:                                                 /* GMM cause������Ҫ���                    */
            ucIeOffset += 2;
            break;
        case GMM_IEI_T3302_VALUE:                                               /* T3302 value������Ҫ���                  */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_T3302_Value(pMsg, ucIeOffset, &ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }
            ucIeOffset += 3;
            break;
        case GMM_IEI_CELL_NOTIFICATION:                                         /* Cell Notification������Ҫ���            */
            ucIeOffset += 1;
            break;
        case GMM_IEI_EQUIVALENT_PLMNS:                                          /* Equivalent PLMNs                         */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_Equivalent_Plmns(pMsg, ucIeOffset, &ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }
            ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            break;
        case GMM_IEI_EMERGENCY_NUMBER_LIST:                                     /* Emergency Number List                    */
            /*lint -e961*/
            if (ucIeOffset + 2 + pMsg->aucNasMsg[ucIeOffset + 1] <= pMsg->ulNasMsgSize)
            {
                ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            }
            else
            {
                ucEndFlg = GMM_TRUE;
            }
            /*lint +e961*/
            break;

        case NAS_GMM_IEI_T3323_VALUE:
            ucIeOffset += NAS_GMM_IE_T3323_VALUE_LEN;
            break;

        case NAS_GMM_IEI_T3312_EXTENDED_VALUE:
            ucIeOffset += NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN;
            break;

        default:
            if(GMM_IEI_NETWORK_FEATURE_SUPPORT == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            { /* Network feature support                  */
                ucIeOffset += 1;
            }
            /* referenc to 24.008 8.5 */
            else if(GMM_IEI_COMPREHENSION_REQUIRED == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            {
                return GMM_FAILURE;
            }
            /* TV���͵�IE */
            else if(GMM_IEI_FORMAT_T_TYPE == (pMsg->aucNasMsg[ucIeOffset] & GMM_IEI_FORMAT_TYPE_INFO))
            {
                ucIeOffset += 1;
            }
            /* TLV���͵�IE */
            /*lint -e961*/
            else if (ucIeOffset + 2 + pMsg->aucNasMsg[ucIeOffset + 1] < pMsg->ulNasMsgSize)
            {
                ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            }
            /*lint +e961*/
            else
            {
                ucEndFlg = GMM_TRUE;
            }
            break;
        }
    }
    return GMM_SUCCESS;

}
/*****************************************************************************
 �� �� ��  : NAS_GMM_AttachAcceptHandle_UpdateEPlmn
 ��������  : ����ATTACH Accept��Ϣ��EPLMN��Ϣ
 �������  : pstAcceptIe:   Attach Accept��ϢIE��Ϣ
              pstMsg    :    Attach Accept��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2012��10��26��
    ��    ��   : W00176964
    �޸�����   : DTS2012090303157:����EPLMN��Ч���
  4.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_AttachAcceptHandle_UpdateEPlmn(
    GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pstMsg
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmn = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stTmpEPlmnList;


    PS_MEM_SET(&stTmpEPlmnList, 0x00, sizeof(stTmpEPlmnList));

    pstEPlmnList = NAS_MML_GetEquPlmnList();
    pstCurrCampPlmn = NAS_MML_GetCurrCampPlmnId();

    /* ����տ���Ϣ��û��EPLMN,���浱ǰ����ΪEPLMN */
    if (GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG
        != (pstAcceptIe->ulOptionalIeMask
        & GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG))
    {
        stTmpEPlmnList.ucEquPlmnNum = 0x1;
        stTmpEPlmnList.astEquPlmnAddr[0] = *pstCurrCampPlmn;
    }
    else
    {
        /* ��IE�н���EquPlmn��Ϣ */
        NAS_GMM_DecodeEquPlmnInfoIE(GMM_MMC_ACTION_ATTACH,
                                    pstAcceptIe,
                                    pstMsg,
                                    &stTmpEPlmnList);
    }

    /* �տ���Ϣ��EPLMN�뱣��Ĳ�ͬ,��EPLMN���浽MMLȫ�ֱ����͸���NV */


    /* ��EPLMN���浽MMLȫ�ֱ��� */
    PS_MEM_CPY(pstEPlmnList, &stTmpEPlmnList, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MML_SetEplmnValidFlg(VOS_TRUE);

    /* ��EPLMN���µ�NV�� */
    NAS_GMM_WriteEplmnNvim(pstEPlmnList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsAttachOtherCause
 ��������  : �ж�GMM�ľܾ�ԭ��ֵ�Ƿ��ǲ����ṩCM����
 �������  : ucGmmCause   �ܾ���ԭ��

 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��9��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_IsAttachOtherCause(VOS_UINT16 usGmmCause )
{
     switch (usGmmCause)
     {
        /* ����ԭ��ֵ����Э����ȷ�����Ĳ����ṩCM����    */
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            return VOS_FALSE;
        default:
            return VOS_TRUE;
     }

}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

