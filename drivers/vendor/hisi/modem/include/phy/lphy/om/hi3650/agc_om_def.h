/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
 �� �� ��   : AFC.h
 �� �� ��   : ����
 ��    ��   : Shen Guang
 ��������   : 2010��12��23��
 ����޸�   :
 ��������   : AFC��ͷ�ļ�
 �����б�   :
 �޸���ʷ   :
 1.��    ��   : 2010��12��23��
   ��    ��   : Shen Guang
   �޸�����   : �����ļ�
 2.��    ��   : 2012��04��17��
   ��    ��   : Shen Guang
   �޸�����   : [DTS2012022700423]FDD-TDD������
 3.��    ��   : 2012��05��05��
   ��    ��   : Shen Guang
   �޸�����   : [DTS2012050201496]�޸�AGCפ��ʧ������

******************************************************************************/


#ifndef __AGC_OM_DEF_H__
#define __AGC_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
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

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum
{
    LPHY_REQ_AGC_REPORT_ENA         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RSSI_DS_FRAME_CONFIG_ENA,
    LPHY_REQ_RSSI_GAP_MODE_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_RF_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_PRE_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_FIXED_POST_GAIN_CONFIG_ENA,
    LPHY_REQ_AAGC_ANTENNA_ADJUST_CONFIG_ENA,
    LPHY_REQ_AAGC_INTERFERENCE_CONFIG_ENA,
    LPHY_REQ_AAGC_DEM_PERIOD_CONFIG_ENA,
    LPHY_REQ_AAGC_PRE_TARGET_CONFIG_ENA,
    LPHY_REQ_AAGC_POST_TARGET_CONFIG_ENA,
    LPHY_REQ_AAGC_RS_DIFF_THRE_CONFIG_ENA,
    LPHY_REQ_AAGC_TDD_BLOCK_POWER_THRE_CONFIG_ENA,
    LPHY_REQ_AAGC_TDD_BLOCK_GAIN_STEPSIZE_CONFIG_ENA,
    LPHY_REQ_DAGCF_FIXED_GAIN_CONFIG_ENA,
    LPHY_REQ_DAGCF_ADJ_BIT_CONFIG_ENA,
    LPHY_REQ_DAGCF_EXTRA_PA_CONFIG_ENA,
    LPHY_REQ_DAGCF_SHIFT_BIT_CONFIG_ENA,
    LPHY_REQ_AGC_SPECIAL_SENARIO_CONFIG_ENA,
    LPHY_REQ_TRIGGER_RFIN_SAMPLING_ENA,
    LPHY_REQ_1SUBF_PWRDIFF_THR_CONFIG_ENA,
    LPHY_REQ_HRL_INTERFACE_RPT_ENA,
    LPHY_REQ_HRL_STATUS_RPT_ENA,
    LPHY_REQ_HRL_NV_INFO_RPT_ENA,
    LPHY_REQ_HRL_ENABLE_ENA,
    LPHY_REQ_HRL_FIX_THR_COEF_ENA,
    LPHY_REQ_HRL_FIX_COM_COEF_ENA,
    LPHY_REQ_HRL_FIX_FILTER_IN_FOESET_ENA,
    LPHY_REQ_HRL_FIX_WORK_MODE_ENA,
    LPHY_REQ_HRL_FIX_SUPPRESS_IDX_ENA,
    LPHY_REQ_HRL_FIX_COMEN_ENA,
    LPHY_REQ_HRL_SET0_INTERFACE_RPT_ENA,
    LPHY_REQ_HRL_FIX_COM_IDX_ENA
}LPHY_REQ_AGC_ENUM;

/* BEGIN: Added by s00175552, 2011/6/27   ���ⵥ��:DTS2011062704134*/
typedef enum
{
    AGC_OM_SWITCH_OFF = 0,
    AGC_OM_SWITCH_ON,
}AGC_OM_SWITCH_ENUM;
typedef UINT16 AGC_OM_SWITCH_ENUM_UINT16;
typedef UINT32 AGC_OM_SWITCH_ENUM_UINT32;


