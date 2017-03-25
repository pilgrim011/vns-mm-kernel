/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : chanctrl_om_def.h
  �� �� ��   : ����
  ��    ��   : w00159358
  ��������   : 2011��3��7��
  ����޸�   :
  ��������   : �����ŵ�����ģ��OM��Ҫ�ϱ��Ľṹ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��3��7��
    ��    ��   : w00159358
    �޸�����   : �����ļ�
  ------------------------------------------------------------------------------
  2.��    ��   : 2012��4��18��
     ��    ��   : sunyanjie
     �޸�����   : [DTS2012041802974]OM�Ż��޸�

******************************************************************************/

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __CHANCTRL_OM_DEF_H__
#define __CHANCTRL_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                    1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
    LPHY_REQ_CHANCTRL_TM_REQUEST           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_CHANCTRL_CP_REQUEST,
    LPHY_REQ_CHANCTRL_CELL_STAT_REQUEST,

    LPHY_REQ_TAS_STAT_REQUEST,
    LPHY_REQ_DPDT_STAT_REQUEST,

}LPHY_CHANCTRL_REQ_ENUM;

typedef UINT16 LPHY_CHANCTRL_REQ_ENUM_UINT16;


typedef struct
{
    OM_REQ_ENABLE_ENUM enOmTmSwitch;
    OM_REQ_ENABLE_ENUM enOmCpSwitch;
}LPHY_OM_REQ_CHANCTRL_STRU;
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptChanEna;
    UINT32 ulRptChanPeriod;
}LPHY_OM_REQ_CHANCTRL_STAT_ENA_STRU;
typedef struct
{
    LPHY_OM_REQ_CHANCTRL_STAT_ENA_STRU stRptChanEna;
    UINT32 ulRptPeriodCnt;
}LPHY_OM_REQ_CHANCTRL_STAT_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM enRptChanEna;
    UINT32             ulRptTasPeriod;
}LPHY_OM_REQ_TASCTRL_STAT_ENA_STRU;
typedef struct
{
    LPHY_OM_REQ_TASCTRL_STAT_ENA_STRU stRptTasEna;
    UINT32                            ulRptTasPeriodCnt;
}LPHY_OM_REQ_TAS_STAT_ENA_STRU;
typedef struct
{
    OM_REQ_ENABLE_ENUM enRptDpdtEna;
    UINT16             usRev;
}LPHY_OM_REQ_DPDT_STAT_ENA_STRU;

/************************************************************
                    2. CNF���ݽṹ����
************************************************************/


/************************************************************
                    3. Ind���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_IND_CHANCTRL_TM_REPORT           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_CHANCTRL_CP_REPORT,
    LPHY_IND_CHANCTRL_CELL_STAT,

	LPHY_IND_TAS_ASU_STAT,
	LPHY_IND_TAS_DPDT_SWITCH_STAT,
	LPHY_IND_TAS_STATE_CHANGE_STAT,
	LPHY_IND_TAS_GIVE_STAT,
	LPHY_IND_TAS_GIVE_DCH,
	LPHY_IND_TAS_GIVE_IDLE,
	LPHY_IND_TAS_BS_RSSI_STAT,
	LPHY_IND_DPDT_STAT,
    LPHY_IND_MAS_ESTIMATE_HIGH,
    LPHY_IND_MAS_ESTIMATE_LOW,
    LPHY_IND_MAS_ESTIMATE_END,
    LPHY_IND_MAS_GET_NEXT_ANT,
    LPHY_IND_MAS_TRACE_REPORT,
    LPHY_IND_MAS_ERROR_REPORT,
    LPHY_IND_MAS_CONN_UPDATE_ACTIVE,
    LPHY_IND_MAS_CONN_UPDATE_PASSIVE,
    LPHY_IND_MAS_CONN_PROBE,
    LPHY_IND_MAS_CAP_CHANGE_INIT,
}LPHY_CHANCTRL_IND_ENUM;

typedef UINT16 LPHY_CHANCTRL_IND_ENUM_UINT16;

typedef struct
{
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_IND_CHANCTRL_STRU;
enum LPHY_CHANCTRL_BAND_WIDTH_ENUM
{
    LPHY_BAND_WIDTH_6RB              = 0,                /* ����Ϊ6RB */
    LPHY_BAND_WIDTH_15RB,                                /* ����Ϊ15RB */
    LPHY_BAND_WIDTH_25RB,                                /* ����Ϊ25RB */
    LPHY_BAND_WIDTH_50RB,                                /* ����Ϊ50RB */
    LPHY_BAND_WIDTH_75RB,                                /* ����Ϊ75RB */
    LPHY_BAND_WIDTH_100RB,                               /* ����Ϊ100RB */
    LPHY_BAND_WIDTH_BUTT
};
typedef UINT8 LPHY_CHANCTRL_BAND_WIDTH_ENUM_UINT8;

