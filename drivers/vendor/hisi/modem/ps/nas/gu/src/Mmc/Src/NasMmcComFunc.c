/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcComFunc.c
  �� �� ��   : ����
  ��    ��   : l00130025
  ��������   : 2011��8��7��
  ����޸�   :
  ��������   : MMC����������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmSublayerDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMscc.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcCtx.h"
#include "NasMmcComFunc.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcSndAps.h"
#include "NasMmcSndCds.h"
#include "NasMmcProcUsim.h"
#include "Nasrrcinterface.h"

#include "NasUtranCtrlInterface.h"
#include "NasMmcProcRegRslt.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#include "NasUsimmApi.h"
#include "NasMmcFsmMainTbl.h"
/* added by wx270776 for OM�ں�, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM�ں�, 2014-08-21, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_COM_FUNC_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSndEPlmn
 ��������  : ��ǰ�Ƿ���Ҫ���͵�ЧPlmn
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��6��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��15��
   ��    ��   : w00167002
   �޸�����   : û��Eplmnʱ��Ҳ��Ҫ֪ͨ�����
 3.��    ��   : 2013��12��13��
   ��    ��   : w00242748
   �޸�����   : DTS2013121103237:G NMOII���ɹ�פ��������ҵ��ҵ����й����У�
                ָ�����������磬������ʧ�ܣ�����פ��������ҵ��ָ����˴��޸�
                �������ֶ������ҵ�ǰ����פ����δע��ʱ����������㷢�͵�ЧPLMN
 4.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndEplmn( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    VOS_UINT8                                               ucAsAnyCampOn;
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    /* �޿�ʱ�����뷢�͵�Ч Plmn */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /*  ��ǰפ�����磬��Rplmnʱ�������� Eplmn������㣬�������㶪�� */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();


    /* ��ǰ��EPlmn��֪ͨ�����,����RAU��������ATTACH,LAUʱ����Ҫɾ��Eplmn��24008:4.7.3.2.5
    if the attach attempt counter is smaller than 5 and, additionally,
    the update status is different from U1 UPDATED or the stored LAI is different
    from the one of the current serving cell, then the mobile station shall delete
    any LAI, TMSI, ciphering key sequence number stored in the SIM/USIM
    and list of equivalent PLMNs */
    if ( 0 == pstEplmnInfo->ucEquPlmnNum)
    {
        /* û��EPlmnʱ����֪ͨ����㵱ǰפ�������� */
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(), &(pstEplmnInfo->astEquPlmnAddr[0])))
    {
        return VOS_FALSE;
    }

    ulEplmnValidFlg   = NAS_MML_GetEplmnValidFlg();
    ulRegFlag         = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* �ֶ�����ģʽ�ж�eplmn�б��Ƿ���Ч����Ч�򷵻� */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            return VOS_FALSE;
        }
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    ucAsAnyCampOn = NAS_MMC_GetAsAnyCampOn();

    /* �����3GPP2����ע�ᣬ��ǰLΪ����פ������������ע�� */
    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
     && (VOS_TRUE == ucAsAnyCampOn))
    {
        return VOS_FALSE;
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLaiForbTypeManualSelMode
 ��������  : ��ȡ�ֶ�ģʽ�µĽ�ֹPlmn����
 �������  : pstLai
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��11��
    ��    ��   : w00166186
    �޸�����   : DTS201111105194,�ֶ�����ʧ�ܺ�ANYCELL�Ѳ���ָ�����緢����ע�ᣬ���³ɹ�������ָ��������
  3.��    ��   : 2011��11��24��
    ��    ��   : w00167002
    �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                 ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
                 ��������ͣ���������ȽϿ��ܻ����
  4.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���ӽ�ֹLTE�������ζ���
  5.��    ��   : 2012��11��09��
    ��    ��   : l65478
    �޸�����   : DTS2012103005174, PS�ɹ�,�ڵ�ЧPLMN�в����ý�ֹ��־
  6.��    ��  : 2012��11��09��
    ��    ��  : z00161729
    �޸�����  : DTS2013012301312:��ֹlte���Σ�syscfgex����lw��l���ȣ�����פ��w������46011��disable lte��
                ��ָ����46009ʧ�ܣ�anycellפ��46011��available��ʱ����ʱ��46009����ָ����46011�������뼼����
                pdp����ʧ�ܺ�ϵͳ��Ϣ��Ϊ��forbidden����
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetLaiForbTypeManualSelMode(
    NAS_MML_LAI_STRU                   *pstLai
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulRlst;
    VOS_UINT32                          ulRegFlag;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
#endif
    VOS_UINT32                          ulEplmnValidFlg;

    /* �ֶ�ģʽ��ǰPlmn����Eplmn�������û�ָ�����粻ͬʱ,��ֹע�� */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstLai->stPlmnId),
                                            pstEplmnInfo->ucEquPlmnNum,
                                            pstEplmnInfo->astEquPlmnAddr);

    ulRegFlag = NAS_MMC_GetUserSpecPlmnRegisterStatus();
    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* LTE��ֹ��������ʱ����ǰ�û�ָ��������ʱ��������Ӧ����forbidden���� */
#if (FEATURE_ON == FEATURE_LTE)
    enRatType = NAS_MML_GetCurrNetRatType();

    if ((VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
     {
        /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* ��ǰפ��PLMN IDΪ������������ */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstUserSpecPlmn->stPlmnId.ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLaiForbTypeManualSelMode FORBIDDEN:ROAM NOT ALLOWED");
            
            return NAS_MML_PLMN_FORBID_PLMN;
        }
     }
#endif

    if ((VOS_TRUE== NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId), &(pstUserSpecPlmn->stPlmnId)))
     || ((VOS_TRUE == ulRegFlag)
      && (VOS_TRUE == ulRlst)
      && (VOS_TRUE == ulEplmnValidFlg)))
    {
        return   NAS_MML_GetLaiForbType(pstLai);
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLaiForbTypeManualSelMode FORBIDDEN:LIKE NOT USER SPEC PLMN");        
        
        return NAS_MML_PLMN_FORBID_PLMN;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLaiForbTypeAutoSelMode
 ��������  : ��ȡ�Զ�ģʽ�µĽ�ֹPlmn����
 �������  : pstLai
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��24��
    ��    ��   : w00167002
    �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                 ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
                 ��������ͣ���������ȽϿ��ܻ����
  3.��    ��   : 2012��5��10��
    ��    ��   : l00130025
    �޸�����   : DTS2012050301244: �Զ�ģʽ��MMC�ܷ�פ��������Ҫ�ж�ucWrrLimitServiceInd
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetLaiForbTypeAutoSelMode(
    NAS_MML_LAI_STRU                   *pstLai
)
{

    return NAS_MML_GetLaiForbType(pstLai);


}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrentLaiForbbidenType
 ��������  : ��ȡ��ǰLA�Ƿ��ڽ�ֹ�б��У�����ڽ�ֹ�б��У���ֹ�б������
 �������  : VOS_UINT32                          *pulPlmnLaType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��3��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenType(VOS_VOID)
{
    NAS_MML_LAI_STRU                                       *pstCurrentLai = VOS_NULL_PTR;
    VOS_UINT32                                              ulPlmnLaType;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enPlmnSelMode;
    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��USIM������SIM����Чʱ������Ҫ�ж�FORBIDDEN��־��ֱ�ӷ��� */
    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    enPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    pstCurrentLai  = NAS_MML_GetCurrCampLai();

    /* ����ʱ��ǰפ��������Ϣ��Ĭ����Чֵ�������жϽ�ֹ���� */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&pstCurrentLai->stPlmnId))
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enPlmnSelMode)
    {
        ulPlmnLaType =  NAS_MMC_GetLaiForbTypeManualSelMode(pstCurrentLai);
    }
    /*�Զ�ģʽ�½�ֹ��Ϣ��ȡ*/
    else
    {
        ulPlmnLaType = NAS_MMC_GetLaiForbTypeAutoSelMode(pstCurrentLai);
    }

    /*���ؽ�ֹ��Ϣ*/
    return ulPlmnLaType;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHPlmnSpecDomainAccessCapa
 ��������  : ��ǰ��Hplmn�����ָ����Ŀǰ�Ƿ��������,(�����Ƿ�֮ǰ��ע�ᱻ�ܹ�)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:������룻VOS_FALSE:���������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��24��
    ��    ��   : likelai
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��29��
    ��    ��   : lijun 00171473
    �޸�����   : V7R1 PhaseII �޸�
  3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetHPlmnSpecDomainAccessCapa(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrLai         = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCurrCampRac;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain;

    if ((NAS_MMC_REG_DOMAIN_CS != enRegCnDomain)
     && (NAS_MMC_REG_DOMAIN_PS != enRegCnDomain)
#if   (FEATURE_ON == FEATURE_LTE)
     && (NAS_MMC_REG_DOMAIN_EPS !=  enRegCnDomain)
#endif
     )
    {
        return VOS_TRUE;
    }

    /* ��ȡ��ǰפ����PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* ��ǰפ��PLMN����HPLMN�б��У���ֱ�ӷ��� */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
         return VOS_TRUE;
    }

    /* ��ȡHPLMNע�ᱻ�ܵ��б� */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ǰפ��PLMN��HPLMNע�ᱻ���б��У���ֱ�ӷ��� */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (NAS_MML_INVALID_INDEX == ulIndex)
    {
        return VOS_TRUE;
    }

    /* ��ȡ��ǰפ����LAI */
    pstCurrLai = NAS_MML_GetCurrCampLai();

    NAS_MMC_GetHplmnRejDomainInfo(&enDomain);

    if (enDomain & enRegCnDomain)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enRegCnDomain)
        {
            if ( (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0] == pstCurrLai->aucLac[0])
              && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1] == pstCurrLai->aucLac[1]) )
            {
                NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                                "NAS_MMC_GetHPlmnSpecDomainAccessCapa: Curr LAC in HPLMN REG REJ list ",
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMcc,
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMnc,
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0],
                                pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1]);
                return VOS_FALSE;
            }
        }
        else
        {
           ucCurrCampRac = NAS_MML_GetCurrCampRac();
           if ( (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0] == pstCurrLai->aucLac[0])
             && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1] == pstCurrLai->aucLac[1])
             && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].ucRac == ucCurrCampRac) )
           {
               NAS_NORMAL_LOG3(WUEPS_PID_MMC,
                               "NAS_MMC_GetHPlmnSpecDomainAccessCapa: Curr RAC in HPLMN REG REJ list ",
                               pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMcc,
                               pstRegRejCtx->astPlmnRegInfoList[ulIndex].stPlmnId.ulMnc,
                               pstRegRejCtx->astPlmnRegInfoList[ulIndex].ucRac);
               return VOS_FALSE;
           }
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnIndexInRegInfoList
 ��������  : ȷ��pstPlmnId��ע����Ϣ�б��е�λ��
 �������  : pstPlmnId: ��Ҫ���ҵ�PLMN ID
             ulRegPlmnListNum: �б���Ԫ�صĸ���
             pstPlmnRegList: �б��ָ��
 �������  : ��
 �� �� ֵ  : ���ҵ���PLMN��Index
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : L00171473
    �޸�����   : V7R1 PhaseII �޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetPlmnIndexInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulRegPlmnListNum,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulRegPlmnListNum; i++ )
    {
        /* pstPlmnRegList�洢���� BCCH�е�ֵ��pstPlmnId����ʱ���е� Plmn */
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnRegList[i].stPlmnId), pstPlmnId) )
        {
            break;
        }
    }

    if (i < ulRegPlmnListNum)
    {
        return i;
    }
    else
    {
        return NAS_MML_INVALID_INDEX;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetOptMask_WasSysinfo
 ��������  : ��ȡת���� MM/GMM ��Wϵͳ��Ϣ��Ҫ��Maslֵ
 �������  : RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd;
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��8��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetOptMask_WasSysinfo(
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd
)
{
    VOS_UINT32                          ulBitMask;

    ulBitMask = 0;

    /* ����ϵͳ��Ϣ�����ݣ����Maskֵ */
    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpPlmnId)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_PLMN;
    }

    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpCsDrx)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_CS_DRX;
    }

    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpPsDrx)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_PS_DRX;
    }

    if ((0< pstRrMmSysInfoInd->ucCsInfoSize)
     || (0< pstRrMmSysInfoInd->ucPsInfoSize))
    {
        ulBitMask |= RRC_NAS_SYS_MSK_CSPS_INFO;
    }

    return ulBitMask;
}

/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, begin */
/* ɾ��NAS_MMC_ConvertUserSpecAccessMode2MmlRat����*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, end */