typedef enum
{
    DEBUG_RFIN_NO_TRIGGER = 0,
    DEBUG_RFIN_SAMPLING_ENABLE,
    DEBUG_RFIN_PBCH_FAILURE,
    DEBUG_RFIN_GAP_INTER_FREQ_START,
    DEBUG_RFIN_IDLE_INTER_FREQ_START,
    DEBUG_RFIN_INTER_FREQ_FINISH,
    DEBUG_RFIN_PRE_DEFINED_SUBFRAME,
    DEBUG_RFIN_DLSCH_CRC,
    DEBUG_RFIN_BCCH_CRC,
    DEBUG_RFIN_PCH_CRC,
    DEBUG_RFIN_TIMING_ERROR,
    DEBUG_EMU_ABNORMAL_RPT,
    DEBUG_CMU_ABNORMAL_RPT,
    DEBUG_AFC_ABNORMAL_RPT
}LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM;
typedef UINT16 LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM_UINT16;

typedef struct
{
    LPHY_DEBUG_RFIN_SAMPLING_TYPE_ENUM  enRfinSamplingTrigger;
    UINT32                              ulCounter;
    UINT16                              usFreqInfo;
    UINT16                              usCellId;
    INT16                               sUpThreshold;
    INT16                               sLowThreshold;
    UINT16                              usEmuMode;
    UINT16                              enCcIndex;
}LPHY_DEBUG_RFIN_SAMPLING_CTRL_STRU;
typedef struct
{
    AGC_OM_SWITCH_ENUM    enReportEn;    /*1 ʹ��AFC״̬�ϱ�*/
}LPHY_REQ_AGC_REPORT_ENA_STRU;
/* END: Added by s00175552, 2011/6/27   ���ⵥ��:DTS2011062704134*/

typedef enum
{
    AGC_USE_ALL_DS_FRAME = 0,
    AGC_USE_LAST_DS_FRAME,
    AGC_USE_LAST_0_5_DS_FRAME,
}AGC_DEM_SUBFRAME_SEL_ENUM;
typedef UINT16  AGC_DEM_SUBFRAME_SEL_ENUM_UINT16;

typedef enum
{
    AGC_GAP_FAST = 0,
    AGC_GAP_FAST_SLOW =1,
    AGC_GAP_SLOW = 2,
}AGC_GAP_MODE_SEL_ENUM;
typedef UINT16  AGC_GAP_MODE_SEL_ENUM_UINT16;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT32     lFixedRssi;

}LPHY_REQ_RSSI_FIXED_VALUE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    AGC_DEM_SUBFRAME_SEL_ENUM     enDemSubFrameSel;
}LPHY_REQ_RSSI_DS_FRAME_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    AGC_GAP_MODE_SEL_ENUM     enGAPModeSel;
}LPHY_REQ_RSSI_GAP_MODE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulRssiPoint;
}LPHY_REQ_RSSI_POINT_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulRssiCompensate;
}LPHY_REQ_RSSI_COMPEMSATE_CONFIG_ENA_STRU;

typedef enum
{
    AGC_INDEPENDENT_ANTENNA,
    AGC_COMBINED_ANTENNA,
    AGC_NOISE_DECIDED,
    AGC_ON_AIR,
}AGC_ANT_CONFIG_ENUM;
typedef UINT16  AGC_ANT_CONFIG_ENUM_UINT16;

typedef enum
{
    AGC_NO_INTERFERENCE =0,
    AGC_ACS_INTERF_VAR,
    AGC_ACS_INTERF_CONST,
    AGC_NB_INTERF_VAR,
    AGC_NB_INTERF_CONST,
    AGC_INTERF_BUTT,
}AGC_INTERFERENCE_TYPE_ENUM;
typedef UINT16  AGC_INTERFERENCE_TYPE_ENUM_UINT16;

typedef enum
{
    AGC_DEM_PERIOD_1MS = 0,
    AGC_DEM_PERIOD_5MS,
    AGC_DEM_PERIOD_10MS,
    AGC_DEM_PERIOD_20MS,
    AGC_DEM_PERIOD_BUTT,
}AGC_DEM_MODE_SEL_ENUM;
typedef UINT16  AGC_DEM_MODE_SEL_ENUM_UINT16;
typedef enum
{
    AGC_RF_IDX0 = 0,
    AGC_RF_IDX1,
    AGC_RF_IDX2,
    AGC_RF_IDX3,
    AGC_RF_IDX4,
    AGC_RF_IDX5,
    AGC_RF_IDX6,
    AGC_RF_IDX7,
    AGC_RF_IDX8,
    AGC_RF_IDX9,
    AGC_RF_IDX10,
    AGC_RF_IDX11,
    AGC_RF_IDX12,
    AGC_RF_IDX13,
    AGC_RF_IDX14,
    AGC_RF_IDX15,
}AGC_RF_IDX_ENUM;
typedef UINT16  AGC_RF_IDX_ENUM_UINT16;
typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    AGC_RF_IDX_ENUM_UINT16       aenFixedRfIdx[2][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_RF_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT16     asFixedPreDagcGain[2][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_PRE_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT16     asFixedPostDagcGain[2][LPHY_MAX_RX_ANTENNA_NUM];//om for ca
}LPHY_REQ_AAGC_FIXED_POST_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    AGC_ANT_CONFIG_ENUM     enAntennaConfig; // default AGC_ON_AIR
}LPHY_REQ_AAGC_ANTENNA_ADJUST_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    AGC_INTERFERENCE_TYPE_ENUM      enInterfConfig;
}LPHY_AGC_OM_INTERF_CONFIG_STRU;

