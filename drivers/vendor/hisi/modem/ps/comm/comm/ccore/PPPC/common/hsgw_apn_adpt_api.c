/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hsgw_apn_adpt_api.c
  �� �� ��   : ����
  ��    ��   : honglei 50774
  ��������   : 2013��5��17��
  ����޸�   :
  ��������   : HSGW��ƷAPN/DOMAIN����ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��17��
    ��    ��   : honglei 50774
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "srv_common_inc.h"

#include "am_public.h"
#include "apn_adpt_api.h"
#include "a11_spu_sru_pub.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

S_CFG_DOMAINNODE *g_pstApnByIndex = NULL;
extern VOS_UINT32 A11_GetDomainByIndex( VOS_UINT16 usAPNIndex, S_CFG_DOMAINNODE **pstAPN);
extern VOS_UINT32 USM_GetApnCfgByApnIndex(VOS_UINT16 usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetL2tpGroup
 ��������  : APN��L2TP group����
 �������  : VOS_UINT16 usApnIdx
 �������  : VOS_UINT16 *pusL2tpGroup
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetL2tpGroup(VOS_UINT16 usApnIdx, VOS_UINT16 *pusL2tpGroup)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    VOS_UINT32 ulRet = VOS_OK;

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* δʹ��L2TP */
    if (VOS_TRUE != pstDomain->ucL2tp)
    {
        return VOS_ERR;
    }

    *pusL2tpGroup = pstDomain->usGroupNum;
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetApnIdx
 ��������  : ����APN�ṹ����APN��������Ҫ���ڸ����APN�ص�����
 �������  : UCHAR *pucApnInfo
 �������  : VOS_UINT16 *pusApnIdx
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnIdx(UCHAR *pucApnInfo, VOS_UINT16 *pusApnIdx)
{
    S_CFG_DOMAINNODE *pstDomain = (S_CFG_DOMAINNODE*)pucApnInfo;

    if (VOS_NULL == pstDomain)
    {
        return VOS_ERR;
    }

    *pusApnIdx = pstDomain->usApnIndex;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetApnIdxByName
 ��������  : ����APN������APN������ע��ýӿ�Ч�ʽϵͣ������ʹ��!
 �������  : UCHAR *pucApnInfo
 �������  : VOS_UINT16 *pusApnIdx
 �� �� ֵ  : APN/Domain����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnIdxByName(UCHAR *pucApnName, VOS_UINT16 *pusApnIdx)
{
    VOS_UINT32 ulRet = VOS_OK;
    S_CFG_CDB_CONDITION sCondition = {0};
    S_CFG_DOMAINNODE tmpApn = {0};

    if ((NULL == pusApnIdx) || (NULL == pucApnName))
    {
        return VOS_ERR;
    }

    sCondition.ucOper = M_CFG_CDB_EQUAL;
    sCondition.udwFieldId = M_HSGW_APN_COMMOM_TBL_APN_FLD_ID;

    VOS_StrCpy((CHAR*)sCondition.aValue, (CHAR*)pucApnName);

    /*  ��ѯCDB �е�APN��Ϣ���ñ� */
    ulRet = DBApiQuerySingle(M_HSGW_APN_COMMOM_TBL_ID, 1, &sCondition, (CHAR *)&tmpApn);
    if (ulRet == CDB_EC_SUCCESS)
    {
        *pusApnIdx = tmpApn.usApnIndex;
        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 �� �� ��  : AM_ApnApiGetApnIdxByName
 ��������  : ����CDB��APN�������ݣ���ȡAPN������RadiusGroupID
 �������  : UCHAR *pucApnInfo
 �������  : VOS_UINT16 *pusApnIdx
             VOS_UINT16 *pusServerGroupID
 �� �� ֵ  : APN/Domain����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 AM_ApnApiGetRadiusInfo(UCHAR *pucApnNodeAddr, VOS_UINT16 *pusApnIdx, VOS_UINT16 *pusServerGroupID)
{
    S_CFG_DOMAINNODE *pstApn = (S_CFG_DOMAINNODE*)pucApnNodeAddr;

    if ((NULL == pstApn) || (NULL == pusApnIdx) || (NULL == pusServerGroupID))
    {
        return VOS_ERR;
    }

    *pusApnIdx = pstApn->usApnIndex;
    *pusServerGroupID = pstApn->usServerGroupID;
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AM_ApnApiGetAcctInfo
 ��������  : ����APN/Domain������ȡ�Ʒ���Ϣ
 �������  : VOS_UINT16 usApnIdx
 �������  : APN_ACCT_INFO *pstAcctInfo
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetAcctInfo(VOS_UINT16 usApnIdx, APN_ACCT_INFO *pstAcctInfo)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    VOS_UINT32 ulRet = VOS_OK;

    if (NULL == pstAcctInfo)
    {
        return VOS_ERR;
    }

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    pstAcctInfo->pucAPN         = &pstDomain->aucAPN[0];
    pstAcctInfo->ucTransAccess  = pstDomain->ucTransAccess;
    pstAcctInfo->usServerGroupID = pstDomain->usServerGroupID;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetAcctInfo
 ��������  : ����APN/Domain������ȡ�Ʒ�����
 �������  : VOS_UINT16 usApnIdx
 �������  : APN_CM_TYPE_S *pstApnType
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetCmApnType(VOS_UINT16 usApnIdx, APN_CM_TYPE_S *pstApnType)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetAcctInfo
 ��������  : ����APN/Domain������ȡIdle����
 �������  : VOS_UINT16 usApnIdx
 �������  : UCHAR *pucIdleSwitch
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetIdleSwitch(VOS_UINT16 usApnIdx, UCHAR *pucIdleSwitch, UCHAR *pucUpdateSwitch)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetApnName
 ��������  : ����APN/Domain������ȡIdle����
 �������  : VOS_UINT16 usApnIdx
 �������  :
 �� �� ֵ  : APN/DOMAIN������������ʱ����NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
UCHAR* AM_ApnApiGetApnName(VOS_UINT16 usApnIdx)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    VOS_UINT32 ulRet = VOS_OK;

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_NULL;
    }

    return &pstDomain->aucAPN[0];
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetAliasApnName
 ��������  : ��ȡ����APN/Domain����
 �������  : VOS_UINT16 usApnIdx
 �������  :
 �� �� ֵ  : APN/DOMAIN������������ʱ����NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : h50774
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetAliasApnName(VOS_UINT16 usAliasApnIdx, UCHAR *pucAliasApnName)
{
    UCHAR *pucApnName = NULL;

    pucApnName = AM_ApnApiGetApnName(usAliasApnIdx);

    if (NULL != pucApnName)
    {
        VOS_StrNCpy(pucAliasApnName, pucApnName, M_CFG_MAX_APN_STRING_LEN - 1);
        pucAliasApnName[M_CFG_MAX_APN_STRING_LEN - 1] = '\0';
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetMultiServiceMod
 ��������  : ��ȡAPN���õ�MultiServiceMod
 �������  : VOS_UINT16 usApnIdx
 �������  : pucMultiServiceMod
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��22��
    ��    ��   : Z66908
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetMultiServiceMod(VOS_UINT16 usApnIdx, UCHAR *pucMultiServiceMod)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AM_ApnApiGetApnNameForHsgw
 ��������  : hsgw ����apn index ��ȡapn name
 �������  : VOS_UINT16 usApnIndex
             UCHAR *pucApnName
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��28��
    ��    ��   : y00138047
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnNameForHsgw(VOS_UINT16 usApnIndex, UCHAR *pucApnName)
{
    VOS_UINT32 ulRet = VOS_OK;
    HSGW_APN_INFO_S *pstApn = VOS_NULL;

    if ( NULL == pucApnName )
    {
        return VOS_ERR;
    }

    ulRet = USM_GetApnCfgByApnIndex(usApnIndex, &pstApn);
    if ( VOS_OK != ulRet )
    {
        return ulRet;
    }

    VOS_StrCpy(pucApnName, pstApn->aucApnInfoName);
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : AM_ApnApiGetApnSoftParaVaule
 ��������  : ����APN�����������ȡ���ֵ
 �������  : APN������usAPNIndex, ucSoftParaIndex(1-8)
 �������  : ���ֵ�� *pucSoftParaValue
 �� �� ֵ  : VOS_OK���ɹ� VOS_ERR��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��6��
    ��    ��   : xuchao 00249899
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 AM_ApnApiGetApnSoftParaVaule(VOS_UINT16 usAPNIndex , UCHAR ucSoftParaIndex, UCHAR *pucSoftParaValue)
{
    if ((NULL == g_pstApnByIndex) || (NULL == pucSoftParaValue))
    {
        VOS_ASSERT(0);
        return VOS_ERR;
    }

    *pucSoftParaValue = 0;
    return VOS_OK;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