/*****************************************************************************
 �� �� ��  : NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode
 ��������  : ��MML�����ϵͳ��ģʽתΪMSCC�е�ϵͳ��ģʽ
 �������  : enSysSubMode: MML�����ϵͳ��ģʽ
 �������  : ��
 �� �� ֵ  : TAF_SYS_SUBMODE_ENUM_UINT8:  MSCC�е�ϵͳ��ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��25��
   ��    ��   : z00359541
   �޸�����   : DTS2015121007229:��subsysmodeȱʡֵת��Ϊ�޷���
*****************************************************************************/
TAF_SYS_SUBMODE_ENUM_UINT8 NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
)
{
    VOS_UINT32                          i;

    VOS_UINT8                           aucSysSubModeMapTable[NAS_MML_MAX_SYS_SUBMODE_NUM][2] =
    {
        {NAS_MML_RRC_SYS_SUBMODE_NULL,        TAF_SYS_SUBMODE_NONE       },
        {NAS_MML_RRC_SYS_SUBMODE_GSM,         TAF_SYS_SUBMODE_GSM        },
        {NAS_MML_RRC_SYS_SUBMODE_GPRS,        TAF_SYS_SUBMODE_GPRS       },
        {NAS_MML_RRC_SYS_SUBMODE_EDGE,        TAF_SYS_SUBMODE_EDGE       },
        {NAS_MML_RRC_SYS_SUBMODE_WCDMA,       TAF_SYS_SUBMODE_WCDMA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSDPA,       TAF_SYS_SUBMODE_HSDPA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSUPA,       TAF_SYS_SUBMODE_HSUPA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSDPA_HSUPA, TAF_SYS_SUBMODE_HSDPA_HSUPA},
        {NAS_MML_RRC_SYS_SUBMODE_LTE,         TAF_SYS_SUBMODE_LTE        },
        {NAS_MML_RRC_SYS_SUBMODE_BUTT,        TAF_SYS_SUBMODE_NONE       },
    };

    for (i = 0; i < NAS_MML_MAX_SYS_SUBMODE_NUM; i++)
    {
        if (enSysSubMode == aucSysSubModeMapTable[i][0])
        {
            return aucSysSubModeMapTable[i][1];
        }
    }

    return TAF_SYS_SUBMODE_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsHplmnTimerLenValid
 ��������  : HPLMN��ʱ��ʱ���Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHplmnTimerLenValid( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    /* H3G��������(VPLMN�·��״���HPLMNʱ��NV������)��*/
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        /* HPLMN��ʱ����ʱ���Ӵ�NV��en_NV_Item_SearchHplmnTtimerValue�л�ȡ��
           NV��ֵ����0ʱ��HPLMN��ʱ��ʱ����Ч */
        if (pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen != 0)
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* HPLMN��ʱ����ʱ����USIM�ļ�EFHPPLMN (0x6F31 Higher Priority PLMN search period)
           �л�ȡ�����ļ���ֵ����0ʱ��HPLMN��ʱ��ʱ����Ч */
        if (NAS_MML_GetSimHplmnTimerLen() != 0)
        {
            return VOS_TRUE;
        }
    }

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "stNonFirstHplmnTimerPeriod active and time len is: ",pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg, pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen);

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsHighPrioPlmnSearchVaild
 ��������  : �����ȼ�ѡ����ǰ�Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��22��
   ��    ��   : w00176964
   �޸�����   : DTS2012062007370:PS ONLY,PS����#3����Ч,�����HPLMN��ʱ������BG����
                balong������BG����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHighPrioPlmnSearchVaild( VOS_VOID )
{
    /* �ֶ�ģʽ�·�����Ч */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "highPrioPlmnSearchVaild:manual mode");
        
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "highPrioPlmnSearchVaild:UsimStaus IN Valid");
        
        return VOS_FALSE;
    }

    /* HPLMN TIMER LEN��ʱ��ʱ����Ч */
    if ( VOS_FALSE == NAS_MMC_IsHplmnTimerLenValid() )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "plmnTimerLen is inValid");
        
        return VOS_FALSE;
    }

    /* ������Ч */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCampOnHPlmn
 ��������  : �жϵ�ǰ�Ƿ��Ѿ�פ����HPLMN��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : �Ѿ�פ����HPLMN��������
             VOS_FALSE : û��פ����HPLMN��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampOnHPlmn(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList      = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��HPLMN��ͬ��������פ��HPLMN�� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId))
    {
        return VOS_TRUE;
    }

    pstEplmnList  = NAS_MML_GetEquPlmnList();

    /* �����ǰ������EPLMN��1����ͬ,��ʾ�洢��EPLMN�ǵ�ǰ�����EPLMN,��ʱ���ñȽ�EPLMN�� */
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &pstEplmnList->astEquPlmnAddr[0]))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCampOnHPlmn:false, not eplmn");
        
        return VOS_FALSE;
    }

    /* EPLMN�Ǵ������±�1��ʼ��ŵģ������±�0��ŵ���RPLMN */
    for ( i = 1; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrCampPlmnId->ulMcc, pstEplmnList->astEquPlmnAddr[i].ulMcc))
        {
            continue;
        }

        /* ���HOME PLMN��EPLMN�У��Һ͵�ǰפ����PLMN��MCC��ͬ��
           ��Ϊ��ǰ�Ѿ���HOME PLMN�� */
        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&pstEplmnList->astEquPlmnAddr[i]))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCampOnHPlmn:true");
            
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCampOnHighestPrioPlmn
 ��������  : �жϵ�ǰ�Ƿ��Ѿ�פ����������ȼ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : �Ѿ�פ����������ȼ���������
             VOS_FALSE : û��פ����������ȼ���������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��21��
   ��    ��   : W00167002
   �޸�����   :�������ȼ�ST���֣�����������:D03_HighPrioPlmnSearch_091
                ����:��L��ע��ɹ��󣬵�ģ����������, ��Ϊפ����������ȼ��������ϣ�û���������ڳ���������ʱ����
                ���ӵ�ǰפ������������ЧPLMNID���ж�

 3.��    ��   : 2012��5��17��
   ��    ��   : zhoujun 40661
   �޸�����   : ̩��AIS����

 4.��    ��   : 2012��6��13��
   ��    ��   : l00171473
   �޸�����   : DTS2012061302162, ��ǰפ��(E)HPLMN��Ϊפ��������ȼ����粻��BG��
 5.��    ��   : 2012��6��20��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ
 6.��    ��   : 2014��5��28��
   ��    ��   : z00234330
   �޸�����   : covertity�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampOnHighestPrioPlmn(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList             = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighestPrioPlmnInfo;
    NAS_MML_AIS_ROAMING_CFG_STRU                           *pstRoamingCfg            = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsCampOnHPlmn;
    NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU           *pstBgSearchRegardlessMccCtx = VOS_NULL_PTR;

    pstCurrCampPlmnId           = NAS_MML_GetCurrCampPlmnId();
    pstPlmnSelectionListInfo    = NAS_MMC_GetHighPrioPlmnList();
    pstBgSearchCfg              = NAS_MML_GetBgSearchCfg();
    pstEplmnList                = NAS_MML_GetEquPlmnList();

    pstBgSearchRegardlessMccCtx = NAS_MML_GetBgSearchRegardlessMccCtx();

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    PS_MEM_SET(&stHighestPrioPlmnInfo,0x00, sizeof(stHighestPrioPlmnInfo));
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */


    /* �����ǰ������Ч���򷵻�δפ����������ȼ������ϣ�����ģ�����󣬵�ǰפ��������
       ����ЧPLMNID */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(pstCurrCampPlmnId) )
    {
        return VOS_FALSE;
    }

    /* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */
    pstRoamingCfg  = NAS_MML_GetAisRoamingCfg();
    if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
    {
        /* �ж��Ƿ�פ���������PLMN��,�����Ѿ�����Ӫ��ȷ��,
        AIS��TOT����������֮�䲻������ΪEPLMN��С��֮��Ҳ��������Ϊ������ϵ
        */
        return NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
            1, &(pstRoamingCfg->stHighPrioPlmnId));
    }

    /* Modified by z40661 for ̩��AIS���� 2012-05-17, end */


    ulIsCampOnHPlmn = NAS_MMC_IsCampOnHPlmn();
    /* �����ǰ��פ����(E)HPLMN��, ��Ϊפ����������ȼ������� */
    if (VOS_TRUE == ulIsCampOnHPlmn)
    {
        return VOS_TRUE;
    }


    if (VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
    {
        /* Vplmn��Hplmn��ͬ������ʱ,����ص�Hplmn�Ķ������Կ��ش�ʱ */
        if (VOS_TRUE == pstBgSearchCfg->ucSpecialRoamFlg)
        {
            return VOS_FALSE;
        }

        /* AT&T BG�Ѳ����ǹ����붨�ƿ��ش򿪣���VPLMN�������ڶ����б��� */
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstCurrCampPlmnId->ulMcc, pstBgSearchRegardlessMccCtx->ucCustomMccNum, pstBgSearchRegardlessMccCtx->aulCostumMccList))
        {
            return VOS_FALSE;
        }
    }

    /* �Ӹ����ȼ��б��л�ȡ�͵�ǰפ��������ͬ�������������ȼ����� */
    if (VOS_FALSE == NAS_MMC_GetHighestPrioPlmnInHighPrioPlmnList(pstPlmnSelectionListInfo,
                                                          &stHighestPrioPlmnInfo))
    {
        /* û����ͬ������ĸ����ȼ����磬��Ϊ�Ѿ�פ����������ȼ����磬����vos_true,��������hplmn��ʱ��*/
        return VOS_TRUE;
    }

    /* �Ƚ�VPLMN�͸����ȼ��������ȼ��Ƿ���ͬ����ͬ����Ϊ�Ѿ�פ����������ȼ����� */
    if (VOS_TRUE == NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(pstCurrCampPlmnId,
                                                             NAS_MML_GetCurrNetRatType(),
                                                             pstEplmnList,
                                                             &stHighestPrioPlmnInfo ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartHPlmnTimer
 ��������  : �ж��Ƿ���Ҫ����HPLMN��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����HPLMN��ʱ��
             VOS_FALSE:����Ҫ����HPLMN��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��21��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : ��ǰUTRAN����ģʽΪTDD�������������Ѷ�ʱ��

 3.��    ��   : 2013��12��20��
   ��    ��   : w00167002
   �޸�����   : DTS2013112917981:guNASɾ����TDģʽ�²��ܽ���bg�ѵ����ơ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartHPlmnTimer(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg           = VOS_NULL_PTR;


    /* �жϵ�ǰ�����ȼ������Ƿ���Ч���ֶ�ģʽ��SIM������λ��CS��PS������Ч
       ��HPLMN��ʱ��ʱ��Ϊ0ʱ����Ϊ��ǰ��������HPLMN��ʱ����������и����ȼ����� */
    if (VOS_FALSE == NAS_MMC_IsHighPrioPlmnSearchVaild())
    {
        return VOS_FALSE;
    }

    /* Ϊ�˱��ⷴ�����ø����ȼ������Ĵ�����10s�����Գ��Զ�ʱ�������ڼ䲻����HPLMN��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStartHPlmnTimer:TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH:RUNNING");
        
        return VOS_FALSE;
    }

    /* ���HPLMN�Ѿ������У���������,on plmn���յ�psע������csע���������ж��Ƿ���Ҫ����hplmn��ʱ�������ܴ����������е���� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedStartHPlmnTimer:TI_NAS_MMC_HPLMN_TIMER:RUNNING");
        
        return VOS_FALSE;
    }

    pstBgSearchCfg            = NAS_MML_GetBgSearchCfg();

    /* ����Ѿ�פ����������ȼ����� */
    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioPlmn())
    {
        /* �����ǿ��Hplmn����,���綨�����Կ��ش�: ����Hplmn Timer��ʱ��,
           ֻҪû��פ����home PLMN��,Ҳ��Ҫ�����˶�ʱ��,��һ������2Min,��������T Min����*/
        if ((VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
         && (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg))
        {
            return VOS_TRUE;
        }

        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedStartHPlmnTimer:ucEnhancedHplmnSrchFlg is",pstBgSearchCfg->ucEnhancedHplmnSrchFlg);

        return VOS_FALSE;
    }

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo
 ��������  : �����������������Ӧ���뼼������Ϣ
 �������  : enRat
             pstPlmnIdList
 �������  : pstSearchedPlmnListInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��9��26��
   ��    ��   : w00167002
   �޸�����   : NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo_PlmnSelection����
                ���Ƹ���ΪNAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo������
                �ļ�NasMmcFsmPlmnSelection.c�ļ�Ǩ�Ƶ�NasMmcComFunc.c
 3.��    ��   : 2011��10��4��
   ��    ��   : s46746
   �޸�����   : �޸ı�����pstInterPlmnSearchInfoΪpstSearchedPlmnListInfo,��ṹ������һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRC_PLMN_ID_LIST_STRU                                  *pstPlmnIdList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;

    pstSearchedPlmnListInfo->enRatType = enRat;

    /* ѭ��pstPlmnIdList�е�ÿһ��������PLMN ID,��ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstPlmnIdList->ulHighPlmnNum) && (i < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)); i++)
    {
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMcc         = pstPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMnc         = pstPlmnIdList->aHighPlmnList[i].stPlmnId.ulMnc;
    }
    pstSearchedPlmnListInfo->ulHighPlmnNum = i;

    /* ѭ��pstPlmnIdList�е�ÿһ��������PLMN ID,��PLMN ID��������ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstPlmnIdList->ulLowPlmnNum) && (i < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)); i++)
    {
        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId.ulMcc = pstPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId.ulMnc = pstPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc;
        pstSearchedPlmnListInfo->astLowPlmnList[i].lRscp          = pstPlmnIdList->aLowPlmnList[i].lRscp;
    }
    pstSearchedPlmnListInfo->ulLowPlmnNum = i;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo
 ��������  : ��GU�µ�BG��������е�PLMN��ϢתΪ�ڲ�������Ϣ�ṹ��PLMN��Ϣ
 �������  : enRat                  -- ��ǰ����BG�ѵĽ��뼼��
             pstBgSearchRslt        -- BG���������Ϣ
             pstSearchedPlmnListInfo -- �ڲ�������Ϣ�ṹ��PLMN��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��5��7��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL �������޸�

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchRslt,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTotalNum;

    /* ���õ�ǰ����BG�ѵĽ��뼼�� */
    pstSearchedPlmnListInfo->enRatType = enRat;

    /* ѭ��pstBgPlmnIdList�е�ÿһ��PLMN ID, ��ֵ��pstIntraPlmnSearchInfo */
    ulTotalNum                             = pstBgSearchRslt->ucPlmnNum;
    pstSearchedPlmnListInfo->ulHighPlmnNum = pstBgSearchRslt->ucPlmnNum;

    if (pstSearchedPlmnListInfo->ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstSearchedPlmnListInfo->ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
        ulTotalNum                             = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    pstSearchedPlmnListInfo->ulLowPlmnNum  = 0x0;

    for ( i = 0 ; i < ulTotalNum; i++ )
    {
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMcc = pstBgSearchRslt->astPlmnId[i].stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMnc = pstBgSearchRslt->astPlmnId[i].stPlmnId.ulMnc;
    }


    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo
 ��������  : ��Lģ����������е�PLMN��ϢתΪ�ڲ�������Ϣ�ṹ��PLMN��Ϣ
 �������  : pstPlmnIdList: ��������е�PLMN��Ϣ
 �������  : pstSearchedPlmnListInfo: �ڲ�������Ϣ�ṹ��PLMN��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��9��26��
   ��    ��   : w00167002
   �޸�����   : NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo_PlmnSelection����
                ���Ƹ���ΪNAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo������
                �ļ�NasMmcFsmPlmnSelection.c�ļ�Ǩ�Ƶ�NasMmcComFunc.c
 3.��    ��   : 2011��10��4��
   ��    ��   : s46746
   �޸�����   : �޸ı�����pstInterPlmnSearchInfoΪpstSearchedPlmnListInfo,��ṹ������һ��
 4.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL_BG��Ŀ����:L�������б�ṹ�����,Я�����뼼��
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(
    MMC_LMM_PLMN_ID_LIST_STRU                              *pstLMMPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    pstSearchedPlmnListInfo->enRatType = NAS_MML_NET_RAT_TYPE_LTE;

    /* ѭ��pstLMMPlmnList�е�ÿһ��������PLMN ID,��ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstLMMPlmnList->ulHighPlmnNum) && (i < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)); i++)
    {
        /* ��ת��ΪSIM��ʽ */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmnList->astHighPlmnWithRatList[i].aucPlmnId, MMC_LMM_PLMN_ID_LEN);

        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        pstSearchedPlmnListInfo->astHighPlmnList[i]         = stPlmn;
    }

    pstSearchedPlmnListInfo->ulHighPlmnNum = i;

    /* ѭ��pstLMMPlmnList�е�ÿһ��������PLMN ID,��PLMN ID��������ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstLMMPlmnList->ulLowPlmnNum) && (i < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)); i++)
    {
        /* ��ת��ΪSIM��ʽ */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmnList->astLowPlmnWithRatList[i].stPlmnIdWithRat.aucPlmnId, MMC_LMM_PLMN_ID_LEN);

        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        pstSearchedPlmnListInfo->astLowPlmnList[i].lRscp    = pstLMMPlmnList->astLowPlmnWithRatList[i].lRscp;


        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId = stPlmn;
    }
    pstSearchedPlmnListInfo->ulLowPlmnNum = i;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo
 ��������  : ��Lģ�ı�����������е�PLMN��ϢתΪ�ڲ�������Ϣ�ṹ��PLMN��Ϣ
 �������  : pstLmmPlmnList          - ��������е�PLMN��Ϣ
 �������  : pstSearchedPlmnListInfo - �ڲ�������Ϣ�ṹ��PLMN��Ϣ
             enRatType               - ���뼼��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��4��25��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��19��
   ��    ��   : z00161729
   �޸�����   : DTS2012061908820:L�ϱ�bg����ʧ��û�д��κ�����ʱδ���½��뼼��

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo(
    LMM_MMC_BG_PLMN_SEARCH_CNF_STRU                        *pstLmmPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
     NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        enRatType
)
{
    VOS_UINT32                          ulIndex;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;
    VOS_UINT32                          ulTotalNum;

    pstSearchedPlmnListInfo->enRatType     = enRatType;

    ulTotalNum                             = pstLmmPlmnList->ulPlmnNum;
    pstSearchedPlmnListInfo->ulHighPlmnNum = pstLmmPlmnList->ulPlmnNum;

    if (pstSearchedPlmnListInfo->ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstSearchedPlmnListInfo->ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
        ulTotalNum                             = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    pstSearchedPlmnListInfo->ulLowPlmnNum  = 0x0;

    for ( ulIndex = 0; ulIndex < ulTotalNum; ulIndex++ )
    {
        pstSearchedPlmnListInfo->enRatType = pstLmmPlmnList->astPlmnIdWithRatList[ulIndex].enPlmnRat;
        PS_MEM_CPY(stLmmPlmn.aucPlmnId, pstLmmPlmnList->astPlmnIdWithRatList[ulIndex].aucPlmnId, MMC_LMM_PLMN_ID_LEN);
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn, &stGUNasPlmn);
        pstSearchedPlmnListInfo->astHighPlmnList[ulIndex].ulMcc = stGUNasPlmn.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[ulIndex].ulMnc = stGUNasPlmn.ulMnc;
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MML_IsPlmnWithRatInPlmnList
 ��������  : ���PLMN�Ƿ����б���
 �������  : NAS_MML_PLMN_ID_STRU               *pstPlmnId
             NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
             NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
             VOS_UINT32                          ulPlmnNum
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulPlmnNum
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    if (ulPlmnNum > pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_IsPlmnWithRatInPlmnList: Plmn Num Overflow!");
        return VOS_FALSE;
    }

    /* ����Ӧ���뼼����PLMN ID �Ƿ����б��� */
    for (i = 0; i < ulPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++)
        {
            /* Modified by z00234330 for PCLINT����, 2014-06-16, begin */
            if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                                 &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
             && (enRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType))
            {
                return VOS_TRUE;
            }
            /* Modified by z00234330 for PCLINT����, 2014-06-16, end */
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertPlmnId2NasFormat
 ��������  : ��ԭPLMNidת��ΪNAS�ڲ�ʹ�ø�ʽ��¼
             ����:MCCΪ460,MNCΪ01ʱ,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        <----
             pstPlmnId->Mnc = 0x000100      pstPlmnId->Mnc = 0x00000001
 �������  : pstPlmnId - ԭplmn��ʽ
 �������  : pstPlmnId - nas�ڲ�plmn��ʽ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertPlmnId2NasFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnMncNum
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           aucTmp[4];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;

    PS_MEM_SET(aucTmp, 0, sizeof(aucTmp));
    ulMcc = 0;
    ulMnc = 0;

    ulMcc            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;

    for ( i = 0 ; i < 3 ; i++ )
    {
        aucTmp[i]     = ulMcc & 0x0f;
        ulMcc         >>=  4;
    }

    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    /*����MNCǰ����ձ���*/
    PS_MEM_SET(aucTmp, 0, sizeof(aucTmp));

    ulMnc           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;

    for ( i = 0 ; i < 3 ; i++ )
    {
        aucTmp[i]     = ulMnc & 0x0f;
        ulMnc         >>=  4;
    }

    if(NAS_MML_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucPlmnMncNum)
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RemoveSpecDplmnFromeNplmnList
 ��������  : ��ָ��DPLMN����NPLMN List��ɾ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RemoveSpecDplmnFromNplmnList(
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstSpecDplmn,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                        stTempLai;
    VOS_UINT8                                               i;

    PS_MEM_SET(&stTempLai, 0x00, sizeof(NAS_MML_LAI_STRU));

    pstRatPrioList       = NAS_MML_GetMsPrioRatList();
    stTempLai.stPlmnId   = pstSpecDplmn->stSimPlmnWithRat.stPlmnId;

    for (i = 0;  i < pstRatPrioList->ucRatNum; i++)
    {
        stTempLai.enCampPlmnNetRat = pstRatPrioList->aucRatPrio[i];

        if (VOS_FALSE == NAS_MMC_IsNetRatContainedInSimRat(stTempLai.enCampPlmnNetRat, pstSpecDplmn->stSimPlmnWithRat.usSimRat))
        {
            continue;
        }

        NAS_MMC_DeleteDPlmnNPlmnList(&(stTempLai), pstSpecDplmn->enRegDomain, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDplmnNplmnInfo
 ��������  : ����mmc DPLMN��NPLMN��Ϣ
 �������  : pstNvimCfgDPlmnNPlmnInfo - nv����dplmn��nplmn��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�
  2.��    ��   : 2015-5-18
    ��    ��   : c00318887
    �޸�����   : DPlmn���ݺ����Ƚ���HPLMN
  3.��    ��   : 2015��10��21��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
  4.��    ��   : 2015��12��15��
    ��    ��   : s00217060
    �޸�����   : DTS2015120701561:��ֹ����Խ��
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateDplmnNplmnInfo(
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    VOS_UINT16                                              usSimRat;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain;

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
    NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM_UINT8             enType;
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

    enRegDomain              = NAS_MMC_REG_DOMAIN_BUTT;
    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));

    /* ��ֹNV��Խ�磬���쳣���� */
    if (pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum > NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usDplmnListNum of NVIM is greater than NAS_MMC_MAX_CFG_DPLMN_NUM");

        pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = NAS_MMC_NVIM_MAX_CFG_DPLMN_NUM;
    }

    /* ��NV�е�DPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList + (ulStep * (NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);


        /* �洢PLMN��Ӧ��RAT */
        usSimRat    = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                                | pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        enType      = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX]);
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

        /* ������Ҫ��ӵ�DPLMN�Ѿ����ڣ�����Ҫ�ظ���� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, usSimRat, pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            continue;
        }

        if ((VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
         && (NAS_MML_INVALID_SIM_RAT != usSimRat))
        {
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].stSimPlmnWithRat.stPlmnId = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].stSimPlmnWithRat.usSimRat = usSimRat;
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].enRegDomain               = enRegDomain;

            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].enType                    = enType;
            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

            pstDPlmnNPlmnCfgInfo->usDplmnListNum++;

        }

        /* ��������б������ﵽ������ʱ�������� */
        if (pstDPlmnNPlmnCfgInfo->usDplmnListNum >= NAS_MMC_MAX_CFG_DPLMN_NUM)
        {
            /* normal��ӡ */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usDplmnListNum of pstDPlmnNPlmnCfgInfo is NAS_MMC_MAX_CFG_DPLMN_NUM");
            break;
        }
    }


    /* NV��ȱ��� */
    if (pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum > NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usNplmnListNum of NVIM is greater than NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM");
        pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum    = NAS_MMC_NVIM_MAX_CFG_NPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn, pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList + (ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);


        /* �洢PLMN��Ӧ��RAT */
        usSimRat = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                     | pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        enType      = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX]);
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

        /* ������Ҫ��ӵ�NPLMN�Ѿ����ڣ�����Ҫ�ظ���� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, usSimRat, pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
        {
            continue;
        }

        if ((VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
         && (NAS_MML_INVALID_SIM_RAT != usSimRat))
        {
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].stSimPlmnWithRat.stPlmnId = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].stSimPlmnWithRat.usSimRat = usSimRat;
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].enRegDomain = enRegDomain;

            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].enType                    = enType;
            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

            pstDPlmnNPlmnCfgInfo->usNplmnListNum++;

        }
        /* ��������б������ﵽ������ʱ�������� */
        if (pstDPlmnNPlmnCfgInfo->usNplmnListNum >= NAS_MMC_MAX_CFG_NPLMN_NUM)
        {
            /* normal��ӡ */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateDplmnNplmnInfo: usNplmnListNum of pstDPlmnNPlmnCfgInfo is NAS_MMC_MAX_CFG_NPLMN_NUM");
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDPlmnNPlmnCfgHplmnInfo
 ��������  : ����DPLMNNPLMN���ܿ�����Ϣ��HPLMN��Ϣ
 �������  : pstNvimCfgDPlmnNPlmnFlagInfo - nv����DPLMNNPLMN���ܿ��������Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��8��
    ��    ��   : c00188733
    �޸�����   : ��������������Ŀ�޸�
  2.��    ��   : 2015��12��15��
    ��    ��   : s00217060
    �޸�����   : DTS2015120701561:�ظ���EHPLMN�����
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateDPlmnNPlmnCfgInfo(
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                      *pstNvimDPlmnNPlmnCfg,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{

    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;

    PS_MEM_SET(&stTempPlmn, 0x00, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0x00, sizeof(stNvimPlmn));

    /* ��NV�е�EHPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if (pstNvimDPlmnNPlmnCfg->ucEHplmnNum > NAS_MMC_MAX_CFG_HPLMN_NUM)
    {
        pstNvimDPlmnNPlmnCfg->ucEHplmnNum = NAS_MMC_MAX_CFG_HPLMN_NUM;
    }

    for (ulStep = 0; ulStep < pstNvimDPlmnNPlmnCfg->ucEHplmnNum; ulStep++)
    {
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimDPlmnNPlmnCfg->aucEHplmnList+ (ulStep * NAS_MML_SIM_PLMN_ID_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);

        /* ������Ҫ��ӵ�EHPLMN�Ѿ����ڣ�����Ҫ�ظ���� */
        if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stTempPlmn, pstDPlmnNPlmnCfgInfo->ucEHplmnNum, pstDPlmnNPlmnCfgInfo->astEHplmnList))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
        {
            pstDPlmnNPlmnCfgInfo->astEHplmnList[pstDPlmnNPlmnCfgInfo->ucEHplmnNum] = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->ucEHplmnNum++;
        }
    }

    PS_MEM_CPY(pstDPlmnNPlmnCfgInfo->aucVersionId, pstNvimDPlmnNPlmnCfg->aucVersionId, NAS_MCC_INFO_VERSION_LEN);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MML_DelPlmnWithRatInPlmnList
 ��������  : ɾ���б����ظ�PLMN
 �������  : NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                   pstPlmnSelectionListInfo
 �������  : pstPlmnSelectionListInfo
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��28��
    ��    ��   : z00234330
    �޸�����   : covertity�޸�

*****************************************************************************/
VOS_VOID  NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList (
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    /* ɾ���ظ���PLMN */
    for (i = 0; i < NAS_MML_MIN(pstPlmnSelectionListInfo->usSearchPlmnNum, NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST); )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; )
        {
            if (VOS_TRUE == NAS_MMC_IsPlmnWithRatInPlmnList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId),
                                                            pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType,
                                                            pstPlmnSelectionListInfo,
                                                            i))
            {
                /* ɾ����Ӧ��RAT */
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1]),
                            ((pstPlmnSelectionListInfo->astPlmnSelectionList[i]).ucRatNum - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                /*lint +e961*/

                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;

            }
            else
            {
                j++;
            }
        }

        /* ���뼼������Ϊ0ʱ��ɾ����Ӧ��PLMN ID */
        if (0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1]),
                        (pstPlmnSelectionListInfo->usSearchPlmnNum - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
            /*lint +e961*/
            pstPlmnSelectionListInfo->usSearchPlmnNum--;
        }
        else
        {
            i++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection
 ��������  : ȷ����ǰ�Ƿ�Ϊ�û�ָ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    VOS_UINT32                          ulEventType
)
{
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == enFsmId )
      && ( ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ )))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
	/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch
 ��������  : ���û��ֶ�����ʱ���жϵ�ǰLAI�Ľ�ֹ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��09��13��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(VOS_VOID)
{
    NAS_MML_LAI_STRU                                       *pstCurrentLai     = VOS_NULL_PTR;
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstForbGprsPlmn   = VOS_NULL_PTR;
    NAS_MMC_FSM_EXTRA_CTX_UNION                            *punParentFsmCtx   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulPlmnLaType;
    VOS_UINT32                                              ulRlst;

    ulPlmnLaType      = NAS_MML_PLMN_FORBID_NULL;
    pstCurrentLai     = NAS_MML_GetCurrCampLai();
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    punParentFsmCtx   = NAS_MMC_GetParentFsmCtx();

    /* �����ǰ״̬����PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
    {
        pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
        pstForbGprsPlmn   = NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection();
    }

    /* ��ǰ��״̬����ѡ��״̬�����ҵ�ǰ�ĸ�״̬�������������ݴ��ڣ���ȡ��״̬����ؽ�ֹ��Ϣ */
    else if ( (NAS_MMC_FSM_PLMN_SELECTION == enParentFsmId)
           && (VOS_NULL_PTR               != punParentFsmCtx) )
    {
        pstForbRoamLaInfo = &(punParentFsmCtx->stPlmnSelectionCtx.stForbRoamLaInfo);
        pstForbGprsPlmn   = &(punParentFsmCtx->stPlmnSelectionCtx.stForbGprsPlmn);
    }
    else
    {
        /* ��ǰ��״̬������ѡ��״̬�������ߵ�ǰ�ĸ�״̬��������������Ϊ�գ�ֱ���쳣���� */
        return ulPlmnLaType;
    }

    /* �Ƿ��� ForbLA��Ϣ�� */
    ulRlst =  NAS_MML_IsLaiInDestLaiList(pstCurrentLai,
                                        pstForbRoamLaInfo->ucForbRoamLaNum,
                                        pstForbRoamLaInfo->astForbRomLaList);

    if(VOS_TRUE == ulRlst)
    {
         ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
    }


    /* ��forbid plmn for gprs�б��� */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                   1,
                                                   pstForbGprsPlmn);
    if(VOS_TRUE == ulRlst)
    {
        ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS;
    }

    return ulPlmnLaType;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecTypePlmnIdInDestPlmnList
 ��������  : �ж�ָ�����͹��ܵ�PLMN ID�Ƿ����б���
 �������  : stSpecPlmnId:     ��Ҫ�жϵ�PLMN ID
              enSpecPlmnType:   PLMN ID������
              ucPlmnNum:        �б���plmn id�ĸ���
              pstPlmnIdList:    plmn�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID���б���
              VOS_FALSE : PLMN ID�����б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecTypePlmnIdInDestPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSpecPlmnId,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    VOS_UINT8                           ucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
)
{
    /* ��ָ����PLMN����ΪH/U/O,��ʹ��Sim���͵�PLMN���жϵ�ǰPLMNID�Ƿ���
        �����б��� */
    if ( (NAS_MMC_PLMN_TYPE_HPLMN  == enSpecPlmnType)
      || (NAS_MMC_PLMN_TYPE_UPLMN  == enSpecPlmnType)
      || (NAS_MMC_PLMN_TYPE_OPLMN  == enSpecPlmnType) )
    {
        if ( VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstSpecPlmnId,
                                                               ucPlmnNum,
                                                               pstPlmnIdList) )
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ��ָ����PLMN���Ͳ�ΪH/U/O,��ʹ��BCCH���͵�PLMN���жϵ�ǰPLMNID�Ƿ���
        �����б��� */
    if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstSpecPlmnId,
                                                           ucPlmnNum,
                                                           pstPlmnIdList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateCsPsRestriction_WasInfo
 ��������  : ����WAS�µ�AccessBar��Ϣ�Լ�Bar״̬�仯��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  3.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : ����С����ֹ����ҵ����
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateCsPsRestriction_WasInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{
    /* ���õ�ǰ��Cs����ע��ı任��ʶ */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;
    /* ���õ�ǰ��Ps����ע��ı任��ʶ */
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

    if (VOS_FALSE == pstWrrSysInfo->stCsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Cs����ע��ı任��ʶ */
            pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    if (VOS_FALSE == pstWrrSysInfo->stPsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Ps����ע��ı任��ʶ */
            pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    /* ����CS����������Ϣ */
    NAS_MML_SetCsRestrictRegisterFlg(pstWrrSysInfo->stCsRestriction.enRestrictRegister);
    NAS_MML_SetCsRestrictPagingFlg(pstWrrSysInfo->stCsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    NAS_MML_SetCsRestrictNormalServiceFlg(pstWrrSysInfo->stCsRestriction.enRestrictNormalService);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(pstWrrSysInfo->stCsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */


    /* ����PS����������Ϣ */
    NAS_MML_SetPsRestrictRegisterFlg(pstWrrSysInfo->stPsRestriction.enRestrictRegister);
    NAS_MML_SetPsRestrictPagingFlg(pstWrrSysInfo->stPsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    NAS_MML_SetPsRestrictNormalServiceFlg(pstWrrSysInfo->stPsRestriction.enRestrictNormalService);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(pstWrrSysInfo->stPsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    return;
}






/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateCsPsRestriction_GasSysInfo
 ��������  : ����GAS�µ�Restriction��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  3.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : ����С����ֹ����ҵ����
  4.��    ��   : 2012��12��27��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE:���USIM��GSM��ֹ���룬��������ע����������н���
  5.��    ��   : 2013��1��8��
    ��    ��   : w00176964
    �޸�����   : DTS2013010706340:G����PS���������ҵ��,G�½����ֹʱ�ñ��Ӧ��ʼ��ΪFALSE
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateCsPsRestriction_GasSysInfo(
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{
    /* GSM���޷�������,ȫ�ֱ�����λ�� */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag = VOS_FALSE;
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag = VOS_FALSE;

    /* ����CS/PS �Ƿ�����ע��ı�־ */
    switch (pstGrrSysInfo->unAcInfo.ucRestrictType)
    {
        case RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE:
            {
                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_TRUE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
            }
            break;
        case RRC_NAS_ACCESS_NO_RESTRICTION:
            {
                if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
                {
                    /* ���õ�ǰ��Cs����ע��ı任��ʶ */
                    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
                }


                if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
                {
                    /* ���õ�ǰ��Ps����ע��ı任��ʶ */
                    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
                }

                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
            }
            break;

        case RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE:
            {
                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
            }
            break;

        case RRC_NAS_ACCESS_RESTRICTION_EMERGENCY_SERVICE:
            {
                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_TRUE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
            }
            break;

        default:
            break;

    }

    /* PS�޽���ҵ�񣬸�ֵʼ�ղ����� */
    NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);

    /* USIM����ֹGSM����ʱ��Ҳ��Ҫ����CS/PS �Ƿ�����ע��ı�־ */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        /* ���õ�ǰ��Cs����ע��ı任��ʶ */
        pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;

        /* ���õ�ǰ��Ps����ע��ı任��ʶ */
        pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

        /* ����CS����������Ϣ */
        NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
        NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);

        /* ����PS����������Ϣ */
        NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);

    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateCsPsRestriction_WasInfo
 ��������  : ����WAS�µ�AccessBar��Ϣ�Լ�Bar״̬�仯��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  3.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : ����С����ֹ����ҵ����
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateCsPsRestriction_AcChangeInd(
    RRMM_W_AC_INFO_CHANGE_IND_STRU     *pstWAcChangeInd,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{

    /* ���õ�ǰ��Cs����ע��ı任��ʶ */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;

    /* ���õ�ǰ��Ps����ע��ı任��ʶ */
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

    if (VOS_FALSE == pstWAcChangeInd->stCsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Cs����ע��ı任��ʶ */
            pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    if (VOS_FALSE == pstWAcChangeInd->stPsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Ps����ע��ı任��ʶ */
            pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    /* ����CS����������Ϣ */
    NAS_MML_SetCsRestrictRegisterFlg(pstWAcChangeInd->stCsRestriction.enRestrictRegister);
    NAS_MML_SetCsRestrictPagingFlg(pstWAcChangeInd->stCsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    NAS_MML_SetCsRestrictNormalServiceFlg(pstWAcChangeInd->stCsRestriction.enRestrictNormalService);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(pstWAcChangeInd->stCsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    /* ����PS����������Ϣ */
    NAS_MML_SetPsRestrictRegisterFlg(pstWAcChangeInd->stPsRestriction.enRestrictRegister);
    NAS_MML_SetPsRestrictPagingFlg(pstWAcChangeInd->stPsRestriction.enRestrictPagingRsp);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    NAS_MML_SetPsRestrictNormalServiceFlg(pstWAcChangeInd->stPsRestriction.enRestrictNormalService);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(pstWAcChangeInd->stPsRestriction.enRestrictEmergencyService);
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcRatToNasFormat
 ��������  : ���������ϵĽ��뼼������ת��ΪNAS��ʽ�Ľ��뼼������
 �������  : ulRrcRat �����������Ľ��뼼������
 �������  : enRat NAS��ʽ�Ľ��뼼������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertRrcRatToNasFormat(
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    switch (ulRrcRat)
    {
        case RRC_NAS_RAT_WCDMA_FDD:

            *penRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        case RRC_NAS_RAT_GSM:

            *penRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case RRC_NAS_RAT_LTE:

            *penRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcRatToNasFormat,Unexpected Rrc rat!");
            *penRat = NAS_MML_NET_RAT_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertNasRatToRrcFormat
 ��������  : ��NAS��ʽ�Ľ��뼼������ת��Ϊ�������ϵĽ��뼼������
 �������  : enNasRat NAS��ʽ�Ľ��뼼������
 �������  : penRrcRat �����������Ľ��뼼������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��24��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

 2.��    ��   : 2013��10��29��
   ��    ��   : w00167002
   �޸�����   : BUTT-->ת��Ϊ��������BUTT
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertNasRatToRrcFormat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRrcRat
)
{
    switch (enNasRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            *penRrcRat = RRC_NAS_RAT_GSM;
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            *penRrcRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case NAS_MML_NET_RAT_TYPE_LTE:
            *penRrcRat = RRC_NAS_RAT_LTE;
            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcRatToNasFormat,Unexpected Nas rat!");

            *penRrcRat = RRC_NAS_RAT_TYPE_BUTT;

            break;
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRrcCoverTypeToNasFormat
 ��������  : ���������ϵ����縲������ת��ΪNAS��ʽ�����縲������
 �������  : enRrcCoverType ���������������縲������
 �������  : *penCoverType NAS��ʽ�����縲������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��5��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID   NAS_MMC_ConvertRrcCoverTypeToNasFormat(
    RRC_NAS_COVERAGE_TYPE_ENUM_UINT32   enRrcCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
)
{
    switch (enRrcCoverType)
    {
        case RRC_NAS_COVERAGE_TYPE_NONE:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case RRC_NAS_COVERAGE_TYPE_LOW:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case RRC_NAS_COVERAGE_TYPE_HIGH:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcCoverTypeToNasFormat,Unexpected Rrc coverage type!");
            *penCoverType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmCoverTypeToNasFormat
 ��������  : ���������ϵ����縲������ת��ΪNAS��ʽ�����縲������
 �������  : enLmmCoverType ���������������縲������
 �������  : *penCoverType NAS��ʽ�����縲������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��5��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID   NAS_MMC_ConvertLmmCoverTypeToNasFormat(
    MMC_LMM_COVERAGE_TYPE_ENUM_UINT32   enLmmCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
)
{
    switch (enLmmCoverType)
    {
        case MMC_LMM_COVERAGE_TYPE_NONE:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case MMC_LMM_COVERAGE_TYPE_LOW:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case MMC_LMM_COVERAGE_TYPE_HIGH:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertLmmCoverTypeToNasFormat,Unexpected Rrc coverage type!");
            *penCoverType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return;
}
#endif



#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmRatToRrcFormat
 ��������  : ��LMM����ϵĽ��뼼������ת��ΪRRC��ʽ�Ľ��뼼������
 �������  : ulLmmRat �����������Ľ��뼼������
 �������  : enRat RRC��ʽ�Ľ��뼼������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��4��28��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmRatToRrcFormat(
    MMC_LMM_RAT_TYPE_ENUM_UINT8         ucLmmRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRat
)
{
    switch (ucLmmRat)
    {
        case MMC_LMM_RAT_WCDMA_FDD:
            *penRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case MMC_LMM_RAT_GSM:
            *penRat = RRC_NAS_RAT_GSM;
            break;

        case MMC_LMM_RAT_LTE:
            *penRat = RRC_NAS_RAT_LTE;
            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertLmmRatToRrcFormat,Unexpected Rrc rat!");
            *penRat = RRC_NAS_RAT_TYPE_BUTT;
            break;
    }

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertGasNetModeToMmlNetMode
 ��������  : ��GAS��ϵͳ��Ϣ������ģʽ����תΪMML�е�����ģʽ����
 �������  : enGasNetMode: GASϵͳ��Ϣ�е�����ģʽ
 �������  : ��
 �� �� ֵ  : MML�е�����ģʽ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��5��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_NET_MODE_ENUM_UINT8 NAS_MMC_ConvertGasNetModeToMmlNetMode(
    GRRMM_NW_OP_MODE_ENUM_UINT8         enGasNetMode
)
{
    NAS_MML_NET_MODE_ENUM_UINT8         enMmlNetMode;

    switch ( enGasNetMode )
    {
        case GRRMM_NW_OP_MODE_I:
            enMmlNetMode = NAS_MML_NET_MODE_I;
            break;

        case GRRMM_NW_OP_MODE_II:
            enMmlNetMode = NAS_MML_NET_MODE_II;
            break;

        case GRRMM_NW_OP_MODE_III:
            enMmlNetMode = NAS_MML_NET_MODE_III;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertGasNetModeToMmlNetMode, net mode invalid");
            enMmlNetMode = NAS_MML_NET_MODE_BUTT;
            break;
    }

    return enMmlNetMode;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsOptItemVaild_WasSysInfo
 ��������  : WAS ϵͳ��Ϣ��Я����Opt������Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsOptItemVaild_WasSysInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo
)
{
    if ((0 == pstWrrSysInfo->ucCnCommonSize)
     && (0 == pstWrrSysInfo->ucCsInfoSize)
     && (0 == pstWrrSysInfo->ucPsInfoSize)
     && (0 == pstWrrSysInfo->bitOpPlmnId)
     && (0 == pstWrrSysInfo->bitOpCsDrx)
     && (0 == pstWrrSysInfo->bitOpPsDrx))
    {
        return VOS_FALSE;
    }

    if ((RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucCnCommonSize)
     || (RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucCsInfoSize)
     || (RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucPsInfoSize))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableUtran_AnyCellSearch
 ��������  : ����Anycell����״̬�������Utran��Disable,��Ҫ����Enable Utran��UE�ܹ���Utran������פ��
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableUtran_AnyCellSearch (VOS_VOID)
{
    /* ������Anycell����״̬��ʱ���ҵ�ǰUtran��Disable�ˣ���Re-Enable Utran */

    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo
 ��������  : �յ�GASϵͳ��Ϣ��ʱ�������ʱUTRAN��Re-Enable״̬����UTRAN����Disable
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo (VOS_VOID)
{
    /* ���Utran�ڽ�ֹ���뼼���б����Ҵ�ʱUtranΪEnable״̬�����յ�Gas��ϵͳ��Ϣ��Disable Utran */
    if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_WCDMA))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_REENABLE != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init
 ��������  : ��ʼAnycell����ǰ�����Utran��Disable,����Ҫ����Enable Utran
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init (VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsNeedEnableUtran_AnyCellSearch())
    {
        NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_REENABLE);
        NAS_MMC_SndAsRatCapabilityStatusChangeInfo();
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus
 ��������  : �յ�GASϵͳ��Ϣ��ʱ�������ʱUTRAN��Re-Enable״̬����UTRAN����Disable
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus (VOS_VOID)
{

    if (VOS_TRUE == NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo())
    {
        NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        NAS_MMC_SndAsRatCapabilityStatusChangeInfo();
    }

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateOperNameInfo
 ��������  : ����Operate Name����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��8��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateOperNameInfo(
    RRC_PLMN_ID_STRU                   *pstPlmnId
)
{
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstOperNameInfo = VOS_NULL_PTR;

    /* ���µ�ǰפ��������Ϣ */
    pstOperNameInfo = NAS_MML_GetOperatorNameInfo();

    /* �������ĳ����������뵱ǰפ����PLMN ID��ͬ�����ȫ�ֱ��� */
    if ((pstOperNameInfo->stOperatorPlmnId.ulMcc != pstPlmnId->ulMcc)
     || (pstOperNameInfo->stOperatorPlmnId.ulMnc != pstPlmnId->ulMnc))
    {
        /* ���aucOperatorNameShort��aucOperatorNameLong */
        PS_MEM_SET(pstOperNameInfo, 0x00, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
        pstOperNameInfo->stOperatorPlmnId.ulMcc = pstPlmnId->ulMcc;
        pstOperNameInfo->stOperatorPlmnId.ulMnc = pstPlmnId->ulMnc;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateNetworkInfo_GasSysInfo
 ��������  : ��鲢����GSM�µ�ϵͳ��Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��15��
    ��    ��   : w00166186
    �޸�����   : DTS2011111500751,LACֵ�ߵ�λ���淴�ˣ����·��������Ľ�ֹLACֵ����ȷ
  3.��    ��   : 2012��6��9��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL���������޸�
  4.��    ��   : 2012��11��13��
    ��    ��   : z40661
    �޸�����   : V7R1C50 GUL���������޸�

  5.��    ��   : 2013��6��25��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE ST����:����PS���GPRS�Ƿ�֧�ֱ�־��

  6.��    ��   : 2013��10��29��
    ��    ��   : z00234330
    �޸�����   : �͹��Ľӿں���dts2013102911530
  7.��    ��   : 2014��2��14��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
  8.��   ��    : 2014-04-15
    ��   ��    : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����:�ϴ�פ��LAI��Ϣ���浽MML��
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkInfo_GasSysInfo(
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_3GPP_REL_STRU      *pst3GPPRelVersion   = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
    NAS_MML_LAI_STRU                   *pstOldCampLai       = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, end */


    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo      = VOS_NULL_PTR;

    pstNetWorkInfo  =  NAS_MML_GetNetworkInfo();

    pstGrrSysInfo     = (GRRMM_SYS_INFO_IND_ST *)pstMsg;
    pst3GPPRelVersion = NAS_MML_GetNetwork3GppRel();

    pst3GPPRelVersion->enNetSgsnRel = pstGrrSysInfo->ucSgsnRelease;
    pst3GPPRelVersion->enNetMscRel  = pstGrrSysInfo->ucMsrRelease;

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
    pstOldCampLai       = NAS_MML_GetOldCampLai();

    /* �����ϴ�פ����LAI��Ϣ,Ȼ�����沽����µ�ǰפ��LAI��Ϣ */
    if (VOS_FALSE == NAS_MMC_IsInValidCampPlmn())
    {
        PS_MEM_CPY(pstOldCampLai, &(pstCurrCampPlmnInfo->stLai), sizeof(NAS_MML_LAI_STRU));
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, end */

    /* ��ǰucGprsSupportIndΪGsmʱ������ǰ��֧��GPRS���޷���PS����Ϣ�л�ȡ����ģʽ */
    if (NAS_MML_GAS_SUBMODE_GSM == pstGrrSysInfo->ucGprsSupportInd)
    {
        /* ���õ�ǰ����ģʽΪ��ЧNAS_MML_NET_MODE_BUTT */
        pstCurrCampPlmnInfo->enNetworkMode = NAS_MML_NET_MODE_BUTT;

        pstCurrCampPlmnInfo->ucRac = NAS_MML_RAC_INVALID;
    }
    else
    {
        /* ��������ģʽ ��ֻ����PS����Ϣ��Ч������£�����ģʽ����Ч */
        if (GRRMM_NW_OP_MODE_INVALID != pstGrrSysInfo->ucNetworkOperationMode)
        {
            pstCurrCampPlmnInfo->enNetworkMode =
                NAS_MMC_ConvertGasNetModeToMmlNetMode(pstGrrSysInfo->ucNetworkOperationMode);
        }

        pstCurrCampPlmnInfo->ucRac                = pstGrrSysInfo->ucRac;
    }

    /* ����GAS�ϱ���GPRS֧��ָʾ��ת��Ϊ��Ӧ��ϵͳ��ģʽ */
    pstCurrCampPlmnInfo->enSysSubMode = NAS_MML_ConvertGprsSupportIndToSysSubMode(pstGrrSysInfo->ucGprsSupportInd);

    /* ������·����Ӫ��������Ϣ */
    NAS_MMC_UpdateOperNameInfo(&(pstGrrSysInfo->PlmnId));

    /* ���µ�ǰפ��������Ϣ */
    pstCurrCampPlmnInfo->stLai.stPlmnId.ulMcc = pstGrrSysInfo->PlmnId.ulMcc;
    pstCurrCampPlmnInfo->stLai.stPlmnId.ulMnc = pstGrrSysInfo->PlmnId.ulMnc;

    pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_GSM;

    /* ���µ�ǰפ�������LAC��RAC��Ϣ */
    pstCurrCampPlmnInfo->stLai.aucLac[0]      = (VOS_UINT8)((pstGrrSysInfo->usLac & 0xFF00) >> 8);
    pstCurrCampPlmnInfo->stLai.aucLac[1]      = (VOS_UINT8)(pstGrrSysInfo->usLac & 0x00FF);


    /* ��С���л�ȡGPRS֧����Ϣ */
    pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = pstGrrSysInfo->ucGprsSupportInd;

    /* ����cell Info */
    pstCurrCampPlmnInfo->stCampCellInfo.ucCellNum = 1;
    pstCurrCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId = pstGrrSysInfo->usCellId;

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    NAS_MML_SetCurrCampArfcn(0x0);
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    /* ���µ�ǰ��ϵͳGsmBand��Ϣ��W,L פ�� BandΪ0 */
    pstBandInfo = NAS_MML_GetCurrBandInfo();
    pstBandInfo->unWcdmaBand.ulBand      = 0;
    pstBandInfo->unGsmBand.ulBand        = pstGrrSysInfo->unGsmBand.ulBand;
#if (FEATURE_ON == FEATURE_LTE)
    pstBandInfo->stLteBand.aulLteBand[0] = 0;
    pstBandInfo->stLteBand.aulLteBand[1] = 0;
#endif

    /* ���µ�ǰ����� CS/PS��ķ������������ */
    NAS_MMC_UpdateCsPsRestriction_GasSysInfo(pstGrrSysInfo, NAS_MML_GetNetworkInfo());
    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateNetworkInfo_WasSysInfo
 ��������  : �յ�WAS��ϵͳ��Ϣ�Ĵ���
 �������  : RRMM_SYS_INFO_IND_STRU* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��9��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL���������޸�
  3.��    ��   : 2012��11��13��
    ��    ��   : z40661
    �޸�����   : V7R1C50 GUL���������޸�
  4.��    ��   : 2014��2��14��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
  5.��   ��    : 2014-04-15
    ��   ��    : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����:�ϴ�פ��LAI��Ϣ���浽MML��
  6.��   ��    : 2015-6-11
    ��   ��    : b00269685
    �޸�����   : ����ota �� sys
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkInfo_WasSysInfo(
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo   = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo  = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
    NAS_MML_LAI_STRU                   *pstOldCampLai   = VOS_NULL_PTR;
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, end */

    pstWrrSysInfo = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

    if (VOS_FALSE == NAS_MMC_IsOptItemVaild_WasSysInfo(pstWrrSysInfo))
    {
        return;
    }

    pstNetWorkInfo  =  NAS_MML_GetNetworkInfo();

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
    pstOldCampLai       = NAS_MML_GetOldCampLai();

    /* �����ϴ�פ����LAI��Ϣ,Ȼ�����沽����µ�ǰפ��LAI��Ϣ */
    if (VOS_FALSE == NAS_MMC_IsInValidCampPlmn())
    {
        PS_MEM_CPY(pstOldCampLai, &(pstNetWorkInfo->stCampPlmnInfo.stLai), sizeof(NAS_MML_LAI_STRU));
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-28, end */

    if (VOS_TRUE == pstWrrSysInfo->bitOpPlmnId)
    {
        /* ������·����Ӫ��������Ϣ */
        NAS_MMC_UpdateOperNameInfo(&(pstWrrSysInfo->PlmnId));

        /* ���µ�ǰפ���������Ϣ */
        pstNetWorkInfo->stCampPlmnInfo.stLai.stPlmnId.ulMcc   = pstWrrSysInfo->PlmnId.ulMcc;
        pstNetWorkInfo->stCampPlmnInfo.stLai.stPlmnId.ulMnc   = pstWrrSysInfo->PlmnId.ulMnc;

        pstNetWorkInfo->stCampPlmnInfo.stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_WCDMA;
    }

    /* ��ȡ LAC, aucCnCommonInfo[0]����Lac, aucCnCommonInfo[1]���� Lac Continued Byte*/
    if (0 != pstWrrSysInfo->ucCnCommonSize)
    {
        pstNetWorkInfo->stCampPlmnInfo.stLai.aucLac[0] = pstWrrSysInfo->aucCnCommonInfo[0];
        pstNetWorkInfo->stCampPlmnInfo.stLai.aucLac[1] = pstWrrSysInfo->aucCnCommonInfo[1];
    }

    /* ���� rac��Ϣ��PS��֧����Ϣ */
    if (0 == pstWrrSysInfo->ucPsInfoSize)
    {
        if (RRC_NAS_SYS_INFO_TYPE_SYS == pstWrrSysInfo->enSysInfoType)
        {
            pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = VOS_FALSE;

            pstNetWorkInfo->stCampPlmnInfo.ucRac = NAS_MML_RAC_INVALID;
        }
    }
    else
    {
        pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = VOS_TRUE;
        pstNetWorkInfo->stCampPlmnInfo.ucRac = pstWrrSysInfo->aucPsInfo[0];
    }

    if (VOS_TRUE == pstWrrSysInfo->bitOpCellId)
    {
        /* ����С��ID */
        pstNetWorkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId = pstWrrSysInfo->ulCellId;
        pstNetWorkInfo->stCampPlmnInfo.stCampCellInfo.ucCellNum               = 1;
    }

    /* ��������ģʽ :aucPsInfo[1]��Bit1ָʾ����ģʽ */
    if ( 0 == (pstWrrSysInfo->aucPsInfo[1] & NAS_MML_NET_MODE_BIT_MASK_WAS_SYS_INFO) )
    {
        /* ����Ϊ����ģʽI ,NAS_MML_NET_MODE_I */
        pstNetWorkInfo->stCampPlmnInfo.enNetworkMode = NAS_MML_NET_MODE_I;
    }
    else
    {
        /* ����Ϊ����ģʽII ,NAS_MML_NET_MODE_II */
        pstNetWorkInfo->stCampPlmnInfo.enNetworkMode = NAS_MML_NET_MODE_II;
    }

    /* ����Sysinfo����ģʽ */
    pstNetWorkInfo->stCampPlmnInfo.enSysSubMode = pstWrrSysInfo->enSysSubMode;

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    NAS_MML_SetCurrCampArfcn(0x0);
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    /* ���µ�ǰ�� W Band ϵͳ��Ϣ��G��Lפ�� BandΪ0 */
    pstNetWorkInfo->stBandInfo.unWcdmaBand.ulBand      = pstWrrSysInfo->unWcdmaBand.ulBand;
    pstNetWorkInfo->stBandInfo.unGsmBand.ulBand        = 0;
#if (FEATURE_ON == FEATURE_LTE)
    pstNetWorkInfo->stBandInfo.stLteBand.aulLteBand[0] = 0;
    pstNetWorkInfo->stBandInfo.stLteBand.aulLteBand[1] = 0;
#endif

    /* ����CsPS ���Ƿ�����ע��ı�־��unBar��־λ */

    NAS_MMC_UpdateCsPsRestriction_WasInfo(pstWrrSysInfo, pstNetWorkInfo);

    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);
    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateSuitPlmnList_LmmSysInfo
 ��������  : �յ�lϵͳ��Ϣ���¹���������Ϣ
 �������  : pstLteSysInfo - ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(
    MMC_LMM_SYS_INFO_STRU              *pstLteSysInfo
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmnId = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucSuitTotalPlmnNum;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;

    pstSuitPlmnList    = NAS_MML_GetSuitPlmnList();
    ucSuitTotalPlmnNum = (VOS_UINT8)pstLteSysInfo->stSpecPlmnIdList.ulSuitPlmnNum;

    if (ucSuitTotalPlmnNum > MMC_LMM_MAX_SRCH_PLMN_NUM)
    {
        ucSuitTotalPlmnNum = MMC_LMM_MAX_SRCH_PLMN_NUM;
    }

    for (ucIndex = 0; ucIndex < ucSuitTotalPlmnNum; ucIndex++)
    {
        pstLmmPlmnId = &(pstLteSysInfo->stSpecPlmnIdList.astSuitPlmnList[ucIndex]);

        /* ���湲��������Ϣ��������ǰפ������ */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

        PS_MEM_CPY(&pstSuitPlmnList->astSuitPlmnList[ucIndex], &stPlmnId, sizeof(pstSuitPlmnList->astSuitPlmnList[ucIndex]));
    }

    pstSuitPlmnList->ucSuitPlmnNum = ucSuitTotalPlmnNum;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateNetworkInfo_LmmSysInfo
 ��������  : ��鲢����LTE�µ�ϵͳ��Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��6��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��4��
    ��    ��   : zhoujun 40661
    �޸�����   : LMM��ϵͳ��Ϣ�������
  3.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  4.��    ��   : 2012��6��9��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL�������޸�
  5.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1���޸�LTEϵͳ��ģʽ

  6.��    ��   : 2012��11��9��
    ��    ��   : z40661
    �޸�����   : DRX TImer�޸�
  7.��    ��   : 2014��2��14��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
  7.��    ��   : 2014��8��14��
    ��    ��   : s00217060
    �޸�����   : DTS2014080700822:����LTEפ����С����FDD����TDD
  8.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNetworkInfo_LmmSysInfo(
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmnId        = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCell         = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId       = VOS_NULL_PTR;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstOperNameInfo     = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;


    pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;

    pstLmmPlmnId = &(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    /* ����PLMN ID��Ϣ����ǰ����Ϣ�� */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

    pstCurCampInfo                       = NAS_MML_GetCurrCampPlmnInfo();
    NAS_MML_InitRssiValue(&(pstCurCampInfo->stCampCellInfo));

    /* ��L�º��������������Ϣ */
    NAS_MML_ClearCsPsRestrictionAll();

    /* ����פ����Ϣ */
    pstOperNameInfo = NAS_MML_GetOperatorNameInfo();
    pstCurrPlmnId   = NAS_MML_GetCurrCampPlmnId();

    pstCurrPlmnId->ulMcc                    = stPlmnId.ulMcc;
    pstCurrPlmnId->ulMnc                    = stPlmnId.ulMnc;

    /* �������ĳ����������뵱ǰפ����PLMN ID��ͬ�����ȫ�ֱ��� */
    if ((pstCurrPlmnId->ulMcc != pstOperNameInfo->stOperatorPlmnId.ulMcc)
     || (pstCurrPlmnId->ulMnc != pstOperNameInfo->stOperatorPlmnId.ulMnc))
    {
        /* ���aucOperatorNameShort��aucOperatorNameLong */
        PS_MEM_SET(pstOperNameInfo, 0x00, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
        pstOperNameInfo->stOperatorPlmnId.ulMcc = stPlmnId.ulMcc;
        pstOperNameInfo->stOperatorPlmnId.ulMnc = stPlmnId.ulMnc;

    }

    /* ����cell Info */
    pstCampCell     = NAS_MML_GetCampCellInfo();

    /* ����С��ID */
    pstCampCell->ucCellNum               = 1;
    pstCampCell->astCellInfo[0].ulCellId = pstLmmSysInfoMsg->stLteSysInfo.ulCellId;

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    NAS_MML_SetCurrCampArfcn(pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    /* ���µ�ǰ��ϵͳGsmBand��Ϣ��W,L פ�� BandΪ0 */
    pstBandInfo = NAS_MML_GetCurrBandInfo();
    pstBandInfo->unWcdmaBand.ulBand      = 0;
    pstBandInfo->unGsmBand.ulBand        = 0;
    pstBandInfo->stLteBand.aulLteBand[0] = pstLmmSysInfoMsg->stLteSysInfo.stLteBand.aulLteBand[0];
    pstBandInfo->stLteBand.aulLteBand[1] = pstLmmSysInfoMsg->stLteSysInfo.stLteBand.aulLteBand[1];

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo->enNetworkMode        = NAS_MML_NET_MODE_INVALID;

    pstCurCampInfo->enSysSubMode         = NAS_MML_RRC_SYS_SUBMODE_LTE;

    pstCurCampInfo->stLai.aucLac[0]      = pstLmmSysInfoMsg->stLteSysInfo.stTac.ucTac;
    pstCurCampInfo->stLai.aucLac[1]      = pstLmmSysInfoMsg->stLteSysInfo.stTac.ucTacCnt;
    pstCurCampInfo->ucRac                = NAS_MML_RAC_INVALID;

    pstCurCampInfo->enLmmAccessType      = pstLmmSysInfoMsg->stLteSysInfo.enAccessType;


    pstCurCampInfo->stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_LTE;

    /* Modified by z00234330 for �͹��Ľӿ� , 2013-10-29, begin */
    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    /* Modified by z00234330 for �͹��Ľӿ� , 2013-10-29, end */
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);

    NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(&pstLmmSysInfoMsg->stLteSysInfo);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetDomainRegStatusInRegInfoList
 ��������  : ��ע����Ϣ�������ȡ��ָ������ָ�����뼼����CS/PS��Ľ����Ϣ
 �������  : pstPlmnId      : ��Ҫ���ҵ�PLMN ID
              enCurNetRatType: ָ������Ľ��뼼��
 �������  : penCsCause     : CS��Ľ����Ϣ
              penPsCause     : PS��Ľ����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��21��
    ��    ��   : w00167002
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID NAS_MMC_GetDomainRegStatusInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ȡע��ԭ���б��ָ�� */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* �жϵ�ǰ�����Ƿ�����ע���б��� */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmnId,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);

    /* ��ǰ������ע���б��У�ȡ�ö�Ӧ���뼼����CS/PS���ע���� */
    if ((ulIndex < pstPlmnRegRejInfo->ucPlmnRegInfoNum)
     && (ulIndex < NAS_MMC_MAX_REG_PLMN_INFO_NUM))
    {
        switch ( enCurNetRatType )
        {

        #if (FEATURE_ON == FEATURE_LTE)

            case NAS_MML_NET_RAT_TYPE_LTE :
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enLCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enLPsRegStatus;
                return;
        #endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enWCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enWPsRegStatus;
                return;

            case NAS_MML_NET_RAT_TYPE_GSM :
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enGCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enGPsRegStatus;
                return;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetDomainRegStatusInRegInfoList: NETRAT TYPE INVALID ");
                return;
        }
    }

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetDomainRegStatusInRegInfoList: can't find the plmn id ");

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnRegInfoAllSucc
 ��������  : ���PLMN�Ƿ���ע��ʧ�ܵ�����Ϣ
 �������  : pstPlmnRegList : PLMN��ע����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE       : PLMN��ע��ʧ�ܵ�����Ϣ��
             VOS_FALSE      : PLMNû��ע��ʧ�ܵ�����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��15��
    ��    ��   : w00167002
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsPlmnRegInfoAllSucc(
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
)
{
	/* G��CS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enGCsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* G��PS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enGPsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* W��CS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */

	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enWCsRegStatus )
	{
	    return VOS_FALSE;
	}
	/* W��PS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enWPsRegStatus )
	{
	    return VOS_FALSE;
	}

#if (FEATURE_ON == FEATURE_LTE)

	/* L��CS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enLCsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* L��PS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLEs */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enLPsRegStatus )
	{
	    return VOS_FALSE;
	}
#endif

	/* ������ΪNAS_MML_REG_FAIL_CAUSE_NULL,����Ϊ������ע��ɹ� */
	return VOS_TRUE;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_NotifyModeChange
 ��������  : ֪ͨ����ģ�鵱ǰ������ģʽ�����仯
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��01��04��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_NotifyModeChange(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType,
    VOS_UINT8                                   ucSimPsRegStatus
)
{
    NAS_MMC_SRV_STA_CHNG_INFO_STRU             *pstLastSrvStaInfo;

    pstLastSrvStaInfo = NAS_MMC_GetSrvStaChngInfo();

    /* ����ģʽ�����仯ʱ��֪ͨAPS��CDS������Ϊ��Чʱ��֪ͨAPS��CDS */
    if ( ( enRatType != pstLastSrvStaInfo->enRatType )
      || ( ( ucSimPsRegStatus != pstLastSrvStaInfo->ucSimPsRegStatus )
        && ( VOS_FALSE == ucSimPsRegStatus )) )
    {
        NAS_MMC_SndApsServiceStatusInd(enRatType, ucSimPsRegStatus);
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
        /* CDMA��رյ�����£���MMC֪ͨCDS���뼼����� */
        NAS_MMC_SndCdsModeChangeInd(enRatType);
#endif
        pstLastSrvStaInfo->enRatType          = enRatType;
        pstLastSrvStaInfo->ucSimPsRegStatus   = ucSimPsRegStatus;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnAllowedInManualMode
 ��������  : �ֶ�ѡ��ģʽʱ��PlmnId�Ƿ�����
 �������  : enPlmnSelectionMode : ѡ��ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��7��7��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,�ڵ�ЧPLMN�в����ý�ֹ��־

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnAllowedInManualMode(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo      = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlst;
    VOS_UINT32                                              ulEplmnValidFlg;

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
    pstEplmnInfo      = NAS_MML_GetEquPlmnList();

    /* �ֶ�ѡ��ģʽ��LTE���������û�ָ����������ͬ */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstUserSpecPlmnId->stPlmnId)))
    {
        return VOS_TRUE;
    }

    /* �ж��ֶ�ѡ��ģʽ��LTE�������ǲ����û�ָ���������EPLMN */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                            pstEplmnInfo->ucEquPlmnNum,
                                            pstEplmnInfo->astEquPlmnAddr);

    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    /* �ֶ�ѡ��ģʽʱ���û�ָ����������ע�ᣬ��LTE���������û�ָ���������EPLMN*/
    if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
     && (VOS_TRUE == ulRlst)
     && (VOS_TRUE == ulEplmnValidFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_SysCfg
 ��������  : SYSCFG������ɺ��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662 disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��SIM��ʱ����ҪDisable Lte;
 4.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 5.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 6.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
 7.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE.
                 ���޸�Ϊ��SYSCFG��,�����Ҫ���������б��Ƿ�ATTACH PS��Ҫ��ENABLE LTE��
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    VOS_UINT32                                              ulRatForbiddenFlg;

    ulRatForbiddenFlg   = NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)SYSCFG���õ�ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч����PS������attach��SIM��
    (3)CS����Ч��CS����ע�� */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE ONLY���������ֹLTE�����������Ҫ��ֹ */
    if ((VOS_FALSE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (VOS_TRUE == ulRatForbiddenFlg))
    {
        return VOS_TRUE;
    }

    /* ��L��ģ��ΪSIM����ֱ��disable Lģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_TRUE;
    }

    /* CS������ע���CS����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* PS����Ч������PS����attach */

    if (((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
       || (VOS_TRUE == pstSyscfgRsltMsg->ulIsNeedAttachPs))
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_SysCfg
 ��������  : SYSCFG������ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE.
                 ���޸�Ϊ��SYSCFG��,�����Ҫ���������б��Ƿ�ATTACH PS��Ҫ��ENABLE LTE��
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)����ģʽ����֧��LTE ONLY */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* ��ǰ����ģʽΪL only,��Ҫenable LTE */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_TRUE;
    }


    /* �ж�ATTACH PS�Ƿ���Ҫ����ENABLE LTE */
    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == pstSyscfgRsltMsg->ulIsNeedAttachPs))
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_AttachPs())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_ModeChange
 ��������  : ModeChange������ɺ��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��SIM��ʱ����ҪDisable Lte;
 4.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 5.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_ModeChange(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)��ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч��SIM��
    (3)CS+PS */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE��ģ,����disable */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS����Ч */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* MSģʽ��CS+PS */
    if (NAS_MML_MS_MODE_PS_CS != NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_ModeChange
 ��������  : ModeChange������ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
10.��    ��   : 2012��12��15��
   ��    ��   : l65478
   �޸�����   : DTS2012120508936:�ڷ����������ʱ��Ҫdisable LTE
11.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
12.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_ModeChange(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    VOS_UINT8                                               ucCsAllowAttachFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)MSģʽ����֧��PS ONLY��CS������ע��
    (3)PS����Ч����USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    ucCsAllowAttachFlg     = NAS_MML_GetCsAttachAllowFlg();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }


    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    /* ��ǰMSģʽΪPS only,��Ҫenable LTE */
    if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == ucCsAllowAttachFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_DetachPs
 ��������  : Detach PS��ɺ��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��SIM��ʱ��ҪDisable Lte
 4.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 5.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachPs(VOS_VOID)
{
    NAS_MMC_DETACH_REQ_CTX_STRU                            *pstDetachReqCtx = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э��3GPP 24.301����,5.5.2.2.2 UE initiated detach procedure completion for EPS services only
    The UE in CS/PS mode 1 or CS/PS mode 2 of operation shall set the update status
    to U2 NOT UPDATED, disable E UTRAN and select GERAN or UTRAN access technology
    and enter the EMM-NULL state.

    ��ʵ����⿴�����������������£���Ҫdisable LTE��
    (1)��ǰ���뼼��ΪLW,LG,LWG
    (2)PS��������ע���SIM��
    (3)CS����Ч��CS����ע�� */

    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* LTE��ģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* PSû�н���Detach */
    if (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }


    /* CS������ע���CS����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    pstDetachReqCtx = NAS_MMC_GetDetachReqCtxAddr();

    if (VOS_FALSE == NAS_MMC_IsDetachReqestDisableLte(pstDetachReqCtx->enDetachType,
                                                      pstDetachReqCtx->enDetachReason))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_DetachPs
 ��������  : Detach PS��ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 3.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    VOS_UINT8                                               ucCsAttachAllowFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM������,USIM��SIM��*/

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)CS����Ч��CS��������ע�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    ucCsAttachAllowFlg     = NAS_MML_GetCsAttachAllowFlg();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* CS����Ч��CS��������ע�ᣬ��ҪEnable Lte */
    if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
     || (VOS_FALSE == ucCsAttachAllowFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_AttachPs
 ��������  : Attach PS��ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��9��4��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�DTS2012090600196,֧��GL,פ��G,syscfg����G only,
                ��detach ps��disable lte��syscfg���ú�attach ps���жϵ�ǰ��֧��Lδenable lte��
                ����syscfg����GL,Ҳδenable lte������gmm�յ�ms radio capability��Ϣδ����rau
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
 4.��    ��   : 2012��12��15��
   ��    ��   : l65478
   �޸�����   : DTS2012120508936:�ڷ����������ʱ��Ҫdisable LTE
 5.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 6.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)PS����Ч
    (3)USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_AttachCs
 ��������  : Attach CS��ɺ��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��SIM��ʱ����ҪDisable Lte;
 4.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 5.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCs(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)SYSCFG���õ�ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч��PS������ע���SIM��
    (3)CS����Ч��ģʽΪCS+PS */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE��ģ������disable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS����Ч */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* PS����Ч������PS����attach */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }


    if (NAS_MML_MS_MODE_PS_CS != NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_DetachCs
 ��������  : Detach CS��ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM����ҪEnable Lte;SIM��ʱ����Ҫ
 4.��    ��   : 2012��12��15��
   ��    ��   : l65478
   �޸�����   : DTS2012120508936:�ڷ����������ʱ��Ҫdisable LTE
 5.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 6.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)֧��LTE
    (3) USIM */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }


    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* CSû�н���Detach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_AttachCsPs
 ��������  : Attach CSPS��ɺ��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��SIM��ʱ����ҪDisable Lte;
 3.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 5.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCsPs(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)SYSCFG���õ�ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч��SIM��
    (3)CS����Ч */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType              = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE��ģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS����Ч */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_AttachCsPs
 ��������  : attach CSPS��ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
 4.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 5.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachCsPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)PS����Ч */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_DetachCsPs
 ��������  : Detach CSPS��ɺ��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachCsPs(VOS_VOID)
{
    /* �ó�������ҪDisable lte, ����Ԥ��������չʹ�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_DetachCsPs
 ��������  : Detach CSPS��ɺ��ж��Ƿ���Ҫenable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��12��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 4.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCsPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM������,USIM��SIM��*/

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)֧��LTE */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* CSû�н���Detach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLteRoam
 ��������  : �ж��Ƿ���Ҫdisable LTE����
 �������  : ulMcc:��ǰPLMN ID�Ĺ�����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE����
             VOS_FALSE:����Ҫdisable LTE����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 3.��    ��   : 2015��3��9��
   ��    ��   : wx270776
   �޸�����   : DTS2015021601238:MCC��Чʱ�򣬲���ҪDISABLE LTE
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLteRoam(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    VOS_UINT32                          ulPlatformSuppLteFlg;

    ulPlatformSuppLteFlg = NAS_MML_IsPlatformSupportLte();


    /* MCC��Чʱ�򣬲���ҪDISABLE LTE */
    if ( VOS_FALSE == NAS_MML_IsMccValid(ulMcc) )
    {
        return VOS_FALSE;
    }

    /* ��ֹLTE��������ʱ */
    if ((VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
     && (VOS_TRUE == ulPlatformSuppLteFlg))
    {
        /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* ��ǰפ��PLMN IDΪ������������ */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLteRoam
 ��������  : �ж��Ƿ���Ҫenable LTE����
 �������  : ulMcc:��ǰPLMN ID�Ĺ�����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE����
             VOS_FALSE:����Ҫenable LTE����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 3.��    ��   : 2015��3��9��
   ��    ��   : wx270776
   �޸�����   : DTS2015021601238:MCC��Чʱ�򣬲���ҪDISABLE LTE
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLteRoam(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          ulDisableLte;
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    /* ��ȡ�Ƿ���Ҫdisable LTE���α�� */
    ulDisableLte  = NAS_MML_GetDisableLteRoamFlg();


    /* MCC��Чʱ�򣬲���ҪDISABLE LTE */
    if ( VOS_FALSE == NAS_MML_IsMccValid(ulMcc) )
    {
        return VOS_FALSE;
    }

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ��ֹLTE��������ʱ */
    if (VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
    {
        /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* ��ǰפ��PLMN IDΪ�������粢���Ѿ�disable LTE */
        if ((VOS_TRUE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
         && (VOS_TRUE == ulDisableLte))
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_ImsSwitchOn
 ��������  : �ж�IMS���ܴ�ʱ���Ƿ���ҪEnable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫenable LTE
             VOS_FALSE:����Ҫenable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_ImsSwitchOnOrNotCsOnly(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM������,USIM��SIM��*/

    /* ����������������MMC��Ҫ����enable LTE��
    (1)NVû�����ý�ֹLTEģ
    (2)�Ѿ�Disable LTE
    (3)USIM��,����SIM��L��ģ
    (4)PS����Ч,������ע��
    (5)Disable LTE��ԭ��ֵΪLTE��voice unavailable
    (6)UE֧��IMS
    (7)voice domain��Ϊcs only

    ����ط���DS�ĵ���ͬ����Ϊ��ʱ�޷�֪��֮ǰ��LTE����ע��ɹ����µ�Disable LTE
    ����������ʧ��5�ε��µ�Disable LTE
    ����LTE������ע��������ʧ�ܵ����������ط�Ҳ��Enable LTE�����������LTE����Ȼʧ�ܣ���Disable LTE */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* UE��֧��ims */
    if (VOS_FALSE == NAS_MML_IsUeSupportIms())
    {
        return VOS_FALSE;
    }

    /* voice domainΪcs only */
    if (NAS_MML_CS_VOICE_ONLY == NAS_MML_GetVoiceDomainPreference())
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* PS��������ע�� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    /* Disable LTE��ԭ��ֵΪLTE������������ */
    if (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE == NAS_MML_GetDisableLteReason())
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCampLteNormalService
 ��������  : �ж��Ƿ��Ѿ�פ����L�����ṩ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE: �����Ѿ�פ����L�����ṩ��������
              VOS_TRUE: �Ѿ�פ����L�����ṩ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��06��02��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampLteNormalService(VOS_VOID)
{
    /* ��ǰ���뼼������LTE */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* ��ǰNASΪδפ��״̬ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_FALSE;
    }

    /* ��ǰ���ڷ���������״̬ */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsReCampLteLimitedService
 ��������  : LTE��Ҫdisableʱ���ж��Ƿ���Ȼפ����LTE��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ȼפ����LTE��������
             VOS_FALES:disable Lte
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsReCampLteLimitedService( VOS_VOID )
{
    /* ��ǰ���뼼������LTE */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* ��ǰNASΪδפ��״̬ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_FALSE;
    }

    /* ����ǿ���Ч���µ���Ҫdisable lte����,����Ҫ��LTE�� */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* �����PS��detach���µ���Ҫdisable lte����,����Ҫ��LTE�� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode
 ��������  : �жϵ�ǰ������lte PLMN�Ƿ���������
 �������  : pstPlmnId: plmnIdֵ
 �������  : ��
 �� �� ֵ  : vos_ture:��ǰplmn��������
             vos_false:��ǰplmn����������

 �޸���ʷ      :
  1.��    ��   : 2015��9��11��
    ��    ��   : y00346957
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(NAS_MML_PLMN_ID_STRU *pstPlmnId)
{
    NAS_MMC_CL_ASSOCIATED_INFO_NTF_STRU                    *psCLAssociatedInfo;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPlmnPriClass;
    VOS_UINT32                                              ulIs1xSupported;
    VOS_UINT32                                              ulIsCurrLtePlmnAllowSrch;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enEqPlmnPriClass;
    VOS_UINT32                                              ulIsEqPlmnAllowSrch;
    NAS_MML_PLMN_ID_STRU                                    stEqPlmnId;

    ulIsCurrLtePlmnAllowSrch = VOS_TRUE;
    psCLAssociatedInfo       = NAS_MMC_GetCLAssociatedInfoAddr();

    /* �Ƿ�֧��1x */
    ulIs1xSupported          = NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_CDMA1X, NAS_MML_GetMs3Gpp2PrioRatList());

    /* 1x��֧�֣�lte��priclassû���޶� */
    if (VOS_FALSE == ulIs1xSupported)
    {
        return VOS_TRUE;
    }

    /* lte������,����false */
    if (VOS_FALSE == psCLAssociatedInfo->ucAllowSrchLteFlg)
    {
        return VOS_FALSE;
    }

    /* ��ǰ������פ����lte��priclass */
    enPlmnPriClass = NAS_MMC_GetPlmnPrioClass(pstPlmnId);

    /* �жϵ�ǰ������פ����lte��priclass�Ƿ���ڵ���Ҫ�����͵ȼ���priclass */
    ulIsCurrLtePlmnAllowSrch = NAS_MMC_ComParePlmnPrioClass(enPlmnPriClass, psCLAssociatedInfo->enLteSysPriClass);

    if (VOS_TRUE == ulIsCurrLtePlmnAllowSrch)
    {
        return ulIsCurrLtePlmnAllowSrch;
    }

    /* �ڵ�ǰplmn����������(פ��)ʱ�������Чplmn�б�������������(פ��)��plmn����ǰplmn��������(פ��) */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();

    if ((VOS_FALSE == pstEquPlmnInfo->ucValidFlg) || (0 == pstEquPlmnInfo->ucEquPlmnNum))
    {
        return ulIsCurrLtePlmnAllowSrch;
    }

    /* �����Чplmn�б��е�1��plmn���ǵ�ǰ��plmn��mmc����ĵ�Чplmn�б��뵱ǰplmn���ǻ�Ϊ��Чplmn */
    if ((pstPlmnId->ulMcc != pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc)
     || (pstPlmnId->ulMnc != pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc))
    {
        return ulIsCurrLtePlmnAllowSrch;
    }

    /* ���eplmn���з���������plmn����ǰplmnҲ�������� */
    for (ucIndex = 1; ucIndex < pstEquPlmnInfo->ucEquPlmnNum; ucIndex++)
    {
        stEqPlmnId.ulMcc = pstEquPlmnInfo->astEquPlmnAddr[ucIndex].ulMcc;
        stEqPlmnId.ulMnc = pstEquPlmnInfo->astEquPlmnAddr[ucIndex].ulMnc;

        enEqPlmnPriClass = NAS_MMC_GetPlmnPrioClass(&stEqPlmnId);

        ulIsEqPlmnAllowSrch = NAS_MMC_ComParePlmnPrioClass(enEqPlmnPriClass, psCLAssociatedInfo->enLteSysPriClass);

        if (VOS_TRUE == ulIsEqPlmnAllowSrch)
        {
            ulIsCurrLtePlmnAllowSrch = VOS_TRUE;

            break;
        }
    }

    return ulIsCurrLtePlmnAllowSrch;
}
#endif
#endif

/* NAS_MMC_GetMmlCsTransactionStatu�����Ƶ�NAS MML LIB ��*/

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortPlmnSearchListSpecRatPrioLowest
 ��������  : �������б�������򣬽�ָ�����뼼�����зŵ��б����
 �������  : pstPlmnSelectionListInfo
 �������  : pstPlmnSelectionListInfo
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��2��16��
   ��    ��   : h00202780
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��17��
   ��    ��   : z00161729
   �޸�����   : DTS2012081604223:csfbʧ����Ҫ������gu��gu������ʧ�ܻ�lte��û����rplmn�����ѵ�eplmn����Ϊrplmn״̬����Ϊbutt
 3.��    ��   : 2013��8��26��
   ��    ��   : w00242748
   �޸�����   : DTS2013071808373����澯����

 4.��    ��   : 2014��11��13��
   ��    ��   : w00167002
   �޸�����   : DTS2014111201728:CSFB����ʱ�򣬵�ǰ����AVAILABLE���磬����û������GU��
                PLMN������������L��PLMN�����»ص�L,
*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enSpecRatType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* �б��б����PLMN���� */
    VOS_UINT16                          usSearchPlmnNum;
    usSearchPlmnNum  = pstPlmnSelectionListInfo->usSearchPlmnNum;

    for( i = 0; i < usSearchPlmnNum; i++ )
    {
        for ( j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++ )
        {
            /* ����ǰPLMN�б����������˳� */
            if ( NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST <= pstPlmnSelectionListInfo->usSearchPlmnNum )
            {
                return;
            }

            if ( enSpecRatType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType )
            {

                /* ����һ�ݵ�ǰ�����������Ϣ�����е������б�ĺ��� */
                PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum]),
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                           sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

                /* �����һ������Ľ��뼼����������Ϊ1�����ҽ��뼼������Ϊ�û���Ҫ���õĽ��뼼�� */
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].ucRatNum = 1;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enRatType = enSpecRatType;

                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enNetStatus
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enQuality
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].lRscp
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].ucReserve
                    = 0;

                /* ѡ�������б��е��������������1�� */
                pstPlmnSelectionListInfo->usSearchPlmnNum++;

                /* ����ǰ����������Ҫ�ƶ��Ľ��뼼������Ϊ��Чֵ������ǰ����Ľ��뼼���������һ����
                       ����Ҫ������Ľ��뼼���Ƶ�ǰ��ȥ */
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
                if ( (NAS_MML_MAX_RAT_NUM - 1) > j  )
                {
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1] ),
                            (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    /*lint +e961*/
                }

                /* ��ǰ��������Ľ��뼼������һ�� */
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;


                /* �ҵ���ָ�����뼼�������磬���˳�����ѭ����������һ������ */
                break;

            }
        }
    }

    /* ������н��뼼������Ϊ0������ */
    for ( i = 0; i < usSearchPlmnNum;  )
    {
        /* ����ǰ���������Ľ��뼼������Ϊ0������ɾ����PLMN���� */
        if( 0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum )
        {
            if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
            {
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1] ),
                        (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                /*lint +e961*/
            }

            /* ѡ�������б��е��������������1�� */
            pstPlmnSelectionListInfo->usSearchPlmnNum--;

            /* ��Ҫ�жϴ�����뼼��Ϊ0�������������һ�� */
            usSearchPlmnNum--;
            continue;
        }

        i++;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsRejectedBySpecCause
 ��������  : �ж�UE���ο����Ƿ�ָ����ԭ��ֵ�ܾ���
 �������  : enDomain:ָ����
             enCause:ָ����ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ܾ���
             VOS_FALSE:δ���ܾ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��09��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRejectedBySpecCause(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    for (i = 0; i < pstPlmnRegRejInfo->ucPlmnRegInfoNum; i++)
    {
        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            if ((enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus)
#if (FEATURE_ON == FEATURE_LTE)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus)
#endif
             )
            {
                return VOS_TRUE;
            }
        }

        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            if ((enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus)
#if (FEATURE_ON == FEATURE_LTE)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus)
#endif
             )
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}


/* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAisRoamingEffect
 ��������  : �ж�AIS�������ι����Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:����Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��17��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsAisRoamingEffect( VOS_VOID )
{
    /******************************************************************
    1.���ĵ�ֻʵ���Զ�ģʽ��������TOT�����硣
    2��ֻҪ���ض��򿪣���ֻ���AIS SIM��������TOT���硣
    3��������ֻ�ڿ����ͱ����ѹ����������á�
    4�������ѹ��̱�SYSCFG���û��б��ѡ����Ʒ������û���ѡ�Ȼ����������ĳ�����ϣ���������������ʵʱ����TOT����Ĵ���״̬����Ҫ�ȵ��´α����ѲŻ���TOT��
    *******************************************************************/
    NAS_MML_AIS_ROAMING_CFG_STRU        *pstAisRoamingCfg;


    pstAisRoamingCfg        = NAS_MML_GetAisRoamingCfg();

    /* NVIM�й��ܲ���Чʱ,ֱ�ӷ��ع��ܲ���Ч */
    if ( VOS_FALSE == pstAisRoamingCfg->ucEnableFlg )
    {
        return VOS_FALSE;
    }

    /* ��ǰ��AIS��SIM�� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn((NAS_MML_PLMN_ID_STRU*)&(pstAisRoamingCfg->stSimHPlmnId)))
    {
        return VOS_TRUE;
    }

    /* �����������VOS_FALSE */
    return VOS_FALSE;
}
/* Modified by z40661 for ̩��AIS���� 2012-05-17, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail
 ��������  : ע��ʧ��ԭ��ֵΪ11 12 13 15��ʱ������û��ֶ�ָ�������ע��״̬��־
                PSע��ɹ�, CSע��ʧ��, ԭ��Ϊ11 12 13 15�����, ��Ҫ����ñ�־.
                ��Ϊ��ʱCS��RPLMNû�и���Ϊ�û�ָ����PLMN, �˺����ȴ���������������
                RPLMN����EPLMN, ����Ҫ����ñ�־.
                CSע��ɹ�, PSע��ʧ��ʱ, ��ȻRPLMN���û�ָ��PLMN��ͬ, ��Ϊ�˴���Գ�,
                Ҳ�������־�Ĵ���.

 �������  : enRegFailCause: ע��ʧ�ܵ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��04��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  2.��    ��   : 2012��11��09��
    ��    ��   : l65478
    �޸�����   : DTS2012103005174, ��#12,#15ʱ����Ҫ���ע��״̬��־
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause
)
{
    /* �Զ�ģʽ�²���Ҫ���¸�ȫ�ֱ��� */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if ( (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW  == enRegFailCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW  == enRegFailCause))
    {
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_FALSE);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUserSpecPlmnRegisterStatus
 ��������  : ���ֶ�����ģʽ��,ע��ɹ�ʱ,��Ҫ�����û�ָ��������״̬

 �������  : enCsCause: CSע��ʧ�ܵ�ԭ��ֵ
             enCsCause: PSע��ʧ�ܵ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��18��
    ��    ��   : l65478
    �޸�����   : �����ɺ���, DTS2012081703289
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatus(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    /* �Զ�ģʽ�²���Ҫ���¸�ȫ�ֱ��� */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NULL == enCause)
    {
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);
    }
    else
    {
        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enCause);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct
 ��������  : stPlmnId,              ��Ҫ����HPLMN
              usRatForOneEhplmnItem, ����EHPLM��Ӧ��RAT
              ulPlmnNum,             �Ѿ����µ�EHPLMN�ĸ���
 �������  : pstPlmnWithRatInfo     ���º��EHPLMN
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��9��
    ��    ��   : w00166186
    �޸�����   : AT&T & DCM��Ŀ
  2.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(
    NAS_MML_PLMN_ID_STRU                stPlmnId,
    VOS_UINT16                         *pusRatForOneEhplmnItem,
    VOS_UINT32                         *pulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRatInfo
)
{
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU        *pstHplmnWithRatList= VOS_NULL_PTR;
    VOS_UINT32                                   i;
    VOS_UINT32                                   ulEqual;
    VOS_UINT16                                   usRatInUsim;
    VOS_UINT16                                   usUeSptRat;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstHplmnWithRatList = NAS_MML_GetSimHplmnWithRatList();
    ulEqual             = VOS_FALSE;

    /* ��ȡSIM����Ϣ */
    for (i = 0; i < pstHplmnWithRatList->ucHPlmnWithRatNum; i++)
    {
        ulEqual = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstHplmnWithRatList->astHPlmnWithRatInfo[i].stPlmnId),
                                                     &stPlmnId);
        if (VOS_TRUE == ulEqual )
        {
            usRatInUsim = pstHplmnWithRatList->astHPlmnWithRatInfo[i].usSimRat;

            if (NAS_MML_SIM_NO_RAT == ( usRatInUsim & (NAS_MML_SIM_ALL_RAT_SUPPORT_LTE)))
            {
                usRatInUsim = usUeSptRat;
            }
            else
            {
                usRatInUsim &= usUeSptRat;
            }

            if (NAS_MML_SIM_NO_RAT != ((~*pusRatForOneEhplmnItem) & usRatInUsim))
            {
                /*����Sim���д��ڵ�ʣ��Ľ��뼼������ʱȫ�ֱ�������*/
                pstPlmnWithRatInfo[*pulPlmnNum].usSimRat = ((~*pusRatForOneEhplmnItem) & usRatInUsim);

                pstPlmnWithRatInfo[*pulPlmnNum].stPlmnId.ulMcc = stPlmnId.ulMcc;

                pstPlmnWithRatInfo[*pulPlmnNum].stPlmnId.ulMnc = stPlmnId.ulMnc;

                (*pulPlmnNum)++;

                (*pusRatForOneEhplmnItem) |= usRatInUsim;
            }

            if ((*pulPlmnNum >= NAS_MML_MAX_EHPLMN_NUM)
             || (usUeSptRat == (*pusRatForOneEhplmnItem & usUeSptRat)))
            {
                /*  ��ǰPlmn�����������������������н��뼼������ӣ� �˳��������� */
                break;
            }
        }
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct
 ��������  : ���ݶ��Ƶ�HPLMN��������Sim���е�HplmnACt�ļ�����EHPLMN�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��9��
    ��    ��   : l00130025
    �޸�����   : DTS2012060400029:��Ӷ�HPLMNAct���Ƚ��뼼���Ķ��ƣ�ĿǰUSim����HPLMNACT�ܶ಻֧��L
  2.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct(VOS_VOID)
{
    NAS_MML_PRIO_HPLMNACT_CFG_STRU              *pstNvPrioHPlmnActCfg;
    NAS_MML_SIM_EHPLMN_INFO_STRU                *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU              *pstTmpPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                   k;
    VOS_UINT32                                   i;
    VOS_UINT32                                   ulPlmnNum;
    VOS_UINT16                                   usRatForOneEhplmnItem;
    VOS_UINT16                                   usRatNeedToAdd;
    VOS_UINT16                                   usUeSptRat;

    pstNvPrioHPlmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    /* ��ȡSIM����EHPLMN��Ϣ*/
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

    ulPlmnNum = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstTmpPlmnInfo  = (NAS_MML_SIM_PLMN_WITH_RAT_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, NAS_MML_MAX_EHPLMN_NUM * sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));

    if ( VOS_NULL_PTR == pstTmpPlmnInfo )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateEhplmnRat: Alloc Mem Failed ");
        return;
    }

    NAS_MML_InitSimPlmnInfo(NAS_MML_MAX_EHPLMN_NUM, pstTmpPlmnInfo);

    /*����NVֵ��EHPLMN�Ľ��뼼������*/
    for ( k = 0; k < pstEHPlmnInfo->ucEhPlmnNum; k++ )
    {
        usRatForOneEhplmnItem = 0;

        /* ��NV�����õ�HPLMNAct��Ϊ������ȼ���ֱ����� */
        if (ulPlmnNum < NAS_MML_MAX_EHPLMN_NUM)
        {
            pstTmpPlmnInfo[ulPlmnNum].usSimRat = pstNvPrioHPlmnActCfg->usPrioHplmnAct;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;

            usRatForOneEhplmnItem = pstNvPrioHPlmnActCfg->usPrioHplmnAct;

        }

        /* EHPLMN������Ѵﵽ���������˳� */
        if(ulPlmnNum >= NAS_MML_MAX_EHPLMN_NUM)
        {
            break;
        }

        /* ���н��뼼������ӣ� �˳��������� */
        if (usUeSptRat == (usRatForOneEhplmnItem & usUeSptRat))
        {
            continue;
        }

        /* ��ȡSIM����Ϣ */
        NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId,
                                                  &usRatForOneEhplmnItem,
                                                  &ulPlmnNum,
                                                  pstTmpPlmnInfo);

        /* ȷ��ʣ��� Ҫ��ӵ�RAT */
        usRatNeedToAdd = ( (~usRatForOneEhplmnItem) & usUeSptRat);

        if ((NAS_MML_SIM_NO_RAT != usRatNeedToAdd)
         && (ulPlmnNum  < NAS_MML_MAX_EHPLMN_NUM))
        {
             /* ��NV�кͿ��е�HplmnAct�����ж�Ӧ��RAT,��Ҫ������н��뼼��;
                ������Ӳ��� RAT,���ʣ���RAT
             */
            pstTmpPlmnInfo[ulPlmnNum].usSimRat       = usRatNeedToAdd;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;
        }

    }

    /* ����Hplmn�ĸ�����Rat�б� */
    pstEHPlmnInfo->ucEhPlmnNum = (VOS_UINT8)ulPlmnNum;
    for (i = 0; i < ulPlmnNum; i++)
    {
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc = pstTmpPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc = pstTmpPlmnInfo[i].stPlmnId.ulMnc;
        pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat       = pstTmpPlmnInfo[i].usSimRat;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnInfo);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct
 ��������  : ����SIM����HplmnAct��ԭʼ��Ϣ������EHPLMN�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��2��28��
    ��    ��   : z00161729
    �޸�����   : DTS2011021602201:��������hplmn�Ľ��뼼��û�и�ֵ�����ֵ,��Ӱ�칦��ֻӰ���ά�ɲ���Ϣ��ʾ
  3.��    ��   : 2011��4��13��
    ��    ��   : l00130025
    �޸�����   : �޸Ķ�GUL 3ģ�Ĵ���
  4.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  5.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : ����ע��BBIT����

  6.��    ��   : 2012��1��11��
    ��    ��   : w00167002
    �޸�����   : DTS2012011208030:�������Է������⣬��L��ע�ᱻ��#13����L��
                  ����HOME PLMN.(D03_DTS2011102200381_Combined_Registeration_FAIL_SCENE_13)
  7.��    ��   : 2012��6��9��
    ��    ��   : l00130025
    �޸�����   : DTS2012060400029:��Ӷ�HPLMNAct���Ƚ��뼼���Ķ��ƣ�
                 ����������;6F62�д���HplmnΪ0x0000�ļ�¼ʱ��HPLMN������ʱ���ᱻ���
  8.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct(VOS_VOID)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU                         *pstTmpPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              k;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT16                                              usRatForOneEhplmnItem;
    VOS_UINT16                                              usRatNeedToAdd;
    VOS_UINT16                                              usUeSptRat;

    /* ��ȡSIM����EHPLMN��Ϣ*/
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    /* HPLMNĬ���� ���ģʽ��֧�ֵ�,HPLMNWithRat�еĽ���ģʽ����
    ��Ҫ���µ�ǰPLMN�Ľ������ȼ�,�����ǰHPLMNWithRat֧������ģʽ,
    �򲻽����޸�,�����ǰHPLMNWithRat֧�ֵ�ģ��2��ģʽ,����Ҫ����HplmnWithACt,ȷ�����µĽ��뼼�����ȼ�ָʾ,
    ֧�� ��ģʽ ����ǰ��,����ģʽ�ķ��ں���;
    ��HplmnWithActָʾ: W -> L ��������Ҫ��3�� Hplmn: W->L->G ;����ָʾ W,�����ΪW->LG
    */
    ulPlmnNum = 0;

    pstTmpPlmnInfo  = (NAS_MML_SIM_PLMN_WITH_RAT_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, NAS_MML_MAX_EHPLMN_NUM * sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));
    if ( VOS_NULL_PTR == pstTmpPlmnInfo )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateEhplmnRat: Alloc Mem Failed ");
        return;
    }

    NAS_MML_InitSimPlmnInfo(NAS_MML_MAX_EHPLMN_NUM, pstTmpPlmnInfo);

    for ( k = 0; k < pstEHPlmnInfo->ucEhPlmnNum; k++ )
    {
        usRatForOneEhplmnItem = 0;

        /* ��SIM���ļ�0x6F62�л�ȡ��ӦPLMN��RAT */

        NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId,
                                                  &usRatForOneEhplmnItem,
                                                  &ulPlmnNum,
                                                  pstTmpPlmnInfo);

        /* ȷ��ʣ��� Ҫ��ӵ�RAT */
        usRatNeedToAdd = ( (~usRatForOneEhplmnItem) & usUeSptRat);

        if ((NAS_MML_SIM_NO_RAT != usRatNeedToAdd)
         && (ulPlmnNum  < NAS_MML_MAX_EHPLMN_NUM))
        {
             /* ����û���ҵ���Ӧ��RAT,��Ҫ������н��뼼��;
                ������Ӳ��� RAT,���ʣ���RAT
             */
            pstTmpPlmnInfo[ulPlmnNum].usSimRat       = usRatNeedToAdd;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;
        }

    }

    /* ����Hplmn�ĸ�����Rat�б� */
    pstEHPlmnInfo->ucEhPlmnNum = (VOS_UINT8)ulPlmnNum;
    for (i =0;i< ulPlmnNum;i++)
    {
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc = pstTmpPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc = pstTmpPlmnInfo[i].stPlmnId.ulMnc;
        pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat       = pstTmpPlmnInfo[i].usSimRat;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEhplmnRat
 ��������  : ����EHPLMN�Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��2��28��
    ��    ��   : z00161729
    �޸�����   : DTS2011021602201:��������hplmn�Ľ��뼼��û�и�ֵ�����ֵ,��Ӱ�칦��ֻӰ���ά�ɲ���Ϣ��ʾ
  3.��    ��   : 2011��4��13��
    ��    ��   : l00130025
    �޸�����   : �޸Ķ�GUL 3ģ�Ĵ���
  4.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  5.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : ����ע��BBIT����

  6.��    ��   : 2012��1��11��
    ��    ��   : w00167002
    �޸�����   : DTS2012011208030:�������Է������⣬��L��ע�ᱻ��#13����L��
                  ����HOME PLMN.(D03_DTS2011102200381_Combined_Registeration_FAIL_SCENE_13)
  7.��    ��   : 2012��6��9��
    ��    ��   : l00130025
    �޸�����   : DTS2012060400029:��Ӷ�HPLMNAct���Ƚ��뼼���Ķ��ƣ�ĿǰUSim����HPLMNACT�ܶ಻֧��L
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateEhplmnRat(VOS_VOID)
{

    NAS_MML_PRIO_HPLMNACT_CFG_STRU     *pstPrioHPlmnActCfg;

    pstPrioHPlmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    if ((VOS_TRUE == pstPrioHPlmnActCfg->ucActiveFlg)
     && (NAS_MML_SIM_NO_RAT != pstPrioHPlmnActCfg->usPrioHplmnAct))
    {
        /*����NV���Ƶ�HPLMN��������Sim���е�HPLMNACt����HPLMN�Ľ��뼼��*/
        NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct();
    }
    else
    {
        /* ����ԭʼ��SIM���е�HPLMN������򲹳�EHPLMN�Ľ��뼼��*/
        NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct();
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateHomePlmn
 ��������  : ��IMSIת���Э��ջ��ʹ�õ���ʽ�洢����
              ��IMSI�н�����HOME PLMN���µ�ȫ�ֱ�����
 �������  : aucIMSI:�洢IMSI������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui / l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������,�õ���λMNC
  4.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : V7R1C50_GUTL_PhaseII:ɾ����46002/46007�й��ƶ���������⴦��,
                  ��46002��46007ת��Ϊ46000�����緽ȷ��MP��̨֧��46002��46007�Ĵ���
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateHomePlmn(
    VOS_UINT8                           *pucIMSI
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;

    /* Added by t00212959 for DCM�����������������, 2012-8-22, begin */
    VOS_UINT8                           ucUsimMncLenth;
    VOS_UINT8                           ucExactlyComparaFlag;

    ucUsimMncLenth       = NAS_MML_GetUsimMncLen();
    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();
    /* Added by t00212959 for DCM�����������������, 2012-8-22, end */

    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();

    pstEHPlmnInfo->ucEhPlmnNum = 1;

    PS_MEM_SET(&pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[1] & NAS_MML_OCTET_HIGH_FOUR_BITS) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[2] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_EIGHT_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[2] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_TWELVE_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[3] & NAS_MML_OCTET_LOW_FOUR_BITS);
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[3] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_FOUR_BITS;

    /* Modified by t00212959 for DCM�����������������, 2012-8-15, begin */
    if ((NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucUsimMncLenth)
     && (VOS_TRUE == ucExactlyComparaFlag))
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (NAS_MML_LOW_BYTE_INVALID) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    else
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[4] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    /* Modified by t00212959 for DCM�����������������, 2012-8-15, end */

    /* ����PLMN ID��ͬ�ıȽϣ�ĩλΪ0����F��������Ѿ����µıȽϺ�����
      ����:NAS_MMC_CompareBcchPlmnwithSimPlmn����Ҫ�������PLMN ID������
      ���ƶ��������⴦����Ҫ����,���2λMNC��HPLMN��Hplmn�б���,
      �ƶ�MCC=460,MNC=02��07�й��ƶ������⴦��
    */
    if (( 0x000604 == pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc )
     && ( (0x200   == (pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc & 0xFFFF ) )
       || (0x700   == (pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc & 0xFFFF))))
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc &= 0xFF0000;
    }
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_DelLowPrioEHPlmn
 ��������  : ��list�����н�����EHPLMN��������ȼ���PLMN,ɾ�������EHPLMN
 �������  : pstReportList:�ϱ���list�����б�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��23��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_DelLowPrioEHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU           *pstEHPlmnList;
    VOS_UINT32                              i,j;
    VOS_UINT8                               ucHighPrioPlmn;
    VOS_UINT16                              usSearchPlmnNum;
    NAS_MML_PLMN_ID_STRU                    stHighPrioPlmnId;

    pstEHPlmnList   = NAS_MML_GetSimEhplmnList();
    ucHighPrioPlmn  = VOS_TRUE;
    usSearchPlmnNum = pstReportList->usSearchPlmnNum;

    stHighPrioPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stHighPrioPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    for ( i = 0 ; i < pstEHPlmnList->ucEhPlmnNum ; i++ )
    {
        for ( j = 0 ; j < pstReportList->usSearchPlmnNum ; j++ )
        {
            /* ���ҵ���ǰ���ȼ���ߵ�EHPLMN��list�д��� */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstReportList->astPlmnSelectionList[j].stPlmnId,
                                                               &pstEHPlmnList->astEhPlmnInfo[i].stPlmnId))
            {
                /* ������������ȼ���EHPLMN */
                if ( VOS_TRUE == ucHighPrioPlmn )
                {
                    ucHighPrioPlmn         = VOS_FALSE;
                    stHighPrioPlmnId.ulMcc = pstEHPlmnList->astEhPlmnInfo[i].stPlmnId.ulMcc;
                    stHighPrioPlmnId.ulMnc = pstEHPlmnList->astEhPlmnInfo[i].stPlmnId.ulMnc;
                    continue;
                }

                if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stHighPrioPlmnId,
                                                               &pstEHPlmnList->astEhPlmnInfo[i].stPlmnId))
                {
                    /* ɾ��������PLMN */
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstReportList->astPlmnSelectionList[j]),
                                &(pstReportList->astPlmnSelectionList[j + 1]),
                                ((pstReportList->usSearchPlmnNum- j - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));
                    /*lint +e961*/
                    usSearchPlmnNum--;
                }
            }
        }
    }

    pstReportList->usSearchPlmnNum = usSearchPlmnNum;
}




#if (FEATURE_ON == FEATURE_LTE)

/* Added by t00212959 for DCM�����������������, 2012-8-14, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGuSysInfoIndSetLteRoamAbility
 ��������  : �յ�GU������ϵͳ��Ϣ�󣬽���disable L ���� enable L
 �������  : ulSysInfoMcc        - GU�ϱ���ϵͳ��Ϣ�����ϵĹ�����
             enLCapabilityStatus - ���ڵ�LTE����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  3.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  4.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteRoamAbility(
    VOS_UINT32                                              ulSysInfoMcc,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{    /* �Ƿ���Ҫ��ֹLTE���� */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(ulSysInfoMcc))
    {
        /* �Ѿ�֪ͨdisable LTE����Ҫ��֪ͨ�� */
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);

                /* ��¼disable lteʱפ����������Ϣ */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);

        if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        }
        return;
    }

    /* �Ƿ���Ҫ����LTE���� */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLteRoam(ulSysInfoMcc))
    {
        /* ��ǰLTE�����ָ����û���ΪĬ��ֵ */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
    return;

}
/* Added by t00212959 for DCM�����������������, 2012-8-14, end */
#endif
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsInterNationalRoamingSearchRPLMN
 ��������  : �жϹ�������ʱ�Ƿ���RPLMN
 �������  : ulMcc:��ǰPLMN ID�Ĺ�����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����ʱҪ��
             VOS_FALSE:����δ���������ڹ��ڲ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��24��
   ��    ��   : t00173447
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsInterNationalRoamingSearchRPLMN(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          *aulComparedMcc ;

    aulComparedMcc = NAS_MML_GetNationalMCCList();

    if( VOS_TRUE == NAS_MML_GetRoamRplmnSearchFlg() )
    {
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_MAX_NATIONAL_MCC_NUM, aulComparedMcc))
        {
           return VOS_FALSE;
        }
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MCC_IsNeedDisableLteWBand
 ��������  : ����Ƶ�ν���LTE
 �������  : ulBandƵ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE����
             VOS_FALSE:����Ҫdisable LTE����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��24��
   ��    ��   : t00173447
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MCC_IsNeedDisableLteWBand(
    VOS_UINT32                         ulBand
)
{
    /*��Ҫ��NV���� */
    if (VOS_TRUE == NAS_MML_GetDisableLTEOnBandFlg())
    {
        /* ��ǰפ��Ƶ��ΪBAND9 */
        if (NAS_MMC_WCDMA_BAND_IX == ulBand)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGuSysInfoIndSetLteAbility
 ��������  : �յ�GU������ϵͳ��Ϣ�󣬽���disable L ���� enable L
 �������  : SysInfo        - GU�ϱ���ϵͳ��Ϣ
             enLCapabilityStatus - ���ڵ�LTE����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��18��
    ��    ��   : t00173447
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  3.��    ��   : 2015��3��9��
    ��    ��   : wx270776
    �޸�����   : 3gϵͳ��Ϣ����ʱ��was�Ƿ��mmc�����ж�
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteAbility(
    struct MsgCB                       *pstMsg,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{
    MSG_HEADER_STRU                    *MsgHeader      = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysinfo  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGasSysInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulSysInfoMcc;
    VOS_UINT32                          ulBand;
    VOS_UINT32                          ucDisableLTEOnBandFlg;

    ulSysInfoMcc            = NAS_MML_INVALID_MCC;
    ulBand                  = 0;
    ucDisableLTEOnBandFlg   = VOS_FALSE;

    MsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if( RRMM_SYS_INFO_IND == MsgHeader->ulMsgName )
    {
        /*3g��ϵͳ��Ϣ����,��ȡMCC��BAND��Ϣ*/
        pstWrrSysinfo = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

        if (VOS_TRUE == pstWrrSysinfo->bitOpPlmnId)
        {
            ulSysInfoMcc = pstWrrSysinfo->PlmnId.ulMcc;
        }
        ulBand = pstWrrSysinfo->unWcdmaBand.ulBand;
    }
    else if( GRRMM_SYS_INFO_IND == MsgHeader->ulMsgName)
    {
        /*2g��ϵͳ��Ϣ����,��ȡMCC��BAND��Ϣ*/
        pstGasSysInfo = (GRRMM_SYS_INFO_IND_ST*)pstMsg;
        ulSysInfoMcc = pstGasSysInfo->PlmnId.ulMcc;
        ulBand = pstGasSysInfo->unGsmBand.ulBand;
    }
    else
    {
        return;
    }

    ucDisableLTEOnBandFlg = NAS_MCC_IsNeedDisableLteWBand(ulBand);

    /* �Ƿ���Ҫ��ֹLTE���� */
    if ( (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(ulSysInfoMcc))
      || (VOS_TRUE == ucDisableLTEOnBandFlg) )
    {
        /* �Ѿ�֪ͨdisable LTE����Ҫ��֪ͨ�� */
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        return;
    }

    /* �Ƿ���Ҫ����LTE���� */
    if ( (VOS_TRUE  == NAS_MMC_IsNeedEnableLteRoam(ulSysInfoMcc))
      && (VOS_FALSE == ucDisableLTEOnBandFlg) )
    {
        /* ��ǰLTE�����ָ����û���ΪĬ��ֵ */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
    return;

}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelHplmnInFplmn
 ��������  : ɾ��FPLMN��HPLMN
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��02��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2012��8��24��
    ��    ��   : w00167002
    �޸�����   : ����ԭ����NAS_MMC_DelHplmnInFplmn_SwitchOn�ĺ������֣�������
                  �������ļ�λ�ã��������ݹ��ܲ��漰�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_DelHplmnInFplmn(VOS_VOID)
{
    VOS_INT8                            i;
    VOS_UINT8                           ucForbPlmnNum;
    VOS_UINT32                          ulHplmnInFplmnFlg;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;

    pstForbidPlmnInfo           = NAS_MML_GetForbidPlmnInfo();

    ucForbPlmnNum               = pstForbidPlmnInfo->ucForbPlmnNum;
    ulHplmnInFplmnFlg           = VOS_FALSE;

    for (i = 0; i < ucForbPlmnNum; i++)
    {
        /* ���hplmn��fplmn�б�����ɾ��fplmnȫ�ֱ����еļ�¼,�����޷�����hplmn��ע�� */
        if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&(pstForbidPlmnInfo->astForbPlmnIdList[i]))))
        {
            if ( i < (ucForbPlmnNum - 1) )
            {
                (VOS_VOID)PS_MEM_MOVE(&pstForbidPlmnInfo->astForbPlmnIdList[i],
                            &pstForbidPlmnInfo->astForbPlmnIdList[i+1],
                            ((ucForbPlmnNum - i) - 1) * sizeof(NAS_MML_PLMN_ID_STRU ) );
            }
            ucForbPlmnNum--;
            i--;
            ulHplmnInFplmnFlg = VOS_TRUE;
        }
    }

    pstForbidPlmnInfo->ucForbPlmnNum = ucForbPlmnNum;

    if (VOS_TRUE == ulHplmnInFplmnFlg)
    {
        /* ���HPLMN������FPLMN����Ϊ���ļ����Ϸ�,��FPLMN��ɾ��HPLMN��¼ */
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertPlmnIdListToGUFormat
 ��������  : ��L��ʽ��PLMN ID�б�ת����GU��ʽ��PLMN ID�б�
 �������  : pstSrcPlmnIdList  ��Ҫת����PLMN ID�б�
 �������  : pstDestPlmnIdList ת�����PLMN ID�б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��28��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����: Lģ�ӿڸı�
  3.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : �޸ĺ�����
*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmPlmnIdListToGUFormat(
    MMC_LMM_PLMN_ID_LIST_STRU          *pstSrcPlmnIdList,
    RRC_PLMN_ID_LIST_STRU              *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_PLMN_ID_STRU                stPlmn;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat;

    ulRrcRat = RRC_NAS_RAT_TYPE_BUTT;

    /* ��ת�������������б� */
    if (pstSrcPlmnIdList->ulLowPlmnNum > RRC_MAX_LOW_PLMN_NUM)
    {
        pstSrcPlmnIdList->ulLowPlmnNum = RRC_MAX_LOW_PLMN_NUM;
    }

    pstDestPlmnIdList->ulLowPlmnNum = pstSrcPlmnIdList->ulLowPlmnNum;

    for ( i = 0; i < pstSrcPlmnIdList->ulLowPlmnNum; i++)
    {
        /* ��L��ʽ��PLMN �б�ת����GU��ʽ��*/
        for ( j = 0; j < MMC_LMM_PLMN_ID_LEN; j++)
        {
            stLmmPlmn.aucPlmnId[j] = pstSrcPlmnIdList->astLowPlmnWithRatList[i].stPlmnIdWithRat.aucPlmnId[j];
        }
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                            &stPlmn);
        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc = stPlmn.ulMcc;

        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc = stPlmn.ulMnc;

        NAS_MMC_ConvertLmmRatToRrcFormat(pstSrcPlmnIdList->astLowPlmnWithRatList[i].stPlmnIdWithRat.enPlmnRat, &ulRrcRat);

        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.ulRat = ulRrcRat;

        pstDestPlmnIdList->aLowPlmnList[i].lRscp =
                                pstSrcPlmnIdList->astLowPlmnWithRatList[i].lRscp;
    }

    /* ת�������������б� */
    if (pstSrcPlmnIdList->ulHighPlmnNum > RRC_MAX_HIGH_PLMN_NUM)
    {
        pstSrcPlmnIdList->ulHighPlmnNum = RRC_MAX_HIGH_PLMN_NUM;
    }

    pstDestPlmnIdList->ulHighPlmnNum = pstSrcPlmnIdList->ulHighPlmnNum;

    for ( i=0; i < pstSrcPlmnIdList->ulHighPlmnNum; i++)
    {
        /* ��L��ʽ��PLMN �б�ת����GU��ʽ��*/
        for ( j = 0; j < MMC_LMM_PLMN_ID_LEN; j++)
        {
            stLmmPlmn.aucPlmnId[j] = pstSrcPlmnIdList->astHighPlmnWithRatList[i].aucPlmnId[j];
        }

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                            &stPlmn);

        pstDestPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc = stPlmn.ulMcc;

        pstDestPlmnIdList->aHighPlmnList[i].stPlmnId.ulMnc = stPlmn.ulMnc;

        NAS_MMC_ConvertLmmRatToRrcFormat(pstSrcPlmnIdList->astHighPlmnWithRatList[i].enPlmnRat, &ulRrcRat);

        pstDestPlmnIdList->aHighPlmnList[i].ulRat = ulRrcRat;

    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPsRelConnEnableLteTimerExpired
 ��������  : �ж�enable lte��ʱ����ʱ�Ƿ���Ҫ�����ͷ�ps����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ�ͷ�����
             VOS_TRUE: ��Ҫ�ͷ�����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��20��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedRelPsConnEnableLteTimerExpired(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus  = VOS_NULL_PTR;
    NAS_MML_GMM_PROC_INFO_STRU         *pstGmmProcInfo = VOS_NULL_PTR;

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus    = NAS_MML_GetConnStatus();
    pstGmmProcInfo   = NAS_MML_GetGmmProcInfo();

    /* ������rrc���ӣ�����false����Ҫ�����ͷ����� */
    if (VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        return VOS_FALSE;
    }

    /* �������csҵ�񣬷���false����Ҫ�����ͷ����� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        return VOS_FALSE;
    }

    /* �������cs��������lau���̣�����false����Ҫ�����ͷ����� */
    if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
    {
        return VOS_FALSE;
    }

    /* ���gmm��ע�����̣�����false������Ҫ�����ͷ����� */
    if ((NAS_MML_GMM_PROC_TYPE_INVALID != pstGmmProcInfo->enGmmProcType)
     && (NAS_MML_GMM_PROC_FLAG_START == pstGmmProcInfo->enGmmProcFlag))
    {
        return VOS_FALSE;
    }

    /* sm�ڽ���pdp���ȥ���modify���̣�����false������Ҫ�����ͷ����� */
    if (NAS_MML_SM_PROC_FLAG_START == NAS_MML_GetSmProcFlag())
    {
        return VOS_FALSE;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn
 ��������  : �ж��Ƿ���Ҫ�ͷ�EPS����
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ�ͷ�EPS����
              VOS_TRUE: ��Ҫ�ͷ�EPS����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��22��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��4��
   ��    ��   : t00212959
   �޸�����   : DTS2012120302949 EPS only #16,#17,#22��5���ֻ����ͷ�����
 3.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
 4.��    ��   : 2014��5��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014051308442:L��ע��ɹ�֧��IMS����SMS ONLY��������TAU��16��һ�Σ�ֱ��disable
                LTE��
 5.��    ��   : 2015��4��20��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
 6.��    ��   : 2015��6��19��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn(VOS_VOID)
{
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;
    VOS_UINT32                                              ulCsDomainUnAvailFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    VOS_UINT32                                              ulAttempCounter;

    /* Attempt Counter ��ʼ��Ϊ0 */
    ulAttempCounter = 0;

    enPsRegCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause = NAS_MML_REG_FAIL_CAUSE_NULL;

    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();
    ulCsDomainUnAvailFlg = VOS_FALSE;
    enDisableLteReason   = NAS_MML_GetDisableLteReason();

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, begin */
    /* disable LTE������ԭ����IMS VOICE��������Ҫ֪ͨL�ͷ�����*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  != NAS_MML_GetLteCapabilityStatus())
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE != enDisableLteReason))
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, end */
    {
        return VOS_FALSE;
    }


    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_NET_RAT_TYPE_LTE,
                                             &enCsRegCause,
                                             &enPsRegCause );

    /* ��ȡL�µĳ��Դ���*/
    ulAttempCounter = NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType());

    /* EPS only �ɹ���#16,#17,#22��Ҫdisable lteʱ�����ͷ�����*/
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause)
     && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulAttempCounter))
    {
        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT��EPS ONLY�ɹ�������ԭ��ֵΪ16,17��CS/PS1��DIABLE LTE����������
          persistent EPS bearer�Ƿ���ڣ���Ӧ24301 5.5.3.3.4.3�½�:
              #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          ��CR��Э��汾���� */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /*�Ƿ���#18�б���*/
    ulCsDomainUnAvailFlg = NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId());

    /* ��#18�б��У�SMS ONLY ,CSFB NOT PREFERRED��Ҫ֪ͨL�ͷ�����*/
    if ((VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
     || (VOS_TRUE == ulCsDomainUnAvailFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnMccSameWithRplmn
 ��������  : �ж�MCC�Ƿ��ں�rplmn��mcc��ͬ
 �������  : ulMcc - ��Ҫ�жϵ�MCC
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : MCC��rplmn��mcc��ͬ
             VOS_FALSE : MCC��rplmn��mcc��ͬ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��10��30��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnMccSameWithRplmn(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          i;

    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));
    i = 0;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* ��ȡRPLMN������Ϣ */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    /* ������֧�ֽ��뼼����rplmn��mcc�Ƚ�,��Ϊ��rplmn���Կ���ʱ��gul��rplmn���ܻ᲻ͬ,
       �����rplmn���Թرգ���ֻ����ǰ���뼼��rplmn mcc�Ƚϣ���Ϊ��ʹ�ǵ�rplmn������Ҳ����gu��rplmn��lte�²�ͬ�ĳ���*/
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
        {
            /* rplmn�����ڷ���false*/
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, stRPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ��rplmn���Կ��� */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstPrioRatList->aucRatPrio[i], &stRPlmnId))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, stRPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnMccSameWithHplmn
 ��������  : �ж�MCC�Ƿ��ں�hplmn��mcc��ͬ
 �������  : ulMcc - ��Ҫ�жϵ�MCC
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : MCC��hplmn��mcc��ͬ
             VOS_FALSE : MCC��hplmn��mcc��ͬ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��10��30��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnMccSameWithHplmn(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* ��ȡEHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i < pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc,
                             pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnSameWithRplmn
 ��������  : �ж�PLMN�Ƿ���RPLMN
 �������  : ���жϵ�PLMN
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : ��ͬ��VOS_FALSE : ��ͬ
 ���ú���  :
 ��������  :
 �޸���ʷ     :
 1.��    ��   : 2015��10��21��
   ��    ��   : s00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnSameWithRplmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          i;

    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* ��ȡRPLMN������Ϣ */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    /* ������֧�ֽ��뼼����rplmn��mcc�Ƚ�,��Ϊ��rplmn���Կ���ʱ��gul��rplmn���ܻ᲻ͬ,
       �����rplmn���Թرգ���ֻ����ǰ���뼼��rplmn mcc�Ƚϣ���Ϊ��ʹ�ǵ�rplmn������Ҳ����gu��rplmn��lte�²�ͬ�ĳ���*/
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
        {
            /* rplmn�����ڷ���false*/
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &stRPlmnId))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ��rplmn���Կ��� */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstPrioRatList->aucRatPrio[i], &stRPlmnId))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &stRPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsgIdIndexInDestCsgIdList
 ��������  : ��ȡcsd id��ָ��csg id�б��е�����
 �������  : ulCsgId        - ָ��csg id
             ucDestCsgIdNum - CSG ID����
             pstCsgIdlist   - CSG ID�б�
 �������  : ��
 �� �� ֵ  : ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��15��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCsgIdIndexInDestCsgIdList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnWithCsgId,
    VOS_UINT32                          ulDestCsgIdNum,
    NAS_MML_PLMN_WITH_CSG_ID_INFO_STRU *pstDestCsgIdlist
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;

    ulIndex = NAS_MML_MIN(NAS_MML_MAX_PLMN_CSG_ID_NUM, ulDestCsgIdNum);

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnWithCsgId->stPlmnId), &(pstDestCsgIdlist[i].stPlmnWithCsgId.stPlmnId)))
         && (pstPlmnWithCsgId->ulCsgId == pstDestCsgIdlist[i].stPlmnWithCsgId.ulCsgId))
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList
 ��������  : �ж�CSG ID�Ƿ���Ŀ��CSG List��
 �������  : pstPlmnWithCsgId - ָ��csg id
             ulPlmnWithCsgIdListNum   - csg id�б����
             pstPlmnWithCsgIdList     - CSG ID�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : ��Ŀ��CSG List��
             VOS_FALSE : ����Ŀ��CSG List��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��15��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnWithCsgId,
    VOS_UINT32                          ulPlmnWithCsgIdListNum,
    NAS_MML_PLMN_WITH_CSG_ID_INFO_STRU *pstPlmnWithCsgIdList
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < NAS_MML_MIN(NAS_MML_MAX_PLMN_CSG_ID_NUM, ulPlmnWithCsgIdListNum); ulIndex++)
    {
        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstPlmnWithCsgId->stPlmnId, &(pstPlmnWithCsgIdList[ulIndex].stPlmnWithCsgId.stPlmnId)))
          && (pstPlmnWithCsgId->ulCsgId == pstPlmnWithCsgIdList[ulIndex].stPlmnWithCsgId.ulCsgId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnCsgIdInForbidCsgList
 ��������  : �ж�CSG ID�Ƿ���Forbbiden LIST��
 �������  : pstPlmnCsgId - ָ��CSG ID��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : �ڣ�VOS_FALSE : ����
 ���ú���  :
 ��������  :
 �޸���ʷ     :
 1.��    ��   : 2015��10��21��
   ��    ��   : s00193151
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnCsgIdInForbiddenCsgList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    VOS_UINT32                                              i;
    NAS_MML_CSG_ID_WITH_FORBIDDEN_PERIOD_LIST_STRU         *pstForbiddenList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;

    stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstForbiddenList = NAS_MML_GetForbiddenCsgList();

    for (i = 0; i < NAS_MML_MIN(pstForbiddenList->ulForbiddenCsgIdNum, NAS_MML_MAX_FORBIDDEN_CSG_ID_NUM); i++)
    {
        stPlmnId.ulMcc = pstForbiddenList->astForbiddenCsgIdPeriodInfo[i].stPlmnWithCsgIdInfo.stPlmnId.ulMcc;
        stPlmnId.ulMnc = pstForbiddenList->astForbiddenCsgIdPeriodInfo[i].stPlmnWithCsgIdInfo.stPlmnId.ulMnc;

        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstPlmnCsgId->stPlmnId, &stPlmnId))
         && (pstPlmnCsgId->ulCsgId == pstForbiddenList->astForbiddenCsgIdPeriodInfo[i].stPlmnWithCsgIdInfo.ulCsgId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList
 ��������  : �ж�PLMN�Ƿ��ڵ����������б���
 �������  : pstBcchPlmnId  - plmn��Ϣ
             ulPlmnNum      - �����������б����
             pstLowPlmnList - �����������б���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ���ڣ�VOS_FALSE- ������
 ���ú���  :
 ��������  :
 �޸���ʷ     :
 1.��    ��   : 2015��10��21��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsBcchPlmnInInDestLowPlmnInfoList(
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT32                          ulPlmnNum,
    NAS_MMC_LOW_PLMN_INFO_STRU         *pstLowPlmnList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulPlmnNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            &(pstLowPlmnList[i].stPlmnId)) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMccListInRrcPlmnIdList
 ��������  : ��GU RRC��PLMN ID�б��л�ȡMCC�б�
 �������  : pstRrcPlmnIdList:Ŀ��PLMN ID�б�
 �������  : *pulMccNum:MCC�б����
             pulMccList:MCC�б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012-08-14
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_GetMccListInRrcPlmnIdList(
    VOS_UINT32                         *pulMccNum,
    VOS_UINT32                         *pulMccList,
    RRC_PLMN_ID_LIST_STRU              *pstRrcPlmnIdList
)
{
    VOS_UINT32                          i;

    *pulMccNum = 0;

    if (pstRrcPlmnIdList->ulHighPlmnNum > RRC_MAX_HIGH_PLMN_NUM)
    {
        pstRrcPlmnIdList->ulHighPlmnNum = RRC_MAX_HIGH_PLMN_NUM;
    }

    /* �������������� */
    for (i = 0; i < pstRrcPlmnIdList->ulHighPlmnNum; i++)
    {
        /*lint -e961*/
        pulMccList[(*pulMccNum)++]= pstRrcPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc;
        /*lint +e961*/
    }

    if (pstRrcPlmnIdList->ulLowPlmnNum > RRC_MAX_LOW_PLMN_NUM)
    {
        pstRrcPlmnIdList->ulLowPlmnNum = RRC_MAX_LOW_PLMN_NUM;
    }

    /* �������������� */
    for (i = 0; i < pstRrcPlmnIdList->ulLowPlmnNum; i++)
    {
        /*lint -e961*/
        pulMccList[(*pulMccNum)++] = pstRrcPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;
        /*lint +e961*/

    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelPlmnSelectionRatInfoInPlmnWithRatList
 ��������  : ���б��в���ָ����PLMN�Ľ��뼼�������ҵ�����ɾ��ָ����PLMN�Ľ��뼼��
 �������  :
             NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn,
             VOS_UINT8                              ucPlmnNum,
             NAS_MML_PLMN_WITH_RAT_STRU            *pstPlmnIdList
 �������  : pstPlmn
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��30��
    ��    ��   : w00167002
    �޸�����   : �����߼����������ǰ���������뼼������һ������ֹ�Ļ���
                 �ڶ������뼼��δ����ֹ���ᵼ�´���
*****************************************************************************/
VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInPlmnWithRatList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;

    /* ���б��в���ָ����PLMN�Ľ��뼼�� */
    for (i = 0; i < ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnIdList[i].stPlmnId),
                                                            &(pstPlmn->stPlmnId)))
        {
            j = 0;

            while ( j < (pstPlmn->ucRatNum) )
            {
                if (pstPlmnIdList[i].enRat == pstPlmn->astPlmnRatInfo[j].enRatType)
                {
                    if (j < (pstPlmn->ucRatNum - 1))
                    {

                        /*lint -e961*/
                        (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                    &(pstPlmn->astPlmnRatInfo[j + 1]),
                                    (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                        /*lint +e961*/
                    }

                    (pstPlmn->ucRatNum)--;

                    continue;
                }

                j++;
            }
        }
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndEnableLteNotify
 ��������  : enable lte��֪ͨ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_SndEnableLteNotify(VOS_VOID)
{
    /* ��WAS/GAS����enable LTE֪ͨ��Ϣ */
    NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE);
    NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE);

    /* ��LMM����enable LTE��Ϣ */
    NAS_MMC_SndLmmEnableLteNotify();
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndDisableLteNotify
 ��������  : disable lte��֪ͨ�����
 �������  : enDisableLteReason - disable lteԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_SndDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    /* ��WAS/GAS����disable LTE֪ͨ��Ϣ */
    NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);
    NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);

    /* ��LMM����disable LTE��Ϣ */
    NAS_MMC_SndLmmDisableLteNotify(enDisableLteReason);
    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList
 ��������  : ���б��в���ָ����PLMN�Ľ��뼼�������ҵ�����ɾ��ָ����PLMN�Ľ��뼼��
 �������  : VOS_UINT8                                          ucPlmnNum,
             NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU   *pstPlmnIdList
 �������  : pstPlmn
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  2.��    ��   : 2015��4��29��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;
    VOS_UINT32                          ulIndex;

    ulIndex = ulPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    /* ���б��в���ָ����PLMN�Ľ��뼼�� */
    for (i = 0; i < ulIndex; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnIdList[i].stPlmnWithRat.stPlmnId),
                                                            &(pstPlmn->stPlmnId)))
        {
            j = 0;

            while ( j < (pstPlmn->ucRatNum) )
            {
                if (pstPlmnIdList[i].stPlmnWithRat.enRat == pstPlmn->astPlmnRatInfo[j].enRatType)
                {
                    if (j < (pstPlmn->ucRatNum - 1))
                    {

                        /*lint -e961*/
                        (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                    &(pstPlmn->astPlmnRatInfo[j + 1]),
                                    (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                        /*lint +e961*/
                    }

                    (pstPlmn->ucRatNum)--;

                    continue;
                }

                j++;
            }
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo
 ��������  : �ж�SIM���Ƿ��ڽ�ֹ�б��У�ɾ����Ӧ�Ľ�ֹRAT
 �������  :
             NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn,
 �������  : pstPlmn
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��1��3��
    ��    ��   : s00261364
    �޸�����   : gmmģ��Converity�澯����

*****************************************************************************/
VOS_VOID  NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;

    i               = 0;
    j               = 0;
    pstRatBlackList = NAS_MML_GetRatForbiddenListCfg();

    /* ���IMSI���ں������У��򷵻� */
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return;
    }

    /* ���IMSI�ں������У���Ҫ�������б��н�NV�����ý�ֹ��RAT��ɾ�� */
    for (i = 0; i < pstRatBlackList->ucForbidRatNum; i++)
    {
        j = 0;
        while ( j < NAS_MML_MIN((pstPlmn->ucRatNum),NAS_MML_MAX_RAT_NUM) )
        {
            if (pstRatBlackList->aenForbidRatList[i] == pstPlmn->astPlmnRatInfo[j].enRatType)
            {
                if ( (j + 1) < (pstPlmn->ucRatNum) )
                {
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                &(pstPlmn->astPlmnRatInfo[j + 1]),
                                (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    /*lint +e961*/
                }

                (pstPlmn->ucRatNum)--;

                continue;
            }

            j++;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MML_IsPlmnIdWithRatInDestPlmnWithRatList
 ��������  : �жϴ����뼼����PLMN ID�Ƿ��ڴ����뼼����PLMN ID�б���
 �������  : pstSrcPlmnId:��Ҫ�жϵ�PLMN ID
             ulDestPlmnNum:�б���plmn id�ĸ���
             pstDestPlmnIdList:plmn�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID���б���
             VOS_FALSE : PLMN ID�����б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��08��20��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_AddPlmnListIntoSimEhplmnInfo(
    VOS_UINT32                          ulPlmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucTempSimEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astTempEhplmnList[NAS_MML_MAX_EHPLMN_NUM];

    /* ��SIM�е�EHplmn������ʱ��EHplmn LIST���棬���ں�����бȽϵ�ǰ�����Ƿ���EHPLMN LIST ���� */
    for ( i = 0 ; i < pstEhplmnInfo->ucEhPlmnNum; i++ )
    {
        astTempEhplmnList[i] = pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId;
    }
    ucTempSimEhplmnListNum = pstEhplmnInfo->ucEhPlmnNum;

    for ( i = 0 ; i < ulPlmnListNum; i++ )
    {
        /* �����ǰ��SIM Ehplmn LIST�������������������� */
        if ( NAS_MML_MAX_EHPLMN_NUM <= pstEhplmnInfo->ucEhPlmnNum )
        {
            return;
        }

        /* �����ǰ��������SIM Ehplmn LIST���棬����� */
        if ( VOS_TRUE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList( &pstPlmnList[i],
                                                                 enSpecPlmnType,
                                                                 ucTempSimEhplmnListNum,
                                                                 astTempEhplmnList) )
        {
            continue;
        }

        /* ��PLMN ID���뵽SIM Ehplmn LIST���� */
        pstEhplmnInfo->astEhPlmnInfo[pstEhplmnInfo->ucEhPlmnNum].stPlmnId = pstPlmnList[i];
        pstEhplmnInfo->ucEhPlmnNum++;

        /* ��PLMN ID���뵽��ʱ��SIM Ehplmn LIST���� */
        astTempEhplmnList[ucTempSimEhplmnListNum] = pstPlmnList[i];
        ucTempSimEhplmnListNum++;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCurrentWcdmaMode
 ��������  : �жϵ�ǰ��ģ�Ƿ�ΪWCDMA
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰ��ģΪW
             VOS_FALSE:��ǰ��ģ��ΪW
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��06��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCurrentWcdmaMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType       = NAS_MML_GetCurrNetRatType();

    if ((NAS_UTRANCTRL_UTRAN_MODE_FDD   == NAS_UTRANCTRL_GetCurrUtranMode())
     && (NAS_MML_NET_RAT_TYPE_WCDMA     == enRatType))
    {
        return VOS_TRUE;
    }

    /* �����������VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCurrentTdscdmaMode
 ��������  : �жϵ�ǰ��ģ�Ƿ�ΪTDSCDMA
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰ��ģΪTD
             VOS_FALSE:��ǰ��ģ��ΪTD
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCurrentTdscdmaMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType       = NAS_MML_GetCurrNetRatType();

    if ((NAS_UTRANCTRL_UTRAN_MODE_TDD   == NAS_UTRANCTRL_GetCurrUtranMode())
     && (NAS_MML_NET_RAT_TYPE_WCDMA     == enRatType))
    {
        return VOS_TRUE;
    }

    /* �����������VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNetRatSupportedTdscdma
 ��������  : �жϵ�ǰ���뼼���Ƿ�֧��TDSCDMA
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:֧��
             VOS_FALSE:��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��18��
   ��    ��   : z40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNetRatSupportedTdscdma(VOS_VOID)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode  = NAS_UTRANCTRL_GetCurrUtranMode();

    if ((VOS_TRUE                     == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_WCDMA))
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsEpsEmergencyAttachType
 ��������  : ����attach����е�ulReqType��ȡ�Ƿ�Ϊ����ע���ʶ
 �������  : ulReqType - l����attach������
 �������  : VOS_TRUE  - attach����Ϊ����ע��
             VOS_FALSE - attach���Ͳ�Ϊ����ע��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��17��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsEpsEmergencyAttachType(
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32     ulReqType
)
{
    if (MMC_LMM_ATT_TYPE_EPS_EMERGENCY == ulReqType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_DelForbInfo_LmmAttRsltSucc
 ��������  : L��ע��ɹ�ʱ��ɾ����Ӧ��Forbidden��Ϣ
 �������  : pstLmmLai                - lai��Ϣ
             ulEpsEmergencyAttachFlag - ע�������Ƿ�Ϊ����attach��VOS_TRUE:�ǽ���ע��;VOS_FALSE:�ǽ���ע��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��14��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_DelForbInfo_LmmAttRsltSucc(
    MMC_LMM_LAI_STRU                   *pstLmmLai,
    VOS_UINT32                          ulEpsEmergencyAttachFlag
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmn         = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                    stForbLai;

    /* ���ڻ�ȡ��ֹLA����Ϣ */
    pstForbPlmnInfo     = NAS_MML_GetForbidPlmnInfo();
    pstPlmn             = NAS_MML_GetCurrCampPlmnId();
    PS_MEM_SET(&stForbLai, 0, sizeof(NAS_MML_LAI_STRU));

    /* 24301_CR1189R2_(Rel-11)_C1-113741
       1.If the attach procedure is not for emergency bearer services,
         and if the PLMN identity of the registered PLMN is a member of the list
         of "forbidden PLMNs" or the list of "forbidden PLMNs for GPRS service",
         any such PLMN identity shall be deleted from the corresponding list(s).
       2.If there is no established PDN connection for emergency bearer services
         and if the PLMN identity of the registered PLMN is a member of the list
         of "forbidden PLMNs" or the list of "forbidden PLMNs for GPRS service",
         any such PLMN identity shall be deleted from the corresponding list(s).
       ��CR����Э��汾���� */
    /* �����ڽ���PDN���ӣ��Ҳ���Ϊ�������ص�attach,ע��ɹ�ֱ��ɾ����ֹPLMN��Ϣ,����Ҫ�ж��Ƿ�Ϊָ������,���֮ǰPS���CS��ע��
       �ӵ���ֹ�б�,ֻ����ָ������ʱ�Żᷢ��CS/PS��ע��,ע��ɹ������ֱ��ɾ����ֹ��Ϣ */
    if ((VOS_FALSE == NAS_MML_GetEmcPdpStatusFlg())
     && (VOS_FALSE == ulEpsEmergencyAttachFlag))
    {
        if (VOS_TRUE ==  NAS_MML_DelForbPlmn(pstPlmn))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }

        NAS_MML_DelForbGprsPlmn(pstPlmn);
    }

    /* pstLmmLaiΪ��Чֵʱ������Ҫɾ��ForbLai */
    if (VOS_NULL_PTR == pstLmmLai)
    {
        return;
    }

    /* ��LMM��LAת����NAS��LA */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmLai->stPlmnId), &(stForbLai.stPlmnId));
    stForbLai.aucLac[0]   = pstLmmLai->stLac.ucLac;
    stForbLai.aucLac[1]   = pstLmmLai->stLac.ucLacCnt;

    /* ���뼼��ΪLʱ��LAI��ATTACH_IND��Ϣ�д���LAI�������õ�ǰפ����LAI */
    (VOS_VOID)NAS_MML_DelForbLa(&stForbLai, NAS_MML_REG_DOMAIN_CS);

    /* ��ֹForbidden LA Ϊ�գ���ֹͣ Forbidden LA TImer */
    if ( ( 0 == pstForbPlmnInfo->ucForbRegLaNum )
      && ( 0 == pstForbPlmnInfo->ucForbRoamLaNum ) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_FORBID_LA_TIMER);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch
 ��������  : �յ�LMM��ATTACH CNFʱ���Ƿ���Ҫ��������
 �������  : pstLmmAttachCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���: L->LWG�󣬻���DETACH CS/PS��MMA���յ�SYSCFG CNFʱ��
                 ���·�ATTACH CS/PS��ATTACHʧ��ʱ��Ҫ��������.
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{
    if ( NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER) )
    {
        return VOS_FALSE;
    }

    /* ��ǰ�Ѿ�����������������Ҫ�������� */
    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼����֧��W/G������Ҫ���� */
    if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()) )
    {
        return VOS_FALSE;
    }

    switch ( pstLmmAttachCnf->ulAttachRslt)
    {
        /* ���Դ������� */
        case MMC_LMM_ATT_RSLT_FAILURE :
        case MMC_LMM_ATT_RSLT_FORBID_PLMN :
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS :
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING :
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS :

            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }

}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelForbInfo_AttRsltSucc
 ��������  : GU��ע��ɹ�ʱ��ɾ����Ӧ��Forbidden��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��06��03��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2014��5��4��
    ��    ��   : z00161729
    �޸�����   : DTS2014042816166:l csfb ��w��rau��12�ܾ���lau�ɹ�û�����forbidden��Ϣ������fast return��l��csfb��w��ͬС���绰ʧ��
  4.��    ��   : 2014��5��19��
    ��    ��   : w00242748
    �޸�����   : DTS2014051308442:L��ע��ɹ�֧��IMS����SMS ONLY��������TAU��16��һ�Σ�ֱ��disable
                 LTE��
*****************************************************************************/
VOS_VOID  NAS_MMC_DelForbInfo_GuRegRsltSucc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLai          = VOS_NULL_PTR;

    /* ���ڻ�ȡ��ֹLA����Ϣ */
    pstForbPlmnInfo     = NAS_MML_GetForbidPlmnInfo();
    pstLai              = NAS_MML_GetCurrCampLai();

    /* ע��ɹ�ֱ��ɾ����ֹPLMN��Ϣ,����Ҫ�ж��Ƿ�Ϊָ������,���֮ǰPS���CS��ע��
       �ӵ���ֹ�б�,ֻ����ָ������ʱ�Żᷢ��CS/PS��ע��,ע��ɹ������ֱ��ɾ����ֹ��Ϣ */
    if (VOS_TRUE ==  NAS_MML_DelForbPlmn(&(pstLai->stPlmnId)))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    if (NAS_MMC_REG_DOMAIN_CS != enDomain)
    {
        NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
    }

    /* ��ȡCS PS��ע��ԭ��ֵ */

    /* ���һ�����Ѿ���#12��13��#15�ܣ���һ����ע��ɹ���Ҫɾ��ForbLai */


    if (VOS_TRUE == NAS_MML_DelForbLa(pstLai, enDomain))
    {
        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    /* ��ֹForbidden LA Ϊ�գ���ֹͣ Forbidden LA TImer */
    if ( ( 0 == pstForbPlmnInfo->ucForbRegLaNum )
      && ( 0 == pstForbPlmnInfo->ucForbRoamLaNum ) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_FORBID_LA_TIMER);
    }
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLteInfo
 ��������  : ��ȡLTE��Ϣ�����ӿں���
 �������  : ulInfoType
 �������  : pstLmmInfo
 �� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
              VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��12��27��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
)
{
    /* ƽ̨��֧��LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����LNAS�ṩ�ӿں������ɹ�����VOS_OK */
    if (MMC_LMM_SUCC == Nas_GetLteInfo(ulInfoType, pstLmmInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ChangeCsRegState
 ��������  : ����CSע��״̬
 �������  : ucCsRegState:Ŀ��ע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��28��
   ��    ��   : w00281933
   �޸�����   : ����״̬��ʾ�Ż�PhaseI��
*****************************************************************************/
VOS_VOID  NAS_MMC_ChangeCsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucCsRegState
)
{
    NAS_MML_REG_STATUS_ENUM_UINT8       ucOldRegState;

    ucOldRegState = NAS_MML_GetCsRegStatus();

    /*normal ע��״̬�������ϱ�*/
    if ((ucCsRegState == ucOldRegState)
     && (NAS_MML_REG_REGISTERED_HOME_NETWORK != ucCsRegState)
     && (NAS_MML_REG_REGISTERED_ROAM != ucCsRegState))
    {
        return;
    }

    NAS_MMC_ErrLogRecordCsOosCause(ucOldRegState, ucCsRegState);
    NAS_MMC_ErrLogClrNwSearchCount(ucOldRegState, ucCsRegState);

    /* ����CSע��״̬ */
    NAS_MML_SetCsRegStatus(ucCsRegState);

    /* �ϱ�ע��״̬�����ı� */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, ucCsRegState);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ChangePsRegState
 ��������  : ����PSע��״̬
 �������  : ucPsRegState:Ŀ��ע��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

 2.��    ��   : 2014��11��28��
   ��    ��   : w00281933
   �޸�����   : ����״̬��ʾ�Ż�PhaseI��

 3.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
VOS_VOID  NAS_MMC_ChangePsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegState
)
{
    NAS_MML_REG_STATUS_ENUM_UINT8       ucOldRegState;

    ucOldRegState = NAS_MML_GetPsRegStatus();

    /*normal ע��״̬�������ϱ�*/
    if((ucPsRegState == ucOldRegState)
    && (NAS_MML_REG_REGISTERED_HOME_NETWORK != ucPsRegState)
    && (NAS_MML_REG_REGISTERED_ROAM != ucPsRegState))
    {
        return;
    }

    NAS_MMC_ErrLogRecordPsOosCause(ucOldRegState, ucPsRegState);
    NAS_MMC_ErrLogClrNwSearchCount(ucOldRegState, ucPsRegState);

    /*ѡ����Anycell����ʱ���ϱ�LTE��ע��״̬*/

    /* ����PSע��״̬ */
    NAS_MML_SetPsRegStatus(ucPsRegState);

    /* �ϱ�ע��״̬�����ı� */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, ucPsRegState);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRegStateSpecPlmnSearch
 ��������  : ѡ����AnyCell����ָ������ʱ����ע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateRegStateSpecPlmnSearch(VOS_VOID)
{
    /* ����޿�ע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ����CSFBҵ�񲻸���CSPSע��״̬ */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return;
    }
#endif

    /* ���CS����Ч����CSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ���CS������ע�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    /* ���PS����Ч����PSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ���PS������ע�����PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRegStateAnyCellSearchSucc
 ��������  : AnyCell�����ɹ�����CSPSע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��06��03��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateRegStateAnyCellSearchSucc(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulForbPlmnFlag;
    VOS_UINT8                                               ucUpdateRegStaFlg;
#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLteOnlyFlg;
#endif

    ucUpdateRegStaFlg = VOS_FALSE;

    /* ��ʱ����������,һ��Ҫ����ע��״̬ */
    if (NAS_MMC_TIMER_STATUS_STOP == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        ucUpdateRegStaFlg = VOS_TRUE;
    }
    else
    {
        enSelectionMode   = NAS_MMC_GetPlmnSelectionMode();
        pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
        ulForbPlmnFlag    = NAS_MML_IsPlmnIdInForbidPlmnList( &(pstUserSpecPlmnId->stPlmnId) );

        /* ��ǰΪ�ֶ�ģʽ���û�ָ���������ڽ�ֹ�����б�����Ҫ����ע��״̬ */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
         && (VOS_TRUE                           == ulForbPlmnFlag))
        {
            ucUpdateRegStaFlg = VOS_TRUE;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        ulLteOnlyFlg        = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());
        pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

        ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                  pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                                  pstForbidPlmnInfo->astForbGprsPlmnList);

        /* LTE ONLY�ֶ�ģʽ���û�ָ���������ڽ�ֹGPRS�б���,��Ҫ����ע��״̬ */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
         && (VOS_TRUE == ulLteOnlyFlg)
         && (VOS_TRUE == ulRet))
        {
            ucUpdateRegStaFlg = VOS_TRUE;
        }
