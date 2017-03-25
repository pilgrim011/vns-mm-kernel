/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCbaCtx.c
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��3��19��
  ����޸�   :
  ��������   : CBAģ�����������صĴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "TafCbaProcNvim.h"
#include  "MnMsgTimerProc.h"
#include  "MnErrorCode.h"
#include  "MnComm.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_CTX_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

TAF_CBA_CTX_STRU                        g_stCbaCtx;                             /* CBA����������Ϣ */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitSimInfo
 ��������  : ��ʼ��CBAģ���SIM��״̬��ȫ�ֱ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��29��
    ��    ��   : w00176964
    �޸�����   : USIM�ļ���ȡ������ӳ�ʼ��
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID TAF_CBA_InitSimInfo(VOS_VOID)
{
    TAF_CBA_SIM_INFO_STRU               *pstSimInfo;

    pstSimInfo = TAF_CBA_GetSimInfo();

    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* TAF_CBA_ClearAllReadUsimFilesFlg */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ��ʼ�� EFCBMI �ļ�״̬��Ϣ */
    pstSimInfo->stEfCbmiFileInfo.ucEfCbmiExistFlg = VOS_FALSE;                  /* Efcbmi �ļ������� */
    pstSimInfo->stEfCbmiFileInfo.ucRsv            = 0;
    pstSimInfo->stEfCbmiFileInfo.usEfCbmiFileLen  = 0;

    /* ��ʼ�� EFCBMIR �ļ�״̬��Ϣ */
    pstSimInfo->stEfCbmirFileInfo.ucEfCbmirExistFlg = VOS_FALSE;                /* Efcbmir �ļ������� */
    pstSimInfo->stEfCbmirFileInfo.ucRsv             = 0;
    pstSimInfo->stEfCbmirFileInfo.usEfCbmirFileLen  = 0;

    /* ��ʼ�� EFCBMID �ļ�״̬��Ϣ */
    pstSimInfo->stEfCbmidFileInfo.ucEfCbmidExistFlg = VOS_FALSE;                /* Efcbmid �ļ������� */
    pstSimInfo->stEfCbmidFileInfo.ucRsv             = 0;
    pstSimInfo->stEfCbmidFileInfo.usEfCbmidFileLen  = 0;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitCbmiRangeList
 ��������  : ��ʼ��CBMI RANGE List ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitCbmiRangeList(VOS_VOID)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiRangInfo;
    VOS_UINT32                          ulInx;

    pstCbmiRangInfo = TAF_CBA_GetCbMiRangeList();

    pstCbmiRangInfo->usCbmirNum    = 0;                                         /* �趨��CBS ID����Ϊ0 */

    pstCbmiRangInfo->aucReserve[0] = 0;
    pstCbmiRangInfo->aucReserve[1] = 0;

    for (ulInx = 0; ulInx < TAF_CBA_MAX_CBMID_RANGE_NUM; ulInx++)
    {
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].ucLabel[0]  = '\0';            /* ���ַ���*/
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].usMsgIdFrom = 0;
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].usMsgIdTo   = 0;               /* ��ʼ��Ϊ0 */
        pstCbmiRangInfo->astCbmiRangeInfo[ulInx].enRcvMode   =
                                       TAF_CBA_CBMI_RANGE_RCV_MODE_BUTT;        /* Ĭ��ΪBUTT���� */
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitCbsMsCfgInfo
 ��������  : ��ʼ���û�����CBS��Ϣ��ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��04��
    ��    ��   : l00171473
    �޸�����   : for DTS2012120600056,����ȫ�ֱ�����ʼ��
*****************************************************************************/
VOS_VOID  TAF_CBA_InitCbsMsCfgInfo(VOS_VOID)
{
    TAF_CBA_MS_CFG_CBS_INFO_STRU       *pstCfgCbsInfo;
    VOS_UINT32                          ulCbmidNumCount;


    pstCfgCbsInfo = TAF_CBA_GetMsCfgCbsInfo();

    /* ��ʼ��CBS config״̬ */
    pstCfgCbsInfo->enCbStatus             = TAF_CBA_CBSTATUS_BUTT;              /* Ĭ��Ϊ��Ч״̬ */

    pstCfgCbsInfo->enDupDetectCfg         = TAF_CBA_DUP_DETECT_CFG_BUTT;

    pstCfgCbsInfo->ucRptAppFullPageFlg    = VOS_FALSE;
    pstCfgCbsInfo->ucRsv                  = 0;

    /* ��ʼ��CBS config--stCbMirList״̬ */
    TAF_CBA_InitCbmiRangeList();

    /* ��ʼ��CBS config--stCbMidList״̬ */
    pstCfgCbsInfo->stCbMiDownloadList.usCbmidNum = 0;                                /* �ܵ�CBS ID����Ϊ0 */

    pstCfgCbsInfo->stCbMiDownloadList.aucRsv[0]  = 0;
    pstCfgCbsInfo->stCbMiDownloadList.aucRsv[1]  = 0;

    for (ulCbmidNumCount = 0; ulCbmidNumCount < TAF_CBA_MAX_CBMID_NUM; ulCbmidNumCount++)
    {
        pstCfgCbsInfo->stCbMiDownloadList.ausMsgId[ulCbmidNumCount] = 0;             /* �б����е� CBS IDֵΪ0 */
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitNetworkInfo
 ��������  : ��ʼ��CBAģ����ص�������Ϣȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitNetworkInfo(VOS_VOID)
{
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = TAF_CBA_GetNetworkInfo();

    pstNetworkInfo->enCurrNetRatType = TAF_CBA_NET_RAT_TYPE_BUTT;               /* Ĭ��Ϊ��Ч */

    pstNetworkInfo->aucRsv3[0]       = 0;                                       /* ����ַ��� */
    pstNetworkInfo->aucRsv3[1]       = 0;                                       /* ����ַ��� */
    pstNetworkInfo->aucRsv3[2]       = 0;                                       /* ����ַ��� */

    pstNetworkInfo->stCurPlmn.ulMcc  = TAF_CBA_INVALID_MCC;                     /* Ĭ��Ϊ��Ч */
    pstNetworkInfo->stCurPlmn.ulMnc  = TAF_CBA_INVALID_MNC;                     /* Ĭ��Ϊ��Ч */

    pstNetworkInfo->usSa             = 0;                                       /* Ĭ��Ϊ0 */

    pstNetworkInfo->aucRsv2[0]       = 0;                                       /* ����ַ��� */
    pstNetworkInfo->aucRsv2[1]       = 0;                                       /* ����ַ��� */

    pstNetworkInfo->ulCellId         = 0;                                       /* Ĭ��Ϊ0 */
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitOldNetworkInfo
 ��������  : ��ʼ���ϴε�������Ϣȫ�ֱ���(�ϴ� GS_STATUS_CHANGE_IND ��������Ϣ)
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitOldNetworkInfo(VOS_VOID)
{
    TAF_CBA_NETWORK_INFO_STRU          *pstOldNetworkInfo;

    pstOldNetworkInfo = TAF_CBA_GetOldNetworkInfo();

    pstOldNetworkInfo->enCurrNetRatType = TAF_CBA_NET_RAT_TYPE_BUTT;            /* Ĭ��Ϊ��Ч */

    pstOldNetworkInfo->aucRsv3[0]       = 0;                                    /* ����ַ��� */
    pstOldNetworkInfo->aucRsv3[1]       = 0;                                    /* ����ַ��� */
    pstOldNetworkInfo->aucRsv3[2]       = 0;                                    /* ����ַ��� */

    pstOldNetworkInfo->stCurPlmn.ulMcc  = TAF_CBA_INVALID_MCC;                  /* Ĭ��Ϊ��Ч */
    pstOldNetworkInfo->stCurPlmn.ulMnc  = TAF_CBA_INVALID_MNC;                  /* Ĭ��Ϊ��Ч */

    pstOldNetworkInfo->usSa             = 0;                                    /* Ĭ��Ϊ0 */

    pstOldNetworkInfo->aucRsv2[0]       = 0;                                    /* ����ַ��� */
    pstOldNetworkInfo->aucRsv2[1]       = 0;                                    /* ����ַ��� */

    pstOldNetworkInfo->ulCellId         = 0;                                    /* Ĭ��Ϊ0 */
}

#if (FEATURE_ETWS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : TAF_CBA_InitEtwsRecordList
 ��������  : ��ʼ��ETWS��ʷ��¼��ȫ�ֱ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitEtwsRecordList(VOS_VOID)
{
    TAF_CBA_RECORD_LIST_STRU           *pstRcvRecList;
    VOS_UINT32                          ulRecInx;

    pstRcvRecList = TAF_CBA_GetRcvRecordListInfo();

    /* ��ʼ����֪ͨ��ʷ��¼����Ϣ */
    pstRcvRecList->usRcvEtwsPrimNtfNum = 0;                                     /* ETWS��֪ͨ��ʷ��¼���� */
    pstRcvRecList->aucRsv[0]           = 0;                                     /* ���λ����*/
    pstRcvRecList->aucRsv[1]           = 0;                                     /* ���λ����*/

    for (ulRecInx = 0; ulRecInx < TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM; ulRecInx++)
    {
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].enNetMode        = TAF_CBA_NET_RAT_TYPE_BUTT;      /* ��Ч�Ľ��뼼��*/
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].ucTotalPage      = 0;                              /* ��ҳ����G��CBS��Ϣ��������Ϣ�� */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].usPageBitmap     = 0;                              /* �ѽ���ҳ��BitMap(G��CBS��Ϣ��������Ϣ) */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].usMsgID          = 0;                              /* ����֪ͨ/CBS��ϢID */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].usSN             = 0;                              /* ����֪ͨ/CBS���к� */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].stPlmn.ulMcc     = TAF_CBA_INVALID_MCC;            /* Ĭ��Ϊ��Ч */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].stPlmn.ulMnc     = TAF_CBA_INVALID_MNC;            /* Ĭ��Ϊ��Ч */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].ulDupDetcTimeLen = 0;                              /* ��Чʱ��N,��λ: ��, Ϊ0��ʾһֱ��Ч */
        pstRcvRecList->astRcvEtwsPrimNtfList[ulRecInx].ulRcvTimeTick    = 0;                              /* �յ���Ϣʱ��ʱ���, ȡ�� VOS_GetTick, ��λ: 10 ms */
    }
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitCbsRecordList
 ��������  : ��ʼ��CBS��ʷ��¼��ȫ�ֱ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitCbsRecordList(VOS_VOID)
{
    TAF_CBA_RECORD_LIST_STRU           *pstRcvRecList;
    VOS_UINT32                          ulRecInx;

    pstRcvRecList = TAF_CBA_GetRcvRecordListInfo();

    /* ��ʼ��CBS��ʷ��¼����Ϣ */
    pstRcvRecList->usRcvCbsNum = 0;                                             /* CBS(����ETWS��֪ͨ)��ʷ��¼���� */
    pstRcvRecList->aucRsv1[0]  = 0;                                             /* ���λ����*/
    pstRcvRecList->aucRsv1[1]  = 0;                                             /* ���λ����*/

    for (ulRecInx = 0; ulRecInx < TAF_CBA_MAX_CBS_RECORD_NUM; ulRecInx++)
    {
        /* ETWS��֪ͨ/CBS��ʷ��¼�� */
        pstRcvRecList->astRcvCbsList[ulRecInx].enNetMode        = TAF_CBA_NET_RAT_TYPE_BUTT;    /* ��Ч�Ľ��뼼�� */
        pstRcvRecList->astRcvCbsList[ulRecInx].ucTotalPage      = 0;                            /* ��ҳ����G��CBS��Ϣ��������Ϣ�� */
        pstRcvRecList->astRcvCbsList[ulRecInx].usPageBitmap     = 0;                            /* �ѽ���ҳ��BitMap(G��CBS��Ϣ��������Ϣ) */
        pstRcvRecList->astRcvCbsList[ulRecInx].usMsgID          = 0;                            /* ����֪ͨ/CBS��ϢID */
        pstRcvRecList->astRcvCbsList[ulRecInx].usSN             = 0;                            /* ����֪ͨ/CBS���к� */
        pstRcvRecList->astRcvCbsList[ulRecInx].stPlmn.ulMcc     = TAF_CBA_INVALID_MCC;          /* Ĭ��Ϊ��Ч */
        pstRcvRecList->astRcvCbsList[ulRecInx].stPlmn.ulMnc     = TAF_CBA_INVALID_MNC;          /* Ĭ��Ϊ��Ч */
        pstRcvRecList->astRcvCbsList[ulRecInx].ulDupDetcTimeLen = 0;                            /* ��Чʱ��Ϊ0��ʾһֱ��Ч */
        pstRcvRecList->astRcvCbsList[ulRecInx].ulRcvTimeTick    = 0;                            /* ʱ���,*/
    }
}


