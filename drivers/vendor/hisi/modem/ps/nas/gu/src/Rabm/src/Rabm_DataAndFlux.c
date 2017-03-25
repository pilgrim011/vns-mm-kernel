/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_DataAndFlux.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : ��C�ļ�������R_DataAndFluxģ���ʵ��
  Function List:
        1. NAS_RabmAppDataTransReq
        2. NAS_RabmSnDataReq
        5. Taf_RabmFlowClear
        6. NAS_RabmFlowClearTotal
        7. NAS_RabmFlowClearWithRabId
        8. Taf_RabmFlowQuery
        9. NAS_RabmFlowQueryAccumulate
        10.NAS_RabmFlowQueryWithRabId
        11.NAS_RabmFlowQueryTotal
        12.NAS_RabmFlowReport
        13.NAS_RabmFlowReportAccumulate
        14.NAS_RabmFlowReportWithRabId
        15.NAS_RabmFlowReportTotal
        16.NAS_RabmSetFlowReportMode
        17.Taf_RabmStartFlowReport
        18.Taf_RabmStopFlowReport
        19.NAS_RabmCalculateFluxRate
        20.NAS_Rabm64BitsDivide32Bits

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create
  2.Date        : 2006-03-08
    Author      : l47619
    Modification: ���ⵥ: A32D02344
  3.Date        : 2006-05-05
    Author      : l47619
    Modification: ���ⵥ: A32D03487
  4.Date        : 2007-10-16
    Author      : F62575
    Modification: ���ⵥA32D13062(�ĵ�У�Է�������)
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"
#include "NasRabmMain.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_DATAANDFLUX_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/