#endif
    }

    if (VOS_FALSE == ucUpdateRegStaFlg)
    {
        return;
    }

    /* ����޿�ע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ����CSFBҵ�񲻸���CSPSע��״̬ */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return;
    }
#endif

    /* ���CS����Ч����CSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* ���PS����Ч����PSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ����PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateCsRegStateCsRegSucc
 ��������  : CSע��ɹ�ʱ����CSע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��2��
    ��    ��   : b00269685
    �޸�����   : ��EPLMN�а���HOME������ʾΪ������

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateCsRegStateCsRegSucc(VOS_VOID)
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    ucHplmnInEplmnDisplayHomeFlg = NAS_MML_GetHplmnInEplmnDisplayHomeFlg();
    ulIsHplmnInEplmnList         = NAS_MML_IsHplmnInEplmnList();

    if ((VOS_FALSE == NAS_MMC_IsRoam())
     || ((VOS_TRUE == ucHplmnInEplmnDisplayHomeFlg)
      && (VOS_TRUE == ulIsHplmnInEplmnList)))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_ROAM);
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePsRegStatePsRegSucc
 ��������  : PSע��ɹ�ʱ����PSע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��2��
    ��    ��   : b00269685
    �޸�����   : ��EPLMN��HOME�У�����ʾΪ������

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePsRegStatePsRegSucc(VOS_VOID)
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    ucHplmnInEplmnDisplayHomeFlg = NAS_MML_GetHplmnInEplmnDisplayHomeFlg();
    ulIsHplmnInEplmnList         = NAS_MML_IsHplmnInEplmnList();

    if ((VOS_FALSE == NAS_MMC_IsRoam())
     || ((VOS_TRUE == ucHplmnInEplmnDisplayHomeFlg)
      && (VOS_TRUE == ulIsHplmnInEplmnList)))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_ROAM);
    }

    return;
}

/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, begin */
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : NAS_MM_ConvertToLmmSrvccStatus
 ��������  : ��MSCC�ķ���״̬ת��ΪMMC�ĸ�ʽ
 �������  : penMmcServiceState--MMC�ķ���״̬
 �������  : enMsccServiceState---�ϱ�MSCC�ķ���״̬
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��8��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertToMsccSrvStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enMmcServiceState,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  *penMsccServiceState
)
{
    switch(enMmcServiceState)
    {
        case NAS_MMC_NO_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
            break;
        case NAS_MMC_NORMAL_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;
            break;
        case NAS_MMC_LIMITED_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
            break;
        case NAS_MMC_LIMITED_SERVICE_REGION:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION;
            break;
        default:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_BUTT;
            break;
    }

    return;
}
/*lint -restore */

