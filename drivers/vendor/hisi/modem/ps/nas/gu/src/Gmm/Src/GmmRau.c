/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmRau.c
  Description   : GMM RAU������ش�����Դ�ļ�
  Function List :
    01.   Gmm_ComCmpMmLai
    02.   Gmm_Com_CmpMmPlmnid
    03.   Gmm_Com_CmpRai
    04.   Gmm_FillPdpContext
    05.   Gmm_PeriodRoutingAreaUpdateType
    06.   Gmm_RcvRoutingAreaUpdateAcceptMsg
    07.   Gmm_RcvRoutingAreaUpdateRejectMsg
    08.   Gmm_RoutingAreaUpdataAcceptCombined
    09.   Gmm_RoutingAreaUpdataAcceptRaOnly
    10.   Gmm_RoutingAreaUpdateAcceptMsgJudge
    11.   Gmm_RoutingAreaUpdateAttemptCounter
    12.   Gmm_RoutingAreaUpdateCompleteMsgMake
    13.   Gmm_RoutingAreaUpdateHandle
    14.   Gmm_RoutingAreaUpdateHandleFollowOn
    15.   Gmm_RoutingAreaUpdateInitiate
    16.   Gmm_RoutingAreaUpdateRejectCause11
    17.   Gmm_RoutingAreaUpdateRejectCause13
    18.   Gmm_RoutingAreaUpdateRejectCause3
    19.   Gmm_RoutingAreaUpdateRejectCause9
    20.   Gmm_RoutingAreaUpdateRequestMsgMake
    21.   Gmm_RoutingAreaUpdateResolveIe
    22.   Gmm_SndRoutingAreaUpdateReq
  History       :
    1.  ��־��  2003.12.05  �¹�����
    2.  s46746  2006-03-08  �������ⵥA32D02368�޸�
    3.  s46746  2006-03-15  �������ⵥA32D02466�޸�
    4.��    ��   : 2006��3��24��
      ��    ��   : liuyang id:48197
      �޸�����   : ���ⵥ�ţ�A32D01882�������ͷ�RR����ָʾ�ؽ����ӣ���ǰ�ؽ�ʱ
                   �����RR����ԭ�����
    5.  s46746  2006-04-03  �������ⵥA32D01509�޸�
    6.  s46746  2006-04-03  �������ⵥA32D02921�޸�
    7.  l40632  2006-04-18  �������ⵥA32D03250�޸�
    8.  s46746  2006-04-21  �������ⵥA32D02855�޸�
    9.  x51137 2006/4/28 A32D02889
   10.  s46746  2006-05-08  �������ⵥA32D03487�޸�
   11.  l40632  2006.05.20  �������ⵥA32D03865�޸�
   12.  l40632  2006.05.29  �������ⵥA32D04010�޸�
   13.  l40632  2006.06.08  �������ⵥA32D04196�޸�
                            �������ⵥA32D04193�޸�
   14.  s46746 2006-06-27   �������ⵥA32D04528�޸�
   15.��    ��   : 2006��9��13��
      ��    ��   : liurui id:40632
      �޸�����   : �������ⵥ�ţ�A32D05874
   16.��    ��   : 2006��11��1��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D06572
   17.��    ��   : 2006��11��7��
      ��    ��   : sunxibo id:46746
      �޸�����   : �������ⵥ�ţ�A32D06823
   18.��    ��   : 2006��11��8��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��:A32D06867
   19.��    ��   : 2007��01��16��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D08381
   20.��    ��   : 2007��3��5��
      ��    ��   : liurui id:40632
      �޸�����   : �������ⵥ�ţ�A32D09094
   21.��    ��   : 2007��05��11��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D10713
   22.��    ��   : 2007��06��16��
      ��    ��   : luojian id:60022475
      �޸�����   : �������ⵥ�ţ�A32D11635,gas�ϱ�GPRS RESUME FAILUREʱ,��Ȼ֪ͨ
                   RABM �ָ��ɹ�,�������PDP����ʱ,����RAU,��������RAU������ϵ
                   ͳ��ϢָʾRAI�����ı�Ͳ��ٷ���RAU.
   23.��    ��   : 2007��07��05��
      ��    ��   : luojian id:60022475
      �޸�����   : �������ⵥ�ţ�A32D11970,�����ϢIE����spareλ�������.
   24.��    ��   : 2007��10��27��
      ��    ��   : luojian id:107747
      �޸�����   : �������ⵥ�ţ�A32D13038
   25.��    ��   : 2007��11��12��
      ��    ��   : l39007
      �޸�����   : �������ⵥA32D13044,GSM����,ATTACHʧ��5��,֪ͨMM����һ��LAU
                   ��ʱ������Ϊ��GMM����ATTACH COMPLETE֮��
   26.��    ��   : 2007��11��12��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13123,RAU������Ϣ��Я��ready timer��MS Network Cap
                   ȥ��PDP������״̬.
   27.��    ��   : 2007��11��22��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13475,�޸���ϵͳ�ı��ָ�ɵ�old TLLI�Ϳ���������ԿΪȫ0����
   28.��    ��   : 2007��12��04��
      ��    ��   : s46746
      �޸�����   : 1.GMMģ�����ATTACH��RAUʱ�������ʱ����������������
                   �ᵼ��LLC��ATTACH��RAU�ӳٷ��ͣ�ʹ��ATTACH��RAUʱ�������
                   2.GMM�ڽ���RAU����ʱ�����DRX�������ı䣬����������Ϣ��
                   ��DRX������������SGSN��RAUʱ�����ܵ������಻ʶ��UE��DR
                   X������ʹ��RAU���ܳɹ���
   29.��    ��   : 2007��12��14��
      ��    ��   : s46746
      �޸�����   : ���ⵥA32D13638����֤����RAU֮ǰ�������෢���������ݣ�����RAU���ɹ������ָ���2
   30.��    ��   : 2007��12��15��
      ��    ��   : l00107747
      �޸�����   : ���ⵥ��:A32D13897,�ؽ�RR����ʱ��RAU������������:����ͷű�־
   31.��    ��   : 2007��12��20��
      ��    ��   : s46746
      �޸�����   : 2G3�л���W��RAU�����йҶϵ绰��RAU ACCEPT��Ϣ���յ���
                   ��RAU COMPLETE��Ϣδ���;ͽ�������RAU
   32.��    ��   : 2007��12��21��
      ��    ��   : l00107747
      �޸�����   : ���ⵥ��:A32D13951
   33.��    ��   : 2007��12��28��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
   34.��    ��   : 2007��12��28��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13987,RAU֮��û�����SPEC��־
   35.��    ��   : 2008��7��28��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��:AT2D03915,�޸�����RAU����,CS����Ѿ�����LAU�ɹ�����Ҫ
                   ����with IMSI Attach��RAU
   36.��    ��   : 2008��9��26��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D05431
   37.��    ��   : 2008��10��20��
      ��    ��   : o00132663
      �޸�����   : ���ⵥ��:AT2D06266, ���ӶԲ�֧��CELL NOTIFICATION�Ĵ���
   38.��    ��   : 2008��11��03��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D06494
   39.��    ��   : 2008��11��19��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D06723
   40.��    ��   : 2008��11��20��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D06857
   41.��    ��   : 2009��02��06��
      ��    ��   : o00132663
      �޸�����   : ���ⵥ��:AT2D08277,С����ѡ���µ�����ģʽ�ı��RAU�����쳣��
   42.��    ��   : 2009��2��18��
      ��    ��   : h44270
      �޸�����   : ���ⵥ��:AT2D08904,���ⳡ����-HK��D̬�����󣬷����������˺ܳ�ʱ�䣬�����ѵ�С����PS��ע��ʧ�ܣ�ȥ����PDP��Ȼע��ʧ��
   43.��    ��   : 2009��2��21��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D09315,��������ע��󣬱仯LAC, ����RAUʧ�ܣ�
                   ԭ��ֵRoaming not allowed in this location area,����������
                   ����������Ӧ������Rau������ΪCombined RA/LA updating with IMSI attach��
                   ��ʵ�ʷ���Attach���̡�
   44.��    ��   : 2009��4��30��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D11607,CS����й����У�PS�������һ��Normal Rau��
                   CS��ص����к�û�з���Combined Rau��
   45.��    ��   : 2009��5��13��
      ��    ��   : h44270
      �޸�����   : �������ⵥ�ţ�AT2D11658/AT2D11861�����������У��յ�RAU��PDP״̬Ϊȥ�������MS����PDPȥ����
   46.��    ��   : 2009��07��07��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D12817,2G�£�MS�����detach������RAI�ı䣬
                   Rau������û�����·���detach����
   47.��    ��   : 2009��07��14��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D12996,W��RAB�ؽ�����λ�����ı䷢��Rau��Rau����
                   ����ѡ��G�£�G��Rau��������Ȼ����Service Request����
   48.��    ��   : 2009��08��19��
      ��    ��   : x00115505
      �޸�����   : ���ⵥ��:AT2D13829,TLLIά������
   49.��    ��   : 2009��08��24��
      ��    ��   : x00115505
      �޸�����   : AT2D14023,����GCF����44.2.2.1.9ʧ��
   50.��    ��   : 2009��09��07��
      ��    ��   : x00115505
      �޸�����   : AT2D14252,���������У���RNCǨ�Ƶ���RNC�£�MS����RAU���̣�û������Follow-on
   51.��    ��   : 2009��09��30��
      ��    ��   : x00115505
      �޸�����   : AT2D14857,פ����FPLMN�ϣ�GMM������״̬�޸�ΪGU3��
   52.��    ��   : 2009��11��09��
      ��    ��   : x00115505
      �޸�����   : AT2D15398,����̬��G��ѡ��W�£�PDP������ȥ��������RABM���󱻷���
   53.��    ��   : 2010��03��15��
      ��    ��   : x00115505
      �޸�����   : AT2D17570,ĳЩ���Rau����ʱû���ϱ�EVENT�¼�
   54.��    ��   : 2010��04��14��
      ��    ��   : x00115505
      �޸�����   : AT2D18080,Direct Signalling Re-establish������Rau��Counterά������
*******************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "GmmCasSuspend.h"
#include "GmmCasMain.h"
#include "GmmMmInterface.h"
#include "NasMmlCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasGmmProcLResult.h"
#endif

 /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
#include "NasStkInterface.h"
#include "NasUsimmApi.h"
 /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */
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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_RAU_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*lint -save -e958 */

/*******************************************************************************
  Module   : Gmm_FillPdpContext
  Function : ��дPDP Context status
  Input    : VOS_UINT8 *pAddr  ��дPDP Context status���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    2.��    ��   : 2012��3��7��
      ��    ��   : z00161729
      �޸�����   : V7R1 C50 ֧��ISR�޸�
*******************************************************************************/
VOS_VOID Gmm_FillPdpContext(
                        VOS_UINT8 *pAddr                                        /* ��дPDP Context status���׵�ַ           */
                        )
{
    VOS_UINT32                          ulPdpCtxStatus;
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    pAddr[0] = GMM_IEI_PDP_CONTEXT_STATUS;                                      /* PDP context status IEI                   */
    pAddr[1] = 2;                                                               /* Length of PDP context status contents    */

    NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(pstPsBearerCtx, &ulPdpCtxStatus);
    pAddr[2] = (VOS_UINT8)ulPdpCtxStatus;
    pAddr[3] = (VOS_UINT8)(ulPdpCtxStatus >> NAS_MML_OCTET_MOVE_EIGHT_BITS);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillRoutingPtmsiIE
 ��������  : ����PTMSI IE����
 �������  : VOS_UINT8                          *pstAddr
 �������  : VOS_UINT8                          *pstAddr
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��15��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����  :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
  3.��    ��   :2014��1��14��
    ��    ��   :z00161729
    �޸�����   :DTS2014011413748:disable lteʱ����gu������ע�ᷢ��rauʱ���������ptmsi����Ч��Ӧ��Я������ptmsi��ptmsi type
  4.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������
*****************************************************************************/
VOS_UINT8  NAS_Gmm_FillRoutingPtmsiIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                          *pucPtmsiAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucNumber;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT8                          *pucMappedPtmsiAddr = VOS_NULL_PTR;

    VOS_UINT32                          ulIsSupportLteCapability;

    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;

    ucLDisabledRauUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();
#endif

    ucNumber                = GMM_MSG_LEN_TLV_PTMSI;


    /* ������ѡIE,�Լ���wģʽ��û��PTMSI IE */
    enRatType    = NAS_MML_GetCurrNetRatType();

    if (NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
    {
        ucNumber       = 0;
        return ucNumber;
    }

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr = NAS_MML_GetUeIdPtmsi();

    /* GU���ص�UE ID MASK*/
    ucUeIdMask         = NAS_GMM_GetUeIdMask();

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg    = VOS_FALSE;

    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /*4.7.5.1.1 Normal and periodic routing area updating procedure initiation
    If the MS supports S1 mode, the MS shall handle the P-TMSI  IE as follows:
    */

    /*If the TIN indicates "GUTI" and the MS holds a valid GUTI,  the MS shall map the GUTI into a P-TMSI,
    When the routing area updating procedure is initiated in Iu mode, the MS shall also include the mapped P-TMSI in the P TMSI IE.
    */

     /*If the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a
    valid P-TMSI and RAI, the MS shall indicate the RAI in the Old routing area
    identification IE. When the routing area updating procedure is initiated in Iu mode,
    the MS shall also include the P-TMSI in the P TMSI IE.
    */

    enTinType               = NAS_MML_GetTinType();
    ulGetGutiRst            = NAS_GMM_MapPtmsiFromGUTI();
    pucMappedPtmsiAddr      = NAS_GMM_GetMappedPtmsiAddr();

    ulIsSupportLteCapability = NAS_MML_IsSupportLteCapability();

    if ((VOS_TRUE == ulIsSupportLteCapability)
     || (VOS_TRUE == ucLDisabledRauUseLInfoFlag))
    {
        if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
         && (VOS_OK == ulGetGutiRst))
        {
            pucAddr[0]      = GMM_IEI_P_TMSI;
            NAS_GMM_Fill_IE_PtmsiFromSrc(&pucAddr[1], pucMappedPtmsiAddr);
        }
        else if ( ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType) || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
               && (VOS_TRUE == ulLocalPtmsiFlg) )
        {
            pucAddr[0]      = GMM_IEI_P_TMSI;
            NAS_GMM_Fill_IE_PtmsiFromSrc(&pucAddr[1], pucPtmsiAddr);
        }
        else
        {
            ucNumber       = 0;
        }

        return ucNumber;
    }
    else
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            pucAddr[0]      = GMM_IEI_P_TMSI;
            NAS_GMM_Fill_IE_PtmsiFromSrc(&pucAddr[1], pucPtmsiAddr);
        }
        else
        {
            ucNumber       = 0;
        }

        return ucNumber;
    }
#else

    if (VOS_TRUE == ulLocalPtmsiFlg)
    {
        pucAddr[0]      = GMM_IEI_P_TMSI;
        NAS_GMM_Fill_IE_PtmsiFromSrc(&pucAddr[1], pucPtmsiAddr);
    }
    else
    {
        ucNumber       = 0;
    }

    return ucNumber;

#endif

}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillRoutingPtmsiTypeIE
 ��������  : ����PTMSI TYPE IE����
 �������  : VOS_UINT8                          *pstAddr
 �������  : VOS_UINT8                          *pstAddr
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 Э������  :
             10.5.5.29   P-TMSI type
             The purpose of the P-TMSI type information element is to indicate whether the P-TMSI included in the P-TMSI information element represents a native P-TMSI or mapped P-TMSI when Type of Identity in the P-TMSI information element is "TMSI/P-TMSI/M-TMSI".
             The P-TMSI type information element information element is coded as shown in figure 10.5.5.29.1 and table 10.5.5.29.1.
             The P-TMSI type is a type 1 information element.

 �޸���ʷ      :
  1.��    ��   : 2011��4��15��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��12��
    ��    ��   : w00166186
    �޸�����   : DTS201205845812:L��G֮��������ѡ��RAU����ʧ��
  3.��    ��   :2013��8��29��
    ��    ��   :z00161729
    �޸�����   :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability,��ʹ�ô�gutiӳ���ptmsi
  4.��    ��   :2014��1��14��
    ��    ��   :z00161729
    �޸�����   :DTS2014011413748:disable lteʱ����gu������ע�ᷢ��rauʱ���������ptmsi����Ч��Ӧ��Я������ptmsi��ptmsi type
  5.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������
*****************************************************************************/
VOS_UINT8 NAS_Gmm_FillRoutingPtmsiTypeIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucNumber;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulGetGutiRst;

    VOS_UINT32                          ulIsSupportLteCapability;

    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;

    ucLDisabledRauUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();

    ucNumber                = GMM_MSG_LEN_TV_PTMSITYPE;


    /* GU���ص�UE ID MASK*/
    ucUeIdMask         = NAS_GMM_GetUeIdMask();

    /* GU���ص�PTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    ulLocalPtmsiFlg    = VOS_FALSE;

    if ( GMM_UEID_P_TMSI == ( ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }

    /*4.7.5.1.1 Normal and periodic routing area updating procedure initiation
    If the MS supports S1 mode, the MS shall handle the P-TMSI  IE as follows:
    */

    /*If the TIN indicates "GUTI" and the MS holds a valid GUTI,  the MS shall map the GUTI into a P-TMSI,
    When the routing area updating procedure is initiated in Iu mode, the MS shall also include the mapped P-TMSI in the P TMSI IE.
    */

     /*If the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a
    valid P-TMSI and RAI, the MS shall indicate the RAI in the Old routing area
    identification IE. When the routing area updating procedure is initiated in Iu mode,
    the MS shall also include the P-TMSI in the P TMSI IE.
    */

    enTinType               = NAS_MML_GetTinType();
    ulGetGutiRst            = NAS_GMM_MapPtmsiFromGUTI();

    ulIsSupportLteCapability = NAS_MML_IsSupportLteCapability();

    if ((VOS_TRUE == ulIsSupportLteCapability)
     || (VOS_TRUE == ucLDisabledRauUseLInfoFlag))
    {
        if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
         && (VOS_OK == ulGetGutiRst) )
        {
            /* ��дP-TMSI typeΪ Mapped P-TMSI*/
            pucAddr[0]       = 0x01;

            /* ��дIEIΪ E- */
            pucAddr[0]      |= GMM_IEI_P_TMSI_TYPE;
        }
        else if ( ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType) || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
               && (VOS_TRUE == ulLocalPtmsiFlg) )
        {
            /* ��дP-TMSI typeΪ Mapped P-TMSI*/
            pucAddr[0]       = 0x00;

            /* ��дIEIΪ E0 */
            pucAddr[0]      |= GMM_IEI_P_TMSI_TYPE;
        }
        else
        {
            ucNumber       = 0;
        }
    }
    else
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            pucAddr[0]       = 0x00;

            /* ��дIEIΪ E0 */
            pucAddr[0]      |= GMM_IEI_P_TMSI_TYPE;
        }
        else
        {
            ucNumber       = 0;
        }
    }

    return ucNumber;

}
#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetRoutingAreaUpdateRequestMsgIELength
 ��������  : ����IE�ĳ��ȣ���Table 9.4.14/3GPP TS 24.008: ROUTING AREA UPDATE REQUEST message content
              �ó�������Ҫ���IE����󳤶�,IE��ʵ�ʳ����к����ֶθ���
 �������  : ��
 �������  : ������Ҫ���IE����󳤶�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��15��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  3.��    ��   : 2012��3��24��
    ��    ��   : z40661
    �޸�����   : DTS2012032004429 MS networkcapablity������ˢ��
  4.��    ��   : 2012��2��15��
    ��    ��   : w00167002
    �޸�����   : ���ӳ���GMM_MSG_LEN_TLV_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING_LEN
  5.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
  6.��    ��   : 2013��02��18��
    ��    ��   : l65478
    �޸�����   : DTS2013021700426:LTE disableʱ���ϱ���UE CAPABILITY��Ϣ
  7.��    ��   : 2014��10��9��
    ��    ��   : b00269685
    �޸�����   : ֧��srvccʱ��ҪЯ��classmark2,classmark3, supported codec list
  8.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�,�����ֵ�����ڴ�
*****************************************************************************/
VOS_UINT32  NAS_GMM_GetRoutingAreaUpdateRequestMsgIELength( VOS_VOID )
{
    VOS_UINT32                          ulMsgLen;

    /* Protocol discriminator �� Skip indicator IE ����1�ֽ� */
    ulMsgLen = 1;

    /* Routing area update request message identity IE����1�ֽ� */
    ulMsgLen += 1;

    /* Update type ��GPRS ciphering key sequence number IE����1�ֽ� */
    ulMsgLen += 1;

    /* Old routing area identification IE����6�ֽ� */
    ulMsgLen += 6;

    /* �̶�IE: MS Radio Access capability IE 6-51�ֽ�*/
    ulMsgLen += 51;

    /* Old P-TMSI signature IE */
    ulMsgLen += 4;

    /* Requested READY timer value IE */
    ulMsgLen += 2;

    /* Modified by t00212959 for DCM�����������������, 2012-8-18, begin */
    /* DRX parameter IE */
    /* �����ѡIE ,���ڲ�������Զ���ڵģ���LTE Attach/TAU δЯ����DRX ����ʱ��RAU��Я��*/
    ulMsgLen += 3;

    /* Modified by t00212959 for DCM�����������������, 2012-8-18, end */


    /* TMSI status IE */
    ulMsgLen += 1;

    /*R99��ǰ�汾��P-TMSI(��)��������ѡIE*/
    /* P-TMSI IE */
    ulMsgLen += 7;

    /* ��ѡIE: MS Network Capability IE ,4-10�ֽ� */
    ulMsgLen += 10;

    /* ��ѡIE: PDP Context status IE */
    ulMsgLen += 4;

    /* PS LCS Capability IE ����3�ֽ� */
    ulMsgLen += 3;

    /* MBMS context status ����2-18�ֽ� */
    ulMsgLen += 18;

    /* Additional mobile identity IE */
    ulMsgLen += 7;

    /* Additional old routing area identification IE */
    ulMsgLen += 8;

    /* P-TMSI type */
    ulMsgLen += 1;

    /* Device properties IE����1�ֽ� */
    ulMsgLen += 1;

    /* classmark2  */
    ulMsgLen += 5;

    /* classmark3  */
    ulMsgLen += 34;

    /* supported codec list  */
    ulMsgLen += 10;

    /* UE network capability IE 4-15�ֽ� */
    ulMsgLen += 15;
    /* ˵�����UE֧��E-UTRAN������֧��CS fallback and SMS over SGs��
        ��ATTACH��RAU������Ϣ����Ҫ��Voice domain preference and UE's usage setting IE�� */

    /* ��дVoice domain preference and UE's usage setting IE��,����Ϊ3 */
    ulMsgLen += GMM_MSG_LEN_TLV_VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING_LEN;

    /* MS network feature support IE */
    ulMsgLen += 1;

    /* Old location area identification IE ����7�ֽ�*/
    ulMsgLen += 7;

    /* Additional update type ����1�ֽ� */
    ulMsgLen += 1;

    /* TMSI based NRI container IE ����4�ֽ� */
    ulMsgLen += 4;

    /* T3324 value IE����3�ֽ� */
    ulMsgLen += 3;

    /* T3312 extended value IE����3�ֽ� */
    ulMsgLen += 3;

    return ulMsgLen;

}

