/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCbaProcUsim.c
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��3��19��
  ����޸�   :
  ��������   : CBAģ���USIM��صĴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcUsim.h"
#include  "TafCbaMntn.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcNvim.h"

#include  "UsimPsInterface.h"
#include  "MnMsgSmCommProc.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "TafCbsInterface.h"
#include  "TafLog.h"

#include "NasUsimmApi.h"

#include "TafSdcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_USIM_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted TAF_CBA_ProcUsimGetFileRsp */
/* Deleted TAF_CBA_SndUsimGetFileReq */
/* Deleted TAF_CBA_RcvUsimGetEfCbmiRsp TAF_CBA_RcvUsimGetEfCbmirRsp TAF_CBA_RcvUsimGetEfCbmidRsp */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : TAF_CBA_ParseUsimFileEfCbmiData
 ��������  : ����USIM�е�EFCBMI �ļ�����, ���µ��ڴ���
 �������  : pstUsimGetFileRsp: USIM��EFCBMI�ļ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��3��30��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.��    ��   : 2012��12��26��
    ��    ��   : ���� /z00214637
    �޸�����   : PS_USIM_GET_FILE_RLT_SUCCESS�滻ΪVOS_OK
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID TAF_CBA_ParseUsimFileEfCbmiData(
    VOS_UINT8                           ucEfCbmiExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
)
{
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU *pstEfCbmiFileInfo;
    VOS_UINT32                          ulLoop;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmRangeids;
    VOS_UINT8                           ucMsgIdHigh;
    VOS_UINT8                           ucMsgIdLow;
    VOS_UINT16                          usMsgId;
    VOS_UINT8                          *pucCbmiOct;

    pstEfCbmiFileInfo = TAF_CBA_GetEfCbmiInfo();

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pstEfCbmiFileInfo->ucEfCbmiExistFlg = ucEfCbmiExistFlg;

    /* �ļ������ڣ�������ȫ�ֱ����Ĵ��ڱ�־ */
    if (VOS_FALSE == ucEfCbmiExistFlg)
    {
        return;
    }

    /* �ļ����ڣ������ļ����� */
    pstEfCbmiFileInfo->usEfCbmiFileLen  = usEfLen;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ��USIM��CBMI�ļ���¼��ID������д�ڴ��� */
    pstCbmRangeids = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstCbmRangeids)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseUsimFileEfCbmiData: Fail to Alloc memory.");
        return;
    }

    PS_MEM_SET(pstCbmRangeids, 0x00, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    /* ����USIM EFCBMI��CBMI�ĸ��� */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pucCbmiOct                  = pucEf;
    pstCbmRangeids->usCbmirNum  = TAF_CBA_CountCbmiNum((VOS_UINT16 *)pucEf, usEfLen);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ���ݸ������ */
    if ( pstCbmRangeids->usCbmirNum >= TAF_CBA_MAX_CBMID_RANGE_NUM )
    {
        pstCbmRangeids->usCbmirNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    for (ulLoop = 0; ulLoop < pstCbmRangeids->usCbmirNum; ulLoop++)
    {
        ucMsgIdHigh = *(pucCbmiOct);
        pucCbmiOct++;

        ucMsgIdLow  = *(pucCbmiOct);
        pucCbmiOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));

        pstCbmRangeids->astCbmiRangeInfo[ulLoop].usMsgIdFrom = usMsgId;
        pstCbmRangeids->astCbmiRangeInfo[ulLoop].usMsgIdTo   = usMsgId;
        pstCbmRangeids->astCbmiRangeInfo[ulLoop].enRcvMode   = TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT;
    }

    /* �����ڴ��б� */
    (VOS_VOID)TAF_CBA_AddCbMiRangeListToActiveList(pstCbmRangeids);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmRangeids);

}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ParseUsimFileEfCbmirData
 ��������  : ����USIM�е�EFCBMIR�ļ�����, �����µ��ڴ���
 �������  : pstUsimGetFileRsp: USIM��EFCBMIR�ļ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� /z00214637
    �޸�����   : PS_USIM_GET_FILE_RLT_SUCCESS�滻ΪVOS_OK
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID TAF_CBA_ParseUsimFileEfCbmirData(
    VOS_UINT8                           ucEfCbmirExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
)
{
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                    *pstEfCbmirFileInfo;
    VOS_UINT32                                              ulLoop;
    TAF_CBA_CBMI_RANGE_LIST_STRU                           *pstCbmirList;
    VOS_UINT8                                               ucMsgIdHigh;
    VOS_UINT8                                               ucMsgIdLow;
    VOS_UINT16                                              usMsgId;
    VOS_UINT8                                              *pucCbmirOct;

    pstEfCbmirFileInfo = TAF_CBA_GetEfCbmiRangeInfo();

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pstEfCbmirFileInfo->ucEfCbmirExistFlg = ucEfCbmirExistFlg;

    if (VOS_FALSE == ucEfCbmirExistFlg)
    {
        return;
    }

    pstEfCbmirFileInfo->usEfCbmirFileLen  = usEfLen;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ��USIM��CBMIR�ļ���¼��ID������д��ʱ�ڴ��� */
    pstCbmirList = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));
    if (VOS_NULL_PTR == pstCbmirList)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseUsimFileEfCbmirData: Fail to Alloc memory.");
        return;
    }

    /* ����USIM EFCBMIR��CBMIR�ĸ��� */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pstCbmirList->usCbmirNum = TAF_CBA_CountCbmirNum((VOS_UINT16 *)pucEf, usEfLen);

    pucCbmirOct = pucEf;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ���ݸ������ */
    if ( pstCbmirList->usCbmirNum >= TAF_CBA_MAX_CBMID_RANGE_NUM )
    {
        pstCbmirList->usCbmirNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    for (ulLoop = 0; ulLoop < pstCbmirList->usCbmirNum; ulLoop++)
    {
        ucMsgIdHigh = *(pucCbmirOct);
        pucCbmirOct++;

        ucMsgIdLow  = *(pucCbmirOct);
        pucCbmirOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));
        pstCbmirList->astCbmiRangeInfo[ulLoop].usMsgIdFrom = usMsgId;

        ucMsgIdHigh = *(pucCbmirOct);
        pucCbmirOct++;

        ucMsgIdLow  = *(pucCbmirOct);
        pucCbmirOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));
        pstCbmirList->astCbmiRangeInfo[ulLoop].usMsgIdTo = usMsgId;

        pstCbmirList->astCbmiRangeInfo[ulLoop].enRcvMode = TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT;
    }

    /* �ȶ�range list���� */
    TAF_CBA_SortCbmiRangeList(pstCbmirList);

    /* �����ڴ���CBMIR�ķ�Χ */
    (VOS_VOID)TAF_CBA_AddCbMiRangeListToActiveList(pstCbmirList);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbmirList);
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_CBA_ApplyUsimInfo
 ��������  : ����USIM�ļ���NV��͵ײ�ģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_VOID TAF_CBA_ApplyUsimInfo(VOS_VOID)
{
    VOS_UINT32                          ulIsActiveListEmpty;

    /* CBS�����б��Ƿ�Ϊ�� */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();

    /* CBS�����б�Ϊ�ղ�����Ҫ��AS����CBS����ʱ��AS����CBS���� */
    if ((VOS_TRUE  == TAF_CBA_IsNeedActAsCbs())
     && (VOS_FALSE == ulIsActiveListEmpty))
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }

    /* ����NV��USIM���ļ�, ʹUSIM���к�UE��NV�е�CBMI��Ϣ����һ�� */
    if ( TAF_CBA_GetCbmiRangNum() > 0)
    {
        /* ����NV���е�MSGID �б� */
        TAF_CBA_WriteCbmiRangeListNvim();

        /* ����USIM�е�MSGID �ļ� */
        TAF_CBA_UpdateUsimFile();
    }

    /* ��ά�ɲ���Ϣ */
    TAF_CBA_SndOmCbmiDownloadListInfo();

    /* ��ά�ɲ���Ϣ */
    TAF_CBA_SndOmCbmiRangeList();

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ParseSpecUsimFileData
 ��������  : ����ָ��CBA�ļ�����Ϣ
 �������  :  VOS_UINT16                          usFileId,
    VOS_UINT8                           ucFileExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT32                          ulEfLen
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��27��
    ��    ��   : l00208543
    �޸�����   : STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CBA_ParseSpecUsimFileData (
    VOS_UINT16                          usFileId,
    VOS_UINT8                           ucFileExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          ulEfLen
)
{
    switch (usFileId)
    {
        case USIMM_USIM_EFCBMI_ID:
            TAF_CBA_ParseUsimFileEfCbmiData(ucFileExistFlg, pucEf, ulEfLen);
            break;

        case USIMM_USIM_EFCBMIR_ID:
             TAF_CBA_ParseUsimFileEfCbmirData(ucFileExistFlg, pucEf, ulEfLen);
             break;

        case USIMM_USIM_EFCBMID_ID:
             TAF_CBA_ParseUsimFileEfCbmidData(ucFileExistFlg, pucEf, ulEfLen);
             break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ParseSpecUsimFileData: The input is invalid.");
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ReadSpecificFileListRefreshFile
 ��������  : ָ���ļ��б��REFRESH�¼��������ļ����£�����ָ���ļ���Ϣ
 �������  : usFileId           �ļ�ID
             ulUsimmService     �ļ��漰��USIM���񣬽��з������������ļ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : STK������Ŀ
  2.��    ��   : 2013��11��04��                                                    
    ��    ��   : s00217060                                                         
    �޸�����   : VoLTE_PhaseII��Ŀ
*****************************************************************************/
VOS_VOID TAF_CBA_ReadSpecificFileListRefreshFile(
    VOS_UINT32                          ulFileId,
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 ulUsimmService,
    USIMM_STKREFRESH_IND_STRU          *pstRefreshInd
)
{
    VOS_UINT32                          ulEfLen;
    VOS_UINT32                          ulResult;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;      /*APP����*/
    VOS_UINT8                           ucFileExistFlg;
    VOS_UINT8                          *pucEf   = VOS_NULL_PTR;

    ulEfLen = 0;

    if (PS_USIM_SERVICE_NOT_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(ulUsimmService))
    {
        if (VOS_TRUE == TAF_GetSpecificFileListRefreshFileInfo((VOS_UINT16)ulFileId, pstRefreshInd, &enAppType))
        {
            /* ��ȡ TAF_CBA_EF_CBMI_ID USIM�ļ� */
            ucFileExistFlg = VOS_TRUE;
            ulResult = NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, enAppType);
            if (USIMM_API_SUCCESS != ulResult)
            {
                ucFileExistFlg = VOS_FALSE;
            }
            TAF_CBA_ParseSpecUsimFileData((VOS_UINT16)ulFileId, ucFileExistFlg, pucEf, (VOS_UINT16)ulEfLen);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ReadUsimFile
 ��������  : ����ָ��USIM�ļ���Ϣ
 �������  : usFileId           �ļ�ID
             ulUsimmService     �ļ��漰��USIM���񣬽��з������������ļ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : STK������Ŀ
  2.��    ��   : 2013��11��04��                                                    
    ��    ��   : s00217060                                                         
    �޸�����   : VoLTE_PhaseII��Ŀ
*****************************************************************************/
VOS_VOID TAF_CBA_ReadUsimFile(
    VOS_UINT32                          ulFileId,
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 ulUsimmService
)
{
    VOS_UINT32                          ulEfLen;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucFileExistFlg;
    VOS_UINT8                          *pucEf   = VOS_NULL_PTR;

    if (PS_USIM_SERVICE_NOT_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(ulUsimmService))
    {
        ucFileExistFlg = VOS_TRUE;
        ulResult = NAS_USIMMAPI_GetCachedFile(ulFileId, &ulEfLen, &pucEf, USIMM_GUTL_APP);
        if (USIMM_API_SUCCESS != ulResult)
        {
            ucFileExistFlg = VOS_FALSE;
        }

        TAF_CBA_ParseSpecUsimFileData((VOS_UINT16)ulFileId, ucFileExistFlg, pucEf, (VOS_UINT16)ulEfLen);

    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ProcRefreshInd
 ��������  : ��������USIMģ����ļ�������Ϣ
 �������  : pstMsg: ����USIMģ���VOS��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  2.��    ��   : 2013��11��04��                                                    
    ��    ��   : s00217060                                                         
    �޸�����   : VoLTE_PhaseII��Ŀ

*****************************************************************************/
VOS_VOID TAF_CBA_ProcRefreshInd(USIMM_STKREFRESH_IND_STRU *pstRefreshInd)
{
    if ((USIMM_REFRESH_FILE_LIST != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_3G_SESSION_RESET != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_ALL_FILE != pstRefreshInd->enRefreshType))
    {
        return;
    }

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
    if (USIMM_REFRESH_FILE_LIST == pstRefreshInd->enRefreshType)
    {
        TAF_CBA_ReadSpecificFileListRefreshFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI, pstRefreshInd);

        TAF_CBA_ReadSpecificFileListRefreshFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR, pstRefreshInd);

        TAF_CBA_ReadSpecificFileListRefreshFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB, pstRefreshInd);
    }
    else
    {
        TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI);

        TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR);

        TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB);

    }

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

    /* Ӧ��USIM�ļ���Ϣ�����غ�֪ͨ�ײ����ø��� */
    TAF_CBA_ApplyUsimInfo();

    return;
}