typedef struct
{
	LPHY_AGC_OM_INTERF_CONFIG_STRU astInterfConfig[2];//om for ca
}LPHY_REQ_AAGC_INTERFERENCE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
}LPHY_REQ_AAGC_GAIN_SWITCH_DELAY_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
}LPHY_REQ_AAGC_IDX_SWITCH_DELAY_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    AGC_DEM_MODE_SEL_ENUM      enDemPeriodSel;
}LPHY_REQ_AAGC_DEM_PERIOD_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT32     lPowerCalcConst;
}LPHY_REQ_AAGC_POWER_CALC_CONST_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT32     lPreTarPower;
}LPHY_REQ_AAGC_PRE_TARGET_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT32     lPostTarPower;
}LPHY_REQ_AAGC_POST_TARGET_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
}LPHY_REQ_AAGC_PRE_DAGC_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
}LPHY_REQ_AAGC_POST_DAGC_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulNoiseLimit;
}LPHY_REQ_AAGC_NOISE_LOWER_BOUNDARY_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulRsDifThre;
}LPHY_REQ_AAGC_RS_DIFF_THRE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT32     lTddBlockPowerThresh;
}LPHY_REQ_AAGC_TDD_BLOCK_POWER_THRE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    INT32     lTddBlockGainStep;
}LPHY_REQ_AAGC_TDD_BLOCK_GAIN_STEPSIZE_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    aulFixedDagcFGain[2];//om for ca
}LPHY_REQ_DAGCF_FIXED_GAIN_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulAdjBit;
}LPHY_REQ_DAGCF_ADJ_BIT_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulExtraPA;
}LPHY_REQ_DAGCF_EXTRA_PA_CONFIG_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulBitShift;
}LPHY_REQ_DAGCF_SHIFT_BIT_CONFIG_ENA_STRU;
typedef struct
{
    AGC_OM_SWITCH_ENUM    enEnable;
    UINT32    ulNoiseFactor;
}LPHY_REQ_DAGCF_FIXED_NOISE_ENA_STRU;
typedef struct
{
    AGC_OM_SWITCH_ENUM    enCase1Enable;
    AGC_OM_SWITCH_ENUM    enCase3Enable;
    AGC_OM_SWITCH_ENUM    enCase4Enable;
    AGC_OM_SWITCH_ENUM    enCase6Enable;
}LPHY_REQ_AGC_SPECIAL_SENARIO_CONFIG_ENA_STRU;
/*v7r2 add*/
typedef struct
{
    AGC_OM_SWITCH_ENUM  enEnable;
	INT16 				sSymolbPwrDiffThr;
	INT16 				sFreqTimePwrDiffThr;
}LPHY_REQ_1SUBF_PWRDIFF_THR_CONFIG_ENA_STRU;

typedef enum
{
    HRL_SWITCH_OFF = 0,
    HRL_SWITCH_ON,
}HRL_SWITCH_ENUM;
typedef UINT16 HRL_SWITCH_ENUM_UINT16;
typedef UINT32 HRL_SWITCH_ENUM_UINT32;


typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
}LPHY_REQ_HRL_INTERFACE_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
}LPHY_REQ_HRL_STATUS_RPT_ENA_STRU;

typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
}LPHY_REQ_HRL_NV_INFO_RPT_ENA_STRU;

/*г��,DC �������� */
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT16 usRsv;
    UINT16 usDemHarIdx[2];
    UINT16 usDemDcIdx[2];
    UINT16 usMeasHarIdx[2];
    UINT16 usMeasDcIdx[2];
}LPHY_REQ_HRL_FIX_SUPPRESS_ENA_STRU;