enum LPHY_CHANCTRL_LTE_MODE_TYPE_ENUM
{
    LPHY_LTE_MODE_TYPE_FDD                = 0,                             /* LTE FDD ��ʽ */
    LPHY_LTE_MODE_TYPE_TDD                = 1,                             /* LTE TDD ��ʽ */
    LPHY_LTE_MODE_TYPE_BUTT
};
typedef UINT8 LPHY_CHANCTRL_LTE_MODE_TYPE_ENUM_UINT8;

enum LPHY_CHANCTRL_CONTINUOUS_CA_ENUM
{
    LPHY_NON_CONTINUOUS_CA                = 0,                             /* LTE FDD ��ʽ */
    LPHY_CONTINUOUS_CA                    = 1,                             /* LTE TDD ��ʽ */
    LPHY_CA_TYPE_BUTT
};
typedef UINT8 LPHY_CHANCTRL_CONTINUOUS_CA_ENUM_UINT8;

enum LPHY_CHANCTRL_CROSS_CA_ENUM
{
    LPHY_NON_CROSS_CA                = 0,                             /* LTE FDD ��ʽ */
    LPHY_CROSS_CA                    = 1,                             /* LTE TDD ��ʽ */
    LPHY_CROSS_CA_TYPE_BUTT
};
typedef UINT8 LPHY_CHANCTRL_CROSS_CA_ENUM_UINT8;

typedef struct
{
    UINT16 ucCellId;
    UINT16 usFreqInfo;

    UINT8 ucBandInd;
    LPHY_CHANCTRL_BAND_WIDTH_ENUM_UINT8 ucBandWidth;
    LPHY_CHANCTRL_LTE_MODE_TYPE_ENUM_UINT8 ucLteModeType;
    UINT8 ucTmMode;

    UINT8 ucCellIndex;
    UINT8 ucRsv;
    UINT16 usRsv;
}LPHY_OM_CHANCTRL_CELL_STAT_STRU;

typedef struct
{
    LPHY_CHANCTRL_CROSS_CA_ENUM_UINT8 ucCrossCa;
    UINT8 ucScellCifPresent;
    UINT8 ucPdschStart;
    LPHY_CHANCTRL_CONTINUOUS_CA_ENUM_UINT8 ucContiCa;
}LPHY_OM_CHANCTRL_CELL_CA_STAT_STRU;