/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateRequestMsgMake
  Function : RAU Request��Ϣ����
  Input    : VOS_UINT8 ucRauType     RAU������
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *pRauRequest    ָ��NAS_MSG_STRU�ṹ��ָ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��  : 2007��12��21��
      ��    ��  : l00107747
      �޸�����  : ���ⵥ��:A32D13951
    3.��    ��  : 2009��06��17��
      ��    ��  : ouyangfei, o00132663
      �޸�����  : �����ն˿����������޸ģ�R99��ǰ�汾��P-TMSI(��)��������ѡIE
    4.��    ��   : 2009��08��14��
      ��    ��   : ouyangfei o00132663
      �޸�����   : AT2D13748:��ȡ3GPPЭ��汾��������������Ӧ�ò�ѯPS��汾��
    5.��    ��   : 2010��11��29��
      ��    ��   : z00161729
      �޸�����  : ���ⵥ��:DTS2010112900029:W��RAU������Ǩ��ʧ�ܣ��������DSCR,UE����פ��������RAU������������������RAU
    6.��    ��   : 2011��8��8��
      ��    ��   : luokaihui / 00167671
      �޸�����   : ���ⵥ��DTS2011080200129, PDP Context����û������
    7.��    ��   : 2011��10��27��
      ��    ��   : s46746
      �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��
    8.��    ��   : 2012��02��16��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�DTS2012021304254��GCF����ʱ�ϱ���REL9���Ժ��IE����ʧ��
    9.��    ��   : 2012��2��15��
      ��    ��   : w00167002
      �޸�����   : ���ӿ�ѡIE�����:VOICE_DOMAIN_PREFERANCE_AND_UE_USAGE_SETTING
              TS24008 9.4.1.11 Voice domain preference and UE's usage setting
                This IE shall be included:
                  if the MS supports CS fallback and SMS over SGs, or the MS is configured to support IMS voice, or both; and
                  if the MS is E-UTRAN capable.
    9.��    ��   : 2012��5��15��
      ��    ��   : l00130025
      �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��
   11.��    ��   : 2012��8��13��
      ��    ��   : t00212959
      �޸�����   : DCM�����������������
   12.��    ��   : 2012��8��15��
      ��    ��   : z00161729
      �޸�����   : DCM������������������޸�
   13.��    ��   : 2012��10��20��
      ��    ��   : t00212959
      �޸�����   : DTS2012101805471,IE��Voice domain preference and UE's usage setting ��UE֧��Lģʱ����ҪЯ��
   14.��    ��   : 2012��12��28��
      ��    ��   : s46746
      �޸�����   : DSDA GUNAS C CORE��Ŀ�����·�װLMM�ṩ�Ľӿں���
   15.��    ��   : 2013��02��18��
      ��    ��   : l65478
      �޸�����   : DTS2013021700426:LTE disableʱ���ϱ���UE CAPABILITY��Ϣ

   16.��    ��   : 2013��7��8��
      ��    ��   : w00167002
      �޸�����   : DTS2013070506409:fortify�������
   17.��    ��   :2013��8��29��
      ��    ��   :z00161729
      �޸�����   :DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
   18.��    ��   :2013��8��29��
      ��    ��   :l65478
      �޸�����   :DTS2013100802302:��L�л���W����RAUʱû������follow on��־
   19.��    ��   : 2014��10��9��
      ��    ��   : b00269685
      �޸�����   : ֧��srvccʱ��ҪЯ��classmark2,classmark3,supported codec list
   20.��    ��   : 2015��2��12��
      ��    ��   : s00217060
      �޸�����   : VOLTE SWITCH�޸�:voice domain�����仯ʱ��Ҫ��RAU
   21.��    ��   : 2015��6��8��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
   22.��    ��   : 2015��8��13��
      ��    ��   : l00289540
      �޸�����   : User_Exp_Improve�޸�
  22.��    ��   : 2016��1��20��
     ��    ��   : c00318887
     �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*******************************************************************************/
NAS_MSG_STRU *Gmm_RoutingAreaUpdateRequestMsgMake(
    VOS_UINT8                           ucRauType                               /* RAU������                                */
)
{
    VOS_INT8                            cVersion;
    NAS_MSG_STRU                       *pRauRequest;
    VOS_UINT8                           ucNumber;                                /* ��дIEʱ��������                         */
    VOS_UINT32                          ulMsgLen;                                /* �� MS Radio Access capability IE��Ĺ̶�IE ���� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_LMM_INFO_STRU                   stLmmInfo;
#endif
    VOS_UINT32                          ulDataAvailFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulIsLteCapabilityDisabled;

#endif
    ulDataAvailFlg = CDS_IsPsDataAvail();

    ucNumber         = 0;

    /* ȡ�����IE����Ҫ�ĳ��� */
    ulMsgLen = NAS_GMM_GetRoutingAreaUpdateRequestMsgIELength();

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    if (VOS_TRUE == NAS_GMM_IsCombinedSpecProc())
    {
        NAS_GMM_SetSpecProcInCsTrans(GMM_NULL_PROCEDURE);
    }

    /* Ŀǰ�Ĵ������������仯�󲻻����RAU */
    pRauRequest =
            (NAS_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_GMM, (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);

    if (VOS_NULL_PTR == pRauRequest)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_RoutingAreaUpdateRequestMsgMake:ERROR: MALLOC FAIL!");
        return pRauRequest;                                                     /* ����                                     */
    }
    PS_MEM_SET(pRauRequest, 0, (sizeof(NAS_MSG_STRU ) + ulMsgLen) - 4);        /* �ڴ�ռ���0                              */

    pRauRequest->ulNasMsgSize = ulMsgLen;
    pRauRequest->aucNasMsg[0] = GMM_PD_GMM;
    pRauRequest->aucNasMsg[1] = GMM_MSG_RAU_REQUEST;
    ucNumber += 2;

    pRauRequest->aucNasMsg[ucNumber] = ucRauType;                               /* update type                              */

    /* ��ȡ�ϲ��Ƿ���ڻ�������,���ϲ���ڻ��������ʱ,������Ҫ����PS_TRUE��־ */
    if (VOS_TRUE == NAS_GMM_IsFollowOnPend())
    {
        pRauRequest->aucNasMsg[ucNumber] |= GMM_FOLLOW_ON_REQ_PENDING;          /* follow on                                */
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
         &&  (PS_TRUE  == ulDataAvailFlg))
    {
        pRauRequest->aucNasMsg[ucNumber] |= GMM_FOLLOW_ON_REQ_PENDING;          /* follow on                                */
    }
    else
    {
    }

    if (VOS_TRUE == NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth())
    {
        NAS_MML_SetSimPsSecurityCksn(MM_CKSN_INVALID);

        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);        
    }
    
    pRauRequest->aucNasMsg[ucNumber]     |= ((NAS_MML_GetSimPsSecurityCksn()<< 4) & 0xF0);  /* CKSN                                     */
    ucNumber += 1;

    /* ��д RAI IE */
    ucNumber += NAS_Gmm_FillRaiForSnd(&pRauRequest->aucNasMsg[ucNumber]);       /* ��дRAI                                  */

    /* ���߽���������д */
    /* Modified by z00161729 for DCM�����������������, 2012-8-17, begin */
#if (FEATURE_ON == FEATURE_LTE)
     g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq = g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs;
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-17, end */

    ucNumber += Gmm_Fill_IE_RadioAccessCapability(&pRauRequest->aucNasMsg[ucNumber]);

    /* ��д P-TMSI Signature IE */
    ucNumber += NAS_Gmm_FillPtmsiSignatureIeForSnd(&pRauRequest->aucNasMsg[ucNumber]);

    GMM_FillReadyTimerParaIe(&pRauRequest->aucNasMsg[ucNumber]);
    ucNumber += 2;

    /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */
    g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_GU_PS_REG_NOT_CONTAIN_DRX_PARA;

    if (NAS_MML_LTE_PS_REG_CONTAIN_DRX_PARA != NAS_MML_GetPsRegContainDrx())
    {

        /* ��дDRX���� */
        /*lint -e961*/
        pRauRequest->aucNasMsg[ucNumber++] = GMM_IEI_DRX_PARAMETER;             /* [false alarm]: �����Ѷ�̬����*/
        /*lint +e961*/

        Gmm_FillDrxPara(&pRauRequest->aucNasMsg[ucNumber]);
        ucNumber += 2;                                                      /* DRX��������Ϊ2                           */

        g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA;
    }
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */

    if (VOS_TRUE == NAS_GMM_IsRegNeedFillTmsiStatusIE())
    {                                                                           /* TMSI status                              */

        /* ��дTMSI status */
        pRauRequest->aucNasMsg[ucNumber] = GMM_IEI_TMSI_STATUS_NO_VALID;        /* [false alarm]: �����Ѷ�̬���� */
        ucNumber += 1;                                                          /* DRX��������Ϊ3                           */
    }

    /* R99��ǰ�汾��P-TMSI(��)��������ѡIE*/
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        ucNumber += NAS_Gmm_FillRoutingPtmsiIE(&pRauRequest->aucNasMsg[ucNumber]);

        /*��д��������
 */
        pRauRequest->aucNasMsg[ucNumber] = GMM_IEI_MS_NETWORK_CAPABILITY;
        ucNumber += 1;
        ucNumber += Gmm_Fill_IE_NetworkCapability(&pRauRequest->aucNasMsg[ucNumber]);

        Gmm_FillPdpContext(&pRauRequest->aucNasMsg[ucNumber]);                     /* ��дPDP context capability               */


        ucNumber += 4;


#if (FEATURE_ON == FEATURE_LTE)
        if (cVersion >= PS_PTL_VER_R9)
        {
            /* An MS supporting S1 mode shall include this IE, unless the update type indicates "periodic update" */
            if ((VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
             && (GMM_PERIODC_UPDATING != ucRauType))
            {
                /* ��дUE network Capacility */
                ulIsLteCapabilityDisabled = NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(),
                                                                    NAS_MML_GetDisableLteRoamFlg());

                /* Lδ��disabled */
                if (VOS_FALSE == ulIsLteCapabilityDisabled)
                {
                    ucNumber += NAS_GMM_Fill_IE_UeNetwrokCapacity(&pRauRequest->aucNasMsg[ucNumber]);
                }


                /* ��дAdditional mobile identity */
                ucNumber += NAS_Gmm_Fill_IE_AdditionalMobileIdentity(&pRauRequest->aucNasMsg[ucNumber]);

                /* ��дAdditional old routing area identification */
                ucNumber += NAS_Gmm_Fill_IE_AdditionalOldRAI(&pRauRequest->aucNasMsg[ucNumber]);

            }

            if (VOS_TRUE == NAS_MML_GetSupportSrvccFlg())
            {
                /* ��дclassmark2 */
                GMM_Fill_IE_ClassMark2(&pRauRequest->aucNasMsg[ucNumber]);
                ucNumber += GMM_MSG_LEN_CLASSMARK2;

                /* ��дclassmark3 */
                if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
                {
                    ucNumber += GMM_Fill_IE_FDD_ClassMark3(&pRauRequest->aucNasMsg[ucNumber]);
                }
                else if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
                {
                    ucNumber += GMM_Fill_IE_TDD_ClassMark3(&pRauRequest->aucNasMsg[ucNumber]);
                }
                else
                {
                }

                /* ��дsupport code list */
                ucNumber += GMM_CALL_FillIeSupCodecList(&pRauRequest->aucNasMsg[ucNumber]);

            }



            if (VOS_TRUE == NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE())
            {
                /* ��дVoice domain preference and UE's usage setting IE��,����Ϊ3 */
                ucNumber += NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting(&pRauRequest->aucNasMsg[ucNumber]);
            }

            /* ��дP-TMSI type */
            ucNumber += NAS_Gmm_FillRoutingPtmsiTypeIE(&pRauRequest->aucNasMsg[ucNumber]);

            /* �����ά�ɲ���Ϣ */
            if ( VOS_TRUE == NAS_GMM_GetLteInfo(NAS_LMM_GUTI, &stLmmInfo))
            {
                NAS_GMM_LogGutiInfo(&(stLmmInfo.u.stGuti));
            }
        }

#endif

        /* ��дMS network feature support IE */
        if (PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
        {
            ucNumber += NAS_GMM_FillMsNetworkFeatureSupportIE(&pRauRequest->aucNasMsg[ucNumber]);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* ��дOld location area identification IE */
        if (VOS_TRUE == NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE())
        {
            ucNumber += NAS_GMM_FillOldLocationAreaIdentificationIE(&pRauRequest->aucNasMsg[ucNumber]);
        }
#endif

        /* ��д TMSI based NRI container IE*/
        if (VOS_TRUE == NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE())
        {
            ucNumber += NAS_GMM_FillTmsiBasedNRIContainerIE(&pRauRequest->aucNasMsg[ucNumber]);
        }

    }

    g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq  = NAS_MML_GetVoiceDomainPreference();

    /* ��д�տ���Ϣ����*/
    pRauRequest->ulNasMsgSize = ucNumber;

    /* ����RAU���̣�����GMM��·�ͷſ��Ʊ��� */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    NAS_GMM_SetRetryRauForRelCtrlFlg(VOS_FALSE);

    return (NAS_MSG_STRU *)pRauRequest;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetRauComPleteMsgLen
 ��������  : ��ȡRAU COMPLETE��Ϣ�ĳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : RAU COMPLETE��Ϣ�ĳ���
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
VOS_UINT16 NAS_GMM_GetRauComPleteMsgLen()
{
    VOS_UINT16                          usMsgLen;
    VOS_UINT8                           ucInterRatInfoFlag;

#if (FEATURE_ON == FEATURE_LTE)
        VOS_UINT16              ucEUeCapDataLen = 0;
        VOS_UINT8               aucEUeCapData[LTE_NAS_INTER_RAT_UETRAN_CAP_LEN];
        MMC_LMM_PLMN_ID_STRU    stLmmPlmn;
        VOS_UINT8               ucEUtranInterRatInfoFlag = VOS_FALSE;


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

    if ((VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
      && (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg)
      && (0 != g_GmmInterRatInfoCtrl.ucDataLen))
    {
        ucInterRatInfoFlag = VOS_TRUE;
    }
    else
    {
        ucInterRatInfoFlag = VOS_FALSE;
    }

    usMsgLen = sizeof(NAS_MSG_STRU) + g_GmmRauCtrl.ucNpduCnt;

    /* ����UTRAN INTER RAT INFOMATION */
    if (VOS_TRUE == ucInterRatInfoFlag)
    {
        usMsgLen += 2 + g_GmmInterRatInfoCtrl.ucDataLen;
    }

    /* ����E-UTRAN INTER RAT INFORMATION */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == ucEUtranInterRatInfoFlag)
    {
        usMsgLen += 2 + ucEUeCapDataLen;
    }
#endif

    return  usMsgLen;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RoutingAreaUpdateHandle_Handling_REQUESTED_MS_INFORMATION_IE
 ��������  : ����RAU��Ϣ�е�REQUESTED MS INFORMATION IE
 �������  : pMsg
             pRauAcceptIe
 �������  : pucSndCompleteFlg ����complete��־
             pucInterRatInfoFlg ��ȡINTER RAT INFO ��־

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��12��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��26��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�������
 3.��    ��   : 2015��6��9��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_RoutingAreaUpdateHandle_Handling_REQUESTED_MS_INFORMATION_IE(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU               *pRauAcceptIe,
    VOS_UINT8                          *pucSndCompleteFlg,
    VOS_UINT8                          *pucInterRatInfoFlg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList;
    VOS_UINT32                          ulSurpportLteFlag;

    pstRatList        = NAS_MML_GetMsPrioRatList();
    ulSurpportLteFlag = NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE);

    if ( (( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_WCDMA))
        || ( VOS_TRUE == ulSurpportLteFlag))
      && ( pstRatList->ucRatNum > 1))
    {
        if (GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG
            != (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG))
        {
            /* ��Ϣ�в����� IE:Requested MS informationֱ�ӷ���   */
            return;
        }

        g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg = VOS_FALSE;

        /* ƽ̨֧��UTRAN */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
        {
            if (0x08 == (0x08 & (pMsg->aucNasMsg
                    [pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION]])))
            {                                                                   /* ��Ϣ��ָʾ Inter RAT information container IE requested */
                *pucSndCompleteFlg = GMM_TRUE;                                  /* �趨��Ҫ����RAU COMPLETE��Ϣ             */
                *pucInterRatInfoFlg = GMM_TRUE;
            }
        }

#if   (FEATURE_ON == FEATURE_LTE)
        /* ƽ̨֧��LTE */
        if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
        {
            if (0x04 == (0x04 & (pMsg->aucNasMsg
                    [pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION]])))
            {
                *pucSndCompleteFlg = GMM_TRUE;                                    /* �趨��Ҫ����RAU COMPLETE��Ϣ             */
                g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag = VOS_TRUE;
            }
        }
#endif
    }
}


/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateCompleteMsgMake
  Function : RAU Complete��Ϣ����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *pRauComplete    ָ��NAS_MSG_STRU�ṹ��ָ��
  History  :
  1. ��־��  2003.12.10  �¹�����

  2.��    ��   : 2010��3��17��
    ��    ��   : o00132663
    �޸�����   : NAS R7Э��������InterRatInfo IEͨ����Ϣ�ӿڻ�ȡ
  3.��    ��   : 2011��01��27��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011012501578�����RAU ACCEPT��Ϣ�в�Я��IE��NPDU NUMBER LIST��
                 ��RAU COMPLETE��Ϣ�в���ҪЯ��IE��NPDU NUMBER LIST
 2. ��    ��   : 2012��05��13��
    ��    ��   : W00166186
    �޸�����   : DTS201204261955,RAU COMPLETEû�лظ�
 3. ��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
*******************************************************************************/
NAS_MSG_STRU *Gmm_RoutingAreaUpdateCompleteMsgMake(VOS_VOID)
{
    NAS_MSG_STRU    *pRauComplete = VOS_NULL_PTR;
    VOS_UINT16      usMsgLen;
    VOS_UINT16      usIeOffset    = GMM_MSG_LEN_RAU_COMPLETE;
    VOS_BOOL        bInterRatInfoFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT16              usEUeCapDataLen     = 0;
    VOS_UINT8               aucEUeCapData[LTE_NAS_INTER_RAT_UETRAN_CAP_LEN]  = {0};
    MMC_LMM_PLMN_ID_STRU    stLmmPlmn;
#endif

    if ( (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
      && (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg)
      && (0 != g_GmmInterRatInfoCtrl.ucDataLen))
    {
        bInterRatInfoFlg = VOS_TRUE;
    }
    else
    {
        bInterRatInfoFlg = VOS_FALSE;
    }

    usMsgLen = NAS_GMM_GetRauComPleteMsgLen();

    pRauComplete = (NAS_MSG_STRU *)Gmm_MemMalloc(usMsgLen);                     /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pRauComplete)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_RoutingAreaUpdateCompleteMsgMake:ERROR: MemMalloc Failed.");
        return pRauComplete;
    }
    Gmm_MemSet(pRauComplete, 0, usMsgLen);                                      /* �ڴ�ռ���0                              */

    pRauComplete->ulNasMsgSize = GMM_MSG_LEN_RAU_COMPLETE;                      /* ��д��Ϣ��С                             */
    pRauComplete->aucNasMsg[0] = GMM_PD_GMM;                                    /* ��дProtocol discriminator               */
    pRauComplete->aucNasMsg[1] = GMM_MSG_RAU_COMPLETE;                          /* ��дRAU complete message identity        */
    /*lint -e961*/
    if (VOS_TRUE == g_GmmRauCtrl.bNpduPresentInRauAccFlg)
    {                                                                           /* ��N-PDU NUMBER                           */
        pRauComplete->ulNasMsgSize              = 4 + g_GmmRauCtrl.ucNpduCnt;
        pRauComplete->aucNasMsg[usIeOffset++]   = GMM_IEI_LIST_OF_RECEIVE_N_PDU_NUMBERS;
        pRauComplete->aucNasMsg[usIeOffset++]   = g_GmmRauCtrl.ucNpduCnt;
        Gmm_MemCpy(&pRauComplete->aucNasMsg[usIeOffset],
                   &g_GmmRauCtrl.aucNpduNum[0], g_GmmRauCtrl.ucNpduCnt);
        usIeOffset += g_GmmRauCtrl.ucNpduCnt;
    }

    if (VOS_TRUE == bInterRatInfoFlg)
    {
        pRauComplete->ulNasMsgSize             += 2 + g_GmmInterRatInfoCtrl.ucDataLen;
        pRauComplete->aucNasMsg[usIeOffset++]   = GMM_IEI_INTER_RAT_HANDOVER_INFORMATION;  /* [false alarm]: �����Ѷ�̬���� */
        pRauComplete->aucNasMsg[usIeOffset++]   = g_GmmInterRatInfoCtrl.ucDataLen;         /* [false alarm]: �����Ѷ�̬���� */
        Gmm_MemCpy(&(pRauComplete->aucNasMsg[usIeOffset]),
                   g_GmmInterRatInfoCtrl.aucData, g_GmmInterRatInfoCtrl.ucDataLen);
        usIeOffset += g_GmmInterRatInfoCtrl.ucDataLen;

    }
    /*lint +e961*/
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag)
    {

        PS_MEM_SET(&stLmmPlmn, 0x00, sizeof(stLmmPlmn));

        NAS_MML_ConvertNasPlmnToLMMFormat(&stLmmPlmn,NAS_MML_GetCurrCampPlmnId());

        usEUeCapDataLen = LTE_NAS_INTER_RAT_UETRAN_CAP_LEN;
        if (MMC_LMM_SUCC != Nas_GetEutraUeCap(stLmmPlmn, &usEUeCapDataLen, aucEUeCapData))
        {
            usEUeCapDataLen = 0;
        }
    }
    /*lint -e961*/
    if ((VOS_TRUE == g_GmmInterRatInfoCtrl.ucEutranInterRatInfoRequestedFlag)
     && (0 != usEUeCapDataLen))
    {
        pRauComplete->ulNasMsgSize             += 2 + usEUeCapDataLen;
        pRauComplete->aucNasMsg[usIeOffset++]   = GMM_IEI_E_UTRAN_INTER_RAT_HANDOVER_INFORMATION;
        pRauComplete->aucNasMsg[usIeOffset++]   = (VOS_UINT8)usEUeCapDataLen;
        Gmm_MemCpy(&(pRauComplete->aucNasMsg[usIeOffset]),
                   aucEUeCapData, usEUeCapDataLen);
    }
    /*lint +e961*/
#endif

    /* ȫ�ֱ�����λ */
    Gmm_MemSet(&g_GmmInterRatInfoCtrl, 0, sizeof(GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU));

    return pRauComplete;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateRejectCause13
  Function : �տ���ϢRAU REJECTԭ��ֵΪ#13,#15�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����

*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateRejectCause13(VOS_BOOL   bUpdateSimFlg)
{
    if (VOS_TRUE == bUpdateSimFlg)
    {
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                              /* ����״̬�Ĺ�������                       */
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;
    g_GmmRauCtrl.ucRauAttmptCnt = 0;                                            /* RAU attempt counter��0                   */

    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateRejectCause11
  Function : �տ���ϢRAU REJECTԭ��ֵΪ#11,#12,#14�Ĵ���
  Input    : VOS_UINT32 ulGmmCause   ʧ��ԭ��ֵ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    4.��    ��   : 2009��01��14��
      ��    ��   : l65478
      �޸�����   : ���ⵥ�ţ�AT2D07971,������״̬���ϱ��Ľ��뼼������
    5. ��    ��   : 2009��2��18��
       ��    ��   : h44270
       �޸�����  : ���ⵥ��:AT2D08904,���ⳡ����-HK��D̬�����󣬷����������˺ܳ�ʱ�䣬�����ѵ�С����PS��ע��ʧ�ܣ�ȥ����PDP��Ȼע��ʧ��
    6.��    ��   : 2011��10��8��
      ��    ��   : s46746
      �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��
    7.��    ��   : 2015��6��3��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateRejectCause11(
                                        VOS_UINT32 ulGmmCause,                 /* ʧ��ԭ��ֵ                               */
                                        VOS_BOOL   bUpdateSimFlg
                                        )
{
    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == ulGmmCause)
    {
        g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
    }

    /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.5.1.4�½���������:
    #11/#14:The MS shall delete any RAI, P-TMSI, P-TMSI signature and GPRS ciphering
    key sequence number, shall set the GPRS update status to GU3 ROAMING NOT ALLOWED
    (and shall store it according to subclause 4.1.3.2), shall reset the routing area
    updating attempt counter and enter the state GMM-DEREGISTERED*/

    g_GmmRauCtrl.ucRauAttmptCnt = 0;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateRejectCause11:INFO: PLMN not allowed");

    if (VOS_TRUE == bUpdateSimFlg)
    {
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* ����״̬��ΪGU3                          */
        Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOCATION INFO             */
    }

    if ((VOS_FALSE == bUpdateSimFlg)
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
    }

    if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == ulGmmCause)
    {                                                                           /* ԭ��ֵ#12                                */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
    }
    else if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == ulGmmCause)
    {                                                                           /* ԭ��ֵ#11                                */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;

        NAS_GMM_DeleteEPlmnList();
    }
    else
    {
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN_FOR_GPRS;
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateRejectCause9
  Function : �տ���ϢRAU REJECTԭ��ֵΪ#9,#10�Ĵ���
  Input    : VOS_UINT32 ulGmmCause   ʧ��ԭ��ֵ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    2.��    ��   : 2011��02��12��
      ��    ��   : c00173809
      �޸�����   : ���ⵥ�ţ�DTS2011021100487,
                 ��LAU����,RAUҲ����(ԭ��ֵ9��10)�������,���岻�������ϱ�ERROR.
    3.��    ��   : 2011��03��08��
      ��    ��   : z00161729
      �޸�����   : ���ⵥ��DTS2011030102593:W��rau����ԭ��ֵ9��10����attachʧ�ܶ�����
                    G����attach֮ǰδȥָ��TLLI���²������������Ϣ��
    4.��    ��   : 2011��08��02��
      ��    ��   : f00179208
      �޸�����   : ���ⵥ��:DTS2011080200067,��ɳ���ⳡ���ֶ��б�������ѡ����������ע��ʧ�ܣ��Ļ��Զ�ģʽ����HPLMN
                   ע�ᣬ����CSע�ᣬPS�쳣������ʧ��
    5.��    ��   : 2012��3��21��
      ��    ��   : z40661
      �޸�����   : DTS2011110201060:L��ѡ��W��������ܾ�#9��Я����PTMSI����ȷ
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateRejectCause9(
    VOS_UINT32                              ulGmmCause,
    VOS_UINT8                              *pucAttachFlg
)
{
    *pucAttachFlg = GMM_TRUE;

    if (NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED == ulGmmCause)
    {                                                                           /* ԭ��ֵ#9                                 */
        if (GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
        {
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* ����״̬��ΪGU2                          */
            if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
            {
                Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);
            }
            Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOCATION INFO             */
        }
        else
        {
            /* �����FORBINDDEN�б��У�����Attach */
            *pucAttachFlg = GMM_FALSE;
        }
    }
    else
    {
        /* W��rau����ԭ��ֵ10�����Ҳ��ȥָ��TLLI */
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }

        if (GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask)
        {
            /* �����FORBINDDEN�б��У�����Attach */
            *pucAttachFlg = GMM_FALSE;
        }

#if (FEATURE_ON == FEATURE_LTE)
        if ( NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
        {
            NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
            NAS_MML_InitPsSecurityUmtsCkInvalid();
            NAS_MML_InitPsSecurityUmtsIkInvalid();
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);
            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DEL_KEY);
        }

#endif

    }
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE == *pucAttachFlg)
    {
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
    }
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
    g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;

    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateRejectCause3
  Function : �տ���ϢRAU REJECTԭ��ֵΪ#3,#6,#7,#8�Ĵ���
  Input    : VOS_UINT32 ulGmmCause   ʧ��ԭ��ֵ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����
    2.��    ��   : 2011��10��8��
      ��    ��   : s46746
      �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��

*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateRejectCause3(
                                       VOS_UINT32 ulGmmCause                    /* ʧ��ԭ��ֵ                               */
                                       )
{
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    Gmm_DelPsLocInfoUpdateUsim();                                               /* ���ú���ɾ��PS LOCATION INFO             */
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* ����״̬�Ĺ�������                       */

    /* �����ر�־ */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_DeleteEPlmnList();

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvRoutingAreaUpdateRejectMsg_T3302_Handling
 *  FUNCTION : Gmm_RcvRoutingAreaUpdateRejectMsg���������Ӷ�: T3302�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
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
 ************************************************************************/
VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_T3302_Handling(
                                       NAS_MSG_FOR_PCLINT_STRU *pMsg
                                       )
{
    NAS_MSG_STRU   *pGmmStatus;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    if (GMM_MSG_LEN_RAU_REJECT < pMsg->ulNasMsgSize)
    {                                                                           /* ��Ϣ�к���OP��                           */
        /* 24.008: 9.4.17.1
          In Iu mode, the MS shall ignore the contents of this IE if this message is received
          without integrity protection.
          If this IE is not included or if in Iu mode the message is not integrity protected,
          the MS shall use the default value.  */
        if (GMM_IEI_T3302_VALUE == pMsg->aucNasMsg[GMM_MSG_LEN_RAU_REJECT])
        {                                                                       /* ��Ϣ�к���T3302 value                    */
            if (((GMM_MSG_LEN_RAU_REJECT + 1) == pMsg->ulNasMsgSize)
                || ((GMM_MSG_LEN_RAU_REJECT + 2) == pMsg->ulNasMsgSize))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateRejectMsg:WARNING: T3302 of RAU REJECT is omitted");
            }
            else
            {
                if (1 != pMsg->aucNasMsg[GMM_MSG_LEN_RAU_REJECT + 1])
                {
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateRejectMsg:WARNING: RAU REJECT is semantically incorrect(IE:T3302)");
                    pGmmStatus = Gmm_GmmStatusMsgMake(
                                      NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

                    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                    return;
                }


                /* TDD/FDD��Ҫ�����Ա���,��û�յ�SMC����ʹ��Ĭ��ֵ */
                if ( (VOS_TRUE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())
                  && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE != g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) )
                {                                                               /* If in Iu mode the message is not integrity protected, the MS shall use the default value */
                    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
                }
                else
                {
                    Gmm_SaveTimerValue(GMM_TIMER_T3302,
                                   pMsg->aucNasMsg[GMM_MSG_LEN_RAU_REJECT + 2]);/* �洢T3302ʱ��                            */

                    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(),sizeof(stPlmnWithRat.stPlmnId));
                    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

                    NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);
                }
            }
        }

        else
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }
    }

    else
    {                                                                           /* If this IE is not included , the MS shall use the default value */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvRoutingAreaUpdateRejectMsg_Default_Cause_Handling
 *  FUNCTION : Gmm_RcvRoutingAreaUpdateRejectMsg���������Ӷ�: Default Rej Cause�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����

  1.��    ��   : 2010��11��18��
    ��    ��   : zhoujun /40661
    �޸�����   : ���ⵥDTS2010111601893,�յ��ܾ�ԭ��ֵΪ102-110��
                 ����Ӧ�ú�ԭ��ֵ111�Ĵ���һ��
   2.��    ��   : 2011��12��12��
     ��    ��   : luokaihui /l00167671
     �޸�����   : ���ⵥDTS201111303439, L2G ��ѡRAU����111,δ����T3302��ɾ��EPLMN
   3.��    ��   : 2011��2��11��
     ��    ��   : w00176964
     �޸�����   : DTS2012021003156:GMMע�ᱻ��ԭ��ֵΪ4ʱ��������Э�鲻һ�£�����
                  ��Чattach��RAU����

  ************************************************************************/
 VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_Default_Cause_Handling(
                                                 NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                 VOS_UINT8       *pucAbnormalCaseFlg)
 {
    /* 3GPP 24.008, 4.7.3.1.5 Abnormal cases in the MS
      d)ATTACH REJECT, other causes than those treated in subclause 4.7.3.1.4
      Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the
      MS should set the GPRS attach attempt counter to 5.

      Gmm Combined RAU has similiar handling. */

    /*  3GPP 24.008 10.5.5.14 GMM cause
        Any other value received by the mobile station shall be treated as 0110 1111,
        "Protocol error, unspecified". Any other value received by the network shall
        be treated as 0110 1111, "Protocol error, unspecified".*/

#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
    if ((NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == pMsg->aucNasMsg[2])
     || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF == pMsg->aucNasMsg[2])
     || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == pMsg->aucNasMsg[2])
     || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == pMsg->aucNasMsg[2])
    /* ����24008Э�飬���Ӷ�GMM��©��ԭ��ֵ���� */
     || (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR == pMsg->aucNasMsg[2])
     || (NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_NOT_AVAILABLE == pMsg->aucNasMsg[2])
     || (NAS_MML_REG_FAIL_CAUSE_ESM_FAILURE == pMsg->aucNasMsg[2])
     || ((pMsg->aucNasMsg[2] >= NAS_MML_REG_FAIL_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG )
      && (pMsg->aucNasMsg[2] <= NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE))
     || ((pMsg->aucNasMsg[2] > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
      && (pMsg->aucNasMsg[2] <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) ))
    {
        g_GmmRauCtrl.ucRauAttmptCnt = 5;
    }
#endif
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateRejectMsg:WARNING: GMM cause is Abnormal");
    if ((NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN    <= pMsg->aucNasMsg[2])
        && (NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX >= pMsg->aucNasMsg[2]))
    {
        g_GmmRauCtrl.ucRetryFlg = GMM_TRUE;                                 /* �û�С������RAU��־                      */
    }
    else
    {
        g_GmmRauCtrl.ucRetryFlg = GMM_FALSE;                                /* �����С������RAU��־                    */
    }

    if (VOS_TRUE == NAS_MML_IsRoamingRejectNoRetryFlgActived(pMsg->aucNasMsg[2]))
    {
        g_GmmRauCtrl.ucRauAttmptCnt = 5;
    }

    Gmm_RoutingAreaUpdateAttemptCounter(pMsg->aucNasMsg[2]);                /* �����쳣������                         */
    *pucAbnormalCaseFlg = GMM_TRUE;

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvRoutingAreaUpdateRejectMsg_Cause_Handling
 *  FUNCTION : Gmm_RcvRoutingAreaUpdateRejectMsg���������Ӷ�: Rej Cause�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����       2009.06.11  �°�����
 2.��    ��   : 2010��01��03��
   ��    ��   : o00132663
   �޸�����   : ���ⵥ�ţ�xxxx,NAS R7Э��������������PS ���������ͷŶ�ʱ��T3340
 3.��    ��   : 2011��7��14��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
 4.��    ��   : 2011��08��02��
   ��    ��   : f00179208
   �޸�����   : ���ⵥ��:DTS2011080200067,��ɳ���ⳡ���ֶ��б�������ѡ����������ע��ʧ�ܣ��Ļ��Զ�ģʽ����HPLMN
                     ע�ᣬ����CSע�ᣬPS�쳣������ʧ��
 5.��    ��   : 2011��10��8��
   ��    ��   : s46746
   �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��
 6.��    ��   : 2011��12��20��
   ��    ��   : w00166186
   �޸�����   : ������ע��������RAU,�����쳣8��ԭ��ܾ�,���¿���Ч
 7.��    ��   : 2012��8��25��
   ��    ��   : m00217266
   �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
               ���浼��Attachʧ�ܵ�ԭ��ֵ
************************************************************************/
VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_Cause_Handling(
                                       NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                       VOS_UINT8       *pucAttachFlg,
                                       VOS_UINT8       *pucAbnormalCaseFlg
                                       )
{
    /* ���������*/
    NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(pMsg->aucNasMsg[2]));

    switch (pMsg->aucNasMsg[2])
    {                                                                           /* GMM CAUSE                                */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        Gmm_RoutingAreaUpdateRejectCause3(pMsg->aucNasMsg[2]);                  /* ����#3,#6,#7,#8������                  */
        if (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW == pMsg->aucNasMsg[2])
        {                                                                       /* ԭ��ֵ7                                  */
            if ((GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg)
                && (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg))
            {                                                                   /* Ҫ����LU                                 */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);              /* ֪ͨMM����LU                             */
            }
        }
        break;

    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        if ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* ��ǰ����Ϊnormal RAU                     */
            g_GmmRauCtrl.ucRetryFlg = GMM_FALSE;

            /* ������ע��������RAU,�����쳣8��ԭ��ת��Ϊ111,���⵼�¿���Ч */
            Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR);            /* �����쳣������                         */
            *pucAbnormalCaseFlg = GMM_TRUE;
        }
        else
        {                                                                       /* ��ǰ����Ϊcombined RAU                   */
            Gmm_RoutingAreaUpdateRejectCause3(pMsg->aucNasMsg[2]);              /* ����#3,#6,#7,#8������                  */
        }
        break;

    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Gmm_RoutingAreaUpdateRejectCause9(pMsg->aucNasMsg[2], pucAttachFlg);                  /* ����#9,#10 ������                      */

        NAS_GMM_DeleteEPlmnList();
        break;

    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        Gmm_RoutingAreaUpdateRejectCause11(pMsg->aucNasMsg[2],VOS_TRUE);        /* ����#11,#12,#14 ������                 */
        if (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN == pMsg->aucNasMsg[2])
        {                                                                       /* ԭ��ֵ14                                 */
            g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;
            if ((GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg)
                && (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg))
            {                                                                   /* Ҫ����LU                                 */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);              /* ֪ͨMM����LU                             */
            }
        }
        break;

    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Gmm_RoutingAreaUpdateRejectCause13(VOS_TRUE);                                   /* ����#13,#15������                      */
        if (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == pMsg->aucNasMsg[2])
        {
            NAS_GMM_DeleteEPlmnList();
        }
        break;

    default:
        Gmm_RcvRoutingAreaUpdateRejectMsg_Default_Cause_Handling(pMsg, pucAbnormalCaseFlg);
        break;
    }

    NAS_GMM_CheckCauseToStartT3340(pMsg->aucNasMsg[2]);

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling
 *  FUNCTION : Gmm_RcvRoutingAreaUpdateRejectMsg���������Ӷ�: AttachFlg�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
    1.  ŷ����   2009.06.11  �°�����
    2.��    ��   : 2011��7��25��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    3.��    ��   : 2012��12��5��
      ��    ��   : t00212959
      �޸�����   : DTS2012120504420:CS��ҵ��ʱ��Ӧ�÷������NORMAL ATTACH
    4.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
************************************************************************/
VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsAttachAllow;

    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    ucCsAttachAllow     = NAS_MML_GetCsAttachAllowFlg();

    if (((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
      || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;                         /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling:INFO: normal attach procedure start");
    }
    else if ((VOS_TRUE == ucSimCsRegStatus)
        && (VOS_TRUE == ucCsAttachAllow)
        && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
                                                                    /* CS��ATTACHû����ֹ,��û��CSҵ��                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_COMBINED;           /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling:INFO: combined attach procedure started");
    }
    else
    {                                                                           /* SIM��Ч�����ߴ���CSҵ��                                  */
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;                         /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling:INFO: normal attach procedure start");
    }
    NAS_GMM_SndAttachReq();

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvRoutingAreaUpdateRejectMsg_Not_AbnormalCaseFlg_Handling
 *  FUNCTION : Gmm_RcvRoutingAreaUpdateRejectMsg���������Ӷ�: Not AbnormalCase�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.ŷ����   2009.06.11  �°�����
 2.��    ��   : 2011��7��14��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ע������
************************************************************************/
VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg_Not_AbnormalCaseFlg_Handling(NAS_MSG_FOR_PCLINT_STRU *pMsg)
{
    if ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                       /* NORMAL RAU                               */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        pMsg->aucNasMsg[2]);                         /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */
    }
    else
    {
        NAS_GMM_SndMmCombinedRauRejected(pMsg->aucNasMsg[2]);                  /* ����MMCGMM_COMBINED_RAU_REJECTED��MMC    */
    }


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 pMsg->aucNasMsg[2]);

    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_RAU_FAIL,
                    (VOS_VOID *)&pMsg->aucNasMsg[2],
                    NAS_OM_EVENT_RAU_FAIL_LEN);


    return;
}


/* Added by l00208543 for V9R1 STK����, 2013-07-09, begin */

/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertGmmRauTypeToStkRauType
 ��������  : ��������ת��:NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8->NAS_STK_UPDATE_TYPE_ENUM_UINT8
 �������  : NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8 enGmmRauType MM���RAU TYPE
 �������  :
 �� �� ֵ  : PS_STK_UPDATE_TYPE_ENUM_UINT8 �ϱ���STK��RAU TYPE
 ���ú���  : NAS_GMM_SndStkRauRej
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

*****************************************************************************/
NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_GMM_ConvertGmmRauTypeToStkRauType (
   NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8    enGmmRauType
)
{
    switch (enGmmRauType)
    {
        case GMM_RAU_COMBINED:
             return NAS_STK_RAU_COMBINED;

        case GMM_RAU_WITH_IMSI_ATTACH:
             return NAS_STK_RAU_WITH_IMSI_ATTACH;

        case GMM_RAU_NORMAL:
             return NAS_STK_RAU_NORMAL;

        case GMM_RAU_NORMAL_CS_TRANS:
             return NAS_STK_RAU_NORMAL_CS_TRANS;

        case GMM_RAU_NORMAL_CS_UPDATED:
             return NAS_STK_RAU_NORMAL_CS_UPDATED;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ConvertGmmRauTypeToStkRauType:WARNING: The input in invalid");
            return NAS_STK_UPDATE_TYPE_ENUM_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertGmmRatTypeToStkRatType
 ��������  : ����RAT����ת��:NAS_MML_NET_RAT_TYPE_ENUM_UINT8->TAF_MMA_RAT_TYPE_ENUM_UINT8
 �������  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enMmRatType GMM���RAT TYPE
 �������  : ��
 �� �� ֵ  : TAF_PH_RAT_TYPE_ENUM_UINT8�ϱ���STK��RAT TYPE
 ���ú���  : NAS_GMM_SndStkRauRej  NAS_GMM_SndStkAttachRej
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK��������������

  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/

TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_GMM_ConvertGmmRatTypeToStkRatType (
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enGmmRatType
)
{
    switch (enGmmRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MML_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ConvertGmmRatTypeToStkRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_SndStkRauRej
 ��������  : GMM�ϱ�STK Network Rejection Event
 �������  : ucCause   �ܾ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :Gmm_RcvRoutingAreaUpdateRejectMsg()
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_VOID NAS_GMM_SndStkRauRej(VOS_UINT8 ucCause)
{
    NAS_STK_NETWORK_REJECTION_EVENT_STRU                   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;
    NAS_MML_LAI_STRU                                       *pstRAI = VOS_NULL_PTR;

    /* �����ڴ� */
    ulLength = sizeof(NAS_STK_NETWORK_REJECTION_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_NETWORK_REJECTION_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL_PTR, LOG_LEVEL_ERROR, "NAS_GMM_ReportStkRauRej: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stNetworkRejectionEvent), 0, sizeof(NAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU));

    /* ��д����Ϣ���� */
    pstMsg->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstRAI    =  NAS_MML_GetCurrCampLai();
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.stCurPlmnID.Mcc = pstRAI->stPlmnId.ulMcc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.stCurPlmnID.Mnc = pstRAI->stPlmnId.ulMnc;
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.usLac           = (pstRAI->aucLac[0] << 8) | (pstRAI->aucLac[1]);
    pstMsg->stNetworkRejectionEvent.uRejectInfo.stRauInfo.ucRac           = NAS_MML_GetCurrCampRac();
    pstMsg->stNetworkRejectionEvent.enRejType                 = NAS_STK_RAU_REJECT;

    pstMsg->stNetworkRejectionEvent.enRat                     = NAS_GMM_ConvertGmmRatTypeToStkRatType(pstRAI->enCampPlmnNetRat);

    pstMsg->stNetworkRejectionEvent.ucCauseCode               = ucCause;

    pstMsg->stNetworkRejectionEvent.enUpdateAttachType        = NAS_GMM_ConvertGmmRauTypeToStkRauType(NAS_GMM_GetSpecProc());

    if (VOS_TRUE == NAS_GMM_GetPeriodicRauFlag())
    {
        pstMsg->stNetworkRejectionEvent.enUpdateAttachType    = NAS_STK_RAU_PERIODIC_UPDATING;
    }

    pstMsg->ulMsgName                                         = ID_NAS_STK_NETWORK_REJECTION_EVENT;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_GMM, pstMsg))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL_PTR, LOG_LEVEL_WARNING, "NAS_GMM_ReportStkRauRej: PS_SEND_MSG ERROR");
    }

    return;
}

/* Added by l00208543 for V9R1 STK����, 2013-07-09, end */

/*******************************************************************************
  Module   : Gmm_RcvRoutingAreaUpdateRejectMsg
  Function : ���տտ���Ϣ�տ���ϢRAU REJECT�Ĵ���
  Input    : NAS_MSG_STRU *pMsg     ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.08  �¹�����
  2. x51137 2006/4/28 A32D02889
  3. s46746 2006-06-27 �������ⵥA32D04528�޸�
  4. ��    ��   : 2006��11��7��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D06823
  5.��    ��   : 2007��01��16��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D08381
  6.��    ��   : 2007��3��5��
    ��    ��   : liurui id:40632
    �޸�����   : �������ⵥ�ţ�A32D09094
  7.��    ��   : 2007��05��11��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D10713
  8.��    ��   : 2007��06��16��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D11635,gas�ϱ�GPRS RESUME FAILUREʱ,��Ȼ֪ͨ
                 RABM �ָ��ɹ�,�������PDP����ʱ,����RAU,��������RAU������ϵ
                 ͳ��ϢָʾRAI�����ı�Ͳ��ٷ���RAU.
  9.��    ��    : 2009��9��03��
    ��    ��    : l65478
    �޸�����    : created AT2D14239,detach��ɺ�,�ٴη���ATTATCH REQʱ,GASʹ�þɵ�TLLI������TBF��������,û�м�ʱʹ���µ�TLLI,����MS��������ά����TLLI��һ��,�Ӷ�����GAS��ΪTLLI��ƥ�䶪���˽�������TBF��ָ������,���յ�������ʧ��
  10.��    ��   : 2009��9��16��
      ��    ��   : l65478
      �޸�����   : ���ⵥ��:AT2D13861,RAUʧ��֪ͨOM�ڵ�ԭ��ֵ���� ��Ӧ����rr��connect fail
  11.��    ��   : 2011��7��27��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  12.��    ��   : 2011��8��19��
     ��    ��   : l00130025
     �޸�����   : PhaseI ���ⵥ�޸�:DTS2011080305247,GģҪʹ��ӳ���P-TMSI����TLLI
   13.��    ��   : 2011��3��6��
      ��    ��   : l65478
      �޸�����   : DTS2011052703809,GCF����9.4.2.2.1ʧ��,��ΪGMM������������GMM STATUS��Ϣ
   14.��    ��   : 2011��4��29��
      ��    ��   : c00173809
      �޸�����   : DTS2011042804013,UE������ģʽI��,ͨ������W��ģ������W����ͬRAI
                   ��С��,����W�·���绰,Ȼ��PDP����,Ȼ���ͷ�CS�绰,UE���е�����RAU
                   ��ͨ��EST_REQ������ͨ��DATE_REQ���͵�.
   15.��    ��   : 2012��3��21��
      ��    ��   : z40661
      �޸�����   : DTS2011110201060:L��ѡ��W��������ܾ�#9��Я����PTMSI����ȷ
   16.��    ��   : 2012��3��3��
      ��    ��   : z00161729
      �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
   15.��    ��   : 2012��5��21��
      ��    ��   : l65478
      �޸�����   : DTS2012052101009:��detach������RAI�ı��,����û�м�������DETACH
   16.��    ��   : 2012��9��10��
      ��    ��   : z40661
      �޸�����   : DTS2012081608654:����ģʽI�£�RAU��#9�ܾ���,MMδ����LAU
   17.��    ��   : 2013��5��20��
      ��    ��   : s00217060
      �޸�����   : coverity��foritfy�޸�
   18.��    ��   : 2013��7��13��
      ��    ��   : l00208543
      �޸�����   : STK������Ŀ������NAS_GMM_ReportStkRauRej�ĵ��ã���STK�ϱ�reject��Ϣ
   19.��    ��   : 2013��08��16��
      ��    ��   : l65478
      �޸�����   : DTS2013081400197,T3314��ʱ��,������ֹ��ǰ��ע�����
   20.��    ��   : 2013��10��9��
      ��    ��   : l00208543
      �޸�����   : DTS2013100904573

*******************************************************************************/
VOS_VOID Gmm_RcvRoutingAreaUpdateRejectMsg(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg
)
{
    VOS_UINT8                       ucAttachFlg;                                /* ����ATTACH��־                           */
    VOS_UINT8                       ucAbnormalCaseFlg;                          /* ԭ��ֵ�Ƿ��쳣��־                       */
    NAS_MSG_STRU                   *pGmmStatus = VOS_NULL_PTR;
    VOS_UINT8                       ucForceToStandby;
    VOS_UINT32                      ulNewTlli;
    VOS_UINT8                       aucPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT32                      ulPtmsiValidFlag;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif
    ucAttachFlg        = GMM_FALSE;
    ucAbnormalCaseFlg  = GMM_FALSE;
    ulNewTlli          = 0;

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;

    if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
    {
        /* GMM״̬����GMM_ROUTING_AREA_UPDATING_INITIATED����������Ϣ */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateRejectMsg:WARNING: RAU REJECT is unexpected");

        return;
    }

    /* ��Ϣ���� */
    if (GMM_MSG_LEN_RAU_REJECT > pMsg->ulNasMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateRejectMsg:WARNING: The length of RAU REJECT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        /* ��Ҫ���T3423��ʱ��״̬�������ٴ��յ�ϵͳ��Ϣ��ᷴ��������RAU */
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }
#endif

    /*==>A32D11635*/
    g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;
    /*<==A32D11635*/

    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[3] & 0x0F);

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
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateRejectMsg:WARNING: RAU REJECT is semantically incorrect (IE:Force to Standby)");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    NAS_GMM_ChangeRegRejCauseAvoidInvalidSim(&(pMsg->aucNasMsg[2]));

    /* Added by l00208543 for V9R1 STK����, 2013-07-11, begin */
    NAS_GMM_SndStkRauRej(pMsg->aucNasMsg[2]);
    /* Added by l00208543 for V9R1 STK����, 2013-07-11, end */

    Gmm_RcvRoutingAreaUpdateRejectMsg_T3302_Handling(pMsg);

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ֹͣTimer3330                            */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        g_GmmGlobalCtrl.ucEventCause = pMsg->aucNasMsg[2];
        GMM_RauFailureInterSys();
        g_GmmGlobalCtrl.ucEventCause = GMM_EVENT_CAUSE_INVALID;
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    Gmm_RcvRoutingAreaUpdateRejectMsg_Cause_Handling(pMsg, &ucAttachFlg, &ucAbnormalCaseFlg);

    if (GMM_FALSE == ucAbnormalCaseFlg)
    {                                                                           /* �����쳣ԭ��ֵ                           */
        Gmm_RcvRoutingAreaUpdateRejectMsg_Not_AbnormalCaseFlg_Handling(pMsg);
    }

    /* ����������PS DETACH��Ϣ,��RAU�ܾ���������������PSע��ı�־ */
    if ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
     || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
    {
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

        ucAttachFlg = GMM_FALSE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
    }

    Gmm_ComCnfHandle();
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                         /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */
    g_GmmRauCtrl.ucPeriodicRauFlg  = GMM_FALSE;                                 /* �����ǰRAU�Ƿ�������RAU��־             */
    g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                        /* ������ڽ��е�specific���̱�־           */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRoutingAreaUpdateRejectMsg:INFO: specific procedure ended");


    /* Modified by s00217060 for coverity��foritfy�޸� , 2013-05-20, begin */
    /* ��ʼ�� */
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));
    /* Modified by s00217060 for coverity��foritfy�޸� , 2013-05-20, end */

    ulPtmsiValidFlag   = NAS_GMM_GetPTmsiForTLLI(aucPtmsi);

    if ((GMM_TRUE == GMM_IsCasGsmMode())
      &&(VOS_TRUE == ulPtmsiValidFlag))
    {
        GMM_CharToUlong(&ulNewTlli, aucPtmsi);                                  /* �µ�PTMSI */
        GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);                          /* ������TLLI */

        if (GMM_FALSE == GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI))
        {
            GMM_LOG_WARN("Gmm_RcvRoutingAreaUpdateRejectMsg():Error: new TLLI assigned unsuccessfully!");
        }
    }


    if (GMM_TRUE == ucAttachFlg)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if ( NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED == pMsg->aucNasMsg[2] )
        {
            NAS_GMM_SetLteGutiValid(VOS_FALSE);
        }