/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ChangeServiceState
 ��������  : ���ķ���״̬
 �������  : enServiceState:Ŀ�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��04��03��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
  3.��    ��   : 2014��11��25��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�
  4.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_ChangeServiceState(
    VOS_UINT32                          ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
)
{

    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enMsccServiceState;



    /*ѡ����Anycell����ʱ���ϱ�LTE�ķ���״̬*/


    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    switch (ulCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            /* ��������ʱ������֪ͨMMA����״̬��MMA��Ҫ����������ʱ����stAppNetworkInfo
               ���������ǰ�Ѿ�����Ҫ���µ�ע��״̬����Ҫ������ */
            if ((enServiceState == pstServiceInfo->enCsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }
            /* ����CS����״̬ */
            NAS_MMC_SetCsServiceStatus(enServiceState);
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:

            /* ��������ʱ������֪ͨMMA����״̬��MMA��Ҫ����������ʱ����stAppNetworkInfo
               ���������ǰ�Ѿ�����Ҫ���µ�ע��״̬����Ҫ������ */
            if ((enServiceState == pstServiceInfo->enPsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }
            /* ����PS����״̬ */
            NAS_MMC_SetPsServiceStatus(enServiceState);
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

            /* ��������ʱ������֪ͨMMA����״̬��MMA��Ҫ����������ʱ����stAppNetworkInfo
               ���������ǰ�Ѿ�����Ҫ���µ�ע��״̬����Ҫ������ */
            if ((enServiceState == pstServiceInfo->enPsCurrService)
             && (enServiceState == pstServiceInfo->enCsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }

            /* ����CS����״̬ */
            NAS_MMC_SetCsServiceStatus(enServiceState);

            /* ����PS����״̬ */
            NAS_MMC_SetPsServiceStatus(enServiceState);
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_ChangeServiceState: domain Type Error");
            return;
    }

    NAS_MMC_ConvertToMsccSrvStatus(enServiceState, &enMsccServiceState);

    NAS_MMC_SndMsccServiceStatusInd(ulCnDomainId,  enMsccServiceState);

    return;
}
/*lint -restore */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegStateAndCsServiceStateWhenReceiveDetachCnfSucc
 ��������  : �յ�Detach Cnf Succ ��Ϣʱ��CS���ע��״̬�ͷ���״̬�Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��9��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo = VOS_NULL_PTR;

    ucSimCsRegStatus = VOS_FALSE;
    pstServiceInfo   = NAS_MMC_GetServiceInfo();

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_ProcCsRegStateAndCsServiceState_DetachCnfSucc:CsRegStatus, enCsCurrService", ucSimCsRegStatus, pstServiceInfo->enCsCurrService);

    /* ���CS����Ч���ϱ�csע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if (VOS_TRUE == ucSimCsRegStatus)
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* ���֮ǰ����������״̬���������Ϊ���Ʒ���״̬ */
    if (NAS_MMC_NORMAL_SERVICE == pstServiceInfo->enCsCurrService)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegStateAndPsServiceStateWhenReceiveDetachCnfSucc
 ��������  : �յ�Detach Cnf Succ ��Ϣʱ��PS���ע��״̬�ͷ���״̬�Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��9��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegStateAndPsServiceState_DetachCnfSucc(VOS_VOID)
{
    VOS_UINT8                           ucSimPsRegStatus;
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo = VOS_NULL_PTR;

    ucSimPsRegStatus = VOS_FALSE;
    pstServiceInfo   = NAS_MMC_GetServiceInfo();

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_ProcPsRegStateAndPsServiceState_DetachCnfSucc:PsRegStatus, enPsCurrService", ucSimPsRegStatus, pstServiceInfo->enPsCurrService);

    /* ���PS������ע�����PS����Ч���ϱ�psע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH*/
    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* ���֮ǰ����������״̬���������Ϊ���Ʒ���״̬ */
    if (NAS_MMC_NORMAL_SERVICE == pstServiceInfo->enPsCurrService)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }

    return;
}

/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLRegSuccRsltType
 ��������  : �жϵ�ǰLע��ɹ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_PIF_PS_REG_PROC_ENUM_UINT32:��ǰLע��ɹ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��6��
    ��    ��   : z00359541
    �޸�����   : ��������
*****************************************************************************/
NAS_MSCC_PIF_PS_REG_PROC_ENUM_UINT32 NAS_MMC_GetLRegSuccRsltType(VOS_VOID)
{
    NAS_MMC_REG_RSLT_CTX_STRU                              *pstRegRsltCtx = VOS_NULL_PTR;
    NAS_MSCC_PIF_PS_REG_PROC_ENUM_UINT32                     enRslt;

    enRslt          = NAS_MSCC_PIF_L_REG_PROC_BUTT;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-11, begin */
    /* �����̱�־��Чʱ��ֱ�ӷ��ؼ����̽�� */
    if (VOS_TRUE == NAS_MMC_GetLteUnrealRegProcFlg())
    {
        enRslt = NAS_MSCC_PIF_L_TAU_UNREAL_PROC;
        NAS_NORMAL_LOG1(WUEPS_PID_MMC,"NAS_MMC_GetLRegSuccRsltType: UnReal TAU proc", enRslt);
        return enRslt;
    }
    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-11, end */

    switch (pstRegRsltCtx->enRegRsltType)
    {
        case LMM_MMC_ATTACH_IND:
            if (VOS_TRUE == pstRegRsltCtx->unRegRsltCtx.pstLmmAttachIndMsg->bitOpCnRslt)
            {
                enRslt = NAS_MSCC_PIF_L_ATT_REAL_PROC;
            }
            break;

        case LMM_MMC_TAU_RESULT_IND:
            if (VOS_TRUE == pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg->bitOpCnRst)
            {
                enRslt = NAS_MSCC_PIF_L_TAU_REAL_PROC;
            }
            else
            {
                enRslt = NAS_MSCC_PIF_L_TAU_UNREAL_PROC;
            }
            break;

        default:
            enRslt = NAS_MSCC_PIF_L_REG_PROC_BUTT;
            break;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_MMC,"NAS_MMC_GetLRegSuccRsltType: enRslt", enRslt);
    return enRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsDomainValidForPsRegCnRsltInd
 ��������  : ��ǰ�����Ƿ���Ը�MSCC����PS REG RSLT IND��Ϣ
 �������  : ulCnDomainId:��ID
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ���� VOS_FALSE: ������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2016��4��5��
    ��    ��   : z00359541
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsDomainValidForPsRegCnRsltInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  ulCnDomainId
)
{
    VOS_UINT32                          ulDomainValidFlg;

    switch (ulCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            ulDomainValidFlg = VOS_TRUE;
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
            ulDomainValidFlg = VOS_TRUE;
            break;

        default:
            ulDomainValidFlg = VOS_FALSE;
            break;
    }

    return ulDomainValidFlg;
}
/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ChangeServiceState
 ��������  : ���ķ���״̬
 �������  : enServiceState:Ŀ�����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854:  ���α�ǲ�׼
  2.��    ��   : 2016��4��5��
    ��    ��   : z00359541
    �޸�����   : MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���:  ����������̵��жϣ��Ա�
                 MSCC��֪ͨIMSA SERVICE CHANGEʱ��IMSA��֪���˴��������̻��Ǽ�����
                 ������
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateServiceState_RegSucc(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32      ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8              enServiceState
)
{
    NAS_NORMAL_LOG2(WUEPS_PID_MMC,"NAS_MMC_UpdateServiceState_RegSucc entered ulCnDomainId, enServiceState", ulCnDomainId, enServiceState);

    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    if (VOS_TRUE == NAS_MMC_IsDomainValidForPsRegCnRsltInd(ulCnDomainId))
    /* �ڸ���ע�����״̬֮ǰ��֪ͨMSCC��ǰ�������̻��Ǽ����̴����ĸ���*/
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_UpdateServiceState_RegSucc: Send MSCC PS REG CN RSLT IND");
        NAS_MMC_SndMsccCurrPsRegCnRsltInd(NAS_MMC_GetLRegSuccRsltType());
    }
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == ulCnDomainId)
    {
        NAS_MMC_UpdatePsRegStatePsRegSucc();
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, enServiceState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
    {
        NAS_MMC_UpdateCsRegStateCsRegSucc();
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, enServiceState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == ulCnDomainId)
    {
        NAS_MMC_UpdateCsRegStateCsRegSucc();
        NAS_MMC_UpdatePsRegStatePsRegSucc();

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, enServiceState);
    }
    else
    {
        /* nothing */
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateServiceStateSpecPlmnSearch
 ��������  : ѡ����AnyCell����ָ������ʱ���·���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��04��08��
    ��    ��   : s00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateServiceStateSpecPlmnSearch(VOS_VOID)
{
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;

    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();

#if (FEATURE_ON == FEATURE_LTE)
     /* ����CSFBҵ�񲻸���CSPS����״̬ */
     if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
     {
         return;
     }
#endif

     /* �ж�פ�������MCC��MNC��Ч */
    if (VOS_TRUE == NAS_MMC_IsInValidCampPlmn())
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        return;
    }

    /* �������������Ϊ���Ʒ���;�������治��-���ж�CS������attach��� */
    if( NAS_MMC_NORMAL_SERVICE == enCsServiceStatus)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS ,NAS_MMC_LIMITED_SERVICE);
    }

    if( NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }

    return;
}