typedef struct
{
    LPHY_OM_CHANCTRL_CELL_STAT_STRU astCellStat[2];
    LPHY_OM_CHANCTRL_CELL_CA_STAT_STRU stCaStat;
}LPHY_OM_IND_CHANCTRL_STAT_STRU;
/************************************************************
                    4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_CHACNTRL_PBCH_SETUP           = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_CHACNTRL_PDSCH_BCCH_SETUP,
    LPHY_TRACE_CHACNTRL_PDSCH_PCH_SETUP,
    LPHY_TRACE_CHANCTRL_PDSCH_RACH_SETUP,
    LPHY_TRACE_CHANCTRL_PDSCH_DSCH_SETUP,
    /* BEGIN: Added by l00131321, 2012/12/19   ���ⵥ��:V7R2_MODIFY*/
    LPHY_TRACE_CHANCTRL_SCELL_PDSCH_DSCH_SETUP,
    LPHY_TRACE_CHANCTRL_PBCH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_BCCH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_PCH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_RACH_RELEASE,
    LPHY_TRACE_CHANCTRL_PDSCH_DSCH_RELEASE,
    /* BEGIN: Added by l00131321, 2012/12/19   ���ⵥ��:V7R2_MODIFY*/
    LPHY_TRACE_CHANCTRL_SCELL_PDSCH_DSCH_RELEASE,
    LPHY_TRACE_CHACNTRL_CAMPED_ON_MAIN_CELL,
    LPHY_TRACE_CHANCTRL_HANDOVER,
    LPHY_TRACE_CHANCTRL_SI_CONFIG,
    LPHY_TRACE_CHANCTRL_C_RNTI_CONFIG,
    LPHY_TRACE_CHANCTRL_TC_RNTI_CONFIG,
    LPHY_TRACE_CHANCTRL_TC_RNTI_TO_C_RNTI,
    LPHY_TRACE_CHANCTRL_PCH_STOP_BY_NC_BCH,
    LPHY_TRACE_CHANCTRL_ANR_READY,
    LPHY_TRACE_CHANCTRL_ANR_START,
    LPHY_TRACE_CHANCTRL_ANR_HOLD,
    LPHY_TRACE_CHANCTRL_ANR_TIME_OK,
    LPHY_TRACE_CHANCTRL_BLIND_HANDOVER,
    LPHY_TRACE_CHANCTRL_RELEASE_ALL,
    LPHY_TRACE_CHANCTRL_CHANNEL_RECONFIG,
    LPHY_TRACE_CHANCTRL_INITIAL_CELL_PBCH_SETUP,
    LPHY_TRACE_CHANCTRL_NEIGHBOUR_CELL_PBCH_SETUP,
    LPHY_TRACE_CHANCTRL_MAINCELL_PBCH_SETUP,
    LPHY_TRACE_CHANCTRL_INITIAL_CELL_BCCH_SETUP,
    LPHY_TRACE_CHANCTRL_NEIGHBOUR_CELL_BCCH_SETUP,
    LPHY_TRACE_CHANCTRL_MAINCELL_BCCH_SETUP,
    LPHY_TRACE_CHANCTRL_TRANSMISSION_MODE_UPDATA,
    LPHY_TRACE_CHANCTRL_CALLING_RFE_CHANGE,
    LPHY_TRACE_CHANCTRL_SCELL_ACT,
    LPHY_TRACE_CHANCTRL_SCELL_INACT,

}LPHY_CHANCTRL_TRACE_ENUM;

typedef UINT16 LPHY_CHANCTRL_TRACE_ENUM_UINT16;

