/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾
*******************************************************************************
  �� �� ��   : BST_PAL_As.c
  �� �� ��   : ����
  ��    ��   : d00173029
  ��������   : 2014��7��3��
  ����޸�   :
  ��������   : ʵ�ֽ������ش��������ӿ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��07��3��
    ��    ��   : d00173029
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_As.h"
#include "BST_OS_Memory.h"
#include "NVIM_Interface.h"
#include "BastetRabmInterface.h"
#include "BastetRrcInterface.h"
#include "BST_SYS_MsgProc.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_AS_C
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/
BST_MODEM_SIM_MODE_ENUM_UINT32  BST_PAL_AsApiGetCurSimMode( BST_VOID );
BST_BOOL BST_PAL_AsApiGetCsServiceState( BST_MODEM_ID_ENUM_UINT32 enModemId );
BST_BOOL BST_PAL_AsApiGetPsServiceState( BST_MODEM_ID_ENUM_UINT32 enModemId );
BST_BOOL BST_PAL_AsApiGetCsConnectState( BST_MODEM_ID_ENUM_UINT32 enModemId );
BST_VOID BST_PAL_AsCsEvtProc( BST_VOID );


/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_DRV_RCV_AS_EVENT_T                  g_BstPalAsEventRcvCb    = BST_NULL_PTR;

BST_PAL_AS_INFO_STRU                    g_stBstPalAsInfo;


/******************************************************************************
   6 ����ʵ��
******************************************************************************/