#endif

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        else
        {
        /* ����ATTACHʹ����ԭ����TBF����ATTACHʧ�ܣ������ڴ˴��ȵ�TBF�ͷź��ٷ���ATTACH */
            if(GMM_TRUE == GMM_IsCasGsmMode())
            {
                g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_TRUE;
            }
            else
            {
                Gmm_RcvRoutingAreaUpdateRejectMsg_AttachFlg_Handling();
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg)
        {
            gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

            if (0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue)
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                Gmm_TimerStop(GMM_TIMER_T3314);
                if ((0x10 != (g_GmmGlobalCtrl.ucState & 0xF0))
                 && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);
                }

                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
        }
    }

    /* ��ucRauCauseΪGMM_RAU_FOR_INTERSYSTEMʱ,֪ͨRABM��RAU���Ͳ�ͬ(RAU����Ϊϵͳ���л�),
       ����������ԭ��ֵ���͸�RABM��RAU������ͬ(������RAU),RABM�����RAU�����ͽ���״̬��Ǩ��,
       �������RAUԭ��ΪGMM_RAU_FOR_INTERSYSTEMʱ, �������ucRauCause */
    if (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
    {
        /* �˱�־��¼����ϵͳ����ѡ�����л�ʱ,RAI��ͬʱ,����������������ʱ��Ҫ����RAU.
           ��Ϊ���ô˺���ʱRAU�Ѿ����,������Ҫ����˱�־ */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_Com_CmpRai
  Function : �ж��յ���RAU ACCEPT��Ϣ�е�RAI��ϵͳ��Ϣ�е�RAI�Ƿ�һ��
  Input    : GMM_RAI_STRU *pRaiTemp  GMM_RAI_STRU���͵�ָ�����
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ��־��  2003.12.10  �¹�����
    2.��    ��   : 2012��3��7��
      ��    ��   : z00161729
      �޸�����   : V7R1 C50 ֧��ISR�޸�
    3. ��    ��   : 2012��7��17��
       ��    ��   : z00161729
       �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                    ��������rau
    4. ��    ��   : 2012��7��17��
        ��    ��   : z00161729
        �޸�����   : DTS2012073106360:ISR����CSFB�ض����CCO��GU,idle̬λ��������������RAU
    5. ��    ��   : 2012��09��08��
       ��    ��   : l65478
       �޸�����   : DTS012090302087,L->GUʱ,RAIû�иı�ʱ,GMM������RAU
    6.��    ��   : 2015��1��5��
      ��    ��   : z00161729
      �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_UINT8 Gmm_Com_CmpRai(
    GMM_RAI_STRU                       *pstNewRai,
    GMM_RAI_STRU                       *pstOldRai,
    VOS_UINT8                           ucNetMod
)
{
    VOS_UINT8                           ucRet;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;
    VOS_UINT32                          ulT3302Status;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());
    ulT3302Status                = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    ucRet         = GMM_FALSE;

    if (GMM_TRUE == Gmm_Compare_Lai(&pstNewRai->Lai, &pstOldRai->Lai))
    {                                                                           /* LAIһ��                                  */
        if (pstNewRai->ucRac == pstOldRai->ucRac)
        {                                                                       /* RACһ��                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }


#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
    {
        /* 3GPP 23401 4.3.5.6   Idle mode signalling reduction function:
           The Idle mode Signalling Reduction (ISR) function provides a
           mechanism to limit signalling during inter-RAT cell-reselection
           in idle mode (ECM-IDLE, PMM-IDLE, GPRS STANDBY states).
        */
        /* AT&T LTE-BTR-1-1824��LTE-BTR-1-1826��LTE-BTR-1-1828����Ҫ��
           GMM��GU��attach����Ӧ�򱻾ܴ�����������T3302��ʱ����������ϵͳ
           ��������L�º�����ֹͣ��L��ע��ʧ������disable lte������GU������
           ��ԭʧ��С��ʱ����T3302��ʱ������ps attach */
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != NAS_MML_GetTinType()
          && ((VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo)
           || (VOS_FALSE == ulT3302Status)))
        {
            ucRet = GMM_FALSE;
        }

        /* �������ģʽI,��L��ϵͳ��GU,��Ҫ�ж�CS ��LAI�Ƿ�ı䣬����ı���Ҫ��������rau */
        if (GMM_TRUE == NAS_GMM_IsCsLaiChangeNeedRegister(ucNetMod))
        {
            ucRet = GMM_FALSE;
        }
    }
#endif

    return ucRet;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateAttemptCounter
  Function : RAU Attempt Counter�Ĵ���
  Input    : VOS_UINT32 ulGmmCause       ʧ��ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �¹�����
  2.��    ��   : 2007��01��16��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D08381
  3.��    ��   : 2007��05��11��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D10713
  4.��    ��   : 2007��06��16��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D11635
  5.��    ��   : 2009��09��25��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D14675,RAU/Attach�����У�list����ʧ��
  6.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
  7.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  8.��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  9.��    ��   : 2011��7��26��
    ��    ��   : l00130025
    �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
 10.��    ��   : 2011��10��8��
    ��    ��   : s46746
    �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��
 11.��    ��   : 2012��7��17��
    ��    ��   : z00161729
    �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                 ��������rau
 12.��    ��   : 2012��10��25��
    ��    ��   : w00167002
    �޸�����   : DTS2012101600008:TS24008a60:4.7.5.1.5:Э�������������ǰRAIû��
                 �����ı䣬�ҵ�ǰ��TIN��ΪGUTI����ǰ����U1̬��GMM��Ǩ�Ƶ�NORMAL
                 SERVICE.
 13.��    ��   : 2012��11��27��
    ��    ��   : t00212959
    �޸�����   : DTS2012021004490:RAU����#111��GMM��MMC�ϱ���PS_REG_RESULT��Я����ע�����Ϊ6
 14.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 15.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
 16.��    ��   : 2013��10��05��
    ��    ��   : l65478
    �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
 17.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
 18.��    ��   : 2015��6��10��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateAttemptCounter(
                                         VOS_UINT32 ulGmmCause                  /* ʧ��ԭ��                                 */
                                         )
{
    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    NAS_MML_RAI_STRU                           *pstLastSuccRai;
    GMM_RAI_STRU                                stGmmRai;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;
    NAS_MML_TIN_TYPE_ENUM_UINT8                 enTinType;

    enTinType       = NAS_MML_GetTinType();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* �Ѿ��ﵽ����Դ�������û�м�����1�ı�Ҫ��ֻҪ�ﵽ�򳬹�5�δ�����һ����*/
    if (GMM_ATTACH_RAU_ATTEMPT_MAX_CNT > g_GmmRauCtrl.ucRauAttmptCnt)
    {
        g_GmmRauCtrl.ucRauAttmptCnt++;                                          /* RAU Attempt Counter��1                   */
    }

    if (5 > g_GmmRauCtrl.ucRauAttmptCnt)
    {                                                                           /* ucRauAttmptCntС��5                      */
        enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

        if ((GMM_TRUE == Gmm_Com_CmpRai(&stGmmRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
         && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus)
         && (NAS_MML_TIN_TYPE_GUTI                 != enTinType))
        {                                                                       /* RAI����Ҹ���״̬��GU1                   */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                       /* ����״̬�Ĺ�������                       */


            /*ֻ��ǰ����й�RAU suspend���˴�resume��������*/
            if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
                }
            }

        }
        else
        {                                                                       /* RAI����Ȼ��߸���״̬����GU1             */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* �ø���״̬ΪGU2                          */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);                 /* ����״̬�Ĺ�������                       */
        }
        Gmm_TimerStart(GMM_TIMER_T3311);                                        /* ����Timer3311                            */

    }
    else
    {                                                                           /* ucRauAttmptCnt���ڵ���5                  */

        /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

        /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* �ø���״̬ΪGU2                          */

        /* ��U2״̬��Ǩ��attempting to attach״̬���浱ǰ��RAI��Ϣ */
        NAS_GMM_SetAttemptUpdateRaiInfo(NAS_MML_GetCurrCampPlmnInfo());

        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;                             /* ���̽��������3312�����־               */
        /*==>A32D11635*/
        g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;
        /*<==A32D11635*/
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);                     /* ����״̬�Ĺ�������                       */

        /* 24008_CR1904R1_(Rel-11)_C1-113602 Handling of timer T3302 24008 4.7.2.x�½���������:
        The MS shall apply this value in the routing area registered by the MS, until a new value is received.
        The default value of this timer is used in the following cases:
        -   ATTACH ACCEPT message, ROUTING AREA UPDATE ACCEPT message, ATTACH REJECT message, or ROUTING AREA UPDATE REJECT message is received without a value specified;
        -   In Iu mode, if the network provides a value in a non-integrity protected Iu mode GMM message and the MS is not attaching for emergency services or not attached for emergency services;
        -   the MS does not have a stored value for this timer; or
        -   a new PLMN which is not in the list of equivalent PLMNs has been entered, the routing area updating fails and the routing area updating attempt counter is equal to 5.
        ע��ʧ�ܴ�5�Σ����ϴ��·�t3302��ʱ��ʱ��������ͬ��ǰפ�����粻ͬ����t3302ʹ��Ĭ��ֵ��*/
        if (VOS_TRUE == NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax())
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }

        Gmm_TimerStart(GMM_TIMER_T3302);                                        /* ����Timer3302                            */

        NAS_GMM_DeleteEPlmnList();
    }

    if ((GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_RAU_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* NORMAL RAU                               */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulGmmCause);                             /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */

    }
    else if (GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmCombinedRauRejected(ulGmmCause);                              /* ����MMCGMM_COMBINED_RAU_REJECTED��MMC    */
    }
    else
    {
    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulGmmCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_RAU_FAIL,
                    (VOS_VOID*)&ulGmmCause,
                    NAS_OM_EVENT_RAU_FAIL_LEN);

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        if (GMM_DETACH_COMBINED == g_GmmGlobalCtrl.ucSpecProcHold)
        {
            NAS_GMM_SndMmGprsDetachInitiation();                                   /* ��MMC����MMCGMM_GPRS_DETACH_INITIATION   */

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                /* ����detach��,��ҪǨ�Ƶ���Ӧ��״̬ */
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }
                NAS_GMM_SndMmcMmDetachInfo();
            }

            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                          /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                /* ������ڽ��е�specific���̱�־           */
        }
        else if (GMM_DETACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcHold)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                          /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                /* ������ڽ��е�specific���̱�־           */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                /* ����detach��,��ҪǨ�Ƶ���Ӧ��״̬ */
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }
                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
                NAS_GMM_SndMmGprsDetachComplete();
            }

        }
        else if (GMM_DETACH_WITH_IMSI == g_GmmGlobalCtrl.ucSpecProcHold)
        {
            NAS_GMM_SndMmImsiDetachInitiation();                                   /* ��MMC����MMCGMM_IMSI_DETACH_INITIATION   */

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                          /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                /* ������ڽ��е�specific���̱�־           */
        }
        else
        {
        }
    }
    Gmm_ComCnfHandle();

    if (NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT == ulGmmCause)
    {                                                                           /* T3330 time-out 5��                       */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                   /* �ͷ�PS����������                         */
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �����ǰ���е�specific����               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateAttemptCounter:INFO: specific procedure ended");

    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdataAcceptRaOnly
  Function : RAU ACCEPT�Ľ����GPRS only attached�Ĵ���
  Input    : GMM_MSG_RESOLVE_STRU  *pRauAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                     �ṹ��ָ��
             NAS_MSG_STRU          *pMsg             ָ��NAS_MSG_STRU�ṹ
                                                     ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �¹�����
  2.��    ��   : 2007��11��12��
    ��    ��   : l39007
    �޸�����   : �������ⵥA32D13044
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��03��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����
  5.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : ɾ��GMM_ClearErrCode��PS��������ϱ���Ŀ��
  6.��    ��   : 2014��08��5��
    ��    ��   : b00269685
    �޸�����   : DTS2014072107208�޸�
  6.��    ��   : 2014��9��3��
    ��    ��   : w00167002
    �޸�����   : DTS2014090300904:����TAU, RA UPDATING SUCCҲͬ����ע��ɹ�
  7.��    ��   : 2015��6��9��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdataAcceptRaOnly(
    GMM_MSG_RESOLVE_STRU                *pRauAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU             *pMsg
)
{

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_NULL;

    if (GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG
        == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG))
    {
        enCause = pMsg->aucNasMsg[pRauAcceptIe->
                aucIeOffset[GMM_RAU_ACCEPT_IE_GMM_CAUSE] + 1 ];                 /* �õ�GMM CAUSE                            */
    }


    if ((GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_RAU_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ��specific������NORMAL RAU           */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* ����״̬�Ĺ�������                       */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* routing area updating attempt counter��0 */

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);                         /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */



        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_RAU_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }
    else
    {                                                                           /* combined����                             */
        if ((GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
            && (NAS_MML_REG_FAIL_CAUSE_NULL == enCause))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                       /* ����״̬�Ĺ�������                       */
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* routing area updating attempt counter��0 */
            NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                           enCause,
                                           pMsg,
                                           pRauAcceptIe);                          /* ����MMCGMM_COMBINED_RAU_ACCEPTED��MMC    */

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);
            /*����RAU������ */
            if(5<=g_GmmRauCtrl.ucRauAttmptCnt)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }

            /*  �¼��ϱ� */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_RAU_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);

            g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                 /* �����ǰ���е�specific ���̱�־          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdataAcceptRaOnly:INFO: specific procedure ended");
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;                          /* �����ǰRAU�Ƿ�������RAU��־             */
            return;
        }


        /* R11����:   24008 4.7.3.2.3.2    Other GMM causevalues and the case that no GMM cause IE
           was received are considered as abnormal cases. The combined attach procedure shall be
           considered as failed for non-GPRS services */
        if ((GMM_RAU_WITH_IMSI_ATTACH == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_RAU_COMBINED         == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                           /* ��ǰ���������ע�� */
            /* ��ʧ��ԭ��ֵ��Ϊ#2,#16,#17,#22,ֱ�ӽ�ԭ��ֵ�滻Ϊ#16 */
            if ((NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE      != enCause)
             && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE      != enCause)
             && (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION != enCause)
             && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR  != enCause))
            {
                enCause = NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE;
            }
        }


        if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == enCause)
        {                                                                       /* ԭ��ֵΪ2                                */
            /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.5.2.3.2�½���������:
            #2:The MS shall stop timer T3330 if still running and shall reset the
            routing area updating attempt counter. The MS shall set the update
            status to U3 ROAMING NOT ALLOWED and shall delete any TMSI, LAI and
            ciphering key sequence number. The MS shall enter state GMM-REGISTERED.NORMAL-SERVICE.
            The new MM state is MM IDLE*/
            g_GmmRauCtrl.ucRauAttmptCnt = 0;
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        }
        else if ((NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE         == enCause)
                 || (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE      == enCause)
                 || (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCause))
        {                                                                       /* ԭ��ֵΪ16,17,22                         */
            Gmm_AttachRauAcceptCause16(enCause);                                       /* ����ԭ��ֵ16��17��22������             */
        }
        else
        {

        }
        if((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            ||(5 > g_GmmRauCtrl.ucRauAttmptCnt))
        {
            NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                           enCause,
                                           pMsg,
                                           pRauAcceptIe);                          /* ����MMCGMM_COMBINED_RAU_ACCEPTED��MMC    */


            /* ��MMC����PSע���� */

            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         enCause);


            /* �¼��ϱ� */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_RAU_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA
                            );
        }
        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                     /* �����ǰ���е�specific ���̱�־          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdataAcceptRaOnly:INFO: specific procedure ended");
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;                              /* �����ǰRAU�Ƿ�������RAU��־             */
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdataAcceptCombined
  Function : RAU ACCEPT�Ľ����combined updated�Ĵ���
  Input    : GMM_MSG_RESOLVE_STRU  *pRauAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                     �ṹ��ָ��
             NAS_MSG_STRU          *pMsg             ָ��NAS_MSG_STRU�ṹ
                                                     ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2012��3��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����
  4.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : ɾ��GMM_ClearErrCode��PS��������ϱ���Ŀ��
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdataAcceptCombined(
                                     GMM_MSG_RESOLVE_STRU    *pRauAcceptIe,     /* ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��       */
                                     NAS_MSG_FOR_PCLINT_STRU *pMsg
                                     )
{
    g_GmmRauCtrl.ucRauAttmptCnt = 0;                                            /* routing area updating attempt counter��0 */
    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* ����״̬�Ĺ�������                       */

    if ((GMM_RAU_NORMAL             == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ��specific������NORMAL RAU           */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);     /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */


        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


    }
    else
    {                                                                           /* combined����                             */
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                       NAS_MML_REG_FAIL_CAUSE_NULL,
                                       pMsg,
                                       pRauAcceptIe);                              /* ����MMCGMM_COMBINED_RAU_ACCEPTED��MMC    */


        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                     /* �����ǰ���е�specific ���̱�־          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdataAcceptCombined:INFO: specific procedure ended");
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;                              /* �����ǰRAU�Ƿ�������RAU��־             */

        if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
            && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {                                                                       /* ����ģʽ��ʵ�ʲ�һ��                     */
            g_GmmGlobalCtrl.ucNetMod = GMM_NET_MODE_I;                          /* ������ģʽΪI                            */
        }

    }


    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_RAU_SUCC,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckNpduValid
 ��������  : ���NPDU�Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE : NPDU��Ч
             VOS_FALSE: NPDU��Ч
 ���ú���  :
 ��������  :