typedef struct
{
    UINT16      usSysFrmNum;    /*ϵͳ֡��*/
    UINT16      usSubFrmNum;    /*��֡��*/
    UINT16      usSymbNum;      /*��ǰ������*/
    UINT16      usReserved;
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_TRACE_CHANCTRL_STRU;

/************************************************************
                    5. ERROR���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_ERROR_CHACNTRL_UL_MAILBOX_FEEDBACK_FAIL         = OM_CMD_ID(LPHY_CHANCTRL_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_CHACNTRL_SEARCH_CELL_FROM_CSLIST_FAIL,
    LPHY_ERROR_CHACNTRL_SERVE_CELL_STATE_ERROR,
    LPHY_ERROR_CHANCTRL_SETUP_TOO_MANY_CHANNELS,
    LPHY_ERROR_CHANCTRL_CANNOT_FIND_THE_SPECIAL_CHANNEL,
    LPHY_ERROR_CHANCTRL_TPC_RNTI_TYPE_ERROR,
    LPHY_ERROR_CHANCTRL_PRIMITIVE_PARA_ERROR,
    LPHY_ERROR_CHANCTRL_TIMING_START_ERROR,
    LPHY_ERROR_CHANCTRL_TIMING_STOP_ERROR,
    LPHY_ERROR_CHANCTRL_GET_TIMING_CELL_ERROR,
    LPHY_ERROR_CHANCTRL_GET_TIMING_NOTREADY_ERROR,
    LPHY_ERROR_CHANCTRL_BGS_PDS_BCH_CHANNEL_SETUP,
    LPHY_ERROR_CHANCTRL_BGS_PBCH_CHANNEL_SETUP,
    LPHY_ERROR_CHANCTRL_BGS_PCH_CHANNEL_SETUP,
#ifdef TLPHY_FEATURE_DSDS
    LPHY_ERROR_CHACNTRL_NO_RF_FAIL,
#endif
}LPHY_CHANCTRL_ERROR_ENUM;

typedef UINT32 LPHY_CHANCTRL_ERROR_ENUM_UINT32;

typedef struct
{
    UINT16      usSysFrmNum;    /*ϵͳ֡��*/
    UINT16      usSubFrmNum;    /*��֡��*/
    UINT16      usSymbNum;      /*��ǰ������*/
    UINT16      usReserved;
    UINT32      ulData1;
    UINT32      ulData2;
    UINT32      ulData3;
    UINT32      ulData4;
}LPHY_OM_ERROR_CHANCTRL_STRU;

typedef struct _LPHY_MAS_GETANT_OM_STRU_{
    UINT16        usCurAntIdx;
    UINT16        usNextAntIdx;
    UINT16        usSwitchFlg;
    UINT16        usMeasedAntNum ;
    UINT16        usInitAntIdx;
    UINT16        usRound;
}LPHY_MAS_GETANT_OM_STRU;
typedef struct _LPHY_MAS_CONN_PROBE_OM_STRU_{
    UINT16        usAntSwt;
    UINT16        usConflictWithPage;
    UINT16        usInHyst;
    UINT16        usGoodEnough;
    UINT16        usAntComplet;
    UINT16        usMeasSwt;
}LPHY_MAS_CONN_PROBE_OM_STRU;
/*һ��OM�ϱ�������ȡ��printf��ӡ �ϱ������ݲ��̶� �������ⶨλ ����չ*/
typedef struct _LPHY_MAS_TRACE_OM_STRU_{
    UINT32        ulOmType;
    INT32         slPrint1;
    INT32         slPrint2;
    INT32         slPrint3;
    INT32         slPrint4;
    UINT32        ulPrint5;
    UINT32        ulPrint6;
}LPHY_MAS_TRACE_OM_STRU;
typedef struct _LPHY_MAS_CONN_UPDATE_OM_STRU_{
    UINT16        usRcmState;
    UINT16        usRunState;
    INT32         slCurRsrp;
    INT32         slOutStbRsrpThr;
    INT32         slCurSinr;
    INT32         slOutStbSinrThr;
    UINT32        ulCurPoorCnt;
    UINT32        ulOutStbCntThr;
}LPHY_MAS_CONN_UPDATE_OM_STRU;
typedef struct _LPHY_MAS_COMPARE_OM_STRU_{
    INT32         slRsrpDelta;
    UINT32        ulDeltaHighThr;
    UINT32        ulDeltaLowThr;

    UINT8         ucRsv0;
    UINT8         ucCntHigh;
    UINT16        usCntHighThr;

    UINT8         ucRsv1;
    UINT8         ucCntLow;
    UINT16        usCntLowThr;

    UINT8         ucRsv2;
    UINT8         ucCntTotal;
    UINT16        usCntTotalThr;

    UINT8         ucSwtFlg;
    UINT8         ucCmpEndFlg;
    UINT16        usRsv3;
}LPHY_MAS_COMPARE_OM_STRU;


typedef UINT8 TAS_NEW_STATE_ENUM_UINT8;

