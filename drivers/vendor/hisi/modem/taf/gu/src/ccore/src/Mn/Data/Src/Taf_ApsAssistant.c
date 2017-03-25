/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Taf_ApsAssistant.c
  Author       : ��³��
  Version      : V200R001
  Date         : 2005-0
  Description  :
  Function List:
        ---Aps_Init
        ---Aps_DbInit
        ---Aps_PdpTabInit
        ---Aps_PdpEntityInit
        ---Aps_ResourseReleas

        ---Aps_ReleaseSmResource
        ---Aps_ReleaseSndcpResource
        ---Aps_CleanEntityFlagOp
        ---Aps_ReleaseApsResource
        ---Aps_ClearAppEvent

        ---Aps_ChngTearDownPdpState
        ---Taf_IpAddr2LenStr

        ---Taf_Apn2Lenstr
        ---Aps_3GQos2AppQos
        ---Aps_TimerExpired
        ---
  History      :
  1. Date:2005-10-30
     Author: ��³��
     Modification:Create
  2. Date:2006-02-23
     Author: ��³��
     Modification: ���ⵥ��:A32D02142
  3. 2006-02-23 modify by ��³�� FOR A32D02144
  4. 2006-03-03 added by h41410 for A32D00636
  5. Date        : 2006-02-24
     Author      : L47619
     Modification: ���ⵥ:A32D02059
  6. 2006-03-31 modify by h41410 for A32D02448
  7. 2006-04-10 MODIFY BY H41410 FOR A32D01902
  8. 2006-04-14 DELETE BY H41410 FOR A32D03180
  9. 2006-04-14 modify by h41410 for A32D03182
  10.2006-04-14 MODIFY BY H41410 FOR A32D03185
  11.2006-04-15 modify by h41410 for A32D03206
  12.��    ��   : 2006��4��4��
     ��    ��   : liuyang id:48197
     �޸�����   : ���ⵥ��:A32D01738
  13.2006-05-13 modify by h41410 for A32D03787
  14.2006-05-13 modify by h41410 for A32D03843
  15.2006-08-15 modify by L47619 for A32D05709
  16.Date        : 2006-09-14
     Author      : l47619
     Modification: �������ⵥ����:A32D05600
  17.2006-09-30 modify by L47619 for A32D06451
  18.2006-12-31 modify by L47619 for A32D08105
  19.��    ��   : 2007��01��09��
    ��    ��   : S62952
    �޸�����   : ���ⵥ�ţ�A32D08079
  20.Date        : 2006-12-31
     Author      : l60022475
     Modification: ���ⵥ:A32D11633
  21.2007-07-06 modify by L47619 for A32D11866
  22.2007-7-31 Add by hanlufeng 41410 for A32D12649
  23.��    ��   : 2007��8��28��
     ��    ��   : l60022475
     �޸�����   : ���ⵥ�ţ�A32D12744,��ʼ��APS Timer���
  24.��    ��   : 2009��5��20��
     ��    ��   : h44270
     �޸�����   : ���ⵥ�ţ�AT2D11987,�޸�NV��ͷ�ļ�����PS/SYS/RF��NV���ֳ������Ա���ά��
  25.��    ��   : 2010��1��9��
     ��    ��   : f62575
     �޸�����   : ���ⵥ�ţ�AT2D16263����Ч����ɾ��NAS_PsIsAllowSleep, Aps_IsAllowSleep
  26.��    ��   : 2010��02��26��
     ��    ��   : z00163274
     �޸�����   : ����PS���ά�ɲ⹦��
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnComm.h"
#include "NasOmInterface.h"
#include "NasOmTrans.h"
#include "MnApsComm.h"
#include "TafApsCtx.h"
#include "TafLog.h"
#include "TafApsMain.h"
#include "TafApsFsmMainTbl.h"
#include "NVIM_Interface.h"
#if (FEATURE_ON == FEATURE_IPV6)
#include "TafApsSndNd.h"
#endif
#include "TafApsComFunc.h"
#include "TafApsProcNvim.h"
#include "ApsL4aInterface.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsComFunc.h"
#include "TafSdcLib.h"
#include "TafApsSndCds.h"
#include "TafApsProcEpdszid.h"

#include "TafApsSndPpp.h"
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
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSASSISTANT_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


VOS_UINT8                               g_ucApsInitFlg      = VOS_FALSE;
APS_PDP_MDF_REQ_ST                     *g_PdpModifyReqTable = VOS_NULL_PTR;
TAF_PDP_TABLE_STRU                     *g_TafCidTab         = VOS_NULL_PTR;
APS_PDP_CONTEXT_ENTITY_ST              *g_PdpEntity         = VOS_NULL_PTR;
TAF_PS_ANSWER_MODE_STRU                 g_PsAnsMode;

TAF_APS_CID_IMS_CFG_TBL_STRU          g_stCidImsCfgTable;



/* �ն˿���������:2G���������ֹSpare_bit3�Ȳ��� */
VOS_UINT8   g_ucDisable2GR5QosExt;

/*Mean throughput���� */
VOS_UINT8   g_ucMeanThrough;

/* WINS���������� */
VOS_UINT8   g_ApsWins;

/*WIN7 NDIS��������:���ڱ���^AUTHDATA����ļ�Ȩ����*/
TAF_NDIS_AUTHDATA_TABLE_STRU            *g_ApsNdisAuthdataTab = VOS_NULL_PTR;

HTIMER                                  g_hGprsDataReqTimer = VOS_NULL_PTR;
TAF_APS_GPRS_DATA_STRU                  g_stGprsDataReq = {0};


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 Prototype      : Aps_Init()
 Description    : ��ʼ��ȫ�ֱ���,����PDPȫ�����ݱ�g_TafCidTab;PDP״̬��.
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : Aps_PdpEntityInit()
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-0
    Author      : ��³�� 41410
    Modification: Created function
  2.Date        : 2006-02-24
    Author      : L47619
    Modification: ���ⵥ:A32D02059
  3.��    ��   : 2007��8��28��
    ��    ��   : l60022475
    �޸�����   : ���ⵥ�ţ�A32D12744,��ʼ��APS Timer���

  4.��    ��   : 2011��12��13��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ������APS��ʱ��CONTEXT������CONTEXT�ĳ�ʼ��
  4.��    ��   : 2012��1��27��
    ��    ��   : h44270
    �޸�����   : PS�ں���Ŀ��ɾ����������ȫ�ֱ���
*****************************************************************************/
VOS_VOID Aps_Init(VOS_VOID)
{
    APS_NORM_LOG("APS INIT 1 begin...");

    /*��APS�Ѿ���ʼ��,��ֱ�ӷ���*/
    if (VOS_TRUE == g_ucApsInitFlg)
    {
        return;
    }

    g_ucApsInitFlg                  = VOS_TRUE;


    TAF_APS_InitTask();



    /*�����ڴ�,�������¸�ȫ������: */
    g_PdpModifyReqTable
        = (APS_PDP_MDF_REQ_ST *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                             (TAF_APS_MAX_PDPID)*(sizeof(APS_PDP_MDF_REQ_ST)));
    if ( VOS_NULL_PTR == g_PdpModifyReqTable )
    {
        APS_ERR_LOG("PS_MEM_ALLOC err!");
        return;
    }

    g_TafCidTab
        = (TAF_PDP_TABLE_STRU *)PS_MEM_ALLOC( WUEPS_PID_TAF,
                                             ((TAF_MAX_CID +1)*(sizeof(TAF_PDP_TABLE_STRU))));
    if ( VOS_NULL_PTR == g_TafCidTab )
    {
        Aps_GlobVarFree();
        APS_ERR_LOG("PS_MEM_ALLOC err!");
        return;
    }

    g_PdpEntity
        = (APS_PDP_CONTEXT_ENTITY_ST *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                   ((TAF_APS_MAX_PDPID)*(sizeof(APS_PDP_CONTEXT_ENTITY_ST))));

    if ( VOS_NULL_PTR == g_PdpEntity )
    {
        Aps_GlobVarFree();
        APS_ERR_LOG("PS_MEM_ALLOC err!");
        return;
    }

    g_ApsNdisAuthdataTab = (TAF_NDIS_AUTHDATA_TABLE_STRU *)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ((TAF_MAX_CID + 1)* (sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU))));
    if ( VOS_NULL_PTR == g_ApsNdisAuthdataTab )
    {
        Aps_GlobVarFree();
        APS_ERR_LOG("VOS_MemAlloc for g_ApsNdisAuthdataTab err!");
        return;
    }

    PS_MEM_SET(&g_stCidImsCfgTable, 0x00, sizeof(g_stCidImsCfgTable));

    /*��ȡPDP Profile�������������NV����*/
    Aps_DbInit();

    /*״̬����ʼ��*/
    Aps_PdpEntityInit();

    APS_NORM_LOG("APS INIT 1 OK.");

    /* DMT����׮ */
    TAF_APS_SetApsDmtTestStub(VOS_FALSE);

    return;
}

/*****************************************************************************
 Prototype      : Aps_GlobVarFree()
 Description    : �ͷ������Ѿ�������ڴ�
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          :
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-0
    Author      : ��³�� 41410
    Modification: Created function
  2.��    ��   : 2012��1��27��
    ��    ��   : h44270
    �޸�����   : PS�ں���Ŀ��ɾ����������ȫ�ֱ���
*****************************************************************************/
VOS_VOID    Aps_GlobVarFree(        VOS_VOID    )
{
    APS_NORM_LOG("APS Globle Variable Mem Free begin:");

    /*APS_PDP_MDF_REQ_ST            g_PdpModifyReqTable[APS_MAX_PDP_NUM + 1 ];*/
    if ( VOS_NULL_PTR != g_PdpModifyReqTable )
    {
        (VOS_VOID)APS_MEM_FREE(g_PdpModifyReqTable);
        g_PdpModifyReqTable         = VOS_NULL_PTR;
        APS_NORM_LOG("Aps_GlobVarFree g_PdpModifyReqTable is freed !");
    }

    /*TAF_PDP_TABLE_STRU            g_TafCidTab[TAF_MAX_CID + 1];*/
    if ( VOS_NULL_PTR != g_TafCidTab )
    {
        (VOS_VOID)APS_MEM_FREE(g_TafCidTab);
        g_TafCidTab                 = VOS_NULL_PTR;
        APS_NORM_LOG("Aps_GlobVarFree g_TafCidTab is freed !");
    }

    /*APS_PDP_CONTEXT_ENTITY_ST     g_PdpEntity[APS_MAX_PDP_NUM +1];*/
    if ( VOS_NULL_PTR != g_PdpEntity )
    {
        (VOS_VOID)APS_MEM_FREE(g_PdpEntity);
        g_PdpEntity                 = VOS_NULL_PTR;
        APS_NORM_LOG("Aps_GlobVarFree g_PdpEntity is freed !");
    }

    /*��APS�ĳ�ʼ����ʶ*/
    g_ucApsInitFlg                  = VOS_FALSE;

    APS_NORM_LOG("APS Globle Variable Mem Free end.");

    return  ;
}

