/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_ApsTransmodeSet.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : ��C�ļ�������R_APSģ���ʵ��
  Function List:
        1.NAS_RabmSetTransMode
        2.NAS_RabmTransModeError

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create

************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"


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
#define    THIS_FILE_ID        PS_FILE_ID_RABM_APSTRANSMODESET_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 Prototype      : NAS_RabmSetTransMode()
 Description    : APS����RABM���ݴ���ģʽ
 Input          : pSetTransMode        ����ģʽ���ָ��
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function

  2.��    ��   : 2011��12��23��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��֪ͨCDS���Է�������
  3.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��
*****************************************************************************/
VOS_VOID  NAS_RabmSetTransMode( RABM_APS_SET_TRANS_MODE_ST   *pSetTransMode )
{
    RABM_TRANSMODE_LEGITIMACY_ENUM      LegitimacyFlag = RABM_TRANSMODE_LEGAL;             /*��ڲ����Ĵ���ģʽ�ֶκϷ��Ա��*/
    RABM_NSAPI_ENUM                     NsapiIndex;

    /*�����ڲ����Ƿ�Ϸ�:*/
    if ( VOS_NULL_PTR == pSetTransMode )
    {
        /*��ӡ������Ϣ---���ָ��Ϊ��:*/
        RABM_LOG_WARNING( "NAS_RabmSetTransMode:WARNING:Entry Pointer is NULL!" );
        return;
    }

    if ( ( pSetTransMode->ucNsapi < RABM_MIN_NSAPI_NUMBER )
         || ( pSetTransMode->ucNsapi > RABM_MAX_NSAPI_NUMBER ) )
    {
        /*��ӡ������Ϣ---��ڲ�����NSAPI������Χ:*/
        RABM_LOG_WARNING( "NAS_RabmSetTransMode:WARNING:The NSAPI of the Input Parameter is BEYOND range!" );
        return;
    }

    /*��ӡ������Ϣ---���ô���ģʽ:*/
    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Set Transmode: NSAPI:", pSetTransMode->ucNsapi );

    if ( ( RABM_ABM_ENUM != pSetTransMode->TransMode )
         && ( RABM_ADM_ENUM != pSetTransMode->TransMode ) )        /*����ģʽ�������Ϸ�*/
    {
        LegitimacyFlag = RABM_TRANSMODE_ILLEGAL;
        /*��ӡ������Ϣ---����ģʽ�������Ϸ�:*/
        RABM_LOG1_WARNING( "NAS_RabmSetTransMode:WARNING:The Transmode of the Input Parameter is ILLEGAL!: NSAPI:", pSetTransMode->ucNsapi );
    }

    NsapiIndex = ( RABM_NSAPI_ENUM )( pSetTransMode->ucNsapi - RABM_2G_NSAPI_OFFSET );

    switch ( gastRabm2GEntity[NsapiIndex].State )    /*ָ����NSAPI����Ӧ��RABMʵ���״̬*/
    {
        case RABM_2G_NULL:
            /*��ӡ������Ϣ---�����߼����¼�:*/
            RABM_LOG1_WARNING( "NAS_RabmSetTransMode:WARNING:RABM_2G_NULL State CAN'T set Transmode!: NSAPI:", pSetTransMode->ucNsapi );
            return;
        case RABM_NSAPI_OK_TRANSMODE_NO:
            if ( RABM_ACT_REQ_T1_ON == gaRabmActReqT1Switch[NsapiIndex] )    /*������Rabm.act.req.T1��ʱ��*/
            {
                /*�ر�Rabm.act.req.T1��ʱ��:*/
                NAS_RabmStopTimer( ( RABM_TIMER_NAME_ENUM )NsapiIndex, RABM_TIMER_PARA_ACT_REQ_T1 );
            }

            if ( RABM_TRANSMODE_ILLEGAL == LegitimacyFlag )                /*����ģʽ���Ϸ�*/
            {
                NAS_RabmTransModeError( pSetTransMode->ucNsapi );

                /*��ӡ������Ϣ---����Ϊ��ȷ��ģʽ:*/
                RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode set to ADM: NSAPI:", pSetTransMode->ucNsapi );

                /*����RABM-DATA-TRANS-READY״̬:*/
                RABM_SetGState(NsapiIndex,RABM_DATA_TRANS_READY);
                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", pSetTransMode->ucNsapi );
            }
            else
            {
                gastRabm2GEntity[NsapiIndex].TransMode = pSetTransMode->TransMode; /*����TRANSMODE*/

                if ( RABM_ABM_ENUM == pSetTransMode->TransMode )
                {
                    /*��ӡ������Ϣ---����Ϊȷ��ģʽ:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode set to ABM: NSAPI:", pSetTransMode->ucNsapi );
                }
                else
                {
                    /*��ӡ������Ϣ---����Ϊ��ȷ��ģʽ:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode set to ADM: NSAPI:", pSetTransMode->ucNsapi );
                }

                /*����RABM-DATA-TRANS-READY״̬:*/
                RABM_SetGState(NsapiIndex,RABM_DATA_TRANS_READY);

                /*��ӡ������Ϣ---״̬�л�:*/
                RABM_LOG1_NORMAL( "STATE RABM_NSAPI_OK_TRANSMODE_NO state CHANGE TO RABM_DATA_TRANS_READY state: NSAPI:", pSetTransMode->ucNsapi );
            }


            /* ֪ͨCDS���Է������� */
            NAS_RABM_SndCdsSendBuffDataInd(pSetTransMode->ucNsapi,
                                           CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);



            break;
        case RABM_ROUT_AREA_UPDATE:
            /*��ӡ������Ϣ---�����߼����¼�:*/
            RABM_LOG1_WARNING( "NAS_RabmSetTransMode:WARNING:RABM_ROUT_AREA_UPDATE State CAN'T set Transmode!: NSAPI:", pSetTransMode->ucNsapi );
            return;
        case RABM_DATA_TRANS_READY:
        case RABM_DATA_TRANS_STOP:                          /*������״̬�£�������PDP�޸ģ�����һ��*/
            if ( RABM_TRANSMODE_ILLEGAL == LegitimacyFlag ) /*����ģʽ���Ϸ�*/
            {
                NAS_RabmTransModeError( pSetTransMode->ucNsapi );
                /*��ӡ������Ϣ---�޸�Ϊ��ȷ��ģʽ:*/
                RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode modify to ADM: NSAPI:", pSetTransMode->ucNsapi );
            }
            else
            {
                gastRabm2GEntity[NsapiIndex].TransMode = pSetTransMode->TransMode; /*����TRANSMODE*/

                if ( RABM_ABM_ENUM == pSetTransMode->TransMode )
                {
                    /*��ӡ������Ϣ---�޸�Ϊȷ��ģʽ:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode modify to ABM: NSAPI:", pSetTransMode->ucNsapi );
                }
                else
                {
                    /*��ӡ������Ϣ---�޸�Ϊ��ȷ��ģʽ:*/
                    RABM_LOG1_NORMAL( "NAS_RabmSetTransMode:NORMAL:Transmode modify to ADM: NSAPI:", pSetTransMode->ucNsapi );
                }
            }
            break;
        default:
            /*��ӡ������Ϣ---��NSAPI����Ӧ��״̬����:*/
            RABM_LOG1_ERROR( "NAS_RabmSetTransMode:ERROR:This NSAPI's state is WRONG!: NSAPI:", pSetTransMode->ucNsapi );
            return;
    }
}



/*****************************************************************************
 Prototype      : NAS_RabmTransModeError()
 Description    : ���ô���ģʽʱ����ڲ����д���ģʽ�ֶγ���Ĵ���
 Input          : ucNsapi         ָ����NSAPI
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
*****************************************************************************/
VOS_VOID    NAS_RabmTransModeError( VOS_UINT8  ucNsapi )
{
    RABM_NSAPI_ENUM                     NsapiIndex;

    NsapiIndex = ( RABM_NSAPI_ENUM )( ucNsapi - RABM_2G_NSAPI_OFFSET );
    /*����NSAPI����Ϊ��ȷ��ģʽ:*/
    gastRabm2GEntity[NsapiIndex].TransMode = RABM_ADM_ENUM;
}

/*lint +e958*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