typedef struct _ASU_DPDT_SWITCH_STRU_{
    INT32        lGiveConnRsrp0;
    INT32        lGiveConnRsrp1;
    INT32        lGiveIdleRsrp0;
    INT32        lGiveIdleRsrp1;
}ASU_DPDT_SWITCH_STRU;
/*����֡Ƶ���ϱ���TAS TRACE����Ҫ�ϱ���ǰ״̬�����о���ʵʱ״̬*/
typedef struct _TAS_ASU_STATE_OM_STRU_{
    UINT32                     ulRsv3;
    TAS_NEW_STATE_ENUM_UINT8   enTasNewState;      //��ǰLTE ASU����״̬
    TAS_NEW_STATE_ENUM_UINT8   enIdleLastHappyState;
    UINT16                     usCurrNGI_Sinr;     //idle̬�о�Ϊgood��sinr���ޣ���ͬ

    UINT16                     usCurrNPI_Sinr;
    UINT16                     usCurrNGI_Rsrp;

    UINT16                     usCurrNPI_Rsrp;
    TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //LTE ASUZ״̬ת��ǰ�ľ�״̬
    UINT8                      ucInitPrachState;

    UINT16                     usPrachFailNum;     //��ǰ��������ʧ�ܵĴ���
    UINT16                     usCurrNGC;          //��ǰ�����о�ΪGOOD�Ĵ���

    UINT16                     usCurrNPC;          //��ǰ�����о�ΪPOOR�Ĵ���
    UINT16                     usRsv2;

    ASU_DPDT_SWITCH_STRU       stIdleConnSubPara;

}TAS_ASU_STATE_OM_STRU;

typedef struct _TAS_ASU_DATA_OM_STRU_{
	TAS_ASU_STATE_OM_STRU stTasState;
	UINT32                ulDpdtCurrState;
	UINT32                ulRsv;
}TAS_ASU_DATA_OM_STRU;

/*���������л�ʱ��������������ֵ OM*/


typedef struct _TAS_DPDT_SWITCH_STRU_{
	ASU_DPDT_SWITCH_STRU stTasDpdtStru;

    UINT32               ulDpdtCurrState;
    UINT32               ulBlankType;
    UINT32               ulRsv;
}TAS_DPDT_SWITCH_STRU;

typedef struct
{
    UINT16  			  usMsgID;//����PHY���Բ�һ��
    UINT16				  usToolsID;
    UINT16                usCurrentBand;
    UINT16                usAuthorize;
	UINT16                usWholeRoundAnt;
    UINT16                usSingleRoundAnt;
    INT16                 ssCompareAnt0Signal;  /* �ȽϽ׶�����0����RSCP/RSRP*/
    INT16                 ssCompareAnt1Signal;  /* �ȽϽ׶�����1����RSCP/RSRP*/
    INT16                 ssCompareAnt2Signal;  /* �ȽϽ׶�����2����RSCP/RSRP*/
    INT16                 ssCompareAnt3Signal;  /* �ȽϽ׶�����3����RSCP/RSRP*/
}LTE_OM_DPDT_STATE_IND_STRU;

/*����IDLE GOOD/POOR CONN GOOD/POOR״̬��״̬����ʱ���ϱ��¾�״̬��dpdt״̬*/
typedef struct _ASU_STATE_STRU_{
    UINT32       ulTasNewState;
	UINT32       ulTasOldState;
	UINT32       ulDpdtCurrState;
	UINT32       ulRsv0;
	UINT32       ulRsv1;
}ASU_STATE_STRU;

/*�ϱ�LTEɨƵ�׶�����RSSI*/
typedef struct _TAS_BS_RSSI_OM_STRU_{
    SINT16       ssMaxRssi;
	UINT16       usRsv;
}TAS_BS_RSSI_OM_STRU;

