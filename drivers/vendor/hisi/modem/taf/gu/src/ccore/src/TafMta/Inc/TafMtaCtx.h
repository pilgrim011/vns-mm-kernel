/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaCtx.h
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

#ifndef __TAFMTACTX_H__
#define __TAFMTACTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaTimerMgmt.h"
#include "AtMtaInterface.h"
#include "MtaPhyInterface.h"

#include "NasErrorLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* �ȴ���Ϣ����Ķ��г��ȡ�������ʱ��ʱ����ͬʱ������Ϣ���ʸ�ֵ��TAF_MTA_CTX_MAX_TIMER_NUMһ�� */
#define TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE                   (5)

#define TAF_MTA_REFCLOCK_DEFAULT_FREQ                       (49152000)
#define TAF_MTA_REFCLOCK_DEFAULT_PRECISION                  (100)

#define TAF_MTA_INVALID_MCC                                 (0x0FFF)

#define TAF_MTA_ISMCOEX_BANDWIDTH_NUM                       (AT_MTA_ISMCOEX_BANDWIDTH_NUM)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Ƶ���ռ��ظ����ö��
*****************************************************************************/
enum TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM
{
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL          = 0x00,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS           = 0x01,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS           = 0x02,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC          = 0x04,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GUL           = 0x07,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_BUTT
};
typedef VOS_UINT8 TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������Ϣ�ռ��ظ����ö��
*****************************************************************************/
enum TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM
{
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NULL          = 0x00,
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NAS           = 0x01,
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_PHY           = 0x02,
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_BUTT
};
typedef VOS_UINT8 TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
�ṹ��    : TAF_MTA_XML_TEXT_STRU
�ṹ˵��  : ��¼XML�������ڴ��ַ�Ľṹ
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_CHAR                           *pcBufHead;                              /* ���XML�����ڴ���׵�ַ */
    VOS_CHAR                           *pcBufCur;                               /* ��ǰ�����ڴ���׵�ַ */
}TAF_MTA_XML_TEXT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_REFCLOCK_INFO_STRU
 �ṹ˵��  : ��¼GPS�ο�ʱ��״̬��Ϣ�Ľṹ

  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /* �����ϱ����ر�־ */
    VOS_UINT8                           aucReserved1[3];                        /* ����λ */
    VOS_UINT32                          ulFreq;                                 /* GPS�ο�ʱ�ӵ�Ƶ��ֵ����λHz */
    VOS_UINT32                          ulPrecision;                            /* ��ǰGPS�ο�ʱ�ӵľ��ȣ���λppb */
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16 enStatus;                               /* ʱ��Ƶ������״̬ */
    VOS_UINT8                           aucReserved2[2];                        /* ����λ */
} TAF_MTA_REFCLOCK_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_AGPS_CTX_STRU
 �ṹ˵��  : ��¼AGPS��ع�����Ϣ�������Ľṹ

  1.��    ��  : 2012��06��28��
    ��    ��  : y00213812
    �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    TAF_MTA_XML_TEXT_STRU               stXmlText;                              /* ���XML�������ڴ� */
    TAF_MTA_REFCLOCK_INFO_STRU          stRefClockInfo;                         /* GPS�ο�ʱ��״̬��Ϣ */
    TAF_NVIM_ECID_TL2GSM_CFG_STRU       stEcidCfg;                              /* ECID�������� */
}TAF_MTA_AGPS_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_CMD_BUFFER_STRU
 �ṹ˵��  : �����������Ϣ�ṹ
 1.��    ��   : 2012��07��09��
   ��    ��   : Y00213812
   �޸�����   : V7R1C50 A_GPS��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;
    VOS_UINT8                          *pucMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
}TAF_MTA_CMD_BUFFER_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_RF_LCD_CTX_STRU
 �ṹ˵��  : RF&LCD���������
 1.��    ��   : 2014��03��04��
   ��    ��   : j00174725
   �޸�����   : RF&LCD INTRUSION��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNewMipiClk;                           /* �������µ�MIPICLKֵ */
    VOS_UINT16                          usReportMipiClk;                        /* �����Ѿ��ϱ����ĵ�MIPICLKֵ */
    VOS_UINT32                          ulTimerInterVal;                        /* ����MIPICLK�ϱ���ʱ���� */
    VOS_UINT16                          usEnableBitMap;                         /* ʹ�ܿ��أ�ÿ��bit����ͬ���㷨����0����ʹ�� */
    VOS_UINT8                           aucReserved2[2];                        /* ����λ */
}TAF_MTA_RF_LCD_CTX_STRU;