��ȡ
 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckNpduValid(
    VOS_UINT8                           ucNpduLen,
    VOS_UINT8                          *pucNpdu
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNpduNumber;

    if (ucNpduLen > GMM_NPDU_MAX_LENGTH)
    {
        return VOS_FALSE;
    }

    /*���N-PDU�ĸ���:*/
    ucNpduNumber = ( VOS_UINT8 )((ucNpduLen * 8) / 12);

    /*����N-PDU:*/
    for ( ucLoop = 1; ucLoop <= ucNpduNumber; ucLoop++ )
    {
        if ( 1 == (ucLoop % 2) )
        {
            /*�õ�N-PDU value�������е�����(���Ϊ����):*/
            ucIndex  = ( VOS_UINT8 )(( ( ucLoop - 1 ) * 12 ) / 8);

            /*��ȡNSAPI��:*/
            ucNsapi = (pucNpdu[ucIndex] >> 4) & 0x0f;
        }
        else
        {
            /*�õ�N-PDU value�������е�����(���Ϊż��):*/
            ucIndex  = ( VOS_UINT8 )(( ucLoop * 12 ) / 8);

            /*��ȡNSAPI��:*/
            ucNsapi = pucNpdu[ucIndex] & 0x0f;
        }

        if ((ucNsapi > GMM_NSAPI_MAX_VALUE) || (ucNsapi < GMM_NSAPI_MIN_VALUE))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  :NAS_GMM_DecodeT3312ExtendedValueIE_RcvRauAccept
 ��������  :��rau accept��Ϣ�н���T3312 extended value IE����
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
VOS_UINT32 NAS_GMM_DecodeT3312ExtendedValueIE_RcvRauAccept(
    GMM_MSG_RESOLVE_STRU               *pRauAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    VOS_UINT8                           ucIeOffset
)
{
    if ((ucIeOffset + NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN) > (VOS_UINT8)pMsg->ulNasMsgSize)
    {
        return VOS_FALSE;
    }

    if (NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG == (pRauAcceptIe->ulOptionalIeMask & NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG))
    {
        return VOS_TRUE;
    }

    if (PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
    {
        NAS_GMM_SaveGprsTimer3Value(GMM_TIMER_T3312, pMsg->aucNasMsg[ucIeOffset + 2]);
    }

    pRauAcceptIe->ulOptionalIeMask |= NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE_FLG;
    pRauAcceptIe->aucIeOffset[NAS_GMM_RAU_ACCEPT_IE_T3312_EXTENDED_VALUE] = ucIeOffset;

    return VOS_TRUE;
}


/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateResolveIe
  Function : ����RAU ACCEPT��IE
  Input    : GMM_MSG_RESOLVE_STRU  *pRauAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                     �ṹ��ָ��
             NAS_MSG_STRU          *pMsg             ָ��NAS_MSG_STRU�ṹ
                                                     ��ָ��
  Output   : GMM_MSG_RESOLVE_STRU  *pRauAcceptIe     ָ��GMM_MSG_RESOLVE_STRU
                                                     �ṹ��ָ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����

    2.��    ��   : 2012��3��20��
      ��    ��   : z00161729
      �޸�����   : �����ɺ���
    3.��    ��   : 2012��3��27��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
    4.��    ��   : 2013��8��30��
      ��    ��   : w00242748
      �޸�����   : KLOC�澯����
    5.��    ��   : 2013��09��10��
      ��    ��   : l65478
      �޸�����   : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
    6.��    ��   : 2013��10��25��
      ��    ��   : w00167002
      �޸�����   : DTS2013102201891:���ӶԽ����������쳣�Ĵ���
                 1.���ս�������д���ܳ���ֵ�������ᳬ��������Ϣ�ĳ��ȣ�����Ϊ�쳣��
                 2.����ÿ���ӽ�������Ϣ�ĳ���ֵ�����������˽�������д���ܳ���ֵ������Ϊ�쳣��

                 ����NAS_MM_DecodeEMC������MML��NAS_MML_DecodeEmergencyNumList��
                 ��GMM/MM����������б�ʹ�á�
    7.��    ��   : 2015��6��8��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateResolveIe(
                                    GMM_MSG_RESOLVE_STRU    *pRauAcceptIe,      /* ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��       */
                                    NAS_MSG_FOR_PCLINT_STRU *pMsg               /* ָ��NAS_MSG_FOR_PCLINT_STRU�ṹ          */
                                    )
{
    VOS_UINT8   ucEndFlg    = GMM_FALSE;
    VOS_UINT8   ucIeOffset  = GMM_MSG_LEN_RAU_ACCEPT;                           /* ������ʱ�����洢�洢IE��ƫ����           */

    VOS_UINT16                          usIeOffsetAdapt;

    usIeOffsetAdapt         = 0;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (0 == ((pMsg->aucNasMsg[2] >> 4) & 0x08))
        {
            g_GmmGlobalCtrl.ucFopFlg = GMM_TRUE;
        }
        else
        {
            g_GmmGlobalCtrl.ucFopFlg = GMM_FALSE;
        }
    }

    for (; (ucIeOffset<pMsg->ulNasMsgSize) && (GMM_FALSE == ucEndFlg); )
    {                                                                           /* �洢IE��ƫ����С�ڿտ���Ϣ�ĳ���         */
        switch (pMsg->aucNasMsg[ucIeOffset])
        {                                                                       /* IEI                                      */
        case GMM_IEI_P_TMSI_SIGNATURE:                                          /* P-TMSI signature                         */
            if ((ucIeOffset + 4) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"P-TMSI signature\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE_FLG))
            {
                ucIeOffset += 4;
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE]
                = ucIeOffset;
            ucIeOffset += 4;
            break;
        case GMM_IEI_ALLOCATED_PTMSI:                                           /* Allocated P-TMSI                         */
            if ((ucIeOffset + 7) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"P-TMSI\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_PTMSI_FLG ==
                (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_PTMSI_FLG))
            {
                ucIeOffset += 7;
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_PTMSI_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_PTMSI]
                = ucIeOffset;
            ucIeOffset += 7;
            break;
        case GMM_IEI_MS_IDENTITY:                                               /* MS identity                              */
            if (GMM_MOBILE_ID_IMSI == (pMsg->aucNasMsg[ucIeOffset + 2] & 0x07))
            {                                                                   /* IE����IMSI                               */
                if ((ucIeOffset + 10) > (VOS_UINT8)pMsg->ulNasMsgSize)
                {
                    /* IMSI����ʱ,��ʹ���Ȳ���,Ҳ��Ҫ���� */
                    pRauAcceptIe->ulOptionalIeMask
                        |= GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG;
                    pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_MS_IDENTITY]
                        = ucIeOffset;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"MS ID(IMSI)\" in RAU ACCEPT is invalid");
                    return;
                }
                if (GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG ==
                    (pRauAcceptIe->ulOptionalIeMask
                    & GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG))
                {
                    ucIeOffset += 10;
                    break;
                }
            }
            else
            {
                if ((ucIeOffset + 7) > (VOS_UINT8)pMsg->ulNasMsgSize)
                {
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"MS ID(TMSI)\" in RAU ACCEPT is invalid");
                    return;
                }
                if (GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG ==
                    (pRauAcceptIe->ulOptionalIeMask
                    & GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG))
                {
                    ucIeOffset += 7;
                    break;
                }
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_MS_IDENTITY]
                = ucIeOffset;
            if (GMM_MOBILE_ID_IMSI == (pMsg->aucNasMsg[ucIeOffset + 2] & 0x07))
            {                                                                   /* IE����IMSI                               */
                ucIeOffset += 10;
            }
            else
            {                                                                   /* IE����TMSI                               */
                ucIeOffset += 7;
            }
            break;
        case GMM_IEI_LIST_OF_RECEIVE_N_PDU_NUMBERS:                             /* Allocated P-TMSI                         */
            if ((ucIeOffset + (2 + pMsg->aucNasMsg[ucIeOffset + 1]))
                 > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"N-PDU\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_NPDU_NUMBER_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_NPDU_NUMBER_FLG))
            {
                ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
                break;
            }

            if (VOS_TRUE == NAS_GMM_CheckNpduValid(pMsg->aucNasMsg[ucIeOffset + 1], &(pMsg->aucNasMsg[ucIeOffset + 2])))
            {
                pRauAcceptIe->ulOptionalIeMask
                    |= GMM_RAU_ACCEPT_IE_NPDU_NUMBER_FLG;
            }
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_NPDU_NUMBER]
                = ucIeOffset;
            ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            break;
        case GMM_IEI_NEGOTIATED_READY_TIMER_VALUE:                              /* Negotiated READY timervalue              */
            if ((ucIeOffset + 2) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"READY TIMER value\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_READY_TIMER_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_READY_TIMER_FLG))
            {
                ucIeOffset += 2;
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_READY_TIMER_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_READY_TIMER]
                = ucIeOffset;
            ucIeOffset += 2;
            break;
        case GMM_IEI_GMM_CAUSE:                                                 /* GMM cause                                */
            if ((ucIeOffset + 2) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"GMM cause\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG))
            {
                ucIeOffset += 2;
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_GMM_CAUSE]
                = ucIeOffset;
            ucIeOffset += 2;
            break;
        case GMM_IEI_T3302_VALUE:                                               /* T3302 value                              */
            if ((ucIeOffset + 3) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"T3302 value\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_T3302_VALUE_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_T3302_VALUE_FLG))
            {
                ucIeOffset += 3;
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_T3302_VALUE_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_T3302_VALUE]
                = ucIeOffset;
            ucIeOffset += 3;
            break;
        case GMM_IEI_CELL_NOTIFICATION:                                         /* Cell Notification                        */
            if ((ucIeOffset + 1) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"Cell notification\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION_FLG))
            {
                ucIeOffset += 1;
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION]
                = ucIeOffset;
            ucIeOffset += 1;
            break;
        case GMM_IEI_EQUIVALENT_PLMNS:                                          /* Equivalent PLMNs                         */
            if ((ucIeOffset + (2 + pMsg->aucNasMsg[ucIeOffset + 1]))
                 > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"Equivalent PLMNs\" in RAU ACCEPT is invalid");
                return;
            }
            if (GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG ==
                (pRauAcceptIe->ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG))
            {
                ucIeOffset += 2 + pMsg->aucNasMsg[ucIeOffset + 1];
                break;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN]
                = ucIeOffset;
            ucIeOffset += 2 + pMsg->aucNasMsg[ucIeOffset + 1];
            break;
        case GMM_IEI_PDP_CONTEXT_STATUS:
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS_FLG;
            pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS]
                = ucIeOffset;
            ucIeOffset += 4;
            break;
        case GMM_IEI_EMERGENCY_NUMBER_LIST:                                     /* Emergency Number List                    */
            if ( (ucIeOffset + (2 + pMsg->aucNasMsg[ucIeOffset + 1]))
                 > (VOS_UINT8)pMsg->ulNasMsgSize )
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"emergency number\" length error in ATTACH ACCEPT");
                return;
            }
            pRauAcceptIe->ulOptionalIeMask
                |= GMM_RAU_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG;

            usIeOffsetAdapt = ucIeOffset;
            (VOS_VOID)NAS_MML_DecodeEmergencyNumList(&usIeOffsetAdapt, pMsg->aucNasMsg, (VOS_UINT16)pMsg->ulNasMsgSize);
            ucIeOffset      = (VOS_UINT8)usIeOffsetAdapt;


            break;

        case NAS_GMM_IEI_T3323_VALUE:
            if ((ucIeOffset + NAS_GMM_IE_T3323_VALUE_LEN) > (VOS_UINT8)pMsg->ulNasMsgSize)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateResolveIe:WARNING: IE\"T3302 value\" in RAU ACCEPT is invalid");
                return;
            }

            if (GMM_RAU_ACCEPT_IE_T3323_VALUE_FLG == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_T3323_VALUE_FLG))
            {
                ucIeOffset += NAS_GMM_IE_T3323_VALUE_LEN;
                break;
            }

            Gmm_SaveTimerValue(GMM_TIMER_T3323, pMsg->aucNasMsg[ucIeOffset + 2]);

            pRauAcceptIe->ulOptionalIeMask |= GMM_RAU_ACCEPT_IE_T3323_VALUE_FLG;
            pRauAcceptIe->aucIeOffset[NAS_GMM_RAU_ACCEPT_IE_T3323_VALUE] = ucIeOffset;
            ucIeOffset += NAS_GMM_IE_T3323_VALUE_LEN;
            break;

        case NAS_GMM_IEI_T3312_EXTENDED_VALUE:
            if (VOS_FALSE == NAS_GMM_DecodeT3312ExtendedValueIE_RcvRauAccept(pRauAcceptIe, pMsg, ucIeOffset))
            {
                return;
            }

            ucIeOffset += NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN;
            break;

        default:
            if(GMM_IEI_NETWORK_FEATURE_SUPPORT == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            {/* Network feature support                  */
                ucIeOffset += 1;
            }
            else if (GMM_IEI_REQUESTED_MS_INFORMATION == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            {/* Requested MS information                 */
                pRauAcceptIe->ulOptionalIeMask
                    |= GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION_FLG;
                pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_REQUESTED_MS_INFORMATION]
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

/*****************************************************************************
 �� �� ��  : Gmm_RoutingAreaUpdateHandle_Under_Gsm
 ��������  : GSM��RAU�Ĵ���
 �������  : VOS_UINT8               ucInterRatInfoFlg
             VOS_UINT8               ucReadychangFLG
             VOS_BOOL                bTlliUpdateFlag
             VOS_UINT8               ucSndCompleteFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��12��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��4��12��
    ��    ��   : l65478
    �޸�����   : AT2D18389,�ڳ�ʼС������ʱ��GMMӦ��֪ͨLLC����NULL֡
  3.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����

*****************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_Under_Gsm(
                                 VOS_UINT8               ucInterRatInfoFlg,
                                 VOS_UINT8               ucReadychangFLG,
                                 VOS_BOOL                bTlliUpdateFlag,
                                 VOS_UINT8               ucSndCompleteFlg
                                 )
{
    NAS_MSG_STRU               *pSendNasMsg      = VOS_NULL_PTR;                /* ������ʱ����                             */

    /* ֪ͨRABM��ȡ��N-PDU Number */
    Gmm_TimerStart(GMM_TIMER_RAU_RSP);                                          /* ��Ϣ���ܱ�����ʱ�� */

    if (VOS_FALSE == bTlliUpdateFlag)
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
        {
            g_GmmRauCtrl.ucNpduCnt = g_GmmDownLinkNpduBake.ucNpduCnt;
            Gmm_MemCpy(g_GmmRauCtrl.aucNpduNum, g_GmmDownLinkNpduBake.aucNpduNum, g_GmmRauCtrl.ucNpduCnt);
            gstGmmCasGlobalCtrl.ucRauCmpFlg = GMM_FALSE;
            pSendNasMsg = Gmm_RoutingAreaUpdateCompleteMsgMake();

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

            /*ֻ��ǰ����й�RAU suspend���˴�resume��������*/
            if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* �ָ�LLC���ݴ��� */
                }
            }

            GMM_InitCellUpdate(ucReadychangFLG);                                               /* С�����£���Ч�µ�READY TIMER */

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandle_Under_Gsm:INFO: specific procedure ended");
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
        }
        GMM_LOG_WARN("Gmm_RoutingAreaUpdateHandle():WARNING: receive rau accept again!");
    }
    else if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL,GMM_RABM_RAU_SUCCESS);
    }

    if (GMM_TRUE == ucReadychangFLG)
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_READY_TIMER);
    }

    /* ֻ���ڲ���Ҫ����RAU COMPLETE��Ϣʱ����Ҫ֪ͨLLC����cell update��
       ��Ϊ���ظ��յ������RAU ACCEPT��Ϣʱ����ǰ�淢��RAU COMPLETE��
       �Ѿ���ucRauCmpFlg��������Դ�ʱ��Ҫʹ��������־���ж��Ƿ���Ҫ����
       RAU COMPLETE
    */
    if (GMM_TRUE == ucSndCompleteFlg)
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        GMM_InitCellUpdate(ucReadychangFLG);                                               /* only restart ready timer */

    }
    else
    {
        /*ֻ��ǰ����й�RAU suspend���˴�resume��������*/
        if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
        {
            gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                            /* �ָ�LLC���ݴ��� */
            }
        }
        if (0 != (g_GmmTimerMng.ulTimerValMask & GMM_TIMER_T3314_FLG))      /* 3314 value change */
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_TRUE;

            /* ����24.008 4.7.2.1.1 If a new READY timer value is negotiated,
            the MS shall upon the reception of the ATTACH ACCEPT or ROUTING
            AREA UPDATE ACCEPT message perform a initial cell update
            (either by transmitting a LLC frame or, if required, a ATTACH
            COMPLETE or ROUTING AREA UPDATE COMPLETE message), in order to
            apply the new READY timer value immediately. If both the network
            and the MS supports the Cell Notification, the initial cell
            update shall useany LLC frame except the LLC NULL frame. */
            GMM_InitCellUpdate(ucReadychangFLG);                                           /* CELL update&restart ready timer */
        }

        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandle:INFO: specific procedure ended");
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
        if ( (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
           &&(GMM_TRUE != g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg))
        {                                                                   /* �б�������Ϣ���ҵ�ǰû�л����RAU����                             */
            Gmm_DealWithBuffAfterProc();
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_Under_W
 *  FUNCTION : Gmm_RoutingAreaUpdateHandle���������Ӷ�: WCDMA�µĴ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2012��3��7��
      ��    ��   : z00161729
      �޸�����   : V7R1 C50 ֧��ISR�޸�
 ************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_Under_W(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsPsBearerExist())
    {

        if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
        {
            GMM_RauSuccessInterSys();
        }
        else
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
    }
    else
    {
        if (GMM_RAU_FOR_INTERSYSTEM != gstGmmSuspendCtrl.ucRauCause)
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_T3302_Handling
 *  FUNCTION : Gmm_RoutingAreaUpdateHandle���������Ӷ�: T3302�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2011��3��3��
       ��    ��   : z00161729
       �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��

     3.��    ��   : 2013��11��18��
       ��    ��   : w00167002
       �޸�����   : DTS2013112006986:������3G TDDģʽ���Ƿ���Ҫ����SMC��֤���:�й��ƶ����������豸��
                    TD�²�����SMC���̡�
     4.��    ��   : 2015��6��9��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 ************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_T3302_Handling(GMM_MSG_RESOLVE_STRU           *pRauAcceptIe,
                                                    NAS_MSG_FOR_PCLINT_STRU        *pMsg)
{
    VOS_UINT8                           ucIsUtranSmcNeeded;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    ucIsUtranSmcNeeded = NAS_UTRANCTRL_IsUtranPsSmcNeeded();

    if (GMM_RAU_ACCEPT_IE_T3302_VALUE_FLG
        == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_T3302_VALUE_FLG))
    {                                                                           /* ��T3302IE                                */
        /* 24.008: 9.4.15.7
          In Iu mode, if this message is received without integrity protection
          the MS shall ignore the contents of this IE and use the last received value if available.
          If there is no last received value, the MS shall use the default value. */

        if ((VOS_TRUE                             == ucIsUtranSmcNeeded)
         && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE != g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect))
        {
            if (0 == g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal)
            {
                g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
            }
        }
        else
        {
            Gmm_SaveTimerValue(GMM_TIMER_T3302,
                               pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset
                               [GMM_RAU_ACCEPT_IE_T3302_VALUE] + 2]);               /* �洢T3302ʱ��                            */

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(),sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);
        }
    }
    else
    {
        /* 24.008: 9.4.15.7
          If this IE is not included in the message in A/Gb mode or
          if in Iu mode this IE is not included in an integrity protected message,
          the MS shall use the default value. */

        if ( (VOS_FALSE == ucIsUtranSmcNeeded)
          || ( (VOS_TRUE == ucIsUtranSmcNeeded)
            && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) ) )
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleRoutingAreaUpdateEPlmn
 ��������  : ����RAU Accept��Ϣ��EPLMN��Ϣ
 �������  : pstRauAcceptIe,RAU Accept��ϢIE��Ϣ
             pstMsg,RAU Accept��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : s46746
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
  5.��    ��   : 2015��6��9��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_HandleRoutingAreaUpdateEPlmn(
    GMM_MSG_RESOLVE_STRU               *pstRauAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pstMsg
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmn = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stTmpEPlmnList;


    PS_MEM_SET(&stTmpEPlmnList, 0x00, sizeof(stTmpEPlmnList));

    pstEPlmnList    = NAS_MML_GetEquPlmnList();
    pstCurrCampPlmn = NAS_MML_GetCurrCampPlmnId();

    /* ����տ���Ϣ��û��EPLMN,���浱ǰ����ΪEPLMN */
    if (GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG
        != (pstRauAcceptIe->ulOptionalIeMask
        & GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG))
    {
        stTmpEPlmnList.ucEquPlmnNum = 0x1;
        stTmpEPlmnList.astEquPlmnAddr[0] = *pstCurrCampPlmn;
    }
    else
    {
        /* ������Ϣ��EPLMN */
        NAS_GMM_DecodeEquPlmnInfoIE(GMM_MMC_ACTION_RAU,
                                pstRauAcceptIe,
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

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_PTMSI_SIGNATURE_Handling
 *  FUNCTION : Gmm_RoutingAreaUpdateHandle���������Ӷ�: PTMSI_SIGNATURE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
    1.  ŷ����   2009.06.11  �°�����
    2.��    ��   : 2011��7��27��
      ��    ��   : h44270
      �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
    3.��    ��   : 2015��6��9��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 ************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_PTMSI_SIGNATURE_Handling(GMM_MSG_RESOLVE_STRU   *pRauAcceptIe,
                                                    NAS_MSG_FOR_PCLINT_STRU          *pMsg)
{
    if (GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE_FLG
        == (pRauAcceptIe->ulOptionalIeMask
        & GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE_FLG))
    {                                                                           /* �տ���Ϣ����P-TMSI signature             */
        NAS_MML_SetUeIdPtmsiSignature(&(pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset
                   [GMM_RAU_ACCEPT_IE_PTMSI_SIGNATURE] + 1]));                                                          /* �洢P-TMSI signature                     */

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* ����UE ID���ڱ�־                        */

    }
    else
    {
        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ��UE ID���ڱ�־                          */

    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_READY_TIMER_Handling
 *  FUNCTION : Gmm_RoutingAreaUpdateHandle���������Ӷ�: READY_TIMER�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2015��6��9��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 ************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_READY_TIMER_Handling(GMM_MSG_RESOLVE_STRU   *pRauAcceptIe,
                                                    NAS_MSG_FOR_PCLINT_STRU      *pMsg,
                                                    VOS_UINT8                    *pucReadychangFLG)
{
    if (GMM_RAU_ACCEPT_IE_READY_TIMER_FLG
        == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_READY_TIMER_FLG))
    {
        *pucReadychangFLG = GMM_TRUE;
       GMM_SaveReadyTimerValue(pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset\
                [GMM_RAU_ACCEPT_IE_READY_TIMER] + 1]);
    }
    else
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg)
        {
            *pucReadychangFLG = GMM_TRUE;
            GMM_SaveReadyTimerValue(GMM_REQUESTED_READY_TIMER_VALUE);
            gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg = GMM_FALSE;
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_Handling_Local_TLLI
 *  FUNCTION : Gmm_RoutingAreaUpdateHandle���������Ӷ�: Local_TLLI�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
    1.  ŷ����   2009.06.11  �°�����
    2.��    ��   : 2011��7��27��
     ��    ��   : h44270
     �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_Handling_Local_TLLI(VOS_BOOL                bTlliUpdateFlag)
{
    VOS_UINT32                  ulNewTlli        = 0;

    if (VOS_TRUE == bTlliUpdateFlag)
    {
        GMM_CharToUlong(&ulNewTlli,
                        NAS_MML_GetUeIdPtmsi());                                /* �µ�PTMSI */
        GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);                          /* ������TLLI */
        if ( GMM_FALSE == GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI) )
        {
            GMM_LOG_WARN("Gmm_RoutingAreaUpdateHandle():Error: new TLLI assigned unsuccessfully!");
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

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_Handling_RAU_RESULT_IE
 *  FUNCTION : Gmm_RoutingAreaUpdateHandle���������Ӷ�: RAU_RESULT_IE�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2. ��    ��   : 2009��10��3��
        ��    ��   : l00130025
        �޸�����   : �������ⵥ�ţ�AT2D14889,G����ģʽI��,Combined RAU�����У�
                     ������ҪCS detach��SYSCFGʧ��
     3. ��    ��   : 2012��3��21��
        ��    ��   : z00161729
        �޸�����   : ֧��ISR�����޸�
     4. ��    ��   : 2013��1��23��
        ��    ��   : W00176964
        �޸�����   : DTS2013012290625:DCM����:ISR�����������RAU�����������RAU
     5.��    ��   : 2015��6��9��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 ************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_Handling_RAU_RESULT_IE(
                                 GMM_MSG_RESOLVE_STRU           *pRauAcceptIe,          /* ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��       */
                                 NAS_MSG_FOR_PCLINT_STRU        *pMsg,
                                 VOS_UINT8                      *pucSndCompleteFlg,
                                 VOS_BOOL                        bTlliUpdateFlag
                                 )
{
    VOS_UINT8                           ucUpdateResultValue;

    ucUpdateResultValue = (pMsg->aucNasMsg[2] >> NAS_MML_OCTET_MOVE_FOUR_BITS) & NAS_MML_OCTET_LOW_THREE_BITS;

    if ((GMM_COMBINED_RALA_UPDATED == ucUpdateResultValue)
     || (GMM_COMBINED_RALA_UPDATED_ISR_ACTIVE == ucUpdateResultValue))
    {                                                                           /* RAU�����combined RA/LA updated          */
        if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_TRUE;
        }
        else
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
        }
        Gmm_RoutingAreaUpdataAcceptCombined(pRauAcceptIe, pMsg);                /* ���ú�������combined RA/LA updated       */

        if (GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG
            == (pRauAcceptIe->ulOptionalIeMask
            & GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG))
        {                                                                       /* ��IE����                                 */
            if (GMM_MOBILE_ID_TMSI_PTMSI
                == (GMM_MOBILE_ID_TMSI_PTMSI &
                pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset
                [GMM_RAU_ACCEPT_IE_MS_IDENTITY] + 2]))
            {                                                                   /* IE_MS_IDENTITY��Я��TMSI                 */
                *pucSndCompleteFlg = GMM_TRUE;                                  /* �趨��Ҫ����RAU COMPLETE��Ϣ             */
            }
        }
    }
    else
    {
        /* ������RAUʱ��Ϊ����ע��ɹ�,����Ҫ���GS�� */
        if (VOS_FALSE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
        }

        /* ���bTlliUpdateFlag��FALSE��˵����RAU ACCEPT�ظ��յ���
           ��ʱ����Ҫ�ٴ�֪ͨMM/MMC RAU���,��Ϊ��ʱ���֪ͨ��
           RAU�������Ǵ����
        */
        if(VOS_TRUE == bTlliUpdateFlag)
        {
            Gmm_RoutingAreaUpdataAcceptRaOnly(pRauAcceptIe, pMsg);              /* ���ú�������RA only updated              */
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RoutingAreaUpdateHandle_Handling_SndComplete_Flag
 *  FUNCTION : RAU�����Ƿ���RAU COMPLETE��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle_Handling_SndComplete_Flag(
    VOS_UINT8                   ucSndCompleteFlg,
    VOS_UINT8                   ucInterRatInfoFlg
)
{
    NAS_MSG_STRU                *pSendNasMsg = VOS_NULL_PTR;
    VOS_UINT32                  ulRst;

    if (VOS_TRUE == ucSndCompleteFlg)
    {
        /* ��Ҫ��WRR��ȡInterRatInfo��Ϣ */
        if (VOS_TRUE == ucInterRatInfoFlg)
        {
            ulRst = NAS_GMM_SndRrmmInterRatHandoverInfoReq();

            if (VOS_OK == ulRst)
            {
                gstGmmCasGlobalCtrl.ucRauCmpFlg = VOS_TRUE;

                /* ��Ҫ�ȴ�WRR�ظ��󣬷���RAU COMPLETE ��Ϣ  */
                g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg = VOS_TRUE;
                g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg = VOS_FALSE;
                g_GmmInterRatInfoCtrl.ucDataLen = 0;
            }
        }

        /* G�£���Ҫ�ȴ�RABM�ظ����ٷ���RAU COMPLETE ��Ϣ  */
        if (VOS_TRUE == GMM_IsCasGsmMode())
        {
            gstGmmCasGlobalCtrl.ucRauCmpFlg = VOS_TRUE;

            /* G�£���ȴ�RABM�Ļظ� */
            gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = VOS_TRUE;
            gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_FALSE;
        }

        /* ����Ҫ�ȴ�WRR��RABM�ظ���ֱ�ӷ���RAU COMPLETE��Ϣ */
        if (VOS_FALSE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
        {
            g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg = VOS_FALSE;
            gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = VOS_FALSE;

            pSendNasMsg = Gmm_RoutingAreaUpdateCompleteMsgMake();
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

        }
    }
    else
    {
        gstGmmCasGlobalCtrl.ucRauCmpFlg = GMM_FALSE;
    }
}

/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateHandle
  Function : ����RAU ACCEPT��Ϣ
  Input    : NAS_MSG_STRU          *pMsg         ָ��NAS_MSG_STRU�ṹ��ָ��
             GMM_MSG_RESOLVE_STRU  *pRauAcceptIe ָ��GMM_MSG_RESOLVE_STRU
                                                 �ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2. ��־��  2005.03.31  NAS_IT_BUG_043��Ӧ
  3. x51137 2006/4/28 A32D02889
  4. ��    ��   : 2006��11��8��
     ��    ��   : s46746
     �޸�����   : ���ⵥ��:A32D06867
  5. ��    ��   : 2008��10��20��
     ��    ��   : o00132663
     �޸�����   : ���ⵥ��:AT2D06266, ���ӶԲ�֧��CELL NOTIFICATION�Ĵ���
  6.��    ��   : 2008��11��25��
    ��    ��   : l65478
    �޸�����   : �������ⵥ�ţ�AT2D06903��GSMģʽ�£������յ�����RAU accept��Ϣ��GMM����RAU complete
  7.��    ��   : 2010��11��29��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ��:DTS2010112900029:W��RAU������Ǩ��ʧ�ܣ��������DSCR,UE����פ��������RAU������������������RAU
  8. ��    ��   : 2011��01��27��
     ��    ��   : A00165503
     �޸�����   : ���ⵥ��: DTS2011012501578�����RAU ACCEPT��Ϣ�в�Я��IE��NPDU NUMBER LIST��
                  ��RAU COMPLETE��Ϣ�в���ҪЯ��IE��NPDU NUMBER LIST
  9.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 10.��    ��   : 2011��4��29��
    ��    ��   : c00173809
    �޸�����   : DTS2011042804013,UE������ģʽI��,ͨ������W��ģ������W����ͬRAI
                      ��С��,����W�·���绰,Ȼ��PDP����,Ȼ���ͷ�CS�绰,UE���е�����RAU
                      ��ͨ��EST_REQ������ͨ��DATE_REQ���͵�.
 11.��    ��   : 2011��10��8��
    ��    ��   : s46746
    �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��
 12.��    ��   : 2012��4��17��
     ��    ��   : z00161729
     �޸�����  : DTS2012041402264��LС���·���CS����ҵ��ͨ���ض���CS Fallback��WС��������PDP���ͷ�CS������δ��ϵͳ��Ϣ��UE���ᷢ������RAU
 12.��    ��   : 2012��05��13��
    ��    ��   : W00166186
    �޸�����   : DTS201204261955,RAU COMPLETEû�лظ�
 13.��    ��   : 2012��06��8��
    ��    ��   : z00161729
    �޸�����   : DTS2012052103216: g_GmmGlobalCtrl.ucSpecProcΪGMM_RAU_NORMAL_CS_TRANSʱδ�жϵ�ǰ����ģʽ�Ƿ�ΪA+I,ֱ����������ע�ᣬ���ӱ���
 14.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
 15.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������
 16.��    ��   : 2012��10��16��
    ��    ��   : t00212959
    �޸�����   : DTS2012082202926,CSFB��L��W��LAI��RAI�������ı䣬LAU��#13�ܾ���normal RAU�ɹ�,��������������RAU
 17.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 18.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
 19.��    ��   : 2014��7��18��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�޸�
 20.��    ��   : 2015��6��9��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
 21.��    ��   : 2015��10��14��
    ��    ��   : w00167002
    �޸�����   : DTS2015091104629:��ǰ����PDP���SM֪ͨpdp ACTIVE PENDING����ʱLAC
                 �ı䣬������RAU. RAU�ɹ����ж���PDP״̬��������ָʾû��PDP�����ġ�
                 ���������˻����PDP��������
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandle(
    GMM_MSG_RESOLVE_STRU               *pRauAcceptIe,          /* ָ��GMM_MSG_RESOLVE_STRU�ṹ��ָ��       */
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    VOS_BOOL                            bTlliUpdateFlag
)
{
    VOS_UINT8                           ucSndCompleteFlg = GMM_FALSE;                   /* �Ƿ���RAU COMPLETE��Ϣ                 */
    VOS_UINT32                          ulPDPStatus;
    VOS_UINT8                           ucReadychangFLG  = GMM_FALSE;
    VOS_UINT8                           ucOffSet;
    VOS_UINT8                           ucInterRatInfoFlg = GMM_FALSE;

    /* Added by t00212959 for DCM�����������������, 2012-8-16, begin */
    VOS_UINT8                           ucUeWDrxlength;
    VOS_UINT8                           ucWSysinfoDrxlength;
    /* Added by t00212959 for DCM�����������������, 2012-8-16, end */


    GMMSM_DATA_REQ_STRU                 *pstSmDataReqMsg = VOS_NULL_PTR;


    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_UPDATED);             /* �ø���״̬ΪGU1                          */
    gstGmmCasGlobalCtrl.ucRauCmpFlg = GMM_FALSE;                                /* Ĭ��RAU CMP���Ͳ��ȴ� */

    NAS_GMM_RoutingAreaUpdateHandle_Handling_REQUESTED_MS_INFORMATION_IE(pMsg, pRauAcceptIe, &ucSndCompleteFlg, &ucInterRatInfoFlg);

    Gmm_RoutingAreaUpdateHandle_Handling_RAU_RESULT_IE(pRauAcceptIe, pMsg, &ucSndCompleteFlg, bTlliUpdateFlag);


    Gmm_RoutingAreaUpdateHandle_T3302_Handling(pRauAcceptIe, pMsg);

    Gmm_RoutingAreaUpdateHandle_PTMSI_SIGNATURE_Handling(pRauAcceptIe, pMsg);

    NAS_GMM_HandleRoutingAreaUpdateEPlmn(pRauAcceptIe, pMsg);

    if (GMM_RAU_ACCEPT_IE_NPDU_NUMBER_FLG
        == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_NPDU_NUMBER_FLG))
    {                                                                           /* �տ���Ϣ����N-PDU Numbers                */
        g_GmmRauCtrl.ucNpduCnt = pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset
                                 [GMM_RAU_ACCEPT_IE_NPDU_NUMBER] + 1];          /* �洢N-PDU Numbers�ĸ���                  */
        Gmm_MemCpy(&g_GmmRauCtrl.aucNpduNum[0],
                   &pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset
                   [GMM_RAU_ACCEPT_IE_NPDU_NUMBER] + 2],
                   g_GmmRauCtrl.ucNpduCnt);                                     /* �洢N-PDU Numbers                        */

        ucSndCompleteFlg = GMM_TRUE;
        g_GmmRauCtrl.bNpduPresentInRauAccFlg = VOS_TRUE;
    }
    else
    {
        g_GmmRauCtrl.ucNpduCnt = 0;                                             /* �������� N-PDU NUMBER                  */
        g_GmmRauCtrl.bNpduPresentInRauAccFlg = VOS_FALSE;
    }

    Gmm_RoutingAreaUpdateHandle_READY_TIMER_Handling(pRauAcceptIe, pMsg, &ucReadychangFLG);

    if (GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION_FLG
        == (pRauAcceptIe->ulOptionalIeMask
            & GMM_RAU_ACCEPT_IE_CELL_NOTIFICATION_FLG))
    {
        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_TRUE;                         /* cell notificaion��Ч��־ */
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellNotifyFlg = GMM_FALSE;                        /* cell notificaion��Ч��־ */
    }

    if (GMM_RAU_ACCEPT_IE_PTMSI_FLG
        == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_PTMSI_FLG))
    {                                                                           /* �տ���Ϣ����P-TMSI                       */
        Gmm_MemCpy(NAS_MML_GetUeIdPtmsi(),
                   &pMsg->aucNasMsg[pRauAcceptIe->aucIeOffset
                   [GMM_RAU_ACCEPT_IE_PTMSI] + 3],
                   NAS_MML_MAX_PTMSI_LEN);                                                          /* �洢P-TMSI                               */
        ucSndCompleteFlg = GMM_TRUE;                                            /* �û�COMPLETE��Ϣ��־                     */

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;              /* ����UE ID���ڱ�־                        */
    }

    if (GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS_FLG
        == (pRauAcceptIe->ulOptionalIeMask & GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS_FLG))
    {
        ucOffSet = pRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_PDP_CONTEXT_STATUS];
        ulPDPStatus = (pMsg->aucNasMsg[(ucOffSet+2)]
                    | (pMsg->aucNasMsg[(ucOffSet+3)]<<8))& 0x0000FFFF;

        /*2G�£�����յ���RAU ACCEPT,��ʱ����Normal Service�£���ôʵ�ʲ����κβ���*/
        if (bTlliUpdateFlag != VOS_FALSE)
        {
            Gmm_SndSmPdpStatusInd(ulPDPStatus, GMM_SM_CAUSE_RAU_ACCEPT);

            if (0x0 == ulPDPStatus)
            {
                if (GMM_MSG_HOLD_FOR_SERVICE
                    == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
                {
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
                    Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
                    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                }
                if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    && ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProcHold)
                    || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProcHold)))
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
                    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                }

                /* ���֮ǰ��PDP����,��ʱPDP��ȥ������,��Ҫ��������PDPȥ��������,���������ȥ���������SM */
                if (GMM_MSG_HOLD_FOR_SM == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
                {
                    /* �õ��������Ϣ */
                    pstSmDataReqMsg = (GMMSM_DATA_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

                    if (SM_ACT_PDP_CONTEXT_REQ != NAS_GMM_GetGmmSmDataReqMsgType(&(pstSmDataReqMsg->SmMsg)))
                    {
                        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RoutingAreaUpdateHandle(): Clear cached SM data Req");

                        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
                        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
                    }
                }
            }
        }
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                        /* ֪ͨRRC NAS����Ϣ�仯                    */

    /* 2Gģʽ�����µ�local TLLIֵ */
    if ((GMM_TRUE==GMM_IsCasGsmMode())
      &&(GMM_UEID_P_TMSI==(g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
         & GMM_UEID_P_TMSI))
       )
    {
        Gmm_RoutingAreaUpdateHandle_Handling_Local_TLLI(bTlliUpdateFlag);
    }

    Gmm_RoutingAreaUpdateHandle_Handling_SndComplete_Flag(ucSndCompleteFlg, ucInterRatInfoFlg);

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
    }

    /* Modified by t00212959 for DCM�����������������, 2012-8-14, begin */
    ucUeWDrxlength      = NAS_MML_GetUeUtranPsDrxLen();
    ucWSysinfoDrxlength = NAS_MML_GetWSysInfoDrxLen();
    if (ucWSysinfoDrxlength != ucUeWDrxlength)
    {                                                                           /* DRX���������仯                          */
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_DRX);                          /* ֪ͨRRCЭ�̺��PS��DRX����               */
    }
    /* Modified by t00212959 for DCM�����������������, 2012-8-14, end */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_RoutingAreaUpdateHandle_Under_Gsm(ucInterRatInfoFlg, ucReadychangFLG, bTlliUpdateFlag, ucSndCompleteFlg);
    }
    else
    {
        Gmm_RoutingAreaUpdateHandle_Under_W();
    }


    /* ��ucRauCauseΪGMM_RAU_FOR_INTERSYSTEMʱ,֪ͨRABM��RAU���Ͳ�ͬ(RAU����Ϊϵͳ���л�),
       ����������ԭ��ֵ���͸�RABM��RAU������ͬ(������RAU),RABM�����RAU�����ͽ���״̬��Ǩ��,
       �������RAUԭ��ΪGMM_RAU_FOR_INTERSYSTEMʱ, �������ucRauCause */
    if (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
    {
        /* �˱�־��¼����ϵͳ����ѡ�����л�ʱ,RAI��ͬʱ,����������������ʱ��Ҫ����RAU.
           ��Ϊ���ô˺���ʱRAU�Ѿ����,������Ҫ����˱�־ */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* CSͨ���е�NORMAL RAU                     */
        if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {                                                                       /* CS����ͨ����                             */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific ���̱�־          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandle:INFO: specific procedure ended");
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;                          /* �����ǰRAU�Ƿ�������RAU��־             */

            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                 /* RAU�Ѿ���������������RAU��־*/
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                /*  GMM����RAU���������MM��LU���̵ı�־   */

            if (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);          /* ����RAU����                              */
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
        }
        else
        {                                                                       /* CS��ͨ����                               */
            g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                 /* �����ǰ���е�specific ���̱�־          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandle:INFO: specific procedure ended");
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_RAU_NORMAL;               /* ��¼CSͨ���е�����                       */
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;                          /* �����ǰRAU�Ƿ�������RAU��־             */
        }
    }
    else
    {                                                                           /* GMM_RAU_NORMAL                           */
        g_GmmGlobalCtrl.ucSpecProc          = GMM_NULL_PROCEDURE;                     /* �����ǰ���е�specific ���̱�־          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandle:INFO: specific procedure ended");
        g_GmmRauCtrl.ucPeriodicRauFlg       = GMM_FALSE;                              /* �����ǰRAU�Ƿ�������RAU��־             */
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateHandleFollowOn
  Function : RAU��������follow on
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����

    2. ��    ��   : 2010��7��17��
       ��    ��   : ŷ����
       �޸�����   : DTS2010071601574, ���ڻ����RABM�Ľ�������Ӧ���ú���
                    Gmm_ServiceRequestMsgMake_ForData����service request��Ϣ��
    3.��    ��   : 2012��8��1��
      ��    ��   : A00165503
      �޸�����   : DTS2012072705055: GMM��SM֮�������������ӽ���ָʾԭ��, SM��
                   �ݸ�ԭ������T3380, T3381��T3390
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateHandleFollowOn(VOS_VOID)
{
    NAS_MSG_STRU          *pSendNasMsg;                                         /* �����洢������service request��Ϣ        */
    GMMSM_DATA_REQ_STRU   *pSmDataReqMsg;

    switch (g_GmmGlobalCtrl.ucSpecProcHold)
    {                                                                           /* ������specific����                       */

    case GMM_SERVICE_REQUEST_DATA_IDLE:
    case GMM_SERVICE_REQUEST_DATA_CONN:
        /* RABM������ Service Request ���̱� Rau �����жϣ������� Follow On
           ��־������� Rau ���������յ� RABM �ؽ���Ϣ����ô�� Rau ����֮��
           ���� Follow On ��־��ʱ����Ҫ������棬��������������������
           Service Request ���󣬼� Service Request ���̽���֮���ȥ������
           ����Ϣ��*/
        if (GMM_MSG_HOLD_FOR_SERVICE ==
            (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;  /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL;
        }

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {                                                                       /* 2G�²���Ҫ���� RAB �ؽ�                  */
            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                /* ���������specific���̱�־               */
            return;
        }

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_DELAYED);

        break;

    case GMM_SERVICE_REQUEST_SIGNALLING:
        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {
            if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
            {
                Gmm_SndSmsEstCnf();
            }
            else
            {
                g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

                GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RoutingAreaUpdateHandleFollowOn:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

                g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_SIGNALLING;    /* �洢��ǰ������                           */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandleFollowOn:INFO: SR(signaling) procedure started");

                pSendNasMsg = Gmm_ServiceRequestMsgMake();                      /* ����service request��������              */

                Gmm_SndRrmmEstReq(g_GmmGlobalCtrl.ulEstCause,
                                  GMM_RRC_IDNNS_UNKNOWN,
                                  pSendNasMsg);                                 /* ����service request(signalling)          */

                Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);

                return;
            }

        }
        if (GMM_MSG_HOLD_FOR_SM
            ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
        {                                                                       /* ����б�����SmDataReqԭ��                */
            pSmDataReqMsg =
                (GMMSM_DATA_REQ_STRU*)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;   /* �õ���������Ϣ                           */

            if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
            {
                NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RoutingAreaUpdateHandleFollowOn(): Process cached SM data Req");

                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                    &pSmDataReqMsg->SmMsg);                                     /* ����RRMM_DATA_REQ(CM�Ӳ����Ϣ�׵�ַ)    */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;   /* ���������־                             */
                Gmm_MemFree(pSmDataReqMsg);                                     /* �ͷű����SM��Ϣ                         */

                NAS_GMM_SndSmSigConnInd();
            }
            else
            {
                /* ��SM�Ľ���ԭ��ֵת��ΪRRC�Ľ���ԭ��ֵ */
                NAS_GMM_TransferSmEstCause2RrcEstCause(((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->ulEstCause,
                                                        &g_GmmGlobalCtrl.ulEstCause);

                g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

                GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RoutingAreaUpdateHandleFollowOn:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

                g_GmmServiceCtrl.ucSmFlg = GMM_TRUE;
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
                g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_SIGNALLING;    /* �洢��ǰ������                           */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandleFollowOn:INFO: SR(signaling) procedure started");

                pSendNasMsg = Gmm_ServiceRequestMsgMake();                      /* ����service request��������              */

                Gmm_SndRrmmEstReq(g_GmmGlobalCtrl.ulEstCause, GMM_RRC_IDNNS_UNKNOWN, pSendNasMsg);          /* ����service request(signalling)          */
                Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            }
        }
        break;

    case GMM_DETACH_COMBINED:
        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */
        if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        {
            Gmm_MsInitNormalDetach(MMC_GMM_PS_CS_DETACH);
        }
        else
        {
            Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
        }
        break;

    case GMM_DETACH_NORMAL:
    case GMM_DETACH_NORMAL_NETMODE_CHANGE:
        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */
        Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
        g_GmmGlobalCtrl.ucSpecProc = g_GmmGlobalCtrl.ucSpecProcHold;
        break;

    case GMM_DETACH_WITH_IMSI:
        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */
        Gmm_MsInitNormalDetach(MMC_GMM_CS_DETACH);
        break;

    default:
        break;
    }
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* ���������specific���̱�־               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateHandleFollowOn:INFO: specific procedure ended");
}

/*******************************************************************************
  Module   : Gmm_RcvRoutingAreaUpdateAcceptMsg
  Function : ���տտ���Ϣ�տ���ϢRAU ACCEPT�Ĵ���
  Input    : NAS_MSG_STRU *pMsg     ָ��NAS_MSG_STRU�ṹ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2006��11��1��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D06572
  3.��    ��   : 2007��05��11��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D10713
  4.��    ��   : 2007��06��16��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ�ţ�A32D11635
  5.��    ��   : 2008��11��25��
    ��    ��   : l65478
    �޸�����   : �������ⵥ�ţ�AT2D06903��GSMģʽ�£������յ�����RAU accept��Ϣ��GMM����RAU complete
  6.��    ��   : 2010��01��03��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�AT2D17661,NAS R7Э��������������PS ���������ͷŶ�ʱ��T3340
  7.��    ��   : 2010��5��10��
    ��    ��   : o00132663
    �޸�����   : AT2D18802,��PDP Context���ڵ�����£�������T3340
  8.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  9.��    ��   : 2011��10��8��
    ��    ��   : s46746
    �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��

  10.��    ��   : 2012��1��08��
     ��    ��   : z00161729
     �޸�����   : V7R1 PhaseIV�׶ε���,TIN typeֱ�Ӹ���MMLȫ�ֱ�����дnv��ͨ����Ϣ֪ͨMMC��MMC����
  11.��    ��   : 2012��2��27��
     ��    ��   : z00161729
     �޸�����   : V7R1 C50 ֧��ISR�޸�
  12.��    ��   : 2012��3��27��
     ��    ��   : w00166186
     �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
  13. ��    ��   : 2012��6��12��
     ��    ��   : w00166186
     �޸�����   : AT&T&DCM��Ŀ
  14.��    ��   : 2012��8��13��
     ��    ��   : L65478
     �޸�����   : DTS2012080301606:ע��ʧ�ܺ����ֶ�����ʧ��
  15.��    ��   : 2012��8��14��
     ��    ��   : t00212959
     �޸�����   : DCM�����������������
  16.��    ��   : 2013��7��24��
     ��    ��   : y00245242
     �޸�����   : VoLTE�������ϱ�UTRAN network capability information
  17.��    ��  :2014��01��09��
     ��    ��  :l65478
     �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ

  18.��    ��   : 2014��01��10��
     ��    ��   : w00176964
     �޸�����   : VoLTE_PhaseIII��Ŀ

  19.��    ��   : 2014��2��18��
      ��    ��   : l00215384
      �޸�����   : DTS2014021006453��RAU�ɹ����Ȩ�ܾ���������
  20.��    ��  : 2014��08��4��
     ��    ��  : b00269685
     �޸�����  : ����RAUʱ�յ�ps only accept������csʧ�ܣ�ps�ɹ�����
  21.��    ��   : 2014��9��30��
      ��    ��   : z00161729
      �޸�����   : DTS2014073003377: attach�ɹ��������·�����ptmsi��ͨ��nas comm info֪ͨ������ptmsi���ϵģ����º���ps service����#10�ܾ�
  22.��    ��   : 2014��12��17��
     ��    ��   : b00269685
     �޸�����   : ��Rau�ɹ���ֹͣ3314��ʱ��
  23.��    ��   : 2015��6��5��
     ��    ��   : z00161729
     �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRoutingAreaUpdateAcceptMsg(
                                       NAS_MSG_FOR_PCLINT_STRU *pMsg
                                       )
{
    GMM_MSG_RESOLVE_STRU            RauAcceptIe;
    NAS_MSG_STRU                   *pGmmStatus;
    VOS_BOOL                        bTlliUpdateFlag = VOS_TRUE;
    VOS_UINT8                       i,j;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;

    NAS_MML_RAI_STRU                   *pstLastSuccRai = VOS_NULL_PTR;

    VOS_UINT8                           ucUpdateResultValue;

    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList;

    NAS_MML_PLMN_ID_STRU               stMmcPlmnId;

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    PS_MEM_SET(&stMmcPlmnId, 0, sizeof(stMmcPlmnId));

    pstEmergencyNumList     = NAS_MML_GetEmergencyNumList();

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;

    Gmm_MemSet(&RauAcceptIe, 0, sizeof(GMM_MSG_RESOLVE_STRU));

    if ((GMM_TRUE == GMM_IsCasGsmMode())
        && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        bTlliUpdateFlag = VOS_FALSE;
    }
    else if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
    {                                                                           /* GMM״̬����GMM_RAU_INITIATED             */

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateAcceptMsg:WARNING: RAU ACCEPT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

        return;
    }
    else if (0x20 != (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ��specific���̲���RAU����            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateAcceptMsg:WARNING: Current Specific Process is not RAU process");
        return;
    }
    else
    {
    }

    g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;

    if (GMM_MSG_LEN_RAU_ACCEPT > pMsg->ulNasMsgSize)
    {                                                                           /* ��Ϣ����                                 */

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateAcceptMsg:WARNING: RAU ACCEPT is too short");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

        return;
    }

    if (GMM_FAILURE == Gmm_IECheck_RauAccept(pMsg))                             /* ���ú����ж�RAU ACCEPT��Ϣ����ȷ��       */
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateAcceptMsg:WARNING: RAU ACCEPT is semantically incorrect");
        pGmmStatus =
            Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }
    if (GMM_FALSE == Gmm_AttachRauAcceptJudgeRai(pMsg))
    {                                                                           /* RAU ACCEPT�е�RAI��ϵͳ��Ϣ��RAI��һ��   */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRoutingAreaUpdateAcceptMsg:WARNING: RAI in RAU ACCEPT is different with current RAI");
        pGmmStatus =
            Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    NAS_GMM_ResetRejCauseChangedCounter();

    /* �ȸ���mandatory Periodic RA update timer IE t3312��ֵ��
      Gmm_RoutingAreaUpdateResolveIe����� T3312 extended value IE�ٸ���t3312��ֵ */
    Gmm_SaveTimerValue(GMM_TIMER_T3312, pMsg->aucNasMsg[3]);                    /* �洢T3312ʱ��                            */

    Gmm_RoutingAreaUpdateResolveIe(&RauAcceptIe, pMsg);                         /* ���ú�������RAU ACCEPT��Ϣ��IE           */
    NAS_Gmm_SaveRauAcceptGmmCause(pMsg, &RauAcceptIe);
    /* Added by t00212959 for DCM�����������������, 2012-8-14, begin */
    /*RAU �ɹ�������Drx����Я��״̬*/
    NAS_MML_SetPsRegContainDrx(g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx);

    /* ��ά�ɲ�������Ϣ��ӡ */
    NAS_GMM_LogPsRegContainDrxInfo(g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx);

    /* Added by t00212959 for DCM�����������������, 2012-8-14, end */

    if (GMM_RAU_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG
        == (RauAcceptIe.ulOptionalIeMask
                & GMM_RAU_ACCEPT_IE_EMERGENCY_NUMBER_LIST_FLG))
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

                for (j=0; j < NAS_MML_EMERGENCY_NUM_MAX_LEN; j++)
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


    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ֹͣTimer3330                            */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ֹͣTimer3311                            */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_T3316);                                             /* ֹͣT3316                                */

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

    /* �����Ȩ���ȫ�ֱ��� */
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��"RES���ڱ�־ "��Ϊ0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* ��"RAND���ڱ�־ "��Ϊ0                   */

    ucUpdateResultValue = (pMsg->aucNasMsg[2] >> NAS_MML_OCTET_MOVE_FOUR_BITS) & NAS_MML_OCTET_LOW_THREE_BITS;


#if   (FEATURE_ON == FEATURE_LTE)
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    if ( NAS_MML_TIN_TYPE_PTMSI != pstRplmnCfgInfo->enTinType)
    {
        NAS_GMM_UpdateTinType_RauAccept(pstRplmnCfgInfo->enTinType,
                            pstRplmnCfgInfo->aucLastImsi, ucUpdateResultValue);
    }
#endif

    Gmm_RoutingAreaUpdateHandle(&RauAcceptIe, pMsg, bTlliUpdateFlag);                            /* ����RAU ACCEPT�е�IE                     */


    /* ȡ�õ�ǰע��ɹ���RAI��Ϣ��ע��:����Ϣ�Ļ�ȡҪ���ڽ�����RAI��Ϣ֮�� */
    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();

    /* ��GUģ��RPlmn��Ϣ�����˸ı䣬�򱣴�RPlmn��Ϣ��ȫ�ֱ����У������µ�NVIM�� */
    if ( VOS_TRUE == NAS_GMM_IsGURplmnChanged( &(pstLastSuccRai->stLai.stPlmnId),
                                               NAS_MML_GetCurrNetRatType()) )
    {
        /* ����RPlmn��Ϣ��ȫ�ֱ����� */
        NAS_MML_UpdateGURplmn( &(pstLastSuccRai->stLai.stPlmnId),
                               NAS_MML_GetCurrNetRatType() );

        /* ��ȫ�ֱ����е�RPlmn��Ϣ���µ�NVIM�� */
        NAS_GMM_WriteRplmnWithRatNvim( NAS_MML_GetRplmnCfg() );
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg)
    {                                                                           /* �ȴ�����RAU                              */
        if (GMM_TRUE == g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg)
        {                                                                       /* ��Ҫ����MM����LU                         */
            if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
                && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
            {                                                                   /* ����ģʽ�ı�                             */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
                g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
                g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
                return;
            }
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
        return;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == ulT3423StatusChgNeedRegFlg)
    {
        /* ��Ҫ���T3423��ʱ��״̬�������ٴ��յ�ϵͳ��Ϣ��ᷴ��������RAU */
        NAS_MML_SetT3423Status(NAS_MML_TIMER_STOP);
        NAS_MML_SetT3412Status(NAS_MML_TIMER_STOP);
    }

#endif

    /*����Ƿ���Ҫ����T3340��ʱ�����RRC��·���ͷ� */
    NAS_GMM_CheckIfNeedToStartTimerT3340();

    /*����follow on ������������¼� */
    NAS_GMM_HandleDelayedEvent();

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
    pstAuthRejInfo->ucHplmnPsAuthRejCounter = 0;
    return;
}
/*******************************************************************************
  Module   : Gmm_SndRoutingAreaUpdateReq
  Function : ����RAU REQUEST
  Input    : VOS_UINT8 ucUpdataType         ����RAU REQUEST������
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
    2.��    ��   : 2006��9��13��
      ��    ��   : liurui id:40632
      �޸�����   : �������ⵥ�ţ�A32D05874
    3.��    ��   : 2009��01��03��
      ��    ��   : l65478
      �޸�����   : �������ⵥ�ţ�AT2D07726,û��֪ͨLLC�����㷨
    4.��    ��    : 2009��03��18��
      ��    ��    : l65478
      �޸�����    : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
    5.��    ��   : 2009��05��23��
      ��    ��   : L65478
      �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
    6.��    ��   : 2009��06��30��
      ��    ��   : l65478
      �޸�����   : ���ⵥ��AT2D12655,�������LLC�������͵Ĵ���
    7.��    ��   : 2010��9��09��
      ��    ��   : l65478
      �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
    8.��    ��   : 2011��01��07��
      ��    ��   : A00165503
      �޸�����   : ���ⵥ�ţ�DTS2011010703265��GPRSС��PDP�����ѡ��GSM ONLYС
                   ����PDPȥ�����ѡ��ԭGPRSС�����һ��PDP����ʧ��
    9.��    ��   : 2011��04��25��
      ��    ��   : f00179208
      �޸�����   : ���ⵥ�ţ�DTS2011042501657��MTS�����£�3G��2G��ͬLAI��RAI����ϵͳ��ѡ
                   ʱ�������Գ���RAUʧ�ܣ�����PDPȥ����
   10.��     ��  : 2011��4��29��
      ��    ��   : c00173809
      �޸�����   : DTS2011042804013,UE������ģʽI��,ͨ������W��ģ������W����ͬRAI
                   ��С��,����W�·���绰,Ȼ��PDP����,Ȼ���ͷ�CS�绰,UE���е�����RAU
                   ��ͨ��EST_REQ������ͨ��DATE_REQ���͵�.
   11.��     ��  : 2011��9��26��
      ��    ��   : c00173809
      �޸�����   : DTS2011092001088,GCF 44.2.2.2.4����ʧ��
   16.��    ��   : 2012��2��15��
      ��    ��   : w00167002
      �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����������ǰ����CSFBҵ���־����ֻ��RAU
   17.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
   18.��    ��   : 2012��4��17��
     ��    ��   : z00161729
     �޸�����  : DTS2012041402264��LС���·���CS����ҵ��ͨ���ض���CS Fallback��WС��������PDP���ͷ�CS������δ��ϵͳ��Ϣ��UE���ᷢ������RAU
   12.��     ��  : 2012��5��17��
      ��    ��   : w00166186
      �޸�����   : DTS2012051205814,L->G��ѡ��RAU����ʧ��
   13.��    ��   : 2012��06��8��
      ��    ��   : z00161729
      �޸�����  : DTS2012052103216:����ģʽIʱ��g_GmmGlobalCtrl.ucSpecProcΪGMM_RAU_NORMAL_CS_TRANS
   14.��    ��   : 2012��07��27��
      ��    ��   : z40661
      �޸�����  : DTS2012071603415:L2U �ض�����U������ԭ�������interrat cell reselection����������registration��Ӱ��IOT
   15.��    ��   : 2012��10��22��
      ��    ��   : t00212959
      �޸�����   : DTS2012101907218:NAS�����㷢��RAU����ʱ��Establishment cause����Э��дΪRegistration
   16.��    ��   : 2012��10��25��
      ��    ��   : t00212959
      �޸�����   : DTS2012102403382,RAU��,����ͷ�ԭ��ֵ,�����п��ܻ����RAU
   17.��    ��   : 2013��3��30��
      ��    ��   : l00167671
      �޸�����   : �����ϱ�AT�������������C��
   18.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_SndRoutingAreaUpdateReq(
                                 VOS_UINT8 ucUpdataType                         /* ����RAU REQUEST������                    */
                                 )
{
    NAS_MSG_STRU                               *pSendNasMsg = VOS_NULL_PTR;                                /* ����NAS_MSG_STRU���͵�ָ�����           */
    NAS_MML_RAI_STRU                           *pstLastSuccRai;
    GMM_RAI_STRU                                stGmmRai;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                  ulPtmsiMappedFlag;
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

#if (FEATURE_ON == FEATURE_LTE)
    ulPtmsiMappedFlag = NAS_Gmm_IsPtmsiMappedFromGuti();
#endif


#if (FEATURE_ON == FEATURE_LTE)
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        /* CSҵ�����������ģʽI,��PSע��ɹ���Ҳ��Ҫ����COMBINED RAU */
        if ( GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod )
        {
            NAS_GMM_SetSpecProcInCsTrans(GMM_RAU_NORMAL);

            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;
        }
        else
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        }


        /* ����CSFBҵ��ʱ�����������ϵ�RAU,�����Ϊֻ����RAU */
        if ( (GMM_COMBINED_RALA_UPDATING == ucUpdataType)
          || (GMM_COMBINED_RALAU_WITH_IMSI_ATTACH == ucUpdataType) )
        {
            ucUpdataType = GMM_RA_UPDATING;
        }

    }