/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertMsccMsModeToMmlMsMode
 ��������  : ��ȡCS�������仯����
 �������  : enMsMode:�ֻ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:CS����������
              VOS_FALSE:CS������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MML_MS_MODE_ENUM_UINT8  NAS_MMC_ConvertMsccMsModeToMmlMsMode(
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsccMsMode
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          enMmlMsMode;

    /* ��ʼ��ΪNAS_MML_MS_MODE_BUTT */
    enMmlMsMode = NAS_MML_MS_MODE_BUTT;

    switch (enMsccMsMode)
    {
        case NAS_MSCC_PIF_MS_MODE_A:

            enMmlMsMode = NAS_MML_MS_MODE_PS_CS;
            break;

        case NAS_MSCC_PIF_MS_MODE_CG:

            enMmlMsMode = NAS_MML_MS_MODE_PS_ONLY;
            break;

        case NAS_MSCC_PIF_MS_MODE_CC:

            enMmlMsMode = NAS_MML_MS_MODE_CS_ONLY;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MML_ConvertMsccMsModeToMmlMsMode: Ms Mode Type Error");
    }

    return enMmlMsMode;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsDomainCapaChangeType
 ��������  : ��ȡCS�������仯����
 �������  : enMsMode:�ֻ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:CS����������
              VOS_FALSE:CS������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM_UINT8  NAS_MMC_GetCsDomainCapaChangeType(
    NAS_MML_MS_MODE_ENUM_UINT8          enOldMsMode,
    NAS_MML_MS_MODE_ENUM_UINT8          enNewMsMode
)
{
    VOS_UINT32                          ulOldCsAvailFlg;
    VOS_UINT32                          ulNewCsAvailFlg;

    ulOldCsAvailFlg = NAS_MML_IsCsServDomainAvail(enOldMsMode);
    ulNewCsAvailFlg = NAS_MML_IsCsServDomainAvail(enNewMsMode);

    /* �ɵ�CS���������µ���ͬʱ���ޱ仯 */
    if (ulOldCsAvailFlg == ulNewCsAvailFlg)
    {
        return NAS_MMC_CS_DOMAIN_CAPA_NO_CHANGE;
    }

    /* �ɵ�CS���������ã��µ�CS������������ */
    if ( (VOS_TRUE  == ulOldCsAvailFlg)
      && (VOS_FALSE == ulNewCsAvailFlg) )
    {
        return NAS_MMC_CS_DOMAIN_CAPA_AVAIL_TO_UNAVAIL;
    }

    /* �ɵ�CS�����������ã��µ�CS���������� */
    return NAS_MMC_CS_DOMAIN_CAPA_UNAVAIL_TO_AVAIL;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelForbPlmnFromAsSrchedPlmnList
 ��������  : ���б���ɾ����ֹ��PLMN
 �������  : pstSrchedPlmn:��ɾ����PLMN��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��03��
   ��    ��   : L65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��09��11��
   ��    ��   : w00242748
   �޸�����   : ����澯����
 3.��    ��   : 2013��10��18��
   ��    ��   : z00161729
   �޸�����   : DTS2013101705317:oos was�ϱ�limit service camp in���ڶ������������
                ����forbidden plmn��mmc���������б������ڲ���������
*****************************************************************************/
VOS_VOID NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
)
{
    VOS_UINT32                                              ulPlmnCnt;
    VOS_UINT32                                              ulRatCnt;

    /* ɾ����ֹ��PLMN��Ϣ */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulHighPlmnNum; )
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt])))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulHighPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));

                pstSrchedPlmn[ulRatCnt].ulHighPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulLowPlmnNum; )
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt].stPlmnId)))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulLowPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));

                pstSrchedPlmn[ulRatCnt].ulLowPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList
 ��������  : ���б���ɾ�����û�ָ����PLMN
 �������  : pstSrchedPlmn:��ɾ����PLMN��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��03��
   ��    ��   : L65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��09��011��
   ��    ��   : w00242748
   �޸�����   : ����澯����
 3.��    ��   : 2013��10��18��
   ��    ��   : z00161729
   �޸�����   : DTS2013101705317:oos was�ϱ�limit service camp in���ڶ������������
               ����forbidden plmn��mmc���������б������ڲ���������

*****************************************************************************/
VOS_VOID NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSrchedPlmn
)
{
    VOS_UINT32                                              ulPlmnCnt;
    VOS_UINT32                                              ulRatCnt;
    VOS_UINT32                                              ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU                              *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();
    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL != NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    /* �ֶ�����ģʽ��,ɾ�����û�ָ����PLMN��Ϣ */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        if ((VOS_TRUE != NAS_MMC_GetUserSpecPlmnRegisterStatus())
         || (VOS_TRUE != ulEplmnValidFlg))
        {
            /* EPLMN��Ч�������Ŀǰ������ */
            pstSrchedPlmn[ulRatCnt].ulHighPlmnNum = 0;

            /* EPLMN��Ч�������Ŀǰ������ */
            pstSrchedPlmn[ulRatCnt].ulLowPlmnNum  = 0;

            continue;
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulHighPlmnNum; )
        {
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                                        pEplmnAddr->ucEquPlmnNum,
                                        pEplmnAddr->astEquPlmnAddr))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulHighPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));

                pstSrchedPlmn[ulRatCnt].ulHighPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulLowPlmnNum; )
        {
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt].stPlmnId),
                                        pEplmnAddr->ucEquPlmnNum,
                                        pEplmnAddr->astEquPlmnAddr))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulLowPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));

                pstSrchedPlmn[ulRatCnt].ulLowPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitSearchedPlmnListInfo
 ��������  : ��ʼ���������������б���Ϣ
 �������  : pstListInfo - ��Ҫ��ʼ���������б���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : z00161729
   �޸�����   : DTS2013062406563:WAS����̬OOS,T305�����ڼ�ֻ���ڱ�ϵͳ���ѵ�Чplmn��
                ����פ������ϵͳ�������磬Ҳ������ϵͳ�½��������������޷��ܿ�����������ע�ᣬnas����޸�

*****************************************************************************/
VOS_VOID NAS_MMC_InitSearchedPlmnListInfo(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;

    if (VOS_NULL_PTR == pstListInfo)
    {
        return;
    }

    for ( i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* �����ȼ��б� */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* �����ȼ��б� */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateSearchedPlmnListInfo
 ��������  : �����������������б���Ϣ
 �������  : pstRrcList  WAS����ʱ�ϱ��������б���Ϣ
 �������  : pstListInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��29��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��21��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo(
    NAS_MMC_SEARCHED_TYPE_STRU                             *pstSearchedType,
    RRC_PLMN_ID_LIST_STRU                                  *pstRrcList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    if ((VOS_NULL_PTR == pstRrcList)
     || (VOS_NULL_PTR == pstListInfo))
    {
        return;
    }

    /* ��ȡ���ȼ��б� */
    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* ��ʼ���ϱ��Ľ��뼼���б� */
    for (i =0; i< pstRatPrioList->ucRatNum; i++)
    {
        pstListInfo[i].enRatType        = pstRatPrioList->aucRatPrio[i];
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;

        /* ����AS�Ѿ������������ͣ�û������ϢʱĬ��û�ѹ� */
        pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_FALSE;
        pstListInfo[i].stSearchedType.ucPrefBandSearchedFlg = VOS_FALSE;
        pstListInfo[i].stSearchedType.ucSpecSearchedFlg     = VOS_FALSE;

        if ((pstListInfo[i].enRatType == NAS_MML_GetCurrNetRatType())
         && (VOS_NULL_PTR != pstSearchedType))
        {
            /* �Ѿ����й�spec��ʱ����Ϊhistory��pref bandҲ�Ѿ��ѹ� */
            if (VOS_TRUE == pstSearchedType->ucSpecSearchedFlg)
            {
                pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
                pstListInfo[i].stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
                pstListInfo[i].stSearchedType.ucSpecSearchedFlg     = VOS_TRUE;
                break;
            }

            /* �Ѿ����й�pref band��ʱ����ΪhistoryҲ�Ѿ��ѹ� */
            if (VOS_TRUE == pstSearchedType->ucPrefBandSearchedFlg)
            {
                pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
                pstListInfo[i].stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
                break;
            }

            if (VOS_TRUE == pstSearchedType->ucHistorySearchedFlg)
            {
                pstListInfo[i].stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
                break;
            }
        }
    }




    /* ����������б���������Ӧ���뼼�����б� */
    for (i = 0; i < pstRrcList->ulHighPlmnNum; i++)
    {
        /* ת��RRC��ʽ�Ľ��뼼�� */
        NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[i].ulRat, &enRat);

        for (j = 0; j < pstRatPrioList->ucRatNum; j++)
        {
            if (enRat == pstListInfo[j].enRatType)
            {
                pstListInfo[j].astHighPlmnList[pstListInfo[j].ulHighPlmnNum].ulMcc
                       = pstRrcList->aHighPlmnList[i].stPlmnId.ulMcc;

                pstListInfo[j].astHighPlmnList[pstListInfo[j].ulHighPlmnNum].ulMnc
                       = pstRrcList->aHighPlmnList[i].stPlmnId.ulMnc;

                pstListInfo[j].ulHighPlmnNum ++;

                break;
            }
        }
    }

    /* ����������б���������Ӧ���뼼�����б� */
    for (i = 0; i < pstRrcList->ulLowPlmnNum; i++)
    {
        /* ת��RRC��ʽ�Ľ��뼼�� */
        NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[i].PlmnId.ulRat, &enRat);

        for (j = 0; j < pstRatPrioList->ucRatNum; j++)
        {
            if ( enRat == pstListInfo[j].enRatType)
            {
                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;

                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc;

                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].lRscp
                       = pstRrcList->aLowPlmnList[i].lRscp;

                pstListInfo[j].ulLowPlmnNum ++;

                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildEquPlmnInfo
 ��������  : �����Чplmn��Ϣ
 �������  : ��
 �������  : pstEquPlmnInfo - �����ĵ�Чplmn�б�,
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
 3.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 4.��    ��   : 2015��4��23��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_BuildEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU         *pstOutEplmnInfo
)
{
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               ucSndEplmnNum;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrPlmnId = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    MSCC_MMC_PLMN_ID_STRU                                   astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];

    PS_MEM_SET(astEquPlmnAddr, 0, sizeof(astEquPlmnAddr));

    /* ��ȡ��ǰפ��������͵�Чplmn  */
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();
    ucSndEplmnNum = 0;
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* EPLMN����ʱ */
    if (pstOutEplmnInfo->ucEquPlmnNum > 0)
    {
        for (ulLoop = 0; ulLoop < pstOutEplmnInfo->ucEquPlmnNum; ulLoop++)
        {
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstOutEplmnInfo->astEquPlmnAddr[ulLoop]),
                                               (VOS_UINT8)ucSndEplmnNum, astEquPlmnAddr))
            {
                continue;
            }

            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstOutEplmnInfo->astEquPlmnAddr[ulLoop])))
            {
                continue;
            }

            /* ��������뼼����PLMN ID */
            stPlmnWithRat.enRat         = NAS_MML_GetCurrNetRatType();
            stPlmnWithRat.stPlmnId      = pstOutEplmnInfo->astEquPlmnAddr[ulLoop];

            /* �жϵ�ЧPLMN�Ƿ��ڽ�ֹ���뼼����PLMN�б���,������򲻽���PLMN ID����RRC */
            if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                continue;
            }

            astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstOutEplmnInfo->astEquPlmnAddr[ulLoop].ulMcc;
            astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstOutEplmnInfo->astEquPlmnAddr[ulLoop].ulMnc;

            ucSndEplmnNum++;
        }
    }
    /*Eplmn������ʱ��ֻ��ӵ�ǰ����*/
    else
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(pstCurrPlmnId))
        {
            astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstCurrPlmnId->ulMcc;
            astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstCurrPlmnId->ulMnc;

            ucSndEplmnNum++;
        }
    }


    pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsExistAvailPlmnInSearchedPlmnList
 ��������  : �ж������б����Ƿ��п�������
 �������  : pastIntraPlmnSrchInfo:PLMN��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�п�������
             VOS_FALSE:�޿�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��03��
   ��    ��   : L65478
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastIntraPlmnSrchInfo
)
{
    VOS_UINT32                                              ulRatCnt;

    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_FALSE;
    }

    /* �п�������,��Ҫ�������� */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        if ((0 != pastIntraPlmnSrchInfo[ulRatCnt].ulHighPlmnNum)
         || (0 != pastIntraPlmnSrchInfo[ulRatCnt].ulLowPlmnNum))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_PTM)


/*****************************************************************************
 �� �� ��  : NAS_MMC_CsRegErrRecord
 ��������  : ��¼CSע��ʧ���¼�
 �������  : MMMMC_CS_REG_RESULT_IND_STRU *pstCsRegRstInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_CsRegErrRecord(MMMMC_CS_REG_RESULT_IND_STRU *pstCsRegRstInd)
{
    NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU                    stCsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* �ж϶�Ӧ���쳣ԭ��ֵ�Ƿ���Ҫ��¼ */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstCsRegRstInd->enRegFailCause);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stCsRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_CS_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCsRegRstEvent.ulLuResult        = pstCsRegRstInd->enLuResult;
    stCsRegRstEvent.enNetType         = pstCsRegRstInd->enNetType;
    stCsRegRstEvent.ucIsComBined      = pstCsRegRstInd->ucIsComBined;
    stCsRegRstEvent.usRegFailCause    = pstCsRegRstInd->enRegFailCause;
    stCsRegRstEvent.ulServiceStatus   = pstCsRegRstInd->ulServiceStatus;
    stCsRegRstEvent.ulCsUpdateStatus  = pstCsRegRstInd->ulCsUpdateStatus;
    stCsRegRstEvent.ulLuAttemptCnt    = pstCsRegRstInd->ulLuAttemptCnt;

    PS_MEM_CPY(&stCsRegRstEvent.stOldLai, &pstCsRegRstInd->stOldLai, sizeof(MM_LAI_STRU));

    NAS_MNTN_OutputPositionInfo(&stCsRegRstEvent.stPositionInfo);

    stCsRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stCsRegRstEvent.usRegFailCause);
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_CsRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stCsRegRstEvent,
                           sizeof(stCsRegRstEvent));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PsRegErrRecord
 ��������  : ��¼PSע���쳣�¼�
 �������  : GMMMMC_PS_REG_RESULT_IND_STRU *pstPsRegRstInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_PsRegErrRecord(GMMMMC_PS_REG_RESULT_IND_STRU *pstPsRegRstInd)
{
    NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU                    stPsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* �ж϶�Ӧ���쳣ԭ��ֵ�Ƿ���Ҫ��¼ */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstPsRegRstInd->enRegFailCause);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU);

    /* ���PSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stPsRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_PS_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsRegRstEvent.enGmmActionType   = pstPsRegRstInd->enGmmActionType;
    stPsRegRstEvent.ulActionResult    = pstPsRegRstInd->enActionResult;
    stPsRegRstEvent.enReqDomain       = pstPsRegRstInd->enReqDomain;
    stPsRegRstEvent.enRsltDomain      = pstPsRegRstInd->enRsltDomain;
    stPsRegRstEvent.usRegFailCause    = pstPsRegRstInd->enRegFailCause;
    stPsRegRstEvent.enNetType         = pstPsRegRstInd->enNetType;
    stPsRegRstEvent.ulRegCounter      = pstPsRegRstInd->ulRegCounter;
    stPsRegRstEvent.ulServiceStatus   = pstPsRegRstInd->ulServiceStatus;

    NAS_MNTN_OutputPositionInfo(&stPsRegRstEvent.stPositionInfo);
    stPsRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stPsRegRstEvent.usRegFailCause);
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stPsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_PsRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stPsRegRstEvent,
                           sizeof(stPsRegRstEvent));
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PsServiceRegErrRecord
 ��������  : ��¼PS Service �����쳣�¼�
 �������  : GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU  *pstServiceRsltInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��28��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_PsServiceRegErrRecord(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU                stPsSrvRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* �ж϶�Ӧ���쳣ԭ��ֵ�Ƿ���Ҫ��¼ */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstServiceRsltInd->enRegFailCause);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU);

    /* ���PSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stPsSrvRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsSrvRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsSrvRegRstEvent.enActionResult = pstServiceRsltInd->enActionResult;
    stPsSrvRegRstEvent.enRegFailCause = pstServiceRsltInd->enRegFailCause;
    stPsSrvRegRstEvent.ulServiceSts   = pstServiceRsltInd->ulServiceSts;

    NAS_MNTN_OutputPositionInfo(&stPsSrvRegRstEvent.stPositionInfo);

    stPsSrvRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stPsSrvRegRstEvent.enRegFailCause);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stPsSrvRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_PsServiceRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stPsSrvRegRstEvent,
                           sizeof(stPsSrvRegRstEvent));
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CmServiceRejErrRecord
 ��������  : ��¼Cm Service �����쳣�¼�
 �������  : VOS_UINT32                              ulCause,
             VOS_UINT32                              ulServiceStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_CmServiceRejErrRecord(
    VOS_UINT32                                              ulCause,
    VOS_UINT32                                              ulServiceStatus
)
{
    NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU                   stCmSrvRejIndEvent;
    VOS_UINT32                                              ulIsLogNeedRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CM_SRV_REJ_IND);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU);

    /* ���Cm���񱻾��쳣��Ϣ */
    PS_MEM_SET(&stCmSrvRejIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCmSrvRejIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCmSrvRejIndEvent.ulCause         = ulCause;
    stCmSrvRejIndEvent.ulServiceStatus = ulServiceStatus;

    NAS_MNTN_OutputPositionInfo(&stCmSrvRejIndEvent.stPositionInfo);
    stCmSrvRejIndEvent.ucOriginalCause = NAS_MML_GetOriginalRejectCause(stCmSrvRejIndEvent.ulCause);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCmSrvRejIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_CmServiceRejErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stCmSrvRejIndEvent,
                           sizeof(stCmSrvRejIndEvent));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_MoDetachIndRecord
 ��������  : ��¼MO Detachָʾ�¼�
 ��������  : ��¼����Detachָʾ�¼�
 �������  : VOS_UINT32                              ulDetachType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_MoDetachIndRecord(
    VOS_UINT32                              ulDetachType
)
{
    NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU                    stMoDetachIndEvent;
    VOS_UINT32                                              ulIsLogNeedRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MO_DETACH_IND);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU);

    /* ��䱾��DETACH�쳣��Ϣ */
    PS_MEM_SET(&stMoDetachIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stMoDetachIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_MO_DETACH_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    NAS_MNTN_OutputPositionInfo(&stMoDetachIndEvent.stPositionInfo);

    stMoDetachIndEvent.enDetachType         = ulDetachType;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stMoDetachIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MoDetachIndRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MO_DETACH_IND,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stMoDetachIndEvent,
                           sizeof(stMoDetachIndEvent));

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ErrLogRecordCsOosCause
 ��������  : ��¼CS��������ԭ��ֵ
 �������  : enOldCsRegStatus -- �ɵ�CS��ע��״̬
             enNewCsRegStatus -- �µ�CS��ע��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ErrLogRecordCsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldCsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewCsRegStatus
)
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32    enOosCause;

    /* �з����޷��������£���¼�޷����ԭ�� */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == enOldCsRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enOldCsRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK != enNewCsRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enNewCsRegStatus)))
    {
        enOosEvent = NAS_MML_GetErrLogOosEvent();
        enOosCause = NAS_MNTN_ConvertOosEventToOosCause(enOosEvent);

        NAS_MML_SetErrLogCsOosCause(enOosCause);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ErrLogRecordPsOosCause
 ��������  : ��¼PS��������ԭ��ֵ
 �������  : enOldPsRegStatus -- �ɵ�PS��ע��״̬
             enNewPsRegStatus -- �µ�PS��ע��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ErrLogRecordPsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldPsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewPsRegStatus
)
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32    enOosCause;

    /* �з����޷��������£���¼�޷����ԭ�� */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == enOldPsRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enOldPsRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK != enNewPsRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enNewPsRegStatus)))
    {
        enOosEvent = NAS_MML_GetErrLogOosEvent();
        enOosCause = NAS_MNTN_ConvertOosEventToOosCause(enOosEvent);

        NAS_MML_SetErrLogPsOosCause(enOosCause);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ErrLogClrNwSearchCount
 ��������  : ���������¼����
 �������  : enOldRegStatus -- �ɵ���ע��״̬
             enNewRegStatus -- �µ���ע��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ErrLogClrNwSearchCount(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewRegStatus
)
{
    /* �޷����з��������£����������¼�Ĵ��� */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK != enOldRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enOldRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enNewRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enNewRegStatus)))
    {
        NAS_MML_ClrErrLogNwSearchCount();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RecordErrLogOosEvent
 ��������  : ��¼��������¼�
 �������  : enOosEvent
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RecordOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent
)
{
    NAS_MML_SetErrLogOosEvent(enOosEvent);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RecordOosEventForPlmnSearchScene
 ��������  : ��������������¼��������¼�
 �������  : enPlmnSearchScene
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RecordOosEventForPlmnSearchScene(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene
)
{
    switch (enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_DISABLE_LTE);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_ENABLE_LTE);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RecordOosEventForDetachReason
 ��������  : ����DETACHԭ���¼��������¼�
 �������  : enDetachReason
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RecordOosEventForDetachReason(
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32  enDetachReason
)
{
    switch (enDetachReason)
    {
        case NAS_MSCC_PIF_DETACH_REASON_USER_DETACH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_DETACH);
            break;

        case NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH:
        case NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG);
            break;

        default:
            break;
    }

    return;

}

