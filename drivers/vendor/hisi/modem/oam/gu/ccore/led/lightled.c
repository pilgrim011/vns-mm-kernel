/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: LightLED.c                                                      */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: Turn on LED according to some Events which be supported by PS*/
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-06                                                          */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "lightled.h"
#include "mdrv.h"
#include "UsimPsInterface.h"
#include "apminterface.h"
#include "TafOamInterface.h"

VOS_INT g_lOldLedState = LED_LIGHT_POWER_ON;


/*****************************************************************************
 Function   : OM_GetLedState
 Description: Get led state from the PS state.
 Input      : event
 Return     : void
 Other      :
 *****************************************************************************/
VOS_INT OM_GetLedState(USIMM_CARD_SERVIC_ENUM_UINT32 ucCardStatus,
                            WAS_MNTN_OM_OUT_OF_SERVICE_ENUM_UINT8 enIsOutService,
                            NAS_OM_REGISTER_STATE_ENUM_UINT8 enRegState,
                            NAS_OM_SERVICE_TYPE_ENUM_UINT8 enServiceType)
{
    TAF_APS_USER_CONN_STATUS_ENUM_UINT8 ucConnStatus;

    /*δ����Э��ջ*/
    if (NAS_OM_REGISTER_STATE_POWEROFF == enRegState)
    {
        return LED_LIGHT_OFFLINE;
    }

    if ((WAS_MNTN_OM_OUT_SERVICE == enIsOutService)
        || (NAS_OM_REGISTER_STATE_NOT_REGISTER == enRegState))
    {
        return LED_LIGHT_OFFLINE;
    }

    ucConnStatus = TAF_APS_GetUserConnStatus();


    /*�����磬��ҵ��*/
    if (NAS_OM_SERVICE_TYPE_NO_SERVICE == enServiceType)
    {
        /*GSM �̵Ƶ���*/
        if (NAS_OM_REGISTER_STATE_REGISTER_2G == enRegState)
        {
            return LED_LIGHT_G_REGISTERED;
        }

        /*WCDMA ���Ƶ���*/
        if (NAS_OM_REGISTER_STATE_REGISTER_3G == enRegState)
        {
            return LED_LIGHT_W_REGISTERED;
        }



        /*LTE ��Ƶ���*/
        if (NAS_OM_REGISTER_STATE_REGISTER_4G == enRegState)
        {
            /* ���ź���IDLE̬��Ϊ����LTEҵ��״̬ */
            if(TAF_APS_USER_CONN_EXIST == ucConnStatus)
            {
                return LED_LIGHT_H_CONNNECTED;
            }
            else
            {
                return LED_LIGHT_L_REGISTERED;
            }
        }


    }

    /*����·����GSMҵ��*/
    if (NAS_OM_SERVICE_TYPE_GSM == enServiceType)
    {
        return (TAF_APS_USER_CONN_EXIST == ucConnStatus) ? LED_LIGHT_G_CONNECTED : LED_LIGHT_G_REGISTERED;
    }

    /*����·����WCDMAҵ��*/
    if (NAS_OM_SERVICE_TYPE_WCDMA == enServiceType)
    {
        return (TAF_APS_USER_CONN_EXIST == ucConnStatus) ? LED_LIGHT_W_CONNNECTED : LED_LIGHT_W_REGISTERED;
    }

    /*����·����HSPAҵ��*/
    if (NAS_OM_SERVICE_TYPE_HSPA == enServiceType)
    {
        return (TAF_APS_USER_CONN_EXIST == ucConnStatus) ? LED_LIGHT_H_CONNNECTED : LED_LIGHT_W_REGISTERED;
    }

    /*��LTEҵ�� �� ���ź���IDLE̬����Ϊ����LTEҵ��״̬*/
    if ((NAS_OM_SERVICE_TYPE_LTE == enServiceType) || (NAS_OM_REGISTER_STATE_REGISTER_4G == enRegState))
    {
        return (TAF_APS_USER_CONN_EXIST == ucConnStatus) ? LED_LIGHT_H_CONNNECTED : LED_LIGHT_L_REGISTERED;
    }

    return LED_LIGHT_OFFLINE;
}


/*****************************************************************************
 Function   : OM_RuningPsStateCheckCb
 Description: Get the current PS state called by driver.
 Input      : VOS_VOID
 Return     : void
 Other      :
 *****************************************************************************/
VOS_INT OM_RuningPsStateCheckCb(VOS_VOID)
{
    WAS_MNTN_OM_OUT_OF_SERVICE_ENUM_UINT8   enIsOutService;
    NAS_OM_REGISTER_STATE_ENUM_UINT8        enRegState;
    NAS_OM_SERVICE_TYPE_ENUM_UINT8          enServiceType;
    VOS_INT                                 lCurLedState;
    VOS_UINT8                               ucCardStatus;

    enIsOutService  = WAS_MNTN_GetOmOutOfService();
    enRegState      = NAS_GetRegisterState();
    enServiceType   = NAS_GetServiceType();

    /*lint -e534*/
    USIMM_GetCardTypeByAppType(&ucCardStatus, VOS_NULL_PTR, USIMM_GUTL_APP);
    /*lint +e534*/

    lCurLedState    = OM_GetLedState((USIMM_CARD_SERVIC_ENUM_UINT32)ucCardStatus,
                                enIsOutService, enRegState, enServiceType);

    /*������LED���б仯�����ϱ���SDT������ʾ*/
    if (g_lOldLedState != lCurLedState)
    {
        g_lOldLedState = lCurLedState;
    }

    return lCurLedState;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