/*TAS200 ����̬�յ��Ĳ���ģ���������������ֵ���������������߼����źŽϺõ�����*/
typedef struct _ASU_GIVE_RSRP_STRU_{
    INT32       slTasAnt0;
	INT32       slTasAnt1;
    UINT32      ulDpdtCurrState;	//��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    INT32       slTasAnt0Filter;
	INT32       slTasAnt1Filter;
	INT32       slTasAntDelta;
    UINT32      ulCnt;
    UINT32      ulRsv;
}ASU_GIVE_RSRP_STRU;

//����̬�ϱ�����PROTECT״̬ʱ������״̬
typedef struct _ASU_TAS_HYST_STRU_{
    UINT32      ulDpdtCurrState; //��ǰ��dpdt״̬ 1-����  0-ֱ̬ͨ
    UINT32      ulRsv;
}ASU_TAS_HYST_STRU;

/*idle̬ASU�յ����������������ϱ���OM*/
typedef struct _ASU_GIVE_IDLE_STRU_{
    UINT32                     ulRsv3;

    TAS_NEW_STATE_ENUM_UINT8   enTasNewState;
    UINT8                      ucRsv;
    UINT16                     usCurrNGI_Sinr;

    UINT16                     usCurrNPI_Sinr;
    UINT16                     usCurrNGI_Rsrp;

    UINT16                     usCurrNPI_Rsrp;
    TAS_NEW_STATE_ENUM_UINT8   enTasOldState;      //LTE ASUZ״̬ת��ǰ�ľ�״̬
    UINT8                      ucInitPrachState;
}ASU_GIVE_IDLE_STRU;

typedef struct _ASU_GIVE_IDLE_OM_STRU_{
    ASU_GIVE_IDLE_STRU stGiveIdle;
    INT32              lRsrpAnt0;
    INT32              lRsrpAnt1;
    INT32              lRsrpUse;
    INT32              lSinrUse;

    UINT32             ulDpdtCurrState;
    UINT32             ulRsv;
}ASU_GIVE_IDLE_OM_STRU;

/*DCH̬ASU�յ����������������ϱ���OM*/
typedef struct _ASU_GIVE_DCH_OM_STRU_{
    INT32         slDchNewState;
    INT32         slDchOldState;

    UINT16        usCurrNGC;
    UINT16        usCurrNPC;
    UINT8         ucDrxValidFlag;
    UINT8         ucRsv0;
    UINT16        usRsv1;
    INT32         lRsrpAnt0;
    INT32         lRsrpAnt1;
    INT32         lRsrpUse;
    INT32         lSinrUse;

    UINT32        ulDpdtCurrState;
    UINT32        ulRsv;
}ASU_GIVE_DCH_OM_STRU;

typedef struct _LPHY_MAS_CAP_CHANGE_INIT_STRU_{

    UINT16 usNvTasEna;
    UINT16 usNvMasEna;

    UINT16 usAtTasEna;
    UINT16 usAtMasEna;

    UINT16 usUpMasEna;
    UINT16 usDownMasEna;
    
	UINT16 usNvBandTas;
	UINT16 usNvBandMas;

    UINT16 usRcmTasState;
    UINT16 usRcmMasState;

    UINT16 usRunTasState;
    UINT16 usRunMasState;

    UINT16 usRcmGrant;
    UINT16 usUpdateFlg;

    UINT16 usBlindFlag;
    UINT16 usBlindNvFlg;
	
    UINT16 usAvoidPagingCfgFlag;
    UINT16 usWired;

	UINT16 usAsuRrcState;
	UINT16 usReqEmuFlg;

	UINT16 usAntStubFlg;
	UINT16 usIsProbeAntFlg;
	
    UINT16 usAntInit;
    UINT8 ucAntInitIdx;
    UINT8 ucCurrAntIdx;
    
    UINT16 usRsv1;
    UINT16 usRsv2;
    

}LPHY_MAS_CAP_CHANGE_INIT_STRU;

/*TAS OM REPORT end k3v3+tas*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHANCTRL_OM_DEF_H__ */