/*****************************************************************************
 �ṹ��    : TAF_NETWORK_INFO_CLT_CTX_STRU
 �ṹ˵��  : ������Ϣ
 1.��    ��   : 2015��12��01��
   ��    ��   : g00322017
   �޸�����   : ��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellid;        /* С��id */
    VOS_UINT16                          usDlFreqInfo;    /* ����Ƶ�� */
    VOS_UINT16                          usUlFreqInfo;    /* ����Ƶ�� */
    VOS_UINT16                          usBandInfo;      /* BAND */
    VOS_INT16                           sRxPower;        /* Rxlev(GSM), RSCP(UMTS,TDS),Rsrp(LTE) */
    VOS_INT16                           sChanelQuality;  /* Rxqual(GSM), EcN0(UMTS), Scale(TDS),RsrQ(LTE) */
    VOS_UINT8                           ucIsExsitRrcConn;
    VOS_UINT8                           aucRsv[3];
    VOS_INT32                           lTxPwr;          /* ���з��书��, 0.1dBm���� */
    VOS_UINT32                          ulSavedSlice;    /* ��ǰ�ϱ�ʱ�� */
}TAF_NETWORK_INFO_CLT_CTX_STRU;

/*****************************************************************************
 �ṹ��    : MTA_LRRC_COEX_PARA_STRU
 �ṹ˵��  : LTE&WIFI��������ṹ��

  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
typedef AT_MTA_COEX_PARA_STRU TAF_MTA_COEX_PARA_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_INFO_CLT_CTX_STRU
 �ṹ˵��  : ��Ϣ�ռ����������
 1.��    ��   : 2015��07��22��
   ��    ��   : y00270069
   �޸�����   : ��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU    *pstFreqInfoCltCtx;
    TAF_NETWORK_INFO_CLT_CTX_STRU               stNetworkInfo;
    VOS_UINT8                                   ucWaitFreqCltCnfFlag;
    VOS_UINT8                                   ucWaitNetworkInfoCnfFlag;
    VOS_UINT8                                   aucRsv[2];
}TAF_MTA_INFO_CLT_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_NETMON_GSM_INFO_STRU
 �ṹ˵��  : GSM��ѯʱ�����Ϣ
 1.��    ��   : 2015��10��19��
   ��    ��   : zwx247453
   �޸�����   : ��Ŀ�����ṹ
*****************************************************************************/
typedef struct
{
    MTA_AT_NETMON_GSM_STATE_ENUM_UINT32         enNetMonGsmState;               /* GSM ��ѯ�����ڵĲ�ѯ״̬ */
    MTA_AT_NETMON_CELL_INFO_STRU                stNetMonCellInfoCnf;            /* GSM С����Ϣ��ȫ�ֱ��� */
}TAF_MTA_NETMON_GSM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAF_MTA_CONTEXT_STRU
 �ṹ˵��  : TAF MTA ģ������������
1.��    ��  : 2012��06��28��
  ��    ��  : y00213812
  �޸�����  : V7R1C50 A_GPS��Ŀ�����ṹ

*****************************************************************************/
typedef struct
{
    /* ��¼AGPS XML��������������Դ */
    TAF_MTA_AGPS_CTX_STRU           stAgpsCtx;

    /* MTA��ǰ�������еĶ�ʱ����Դ */
    TAF_MTA_TIMER_CTX_STRU          astTimerCtx[TAF_MTA_CTX_MAX_TIMER_NUM];

    /* MTA������Ϣ���� */
    TAF_MTA_CMD_BUFFER_STRU         astCmdBufferQueue[TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE];

    TAF_MTA_RF_LCD_CTX_STRU         stMtaRfLcdCtx;

#if(FEATURE_ON == FEATURE_LTE)
    TAF_MTA_COEX_PARA_STRU           astIsmCoex[TAF_MTA_ISMCOEX_BANDWIDTH_NUM];
#endif

    TAF_MTA_INFO_CLT_CTX_STRU       stInfoCltCtx;

    TAF_MTA_NETMON_GSM_INFO_STRU   stNetmonGsmInfo;

}TAF_MTA_CONTEXT_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  10 ��������
*****************************************************************************/
extern TAF_MTA_AGPS_CTX_STRU*  TAF_MTA_GetMtaAgpsCtxAddr( VOS_VOID );