#endif

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        if ((GMM_COMBINED_RALA_UPDATING == ucUpdataType)
            || (GMM_COMBINED_RALAU_WITH_IMSI_ATTACH == ucUpdataType))
        {
            ucUpdataType = GMM_RA_UPDATING;
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
    }

    if (GMM_PERIODC_UPDATING != ucUpdataType)
    {
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
    }

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */

    /* deleted by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    GMM_CasFsmStateChangeTo(GMM_ROUTING_AREA_UPDATING_INITIATED);

    /*24008_CR1906R2_(Rel-11)_C1-113744 Stopping of timer T3311 and T3302 24008
    4.7.5.1.1�½���������:
    To initiate the normal routing area updating procedure, the MS sends the message
    ROUTING AREA UPDATE REQUEST to the network, starts timer T3330 and changes to state
    GMM-ROUTING-AREA-UPDATING-INITIATED. If timer T3302 is currently running, the MS
    shall stop timer T3302. If timer T3311 is currently running, the MS shall stop timer T3311.
    4.7.5.2.1�½���������:
    If timer T3302 is currently running, the MS shall stop timer T3302. If timer T3311 is
    currently running, the MS shall stop timer T3311.*/
    Gmm_TimerStop(GMM_TIMER_T3311);
    Gmm_TimerStop(GMM_TIMER_T3302);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_SndRoutingAreaUpdateReq:NORMAL: STATUS IS GMM_ROUTING_AREA_UPDATING_INITIATED");

    g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

    /* ���� Rau ʱ���ж��Ƿ����ϲ�ҵ������У������� Follow-On ��־ */

    if ((GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        ||(GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
        || (GMM_MSG_HOLD_FOR_SMS
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS)))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

    }

    /* ����Ƿ���Ҫ��RAU����DETACH����*/
    if (VOS_TRUE == g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmDetachCtrl.ucDetachProc;
    }

    /* ����Ƿ���Ҫ��RAU����Service Request����*/
    if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmServiceCtrl.ucServiceRequestProc;
    }

    pSendNasMsg = Gmm_RoutingAreaUpdateRequestMsgMake(ucUpdataType);            /* ����RAU REQUEST��Ϣ                      */

    gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;                                /* ϵͳ��ϢҪ���RAU���̱�־��� */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

        if ( (GMM_FALSE == Gmm_Compare_Rai(&stGmmRai, &g_GmmGlobalCtrl.SysInfo.Rai))
          || (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED != enPsUpdateStatus)
#if (FEATURE_ON == FEATURE_LTE)
          || (VOS_TRUE == ulPtmsiMappedFlag)
#endif
          )
        {
            GMM_UpdateSysTlli(GMM_FOREIGN_TLLI);                                    /* ���foreign TLLI */

            if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
            {
                if (GMM_FALSE == GMM_AssignModifyTlli(gstGmmCasGlobalCtrl.ulTLLI,
                                                      gstGmmCasGlobalCtrl.ucflgTLLI))
                {
                    GMM_LOG_WARN("Gmm_SndRoutingAreaUpdateReq():Error: new TLLI assigned unsuccessfully!");
                }
            }
            else
            {
                GMM_AssignSysTlli();
            }
        }
        else
        {
            if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
            {
                GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                GMM_AssignSysTlli();
            }
            else if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                            NAS_MML_GetCurrNetRatType())
            {
                GMM_UpdateSysTlli(GMM_LOCAL_TLLI);
                GMM_FreeOldTlli();
                gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
            }
            else
            {
            }
        }

        if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcSuspendReq();                                             /* ֹͣLLC���ݴ��� */
        }

        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;

        if (VOS_FALSE == g_GmmGlobalCtrl.ucDetachAcceptedFlg )
        {
            /* send LLC Abort Req to delete the saved data */
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
        }

        /* �ڷ���RAUʱ��Ҫ��L2���Է���GMM��������Ϣ��������Ҫ֪ͨL2�ָ������� */
        GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
    }

    /* �����㷢�͵Ľ���ԭ��ֵ����Э�飬��дΪע��*/
    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��PS��������                             */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);              /* ��RRMM_DATA_REQ����RAU REQUEST��Ϣ       */
        Gmm_TimerStart(GMM_TIMER_T3330);                                        /* ����Timer3330                            */
    }
    else
    {
        Gmm_SndRrmmEstReq(RRC_EST_CAUSE_REGISTRATION,
                          GMM_RRC_IDNNS_UNKNOWN,
                          pSendNasMsg);                                         /* ��RRMM_EST_REQ����RAU REQUEST��Ϣ        */

        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    if ((GMM_RAU_NORMAL             != g_GmmGlobalCtrl.ucSpecProc)
        && (GMM_RAU_NORMAL_CS_TRANS != g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* RAU���Ͳ���normal NORMAL                 */
        NAS_GMM_SndMmCombinedRauInitiation();                                      /* ����MMCGMM_COMBINED_RAU_INITIATIONԭ ��
                                                                                 * ��MMC                                    */
    }
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_RAU_REQ,
                    (VOS_VOID *)&ucUpdataType,
                    NAS_OM_EVENT_RAU_REQ_LEN);

    /* ����ͷ�ԭ��ֵ,��������(�ͷ�ԭ��ֵΪ#5)��U->Lʧ�ܻ��˺��п��ܶ���RAU*/
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcStartReqInNull
 ��������  : ����RAU REQUEST
 �������  : ucUpdataType:����RAU REQUEST������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
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
  5.��    ��   :2013��11��19��
    ��    ��   :l65478
    �޸�����   :DTS2013112003014�ڷ���RAUʱ,�������֪ͨLL�ָ�����
  6.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������
  7.��    ��   : 2014��9��4��
    ��    ��   : b00269685
    �޸�����   : DTS2014083001793:�ڸ�LL����suspendǰ��Ҫ���ж��Ƿ���ָ��

*****************************************************************************/

VOS_VOID NAS_GMM_SndRoutingAreaUpdateReq(
    VOS_UINT8                           ucUpdataType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    VOS_UINT32                          ucIsSupportLteCapaFlg;

    VOS_UINT8                           ucLDisabledRauUseLSecuInfoFlag;

    ucLDisabledRauUseLSecuInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();

    ucIsSupportLteCapaFlg  = NAS_MML_IsSupportLteCapability();

    /* 1��L disable״̬��syscfg�������ò�֧��L����ȫ�ֱ�����¼GAS����㷢�͵�MS Radio Access capability IE��֧��LTE�ģ�
       2��L enalbe״̬��syscfg����֧��L,��ȫ�ֱ�����¼GAS����㷢�͵�MS Radio Access capability IE�ǲ�֧��LTE�ģ�
       ��Ҫ������ʱ���ȴ�GAS������ϱ����µ�MS Radio Access capability IE��Ϣ*/
    if ( ucIsSupportLteCapaFlg != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs)
    {
        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO);
        NAS_GMM_SetRauUpdateType(ucUpdataType);
        Gmm_ComStaChg(GMM_ROUTING_AREA_UPDATING_INITIATED);

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
            {
                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcSuspendReq();                                             /* ֹͣLLC���ݴ��� */
                }
                gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;
            }
        }

        return;
    }
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && (VOS_FALSE == gstGmmSuspendCtrl.ucGetLteSecContext)
     && ((VOS_TRUE == ucIsSupportLteCapaFlg)
      || (VOS_TRUE == ucLDisabledRauUseLSecuInfoFlag)))
    {
        if ( VOS_TRUE == NAS_GMM_GetLmmSecInfoFlg() )
        {
            return;
        }

        NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        NAS_GMM_SetRauUpdateType(ucUpdataType);

        NAS_GMM_SetLmmSecInfoFlg(VOS_TRUE);

        Gmm_ComStaChg(GMM_ROUTING_AREA_UPDATING_INITIATED);

        /* ��Lģ����GMM_LMM_RESEL_SECU_INFO_REQ */
        NAS_GMM_SndLmmReselSecuInfoReq();

        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
            {
                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcSuspendReq();                                             /* ֹͣLLC���ݴ��� */
                }
                gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;
            }
        }
    }
    else