/*г������ʹ�ܴ�׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    HRL_SWITCH_ENUM_UINT32 enHrlSwitch[2];
}LPHY_REQ_HRL_ENA_CFG_STRU;

/*HRL ����ģʽ��׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT8 ucHrlMode[2];
}LPHY_REQ_HRL_FIX_WORK_MODE_CFG_ENA_STRU;

/*ֱ��ƫ�ô�׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    INT32 lFilterInFOest[2];
}LPHY_REQ_HRL_FIX_FOEST_ENA_STRU;

/*����ϵ����׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    SINT16 sComCoefReal[2];
    SINT16 sComCoefImg[2];
}LPHY_REQ_HRL_FIX_COM_COEF_ENA_STRU;

/*��������ϵ����׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT16  enEnable;
    UINT8 ucThrCoef[2];
}LPHY_REQ_HRL_FIX_THR_COEF_ENA_STRU;

/*��������ϵ����׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    HRL_SWITCH_ENUM_UINT32 enHrlComSwitch[2];
}LPHY_REQ_HRL_FIX_COMEN_ENA_STRU;

/*г����ֵ����ӿ���Ϣ�ϱ�����*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
}LPHY_REQ_HRL_SET0_INTERFACE_RPT_ENA_STRU;

typedef struct
{
    UINT16 usComIdx;
    UINT8  aucComFlag[2][3]; //2r 3idx
}LPHY_REQ_HRL_FIX_COM_IDX_STRU;

/*����������׮*/
typedef struct
{
    AGC_OM_SWITCH_ENUM_UINT32  enEnable;
    LPHY_REQ_HRL_FIX_COM_IDX_STRU stHarComInfo[2];  //2cc
    LPHY_REQ_HRL_FIX_COM_IDX_STRU stDcComInfo[2];   //2cc
}LPHY_REQ_HRL_FIX_COM_IDX_ENA_STRU;


/************************************************************
                           3. Sg���ݽṹ����
************************************************************/

typedef enum
{
    LPHY_SG_AAGC_REPORT_ENA         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_DAGC_REPORT_ENA         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x1),
    LPHY_SG_MAGC_REPORT_ENA         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_SG, 0x2),
}LPHY_SG_AGC_ENUM;

typedef struct
{
    INT16     sPreTargetPower;
    INT16     sPostTargetPower;
}AGC_TARGET_POWER_STRU;


typedef struct
{
	INT32   alPreRssiSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];			//pre-rssi dB �����ۺ�
	INT32	alPostRssiSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];			//post-rssi dB �����ۺ�
	INT32	alInbandSymbolAcc[LPHY_MAX_RX_ANTENNA_NUM];				//inband dB �����ۺ�
	INT32	alCRSSubframeAcc[LPHY_MAX_RX_ANTENNA_NUM];				//ÿ��֡ƽ��CRS dB��֡���ۺ�
	UINT8	ucSymbolNum;
	UINT8	ucSubframeNum;
	UINT8   ucReserved[2];
}AGC_ACC_INFO_STRU;