/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
 �� �� ��  : TAF_CBA_ParseUsimFileEfCbmidData
 ��������  : ����USIM�е�EFCBMID�ļ�����, ���µ��ڴ���
 �������  : pstUsimGetFileRsp: USIM��EFCBMIR�ļ�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� /z00214637
    �޸�����   : PS_USIM_GET_FILE_RLT_SUCCESS�滻ΪVOS_OK
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_VOID TAF_CBA_ParseUsimFileEfCbmidData(
    VOS_UINT8                           ucEfCbmidExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
)
{
    TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU                    *pstEfCbmidFileInfo;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU                        *pstCfgData;
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               ucMsgIdHigh;
    VOS_UINT8                                               ucMsgIdLow;
    VOS_UINT16                                              usMsgId;
    VOS_UINT8                                              *pucCbmiOct;

    pstEfCbmidFileInfo  = TAF_CBA_GetEfCbmidInfo();
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pstEfCbmidFileInfo->ucEfCbmidExistFlg = ucEfCbmidExistFlg;
    if (VOS_FALSE == ucEfCbmidExistFlg)
    {
        return;
    }
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    pstCfgData          = TAF_CBA_GetCbmiDownloadList();

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    pstEfCbmidFileInfo->usEfCbmidFileLen  = usEfLen;

    /* ����USIM EFCBMID��CBMI�ĸ��� */
    pucCbmiOct              = pucEf;
    pstCfgData->usCbmidNum  = TAF_CBA_CountCbmiNum((VOS_UINT16 *)pucEf, usEfLen);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ���ݸ������ */
    if ( pstCfgData->usCbmidNum >= TAF_CBA_MAX_CBMID_NUM )
    {
        pstCfgData->usCbmidNum = TAF_CBA_MAX_CBMID_NUM;
    }

    for (ulLoop = 0; ulLoop < pstCfgData->usCbmidNum; ulLoop++)
    {
        ucMsgIdHigh = *(pucCbmiOct);
        pucCbmiOct++;

        ucMsgIdLow  = *(pucCbmiOct);
        pucCbmiOct++;

        usMsgId     = (VOS_UINT16)( (ucMsgIdHigh << 8) | (ucMsgIdLow));
        pstCfgData->ausMsgId[ulLoop] = usMsgId;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_CountCbmiNum
 ��������  : ����USIM���д洢��CBMI��CBMID ����
 �������  : pusCbmi : ����������ʼָ�룻
             ulLength: ���������ȣ�
 �������  : ��
 �� �� ֵ  : CB Message Identifier�ĸ���; ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_CBA_CountCbmiNum(
    VOS_UINT16                         *pusCbmi,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT8                           ucCounter;
    VOS_UINT32                          ulRealLen;
    VOS_UINT8                           ucOffset;

    /* ��������ʵ�ʵĳ���  TAF_CBA_CBMI_UNIT_LEN * N */
    ulRealLen = ulLength;
    ucOffset  = ulLength%TAF_CBA_CBMI_UNIT_LEN;
    if (0 != ucOffset)
    {
        ulRealLen -= ucOffset;
    }

    /* �μ� 3GPP 31.102 4.2.14, 4.2.20 �ڵ����� , Unused entries shall be set to 'FF FF'. */
    ucCounter = (VOS_UINT8)(ulRealLen/TAF_CBA_CBMI_UNIT_LEN);
    while (ucCounter >= 1)
    {
        if (TAF_CBA_EF_MSGID_PADDING != pusCbmi[ucCounter - 1])
        {
            break;
        }
        ucCounter--;
    }
    return ucCounter;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_CountCbmirNum
 ��������  : ����CBMIR�ĸ�����
 �������  : pusCbmir: ����������ʼָ�룻
             ucLength: ���������ȣ��������������ֽ�Ϊ��λ��
 �������  : ��
 �� �� ֵ  : CB Message Identifier Range�ĸ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��5��20��
    ��    ��   : zhoujun /z40661
    �޸�����   : �˴��޸ĵ�Ŀ����Ϊ�˱�������������û�����0-65535
  3.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Fortify
*****************************************************************************/
VOS_UINT16 TAF_CBA_CountCbmirNum(
    VOS_UINT16                         *pusCbmir,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT8                           ucCounter;
    VOS_UINT16                          usTemp1;
    VOS_UINT16                          usTemp2;
    VOS_UINT32                          ulRealLen;
    VOS_UINT8                           ucOffset;

    /* ��������ʵ�ʵĳ���  TAF_CBA_CBMIR_UNIT_LEN*N */
    ulRealLen = ulLength;
    ucOffset  = ulLength%TAF_CBA_CBMIR_UNIT_LEN;
    if ( 0 != ucOffset  )
    {
        ulRealLen -= ucOffset;
    }

    /* �μ� 3GPP 31.102 4.2.22�ڵ����� , Unused entries shall be set to 'FF FF FF FF'. */
    ucCounter = (VOS_UINT8)(ulRealLen/TAF_CBA_CBMI_UNIT_LEN);
    while (2 <= ucCounter)
    {
        usTemp1 = pusCbmir[ucCounter - 1];
        usTemp2 = pusCbmir[ucCounter - 2];
        if ((TAF_CBA_EF_MSGID_PADDING != usTemp1)
         || (TAF_CBA_EF_MSGID_PADDING != usTemp2))
        {
            break;
        }
        ucCounter -= 2;
    }

    ucCounter /=2;

    return ucCounter;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_BuildUsimEfCbmiContent
 ��������  : ���췢�͸�USIM��EF CBMI�ļ�����
 �������  : ��
 �������  : pusMsgId: USIM��EF CBMI�ļ�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity

*****************************************************************************/
VOS_VOID TAF_CBA_BuildUsimEfCbmiContent(
    VOS_UINT16                         *pusMsgId
)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmidRangeList;
    TAF_CBA_CBMI_RANGE_STRU            *pstCbmidRange;
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU *pstEfCbmiFileInfo;
    VOS_UINT32                          ulEfCbmiLen;
    VOS_UINT8                           ucMsgIdHigh;
    VOS_UINT8                           ucMsgIdLow;
    VOS_UINT32                          ulCbmirRangeIdx;
    VOS_UINT16                          usCbmiNum;

    ulEfCbmiLen       = 0;
    pstCbmidRangeList = TAF_CBA_GetCbMiRangeList();
    usCbmiNum         = TAF_CBA_GetCbmiRangNum();

    if(usCbmiNum > TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    pstEfCbmiFileInfo = TAF_CBA_GetEfCbmiInfo();

    for ( ulCbmirRangeIdx = 0; ulCbmirRangeIdx < usCbmiNum; ulCbmirRangeIdx++ )
    {
        pstCbmidRange = &(pstCbmidRangeList->astCbmiRangeInfo[ulCbmirRangeIdx]);

        if ( (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmidRange->enRcvMode)
          && (pstCbmidRange->usMsgIdFrom == pstCbmidRange->usMsgIdTo)
          && (ulEfCbmiLen < (pstEfCbmiFileInfo->usEfCbmiFileLen/TAF_CBA_CBMI_UNIT_LEN)) )
        {
            ucMsgIdHigh = (pstCbmidRange->usMsgIdFrom)>>8;
            ucMsgIdLow  = (pstCbmidRange->usMsgIdFrom) & 0xFF;
            pusMsgId[ulEfCbmiLen] = ((ucMsgIdLow << 8) | ucMsgIdHigh);
            ulEfCbmiLen++;
        }

        if ( ulEfCbmiLen >= TAF_CBA_MAX_CBMID_RANGE_NUM )
        {
            break;
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_CBA_BuildUsimEfCbmirContent
 ��������  : ���췢�͸�USIM��EF CBMIR�ļ�����
 �������  : ��
 �������  : pstMsgRange: USIM�� EF CBMIR�ļ�����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2013��07��22��
    ��    ��   : j00177245
    �޸�����   : ����Fortify

*****************************************************************************/
VOS_VOID TAF_CBA_BuildUsimEfCbmirContent(
    TAF_CBA_USIM_CBMIR_STRU                                *pstMsgRange
)
{
    TAF_CBA_CBMI_RANGE_LIST_STRU                           *pstCbmidRangeList;
    TAF_CBA_CBMI_RANGE_STRU                                *pstCbmidRange;
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                    *pstEfCbmirFileInfo;
    VOS_UINT32                                              ulEfCbmirlLen;
    VOS_UINT8                                               ucMsgIdHigh;
    VOS_UINT8                                               ucMsgIdLow;
    VOS_UINT32                                              ulCbmidRangeIdx;
    VOS_UINT16                                              usCbmiNum;


    ulEfCbmirlLen      = 0;
    pstCbmidRangeList  = TAF_CBA_GetCbMiRangeList();
    usCbmiNum          = TAF_CBA_GetCbmiRangNum();

    if (usCbmiNum > TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
    }

    pstEfCbmirFileInfo = TAF_CBA_GetEfCbmiRangeInfo();

    for ( ulCbmidRangeIdx = 0; ulCbmidRangeIdx < usCbmiNum; ulCbmidRangeIdx++ )
    {
        pstCbmidRange = &(pstCbmidRangeList->astCbmiRangeInfo[ulCbmidRangeIdx]);

        if ( (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT == pstCbmidRange->enRcvMode)
          && (pstCbmidRange->usMsgIdFrom != pstCbmidRange->usMsgIdTo)
          && (ulEfCbmirlLen < (pstEfCbmirFileInfo->usEfCbmirFileLen/TAF_CBA_CBMIR_UNIT_LEN)) )
        {
            ucMsgIdHigh = (pstCbmidRange->usMsgIdFrom)>>8;
            ucMsgIdLow  = (pstCbmidRange->usMsgIdFrom) & 0xFF;
            pstMsgRange[ulEfCbmirlLen].usMsgIdFrom = ((ucMsgIdLow << 8) | ucMsgIdHigh);

            ucMsgIdHigh = (pstCbmidRange->usMsgIdTo)>>8;
            ucMsgIdLow  = (pstCbmidRange->usMsgIdTo) & 0xFF;
            pstMsgRange[ulEfCbmirlLen].usMsgIdTo = ((ucMsgIdLow << 8) | ucMsgIdHigh);
            ulEfCbmirlLen++;
        }

        if ( ulEfCbmirlLen >= TAF_CBA_MAX_CBMID_RANGE_NUM )
        {
            break;
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_CBA_UpdateUsimFileEfCbmiReq
 ��������  : ����ȫ�ֱ����е�MSG ID����USIM��EFCBMI�ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ��� ��
                 Client ID �� PID��ת������ ����η�װ�ɽṹ�塣
  3.��    ��   : 2013��6��7��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
  4.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_VOID TAF_CBA_UpdateUsimFileEfCbmiReq(VOS_VOID)
{
    TAF_CBA_USIM_EFCBMI_FILE_INFO_STRU *pstEfCbmiFileInfo;
    VOS_UINT32                          ulSndCbmiFileLen;
    VOS_UINT16                          ausMsgId[TAF_CBA_MAX_CBMID_RANGE_NUM];
    VOS_UINT32                          ulRet;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;
    VOS_UINT16                          usFileId;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    usFileId = USIMM_DEF_FILEID_BUTT;
    enSimType = TAF_SDC_GetSimType();
    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    /* CBMI�ļ��������򷵻� */
    pstEfCbmiFileInfo = TAF_CBA_GetEfCbmiInfo();
    if ( VOS_TRUE != pstEfCbmiFileInfo->ucEfCbmiExistFlg )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmiReq: File not exist in sim!");
        return;
    }

    PS_MEM_SET(ausMsgId, (VOS_CHAR)0xFF, sizeof(ausMsgId));

    /* ����ȫ�ֱ����е�MSG ID����EF�ļ����� */
    TAF_CBA_BuildUsimEfCbmiContent(ausMsgId);

    /* ���͸�USIM���ļ��������Զ̵�Ϊ��, */
    ulSndCbmiFileLen = pstEfCbmiFileInfo->usEfCbmiFileLen;
    if ( ulSndCbmiFileLen > sizeof(ausMsgId) )
    {
        ulSndCbmiFileLen = sizeof(ausMsgId);
    }

    if (TAF_SDC_SIM_TYPE_SIM == enSimType)
    {
        usFileId = USIMM_GSM_EFCBMI_ID;
    }
    else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        usFileId = USIMM_USIM_EFCBMI_ID;
    }
    else
    {
        return;
    }

    /* ���͸�USIM */
    TAF_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0,
                                    (VOS_UINT8)ulSndCbmiFileLen,
                                    (VOS_UINT8 *)ausMsgId);

    ulRet = NAS_USIMMAPI_SetFileReq(WUEPS_PID_TAF, 0, &stSetFileInfo);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmiReq: Write USIM failed!");
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_UpdateUsimFileEfCbmirReq
 ��������  : ����ȫ�ֱ����е�MSG ID����USIM��EFCBMIR�ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ��� ��
                 Client ID �� PID��ת������ ����η�װ�ɽṹ�塣
  3.��    ��   : 2013��6��7��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
  4.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
VOS_VOID TAF_CBA_UpdateUsimFileEfCbmirReq(VOS_VOID)
{
    TAF_CBA_USIM_EFCBMIR_FILE_INFO_STRU                    *pstEfCbmirFileInfo;
    VOS_UINT32                                              ulSndCbmirFileLen;
    TAF_CBA_USIM_CBMIR_STRU                                 astMsgRange[TAF_CBA_MAX_CBMID_RANGE_NUM];
    VOS_UINT32                                              ulRet;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;
    VOS_UINT16                          usFileId;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType = TAF_SDC_GetSimType();
    usFileId = USIMM_DEF_FILEID_BUTT;
    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    /* CBMIR�ļ��������򷵻� */
    pstEfCbmirFileInfo = TAF_CBA_GetEfCbmiRangeInfo();
    if ( VOS_TRUE != pstEfCbmirFileInfo->ucEfCbmirExistFlg )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmirReq: File not exist in sim!");
        return;
    }

    PS_MEM_SET(astMsgRange, (VOS_CHAR)0xFF, sizeof(astMsgRange));

    /* ����ȫ�ֱ����е�MSG ID����EF�ļ����� */
    TAF_CBA_BuildUsimEfCbmirContent(astMsgRange);

    /* ���͸�USIM���ļ��������Զ̵�Ϊ��, */
    ulSndCbmirFileLen = pstEfCbmirFileInfo->usEfCbmirFileLen;
    if ( ulSndCbmirFileLen > sizeof(astMsgRange) )
    {
        ulSndCbmirFileLen = sizeof(astMsgRange);
    }

    if (TAF_SDC_SIM_TYPE_SIM == enSimType)
    {
        usFileId = USIMM_GSM_EFCBMIR_ID;
    }
    else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        usFileId = USIMM_USIM_EFCBMIR_ID;
    }
    else
    {
        return;
    }

    /* ���͸�USIM */
    TAF_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0,
                                    (VOS_UINT8)ulSndCbmirFileLen,
                                    (VOS_UINT8 *)astMsgRange);

    ulRet = NAS_USIMMAPI_SetFileReq(WUEPS_PID_TAF, 0, &stSetFileInfo);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_UpdateUsimFileEfCbmirReq: Write USIM failed!");
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_UpdateUsimFile
 ��������  : ����ȫ�ֱ����е�MSG ID����USIM�ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2012��3��28��
    ��    ��   : w00176964
    �޸�����   : ��ȡUSIM�ļ��߼�����
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID  TAF_CBA_UpdateUsimFile(VOS_VOID)
{
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ���ڻ�ȡUSIM�ļ��Ĺ�����,����д�ļ� */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ���� CBMI �ļ� */
    TAF_CBA_UpdateUsimFileEfCbmiReq();

    /* ���� CBMIR �ļ� */
    TAF_CBA_UpdateUsimFileEfCbmirReq();
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ProcUsimSetFileRsp
 ��������  : ������յ�USIM���͹�����SetFileRsp��ԭ��
 �������  : pMsg:USIM���͹����������ļ�������
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2012��12��26��
    ��    ��   : ����/z00214637
    �޸�����   : PS_USIM_SET_FILE_RLT_SUCCESSת��ΪVOS_OK
  3.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_UINT32  TAF_CBA_ProcUsimSetFileRsp(
    USIMM_UPDATEFILE_CNF_STRU           *pstSetFileRsp
)
{

    VOS_UINT32                          ulEfId;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstSetFileRsp->stFilePath.ulPathLen, pstSetFileRsp->stFilePath.acPath, &ulEfId))
    {
        return VOS_ERR;
    }

    if (((USIMM_GSM_EFCBMI_ID != ulEfId) && (USIMM_USIM_EFCBMI_ID != ulEfId))
     && ((USIMM_GSM_EFCBMIR_ID != ulEfId) && (USIMM_USIM_EFCBMIR_ID != ulEfId))
     && ((USIMM_GSM_EFCBMID_ID != ulEfId) && (USIMM_USIM_EFCBMID_ID != ulEfId)))
    {
        return VOS_ERR;
    }

    if (VOS_OK != (pstSetFileRsp->stCmdResult.ulResult))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_CBA_ProcUsimSetFileRsp:Write Files Error",
                        ulEfId);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_SndUsimCbMsg
 ��������  : �洢EFCBMID��ָ����CBS��Ϣ
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCbMsg           - ��ҪEnvelope Download��USIM��CBS����;
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��14��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ���
  3.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:SI_STK_EnvelopeDownload�ӿ�����client ID
  4.��    ��   : 2013��6��7��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿڵ���
*****************************************************************************/
VOS_VOID TAF_CBA_SndUsimCbMsg(
    VOS_UINT32                          ulSendPID,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbMsg
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPE_STRU                stDataDownLoad;

    PS_MEM_SET(&stDataDownLoad, 0, sizeof(stDataDownLoad));

    /* ��д���͸�USIM�Ĺ̶��ֶ� */
    stDataDownLoad.enEnvelopeType  = SI_STK_ENVELOPE_CBDOWN;
    stDataDownLoad.DeviceId.ucSDId = SI_DEVICE_NETWORK;
    stDataDownLoad.DeviceId.ucDDId = SI_DEVICE_UICC;

    stDataDownLoad.uEnvelope.CBDown.OP_CBPage        = 1;

    /* Խ�籣�� */
    if (pstCbMsg->ulLen > SI_STK_DATA_MAX_LEN)
    {
        pstCbMsg->ulLen = SI_STK_DATA_MAX_LEN;
    }

    stDataDownLoad.uEnvelope.CBDown.CBPage.ulLen     = (VOS_UINT8)pstCbMsg->ulLen;

    PS_MEM_CPY(stDataDownLoad.aucData, pstCbMsg->aucData, pstCbMsg->ulLen);

    stDataDownLoad.uEnvelope.CBDown.CBPage.pucCBPage = stDataDownLoad.aucData;

    /* ֪ͨUSIM����Envelope */

    ulRet = NAS_STKAPI_EnvelopeDownload(ulSendPID, MN_CLIENT_ID_BROADCAST,&stDataDownLoad);


    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "MN_MSG_EnvelopeCbm: Fail to envelope download Cbm in USIM!");
    }

    return;
}

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted TAF_CBA_IsUsimFileReadFinished */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */
/*lint -restore */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