/*****************************************************************************
 �� �� ��  : TAF_CBA_InitRecordList
 ��������  : ��ʼ����ʷ��¼��ȫ�ֱ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitRecordList(VOS_VOID)
{
#if (FEATURE_ETWS == FEATURE_ON)
    /* ETWS��ʷ��¼��ʼ�� */
    TAF_CBA_InitEtwsRecordList();
#endif

    /* CBS��ʷ��¼��ʼ�� */
    TAF_CBA_InitCbsRecordList();
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitCtx
 ��������  : ��ʼ��CBAģ���CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBA CTX��ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��24��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID  TAF_CBA_InitCtx(VOS_VOID)
{
    /* ��ʼ��SIM��״̬��ȫ�ֱ�����Ϣ */
    TAF_CBA_InitSimInfo();

    /* ��ʼ��CBS config״̬ */
    TAF_CBA_InitCbsMsCfgInfo();

#if (FEATURE_ETWS == FEATURE_ON)
    /* ��ʼ��ETWS ������Ϣ */
    TAF_CBA_InitEtwsMsCfgInfo();
#endif

    /* ��ʼ��������Ϣ */
    TAF_CBA_InitNetworkInfo();

    /* ��ʼ���ϴε�������Ϣȫ�ֱ���(�ϴ� GS_STATUS_CHANGE_IND ��������Ϣ) */
    TAF_CBA_InitOldNetworkInfo();

    /* ��ʼ����ʷ��¼����Ϣ */
    TAF_CBA_InitRecordList();
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbsCtx
 ��������  : ��ȡCBS��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBS CTX��ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CTX_STRU* TAF_CBA_GetCbaCtx(VOS_VOID)
{
    return (&g_stCbaCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetSimInfo
 ��������  : ��ȡCBAģ����SIM�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBS CTX��ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_SIM_INFO_STRU* TAF_CBA_GetSimInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsSimInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetEfCbmiInfo
 ��������  : ��ȡCBAģ����EFCBMI����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBAģ����EFCBMI����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU* TAF_CBA_GetEfCbmiInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmiFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetEfCbmiRangeInfo
 ��������  : ��ȡCBAģ����EFCBMIR ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBAģ����EFCBMIR����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU* TAF_CBA_GetEfCbmiRangeInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmirFileInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetEfCbmidInfo
 ��������  : ��ȡCBAģ����EFCBMID����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBAģ����EFCBMID����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU* TAF_CBA_GetEfCbmidInfo(VOS_VOID)
{
    return &(TAF_CBA_GetSimInfo()->stEfCbmidFileInfo);
}

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted TAF_CBA_SetReadUsimFileFlg TAF_CBA_GetReadUsimFileFlg TAF_CBA_ClearReadUsimFileFlg TAF_CBA_ClearAllReadUsimFilesFlg */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbsMsCfgInfo
 ��������  : ��ȡ�û����õ�CBS��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����û����õ�CBS��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_MS_CFG_CBS_INFO_STRU* TAF_CBA_GetMsCfgCbsInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsMsCfg);
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetCbsStatus
 ��������  : ��ȡ��ǰCBS���ܼ����־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS���ܼ����־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBSTATUS_ENUM_UINT8 TAF_CBA_GetCbsStatus(VOS_VOID)
{
    return TAF_CBA_GetMsCfgCbsInfo()->enCbStatus;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SetCbsStatus
 ��������  : ���µ�ǰCBS���ܼ����־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS���ܼ����־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetCbsStatus(
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->enCbStatus) = enCbsStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetDupDetectCfg
 ��������  : ����CBS�ظ��������ÿ���
 �������  : CBS�ظ����˵����ÿ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��04��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for DTS2012120600056

*****************************************************************************/
VOS_VOID TAF_CBA_SetDupDetectCfg(
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enTmpDupDetectCfg
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->enDupDetectCfg) = enTmpDupDetectCfg;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetDupDetectCfg
 ��������  : ��ȡCBS�ظ��������ÿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBS�ظ����˵����ÿ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��04��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for DTS2012120600056

*****************************************************************************/
TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8 TAF_CBA_GetDupDetectCfg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgCbsInfo()->enDupDetectCfg);
}


/*****************************************************************************
 �� �� ��  : TAF_CBA_SetRptAppFullPageFlg
 ��������  : ������APP�ϱ���ҳ�����ÿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��APP�ϱ���ҳ�����ÿ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��04��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for DTS2012120609682,�ն�Ҫ��CBSͳһ�ϱ�88���ֽ�

*****************************************************************************/
VOS_VOID TAF_CBA_SetRptAppFullPageFlg(
    VOS_UINT8                           ucTmpRptAppFullPageFlg
)
{
    (TAF_CBA_GetMsCfgCbsInfo()->ucRptAppFullPageFlg) = ucTmpRptAppFullPageFlg;
}
/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRptAppFullPageFlg
 ��������  : ��ȡ�Ƿ���APP�ϱ���ҳ�����ÿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���APP�ϱ���ҳ�����ÿ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��04��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for DTS2012120609682,�ն�Ҫ��CBSͳһ�ϱ�88���ֽ�

*****************************************************************************/
VOS_UINT8 TAF_CBA_GetRptAppFullPageFlg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgCbsInfo()->ucRptAppFullPageFlg);
}