#endif
    {
        Gmm_SndRoutingAreaUpdateReq(ucUpdataType);
    }

}

/*******************************************************************************
  Module   : Gmm_PeriodRoutingAreaUpdateType
  Function : ��д�����Ե�RAU������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/
VOS_VOID Gmm_PeriodRoutingAreaUpdateType(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS��SIM��Ч                              */

        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)

        {                                                                       /* CS���Ѿ�ע��                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {                                                                   /* CS����ͨ����                             */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;           /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_PeriodRoutingAreaUpdateType:INFO: normal RAU procedure during CS transaction started");
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
            }
            else
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;                  /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_PeriodRoutingAreaUpdateType:INFO: combined RAU procedure started");
            }
        }
        else
        {                                                                       /* CS��ûע��                               */
            if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
            {                                                                   /* CS��ATTACH����ֹ                         */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                    /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_PeriodRoutingAreaUpdateType:INFO: normal RAU procedure started");
            }
            else
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;          /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_PeriodRoutingAreaUpdateType:INFO: combined RAU with IMSI attach procedure started");
            }
        }
    }
    else
    {                                                                           /* SIM��Ч                                  */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                            /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_PeriodRoutingAreaUpdateType:INFO: normal RAU procedure started");
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_RoutingAreaUpdateInitiate
  Function : RAU���ܵ���ں���
  Input    : VOS_UINT8 ucUpdataType  RAU������
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2006��11��8��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D06867
  3.��    ��   : 2010��11��6��
    ��    ��   : w00166186
    �޸�����   : ���ⵥ��:DTS2010110500511,G->W�������RAU
  4.��    ��   : 2011��7��25��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��2��15��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����������ǰ����CSFBҵ���־����ֻ��RAU
  6.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  7.��    ��   : 2012��6��4��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL�������޸ģ�L->G��CCO,����rau����ΪGMM_COMBINED_RALAU_WITH_IMSI_ATTACH��
                 ��������Ӧ��T3330��ʱ������rau����ΪGMM_COMBINED_RALA_UPDATING��һ��
  8.��    ��   : 2012��06��08��
    ��    ��   : L65478
    �޸�����   : DTS2012060805375:��#13,#15ʱ��GU�·����RAU���ʹ���
  9.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 10.��    ��   : 2014��6��17��
    ��    ��   : s00217060
    �޸�����   : DTS2014061003286:RAU��������3311��ʱ����ʱ��־
 11.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateInitiate(
                                   VOS_UINT8 ucUpdataType                       /* RAU������                                */
                                   )
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    VOS_UINT8                           ucCsRestrictRegister;

    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();
    enCurRat = NAS_MML_GetCurrNetRatType();

    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        || (GMM_NULL == g_GmmGlobalCtrl.ucState))
    {                                                                           /* PS��û��ע��                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateInitiate:WARNING: PS domain hasn't register");
        return;
    }
    /*RAU��������3312��ʱ����ʱ��־*/
    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;

    g_GmmRauCtrl.ucT3330outCnt = 0;

    /* RAU��������3311��ʱ����ʱ��־ */
    g_GmmRauCtrl.ucT3311ExpiredFlg  = GMM_FALSE;

    NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_FALSE);
    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    if (GMM_UPDATING_TYPE_INVALID != ucUpdataType)
    {                                                                           /* ���������Ч                             */
        if(GMM_PERIODC_UPDATING == ucUpdataType)
        {                                                                       /* �����Ե�RAU                              */
            g_GmmRauCtrl.ucPeriodicRauFlg = GMM_TRUE;                           /* ��Ǵ���������RAU                        */

            if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
             || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* �����û�ģʽA������ģʽI                 */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                    /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure started");
            }
            else
            {
                Gmm_PeriodRoutingAreaUpdateType();                              /* ���ú�����д�����Ե�RAU������            */
            }
        }
        else
        {
            switch (ucUpdataType)
            {                                                                   /* ����RAU���ʹ洢��ǰ���е�specific����    */
            case GMM_RA_UPDATING:
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure started");
                break;
            case GMM_COMBINED_RALA_UPDATING:
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: combined RAU procedure started");
                break;
            case GMM_COMBINED_RALAU_WITH_IMSI_ATTACH:
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: combined RAU with IMSI attach procedure started");
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateInitiate:WARNING: Update Type is Abnormal");
                break;
            }
        }
        NAS_GMM_SndRoutingAreaUpdateReq(ucUpdataType);                              /* ���ú�������RAU REQUEST                  */
        return;
    }

    /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ��������ע�� */
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                            /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure started");
        NAS_GMM_SndRoutingAreaUpdateReq(GMM_RA_UPDATING);                           /* ���ú�������ATTACH REQUEST               */
        return;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS��SIM��Ч                              */

        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)

        {                                                                       /* CS���Ѿ�ע��                             */
            if ((VOS_TRUE == ucCsRestrictRegister)
             || ((GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
              && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)))
            {                                                                   /* CS����ͨ����                             */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;           /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure during CS transaction started");
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
                NAS_GMM_SndRoutingAreaUpdateReq(GMM_RA_UPDATING);                   /* ���ú�������RAU REQUEST                  */
            }
            else
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;                  /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: combined RAU procedure started");

                if (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    NAS_GMM_SndRoutingAreaUpdateReq(GMM_COMBINED_RALA_UPDATING);    /* ���ú�������RAU REQUEST                  */
                }
                else
                {
                    /* δ��g_GmmGlobalCtrl.ucSpecProcΪGMM_RAU_WITH_IMSI_ATTACH,
                      T3330��ʱ���������rau���Ͳ�ΪGMM_COMBINED_RALAU_WITH_IMSI_ATTACH*/
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;

                    NAS_GMM_SndRoutingAreaUpdateReq(
                                     GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                }
            }
        }
        else
        {                                                                       /* CS��ûע��                               */
            if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
             || (VOS_TRUE == ucCsRestrictRegister))
            {                                                                   /* CS��ATTACH����ֹ                         */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                    /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure started");
                NAS_GMM_SndRoutingAreaUpdateReq(GMM_RA_UPDATING);                   /* ���ú�������RAU REQUEST                  */
            }
            else
            {                                                                   /* CS��ATTACHû����ֹ                       */
                if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                {                                                               /* CS����ͨ����                             */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;       /* �洢��ǰ���е�specific����               */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure during CS transaction started");
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;   /* ���CSͨ���е�����                       */
                    NAS_GMM_SndRoutingAreaUpdateReq(GMM_RA_UPDATING);               /* ���ú�������RAU REQUEST                  */
                }
                else
                {
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;      /* �洢��ǰ���е�specific����               */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: combined RAU with IMSI attach procedure started");
                    NAS_GMM_SndRoutingAreaUpdateReq(
                                     GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);      /* ���ú�������RAU REQUEST                  */
                }
            }
        }
    }
    else
    {                                                                           /* SIM��Ч                                  */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                            /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiate:INFO: normal RAU procedure started");
        NAS_GMM_SndRoutingAreaUpdateReq(GMM_RA_UPDATING);                           /* ���ú�������RAU REQUEST                  */
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RauAccept_Mandatory_Ie_Check
  Function : ��Rau Accept��Ϣ�еı�ѡ����м��
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
    3.��    �� : 2012��03��21��
      ��    �� : z00161729
      �޸����� : ֧��ISR�����޸�
*******************************************************************************/
VOS_UINT8 Gmm_RauAccept_Mandatory_Ie_Check(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *pNeedReturn)
{
    VOS_UINT8                           ucForceToStandby = 0;

    VOS_UINT8                           ucUpdateResultValue;

    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RauAccept_Mandatory_Ie_Check:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x07);

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
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RauAccept_Mandatory_Ie_Check:WARNING: IE\"Force to standby\" is invalid in RAU ACCEPT");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    ucUpdateResultValue = (pMsg->aucNasMsg[2] >> NAS_MML_OCTET_MOVE_FOUR_BITS) & NAS_MML_OCTET_LOW_THREE_BITS;

    if ((GMM_RA_UPDATED != ucUpdateResultValue)
     && (GMM_COMBINED_RALA_UPDATED != ucUpdateResultValue)
     && (GMM_RA_UPDATED_ISR_ACTIVE != ucUpdateResultValue)
     && (GMM_COMBINED_RALA_UPDATED_ISR_ACTIVE != ucUpdateResultValue))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RauAccept_Mandatory_Ie_Check:WARNING: IE\"Update result\" is invalid in RAU ACCEPT");
        return GMM_FAILURE;
    }

    *pNeedReturn = GMM_FALSE;

    return GMM_SUCCESS;
}
/*******************************************************************************
  Module   : Gmm_IeCheck_Npdu_Numbers
  Function : ��IE List of Receive N-PDU Numbers���м��
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
VOS_UINT8 Gmm_IeCheck_Npdu_Numbers(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn)
{
    if ((VOS_NULL == pMsg) || (VOS_NULL == pNeedReturn))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_IeCheck_Npdu_Numbers:ERROR: Null Pointer");
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
  Module   : Gmm_IECheck_RauAccept
  Function : �Կտ���ϢRouting area update accept��IE���м��
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
    4.��    ��   : 2013��09��10��
      ��    ��   : l65478
      �޸�����   : DTS2013090202323:��ѡIE�ļ�����ʱ������FAIL
    5.��    ��   : 2015��6��8��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_UINT8 Gmm_IECheck_RauAccept(NAS_MSG_FOR_PCLINT_STRU *pMsg)
{
    VOS_UINT8   ucIeOffset = GMM_MSG_LEN_RAU_ACCEPT;                            /* ������ʱ�����洢�洢IE��ƫ����           */
    VOS_UINT8   ucEndFlg   = GMM_FALSE;                                         /* ���ڻ�������־ΪFALSE                    */
    VOS_UINT8   ucResult   = GMM_SUCCESS;
    VOS_UINT8   ucNeedReturn = GMM_TRUE;

    ucResult = Gmm_RauAccept_Mandatory_Ie_Check(pMsg, &ucNeedReturn);

    if (GMM_TRUE == ucNeedReturn)
    {
        return ucResult;
    }

    /* ��ѡIE��� */
    for (; (ucIeOffset < pMsg->ulNasMsgSize) && (GMM_FALSE == ucEndFlg); )
    {                                                                           /* �洢IE��ƫ����С�ڿտ���Ϣ�ĳ���         */
        switch (pMsg->aucNasMsg[ucIeOffset])
        {                                                                       /* IEI                                      */
        case GMM_IEI_P_TMSI_SIGNATURE:                                          /* P-TMSI signature������Ҫ���             */
            ucIeOffset += 4;
            break;
        case GMM_IEI_ALLOCATED_PTMSI:                                           /* Allocated P-TMSI                         */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_Allocated_Ptmsi(pMsg,ucIeOffset,&ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }
            ucIeOffset += 7;
            break;
        case GMM_IEI_MS_IDENTITY:                                               /* MS identity                              */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_Ms_Identity(pMsg,&ucIeOffset,&ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }
            break;
        case GMM_IEI_LIST_OF_RECEIVE_N_PDU_NUMBERS:                             /* Allocated P-TMSI                         */
            ucNeedReturn = GMM_TRUE;

            ucResult = Gmm_IeCheck_Npdu_Numbers(pMsg,ucIeOffset,&ucNeedReturn);

            if (GMM_TRUE == ucNeedReturn)
            {
                return ucResult;
            }

            ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            break;
        case GMM_IEI_NEGOTIATED_READY_TIMER_VALUE:                              /* Negotiated READY timervalue������Ҫ���  */
            ucIeOffset += 2;
            break;
        case GMM_IEI_GMM_CAUSE:                                                 /* GMM cause������Ҫ���                    */
            ucIeOffset += 2;
            break;
        case GMM_IEI_T3302_VALUE:                                               /* T3302 value                              */
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
            ucIeOffset += 2 + pMsg->aucNasMsg[ucIeOffset + 1];
            break;
        case GMM_IEI_PDP_CONTEXT_STATUS:
            ucIeOffset += 4;
            break;
        case GMM_IEI_EMERGENCY_NUMBER_LIST:                                     /* Emergency Number List                    */
            /*lint -e961*/
            if (ucIeOffset + 2 + pMsg->aucNasMsg[ucIeOffset + 1] <= pMsg->ulNasMsgSize)
            /*lint +e961*/
            {
                ucIeOffset += (2 + pMsg->aucNasMsg[ucIeOffset + 1]);
            }
            else
            {
                ucEndFlg = GMM_TRUE;
            }
            break;

            case NAS_GMM_IEI_T3323_VALUE:
                ucIeOffset += 3;
                break;

            case NAS_GMM_IEI_T3312_EXTENDED_VALUE:
                ucIeOffset += NAS_GMM_IE_T3312_EXTENDED_VALUE_LEN;
                break;

        default:
            if(GMM_IEI_NETWORK_FEATURE_SUPPORT == (pMsg->aucNasMsg[ucIeOffset] & 0xF0))
            {/* Network feature support                  */
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
    return GMM_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : Gmm_RoutingAreaUpdateInitiateWithReEstRR
 ��������  : �յ�RR�����ͷţ�Я��ԭ��ֵΪ16��Ҫ���ؽ�RR����ʱ��RAU��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2006��3��22��
   ��    ��   : liuyang id:48197
   �޸�����   : �����ɺ��������ⵥ��:A32D01882
 2.��    ��   : 2007��12��15��
   ��    ��   : l00107747
   �޸�����   : ���ⵥ��:A32D13897
 3.��    ��   : 2010��11��29��
   ��    ��   : z00161729
   �޸�����   : ���ⵥ��:DTS2010112900029:W��RAU������Ǩ��ʧ�ܣ��������DSCR,UE����פ��������RAU������������������RAU
 4.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 5.��    ��   : 2011��8��26��
   ��    ��   : c00173809
   �޸�����   : ���ⵥ��:DTS2011082500573,��PSҵ������У�RR�����쳣�ͷţ�ԭ��ΪrRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST
                 Ȼ��פ���ڲ�ͬRAI��С����RAU�ɹ����޷�����CC�绰��
 5.��    ��   : 2012��2��15��
   ��    ��   : w00167002
   �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����������ǰ����CSFBҵ���־����ֻ��RAU
 6.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID Gmm_RoutingAreaUpdateInitiateWithReEstRR()
{

    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        || (GMM_NULL == g_GmmGlobalCtrl.ucState))
    {                                                                           /* PS��û��ע��                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:WARNING: PS domain hasn't register");
        return;
    }

    g_GmmRauCtrl.ucT3330outCnt = 0;

    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;

#if (FEATURE_ON == FEATURE_LTE)

    /* ����CS��������ʱ������RAU */
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_RA_UPDATING);
        return;
    }
#endif

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                            /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: normal RAU procedure started");
        Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_RA_UPDATING);                           /* ���ú�������ATTACH REQUEST               */
        return;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS��SIM��Ч                              */

        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)

        {                                                                       /* CS���Ѿ�ע��                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {                                                                   /* CS����ͨ����                             */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;           /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: normal RAU procedure during CS transaction started");
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
                Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_RA_UPDATING);        /* ���ú�������RAU REQUEST                  */
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: combined RAU procedure started");
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;      /* �洢��ǰ���е�specific����               */
                    Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                }
                else
                {

                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;              /* �洢��ǰ���е�specific����               */
                    Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_COMBINED_RALA_UPDATING);        /* ���ú�������RAU REQUEST                  */
                }
            }
        }
        else
        {                                                                       /* CS��ûע��                               */
            if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
            {                                                                   /* CS��ATTACH����ֹ                         */
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                    /* �洢��ǰ���е�specific����               */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: normal RAU procedure started");
                Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_RA_UPDATING);                   /* ���ú�������RAU REQUEST                  */
            }
            else
            {                                                                   /* CS��ATTACHû����ֹ                       */
                if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                {                                                               /* CS����ͨ����                             */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;       /* �洢��ǰ���е�specific����               */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: normal RAU procedure during CS transaction started");
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;   /* ���CSͨ���е�����                       */
                    Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_RA_UPDATING);    /* ���ú�������RAU REQUEST                  */
                }
                else
                {
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;      /* �洢��ǰ���е�specific����               */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: combined RAU with IMSI attach procedure started");
                    Gmm_SndRoutingAreaUpdateReqWithReEstRR(
                                     GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);      /* ���ú�������RAU REQUEST                  */
                }
            }
        }
    }
    else
    {                                                                           /* SIM��Ч                                  */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                            /* �洢��ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RoutingAreaUpdateInitiateWithReEstRR:INFO: normal RAU procedure started");
        Gmm_SndRoutingAreaUpdateReqWithReEstRR(GMM_RA_UPDATING);                /* ���ú�������RAU REQUEST                  */
    }

    if ((GMM_RAU_NORMAL             != g_GmmGlobalCtrl.ucSpecProc)
        && (GMM_RAU_NORMAL_CS_TRANS != g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* RAU���Ͳ���normal NORMAL                 */
        NAS_GMM_SndMmCombinedRauInitiation();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Gmm_SndRoutingAreaUpdateReqWithReEstRR
 ��������  : ��RR�ͷ�ָʾ�д����ؽ�RR���ӵ�ָʾ������RAU REQUEST,
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��22��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ��������ⵥ��:A32D01882
  2.��    ��   : 2006��9��13��
    ��    ��   : liurui id:40632
    �޸�����   : �������ⵥ�ţ�A32D05874
  3.��    ��   : 2010��9��09��
    ��    ��   : l65478
    �޸�����   : DTS2010090302562,PDP��������з�����ѡ��PDP�����¼��ȱ����
*****************************************************************************/
VOS_VOID Gmm_SndRoutingAreaUpdateReqWithReEstRR(
                                 VOS_UINT8 ucUpdataType                         /* ����RAU REQUEST������                    */
                                 )
{
    NAS_MSG_STRU    *pSendNasMsg = VOS_NULL_PTR;                                /* ����NAS_MSG_STRU���͵�ָ�����           */

    GMM_CasFsmStateChangeTo(GMM_ROUTING_AREA_UPDATING_INITIATED);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_SndRoutingAreaUpdateReqWithReEstRR:NORMAL: STATUS IS GMM_ROUTING_AREA_UPDATING_INITIATED");

    g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

    /* ���� Rau ʱ���ж��Ƿ����ϲ�ҵ������У������� Follow-On ��־ */

    if ((GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        ||(GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
        || (GMM_MSG_HOLD_FOR_SMS
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS)))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
    }


    /* ����Ƿ���Ҫ��RAU����DETACH���� */
    if (VOS_TRUE == g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmDetachCtrl.ucDetachProc;
    }

    /* ����Ƿ���Ҫ��RAU����Service Request���� */
    if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmServiceCtrl.ucServiceRequestProc;
    }

    pSendNasMsg = Gmm_RoutingAreaUpdateRequestMsgMake(ucUpdataType);            /* ����RAU REQUEST��Ϣ                      */

    gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;                                /* ϵͳ��ϢҪ���RAU���̱�־��� */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_UpdateSysTlli(GMM_FOREIGN_TLLI);                                    /* ���foreign TLLI */

        if ( GMM_FALSE == GMM_AssignModifyTlli(gstGmmCasGlobalCtrl.ulTLLI,
                gstGmmCasGlobalCtrl.ucflgTLLI) )
        {
            GMM_LOG_WARN("Gmm_SndRoutingAreaUpdateReqWithReEstRR():Error: new TLLI assigned unsuccessfully!");
        }
        if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcSuspendReq();                                             /* ֹͣLLC���ݴ��� */
        }

        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_RAU;

        /* �ڷ���RAUʱ��Ҫ��L2���Է���GMM��������Ϣ��������Ҫ֪ͨL2�ָ�������,
        ������ΪL2���ܱ����л�������ݣ���������Ҫ���L2������  */
        Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);

        GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
    }

    Gmm_SndRrmmEstReq(RRC_EST_CAUSE_CALL_RE_ESTABLISH,
                      GMM_RRC_IDNNS_UNKNOWN,
                      pSendNasMsg);                                             /* ��RRMM_EST_REQ����RAU REQUEST��Ϣ        */

    Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);

    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_RAU_REQ,
                    (VOS_VOID *)&ucUpdataType,
                    NAS_OM_EVENT_RAU_REQ_LEN);
    return;
}