typedef struct
{
	AGC_ACC_INFO_STRU stAccInfo;									//ͳ�������ۺ�
    INT16     asPreRssidB[LPHY_MAX_RX_ANTENNA_NUM];                 //��������0/1���˲�ǰʱ��DAGC��RSSI ƽ��ֵ
    INT16     asPreDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM];         		//��������0/1���˲�ǰʱ��DAGC����
    INT16     asPreAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];           	//�˲�ǰ��������0/1���߿ڹ���,dBm
    INT16     asPostRssidB[LPHY_MAX_RX_ANTENNA_NUM];                //�˲����������0/1��ʱ��DAGC��RSSI ƽ��ֵ
    INT16     asPostDAGCTgain[2][LPHY_MAX_RX_ANTENNA_NUM];       		//�˲����������0/1��ʱ��DAGC����, none-ABS��ABS
    INT16     asPostAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];          	//�˲����������1���߿ڹ���,dBm
    INT16     asAAGCgain[LPHY_MAX_RX_ANTENNA_NUM];             		//��������0/1��AAGC����
    UINT16    ausLNAGain[LPHY_MAX_RX_ANTENNA_NUM];             		//��ǰ��������0/1��LNA��λ
    UINT16    ausRFGain[LPHY_MAX_RX_ANTENNA_NUM];
    UINT16    ausRFIdex[LPHY_MAX_RX_ANTENNA_NUM];
    AGC_RF_IDX_ENUM_UINT16    aenFinalIdx[LPHY_MAX_RX_ANTENNA_NUM];
    AGC_INTERFERENCE_TYPE_ENUM_UINT16    aenAAGCIdxSel[LPHY_MAX_RX_ANTENNA_NUM];          //��������0/1����ѡ���ź�
    /*last Value*/
    UINT16    ausLastRfGain[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1��AAGC����
    INT16     asLastPreAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1��AAGC����
    INT16     asLastPostAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];
    INT16     asLastCrsAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];

    INT16     asLastAAGCgain[LPHY_MAX_RX_ANTENNA_NUM];      //��������0/1��AAGC����
    INT16     asLastPreDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM];  //�˲����������0/1��ʱ��DAGC����
    INT16     asLastPostDAGCTgain[LPHY_MAX_RX_ANTENNA_NUM]; //��������0/1��AAGC����alex tbd abs

    /*��ģ��������*/
     UINT8    ucFixAgcFlag;                                /*��Ƶ��̶�AGC��ʶ*/
     UINT8    ucReserved;                                     /*����ʱ��*/
     UINT8    ucLastFixAgcFlag;
     UINT8    ucBigIdx;
    /*END*/
    INT16     asInBanddB[LPHY_MAX_RX_ANTENNA_NUM];                	//ƽ����InBand����ͳ��δ�۵����߿ڣ�����CA�����������Ƶ��ΪSum_InBand
    INT16     asInBandAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];         	//asInBanddB ���㵽���߿�
    INT16     asCRSdB[LPHY_MAX_RX_ANTENNA_NUM];                		//ƽ����CRS����ͳ��δ�۵����߿ڣ�����CA�����������Ƶ��ΪSum_CRS
    INT16     asCRSAntPwrdBm[LPHY_MAX_RX_ANTENNA_NUM];              //asCRSdB ���㵽���߿�
	AGC_INTERFERENCE_TYPE_ENUM_UINT16 enInterfInd;
	UINT16    usReserved2;
}AAGC_PARA_STRU;

typedef struct
{
    UINT32    aulSym0Pwr[2][LPHY_MAX_RX_ANTENNA_NUM];//cc0 cc1
    UINT16    ausSym0PwrInv[2];//cc0 cc1
	UINT32	  aulCSIDAGCFGain[2];//cc0 cc1
    UINT32    aulDAGCFGain[2];              //cc0 cc1��ǰ��֡DAGCF������ֵ
    //UINT16    usDAGCFSftBit;            //���ݷ������߸�����ϵͳ����,�����������л���Ҫ�任
    //UINT16    usDAGCFPAFac;             //���ݴ���ģʽ��PA�������õ�,�ڷ���2�ж��и���
    INT16     asAGCNoiseFactor[2];         //��������PCC SCC
    UINT16    ausDAGCFTar[2];               //����ADJBit�õ�,����DAGCFĿ�깦��,�ڷ���2�ж��и���
    UINT8     ucCounter1;
    UINT8     ucCounter3;
    UINT8	  aucRsv[2];
}DAGCF_PARA_STRU;

typedef struct
{
    UINT8     ucIndepAGCFlag;
    UINT8     ucFreqIndex;
    UINT16    usFreqInfo;
    AAGC_PARA_STRU    stAAGCPara;
}LPHY_AGC_OM_AAGC_REPORT_ONE_CC_STRU;

typedef struct
{
	LPHY_AGC_OM_AAGC_REPORT_ONE_CC_STRU astAAgcPara[3];//om for ca
} LPHY_SG_AAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT8     aucAgcPaValue[2];                //PA ����cc0 cc1
    UINT8     aucExtraPa[2];                   //Extra PA   cc0 cc1
    UINT8     ucMflag;
    UINT8     ucReserved;
    UINT16    usSubFrameNum;// = SCHED_GetSubFrmNum();
    DAGCF_PARA_STRU   stDAGCFPara;             //��ǰ��֡DAGCF�Ĳ���
} LPHY_SG_DAGC_REPORT_ENA_STRU;

typedef struct
{
    UINT16    usMs1DagcfGain;
    UINT16    usMDagcfGain;

    UINT16    usDagcfGainDiff;
    UINT16    usDagcfGainCoef;

    INT16     sOutDiffPowdBm;//PMCH��֡��֮ǰ���ڵĵ�����֡�˲������߿ڹ���֮��
    UINT16    usReserved;

    AAGC_PARA_STRU    stMAGCPara;
} LPHY_SG_MAGC_REPORT_ENA_STRU;





/* END: Added by s00175552, 2011/8/01   ���ⵥ��:DTS2011080101213*/