/* ������ȡNAS�������Ϣ���� */
/*****************************************************************************
 �� �� ��  : MM_GetNasInfo
 ��������  : WAS ��ȡͨ�����ô˽ӿ�����ȡNAS�������Ϣ������˵PLMN����Ϣ��
             ��
 �������  : VOS_INT8 ucType -- 0 :  PLMN��Ϣ�뿨״̬��Ϣ��� ����ֵδ����
             VOS_VOID *pMmInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��1��4��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���,����A32D01561���ⵥ���
  2.��    ��   : 2006��12��5��
    ��    ��   : luojian 60022475
    �޸�����   : Maps3000�ӿ��޸�
  3.��    ��   : 2010��08��14��
    ��    ��   : s46746
    �޸�����   : DTS2010081400653,PLMN��Ϣ�޸�Ϊֱ�Ӹ������ָʾEPLMN����GAS��ȷ��
  4.��    ��   : 2011��12��07��
    ��    ��   : s46746
    �޸�����   : DTS2011112501364,��ǰû��EPLMN�б�ʱ��Ҫ����ǰ������ΪEPLMN����,�����޷�������ϵͳ��ѡ
  5.��    ��   : 2012��2��2��
    ��    ��   : l00130025
    �޸�����   : DTS2012011905274,MM_GetNasInfo�е�Eplmn���󣬵���L���޷���ѡ��G��
  6.��    ��   : 2012��8��15��
    ��    ��   : w00176964
    �޸�����   : V7R1C50_GUTL_PhaseII:��disabled RAT�е�PLMN�ӵ�ЧPLMN�б���ɾ�����͸�RRC
  7.��    ��   : 2012��12��4��
    ��    ��   : w00176964
    �޸�����   : DTS201212905979:֪ͨRRC��ǰEPLMNʱ,�����ֹPLMN
  8.��    ��   : 2013��10��15��
    ��    ��   : z00161729
    �޸�����   : DTS2013082907281:UE��w���н������й���rrc rej�ض���g����Ϣ��
                ���н������޷��ɹ��ض���wԭС������Ϊ������ѯplmnʱnasֻ����gС��plmn
  9.��    ��   : 2013��11��18��
    ��    ��   : z00161729
    �޸�����   : DTS2013111807881:������ѯeplmn����ǰפ��������Ҫ�ж��Ƿ�Ϊ��ֹ���磬�������֪ͨ�����
  10.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  11.��    ��   : 2015��4��23��
     ��    ��   : z00161729
     �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID MM_GetNasInfo(MM_INFO_ST *pMmInfo)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmn;
    NAS_MML_LAI_STRU                                       *pstLai;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnAddr;
    VOS_UINT32                                              i;
    PLMN_INFO_LIST_ST                                      *pstPlmnList;
    MM_INFO_ST                                             *pstMmInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    VOS_UINT32                                              ulIsPlmnIdInDestPlmnWithRatList;
    VOS_UINT32                                              ulIsPlmnIdInForbidPlmnList;

    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList =VOS_NULL_PTR;


    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    pstEquPlmn        = NAS_MML_GetEquPlmnList();
    pstMmInfo         = (MM_INFO_ST *)pMmInfo;
    pstPlmnList       = &(pstMmInfo->stPlmnInfo);


    pstCurPlmnAddr    = NAS_MML_GetCurrCampPlmnId();
    pstLai            = NAS_MML_GetCurrCampLai();

    pstPlmnList->stEplmnInfo.ulPlmnIdNum  = 0;
    pstPlmnList->stEplmnInfo.bitOpCurPlmn = VOS_FALSE;
    pstUserSpecPlmnId                     = NAS_MMC_GetUserSpecPlmnId();
    ulEplmnValidFlg                       = NAS_MML_GetEplmnValidFlg();
    ulRegFlag                             = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    /*��ȡ��ֹ�б�*/
    pstPlmnList->ulForbLaNum = pstForbidPlmnInfo->ucForbRoamLaNum;

    for (i = 0; i < pstPlmnList->ulForbLaNum; i++)
    {
        pstPlmnList->aForbLaList[i].PlmnId.ulMcc = pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMcc;
        pstPlmnList->aForbLaList[i].PlmnId.ulMnc = pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMnc;

        pstPlmnList->aForbLaList[i].ulForbLac    = (VOS_UINT32)pstForbidPlmnInfo->astForbRomLaList[i].aucLac[1]
                                                   |(VOS_UINT32)((VOS_UINT32)pstForbidPlmnInfo->astForbRomLaList[i].aucLac[0]<<8);
    }

    pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
    for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
    {
        pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if ( (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList))
          && ( pstPlmnList->ulForbLaNum < RRC_MAX_FORBLA_NUM) )
        {
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].PlmnId.ulMcc   =
                        pstLai->stPlmnId.ulMcc;
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].PlmnId.ulMnc   =
                        pstLai->stPlmnId.ulMnc;
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].ulForbLac      =
                        ((VOS_UINT32)((pstLai->aucLac[0]) << 8 ) | (VOS_UINT32)((pstLai->aucLac[1])));
            (pstPlmnList->ulForbLaNum)++;
        }
    }


    /*��ȡusim��״̬*/
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {                                                                           /* SIM��������                              */
        pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_UICC_ABSENT;                                      /* �趨SIM��״̬                            */
    }
    else
    {                                                                           /* SIM������                                */
        if (NAS_MML_SIM_TYPE_SIM  == NAS_MML_GetSimType())
        {
            pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_SIM_PRESENT;
        }
        else
        {
            pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_USIM_PRESENT;                                     /* �趨SIM��״̬                            */
        }

        pstMmInfo->ucUeOperMode = NAS_MML_GetUeOperMode();
    }

    pMmInfo->stCurPlmnId.ulMcc = pstCurPlmnAddr->ulMcc;
    pMmInfo->stCurPlmnId.ulMnc = pstCurPlmnAddr->ulMnc;

    pMmInfo->usCurLac          = (VOS_UINT16)pstLai->aucLac[1]
                                 |(VOS_UINT16)((VOS_UINT16)pstLai->aucLac[0]<<8);

    pMmInfo->ucCurRac          = NAS_MML_GetCurrCampRac();

    pstPlmnList->stEplmnInfo.stCurCampedPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnList->stEplmnInfo.stCurCampedPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        stPlmnWithRat.stPlmnId = pstUserSpecPlmnId->stPlmnId;
    }
    else
    {
        stPlmnWithRat.stPlmnId = *pstCurPlmnAddr;
    }

    ulIsPlmnIdInDestPlmnWithRatList = NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat);

    ulIsPlmnIdInForbidPlmnList = NAS_MML_IsPlmnIdInForbidPlmnList(&stPlmnWithRat.stPlmnId);

    if ((VOS_FALSE == ulIsPlmnIdInDestPlmnWithRatList)
     && (VOS_FALSE == ulIsPlmnIdInForbidPlmnList))
    {
        pstPlmnList->stEplmnInfo.bitOpCurPlmn = VOS_TRUE;
        pMmInfo->stPlmnInfo.stEplmnInfo.stCurCampedPlmnId.ulMcc = stPlmnWithRat.stPlmnId.ulMcc;
        pMmInfo->stPlmnInfo.stEplmnInfo.stCurCampedPlmnId.ulMnc = stPlmnWithRat.stPlmnId.ulMnc;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* �ж�eplmn�б��Ƿ���Ч,��Ч�򷵻� */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            pstPlmnList->stEplmnInfo.ulPlmnIdNum  = 0;
            return;
        }
    }

    /* ��ȡ��ЧPLMN�б�,����ǰ���粻��Eplmn��,����ǰ���緵�ظ������ */
    for (i = 0; i < pstEquPlmn->ucEquPlmnNum; i++)
    {
        /* ��������뼼����PLMN ID */
        stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;
        stPlmnWithRat.stPlmnId      = pstEquPlmn->astEquPlmnAddr[i];

        /* �жϵ�ЧPLMN�Ƿ��ڽ�ֹ���뼼����PLMN�б���,������򲻽���PLMN ID����RRC */
        if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstEquPlmn->astEquPlmnAddr[i])))
        {
            continue;
        }

        pstPlmnList->stEplmnInfo.aPlmnIdList[pstPlmnList->stEplmnInfo.ulPlmnIdNum].ulMcc = pstEquPlmn->astEquPlmnAddr[i].ulMcc;
        pstPlmnList->stEplmnInfo.aPlmnIdList[pstPlmnList->stEplmnInfo.ulPlmnIdNum].ulMnc = pstEquPlmn->astEquPlmnAddr[i].ulMnc;
        pstPlmnList->stEplmnInfo.ulPlmnIdNum++;
    }



    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCsPsBothRegSucc
 ��������  : �ж�cs��ps�Ƿ�ע��ɹ�
 �������  : enNetRatType - ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:cs��psע����ɹ�
             VOS_FALSE:cs��ps���Ƕ�ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��22��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCsPsBothRegSucc(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;


    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();


    /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            enNetRatType,
                                            &enCsRegCause,
                                            &enPsRegCause);


    if ((NAS_MMC_NORMAL_SERVICE == enCsServiceStatus)
     && (NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enCsRegCause)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail
 ��������  : IMS�����ú��ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��5��6��
   ��    ��   : z00161729
   �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
 3.��    ��   : 2014��5��8��
   ��    ��   : z00161729
   �޸�����   : DTS2014050701865:volte�޸�cs ps mode1 l��16��17��22�ܾ���5��disable lte��δ����enable lte��ʱ��
 4.��    ��   : 2014��5��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014051402293:CSPS MODE1��ָ����24005 L��LTE��ע��ɹ���ָʾSMS ONLY��
                Disable LTE�󣬷���GU��������GU������ʧ�ܣ�RECAMP LTE(������)������available
                ��ʱ����ʱ�󣬷����б��ѣ���������24005��ЧPLMN��46002L��24005L��23002GU��ָ��
                ��������L��PLMNʧ�ܣ�����פ����GU23002�£�������available��ʱ����available��ʱ
                ����ʱ��������24005 L(����Ҫdisalbe lte������)��L�¸�NAS�ϱ�TAU�����̣���ʱNAS
                δ����Disable LTE��Ҳδ����available��ʱ����
 5.��    ��   : 2014��5��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014051308442:L��ע��ɹ�֧��IMS����SMS ONLY��������TAU��16��һ�Σ�ֱ��disable
                LTE��
 6.��    ��   : 2014��5��20��
   ��    ��   : s00217060
   �޸�����   : DTS2014051406792:L��TAU����#18������other cause����5��֮��disable LTE��
 7.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
 8.��    ��   : 2015��4��22��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail(VOS_VOID)
{
    VOS_UINT32                                              ulIsNeedDisableL;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MMC_SERVICE_ENUM_UINT8                              enPsServiceStatus;

    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    VOS_UINT32                                              ulIsNeedAddVoiceNotAvailPlmnFlag;

    NAS_MMC_REG_RSLT_CTX_STRU                              *pstRegRsltCtx = VOS_NULL_PTR;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS");
        return VOS_FALSE;
    }


    /* ֮ǰ��L�½��й�δTAU��ATTACH��ҵ������ */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: CURR NOT LTE");
        return VOS_FALSE;
    }

    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();

    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MML_NET_RAT_TYPE_LTE,
                                            &enCsRegCause,
                                            &enPsRegCause);

    /* CS+EPS ���ɹ� */
    if (VOS_TRUE == NAS_MMC_IsCsPsBothRegSucc(NAS_MML_NET_RAT_TYPE_LTE))
    {
        ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc();

        if (VOS_TRUE == ulIsNeedDisableL)
        {
            if (VOS_TRUE == NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat, NAS_MML_REG_FAIL_CAUSE_NULL, NAS_MML_REG_FAIL_CAUSE_NULL, NAS_MML_GetAdditionUpdateRslt()))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }
        }

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: CS&EPS SUCC");

        return ulIsNeedDisableL;
    }

    if ((NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
    {

        /* EPS����ע��ɹ� */
        if (VOS_TRUE == pstRegRsltCtx->ucIsLteRegTypeEpsOnly)
        {
            ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc();

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: ONLY EPS SUCC");

            return ulIsNeedDisableL;
        }

        /* EPS ONLY�ɹ�,CS����18,CS����16,17,22,other cause,EPS���Դ����ﵽ5�� */
        if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != enCsRegCause)
        {
            ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_CombinedRegRsltOnlyEpsSucc(enCsRegCause);

            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: ulIsNeedDisableL.", ulIsNeedDisableL);

            if ((NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
              && (VOS_TRUE == ulIsNeedDisableL))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

                if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
                {
                    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                                  NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                                  MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
                }

            }

            ulIsNeedAddVoiceNotAvailPlmnFlag = NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat, enCsRegCause, enPsRegCause, NAS_MML_GetAdditionUpdateRslt());

            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail: ulIsNeedAddVoiceNotAvailPlmnFlag.", ulIsNeedAddVoiceNotAvailPlmnFlag);

            if ((VOS_TRUE == ulIsNeedDisableL)
             && (VOS_TRUE == ulIsNeedAddVoiceNotAvailPlmnFlag))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }
            return ulIsNeedDisableL;
        }
    }

    return VOS_FALSE;
}

#endif
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen
 ��������  : ��ȡGAS��������ʱ��ʱ��
 �������  : ulUserSpecSearchFlg:�Ƿ��û�ָ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���:��ǰ��DSDS˫���У�GSM���������ܲ���NAS ����NO RF,��ô
                 NAS������ʱ����ʱ�����ϱ��޷����ˡ��޸�Ϊ�ӳ�NAS��ʱ��ʱ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(
    VOS_UINT32                          ulUserSpecSearchFlg
)
{
    /* ��DSDS�汾ģʽ���ҷ��û�ָ����ʱ��ȡ����ʱ����ʱ�� */
    if ( (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
      && (VOS_FALSE == ulUserSpecSearchFlg) )
    {
        return TI_NAS_MMC_DSDS_SCEAN_WAIT_GAS_PLMN_SEARCH_CNF_LEN;
    }

    return TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RegisterRrmResourceNtf
 ��������  : ������RRM����ע����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : y00176023
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��26��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�ӿ��޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RegisterRrmResourceNtf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_RATMODE_ENUM_UINT32             enRrmRat;

    enRrmRat = NAS_MMC_ConvertRatToRrmPsRat(enNasRat);

    /* ��ȡmodem id */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* �����ǰNVδ����DSDS,����RRM����ע�� */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RegisterRrmResourceNtf: DSDS RF SHARE FLG IS VOS_FALSE!!!");
        return;
    }

    /* ����ע����Ϣ */
    if((VOS_RATMODE_BUTT     != enRrmRat)
    && (MODEM_ID_BUTT        != enModemId))
    {
        NAS_MMC_SndRrmRegisterInd(enModemId,
                                  enRrmTaskType,
                                  enRrmRat);
    }

#endif

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_RegisterRrmResourceNtf : enNasRat, enRrmTaskType", enNasRat, enRrmTaskType);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DeregisterRrmResourceNtf
 ��������  : ������RRM����ȥע����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : y00176023
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��26��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�ӿ��޸�
*****************************************************************************/
VOS_VOID NAS_MMC_DeregisterRrmResourceNtf(
    VOS_RATMODE_ENUM_UINT32             enRrmRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    MODEM_ID_ENUM_UINT16                usModemId;

    /* ȡ�õ�ǰMODEM��ID��Ϣ  */
    usModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* �����ǰNVδ����DSDS,����RRM����ȥע�� */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return;
    }

    /* ��RRM���͵�ȥע����Ϣ */
    if((VOS_RATMODE_BUTT     != enRrmRat)
    && (MODEM_ID_BUTT        != usModemId))
    {
        NAS_MMC_SndRrmDeRegisterInd(usModemId,
                                    enRrmTaskType,
                                    enRrmRat);
    }
#endif

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_DeregisterRrmResourceNtf : enRrmRat, enRrmTaskType", enRrmRat, enRrmTaskType);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DeregisterRrmResourceNtfAllRat
 ��������  : ������RRM����ƽ̨֧������RATȥע����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��16��
    ��    ��   : y00176023
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��26��
    ��    ��   : b00269685
    �޸�����   : �ӿ��޸�
*****************************************************************************/
VOS_VOID NAS_MMC_DeregisterRrmResourceNtfAllRat(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    VOS_UINT32                          i;
    NAS_MML_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap  = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    /* LTE�Ƿ���ƽ̨���뼼�������б��� */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_GSM == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_GSM, enRrmTaskType);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (NAS_MML_PLATFORM_RAT_TYPE_LTE == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_LTE, enRrmTaskType);
        }
#endif
        else if (NAS_MML_PLATFORM_RAT_TYPE_WCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_WCDMA, enRrmTaskType);
        }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        else if (NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ע�ᡢȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_TDS, enRrmTaskType);\
        }
#endif
        else
        {
            ;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRatToRrmPsRat
 ��������  : ����������RATת��ΪRRM PS RAT
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : y00176023
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��26��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�ӿ��޸�
*****************************************************************************/
VOS_RATMODE_ENUM_UINT32 NAS_MMC_ConvertRatToRrmPsRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMmcRat
)
{
    VOS_RATMODE_ENUM_UINT32             enRrmPsRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    /*��ȡTD����WCDMA*/
    enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    if (NAS_MML_NET_RAT_TYPE_GSM == enMmcRat)
    {
        enRrmPsRat = VOS_RATMODE_GSM;
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA   == enMmcRat)
          && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode))
    {
        enRrmPsRat = VOS_RATMODE_WCDMA;
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA   == enMmcRat)
          && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
    {
        enRrmPsRat = VOS_RATMODE_TDS;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enMmcRat)
    {
        enRrmPsRat = VOS_RATMODE_LTE;
    }
#endif
    else
    {
        enRrmPsRat = VOS_RATMODE_BUTT;
    }

    return enRrmPsRat;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd
 ��������  : CSFB END�����������Ƿ���Ҫ�������ȼ�RAT��HPLMN��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd( VOS_VOID )
{
    VOS_UINT32                                              ulIsRrcConnExist;
    VOS_UINT32                                              ulIsNeedStartHighPrioRatHPlmnTimer;

    ulIsRrcConnExist                    = NAS_MML_IsRrcConnExist();
    ulIsNeedStartHighPrioRatHPlmnTimer  = NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer();

    /* ҵ�񲻴��ڣ�����RRC���Ӳ����ڣ������ȼ�RAT��HPLMN��ʱ����NV�� */
    if ((VOS_FALSE  == NAS_MML_GetCmServiceSetupFlg())
     && (VOS_FALSE  == ulIsRrcConnExist)
     && (VOS_TRUE   == ulIsNeedStartHighPrioRatHPlmnTimer))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer
 ��������  : �ж��Ƿ���Ҫ���������ȼ�RAT��HPLMN��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����HPLMN��ʱ��
             VOS_FALSE:����Ҫ����HPLMN��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo  = VOS_NULL_PTR;

    if (VOS_FALSE == NAS_MMC_IsHighPrioRatHplmnSearchVaild())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER))
    {
        return VOS_FALSE;
    }

    /* ��ȡMML�б���ĵ�ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ� */
    pstPlmnRatList = NAS_MML_GetMsPrioRatList();

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stLai.stPlmnId))
    {
        return VOS_FALSE;
    }

    /* פ����HPLMN��������ȼ��Ľ��뼼�� */
    if (pstPlmnRatList->aucRatPrio[0] == pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsHighPrioRatHplmnSearchVaild
 ��������  : �����ȼ�RAT��HPLMNѡ����ǰ�Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��21��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHighPrioRatHplmnSearchVaild( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU       *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_GetHighPrioRatHplmnTimerActiveFlg())
    {
        return VOS_FALSE;
    }

    /* �ֶ�ģʽ�·�����Ч */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* HPLMN TIMER LEN��ʱ��ʱ����Ч */
    if ((0 != pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen)
     && (0 != pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen)
     && (0 != pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen))
    {
        /* ������Ч */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCampOnHighestPrioRatHplmn
 ��������  : �жϵ�ǰ�Ƿ��Ѿ�פ�������RAT���ȼ���HPLMN��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : �Ѿ�פ�������RAT���ȼ���HPLMN��
             VOS_FALSE : û��פ�������RAT���ȼ���HPLMN��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��22��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCampOnHighestPrioRatHplmn(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo  = VOS_NULL_PTR;

    /* ��ȡMML�б���ĵ�ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ� */
    pstPlmnRatList = NAS_MML_GetMsPrioRatList();

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* �����ǰ������Ч���򷵻�δפ����������ȼ������ϣ�����ģ�����󣬵�ǰפ��������
       ����ЧPLMNID */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&pstCurrCampPlmnInfo->stLai.stPlmnId) )
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stLai.stPlmnId))
    {
        return VOS_FALSE;
    }

    /* פ����HPLMN�Ƿ�������ȼ��Ľ��뼼�� */
    if (pstPlmnRatList->aucRatPrio[0] != pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount
 ��������  : ����Td Count
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount(VOS_VOID)
{
    VOS_UINT8                                               ucCurrHighRatHplmnTdCount;
    VOS_UINT8                                               ucHighRatHplmnTdThreshold;

    if (VOS_FALSE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        return;
    }

    ucCurrHighRatHplmnTdCount = NAS_MMC_GetTdHighRatSearchCount();
    ucHighRatHplmnTdThreshold = NAS_MML_GetHighPrioRatHplmnTimerTdThreshold();

    if (ucCurrHighRatHplmnTdCount >= ucHighRatHplmnTdThreshold)
    {
        NAS_MMC_InitTdHighRatSearchCount();
    }

    NAS_MMC_AddTdHighRatSearchCount();

    return;

}

/* Added by s00246516 for L-C��������Ŀ, 2014-02-12, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnPrioClass
 ��������  : ��ȡָ����������ȼ����
 �������  : pstPlmnId
 �������  : ��
 �� �� ֵ  : NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��13��
    ��    ��   : b00269685
    �޸�����   : ����3gpp2,Pref���粻����UPLMN
*****************************************************************************/
NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8 NAS_MMC_GetPlmnPrioClass(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_BUTT;
    }

    /* ��HPLMN��ͬ������NAS_MSCC_PIF_PLMN_PRIORITY_HOME */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_HOME;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstPlmnId))
    {
        if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
        {
            return NAS_MSCC_PIF_PLMN_PRIORITY_PREF;
        }
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_PREF;
    }

    return NAS_MSCC_PIF_PLMN_PRIORITY_ANY;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComParePlmnPrioClass
 ��������  : �Ƚ�����PLMN���ȼ���������ȼ�
 �������  : enSrcPrioClass
             enDestPrioClass
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --enSrcPrioClass���ȼ����ڻ����enDestPrioClass
             VOS_FALSE --enSrcPrioClass���ȼ�����enDestPrioClass
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComParePlmnPrioClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enSrcPrioClass,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enDestPrioClass
)
{
    /* ���enSrcPrioClass�Ѿ���������ȼ���ֱ�ӷ���VOS_TRUE */
    if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == enSrcPrioClass)
    {
        return VOS_TRUE;
    }
    else if (NAS_MSCC_PIF_PLMN_PRIORITY_PREF == enSrcPrioClass)
    {
        /* ���enSrcPrioClass��NAS_MSCC_PIF_PLMN_PRIORITY_PREF������enDestPrioClassΪ������ȼ�ʱ����VOS_FALSE */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == enDestPrioClass)
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* ���enSrcPrioClass��NAS_MSCC_PIF_PLMN_PRIORITY_ANY������enDestPrioClassΪ��ͬ���ȼ�ʱ����VOS_TRUE */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_ANY == enDestPrioClass)
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSuccRegInSpecCellInfo
 ��������  : �Ƿ��Ѿ���ָ��CellInfo��С����ע��ɹ�
 �������  : pstCellInfo
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --�Ѿ���ָ��CellInfo��С����ע��ɹ�
             VOS_FALSE --û����ָ��CellInfo��С����ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSuccRegInSpecCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCell         = VOS_NULL_PTR;

    /* ���뼼����ͬ������VOS_FALSE */
    if (pstCellInfo->ucRat != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* Ƶ�㲻ͬ������VOS_FALSE */
    if (pstCellInfo->ulArfcn != NAS_MML_GetCurrCampArfcn())
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��PLMN���ڶ����뵱ǰפ����ͬ������VOS_FALSE */
    if (pstCellInfo->ucPlmnNum > 0)
    {
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                  pstCellInfo->ucPlmnNum,
                                                  pstCellInfo->astPlmnId))
        {
            return VOS_FALSE;
        }
    }

    /* ������Ϣ��û��Я��С��ID������VOS_TRUE */
    if (0 == pstCellInfo->ucCellNum)
    {
        return VOS_TRUE;
    }

    pstCampCell     = NAS_MML_GetCampCellInfo();

    /* ������Ϣ��CELL ID���ڶ����뵱ǰפ����ͬ������VOS_TRUE */
    for (i = 0; i < pstCellInfo->ucCellNum; i++)
    {
        if (pstCellInfo->ausCellId[i] == pstCampCell->astCellInfo[0].ulCellId)
        {
            return VOS_TRUE;
        }
    }

    /* ������Ϣ��CELL ID���ڶ����뵱ǰפ����ͬ������VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSearchSceneMsccRegReq
 ��������  : ��MSCCģ���REG������Ϣ�л����������
 �������  : pstRegReq
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccRegReq(
    MSCC_MMC_REG_REQ_STRU               *pstRegReq
)
{
    /* �����ڲ�������Ϣ���������������߼� */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL;
    }
    /* ����ָ�����ȼ���ע�� */
    else if (VOS_TRUE == pstRegReq->bitOpPrioClass)
    {
        /* ����ָ�����ȼ�ΪHPLMN��ע�� */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == pstRegReq->enPrioClass)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN;
        }
        /* ����ָ�����ȼ�ΪPREF��ע�� */
        else if (NAS_MSCC_PIF_PLMN_PRIORITY_PREF == pstRegReq->enPrioClass)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN;
        }
        else
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN;
        }
    }
    /* �쳣������NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN���� */
    else
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN;
    }
}

/* Added by s00246516 for L-C��������Ŀ, 2014-02-12, End */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-19, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_Convert3GPP2RatType
 ��������  : ��MSCC��������3GPP2����ת��ΪMML���͸�ʽ
 �������  : enMSCC3GPP2RatType      MSCC��������3GPP2����
 �������  : *penMML3GPP2RatType    MML�����3GPP2����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��19��
   ��    ��   : w00167002
   �޸�����   : �½�����
*****************************************************************************/
VOS_VOID   NAS_MMC_Convert3GPP2RatType(
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8   enMSCC3GPP2RatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8  *penMML3GPP2RatType
)
{
    switch (enMSCC3GPP2RatType)
    {
        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X:

            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_CDMA1X;
            break;

        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD:

            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_HRPD;
            break;

        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT:
            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcCoverTypeToNasFormat TYPE ERROR!!!");
            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;
    }

    return;
}


