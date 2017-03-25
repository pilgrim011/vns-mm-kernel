/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaCtx.c
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2012��6��27��
  ����޸�   :
  ��������   : MTAģ��ȫ�ֱ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��6��27��
    ��    ��   : Y00213812
    �޸�����   : A-GPS��Ŀ����

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_CTX_C

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaCtx.h"
#include "TafMtaComm.h"

#include "NVIM_Interface.h"



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* MTAģ��������������Դ */
TAF_MTA_CONTEXT_STRU            g_stTafMtaCtx;

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MTA_GetMtaAgpsCtxAddr
 ��������  : ��ȡMTA CTXģ���е�AGPS��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTA CTXģ���е�AGPS��������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A_GPS��Ŀ����
*****************************************************************************/
TAF_MTA_AGPS_CTX_STRU*  TAF_MTA_GetMtaAgpsCtxAddr( VOS_VOID )
{
    return &(g_stTafMtaCtx.stAgpsCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetMtaCtxAddr
 ��������  : ��ȡMTA CTXģ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTA CTXģ���������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A_GPS��Ŀ����
*****************************************************************************/
TAF_MTA_CONTEXT_STRU*  TAF_MTA_GetMtaCtxAddr( VOS_VOID )
{
    return &(g_stTafMtaCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetTimerCtxAddr
 ��������  : ��ȡMTA CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTA CTXģ���ж�ʱ����������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A_GPS��Ŀ����
*****************************************************************************/
TAF_MTA_TIMER_CTX_STRU*  TAF_MTA_GetTimerCtxAddr( VOS_VOID )
{
    return g_stTafMtaCtx.astTimerCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetRfLcdCtxAddr
 ��������  : ��ȡMTA CTXģ����Rf&Lcd���Ź�ܵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTA CTXģ���ж�ʱ����������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ����
*****************************************************************************/
TAF_MTA_RF_LCD_CTX_STRU* TAF_MTA_GetRfLcdCtxAddr( VOS_VOID )
{
    return &g_stTafMtaCtx.stMtaRfLcdCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitRfLcdIntrusionCtx
 ��������  : ��ʼ��MTA�УRRf&Lcd���Ź�����������
 �������  : TAF_MTA_RF_LCD_CTX_STRU*
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ����
*****************************************************************************/
VOS_VOID  TAF_MTA_InitRfLcdIntrusionCtx(
    TAF_MTA_RF_LCD_CTX_STRU            *pstRfLcdCtx
)
{
    VOS_UINT32                          ulRet;
    MTC_RF_LCD_TIMER_INTERVAL_STRU      stRfLcdTimerInterval;
    MTC_NVIM_RF_LCD_CFG_STRU            stRfLcdCfg;

    /* ��ʼ�� */
    PS_MEM_SET(&stRfLcdCfg, 0x0, sizeof(MTC_NVIM_RF_LCD_CFG_STRU));
    PS_MEM_SET(&stRfLcdTimerInterval, 0x0, sizeof(MTC_RF_LCD_TIMER_INTERVAL_STRU));
    PS_MEM_SET(pstRfLcdCtx, 0x0, sizeof(TAF_MTA_RF_LCD_CTX_STRU));


    /* ��ȡen_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG NV�� */
    ulRet = NV_Read(en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG,
                    &stRfLcdTimerInterval,
                    sizeof(MTC_RF_LCD_TIMER_INTERVAL_STRU));
    if (VOS_OK != ulRet)
    {
        MTA_WARNING1_LOG("MTC_ReadRfLcdCfgNv: Read Nv Fail.", en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG);
        pstRfLcdCtx->ulTimerInterVal = TAF_MTA_RF_LCD_TIMER_INTERVAL_DEFAULT;
    }
    else
    {
        pstRfLcdCtx->ulTimerInterVal = stRfLcdTimerInterval.ulTimerInterval * TIMER_S_TO_MS_1000;
    }

    /* ��ȡen_NV_Item_MTC_RF_LCD_CFG NV�� */
    ulRet = NV_Read(en_NV_Item_MTC_RF_LCD_CFG,
                    &stRfLcdCfg,
                    sizeof(MTC_NVIM_RF_LCD_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        pstRfLcdCtx->usEnableBitMap = 0;
    }
    else
    {
        pstRfLcdCtx->usEnableBitMap = stRfLcdCfg.usEnableBitMap;
    }

    pstRfLcdCtx->usNewMipiClk    = 0x0000;
    pstRfLcdCtx->usReportMipiClk = 0x0000;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_InitCmdBufferQueue
 ��������  : ��ʼ���ȴ�����Ϣ����
 �������  : pstCmdBufferQueue:��Ҫ�ȴ���ʼ���Ķ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ����
*****************************************************************************/
VOS_VOID  TAF_MTA_InitCmdBufferQueue(
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        pstCmdBufferQueue[i].enTimerId      = TI_TAF_MTA_TIMER_BUTT;
        pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
        pstCmdBufferQueue[i].ulMsgInfoLen   = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetCmdBufferQueueAddr
 ��������  : ��ȡMTA��Ϣ���еĵ�ַ
 �������  :  VOID
 �������  : ��
 �� �� ֵ  : MTA��Ϣ���еĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ����

*****************************************************************************/
TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetCmdBufferQueueAddr( VOS_VOID )
{
    return g_stTafMtaCtx.astCmdBufferQueue;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_DelItemInCmdBufferQueue
 ��������  : �Ӷ�����ɾ�����Ӧ�ĵȴ���Ϣ
 �������  : ֮ǰ�ȴ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ����

*****************************************************************************/
VOS_VOID  TAF_MTA_DelItemInCmdBufferQueue(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    VOS_UINT32                          i;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue;

    pstCmdBufferQueue = TAF_MTA_GetCmdBufferQueueAddr();

    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (enTimerId == pstCmdBufferQueue[i].enTimerId)
        {
            /* ����л������Ϣ���ͷ���Ϣ�ڴ� */
            if (VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
            {
                PS_MEM_FREE(UEPS_PID_MTA, pstCmdBufferQueue[i].pucMsgInfo);
            }

            /* ��ʼ�� */
            pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
            pstCmdBufferQueue[i].enTimerId      = TI_TAF_MTA_TIMER_BUTT;
            pstCmdBufferQueue[i].ulMsgInfoLen   = 0;

            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SaveItemInCmdBufferQueue
 ��������  : �������Ϣ���뵽�ȴ��Ļ��������, �ȴ�����Ľ��
 �������  :  TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
              VOS_UINT32                         *pulMsgInfo,
              VOS_UINT32                          ulMsgInfoLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ����

*****************************************************************************/
VOS_VOID  TAF_MTA_SaveItemInCmdBufferQueue(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT8                          *pucMsgInfo,
    VOS_UINT32                          ulMsgInfoLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucMsgBuf;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue;

    /* �����Ϣָ��Ϊ�գ�ֱ�ӷ��� */
    if (VOS_NULL_PTR == pucMsgInfo)
    {
        return;
    }

    pstCmdBufferQueue = TAF_MTA_GetCmdBufferQueueAddr();

    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (TI_TAF_MTA_TIMER_BUTT == pstCmdBufferQueue[i].enTimerId)
        {
            break;
        }
    }

    /* �ж���ǰ��ѭ�������Ƿ��Ѿ����ˣ����������ֱ�ӷ��أ������쳣��ӡ */
    if ( i >= TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE )
    {
        /* ����������� */
        MTA_WARNING2_LOG("TAF_MTA_SaveItemInCmdBufferQueue, Buffer Full, Timer Id :",
                         UEPS_PID_MTA,
                         enTimerId);

        return;
    }

    /* �ڶ���������Ӧ����Ϣ�������ڴ棬������Ϣ��ֵ */
    pucMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_MTA, ulMsgInfoLen);
    if (VOS_NULL_PTR == pucMsgBuf)
    {
        /* �ڴ����ʧ�� */
        MTA_WARNING2_LOG("TAF_MTA_SaveItemInCmdBufferQueue, Mem Alloc Fail, Timer Id :",
                         UEPS_PID_MTA,
                         enTimerId );
        return;
    }

    /* ��ֵ */
    PS_MEM_CPY((VOS_UINT8 *)pucMsgBuf, pucMsgInfo, ulMsgInfoLen);
    pstCmdBufferQueue[i].pucMsgInfo     = pucMsgBuf;
    pstCmdBufferQueue[i].enTimerId      = enTimerId;
    pstCmdBufferQueue[i].ulMsgInfoLen   = ulMsgInfoLen;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetItemFromCmdBufferQueue
 ��������  : �ӵȴ��Ļ�������л�ȡ�����Ϣ
 �������  : TAF_MTA_TIMER_ID_ENUM_UINT32                enTimerId
 �������  : ��
 �� �� ֵ  : TAF_MTA_BUF_WAIT_CNF_MSG_INFO_STRU      ��Ϣָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ����

*****************************************************************************/
TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetItemFromCmdBufferQueue(
    TAF_MTA_TIMER_ID_ENUM_UINT32                enTimerId
)
{
    VOS_UINT32                          i;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue;


    pstCmdBufferQueue = TAF_MTA_GetCmdBufferQueueAddr();

    /* ��������, ��ȡenTimerIdָ������Ϣ�ڵ� */
    for ( i = 0; i < TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (enTimerId == pstCmdBufferQueue[i].enTimerId)
        {
            break;
        }
    }

    /* �ж���ǰ��ѭ�������Ƿ��Ѿ����ˣ����������ֱ�ӷ��أ������쳣��ӡ */
    if ( i >= TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE )
    {
        /* δ�ҵ� */
        MTA_WARNING2_LOG("TAF_MTA_GetItemFromCmdBufferQueue, Msg Not Found, Timer Id :",
                         UEPS_PID_MTA,
                         enTimerId);

        return VOS_NULL_PTR;
    }

    /* ���������Ϣָ�뷵�� */
    return &pstCmdBufferQueue[i];
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitRefClockInfo
 ��������  : ��ʼ��GPS�ο�ʱ����Ϣ
 �������  : pstRefClockInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
  2.��    ��   : 2014��04��25��
    ��    ��   : l00198894
    �޸�����   : DTS2014042408217: �޸�GPS�ο�ʱ��Ĭ������״̬
*****************************************************************************/
VOS_VOID TAF_MTA_InitRefClockInfo(
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo
)
{
    PS_MEM_SET(pstRefClockInfo, 0, sizeof(TAF_MTA_REFCLOCK_INFO_STRU));

    pstRefClockInfo->enRptFlg       = AT_MTA_CMD_RPT_FLG_OFF;
    pstRefClockInfo->ulFreq         = TAF_MTA_REFCLOCK_DEFAULT_FREQ;
    pstRefClockInfo->ulPrecision    = TAF_MTA_REFCLOCK_DEFAULT_PRECISION;
    pstRefClockInfo->enStatus       = PHY_MTA_REFCLOCK_UNLOCKED;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetRefClockInfo
 ��������  : ��ȡGPS�ο�ʱ����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_MTA_REFCLOCK_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
TAF_MTA_REFCLOCK_INFO_STRU* TAF_MTA_GetRefClockInfo(VOS_VOID)
{
    return &(g_stTafMtaCtx.stAgpsCtx.stRefClockInfo);
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_InitEcidCfg
 ��������  : ��ʼ��GPSҵ��ECID��������
 �������  : pstEcidCfg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_InitEcidCfg(
    TAF_NVIM_ECID_TL2GSM_CFG_STRU      *pstEcidCfg
)
{
    TAF_NVIM_ECID_TL2GSM_CFG_STRU       stNvTmp;

    PS_MEM_SET(&stNvTmp, 0, sizeof(stNvTmp));
    PS_MEM_SET(pstEcidCfg, 0, sizeof(TAF_NVIM_ECID_TL2GSM_CFG_STRU));

    /* ��ȡNV�� */
    if (NV_OK == NV_Read(en_NV_Item_ECID_TL2GSM_CFG,
                         &stNvTmp,
                         sizeof(TAF_NVIM_ECID_TL2GSM_CFG_STRU)))
    {
        /* NV��Ч�Լ�� */
        if ( (VOS_TRUE == stNvTmp.ucEnableFlg)
          && (TAF_MTA_INVALID_MCC > stNvTmp.usMcc) )
        {
            pstEcidCfg->ucEnableFlg = stNvTmp.ucEnableFlg;
            pstEcidCfg->usMcc       = stNvTmp.usMcc;
            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetEcidCfg
 ��������  : ��ȡAGPS����ECID���������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_NVIM_ECID_TL2GSM_CFG_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
TAF_NVIM_ECID_TL2GSM_CFG_STRU* TAF_MTA_GetEcidCfg(VOS_VOID)
{
    return &(g_stTafMtaCtx.stAgpsCtx.stEcidCfg);
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_InitNetmonGsmInfo
 ��������  : ��ʼ��MTA��GSM��ѯʱ�����Ϣ
 �������  : TAF_MTA_NETMON_GSM_INFO_STRU*
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  TAF_MTA_InitNetmonGsmInfo(
    TAF_MTA_NETMON_GSM_INFO_STRU       *pstNetmonGsmInfo
)
{
    pstNetmonGsmInfo->enNetMonGsmState = MTA_AT_NETMON_GSM_STATE_INIT;
    PS_MEM_SET(&pstNetmonGsmInfo->stNetMonCellInfoCnf, 0x0, sizeof(pstNetmonGsmInfo->stNetMonCellInfoCnf));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetNetmonGsmState
 ��������  : ��ȡMTA��GSM ��ѯ�����ڵĲ�ѯ״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : MTA_AT_NETMON_GSM_STATE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������
*****************************************************************************/
MTA_AT_NETMON_GSM_STATE_ENUM_UINT32  TAF_MTA_GetNetmonGsmState(VOS_VOID)
{
    return g_stTafMtaCtx.stNetmonGsmInfo.enNetMonGsmState;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SetNetmonGsmState
 ��������  : �趨MTA��GSM ��ѯ�����ڵĲ�ѯ״̬
 �������  : MTA_AT_NETMON_GSM_STATE_ENUM_UINT32
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  TAF_MTA_SetNetmonGsmState(
    MTA_AT_NETMON_GSM_STATE_ENUM_UINT32 enNetMonGsmState
)
{
    g_stTafMtaCtx.stNetmonGsmInfo.enNetMonGsmState = enNetMonGsmState;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetNetmonCellInfo
 ��������  : ��ȡMTA��GSM С����Ϣ��ȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : MTA_AT_NETMON_CELL_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������
*****************************************************************************/
MTA_AT_NETMON_CELL_INFO_STRU*  TAF_MTA_GetNetmonCellInfo(VOS_VOID)
{
    return &(g_stTafMtaCtx.stNetmonGsmInfo.stNetMonCellInfoCnf);
}


#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_GetIsmCoexAddr
 ��������  : ��ȡMTA CTXģ����IsmCoex�����б��׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTA CTXģ����IsmCoex�����б�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
TAF_MTA_COEX_PARA_STRU*  TAF_MTA_GetIsmCoexAddr( VOS_VOID )
{
    return g_stTafMtaCtx.astIsmCoex;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitIsmCoex
 ��������  : ��ʼ��IsmCoex�����б�
 �������  : pstMtaCoexPara
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  TAF_MTA_InitIsmCoex(
    TAF_MTA_COEX_PARA_STRU              *pstMtaCoexPara
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        PS_MEM_SET(pstMtaCoexPara + i, 0x00, sizeof(TAF_MTA_COEX_PARA_STRU));
    }

    return;
}
#endif


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : TAF_MMA_InitInfoCltCtx
 ��������  : ��ʼ��MTA����Ϣ�ռ����������
 �������  : TAF_MTA_INFO_CLT_CTX_STRU*
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_VOID  TAF_MMA_InitInfoCltCtx(
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx
)
{
    pstInfoCltCtx->pstFreqInfoCltCtx =  VOS_NULL_PTR;

    TAF_MTA_ClrAllWaitFreqCltCnfFlag();

    TAF_MMA_ClearNetworkInfo();

    TAF_MTA_ClrAllWaitNetworkInfoCnfFlag();
    return;
}

/*lint -e429 -e830*/
/*****************************************************************************
 �� �� ��  : TAF_MMA_AllocFreqInfoCltCtx
 ��������  : ��ʼ��MTA����Ϣ�ռ����������
 �������  : TAF_MTA_INFO_CLT_CTX_STRU*
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_VOID  TAF_MMA_AllocFreqInfoCltCtx(VOS_VOID)
{
    TAF_MTA_INFO_CLT_CTX_STRU                  *pstInfoCltCtx  = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU    *pstFreqInfoClt = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ��ȡMTA�������б�����ͨ��Ƶ��ɼ������� */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();

    /* �����ڴ����ͨ��Ƶ��ɼ������ĺͳ�ʼ�� */
    ulLength         = sizeof(NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU);
    pstFreqInfoClt   = (NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU *)PS_MEM_ALLOC(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstFreqInfoClt)
    {
        MTA_ERROR_LOG("TAF_MMA_AllocFreqInfoCltCtx: Alloc msg fail!");
        return;
    }

    PS_MEM_SET(pstFreqInfoClt, 0, ulLength);

    pstInfoCltCtx->pstFreqInfoCltCtx = pstFreqInfoClt;

    return;
}
/*lint +e429 +e830*/

/*****************************************************************************
 �� �� ��  : TAF_MMA_FreeFreqInfoCltCtx
 ��������  : �ͷ�MTA����Ϣ�ռ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_VOID  TAF_MMA_FreeFreqInfoCltCtx(VOS_VOID)
{
    TAF_MTA_INFO_CLT_CTX_STRU                   *pstInfoCltCtx;

    pstInfoCltCtx = TAF_MTA_GetInfoCltAddr();

    if (VOS_NULL_PTR == pstInfoCltCtx->pstFreqInfoCltCtx)
    {
        return;
    }

    PS_MEM_FREE(UEPS_PID_MTA, pstInfoCltCtx->pstFreqInfoCltCtx);

    pstInfoCltCtx->pstFreqInfoCltCtx = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetCloudFreqInfoCltAddr
 ��������  : ��ȡMTA��Ϣ�ɼ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTA��Ϣ�ɼ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
TAF_MTA_INFO_CLT_CTX_STRU*  TAF_MTA_GetInfoCltAddr(VOS_VOID)
{
    return &g_stTafMtaCtx.stInfoCltCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetWaitFreqCltCnfFlag
 ��������  : ��ȡƵ���ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_UINT8 TAF_MTA_GetWaitFreqCltCnfFlag(VOS_VOID)
{
    return g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SetWaitFreqCltCnfFlag
 ��������  : ����Ƶ���ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_VOID TAF_MTA_SetWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8       enFreqCltCnf
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag |= enFreqCltCnf;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_ClrWaitFreqCltCnfFlag
 ��������  : ���Ƶ���ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_VOID TAF_MTA_ClrWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8       enFreqCltCnf
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag &= (~enFreqCltCnf);
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_ClrAllWaitFreqCltCnfFlag
 ��������  : �������Ƶ���ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��22��
    ��    ��   : y00270069
    �޸�����   : ��ͨ����Ŀ����
*****************************************************************************/
VOS_VOID TAF_MTA_ClrAllWaitFreqCltCnfFlag(VOS_VOID)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitFreqCltCnfFlag = TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ClearNetworkInfo
 ��������  : ���ȫ�ֱ����е�NetworkInfo
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��01��
    ��    ��   : g00322017
    �޸�����   : ˫������
*****************************************************************************/
VOS_VOID  TAF_MMA_ClearNetworkInfo(VOS_VOID)
{
    PS_MEM_SET(&(g_stTafMtaCtx.stInfoCltCtx.stNetworkInfo), 0, sizeof(TAF_NETWORK_INFO_CLT_CTX_STRU));
}
/*****************************************************************************
 �� �� ��  : TAF_MTA_ClrAllWaitNetworkInfoCnfFlag
 ��������  : �������������Ϣ�ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��01��
    ��    ��   : g00322017
    �޸�����   : ˫������
*****************************************************************************/
VOS_VOID TAF_MTA_ClrAllWaitNetworkInfoCnfFlag(VOS_VOID)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag = TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NULL;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetWaitNetworkInfoCnfFlag
 ��������  : ��ȡ������Ϣ�ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��01��
    ��    ��   : g00322017
    �޸�����   : ˫������
*****************************************************************************/
VOS_UINT8 TAF_MTA_GetWaitNetworkInfoCnfFlag(VOS_VOID)
{
    return g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SetWaitFreqCltCnfFlag
 ��������  : ����������Ϣ�ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��01��
    ��    ��   : g00322017
    �޸�����   : ˫������
*****************************************************************************/
VOS_VOID TAF_MTA_SetWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag |= enNetworkInfoCltCnfFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_ClrWaitNetworkInfoCnfFlag
 ��������  : ���������Ϣ�ռ��ظ���ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��01��
    ��    ��   : g00322017
    �޸�����   : ˫������
*****************************************************************************/
VOS_VOID TAF_MTA_ClrWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
)
{
    g_stTafMtaCtx.stInfoCltCtx.ucWaitNetworkInfoCnfFlag &= (~enNetworkInfoCltCnfFlag);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