/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_TRACE_AGC_STATE         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_TRACE, 0x1),
    LPHY_TRACE_AGC_TDD_BLOCK_EVENT,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_1,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_3,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_4,
    LPHY_TRACE_AGC_SPECIAL_SENARIO_6,
    LPHY_TRACE_AGC_FREQ_INFO,
    LPHY_TRACE_AGC_EMBMS_FRAME,
    LPHY_TRACE_AGC_BAND_INFO,
    LPHY_TRACE_AGC_DVTY_INFO,
    LPHY_TRACE_HRL_STATUS_INFO,
    LPHY_TRACE_HRL_INTERFACE_RSRP_INFO,
    LPHY_TRACE_HRL_INTERFACE_FOEST_INFO,
    LPHY_TRACE_HRL_NV_INFO,
    LPHY_TRACE_HRL_SET0_INTERFACE_INFO
}LPHY_TRACE_AGC_ENUM;


typedef enum
{
    AGC_BAND_SCAN = 0,                                /*ɨƵģʽ*/
    AGC_INIT_CELL_SEARCH,                             /*��ʼС������ģʽ��RSSIͳ��ʱ��5ms��ʹ��ȫ����������*/
    AGC_DEMOD,                                        /*���ģʽ��RSSIͳ��ʹ�õ�Ƶ����*/
    AGC_GAP,                                          /*GAP��Ƶģʽ*/
    AGC_DRX,                                          /*DRX��Ƶģʽ*/
    AGC_FIXED_GAIN0,                                  /*�̶�����*/
    AGC_FIXED_GAIN1,
    AGC_NULL
} AGC_WORKING_MODE_ENUM;
typedef UINT16 AGC_WORKING_MODE_ENUM_UINT16;


typedef struct
{
    LTE_BAND_WIDTH_ENUM_UINT16      enAGCRFBW;     /*RF�˲�������*/
    LTE_BAND_WIDTH_ENUM_UINT16      enAGCBBBW;     /*�����˲�������*/
} AGC_BW_CHANGE_STRU ;

typedef struct
{
    UINT16                             usAGCFreqInfo; 							/*AGCƵ����Ϣ*/
    UINT16                             usBand;
    AGC_BW_CHANGE_STRU                 stAGCBWChange; 							/*AGC����仯*/
}AGC_FREQUENCY_INFO_STRU;

typedef struct
{
	AGC_FREQUENCY_INFO_STRU			   	astAgcFreqInfo[3]; 						/*agc Ƶ����Ϣ�����ģʽƵ�����PCC SCC CONT_CC*/
	LTE_FRAME_TYPE_ENUM_UINT16         	enFrametype;
    AGC_WORKING_MODE_ENUM_UINT16       	enAAGCMode;    							/*��ǰ��֡AAGC����ģʽ*/
    UINT32                             	ulBaseCellPos;
    UINT8								ucCaActive;								/*���ģʽCA��Ч��־*/
    UINT8								ucContCaValid;							/*��ucCaActive��Чָʾ�Ƿ�Ϊ����CA*/
} AGC_MODE_CFG_REQ_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT16      usReserved;
    AGC_MODE_CFG_REQ_STRU            stAgcModeCfg;
}LPHY_TRACE_AGC_STATE_STRU;

typedef struct
{
    UINT32      ulSubframe;
}LPHY_TRACE_AGC_EMBMS_FRAME_STRU;

typedef enum
{
    AGC_ENTER_TDD_BLOCK_STATE = 0,
    AGC_TDD_BLOCK_INC_PWR,
    AGC_TDD_BLOCK_REACH_MAX_GAIN,
}AGC_TDD_BLK_EVENT_TRACE_ENUM;

typedef struct
{
    INT16     sCounter;
    UINT16    usState;
}AGC_SPECIAL_SENARION_TRACE_STRU;
typedef struct
{
    AGC_TDD_BLK_EVENT_TRACE_ENUM    enEvent;
}LPHY_TRACE_TDD_BLK_STRU;

typedef enum
{
    AGC_CONFIG_SCELL_FREQ_INFO = 0,                     						/*����AGC������Ƶ����Ϣ(����CA��Ϣ�仯)*/
    AGC_CONFIG_NCELL_FREQ_INFO,                         						/*����AGC��ƵƵ����Ϣ*/
    AGC_SWITCH_SCELL_FREQ_INFO,                        	 						/*�л�AGC������Ƶ��*/
} AGC_FREQ_CMD_ENUM;
typedef UINT16 AGC_FREQ_CMD_ENUM_UINT16;