/*****************************************************************************
 Prototype      : Aps_DbInit()
 Description    : ��ʼ��ȫ�ֱ���,����PDPȫ�����ݱ�g_TafCidTab;PDP״̬��.
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : Aps_PdpTabInit()
                  Aps_PdpEntityInit()
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-0
    Author      : ��³�� 41410
    Modification: Created function
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻
*****************************************************************************/
VOS_VOID Aps_DbInit( VOS_VOID )
{
    VOS_UINT16                          usDataLen;
    TAF_PS_ANSWER_MODE_STRU             stTmpTelePara;


    stTmpTelePara.enAnsMode  = TAF_PDP_ANSWER_MODE_MANUAL;
    stTmpTelePara.enAnsType  = TAF_PDP_ANSWER_TYPE_REJECT;
    stTmpTelePara.usClientId = 0;


    /*��ʼ��PDPȫ�����ݱ�*/
    Aps_PdpTabInit();

    /* ��ʼ��g_ApsNdisAuthdataTab�б� */
    Aps_AuthdataTabInit();

    /*��ʼ���Զ�Ӧ�����*/
    /*��NVIM�ж�ȡg_TafTelePara*/
    usDataLen   = sizeof(TAF_PS_ANSWER_MODE_STRU);     /*��ȡ����*/

    if (NV_OK != NV_Read(en_NV_Item_PS_TelePara, (VOS_VOID*)&stTmpTelePara, usDataLen))
    {
        /*��ȡʧ�ܸ�Ĭ��ֵ*/
        g_PsAnsMode.enAnsMode           = TAF_PDP_ANSWER_MODE_MANUAL;
        g_PsAnsMode.enAnsType           = TAF_PDP_ANSWER_TYPE_REJECT;
        g_PsAnsMode.usClientId          = 0;
    }
    else
    {
        g_PsAnsMode.enAnsMode           = stTmpTelePara.enAnsMode;
        g_PsAnsMode.enAnsType           = stTmpTelePara.enAnsType;
        g_PsAnsMode.usClientId          = stTmpTelePara.usClientId;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_Customize_WINS()
 Description    : ���ݶ��Ƶ�Ҫ�󣬳�ʼ����Ӧ����
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-11
    Author      : L47619
    Modification: �ɶ�������
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID    Aps_Customize_WINS(VOS_VOID)
{
    WINS_CONFIG_STRU    stWins;
    VOS_UINT32          ulLength;

    ulLength = 0;


    stWins.ucStatus = VOS_FALSE;
    stWins.ucWins   = WINS_CONFIG_ENABLE;

    (VOS_VOID)NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    if (ulLength > sizeof(stWins))
    {
        return;
    }
    if(NV_OK != NV_Read(en_NV_Item_WINS_Config, &stWins, ulLength))
    {
        /* ����ȡen_NV_Item_WINSʧ�ܣ���Ĭ��WINS����Ϊʹ�� */
        g_ApsWins = WINS_CONFIG_ENABLE;
        return;
    }

    if (0 == stWins.ucStatus)
    {
        /* ��en_NV_Item_WINSδ���ã���ο�Q��ʵ�֣�Ĭ��WINS����Ϊʹ�� */
        g_ApsWins = WINS_CONFIG_ENABLE;
    }
    else
    {
        /* �ж�ucWinsֵ�ĺϷ��� */
        if ((WINS_CONFIG_DISABLE != stWins.ucWins) && (WINS_CONFIG_ENABLE != stWins.ucWins))
        {
            /* ��ucWins�Ƿ�����Ĭ��WINS����Ϊʹ�� */
            g_ApsWins = WINS_CONFIG_ENABLE;
        }
        else
        {
            g_ApsWins = stWins.ucWins;
        }
    }

    return;
}



/*****************************************************************************
 Prototype      : Aps_Customize_APN()
 Description    : �ɶ�������:����Ĭ��APN����
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: �����ն˿�������������
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻

  *****************************************************************************/
VOS_VOID Aps_Customize_APN(VOS_VOID)
{
    APS_APN_CUSTOMIZE_STRU                  stApnCustmize;
    VOS_UINT8                               ucCid;
    VOS_UINT8                               ucApnLen;
    VOS_UINT8                               ucApn;
    VOS_UINT32                              i;


    PS_MEM_SET(&stApnCustmize, 0x00, sizeof(stApnCustmize));


    /*��ȡAPN������NV��*/
    if(NV_OK == NV_Read(en_NV_Item_APN_Customize, &stApnCustmize, sizeof(APS_APN_CUSTOMIZE_STRU)))
    {
        if(0 != stApnCustmize.ucStatus)
        {
            /* ��ȡAPN���� */
            ucApnLen = (VOS_UINT8)VOS_StrNLen((VOS_CHAR *)stApnCustmize.aucApn, TAF_MAX_APN_LEN + 1);
            if ((0 == ucApnLen) || (ucApnLen > TAF_MAX_APN_LEN))
            {
                TAF_LOG1(WUEPS_PID_TAF,
                        TAF_APS,
                        PS_LOG_LEVEL_WARNING,
                        "Aps_Customize_APN:WARNING:ucApnLen is Abnormal,len :",
                        ucApnLen );
                return;
            }

            for (i=0;i < ucApnLen;i++)
            {
                ucApn = UPCASE(stApnCustmize.aucApn[i]);

                if((0 == i) || ((ucApnLen - 1) == i))
                {
                    if ( ! ((('A' <= ucApn ) && ('Z' >= ucApn)) ||
                             (('0' <= ucApn ) && ('9' >= ucApn))))
                    {
                        APS_WARN_LOG ("Invalid begin/end character in APN");
                        return;
                    }
                }
                else
                {
                    /* ����ַ��ĺϷ��� */
                    if ( ! ((('A' <= ucApn ) && ('Z' >= ucApn)) ||
                            (('0' <= ucApn ) && ('9' >= ucApn)) ||
                            ('-' == ucApn) ||
                            ('.' == ucApn)))
                    {
                        APS_WARN_LOG("Invalid character in APN");
                        return;
                    }
                }
            }

            for (ucCid = 1; ucCid <= TAF_MAX_CID; ucCid++)
            {
                /* �����Ƶ�APN����g_TafCidTab�ṹ�� */
                g_TafCidTab[ucCid].CidTab.stApn.ucLength = ucApnLen;
                (VOS_VOID)VOS_MemCpy(g_TafCidTab[ucCid].CidTab.stApn.aucValue,
                           stApnCustmize.aucApn,
                           ucApnLen);

                /*���Ѿ�������PDP������*/
                if((VOS_TRUE == g_TafCidTab[ucCid].usNvFlag) && (VOS_TRUE == g_TafCidTab[ucCid].ucUsed))
                {
                    /* �������ñ�־λ */
                }
                else
                {
                    /* ������Ӧ��־λ */
                    g_TafCidTab[ucCid].usNvFlag = VOS_TRUE;
                    g_TafCidTab[ucCid].ucUsed   = VOS_TRUE;
                }
            }
        }
    }
    return;

}
/*****************************************************************************
 Prototype      : Aps_Customize_TrafficClass()
 Description    : ��������������: Traffic Class����
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: �����ն˿�������������
  2.Date        : 2010-11-25
    Author      : S62952
    Modification: ���ⵥ�ţ�DTS2010112400342 QOSĬ��ֵtrafficClass���˲�һ��
  3.Date        : 2012-03-19
    Author      : w00199382
    Modification: ���ⵥ�ţ�DTS2012031306141 QOSĬ��ֵ��Ϊsubscribed
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  5.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
  *****************************************************************************/
VOS_VOID Aps_Customize_TrafficClass(VOS_VOID)
{
    VOS_UINT8                               ucCid;
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU         stTrafficClass;
    VOS_UINT8                               ucCustomize = VOS_ERR;   /* �Ƿ��Ƶı�� */
    VOS_UINT32                              ulLength;

    /* ���ڶ��Ƶ�Traffic ClassΪ����ֵ:
        0��subscribed value
        1: Conversational class
        2: Streaming Class
        3: Interactive Class
        4: Background Calass

        ��g_TafCidTab�д洢��Traffic Class��ȡֵ��Ϊ:
        0: Conversational class
        1: Streaming Class
        2: Interactive Class
        3: Background Calass
        4��subscribed value

        ���ڶ�g_TafCidTab��ֵʱ���뽫����NV���е�Traffic Classת��Ϊg_TafCidTab�еĺϷ�ֵ
     */
    VOS_UINT8                               ucRealTafficClass;


    stTrafficClass.ucStatus       = VOS_FALSE;
    stTrafficClass.ucTrafficClass = 0;
    ulLength = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_TRAFFIC_CLASS_Type, &ulLength);

    /*��ȡTraffic Class������NV��*/
    if(NV_OK == NV_Read(en_NV_Item_TRAFFIC_CLASS_Type,
                        &stTrafficClass,
                        ulLength))
    {
        if(0 != stTrafficClass.ucStatus)
        {
            switch (stTrafficClass.ucTrafficClass)
            {
                case APS_3GPP_QOS_TRAFFIC_CLASS_SUBSCRIBE:
                    ucRealTafficClass = 4;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL:
                    ucRealTafficClass = 0;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING:
                    ucRealTafficClass = 1;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE:
                    ucRealTafficClass = 2;
                    break;
                case APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND:
                    ucRealTafficClass = 3;
                    break;
                default :
                    /* �����Ƶ�traffic class���������Ĭ�ϵ�Interactive���� */
                    ucRealTafficClass = 4;
                    break;
            }

            for (ucCid = 1; ucCid <= TAF_MAX_CID; ucCid++)
            {
                /* ����Ϊ���Ƶ�Traffic Class */
                g_TafCidTab[ucCid].QosTab.ucTrafficClass = ucRealTafficClass;

                /*���Ѿ�������QOS*/
                if((VOS_TRUE == g_TafCidTab[ucCid].usNvFlag) && (VOS_TRUE == g_TafCidTab[ucCid].ucQosTabFlag))
                {
                    /* �������ñ�־λ */
                }
                else
                {
                    /* ������Ӧ��־λ */
                    g_TafCidTab[ucCid].usNvFlag     = VOS_TRUE;
                    g_TafCidTab[ucCid].ucQosTabFlag = VOS_TRUE;
                }
            }

            /* �ö��Ʊ��ΪVOS_OK */
            ucCustomize = VOS_OK;
        }
    }

    if (VOS_ERR == ucCustomize)
    {
        /* �ο�Qʵ�֣���δ����Traffic Class,����Interactive���ͷ���PDP�������� */
        for (ucCid = 1; ucCid <= TAF_MAX_CID; ucCid++)
        {

            /* ��Traffic Class��Ϊsubscribed���� */
            g_TafCidTab[ucCid].QosTab.ucTrafficClass = 4;  /* 4: subscribed value */



            /*���Ѿ�������QOS*/
            if((VOS_TRUE == g_TafCidTab[ucCid].usNvFlag) && (VOS_TRUE == g_TafCidTab[ucCid].ucQosTabFlag))
            {
                /* �������ñ�־λ */
            }
            else
            {
                /* ������Ӧ��־λ */
                g_TafCidTab[ucCid].usNvFlag     = VOS_TRUE;
                g_TafCidTab[ucCid].ucQosTabFlag = VOS_TRUE;
            }
        }
    }

    return;

}

/*****************************************************************************
 Prototype      : Aps_Customize_MeanThrough
 Description    : �ɶ�������: Mean Throughput ����
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: �����ն˿�������������
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
  *****************************************************************************/
VOS_VOID Aps_Customize_MeanThrough(VOS_VOID)
{
    APS_MEAN_THROUGH_CUSTOMIZE_STRU     stMeanThrough;
    VOS_UINT32                          ulLength;


    ulLength                    = 0;
    stMeanThrough.ucStatus      = VOS_FALSE;
    stMeanThrough.ucMeanThrough = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MEAN_THROUGHPUT, &ulLength);

    /*��ȡAPN������NV��*/
    if(NV_OK == NV_Read(en_NV_Item_MEAN_THROUGHPUT,
                        &stMeanThrough,
                        ulLength))
    {
        if(1 == stMeanThrough.ucStatus)
        {
            g_ucMeanThrough = stMeanThrough.ucMeanThrough;
        }
        else
        {
            g_ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
        }

    }
    else
    {
        g_ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
    }
    return;

}

/*****************************************************************************
 Prototype      : Aps_Customize_Disable2GR5QosExt()
 Description    : �ɶ�������:2G���������ֹSpare_bit3�Ȳ���
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: �����ն˿�������������
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  *****************************************************************************/
VOS_VOID Aps_Customize_Disable2GR5QosExt(VOS_VOID)
{
    APS_2G_DISABLE_BIT3_CUSTOMIZE_STRU  stDisable2GBit3;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    stDisable2GBit3.ucStatus        = 0;
    stDisable2GBit3.ucDisable2GBit3 = 0;


    (VOS_VOID)NV_GetLength(en_NV_Item_2G_DISABLE_SPARE_BIT3, &ulLength);

    /*��ȡ2G�²��������ֹSpare_bit3�Ȳ����Ŀ�����NV��*/
    if(NV_OK == NV_Read(en_NV_Item_2G_DISABLE_SPARE_BIT3,
                        &stDisable2GBit3,
                        ulLength))
    {
        if (1 == stDisable2GBit3.ucStatus)
        {
            g_ucDisable2GR5QosExt = stDisable2GBit3.ucDisable2GBit3;
        }
        else
        {
            g_ucDisable2GR5QosExt = APS_2G_BIT3_DISABLE;
        }
    }
    else
    {
        g_ucDisable2GR5QosExt = APS_2G_BIT3_DISABLE;
    }
    return;
}