/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbmiDownloadList
 ��������  : ��ȡ��ǰCBS CBMID List����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS CBMID List����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBMI_DOWNLOAD_LIST_STRU* TAF_CBA_GetCbmiDownloadList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiDownloadList);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbmiDownloadNum
 ��������  : ��ȡ��ǰCBS CBMID List��CBMID �ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS CBMID List��CBMID �ĸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetCbmiDownloadNum(VOS_VOID)
{
    return (TAF_CBA_GetCbmiDownloadList()->usCbmidNum);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbMiRangeList
 ��������  : ��ȡ��ǰCBS CBMIR List����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS CBMIR List����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBMI_RANGE_LIST_STRU* TAF_CBA_GetCbMiRangeList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiRangeList);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbmiRangeListHead
 ��������  : ��ȡ��ǰCBS CBMIR List��ͷָ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰCBS CBMIR List��ͷָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_CBMI_RANGE_STRU* TAF_CBA_GetCbmiRangeListHead(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgCbsInfo()->stCbMiRangeList.astCbmiRangeInfo[0]);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCbmiRangNum
 ��������  : ��ȡ��ǰCBS CBMIR List�е�CBMIR�ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS CBMIR List�е�CBMIR�ĸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetCbmiRangNum(VOS_VOID)
{
    return (TAF_CBA_GetCbMiRangeList()->usCbmirNum);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetCbmiRangeNum
 ��������  : ���õ�ǰ CBMIR List�е�CBMIR�ĸ���
 �������  : CBMIR�ĸ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetCbmiRangeNum(
    VOS_UINT16                          usCbmiRangNum
)
{
    if (usCbmiRangNum >= TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiRangNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    (TAF_CBA_GetCbMiRangeList()->usCbmirNum) = usCbmiRangNum;
}

#if (FEATURE_ETWS == FEATURE_ON)

/*****************************************************************************
 �� �� ��  : TAF_CBA_InitEtwsMsCfgInfo
 ��������  : ��ʼ��ETWS���û�����ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitEtwsMsCfgInfo(VOS_VOID)
{
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstEtwsCfg;
    VOS_UINT32                          ulInx;

    pstEtwsCfg = TAF_CBA_GetMsCfgEtwsInfo();

    /* ��ʼ��ETWS״̬ */
    TAF_CBA_SetEtwsEnableFlg(VOS_FALSE);

    pstEtwsCfg->aucRsv[0]       = 0;                                            /* ����ַ���*/
    pstEtwsCfg->aucRsv[1]       = 0;                                            /* ����ַ���*/
    pstEtwsCfg->aucRsv[2]       = 0;                                            /* ����ַ���*/

    /* ��ʼ���ظ����������Ϣ */
    pstEtwsCfg->stDupDetectCfg.ucEnhDupDetectFlg = 0;                           /* ����Ϊ0*/

    pstEtwsCfg->stDupDetectCfg.aucRsv[0]         = 0;
    pstEtwsCfg->stDupDetectCfg.aucRsv[1]         = 0;
    pstEtwsCfg->stDupDetectCfg.aucRsv[2]         = 0;

    pstEtwsCfg->stDupDetectCfg.ulNormalTimeLen                          = 0;    /* ����Ϊ0*/
    pstEtwsCfg->stDupDetectCfg.stDupDetectTimeLen.ulSpecMccTimeLen      = 0;    /* ʱ��Ϊ0*/
    pstEtwsCfg->stDupDetectCfg.stDupDetectTimeLen.ulOtherMccTimeLen     = 0;    /* ʱ��Ϊ0*/

    for ( ulInx = 0; ulInx < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; ulInx++ )
    {
        pstEtwsCfg->stDupDetectCfg.stDupDetectTimeLen.aulSpecMcc[ulInx] = 0;    /* ʱ��Ϊ0*/
    }

    /* ��ʼ����ʱʹ��CBSʱ�� */
    pstEtwsCfg->ulTempEnableCbsTimeLen = 0;                                     /* ʱ��Ϊ0*/

    /* ��ʼ���û����Ƶ�ETWS��Ϣ�� MSG ID��Χ */
    for ( ulInx = 0; ulInx < TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM; ulInx++ )
    {
        pstEtwsCfg->astSpecEtwsMsgIdList[ulInx].usMsgIdFrom = 0;
        pstEtwsCfg->astSpecEtwsMsgIdList[ulInx].usMsgIdTo   = 0;                /* ��ʼ��Ϊ0*/
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetMsCfgEtwsInfo
 ��������  : ��ȡ�û����õ�ETWS��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����û����õ�ETWS��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_MS_CFG_ETWS_INFO_STRU* TAF_CBA_GetMsCfgEtwsInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stEtwsMsCfg);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetEtwsEnableFlg
 ��������  : �����û����õ�ETWS��Ϣ
 �������  : ucEtwsEnableFlg - ��NV������ETWS�Ƿ���Ч
 �������  : ��
 �� �� ֵ  : �����û����õ�ETWS��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��23��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetMsCfgEtwsInfo(
    TAF_CBA_MS_CFG_ETWS_INFO_STRU      *pstMsCfgEtwsInfo
)
{
    (TAF_CBA_GetCbaCtx()->stEtwsMsCfg) = (*pstMsCfgEtwsInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetEtwsEnableFlg
 ��������  : ���õ�ǰETWS�Ƿ񼤻���
 �������  : ETWS�Ƿ񼤻�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��31��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetEtwsEnableFlg(
    VOS_UINT8                           ucEtwsEnableFlg
)
{
    g_stCbaCtx.stEtwsMsCfg.ucEtwsEnableFlg = ucEtwsEnableFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetEtwsEnableFlg
 ��������  : ��ȡ��ǰETWS�Ƿ񼤻��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰETWS�Ƿ񼤻���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32 TAF_CBA_GetEtwsEnableFlg(VOS_VOID)
{
    return (VOS_UINT32)(TAF_CBA_GetMsCfgEtwsInfo()->ucEtwsEnableFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetEnhDupDetcFlg
 ��������  : ����DOCOMO��ǿ���ظ���ⶨ�����Կ���
 �������  : ��ǿ���ظ�������Կ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID  TAF_CBA_SetEnhDupDetcFlg(
    VOS_UINT8       ucDetcFlg
)
{
    g_stCbaCtx.stEtwsMsCfg.stDupDetectCfg.ucEnhDupDetectFlg = ucDetcFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetEnhDupDetcFlg
 ��������  : ��ȡDOCOMO��ǿ���ظ���ⶨ�����Կ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǿ���ظ�������Կ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT8  TAF_CBA_GetEnhDupDetcFlg(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.ucEnhDupDetectFlg);
}


/*****************************************************************************
 �� �� ��  : TAF_CBA_GetNormalDupDetcTimeLen
 ��������  : ��ȡ��ͨ���ظ����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ͨ���ظ����ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_UINT32  TAF_CBA_GetNormalDupDetcTimeLen(VOS_VOID)
{
    return (TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.ulNormalTimeLen);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetEnhDupDetcTimeLenCfg
 ��������  : ��ȡ��ǿ�ظ����ʱ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǿ�ظ����ʱ��������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU* TAF_CBA_GetEnhDupDetcTimeLenCfg(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgEtwsInfo()->stDupDetectCfg.stDupDetectTimeLen);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetUserSpecEtwsMsgIdList
 ��������  : ��ȡ�û����Ƶ�ETWS��ϢID��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û����Ƶ�ETWS��ϢID��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_ETWS_MSGID_RANGE_STRU* TAF_CBA_GetUserSpecEtwsMsgIdList(VOS_VOID)
{
    return &(TAF_CBA_GetMsCfgEtwsInfo()->astSpecEtwsMsgIdList[0]);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRcvEtwsPrimNtfNum
 ��������  : ��ȡETWS��֪ͨ��ʷ��¼����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ETWS��֪ͨ��ʷ��¼����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetRcvEtwsPrimNtfNum(VOS_VOID)
{
    return (TAF_CBA_GetRcvRecordListInfo()->usRcvEtwsPrimNtfNum);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetRcvEtwsPrimNtfNum
 ��������  : ����ETWS��֪ͨ��ʷ��¼����
 �������  : usEtwsPrimNtfNum: ETWS��֪ͨ��ʷ��¼����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_SetRcvEtwsPrimNtfNum(
    VOS_UINT16                          usEtwsPrimNtfNum
)
{
    (TAF_CBA_GetRcvRecordListInfo()->usRcvEtwsPrimNtfNum) = usEtwsPrimNtfNum;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRcvEtwsPrimNtfList
 ��������  : ��ȡETWS��֪ͨ��ʷ��¼��ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ETWS��֪ͨ��ʷ��¼��ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvEtwsPrimNtfList(VOS_VOID)
{
    return &(TAF_CBA_GetRcvRecordListInfo()->astRcvEtwsPrimNtfList[0]);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_UpdateTempEnableCbsTimerLen
 ��������  : ����NV�е���ʱʹ��CBS��ʱ����ʼ����ʱ����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_UpdateTempEnableCbsTimerLen(VOS_VOID)
{
    /* ����NV�е���ʱʹ��CBS��ʱ�����¶�ʱ����Ϣ */

    MN_MSG_UpdateRetryPeriod( TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS,
                              ((TAF_CBA_GetMsCfgEtwsInfo()->ulTempEnableCbsTimeLen) * TAF_CBA_SECOND_TO_MILLISECOND) );
}

#endif

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetNetworkInfo
 ��������  : ��ȡ��ǰCBS����ģ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS����ģ���������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��120��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetNetworkInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stCbsNetworkInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetOldNetworkInfo
 ��������  : ��ȡ�ϴε�������Ϣ(�ϴ� GS_STATUS_CHANGE_IND ��������Ϣ)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS����ģ���������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��120��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NETWORK_INFO_STRU* TAF_CBA_GetOldNetworkInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stOldNetworkInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetOldNetworkInfo
 ��������  : �����ϴε�������Ϣ(�ϴ� GS_STATUS_CHANGE_IND ��������Ϣ)
 �������  : pstNetworkinfo: ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��120��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetOldNetworkInfo(
    TAF_CBA_NETWORK_INFO_STRU          *pstNetworkinfo
)
{
    (TAF_CBA_GetCbaCtx()->stOldNetworkInfo) = (*pstNetworkinfo);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetNetRatType
 ��������  : ��ȡ��ǰCBS����ģ�������ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS����ģ�������ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetNetRatType(VOS_VOID)
{
    return TAF_CBA_GetNetworkInfo()->enCurrNetRatType;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SetNetRatType
 ��������  : ���õ�ǰCBS����ģ�������ģʽ
 �������  : enCurrNetMode - ����ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��24��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
VOS_VOID TAF_CBA_SetNetRatType(
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enCurrNetMode
)
{
    (TAF_CBA_GetNetworkInfo()->enCurrNetRatType) = enCurrNetMode;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetCurrPlmn
 ��������  : ��ȡ��ǰCBS����ģ���Plmn
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰCBS����ģ���Plmn
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_PLMN_ID_STRU* TAF_CBA_GetCurrPlmn(VOS_VOID)
{
    return &(TAF_CBA_GetNetworkInfo()->stCurPlmn);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRcvRecordListInfo
 ��������  : CBS��ETWS��¼��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����CBS��ETWS��¼��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��120��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR

*****************************************************************************/
TAF_CBA_RECORD_LIST_STRU* TAF_CBA_GetRcvRecordListInfo(VOS_VOID)
{
    return &(TAF_CBA_GetCbaCtx()->stRcvRecordList);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRcvCbsNum
 ��������  : ��ȡ��ͨCBS��ETWS��֪ͨ��¼����
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBS��¼����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_CBA_GetRcvCbsNum(VOS_VOID)
{
    return (TAF_CBA_GetRcvRecordListInfo()->usRcvCbsNum);
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRcvCbsNum
 ��������  : ������ͨCBS��ETWS��֪ͨ��¼����
 �������  : usNewRcvCbsNum: �µ�CBS��¼����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_SetRcvCbsNum(
    VOS_UINT16                          usNewRcvCbsNum
)
{
    (TAF_CBA_GetRcvRecordListInfo()->usRcvCbsNum) = usNewRcvCbsNum;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetRcvCbsList
 ��������  : ��ȡ��ͨCBS��ETWS��֪ͨ��ʷ��¼��ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CBS��ʷ��¼��ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CBA_RECORD_STRU* TAF_CBA_GetRcvCbsList(VOS_VOID)
{
    return &(TAF_CBA_GetRcvRecordListInfo()->astRcvCbsList[0]);
}


/*****************************************************************************
 �� �� ��  : TAF_CBA_Init
 ��������  : CBAģ��ĳ�ʼ������, �ýӿ�Ŀǰ����PID�ĳ�ʼ��ʱ����(�ϵ翪��ʱ).
             ����˵: ĿǰCBS��ص�NV�����ϵ��ʱ��Ż��ȡ, �޸�����ص�NV�����Ҫ
             �����ϵ翪��������Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2013��8��12��
    ��    ��   : f62575
    �޸�����   : DTS2013081900835��֧���ȸ���USIM���ã������NV����

*****************************************************************************/
VOS_VOID TAF_CBA_Init(VOS_VOID)
{
    /* ��ʼ��CBA��CTX */
    TAF_CBA_InitCtx();

    /* ��ȡCBS����ʹ��NV�� */
    TAF_CBA_ReadCbsServiceParamNvim();

    /* TAF_CBA_ReadCbmiRangeListNvim */    

#if (FEATURE_ETWS == FEATURE_ON)
    /* ��ȡETWS������NV�� */
    TAF_CBA_ReadEtwsServieCfgNvim();

    /* ����ȫ�ֱ����е���ʱʹ��CBS��ʱ�����¶�ʱ����Ϣ */
    TAF_CBA_UpdateTempEnableCbsTimerLen();
#endif
}


#endif  /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