#define AGC_FREQ_CONFIG_NUM_MAX         (LPHY_FEATURE_MAX_INTER_EMU_NUM)
typedef struct
{
    AGC_FREQ_CMD_ENUM_UINT16            enAGCFreqCmd;							/*Ƶ����������*/
    UINT16                              usAGCNumOfFreq;							/*Ƶ�����ø���*/
    UINT16                              usAGCFreqInfo[AGC_FREQ_CONFIG_NUM_MAX];	/*��Ϊ���û��л���������Ƶ�����PCC SCC CONT_CC*/
    UINT16								ausBand[AGC_FREQ_CONFIG_NUM_MAX];		/*��Ϊ���û��л���������BAND�ŷ���PCC SCC CONT_CC*/
} AGC_FREQ_INFO_STRU;

typedef struct
{
	CHANCTRL_CA_IND_ENUM_UINT16			enCaInd;			/*��ǰCAָʾ*/
    UINT16                              usAGCNumOfFreq;     /*������Ƶ�������CAΪ2����CAΪ1*/
    UINT16                              usAGCFreqInfo[2];	/*Ƶ�����PCC SCC */
    UINT16								ausBand[2];			/*Ƶ�η���PCC SCC*/
}AGC_CHANCTRL_CA_INFO_STRU;

typedef struct
{
    AGC_FREQ_INFO_STRU      stFreqInfo;
}LPHY_TRACE_FREQ_INFO_STRU;

/*band ���nv buffer*/
typedef enum
{
    AGC_SERV_CELL_NV_INDEX = 0,
    AGC_NEIGHBOR_CELL_NV_INDEX,
}AGC_CELL_NV_TYPE_ENUM;
typedef UINT16   AGC_CELL_NV_TYPE_ENUM_UINT16;
typedef struct
{
    UINT16    usBandInd;
    AGC_CELL_NV_TYPE_ENUM_UINT16  enCellInd;
    UINT16    usOldIndex;
    UINT16    usNewIndex;
}LPHY_TRACE_BAND_INFO_STRU;

#define     HRL_MAX_FREQ_NUM 	        (6)
#define     HRL_MAX_SYM_NUM 	        (4)
#define     HRL_MAX_IDX_NUM  	        (3)
#define     HRL_MAX_COM_IDX_NUM  	    (6)
#define     HRL_MAX_HAR_COM_IDX_NUM  	(3)

typedef struct
{
    UINT8  ucMbmsFlg[HRL_MAX_SYM_NUM];
    INT8  ucBbpRptSuppIdx[HRL_MAX_SYM_NUM][HRL_MAX_IDX_NUM];
}HRL_BBP_RESULT_STRU;

typedef struct
{
    UINT8 	ucHarSwitch; 	         //0:off 1:on
    UINT8  ucDcSwitch;              //DCƫ��������Ч��־,��ʼ��Ĭ��ΪLPHY_FALSE
    UINT16  usSpurFreqInfo;

    LTE_BAND_WIDTH_ENUM_UINT16	enBWDem;	            //��Ч�Ľ������
    LTE_BAND_WIDTH_ENUM_UINT16	enBWMeas;	            //��Ч�Ĳ�������

    UINT16  usDemNre;                   //�������ز����뵱ǰ�����й� [72 180 300 600 900 1200]
    UINT16  usMeasNre;                  //�������ز����뵱ǰ�����й� [72 180 300 600 900 1200]

    UINT16 	usHarDemSuppIdx;           //���ͨ·г�������������ز�����
    UINT16 	usHarMeasSuppIdx;          //����ͨ·г�������������ز�����

    UINT16 	usDcDemSuppIdx;            //DCƫ�������������ز�����
    UINT16 	usDcMeasSuppIdx;           //DCƫ�������������ز�����

    UINT16  usHarComIdx;               //hrl ��������
    UINT16  usDcComIdx;                //dc ��������

    HRL_BBP_RESULT_STRU stHarBbpResult[LPHY_MAX_RX_ANTENNA_NUM]; //г��������Ϣ�ϱ�
    HRL_BBP_RESULT_STRU stDcBbpResult[LPHY_MAX_RX_ANTENNA_NUM];  //dc������Ϣ�ϱ�
    UINT8 ucComFlag[LPHY_MAX_RX_ANTENNA_NUM][HRL_MAX_COM_IDX_NUM];
    UINT8 ucDemSet0Flag[LPHY_MAX_RX_ANTENNA_NUM][HRL_MAX_COM_IDX_NUM];
}HRL_CTRL_STRU;