extern TAF_MTA_CONTEXT_STRU*  TAF_MTA_GetMtaCtxAddr( VOS_VOID );

extern TAF_MTA_TIMER_CTX_STRU*  TAF_MTA_GetTimerCtxAddr( VOS_VOID );

extern VOS_VOID  TAF_MTA_InitCmdBufferQueue(
            TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue);

extern TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetCmdBufferQueueAddr( VOS_VOID );

extern VOS_VOID  TAF_MTA_DelItemInCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId);

extern VOS_VOID  TAF_MTA_SaveItemInCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
            VOS_UINT8                          *pucMsgInfo,
            VOS_UINT32                          ulMsgInfoLen);

extern TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetItemFromCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32                enTimerId);


extern VOS_VOID TAF_MTA_InitRefClockInfo(
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo
);

extern TAF_MTA_REFCLOCK_INFO_STRU* TAF_MTA_GetRefClockInfo(VOS_VOID);

VOS_VOID  TAF_MTA_InitRfLcdIntrusionCtx(
    TAF_MTA_RF_LCD_CTX_STRU            *pstRfLcdCtx
);
TAF_MTA_RF_LCD_CTX_STRU* TAF_MTA_GetRfLcdCtxAddr( VOS_VOID );


VOS_VOID TAF_MTA_InitEcidCfg(
    TAF_NVIM_ECID_TL2GSM_CFG_STRU      *pstEcidCfg);

TAF_NVIM_ECID_TL2GSM_CFG_STRU* TAF_MTA_GetEcidCfg(VOS_VOID);

#if(FEATURE_ON == FEATURE_LTE)
TAF_MTA_COEX_PARA_STRU*  TAF_MTA_GetIsmCoexAddr( VOS_VOID );
VOS_VOID  TAF_MTA_InitIsmCoex(
    TAF_MTA_COEX_PARA_STRU              *pstMtaCoexPara
);
#endif
#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID  TAF_MMA_InitInfoCltCtx(
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx
);
VOS_VOID  TAF_MMA_AllocFreqInfoCltCtx(VOS_VOID);
VOS_VOID  TAF_MMA_FreeFreqInfoCltCtx(VOS_VOID);
TAF_MTA_INFO_CLT_CTX_STRU*  TAF_MTA_GetInfoCltAddr(VOS_VOID);
VOS_UINT8 TAF_MTA_GetWaitFreqCltCnfFlag(VOS_VOID);
VOS_VOID TAF_MTA_SetWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8    enFreqCltCnf
);
VOS_VOID TAF_MTA_ClrWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8    enFreqCltCnf
);
VOS_VOID TAF_MTA_ClrAllWaitFreqCltCnfFlag(VOS_VOID);
VOS_VOID  TAF_MMA_ClearNetworkInfo(VOS_VOID);
VOS_VOID TAF_MTA_ClrAllWaitNetworkInfoCnfFlag(VOS_VOID);
VOS_UINT8 TAF_MTA_GetWaitNetworkInfoCnfFlag(VOS_VOID);
VOS_VOID TAF_MTA_SetWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
);
VOS_VOID TAF_MTA_ClrWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
);
#endif

VOS_VOID  TAF_MTA_InitNetmonGsmInfo(
    TAF_MTA_NETMON_GSM_INFO_STRU       *pstNetmonGsmInfo
);
MTA_AT_NETMON_GSM_STATE_ENUM_UINT32  TAF_MTA_GetNetmonGsmState(VOS_VOID);
VOS_VOID  TAF_MTA_SetNetmonGsmState(
    MTA_AT_NETMON_GSM_STATE_ENUM_UINT32 enNetMonGsmState
);
MTA_AT_NETMON_CELL_INFO_STRU*  TAF_MTA_GetNetmonCellInfo(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