/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiReleaseRrcConn
 ��������  : AS����ؿ�������ӿ�ʵ��
 �������  : BST_DRV_CMD_ENUM_UINT32 enCmd, ������������
             BST_VOID *pvData               ������������
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8 BST_NO_ERROR_MSG        ���Ƴɹ�ִ��
                                BST_ERR_ILLEGAL_PARAM   ���Ʋ�������
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_PAL_AsApiReleaseRrcConn( BST_VOID )
{
    BST_MODEM_ID_ENUM_UINT32           enPsModemId;
    BST_AS_RAT_MODE_UINT32             enPsRatMode;

    enPsModemId                        = BST_PAL_AsApiGetPsModemId();
    if ( enPsModemId >= BST_MODEM_MAX )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    enPsRatMode                        = BST_PAL_AsApiGetModemRat( enPsModemId );

    if ( !BST_AS_IsRatSupport ( enPsRatMode ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    switch ( enPsRatMode )
    {
        case BST_AS_RAT_WCDMA:
        case BST_AS_RAT_TDSCDMA:
            BST_DBG_LOG( "BST_DRV_CMD_RELEASE_RRC 3G" );
            BST_MSG_ProcRrrcRealseSend();
            break;

        case BST_AS_RAT_LTE:
            if(BST_FALSE == BST_PAL_AsApiGetCsServiceState( enPsModemId ))
            {
                BST_DBG_LOG( "BST_DRV_CMD_RELEASE_RRC 4G." );
                BST_MSG_ProcLRrcRealseSend();
            }
            break;

        default:
            break;
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiGetModemRat
 ��������  : ��ȡָ����Modem��ǰ����ģʽ
 �������  : BST_MODEM_ID_ENUM_UINT32 enModemId
            BST_MODEM_ID_1,     Modem 1
            BST_MODEM_ID_2,     Modem 2

 �������  : ��
 �� �� ֵ  :
            BST_AS_RAT_NONE(0x00)       ��Чģʽ
            BST_AS_RAT_GPRS(0x01)       GSM/GPRS/EDGEģʽ
            BST_AS_RAT_CDMA(0x02)       CDMA 1X(IS95)ģʽ
            BST_AS_RAT_EVDO(0x04)       EVDO(HDR)ģʽ
            BST_AS_RAT_WCDMA(0x08)      UMTSģʽ
            BST_AS_RAT_TDSCDMA(0x10)    TD-SCDMAģʽ
            BST_AS_RAT_LTE(0x20)        LTE(TDD/FDD)ģʽ
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_AS_RAT_MODE_UINT32 BST_PAL_AsApiGetModemRat( BST_MODEM_ID_ENUM_UINT32 enModemId )
{
    if(enModemId >= BST_MODEM_MAX)
    {
        return BST_AS_RAT_NONE;
    }

    if((BST_FALSE == BST_PAL_AsApiGetCsServiceState(enModemId))
       &&(BST_FALSE == BST_PAL_AsApiGetPsServiceState(enModemId)))
    {
        return BST_AS_RAT_NONE;
    }

    return g_stBstPalAsInfo.stModemInfo[enModemId].enRatMode;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiGetPsModemId
 ��������  : ��ȡ��ǰPDP���PSҵ�����ڵ�MODEM ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : BST_MODEM_ID_ENUM_UINT32
             BST_MODEM_ID_1,        Modem 1
             BST_MODEM_ID_2,        Modem 2
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_MODEM_ID_ENUM_UINT32 BST_PAL_AsApiGetPsModemId( BST_VOID )
{
    return g_stBstPalAsInfo.enPsModemId;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiGetCsServiceState
 ��������  : ��ȡָ����modem��CS����״̬
 �������  : BST_MODEM_ID_ENUM_UINT32
                           BST_MODEM_ID_1,        Modem 1
                           BST_MODEM_ID_2,        Modem 2
 �������  : ��
 �� �� ֵ  :    BST_TRUE, CS�з���BST_FALSE, CS�޷���
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��12��04��
      ��    ��   :  z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_BOOL BST_PAL_AsApiGetCsServiceState( BST_MODEM_ID_ENUM_UINT32 enModemId )
{
    if(enModemId >= BST_MODEM_MAX)
    {
        return BST_FALSE;
    }

    return g_stBstPalAsInfo.stModemInfo[enModemId].bCsInService;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiGetPsServiceState
 ��������  : ��ȡָ����modem��PS����״̬
 �������  : BST_MODEM_ID_ENUM_UINT32
                           BST_MODEM_ID_1,        Modem 1
                           BST_MODEM_ID_2,        Modem 2
 �������  : ��
 �� �� ֵ  :    BST_TRUE, PS�з���BST_FALSE, PS�޷���
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��12��04��
      ��    ��   :  z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_BOOL BST_PAL_AsApiGetPsServiceState( BST_MODEM_ID_ENUM_UINT32 enModemId )
{
    if(enModemId >= BST_MODEM_MAX)
    {
        return BST_FALSE;
    }

    return g_stBstPalAsInfo.stModemInfo[enModemId].bPsInService;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiGetCsExistInfo
 ��������  : ��ȡָ����modem���Ƿ����Csҵ��
 �������  : BST_MODEM_ID_ENUM_UINT32
                           BST_MODEM_ID_1,        Modem 1
                           BST_MODEM_ID_2,        Modem 2
 �������  : ��
 �� �� ֵ  :    BST_TRUE,��CSҵ��BST_FALSE, ��CSҵ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��12��04��
      ��    ��   :  z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_BOOL BST_PAL_AsApiGetCsConnectState( BST_MODEM_ID_ENUM_UINT32 enModemId )
{
    if(enModemId >= BST_MODEM_MAX)
    {
        return BST_FALSE;
    }

    return g_stBstPalAsInfo.stModemInfo[enModemId].bCsConnected;
}


#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiReadRfCfgNvim
 ��������  : ����NV:BST_PAL_ReadModemRfShareCfgNvim��ʼ���Ƿ�֧��DSDS
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : z00128442
    �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_PAL_AsApiReadRfCfgNvim(BST_VOID)
{
    NV_MODEM_RF_SHARE_CFG_STRU          stNvimRfShareCfgInfo;
    BST_UINT32                          ulModemIndex;

    /* ��NV��NV_MODEM_RF_SHARE_CFG_STRU��ʧ�ܣ�ֱ�ӷ��� */
    for(ulModemIndex = BST_MODEM_ID_1; ulModemIndex < BST_MODEM_MAX; ulModemIndex++)
    {
        PS_MEM_SET(&stNvimRfShareCfgInfo, 0x00, sizeof(NV_MODEM_RF_SHARE_CFG_STRU));
        if (NV_OK != NV_ReadEx((MODEM_ID_ENUM_UINT16)ulModemIndex, en_NV_MODEM_RF_SHARE_CFG,
                         &stNvimRfShareCfgInfo, sizeof(NV_MODEM_RF_SHARE_CFG_STRU)))
        {
            BST_RLS_LOG("BST_PAL_AsApiReadRfCfgNvim():WARNING: read en_NV_MODEM_RF_SHARE_CFG Error");

            g_stBstPalAsInfo.stModemInfo[ulModemIndex].bDsDsSupport = BST_FALSE;
            continue;
        }
        if( BST_TRUE == stNvimRfShareCfgInfo.usSupportFlag )
        {
            g_stBstPalAsInfo.stModemInfo[ulModemIndex].bDsDsSupport = BST_TRUE;
            g_stBstPalAsInfo.stModemInfo[ulModemIndex].ulRFID[BST_DRV_AS_RAT_GSM_ENUM]     = stNvimRfShareCfgInfo.usGSMRFID;
            g_stBstPalAsInfo.stModemInfo[ulModemIndex].ulRFID[BST_DRV_AS_RAT_WCDMA_ENUM]   = stNvimRfShareCfgInfo.usWCDMARFID;
            g_stBstPalAsInfo.stModemInfo[ulModemIndex].ulRFID[BST_DRV_AS_RAT_TDSCDMA_ENUM] = stNvimRfShareCfgInfo.usTDSRFID;
            g_stBstPalAsInfo.stModemInfo[ulModemIndex].ulRFID[BST_DRV_AS_RAT_LTE_ENUM]     = stNvimRfShareCfgInfo.usLTERFID;
        }
        else
        {
            g_stBstPalAsInfo.stModemInfo[ulModemIndex].bDsDsSupport = BST_FALSE;
        }
    }
    return;
}


/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiJudgeModemConflict
 ��������  : �ж�ָ��������modem��Ӧ��RF�Ƿ��ͻ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��07��18��
      ��    ��   :  z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/

BST_BOOL BST_PAL_AsApiJudgeModemConflict(
    BST_MODEM_ID_ENUM_UINT32 enModemId1,
    BST_MODEM_ID_ENUM_UINT32 enModemId2 )
{
    BST_AS_RAT_MODE_UINT32              ulRatMode1;
    BST_AS_RAT_MODE_UINT32              ulRatMode2;
    BST_DRV_AS_RAT_ENUM_UINT32          enRatModeEnum1;
    BST_DRV_AS_RAT_ENUM_UINT32          enRatModeEnum2;
    BST_PAL_AS_MODEMINFO_STRU          *pstModem1Info;
    BST_PAL_AS_MODEMINFO_STRU          *pstModem2Info;

    BST_ASSERT_NORM_RTN( enModemId1 >= BST_MODEM_MAX, BST_FALSE);
    BST_ASSERT_NORM_RTN( enModemId2 >= BST_MODEM_MAX, BST_FALSE);

    pstModem1Info                       = &(g_stBstPalAsInfo.stModemInfo[enModemId1]);
    pstModem2Info                       = &(g_stBstPalAsInfo.stModemInfo[enModemId2]);

    BST_DBG_LOG4("BST_PAL_AsApiJudgeModemConflict. enModemId1:%d,bDsDsSupport:%d, enModemId1:%d, bDsDsSupport:%d",
        enModemId1,enModemId2,pstModem1Info->bDsDsSupport,pstModem2Info->bDsDsSupport);

    if(( BST_FALSE == pstModem1Info->bDsDsSupport )
      ||( BST_FALSE == pstModem2Info->bDsDsSupport ))
    {
        return BST_FALSE;
    }

    ulRatMode1                          = BST_PAL_AsApiGetModemRat(enModemId1);
    ulRatMode2                          = BST_PAL_AsApiGetModemRat(enModemId2);

    enRatModeEnum1                      = BST_DRV_AsMapRatToEnum(ulRatMode1);
    enRatModeEnum2                      = BST_DRV_AsMapRatToEnum(ulRatMode2);


    BST_DBG_LOG2("BST_PAL_AsApiJudgeModemConflict. enRatMode1:%d, enRatMode2:%d",enRatModeEnum1,enRatModeEnum2);

    if(((enRatModeEnum1 >= BST_DRV_AS_RAT_NUMBER) || (BST_DRV_AS_RAT_INVALID_ENUM ==enRatModeEnum1))
       ||((enRatModeEnum2 >= BST_DRV_AS_RAT_NUMBER) || (BST_DRV_AS_RAT_INVALID_ENUM ==enRatModeEnum2)))
    {
        return BST_FALSE;
    }

    BST_DBG_LOG2("BST_PAL_AsApiJudgeModemConflict. RFID1:%d, RFID2:%d",pstModem1Info->ulRFID[enRatModeEnum1],pstModem2Info->ulRFID[enRatModeEnum2]);
    if(pstModem1Info->ulRFID[enRatModeEnum1] == pstModem2Info->ulRFID[enRatModeEnum2])
    {
        BST_DBG_LOG2("BST_PAL_AsApiJudgeModemConflict. modemId:%d, cs connected:%d",pstModem1Info->ulRFID[enRatModeEnum1],pstModem2Info->ulRFID[enRatModeEnum2]);
        return BST_TRUE;
    }

    return BST_FALSE;
}

#endif



/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiSetLpmMode
 ��������  : AS����ؿ�������ӿ�ʵ��
 �������  : BST_DRV_CMD_ENUM_UINT32 enCmd, ������������
             BST_VOID *pvData               ������������
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8 BST_NO_ERROR_MSG        ���Ƴɹ�ִ��
                                BST_ERR_ILLEGAL_PARAM   ���Ʋ�������
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_PAL_AsApiSetChnlMode( BST_DRV_CHNLMODE_ENUM_UINT32 enChnlMode  )
{
    BST_MODEM_ID_ENUM_UINT32            enModeId;
    BST_AS_RAT_MODE_UINT32              enRatMode;
    BST_PAL_CHNLMODE_STRU               stChnlMode;
    BST_UINT16                          usRabId;
    BST_UINT8                           ucRbId;
    BST_UINT32                          ulResult;

    enModeId                            = BST_PAL_AsApiGetPsModemId();
    if( enModeId != BST_MODEM_ID_1)
    {
        return BST_ERR_NOT_SUPPORT;
    }

    enRatMode                           = BST_PAL_AsApiGetModemRat(BST_MODEM_ID_1);

    if( BST_AS_RAT_WCDMA != enRatMode )
    {
        return BST_ERR_NOT_SUPPORT;
    }

    PS_MEM_SET(&stChnlMode, 0x00, sizeof(BST_PAL_CHNLMODE_STRU));

    stChnlMode.enChnlMode                = enChnlMode;

    if(BST_DRV_CHNLMODE_LPM == enChnlMode)
    {
        stChnlMode.usLimit              = BST_CHNL_MODE_LPM_LIMIT_BYTE;
    }
    else if ( BST_DRV_CHNLMODE_HPR == enChnlMode )
    {
        usRabId                         = BST_PAL_AsMsgGetRabID();
        ucRbId                          = RABM_GetRbId((BST_UINT8)usRabId);
        if(( ucRbId > BST_MAX_RBID ) || ( ucRbId < BST_MIN_RBID ))
        {
            return BST_ERR_NOT_SUPPORT;
        }
        stChnlMode.rbId                 = ucRbId;
    }
    else
    {
        //nothing to do
    }
    BST_DBG_LOG1("Setchnl mode :%d",enChnlMode);
    ulResult = BST_MSG_SendWChnlModeInfo( &stChnlMode );


    if(BST_SEND_SUCCESS != ulResult)
    {
        return BST_ERR_NOT_SUPPORT;
    }
    return BST_NO_ERROR_MSG;
}


/*****************************************************************************
 �� �� ��  : BST_PAL_AsMsgSetRatModeInfo
 ��������  : ���ö�Ӧmodem�ĵ�ǰ������ʽ
 �������  : enModemId   -- ֪ͨ��modemid
                           enRatMode    -- ��modem��Ӧ�Ľ�����ʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��11��10��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_PAL_AsMsgSetRatModeInfo(
    BST_MODEM_ID_ENUM_UINT32 enModemId,
    BST_AS_RAT_MODE_UINT32   enRatMode
)
{
    BST_UINT32                          ulAppData;
    BST_UINT32                          ulUsedLen;
    BST_AS_RAT_MODE_UINT32              enOldRatMode;
    BST_AS_RAT_MODE_UINT32              enNewRatMode;

    if(enModemId >= BST_MODEM_MAX)
    {
        BST_RLS_LOG1( "BST_PAL_AsMsgSetRatModeInfo, enModemId is illegal=%u", enModemId );
        return;
    }


    enOldRatMode = BST_PAL_AsApiGetModemRat(enModemId);
    g_stBstPalAsInfo.stModemInfo[enModemId].enRatMode  = enRatMode;

    /*������һ����Ҫ�����ϱ�һ����ʽ���������PS modem�ٽ�������*/
    if( BST_FALSE == g_stBstPalAsInfo.bRatReported )
    {
        if( BST_AS_RAT_NONE != enRatMode )
        {
            ulAppData   = enRatMode;
            BST_RLS_LOG1( "Rcv As Event: BST_AS_EVT_L3_RAT_STATE, para=%u", ulAppData );
            ulUsedLen                   = BST_OS_SIZEOF( BST_AS_RAT_MODE_UINT32 );
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_RAT_STATE, ulUsedLen, &ulAppData );
            g_stBstPalAsInfo.bRatReported = BST_TRUE;
            return;
        }
    }

    /*��PSҵ�����ڵ�modem�Ľ�����ʽ����Ҫ�ϱ�*/
    if(enModemId == BST_PAL_AsApiGetPsModemId())
    {
        enNewRatMode = BST_PAL_AsApiGetModemRat(enModemId);
        if((enNewRatMode != enOldRatMode) && (BST_AS_RAT_NONE != enNewRatMode))
        {
            ulAppData   = enNewRatMode;
            BST_RLS_LOG1( "Rcv As Event: BST_AS_EVT_L3_RAT_STATE, para=%u", ulAppData );
            ulUsedLen                   = BST_OS_SIZEOF( BST_AS_RAT_MODE_UINT32 );
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_RAT_STATE, ulUsedLen, &ulAppData );
        }
    }

    BST_DBG_LOG2( "BST_PAL_AsMsgSetRatModeInfo, enModemId :%d, Ratmode:%d", enModemId,enRatMode );

    /*�κ�һ��modem����ʽ�����仯�������ܵ���CS��PSҵ������ͻ����������仯*/
    BST_PAL_AsCsEvtProc();

}


/*****************************************************************************
 �� �� ��  : BST_PAL_SetCsRrcStatus
 ��������  : ���� CS��Rrc ״̬
 �������  :BST_MODEM_ID_ENUM_UINT32
             BST_MODEM_ID_1,        Modem 1
             BST_MODEM_ID_2,        Modem 2
             BST_BOOL                 bExist  �Ƿ����CSҵ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��11��10��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/

BST_VOID BST_PAL_AsMsgSetCsUsingInfo(
    BST_MODEM_ID_ENUM_UINT32 enModemId,
    BST_BOOL                 bCsConnected
)
{

    if ( enModemId >= BST_MODEM_MAX )
    {
        return;
    }

    g_stBstPalAsInfo.stModemInfo[enModemId].bCsConnected   = bCsConnected;


    /*�κ�һ��modem��CS״̬�����仯�������ܵ���CS��PSҵ������ͻ����������仯*/
    BST_PAL_AsCsEvtProc();

    return;
}


/*****************************************************************************
 �� �� ��  : BST_PAL_AsMsgSetServiceStatus
 ��������  : ���ö�Ӧmodem�ķ���״̬
 �������  :BST_MODEM_ID_ENUM_UINT32
             BST_MODEM_ID_1,        Modem 1
             BST_MODEM_ID_2,        Modem 2
             BST_BOOL                 bCSInservice  CS�Ƿ��з���
             BST_BOOL                 bPSInservice  PS�Ƿ��з���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��11��10��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/

BST_VOID BST_PAL_AsMsgSetServiceStatus(
    BST_MODEM_ID_ENUM_UINT32 enModemId,
    BST_BOOL                 bCsInservice,
    BST_BOOL                 bPsInservice
)
{
    BST_UINT32                          ulAppData;
    BST_UINT32                          ulUsedLen;
    BST_BOOL                            bOldPsSrvStatus;
    BST_BOOL                            bOldCsSrvStatus;
    BST_AS_RAT_MODE_UINT32              enOldRatMode;
    BST_AS_RAT_MODE_UINT32              enNewRatMode;
    BST_SRV_UTRAN_SRV_STATE_STRU        stSrvEvent;

    if(enModemId >= BST_MODEM_MAX)
    {
        BST_RLS_LOG1( "BST_PAL_AsMsgSetServiceStatus, enModemId is illegal=%u", enModemId );
        return;
    }

    enOldRatMode                   = BST_PAL_AsApiGetModemRat(enModemId);
    bOldPsSrvStatus                = BST_PAL_AsApiGetPsServiceState(enModemId);
    bOldCsSrvStatus                = BST_PAL_AsApiGetCsServiceState(enModemId);

    g_stBstPalAsInfo.stModemInfo[enModemId].bCsInService = bCsInservice;
    g_stBstPalAsInfo.stModemInfo[enModemId].bPsInService = bPsInservice;
    BST_RLS_LOG3( "BST_PAL_AsMsgSetServiceStatus, enModemId %u,CS service state:%d,Ps service state:%d",
            enModemId,bCsInservice, bPsInservice);

    if(enModemId != BST_PAL_AsApiGetPsModemId())
    {
        return;
    }

    /*if rat of ps modem changed ,need notify upper layer*/
    enNewRatMode  = BST_PAL_AsApiGetModemRat(enModemId);

    if((enNewRatMode != BST_AS_RAT_NONE) && (enNewRatMode != enOldRatMode ))
    {
        ulUsedLen                   = BST_OS_SIZEOF( BST_AS_RAT_MODE_UINT32 );
        ulAppData                   = enNewRatMode;

        BST_PalAsEventRcvCb( BST_AS_EVT_L3_RAT_STATE, ulUsedLen, &ulAppData );
        BST_RLS_LOG1( "BST_PAL_AsMsgSetServiceStatus, notify rat mode changed:%d", ulAppData );
    }

    /*if ps service state of ps modem changed ,need notify upper layer*/
    if( ( bOldPsSrvStatus != bPsInservice)
     || ( bOldCsSrvStatus != bCsInservice) )
    {
        stSrvEvent.bCsService       = bCsInservice;
        stSrvEvent.bPsService       = bPsInservice;
        BST_PalAsEventRcvCb( BST_AS_EVT_L3_SERVICE_STATE,
                            ( BST_UINT32 )BST_OS_SIZEOF( BST_SRV_UTRAN_SRV_STATE_STRU ),
                            &stSrvEvent );
    }
    return;


}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsMsgModemIdChanged
 ��������  : ����PS ����modem�����仯��Ϣ
 �������  :enOldModemId  --�仯ǰPs����modem
                          enNewModemId  --�仯��Ps����modem
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��11��10��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/

BST_VOID BST_PAL_AsMsgModemIdChanged(
    BST_MODEM_ID_ENUM_UINT32 enNewModemId )
{
    BST_AS_RAT_MODE_UINT32              enRatMode;
    BST_UINT32                          ulAppData;
    BST_UINT32                          ulUsedLen;
    BST_SRV_UTRAN_SRV_STATE_STRU        stSrvEvent;

    if(enNewModemId >= BST_MODEM_MAX)
    {
        return;
    }

    g_stBstPalAsInfo.enPsModemId        = enNewModemId;

    /*if modem changed,need report the rat of new modem to upper layer*/
    enRatMode                           = BST_PAL_AsApiGetModemRat(enNewModemId);
    if(BST_AS_RAT_NONE != enRatMode)
    {
        ulUsedLen                       = BST_OS_SIZEOF( BST_AS_RAT_MODE_UINT32 );
        ulAppData                       = enRatMode;
        BST_PalAsEventRcvCb( BST_AS_EVT_L3_RAT_STATE, ulUsedLen, &ulAppData );
        BST_RLS_LOG1( "BST_PAL_AsMsgModemIdChanged, notify rat mode changed:%d", ulAppData );
    }

    /*if modem changed,need report the service state of new modem to upper layer*/
    stSrvEvent.bCsService               = BST_PAL_AsApiGetCsServiceState(enNewModemId);
    stSrvEvent.bPsService               = BST_PAL_AsApiGetPsServiceState(enNewModemId);
    BST_PalAsEventRcvCb( BST_AS_EVT_L3_SERVICE_STATE,
                        ( BST_UINT32 )BST_OS_SIZEOF( BST_SRV_UTRAN_SRV_STATE_STRU ),
                        &stSrvEvent );
    /*PS���ڵ�modem�����仯���ܵ���CS��PSҵ������ͻ����������仯*/
    BST_PAL_AsCsEvtProc();

}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiSndRptFlag
 ��������  : �����Ƿ�����MODEM�ϱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
            BST_BOOL    bReportFlg  �Ƿ������ϱ�
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_PAL_AsApiSndRptFlag (
    BST_MODEM_ID_ENUM_UINT32    enPsModemId,
    BST_UINT8                   ucReportFlg )
{

}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsMsgSetRabID
 ��������  : ���õ�ǰʹ�õ�Rabid
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��11��10��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/

BST_VOID BST_PAL_AsMsgSetRabID(
    BST_UINT16                  usRabId
 )
{
    if(( usRabId < BST_MIN_RABID ) || ( usRabId > BST_MAX_RABID ))
    {
        BST_RLS_LOG1("BST_PAL_AsMsgSetRabID, invalid Rabid:%d",usRabId);
        return;
    }

    g_stBstPalAsInfo.usRabId            = usRabId;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsMsgGetRabID
 ��������  : ��ȡ��ǰʹ�õ�Rabid
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��11��10��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/

BST_UINT16 BST_PAL_AsMsgGetRabID ( BST_VOID )
{
    return g_stBstPalAsInfo.usRabId;
}

/*****************************************************************************
 �� �� ��  : BST_PAL_AsCsEvtProc
 ��������  : CS���¼��������������
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2015��07��18��
      ��    ��   : z00128442
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_PAL_AsCsEvtProc( BST_VOID )
{
    BST_MODEM_ID_ENUM_UINT32            ulPsModemId;
    BST_AS_RAT_MODE_UINT32              ulPsRatMode;
    BST_BOOL                            ulCsConflit;
    BST_BOOL                            ulCsConnected;
#if (FEATURE_ON == FEATURE_DSDS)
    BST_UINT32                          ulIndex;
    BST_BOOL                            ulRFShared;
#endif
    ulPsModemId                         = BST_PAL_AsApiGetPsModemId();

    BST_ASSERT_NORM( ulPsModemId >= BST_MODEM_MAX );

#if (FEATURE_ON == FEATURE_DSDS)
    for(ulIndex = BST_MODEM_ID_1; ulIndex < BST_MODEM_MAX; ulIndex++)
    {
        if(ulIndex == ulPsModemId)
        {
            continue;
        }

        ulCsConnected                   = BST_PAL_AsApiGetCsConnectState(ulIndex);
        BST_DBG_LOG3("BST_PAL_AsCsEvtProc. ulPsModemId:%d,modemId:%d, cs connected:%d",ulPsModemId,ulIndex,ulCsConnected);
        if( BST_TRUE == ulCsConnected )
        {
            ulRFShared = BST_PAL_AsApiJudgeModemConflict(ulPsModemId,ulIndex);
            if(BST_TRUE == ulRFShared)
            {
                ulCsConflit             = BST_TRUE;
                BST_PalAsEventRcvCb( BST_AS_EVT_L3_CS_EVENT_STATE,
                                        ( BST_UINT32 )BST_OS_SIZEOF( ulCsConflit ),
                                        &ulCsConflit );
                return;
            }
        }
    }
#endif

    ulPsRatMode                         = BST_PAL_AsApiGetModemRat( ulPsModemId );
    ulCsConnected                       = BST_PAL_AsApiGetCsConnectState( ulPsModemId );
    BST_DBG_LOG2("BST_PAL_AsCsEvtProc. ulPsRatMode:%d, cs connected:%d",ulPsRatMode,ulCsConnected);
    if( BST_TRUE == ulCsConnected )
    {
        if ( ( BST_AS_RAT_CDMA == ulPsRatMode )
           ||( BST_AS_RAT_GPRS == ulPsRatMode ) )
        {
            ulCsConflit                 = BST_TRUE;
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_CS_EVENT_STATE,
                                    ( BST_UINT32 )BST_OS_SIZEOF( ulCsConflit ),
                                    &ulCsConflit );
            return;
        }
    }

    ulCsConflit                         = BST_FALSE;
    BST_PalAsEventRcvCb( BST_AS_EVT_L3_CS_EVENT_STATE,
                            ( BST_UINT32 )BST_OS_SIZEOF( ulCsConflit ),
                            &ulCsConflit );
}


/*****************************************************************************
 �� �� ��  : BST_PAL_AsApiInitial
 ��������  : ��ʼ��AS(�����)�����Ϣ�ӿ�
 �������  : BST_DRV_RCV_AS_EVENT_T pfRcvCallBack   �յ���Ϣ��ص�����
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8     BST_ERR_INVALID_PTR:�ص�����գ����ɹ�
                                    BST_NO_ERROR_MSG:��ʼ���ɹ�
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_PAL_AsApiInitial( BST_DRV_RCV_AS_EVENT_T pfRcvCallBack )
{
    BST_MODEM_ID_ENUM_UINT32            enModemIndex;
#if (FEATURE_ON == FEATURE_DSDS)
    BST_UINT32                          ulIndex;
#endif
    if( BST_NULL_PTR == pfRcvCallBack )
    {
        return BST_ERR_INVALID_PTR;
    }

    g_BstPalAsEventRcvCb                                         = pfRcvCallBack;
    g_stBstPalAsInfo.enPsModemId                                 = BST_MODEM_ID_1;
    g_stBstPalAsInfo.bRatReported                                = BST_FALSE;

    for( enModemIndex = BST_MODEM_ID_1; enModemIndex < BST_MODEM_MAX; enModemIndex++)
    {
        g_stBstPalAsInfo.stModemInfo[enModemIndex].enRatMode     = BST_AS_RAT_NONE;
        g_stBstPalAsInfo.stModemInfo[enModemIndex].bCsInService  = BST_FALSE;
        g_stBstPalAsInfo.stModemInfo[enModemIndex].bPsInService  = BST_FALSE;
        g_stBstPalAsInfo.stModemInfo[enModemIndex].bCsConnected  = BST_FALSE;
    }

#if (FEATURE_ON == FEATURE_DSDS)
    for( enModemIndex = BST_MODEM_ID_1; enModemIndex < BST_MODEM_MAX; enModemIndex++)
    {
        g_stBstPalAsInfo.stModemInfo[enModemIndex].bDsDsSupport  = BST_FALSE;
        for( ulIndex = 0; ulIndex < BST_DRV_AS_RAT_NUMBER; ulIndex++ )
        {
            g_stBstPalAsInfo.stModemInfo[enModemIndex].ulRFID[ulIndex] = 0;
        }
    }
    BST_PAL_AsApiReadRfCfgNvim();
#endif
    return BST_NO_ERROR_MSG;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