typedef struct
{
    UINT16 usFreqInfo;
    UINT16 usBand;

    LPHY_CA_CC_ENUM_UINT16 enCc;
    UINT8 usHrlWorkState;
    UINT8 usRsv;

	HRL_CTRL_STRU stCtrlRpt;
}LPHY_HRL_STATUS_RPT_ENA_STRU;

typedef struct
{
    UINT8 ucHarSwitch;
    UINT8 ucDcSwitch;
    UINT8 ucHarSpurFreqNum; //г������Ƶ�����  С��AGC_HRL_MAX_HAR_FREQ_NUM
    UINT8 ucRsv;
    UINT16 ausHarSpurFreqInfo[AGC_HRL_MAX_HAR_FREQ_NUM];
}LPHY_HRL_SPUR_RPT_STRU;


typedef struct
{
    SINT16 sRsrp;
    UINT16 usRsv;
}LPHY_HRL_INTERFACE_RSRP_STRU;

typedef struct
{
    SINT32 lFilterInFOest;
}LPHY_HRL_INTERFACE_FOEST_STRU;


/************************************************************
                           5. ERROR���ݽṹ����
************************************************************/
typedef enum
{
    LPHY_ERROR_AGC_ARRAY_INDEX         = OM_CMD_ID(LPHY_AGC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_AGC_CASE,
    LPHY_ERROR_AGC_FREQ_INFO,
    LPHY_ERROR_AGC_ISR_BLOCK,
    LPHY_ERROR_AGC_ZERO_DIV,
}LPHY_ERROR_AGC_ENUM;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulIncorrectValue;
}LPHY_ERROR_AGC_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulCurrentCase;
    UINT32      ulLastCase;
}LPHY_ERROR_AGC_CASE_STRU;

typedef struct
{
    UINT32      ulLineNum;//__LINE__
    UINT32      ulFreqInfo;
}LPHY_ERROR_AGC_FREQ_INFO_STRU;

typedef struct
{
    UINT32      ultimeout;
}LPHY_ERROR_AGC_ISR_BLOCK_STRU;
typedef struct
{
    UINT32      ulAgcMode;
}LPHY_ERROR_AGC_ISR_DELAY_STRU;


typedef struct
{
    UINT32      ulDvtyAntIdx;
}LPHY_TRACE_AGC_DVTY_ANT_IDX_STRU;

typedef struct
{
	UINT8              usDcSuppressNum;
	UINT8              usHarSuppressNum;
    UINT16             ausSuppressIdx[6]; //0-2г�� 3-5 dc
}HRL_SET0_INTERFACE_RPT_STRU;


typedef union
{
    LPHY_TRACE_AGC_STATE_STRU         stAgcStateTrace;
    /* BEGIN: Added by s00175552, 2011/7/13   ���ⵥ��:DTS2011062704134*/
    LPHY_TRACE_TDD_BLK_STRU           stAgcTddBlockEvent;
    LPHY_TRACE_AGC_EMBMS_FRAME_STRU   stAgcEmbmsTrace;
    AGC_SPECIAL_SENARION_TRACE_STRU   stAgcSpecialSenario;
    /* BEGIN: Added by s00175552, 2011/8/01   ���ⵥ��:DTS2011080101213*/
    LPHY_TRACE_FREQ_INFO_STRU        stAGCFreqInfo;
    /* END: Added by s00175552, 2011/8/01   ���ⵥ��:DTS2011080101213*/
    /* END: Added by s00175552, 2011/7/13   ���ⵥ��:DTS2011062704134*/
    //AGC_SPECIAL_SENARION_TRACE_STRU   stAgcSpecialSenario3;
    //AGC_SPECIAL_SENARION_TRACE_STRU   stAgcSpecialSenario4;
    //AGC_SPECIAL_SENARION_TRACE_STRU   stAgcSpecialSenario6;
    //LPHY_ERROR_AGC_ARRAY_INDEX_STRU   stAgcArrayIndexError;
    LPHY_ERROR_AGC_CASE_STRU          stAgcCaseError;
    LPHY_ERROR_AGC_FREQ_INFO_STRU     stAgcFreqInfoError;
    LPHY_ERROR_AGC_ISR_BLOCK_STRU     stAgcIsrBlockError;
    LPHY_TRACE_AGC_DVTY_ANT_IDX_STRU  stAgcDvtyAntIdx;
}AGC_OM_REPORT_UNION;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __AGC_OM_DEF_H__ */