/*****************************************************************************
 Prototype      : Aps_InitCustomizeData()
 Description    : ���ݶ��Ƶ�Ҫ�󣬳�ʼ����Ӧ����
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-07-11
    Author      : L47619
    Modification: �ɶ�������
*****************************************************************************/
VOS_VOID    Aps_InitCustomizeData(VOS_VOID)
{
    /* �ɶ�������: ����Ĭ��APN���� */
    Aps_Customize_APN();

    /* �ɶ�������: Traffic Class���� */
    Aps_Customize_TrafficClass();

    /* �ɶ�������: Mean Throughput ���� */
    Aps_Customize_MeanThrough();

    /* �ɶ�������: 2G���������ֹSpare_bit3�Ȳ��� */
    Aps_Customize_Disable2GR5QosExt();

    /* �ɶ�������: WINS�Ƿ�ʹ�ܶ��� */
    Aps_Customize_WINS();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ConvertLocalPdpTab2NvPdpTab
 ��������  : LOCAL PDP��ṹת����NV PDP��ṹ
 �������  : pstLocalPdpTab --- LOCAL PDP TABLE
 �������  : pstNvPdpTab    --- NV PDP TABLE
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��30��
    ��    ��   : w00316404
    �޸�����   : DTS2015120209042: ����traffic classʹ�ܺ�, Ĭ�ϵ�QOS�ᱻ��д

*****************************************************************************/
VOS_VOID TAF_APS_ConvertLocalPdpTab2NvPdpTab(
    CONST TAF_PDP_TABLE_STRU           *pstLocalPdpTab,
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTab
)
{
    /* CID */
    pstNvPdpTab->ucUsed                     = pstLocalPdpTab->ucUsed;
    pstNvPdpTab->ucCid                      = pstLocalPdpTab->ucCid;
    pstNvPdpTab->ucPriCidFlag               = pstLocalPdpTab->ucPriCidFlag;
    pstNvPdpTab->ucPriCid                   = pstLocalPdpTab->ucPriCid;
    pstNvPdpTab->CidTab.enPdpType           = pstLocalPdpTab->CidTab.stPdpAddr.enPdpType;
    Taf_IpAddr2LenStr(pstLocalPdpTab->CidTab.stPdpAddr.aucIpv4Addr, pstNvPdpTab->CidTab.aucPdpAddr);
    PS_MEM_CPY(&pstNvPdpTab->CidTab.stApn, &pstLocalPdpTab->CidTab.stApn, sizeof(TAF_PDP_APN_STRU));
    pstNvPdpTab->CidTab.enPdpDcomp          = pstLocalPdpTab->CidTab.enPdpDcomp;
    pstNvPdpTab->CidTab.enPdpHcomp          = pstLocalPdpTab->CidTab.enPdpHcomp;
    pstNvPdpTab->CidTab.enIpv4AddrAlloc     = pstLocalPdpTab->CidTab.enIpv4AddrAlloc;
    pstNvPdpTab->CidTab.enEmergencyInd      = pstLocalPdpTab->CidTab.enEmergencyInd;
    pstNvPdpTab->CidTab.enPcscfDiscovery    = pstLocalPdpTab->CidTab.enPcscfDiscovery;
    pstNvPdpTab->CidTab.enImCnSignalFlg     = pstLocalPdpTab->CidTab.enImCnSignalFlg;

    /* EPS QOS */
    if (VOS_TRUE == pstLocalPdpTab->ucEpsQosInfoFlg)
    {
        pstNvPdpTab->ucEpsQosInfoFlg        = pstLocalPdpTab->ucEpsQosInfoFlg;
        PS_MEM_CPY(&pstNvPdpTab->stEpsQosInfo, &pstLocalPdpTab->stEpsQosInfo, sizeof(TAF_EPS_QOS_STRU));
    }

    /* UMTS QOS */
    if (VOS_TRUE == pstLocalPdpTab->ucQosTabFlag)
    {
        pstNvPdpTab->ucQosTabFlag           = pstLocalPdpTab->ucQosTabFlag;
        PS_MEM_CPY(&pstNvPdpTab->QosTab, &pstLocalPdpTab->QosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* MIN UTMS QOS */
    if (VOS_TRUE == pstLocalPdpTab->ucMinQosFlag)
    {
        pstNvPdpTab->ucMinQosFlag           = pstLocalPdpTab->ucMinQosFlag;
        PS_MEM_CPY(&pstNvPdpTab->MinQosTab, &pstLocalPdpTab->MinQosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* TFT */
    pstNvPdpTab->ucPfTabFlag               = pstLocalPdpTab->ucPfTabFlag;
    pstNvPdpTab->ucPfNum                    = pstLocalPdpTab->ucPfNum;
    PS_MEM_CPY(&pstNvPdpTab->astPfTab[0], &pstLocalPdpTab->astPfTab[0], sizeof(TAF_PDP_PF_STRU) * TAF_MAX_SDF_PF_NUM);

    /* DNS */
    pstNvPdpTab->ucDnsFlag                  = pstLocalPdpTab->ucDnsFlag;
    pstNvPdpTab->DnsTab.bitOpPrimDnsAddr    = pstLocalPdpTab->DnsTab.bitOpPrimDnsAddr;
    pstNvPdpTab->DnsTab.bitOpSecDnsAddr     = pstLocalPdpTab->DnsTab.bitOpSecDnsAddr;
    PS_MEM_CPY(pstNvPdpTab->DnsTab.aucPrimDnsAddr, pstLocalPdpTab->DnsTab.aucPrimDnsAddr, sizeof(pstNvPdpTab->DnsTab.aucPrimDnsAddr));
    PS_MEM_CPY(pstNvPdpTab->DnsTab.aucSecDnsAddr, pstLocalPdpTab->DnsTab.aucSecDnsAddr, sizeof(pstNvPdpTab->DnsTab.aucSecDnsAddr));

    /* NV FLAG */
    pstNvPdpTab->usNvFlag                   = pstLocalPdpTab->usNvFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ConvertNvPdpTab2LocalPdpTab
 ��������  : NV PDPPDP��ṹת����LOCAL PDP��ṹ
 �������  : pstNvPdpTab    --- NV PDP TABLE
 �������  : pstLocalPdpTab --- LOCAL PDP TABLE
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��3��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��30��
    ��    ��   : w00316404
    �޸�����   : DTS2015120209042: ����traffic classʹ�ܺ�, Ĭ�ϵ�QOS�ᱻ��д

*****************************************************************************/
VOS_VOID TAF_APS_ConvertNvPdpTab2LocalPdpTab(
    CONST TAF_NV_PDP_TABLE_STRU        *pstNvPdpTab,
    TAF_PDP_TABLE_STRU                 *pstLocalPdpTab
)
{
    /* CID */
    pstLocalPdpTab->ucUsed                      = pstNvPdpTab->ucUsed;
    pstLocalPdpTab->ucCid                       = pstNvPdpTab->ucCid;
    pstLocalPdpTab->ucPriCidFlag                = pstNvPdpTab->ucPriCidFlag;
    pstLocalPdpTab->ucPriCid                    = pstNvPdpTab->ucPriCid;
    pstLocalPdpTab->CidTab.stPdpAddr.enPdpType  = pstNvPdpTab->CidTab.enPdpType;
    Taf_LenStr2IpAddr(pstNvPdpTab->CidTab.aucPdpAddr, pstLocalPdpTab->CidTab.stPdpAddr.aucIpv4Addr);
    PS_MEM_CPY(&pstLocalPdpTab->CidTab.stApn, &pstNvPdpTab->CidTab.stApn, sizeof(TAF_PDP_APN_STRU));
    pstLocalPdpTab->CidTab.enPdpDcomp           = pstNvPdpTab->CidTab.enPdpDcomp;
    pstLocalPdpTab->CidTab.enPdpHcomp           = pstNvPdpTab->CidTab.enPdpHcomp;
    pstLocalPdpTab->CidTab.enIpv4AddrAlloc      = pstNvPdpTab->CidTab.enIpv4AddrAlloc;
    pstLocalPdpTab->CidTab.enEmergencyInd       = pstNvPdpTab->CidTab.enEmergencyInd;
    pstLocalPdpTab->CidTab.enPcscfDiscovery     = pstNvPdpTab->CidTab.enPcscfDiscovery;
    pstLocalPdpTab->CidTab.enImCnSignalFlg      = pstNvPdpTab->CidTab.enImCnSignalFlg;

    /* EPS QOS */
    if (VOS_TRUE == pstNvPdpTab->ucEpsQosInfoFlg)
    {
        pstLocalPdpTab->ucEpsQosInfoFlg         = pstNvPdpTab->ucEpsQosInfoFlg;
        PS_MEM_CPY(&pstLocalPdpTab->stEpsQosInfo, &pstNvPdpTab->stEpsQosInfo, sizeof(TAF_EPS_QOS_STRU));
    }

    /* UMTS QOS */
    if (VOS_TRUE == pstNvPdpTab->ucQosTabFlag)
    {
        pstLocalPdpTab->ucQosTabFlag            = pstNvPdpTab->ucQosTabFlag;
        PS_MEM_CPY(&pstLocalPdpTab->QosTab, &pstNvPdpTab->QosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* MIN UTMS QOS */
    if (VOS_TRUE == pstNvPdpTab->ucMinQosFlag)
    {
        pstLocalPdpTab->ucMinQosFlag            = pstNvPdpTab->ucMinQosFlag;
        PS_MEM_CPY(&pstLocalPdpTab->MinQosTab, &pstNvPdpTab->MinQosTab, sizeof(TAF_UMTS_QOS_STRU));
    }

    /* TFT */
    pstLocalPdpTab->ucPfTabFlag                 = pstNvPdpTab->ucPfTabFlag;
    pstLocalPdpTab->ucPfNum                     = pstNvPdpTab->ucPfNum;
    PS_MEM_CPY(&pstLocalPdpTab->astPfTab[0], &pstNvPdpTab->astPfTab[0], sizeof(TAF_PDP_PF_STRU) * TAF_MAX_SDF_PF_NUM);

    /* DNS */
    pstLocalPdpTab->ucDnsFlag                   = pstNvPdpTab->ucDnsFlag;
    pstLocalPdpTab->DnsTab.bitOpPrimDnsAddr     = pstNvPdpTab->DnsTab.bitOpPrimDnsAddr;
    pstLocalPdpTab->DnsTab.bitOpSecDnsAddr      = pstNvPdpTab->DnsTab.bitOpSecDnsAddr;
    PS_MEM_CPY(pstLocalPdpTab->DnsTab.aucPrimDnsAddr, pstNvPdpTab->DnsTab.aucPrimDnsAddr, sizeof(pstLocalPdpTab->DnsTab.aucPrimDnsAddr));
    PS_MEM_CPY(pstLocalPdpTab->DnsTab.aucSecDnsAddr, pstNvPdpTab->DnsTab.aucSecDnsAddr, sizeof(pstLocalPdpTab->DnsTab.aucSecDnsAddr));

    /* NV FLAG */
    pstLocalPdpTab->usNvFlag                    = pstNvPdpTab->usNvFlag;

    return;
}

/*****************************************************************************
 Prototype      : Aps_PdpTabInit()
 Description    : ��ʼ��PDPȫ�����ݱ�g_TafCidTab
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function

  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��EVENT�ṹ�滻

  3.��    ��   : 2014��3��3��
    ��    ��   : A00165503
    �޸�����   : DTS2014030404070: APS���ؽṹ����NV�ṹ
*****************************************************************************/
VOS_VOID    Aps_PdpTabInit(VOS_VOID)
{
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTable = VOS_NULL_PTR;
    VOS_UINT16                          usIndex;
    VOS_UINT16                          usNvId;

    if (VOS_NULL_PTR == g_TafCidTab)
    {
        APS_ERR_LOG("ERROR:Aps_PdpTabInit g_TafCidTab is NUILL PTR!");
        return;
    }

    pstNvPdpTable = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));
    if (VOS_NULL_PTR == pstNvPdpTable)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_PdpTabInit: Alloc memory fail!");
        return;
    }

    /* �Ա����ռ��λ��� */
    for (usIndex = 0; usIndex <= TAF_MAX_CID; usIndex++)
    {
        /* ���g_TafCidTab */
        PS_MEM_SET(&g_TafCidTab[usIndex], 0, sizeof(TAF_PDP_TABLE_STRU));

        g_TafCidTab[usIndex].ucUsed         = VOS_FALSE;
        g_TafCidTab[usIndex].ucCid          = (VOS_UINT8)usIndex;
        g_TafCidTab[usIndex].ucEpsQosInfoFlg = VOS_FALSE;
        g_TafCidTab[usIndex].ucQosTabFlag   = VOS_FALSE;
        g_TafCidTab[usIndex].ucMinQosFlag   = VOS_FALSE;
        g_TafCidTab[usIndex].ucPfTabFlag    = VOS_FALSE;
        g_TafCidTab[usIndex].ucDnsFlag      = VOS_FALSE;
        g_TafCidTab[usIndex].ucPriCidFlag   = VOS_FALSE;

        /* ��ʼ��PDP������Ϣ */
        g_TafCidTab[usIndex].CidTab.stPdpAddr.enPdpType     = TAF_PDP_IPV4;
        g_TafCidTab[usIndex].CidTab.stApn.ucLength          = 0;
        g_TafCidTab[usIndex].CidTab.enPdpDcomp              = TAF_PDP_D_COMP_OFF;
        g_TafCidTab[usIndex].CidTab.enPdpHcomp              = TAF_PDP_H_COMP_OFF;

        /* ��ʼ��Qos�� */
        g_TafCidTab[usIndex].QosTab.ucTrafficClass          = 4;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucDeliverOrder          = 2;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucDeliverErrSdu         = 3;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.usMaxSduSize            = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulMaxBitUl              = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulMaxBitDl              = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucResidualBer           = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucSduErrRatio           = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.usTransDelay            = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ucTraffHandlePrior      = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulGuarantBitUl          = 0;    /*Subscribed value*/
        g_TafCidTab[usIndex].QosTab.ulGuarantBitDl          = 0;    /*Subscribed value*/

    }

    /* ��ȡNV(0-11), ʵ��NV�ṹ->���ؽṹת�� */
    for (usIndex = 0; usIndex <= TAF_MAX_CID_NV; usIndex++)
    {
        PS_MEM_SET(pstNvPdpTable, 0x00, sizeof(TAF_NV_PDP_TABLE_STRU));

        usNvId = en_NV_Item_Taf_PdpPara_0 + usIndex;
        if (NV_OK != NV_Read(usNvId, pstNvPdpTable, sizeof(TAF_NV_PDP_TABLE_STRU)))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_PdpTabInit: Read NV fail!");
            continue;
        }

        /* NV PDP������ṹ->LOCAL PDP������ṹ */
        TAF_APS_ConvertNvPdpTab2LocalPdpTab(pstNvPdpTable, TAF_APS_GetTafCidInfoAddr(usIndex));
    }

    /* ��ʼ���������������Ӧ���� */
    Aps_InitCustomizeData();

    /* �ͷ���ʱ�ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNvPdpTable);

    return;
}


/*****************************************************************************
 Prototype      : Aps_AuthdataTabInit()
 Description    : ��ʼ��g_ApsNdisAuthdataTab�б�
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2009-09-01
    Author      : L47619
    Modification: Created function
  2.Date        : 2011-07-21
    Author      : k66584
    Modification: ���ⵥ��: DTS2011040706046�������ݲ�ʹ�õ�NV��UENDIS_AUTHDATA_0
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2013��12��25��
    ��    ��   : A00165503
    �޸�����   : DTS2013122403650: ^AUTHDATA����֧��CID0
*****************************************************************************/
VOS_VOID    Aps_AuthdataTabInit(VOS_VOID)
{
    VOS_UINT16                              usIndex;
    VOS_UINT16                              usDataLen;
    TAF_NDIS_AUTHDATA_TABLE_STRU            TmpAuthdataTab;


    PS_MEM_SET(&TmpAuthdataTab, 0x00, sizeof(TmpAuthdataTab));


    if (VOS_NULL_PTR == g_ApsNdisAuthdataTab)
    {
        APS_ERR_LOG("Aps_AuthdataTabInit:ERROR:g_ApsNdisAuthdataTab is NUILL PTR!");
        return;
    }

    usDataLen = sizeof(TAF_NDIS_AUTHDATA_TABLE_STRU);

    for (usIndex = 0; usIndex <= TAF_MAX_CID; usIndex++)
    {
        /*���g_ApsNdisAuthdataTab*/
        PS_MEM_SET(&g_ApsNdisAuthdataTab[usIndex], 0, usDataLen);

        g_ApsNdisAuthdataTab[usIndex].ucUsed                    = VOS_FALSE;

        /* ��ʼ����Ȩ��Ϣ */
        g_ApsNdisAuthdataTab[usIndex].stAuthData.enAuthType     = TAF_PDP_AUTH_TYPE_NONE;
        g_ApsNdisAuthdataTab[usIndex].stAuthData.aucPlmn[0]     = 0;
        g_ApsNdisAuthdataTab[usIndex].stAuthData.aucPassword[0] = 0;
        g_ApsNdisAuthdataTab[usIndex].stAuthData.aucUsername[0] = 0;
    }

    for (usIndex = 0; usIndex <= TAF_MAX_CID_NV; usIndex++)
    {
        /*total 11 records*/
        if (NV_OK == NV_Read((NV_ID_ENUM_U16)((en_NV_Item_NDIS_Authdata_1 + usIndex) - 1),
                              (VOS_VOID*)&TmpAuthdataTab,
                              usDataLen))
        {
            /*����Ӧ��NV���Ƿ�����NV Table�����ù�*/
            if (VOS_TRUE == TmpAuthdataTab.ucUsed)
            {
                /*����NV���ݵ�g_ApsNdisAuthdataTab��*/
                g_ApsNdisAuthdataTab[usIndex] = TmpAuthdataTab;
            }
        }
    }
}

/*****************************************************************************
 Prototype      : Aps_PdpEntityInit()
 Description    : ��ʼ��PDP״̬��
 Input          : NO
 Output         : NO
 Return Value   : ---
 Calls          : ---
 Called By      : NO
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_PdpEntityInit(VOS_VOID)
{
    VOS_UINT8           ucTmpPdpId;

    for(ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++ )
    {
        Aps_ReleaseApsResource(ucTmpPdpId);
    }


    return;
}


/*****************************************************************************
 Prototype      : Aps_ReleaseSndcpResource()
 Description    : ��SNDCP����ȥ������Ϣ,���ͷ�SNDCP����Դ
 Input          : ucPdpId
 Output         : NO
 Return Value   : ---
 Calls          : Aps_SmMsgModSnDeActInd()
 Called By      : Aps_ResourseReleas()
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
  2.��    ��   : 2012��1��3��
    ��    ��   : A00165503
    �޸�����   : PS Project: ��SNDCP��������ΪINACT
*****************************************************************************/
VOS_VOID    Aps_ReleaseSndcpResource    (   VOS_UINT8   ucPdpId )
{
    if (TAF_APS_FAIL == Aps_SmMsgModSnDeActInd ( ucPdpId ))
    {
        APS_ERR_LOG("Snd Sndcp Deact Msg Fail !");
    }

    /* SNDCP��������ΪINACTIVE */
    g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;

    return;
}



/*****************************************************************************
 Prototype      : Aps_ReleaseApsResource()
 Description    : �ͷ�APS�Լ�����Դ,����״̬��,��ʱ��,ȫ�ֱ���
 Input          : ucPdpId
 Output         : NO
 Return Value   : ---
 Data Accessed  :
 Data Update    : g_PdpEntity[ucPdpId]
 Calls          : ---
 Called By      : Aps_ResourseReleas()
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function

  2.��    ��   : 2011��12��13��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��ʹ��APS��ʱ���½ӿ�
  3.��    ��   : 2012��1��27��
    ��    ��   : h44270
    �޸�����   : PS�ں���Ŀ��ɾ����������ȫ�ֱ���
*****************************************************************************/
VOS_VOID    Aps_ReleaseApsResource  (   VOS_UINT8   ucPdpId )
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_ReleaseEpdszidResource();

    /* disabe dormant timer feature  */
    TAF_APS_SetSocmDormantTiLen(0);

    TAF_APS_SetUserCfgDormTiVal(0);
#endif

    PS_MEM_SET(&g_PdpEntity[ucPdpId], 0x00, sizeof(APS_PDP_CONTEXT_ENTITY_ST));

    g_PdpEntity[ucPdpId].ulUsedFlg              = VOS_FALSE;
    g_PdpEntity[ucPdpId].ucPdpId                = ucPdpId;
    g_PdpEntity[ucPdpId].stClientInfo.ucCid     = TAF_APS_INVALID_CID;

    g_PdpEntity[ucPdpId].stCdataInfo.enLastReOrigErr = TAF_XCC_FAIL_LAYER_BUTT;

    g_PdpModifyReqTable[ucPdpId].Op_Spare            = APS_MDF_NO_QOS;

    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/*****************************************************************************
 �� �� ��  : Aps_3GQos2AppQos_ForMaxBitRateForUp
 ��������  : ����Maximum bit rate for uplink (Aps_3GQos2AppQos��Ȧ���Ӷ�)
 �������  : pApsQos
 �������  : pTafPdp
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : w00316404
    �޸�����   : R11Э������

*****************************************************************************/
VOS_VOID Aps_3GQos2AppQos_ForMaxBitRateForUp(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucMaxBitRateForUpExt)
      && (0 == pApsQos->ucMaxBitRateForUpExt_2) )
    {
        /*  In MS to network direction:
            0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
            In network to MS direction:
            0 0 0 0 0 0 0 0 Reserved
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
            0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

            0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
            0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

            1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
            1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

            1 1 1 1 1 1 1 1 0kbps
        */
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucMaxBitRateForUp)
        {
            pTafQos->ulMaxBitUl = APS_APP_QOS_BIT_0KBPS;
        }
        else if( pApsQos->ucMaxBitRateForUp >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulMaxBitUl
                =   ((pApsQos->ucMaxBitRateForUp - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucMaxBitRateForUp >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulMaxBitUl
                =   ((pApsQos->ucMaxBitRateForUp - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulMaxBitUl = pApsQos->ucMaxBitRateForUp;
        }
    }
    else if ( (0 != pApsQos->ucMaxBitRateForUpExt)
           && (0 == pApsQos->ucMaxBitRateForUpExt_2) )
    {
        /*In MS to network direction and in network to MS direction:
          0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for uplink in octet 9.

          For all other values: Ignore the value indicated by the Maximum bit rate for uplink in octet 9
          and use the following value:
          0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
          0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

          0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
          1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

          1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
          1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
         */
        if (pApsQos->ucMaxBitRateForUpExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucMaxBitRateForUpExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS));
        }
        else
        {
            /* ������APS_3GPP_QOS_BIT_256MBPS����ֵΪ256000 */
            pTafQos->ulMaxBitUl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucMaxBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucMaxBitRateForUpExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucMaxBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulMaxBitUl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucMaxBitRateForUpExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* ������APS_APP_QOS_BIT_10GBPS����ֵΪ10000000 */
            pTafQos->ulMaxBitUl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}

/*****************************************************************************
 �� �� ��  : Aps_3GQos2AppQos_ForMaxBitRateForDown
 ��������  : ����Maximum bit rate for downlink (Aps_3GQos2AppQos��Ȧ���Ӷ�)
 �������  : pApsQos
 �������  : pTafPdp
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : w00316404
    �޸�����   : R11Э������

*****************************************************************************/
VOS_VOID Aps_3GQos2AppQos_ForMaxBitRateForDown(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucMaxBitRateForDownExt)
      && (0 == pApsQos->ucMaxBitRateForDownExt_2) )
    {
        /*usMaxBitDl*/
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucMaxBitRateForDown )
        {
            pTafQos->ulMaxBitDl = APS_APP_QOS_BIT_0KBPS;
        }
        else if( pApsQos->ucMaxBitRateForDown >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulMaxBitDl
                =   ((pApsQos->ucMaxBitRateForDown - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucMaxBitRateForDown >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulMaxBitDl
                =   ((pApsQos->ucMaxBitRateForDown - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulMaxBitDl = pApsQos->ucMaxBitRateForDown;
        }
    }
    else if ( (0 != pApsQos->ucMaxBitRateForDownExt)
           && (0 == pApsQos->ucMaxBitRateForDownExt_2) )
    {
        /*In MS to network direction and in network to MS direction:
          0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9.

          For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9
          and use the following value:
          0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
          0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

          0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
          1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

          1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
          1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
        */
        if (pApsQos->ucMaxBitRateForDownExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucMaxBitRateForDownExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS));
        }
        else
        {
            /* ������APS_3GPP_QOS_BIT_256MBPS����ֵΪ256000 */
            pTafQos->ulMaxBitDl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucMaxBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucMaxBitRateForDownExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucMaxBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulMaxBitDl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucMaxBitRateForDownExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* ������APS_APP_QOS_BIT_10GBPS����ֵΪ10000000 */
            pTafQos->ulMaxBitDl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}

/*****************************************************************************
 �� �� ��  : Aps_3GQos2AppQos_ForGuarantBitRateForUp
 ��������  : ����Guaranteed bit rate for downlink (Aps_3GQos2AppQos��Ȧ���Ӷ�)
 �������  : pApsQos
 �������  : pTafPdp
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : w00316404
    �޸�����   : R11Э������

*****************************************************************************/
VOS_VOID Aps_3GQos2AppQos_ForGuarantBitRateForUp(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucGuarantBitRateForUpExt)
      && (0 == pApsQos->ucGuarantBitRateForUpExt_2) )
    {
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucGuarantBitRateForUp)
        {
            pTafQos->ulGuarantBitUl = APS_APP_QOS_BIT_0KBPS;
        }
        else if ( pApsQos->ucGuarantBitRateForUp >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulGuarantBitUl
                =   ((pApsQos->ucGuarantBitRateForUp - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucGuarantBitRateForUp >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulGuarantBitUl
                =   ((pApsQos->ucGuarantBitRateForUp - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulGuarantBitUl = pApsQos->ucGuarantBitRateForUp;
        }
    }
    else if ( (0 != pApsQos->ucGuarantBitRateForUpExt)
           && (0 == pApsQos->ucGuarantBitRateForUpExt_2) )
    {
        /*  Guaranteed bit rate for downlink (extended), octet 16
            Bits
            8 7 6 5 4 3 2 1
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for downlink in octet 13.

            For all other values: Ignore the value indicated by the Guaranteed bit rate for downlink in octet 9
            and use the following value:
            0 0 0 0 0 0 0 1 The guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
            0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

            0 1 0 0 1 0 1 1 The guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
            1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

            1 0 1 1 1 0 1 1 The guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
            1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForUpExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucGuarantBitRateForUpExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucGuarantBitRateForUpExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulGuarantBitUl =
                APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS);
        }
        else if (pApsQos->ucGuarantBitRateForUpExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulGuarantBitUl =
                APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS);
        }
        else
        {
            /* ������APS_3GPP_QOS_BIT_256MBPS����ֵΪ256000 */
            pTafQos->ulGuarantBitUl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucGuarantBitRateForUpExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForUpExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulGuarantBitUl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucGuarantBitRateForUpExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* ������APS_APP_QOS_BIT_10GBPS����ֵΪ10000000 */
            pTafQos->ulGuarantBitUl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}

/*****************************************************************************
 �� �� ��  : Aps_3GQos2AppQos_ForGuarantBitRateForDown
 ��������  : ����Guaranteed bit rate for downlink (Aps_3GQos2AppQos��Ȧ���Ӷ�)
 �������  : pApsQos
 �������  : pTafPdp
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : w00316404
    �޸�����   : R11Э������

*****************************************************************************/
VOS_VOID Aps_3GQos2AppQos_ForGuarantBitRateForDown(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    if ( (0 == pApsQos->ucGuarantBitRateForDownExt)
      && (0 == pApsQos->ucGuarantBitRateForDownExt_2) )
    {
        /*usGuarantBitDl*/
        if (APS_3GPP_QOS_BIT_0KBPS == pApsQos->ucGuarantBitRateForDown)
        {
            pTafQos->ulGuarantBitDl = APS_APP_QOS_BIT_0KBPS;
        }
        else if( pApsQos->ucGuarantBitRateForDown >= APS_3GPP_QOS_BIT_576KBPS)
        {
            pTafQos->ulGuarantBitDl
                =   ((pApsQos->ucGuarantBitRateForDown - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (pApsQos->ucGuarantBitRateForDown >= APS_3GPP_QOS_BIT_64KBPS)
        {
            pTafQos->ulGuarantBitDl
                =   ((pApsQos->ucGuarantBitRateForDown - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            pTafQos->ulGuarantBitDl = pApsQos->ucGuarantBitRateForDown;
        }
    }
    else if ( (0 != pApsQos->ucGuarantBitRateForDownExt)
           && (0 == pApsQos->ucGuarantBitRateForDownExt_2) )
    {
        /*  Guaranteed bit rate for downlink (extended), octet 16
            Bits
            8 7 6 5 4 3 2 1
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for downlink in octet 13.

            For all other values: Ignore the value indicated by the Guaranteed bit rate for downlink in octet 9
            and use the following value:
            0 0 0 0 0 0 0 1 The guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
            0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

            0 1 0 0 1 0 1 1 The guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
            1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

            1 0 1 1 1 0 1 1 The guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
            1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForDownExt <= APS_3GPP_QOS_BIT_16000KBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_8600KBPS
                 + (pApsQos->ucGuarantBitRateForDownExt * APS_3GPP_QOS_BIT_INC_100KBPS));
        }
        else if (pApsQos->ucGuarantBitRateForDownExt <= APS_3GPP_QOS_BIT_128MBPS)
        {
            pTafQos->ulGuarantBitDl =
                APS_APP_QOS_BIT_16MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt - APS_3GPP_QOS_BIT_16000KBPS)
                   * APS_3GPP_QOS_BIT_INC_1MBPS);
        }
        else if (pApsQos->ucGuarantBitRateForDownExt <= APS_3GPP_QOS_BIT_256MBPS)
        {
            pTafQos->ulGuarantBitDl =
                APS_APP_QOS_BIT_128MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt - APS_3GPP_QOS_BIT_128MBPS)
                   * APS_3GPP_QOS_BIT_INC_2MBPS);
        }
        else
        {
            /* ������APS_3GPP_QOS_BIT_256MBPS����ֵΪ256000 */
            pTafQos->ulGuarantBitDl = APS_APP_QOS_BIT_256MBPS;
        }
    }
    else
    {
        /*
            In MS to network direction and in network to MS direction:
            0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

            For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
            octet 15 and use the following value:
            0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
            0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

            0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
            1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

            1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
            1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
        */
        if (pApsQos->ucGuarantBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_500MBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_256MBPS
                 + (pApsQos->ucGuarantBitRateForDownExt_2 * APS_3GPP_QOS_BIT_INC_4MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_1500MBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_500MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt_2 - APS_3GPP_QOS_BIT_500MBPS)
                   * APS_3GPP_QOS_BIT_INC_10MBPS));
        }
        else if (pApsQos->ucGuarantBitRateForDownExt_2 <= APS_3GPP_QOS_BIT_10GBPS)
        {
            pTafQos->ulGuarantBitDl =
                (APS_APP_QOS_BIT_1500MBPS
                 + ((pApsQos->ucGuarantBitRateForDownExt_2 - APS_3GPP_QOS_BIT_1500MBPS)
                   * APS_3GPP_QOS_BIT_INC_100MBPS));
        }
        else
        {
            /* ������APS_APP_QOS_BIT_10GBPS����ֵΪ10000000 */
            pTafQos->ulGuarantBitDl = APS_APP_QOS_BIT_10GBPS;
        }
    }
}

/*****************************************************************************
 �� �� ��  : Aps_3GQos2AppQos
 ��������  : ��QOS�ϱ���APPʱ,��Ҫ��3G��QOS����ת��ΪAPP��QOS����.
 �������  : pApsQos
 �������  : pTafPdp
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��24��
    ��    ��   : L47619
    �޸�����   : V7R1C50 IPC��Ŀ:����ucSrcStatisticsDescriptor��
                 ucSignallingIndication�ĸ�ֵ
*****************************************************************************/
VOS_VOID Aps_3GQos2AppQos(
    APS_PDP_QOS_STRU                    *pApsQos,
    TAF_UMTS_QOS_STRU                   *pTafQos
)
{
    /*ucTrafficClass*/
    /*
    In MS to network direction:
    0 0 0       Subscribed traffic class
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       Conversational class
    0 1 0       Streaming class
    0 1 1       Interactive class
    1 0 0       Background class
    1 1 1       Reserved
    */
    if ( APS_3GPP_QOS_TRAFFICCLASS_BOT == pApsQos->ucTrafficClass)
    {   /*���粻Ӧ�÷�0�������������ˣ�����Ϊ0�����ķ���*/
        pTafQos->ucTrafficClass = APS_QOS_TRAFFIC_CLASS_BACKGROUND;
    }
    else
    {
        pTafQos->ucTrafficClass
            =   pApsQos->ucTrafficClass - APS_TRAFFICCLASS_APP3GPP_DIFF_VAL;
    }


    /*ucDeliverOrder*/
    /*
        In MS to network direction:
        0 0     Subscribed delivery order
        In network to MS direction:
        0 0     Reserved
        In MS to network direction and in network to MS direction:
        0 1     With delivery order ('yes')
        1 0     Without delivery order ('no')
        1 1     Reserved
        ~~~~~~~~~~~~~~~~~~~~~
        0 - no
        1 - yes
        2 - subscribed value.
    */
    if ((APS_3GPP_QOS_DELIVERORDER_BOT < pApsQos->ucDeliverOrder) &&
        (pApsQos->ucDeliverOrder < APS_3GPP_QOS_DELIVERORDER_TOP))
    {
        pTafQos->ucDeliverOrder
            =   APS_DELIVERORDER_APP3GPP_DIFF_VAL - pApsQos->ucDeliverOrder;
    }
    else
    {
        pTafQos->ucDeliverOrder = APS_APPQOS_DELIVERORDER_SUBSCRIB;
    }

    /*ucDeliverErrSdu*/
    /*
        In MS to network direction:
        0 0 0       Subscribed delivery of erroneous SDUs
        In network to MS direction:
        0 0 0       Reserved
        In MS to network direction and in network to MS direction:
        0 0 1       No detect ('-')
        0 1 0       Erroneous SDUs are delivered ('yes')
        0 1 1       Erroneous SDUs are not delivered ('no')
        1 1 1       Reserved
        ~~~~~~~~~~~~~~~~
        0 - no
        1 - yes
        2 - no detect
        3 - subscribed value
    */
    if ( pApsQos->ucDeliverOfErrSdu <= APS_3GPP_QOS_DELIVER_ERRSDU_TOP)
    {
        pTafQos->ucDeliverErrSdu
            =   APS_DELIVEROFERRSDU_APP3GPP_DIFF_VAL - pApsQos->ucDeliverOfErrSdu;
    }
    else
    {
        pTafQos->ucDeliverErrSdu = APS_APPQOS_DELIVEReRRSDU_SUBSCRIB;
    }

    /*usMaxSduSize*/
    
    if ( APS_3GPP_QOS_MAXSDUSIZE_1520OCTS == pApsQos->ucMaximSduSize )
    {
        pTafQos->usMaxSduSize = APS_APP_QOS_MAXSDUSIZE_1520OCTS;
    }
    else if ( APS_3GPP_QOS_MAXSDUSIZE_1510OCTS == pApsQos->ucMaximSduSize)
    {
        pTafQos->usMaxSduSize = APS_APP_QOS_MAXSDUSIZE_1510OCTS;
    }
    else if ( APS_3GPP_QOS_MAXSDUSIZE_1502OCTS == pApsQos->ucMaximSduSize)
    {
        pTafQos->usMaxSduSize = APS_APP_QOS_MAXSDUSIZE_1502OCTS;
    }
    else
    {
        pTafQos->usMaxSduSize = APS_3GPP_QOS_MAXSDUSIZE_GRANUL_10 * (pApsQos->ucMaximSduSize);
    }

    /*ulMaxBitUl*/
    Aps_3GQos2AppQos_ForMaxBitRateForUp(pApsQos, pTafQos);

    /*ulMaxBitDl*/
    Aps_3GQos2AppQos_ForMaxBitRateForDown(pApsQos, pTafQos);

    /*ucResidualBer*/
    /*
        In network to MS direction:
        0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:
        The Residual BER value consists of 4 bits. The range is from 5*10-2 to 6*10-8.
        0 0 0 1     5*10-2
        0 0 1 0     1*10-2
        0 0 1 1     5*10-3
        0 1 0 0     4*10-3
        0 1 0 1     1*10-3
        0 1 1 0     1*10-4
        0 1 1 1     1*10-5
        1 0 0 0     1*10-6
        1 0 0 1     6*10-8
        1 1 1 1     Reserved
    */
    pTafQos->ucResidualBer = pApsQos->ucResidualBer;


    /*ucSduErrRatio*/
    /*
        In MS to network direction:
        0 0 0 0     Subscribed SDU error ratio
        In network to MS direction:
        0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:
        The SDU error ratio value consists of 4 bits. The range is is from 1*10-1 to 1*10-6.
        0 0 0 1     1*10-2
        0 0 1 0     7*10-3
        0 0 1 1     1*10-3
        0 1 0 0     1*10-4
        0 1 0 1     1*10-5
        0 1 1 0     1*10-6
        0 1 1 1     1*10-1
        1 1 1 1     Reserved
    */
    pTafQos->ucSduErrRatio = pApsQos->ucSduErrRatio;


    /*usTransDelay*/
    /*
        In MS to network direction:
        0 0 0 0 0 0     Subscribed transfer delay
        In network to MS direction:
        0 0 0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:

        0 0 0 0 0 1     The Transfer delay is binary coded in 6 bits, using a granularity of 10 ms
        0 0 1 1 1 1     giving a range of values from 10 ms to 150 ms in 10 ms increments

        0 1 0 0 0 0     The transfer delay is 200 ms + ((the binary coded value in 6 bits - 010000) * 50 ms)
        0 1 1 1 1 1     giving a range of values from 200 ms to 950 ms in 50ms increments

        1 0 0 0 0 0     The transfer delay is 1000 ms + ((the binary coded value in 6 bits - 100000) * 100 ms)
        1 1 1 1 1 0     giving a range of values from 1000 ms to 4000 ms in 100ms increments

        1 1 1 1 1 1     Reserved
    */
    if ( pApsQos->ucTransDelay >= APS_3GPP_QOS_TRANSDELAY_1000MS )
    {
        pTafQos->usTransDelay
            =   ((pApsQos->ucTransDelay - APS_3GPP_QOS_TRANSDELAY_1000MS)
              * APS_3GPP_QOS_TRANSDELAY_INC_100MS)
              + APS_APP_QOS_TRANSDELAY_1000MS;
    }
    else if ( pApsQos->ucTransDelay >= APS_3GPP_QOS_TRANSDELAY_200MS )
    {
        pTafQos->usTransDelay
            =   ((pApsQos->ucTransDelay - APS_3GPP_QOS_TRANSDELAY_200MS)
              * APS_3GPP_QOS_TRANSDELAY_INC_50MS)
              + APS_APP_QOS_TRANSDELAY_200MS;
    }
    else
    {
        pTafQos->usTransDelay
            =   pApsQos->ucTransDelay * APS_3GPP_QOS_TRANSDELAY_INC_10MS;
    }


    /*ucTraffHandlePrior;*/
    /*
        In MS to network direction:
        0 0     Subscribed traffic handling priority
        In network to MS direction:
        0 0     Reserved
        In MS to network direction and in network to MS direction:
        0 1     Priority level 1
        1 0     Priority level 2
        1 1     Priority level 3
    */
    pTafQos->ucTraffHandlePrior = pApsQos->ucTraffHandlPrior;


    /*ulGuarantBitUl;*/
    Aps_3GQos2AppQos_ForGuarantBitRateForUp(pApsQos, pTafQos);

    /*ulGuarantBitDl*/
    Aps_3GQos2AppQos_ForGuarantBitRateForDown(pApsQos, pTafQos);

#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pTafQos->ucSrcStatisticsDescriptor = pApsQos->ucSrcStatisticsDescriptor;
    pTafQos->ucSignallingIndication    = pApsQos->ucSignallingIndication;
#else
    pTafQos->ucSrcStatisticsDescriptor = APS_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN;
    pTafQos->ucSignallingIndication    = APS_QOS_SIGNAL_IND_NOT_OPTIMISE;
#endif

    return;
}

/*****************************************************************************
 Prototype      : Aps_SetEvtApn
 Description    :
 Input          : ucPdpId
 Output         : pPsAppEvt
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��EVENT�ṹ�滻
*****************************************************************************/
VOS_UINT32    Aps_SetEvtApn(
    VOS_UINT8                       ucPdpId,
    TAF_PDP_APN_STRU               *pstPdpApn)
{
    VOS_UINT32                  ulRelt;

    VOS_UINT8                   aucTmpEntityApn[APS_MAX_LENGTH_OF_APN + 1];
    VOS_UINT8                   aucTmpLenStr[TAF_MAX_APN_LEN + 1];

    if ( VOS_FALSE == g_PdpEntity[ucPdpId].PdpApnFlag)
    {
        ulRelt = VOS_ERR;
    }
    else if(g_PdpEntity[ucPdpId].PdpApn.ucLength > APS_MAX_LENGTH_OF_APN)
    {
        ulRelt = VOS_ERR;
    }
    else
    {
        ulRelt = VOS_OK;

        aucTmpEntityApn[0]      = g_PdpEntity[ucPdpId].PdpApn.ucLength;

        PS_MEM_CPY(             &aucTmpEntityApn[1],
                                g_PdpEntity[ucPdpId].PdpApn.aucValue,
                                aucTmpEntityApn[0]);

        Taf_Apn2Lenstr(aucTmpEntityApn, aucTmpLenStr);

        pstPdpApn->ucLength = aucTmpLenStr[0];
        if (pstPdpApn->ucLength > TAF_MAX_APN_LEN)
        {
            pstPdpApn->ucLength = TAF_MAX_APN_LEN;
        }
        PS_MEM_CPY(pstPdpApn->aucValue, &aucTmpLenStr[1], pstPdpApn->ucLength);
    }

    return ulRelt;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/*****************************************************************************
 Prototype      : Aps_SetEvtDns
 Description    : ����ʵ��DNS��ϱ����¼���
 Input          : ---
 Output         : ---
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��EVENT�ṹ�滻

*****************************************************************************/
VOS_VOID Aps_SetEvtDns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_DNS_STRU                   *pstDns,
    TAF_PDP_IPV6_DNS_STRU              *pstIpv6Dns
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)
    {
        PS_MEM_CPY((VOS_CHAR*)pstDns,
                   (VOS_CHAR*)&pstPdpEntity->PdpDns,
                   sizeof(TAF_PDP_DNS_STRU));
    }

#if (FEATURE_ON == FEATURE_IPV6)
    PS_MEM_CPY((VOS_CHAR*)pstIpv6Dns,
               (VOS_CHAR*)&pstPdpEntity->stPdpIpV6Dns,
               sizeof(MN_APS_PDP_IPV6_DNS_STRU));
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : MN_APS_SetEvtNbns
 ��������  : ��дNBNS���¼�
 �������  : VOS_UINT8                           ucPdpId
             TAF_PDP_NBNS_STRU                  *pstNbns
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��16��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻
  3.��    ��   : 2014��02��14��
    ��    ��   : Y00213812
    �޸�����   : DTS2014031105153

*****************************************************************************/
VOS_VOID MN_APS_SetEvtNbns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_NBNS_STRU                  *pstNbns
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    PS_MEM_SET(pstNbns, 0x00, sizeof(TAF_PDP_NBNS_STRU));

    /* Primary NBNS */
    if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_PriNbns)
    {
        pstNbns->bitOpPrimNbnsAddr   = VOS_TRUE;

        PS_MEM_CPY(pstNbns->aucPrimNbnsAddr,
                   pstPdpEntity->stPdpNbns.aucPriNbns,
                   TAF_IPV4_ADDR_LEN);
    }

    /* Secondary NBNS */
    if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_SecNbns)
    {
        pstNbns->bitOpSecNbnsAddr  = VOS_TRUE;

        PS_MEM_CPY(pstNbns->aucSecNbnsAddr,
                   pstPdpEntity->stPdpNbns.aucSecNbns,
                   TAF_IPV4_ADDR_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_APS_SetEvtGateWay
 ��������  : ��дGATE WAY���¼�
 �������  : VOS_UINT8                           ucPdpId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��16��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻

*****************************************************************************/
VOS_VOID MN_APS_SetEvtGateWay(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_FALSE == pstPdpEntity->bitOpPdpGateWay)
    {
        pstPsCallEvt->stGateWay.bitOpGateWayAddr = VOS_FALSE;
    }
    else
    {
        if (VOS_TRUE == pstPdpEntity->stPdpGateWay.bitOpGateWay)
        {
            pstPsCallEvt->stGateWay.bitOpGateWayAddr = VOS_TRUE;

            PS_MEM_CPY(pstPsCallEvt->stGateWay.aucGateWayAddr,
                       pstPdpEntity->stPdpGateWay.aucGateWay,
                       TAF_IPV4_ADDR_LEN);
        }
    }

    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */




/*****************************************************************************
 Prototype      : Aps_FillEvtPcoIpcpInfo
 Description    : ��д�ϱ��¼���PCO��Ϣ��IPCP��Ϣ
 Input          : ---
 Output         : ---
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-9-29
    Author      : L47619
    Modification: �������ⵥ����:A32D06451
*****************************************************************************/
VOS_VOID  Aps_FillEvtPcoIpcpInfo(VOS_UINT8 *pucIpcpInfo, SM_TAF_PROT_CFG_OPT_STRU *pSmPco)
{
    VOS_UINT8       ucSubPackNum = 0;
    VOS_UINT16      usIpcpInfoLen = 0;
    VOS_UINT32      ulLocation = 0;
    VOS_UINT16      usCurPackLen = 0;
    VOS_UINT8 *     pucIpcpInfoBegin = pucIpcpInfo;

    pucIpcpInfo += 2;                /*����IPCP�ܳ����ֶ�2�ֽ�*/

    pucIpcpInfo += 1;                /*����IPCP�Ӱ������ֶ�1�ֽ�*/

    ulLocation += 1;                 /*����PCO�еĵ�һ���ֶ�:0x80*/

    while((ulLocation + 1) < pSmPco->ulPcoLen)
    {
        usCurPackLen = pSmPco->aucProtCfgOpt[ulLocation + 2];

        if ( (0x80 == pSmPco->aucProtCfgOpt[ulLocation])
             && (0x21 == pSmPco->aucProtCfgOpt[ulLocation + 1]) )
        {
            ucSubPackNum++;
            usIpcpInfoLen += usCurPackLen;

            /*lint -e961*/
            *pucIpcpInfo++ = ((0xFF00 & usCurPackLen) >> 8);
            *pucIpcpInfo++ = (0xFF & usCurPackLen);
            /*lint +e961*/

            /*�����Ӱ�����:*/
            PS_MEM_CPY(pucIpcpInfo, &(pSmPco->aucProtCfgOpt[ulLocation + 3]), usCurPackLen);

            pucIpcpInfo += usCurPackLen;
        }

        ulLocation += 2 + 1 + usCurPackLen;
    }

    /*ͳ���ϱ��¼��е�PCO��IPCP��Ϣ�ܳ���:*/
    usIpcpInfoLen += 1 + (ucSubPackNum * 2);

    /*lint -e961*/
    /*��дPCO��IPCP��Ϣ�ܳ����ֶ�:*/
    *pucIpcpInfoBegin++ = ((0xFF00 & usIpcpInfoLen) >> 8);
    *pucIpcpInfoBegin++ = (0xFF & usIpcpInfoLen);
    /*lint +e961*/

    /*��д�Ӱ�����:*/
    *pucIpcpInfoBegin = ucSubPackNum;

    return;
}

/*****************************************************************************
 �� �� ��  : Aps_SetEvtAddr
 ��������  : �����ϱ��¼��е�PDP ADDRESS
 �������  : ucPdpId      - PDPʵ������
             pstPsCallEvt - �ϱ��¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005
    ��    ��   : ��³��
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��4��19��
    ��    ��   : S62952
    �޸�����   : ����IPV6��ַ�Ĵ���

  3.��    ��   : 2012��11��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012111205973: LTEĬ��ȱʡ����IP����IPv4v6, �û�����IP��
                 ��IPv4 only��IPv6 only, ȱʡ����IP���ͱ�������޸�Ϊ�û���
                 ��IP����

  4.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻

*****************************************************************************/
VOS_UINT32 Aps_SetEvtAddr(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr
)
{
    VOS_UINT32                          ulRelt;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    ulRelt = VOS_OK;

    if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {
        PS_MEM_CPY(pstPdpAddr->aucIpv4Addr,
                   pstPdpEntity->PdpAddr.aucIpAddr,
                   TAF_IPV4_ADDR_LEN);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {
        PS_MEM_CPY(pstPdpAddr->aucIpv6Addr,
                   pstPdpEntity->PdpAddr.aucIpV6Addr,
                   TAF_IPV6_ADDR_LEN);
    }
    else if (MN_APS_ADDR_IPV4V6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
    {
        PS_MEM_CPY(pstPdpAddr->aucIpv4Addr,
                   pstPdpEntity->PdpAddr.aucIpAddr,
                   TAF_IPV4_ADDR_LEN);

        PS_MEM_CPY(pstPdpAddr->aucIpv6Addr,
                   pstPdpEntity->PdpAddr.aucIpV6Addr,
                   TAF_IPV6_ADDR_LEN);
    }
#endif
    else
    {
        ulRelt = VOS_ERR;
    }

    return ulRelt;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/*****************************************************************************
 �� �� ��  : TAF_APS_SetEvtPcscf
 ��������  : ��дP-CSCF��Ϣ��PS�����¼�
 �������  : ucPdpId                - PDP ID
             pstPcscf               - IPv4Pcscf
             pstIpv6Pcscf           - IPv6Pcscf
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻
  3.��    ��   : 2014��02��14��
    ��    ��   : Y00213812
    �޸�����   : DTS2014031105153
  4.��    ��   : 2012��08��07��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2015031000157, ����������p-cscf��ַ
*****************************************************************************/
VOS_VOID TAF_APS_SetEvtPcscf(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_PCSCF_STRU                 *pstPcscf,
    TAF_PDP_IPV6_PCSCF_STRU            *pstIpv6Pcscf
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr)
    {
        pstPcscf->bitOpPrimPcscfAddr     = VOS_TRUE;
        PS_MEM_CPY(pstPcscf->aucPrimPcscfAddr,
                   pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pstPcscf->bitOpPrimPcscfAddr     = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr)
    {
        pstPcscf->bitOpSecPcscfAddr      = VOS_TRUE;
        PS_MEM_CPY(pstPcscf->aucSecPcscfAddr,
                   pstPdpEntity->stPdpPcscf.aucSecPcscfAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pstPcscf->bitOpSecPcscfAddr     = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpThiPcscfAddr)
    {
        pstPcscf->bitOpThiPcscfAddr      = VOS_TRUE;
        PS_MEM_CPY(pstPcscf->aucThiPcscfAddr,
                   pstPdpEntity->stPdpPcscf.aucThiPcscfAddr,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pstPcscf->bitOpThiPcscfAddr     = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        pstIpv6Pcscf->bitOpPrimPcscfAddr = VOS_TRUE;
        PS_MEM_CPY(pstIpv6Pcscf->aucPrimPcscfAddr,
                   pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        pstIpv6Pcscf->bitOpPrimPcscfAddr = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
    {
        pstIpv6Pcscf->bitOpSecPcscfAddr  = VOS_TRUE;
        PS_MEM_CPY(pstIpv6Pcscf->aucSecPcscfAddr,
                   pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        pstIpv6Pcscf->bitOpSecPcscfAddr  = VOS_FALSE;
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
    {
        pstIpv6Pcscf->bitOpThiPcscfAddr  = VOS_TRUE;
        PS_MEM_CPY(pstIpv6Pcscf->aucThiPcscfAddr,
                   pstPdpEntity->stPdpIpv6Pcscf.aucThiPcscfAddr,
                   TAF_IPV6_ADDR_LEN);
    }
    else
    {
        pstIpv6Pcscf->bitOpThiPcscfAddr  = VOS_FALSE;
    }

#endif

    return;
}

/*****************************************************************************
 Prototype      : Aps_DecideTransMode
 Description    :
 Input          : ---
 Output         : ---
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_DecideTransMode(VOS_UINT8                       ucPdpId,
                                RABM_TRANS_MODE_ENUM           *pTransMode   )
{
    if ( g_PdpEntity[ucPdpId].PdpQos.ucReliabClass
         < APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA)
    {
        *pTransMode             = RABM_ABM_ENUM;
    }
    else
    {
        *pTransMode             = RABM_ADM_ENUM;
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : MN_APS_Itoa
 ��������  : ����ת������(10��16), ������ת��ΪASCII��, �����������ַ���
 �������  : usValue    - ��ת��ΪASCII�������
             pcStr      - ���������ַ���
             usRadix    - ת������
 �������  : ��
 �� �� ֵ  : VOS_CHAR*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��7��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_CHAR* MN_APS_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
)
{
    if (usRadix == 16)
    {
        /*lint -e586*/
        pcStr += sprintf(pcStr, "%x", usValue);
        /*lint +e586*/
    }
    else if(usRadix == 10)
    {
        /*lint -e586*/
        pcStr += sprintf(pcStr, "%d", usValue);
        /*lint +e586*/
    }
    else
    {
    }

    return pcStr;
}

/*****************************************************************************
 �� �� ��  : MN_APS_ConvertIpv6AddrToStr
 ��������  : ��IPV6��ַ��ʽת��Ϊ�ַ�����ʽ
 �������  : aucIpAddr[]    - IPV6��ַ(Э���ʽ)
             enIpStrType    - IPV6�ַ�����ʽ�������
 �������  : aucAddrStr[]   - IPV6��ַ(�ַ�����ʽ)
 �� �� ֵ  : VOS_OK         - ת���ɹ�
             VOS_ERR        - ת��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��7��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_APS_ConvertIpv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    MN_APS_IPV6_STR_TYPE_ENUM_UINT8     enIpStrType
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT16                          ausAddrValue[MN_APS_IPV6_STR_MAX_TOKENS];
    VOS_UINT16                          usAddrNum;
    VOS_UINT8                           ucDelimiter;
    VOS_UINT8                           ucTokensNum;
    VOS_UINT8                           ucRadix;
    VOS_UINT32                          i;

    pucBuffer                           = aucAddrStr;

    PS_MEM_SET(ausAddrValue, 0x00, sizeof(ausAddrValue));

    /* ����IP�ַ�����ʽ�������, ���ö�Ӧ��ת������ */
    switch (enIpStrType)
    {
        case MN_APS_IPV6_STR_TYPE_HEX:
            ucDelimiter = MN_APS_IPV6_STR_DELIMITER;
            ucTokensNum = 8;
            ucRadix     = 16;
            break;

        case MN_APS_IPV6_STR_TYPE_DEC:
            ucDelimiter = MN_APS_IPV4_STR_DELIMITER;
            ucTokensNum = 16;
            ucRadix     = 10;
            break;

        default:
            MN_ERR_LOG1("MN_APS_ConvertIpv6AddrToStr: Wrong IPV6 string type:",
                        enIpStrType);
            return VOS_ERR;
    }
/*lint -e961*/
    /* ����IP�ַ�����ʽ�������, ��ȡ�ֶε�IP��ַ��ֵ */
    for (i = 0; i < ucTokensNum; i++)
    {
        usAddrNum = *aucIpAddr++;

        if (MN_APS_IPV6_STR_TYPE_HEX == enIpStrType)
        {
            usAddrNum <<= 8;
            usAddrNum  |= *aucIpAddr++;
        }

        ausAddrValue[i] = usAddrNum;
    }

    /* ����IP��ַ�ֶ�, �����зָ�����ǵ�IP��ַ�ַ��� */
    for (i=0; i < ucTokensNum; i++)
    {
        pucBuffer    = (VOS_UINT8*)MN_APS_Itoa(ausAddrValue[i],
                                               (VOS_CHAR*)pucBuffer,
                                               ucRadix);
        *pucBuffer++ = ucDelimiter;
    }

    /* ȡ�����һ���ָ���, �����ַ��������� */
    if (aucAddrStr != pucBuffer)
    {
        *(--pucBuffer) = '\0';
    }
/*lint +e961*/

    return VOS_OK;
}
#endif

/**********************************************************
 Function:       Taf_IpAddr2LenStr
 Description:    ��SMЭ��IP��ַ��ʽת��Ϊ�ַ���+ ���ȸ�ʽ��IP��ַ
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pucIpAddr - SMЭ�鶨���IP��ַ
 Output:         pucStr - �ַ�����ʽ��IP��ַ
 Return:
 Others:
**********************************************************/
VOS_VOID Taf_IpAddr2LenStr(CONST VOS_UINT8* pucIpAddr, VOS_UINT8 *pucStr)
{
    VOS_UINT8 i, j = 1;
    VOS_UINT8 ucHundred;
    VOS_UINT8 ucDecade;
    VOS_UINT8 ucSingle;

    for (i = 0; i < 4; i++)
    {
        ucHundred = pucIpAddr[i] / 100;
        ucDecade = (VOS_UINT8)((pucIpAddr[i] - (ucHundred * 100)) / 10);
        ucSingle = (VOS_UINT8)((pucIpAddr[i] - (ucHundred * 100)) - (ucDecade * 10));
        if (ucHundred != 0)
        {
            pucStr[j] = ucHundred + 0x30;  /*����λת��Ϊ�ַ�*/
            j++;
        }
        if ((0 != ucHundred) || (0 != ucDecade ))
        {
            pucStr[j] = ucDecade + 0x30;   /*��ʮλת��Ϊ�ַ�*/
            j++;
        }
        pucStr[j] = ucSingle + 0x30;       /*����λת��Ϊ�ַ�*/
        j++;
        /* mod by zzy,���һ��λ��ʱ��Ӧ������ţ������»�������� */
        if (i != 3)
        {
            pucStr[j] = '.';                   /*һ��λ�ν��������'.'��*/
        }
        j++;
    }
    pucStr[0] = j - 2; /*��������ַ����ĳ���*/
    return;
}

/**********************************************************
 Function:       Taf_Apn2Lenstr
 Description:    ��Э�鶨���APN��ʽת��Ϊ�ַ�����ʽ��APN
 Calls:          Taf_Apn2str
 Data Accessed:
 Data Updated:
 Input:          pucApn - Э�鶨���APN
 Output:         pucStr - �ַ�����ʽ��Apn
 Return:
 Others:
**********************************************************/
VOS_VOID Taf_Apn2Lenstr(VOS_UINT8* pucApn, VOS_UINT8 *pucStr)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucLabelLen = 0;

    if (0 == pucApn[0])
    {   /*APN����Ϊ0��ֱ�ӳ��ȸ�ֵ����*/
        pucStr[0] = 0;
        return;
    }
    ucLabelLen = pucApn[1]; /*��1��label�ĳ���*/
    for (i = 1; (i < pucApn[0]) && (i < TAF_MAX_APN_LEN); i++)
    {   /*�ӵ�1����Ч�ַ���ʼ���*/
        if (j < ucLabelLen)
        {   /*����ucLabelLen���ַ�*/
            pucStr[i] = pucApn[i + 1];
            j++;  /*��Ч�ַ�����1*/
        }
        else
        {   /*����һ��Label��Ϻ�׷��һ��'.'��*/
            pucStr[i] = '.';
            j = 0;     /*��ʼ��һ��Label�ĳ����ۼ�*/
            ucLabelLen = pucApn[i + 1]; /*ȡ��һ��label�ĳ���*/
        }
    }
    pucStr[0] = i - 1;  /*�ַ����ĳ���*/
    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/**********************************************************
 Function:     Taf_CheckActCid
 Description:  ���Cid�Ƿ����ڱ�ʹ��
 Calls:
 Data Accessed:
 Data Updated:
 Input:        ucCid - Cidֵ
 Output:
 Return:       TAF_TRUE  - ���ڱ�ʹ��
               TAF_FALSE - δ��ʹ��
 Others:
��1.��    ��  : 2011��12��22��
  ����    ��  : h44270
  ���޸�����  : ɾ��middle pdp id�ĸ���
**********************************************************/
VOS_UINT32 Taf_CheckActCid(VOS_UINT8 ucCid)
{
    VOS_UINT8 ucTi;

    for (ucTi = 0; ucTi < TAF_APS_MAX_PDPID; ucTi++)
    {
        if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucTi, ucCid))
         && (VOS_TRUE == g_PdpEntity[ucTi].ulUsedFlg))
        {
            /*Cid���ڱ�����*/
            return TAF_TRUE;
        }
    }
    return TAF_FALSE;
}


/*****************************************************************************
 Prototype      : Aps_Str2LenStr
 Description    : �����ַ������������ַ���ת��Ϊ�ַ�������+�ַ�������ʽ
 Input          : pStr
                  ulStrMaxLen:��ת�����ַ�������󳤶ȣ����ڱ��⿽��Խ��
 Output         : pLenStr
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_Str2LenStr(             VOS_UINT32          ulMaxStrLen,
                                        VOS_UINT8          *pStr,
                                        VOS_UINT8          *pLenStr )
{
    VOS_UINT32                          ulRealStrLen;
    VOS_UINT32                          ulTempAddr;

    ulRealStrLen                        = VOS_StrLen((VOS_CHAR *)pStr);

    /*���ʵ�ʳ��ȳ�����󳤶�,��ǿ�Ƹ�ֵΪ��󳤶�*/
    if (ulMaxStrLen < ulRealStrLen )
    {
        ulRealStrLen                    = ulMaxStrLen;
    }

    pLenStr[0]                          = (VOS_UINT8)ulRealStrLen;

    ulTempAddr = (VOS_UINT32)&pLenStr[1];
    PS_MEM_CPY((VOS_UINT32 *)ulTempAddr, pStr, ulRealStrLen);

    return;
}

/*****************************************************************************
 Prototype      : Aps_LenStr2Str
 Description    : ���ַ�������+�ַ�������ʽת��Ϊ���ַ������������ַ�����ʽ
 Input          : pLenStr
 Output         : pStr
 Return Value   : ---
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_LenStr2Str(             VOS_UINT8           ucMaxLen,
                                        VOS_UINT8          *pLenStr,
                                        VOS_UINT8          *pStr )
{
    VOS_UINT8                           ucRealLen;

    ucRealLen                           = pLenStr[0];

    if ( ucRealLen > ucMaxLen)
    {
        ucRealLen                       = ucMaxLen;
    }

    PS_MEM_CPY(pStr, &pLenStr[1], ucRealLen);

    pStr[ucRealLen]  = '\0';

    return;
}

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/**********************************************************
 Function:       Taf_PsParaSetResult
 Description:    TAF��APP����ͨ�Ų������ý��
 Calls:          TAFM module
 Data Accessed:
 Data Updated:
 Input:          ClientId - �ͻ��˱�ʶ
                 OpId - ������ʶ
                 Result - �������ý��
 Output:
 Return:
 Others:
1.��    ��   : 2011��10��19��
  ��    ��   : f00179208
  �޸�����   : AT��ֲ��Ŀ,CallBack������
**********************************************************/
VOS_VOID  Taf_PsParaSetResult(  VOS_UINT16           ClientId,
                            VOS_UINT8                  OpId,
                            TAF_PARA_SET_RESULT     Result,
                            TAF_PARA_TYPE           ParaType,
                            VOS_VOID                   *pPara )
{
    MN_SETPARA_SendMsg(ClientId,
                       OpId,
                       Result,
                       ParaType,
                       pPara);

    return;
}


/*****************************************************************************
 Prototype      : Aps_Option12Cids
 Description    : ����Ƿ�����ӿ��е�ȫ��12��CID
 Input          : pLenStr
 Output         : pStr
 Return Value   : APS_PARA_VALID
                  APS_PARA_INVALID
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_Option12Cids(           VOS_UINT8          *paucCid )
{
    VOS_UINT8                           ucCidLoc;
    VOS_UINT8                           ulCidFlg;

    ulCidFlg                            = TAF_CID_NUMS_INVALID;

    /*���ȫ������0��������12��PDP������ʧ��*/
    for (ucCidLoc = 0; ucCidLoc < (APS_PDP_MAX_CID+1); ucCidLoc ++)
    {
        if ( 0 == paucCid[ucCidLoc])
        {   /*��һ������0���򲻲���ȫ����12��CID*/
            ulCidFlg                    = TAF_CID_NUMS_VALID;
            break;
        }
    }

    return  ulCidFlg;
}


/*****************************************************************************
 Prototype      : Aps_Option0Cid
 Description    : ����Ƿ�����ӿ��е�ȫ��12��CID
 Input          : pLenStr
 Output         : pStr
 Return Value   : APS_PARA_VALID
                  APS_PARA_INVALID
 Data Accessed  :
 Data Update    :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_Option0Cid(             VOS_UINT8          *paucCid )
{
    VOS_UINT8                           ucCidLoc;
    VOS_UINT8                           ulCidFlg;

    ulCidFlg                            = TAF_CID_NUMS_INVALID;


    /*���ȫ������0��������0��PDP��Ҳ����ʧ��*/
    for (ucCidLoc = 0; ucCidLoc < (APS_PDP_MAX_CID+1); ucCidLoc ++)
    {
        if (0 != paucCid[ucCidLoc])
        {   /*��һ��������0,���������*/
            ulCidFlg                    = TAF_CID_NUMS_VALID;
            break;
        }
    }

    return  ulCidFlg;
}



/*****************************************************************************
 Prototype      : Aps_PowerOff()
 Description    : ��ػ������У����Ի�����Դ��������̬������ڴ��ʱ���ȡ�
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2006-09-14
    Author      : l47619
    Modification: �������ⵥ����:A32D05600
  2.Date        : 2007-06-06
    Author      : s62952
    Modification: �������ⵥ����:A32D11493
  3.Date        : 2007-09-21
    Author      : L47619
    Modification: �������ⵥ����:A32D12903
  4.Date        : 2008-01-01
    Author      : L47619
    Modification: �������ⵥ����:A32D14008

  5.��    ��   : 2011��12��13��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ�������½ӿ�ֹͣ����APS��ʱ��

  6.��    ��   : 2012��1��3��
    ��    ��   : A00165503
    �޸�����   : PS Project: �ͷ�NDʵ����Դ

  7.��    ��   : 2012��01��06��
    ��    ��   : h44270
    �޸�����   : modified by h44270 for ps project,ɾ��middle pdp id�ĸ���

  8.��    ��   : 2012��3��27��
    ��    ��   : A00165503
    �޸�����   : DTS2012032603652: Gģ����ػ�, APSδȥ����SNDCP

  9.��    ��   : 2012��5��15��
    ��    ��   : A00165503
    �޸�����   : DTS2012051402688: Gģ�����������Ϣ�󲦺�����, ʱ��С��10��
                 ��, ��������ʱû�н�������Ϣд��NV

  10.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_VOID    Aps_PowerOff(VOS_VOID)
{
    VOS_UINT8                   ucPdpId;
    TAF_APS_STA_ENUM_UINT32     enState;

    for ( ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++ )
    {
        enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if  ( TAF_APS_STA_INACTIVE != enState )
        {
            if ( (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrackFlag)
              && (VOS_TRUE == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot) )
            {
                (VOS_VOID)Aps_SmMsgModSnDeActInd(ucPdpId);
            }

            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_GMM_PS_DETACH);

            if (TAF_APS_RAT_TYPE_NULL != TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ���õ�ǰPSҵ�����ڵ�ģʽ */
                TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_NULL);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                /* ֪ͨ�ⲿģ�鵱ǰPSҵ�����ڵ�ģʽ */
                TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_NULL);

                /* ֪ͨPPPC����ȥ���� */
                if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
                {
                    TAF_APS_SndPppDeactInd(ucPdpId);
                }
#endif
            }
        }
    }

    TAF_APS_SaveDsFlowInfoToNv();

    TAF_APS_ReleaseDfs();

#if (FEATURE_ON == FEATURE_IPV6)
    TAF_APS_SndNdRelInd();
#endif

    /* ֹͣ���ж�ʱ��*/
    TAF_APS_StopAllTimer();

    /*���ó�ʼ������:*/
    Aps_PdpEntityInit();

    /* APS CTXģ���ʼ�� */
    TAF_APS_InitCtx();

    /* �ػ����µı����ͷ�, ���ܲ�����������״̬������,
     * ��Ҫ����֪ͨһ��STK��ǰ��PS�����״̬
     */
    TAF_APS_SndStkPsCallEvent();

    return;
}

/*****************************************************************************
 Prototype      : Aps_JudgeSapiValid()
 Description    : ԭ���ΪAPS_JUDGE_SAPI_VALID������GCF W��ģ���ԣ������·�
                  Wϵͳ�µ�SAPI==0��Ϊ����W��ģ�¶�SAPI����ʧ�ܣ��޸ĺ�Ϊһ
                  ������
 Input          : ucSapi
 Output         : 1:�����Ϸ�
                  0:�����Ƿ�
 Return Value   :
 Calls          :
 Called By      :
 History        :
  1.Date        : 2007-8-2
    Author      : hanlufeng 41410
    Modification: �������ⵥ����:A32D12649

  2.Date        : 2010-12-17
    Author      : A00165503
    Modification: ���ⵥ��: DTS2010120605160��W��ģ��PDP������޸�Ϊ˫ģ��
                  ��ѡ��G�������޷��ָ�

*****************************************************************************/
VOS_UINT32 Aps_JudgeSapiValid(VOS_UINT8 ucSapi)
{
    if (TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
    {
        /* ��ǰ�������ģʽΪGSMʱ���˲��� */
        if ( (APS_SAPI_3 == ucSapi)
          || (APS_SAPI_5 == ucSapi)
          || (APS_SAPI_9 == ucSapi)
          || (APS_SAPI_11 == ucSapi) )
        {
            return  APS_SAPI_VALID;
        }
        else
        {
            return  APS_SAPI_INVALID;
        }
    }
    else
    {
        return  APS_SAPI_VALID;
    }
}


/*******************************************************************************
  Module:      APS_LoadDefault
  Function:    APSģ��ָ���������
  Input:       None
  Output:      None
  NOTE:
  Return:      None
  History:
  1.  L47619      2008.08.20   �¹�����

  2.��    ��   : 2011��12��24��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ���ṹ̫�󣬸�Ϊ��̬�ڴ�����

  3.��    ��   : 2014��3��3��
    ��    ��   : A00165503
    �޸�����   : DTS2014030404070: APS���ؽṹ����NV�ṹ
*******************************************************************************/
VOS_VOID    Aps_LoadDefault(VOS_VOID)
{
    TAF_NV_PDP_TABLE_STRU  *psTmpPdpTbl;
    TAF_PS_ANSWER_MODE_STRU stTmpTelePara;
    TAF_UINT8               ucCid;
    TAF_UINT32              ulResult;

    /*Part 1: +CGEQREQ, +CGEQMIN, +CGTFT, +CGDCONT, +CGDSCONT, ^CGAUTH, ^CGDNS*/
    psTmpPdpTbl = (TAF_NV_PDP_TABLE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_NV_PDP_TABLE_STRU));

    if (VOS_NULL_PTR == psTmpPdpTbl)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "Aps_LoadDefault: Ps Mem Alloc Fail!");
        return;
    }

    PS_MEM_SET(psTmpPdpTbl , 0, sizeof(TAF_NV_PDP_TABLE_STRU));
    for (ucCid = 1 ; ucCid <= TAF_MAX_CID_NV; ucCid++)
    {
        ulResult = NV_Write((NV_ID_ENUM_U16)(en_NV_Item_Taf_PdpPara_0 + ucCid),
                             psTmpPdpTbl ,
                             sizeof(TAF_NV_PDP_TABLE_STRU));
        if (NV_OK != ulResult)
        {
            APS_WARN_LOG("Aps_LoadDefault:WARNING:NV_Write PDP Para FAIL!");
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, psTmpPdpTbl);

    /*Part 2: +CGAUTO*/
    PS_MEM_SET(&stTmpTelePara, 0, sizeof(TAF_PS_ANSWER_MODE_STRU));
    ulResult = NV_Write( en_NV_Item_PS_TelePara,
                         &stTmpTelePara,
                         sizeof(TAF_PS_ANSWER_MODE_STRU));
    if (NV_OK != ulResult)
    {
        APS_WARN_LOG("Aps_LoadDefault:WARNING:NV_Write PS_TelePara FAIL!");
    }

    return;
}


/*******************************************************************************
  Module:      Taf_ApsIsSndcpActive
  Function:    �ж�ָ����NSAPI����Ӧ��SNDCP�Ƿ��Ѿ�����
  Input:       VOS_UINT8  ucNsapi
  Output:      None
  NOTE:
  Return:      VOS_TRUE          \\ָ����NSAPI����Ӧ��SNDCP�Ѿ�����
               VOS_FALSE         \\ָ����NSAPI����Ӧ��SNDCPû�м���
  History:
  1.  L47619      2009.01.05   �¹�����
  2. ��    ��   : 2010��12��27��
     ��    ��   : h44270
     �޸�����   : Modified by PS Project, ��ѯ״̬�ĺ����޸�
  3. ��    ��   : 2012��01��06��
     ��    ��   : h444280
     �޸�����   : modified by h44270 for ps project,ɾ��middle pdp id�ĸ���
  4. ��    ��   : 2013��09��23��
     ��    ��   : z60575
     �޸�����   : DTS2013092205675, ��ȡģʽ
*******************************************************************************/
VOS_UINT32  Taf_ApsIsSndcpActive(VOS_UINT8  ucNsapi, RABM_TRANS_MODE_ENUM *penTransMode)
{
    VOS_UINT8   ucLoop;

    /*����ָ����CID�Ƿ��Ѽ���*/
    for (ucLoop = 0; ucLoop < TAF_APS_MAX_PDPID; ucLoop++)
    {
        if (VOS_TRUE == g_PdpEntity[ucLoop].ulUsedFlg)
        {
            if (ucNsapi == g_PdpEntity[ucLoop].ucNsapi)
            {
                if (APS_SNDCP_ACT == g_PdpEntity[ucLoop].PdpProcTrack.ucSNDCPActOrNot)
                {
                    *penTransMode = g_PdpEntity[ucLoop].GprsPara.TransMode;

                    return VOS_TRUE;
                }
                else
                {
                    return VOS_FALSE;
                }
            }
        }
    }

    return VOS_FALSE;
}


/*******************************************************************************
  Module:      TAF_DecodeMaxBitrateOfQos
  Function:    �������·���QoS��Ϣ�е�Maximum bit rate(uplink and downlink)
               ����Ϊʵ�ʵ���������
  Input:       ucMaxBitrateOfQos    Qos��Ϣ�е�ԭʼ���������ֽ�
               pulRealMaxBitrate    ������ʵ������������Ϣ
  Output:      None
  NOTE:
  Return:      VOS_OK   ����ɹ�
               VOS_ERR  ����ʧ��
  History:
      1.  L47619      2009.03.26   �ȱ�������
*******************************************************************************/
VOS_UINT32  TAF_DecodeMaxBitrateOfQos(VOS_UINT8   ucMaxBitrateOfQos,
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
                                                  VOS_UINT8   ucMaxBitrateOfQosExt,
#endif
                                                  VOS_UINT32  *pulRealMaxBitrate)
{
    if (VOS_NULL_PTR == pulRealMaxBitrate)
    {
        APS_WARN_LOG("TAF_DecodeMaxBitrateOfQos:WARNING:pulRealMaxBitrate is Null Ptr!");
        return VOS_ERR;
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (0 != ucMaxBitrateOfQosExt)
    {
        *pulRealMaxBitrate = (APS_APP_QOS_BIT_8600KBPS
             + (ucMaxBitrateOfQosExt * APS_3GPP_QOS_BIT_INC_100KBPS));
    }
    else
    #endif
    {
        if (APS_3GPP_QOS_BIT_0KBPS == ucMaxBitrateOfQos)
        {
            *pulRealMaxBitrate = APS_APP_QOS_BIT_0KBPS;
        }
        else if( ucMaxBitrateOfQos >= APS_3GPP_QOS_BIT_576KBPS)
        {
            *pulRealMaxBitrate
                =   ((ucMaxBitrateOfQos - APS_3GPP_QOS_BIT_576KBPS)
                  * APS_3GPP_QOS_BIT_INC_64KBPS)
                  + APS_APP_QOS_BIT_576KBPS;
        }
        else if (ucMaxBitrateOfQos >= APS_3GPP_QOS_BIT_64KBPS)
        {
            *pulRealMaxBitrate
                =   ((ucMaxBitrateOfQos - APS_3GPP_QOS_BIT_64KBPS)
                  * APS_3GPP_QOS_BIT_INC_8KBPS)
                  + APS_APP_QOS_BIT_64KBPS;
        }
        else
        {
            *pulRealMaxBitrate = (VOS_UINT32)ucMaxBitrateOfQos;
        }
    }

    return VOS_OK;
}


/*******************************************************************************
  Module:      TAF_EncodeMaxBitrateOfQos
  Function:    �������·���QoS��Ϣ�е�Maximum bit rate(uplink and downlink)
               ����Ϊʵ�ʵ���������
  Input:       ulRealMaxBitrate      ʵ������������Ϣ
               pucMaxBitrateOfQos    �����Qos��Ϣ�е����������ֽ�
  Output:      None
  NOTE:
  Return:      VOS_OK   ����ɹ�
               VOS_ERR  ����ʧ��
  History:
      1.  L47619      2009.03.26   �ȱ�������
*******************************************************************************/
VOS_UINT32  TAF_EncodeMaxBitrateOfQos(VOS_UINT32  ulRealMaxBitrate,
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
                                                  VOS_UINT8   *pucMaxBitrateOfQosExt,
#endif
                                                  VOS_UINT8   *pucMaxBitrateOfQos
                                                  )
{
    if (VOS_NULL_PTR == pucMaxBitrateOfQos)
    {
        APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:pucMaxBitrateOfQos is Null Ptr!");
        return VOS_ERR;
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
    {
        *pucMaxBitrateOfQosExt = 0;
    }
    #endif

    if(ulRealMaxBitrate == 0)
    {
        *pucMaxBitrateOfQos   = 255;  /*1 1 1 1 1 1 1 1*/
    }
    else if(ulRealMaxBitrate <= 63)
    {
        *pucMaxBitrateOfQos   = (VOS_UINT8)ulRealMaxBitrate;
    }
    else
    {
        if (ulRealMaxBitrate <= 568)
        {
            *pucMaxBitrateOfQos = (VOS_UINT8)(((ulRealMaxBitrate - 64) / 8) + 64);
        }
        else
        {
            if (ulRealMaxBitrate < 576)
            {
                *pucMaxBitrateOfQos = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (ulRealMaxBitrate <= 8640)
                {
                    *pucMaxBitrateOfQos = (VOS_UINT8)(((ulRealMaxBitrate - 576) / 64) + 128);
                }
                else
                {
                #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    *pucMaxBitrateOfQos = 254;  /*1 1 1 1 1 1 1 0*/
                #else
                    /* If the sending entity wants to indicate a Maximum bit rate for downlink */
                    /* higher than 8640 kbps, it shall set octet 9 to "11111110", i.e. 8640 kbps, */
                    /* and shall encode the value for the Maximum bit rate in octet 15. */
                    if (ulRealMaxBitrate < 8700)
                    {
                        *pucMaxBitrateOfQos = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        if (ulRealMaxBitrate <= 16000)
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt
                                    = (VOS_UINT8)((ulRealMaxBitrate - 8600) / 100);
                            }
                            else
                            {
                                /* Ϊ��ָ�룬��������MAX UL Bitrate������ֹ��R6Э�飬MAX UL Bitrate���ᳬ��8640��
                                        �ʽ�֮��Ϊ8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (ulRealMaxBitrate <= 128000)
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt
                                    = (VOS_UINT8)(((ulRealMaxBitrate - 16000) / 1000) + 74);
                            }
                            else
                            {
                                /* Ϊ��ָ�룬��������MAX UL Bitrate������ֹ��R6Э�飬MAX UL Bitrate���ᳬ��8640��
                                        �ʽ�֮��Ϊ8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                        else if (ulRealMaxBitrate <= 256000)
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt
                                    = (VOS_UINT8)(((ulRealMaxBitrate - 128000) / 2000) + 186);
                            }
                            else
                            {
                                /* Ϊ��ָ�룬��������MAX UL Bitrate������ֹ��R6Э�飬MAX UL Bitrate���ᳬ��8640��
                                        �ʽ�֮��Ϊ8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                    #endif
                        else
                        {
                            if (VOS_NULL_PTR != pucMaxBitrateOfQosExt)
                            {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt = 74;  /*0 1 0 0 1 0 1 0*/
                            #else
                                *pucMaxBitrateOfQos = 254;
                                *pucMaxBitrateOfQosExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                            }
                            else
                            {
                                /* Ϊ��ָ�룬��������MAX UL Bitrate������ֹ��R6Э�飬MAX UL Bitrate���ᳬ��8640��
                                        �ʽ�֮��Ϊ8640*/
                                APS_WARN_LOG("TAF_EncodeMaxBitrateOfQos:WARNING:ulRealMaxBitrate is beyond 8640!");
                                *pucMaxBitrateOfQos = 254;
                            }
                        }
                    }
                #endif
                }
            }
        }
    }

    return VOS_OK;
}

/*******************************************************************************
  Module:      Aps_UpdateWinsConfig
  Function:    �û�ͨ��AT��������WINSʱ��Ϊ�˱�֤������Ч������ͬ������g_ApsWins
  Input:       VOS_VOID
  Output:      None
  NOTE:
  Return:      None
  History:
      1.  L47619      2009.07.13   ����������:WINS
*******************************************************************************/
VOS_VOID    Aps_UpdateWinsConfig(VOS_UINT8 ucWins)
{
    if ((WINS_CONFIG_DISABLE != ucWins) && (WINS_CONFIG_ENABLE != ucWins))
    {
        /* ucWinsֵ��Ч */
        return;
    }

    /* ����g_ApsWins */
    g_ApsWins = ucWins;

    return;
}

/*******************************************************************************
 �� �� ��  : Aps_GetPdpContextInfo_ForActTypeAndNsapi
 ��������  : ��ѯPDP�����ĵļ������ͺͶ�Ӧ��Nsapi
 �������  : ucPdpId
             NAS_PDP_CONTEXT_STRU *
 �������  : ��
 �� �� ֵ  : None
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : Z00163274
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID Aps_GetPdpContextInfo_ForActTypeAndNsapi(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* ���PDP�������ͺͶ�Ӧ����PDP��Nsapi */
    if ( APS_PDP_ACT_PRI == g_PdpEntity[ucPdpId].ActType )
    {
        pstPdpCntxt->enActType = NAS_OM_PDP_ACT_PRI;
    }
    else if ( APS_PDP_ACT_SEC == g_PdpEntity[ucPdpId].ActType )
    {
        pstPdpCntxt->enActType = NAS_OM_PDP_ACT_SEC;
        pstPdpCntxt->ucLinkedNsapi = g_PdpEntity[ucPdpId].ucLinkedNsapi;
    }
    else
    {
        /*��ӡ������Ϣ---ActType����:*/
        APS_WARN_LOG("Aps_GetPdpContextInfo: ActType is error!");
    }

    return;
}

/*******************************************************************************
 �� �� ��  : Aps_GetPdpContextInfo_ForSapi
 ��������  : ��ѯPDP�����ĵ�Sapi
 �������  : ucPdpId
             NAS_PDP_CONTEXT_STRU *
 �������  : ��
 �� �� ֵ  : None
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : Z00163274
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID Aps_GetPdpContextInfo_ForSapi(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* ���Sapi */
    if ( VOS_TRUE == g_PdpEntity[ucPdpId].GprsPara.Op_Sapi )
    {
        pstPdpCntxt->ucPdpLlcSapi = g_PdpEntity[ucPdpId].GprsPara.ucSapi;
    }
    else
    {
        pstPdpCntxt->ucPdpLlcSapi = 0xFF;
    }

    return;
}

/*******************************************************************************
 �� �� ��  : Aps_GetPdpContextInfo_ForRadioPriority
 ��������  : ��ѯPDP�����ĵ�RadioPriority
 �������  : ucPdpId
             NAS_PDP_CONTEXT_STRU *
 �������  : ��
 �� �� ֵ  : None
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : Z00163274
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID Aps_GetPdpContextInfo_ForRadioPriority(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* ���RadioPriority */
    if ( VOS_TRUE == g_PdpEntity[ucPdpId].GprsPara.Op_RadioPriority )
    {
        pstPdpCntxt->ucPdpRadioPriority = g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority;
    }
    else
    {
        pstPdpCntxt->ucPdpRadioPriority = 0xFF;
    }

    return;
}


/*******************************************************************************
 �� �� ��  : Aps_GetPdpContextInfo_ForIpAddress
 ��������  : ��ѯPDP�����ĵ�IpAddress
 �������  : ucPdpId
             NAS_PDP_CONTEXT_STRU *
 �������  : ��
 �� �� ֵ  : None
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : Z00163274
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��20��
    ��    ��   : c00173809
    �޸�����   : ���ⵥ��DTS2011090904518:SDT����ʾ��IPV6��ַ����ȷ
  3.��    ��   : 2015��9��17��
    ��    ��   : zwx247453
    �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
*******************************************************************************/
VOS_VOID Aps_GetPdpContextInfo_ForIpAddress(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    /* Ϊ��OM�ܼ�����ʾδ���IPV6��IP��ַ����ʼ��ucPdpTypeΪ��Ч��IP��ַ���͡�
       ��Ϊ�ϰ汾�ýӿڻ��ʼ��ucPdpTypeΪ0�����°汾ucPdpTypeֵֻ��ȡ
       MN_APS_ADDR_BUTT��APS_ADDR_STATIC_IPV4��MN_APS_ADDR_IPV6��MN_APS_ADDR_IPV4V6
    */

    switch (g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
    {
        case APS_ADDR_STATIC_IPV4 :/* IPV4 */
            /* ���Ip��ַ */
            PS_MEM_CPY( pstPdpCntxt->aucIpAddr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                    4 );

            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
            pstPdpCntxt->enPdpType = APS_ADDR_STATIC_IPV4;
            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        /* IPV6 */
        case MN_APS_ADDR_IPV6:
            PS_MEM_CPY( pstPdpCntxt->aucIpv6Addr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpV6Addr,
                    TAF_IPV6_ADDR_LEN );

            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
            pstPdpCntxt->enPdpType = MN_APS_ADDR_IPV6;
            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

            break;

        /* IPV4V6 */
        case MN_APS_ADDR_IPV4V6:
            PS_MEM_CPY( pstPdpCntxt->aucIpAddr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                    4 );

            PS_MEM_CPY( pstPdpCntxt->aucIpv6Addr,
                    g_PdpEntity[ucPdpId].PdpAddr.aucIpV6Addr,
                    TAF_IPV6_ADDR_LEN );

            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
            pstPdpCntxt->enPdpType = MN_APS_ADDR_IPV4V6;
            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

            break;
#endif
        default:
            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
            pstPdpCntxt->enPdpType = APS_ADDR_STATIC_IPV4;
            /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
            break;
    }


    return;
}

/*******************************************************************************
 �� �� ��  : Aps_IsInvalidAlphaInApn
 ��������  : ��ѯApn�зǷ����ַ�'.'
 �������  : ucPdpId
             ulLoop
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : Z00163274
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_UINT32 Aps_IsInvalidAlphaInApn(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulLoop
)
{
    if (((g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] >= 'A')
          && (g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] <= 'Z'))
        || ((g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] >= 'a')
            && (g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] <= 'z'))
        || ((g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] >= '0')
            && (g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1] <= '9'))
        || ('-' == g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1]))
    {
        return TAF_APS_SUCC;
    }
    else
    {
        return TAF_APS_FAIL;
    }
}

/*******************************************************************************
 �� �� ��  : Aps_GetPdpContextInfo_ForApn
 ��������  : ��ѯPDP�����ĵ�Apn
 �������  : ucPdpId
             NAS_PDP_CONTEXT_STRU *
 �������  : ��
 �� �� ֵ  : None
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��18��
    ��    ��   : Z00163274
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID Aps_GetPdpContextInfo_ForApn(
    VOS_UINT8                           ucPdpId,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    VOS_UINT32                          ulLoop;
    /* ���APN */
    if ((g_PdpEntity[ucPdpId].PdpApn.ucLength <= (APS_MAX_LENGTH_OF_APN - 1))
        && (g_PdpEntity[ucPdpId].PdpApn.ucLength > 1))
    {
        pstPdpCntxt->ucApnLength = g_PdpEntity[ucPdpId].PdpApn.ucLength - 1;

        for (ulLoop = 0; ulLoop < pstPdpCntxt->ucApnLength; ulLoop++)
        {
            if (TAF_APS_SUCC == Aps_IsInvalidAlphaInApn(ucPdpId, ulLoop))
            {
                pstPdpCntxt->aucApn[ulLoop] = g_PdpEntity[ucPdpId].PdpApn.aucValue[ulLoop + 1];
            }
            else
            {
                pstPdpCntxt->aucApn[ulLoop] = '.';
            }
        }
    }
    else
    {
        /*��ӡ������Ϣ---ucApnLength����101:*/
        APS_WARN_LOG("Aps_GetPdpContextInfo: ucApnLength > 100");
    }

    return;
}

/*******************************************************************************
 �� �� ��  : Aps_GetPdpContextInfo
 ��������  : ��ѯPDP�����������Ϣ-��ά�ɲ�����
 �������  : ucNsapi
             NAS_PDP_CONTEXT_STRU *
 �������  : ��
 �� �� ֵ  : None
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��26��
    ��    ��   : L47619
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��01��06��
    ��    ��   : h444280
    �޸�����   : modified by h44270 for ps project,ɾ��middle pdp id�ĸ���
  3.��    ��   : 2015��9��17��
    ��    ��   : zwx247453
    �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
*******************************************************************************/
VOS_VOID Aps_GetPdpContextInfo(
    VOS_UINT8                           ucNsapi,
    NAS_PDP_CONTEXT_STRU                *pstPdpCntxt
)
{
    VOS_UINT8                           ucPdpId;

    PS_MEM_SET(pstPdpCntxt, 0, sizeof(NAS_PDP_CONTEXT_STRU));

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (ucNsapi == g_PdpEntity[ucPdpId].ucNsapi)
        {
        #if 0
            if ((APS_PDP_ACTIVE == g_PdpEntity[ucPdpId].EntityState)
                || (APS_PDP_MODIFY_PENDING == g_PdpEntity[ucPdpId].EntityState))
            {
        #endif
                /* ���PDP��NSAPI */
                pstPdpCntxt->ucNsapi = g_PdpEntity[ucPdpId].ucNsapi;

                /* ���PDP�����ĵ�״̬ */
                /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
                pstPdpCntxt->enActivePDPContexts = SM_OM_PDP_ACTIVATED;
                /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

                /* ���PDP�������ͺͶ�Ӧ����PDP��Nsapi */
                Aps_GetPdpContextInfo_ForActTypeAndNsapi(ucPdpId, pstPdpCntxt);

                /* ���Sapi */
                Aps_GetPdpContextInfo_ForSapi(ucPdpId, pstPdpCntxt);

                /* ���RadioPriority */
                Aps_GetPdpContextInfo_ForRadioPriority(ucPdpId, pstPdpCntxt);

                /* ���Ip��ַ */
                Aps_GetPdpContextInfo_ForIpAddress(ucPdpId, pstPdpCntxt);

                /* ���APN */
                Aps_GetPdpContextInfo_ForApn(ucPdpId, pstPdpCntxt);

                break;
        #if 0
            }
        #endif
        }
    }

    if (TAF_APS_MAX_PDPID == ucPdpId)
    {
        /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
        pstPdpCntxt->enActivePDPContexts = SM_OM_PDP_NOT_ACTIVATED;
        /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_FillCallEvtPdpAvtivateIndFromEsm
 ��������  : ��ESM����Ϣ���������ID_EVT_TAF_PS_CALL_PDP_ACTIVE_IND�¼�
 �������  : pstCallEvt                 - �������¼�ָ��
             pstEsmPdpManageInd         - ESM��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��EVENT�ṹ�滻������PID

  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

*****************************************************************************/
VOS_VOID TAF_APS_FillCallEvtPdpAvtivateIndFromEsm(
    TAF_PS_CALL_PDP_MANAGE_IND_STRU    *pstCallEvt,
    APP_ESM_PDP_MANAGER_IND_STRU       *pstEsmPdpManageInd
)
{

    /* ��ʼ���¼� */
    PS_MEM_SET(pstCallEvt, 0x00, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    /* ����¼����� */
    pstCallEvt->stCtrl.ulModuleId       = WUEPS_PID_AT;
    pstCallEvt->stCtrl.usClientId       = TAF_CLIENTID_BROADCAST;
    pstCallEvt->ucCid                   = (VOS_UINT8)pstEsmPdpManageInd->ulCid;

}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_FillEvtPdpType
 ��������  : ��дPS������¼���PDP����
 �������  : pstCallEvtInfo - PS������¼�
             ucPdpId        - ʵ������
 �������  : penPdpType
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��7��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��EVENT�ṹ�滻
*****************************************************************************/
VOS_VOID TAF_APS_FillEvtPdpType(
    TAF_PDP_TYPE_ENUM_UINT8            *penPdpType,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeRequest;

    enPdpTypeRequest = TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid);

    /*----------------------------------------------------------------------
       ���û�����IP����Ϊ��׼
       (1) IPv4v6����, �ϱ������¼���IP����Ϊ����IP����
       (2) ��������, �ϱ������¼���IP����Ϊ�û�����IP����
    ----------------------------------------------------------------------*/
#if (FEATURE_ON == FEATURE_IPV6)
    if (TAF_PDP_IPV4V6 == enPdpTypeRequest)
    {
        *penPdpType  = TAF_APS_ConvertPdpType(TAF_APS_GetPdpEntPdpAddrType(ucPdpId));
        return;
    }
#endif

    *penPdpType = enPdpTypeRequest;

    return;
}



/*lint +e958*/
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_SetEvtTftInfo
 ��������  : ��дTFT��Ϣ��PS�����¼�
 �������  : ucPdpId                - PDP ID
             pstTft                 - tft info
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��28��
    ��    ��   : W00316404
    �޸�����   : R11 TFT Э������
*****************************************************************************/
VOS_VOID TAF_APS_SetEvtTftInfo(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TFT_STRU                   *pstTft
)
{
    VOS_UINT32                          i;
    TAF_PDP_PF_STRU                    *pstTafPf = VOS_NULL_PTR;
    SM_ESM_PF_STRU                     *pstPdpPf = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstTft->ulPfNum = pstPdpEntity->stTft.ulPfNum;

    for (i = 0; i < pstTft->ulPfNum; i++)
    {
        pstTafPf = &pstTft->astPf[i];
        pstPdpPf = &pstPdpEntity->stTft.astCidPf[i].stPf;

        pstTafPf->bitOpRmtIpv4AddrAndMask = pstPdpPf->bitOpRmtIpv4AddrAndMask;
        pstTafPf->bitOpRmtIpv6AddrAndMask = pstPdpPf->bitOpRmtIpv6AddrAndMask;
        pstTafPf->bitOpProtocolId         = pstPdpPf->bitOpProtocolId;
        pstTafPf->bitOpSingleLocalPort    = pstPdpPf->bitOpSingleLocalPort;
        pstTafPf->bitOpLocalPortRange     = pstPdpPf->bitOpLocalPortRange;
        pstTafPf->bitOpSingleRemotePort   = pstPdpPf->bitOpSingleRemotePort;
        pstTafPf->bitOpRemotePortRange    = pstPdpPf->bitOpRemotePortRange;
        pstTafPf->bitOpSecuParaIndex      = pstPdpPf->bitOpSecuParaIndex;
        pstTafPf->bitOpTypeOfService      = pstPdpPf->bitOpTypeOfService;
        pstTafPf->bitOpFlowLabelType      = pstPdpPf->bitOpFlowLabelType;
        pstTafPf->bitOpLocalIpv4AddrAndMask = pstPdpPf->bitOpLocalIpv4AddrAndMask;
        pstTafPf->bitOpLocalIpv6AddrAndMask = pstPdpPf->bitOpLocalIpv6AddrAndMask;
        pstTafPf->bitOpSpare              = pstPdpPf->bitOpSpare;

        pstTafPf->ucPacketFilterId        = pstPdpPf->ucPacketFilterId;
        pstTafPf->ucNwPacketFilterId      = pstPdpPf->ucNwPacketFilterId;
        pstTafPf->enDirection             = pstPdpPf->enDirection;
        pstTafPf->ucPrecedence            = pstPdpPf->ucPrecedence;
        pstTafPf->ulSecuParaIndex         = pstPdpPf->ulSecuParaIndex;
        pstTafPf->usSingleLcPort          = pstPdpPf->usSingleLcPort;
        pstTafPf->usLcPortHighLimit       = pstPdpPf->usLcPortHighLimit;
        pstTafPf->usLcPortLowLimit        = pstPdpPf->usLcPortLowLimit;
        pstTafPf->usSingleRmtPort         = pstPdpPf->usSingleRmtPort;
        pstTafPf->usRmtPortHighLimit      = pstPdpPf->usRmtPortHighLimit;
        pstTafPf->usRmtPortLowLimit       = pstPdpPf->usRmtPortLowLimit;
        pstTafPf->ucProtocolId            = pstPdpPf->ucProtocolId;
        pstTafPf->ucTypeOfService         = pstPdpPf->ucTypeOfService;
        pstTafPf->ucTypeOfServiceMask     = pstPdpPf->ucTypeOfServiceMask;
        pstTafPf->ulFlowLabelType         = pstPdpPf->ulFlowLabelType;

        PS_MEM_CPY(pstTafPf->aucRmtIpv4Address, pstPdpPf->aucRmtIpv4Address, TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucRmtIpv4Mask,    pstPdpPf->aucRmtIpv4Mask,    TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucRmtIpv6Address, pstPdpPf->aucRmtIpv6Address, TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucRmtIpv6Mask,    pstPdpPf->aucRmtIpv6Mask,    TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucLocalIpv4Addr,  pstPdpPf->aucLocalIpv4Addr,  TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucLocalIpv4Mask,  pstPdpPf->aucLocalIpv4Mask,  TAF_IPV4_ADDR_LEN * sizeof(VOS_UINT8));
        PS_MEM_CPY(pstTafPf->aucLocalIpv6Addr,  pstPdpPf->aucLocalIpv6Addr,  TAF_IPV6_ADDR_LEN * sizeof(VOS_UINT8));
        pstTafPf->ucLocalIpv6Prefix = pstPdpPf->ucLocalIpv6Prefix;

    }

    return;
}
#endif

#if 0
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_APS_ProcCardReadFileCnf_CDMA_EFDGC
 ��������  : Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ProcCardReadFileCnf_CDMA_EFDGC(
    struct MsgCB                       *pstMsg
)
{
    /*
    Data dormant timer         : 1 byte
    EPZID Type Information     : 1 byte
    Hysteresis Activation Time : 1 byte
    */
    USIMM_READFILE_CNF_STRU            *pstFile  = VOS_NULL_PTR;
    VOS_UINT8                           uc1XPktDtInactivityTmrLen;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* �ж��ļ��Ķ�ȡ��� */
    if (VOS_OK != (pstFile->stCmdResult.ulResult))
    {
        /*����ʧ�ܣ���ȡNV */
        TAF_APS_Read1xPktDataInactivityTimeLenFromNv();

        return;
    }

    uc1XPktDtInactivityTmrLen = pstFile->aucEf[0];

    TAF_APS_SetPktCdataInactivityTimerLen(uc1XPktDtInactivityTmrLen);
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_ProcUsimMsg
 ��������  : Ԥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ProcUsimMsg(
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstFile;
    VOS_UINT32                          ulEfId;

    pstFile = (USIMM_READFILE_CNF_STRU *)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstFile->stFilePath.ulPathLen, pstFile->stFilePath.acPath, &ulEfId))
    {
        return;
    }

    switch (ulEfId)
    {
        case USIMM_CDMA_EFDGC_ID:
        case USIMM_CSIM_EFDGC_ID:
            TAF_APS_ProcCardReadFileCnf_CDMA_EFDGC(pstMsg);
            break;
        default:

            break;

    }

    return;
}
#endif
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_SnDataReq
 ��������  : �������ݸ�SNDCP
 �������  : VOS_UINT8 ucMode
             VOS_UINT8 ucNsapi
             VOS_UINT32 ulLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : t00148005
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SnDataReq(VOS_UINT8 ucMode, VOS_UINT8 ucNsapi, VOS_UINT32 ulLen)
{
    VOS_VOID                           *pData = VOS_NULL_PTR;
    SN_DATA_REQ_ST                      stSnDataReq;
    SN_UNITDATA_REQ_ST                  stSnUnitDataReq;
    VOS_UINT16                          i;

    PS_MEM_SET(&stSnDataReq, 0, sizeof(SN_DATA_REQ_ST));
    PS_MEM_SET(&stSnUnitDataReq, 0, sizeof(SN_UNITDATA_REQ_ST));

    pData = PS_MEM_ALLOC(WUEPS_PID_TAF, ulLen);
    if (VOS_NULL_PTR == pData)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: alloc memory failed! ");
        return;
    }

    if (0 == ucMode)
    {
        stSnUnitDataReq.ucNsapi     = ucNsapi;
        stSnUnitDataReq.usDataLen   = (VOS_UINT16)ulLen;
        stSnUnitDataReq.pPdu        = pData;

        for (i = 0; i < stSnUnitDataReq.usDataLen; i++)
        {
            *((VOS_UINT8*)(stSnUnitDataReq.pPdu) + i) = 5;
        }

        if (VOS_OK != SN_UnitDataReq(&stSnUnitDataReq))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: SN_UnitDataReq ERROR! ");
        }
    }
    else
    {
        stSnDataReq.ucNsapi         = ucNsapi;
        stSnDataReq.ucMask          = 0;
        stSnDataReq.usDataLen       = (VOS_UINT16)ulLen;
        stSnDataReq.pPdu            = pData;

        for (i = 0; i < stSnDataReq.usDataLen; i++)
        {
            *((VOS_UINT8*)(stSnDataReq.pPdu) + i) = 5;
        }

        if (VOS_OK != SN_DataReq(&stSnDataReq))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: SN_DataReq ERROR! ");
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pData);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GprsDataReqTimeoutFunc
 ��������  : VOS_StartCallBackRelTimer�ص�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : t00148005
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GprsDataReqTimeoutFunc(VOS_VOID)
{
    TAF_APS_GPRS_DATA_STRU             *pstDataReq = &g_stGprsDataReq;

    /* ����һ������ */
    TAF_APS_SnDataReq(pstDataReq->ucMode, pstDataReq->ucNsapi, pstDataReq->ulLen);

    pstDataReq->usSendTimes--;
    if (pstDataReq->usSendTimes > 0)
    {
        (VOS_VOID)VOS_StartCallBackRelTimer(&g_hGprsDataReqTimer,
                                             WUEPS_PID_TAF,
                                             pstDataReq->ulMillSecs,
                                             0,
                                             0,
                                             VOS_RELTIMER_NOLOOP,
                                             (REL_TIMER_FUNC)TAF_APS_GprsDataReqTimeoutFunc,
                                             VOS_TIMER_PRECISION_5);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GprsDataReq
 ��������  : GCF�������ݷ��ʹ�׮����
 �������  : VOS_UINT8 ucMode
             VOS_UINT8 ucNsapi
             VOS_UINT32 ulLen
             VOS_UINT8 ucTimes
             VOS_UINT32 ulMillSecs
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : t00148005
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GprsDataReq(
    VOS_UINT8                           ucMode,
    VOS_UINT8                           ucNsapi,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucTimes,
    VOS_UINT32                          ulMillSecs
)
{
    TAF_APS_GPRS_DATA_STRU             *pstDataReq = &g_stGprsDataReq;

    if (0 == ucTimes)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SnDataReq: Invalid times, times = 0! ");
        return;
    }

    pstDataReq->ucMode        = ucMode;
    pstDataReq->ucNsapi       = ucNsapi;
    pstDataReq->ulLen         = ulLen;
    pstDataReq->usSendTimes   = ucTimes;
    pstDataReq->ulMillSecs    = ulMillSecs;

    /* ����һ������ */
    TAF_APS_SnDataReq(ucMode, ucNsapi, ulLen);

    pstDataReq->usSendTimes--;
    if (pstDataReq->usSendTimes > 0)
    {
        (VOS_VOID)VOS_StartCallBackRelTimer(&g_hGprsDataReqTimer,
                                             WUEPS_PID_TAF,
                                             ulMillSecs,
                                             0,
                                             0,
                                             VOS_RELTIMER_NOLOOP,
                                             (REL_TIMER_FUNC)TAF_APS_GprsDataReqTimeoutFunc,
                                             VOS_TIMER_PRECISION_5);
    }
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