/*****************************************************************************
 �� �� ��  : GMM_RauFailureInterSys
 ��������  : ��ϵͳ�л���RAUʧ�ܴ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��5��6��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��7��21��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��DTS2010072801975����ϵͳRAUʧ�ܺ���Ҫ�ٴν��������ͷŴ���
*****************************************************************************/
VOS_VOID GMM_RauFailureInterSys()
{
    GMM_LOG_INFO("GMM_RauFailureInterSys:Gmm rau failure for intersystem change.");

    if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }

    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

    if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
    {
        gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
    }

    GMM_BufferMsgDump();
    Gmm_HoldBufferFree();
    Gmm_ComCnfHandle();

    return;
}

/*****************************************************************************
 �� �� ��  : GMM_RauSuccessInterSys
 ��������  : ��ϵͳ�л���RAU�ɹ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��5��6��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID GMM_RauSuccessInterSys()
{
    GMM_LOG_INFO("GMM_RauSuccessInterSys:Gmm rau success for intersystem change.");

    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

    GMM_ResumeSuccess();
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcMmLuResult
 ��������  : ����LU���
 �������  : VOS_VOID                            *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��6��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��08��02��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2011080200067,��ɳ���ⳡ���ֶ��б�������ѡ����������ע��ʧ�ܣ��Ļ��Զ�ģʽ����HPLMN
                 ע�ᣬ����CSע�ᣬPS�쳣������ʧ��
  3.��    ��   : 2011��10��17��
    ��    ��   : h44270
    �޸�����   : GUL NAS 2�׶Σ���GMM�յ�MM��ע��ԭ��ֵ11����ʱ�����HPLMN�ϣ���
                  GMM������MM��ע��������Ȼ����ע�ᣬ���������޷���
  4.��    ��   : 2012��4��20��
    ��    ��   : l00130025
    �޸�����   : DTS2012031502528��GMM GPRS Suspension״̬û�д���LuRsltInd��
                 W->G Rej 11->WԭС��ʱ,û����Attach�����º���SMҵ��ʧ��
  5.��    ��  : 2012��08��24��
    ��    ��  : m00217266
    �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ��ɾ��GMM_SaveErrCode��
                ���NAS_GMM_SetAttach2DetachErrCode�����浼��Attachʧ�ܵ�ԭ��ֵ
  6.��    ��  : 2013��01��7��
    ��    ��  : t00212959
    �޸�����  : DTS2013010907158:CS�ȱ�#11�ܾ���RAU���ܾ�û��֪ͨMMC
*****************************************************************************/
VOS_VOID NAS_GMM_ProcMmLuResult(
    VOS_VOID                           *pstRcvMsg
)
{
    MMGMM_LU_RESULT_IND_STRU           *pstLuResult;
    GMM_STATE_TYPE_UINT8                ucPreState;

    pstLuResult = (MMGMM_LU_RESULT_IND_STRU *)pstRcvMsg;

    if (MMGMM_LU_FAILURE == pstLuResult->enLuResult)
    {
        switch ( pstLuResult->enCause)
        {
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW :
                /* ��ʱ�����HPLMN�ϣ���GMM������MM��ע��������Ȼ����ע�ᣬ���������޷��� */
                if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
                {
                    NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PLMN_NOT_ALLOW);

                    ucPreState = g_GmmGlobalCtrl.ucState;

                    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ֹͣTimer3310                            */
                    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
                    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {                                                                           /* ATTACH��������SM������                   */

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PLMN_NOT_ALLOW); /* ֪ͨSM GMMע��ʧ��                       */
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
                    }

                    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* ����״̬��ΪGU3                          */

                    Gmm_DelPsLocInfoUpdateUsim();                                               /* ���ú���ɾ��PS LOCATION INFO             */
                    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;

                    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
                    {
                        /* ��MMC����PSע���� */
                        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                                     NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);
                    }
                    else
                    {
                        /* ��MMC����PSע���� */
                        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                                     NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);
                    }

                    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* ����״̬��������                         */

                    g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                      /* attach attempt counter��0                */
                    g_GmmRauCtrl.ucRauAttmptCnt       = 0;                                      /* RAU attempt counter��0                   */

                    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
                    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                             & GMM_WAIT_PS_ATTACH))
                    {
                        NAS_GMM_SndMmcAttachCnf();
                    }
                    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

                    NAS_GMM_DeleteEPlmnList();

                    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
                     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
                    {
                        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                    }

                    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                         /* �����־                                 */
                    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */
                    g_GmmGlobalCtrl.ucSpecProc              = GMM_NULL_PROCEDURE;                         /* ������ڽ��е�specific���̱�־           */
                    g_GmmGlobalCtrl.ucFollowOnFlg           = GMM_FALSE;

                    /* ���fallowon��־                         */
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    if ((GMM_GPRS_SUSPENSION == ucPreState)
                     || (GMM_SUSPENDED_GPRS_SUSPENSION == ucPreState))
                    {
                        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_LIMITED_SERVICE;

                        Gmm_ComStaChg(ucPreState);

                        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3310);
                        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3318);
                        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3320);
                    }

                    NAS_GMM_CheckCauseToStartT3340(NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);


                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW :
                g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
                break;
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW :
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL :
                g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;
                break;
            default:
                break;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetRoutingAreaUpdateType
 ��������  : ��ȡrau����
 �������  : ��
 �������  : ��
 �� �� ֵ  : rau ����
 ���ú���  :
 ��������  :
��ȡ
 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��12��11��
    ��    ��   : z00234330
    �޸�����   : dts2013121106833,��Ȧ���Ӷ�
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetRoutingAreaUpdateType(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    VOS_UINT8                           ucCsRestrictRegister;
    VOS_UINT8                           ucUpdateType;

    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();
    enCurRat = NAS_MML_GetCurrNetRatType();


    /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ��������ע�� */
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {
        ucUpdateType               = GMM_RA_UPDATING;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        return ucUpdateType;
    }


    /* cs����Ч */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        /* SIM��Ч                                  */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                            /* �洢��ǰ���е�specific����               */
        ucUpdateType = GMM_RA_UPDATING;
        return ucUpdateType;
    }

    /* CS���Ѿ�ע�� */
    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        if ((VOS_TRUE == ucCsRestrictRegister)
         || ((GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)))
        {
            /* CS����ͨ����                             */
            g_GmmGlobalCtrl.ucSpecProc          = GMM_RAU_NORMAL_CS_TRANS;  /* �洢��ǰ���е�specific����               */
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
            ucUpdateType                        = GMM_RA_UPDATING;
            return ucUpdateType;
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_COMBINED;                  /* �洢��ǰ���е�specific����               */

        if (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
        {
            ucUpdateType = GMM_COMBINED_RALA_UPDATING;
            return ucUpdateType;
        }

        /* δ��g_GmmGlobalCtrl.ucSpecProcΪGMM_RAU_WITH_IMSI_ATTACH,
          T3330��ʱ���������rau���Ͳ�ΪGMM_COMBINED_RALAU_WITH_IMSI_ATTACH*/
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        ucUpdateType               = GMM_COMBINED_RALAU_WITH_IMSI_ATTACH;
        return ucUpdateType;

    }

    /* CS��ûע��                               */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_TRUE == ucCsRestrictRegister))
    {
        /* CS��ATTACH����ֹ                         */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;                    /* �洢��ǰ���е�specific����               */
        ucUpdateType               = GMM_RA_UPDATING;
        return ucUpdateType;
    }

    /* CS��ATTACHû����ֹ                       */
    if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
    {
        /* CS����ͨ����                             */
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL_CS_TRANS;       /* �洢��ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;   /* ���CSͨ���е�����                       */
        ucUpdateType                        = GMM_RA_UPDATING;
        return ucUpdateType;
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;      /* �洢��ǰ���е�specific����               */
    ucUpdateType               = GMM_COMBINED_RALAU_WITH_IMSI_ATTACH;
    return ucUpdateType;

}


/*****************************************************************************
 �� �� ��  : NAS_Gmm_SaveRauAcceptGmmCause
 ��������  : ����RAU accept�е�gmm cause
 �������  : GMM_MSG_RESOLVE_STRU  *pRauAcceptIe ָ��GMM_MSG_RESOLVE_STRU
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
VOS_VOID NAS_Gmm_SaveRauAcceptGmmCause(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU               *pstRauAcceptIe
)
{
    VOS_UINT32                          ulOptionalIeMask;
    VOS_UINT8                           ucGmmCause;

    ulOptionalIeMask = pstRauAcceptIe->ulOptionalIeMask;
    if ( (GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG == (ulOptionalIeMask & GMM_RAU_ACCEPT_IE_GMM_CAUSE_FLG))
      && (pstRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_GMM_CAUSE] < 254) )
    {
        ucGmmCause = pMsg->aucNasMsg[pstRauAcceptIe->aucIeOffset[GMM_RAU_ACCEPT_IE_GMM_CAUSE] + 1 ];
    }
    else
    {
        ucGmmCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    NAS_MML_SetOriginalRejectCause(ucGmmCause);
    return;
}

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
