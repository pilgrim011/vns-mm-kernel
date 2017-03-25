/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Aps_DealApiParaMsg.c
  Author       : ��³��
  Version      : V200R001
  Date         : 2005-0
  Description  : ��FLASH�����ݱ�Ĵ���������д�޸�
  Function List:
        ---Aps_DefPsPdpContext()
        ---Aps_ChngPdpPri
        ---Aps_DefPdpPri
        ---Aps_DefPsPdpAuth
        ---Aps_ChngAuth

        ---Aps_DefPsSecPdpContext
        ---Aps_ChngSecPara
        ---Aps_DefSecPara
        ---Aps_DefPsTft
        ---Aps_ChngTft

        ---Aps_JudgeTftItemCombin
        ---Aps_DefPs3gReqQos
        ---Aps_ChngQos
        ---Aps_DefQos
        ---Aps_DefPs3gMinAcceptQos

        ---Aps_ChngMinQos
        ---Aps_DefMinQos
        ---Aps_DbQuery
        ---Aps_DbQueryButt
        ---Aps_QuePri

        ---Aps_QueSec
        ---Aps_QueTft
        ---Aps_QueState
        ---Aps_NvimAct
        ---Aps_JudegNvimActType

  History      :
  1. Date:2005-0
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by ��³�� FOR A32D02144
  3. 2006-03-03 MODIFY BY H41410 FOR A32D02345
  4. 2006-04-14 modify by h41410 for A32D03182
  5. 2006-10-23 modify by L47619 for A32D06872
  6.��    �� : 2006-12-07
    ��    �� : ��³��
    �޸����� : A32D07824 ����CGEQNEG�Ĵ���
  7.��    �� : 2007��09��26��
    ��    �� : l00107747
    �޸����� : ���ⵥ�ţ�A32D12931,��ѯAPI�ӿ����Ӵ������ϱ�
  8.��    ��   : 2009��5��20��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�AT2D11987,�޸�NV��ͷ�ļ�����PS/SYS/RF��NV���ֳ������Ա���ά��
  9.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: ɾ��Taf_DbPdpProc, Aps_DbQuery, Aps_DbQueryButt,
                 Aps_GetParaPointer
************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"

#include "TafLog.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsCtx.h"
#include "TafApsComFunc.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALAPIPARAMSG_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*�ݴ潫��������PDP���������������������PDP�����Ƚϣ��Ծ�����Ҫ��NVIM��
�����ݽ����������޸�*/
TAF_PDP_TABLE_STRU                      g_TmpPdpTab;


/*������ѯ�Ƿ�����ı�ʶ*/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 Prototype      : Aps_DefPsPdpContext()
 Description    : ���壬�޸ģ�ɾ��PDP CONTEXT.�������������ݽṹ�Ĳ���,FLASH��
                  PDP���ݱ��ȫ�ֱ������ݱ�.
 Input          : ClientId, ʶ��ĳ��Ӧ�ó���;
                  OpId, ʶ��ĳ��Ӧ�ó����е�ĳ�κ���;
                  pPara,ָ��PDP CONTEXT���ṹ��ָ��;
                        û��PDP CONTEXT���ṹ����IE����ʾɾ��PDP CONTEXT;
                        ��PDP CONTEXT���ṹ����IE����ʾ������޸�PDP CONTEXT��
                        �Ѿ�������PDP CONTEXT��Ϊ�޸ģ�����Ϊ���塣
 Output         : NO
 Return Value   :
 Calls          : VOS_UINT16 NV_Read();
                  VOS_UINT16 NV_Write();

 Called By      : TAFM
 Pseudocode     :
 History        : ---
  1.Date        : 2005-
    Author      : ��³��
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    ��   : 2012��01��02��
    ��    ��   : s46746
    �޸�����   : DTS2012010200121: cgdcont����ɾ������PDP������,cgdscont����
                 ɾ����PDP������,ֻ�ܶ�����PDP�Ѿ�����Ķ���������

  4.��    ��   : 2012��5��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012052404203: +CGDCONT�������Ӷ�<CID 0>��֧��
*****************************************************************************/
VOS_VOID Aps_DefPsPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    ulReturn                            = TAF_APS_SUCC;

    if ( ( VOS_NULL == pPara )
      || (!(TAF_PS_PDP_CONTEXT_CID_VALID(pPara->ucCid))) )
    {
        APS_WARN_LOG("Aps_DefPsPdpContext input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }


    /*����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab��*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];


    /*����pPara�ж��Ƿ���ɾ��PDP_PRI����*/
    if (VOS_FALSE == pPara->ucDefined)
    {
        /*ɾ��PDP_PRI����*/
        /*----------------------------------------------------------
           CID0��ɾ������Э����Ҫ��ָ��ض���Ĭ��ֵ, Ŀǰ��֧��,
           ͳһ����ERROR, �ο� TS 27.007 R11 section 10.1.0
        ----------------------------------------------------------*/
        if (0 == pPara->ucCid)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "Aps_DefPsPdpContext: Can't delete CID <0>");
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /*�����ն˵�Ҫ�������ָ��ɾ����CID������APS_PDP_INACTIVE״̬��
           ���ֹ��ɾ������*/
        if (TAF_TRUE == Taf_CheckActCid(pPara->ucCid))
        {
            APS_WARN_LOG("Aps_DefPsPdpContext: Can't delete the Context of \
                          the CID which is not in APS_PDP_INACTIVE state!");
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /*��������PDP_PRI���������Ѿ�����*/
        if ( VOS_TRUE == g_TmpPdpTab.ucUsed )
        {
            /* ��������PDP������Ƕ���PDP�����ģ�����ɾ�� */
            if (VOS_TRUE == g_TmpPdpTab.ucPriCidFlag)
            {
                *pulErrCode = TAF_PARA_SET_ERROR;
                return;
            }
            else
            {
                /*���PDP�Ķ����ʶ*/
                g_TafCidTab[pPara->ucCid].ucUsed        = VOS_FALSE;

                Aps_DeleteLinkedCidSecPdpContext(pPara->ucCid);
            }
        }
        else
        {
            /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {
        /*��������޸�PDP_PRI����*/
        ulReturn = Aps_ChngPdpPri( pPara, pPara->ucCid );
        if ( TAF_APS_FAIL == ulReturn )
        {
            /*����޸�ʧ��*/
            g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;

            APS_WARN_LOG("Aps_ChngPdpPri ERR!");
            *pulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
            return;
        }

        /*���ԭ���Ƕ���PDP������б�ʶ�����ͱ�Ҫ����������*/
        if (g_TafCidTab[pPara->ucCid].ucPriCidFlag)
        {
            g_TafCidTab[pPara->ucCid].ucPriCidFlag  = VOS_FALSE;
        }

        /*AT��APP����PdpPri����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣*/
        Aps_DefPdpPri( pPara, pPara->ucCid );

    }

    ulReturn = Aps_NvimAct( pPara->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {
        /*�����ɹ�*/
        *pulErrCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        APS_WARN_LOG("NVIM ACT ERR!");
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        return;
    }
}


/*****************************************************************************
 Prototype      : Aps_ChngPdpPri
 Description    : APP�޸�PdpPri����ʱ,�ô˺���������Ĳ�������PDP����.
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ��Э������������enImCnSignalFlg��enPcscfDiscovery

*****************************************************************************/
VOS_UINT32  Aps_ChngPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
)
{
    /*pPdpPriPara��ucCid �Ƿ�Ϊ�������������м�飬���ڴ˱��������м��*/

    if ( VOS_TRUE  == pPdpPriPara->bitOpPdpType )
    {
        g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType   = pPdpPriPara->enPdpType;
    }

    if ( VOS_TRUE  == pPdpPriPara->bitOpApn )
    {
        /* �ַ���ת��Ϊû���ַ����������Ĳ�����ʽ */
        PS_MEM_SET(&g_TafCidTab[ucCid].CidTab.stApn, 0x00,
                   sizeof(TAF_PDP_APN_STRU));

        g_TafCidTab[ucCid].CidTab.stApn.ucLength = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pPdpPriPara->aucApn);
        PS_MEM_CPY(g_TafCidTab[ucCid].CidTab.stApn.aucValue,
                   pPdpPriPara->aucApn,
                   TAF_MAX_APN_LEN);
    }

    if ( (VOS_TRUE     == pPdpPriPara->bitOpPdpAddr)
      && (TAF_PDP_IPV4 == pPdpPriPara->stPdpAddr.enPdpType) )
    {
        /* �ַ���ת��Ϊû���ַ����������Ĳ�����ʽ */
        PS_MEM_SET(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr, 0x00,
                   sizeof(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr));

        PS_MEM_CPY(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr,
                   pPdpPriPara->stPdpAddr.aucIpv4Addr,
                   TAF_IPV4_ADDR_LEN);
    }

    if ( VOS_TRUE  == pPdpPriPara->bitOpPdpDcomp )
    {
        g_TafCidTab[ucCid].CidTab.enPdpDcomp  = pPdpPriPara->enPdpDcomp;
    }

    if ( VOS_TRUE  == pPdpPriPara->bitOpPdpHcomp )
    {
        g_TafCidTab[ucCid].CidTab.enPdpHcomp  = pPdpPriPara->enPdpHcomp;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpIpv4AddrAlloc )
    {
        g_TafCidTab[ucCid].CidTab.enIpv4AddrAlloc = pPdpPriPara->enIpv4AddrAlloc;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpEmergencyInd)
    {
        g_TafCidTab[ucCid].CidTab.enEmergencyInd = pPdpPriPara->enEmergencyFlg;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpImCnSignalFlg)
    {
        g_TafCidTab[ucCid].CidTab.enImCnSignalFlg = pPdpPriPara->enImCnSignalFlg;
    }

    if ( VOS_TRUE   == pPdpPriPara->bitOpPcscfDiscovery)
    {
        g_TafCidTab[ucCid].CidTab.enPcscfDiscovery = pPdpPriPara->enPcscfDiscovery;
    }

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      : Aps_DefPdpPri
 Description    : APP����PdpPri����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2012��5��18��
    ��    ��   : z60575
    �޸�����   : DTS2012051706679 ���ucIpv4AddrAlloc��ucEmergency
  4.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ��Э������������enImCnSignalFlg��enPcscfDiscovery

*****************************************************************************/
VOS_VOID  Aps_DefPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
)
{
    /*pQosPara��ucCid �����������м�飬���ڴ˱��������м��*/

    if ( (VOS_FALSE == pPdpPriPara->bitOpPdpType)
      && (TAF_PDP_IPV4   != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
#if ( FEATURE_ON == FEATURE_IPV6 )
      && (TAF_PDP_IPV6   != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
      && (TAF_PDP_IPV4V6 != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
#endif
      && (TAF_PDP_PPP    != g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType) )
    {
        g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType   =   TAF_PDP_IPV4;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpApn)
    {
        PS_MEM_SET(g_TafCidTab[ucCid].CidTab.stApn.aucValue, 0, TAF_MAX_APN_LEN);
        g_TafCidTab[ucCid].CidTab.stApn.ucLength    =   0;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpPdpAddr)
    {
        PS_MEM_SET(g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr, 0, TAF_IPV4_ADDR_LEN);
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpPdpDcomp)
    {
        g_TafCidTab[ucCid].CidTab.enPdpDcomp        =   TAF_PDP_D_COMP_OFF;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpPdpHcomp)
    {
        g_TafCidTab[ucCid].CidTab.enPdpHcomp        =   TAF_PDP_H_COMP_OFF;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpIpv4AddrAlloc)
    {
        g_TafCidTab[ucCid].CidTab.enIpv4AddrAlloc   =   0;
    }

    if ( VOS_FALSE  == pPdpPriPara->bitOpEmergencyInd)
    {
        g_TafCidTab[ucCid].CidTab.enEmergencyInd       =   0;
    }

    if ( VOS_FALSE   == pPdpPriPara->bitOpImCnSignalFlg)
    {
        g_TafCidTab[ucCid].CidTab.enImCnSignalFlg = TAF_PDP_NOT_FOR_IMS_CN_SIG_ONLY;
    }

    if ( VOS_FALSE   == pPdpPriPara->bitOpPcscfDiscovery)
    {
        g_TafCidTab[ucCid].CidTab.enPcscfDiscovery = TAF_PDP_PCSCF_DISCOVERY_NOT_INFLUENCED;
    }

    g_TafCidTab[ucCid].ucUsed                   = VOS_TRUE;

    return;
}

/*****************************************************************************
 Prototype      : Aps_DefPsSecPdpContext()
 Description    : ���塢�޸ġ�ɾ��Secondary PDP Context���������PDP��Ҫ���
                  PDP�Ѿ����������ͨ���˺�������ת��Ϊ����PDP�������һ��
                  ��PDP�ϡ�ע����μ���������������������IP����,������PPP����
 Input          : ClientId, ʶ��ĳ��Ӧ�ó���;
                  OpId, ʶ��ĳ��Ӧ�ó����е�ĳ�κ���;
                  pPara,ָ��TAF_PDP_SEC_EXT_STRU�ṹ��ָ��;
                        û��TAF_PDP_SEC_EXT_STRU�ṹ����IE����ʾɾ��;
                        ��TAF_PDP_SEC_EXT_STRU�ṹ����IE����ʾ������޸ģ�
                        �Ѿ�������TAF_PDP_SEC_EXT_STRU��Ϊ�޸ģ�����Ϊ���塣
 Output         :
 Return Value   : 0--���塢�޸ġ�ɾ�������ɹ�;
                  1--���塢�޸ġ�ɾ������ʧ��;
 Data Access    :
 Data Update    : g_TafCidTab[]
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2012��01��02��
    ��    ��   : s46746
    �޸�����   : DTS2012010200121: cgdcont����ɾ������PDP������,cgdscont����
                 ɾ����PDP������,ֻ�ܶ�����PDP�Ѿ�����Ķ���������
  4.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ��Э���������ṹ���

*****************************************************************************/
VOS_VOID Aps_DefPsSecPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    if ( VOS_NULL == pPara )
    {   /*��������д�*/
        *pulErrCode = TAF_PARA_SET_ERROR;
        APS_WARN_LOG("input para err!");
        return;
    }

    /*����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab��*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];

    if (VOS_FALSE == pPara->ucDefined)
    {
        /*ɾ������*/
        /*��������PDP_PRI���������Ѿ�����*/
        if (VOS_TRUE == g_TmpPdpTab.ucUsed )
        {
            if (VOS_TRUE == g_TmpPdpTab.ucPriCidFlag)
            {
                /* ��PDPδ�������PDP����ʱ��ȥ����*/
                g_TafCidTab[pPara->ucCid].ucUsed        = VOS_FALSE;
                g_TafCidTab[pPara->ucCid].ucPriCidFlag  = VOS_FALSE;
            }
            else
            {
                *pulErrCode = TAF_PARA_SET_ERROR;
                return;
            }
        }
        else
        {   /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {
        if ((VOS_FALSE == g_TafCidTab[pPara->ucLinkdCid].ucUsed)
         || (VOS_TRUE == g_TafCidTab[pPara->ucLinkdCid].ucPriCidFlag))
        {

            /* ��������û�ж���,������Ƕ���PDP�����ķ��ش��� */
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /*��������޸Ĳ���*/
        Aps_ChngSecPara(pPara);

        /*����û�ж��壬���Ƕ��壬��Ҫȱʡ����û�������ֵ*/
        if (  (TAF_FREE == g_TmpPdpTab.ucUsed)
            ||(TAF_FREE == g_TmpPdpTab.ucPriCidFlag) )
        {
            /*��û������CID�������*/
            if (VOS_FALSE == pPara->bitOpLinkdCid)
            {
                g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;

                *pulErrCode = TAF_PARA_SET_ERROR;
                APS_WARN_LOG("input para err!");
                return;
            }

        }

        /*APP����SecPdpPara����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣*/
        Aps_DefSecPara( pPara );
    }


    ulReturn = Aps_NvimAct( pPara->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {   /*�����ɹ�*/
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*����NVIMʧ�ܣ��ָ�ԭֵ*/

        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("input para err!");
    }
    return;
}

/*****************************************************************************
 Prototype      : Aps_ChngSecPara
 Description    : APP�޸�PdpPri����ʱ,�ô˺���������Ĳ�������PDP����.
 Input          : pPara
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ��Э������������enImCnSignalFlg��enPcscfDiscovery

*****************************************************************************/
VOS_VOID  Aps_ChngSecPara(TAF_PDP_SEC_CONTEXT_EXT_STRU   *pSecPara )
{
    if ( pSecPara->bitOpLinkdCid)
    {
        g_TafCidTab[pSecPara->ucCid].ucPriCid
            = pSecPara->ucLinkdCid;
    }

    if ( pSecPara->bitOpPdpDcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpDcomp
            = pSecPara->enPdpDcomp;
    }

    if ( pSecPara->bitOpPdpHcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpHcomp
            = pSecPara->enPdpHcomp;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_DefSecPara
 Description    : APP����PdpPri����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      : Aps_DefPsPdpContext
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ṹ���

*****************************************************************************/
VOS_VOID  Aps_DefSecPara( TAF_PDP_SEC_CONTEXT_EXT_STRU   *pSecPara )
{
    g_TafCidTab[pSecPara->ucCid].ucUsed            = VOS_TRUE;
    g_TafCidTab[pSecPara->ucCid].ucPriCidFlag      = VOS_TRUE;

    if ( VOS_FALSE == pSecPara->bitOpPdpDcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpDcomp
            = TAF_PDP_D_COMP_OFF;
    }

    if ( VOS_FALSE == pSecPara->bitOpPdpHcomp)
    {
        g_TafCidTab[pSecPara->ucCid].CidTab.enPdpHcomp
            = TAF_PDP_H_COMP_OFF;
    }

    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */


/*****************************************************************************
 Prototype      : Aps_DefPsDns()
 Description    : ���塢�޸ġ�ɾ��DNS�ļ�Ȩ��Ϣ��
 Input          : ClientId, ʶ��ĳ��Ӧ�ó���;
                  OpId, ʶ��ĳ��Ӧ�ó����е�ĳ�κ���;
                  pPara,ָ��TAF_PDP_AUTH_EXT_STRU�ṹ��ָ��;
                        û��TAF_PDP_AUTH_EXT_STRU�ṹ����IE����ʾɾ��;
                        ��TAF_PDP_AUTH_EXT_STRU�ṹ����IE����ʾ������޸ģ�
                        �Ѿ�������TAF_PDP_AUTH_EXT_STRU��Ϊ�޸ģ�����Ϊ���塣
                  ucCid:[1,11]
 Output         :
 Return Value   : 0--���塢�޸ġ�ɾ�������ɹ�;
                  1--���塢�޸ġ�ɾ������ʧ��;
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ṹ���

*****************************************************************************/
VOS_VOID Aps_DefPsDns(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_DNS_EXT_STRU               *pDnsPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    if ( ( VOS_NULL == pDnsPara )
         || (!(TAF_PS_CID_VALID(pDnsPara->ucCid))))
    {
        /*�ϱ���������ʧ��*/
        *pulErrCode = TAF_PARA_SET_ERROR;
        APS_WARN_LOG("input para err!");
        return;
    }

    /*����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab��*/
    g_TmpPdpTab = g_TafCidTab[pDnsPara->ucCid];

    if (VOS_FALSE == pDnsPara->ucDefined)
    {   /*ɾ������*/
        if ( (VOS_TRUE == g_TmpPdpTab.ucDnsFlag)
            ||(VOS_TRUE == g_TmpPdpTab.DnsTab.bitOpPrimDnsAddr)
            ||(VOS_TRUE == g_TmpPdpTab.DnsTab.bitOpSecDnsAddr) )
        {
            g_TafCidTab[pDnsPara->ucCid].ucDnsFlag          = VOS_FALSE;
            g_TafCidTab[pDnsPara->ucCid].DnsTab.bitOpPrimDnsAddr   = VOS_FALSE;
            g_TafCidTab[pDnsPara->ucCid].DnsTab.bitOpSecDnsAddr   = VOS_FALSE;
        }
        else
        {   /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {
        /*����������ȫ�ֱ���*/
        ulReturn = Aps_ChngDns( pDnsPara, pDnsPara->ucCid );
        if ( TAF_APS_FAIL == ulReturn )
        {   /*����޸�ʧ��*/
            g_TafCidTab[pDnsPara->ucCid] = g_TmpPdpTab;

            *pulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
            APS_WARN_LOG("NVIM ACT ERR!");
            return;
        }

        /*�����DNS����û�ж��壬���Ƕ��壬��DNS����Ҫȱʡ����û������Ĳ���ֵ*/
        if ( TAF_FREE == g_TmpPdpTab.ucDnsFlag)
        {
            g_TafCidTab[pDnsPara->ucCid].ucDnsFlag = TAF_USED;
        }
    }

    ulReturn = Aps_NvimAct( pDnsPara->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {   /*�����ɹ�*/
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*����NVIMʧ�ܣ��ָ�ԭֵ*/

        g_TafCidTab[pDnsPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_ChngDns
 Description    : APP�޸�TFT����ʱ,�ô˺���������Ĳ�������PDP����.
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_TafCidTab[ucCid]
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ṹ���

*****************************************************************************/
VOS_UINT32  Aps_ChngDns(
    TAF_PDP_DNS_EXT_STRU               *pDnsPara,
    VOS_UINT8                           ucCid
)
{

    /*pQosPara��ucCid �����������м�飬���ڴ˱��������м��*/

    if ( TAF_USED == pDnsPara->bitOpPrimDnsAddr)
    {
        g_TafCidTab[ucCid].DnsTab.bitOpPrimDnsAddr = VOS_TRUE;

        PS_MEM_CPY(g_TafCidTab[ucCid].DnsTab.aucPrimDnsAddr,
                   pDnsPara->aucPrimDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    if ( TAF_USED == pDnsPara->bitOpSecDnsAddr)
    {
        g_TafCidTab[ucCid].DnsTab.bitOpSecDnsAddr = VOS_TRUE;

        PS_MEM_CPY(g_TafCidTab[ucCid].DnsTab.aucSecDnsAddr,
                   pDnsPara->aucSecDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }

    return  TAF_APS_SUCC;
}
/*****************************************************************************
 Prototype      : Aps_DefPs3gReqQos()
 Description    : ���塢�޸ġ�ɾ��PDP Context�е�3G QOS����
 Input          : ClientId, ʶ��ĳ��Ӧ�ó���;���CID��ָ������ʾɾ�����ж����CID
                  OpId, ʶ��ĳ��Ӧ�ó����е�ĳ�κ���;
                  pPara,ָ��TAF_PDP_QOS_EXT_STRU�ṹ��ָ��;
                        û��TAF_PDP_QOS_EXT_STRU�ṹ����IE����ʾɾ��;
                        ��TAF_PDP_QOS_EXT_STRU�ṹ����IE����ʾ������޸ģ�
                        �Ѿ�������TAF_PDP_QOS_EXT_STRU��Ϊ�޸ģ�����Ϊ���塣
 Output         :
 Return Value   : 0--���塢�޸ġ�ɾ�������ɹ�;
                  1--���塢�޸ġ�ɾ������ʧ��;
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

*****************************************************************************/
VOS_VOID Aps_DefPs3gReqQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    APS_NORM_LOG("into Aps_DefPs3gReqQos ");

    if ( ( VOS_NULL == pPara )
         || (!(TAF_PS_CID_VALID(pPara->ucCid))))
    {
        APS_WARN_LOG("input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /*����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab��*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];


    /*����pPara�ж��Ƿ���ɾ��PDP�����*/
    if (VOS_FALSE == pPara->ucDefined)
    {   /*ɾ��QOS����*/
        APS_NORM_LOG("Aps_DefPs3gReqQos Delete qos def !");
        if ( VOS_TRUE == g_TmpPdpTab.ucQosTabFlag )
        {   /*�����QOS�����Ѿ�����*/
            g_TafCidTab[pPara->ucCid].ucQosTabFlag  = VOS_FALSE;
        }
        else
        {   /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {   /*��������޸�QOS*/
        APS_NORM_LOG("Aps_DefPs3gReqQos Chng qos def !");
        Aps_ChngQos( pPara, pPara->ucCid );

        /*����QOSʱ������û������Ĳ������ô˺�������ȱʡ����*/
        Aps_DefQos( pPara, pPara->ucCid );
    }

    /* �ο�Qʵ��Ч������ʹ��AT+CGEQREQ����QOS������ʱ������д��NV */
    if ( TAF_APS_SUCC   == Aps_NvimAct( pPara->ucCid ) )
    {   /*�����ɹ�*/
        APS_NORM_LOG("Aps_DefPs3gReqQos Chng qos succ !");
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }
    return;

}

/*****************************************************************************
 �� �� ��  : Aps_ChngQos
 ��������  : APP�޸�QOS����ʱ,�ô˺���������Ĳ�������PDP����.
 �������  : pPara
             ucCid
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_ChngQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{

    /*pQosPara��ucCid �����������м�飬���ڴ˱��������м��*/

    if ( VOS_TRUE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[ucCid].QosTab.ucTrafficClass    = pQosPara->ucTrafficClass;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[ucCid].QosTab.ucDeliverOrder    = pQosPara->ucDeliverOrder;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[ucCid].QosTab.ucDeliverErrSdu   = pQosPara->ucDeliverErrSdu;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[ucCid].QosTab.usMaxSduSize      = pQosPara->usMaxSduSize;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[ucCid].QosTab.ulMaxBitUl        = pQosPara->ulMaxBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[ucCid].QosTab.ulMaxBitDl        = pQosPara->ulMaxBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[ucCid].QosTab.ucResidualBer     = pQosPara->ucResidualBer;
    }

    if ( VOS_TRUE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[ucCid].QosTab.ucSduErrRatio     = pQosPara->ucSduErrRatio;
    }

    if ( VOS_TRUE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[ucCid].QosTab.usTransDelay      = pQosPara->usTransDelay;
    }

    if ( VOS_TRUE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[ucCid].QosTab.ucTraffHandlePrior= pQosPara->ucTraffHandlePrior;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[ucCid].QosTab.ulGuarantBitUl    = pQosPara->ulGtdBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[ucCid].QosTab.ulGuarantBitDl    = pQosPara->ulGtdBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[ucCid].QosTab.ucSrcStatisticsDescriptor = pQosPara->ucSrcStatisticsDes;
    }

    if ( VOS_TRUE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[ucCid].QosTab.ucSignallingIndication    = pQosPara->ucSignalIndication;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : Aps_DefQos
 ��������  : ����QOSʱ������û������Ĳ������ô˺�������ȱʡ���塣
 �������  : pPara
             ucCid
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_DefQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{
    /*pQosPara��ucCid �����������м�飬���ڴ˱��������м��*/

    /*QOS��ʶ��λ*/
    g_TafCidTab[pQosPara->ucCid].ucQosTabFlag               = TAF_USED;

    if ( TAF_FREE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucTrafficClass  = APS_APPQOS_TRAFFCLASS_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucDeliverOrder  = APS_APPQOS_DELIVERORDER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucDeliverErrSdu = APS_APPQOS_DELIVEReRRSDU_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.usMaxSduSize    = APS_APPQOS_MAXSDUSIZE_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulMaxBitUl      = APS_APPQOS_MAXBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulMaxBitDl      = APS_APPQOS_MAXBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucResidualBer   = APS_APPQOS_RESIDUALBER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucSduErrRatio   = APS_APPQOS_SDUERRRATIO_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.usTransDelay    = APS_APPQOS_TRANSDELAY_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ucTraffHandlePrior = APS_APPQOS_TRAFFHANDPRIOR_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulGuarantBitUl  = APS_APPQOS_GUARANTBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].QosTab.ulGuarantBitDl  = APS_APPQOS_GUARANTBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[ucCid].QosTab.ucSrcStatisticsDescriptor = APS_APPQOS_SRCSTATISTICSDES_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[ucCid].QosTab.ucSignallingIndication    = APS_APPQOS_SIGNALINDICATION_SUBSCRIB;
    }

    return;

}
/*****************************************************************************
 Prototype      : Aps_DefPs3gMinAcceptQos()
 Description    : ���塢�޸ġ�ɾ��PDP Context�е�3G��С�ɽ���QOS������ʵ�ֹ���
                  �붨��QOS�ǳ����ơ�
 Input          : ClientId, ʶ��ĳ��Ӧ�ó���;
                  OpId, ʶ��ĳ��Ӧ�ó����е�ĳ�κ���;
                  pPara,ָ��TAF_PDP_QOS_EXT_STRU�ṹ��ָ��;
                        û��TAF_PDP_QOS_EXT_STRU�ṹ����IE����ʾɾ��MINQOS;
                        ��TAF_PDP_QOS_EXT_STRU�ṹ����IE����ʾ������޸�MINQOS��
                        �Ѿ�������TAF_PDP_QOS_EXT_STRU��Ϊ�޸ģ�����Ϊ���塣
 Output         :
 Return Value   : 0--���塢�޸ġ�ɾ�������ɹ�;
                  1--���塢�޸ġ�ɾ������ʧ��;
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

*****************************************************************************/
VOS_VOID Aps_DefPs3gMinAcceptQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulReturn;

    ulReturn                            = TAF_APS_SUCC;

    if ( ( VOS_NULL == pPara )
         || (!(TAF_PS_CID_VALID(pPara->ucCid))))
    {
        APS_WARN_LOG("input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /*����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab��*/
    g_TmpPdpTab = g_TafCidTab[pPara->ucCid];


    /*����pPara�ж��Ƿ���ɾ��PDP�����*/
    if (VOS_FALSE == pPara->ucDefined)
    {   /*ɾ��MINQOS����*/

        if ( VOS_TRUE == g_TmpPdpTab.ucMinQosFlag )
        {   /*�����MINQOS�����Ѿ�����*/
            g_TafCidTab[pPara->ucCid].ucMinQosFlag  = VOS_FALSE;
        }
        else
        {   /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {   /*��������޸�MINQOS*/

        Aps_ChngMinQos(  pPara, pPara->ucCid );

        /*����MINQOSʱ������û������Ĳ������ô˺�������ȱʡ����,ȱʡ
           ֵΪ����Э��,�����緵���κ�ֵ������*/
        Aps_DefMinQos( pPara, pPara->ucCid );
    }

    ulReturn        =  Aps_NvimAct( pPara->ucCid );
    if ( TAF_APS_SUCC   == ulReturn )
    {   /*�����ɹ�*/

        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        g_TafCidTab[pPara->ucCid] = g_TmpPdpTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }
    return;

}

/*****************************************************************************
 �� �� ��  : Aps_ChngMinQos
 ��������  : APP�޸�QOS����ʱ,�ô˺���������Ĳ�������PDP����.
 �������  : pPara
             ucCid
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_ChngMinQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{

    /*pQosPara��ucCid �����������м�飬���ڴ˱��������м��*/

    if ( VOS_TRUE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[ucCid].MinQosTab.ucTrafficClass    = pQosPara->ucTrafficClass;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[ucCid].MinQosTab.ucDeliverOrder    = pQosPara->ucDeliverOrder;
    }

    if ( VOS_TRUE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[ucCid].MinQosTab.ucDeliverErrSdu   = pQosPara->ucDeliverErrSdu;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[ucCid].MinQosTab.usMaxSduSize      = pQosPara->usMaxSduSize;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulMaxBitUl        = pQosPara->ulMaxBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulMaxBitDl        = pQosPara->ulMaxBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[ucCid].MinQosTab.ucResidualBer     = pQosPara->ucResidualBer;
    }

    if ( VOS_TRUE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[ucCid].MinQosTab.ucSduErrRatio     = pQosPara->ucSduErrRatio;
    }

    if ( VOS_TRUE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[ucCid].MinQosTab.usTransDelay      = pQosPara->usTransDelay;
    }

    if ( VOS_TRUE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[ucCid].MinQosTab.ucTraffHandlePrior= pQosPara->ucTraffHandlePrior;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulGuarantBitUl    = pQosPara->ulGtdBitUl;
    }

    if ( VOS_TRUE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[ucCid].MinQosTab.ulGuarantBitDl    = pQosPara->ulGtdBitDl;
    }

    if ( VOS_TRUE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[ucCid].MinQosTab.ucSrcStatisticsDescriptor = pQosPara->ucSrcStatisticsDes;
    }

    if ( VOS_TRUE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[ucCid].MinQosTab.ucSignallingIndication    = pQosPara->ucSignalIndication;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : Aps_DefMinQos
 ��������  : ����MINQOSʱ������û������Ĳ������ô˺�������ȱʡ����,ȱʡ
             ֵΪ����Э��,�����緵���κ�ֵ�����ܡ�
 �������  : pPara
             ucCid
 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : M project A characeristic AT part

*****************************************************************************/
VOS_VOID  Aps_DefMinQos(
    TAF_UMTS_QOS_EXT_STRU              *pQosPara,
    VOS_UINT8                           ucCid
)
{
    /*pQosPara��ucCid �����������м�飬���ڴ˱��������м��*/

    /*QOS��ʶ��λ*/
    g_TafCidTab[pQosPara->ucCid].ucMinQosFlag                  = TAF_USED;

    if ( TAF_FREE == pQosPara->bitOpTrafficClass)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucTrafficClass  = APS_APPQOS_TRAFFCLASS_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverOrder)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucDeliverOrder  = APS_APPQOS_DELIVERORDER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpDeliverErrSdu)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucDeliverErrSdu = APS_APPQOS_DELIVEReRRSDU_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxSduSize)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.usMaxSduSize    = APS_APPQOS_MAXSDUSIZE_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulMaxBitUl      = APS_APPQOS_MAXBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpMaxBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulMaxBitDl      = APS_APPQOS_MAXBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpResidualBer)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucResidualBer   = APS_APPQOS_RESIDUALBER_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSduErrRatio)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucSduErrRatio   = APS_APPQOS_SDUERRRATIO_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTransDelay)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.usTransDelay    = APS_APPQOS_TRANSDELAY_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpTraffHandlePrior)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucTraffHandlePrior = APS_APPQOS_TRAFFHANDPRIOR_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitUl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulGuarantBitUl  = APS_APPQOS_GUARANTBITUL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpGtdBitDl)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ulGuarantBitDl  = APS_APPQOS_GUARANTBITDL_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSrcStatisticsDes)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucSrcStatisticsDescriptor = APS_APPQOS_SRCSTATISTICSDES_SUBSCRIB;
    }

    if ( TAF_FREE == pQosPara->bitOpSignalIndication)
    {
        g_TafCidTab[pQosPara->ucCid].MinQosTab.ucSignallingIndication    = APS_APPQOS_SIGNALINDICATION_SUBSCRIB;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_DefNdisAuthdata()
 Description    : ���壬�޸ģ�ɾ��NDIS��AUTHDATA.�������������ݽṹ�Ĳ���,FLASH��
                  AUTHDATA���ݱ��ȫ�ֱ������ݱ�.
 Input          : ClientId, ʶ��ĳ��Ӧ�ó���;
                  OpId, ʶ��ĳ��Ӧ�ó����е�ĳ�κ���;
                  pPara,ָ��AUTHDATA���ṹ��ָ��;
                        û��AUTHDATA���ṹ����IE����ʾɾ��AUTHDATA;
                        ��AUTHDATA���ṹ����IE����ʾ������޸�AUTHDATA��
                        �Ѿ�������AUTHDATA��Ϊ�޸ģ�����Ϊ���塣
 Output         : NO
 Return Value   :
 Calls          :
 History        :
  1.Date        : 2009-09-02
    Author      : L47619
    Modification: Created function

  2.Date        : 2011-07-21
    Author      : k66584
    Modification: ���ⵥ��: DTS2011040706046�������ݲ�ʹ�õ�NV��UENDIS_AUTHDATA_0

  3.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  4.��    ��   : 2012��1��27��
    ��    ��   : h44270
    �޸�����   : PS�ں���Ŀ��ɾ����������ȫ�ֱ���

  5.��    ��   : 2013��12��25��
    ��    ��   : A00165503
    �޸�����   : DTS2013122403650: ^AUTHDATA����֧��CID0
*****************************************************************************/
VOS_VOID    Aps_DefNdisAuthdata (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_AUTHDATA_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode)
{
    VOS_UINT32                          ulReturn;
    VOS_UINT32                          ulNvimRet;
    TAF_NDIS_AUTHDATA_TABLE_STRU        TmpAuthdataTab;
    TAF_NDIS_AUTHDATA_TABLE_STRU        stTmpAuthdataTab;

    ulReturn                            = TAF_APS_SUCC;
    if ( ( VOS_NULL == pPara )
        || (!(TAF_PS_PDP_CONTEXT_CID_VALID(pPara->ucCid))))
    {
        APS_WARN_LOG("Aps_DefNdisAuthdata input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    stTmpAuthdataTab = g_ApsNdisAuthdataTab[pPara->ucCid];

    if (VOS_FALSE == pPara->ucDefined)
    {   /*ɾ��AUTHDATA����*/

        /*��������PDP_PRI���������Ѿ�����*/
        if ( VOS_TRUE == stTmpAuthdataTab.ucUsed )
        {
            /*���PDP�Ķ����ʶ*/
            g_ApsNdisAuthdataTab[pPara->ucCid].ucUsed = VOS_FALSE;
        }
        else
        {   /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            *pulErrCode = TAF_PARA_OK;
            return;
        }
    }
    else
    {   /*��������޸�PDP_PRI����*/

        ulReturn = Aps_ChngAuthdata( pPara, pPara->ucCid );
        if ( TAF_APS_FAIL == ulReturn )
        {   /*����޸�ʧ��*/
            g_ApsNdisAuthdataTab[pPara->ucCid] = stTmpAuthdataTab;
            *pulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
            APS_WARN_LOG("Aps_ChngAuthdata ERR!");
            return;
        }

        /*AT��APP����PdpPri����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣*/
        Aps_DefAuthdata( pPara, pPara->ucCid );
    }

    if ( NV_OK == NV_Read((NV_ID_ENUM_U16)((en_NV_Item_NDIS_Authdata_1 + pPara->ucCid) - 1),
                              (VOS_VOID*)&TmpAuthdataTab,
                              sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU)) )
    {
        if ( 0 == VOS_MemCmp(&TmpAuthdataTab,
                               &g_ApsNdisAuthdataTab[pPara->ucCid],
                               sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU)) )
        {
            *pulErrCode = TAF_PARA_OK;
            APS_INFO_LOG("Aps_DefNdisAuthdata():The content to write is same as NV's");
            return;
        }
    }

    /* д��NV */
    ulNvimRet   = NV_Write((NV_ID_ENUM_U16)((en_NV_Item_NDIS_Authdata_1 + pPara->ucCid) - 1),
                            &g_ApsNdisAuthdataTab[pPara->ucCid],
                            sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU));

    if (TAF_APS_SUCC == ulNvimRet)
    {   /*�����ɹ�*/

        *pulErrCode = TAF_PARA_OK;
    }
    else
    {   /*����NVIMʧ�ܣ��ָ�ԭֵ*/

        g_ApsNdisAuthdataTab[pPara->ucCid] = stTmpAuthdataTab;
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
        APS_WARN_LOG("NVIM ACT ERR!");
    }

    return;
}


/*****************************************************************************
 Prototype      : Aps_ChngAuthdata
 Description    : APP�޸�authdata����ʱ,�ô˺���������Ĳ�������PDP����.
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_ApsNdisAuthdataTab[ucCid]
 Calls          :
 Called By      : Aps_DefNdisAuthdata
 History        : ---
  1.Date        : 2009-09-02
    Author      : L47619
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

*****************************************************************************/
VOS_UINT32  Aps_ChngAuthdata(
    TAF_AUTHDATA_EXT_STRU              *pAuthdataPara,
    VOS_UINT8                           ucCid
)
{
    if ( VOS_TRUE  == pAuthdataPara->bitOpAuthType)
    {
        g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType = pAuthdataPara->enAuthType;
    }

    if ( VOS_TRUE  == pAuthdataPara->bitOpPlmn)
    {
        PS_MEM_CPY( g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn,
                    pAuthdataPara->aucPlmn,
                    VOS_StrLen((VOS_CHAR *)pAuthdataPara->aucPlmn) + 1);
    }

    if ( VOS_TRUE  == pAuthdataPara->bitOpPassWord)
    {
        PS_MEM_CPY( g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                    pAuthdataPara->aucPassWord,
                    VOS_StrLen((VOS_CHAR *)pAuthdataPara->aucPassWord) + 1);
    }

    if ( VOS_TRUE  == pAuthdataPara->bitOpUserName)
    {
        PS_MEM_CPY( g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                    pAuthdataPara->aucUserName,
                    VOS_StrLen((VOS_CHAR *)pAuthdataPara->aucUserName) + 1);
    }

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      : Aps_DefAuthdata
 Description    : APP����AUTHDATA����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣
 Input          : pPara
                  ucCid
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_ApsNdisAuthdataTab[ucCid]
 Calls          :
 Called By      : Aps_DefNdisAuthdata
 History        : ---
  1.Date        : 2009-09-02
    Author      : L47619
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

*****************************************************************************/
VOS_VOID  Aps_DefAuthdata(
    TAF_AUTHDATA_EXT_STRU              *pAuthdataPara,
    VOS_UINT8                           ucCid
)
{
    if ( TAF_FREE  == pAuthdataPara->bitOpAuthType)
    {
        g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType = TAF_PDP_AUTH_TYPE_NONE;
    }

    if ( TAF_FREE  == pAuthdataPara->bitOpPlmn)
    {
        PS_MEM_SET(g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn, 0, TAF_MAX_AUTHDATA_PLMN_LEN + 1);
    }

    if ( TAF_FREE  == pAuthdataPara->bitOpPassWord)
    {
        PS_MEM_SET(g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                   0,
                   TAF_MAX_AUTHDATA_PASSWORD_LEN + 1);
    }

    if ( TAF_FREE  == pAuthdataPara->bitOpUserName)
    {
        PS_MEM_SET(g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                   0,
                   TAF_MAX_AUTHDATA_USERNAME_LEN + 1);
    }

    g_ApsNdisAuthdataTab[ucCid].ucUsed = VOS_TRUE;

    return;
}

/*****************************************************************************
 Prototype      : Aps_QuePri()
 Description    :
 Input          : ucCid
 Output         : PdpPriExtPara,
                  pucErrorCode
 Return Value   :
 Data Access    : g_TafCidTab
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3.��    ��   : 2012��5��18��
    ��    ��   : z60575
    �޸�����   : DTS2012051706679 ���ucIpv4AddrAlloc��ucEmergency
    3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ṹ���

*****************************************************************************/
VOS_VOID Aps_QuePri(
    VOS_UINT8                           ucCid,
    TAF_PRI_PDP_QUERY_INFO_STRU        *pPdpPriPara,
    VOS_UINT32                         *pulErrorCode
)
{
    /*��ʼ��*/
    *pulErrorCode                       = TAF_PARA_OK;

    /*��PDPû�ж���*/
    if (TAF_FREE == g_TafCidTab[ucCid].ucUsed)
    {
        *pulErrorCode                    = TAF_PARA_PDP_CONTEXT_NOT_DEFINED;
        return;
    }

    /*��PDP������ɶ���PDP*/
    if (TAF_USED == g_TafCidTab[ucCid].ucPriCidFlag)
    {
       *pulErrorCode                    = TAF_PARA_PDP_CONTEXT_NOT_DEFINED;
        return;
    }

    pPdpPriPara->ucCid                  = ucCid;

    /*PDPTYPE*/
    pPdpPriPara->stPriPdpInfo.stPdpAddr.enPdpType   = g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType;

    /*APN*/
    if ( g_TafCidTab[ucCid].CidTab.stApn.ucLength >  TAF_MAX_APN_LEN )
    {
        *pulErrorCode                   = TAF_PARA_UNSPECIFIED_ERROR;
        return;
    }
    else if( 0 != g_TafCidTab[ucCid].CidTab.stApn.ucLength )
    {
        pPdpPriPara->stPriPdpInfo.stApn.ucLength = g_TafCidTab[ucCid].CidTab.stApn.ucLength;
        PS_MEM_CPY(pPdpPriPara->stPriPdpInfo.stApn.aucValue,
                   g_TafCidTab[ucCid].CidTab.stApn.aucValue,
                   pPdpPriPara->stPriPdpInfo.stApn.ucLength);
    }
    else
    {
        pPdpPriPara->stPriPdpInfo.stApn.aucValue[0] = '\0';
    }

    /*ADDR*/
    /* ԭ�ȵ�ʵ��:PPP���͵�IP��ַ���ϱ���ֻ��IP���͵ĵ�ַ���ϱ�
       �޸ĺ��ʵ��:Ϊ�����ն˵�ʵ��һ�£�����������IP����PPP���Ͷ��ϱ�IP��ַ*/
    PS_MEM_CPY(pPdpPriPara->stPriPdpInfo.stPdpAddr.aucIpv4Addr,
               g_TafCidTab[ucCid].CidTab.stPdpAddr.aucIpv4Addr,
               TAF_IPV4_ADDR_LEN);

    /*XID*/
    pPdpPriPara->stPriPdpInfo.enPdpDcomp  = g_TafCidTab[ucCid].CidTab.enPdpDcomp;
    pPdpPriPara->stPriPdpInfo.enPdpHcomp  = g_TafCidTab[ucCid].CidTab.enPdpHcomp;

    pPdpPriPara->stPriPdpInfo.enIpv4AddrAlloc  = g_TafCidTab[ucCid].CidTab.enIpv4AddrAlloc;
    pPdpPriPara->stPriPdpInfo.enEmergencyInd   = g_TafCidTab[ucCid].CidTab.enEmergencyInd;

    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    pPdpPriPara->stPriPdpInfo.enImCnSignalFlg  = g_TafCidTab[ucCid].CidTab.enImCnSignalFlg;
    pPdpPriPara->stPriPdpInfo.enPcscfDiscovery = g_TafCidTab[ucCid].CidTab.enPcscfDiscovery;
    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueSec();
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

*****************************************************************************/
VOS_VOID Aps_QueSec(
    VOS_UINT8                           ucCid,
    TAF_PDP_SEC_CONTEXT_STRU           *pPdpSecPara,
    VOS_UINT32                         *pulErrorCode
)
{
    /*��ʼ��*/
    *pulErrorCode                       = TAF_PARA_OK;

    if ( TAF_FREE == g_TafCidTab[ucCid].ucUsed)
    {
       *pulErrorCode                    = TAF_PARA_SEC_PDP_CONTEXT_NOT_DEFINED;
        return;
    }

    if ( TAF_USED == g_TafCidTab[ucCid].ucPriCidFlag)
    {   /*��Cid����ɴ���PDP context*/

        pPdpSecPara->ucCid             = ucCid;
        pPdpSecPara->ucLinkdCid        = g_TafCidTab[ucCid].ucPriCid;
        pPdpSecPara->enPdpDcomp        = g_TafCidTab[ucCid].CidTab.enPdpDcomp;
        pPdpSecPara->enPdpHcomp        = g_TafCidTab[ucCid].CidTab.enPdpHcomp;
    }
    else
    {   /*��Cid���Ǵ���PDP Context*/
       *pulErrorCode                    = TAF_PARA_SEC_PDP_CONTEXT_NOT_DEFINED;
    }

    return;
}


/*****************************************************************************
 Prototype      : Aps_QueState
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2012��06��25��
    ��    ��   : f62575
    �޸�����   : DTS2012062802463, CGACT��ѯ��������CGDCONT���ù���INDEX�Ĳ���״̬��

  3.��    ��   : 2012��06��25��
    ��    ��   : z60575
    �޸�����   : DTS2012120801696, ���⼤���CID��Ҫ�ܲ�ѯ��

  4.��    ��   : 2015��3��2��
    ��    ��   : A00165503
    �޸�����   : DTS2015021101062: PDP�޸Ĺ����в�ѯPDP״̬�쳣
*****************************************************************************/
VOS_VOID Aps_QueState(
    VOS_UINT8                           ucCid,
    TAF_CID_STATE_STRU                 *pPsState,
    VOS_UINT32                         *pulErrorCode
)
{
    VOS_UINT8                   ucTmpPdpId;
    VOS_UINT32                  ucState;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enCdataPsState;

    /*��ʼ��*/
    *pulErrorCode               = TAF_PARA_OK;

    pPsState->ucCid             = ucCid;
    pPsState->ucState           = TAF_PDP_INACTIVE;

    if ((VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(ucCid))
     && (ucCid >= APS_PDP_MIN_CID)
     && (ucCid <= APS_PDP_MAX_CID))
    {
        *pulErrorCode               = TAF_PARA_UNSPECIFIED_ERROR;
        return;
    }

    for ( ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++)
    {
        ucState = TAF_APS_GetPdpIdMainFsmState(ucTmpPdpId);

        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucTmpPdpId);

        /* Xģ���жϵ�ǰPDP�Ƿ񼤻���Ҫ�ж���״̬��CDATA��PS״̬ */
        if ( (VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucTmpPdpId, ucCid))
          && ( (TAF_APS_STA_ACTIVE == ucState)
            || (TAF_APS_STA_MS_MODIFYING == ucState)
            || (TAF_APS_STA_MS_DEACTIVATING == ucState)
            || (TAF_APS_STA_CDATA_DISCING   == ucState)
            || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState) ) )
        {
            pPsState->ucState  = TAF_PDP_ACTIVE;
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Aps_QueRealIpAddr
 ��������  : ��ѯCID��Ӧ��PDPʵ���IP��ַ
 �������  : VOS_UINT8                           ucCid
             TAF_PDP_ADDR_QUERY_INFO_STRU    *paucIpAddr
             VOS_UINT8                          *pucErrorCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��
    ��    ��   : ---
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��6��3��
    ��    ��   : A00165503
    �޸�����   : ����IPV6��ַ�Ĵ���


  3.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  4. ��    ��   : 2010��12��27��
     ��    ��   : h44270
     �޸�����   : Modified by PS Project, ��ѯ״̬�ĺ����޸ģ�ɾ��middle pdp id�ĸ���

*****************************************************************************/
VOS_VOID Aps_QueRealIpAddr(
    VOS_UINT8                           ucCid,
    TAF_PDP_ADDR_QUERY_INFO_STRU       *paucIpAddr,
    VOS_UINT32                         *pulErrorCode
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
    TAF_APS_STA_ENUM_UINT32             enState;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enCdataPsState;

    /* ��ʼ�� */
    *pulErrorCode                       = TAF_PARA_OK;
    paucIpAddr->ucCid                   = ucCid;

    PS_MEM_SET(&paucIpAddr->stPdpAddr, 0x00, sizeof(TAF_PDP_ADDR_STRU));

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
        enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucPdpId);

        /* �˲�ѯ��Ҫ��AT�ϱ����û�����ɹ���PPPЭ�̺�IPv6��ַЭ���ڼ��ѯ�ĵ�ַ��׼ȷ */
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
         && ((TAF_APS_STA_ACTIVE          == enState)
          || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState)))
        {
            if (APS_ADDR_PPP == pstPdpEntity->PdpAddr.ucPdpTypeNum)
            {
                /* PPP���� */
                *pulErrorCode   = TAF_PARA_UNSPECIFIED_ERROR;
            }
#if (FEATURE_ON == FEATURE_IPV6)
            else if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
            {
                /* IPV6���� */
                paucIpAddr->stPdpAddr.enPdpType = TAF_PDP_IPV6;
                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv6Addr,
                           pstPdpEntity->PdpAddr.aucIpV6Addr,
                           TAF_IPV6_ADDR_LEN);
            }
            else if (MN_APS_ADDR_IPV4V6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
            {
                /* IPV4V6���� */
                paucIpAddr->stPdpAddr.enPdpType = TAF_PDP_IPV4V6;

                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv4Addr,
                           pstPdpEntity->PdpAddr.aucIpAddr,
                           TAF_IPV4_ADDR_LEN);

                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv6Addr,
                           pstPdpEntity->PdpAddr.aucIpV6Addr,
                           TAF_IPV6_ADDR_LEN);
            }
#endif
            else
            {
                /*IP����*/
                paucIpAddr->stPdpAddr.enPdpType = TAF_PDP_IPV4;
                PS_MEM_CPY(paucIpAddr->stPdpAddr.aucIpv4Addr,
                           pstPdpEntity->PdpAddr.aucIpAddr,
                           TAF_IPV4_ADDR_LEN);
            }

            break;
        }
    }

    /* ���û���ҵ���Ӧ��PDP */
    if (ucPdpId >= TAF_APS_MAX_PDPID)
    {
        *pulErrorCode = TAF_PARA_UNSPECIFIED_ERROR;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueQosNeg
 Description    : ��ѯPDPЭ�̺�ʵ��ʹ�õ�QOS
 Input          : ucCid
 Output         : pQosNeg
                  pucErrorCode
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2006-11-08
    Author      : h41410
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��
  3. ��    ��   : 2010��12��27��
     ��    ��   : h44270
     �޸�����   : Modified by PS Project, ��ѯ״̬�ĺ����޸ģ�ɾ��middle pdp id�ĸ���

*****************************************************************************/
VOS_VOID Aps_QueQosNeg(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pQosNeg,
    VOS_UINT32                         *pulErrorCode
)
{
    VOS_UINT8                           ucTmpPdpId;

    APS_NORM_LOG("Into Aps_QueQosNeg");

    /*��ʼ��*/
    *pulErrorCode                       = TAF_PARA_OK;

    for ( ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++)
    {
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucTmpPdpId, ucCid))
         && (VOS_TRUE == g_PdpEntity[ucTmpPdpId].PdpNsapiFlag))
        {   /*�����״̬�����ҵ��˸�CID*/

            Aps_3GQos2AppQos(       &(g_PdpEntity[ucTmpPdpId].PdpQos),
                                    &(pQosNeg->stQosInfo));
            pQosNeg->ucCid          = ucCid;
            break;
        }
    }

    /*���û���ҵ���Ӧ��PDP*/
    if ( ucTmpPdpId >= TAF_APS_MAX_PDPID)
    {
        *pulErrorCode = TAF_PARA_UNSPECIFIED_ERROR;
        APS_NORM_LOG("Aps_QueQosNeg: This CID is not ACTIVE.");
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueDns
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ṹ���

*****************************************************************************/
VOS_VOID Aps_QueDns(
    VOS_UINT8                           ucCid,
    TAF_DNS_QUERY_INFO_STRU            *paucDns,
    VOS_UINT32                         *pulErrorCode
)
{
    TAF_PDP_DNS_STRU                   *pCidDns;

    /*��ʼ��*/
    *pulErrorCode                       = TAF_PARA_OK;

    paucDns->ucCid                      = ucCid;
    paucDns->stDnsInfo.bitOpSpare       = VOS_FALSE;


    if ( TAF_FREE == g_TafCidTab[ucCid].ucDnsFlag)
    {   /*ucDnsFlagδ����*/
       *pulErrorCode                    = TAF_PARA_UNSPECIFIED_ERROR;
        return;
    }

    /*ָ�븳ֵ����ʹ����ļ��*/
    pCidDns                             = &g_TafCidTab[ucCid].DnsTab;

    /*����PriDns�ַ���*/
    if (pCidDns->bitOpPrimDnsAddr)
    {
        paucDns->stDnsInfo.bitOpPrimDnsAddr = VOS_TRUE;
        PS_MEM_CPY(paucDns->stDnsInfo.aucPrimDnsAddr,
                   pCidDns->aucPrimDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        paucDns->stDnsInfo.bitOpPrimDnsAddr = VOS_FALSE;
    }

    /*����SecDns�ַ���*/
    if (pCidDns->bitOpSecDnsAddr)
    {
        paucDns->stDnsInfo.bitOpSecDnsAddr = VOS_TRUE;
        PS_MEM_CPY(paucDns->stDnsInfo.aucSecDnsAddr,
                   pCidDns->aucSecDnsAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        paucDns->stDnsInfo.bitOpSecDnsAddr = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_QueAuthdata
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2009-09-07
    Author      : L47619
    Modification: Created function

  2.��    ��   : 2011��10��20��
    ��    ��   : A00165503
    �޸�����   : AT Project: �޸���νṹ��

*****************************************************************************/
VOS_VOID Aps_QueAuthdata(
    VOS_UINT8                           ucCid,
    TAF_AUTHDATA_QUERY_INFO_STRU       *pAuthDataPara,
    VOS_UINT32                         *pulErrorCode
)
{
    /*��ʼ��*/
    *pulErrorCode                       = TAF_PARA_OK;

    /*��AUTHDATAû�ж���*/
    if (TAF_FREE == g_ApsNdisAuthdataTab[ucCid].ucUsed)
    {
       *pulErrorCode                    = TAF_PARA_NDIS_AUTHDATA_NOT_DEFINED;
        return;
    }

    pAuthDataPara->ucCid                        = ucCid;

    /*AUTHTYPE*/
    pAuthDataPara->stAuthDataInfo.enAuthType    = g_ApsNdisAuthdataTab[ucCid].stAuthData.enAuthType;

    /*PLMN*/
    if( 0 != VOS_StrLen((VOS_CHAR *)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn))
    {
        PS_MEM_CPY(pAuthDataPara->stAuthDataInfo.aucPlmn,
                   g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPlmn,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPlmn));
    }
    else
    {
        PS_MEM_SET(pAuthDataPara->stAuthDataInfo.aucPlmn,
                   0,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPlmn));
    }

    /*PASSWORD*/
    if ( 0 != VOS_StrLen((VOS_CHAR *)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword))
    {
        PS_MEM_CPY(pAuthDataPara->stAuthDataInfo.aucPassword,
                   g_ApsNdisAuthdataTab[ucCid].stAuthData.aucPassword,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPassword));
    }
    else
    {
        PS_MEM_SET(pAuthDataPara->stAuthDataInfo.aucPassword,
                   0,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucPassword));
    }

    /*USERNAME*/
    if ( 0 != VOS_StrLen((VOS_CHAR *)g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername))
    {
        PS_MEM_CPY(pAuthDataPara->stAuthDataInfo.aucUsername,
                   g_ApsNdisAuthdataTab[ucCid].stAuthData.aucUsername,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucUsername));
    }
    else
    {
        PS_MEM_SET(pAuthDataPara->stAuthDataInfo.aucUsername,
                   0,
                   sizeof(pAuthDataPara->stAuthDataInfo.aucUsername));
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_NvimAct()
 Description    : ��NVIM�Ĳ����������������塢�޸ġ����жԲ����Ĳ��������漰��
                  ��NVIM�Ĳ�������NVIM������ֱ��ԭ����ȫ�ֱ�������޸ġ���˲�
                  �������ӿں�����ɶ�ȫ�ֱ�����Ĳ����󣬾ͻ���ô˺�����ʵ��
                  ��NVIM�Ĳ�����
                  �����ɹ�,�����g_TafCidTab�е�index����
 Input          : ucCid
 Output         : NO
 Return Value   : TAF_APS_SUCC,
                  TAF_APS_FAIL
 Data Access    : g_TmpPdpTab,
                  g_TafCidTab[pPara->ucCid]
 Data Update    :
 Calls          : NV_Write
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function

  2.��    ��   : 2011��12��24��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDPTBL�ֲ�����̫�󣬸�Ϊ��̬�����ڴ�

  3.��    ��   : 2012��3��6��
    ��    ��   : z40661/anhuiqing
    �޸�����   : NVIMʧ�ܺ��������ִ�У�DTS2012030203625

  4.��    ��   : 2014��3��3��
    ��    ��   : A00165503
    �޸�����   : DTS2014030404070: APS���ؽṹ����NV�ṹ
*****************************************************************************/
VOS_UINT32 Aps_NvimAct(VOS_UINT8 ucCid)
{
    TAF_PDP_TABLE_STRU                 *pstTmpLocalPdpTbl;
    TAF_NV_PDP_TABLE_STRU              *pstTmpNvPdpTbl;
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTbl;
    VOS_UINT16                          usNvId;
    APS_NVIM_ACT_TYPE                   NvimActType;

    /* CID�������NV�����Ĳ���, ֱ�ӷ��سɹ� */
    if (ucCid > TAF_MAX_CID_NV)
    {
        return TAF_APS_SUCC;
    }

    usNvId      = en_NV_Item_Taf_PdpPara_0 + ucCid;
    NvimActType = Aps_JudegNvimActType(ucCid);

    /* �����ڴ� */
    pstTmpLocalPdpTbl = (TAF_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstTmpLocalPdpTbl)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_NvimAct: Alloc pstTmpLocalPdpTbl fail.");
        return  TAF_APS_FAIL;
    }

    pstTmpNvPdpTbl = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstTmpNvPdpTbl)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTmpLocalPdpTbl);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_NvimAct: Alloc pstTmpNvPdpTbl fail.");
        return  TAF_APS_FAIL;
    }

    pstNvPdpTbl = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstNvPdpTbl)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTmpLocalPdpTbl);
        PS_MEM_FREE(WUEPS_PID_TAF, pstTmpNvPdpTbl);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_NvimAct: Alloc pstNvPdpTbl fail.");
        return  TAF_APS_FAIL;
    }

    PS_MEM_SET(pstTmpLocalPdpTbl, 0x00, sizeof(TAF_PDP_TABLE_STRU));
    PS_MEM_SET(pstTmpNvPdpTbl, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));
    PS_MEM_SET(pstNvPdpTbl, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));

    if (NV_OK != NV_Read(usNvId, pstNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)) )
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Read pstNvPdpTbl fail! <NvId>", (VOS_INT32)usNvId);
    }

    if (APS_NVIM_ADD == NvimActType)
    {
        /* ��Ӽ�¼ */
        g_TafCidTab[ucCid].usNvFlag = VOS_TRUE;

        /* �ο�Qʵ�֣�QOS��д��NV�� */
        PS_MEM_CPY(pstTmpLocalPdpTbl, &g_TafCidTab[ucCid], sizeof(TAF_PDP_TABLE_STRU));
        pstTmpLocalPdpTbl->ucQosTabFlag = VOS_FALSE;
        PS_MEM_SET(&pstTmpLocalPdpTbl->QosTab, 0, sizeof(TAF_UMTS_QOS_STRU));
        pstTmpLocalPdpTbl->QosTab.ucTrafficClass  = 4;
        pstTmpLocalPdpTbl->QosTab.ucDeliverOrder  = 2;
        pstTmpLocalPdpTbl->QosTab.ucDeliverErrSdu = 3;

        /* ת�����ؽṹ->NV�ṹ */
        TAF_APS_ConvertLocalPdpTab2NvPdpTab(pstTmpLocalPdpTbl, pstTmpNvPdpTbl);

        /* �Ƚ�NV�����Ƿ�ı� */
        if (0 != PS_MEM_CMP(pstNvPdpTbl, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            if (NV_OK != NV_Write(usNvId, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
            {
                TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Write pstTmpNvPdpTbl(ADD) fail! <NvId>", (VOS_INT32)usNvId);
            }
        }
    }
    else if ( APS_NVIM_CHNG == NvimActType )
    {   /*�޸ļ�¼*/

        /* �ο�Qʵ�֣�QOS��д��NV�� */
        PS_MEM_CPY(pstTmpLocalPdpTbl, &g_TafCidTab[ucCid], sizeof(TAF_PDP_TABLE_STRU));
        pstTmpLocalPdpTbl->ucQosTabFlag = VOS_FALSE;
        PS_MEM_SET(&pstTmpLocalPdpTbl->QosTab, 0, sizeof(TAF_UMTS_QOS_STRU));
        pstTmpLocalPdpTbl->QosTab.ucTrafficClass  = 4;
        pstTmpLocalPdpTbl->QosTab.ucDeliverOrder  = 2;
        pstTmpLocalPdpTbl->QosTab.ucDeliverErrSdu = 3;

        /* ת�����ؽṹ->NV�ṹ */
        TAF_APS_ConvertLocalPdpTab2NvPdpTab(pstTmpLocalPdpTbl, pstTmpNvPdpTbl);

        /* �Ƚ�NV�����Ƿ�ı� */
        if (0 != PS_MEM_CMP(pstNvPdpTbl, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            if (NV_OK != NV_Write(usNvId, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
            {
                TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Write pstTmpNvPdpTbl(CHG) fail! <NvId>", (VOS_INT32)usNvId);
            }
        }
    }
    else
    {
        /* ɾ����¼ */
        g_TafCidTab[ucCid].usNvFlag = VOS_FALSE;
        PS_MEM_SET(pstTmpNvPdpTbl, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));

        if (NV_OK != NV_Write(usNvId, pstTmpNvPdpTbl, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "Aps_NvimAct: Write pstTmpNvPdpTbl(DEL) fail! <NvId>", (VOS_INT32)usNvId);
        }
    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpLocalPdpTbl);
    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpNvPdpTbl);
    PS_MEM_FREE(WUEPS_PID_TAF, pstNvPdpTbl);

    return  TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      :
 Description    : ����g_TafCidTab[ucCid]��g_TmpPdpTab�Ĳ����Ķ�������жϴ˴�
                  ���������,�޸Ļ���ɾ��.
 Input          :
 Output         :
 Return Value   : typedef VOS_UINT8   APS_NVIM_ACT_TYPE;
                  #define APS_NVIM_ADD                    0
                  #define APS_NVIM_CHNG                   1
                  #define APS_NVIM_DELETE                 2
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
APS_NVIM_ACT_TYPE   Aps_JudegNvimActType ( VOS_UINT8        ucCid   )
{
    /*ucCid������������֤�Ϸ���*/
    if ( APS_NVIM_DELETE_ITEM(ucCid) )
    {
        return  APS_NVIM_DELETE;
    }
    else if ( APS_NVIM_UPDATE_ITEM )
    {   /*����ɾ�������п����Ǹ��»����*/
        return  APS_NVIM_CHNG;
    }
    else
    {
        return  APS_NVIM_ADD;
    }
}

/*****************************************************************************
 Prototype      : Aps_SetPsAnsMode
 Description    :
 Input          :
 Output         :
 Return Value   :
 Data Access    :
 Data Update    : g_PsAnsMode
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.��    ��   : 2012��1��27��
    ��    ��   : h44270
    �޸�����   : PS�ں���Ŀ��ɾ����������ȫ�ֱ���
*****************************************************************************/
VOS_VOID Aps_SetPsAnsMode(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      enAnsMode,
    VOS_UINT32                         *pulErrorCode
)
{
    VOS_UINT32                          ulNvimRet;
    TAF_PS_ANSWER_MODE_STRU             stTmpPsAnsMode;


    /*����Ӧ������ʱ���浽��ʱ����g_TmpPsAnsMode��*/
    stTmpPsAnsMode                      = g_PsAnsMode;


    /*��������޸�PDP_PRI����*/
    g_PsAnsMode.enAnsMode               = enAnsMode;
    g_PsAnsMode.enAnsType               = TAF_PDP_ANSWER_TYPE_ACCEPT;
    g_PsAnsMode.usClientId              = ClientId;

    /*�޸�Ӧ��ģʽ*/
    ulNvimRet   = NV_Write(           en_NV_Item_PS_TelePara,
                                       &g_PsAnsMode,
                                       sizeof(TAF_PS_ANSWER_MODE_STRU));
    if ( NV_OK == ulNvimRet )
    {
        *pulErrorCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        g_PsAnsMode                    = stTmpPsAnsMode;
        *pulErrorCode = TAF_PARA_WRITE_NVIM_ERROR;
        return;
    }
}

/*****************************************************************************
 �� �� ��  : MN_APS_GetUtmsQosInfo
 ��������  :
 �������  : VOS_UINT8                           ucCid
             TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
             VOS_UINT32                         *pulErrCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��19��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_APS_GetUtmsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
)
{
    if ( VOS_FALSE == g_TafCidTab[ucCid].ucQosTabFlag )
    {
        /* Qosδ���� */
        *pulErrCode = TAF_PARA_QOS_NOT_DEFINED;
        return;
    }

    pstUmtsQosQueryInfo->ucCid      = ucCid;
    pstUmtsQosQueryInfo->stQosInfo  = g_TafCidTab[ucCid].QosTab;

    *pulErrCode = TAF_PARA_OK;

    return;
}

/*****************************************************************************
 �� �� ��  : MN_APS_GetUtmsQosMinInfo
 ��������  :
 �������  : VOS_UINT8                           ucCid
             TAF_UMTS_QOS_EXT_STRU              *pstUmtsQosInfo
             VOS_UINT32                         *pulErrCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��19��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_APS_GetUtmsQosMinInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
)
{
    if ( VOS_FALSE == g_TafCidTab[ucCid].ucMinQosFlag )
    {
        /* Qosδ���� */
        *pulErrCode = TAF_PARA_QOS_NOT_DEFINED;
        return;
    }

    pstUmtsQosQueryInfo->ucCid      = ucCid;
    pstUmtsQosQueryInfo->stQosInfo  = g_TafCidTab[ucCid].MinQosTab;

    *pulErrCode = TAF_PARA_OK;

    return;
}




/*****************************************************************************
 �� �� ��  : TAF_APS_QueryPfInTft
 ��������  : ��ѯTFT����, �����л�ȡPfId��Ӧ������
 �������  : VOS_UINT8                  ucCid,
             VOS_UINT8                  ucPacketFilterId,
 �������  : VOS_UINT8                 *pucPfIndex
 �� �� ֵ  : VOS_TRUE                   - ������ѯ�ɹ�
             VOS_FALSE                  - û�в�ѯ��PfId��Ӧ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_QueryPfIdInTft(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPacketFilterId,
    VOS_UINT8                          *pucPfIndex
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucPfNum;

    /* ������ʼ�� */
    *pucPfIndex      = VOS_NULL;
    ucIndex         = VOS_NULL;
    ucPfNum         = g_TafCidTab[ucCid].ucPfNum;

    /* ѭ����������ֵ */
    for (ucIndex = 0; ucIndex < ucPfNum; ucIndex++)
    {
        if (ucPacketFilterId == g_TafCidTab[ucCid].astPfTab[ucIndex].ucPacketFilterId)
        {
            *pucPfIndex = ucIndex;
            return VOS_TRUE;
        }
    }

    /* δ�ҵ�����ʧ�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_IsSetTftInfoValid
 ��������  : ���TFT�����������Ч��
 �������  : TAF_TFT_EXT_STRU          *pstTftInfo
 �������  : ��
 �� �� ֵ  : VOS_TRUE       - TFT������Ч
             VOS_FALSE      - TFT������Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_IsSetTftInfoValid(
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    /* ������޸�TFT����, ��PfId, ���ȼ����Ǳ���� */
    if ( (VOS_TRUE == pstTftInfo->ucDefined)
      && (VOS_TRUE == pstTftInfo->bitOpPktFilterId)
      && (VOS_TRUE == pstTftInfo->bitOpPrecedence) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_CheckTftInfoValid
 ��������  : ���TFT��������Ч�Լ���������
 �������  : TAF_TFT_EXT_STRU          *pstTftInfo
 �������  : VOS_UINT8                 *pucPfIndex      -���ؿ��õ�PF����ֵ
 �� �� ֵ  : VOS_TRUE       - TFT������Ч
             VOS_FALSE      - TFT����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_CheckTftInfoValid(
    TAF_TFT_EXT_STRU                   *pstTftInfo,
    VOS_UINT8                          *pucPfIndex
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucPfPrecedence;
    VOS_UINT8                           ucPfId;

    /* ������ʼ�� */
    ulIndex         = VOS_NULL;
    ucPfPrecedence  = VOS_NULL;
    ucPfId          = VOS_NULL;

    /* ���TFT�����������Ч�� */
    /* �˴�����Ҫ�ο���������ʵ�� */
    if (VOS_FALSE == TAF_APS_IsSetTftInfoValid(pstTftInfo))
    {
        TAF_PS_WARN_LOG("TAF_APS_CheckTftInfoValid: TFT info error!");
        return VOS_FALSE;
    }

    /* ͬһ��Cid��,���ȼ�������ͬ*/
    for (ulIndex = 0; ulIndex < g_TafCidTab[pstTftInfo->ucCid].ucPfNum; ulIndex++)
    {
        ucPfPrecedence  = g_TafCidTab[pstTftInfo->ucCid].astPfTab[ulIndex].ucPrecedence;
        ucPfId          = g_TafCidTab[pstTftInfo->ucCid].astPfTab[ulIndex].ucPacketFilterId;

        /* �����ͬһ��Packetfilter������ͬ�����ȼ�*/
        if ((ucPfPrecedence == pstTftInfo->ucPrecedence)
         && (ucPfId != pstTftInfo->ucPacketFilterId))
        {
            TAF_PS_WARN_LOG("TAF_APS_CheckTftInfoValid: Pf precedence error!");
            return VOS_FALSE;
        }
    }

    /* ����ָ��PF ID */
    if (VOS_FALSE == TAF_APS_QueryPfIdInTft(pstTftInfo->ucCid,
                                            pstTftInfo->ucPacketFilterId,
                                            pucPfIndex))
    {
        /* ��ָ��PF�����ڣ�����PF���������򷵻����ô��� */
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        if (g_TafCidTab[pstTftInfo->ucCid].ucPfNum >= TAF_MAX_SDF_PF_NUM)
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
        {
            TAF_PS_WARN_LOG("TAF_APS_CheckTftInfoValid: Pf number is full!");
            return VOS_FALSE;
        }
        else
        {
            /*lint -e961*/
            *pucPfIndex = g_TafCidTab[pstTftInfo->ucCid].ucPfNum++;
            /*lint +e961*/
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_FillTftInfo
 ��������  : �����ò�������PDP��ȫ�ֱ���
 �������  : VOS_UINT8                           ucCid
             VOS_UINT8                           ucPfIndex
             TAF_TFT_EXT_STRU                   *pstTftInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��28��
    ��    ��   : W00316404
    �޸�����   : R11 TFT Э������

*****************************************************************************/
VOS_VOID TAF_APS_FillTftInfo(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPfIndex,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    /* pstTftInfo, ucCid, ucPfIndex����Ч��������������֤ */
    if ( VOS_TRUE == pstTftInfo->bitOpPktFilterId )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucPacketFilterId = pstTftInfo->ucPacketFilterId;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpPrecedence )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucPrecedence      = pstTftInfo->ucPrecedence;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpSrcPortRange )
    {
        if(pstTftInfo->usLowSourcePort == pstTftInfo->usHighSourcePort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleRemotePort = VOS_TRUE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRemotePortRange  = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usSingleRmtPort       = pstTftInfo->usLowSourcePort;
        }
        else if(pstTftInfo->usLowSourcePort < pstTftInfo->usHighSourcePort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleRemotePort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRemotePortRange  = VOS_TRUE;

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usRmtPortHighLimit    = pstTftInfo->usHighSourcePort;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usRmtPortLowLimit     = pstTftInfo->usLowSourcePort;
        }
        else
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleRemotePort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRemotePortRange  = VOS_FALSE;
        }

    }

    if ( VOS_TRUE == pstTftInfo->bitOpDestPortRange )
    {
        if(pstTftInfo->usLowDestPort == pstTftInfo->usHighDestPort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleLocalPort = VOS_TRUE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalPortRange  = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usSingleLcPort       = pstTftInfo->usLowDestPort;
        }
        else if(pstTftInfo->usLowDestPort < pstTftInfo->usHighDestPort)
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleLocalPort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalPortRange = VOS_TRUE;

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usLcPortLowLimit = pstTftInfo->usLowDestPort;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].usLcPortHighLimit = pstTftInfo->usHighDestPort;
        }
        else
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSingleLocalPort = VOS_FALSE;
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalPortRange  = VOS_FALSE;
        }

    }

    if ( VOS_TRUE == pstTftInfo->bitOpSrcIp )
    {
        if (TAF_PDP_IPV4 == pstTftInfo->stSourceIpaddr.enPdpType )
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv4AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Address,
                       pstTftInfo->stSourceIpaddr.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Mask,
                       pstTftInfo->stSourceIpMask.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv6AddrAndMask = VOS_FALSE;
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Address,
                       0x00,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Mask,
                       0x00,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        }
        else if (TAF_PDP_IPV6 == pstTftInfo->stSourceIpaddr.enPdpType )
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv6AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Address,
                       pstTftInfo->stSourceIpaddr.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Mask,
                       pstTftInfo->stSourceIpMask.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv4AddrAndMask = VOS_FALSE;
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Address,
                       0x00,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_SET(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Mask,
                       0x00,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        }
        else
        {
            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv4AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Address,
                       pstTftInfo->stSourceIpaddr.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv4Mask,
                       pstTftInfo->stSourceIpMask.aucIpv4Addr,
                       TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

            g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpRmtIpv6AddrAndMask = VOS_TRUE;
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Address,
                       pstTftInfo->stSourceIpaddr.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
            PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucRmtIpv6Mask,
                       pstTftInfo->stSourceIpMask.aucIpv6Addr,
                       TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        }
    }

    if ( VOS_TRUE == pstTftInfo->bitOpTosMask )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpTypeOfService   = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucTypeOfService      = pstTftInfo->ucTypeOfService;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucTypeOfServiceMask  = pstTftInfo->ucTypeOfServiceMask;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpProtocolId )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpProtocolId    = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucProtocolId       = pstTftInfo->ucProtocolId;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpSpi )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpSecuParaIndex = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ulSecuParaIndex    = pstTftInfo->ulSecuParaIndex;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpNwPktFilterId )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucNwPacketFilterId = pstTftInfo->ucNwPktFilterId;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpFlowLable )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpFlowLabelType = VOS_TRUE;
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ulFlowLabelType    = pstTftInfo->ulFlowLable;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpDirection)
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].enDirection = pstTftInfo->ucDirection;
    }

    if ( VOS_TRUE == pstTftInfo->bitOpLocalIpv4AddrAndMask )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalIpv4AddrAndMask = VOS_TRUE;
        PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucLocalIpv4Addr,
                   pstTftInfo->aucLocalIpv4Addr,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucLocalIpv4Mask,
                   pstTftInfo->aucLocalIpv4Mask,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
    }

    if ( VOS_TRUE == pstTftInfo->bitOpLocalIpv6AddrAndMask )
    {
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].bitOpLocalIpv6AddrAndMask = VOS_TRUE;
        PS_MEM_CPY(g_TafCidTab[ucCid].astPfTab[ucPfIndex].aucLocalIpv6Addr,
                   pstTftInfo->aucLocalIpv6Addr,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        g_TafCidTab[ucCid].astPfTab[ucPfIndex].ucLocalIpv6Prefix         = pstTftInfo->ucLocalIpv6Prefix;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SetTftInfo
 ��������  : ���塢�޸ġ�ɾ��PDP Context�е�TFT����
 �������  : TAF_TFT_EXT_STRU                   *pstTftInfo
             VOS_UINT32                         *pulErrCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��04��23��
    ��    ��   : z60575
    �޸�����   : DTS2012042304705�޸ģ�ɾ��CID��TFT��Ϣʱ��ҪдNV��
*****************************************************************************/
VOS_VOID TAF_APS_SetTftInfo(
    TAF_TFT_EXT_STRU                   *pstTftInfo,
    VOS_UINT32                         *pulErrCode
)
{
    /* ����, �޸�TFT����NV�ȫ�ֱ��� */
    VOS_UINT32                          ulReturn;
    VOS_UINT8                           ucPfIndex;

    /* ������ʼ�� */
    ulReturn                            = TAF_APS_SUCC;
    ucPfIndex                           = VOS_NULL;

    /* ������(cid)����Ч�� */
    if ( ( VOS_NULL_PTR == pstTftInfo )
       || (!(TAF_PS_CID_VALID(pstTftInfo->ucCid))))
    {
        TAF_PS_WARN_LOG("TAF_APS_SetTftInfo input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /* ����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab �� */
    g_TmpPdpTab = g_TafCidTab[pstTftInfo->ucCid];

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if (VOS_FALSE == pstTftInfo->ucDefined)
    {
        /* CID״̬������, ���ֹ��ɾ������ */
        if (TAF_TRUE == Taf_CheckActCid(pstTftInfo->ucCid))
        {
            TAF_PS_WARN_LOG("TAF_APS_SetTftInfo: Delete is not allowed when cid is operating!");
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /* ����ucCid��ɾ��������Ӧ�ṹ�е�TFT��Ϣ */
        g_TafCidTab[pstTftInfo->ucCid].ucPfTabFlag  = VOS_FALSE;
        g_TafCidTab[pstTftInfo->ucCid].ucPfNum      = VOS_NULL;

        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        PS_MEM_SET((VOS_UINT32 *)(g_TafCidTab[pstTftInfo->ucCid].astPfTab),
                   VOS_NULL,
                   sizeof(TAF_PDP_PF_STRU) * TAF_MAX_SDF_PF_NUM);
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
        *pulErrCode = TAF_PARA_OK;
    }
    else
    {
        /* ��������޸�TFT���� */
        g_TafCidTab[pstTftInfo->ucCid].ucPfTabFlag = VOS_TRUE;

        /* ������õ�TFT���� */
        if (VOS_FALSE == TAF_APS_CheckTftInfoValid(pstTftInfo, &ucPfIndex))
        {
            *pulErrCode = TAF_PARA_SET_ERROR;
            return;
        }

        /* �����ò�������PDP��ȫ�ֱ��� */
        TAF_APS_FillTftInfo(pstTftInfo->ucCid, ucPfIndex, pstTftInfo);

        /* �˴�ȱ�ٶ�ȫ�ֱ����ĺϷ��Լ�� */
    }

    /* д��NV�� */
    ulReturn = Aps_NvimAct( pstTftInfo->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {
        /* �����ɹ� */
        *pulErrCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        g_TafCidTab[pstTftInfo->ucCid] = g_TmpPdpTab;
        TAF_PS_WARN_LOG("NVIM ACT ERR!");
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_FillTftQryParam
 ��������  : ��ѯPDP Context�е�TFT����
 �������  : VOS_UINT8                           ucCid
 �������  : TAF_TFT_QUREY_INFO_STRU            *pPdpTftPara
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��28��
    ��    ��   : W00316404
    �޸�����   : R11 TFT Э������

*****************************************************************************/
VOS_VOID TAF_APS_FillTftQryParam(
    VOS_UINT8                           ucCid,
    TAF_TFT_QUREY_INFO_STRU            *pPdpTftPara
)
{
    VOS_UINT8                           ucIndex;

    /*��ʼ��*/
    ucIndex                             = 0;

    /* ����ѯ��TFT���� */
    pPdpTftPara->ucCid                  = ucCid;
    pPdpTftPara->ucPfNum                = g_TafCidTab[ucCid].ucPfNum;

    /* ѭ��������е�TFT���� */
    for (ucIndex = 0; ucIndex < pPdpTftPara->ucPfNum; ucIndex++)
    {
        pPdpTftPara->astPfInfo[ucIndex].bitOpRmtIpv4AddrAndMask    = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpRmtIpv4AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpRmtIpv6AddrAndMask    = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpRmtIpv6AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpProtocolId            = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpProtocolId;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSingleLocalPort       = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSingleLocalPort;
        pPdpTftPara->astPfInfo[ucIndex].bitOpLocalPortRange        = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpLocalPortRange;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSingleRemotePort      = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSingleRemotePort;
        pPdpTftPara->astPfInfo[ucIndex].bitOpRemotePortRange       = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpRemotePortRange;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSecuParaIndex         = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSecuParaIndex;
        pPdpTftPara->astPfInfo[ucIndex].bitOpTypeOfService         = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpTypeOfService;
        pPdpTftPara->astPfInfo[ucIndex].bitOpFlowLabelType         = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpFlowLabelType;
        pPdpTftPara->astPfInfo[ucIndex].bitOpLocalIpv4AddrAndMask  = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpLocalIpv4AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpLocalIpv6AddrAndMask  = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpLocalIpv6AddrAndMask;
        pPdpTftPara->astPfInfo[ucIndex].bitOpSpare                 = g_TafCidTab[ucCid].astPfTab[ucIndex].bitOpSpare;
        pPdpTftPara->astPfInfo[ucIndex].ucPacketFilterId           = g_TafCidTab[ucCid].astPfTab[ucIndex].ucPacketFilterId;
        pPdpTftPara->astPfInfo[ucIndex].ucNwPacketFilterId         = g_TafCidTab[ucCid].astPfTab[ucIndex].ucNwPacketFilterId;
        pPdpTftPara->astPfInfo[ucIndex].enDirection                = g_TafCidTab[ucCid].astPfTab[ucIndex].enDirection;
        pPdpTftPara->astPfInfo[ucIndex].ucPrecedence               = g_TafCidTab[ucCid].astPfTab[ucIndex].ucPrecedence;

        pPdpTftPara->astPfInfo[ucIndex].ulSecuParaIndex            = g_TafCidTab[ucCid].astPfTab[ucIndex].ulSecuParaIndex;
        pPdpTftPara->astPfInfo[ucIndex].usSingleLcPort             = g_TafCidTab[ucCid].astPfTab[ucIndex].usSingleLcPort;
        pPdpTftPara->astPfInfo[ucIndex].usLcPortHighLimit          = g_TafCidTab[ucCid].astPfTab[ucIndex].usLcPortHighLimit;
        pPdpTftPara->astPfInfo[ucIndex].usLcPortLowLimit           = g_TafCidTab[ucCid].astPfTab[ucIndex].usLcPortLowLimit;
        pPdpTftPara->astPfInfo[ucIndex].usSingleRmtPort            = g_TafCidTab[ucCid].astPfTab[ucIndex].usSingleRmtPort;
        pPdpTftPara->astPfInfo[ucIndex].usRmtPortHighLimit         = g_TafCidTab[ucCid].astPfTab[ucIndex].usRmtPortHighLimit;
        pPdpTftPara->astPfInfo[ucIndex].usRmtPortLowLimit          = g_TafCidTab[ucCid].astPfTab[ucIndex].usRmtPortLowLimit;
        pPdpTftPara->astPfInfo[ucIndex].ucProtocolId               = g_TafCidTab[ucCid].astPfTab[ucIndex].ucProtocolId;
        pPdpTftPara->astPfInfo[ucIndex].ucTypeOfService            = g_TafCidTab[ucCid].astPfTab[ucIndex].ucTypeOfService;
        pPdpTftPara->astPfInfo[ucIndex].ucTypeOfServiceMask        = g_TafCidTab[ucCid].astPfTab[ucIndex].ucTypeOfServiceMask;

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv4Address,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv4Address,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv4Mask,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv4Mask,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv6Address,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv6Address,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucRmtIpv6Mask,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucRmtIpv6Mask,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucLocalIpv4Addr,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucLocalIpv4Addr,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucLocalIpv4Mask,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucLocalIpv4Mask,
                   TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));

        PS_MEM_CPY(pPdpTftPara->astPfInfo[ucIndex].aucLocalIpv6Addr,
                   g_TafCidTab[ucCid].astPfTab[ucIndex].aucLocalIpv6Addr,
                   TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));

        pPdpTftPara->astPfInfo[ucIndex].ucLocalIpv6Prefix          = g_TafCidTab[ucCid].astPfTab[ucIndex].ucLocalIpv6Prefix;

        pPdpTftPara->astPfInfo[ucIndex].ulFlowLabelType            = g_TafCidTab[ucCid].astPfTab[ucIndex].ulFlowLabelType;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_SetEpsQosInfo
 ��������  : ����, �޸�, ɾ��EPS QOS����NV�ȫ�ֱ���
 �������  : TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
             VOS_UINT32                         *pulErrCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��25��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SetEpsQosInfo(
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
)
{
    /* ����, �޸�EPS QOS����NV�ȫ�ֱ��� */
    VOS_UINT32                          ulReturn;
    VOS_UINT32                          ulDelFlag;

    /* ������ʼ�� */
    ulReturn                            = TAF_APS_SUCC;
    ulDelFlag                           = 0;

    if ( ( VOS_NULL_PTR == pstEpsQosInfo )
       || (!(TAF_PS_CID_VALID(pstEpsQosInfo->ucCid))))
    {
        TAF_PS_WARN_LOG("TAF_APS_SetEpsQosInfo input para err!");
        *pulErrCode = TAF_PARA_SET_ERROR;
        return;
    }

    /* ����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab �� */
    g_TmpPdpTab = g_TafCidTab[pstEpsQosInfo->ucCid];

    /* ��������޸�EPS_QOS���� */
    g_TafCidTab[pstEpsQosInfo->ucCid].ucEpsQosInfoFlg           = VOS_TRUE;

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpQCI )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ucQCI    = pstEpsQosInfo->ucQCI;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpDLGBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulDLGBR  = pstEpsQosInfo->ulDLGBR;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpULGBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulULGBR  = pstEpsQosInfo->ulULGBR;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpDLMBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulDLMBR  = pstEpsQosInfo->ulDLMBR;
        ulDelFlag++;
    }

    if ( VOS_TRUE  == pstEpsQosInfo->bitOpULMBR )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo.ulULMBR  = pstEpsQosInfo->ulULMBR;
        ulDelFlag++;
    }

    /* ����ֻ��cid, ɾ����cid��Ӧ��EQOS��Ϣ */
    if ( 0 == ulDelFlag )
    {
        g_TafCidTab[pstEpsQosInfo->ucCid].ucEpsQosInfoFlg       = VOS_FALSE;
        PS_MEM_SET(&(g_TafCidTab[pstEpsQosInfo->ucCid].stEpsQosInfo),
                    0x00,
                    sizeof(TAF_EPS_QOS_STRU));
    }

    ulReturn = Aps_NvimAct( pstEpsQosInfo->ucCid );
    if ( TAF_APS_SUCC == ulReturn )
    {
        /* �����ɹ� */
        *pulErrCode = TAF_PARA_OK;
        return;
    }
    else
    {
        /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        g_TafCidTab[pstEpsQosInfo->ucCid] = g_TmpPdpTab;
        TAF_PS_WARN_LOG("NVIM ACT ERR!");
        *pulErrCode = TAF_PARA_WRITE_NVIM_ERROR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_QueEpsQosInfo
 ��������  : ��ѯEPS QOS����
 �������  : VOS_UINT8                           ucCid
             TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo
             VOS_UINT32                         *pulErrCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��27��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_QueEpsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
)
{
    /* ������ʼ�� */
    *pulErrCode                         = TAF_PARA_OK;

    /* ��EQOSû�ж��� */
    if (TAF_FREE == g_TafCidTab[ucCid].ucEpsQosInfoFlg)
    {
        *pulErrCode                     = TAF_PARA_EPS_QOS_NOT_DEFINED;
        return;
    }

    /* ����ѯ��EPS QOS��� */
    pstEpsQosInfo->ucCid                = ucCid;

    pstEpsQosInfo->bitOpQCI             = VOS_TRUE;
    pstEpsQosInfo->ucQCI                = g_TafCidTab[ucCid].stEpsQosInfo.ucQCI;
    pstEpsQosInfo->bitOpDLGBR           = VOS_TRUE;
    pstEpsQosInfo->ulDLGBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulDLGBR;
    pstEpsQosInfo->bitOpULGBR           = VOS_TRUE;
    pstEpsQosInfo->ulULGBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulULGBR;
    pstEpsQosInfo->bitOpDLMBR           = VOS_TRUE;
    pstEpsQosInfo->ulDLMBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulDLMBR;
    pstEpsQosInfo->bitOpULMBR           = VOS_TRUE;
    pstEpsQosInfo->ulULMBR              = g_TafCidTab[ucCid].stEpsQosInfo.ulULMBR;

    return;
}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
/*****************************************************************************
 �� �� ��  : Aps_DefPsPdprofmod
 ��������  : ����PDPROFMOD����
 �������  :
             VOS_UINT8                                     ucCid
             VOS_UINT8                                     OpId
             TAF_PDP_PROFILE_EXT_STRU         *pPara
             VOS_UINT32                                 *pulErrCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��15��
    ��    ��   : x00126983
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID    Aps_DefPsPdprofmod (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PROFILE_EXT_STRU           *pPara,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT32                          ulTmpErrCode;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  stSetPdpCtxInfoReq;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU          stAuthDataReq;

    PS_MEM_SET(&stSetPdpCtxInfoReq, 0, sizeof(stSetPdpCtxInfoReq));
    PS_MEM_SET(&stAuthDataReq, 0, sizeof(stAuthDataReq));
    stSetPdpCtxInfoReq.stCtrl.usClientId = ClientId;
    stSetPdpCtxInfoReq.stCtrl.ucOpId     = OpId;
    ulTmpErrCode                         = 0;

    stSetPdpCtxInfoReq.stPdpContextInfo.bitOpPdpType = pPara->bitOpPdpType;
    stSetPdpCtxInfoReq.stPdpContextInfo.bitOpApn = pPara->bitOpApn;
    stSetPdpCtxInfoReq.stPdpContextInfo.bitOpSpare = pPara->bitOpSpare;

    stSetPdpCtxInfoReq.stPdpContextInfo.ucCid = pPara->ucCid;
    stSetPdpCtxInfoReq.stPdpContextInfo.ucDefined = pPara->ucDefined;

    stSetPdpCtxInfoReq.stPdpContextInfo.enPdpType = pPara->enPdpType;
    PS_MEM_CPY((VOS_UINT8*)(stSetPdpCtxInfoReq.stPdpContextInfo.aucApn),
               (VOS_UINT8*)(pPara->aucApn),
               (TAF_MAX_APN_LEN + 1));

    /* ����Primary PDP������ */
    Aps_DefPsPdpContext(stSetPdpCtxInfoReq.stCtrl.usClientId,
                        stSetPdpCtxInfoReq.stCtrl.ucOpId,
                        &(stSetPdpCtxInfoReq.stPdpContextInfo),
                        &ulTmpErrCode);
    if (TAF_PARA_OK != ulTmpErrCode)
    {
        *pulErrCode = ulTmpErrCode;
        return;
    }

    stAuthDataReq.stCtrl.usClientId = ClientId;
    stAuthDataReq.stCtrl.ucOpId = OpId;

    stAuthDataReq.stAuthDataInfo.bitOpUserName = pPara->bitOpUsername;
    stAuthDataReq.stAuthDataInfo.bitOpPassWord = pPara->bitOpPassword;
    stAuthDataReq.stAuthDataInfo.bitOpAuthType = pPara->bitOpAuthType;
    stAuthDataReq.stAuthDataInfo.bitOpSpare    = pPara->bitOpSpare;

    stAuthDataReq.stAuthDataInfo.ucCid         = pPara->ucCid;
    stAuthDataReq.stAuthDataInfo.ucDefined     = pPara->ucDefined;

    stAuthDataReq.stAuthDataInfo.enAuthType    = pPara->ucAuthType;
    PS_MEM_CPY((VOS_UINT8*)(stAuthDataReq.stAuthDataInfo.aucPassWord),
               (VOS_UINT8*)(pPara->aucPassWord),
               (TAF_MAX_AUTHDATA_PASSWORD_LEN + 1));
    PS_MEM_CPY((VOS_UINT8*)(stAuthDataReq.stAuthDataInfo.aucUserName),
               (VOS_UINT8*)(pPara->aucUserName),
               (TAF_MAX_AUTHDATA_USERNAME_LEN + 1));

    /* ����AUTHDATA����(NDIS) */
    Aps_DefNdisAuthdata(stAuthDataReq.stCtrl.usClientId,
                        stAuthDataReq.stCtrl.ucOpId,
                        &(stAuthDataReq.stAuthDataInfo),
                        &ulTmpErrCode);

    *pulErrCode = ulTmpErrCode;
    return;
}
/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

#endif

/*****************************************************************************
 �� �� ��  : Aps_DeleteLinkedCidSecPdpContext
 ��������  : ɾ��ĳ����Cid��������ж���PDP������
 �������  : VOS_UINT8                           ucCid

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Aps_DeleteLinkedCidSecPdpContext(
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                          i;

    for (i = 1 ; i <= TAF_MAX_CID; i++)
    {
        if ((VOS_TRUE == g_TafCidTab[i].ucUsed )
         && (VOS_TRUE == g_TafCidTab[i].ucPriCidFlag))
        {
            if (ucCid == g_TafCidTab[i].ucPriCid)
            {
                g_TafCidTab[i].ucUsed        = VOS_FALSE;
                g_TafCidTab[i].ucPriCidFlag  = VOS_FALSE;
            }
        }
    }
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
