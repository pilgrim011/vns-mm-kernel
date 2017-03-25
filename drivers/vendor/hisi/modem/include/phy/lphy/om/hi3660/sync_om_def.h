/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sync_om_def.h
  �� �� ��   : ����
  ��    ��   : tuzhiguo(52067)
  ��������   : 2010��12��29��
  ����޸�   :
  ��������   : ����ͬ��ģ��OM��Ҫ�ϱ��Ľṹ��,���ļ����ջύ����HiStudioʹ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��12��29��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : �����ļ�

  2.��    ��   : 2011��05��26��
    ��    ��   : tuzhiguo(52067)
    �޸�����   : CQI�������޸ĺ���

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

#ifndef __SYNC_OM_DEF_H__
#define __SYNC_OM_DEF_H__


/* #ifdef __cplusplus */
/* #if __cplusplus */
/* extern "C"{ */
/* #endif */
/* #endif /\* __cplusplus *\/ */

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum __LPHY_REQ_MSGID_SYNC__
{
    LPHY_REQ_SYNC_RESERVED            = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_REQ, 0x0),//0x30600000
    LPHY_REQ_SYNC_ENA,
    LPHY_REQ_SYNC_RBIR_ALPHA,                //RLM����ʱ��RBIR�˲�����
    LPHY_REQ_SYNC_THRESH_INSYNC,             //RLM��ͬ������
    LPHY_REQ_SYNC_THRESH_OUTSYNC,            //RLM��ʧ������
    LPHY_REQ_SYNC_STAT
}LPHY_REQ_MSGID_SYNC_ENUM;

typedef struct
{
	OM_REQ_ENABLE_ENUM_UINT16	enEn;
	UINT8						aucRsv1[2];
}LPHY_REQ_SYNC_EN_STRU;

typedef struct 
{
    LPHY_REQ_SYNC_EN_STRU stInputSw;
    LPHY_REQ_SYNC_EN_STRU stCalSw;

    LPHY_REQ_SYNC_EN_STRU stBbpResultSw;
    LPHY_REQ_SYNC_EN_STRU stPHSw;

    LPHY_REQ_SYNC_EN_STRU stRsv1;
    LPHY_REQ_SYNC_EN_STRU stRsv;
}LPHY_REQ_SYNC_REPORT_SWITCH_STRU;
    
    
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
   UINT16                      usAlpha;
}LPHY_REQ_SYNC_RBIR_ALPHA_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    INT16                      sThresh;
}LPHY_REQ_SYNC_THRESH_STRU;


typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usRuuMode;            /*0, 1, 2*/
}LPHY_REQ_SYNC_RUU_MODE_STRU;