/*****************************************************************************
 Prototype      : NAS_RabmAppDataTransReq()
 Description    : APP���ô˺��������������ݣ�RABM���ݵ�ǰϵͳ����ѡ��:
                  ��Ϊ3G�������3G�е�Api_AppRabmDataReq()�������д���
                  ��Ϊ2G, �����SNDCP �ṩ�ĺ������д���
 Input          : pRabmDataReq        �����û������ݽṹ��ָ��
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
  2.Date        : 2006-05-05
    Author      : l47619
    Modification: �������ⵥ�޸�:A32D03487

  3.��    ��   : 2010��4��22��
    ��    ��   : o00132663
    �޸�����   : AT2D18350, GCF 14.2.4 ���ز���ʧ��
*****************************************************************************/
VOS_VOID  NAS_RabmAppDataTransReq( ST_APP_RABM_DATA  *pRabmDataReq )
{
    TTF_MEM_ST * pstData;

    /*�����ڲ����Ƿ�Ϸ�:*/
    if ( VOS_NULL_PTR == pRabmDataReq )
    {
        /*��ӡ������Ϣ---��ڲ����Ƿ�:*/
        RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( VOS_NULL_PTR == pRabmDataReq->pucData )
    {
        /*��ӡ������Ϣ---��ڲ����е�ָ��Ϊ��:*/
        RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:The pucData Pointer item of the Entry Parameter is NULL!" );
        return;
    }

    if( pRabmDataReq->ucDomain == D_RABM_PS_DOMAIN )
    {
        if ( ( pRabmDataReq->ucRabId < RABM_MIN_NSAPI_NUMBER )
             || ( pRabmDataReq->ucRabId > RABM_MAX_NSAPI_NUMBER ) )
        {
            /*��ӡ������Ϣ---��ڲ����е�RABID������Χ:*/
            RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:The NSAPI item of the Entry Parameter is BEYOND range!" );
            return;
        }
    }

    if ( ( pRabmDataReq->ucDomain != D_RABM_CS_DOMAIN )
        && ( pRabmDataReq->ucDomain != D_RABM_PS_DOMAIN ) )
    {
        /*��ӡ������Ϣ---��ڲ����е�CN���ֶβ���ȷ:*/
        RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:The DOMAIN item of the Entry Parameter is Error!" );
        return;
    }

    if (D_RABM_CS_DOMAIN == pRabmDataReq->ucDomain)     /*CS������*/
    {
        /*ִ��3G��CS�����ݷ��Ͳ���(�ú��������ݴ��������Ϣ��ʽ���͸�RABM):*/
        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
        {
            Api_AppRabmDataReq(pRabmDataReq);
            return;
        }
        else
        {
            /*��ӡ������Ϣ---2Gģʽ�£�RABM������CS������:*/
            RABM_LOG_WARNING( "NAS_RabmAppDataTransReq:WARNING:RABM doesn't process CS Domain data in 2G mode!" );
            return;
        }
    }

    /*�������ڴ�ת��Ϊ�㿽���ڴ�*/
    pstData = TTF_MemBlkCopyAlloc(WUEPS_PID_RABM, TTF_MEM_POOL_ID_UL_RLC_SDU, pRabmDataReq->pucData, (VOS_UINT16)pRabmDataReq->ulDataLen);
    if(VOS_NULL_PTR == pstData)
    {
        RABM_LOG_ERROR( "NAS_RabmAppDataTransReq:ERROR:The Alloc TTF mem fail!" );
        return;
    }

    /*������������(GNA/API��Ӧ��)*/
    RABM_SendUlData(pRabmDataReq->ucRabId, pstData);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_RabmRcvTafGprsPsDataReq
 ��������  : RABM����APP���͵�����������ϢRABM_TAF_GPRS_PS_DATA_REQ_MSG_TYPE
 �������  : TAFRABM_PS_DATA_REQ_STRU *pPsDataReqMsg - �����û���������Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��03��06��
    ��    ��   : L47619
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��11��26��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2010112505628
                 G�����������н�������ҵ������ҵ����������������Իָ���
  3.��    ��   : 2011��12��8��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�DTS2011111603445,���յ�ϵͳ��Ϣ���Ҳ�2�Ѿ�ָ�ɺ���ָܻ�RABM

*****************************************************************************/
VOS_VOID  NAS_RabmRcvTafGprsPsDataReq(TAFRABM_PS_DATA_REQ_STRU *pPsDataReqMsg)
{
    RABM_NSAPI_ENUM                     NsapiIndex;
    ST_APP_RABM_ERROR                   stReportError;
    ST_APP_RABM_STATUS                  stReportStatus;

    /*�����ڲ����Ƿ�Ϸ�:*/
    if ( VOS_NULL_PTR == pPsDataReqMsg )
    {
        /*��ӡ������Ϣ---��ڲ����Ƿ�:*/
        RABM_LOG_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( VOS_NULL_PTR == pPsDataReqMsg->pData )
    {
        /*��ӡ������Ϣ---��ڲ����е�ָ��Ϊ��:*/
        RABM_LOG_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:The pstData Pointer item of the Entry Parameter is NULL!" );
        return;
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pPsDataReqMsg->ulNsapi - RABM_2G_NSAPI_OFFSET );

    switch ( gastRabm2GEntity[NsapiIndex].State )
    {
        case RABM_2G_NULL:
            /*��ӡ������Ϣ---��ʱ���ܴ����û�������:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_2G_NULL state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*RABM��APP�ϱ�������Ϣ:*/
            stReportError.ucDomain  = D_RABM_PS_DOMAIN;
            stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
            stReportError.ucErrType = TAF_DATA_CAUSE_LOWLAYER_INDICATION;
            Api_AppRabmErrInd( &stReportError );
            /*��ӡ������Ϣ---�ϱ��˳�����Ϣ:*/
            RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*ֱ�Ӷ������������ݿ�:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            return;
        case RABM_NSAPI_OK_TRANSMODE_NO:
            /*��ӡ������Ϣ---��ʱ���ܴ����û�������:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_NSAPI_OK_TRANSMODE_NO state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*RABM��APP�ϱ�������Ϣ:*/
            stReportError.ucDomain  = D_RABM_PS_DOMAIN;
            stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
            stReportError.ucErrType = TAF_DATA_CAUSE_NO_TRANSMODE;
            Api_AppRabmErrInd( &stReportError );
            /*��ӡ������Ϣ---�ϱ��˳�����Ϣ:*/
            RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*ֱ�Ӷ������������ݿ�:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            return;
        case RABM_ROUT_AREA_UPDATE:
            if ( ( RABM_RA_UPDATE_CAUSE_NORMAL != gastRabm2GEntity[NsapiIndex].RAUpdateCause )
                 && ( RABM_RA_UPDATE_CAUSE_3G_TO_2G != gastRabm2GEntity[NsapiIndex].RAUpdateCause ) )
            {
                /*��ӡ������Ϣ---·��������ԭ��ֵ����:*/
                RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RA update cause is ERROR!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*��ӡ������Ϣ---��ʱ���ܴ����û�������:*/
                RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_ROUT_AREA_UPDATE(RA update cause is ERROR) state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*RABM��APP�ϱ�������Ϣ:*/
                stReportError.ucDomain  = D_RABM_PS_DOMAIN;
                stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
                stReportError.ucErrType = TAF_DATA_CAUSE_LOWLAYER_INDICATION;
                Api_AppRabmErrInd( &stReportError );
                /*��ӡ������Ϣ---�ϱ��˳�����Ϣ:*/
                RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*ֱ�Ӷ������������ݿ�:*/
                TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
                return;
            }

            if ( RABM_RA_UPDATE_CAUSE_3G_TO_2G == gastRabm2GEntity[NsapiIndex].RAUpdateCause )
            {
                /*��ӡ������Ϣ---��ʱ���ܴ����û�������:*/
                RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM_ROUT_AREA_UPDATE(RA update cause is RABM_RA_UPDATE_CAUSE_3G_TO_2G)state CAN'T send user data!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*RABM��APP�ϱ�������Ϣ:*/
                stReportError.ucDomain  = D_RABM_PS_DOMAIN;
                stReportError.ucRabId   = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
                stReportError.ucErrType = TAF_DATA_CAUSE_3G_TO_2G_RA_UPDATE;
                Api_AppRabmErrInd( &stReportError );
                /*��ӡ������Ϣ---�ϱ��˳�����Ϣ:*/
                RABM_LOG1_NORMAL( "NAS_RabmRcvTafGprsPsDataReq:NORMAL:Report ERROR info to APP!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

                /*ֱ�Ӷ������������ݿ�:*/
                TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
                return;
            }

            /*2G�е�·�������£������������ݷ��ͽӿ�:*/
            (VOS_VOID)RABM_SndSndcpUlDataCallBack((VOS_UINT8)(pPsDataReqMsg->ulNsapi),
                                        (VOS_UINT8)(pPsDataReqMsg->ulNsapi),
                                        pPsDataReqMsg->pData);

            break;

        case RABM_DATA_TRANS_STOP:
            /*��APP�ϱ�TAFRABM_STARTSTOP_IND(STOP)��Ϣ:*/
            stReportStatus.ucDomain     = D_RABM_PS_DOMAIN;
            stReportStatus.ucRabId      = (VOS_UINT8)(pPsDataReqMsg->ulNsapi);
            stReportStatus.ucStatus     = TAF_RABM_STOP_DATA;
            stReportStatus.ucStartCause = TAF_RABM_STOP_CAUSE_NORMAL;
            Api_AppRabmStatusInd( &stReportStatus );             /*֪ͨAPPֹͣ���ݴ���*/
            /*��ӡ������Ϣ---�ϱ�����Ϣ:*/
            RABM_LOG1_NORMAL( "STATE RABM_DATA_TRANS_STOP state report TAFRABM_STARTSTOP_IND(STOP) msg to APP: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*ֱ�Ӷ������������ݿ�:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);

            break;

        case RABM_DATA_TRANS_READY:
            /*��ӡ������Ϣ---��״̬��RABM�յ��������쳣��:*/
            RABM_LOG1_WARNING( "NAS_RabmRcvTafGprsPsDataReq:WARNING:RABM RCV UL Data in RABM_DATA_TRANS_READY State Is Abnormal!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*ֱ�Ӷ������������ݿ�:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            break;
        default:
            /*��ӡ������Ϣ---��NSAPI����Ӧ��״̬����:*/
            RABM_LOG1_ERROR( "NAS_RabmRcvTafGprsPsDataReq:ERROR:This NSAPI's state is WRONG!: NSAPI:", (VOS_INT32)pPsDataReqMsg->ulNsapi );

            /*ֱ�Ӷ������������ݿ�:*/
            TTF_MemFree(WUEPS_PID_RABM, pPsDataReqMsg->pData);
            break;
    }
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