/* Added by w00167002 for L-C��������Ŀ, 2014-2-19, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSorTriggerSpecPlmnSrch_L1Main
 ��������  : �ж��Ƿ�SOR����ָ�������������б�����
 �������  : VOS_UINT32
 �������  : VOS_TRUE : ��Ҫ����ָ������
             VOS_FALSE: ����Ҫ����ָ������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��05��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���: DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSorTriggerAdditionalLau(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU                        *pstAdditionalLau    = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampInfo         = VOS_NULL_PTR;


    pstAdditionalLau    = NAS_MML_GetSorAdditionalLauCtx();
    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();

    if ( VOS_FALSE == pstAdditionalLau->ucAdditionalLauFlag )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSorTriggerAdditionalLau: false");
        return VOS_FALSE;
    }

    /* ��ǿ�ж�LAI�Ƿ�ı� */
    if ( VOS_FALSE == NAS_MML_CompareLai(&(pstAdditionalLau->stLai),&(pstCampInfo->stLai)) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSorTriggerAdditionalLau: LAI NO Same");
        return VOS_FALSE;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSorTriggerAdditionalLau: NAS_MMC_PLMN_SELECTION_MODE_MANUAL");
        return VOS_FALSE;
    }

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSorTriggerAdditionalLau: true");

    /* ���򷵻���Ҫ����ADDITIONAL LAU */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccCurrServiceRelatedInfo
 ��������  : �ϱ���MSCC��ǰ��ҵ��״̬��ص���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��06��25��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��07��24��
   ��    ��   : b00269685
   �޸�����   : Coverify����
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCurrServiceRelatedInfo(VOS_VOID)
{
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enMsccServiceState;

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));

    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    /* �ϱ���ǰ��ϵͳ��Ϣ����MSCC������Ϣͬ�� */
    NAS_MMC_SndMsccSysInfo();

    /* �ϱ�CAMP ON��Ϣ */
    /* Modified by b00269685 for Coverify����, 2014-7-24, begin */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    /* Modified by b00269685 for Coverify����, 2014-7-24, end */

    /* �ϱ�����״̬ */
    NAS_MMC_ConvertToMsccSrvStatus(NAS_MMC_GetCsServiceStatus(), &enMsccServiceState);
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS,  enMsccServiceState);

    NAS_MMC_ConvertToMsccSrvStatus(NAS_MMC_GetPsServiceStatus(), &enMsccServiceState);
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS,  enMsccServiceState);

    /* �ϱ�ע��״̬ */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MML_GetCsRegStatus());
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MML_GetPsRegStatus());

    /* �ϱ�RSSI */
    NAS_MMC_SndMsccRssiInd(&unMeasReportType);

    return;
}


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetIndexOfFirstSelfLearningTypeElement
 ��������  : ��ȡ DplmnList �����һ��������Ԥ�����͵�plmn���±�
 �������  :
             pulDestPlmnNum    - DPLMN/NPLMN list����
             pstDestPlmnIdList - DPLMN/NPLMN listָ��
 �������  : ��
 �� �� ֵ  : ulIndex -- �����±�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��18��
   ��    ��   : c00318887
   �޸�����   : for DPlmn���ݺ����Ƚ���HPLMN
 2.��    ��   : 2015��11��3��
   ��    ��   : l00289540
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetIndexOfFirstSelfLearningTypeElement(
    VOS_UINT16                                             *pulFirstPosition,
    VOS_UINT16                                              ulMaxAllowPlmnNum,
    VOS_UINT16                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                    ulLoop  = 0;

    for (ulLoop = 0; ulLoop < ulDestPlmnNum; ulLoop++)
    {
        if (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[ulLoop].enType)
        {
            break;
        }
    }

    /* ����ѧϰ���� */
    if (ulLoop < ulDestPlmnNum)
    {
        *pulFirstPosition = (VOS_UINT16)ulLoop;
        return VOS_TRUE;
    }

    /* û����ѧϰ���� ����û�� */
    if (ulMaxAllowPlmnNum - 1 >= ulDestPlmnNum)
    {
        *pulFirstPosition = ulDestPlmnNum;
        return VOS_TRUE;
    }

    /* û����ѧϰ����, ������  */
    *pulFirstPosition = ulMaxAllowPlmnNum;

    return VOS_FALSE;
}
/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDPlmnNPlmnList
 ��������  : ����DPLMNNPLMN�б�
 �������  : pstCurrPlmnLai - ����ĵ�ǰע�������PLMN��Ϣ
             enNetType      - ���뼼��
             enRegDomain    - ע����
             pulDestPlmnNum - ����DPLMN/NPLMN list����
             pstDestPlmnIdList - ����DPLMN/NPLMN list
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��11��
   ��    ��   : c00188733
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��18��
   ��    ��   : c00318887
   �޸�����   : for DPlmn���ݺ����Ƚ���HPLMN
 3.��    ��   : 2015��10��22��
   ��    ��   : l00289540
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateDPlmnNPlmnList(
    NAS_MML_LAI_STRU                                       *pstCurrLai,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain,
    VOS_UINT16                                              ulMaxAllowPlmnNum,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                                              i;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usSimRat;

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
    VOS_UINT16                                              usIndex;
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */

    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    usSimRat              = NAS_MML_INVALID_SIM_RAT;

    usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstCurrLai->enCampPlmnNetRat);

    for (i = 0; i < *pulDestPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrLai->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
        {
            /* ���PLMN��ͬ��RATҲ��ͬ�򲻸��� */
            if ((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat) == usSimRat)
            {
                return;
            }
            /*���PLMN��ͬ��RAT��ͬ */
            else
            {
                /* ����ѧϰ����,�������RAT */
                /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
                if (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[i].enType)
                {
                    pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat = usSimRat | pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat;
                    return;
                }
                /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */
            }
        }
    }

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
    if (VOS_FALSE == NAS_MMC_GetIndexOfFirstSelfLearningTypeElement(&usIndex, ulMaxAllowPlmnNum, *pulDestPlmnNum, pstDestPlmnIdList))
    {
        return;
    }

    /* ����¼�¼ */
    if (*pulDestPlmnNum < ulMaxAllowPlmnNum )
    {
        (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[usIndex + 1], &pstDestPlmnIdList[usIndex],
                               (*pulDestPlmnNum - usIndex) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMcc    = pstCurrLai->stPlmnId.ulMcc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMnc    = pstCurrLai->stPlmnId.ulMnc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.usSimRat          = usSimRat;
        pstDestPlmnIdList[usIndex].enRegDomain                        = enRegDomain;
        pstDestPlmnIdList[usIndex].enType                             = NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE;
        (*pulDestPlmnNum)++;
    }
    else
    {
        (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[usIndex + 1], &pstDestPlmnIdList[usIndex],
                               (ulMaxAllowPlmnNum - usIndex - 1) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMcc    = pstCurrLai->stPlmnId.ulMcc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMnc    = pstCurrLai->stPlmnId.ulMnc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.usSimRat          = usSimRat;
        pstDestPlmnIdList[usIndex].enRegDomain                        = enRegDomain;
        pstDestPlmnIdList[usIndex].enType                             = NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE;
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */

    /* APû��Ԥ��DPLMN��Ϣ����ѧϰ��DPLMN��Ҳ��Ҫ��Ehplmn���µ�ȫ�ֱ�����NV�У�
     * �Թ�����modem�ж�֪ͨ������DPLMN�Ƿ����ʹ��
     */
    if (0 == pstDPlmnNPlmnCfgInfo->ucEHplmnNum)
    {
        NAS_MMC_UpdateEhplmnToDplmnNplmnCfgInfo();
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateDPlmnNPlmnList
 ��������  : ɾ��DPLMNNPLMN�б�
 �������  : pstCurrPlmnLai - ����ĵ�ǰע�������PLMN��Ϣ
             enNetType      - ���뼼��
             enRegDomain    - ע����
             pulDestPlmnNum - ɾ��DPLMN/NPLMN list����
             pstDestPlmnIdList - ɾ��DPLMN/NPLMN list
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��11��
   ��    ��   : c00188733
   �޸�����   : �����ɺ���
2.��    ��   : 2015��5��18��
  ��    ��   : c00318887
  �޸�����   : for DPlmn���ݺ����Ƚ���HPLMN
*****************************************************************************/
VOS_VOID  NAS_MMC_DeleteDPlmnNPlmnList(
    NAS_MML_LAI_STRU                                       *pstCurrLai,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                                              i;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usSimRat;
    VOS_UINT16                                              usTmpSimRat;
    VOS_UINT32                                              ulIsDplmnType;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    usSimRat                 = NAS_MML_INVALID_SIM_RAT;
    usTmpSimRat              = NAS_MML_INVALID_SIM_RAT;

    usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstCurrLai->enCampPlmnNetRat);

    ulIsDplmnType = NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&(pstCurrLai->stPlmnId),
                                                                         usSimRat,
                                                                         pstDPlmnNPlmnCfgInfo->usDplmnListNum,
                                                                         pstDPlmnNPlmnCfgInfo->astDPlmnList);

    for (i = 0; i < *pulDestPlmnNum;)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrLai->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
        {
            usTmpSimRat = pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat & ~usSimRat;

            /*���PLMN��ͬ��RATҲ��ȫ��ͬ��ɾ��������¼*/
            if(usSimRat == pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)
            {
                /* ɾ������Ԥ�õ�DPLMN�������usPresetDplmnNum */
                if ((VOS_TRUE == ulIsDplmnType)
                 && (NAS_MMC_DPLMN_NPLMN_PRESETTING_TYPE == pstDestPlmnIdList[i].enType))
                {
                    pstDPlmnNPlmnCfgInfo->usPresetDplmnNum--;
                }

                /* Ҫɾ���Ĳ������һ��ʱ���Ѻ�����б�ȫ����ǰ��1λ */
                if ((i + 1) < *pulDestPlmnNum)
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[i], &pstDestPlmnIdList[ i + 1 ],
                            ((*pulDestPlmnNum - i) - 1 ) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
                }

                (*pulDestPlmnNum)--;

                continue;
            }
            /*���PLMN��ͬ��RAT����RAT������һ����ɾ��������ʽ*/
            else if((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat) == usSimRat)
            {
                pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat = usTmpSimRat;
            }
            else
            {

            }
        }

        i++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertApPresetRatToSimRat
 ��������  : ��Ap Ԥ�õ�DPLMN Ratת��ΪSim Rat��ʽ
 �������  : VOS_UINT16 usApPresetDplmnRat
 �������  : ��
 �� �� ֵ  : VOS_UINT16 usSimRat ת�����SIMRAT����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  NAS_MMC_ConvertApPresetRatToSimRat(
    VOS_UINT16                          usApPresetDplmnRat
)
{
    VOS_UINT16                          usSimRat;

    switch (usApPresetDplmnRat)
    {
        case NAS_MML_AP_PRESET_RAT_GSM:
            usSimRat = NAS_MML_SIM_RAT_GSM;
            break;

        case NAS_MML_AP_PRESET_RAT_UTRN:
            usSimRat = NAS_MML_SIM_RAT_UTRN;
            break;

        case NAS_MML_AP_PRESET_RAT_UTRN_GSM:
            usSimRat = NAS_MML_SIM_UTRN_GSM_RAT;
            break;

        case NAS_MML_AP_PRESET_RAT_E_UTRN:
            usSimRat = NAS_MML_SIM_RAT_E_UTRN;
            break;

        case NAS_MML_AP_PRESET_RAT_E_UTRN_GSM:
            usSimRat = NAS_MML_SIM_E_UTRN_GSM_RAT;
            break;

        case NAS_MML_AP_PRESET_RAT_E_UTRN_UTRN:
            usSimRat = NAS_MML_SIM_E_UTRN_UTRN_RAT;
            break;

        case NAS_MML_AP_PRESET_RAT_ALL_SUPPORT:
            usSimRat = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
            break;

        default:
            usSimRat = NAS_MML_INVALID_SIM_RAT;
            break;
    }

    return usSimRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertNetRatToSimRat
 ��������  : ������RAT����ת��ΪSIM����RAT����
 �������  :NAS_MML_NET_RAT_TYPE_ENUM_UINT8   enPlmnNetRat ��Ҫת����NetRAT����
 �������  : ��
 �� �� ֵ  : VOS_UINT16 usSimRat ת�����SIMRAT����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��14��
   ��    ��   : c00188733
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16  NAS_MMC_ConvertNetRatToSimRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPlmnNetRat
)
{
    VOS_UINT16                          usSimRat;

    usSimRat = NAS_MML_INVALID_SIM_RAT;

    if (NAS_MML_NET_RAT_TYPE_LTE == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_E_UTRN;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_UTRN;
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_GSM;
    }
    else
    {
        usSimRat = NAS_MML_INVALID_SIM_RAT;
    }

    return usSimRat;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList
 ��������  : �жϴ����뼼��PLMN ID�Ƿ����б���
 �������  : pstBcchPlmnId:��Ҫ�жϵ�PLMN ID
             usSimPlmnWithRatNum:�б���plmn id�ĸ���
             pstSimPlmnWithRatList:plmn with rat�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID���б���
             VOS_FALSE : PLMN ID�����б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstBcchPlmnIdWithRat,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usBcchPlmnSimRat;

    usBcchPlmnSimRat = NAS_MMC_ConvertNetRatToSimRat(pstBcchPlmnIdWithRat->enRat);

    for ( i = 0; i < usSimPlmnWithRatNum; i++ )
    {
        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstBcchPlmnIdWithRat->stPlmnId,
                                                            &pstSimPlmnWithRatList[i].stPlmnId))
          && (usBcchPlmnSimRat == (pstSimPlmnWithRatList[i].usSimRat & usBcchPlmnSimRat)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnIdWithRatWithUplmn
 ��������  : �ж�PLMN�����뼼���Ƿ���UPLMN
 �������  : pstPlmnIdWithRat:��Ҫ�Ƚϵ�PLMNID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��uplmn��ͬ
             VOS_FALSE - ��uplmn��ͬ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithUplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList  = VOS_NULL_PTR;

    /* ��ȡUOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        if (VOS_TRUE == NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList(pstPlmnIdWithRat,
                                                      pstUserPlmnList->ucUserPlmnNum,
                                                      pstUserPlmnList->astUserPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN��ʹ��PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&pstPlmnIdWithRat->stPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnIdWithRatWithOplmn
 ��������  : �жϴ����뼼����PLMN�Ƿ���OPLMN
 �������  : pstPlmnId:��Ҫ�Ƚϵ�PLMNID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��02��21��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithOplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList  = VOS_NULL_PTR;

    /* ��ȡUOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        if (VOS_TRUE == NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList(pstPlmnIdWithRat,
                                                      pstOperPlmnList->usOperPlmnNum,
                                                      pstOperPlmnList->astOperPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN��ʹ��PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&pstPlmnIdWithRat->stPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList
 ��������  : �ж�PLMN ID�Ƿ���NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU��ʽ�����б���
 �������  : pstSrcPlmnId:��Ҫ�жϵ�PLMN ID
             usSimRat    :���뼼��
             ulDestPlmnNum:�б���plmn id�ĸ���
             pstDestPlmnIdList:plmn�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID���б���
             VOS_FALSE : PLMN ID�����б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��11��8��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    VOS_UINT16                                              usSimRat,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < ulDestPlmnNum; i++)
    {
        if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
         && ((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)  == usSimRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertSimRatToNetRat
 ��������  : ��SIM����RAT����ת��Ϊ����RAT���ͣ����sim��rat�����ж�������뼼�����ȼ����ص�һ��
 �������  : usSimRat - sim ��rat
 �������  : ��
 �� �� ֵ  : enPlmnNetRat - ת����net rat
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MMC_ConvertSimRatToNetRat(
    VOS_UINT16                          usSimRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrio = VOS_NULL_PTR;
    VOS_UINT16                          usConvertedSimRat;
    VOS_UINT32                          i;

    pstRatPrio = NAS_MML_GetMsPrioRatList();

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        usConvertedSimRat = NAS_MMC_ConvertNetRatToSimRat(pstRatPrio->aucRatPrio[i]);

        if (usConvertedSimRat == (usConvertedSimRat & usSimRat))
        {
            return pstRatPrio->aucRatPrio[i];
        }
    }

    return NAS_MML_NET_RAT_TYPE_BUTT;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNetRatContainedInSimRat
 ��������  : �ж�SimRat�Ƿ������ǰSpecRat
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNetRatContainedInSimRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT16                          usSimRat
)
{
    VOS_UINT16                          usConvertedSimRat;

    usConvertedSimRat = NAS_MMC_ConvertNetRatToSimRat(enRat);

    if (usConvertedSimRat == (usConvertedSimRat & usSimRat))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList
 ��������  : �жϴ����뼼����PLMN ID�Ƿ���NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU��ʽ�����б���
 �������  : pstSrcPlmnId:��Ҫ�жϵ�PLMN ID
             ulDestPlmnNum:�б���plmn id�ĸ���
             pstDestPlmnIdList:plmn�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID���б���
             VOS_FALSE : PLMN ID�����б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2014��10��30��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usSrcPlmnSimRat;

    for ( i = 0; i < ulDestPlmnNum; i++ )
    {
        usSrcPlmnSimRat = NAS_MMC_ConvertNetRatToSimRat(pstSrcPlmnId->enRat);

        if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
         && (usSrcPlmnSimRat == (usSrcPlmnSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}






/*****************************************************************************
 �� �� ��  : NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly
 ��������  : IMS���ش�ʱ��voice domain��ɷ�cs onlyʱ��Enable LTE�Ƿ���Ҫ��������
 �������  :
 �� �� ֵ  : VOS_TRUE  : ��Ҫ����
             VOS_FALSE : ����Ҫ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��02��12��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    pstPrioRatList      = NAS_MML_GetMsPrioRatList();
    enFsmId             = NAS_MMC_GetCurrFsmId();

    /* ��߽��뼼�����ȼ�����LTE������Ҫ���� */
    if ((NAS_MML_NET_RAT_TYPE_LTE != pstPrioRatList->aucRatPrio[0]))
    {
        return VOS_FALSE;
    }

    /* ���CSҵ����ڲ���Ҫ���� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        return VOS_FALSE;
    }

    /* ON PLMN״̬��ʱ��Ҫ���� */
    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
     && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnValid
 ��������  : �ж�PLMN�Ƿ���Ч
 �������  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 �������  : ��
 �� �� ֵ  : VOS_FALSE/VOS_TRUE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_BOOL NAS_MMC_IsPlmnValid(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT32                          i;

    for (i=0; i<3; i++)
    {
        if ((((pstPlmnId->ulMcc >> (i*4)) & 0x0F) > 9)
         || ((((pstPlmnId->ulMnc >> (i*4)) & 0x0F) > 9) && (i != 2 ))
         || ((((pstPlmnId->ulMnc >> (i*4)) & 0x0F) > 9) && (((pstPlmnId->ulMnc >> (i*4)) & 0x0F) != 0x0F)))
        {
            /* PLMN ID?? */
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PlmnId2Bcd
 ��������  : ��PLMNת��ΪBCD��
 �������  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_VOID NAS_MMC_PlmnId2Bcd(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT8                           ucI;
    VOS_UINT32                          ulTmp;
    VOS_UINT8                           aucTmp[4];

    ulTmp            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;
    for (ucI = 0 ;ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }
    pstPlmnId->ulMcc = ((VOS_UINT32)aucTmp[0] << 8)
                      |((VOS_UINT32)aucTmp[1] << 4)
                      | aucTmp[2];

    ulTmp            = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }

    if (0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 4)
                          |((VOS_UINT32)aucTmp[1] )
                          |0xf00;
    }
    else
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 8)
                          |((VOS_UINT32)aucTmp[1] << 4)
                          | aucTmp[2];
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PlmnId2Bcd
 ��������  : ��PLMNת��ΪNasStyle��ʽ����
 �������  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_VOID NAS_MMC_PlmnId2NasStyle(NAS_MSCC_PIF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT8   aucTmp[4];
    VOS_UINT32  ulTmp;

    ulTmp           = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc  = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    ulTmp           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }

    if (0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUpdateFileForPrefPlmn
 ��������  : ����Pref PLMN�Ĳ���,ȷ����ǰҪ���µ��ļ�
 �������  : ��Ҫ���µ�USIM�ļ�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetUpdateFileForPrefPlmn(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                          usUpdateFile;
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType       = NAS_MML_GetSimType();
    usUpdateFile    = 0;

    if (NAS_MSCC_UPLMN_INFO == enPrefPLMNType)
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFPLMNWACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else if (NAS_MSCC_PLMNSEL_INFO == enPrefPLMNType)
    {
        usUpdateFile = USIMM_GSM_EFPLMNSEL_ID;
    }
    else if (NAS_MSCC_OPLMN_INFO == enPrefPLMNType)
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFOPLMNWACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFOPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFHPLMNwACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFHPLMNACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }

    return usUpdateFile;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitAsResumeIndTimerLen
 ��������  : ��ȡResume ind ��ʱ��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���:������޸����������֮��Ķ�ʱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitAsResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_WAIT_AS_RESUME_IND_LEN;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen
 ��������  : ��ȡGUT������ض���Resume ind ��ʱ��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���:������޸����������֮��Ķ�ʱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetWaitAsOosResumeIndTimerLen
 ��������  : ��ȡ�����OOS��Resume ind ��ʱ��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���:������޸����������֮��Ķ�ʱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetWaitAsOosResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN;
}




#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsDetachReqestDisableLte
 ��������  : check detach�����Ƿ���Ҫdisable LTE
 �������  : pstDetachReq -- detach����
 �� �� ֵ  : VOS_TRUE  -- ��Ҫdisable LTE
             VOS_FALSE -- ����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��16��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDetachReqestDisableLte(
    NAS_MMC_DETACH_TYPE_ENUM_UINT32     enDetachType,
    NAS_MMC_DETACH_REASON_ENUM_UINT32   enDetachReason
)
{
    if (((NAS_MSCC_PIF_DETACH_REASON_USER_DETACH       == enDetachReason)
      || (NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH == enDetachReason))
     && (NAS_MSCC_PIF_DETACH_TYPE_GPRS            == enDetachType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd
 ��������  : ����GU��RRMM_AREA_LOST�����б���Ϣ
 �������  : RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
)
{
    RRC_PLMN_ID_LIST_STRU                                  *pstGuPlmnIdList = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_TYPE_STRU                              stNasSearchedType;

    pstGuPlmnIdList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd:ERROR: Memory Alloc Error");
        return;
    }

    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstAreaLostInd->stPlmnIdList),
                                           pstGuPlmnIdList);

    /* ����area lost��Ϣ��������������ͺ͸ߵ�����plmn�����ڲ�ѡ����Ϣ */
    NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, pstGuPlmnIdList, pstPlmnListInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    return;
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd
 ��������  : ����GU��RRMM_AREA_LOST�����б���Ϣ
 �������  : RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
)
{
    NAS_MMC_SEARCHED_TYPE_STRU                              stNasSearchedType;

    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

    /* ����area lost��Ϣ��������������ͺ͸ߵ�����plmn�����ڲ�ѡ����Ϣ */
    NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, &(pstAreaLostInd->PlmnIdList), pstPlmnListInfo);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsOosPlmnSearchScene
 ��������  : �Ƿ�ΪOOS��������
 �������  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsOosPlmnSearchScene(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    VOS_UINT8                                               ulRslt;

    switch(enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED:
        case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH:
        case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH:

            ulRslt = VOS_TRUE;
            break;

        default:

            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsHistorySearchSupportInCurrPhase
 ��������  : ��ǰ�׶�history�Ƿ�֧��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��5��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsHistorySearchSupportInCurrPhase(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_STRATEGY_INFO_STRU             *pstOosPlmnSearchInfo    = VOS_NULL_PTR;
    NAS_MMC_OOS_PHASE_ENUM_UINT8                            enPhaseNum;
    VOS_UINT8                                               ucRslt;

    pstOosPlmnSearchInfo    = NAS_MMC_GetOosPlmnSearchStrategyInfo();
    enPhaseNum              = NAS_MMC_GetCurrOosSearchPhaseNum();
    ucRslt                  = VOS_FALSE;

    switch (enPhaseNum)
    {
        case NAS_MMC_OOS_PHASE_ONE:
            if (0 != pstOosPlmnSearchInfo->stPhaseOnePatternCfg.ucHistoryNum)
            {
                ucRslt = VOS_TRUE;
            }
            break;

        case NAS_MMC_OOS_PHASE_TWO:
            if (0 != pstOosPlmnSearchInfo->stPhaseTwoPatternCfg.ucHistoryNum)
            {
                ucRslt = VOS_TRUE;
            }
            break;

        default:
            ucRslt = VOS_FALSE;
            break;
    }

    return ucRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo
 ��������  : ��MSCCPLMN�����б�ת��ΪMMC��ʽ��PLMN�б���Ϣ
 �������  : ulMsccPlmnNum
             enRat
             pstMsccPlmnList
 �������  : pstMmcPlmnListInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��3��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��6��1��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 12:�޸Ľӿ�

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstMmcPlmnListInfo
)
{
    VOS_UINT32                          i;

    if (VOS_NULL_PTR == pstHighPrioPlmnInfo)
    {
        return;
    }

    pstMmcPlmnListInfo[0].enRatType     = pstHighPrioPlmnInfo->enRat;
    pstMmcPlmnListInfo[0].enCoverType   = NAS_MMC_COVERAGE_TYPE_HIGH;

    pstMmcPlmnListInfo[0].ulHighPlmnNum = pstHighPrioPlmnInfo->ucHighPlmnNum;
    if (pstMmcPlmnListInfo[0].ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstMmcPlmnListInfo[0].ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    for (i = 0; i < (pstMmcPlmnListInfo[0].ulHighPlmnNum); i++)
    {
        pstMmcPlmnListInfo[0].astHighPlmnList[i].ulMcc = pstHighPrioPlmnInfo->astHighPlmnID[i].ulMcc;

        pstMmcPlmnListInfo[0].astHighPlmnList[i].ulMnc = pstHighPrioPlmnInfo->astHighPlmnID[i].ulMnc;
    }

    pstMmcPlmnListInfo[0].ulLowPlmnNum  = pstHighPrioPlmnInfo->ucLowPlmnNum;
    if (pstMmcPlmnListInfo[0].ulLowPlmnNum > NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
    {
        pstMmcPlmnListInfo[0].ulHighPlmnNum = NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM;
    }

    for (i = 0; i < (pstMmcPlmnListInfo[0].ulLowPlmnNum); i++)
    {
        pstMmcPlmnListInfo[0].astLowPlmnList[i].stPlmnId.ulMcc = pstHighPrioPlmnInfo->astLowPlmnID[i].ulMcc;

        pstMmcPlmnListInfo[0].astLowPlmnList[i].stPlmnId.ulMnc = pstHighPrioPlmnInfo->astLowPlmnID[i].ulMnc;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq
 ��������  : ��MSCCģ���plmn search������Ϣ�л����������
 �������  : pstRegReq
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSrchReq
)
{
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
    }

    if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH;
    }

    if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
    }

    return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType
 ��������  : ��MSCC��������RAT����ת��ΪMML��3GPP2�����͸�ʽ
 �������  : enMsccRatType          MSCC��������RAT����
 �������  : *penMml3GPP2RatType    MML�����3GPP2����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��9��
   ��    ��   : w00176964
   �޸�����   : �½�����
*****************************************************************************/
VOS_VOID   NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMsccRatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8                      *penMml3GPP2RatType
)
{
    switch (enMsccRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_1X:

            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_CDMA1X;
            break;

        case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:

            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_HRPD;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType TYPE ERROR!!!");
            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsRatPrioChangeTriggerPlmnSrch
 ��������  : �жϽ��뼼�����ȼ��仯�Ƿ���Ҫ��������ȼ�����
 �������  : pstOldRatList --�ɵĽ��뼼���б�
             pstNewRatList --�µĽ��뼼���б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ�����ȼ�����
              VOS_FALSE:����Ҫ�����ȼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��15��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��8��6��
   ��    ��   : c00318887
   �޸�����   : DTS2015041401965��syscfg����ֻ�����ӽ��뼼�����������뼼�����ȼ����ڵ�ǰ���뼼���Ŵ�������
                ����: 4g -> 2g 4g(��ǰפ��4g������2g��2g���뼼�����ȼ�0 ���� 4g ���뼼�����ȼ� 1����������)
                ����: 4g -> 4g 2g(��ǰפ��4g������2g��2g���뼼�����ȼ�1 ���� 4g ���뼼�����ȼ� 0������������)
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsRatPrioChangeTriggerPlmnSrch(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstNewRatList
)
{
    VOS_UINT32                               ulCurrRatIndex;                         /* ��ǰ���뼼�������ȼ����б��index,0��ߣ�2��� */
    VOS_UINT8                                ucNewRatNum;                            /* �������뼼������  */
    VOS_UINT8                                ucOldRatNum;                            /* ԭ�н��뼼������  */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstNewRatPrio = VOS_NULL_PTR;           /* �����������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstOldRatPrio = VOS_NULL_PTR;           /* ԭ�н������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8          enCurrRat;
    VOS_UINT8                                ucOldRatIndex;
    VOS_UINT8                                ucNewRatIndex;


    /* ȡ�������������ȸ��� */
    ucNewRatNum        = pstNewRatList->ucRatNum;

    /* ȡ�������������ȼ��б� */
    pstNewRatPrio      = pstNewRatList->aucRatPrio;


    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat          = NAS_MML_GetCurrNetRatType();

    /* ȡ��ԭ�еĽ������ȸ��� */
    ucOldRatNum        = pstOldRatList->ucRatNum;

    /* ȡ��ԭ�еĽ������ȼ��б� */
    pstOldRatPrio      = pstOldRatList->aucRatPrio;

    if ( (0 == ucNewRatNum)
      || (0 == ucOldRatNum) )
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼�����µ����ȼ��б����index, 0��ߣ�2���  */
    ulCurrRatIndex = NAS_MML_GetRatIndexInPrioRatList(enCurrRat, pstNewRatList);

    /* ��ǰ���뼼�����µ����ȼ��б���û�У�����true */
    if (NAS_MML_INVALID_INDEX == ulCurrRatIndex)
    {
        return VOS_TRUE;
    }

    /* ��������:1��SysSet�������˽��뼼�� */
    /*          2�������Ľ��뼼�����ȼ����ڵ�ǰפ�����뼼�� */
    for (ucNewRatIndex = 0; ucNewRatIndex < ucNewRatNum; ucNewRatIndex++)
    {
        for (ucOldRatIndex = 0; ucOldRatIndex < ucOldRatNum; ucOldRatIndex++)
        {
            if (pstNewRatPrio[ucNewRatIndex] == pstOldRatPrio[ucOldRatIndex])
            {
                /* SysSet��ĳ�����뼼���ڵ�ǰ���뼼���� */
                break;
            }
        }

        /* ��ԭ�н��뼼���б��У������ڣ���ʾ��������  */
        if (ucOldRatIndex == ucOldRatNum)
        {
            /* ���ж��������뼼���ڽ��뼼���б�������� �Ƿ�С�� ��ǰ���뼼���ڽ��뼼���б�������� */
            if ((VOS_UINT32)ucNewRatIndex < ulCurrRatIndex)
            {
                return VOS_TRUE;
            }
        }

    }


    /* Ĭ�ϲ���Ҫ���и����ȼ��б����� */
    return VOS_FALSE;
}


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_StartPlmnSearchPhaseOneTotalTimer
 ��������  : ��������������һ�׶�������ʱ����ƶ�ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE: TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER �����ɹ�
             VOS_FALSE: TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : c00318887
    �޸�����   : �½�
  2.��    ��   : 2015��10��21��
    ��    ��   : h00281185
    �޸�����   : �ܹ����� pstPhaseOneOosPlmnSearchPatternInfo, ȡ�� pstAvailTimerCfg/pstHistoryinfo
*****************************************************************************/
VOS_UINT32 NAS_MMC_StartPlmnSearchPhaseOneTotalTimer(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;


    pstPhaseOneOosPlmnSearchPatternInfo                    = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer entered.");

    /* ����Ѿ��������ڶ��׶Σ������� */
    if (NAS_MMC_OOS_PHASE_ONE != NAS_MMC_GetOosPhaseNum())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer WANRING: UE is in plmn search phaseII");

        return VOS_FALSE;
    }

    /* no rf �������� */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: no rf");

        return VOS_FALSE;
    }

    /* Timer Length Ϊ0, ��ʾ�������� ��ʱ�� */
    if (0 == pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen = 0, not start");

        return VOS_FALSE;
    }

     /* ��һ�׶���ʱ�� С�� ��һ�׶���С˯��ʱ���������� */
    if ( pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen < pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen)
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: PhaseOneTotalTimeLen=%d, historyFirstTimerLen=%d",
                        pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen, pstPhaseOneOosPlmnSearchPatternInfo->usSleepTimerLen);

        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER,
                                       (pstPhaseOneOosPlmnSearchPatternInfo->usTotalTimerLen) * NAS_MML_ONE_THOUSAND_MILLISECOND))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer START SUCC.");
        return VOS_TRUE;
    }

    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:info: START TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER IS FALSE");

    return VOS_FALSE;
}
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertRatTypeFromNasMsccToNasErr
 ��������  : ��NAS_MSCC�����RatTypeת��ΪNas_Err�����RatTypeֵ,��ΪNas_Err��δ֧��1X&HRPD
 �������  : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : NAS_ERR_LOG_RATMODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : h00279575
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_ERR_LOG_RATMODE_ENUM_UINT8 NAS_MMC_ConvertRatTypeFromNasMsccToNasErr (
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 msccRatType
)
{
    NAS_ERR_LOG_RATMODE_ENUM_UINT8 errRatType;
    switch (msccRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:           /* GSM���뼼�� */
            errRatType = NAS_ERR_LOG_RATMODE_GSM;
            break;
        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:         /* WCDMA���뼼�� */
            errRatType = NAS_ERR_LOG_RATMODE_WCDMA;
            break;
        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:           /* LTE���뼼�� */
            errRatType = NAS_ERR_LOG_RATMODE_LTE;
            break;
        default:
            NAS_TRACE_HIGH("NAS_MMC_ConvertRatTypeFromNasMsccToNasErr: Convert rat(%d) to BUTT", msccRatType);
            errRatType = NAS_ERR_LOG_RATMODE_BUTT;
            break;
    }

    return errRatType;
}
#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RecordFftSrchMccInfo
 ��������  : ��FFT����MCC�Ľ��д��CHR����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : h00279575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RecordFftSrchMccInfo( VOS_VOID )
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU          *pstGeoSrchInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU     stProcInfoEvent;
    VOS_UINT32                                  ulIsLogNeedRecord;
    VOS_UINT32                                  ulLength;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel             = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO);
    ulIsLogNeedRecord   = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* NV���ò���Ҫ��¼ */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RecordFftSrchMccInfo,ERROR:log nv disable or low level");
        return;
    }

    NAS_TRACE_HIGH("NAS_MMC_RecordFftSrchMccInfo(): recording ");

    ulLength = sizeof(NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU);

    /* ��䱾�ؼ�¼��Ϣ */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    pstGeoSrchInfo = NAS_MML_GetErrLogFftSrchInfoAddr();
    stProcInfoEvent.ulSrchStartSlice  = pstGeoSrchInfo->ulSrchStartSlice;
    stProcInfoEvent.ulSrchFinishSlice = pstGeoSrchInfo->ulSrchFinishSlice;

    /* ת��GetGeo������MCC������ɹ�����ʧ�ܣ��Լ�ʧ�ܵ�ԭ�� */
    if (NAS_MMC_GET_GEO_SUCCESS == pstGeoSrchInfo->ucSrchRslt)
    {
        stProcInfoEvent.ucSrchRslt  = VOS_TRUE;
        stProcInfoEvent.ucFailCause = 0;

        /* ת��MCC�Ľ��뼼����ʽ */
        stProcInfoEvent.enMccRatType = NAS_MMC_ConvertRatTypeFromNasMsccToNasErr(pstGeoSrchInfo->enMccRatType);

    }
    else
    {
        stProcInfoEvent.ucSrchRslt   = VOS_FALSE;
        stProcInfoEvent.ucFailCause  = pstGeoSrchInfo->ucSrchRslt;

        /* δ�ҵ�MCC����ʼ����ǰ��ʽΪĬ��ֵ */
        stProcInfoEvent.enMccRatType = NAS_ERR_LOG_RATMODE_BUTT;
    }


    /* ��¼CSS Multi Band Scan�Ľ�� */
    stProcInfoEvent.stMultiBandScanInfo.ucResult                = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enResult;
    stProcInfoEvent.stMultiBandScanInfo.ulBandScanStartSlice    = pstGeoSrchInfo->stCssBandScanInfo.ulBandScanStartSlice;
    stProcInfoEvent.stMultiBandScanInfo.ulBandScanFinishSlice   = pstGeoSrchInfo->stCssBandScanInfo.ulBandScanFinishSlice;
    stProcInfoEvent.stMultiBandScanInfo.ucGsmCoverageType       = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enGsmCoverageType;
    stProcInfoEvent.stMultiBandScanInfo.ucLteCoverageType       = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enLteCoverageType;
    stProcInfoEvent.stMultiBandScanInfo.ucUmtsFddCoverageType   = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enUmtsFddCoverageType;

    /* ��յ�FFT����MCCȫ�ֱ�����Ϣ */
    NAS_MML_InitErrLogFftSrchInfo();

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RecordFftSrchMccInfo(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}
#endif
/*****************************************************************************
 �� �� ��  : NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej
 ��������  : ��hplmn��ע�ᱻ��ʱ����Ҫ�޸�ת����ϵͳ��Ϣ�е�forbidden flag.
 �������  : ulInForbiddenFlg       -- ����� forbidden flag
             ulUserSrchFlg          -- �Ƿ��ֶ�ģʽ
             enRat                  -- ���뼰ʱ
             enRegCnDomain          -- PS /cs ��
 �������  : ��
 �� �� ֵ  : ulOutForbiddenFlg      -- �޸ĺ��forbidden flag
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : c00318887
    �޸�����   : DTS2015061609864
*****************************************************************************/
VOS_UINT32  NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
    VOS_UINT32                          ulInForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegCnDomain
)
{
    VOS_UINT32                          ulOutForbiddenFlg;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;

    ulOutForbiddenFlg                   = ulInForbiddenFlg;

    /* �ֶ���ģʽ���޸� */
    if (VOS_TRUE == ulUserSrchFlg)
    {      
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, 
                        "NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej: ulUserSrchFlg = ",
                        ulUserSrchFlg);
        return ulOutForbiddenFlg;
    }

    ucHplmnRegisterCtrlFlg              = NAS_MML_GetHplmnRegisterCtrlFlg();

    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            enRat,
                                            &enCsRegCause,
                                            &enPsRegCause);

    NAS_NORMAL_LOG3(WUEPS_PID_MMC, 
                    "NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej: ucHplmnRegisterCtrlFlg, enCsRegCause and enPsRegCause ",
                    ucHplmnRegisterCtrlFlg,
                    enCsRegCause,
                    enPsRegCause);

    if (VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(enRegCnDomain))
    {
        if (MMCMM_NO_FORBIDDEN == ulInForbiddenFlg)
        {
            ulOutForbiddenFlg           = MMCMM_FORBIDDEN_PLMN;
        }

        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
          && (VOS_TRUE                   == ucHplmnRegisterCtrlFlg))
        {
            ulOutForbiddenFlg           &= (~MMCMM_FORBIDDEN_PLMN);
        }
    }

    if (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN == enPsRegCause)
    {
        /* ��Hplmn��PSע�ᱻ#14�ܺ󣬷�E5ʱ�����ٷ���PS attach, E5ʱ������ѭ������PS attach */
        if (MMCMM_NO_FORBIDDEN == ulInForbiddenFlg)
        {
            ulOutForbiddenFlg           |= MMCMM_FORBIDDEN_PLMN_FOR_GPRS;
        }

        if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
          && (VOS_TRUE                   == ucHplmnRegisterCtrlFlg))
        {
            ulOutForbiddenFlg           &= (~MMCMM_FORBIDDEN_PLMN_FOR_GPRS);
        }
    }

    return ulOutForbiddenFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMmssLteUnavailableReasonByDetachReason
 ��������  : ͨ��detachԭ���ȡLTE�����õ�ԭ��
 �������  : enDetachReason---detach ԭ��ֵ
 �������  : ��
 �� �� ֵ  : MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8 NAS_MMC_GetMmssLteUnavailableReasonByDetachReason (
    NAS_MMC_DETACH_REASON_ENUM_UINT32   enDetachReason
)
{
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8          enReason;

    switch (enDetachReason)
    {
        case NAS_MSCC_PIF_DETACH_REASON_USER_DETACH:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_USER_DETACH;
            break;

        case NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_RAT_OR_BAND_DETACH;
            break;

        case NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SRV_DOMAIN_DETACH;
            break;

        default:
            enReason = MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_BUTT;
            break;
    }

    return enReason;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertToMmlSessionType
 ��������  : ��MMC��Session type ת��MML������
 �������  :
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��27��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertToMmlSessionType(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8   enMmSessionType,
    NAS_MML_SESSION_TYPE_ENUM_UINT8  *penMmlSessionType
)
{
    switch(enMmSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_CS_MO_SMS;
            break;

        default:
            *penMmlSessionType = NAS_MML_SESSION_TYPE_BUTT;
            break;
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