/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_SYNC__
{
    LPHY_CNF_SYNC_RESERVED            = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_SYNC_ENUM;

/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_MSGID_SYNC__
{
    LPHY_IND_SYNC_RESERVED            = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_SYNC_ENUM;


/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_SYNC_
{
    LPHY_TRACE_SYNC_RESERVED         = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_SYNC_TRACE_BINARY,  
    LPHY_TRACE_SYNC_TRACE,  
}LPHY_TRACE_SYNC_ENUM;

typedef enum __LPHY_TRACE_SYNC_STAT__
{
    LPHY_TRACE_SYNC_STAT_NEW_CFG_PARA = 1,   /*�յ�CONFIG��Ϣ*/
    LPHY_TRACE_SYNC_STAT_INVALID_CFG_PARA,   /*�յ�CONFIG��Ϣ���Ϸ�*/
    LPHY_TRACE_SYNC_STAT_GET_CNF_BUF_FAIL,       /*�յ�CONFIG��Ϣ�ظ�ȷ����Ϣ�޻�����*/
}LPHY_TRACE_SYNC_STAT_ENUM;
typedef UINT16 LPHY_TRACE_SYNC_STAT_ENUM_UINT16;

typedef struct __LPHY_TRACE_SYNC_STRU__
{
    LPHY_TRACE_SYNC_STAT_ENUM_UINT16  enTraceStat;    
}LPHY_TRACE_SYNC_STRU;


/************************************************************
                           5. SG���ݽṹ����
************************************************************/
typedef enum __LPHY_SG_SYNC_
{
    LPHY_SG_SYNC_RESERVED         = OM_CMD_ID(LPHY_SYNC_MID, OM_TYPE_SG, 0x0),//0x30630000
    LPHY_SG_PCELL_SYNC_STAT,
    LPHY_PCELL_INPUT_STAT,
    LPHY_PCELL_CAL_STAT,
    LPHY_PCELL_BBP_RESULT_STAT,
    LPHY_TEXT_RESULT_STAT,
}LPHY_SG_SYNC_ENUM;

typedef struct __LPHY_SG_SYNC_SNR_STRU__
{
    INT16       sOSSINR;
    INT16       sISSINR;
}LPHY_SG_SYNC_SNR_STRU;

typedef struct __LPHY_SG_SYNC_RESULT_STRU__
{
	UINT8      ucRsv[2];
    UINT8      ucOSFlag;   
    UINT8      ucISFlag;   
}LPHY_SG_SYNC_RESULT_STRU;

typedef struct __LPHY_SG_SYNC_OM_STAT_STRU__
{
    UINT8       ucOSFlag;
    UINT8       ucISFlag;
    UINT8       ucTrmsInd;
    UINT8       ucUnevenFlagFinal;
    
    INT16       sISSINR;
    INT16       sOSSINR;

    INT16       sIThrd;  
    INT16       sOThrd;  

    UINT16      usAlphaRlm;  
    UINT8       ucCdrx;  
    UINT8       ucRsv;
    
    INT16       sAvSinDb;  
    INT16       sISMinSINR;  

	INT32       sOSSINRSum;
	INT32       sISSINRSum;

	INT32       sCnt;
}LPHY_SG_SYNC_OM_STAT_STRU;
    

typedef struct
{
    UINT16 usSysFrmNum;
    UINT16 usSubFrmNum;
    
    UINT16 usNoiseMulFactor;
    UINT8  ucTrmsInd;
    UINT8  ucDftCheFlag;
    
    UINT16 usFrameType;
    UINT8  ucHetnet;
    UINT8  ucRsv;
    
    INT16 asSinrDB[4];

    UINT32 aulNoiseCmu[4];
    
    UINT32 ulRsv[4];
    
}LPHY_SYNC_INPUT_REPORT_STRU;
    
typedef struct 
{
    UINT32 ulWhiteSel;
    
    UINT16 usBeta;
    UINT16 usGamma;
    
    UINT32 ulRsv;
    UINT32 ulRsv1;
    UINT32 ulRsv2;
    UINT32 ulRsv3;
}LPHY_SYNC_CAL_REPORT_STRU;
typedef struct 
{

    UINT32 ulBaseRbir;
    UINT32 ulDrxRbir;
    UINT32 ulAccRbir;
    UINT32 ulAccCnt;
    

    UINT8 ucCdrx;
    UINT8 ucRsv;
    UINT8 ucRsv1;
    UINT8 ucRsv2;
    
    INT16 sRsv;
    UINT16 usAlpha;
    

    UINT32 ulRsv;
}LPHY_SYNC_BBPRESULT_REPORT_STRU;

typedef struct 
{
    UINT32 ulSysNum;
    UINT32 ulSubNum;
    UINT32 aulContent[128];

}LPHY_SYNC_TEXT_REPORT_STRU;

    

/*
    ͬʧ���ṹ�嶨�壬������Ը��ݿ���ȫ���ϱ�
*/
typedef enum __SYNC_TYPE_E__
{
    SYNC_TYPE_NONE,
    SYNC_TYPE_FILTER,
    SYNC_TYPE_REPORT    
}SYNC_TYPE_E;
typedef UINT16 SYNC_TYPE_ENUM_UINT16;

typedef struct __SYNC_MODULE_STRU__
{
    /*ԭ���·�ͬʧ��ʹ��*/
    UINT8           ucInSyncReportEn;       /*ͬ���ϱ�ʹ��*/
    UINT8           ucOutofSyncReportEn;    /*ʧ���ϱ�ʹ��*/

    /*ͬʧ������*/
    UINT8           ucInitFliterAlhpaFlag;  /*��ʼ���˲���alphaϵ�����*/
    UINT8           ucJudge2InitAlphaFlag;  /*�о���ʽalpha��ʼ�����*/
    UINT16          usCounter;              /*������ʱ���������λ����*/
    SYNC_TYPE_ENUM_UINT16     enType;       /*����ͬʧ����������øñ�ǣ�ͬʧ���о�������ñ��*/
    UINT16          usInSyncAlpha;
    UINT16          usOutSyncAlpha;
    
    /*ͬʧ���о�*/
    UINT16          usOSRptFlag;            /*ʧ������ϱ���� 1����ʾʧ��; 0, ��ʾδʧ��*/
    UINT16          usISRptFlag;            /*ͬ������ϱ���� 1����ʾͬ��; 0, ��ʾδͬ��*/
    INT32           lSINR;                  /*�о���ʽ2�˲�ֵ*/
    UINT16          usJudge2OSFlag;         /*�о���ʽ2ʧ�����*/

    /*��¼ͬʧ�����쳣��֧*/
    UINT8           ucStartDgbBranch1;      /*��¼��ǰ��֡���쳣��֧���������*/
    UINT8           ucCompleteDbgBranch2;   /*��¼��ǰ��֡�Ľ�����֧, �������*/  

    /*��¼OM�ϱ�ÿ����֡�������*/
    LPHY_SG_SYNC_SNR_STRU   stSNR;          /*����ȣ�ÿ��������һ�ζ�һ��*/
    
    /*OM�ϱ�����*/
    UINT32          ulAccTimeCounter;       /*�ۼӾ�����ʱ���������λ����*/
    INT32           lAccNum;                /*�ۼӴ���*/
    INT32           lOSSNRSum;              /*ʧ��������ۼ�ֵ*/
    INT16           sMaxOSSINR;             /*���ʧ��ֵ*/
    INT16           sMinOSSINR;             /*��Сʧ��ֵ*/
    INT32           lISSNRSum;              /*ͬ��������ۼ�ֵ*/
    INT16           sMaxISSINR;             /*���ͬ��ֵ*/
    INT16           sMinISSINR;             /*��Сͬ��ֵ*/

    /*����OM*/
    INT16           sOrgCmuSINR;            /*��CMU��ȡ��SINR*/
    INT16           sOrgCqiSINR;            /*CMU��CQI��CQI�ٸ�RLM��SINR, RLM�ø�ֵ���˲�*/
    INT16           usValidSINR;            /*���Ƿ���Ч�ı�ʾSINR*/
    INT16           usRsv;
    
}SYNC_MODULE_STRU;


/* #ifdef __cplusplus */
/* #if __cplusplus */
/* } */
/* #endif */
/* #endif /\* __cplusplus *\/ */


#endif /* __SYNC_OM_DEF_H__ */
